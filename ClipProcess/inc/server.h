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
#include <hal.h>
#include <hal_data.h>
#include <gdi.h>
#include <eikenv.h>
#include <baclipb.h>
//#include <browserlauncher.h>
#include "logger1.h"
#include "constants.h"
#include "change_trap.h"
#include "timer.h"
#include "caller.h"




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
    TInt iClipboardDrive;
    };
class CMyServer : public CActive, public MNotifyChangeServer
    {
public:
	enum ETypeEvent
		{
		ETypeSearch,
		ETypeCall
		};
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
    void HideWindow();
    void HideRequest();
    void StartManagement();
    void GetFontSize();
    void ClipboardChanged();
    void LaunchStandardBrowser();
    void LaunchOtherBrowser(TDes& aText,TUid& aUidBrowser);
    void GetOsVersion(OsVersion& aVersion);
private:
    TInt iOrientation;
    TFrameInfo iFrameInfo;
    TRect iRect;
    //CFbsBitmap* iBitmap;
    RFs iFs;
    RFile iFile;
    RWsSession iWs;
    CWsScreenDevice* iScreen;
    TPixelsAndRotation iPixels;
    RWindowGroup iWg;
    CWindowGc* iGc;
    RWindow iWindow;
    TApaTaskList* iTaskList;
    TTypefaceSupport iTypefaceSupport;
   	TBuf<KMaxTypefaceNameLength> iFontName;
   	TFontSpec iFontSpec;
    CFont* iFont;
    TSize iSize;
    TPoint iPos;
    ETypeEvent iTypeEvent;
    CPlainText* iTextPlain;
    TBuf<512> iDrawTextNew;
    TBuf<512> iDrawTextOld;
    TBuf<64> iTitle;
    CClipboard* iClipboard;
    CChangeTrap* iChangeTrap;
    TBuf<256> iOldName;
    TBuf<256> iNewName;
    CPTimer* iTimer;
    CCaller* iCaller;
    };
#endif /* SERVER_H_ */
