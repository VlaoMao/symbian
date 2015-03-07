#ifndef ACTIVE_H
#define ACTIVE_H

#include <hwrmlight.h>
#include <centralrepository.h>
#include "configuration_manager.h"
#include "light_change.h"
#include "timer_active.h"
#include "definitions.h"
#include "crash_handler.h"

class CLightWorker : public CActive, public MSettingsCallBack, public MLightTimeoutChanged, public MCTimerActiveCallBack
    {
public:
    CLightWorker();
    ~CLightWorker();
    static CLightWorker* NewL();
    static CLightWorker* NewLC();
    TDesC& ClassName(){return iClassName;}
private:
    TBuf<50> iClassName;
    void StartWork();
    void TimerExpired();
//    void Sort();
    void ConfigurationhasChanged(RTTimeSettings& aNewSettings);
    void LightTimeoutChanged(TInt &aNewValue);
    void ConstructL();
    void RunL();
    void DoCancel();
    TInt RunError(TInt aError){__L1("RunError: %d",aError);return KErrNone;}
    RTTimeSettings iTimeSettings;
    CHWRMLight* iLight;
    CLightChange* iLightChange;
    CConfigurationManager* iConfigurationManager;
    TInt iLightTimeout;
    CTimerActive* iTimerActive;
    TInt iWorkCount;
    TBool iDryRun;
    };

#endif // ACTIVE_H
