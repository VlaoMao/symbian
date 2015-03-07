#include "serveranim.h"

// *****************************************************************************
// CKeyEventsAnim

// -----------------------------------------------------------------------------
// CAnim

void CKeyEventsAnim::ConstructL(TAny* args, TBool) : iIsHandleEnabled(EFalse)
	{
  TKeyServerArgs* property_definition = reinterpret_cast<TKeyServerArgs*>(args);
  User::LeaveIfError(keyevent_notification_property_.Attach(
      TUid::Uid(property_definition->category_uid),
      property_definition->key_id, EOwnerThread));
  iFunctions->GetRawEvents(ETrue);
}

void CKeyEventsAnim::Redraw() {
}

void CKeyEventsAnim::FocusChanged(TBool) {
}


void CKeyEventsAnim::Animate(TDateTime*) {
}

TInt CKeyEventsAnim::CommandReplyL(TInt, TAny*) {
  return KErrNone;
}

void CKeyEventsAnim::Command(TInt, TAny*) {
}

CKeyEventsAnim::CKeyEventsAnim() {
}

CKeyEventsAnim::~CKeyEventsAnim() {
  keyevent_notification_property_.Close();
}

// -----------------------------------------------------------------------------
// MEventHandler via CAnim

TBool CKeyEventsAnim::OfferRawEvent(const TRawEvent &raw_event) {
  if (raw_event.Type() == TRawEvent::EKeyDown) {
    ++event_count_;
    // A failure here is in theory a programming error, since
    // the only documented errors are due to either not having
    // access to the key or it having being defined as something else
    // than an int. Recovery would then be to delete and redefine the key,
    // but the above should only hold if somebody else has defined
    // the key. Don't really want to panic the client either, so we
    // just ignore any errors.
    // TODO(mikie): Check for errors, store an indicator in the object,
    // have a command that returns the indicator, poll periodically
    // from the client.
    keyevent_notification_property_.Set(event_count_);
    if(iIsHandleEnabled)
    	return ETrue;
  }
  return EFalse;
}
