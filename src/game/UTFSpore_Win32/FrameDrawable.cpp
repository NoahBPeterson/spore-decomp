// src/game/UTFSpore_Win32/FrameDrawable.cpp -- migrated from slice(s) s0096f3f0, s0096e3a0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/FrameDrawable.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include "EA/UTFWin/RenderContext.h"
#include "EA/UTFWinControls/WinGrid.h"
#include <intrin.h>
#pragma intrinsic(sqrt)

// ---- items of slice s0096e3a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Ctx96 {
    char pad[0x50];
    void a(float* p, float f);       // 0x96f1b0
    void b(float* p);                // 0x96f1f0
    int  q(int iid);                 // 0x96f240
    int  FUN_00951240(int iid);      // 0x951240 base AsInterface (thiscall)
    int  s(unsigned flags);          // 0x96f280
};
// ---- items of slice s0096e3a0 end

// ---- items of slice s0096f3f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace UTFWin {
struct RenderContext_s0096_f3f0 {
    RenderContext_s0096_f3f0* Begin2D(int mode);   // 0x0095bc10
    void End2D();                       // 0x0095bb20
};  // namespace UTFWin
}
}
namespace EA {
namespace UTFWinControls {
void  __fastcall FUN_0096f280(void* this_, int arg);                           // 0x0096f280
}
}
namespace EA {
namespace UTFWinControls {
class FrameDrawable { public:
    void* vtbl;            // +0x00
    void* vtblSer;         // +0x04
    int   mRefCount;       // +0x08
    int   field0c;         // +0x0c
    int   field10;         // +0x10
    int   states[14];      // +0x14 .. +0x48
    float mBorderWidth[4]; // +0x4c .. +0x58
    int   mOutlineColor;   // +0x5c

    FrameDrawable();                                                        // 0x0096fe30
    int CreateRenderables(UTFWin::RenderContext_s0096_f3f0* ctx, void* pRect);         // 0x0096f3f0
};
}
}
// ---- items of slice s0096f3f0 end

// @ 0x0096f1b0
void Ctx96::a(float* p, float f)
{
    (*(void(__thiscall**)(void*, float, float, float, float, float))((char*)*(void**)this + 0x1c))(
        this, p[0], p[1], p[2], p[3], f);
}

// @ 0x0096f240
int Ctx96::q(int iid)
{
    switch (iid) {
    case 0x30d54ac:
        return (int)this;
    case (int)0xeec58382:
        return this ? (int)this + 4 : 0;
    }
    return FUN_00951240(iid);
}

// @ 0x0096f280
int Ctx96::s(unsigned flags)
{
    char* self = (char*)this;
    switch (flags & 7) {
    case 0:
        if ((flags & 8) != 0 && *(int*)(self + 0x2c) != 0)
            return (int)(self + 0x2c);
        break;
    case 1:
        if ((flags & 8) != 0 && *(int*)(self + 0x34) != 0)
            return (int)(self + 0x34);
        if (*(int*)(self + 0x14) != 0)
            return (int)(self + 0x14);
        break;
    case 2:
        if ((flags & 8) != 0) {
            if (*(int*)(self + 0x3c) != 0)
                return (int)(self + 0x3c);
            if (*(int*)(self + 0x2c) != 0)
                return (int)(self + 0x2c);
        }
        if (*(int*)(self + 0x1c) != 0)
            return (int)(self + 0x1c);
        break;
    case 3:
        if ((flags & 8) != 0) {
            if (*(int*)(self + 0x44) != 0)
                return (int)(self + 0x44);
            if (*(int*)(self + 0x2c) != 0)
                return (int)(self + 0x2c);
        }
        if (*(int*)(self + 0x24) != 0)
            return (int)(self + 0x24);
        break;
    }
    return (int)(self + 0x0c);
}

// @ 0x0096f3f0
namespace EA { namespace UTFWinControls {
int FrameDrawable::CreateRenderables(UTFWin::RenderContext_s0096_f3f0* ctx, void* pRect)
{
    UTFWin::RenderContext_s0096_f3f0* pRC = ctx;
    void* p = pRC->Begin2D(0);
    (*(void(__fastcall**)(void*, int))((char*)*(void**)p + 4))(p, -1);
    FUN_0096f280(this, *(int*)pRect);
    return 0;
}
}}  // namespace EA::UTFWinControls

// @ 0x0096fe30
namespace EA { namespace UTFWinControls {
FrameDrawable::FrameDrawable()
{
    const float one = *(const float*)0x01485720;
    *(void* volatile*)((char*)this + 4) = (void*)0x013fa72c;
    *(void**)((char*)this + 0) = (void*)0x014424d4;
    *(void* volatile*)((char*)this + 4) = (void*)0x014424bc;
    _ReadWriteBarrier();
    int zero = 0;
    *(int*)((char*)this + 8) = zero;
    *(float*)((char*)this + 0x4c) = one;
    *(float*)((char*)this + 0x50) = one;
    *(float*)((char*)this + 0x54) = one;
    *(float*)((char*)this + 0x58) = one;
    *(int*)((char*)this + 0x5c) = (int)0xff000000;
    *(int*)((char*)this + 0x18) = zero;
    *(int*)((char*)this + 0x14) = zero;
    *(int*)((char*)this + 0x20) = zero;
    *(int*)((char*)this + 0x1c) = zero;
    *(int*)((char*)this + 0x28) = zero;
    *(int*)((char*)this + 0x24) = zero;
    *(int*)((char*)this + 0x30) = zero;
    *(int*)((char*)this + 0x2c) = zero;
    *(int*)((char*)this + 0x38) = zero;
    *(int*)((char*)this + 0x34) = zero;
    *(int*)((char*)this + 0x40) = zero;
    *(int*)((char*)this + 0x3c) = zero;
    *(int*)((char*)this + 0x48) = zero;
    *(int*)((char*)this + 0x44) = zero;
    *(int*)((char*)this + 0x10) = -1;
    *(int*)((char*)this + 0x0c) = 2;
}
}}  // namespace EA::UTFWinControls
