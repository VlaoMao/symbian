/*
 * Window.h
 *
 *  Created on: 29.06.2011
 *      Author: vl
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <e32base.h>
#include <f32file.h>
#include <w32std.h>
#include <coedef.h>
#include <bautils.h>
#include <imageconversion.h>
#include "shared.h"
#include "logger1.h"
#include "CreateReadConf.h"
//#include "Caller.h"
#include <etel.h>
#include "ATSender.h"
#include "property.h"
#include "virtualobserver.h"
//
#include "timer.h"

_LIT(KFileImagePath,"C:\\System\\apps\\fastCallback\\callback.png");

struct ScreenPos
	{
public:
	TInt iX;
	TInt iY;
	TInt iWidth;
	TInt iHeight;
	};

class CWindow : public CActive, public MVirtualObserver, public MTimerObserver
    {
	friend class CSMSreceiver;
public:
	enum EWorkMode
		{
		EModeNormal,
		EModeSetpos
		};
    static CWindow* NewL();
    static CWindow* NewLC();
    CWindow();
    void Draw();
    void SetVisible(TBool aIsVisible);
    void SetReceiptOfFocus(TBool aIsReceiptOfFocus);
//    void RunCall();
    void HangUp();
    void HangUpEtel();
    void HangUpAT();
    void SetNeedToRecall(TBool aIsNeed);
    TBool GetNeedToRecall();
private:
    void ConstructL();
    virtual void RunL();
    virtual TInt RunError(TInt aError);
    virtual void DoCancel();
    void LoadImage();
    void SaveConfig();
public:
    void GetWgEvent();
    void WaitWgEvent();
    EWorkMode GetWorkMode();
    void GetFontSize(const TDesC& aText);
    TBool IsVisible() const;
   // void SetText(const TInt& aNumText);
    ScreenPos iPosition;
    TBuf<56> iText;
    ~CWindow();
    TRgb iBackgroundColor;
    TRgb iRectColor;
    //CCaller* iCaller;
    TInt iFontSize;
    TBool iIsNeedToReCall;
    CATSender* iSender;
    CATReader* iReader;
    CActiveSchedulerWait* iSchedulerWait;
    void NeedSetPos();
    void Draw_pos();
    void TimerExpired();
private:
    void ReadConf();
    TBool iIsFocus;
    TBool iIsVisible;
    RFs iFs;
    RFile iFile;
    RWsSession iWs;
    RWindowGroup iWg;
    RWindow iWindow;
    CWindowGc* iGc;
    CWsScreenDevice* iScreen;
   	TBuf<KMaxTypefaceNameLength> iFontName;
    TTypefaceSupport iTypefaceSupport;
   	TFontSpec iFontSpec;
    CFont* iFont;
    TSize iSize;
    TRect iRect;
    TRect iImageRect;
    TRgb iTextColor;
    CFbsBitmap* iBitmap;
    //CFbsBitmap* iBitmapMask;
    TBool iImageIsLoaded;
    EWorkMode iWorkMode;
    TPoint iOldpos;
    TPoint iCurrentPos;
    CPropImpl* iPropImpl;
    CMyTimer* iTimer;
    };

#endif /* WINDOW_H_ */
