/*
 * anim : myanim.cpp
 *
 *  Created on: 27.11.2010
 *  Author: vl
 */

#include "myanim.h"
#include "logger1.h"
void CMyAnim::ConstructL(TAny*/* aArgs*/)
    {
//    ActivateL();
// begin by chen
    iPeriodic = CPeriodic::NewL(CActive::EPriorityStandard);
// end by chen
    }

// begin by chen
TInt CMyAnim::Tick(TAny* aObject)
	{
	if(aObject!=NULL)
		{
		CMyAnim* self = reinterpret_cast<CMyAnim*>(aObject);
		self->DoTick();
		}
	}

void CMyAnim::DoTick() // indirectly called
	{
	if(iPeriodic!=NULL)
		{
		iPeriodic->Cancel();
		}
	// Long key press event detected!
RDebug::Printf("CMyAnim::DoTick, Long Key Press Event");
	}
CMyAnim* CMyAnim::NewL()
    {
    CMyAnim* self = new(ELeave) CMyAnim();
    self->ConstructL(self);
    return self;
    }
CMyAnim::CMyAnim()
    {

    }
CMyAnim::~CMyAnim()
    {
    if(iPeriodic)
	{
	delete iPeriodic;
	iPeriodic = NULL;
	}
    }
TBool CMyAnim::OfferRawEvent(const TRawEvent& aRawEvent)
    {
    __LOGSTR1("captured: %d", aRawEvent.Type());
    return EFalse;
    }
