/*
========================================================================
 Name        : vcallsettingsApplication.h
 Author      : SQR
 Copyright   : 
 Description : 
========================================================================
*/
#ifndef VCALLSETTINGSAPPLICATION_H
#define VCALLSETTINGSAPPLICATION_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknapp.h>
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Constants]
const TUid KUidvcallsettingsApplication = { 0xEB21BC3C };
// ]]] end generated region [Generated Constants]

/**
 *
 * @class	CvcallsettingsApplication vcallsettingsApplication.h
 * @brief	A CAknApplication-derived class is required by the S60 application 
 *          framework. It is subclassed to create the application's document 
 *          object.
 */
class CvcallsettingsApplication : public CAknApplication
	{
private:
	TUid AppDllUid() const;
	CApaDocument* CreateDocumentL();
	
	};
			
#endif // VCALLSETTINGSAPPLICATION_H		
