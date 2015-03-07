/*
 *  Accessories
 *
 *  Created on: 21.10.2011
 *  Author: SQR
 */
#include <e32base.h>
#include "logger1.h"
#include "Acc.h"
#include "accel.h"

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

	    if(val>1)
		{
	    	CAcc* acc = new(ELeave) CAcc();
	    	acc->LaunchMPXViewLNoSimulate(KMPXPlaybackViewTypeUid);
		}else{
			RProcess processHandle;
			__LOGSTR("Set process priority");
			processHandle.SetPriority(EPriorityHigh);
			processHandle.Close();
            /******************/
           //     CAccel* accel = CAccel::NewLC();
           //     accel->StartMonitor();
            /******************/
			CAcc* acc = CAcc::NewLC();
			__LOGSTR("Destroy acc");
			_CPOPD(acc);
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
