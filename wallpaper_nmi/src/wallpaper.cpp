/*
 * wallpaper.cpp
 *
 *  Created on: 01.02.2010
 *      Author: SQR
 */

#include "nmisdk/NativeModule.h"
#include <aknswallpaperutils.h>

class WallPaperModule : public NativeModule{
private:
	CCoeEnv* aCoeEnv;
	Runtime::Value value;
	TBuf<256> WallImage;
	enum{
	ChangeFunction
	};
protected:
	TInt ExpectedRuntimeVersion(){
	return Runtime::VERSION;
	}
	const char *ModuleVersion(){return "10";}
	void ConstructL(){
	runtime->AddNativeFunctionL(_L("change"),1,1,ChangeFunction);
	
	runtime->AddConstantL(_L("about"),_L("wallpaper mShell module, version 1.0\nCreated by SQR\n2011, Russia"));
	}
	Runtime::Value ExecuteL(TInt index, Runtime::Value *params, TInt paramCount,
							TRequestStatus &status){
							switch (index){
							case ChangeFunction:
								WallImage.Copy(params[0].GetPtrCL());
								AknsWallpaperUtils::SetIdleWallpaper(WallImage,aCoeEnv);
								value=runtime->NewStringL(WallImage);
								break;
							}
	return value;
					}
};
EXPORT_C NativeModule* NewWallPaperModuleL(){
return new(ELeave) WallPaperModule;
}


#ifndef EKA2
GLDEF_C TInt E32Dll(TDllReason) {
 return KErrNone; 
}
#endif
