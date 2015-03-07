#include "timer.h"

CVTimer::CVTimer() : CActive(EPriorityNormal)
{

}
CVTimer::~CVTimer()
{
    Cancel();
    if(iVibra)
    {
        if(iVibra->VibraStatus() == CHWRMVibra::EVibraStatusOn)
            iVibra->StopVibraL();
        delete iVibra;
    }
}
void CVTimer::ConstructL()
{
    CActiveScheduler::Add(this);
    iTimer.CreateLocal();
    iVibra = CHWRMVibra::NewL();
    iCount = 0;
}

void CVTimer::startTimer(TInt aCount)
{
    __LOGSTR("CVtimer::startTimer");
    if(iTimes.Count() == 0)
    {
        User::Panic(_L("Count times is 0"),KErrAbort);
    }
    iCount = aCount;
    if(iCount >= iTimes.Count())
    {
        return;
    }
    TInt firstTime = iTimes[iCount];
    if(firstTime <= 0)
        return;
    TTimeIntervalSeconds secs = TTimeIntervalSeconds(firstTime);
    TTime homeTime;
    TTime workTime;
    homeTime.HomeTime();
    if(aCount == 0)
        iCallStartTime = homeTime;
    workTime = iCallStartTime + secs;
    iTimer.At(iStatus,workTime);
    __LOGSTR3("timer: %d:%d:%d",workTime.DateTime().Hour(),workTime.DateTime().Minute(),workTime.DateTime().Second());
    SetActive();
}
void CVTimer::stopTimer()
{
    __LOGSTR("CVtimer::stopTimer");
    Cancel();
}

void CVTimer::RunL()
{
    __LOGSTR("CVtimer::RunL");
    if(iStatus.Int() == KErrNone)
    {
        CHWRMVibra::TVibraStatus statusVibra = iVibra->VibraStatus();
        if((statusVibra != CHWRMVibra::EVibraStatusNotAllowed) && (statusVibra != CHWRMVibra::EVibraStatusUnknown))
        {
            TRAPD(err,iVibra->StartVibraL(200,50));
            if(err != KErrNone)
            {
                __LOGSTR1("Vibration error: %d",err);
                User::Leave(err);
            }
            ++iCount;
            startTimer(iCount);
        }else{
            __LOGSTR("Vibra not allowed or status unknown");
        }
    }else{
        //TODO: error
        __LOGSTR1("CVtimer::RunL error: %d",iStatus.Int());
    }
}

void CVTimer::DoCancel()
{
    iTimer.Cancel();
    if(iVibra->VibraStatus() == CHWRMVibra::EVibraStatusOn)
        iVibra->StopVibraL();
}

void CVTimer::setTimes(RArray<TInt> & aTimes)
{
    if(aTimes.Count() == 0)
    {
        User::Panic(_L("Count times array is 0"),KErrGeneral);
    }
    iTimes = aTimes;
}

TInt CVTimer::RunError(TInt aError)
{
    __LOGSTR1("CVtimer::RunError: %d",aError);
    return KErrNone;
}

CVTimer* CVTimer::NewL()
{
    CVTimer* self = CVTimer::NewLC();
    _CPOP(self);
    return self;
}

CVTimer* CVTimer::NewLC()
{
    CVTimer* self = new (ELeave) CVTimer();
    _CPUSH(self);
    self->ConstructL();
    return self;
}
