/*
========================================================================
 Name        : SetupGisWeatherAppUi.h
 Author      : SQR
 Copyright   : Created SQR, 2010, Russia
 Description : 
========================================================================
*/
#ifndef SETUPGISWEATHERAPPUI_H
#define SETUPGISWEATHERAPPUI_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknviewappui.h>
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class CSetupGisWeatherSettingItemListView;
// ]]] end generated region [Generated Forward Declarations]

/**
 * @class	CSetupGisWeatherAppUi SetupGisWeatherAppUi.h
 * @brief The AppUi class handles application-wide aspects of the user interface, including
 *        view management and the default menu, control pane, and status pane.
 */
class CSetupGisWeatherAppUi : public CAknViewAppUi
	{
public: 
	// constructor and destructor
	CSetupGisWeatherAppUi();
	virtual ~CSetupGisWeatherAppUi();
	void ConstructL();

public:
	// from CCoeAppUi
	TKeyResponse HandleKeyEventL(
				const TKeyEvent& aKeyEvent,
				TEventCode aType );

	// from CEikAppUi
	void HandleCommandL( TInt aCommand );
	void HandleResourceChangeL( TInt aType );

	// from CAknAppUi
	void HandleViewDeactivation( 
			const TVwsViewId& aViewIdToBeDeactivated, 
			const TVwsViewId& aNewlyActivatedViewId );

private:
	void InitializeContainersL();
	// [[[ begin generated region: do not modify [Generated Methods]
public: 
	// ]]] end generated region [Generated Methods]
	
	// [[[ begin generated region: do not modify [Generated Instance Variables]
private: 
	CSetupGisWeatherSettingItemListView* iSetupGisWeatherSettingItemListView;
	// ]]] end generated region [Generated Instance Variables]
	
	
	// [[[ begin [User Handlers]
protected: 
	// ]]] end [User Handlers]
	
	};

#endif // SETUPGISWEATHERAPPUI_H			
