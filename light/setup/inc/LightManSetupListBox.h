/*
========================================================================
 Name        : LightManSetupListBox.h
 Author      : SQR
 Copyright   : 
 Description : 
========================================================================
*/
#ifndef LIGHTMANSETUPLISTBOX_H
#define LIGHTMANSETUPLISTBOX_H

// [[[ begin generated region: do not modify [Generated Includes]
#include <coecntrl.h>		
// ]]] end generated region [Generated Includes]


// [[[ begin [Event Handler Includes]
#include <eiklbo.h>
#include <aknconsts.h>
#include <eiklbv.h>
#include <aknviewappui.h>
#include <aknlists.h>
#include <aknsfld.h>
#include <akniconarray.h>
#include <aknconsts.h>
#include <avkon.mbg>
#include <gulicon.h>  
#include <eikclbd.h>
#include <barsread.h>
#include <stringloader.h>
#include <aknlists.h>
#include <eikenv.h>
#include <akniconarray.h>
#include <eikclbd.h>
#include <aknviewappui.h>
#include <eikappui.h>
#include <aknglobalnote.h>
#include <LightManSetup.rsg>

#include "LightManSetupListBoxView.h"
// ]]] end [Event Handler Includes]

// [[[ begin generated region: do not modify [Generated Forward Declarations]
class MEikCommandObserver;		
class CAknDoubleTimeStyleListBox;
class CEikTextListBox;
// ]]] end generated region [Generated Forward Declarations]

/**
 * Container class for LightManSetupListBox
 * 
 * @class	CLightManSetupListBox LightManSetupListBox.h
 */
class CLightManSetupListBox : public CCoeControl
	,MEikListBoxObserver	{
public:
	// constructors and destructor
	CLightManSetupListBox();
	static CLightManSetupListBox* NewL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	static CLightManSetupListBox* NewLC( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
	void ConstructL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver );
    TInt GetListBoxItemCount();
	virtual ~CLightManSetupListBox();
    CTextListBoxModel* GetModel();

public:
	// from base class CCoeControl
	TInt CountComponentControls() const;
	CCoeControl* ComponentControl( TInt aIndex ) const;
	TKeyResponse OfferKeyEventL( 
			const TKeyEvent& aKeyEvent, 
			TEventCode aType );
	void HandleResourceChange( TInt aType );
	
protected:
	// from base class CCoeControl
	void SizeChanged();

private:
	// from base class CCoeControl
	void Draw( const TRect& aRect ) const;

private:
	void InitializeControlsL();
	void LayoutControls();
	CCoeControl* iFocusControl;
	MEikCommandObserver* iCommandObserver;
	// [[[ begin generated region: do not modify [Generated Methods]
public: 
	static void AddListBoxItemL( 
			CEikTextListBox* aListBox,
			const TDesC& aString );
    void AddListBoxItemL(const TDesC& aString);
    void AddListBoxItemL(const TDesC& aTime,const TDesC& aLevel);
    void AddListBoxItemL(const TDesC& aTime,const TInt aLevel);
    void EditListBoxItemL(const TDesC& aString, TInt aPos );
    void DeleteItem();
    void DeleteItem(TInt aPos);
    void GetListBoxItem(TDes& aDes,TInt aCount);
	static RArray< TInt >* GetSelectedListBoxItemsLC( CEikTextListBox* aListBox );
	static void DeleteSelectedListBoxItemsL( CEikTextListBox* aListBox );
    CAknDoubleTimeStyleListBox* ListBox();
	static void CreateListBoxItemL( TDes& aBuffer, 
			const TDesC& aTime1Text,
			const TDesC& aTime2Text,
			const TDesC& aMainText,
			const TDesC& aSecondaryText );
	void AddListBoxResourceArrayItemL( TInt aResourceId );
	void SetupListBoxIconsL();
	TBool HandleMarkableListCommandL( TInt aCommand );
    void ShowNoteL(TAknGlobalNoteType aType,TInt aResourceId);
private: 
    TBuf<50> iListBoxItemFormatted;
    CAknDoubleTimeStyleListBox* iListBox;
    TInt iCount;
    HBufC* iTimeTitle;
    HBufC* iLevelTitle;
protected: 
	void HandleListBoxEventL( 
			CEikListBox* aListBox,
			TListBoxEvent anEventType );
protected: 
	void HandleListBoxItemClickedL( 
			CEikListBox* aListBox,
			TListBoxEvent anEventType );	
public: 
	enum TControls
		{
		EListBox,
		ELastControl
		};
	enum TListBoxImages
		{
		EListBoxFirstUserImageIndex		
		};
    void SaveSettings();
private: 
    void LoadSettings();
    RFs iFs;
    RFile iFile;
    TFileText iText;
	typedef void ( CLightManSetupListBox::*ListBoxEventHandler )( 
			CEikListBox* aListBox, 
			TListBoxEvent anEvent );
	
	void AddListBoxEventHandlerL( 
			CEikListBox* aListBox, 
			TListBoxEvent anEvent, 
			ListBoxEventHandler aHandler );
	
	struct TListBoxEventDispatch 
		{ 
		CEikListBox* src; 
		TListBoxEvent event; 
		ListBoxEventHandler handler;
		};
		
	RArray< TListBoxEventDispatch > iListBoxEventDispatch;
	// ]]] end [MEikListBoxObserver support]
	
	};
				
#endif // LIGHTMANSETUPLISTBOX_H
