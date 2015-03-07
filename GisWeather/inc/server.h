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

#ifdef __DEBUG
#include "logger1.h"
#endif

#include "Constants.h"
//#include "Decoder.h"
#include "time_management.h"


struct Config
    {
public:
    TInt iX;
    TInt iY;
    TInt iLandY;
    TInt iLandX;
    TInt iPeriod;
    TUid iUid;
    TInt iFromHour;
    TInt iFromMinute;
    TInt iDoHour;
    TInt iDoMinute;
    TBool iAutostartEnabled;
    };
class CMyServer : public CActive,public MTimeServerObserver
    {
public:
    static CMyServer* NewL(TBool aAutostart);
    CMyServer(TBool aAutostart);
private:
    void ConstructL();
    virtual void RunL();
    virtual TInt RunError(TInt aError);
    virtual void DoCancel();
    void ReadConf();
    ~CMyServer();
public:
    void Draw();
    void LoadImage();
    void WaitWgEvent();
    void GetWgEvent();
    void Refresh();
    void GetOrientation();
    virtual void TimeEvent(const TEventTime aEvent);
    TTime GetLocaltime(TTime& aTime);
    Config iConfig;
    CTimeManagement* iTimeMan;
private:
    TBool iIsImageLoaded;
    TTime iModified;
    TTime iModifiedLocal;
    TTime iTime;
    TInt iOrientation;
    TTimeIntervalHours iDifference;
    CImageDecoder* iDecoder;
    //CDecoder* iDecoder;
    TFrameInfo iFrameInfo;
    TRect iRect;
    CFbsBitmap* iBitmap;
    TBuf8<256> iUrl;
    TBool iFileExists;
    TBool iAutostart;
    CActiveSchedulerWait* iSchedulerWait;
    RFs iFs;
    RFile iFile;
    RFile iFileTime;
    RWsSession iWs;
    CWsScreenDevice* iScreen;
    TPixelsAndRotation iPixels;
    RWindowGroup iWg;
    CWindowGc* iGc;
    RWindow iWindow;
    TApaTaskList* iTaskList;
    TWsEvent iEventType;
    TPoint iOldPoint;
    TPoint iNewPoint;
    };
#endif /* SERVER_H_ */
