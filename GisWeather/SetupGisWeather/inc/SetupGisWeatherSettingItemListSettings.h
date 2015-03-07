/*
========================================================================
 Name        : SetupGisWeatherSettingItemListSettings.h
 Author      : SQR
 Copyright   : Created SQR, 2010, Russia
 Description : 
========================================================================
*/
#ifndef SETUPGISWEATHERSETTINGITEMLISTSETTINGS_H
#define SETUPGISWEATHERSETTINGITEMLISTSETTINGS_H
			
// [[[ begin generated region: do not modify [Generated Includes]
#include <e32std.h>
#include <f32file.h>
#include <aknutils.h>
#include <aknlists.h>
#include <activeapdb.h>
#include <apsettingshandlerui.h>
//listbox
#include <aknlists.h>
#include <aknpopup.h>
#include <barsread.h>
//end listbox
//apa window
#include <apgwgnam.h>
//apa window
#include "logger1.h"
#include <s32file.h>
//#include "CListboxContainer.h"
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Constants]
const int KEdit1MaxLength = 255;
const int KEdit2MaxLength = 255;
const int KEdit3MaxLength = 255;
_LIT(KFile_ext,"C:\\externalized.dat");
// ]]] end generated region [Generated Constants]

/**
 * @class	TSetupGisWeatherSettingItemListSettings SetupGisWeatherSettingItemListSettings.h
 */
class TSetupGisWeatherSettingItemListSettings
	{
public:
	// construct and destroy
	static TSetupGisWeatherSettingItemListSettings* NewL();
	void ConstructL();
private:
	// constructor
	TSetupGisWeatherSettingItemListSettings();
	// [[[ begin generated region: do not modify [Generated Accessors]
public:
	RFs iFs;
	RFile iFile;
	TInt& IntegerEditor1();
	void SetIntegerEditor1(const TInt& aValue);
	TInt& IntegerEditor2();
	TInt& IntegerEditor_land_y();
	void SetIntegerEditor_land_y(const TInt& aValue);
	TInt& IntegerEditor_land_x();
	void SetIntegerEditor_land_x(const TInt& aValue);
	void SetIntegerEditor2(const TInt& aValue);
	TInt& IntegerEditor3();
	void SetIntegerEditor3(const TInt& aValue);
	TDes& Edit1();
	void SetEdit1(const TDesC& aValue);
	TDes& Edit2();
	void SetEdit2(const TDesC& aValue);
	TDes& Edit3();
	void SetEdit3(const TDesC& aValue);
	void SetTimeFrom(const TTime& aTime);
	TTime& TimeFrom();
	void SetTimeDo(const TTime& aTime);
	TTime& TimeDo();
	void SetAutostart(const TBool aAutostart);
	TBool Autostart();
	void SelectApp();
	void SelectAP();
    TBool iAutostart;
protected:
	TInt iIntegerEditor1;
	TInt iIntegerEditor2;
	TInt iIntegerEditor_land_y;
	TInt iIntegerEditor_land_x;
	TInt iIntegerEditor3;
	TTime iTimeFrom;
	TTime iTimeDo;
	TBuf<KEdit1MaxLength> iEdit1;
	TBuf<KEdit2MaxLength> iEdit2;
	TBuf<KEdit3MaxLength> iEdit3;
        CEikColumnListBox* iListBox;
	// ]]] end generated region [Generated Members]
	
	};
#endif // SETUPGISWEATHERSETTINGITEMLISTSETTINGS_H
