/*
 * observer.h
 *
 *  Created on: 29.04.2011
 *      Author: Vladislav
 */

#ifndef OBSERVER_H_
#define OBSERVER_H_
#include "act.h"
class CMyObserverClass : public MPhoneReceiverObserver,public CActive
{
public:
	CMyObserverClass();
	void ConstructL();
	static CMyObserverClass* NewL();
	~CMyObserverClass();
	void CallRinging();
	void CallAnswered();
	void RunL();
	void DoCancel();

private:
//Define object to phone receiver

	CTelephony*		iTelephony;
	CTelephony::TCallId	iCallID;
};

#endif /* OBSERVER_H_ */
