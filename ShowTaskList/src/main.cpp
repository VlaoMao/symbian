/*
 * AutoAnswer : main.cpp
 *
 *  Created on: 30.04.2011
 *  Author: Vladislav
 */
#include <e32base.h>
#include <eikenv.h>
#include "logger1.h"

LOCAL_C void SavePanic(TInt aError)
	{
	__LOGSTR1("Panic: %d",aError);
	}
GLDEF_C TInt E32Main()
	{
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	CEikonEnv* env = new CEikonEnv;
	TRAPD(err,env->ConstructL());
	env->Static()->DisplayTaskList();
	__ASSERT_ALWAYS(!err,SavePanic(err));
	delete env;
	delete cleanup;
	__UHEAP_MARKEND;
	return 0;
	}
