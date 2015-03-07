/*
========================================================================
 Name        : LightManSetupDocument.cpp
 Author      : SQR
 Copyright   : 
 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated User Includes]
#include "LightManSetupDocument.h"
#include "LightManSetupAppUi.h"
// ]]] end generated region [Generated User Includes]

/**
 * @brief Constructs the document class for the application.
 * @param anApplication the application instance
 */
CLightManSetupDocument::CLightManSetupDocument( CEikApplication& anApplication )
	: CAknDocument( anApplication )
	{
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here.  
 */ 
void CLightManSetupDocument::ConstructL()
	{
	}
	
/**
 * Symbian OS two-phase constructor.
 *
 * Creates an instance of CLightManSetupDocument, constructs it, and
 * returns it.
 *
 * @param aApp the application instance
 * @return the new CLightManSetupDocument
 */
CLightManSetupDocument* CLightManSetupDocument::NewL( CEikApplication& aApp )
	{
	CLightManSetupDocument* self = new ( ELeave ) CLightManSetupDocument( aApp );
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * @brief Creates the application UI object for this document.
 * @return the new instance
 */	
CEikAppUi* CLightManSetupDocument::CreateAppUiL()
	{
	return new ( ELeave ) CLightManSetupAppUi;
	}
				
