/*
 * rfile : form.cpp
 *
 *  Created on: 14.11.2010
 *  Author: vl
 */
#include "form.h"
CMyForm* CMyForm::NewL()
    {
    CMyForm* self = new(ELeave) CMyForm();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }
CMyForm::CMyForm()
    {

    }
CMyForm::~CMyForm()
    {

    }
TBool CMyForm::SaveFormDataL()
    {
    return ETrue;
    }
void CMyForm::DoNotSaveFormDataL()
    {

    }
void CMyForm::DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane)
    {
    CAknForm::DynInitMenuPaneL(aResourceId,aMenuPane);
    if(aResourceId==R_AVKON_FORM_MENUPANE)
	{
	aMenuPane->SetItemDimmed(EAknFormCmdLabel,ETrue);
	aMenuPane->SetItemDimmed(EAknFormCmdAdd,ETrue);
	aMenuPane->SetItemDimmed(EAknFormCmdDelete,ETrue);
	}
    }
