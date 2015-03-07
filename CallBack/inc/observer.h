/*
 * observer.h
 *
 *  Created on: 29.04.2011
 *      Author: Vladislav
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_
#include <e32msgqueue.h>
#include <pathinfo.h>
#include <etel3rdparty.h>
#include <f32file.h>
#include <s32file.h>
#include "logger1.h"
#include "shared.h"
#include "Window.h"
#include "Caller.h"




class CMyObserverClass : public CBase, public MPhoneReceiverObserver
{
public:
	CMyObserverClass(CWindow& aWindowClass);
	void ConstructL();
	static CMyObserverClass* NewL(CWindow& aWindowClass);
	static CMyObserverClass* NewLC(CWindow& aWindowClass);
	~CMyObserverClass();
	void CallRinging();
	void CallAnswered();
	void CallConnected();
	void CallDisconnecting();
	void CallDialling();
	void Idle();
	void SaveError(TInt aError);
	void TelNumber(TDes& aTelNumber);
	void SaveNumber();
	void Call();
	TBool iIsNeedToReCall;
private:
	TBuf<128> iTelNumber;
	TBuf<256> iAbsolutePath;
	TBool iIsConnected;
	CWindow* iWindow;
	CTelephony* iTelephony;
	CCaller* iCaller;
};

#endif /* OBSERVER_H_ */
