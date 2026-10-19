// src/game/UTFSpore_Win32/t2k.cpp -- migrated from slice(s) s008c0760, s008bfc10 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/t2k.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void tsi_Error(void* mem, int code);                              // 0x008d10c0
extern "C" void tsi_EmergencyShutDown(void* mem);                            // 0x008d1210
extern "C" void* tsi_AllocMem(void* mem, int size);                          // 0x008d1260
extern "C" int util_FixMul(int a, int b);                                    // 0x008d1590
extern "C" int util_FixDiv(int a, int b);                                    // 0x008d16d0
extern "C" int util_EuclidianDistance(int a, int b);                         // 0x008d17d0
extern "C" unsigned short GetUPEM(void* sfnt);                               // 0x008ceb70
extern "C" int GetNumGlyphs_sfntClass(void* sfnt);                           // 0x008cef90
extern "C" void setT2KScaleFactors(int ppem, int upem, void* out);           // 0x008cd1b0
extern "C" void GetFontWideSbitMetrics(void* a, void* b, int xppem, int yppem, void* hor, void* ver);   // 0x008c4f40
extern "C" void FUN_008cf460(void* sfnt, void* hor, void* ver);              // 0x008cf460
extern "C" void FUN_008ccbb0(void* a, int b, int c);                         // 0x008ccbb0
extern "C" void T2K_TransformXFunits(void* t, short units, int* outScaled, int* outRounded);   // 0x008bfdb0
extern "C" void T2K_TransformYFunits(void* t, short units, int* outScaled, int* outRounded);   // 0x008bfe10
#include <setjmp.h>
#include <string.h>

// ---- items of slice s008bfc10 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define I32(p, o) (*(int*)((char*)(p) + (o)))
#define I16(p, o) (*(short*)((char*)(p) + (o)))
#define U16(p, o) (*(unsigned short*)((char*)(p) + (o)))
#define I8(p, o) (*(char*)((char*)(p) + (o)))
#define PTR(p, o) (*(char**)((char*)(p) + (o)))
extern "C" void tsi_Error(void* mem, int code);                              // 0x008d10c0
extern "C" void tsi_EmergencyShutDown(void* mem);                            // 0x008d1210
extern "C" void* tsi_AllocMem(void* mem, int size);                          // 0x008d1260
extern "C" int util_FixMul(int a, int b);                                    // 0x008d1590
extern "C" int util_FixDiv(int a, int b);                                    // 0x008d16d0
extern "C" int util_EuclidianDistance(int a, int b);                         // 0x008d17d0
extern "C" unsigned short GetUPEM(void* sfnt);                               // 0x008ceb70
extern "C" int GetNumGlyphs_sfntClass(void* sfnt);                           // 0x008cef90
extern "C" void setT2KScaleFactors(int ppem, int upem, void* out);           // 0x008cd1b0
extern "C" void GetFontWideSbitMetrics(void* a, void* b, int xppem, int yppem, void* hor, void* ver);   // 0x008c4f40
extern "C" void FUN_008cf460(void* sfnt, void* hor, void* ver);              // 0x008cf460
extern "C" void FUN_008ccbb0(void* a, int b, int c);                         // 0x008ccbb0
extern "C" void T2K_TransformXFunits(void* t, short units, int* outScaled, int* outRounded);   // 0x008bfdb0
extern "C" void T2K_TransformYFunits(void* t, short units, int* outScaled, int* outRounded);   // 0x008bfe10
static void FUN_008bfc10(char* t)
{
    int x = I32(t, 0x128);
    if (I32(t, 0x16c) != x || I32(t, 0x170) != I32(t, 0x12c)) {
        char* sfnt = PTR(t, 0x184);
        if (I32(sfnt, 0x44) != 0) {
            I8(t, 0x174) = 0;
            FUN_008ccbb0(PTR(sfnt, 0x44), I32(t, 0x128), I32(t, 0x12c));
        }
        I32(t, 0x16c) = I32(t, 0x128);
        I32(t, 0x170) = I32(t, 0x12c);
    }
}
static void T2K_NewTransformationInternal(char* t, int* m, int arg, int x, int y)
{
    I32(t, 8) = m[0];
    I32(t, 0xc) = m[1];
    I32(t, 0x10) = m[2];
    I32(t, 0x14) = m[3];
    I32(t, 0x1c) = (I32(t, 8) == 0x10000 && I32(t, 0xc) == 0 && I32(t, 0x10) == 0 && I32(t, 0x14) == 0x10000) ? 1 : 0;
    I32(t, 0x128) = x;
    I32(t, 0x12c) = y;
    if (arg != 0)
        FUN_008bfc10(t);
}
static char* FUN_008bf2b0(int n, void* mem)
{
    char* p = (char*)tsi_AllocMem(mem, 0x18);
    PTR(p, 0) = (char*)mem;
    I32(p, 8) = -1;
    I32(p, 4) = -1;
    if (n > 0x800)
        n = 0x800;
    int size = ((n + 7) >> 3) * 2;
    I32(p, 0xc) = size;
    char* buf = (char*)tsi_AllocMem(mem, size);
    PTR(p, 0x10) = buf;
    PTR(p, 0x14) = buf + (I32(p, 0xc) >> 1);
    return p;
}
static void ConcatFontMatrix(int* m, char* sfnt)
{
#define A20(o) I32(PTR(sfnt, 0x20), o)
#define A24(o) I32(PTR(sfnt, 0x24), o)
    if (PTR(sfnt, 0x20) != 0) {
        m[0] = util_FixMul(A20(0x20c), m[1]) + util_FixMul(A20(0x204), m[0]);
        m[2] = util_FixMul(A20(0x20c), m[3]) + util_FixMul(A20(0x204), m[2]);
        int t1 = util_FixMul(A20(0x208), m[0]);
        t1 += util_FixMul(A20(0x210), m[1]);
        m[1] = t1;
        m[3] = util_FixMul(A20(0x210), m[3]) + util_FixMul(A20(0x208), m[2]);
    }
    if (PTR(sfnt, 0x24) != 0) {
        m[0] = util_FixMul(A24(0x4e0), m[1]) + util_FixMul(A24(0x4d8), m[0]);
        m[2] = util_FixMul(A24(0x4e0), m[3]) + util_FixMul(A24(0x4d8), m[2]);
        m[1] = util_FixMul(A24(0x4e4), m[1]) + util_FixMul(A24(0x4dc), m[0]);
        m[3] = util_FixMul(A24(0x4e4), m[3]) + util_FixMul(A24(0x4dc), m[2]);
    }
#undef A20
#undef A24
}
struct FontWideMetrics {
    int valid;                      // +0
    short a, b;                     // +4  (T2K 26.6 values)
    short c; unsigned short d;      // +8
    int e, f;                       // +0xc, +0x10
    short g, h;                     // +0x14
};
// ---- items of slice s008bfc10 end

// ---- items of slice s008c0760 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void tsi_DeAllocMem(void* mem, void* p);  // 0x008d1440
extern "C" void Delete_GlyphClass(void* glyph);  // 0x008b0280
extern "C" unsigned short GetSfntClassGlyphIndex(void* sfnt, int ch);  // 0x008d0b00
extern "C" char* FUN_008cefe0(void* sfnt, int idx, unsigned flag, unsigned short* adv, unsigned short* adv2);
extern "C" int IsFigure(void* sfnt, int ch);  // 0x008d0b60
extern "C" void FUN_008afee0(char** outGlyph, char* glyph, unsigned flags, int x, int y);
extern "C" void FUN_008cceb0(void* a, void* glyph);
extern "C" void SetScale_FFT1HintClass(void* h, int sx, int sy);  // 0x008a8830
extern "C" void FUN_008abc50(void* h, int a, int b, int c, int d, int e, int f, int g, int h2, int i, int j, int k);
extern "C" void ApplyHints_FFT1HintClass(void* h, int n, int four, void* glyph);  // 0x008a8880
extern "C" char* FUN_008c8c30(void* mem, unsigned short a, int b, int c, int* xs, int* ys, int d, int e, int f, int g, int h, int i, int j, int k, int l);
extern "C" void FUN_008c9000(char* bmp, int a, int b, int c, int d, int e, int f, int g);
extern "C" void FUN_008c9a70(char* bmp);
#define U32(p, o) (*(unsigned*)((char*)(p) + (o)))
#define IARR(p, o) ((int*)I32(p, o))
#define SARR(p, o) ((short*)I32(p, o))
static __declspec(noinline) void scalePoints(short* src, int* dst, void* scale, int count)
{
    short mode = I16(scale, 0x10);
    short mul = I16(scale, 0);
    int round = I32(scale, 8);
    int i;
    if (mode == 0) {
        short shift = I16(scale, 2);
        for (i = 0; i < count; i++)
            dst[i] = (src[i] * (int)mul + round) >> (shift & 0x1f);
    } else if (mode == 1) {
        int denom = I32(scale, 4);
        for (i = 0; i < count; i++) {
            int v = src[i] * (int)mul;
            if (v >= 0)
                dst[i] = (v + round) / denom;
            else
                dst[i] = -((round - v) / denom);
        }
    } else if (mode == 2) {
        int m = I32(scale, 0xc);
        for (i = 0; i < count; i++)
            dst[i] = util_FixMul(m, src[i]);
    }
}
// ---- items of slice s008c0760 end

// @ 0x008c0000
void T2K_NewTransformation(char* t, int arg, int ptSizeX, int ptSizeY, int* matrixIn, int wantSbit, int* errOut)
{
    int mat[4];
    int* m = mat;
    int sx, sy;                     // matrix scale (|column| lengths)

    *errOut = setjmp(*(jmp_buf*)(PTR(t, 4) + 0x10));
    if (*errOut == 0) {
    if (matrixIn == 0)
        tsi_Error(PTR(t, 4), 0x2711);
    if (ptSizeX <= 0 || ptSizeY <= 0)
        tsi_Error(PTR(t, 4), 0x2712);

    m[0] = matrixIn[0];
    m[1] = matrixIn[1];
    m[2] = matrixIn[2];
    m[3] = matrixIn[3];
    ConcatFontMatrix(m, PTR(t, 0x184));
    unsigned short upem16 = GetUPEM(PTR(t, 0x184));
    U16(t, 0x180) = upem16;
    if (m[2] != 0 && m[1] != 0) {
        sx = util_EuclidianDistance(m[0], m[2]);
        sy = util_EuclidianDistance(m[1], m[3]);
    } else {
        sx = m[0];
        if (sx < 0)
            sx = -sx;
        sy = m[3];
        if (sy < 0)
            sy = -sy;
    }
    int fx = util_FixMul(sx, (ptSizeX << 16) / 72);
    int fy = util_FixMul(sy, (ptSizeY << 16) / 72);
    int upem = upem16;
    int upemFixed = upem << 16;
    I32(t, 0x130) = fx;
    I32(t, 0x134) = fy;
    I32(t, 0x138) = util_FixDiv(fx, upemFixed);
    I32(t, 0x13c) = util_FixDiv(I32(t, 0x134), upemFixed);
    int xppem = (fx + 0x8000) >> 16;
    int yppem = (fy + 0x8000) >> 16;
    if (xppem > 0 && yppem > 0) {
        m[0] = util_FixDiv(m[0], sx);
        m[2] = util_FixDiv(m[2], sx);
        m[3] = util_FixDiv(m[3], sy);
        m[1] = util_FixDiv(m[1], sy);
    } else {
        m[0] = 0;
        m[2] = 0;
        m[3] = 0;
        m[1] = 0;
    }
    if (PTR(t, 0x184) != 0) {
        I32(PTR(t, 0x184), 0x9c) = xppem;
        I32(PTR(t, 0x184), 0xa0) = yppem;
    }
    T2K_NewTransformationInternal(t, m, arg, xppem, yppem);
    setT2KScaleFactors(xppem, upem, t + 0x140);
    setT2KScaleFactors(yppem, upem, t + 0x154);
    if (PTR(t, 0x18) == 0) {
        int n = GetNumGlyphs_sfntClass(PTR(t, 0x184));
        PTR(t, 0x18) = FUN_008bf2b0(n, PTR(t, 4));
    }
    char* cache = PTR(t, 0x18);
    if (I32(cache, 4) != xppem || I32(cache, 8) != xppem) {
        I32(cache, 4) = xppem;
        I32(cache, 8) = xppem;
        if (I32(cache, 0xc) > 0)
            memset(PTR(cache, 0x10), 0, I32(cache, 0xc));
    }
    int minppem = xppem;
    if (yppem < minppem)
        minppem = yppem;
    I32(t, 0x168) = (minppem << 6) / (upem * 2);
    I32(t, 0x64) = 0;
    I32(t, 0xa0) = 0;

    char* sfnt = PTR(t, 0x184);
    if (PTR(sfnt, 0x28) != 0)
        I32(t, 0x17c) = (wantSbit != 0 && I16(PTR(sfnt, 0x28), 0x38) != 0 && I32(t, 0x1c) != 0) ? 1 : 0;
    else
        I32(t, 0x17c) = (wantSbit != 0 && I32(sfnt, 0x38) != 0 && I32(t, 0x1c) != 0) ? 1 : 0;
    FontWideMetrics hor = { 0 };
    FontWideMetrics ver = { 0 };
    int computed = 0;
    if (I32(t, 0x17c) != 0 && PTR(sfnt, 0x28) == 0) {
        hor.g = I16(sfnt, 0x8c);
        hor.h = I16(sfnt, 0x8c);
        ver.g = 0;
        ver.h = 0;
        GetFontWideSbitMetrics(PTR(sfnt, 0x38), PTR(sfnt, 0x3c), xppem, yppem, &hor, &ver);
        I32(t, 0x64) = hor.valid;
        I32(t, 0xa0) = ver.valid;
    }
    if (I32(t, 0x64) == 0 && I32(t, 0xa0) == 0) {
        FUN_008cf460(PTR(t, 0x184), &hor, &ver);
        computed = 1;
    }
    if (hor.valid != 0) {
        I32(t, 0x6c) = (int)hor.a << 16;
        I32(t, 0x74) = (int)hor.b << 16;
        I32(t, 0x94) = (int)hor.g;
        I32(t, 0x7c) = (int)hor.c << 16;
        I32(t, 0x80) = (unsigned)hor.d << 16;
        I32(t, 0x68) = 0;
        I32(t, 0x70) = 0;
        I32(t, 0x78) = 0;
        I32(t, 0x84) = 0;
        I32(t, 0x88) = hor.e;
        I32(t, 0x8c) = hor.f;
        I32(t, 0x9c) = (int)hor.h;
        I32(t, 0x64) = 1;
        if (computed) {
            if (I32(t, 0x1c) == 0) {
                int e = hor.e, f = hor.f;
                I32(t, 0x88) = util_FixMul(I32(t, 8), e) + util_FixMul(I32(t, 0xc), f);
                I32(t, 0x8c) = util_FixMul(I32(t, 0x14), f) + util_FixMul(I32(t, 0x10), e);
            }
            T2K_TransformYFunits(t, hor.a, (int*)(t + 0x68), (int*)(t + 0x6c));
            T2K_TransformYFunits(t, hor.b, (int*)(t + 0x70), (int*)(t + 0x74));
            T2K_TransformYFunits(t, hor.c, (int*)(t + 0x78), (int*)(t + 0x7c));
            T2K_TransformXFunits(t, hor.d, (int*)(t + 0x80), (int*)(t + 0x84));
            T2K_TransformYFunits(t, hor.g, (int*)(t + 0x90), (int*)(t + 0x94));
            T2K_TransformYFunits(t, hor.h, (int*)(t + 0x98), (int*)(t + 0x9c));
        }
    }
    if (ver.valid != 0) {
        I32(t, 0xa4) = (int)ver.a << 16;
        I32(t, 0xac) = (int)ver.b << 16;
        I32(t, 0x90) = (int)ver.g;
        I32(t, 0xb4) = (int)ver.c << 16;
        I32(t, 0xc0) = (unsigned)ver.d << 16;
        I32(t, 0xa8) = 0;
        I32(t, 0xb0) = 0;
        I32(t, 0xb8) = 0;
        I32(t, 0xbc) = 0;
        I32(t, 0xc4) = ver.e;
        I32(t, 0xc8) = ver.f;
        I32(t, 0x98) = (int)ver.h;
        I32(t, 0xa0) = 1;
        if (computed) {
            if (I32(t, 0x1c) == 0) {
                int e = ver.e, f = ver.f;
                I32(t, 0xc4) = util_FixMul(I32(t, 8), e) + util_FixMul(I32(t, 0xc), f);
                I32(t, 0xc8) = util_FixMul(I32(t, 0x14), f) + util_FixMul(I32(t, 0x10), e);
            }
            T2K_TransformXFunits(t, ver.a, (int*)(t + 0xa4), (int*)(t + 0xa8));
            T2K_TransformXFunits(t, ver.b, (int*)(t + 0xac), (int*)(t + 0xb0));
            T2K_TransformXFunits(t, ver.c, (int*)(t + 0xb4), (int*)(t + 0xb8));
            T2K_TransformYFunits(t, ver.d, (int*)(t + 0xbc), (int*)(t + 0xc0));
        }
    }
    } else {
        tsi_EmergencyShutDown(PTR(t, 4));
    }
}

// @ 0x008c0760
void T2K_RenderGlyphInternal(char* t, int ch, unsigned depth, int param_4, int param_5, int param_6, unsigned flags)
{
    unsigned short advX;
    unsigned short advY[2];
    char* sfnt;
    char* g;
    int n;                 // iVar14: number of contour points
    int* pX;               // local_50 (point X array, 26.6)
    int* pY;               // local_54
    int local_14, local_18;
    int local_20 = 0, local_24 = 0, local_28;
    unsigned local_2c, local_30, local_34;
    int local_40, local_44;
    unsigned local_48, local_1c;
    int local_4c;

    local_48 = flags & 0x80;
    local_1c = 1;
    local_40 = 0;
    local_44 = 0;
    local_2c = 0;
    local_30 = 0;
    unsigned newFlags = flags;
    if (local_48 != 0) {
        char* hs = PTR(t, 0x184);
        char* hg = PTR(hs, 0x50);
        if (hg == 0 || ((1999 < I16(hg, 0x38) && I16(hg, 0x38) < 0x7d3) || (local_44 = 1, I32(hs, 0x78) != 0))) {
            local_44 = 0;
        }
        local_2c = I32(hs, 0x20) != 0;
        local_30 = I32(hs, 0x28) != 0;
        newFlags = flags & 0xfffe;
        if (local_44 == 0) {
            if (local_2c != 0 || local_30 != 0) {
                local_40 = 1;
            } else {
                local_48 = 0;
                newFlags = flags & 0xff7e;
            }
        } else if (I32(t, 0x128) < (int)U16(hg, 0x32) || I32(t, 300) < (int)U16(hg, 0x32)) {
            local_48 = 0;
            newFlags = flags & 0xff7e;
            local_40 = 1;
        }
    }
    flags = newFlags;
    if (5 < (unsigned char)param_6) {
        tsi_Error(PTR(t, 4), 0x2713);
    }
    local_14 = (unsigned short)I16(t, 0x180);
    Delete_GlyphClass(PTR(t, 0x104));
    char* mem118 = PTR(t, 0x118);
    PTR(t, 0x104) = 0;
    if (mem118 != 0 && I32(t, 0x30) != 0) {
        char* mm = PTR(t, 4);
        if (mem118 == PTR(mm, 100)) {
            I32(mm, 0x9c) = 1;
        } else {
            tsi_DeAllocMem(mm, mem118);
        }
        PTR(t, 0x118) = 0;
    }
    if (PTR(t, 0x11c) != 0 && I32(t, 0x34) != 0) {
        tsi_DeAllocMem(PTR(t, 4), PTR(t, 0x11c));
        PTR(t, 0x11c) = 0;
    }
    sfnt = PTR(t, 0x184);
    I32(sfnt, 0xc0) = I32(t, 0x14c);
    I32(PTR(t, 0x184), 0xc4) = I32(t, 0x160);
    if ((flags & 8) == 0) {
        g = FUN_008cefe0(PTR(t, 0x184), GetSfntClassGlyphIndex(PTR(t, 0x184), ch), local_48, &advX, advY);
        if (depth == 0) {
            I16(t, 0x108) = I16(g, 0x76);
            if ((unsigned char)param_6 == 0) {
                I8(t, 0x124) = 1;
            } else {
                I8(t, 0x124) = (I32(t, 0x48) != 0) + 7;
            }
        }
    } else {
        g = FUN_008cefe0(PTR(t, 0x184), ch, local_48, &advX, advY);
        IsFigure(PTR(t, 0x184), ch);
        if (depth == 0) {
            I16(t, 0x108) = (short)ch;
            if ((unsigned char)param_6 == 0) {
                I8(t, 0x124) = 1;
            } else {
                I8(t, 0x124) = (I32(t, 0x48) != 0) + 7;
            }
        }
    }
    if (g == 0) {
        tsi_Error(PTR(t, 4), 0x2715);
    }
    PTR(t, 0x104) = g;
    if (I16(g, 0x36) < 0) {
        // composite glyph
        int saved64 = I32(g, 100);
        int* saved68 = (int*)PTR(g, 0x68);
        unsigned short* comp = (unsigned short*)PTR(g, 0x58);
        PTR(g, 0x58) = 0;
        I32(g, 100) = 0;
        PTR(g, 0x68) = 0;
        int local_10 = I32(t, 8);
        int local_8 = I32(t, 0x10);
        local_28 = I32(t, 0x128);
        int local_c = I32(t, 0xc);
        int local_4 = I32(t, 0x14);
        local_30 = I32(t, 300);
        unsigned recFlags = (unsigned char)flags & 0x9d | 0xc;
        char* newGlyph = 0;
        unsigned acc38 = 0;
        if (I32(t, 0x178) == 2) {
            recFlags &= 0xfdfe;
        }
        local_20 = depth + 1;
        unsigned short* compBase = comp;
        unsigned uVar9;
        do {
            unsigned short cf = *comp;
            local_2c = cf;
            local_24 = comp[1];
            acc38 |= local_2c;
            int uVar13 = (short)comp[2];
            unsigned short* p15 = comp + 3;
            if ((cf & 1) == 0) {
                if ((cf & 2) == 0) {
                    local_4c = uVar13 & 0xff;
                    uVar13 = (uVar13 >> 8) & 0xff;
                    comp = p15;
                } else {
                    local_4c = (char)comp[2];
                    uVar13 = uVar13 >> 8;
                    comp = p15;
                }
            } else {
                local_4c = (short)*p15;
                comp = comp + 4;
            }
            if ((cf & 2) != 0) {
                short sVar3 = I16(t, 0x180);
                uVar13 = (I32(t, 0x128) * uVar13 * 0x40 + (sVar3 >> 1)) / sVar3;
                local_4c = (I32(t, 300) * local_4c * 0x40 + (sVar3 >> 1)) / sVar3;
            }
            int m00, m01, m10, m11;
            if ((cf & 8) != 0) {
                m00 = (short)*comp * 4;
                comp = comp + 1;
                m10 = 0;
                m01 = 0;
                m11 = m00;
            } else if ((cf & 0x40) != 0) {
                m00 = (short)comp[0] * 4;
                m01 = 0;
                m10 = 0;
                m11 = (short)comp[1] * 4;
                comp = comp + 2;
            } else if ((char)cf < 0) {
                m00 = (short)comp[0] * 4;
                m10 = (short)comp[1] * 4;
                m01 = (short)comp[2] * 4;
                m11 = (short)comp[3] * 4;
                comp = comp + 4;
            } else {
                m00 = 0x10000;
                m10 = 0;
                m01 = 0;
                m11 = m00;
            }
            I32(t, 8) = m00;
            I32(t, 0xc) = m01;
            I32(t, 0x10) = m10;
            I32(t, 0x14) = m11;
            if (m00 == 0x10000 && m01 == 0 && m10 == 0 && m11 == 0x10000) {
                I32(t, 0x1c) = 1;
            } else {
                I32(t, 0x1c) = 0;
            }
            T2K_RenderGlyphInternal(t, local_24, local_20, param_4, param_5, 0, recFlags);
            uVar9 = local_2c;
            I32(t, 8) = local_10;
            I32(t, 0xc) = local_c;
            I32(t, 0x10) = local_8;
            I32(t, 0x14) = local_4;
            if (local_10 == 0x10000 && local_c == 0 && local_8 == 0 && local_4 == 0x10000) {
                I32(t, 0x1c) = 1;
            } else {
                I32(t, 0x1c) = 0;
            }
            I32(t, 0x128) = local_28;
            I32(t, 300) = local_30;
            FUN_008afee0(&newGlyph, PTR(t, 0x104), local_2c, uVar13, local_4c);
            if (newGlyph != PTR(t, 0x104)) {
                Delete_GlyphClass(PTR(t, 0x104));
            }
            g = newGlyph;
            PTR(t, 0x104) = 0;
        } while ((uVar9 & 0x20) != 0);
        char* mm = PTR(t, 4);
        int* pp = (int*)(newGlyph + 100);
        PTR(t, 0x104) = newGlyph;
        int cur = *pp;
        if (cur == I32(mm, 0x5c)) {
            I32(mm, 0x94) = 1;
        } else {
            tsi_DeAllocMem(mm, (void*)cur);
        }
        *pp = saved64;
        PTR(g, 0x68) = (char*)saved68;
        tsi_DeAllocMem(PTR(t, 4), compBase);
        pX = IARR(g, 0x50);
        pY = IARR(g, 0x54);
        n = I16(g, 0x38);
        if ((acc38 & 0x200) == 0) {
            SARR(g, 0x44)[n] = 0;
            SARR(g, 0x44)[I16(g, 0x38) + 1] =
                SARR(g, 0x44)[I16(PTR(t, 0x104), 0x38)] + (short)advX;
            IARR(g, 0x50)[I16(g, 0x38) + 1] =
                ((int)SARR(g, 0x44)[I16(g, 0x38) + 1] * I32(t, 0x128) * 0x40 + (I16(t, 0x180) >> 1)) /
                I16(t, 0x180);
            if ((flags & 0x81) != 0) {
                int* p = &IARR(g, 0x50)[I16(g, 0x38) + 1];
                *p = *p + 0x20;
                unsigned* q = (unsigned*)&IARR(g, 0x50)[I16(g, 0x38) + 1];
                *q = *q & 0xffffffc0;
            }
            IARR(g, 0x50)[I16(g, 0x38)] = 0;
        }
        if ((flags & 0x80) != 0) {
            unsigned upem = local_14 & 0xffff;
            local_14 = util_FixDiv(upem, I32(t, 0x128) << 6);
            local_18 = util_FixDiv(upem, I32(t, 300) << 6);
            n = I16(g, 0x38);
            int i = 0;
            if (n != -4 && -1 < n + 4) {
                local_4c = (int)pX - (int)pY;
                int* it = pY;
                do {
                    local_20 = *it;
                    local_24 = util_FixMul(*(int*)(local_4c + (int)it), local_14);
                    short sy = (short)util_FixMul(local_20, local_18);
                    it = it + 1;
                    SARR(g, 0x44)[i] = (short)local_24;
                    SARR(g, 0x48)[i] = sy;
                    i = i + 1;
                } while (i < n + 4);
            }
            if (local_48 != 0 && local_44 != 0) {
                FUN_008cceb0(PTR(PTR(t, 0x184), 0x44), g);
            }
        }
    } else {
        pX = IARR(g, 0x50);
        pY = IARR(g, 0x54);
        n = I16(g, 0x38);
        if (local_48 == 0 || (flags & 0x10) != 0 || n < 1) {
            scalePoints(SARR(g, 0x44), pX, t + 0x140, n + 4);
            scalePoints(SARR(g, 0x48), pY, t + 0x154, n + 4);
            if ((flags & 0x10) != 0) {
                int i;
                if ((char)param_4 != 0 && (i = 0, 0 < n)) {
                    do {
                        pX[i] = pX[i] + (char)param_4;
                        i = i + 1;
                    } while (i < n);
                }
                if ((char)param_5 != 0 && (i = 0, 0 < n)) {
                    do {
                        pY[i] = pY[i] - (char)param_5;
                        i = i + 1;
                    } while (i < n);
                }
            }
        } else {
            if (local_44 != 0) {
                scalePoints(SARR(g, 0x44), pX, t + 0x140, n + 4);
                scalePoints(SARR(g, 0x48), pY, t + 0x154, n + 4);
                FUN_008cceb0(PTR(PTR(t, 0x184), 0x44), g);
            }
            if (local_2c != 0) {
                SetScale_FFT1HintClass(PTR(PTR(t, 0x184), 0x48), I32(t, 0x128), I32(t, 300));
                char* hx = PTR(PTR(t, 0x184), 0x20);
                FUN_008abc50(PTR(PTR(t, 0x184), 0x48), I32(hx, 0x14c), I32(hx, 0x150), I32(hx, 0x158),
                             I32(hx, 0x154), (int)(hx + 0x114), I32(hx, 0x1c8), I32(hx, 0x1c4),
                             (int)(hx + 400), (int)(hx + 0x15c), I32(hx, 0x1c0), I32(hx, 0x18c));
                ApplyHints_FFT1HintClass(PTR(PTR(t, 0x184), 0x48), n, 4, g);
            }
            if (local_30 != 0) {
                SetScale_FFT1HintClass(PTR(PTR(t, 0x184), 0x48), I32(t, 0x128), I32(t, 300));
                char* hy = PTR(PTR(t, 0x184), 0x28);
                FUN_008abc50(PTR(PTR(t, 0x184), 0x48), I32(hy, 0x164), I32(hy, 0x168), I32(hy, 0x16c),
                             I32(hy, 0x170), (int)(hy + 300), I32(hy, 0x174), I32(hy, 0x178),
                             (int)(hy + 0x1b4), (int)(hy + 0x184), I32(hy, 0x17c), I32(hy, 0x180));
                ApplyHints_FFT1HintClass(PTR(PTR(t, 0x184), 0x48), n, 4, g);
            }
        }
    }

    int* piVar18 = pX;
    I32(t, 0xd8) = (int)advX << 0x10;
    I32(t, 0xdc) = 0;
    I32(t, 0xf8) = (int)advY[0] << 0x10;
    I32(t, 0xf4) = 0;
    if (depth == 0) {
        int centre;
        if ((flags & 0x140) == 0 || (centre = 1, local_48 != 0)) {
            centre = 0;
        }
        int sh = pX[n];
        if (sh != 0) {
            int i = 0;
            if (0 < n + 4) {
                do {
                    pX[i] = pX[i] - sh;
                    i = i + 1;
                } while (i < n + 4);
            }
        }
        local_14 = pY[n];
        int i;
        if (local_14 != 0 && (i = 0, n != -4 && -1 < n + 4)) {
            do {
                pY[i] = pY[i] - local_14;
                i = i + 1;
            } while (i < n + 4);
        }
        if ((flags & 0x10) == 0) {
            int lsb = pX[n];
            int adv = pX[n + 1];
            unsigned uVar13 = (unsigned)(lsb + 0x20) & 0xffffffc0;
            int w = (((adv - lsb) + 0x20) & 0xffffffc0) + uVar13;
            pX[n] = uVar13;
            pX[n + 1] = w;
            int sft;
            if (centre != 0 && 0 < n && (sft = ((w - adv) - lsb + (int)uVar13) >> 1, sft != 0) &&
                (i = 0, 0 < n)) {
                do {
                    pX[i] = pX[i] + sft;
                    i = i + 1;
                } while (i < n);
            }
        }
    }
    I32(t, 0xd8) = util_FixMul(I32(t, 0xd8), I32(t, 0x138));
    I32(t, 0xf8) = util_FixMul(I32(t, 0xf8), I32(t, 0x13c));
    piVar18[n] = piVar18[n] << 10;
    pY[n] = pY[n] << 10;
    piVar18[n + 1] = piVar18[n + 1] << 10;
    pY[n + 1] = pY[n + 1] << 10;
    piVar18[n + 2] = piVar18[n + 2] << 10;
    pY[n + 2] = pY[n + 2] << 10;
    piVar18[n + 3] = piVar18[n + 3] << 10;
    pY[n + 3] = pY[n + 3] << 10;
    if (I32(t, 0x1c) == 0) {
        local_34 = I32(t, 8);
        local_20 = I32(t, 0xc);
        local_2c = I32(t, 0x14);
        local_24 = I32(t, 0x10);
        if (local_20 == 0 && local_24 == 0) {
            local_30 = n + 4;
            if (0 < (int)local_30) {
                local_4c = (int)piVar18 - (int)pY;
                int* it50 = pY;
                do {
                    int y = *it50;
                    *(int*)((int)it50 + local_4c) = util_FixMul(local_34, *(int*)((int)it50 + local_4c));
                    *it50 = util_FixMul(local_2c, y);
                    it50 = it50 + 1;
                    local_30 = local_30 - 1;
                } while (local_30 != 0);
            }
        } else if (0 < n + 4) {
            local_4c = (int)piVar18 - (int)pY;
            int* it38 = pY;
            local_28 = n + 4;
            do {
                int x = *(int*)((int)it38 + local_4c);
                int y = *it38;
                local_30 = x;
                local_14 = util_FixMul(local_20, y);
                int a = util_FixMul(local_34, x);
                *(int*)((int)it38 + local_4c) = local_14 + a;
                int b = util_FixMul(local_2c, y);
                int c = util_FixMul(local_24, local_30);
                *it38 = b + c;
                it38 = it38 + 1;
                local_28 = local_28 - 1;
            } while (local_28 != 0);
            local_28 = 0;
        }
        local_30 = I32(t, 0xd8);
        I32(t, 0xd8) = util_FixMul(local_34, local_30);
        I32(t, 0xdc) = util_FixMul(local_24, local_30);
        int adv2 = I32(t, 0xf8);
        I32(t, 0xf4) = util_FixMul(local_20, adv2);
        I32(t, 0xf8) = util_FixMul(local_2c, adv2);
    }
    I32(t, 0xd0) = piVar18[n + 1] - piVar18[n];
    unsigned thr = 0xff;
    I32(t, 0xd4) = pY[n + 1] - pY[n];
    I32(t, 0xec) = piVar18[n + 2] - piVar18[n + 3];
    I32(t, 0xf0) = pY[n + 2] - pY[n + 3];
    piVar18[n] = piVar18[n] >> 10;
    pY[n] = pY[n] >> 10;
    piVar18[n + 1] = piVar18[n + 1] >> 10;
    pY[n + 1] = pY[n + 1] >> 10;
    piVar18[n + 2] = piVar18[n + 2] >> 10;
    pY[n + 2] = pY[n + 2] >> 10;
    piVar18[n + 3] = piVar18[n + 3] >> 10;
    pY[n + 3] = pY[n + 3] >> 10;
    I32(t, 0x11c) = 0;
    I32(t, 0x118) = 0;
    I32(t, 0x114) = 0;
    I32(t, 0x10c) = 0;
    I32(t, 0x110) = 0;
    I32(t, 0xe0) = 0;
    I32(t, 0xe4) = 0;
    I32(t, 0xfc) = 0;
    I32(t, 0x100) = 0;
    I8(g, 0x74) = 1;
    if (local_48 != 0 && local_44 != 0) {
        if (I32(t, 0x1c) != 0) {
            unsigned w7c = U32(PTR(PTR(t, 0x184), 0x44), 0x7c);
            unsigned lo = w7c & 0xff;
            if (lo != 0xff) {
                thr = lo;
            }
            if ((w7c & 0x2000) != 0) {
                thr = 0;
            }
        }
        unsigned w7c = U32(PTR(PTR(t, 0x184), 0x44), 0x7c);
        local_1c = w7c >> 0x11 & 1;
        local_40 = w7c >> 0x12 & 1;
        I8(g, 0x74) = (unsigned char)(w7c >> 0x10) & 1;
    }
    if ((int)thr < I32(t, 0x128)) {
        I8(g, 0x74) = 0;
    }
    if ((flags & 2) != 0 && I16(g, 0x38) >= 1) {
        char* bmp = 0;
        if (I8(t, 0x174) == 0 || (flags & 1) == 0) {
            local_2c = local_2c & 0xffffff00;
        } else {
            local_2c = (local_2c & 0xffffff00) | 1;
            if (0x18 < I32(t, 0x16c)) {
                local_2c = local_2c & 0xffffff00;
            }
        }
        if (I32(g, 0xc) < 1) {
            unsigned short gid = U16(t, 0x108);
            local_30 = gid;
            char vis = I8(g, 0x74);
            local_20 = (local_20 & 0xffffff00) | (unsigned char)vis;
            local_24 = (local_24 & 0xffffff00) | (unsigned char)vis;
            if ((unsigned char)param_6 == 0 && I32(t, 0x1c) != 0 && vis != 0 && gid < 0x800) {
                unsigned char bit = (unsigned char)(1 << (gid & 7));
                if ((*(unsigned char*)((gid >> 3) + I32(PTR(t, 0x18), 0x10)) & bit) != 0) {
                    local_24 = local_24 & 0xffffff00;
                }
                if ((*(unsigned char*)((gid >> 3) + I32(PTR(t, 0x18), 0x14)) & bit) != 0) {
                    local_20 = local_20 & 0xffffff00;
                }
            }
            unsigned f100 = flags & 0x100;
            local_44 = 0;
            if (f100 == 0 || (flags & 0x4000) != 0 || (flags & 0x8000) != 0) {
                if (((unsigned short)flags & 0x4000) == 0x4000 || (flags & 0x8000) != 0) {
                    local_44 = 2;
                }
            } else {
                local_44 = 1;
            }
            unsigned short f4000 = (unsigned short)flags & 0x4000;
            if (f4000 != 0x4000 && (flags & 0x8000) == 0 && (short)f100 != 0) {
                local_44 = 1;
            }
            if ((flags & 0x3000) == 0) {
                if (f4000 == 0x4000 || (flags & 0x8000) != 0) {
                    int cnt = (int)*(short*)(I32(g, 0x40) - 2 + I16(g, 0x36) * 2) + 1;
                    int i = 0;
                    if (0 < cnt) {
                        do {
                            pY[i] = pY[i] * 3;
                            i = i + 1;
                        } while (i < cnt);
                    }
                    I32(t, 0xe0) = I32(t, 0xe0) * 3;
                    I32(t, 0xfc) = I32(t, 0xfc) * 3;
                }
            } else {
                int cnt = *(short*)(I32(g, 0x40) - 2 + I16(g, 0x36) * 2) + 1;
                int i = 0;
                if (0 < cnt) {
                    do {
                        piVar18[i] = piVar18[i] * 3;
                        i = i + 1;
                    } while (i < cnt);
                }
                I32(t, 0xe4) = I32(t, 0xe4) * 3;
                I32(t, 0x100) = I32(t, 0x100) * 3;
            }
            if (I32(t, 0x18c) == 1) {
                int cnt = *(short*)(I32(g, 0x40) - 2 + I16(g, 0x36) * 2) + 1;
                int i = 0;
                if (0 < cnt) {
                    do {
                        piVar18[i] = piVar18[i] * 3;
                        i = i + 1;
                    } while (i < cnt);
                }
            } else if (I32(t, 400) == 1) {
                int cnt = (int)*(short*)(I32(g, 0x40) - 2 + I16(g, 0x36) * 2) + 1;
                int i = 0;
                if (0 < cnt) {
                    do {
                        pY[i] = pY[i] * 3;
                        i = i + 1;
                    } while (i < cnt);
                }
            }
            bmp = FUN_008c8c30(PTR(t, 4), U16(g, 0x36), I32(g, 0x3c), I32(g, 0x40), piVar18, pY,
                               I32(g, 0x4c), param_6, I8(g, 0x34), local_24, local_20, local_1c,
                               local_40, I32(t, 0x168), I32(t, 0x194));
            int aA, aB;
            if (I32(t, 0x28) == 0) {
                aA = 0;
                aB = 0;
            } else {
                aA = I32(t, 0x20);
                aB = I32(t, 0x24);
            }
            FUN_008c9000(bmp, local_2c, (unsigned char)flags & 0x20, aB, aA, I32(t, 0x48),
                         I32(t, 0x4c), local_44);
            I32(t, 0x30) = I32(bmp, 0x28);
            I32(t, 0x10c) = I32(bmp, 0xc) - I32(bmp, 8);
            I32(t, 0x110) = I32(bmp, 0x14) - I32(bmp, 0x10);
            I32(t, 0xe0) = I32(bmp, 0x18);
            I32(t, 0xe4) = I32(bmp, 0x1c);
            I32(t, 0xfc) = I32(bmp, 0x18);
            I32(t, 0x100) = I32(bmp, 0x1c);
            I32(t, 0x114) = I32(bmp, 0x20);
            if ((unsigned char)param_6 == 0 && I32(t, 0x1c) != 0 && (flags & 0x20) == 0) {
                unsigned short uVar11 = (unsigned short)local_30;
                if (I32(bmp, 0x2214) == 0 && uVar11 < 0x800) {
                    unsigned char* pb = (unsigned char*)(((local_30 & 0xffff) >> 3) + I32(PTR(t, 0x18), 0x10));
                    *pb = *pb | (unsigned char)(1 << (local_30 & 7));
                }
                if (I32(bmp, 0x2218) == 0 && uVar11 < 0x800) {
                    unsigned char* pb = (unsigned char*)(I32(PTR(t, 0x18), 0x14) + (unsigned)(uVar11 >> 3));
                    *pb = *pb | (unsigned char)(1 << (local_30 & 7));
                }
            }
        }
        I32(t, 0x100) = I32(t, 0x100) - piVar18[n + 2];
        I32(t, 0xfc) = I32(t, 0xfc) - pY[n + 2];
        if (I32(g, 0xc) < 1) {
            I32(t, 0x118) = I32(bmp, 0x24);
            I32(bmp, 0x24) = 0;
            I32(t, 0x11c) = 0;
        }
        if (piVar18[n] != 0) {
            I32(t, 0xe4) = I32(t, 0xe4) - piVar18[n];
        }
        if (pY[n] != 0) {
            I32(t, 0xe0) = I32(t, 0xe0) - pY[n];
        }
        U32(t, 0xe4) = U32(t, 0xe4) & 0xffffffc0;
        U32(t, 0xe0) = U32(t, 0xe0) & 0xffffffc0;
        FUN_008c9a70(bmp);
    }
    if (((unsigned char)flags & 4) == 0) {
        Delete_GlyphClass(PTR(t, 0x104));
        PTR(t, 0x104) = 0;
    }
}
