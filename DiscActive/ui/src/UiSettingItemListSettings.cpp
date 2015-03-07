/*
========================================================================
 Name        : UiSettingItemListSettings.cpp
 Author      : SQR
 Copyright   : Your copyright notice
 Description : 
========================================================================
*/
/**
 *	Generated helper class which manages the settings contained 
 *	in 'uiSettingItemList'.  Each CAknSettingItem maintains
 *	a reference to data in this class so that changes in the setting
 *	item list can be synchronized with this storage.
 */
 
// [[[ begin generated region: do not modify [Generated Includes]
#include <e32base.h>
#include <stringloader.h>
#include <barsread.h>
#include <ui.rsg>
#include "UiSettingItemListSettings.h"
// ]]] end generated region [Generated Includes]
#include <aknnotewrappers.h>

/**
 * C/C++ constructor for settings data, cannot throw
 */
TUiSettingItemListSettings::TUiSettingItemListSettings()
	{
	}

/**
 * Two-phase constructor for settings data
 */
TUiSettingItemListSettings* TUiSettingItemListSettings::NewL()
	{
	TUiSettingItemListSettings* data = new( ELeave ) TUiSettingItemListSettings;
	CleanupStack::PushL( data );
	data->ConstructL();
	CleanupStack::Pop( data );
	return data;
	}
	
/**
 *	Second phase for initializing settings data
 */
void TUiSettingItemListSettings::ConstructL()
	{
	
	RFile file;
	TFileText text;
	TLex lex;
	TInt val;
	TBuf<256> buf;
	iFs.Connect();
	TInt err = file.Open(iFs,_L("C:\\System\\Apps\\DiskActive\\DiskActive.cfg"),EFileRead | EFileWrite);
	if(err == KErrNone)
		{
		text.Set(file);
		text.Read(buf);
		lex.Assign(buf);
		lex.Val(val);
		iX = val;
		
		text.Read(buf);
		lex.Assign(buf);
		lex.Val(val);
		iY = val;
		
		text.Read(buf);
		lex.Assign(buf);
		lex.Val(val);
		iHeigth = val;
		
		text.Read(buf);
		lex.Assign(buf);
		lex.Val(val);
		iWidth = val;
		
		text.Read(buf);
		lex.Assign(buf);
		lex.Val(val);
		iLong = val;
		
		text.Read(buf);
		iColor = buf;
		}else{
		iX = 235;
		iY = 0;
		iHeigth = 5;
		iWidth = 50;
		iLong = 50;
		iColor = _L("0x0000ff");
		}
	file.Close();
	// [[[ begin generated region: do not modify [Generated Initializers]
	SetIntegerEditor1( iX );
	SetIntegerEditor2( iY );
	SetIntegerEditor4( iHeigth );
	SetIntegerEditor3( iWidth );
	SetIntegerEditor5( iLong );
		{
		//HBufC* text = StringLoader::LoadLC( R_UI_SETTING_ITEM_LIST_EDIT1 );
		SetEdit1( iColor );
		//CleanupStack::PopAndDestroy( text );
		}
	// ]]] end generated region [Generated Initializers]
	
	}
	
// [[[ begin generated region: do not modify [Generated Contents]
TInt& TUiSettingItemListSettings::IntegerEditor1()
	{
	return iIntegerEditor1;
	}

void TUiSettingItemListSettings::SetIntegerEditor1(const TInt& aValue)
	{
	iIntegerEditor1 = aValue;
	}

TInt& TUiSettingItemListSettings::IntegerEditor2()
	{
	return iIntegerEditor2;
	}

void TUiSettingItemListSettings::SetIntegerEditor2(const TInt& aValue)
	{
	iIntegerEditor2 = aValue;
	}

TInt& TUiSettingItemListSettings::IntegerEditor4()
	{
	return iIntegerEditor4;
	}

void TUiSettingItemListSettings::SetIntegerEditor4(const TInt& aValue)
	{
	iIntegerEditor4 = aValue;
	}

TInt& TUiSettingItemListSettings::IntegerEditor3()
	{
	return iIntegerEditor3;
	}

void TUiSettingItemListSettings::SetIntegerEditor3(const TInt& aValue)
	{
	iIntegerEditor3 = aValue;
	}

TInt& TUiSettingItemListSettings::IntegerEditor5()
	{
	return iIntegerEditor5;
	}

void TUiSettingItemListSettings::SetIntegerEditor5(const TInt& aValue)
	{
	iIntegerEditor5 = aValue;
	}

TDes& TUiSettingItemListSettings::Edit1()
	{
	return iEdit1;
	}

void TUiSettingItemListSettings::SetEdit1(const TDesC& aValue)
	{
	if ( aValue.Length() < KEdit1MaxLength)
		iEdit1.Copy( aValue );
	else
		iEdit1.Copy( aValue.Ptr(), KEdit1MaxLength);
	}

// ]]] end generated region [Generated Contents]
void TUiSettingItemListSettings::SaveEditor1()
	{
	iX = iIntegerEditor1;
	}
void TUiSettingItemListSettings::SaveEditor2()
	{
	iY = iIntegerEditor2;
	}
void TUiSettingItemListSettings::SaveEditor3()
	{
	iWidth = iIntegerEditor3;
	}
void TUiSettingItemListSettings::SaveEditor4()
	{
	iHeigth = iIntegerEditor4;
	}
void TUiSettingItemListSettings::SaveEditor5()
	{
	iLong = iIntegerEditor5;
	}
void TUiSettingItemListSettings::SaveEditor6()
	{
	iColor = iEdit1;
	}

TInt TUiSettingItemListSettings::RestartDA()
	{
	_LIT(KDiskActiveKill,"DiskActive.exe*");
				_LIT(KDiskActiveStart,"DiskActive.exe");
				HBufC* mess;
				RProcess proc;
				TInt error;
				TFullName result;
				CAknInformationNote* note = new(ELeave) CAknInformationNote;
				TFindProcess procFinder(KDiskActiveKill);
				while(procFinder.Next(result)==KErrNone)//Kill DiskActive process
					{
						proc.Open(procFinder,EOwnerThread);
						proc.Kill(KErrNone);
						proc.Close();
					}
							    // end kill
							    //start
				error = proc.Create(KDiskActiveStart,KNullDesC);
				proc.Resume();
			    proc.Close();
			    switch(error)
						{
							case KErrNone:
							mess = StringLoader::LoadLC(R_STR_SUCCESS);
							break;
							case KErrNotFound:
							mess = StringLoader::LoadLC(R_STR_FAILED);
							break;
						}
			    note->ExecuteLD(*mess);
			    CleanupStack::PopAndDestroy(mess);
			    return error;
	}
TInt TUiSettingItemListSettings::SaveValues()
	{
	RFile file;
	TFileText text;
	
	SaveEditor1();
	SaveEditor2();
	SaveEditor3();
	SaveEditor4();
	SaveEditor5();
	SaveEditor6();
	
	TBuf16<256> buf;
	TBuf8<32> enc(_L8("\xff\xfe"));
	iFs.Delete(_L("C:\\System\\Apps\\DiskActive\\DiskActive.cfg"));
	TInt err = file.Create(iFs,_L("C:\\System\\Apps\\DiskActive\\DiskActive.cfg"),EFileRead | EFileWrite);
	if(err == KErrNone)
		{
		text.Set(file);
		file.Write(enc);
		
		buf.Num(iX);
		buf.Append(_L("\r\n"));
		TPtrC8 ptrCX((TUint8*)buf.Ptr(),buf.Size());
		file.Write(ptrCX);
		//buf.Delete(0,buf.Length());
		
		buf.Num(iY);
		buf.Append(_L("\r\n"));
		TPtrC8 ptrCY((TUint8*)buf.Ptr(),buf.Size());
		file.Write(ptrCY);
		//buf.Delete(0,buf.Length());
		
		buf.Num(iHeigth);
		buf.Append(_L("\r\n"));
		TPtrC8 ptrCH((TUint8*)buf.Ptr(),buf.Size());
		file.Write(ptrCH);
		//buf.Delete(0,buf.Length());
		
		buf.Num(iWidth);
		buf.Append(_L("\r\n"));
		TPtrC8 ptrCW((TUint8*)buf.Ptr(),buf.Size());
		file.Write(ptrCW);
		//buf.Delete(0,buf.Length());
		
		buf.Num(iLong);
		buf.Append(_L("\r\n"));
		TPtrC8 ptrCL((TUint8*)buf.Ptr(),buf.Size());
		file.Write(ptrCL);
		//buf.Delete(0,buf.Length());
		
		buf = iColor;
		buf.Append(_L("\r\n"));
		TPtrC8 ptrCC((TUint8*)buf.Ptr(),buf.Size());
		file.Write(ptrCC);
		
		file.Close();
		}
	return err;
	}
