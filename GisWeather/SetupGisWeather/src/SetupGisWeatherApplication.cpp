/*
========================================================================
 Name        : SetupGisWeatherApplication.cpp
 Author      : SQR
 Copyright   : Created SQR, 2010, Russia
 Description : 
========================================================================
*/

#include "SetupGisWeatherApplication.h"
#include "SetupGisWeatherDocument.h"
#ifdef EKA2
#include <eikstart.h>
#endif

/**
 * @brief Returns the application's UID (override from CApaApplication::AppDllUid())
 * @return UID for this application (KUidSetupGisWeatherApplication)
 */
TUid CSetupGisWeatherApplication::AppDllUid() const
	{
	return KUidSetupGisWeatherApplication;
	}

/**
 * @brief Creates the application's document (override from CApaApplication::CreateDocumentL())
 * @return Pointer to the created document object (CSetupGisWeatherDocument)
 */
CApaDocument* CSetupGisWeatherApplication::CreateDocumentL()
	{
	return CSetupGisWeatherDocument::NewL( *this );
	}

#ifdef EKA2

/**
 *	@brief Called by the application framework to construct the application object
 *  @return The application (CSetupGisWeatherApplication)
 */	
LOCAL_C CApaApplication* NewApplication()
	{
	return new CSetupGisWeatherApplication;
	}

/**
* @brief This standard export is the entry point for all Series 60 applications
* @return error code
 */	
GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication( NewApplication );
	}
	
#else 	// Series 60 2.x main DLL program code

/**
* @brief This standard export constructs the application object.
* @return The application (CSetupGisWeatherApplication)
*/
EXPORT_C CApaApplication* NewApplication()
	{
	return new CSetupGisWeatherApplication;
	}

/**
* @brief This standard export is the entry point for all Series 60 applications
* @return error code
*/
GLDEF_C TInt E32Dll(TDllReason /*reason*/)
	{
	return KErrNone;
	}

#endif // EKA2
