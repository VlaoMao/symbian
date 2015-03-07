/*
 * main.cpp
 *
 *  Created on: 05.11.2010
 *      Author: vl
 */
#include <e32base.h>
#include "act.h"
_LIT(KName,"DiskActive.exe*");

LOCAL_C void Work()
	{
	CMyClass* notif = CMyClass::NewL();
	notif->Fun();
	CActiveScheduler::Start();
	}
LOCAL_C void Run()
    {
    RProcess proc;
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
	__LOGSTR1("buf = %S",&buf);
	procFinder=buf;
	while(procFinder.Next(result)==KErrNone)
	    {
	    proc.Open(procFinder,EOwnerProcess);
	    proc.Terminate(EExitTerminate);
	    proc.Close();
	    }
	buf.Delete(buf.Length()-1,1);
	}
	}else{
	Work();
	}
    }

LOCAL_C void SavePanic(TInt aError, const TUint8* aFile, TInt aLine)
	{
	__LOGSTR3("Panic: %d, File: %S : %d",aError,aFile,aLine);
	}
GLDEF_C TInt E32Main()
	{
	CActiveScheduler* shed = new(ELeave) CActiveScheduler();
	CActiveScheduler::Install(shed);
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TRAPD(error,Run());
	__ASSERT_ALWAYS(!error,SavePanic(error,(TText8*)__FILE__,__LINE__));
	delete cleanup;
	__UHEAP_MARKEND;
	return 0;
	}
