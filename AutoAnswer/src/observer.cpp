/*
 * observer.cpp
 *
 *  Created on: 29.04.2011
 *      Author: vl
 */
#include "observer.h"
// ---------------------------------------------------------
//	CallRinging
// ---------------------------------------------------------

CMyObserverClass::CMyObserverClass() : CActive(EPriorityHigh)
{

}
CMyObserverClass::~CMyObserverClass()
{

}
void CMyObserverClass::ConstructL()
{
#ifdef __DEBUG
		__LOGSTR("CMyObserverClass::ConstructL()");
#endif
	CActiveScheduler::Add(this);
	iTelephony = CTelephony::NewL();
}
CMyObserverClass* CMyObserverClass::NewL()
{
	CMyObserverClass* self = new(ELeave) CMyObserverClass();
	return self;
}
void CMyObserverClass::RunL()
{
	Cancel();
}
void CMyObserverClass::DoCancel()
{
	iTelephony->CancelAsync(CTelephony::EOwnedCall1StatusChangeCancel);
}
/************************************************************************/
/* This function is called when the phone call is answered              */
/************************************************************************/
void CMyObserverClass::CallAnswered()
{
#ifdef __DEBUG
	__LOGSTR("Call Answered");
#endif
}
void CMyObserverClass::CallRinging()
{
#ifdef __DEBUG
	__LOGSTR("Call Ringing");
#endif

	//Open line
	iTelephony->AnswerIncomingCall(iStatus, iCallID);
	SetActive();
}
