/*
 * act.cpp
 *
 *  Created on: 14.03.2010
 *      Author: vl
 */

#include "act_management.h"

CNotifyer::CNotifyer(const TDesC& aPath) : CActive(EPriorityStandard),iPath(aPath)
{

}
CNotifyer::~CNotifyer()
{
	Cancel(); //TODO Отмена таймера, вызов DoCancel
	if(iDirList)
	{
		delete iDirList;
		iDirList = NULL;
	}
	iFs.Close();
}
void CNotifyer::ConstructL()
{
	CActiveScheduler::Add(this); //TODO Добавление активного объекта в планировщик
	iFs.Connect();
}

void CNotifyer::RunL()
{
	iFs.GetDir(iPath,KEntryAttNormal,ESortByName,iDirList);
	for(TInt i=0;i<iDirList->Count();i++)
	    {
	    if((*iDirList)[i].iName == _L("Exit"))
		{
		__LOGSTR("Find exit event, exiting....");
		iFs.Delete(KFileExit);
		CActiveScheduler::Stop();
		User::Exit(KErrNone);
		}
	    }
	Fun();
}

TInt CNotifyer::RunError(TInt aError)
{
	#ifdef __DEBUG
	__LOGSTR1("RunError: %d",aError);
	#endif
	return KErrNone;
}
void CNotifyer::DoCancel()
{
	iFs.NotifyChangeCancel();
}
CNotifyer* CNotifyer::NewL(const TDesC& aPath)
{
	CNotifyer* self = new(ELeave) CNotifyer(aPath);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
}
void CNotifyer::Fun()
{
	iFs.NotifyChange(ENotifyAll,iStatus,iPath);
	SetActive();
}

