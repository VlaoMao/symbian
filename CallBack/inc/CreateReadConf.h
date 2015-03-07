/*
 * CreateReadConf.h
 *
 *  Created on: 01.07.2011
 *      Author: vl
 */

#ifndef CREATEREADCONF_H_
#define CREATEREADCONF_H_

#include <f32file.h>
#include "logger1.h"
#include "shared.h"

inline void CreateConfigFile()
	{
	RFs fs;
	fs.Connect();
	RFile file;
	TInt err = fs.MkDirAll(_L("C:\\System\\Apps\\fastCallback\\"));
	__LOGSTR1("Mkdir: %d",err);
	file.Replace(fs,KFilePos,EFileRead|EFileWrite);
	TFileText text;
	file.Write(0,_L8("\xff\xfe"));//Сигнатура файла
	text.Set(file);
	text.Write(_L("0"));//iX
	text.Write(_L("0"));//iY
	text.Write(_L("100"));//width
	text.Write(_L("100"));//heigth
	text.Write(_L("15"));//font size

	file.Close();
	}
inline void CreateConfigFile(TInt aX,TInt aY,TInt aWidth,TInt aHeight)
    {
    RFs fs;
    User::LeaveIfError(fs.Connect());
    RFile file;
    TInt err = fs.MkDirAll(_L("C:\\System\\Apps\\fastCallback\\"));
    __LOGSTR1("Mkdir: %d",err);
    file.Replace(fs,KFilePos,EFileRead|EFileWrite);
    TFileText text;
    file.Write(0,_L8("\xff\xfe"));//Сигнатура файла
    text.Set(file);
    TBuf<56> buf;
    TBuf<12> format(_L("%d"));
    buf.Format(format,aX);
    text.Write(buf);//iX
    buf.Format(format,aY);
    text.Write(buf);//iY
    buf.Format(format,aWidth);
    text.Write(buf);//width
    buf.Format(format,aHeight);
    text.Write(buf);//heigth
    text.Write(_L("15"));//font size

    file.Close();
    }

#endif /* CREATEREADCONF_H_ */
