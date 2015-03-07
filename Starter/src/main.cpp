/*
 * wallpaper.cpp
 *
 *  Created on: 01.02.2010
 *      Author: SQR
 */

#include "nmisdk/NativeModule.h"
#include "starter.h"

class StarterModule : public NativeModule{
private:
	enum{
	RebootFunction,
	ShutdownFunction
	};
protected:
	TInt ExpectedRuntimeVersion(){
	return Runtime::VERSION;
	}
	const char *ModuleVersion(){return "10";}
	void ConstructL(){
	runtime->AddNativeFunctionL(_L("reboot"),0,0,RebootFunction);
	runtime->AddNativeFunctionL(_L("shutdown"),0,0,ShutdownFunction);
	
	runtime->AddConstantL(_L("about"),_L("starter mShell module, version 1.0\nCreated by SQR\n2011, Russia"));
	}
	Runtime::Value ExecuteL(TInt index, Runtime::Value *params, TInt paramCount,
							TRequestStatus &status){
							switch (index){
							case RebootFunction:
								{
								RStarterSession sess;
								User::LeaveIfError(sess.Connect());
								sess.Reset(RStarterSession::ENormalRestart);
								sess.Close();
								break;
								}

							case ShutdownFunction:
								{
								RStarterSession sess;
								User::LeaveIfError(sess.Connect());
								sess.Shutdown();
								sess.Close();
								break;
								}
							}
							return KErrNone;
					}
};
EXPORT_C NativeModule* NewStarterModuleL(){
return new(ELeave) StarterModule;
}


#ifndef EKA2
GLDEF_C TInt E32Dll(TDllReason) {
 return KErrNone; 
}
#endif
