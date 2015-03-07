#include "configuration_manager.h"

void CConfigurationManager::ConstructL()
    {
        CActiveScheduler::Add(this);
        User::LeaveIfError(iFs.Connect());
        CleanupClosePushL(iFs);
        iFs.MkDirAll(KBaseDirSettingsPath);
    }

void CConfigurationManager::SetObserver(MSettingsCallBack *aNewObserver)
    {
        if(aNewObserver)
            iObserver = aNewObserver;
    }
void CConfigurationManager::LoadSettings()
    {
        __L("CConfigurationManager::LoadSettings");
        if(iFile.Open(iFs,KBaseConfSettingsPath,EFileWrite | EFileRead) != KErrNone)
            {
                __L("iFile.Open != KErrNone");
                User::LeaveIfError(iFile.Replace(iFs,KBaseConfSettingsPath,EFileWrite | EFileRead));
                iFile.Write(0,_L8("\xff\xfe"));//signature
                iText.Set(iFile);
                iText.Write(_L("00:00 - 100\r\n"));//default config
                iFile.Close();
                LoadSettings();
            }
        iText.Set(iFile);
        TTime ttime;
        ttime.HomeTime();
        TDateTime dtime = ttime.DateTime();
        TBuf<100> TimeFromString;
        TBuf<20> time;
        TBuf<10> hour;
        TBuf<20> percent;
        TInt intPercent;
        while(iText.Read(iBuf) == KErrNone)
            {
                __L1("Read buf: %S",&iBuf);
                TInt posFound = iBuf.Find(KSeparator);
                if( posFound != KErrNotFound)
                    {
                        __L("Pos found!");
                        time = iBuf.Left(posFound);
                        percent = iBuf.Right(iBuf.Length()-(posFound+3));
                        __L2("time: %S, percent: %S",&time,&percent);
                        iLex.Assign(percent);
                        iLex.Val(intPercent);

                        hour = time.Left(2);
                        hour.Append(time.Right(2));
                        TimeFromString.Format(KTimeString,dtime.Year(),dtime.Month(),dtime.Day(),&hour);
                        __L1("TimeFromString: %S",&TimeFromString);
                        TTime test_time(TimeFromString);
                        __L3("DATE: %04d%02d%02d",test_time.DateTime().Year(),test_time.DateTime().Month()+1,test_time.DateTime().Day()+1);
                        __L3("TIME: %02d%02d%02d",test_time.DateTime().Hour(),test_time.DateTime().Minute(),test_time.DateTime().Second());
                        TTimeLightSettings settings;
                        settings.iTime = test_time;
                        settings.iLightLevel = intPercent;
                        iSettings.Append(settings);
                    }
            }
         iFile.Close();
    }
void CConfigurationManager::StartListening()
    {
        iFs.NotifyChange(ENotifyAll,iStatus,KBaseDirSettingsPath);
        SetActive();
    }
void CConfigurationManager::StopListening()
    {

    }
void CConfigurationManager::DoCancel()
    {

    }
void CConfigurationManager::RunL()
    {
        if(iStatus.Int() == KErrNone)
            {
                CDir* dir;
                iFs.GetDir(KBaseDirSettingsPath,KEntryAttNormal,ESortByName,dir);
                for(TInt i=0;i<dir->Count();i++)
                    {
                        if((*dir)[i].iName == _L("Exit"))
                        {
                            __LOGSTR("Find exit event, exiting....");
                            iFs.Delete(KFileExit);
                            CActiveScheduler::Stop();
                            User::Exit(KErrNone);
                        }
                    }
                iSettings.Reset();
                LoadSettings();
                iObserver->ConfigurationhasChanged(iSettings);
            }else{
                __L1("CConfigurationManager::RunL non zero iStatus: %d",iStatus.Int());
            }
    }

CConfigurationManager::CConfigurationManager() : CActive(EPriorityNormal)
    {

    }
CConfigurationManager::~CConfigurationManager()
    {
        Cancel();
        _CPOPD(&iFs);
    }
CConfigurationManager* CConfigurationManager::NewL()
    {
        CConfigurationManager* self = CConfigurationManager::NewLC();
        _CPOP(self);
        return self;
    }
CConfigurationManager* CConfigurationManager::NewLC()
    {
        CConfigurationManager* self = new (ELeave) CConfigurationManager();
        _CPUSH(self);
        self->ConstructL();
        return self;
    }
RTTimeSettings CConfigurationManager::GetSettings()
    {
        return iSettings;
    }
