#ifndef CALLBACK_H
#define CALLBACK_H

#include <mpxplaybackobserver.h>
#include <mpxplaybackmessage.h>
#include <mpxmessagegeneraldefs.h>
#include <aknglobalnote.h>
#include "logger1.h"

class CCallBack : public CBase, public MMPXPlaybackCallback, public MMPXPlaybackObserver
{
public:
    static CCallBack *NewL();
    void setFileName(HBufC *aNewFileName);
protected:
    CCallBack();
    virtual void HandlePropertyL(TMPXPlaybackProperty aProperty,
                                 TInt aValue,
                                 TInt aError);
    virtual void HandleSubPlayerNamesL(TUid aPlayer,
                                       const MDesCArray* aSubPlayers,
                                       TBool aComplete,
                                       TInt aError);
    virtual void HandleMediaL(const CMPXMedia& aProperties,
                              TInt aError);
    virtual void HandlePlaybackCommandComplete(CMPXCommand* aCommandResult,
                                               TInt aError);
    virtual void HandlePlaybackMessage(CMPXMessage* aMessage, TInt aErr);
private:
    HBufC *iFileName;
    TBool isReceived;
    TBool isSkipped;
};

#endif // CALLBACK_H
