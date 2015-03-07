/*
 * GisWeather : server.h
 *
 *  Created on: 25.11.2010
 *  Author: vl
 */

#ifndef SERVER_H_
#define SERVER_H_
#include <avkon.rsg>
#include <aknquerydialog.h>
#include <imageconversion.h>
#include <apgwgnam.h>
#include <apgtask.h>
#include <apgcli.h>
#include <apacmdln.h>
#include <w32std.h>
#include <fbs.h>
#include <bautils.h>
#include <coecntrl.h>
#include <tzconverter.h> //TZ converter
#include <tz.h> //RTz
#include <hal.h>
#include <hal_data.h>
#include <gdi.h>
#include <badesca.h>
#include <coefont.h>
#include <mprofileengine.h>
#include <mprofile.h>
#include <mprofilename.h>

#ifdef __DEBUG
#include "logger1.h"
#endif

#include "Constants.h"



struct Config
    {
public:
    TInt iX;
    TInt iY;
    TInt iLandY;
    TInt iLandX;
    TRgb iColor;
    TInt iHeight;
    TUid iUid;
    };
class CMyServer : public CActive
    {
public:
    static CMyServer* NewL();
    CMyServer();
private:
    void ConstructL();
    virtual void RunL();
    virtual TInt RunError(TInt aError);
    virtual void DoCancel();
    void ReadConf();
    ~CMyServer();
public:
    void Draw(const TDesC& aText);
    void WaitWgEvent();
    void GetWgEvent();
    void GetOrientation();
    Config iConfig;
    void Hide();
    void Show();
private:
    TInt iOrientation;
    TFrameInfo iFrameInfo;
    TRect iRect;
    CFbsBitmap* iBitmap;
    RFs iFs;
    RFile iFile;
    RWsSession iWs;
    CWsScreenDevice* iScreen;
    TPixelsAndRotation iPixels;
    RWindowGroup* iWg;
    CWindowGc* iGc;
    RWindow iWindow;
    TApaTaskList* iTaskList;
    RWsSprite* iSprite;
    TSpriteMember iMember;
    CFbsBitmap* iMask;
    CFbsBitGc* iBitGc;
    CFbsBitmapDevice* iBitDevice;
    CFbsBitmapDevice* iMaskDevice;
    CFbsBitGc* iMaskGc;
    CFont* iFont;
    TBool iIsVisible;
    TSize iSize;
    TPoint iPos;
    //HBufC* iText;
    MProfileEngine* iEngine;
    TBuf<256> iOldName;
    TBuf<256> iNewName;
    };
#endif /* SERVER_H_ */
