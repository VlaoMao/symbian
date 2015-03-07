#ifndef FORM_H
#define FORM_H

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

class CMyForm : public CAknForm
    {
    public:
        static CMyForm* NewL();
        virtual ~CMyForm();
        CMyForm();

    public:
        TInt ExecuteLD( TInt aResourceId );
        TInt GetDelay();
        TInt GetDuration();
        TInt GetIntensity();
        void SetDelay(TInt);
        void SetDuration(TInt);
        void SetIntensity(TInt);
        void SetIsDef(TBool aDef);
        TBool iIsDef;

        void PrepareLC( TInt aResourceId );
        void LoadFormValuesFromDataL();
        void LoadValuesDef();
        TBool OkToExitL(TInt aButtonId);
    private:
        void ConstructL();
        TInt iDelay;
        TInt iDuration;
        TInt iIntensity;

    private:
        void PreLayoutDynInitL();
        void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);
        void DoNotSaveFormDataL();
 };

#endif // FORM_H
