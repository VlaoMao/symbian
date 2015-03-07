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
CMyForm::CMyForm() : iIsDef(ETrue),iDelay(0),iDuration(0),iIntensity(0)
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
        CEikNumberEditor* delayEd =
                (CEikNumberEditor*) Control( EmyformDlgCIdEdwin);
        CEikNumberEditor* durationEd =
                (CEikNumberEditor*) Control( EmyformDlgCIdEdwin2);
        CAknSlider* intensity = (CAknSlider*)Control(EmyformDlgCIdEdwin3);
        iDelay = delayEd->Number();
        iDuration = durationEd->Number();
        iIntensity = intensity->Value();

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
            CEikNumberEditor* delayEd =
                        (CEikNumberEditor*) Control( EmyformDlgCIdEdwin);
            CEikNumberEditor* durationEd =
                        (CEikNumberEditor*) Control( EmyformDlgCIdEdwin2);
            CAknSlider* slider = (CAknSlider*)Control(EmyformDlgCIdEdwin3);
            slider->SetValueL(iIntensity);
            }else{
                CEikNumberEditor* delayEd =
                        (CEikNumberEditor*) Control( EmyformDlgCIdEdwin);
                CEikNumberEditor* durationEd =
                        (CEikNumberEditor*) Control( EmyformDlgCIdEdwin2);
                CAknSlider* slider = (CAknSlider*)Control(EmyformDlgCIdEdwin3);
                slider->SetValueL(iIntensity);
                delayEd->SetNumber(iDelay);
                durationEd->SetNumber(iDuration);
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
TInt CMyForm::GetDuration()
    {
        return iDuration;
    }

TInt CMyForm::GetIntensity()
    {
        return iIntensity;
    }

TInt CMyForm::GetDelay()
    {
        return iDelay;
    }
void CMyForm::SetDuration(TInt aNewDuration)
    {
        iDuration = aNewDuration;
    }
void CMyForm::SetDelay(TInt aNewDelay)
    {
        iDelay = aNewDelay;
    }
void CMyForm::SetIntensity(TInt aNewIntensity)
    {
        iIntensity = aNewIntensity;
    }
void CMyForm::SetIsDef(TBool aDef)
    {
        iIsDef = aDef;
    }
