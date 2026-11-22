// src/game/UTFSpore_Win32/RotateEffect.cpp -- migrated from slice(s) s00980760 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/RotateEffect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinControls/IScrollbarDrawable.h"
#include "EA/UTFWinControls/IWinScrollbar.h"
#include <math.h>
#include <xmmintrin.h>

// ---- items of slice s00980760 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(size_t, void* p) { return p; }
void* GetDefaultAllocator();                                                       // 009512C0
void* AllocAligned(uint32_t size, uint32_t align, const char* name, void* alloc);  // 009512D0 (cdecl)
void __fastcall FadeEffect_ctor(void* p);                              // 00963db0
struct XCM {
    void SetX(float v);                                                // 0095eb00
    void SetY(float v);                                                // 0095ec30
    void SetZ(float v);                                                // 0095ed60
    void SetRotationAtLeast2(float* face, float v);                    // 0095f5c0
};
namespace EA {
namespace UTFWinControls {
extern void* vt_1444368[];
}
}
namespace EA {
namespace UTFWinControls {
extern void* vt_1444350[];
}
}
namespace EA {
namespace UTFWinControls {
extern void* vt_1444314[];
}
}
namespace EA {
namespace UTFWinControls {
extern void* vt_1444458[];
}
}
namespace EA {
namespace UTFWinControls {
extern void* vt_1444434[];
}
}
namespace EA {
namespace UTFWinControls {
class RotateEffect { public:
    void* vt0;                                                         // +0x00
    void* vt4;                                                         // +0x04
    int   f08;                                                         // +0x08
    void* vtc;                                                         // +0x0c
    int   f10;                                                         // +0x10
    int   f14;                                                         // +0x14
    int   f18;                                                         // +0x18
    int   f1c;                                                         // +0x1c
    char  pad20[0x60 - 0x20];
    void* vt60;                                                        // +0x60
    float fx;                                                          // +0x64
    float fy;                                                          // +0x68
    float fz;                                                          // +0x6c
    float scale;                                                       // +0x70
    RotateEffect();                                                    // 00980e30
    ~RotateEffect();                                                   // 00980c00
    void SetRotation(void* unused, XCM* cm, float deg);               // 00980cf0
};
}
}
namespace EA {
namespace UTFWinControls {
class BasicFactory_RotateEffect { public:
    RotateEffect* CreateInstance(int unused, void* alloc);             // 00980ea0
};
}
}
// ---- items of slice s00980760 end

// @ 0x00980cf0
void EA::UTFWinControls::RotateEffect::SetRotation(void* unused, XCM* cm, float deg)
{
    (void)unused;
    int axis = 0;
    int count = 0;
    if (fabsf(fx) > 1.1920929e-07f) count = 1;
    if (fabsf(fy) > 1.1920929e-07f) { axis = 1; count++; }
    if (fabsf(fz) > 1.1920929e-07f) { axis = 2; count++; }
    if (count > 1) axis = 3;
    if (count <= 0) return;
    switch (axis) {
    case 0: cm->SetX(scale * deg * 0.017453292f); return;
    case 1: cm->SetY(scale * deg * 0.017453292f); return;
    case 2: cm->SetZ(scale * deg * 0.017453292f); return;
    case 3: cm->SetRotationAtLeast2(&fx, scale * deg * 0.017453292f); return;
    }
}

// @ 0x00980e30
EA::UTFWinControls::RotateEffect::RotateEffect()
{
    FadeEffect_ctor(this);
    *(void**)((char*)this + 0x60) = EA::UTFWinControls::vt_1444434;
    *(void**)this = EA::UTFWinControls::vt_1444368;
    *(void**)((char*)this + 4) = EA::UTFWinControls::vt_1444350;
    *(void**)((char*)this + 0xc) = EA::UTFWinControls::vt_1444314;
    *(void**)((char*)this + 0x60) = EA::UTFWinControls::vt_1444458;
    fx = 0.0f;
    fz = 0.0f;
    fy = 1.0f;
    scale = 45.0f;
}

// @ 0x00980ea0
EA::UTFWinControls::RotateEffect* EA::UTFWinControls::BasicFactory_RotateEffect::CreateInstance(int unused, void* alloc)
{
    if (alloc == 0) alloc = GetDefaultAllocator();
    void* mem = AllocAligned(0x78, 8, "UTFWin/EA::UTFWinControls::RotateEffect", alloc);
    if (mem != 0) {
        return new (mem) EA::UTFWinControls::RotateEffect();
    }
    return 0;
}
