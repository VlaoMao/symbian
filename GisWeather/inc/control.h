/*
 * control.h
 *
 *  Created on: 24.05.2011
 *      Author: vl
 */
#include <coecntrl.h>

#ifndef CONTROL_H_
#define CONTROL_H_

class CMyControl : public CCoeControl
	{
public:
	static CMyControl* NewL(const TRect& aRect,const CCoeControl* aParent=NULL);
	virtual ~CMyControl();
private:
	void Draw(const TRect& aRect);
	//void SizeChanged();
public:
	//void UpdateControls();
private:
	CMyControl();
	void ConstructL(const TRect& aRect);
	};
#endif /* CONTROL_H_ */
