#ifndef __CSMSHANDLER_H__
#define __CSMSHANDLER_H__

//  INCLUDES
#include <e32base.h>
#include <msvapi.h>
#include <mtuireg.h>
#include <txtrich.h>
#include <tz.h>
#include <tzconverter.h>
//#include "logger1.h"
#include "crash_handler.h"
// CONSTANTS
const TInt KBfrLength = 20;

// FORWARD DECLARATIONS
class CSmsAppUi;
class CClientMtmRegistry;
class CSmsClientMtm;

enum KSMSTypes
	{
	EMessageIn,
	EMessageOut
	};
_LIT(KTimeFormat,"%d.%d.%d %d:%d:%d");
_LIT(KDateConstFormat,"%D%M%Y%/0%1%/1%2%/2%3%/3 %:0%H%:1%T%:2%S");
_LIT(KMessName,"Имя: ");
_LIT(KMessNumber,"Номер: ");
_LIT(KMessDate,"Дата: ");
_LIT(KMessMess,"Сообщение: ");
_LIT(KMessIn,"Входящее сообщение");
_LIT(KMessOut,"Исходящее сообщение");
_LIT(KWorkFilePath,"C:\\Data\\SMSBackup.txt");
_LIT(KWorkFileInbox,"C:\\Data\\SMSBackup_inbox.txt");
_LIT(KWorkFileSent,"C:\\Data\\q.txt");
// CLASS DECLARATION
/**
* CSmsHandler application engine class.
* Takes care of sending and receiveing SMS messages using the SMS client MTM.
* Interacts with the application UI class.
*/
class CSmsHandler : public CActive, public MMsvSessionObserver
    {
    public: // Constructors and destructor

        /**
        * NewL.
        * Two-phased constructor.
        * @param aSmsAppUi Pointer to AppUi instance.
        * @return Pointer to the created instance of CSmsHandler.
        */
        static CSmsHandler* NewL( );

        /**
        * NewLC.
        * Two-phased constructor.
        * @param aSmsAppUi Pointer to AppUi instance.
        * @return Pointer to the created instance of CSmsHandler.
        */
        static CSmsHandler* NewLC();

        /**
        * ~CSmsHandler
        * Destructor.
        */
        virtual ~CSmsHandler();

    public: // New functions
	void ReadInboxMsgs(); //Added by Kiran
	void ReadSentMsgs();
	void WriteToFile(const TDesC8& aSMSContent8);
	void WriteToFile(const TDesC16& aMsgHeader, const TDesC16& aNumber,const TDesC& aDate,const TDesC16& aMsgBody,const KSMSTypes aType);
        /**
        * SendL.
        * Starts the process of creating and sending an SMS message.
        * @param aRecipientNumber The number of the recipent.
        * @param aMessageText The message text.
        * @return ETrue if successful, EFalse if not.
        */
       TBool SendL( const TDesC& aRecipientNumber,
                    const TDesC& aMessageText );

        /**
        * ViewL.
        * Displays a received SMS message.
        */
        void ViewL();

    public: // Functions from base classes

        /**
        * From MMsvSessionObserver, HandleSessionEventL.
        * Handles notifications of events from the Message Server.
        * @param aEvent The event that has taken place
        * @param aArg1 Event type-specific argument value
        * @param aArg2 Event type-specific argument value
        * @param aArg3 Event type-specific argument value
        */
        void HandleSessionEventL( TMsvSessionEvent aEvent, TAny* aArg1,
                                  TAny* aArg2, TAny* aArg3 );

    protected: // Functions from base classes

        /**
        * From CActive, DoCancel.
        * Cancels any outstanding requests.
        */
        void DoCancel();

        /**
        * From CActive, RunL.
        * Handles an active object�s request completion event.
        */
        void RunL();

    private: // Constructors

        /**
        * CSmsHandler.
        * C++ default constructor.
        * @param aSmsAppUi Pointer to AppUi instance.
        */
        CSmsHandler();

        /**
        * ConstructL.
        * 2nd phase constructor.
        */
        void ConstructL();

    private: // New functions

        /**
        * AccessMtmL.
        * Access the MTM Registry and create an SMS specific Client MTM instance.
        */
        void AccessMtmL();

        /**
        * CreateMsgL.
        * Create an SMS message.
        * @return ETrue if successful, EFalse is unsuccessful.
        */
	    TBool CreateMsgL();

        /**
        * ScheduleL.
        * Schedule an SMS message for sending.
        */
        void ScheduleL();

        /**
        * MessageReceivedL.
        * Handles a received SMS message.
        * @param aEntryId The message server id of the received message.
        */
        void MessageReceivedL( TMsvId aEntryId );
        void MessageSent(TMsvId aEntryId);

        /**
        * ValidateL.
        * Validate an SMS message.
        * @return ETrue if successful, EFalse is unsuccessful.
        */
        TBool ValidateL();

    private: // Enumeration

        /**
        * TState, enumeration for the state of the handler, used by RunL().
        */
        enum TState
            {
            EWaitingForMoving = 1,
            EWaitingForScheduling
            };

    private: // Data

        /**
        * iState, the state of the handler.
        */
        TState iState;

        /**
        * iSession, the contact database.
        * Owned by CSmsHandler object.
        */
        CMsvSession* iSession;

        /**
        * iMtmRegistry, client MTM registry.
        * Owned by CSmsHandler object.
        */
        CClientMtmRegistry* iMtmRegistry;

        /**
        * iSmsMtm, SMS specific Client MTM.
        * Owned by CSmsHandler object.
        */
        CSmsClientMtm* iSmsMtm;

        /**
        * iOperation, the current message server operation.
        * Owned by CSmsHandler object.
        */
        CMsvOperation* iOperation;

        /**
        * iRecipientNumber, telephone number of the recipient.
        */
//        TBuf<EMaxTelephoneNumberLength> iRecipientNumber;
		  TBuf<15> iRecipientNumber;

        /**
        * iMessageText, SMS message text.
        */
//        TBuf<EMaxMessageLength> iMessageText;
		  TBuf<160> iMessageText;

        /**
        * iSmsAppUi, application UI
        * Not owned by CSmsHandler object.
        */
        CSmsAppUi* iSmsAppUi;

        /**
        * iMtmUiRegistry, User Interface MTM Registry.
        * Owned by CSmsHandler object.
        */
        CMtmUiRegistry* iMtmUiRegistry;

        /**
        * iSelection, entry selection to hold received messages.
        * Owned by CSmsHandler object.
        */
        CMsvEntrySelection* iSelection;

        /**
        * iNextUnread, index of the next unread message in iSelection.
        */
        TInt iNextUnread;
    };

#endif // __CSMSHANDLER_H__

