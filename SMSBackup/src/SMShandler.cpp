// INCLUDE FILES
#include <eikenv.h>
#include <coemain.h>
#include <e32std.h>
#include <msvids.h>
#include <msvstd.h>
#include <smsclnt.h>
#include <smut.h>
#include <mtclreg.h>
#include <txtrich.h>
#include <smscmds.h>
#include <mtmuibas.h>
#include <mtmdef.h>
#include <stringloader.h>
#include "SMShandler.h"
#include "smutset.h"
#include "smuthdr.h"



// ============================ MEMBER FUNCTIONS ===============================
// -----------------------------------------------------------------------------
// CSmsHandler::CSmsHandler()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CSmsHandler::CSmsHandler()
: CActive( CActive::EPriorityStandard )
    {
    CActiveScheduler::Add( this );
    iNextUnread = 0;            // index of next unread message in iSelection
    }

// -----------------------------------------------------------------------------
// CSmsHandler::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CSmsHandler::ConstructL()
    {
	__CH__NEW__();
 // Session to message server is opened synchronously.
    iSession = CMsvSession::OpenSyncL( *this );

    iMtmRegistry = CClientMtmRegistry::NewL(*iSession);
    //iMtm = iMtmRegistry->NewMtmL(KUidMsgTypeSMS);
    iSmsMtm = STATIC_CAST(CSmsClientMtm*,iMtmRegistry->NewMtmL(KUidMsgTypeSMS));
    
    // Entry selection for all received messages.
    iSelection = new ( ELeave ) CMsvEntrySelection();
    RFs fs;
    User::LeaveIfError(fs.Connect());
    RFile file;
    if(file.Open(fs,KWorkFilePath,EFileWrite) != KErrNone)
    	{
    	ReadInboxMsgs();
    	ReadSentMsgs();
    	}else{
    		file.Close();
    	}
    fs.Close();
    }

// -----------------------------------------------------------------------------
// CSmsHandler::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSmsHandler* CSmsHandler::NewL( )
    {
    CSmsHandler* self = NewLC( );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CSmsHandler::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CSmsHandler* CSmsHandler::NewLC()
    {
    CSmsHandler* self = new ( ELeave ) CSmsHandler();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------
// CSmsHandler::~CSmsHandler()
// Destructor.
// ----------------------------------------------------------
//
CSmsHandler::~CSmsHandler()
    {
    Cancel();           // cancel any outstanding request

    delete iOperation;
    delete iMtmUiRegistry;
    delete iSelection;
	delete iSmsMtm;
    delete iMtmRegistry;
    delete iSession;    // session must be deleted last
    }

// -----------------------------------------------------------------------------
// CSmsHandler::DoCancel()
// Cancels a request.
// -----------------------------------------------------------------------------
//
void CSmsHandler::DoCancel()
    {
    if ( iOperation )
        {
        iOperation->Cancel();
        }
    }

// -----------------------------------------------------------------------------
// CSmsHandler::RunL()
// Handles request completion events.
// -----------------------------------------------------------------------------
//
void CSmsHandler::RunL()
    {
    User::LeaveIfError( iStatus != KErrNone );

    // Determine the current operations progress.
    // ProgressL returns an 8 bit descriptor.
    TBufC8<KMsvProgressBufferLength> progress( iOperation->ProgressL() );
    _LIT8( KCompare, "KErrNone" );
    User::LeaveIfError( !progress.Compare( KCompare ) );

    // The pointer to the current CMsvOperation object is no longer needed.
    delete iOperation;
    iOperation = NULL;

	__LOGSTR1("CSMSHandler::RunL,iState: %d",iState);
    // Determine which request has finished.
    switch ( iState )
        {
        case EWaitingForMoving:
            // Once a message is moved to Outbox it is scheduled for sending.
            ScheduleL();
            break;

        case EWaitingForScheduling:
            {
            TMsvEntry entry( iSmsMtm->Entry().Entry() );
            TInt state( entry.SendingState() );

            if ( state == KMsvSendStateWaiting || state == KMsvSendStateScheduled)
                {
                }

            break;
            }

        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CSmsHandler::HandleSessionEventL()
// Handles notifications of events from the Message Server.
// -----------------------------------------------------------------------------
//
void CSmsHandler::HandleSessionEventL( TMsvSessionEvent aEvent,
                                      TAny* aArg1, TAny* aArg2, TAny* aArg3)
	{
	__LOGSTR1("HandleSessionEventL,event: %d",aEvent);
	switch ( aEvent )
		{
        // Session to server established
		case EMsvServerReady:
            {
            TMsvId serviceId( KUidMsgTypeSMS.iUid ); // SMS service id

            // Determine if the event was succesful.
            // ServiceProgress inserts TBuf8 value in progress.
            TBuf8<KBfrLength> progress;
			iSession->ServiceProgress( serviceId, progress );
			_LIT8( KCompare, "KErrNone" );

			if ( progress.Compare( KCompare ) )
				{
                // Check that MtmRegistry has not already been accessed.
                if ( !iMtmRegistry )
                    {
                    AccessMtmL();
                    }
                }
            break;
            }

        // A new entry has been created on the message server.
        case EMsvEntriesCreated:
            {
            // Entry id is obtained from the session event arguments.
            TMsvId* entryId = STATIC_CAST( TMsvId*, aArg2 );

            // We are interested in messages that are created in Inbox.
            __LOGSTR1("entryId where message created: 0x%x",*entryId);
            if ( *entryId == KMsvGlobalInBoxIndexEntryId )
                {
            	__LOGSTR("Inbox message");
            	// We take the created entries into a selection
            	            CMsvEntrySelection* newEntries =
            	                STATIC_CAST( CMsvEntrySelection*, aArg1 );

            	            // Process each created entry.
            	            __LOGSTR1("CMsvEntrySelection count: %d",newEntries->Count());
            	            __LOGSTR1("iDetails: %S",&( iSession->GetEntryL( newEntries->At( 0 ) ) )->Entry().iDetails);
            	            for ( TInt i( 0 ); i < newEntries->Count(); i++ )
            	                {
            	                // We are interested in SMS messages.
            	                if ( ( iSession->GetEntryL( newEntries->At( i ) ) )
            	                    ->Entry().iMtm == KUidMsgTypeSMS )
            	                    {
            	                    // Add the entry to the selection of all received messages.
            	                    iSelection->AppendL( newEntries->At( i ), 1 );

            	                    // Set received messages visible.
            	                    MessageReceivedL( newEntries->At( i ) );
            	                    }
            	                }
                }
            if( *entryId == KMsvSentEntryId)
            	{
            	__LOGSTR("Sent message");
            	TMsvId* newEntryId = STATIC_CAST(TMsvId*,aArg2);
            	__LOGSTR1("EMsvEntriesMoved, new folder id: 0x%x",newEntryId);
            	CMsvEntrySelection* newEntries =
            	                STATIC_CAST( CMsvEntrySelection*, aArg1 );
                if ( ( iSession->GetEntryL( newEntries->At( 0 ) ) )
                    ->Entry().iMtm == KUidMsgTypeSMS )
                    {
                    // Add the entry to the selection of all received messages.
                    iSelection->AppendL( newEntries->At( 0 ), 1 );

                    // Set received messages visible.
                    MessageSent( newEntries->At( 0 ) );
            	}


            break;
            }
            }
        case EMsvEntriesMoved:
        	{
        /*	__LOGSTR2("Entries moved from 0x%x to 0x%x",aArg3,aArg2);
        	if((TInt32)aArg3 == 0x411db4)
        		{
        		if((TInt32)aArg2 == 0x411db8)
        			{
                	__LOGSTR("Sent message");
                	TMsvId* newEntryId = STATIC_CAST(TMsvId*,aArg2);
                	__LOGSTR1("EMsvEntriesMoved, new folder id: 0x%x",newEntryId);
                	CMsvEntrySelection* newEntries =
                	                STATIC_CAST( CMsvEntrySelection*, aArg1 );
                    if ( ( iSession->GetEntryL( newEntries->At( 0 ) ) )
                        ->Entry().iMtm == KUidMsgTypeSMS )
                        {
                        // Add the entry to the selection of all received messages.
                        iSelection->AppendL( newEntries->At( 0 ), 1 );

                        // Set received messages visible.
                        MessageSent( newEntries->At( 0 ) );
                        }
        			}
        		}
        	break;*/
        	}
        case EMsvCloseSession:
        case EMsvServerTerminated:
        case EMsvGeneralError:
        case EMsvServerFailedToStart:
            {
//            iSmsAppUi->ServerDown( aEvent );    // close application
            break;
            }

        // All other events are ignored.
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CSmsHandler::AccessMtmL()
// Access the MTM Registry and create a SMS specific Client MTM instance.
// -----------------------------------------------------------------------------
//
void CSmsHandler::AccessMtmL()
	{
    // Create an MTM Registry object.
    iMtmRegistry = CClientMtmRegistry::NewL( *iSession );

    // Create an SMS Client MTM object.
    iSmsMtm = STATIC_CAST( CSmsClientMtm*, iMtmRegistry->NewMtmL( KUidMsgTypeSMS ) );
    }

// -----------------------------------------------------------------------------
// CSmsHandler::SendL()
// Starts the process of creating and sending an SMS message.
// -----------------------------------------------------------------------------
//
TBool CSmsHandler::SendL( const TDesC& aRecipientNumber,
                            const TDesC& aMessageText )
    {
    iRecipientNumber = aRecipientNumber;
    iMessageText = aMessageText;

    if ( CreateMsgL() )
        {
        return ETrue;
        }

    return EFalse;
    }

// -----------------------------------------------------------------------------
// CSmsHandler::CreateMsgL()
// Create an SMS message.
// -----------------------------------------------------------------------------
//
TBool CSmsHandler::CreateMsgL()
    {
    // Current entry is the Draft folder.
    iSmsMtm->SwitchCurrentEntryL( KMsvDraftEntryId );

    // Create a new SMS message entry as a child of the current context.
    iSmsMtm->CreateMessageL( KUidMsgTypeSMS.iUid );

    CMsvEntry& serverEntry = iSmsMtm->Entry();
    TMsvEntry entry( serverEntry.Entry() );

    CRichText& body = iSmsMtm->Body();   // the body of the message
    body.Reset();
    // Insert the message text gotten as input from user.
    body.InsertL( 0, iMessageText );

    // Message will be sent immediately.
    entry.SetSendingState( KMsvSendStateWaiting );

//Added by Kiran:for 3rd edition
//    entry.iDate.HomeTime(); // insert current time //This was causing problem:SMS stays into Outbox only.
	entry.iDate.UniversalTime(); // insert current time //Solution for HomeTime()
//Code Ends-Kiran
    // Set the SMS message settings for the message.
    CSmsHeader& header = iSmsMtm->SmsHeader();
    CSmsSettings* settings = CSmsSettings::NewL();
    CleanupStack::PushL( settings );

    settings->CopyL( iSmsMtm->ServiceSettings() );    // restore settings
    settings->SetDelivery( ESmsDeliveryImmediately ); // to be delivered immediately
	settings->SetDeliveryReport(ETrue);
    header.SetSmsSettingsL( *settings );              // new settings

	// Let's check if there is a service center address.
	if ( header.Message().ServiceCenterAddress().Length() == 0 )
		{
		// No, there isn't. We assume there is at least one service center
        // number set and use the default service center number.
		CSmsSettings* serviceSettings = &( iSmsMtm->ServiceSettings() );

        // Check if number of service center addresses in the list is null.

//Changed for 3rd Edition specially- Kiran - 30-10-06
//        if ( !serviceSettings->NumSCAddresses() )
		if ( !serviceSettings->ServiceCenterCount() )
            {
			return EFalse;     // quit creating the message
            }

		else
			{
//Changed for 3rd Edition specially- Kiran - 30-10-06
//          CSmsNumber* smsCenter = &( serviceSettings->SCAddress( serviceSettings->DefaultSC() ) );
				CSmsNumber* smsCenter= CSmsNumber::NewL();
				CleanupStack::PushL(smsCenter);
				smsCenter->SetAddressL((serviceSettings->GetServiceCenter( serviceSettings->DefaultServiceCenter())).Address());
				header.Message().SetServiceCenterAddressL( smsCenter->Address() );
				CleanupStack::PopAndDestroy(smsCenter);
		    }
        }

	CleanupStack::PopAndDestroy( settings );

    // Recipient number is displayed also as the recipient alias.
    entry.iDetails.Set( iRecipientNumber );
    // Add addressee.
    iSmsMtm->AddAddresseeL( iRecipientNumber, entry.iDetails );

    // Validate message.
    if ( !ValidateL() )
        {
        return EFalse;
        }

    entry.SetVisible( ETrue );          // set message as visible
    entry.SetInPreparation( EFalse );   // set together with the visibility flag
    serverEntry.ChangeL( entry );       // commit changes		
    iSmsMtm->SaveMessageL();            // save message

    TMsvSelectionOrdering selection;
	CMsvEntry* parentEntry = CMsvEntry::NewL( iSmsMtm->Session(), KMsvDraftEntryId, selection );
    CleanupStack::PushL( parentEntry );

    // Move message to Outbox.
    iOperation =parentEntry->MoveL( entry.Id(), KMsvGlobalOutBoxIndexEntryId, iStatus );

    CleanupStack::PopAndDestroy( parentEntry );

    iState = EWaitingForMoving;
    SetActive();

    return ETrue;
  }

// -----------------------------------------------------------------------------
// CSmsHandler::ValidateL()
// Validate an SMS message.
// -----------------------------------------------------------------------------
//
TBool CSmsHandler::ValidateL()
    {
    // Empty part list to hold the result.
    TMsvPartList result( KMsvMessagePartNone );

    // Validate message body.
    result = iSmsMtm->ValidateMessage( KMsvMessagePartBody );

    if ( result != KMsvMessagePartNone )
        {
        return EFalse;
        }

    // Validate recipient.
    result = iSmsMtm->ValidateMessage( KMsvMessagePartRecipient );

    if ( result != KMsvMessagePartNone )
        {
        return EFalse;
        }

    return ETrue;
    }

// -----------------------------------------------------------------------------
// CSmsHandler::ScheduleL()
// Schedule an SMS message for sending.
// -----------------------------------------------------------------------------
//
void CSmsHandler::ScheduleL()
    {
    CMsvEntrySelection* selection = new ( ELeave ) CMsvEntrySelection;
    CleanupStack::PushL( selection );
    selection->AppendL( iSmsMtm->Entry().EntryId() ); // add message to selection

    // Add entry to task scheduler.
    TBuf8<1> dummyParams;   // dummy parameters needed for InvokeAsyncFunctionL
    iOperation = iSmsMtm->InvokeAsyncFunctionL( ESmsMtmCommandScheduleCopy,
                          *selection, dummyParams, iStatus );

    CleanupStack::PopAndDestroy( selection );

    iState = EWaitingForScheduling;
    SetActive();
    }

// -----------------------------------------------------------------------------
// CSmsHandler::MessageReceivedL()
// Handles a received SMS message.
// -----------------------------------------------------------------------------
//
void CSmsHandler::MessageReceivedL( TMsvId aEntryId )
    {
	__LOGSTR("MessageReceivedL");
	CMsvEntry* serverEntry = iSession->GetEntryL( aEntryId );   // current entry
	CleanupStack::PushL( serverEntry );
	TMsvEntry entry = serverEntry->Entry(); // currently handled message entry

	//entry.SetNew( ETrue );
	//entry.SetUnread( ETrue );
	//entry.SetVisible( ETrue );

	//serverEntry->ChangeL( entry );  // commit changes

	//Added to retrieve message body
	HBufC16* SMSContent = HBufC16::NewLC(400);
    TBuf16<30> name;
	name.Copy(KMessName);
	name.Append(entry.iDetails);

	//Added to retrieve Phone Number of the Sender
	iSmsMtm->SwitchCurrentEntryL(aEntryId);
	iSmsMtm->LoadMessageL();
	CSmsHeader& header = iSmsMtm->SmsHeader();

    /* This will give you actual phone number irrespective of the name of contact*/
    TPtrC from = header.FromAddress();
    TBuf16<60> number;
    number.Copy(KMessNumber);
    number.Append(from);

	TTime utc(entry.iDate);
	RTz tzServer;
	User::LeaveIfError(tzServer.Connect());
	CTzConverter* tzConverter = CTzConverter::NewL(tzServer);
	__LOGSTR1("Convert to local time: %d",tzConverter->ConvertToLocalTime(utc));

    TBuf<60> date;
    TDateTime dateTime(utc.DateTime());
    //date.Format(KTimeFormat,dateTime.Day()+1,TInt(dateTime.Month()+1),dateTime.Year(),dateTime.Hour(),dateTime.Minute(),dateTime.Second());
    utc.FormatL(date,KDateConstFormat);
    date.Insert(0,KMessDate);
   /* To read phone number from Sent Item folder, see the Note below */

    CRichText& richText= iSmsMtm->Body();
    //inboxStore->RestoreBodyTextL(richText);
    const TInt length = richText.DocumentLength();

    /* Gives you actual content(Body) of SMS */
    SMSContent->Des().Copy(KMessMess);
    SMSContent->Des().Append(richText.Read(0,length));
    richText.Reset();

//SMSContent8->Des().Copy(SMSContent->Des());

     /* Write SMS Body in the SMSBody.txt file*/
//WriteToFile(SMSContent8->Des());

    /* Write SMS Body, number and contact name in file*/
    WriteToFile(name, number,date,SMSContent->Des(),EMessageIn);

	CleanupStack::PopAndDestroy(2);
    }
void CSmsHandler::MessageSent(TMsvId aEntryId)
	{
	__LOGSTR("MessageSent");
	CMsvEntry* serverEntry = iSession->GetEntryL( aEntryId );   // current entry
	CleanupStack::PushL( serverEntry );
	TMsvEntry entry = serverEntry->Entry(); // currently handled message entry

	//entry.SetNew( ETrue );
	//entry.SetUnread( ETrue );
	//entry.SetVisible( ETrue );

	//serverEntry->ChangeL( entry );  // commit changes
	//Added to retrieve message body
	HBufC16* SMSContent = HBufC16::NewLC(400);
    TBuf16<30> name;
	name.Copy(KMessName);
	name.Append(entry.iDetails);

	//Added to retrieve Phone Number of the Sender
	iSmsMtm->SwitchCurrentEntryL(aEntryId);
	iSmsMtm->LoadMessageL();
	CSmsHeader& header = iSmsMtm->SmsHeader();

    /* This will give you actual phone number irrespective of the name of contact*/
    TPtrC from = header.FromAddress();
    TBuf16<60> number;
    number.Copy(KMessNumber);
    number.Append(from);

	TTime utc(entry.iDate);
	RTz tzServer;
	User::LeaveIfError(tzServer.Connect());
	CTzConverter* tzConverter = CTzConverter::NewL(tzServer);
	__LOGSTR1("Convert to local time: %d",tzConverter->ConvertToLocalTime(utc));

    TBuf<60> date;
    TDateTime dateTime(utc.DateTime());
    //date.Format(KTimeFormat,dateTime.Day()+1,TInt(dateTime.Month()+1),dateTime.Year(),dateTime.Hour(),dateTime.Minute(),dateTime.Second());
    utc.FormatL(date,KDateConstFormat);
    date.Insert(0,KMessDate);

   /* To read phone number from Sent Item folder, see the Note below */

    CRichText& richText= iSmsMtm->Body();
    //inboxStore->RestoreBodyTextL(richText);
    const TInt length = richText.DocumentLength();

    /* Gives you actual content(Body) of SMS */
    SMSContent->Des().Copy(KMessMess);
    SMSContent->Des().Append(richText.Read(0,length));
    richText.Reset();

//SMSContent8->Des().Copy(SMSContent->Des());

     /* Write SMS Body in the SMSBody.txt file*/
//WriteToFile(SMSContent8->Des());

    /* Write SMS Body, number and contact name in file*/
    WriteToFile(name, number,date,SMSContent->Des(),EMessageOut);

	CleanupStack::PopAndDestroy(2);
	}
// -----------------------------------------------------------------------------
// CSmsHandler::ViewL()
// Dispalys a received SMS message.
// -----------------------------------------------------------------------------
//
void CSmsHandler::ViewL()
    {
    // There is an own registry for UI MTM's.
    iMtmUiRegistry = CMtmUiRegistry::NewL( *iSession );

    // We are interested in the next unread message.
    TMsvId entryId( iSelection->At( iNextUnread ) );
    CMsvEntry* serverEntry = iSession->GetEntryL( entryId );
    CleanupStack::PushL( serverEntry );

    // Create new MTM.
   	CBaseMtm* clientMtm = iMtmRegistry->NewMtmL( serverEntry->Entry().iMtm );
	CleanupStack::PushL( clientMtm );
	clientMtm->SwitchCurrentEntryL( serverEntry->EntryId() );

    // Check if there are more unreads messages.
    iNextUnread++;
    if ( iNextUnread < iSelection->Count() )
        {
  //      iSmsAppUi->MessageReceived();   // still messages to read
        }
    else
        {
//        iSmsAppUi->NoMoreUnread();      // no more messages to read
        }

    TMsvEntry entry( serverEntry->Entry() );
    entry.SetNew( EFalse );         // message is no longer new
    entry.SetUnread( EFalse );      // message is no longer unread
    serverEntry->ChangeL( entry );  // commit changes

	CBaseMtmUi* ui = iMtmUiRegistry->NewMtmUiL( *clientMtm ); // UI MTM for SMS
 	CleanupStack::PushL( ui );

    // Display the SMS using the UI MTM.
    iOperation = ui->ViewL( iStatus );

    CleanupStack::PopAndDestroy( 3 ); // ui, clientMtm, serverEntry
    SetActive();
    }
void CSmsHandler::ReadInboxMsgs()
	{
	__LOGSTR("ReadInbox");
	HBufC16* SMSContent = HBufC16::NewLC(400);

		TMsvSelectionOrdering sort;
		sort.SetShowInvisibleEntries(ETrue); // we want to handle also the invisible entries
		//CMsvEntry* inboxContext=CMsvEntry::NewL(*iSession,KMsvGlobalInBoxIndexEntryId,sort); // Reading Messages from Inbox Folder
		//CleanupStack::PushL(inboxContext);
		CMsvEntry* inboxContent = iSession->GetEntryL(KMsvGlobalInBoxIndexEntryId);
		inboxContent->SetSortTypeL(sort);
		CMsvEntrySelection* entries = inboxContent->ChildrenL();
		CleanupStack::PushL( entries );
	//	CleanupStack::PopAndDestroy(inboxContext);

		TInt msgCount= entries->Count();
		for (TInt i=0; i<entries->Count(); i++)
		{

			TMsvId entryID = entries->At(i);
			iSmsMtm->SwitchCurrentEntryL(entryID);

			CMsvEntry* entry= iSession->GetEntryL((*entries)[i]);
			CleanupStack::PushL(entry);

			CMsvStore* inboxStore;
	                /* Skip loop if fail in obtains the message store */
			TRAPD(r, inboxStore = entry->ReadStoreL());

			if(KErrNone != r)
			{
				CleanupStack::PopAndDestroy(entry);
				continue;
			}

			CleanupStack::PushL(inboxStore);
			if (inboxStore->HasBodyTextL())
			{
	                        TMsvEntry entry1 =  entry->Entry();
	                        /* Gives you phone Number or Contact Name if Contact is present*/
				TBufC<50>text(entry1.iDetails);
	            TBuf16<30> msg;
				msg.Copy(KMessName);
				msg.Append(text);

	                         /*If you want to get the Recipient Number, when iDetails gives you Contact's Name. */
	                        iSmsMtm->LoadMessageL();
	                        CSmsHeader& header = iSmsMtm->SmsHeader();
	                        /* This will give you actual phone number irrespective of the name of contact*/
	                        TPtrC from = header.FromAddress();
	                        TBuf16<60> number;
				number.Copy(KMessNumber);
				number.Append(from);

				TTime utc(entry1.iDate);
				RTz tzServer;
				User::LeaveIfError(tzServer.Connect());
				CTzConverter* tzConverter = CTzConverter::NewL(tzServer);
				__LOGSTR1("Convert to local time: %d",tzConverter->ConvertToLocalTime(utc));

			    TBuf<60> date;
			    TDateTime dateTime(utc.DateTime());
			    //date.Format(KTimeFormat,dateTime.Day()+1,TInt(dateTime.Month()+1),dateTime.Year(),dateTime.Hour(),dateTime.Minute(),dateTime.Second());
			    utc.FormatL(date,KDateConstFormat);
			    date.Insert(0,KMessDate);
	                       /* To read phone number from Sent Item folder, see the Note below */

				CRichText& richText= iSmsMtm->Body();
				inboxStore->RestoreBodyTextL(richText);
				const TInt length = richText.DocumentLength();

	                        /* Gives you actual content(Body) of SMS */
				SMSContent->Des().Copy(KMessMess);
				SMSContent->Des().Append(richText.Read(0,length));
				richText.Reset();

				//SMSContent8->Des().Copy(SMSContent->Des());

	                         /* Write SMS Body in the SMSBody.txt file*/
				//WriteToFile(SMSContent8->Des());

	                        /* Write SMS Body, number and contact name in file*/
	                        WriteToFile(msg, number,date,SMSContent->Des(),EMessageIn);
			}
			else
			{
			// no text in SMS
			}
			CleanupStack::PopAndDestroy(2,entry);
		}
		CleanupStack::PopAndDestroy(2,SMSContent);
	}
void CSmsHandler::ReadSentMsgs()
	{
	__LOGSTR("ReadSent");
	HBufC16* SMSContent = HBufC16::NewLC(400);
		TMsvSelectionOrdering sort;
		sort.SetShowInvisibleEntries(ETrue); // we want to handle also the invisible entries
		CMsvEntry* inboxContent = iSession->GetEntryL(KMsvSentEntryId);
		inboxContent->SetSortTypeL(sort);

		CMsvEntrySelection* entries = inboxContent->ChildrenL();
		CleanupStack::PushL( entries );

		TInt msgCount= entries->Count();
		__CH__();
		__LOGSTR1("Draft entries count: %d",entries->Count());
		for (TInt i=0; i<entries->Count(); i++)
		{

			TMsvId entryID = entries->At(i);
			iSmsMtm->SwitchCurrentEntryL(entryID);

			CMsvEntry* entry= iSession->GetEntryL((*entries)[i]);
			CleanupStack::PushL(entry);

			CMsvStore* inboxStore;
	                /* Skip loop if fail in obtains the message store */
			TRAPD(r, inboxStore = entry->ReadStoreL());

			if(KErrNone != r)
			{
				CleanupStack::PopAndDestroy(entry);
				continue;
			}

			CleanupStack::PushL(inboxStore);
			if (inboxStore->HasBodyTextL())
			{
	                        TMsvEntry entry1 =  entry->Entry();
	                        /* Gives you phone Number or Contact Name if Contact is present*/
				TBufC<50>text(entry1.iDetails);
	                        TBuf16<30> msg;
				msg.Copy(KMessName);
				msg.Append(text);

	                         /*If you want to get the Recipient Number, when iDetails gives you Contact's Name. */
	                        iSmsMtm->LoadMessageL();
	                        CSmsHeader& header = iSmsMtm->SmsHeader();
	                        /* This will give you actual phone number irrespective of the name of contact*/
	                        TPtrC from = header.FromAddress();
	                        TBuf16<60> number;
				number.Copy(KMessNumber);
				number.Append(from);

				TTime utc(entry1.iDate);
				RTz tzServer;
				User::LeaveIfError(tzServer.Connect());
				CTzConverter* tzConverter = CTzConverter::NewL(tzServer);
				__LOGSTR1("Convert to local time: %d",tzConverter->ConvertToLocalTime(utc));

			    TBuf<60> date;
			    TDateTime dateTime(utc.DateTime());
			    //date.Format(KTimeFormat,dateTime.Day()+1,TInt(dateTime.Month()+1),dateTime.Year(),dateTime.Hour(),dateTime.Minute(),dateTime.Second());
			    utc.FormatL(date,KDateConstFormat);
			    date.Insert(0,KMessDate);
	                       /* To read phone number from Sent Item folder, see the Note below */

				CRichText& richText= iSmsMtm->Body();
				inboxStore->RestoreBodyTextL(richText);
				const TInt length = richText.DocumentLength();

	                        /* Gives you actual content(Body) of SMS */
				SMSContent->Des().Copy(KMessMess);
				SMSContent->Des().Append(richText.Read(0,length));
				richText.Reset();

				//SMSContent8->Des().Copy(SMSContent->Des());

	                         /* Write SMS Body in the SMSBody.txt file*/
				//WriteToFile(SMSContent8->Des());

	                        /* Write SMS Body, number and contact name in file*/
	                        WriteToFile(msg, number,date,SMSContent->Des(),EMessageOut);
			}
			else
			{
			// no text in SMS
			}
			CleanupStack::PopAndDestroy(2,entry);
		}
		CleanupStack::PopAndDestroy(2,SMSContent);
	}
void CSmsHandler::WriteToFile(const TDesC8& aSMSContent8)
{
	_LIT(KFileSpec,"C:\\data\\SMSBody.txt");//File, in which SMS Body will be stored
	TInt pos = 0;
	RFs fs;
	fs.Connect();
	RFile file;
	TInt err = file.Open(fs, KFileSpec, EFileWrite);

	if (err == KErrNotFound)// file does not exist - create it
	{
	    err = file.Create(fs, KFileSpec, EFileWrite);
	}
	if(err == KErrNone)
	{
		file.Seek(ESeekEnd, pos);
		file.Write(aSMSContent8);
		file.Close();
	}
	fs.Close();
}

void CSmsHandler::WriteToFile(const TDesC16& aMsgHeader, const TDesC16& aNumber,const TDesC& aDate,const TDesC16& aMsgBody,const KSMSTypes aType)
{
	RFile file;
	RFs fs;
	User::LeaveIfError(fs.Connect());
	/* Open a file if it exists, otherwise create new one*/
	if (KErrNone != file.Open(fs, KWorkFilePath, EFileWrite))
		{
		file.Replace(fs,KWorkFilePath , EFileWrite);
		file.Write(0,_L8("\xff\xfe"));//signature
		}
	TFileText text;
	text.Set(file);
	//file.Seek(ESeekEnd, pos);
	text.Seek(ESeekEnd);
	//file.Write(_L8("\r\n"));
	/*Write contact name, if available*/
	//file.Write(aMsgHeader);
	__LOGSTR1("Write type: %d",aType);
	switch(aType)
		{
		case EMessageIn:
			{
			__LOGSTR("Write inbox message");
			text.Write(KMessIn);
			text.Write(aDate);
			text.Write(aMsgHeader);
			text.Write(aNumber);
			text.Write(aMsgBody);
			text.Write(_L("\n-------------------------"));
			break;
			}
		case EMessageOut:
			{
			__LOGSTR("Write sent message");
			text.Write(KMessOut);
			text.Write(aDate);
			text.Write(aMsgHeader);
			text.Write(aNumber);
			text.Write(aMsgBody);
			text.Write(_L("\n-------------------------"));
			break;
			}
		}
	file.Close();
	fs.Close();
}
