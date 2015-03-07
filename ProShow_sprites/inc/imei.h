/*
 * autoscript : imei.h
 *
 *  Created on: 17.01.2011
 *  Author: vl
 */

#ifndef IMEI_H_
#define IMEI_H_
#include <e32base.h>
#include <etel3rdparty.h>

enum Funtions
{
	ENothing = 0, EImeiGet = 1, EModelGet = 2
};
class CInfoApp : public CActive
{
	private:
		void ConstructL();
		CTelephony* iTelephony;
		CTelephony::TPhoneIdV1 iPhoneIdV1;
        CTelephony::TPhoneIdV1Pckg iPhoneIdV1Pckg;

	public:
		CInfoApp(TDes& aIMEI);
		~CInfoApp();
		static void GetIMEI(TDes& aIMEI);
		static void GetPhoneModel(TDes& aModel);
		TDes& iInternalBuf;
		TInt iWhatGet;

	private:

        /*
        These are the pure virtual methods from CActive that
        MUST be implemented by all active objects
        */
		void RunL();
		void DoCancel();
};
#endif /* IMEI_H_ */
