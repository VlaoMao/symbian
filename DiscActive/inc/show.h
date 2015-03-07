/*
 * show.h
 *
 *  Created on: 04.11.2010
 *      Author: vl
 */

#ifndef SHOW_H_
#define SHOW_H_
#include<aknglobalnote.h>
LOCAL_C void Show()
{
	TBuf<54> buf;
	buf.Copy(_L("Событие!"));
	CAknGlobalNote* note = CAknGlobalNote::NewL();
	TInt noteId = note->ShowNoteL(EAknGlobalInformationNote,buf);
	User::After(2000000);
	note->CancelNoteL(noteId);
}

#endif /* SHOW_H_ */
