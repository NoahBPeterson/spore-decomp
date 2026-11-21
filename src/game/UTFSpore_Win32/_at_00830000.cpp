// src/game/UTFSpore_Win32/_at_00830000.cpp -- migrated from slice(s) s0083f140 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_00830000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Stopwatch.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl Messaging_GetServer();

// ---- items of slice s0083f140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl Messaging_GetServer();
// ---- items of slice s0083f140 end

struct IListener_83f580 {
    virtual void v00();
    virtual int HandleMessage(unsigned id, void* msg);   // +0x04
};
struct Base0_83f580 { virtual void v00(); };
struct FileListener_83f580 : Base0_83f580, IListener_83f580 {};
struct IServer_83f580 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual int Post(unsigned id, void* a, void* b, IListener_83f580* l);   // +0x18
};
// @ 0x0083f580
void __cdecl FileMessageCallback(void*, void*, void*, void*, void* arg)
{
    FileListener_83f580* f = (FileListener_83f580*)arg;
    IServer_83f580* server = (IServer_83f580*)Messaging_GetServer();
    if (server)
        server->Post(0x6f41f272, 0, 0, f);
    else if (f)
        ((IListener_83f580*)f)->HandleMessage(0x6f41f272, 0);
}
