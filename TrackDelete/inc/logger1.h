/*
 * logger1.h
 *
 *  Created on: 21.10.2011
 *      Author: SQR
 */

#ifndef __FILELOGGER_H__
#define __FILELOGGER_H__

#ifdef __DEBUG

#include <e32std.h>
#include <flogger.h>

_LIT(KLogsDir,"TrackDelete");
_LIT(KLogsFileName,"log.txt");

#define __LOGSTR(S)\
		{\
			_LIT(KTmpStr,S);\
			RFileLogger::WriteFormat(KLogsDir(),\
			KLogsFileName(),EFileLoggingModeAppend,KTmpStr());\
		}
#define __LOGSTR1(S,P0)\
		{\
			_LIT(KTmpStr,S);\
			RFileLogger::WriteFormat(KLogsDir(),\
			KLogsFileName(),EFileLoggingModeAppend,TRefByValue<const TDesC>(KTmpStr()),P0);\
		}
#define __LOGSTR2(S,P0,P1)\
		{\
			_LIT(KTmpStr,S);\
			RFileLogger::WriteFormat(KLogsDir(),\
			KLogsFileName,EFileLoggingModeAppend,TRefByValue<const TDesC>(KTmpStr()),P0,P1);\
		}
#define __LOGSTR3(S,P0,P1,P2)\
		{\
			_LIT(KTmpStr,S);\
			RFileLogger::WriteFormat(KLogsDir(),\
			KLogsFileName,EFileLoggingModeAppend,TRefByValue<const TDesC>(KTmpStr()),P0,P1,P2);\
		}
#define __LOGSTR4(S,P0,P1,P2,P3)\
		{\
			_LIT(KTmpStr,S);\
			RFileLogger::WriteFormat(KLogsDir(),\
			KLogsFileName,EFileLoggingModeAppend,TRefByValue<const TDesC>(KTmpStr()),P0,P1,P2,P3);\
		}
#endif
#endif

#ifndef __DEBUG// Если релиз, объявляем только заглушки макросов
#define __LOGSTR(S){}
#define __LOGSTR1(S,P0){}
#define __LOGSTR2(S,P0,P1){}
#define __LOGSTR3(S,P0,P1,P2){}
#define __LOGSTR4(S,P0,P1,P2,P3){}
#endif
#define _CPUSH(S){CleanupStack::PushL(S);}
#define _CPOP(S){CleanupStack::Pop(S);}
#define _CPOPD(S){CleanupStack::PopAndDestroy(S);}
