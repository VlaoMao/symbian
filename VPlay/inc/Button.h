/*
 * Button.h
 *
 *  Created on: 08.06.2011
 *      Author: vl
 */

#ifndef BUTTON_H_
#define BUTTON_H_
#include <e32base.h>
#include <f32file.h>
#include <w32std.h>
#include <videoplayer.h>
#include <coedef.h>
#include <hal.h>
#include <hal_data.h>
#include "logger1.h"
#include "connect.h"

#define KRgbSilver TRgb(0xc0c0c0)

_LIT(KFileConfig,"C:\\System\\Apps\\VPlay\\video.mp4");

class CButton : public CActive
    {
public:
    static CButton* NewL(MConnect* aConnect);
    CButton(MConnect* aConnect);
    void Draw();
private:
    void ConstructL();
    virtual void RunL();
    virtual TInt RunError(TInt aError);
    virtual void DoCancel();
public:
    void GetWgEvent();
    void WaitWgEvent();
    void GetFontSize();
private:
    ~CButton();
    RFs iFs;
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
    TRect iRectButton;
    MConnect* iMconnect;
    ScreenSize iScreenSize;
    TBool iIsFocus;
    TRgb iColor;
    };

#endif /* BUTTON_H_ */
