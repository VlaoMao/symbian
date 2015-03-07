/*
 * act.cpp
 *
 *  Created on: 30.04.2011
 *      Author: Vladislav
 */
#include <e32base.h>
#include "act.h"

CPhoneReceiver::CPhoneReceiver()
	:	CActive(EPriorityHigh),
		iCurrentStatusPckg(iCurrentCallInfo),iCallStatus(CTelephony::EStatusIdle)
	{
	}
CPhoneReceiver* CPhoneReceiver::NewLC()
	{
	CPhoneReceiver* self = new(ELeave) CPhoneReceiver();
	_CPUSH(self);
	self->ConstructL();
	return self;
	}
CPhoneReceiver* CPhoneReceiver::NewL()
	{
	CPhoneReceiver* self = CPhoneReceiver::NewLC();
	_CPOP(self);
	return self;
	}
void CPhoneReceiver::ConstructL()
{
	//Create new object to telephony
	iTelephony = CTelephony::NewL();
	//iNumms = 0;
	CActiveScheduler::Add(this);	// Add to scheduler
	StartL();
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

void CPhoneReceiver::SetObserver(MActiveCallListener* aObserver)
	{
	iObserver = aObserver;
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
			iCallStatus = CTelephony::EStatusRinging;
			break;

		case CTelephony::EStatusAnswering:
			iCallStatus = CTelephony::EStatusAnswering;
			break;
		case CTelephony::EStatusConnected:
			iCallStatus = CTelephony::EStatusConnected;
			break;
		case CTelephony::EStatusDisconnecting:
			iCallStatus = CTelephony::EStatusDisconnecting;
			break;
		case CTelephony::EStatusDialling:
			iCallStatus = CTelephony::EStatusDialling;
			break;
		case CTelephony::EStatusIdle:
			iCallStatus = CTelephony::EStatusIdle;
			iObserver->StateChangedToIdle();
			break;
		default:
			__LOGSTR1("default call status: %d",iCallStatus);
			break;
		}
		if(iCallStatus != CTelephony::EStatusIdle)
			{
			iObserver->StateChangedFromIdle();
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
TBool CPhoneReceiver::IsActiveCallPersist()
	{
	if(iCallStatus == CTelephony::EStatusIdle)
		{
		return EFalse;
		}else{
			return ETrue;
		}
	}
