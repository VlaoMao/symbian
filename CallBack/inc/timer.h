#ifndef TIMER_H
#define TIMER_H

#include <e32base.h>
#include "logger1.h"

class MTimerObserver
    {
public:
        virtual void TimerExpired() = 0;
    };

class CMyTimer : public CActive
    {
public:
    CMyTimer();
    ~CMyTimer();
    static CMyTimer* NewL();
    static CMyTimer* NewLC();
    void StartTimer();
    void StopTimer();
    void SetObserver(MTimerObserver* aNewObserver);
    void RunL();
    void DoCancel();
    TInt RunError(TInt aError);
private:
    void ConstructL();
    RTimer iTimer;
    MTimerObserver* iObserver;
    TInt iInterval;
    };

#endif // TIMER_H
