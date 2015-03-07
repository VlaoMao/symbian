/*
 * ============================================================================
 *  Name     : ClientApplication.h
 *  Part of  : HTTP Client Example
 *  Created  : 06/26/2006 by Forum Nokia
 *  Version  : 2.0
 *  Copyright: Forum Nokia
 * ============================================================================
 */

#ifndef __CLIENT_APPLICATION_H__
#define __CLIENT_APPLICATION_H__

#include <aknapp.h>

class CClientApplication : public CAknApplication
    {
/*
* From CAknApplication
*/
public:
	/*
	* AppDllUid()
	*
	* Returns the UID for the Client application
	*
	* Params:
	*		-
	*
	* Returns:
	* 		UID of the application.
	*
	*/
    TUid AppDllUid() const;

/*
* From CAknApplication
*/
protected:
	/*
	* CreateDocumentL()
	*
	* Creates new document and returns pointer to it. Called by the application
	* DLL framework to create a new instance of the document associated with this
	* application.
	*
	* Params:
	*		-
	*
	* Returns:
	* 		-
	*
	*/
    CApaDocument*	CreateDocumentL();
    virtual TFileName ResourceFileName();
    };

#endif // __CLIENT_APPLICATION_H__
