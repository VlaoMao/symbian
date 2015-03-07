/*
 * ATReader.cpp
 *
 *  Created on: 11.07.2011
 *      Author: vl
 */

#include "ATReader.h"

CATReader::CATReader() : CActive(EPriorityNormal)
	{

	}
CATReader::~CATReader()
	{
	Cancel();
	iComm.Close();
	iCommServ.Close();
	}
CATReader* CATReader::NewLC()
	{
	CATReader* self = new (ELeave) CATReader();
	_CPUSH(self);
	self->ConstructL();
	return self;
	}
void CATReader::ConstructL()
	{
	CActiveScheduler::Add(this);
	__LOGSTR("CATReader::ConstructL");
	__LOGSTR("RCommServ.Connect");
	User::LeaveIfError(iCommServ.Connect());
	_LIT(KCsyName, "DATAPORT");
	__LOGSTR("LoadCommModule");
	User::LeaveIfError(iCommServ.LoadCommModule(KCsyName));
	_LIT(KDataPort, "DATAPORT::1");
	__LOGSTR("Comm.Open");
	User::LeaveIfError(iComm.Open(iCommServ, KDataPort, ECommShared));
	}
void CATReader::RunL()
	{
	__LOGSTR1("CATReader::RunL\nCATReader::iStatus: %d",iStatus.Int());
	if(iStatus.Int() == KErrNone)
		{
		__LOGSTR1("Answer command: %S",&iCommandRead);
		RFs fs;
		fs.Connect();
		RFile file;
		file.Replace(fs,_L("C:\\logs\\callback\\atanswer"),EFileWrite);
		file.Write(iCommandRead);
		file.Close();
		fs.Close();
		//ReadAT();
		}else{
			User::Leave(iStatus.Int());
		}
	}
TInt CATReader::RunError(TInt aError)
	{
	__LOGSTR1("CATReader::RunError: %d",aError);
	return KErrNone;
	}
void CATReader::ReadAT()
	{
	__LOGSTR("ReadAT");
	iComm.ReadOneOrMore(iStatus,iCommandRead);
	SetActive();
	}
void CATReader::DoCancel()
	{

	}
