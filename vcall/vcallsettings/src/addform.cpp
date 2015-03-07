#include "addform.h"
/**
* Symbian OS 2 phase constructor.
* Constructs the CAddForm  using the NewLC method, popping
* the constructed object from the CleanupStack before returning it.
*
* @return The newly constructed CAddForm
*/

CAddForm * CAddForm ::NewL()
    {
    CAddForm * self = new (ELeave) CAddForm ();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }
CAddForm::CAddForm() : iIsDef(ETrue)
    {

    }
CAddForm::~CAddForm()
    {

    }

void CAddForm::ConstructL()
    {
        CAknForm::ConstructL();
    }

/**
* Called by the framework whenver the 'Save' menu item is selected, and by the
* QuerySaveChangesL method when the user answers yes to the save query.
* Saves the data from the forms controls.
* @return TBool ETrue if the form data has been saved, EFalse otherwise.
*/

TBool CAddForm::OkToExitL(TInt /*aButtonId*/)
    {
        return ETrue;
    }

/**
* Called by QuerySaveChangeL when the user chooses to discard changes made to
* the form. Loads the form values from iOpponent
*/

void CAddForm ::DoNotSaveFormDataL()
    {
    //LoadFormValuesFromDataL();
    }


/**
* Called by the framework before the form is initialised
* Loads the form values from iOpponent ready for execution of the form
*/

void CAddForm ::PreLayoutDynInitL()
    {
    CAknForm::PreLayoutDynInitL();
    LoadFormValuesFromDataL();
    }

/**
* Called by the framework when a menu is displayed.
* Removes the default items from the options menu of the form for editing a
* fields label, adding a field and deleting a field
*/

void CAddForm::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
    {
    CAknForm::DynInitMenuPaneL(aResourceId,aMenuPane);
    }

void CAddForm::LoadFormValuesFromDataL()
    {
        if(iIsDef)
            {
            }else{
        }
    }
TInt CAddForm::ExecuteLD(TInt aResourceId)
    {
        return CAknForm::ExecuteLD(aResourceId);
    }
void CAddForm::PrepareLC(TInt aResourceId)
    {
        CAknForm::PrepareLC(aResourceId);
    }
