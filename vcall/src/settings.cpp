#include "settings.h"

CSettings::CSettings()
{

}
CSettings::~CSettings()
{

}

void CSettings::ConstructL()
{
    RFs fs;
    RFile file;
    TFileText text;
    TLex lex;
    TBuf<256> buf;
    User::LeaveIfError(fs.Connect());
    if(file.Open(fs,_L("C:\\System\\Apps\\vcall\\times"),EFileRead) != KErrNone)
    {
        User::Panic(_L("Config file not open"),KErrNotFound);
    }
    text.Set(file);
    while(text.Read(buf) == KErrNone)
    {
        lex.Assign(buf);
        TInt val;
        lex.Val(val);//TODO: error handling
        iTimes.Append(val);
    }
    file.Close();
    //iTimes.SortSigned();//TODO: fix sort
    iTimer = CVTimer::NewL();
    iTimer->setTimes(iTimes);
}

void CSettings::CallConnected()
{
    iTimer->startTimer(0);
}
void CSettings::CallDisconnected()
{
    iTimer->stopTimer();
}

CSettings* CSettings::NewL()
{
    CSettings* self = CSettings::NewLC();
    _CPOP(self);
    return self;
}

CSettings* CSettings::NewLC()
{
    CSettings* self = new (ELeave) CSettings();
    _CPUSH(self);
    self->ConstructL();
    return self;
}
