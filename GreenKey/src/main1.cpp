/*
 * anim : main1.cpp
 *
 *  Created on: 27.11.2010
 *  Author: vl
 */
#include <e32base.h>
#include "myanim.h"
LOCAL_C void Work()
	{
    CMyAnim* anim = CMyAnim::NewL();
	}
LOCAL_C void SavePanic(TInt aError)
	{
	
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
