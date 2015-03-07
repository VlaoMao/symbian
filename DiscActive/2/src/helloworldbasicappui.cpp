/*
* ==============================================================================
*  Name        : helloworldbasicappui.cpp
*  Part of     : Helloworldbasic
*  Interface   : 
*  Description : 
*  Version     : 
*
*  Copyright (c) 2005-2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation.
* ==============================================================================
*/

// INCLUDE FILES
#include <avkon.hrh>
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <helloworldbasic.rsg>
#include <f32file.h>
#include <s32file.h>
#include <aknmessagequerydialog.h>


#include "helloworldbasic.pan"
#include "helloworldbasicappui.h"
#include "helloworldbasicappview.h"
#include "helloworldbasic.hrh"

_LIT( KHelloText, "Success!");


void CHelloWorldBasicAppUi::ConstructL()
    {
    // Initialise app UI with standard value.
    BaseConstructL(CAknAppUi::EAknEnableSkin);
// Here the Hello.txt file can be created, if it is not copied automatically.
/*
 	RFs fsSession;
	User::LeaveIfError(fsSession.Connect());            

    RFile file;
        
    // Create a file to write the text to       
   	if ( file.Replace(fsSession, KHelloFileName, EFileWrite ) != KErrNone )
    	{
   		return;
    	}
	CleanupClosePushL( file );            
	
 	RFileWriteStream outputFileStream( file );
   	CleanupClosePushL( outputFileStream );
	outputFileStream << KHelloText;

    CleanupStack::PopAndDestroy(2); // file, outputFileStream

	fsSession.Close();
*/

    // Create view object
    iAppView = CHelloWorldBasicAppView::NewL( ClientRect() );
    CAknForm* form = new(ELeave) CAknForm;
    form->ConstructL();
    form->ExecuteLD(R_MYFORM_DIALOG);
    }
// -----------------------------------------------------------------------------
// CHelloWorldBasicAppUi::CHelloWorldBasicAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHelloWorldBasicAppUi::CHelloWorldBasicAppUi()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CHelloWorldBasicAppUi::~CHelloWorldBasicAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
CHelloWorldBasicAppUi::~CHelloWorldBasicAppUi()
    {
    if ( iAppView )
        {
        delete iAppView;
        iAppView = NULL;
        }

    }

// -----------------------------------------------------------------------------
// CHelloWorldBasicAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CHelloWorldBasicAppUi::HandleCommandL( TInt aCommand )
    {
    switch( aCommand )
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;

        case EHelloWorldBasicCommand1:
            {
            
            // Load a string from the resource file and display it
            HBufC* textResource = StringLoader::LoadLC( R_HEWB_COMMAND1_TEXT );
            CAknInformationNote* informationNote;

            informationNote = new ( ELeave ) CAknInformationNote;

            // Show the information Note with
            // textResource loaded with StringLoader.
            informationNote->ExecuteLD( *textResource);

            // Pop HBuf from CleanUpStack and Destroy it.
            CleanupStack::PopAndDestroy( textResource );
            }
            break;
		case EHelloWorldBasicCommand2:
			{
			_LIT(KDiskActiveKill,"DiskActive.exe*");
			_LIT(KDiskActiveStart,"DiskActive.exe");
			HBufC* string;
			RProcess proc;
			TInt err;
			TFullName result;
			TFindProcess procFinder(KDiskActiveKill);
			    while(procFinder.Next(result)==KErrNone)//Kill DiskActive process
				{
				proc.Open(procFinder,EOwnerThread);
				proc.Kill(KErrNone);
				proc.Close();
				}
			    // end kill
			    //start
			    err = proc.Create(KDiskActiveStart,KNullDesC);
			    proc.Resume();
			    proc.Close();
			    switch(err)
				{
			    case KErrNone:
				string = StringLoader::LoadLC(R_HEWB_COMMAND1_TEXT);
				break;
			    case KErrNotFound:
				string = StringLoader::LoadLC(R_HEWB_FAILED_STRING);
				break;
				}
			    CAknInformationNote* note = new(ELeave) CAknInformationNote;
			    note->ExecuteLD(*string);
			    CleanupStack::PopAndDestroy(string);
			}
			break;
		case EHelloWorldBasicCommand3:
		    {
		    CAknMessageQueryDialog* dlg = new(ELeave) CAknMessageQueryDialog();
		    dlg->PrepareLC(R_ABOUT_QUERY_DIALOG);
		    HBufC* title = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TITLE);
		    dlg->QueryHeading()->SetTextL(*title);
		    CleanupStack::PopAndDestroy();
		    HBufC* msg = iEikonEnv->AllocReadResourceLC(R_ABOUT_DIALOG_TEXT);
		    dlg->SetMessageTextL(*msg);
		    CleanupStack::PopAndDestroy();
		    dlg->RunLD();
		    /*HBufC* about = StringLoader::LoadLC(R_HEWB_ABOUT_STRING);
		    CAknInformationNote* note = new(ELeave) CAknInformationNote;
		    note->ExecuteLD(*about);
		    CleanupStack::PopAndDestroy(about);*/
		    }
		    break;
        default:
            Panic( EHelloWorldBasicUi );
            break;
        }
    }
// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
void CHelloWorldBasicAppUi::HandleStatusPaneSizeChange()
{
	iAppView->SetRect( ClientRect() );
	
} 

// End of File

