/*
 * property.h
 *
 *  Created on: 15.12.2011
 *      Author: vl
 */

#ifndef PROPERTY_H_
#define PROPERTY_H_

#include <e32base.h>
#include <e32property.h>
#include "virtualobserver.h"
#include "logger1.h"

const TUid PropertyUID = {0xe14fff54};

class CPropImpl : public CActive
	{
public:
	CPropImpl();
	virtual ~CPropImpl();
	static CPropImpl* NewL();
	static CPropImpl* NewLC();
	void RunL();
	void DoCancel();
	TInt RunError(TInt aError);
	void Subscribe();
	void SetObserver(MVirtualObserver* aNewObserver);
private:
	void ConstructL();
	RProperty iProperty;
	MVirtualObserver* iObserver;
	};


#endif /* PROPERTY_H_ */
