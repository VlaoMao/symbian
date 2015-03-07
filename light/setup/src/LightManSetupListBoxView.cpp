/*
========================================================================
 Name        : LightManSetupListBoxView.cpp
 Author      : SQR
 Copyright   : 
 Description : 
========================================================================
*/
#include "LightManSetupListBoxView.h"

/**
 * First phase of Symbian two-phase construction. Should not contain any
 * code that could leave.
 */
CLightManSetupListBoxView::CLightManSetupListBoxView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iLightManSetupListBox = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * The view's destructor removes the container from the control
 * stack and destroys it.
 */
CLightManSetupListBoxView::~CLightManSetupListBoxView()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iLightManSetupListBox;
	iLightManSetupListBox = NULL;
	// ]]] end generated region [Generated Contents]
	
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance then calls the second-phase constructor
 * without leaving the instance on the cleanup stack.
 * @return new instance of CLightManSetupListBoxView
 */
CLightManSetupListBoxView* CLightManSetupListBoxView::NewL()
	{
	CLightManSetupListBoxView* self = CLightManSetupListBoxView::NewLC();
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Symbian two-phase constructor.
 * This creates an instance, pushes it on the cleanup stack,
 * then calls the second-phase constructor.
 * @return new instance of CLightManSetupListBoxView
 */
CLightManSetupListBoxView* CLightManSetupListBoxView::NewLC()
	{
	CLightManSetupListBoxView* self = new ( ELeave ) CLightManSetupListBoxView();
	CleanupStack::PushL( self );
	self->ConstructL();
	return self;
	}


/**
 * Second-phase constructor for view.  
 * Initialize contents from resource.
 */ 
void CLightManSetupListBoxView::ConstructL()
	{
    BaseConstructL( R_LIGHT_MAN_SETUP_LIST_BOX_LIGHT_MAN_SETUP_LIST_BOX_VIEW );
	}

/**
 * @return The UID for this view
 */
TUid CLightManSetupListBoxView::Id() const
	{
	return TUid::Uid( ELightManSetupListBoxViewId );
	}

/**
 * Handle a command for this view (override)
 * @param aCommand command id to be handled
 */
void CLightManSetupListBoxView::HandleCommandL( TInt aCommand )
	{
	// [[[ begin generated region: do not modify [Generated Code]
	TBool commandHandled = EFalse;
	switch ( aCommand )
		{	// code to dispatch to the AknView's menu and CBA commands is generated here
		case ELightManSetupListBoxViewAddMenuItemCommand:
			commandHandled = HandleAddMenuItemSelectedL( aCommand );
			break;
		case ELightManSetupListBoxViewChangeMenuItemCommand:
			commandHandled = HandleChangeMenuItemSelectedL( aCommand );
			break;
		case ELightManSetupListBoxViewDeleteMenuItemCommand:
			commandHandled = HandleDeleteMenuItemSelectedL( aCommand );
			break;
		case ELightManSetupListBoxViewAboutMenuItemCommand:
			commandHandled = HandleAboutMenuItemSelectedL( aCommand );
			break;
		case ELightManSetupListBoxViewExitMenuItemCommand:
			commandHandled = HandleExitMenuItemSelectedL( aCommand );
			break;
    case ELightSave:
            commandHandled = HandleSaveL(aCommand);
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
void CLightManSetupListBoxView::DoActivateL( 
		const TVwsViewId& /*aPrevViewId*/,
		TUid /*aCustomMessageId*/,
		const TDesC8& /*aCustomMessage*/ )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	SetupStatusPaneL();
	
				
				
	
	if ( iLightManSetupListBox == NULL )
		{
		iLightManSetupListBox = CreateContainerL();
		iLightManSetupListBox->SetMopParent( this );
		AppUi()->AddToStackL( *this, iLightManSetupListBox );
		} 
	// ]]] end generated region [Generated Contents]
	
	}

/**
 */
void CLightManSetupListBoxView::DoDeactivate()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CleanupStatusPane();
	
	if ( iLightManSetupListBox != NULL )
		{
		AppUi()->RemoveFromViewStack( *this, iLightManSetupListBox );
		delete iLightManSetupListBox;
		iLightManSetupListBox = NULL;
		}
	// ]]] end generated region [Generated Contents]
	
	}

/** 
 * Handle status pane size change for this view (override)
 */
void CLightManSetupListBoxView::HandleStatusPaneSizeChange()
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
void CLightManSetupListBoxView::SetupStatusPaneL()
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
		iEikonEnv->CreateResourceReaderLC( reader, R_LIGHT_MAN_SETUP_LIST_BOX_TITLE_RESOURCE );
		title->SetFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
				
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
void CLightManSetupListBoxView::CleanupStatusPane()
	{
	}

// ]]] end generated function

/**
 *	Creates the top-level container for the view.  You may modify this method's
 *	contents and the CLightManSetupListBox::NewL() signature as needed to initialize the
 *	container, but the signature for this method is fixed.
 *	@return new initialized instance of CLightManSetupListBox
 */
CLightManSetupListBox* CLightManSetupListBoxView::CreateContainerL()
	{
	return CLightManSetupListBox::NewL( ClientRect(), NULL, this );
	}
void CLightManSetupListBoxView::CheckForm()
    {
        if(iNewForm != NULL)
            {
                delete iNewForm;
                iNewForm = NULL;
            }
    }

/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CLightManSetupListBoxView::HandleAddMenuItemSelectedL( TInt aCommand )
	{
	// TODO: implement selected event handler
        iNewForm = CMyForm::NewL();
        TBool err = iNewForm->ExecuteLD(R_MYFORM_FORM_DIALOG);
        if(!err)
            return ETrue;
        if(iLightManSetupListBox->GetListBoxItemCount() == 0)
            {
                MenuBar()->SetMenuTitleResourceId(R_LIGHT_MENUBAR_MAIN);
            }
    TInt length = 50;
    length += iNewForm->GetTime().Length();
    length += iNewForm->GetNote().Length();
    //HBufC* buf = HBufC::NewL(length);
    //buf->Des().Format(_L("%S\t%S\t%S\t%d"),*iTimeTitle,&iNewForm->GetTime(),*iLevelTitle,iNewForm->GetLevel());
    iLightManSetupListBox->AddListBoxItemL(iNewForm->GetTime(),iNewForm->GetLevel());
    iLightManSetupListBox->ListBox()->View()->SetCurrentItemIndex ( iLightManSetupListBox->ListBox()->Model()->NumberOfItems() - 1 );
    //CheckForm();
	return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CLightManSetupListBoxView::HandleChangeMenuItemSelectedL( TInt aCommand )
	{
	// TODO: implement selected event handler
        iNewForm = CMyForm::NewL();
        iNewForm->SetIsDef(EFalse);
        TInt currentItem = iLightManSetupListBox->ListBox()->CurrentItemIndex();
        TPtrC itemText(iLightManSetupListBox->ListBox()->Model()->ItemText(currentItem));
        RArray<TPtrC> arr;
        TChar ch;
        TLex lex(itemText);
        lex.Mark();
        while((ch = lex.Get()) != 0)
            {
                if(ch == '\t')
                    {
                        lex.UnGet();
                        arr.Append(lex.MarkedToken());
                        lex.Get();
                        lex.Mark();
                    }
            }
        arr.Append(lex.MarkedToken());
        iNewForm->SetTime(arr.operator [](1));
        iNewForm->SetLevel(arr.operator [](3));
        TBool err = iNewForm->ExecuteLD(R_MYFORM_FORM_DIALOG);
        //return ETrue;
        if(!err)
            return ETrue;
//        iLightManSetupListBox->DeleteItem();
        TInt length = 100;
        length += iNewForm->GetTime().Length();
        HBufC* buf = HBufC::NewL(length);
        buf->Des().Format(_L("Время\t%S\tУровень, %%\t%d"),&iNewForm->GetTime(),iNewForm->GetLevel());
        iLightManSetupListBox->EditListBoxItemL(*buf,currentItem);
        //iLightManSetupListBox->AddListBoxItemL(*buf);
        //iLightManSetupListBox->ListBox()->SetCurrentItemIndexAndDraw(currentItem);
        delete buf;
        //CheckForm();
    return ETrue;
	}
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CLightManSetupListBoxView::HandleDeleteMenuItemSelectedL( TInt aCommand )
	{
	// TODO: implement selected event handler
        iLightManSetupListBox->DeleteItem();
        if(iLightManSetupListBox->GetListBoxItemCount() == 0)
            {
                MenuBar()->SetMenuTitleResourceId(R_LIGHT_MENUBAR_ADD);
            }
	return ETrue;
    }
void CLightManSetupListBoxView::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane *aMenuPane)
    {
       /* if(aResourceId == R_LIGHT_MENU_ADD)
            {
                CEikMenuPaneItem::SData data;
                data.iText.Copy(_L("TEST"));
                data.iCommandId = ELightManSetupListBoxViewAddMenuItemCommand;
                data.iCascadeId=0;
                data.iFlags=0;
                data.iExtraText=KNullDesC;

                aMenuPane->AddMenuItemL(data);
            }*/
    }

/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CLightManSetupListBoxView::HandleAboutMenuItemSelectedL( TInt aCommand )
	{
	// TODO: implement selected event handler
        TInt val = 0;
        HAL::Get(HALData::ELanguageIndex,val);
        TBuf<256> string;
        if(val == 16)
            {
                //ru
                string = _L("LightMan поможет вам в управлении подсветкой смартфона\nАвтор: SQR\nsqr.1cs.su\nРоссия,2012");
            }else{
                //other
                string = _L("LightMan be help you to manage backlight on smartphone\nAutor:SQR\nsqr.1cs.su\nRussia,2012");
            }
        CAknMessageQueryDialog* dlg = new(ELeave) CAknMessageQueryDialog();
        dlg->PrepareLC(R_ABOUT_DIALOG);
        dlg->QueryHeading()->SetTextL(_L("LightManSetup"));
        dlg->SetMessageText(string);
        dlg->RunLD();
	return ETrue;
    }
				
/** 
 * Handle the selected event.
 * @param aCommand the command id invoked
 * @return ETrue if the command was handled, EFalse if not
 */
TBool CLightManSetupListBoxView::HandleExitMenuItemSelectedL( TInt aCommand )
	{
	// TODO: implement selected event handler
    AppUi()->Exit();
	return ETrue;
	}
				
TBool CLightManSetupListBoxView::HandleSaveL(TInt aCommand)
    {
        iLightManSetupListBox->SaveSettings();
        TryRun();
        return ETrue;
    }
void CLightManSetupListBoxView::TryRun()
    {
        RProcess proc;
        TInt err;
        err = proc.Create(_L("LightMan.exe"),KNullDesC);
        proc.Resume();
        proc.Close();
    }

