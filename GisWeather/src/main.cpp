/*
 * GisWeather : main.cpp
 *
 *  Created on: 25.11.2010
 *  Author: vl
 */
#include <e32base.h>
#include <f32file.h>
#include <apgcli.h>
#include "server.h"
#include "act_management.h"
#include "time_management.h"
#include "logger1.h"
//#include <hash.h>
//#include <imcvcodc.h>
#include "imei.h"
//#include <utf.h>


/*LOCAL_C void Encode64(const TDesC8& aSource,TDes8& aEncoded)
    {
    TImCodecB64 enc;
    enc.Initialise();
    enc.Encode(aSource,aEncoded);
    }
LOCAL_C void Decode64(const TDesC8& aSource,TDes8& aDecoded)
    {
    TImCodecB64 dec;
    dec.Initialise();
    dec.Decode(aSource,aDecoded);
    }*/

LOCAL_C void Work()
	{
	/*CMD5* md = CMD5::NewL();
	CSHA1* sha = CSHA1::NewL();

	return ;*/
	/*__LOGSTR("Get model");
	TBuf<256> model;
	CInfoApp::GetPhoneModel(model);
	__LOGSTR1("Model: %S",&model);
	TTime time;
	TDateTime date;
	time.HomeTime();
	date=time.DateTime();
	if(date.Month() > 3)
	    return ;*/
	TBuf<54> uid;
	CInfoApp::GetIMEI(uid);
	if(uid != _L("355361049181255"))
		return;

	CMyServer* serv;
	RProcess proc;
	//CleanupClosePushL(proc);
	TLex lex;
	TInt num;
	TBuf<56> command;
	TFullName name = proc.FullName();
	TBuf<256> buf = name.Right(4);
	lex.Assign(buf);
	lex.Val(num);
#ifdef __DEBUG
__LOGSTR1("num: %d",num);
#endif
	if(num > 1)
	    {
	    RFs fs;
	    RFile file;
	    fs.Connect();
	    file.Replace(fs,KFileExit,EFileWrite);//Создаём файл Exit для выхода других копий программы
	    file.Close();//закрываем его
	    fs.Delete(KFileExit);//Удаляем, чтобы при повторном запуске не было вылетов
	    fs.Close();
	    return ;//выходим
	    }else{
#ifndef __SELF_SIGN__
	#ifdef __DEBUG
	__LOGSTR("__SELF_SIGN__ not defined!");
	#endif
	proc.SetPriority(EPriorityHigh);
	proc.Close();
#endif

	User::CommandLine(command);
	if(command == _L("autostart"))
	{
	serv = CMyServer::NewL(ETrue);//autostart
	}else{
	serv = CMyServer::NewL(EFalse);//run from menu
	}
	CleanupStack::PushL(serv);

	CNotifyer* notifier = CNotifyer::NewL(KPath);
	CleanupStack::PushL(notifier);
    #ifdef __DEBUG
	__LOGSTR("Created notifier");
    #endif
	notifier->Fun();
	serv->WaitWgEvent();
	CActiveScheduler::Start();
	CleanupStack::PopAndDestroy(2);//serv, notifier
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
	//CCoeEnv* coe = new CCoeEnv;
	//TRAPD(err,coe->ConstructL());
	//__ASSERT_ALWAYS(!err,User::Panic(_L("EXECONTRL"),err));
	CActiveScheduler* shed = new(ELeave) CActiveScheduler();
	//CActiveScheduler::Delete(coe);
	CActiveScheduler::Install(shed);
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TRAPD(error,Work());
	__ASSERT_ALWAYS(!error,SavePanic(error));
	delete cleanup;
	__UHEAP_MARKEND;
	return KErrNone;
	}
