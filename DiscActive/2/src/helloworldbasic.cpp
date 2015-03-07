/*
* ==============================================================================
*  Name        : helloworldbasic.cpp
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

// INCLUDE FILES
#include <eikstart.h>
#include "helloworldbasicapplication.h"


LOCAL_C CApaApplication* NewApplication()
	{
	return new CHelloWorldBasicApplication;
	}

GLDEF_C TInt E32Main()
	{
	return EikStart::RunApplication( NewApplication );
	}

