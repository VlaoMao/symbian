/*
 * ============================================================================
 *  Name     : ClientApplication.cpp
 *  Part of  : HTTP Client Example
 *  Created  : 06/20/2006 by Forum Nokia
 *  Version  : 2.0
 *  Copyright: Forum Nokia
 * ============================================================================
 */

#include "ClientDocument.h"
#include "ClientApplication.h"

// UID for the application; this should correspond to the uid defined in
// the mmp file
#ifdef __SERIES60_3X__
  const TUid KUidClientApp = {0x20041D0D};
#else
  const TUid KUidClientApp = {0x20041D0D};
#endif

// ----------------------------------------------------------------------------
// CClientApplication::CreateDocumentL()
//
// Creates an Client document, and returns a pointer to it
// ----------------------------------------------------------------------------
CApaDocument* CClientApplication::CreateDocumentL()
	{
	return (static_cast<CApaDocument*>(CClientDocument::NewL(*this)));
	}
TFileName CClientApplication::ResourceFileName()
    {
    return TFileName();
    }
// ----------------------------------------------------------------------------
// CClientApplication::AppDllUid()
//
// Returns the UID for the Client application
// ----------------------------------------------------------------------------
TUid CClientApplication::AppDllUid() const
	{
    return KUidClientApp;
	}
	
// end of file
