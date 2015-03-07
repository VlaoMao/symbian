/*
========================================================================
 Name        : SetupGisWeatherSettingItemListSettings.cpp
 Author      : SQR
 Copyright   : Created SQR, 2010, Russia
 Description : 
========================================================================
*/
/**
 *	Generated helper class which manages the settings contained 
 *	in 'SetupGisWeatherSettingItemList'.  Each CAknSettingItem maintains
 *	a reference to data in this class so that changes in the setting
 *	item list can be synchronized with this storage.
 */
 
#include <e32base.h>
#include <stringloader.h>
#include <barsread.h>
#include <SetupGisWeather.rsg>
#include "SetupGisWeatherSettingItemListSettings.h"

/**
 * C/C++ constructor for settings data, cannot throw
 */
TSetupGisWeatherSettingItemListSettings::TSetupGisWeatherSettingItemListSettings()
	{
	}

/**
 * Two-phase constructor for settings data
 */
TSetupGisWeatherSettingItemListSettings* TSetupGisWeatherSettingItemListSettings::NewL()
	{
	TSetupGisWeatherSettingItemListSettings* data = new( ELeave ) TSetupGisWeatherSettingItemListSettings;
	CleanupStack::PushL( data );
	data->ConstructL();
	CleanupStack::Pop( data );
	return data;
	}

/**
 *	Second phase for initializing settings data
 */
void TSetupGisWeatherSettingItemListSettings::ConstructL()
	{
	//iTimeFrom = TDateTime();
	//iTimeDo = TDateTime();
	TFileText text;
	TBuf<256> buf;
	TInt val;
	TLex lex;
	iFs.Connect();
	TInt err = iFile.Open(iFs,_L("C:\\System\\Apps\\GisWeather\\cfg"),EFileRead);
	//fileurl.Open(fs,_L("C:\\Sytem\\Apps\\GisWeather\\url"),EFileRead);
	if(err == KErrNone)
	    {
	
	text.Set(iFile);
	
	text.Read(buf);
	lex.Assign(buf);
	lex.Val(val);
	SetIntegerEditor1(val); //portrait X
	
	text.Read(buf);
	lex.Assign(buf);
	lex.Val(val);
	SetIntegerEditor2(val); //portrait Y

	text.Read(buf);
	lex.Assign(buf);
	lex.Val(val);
	SetIntegerEditor_land_y(val); //landscape Y

	text.Read(buf);
	lex.Assign(buf);
	lex.Val(val);
	SetIntegerEditor_land_x(val); //landscape X
	
	text.Read(buf);
	lex.Assign(buf);
	lex.Val(val);
	SetIntegerEditor3(val); // time refresh
		{
		text.Read(buf);
		SetEdit1(buf);//UID
		}
		{
		text.Read(buf);//Access point
		SetEdit2(buf);
		}
		__LOGSTR("Now reading times");
		text.Read(buf);//time from
		__LOGSTR1("TimeFrom:%S",&buf);
		TInt from_ = iTimeFrom.Parse(buf,00);
		__LOGSTR1("from_:%d",from_);
		__LOGSTR2("iTimeFrom.Datetime.hour:%d,iTimeFrom.DateTime.minute:%d",iTimeFrom.DateTime().Hour(),iTimeFrom.DateTime().Minute());
		if(from_ >= 1)
		    {

		    }else{
		    iTimeFrom.HomeTime();
		    //SetTimeFrom(iTimeFrom);
		    }
		text.Read(buf);//time do
		__LOGSTR1("TimeDo:%S",&buf);
		TInt do_ = iTimeDo.Parse(buf,00);
		__LOGSTR1("do_:%d",do_);
		__LOGSTR2("iTimeDo.Datetime.hour:%d,iTimeDo.DateTime.minute:%d",iTimeDo.DateTime().Hour(),iTimeDo.DateTime().Minute());
		if(do_ >= 1)
		    {

		    }else{
		    iTimeDo.HomeTime();
		    }
		text.Read(buf);
		lex.Assign(buf);
		lex.Val(iAutostart);
		{
		iFile.Close();
		iFile.Open(iFs,_L("C:\\System\\Apps\\GisWeather\\url"),EFileRead);
		text.Set(iFile);
		text.Read(buf);//url
		SetEdit3(buf);
		}
	    }else{
	    }
	iFile.Close();
	iFs.Close();
	}
	
TInt& TSetupGisWeatherSettingItemListSettings::IntegerEditor1()
	{
	return iIntegerEditor1;
	}

void TSetupGisWeatherSettingItemListSettings::SetIntegerEditor1(const TInt& aValue)
	{
	iIntegerEditor1 = aValue;
	}

TInt& TSetupGisWeatherSettingItemListSettings::IntegerEditor2()
	{
	return iIntegerEditor2;
	}

void TSetupGisWeatherSettingItemListSettings::SetIntegerEditor2(const TInt& aValue)
	{
	iIntegerEditor2 = aValue;
	}

TInt& TSetupGisWeatherSettingItemListSettings::IntegerEditor_land_y()
	{
	return iIntegerEditor_land_y;
	}

void TSetupGisWeatherSettingItemListSettings::SetIntegerEditor_land_y(const TInt& aValue)
	{
	iIntegerEditor_land_y = aValue;
	}

TInt& TSetupGisWeatherSettingItemListSettings::IntegerEditor_land_x()
	{
	return iIntegerEditor_land_x;
	}

void TSetupGisWeatherSettingItemListSettings::SetIntegerEditor_land_x(const TInt& aValue)
	{
	iIntegerEditor_land_x = aValue;
	}


TInt& TSetupGisWeatherSettingItemListSettings::IntegerEditor3()
	{
	return iIntegerEditor3;
	}

void TSetupGisWeatherSettingItemListSettings::SetIntegerEditor3(const TInt& aValue)
	{
	iIntegerEditor3 = aValue;
	}

TDes& TSetupGisWeatherSettingItemListSettings::Edit1()
	{
	return iEdit1;
	}

void TSetupGisWeatherSettingItemListSettings::SetEdit1(const TDesC& aValue)
	{
	if ( aValue.Length() < KEdit1MaxLength)
		iEdit1.Copy( aValue );
	else
		iEdit1.Copy( aValue.Ptr(), KEdit1MaxLength);
	}

TDes& TSetupGisWeatherSettingItemListSettings::Edit2()
	{
	return iEdit2;
	}
TTime& TSetupGisWeatherSettingItemListSettings::TimeDo()
    {
    return iTimeDo;
    }
TTime& TSetupGisWeatherSettingItemListSettings::TimeFrom()
    {
    return iTimeFrom;
    }
void TSetupGisWeatherSettingItemListSettings::SetTimeFrom(const TTime& aTime)
    {
    iTimeFrom = aTime;
    }
void TSetupGisWeatherSettingItemListSettings::SetTimeDo(const TTime& aTime)
    {
    iTimeDo = aTime;
    }
void TSetupGisWeatherSettingItemListSettings::SelectApp()
{
	RWsSession& wsSession = CEikonEnv::Static()->WsSession();
	CApaWindowGroupName* wgName=CApaWindowGroupName::NewL(wsSession);
	RArray<TInt32> arr = RArray<TInt32>();
	HBufC* string = StringLoader::LoadL(R_SELECT_APP);
	//CleanupStack::PushL(wgName);

	CArrayFixFlat<TInt>* WindowGroupIds = new(ELeave)CArrayFixFlat<TInt>(1);
	//CleanupStack::PushL(WindowGroupIds);

	User::LeaveIfError(wsSession.WindowGroupList(0,WindowGroupIds));
	const TInt count = WindowGroupIds->Count();



	//CleanupStack::PopAndDestroy(2);//WindowGroupIds, wgName
	    CAknSinglePopupMenuStyleListBox* list =
	new(ELeave)CAknSinglePopupMenuStyleListBox;
	   // CleanupStack::PushL(list);

	    CAknPopupList* popupList = CAknPopupList::NewL(list,
	R_AVKON_SOFTKEYS_OK_BACK, AknPopupLayouts::EMenuWindow);
	   // CleanupStack::PushL(popupList);

	    list->ConstructL(popupList, 0);
	    list->CreateScrollBarFrameL(ETrue);
	    list->ScrollBarFrame()->SetScrollBarVisibilityL(CEikScrollBarFrame::EOff,
	CEikScrollBarFrame::EAuto);

	    CDesCArrayFlat* ItemArray = new(ELeave)CDesCArrayFlat(5);
	   // CleanupStack::PushL(ItemArray);

	    // add the item adding in here..
		for (TInt ii=0; ii<count; ii++)
		{
			TInt wgId = WindowGroupIds->At(ii);
			wgName->ConstructFromWgIdL(wgId);
			if(wgName->Hidden() == EFalse)
			{
				ItemArray->AppendL(wgName->Caption());
				arr.Append(wgName->AppUid().iUid);
			}
			//wgName->AppUid().Name()
			//wgName->Hidden()
			//wgName->IsSystem()
			//wgName->IsBusy()
			//wgName->AppUid()

		}


	    //CleanupStack::Pop();            //ItemArray
	    list->Model()->SetItemTextArray(ItemArray);
	    list->Model()->SetOwnershipType(ELbmOwnsItemArray);

	    popupList->SetTitleL(*string);

	    // Show popup list and then show return value.
	    TInt popupOk = popupList->ExecuteLD();
	    if (popupOk)
	    {
	    	TInt Sel = list->CurrentItemIndex();
	    	if (Sel >= 0 && Sel < ItemArray->MdcaCount())
	    	{
	    	    iEdit1.Format(_L("0x%x"),arr[Sel]);
	    	}
	    }

	   // CleanupStack::Pop();            // popuplist
	   // CleanupStack::PopAndDestroy(3); // list
}
void TSetupGisWeatherSettingItemListSettings::SelectAP()
    {
	TInt bearerFilter = EApBearerTypeAllBearers;
	CActiveApDb* aDb = CActiveApDb::NewL();
	CApSettingsHandler* settings = CApSettingsHandler::NewLC(
	            *aDb,
	            ETrue,
	            EApSettingsSelListIsPopUp,
	            EApSettingsSelMenuSelectNormal,
	            KEApIspTypeAll,
	            bearerFilter,
	            KEApSortNameAscending,
	            0,
	            EVpnFilterBoth,
	            ETrue);
	TUint32 sel;
	TUint32 selected_ap;
	TUint32 high(0);
	CCommsDatabase* data=CCommsDatabase::NewL();
	CApSelect* select=CApSelect::NewLC(*data,KEApIspTypeAll,EApBearerTypeAllBearers,KEApSortNameAscending);
	select->MoveToFirst();
	for(TUint nums=0;nums<select->Count();nums++)
	    {
	    if(select->Name() == iEdit2)
		{
		   high = select->Uid();
		}
	    select->MoveNext();
	    }
	TInt errRet = settings->RunSettingsL(high,selected_ap);
	__LOGSTR2("errRet: %d,selected_ap: %d",errRet,selected_ap);
	if(errRet == KApUiEventSelected)
	    {
	    __LOGSTR("KApUiEventSelected");
	    select->MoveToFirst();
	    for(TUint i=0;i<select->Count();i++)
		{
		sel = select->Uid();
		__LOGSTR1("Sel: %d",sel);
		if(sel == selected_ap)
		    {
		    __LOGSTR1("SetName: %S",&select->Name());
		    SetEdit2(select->Name());
		    }
		select->MoveNext();
		}
	    }
    }

void TSetupGisWeatherSettingItemListSettings::SetEdit2(const TDesC& aValue)
	{
	if ( aValue.Length() < KEdit2MaxLength)
		iEdit2.Copy( aValue );
	else
		iEdit2.Copy( aValue.Ptr(), KEdit2MaxLength);
	}

TDes& TSetupGisWeatherSettingItemListSettings::Edit3()
	{
	return iEdit3;
	}

void TSetupGisWeatherSettingItemListSettings::SetEdit3(const TDesC& aValue)
	{
	if ( aValue.Length() < KEdit3MaxLength)
		iEdit3.Copy( aValue );
	else
		iEdit3.Copy( aValue.Ptr(), KEdit3MaxLength);
	}

void TSetupGisWeatherSettingItemListSettings::SetAutostart(const TBool aAutostart)
{
	iAutostart = aAutostart;
}
TBool TSetupGisWeatherSettingItemListSettings::Autostart()
{
	return iAutostart;
}
