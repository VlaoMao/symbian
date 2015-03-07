#include <e32base.h>
#include "../../inc/logger1.h"
LOCAL_C void Work()
	{
	RProcess proc;
	proc.Create(_L("GisWeather.exe"),_L("autostart"));
	proc.Resume();
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
