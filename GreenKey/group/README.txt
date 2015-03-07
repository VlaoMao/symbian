Concepts:
!Capturing keypresses!

The keyevents library allows you to be notified whenever
the user presses a key on an Symbian (tested on S60) device.
From the client side you need a window group to construct
the client and an RProperty to listen to notifications. You
have to allocate a category and key to use for the notifications.

The implementation is an animation dll, which has a server
side part (keyevents_server), based on CAnimDll and CWindowAnim
that gets loaded into the window server process, and a client
side based on RAnim that instantiates the server side object
passing it the key to notify through.

The animation dll is probably the most performant and robust
way to get notifications when keys are pressed somewhere else
than in your app. FEPs need code loaded to each process and
CaptureKey() really only works as long there is only one app
capturing the key in question, and it's easy to forward the
keys to the wrong windowgroup.

The file server_anim.h documents how this can be extended to
listen to specific keys or other events/notification styles.

Caveats:
  The code only directly compiles within the Jaiku source tree,
  you'll need to change some of the includes in source files
  and MMP files, and add the right defines for UIDs and dll names.
  Just remove any includes starting with 'context', try compiling
  and you'll see what breaks.

  The same goes for pkg files: you'll need to modify them to use
  the right UIDs and names as well as all the other pkg file
  things. The Jaiku build processes pkg files heavily before
  using them.

Author: mikie@iki.fi (Mike Raento)

