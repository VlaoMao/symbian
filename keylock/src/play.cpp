/*
 * play.cpp
 *
 *  Created on: 05.11.2010
 *      Author: vl
 */

#include "play.h"
#include "logger1.h"

CmyPlay::CmyPlay() : iNeedToSetVolume(EFalse),iNewVolume(0)
    {

    }
CmyPlay::~CmyPlay()
    {
    __LOGSTR("Destructor");
    }
void CmyPlay::ConstructL()
    {
 //   iPlayer=CMdaAudioPlayerUtility::NewFilePlayerL(aFile,*this);
    iPlayer = CMdaAudioPlayerUtility::NewL(*this);
    iAllow = ETrue;
    }
void CmyPlay::MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds &aDuration)
    {
    __LOGSTR("MapcInitComplete");
    iState = aError ? ENotReady : EReady;
    __LOGSTR1("after MapcInitComplete max vol: %d",iPlayer->MaxVolume());
    if(iNeedToSetVolume)
        {
            iPlayer->SetVolume(iNewVolume);
            iNeedToSetVolume = EFalse;
        }
    if(iAllow)
        iPlayer->Play();
    __LOGSTR1("iState: %d",iState);
    }
void CmyPlay::MapcPlayComplete(TInt aError)
    {
    __LOGSTR("MapsPlayComplete");
    iState = aError ? ENotReady : EReady;
    CActiveScheduler::Stop();
    }

void CmyPlay::Open(TDesC& aFile)
    {
    iPlayer->OpenFileL(aFile);
    __LOGSTR1("Open file: %S",&aFile);
    }
TInt CmyPlay::MaxVolume()
    {
    return iPlayer->MaxVolume();
    }
void CmyPlay::SetVolume(TInt aVolume)
    {
    //iPlayer->SetVolume(aVolume);
    iNeedToSetVolume = ETrue;
    iNewVolume = aVolume;
    }
CmyPlay* CmyPlay::NewL()
    {
    CmyPlay* self = new(ELeave) CmyPlay();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }
