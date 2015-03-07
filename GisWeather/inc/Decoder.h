/*
 * GisWeather : Decoder.h
 *
 *  Created on: 07.12.2010
 *  Author: vl
 */

#ifndef DECODER_H_
#define DECODER_H_
#include <e32base.h>
#include <fbs.h>
#include <imageconversion.h>
#include "Constants.h"
#include "logger1.h"

class CDecoder : public CActive
    {
public:
    CDecoder(TRect& aRect);
    ~CDecoder();
    static CDecoder* NewL(TRect& aRect);
    CFbsBitmap* iBitmap;
    CImageDecoder* iDecoder;
    RFs iFs;
    TFrameInfo iFrameInfo;
    TRect iRect;
    TBool iLoaded;
    void Convert();
private:
    virtual void RunL();
    virtual TInt RunError(TInt aError);
    virtual void DoCancel();
    void ConstructL();
   // CActiveSchedulerWait* iSchedWait;
    };

#endif /* DECODER_H_ */
