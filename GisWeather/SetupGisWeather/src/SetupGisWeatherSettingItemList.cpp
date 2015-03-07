/*
========================================================================
 Name        : SetupGisWeatherSettingItemList.cpp
 Author      : SQR
 Copyright   : Created SQR, 2010, Russia
 Description : 
========================================================================
*/
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
#include <SetupGisWeather.rsg>
#include "SetupGisWeatherSettingItemList.h"
#include "SetupGisWeatherSettingItemListSettings.h"
#include "SetupGisWeather.hrh"
#include "SetupGisWeatherSettingItemList.hrh"
#include "SetupGisWeatherSettingItemListView.h"

/**
 * Construct the CSetupGisWeatherSettingItemList instance
 * @param aCommandObserver command observer
 */ 
CSetupGisWeatherSettingItemList::CSetupGisWeatherSettingItemList( 
		TSetupGisWeatherSettingItemListSettings& aSettings, 
		MEikCommandObserver* aCommandObserver )
	: iSettings( aSettings ), iCommandObserver( aCommandObserver )
	{
	
	}
/** 
 * Destroy any instance variables
 */
CSetupGisWeatherSettingItemList::~CSetupGisWeatherSettingItemList()
	{
	
	}

/**
 * Handle system notification that the container's size has changed.
 */
void CSetupGisWeatherSettingItemList::SizeChanged()
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
CAknSettingItem* CSetupGisWeatherSettingItemList::CreateSettingItemL( TInt aId )
	{
	switch ( aId )
		{
		case ESetupGisWeatherSettingItemListViewIntegerEditor1:
			{			
			CAknIntegerEdwinSettingItem* item = new ( ELeave ) 
				CAknIntegerEdwinSettingItem( 
					aId,
					iSettings.IntegerEditor1() );
			return item;
			}
		case ESetupGisWeatherSettingItemListViewIntegerEditor2:
			{			
			CAknIntegerEdwinSettingItem* item = new ( ELeave ) 
				CAknIntegerEdwinSettingItem( 
					aId,
					iSettings.IntegerEditor2() );
			return item;
			}
		case ESetupGisWeatherSettingItemListViewIntegerEditor_land_y:
		{
			CAknIntegerEdwinSettingItem* item = new ( ELeave )
				CAknIntegerEdwinSettingItem(
				aId,
				iSettings.IntegerEditor_land_y() );
			return item;
		}
		case ESetupGisWeatherSettingItemListViewIntegerEditor_land_x:
		{
			CAknIntegerEdwinSettingItem* item = new ( ELeave )
				CAknIntegerEdwinSettingItem(
				aId,
				iSettings.IntegerEditor_land_x() );
			return item;
		}
		case ESetupGisWeatherSettingItemListViewIntegerEditor3:
			{			
			CAknIntegerEdwinSettingItem* item = new ( ELeave ) 
				CAknIntegerEdwinSettingItem( 
					aId,
					iSettings.IntegerEditor3() );
			return item;
			}
		case ESetupGisWeatherSettingItemListViewEdit1:
			{			
			CAknTextSettingItem* item = new ( ELeave ) 
				CAknTextSettingItem( 
					aId,
					iSettings.Edit1() );
			return item;
			}
		case ESetupGisWeatherSettingItemListViewEdit2:
			{			
			CAknTextSettingItem* item = new ( ELeave ) 
				CAknTextSettingItem( 
					aId,
					iSettings.Edit2() );
			return item;
			}
		case ESetupGisWeatherSettingItemListViewEdit3:
			{			
			CAknTextSettingItem* item = new ( ELeave ) 
				CAknTextSettingItem( 
					aId,
					iSettings.Edit3() );
			return item;
			}
		case ESetupGisWeatherTimeEditFrom:
		    {
		    CAknTimeOrDateSettingItem* item = new(ELeave) CAknTimeOrDateSettingItem(aId,CAknTimeOrDateSettingItem::ETime,iSettings.TimeFrom());
		    return item;
		    }
		case ESetupGisWeatherTimeEditDo:
		    {
		    CAknTimeOrDateSettingItem* item = new(ELeave) CAknTimeOrDateSettingItem(aId,CAknTimeOrDateSettingItem::ETime,iSettings.TimeDo());
		    return item;
		    }
		case ESetupGisWeatherAutostart:
		{
			CAknBinaryPopupSettingItem* item = new(ELeave) CAknBinaryPopupSettingItem(aId,iSettings.iAutostart);
			return item;
		}
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
void CSetupGisWeatherSettingItemList::EditItemL ( TInt aIndex, TBool aCalledFromMenu )
	{
	CAknSettingItem* item = ( *SettingItemArray() )[aIndex];
	switch ( item->Identifier() )
		{
	
		}

	switch(aIndex)
	    {
	case 5:
		iSettings.SelectApp();
		LoadSettingsL();
		break;
	case 6:
	    iSettings.SelectAP();
	    LoadSettingsL();
	    break;
	case 7:
	    InputUrl();
	    LoadSettingsL();
	    break;
	default:
	    CAknSettingItemList::EditItemL( aIndex, aCalledFromMenu );
	    break;
	    }
	//TResourceReader read;
	//asfawefiCoeEnv->CreateResourceReaderLC(read,R_SETTING_LIST_SETTING_TIME);
	TBool storeValue = ETrue;
	switch ( item->Identifier() )
	    {

	    }
		
	if ( storeValue )
		{
		item->StoreL();
		SaveSettingValuesL();
		}	
	}
void CSetupGisWeatherSettingItemList::InputUrl()
    {
	HBufC* mess = StringLoader::LoadLC(R_STR_TITLE_URL);
	CAknTextQueryDialog* Dialog =CAknTextQueryDialog::NewL(iSettings.Edit3(),CAknQueryDialog::ENoTone);
	Dialog->PrepareLC(R_ASK_NAME_DIALOG);
	Dialog->SetPromptL(*mess);
	Dialog->RunLD();
	LoadSettingsL();
    }
/**
 *	Handle the "Change" option on the Options menu.  This is an
 *	alternative to the Selection key that forces the settings page
 *	to come up rather than changing the value in place (if possible).
 */
void CSetupGisWeatherSettingItemList::ChangeSelectedItemL()
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
void CSetupGisWeatherSettingItemList::LoadSettingValuesL()
	{
	// load values into iSettings
	}
	
/**
 *	Save the contents of the setting items.  Note, this is called
 *	whenever an item is changed and stored to the model, so it
 *	may be called multiple times or not at all.
 */
void CSetupGisWeatherSettingItemList::SaveSettingValuesL()
	{
	// store values from iSettings
	}


/** 
 * Handle global resource changes, such as scalable UI or skin events (override)
 */
void CSetupGisWeatherSettingItemList::HandleResourceChange( TInt aType )
	{
	CAknSettingItemList::HandleResourceChange( aType );
	SetRect( iAvkonViewAppUi->View( TUid::Uid( ESetupGisWeatherSettingItemListViewId ) )->ClientRect() );
	
	}
				
/** 
 * Handle key event (override)
 * @param aKeyEvent key event
 * @param aType event code
 * @return EKeyWasConsumed if the event was handled, else EKeyWasNotConsumed
 */
TKeyResponse CSetupGisWeatherSettingItemList::OfferKeyEventL( 
		const TKeyEvent& aKeyEvent, 
		TEventCode aType )
	{
	
	if ( aKeyEvent.iCode == EKeyLeftArrow/*
		|| aKeyEvent.iCode == EKeyRightArrow */)
		{
		// allow the tab control to get the arrow keys
		ListBox()->SetCurrentItemIndexAndDraw(0);
		//return EKeyWasNotConsumed;
		}
	if(aKeyEvent.iCode == EKeyRightArrow)
	    {
	    ListBox()->SetCurrentItemIndexAndDraw(/*5*/SettingItemArray()->Count()-1);
	    }

	return CAknSettingItemList::OfferKeyEventL( aKeyEvent, aType );
	}
				
/** 
 * Handle the Editing Stopped event.
 *
 * The embedded editor contains the updated setting value.  If this routine
 * returns ETrue, that value will be committed via aItem->StoreL().
 * <p>
 * Note that returning EFalse has no effect on the editor control, only 
 * on the iSettings store.  It is not possible to revert the editor's 
 * value automatically here (use editingStarted and editingStopped together 
 * to coordinate storing/restoring if necessary).
 * @return ETrue to store the value to the settings store
 */
TBool CSetupGisWeatherSettingItemList::HandleEdit2EditingStoppedL( 
		CAknSettingItem* /*aItem*/, 
		TBool /*aCalledFromMenu*/ )
	{
	// TODO: implement editingStopped event handler
	return ETrue;
	}

/** 
 * Handle the Editing Stopped event.
 *
 * The embedded editor contains the updated setting value.  If this routine
 * returns ETrue, that value will be committed via aItem->StoreL().
 * <p>
 * Note that returning EFalse has no effect on the editor control, only 
 * on the iSettings store.  It is not possible to revert the editor's 
 * value automatically here (use editingStarted and editingStopped together 
 * to coordinate storing/restoring if necessary).
 * @return ETrue to store the value to the settings store
 */
TBool CSetupGisWeatherSettingItemList::HandleEnumeratedTextPopup1EditingStoppedL( 
		CAknSettingItem* /*aItem*/, 
		TBool /*aCalledFromMenu*/ )
	{
	// TODO: implement editingStopped event handler
	return ETrue;
	}

