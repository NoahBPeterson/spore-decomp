// Slice s008bfc10: T2K (Type 2000 font scaler) T2K_NewTransformation @ 0x008c0000.
// The T2K struct layout is not recovered, so fields are accessed by raw offset through macros
// (same style as slice s008c0760).  Module flags: /O2 /MD /Gy /TP.
// The function calls setjmp, so cl keeps most locals in memory.
#include "types.h"
#include <setjmp.h>
#include <string.h>

#define I32(p, o) (*(int*)((char*)(p) + (o)))
#define U32(p, o) (*(unsigned*)((char*)(p) + (o)))
#define I16(p, o) (*(short*)((char*)(p) + (o)))
#define U16(p, o) (*(unsigned short*)((char*)(p) + (o)))
#define I8(p, o) (*(char*)((char*)(p) + (o)))
#define PTR(p, o) (*(char**)((char*)(p) + (o)))

extern "C" {
void tsi_Error(void* mem, int code);                              // 0x008d10c0
void tsi_EmergencyShutDown(void* mem);                            // 0x008d1210
void* tsi_AllocMem(void* mem, int size);                          // 0x008d1260
int util_FixMul(int a, int b);                                    // 0x008d1590
int util_FixDiv(int a, int b);                                    // 0x008d16d0
int util_EuclidianDistance(int a, int b);                         // 0x008d17d0
unsigned short GetUPEM(void* sfnt);                               // 0x008ceb70
int GetNumGlyphs_sfntClass(void* sfnt);                           // 0x008cef90
void setT2KScaleFactors(int ppem, int upem, void* out);           // 0x008cd1b0
void GetFontWideSbitMetrics(void* a, void* b, int xppem, int yppem, void* hor, void* ver);   // 0x008c4f40
void FUN_008cf460(void* sfnt, void* hor, void* ver);              // 0x008cf460
void FUN_008ccbb0(void* a, int b, int c);                         // 0x008ccbb0
void T2K_TransformXFunits(void* t, short units, int* outScaled, int* outRounded);   // 0x008bfdb0
void T2K_TransformYFunits(void* t, short units, int* outScaled, int* outRounded);   // 0x008bfe10
}

// Same-TU static helpers: cl gives them register calling conventions, as in the original.

// 0x008bfc10: register arg esi = t.  Pushes the new ppem size to the hinting object when it changed.
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

// 0x008bfd50: register args ecx = t, eax = matrix.
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

// 0x008bf2b0: register args eax = glyph count, edi = mem.  Allocates the 0x18-byte bitmap-size cache.
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

// 0x008bfe80: register args esi = matrix, edi = sfnt.  Concatenates the font's own matrices
// (sfnt +0x20 / +0x24 sub-objects) onto the caller's 2x2 16.16 matrix.
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

// Font-wide bitmap metrics block (0x18 bytes) filled by GetFontWideSbitMetrics / FUN_008cf460.
struct FontWideMetrics {
    int valid;                      // +0
    short a, b;                     // +4  (T2K 26.6 values)
    short c; unsigned short d;      // +8
    int e, f;                       // +0xc, +0x10
    short g, h;                     // +0x14
};

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
