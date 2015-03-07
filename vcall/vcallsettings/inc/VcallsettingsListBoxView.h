/*
========================================================================
 Name        : VcallsettingsListBoxView.h
 Author      : SQR
 Copyright   : 
 Description : 
========================================================================
*/
#ifndef VCALLSETTINGSLISTBOXVIEW_H
#define VCALLSETTINGSLISTBOXVIEW_H

#include <aknview.h>
#include <hal.h>
#include <hal_data.h>
#include <aknmessagequerydialog.h>
#include "addform.h"
class CVcallsettingsListBox;

/**
 * Avkon view class for vcallsettingsListBoxView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CvcallsettingsListBoxView vcallsettingsListBoxView.h
 */						
			
class CvcallsettingsListBoxView : public CAknView
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CvcallsettingsListBoxView();
	static CvcallsettingsListBoxView* NewL();
	static CvcallsettingsListBoxView* NewLC();        
	void ConstructL();
	virtual ~CvcallsettingsListBoxView();
						
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	
	CVcallsettingsListBox* CreateContainerL();
protected:
	// from base class CAknView
	void DoActivateL(
		const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId,
		const TDesC8& aCustomMessage );
	void DoDeactivate();
	void HandleStatusPaneSizeChange();
    TBool Handle_ExitSelected(TInt aCommand );
    TBool Handle_AddSelected( TInt aCommand );
    TBool Handle_SettingsSelected( TInt aCommand );
    TBool Handle_AboutSelected( TInt aCommand );
    TBool Handle_DeleteSelected( TInt aCommand );
private:
	void SetupStatusPaneL();
	void CleanupStatusPane();
	
	CVcallsettingsListBox* iVcallsettingsListBox;
	
	};

#endif // VCALLSETTINGSLISTBOXVIEW_H
