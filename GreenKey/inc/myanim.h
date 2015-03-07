/*
 * anim : myanim.h
 *
 *  Created on: 27.11.2010
 *  Author: vl
 */
#ifndef __MYANIM_H__
#define __MYANIM_H__

#include <w32adll.h> // CAnim

class CMyAnim : public CSpriteAnim
    {
public: // con/de structors
    ~CMyAnim();
    CMyAnim();
public: // MEventHandler
    static CMyAnim* NewL();
	TBool OfferRawEvent(const TRawEvent &aRawEvent);
public: // CSpriteAnim
    void ConstructL(TAny *aArgs);

private:
// begin by chen
private:
	static TInt Tick(TAny* aObject); // directly called
	void DoTick(); // indirectly called

private:
	TRawEvent iLastEvent;
	CPeriodic* iPeriodic;
// end by chen
    };

#endif // __MYANIM_H__
