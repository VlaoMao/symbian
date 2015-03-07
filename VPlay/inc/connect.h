/*
 * connect.h
 *
 *  Created on: 09.06.2011
 *      Author: vl
 */

#ifndef CONNECT_H_
#define CONNECT_H_

class MConnect
	{
public:
	virtual void SendClose() = 0;
	};

struct ScreenSize
	{
public:
	TInt iX;
	TInt iY;
	};
#endif /* CONNECT_H_ */
