/*
 * proc.cpp
 *
 *  Created on: 04.02.2010
 *      Author: SQR
 */

#include <f32file.h>
#include <apgtask.h>
#include <aknglobalnote.h>
#include <e32base.h>


_LIT(KFilePath,"C:\\Data\\TaskList.txt");
_LIT(KNameProc,"*");
//_LIT8(KCesFF,"\ufe00");

class TElement
	{
public:
	TElement();
public:
	TBuf<100> iData;
	};
TElement::TElement()
	{
	_LIT(KTextBase,"BASE");
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

LOCAL_C void CreateTaskListL()
	{
	TInt forix;
	RFs session;
	RFile exFile;
	TFileText textFile;
	TFindProcess procFinder;
	TFullName result;
	TBuf<200> writeBuf;
	TBuf<100> show;
	TInt cycle=0;
	TBuf8<20> wrtemp;
	CArrayFixFlat<TElement>* fixflat;
	fixflat=new(ELeave) CArrayFixFlat<TElement>(3);
	TElement element;
	User::LeaveIfError(session.Connect());
	show.Append(_L("Task's found and save:"));
	procFinder=KNameProc();
	exFile.Create(session,KFilePath,EFileWrite|EFileStream|EFileShareAny);
	//exFile.Write(KCesFF);
	textFile.Set(exFile);
	element.iData.Delete(0,sizeof element.iData);
	while(procFinder.Next(result)==KErrNone)
		{
		++cycle;
		/*writeBuf.Copy(result);
		textFile.Write(writeBuf);
		writeBuf.Delete(0,sizeof writeBuf);*/
		element.iData.Append(result);
		fixflat->AppendL(element);
		element.iData.Delete(0,sizeof element.iData);
		}
	TKeyArrayFix key(0,ECmpFolded);
	fixflat->Sort(key);
	for(forix=0;forix<fixflat->Count();forix++)
		textFile.Write((*fixflat)[forix].iData);
	show.AppendNum(cycle);
	ShowNoteL(show);
	exFile.Close();
	session.Close();
	}

LOCAL_C void ListProcL()
	{
	RFs fsSession;
	RFile file;
	TFileText text;
	TFileName path;
	RProcess procHandle;
	TBuf<200> readBuf;
	TBuf<100> shownote;
	TFullName aRes;
	TFindProcess procfinder;
	TInt acycle=0;
	shownote.Append(_L("Tasks's killed:"));
	User::LeaveIfError(fsSession.Connect());
	TInt err=file.Open(fsSession,KFilePath,EFileShareExclusive|EFileWrite);
	//file.Seek(ESeekAdress,2);
	if(err==KErrNotFound)
		CreateTaskListL();
	if(err==KErrNone){
	text.Set(file);
	while(text.Read(readBuf)==KErrNone)
		{
		procfinder=readBuf;
		while(procfinder.Next(aRes)==KErrNone)
			{
			User::LeaveIfError(procHandle.Open(procfinder,EOwnerThread));
			procHandle.Terminate(EExitTerminate);
			procHandle.Close();
			++acycle;
			}
		}
	shownote.AppendNum(acycle);
	ShowNoteL(shownote);
	file.Close();
	fsSession.Close();
	}
	}
GLDEF_C TInt E32Main()
	{
	__UHEAP_MARK;
	CTrapCleanup* cleanup=CTrapCleanup::New();
	TRAPD(error,ListProcL());
	__ASSERT_ALWAYS(!error,User::Panic(_L("EXEUI"),error));
	delete cleanup;
	__UHEAP_MARKEND;
	return 0;
	}
