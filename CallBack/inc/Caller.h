/*
 * Caller.h
 *
 *  Created on: 04.07.2011
 *      Author: vl
 */

#ifndef CALLER_H_
#define CALLER_H_
#include <f32file.h>
#include <etel3rdparty.h>
#include <etel.h>
#include <w32std.h>
#include "logger1.h"
#include "shared.h"

class CCaller : public CActive
	{
public:
	CCaller();
	~CCaller();
	static CCaller* NewLC();
	void CallL();
	//void HangUpEtel();
	void HangUpKey();
	void RunL();
	TInt RunError(TInt aError);
	void DoCancel();
	void ConstructL();
private:
	RFs iFs;
	RFile iFile;
	TFileText iText;
	CTelephony* iTelephony;
	};
#endif /* CALLER_H_ */
