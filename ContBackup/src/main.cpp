/*
 *  ContBackup
 *
 *  Created on: 01.11.2011
 *  Author: SQR
 */
#include <e32base.h>
//#include <cpbkcontactengine.h>
#include "logger1.h"
#include "vCardBack.h"

_LIT(KFormat,"C:\\cont\\%d.vcf");

LOCAL_C void Work()
	{
	RFs fs;
	User::LeaveIfError(fs.Connect());
	CContactDatabase* db = CContactDatabase::OpenL();

	__LOGSTR1("arr count: %d",db->CountL());

	for(TInt i = 0; i < db->CountL() ; ++i)
		{
		TBuf<56> buf;
		buf.Zero();
		buf.Format(KFormat,i);

		ExportVCardL(buf,i);
		}

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
