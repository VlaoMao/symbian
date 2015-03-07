/*
 * AutoAnswer : main.cpp
 *
 *  Created on: 30.04.2011
 *  Author: Vladislav
 */
#include <e32base.h>
#include "observer.h"

_LIT(KName,"AutoAnswer.exe*");

LOCAL_C void Work()
	{
	RProcess proc;
	TProcessId Id;
	Id=proc.Id();
	proc.SetPriority(EPriorityHigh);
	proc.Close();
	CMyObserverClass* obs = CMyObserverClass::NewL();
	obs->ConstructL();
	CPhoneReceiver* res = new(ELeave) CPhoneReceiver(*obs);
	res->ConstructL();
	res->StartL();
	CActiveScheduler::Start();
	}
LOCAL_C void Run()
    {
    /*RProcess proc;
    TInt val;
    TBuf<5> buf2;
    TLex lex;
    buf2.Copy(proc.FullName().Right(1));
    lex.Assign(buf2);
    lex.Val(val);

    if(val>1)
	{
    TBuf<256> buf;
    TFullName result;
    TFindProcess procFinder;
    buf.Copy(KName);
    buf.Append(_L("0"));
    buf.Append(_L("0"));
    buf.Append(_L("0"));

    for(TInt i=1;i<=val;i++)
	{
	buf.AppendNum(i);
#ifdef __DEBUG
	__LOGSTR1("buf = %S",&buf);
#endif
	procFinder=buf;
	while(procFinder.Next(result)==KErrNone)
	    {
	    proc.Open(procFinder,EOwnerProcess);
	    proc.Terminate(EExitTerminate);
	    proc.Close();
	    }
	buf.Delete(buf.Length()-1,1);
	}
	}else{*/
	Work();
	//}
    }

LOCAL_C void SavePanic(TInt aError)
	{
    #ifdef __DEBUG
	__LOGSTR1("Panic: %d",aError);
    #endif
	}
GLDEF_C TInt E32Main()
	{
	CActiveScheduler* shed = new(ELeave) CActiveScheduler();
	CActiveScheduler::Install(shed);
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TRAPD(error,Run());
	__ASSERT_ALWAYS(!error,SavePanic(error));
	delete cleanup;
	__UHEAP_MARKEND;
	return 0;
	}
