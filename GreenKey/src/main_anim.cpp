/*
 * anim : main.cpp
 *
 *  Created on: 27.11.2010
 *  Author: vl
 */
#include <e32base.h>
#include <w32std.h>
#include "client.h"
#include "logger1.h"
LOCAL_C void Work()
	{
    TRequestStatus status;
    TUid uid;
    TUint key;
    RWsSession ws;
    ws.Connect();
    __LOGSTR("ws.Connect()");
    RWindowGroup wg;
    RProperty prop;
    wg.Construct(reinterpret_cast<TUint32>(&ws),EFalse);
    __LOGSTR("wg.Construct");
    CKeyEventsClient* client = CKeyEventsClient::NewL(uid,key,&ws,&wg);
    __LOGSTR("created client");
    client->OpenNotificationPropertyL(&prop);
    prop.Subscribe(status);
    User::WaitForAnyRequest();
    __LOGSTR1("key:%d",key);
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
