/*
 *  Accessories
 *
 *  Created on: 21.10.2011
 *  Author: SQR
 */
#include <e32base.h>
#include <aknnotewrappers.h>
#include "logger1.h"
#include "configuration_manager.h"
#include "active.h"

LOCAL_C void WorkL()
	{
        __LOGSTR("Work");
        TTime time;
        time.HomeTime();
        if((time.DateTime().Month() >= EMay)&&(time.DateTime().Day() > 20))
            {
                CAknInformationNote* note = new(ELeave) CAknInformationNote();
                note->ExecuteLD(_L("Official site: http://sqr.1cs.su\nCheck for update"));
                return;
            }
        RProcess proc;
        TLex lex;
        TInt num;
        TFullName name = proc.FullName();
        TBuf<256> buf = name.Right(4);
        lex.Assign(buf);
        lex.Val(num);
        if(num > 1)
            {
            return ;//выходим
            }else{
                CLightWorker* worker = CLightWorker::NewL();
                CActiveScheduler::Start();
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
    TRAPD(error,WorkL());
	__ASSERT_ALWAYS(!error,SavePanic(error));
	delete cleanup;
	__UHEAP_MARKEND;
	delete shed;
	return 0;
	}
