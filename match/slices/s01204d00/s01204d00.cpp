// Slice s01204d00 (batch gold4) -- SP volume/segment geometry + placement helpers
// (rwcVolume relocate/init wrappers, vertex-grid emit loops, slab/sphere
// intersection, and the shape-bounds padding helpers).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// The two big functions (0x01204d00 / 0x012051f0) are the vertex-emit kernels of
// the procedural volume generator: they transform a batch of grid vertices by a
// float4x4, test them against the volume's bounding slab and push accepted
// vertices into a growable pool.  The pool header is a 6-dword block populated by
// 0x012055f0 from the (w,h,depth,cells) counts.
//
// Field map for the generator context (param_1) and the work object (param_2):
//   ctx +0x24 byte  material id
//   ctx +0x34/+0x38 vertex table begin / element stride table
//   ctx +0x3c       volume instance (thiscall target for the sub-generators)
//   ctx +0x40       bitfield table for per-vertex material tags
//   work +0x04      grid base
//   work +0x14/+0x18 cursor / end for the emit loop
//   work +0x24..+0x38  the 4x4 object-to-world scale/translate rows
//   work +0xd0..+0xe8  second slab state (0x012051f0)
//   work +0xf0/+0xec/+0xdc/+0xd8  stride / frame counters

#include "types.h"

typedef unsigned int uint;
typedef unsigned char uint8;

#include <xmmintrin.h>

// ------------------------------------------------------------------ callees
extern "C" {
unsigned int DAT_01485720;                  // 0x01485720  float 1.0f
unsigned int DAT_013eb1bc;                  // 0x013eb1bc  float constant
unsigned int DAT_0171e598;                  // 0x0171e598  volume vtable slot
unsigned int DAT_0171e59c;                  // 0x0171e59c
unsigned int DAT_0171e5a0;                  // 0x0171e5a0
unsigned int DAT_0171e5a4;                  // 0x0171e5a4
unsigned int DAT_0171e5a8;                  // 0x0171e5a8
unsigned int DAT_0171e5ac;                  // 0x0171e5ac
unsigned int DAT_015d0a7c;                  // 0x015d0a7c  vtable anchor
unsigned int DAT_015d0abc, DAT_015d0a98, DAT_015d0a58, DAT_015d0b04, DAT_015d0ae0;

unsigned int FUN_01204380(uint* out);                 // 0x01204380  next vertex index
int          FUN_01201a20(void* v, void* a, void* b, void* c, void* d, void* e);  // 0x01201a20
int          FUN_01202260(void* a, void* b, void* c, void* d);   // 0x01202260
void         FUN_01204420(int a);                     // 0x01204420
int          FUN_01204c60(void* a, void* b, void* c); // 0x01204c60
void         FUN_01202020(void* a, int b);            // 0x01202020
int          FUN_012045a0(uint* out);                 // 0x012045a0
void*        FUN_01204780(void* a, void* b);          // 0x01204780
int          FUN_01204620(void* a, void* b);          // 0x01204620
void         FUN_01203fc0(void* a, void* b, void* c, unsigned int d, int e);   // 0x01203fc0
void*        FUN_012016f0(void* a, void* b);          // 0x012016f0  SP::Segment::Segment
void         FUN_012070e0(void* a, void* b);          // 0x012070e0  rwcVolumeInstanceInitialize
void         FUN_012070a0(void* a, void* b);          // 0x012070a0  rwcVolumeRelocateReturnSecond
void         FUN_012070c0(void* a, void* b, void* c); // 0x012070c0  thunk_FUN_011fb220
void         FUN_01207110(void* a, void* b, void* c); // 0x01207110  rwcVolumeRelocateFixupNoOp
int          FUN_012070d0(void* a, void* b);          // 0x012070d0  thunk_FUN_012057f0
void         FUN_01207140(void* a, void* b);          // 0x01207140  rwcVolumeRelocateFixupReturnOne
int          FUN_01205a30(float* a, float* b, float* c, float* d, float* e,
                          float f, float g, int h, int i);   // 0x01205a30
unsigned int* FUN_012055f0(unsigned int* pool, int w, int h, int depth, int self, int a2, int a5);
}

// ------------------------------------------------------------------ helpers
extern "C" float __cdecl sqrtf(float x);
static inline float Sqrtf(float x) { return sqrtf(x); }

// 16-byte vector: the sweep kernel reads vertex/plane data as float4 blocks and
// uses packed SSE dot products, so the source aggregates must have this shape.
struct vec4 { float x, y, z, w; };
static inline float dot4(const vec4& a, const vec4& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
// The retail slab kernels clear the sign bit with an integer AND (0x7fffffff),
// not a compare/negate branch, so mirror that exactly.
static inline float fabsf_(float v)
{
    unsigned int b = *(unsigned int*)&v;
    b &= 0x7fffffffu;
    return *(float*)&b;
}

// Packed form: the retail code materialises the products with mulps and does the
// horizontal sum with shufps/addps, which is what MSVC emits for __m128 math.
static inline __m128 vload(const float* p) { return *(__m128 const*)p; }
static inline float vdot(const float* a, const float* b)
{
    __m128 va = vload(a);
    __m128 vb = vload(b);
    __m128 p = _mm_mul_ps(vb, va);
    __m128 s1 = _mm_shuffle_ps(p, p, 2);
    __m128 s2 = _mm_shuffle_ps(p, p, 1);
    s1 = _mm_add_ps(s2, s1);
    p = _mm_add_ps(p, s1);
    __m128 r = _mm_shuffle_ps(p, p, 0);
    return ((float*)&r)[0];
}
// cross(a, b) exactly as the retail kernel builds it:
//   shuffle(a,9)*shuffle(b,0x12) - shuffle(b,9)*shuffle(a,0x12)
static inline __m128 vcross(__m128 a, __m128 b)
{
    __m128 a9  = _mm_shuffle_ps(a, a, 0x9);
    __m128 a12 = _mm_shuffle_ps(a, a, 0x12);
    __m128 b9  = _mm_shuffle_ps(b, b, 0x9);
    __m128 b12 = _mm_shuffle_ps(b, b, 0x12);
    return _mm_sub_ps(_mm_mul_ps(a9, b12), _mm_mul_ps(b9, a12));
}
static inline float vhsum(__m128 p)
{
    __m128 s1 = _mm_shuffle_ps(p, p, 2);
    __m128 s2 = _mm_shuffle_ps(p, p, 1);
    s1 = _mm_add_ps(s2, s1);
    p = _mm_add_ps(p, s1);
    __m128 r = _mm_shuffle_ps(p, p, 0);
    return ((float*)&r)[0];
}
// Inline x87 square root: the retail kernel uses fsqrt, not a library sqrtf call.
static inline float fsqrt_x87(float x)
{
    __asm { fld x }
    __asm { fsqrt }
    __asm { fstp x }
    return x;
}

// Float4 vector helpers: the generator works on 16-byte float4 columns.
static inline void vsplat(float* d, float f) { d[0] = d[1] = d[2] = d[3] = f; }

// ================================================================== 0x01204d00
// int __thiscall FUN_01204d00(void* ctx, int* work, float* xf)   [ret 8]
//   Generate one grid batch: transform every vertex by `xf`, keep the ones
//   inside the volume slab, and emit them through 0x01202260.
// @ 0x01204d00
struct SweepCtx {
    int Generate(int* work, float* xf);   // 0x01204d00  ecx = this
};
int SweepCtx::Generate(int* work, float* xf)
{
    void* ctx = (void*)this;
    float* pf = (float*)ctx;
    // Object-to-world columns lifted from the work object.
    float m0[4] = { pf[(0x20 >> 2)], 0, 0, 0 };  (void)m0;
    float o0 = ((float*)work)[8];
    float o1 = ((float*)work)[9];
    float o2 = ((float*)work)[10];
    float t0 = ((float*)work)[12];
    float t1 = ((float*)work)[13];
    float t2 = ((float*)work)[14];
    (void)o0; (void)o1; (void)o2; (void)t0; (void)t1; (void)t2;

    // ---- transform the two corner points (min/max) by the 4x4 `xf` ----
    float m00 = xf[0],  m01 = xf[1],  m02 = xf[2];
    float m10 = xf[4],  m11 = xf[5],  m12 = xf[6];
    float m20 = xf[8],  m21 = xf[9],  m22 = xf[10];
    float m30 = xf[12], m31 = xf[13], m32 = xf[14];

    float a0 = xf[0] - xf[4], b0 = xf[4], c0 = xf[8];  (void)a0; (void)b0; (void)c0;

    // corner A (column 0) and corner B (column 1) of the sweep box
    float cA[4], cB[4];
    cA[0] = (m00) ; cA[1] = (m01); cA[2] = (m02); cA[3] = 1.0f;
    cB[0] = (m10) ; cB[1] = (m11); cB[2] = (m12); cB[3] = 1.0f;
    (void)c0;

    // subtract: delta = cornerB - cornerA (column-wise), then length^2 pieces
    float dx0 = m10 - m00, dx1 = m11 - m01, dx2 = m12 - m02;
    float len2 = dx0 * dx0 + dx1 * dx1 + dx2 * dx2;
    (void)len2;
    (void)m20; (void)m21; (void)m22; (void)m30; (void)m31; (void)m32;
    (void)cA; (void)cB;

    float minp[4], maxp[4];
    vsplat(minp, 0.0f);
    vsplat(maxp, 0.0f);
    (void)minp; (void)maxp;

    if (work[0x3e] == 0) {
        if (work[0x3d] == 0)
            work[0x3e] = 0;
        else
            work[0x3e] = FUN_01204c60(*(void**)((char*)ctx + 0x3c), minp, maxp);
    }
    if (work[0x40] != 0)
        FUN_01204420(work[0x3f]);

    while ((uint)work[5] < (uint)work[6] && (uint)work[0x3a] < (uint)work[0x3b]) {
        uint idx;
        int ok = FUN_01204380(&idx);
        if (ok == 0)
            return 1;
        // vertex stride records: 3 int indices + 1 extra, one per 0x10 bytes
        int* vrec = (int*)(work[5] * 0xd0 + work[4]);
        int vt = *(int*)((char*)ctx + 0x38);
        int* rec = (int*)(idx * 0x10 + *(int*)((char*)ctx + 0x34));
        float* p0 = (float*)(rec[0] * 0x10 + vt);
        float* p1 = (float*)(rec[1] * 0x10 + vt);
        float* p2 = (float*)(rec[2] * 0x10 + vt);
        if (FUN_01201a20(vrec, xf, &dx0, p0, p1, p2) != 0) {
            work[5] = work[5] + 1;
            float frame = (float)(work[0x3a] * 0x60 + work[0x39]);
            work[0x3a] = work[0x3a] + 1;
            (void)frame;
            int node = FUN_01202260(p0, p1, p2, 0);
            *(int*)(node + 0x54) = rec[3];
            *(int*)(node + 0x58) = rec[3];
            *(uint*)(node + 0x44) =
                *(uint*)(*(int*)((char*)ctx + 0x40) + (idx >> 3) * 4) >> ((idx & 7) << 2) & 0xf;
            if (work[0x40] != 0 &&
                (float)vrec[0x10] <= (float)work[0x3f] &&
                (float)work[0x3f] != (float)vrec[0x10]) {
                int a = vrec[0x10];
                work[0x3f] = a;
                FUN_01204420(a);
            }
            *vrec = *(int*)(*work + -4 + work[3] * 4);
            vrec[0x14] = node;
            for (int i = 0; i < 4; ++i) {
                vrec[0x18 + i * 4 + 0] = (int)xf[i * 4 + 0];
                vrec[0x18 + i * 4 + 1] = (int)xf[i * 4 + 1];
                vrec[0x18 + i * 4 + 2] = (int)xf[i * 4 + 2];
                vrec[0x18 + i * 4 + 3] = (int)xf[i * 4 + 3];
            }
            vrec[0x15] = (int)(vrec + 0x18);
            FUN_01202020(vrec + 8, 0);
            vrec[0x30] = (int)((uint)(idx + 1) << (*(uint8*)((char*)work + 0x42) & 0x1f)
                                | (uint)work[0x41]);
            *(uint8*)(vrec + 0x31) = (uint8)(*(uint8*)((char*)ctx + 0x24)
                                             + (uint8)work[0x42]);
        }
    }
    return 0;
}

// ================================================================== 0x012051f0
// int __thiscall FUN_012051f0(void* ctx, int work, float* xf)   [ret 8]
// @ 0x012051f0
struct SweepCtx2 {
    int GeneratePre(int work, float* xf);   // 0x012051f0  ecx = this
};
int SweepCtx2::GeneratePre(int work, float* xf)
{
    void* ctx = (void*)this;
    float* pxf = xf;
    if (*(int*)(work + 0xe8) == 0) {
        int src;
        if (xf == 0) {
            src = work + 0x10;
        } else {
            src = 0;
            (void)src;
        }
        if (*(int*)(work + 0xe4) == 0)
            *(int*)(work + 0xe8) = 0;
        else
            *(int*)(work + 0xe8) = FUN_01204620(*(void**)((char*)ctx + 0x3c), (void*)src);
    }

    *(int*)(work + 0xd8) = 0;
    *(int*)(work + 0xcc) = 0;
    while (*(uint*)(work + 0xd8) < *(uint*)(work + 0xdc) &&
           *(uint*)(work + 0xcc) < *(uint*)(work + 0xd0)) {
        uint idx;
        int ok = FUN_012045a0(&idx);
        if (ok == 0)
            return 1;
        int vt = *(int*)((char*)ctx + 0x38);
        int* rec = (int*)(idx * 0x10 + *(int*)((char*)ctx + 0x34));
        float* p0 = (float*)(rec[0] * 0x10 + vt);
        float* p1 = (float*)(rec[1] * 0x10 + vt);
        float* p2 = (float*)(rec[2] * 0x10 + vt);

        float minx = p0[0] < p1[0] ? p0[0] : p1[0];
        float maxx = p0[0] > p1[0] ? p0[0] : p1[0];
        float miny = p0[1] < p1[1] ? p0[1] : p1[1];
        float maxy = p0[1] > p1[1] ? p0[1] : p1[1];
        float minz = p0[2] < p1[2] ? p0[2] : p1[2];
        float maxz = p0[2] > p1[2] ? p0[2] : p1[2];
        (void)miny; (void)maxy; (void)minz; (void)maxz; (void)minx; (void)maxx;

        float frame = (float)(*(int*)(work + 0xd8) * 0x60 + *(int*)(work + 0xd4));
        *(int*)(work + 0xd8) = *(int*)(work + 0xd8) + 1;
        int node = FUN_01202260(p0, p1, p2, 0);
        *(int*)(node + 0x54) = rec[3];
        *(int*)(node + 0x58) = rec[3];
        *(uint*)(node + 0x44) =
            *(uint*)(*(int*)((char*)ctx + 0x40) + (idx >> 3) * 4) >> ((idx & 7) << 2) & 0xf;
        FUN_01203fc0((void*)node, pxf, &frame,
                     (uint)(idx + 1) << (*(uint8*)(work + 0xf0) & 0x1f) | *(uint*)(work + 0xec),
                     *(uint8*)((char*)ctx + 0x24) + *(uint8*)(work + 0xf0));
    }
    return 0;
}

// ================================================================== 0x012055f0
// @ 0x012055f0
// 0x012055f0 FUN_012055f0   (retail: unsigned int* FUN_012055f0(pool,w,h,depth,self,a2,a5))
__declspec(noinline) unsigned int* FUN_012055f0(unsigned int* pool, int w, int h, int depth, int self, int a2, int a5) {
    (void)self; (void)a2; (void)a5;
    pool[1] = 1;
    pool[3] = 1;
    pool[0] = 0;
    pool[2] = 0;
    pool[5] = 1;
    pool[4] = 0;
    pool[7] = 1;
    pool[6] = 0;
    pool[0] = (int)((((uint)(h + 7) >> 3) + 0x14 + (uint)(w + h) * 4) * 4 + 0xf & 0xfffffff0u)
              + depth * 0x20 + 0x30;
    pool[1] = 0x10;
    return pool;
}

// ================================================================== 0x01205670
// int __thiscall FUN_01205670(void* self)
// @ 0x01205670
struct VolPoolSizer {
    unsigned int Size();        // 0x01205670  ecx = this
};
unsigned int VolPoolSizer::Size()
{
    char* s = (char*)this;
    unsigned int hdr[8];
    int a5 = *(int*)(s + 0x20);
    int depth = *(int*)(*(int*)(s + 0x3c) + 4);
    unsigned int* r = FUN_012055f0(hdr, *(int*)(s + 0x30), *(int*)(s + 0x28),
                 depth, (int)this, a5, 0x50);
    return (int)*r;
}

// ================================================================== 0x012056a0
// void FUN_012056a0(void* a, void* b)
// @ 0x012056a0
void FUN_012056a0(int a, int b)
{
    FUN_012070e0(*(void**)(a + 0x3c), (void*)b);
    int d = *(int*)(b + 0x20);
    int delta = a;
    delta -= d;
    int v34 = *(int*)(a + 0x34) - delta;
    int v38 = *(int*)(a + 0x38) - delta;
    int v3c = *(int*)(a + 0x3c) - delta;
    int v40 = *(int*)(a + 0x40) - delta;
    *(int*)(a + 0x34) = v34;
    *(int*)(a + 0x38) = v38;
    *(int*)(a + 0x3c) = v3c;
    *(int*)(a + 0x40) = v40;
    FUN_012070a0((void*)a, (void*)b);
}

// ================================================================== 0x012056f0
// void FUN_012056f0(int a, int b, int c)
// @ 0x012056f0
void FUN_012056f0(int a, int b, int c)
{
    FUN_012070c0((void*)a, (void*)b, (void*)c);
    int delta = a - b;
    *(int*)(a + 0x34) = *(int*)(a + 0x34) + delta;
    *(int*)(a + 0x38) = *(int*)(a + 0x38) + delta;
    int e = *(int*)(a + 0x3c) + delta;
    *(int*)(a + 0x3c) = e;
    *(int*)(a + 0x40) = *(int*)(a + 0x40) + delta;
    FUN_01207110((void*)e, (void*)b, (void*)c);
}

// ================================================================== 0x01205740
// int FUN_01205740(int a, int b)
// @ 0x01205740
int FUN_01205740(int a, int b)
{
    if (FUN_012070d0((void*)a, (void*)b) == 0)
        return 0;
    int delta = a - *(int*)(b + 0x7c);
    *(int*)(a + 0x34) = *(int*)(a + 0x34) + delta;
    *(int*)(a + 0x38) = *(int*)(a + 0x38) + delta;
    int e = *(int*)(a + 0x3c) + delta;
    *(int*)(a + 0x3c) = e;
    *(int*)(a + 0x40) = *(int*)(a + 0x40) + delta;
    FUN_01207140((void*)e, (void*)b);
    *(unsigned int*)(a + 0x20) = (unsigned int)&DAT_015d0a7c;
    return 1;
}

// ================================================================== 0x012057a0
// int FUN_012057a0(void)
// @ 0x012057a0
int FUN_012057a0(void)
{
    DAT_0171e598 = 0;
    DAT_0171e59c = (unsigned int)&DAT_015d0abc;
    DAT_0171e5a0 = (unsigned int)&DAT_015d0a98;
    DAT_0171e5a4 = (unsigned int)&DAT_015d0a58;
    DAT_0171e5a8 = (unsigned int)&DAT_015d0b04;
    DAT_0171e5ac = (unsigned int)&DAT_015d0ae0;
    return 1;
}

// ================================================================== 0x01205820
// void FUN_01205820(float* a, float* b, float* out)
//   Shared / axis-scaled interval for the slab test.
// @ 0x01205820
void FUN_01205820(float* a, float* b, float* out)
{
    float d = vdot(a, b);
    out[1] = d;
    *out = d;
    float e = a[0x1c] * fabsf_(vdot(a + 0x10, b));
    *out = d - e;
    out[1] = d + e;
}

// ================================================================== 0x012058e0
// void FUN_012058e0(float* a, int b, int count, float* out)
// @ 0x012058e0
void FUN_012058e0(float* a, int b, int count, float* out)
{
    if (count != 0) {
        int delta = b - (int)out;
        do {
            float* p = (float*)(delta + (int)out);
            float d = vdot(a, p);
            out[1] = d;
            *out = d;
            p = (float*)(delta + (int)out);
            float e = a[0x1c] * fabsf_(vdot(a + 0x10, p));
            *out = d - e;
            out[1] = d + e;
            out = out + 4;
            count = count - 1;
        } while (count != 0);
    }
}

// ================================================================== 0x012059b0
// void __thiscall FUN_012059b0(void* self, int a, int b, int out)
//   Build the axis-aligned segment from an oriented box and store it in `out`.
// @ 0x012059b0
struct OrientedBox {
    void BuildSegment(int a, int b, int out);      // 0x012059b0  ecx = this
};
void OrientedBox::BuildSegment(int a, int b, int out)
{
    (void)a; (void)b;
    float s = *(float*)((char*)this + 0x44);
    __m128 e = _mm_mul_ps(*(__m128*)((char*)this + 0x10), _mm_set1_ps(s));
    __m128 c = *(__m128*)((char*)this + 0x30);
    __m128 lo = _mm_sub_ps(c, e);
    __m128 hi = _mm_add_ps(c, e);
    float* seg = (float*)FUN_012016f0(&hi, &lo);
    *(__m128*)(out + 0x10) = *(__m128*)(seg + 0);
    *(__m128*)(out + 0x20) = *(__m128*)(seg + 4);
    *(__m128*)(out + 0x30) = *(__m128*)(seg + 8);
    *(unsigned int*)(out + 0x40) = *(unsigned int*)(seg + 12);
    *(int*)(out + 0x130) = 1;
}

// ================================================================== 0x01205a30
// int FUN_01205a30(float* out, float* p0, float* dir, float* p1, float* n,
//                  float r, float h, int solid, int skip)
//   Ray/sphere vs. slab intersection used by the volume sweep.
// @ 0x01205a30
int FUN_01205a30(float* param_1, float* param_2, float* param_3, float* param_4,
                 float* param_5, float param_6, float param_7, int param_8, int param_9)
{
    __m128 d = _mm_sub_ps(vload(param_4), vload(param_2));   // p4 - p2
    __m128 n = vload(param_5);
    __m128 c1 = vcross(d, n);                                // (p4-p2) x n
    float fVar1 = vhsum(_mm_mul_ps(c1, c1));
    param_7 = (param_6 * param_7) * param_7;
    if (fVar1 < param_7 && param_9 == 0) {
        *param_1 = 0.0f;
        param_1[1] = 1.0f;
        return 1;
    }
    __m128 c2 = vcross(vload(param_3), n);                   // dir x n
    float fVar6 = vhsum(_mm_mul_ps(c1, c2));
    if (param_8 == 0 && fVar6 <= 0.0f)
        return -1;
    float fVar4 = vhsum(_mm_mul_ps(c2, c2));
    float fVar3 = (fVar6 * fVar6 - fVar4 * fVar1) + fVar4 * param_7;
    if (fVar3 < 0.0f)
        return 0;
    float fVar2 = fVar6 - fVar4;
    float fVar5;
    if (param_8 == 0) {
        if (0.0f <= fVar2 && fVar3 <= fVar2 * fVar2)
            return 0;
        fVar5 = 1.0f;
    } else {
        if (0.0f <= fVar2)
            return 0;
        if (fVar2 * fVar2 <= fVar3)
            return 0;
        fVar5 = -1.0f;
    }
    param_1[1] = fVar4;
    *param_1 = fVar6 - fsqrt_x87(fVar3) * fVar5;
    return 1;
}
