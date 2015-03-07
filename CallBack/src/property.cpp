/*
 * property.cpp
 *
 *  Created on: 15.12.2011
 *      Author: vl
 *  Реализация класса, оповещающего о необходимости настройки позиции окна
 */

#include "property.h"

CPropImpl::CPropImpl() : CActive(EPriorityNormal)
	{

	}
CPropImpl::~CPropImpl()
	{

	}
CPropImpl* CPropImpl::NewL()
	{
	CPropImpl* self = CPropImpl::NewLC();
	_CPOP(self);
	return self;
	}
CPropImpl* CPropImpl::NewLC()
	{
	CPropImpl* self = new (ELeave) CPropImpl();
	_CPUSH(self);
	self->ConstructL();
	return self;
	}
void CPropImpl::ConstructL()
	{
	__LOGSTR("CPropImpl::ConstructL");
	CActiveScheduler::Add(this);
	//iProperty = RProperty();
	static _LIT_SECURITY_POLICY_PASS(KAllowAllPolicy);
	static _LIT_SECURITY_POLICY_C1(KPowerMgmtPolicy,ECapabilityPowerMgmt);
	TInt r = iProperty.Define(PropertyUID,0x01,RProperty::EInt,KAllowAllPolicy,KPowerMgmtPolicy);
	if (r!=KErrAlreadyExists)
	    {
	    User::LeaveIfError(r);
	    }
	}
void CPropImpl::RunL()
	{
	__LOGSTR("CPropImpl::RunL");
	if(iStatus.Int() == KErrNone)
		{
		//callback
		iObserver->NeedSetPos();
		iProperty.Cancel();
		Subscribe();
		}
	}
TInt CPropImpl::RunError(TInt aError)
	{
	return KErrNone;
	}
void CPropImpl::DoCancel()
	{
	iProperty.Cancel();
	}
void CPropImpl::Subscribe()
	{
	__LOGSTR("CPropImpl::Subscribe");
	TInt r = iProperty.Attach(PropertyUID,0x01,EOwnerThread);
	User::LeaveIfError(r);
	iProperty.Subscribe(iStatus);
	SetActive();
	}
void CPropImpl::SetObserver(MVirtualObserver* aNewObserver)
	{
	__LOGSTR("CPropImpl::SetObserver");
	iObserver = aNewObserver;
	}
