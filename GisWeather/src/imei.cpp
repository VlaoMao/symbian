/*
 * autoscript : imei.cpp
 *
 *  Created on: 17.01.2011
 *  Author: vl
 */
#include "imei.h"

void CInfoApp::GetIMEI(TDes& aIMEI)
{
	CInfoApp* self= new (ELeave) CInfoApp(aIMEI);
	CleanupStack::PushL(self);
	self->iWhatGet = EImeiGet;
	self->ConstructL();
	CActiveScheduler::Start();

	CleanupStack::PopAndDestroy(self);
}
void CInfoApp::GetPhoneModel(TDes& aModel)
{
	CInfoApp* self = new (ELeave) CInfoApp(aModel);
	CleanupStack::PushL(self);
	self->iWhatGet = EModelGet;
	self->ConstructL();
	CActiveScheduler::Start();

	CleanupStack::PopAndDestroy(self);
}

void CInfoApp::ConstructL()
{
	CActiveScheduler::Add(this);
	switch(iWhatGet)
	{
	case ENothing:
		break;
	case EImeiGet:
		iTelephony = CTelephony::NewL();
		iTelephony->GetPhoneId(iStatus, iPhoneIdV1Pckg);
		SetActive();
		break;
	case EModelGet:
		iTelephony = CTelephony::NewL();
		iTelephony->GetPhoneId(iStatus,iPhoneIdV1Pckg);
		SetActive();
		break;
	}
}

CInfoApp:: CInfoApp(TDes& imei): CActive(EPriorityStandard),iInternalBuf(imei),iPhoneIdV1Pckg(iPhoneIdV1),iWhatGet(ENothing)
{
    //default constructor
}

CInfoApp::~CInfoApp()
{
    delete iTelephony;
    iTelephony = NULL;
}

void CInfoApp::RunL()
{
    if(iStatus==KErrNone)
    {
    	switch(iWhatGet)
    	{
    	case ENothing:
    		CActiveScheduler::Stop();
    		break;
    	case EImeiGet:
    		iInternalBuf = iPhoneIdV1.iSerialNumber;
    		break;
    	case EModelGet:
    		iInternalBuf.Copy(iPhoneIdV1.iManufacturer);
    		iInternalBuf.Append(_L(" "));
    		iInternalBuf.Append(iPhoneIdV1.iModel);
    		break;
    	}
    	CActiveScheduler::Stop();

    }
}

void CInfoApp::DoCancel()
{
    iTelephony->CancelAsync(CTelephony::EGetPhoneIdCancel);
}
