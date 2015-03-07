#include "callback.h"

CCallBack *CCallBack::NewL()
{
    CCallBack *self = new (ELeave) CCallBack();
    return self;
}

CCallBack::CCallBack() : isReceived(EFalse),isSkipped(EFalse)
{

}

void CCallBack::HandlePropertyL(TMPXPlaybackProperty aProperty, TInt aValue, TInt aError)
{
    __LOGSTR("CCallBack::HandlePropertyL");
}

void CCallBack::HandleSubPlayerNamesL(TUid aPlayer, const MDesCArray *aSubPlayers, TBool aComplete, TInt aError)
{
    __LOGSTR("CCallBack::HandleSubPlayerNamesL");
}

void CCallBack::HandleMediaL(const CMPXMedia &aProperties, TInt aError)
{
    __LOGSTR("CCallBack::HandleMediaL");
}

void CCallBack::HandlePlaybackCommandComplete(CMPXCommand *aCommandResult, TInt aError)
{
    __LOGSTR("CCallBack::HandlePlaybackCommandComplete");
}

void CCallBack::HandlePlaybackMessage(CMPXMessage* aMessage, TInt aErr)
{
    __LOGSTR("CCallBack::HandlePlaybackMessage(CMPXMessage*,TInt)");
    TMPXMessageId id(aMessage->ValueTObjectL<TMPXMessageId>(KMPXMessageGeneralId));
    if (KMPXMessageGeneral == id)
    {
        TInt event(aMessage->ValueTObjectL<TInt>(KMPXMessageGeneralEvent));
        __LOGSTR1("Event: %d",event);
        switch (event)
        {
        case TMPXPlaybackMessage::ECommandReceived:
        {
            __LOGSTR("Command received");
            isReceived = ETrue;
            break;
        }
        case TMPXPlaybackMessage::ESkipEnd:
        {
            if(isReceived)
            {
                isSkipped = ETrue;
            }
            break;
        }
        case TMPXPlaybackMessage::EMediaChanged:
        {
            if(isReceived && isSkipped)
            {
                isReceived = EFalse;
                isSkipped = EFalse;
                TParse parse;
                parse.Set(*iFileName,0,0);
                RFs fs;
                User::LeaveIfError(fs.Connect());
                TInt deleteRes = fs.Delete(*iFileName);
                CAknGlobalNote *note = CAknGlobalNote::NewLC();
                TInt noteId;
                if(deleteRes == KErrNone)
                {
                    TBuf<256> buf;
                    buf.Format(_L("Файл %S успешно удалён"),&parse.NameAndExt());
                    noteId = note->ShowNoteL(EAknGlobalInformationNote,buf);
                    User::After(3000000);
                    note->CancelNoteL(noteId);
                }else{
                    TBuf<256> buf;
                    buf.Format(_L("Файл %S не удалён. Код ошибки: %d"),&parse.NameAndExt(),deleteRes);
                    noteId = note->ShowNoteL(EAknGlobalErrorNote,buf);
                    User::After(3000000);
                    note->CancelNoteL(noteId);
                }
                CleanupStack::PopAndDestroy(note);
                CActiveScheduler::Stop();
            }
            break;
        }
        default:
        {
            break;
        }
        }
    }
}

void CCallBack::setFileName(HBufC *aNewFileName)
{
    iFileName = aNewFileName;
}
