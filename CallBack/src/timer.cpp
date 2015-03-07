#include "timer.h"

CMyTimer::CMyTimer() : CActive(EPriorityNormal),iInterval(3000000)
    {

    }
CMyTimer::~CMyTimer()
    {
        Cancel();
        iTimer.Close();
    }

CMyTimer* CMyTimer::NewL()
    {
        CMyTimer* self = CMyTimer::NewLC();
        _CPOP(self);
        return self;
    }

CMyTimer* CMyTimer::NewLC()
    {
        CMyTimer* self = new (ELeave) CMyTimer();
        _CPUSH(self);
        self->ConstructL();
        return self;
    }

void CMyTimer::ConstructL()
    {
        CActiveScheduler::Add(this);
        iTimer.CreateLocal();
    }
void CMyTimer::StartTimer()
    {
        iTimer.After(iStatus,iInterval);
        SetActive();
    }
void CMyTimer::StopTimer()
    {
        Cancel();
    }

void CMyTimer::RunL()
    {
        iObserver->TimerExpired();
    }
void CMyTimer::DoCancel()
    {
        iTimer.Cancel();
    }
TInt CMyTimer::RunError(TInt aError)
    {
        return KErrNone;
    }
void CMyTimer::SetObserver(MTimerObserver *aNewObserver)
    {
        iObserver = aNewObserver;
    }
