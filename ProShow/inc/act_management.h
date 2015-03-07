/*
 * act.h
 *
 *  Created on: 14.03.2010
 *      Author: vl
 */

#include <e32base.h>
#include <f32file.h>
#include "Constants.h"
#include "logger1.h"

class CNotifyer : public CActive
{
public:
	~CNotifyer();
	static CNotifyer* NewL(const TDesC& aPath);
	void Fun();
protected:
	CNotifyer(const TDesC& aPath);
	void ConstructL();

protected:
	virtual void RunL();
	virtual void DoCancel();
	virtual TInt RunError(TInt aError);

private:
	RFs iFs;
	TBuf<256> iPath;
	CDir* iDirList;
	TBuf<256> iName;
};
