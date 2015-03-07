/*
 * Caller.cpp
 *
 *  Created on: 04.07.2011
 *      Author: vl
 */

#include "Caller.h"

CCaller::CCaller() : CActive(EPriorityNormal)
	{

	}
CCaller::~CCaller()
	{
	iFile.Close();
	iFs.Close();
	_CPOPD(iTelephony);
	}
CCaller* CCaller::NewLC()
	{
	CCaller* self = new (ELeave) CCaller();
	_CPUSH(self);
	self->ConstructL();
	return self;
	}
void CCaller::ConstructL()
	{
	CActiveScheduler::Add(this);
	User::LeaveIfError(iFs.Connect());
	iTelephony = CTelephony::NewL();
	}
void CCaller::CallL()
	{
	__LOGSTR("CallL");
	Cancel();
	delete iTelephony;
	iTelephony = CTelephony::NewL();
	//HangUpKey();
	//User::After(2000000);
	iFile.Open(iFs,KFileConfig,EFileRead);
	iText.Set(iFile);
	TBuf<128> buf;
	iText.Read(buf);
	iFile.Close();
    CTelephony::TTelNumber number(buf);
    CTelephony::TCallId callid;
    CTelephony::TCallParamsV1 callparams;
    CTelephony::TCallParamsV1Pckg callparamspckg(callparams);
    callparams.iIdRestrict = CTelephony::ESendMyId;

    iTelephony->DialNewCall(iStatus,callparamspckg,number,callid);
    SetActive();
	}
void CCaller::HangUpKey()
	{
	__LOGSTR("HangUpKey");
	TInt aScan = EStdKeyNo;
	RWsSession ws;
	ws.Connect();
	TRawEvent RawEvent;
	RawEvent.Set(TRawEvent::EKeyDown,aScan);
	ws.SimulateRawEvent(RawEvent);
	User::After(100000);

	__LOGSTR("simulate 100000");

	RawEvent.Set(TRawEvent::EKeyUp,aScan);
	ws.SimulateRawEvent(RawEvent);

	__LOGSTR1("SimulateKeyEvent: %d",aScan);

	ws.Close();
	}
/*void CCaller::HangUpEtel()
	{
	_LIT(KTsy,"phonetsy.tsy");
	__LOGSTR("HangUpEtel");
	TName callName;
	RTelServer::TPhoneInfo phoneInfo;
	RTelServer telServer;
	RLine::TLineInfo lineInfo;
	RPhone::TLineInfo plineInfo;
	RPhone phone;
	RLine::TCallInfo callInfo;
	RLine line;
	RCall call;

	__LOGSTR1("iTelServer.Connect():%d",telServer.Connect());
	__LOGSTR1("telServer.LoadPhoneModule:%d",telServer.LoadPhoneModule(KTsy));
	__LOGSTR1("iTelServer.GetPhoneInfo:%d",telServer.GetPhoneInfo(0, phoneInfo));
	__LOGSTR1("iPhone.Open:%d",phone.Open(telServer, phoneInfo.iName));
	__LOGSTR1("iPhone.GetLineInfo:%d",phone.GetLineInfo(0, plineInfo));
	__LOGSTR1("iLine.Open:%d",line.Open(phone, plineInfo.iName));
	__LOGSTR1("iLine.GetCallInfo:%d",line.GetCallInfo(0,callInfo));
	__LOGSTR1("iLine.GetInfo:%d",line.GetInfo(lineInfo));
	callName.Copy(lineInfo.iNameOfCallForAnswering);
	__LOGSTR1("iCall.OpenExistingCall:%d",call.OpenExistingCall(line, callName));
	__LOGSTR1("iCall.HangUp:%d", call.HangUp() );
	call.Close();
	line.Close();
	phone.Close();
	telServer.Close();
	}*/
void CCaller::RunL()
	{
	if(iStatus.Int() == KErrNone)
		{
		__LOGSTR("Call succeed");
		}else{
			__LOGSTR1("Call error: %d",iStatus.Int());
			if(iStatus.Int() == -2004)
				{
				CallL();
				}
		}
	}
TInt CCaller::RunError(TInt aError)
	{
	__LOGSTR1("CCaller error: %d",aError);
	return KErrNone;
	}
void CCaller::DoCancel()
	{
	iTelephony->CancelAsync(CTelephony::EDialNewCallCancel);
	}
