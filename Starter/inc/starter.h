/*
 * starter.h
 *
 *  Created on: 30.10.2011
 *      Author: vl
 */

#ifndef STARTER_H_
#define STARTER_H_

#include <e32base.h>
#include <e32std.h>

class RStarterSession : public RSessionBase
	{
public:
	enum	TGlobalState {
							ENormal = 100,
							EAlarm,
							ECharging,
							EOffline,
							EBTSap
						};
	enum	TResetReason {
							ENormalRestart = 0x64,
							//ESoftReset = 0x65
							//EHardReset = 0x66
							ELanguageSwitchReset = 100,
							ENormalRFSReset = 101,
							EDeepRFSReset = 102,
							EUnknownReset = 104,
							EOperatorSettingReset = 105,
							ENetworkModeChangeReset = 106,
							ESIMStatusChangeReset = 107,
							EDRMReset = 108,
							EFirmwareUpdate = 109,
							EDataRestoreReset = 110,
							EFieldTestReset = 111
							};
	IMPORT_C TInt	ActivateRfForEmergencyCall();
	IMPORT_C TInt	Connect();
	IMPORT_C TInt	DeactivateRfAfterEmergencyCall();
	IMPORT_C TInt	EndSplashScreen();
	IMPORT_C TBool	IsRTCTimeValid();
	IMPORT_C void	Reset(const TResetReason);
	IMPORT_C TInt	ResetNetwork();
	IMPORT_C TInt	SetState(const TGlobalState);
	IMPORT_C void	Shutdown();
	};
#endif /* STARTER_H_ */
