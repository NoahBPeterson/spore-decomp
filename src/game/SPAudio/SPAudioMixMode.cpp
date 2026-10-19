// src/game/SPAudio/SPAudioMixMode.cpp -- migrated from slice(s) s00a168c0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioMixMode.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/IPrimitive.h"
#include "EA/Audio/ResponseCurve.h"
#include <intrin.h>
#include <string.h>

// ---- items of slice s00a168c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
struct Server;                         // EA::Messaging::Server
Server*   GetServer();                 // 0x00883860
struct IPrimitive {
    virtual void  v00();
    virtual int   v04();                 // AddRef
    virtual void  v08();                 // Release
    virtual void* v0c(u32);
    virtual bool  v10();
    virtual void  v14();
    virtual void  v18();
    virtual void  v1c();
    virtual bool  v20(int);
    virtual void  v24(int);
    virtual void  v28(float value, int mod);   // SetModificationSource(value, mod)
    virtual void  v2c(int);
    virtual int   v30();
    virtual void  v34();
    virtual void  v38();
};
struct PrimBase {
    void* vtbl0;    // +0x00
    void* vtbl1;    // +0x04
    void* vtbl2;    // +0x08
    void* m0c;      // +0x0c
    bool  mbDirty;  // +0x10
    u8    pad11[3];
    void* m14;      // +0x14
    void* mpConfig; // +0x18
    void* m1c;      // +0x1c
    int   m20;      // +0x20

    bool  Shutdown();                                   // 00a16e70
    bool  GetDirty(int);                                // 00a16eb0
    void  ClearDirty(int);                              // 00a16ec0
    bool  HandleMessage(int id, void* arg);             // 00a16f00
    bool  Init();                                       // 00a16f60
};
// ---- items of slice s00a168c0 end

// @ 0x00a16e70
bool PrimBase::Shutdown()
{
    Server* s = GetServer();
    if (s != 0) {
        void* payload = this ? (char*)this + 4 : 0;
        ((void (__thiscall*)(void*, void*, u32, int))((*(void***)s)[0x2c / 4]))(
            s, payload, 0x2b0c259u, 0xffffd8f1);
    }
    return true;
}

// @ 0x00a16eb0
bool PrimBase::GetDirty(int)
{
    return mbDirty;
}

// @ 0x00a16ec0
void PrimBase::ClearDirty(int arg)
{
    if (m20 == arg)
        mbDirty = false;
}

// @ 0x00a16f00
bool PrimBase::HandleMessage(int id, void* arg)
{
    if (id == 0x2b0c259) {
        char* obj = (char*)this - 4;
        int other = *(int*)((char*)arg + 0x18);
        int mine = ((int (__thiscall*)(void*))((*(void***)obj)[0x18 / 4]))(obj);
        if (other == mine)
            ((IPrimitive*)obj)->v38();
    }
    return true;
}
