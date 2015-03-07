/*
 * GisWeather : Decoder.cpp
 *
 *  Created on: 07.12.2010
 *  Author: vl
 */

#include "Decoder.h"

CDecoder::CDecoder(TRect& aRect) : CActive(EPriorityStandard),iRect(aRect)
    {

    }
CDecoder::~CDecoder()
    {
    if(iDecoder)
	{
	CleanupStack::Pop(iDecoder);
	delete iDecoder;
	iDecoder = NULL;
	}
    if(iBitmap)
	{
	CleanupStack::Pop(iBitmap);
	delete iBitmap;
	iBitmap = NULL;
	}
    if(iSchedWait)
	{
	CleanupStack::Pop(iSchedWait);
	delete iSchedWait;
	iSchedWait = NULL;
	}
    iFs.Close();
    }
CDecoder* CDecoder::NewL(TRect& aRect)
    {
    CDecoder* self = new(ELeave) CDecoder(aRect);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

void CDecoder::ConstructL()
    {
    iLoaded = EFalse;
    CActiveScheduler::Add(this);
    iSchedWait = new(ELeave) CActiveSchedulerWait();
    CleanupStack::PushL(iSchedWait);
    iFs.Connect();
    iBitmap = new(ELeave) CFbsBitmap();
    CleanupStack::PushL(iBitmap);
    iDecoder = CImageDecoder::FileNewL(iFs,KFileName);
    CleanupStack::PushL(iDecoder);
    iFrameInfo = iDecoder->FrameInfo(0);
    iRect = iFrameInfo.iFrameCoordsInPixels;
    iBitmap->Create(iRect.Size(),EColor16M);
    iDecoder->Convert(&iStatus,*iBitmap,0);
    SetActive();
    iSchedWait->Start();
    }
void CDecoder::RunL()
    {
	if( iStatus == KErrUnderflow ) // continue converting
    {
    iDecoder->ContinueConvert( &iStatus );
    SetActive();
    }

	else if( iStatus == KErrNone )
	    {
		 // Nothing to do, we're done
	    iLoaded = ETrue;
	    }

    else // error
        {
        __LOGSTR1("Error while opening image:%d" , iStatus.Int()); // Error is my own error reporting function
        }

    // Stop blocking the Active Scheduler
	iSchedWait->AsyncStop();

	// Free up resources for next time.
	/*if(iDecoder)
		{
		delete iDecoder;
		iDecoder = NULL;
		}
	if(iSchedWait)
		{
		delete iSynchroniser;
		iSynchroniser = NULL;
		}*/

    }
TInt CDecoder::RunError(TInt aError)
    {
    return KErrNone;
    }
void CDecoder::DoCancel()
    {
    }
