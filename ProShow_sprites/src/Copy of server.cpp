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

    //iWg = RWindowGroup(iWs);
    //iWg.Construct((TUint32)&iWg,EFalse);
    //iWg.SetOrdinalPosition(0,ECoeWinPriorityAlwaysAtFront);
    //iWg.EnableReceiptOfFocus(EFalse);
    iScreen->CreateContext(iGc);
    //CleanupStack::PushL(iGc);
    //iWindow = RWindow(iWs);
    //iWindow.Construct(iWg,(TUint32)&iWg+1);
    //iWindow.SetBackgroundColor(TRgb(KRgbWhite));
    //iWindow.Activate();
    //iWindow.SetExtent(TPoint(0,0),TSize(1,1));
    //iWindow.SetNonFading(ETrue);

   // iImageLoaded = EFalse;
    //iGetEvent = EFalse;
    //iWaitEvent = EFalse;
    //iIsDraw = EFalse;
    iSprite = new(ELeave) RWsSprite(iWs);
    iMask=new(ELeave) CFbsBitmap();
    iMask->Create(TSize(100,100),EColor16M);
    TPoint point(0,0);
    iSprite->Construct(iWg,point,0);
    iMember.iBitmap=NULL;
    iMember.iMaskBitmap=NULL;
    iMember.iOffset=TPoint(0,0);
    iMember.iInterval=TTimeIntervalMicroSeconds32(0);
    iMember.iInvertMask=EFalse;
    iSprite->AppendMember(iMember);
    iSprite->SetPosition(point);
    iSprite->Activate();
    iWs.Flush();

    }
void CMyServer::Hide()
    {
	iIsVisible=EFalse;
	iMember.iBitmap=NULL; // bitmap is NULL -> sprite is hidden
	iMember.iMaskBitmap=NULL;
	iSprite->SetPosition(TPoint(iConfig.iX,iConfig.iY));
	iSprite->UpdateMember(0,iMember);
	iWs.Flush();
    }
void CMyServer::Show()
    {
	iIsVisible=ETrue;
	iMember.iBitmap=iBitmap; //bitmap isn't NULL -> sprite is shown
	iMember.iMaskBitmap=iBitmap;
	iSprite->UpdateMember(0,iMember);
	iSprite->SetPosition(TPoint(iConfig.iX,iConfig.iY));
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
    __LOGSTR1("focused app with uid: 0x%x",gn->AppUid());
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
    iWg.EnableFocusChangeEvents();
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
void CMyServer::Draw()
    {
	GetOrientation();
if(iOrientation == 0)
{
	iWindow.SetPosition(TPoint(iConfig.iX,iConfig.iY));
#ifdef __DEBUG
		__LOGSTR("iWindow set position portrait");
#endif
}else{
	iWindow.SetPosition(TPoint(iConfig.iLandX,iConfig.iLandY));
#ifdef __DEBUG
		__LOGSTR("iWindow set position landscape");
#endif
	}
    iWindow.SetVisible(ETrue);
    iGc->Activate(iWindow);
    iWindow.BeginRedraw(iRect);
    iGc->Clear();
    iGc->DrawBitmap(iRect,iBitmap);
    iWindow.EndRedraw();
    iGc->Deactivate();
    iWs.Flush();
	//}
    //iIsDraw=EFalse;
    //iGetEvent=EFalse;
    //iWaitEvent=ETrue;
    //if(isVisible)
	//{
	//iMember.iBitmap=iBitmap;
	//iMember.iMaskBitmap=iBitmap;
//	}
  //  iSprite->UpdateMember(0,iMember);
    //iSprite->SetPosition(TPoint(100,100));
    //iWs.Flush();

    }

