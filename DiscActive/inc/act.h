/*
 * act.h
 *
 *  Created on: 04.11.2010
 *      Author: vl
 */

#include <e32base.h>
#include <f32file.h>
#include <w32std.h>
#include <gdi.h>
#include "logger1.h"

_LIT(KConfig,"C:\\System\\Apps\\DiskActive\\DiskActive.cfg");
struct Parameters
    {
public:
    TInt X;
    TInt Y;
    TInt Weight;
    TInt Height;
    TInt longest;
    TRgb Color;
    };
class CMyClass : public CActive
{
public:
	~CMyClass();
	static CMyClass* NewL();
	void Fun();
protected:
	CMyClass();
	void ConstructL();
	TInt ReadConf();
protected:
	virtual void RunL();
	virtual void DoCancel();
	virtual TInt RunError(TInt aError);
	void Draw();
	void ConstRWG(RWsSession& ws);
	void ConstRW(RWsSession& ws);
private:
	RFs iFs;
	RWsSession iws;
	CWsScreenDevice* iscreen;
	RWindowGroup iwg;
	CWindowGc* igc;
	RWindow iwindow;
	TRect irect;
	Parameters param;
};
