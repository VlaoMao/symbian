/*
 * virtualobserver.h
 *
 *  Created on: 15.12.2011
 *      Author: vl
 */

#ifndef VIRTUALOBSERVER_H_
#define VIRTUALOBSERVER_H_
#include <e32base.h>

class MVirtualObserver
	{
public:
	virtual void NeedSetPos() = 0;
	};



#endif /* VIRTUALOBSERVER_H_ */
