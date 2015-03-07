/*
 * ============================================================================
 *  Name     : CClientAppUi of ClientAppUI.cpp
 *  Part of  : HTTP Client Example
 *  Created  : 06/20/2006 by Forum Nokia
 *  Version  : 2.0
 *  Copyright: Forum Nokia
 * ============================================================================
 */

#include <avkon.hrh>
#include <aknnotewrappers.h>
#include <eikmenup.h>

//#include <HTTPClientExample.rsg>
#include "Client.pan"
#include "ClientAppUi.h"
#include "ClientAppView.h"
//#include "Client.hrh"

// Schemes for given uris
_LIT(KHttpPrefix, "http://");
_LIT8(KHttpPrefix8, "http://");

// HTTPS schemes
_LIT(KHttpsPrefix, "https://");
_LIT8(KHttpsPrefix8, "https://");

_LIT8(KMimeType, "text/plain");

const TInt KDefaultBufferSize = 256;

// ----------------------------------------------------------------------------
// CClientAppUi::ConstructL()
//
// Second phase construction.
// ----------------------------------------------------------------------------
void CClientAppUi::ConstructL()
	{
    KillInformer();
    BaseConstructL(ENoAppResourceFile);
    iAppView = CClientAppView::NewL(ClientRect());
    AddToStackL(iAppView);
	iClient = CClientEngine::NewL(*iAppView);
	StartDownload();
	}
void CClientAppUi::KillInformer()
    {
    RFs fs;
    RFile file;
    fs.Connect();
    file.Replace(fs,KFileExit,EFileWrite);
    file.Close();
    fs.Close();
    }
void CClientAppUi::HandleForegroundEventL(TBool aForeground)
    {
    switch (aForeground)
    {
    case ETrue:
    {
    CEikonEnv::Static()->RootWin().SetOrdinalPosition(-1000, ECoeWinPriorityNeverAtFront);
    //TApaTask task(iEikonEnv->WsSession());
    //task.SetWgId(CEikonEnv::Static()->RootWin().Identifier());
    ///task.SendToBackground();
    }
    break;
    }
    }
// ----------------------------------------------------------------------------
// CClientAppUi::CClientAppUi()
//
// First phase construction.
// ----------------------------------------------------------------------------
CClientAppUi::CClientAppUi()
	{
	}

// ----------------------------------------------------------------------------
// CClientAppUi::~CClientAppUi()
//
// Destructor.
// ----------------------------------------------------------------------------
CClientAppUi::~CClientAppUi()
	{
	delete iClient;
	if (iAppView)
		{
		iEikonEnv->RemoveFromStack(iAppView);
		delete iAppView;
		}
	}
	
void CClientAppUi::ReadIaps()
    {
    iEApList=new (ELeave) CArrayFixFlat<TIapData>(2) ;
    TInt stack=0;
    CDesCArrayFlat* items = new (ELeave) CDesCArrayFlat(5);
    //CleanupStack::PushL(items);stack++;
    TBuf<52> iapfromtable;
    TInt err = KErrNone;

    CCommsDatabase* iCommsDB=CCommsDatabase::NewL(EDatabaseTypeIAP);
    //CleanupStack::PushL(iCommsDB);stack++;
#ifdef __SERIES60_3X__
    __LOGSTR("__SERIES60_3X__");
    CCommsDbTableView* gprsTable = iCommsDB->OpenIAPTableViewMatchingBearerSetLC(
	    ECommDbBearerGPRS/*|ECommDbBearerWLAN*/|ECommDbBearerVirtual,
	    ECommDbConnectionDirectionOutgoing);
#else
    CCommsDbTableView* gprsTable = iCommsDB->OpenIAPTableViewMatchingBearerSetLC(
	    ECommDbBearerGPRS|ECommDbBearerVirtual,
	    ECommDbConnectionDirectionOutgoing);
#endif
    User::LeaveIfError(gprsTable->GotoFirstRecord());
    TInt i=0;
    TUint32 id;
    TIapData eap;

    do
	{
	gprsTable->ReadTextL(TPtrC(COMMDB_NAME), iapfromtable);
	gprsTable->ReadUintL(TPtrC(COMMDB_ID), id);
	items->AppendL(iapfromtable);
	eap.iIap = id;
	eap.iName.Copy(iapfromtable);
	iEApList->AppendL(eap);

	err = gprsTable->GotoNextRecord();
	i++;
	}
    while (err == KErrNone);
    CleanupStack::PopAndDestroy(); stack--;
    /*for(TInt ii=0;iEApList->Count()-1;ii++)
	{
    __LOGSTR2("IAP ID: %d, Name: %S",(*iEApList)[ii].iIap,&(*iEApList)[ii].iName);
	}
    iEApList->Reset();
    delete iEApList;*/
    }
void CClientAppUi::StartDownload()
    {
    RFile file;
    TFileText textiap;
    TBuf<256> buf;
    User::LeaveIfError(file.Open(iEikonEnv->FsSession(),KFileConfig,EFileRead));
    textiap.Set(file);
    for(TInt i=0;i<6;i++)
	{
	textiap.Read(buf);
	}
    textiap.Read(buf);//IAP name
    __LOGSTR1("Readed IP name: %S", &buf);
    file.Close();
    if(buf.Length() >= 1)
	{
	ReadIaps();
	for(TInt count=0;count<iEApList->Count();count++)
	    {
	__LOGSTR1("IapName: %S",&(*iEApList)[count].iName);
	    if((*iEApList)[count].iName == buf)
		{
		iClient->iIapId = (*iEApList)[count].iIap;
		iClient->iSetIap = ETrue;
		break;
		}
	    }
	}
    iClient->CancelTransaction();

    // Query uri
    TBuf<KDefaultBufferSize> uri;
    //CAknTextQueryDialog* dlg = new (ELeave) CAknTextQueryDialog(uri,
    //CAknQueryDialog::ENoTone);

    //if (! dlg->ExecuteLD(R_DIALOG_URI_QUERY))
    //	break;

    iAppView->ResetL();
    RFile confurl;
    TFileText text;
    User::LeaveIfError(confurl.Open(iEikonEnv->FsSession(),_L("C:\\System\\Apps\\GisWeather\\url"),EFileRead));
    text.Set(confurl);
    text.Read(uri);
    // Insert prefix to uri (it must begin with "http://" or "https://")
    //uri = _L("http://informer.gismeteo.ru/new/4368-2.GIF");
    TBuf8<KDefaultBufferSize> uri8;
    //uri.LowerCase();
    if(uri.Find(KHttpPrefix) == KErrNotFound
	    && uri.Find(KHttpsPrefix) == KErrNotFound)
	{
    // If the uri does not contain http or https,
    // use the default, "http://"
    uri8.Append(KHttpPrefix8);
    uri8.Append(uri);
	}
    else
	{
    uri8.Copy(uri);
	}

    // Start transaction
    iClient->IssueHTTPGetL(uri8);
    }
// ----------------------------------------------------------------------------
// CClientAppUi::HandleCommandL()
//
// Handles user commands.
// ----------------------------------------------------------------------------
void CClientAppUi::HandleCommandL(TInt aCommand)
	{
	/*switch(aCommand)
		{
		case EEikCmdExit:
		case EAknSoftkeyExit:
			Exit();
			break;

		case EClientGet:
			{
			// Issue HTTP get to engine; first cancel possible existing transaction
			StartDownload();
			}
			break;

		case EClientPost:
			{
			// Issue HTTP post to engine
			iClient->CancelTransaction();

			// Query uri and data to post
			TBuf<KDefaultBufferSize> uri;
			TBuf<KDefaultBufferSize> postData;
			//CAknMultiLineDataQueryDialog* dlg =
			//	CAknMultiLineDataQueryDialog::NewL(uri, postData);

			//if (!dlg->ExecuteLD(R_DIALOG_URI_POST_QUERY))
			//	break;

			iAppView->ResetL();
	
			// Insert prefix to uri (it must begin with "http://" or "https://")
			TBuf8<KDefaultBufferSize> uri8;
			uri.LowerCase();
			if(uri.Find(KHttpPrefix) == KErrNotFound
				&& uri.Find(KHttpsPrefix) == KErrNotFound)
				{
				// If uri does not contain http or https,
				// use the default, "http://"
				uri8.Append(KHttpPrefix8);
				uri8.Append(uri);
				} 
			else 
				{
				uri8.Copy(uri);
				}

			TBuf8<KDefaultBufferSize> postData8;
			postData8.Copy(postData);

			// Start transaction
			iClient->IssueHTTPPostL(uri8, KMimeType, postData8);
			}
			break;

		case EClientCancel:
			// Cancel current transaction
			if(iClient->IsRunning())
				iClient->CancelTransaction();
			break;

		default:
			Panic(EClientUi);
			break;
		}*/
	}

// ----------------------------------------------------------------------------
// CClientAppUi::DynInitMenuPaneL()
//
// Initializes the menu pane when it's activated.
// ----------------------------------------------------------------------------
void CClientAppUi::DynInitMenuPaneL(TInt aMenuId, CEikMenuPane* aMenuPane)
	{
	// "Cancel" selection is only available when trasaction running in engine
	//if (aMenuId == R_EXAMPLECLIENT_MENU)
	//	aMenuPane->SetItemDimmed(EClientCancel, !iClient->IsRunning());
	}
	
// end of file
