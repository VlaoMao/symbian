/*
========================================================================
 Name        : uiApplication.h
 Author      : SQR
 Copyright   : Your copyright notice
 Description : 
========================================================================
*/
#ifndef UIAPPLICATION_H
#define UIAPPLICATION_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <aknapp.h>
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Constants]
const TUid KUiduiApplication = { 0x20066b59 };
// ]]] end generated region [Generated Constants]

/**
 *
 * @class	CuiApplication uiApplication.h
 * @brief	A CAknApplication-derived class is required by the S60 application 
 *          framework. It is subclassed to create the application's document 
 *          object.
 */
class CuiApplication : public CAknApplication
	{
private:
	TUid AppDllUid() const;
	CApaDocument* CreateDocumentL();
	
	};
			
#endif // UIAPPLICATION_H		
