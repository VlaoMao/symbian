#include "timer_active.h"

CTimerActive::CTimerActive() : CActive(EPriorityNormal)
    {

    }
CTimerActive::~CTimerActive()
    {
        Cancel();
        if(iDeltaTimer)
            {
                iDeltaTimer->Cancel();
                iDeltaTimer->Deque();
                delete iDeltaTimer;
            }
    }
CTimerActive* CTimerActive::NewL()
    {
        CTimerActive* self = CTimerActive::NewLC();
        _CPOP(self);
        return self;
    }
CTimerActive* CTimerActive::NewLC()
    {
        CTimerActive* self = new (ELeave) CTimerActive();
        _CPUSH(self);
        self->ConstructL();
        return self;
    }
void CTimerActive::RunL()
    {
        if(iStatus.Int() == KErrNone)
            {
                iObserver->TimerExpired();
            }
    }
void CTimerActive::DoCancel()
    {
    }
void CTimerActive::ConstructL()
    {
        CActiveScheduler::Add(this);
        iDeltaTimer = CDeltaTimer::NewL(EPriorityNormal);
    }
void CTimerActive::SetObserver(MCTimerActiveCallBack *aNewObserver)
    {
        if(aNewObserver != NULL)
            iObserver = aNewObserver;
    }
void CTimerActive::At(const TTime &aTime)
    {
        __L("CTimerActive::At");
        TTime localTime;
        localTime.HomeTime();
        TTimeIntervalMicroSeconds msecs = aTime.MicroSecondsFrom(localTime);
        if(msecs > 0)
            {
                __L("msecs > 0");
                iCb = TCallBack(CallBack,this);
                iEntry.Set(iCb);
                __L("adding to queue delta timer");
                TInt err = iDeltaTimer->QueueLong(msecs,iEntry);
                __L1("adding to queue state: %d",err);
                __L1("CDeltaTimer is added to CActiveScheduler: %d",iDeltaTimer->IsAdded());
            }else{
                __L("msecs < 0!!!");
            }
    }
void CTimerActive::Clear()
    {
        if(iDeltaTimer != NULL)
            {
            iDeltaTimer->Cancel();
            iDeltaTimer->Deque();
            delete iDeltaTimer;
            }
        iDeltaTimer = CDeltaTimer::NewL(EPriorityNormal);
    }

TInt CTimerActive::CallBack(TAny *aPtr)
    {
        __L("CTimerActive::CallBack");
        ((CTimerActive*)aPtr)->TimerExpired();
        return 1;
    }
void CTimerActive::TimerExpired()
    {
        iObserver->TimerExpired();
    }
