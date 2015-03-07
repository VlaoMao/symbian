/*
 * ============================================================================
 *  Name     : Client.cpp
 *  Part of  : HTTP Client Example
 *  Created  : 06/20/2006 by Forum Nokia
 *  Version  : 2.0
 *  Copyright: Forum Nokia
 * ============================================================================
 */

#ifdef __SERIES60_3X__
#include <eikstart.h>
#endif
#include "ClientApplication.h"

// ----------------------------------------------------------------------------
// NewApplication()
//
// Create an application, and return a pointer to it
// ----------------------------------------------------------------------------
EXPORT_C CApaApplication* NewApplication()
	{
	return (static_cast<CApaApplication*>(new CClientApplication));
	}

#ifdef __SERIES60_3X__
// ---------------------------------------------------------
// E32Main()
// Entry point function for new (>= 9.0) EPOC Apps (exe)
// Returns: Sistem Wide error codes or KErrNone if all goes well
// ---------------------------------------------------------
//
GLDEF_C TInt E32Main()
{
	return EikStart::RunApplication( NewApplication );
}
#else
// ---------------------------------------------------------
// E32Dll(TDllReason)
// Entry point function for EPOC Apps
// Returns: KErrNone: No error
// ---------------------------------------------------------
//
GLDEF_C TInt E32Dll( TDllReason )
{
    return KErrNone;
}
#endif

// end of file
