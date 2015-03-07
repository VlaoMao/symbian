/*
========================================================================
 Name        : SetupGisWeatherSettingItemListView.h
 Author      : SQR
 Copyright   : Created SQR, 2010, Russia
 Description : 
========================================================================
*/
#ifndef SETUPGISWEATHERSETTINGITEMLISTVIEW_H
#define SETUPGISWEATHERSETTINGITEMLISTVIEW_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <apgcli.h>
#include <apacmdln.h>
#include <aknview.h>
#include <aknnotewrappers.h>


#include "SetupGisWeatherSettingItemListSettings.h"

//#include "CListboxContainer.h"
// ]]] end generated region [Generated Includes]


// [[[ begin [Event Handler Includes]
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CSetupGisWeatherSettingItemList;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Avkon view class for SetupGisWeatherSettingItemListView. It is register with the view server
 * by the AppUi. It owns the container control.
 * @class	CSetupGisWeatherSettingItemListView SetupGisWeatherSettingItemListView.h
 */						
			
class CSetupGisWeatherSettingItemListView : public CAknView
	{
	
	
	// [[[ begin [Public Section]
public:
	// constructors and destructor
	CSetupGisWeatherSettingItemListView();
	static CSetupGisWeatherSettingItemListView* NewL();
	static CSetupGisWeatherSettingItemListView* NewLC();        
	void ConstructL();
	virtual ~CSetupGisWeatherSettingItemListView();
						
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
	TBool Handle_MenuItemSelectedL( TInt aCommand );
	TBool Handle_MenuItem4SelectedL( TInt aCommand );
	TBool Handle_MenuItem2SelectedL( TInt aCommand );
	TBool Handle_MenuItem3SelectedL( TInt aCommand );
	TBool Handle_MenuItem5SelectedL( TInt aCommand );
	TBool Handle_MenuItem1SelectedL( TInt aCommand );
	// ]]] end [User Handlers]
	
	// ]]] end [Protected Section]
	
	
	// [[[ begin [Private Section]
private:
	void SetupStatusPaneL();
	void CleanupStatusPane();
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
	CSetupGisWeatherSettingItemList* iSetupGisWeatherSettingItemList;
	TSetupGisWeatherSettingItemListSettings* iSettings;
	// ]]] end generated region [Generated Instance Variables]
	
	// [[[ begin generated region: do not modify [Generated Methods]
	// ]]] end generated region [Generated Methods]
	
	// ]]] end [Private Section]
	
	enum TListQuery1Images
		{
		// [[[ begin generated region: do not modify [Generated Enums]
		// ]]] end generated region [Generated Enums]
		
		};
	};

#endif // SETUPGISWEATHERSETTINGITEMLISTVIEW_H
