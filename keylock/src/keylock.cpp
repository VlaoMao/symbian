/*
 * switch.cpp
 *
 *  Created on: 19.02.2010
 *      Author: VlaoMao
 */

#include <e32base.h>
#include <f32file.h>
#include <hwrmvibra.h>
#include <aknkeylock.h>
#include "play.h"
#include "logger1.h"
#include <mprofileengine.h>
#include <mprofile.h>
	
LOCAL_C void Vibra()
    {
    RFs fs;
    RFile file;
    TLex lex;
    TFileText text;
    TBuf<32> buf;
    TInt longest;
    TInt intensive;

    fs.Connect();
    TInt err = file.Open(fs,_L("C:\\System\\Apps\\EasyKeyLock\\vibra"),EFileRead);
    CHWRMVibra* vibra = CHWRMVibra::NewL();
    if((vibra->VibraStatus() != CHWRMVibra::EVibraStatusNotAllowed) && (err == KErrNone))
	{
	text.Set(file);
	text.Read(buf);
	lex.Assign(buf);
	lex.Val(longest);
	text.Read(buf);
	lex.Assign(buf);
	lex.Val(intensive);
	vibra->StartVibraL(longest,intensive);
	User::After(longest*1000);
	vibra->StopVibraL();
	}
    }
LOCAL_C void LockKeyL()
	{
	_LIT(KSoundDir,"C:\\System\\Apps\\EasyKeyLock\\");
    _LIT(KVolumeFile,"C:\\System\\Apps\\EasyKeyLock\\volume");
    TBuf<128> bufLock;
    TBuf<128> bufUnlock;
    TBuf<128> bufName;
    TBuf<28> buf;
    TInt volume = 100;

    CDir* dir;
    RFs fs;
    RFile file;
    TFileText text;
    User::LeaveIfError(fs.Connect());
    User::LeaveIfError(fs.GetDir(KSoundDir,KEntryAttMaskSupported,ESortByName,dir));
    __LOGSTR("Getted file list");
    if(file.Open(fs,KVolumeFile,EFileRead) == KErrNone)
        {
            text.Set(file);
            text.Read(buf);
            TLex lex;
            lex.Assign(buf);
            TInt err = lex.Val(volume);
            __LOGSTR2("Readed volume: %d, error: %d",volume,err);
            file.Close();
        }
    for(TInt i = 0; i < dir->Count(); ++i)
        {
            bufName.Copy(KSoundDir);
            bufName.Append((*dir)[i].iName);
            __LOGSTR1("Parsing file: %S",&bufName);
            TParse parse;
            parse.Set(bufName,NULL,NULL);
            if(parse.Name() == _L("lock"))
                {
                    bufLock.Copy(bufName);
                }
            if(parse.Name() == _L("unlock"))
                {
                    bufUnlock.Copy(bufName);
                }
        }
    delete dir;
    fs.Close();
    MProfileEngine* engine = CreateProfileEngineL();
    MProfile* profile = engine->ActiveProfileL();

    TInt Id = engine->ActiveProfileId();
    TBool set = profile->IsSilent();

    __LOGSTR1("IsSilent: %d",set);
    __LOGSTR1("ProfileId: %d",Id);
    CmyPlay* player1 = CmyPlay::NewL();
	RAknKeyLock key;
	User::LeaveIfError(key.Connect());
	TBool status=key.IsKeyLockEnabled();
    __LOGSTR1("Max volume: %d",player1->MaxVolume());
	switch(status)
		{
        case EFalse://клавиатура разблокирована
            if(set == EFalse && (Id == 0 || Id > 2)) // Проверка , не установлен ли запрет на звуки и не включён ли профиль встреча или без звука
                {
                    player1->SetVolume(volume);
                    player1->Open(bufLock);
                }
			key.EnableWithoutNote();
			break;
		case ETrue:
            if(set == EFalse && (Id == 0 || Id > 2))
			    {
                     player1->SetVolume(volume);
                     player1->Open(bufUnlock);
			    }
			key.DisableWithoutNote();
			break;
		}
	Vibra();
    if(set == EFalse && (Id == 0 || Id > 2))
	    CActiveScheduler::Start();
	key.Close();
	}
LOCAL_C void SavePanic(TInt aError)
    {
    __LOGSTR1("Panic: %d",aError);
    }
GLDEF_C TInt E32Main()
	{
	CActiveScheduler* shed=new(ELeave) CActiveScheduler;
	CActiveScheduler::Install(shed);
	__UHEAP_MARK;
	CTrapCleanup* cleanup=CTrapCleanup::New();
	TRAPD(error,LockKeyL());
	__ASSERT_ALWAYS(!error,SavePanic(error));
	delete cleanup;
	__UHEAP_MARKEND;
	return 0;

	}
