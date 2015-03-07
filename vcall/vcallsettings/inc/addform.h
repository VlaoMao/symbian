#ifndef ADDFORM_H
#define ADDFORM_H

#include <eikenv.h>
#include <barsread.h>
#include <eikedwin.h>
#include <aknform.h>
#include <avkon.hrh>
#include <avkon.rsg>
#include <eikmenup.h>
#include <eikmfne.h>
#include <aknslider.h>
#include "vcallsettingsListBox.hrh"
#include "vcallsettings.rsg"
#include <stringloader.h>
// Derive the class from CAknForm

class CAddForm : public CAknForm
    {
    public:
        static CAddForm* NewL();
        virtual ~CAddForm();
        CAddForm();

    public:
        TInt ExecuteLD( TInt aResourceId );
        TBool iIsDef;

        void PrepareLC( TInt aResourceId );
        void LoadFormValuesFromDataL();
        void LoadValuesDef();
        TBool OkToExitL(TInt aButtonId);
    private:
        void ConstructL();

    private:
        void PreLayoutDynInitL();
        void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);
        void DoNotSaveFormDataL();
 };
#endif // ADDFORM_H
