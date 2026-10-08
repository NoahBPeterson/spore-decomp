// Slice s00f8de70: bilinear sample of a cube-map face image (one byte per texel).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {
int __cdecl WrapCubeFace(int n, int* face, int* x, int* y, int a, int b);  // 0x00684ca0
}

static __forceinline int CeilishFloor(float v)
{
    int i;
    __asm {
        movss    xmm0, v
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
        mov      i, eax
    }
    return i;
}

struct CubeUV {
    float u, v;
    int face;
};

struct Corner { int face, y, x; };

struct CubeImage {
    char pad0[8];
    unsigned mSize;       // +8
    char pad1[4];
    unsigned char* mData; // +0x10

    float Sample(const CubeUV* p);   // @ 0x00f8de70
};

#define TEXEL(F, Y, X) ((float)mData[((F) * (int)mSize + (Y)) * (int)mSize + (X)])
#define OUT(Y, X) ((((unsigned)(Y) | (unsigned)(X)) & ~(mSize - 1)) != 0)

float CubeImage::Sample(const CubeUV* p)
{
    int f3 = p->face;
    float fn = (float)mSize;
    float fx = fn * p->u - 0.5f;
    float fy = p->v * fn - 0.5f;
    int x0 = CeilishFloor(fx);
    int y0 = CeilishFloor(fy);
    int x1 = x0 + 1;
    int y1 = y0 + 1;
    unsigned mask = ~(mSize - 1);
    float fu = fx - (float)x0;
    float fv = fy - (float)y0;

    // corner 0 = (x0,y0), 1 = (x1,y0), 2 = (x0,y1), 3 = (x1,y1)
    Corner c[4];
    c[0].face = f3; c[0].x = x0; c[0].y = y0;
    c[1].face = f3; c[1].x = x1; c[1].y = y0;
    c[2].face = f3; c[2].x = x0; c[2].y = y1;
    c[3].face = f3; c[3].x = x1; c[3].y = y1;

    float v0, v1, v2, v3;
    unsigned sel = ((((unsigned)(y1 | x1) & mask) != 0) ? 8U : 0U) + (((unsigned)(y0 | x0) & mask) != 0)
                 + ((((unsigned)(y1 | x0) & mask) != 0) ? 4U : 0U) + ((((unsigned)(y0 | x1) & mask) != 0) ? 2U : 0U);
    switch (sel) {
    case 0:
        v0 = TEXEL(f3, y0, x0);
        v1 = TEXEL(f3, y0, x1);
        v2 = TEXEL(f3, y1, x0);
        v3 = TEXEL(f3, y1, x1);
        break;
    default:
        return 0.0f;
    case 3:
        if (OUT(c[0].y, c[0].x)) SP::WrapCubeFace(mSize, &c[0].face, &c[0].x, &c[0].y, 0, 0);
        if (OUT(c[1].y, c[1].x)) SP::WrapCubeFace(mSize, &c[1].face, &c[1].x, &c[1].y, 0, 0);
        goto fetch;
    case 5:
        if (OUT(c[0].y, c[0].x)) SP::WrapCubeFace(mSize, &c[0].face, &c[0].x, &c[0].y, 0, 0);
        if (OUT(c[2].y, c[2].x)) SP::WrapCubeFace(mSize, &c[2].face, &c[2].x, &c[2].y, 0, 0);
        goto fetch;
    case 10:
        if (OUT(c[1].y, c[1].x)) SP::WrapCubeFace(mSize, &c[1].face, &c[1].x, &c[1].y, 0, 0);
        goto fetch3;
    case 12:
        if (OUT(c[2].y, c[2].x)) SP::WrapCubeFace(mSize, &c[2].face, &c[2].x, &c[2].y, 0, 0);
    fetch3:
        if (OUT(c[3].y, c[3].x)) SP::WrapCubeFace(mSize, &c[3].face, &c[3].x, &c[3].y, 0, 0);
    fetch:
        v0 = TEXEL(c[0].face, c[0].y, c[0].x);
        v1 = TEXEL(c[1].face, c[1].y, c[1].x);
        v2 = TEXEL(c[2].face, c[2].y, c[2].x);
        v3 = TEXEL(c[3].face, c[3].y, c[3].x);
        break;
    case 7:   // corners 0,1,2 outside: corner 3 is read directly
        v3 = TEXEL(c[3].face, c[3].y, c[3].x);
        if (OUT(c[1].y, c[1].x)) SP::WrapCubeFace(mSize, &c[1].face, &c[1].x, &c[1].y, 0, 0);
        if (OUT(c[2].y, c[2].x)) SP::WrapCubeFace(mSize, &c[2].face, &c[2].x, &c[2].y, 0, 0);
        v1 = TEXEL(c[1].face, c[1].y, c[1].x);
        v2 = TEXEL(c[2].face, c[2].y, c[2].x);
        v0 = ((v3 + v2) + v1) * 0.33333334f;
        break;
    case 11:  // corners 0,1,3 outside: corner 2 is read directly
        v2 = TEXEL(f3, c[2].y, c[2].x);
        if (OUT(c[0].y, c[0].x)) SP::WrapCubeFace(mSize, &c[0].face, &c[0].x, &c[0].y, 0, 0);
        if (OUT(c[3].y, c[3].x)) SP::WrapCubeFace(mSize, &c[3].face, &c[3].x, &c[3].y, 0, 0);
        v3 = TEXEL(c[3].face, c[3].y, c[3].x);
        v0 = TEXEL(c[0].face, c[0].y, c[0].x);
        v1 = ((v3 + v2) + v0) * 0.33333334f;
        break;
    case 13:  // corners 0,2,3 outside: corner 1 is read directly
        v1 = TEXEL(f3, c[1].y, c[1].x);
        if (OUT(c[0].y, c[0].x)) SP::WrapCubeFace(mSize, &c[0].face, &c[0].x, &c[0].y, 0, 0);
        if (OUT(c[3].y, c[3].x)) SP::WrapCubeFace(mSize, &c[3].face, &c[3].x, &c[3].y, 0, 0);
        v3 = TEXEL(c[3].face, c[3].y, c[3].x);
        v0 = TEXEL(c[0].face, c[0].y, c[0].x);
        v2 = ((v3 + v1) + v0) * 0.33333334f;
        break;
    case 14:  // corners 1,2,3 outside: corner 0 is read directly
        v0 = TEXEL(f3, c[0].y, c[0].x);
        if (OUT(c[1].y, c[1].x)) SP::WrapCubeFace(mSize, &c[1].face, &c[1].x, &c[1].y, 0, 0);
        if (OUT(c[2].y, c[2].x)) SP::WrapCubeFace(mSize, &c[2].face, &c[2].x, &c[2].y, 0, 0);
        v2 = TEXEL(c[2].face, c[2].y, c[2].x);
        v1 = TEXEL(c[1].face, c[1].y, c[1].x);
        v3 = ((v2 + v1) + v0) * 0.33333334f;
        break;
    }
    double a = fu;
    double b = fv;
    return (float)(((((1.0 - a) * v2 + v3 * a) * b) + ((v1 * a + (1.0 - a) * v0) * (1.0 - b))) * 0.003921569f);
}
