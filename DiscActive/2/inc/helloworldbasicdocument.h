/*
* ==============================================================================
*  Name        : helloworldbasicdocument.h
*  Part of     : Helloworldbasic
*  Interface   : 
*  Description : 
*  Version     : 
*
*  Copyright (c) 2005-2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation.
* ==============================================================================
*/

#ifndef __HELLOWORLDBASICDOCUMENT_H__
#define __HELLOWORLDBASICDOCUMENT_H__

// INCLUDES
#include <akndoc.h>

// FORWARD DECLARATIONS
class CHelloWorldBasicAppUi;
class CEikApplication;


// CLASS DECLARATION

/**
* CHelloWorldBasicDocument application class.
* An instance of class CHelloWorldBasicDocument is the Document part of the
* AVKON application framework for the HelloWorldBasic example application.
*/
class CHelloWorldBasicDocument : public CAknDocument
    {
    public: // Constructors and destructor

        /**
        * NewL.
        * Two-phased constructor.
        * Construct a CHelloWorldBasicDocument for the AVKON application aApp
        * using two phase construction, and return a pointer
        * to the created object.
        * @param aApp Application creating this document.
        * @return A pointer to the created instance of CHelloWorldBasicDocument.
        */
        static CHelloWorldBasicDocument* NewL( CEikApplication& aApp );

        /**
        * NewLC.
        * Two-phased constructor.
        * Construct a CHelloWorldBasicDocument for the AVKON application aApp
        * using two phase construction, and return a pointer
        * to the created object.
        * @param aApp Application creating this document.
        * @return A pointer to the created instance of CHelloWorldBasicDocument.
        */
        static CHelloWorldBasicDocument* NewLC( CEikApplication& aApp );

        /**
        * ~CHelloWorldBasicDocument
        * Virtual Destructor.
        */
        virtual ~CHelloWorldBasicDocument();

    public: // Functions from base classes

        /**
        * CreateAppUiL
        * From CEikDocument, CreateAppUiL.
        * Create a CHelloWorldBasicAppUi object and return a pointer to it.
        * The object returned is owned by the Uikon framework.
        * @return Pointer to created instance of AppUi.
        */
        CEikAppUi* CreateAppUiL();

    private: // Constructors

        /**
        * ConstructL
        * 2nd phase constructor.
        */
        void ConstructL();

        /**
        * CHelloWorldBasicDocument.
        * C++ default constructor.
        * @param aApp Application creating this document.
        */
        CHelloWorldBasicDocument( CEikApplication& aApp );

    };

#endif // __HELLOWORLDBASICDOCUMENT_H__

// End of File

