/*
 *  template
 *
 *  Created on: date
 *  Author: SQR
 */
#include <e32base.h>
#include "logger1.h"
#include "act.h"

LOCAL_C void Work()
	{
	    __LOGSTR("Work");
	    RProcess proc;
	    TInt val;
	    TBuf<5> buf2;
	    TLex lex;
	    buf2.Copy(proc.FullName().Right(1));
	    lex.Assign(buf2);
	    lex.Val(val);

	    if(val > 1)
		{
		}else{
            CPhoneReceiver* res = CPhoneReceiver::NewLC();
            CActiveScheduler::Start();
            _CPOPD(res);
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
	delete shed;
	return 0;
	}
