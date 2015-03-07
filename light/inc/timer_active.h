#ifndef TIMER_ACTIVE_H
#define TIMER_ACTIVE_H

#include <e32base.h>
#include "logger1.h"


class MCTimerActiveCallBack
    {
public:
    virtual void TimerExpired() = 0;
    };

class CTimerActive : public CActive
    {
public:
    CTimerActive();
    ~CTimerActive();
    static CTimerActive* NewL();
    static CTimerActive* NewLC();
    void SetObserver(MCTimerActiveCallBack* aNewObserver);
    void At(const TTime& aTime);
    void Clear();
private:
    static TInt CallBack(TAny* aPtr);
    void TimerExpired();
    void ConstructL();
    void RunL();
    TInt RunError(TInt aError){__L1("CTimerActive::RunError: %d",aError);return KErrNone;}
    void DoCancel();
    MCTimerActiveCallBack* iObserver;
    CDeltaTimer* iDeltaTimer;
    TDeltaTimerEntry iEntry;
    TCallBack iCb;
    };

#endif // TIMER_ACTIVE_H
