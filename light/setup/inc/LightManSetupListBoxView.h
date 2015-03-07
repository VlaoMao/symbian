/*
========================================================================
 Name        : LightManSetupListBoxView.h
 Author      : SQR
 Copyright   : 
 Description : 
========================================================================
*/
#ifndef LIGHTMANSETUPLISTBOXVIEW_H
#define LIGHTMANSETUPLISTBOXVIEW_H

#include <aknview.h>
#include <aknmessagequerydialog.h>
#include <aknviewappui.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <barsread.h>
#include <stringloader.h>
#include <aknlists.h>
#include <eikenv.h>
#include <akniconarray.h>
#include <eikclbd.h>
#include <akncontext.h>
#include <akntitle.h>
#include <eikbtgpc.h>
#include <hal.h>
#include <hal_data.h>
#include <LightManSetup.rsg>
#include "LightManSetup.hrh"
#include "myform.h"
//#include "LightManSetupListBox.hrh"
#include "LightManSetupListBox.h"


_LIT(KBaseDirSettingsPath,"C:\\System\\Apps\\light\\");
_LIT(KBaseConfSettingsPath,"C:\\System\\Apps\\light\\set.ini");
_LIT(KFileExit,"C:\\System\\Apps\\light\\exit");
_LIT(KSeparator," - ");

class CLightManSetupListBox;

/**
 * Avkon view class for LightManSetupListBoxView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CLightManSetupListBoxView LightManSetupListBoxView.h
 */						
			
class CLightManSetupListBoxView : public CAknView
	{
	
	
public:
	// constructors and destructor
	CLightManSetupListBoxView();
	static CLightManSetupListBoxView* NewL();
	static CLightManSetupListBoxView* NewLC();        
	void ConstructL();
	virtual ~CLightManSetupListBoxView();
						
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	
	CLightManSetupListBox* CreateContainerL();	
protected:
	// from base class CAknView
	void DoActivateL(
		const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId,
		const TDesC8& aCustomMessage );
	void DoDeactivate();
	void HandleStatusPaneSizeChange();
	TBool HandleAddMenuItemSelectedL( TInt aCommand );
	TBool HandleChangeMenuItemSelectedL( TInt aCommand );
	TBool HandleDeleteMenuItemSelectedL( TInt aCommand );
	TBool HandleAboutMenuItemSelectedL( TInt aCommand );
	TBool HandleExitMenuItemSelectedL( TInt aCommand );
    TBool HandleSaveL( TInt aCommand );
    void TryRun();
private:
    void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);
	void SetupStatusPaneL();
	void CleanupStatusPane();
    void CheckForm();
	
	CLightManSetupListBox* iLightManSetupListBox;
    CMyForm* iNewForm;
	};

#endif // LIGHTMANSETUPLISTBOXVIEW_H
