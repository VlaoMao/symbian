/*
 * vCardBack.h
 *
 *  Created on: 01.11.2011
 *      Author: vl
 */

#ifndef VCARDBACK_H_
#define VCARDBACK_H_

#include <e32cmn.h>   //TUid
#include <e32std.h>   //User
#include <e32base.h>  //CArrayPtr, CleanupStack
#include <e32def.h>   //TBool
#include <s32file.h>  //RFileReadStream
#include <f32file.h>  //RFs
#include <cntdb.h>    //CContactDatabase
#include <cntdef.h>   //CContactIdArray
#include <cntfilt.h>  //CCntFilter

TBool ExportVCardL(const TDesC& aFileName, TInt aItemIndex);

#endif /* VCARDBACK_H_ */
