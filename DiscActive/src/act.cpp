/*
 * act.cpp
 *
 *  Created on: 04.11.2010
 *      Author: vl
 */

#include "act.h"
//#include "show.h"
#include <coedef.h>
//#include "rect.h"

CMyClass::CMyClass() : CActive(EPriorityStandard)
{
	//TODO Конструктор класса со стандартным приоритетом
}
CMyClass::~CMyClass()
{
	Cancel(); //TODO Отмена таймера
	iFs.Close();
	iws.Close();
	CleanupStack::PopAndDestroy(5,&iws);
}
void CMyClass::ConstructL()
{
	CActiveScheduler::Add(this); //TODO Добавление активного объекта в планировщик
	iFs.Connect();

	ReadConf();

	iws.Connect();
	 CleanupClosePushL(iws);
	 iscreen = new(ELeave) CWsScreenDevice(iws);
	 CleanupStack::PushL(iscreen);
	 iscreen->Construct();
	 ConstRWG(iws);
	 iwg.Construct(reinterpret_cast<TUint32>(&iwg),EFalse);
	 CleanupClosePushL(iwg);
	 iwg.SetOrdinalPosition(235,ECoeWinPriorityAlwaysAtFront);
	 iscreen->CreateContext(igc);
	 CleanupStack::PushL(igc);
	 ConstRW(iws);
	 iwindow.Construct(iwg,reinterpret_cast<TUint32>(&iwg)+1);
	 CleanupClosePushL(iwindow);
	 iwindow.SetBackgroundColor(param.Color);
	 iwindow.Activate();
	 iwindow.SetExtent(TPoint(param.X,param.Y),TSize(param.Height,param.Weight));
	 iwindow.SetVisible(EFalse);
	 iwindow.SetNonFading(ETrue);
	// igc->Activate(iwindow);
	 irect=TRect(iwindow.Size());
	// iwindow.Invalidate(irect);
	// iwindow.BeginRedraw(irect);
	 //igc->SetBrushStyle(CGraphicsContext::ESolidBrush);
	 //igc->Clear();
	 //igc->SetBrushColor(param.Color);
	 //igc->DrawRect(irect);
	 //iwindow.EndRedraw();
	 //igc->Deactivate();
	 iws.Flush();
}
void CMyClass::ConstRWG(RWsSession& ws)
    {
    RWindowGroup self(ws);
    iwg = self;
    }
void CMyClass::ConstRW(RWsSession& ws)
    {
    RWindow self(ws);
    iwindow = self;
    }
void CMyClass::Draw()
    {
	     iwindow.SetVisible(ETrue);
	     igc->Activate(iwindow);
	     iwindow.BeginRedraw(irect);
   	     igc->SetBrushStyle(CGraphicsContext::ESolidBrush);
   	     igc->Clear();
   	     igc->SetBrushColor(param.Color);
   	     igc->DrawRect(irect);
   	     iwindow.EndRedraw();
   	     igc->Deactivate();
   	     iws.Flush();
   	     User::After((param.longest)*1000);
   	     iwindow.SetVisible(EFalse);
   	     iws.Flush();
    }
void CMyClass::RunL()
{
	Draw();
	Fun(); //TODO Запуск нового цикла
}
TInt CMyClass::RunError(TInt aError)
{
	return KErrNone;
}
void CMyClass::DoCancel()
{
	iFs.Close(); //TODO Отмена активного действия
}
CMyClass* CMyClass::NewL()
{
	CMyClass* self = new(ELeave) CMyClass();
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
}
void CMyClass::Fun()
{
	iFs.NotifyChange(ENotifyAll,iStatus);
	SetActive(); //TODO помечаем объект активным
}

TInt CMyClass::ReadConf()
    {
    RFile aFile;
    TFileText text;
    TLex lex;
    TUint32 rgb;
    TBuf<64> TextBuf;
    TInt err;
    TInt errOpen = aFile.Open(iFs,KConfig,EFileRead);
    if(errOpen==KErrNone)
	{
	text.Set(aFile);

	text.Read(TextBuf); __LOGSTR1("param X string=%S",&TextBuf);
	lex.Assign(TextBuf);
	lex.Val(param.X); __LOGSTR1("param.X=%d",param.X);

	text.Read(TextBuf); __LOGSTR1("param Y string=%S",&TextBuf);
	lex.Assign(TextBuf);
	lex.Val(param.Y); __LOGSTR1("param.Y=%d",param.Y);

	text.Read(TextBuf); __LOGSTR1("param Height string=%S",&TextBuf);
	lex.Assign(TextBuf);
	lex.Val(param.Height); __LOGSTR1("param.Height=%d",param.Height);

	text.Read(TextBuf);
	lex.Assign(TextBuf);
	lex.Val(param.Weight); __LOGSTR1("param.Weight=%d",param.Weight);

	text.Read(TextBuf);
	lex.Assign(TextBuf);
	lex.Val(param.longest); __LOGSTR1("param.longest=%d",param.longest);

	text.Read(TextBuf); __LOGSTR1("RGB: %S",&TextBuf);
	if(TextBuf.Left(2)==_L("0x"))
	    TextBuf.Delete(0,2);
	lex.Assign(TextBuf);
	lex.Val(rgb,EHex);
	param.Color = rgb;  __LOGSTR1("RGB: 0x%x",rgb);

	err = KErrNone;
	aFile.Close();
	}else{
	param.X = 235;
	param.Y = 0;
	param.Height = 5;
	param.Weight = 50;
	param.longest = 10;
	param.Color = 0x00ff0000;
	err = errOpen;
		}
    return err;
    }
