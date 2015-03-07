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

class CPhoneReceiver : public CActive
{
public:
	static CPhoneReceiver* NewL();
	static CPhoneReceiver* NewLC();
	// C++ constructor
	CPhoneReceiver();

	// Second-phase constructor
	void ConstructL();

	// Cancel and destroy
	~CPhoneReceiver();
	void SetObserver(MActiveCallListener* aObserver);

public:

	void StartL();

	//Open incoming call
	void OpenIncommingCall();
	TBool IsActiveCallPersist();
private: // From CActive
	// Handle completion
	void RunL();
	TInt RunError(TInt aError);
	// How to cancel me
	void DoCancel();

private:
	//Define object to CTelephone to manage calls
	CTelephony*				iTelephony;

	CTelephony::TCallInfoV1 		iCurrentCallInfo;
	CTelephony::TCallInfoV1Pckg		iCurrentStatusPckg;
	CTelephony::TCallStatus iCallStatus;

   //Define call ID to hold the ID of current call for further use (hangup, hold, resume)
	CTelephony::TCallId			iCallID;

protected:
	//TInt iNumms;	demo-version
	MActiveCallListener* iObserver;


};
