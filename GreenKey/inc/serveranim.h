// Copyright (c) 2007-2009 Google Inc.
// Copyright (c) 2006-2007 Jaiku Ltd.
// Copyright (c) 2002-2006 Mika Raento and Renaud Petit
//
// This software is licensed at your choice under either 1 or 2 below.
//
// 1. MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// 2. Gnu General Public license 2.0
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
//
// This file is part of the JaikuEngine mobile client.

#ifndef JAIKU_KEYEVENTS_SERVERANIM_H__
#define JAIKU_KEYEVENTS_SERVERANIM_H__

// System includes.
#include <e32property.h>
#include <w32adll.h>

// Local includes.
#include "client_server_constants.h"

// The class CKeyEventsAnim is the key event listener.
// It gets all raw input events from the window server and
// updates an RProperty whenever it sees a keydown event.
// It is instantiated from CKeyEventsServerDll::CreateInstanceL
// when client side code calls RAnim::Construct.
//
// Although the class is an animation class, it doesn't ever draw
// anything or take any commands (as would normally be the case
// for an animation dll). It does take initialization
// parameters in the form of a TKeyServerArgs struct pointer
// passed to RAnim::Construct, which specifies the property
// category and name to update. The category and key need to
// be passed to this class so that they can be defined in
// a process with a suitable SecureUID (you can only define
// new keys with category==process's SecureUID on v9, this
// dll gets loaded into the window server, and it owns the
// namespace, we can't guarantee we wouldn't clash).
//
// To share efficiently over multiple clients the best way is
// to build a separate client-server layer on top of the keyevents
// client dll, since that would allow for sharing a single instance
// over multiple client processes.
//
// Should you want to extent the functionality, you can either
// pass more args to Construct by extending TKeyServerArgs, or
// by starting to define commands. E.g., getting it to listen
// to specific keypresses could be done as new flags in Construct+
// additional RProperty keys to update.
//
// We use an RProperty instead of an asynchronous command so
// that potentially several interested clients can get
// notifications without having to have more than one instance
// listening to key events, as it inserts code into any input
// event codepath. This is slightly broken though, as the
// different clients will need to collaborate on getting an
// instance running and the category+key to use.
//
// TODO(mikie): if we want to listen to several different events
// in the future, using separate async commands for those would
// probably make more sense than several properties.
//
class CKeyEventsAnim : public CWindowAnim {
 public:
  virtual ~CKeyEventsAnim();

  // CWindowAnim
  void ConstructL(TAny* aArgs, TBool aHasFocus);
  TInt CommandReplyL(TInt aCommand, TAny* aArgs);
  void Command(TInt aCommand, TAny* aArgs);
  void Redraw();
  void Animate(TDateTime* aDateTime);
  void FocusChanged(TBool aState);
  TBool OfferRawEvent(const TRawEvent &aRawEvent);

 private:
  CKeyEventsAnim();
  friend class CKeyEventsServerDll;
  TBool iIsHandleEnabled;

  RProperty keyevent_notification_property_;
  TInt event_count_;
};

#endif  //  JAIKU_KEYEVENTS_SERVERANIM_H__
