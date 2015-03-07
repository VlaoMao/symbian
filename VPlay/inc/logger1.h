/*
 * logger1.h
 *
 *  Created on: 28.02.2010
 *      Author: SQR
 */

#ifndef __FILELOGGER_H__
#define __FILELOGGER_H__
#include <e32std.h>
#include <flogger.h>
_LIT(KLogsDir,"observer");
_LIT(KLogsFileName,"log.txt");
#define __LOGSTR(S){_LIT(KTmpStr,S);RFileLogger::WriteFormat(KLogsDir(),KLogsFileName(),EFileLoggingModeAppend,KTmpStr());}
#define __LOGSTR1(S,P0){_LIT(KTmpStr,S);RFileLogger::WriteFormat(KLogsDir(),KLogsFileName(),EFileLoggingModeAppend,TRefByValue<const TDesC>(KTmpStr()),P0);}
#define __LOGSTR2(S,P0,P1){_LIT(KTmpStr,S);RFileLogger::WriteFormat(KLogsDir(),KLogsFileName,EFileLoggingModeAppend,TRefByValue<const TDesC>(KTmpStr()),P0,P1);}

#endif
