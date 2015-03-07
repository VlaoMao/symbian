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
      iCurrentStatusPckg(iCurrentCallInfo),iCallStatus(CTelephony::EStatusIdle),iIn(ETrue)
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
    iSettings = CSettings::NewL();
    SetObserver(iSettings);
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
            iIn = ETrue;
			break;
		case CTelephony::EStatusAnswering:
			iCallStatus = CTelephony::EStatusAnswering;
			break;
		case CTelephony::EStatusConnected:
			iCallStatus = CTelephony::EStatusConnected;
            if(!iIn)
                iObserver->CallConnected();
			break;
		case CTelephony::EStatusDisconnecting:
            iCallStatus = CTelephony::EStatusDisconnecting;
            if(!iIn)
                iObserver->CallDisconnected();
			break;
		case CTelephony::EStatusDialling:
			iCallStatus = CTelephony::EStatusDialling;
            iIn = EFalse;
			break;
		case CTelephony::EStatusIdle:
			iCallStatus = CTelephony::EStatusIdle;
			break;
		default:
			__LOGSTR1("default call status: %d",iCallStatus);
			break;
		}
		__LOGSTR("Run startL");
	}
	else
	{
		__LOGSTR1("Error In status,iStatus: %d",iStatus.Int());
	}
	StartL();
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
