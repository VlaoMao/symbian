/*
* ==============================================================================
*  Name        : helloworldbasicdocument.cpp
*  Part of     : Helloworldbasic
*  Interface   : 
*  Description : 
*  Version     : 
*
*  Copyright (c) 2005-2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation.
* ==============================================================================
*/

// INCLUDE FILES
#include "helloworldbasicappui.h"
#include "helloworldbasicdocument.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CHelloWorldBasicDocument::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CHelloWorldBasicDocument* CHelloWorldBasicDocument::NewL( CEikApplication&
                                                          aApp )
    {
    CHelloWorldBasicDocument* self = NewLC( aApp );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHelloWorldBasicDocument::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CHelloWorldBasicDocument* CHelloWorldBasicDocument::NewLC( CEikApplication&
                                                           aApp )
    {
    CHelloWorldBasicDocument* self =
        new ( ELeave ) CHelloWorldBasicDocument( aApp );

    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CHelloWorldBasicDocument::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHelloWorldBasicDocument::ConstructL()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CHelloWorldBasicDocument::CHelloWorldBasicDocument()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHelloWorldBasicDocument::CHelloWorldBasicDocument( CEikApplication& aApp )
    : CAknDocument( aApp )
    {
    // No implementation required
    }

// ---------------------------------------------------------------------------
// CHelloWorldBasicDocument::~CHelloWorldBasicDocument()
// Destructor.
// ---------------------------------------------------------------------------
//
CHelloWorldBasicDocument::~CHelloWorldBasicDocument()
    {
    // No implementation required
    }

// ---------------------------------------------------------------------------
// CHelloWorldBasicDocument::CreateAppUiL()
// Constructs CreateAppUi.
// ---------------------------------------------------------------------------
//
CEikAppUi* CHelloWorldBasicDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it;
    // the framework takes ownership of this object
    return ( static_cast <CEikAppUi*> ( new ( ELeave )
                                        CHelloWorldBasicAppUi ) );
    }

// End of File

