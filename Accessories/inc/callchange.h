/*
 * callchange.h
 *
 *  Created on: 22.10.2011
 *      Author: vl
 */

#ifndef CALLCHANGE_H_
#define CALLCHANGE_H_

class MActiveCallListener
	{
public:
	virtual void StateChangedFromIdle() = 0;//Используется для переключения плеера на паузу во время звонка
	virtual void StateChangedToIdle()=0;
	};

#endif /* CALLCHANGE_H_ */
