/*
 * act.cpp
 *
 *  Created on: 30.04.2011
 *      Author: Vladislav
 */
#include <e32base.h>
#include "act.h"

CPhoneReceiver::CPhoneReceiver(MPhoneReceiverObserver& aPhoneReceiverObserver)
	:	CActive(EPriorityHigh),
		iCurrentStatusPckg(iCurrentCallInfo),
		iPhoneReceiverObserver(aPhoneReceiverObserver)
{
}
CPhoneReceiver* CPhoneReceiver::NewLC(MPhoneReceiverObserver& aPhoneReceiverObserver)
	{
	CPhoneReceiver* self = new(ELeave) CPhoneReceiver(aPhoneReceiverObserver);
	_CPUSH(self);
	self->ConstructL();
	return self;
	}
CPhoneReceiver* CPhoneReceiver::NewL(MPhoneReceiverObserver& aPhoneReceiverObserver)
	{
	CPhoneReceiver* self = CPhoneReceiver::NewLC(aPhoneReceiverObserver);
	_CPOP(self);
	return self;
	}
void CPhoneReceiver::ConstructL()
{
	//Create new object to telephony
	iTelephony = CTelephony::NewL();
	//iNumms = 0;
	CActiveScheduler::Add(this);	// Add to scheduler
}

CPhoneReceiver::~CPhoneReceiver()
{
	Cancel(); // Cancel any request, if outstanding
	if(iTelephony)
		{
		delete iTelephony;
		iTelephony = NULL;
		}
}

void CPhoneReceiver::DoCancel()
{
	iTelephony->CancelAsync( CTelephony::EVoiceLineStatusChangeCancel );
}
TInt CPhoneReceiver::RunError(TInt aError)
	{

	__LOGSTR1("CPhoneReceiver, error: %d",aError);

	return KErrNone;
	}
void CPhoneReceiver::StartL()
{
	__LOGSTR("CPhoneReceiver::StartL()");
	Cancel();	// Cancel any request, just to be sure

	//Notify of change in telephone line
	iTelephony->NotifyChange( iStatus, CTelephony::EVoiceLineStatusChange,
								iCurrentStatusPckg );

	SetActive();	// Tell scheduler a request is active
}

void CPhoneReceiver::RunL()
{
	__LOGSTR("CPhoneReceiver::RunL()");
	/*if(iNumms > 2)
		return ;*/
	if(iStatus.Int() == KErrNone)
	{
		//Get call status
		iCallStatus = iCurrentStatusPckg().iStatus;
		switch(iCallStatus)
		{
		case CTelephony::EStatusRinging:
			//++iNumms;
			iPhoneReceiverObserver.iCallStatus = CTelephony::EStatusRinging;
			iPhoneReceiverObserver.CallRinging();
			break;

		case CTelephony::EStatusAnswering:
			//iPhoneReceiverObserver.iCallStatus = CTelephony::EStatusAnswering;
			iPhoneReceiverObserver.CallAnswered();
			break;
		case CTelephony::EStatusConnected:
			iPhoneReceiverObserver.iCallStatus = CTelephony::EStatusConnected;
			iPhoneReceiverObserver.CallConnected();
			break;
		case CTelephony::EStatusDisconnecting:
			iPhoneReceiverObserver.iCallStatus = CTelephony::EStatusDisconnecting;
			iPhoneReceiverObserver.CallDisconnecting();
			break;
		case CTelephony::EStatusDialling:
			iPhoneReceiverObserver.iCallStatus = CTelephony::EStatusDialling;
			iPhoneReceiverObserver.CallDialling();
			break;
		case CTelephony::EStatusIdle:
			iPhoneReceiverObserver.iCallStatus = CTelephony::EStatusIdle;
			iPhoneReceiverObserver.Idle();
			break;
		default:
			__LOGSTR1("default call status: %d",iCallStatus);
			break;
		}
		__LOGSTR("Run startL");
	//StartL();
	}
	else
	{
		__LOGSTR1("Error In status,iStatus: %d",iStatus.Int());
	}
	StartL();
}


/************************************************************************/
/* Define function to open incoming call                                */
/************************************************************************/
void CPhoneReceiver::OpenIncommingCall()
{
	__LOGSTR("OpenIncommingCall");

	//Answer incoming call (Required Network services capability)
	//iTelephony->AnswerIncomingCall(iStatus, iCallID);
	//SetActive();
}
