/*
 * ============================================================================
 *  Name     : Client.pan
 *  Part of  : HTTP Client Example
 *  Created  : 06/26/2006 by Forum Nokia
 *  Version  : 2.0
 *  Copyright: Forum Nokia
 * ============================================================================
 */

#ifndef __CLIENT_PAN__
#define __CLIENT_PAN__

/** Client application panic codes */
enum TClientPanics 
    {
    EClientUi = 1,
    EClientView,
    EClientEngine
    // add further panics here
    };

inline void Panic(TClientPanics aReason)
    {
	_LIT(applicationName,"GisWetherDowndloader");
    User::Panic(applicationName, aReason);
    }

#endif // __CLIENT_PAN__
