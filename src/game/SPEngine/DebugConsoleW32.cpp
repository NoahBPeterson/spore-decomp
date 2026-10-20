// src/game/SPEngine/DebugConsoleW32.cpp -- migrated from slice(s) s006bb1c0 by tools/migrate/rewrite.py
// Object file: SPEngine/DebugConsoleW32.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long*);
void __cdecl EASTL_dealloc(void*) throw();

// ---- items of slice s006bb1c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct BaseA2 { virtual ~BaseA2() {} };
struct WStr16 {            // eastl::basic_string<wchar_t>: begin, end, capacity + allocator word
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    int      mAlloc;
    void AllocateSelf(int n);                                   // 0x00429760
    ~WStr16()
    {
        if ((int)(((char*)mpCapacity - (char*)mpBegin) & 0xfffffffe) > 2 && mpBegin) EASTL_dealloc(mpBegin);
    }
};
struct DebugMessage : BaseA2 {
    WStr16 mText;
    long   mRef;
    DebugMessage() : mRef(0) {}
    DebugMessage(const wchar_t* src, int count);
    virtual ~DebugMessage();   // ~DebugMessage 0x6bb690; its ??_G 0x6bb760 is compiler generated from it
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
// @ 0x006bb760
DebugMessage::~DebugMessage()
{}
