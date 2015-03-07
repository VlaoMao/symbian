/*
 * ============================================================================
 *  Name     : CClientAppView of ClientAppView.cpp
 *  Part of  : HTTP Client Example
 *  Created  : 06/20/2006 by Forum Nokia
 *  Version  : 2.0
 *  Copyright: Forum Nokia
 * ============================================================================
 */

#include <coemain.h>
#include <eikenv.h>
#include <gdi.h>
#include <txtrich.h>
#include "Client.pan"
#include "ClientAppView.h"
#include "ClientEngine.h"

// Constants for CEikRichTextEditors
const TInt KNumberOfControls = 2;
const TInt KNumberOfLines = 0;
const TInt KTextLimit = 128;

const TInt KSizeOffset = 4;

// Background color
#define KBackgroundColor	TRgb(128, 128, 128)

// ----------------------------------------------------------------------------
// CClientAppView::NewL()
//
// Creates instance of CClientAppView.
// ----------------------------------------------------------------------------
CClientAppView* CClientAppView::NewL(const TRect& aRect)
	{
    CClientAppView* self = CClientAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
	}

// ----------------------------------------------------------------------------
// CClientAppView::NewLC()
//
// Creates instance of CClientAppView.
// ----------------------------------------------------------------------------
CClientAppView* CClientAppView::NewLC(const TRect& aRect)
	{
    CClientAppView* self = new (ELeave) CClientAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
	}

// ----------------------------------------------------------------------------
// CClientAppView::CClientAppView()
//
// First phase construction.
// ----------------------------------------------------------------------------
CClientAppView::CClientAppView()
	{
	}

// ----------------------------------------------------------------------------
// CClientAppView::~CClientAppView()
//
// Destructor.
// ----------------------------------------------------------------------------
CClientAppView::~CClientAppView()
	{
	delete iOutputWindow;
	delete iStatusWindow;
	iFile.Close();
	}

// ----------------------------------------------------------------------------
// CClientAppView::ConstructL()
//
// Second phase construction.
// ----------------------------------------------------------------------------
void CClientAppView::ConstructL(const TRect& aRect)
	{
    // Create a window for this application view
    CreateWindowL();

	// Create output window
	iOutputWindow = new (ELeave) CEikRichTextEditor();
	iOutputWindow->SetContainerWindowL(*this);
	iOutputWindow->ConstructL(this, KNumberOfLines, KTextLimit,
		EEikEdwinReadOnly, EGulFontControlAll, EGulNoSymbolFonts);

	// Create status window
	iStatusWindow = new (ELeave) CEikRichTextEditor();
	iStatusWindow->SetContainerWindowL(*this);
	iStatusWindow->ConstructL(this, KNumberOfLines, KTextLimit,
		EEikEdwinReadOnly|EEikEdwinNoWrap,
		EGulFontControlAll, EGulNoSymbolFonts);

	iStatusWindow->SetFocus(ETrue);

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    iFile.Replace(iEikonEnv->Static()->FsSession(),_L("C:\\System\\informer.temp"),EFileWrite);
	}

void CClientAppView::SizeChanged()
	{
	/*TRect r = Rect();
	TPoint upperEditPosition = TPoint(2,2);
	TInt upperEditHeight = r.Height()*3/4 - KSizeOffset;
	iOutputWindow->SetExtent(upperEditPosition,
		TSize(r.Width() - KSizeOffset, upperEditHeight));
	upperEditPosition.iY += upperEditHeight + 2;
	upperEditHeight = r.Height()/4 - KSizeOffset;
	iStatusWindow->SetExtent(upperEditPosition,
		TSize(r.Width() - KSizeOffset, upperEditHeight));*/
	}

// ----------------------------------------------------------------------------
// CClientAppView::Draw()
//
// Draw this application's view to the screen
// ----------------------------------------------------------------------------
void CClientAppView::Draw(const TRect& aRect) const
	{
    CWindowGc& gc = SystemGc();

    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KBackgroundColor );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( aRect );
	}

// ----------------------------------------------------------------------------
// CClientAppView::CountComponentControls()
//
// Returns number of controls in this compound control.
// ----------------------------------------------------------------------------
TInt CClientAppView::CountComponentControls() const
	{
    return KNumberOfControls;
	}

// ----------------------------------------------------------------------------
// CClientAppView::ComponentControl()
//
// Returns pointer to control with index aIndex.
// ----------------------------------------------------------------------------
CCoeControl* CClientAppView::ComponentControl(TInt aIndex) const
	{
    switch(aIndex)
		{
		case 0:
			return iOutputWindow;
		case 1:
			return iStatusWindow;
		default:
			Panic(EClientView);
			return 0;
		}
	}

// ----------------------------------------------------------------------------
// CClientAppView::HandleControlEventL()
//
// Handles control events.
// ----------------------------------------------------------------------------
void CClientAppView::HandleControlEventL(CCoeControl* /* aControl */,
											 TCoeEvent /* aEventType */ )
	{
	}

// ----------------------------------------------------------------------------
// CClientAppView::ResetL()
//
// Resets contents of output and status window.
// ----------------------------------------------------------------------------
void CClientAppView::ResetL()
	{
    iOutputWindow->Text()->Reset();
    iOutputWindow->HandleTextChangedL();
    iOutputWindow->SetCursorPosL(0, EFalse);
	}

// ----------------------------------------------------------------------------
// CClientAppView::OfferKeyEventL()
//
// Handles key events.
// ----------------------------------------------------------------------------
TKeyResponse CClientAppView::OfferKeyEventL(const TKeyEvent& aKeyEvent,
												TEventCode aType)
	{
	// Catch EStdKeyNkp5 and EStdKeyDevice3; they are used here to switch
	// the active CEikRichTextEditor.
	/*if(aType == EEventKey)
		{
		switch(aKeyEvent.iScanCode)
			{
			case EStdKeyNkp5:
			case EStdKeyDevice3:
				if (iOutputWindow->IsFocused())
					{
					iOutputWindow->SetFocus(EFalse);
					iStatusWindow->SetFocus(ETrue);
					} 
				else 
					{
					iStatusWindow->SetFocus(EFalse);
					iOutputWindow->SetFocus(ETrue);
					}
				return EKeyWasConsumed;
			}
		}

	// Redirect keyevents to controls
    if (iOutputWindow)
		{
	    if (iOutputWindow->IsFocused())
			return iOutputWindow->OfferKeyEventL(aKeyEvent, aType);
		}

    if (iStatusWindow)
		{
	    if (iStatusWindow->IsFocused())
			return iStatusWindow->OfferKeyEventL(aKeyEvent, aType);
		}*/

    return EKeyWasNotConsumed;
	}

// ----------------------------------------------------------------------------
// CClientAppView::AddToStatusWindowL()
//
// Add a single line of text to the status window.
// ----------------------------------------------------------------------------
void CClientAppView::AddToStatusWindowL(const TDesC& aText)
	{
	// Append aText to status window with line break
	CRichText* text = iStatusWindow->RichText();
	text->InsertL(text->DocumentLength(), aText);
	text->InsertL(text->DocumentLength(), CEditableText::ELineBreak);
	iStatusWindow->HandleTextChangedL();
	iStatusWindow->MoveCursorL(TCursorPosition::EFLineDown, EFalse);
	}

// ----------------------------------------------------------------------------
// CClientAppView::AddToOutputWindowL()
//
// Add text to outputwindow. No formatting is provided.
// ----------------------------------------------------------------------------
void CClientAppView::AddToOutputWindowL(const TDesC8& aText)
	{
	// Convert 8-bit aText to 16-bit and append it to end of output window
	HBufC* tempBuf = HBufC::NewL(aText.Length());
	CleanupStack::PushL(tempBuf);
	tempBuf->Des().Copy(aText);
	CRichText* text = iOutputWindow->RichText();
	text->InsertL(text->DocumentLength(), *tempBuf);
	iOutputWindow->HandleTextChangedL();

	CleanupStack::PopAndDestroy(); // tempBuf
	}

// ----------------------------------------------------------------------------
// CClientAppView::ClientEvent()
//
// Called by CClientEngine to notify events to user
// ----------------------------------------------------------------------------
void CClientAppView::ClientEvent(const TDesC& aEventDescription)
	{
    __LOGSTR1("aEventDescription: %S",&aEventDescription);
	if(aEventDescription == _L("Transaction Successful"))
	    {
	    iFile.Close();
	    CFileMan* manager = CFileMan::NewL(iEikonEnv->FsSession());
	    manager->Move(_L("C:\\System\\informer.temp"),_L("C:\\System\\apps\\GisWeather\\informer.gif"),CFileMan::EOverWrite);
	    manager->Delete(_L("C:\\System\\apps\\GisWeather\\time"));
	    iFile.Create(iEikonEnv->FsSession(),_L("C:\\System\\apps\\GisWeather\\time"),EFileWrite);
	    iFile.Close();
	    RProcess proc;
	    proc.Create(_L("GisWeather.exe"),KNullDesC);
	    proc.Resume();
	    proc.Close();
	    User::Exit(KErrNone);
	    }
	//TRAPD(err, AddToStatusWindowL(aEventDescription));
	//if(err)
	//	Panic(EClientView);
	}

// ----------------------------------------------------------------------------
// CClientAppView::ClientBodyReceived()
//
// Called by CClientEngine when part of response body received
// ----------------------------------------------------------------------------
void CClientAppView::ClientBodyReceived(const TDesC8& aBodyData)
	{
	iFile.Write(aBodyData);
	//TRAPD(err, AddToOutputWindowL(aBodyData));
	//if(err)
	//	Panic(EClientView);
	}

// end of file
