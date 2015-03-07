#ifndef ACCEL_H
#define ACCEL_H

#include <e32base.h>
#include <sensrvchannel.h>
#include <sensrvpropertylistener.h>
#include <sensrvdatalistener.h>
#include <sensrvchannelinfo.h>
#include <sensrvtypes.h>
#include <sensrvchannelfinder.h>
#include <sensrvaccelerometersensor.h>
#include <sensrvtappingsensor.h>/*KSensrvChannelTypeIdAccelerometerDoubleTappingData*/
#include "logger1.h"
#include "connector.h"

class CAccel : public CBase, public MSensrvDataListener
    {
public:
    static CAccel* NewL();
    static CAccel* NewLC();
    CAccel();
    ~CAccel();
    virtual void DataReceived( CSensrvChannel& aChannel,
                               TInt aCount,
                               TInt aDataLost );
    virtual void DataError( CSensrvChannel& aChannel,
                            TSensrvErrorSeverity aError );
    /*
      В доках написано, что оложено на будущее, реализацию можно оставить пустой
    */
    virtual void GetDataListenerInterfaceL( TUid aInterfaceUid, TAny*& aInterface );
    void StartMonitor();
    void StopMonitor();
    void SetObserver(MConnector* aNewConnector);
private:
    TInt x;
    TInt y;
    TInt z;
    TBool iAccelPersist;
    void ConstructL();
    CSensrvChannel* iSensrvChannel;
    MConnector* iConnector;
    };

#endif // ACCEL_H
