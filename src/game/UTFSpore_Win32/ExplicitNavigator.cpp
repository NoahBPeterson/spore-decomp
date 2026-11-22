// src/game/UTFSpore_Win32/ExplicitNavigator.cpp -- migrated from slice(s) s0096e3a0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ExplicitNavigator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" char g_13eb938[];
extern "C" char g_13fa72c[];
extern "C" char g_1442170[];
extern "C" char g_1442188[];
extern "C" char g_14421ac[];
extern "C" char g_14421c8[];
extern "C" void* FUN_009512c0(void);                        // 0x9512c0
extern "C" void* FUN_009512d0(int size, int align, const char* name, void* alloc); // 0x9512d0
extern "C" void FUN_00951330(void* p);   // 0x951330 operator delete (cdecl)
#include <math.h>
#pragma intrinsic(sqrt)

// ---- items of slice s0096e3a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_13eb938[];
extern "C" char g_13fa72c[];
extern "C" char g_1442170[];
extern "C" char g_1442188[];
extern "C" char g_14421ac[];
extern "C" char g_14421c8[];
extern "C" void* FUN_009512c0(void);                        // 0x9512c0
extern "C" void* FUN_009512d0(int size, int align, const char* name, void* alloc); // 0x9512d0
struct ExtBase {
    void ctor963db0();      // 0x963db0
    void dtor980420();      // 0x980420 Navigator::~Navigator
    void ctor980430();      // 0x980430 ExplicitNavigator ctor
};
extern "C" void FUN_00951330(void* p);   // 0x951330 operator delete (cdecl)
struct ExplicitNavigator {
    char pad[0x1c];
    void* f1c;
    void* ScalarDtor(unsigned flags);   // 0x96eee0
};
// ---- items of slice s0096e3a0 end

// @ 0x0096ed70
bool __cdecl FUN_0096ed70(void* p1, char* p2, char* p3)
{
    unsigned* src = *(unsigned**)(p2 + 4);
    unsigned* dst = (unsigned*)(*(int*)((char*)p1 + 4) + *(int*)(p3 + 0x10));
    for (unsigned n = 0; n < *(unsigned*)(p3 + 0x14); n++) {
        unsigned val = 0;
        void* o = (void*)*src;
        if (o) val = (*(unsigned(__thiscall**)(void*, int))((char*)*(void**)o + 0xc))(o, 0xeeee8218);
        *dst = val;
        dst++;
        src++;
    }
    return true;
}

// @ 0x0096eee0
void* ExplicitNavigator::ScalarDtor(unsigned flags)
{
    *(void**)((char*)this + 0x18) = (void*)g_13eb938;
    ((ExtBase*)this)->dtor980420();
    if (flags & 1)
        FUN_00951330(this);
    return this;
}

// @ 0x0096ef10
void* __stdcall BasicFactory_ExplicitNavigator_CreateInstance(int unused, int alloc)
{
    (void)unused;
    if (alloc == 0)
        alloc = (int)FUN_009512c0();
    void* p = FUN_009512d0(0x20, 4, "UTFWin/EA::UTFWinControls::ExplicitNavigator", (void*)alloc);
    if (p) {
        ((ExtBase*)p)->ctor980430();
        *(void* volatile*)((char*)p + 0x18) = (void*)g_13fa72c;
        *(void**)((char*)p + 0x00) = (void*)g_14421c8;
        *(void**)((char*)p + 0x04) = (void*)g_14421ac;
        *(void**)((char*)p + 0x0c) = (void*)g_1442188;
        *(void**)((char*)p + 0x18) = (void*)g_1442170;
        *(void**)((char*)p + 0x1c) = 0;
        return p;
    }
    return 0;
}
