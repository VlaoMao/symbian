/*
 * act.h
 *
 *  Created on: 30.04.2011
 *      Author: Vladislav
 */
#include <e32base.h>
#include <etel3rdparty.h>

#include "logger1.h"
#include "callchange.h"
#include "settings.h"

class CPhoneReceiver : public CActive
{
public:
	static CPhoneReceiver* NewL();
	static CPhoneReceiver* NewLC();
	CPhoneReceiver();
	void ConstructL();
	~CPhoneReceiver();
	void SetObserver(MActiveCallListener* aObserver);

public:

	void StartL();
	TBool IsActiveCallPersist();
private:
	void RunL();
	TInt RunError(TInt aError);
	void DoCancel();

private:
    CTelephony*                     iTelephony;
	CTelephony::TCallInfoV1 		iCurrentCallInfo;
	CTelephony::TCallInfoV1Pckg		iCurrentStatusPckg;
    CTelephony::TCallStatus         iCallStatus;

   //Define call ID to hold the ID of current call for further use (hangup, hold, resume)
	CTelephony::TCallId			iCallID;

protected:
	MActiveCallListener* iObserver;
    CSettings* iSettings;
    TBool iIn;
};
