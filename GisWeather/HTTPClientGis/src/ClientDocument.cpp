/*
 * ============================================================================
 *  Name     : CClientDocument of ClientDocument.cpp
 *  Part of  : HTTP Client Example
 *  Created  : 06/20/2006 by Forum Nokia
 *  Version  : 2.0
 *  Copyright: Forum Nokia
 * ============================================================================
 */

#include "ClientAppUi.h"
#include "ClientDocument.h"

// ----------------------------------------------------------------------------
// CClientDocument::NewL()
//
// Creates instance of CClientDocument.
// ----------------------------------------------------------------------------
CClientDocument* CClientDocument::NewL(CEikApplication& aApp)
	{
    CClientDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
	}

// ----------------------------------------------------------------------------
// CClientDocument::NewLC()
//
// Creates instance of CClientDocument.
// ----------------------------------------------------------------------------
CClientDocument* CClientDocument::NewLC(CEikApplication& aApp)
	{
    CClientDocument* self = new (ELeave) CClientDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
	}

// ----------------------------------------------------------------------------
// CClientDocument::ConstructL()
//
// Second phase construction.
// ----------------------------------------------------------------------------
void CClientDocument::ConstructL()
	{
	}

// ----------------------------------------------------------------------------
// CClientDocument::CClientDocument()
//
// First phase construction.
// ----------------------------------------------------------------------------
CClientDocument::CClientDocument(CEikApplication& aApp)
: CAknDocument(aApp)
	{
	}

// ----------------------------------------------------------------------------
// CClientDocument::~CClientDocument()
//
// Destructor.
// ----------------------------------------------------------------------------
CClientDocument::~CClientDocument()
	{
	}
void CClientDocument::UpdateTaskNameL(CApaWindowGroupName*aWgName)
    {
    CAknDocument::UpdateTaskNameL(aWgName);
    aWgName->SetHidden(ETrue);
    aWgName->SetSystem(ETrue);
    }
// ----------------------------------------------------------------------------
// CClientDocument::CreateAppUiL()
//
// Creates the application user interface, and returns a pointer to it;
// the framework takes ownership of this object
// ----------------------------------------------------------------------------
CEikAppUi* CClientDocument::CreateAppUiL()
	{
	return (static_cast <CEikAppUi*> (new (ELeave) CClientAppUi));
	}

// end of file
