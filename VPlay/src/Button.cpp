/*
 * Button.cpp
 *
 *  Created on: 08.06.2011
 *      Author: vl
 */
#include "Button.h"

CButton::CButton(MConnect* aConnect) : CActive(EPriorityHigh),iMconnect(aConnect)
    {

    }
CButton::~CButton()
    {
	iGc->Activate(iWindow);
	iWindow.BeginRedraw();
	iWindow.Invalidate();
	iGc->Clear();
	iWindow.EndRedraw();
	iGc->Deactivate();
	iWs.Close();
    iFs.Close();
    }
CButton* CButton::NewL(MConnect* aConnect)
    {
    CButton* self = new(ELeave) CButton(aConnect);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

void CButton::ConstructL()
    {
    #ifdef __DEBUG
    __LOGSTR("Construct");
    #endif
    CActiveScheduler::Add(this);
    iColor = KRgbRed;
    iWs = RWsSession();
    iFs.Connect();
    iWs.Connect(iFs);
    iWg = RWindowGroup(iWs);
    iWg.Construct((TUint32)&iWg,EFalse);
    iWg.SetOrdinalPosition(0,ECoeWinPriorityAlwaysAtFront);
    iWg.EnableReceiptOfFocus(ETrue);

    iWindow = RWindow(iWs);
    iWindow.Construct(iWg,(TUint32)&iWg+1);
    iWindow.Activate();
    iWindow.SetNonFading(ETrue);
    //
    iWindow.SetBackgroundColor(KRgbBlack);

    iScreen=new (ELeave) CWsScreenDevice(iWs);
    User::LeaveIfError(iScreen->Construct());
    User::LeaveIfError(iScreen->CreateContext(iGc));
    GetFontSize();
    iScreenSize.iY = iScreen->GetCurrentScreenModeAttributes().iScreenSize.iHeight;
    iScreenSize.iX = iScreen->GetCurrentScreenModeAttributes().iScreenSize.iWidth;
    iWindow.SetExtent(TPoint(0,iScreenSize.iY-60),TSize(iScreenSize.iX,60));
    iWs.Flush();
    Draw();
    iWs.Flush();
    }
void CButton::GetFontSize()
	{
	iFontName.FillZ(KMaxTypefaceNameLength);
	iScreen->TypefaceSupport(iTypefaceSupport, 0);
	iFontName = iTypefaceSupport.iTypeface.iName;
	// get font
	iFontSpec = TFontSpec(iFontName, 10*12);
	iFontSpec.iTypeface.SetIsProportional(ETrue);
	iScreen->GetNearestFontInTwips(iFont,iFontSpec);

	iSize=TSize(iFont->TextWidthInPixels(_L("Пропустить")),iFont->HeightInPixels()*2);
	__LOGSTR2("iSize.width: %d, iSize.height: %d",iSize.iWidth,iSize.iHeight);
	}
void CButton::RunL()
    {
    #ifdef __DEBUG
    __LOGSTR("RunL");
    #endif
	GetWgEvent();
    }
TInt CButton::RunError(TInt aError)
    {
	#ifdef __DEBUG
    __LOGSTR1("RunError: %d",aError);
	#endif
    return KErrNone;
    }
void CButton::DoCancel()
    {
    iWs.EventReadyCancel();
    }

void CButton::GetWgEvent()
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
    switch(e.Type())
    	{
    	case EEventPointer:
    	case EEventPointerEnter:
    	case EEventDragDrop:
    	{
    	__LOGSTR("SendClose");
    	iMconnect->SendClose();
    	break;
    	}
    	case EEventFocusGained:
    		__LOGSTR("Focus gained");
    		iIsFocus = ETrue;
    		//iColor = KRgbGreen;
    		break;
    	case EEventFocusLost:
    		__LOGSTR("Focus lost");
    		iIsFocus = EFalse;
    		//iColor = KRgbRed;
    		break;
    	case EEventKeyDown:
    		__LOGSTR2("EEventKeyDown,iIsFocus: %d,iScanCode: %d",iIsFocus,e.Key()->iScanCode);
    		if(iIsFocus && e.Key()->iScanCode == 167)
    			{
    			iMconnect->SendClose();
    			}
    		break;
    	}
	}
	Draw();
	iWs.Flush();
    WaitWgEvent();
    }
void CButton::WaitWgEvent()
    {
    iWg.EnableFocusChangeEvents();
    iWg.EnableGroupListChangeEvents();
    #ifdef __DEBUG
    __LOGSTR("WaitWgEvent");
    #endif
    iWs.EventReady(&iStatus);
    SetActive();
    }
void CButton::Draw()
	{
	iWindow.SetPosition(TPoint(0,iScreenSize.iY-60));
	iWindow.SetSize(TSize(iScreenSize.iX,60));
	iWindow.SetVisible(ETrue);
	TInt i = iScreenSize.iY-60;
	__LOGSTR1("i: %d",i);
	iGc->Activate(iWindow);
	iRectButton = TRect(TPoint(0,0),TSize(iScreenSize.iX,60));
	iWindow.Invalidate();
	iWindow.BeginRedraw();
	iGc->Clear();
	iGc->SetPenColor(iColor);
	iGc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	iGc->UseFont(iFont);
	iGc->SetPenColor(KRgbBlue);
	iGc->SetBrushColor(KRgbGray);
	iGc->Clear(iRectButton);
	iGc->DrawText(_L("Демо(Пропустить)"),iRectButton/*TRect(0,0, iRectButton.Width(),iRectButton.Height())*/,60-iFont->FontMaxAscent(), CGraphicsContext::ECenter, 0);
	/*iGc->SetPenColor(KRgbSilver);
	iGc->DrawLine(TPoint(iScreenSize.iX/2,0),TPoint(iScreenSize.iX-1,0));//горизонтальная сверху
	iGc->DrawLine(TPoint(iScreenSize.iX-1,0),TPoint(iScreenSize.iX-1,60));//Вертикальная справа
	iGc->DrawLine(TPoint(iScreenSize.iX/2,59),TPoint(iScreenSize.iX,59));//Горизонтальная снизу
	iGc->DrawLine(TPoint(iScreenSize.iX/2,0),TPoint(iScreenSize.iX/2,60));//Вертикальная справа
*/
	iWindow.EndRedraw();
	iGc->Deactivate();
	iWs.Flush();
	}
