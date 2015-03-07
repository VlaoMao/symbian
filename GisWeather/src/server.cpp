/*
 * GisWeather : server.cpp
 *
 *  Created on: 25.11.2010
 *  Author: vl
 */

#include "server.h"

CMyServer::CMyServer(TBool aAutostart) : CActive(EPriorityHigh),iAutostart(aAutostart)
    {

    }
CMyServer::~CMyServer()
    {
    if(iDecoder)
	{
    	delete iDecoder;
    	iDecoder = NULL;
	}
    if(iBitmap)
	{
    	delete iBitmap;
    	iBitmap = NULL;
	}
    if(iSchedulerWait)
    {
    	delete iSchedulerWait;
    	iSchedulerWait = NULL;
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
CMyServer* CMyServer::NewL(TBool aAutostart)
    {
    CMyServer* self = new(ELeave) CMyServer(aAutostart);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }
void CMyServer::TimeEvent(const TEventTime aEvent)
    {
    #ifdef __DEBUG
    __LOGSTR("TimeEvent");
    #endif
    switch(aEvent)
	{
    case EEventTimeRefresh:
	Refresh();
	break;
    default:
	break;
	}
    }
void CMyServer::ConstructL()
    {
    #ifdef __DEBUG
    __LOGSTR("Construct");
    #endif
    CActiveScheduler::Add(this);
    iIsImageLoaded = EFalse;
    iWs = RWsSession();
    iFs.Connect();
    ReadConf();
    #ifdef __DEBUG
    __LOGSTR("ReadConfComplete");
    __LOGSTR2("iAutostart: %d,iConfig.iAutoStartEnabled: %d",iAutostart,iConfig.iAutostartEnabled);
	#endif
    if(iAutostart)//Передан ли сигнал автозапуска
    {
    	if(!iConfig.iAutostartEnabled)//Автозапуск включен?
    	{
		#ifdef __DEBUG
    	__LOGSTR("Autostart is not enabled, exitting");
		#endif
    	User::Exit(KErrNone);
    	}
    }
    iTimeMan = CTimeManagement::NewL(this);
    iTimeMan->SetTimeFrom(iConfig.iFromHour,iConfig.iFromMinute);
    iTimeMan->SetTimeDo(iConfig.iDoHour,iConfig.iDoMinute);
    iTimeMan->iInterval = iConfig.iPeriod;
    iTimeMan->Start();
    iWs.Connect(iFs);
    iTaskList = new(ELeave) TApaTaskList(iWs);
    iSchedulerWait = new(ELeave) CActiveSchedulerWait();

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
    iWindow.SetBackgroundColor(TRgb(KRgbWhite));
    iWindow.Activate();
    iWindow.SetExtent(TPoint(0,0),TSize(1,1));
    iWindow.SetNonFading(ETrue);

    TInt err = iFileTime.Open(iFs,KFileNameTime,EFileRead|EFileShareAny);
    if(err == KErrNone)
	{
    #ifdef __DEBUG
	__LOGSTR("Check: file exists");
    #endif
	iFileExists = ETrue;
	iFile.Close();
	LoadImage();
	}else{
	iFileExists = EFalse;
    #ifdef __DEBUG
	__LOGSTR("informer file not exists, refresh image");
    #endif
	Refresh();
	}
    }

void CMyServer::LoadImage()
    {
    __LOGSTR("Load image");
    if(iFileExists == EFalse)
    	return;
    iBitmap = new(ELeave) CFbsBitmap();
    CleanupStack::PushL(iBitmap);
    //iDecoder = CDecoder::NewL(iRect);
    iDecoder = CImageDecoder::FileNewL(iFs,KFileName);
    iFrameInfo = iDecoder->FrameInfo(0);
    iRect = iFrameInfo.iFrameCoordsInPixels;
    iBitmap->Create(iRect.Size(),EColor16M);
    iDecoder->Convert(&iStatus,*iBitmap);

    SetActive();
    iSchedulerWait->Start();
    CleanupStack::Pop(iBitmap);
    __LOGSTR("Image converted");
    }
void CMyServer::RunL()
    {
    #ifdef __DEBUG
    __LOGSTR("RunL");
    #endif
    if(iSchedulerWait->IsStarted())
	{
	if(iStatus == KErrNone)
	    {
		#ifdef __DEBUG
		__LOGSTR2("bitmapHeight: %d, bitmapWidth: %d",iBitmap->SizeInPixels().iHeight,iBitmap->SizeInPixels().iWidth);
		#endif
	    iWindow.SetExtent(TPoint(iConfig.iX,iConfig.iY),iBitmap->SizeInPixels());
	    iIsImageLoaded = ETrue;
	    }
	iSchedulerWait->AsyncStop();
	Draw();
	iWindow.SetVisible(EFalse);
	}else{
	GetWgEvent();
	}
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
    if(iFile.Open(iFs,KFileConfig,EFileRead) != KErrNone)//file not exist
	{
    #ifdef __DEBUG
    __LOGSTR("File not exist");
    #endif
	TInt err = iFs.MkDirAll(_L("C:\\System\\Apps\\GisWeather\\"));
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
	text.Write(_L("12"));//iPeriod
	text.Write(_L("0x101fd64c"));//default UID
	text.Write(_L(""));//access point
	text.Write(_L(""));//time from
	text.Write(_L(""));//time do
	text.Write(_L("1"));//autostart on
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
	lex.Val(iConfig.iPeriod);

	text.Read(buf);
	buf.Delete(0,2); // delete 0x
	lex.Assign(buf);
	TUint tempuid;
	lex.Val(tempuid,EHex);
	iConfig.iUid.iUid = tempuid;

	text.Read(buf);//IAP Name;

	TBuf<16> hour;
	TBuf<16> minute;
	text.Read(buf);//time from
	TInt do_ = buf.Find(_L(":"));
	if(do_ != KErrNotFound)
	    {
	    hour = buf.Left(do_);
	    minute = buf.Right(buf.Length()-(do_+1));
	    lex.Assign(hour);
	    lex.Val(iConfig.iFromHour);
	    lex.Assign(minute);
	    lex.Val(iConfig.iFromMinute);
	    }else{
	    iConfig.iFromHour = 0;
	    iConfig.iFromMinute = 0;
	    }
	text.Read(buf);//time do
	do_ = buf.Find(_L(":"));
	if(do_ != KErrNotFound)
	    {
	    hour = buf.Left(do_);
	    minute = buf.Right(buf.Length()-(do_+1));
	    lex.Assign(hour);
	    lex.Val(iConfig.iDoHour);
	    lex.Assign(minute);
	    lex.Val(iConfig.iDoMinute);
	    }else{
	    iConfig.iDoHour = 23;
	    iConfig.iDoMinute = 59;
	    }
	text.Read(buf);
	lex.Assign(buf);
	lex.Val(iConfig.iAutostartEnabled);
	iFile.Close();
	}
    }
void CMyServer::GetWgEvent()
    {
    #ifdef __DEBUG
    __LOGSTR1("GetWgEvent,iStatus: %d",iStatus.Int());
    #endif

    User::LeaveIfError(iStatus.Int());

    iWs.GetEvent(iEventType);
    #ifdef __DEBUG
    __LOGSTR1("event: %d",iEventType.Type());
    if(iEventType.Type() == EEventPointer || iEventType.Type() == EEventPointerEnter || iEventType.Type() == EEventDragDrop)
    	{

    	/*TInt posy,posx;
    	TPoint temp = iEventType.Pointer()->iPosition - iOldPoint;
    	posy = temp.iY;
    	posx = temp.iX;
    	iWindow.SetPosition(iEventType.Pointer()->iPosition - iOldPoint);
    	iOldPoint = iEventType.Pointer()->iPosition;
    	__LOGSTR2("Pointer event!, posx: %d, posy: %d",posx,posy);*/
    	}
    #endif

    TInt WgId = iWs.GetFocusWindowGroup();
    CApaWindowGroupName* gn = CApaWindowGroupName::NewLC(iWs, WgId);
    #ifdef __DEBUG
    __LOGSTR1("focused app with uid: 0x%x",gn->AppUid());
    #endif
    if(gn->AppUid() == iConfig.iUid)
	{
	Draw();
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
    #ifdef __DEBUG
    __LOGSTR("WaitWgEvent");
    #endif
    iWs.EventReady(&iStatus);
    SetActive();
    }
void CMyServer::Refresh()
    {
    #ifdef __DEBUG
    __LOGSTR("Refresh");
    #endif
    iFileTime.Close();
    RApaLsSession LsSession;
    CApaCommandLine* cmd = CApaCommandLine::NewL();
    LsSession.Connect();
    cmd->SetExecutableNameL(_L("GisWeatherDownloader.exe"));
    cmd->SetCommandL(EApaCommandBackground);
    TInt ret = LsSession.StartApp(*cmd);
    #ifdef __DEBUG
    __LOGSTR1("StartApp: %d",ret);
    #endif
    if(ret == KErrNone)
	{
	RFile file;
	file.Replace(iFs,KFileExit,EFileRead);//Exiting signal
	file.Close();
	}
    }
TTime CMyServer::GetLocaltime(TTime& aTime)
    {
    RTz TZoneServer;
    CTzConverter* converter;
    TZoneServer.Connect();
    converter = CTzConverter::NewL(TZoneServer);
    converter->ConvertToLocalTime(aTime);
    TZoneServer.Close();
    return aTime;
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
    #ifdef __DEBUG
    __LOGSTR("Draw image");
    #endif

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
    }

