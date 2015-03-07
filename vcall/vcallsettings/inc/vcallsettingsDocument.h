/*
========================================================================
 Name        : vcallsettingsDocument.h
 Author      : SQR
 Copyright   : 
 Description : 
========================================================================
*/
#ifndef VCALLSETTINGSDOCUMENT_H
#define VCALLSETTINGSDOCUMENT_H

#include <akndoc.h>
		
class CEikAppUi;

/**
* @class	CvcallsettingsDocument vcallsettingsDocument.h
* @brief	A CAknDocument-derived class is required by the S60 application 
*           framework. It is responsible for creating the AppUi object. 
*/
class CvcallsettingsDocument : public CAknDocument
	{
public: 
	// constructor
	static CvcallsettingsDocument* NewL( CEikApplication& aApp );

private: 
	// constructors
	CvcallsettingsDocument( CEikApplication& aApp );
	void ConstructL();
	
public: 
	// from base class CEikDocument
	CEikAppUi* CreateAppUiL();
	};
#endif // VCALLSETTINGSDOCUMENT_H
