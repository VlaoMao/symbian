/*
 * GisWeather : main.cpp
 *
 *  Created on: 25.11.2010
 *  Author: vl
 */
#include <e32base.h>
#include <f32file.h>
#include "server.h"
#include "logger1.h"

LOCAL_C void Work()
	{
	RProcess proc;
	TParse parser;
	TLex lex;
	TInt num;
	TFullName name = proc.FullName();
	TBuf<256> buf = name.Right(4);
	lex.Assign(buf);
	lex.Val(num);
#ifdef __DEBUG
	__LOGSTR1("num: %d",num);
#endif
	if(num > 1)
	    {
	    return ;//выходим
	    }else{
    #ifndef __SELF_SIGN__
	    __LOGSTR("__SELF_SIGN__ not defined!");
	TProcessId Id;
	Id=proc.Id();
	proc.SetPriority(EPriorityHigh);
	proc.Close();
    #endif

	CMyServer* serv = CMyServer::NewL();
	CleanupStack::PushL(serv);
    #ifdef __DEBUG
	__LOGSTR("Serv->WaitWgEvent main");
    #endif
	serv->WaitWgEvent();
	CActiveScheduler::Start();
	CleanupStack::PopAndDestroy(1);//serv
	    }
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
	TRAPD(error,Work());
	__ASSERT_ALWAYS(!error,SavePanic(error));
	delete cleanup;
	__UHEAP_MARKEND;
	return 0;
	}
