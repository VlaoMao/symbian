/*
 * caller.cpp
 *
 *  Created on: 21.11.2011
 *      Author: vl
 */

#include "caller.h"

CCaller::CCaller() : CActive(EPriorityNormal)
	{

	}
CCaller::~CCaller()
	{
	if(iTelephony)
		{
		Cancel();
		_CPOPD(iTelephony);
		}

	}
CCaller* CCaller::NewL()
	{
	CCaller* self = CCaller::NewLC();
	_CPOP(self);
	return self;
	}
CCaller* CCaller::NewLC()
	{
	CCaller* self = new (ELeave) CCaller();
	_CPUSH(self);
	self->ConstructL();
	return self;
	}
void CCaller::ConstructL()
	{
	CActiveScheduler::Add(this);
	iTelephony = CTelephony::NewLC();
	}
void CCaller::RunL()
	{

	}
TInt CCaller::RunError(TInt aError)
	{
	return KErrNone;
	}
void CCaller::DoCancel()
	{
	iTelephony->CancelAsync(CTelephony::EDialNewCallCancel);
	}
void CCaller::Call(const TDesC& aNumber)
	{
    CTelephony::TTelNumber number(aNumber);
    CTelephony::TCallId callid;
    CTelephony::TCallParamsV1 callparams;
    CTelephony::TCallParamsV1Pckg callparamspckg(callparams);
    callparams.iIdRestrict = CTelephony::ESendMyId;

    iTelephony->DialNewCall(iStatus,callparamspckg,number,callid);
    SetActive();
	}
