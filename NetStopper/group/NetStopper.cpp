/*
 * stopper.cpp
 *
 *  Created on: 22.02.2010
 *      Author: SQR
 */

#include <e32base.h>
#include <f32file.h>
#include <es_sock.h>
#include <es_enum.h>
#include <aknglobalnote.h>
#include <utf.h>
#include <aputils.h>
#include <commdb.h>
#include <apselect.h>
#include <e32cmn.h> //RArray
//#include <apaccesspointitem.h>
//#include <stringloader.h>
//#include <netstopper.rsg>
//#include <barsc.h>

class TElement
	{
public:
	TElement();
public:
	TBuf<256> iData;
	};
TElement::TElement()
	{
	_LIT(KTextBase,"BASEINIT");
	iData=KTextBase;
	}


LOCAL_C void ShowNoteL(const TDesC & aMessage)
	{
	CAknGlobalNote *iNote;
	TInt iNoteId;
	iNote=CAknGlobalNote::NewL();
	iNoteId=iNote->ShowNoteL(EAknGlobalInformationNote,aMessage);
	User::After(5000000);
	iNote->CancelNoteL(iNoteId);
	}
LOCAL_C void SaveToFile(const TDesC8& aText)
	{
	_LIT(KFile,"C:\\Data\\strings.txt");
	RFs session;
	RFile file;
	session.Connect();
	file.Create(session,KFile,EFileWrite);
	file.Write(aText);
	file.Close();
	session.Close();
	}
LOCAL_C void SaveToFileL(const TDesC& aText)
	{
	_LIT(KFile,"C:\\Data\\strings.txt");
	RFs session;
	RFile file;
	TFileText text;
	session.Connect();
	file.Create(session,KFile,EFileWrite);
	text.Set(file);
	text.Write(aText);
	file.Close();
	session.Close();
	}
/*
LOCAL_C void Open()
	{
	RFs iSession;
	TBuf8<256> iBuf;
//	TBuf16<256> iBBuf;
	RResourceFile iReader;
	User::LeaveIfError(iSession.Connect());
	iReader.OpenL(iSession,_L("\\resource\\apps\\NetStopper.rsc"));
	iReader.ReadL(iBuf,2);
	SaveToFile(iBuf);
	//iBBuf.Copy(iBuf);
	//ShowNoteL(iBBuf);
	}*/
LOCAL_C void Stop()
	{
	CArrayFixFlat<TElement>* array;
	TElement element;
	array=new(ELeave) CArrayFixFlat<TElement>(3);
	RFs session;
	TBuf<256> iBuffer;
	RFile file;
	TFileText text;
	TInt Show;
	TLex lex;
	session.Connect();
	/*TInt error=file.Open(session,_L("C:\\Data\\strings.txt"),EFileRead);
	if(error!=KErrNone)
		{
	file.Create(session,_L("C:\\Data\\strings.txt"),EFileWrite);
	text.Set(file);
	text.Write(_L("1"));
		}
	text.Set(file);
	text.Seek(ESeekStart);
	text.Read(iBuffer);
	lex.Assign(iBuffer);
	lex.Val(Show);
	iBuffer.Delete(0,sizeof iBuffer);
	
	while(text.Read(iBuffer)==KErrNone)
		{
	element.iData.Copy(iBuffer);
	array->AppendL(element);
	element.iData.Delete(0,sizeof element.iData);
	iBuffer.Delete(0,sizeof iBuffer);
		}*/
	//CCommsDatabase* data=CCommsDatabase::NewL();
	//CApSelect* iSelect=CApSelect::NewLC(*data,KEApIspTypeAll,EApBearerTypeAllBearers,KEApSortNameAscending);
	RConnection connection;
	RSocketServ socket;
	TUint count;
	TInt succeed = 0;
	TInt err;
	TBuf<56> noConnections( _L("Нет активных соединений"));
	TBuf<56> yesConnections(_L("Соединений остановлено: %d"));
	TConnectionInfoBuf info;
	User::LeaveIfError(socket.Connect());
	User::LeaveIfError(connection.Open(socket));
	TBuf8<256> ii;
	TBuf<256> iname;
	if(connection.EnumerateConnections(count)==KErrNone)
	    {
	for(TUint i=1;i<=count;i++)
		{
	if(connection.GetConnectionInfo(i,info)==KErrNone)
		{
	if(connection.Attach(info,RConnection::EAttachTypeNormal)==KErrNone)
	    {
	//iSelect->MoveToFirst();
	//iname=iSelect->Name();
	
	//ii=ConvertToUtf8(iname);
	//ShowNote(iname);
	//ii.Copy(iname);
	//  SaveToFileL(iname);
	err=connection.Stop();
	if(err==KErrNone)
		succeed++;
	    }
		}
		}
	    }
	yesConnections.Format(_L("Соединений остановлено: %d"),succeed);
	//HBufC* mess=StringLoader::LoadL(R_MESSAGE_NUM,succeed);
	if(succeed==0)
		ShowNoteL(noConnections);
	if(succeed>0)
		ShowNoteL(yesConnections);
	connection.Close();
	socket.Close();
	}
GLDEF_C TInt E32Main()
	{
	__UHEAP_MARK;
	CTrapCleanup* cleanup=CTrapCleanup::New();
	TRAPD(error,Stop());
	__ASSERT_ALWAYS(!error,User::Panic(_L("STOPPER-ERROR"),error));
	delete cleanup;
	__UHEAP_MARKEND;
	return 0;

	}
