/*
 * change_trap.h
 *
 *  Created on: 19.11.2011
 *      Author: vl
 */

#ifndef CHANGE_TRAP_H_
#define CHANGE_TRAP_H_

#include <e32base.h>
#include <f32file.h>
#include <hal.h>
#include "logger1.h"
#include "constants.h"

class CChangeTrap : public CActive
	{
private:
	CChangeTrap();
	void ConstructL();
public:
	~CChangeTrap();
	static CChangeTrap* NewL();
	static CChangeTrap* NewLC();
	void RunL();
	void DoCancel();
	TInt RunError(TInt aError);
	void StartMonitoring();
	void SetObserver(MNotifyChangeServer* aNewObserver);
	void StopMonitoring();
	RFs iFs;
	TInt iClipboardDrive;
	TBuf<64> iClipboardName;
	TBuf<64> iClipboardPath;
	MNotifyChangeServer* iObserver;
	};
#endif /* CHANGE_TRAP_H_ */
