// Slice s00fb84e0: the planet surface-colour / texture painter of Spore's scenario
// planet editor. A per-instance colouriser object holds a 6x float4 paint matrix and a
// bank of colour stops read out of a property bag, and exposes HSL-scaled stop colours
// plus a texture-driven ramp lookup used to shade the planet surface. Also here: the
// tile resampling kernel, the paint-texture build wrapper, and the model-refresh hook.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed char    i8;
typedef short          i16;
typedef int            i32;

// ---- colour value class ------------------------------------------------------
// Three-float colour passed by value: the original forwards exactly these three
// scalars in the low stack slots and copies them with movss / fld-fstp.
struct ColorRGB {
    float r, g, b;
    ColorRGB() {}
    ColorRGB(float rr, float gg, float bb) : r(rr), g(gg), b(bb) {}
    ColorRGB(const ColorRGB& o) : r(o.r), g(o.g), b(o.b) {}
};
struct Vec3 { float x, y, z; };

// SSE clamp helper (the original's inline EA math, maxss/minss).
__forceinline float Clamp01(float v)
{
    float hi = 1.0f;
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, v
        minss xmm0, hi
        movss v, xmm0
    }
    return v;
}

void __cdecl RGBToHSL(ColorRGB c, float* h, float* s, float* l);    // 0x67ff30

// =============================================================== callees
// Tile-sampling / quad-build kernels operating on a raw 0x400-strided buffer.
void __cdecl SampleTileA(void* buf, void* p3, void* p7);            // 0xfb7c70
void __cdecl SampleTileB(void* buf, void* p5, void* p6, int, int);  // 0xfb7dc0
void __cdecl SampleTileC(void* buf, void* p4, void* p6, int);       // 0xfb7f00
void __cdecl ReplicateRows(void* buf, int);                         // 0xfb8060
void __cdecl BuildQuadTiles(void* buf, int);                        // 0xfb8100
void __cdecl CopySubBuffer(void* buf, int);                         // 0xfb8410
void __cdecl ResampleTiles(int buf, int);                           // 0xfb84e0

// Colour-space helpers (platform library).
float* __cdecl HSLToRGB(float* out, float h, float s, float l);     // 0x67fe30

// Property bag access (0x41ea70) and texture lock / unlock (0x11ef750 / 0x11ef880);
// both callees clean their own stack arguments.
struct PropBag   { float* GetFloat(); };                            // 0x41ea70
struct TexDevice {
    int  Lock(int a, int b, void** out);                            // 0x11ef750
    void Unlock(void* h);                                           // 0x11ef880
};

void* __cdecl FUN_0067dd60();                                       // 0x67dd60

// ---- in-slice cross references ----------------------------------------------
float* ScaleHSL(float* out, ColorRGB c, float sS, float sL);        // 0xfb8fc0
float* ScaleHSLDiv(float* out, ColorRGB c, float dS, float dL,
                   char flag);                                      // 0xfb90b0

// =============================================================== painter object
struct PlanetColor {
    u8    pad00[4];
    void* mpDoc;          // +0x04 document / model owner (holds two scale floats)
    u8    pad08[0x2c - 0x08];
    float f2c;            // +0x2c ramp modulation source
    float f30;            // +0x30 ramp coordinate
    u8    pad34[0x120 - 0x34];
    float f120;           // +0x120
    float f124;           // +0x124
    u8    pad128[0x268 - 0x128];
    ColorRGB stop0;       // +0x268 colour stop 0
    ColorRGB stop1;       // +0x274 colour stop 1
    ColorRGB stop2;       // +0x280 colour stop 2
    ColorRGB stop3;       // +0x28c colour stop 3
    u8    pad298[0x2c0 - 0x298];
    float f2c0, f2c4, f2c8, f2cc, f2d0, f2d4, f2d8, f2dc,
          f2e0, f2e4, f2e8, f2ec, f2f0;   // +0x2c0 .. +0x2f0 stop parameters
    u8    pad2f4[0x328 - 0x2f4];
    void* mp328;          // +0x328 device owning the ramp texture
    u8    pad32c[0x494 - 0x32c];
    float mPaint[24];     // +0x494 paint matrix (6 float4 rows)
    u8    pad4f4[0x5b8 - 0x4f4];
    void* mpProp;         // +0x5b8 property bag

    float SampleRampScaled(float t, float scale);  // 0xfb8830
    float GetRampFraction();                       // 0xfb88d0
    void  InitPaintMatrix();                       // 0xfb8a10
    void  ReadProperties();                        // 0xfb8ae0
    void  SampleColor(float* out, float t);        // 0xfb8dd0
    void  SetStop3(float, float, float);           // 0xfb91d0
    void  SetStop2(float, float, float);           // 0xfb9240
    void* GetStop2(void* out, int flag);           // 0xfb92c0
    void* GetStop3(void* out, int flag);           // 0xfb9310
    void* GetStop0(void* out, int flag);           // 0xfb9360
    void* GetStop1(void* out, int flag);           // 0xfb93b0
};

// =============================================================== kernels

// @ 0x00fb84e0
void ResampleTiles(int base, int param_2)
{
    u32 uVar2 = 1;
    int iVar6 = param_2;
    int local_c = 0xfe00;
    int iVar3;
    do {
        iVar3 = (int)(uVar2 - 1) >> 2;
        int iVar5 = iVar6 - iVar3;
        int iVar4 = 4 - (int)((uVar2 - 1) & 3);
        u8* pbVar1 = (u8*)(base + 0x400 + ((local_c - iVar3) + param_2) * 4);
        iVar3 = 4 - iVar4;
        *pbVar1 = (u8)((int)((u32)*(u8*)(base + 0x3fbfc + iVar5 * 4) * iVar4 +
                             (u32)*pbVar1 * iVar3) >> 2);
        *(i8*)(base + 0x3fc01 + iVar5 * 4) =
            (i8)((int)((u32)*(u8*)(base + 0x3fbfd + iVar5 * 4) * iVar4 +
                       (u32)*(u8*)(base + 0x3fc01 + iVar5 * 4) * iVar3) >> 2);
        *(i8*)(base + 0x3fc02 + iVar5 * 4) =
            (i8)((int)((u32)*(u8*)(base + 0x3fbfe + iVar5 * 4) * iVar4 +
                       (u32)*(u8*)(base + 0x3fc02 + iVar5 * 4) * iVar3) >> 2);

        iVar3 = iVar6 - ((int)uVar2 >> 2);
        pbVar1 = (u8*)(base + ((local_c - ((int)uVar2 >> 2)) + param_2) * 4);
        iVar4 = 4 - (int)(uVar2 & 3);
        iVar5 = 4 - iVar4;
        *pbVar1 = (u8)((int)((u32)*(u8*)(base + 0x3f7fc + iVar3 * 4) * iVar4 +
                             (u32)*pbVar1 * iVar5) >> 2);
        *(i8*)(base + 0x3f801 + iVar3 * 4) =
            (i8)((int)((u32)*(u8*)(base + 0x3f7fd + iVar3 * 4) * iVar4 +
                       (u32)*(u8*)(base + 0x3f801 + iVar3 * 4) * iVar5) >> 2);
        *(i8*)(base + 0x3f802 + iVar3 * 4) =
            (i8)((int)((u32)*(u8*)(base + 0x3f7fe + iVar3 * 4) * iVar4 +
                       (u32)*(u8*)(base + 0x3f802 + iVar3 * 4) * iVar5) >> 2);

        iVar3 = (int)(uVar2 + 1) >> 2;
        iVar5 = 4 - (int)((uVar2 + 1) & 3);
        iVar4 = iVar6 - iVar3;
        pbVar1 = (u8*)(base + -0x400 + ((local_c - iVar3) + param_2) * 4);
        iVar3 = 4 - iVar5;
        *pbVar1 = (u8)((int)((u32)*(u8*)(base + 0x3f3fc + iVar4 * 4) * iVar5 +
                             (u32)*pbVar1 * iVar3) >> 2);
        *(i8*)(base + 0x3f401 + iVar4 * 4) =
            (i8)((int)((u32)*(u8*)(base + 0x3f3fd + iVar4 * 4) * iVar5 +
                       (u32)*(u8*)(base + 0x3f401 + iVar4 * 4) * iVar3) >> 2);
        *(i8*)(base + 0x3f402 + iVar4 * 4) =
            (i8)((int)((u32)*(u8*)(base + 0x3f3fe + iVar4 * 4) * iVar5 +
                       (u32)*(u8*)(base + 0x3f402 + iVar4 * 4) * iVar3) >> 2);

        iVar3 = (int)(uVar2 + 2) >> 2;
        iVar4 = iVar6 - iVar3;
        pbVar1 = (u8*)(base + -0x800 + ((local_c - iVar3) + param_2) * 4);
        iVar3 = 4 - (int)((uVar2 - 2) & 3);
        iVar5 = 4 - iVar3;
        *pbVar1 = (u8)((int)((u32)*(u8*)(base + 0x3effc + iVar4 * 4) * iVar3 +
                             (u32)*pbVar1 * iVar5) >> 2);
        local_c = local_c + -0x400;
        *(i8*)(base + 0x3f001 + iVar4 * 4) =
            (i8)((int)((u32)*(u8*)(base + 0x3effd + iVar4 * 4) * iVar3 +
                       (u32)*(u8*)(base + 0x3f001 + iVar4 * 4) * iVar5) >> 2);
        *(i8*)(base + 0x3f002 + iVar4 * 4) =
            (i8)((int)((u32)*(u8*)(base + 0x3effe + iVar4 * 4) * iVar3 +
                       (u32)*(u8*)(base + 0x3f002 + iVar4 * 4) * iVar5) >> 2);

        iVar6 = iVar6 + -0x400;
        iVar3 = uVar2 + 3;
        uVar2 = uVar2 + 4;
    } while (iVar3 < 0x100);
}

// @ 0x00fb8790
void BuildPaintTexture(void* p1, void* p2, void* p3, void* p4,
                       void* p5, void* p6, void* p7)
{
    SampleTileA(p1, p3, p7);
    SampleTileB(p1, p5, p6, 0, 0);
    ReplicateRows(p1, 0);
    BuildQuadTiles(p1, 0);
    SampleTileC(p1, p4, p6, 0x7f);
    CopySubBuffer(p1, 0x7f);
    ResampleTiles((int)p1, 0x7f);
    ReplicateRows(p1, 0x7f);
    BuildQuadTiles(p1, 0x7f);
    SampleTileB(p1, p2, p6, 0xff, 0);
    CopySubBuffer(p1, 0xff);
    ResampleTiles((int)p1, 0xff);
}

// =============================================================== colour ramp

// @ 0x00fb8830
float PlanetColor::SampleRampScaled(float t, float scale)
{
    void* o = *(void**)((u8*)this + 4);
    float f1 = *(float*)((u8*)o + 0x38);
    float f2 = *(float*)((u8*)o + 0x3c);
    float fm = f1 * f2;
    float x = (((1.0f - (f1 + fm) / (f1 * 2.0f)) * this->f124 + this->f120)
               / (f1 - fm)) * (t - fm) * scale;
    if (x > 0.0f) {
        if (x < 1.0f)
            return x;
        return 1.0f;
    }
    return 0.0f;
}

// @ 0x00fb88d0
float PlanetColor::GetRampFraction()
{
    float v = this->f30;
    float o;
    float lo;
    if (v < *(float*)0x15b15c0) {
        o = ((v - *(float*)0x16d66f4) / (*(float*)0x15b15c0 - *(float*)0x16d66f4))
            * (*(float*)0x15b15bc - *(float*)0x16d66f0) + *(float*)0x16d66f0;
        lo = 0.999f;
    } else if (v < *(float*)0x15b15b8) {
        o = ((v - *(float*)0x15b15c0) / (*(float*)0x15b15b4 - *(float*)0x15b15c0))
            * (*(float*)0x15b15b0 - *(float*)0x15b15ac) + *(float*)0x15b15ac;
        lo = (1.0f - fabsf(this->f2c + this->f2c - 1.0f)) * 0.999f;
    } else if (v < *(float*)0x15b15a8) {
        o = *(float*)0x15b15b0;
        lo = 0.999f;
    } else {
        o = ((v - *(float*)0x15b15a8) / (*(float*)0x15b15a4 - *(float*)0x15b15a8))
            * (*(float*)0x15b159c - *(float*)0x15b15a0) + *(float*)0x15b15a0;
        lo = 0.999f;
    }
    return (float)(int)(o * *(float*)0x13f2100) + lo;
}

// @ 0x00fb8a10
void PlanetColor::InitPaintMatrix()
{
    float* f = this->mPaint;
    f[0] = 0.0f;
    f[4] = 0.0f;
    f[1] = 0.0f;
    f[2] = 1.0f;
    f[3] = 1.0f;
    f[5] = 0.0f;
    f[6] = 1.0f;
    f[7] = 1.0f;
    f[8] = 0.0f;
    f[9] = 0.0f;
    f[10] = 1.0f;
    f[11] = 1.0f;
    f[12] = 0.0f;
    f[13] = 0.0f;
    f[14] = 1.0f;
    f[15] = 1.0f;
    f[16] = 0.0f;
    f[17] = 0.0f;
    f[18] = 1.0f;
    f[19] = 1.0f;
    f[20] = 0.0f;
    f[21] = 0.0f;
    f[22] = 1.0f;
    f[23] = 1.0f;
}

// =============================================================== properties

#define READ_PROP(k, member)                                                    \
    if (this->mpProp != 0) {                                                    \
        void* prop;                                                             \
        u8 ok = ((u8 (__thiscall*)(void*, u32, void**))                         \
                 *(void**)(*(char**)this->mpProp + 0x24))                       \
                 (this->mpProp, (k), &prop);                                    \
        if (ok != 0 && *(i16*)((u8*)prop + 0x12) == 0xd)                        \
            this->member = *((PropBag*)prop)->GetFloat();                       \
    }

// @ 0x00fb8ae0
void PlanetColor::ReadProperties()
{
    READ_PROP(0x7d61360, f2c0)
    READ_PROP(0x7b1ab36, f2c4)
    READ_PROP(0x7b1ab37, f2c8)
    READ_PROP(0x7b1ab38, f2cc)
    READ_PROP(0x7b1ab39, f2d0)
    READ_PROP(0x7b1ab3a, f2d4)
    READ_PROP(0x7d61361, f2d8)
    READ_PROP(0x7b1b699, f2dc)
    READ_PROP(0x7b1b69a, f2e0)
    READ_PROP(0x7b1b69b, f2e4)
    READ_PROP(0x7b1b69c, f2e8)
    READ_PROP(0x7b1b69d, f2ec)
    READ_PROP(0x7b1b69e, f2f0)
}

// =============================================================== sampling

// @ 0x00fb8dd0
void PlanetColor::SampleColor(float* out, float t)
{
    void* m = this->mp328;
    if ((*(u8*)((u8*)m + 4) & 1) == 0) {
        void* g = FUN_0067dd60();
        ((void (__thiscall*)(void*, void*))*(void**)(*(char**)g + 0x34))(g, m);
    }
    void* dev = *(void**)m;

    float fr = GetRampFraction();
    int idx = (int)floorf(fr);
    float frac = fr - (float)idx;

    float A[3] = { *(float*)0x16d6710, *(float*)0x16d6714, *(float*)0x16d6718 };
    float B[3] = { *(float*)0x16d6710, *(float*)0x16d6714, *(float*)0x16d6718 };

    void* tex = 0;
    if (((TexDevice*)dev)->Lock(1, 0, &tex) != 0) {
        float base = (float)((int)(t * *(float*)0x13f2100) << 8);
        u8* p = (u8*)tex + ((int)base + idx) * 4;
        A[2] = (float)p[2] * *(float*)0x13eecd4;
        A[1] = (float)p[1] * *(float*)0x13eecd4;
        A[0] = (float)p[0] * *(float*)0x13eecd4;
        int idx2 = idx + (int)floorf(*(float*)0x14911e0);
        u8* q = (u8*)tex + (idx2 - idx + (int)base) * 4;
        B[2] = (float)q[2] * *(float*)0x13eecd4;
        B[1] = (float)q[1] * *(float*)0x13eecd4;
        B[0] = (float)q[0] * *(float*)0x13eecd4;
        ((TexDevice*)dev)->Unlock(&tex);
    }

    out[0] = (A[2] - B[2]) * frac + B[2];
    out[1] = (A[1] - B[1]) * frac + B[1];
    out[2] = (A[0] - B[0]) * frac + B[0];
}

// =============================================================== HSL helpers

// @ 0x00fb8fc0
float* ScaleHSL(float* out, ColorRGB c, float sS, float sL)
{
    float H, L, S;
    RGBToHSL(c, &H, &S, &L);
    ColorRGB tmp;
    HSLToRGB((float*)&tmp, H, Clamp01(S * sS), Clamp01(L * sL));
    *(ColorRGB*)out = tmp;
    return out;
}

// @ 0x00fb90b0
float* ScaleHSLDiv(float* out, ColorRGB c, float dS, float dL, char flag)
{
    if (flag != 0) {
        float H, L, S;
        RGBToHSL(c, &H, &S, &L);
        ColorRGB tmp;
        HSLToRGB((float*)&tmp, H, Clamp01(S / dS), Clamp01(L / dL));
        *(ColorRGB*)out = tmp;
        return out;
    }
    out[0] = c.r;
    out[1] = c.g;
    out[2] = c.b;
    return out;
}

// =============================================================== stop setters

// @ 0x00fb91d0
void PlanetColor::SetStop3(float r, float g, float b)
{
    float tmp[3];
    float* p = ScaleHSL(tmp, ColorRGB(r, g, b), this->f2d0, this->f2e8);
    *(Vec3*)&this->stop3 = *(Vec3*)p;
}

// @ 0x00fb9240
void PlanetColor::SetStop2(float r, float g, float b)
{
    float tmp[3];
    float* p = ScaleHSL(tmp, ColorRGB(r, g, b), this->f2cc, this->f2e4);
    *(Vec3*)&this->stop2 = *(Vec3*)p;
}

// @ 0x00fb92c0
void* PlanetColor::GetStop2(void* out, int flag)
{
    ScaleHSLDiv((float*)out, this->stop2,
                this->f2cc, this->f2e4, (char)flag);
    return out;
}

// @ 0x00fb9310
void* PlanetColor::GetStop3(void* out, int flag)
{
    ScaleHSLDiv((float*)out, this->stop3,
                this->f2d0, this->f2e8, (char)flag);
    return out;
}

// @ 0x00fb9360
void* PlanetColor::GetStop0(void* out, int flag)
{
    ScaleHSLDiv((float*)out, this->stop0,
                this->f2c4, this->f2dc, (char)flag);
    return out;
}

// @ 0x00fb93b0
void* PlanetColor::GetStop1(void* out, int flag)
{
    ScaleHSLDiv((float*)out, this->stop1,
                this->f2c8, this->f2e0, (char)flag);
    return out;
}
