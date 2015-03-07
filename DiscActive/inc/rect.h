/*
 * rect.h
 *
 *  Created on: 06.11.2010
 *      Author: vl
 */

#ifndef RECT_H_
#define RECT_H_
#include <e32base.h>
#include <w32std.h>
#include <coedef.h>
LOCAL_C void DrawRect()
    {
    RWsSession ws;
    ws.Connect();
    CleanupClosePushL(ws);
    CWsScreenDevice* screen = new(ELeave) CWsScreenDevice(ws);
    CleanupStack::PushL(screen);
    screen->Construct();
    RWindowGroup wg(ws);
    wg.Construct(reinterpret_cast<TUint32>(&wg),EFalse);
    CleanupClosePushL(wg);
    wg.SetOrdinalPosition(235,ECoeWinPriorityAlwaysAtFront);
    CWindowGc* gc;
    screen->CreateContext(gc);
    CleanupStack::PushL(gc);
    RWindow window(ws);
    window.Construct(wg,reinterpret_cast<TUint32>(&wg)+1);
    CleanupClosePushL(window);
    window.SetBackgroundColor(TRgb(0x90,0x90,0x90));
    window.Activate();
    window.SetExtent(TPoint(235,0),TSize(5,50));
    window.SetVisible(ETrue);
    gc->Activate(window);
    TRect rect=TRect(window.Size());
    window.Invalidate(rect);
    window.BeginRedraw(rect);
    gc->SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc->Clear();
    gc->SetBrushColor(KRgbRed);
    gc->DrawRect(rect);

    window.EndRedraw();

    gc->Deactivate();

    ws.Flush();
    User::After(1*1000);
    CleanupStack::PopAndDestroy(5,&ws);
    }
#endif /* RECT_H_ */
