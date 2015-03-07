/*
 * contsnts.h
 *
 *  Created on: 19.11.2011
 *      Author: vl
 */

#ifndef CONTSNTS_H_
#define CONTSNTS_H_

#include <e32base.h>

_LIT(KFileConfigDir,"C:\\System\\Apps\\ClipProcess\\");
_LIT(KFileConfig,"C:\\System\\Apps\\ClipProcess\\cfg");
_LIT(KPathFormat,"%S:\\System\\Data\\");
_LIT(KPathFormatFile,"%S:\\System\\Data\\Clipboard.cbd");
_LIT(KUrlSearchStandard,"4 http://yandex.ru/msearch?text=%S");
_LIT(KUrlSearchOther,"http://yandex.ru/msearch?text=%S");

class MNotifyChangeServer
	{
public:
	virtual void ClipboardChanged() = 0;
	virtual void HideRequest() = 0;
	};

struct OsVersion
    {
    TUint iMajor;
    TUint iMinor;
    };

#endif /* CONTSNTS_H_ */
