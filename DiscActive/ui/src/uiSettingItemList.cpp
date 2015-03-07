/*
========================================================================
 Name        : uiSettingItemList.cpp
 Author      : SQR
 Copyright   : Your copyright notice
 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <avkon.hrh>
#include <avkon.rsg>
#include <eikmenup.h>
#include <aknappui.h>
#include <eikcmobs.h>
#include <barsread.h>
#include <stringloader.h>
#include <aknnumedwin.h>
#include <eikenv.h>
#include <gdi.h>
#include <eikedwin.h>
#include <eikappui.h>
#include <aknviewappui.h>
#include <ui.rsg>
// ]]] end generated region [Generated System Includes]

// [[[ begin generated region: do not modify [Generated User Includes]
#include "uiSettingItemList.h"
#include "UiSettingItemListSettings.h"
#include "ui.hrh"
#include "uiSettingItemList.hrh"
#include "uiSettingItemListView.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * Construct the CUiSettingItemList instance
 * @param aCommandObserver command observer
 */ 
CUiSettingItemList::CUiSettingItemList( 
		TUiSettingItemListSettings& aSettings, 
		MEikCommandObserver* aCommandObserver )
	: iSettings( aSettings ), iCommandObserver( aCommandObserver )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}
/** 
 * Destroy any instance variables
 */
CUiSettingItemList::~CUiSettingItemList()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * Handle system notification that the container's size has changed.
 */
void CUiSettingItemList::SizeChanged()
	{
	if ( ListBox() ) 
		{
		ListBox()->SetRect( Rect() );
		}
	}

/**
 * Create one setting item at a time, identified by id.
 * CAknSettingItemList calls this method and takes ownership
 * of the returned value.  The CAknSettingItem object owns
 * a reference to the underlying data, which EditItemL() uses
 * to edit and store the value.
 */
CAknSettingItem* CUiSettingItemList::CreateSettingItemL( TInt aId )
	{
	switch ( aId )
		{
	// [[[ begin generated region: do not modify [Initializers]
		case EUiSettingItemListViewIntegerEditor1:
			{			
			CAknIntegerEdwinSettingItem* item = new ( ELeave ) 
				CAknIntegerEdwinSettingItem( 
					aId,
					iSettings.IntegerEditor1() );
			return item;
			}
		case EUiSettingItemListViewIntegerEditor2:
			{			
			CAknIntegerEdwinSettingItem* item = new ( ELeave ) 
				CAknIntegerEdwinSettingItem( 
					aId,
					iSettings.IntegerEditor2() );
			return item;
			}
		case EUiSettingItemListViewIntegerEditor4:
			{			
			CAknIntegerEdwinSettingItem* item = new ( ELeave ) 
				CAknIntegerEdwinSettingItem( 
					aId,
					iSettings.IntegerEditor4() );
			return item;
			}
		case EUiSettingItemListViewIntegerEditor3:
			{			
			CAknIntegerEdwinSettingItem* item = new ( ELeave ) 
				CAknIntegerEdwinSettingItem( 
					aId,
					iSettings.IntegerEditor3() );
			return item;
			}
		case EUiSettingItemListViewIntegerEditor5:
			{			
			CAknIntegerEdwinSettingItem* item = new ( ELeave ) 
				CAknIntegerEdwinSettingItem( 
					aId,
					iSettings.IntegerEditor5() );
			return item;
			}
		case EUiSettingItemListViewEdit1:
			{			
			CAknTextSettingItem* item = new ( ELeave ) 
				CAknTextSettingItem( 
					aId,
					iSettings.Edit1() );
			return item;
			}
	// ]]] end generated region [Initializers]
	
		}
		
	return NULL;
	}
	
/**
 * Edit the setting item identified by the given id and store
 * the changes into the store.
 * @param aIndex the index of the setting item in SettingItemArray()
 * @param aCalledFromMenu true: a menu item invoked editing, thus
 *	always show the edit page and interactively edit the item;
 *	false: change the item in place if possible, else show the edit page
 */
void CUiSettingItemList::EditItemL ( TInt aIndex, TBool aCalledFromMenu )
	{
	CAknSettingItem* item = ( *SettingItemArray() )[aIndex];
	switch ( item->Identifier() )
		{
	// [[[ begin generated region: do not modify [Editing Started Invoker]
	// ]]] end generated region [Editing Started Invoker]
	
		}
	
	CAknSettingItemList::EditItemL( aIndex, aCalledFromMenu );
	
	TBool storeValue = ETrue;
	switch ( item->Identifier() )
		{
	// [[[ begin generated region: do not modify [Editing Stopped Invoker]
	// ]]] end generated region [Editing Stopped Invoker]
	
		}
		
	if ( storeValue )
		{
		item->StoreL();
		SaveSettingValuesL();
		}	
	}
/**
 *	Handle the "Change" option on the Options menu.  This is an
 *	alternative to the Selection key that forces the settings page
 *	to come up rather than changing the value in place (if possible).
 */
void CUiSettingItemList::ChangeSelectedItemL()
	{
	if ( ListBox()->CurrentItemIndex() >= 0 )
		{
		EditItemL( ListBox()->CurrentItemIndex(), ETrue );
		}
	}

/**
 *	Load the initial contents of the setting items.  By default,
 *	the setting items are populated with the default values from
 * 	the design.  You can override those values here.
 *	<p>
 *	Note: this call alone does not update the UI.  
 *	LoadSettingsL() must be called afterwards.
 */
void CUiSettingItemList::LoadSettingValuesL()
	{
	// load values into iSettings
	}
	
/**
 *	Save the contents of the setting items.  Note, this is called
 *	whenever an item is changed and stored to the model, so it
 *	may be called multiple times or not at all.
 */
void CUiSettingItemList::SaveSettingValuesL()
	{
	// store values from iSettings
	}


/** 
 * Handle global resource changes, such as scalable UI or skin events (override)
 */
void CUiSettingItemList::HandleResourceChange( TInt aType )
	{
	CAknSettingItemList::HandleResourceChange( aType );
	SetRect( iAvkonViewAppUi->View( TUid::Uid( EUiSettingItemListViewId ) )->ClientRect() );
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}
				
/** 
 * Handle key event (override)
 * @param aKeyEvent key event
 * @param aType event code
 * @return EKeyWasConsumed if the event was handled, else EKeyWasNotConsumed
 */
TKeyResponse CUiSettingItemList::OfferKeyEventL( 
		const TKeyEvent& aKeyEvent, 
		TEventCode aType )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	if ( aKeyEvent.iCode == EKeyLeftArrow 
		|| aKeyEvent.iCode == EKeyRightArrow )
		{
		// allow the tab control to get the arrow keys
		return EKeyWasNotConsumed;
		}
	
	return CAknSettingItemList::OfferKeyEventL( aKeyEvent, aType );
	}
				
