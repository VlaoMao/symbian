/*
 * ============================================================================
 *  Name     : CClientDocument of ClientDocument.h
 *  Part of  : HTTP Client Example
 *  Created  : 06/26/2006 by Forum Nokia
 *  Version  : 2.0
 *  Copyright: Forum Nokia
 * ============================================================================
 */

#ifndef __CLIENT_DOCUMENT_H__
#define __CLIENT_DOCUMENT_H__

#include <akndoc.h>
#include <apgwgnam.h>

/**
* Forward declarations
*/
class CClientAppUi;
class CEikApplication;

class CClientDocument : public CAknDocument
    {
public:
	/*
	* NewL()
	*
	* Create a CClientDocument object.
	*
	* Params:
	*		aApp: Reference to application this document relates.
	*
	* Returns:
	*
	*
	*/
    static CClientDocument* NewL(CEikApplication& aApp);

	/*
	* NewLC()
	*
	* Create a CClientDocument object.
	*
	* Params:
	*		aApp: Reference to application this document relates.
	*
	* Returns:
	*
	*
	*/
    static CClientDocument* NewLC(CEikApplication& aApp);

	/*
	* ~CClientDocument()
	*
	* Destructor for CClientDocument.
	*
	* Params:
	*		-
	*
	* Returns:
	* 		-
	*
	*/
    ~CClientDocument();

/*
* From CAknDocument
*/
public:
	/*
	* CreateAppUiL()
	*
	* Creates the application user interface, and returns a pointer to it;
	* the framework takes ownership of this object
	*
	* Params:
	*		-
	*
	* Returns:
	*		Pointer to created application ui.
	*
	*/
    CEikAppUi* CreateAppUiL();
    virtual void UpdateTaskNameL(CApaWindowGroupName*aWgName);

private:
	/*
	* ConstructL()
	*
	* Second phase construction.
	*
	* Params:
	*		-
	*
	* Returns:
	* 		-
	*
	*/
    void ConstructL();

	/*
	* CClientDocument()
	*
	* First phase construction.
	*
	* Params:
	*		aApp: Reference to application this document relates.
	*
	* Returns:
	* 		-
	*
	*/
    CClientDocument(CEikApplication& aApp);

    };


#endif // __CLIENT_DOCUMENT_H__
