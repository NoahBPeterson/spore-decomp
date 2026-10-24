// Slice s006ffe00: frustum/spatial-cell helpers (bit-pack/unpack) and small vector/accessor
// routines. Region 0x6ffe00-0x700d80. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-.
#include "types.h"
#include <xmmintrin.h>
#include <math.h>

// ---- external callees -------------------------------------------------------------------
void* __cdecl FUN_011e073e(void* p, int a, unsigned size);
void  __cdecl FUN_006ec4a0(void* pos, const void* v);
void  __cdecl FUN_00f47410(int a);
void  __cdecl FUN_00762a00(int a);
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380

// ---- globals ----------------------------------------------------------------------------
extern unsigned short g_cellTable[];   // 0x15352a8, 32 ushort entries

// @ 0x006ffe00  -- spatial query (stub, see partial.txt)
void __cdecl FUN_006ffe00(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }

// @ 0x00700120  -- SP::cFrustumCull::FrustumTestSphere (stub, see partial.txt)
int __cdecl FUN_00700120(void* a, void* b, void* c) { (void)a; (void)b; (void)c; return 0; }

// cell record copy (a POD 0xa0-byte record memcpy)
struct SpCellRecord {
    int     m00[3];     // +0x00
    __m128  m10;        // +0x10  (16-byte aligned -> 4-byte hole at +0x0c)
    int     m20[6];     // +0x20
    uint8_t m38[4];     // +0x38
    int     m3c[3];     // +0x3c  (8-byte hole at +0x48)
    __m128  m50;        // +0x50
    __m128  m60;        // +0x60
    __m128  m70;        // +0x70
    __m128  m80;        // +0x80
    int     m90[3];     // +0x90  (4-byte tail pad to +0xa0)
    SpCellRecord(const SpCellRecord& o);
};
// @ 0x00700290
SpCellRecord::SpCellRecord(const SpCellRecord& o) {
    m00[0] = o.m00[0]; m00[1] = o.m00[1]; m00[2] = o.m00[2];
    m10 = o.m10;
    m20[0] = o.m20[0]; m20[1] = o.m20[1]; m20[2] = o.m20[2];
    m20[3] = o.m20[3]; m20[4] = o.m20[4]; m20[5] = o.m20[5];
    m38[0] = o.m38[0]; m38[1] = o.m38[1]; m38[2] = o.m38[2]; m38[3] = o.m38[3];
    m3c[0] = o.m3c[0]; m3c[1] = o.m3c[1]; m3c[2] = o.m3c[2];
    m50 = o.m50; m60 = o.m60; m70 = o.m70; m80 = o.m80;
    m90[0] = o.m90[0]; m90[1] = o.m90[1]; m90[2] = o.m90[2];
}

// @ 0x00700360
struct CellAccessor {
    char pad[8];
    int  f8;   // +0x08
    int  fc;   // +0x0c
    int Get(int* out);
};
int CellAccessor::Get(int* out) {
    if (out)
        *out = fc;
    return f8;
}

// @ 0x007003a0  -- cell array constructor (stub, see partial.txt)
void* __cdecl FUN_007003a0(void* a, void* b, unsigned c) { (void)a; (void)b; (void)c; return a; }

// @ 0x00700450  -- scalar deleting destructor (stub, see partial.txt)
void* __cdecl FUN_00700450(void* a, unsigned b) { (void)a; (void)b; return a; }

// @ 0x007004d0  -- cPropertyList destructor (stub, see partial.txt)
void* __cdecl FUN_007004d0(void* a, unsigned b) { (void)a; (void)b; return a; }

// @ 0x00700640
struct Vec4b {
    int* begin;   // +0x00
    int* end;     // +0x04
    int* cap;     // +0x08
    void PushBack(const int* v);
    void Grow(void* pos, const void* v);
};
void Vec4b::PushBack(const int* v) {
    int* old = end;
    if (old < cap) {
        end = old + 1;
        if (old)
            *old = *v;
    } else {
        Grow(old, v);
    }
}

// @ 0x007006d0  -- vector release/reset (stub, see partial.txt)
void __cdecl FUN_007006d0(void* a) { (void)a; }

// @ 0x00700a30  -- spatial cell pack (stub, see partial.txt)
void __cdecl FUN_00700a30(void* a, void* b) { (void)a; (void)b; }

namespace {

// @ 0x00700b70
void GetParentChildInfo(unsigned a, unsigned* p2, unsigned* p3) {
    *p3 = (((a >> 9) & 0x800) | (a & 0x400)) >> 9 | (a & 1);
    *p2 = (a >> 1) & 0x7ff7fdff;
}

// @ 0x00700bb0
void ChildCellIDs(unsigned a, int* p) {
    int v = (int)(a & 0xfff7fdff) * 2;
    p[0] = v;
    p[1] = v + 1;
    p[2] = v + 0x400;
    p[3] = v + 0x401;
    p[4] = v + 0x100000;
    p[5] = v + 0x100001;
    p[6] = v + 0x100400;
    p[7] = v + 0x100401;
}
} // namespace

// @ 0x00700c00
unsigned int __cdecl FUN_00700c00(unsigned int a) {
    unsigned int hi = a >> 20;
    unsigned int mid = a >> 10;
    return (((((g_cellTable[(hi >> 5) & 0x1f] * 2 | g_cellTable[(mid >> 5) & 0x1f]) * 2 |
               g_cellTable[(a >> 5) & 0x1f]) << 13 | g_cellTable[hi & 0x1f]) * 2 |
             g_cellTable[mid & 0x1f]) * 2) | g_cellTable[a & 0x1f];
}

// @ 0x00700c80
bool __cdecl FUN_00700c80(const float* a, const float* b, const float* c, float r, float* out) {
    float dx = b[0] - a[0];
    float dy = b[1] - a[1];
    float dz = b[2] - a[2];
    float ex = a[0] - c[0];
    float ey = a[1] - c[1];
    float ez = a[2] - c[2];
    float len2 = dx * dx + dy * dy + dz * dz;
    float dot  = dx * ex + dy * ey + dz * ez;
    float elen = ex * ex + ey * ey + ez * ez;
    float disc = dot * dot - (elen - r * r) * len2;
    if (0.0f > disc) return false;
    float root = sqrtf(disc);
    float t1 = -dot - root;
    if (0.0f > root - dot) return false;
    if (t1 > len2) return false;
    if (out != 0) {
        if (!(t1 <= 0.0f)) *out = t1 / len2;
        else               *out = 0.0f;
    }
    return true;
}
