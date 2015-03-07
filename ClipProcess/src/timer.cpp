/*
 * timer.cpp
 *
 *  Created on: 20.11.2011
 *      Author: vl
 */

#include "timer.h"

CPTimer::CPTimer() : CActive(EPriorityNormal)
	{

	}
CPTimer::~CPTimer()
	{
	if(iTimer)
		{
		iTimer->Cancel();
		delete iTimer;
		}
	}
CPTimer* CPTimer::NewL()
	{
	CPTimer* self = CPTimer::NewLC();
	_CPOP(self);
	return self;
	}
CPTimer* CPTimer::NewLC()
	{
	CPTimer* self = new (ELeave) CPTimer();
	_CPUSH(self);
	self->ConstructL();
	return self;
	}
void CPTimer::ConstructL()
	{
	__LOGSTR("CPTimer::ConstructL");
	CActiveScheduler::Add(this);
	iTimer = CPeriodic::NewL(EPriorityNormal);
	}
TInt CPTimer::CallBackTimer(TAny* aObject)
	{
	__LOGSTR("CPTimer::CallBackTimer");
	((CPTimer*)aObject)->Tick();
	return 1;
	}
void CPTimer::StartTimer(TInt aSeconds)
	{
	__LOGSTR("CPTimer::StartTimer");
	if(iTimer)
		{
		iTimer->Cancel();
		//delete iTimer;
		}
	//iTimer = CPeriodic::New(EPriorityNormal);
	iTimer->Start(aSeconds * 1000000,aSeconds * 1000000,TCallBack(CallBackTimer,this));
	}
void CPTimer::Tick()
	{
	__LOGSTR("CPTimer::HideRequest");
	iObserver->HideRequest();
	}
void CPTimer::RunL()
	{
	__LOGSTR("CPTimer::RunL");
	}
void CPTimer::DoCancel()
	{
	if(iTimer->IsActive())
		{
		iTimer->Cancel();
		}
	}
TInt CPTimer::RunError(TInt aError)
	{
	__LOGSTR("CPTimer::RunError");
	return KErrNone;
	}
void CPTimer::SetObserver(MNotifyChangeServer* aObserver)
	{
	__LOGSTR("CPTimer::SetObserver");
	iObserver = aObserver;
	}
void CPTimer::StopTimer()
	{
	if(iTimer)
		{
		iTimer->Cancel();
		//delete iTimer;
		}
	}
