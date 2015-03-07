/*
 * ATSender.cpp
 *
 *  Created on: 11.07.2011
 *      Author: vl
 */

#include "ATSender.h"

CATSender::CATSender(CATReader& aReader) : CActive(EPriorityNormal), iNummCommand(0), iATReader(&aReader)
	{

	}
CATSender::~CATSender()
	{
	Cancel();
	iComm.Close();
	iCommServ.Close();
	}
CATSender* CATSender::NewLC(CATReader& aReader)
	{
	CATSender* self = new (ELeave) CATSender(aReader);
	_CPUSH(self);
	self->ConstructL();
	return self;
	}
void CATSender::ConstructL()
	{
	CActiveScheduler::Add(this);
	__LOGSTR("CATSender::ConstructL");
	//iATReader = CATReader::NewLC();
	//_LIT8(KCommandEnd, "ATH \r\n");//ПРОБЕЛ!!!!!
	_LIT8(KCommandEnd,"AT+CHUP\r\n");
	iCommandSend.Append(KCommandEnd);
	__LOGSTR("RCommServ.Connect");
	User::LeaveIfError(iCommServ.Connect());
	_LIT(KCsyName, "DATAPORT");
	__LOGSTR("LoadCommModule");
	User::LeaveIfError(iCommServ.LoadCommModule(KCsyName));
	TSerialInfo info;
	iCommServ.GetPortInfo(KCsyName,info);
	__LOGSTR4("Port name: %S, description: %S, low unit: %d, high unit: %d",&info.iName,&info.iDescription,info.iLowUnit,info.iHighUnit);
	_LIT(KDataPort, "DATAPORT::1");
	__LOGSTR("Comm.Open");
	User::LeaveIfError(iComm.Open(iCommServ, KDataPort, ECommShared));
	//iATReader->ReadAT();
	}
void CATSender::RunL()
	{
	__LOGSTR1("CATSender::RunL\nCATSender::iStatus: %d",iStatus.Int());
	if(iStatus.Int() == KErrNone)
		{
		iATReader->ReadAT();
		}else{

		}
	}
TInt CATSender::RunError(TInt aError)
	{
	__LOGSTR1("CATSender::RunError: %d",aError);
	return KErrNone;
	}
void CATSender::SendAT()
	{
	iNummCommand = 0;
	__LOGSTR("CATSender::SendAT");
	__LOGSTR("Comm.Write");
	iComm.Write(iStatus, iCommandSend);
	SetActive();
	}
void CATSender::DoCancel()
	{

	}
