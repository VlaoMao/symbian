/*
 ============================================================================
 Name		: KeepConnect.cpp
 Author	  : Avis
 Copyright   : Avis.
 2009, All rights reserved
 Description : Exe source file
 ============================================================================
 */

//  Include Files  

#include "KeepConnect.h"
#include <e32base.h>
#include <e32std.h>
#include <es_enum.h>
#include <es_sock.h>
#include <http.h>
#include <thttphdrval.h> 
#include <rhttpconnectioninfo.h>
#include <bacline.h>
#include <apacmdln.h>
#include <rhttptransaction.h>
#include <uri8.h>
#include <aknglobalnote.h>
#ifdef _DEBUG
#include <e32debug.h>
#endif
//#include <e32cons.h>			// Console

_LIT(KFileNameIni, "\\Data\\KeepConnect\\KeepConnect.ini");
_LIT(KDateFormat,"%D%M%Y%/0%1%/1%2%/2%3%/3 %-B%:0%J%:1%T%:2%S%:3%+B"); 
const int KMaxHeaderValueLength = 1024;
const int KMaxHeaderNameLength = 1024;
const int KMaxDateTimeStringLength = 1024;

void CConnectionKeeper::ConstructL()
    {
    User::LeaveIfError( iConnectionMonitor.ConnectL() );  //Connecting with server
    User::LeaveIfError( iConnectionMonitor.NotifyEventL( *this ));  //Registering 
    iTimer = CPeriodic::NewL( CActive::EPriorityStandard );
    iPingTimer = CPeriodic::NewL( CActive::EPriorityStandard );
    iConnected = EFalse;
    iConnectingWIFI = EFalse;
    }


CConnectionKeeper* CConnectionKeeper::NewL()
	{
	CConnectionKeeper* self = CConnectionKeeper::NewLC();
	CleanupStack::Pop(self); // self;
	return self;
	}

CConnectionKeeper* CConnectionKeeper::NewLC()
	{
	CConnectionKeeper* self = new (ELeave) CConnectionKeeper();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CConnectionKeeper::CConnectionKeeper(void) //: CBase()
	{
	// No implementation required
	}

CConnectionKeeper::~CConnectionKeeper()
	{
//	iTimer.Cancel();
	delete iTimer;
	iTimer = NULL;
	delete iPingTimer;
	iPingTimer = NULL;
	iConnectionMonitor.CancelNotifications();
	iConnectionMonitor.Close();
	iConnection.Close();
	iSocketServ.Close();

	}
 
void CConnectionKeeper::EventL (const CConnMonEventBase &aConnMonEvent)
	{						
	switch ( aConnMonEvent.EventType() )
		{
		case EConnMonDeleteConnection:
			{
			iConnection.Close();
			iSocketServ.Close();
			if (iPingTimer->IsActive())
				iPingTimer->Cancel();
			iConnected = EFalse;
			iConnectingWIFI = EFalse;
			break;	
			}
		case EConnMonCreateSubConnection:
			{
			break;
			}
		case EConnMonCreateConnection:
			{
			break;	
			}			
		case  EConnMonNetworkStatusChange:
        	{
        	break;
        	}
    	case EConnMonTransmitPowerChange:
    		{
    		iConnectingWIFI = ETrue;
    		}
    		break;        	
		case  EConnMonConnectionStatusChange:
			{
			CConnMonConnectionStatusChange *eventDlData;
        	eventDlData = (CConnMonConnectionStatusChange*)& aConnMonEvent;
			if (eventDlData->ConnectionStatus() == KLinkLayerOpen)
				{
				if (!iConnected)
					{
					if (iConnectingWIFI)
						{
						if (iCatchWiFi)
							StartTimer();
						}
					else
						StartTimer();
					}
				}
			
			break;
			}
		case  EConnMonBearerChange:
			{
			break;
			}
		default:
			break;
		} 	
	}

TBool  CConnectionKeeper::GetCatchWiFi()
	{
	return iCatchWiFi;
	}

void CConnectionKeeper::SetCatchWiFi(const TBool aParam)
	{
	iCatchWiFi = aParam;
	}

TInt CConnectionKeeper::GetPingInterval()
	{
	return iPingInterval;
	}

void CConnectionKeeper::SetPingInterval (const TInt aInterval)
	{
	iPingInterval = aInterval;
	}

TDesC& CConnectionKeeper::GetPingUrl ()
	{
	return iPingUrl;
	}

void CConnectionKeeper::SetPingUrl(const TDesC &aUrl)
	{
	iPingUrl.Copy(aUrl);
	}

void CConnectionKeeper::StartPingTimer(const TInt aMinutes)
	{
	if (iPingTimer->IsActive())
		iPingTimer->Cancel();
	iPingTimer->Start(aMinutes * 60000000, aMinutes * 60000000, TCallBack( CConnectionKeeper::PeriodPing, this));
	}

TInt CConnectionKeeper::PeriodPing( TAny* aPtr )
	{
    ( static_cast<CConnectionKeeper*>( aPtr ) )->DoPingPeriodTask();
    // Returning a value of TRUE indicates the callback should be done again
	return ETrue;
	}

void CConnectionKeeper::DoPingPeriodTask()
	{
	if (!iConnected)
		iPingTimer->Cancel();
	else
		{
		//TODO pinging
/*
		User::LeaveIfError(iSocketServ.Connect());
		User::LeaveIfError(iConnection.Open(iSocketServ)); */
		RHTTPSession iHttpSession;
		iHttpSession.OpenL();
		 
		// Initiate connection
//		iConnection.Start(iStatus);
		 
		//...
		 
		RHTTPConnectionInfo connInfo = iHttpSession.ConnectionInfo();
		RStringPool pool = iHttpSession.StringPool();
		 
		// Attach to socket server
		connInfo.SetPropertyL(pool.StringF(HTTP::EHttpSocketServ, RHTTPSession::GetTable()), THTTPHdrVal(iSocketServ.Handle()));
		 
		// Attach to connection
		TInt connPtr = REINTERPRET_CAST(TInt, &iConnection);
		connInfo.SetPropertyL(pool.StringF(HTTP::EHttpSocketConnection, RHTTPSession::GetTable()), THTTPHdrVal(connPtr));
		 
		// Open transaction...
		TUriParser8 	iuri;
		TBuf8<50> uri8;
		uri8.Copy(iPingUrl);
		iuri.Parse(uri8);
		RHTTPTransaction iHttpTrans = iHttpSession.OpenTransactionL(iuri, *this, pool.StringF(HTTP::EGET, RHTTPSession::GetTable()));
		RHTTPHeaders hdr = iHttpTrans.Request().GetHeaderCollection();

		_LIT8(KAccept, "*/*");
		_LIT8(KAtext, "text/plain");
		_LIT8(KUserAgent, "Mozilla/5.0 (SymbianOS/9.3; U; Series60/3.2 NokiaN96-1/1.11; Profile/MIDP-2.1 Configuration/CLDC-1.1;) AppleWebKit/413 (KHTML, like Gecko) Safari/413");
		
		SetHeaderL(hdr, HTTP::EUserAgent, KUserAgent, pool);
		 SetHeaderL(hdr, HTTP::EAccept, KAccept, pool);
		 SetHeaderL(hdr, HTTP::EContentType, KAtext, pool);
		 iHttpTrans.SubmitL();
		 //TODO
		
		iHttpTrans.Close();
		iHttpSession.Close();
		}
		
	}

void CConnectionKeeper::SetHeaderL(RHTTPHeaders aHeaders, TInt aHdrField,
                                const TDesC8& aHdrValue, RStringPool aPool)
   {
   RStringF valStr = aPool.OpenFStringL(aHdrValue);
   CleanupClosePushL(valStr);
   THTTPHdrVal val(valStr);
   aHeaders.SetFieldL(aPool.StringF(aHdrField, RHTTPSession::GetTable()), val);     
   CleanupStack::PopAndDestroy(); 
   }

void CConnectionKeeper::MHFRunL(RHTTPTransaction aTransaction, const THTTPEvent& aEvent)
	{}

TInt CConnectionKeeper::MHFRunError(TInt aError, RHTTPTransaction aTransaction, const THTTPEvent& aEvent)
	{
	return KErrNone;
	}

void CConnectionKeeper::StartTimer()
	{
	if (iTimer->IsActive())
		iTimer->Cancel();
	iTimer->Start(2000000, 1000000, TCallBack( CConnectionKeeper::Period, this));
	}

TInt CConnectionKeeper::Period( TAny* aPtr )
	{
    ( static_cast<CConnectionKeeper*>( aPtr ) )->DoPeriodTask();
    // Returning a value of TRUE indicates the callback should be done again
	return ETrue;
	}

void CConnectionKeeper::DoPeriodTask()
{
	iTimer->Cancel();
    iSocketServ.Connect();
    iConnection.Open(iSocketServ);
	TConnectionInfoBuf tconnInfo;
	TUint count;
//	TInt selectedIap=1;
	if ( iConnection.EnumerateConnections(count) == KErrNone )
		{
		for (TUint i=1; i<=count; i++)
		{
			// Note: GetConnectionInfo expects 1-based index
		TInt err = iConnection.GetConnectionInfo( i, tconnInfo );
#ifdef _DEBUG
TBuf<10> tOut;
tOut.Num(err);
RDebug::Print(tOut);
#endif	     		
		if ( err == KErrNone )
			{
//                    if ( connInfo().iIapId == selectedIap )
//                  {
			err = iConnection.Attach(tconnInfo, RConnection::EAttachTypeNormal);
#ifdef _DEBUG
TBuf<10> tOut;
tOut.Num(err);
RDebug::Print(tOut);
#endif	     			
			if ( err == KErrNone )
				{
				iConnected = ETrue;
				if (iPingUrl != KNullDesC && iPingInterval > 0)
					{
					StartPingTimer(iPingInterval); // timer for ping
					}
#ifdef _DEBUG
RDebug::Print(_L("Connected"));
#endif	     	                        
				break;
				}
#ifdef _DEBUG
RDebug::Print(_L("Not Connected"));
#endif	                    
//                }
			}
		}
		}

}

void  WriteIniFileL(const TBool aVal, CConnectionKeeper& aqr)
	{
	RFs fs;
	fs.Connect();
	RFile hist;
	TBuf<100> iLine;
	TBuf<3> bufTemp;
	TBool tTemp;
	TBuf<50> iPingUrl;	
		
	TBuf<250> tFileName;	// Get the Drive
	TBuf<3> tDriveName;	// Get the Drive
	TParse fp;
	CCommandLineArguments* args = CCommandLineArguments::NewL();
	TPtrC ar1(args->Arg(0));
	fs.Parse(ar1, fp);	
	delete args;
	tDriveName.Copy(fp.Drive());
	tFileName.Copy(tDriveName);
	tFileName.Append(KFileNameIni);
#ifdef _DEBUG
	RDebug::Print(tFileName);	
#endif		
	fs.MkDirAll(tFileName);
	
	if (hist.Replace(fs,tFileName,EFileWrite) == KErrNone)
		{
		TFileText text;
		text.Set(hist);
		iLine.Copy( _L("[SETTINGS]"));
		text.Write(iLine);
		
		iLine.Copy( _L("Autostart="));
		bufTemp.Num(aVal);
		iLine.Append(bufTemp);
		text.Write(iLine);
		
		iLine.Copy( _L("CatchWiFi="));
		bufTemp.Num(aqr.GetCatchWiFi());
		iLine.Append(bufTemp);
		text.Write(iLine);
		
		iLine.Copy( _L("PingInterval="));
		bufTemp.Num(aqr.GetPingInterval());
		iLine.Append(bufTemp);
		text.Write(iLine);
		
		iLine.Copy( _L("PingURL="));
		bufTemp.Copy(aqr.GetPingUrl());
		iLine.Append(bufTemp);
		text.Write(iLine);				

		hist.Close();
		}	
	fs.Close();
	}

TBool ReadIniFileL(CConnectionKeeper& aqr)
	{
	RFs fs;
	fs.Connect();
	TBool iAutostart = EFalse;
	
	TBuf<250> tFileName;	// Get the Drive
	TBuf<3> tDriveName;	// Get the Drive
	TParse fp;
	CCommandLineArguments* args = CCommandLineArguments::NewL();
	TPtrC ar1(args->Arg(0));
	fs.Parse(ar1, fp);	
	delete args;
	tDriveName.Copy(fp.Drive());
	tFileName.Copy(tDriveName);
	tFileName.Append(KFileNameIni);
#ifdef _DEBUG
	RDebug::Print(tFileName);	
#endif		
	
	RFile hist;
	TBuf<50> iLine;
	TBool dataSection = EFalse;
	if (hist.Open(fs,tFileName,EFileRead) == KErrNone)
	{
		TFileText text;
		text.Set(hist);
		iLine.Copy( _L("  "));
		while (iLine.Length() > 0)
		{
			text.Read(iLine);
			iLine.ZeroTerminate();
			if (iLine.Length() > 0)
			{
				if(dataSection)
					{
					TInt i = iLine.Locate('=');		
					if (i >= 0)
						{
					TBuf<15> iTempDes;
					TBuf<50> iTempVal;
		
					iTempDes.Copy(iLine.Left(i));
					iTempVal.Copy(iLine.Mid(i+1));
					if ( iTempDes.Find(_L("Autostart")) >= 0 )
						{
							if (iTempVal.Locate('0') >= 0)
								iAutostart = EFalse;
							else
								iAutostart = ETrue;
						}
					else if ( iTempDes.Find(_L("CatchWiFi")) >= 0 )
						{
							if (iTempVal.Locate('0') >= 0)
								aqr.SetCatchWiFi(EFalse);
							else
								aqr.SetCatchWiFi(ETrue);
						}
					else if ( iTempDes.Find(_L("PingURL")) >= 0 )
						{
						aqr.SetPingUrl(iTempVal);
						}
					else if ( iTempDes.Find(_L("PingInterval")) >= 0 )
						{
				   	    TLex lex(iTempVal);
				   	    TInt tValUse;
				   	    User::LeaveIfError(lex.Val(tValUse));
				   	    if ((tValUse > 0) && (tValUse < 31))
				   	    	aqr.SetPingInterval(tValUse);
				   	    else
				   	    	aqr.SetPingInterval(0);
						}					
						}
					}
				else
					{
					TInt i = iLine.Find(_L("[SETTINGS]"));
					if (i >= 0) 
						{
						dataSection = ETrue;
						}
					}
			}
		}
		hist.Close();
	}
	fs.Close();
	if (!dataSection)
		{
//		iUseMessage = EFalse;
		}
	return ( dataSection && iAutostart );
	}

LOCAL_C void MainL()
	{
	CConnectionKeeper * tqr  = CConnectionKeeper::NewLC();   
	
	TBool iStart = ReadIniFileL(*tqr);
	TBool tAutoStart;
	TBool tKill = EFalse;
//	TInt procId;
	
	CApaCommandLine* commandLine = NULL;
	TInt getCommandLineError = CApaCommandLine::GetCommandLineFromProcessEnvironment( commandLine );
	User::LeaveIfError( getCommandLineError ); 
	CleanupStack::PushL( commandLine );
	if(commandLine->OpaqueData().Length() > 0)
		{
		tAutoStart = EFalse;
		}
	else
		{
		tAutoStart = ETrue;
		}	

	CleanupStack::PopAndDestroy( commandLine ); 
	commandLine = NULL; 	
	
#ifdef _DEBUG
	CActiveScheduler::Start();
#else	
	TFindProcess processFinder(_L("KeepConnect.exe*")); // by name, case-sensitive
	//or
	//TFindProcess processFinder(_L("*[12345678]*")); // by UID3
	TFullName result;
	RProcess processHandle;
	if (processFinder.Next(result) ==  KErrNone)
		{
		User::LeaveIfError(processHandle.Open ( processFinder, EOwnerThread));		
		if ( processFinder.Next(result) != KErrNone) 
			{
			if ( tAutoStart )
				{
				if (iStart)
					CActiveScheduler::Start();
				}
			else
				{
				WriteIniFileL(ETrue, *tqr);
				CAknGlobalNote* 	tNote;
				tNote = CAknGlobalNote::NewL();
				tNote->ShowNoteL(EAknGlobalInformationNote, _L("KeepConnect enabled & started"));
				delete tNote;
				CActiveScheduler::Start();					
				}
			}
		else
			{
			WriteIniFileL(EFalse, *tqr);
			tKill = ETrue;
			CAknGlobalNote* 	tNote;
			tNote = CAknGlobalNote::NewL();
			tNote->ShowNoteL(EAknGlobalInformationNote, _L("KeepConnect stopped & disabled"));
			delete tNote;
			}
		if (tKill)
			{
			processHandle.Kill(KErrNone);
			}	
		processHandle.Close();
		}	
#endif	
	}

LOCAL_C void DoStartL()
	{
	// Create active scheduler (to run active objects)
	CActiveScheduler* scheduler = new (ELeave) CActiveScheduler();
	CleanupStack::PushL(scheduler);
	CActiveScheduler::Install(scheduler);

	MainL();
	// Delete active scheduler
	CleanupStack::PopAndDestroy(2, scheduler);
	}

//  Global Functions

GLDEF_C TInt E32Main()
	{
	// Create cleanup stack
	__UHEAP_MARK;
	CTrapCleanup* cleanup = CTrapCleanup::New();

	// Run application code inside TRAP harness, wait keypress when terminated
	TRAPD(mainError, DoStartL());

	delete cleanup;
	__UHEAP_MARKEND;
	return KErrNone;
	}

