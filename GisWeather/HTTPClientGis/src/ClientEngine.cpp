/*
 * ============================================================================
 *  Name     : CClientEngine of ClientEngine.cpp
 *  Part of  : HTTP Client Example
 *  Created  : 06/20/2006 by Forum Nokia
 *  Version  : 2.0
 *  Copyright: Forum Nokia
 * ============================================================================
 */

#include <avkon.hrh>
#include <aknnotewrappers.h>
#include <uri8.h>
#include <http.h>
#include <chttpformencoder.h>
#include <httpstringconstants.h>
#include <http/rhttptransaction.h>
#include <http/rhttpsession.h>
#include <http/rhttpheaders.h>
//#include <HTTPClientExample.rsg>

#include <commdb.h> 		//Communications database
#include <cdbpreftable.h>	//Connection Preferences table
#include <commdbconnpref.h>

#include "Client.pan"
#include "Client.hrh"
#include "ClientEngine.h"

// Used user agent for requests
_LIT8(KUserAgent, "SQR S60 client");

// This client accepts all content types.
// (change to e.g. "text/plain" for plain text only)
_LIT8(KAccept, "*/*");

const TInt KStatustextBufferSize = 32;
const TInt KInfotextBufferSize = 64;
const TInt KURIBufferSize = 128;
const TInt KDefaultBufferSize = 256;

// ----------------------------------------------------------------------------
// CClientEngine::NewL()
//
// Creates instance of CClientEngine.
// ----------------------------------------------------------------------------
CClientEngine* CClientEngine::NewL(MClientObserver& aObserver)
	{
    CClientEngine* self = CClientEngine::NewLC(aObserver);
    CleanupStack::Pop(self);
    return self;
	}


// ----------------------------------------------------------------------------
// CClientEngine::NewLC()
//
// Creates instance of CClientEngine.
// ----------------------------------------------------------------------------
CClientEngine* CClientEngine::NewLC(MClientObserver& aObserver)
	{

    CClientEngine* self = new (ELeave) CClientEngine(aObserver);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
	}


// ----------------------------------------------------------------------------
// CClientEngine::CClientEngine()
//
// First phase constructor.
// ----------------------------------------------------------------------------
CClientEngine::CClientEngine(MClientObserver& aObserver)
:	iObserver(aObserver),
	iPostData(NULL),
	iRunning(EFalse)
	{
	}


// ----------------------------------------------------------------------------
// CClientEngine::~CClientEngine()
//
// Destructor.
// ----------------------------------------------------------------------------
CClientEngine::~CClientEngine()
	{	
	iSession.Close();

    // and finally close handles
    iConnection.Close();
    iSocketServ.Close();

	delete iPostData;
	}


// ----------------------------------------------------------------------------
// CClientEngine::ConstructL()
//
// Second phase construction.
// ----------------------------------------------------------------------------
void CClientEngine::ConstructL()
	{
	iSetIap = EFalse;
	// Open RHTTPSession with default protocol ("HTTP/TCP")
	TRAPD(err, iSession.OpenL());
	if(err != KErrNone) 
		{
		// Most common error; no access point configured, and session creation
		// leaves with KErrNotFound.
		_LIT(KErrMsg,
			"Cannot create session. Is internet access point configured?");
		_LIT(KExitingApp, "Exiting app.");
		CEikonEnv::Static()->InfoWinL(KErrMsg, KExitingApp);
		User::Leave(err);
		}

	// Install this class as the callback for authentication requests. When
	// page requires authentication the framework calls GetCredentialsL to get
	// user name and password.
	InstallAuthenticationL(iSession);

	}


// ----------------------------------------------------------------------------
// CClientEngine::SetHeaderL()
//
// Used to set header value to HTTP request
// ----------------------------------------------------------------------------
void CClientEngine::SetHeaderL(RHTTPHeaders aHeaders,
							 TInt aHdrField,
							 const TDesC8& aHdrValue)
	{
	RStringF valStr = iSession.StringPool().OpenFStringL(aHdrValue);
	CleanupClosePushL(valStr);
	THTTPHdrVal val(valStr);
	aHeaders.SetFieldL(iSession.StringPool().StringF(aHdrField,
		RHTTPSession::GetTable()), val);
	CleanupStack::PopAndDestroy(); // valStr
	}


// ----------------------------------------------------------------------------
// CClientEngine::IssueHTTPGetL()
//
// Start a new HTTP GET transaction.
// ----------------------------------------------------------------------------
void CClientEngine::IssueHTTPGetL(const TDesC8& aUri)
	{
	SetupConnectionL();	
		
	// Parse string to URI (as defined in RFC2396)
	TUriParser8 uri;
	uri.Parse(aUri);

	// Get request method string for HTTP GET
	RStringF method = iSession.StringPool().StringF(HTTP::EGET,
		RHTTPSession::GetTable());

	// Open transaction with previous method and parsed uri. This class will
	// receive transaction events in MHFRunL and MHFRunError.
	iTransaction = iSession.OpenTransactionL(uri, *this, method);

	// Set headers for request; user agent and accepted content type
	RHTTPHeaders hdr = iTransaction.Request().GetHeaderCollection();
	SetHeaderL(hdr, HTTP::EUserAgent, KUserAgent);
	SetHeaderL(hdr, HTTP::EAccept, KAccept);

	// Submit the transaction. After this the framework will give transaction
	// events via MHFRunL and MHFRunError.
	iTransaction.SubmitL();

	iRunning = ETrue;
	_LIT(KConnecting,"Connecting...");
	iObserver.ClientEvent(KConnecting);
	}


// ----------------------------------------------------------------------------
// CClientEngine::IssueHTTPPostL()
//
// Start a new HTTP POST transaction.
// ----------------------------------------------------------------------------
void CClientEngine::IssueHTTPPostL(const TDesC8& /*aUri*/,
								 const TDesC8& /*aContentType*/,
								 const TDesC8& /*aBody*/)
	{
	/*SetupConnectionL();
		
	// Parse string to URI
	TUriParser8 uri;
	uri.Parse(aUri);

	// Copy data to be posted into member variable; iPostData is used later in
	// methods inherited from MHTTPDataSupplier.
	delete iPostData;
	iPostData = aBody.AllocL();

	// Get request method string for HTTP POST
	RStringF method = iSession.StringPool().StringF(HTTP::EPOST,
		RHTTPSession::GetTable());

	// Open transaction with previous method and parsed uri. This class will
	// receive transaction events in MHFRunL and MHFRunError.
	iTransaction = iSession.OpenTransactionL(uri, *this, method);

	// Set headers for request; user agent, accepted content type and body's
	// content type.
	RHTTPHeaders hdr = iTransaction.Request().GetHeaderCollection();
	SetHeaderL(hdr, HTTP::EUserAgent, KUserAgent);
	SetHeaderL(hdr, HTTP::EAccept, KAccept);
	SetHeaderL(hdr, HTTP::EContentType, aContentType);

	// Set this class as an data supplier. Inherited MHTTPDataSupplier methods
	// are called when framework needs to send body data.
	MHTTPDataSupplier* dataSupplier = this;
	iTransaction.Request().SetBody(*dataSupplier);

	// Submit the transaction. After this the framework will give transaction
	// events via MHFRunL and MHFRunError.
	iTransaction.SubmitL();

	iRunning = ETrue;
	_LIT(KConnecting,"Connecting...");
	iObserver.ClientEvent(KConnecting);*/
	}

// ----------------------------------------------------------------------------
// CClientEngine::CancelTransaction()
//
// Cancels currently running transaction and frees resources related to it.
// ----------------------------------------------------------------------------
void CClientEngine::CancelTransaction()
	{
	if(!iRunning)
		return;

	// Close() also cancels transaction (Cancel() can also be used but
	// resources allocated by transaction must be still freed with Close())
	iTransaction.Close();

	// Not running anymore
	iRunning = EFalse;
	_LIT(KTransactionCancelled, "Transaction cancelled");
	iObserver.ClientEvent(KTransactionCancelled);
	}


// ----------------------------------------------------------------------------
// CClientEngine::MHFRunL()
//
// Inherited from MHTTPTransactionCallback
// Called by framework to pass transaction events.
// ----------------------------------------------------------------------------
void CClientEngine::MHFRunL(RHTTPTransaction aTransaction,
						  const THTTPEvent& aEvent)
	{
	switch (aEvent.iStatus)
		{
		case THTTPEvent::EGotResponseHeaders:
			{
			// HTTP response headers have been received. Use
			// aTransaction.Response() to get the response. However, it's not
			// necessary to do anything with the response when this event occurs.

			// Get HTTP status code from header (e.g. 200)
			RHTTPResponse resp = aTransaction.Response();
			TInt status = resp.StatusCode();

			// Get status text (e.g. "OK")
			TBuf<KStatustextBufferSize> statusText;
			statusText.Copy(resp.StatusText().DesC());

			TBuf<KDefaultBufferSize> text;
			_LIT(KHeaderReceived, "Header received. Status: %d %S");
			text.Format(KHeaderReceived, status, &statusText);
			iObserver.ClientEvent(text);
			}
			break;

		case THTTPEvent::EGotResponseBodyData:
			{
			// Part (or all) of response's body data received. Use
			// aTransaction.Response().Body()->GetNextDataPart() to get the actual
			// body data.
	
			// Get the body data supplier
			MHTTPDataSupplier* body = aTransaction.Response().Body();
			TPtrC8 dataChunk;

			// GetNextDataPart() returns ETrue, if the received part is the last
			// one.
			TBool isLast = body->GetNextDataPart(dataChunk);
			iObserver.ClientBodyReceived(dataChunk);

			TBuf<KInfotextBufferSize> text;
			_LIT(KBodyPartReceived, "%d bytes received... ");
			text.Format(KBodyPartReceived, dataChunk.Length());
			iObserver.ClientEvent(text);

			// NOTE: isLast may not be ETrue even if last data part received.
			// (e.g. multipart response without content length field)
			// Use EResponseComplete to reliably determine when body is completely
			// received.
			if (isLast)
				{
				_LIT(KBodyReceived,"Body received");
				iObserver.ClientEvent(KBodyReceived);
				}

			// Always remember to release the body data.
			body->ReleaseData();
			}
			break;

		case THTTPEvent::EResponseComplete:
			{
			// Indicates that header & body of response is completely received.
			// No further action here needed.
			_LIT(KTransactionComplete, "Transaction Complete");
			iObserver.ClientEvent(KTransactionComplete);
			}
			break;

		case THTTPEvent::ESucceeded:
			{
			// Indicates that transaction succeeded.
			_LIT(KTransactionSuccessful, "Transaction Successful");
			iObserver.ClientEvent(KTransactionSuccessful);

			// Transaction can be closed now. It's not needed anymore.
			aTransaction.Close();
			iRunning = EFalse;
			}
			break;

		case THTTPEvent::EFailed:
			{
			// Transaction completed with failure.
			_LIT(KTransactionFailed, "Transaction Failed");
			iObserver.ClientEvent(KTransactionFailed);
			aTransaction.Close();
			iRunning = EFalse;
			}
			break;

		default:
			// There are more events in THTTPEvent, but they are not usually
			// needed. However, event status smaller than zero should be handled
			// correctly since it's error.
			{
			TBuf<KInfotextBufferSize> text;
			if (aEvent.iStatus < 0)
				{
				_LIT(KErrorStr, "Error: %d");
				text.Format(KErrorStr, aEvent.iStatus);
				// Just close the transaction on errors
				aTransaction.Close();
				iRunning = EFalse;
				} 
			else 
				{
				// Other events are not errors (e.g. permanent and temporary
				// redirections)
				_LIT(KUnrecognisedEvent, "Unrecognised event: %d");
				text.Format(KUnrecognisedEvent, aEvent.iStatus);
				}
			iObserver.ClientEvent(text);
			}
			break;
		}
	}


// ----------------------------------------------------------------------------
// CClientEngine::MHFRunError()
//
// Inherited from MHTTPTransactionCallback
// Called by framework when *leave* occurs in handling of transaction event.
// These errors must be handled, or otherwise HTTP-CORE 6 panic is thrown.
// ----------------------------------------------------------------------------
TInt CClientEngine::MHFRunError(TInt aError,
							  RHTTPTransaction /*aTransaction*/,
							  const THTTPEvent& /*aEvent*/)
	{
	// Just notify about the error and return KErrNone.
	TBuf<KInfotextBufferSize>	text;
	_LIT(KRunError, "MHFRunError: %d");
	text.Format(KRunError, aError);
	iObserver.ClientEvent(text);
	return KErrNone;
	}


// ----------------------------------------------------------------------------
// CClientEngine::GetNextDataPart()
//
// Inherited from MHTTPDataSupplier
// Called by framework when next part of the body is needed. In this
// this provides data for HTTP post.
// ----------------------------------------------------------------------------
TBool CClientEngine::GetNextDataPart(TPtrC8& aDataPart)
	{
	if(iPostData)
		{
		// Provide pointer to next chunk of data (return ETrue, if last chunk)
		// Usually only one chunk is needed, but sending big file could require
		// loading the file in small parts.
		aDataPart.Set(iPostData->Des());
		}
	return ETrue;
	}


// ----------------------------------------------------------------------------
// CClientEngine::ReleaseData()
//
// Inherited from MHTTPDataSupplier
// Called by framework. Allows us to release resources needed for previous
// chunk. (e.g. free buffers)
// ----------------------------------------------------------------------------
void CClientEngine::ReleaseData()
	{
	// It's safe to delete iPostData now.
	delete iPostData;
	iPostData = NULL;
	}

// ----------------------------------------------------------------------------
// CClientEngine::Reset()
//
// Inherited from MHTTPDataSupplier
// Called by framework to reset the data supplier. Indicates to the data
// supplier that it should return to the first part of the data.
// In practise an error has occured while sending data, and framework needs to
// resend data.
// ----------------------------------------------------------------------------
TInt CClientEngine::Reset()
	{
	// Nothing needed since iPostData still exists and contains all the data.
	// (If a file is used and read in small parts we should seek to beginning
	// of file and provide the first chunk again in GetNextDataPart() )
	return KErrNone;
	}


// ----------------------------------------------------------------------------
// CClientEngine::OverallDataSize()
//
// Inherited from MHTTPDataSupplier
// Called by framework. We should return the expected size of data to be sent.
// If it's not know we can return KErrNotFound (it's allowed and does not cause
// problems, since HTTP protocol allows multipart bodys without exact content
// length in header).
// ----------------------------------------------------------------------------
TInt CClientEngine::OverallDataSize()
	{
	if(iPostData)
		return iPostData->Length();
	else
		return KErrNotFound ;
	}

// ----------------------------------------------------------------------------
// CClientEngine::GetCredentialsL()
//
// Inherited from MHTTPAuthenticationCallback
// Called by framework when we requested authenticated page and framework
// needs to know username and password.
// ----------------------------------------------------------------------------
TBool CClientEngine::GetCredentialsL(const TUriC8& aURI,
								   RString aRealm,
								   RStringF aAuthenticationType,
								   RString& aUsername,
								   RString& aPassword)
	{
	// aURI, aReal and aAuthenticationType are informational only. We only need
	// to set aUsername and aPassword and return ETrue, if aUsername and
	// aPassword are provided by user.

	// Informational only
	TBuf<KURIBufferSize> authType;
	TBuf<KURIBufferSize> uri;
	TBuf<KDefaultBufferSize> authText;
	authType.Copy(aAuthenticationType.DesC());
	uri.Copy(aURI.UriDes());
	_LIT(KAuthRequired, "%S requires %S authentication.");
	authText.Format(KAuthRequired, &uri, &authType);
	_LIT(KAuthNote, "Authentication required.");
	CEikonEnv::Static()->InfoWinL(KAuthNote, authText);

	// Query user name and password
	TBuf<KDefaultBufferSize> userName;
	TBuf<KDefaultBufferSize> password;
	//CAknMultiLineDataQueryDialog* dlg =
	//	CAknMultiLineDataQueryDialog::NewL(userName, password);

	//if (!dlg->ExecuteLD(R_DIALOG_USER_PASSWORD_QUERY))
	//	return EFalse; // No credentials given; must return EFalse

	// Set aUsername and aPassword
	TBuf8<KDefaultBufferSize> temp;
	temp.Copy(userName);
	TRAPD(err, aUsername = aRealm.Pool().OpenStringL(temp));
	if (!err)
		{
		temp.Copy(password);
		TRAP(err, aPassword = aRealm.Pool().OpenStringL(temp));
		if (!err) return ETrue;
		}

	// Return ETrue if user has given credentials (username and password),
	// otherwise EFlase
	return EFalse;
	}

// ----------------------------------------------------------------------------
// CClientEngine::SetupConnectionL()
//
// The method set the internet access point and connection setups.
// ----------------------------------------------------------------------------	
void CClientEngine::SetupConnectionL()
    {
    if( iConnectionSetupDone )
        return;
    
    iConnectionSetupDone = ETrue;
    //open socket server and start the connection
    User::LeaveIfError(iSocketServ.Connect());
    User::LeaveIfError(iConnection.Open(iSocketServ));
    
    TCommDbConnPref connectPref;
    TUint32 iapID;

    if(iSetIap == EFalse)
	{
    // open the IAP communications database 
	CCommsDatabase* commDB = CCommsDatabase::NewL(EDatabaseTypeIAP);
	CleanupStack::PushL(commDB);

	// initialize a view 
	CCommsDbConnectionPrefTableView* commDBView = 
	commDB->OpenConnectionPrefTableInRankOrderLC(ECommDbConnectionDirectionUnknown);

	// go to the first record 
	User::LeaveIfError(commDBView->GotoFirstRecord());

	// Declare a prefTableView Object.
	CCommsDbConnectionPrefTableView::TCommDbIapConnectionPref pref;
	// read the connection preferences 
	commDBView->ReadConnectionPreferenceL(pref);

	iapID = pref.iBearer.iIapId;

	// pop and destroy the IAP View 
	CleanupStack::PopAndDestroy(commDBView);

	// pop and destroy the database object
	CleanupStack::PopAndDestroy(commDB);

	// setup preferences 
	connectPref.SetDialogPreference(ECommDbDialogPrefDoNotPrompt);
	connectPref.SetDirection(ECommDbConnectionDirectionUnknown);
	connectPref.SetBearerSet(ECommDbBearerGPRS);
	//Sets the CommDb ID of the IAP to use for this connection
	connectPref.SetIapId(iapID);
	}else{
	connectPref.SetDialogPreference(ECommDbDialogPrefDoNotPrompt);
	connectPref.SetDirection(ECommDbConnectionDirectionUnknown);
	connectPref.SetBearerSet(ECommDbBearerGPRS);
	//Sets the CommDb ID of the IAP to use for this connection
	connectPref.SetIapId(iIapId);
	}
    
    User::LeaveIfError(iConnection.Start(connectPref));
	
    //set the sessions connection info
    RStringPool strPool = iSession.StringPool();
    RHTTPConnectionInfo connInfo = iSession.ConnectionInfo();
    
    //to use our socket server and connection
    connInfo.SetPropertyL ( strPool.StringF(HTTP::EHttpSocketServ,
        RHTTPSession::GetTable() ), THTTPHdrVal (iSocketServ.Handle()) );

    connInfo.SetPropertyL ( strPool.StringF(HTTP::EHttpSocketConnection,
        RHTTPSession::GetTable() ), 
        THTTPHdrVal (REINTERPRET_CAST(TInt, &(iConnection))) );
    }

// end of file
