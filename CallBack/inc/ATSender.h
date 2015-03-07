/*
 * ATSender.h
 *
 *  Created on: 11.07.2011
 *      Author: vl
 */

#ifndef ATSENDER_H_
#define ATSENDER_H_

#include <c32comm.h>
#include "logger1.h"
#include "ATReader.h"

class CATSender : public CActive
	{
public:
	CATSender(CATReader& aReader);
	~CATSender();
	static CATSender* NewLC(CATReader& aReader);
	void ConstructL();
	void SendAT();
	void SendAT2();
	void SendAT3();
	void RunL();
	TInt RunError(TInt aError);
	void DoCancel();
	TBuf8<256> iCommandSend;
	RCommServ iCommServ;
	RComm iComm;
	TInt iNummCommand;
	CATReader* iATReader;
	};
#endif /* ATSENDER_H_ */
