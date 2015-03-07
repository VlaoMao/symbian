/*
========================================================================
 Name        : LightManSetupApplication.h
 Author      : SQR
 Copyright   : 
 Description : 
========================================================================
*/
#ifndef LIGHTMANSETUPAPPLICATION_H
#define LIGHTMANSETUPAPPLICATION_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknapp.h>
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Constants]
const TUid KUidLightManSetupApplication = { 0xE0918EC0 };
// ]]] end generated region [Generated Constants]

/**
 *
 * @class	CLightManSetupApplication LightManSetupApplication.h
 * @brief	A CAknApplication-derived class is required by the S60 application 
 *          framework. It is subclassed to create the application's document 
 *          object.
 */
class CLightManSetupApplication : public CAknApplication
	{
private:
	TUid AppDllUid() const;
	CApaDocument* CreateDocumentL();
	
	};
			
#endif // LIGHTMANSETUPAPPLICATION_H		
