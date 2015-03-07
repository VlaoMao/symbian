/*
========================================================================
 Name        : SetupGisWeatherDocument.cpp
 Author      : SQR
 Copyright   : Created SQR, 2010, Russia
 Description : 
========================================================================
*/
#include "SetupGisWeatherDocument.h"
#include "SetupGisWeatherAppUi.h"

/**
 * @brief Constructs the document class for the application.
 * @param anApplication the application instance
 */
CSetupGisWeatherDocument::CSetupGisWeatherDocument( CEikApplication& anApplication )
	: CAknDocument( anApplication )
	{
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here.  
 */ 
void CSetupGisWeatherDocument::ConstructL()
	{
	}
	
/**
 * Symbian OS two-phase constructor.
 *
 * Creates an instance of CSetupGisWeatherDocument, constructs it, and
 * returns it.
 *
 * @param aApp the application instance
 * @return the new CSetupGisWeatherDocument
 */
CSetupGisWeatherDocument* CSetupGisWeatherDocument::NewL( CEikApplication& aApp )
	{
	CSetupGisWeatherDocument* self = new ( ELeave ) CSetupGisWeatherDocument( aApp );
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * @brief Creates the application UI object for this document.
 * @return the new instance
 */	
CEikAppUi* CSetupGisWeatherDocument::CreateAppUiL()
	{
	return new ( ELeave ) CSetupGisWeatherAppUi;
	}
				
