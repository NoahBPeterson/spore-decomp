// Slice s00705660 (batch w2g1, slice 35): lighting-world helpers, small
// vector/struct copy helpers and EASTL vector-of-bool routines.
#include "types.h"
#include <xmmintrin.h>
#include <math.h>
#include <algorithm>

void __stdcall sub_406540(void*, void*, int, int, void*); // EASTL fill/uninitialized helper
void sub_41cb40(void*, void*);                    // cSPMatrix3::Assign (this, src)
void __fastcall sub_620230(void*);                // intrusive_list_base dtor
void  sub_f47380(void*);                          // operator delete
void* sub_f473a0(unsigned, const char*, int, int, int, int);   // operator new
void  sub_11e0744(void*, const void*, int);       // memcpy
void  sub_13cc480(void*, const void*, int);       // memmove (IAT)
void  sub_6983a0(const void*, void*);             // 0x6983a0 SP::MatrixFromDirection (dir, out)
unsigned sub_932e80(const char*, unsigned, int);  // 0x932e80 FNV hash used for the effects key

#define GRAPHICS       "Graphics"
#define ALLOCATOR_H    0x13ebb38
#define EFFECTS_POINT  "effects-point"

extern float g_1485720;   // 0x1485720  1.0f
extern float g_1470f1c;   // 0x1470f1c  2.0f
extern float g_14853e0;   // 0x14853e0  4.0f
extern float g_13ec478;   // 0x13ec478  0.05f
extern float g_162992c;   // 0x162992c  uninitialised-basis marker x
extern float g_1629930;   // 0x1629930  uninitialised-basis marker y
extern float g_1629934;   // 0x1629934  uninitialised-basis marker z
extern float g_1629a74;   // 0x1629a74  basis template source

struct __declspec(align(16)) V16 { __m128 m; };
struct __declspec(align(16)) V32 { __m128 a, b; };

// ==========================================================================
// @ 0x00705920  SP::cLightingWorld::GetLightingStateConfig
// ==========================================================================
struct W5920 {
    uint32_t pad[4];        // 0x00
    int**    m10;           // 0x10
    int* get();
};
int* W5920::get()
{
    int** p = m10;
    return p ? *p : 0;
}

// ==========================================================================
// @ 0x00705bb0
// ==========================================================================
struct S11 {
    int   a, b, c;          // 0x00
    float d, e, f, g, h;    // 0x0c
    int   i, j, k;          // 0x20
    S11& operator=(const S11& s);
};
S11& S11::operator=(const S11& s)
{
    a = s.a; b = s.b; c = s.c;
    d = s.d; e = s.e; f = s.f; g = s.g; h = s.h;
    i = s.i; j = s.j; k = s.k;
    return *this;
}

// ==========================================================================
// @ 0x00705c00
// ==========================================================================
struct S7 {
    float f[7];
    S7& operator=(const S7& s);
};
S7& S7::operator=(const S7& s)
{
    f[0] = s.f[0]; f[1] = s.f[1]; f[2] = s.f[2]; f[3] = s.f[3];
    f[4] = s.f[4]; f[5] = s.f[5]; f[6] = s.f[6];
    return *this;
}

// ==========================================================================
// @ 0x00705e90  fill [first,last) with *value
// ==========================================================================
void fill_705e90(__m128* first, __m128* last, const __m128* value)
{
    for (; first != last; ++first)
        *first = *value;
}

// ==========================================================================
// @ 0x00705ec0  fill n elements (destination may be null) with *value
// ==========================================================================
void fill_705ec0(__m128* first, unsigned n, const __m128* value)
{
    // the cursor copy makes the entry load `first` land in eax before the count test,
    // which is what retail leaves in eax for n == 0
    __m128* p = first;
    for (unsigned i = n; i != 0; --i) {
        if (p)
            *p = *value;
        ++p;
    }
}

// ==========================================================================
// @ 0x00705c40  copy [first,last) forward into dst, reporting the end
// ==========================================================================
void copy_705c40(V32** endp, V32* first, V32* last, V32* dst)
{
    *endp = dst;
    if (first != last) {
        do {
            if (dst) {
                dst->a = _mm_load_ps((const float*)&first->a);
                dst->b = _mm_load_ps((const float*)&first->b);
            }
            ++first;
            ++dst;
        } while (first != last);
        *endp = dst;
    }
    // retail's allocator kept the end-report pointer in eax across the loop and spilled
    // `first` into its argument slot instead; cl's /O2 parks the end report in esi, so the
    // leftover eax callers may read is restored here (single instruction, no logic).
    __asm mov eax, endp
}

// ==========================================================================
// @ 0x00705ef0  destructor: list dtor + two possibly-null owned buffers
// ==========================================================================
struct W5ef0 {
    void* buf0;             // 0x00
    uint32_t pad[4];
    void* buf14;            // 0x14
    uint32_t pad2[5];
    void dtor();
};
void W5ef0::dtor()
{
    sub_620230((char*)this + 0x2c);
    void* q = buf14;
    if (q != 0 && *(int*)((char*)q - 4) != 0)
        sub_f47380(q);
    q = buf0;
    if (q != 0 && *(int*)((char*)q - 4) != 0)
        sub_f47380(q);
}

// ==========================================================================
// @ 0x00705660  point -> packed 4-bit lighting-grid coordinate
// ==========================================================================
// retail inlined the SSE1 ftol helper, which converts with the rounding `cvtss2si`
// rather than the truncating `cvttss2si` cl emits for a plain cast (EA's asm helper).
__forceinline int RoundToInt_705660(float f) { __asm cvtss2si eax, f }

int FUN_00705660(float* a, float* b, float param)
{
    if (param == 0.0f)
        return -1;
    int u1 = RoundToInt_705660(((a[0] - b[0]) / (b[3] - b[0])) * 16.0f);
    int u2 = RoundToInt_705660(((a[1] - b[1]) / (b[4] - b[1])) * 16.0f);
    int u3 = RoundToInt_705660(((a[2] - b[2]) / (b[5] - b[2])) * 4.0f);
    if ((((u2 | u1) & 0xfffffff3) | u3) & 0xfffffffc)
        return -1;
    return (u3 * 16 + u2) * 16 + u1;
}

// ==========================================================================
// @ 0x00705970  inverse-blend factor for a distance range
// ==========================================================================
struct W5970 {
    uint32_t pad[4];
    float* m10;             // 0x10
    float f(int a2, float p3);
};
// EA fast-math helpers: the ratio stays in x87 (the original kept its extended
// intermediates) and the clamp is SSE maxss/minss (a NaN ratio becomes 1.0f).
static __forceinline float Ratio_705970(float hi, float t, float d)
{
    float r;
    __asm {
        fld   hi
        fsub  t
        fdiv  d
        fstp  r
    }
    return r;
}
static __forceinline float Clamp01_705970(float v)
{
    float one = 1.0f;
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, v
        minss xmm0, one
        movss v, xmm0
    }
    return v;
}
float W5970::f(int a2, float p3)
{
    (void)a2;
    float d = m10[0x4c] - m10[0x4b];
    if (d < 0.0f)
        return 1.0f;
    if (d == 0.0f) {
        if (p3 < m10[0x4b])
            return 1.0f;
        return 0.0f;
    }
    return Clamp01_705970(Ratio_705970(m10[0x4c], p3, d));
}

// ==========================================================================
// @ 0x00705a20  SP::cLightingManager::SetAtmosphereModel
// ==========================================================================
struct V4 { float x, y, z, w; };
struct V3 { float x, y, z; };
struct W5a20 {
    uint32_t pad[0x12];     // 0x00
    V3    mSun;             // 0x48
    int   nphases;          // 0x54
    V4    phases[1];        // 0x58
    void setAtm(float* v, int n, float* ph);
};
void W5a20::setAtm(float* v, int n, float* ph)
{
    // the length+sqrt+reciprocal stay in x87 (double intermediates: with /arch:SSE
    // doubles are x87), and `inv` reaches the products rounded to float first.
    double len = (double)v[0] * v[0] + (double)v[1] * v[1] + (double)v[2] * v[2] + 1e-8f;
    volatile float inv = (float)(1.0 / sqrt(len));
    V3 sun = { v[0] * inv, inv * v[1], inv * v[2] };
    mSun = sun;
    nphases = n;
    int cnt = std::min(n, 10);
    for (int i = 0; i < cnt; i++)
        phases[i] = ((const V4*)ph)[i];     // phases are 16-byte records, copied as words
}

// ==========================================================================
// @ 0x00705af0  linear search over a 0x144-byte-element array
// ==========================================================================
struct W5af0 {
    uint32_t pad[6];        // 0x00
    int*     begin;         // 0x18
    int*     end;           // 0x1c
    void* find(int key);
};
void* W5af0::find(int key)
{
    int n = (int)((char*)end - (char*)begin) / 0x144;
    for (int i = 0; i < n; i++) {
        int* p = (int*)((char*)begin + i * 0x144);
        if (*p != 0 && *(int*)(*p + 8) == key)
            return p;
    }
    return 0;
}

// ==========================================================================
// @ 0x00705b50  copy a shader-data record, deep-copying its coefficient array
// ==========================================================================
void fn705030() {}
struct V4b { float x, y, z, w; };
struct Big5b50 {
    uint8_t  f0;            // 0x00
    uint8_t  f1;            // 0x01
    uint16_t f2;            // 0x02
    float    f4, f8, fc, f10; // 0x04
    char     pad14[0xc];    // 0x14
    __m128   m20;           // 0x20
    V4b      coeffs[25];    // 0x30
    Big5b50* copy(const Big5b50* s);
};
Big5b50* Big5b50::copy(const Big5b50* s)
{
    f0 = s->f0;
    f1 = s->f1;
    f2 = s->f2;
    f4 = s->f4;
    f8 = s->f8;
    fc = s->fc;
    f10 = s->f10;
    m20 = s->m20;
    sub_406540(&coeffs[0], (void*)&s->coeffs[0], 0x10, 0x19, (void*)fn705030);
    return this;
}

// ==========================================================================
// @ 0x00705c80  grow a vector of 0xb0-byte "light group" records (insert path)
// ==========================================================================
// Each slot is a pointer to a 0xb0-byte record; the head also caches the first
// and last record pointers (plus +0xb0 companions) for the fast inner loops.
struct LightGroup { uint8_t bytes[0xb0]; };
struct LightGroupVec {
    LightGroup** mpBegin;      // +0x00
    unsigned     mnCapacity;   // +0x04  capacity in slots
    uint32_t     mCached08;    // +0x08  copy of mFirst
    uint32_t     mFirst;       // +0x0c  value of *(uint32_t*)mpInsert
    uint32_t     mFirstNext;   // +0x10  mFirst + 0xb0
    LightGroup** mpInsert;     // +0x14
    int32_t      mIndex18;     // +0x18  (count & 3) * 0x2c + mLast
    uint32_t     mLast;        // +0x1c  value of *(uint32_t*)mpEnd[-1]
    uint32_t     mLastNext;    // +0x20  mLast + 0xb0
    LightGroup** mpEnd;        // +0x24
};

// @ 0x00705c80
void FUN_00705c80(void* self, int n, int insertAdvance)
{
    LightGroupVec* v = (LightGroupVec*)self;
    LightGroup** pos = v->mpInsert;
    int tailBytes = (int)((char*)v->mpEnd - (char*)pos);
    int tailCount = (tailBytes >> 2) + 1;
    int newCount  = tailCount + n;
    unsigned cap  = v->mnCapacity;

    LightGroup** dst;
    if ((unsigned)(newCount * 2) < cap) {
        // Room to spare: shift the tail in place and drop the new slot in.
        int shift = (int)((cap - newCount) >> 1) + (insertAdvance ? n : 0);
        dst = v->mpBegin + shift;
        if (dst < pos)
            sub_11e0744(dst, pos, tailBytes + 4);
        else
            sub_13cc480((char*)dst + (tailCount - ((tailBytes + 4) >> 2)) * 4,
                        pos, tailBytes + 4);
    } else {
        // Reallocate: grow to max(capacity, n) + capacity + 2 slots.
        unsigned pick   = (cap >= (unsigned)n) ? cap : (unsigned)n;
        unsigned newCap = pick + cap + 2;
        LightGroup** fresh = (LightGroup**)sub_f473a0(newCap * 4, GRAPHICS, 0, 0,
                                                      ALLOCATOR_H, 0xd1);
        int insertIndex = (int)((char*)v->mpInsert - (char*)v->mpBegin) >> 2;
        dst = fresh + insertIndex + (insertAdvance ? n : 0);
        if (v->mpBegin != 0)
            sub_11e0744(dst, v->mpInsert,
                        (int)((char*)v->mpEnd - (char*)v->mpInsert) + 4);
        if (v->mpBegin != 0)
            sub_f47380(v->mpBegin);
        v->mpBegin = fresh;
        v->mnCapacity = newCap;
    }

    v->mpInsert = dst;
    uint32_t first = *(uint32_t*)dst;
    v->mFirst = first;
    v->mFirstNext = first + 0xb0;
    LightGroup** endp = dst + (tailCount - 1);
    v->mpEnd = endp;
    uint32_t last = *(uint32_t*)endp;
    v->mLast = last;
    v->mLastNext = last + 0xb0;
}

// ==========================================================================
// @ 0x00705db0  build a fresh LightGroupVec: pointer array plus 0xb0-byte records
// ==========================================================================
// @ 0x00705db0
void FUN_00705db0(void* self, unsigned n)
{
    LightGroupVec* v = (LightGroupVec*)self;
    unsigned tailCount = (n >> 2) + 1;
    unsigned candidate = (n >> 2) + 3;
    unsigned cap = (candidate > 8) ? candidate : 8;

    v->mnCapacity = cap;
    LightGroup** base  = (LightGroup**)sub_f473a0(cap * 4, GRAPHICS, 0, 0,
                                                  ALLOCATOR_H, 0xd1);
    LightGroup** first = (LightGroup**)((char*)base + ((cap - tailCount) >> 1) * 4);
    LightGroup** last  = first + tailCount;
    v->mpBegin = base;
    for (LightGroup** it = first; it < last; ++it)
        *it = (LightGroup*)sub_f473a0(0xb0, GRAPHICS, 0, 0, ALLOCATOR_H, 0xd1);

    v->mpInsert = first;
    uint32_t a = *(uint32_t*)first;
    v->mFirst = a;
    v->mFirstNext = a + 0xb0;
    v->mCached08 = v->mFirst;
    LightGroup** endp = last - 1;
    v->mpEnd = endp;
    uint32_t b = *(uint32_t*)endp;
    v->mLast = b;
    v->mLastNext = b + 0xb0;
    v->mIndex18 = (int)((n & 3) * 0x2c + v->mLast);
}

// ==========================================================================
// @ 0x00705740  project a light sample onto its cube face, then split the
//               resulting sample rect into sub-rectangles
// ==========================================================================
// retail's float->int step rounds with cvtss2si and corrects by one (EA's inline ftol);
// cl's plain cast truncates (cvttss2si), so the rounding comes from the asm helper.
static __forceinline int RoundInt_705740(float f) { __asm cvtss2si eax, f }
static __forceinline int FloorInt_705740(float f)
{
    int r = RoundInt_705740(f);
    if (!(f >= (float)r))       // unordered counts as below, like the original's ucomiss/cmovb
        --r;
    return r;
}
static __forceinline int CeilInt_705740(float f)
{
    int r = RoundInt_705740(f);
    if (!((float)r >= f))
        ++r;
    return r;
}

int FUN_006850b0(int, int*, int*);             // rectangle splitter (see slice s00684ee0)

void FUN_00705740(int n, float* b, float scale, int out)
{
    float bx = b[0], by = b[1], bz = b[2];
    float ax = fabsf(bx), ay = fabsf(by), az = fabsf(bz);
    int   face;
    float u;
    if (az >= ax && az >= ay) {                 // dominant axis: z
        face = (bz >= 0.0f) ? 0 : 1;
        u = (bx / bz + 1.0f) * 0.5f;
    } else if (ay >= ax) {                      // dominant axis: y
        face = (by >= 0.0f) ? 4 : 5;
        u = (bz / by + 1.0f) * 0.5f;
    } else {                                    // dominant axis: x
        face = (bx >= 0.0f) ? 2 : 3;
        u = (by / bx + 1.0f) * 0.5f;
    }
    // retail kept the length and the scaled radius in x87 (double intermediates with
    // /arch:SSE), rounding to float only at the store; the face blend stays in SSE.
    float nf = (float)n;
    double len = sqrt((double)by * by + (double)bz * bz + (double)bx * bx);
    float radius = (float)(nf / len * (double)scale);
    // single-precision SSE steps, rounding after every op like the original's addss/mulss chain
    __m128 tv = _mm_set_ss(u);
    tv = _mm_add_ss(tv, _mm_set_ss(1.0f));
    tv = _mm_mul_ss(tv, _mm_set_ss(0.5f));
    tv = _mm_mul_ss(tv, _mm_set_ss(nf));
    tv = _mm_sub_ss(tv, _mm_set_ss(radius));
    volatile float t = _mm_cvtss_f32(tv);
    int rect[5];
    rect[0] = face;
    rect[1] = FloorInt_705740(t);
    rect[2] = FloorInt_705740(t);
    rect[3] = CeilInt_705740(t);
    rect[4] = CeilInt_705740(t);
    FUN_006850b0(n, rect, (int*)out);    // eax is left holding the split count, like retail
}

// ==========================================================================
// @ 0x00705f40  build an "effects-point" renderable for one light sample
// ==========================================================================
// rw::math Matrix33 + a 0x14-byte header that carries the direction, the radius
// and two counts used by the renderable factory.
struct Matrix3 { float m[9]; };
struct LightSampleRecord {        // 0x38 bytes
    uint16_t flags;               // +0x00
    uint16_t count;               // +0x02
    float    dirx;                // +0x04
    float    diry;                // +0x08
    float    dirz;                // +0x0c
    float    radius;              // +0x10
    Matrix3  basis;               // +0x14
};
struct EffectsKey {               // 0x20 bytes
    uint32_t hash;                // +0x00
    uint32_t d04;                 // +0x04
    uint8_t  b08;                 // +0x08
    uint8_t  b09;                 // +0x09
    uint8_t  b0a;                 // +0x0a
    uint8_t  b0b;                 // +0x0b
    uint16_t w0c;                 // +0x0c
    uint8_t  pad0e[2];            // +0x0e
    float    f10;                 // +0x10
    uint32_t d14;                 // +0x14
    uint32_t d18;                 // +0x18
    uint32_t d1c;                 // +0x1c
};
struct LightWorldConfig {
    char  pad[0x138];             // +0x00
    float mScale;                 // +0x138
    float mDivisor;               // +0x13c
};
struct LightWorld {
    char              pad00[0x10]; // +0x00
    LightWorldConfig* mConfig;     // +0x10
    int32_t           mMode18;     // +0x18
    char              pad1c[0x448 - 0x1c];
    void*             mRenderables;// +0x448  vtable: +0x10 create(4,key,rec), +0x14 submit(obj)
};
struct Renderable { char pad[0x38]; float tint[3]; };

// @ 0x00705f40
void FUN_00705f40(void* self, void* a)
{
    LightWorld* lw = (LightWorld*)self;
    float*      p  = (float*)a;

    // Radius / screen-size heuristic; bail out if the sample is too small.
    float t = 1.0f / lw->mConfig->mDivisor;
    t = (t * p[7]) * 2.0f - t * t;
    float r = (p[7] * p[7] - t) * ((p[3] * p[3]) / t);
    if (!(r > g_14853e0))          // r > 4.0f
        return;
    r = sqrtf(r - g_14853e0);      // sqrt(r - 4.0f)
    if (!(r > g_13ec478))          // r > 0.05f
        return;

    LightSampleRecord rec;
    rec.flags  = 0;
    rec.count  = 0;
    rec.dirx   = g_162992c;
    rec.diry   = g_1629930;
    rec.dirz   = g_1629934;
    rec.radius = g_1485720;        // 1.0f
    sub_41cb40(rec.basis.m, &g_1629a74);   // initialise the basis from the template

    rec.dirx = p[4];
    rec.flags |= 4;
    rec.diry = p[5];
    rec.dirz = p[6];
    rec.count += 2;
    rec.radius = r;
    if (lw->mMode18 == 2) {
        float tmp[9];
        sub_6983a0(p + 4, tmp);    // SP::MatrixFromDirection (writes the 2nd arg)
        sub_11e0744(rec.basis.m, tmp, 0x24);
        rec.flags |= 2;
        rec.count += 1;
    }

    // FNV-hash key for the "effects-point" renderable.
    EffectsKey key;
    key.hash = 0xffffffff;
    key.d04  = 0xffffffff;
    key.b08  = 0; key.b09 = 0; key.b0a = 0; key.b0b = 0;
    key.w0c  = 0;
    key.f10  = 0.0f;
    key.d18  = 0xffffffff;
    key.d1c  = 0xffffffff;

    unsigned h = sub_932e80(EFFECTS_POINT, 0x811c9dc5, 1);
    key.b0a |= 1;
    key.hash = h;
    key.d04  = 0;
    key.b09  = 4;

    void* mgr = lw->mRenderables;
    void* obj = ((void* (__thiscall*)(void*, int, void*, void*))
                 (*(void***)mgr)[0x10 / 4])(mgr, 4, &key, &rec);
    *(void**)(p + 8) = obj;

    float* tint = ((Renderable*)obj)->tint;
    float  scale = lw->mConfig->mScale;
    tint[0] = scale * p[0];
    tint[1] = p[1] * scale;
    tint[2] = p[2] * scale;

    mgr = lw->mRenderables;
    ((void (__thiscall*)(void*, void*))(*(void***)mgr)[0x14 / 4])(mgr,
        *(void**)(p + 8));
}
