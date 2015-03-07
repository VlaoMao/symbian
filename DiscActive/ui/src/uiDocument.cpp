/*
========================================================================
 Name        : uiDocument.cpp
 Author      : SQR
 Copyright   : Your copyright notice
 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated User Includes]
#include "uiDocument.h"
#include "uiAppUi.h"
// ]]] end generated region [Generated User Includes]

/**
 * @brief Constructs the document class for the application.
 * @param anApplication the application instance
 */
CuiDocument::CuiDocument( CEikApplication& anApplication )
	: CAknDocument( anApplication )
	{
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here.  
 */ 
void CuiDocument::ConstructL()
	{
	}
	
/**
 * Symbian OS two-phase constructor.
 *
 * Creates an instance of CuiDocument, constructs it, and
 * returns it.
 *
 * @param aApp the application instance
 * @return the new CuiDocument
 */
CuiDocument* CuiDocument::NewL( CEikApplication& aApp )
	{
	CuiDocument* self = new ( ELeave ) CuiDocument( aApp );
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * @brief Creates the application UI object for this document.
 * @return the new instance
 */	
CEikAppUi* CuiDocument::CreateAppUiL()
	{
	return new ( ELeave ) CuiAppUi;
	}
				
