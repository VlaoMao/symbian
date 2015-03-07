/*
* ==============================================================================
*  Name        : helloworldbasicappview.cpp
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
#include <coemain.h>
#include "helloworldbasicappview.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CHelloWorldBasicAppView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CHelloWorldBasicAppView* CHelloWorldBasicAppView::NewL( const TRect& aRect )
    {
    CHelloWorldBasicAppView* self = CHelloWorldBasicAppView::NewLC( aRect );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CHelloWorldBasicAppView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CHelloWorldBasicAppView* CHelloWorldBasicAppView::NewLC( const TRect& aRect )
    {
    CHelloWorldBasicAppView* self = new ( ELeave ) CHelloWorldBasicAppView;
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    return self;
    }

// -----------------------------------------------------------------------------
// CHelloWorldBasicAppView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CHelloWorldBasicAppView::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CHelloWorldBasicAppView::CHelloWorldBasicAppView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHelloWorldBasicAppView::CHelloWorldBasicAppView()
    {
    // No implementation required
    }


// -----------------------------------------------------------------------------
// CHelloWorldBasicAppView::~CHelloWorldBasicAppView()
// Destructor.
// -----------------------------------------------------------------------------
//
CHelloWorldBasicAppView::~CHelloWorldBasicAppView()
    {
    // No implementation required
    }


// -----------------------------------------------------------------------------
// CHelloWorldBasicAppView::Draw()
// Draws the display.
// -----------------------------------------------------------------------------
//
void CHelloWorldBasicAppView::Draw( const TRect& /*aRect*/ ) const
    {
    // Get the standard graphics context
    CWindowGc& gc = SystemGc();

    // Gets the control's extent
    TRect drawRect( Rect());

    // Clears the screen
    gc.Clear( drawRect );
    
  	}

// -----------------------------------------------------------------------------
// CHelloWorldBasicAppView::SizeChanged()
// Called by framework when the view size is changed.
// -----------------------------------------------------------------------------
//
void CHelloWorldBasicAppView::SizeChanged()
    {  
    DrawNow();
    }
// End of File

