/*
 * caller.h
 *
 *  Created on: 21.11.2011
 *      Author: vl
 */

#ifndef CALLER_H_
#define CALLER_H_

#include <e32base.h>
#include <etel3rdparty.h>
#include "logger1.h"

class CCaller : public CActive
	{
public:
	~CCaller();
	static CCaller* NewL();
	static CCaller* NewLC();
	void Call(const TDesC& aNUmber);
	void RunL();
	void DoCancel();
	TInt RunError(TInt aError);
private:
	void ConstructL();
	CCaller();
	CTelephony* iTelephony;
	};

#endif /* CALLER_H_ */
