// src/game/Spui/SPUIMessageBox.cpp -- migrated from slice(s) s00816d40 by tools/migrate/rewrite.py
// Object file: Spui/SPUIMessageBox.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUIMessageBox.h"
#include "cSPUILayout.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void Dealloc(void*);

// ---- items of slice s00816d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int  u32;
typedef unsigned char u8;
struct cSPUILayout_s0081_6d40 {
    char  pad_00[0x0c];
    void* FindWindowByID(u32 id, int arg);  // 0x008105b0 (cSPUILayout::FindWindowByID)
    void  Shutdown(int arg);  // 0x00811ad0 (cSPUILayout::Shutdown)
    void  Init(u32 a, int b, int c, const wchar_t* s);  // 0x00812160 (cSPUILayout::Init)
    ~cSPUILayout_s0081_6d40();
};
struct MsgBoxA {
    char        pad_00[0x0c];
    cSPUILayout_s0081_6d40 layout;   // +0x0c
    void* scalarDtor(u8 flags);
};
extern "C" void Dealloc(void*);
// ---- items of slice s00816d40 end

// @ 0x00817000
void* MsgBoxA::scalarDtor(u8 flags)
{
    *(void**)((char*)this + 0) = (void*)0x1418dd4;
    *(void**)((char*)this + 4) = (void*)0x1418dc4;
    layout.~cSPUILayout_s0081_6d40();
    *(void**)((char*)this + 4) = (void*)0x13ec458;
    *(void**)((char*)this + 0) = (void*)0x13eb938;
    if (flags & 1) Dealloc(this);
    return this;
}
