/*
========================================================================
 Name        : SetupGisWeatherAppUi.cpp
 Author      : SQR
 Copyright   : Created SQR, 2010, Russia
 Description : 
========================================================================
*/

#include <eikmenub.h>
#include <akncontext.h>
#include <akntitle.h>
#include <SetupGisWeather.rsg>


#include "SetupGisWeatherAppUi.h"
#include "SetupGisWeatherSettingItemList.hrh"
#include "SetupGisWeather.hrh"
#include "SetupGisWeatherSettingItemListView.h"

/**
 * Construct the CSetupGisWeatherAppUi instance
 */ 
CSetupGisWeatherAppUi::CSetupGisWeatherAppUi()
	{
	
	}

/** 
 * The appui's destructor removes the container from the control
 * stack and destroys it.
 */
CSetupGisWeatherAppUi::~CSetupGisWeatherAppUi()
	{
	
	}

void CSetupGisWeatherAppUi::InitializeContainersL()
	{
	iSetupGisWeatherSettingItemListView = CSetupGisWeatherSettingItemListView::NewL();
	AddViewL( iSetupGisWeatherSettingItemListView );
	SetDefaultViewL( *iSetupGisWeatherSettingItemListView );
	}

/**
 * Handle a command for this appui (override)
 * @param aCommand command id to be handled
 */
void CSetupGisWeatherAppUi::HandleCommandL( TInt aCommand )
	{
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{ // code to dispatch to the AppUi's menu and CBA commands is generated here
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
		if ( aCommand == EAknSoftkeyExit || aCommand == EEikCmdExit )
			{
			Exit();
			}
		}
	}

/** 
 * Override of the HandleResourceChangeL virtual function
 */
void CSetupGisWeatherAppUi::HandleResourceChangeL( TInt aType )
	{
	CAknViewAppUi::HandleResourceChangeL( aType );
	}
				
/** 
 * Override of the HandleKeyEventL virtual function
 * @return EKeyWasConsumed if event was handled, EKeyWasNotConsumed if not
 * @param aKeyEvent 
 * @param aType 
 */
TKeyResponse CSetupGisWeatherAppUi::HandleKeyEventL(
		const TKeyEvent& aKeyEvent,
		TEventCode aType )
	{
	
	return EKeyWasNotConsumed;
	}

/** 
 * Override of the HandleViewDeactivation virtual function
 *
 * @param aViewIdToBeDeactivated 
 * @param aNewlyActivatedViewId 
 */
void CSetupGisWeatherAppUi::HandleViewDeactivation( 
		const TVwsViewId& aViewIdToBeDeactivated, 
		const TVwsViewId& aNewlyActivatedViewId )
	{
	CAknViewAppUi::HandleViewDeactivation( 
			aViewIdToBeDeactivated, 
			aNewlyActivatedViewId );
	
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here. 
 */ 
void CSetupGisWeatherAppUi::ConstructL()
	{
	BaseConstructL( EAknEnableSkin ); 
	InitializeContainersL();
	}

