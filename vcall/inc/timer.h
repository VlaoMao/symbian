#ifndef TIMER_H
#define TIMER_H

#include <e32base.h>
#include <hwrmvibra.h>
#include "logger1.h"

struct VibraSettings
{
public:
    TInt iDelay;
    TInt iDuration;
    TInt iIntensity;
};

typedef RArray<VibraSettings> RVibraSettingsArray;

struct VibraOne
{
public:
    TInt iDelay;
    TInt iCount;
    RVibraSettingsArray iSettings;
};

class CVTimer : public CActive
{
public:
    static CVTimer* NewL();
    static CVTimer* NewLC();
    CVTimer();
    ~CVTimer();
    void setTimes(RArray<TInt>&);
    void startTimer(TInt aCount);
    void stopTimer();
private:
    void ConstructL();
    void RunL();
    TInt RunError(TInt);
    void DoCancel();
    RTimer iTimer;
    CHWRMVibra* iVibra;
    RArray<TInt> iTimes;
    TInt iCount;
    TTime iCallStartTime;
};

#endif // TIMER_H
