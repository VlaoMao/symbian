#include "light_change.h"

CLightChange::~CLightChange()
    {
        iHandler->Cancel();
        if(iRepository)
            {
                _CPOPD(iRepository);
            }
    }
void CLightChange::ConstructL()
    {
        iRepository = CRepository::NewLC(TUid::Uid(iUid));
        iHandler = CCenRepNotifyHandler::NewL(*this,*iRepository,CCenRepNotifyHandler::EIntKey,0x6);
        //
        //GetLightTimeout();
        //
    }

void CLightChange::StartListeningL()
    {
        iHandler->Cancel();
        iHandler->StartListeningL();
    }
void CLightChange::StopListening()
    {
        iHandler->Cancel();
    }
void CLightChange::SetObserver(MLightTimeoutChanged *aNewObserver)
    {
        if(aNewObserver != NULL)
            iObserver = aNewObserver;
    }
TInt& CLightChange::GetLightTimeout()
    {
        //CRepository* cenrep = CRepository::NewLC(TUid::Uid(iUid));
        User::LeaveIfError(iRepository->Get(iKey,iLightTimeout));
        //_CPOPD(cenrep);
        return iLightTimeout;
    }
TInt CLightChange::SetUIDKey(TUint32 aKey, TInt aNewValue)
    {
        TInt err = iRepository->Set(aKey,aNewValue);
        return err;
    }

CLightChange* CLightChange::NewL(TUint32 aUid,TUint32 aKey)
    {
        CLightChange* self = CLightChange::NewLC(aUid,aKey);
        _CPOP(self);
        return self;
    }
CLightChange* CLightChange::NewLC(TUint32 aUid,TUint32 aKey)
    {
        CLightChange* self = new (ELeave) CLightChange(aUid,aKey);
        _CPUSH(self);
        self->ConstructL();
        return self;
    }
void  	CLightChange::HandleNotifyInt (TUint32 aId, TInt aNewValue)
    {
        __L2("CLightChange::HandleNotifyInt: aId: %u,value: %d",aId,aNewValue);
        if(aId == iKey)
            {
                iObserver->LightTimeoutChanged(aNewValue);
            }
    }

void  	CLightChange::HandleNotifyReal (TUint32 aId, TReal aNewValue)
    {
        __L("CLightChange::HandleNotifyReal");
    }

void  	CLightChange::HandleNotifyString (TUint32 aId, const TDesC16 &aNewValue)
    {
        __L("CLightChange::HandleNotifyString");
    }

void  	CLightChange::HandleNotifyBinary (TUint32 aId, const TDesC8 &aNewValue)
    {
        __L("CLightChange::HandleNotifyBinary");
    }

void  	CLightChange::HandleNotifyGeneric (TUint32 aId)
    {
        __L("CLightChange::HandleNotifyGeneric");
    }

void  	CLightChange::HandleNotifyError (TUint32 aId, TInt aError, CCenRepNotifyHandler *aHandler)
    {
        __L("CLightChange::HandleNotifyError");
    }
