/*
 * time_management.cpp
 *
 *  Created on: 27.03.2011
 *      Author: vl
 */

#include "time_management.h"

CTimeManagement::CTimeManagement(MTimeServerObserver* aObserver) : CActive(EPriorityNormal),iObserver(aObserver)
    {

    }
CTimeManagement::~CTimeManagement()
    {
    Cancel();
    }
CTimeManagement* CTimeManagement::NewL(MTimeServerObserver* aObserver)
    {
    CTimeManagement* self = new(ELeave) CTimeManagement(aObserver);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }
void CTimeManagement::ConstructL()
    {
    CActiveScheduler::Add(this);
    User::LeaveIfError(iFs.Connect());
    iTimer.CreateLocal();
    iTimeFrom.SetHour(0);
    iTimeFrom.SetMinute(0);
    iTimeDo.SetHour(23);
    iTimeDo.SetMinute(59);
    iInterval = 1;
    iSetNullTimes = EFalse;
    }
void CTimeManagement::SetNulltimes()
    {
    iCurrentTime.HomeTime();

    TDateTime testtime(iCurrentTime.DateTime());
    testtime.SetYear(0);
    testtime.SetMonth((TMonth)0);
    testtime.SetDay(0);
    testtime.SetSecond(0);
    iCurrentTime_ = testtime;

    iTimeFrom.SetYear(0);
    iTimeFrom.SetMonth((TMonth)0);
    iTimeFrom.SetDay(0);
    iTimeFrom.SetSecond(0);
    if((iTimeFrom.Hour() == 23) && (iTimeFrom.Minute() == 59))
	{
	iTimeFrom.SetHour(0);
	iTimeFrom.SetMinute(0);
	}
    iTimeFrom_ = iTimeFrom;

    iTimeDo.SetYear(0);
    iTimeDo.SetMonth((TMonth)0);
    iTimeDo.SetDay(0);
    iTimeDo.SetSecond(0);
    if((iTimeDo.Hour() == 0) && (iTimeDo.Minute() == 0))
	{
	iTimeDo.SetHour(23);
	iTimeDo.SetMinute(59);
	}
    iTimeDo_ = iTimeDo;
    iSetNullTimes = ETrue;
    #ifdef __DEBUG
	__LOGSTR2("iCurrentTime_ > iTimeFrom_:%d,iCurrentTime_ < iTimeDo_:%d",iCurrentTime_ > iTimeFrom_,iCurrentTime_ < iTimeDo_);
    #endif
    }
void CTimeManagement::Start()
    {
    if(iSetNullTimes == EFalse)
	SetNulltimes();
    #ifdef __DEBUG
    __LOGSTR("CTimeManagement::Start");
    #endif
    TInt err = iFile.Open(iFs,KFileNameTime,EFileRead|EFileShareAny);
    #ifdef __DEBUG
    __LOGSTR2("File %S open: %d",&KFileNameTime,err);
    #endif
    switch(err)
	{
    case KErrNone:

	iFile.Modified(iFileTime);
	iFile.Close();
	iFileTime = GetLocalTime(iFileTime);
	iCurrentTime.HomeTime();
	iCurrentTime.HoursFrom(iFileTime,iDifference);
	#ifdef __DEBUG
	__LOGSTR2("iDifference: %d, iInterval: %d",iDifference.Int(),iInterval.Int());
	#endif
	if((iDifference >= iInterval) &&
		(iCurrentTime_ > iTimeFrom_) &&
		(iCurrentTime_ < iTimeDo_))
	    {
	    #ifdef __DEBUG
	    __LOGSTR("iObserver->TimeEvent");
	    #endif
	    iObserver->TimeEvent(EEventTimeRefresh);
	    }else{
	    iTimer.After(iStatus,TTimeIntervalMicroSeconds32(60000000));
	    SetActive();
	    }
	break;
    case KErrNotFound:
	    iObserver->TimeEvent(EEventTimeRefresh);
	    break;
    default:
	User::Panic(_L("CTimeManagement::Start panic:"),err);
	break;
	}
    }
void CTimeManagement::RunL()
    {
    User::LeaveIfError(iStatus.Int());
    Start();
    }
TInt CTimeManagement::RunError(TInt aError)
    {
    return KErrNone;
    }
void CTimeManagement::DoCancel()
    {
    if(IsActive())
	{
	iTimer.Cancel();
	}
    }
TTime CTimeManagement::GetLocalTime(TTime& aTime)
    {
    RTz TZoneServer;
    CTzConverter* converter;
    TZoneServer.Connect();
    converter = CTzConverter::NewL(TZoneServer);
    converter->ConvertToLocalTime(aTime);
    TZoneServer.Close();
    return aTime;
    }
void CTimeManagement::SetTimeInterval(const TDateTime& aFrom,const TDateTime& aTo)
    {
    iTimeFrom = aFrom;
    iTimeDo = aTo;
    }
TInt CTimeManagement::SetTimeFrom(TInt& aHours,TInt& aMinutes)
    {
    TInt retHour = iTimeFrom.SetHour(aHours);
    TInt retMinutes = iTimeFrom.SetMinute(aMinutes);
    return (retHour + retMinutes);
    }
TInt CTimeManagement::SetTimeDo(TInt& aHours,TInt& aMinutes)
    {
    TInt retHour = iTimeDo.SetHour(aHours);
    TInt retMinutes = iTimeDo.SetMinute(aMinutes);
    return (retHour + retMinutes);
    }

void CTimeManagement::SetObserver(MTimeServerObserver* aObserver)
    {
    iObserver = aObserver;
    }
