/*
 * change_trap.cpp
 *
 *  Created on: 19.11.2011
 *      Author: vl
 */

#include "change_trap.h"

CChangeTrap::CChangeTrap() : CActive(EPriorityNormal)
	{

	}
CChangeTrap::~CChangeTrap()
	{
	Cancel();
	iFs.Close();
	}
void CChangeTrap::ConstructL()
	{
	__LOGSTR("ChangeTrap::COnstructL");
	CActiveScheduler::Add(this);

	User::LeaveIfError(iFs.Connect());
    if( KErrNone == HAL::Get(HALData::EClipboardDrive,iClipboardDrive))
    	{

    	}else{
    		iClipboardDrive = 2;//drive C for default
    	}
    switch(iClipboardDrive)
    	{
    	case EDriveC:
    		iClipboardPath.Format(KPathFormat,&_L("C"));
    		break;
    	case EDriveD:
    		iClipboardPath.Format(KPathFormat,&_L("D"));
    		break;
    	case EDriveE:
    		iClipboardPath.Format(KPathFormat,&_L("E"));
    		break;
    	case EDriveF:
    		iClipboardPath.Format(KPathFormat,&_L("F"));
    		break;
    	}
	//iFs.GetDriveName(iClipboardDrive,iClipboardName);

	__LOGSTR1("Clipboard file path: %S",&iClipboardPath);
	}
CChangeTrap* CChangeTrap::NewL()
	{
	CChangeTrap* self = CChangeTrap::NewLC();
	_CPOP(self);
	return self;
	}
CChangeTrap* CChangeTrap::NewLC()
	{
	CChangeTrap* self = new (ELeave) CChangeTrap();
	_CPUSH(self);
	self->ConstructL();
	return self;
	}
void CChangeTrap::RunL()
	{
	__LOGSTR("CChangeTrap::RunL");
	iObserver->ClipboardChanged();
	StartMonitoring();
	}
void CChangeTrap::DoCancel()
	{
	iFs.NotifyChangeCancel();
	}
TInt CChangeTrap::RunError(TInt aError)
	{
	return KErrNone;
	}
void CChangeTrap::StartMonitoring()
	{
	__LOGSTR1("CChangeTrap::StartMonitoring dir: %S",&iClipboardPath);
	iFs.NotifyChange(ENotifyWrite,iStatus,iClipboardPath);
	SetActive();
	}
void CChangeTrap::StopMonitoring()
	{
	__LOGSTR("CChangeTrap::StopMonitoring");
	Cancel();
	}
void CChangeTrap::SetObserver(MNotifyChangeServer* aNewObserver)
	{
	__LOGSTR("CChangeTrap::SetObserver");
	iObserver = aNewObserver;
	}
