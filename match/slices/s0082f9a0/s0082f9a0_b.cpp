// Slice s0082f9a0 (part b): out-of-line caller so cl must treat SetMode1/SetMode2 as
// opaque (keeps the descriptor pointer in a callee-saved register, like the original).
#include "types.h"

struct ShadowDesc {
    uint32_t mode1;   // +0x00
    uint32_t mode2;   // +0x04
    uint32_t f8;      // +0x08
    uint32_t fc;      // +0x0c
    uint32_t f10;     // +0x10
    float    s14;     // +0x14
    float    s18;     // +0x18
    float    s1c;     // +0x1c
    float    s20;     // +0x20
    uint32_t f24;     // +0x24
    void SetMode1(int mode);   // defined in s0082f9a0.cpp
    void SetMode2(int mode);   // defined in s0082f9a0.cpp
};

struct ImageInfoFull {
    char        pad0[0x48];
    ShadowDesc  mShadowStroke;   // +0x48
    ShadowDesc  mShadowHalo;     // +0x70
};

// @ 0x008306a0
void FUN_008306a0(ImageInfoFull *p)
{
    p->mShadowHalo.SetMode1(p->mShadowHalo.mode1);
    p->mShadowHalo.SetMode2(p->mShadowHalo.mode2);
    p->mShadowStroke.SetMode1(p->mShadowStroke.mode1);
    p->mShadowStroke.SetMode2(p->mShadowStroke.mode2);
}
