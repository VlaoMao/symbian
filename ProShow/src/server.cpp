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
    iWg = RWindowGroup(iWs);
    iWg.Construct((TUint32)&iWg,EFalse);
    iWg.SetOrdinalPosition(0,ECoeWinPriorityAlwaysAtFront);
    iWg.EnableReceiptOfFocus(EFalse);
    iScreen->CreateContext(iGc);
    iWindow = RWindow(iWs);
    iWindow.Construct(iWg,(TUint32)&iWg+1);

    iWindow.Activate();
    iWindow.SetExtent(TPoint(0,0),TSize(1,1));
    iWindow.SetRequiredDisplayMode(EColor16MA);
    TRgb backgroundColour = KRgbWhite;
    if(KErrNone == iWindow.SetTransparencyAlphaChannel())
    	{
    	backgroundColour.SetAlpha(0);
    	}
    iWindow.SetBackgroundColor(backgroundColour);

    iEngine = CreateProfileEngineL();
    iOldName = iEngine->ActiveProfileL()->ProfileName().Name();

    GetFontSize();

    iWindow.SetSize(iSize);
	#ifdef __DEBUG
    __LOGSTR2("iSize1: %d,iSize2: %d",iSize.iWidth,iSize.iHeight);
	#endif
    iPos=TPoint(iConfig.iX,iConfig.iY);

    iWs.Flush();
    Draw(iOldName);
    }
void CMyServer::GetFontSize()
	{
	iFontName.FillZ(KMaxTypefaceNameLength);
	iScreen->TypefaceSupport(iTypefaceSupport, 0);
	iFontName = iTypefaceSupport.iTypeface.iName;
	// get font
	iFontSpec = TFontSpec(iFontName, 10*iConfig.iHeight);
	iFontSpec.iTypeface.SetIsProportional(ETrue);
	iScreen->GetNearestFontInTwips(iFont,iFontSpec);

	iSize=TSize(iFont->TextWidthInPixels(iOldName),iFont->HeightInPixels()*2);
	__LOGSTR2("iSize.width: %d, iSize.height: %d",iSize.iWidth,iSize.iHeight);
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

	text.Write(_L("0x102750f0"));//default UID
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
    /*
    TUint handle = iWs.GetWindowGroupHandle(WgId);
    RWindowGroup wg_test = RWindowGroup(iWg);
    __LOGSTR2("handle: %d, constuct: %d",handle,wg_test.Construct(handle));*/

    CApaWindowGroupName* gn = CApaWindowGroupName::NewLC(iWs, WgId);
    #ifdef __DEBUG
    __LOGSTR2("focused app with uid: 0x%x,config uid: 0x%x",gn->AppUid(),iConfig.iUid);
    #endif
    if(gn->AppUid() == TUid::Uid(0xa0002f97))
    	{

        CApaWindowGroupName* test = CApaWindowGroupName::NewL(iWs,WgId);
        __LOGSTR2("1: system: %d, hidden: %d",test->IsSystem(),test->Hidden());
        test->SetSystem(ETrue);
        test->SetHidden(ETrue);
        __LOGSTR2("2: system: %d, hidden: %d",test->IsSystem(),test->Hidden());
        CEikonEnv* env = new CEikonEnv;
        env->ConstructL();
    	}
    if(gn->AppUid() == iConfig.iUid)
	{
    	iOldName = iEngine->ActiveProfileL()->ProfileName().Name();
    	Draw(iOldName);
    #ifdef __DEBUG
	__LOGSTR("UIDs ==");
    #endif
	}else{
	iWindow.SetVisible(EFalse);
	iWs.Flush();
    #ifdef __DEBUG
	__LOGSTR("UIDs !=");
    #endif
	}
    WaitWgEvent();
    }
void CMyServer::WaitWgEvent()
    {
    iWg.EnableFocusChangeEvents();
    //iWg->EnableGroupChangeEvents();
    iWg.EnableGroupListChangeEvents();
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
	GetFontSize();
	iWindow.SetSize(iSize);
	#ifdef __DEBUG
	__LOGSTR("Draw");
	#endif
	iWindow.SetPosition(iPos);
	iWindow.SetVisible(ETrue);
	iGc->Activate(iWindow);
	//TRect Drw(iPos,iSize);
	iRect = TRect(iPos,iSize);
	iWindow.Invalidate(iRect);
	iWindow.BeginRedraw();
	iGc->Clear();
	iGc->SetPenColor(iConfig.iColor);
	iGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	iGc->UseFont(iFont);
	iGc->DrawText(aText,TRect(0,0, iRect.Width(),iRect.Height()),iFont->FontMaxAscent(), CGraphicsContext::ECenter, 0);
    iWindow.EndRedraw();
    iGc->Deactivate();
    iWs.Flush();
    }

