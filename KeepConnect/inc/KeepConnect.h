/*
 ============================================================================
 Name		: KeepConnect.h
 Author	  : Avis
 Copyright   : Avis.
 2009, All rights reserved
 Description : Exe header file
 ============================================================================
 */

#ifndef __KEEPCONNECT_H__
#define __KEEPCONNECT_H__

//  Include Files

#include <e32base.h>
#include <rconnmon.h>
#include <es_sock.h>
//#include <rhttpsession.h> 
#include <rhttptransaction.h>
#include <mhttptransactioncallback.h>
//  Function Prototypes

GLDEF_C TInt E32Main();

class CConnectionKeeper : public CBase, MHTTPTransactionCallback, private MConnectionMonitorObserver 
	{
public:
	~CConnectionKeeper();
	static CConnectionKeeper* NewL();
	static CConnectionKeeper* NewLC();
	void MHFRunL(RHTTPTransaction aTransaction, const THTTPEvent& aEvent);
	TInt MHFRunError(TInt aError, RHTTPTransaction aTransaction, const THTTPEvent& aEvent);	
public:
	void  EventL (const CConnMonEventBase &aConnMonEvent);
	TBool GetCatchWiFi();
	void SetCatchWiFi(const TBool aParam);
	TInt GetPingInterval();
	void SetPingInterval(const TInt aInterval);
	TDesC& GetPingUrl();
	void SetPingUrl(const TDesC &aUrl);
private:
	CConnectionKeeper(void);
	void ConstructL(void);
	void DoPeriodTask();
    static TInt Period( TAny* aPtr );
    void StartTimer();
	void DoPingPeriodTask();
    static TInt PeriodPing( TAny* aPtr );
    void StartPingTimer(const TInt aMinutes);	    
    void SetHeaderL(RHTTPHeaders aHeaders, TInt aHdrField, const TDesC8& aHdrValue, RStringPool aPool);
private:
	RConnectionMonitor  iConnectionMonitor;
	RConnection      	iConnection;
	RSocketServ 		iSocketServ;
	CPeriodic*			iTimer;
	CPeriodic*			iPingTimer;
	TBool 				iConnected;
	TBool 				iAutoStart;
	TBool 				iCatchWiFi;
	TInt 				iPingInterval;
	TBuf<50>			iPingUrl;
	TBool				iConnectingWIFI;
//	RHTTPSession		iHttpSession;
	};

#endif  // __KEEPCONNECT_H__

