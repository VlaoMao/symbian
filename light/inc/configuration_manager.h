#ifndef CONFIGURATION_MANAGER_H
#define CONFIGURATION_MANAGER_H

#include <e32base.h>
#include <f32file.h>
#include "logger1.h"

_LIT(KBaseDirSettingsPath,"C:\\System\\Apps\\light\\");
_LIT(KBaseConfSettingsPath,"C:\\System\\Apps\\light\\set.ini");
_LIT(KFileExit,"C:\\System\\Apps\\light\\exit");
_LIT(KSeparator," - ");
_LIT(KTimeString,"%04d%02d%02d:%S00.000000");

class TTimeLightSettings
    {
public:
    TTime iTime;
    TInt iLightLevel;
    TTime& GetTime(){return iTime;}
    };

typedef RArray<TTimeLightSettings> RTTimeSettings;

class MSettingsCallBack
    {
public:
    virtual void ConfigurationhasChanged(RTTimeSettings& aNewSettings) = 0;
    };


class CConfigurationManager : public CActive
    {
public:
    CConfigurationManager();
    ~CConfigurationManager();
    void SetObserver(MSettingsCallBack* aNewObserver);
    static CConfigurationManager* NewL();
    static CConfigurationManager* NewLC();
    RTTimeSettings GetSettings();
    void LoadSettings();
    void StartListening();
    void StopListening();
private:
    void ConstructL();
    void RunL();
    void DoCancel();
    TInt RunError(TInt aError){__L1("CConfigurationManager::RunError: %d",aError);return KErrNone;}
    MSettingsCallBack* iObserver;
    RTTimeSettings iSettings;
    RFs iFs;
    RFile iFile;
    TFileText iText;
    TBuf<256> iBuf;
    TLex iLex;
    };

#endif // CONFIGURATION_MANAGER_H
