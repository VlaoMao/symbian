/*
========================================================================
 Name        : vcallsettingsDocument.cpp
 Author      : SQR
 Copyright   : 
 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated User Includes]
#include "vcallsettingsDocument.h"
#include "vcallsettingsAppUi.h"
// ]]] end generated region [Generated User Includes]

/**
 * @brief Constructs the document class for the application.
 * @param anApplication the application instance
 */
CvcallsettingsDocument::CvcallsettingsDocument( CEikApplication& anApplication )
	: CAknDocument( anApplication )
	{
	}

/**
 * @brief Completes the second phase of Symbian object construction. 
 * Put initialization code that could leave here.  
 */ 
void CvcallsettingsDocument::ConstructL()
	{
	}
	
/**
 * Symbian OS two-phase constructor.
 *
 * Creates an instance of CvcallsettingsDocument, constructs it, and
 * returns it.
 *
 * @param aApp the application instance
 * @return the new CvcallsettingsDocument
 */
CvcallsettingsDocument* CvcallsettingsDocument::NewL( CEikApplication& aApp )
	{
	CvcallsettingsDocument* self = new ( ELeave ) CvcallsettingsDocument( aApp );
	CleanupStack::PushL( self );
	self->ConstructL();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * @brief Creates the application UI object for this document.
 * @return the new instance
 */	
CEikAppUi* CvcallsettingsDocument::CreateAppUiL()
	{
	return new ( ELeave ) CvcallsettingsAppUi;
	}
				
