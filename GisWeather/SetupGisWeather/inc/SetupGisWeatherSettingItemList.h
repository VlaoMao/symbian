/*
========================================================================
 Name        : SetupGisWeatherSettingItemList.h
 Author      : SQR
 Copyright   : Created SQR, 2010, Russia
 Description : 
========================================================================
*/
#ifndef SETUPGISWEATHERSETTINGITEMLIST_H
#define SETUPGISWEATHERSETTINGITEMLIST_H

#include <aknsettingitemlist.h>
#include <eikrted.h>
#include <txtrich.h>
#include <aknmessagequerydialog.h>
#include "logger1.h"

class MEikCommandObserver;
class TSetupGisWeatherSettingItemListSettings;

/**
 * @class	CSetupGisWeatherSettingItemList SetupGisWeatherSettingItemList.h
 */
class CSetupGisWeatherSettingItemList : public CAknSettingItemList
	{
public: // constructors and destructor

	CSetupGisWeatherSettingItemList( 
			TSetupGisWeatherSettingItemListSettings& settings, 
			MEikCommandObserver* aCommandObserver );
	virtual ~CSetupGisWeatherSettingItemList();

public:

	// from CCoeControl
	void HandleResourceChange( TInt aType );

	// overrides of CAknSettingItemList
	CAknSettingItem* CreateSettingItemL( TInt id );
	void EditItemL( TInt aIndex, TBool aCalledFromMenu );
	TKeyResponse OfferKeyEventL( 
			const TKeyEvent& aKeyEvent, 
			TEventCode aType );

public:
	// utility function for menu
	void ChangeSelectedItemL();

	void LoadSettingValuesL();
	void SaveSettingValuesL();
        CEikRichTextEditor* iEditor;
        void InputUrl();
		
private:
	// override of CAknSettingItemList
	void SizeChanged();

private:
	// current settings values
	TSetupGisWeatherSettingItemListSettings& iSettings;
	MEikCommandObserver* iCommandObserver;

protected: 
	TBool HandleEdit2EditingStoppedL( 
			CAknSettingItem* /*aIndex*/, 
			TBool /*aCalledFromMenu*/ );
	TBool HandleEnumeratedTextPopup1EditingStoppedL( 
			CAknSettingItem* /*aIndex*/, 
			TBool /*aCalledFromMenu*/ );
	
	};
#endif // SETUPGISWEATHERSETTINGITEMLIST_H
