/*
========================================================================
 Name        : UiSettingItemListView.h
 Author      : SQR
 Copyright   : Your copyright notice
 Description : 
========================================================================
*/
#ifndef UISETTINGITEMLISTVIEW_H
#define UISETTINGITEMLISTVIEW_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknview.h>
#include "UiSettingItemListSettings.h"
// ]]] end generated region [Generated Includes]


// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CUiSettingItemList;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Avkon view class for uiSettingItemListView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CuiSettingItemListView uiSettingItemListView.h
 */						
			
class CuiSettingItemListView : public CAknView
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CuiSettingItemListView();
	static CuiSettingItemListView* NewL();
	static CuiSettingItemListView* NewLC();        
	void ConstructL();
	virtual ~CuiSettingItemListView();
						
	// from base class CAknView
	TUid Id() const;
	void HandleCommandL( TInt aCommand );
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Public Section]
	
	
	// [[[ begin [Protected Section]
protected:
	// from base class CAknView
	void DoActivateL(
		const TVwsViewId& aPrevViewId,
		TUid aCustomMessageId,
		const TDesC8& aCustomMessage );
	void DoDeactivate();
	void HandleStatusPaneSizeChange();
	
	// [[[ begin generated region: do not modify [Overridden Methods]
	// ]]] end generated region [Overridden Methods]
	
	
	// [[[ begin [User Handlers]
	TBool HandleChangeSelectedSettingItemL( TInt aCommand );
	TBool HandleExitMenuItemSelectedL( TInt aCommand );
	// ]]] end [User Handlers]
	
	// ]]] end [Protected Section]
	
	
	// [[[ begin [Private Section]
private:
	void SetupStatusPaneL();
	void CleanupStatusPane();
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
	CUiSettingItemList* iUiSettingItemList;
	TUiSettingItemListSettings* iSettings;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Private Section]
	
	};

#endif // UISETTINGITEMLISTVIEW_H
