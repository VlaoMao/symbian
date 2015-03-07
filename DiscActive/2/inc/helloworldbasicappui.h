/*
* ==============================================================================
*  Name        : helloworldbasicappui.h
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

#ifndef __HELLOWORLDBASICAPPUI_H__
#define __HELLOWORLDBASICAPPUI_H__

// INCLUDES
#include <aknappui.h>


// FORWARD DECLARATIONS
class CHelloWorldBasicAppView;


// CLASS DECLARATION
/**
* CHelloWorldBasicAppUi application UI class.
* Interacts with the user through the UI and request message processing
* from the handler class
*/
class CHelloWorldBasicAppUi : public CAknAppUi
    {
    public: // Constructors and destructor

        /**
        * ConstructL.
        * 2nd phase constructor.
        */
        void ConstructL();

        /**
        * CHelloWorldBasicAppUi.
        * C++ default constructor. This needs to be public due to
        * the way the framework constructs the AppUi
        */
        CHelloWorldBasicAppUi();

        /**
        * ~CHelloWorldBasicAppUi.
        * Virtual Destructor.
        */
        virtual ~CHelloWorldBasicAppUi();

    private:  // Functions from base classes

        /**
        * From CEikAppUi, HandleCommandL.
        * Takes care of command handling.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );

        /**
        *  HandleStatusPaneSizeChange.
        *  Called by the framework when the application status pane
 		*  size is changed.
        */

		void HandleStatusPaneSizeChange();
        
    private: // Data

        /**
        * The application view
        * Owned by CHelloWorldBasicAppUi
        */
        CHelloWorldBasicAppView* iAppView;
        
        
    };

#endif // __HELLOWORLDBASICAPPUI_H__

// End of File

