/*
 * GisWeather : server.cpp
 *
 *  Created on: 25.11.2010
 *  Author: vl
 */

#include "server.h"

#ifndef __DEBUG
#define __DEBUG 1
#endif

CMyServer::CMyServer() : CActive(EPriorityHigh)
    {

    }
CMyServer::~CMyServer()
    {
    if(iBitmap)
	{
    	delete iBitmap;
    	iBitmap = NULL;
	}
    if(iScreen)
    {
    	delete iScreen;
    	iScreen = NULL;
    }
    if(iGc)
    {
    	delete iGc;
    	iGc = NULL;
    }
    iFs.Close();
    }
CMyServer* CMyServer::NewL()
    {
    CMyServer* self = new(ELeave) CMyServer();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

void CMyServer::ConstructL()
    {
    #ifdef __DEBUG
    __LOGSTR("Construct");
    #endif
    CActiveScheduler::Add(this);
    iWs = RWsSession();
    iFs.Connect();
    ReadConf();
    #ifdef __DEBUG
    __LOGSTR("ReadConfComplete");
    #endif

    iWs.Connect(iFs);
    iTaskList = new(ELeave) TApaTaskList(iWs);

    iScreen = new(ELeave) CWsScreenDevice(iWs);
    CleanupStack::PushL(iScreen);
    iScreen->Construct();
    CleanupStack::Pop(iScreen);
    iEngine = CreateProfileEngineL();
    iOldName = iEngine->ActiveProfileL()->ProfileName().Name();

    //__LOGSTR1("name:%S",&iEngine->ActiveProfileL()->ProfileName().Name());
    // get font name
    	TTypefaceSupport iTypefaceSupport;
    	TBuf<KMaxTypefaceNameLength> fontName;
    	fontName.FillZ(KMaxTypefaceNameLength);
    	iScreen->TypefaceSupport(iTypefaceSupport, 0);
    	fontName = iTypefaceSupport.iTypeface.iName;
    	// get font
    	TFontSpec FontSpec(fontName, 10*iConfig.iHeight);
    	FontSpec.iTypeface.SetIsProportional(ETrue);
    	iScreen->GetNearestFontInTwips(iFont,FontSpec);

    	iIsVisible=EFalse;
    	//calculate size
    //	TBuf<150> temp;
    	//temp.Fill('P',150);
    	iSize=TSize(iFont->TextWidthInPixels(iOldName),iFont->HeightInPixels()*2+3);
    	//__LOGSTR2("iFont->TextWidthInPixels(temp):%d,iFont->HeightInPixels()*2+3:%d",iFont->TextWidthInPixels(temp),iFont->HeightInPixels()*2+3);
    	iPos=TPoint(iConfig.iX,iConfig.iY);
    	// create image and it's mask
    	iBitmap=new(ELeave) CFbsBitmap();
    	iMask=new (ELeave) CFbsBitmap();

    	iBitmap->Create(iSize,EColor16M);
    	iMask->Create(iSize,EColor16M);

    	CFbsBitmapDevice* BitDevice=CFbsBitmapDevice::NewL(iBitmap);
    	CFbsBitmapDevice* MaskDevice=CFbsBitmapDevice::NewL(iMask);

    	BitDevice->CreateContext(iBitGc);
    	MaskDevice->CreateContext(iMaskGc);

    	iBitGc->UseFont(iFont);
    	iMaskGc->UseFont(iFont);
    	//create window group with high priority (always at front)
    	iWg=new (ELeave) RWindowGroup(iWs);
    	iWg->Construct(reinterpret_cast<TUint32>(&iWg));
    	iWg->EnableReceiptOfFocus(EFalse);
    	iWg->SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront);
    	//create sprite
    	iSprite= new (ELeave) RWsSprite(iWs);
    	iSprite->Construct(*iWg,iPos,0);
    	iMember.iBitmap=NULL; // no image
    	iMember.iMaskBitmap=NULL;
    	iMember.iOffset=TPoint(0,0);
    	iMember.iInterval=TTimeIntervalMicroSeconds32(0);
    	iMember.iInvertMask=ETrue; // black - not transparadent, white - transparadent
    	iSprite->AppendMember(iMember);
    	iSprite->SetPosition(iPos);

    	iSprite->Activate();
    	iWs.Flush();
    	Draw(iOldName);
    	Hide();

    }
void CMyServer::Hide()
    {
	__LOGSTR("Hide");
	iIsVisible=EFalse;
	iMember.iBitmap=NULL; // bitmap is NULL -> sprite is hidden
	iMember.iMaskBitmap=NULL;
	iSprite->SetPosition(iPos);
	iSprite->UpdateMember(0,iMember);
	iWs.Flush();
    }
void CMyServer::Show()
    {
	__LOGSTR("Show");
	iNewName = iEngine->ActiveProfileL()->ProfileName().Name();
	if(iNewName != iOldName)
	{
		Draw(iNewName);
		iOldName = iNewName;
		return;
	}
	iIsVisible=ETrue;
	//iMember.iBitmap=iBitmap; //bitmap isn't NULL -> sprite is shown
//	iMember.iMaskBitmap=iMask;
	iMember.iBitmap=iMask; //bitmap isn't NULL -> sprite is shown
	iMember.iMaskBitmap=iBitmap;
	iSprite->UpdateMember(0,iMember);
	iSprite->SetPosition(iPos);
	iWs.Flush();
    }

void CMyServer::RunL()
    {
    #ifdef __DEBUG
    __LOGSTR("RunL");
    #endif
	GetWgEvent();
    }
TInt CMyServer::RunError(TInt aError)
    {
#ifdef __DEBUG
    __LOGSTR1("RunError: %d",aError);
#endif
    return KErrNone;
    }
void CMyServer::DoCancel()
    {
    iWs.EventReadyCancel();
    }

void CMyServer::ReadConf()
    {
    #ifdef __DEBUG
    __LOGSTR("ReadConf");
    #endif
    if(iFile.Open(iFs,KFileConfig,EFileRead) != KErrNone)
	{//file not exist
    #ifdef __DEBUG
    __LOGSTR("File not exist");
    #endif
	TInt err = iFs.MkDirAll(_L("C:\\System\\Apps\\ProShow\\"));
    #ifdef __DEBUG
	__LOGSTR1("Mkdir: %d",err);
    #endif
	iFile.Replace(iFs,KFileConfig,EFileRead|EFileWrite);
	TFileText text;
	iFile.Write(0,_L8("\xff\xfe"));//signature
	text.Set(iFile);
	text.Write(_L("140"));//iX
	text.Write(_L("190"));//iY
	text.Write(_L("120"));//iLandY
	text.Write(_L("150"));//iLandX
	text.Write(_L("15"));//iHeight
	text.Write(_L("0xffffff"));//TRgb white

	text.Write(_L("0x101fd64c"));//default UID
	iFile.Close();
	ReadConf();
	}else{
    #ifdef __DEBUG
	__LOGSTR("File exist");
    #endif
	//file exist
	TFileText text;
	TLex lex;
	TBuf<32> buf;
	text.Set(iFile);
	text.Read(buf);
	lex.Assign(buf);
	lex.Val(iConfig.iX);

	text.Read(buf);
	lex.Assign(buf);
	lex.Val(iConfig.iY);

	text.Read(buf);
	lex.Assign(buf);
	lex.Val(iConfig.iLandY);

	text.Read(buf);
	lex.Assign(buf);
	lex.Val(iConfig.iLandX);

	text.Read(buf);
	lex.Assign(buf);
	lex.Val(iConfig.iHeight);

	text.Read(buf);
	if(buf.Left(2)==_L("0x"))
		buf.Delete(0,2);
	lex.Assign(buf);
	TUint32 rgb;
	lex.Val(rgb,EHex);
	iConfig.iColor = rgb;

	text.Read(buf);
	buf.Delete(0,2); // delete 0x
	lex.Assign(buf);
	TUint tempuid;
	lex.Val(tempuid,EHex);
	iConfig.iUid.iUid = tempuid;

	iFile.Close();
	}
    }
void CMyServer::GetWgEvent()
    {
    #ifdef __DEBUG
    __LOGSTR1("GetWgEvent,iStatus: %d",iStatus.Int());
    #endif
   if(iStatus == KErrNone)
	{
    TWsEvent e;
    iWs.GetEvent(e);
    #ifdef __DEBUG
    __LOGSTR1("event: %d",e.Type());
    #endif
	}
    TInt WgId = iWs.GetFocusWindowGroup();
    CApaWindowGroupName* gn = CApaWindowGroupName::NewLC(iWs, WgId);
    #ifdef __DEBUG
    __LOGSTR2("focused app with uid: 0x%x,config uid: 0x%x",gn->AppUid(),iConfig.iUid);
    #endif
    if(gn->AppUid() == iConfig.iUid)
	{

    	Show();
	//Draw();
    //iWindow.SetVisible(ETrue);
    //iWs.Flush();
    #ifdef __DEBUG
	__LOGSTR("UIDs ==");
    #endif
	}else{
	//iWindow.SetVisible(EFalse);
		Hide();
	iWs.Flush();
    #ifdef __DEBUG
	__LOGSTR("UIDs !=");
    #endif
	}
    WaitWgEvent();
    }
void CMyServer::WaitWgEvent()
    {
    iWg->EnableFocusChangeEvents();
    //iWg->EnableGroupChangeEvents();
    iWg->EnableGroupListChangeEvents();
    //iWg->EnableScreenChangeEvents();
    #ifdef __DEBUG
    __LOGSTR("WaitWgEvent");
    #endif
    iWs.EventReady(&iStatus);
    SetActive();
    }

void CMyServer::GetOrientation()
{
	iScreen->GetDefaultScreenSizeAndRotation(iPixels);
	iOrientation = iPixels.iRotation;
#ifdef __DEBUG
	__LOGSTR1("iOrientation: %d",iOrientation);
#endif
}
void CMyServer::Draw(const TDesC& aText)
    {
	__LOGSTR("Draw()");
	//TBuf<256> text(iEngine->ActiveProfileL()->ProfileName().Name());
	//__LOGSTR1("iText: %S",&text);
	TRgb color(iConfig.iColor);
		//draw
		iBitGc->SetBrushColor(color);
		iBitGc->SetBrushStyle(CFbsBitGc::ESolidBrush);
		iBitGc->SetPenColor(color);
		iBitGc->DrawRect(TRect(-1,-1,iSize.iWidth+1,iSize.iHeight+1));
		iBitGc->SetBrushColor(color);
		iBitGc->SetBrushStyle(CFbsBitGc::ENullBrush);
		iBitGc->SetPenColor(color);
		iBitGc->UseFont(iFont);
		iBitGc->DrawText(aText,TRect(0,0,iFont->TextWidthInPixels(aText),iFont->HeightInPixels()),iFont->AscentInPixels(),CFbsBitGc::ELeft,0);
		//iBitGc->DrawText(arr->MdcaPoint(1),TRect(0,3+iFont->HeightInPixels(),iFont->TextWidthInPixels(arr->MdcaPoint(1)),3+2*iFont->HeightInPixels()),iFont->AscentInPixels(),CFbsBitGc::ELeft,0);

		TRgb TransColor(0,0,0);
		iMaskGc->SetBrushColor(KRgbWhite);
		iMaskGc->SetBrushStyle(CFbsBitGc::ESolidBrush);
		iMaskGc->SetPenColor(KRgbWhite);
		iMaskGc->DrawRect(TRect(-1,-1,iSize.iWidth+1,iSize.iHeight+1));
		iMaskGc->SetPenColor(TransColor);
		iMaskGc->SetBrushColor(TransColor);
		iMaskGc->SetBrushStyle(CFbsBitGc::ENullBrush);
		iMaskGc->UseFont(iFont);
		iMaskGc->DrawText(aText,TRect(0,0,iFont->TextWidthInPixels(aText),iFont->HeightInPixels()),iFont->AscentInPixels(),CFbsBitGc::ELeft,0);
		//iMaskGc->DrawText(arr->MdcaPoint(1),TRect(0,3+iFont->HeightInPixels(),iFont->TextWidthInPixels(arr->MdcaPoint(1)),3+2*iFont->HeightInPixels()),iFont->AscentInPixels(),CFbsBitGc::ELeft,0);
		//CEikonEnv::Static()->InfoMsg(iText->Des());
	//update image (if needed)
		if (iIsVisible)
			{
			iMember.iBitmap=iBitmap;
			iMember.iMaskBitmap=iMask;
			}

		iSprite->UpdateMember(0,iMember);
		iSprite->SetPosition(iPos);
		iWs.Flush();
    }

