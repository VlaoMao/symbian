/*
========================================================================
 Name        : VcallsettingsListBoxView.cpp
 Author      : SQR
 Copyright   : 
 Description : 
========================================================================
*/
#include <aknviewappui.h>
#include <eikmenub.h>
#include <avkon.hrh>
#include <barsread.h>
#include <stringloader.h>
#include <aknlists.h>
#include <eikenv.h>
#include <akniconarray.h>
#include <eikclbd.h>
#include <akncontext.h>
#include <akntitle.h>
#include <eikbtgpc.h>
#include <vcallsettings.rsg>

#include "vcallsettings.hrh"
#include "VcallsettingsListBoxView.h"
#include "vcallsettingsListBox.hrh"
#include "vcallsettingsListBox.h"

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CvcallsettingsListBoxView::CvcallsettingsListBoxView()
	{
	iVcallsettingsListBox = NULL;	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CvcallsettingsListBoxView::~CvcallsettingsListBoxView()
	{
	delete iVcallsettingsListBox;
	iVcallsettingsListBox = NULL;
	
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CvcallsettingsListBoxView
 */
CvcallsettingsListBoxView* CvcallsettingsListBoxView::NewL()
	{
	CvcallsettingsListBoxView* self = CvcallsettingsListBoxView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CvcallsettingsListBoxView
 */
CvcallsettingsListBoxView* CvcallsettingsListBoxView::NewLC()
	{
	CvcallsettingsListBoxView* self = new ( ELeave ) CvcallsettingsListBoxView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CvcallsettingsListBoxView::ConstructL()
	{
	BaseConstructL( R_VCALLSETTINGS_LIST_BOX_VCALLSETTINGS_LIST_BOX_VIEW );
					
	// add your own initialization code here
	
	}

/**
 * @return The UID for this view
 */
TUid CvcallsettingsListBoxView::Id() const
	{
	return TUid::Uid( EVcallsettingsListBoxViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CvcallsettingsListBoxView::HandleCommandL( TInt aCommand )
	{
	TBool commandHandled = EFalse;
	switch ( aCommand )
        {
        case ECommandAdd:
            commandHandled = Handle_AddSelected(aCommand);
            break;
        case ECommandSettings:
            commandHandled = Handle_SettingsSelected(aCommand);
            break;
        case ECommandAbout:
            commandHandled = Handle_AboutSelected(aCommand);
            break;
        case ECommandExit:
            commandHandled = Handle_ExitSelected(aCommand);
			break;
        case ECommandDelete:
            commandHandled = Handle_DeleteSelected(aCommand);
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
void CvcallsettingsListBoxView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	SetupStatusPaneL();
	
	if ( iVcallsettingsListBox == NULL )
		{
		iVcallsettingsListBox = CreateContainerL();
		iVcallsettingsListBox->SetMopParent( this );
		AppUi()->AddToStackL( *this, iVcallsettingsListBox );
		} 	
	}

/**
 */
void CvcallsettingsListBoxView::DoDeactivate()
	{
	CleanupStatusPane();
	
	if ( iVcallsettingsListBox != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iVcallsettingsListBox );
		delete iVcallsettingsListBox;
		iVcallsettingsListBox = NULL;
		}
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CvcallsettingsListBoxView::HandleStatusPaneSizeChange()
	{
	CAknView::HandleStatusPaneSizeChange();
    TVwsViewId view;
	AppUi()->GetActiveViewId( view );
	if ( view.iViewUid == Id() )
		{
		TInt result;
		TRAP( result, SetupStatusPaneL() );
		}
	
	}
void CvcallsettingsListBoxView::SetupStatusPaneL()
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
		iEikonEnv->CreateResourceReaderLC( reader, R_VCALLSETTINGS_LIST_BOX_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CvcallsettingsListBoxView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CVcallsettingsListBox::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CVcallsettingsListBox
 */
CVcallsettingsListBox* CvcallsettingsListBoxView::CreateContainerL()
	{
	return CVcallsettingsListBox::NewL( ClientRect(), NULL, this );
	}

TBool CvcallsettingsListBoxView::Handle_AddSelected(TInt aCommand)
{
    CAddForm* iNewForm = CAddForm::NewL();
    TBool err = iNewForm->ExecuteLD(R_ADDFORM_FORM_DIALOG);
    return ETrue;
}

TBool CvcallsettingsListBoxView::Handle_SettingsSelected(TInt aCommand)
{
    return ETrue;
}

TBool CvcallsettingsListBoxView::Handle_AboutSelected(TInt aCommand)
{
    TInt val = 0;
    HAL::Get(HALData::ELanguageIndex,val);
    TBuf<256> string;
    if(val == 16)
        {
            //ru
            string = _L("\nАвтор: SQR\nsqr.1cs.su\nРоссия,2012");
        }else{
            //other
            string = _L("\nAutor:SQR\nsqr.1cs.su\nRussia,2012");
        }
    CAknMessageQueryDialog* dlg = new(ELeave) CAknMessageQueryDialog();
    dlg->PrepareLC(R_ABOUT_DIALOG);
    dlg->QueryHeading()->SetTextL(_L("VCall"));
    dlg->SetMessageText(string);
    dlg->RunLD();
    return ETrue;
}

TBool CvcallsettingsListBoxView::Handle_DeleteSelected(TInt aCommand)
{
    return ETrue;
}

/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CvcallsettingsListBoxView::Handle_ExitSelected(TInt aCommand )
	{
    // Выход
    AppUi()->Exit();
	return ETrue;
	}
				
