/*
 * act.h
 *
 *  Created on: 30.04.2011
 *      Author: Vladislav
 */
#include <e32base.h>
#include <etel3rdparty.h>
#ifdef __DEBUG
#include "logger1.h"
#endif

class MPhoneReceiverObserver
{
public:
	virtual void CallRinging() = 0;
	virtual void CallAnswered()=0;
};


class CPhoneReceiver : public CActive
{
public:
	// C++ constructor
	CPhoneReceiver(MPhoneReceiverObserver& aPhoneReceiverObserver);

	// Second-phase constructor
	void ConstructL();

	// Cancel and destroy
	~CPhoneReceiver();

public:

	void StartL();

	//Open incoming call
	void OpenIncommingCall();

private: // From CActive
	// Handle completion
	void RunL();

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

	MPhoneReceiverObserver&			iPhoneReceiverObserver;
protected:
	//TInt iNumms;	demo-version


};
