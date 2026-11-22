// src/game/UTFSpore_Win32/DropShadowDescriptor.cpp -- migrated from slice(s) s0096e3a0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/DropShadowDescriptor.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int  g_sQuality[];                  // 0x154f514
extern "C" void* g_vec1c0[];                   // 0x166b1c0 (eastl vector<bool>)
extern "C" void* g_vec1d4[];                   // 0x166b1d4 (eastl vector<GlyphLayoutInfo>)
extern "C" void  FUN_011e0744(void*, void*, unsigned);          // vector<bool>::DoInsertValue
#include <math.h>
#pragma intrinsic(sqrt)

// ---- items of slice s0096e3a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int  g_sQuality[];                  // 0x154f514
extern "C" void* g_vec1c0[];                   // 0x166b1c0 (eastl vector<bool>)
extern "C" void* g_vec1d4[];                   // 0x166b1d4 (eastl vector<GlyphLayoutInfo>)
extern "C" void  FUN_011e0744(void*, void*, unsigned);          // vector<bool>::DoInsertValue
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
struct BoolVec {
    void* v[3];
    void FUN_006eea80(unsigned n);   // 0x6eea80 vector resize (thiscall)
};
struct GlyphLayoutInfo { unsigned char b[0x20]; };
struct GlyphVec {
    unsigned v[3];
    void insert(GlyphLayoutInfo* pos, unsigned n, GlyphLayoutInfo* val);   // 0x96e540
    void resize(unsigned n);                                                // 0x96e6d0
    void* FUN_00899420(void* first, void* last);                            // 0x899420 vector::erase (thiscall)
    unsigned size() const { return (unsigned)(((int)v[1] - (int)v[0]) >> 5); }
};
struct DropShadowText {
    void draw(int* sink, void* a, void* glyphs, unsigned count,
              unsigned color, short flag, unsigned char mode);   // 0x96e740
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
    dst->f14 = (float)floor(src->f14 * 0.5f);   // retail calls the CRT floor
    dst->f18 = (float)floor(src->f18 * 0.5f);
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

// @ 0x0096e740
void DropShadowText::draw(int* sink, void* a, void* glyphs, unsigned count, unsigned color, short flag, unsigned char mode)
{
    ((BoolVec*)g_vec1c0)->FUN_006eea80(count);
    ((GlyphVec*)g_vec1d4)->resize(count);
    FUN_011e0744(g_vec1c0[0], a, count * 2);
    {
        struct G32 { unsigned d[8]; };
        G32* dst = (G32*)g_vec1d4[0];
        G32* sp = (G32*)glyphs;
        G32* send = sp + count;
        for (; sp != send; ++sp, ++dst)
            *dst = *sp;
    }
    ShadowDesc local;
    local.f00 = 0; local.f04 = 2; local.f08 = 3;
    local.f0c = 0.0f; local.f10 = 0.0f; local.f14 = 0.0f; local.f18 = 0.0f;
    local.f24 = 0;
    local.SetMode(2);
    CopyWithQualityAdjustment(&local, (ShadowDesc*)this, 0);
    float amp   = *(float*)&local.f20;
    float bias  = *(float*)&local.f1c;
    float rad1  = (float)sqrt((double)(local.f14 * local.f14 + local.f18 * local.f18)) + 1.0f;
    float cu    = (-local.f14 + local.f14) * 0.5f;     // v-range centre
    float cv    = (-local.f18 + local.f18) * 0.5f;     // u-range centre
    float du    = local.f18 - cv, dv = local.f14 - cu;
    float rad2  = dv * dv + du * du + 1.0f;
    unsigned baseColor = local.f24 & 0xffffff;
    float lastP = 0.0f, lastQ = 0.0f;
    for (float u = -local.f14; u <= local.f14; u += 1.0f) {
        float p = u + local.f0c;
        for (float v = -local.f18; v <= local.f18; v += 1.0f) {
            float q = v + local.f10;
            if (p != 0.0f || q != 0.0f) {
                float dp = p - lastP;
                float dq = q - lastQ;
                lastP = p;
                lastQ = q;
                for (unsigned j = 0; j < count; j++) {
                    unsigned char* g = (unsigned char*)g_vec1d4[0] + j * 0x20;
                    *(float*)(g + 4) += dp;
                    *(float*)(g + 8) += dq;
                    *(float*)(g + 0x10) += dp;
                    *(float*)(g + 0x14) += dq;
                    *(float*)(g + 0x18) += dp;
                    *(float*)(g + 0x1c) += dq;
                }
                float ev = v - cv, eu = u - cu;
                float t = (amp / rad1) * (1.0f - (eu * eu + ev * ev) / rad2) + bias;
                if (t < 0.0f) t = 0.0f;
                else if (t > 1.0f) t = 1.0f;
                // The original rounds with an x87 fistp (current mode: round to nearest even), not a
                // truncating cast. Adding 1.5*2^23 rounds the same way for |x| < 2^22 (here 0..255).
                union { float f; int i; } r;
                r.f = t * 255.0f + 12582912.0f;
                int alpha = r.i - 0x4b400000;
                (*(void(__thiscall**)(int*, int))((char*)*(void**)sink + 4))(sink, (alpha << 24) + baseColor);
                (*(void(__thiscall**)(int*, void*, void*, unsigned))((char*)*(void**)sink + 0x30))(sink, g_vec1c0[0], g_vec1d4[0], count);
            }
        }
    }
    (*(void(__thiscall**)(int*, unsigned))((char*)*(void**)sink + 4))(sink, color);
    if (mode != 0) {
        unsigned c = (flag == -1) ? 0xff00ff00 : 0xffff0000;
        (*(void(__thiscall**)(int*, unsigned))((char*)*(void**)sink + 4))(sink, c);
    }
    (*(void(__thiscall**)(int*, void*, void*, unsigned))((char*)*(void**)sink + 0x30))(sink, a, glyphs, count);
}
