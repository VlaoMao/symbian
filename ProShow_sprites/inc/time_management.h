/*
 * time_management.h
 *
 *  Created on: 27.03.2011
 *      Author: vl
 */

#ifndef TIME_MANAGEMENT_H_
#define TIME_MANAGEMENT_H_

#include <f32file.h>
#include <tz.h>
#include <tzconverter.h>
#include "Constants.h"
#include "logger1.h"

#ifndef __DEBUG
#define __DEBUG 1
#endif

enum TEventTime{
	    EEventTimeRefresh=1,
	    EEventTime
};
class MTimeServerObserver
    {
public:
    virtual void TimeEvent(const TEventTime aEvent)=0;
    };
class CTimeManagement : public CActive
    {
public:
    CTimeManagement(MTimeServerObserver* aObserver);
    ~CTimeManagement();
    static CTimeManagement* NewL(MTimeServerObserver* aObserver);
    void Start();
    void SetTimeInterval(const TDateTime& aFrom,const TDateTime& aTo);
    TInt SetTimeFrom(TInt& aHours,TInt& aMinutes);
    TInt SetTimeDo(TInt& aHours,TInt& aMinutes);
    void SetObserver(MTimeServerObserver* aObserver);
    void SetNulltimes();
    TTime GetLocalTime(TTime& aTime);
    TTimeIntervalHours iInterval;
protected:
    TBool iSetNullTimes;
    void ConstructL();
    virtual void RunL();
    virtual TInt RunError(TInt aError);
    virtual void DoCancel();
    RTimer iTimer;
    TDateTime iTimeFrom;
    TTime iTimeFrom_;
    TDateTime iTimeDo;
    TTime iTimeDo_;
    TTime iFileTime;
    TTime iCurrentTime;
    TTime iCurrentTime_;
    TTimeIntervalHours iDifference;
    RFile iFile;
    RFs iFs;
    MTimeServerObserver* iObserver;
    };
#endif /* TIME_MANAGEMENT_H_ */
