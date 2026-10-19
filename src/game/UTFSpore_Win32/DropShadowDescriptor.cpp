// src/game/UTFSpore_Win32/DropShadowDescriptor.cpp -- migrated from slice(s) s0096e3a0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/DropShadowDescriptor.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int  g_sQuality[];                  // 0x154f514
#include <math.h>
#pragma intrinsic(sqrt)

// ---- items of slice s0096e3a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int  g_sQuality[];                  // 0x154f514
struct ShadowDesc {
    unsigned f00;   // +0x00 mode/quality
    unsigned f04;   // +0x04 detail level
    unsigned f08;
    float    f0c;   // +0x0c
    float    f10;   // +0x10
    float    f14;   // +0x14 width
    float    f18;   // +0x18 height
    unsigned f1c;
    unsigned f20;
    unsigned f24;
    void SetMode(int m);   // 0x830150
};
// ---- items of slice s0096e3a0 end

// @ 0x0096e3a0
void __cdecl CopyWithQualityAdjustment(ShadowDesc* dst, ShadowDesc* src, int quality)
{
    for (int i = 0; i < 10; i++)
        ((unsigned*)dst)[i] = ((unsigned*)src)[i];
    int q = g_sQuality[quality];
    if (q >= 2) {
        if (q != 2)
            return;
        goto two;
    }
    if (q == 1) {
        dst->f04 += 1;
        if (dst->f04 > 9) dst->f04 = 9;
        dst->SetMode((int)dst->f04);
        dst->f00 = 0;
        dst->f14 = 0.0f;
        dst->f18 = 0.0f;
        if (0.0f < src->f14)
            dst->f0c = 1.0f;
        if (src->f18 <= 0.0f)
            return;
        dst->f10 = 1.0f;
        return;
    }
    if (q == (int)0xcfffffff)
        goto two;
    if (q != 0)
        return;
    dst->f00 = 0;
    dst->f14 = 0.0f;
    dst->f0c = 0.0f;
    dst->f10 = 0.0f;
    dst->f18 = 0.0f;
    return;
two:
    dst->f04 += 2;
    if (dst->f04 > 9) dst->f04 = 9;
    dst->SetMode((int)dst->f04);
    dst->f00 = 0;
    dst->f14 = (float)(int)((double)(src->f14 * 0.5f));   // floor
    dst->f18 = (float)(int)((double)(src->f18 * 0.5f));
    if (0.0f < src->f14 && dst->f14 <= 1.0f && dst->f14 != 1.0f)
        dst->f14 = 1.0f;
    if (0.0f < src->f18 && dst->f18 <= 1.0f && dst->f18 != 1.0f)
        dst->f18 = 1.0f;
}

// @ 0x0096e500
void __cdecl cDropShadowDescriptor_SetQuality(int quality, int index)
{
    if (quality <= 0) {
        g_sQuality[index] = 0;
        return;
    }
    if (quality >= 3) {
        g_sQuality[index] = 3;
        return;
    }
    g_sQuality[index] = quality;
}
