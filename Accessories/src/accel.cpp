#include "accel.h"

CAccel::CAccel() : iAccelPersist(EFalse)
    {
    }
CAccel::~CAccel()
    {
        StopMonitor();
    }
CAccel* CAccel::NewLC()
    {
        CAccel* self = new (ELeave) CAccel();
        _CPUSH(self);
        self->ConstructL();
        return self;
    }
CAccel* CAccel::NewL()
    {
        CAccel* self = CAccel::NewLC();
        _CPOP(self);
        return self;
    }
void CAccel::ConstructL()
    {
        __LOGSTR("CPropertyListener::ConstructL");
        x = 0;
        y = 0;
        z = 0;
        CSensrvChannelFinder* channelFinder = CSensrvChannelFinder::NewL();
        RSensrvChannelInfoList ChannelInfoList;

        TSensrvChannelInfo mySearchConditions; // none, so matches all.
        mySearchConditions.iChannelDataTypeId = KSensrvChannelTypeIdAccelerometerXYZAxisData;
        channelFinder->FindChannelsL(ChannelInfoList,mySearchConditions);
        if(ChannelInfoList.Count() != 0)
            {
                //accel found
                iAccelPersist = ETrue;
            }

        iSensrvChannel = CSensrvChannel::NewL( ChannelInfoList[0] );
        iSensrvChannel->OpenChannelL();

        ChannelInfoList.Close();
        __LOGSTR("CPropertListener::ConstructL ends");
    }
void CAccel::DataReceived(CSensrvChannel &aChannel, TInt aCount, TInt aDataLost)
    {
         if(aChannel.GetChannelInfo().iChannelType == KSensrvChannelTypeIdAccelerometerXYZAxisData)
             {
                TSensrvAccelerometerAxisData XYZData;
                TPckg<TSensrvAccelerometerAxisData> XYZPackage( XYZData );
                aChannel.GetData( XYZPackage );
                TInt length = XYZPackage.Length();
                TBool isSnaked = EFalse;
                TSensrvAccelerometerAxisData dat = XYZPackage();

//                __LOGSTR1("XYZPackage length: %d",length);
                __LOGSTR1("iAxisX: %d",dat.iAxisX);
                if(dat.iAxisX > 100)
                    iConnector->Snaked(ESnakeRight);
                if(dat.iAxisX < -100)
                    iConnector->Snaked(ESnakeRight);
                //__LOGSTR1("Count snakeds: %d",count);
                //__LOGSTR1("middleX: %d",middleX1);
             }
    }
void CAccel::DataError(CSensrvChannel &aChannel, TSensrvErrorSeverity aError)
    {
        __LOGSTR1("CAccel::DataError on channel, error: %d",aError);
    }
void CAccel::GetDataListenerInterfaceL(TUid aInterfaceUid, TAny *&aInterface)
    {

    }
void CAccel::StartMonitor()
    {
        iSensrvChannel->StartDataListeningL(this,100,1,0);
    }
void CAccel::StopMonitor()
    {
        TInt err = iSensrvChannel->StopDataListening();
        __LOGSTR1("WARNING: CAccel::StopDataListening returned status: %d",err);
    }
void CAccel::SetObserver(MConnector *aNewConnector)
    {
        if(aNewConnector)
            iConnector = aNewConnector;
    }
