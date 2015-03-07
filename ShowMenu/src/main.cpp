/*
 *  ShowMenu
 *
 *  Created on: 06.10.2011
 *  Author: SQR
 */
#include <e32base.h>
#include <f32file.h>
#include <w32std.h>
#include <apgtask.h>
#include <apgcli.h>
#include <apacmdln.h>
#include <s32file.h>
#include "logger1.h"

#define __MENU_UID__ 0x101f4cd2

LOCAL_C TInt RunProg(const TUid& aUid)
	{
	RApaLsSession apaLsSession;
	__LOGSTR1("UID: %d",aUid);
	User::LeaveIfError(apaLsSession.Connect());
	CleanupClosePushL(apaLsSession);

	TApaAppInfo appInfo;
	TInt retVal=apaLsSession.GetAppInfo(appInfo,aUid);
	__LOGSTR1("Start process by UID return value: %d",retVal);
	if(retVal == KErrNone)
		{
		CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
		cmdLine->SetExecutableNameL(appInfo.iFullName);
		cmdLine->SetCommandL(EApaCommandRun);
		User::LeaveIfError( apaLsSession.StartApp(*cmdLine) );
		__CPOPD(cmdLine);
		}
	else
		{

		}
	CleanupStack::PopAndDestroy(&apaLsSession);
	return retVal;
	}
LOCAL_C void Work()
	{
	RFs fs;
	RWsSession ws;
	User::LeaveIfError(fs.Connect());
        RFile file;
        if(file.Create(fs,_L("C:\\test.file"),EFileStream|EFileWrite)==KErrNone)
        {
                TBuf8<25> buf;
                TUint32 num(4294967295);
		RFileWriteStream stream;
		stream.Attach(file);
		stream.WriteUint32L(100);
		stream.Close();
                file.Close();
        }
        fs.Close();
    }

LOCAL_C void SaveErr(TInt aError)
	{
	__LOGSTR1("Error: %d",aError);
	}
GLDEF_C TInt E32Main()
	{
	CActiveScheduler* shed = new(ELeave) CActiveScheduler();
	CActiveScheduler::Install(shed);
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TRAPD(error,Work());
	__ASSERT_ALWAYS(!error,SaveErr(error));
	delete cleanup;
	__UHEAP_MARKEND;
	return 0;
	}
