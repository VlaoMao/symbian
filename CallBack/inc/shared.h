/*
 * shared.h
 *
 *  Created on: 03.07.2011
 *      Author: vl
 */

#ifndef SHARED_H_
#define SHARED_H_
#include <etel3rdparty.h>

_LIT(KFileConfig,"C:\\System\\Apps\\FastCallBack\\number");
_LIT(KFilePos,"C:\\System\\Apps\\FastCallBack\\pos");

class MPhoneReceiverObserver
{
public:
	virtual void CallRinging() = 0;
	virtual void CallAnswered()=0;
	virtual void CallConnected()=0;
	virtual void CallDisconnecting()=0;
	virtual void CallDialling()=0;
	virtual void Idle()=0;
	CTelephony::TCallStatus iCallStatus;
};


#endif /* SHARED_H_ */
