#ifndef LIGHT_CHANGE_H
#define LIGHT_CHANGE_H
#include <e32base.h>
#include <centralrepository.h>
#include <cenrepnotifyhandler.h>
#include "logger1.h"

class MLightTimeoutChanged
    {
public:
    virtual void LightTimeoutChanged(TInt& aNewValue) = 0;
    };

class CLightChange : public MCenRepNotifyHandlerCallback
    {
public:
    static CLightChange* NewL(TUint32 aUid,TUint32 aKey);
    static CLightChange* NewLC(TUint32 aUid,TUint32 aKey);
    CLightChange(TUint32 aUid,TUint32 aKey) : iUid(aUid),iKey(aKey){}
    ~CLightChange();
    void StartListeningL();
    void StopListening();
    TInt& GetLightTimeout();
    void SetObserver(MLightTimeoutChanged* aNewObserver);
    TInt SetUIDKey(TUint32 aKey,TInt aNewValue);
private:
    void  	HandleNotifyInt (TUint32 aId, TInt aNewValue);
    void  	HandleNotifyReal (TUint32 aId, TReal aNewValue);
    void  	HandleNotifyString (TUint32 aId, const TDesC16 &aNewValue);
    void  	HandleNotifyBinary (TUint32 aId, const TDesC8 &aNewValue);
    void  	HandleNotifyGeneric (TUint32 aId);
    void  	HandleNotifyError (TUint32 aId, TInt aError, CCenRepNotifyHandler *aHandler);
private:
    void ConstructL();
    MLightTimeoutChanged* iObserver;
    CRepository* iRepository;
    CCenRepNotifyHandler* iHandler;
    TInt iLightTimeout;
    TUint32 iUid;
    TUint32 iKey;
    };

#endif // LIGHT_CHANGE_H
