/*
 * AccMonitor.cpp
 *
 *  Created on: 21.10.2011
 *      Author: vl
 */

#include "Acc.h"

CAcc::CAcc(): iIsAccessoryConnected(EFalse),iIsConnectedAllowed(EFalse),iNeedControlState_State_to_idle(EFalse)
	{

	}
CAcc::~CAcc()
	{
	CleanupStack::PopAndDestroy(2);//iPhoneReceiver,iUtility
    iAccel->StopMonitor();
	}
CAcc* CAcc::NewL()
	{
	CAcc* self = CAcc::NewLC();
	_CPOP(self);
	return self;
	}
CAcc* CAcc::NewLC()
	{
	CAcc* self = new (ELeave) CAcc();
	_CPUSH(self);
	self->ConstructL();
	return self;
	}
void CAcc::ConnectedL (CAccMonitorInfo *aAccessoryInfo)
	{
	__LOGSTR1("Connected, device type: %d",aAccessoryInfo->AccDeviceType());
	if(iUtility)
		iUtility->AddObserverL(*this);
	if(aAccessoryInfo->AccDeviceType() == KAccMonHeadset)
		{
		__LOGSTR("Headset connected");
		__LOGSTR1("Switch enabled: %d",IsSwitchEnabled());
		iIsAccessoryConnected = ETrue;
		iIsConnectedAllowed = ETrue;
		if(IsSwitchEnabled())
            {
                iAccel->StartMonitor();
                RunPlayerAndActivate();
            }
		}
	}
void CAcc::DisconnectedL (CAccMonitorInfo *aAccessoryInfo)
	{
	__LOGSTR("Disconnected headset");
	__LOGSTR1("Switch enabled: %d",IsSwitchEnabled());
	iIsAccessoryConnected = EFalse;
	iIsConnectedAllowed = EFalse;
	if(IsSwitchEnabled())
		{
		//if(iUtility->StateL() == EPbStatePlaying)
			//{
			iUtility->CommandL(EPbCmdPause);
			//}
		}
	if(iPhoneReceiver->IsActiveCallPersist())
		{
		iNeedControlState_State_to_idle = ETrue;
		}
		//SimulateRawEvent(KPlayPauseScan);
	}
void CAcc::AccMonitorObserverError (TInt aError)
	{
	__LOGSTR1("monitor error: %d",aError);
	}
void CAcc::ConstructL()
	{
	__LOGSTR("ConstructL");
	iUtility = MMPXPlaybackUtility::NewL(KPbModeActivePlayer,this);
	_CPUSH(iUtility);
	CAccMonitor* accMonitor = CAccMonitor::NewLC();
    iAccel = CAccel::NewL();
    iAccel->SetObserver(this);
	iPhoneReceiver = CPhoneReceiver::NewLC();
	iPhoneReceiver->SetObserver(this);
	RAccMonCapabilityArray capabilityArray;
	CleanupClosePushL( capabilityArray );
	capabilityArray.Append( KAccMonHeadset );
	__LOGSTR("Start observing");
	accMonitor->StartObservingL( this, capabilityArray );
	CActiveScheduler::Start();
	__LOGSTR("End observing");
	CleanupStack::PopAndDestroy( &capabilityArray );
	CleanupStack::PopAndDestroy( accMonitor );
	}
void CAcc::RunPlayerAndActivate()
	{
	__LOGSTR("RunPlayer");
	LaunchMPXViewL(KMPXPlaybackViewTypeUid);
	}
void CAcc::LaunchMPXViewL( const TUid& aViewUid )
	{
	__LOGSTR("LaunchMPXView");
	// Construct MPX parameter string
	   TBuf8<16> param;
	   param.FillZ(16);
	   param[8] = 0x01;
	   param[12] = (TUint8) (aViewUid.iUid & 0x000000ff);
	   param[13] = (TUint8)((aViewUid.iUid & 0x0000ff00) >> 8);
	   param[14] = (TUint8)((aViewUid.iUid & 0x00ff0000) >> 16);
	   param[15] = (TUint8)((aViewUid.iUid & 0xff000000) >> 24);

	   RWsSession sess;
	   User::LeaveIfError(sess.Connect());
	   TApaTaskList taskList( sess );
	   TApaTask task = taskList.FindApp( KAppUidMPX );

	   if ( task.Exists() )
	     {
	    // task.SendMessage( KAppUidMPX, param );
		   iNeedControlState_State_to_idle = EFalse;
	     if(iUtility->StateL() != EPbStatePlaying)
	         iUtility->CommandL(EPbCmdPlay);
	     return;
	     }

	    RApaLsSession apaSession;
	    TApaAppInfo appInfo;
	    User::LeaveIfError( apaSession.Connect() );
	    CleanupClosePushL( apaSession );

	    User::LeaveIfError( apaSession.GetAppInfo( appInfo, KAppUidMPX ) );

	    CApaCommandLine *cmdLine = CApaCommandLine::NewLC();
	    cmdLine->SetExecutableNameL( appInfo.iFullName );
	    cmdLine->SetCommandL( EApaCommandRun );

	    // Collection view is the default view at startup
	    if( aViewUid != KMPXCollectionViewTypeUid )
	      {
	      cmdLine->SetTailEndL( param );
	      }

	  User::LeaveIfError( apaSession.StartApp( *cmdLine ) );
	  //User::After(6000000);
      //iUtility->CommandL(EPbCmdPlay);

	  CleanupStack::PopAndDestroy( 2 ); // cmdLine, apaSession
	  sess.Close();
	  }
void CAcc::LaunchMPXViewLNoSimulate( const TUid& aViewUid )
	{
	__LOGSTR("LaunchMPXView");
	// Construct MPX parameter string
	   TBuf8<16> param;
	   param.FillZ(16);
	   param[8] = 0x01;
	   param[12] = (TUint8) (aViewUid.iUid & 0x000000ff);
	   param[13] = (TUint8)((aViewUid.iUid & 0x0000ff00) >> 8);
	   param[14] = (TUint8)((aViewUid.iUid & 0x00ff0000) >> 16);
	   param[15] = (TUint8)((aViewUid.iUid & 0xff000000) >> 24);

	   RWsSession sess;
	   User::LeaveIfError(sess.Connect());
	   TApaTaskList taskList( sess );
	   TApaTask task = taskList.FindApp( KAppUidMPX );

	   if ( task.Exists() )
	     {
	     task.SendMessage( KAppUidMPX, param );
	     return;
	     }

	    RApaLsSession apaSession;
	    TApaAppInfo appInfo;
	    User::LeaveIfError( apaSession.Connect() );
	    CleanupClosePushL( apaSession );

	    User::LeaveIfError( apaSession.GetAppInfo( appInfo, KAppUidMPX ) );

	    CApaCommandLine *cmdLine = CApaCommandLine::NewLC();
	    cmdLine->SetExecutableNameL( appInfo.iFullName );
	    cmdLine->SetCommandL( EApaCommandRun );

	    // Collection view is the default view at startup
	    if( aViewUid != KMPXCollectionViewTypeUid )
	      {
	      cmdLine->SetTailEndL( param );
	      }

	  User::LeaveIfError( apaSession.StartApp( *cmdLine ) );

	  CleanupStack::PopAndDestroy( 2 ); // cmdLine, apaSession
	  sess.Close();
	}

TBool CAcc::IsSwitchEnabled()
	{
	if(iPhoneReceiver->IsActiveCallPersist())
		{
		__LOGSTR("IsSwitchEnabled: FALSE");
		return EFalse;
		}else{
			__LOGSTR("IsSwitchEnabled: TRUE");
			return ETrue;
		}
	}
void CAcc::HandlePlaybackMessage(CMPXMessage* aMessage, TInt aErr)
	{
	TMPXMessageId id(aMessage->ValueTObjectL<TMPXMessageId>(KMPXMessageGeneralId));
	//__LOGSTR1("HandlePlayBackMessage: 0x%x",id);

	        if (KMPXMessageGeneral == id)
	                {
	                TInt event(aMessage->ValueTObjectL<TInt>(KMPXMessageGeneralEvent));
	               // __LOGSTR1("PlayBackEvent: %d",event);
	                switch (event)
	                        {
	                        case TMPXPlaybackMessage::EInitializeComplete:
	                                {
	                                __LOGSTR("Initialise complete");
	                                if(iIsAccessoryConnected && iIsConnectedAllowed)
	                                	{
	                                    iUtility->CommandL(EPbCmdPlay);
	                                    iIsConnectedAllowed = EFalse;
	                                    iUtility->RemoveObserverL(*this);
	                                	}
	                                break;
	                                }
	                        case TMPXPlaybackMessage::EStateChanged:
	                        	{
	                        	__LOGSTR("StateChanged");
	                        	if(iNeedControlState_State_to_idle)
	                        		{
	                        		__LOGSTR("Need state pause");
	                        		iNeedControlState_State_to_idle = EFalse;
	                        		iUtility->CommandL(EPbCmdPause);
	                        		iUtility->RemoveObserverL(*this);
	                        		}
	                        	break;
	                        	}
	                        default:
	                                {
	                                break;
	                                }
	                        }
	                }

	}
void CAcc::StateChangedFromIdle()
	{
	__LOGSTR1("StateChangedFromIdle, iIsAccessoryConnected: %d",iIsAccessoryConnected);
	if(iIsAccessoryConnected)
		{
		iUtility->CommandL(EPbCmdPause);
		}
	}
void CAcc::StateChangedToIdle()
	{
	__LOGSTR1("StateChangedToIdle, iIsAccessoryConnected: %d",iIsAccessoryConnected);
	__LOGSTR1("iUtility state: %d",iUtility->StateL());
	if(iIsAccessoryConnected)
		{
		iUtility->CommandL(EPbCmdPlay);
		}else{
			if(iNeedControlState_State_to_idle)
				{
				__LOGSTR("iNeedControlState_State_to_idle");
				iUtility->AddObserverL(*this);
				__LOGSTR("Added observer");
				}
		}
	}
void CAcc::Snaked(Snakes aSnake)
    {
        __LOGSTR1("Snaked: %d",aSnake);
    }
