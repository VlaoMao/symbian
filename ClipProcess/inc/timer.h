/*
 * timer.h
 *
 *  Created on: 20.11.2011
 *      Author: vl
 */

#ifndef TIMER_H_
#define TIMER_H_
#include <e32base.h>
#include "constants.h"
#include "logger1.h"

class CPTimer : public CActive
	{
private:
	CPTimer();
public:
	~CPTimer();
	static CPTimer* NewL();
	static CPTimer* NewLC();
	static TInt CallBackTimer(TAny* aObject);
	void StartTimer(TInt aSeconds);
	void Tick();
	void RunL();
	TInt RunError(TInt aError);
	void DoCancel();
	void SetObserver(MNotifyChangeServer* aObserver);
	void StopTimer();
private:
	void ConstructL();
	CPeriodic* iTimer;
	MNotifyChangeServer* iObserver;
	};

#endif /* TIMER_H_ */
