/*
 * crash_handler.h
 *
 *  Created on: 07.10.2011
 *      Author: SQR
 */
#ifndef __DEBUGM_H__
#define __DEBUGM_H__

#include <e32svr.h>

#ifdef _UNICODE

#define WIDEN2(x) L ## x
#define WIDEN(x) WIDEN2(x)
#define __DBG_FILE__ WIDEN(__FILE__)

#define _TD(a) L ## a

#else

#define __DBG_FILE__ __FILE__
#define _TD(a) a

#endif//_UNICODE


#ifdef __DEBUG

#define DBG_WATCHALLOC(a) (RDebug::Print(_L("%s(%d) : [MemAloc] Allocated address 0x%08x ********************"), __DBG_FILE__, __LINE__, (a)))
//#define DBG_WATCHALLOC
#define DBG_PRINT_MSG(msg) (RDebug::Print(_L("%s(%d) : %s"), __DBG_FILE__, __LINE__, (msg)))

#else

#define DBG_WATCHALLOC
#define DBG_PRINT_MSG

#endif//_DEBUG

#endif//__DEBUGM_H__

#ifndef __CRASH_HANDLER_ENABLED__
#define __CRASH_HANDLER_ENABLED__
#include "logger1.h"

#define __CH__(){__LOGSTR2("Function in file: %S,line: %d",__DBG_FILE__,__LINE__);}
#define __CHD__(S,D){if( S != KErrNone ){\
					__LOGSTR3("Function in file: %S,line: %d exitted with status: %d",__DBG_FILE__,__LINE__,S);\
					User::Panic(D,S);\
					}}
#endif
