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
#include "LightManSetupListBox.hrh"
#include "LightManSetup.rsg"
#include <stringloader.h>
// Derive the class from CAknForm

class CMyForm : public CAknForm
    {
    public:
        static CMyForm* NewL();
        virtual ~CMyForm();
        CMyForm();

    public:
        /**
        * From CAknForm, ExecuteLD
        * @return CAknForm::ExecuteLD return value
        * @param aResourceId resource ID
        */
        TInt ExecuteLD( TInt aResourceId );
        TDesC& GetTime();
        TInt& GetLevel();
        TDesC GetNote();
        void SetTime(TDesC& aNewTime);
        void SetLevel(TInt aLevel);
        void SetNote(TDes& aNote);
        void SetIsDef(TBool aDef);
        void SetLevel(TDesC& aNewLevel);
        TBool iIsDef;

        /**
        * From CAknForm, PrepareLC
        * @param aResourceId resource ID
        */
        void PrepareLC( TInt aResourceId );
        void LoadFormValuesFromDataL();
        void LoadValuesDef();
        TBool OkToExitL(TInt aButtonId);
    private:  // Constructor
        void ConstructL();
        TBuf<50> iTimeBuf;
        TInt iLevel;
        TBuf<51> iNote;
        TBuf<51> iDefNote;

    private:  // Functions from base class
        /**
        * From CEikDialog, PostLayoutDynInitL
        * Set default field value to member data.
        */
        void PreLayoutDynInitL();
        void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);

        /**
        * From CAknForm, DoNotSaveFormDataL
        * Does not save the contents of the form.
        */
        void DoNotSaveFormDataL();

    private:
        /**
        * For holding controls value
        */
        TBuf<128> iDataName;
 };

#endif // FORM_H
