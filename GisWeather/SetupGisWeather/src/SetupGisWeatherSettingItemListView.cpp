/*
========================================================================
 Name        : SetupGisWeatherSettingItemListView.cpp
 Author      : SQR
 Copyright   : Created SQR, 2010, Russia
 Description : 
========================================================================
*/
#include <aknviewappui.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <akncontext.h>
#include <aknmessagequerydialog.h>
#include <akntitle.h>
#include <stringloader.h>
#include <barsread.h>
#include <eikbtgpc.h>
#include <SetupGisWeather.rsg>

#include "SetupGisWeather.hrh"
#include "SetupGisWeatherSettingItemListView.h"
#include "SetupGisWeatherSettingItemList.hrh"
#include "SetupGisWeatherSettingItemList.h"


/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CSetupGisWeatherSettingItemListView::CSetupGisWeatherSettingItemListView()
	{
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CSetupGisWeatherSettingItemListView::~CSetupGisWeatherSettingItemListView()
	{
	
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CSetupGisWeatherSettingItemListView
 */
CSetupGisWeatherSettingItemListView* CSetupGisWeatherSettingItemListView::NewL()
	{
	CSetupGisWeatherSettingItemListView* self = CSetupGisWeatherSettingItemListView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CSetupGisWeatherSettingItemListView
 */
CSetupGisWeatherSettingItemListView* CSetupGisWeatherSettingItemListView::NewLC()
	{
	CSetupGisWeatherSettingItemListView* self = new ( ELeave ) CSetupGisWeatherSettingItemListView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CSetupGisWeatherSettingItemListView::ConstructL()
	{
	BaseConstructL( R_SETUP_GIS_WEATHER_SETTING_ITEM_LIST_SETUP_GIS_WEATHER_SETTING_ITEM_LIST_VIEW );
	//iSettings->ConstructL();
	// add your own initialization code here
	
	}

/**
 * @return The UID for this view
 */
TUid CSetupGisWeatherSettingItemListView::Id() const
	{
	return TUid::Uid( ESetupGisWeatherSettingItemListViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CSetupGisWeatherSettingItemListView::HandleCommandL( TInt aCommand )
	{
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
		case ESetupGisWeatherSettingItemListViewMenuItem1Command:
			commandHandled = HandleChangeSelectedSettingItemL( aCommand );
			break;
		case ESetupGisWeatherSettingItemListView_MenuItem2Command:
			commandHandled = Handle_MenuItem2SelectedL( aCommand );
			break;
		case ESetupGisWeatherSettingItemListView_MenuItem3Command:
			commandHandled = Handle_MenuItem3SelectedL( aCommand );
			break;
		case ESetupGisWeatherSettingItemListView_MenuItem5Command:
			commandHandled = Handle_MenuItem5SelectedL( aCommand );
			break;
		case ESetupGisWeatherSettingItemListView_MenuItem1Command:
			commandHandled = Handle_MenuItem1SelectedL( aCommand );
			break;
		case ESetupGisWeatherSettingItemListView_MenuItem4Command:
			commandHandled = Handle_MenuItem4SelectedL( aCommand );
			break;
		case ESetupGisWeatherSettingItemListView_MenuItemCommand:
			commandHandled = Handle_MenuItemSelectedL( aCommand );
			break;
		default:
			break;
		}
	
		
	if ( !commandHandled ) 
		{
	
		if ( aCommand == EAknSoftkeyExit )
			{
			AppUi()->HandleCommandL( EEikCmdExit );
			}
	
		}
	
	}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CSetupGisWeatherSettingItemListView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	SetupStatusPaneL();
				
	if ( iSetupGisWeatherSettingItemList == NULL )
		{
		iSettings = TSetupGisWeatherSettingItemListSettings::NewL();
		iSetupGisWeatherSettingItemList = new ( ELeave ) CSetupGisWeatherSettingItemList( *iSettings, this );
		iSetupGisWeatherSettingItemList->SetMopParent( this );
		iSetupGisWeatherSettingItemList->ConstructFromResourceL( R_SETUP_GIS_WEATHER_SETTING_ITEM_LIST_SETUP_GIS_WEATHER_SETTING_ITEM_LIST );
		iSetupGisWeatherSettingItemList->ActivateL();
		iSetupGisWeatherSettingItemList->LoadSettingValuesL();
		iSetupGisWeatherSettingItemList->LoadSettingsL();
		AppUi()->AddToStackL( *this, iSetupGisWeatherSettingItemList );
		}
	}

/**
 */
void CSetupGisWeatherSettingItemListView::DoDeactivate()
	{
	CleanupStatusPane();
	
	if ( iSetupGisWeatherSettingItemList != NULL )
		{
		AppUi()->RemoveFromStack( iSetupGisWeatherSettingItemList );
		delete iSetupGisWeatherSettingItemList;
		iSetupGisWeatherSettingItemList = NULL;
		delete iSettings;
		iSettings = NULL;
		}
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CSetupGisWeatherSettingItemListView::HandleStatusPaneSizeChange()
	{
	CAknView::HandleStatusPaneSizeChange();
	
	// this may fail, but we're not able to propagate exceptions here
	TVwsViewId view;
	AppUi()->GetActiveViewId( view );
	if ( view.iViewUid == Id() )
		{
		TInt result;
		TRAP( result, SetupStatusPaneL() );
		}
	
	}

void CSetupGisWeatherSettingItemListView::SetupStatusPaneL()
	{
	// reset the context pane
	TUid contextPaneUid = TUid::Uid( EEikStatusPaneUidContext );
	CEikStatusPaneBase::TPaneCapabilities subPaneContext = 
		StatusPane()->PaneCapabilities( contextPaneUid );
	if ( subPaneContext.IsPresent() && subPaneContext.IsAppOwned() )
		{
		CAknContextPane* context = static_cast< CAknContextPane* > ( 
			StatusPane()->ControlL( contextPaneUid ) );
		context->SetPictureToDefaultL();
		}
	
	// setup the title pane
	TUid titlePaneUid = TUid::Uid( EEikStatusPaneUidTitle );
	CEikStatusPaneBase::TPaneCapabilities subPaneTitle = 
		StatusPane()->PaneCapabilities( titlePaneUid );
	if ( subPaneTitle.IsPresent() && subPaneTitle.IsAppOwned() )
		{
		CAknTitlePane* title = static_cast< CAknTitlePane* >( 
			StatusPane()->ControlL( titlePaneUid ) );
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_SETUP_GIS_WEATHER_SETTING_ITEM_LIST_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

void CSetupGisWeatherSettingItemListView::CleanupStatusPane()
	{
	}


/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CSetupGisWeatherSettingItemListView::HandleChangeSelectedSettingItemL( TInt aCommand )
	{
	iSetupGisWeatherSettingItemList->ChangeSelectedItemL();
	return ETrue;
	}
				

/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CSetupGisWeatherSettingItemListView::Handle_MenuItemSelectedL( TInt aCommand )
	{//Exit
	AppUi()->HandleCommandL(EEikCmdExit);
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CSetupGisWeatherSettingItemListView::Handle_MenuItem4SelectedL( TInt aCommand )
	{
	CAknMessageQueryDialog* dlg = new(ELeave) CAknMessageQueryDialog();
	HBufC* title = StringLoader::LoadL(R_ABOUT_TITLE);
	HBufC* about = StringLoader::LoadL(R_ABOUT);
	dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
	dlg->QueryHeading()->SetTextL(*title);
	dlg->SetMessageText(*about);
	dlg->RunLD();

	//About
	// TODO: implement selected event handler

	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CSetupGisWeatherSettingItemListView::Handle_MenuItem2SelectedL( TInt aCommand )
	{
	/// save
	RFile filecfg;
	RFs fs;
	RFile fileurl;
	TFileText textcfg,texturl;
	TBuf<256> buf;
	_LIT(KFormat,"%H:%T");
	User::LeaveIfError(fs.Connect());
	filecfg.Replace(fs,_L("C:\\System\\Apps\\GisWeather\\cfg"),EFileWrite);
	fileurl.Replace(fs,_L("C:\\System\\Apps\\GisWeather\\url"),EFileWrite);
	
	filecfg.Write(0,_L8("\xff\xfe"));
	fileurl.Write(0,_L8("\xff\xfe"));

	textcfg.Set(filecfg);
	texturl.Set(fileurl);
	
	buf.AppendNum(iSettings->IntegerEditor1());
	textcfg.Write(buf);
	buf.Delete(0,buf.Length());
	buf.AppendNum(iSettings->IntegerEditor2());
	textcfg.Write(buf);
	buf.Delete(0,buf.Length());
	buf.AppendNum(iSettings->IntegerEditor_land_y());
	textcfg.Write(buf);
	buf.Delete(0,buf.Length());
	buf.AppendNum(iSettings->IntegerEditor_land_x());
	textcfg.Write(buf);
	buf.Delete(0,buf.Length());
	buf.AppendNum(iSettings->IntegerEditor3());
	textcfg.Write(buf);
	buf.Delete(0,buf.Length());
	
	textcfg.Write(iSettings->Edit1());
	textcfg.Write(iSettings->Edit2());
	texturl.Write(iSettings->Edit3());

	iSettings->TimeFrom().FormatL(buf,KFormat);//from
	textcfg.Write(buf);
	
	iSettings->TimeDo().FormatL(buf,KFormat);//do
	textcfg.Write(buf);

	buf.Delete(0,buf.Length());
	buf.AppendNum(iSettings->Autostart());
	textcfg.Write(buf);
	//buf.Format(KFormat,iSettings->TimeFrom().Hour(),iSettings->TimeFrom().Minute());
	//textcfg.Write(buf);

	CAknInformationNote* note = new(ELeave) CAknInformationNote;
	HBufC* string = StringLoader::LoadL(R_STR_SAVED);
	note->ExecuteLD(*string);
	filecfg.Close();
	fileurl.Close();
	fs.Close();
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CSetupGisWeatherSettingItemListView::Handle_MenuItem3SelectedL( TInt aCommand )
	{
	// Kill informer
	TFindProcess processFinder(_L("GisWeather.exe*"));
	RFile file;
	file.Replace(iEikonEnv->FsSession(),_L("C:\\System\\Apps\\GisWeather\\Exit"),EFileWrite);
	file.Close();
	TFullName result;
	TInt count(0);
	//TInt err;
	//RProcess processHandle;
	User::After(500000);
	while(processFinder.Next(result)==KErrNone)
		{
		//err = processHandle.Open(processFinder,EOwnerThread);
		//processHandle.Kill(KErrNone);
		//processHandle.Close();
		//if(err == KErrNone)
		    count++;
		}
	CAknInformationNote* note = new(ELeave) CAknInformationNote;
	if(count > 0)
	    {
	    HBufC* string = StringLoader::LoadL(R_STR_FAILED);
	    note->ExecuteLD(*string);
	    }else{
	    HBufC* string = StringLoader::LoadL(R_STR_SUCCESS);
	    note->ExecuteLD(*string);
	    }
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CSetupGisWeatherSettingItemListView::Handle_MenuItem5SelectedL( TInt aCommand )
	{
	RProcess proc;
	TInt err;
	err = proc.Create(_L("GisWeather.exe"),KNullDesC);
	proc.Resume();
	proc.Close();
	CAknInformationNote* note = new(ELeave) CAknInformationNote;
	if(err == KErrNone)
	    {
	    HBufC* string = StringLoader::LoadL(R_STR_SUCCESS);
	    note->ExecuteLD(*string);
	    }else{
	    HBufC* string = StringLoader::LoadL(R_STR_FAILED);
	    note->ExecuteLD(*string);
	    }
	//Start informer
	// TODO: implement selected event handler
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CSetupGisWeatherSettingItemListView::Handle_MenuItem1SelectedL( TInt aCommand )
	{
	RApaLsSession LsSession;
	CApaCommandLine* cmd = CApaCommandLine::NewL();
	LsSession.Connect();
	cmd->SetExecutableNameL(_L("GisWeatherDownloader.exe"));
	cmd->SetCommandL(EApaCommandBackground);
	LsSession.StartApp(*cmd);
	CAknInformationNote* note = new(ELeave) CAknInformationNote;
	HBufC* string = StringLoader::LoadL(R_STR_STARTED);
	note->ExecuteLD(*string);
	//Download informer
	// TODO: implement selected event handler
	return ETrue;
	}
				
