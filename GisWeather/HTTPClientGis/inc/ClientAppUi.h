/*
 * ============================================================================
 *  Name     : CClientAppUi of ClientAppUI.h
 *  Part of  : HTTP Client Example
 *  Created  : 06/26/2006 by Forum Nokia
 *  Version  : 2.0
 *  Copyright: Forum Nokia
 * ============================================================================
 */

#ifndef __CLIENT_APPUI_H__
#define __CLIENT_APPUI_H__

#include <aknappui.h>
#include <cdbcols.h>
#include <commdb.h>
#include "../../inc/Constants.h"


/*
* Forward declarations
*/
class CClientAppView;
class CClientEngine;

class CClientAppUi : public CAknAppUi
	{
public:
	/*
	* ConstructL()
	*
	* Perform the second phase construction of a CClientAppUi object.
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
	* CClientAppUi()
	*
	* First phase construction of CClientAppUi.
	*
	* Params:
	*		-
	*
	* Returns:
	* 		-
	*
	*/
	CClientAppUi();

	/*
	* ~CClientAppUi()
	*
	* Destructor for CClientAppUi.
	*
	* Params:
	*		-
	*
	* Returns:
	* 		-
	*
	*/
	~CClientAppUi();
	void StartDownload();
	void KillInformer();
	CArrayFixFlat<TIapData>* iEApList;
	void ReadIaps();

/*
* from CAknAppUi
*/
public:
	/*
	* HandleCommandL()
	*
	* Handles user commands.
	*
	* Params:
	*		aCommand: Command ID.
	*
	* Returns:
	* 		-
	*
	*/
	void HandleCommandL(TInt aCommand);
	virtual void HandleForegroundEventL(TBool aForeground);

	/*
	* DynInitMenuPaneL()
	*
	* Provides dynamic initialization of the menu pane.
	* Called by framework when menu pane is activated.
	*
	* Params:
	*		aMenuId: Resource ID identifying the menu pane to initialise.
	*		aMenuPane: The in-memory representation of the menu pane.
	*
	* Returns:
	* 		-
	*
	*/
	void DynInitMenuPaneL(TInt aMenuId, CEikMenuPane* aMenuPane);

private:
	CClientAppView*	iAppView;
	CClientEngine*			iClient;
	};

#endif // __CLIENT_APPUI_H__
