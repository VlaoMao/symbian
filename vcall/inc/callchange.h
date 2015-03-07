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
    virtual void CallConnected() = 0;
    virtual void CallDisconnected() = 0;
	};

#endif /* CALLCHANGE_H_ */
