/*
 * vCardBack.cpp
 *
 *  Created on: 01.11.2011
 *      Author: vl
 */

#include "vCardBack.h"

TBool ExportVCardL(const TDesC& aFileName, TInt aItemIndex)
{
  RFs fileSession;
  RFile file;

  User::LeaveIfError(fileSession.Connect());
  CleanupClosePushL(fileSession);

  if (file.Replace(fileSession, aFileName, EFileWrite) != KErrNone)
      {
      //failed to create the file
      CleanupStack::PopAndDestroy(); //fileSession
      return EFalse;
      }
  CleanupClosePushL(file);

  //open a write stream to the file
  RFileWriteStream outputFileStream(file);
  CleanupClosePushL(outputFileStream);

  //open the default contacts database
  CContactDatabase* contactsDb = CContactDatabase::OpenL();
  CleanupStack::PushL(contactsDb);

  //create an array of contact IDs to export
  CContactIdArray* exportContacts = CContactIdArray::NewL();
  CleanupStack::PushL(exportContacts);

  //use a filter to get only contact items (e.g. templates are excluded)
  CCntFilter *filter = CCntFilter::NewLC();
  filter->SetContactFilterTypeALL(EFalse);
  filter->SetContactFilterTypeCard(ETrue);
  contactsDb->FilterDatabaseL(*filter);

  //create an array to hold all filtered contact items
  CContactIdArray* contactIds;
  contactIds = CContactIdArray::NewLC(filter->iIds);

  //add given contact(by index) to the array of contact IDs to export
  if((*contactIds).Count() >= aItemIndex)
      exportContacts->AddL((*contactIds)[aItemIndex] );

  CleanupStack::PopAndDestroy(2); //contactIds, filter

  //KVersitEntityUidVCard is used to identify a vCard
  TUid uid = TUid::Uid(KVersitEntityUidVCard);
  contactsDb->ExportSelectedContactsL(uid,
                                      *exportContacts,
                                       outputFileStream,
                                       //contact ID is no exported
                                       CContactDatabase::EExcludeUid);

  CleanupStack::PopAndDestroy(5); //exportContacts,contactsDb,
                  //outputFileStream,file,fileSession

  return ETrue;
}
