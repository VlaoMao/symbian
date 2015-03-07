/*
 * AccMonitor.h
 *
 *  Created on: 21.10.2011
 *      Author: vl
 */

#ifndef ACCMONITOR_H_
#define ACCMONITOR_H_

#include <accmonitor.h>
#include <w32std.h>
#include <apgtask.h>
#include <apgcli.h>
#include <apacmdln.h>
#include <aknkeylock.h>
#include <etel3rdparty.h>
#include <mpxplaybackutility.h>
//
#include <mpxmessage2.h>
#include <mpxplaybackobserver.h>
#include <mpxmessagegeneraldefs.h>
#include <mpxplaybackmessage.h>
//
#include "logger1.h"
#include "act.h"
#include "callchange.h"
#include "accel.h"


const TUid KAppUidMPX                 = { 0x102072C3 };
const TUid KMPXPlaybackViewTypeUid    = { 0x101FFCA0 }; // Now Playing View
const TUid KMPXCollectionViewTypeUid  = { 0x101FFCA1 }; // Collection View

const TInt KPlayPauseScan = 182;


class CAcc : public CBase, public MAccMonitorObserver, public MMPXPlaybackObserver, public MActiveCallListener, public MConnector
	{
public:
	static CAcc* NewL();
	static CAcc* NewLC();
	void RunPlayerAndActivate();
	 void LaunchMPXViewL( const TUid& aViewUid );
	 void LaunchMPXViewLNoSimulate( const TUid& aViewUid );
	 CAcc();
	 TBool iIsAccessoryConnected;//Подключена ли гарнитура
	 TBool iIsConnectedAllowed;//Играть ли при запуске плеера
	 TBool iNeedControlState_State_to_idle;//Контролировать поведение после завершения звонка
     void Snaked(Snakes aSnake);//движения
private:
	~CAcc();
	void ConnectedL (CAccMonitorInfo *aAccessoryInfo);
	void DisconnectedL (CAccMonitorInfo *aAccessoryInfo);
	void AccMonitorObserverError (TInt aError);
	void ConstructL();
	TBool IsSwitchEnabled();//Разрешение работы
	CPhoneReceiver* iPhoneReceiver;//Определение вызовов
	MMPXPlaybackUtility* iUtility;//Управление плеером
	void HandlePlaybackMessage(CMPXMessage* aMessage, TInt aErr);
	void StateChangedFromIdle();
	void StateChangedToIdle();
	void RequestMediaL();
    CAccel* iAccel;
	};
#endif /* ACCMONITOR_H_ */
