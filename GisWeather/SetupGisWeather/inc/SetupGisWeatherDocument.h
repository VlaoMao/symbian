/*
========================================================================
 Name        : SetupGisWeatherDocument.h
 Author      : SQR
 Copyright   : Created SQR, 2010, Russia
 Description : 
========================================================================
*/
#ifndef SETUPGISWEATHERDOCUMENT_H
#define SETUPGISWEATHERDOCUMENT_H

#include <akndoc.h>
		
class CEikAppUi;

/**
* @class	CSetupGisWeatherDocument SetupGisWeatherDocument.h
* @brief	A CAknDocument-derived class is required by the S60 application 
*           framework. It is responsible for creating the AppUi object. 
*/
class CSetupGisWeatherDocument : public CAknDocument
	{
public: 
	// constructor
	static CSetupGisWeatherDocument* NewL( CEikApplication& aApp );

private: 
	// constructors
	CSetupGisWeatherDocument( CEikApplication& aApp );
	void ConstructL();
	
public: 
	// from base class CEikDocument
	CEikAppUi* CreateAppUiL();
	};
#endif // SETUPGISWEATHERDOCUMENT_H
