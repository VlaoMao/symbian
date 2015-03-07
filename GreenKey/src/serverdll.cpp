
#include "serverdll.h"

#include "serveranim.h"

// *****************************************************************************
// Global functions

// The only exported function in the server DLL is the CreateCAnimDllL function
// this is called for us by the windows server framework to create an instance
// of the animation server dll

EXPORT_C CAnimDll* CreateCAnimDllL() {
  return new (ELeave) CKeyEventsServerDll;
}

// *****************************************************************************
// CKeyEventsServerDll

CKeyEventsServerDll::CKeyEventsServerDll() : CAnimDll() {
}

// -----------------------------------------------------------------------------
// CAnimDll

CAnim* CKeyEventsServerDll::CreateInstanceL(TInt) {
  return new (ELeave) CKeyEventsAnim;
}
