// src/game/SPEngine/SPGraphicsFrustumCull.cpp -- migrated from slice(s) s006ffe00, s006ff170 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsFrustumCull.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include "SP/cFrustumCull.h"
#include <xmmintrin.h>
#include <math.h>
#include <float.h>
#include <new>
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern unsigned char g_1628c38;    // 0x1628c38 clip-disable flag
extern int  g_planeIndices[6];     // 0x1534e4c

// ---- items of slice s006ff170 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VertexCtx {
    void SubClip(float d);
    int  TestClip1(const float* a, const float* b);
    int  TestClip2(const float* p, float t);
};
// ---- items of slice s006ff170 end

// ---- items of slice s006ffe00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int            g_planeOrder[6]; // 0x1534e4c, frustum plane evaluation order
extern unsigned char  g_frustumOff;    // 0x1628c38, frustum cull disabled
void* __cdecl FUN_006ffdc0(void* dst, const void* src);          // 0x006ffdc0 4x4 transpose
void  __stdcall FUN_006ffc60(void* plane);                        // 0x006ffc60 plane bisector indices (ret 4)
namespace SP {
struct ClipPlane {
    float x, y, z, w;   // +0x00
    int   idx[6];       // +0x10
};
}
namespace SP {
struct FrustumBuilder {
    ClipPlane planes[6];
    void Build(const void* view);
};
}
namespace SP {
struct cFrustumCull_s006f_fe00 {
    ClipPlane mClipPlanes[6];
    unsigned int FrustumTestSphere(int* a, int* b, unsigned int flags);  // 0x00700120 (SP::cFrustumCull::FrustumTestSphere)
    unsigned int AltTest(int* a, int* b);   // 0x006ffaf0
};
}
// ---- items of slice s006ffe00 end

// @ 0x006ffaf0
int VertexCtx::TestClip1(const float* a, const float* b)
{
    char* self = (char*)this;
    if (g_1628c38 != 0)
        return 0x180;
    float local[6];
    local[0] = a[0];
    local[1] = a[1];
    local[2] = a[2];
    local[3] = b[0];
    local[4] = b[1];
    local[5] = b[2];
    unsigned char found = 0;
    for (unsigned off = 0; off < 0x18; off += 4) {
        int i = g_planeIndices[off / 4];
        float* pf = (float*)(self + i * 0x28);
        int i0 = *(int*)((char*)pf + 0x10);
        int i1 = *(int*)((char*)pf + 0x18);
        int i2 = *(int*)((char*)pf + 0x20);
        float dot = ((pf[2] * local[i2] + pf[1] * local[i1]) + pf[0] * local[i0]) + pf[3];
        if ((*(unsigned int*)&dot & 0x80000000) == 0) {
            found = 1;
            break;
        }
    }
    return (-(unsigned)(found != 0) & 0xfffffec0) + 0x180;
}

// @ 0x006ffbd0
int VertexCtx::TestClip2(const float* p, float t)
{
    char* self = (char*)this;
    if (g_1628c38 != 0)
        return 0x180;
    float x = p[0];
    float y = p[1];
    float z = p[2];
    unsigned char found = 0;
    for (unsigned off = 0; off < 0x18; off += 4) {
        int i = g_planeIndices[off / 4];
        float* pf = (float*)(self + i * 0x28);
        float dot = ((pf[2] * z + pf[1] * y) + pf[0] * x) + pf[3];
        if (dot >= t) {
            found = 1;
            break;
        }
    }
    return (-(unsigned)(found != 0) & 0xfffffec0) + 0x180;
}

// @ 0x006ffc60
void __stdcall FUN_006ffc60(int* p)
{
    float* pf = (float*)p;
    unsigned int mask = 0;
    if (0.0f <= pf[0]) mask |= 1;
    if (0.0f <= pf[1]) mask |= 2;
    if (0.0f <= pf[2]) mask |= 4;
    switch (mask) {
    case 0: p[4]=3; p[5]=0; p[6]=4; p[7]=1; p[8]=5; p[9]=2; break;
    case 1: p[4]=0; p[5]=3; p[6]=4; p[7]=1; p[8]=5; p[9]=2; break;
    case 2: p[4]=3; p[5]=0; p[6]=1; p[7]=4; p[8]=5; p[9]=2; break;
    case 3: p[4]=0; p[5]=3; p[6]=1; p[7]=4; p[8]=5; p[9]=2; break;
    case 4: p[4]=3; p[5]=0; p[6]=4; p[7]=1; p[8]=2; p[9]=5; break;
    case 5: p[4]=0; p[5]=3; p[6]=4; p[7]=1; p[8]=2; p[9]=5; break;
    case 6: p[4]=3; p[5]=0; p[6]=1; p[7]=4; p[8]=2; p[9]=5; break;
    case 7: p[4]=0; p[5]=3; p[6]=1; p[7]=4; p[8]=2; p[9]=5; break;
    }
}

// @ 0x006ffdc0
float* __cdecl FUN_006ffdc0(float* dst, const float* src)
{
    float* d = dst;
    const float* s = src;
    int n = 4;
    do {
        d[0] = s[0];
        d[1] = s[4];
        d[2] = s[8];
        d[3] = s[12];
        ++s;
        d += 4;
    } while (--n);
    return dst;
}

// @ 0x006ffe00
void SP::FrustumBuilder::Build(const void* view)
{
    float tmp[16];
    float m[16];
    memcpy(m, FUN_006ffdc0(tmp, view), 64);

    planes[0].x = -(m[0] + m[12]);
    planes[0].y = -(m[1] + m[13]);
    planes[0].z = -(m[2] + m[14]);
    planes[0].w = -(m[3] + m[15]);
    planes[1].x = -(m[12] - m[0]);
    planes[1].y = -(m[13] - m[1]);
    planes[1].z = -(m[14] - m[2]);
    planes[1].w = -(m[15] - m[3]);
    planes[2].x = -(m[12] - m[4]);
    planes[2].y = -(m[13] - m[5]);
    planes[2].z = -(m[14] - m[6]);
    planes[2].w = -(m[15] - m[7]);
    planes[3].x = -(m[4] + m[12]);
    planes[3].y = -(m[5] + m[13]);
    planes[3].z = -(m[6] + m[14]);
    planes[3].w = -(m[7] + m[15]);
    planes[4].x = -m[8];
    planes[4].y = -m[9];
    planes[4].z = -m[10];
    planes[4].w = -m[11];
    planes[5].x = -(m[12] - m[8]);
    planes[5].y = -(m[13] - m[9]);
    planes[5].z = -(m[14] - m[10]);
    planes[5].w = -(m[15] - m[11]);

    const float kOne = 1.0f;
    for (int i = 0; i < 6; i++) {
        ClipPlane* p = &planes[i];
        float x = p->x, y = p->y, z = p->z;
        float len2 = x * x;
        len2 += y * y;
        len2 += z * z;
        float s = kOne / sqrtf(len2);
        p->x = x * s;
        p->y = y * s;
        p->z = z * s;
        p->w *= s;
        FUN_006ffc60(p);
    }
}

// @ 0x00700120
unsigned int SP::cFrustumCull_s006f_fe00::FrustumTestSphere(int* a, int* b, unsigned int flags)
{
    if (flags & 0x200)
        return AltTest(a, b);
    if (g_frustumOff != 0)
        return 0x13f;

    int bits[6];
    bits[0] = a[0];
    bits[1] = a[1];
    bits[2] = a[2];
    bits[3] = b[0];
    bits[4] = b[1];
    bits[5] = b[2];
    float* pts = (float*)bits;
    flags &= ~0x100u;

    for (unsigned off = 0; off < 0x18; off += 4) {
        int pi = *(int*)((char*)g_planeOrder + off);
        unsigned int bit = 1u << pi;
        if ((flags & bit) != 0)
            continue;
        const ClipPlane* p = &mClipPlanes[pi];
        float f1 = p->x;
        float f2 = p->y;
        float f3 = p->z;
        float f4 = p->w;
        float d0 = f1 * pts[p->idx[0]] + f2 * pts[p->idx[2]] +
                   f3 * pts[p->idx[4]] + f4;
        if ((*(unsigned int*)&d0 & 0x80000000u) == 0) {
            flags |= 0x7f;
            break;
        }
        float d1 = f1 * pts[p->idx[1]] + f2 * pts[p->idx[3]] +
                   f3 * pts[p->idx[5]] + f4;
        if ((*(unsigned int*)&d1 & 0x80000000u) == 0)
            flags |= 0x100;
        else
            flags |= bit;
    }
    if ((flags & 0x140u) == 0)
        flags |= 0x80;
    return flags;
}
