#include "active.h"
CLightWorker::CLightWorker() : CActive(EPriorityNormal),iWorkCount(0),iDryRun(EFalse),iClassName(_L("CLightWorker"))
    {

    }
CLightWorker::~CLightWorker()
    {
        Cancel();
        if(iLight != 0)
            {
                _CPOPD(iLight);
            }
    }
void CLightWorker::ConstructL()
    {
        __L("CLightWorker::ConstructL");
        __CH__();
        iLight = CHWRMLight::NewLC();
        iLightChange = CLightChange::NewLC(LightUID,LightTimeoutKey);
        iTimerActive = CTimerActive::NewL();
        iTimerActive->SetObserver(this);
        iConfigurationManager = CConfigurationManager::NewLC();
        iConfigurationManager->SetObserver(this);
        iConfigurationManager->LoadSettings();
        iTimeSettings = iConfigurationManager->GetSettings();
        TInt settingsCount = iTimeSettings.Count();
        __L1("iTimeSettings count: %d",settingsCount);
        if(settingsCount == 0)
            User::Panic(_L("NO JOBS"),KErrNotFound);
        //Sort();
        iLightChange->SetObserver(this);
        iLightChange->StartListeningL();
        iConfigurationManager->StartListening();
        StartWork();
    }
void CLightWorker::StartWork()
    {
        __L("CLightWorker::StartWork start");

        if(iTimeSettings.Count() == 0)
            return ;
        TTime currentTime;
        TTime workTime = ((TTimeLightSettings)iTimeSettings.operator [](iWorkCount)).iTime;
        currentTime.HomeTime();
        if(workTime > currentTime)
            {
                //all good, starting timer
                __L3("Start timer at date: %04d%02d%02d",workTime.DateTime().Year(),workTime.DateTime().Month()+1,workTime.DateTime().Day()+1);
                __L3("Start timer at time: %02d%02d%02d",workTime.DateTime().Hour(),workTime.DateTime().Minute(),workTime.DateTime().Second());
                iTimerActive->At(workTime);
            }else{
                //need to set day + 1
                __L("time to work less than current time, day + 1");
                /*TDateTime ttime = workTime.DateTime();
                ttime.Set(
                            ttime.Year(),
                            ttime.Month(),
                            ttime.Day()+1,
                            ttime.Hour(),
                            ttime.Minute(),
                            ttime.Second(),
                            ttime.MicroSecond());*/
                TTime time = ((TTimeLightSettings)iTimeSettings.operator [](iWorkCount)).GetTime();
                TTimeIntervalDays days(1);
                time += days;
                iTimeSettings.operator [](iWorkCount).iTime = time;
                //ok, day + 1 is set
                //iTimerActive->At(((TTimeLightSettings)iTimeSettings.operator [](iWorkCount)).iTime);
                iDryRun = ETrue;
                TimerExpired();
            }
        /*if(iWorkCount >= iTimeSettings.Count())
            {
                iWorkCount = 0;
                iConfigurationManager->LoadSettings();
                iTimeSettings = iConfigurationManager->GetSettings();
            }
        TTime time;
        time.HomeTime();
        TTime workTime = ((TTimeLightSettings)iTimeSettings.operator [](iWorkCount)).iTime;
        if(workTime > time)
            {
                iTimerActive->At(workTime);
            }else{
                TDateTime ttime = workTime.DateTime();
                ((TTimeLightSettings)iTimeSettings.operator [](iWorkCount)).iTime.DateTime().Set(ttime.Year(),ttime.Month(),ttime.Day()+1,ttime.Hour(),ttime.Minute(),ttime.Second(),ttime.MicroSecond());
                ++iWorkCount;
                StartWork();
            }*/
        __L("CLightWorker::StartWork end");
        //__L1("LIGHT timeout: %d",iLightChange->GetLightTimeout());
    }

/*void CLightWorker::Sort()
    {
        TInt count = iTimeSettings.Count();
        if(count == 1)
            return;

        for(TInt i = 0; i < (count - 1); ++i)
            {
                TTimeLightSettings arr_i = iTimeSettings.operator [](i);
                TTimeLightSettings arr_i_1 = iTimeSettings.operator [](i+1);
                if(((TTimeLightSettings)arr_i_1).iTime < ((TTimeLightSettings)arr_i).iTime)
                    {
                        iTimeSettings.Insert(arr_i_1,i);
                        iTimeSettings.Insert(arr_i,i+1);
                    }
            }
        for(TInt j = 0; j < count; ++j)
            {
                __L1("STEP: %d",j);
            TTime test_time = ((TTimeLightSettings)iTimeSettings.operator [](j)).iTime;
            __L3("DATE: %04d%02d%02d",test_time.DateTime().Year(),test_time.DateTime().Month()+1,test_time.DateTime().Day()+1);
            __L3("TIME: %02d%02d%02d",test_time.DateTime().Hour(),test_time.DateTime().Minute(),test_time.DateTime().Second());
            }
    }
*/
void CLightWorker::LightTimeoutChanged(TInt &aNewValue)
    {
        iLightTimeout = aNewValue;
        __L1("CLightWorker::LightTimeoutHasChanged, new value: %d",aNewValue);
        iLightChange->StartListeningL();
    }
void CLightWorker::TimerExpired()
    {
        __L("Timer expired!");
        if(!iDryRun)
            {
                __L("DRYRUN");
                TInt lightLevel = ((TTimeLightSettings)iTimeSettings.operator [](iWorkCount)).iLightLevel;
                __L2("Setting light level to: %d,status: %d",lightLevel,iLightChange->SetUIDKey(LightLevelKey,lightLevel));
            //iLight->LightOnL();
            }
        iDryRun = EFalse;
        ++iWorkCount;
        if(iWorkCount >= iTimeSettings.Count())
            {
            iWorkCount = 0;
            //iConfigurationManager->LoadSettings();
            //iTimeSettings = iConfigurationManager->GetSettings();
            }
        StartWork();
    }

void CLightWorker::RunL()
    {

    }

void CLightWorker::DoCancel()
    {
        iConfigurationManager->Cancel();
    }
void CLightWorker::ConfigurationhasChanged(RTTimeSettings &aNewSettings)
    {
        if(aNewSettings.Count() != 0)
            {
                aNewSettings = aNewSettings;
                iWorkCount = 0;
                iTimerActive->Clear();
                StartWork();
                iConfigurationManager->StartListening();
            }else{
                //no entries!
                User::Panic(_L("NO ENTRIES!"),KErrNotFound);
            }
    }
CLightWorker* CLightWorker::NewL()
    {
        CLightWorker* self = CLightWorker::NewLC();
        _CPOP(self);
        return self;
    }
CLightWorker* CLightWorker::NewLC()
    {
        CLightWorker* self = new (ELeave) CLightWorker();
        _CPUSH(self);
        self->ConstructL();
        return self;
    }

