/*
* ==============================================================================
*  Name        : helloworldbasic.pan
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

#ifndef __HELLOWORLDBASIC_PAN__
#define __HELLOWORLDBASIC_PAN__

/** HelloWorldBasic application panic codes */
enum THelloWorldBasicPanics
    {
    EHelloWorldBasicUi = 1
    // add further panics here
    };

inline void Panic(THelloWorldBasicPanics aReason)
    {
    _LIT(applicationName,"DiskActiveConf");
    User::Panic(applicationName, aReason);
    }

#endif // __HELLOWORLDBASIC_PAN__
