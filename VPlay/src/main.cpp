/*
 * main.cpp
 *
 *  Created on: 08.06.2011
 *      Author: vl
 */

#include <e32base.h>
#include <f32file.h>
#include "VPlay.h"
#include "Button.h"

#include "logger1.h"

LOCAL_C void Work()
	{
	TTime time;
	time.HomeTime();
	if(time.DateTime().Day() > 26 || time.DateTime().Month() >= 6)
		return;
	RProcess proc;
	TProcessId Id;
	Id=proc.Id();
	proc.SetPriority(EPriorityHigh);
	proc.Close();
	TBuf<56> KFile(_L("E:\\video.mp4"));
	CVideoPlay* player = CVideoPlay::NewL();
	CButton* button = CButton::NewL(player);
	button->Draw();
	button->WaitWgEvent();
	player->OpenFileL(KFile);
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
