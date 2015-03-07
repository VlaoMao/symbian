/*
========================================================================
 Name        : LightManSetupAppUi.h
 Author      : SQR
 Copyright   : 
 Description : 
========================================================================
*/
#ifndef LIGHTMANSETUPAPPUI_H
#define LIGHTMANSETUPAPPUI_H

#include <aknviewappui.h>
#include <eikmenub.h>
#include <akncontext.h>
#include <akntitle.h>
#include <LightManSetup.rsg>
//#include "LightManSetup.hrh"
#include "LightManSetupListBoxView.h"
class CLightManSetupListBoxView;

/**
 * @class	CLightManSetupAppUi LightManSetupAppUi.h
 * @brief The AppUi class handles application-wide aspects of the user interface, including
 *        view management and the default menu, control pane, and status pane.
 */
class CLightManSetupAppUi : public CAknViewAppUi
	{
public: 
	// constructor and destructor
	CLightManSetupAppUi();
	virtual ~CLightManSetupAppUi();
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
private: 
    CLightManSetupListBoxView* iLightManSetupListBoxView;
	};

#endif // LIGHTMANSETUPAPPUI_H			
