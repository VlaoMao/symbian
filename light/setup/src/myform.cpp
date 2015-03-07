#include "myform.h"
/**
* Symbian OS 2 phase constructor.
* Constructs the CMyForm  using the NewLC method, popping
* the constructed object from the CleanupStack before returning it.
*
* @return The newly constructed CMyForm
*/

CMyForm * CMyForm ::NewL()
    {
    CMyForm * self = new (ELeave) CMyForm ();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }
CMyForm::CMyForm() : iTimeBuf(KNullDesC),iLevel(50),iNote(KNullDesC),iDefNote(KNullDesC),iIsDef(ETrue)
    {

    }
CMyForm::~CMyForm()
    {

    }

void CMyForm::ConstructL()
    {
        CAknForm::ConstructL();
    }

/**
* Called by the framework whenver the 'Save' menu item is selected, and by the
* QuerySaveChangesL method when the user answers yes to the save query.
* Saves the data from the forms controls.
* @return TBool ETrue if the form data has been saved, EFalse otherwise.
*/

TBool CMyForm::OkToExitL(TInt /*aButtonId*/)
    {
        CEikTimeEditor* time_ed = (CEikTimeEditor*)Control(EmyformDlgCIdEdwin);
        TTime time = time_ed->Time();
        iTimeBuf.Format(_L("%02d:%02d"),time.DateTime().Hour(),time.DateTime().Minute());
        CAknSlider* slider = (CAknSlider*)Control(EmyformDlgCIdEdwin2);
        iLevel = slider->Value();
        //CEikEdwin* text_ed = (CEikEdwin*)Control(EmyformDlgCIdEdwin3);
        //text_ed->GetText(iNote);
        return ETrue;
    }

/**
* Called by QuerySaveChangeL when the user chooses to discard changes made to
* the form. Loads the form values from iOpponent
*/

void CMyForm ::DoNotSaveFormDataL()
    {
    //LoadFormValuesFromDataL();
    }


/**
* Called by the framework before the form is initialised
* Loads the form values from iOpponent ready for execution of the form
*/

void CMyForm ::PreLayoutDynInitL()
    {
    CAknForm::PreLayoutDynInitL();
    LoadFormValuesFromDataL();
    }

/**
* Called by the framework when a menu is displayed.
* Removes the default items from the options menu of the form for editing a
* fields label, adding a field and deleting a field
*/

void CMyForm::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
    {
    CAknForm::DynInitMenuPaneL(aResourceId,aMenuPane);
    }

void CMyForm::LoadFormValuesFromDataL()
    {
        if(iIsDef)
            {
            CEikTimeEditor* time_ed = (CEikTimeEditor*)Control(EmyformDlgCIdEdwin);
            TTime time;
            time.HomeTime();
            time_ed->SetTime(time);
            CAknSlider* slider = (CAknSlider*)Control(EmyformDlgCIdEdwin2);
            slider->SetValueL(iLevel);
            if(iDefNote.Length() == 0)
                {
                CEikonEnv* eikonEnv = CEikonEnv::Static();
                HBufC* buf = StringLoader::LoadL(R_NOTE_TITLE_VAL,eikonEnv);
                iDefNote.Copy(*buf);
                delete buf;
                }
            //CEikEdwin* text_ed = (CEikEdwin*)Control(EmyformDlgCIdEdwin3);
            //text_ed->SetTextL(&iDefNote);
            }else{
                CEikTimeEditor* time_ed = (CEikTimeEditor*)Control(EmyformDlgCIdEdwin);
                TTime time;
                time.HomeTime();
                TDateTime dtime = time.DateTime();
                TBuf<50> buftime;
                buftime.Format(_L("%04d%02d%02d:%S00.000000"),dtime.Year(),dtime.Month(),dtime.Day(),&iTimeBuf);
                //iEikonEnv->InfoWinL(_L("BUF:"),buftime);
                TTime timeFromString(buftime);
                time_ed->SetTime(timeFromString);
                CAknSlider* slider = (CAknSlider*)Control(EmyformDlgCIdEdwin2);
                slider->SetValueL(iLevel);
                //CEikEdwin* text_ed = (CEikEdwin*)Control(EmyformDlgCIdEdwin3);
                //text_ed->SetTextL(&iNote);
            }
    }
TInt CMyForm::ExecuteLD(TInt aResourceId)
    {
        return CAknForm::ExecuteLD(aResourceId);
    }
void CMyForm::PrepareLC(TInt aResourceId)
    {
        CAknForm::PrepareLC(aResourceId);
    }
TDesC& CMyForm::GetTime()
    {
        return iTimeBuf;
    }

TInt& CMyForm::GetLevel()
    {
        return iLevel;
    }

TDesC CMyForm::GetNote()
    {
        return ((iNote == iDefNote) ? KNullDesC() : iNote);
    }
void CMyForm::SetTime(TDesC &aNewTime)
    {
        TInt pos = aNewTime.Find(_L(":"));
        if( pos != KErrNotFound)
            {
                iTimeBuf.Zero();
                iTimeBuf.Append(aNewTime.Left(pos));
                iTimeBuf.Append(aNewTime.Right(aNewTime.Length() - pos - 1));
            }else{
                iTimeBuf = aNewTime;
            }
    }
void CMyForm::SetLevel(TInt aLevel)
    {
        iLevel = aLevel;
    }
void CMyForm::SetLevel(TDesC& aNewLevel)
    {
        TLex lex;
        lex.Assign(aNewLevel);
        lex.Val(iLevel);
    }

void CMyForm::SetNote(TDes &aNote)
    {
        iNote = aNote;
    }
void CMyForm::SetIsDef(TBool aDef)
    {
        iIsDef = aDef;
    }
