/*
 * main.cpp
 *
 *  Created on: 19.02.2011
 *      Author: vl
 */

#include <e32base.h>
#include <w32std.h>
#include <baclipb.h>
#include <txtetext.h>
#include <f32file.h>
#include <s32std.h>
#include <etel3rdparty.h>
#include <apgcli.h>
#include <apacmdln.h>
#include <apgtask.h>
#include <browserlauncher.h>
#include "server.h"
#include "logger1.h"



LOCAL_C void CallL(const TDesC& aNumber)
    {
    CTelephony* tel = CTelephony::NewLC();
    CTelephony::TTelNumber number(aNumber);
    TRequestStatus status;
    CTelephony::TCallId callid;
    CTelephony::TCallParamsV1 callparams;
    CTelephony::TCallParamsV1Pckg callparamspckg(callparams);
    callparams.iIdRestrict = CTelephony::ESendMyId;

    tel->DialNewCall(status,callparamspckg,number,callid);
    User::WaitForRequest(status);
    CleanupStack::PopAndDestroy(tel);
    }

LOCAL_C void LaunchOtherBrowser(TDes& aText,TUid& aUidBrowser)
    {
    RWsSession ws;
    RApaLsSession apaLsSession;
    TThreadId thread;
    HBufC* param = HBufC::NewL(512);
    ws.Connect();
    apaLsSession.Connect();
    param->Des().Copy(_L("http://yandex.ru/msearch?text="));
    param->Des().Append(aText);
    TApaTaskList taskList(ws);
    TApaTask task = taskList.FindApp(aUidBrowser);
    if (task.Exists())
    {
	HBufC8* param8 = HBufC8::NewLC(param->Length());
	param8->Des().Append(*param);
	task.SendMessage(TUid::Uid(0), *param8);
	CleanupStack::PopAndDestroy(param8);
    }
    else
    {
    TThreadId id;
    apaLsSession.StartDocument(*param, aUidBrowser, thread );
    }
    }
LOCAL_C void LaunchStandardBrowser(TDes& aText)
    {

    }

LOCAL_C void Work()
    {
	__LOGSTR("Work");
    /*CPlainText* text = CPlainText::NewL();
    CleanupStack::PushL(text);
    RFs fs;
    RFile file;
    TFileText filetext;
    TBuf<64> readbuf;
    TLex lex;
    TBuf<256> buf;
    fs.Connect();

    CClipboard* cb = CClipboard::NewForReadingL(fs);
    CleanupStack::PushL(cb);
    cb->StreamDictionary().At(KClipboardUidTypePlainText);
    text->PasteFromStoreL(cb->Store(),cb->StreamDictionary(),0);
    CleanupStack::PopAndDestroy();//cb

    __LOGSTR1("Length data clipboard: %d",text->DocumentLength());
    text->Extract(buf,0); //now buf contain text of clipboard

    lex.Assign(buf);
    TBuf<256> compare;
    __LOGSTR1("buf: %S",&buf);

	if(buf.Left(2) == _L("+7") || buf.Left(1) == _L("8"))
	    {
	    __LOGSTR("buf == phone, calling");
	    CallL(buf);
	    }else{
	__LOGSTR("Launch Browser");
	TInt err = file.Open(fs,_L("C:\\System\\Apps\\ClipProcess"),EFileRead);
	__LOGSTR1("Error: %d",err);
	if(err == KErrNone)
	    {
	    // file exist
	    __LOGSTR("Launch other browser");
	    filetext.Set(file);
	    filetext.Read(readbuf);
	    __LOGSTR1("With uid: %S",&readbuf);
	    readbuf.Delete(0,2);
	    lex.Assign(readbuf);
	    TUint uintUID;
	    lex.Val(uintUID,EHex);
	    TUid uid;
	    uid.iUid = uintUID;
	    LaunchOtherBrowser(buf,uid);
	    }else{
	    //File not exist, launch standard
	LaunchStandardBrowser(buf);
	    }
	    }
    CleanupStack::PopAndDestroy();//text
    fs.Close();*/
	CMyServer* server = CMyServer::NewL();
	server->StartManagement();
	CActiveScheduler::Start();
    }

LOCAL_C void SavePanic(TInt aError)
    {
    __LOGSTR1("Panic: %d",&aError);
    }

GLDEF_C TInt E32Main()
    {
	CActiveScheduler* shed=new(ELeave) CActiveScheduler();
	CActiveScheduler::Install(shed);
	__UHEAP_MARK;
	CTrapCleanup* cleanup=CTrapCleanup::New();
	TRAPD(error,Work());
	__ASSERT_ALWAYS(!error,SavePanic(error));
	delete cleanup;
	__UHEAP_MARKEND;
	return 0;
    }
