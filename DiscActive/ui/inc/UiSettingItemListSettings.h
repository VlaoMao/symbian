/*
========================================================================
 Name        : UiSettingItemListSettings.h
 Author      : SQR
 Copyright   : Your copyright notice
 Description : 
========================================================================
*/
#ifndef UISETTINGITEMLISTSETTINGS_H
#define UISETTINGITEMLISTSETTINGS_H
			
// [[[ begin generated region: do not modify [Generated Includes]
#include <e32std.h>
// ]]] end generated region [Generated Includes]

// [[[ begin generated region: do not modify [Generated Constants]
const int KEdit1MaxLength = 255;
// ]]] end generated region [Generated Constants]

/**
 * @class	TUiSettingItemListSettings UiSettingItemListSettings.h
 */
class TUiSettingItemListSettings
	{
public:
	// construct and destroy
	static TUiSettingItemListSettings* NewL();
	void ConstructL();
		
private:
	// constructor
	TUiSettingItemListSettings();
	// [[[ begin generated region: do not modify [Generated Accessors]
public:
	TInt& IntegerEditor1();
	void SetIntegerEditor1(const TInt& aValue);
	TInt& IntegerEditor2();
	void SetIntegerEditor2(const TInt& aValue);
	TInt& IntegerEditor4();
	void SetIntegerEditor4(const TInt& aValue);
	TInt& IntegerEditor3();
	void SetIntegerEditor3(const TInt& aValue);
	TInt& IntegerEditor5();
	void SetIntegerEditor5(const TInt& aValue);
	TDes& Edit1();
	void SetEdit1(const TDesC& aValue);
	void SaveEditor1();
	void SaveEditor2();
	void SaveEditor3();
	void SaveEditor4();
	void SaveEditor5();
	void SaveEditor6();
	TInt SaveValues();
	TInt RestartDA();
	// ]]] end generated region [Generated Accessors]
	
	// [[[ begin generated region: do not modify [Generated Members]
protected:
	TInt iIntegerEditor1;
	TInt iIntegerEditor2;
	TInt iIntegerEditor4;
	TInt iIntegerEditor3;
	TInt iIntegerEditor5;
	TBuf<KEdit1MaxLength> iEdit1;
	// ]]] end generated region [Generated Members]
public:
	
	RFs iFs;
	TInt iX;
	TInt iY;
	TInt iHeigth;
	TInt iWidth;
	TInt iLong;
	TBuf<32> iColor;
	};
#endif // UISETTINGITEMLISTSETTINGS_H
