/*
 * play.h
 *
 *  Created on: 05.11.2010
 *      Author: vl
 */

#ifndef _PLAY_H_
#define _PLAY_H_
#include <mdaaudiosampleplayer.h>

class CmyPlay : public CBase, public MMdaAudioPlayerCallback
    {
public:
    ~CmyPlay();
    static CmyPlay* NewL();
    void Open(TDesC& aFIle);
    void  Stop();
    TInt MaxVolume();
    TBool iAllow;
    void SetVolume(TInt aVolume);
    TBool iNeedToSetVolume;
    TInt iNewVolume;
private:
    CMdaAudioPlayerUtility* iPlayer;
protected:
    CmyPlay();
    void ConstructL();
    virtual void MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds &aDuration);
    virtual void MapcPlayComplete(TInt aError);
private:
     enum TState{
     ENotReady,
     EReady,
     EPlaying
     };
     TState iState;
    };

#endif /* PLAY_H_ */
