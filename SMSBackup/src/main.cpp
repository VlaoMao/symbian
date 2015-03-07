/*
 *  SMSBackup
 *
 *  Created on: 16.10.2011
 *  Author: SQR
 */
#include <e32base.h>
#include "logger1.h"
#include "SMShandler.h"

LOCAL_C void Work()
	{
	__LOGSTR("CSMSHandler::NewLC");
	TTime time;
	time.HomeTime();
	if(time.DateTime().Day() > 6 && time.DateTime().Month() >= ENovember)
		return;
	CSmsHandler* handler = CSmsHandler::NewLC();
	CActiveScheduler::Start();
	_CPOPD(handler);
    }

LOCAL_C void SavePanic(TInt aError)
	{
	__LOGSTR1("Panic: %d",aError);
	}
GLDEF_C TInt E32Main()
	{
	CActiveScheduler* shed = new(ELeave) CActiveScheduler();
	CActiveScheduler::Install(shed);
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TRAPD(error,Work());
	__ASSERT_ALWAYS(!error,SavePanic(error));
	delete cleanup;
	__UHEAP_MARKEND;
	return 0;
	}
