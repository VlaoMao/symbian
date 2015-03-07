/*
 * ============================================================================
 *  Name     : CClientAppView of ClientAppView.h
 *  Part of  : HTTP Client Example
 *  Created  : 06/26/2006 by Forum Nokia
 *  Version  : 2.0
 *  Copyright: Forum Nokia
 * ============================================================================
 */

#ifndef __CLIENT_APPVIEW_H__
#define __CLIENT_APPVIEW_H__

#include <coecntrl.h>
#include <eikrted.h>
#include "ClientEngine.h"
#include "logger1.h"

/*
*
* Applications' view. Contains two CEikRichTextEditors for displaying received
* data and status events.
*
*/
class CClientAppView :	public CCoeControl,
								public MCoeControlObserver,
								public MClientObserver
    {
public:
	/*
	* NewL()
	*
	* Create a CClientEngine object.
	*
	* Params:
	*		aRect: Extents of the view.
	*
	* Returns:
	* 		A pointer to the created instance of CClientAppView
	*
	*/
	static CClientAppView* NewL(const TRect& aRect);
	RFile iFile;
	/*
	* NewLC()
	*
	* Create a CClientEngine object.
	*
	* Params:
	*		aRect: Extents of the view.
	*
	* Returns:
	* 		A pointer to the created instance of CClientAppView
	*
	*/
	static CClientAppView* NewLC(const TRect& aRect);

	/*
	* ~CClientAppView()
	*
	* Destructor of CClientAppView.
	*
	* Params:
	*		-
	*
	* Returns:
	*		-
	*
	*/
	~CClientAppView();

	/*
	* ResetL()
	*
	* Resets contents of the view; clears CEikRichTextEditors.
	*
	* Params:
	*		-
	*
	* Returns:
	*		-
	*
	*/
	void ResetL();

/*
* From CCoeControl
*/
public:
	/*
	* Draw()
	*
	* Draws the view.
	*
	* Params:
	*		aRect:
	*
	* Returns:
	* 		-
	*
	*/
    void Draw(const TRect& aRect) const;

/*
* From MCoeControlObserver
*/
private:
	/*
	* CountComponentControls()
	*
	* Gets the number of controls contained in this compound control.
	*
	* Params:
	*		-
	*
	* Returns:
	* 		Number of controls.
	*
	*/
	TInt CountComponentControls() const;

	/*
	* ComponentControl()
	*
	* Gets the specified component of a compound control.
	*
	* Params:
	*		aIndex:
	*
	* Returns:
	* 		Pointer to control with index aIndex.
	*
	*/
	CCoeControl* ComponentControl(TInt aIndex) const;

	/*
	* OfferKeyEventL()
	*
	* Handles key events passed to this control (view).
	*
	* Params:
	*		aKeyEvent: The key event.
	*		aType:	The type of key event: EEventKey, EEventKeyUp or
	*				EEventKeyDown.
	*
	* Returns:
	* 		-
	*
	*/
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

	/*
	* HandleControlEventL()
	*
	* Handles control events.
	*
	* Params:
	*		aControl: Control
	*		aEventType: Event type
	*
	* Returns:
	* 		-
	*
	*/
	void HandleControlEventL(	CCoeControl* /* aControl */,
		TCoeEvent /* aEventType */ );

/*
* From MClientObserver (see ClientEngine.h)
*/
public:
	void ClientEvent(const TDesC& aEventDescription);
	void ClientBodyReceived(const TDesC8& aBodyData);

private:
	/*
	* ConstructL()
	*
	* Perform the second phase construction of a CClientAppView object.
	*
	* Params:
	*		aRect: Extents of the view.
	*
	* Returns:
	* 		-
	*
	*/
    void ConstructL(const TRect& aRect);

	/*
	* CClientAppView()
	*
	* Perform the first phase of two phase construction.
	*
	* Params:
	*		-
	*
	* Returns:
	* 		-
	*
	*/
    CClientAppView();

	/*
	* AddToOutputWindowL()
	*
	* Adds given text to output window (CEikRichTextEditor, iOutputWindow)
	* Does not format the added text.
	*
	* Params:
	*		aText: Text to be added.
	*
	* Returns:
	* 		-
	*
	*/
	void AddToOutputWindowL(const TDesC8& aText);

	/*
	* AddToStatusWindowL()
	*
	* Adds given text to status window (CEikRichTextEditor, iStatusWindow)
	*
	* Params:
	*		aText: A single line of text to be added.
	*
	* Returns:
	* 		-
	*
	*/
	void AddToStatusWindowL(const TDesC& aText);

	void SizeChanged();

private:
	CEikRichTextEditor*	iOutputWindow;
	CEikRichTextEditor* iStatusWindow;
};


#endif // __CLIENT_APPVIEW_H__
