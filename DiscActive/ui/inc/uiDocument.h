/*
========================================================================
 Name        : uiDocument.h
 Author      : SQR
 Copyright   : Your copyright notice
 Description : 
========================================================================
*/
#ifndef UIDOCUMENT_H
#define UIDOCUMENT_H

#include <akndoc.h>
		
class CEikAppUi;

/**
* @class	CuiDocument uiDocument.h
* @brief	A CAknDocument-derived class is required by the S60 application 
*           framework. It is responsible for creating the AppUi object. 
*/
class CuiDocument : public CAknDocument
	{
public: 
	// constructor
	static CuiDocument* NewL( CEikApplication& aApp );

private: 
	// constructors
	CuiDocument( CEikApplication& aApp );
	void ConstructL();
	
public: 
	// from base class CEikDocument
	CEikAppUi* CreateAppUiL();
	};
#endif // UIDOCUMENT_H
