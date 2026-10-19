// src/game/UTFSpore_Win32/FadeEffect.cpp -- migrated from slice(s) s0096e3a0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/FadeEffect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* FUN_009512c0(void);                        // 0x9512c0
extern "C" void* FUN_009512d0(int size, int align, const char* name, void* alloc); // 0x9512d0
#include <math.h>
#pragma intrinsic(sqrt)

// ---- items of slice s0096e3a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_009512c0(void);                        // 0x9512c0
extern "C" void* FUN_009512d0(int size, int align, const char* name, void* alloc); // 0x9512d0
struct ExtBase {
    void ctor963db0();      // 0x963db0
    void dtor980420();      // 0x980420 Navigator::~Navigator
    void ctor980430();      // 0x980430 ExplicitNavigator ctor
};
// ---- items of slice s0096e3a0 end

// @ 0x0096f080
void __cdecl BiStateEffect_func84h(int* self, float f)
{
    f = (1.0f - f) * 255.0f;
    int a = (int)f;
    a <<= 24;
    a += 0xffffff;
    (*(void(__thiscall**)(int*, int))((char*)*self + 0x5c))(self, a);
}

// @ 0x0096f120
void* __stdcall BasicFactory_FadeEffect_CreateInstance(int unused, int alloc)
{
    (void)unused;
    if (alloc == 0)
        alloc = (int)FUN_009512c0();
    void* p = FUN_009512d0(0x60, 8, "UTFWin/EA::UTFWinControls::FadeEffect", (void*)alloc);
    if (p) {
        ((ExtBase*)p)->ctor963db0();
        *(void**)((char*)p + 0x00) = (void*)0x14422f8;
        *(void**)((char*)p + 0x04) = (void*)0x14422e0;
        *(void**)((char*)p + 0x0c) = (void*)0x14422a4;
        return p;
    }
    return 0;
}
