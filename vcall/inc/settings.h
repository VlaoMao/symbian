#ifndef SETTINGS_H
#define SETTINGS_H

#include <e32base.h>
#include <f32file.h>
#include "callchange.h"
#include "timer.h"
#include "logger1.h"

class CSettings : public CBase, public MActiveCallListener
{
public:
    static CSettings* NewL();
    static CSettings* NewLC();
    CSettings();
    ~CSettings();
private:
    void ConstructL();
    void CallConnected();
    void CallDisconnected();
    CVTimer* iTimer;
    RArray<TInt> iTimes;
};

#endif // SETTINGS_H
