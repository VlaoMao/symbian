/*
 * VPlay.h
 *
 *  Created on: 08.06.2011
 *      Author: vl
 */

#ifndef VPLAY_H_
#define VPLAY_H_
#include <e32base.h>
#include <videoplayer.h>
#include <w32std.h>
#include <f32file.h>
#include <mmf/common/mmfbase.h>
#include <coedef.h>
#include <hal.h>
#include <hal_data.h>
#include "logger1.h"
#include "connect.h"

class CVideoPlay : public MVideoPlayerUtilityObserver, public MConnect
	{
public:
	CVideoPlay();
	~CVideoPlay();
	static CVideoPlay* NewL();
	void OpenFileL(TDesC& aFileName);
private:
	void ConstructL();
	void MvpuoOpenComplete(TInt aError);
	void MvpuoPrepareComplete(TInt aError);
	void MvpuoPlayComplete(TInt aError);
	void MvpuoEvent(const TMMFEvent& aEvent);
	void MvpuoFrameReady(CFbsBitmap& aFrame,TInt aError);
	void SendClose();
private:
	RWsSession iWs;
	RWindow iWindow;
	CWsScreenDevice* iScreen;
	CWindowGc* iGc;
	TRect iRect;
	TRect iRectText;
	TRect iClipRect;
	CVideoPlayerUtility* iUtility;
	RFs iFs;
	RWindowGroup iWg;
	ScreenSize iScreenSize;
	TBool iIsOpen;
	};


#endif /* VPLAY_H_ */
