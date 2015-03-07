/*
 * GisWeather : server.cpp
 *
 *  Created on: 25.11.2010
 *  Author: vl
 */

#include "server.h"

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
    if(iChangeTrap)
    	{
    	iChangeTrap->StopMonitoring();
    	delete iChangeTrap;
    	}
    if(iTimer)
    	{
    	iTimer->Cancel();
    	delete iTimer;
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
    __LOGSTR("Construct");
    CActiveScheduler::Add(this);
    iWs = RWsSession();
    iFs.Connect();

    iTextPlain = CPlainText::NewL();

    ReadConf();
    __LOGSTR("ReadConfComplete");
	iOldName = _L("ClipboardChanged");

    iWs.Connect(iFs);
    iTaskList = new(ELeave) TApaTaskList(iWs);

    iScreen = new(ELeave) CWsScreenDevice(iWs);
    CleanupStack::PushL(iScreen);
    iScreen->Construct();
    CleanupStack::Pop(iScreen);

    iChangeTrap = CChangeTrap::NewL();
    iChangeTrap->SetObserver(this);
    iTimer = CPTimer::NewL();
    iTimer->SetObserver(this);
    iCaller = CCaller::NewL();

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
	iWindow.SetOrdinalPosition(5555,ECoeWinPriorityAlwaysAtFront);
    TRgb backgroundColour = KRgbBlack;
    //if(KErrNone == iWindow.SetTransparencyAlphaChannel())
   // 	{
    //	backgroundColour.SetAlpha(0);
    //	}
    iWindow.SetBackgroundColor(backgroundColour);


    GetFontSize();

    iWindow.SetSize(iSize);
    __LOGSTR2("iSize1: %d,iSize2: %d",iSize.iWidth,iSize.iHeight);
    iPos=TPoint(iConfig.iX,iConfig.iY);
	iWindow.SetVisible(EFalse);


    iWs.Flush();
    //Draw(iOldName);
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
	if(iTitle.Length() > iDrawTextOld.Length())
		{
		iSize=TSize(iFont->TextWidthInPixels(iTitle),iFont->HeightInPixels()*4);//XXX:две строки
		}else{
			iSize=TSize(iFont->TextWidthInPixels(iDrawTextOld),iFont->HeightInPixels()*4);//XXX:две строки
		}
	__LOGSTR2("iSize.width: %d, iSize.height: %d",iSize.iWidth,iSize.iHeight);
	}

void CMyServer::RunL()
    {
    __LOGSTR("RunL");
	GetWgEvent();
    }
TInt CMyServer::RunError(TInt aError)
    {
    __LOGSTR1("RunError: %d",aError);
    return KErrNone;
    }
void CMyServer::DoCancel()
    {
    iWs.EventReadyCancel();
    }

void CMyServer::ReadConf()
    {
    __LOGSTR("ReadConf");
    if(iFile.Open(iFs,KFileConfig,EFileRead) != KErrNone)
	{//file not exist
    __LOGSTR("File not exist");
	TInt err = iFs.MkDirAll(KFileConfigDir);
	__LOGSTR1("Mkdir: %d",err);
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
	__LOGSTR("File exist");
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
    __LOGSTR1("GetWgEvent,iStatus: %d",iStatus.Int());
   if(iStatus == KErrNone)
	{
    TWsEvent e;
    iWs.GetEvent(e);
    __LOGSTR1("event: %d",e.Type());
    switch(e.Type())
    	{
    	case EEventPointer:
    	case EEventPointerEnter:
    		//case EEventDragDrop:
    		{
    		__LOGSTR("EventPointer");
    		//обработчик клика
    		switch(iTypeEvent)
    			{
    			case ETypeCall:
    				{
    				if( e.Pointer()->iType == TPointerEvent::EButton1Down )
    					{
    					//iCaller->Cancel();
    					iCaller->Call(iDrawTextOld);
    					}
    				break;
    				}
    			case ETypeSearch:
    				if( e.Pointer()->iType == TPointerEvent::EButton1Down )
    					{
    					LaunchStandardBrowser();
    				break;
    					}
    			}
    		break;
    		}
    	}
	}
   /* TInt WgId = iWs.GetFocusWindowGroup();

    TUint handle = iWs.GetWindowGroupHandle(WgId);
    RWindowGroup wg_test = RWindowGroup(iWg);
    __LOGSTR2("handle: %d, constuct: %d",handle,wg_test.Construct(handle));

    CApaWindowGroupName* gn = CApaWindowGroupName::NewLC(iWs, WgId);
    __LOGSTR2("focused app with uid: 0x%x,config uid: 0x%x",gn->AppUid(),iConfig.iUid);
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
	__LOGSTR("UIDs ==");
	}else{
	iWindow.SetVisible(EFalse);
	iWs.Flush();
	__LOGSTR("UIDs !=");
	}*/
    WaitWgEvent();
    }
void CMyServer::WaitWgEvent()
    {
    iWg.EnableFocusChangeEvents();
    //iWg->EnableGroupChangeEvents();
    iWg.EnableGroupListChangeEvents();
    //iWg->EnableScreenChangeEvents();
    __LOGSTR("WaitWgEvent");
    iWs.EventReady(&iStatus);
    SetActive();
    }

void CMyServer::GetOrientation()
{
	iScreen->GetDefaultScreenSizeAndRotation(iPixels);
	iOrientation = iPixels.iRotation;
	__LOGSTR1("iOrientation: %d",iOrientation);
}
void CMyServer::Draw(const TDesC& aText)
    {
	__LOGSTR("CMyServer::Draw");
	__LOGSTR1("Draw text: %S",&aText);
	GetFontSize();
	iWindow.SetSize(iSize);
	iWindow.SetPosition(TPoint(0,0)/*iPos*/);
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
	iGc->DrawText(iTitle,TRect(0,0, iRect.Width(),iRect.Height()),iFont->FontMaxAscent(), CGraphicsContext::ELeft, 0);
	iGc->DrawText(aText,TRect(0,iSize.iHeight/2, iRect.Width(),iRect.Height()),iFont->FontMaxAscent(), CGraphicsContext::ECenter, 0);
    iWindow.EndRedraw();
    iGc->Deactivate();
    iWs.Flush();
    }

void CMyServer::ClipboardChanged()
	{
	__LOGSTR("CMyServer::ClipboardChanged");
	Cancel();
    iClipboard = CClipboard::NewForReadingL(iFs);
    _CPUSH(iClipboard);
    iClipboard->StreamDictionary().At(KClipboardUidTypePlainText);
    iTextPlain->DeleteL(0,iTextPlain->DocumentLength());
	iTextPlain->PasteFromStoreL(iClipboard->Store(),iClipboard->StreamDictionary(),0);
	//iDrawTextNew.Delete(0,iDrawTextNew.Length());
	iTextPlain->Extract(iDrawTextNew,0);
	_CPOPD(iClipboard);

	if( iDrawTextNew != iDrawTextOld)
		{
		__LOGSTR("Compare success");
		__LOGSTR2("BEFORE COPY:::::: iDrawTextNew: %S,iDrawTextOld: %S",&iDrawTextNew,&iDrawTextOld);
		iDrawTextOld = iDrawTextNew;
		if(iDrawTextOld.Left(2) == _L("+7") || iDrawTextOld.Left(1) == _L("8"))
		    {
			iTitle = _L("Вызвать");
			iTypeEvent = ETypeCall;
		    }else{
		    	iTitle = _L("Искать");
		    	iTypeEvent = ETypeSearch;
		    }
		__LOGSTR2("AFTER COPY:::::: iDrawTextNew: %S,iDrawTextOld: %S",&iDrawTextNew,&iDrawTextOld);
		Draw(iDrawTextOld);
		iTimer->StartTimer(5);
		WaitWgEvent();
		}
	}
void CMyServer::HideWindow()
	{
	__LOGSTR("CMyServer::HideWindow");
	Cancel();
	iTimer->StopTimer();
	iWindow.SetVisible(EFalse);
	iWs.Flush();
	}
void CMyServer::HideRequest()
	{
	__LOGSTR("CMyServer::HideRequest");
	HideWindow();
	}
void CMyServer::StartManagement()
	{
	__LOGSTR("CMyServer::StartManagement");
	iChangeTrap->StartMonitoring();
	}
void CMyServer::LaunchStandardBrowser()
	{
	__LOGSTR("CMyServer::LaunchBrowser");
	TBuf<512> url;
	url.Format(KUrlSearchStandard,&iDrawTextOld);
	TBuf8<512> url8;
	url8.Copy(url);
    TUid UID_Browser_91;
    UID_Browser_91.iUid = 0x1020724D;
    TUid UID_Browser_92;
    UID_Browser_92.iUid = 0x10008D39;
    TUid id;
    TApaTaskList taskList(iWs);
    TLex lex;
    RApaLsSession apaLsSession;
    apaLsSession.Connect();
    OsVersion ver;
    GetOsVersion(ver);
    __LOGSTR2("Major: %D, Minor: %D",ver.iMajor,ver.iMinor);
    if(ver.iMajor == 3 && ver.iMinor == 0)
	{
	//9.1
	__LOGSTR("9.1");
	id = UID_Browser_91;
	}else{
	//greather
	__LOGSTR("9.2 or high");
	id = UID_Browser_92;
	}
    TApaTask task = taskList.FindApp(id);

    if(task.Exists())
        {
        task.BringToForeground();
        task.SendMessage(TUid::Uid(0), url8); // UID not used
        }
    else
        {
        //if(!apaLsSession.Handle())
          //{
          //User::LeaveIfError(apaLsSession.Connect());
          //}
    	TApaAppInfo appInfo;
    	TInt retVal=apaLsSession.GetAppInfo(appInfo,id);
    	if(KErrNone == retVal)
    		{
    		CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
    		cmdLine->SetExecutableNameL(appInfo.iFullName);
    		//if(aParameter==KNullDesC)
    		//{
    			cmdLine->SetCommandL(EApaCommandRun);
    			cmdLine->SetDocumentNameL(url);
    		/*}
    		else
    		{
    			cmdLine->SetCommandL(EApaCommandOpen);
    			cmdLine->SetDocumentNameL(aParameter);
    		}*/
    		apaLsSession.StartApp(*cmdLine);

    		_CPOPD(cmdLine);
            task.BringToForeground();
            task.SendMessage(TUid::Uid(0), url8); // UID not used
    		}
        }
	}
void CMyServer::LaunchOtherBrowser(TDes& aText,TUid& aUidBrowser)
	{

	}
void CMyServer::GetOsVersion(OsVersion& aVersion)
    {
    TFindFile fileFinder = iFs;
    CDir* result;

    _LIT(KS60ProductIDFile, "Series60v*.sis");
    _LIT(KROMInstallDir, "z:\\system\\install\\");

    User::LeaveIfError(fileFinder.FindWildByDir(KS60ProductIDFile,
            KROMInstallDir, result));
    CleanupStack::PushL(result);

    // Sort the file names so that the newest platforms are first
    User::LeaveIfError(result->Sort(ESortByName | EDescending));

    // Parse the version numbers from the file name (e.g. Series60v3_1.sis)
    aVersion.iMajor = (*result)[0].iName[9] - '0';
    aVersion.iMinor = (*result)[0].iName[11] - '0';
    CleanupStack::PopAndDestroy(result);
    }
