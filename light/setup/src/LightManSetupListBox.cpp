/*
========================================================================
 Name        : LightManSetupListBox.cpp
 Author      : SQR
 Copyright   : 
 Description : 
========================================================================
*/
#include "LightManSetupListBox.h"

/**
 * First phase of Symbian two-phase construction. Should not 
 * contain any code that could leave.
 */
CLightManSetupListBox::CLightManSetupListBox()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	iListBox = NULL;
	// ]]] end generated region [Generated Contents]
	
	}
/** 
 * Destroy child controls.
 */
CLightManSetupListBox::~CLightManSetupListBox()
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	delete iListBox;
	iListBox = NULL;
    iListBoxEventDispatch.Close();
    delete iTimeTitle;
    delete iLevelTitle;
	// ]]] end generated region [Generated Contents]
	
    }
CTextListBoxModel* CLightManSetupListBox::GetModel()
    {
        return iListBox->Model();
    }

/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is not left on cleanup stack.
 * @param aRect bounding rectangle
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return initialized instance of CLightManSetupListBox
 */
CLightManSetupListBox* CLightManSetupListBox::NewL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver )
	{
	CLightManSetupListBox* self = CLightManSetupListBox::NewLC( 
			aRect, 
			aParent, 
			aCommandObserver );
	CleanupStack::Pop( self );
	return self;
	}

/**
 * Construct the control (first phase).
 *  Creates an instance and initializes it.
 *  Instance is left on cleanup stack.
 * @param aRect The rectangle for this window
 * @param aParent owning parent, or NULL
 * @param aCommandObserver command observer
 * @return new instance of CLightManSetupListBox
 */
CLightManSetupListBox* CLightManSetupListBox::NewLC( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver )
	{
	CLightManSetupListBox* self = new ( ELeave ) CLightManSetupListBox();
	CleanupStack::PushL( self );
	self->ConstructL( aRect, aParent, aCommandObserver );
	return self;
	}
			
/**
 * Construct the control (second phase).
 *  Creates a window to contain the controls and activates it.
 * @param aRect bounding rectangle
 * @param aCommandObserver command observer
 * @param aParent owning parent, or NULL
 */ 
void CLightManSetupListBox::ConstructL( 
		const TRect& aRect, 
		const CCoeControl* aParent, 
		MEikCommandObserver* aCommandObserver )
	{
	if ( aParent == NULL )
	    {
		CreateWindowL();
	    }
	else
	    {
	    SetContainerWindowL( *aParent );
	    }
	iFocusControl = NULL;
	iCommandObserver = aCommandObserver;
	InitializeControlsL();
	SetRect( aRect );
	ActivateL();
    CEikonEnv* eikonEnv = CEikonEnv::Static();
    iTimeTitle = StringLoader::LoadL(R_MAIN_TIME,eikonEnv);
    iLevelTitle = StringLoader::LoadL(R_MAIN_LEVEL,eikonEnv);

    User::LeaveIfError(iFs.Connect());
    LoadSettings();
    //AddListBoxItemL(iListBox,_L("12:30\t\tЗаметка\t100"));
	// [[[ begin generated region: do not modify [Post-ActivateL initializations]
	// ]]] end generated region [Post-ActivateL initializations]
	
	}
			
/**
* Return the number of controls in the container (override)
* @return count
*/
TInt CLightManSetupListBox::CountComponentControls() const
	{
	return ( int ) ELastControl;
	}
				
/**
* Get the control with the given index (override)
* @param aIndex Control index [0...n) (limited by #CountComponentControls)
* @return Pointer to control
*/
CCoeControl* CLightManSetupListBox::ComponentControl( TInt aIndex ) const
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	switch ( aIndex )
		{
	case EListBox:
		return iListBox;
		}
	// ]]] end generated region [Generated Contents]
	
	// handle any user controls here...
	
	return NULL;
	}
				
/**
 *	Handle resizing of the container. This implementation will lay out
 *  full-sized controls like list boxes for any screen size, and will layout
 *  labels, editors, etc. to the size they were given in the UI designer.
 *  This code will need to be modified to adjust arbitrary controls to
 *  any screen size.
 */				
void CLightManSetupListBox::SizeChanged()
	{
	CCoeControl::SizeChanged();
	LayoutControls();
	// [[[ begin generated region: do not modify [Generated Contents]
			
	// ]]] end generated region [Generated Contents]
	
	}
				
// [[[ begin generated function: do not modify
/**
 * Layout components as specified in the UI Designer
 */
void CLightManSetupListBox::LayoutControls()
	{
	iListBox->SetExtent( TPoint( 0, 0 ), iListBox->MinimumSize() );
	}
// ]]] end generated function

/**
 *	Handle key events.
 */				
TKeyResponse CLightManSetupListBox::OfferKeyEventL( 
		const TKeyEvent& aKeyEvent, 
		TEventCode aType )
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	if ( aKeyEvent.iCode == EKeyLeftArrow 
		|| aKeyEvent.iCode == EKeyRightArrow )
		{
		// Listbox takes all events even if it doesn't use them
		return EKeyWasNotConsumed;
		}
	
	// ]]] end generated region [Generated Contents]
	
	if ( iFocusControl != NULL
		&& iFocusControl->OfferKeyEventL( aKeyEvent, aType ) == EKeyWasConsumed )
		{
		return EKeyWasConsumed;
		}
	return CCoeControl::OfferKeyEventL( aKeyEvent, aType );
	}
				
// [[[ begin generated function: do not modify
/**
 *	Initialize each control upon creation.
 */				
void CLightManSetupListBox::InitializeControlsL()
	{
    iListBox = new ( ELeave ) CAknDoubleTimeStyleListBox;
	iListBox->SetContainerWindowL( *this );
		{
		TResourceReader reader;
		iEikonEnv->CreateResourceReaderLC( reader, R_LIGHT_MAN_SETUP_LIST_BOX_LIST_BOX );
		iListBox->ConstructFromResourceL( reader );
		CleanupStack::PopAndDestroy(); // reader internal state
		}
	// the listbox owns the items in the list and will free them
	iListBox->Model()->SetOwnershipType( ELbmOwnsItemArray );
	
	// setup the icon array so graphics-style boxes work
	SetupListBoxIconsL();
	
	iListBox->SetListBoxObserver( this );
	AddListBoxEventHandlerL( 
			iListBox, 
			EEventItemClicked, 
			&CLightManSetupListBox::HandleListBoxItemClickedL );
	
	// add list items
	
	iListBox->SetFocus( ETrue );
	iFocusControl = iListBox;

	}
// ]]] end generated function

/** 
 * Handle global resource changes, such as scalable UI or skin events (override)
 */
void CLightManSetupListBox::HandleResourceChange( TInt aType )
	{
	CCoeControl::HandleResourceChange( aType );
	SetRect( iAvkonViewAppUi->View( TUid::Uid( ELightManSetupListBoxViewId ) )->ClientRect() );
	// [[[ begin generated region: do not modify [Generated Contents]
	// ]]] end generated region [Generated Contents]
	
	}
				
/**
 *	Draw container contents.
 */				
void CLightManSetupListBox::Draw( const TRect& aRect ) const
	{
	// [[[ begin generated region: do not modify [Generated Contents]
	CWindowGc& gc = SystemGc();
	gc.Clear( aRect );
	
	// ]]] end generated region [Generated Contents]
	
	}
				
// [[[ begin generated function: do not modify
/**
 *	Add a list box item to a list.
 */
void CLightManSetupListBox::AddListBoxItemL( 
		CEikTextListBox* aListBox,
		const TDesC& aString )
	{
	CTextListBoxModel* model = aListBox->Model();
	CDesCArray* itemArray = static_cast< CDesCArray* > ( model->ItemTextArray() );
	itemArray->AppendL( aString );
	aListBox->HandleItemAdditionL();
	}

void CLightManSetupListBox::AddListBoxItemL(const TDesC& aString )
    {
    CTextListBoxModel* model = iListBox->Model();
    CDesCArray* itemArray = static_cast< CDesCArray* > ( model->ItemTextArray() );
    itemArray->AppendL( aString );
    iListBox->HandleItemAdditionL();
    }
void CLightManSetupListBox::AddListBoxItemL(const TDesC &aTime, const TDesC &aLevel)
    {
        TInt length = 50;
        length += aTime.Length();
        HBufC* buf = HBufC::NewL(length);
        buf->Des().Format(_L("%S\t%S\t%S\t%S"),iTimeTitle,&aTime,iLevelTitle,&aLevel);
        AddListBoxItemL(*buf);
    }
void CLightManSetupListBox::AddListBoxItemL(const TDesC &aTime, const TInt aLevel)
    {
        //iEikonEnv->InfoWinL(_L("AddListBoxItemL"),_L("TDesC TInt"));
        TInt length = 50;
        length += aTime.Length();
        HBufC* buf = HBufC::NewL(length);
        buf->Des().Format(_L("%S\t%S\t%S\t%d"),iTimeTitle,&aTime,iLevelTitle,aLevel);
        AddListBoxItemL(*buf);
    }

void CLightManSetupListBox::EditListBoxItemL(const TDesC& aString, TInt aPos )
    {
        DeleteItem(aPos);
        CTextListBoxModel* model = iListBox->Model();
        CDesCArray* itemArray = static_cast< CDesCArray* > ( model->ItemTextArray() );
        itemArray->InsertL(aPos,aString);
        iListBox->HandleItemAdditionL();
    }

// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Get the array of selected item indices, with respect to the list model.
 * The array is sorted in ascending order.
 * The array should be destroyed with two calls to CleanupStack::PopAndDestroy(),
 * the first with no argument (referring to the internal resource) and the
 * second with the array pointer.
 * @return newly allocated array, which is left on the cleanup stack;
 *	or NULL for empty list. 
 */
RArray< TInt >* CLightManSetupListBox::GetSelectedListBoxItemsLC( CEikTextListBox* aListBox )
	{
	CAknFilteredTextListBoxModel* model = 
		static_cast< CAknFilteredTextListBoxModel *> ( aListBox->Model() );
	if ( model->NumberOfItems() == 0 )
		return NULL;
		
	// get currently selected indices
	const CListBoxView::CSelectionIndexArray* selectionIndexes =
		aListBox->SelectionIndexes();
	TInt selectedIndexesCount = selectionIndexes->Count();
	if ( selectedIndexesCount == 0 )
		return NULL;
		
	// copy the indices and sort numerically
	RArray<TInt>* orderedSelectedIndices = 
		new (ELeave) RArray< TInt >( selectedIndexesCount );
	
	// push the allocated array
	CleanupStack::PushL( orderedSelectedIndices );
	
	// dispose the array resource
	CleanupClosePushL( *orderedSelectedIndices );
	
	// see if the search field is enabled
	CAknListBoxFilterItems* filter = model->Filter();
	if ( filter != NULL )
		{
		// when filtering enabled, translate indices back to underlying model
		for ( TInt idx = 0; idx < selectedIndexesCount; idx++ )
			{
			TInt filteredItem = ( *selectionIndexes ) [ idx ];
			TInt actualItem = filter->FilteredItemIndex ( filteredItem );
			orderedSelectedIndices->InsertInOrder( actualItem );
			}
		}
	else
		{
		// the selection indices refer directly to the model
		for ( TInt idx = 0; idx < selectedIndexesCount; idx++ )
			orderedSelectedIndices->InsertInOrder( ( *selectionIndexes ) [ idx ] );
		}	
		
	return orderedSelectedIndices;
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 * Delete the selected item or items from the list box.
 */
void CLightManSetupListBox::DeleteSelectedListBoxItemsL( CEikTextListBox* aListBox )
	{
	CAknFilteredTextListBoxModel* model = 
		static_cast< CAknFilteredTextListBoxModel *> ( aListBox->Model() );
	if ( model->NumberOfItems() == 0 )
		return;
	
	RArray< TInt >* orderedSelectedIndices = GetSelectedListBoxItemsLC( aListBox );		
	if ( !orderedSelectedIndices )
		return;
		
	// Delete selected items from bottom up so indices don't change on us
	CDesCArray* itemArray = static_cast< CDesCArray* > ( model->ItemTextArray() );
	TInt currentItem = 0;
	
	for ( TInt idx = orderedSelectedIndices->Count(); idx-- > 0; ) 
		{
		currentItem = ( *orderedSelectedIndices )[ idx ];
		itemArray->Delete ( currentItem );
		}
	
	// dispose the array resources
	CleanupStack::PopAndDestroy();
	
	// dispose the array pointer
	CleanupStack::PopAndDestroy( orderedSelectedIndices );
	
	// refresh listbox's cursor now that items are deleted
	AknListBoxUtils::HandleItemRemovalAndPositionHighlightL(
		aListBox, currentItem, ETrue );
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Get the listbox.
 */
CAknDoubleTimeStyleListBox* CLightManSetupListBox::ListBox()
	{
	return iListBox;
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Create a list box item with the given column values.
 */
void CLightManSetupListBox::CreateListBoxItemL( TDes& aBuffer, 
		const TDesC& aTime1Text,
		const TDesC& aTime2Text,
		const TDesC& aMainText,
		const TDesC& aSecondaryText )
	{
	_LIT ( KStringHeader, "%S\t%S\t%S\t%S" );
	
	aBuffer.Format( KStringHeader(), &aTime1Text, &aTime2Text, &aMainText, &aSecondaryText );
	} 
				
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Add an item to the list by reading the text items from the array resource
 *	and setting a single image property (if available) from an index
 *	in the list box's icon array.
 *	@param aResourceId id of an ARRAY resource containing the textual
 *	items in the columns
 *	
 */
void CLightManSetupListBox::AddListBoxResourceArrayItemL( TInt aResourceId )
	{
	CDesCArray* array = iCoeEnv->ReadDesCArrayResourceL( aResourceId );
	CleanupStack::PushL( array );
	// This is intended to be large enough, but if you get 
	// a USER 11 panic, consider reducing string sizes.
	TBuf<512> listString; 
	CreateListBoxItemL( listString, ( *array ) [ 0 ], ( *array ) [ 1 ], 
			( *array ) [ 2 ], ( *array ) [ 3 ] );
    AddListBoxItemL( iListBox, listString );
	CleanupStack::PopAndDestroy( array );
	} 
				
// ]]] end generated function

// [[[ begin generated function: do not modify
/**
 *	Set up the list's icon array.
 */
void CLightManSetupListBox::SetupListBoxIconsL()
	{
    CAknIconArray* iconArray = new( ELeave ) CAknIconArray( 1 );
    CleanupStack::PushL( iconArray );
    CFbsBitmap* checkboxOnBitmap = NULL;
    CFbsBitmap* checkboxOnBitmapMask = NULL;
    CFbsBitmap* checkboxOffBitmap = NULL;
    CFbsBitmap* checkboxOffBitmapMask = NULL;
    
    
    //CListItemDrawer is using this logical color as default for its marked icons
    TRgb defaultColor;
    defaultColor = CEikonEnv::Static()->Color( EColorControlText );

    AknsUtils::CreateColorIconLC( AknsUtils::SkinInstance(),
    			KAknsIIDQgnPropCheckboxOff,
    			KAknsIIDQsnIconColors,
    			EAknsCIQsnIconColorsCG13,
    			checkboxOnBitmap,
    			checkboxOnBitmapMask,
    			KAvkonBitmapFile,
    			EMbmAvkonQgn_indi_checkbox_on,
    			EMbmAvkonQgn_indi_checkbox_on_mask,
    			defaultColor
    			);
    			
    CGulIcon* checkboxOnIcon = CGulIcon::NewL( checkboxOnBitmap, checkboxOnBitmapMask );
    CleanupStack::Pop( 2 ); // checkboxOnBitmap, checkboxOnBitmapMask
    CleanupStack::PushL( checkboxOnIcon );
    iconArray->AppendL( checkboxOnIcon );

    AknsUtils::CreateColorIconLC( AknsUtils::SkinInstance(),
    			KAknsIIDQgnPropCheckboxOff,
    			KAknsIIDQsnIconColors,
    			EAknsCIQsnIconColorsCG13,
    			checkboxOffBitmap,
    			checkboxOffBitmapMask,
    			KAvkonBitmapFile,
    			EMbmAvkonQgn_indi_checkbox_off,
    			EMbmAvkonQgn_indi_checkbox_off_mask,
    			defaultColor
    			);
    			    
    CGulIcon* checkboxOffIcon = CGulIcon::NewL( checkboxOffBitmap, checkboxOffBitmapMask );
    CleanupStack::Pop( 2 ); // checkboxOffBitmap, checkboxOffBitmapMask    
    CleanupStack::PushL( checkboxOffIcon );
    iconArray->AppendL( checkboxOffIcon );
        
    iListBox->ItemDrawer()->ColumnData()->SetIconArray( iconArray );
    
    // checkboxOffIcon, checkboxOnIcon, iconArray
    CleanupStack::Pop( 3 );
	}

// ]]] end generated function

// [[[ begin generated function: do not modify
/** 
 *	Handle commands relating to markable lists.
 */
TBool CLightManSetupListBox::HandleMarkableListCommandL( TInt aCommand )
	{
	return EFalse;
	}

// ]]] end generated function

/** 
 * Override of the HandleListBoxEventL virtual function
 */
void CLightManSetupListBox::HandleListBoxEventL( 
		CEikListBox* aListBox,
		TListBoxEvent anEventType )
	{
	for (int i = 0; i < iListBoxEventDispatch.Count(); i++)
		{
		const TListBoxEventDispatch& currEntry = iListBoxEventDispatch[i];
		if ( currEntry.src == aListBox && currEntry.event == anEventType )
			{
			( this->*currEntry.handler )( aListBox, anEventType );
			break;
			}
		}
	}

/** 
 * Helper function to register MEikListBoxObserver event handlers
 */
void CLightManSetupListBox::AddListBoxEventHandlerL( 
		CEikListBox* aListBox,
		TListBoxEvent anEvent,
		ListBoxEventHandler aHandler )
	{
	TListBoxEventDispatch entry;
	entry.src = aListBox;
	entry.event = anEvent;
	entry.handler = aHandler;
	TInt err = iListBoxEventDispatch.Append( entry );
	User::LeaveIfError( err );
	}

/**
 *	Handle the itemClicked event
 */
void CLightManSetupListBox::HandleListBoxItemClickedL( 
		CEikListBox* aListBox,
		TListBoxEvent anEventType )
	{
/*	// TODO: implement itemClicked event handler
    TBuf<20> buf;
	buf.AppendNum(iListBox->SelectionIndexes()->Count());
	CEikonEnv::Static()->InfoWinL(_L("Selection indexes:"), buf);
    iListBox->View()->SelectItemL(iListBox->CurrentItemIndex());*/

	}

void CLightManSetupListBox::DeleteItem()
    {
        MDesCArray* textArray = iListBox->Model()->ItemTextArray();
        CDesCArray* itemList = static_cast<CDesCArray*>(textArray);
        if(itemList->Count() > 0)
            {
            itemList->Delete(iListBox->CurrentItemIndex(), 1); // удалить один элемент с индексом 0
            iListBox->HandleItemRemovalL();
            }
    }
void CLightManSetupListBox::DeleteItem(TInt aPos)
    {
        MDesCArray* textArray = iListBox->Model()->ItemTextArray();
        CDesCArray* itemList = static_cast<CDesCArray*>(textArray);
        if(itemList->Count() > 0)
            {
            itemList->Delete(aPos, 1); // удалить один элемент с индексом 0
            iListBox->HandleItemRemovalL();
            }
    }

TInt CLightManSetupListBox::GetListBoxItemCount()
    {
        MDesCArray* textArray = iListBox->Model()->ItemTextArray();
        CDesCArray* itemList = static_cast<CDesCArray*>(textArray);
        iCount = itemList->Count();
        return iCount;
    }
void CLightManSetupListBox::LoadSettings()
    {
        TBuf<256> buf;
        if(iFile.Open(iFs,KBaseConfSettingsPath,EFileWrite | EFileRead) != KErrNone)
            {
                User::LeaveIfError(iFile.Replace(iFs,KBaseConfSettingsPath,EFileWrite | EFileRead));
                iFile.Write(0,_L8("\xff\xfe"));//signature
                iText.Set(iFile);
                iText.Write(_L("00:00 - 100\r\n"));//default config
                iFile.Close();
                LoadSettings();
            }
        iText.Set(iFile);
        TBuf<20> time;
        TBuf<20> percent;
        while(iText.Read(buf) == KErrNone)
            {
                //__L1("Read buf: %S",&iBuf);
                TInt posFound = buf.Find(KSeparator);
                if( posFound != KErrNotFound)
                    {
                        time = buf.Left(posFound);
                        percent = buf.Right(buf.Length()-(posFound+3));
                        //iEikonEnv->InfoWinL(time,percent);
                        AddListBoxItemL((TDesC&)time,(TDesC&)percent);
                    }
            }
         iFile.Close();
    }
void CLightManSetupListBox::SaveSettings()
    {
        if(iFile.Replace(iFs,KBaseConfSettingsPath,EFileWrite | EFileRead) != KErrNone)
            {
                ShowNoteL(EAknGlobalErrorNote,R_SAVE_FAILED);
                return ;
            }
        iFile.Write(0,_L8("\xff\xfe"));//signature
        iText.Set(iFile);
        TInt count = GetListBoxItemCount();
        for(TInt i = 0; i < count ;++i)
            {
                GetListBoxItem(iListBoxItemFormatted,i);
                iText.Write(iListBoxItemFormatted);
            }
        //iText.Write(_L("00:00 - 100\r\n"));//default config
        iFile.Close();
        ShowNoteL(EAknGlobalInformationNote,R_SAVE_SUCCESS);
    }
void CLightManSetupListBox::ShowNoteL(TAknGlobalNoteType aType, TInt aResourceId)
    {
        CAknGlobalNote* note = CAknGlobalNote::NewL();
        TInt noteId;
        HBufC* string = StringLoader::LoadL(aResourceId,iEikonEnv->Static());
        noteId = note->ShowNoteL(aType,*string);
        User::After(2000000);
        note->CancelNoteL(noteId);
        delete note;
        delete string;
    }

void CLightManSetupListBox::GetListBoxItem(TDes &aDes, TInt aCount)
    {
    TPtrC itemText(ListBox()->Model()->ItemText(aCount));
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
    aDes.Zero();
    aDes.Format(_L("%S - %S"),&arr.operator [](1),&arr.operator [](3));
    }
