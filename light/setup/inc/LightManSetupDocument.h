/*
========================================================================
 Name        : LightManSetupDocument.h
 Author      : SQR
 Copyright   : 
 Description : 
========================================================================
*/
#ifndef LIGHTMANSETUPDOCUMENT_H
#define LIGHTMANSETUPDOCUMENT_H

#include <akndoc.h>
		
class CEikAppUi;

/**
* @class	CLightManSetupDocument LightManSetupDocument.h
* @brief	A CAknDocument-derived class is required by the S60 application 
*           framework. It is responsible for creating the AppUi object. 
*/
class CLightManSetupDocument : public CAknDocument
	{
public: 
	// constructor
	static CLightManSetupDocument* NewL( CEikApplication& aApp );

private: 
	// constructors
	CLightManSetupDocument( CEikApplication& aApp );
	void ConstructL();
	
public: 
	// from base class CEikDocument
	CEikAppUi* CreateAppUiL();
	};
#endif // LIGHTMANSETUPDOCUMENT_H
