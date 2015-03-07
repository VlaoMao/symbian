/*
========================================================================
 Name        : UiSettingItemListView.cpp
 Author      : SQR
 Copyright   : Your copyright notice
 Description : 
========================================================================
*/
// [[[ begin generated region: do not modify [Generated System Includes]
#include <aknviewappui.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <akncontext.h>
#include <akntitle.h>
#include <stringloader.h>
#include <barsread.h>
#include <eikbtgpc.h>
#include <ui.rsg>
// ]]] end generated region [Generated System Includes]
#include <aknnotewrappers.h>
// [[[ begin generated region: do not modify [Generated User Includes]
#include <aknmessagequerydialog.h>

#include "ui.hrh"
#include "UiSettingItemListSettings.h"
#include "uiSettingItemListView.h"
#include "uiSettingItemList.hrh"
#include "uiSettingItemList.h"
// ]]] end generated region [Generated User Includes]

// [[[ begin generated region: do not modify [Generated Constants]
// ]]] end generated region [Generated Constants]

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CuiSettingItemListView::CuiSettingItemListView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CuiSettingItemListView::~CuiSettingItemListView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CuiSettingItemListView
 */
CuiSettingItemListView* CuiSettingItemListView::NewL()
	{
	CuiSettingItemListView* self = CuiSettingItemListView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CuiSettingItemListView
 */
CuiSettingItemListView* CuiSettingItemListView::NewLC()
	{
	CuiSettingItemListView* self = new ( ELeave ) CuiSettingItemListView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CuiSettingItemListView::ConstructL()
	{
	// [[[ begin generated region: do not modify [Generated Code]
	BaseConstructL( R_UI_SETTING_ITEM_LIST_UI_SETTING_ITEM_LIST_VIEW );
				
	// ]]] end generated region [Generated Code]
	
	// add your own initialization code here
	
	}

/**
 * @return The UID for this view
 */
TUid CuiSettingItemListView::Id() const
	{
	return TUid::Uid( EUiSettingItemListViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */

void CuiSettingItemListView::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
		case EUiSettingItemListViewMenuItem1Command:
			commandHandled = HandleChangeSelectedSettingItemL( aCommand );
			break;
		case EUiSettingItemListViewSaveMenuItemCommand: //Сохранить
			TInt err = iSettings->SaveValues();
			HBufC* string;
			CAknInformationNote* note;
			note = new(ELeave) CAknInformationNote;
			if(err == KErrNone)
				{
				string = StringLoader::LoadLC(R_STR_SUCCESS);
				}else{
				string = StringLoader::LoadLC(R_STR_FAILED);
				}
			note->ExecuteLD(*string);
			CleanupStack::PopAndDestroy(string);
			commandHandled = ETrue;
			break;
		case EUiSettingItemListViewRestart_DAMenuItemCommand: //Перезапуск DA
			iSettings->RestartDA();
			commandHandled = ETrue;
			break;
		case EUiSettingItemListViewAboutMenuItemCommand: //О программе
			CAknMessageQueryDialog* dlg = new(ELeave) CAknMessageQueryDialog();
			dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
			HBufC* title = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TITLE);
			dlg->QueryHeading()->SetTextL(*title);
			CleanupStack::PopAndDestroy();
			HBufC* msg = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TEXT);
			dlg->SetMessageTextL(*msg);
			CleanupStack::PopAndDestroy();
			dlg->RunLD();
			commandHandled = ETrue;
			break;
		case EUiSettingItemListViewExitMenuItemCommand: //Выход
			commandHandled = ETrue;
			AppUi()->Exit();
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
	// ]]] end generated region [Generated Code]
	
	}

/**
 *	Handles user actions during activation of the view, 
 *	such as initializing the content.
 */
void CuiSettingItemListView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
	if ( iUiSettingItemList == NULL )
		{
		iSettings = TUiSettingItemListSettings::NewL();
		iUiSettingItemList = new ( ELeave ) CUiSettingItemList( *iSettings, this );
		iUiSettingItemList->SetMopParent( this );
		iUiSettingItemList->ConstructFromResourceL( R_UI_SETTING_ITEM_LIST_UI_SETTING_ITEM_LIST );
		iUiSettingItemList->ActivateL();
		iUiSettingItemList->LoadSettingValuesL();
		iUiSettingItemList->LoadSettingsL();
		AppUi()->AddToStackL( *this, iUiSettingItemList );
		} 
	// ]]] end generated region [Generated Contents]
	
	}

/**
 */
void CuiSettingItemListView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iUiSettingItemList != NULL )
		{
		AppUi()->RemoveFromStack( iUiSettingItemList );
		delete iUiSettingItemList;
		iUiSettingItemList = NULL;
		delete iSettings;
		iSettings = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CuiSettingItemListView::HandleStatusPaneSizeChange()
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
	
	// [[[ begin generated region: do not modify [Generated Code]
	// ]]] end generated region [Generated Code]
	
	}

// [[[ begin generated function: do not modify
void CuiSettingItemListView::SetupStatusPaneL()
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
		iEikonEnv->CreateResourceReaderLC( reader, R_UI_SETTING_ITEM_LIST_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CuiSettingItemListView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CuiSettingItemListView::HandleChangeSelectedSettingItemL( TInt aCommand )
	{
	iUiSettingItemList->ChangeSelectedItemL();
	return ETrue;
	}
				

/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CuiSettingItemListView::HandleExitMenuItemSelectedL( TInt aCommand )
	{
	// TODO: implement selected event handler
	return ETrue;
	}
				
