/*
 * control.cpp
 *
 *  Created on: 24.05.2011
 *      Author: vl
 */

#include "control.h"

CMyControl::CMyControl()
	{

	}
CMyControl::~CMyControl()
	{

	}
CMyControl* CMyControl::NewL(const TRect& aRect,const CCoeControl* aParent)
	{
	CMyControl* self = new(ELeave) CMyControl();
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	CleanupStack::Pop(self);
	return self;
	}
void CMyControl::ConstructL(const TRect& aRect)
	{
	CreateWindowL();
	EnableDragEvents();
	//InitComponentArrayL();
	SetRect(aRect);
	ActivateL();
	}
/*void CMyControl::SizeChanged()
	{
	UpdateControls();
	}
void CMyControl::UpdateControls()
	{
	TPoint position;

	    // Goes through all components of this container control
	    CCoeControlArray::TCursor cursor = Components().Begin();
	    CCoeControl* ctrl = NULL;
	    while ((ctrl = cursor.Control<CCoeControl>()) != NULL)
	    	{
	        // If control is not visible, do not set it's position
	    	if (!ctrl->IsVisible())
	    		{
	            cursor.Next();
	            continue;
	            }

	        // Set position
	        ctrl->SetPosition(position);

	        // Set size
	        TSize size = ctrl->MinimumSize();
	        size.SetSize(Rect().Width(),size.iHeight);
	        ctrl->SetSize(size);

	        // Calculate position
	        position.iY += size.iHeight;

	        // Does control fit to view?
	        if (position.iY >= Rect().iBr.iY)
	            {
	            ctrl->MakeVisible(EFalse);
	            }
	        else
	            {
	            ctrl->MakeVisible(ETrue);
	            }

	        cursor.Next();
	    	}
	}*/
void CMyControl::Draw(const TRect& /*aRect*/)
	{
	CWindowGc& gc = SystemGc();
	gc.SetBrushColor(KRgbBlack);
	gc.Clear(Rect());
	}
