/*
 * ATReader.h
 *
 *  Created on: 11.07.2011
 *      Author: vl
 */

#ifndef ATREADER_H_
#define ATREADER_H_

#include <c32comm.h>
#include <f32file.h>
#include "logger1.h"

class CATReader : public CActive
	{
public:
	CATReader();
	~CATReader();
	static CATReader* NewLC();
	void ConstructL();
	void ReadAT();
	void RunL();
	TInt RunError(TInt aError);
	void DoCancel();
	TBuf8<256> iCommandRead;
	RCommServ iCommServ;
	RComm iComm;
	};


#endif /* ATREADER_H_ */
