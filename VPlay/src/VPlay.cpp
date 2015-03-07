/*
 * VPlay.cpp
 *
 *  Created on: 08.06.2011
 *      Author: vl
 */

#include "VPlay.h"

void CVideoPlay::MvpuoOpenComplete(TInt aError)
	{
	__LOGSTR1("Open complete, err : %d",aError);
	iIsOpen = ETrue;
	iUtility->Prepare();
	}
void CVideoPlay::MvpuoPrepareComplete(TInt aError)
	{
	__LOGSTR1("Prepare complete, err: %d",aError);
	iUtility->SetVolumeL(iUtility->MaxVolume());
	iUtility->Play();
	}

void CVideoPlay::MvpuoPlayComplete(TInt aError)
	{
	__LOGSTR1("Play complete, err: %d", aError);
	//if(iIsOpen)
	if(aError == KErrNone)
		{
		__LOGSTR("Stopping scheduler");
		CActiveScheduler::Stop();
		}
	}
void CVideoPlay::MvpuoEvent(const TMMFEvent& aEvent)
	{
	__LOGSTR("MvpuoEvent");
	}
void CVideoPlay::MvpuoFrameReady(CFbsBitmap& aFrame,TInt aError)
	{
	__LOGSTR("Frame ready");
	iWindow.BeginRedraw(iRect);
	iGc->Activate(iWindow);
	iGc->Clear(iRect);
	iGc->Deactivate();
	iWindow.EndRedraw();
	}
CVideoPlay::CVideoPlay()
	{

	}
CVideoPlay::~CVideoPlay()
	{
	iGc->Activate(iWindow);
	iWindow.BeginRedraw();
	iWindow.Invalidate();
	iGc->Clear();
	iWindow.EndRedraw();
	iGc->Deactivate();
	iUtility->Close();
	iWs.Flush();
	iWs.Close();
	iFs.Close();
	if(iScreen)
		{
		delete iScreen;
		iScreen = NULL;
		}
	if(iUtility)
		{
		delete iUtility;
		iUtility = NULL;
		}
	}
void CVideoPlay::SendClose()
	{
	iUtility->Stop();
	CActiveScheduler::Stop();
	}
CVideoPlay* CVideoPlay::NewL()
	{
	CVideoPlay* self = new(ELeave) CVideoPlay;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}
void CVideoPlay::ConstructL()
	{
	iIsOpen = EFalse;
	User::LeaveIfError(iFs.Connect());
	iWs = RWsSession();
	User::LeaveIfError(iWs.Connect(iFs));
	iWg = RWindowGroup(iWs);
	iWg.Construct((TUint32)&iWg,EFalse);
	iWg.SetOrdinalPosition(0,ECoeWinPriorityAlwaysAtFront);
	iWg.EnableReceiptOfFocus(EFalse);

    iScreen = new(ELeave) CWsScreenDevice(iWs);
    CleanupStack::PushL(iScreen);
    iScreen->Construct();
    CleanupStack::Pop(iScreen);
    iScreen->CreateContext(iGc);

    iWindow = RWindow(iWs);
    iWindow.Construct(iWg,(TUint32)&iWg+1);
    iWindow.SetBackgroundColor(TRgb(KRgbWhite));
    iWindow.Activate();

    iWindow.SetNonFading(ETrue);
    /*HAL::Get(HALData::EDisplayXPixels,iScreenSize.iX);//Размер экрана
    HAL::Get(HALData::EDisplayYPixels,iScreenSize.iY);*/
    iScreenSize.iY = iScreen->GetCurrentScreenModeAttributes().iScreenSize.iHeight;
    iScreenSize.iX = iScreen->GetCurrentScreenModeAttributes().iScreenSize.iWidth;
    __LOGSTR2("iScreenSize.iX: %d,iScreenSize.iY: %d",iScreenSize.iX,iScreenSize.iY);
    /*TInt x,y;
    x = (iScreenSize.iX-200)/2;
    y = (iScreenSize.iY-200)/2;*/
    iWindow.SetPosition(TPoint(0,0));//20,60
    iWindow.SetExtent(TPoint(0,0),TSize(iScreenSize.iX,iScreenSize.iY-60));

    iRect = TRect(0,0,iScreenSize.iX,iScreenSize.iY-60);
    //iRectText = TRect(0,0,iScreenSize.iX,60);
   // iClipRect = TRect(0,60,iScreenSize.iX,iScreenSize.iY);
	iUtility = CVideoPlayerUtility::NewL(*this,EMdaPriorityNormal,EMdaPriorityPreferenceNone,iWs,*iScreen,iWindow,iRect,iRect);
	}
void CVideoPlay::OpenFileL(TDesC& aFileName)
	{
	__LOGSTR("OpenFileL");
	iUtility->OpenFileL(aFileName);
	//iUtility->GetFrameL(EColor16M);
	CActiveScheduler::Start();
	//iUtility->Prepare();
	__LOGSTR("i'm here");
	//iUtility->Play();
	}
