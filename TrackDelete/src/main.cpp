/*
 *  TrackDelete
 *
 *  Created on: 03.11.2012
 *  Author: SQR
 */
#include <e32base.h>
#include "logger1.h"
#include "callback.h"
#include <mpxplaybackutility.h>
#include <mpxmediageneraldefs.h>
#include <mpxmediamusicdefs.h>
#include <aknglobalnote.h>

LOCAL_C void WorkL()
{
    __LOGSTR("Work");
    CCallBack *callback = CCallBack::NewL();
    MMPXPlaybackUtility *utility = MMPXPlaybackUtility::NewL(KPbModeActivePlayer,callback);
    MMPXSource *source = utility->Source();
    if(source)
    {
        HBufC *file = source->UriL();
        if(file)
        {
            __LOGSTR1("Trying delete file: %S",file);
            callback->setFileName(file);
            utility->CommandL(EPbCmdNext);
            CActiveScheduler::Start();
        }else{

        }
    }else{
        __LOGSTR("No media playing");
    }
    utility->RemoveObserverL(*callback);
    utility->Close();
}

LOCAL_C void SavePanic(TInt aError)
{
    __LOGSTR1("Panic: %d",aError);
}
GLDEF_C TInt E32Main()
{
    CActiveScheduler* shed = new(ELeave) CActiveScheduler();
    CActiveScheduler::Install(shed);
    __UHEAP_MARK;
    CTrapCleanup* cleanup = CTrapCleanup::New();
    TRAPD(error,WorkL());
    __ASSERT_ALWAYS(!error,SavePanic(error));
    delete cleanup;
    __UHEAP_MARKEND;
    delete shed;
    return KErrNone;
}
