#include "client.h"
#include "client_server.rh"

// The RKeyEventsAnim class is the client side class for CKeyEventsAnim
// animation class. No commands are needed (commands would normally be used in
// animation dlls to actually trigger animations/other functionality), the
// construction of this class will create the CKeyEventsAnim object
// server-side, which will notify of keypresses via the RProperty key given in
// the args as a TPckg<TKeyEventArgs>.

class RKeyEventsAnim : public RAnim {
 public:
  RKeyEventsAnim(RAnimDll* dll);
  TInt Construct(const RWindowBase& device, const TDesC8& args);

  // Inherited destructor is fine.
};

// *****************************************************************************
// RKeyEventsAnim

// The parameter dll will not be NULL, only called from CKeyEventsClient
RKeyEventsAnim::RKeyEventsAnim(RAnimDll *dll) : RAnim(*dll) {
}

TInt RKeyEventsAnim::Construct(const RWindowBase& device, const TDesC8& args) {
  // server side Anim doesn't care about parameters
  return RAnim::Construct(device, 0, args);
}

// *****************************************************************************
// CKeyEventsClient

EXPORT_C CKeyEventsClient* CKeyEventsClient::NewL(const TUid& category_uid,
    TUint key_id, RWsSession* ws_io, RWindowGroup* window_group_io) {
  if (!ws_io || !window_group_io) {
    User::Leave(KErrArgument);
  }
  CKeyEventsClient* ret = new (ELeave) CKeyEventsClient(ws_io);
  CleanupStack::PushL(ret);
  ret->ConstructL(category_uid, key_id, window_group_io);
  CleanupStack::Pop(ret);
  return ret;
}

EXPORT_C void CKeyEventsClient::OpenNotificationPropertyL(
    RProperty* property_out) {
  property_out->Attach(TUid::Uid(property_definition_.category_uid),
      property_definition_.key_id, EOwnerThread);
}

EXPORT_C CKeyEventsClient::~CKeyEventsClient() {
  // Destroy() does Close() and delete.
  if (keyevents_) keyevents_->Destroy();
  keyevents_dll_.Close();
  window_.Close();
}

CKeyEventsClient::CKeyEventsClient(RWsSession* ws_io)
    : keyevents_dll_(*ws_io),
      window_(*ws_io),
      property_definition_pckg_(property_definition_) {
  // The parameter ws_io is checked for NULL in NewL.
}

// We use ProtServ to protect the property, as that is basically
// what the animation dll is required to have. We can't use
// SwEvent (at least not as a write policy) as the
// window server doesn't have it. Realistically, we could
// just have it world accessible.
static _LIT_SECURITY_POLICY_C1(kProtServPolicy, ECapabilityProtServ);

void CKeyEventsClient::ConstructL(const TUid& category_uid,
    TUint key_id, RWindowGroup* window_group_io) {
  // The parameter window_group_io is checked for NULL in NewL.

  property_definition_.category_uid = category_uid.iUid;
  property_definition_.key_id = key_id;

  TInt err = RProperty::Define(category_uid, key_id, RProperty::EInt,
                               kProtServPolicy, kProtServPolicy);
  if (err != KErrNone && err != KErrAlreadyExists) User::Leave(err);

  err = keyevents_dll_.Load(TPtrC(
      reinterpret_cast<const TUint16*>(
          KEYEVENTS_SERVER_DLL_NAME_STRING)));
  if (err != KErrNone)
    User::Leave(err);
  keyevents_ = new (ELeave) RKeyEventsAnim(&keyevents_dll_);
  err = window_.Construct(*window_group_io,
    reinterpret_cast<TUint32>(&window_));
  if (err != KErrNone)
    User::Leave(err);
  // By not Activate()ing the window, it stays invisible and gets no events
  err = keyevents_->Construct(window_, property_definition_pckg_);
  if (err != KErrNone)
    User::Leave(err);
}
