// Slice s01203ee0 -- 0x01203ee0 .. 0x01204c60 (18 functions).
//
// RenderWare 4 collision: TriangleVolume::LinearCast (the swept sphere / ray cast entry point),
// the triangle KD-tree procedural volume's traversal stack (push/pop/compact/descend, the
// TriangleKDTreeProcedural constructor and Initialize), the swept-AABB builders and the
// swept-AABB slab interval test.  The range is inside the /GL+/LTCG built RenderWare 4 core
// (symbols/renderware4_core.txt), so the callers cannot be byte-exact single-object; they are
// written complete and behaviourally faithful.  The leaf helpers may still match.
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP /arch:SSE  (cl 13.10 -- the RenderWare 4
// core was built with the VC .NET 2003 toolset, see symbols/renderware4_core.txt).

#include <xmmintrin.h>

typedef unsigned int uint32_t;

// Internal calls go through a declared-but-undefined dummy, otherwise cl 13.10
// sees the callee body in this TU, proves ecx survives the call and keeps `this`
// in ecx instead of framing it in a callee-saved register (which breaks the
// byte-match of every caller).
struct ExtC3   { void* f(int a1, int a2, int a3); };           // 0x012040b0
struct ExtC0b  { void h(); };                                  // 0x012044e0
struct ExtCtor { void* ctor(int a2, uint32_t a3, int a6, int a7); }; // 0x01204680

// ---------------------------------------------------------------------------------------
// rw::math::vpu vectors / matrices
struct Matrix44Affine {         // +0x00 .. +0x3f, row-major, row 3 = translation
    __m128 r0, r1, r2, r3;
};

union Vec4Access {
    __m128 v;
    float f[4];
};
static __forceinline float Get(__m128 v, int i)
{
    Vec4Access a;
    a.v = v;
    return a.f[i];
}
static __forceinline __m128 Splat(float f) { return _mm_set_ps1(f); }
static __forceinline __m128 Abs(__m128 v)  { return _mm_max_ps(_mm_mul_ps(Splat(-1.0f), v), v); }

// The retail build lowers the float min used by the stack-compaction filter (0x01204420)
// to a branchless sign-mask select (subss / sar 31 / and / or): the result is `a` when the
// sign bit of (a-b) is set, else `b`.  A C ternary lowers differently and, on a +/-0 tie
// (a == b == 0 with opposite signs, so a-b is -0 or +0), selects the wrong zero; the select
// stores -0 the way the original does, so model it explicitly.
static __forceinline float SignMaskMin(float a, float b)
{
    float d = a - b;
    unsigned m = (unsigned)(*(int*)&d >> 31);
    unsigned ua = *(const unsigned*)&a;
    unsigned ub = *(const unsigned*)&b;
    unsigned r = (m & ua) | (~m & ub);
    return *(const float*)&r;
}

// two Newton-Raphson steps of rcp
static __forceinline __m128 Reciprocal2(__m128 x)
{
    const __m128 two = Splat(2.0f);
    __m128 r = _mm_rcp_ps(x);
    r = _mm_mul_ps(_mm_sub_ps(two, _mm_mul_ps(r, x)), r);
    r = _mm_mul_ps(_mm_sub_ps(two, _mm_mul_ps(r, x)), r);
    return r;
}

// ---------------------------------------------------------------------------------------
// Swept AABB: mn +0x00, extent +0x10, reciprocal extent +0x20, reference point +0x30.
struct AABB {
    __m128 mn;
    __m128 mx;
    __m128 rcp;
    __m128 ref;
    AABB* Transform(AABB* out, const Matrix44Affine* xf);                                    // 0x01204780
    void  BuildSwept(const float* a2, const float* a3, const float* a4, const float* a5);    // 0x01204890
    AABB* BuildSwept2(const float* a2, const float* a3, const float* a4);                    // 0x012049e0
    int   GetInterval(float* p2, float* p3, const float* a4);                                // 0x01204a50
};

// ---------------------------------------------------------------------------------------
// The KD-tree traversal state (opaque block; every method is a thiscall on it).
struct Tree {
    int   m01203fc0(int a2, const void* a3, const void* a4, int a5, char a6);   // 0x01203fc0
    void* m012040b0(int a1, int a2, int a3);                                     // 0x012040b0
    void  m012041a0();                                                           // 0x012041a0
    int   m01204380(unsigned* out);                                              // 0x01204380
    void  m01204420(float p);                                                    // 0x01204420
    void  m012044e0();                                                           // 0x012044e0
    int   m012045a0(unsigned* out);                                              // 0x012045a0
    void* m01204620(void* a1, const __m128* a2);                                 // 0x01204620
    void* m01204680(int a1, int a2, int a3, int a4);                             // 0x01204680
    void* m01204c60(void* a1, const float* a2, const float* a3);                 // 0x01204c60
};

// free functions of the same module (no `this`)
void  m01204110(int* p, int a2, int a3);                                                         // 0x01204110
void* m01204180(int* p, int a2, int a3);                                                         // 0x01204180
void* m012046f0(Tree** p, int a2, uint32_t a3, uint32_t a4, const void* a5, int a6, int a7);     // 0x012046f0

// ---------------------------------------------------------------------------------------
// TriangleVolume + the cast entry points
class TriangleVolume;
struct VolumeCastResult {
    const TriangleVolume* mpVolume;  // +0x00
    uint32_t pad[3];
    __m128 mPosition;                // +0x10
    __m128 mNormal;                  // +0x20
    __m128 mFeature;                 // +0x30
    float  mFraction;                // +0x40
};

// ray vs triangle without radius (cdecl)
int RayTriangleCast(VolumeCastResult* out, const __m128* from, const __m128* dir,
                    const __m128* v0, const __m128* v1, const __m128* v2);          // 0x01201a20

// swept sphere vs triangle: a cl "static" with a register ABI (ecx = `from`, esi = `out`, the
// five remaining arguments on the stack, caller-popped).  A single-object recompile cannot set
// esi, so the receiver models only the ecx half of the ABI.
struct SweepCaster {
    int Cast(const __m128& sweep, const __m128& v0, const __m128& v1,
             const __m128& v2, float radius);                                       // 0x01203110
};

class TriangleVolume {
public:
    void GetWorldVertices(__m128* v0, __m128* v1, __m128* v2, const void* xf) const;  // 0x01202160
    void GetWorldNormal(__m128* normal, const void* xf) const;                        // 0x01202020
    int  LinearCast(const __m128* from, const __m128* to, const void* xf,
                    VolumeCastResult* out) const;                                     // 0x01203ee0

    __m128 mVertices[3];   // +0x00
    __m128 mField30;       // +0x30
    __m128 mField40;       // +0x40
    float  mRadius;        // +0x50
};

// =======================================================================================

// @ 0x01203ee0
int TriangleVolume::LinearCast(const __m128* from, const __m128* to, const void* xf,
                               VolumeCastResult* out) const
{
    __m128 v0, v1, v2;
    GetWorldVertices(&v0, &v1, &v2, xf);
    out->mpVolume = this;
    if (mRadius == 0.0f) {
        __m128 dir = _mm_sub_ps(*to, *from);
        int hit = RayTriangleCast(out, from, &dir, &v0, &v1, &v2);
        if (hit != 0)
            GetWorldNormal(&out->mNormal, xf);
        return hit;
    }
    GetWorldNormal(&out->mNormal, xf);
    __m128 dir = _mm_sub_ps(*to, *from);
    return ((SweepCaster*)(const void*)from)->Cast(dir, v0, v1, v2, mRadius);
}

// =======================================================================================
// Traversal stack (entry stride 0x80 in the pool at +0xc8)

// @ 0x01203fc0
int Tree::m01203fc0(int a2, const void* a3, const void* a4, int a5, char a6)
{
    if (*(unsigned*)((char*)this + 0xcc) >= *(unsigned*)((char*)this + 0xd0))
        return 0;
    *(int*)(*(char**)((char*)this + 0xc8) + *(int*)((char*)this + 0xcc) * 0x80) = a2;
    if (a3 == 0) {
        *(int*)(*(char**)((char*)this + 0xc8) + *(int*)((char*)this + 0xcc) * 0x80 + 4) = 0;
    } else {
        const __m128* m = (const __m128*)a3;
        __m128* d = (__m128*)(*(char**)((char*)this + 0xc8) + *(int*)((char*)this + 0xcc) * 0x80 + 0x10);
        d[0] = m[0];
        d[1] = m[1];
        d[2] = m[2];
        d[3] = m[3];
        *(int*)(*(char**)((char*)this + 0xc8) + *(int*)((char*)this + 0xcc) * 0x80 + 4) = (int)d;
    }
    {
        const __m128* m = (const __m128*)a4;
        __m128* d = (__m128*)(*(char**)((char*)this + 0xc8) + *(int*)((char*)this + 0xcc) * 0x80 + 0x50);
        d[0] = m[0];
        d[1] = m[1];
    }
    *(int*)(*(char**)((char*)this + 0xc8) + *(int*)((char*)this + 0xcc) * 0x80 + 0x70) = a5;
    *(char*)(*(char**)((char*)this + 0xc8) + *(int*)((char*)this + 0xcc) * 0x80 + 0x74) = a6;
    *(int*)((char*)this + 0xcc) = *(int*)((char*)this + 0xcc) + 1;
    return 1;
}

// @ 0x012040b0
void* Tree::m012040b0(int a1, int a2, int a3)
{
    char* p = (char*)this + 0x100;
    int d4 = (int)(p + a1 * 0x80);
    int c8 = d4 + a2 * 0x60;
    *(int*)((char*)this + 0xc4) = a1;
    *(int*)((char*)this + 0xdc) = a2;
    *(int*)((char*)this + 0xd0) = a3;
    *(int*)((char*)this + 0xd4) = d4;
    *(int*)((char*)this + 0x30) = (int)p;
    *(int*)((char*)this + 0xc8) = c8;
    *(int*)((char*)this + 0xe4) = c8 + a3 * 0x80;
    return this;
}

// @ 0x01204110
void m01204110(int* p, int a2, int a3)
{
    p[1] = 1;
    p[3] = 1;
    p[0] = 0;
    p[2] = 0;
    p[5] = 1;
    p[4] = 0;
    p[7] = 1;
    p[6] = 0;
    p[0] = ((a2 + a3 + 2) << 7) + ((a3 * 3) << 5) + 0x27e0;
    p[1] = 0x10;
}

// @ 0x01204180
void* m01204180(int* p, int a2, int a3)
{
    ExtC3* t = (ExtC3*)*p;
    if (t != 0)
        return t->f(a2, a3, a3);
    return 0;
}

// =======================================================================================
// The KD-tree descent (the state block's +0x250 stack, +0x0 base, +0x10/+0x20/+0x30 extents)

// @ 0x012041a0
void Tree::m012041a0()
{
    char* t = (char*)this;
    int cur = *(int*)(t + 0x250) - 1;
    *(int*)(t + 0x250) = cur;
    int* entry = (int*)(t + (cur + 5) * 0x10);
    int nodeIdx = entry[1];
    float lo = *(float*)(entry + 2);
    float hi = *(float*)(entry + 3);
    char* node = (char*)(*(int*)*(int*)t + nodeIdx * 0x20);
    int idx = *(int*)(node + 4);
    __m128 v1 = *(const __m128*)(t + 0x10);
    __m128 v2 = *(const __m128*)(t + 0x40);
    __m128 v3 = *(const __m128*)(t + 0x30);
    float f = Get(v3, idx);
    float arr[4];
    arr[0] = (*(float*)(node + 0x18) + Get(v2, idx) - Get(v1, idx)) * f;
    arr[1] = (*(float*)(node + 0x1c) - Get(v2, idx) - Get(v1, idx)) * f;
    arr[2] = Get(v3, 2);
    arr[3] = Get(v3, 3);
    int e = f > 0.0f ? 1 : 0;
    if (hi > arr[e]) {
        entry[0] = *(int*)(node + 8 + e * 8);
        entry[1] = *(int*)(node + 0xc + e * 8);
        int i = *(int*)(t + 0x250);
        *(float*)(t + i * 0x10 + 0x58) = lo > arr[e] ? lo : arr[e];
        *(float*)(t + i * 0x10 + 0x5c) = hi;
        *(int*)(t + 0x250) = i + 1;
    }
    int e2 = e == 0 ? 1 : 0;
    if (arr[e2] > lo) {
        int i = *(int*)(t + 0x250);
        *(int*)(t + (i + 5) * 0x10) = *(int*)(node + 8 + e2 * 8);
        *(int*)(t + (i + 5) * 0x10 + 4) = *(int*)(node + 0xc + e2 * 8);
        *(float*)(t + i * 0x10 + 0x58) = lo;
        *(float*)(t + i * 0x10 + 0x5c) = hi < arr[e2] ? hi : arr[e2];
        *(int*)(t + 0x250) = i + 1;
    }
}

// @ 0x01204380
int Tree::m01204380(unsigned* out)
{
    char* t = (char*)this;
    while (*(int*)(t + 0x254) == 0) {
        if (*(int*)(t + 0x250) == 0)
            return 0;
        while (*(int*)(t + (*(int*)(t + 0x250) + 4) * 0x10) == -1)
            m012041a0();
        int m = *(int*)(t + 0x250) - 1;
        *(int*)(t + 0x250) = m;
        *(int*)(t + 0x254) = *(int*)(t + (m + 5) * 0x10);
        *(int*)(t + 0x258) = *(int*)(t + m * 0x10 + 0x54);
    }
    *out = *(unsigned*)(t + 0x258);
    *(int*)(t + 0x258) = *(int*)(t + 0x258) + 1;
    *(int*)(t + 0x254) = *(int*)(t + 0x254) - 1;
    return 1;
}

// @ 0x01204420
void Tree::m01204420(float p)
{
    char* t = (char*)this;
    int n = 0;
    if (*(int*)(t + 0x250) == 0) {
        *(int*)(t + 0x250) = 0;
        return;
    }
    const float* src = (const float*)(t + 0x50);
    float* dst = (float*)(t + 0x5c);
    for (unsigned i = 0; i < *(unsigned*)(t + 0x250); i++) {
        if (src[2] <= p) {
            dst[-3] = src[0];
            dst[-2] = src[1];
            dst[-1] = src[2];
            dst[0] = src[3];
            dst[0] = SignMaskMin(dst[0], p);
            n++;
            dst += 4;
        }
        src += 4;
    }
    *(int*)(t + 0x250) = n;
}

// =======================================================================================
// The leaf descent (the state block's +0xb0 stack of node indices, +0x30 array)

// @ 0x012044e0
void Tree::m012044e0()
{
    char* t = (char*)this;
    int d = *(int*)(t + 0xb0) - 1;
    *(int*)(t + 0xb0) = d;
    char* node = (char*)(*(int*)*(int*)t + *(int*)(t + d * 4 + 0x30) * 0x20);
    *(int*)(t + 0xb4) = 0;
    int idx = *(int*)(node + 4);
    __m128 v3 = *(const __m128*)(t + 0x20);
    if (Get(v3, idx) >= *(float*)(node + 0x1c)) {
        if (*(int*)(node + 0x10) == -1) {
            *(int*)(t + d * 4 + 0x30) = *(int*)(node + 0x14);
            *(int*)(t + 0xb0) = d + 1;
        } else {
            *(int*)(t + 0xb4) = *(int*)(node + 0x10);
            *(int*)(t + 0xb8) = *(int*)(node + 0x14);
        }
    }
    __m128 v1 = *(const __m128*)(t + 0x10);
    if (*(float*)(node + 0x18) >= Get(v1, idx)) {
        if (*(int*)(node + 8) == -1) {
            int c = *(int*)(t + 0xb0);
            *(int*)(t + c * 4 + 0x30) = *(int*)(node + 0xc);
            *(int*)(t + 0xb0) = c + 1;
            return;
        }
        *(int*)(t + 0xb4) = *(int*)(t + 0xb4) + *(int*)(node + 8);
        *(int*)(t + 0xb8) = *(int*)(node + 0xc);
    }
}

// @ 0x012045a0
int Tree::m012045a0(unsigned* out)
{
    char* t = (char*)this;
    for (;;) {
        if (*(int*)(t + 0xb4) != 0) {
            *out = *(unsigned*)(t + 0xb8);
            *(int*)(t + 0xb8) = *(int*)(t + 0xb8) + 1;
            *(int*)(t + 0xb4) = *(int*)(t + 0xb4) - 1;
            return 1;
        }
        if (*(int*)(t + 0xb0) == 0)
            return 0;
        ((ExtC0b*)t)->h();
    }
}

// @ 0x01204620
void* Tree::m01204620(void* a1, const __m128* a2)
{
    char* t = (char*)this;
    *(void**)t = a1;
    *(__m128*)(t + 0x10) = a2[0];
    *(__m128*)(t + 0x20) = a2[1];
    *(int*)(t + 0xb4) = 0;
    *(int*)(t + 0xb8) = 0;
    if (*(unsigned*)((char*)a1 + 4) > 0) {
        *(int*)(t + 0x30) = 0;
        *(int*)(t + 0xb0) = 1;
    } else {
        *(int*)(t + 0xb4) = *(int*)((char*)a1 + 8);
        *(int*)(t + 0xb8) = 0;
        *(int*)(t + 0xb0) = 0;
    }
    return this;
}

// =======================================================================================
// TriangleKDTreeProcedural

// @ 0x01204680
void* Tree::m01204680(int a1, int a2, int a3, int a4)
{
    char* t = (char*)this;
    *(int*)(t + 0x20) = a3;
    uint32_t u = (uint32_t)(a2 + 1);
    *(int*)(t + 0x24) = 0;
    *(int*)(t + 0x28) = a2;
    if (u != 0) {
        uint32_t c = 0;
        do {
            u >>= 1;
            c++;
        } while (u != 0);
        *(int*)(t + 0x24) = c;
    }
    int p = ((int)this + a4 + 0xf) & ~0xf;
    *(int*)(t + 0x30) = a1;
    *(int*)(t + 0x38) = p;
    int verts = p + a1 * 0x10;
    *(int*)(t + 0x34) = verts;
    int tris = verts + a2 * 0x10;
    *(int*)(t + 0x40) = tris;
    *(int*)(t + 0x3c) = (tris + (int)(((uint32_t)a2 + 7u) >> 3) * 4 + 0xf) & ~0xf;
    return this;
}

// @ 0x012046f0
void* m012046f0(Tree** p, int a2, uint32_t a3, uint32_t a4, const void* a5, int a6, int a7)
{
    uint32_t u = (a3 + 7) >> 3;
    void* obj;
    if (*p != 0)
        obj = ((ExtCtor*)*p)->ctor(a2, a3, a6, a7);
    else
        obj = 0;
    int* q = *(int**)((char*)obj + 0x3c);
    q[2] = a3;
    q[1] = a4;
    *(__m128*)(q + 4) = ((const __m128*)a5)[0];
    *(__m128*)(q + 8) = ((const __m128*)a5)[1];
    if (a4 > 0)
        q[0] = ((int)q + 0x3f) & ~0xf;
    else
        q[0] = 0;
    for (uint32_t i = 0; i < u; i++)
        *(int*)(*(int*)((char*)obj + 0x40) + i * 4) = -1;
    return obj;
}

// =======================================================================================
// Swept AABB

// @ 0x01204780
AABB* AABB::Transform(AABB* out, const Matrix44Affine* xf)
{
    if (!xf) {
        out->mn = mn;
        out->mx = mx;
        return out;
    }
    const __m128 half = Splat(0.5f);
    __m128 center = _mm_mul_ps(_mm_add_ps(mx, mn), half);
    __m128 ext = _mm_mul_ps(_mm_sub_ps(mx, mn), half);
    __m128 tc = _mm_add_ps(_mm_add_ps(_mm_add_ps(
                           _mm_mul_ps(xf->r0, _mm_shuffle_ps(center, center, 0x00)),
                           _mm_mul_ps(xf->r1, _mm_shuffle_ps(center, center, 0x55))),
                           _mm_mul_ps(xf->r2, _mm_shuffle_ps(center, center, 0xaa))), xf->r3);
    __m128 te = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_max_ps(_mm_sub_ps(_mm_setzero_ps(), xf->r0), xf->r0),
                                                 _mm_shuffle_ps(ext, ext, 0x00)),
                                      _mm_mul_ps(_mm_max_ps(_mm_sub_ps(_mm_setzero_ps(), xf->r1), xf->r1),
                                                 _mm_shuffle_ps(ext, ext, 0x55))),
                           _mm_mul_ps(_mm_max_ps(_mm_sub_ps(_mm_setzero_ps(), xf->r2), xf->r2),
                                      _mm_shuffle_ps(ext, ext, 0xaa)));
    out->mn = _mm_sub_ps(tc, te);
    out->mx = _mm_add_ps(tc, te);
    return out;
}

// @ 0x01204890
void AABB::BuildSwept(const float* a2, const float* a3, const float* a4, const float* a5)
{
    __m128 v1 = *(__m128*)a2;
    __m128 d1 = _mm_sub_ps(*(const __m128*)(a5 + 4), v1);
    __m128 d2 = _mm_sub_ps(*(const __m128*)a5, v1);
    __m128 absmax = _mm_max_ps(Abs(d2), Abs(d1));
    __m128 delta = _mm_mul_ps(_mm_sub_ps(*(const __m128*)a3, v1), Splat(0.5f));
    __m128 adelta = Abs(delta);
    __m128 slack = _mm_sub_ps(_mm_max_ps(_mm_mul_ps(absmax, Splat(1e-6f)), adelta), adelta);
    float sx = Get(delta, 0) >= 0.0f ? 1.0f : -1.0f;
    float sy = Get(delta, 1) >= 0.0f ? 1.0f : -1.0f;
    float sz = Get(delta, 2) >= 0.0f ? 1.0f : -1.0f;
    __m128 off = _mm_mul_ps(_mm_set_ps(sx, sz, sy, sx), slack);
    mn = _mm_sub_ps(v1, off);
    mx = _mm_sub_ps(_mm_add_ps(*(const __m128*)a3, off), mn);
    rcp = Reciprocal2(mx);
    ref = _mm_add_ps(*(const __m128*)a4, slack);
}

// @ 0x012049e0
AABB* AABB::BuildSwept2(const float* a2, const float* a3, const float* a4)
{
    __m128 slack = _mm_mul_ps(_mm_max_ps(Abs(*(const __m128*)a2), Abs(*(const __m128*)a3)), Splat(1e-6f));
    BuildSwept(a2, a3, (const float*)&slack, a4);
    return this;
}

// @ 0x01204a50
int AABB::GetInterval(float* p2, float* p3, const float* a4)
{
    __m128 lo = _mm_sub_ps(_mm_sub_ps(*(const __m128*)a4, ref), mn);
    __m128 hi = _mm_sub_ps(_mm_add_ps(*(const __m128*)(a4 + 4), ref), mn);
    __m128 e0 = _mm_mul_ps(rcp, lo);
    __m128 e1 = _mm_mul_ps(rcp, hi);
    __m128 lanemin = _mm_min_ps(e0, e1);
    __m128 lanemax = _mm_max_ps(e0, e1);
    float a = Get(lanemin, 0);
    float b = Get(lanemin, 1);
    float c = Get(lanemin, 2);
    float tmin = (a < b ? b : a) < c ? c : (a < b ? b : a);
    float d = Get(lanemax, 0);
    float e = Get(lanemax, 1);
    float f = Get(lanemax, 2);
    float tmax = (d < e ? d : e) < f ? (d < e ? d : e) : f;
    *p2 = *p2 < tmin ? tmin : *p2;
    *p3 = *p3 > tmax ? tmax : *p3;
    if (*p3 > *p2)
        return 1;
    return 0;
}

// @ 0x01204c60
void* Tree::m01204c60(void* a1, const float* a2, const float* a3)
{
    char* t = (char*)this;
    *(void**)t = a1;
    ((AABB*)(t + 0x10))->BuildSwept2(a2, a3, (const float*)((char*)a1 + 0x10));
    *(float*)(t + 0x58) = 0.0f;
    *(float*)(t + 0x5c) = 1.0f;
    *(int*)(t + 0x254) = 0;
    *(int*)(t + 0x258) = 0;
    if (((AABB*)(t + 0x10))->GetInterval((float*)(t + 0x58), (float*)(t + 0x5c),
                                         (const float*)((char*)a1 + 0x10)) != 0) {
        if (*(unsigned*)((char*)a1 + 4) > 0) {
            *(int*)(t + 0x54) = 0;
            *(int*)(t + 0x50) = -1;
            *(int*)(t + 0x250) = 1;
            return this;
        }
        *(int*)(t + 0x254) = *(int*)((char*)a1 + 8);
        *(int*)(t + 0x258) = 0;
    }
    *(int*)(t + 0x250) = 0;
    return this;
}
