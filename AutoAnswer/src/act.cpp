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

	delete iTelephony;
}

void CPhoneReceiver::DoCancel()
{
	iTelephony->CancelAsync( CTelephony::EVoiceLineStatusChangeCancel );
}

void CPhoneReceiver::StartL()
{
#ifdef __DEBUG
	__LOGSTR("CPhoneReceiver::StartL()");
#endif
	Cancel();	// Cancel any request, just to be sure

	//Notify of change in telephone line
	iTelephony->NotifyChange( iStatus, CTelephony::EVoiceLineStatusChange,
								iCurrentStatusPckg );

	SetActive();	// Tell scheduler a request is active
}

void CPhoneReceiver::RunL()
{
#ifdef __DEBUG
	__LOGSTR1("CPhoneReceiver::RunL(),iCurrentStatusPckg: %d",iCurrentStatusPckg().iStatus);
#endif
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
			iPhoneReceiverObserver.CallRinging();
			break;

		case CTelephony::EStatusAnswering:
			iPhoneReceiverObserver.CallAnswered();
			break;
		default:
#ifdef __DEBUG
			__LOGSTR("default");
#endif
			break;
		}
#ifdef __DEBUG
		__LOGSTR("Run startL");
#endif
	//StartL();
	}
	else
	{
#ifdef __DEBUG
		__LOGSTR1("Error In status,iStatus: %d",iStatus.Int());
#endif
	}
	StartL();
}


/************************************************************************/
/* Define function to open incoming call                                */
/************************************************************************/
void CPhoneReceiver::OpenIncommingCall()
{
#ifdef __DEBUG
	__LOGSTR("OpenIncommingCall");
#endif

	//Answer incoming call (Required Network services capability)
	iTelephony->AnswerIncomingCall(iStatus, iCallID);
	SetActive();
}
