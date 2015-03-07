/*
 * rfile : form.h
 *
 *  Created on: 14.11.2010
 *  Author: vl
 */

#ifndef FORM_H_
#define FORM_H_

#include <aknform.h>
#include <eikedwin.h>
#include <e32cmn.h>

class CMyForm : public CAknForm
    {
public:
    static CMyForm* NewL();
    virtual ~CMyForm();
    TInt ExecuteLD(TInt aResourceId);
    void PrepareLC(TInt aResourceId);
private:
    CMyForm();
    void ConstructL();
    void PreLayoutDynInitL();
    TBool QuerySaveChangesL();
    TBool SaveFormDataL();
    void DoNotSaveFormDataL();
    TBuf<256> iDataName;
    };
#endif /* FORM_H_ */
