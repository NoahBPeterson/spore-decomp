// src/game/SPEngine/DebugConsoleW32.cpp -- migrated from slice(s) s006bb1c0 by tools/migrate/rewrite.py
// Object file: SPEngine/DebugConsoleW32.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long*);

// ---- items of slice s006bb1c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long*);
void __cdecl EASTL_dealloc(void*);
struct AppMsgBase { void* vtbl; virtual ~AppMsgBase() { } };
struct DebugMessage : AppMsgBase {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    virtual ~DebugMessage();
};
// ---- items of slice s006bb1c0 end

// @ 0x006bb670
int __fastcall FUN_006bb670(void* self)
{
    long* pc = (long*)((char*)self + 0x14);
    long n = InterlockedDecrement(pc);
    if (n == 0 && self) ((void(__thiscall*)(void*, int))(*(void***)self)[0])(self, 1);
    return n;
}

// @ 0x006bb690
DebugMessage::~DebugMessage()
{
    if ((((char*)mpCapacity - (char*)mpBegin) & 0xfffffffe) > 2 && mpBegin) EASTL_dealloc(mpBegin);
}
