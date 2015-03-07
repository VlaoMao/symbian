/*
 * ============================================================================
 *  Name     : CClientEngine of ClientEngine.h
 *  Part of  : HTTP Client Example
 *  Created  : 06/26/2006 by Forum Nokia
 *  Version  : 2.0
 *  Copyright: Forum Nokia
 * ============================================================================
 */

#ifndef __CLIENTENGINE_H__
#define __CLIENTENGINE_H__

#include <coecntrl.h>
#include <http/mhttpdatasupplier.h>
#include <http/mhttptransactioncallback.h>
#include <http/mhttpauthenticationcallback.h>
#include <es_sock.h>

//#include <aknlists.h>
//#include <commdbconnpref.h>
//#include <commdb.h>
//#include "logger1.h"
/*
* Forward declarations
*/
class RHTTPSession;
class RHTTPTransaction;


/*
* MClientObserver
* CClientEngine passes events and responses body data with this interface.
* An instance of this class must be provided for construction of CClientEngine.
*/
class MClientObserver
	{
	public:
		/*
		* ClientEvent()
		*
		* Called when event occurs in CClientEngine.
		*
		* Params:
		*		aEventDescription:	A event in textual format, e.g.
		*							"Transaction Successful"
		*
		* Returns:
		* 		-
		*
		*/
		virtual void ClientEvent(const TDesC& aEventDescription) = 0;

		/*
		* ClientBodyReceived()
		*
		* Called when a part of the HTTP body is received.
		*
		* Params:
		*		aBodyData:	Part of the body data received. (e.g. part of
		*					the received HTML page)
		*
		* Returns:
		* 		-
		*
		*/
		virtual void ClientBodyReceived(const TDesC8& aBodyData) = 0;
	};

/*
* Provides simple interface to HTTP Client API.
*/
class CClientEngine :	public CBase,
						public MHTTPTransactionCallback,
						public MHTTPDataSupplier,
						public MHTTPAuthenticationCallback
	{
public:
	/*
	* NewL()
	*
	* Create a CClientEngine object.
	*
	* Params:
	*		iObserver:
	*
	* Returns:
	* 		A pointer to the created instance of CClientEngine
	*
	*/
	static CClientEngine* NewL(MClientObserver& iObserver);

	/*
	* NewLC()
	*
	* Create a CClientEngine object.
	*
	* Params:
	*		iObserver:
	*
	* Returns:
	* 		A pointer to the created instance of CClientEngine
	*
	*/
	static CClientEngine* NewLC(MClientObserver& iObserver);

	/*
	* ~CClientEngine()
	*
	* Destroy the object
	*
	* Params:
	*		-
	*
	* Returns:
	* 		-
	*
	*/
	~CClientEngine();

	/*
	* IssueHTTPGetL()
	*
	* Starts a new HTTP GET transaction.
	*
	* Params:
	*		aUri: URI to get. (e.g. http://host.org")
	*
	* Returns:
	* 		-
	*
	*/
	void IssueHTTPGetL(const TDesC8& aUri);

	/*
	* IssueHTTPPostL()
	*
	* Starts a new HTTP POST transaction.
	*
	* Params:
	*		aUri: URI where to post the data (e.g. http://host.org")
	*		aContentType: Content type of the body, e.g. "text/plain"
	*		aBody: Body data for the transaction.
	*
	* Returns:
	* 		-
	*
	*/
	void IssueHTTPPostL(const TDesC8& aUri,
						const TDesC8& aContentType,
						const TDesC8& aBody);

	/*
	* CancelTransaction()
	*
	* Closes currently running transaction and frees resources related to it.
	*
	* Params:
	*		-
	*
	* Returns:
	* 		-
	*
	*/
	void CancelTransaction();

	/*
	* IsRunning()
	*
	* Checks if the transaction is running.
	*
	* Params:
	*		-
	*
	* Returns:
	* 		ETrue, if transaction is currently running.
	*
	*/
	inline TBool IsRunning() { return iRunning; };

private:
	/*
	* ConstructL()
	*
	* Perform the second phase construction of a CClientEngine object.
	*
	* Params:
	*		-
	*
	* Returns:
	* 		-
	*
	*/
	void ConstructL();

	/*
	* CClientEngine()
	*
	* Perform the first phase of two phase construction.
	*
	* Params:
	*		iObserver:
	*
	* Returns:
	* 		-
	*
	*/
	CClientEngine(MClientObserver& iObserver);

	/*
	* SetHeaderL()
	*
	* Sets header value of an HTTP request.
	*
	* Params:
	*		aHeaders:	Headers of the HTTP request
	*		aHdrField:	Enumerated HTTP header field, e.g. HTTP::EUserAgent
	*		aHdrValue:	New value for header field
	*
	* Returns:
	* 		-
	*
	*/
	void SetHeaderL(RHTTPHeaders aHeaders, TInt aHdrField,
					const TDesC8& aHdrValue);

/*
* From MHTTPSessionEventCallback
*/
private:
	/*
	* MHFRunL()
	*
	* Called by framework to notify about transaction events.
	*
	* Params:
	*		aTransaction: Transaction, where the event occured.
	*		aEvent: Occured event.
	*
	* Returns:
	* 		-
	*
	*/
	void MHFRunL(RHTTPTransaction aTransaction, const THTTPEvent& aEvent);

	/*
	* MHFRunError()
	*
	* Called by framework when *leave* occurs in handling of transaction event.
	*
	* Params:
	*		aError:			The leave code that occured.
	*		aTransaction:	The transaction that was being processed when leave
	*						occured.
	*		aEvent:			The event that was being processed when leave
	*						occured.
	*
	* Returns:
	* 		KErrNone, if the error was handled. Otherwise the value of aError, or
	*		some other error value. Returning error value causes causes
	*		HTTP-CORE 6 panic.
	*
	*/
	TInt MHFRunError(	TInt aError,
						RHTTPTransaction aTransaction,
						const THTTPEvent& aEvent);

/*
* From MHTTPDataSupplier (needed for HTTP POST)
*/
private:
	/*
	* ReleaseData()
	*
	* Called by framework to allow data supplier to release resources
	* related to previous data part.
	*
	* Params:
	*		-
	*
	* Returns:
	* 		-
	*
	*/
	void ReleaseData();

	/*
	* GetNextDataPart()
	*
	* Called when next data part is needed.
	*
	* Params:
	*		aDataPart: Must be set to point to the next data part.
	*
	* Returns:
	* 		ETrue if the provided data part is the last one. If more data parts
	*		are needed after the provided one, return EFalse.
	*
	*/
	TBool GetNextDataPart(TPtrC8& aDataPart);

	/*
	* Reset()
	*
	* Called by framework to reset the data supplier to its initial state.
	*
	* Params:
	*		-
	*
	* Returns:
	*		KErrNone if successfull.
	*
	*/
	TInt Reset();

	/*
	* OverallDataSize()
	*
	* Called by framework when it needs to know the size of the
	* body data.
	*
	* Params:
	*		-
	*
	* Returns:
	* 		Size of the data, or KErrNotFound (or KErrNotSupported)
	*		if the size of the data is not known.
	*
	*/
	TInt OverallDataSize();
	
	/*
	 * SetupConnectionL()
	 * 
	 * The method set the internet access point and connection setups.
	 * 
	 */
	void SetupConnectionL();
public:
	TUint32 iIapId;
	TBool iSetIap;
	
/*
* From MHTTPAuthenticationCallback (needed for HTTP authentication)
*/
private:
	/*
	* GetCredentialsL()
	*
	* Called by framework when username and password for requested URI is
	* needed.
	*
	* Params:
	*		aURI: The URI being requested (e.g. "http://host.org")
	*		aRealm: The realm being requested (e.g. "user@host.org")
	*		aAuthenticationType: Authentication type. (e.g. "Basic")
	*		aUsername: Given user name.
	*		aPassword: Given password.
	*
	* Returns:
	* 		A pointer to the created document
	*
	*/
	TBool GetCredentialsL(	const TUriC8& aURI,
							RString aRealm,
							RStringF aAuthenticationType,
							RString& aUsername,
							RString& aPassword);

private:
	// declare members
    RSocketServ 			iSocketServ;
    RConnection 			iConnection;

	RHTTPSession			iSession;
	RHTTPTransaction		iTransaction;

	MClientObserver&		iObserver;	// Used for passing body data and
										// events to UI.
	HBufC8*					iPostData;	// Data for HTTP POST
	TBool					iRunning;	// ETrue, if transaction running
	
	TBool 					iConnectionSetupDone;
	};

#endif // __CLIENTENGINE_H__
