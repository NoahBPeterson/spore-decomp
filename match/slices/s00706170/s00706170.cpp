// Slice s00706170 (batch w2g1, slice 36): lighting-config ctor/dtor,
// slot-vector iterators, EASTL vector allocation/copy helpers.
#include "types.h"
#include <xmmintrin.h>
#include <math.h>

void  sub_f47380(void*);                          // operator delete
void* sub_f473d0(int, int, int, const char*, int, int, const char*, int);
void* sub_f473a0(unsigned, const char*, int, int, int, int);
void  sub_705b50(void);                           // copy-ctor body (0x00705b50)
void  sub_e5c780(void);                           // rbtree find (0x00e5c780)

struct IVoid { virtual void v0(); virtual void v1(); };

// ==========================================================================
// @ 0x00706870
// ==========================================================================
struct W6870 {
    int* m0;
    int get(unsigned idx);
};
int W6870::get(unsigned idx)
{
    return m0[idx >> 7] + 0x10 + (idx & 0x7f) * 0x1f0;
}

// ==========================================================================
// @ 0x00706890
// ==========================================================================
struct W6890 {
    int* m0;
    int get(unsigned idx);
};
int W6890::get(unsigned idx)
{
    return m0[idx >> 7] + 4 + (idx & 0x7f) * 0x38;
}

// ==========================================================================
// @ 0x00706920 / 00706980 / 007069e0  slot-vector "next" scan
// ==========================================================================
struct W6920 {
    int** m0;
    unsigned next(unsigned idx);
};
unsigned W6920::next(unsigned idx)
{
    unsigned v = *(unsigned*)((idx & 0x7f) * 0xc4 + (char*)m0[idx >> 7]);
    do {
        if ((v >> 30) & 1)
            return 0x3fffffff;
        ++idx;
        v = *(unsigned*)((idx & 0x7f) * 0xc4 + (char*)m0[idx >> 7]);
    } while ((int)v < 0);
    return idx;
}

struct W6980 {
    int** m0;
    unsigned next(unsigned idx);
};
unsigned W6980::next(unsigned idx)
{
    unsigned v = *(unsigned*)((idx & 0x7f) * 0x1f0 + (char*)m0[idx >> 7]);
    do {
        if ((v >> 30) & 1)
            return 0x3fffffff;
        ++idx;
        v = *(unsigned*)((idx & 0x7f) * 0x1f0 + (char*)m0[idx >> 7]);
    } while ((int)v < 0);
    return idx;
}

struct W69e0 {
    int** m0;
    unsigned next(unsigned idx);
};
unsigned W69e0::next(unsigned idx)
{
    unsigned v = *(unsigned*)((idx & 0x7f) * 0x1e0 + (char*)m0[idx >> 7]);
    do {
        if ((v >> 30) & 1)
            return 0x3fffffff;
        ++idx;
        v = *(unsigned*)((idx & 0x7f) * 0x1e0 + (char*)m0[idx >> 7]);
    } while ((int)v < 0);
    return idx;
}

// ==========================================================================
// @ 0x007067f0  SP::cLightingConfig::~cLightingConfig
// ==========================================================================
struct W67f0 {
    char pad0[0xa8];
    void* pA8;              // 0xa8
    char padAC[0x10];
    void* pBC;              // 0xbc
    ~W67f0();
};
W67f0::~W67f0()
{
    void* p = pBC;
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        sub_f47380(p);
    p = pA8;
    if (p != 0 && *(int*)((char*)p - 4) != 0)
        sub_f47380(p);
    void* q = *(void**)this;
    if (q != 0)
        ((IVoid*)q)->v1();
}

// ==========================================================================
// @ 0x007068c0  copy the shading record plus its tail scalars
// ==========================================================================
struct W68c0 {
    char pad[0x1c0];
    float f1c0, f1c4, f1c8;
    int   f1cc, f1d0;
    W68c0* copyFrom(const W68c0* s);
};
W68c0* W68c0::copyFrom(const W68c0* s)
{
    ((void*(__thiscall*)(void*, const void*))&sub_705b50)(this, s);
    f1c0 = s->f1c0;
    f1c4 = s->f1c4;
    f1c8 = s->f1c8;
    f1cc = s->f1cc;
    f1d0 = s->f1d0;
    return this;
}

// ==========================================================================
// @ 0x00706ab0  forward copy of 16-byte elements keeping a pointer offset
// ==========================================================================
void FUN_00706ab0(__m128* first, __m128* last, __m128* out)
{
    if (first != last) {
        int offset = (int)((char*)first - (char*)out);
        do {
            if (out != 0)
                *(__m128*)out = *(__m128*)((char*)out + offset);
            out = (__m128*)((char*)out + 16);
        } while ((__m128*)((char*)out + offset) != last);
    }
}

// ==========================================================================
// @ 0x00706af0  allocate a vector of 0x20-byte elements
// ==========================================================================
struct Vec20 { void* b; void* e; void* c; Vec20* init(int n, int unused); };
Vec20* Vec20::init(int n, int unused)
{
    (void)unused;
    if (n != 0) {
        void* p = sub_f473d0(n << 5, 0x10, 0, "Graphics", 0, 0,
                             "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xe5);
        b = p;
        e = p;
        c = (char*)p + (n << 5);
    } else {
        b = 0; e = 0; c = 0;
    }
    return this;
}

// ==========================================================================
// @ 0x00706d00  allocate a vector of 0x10-byte elements
// ==========================================================================
struct Vec10 { void* b; void* e; void* c; Vec10* init(int n, int unused); };
Vec10* Vec10::init(int n, int unused)
{
    (void)unused;
    if (n != 0) {
        void* p = sub_f473d0(n << 4, 0x10, 0, "Graphics", 0, 0,
                             "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xe5);
        b = p;
        e = p;
        c = (char*)p + (n << 4);
    } else {
        b = 0; e = 0; c = 0;
    }
    return this;
}

// ==========================================================================
// @ 0x00706c80  forward copy of 9-dword elements (destination nullable)
// ==========================================================================
struct E9 { int a; float b, c, d, e, f, g, h, i; };
void FUN_00706c80(E9** out, E9* first, E9* last, E9* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst != 0) {
                dst->a = first->a;
                dst->b = first->b;
                dst->c = first->c;
                dst->d = first->d;
                dst->e = first->e;
                dst->f = first->f;
                dst->g = first->g;
                dst->h = first->h;
                dst->i = first->i;
            }
            ++first;
            ++dst;
        } while (first != last);
        *out = dst;
    }
}

// ==========================================================================
// @ 0x00706d60  run destructors over an array of 0x144-byte records
// ==========================================================================
struct E144 {
    void*  p0;              // 0x00
    char   pad04[0xa4];     // 0x04
    void*  pA8;             // 0xa8
    char   padAC[0x10];     // 0xac
    void*  pBC;             // 0xbc
};
int FUN_00706d60(E144* first, E144* last, int result)
{
    if (first == last)
        return result;
    do {
        void* p = first->pBC;
        if (p != 0 && *(int*)((char*)p - 4) != 0)
            sub_f47380(p);
        p = first->pA8;
        if (p != 0 && *(int*)((char*)p - 4) != 0)
            sub_f47380(p);
        if (first->p0 != 0)
            ((IVoid*)first->p0)->v1();
        first = (E144*)((char*)first + 0x144);
        result += 0x144;
    } while (first != last);
    return result;
}

// ==========================================================================
// @ 0x00706840  SP::cLightingManager::GetLightingWorld
// ==========================================================================
struct TreeFind { void find(void* result, void* key); };
struct W6840 {
    char pad0[0x2c];        // 0x00
    TreeFind tree;          // 0x2c  (rbtree with anchor at 0x30)
    int GetLightingWorld(int key);
};
int W6840::GetLightingWorld(int key)
{
    void* it;
    tree.find(&it, &key);
    if (it != (char*)this + 0x30)
        return *(int*)((char*)it + 0x14);
    return 0;
}

// ==========================================================================
// @ 0x00706170  SP::cLightingWorld::UpdateEnvLightSample (thiscall, ret 4)
// Evaluates the environment lighting (atmosphere ZH coefficients blended by the sun
// elevation, plus optional ground bounce and a zenith term) for one cache sample and
// writes the resulting SH coefficients into the sample.
// ==========================================================================
struct Vec3f { float x, y, z; };
struct Mat3f { float m[9]; };
struct V4Ret { __m128 v; float f(int i) const { return ((const float*)&v)[i]; } };

// SH helpers (cdecl): see symbols/slices/s00784420.txt, s00783590.txt, s00782860.txt
void SH_Accumulate(const float* dir, int n, const __m128* in, __m128* out);      // 0x00794e60 -> 0x00784560
void SH_RotateZHAdd(const float* dir, int n, const __m128* in, __m128* out);     // 0x00794e70 -> 0x00785500
void SH_Rotate(const Mat3f* m, int n, const __m128* in, __m128* out);            // 0x00795eb0 -> 0x007864c0
void SH_AddGroundBounce(int n, __m128* buf, const __m128* a, const __m128* b);   // 0x00784420
void SH_ZonalCoeffs(float t, float* out);                                        // 0x007831d0
void SH_ApplyNormalizationConstants(int n, __m128* buf);                         // 0x00783590
void MatrixFromDirection(const Vec3f* dir, Mat3f* out);                          // 0x006983a0
extern float g_0162991c, g_016299f4, g_01629ad8, g_01629928;     // 0x0162991c, 0x016299f4, 0x01629ad8, 0x01629928

struct SHGroundQuery {
    virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3();
    virtual void q4(); virtual void q5(); virtual void q6(); virtual void q7();
    virtual void q8(); virtual void q9(); virtual void q10();
    virtual V4Ret Query(const Vec3f* pos);                                       // +0x2c
};

struct LightCfg {
    char pad00[0xbc];
    __m128* vecBegin;                // +0xbc
    __m128* vecEnd;                  // +0xc0
    char padc4[0x18];
    float groundScaleB;              // +0xdc
    float groundScaleA;              // +0xe0
    char pade4[0x20];
    float zhColor[4];                // +0x104
    float riseBias;                  // +0x114
    float riseScale;                 // +0x118
    float setBias;                   // +0x11c
    float setScale;                  // +0x120
    float baseA;                     // +0x124
    float baseB;                     // +0x128
};

struct EnvSample {
    char pad00;
    unsigned char bandsByte;         // +1
    char pad02[2];
    Vec3f sunDir;                    // +4
    float blendA;                    // +0x10
    char pad14[0xc];
    __m128 hdr;                      // +0x20
    __m128 coeffs[25];               // +0x30 ...
    Vec3f pos;                       // +0x1c0
    char pad1cc[4];
    int groundFlag;                  // +0x1d0
};

struct EnvLW {
    char pad00[0x10];
    LightCfg* cfg;                   // +0x10
    char pad14[0x20];
    int nBands;                      // +0x34 (vector count)
    int nOut;                        // +0x38
    char pad3c[0x98];
    float lightPos[3];               // +0xd4
    char padE0[0x10];
    __m128 dayCoeffs[7];             // +0xf0
    __m128 nightCoeffs[7];           // +0x160
    char padD0[0x240 - 0x160 - 7 * 16];
    Vec3f sunDir;                    // +0x240
    SHGroundQuery* ground;           // +0x24c

    void UpdateEnvLightSample(EnvSample* out);
};

static inline void Clamp01(float* x, const float* hi)
{
    _mm_store_ss(x, _mm_min_ss(_mm_max_ss(_mm_setzero_ps(), _mm_load_ss(x)), _mm_load_ss(hi)));
}

// @ 0x00706170
void EnvLW::UpdateEnvLightSample(EnvSample* out)
{
    __m128 R, tmp[7], buf180[49], buf490[49], rz[7];
    float zh[8];
    Mat3f m;

    MatrixFromDirection(&out->pos, &m);
    LightCfg* cfg = this->cfg;
    const Vec3f* dir = &sunDir;
    float t0 = (dir->y * m.m[7] + dir->z * m.m[8]) + dir->x * m.m[6];
    float blend = 0.0f;
    float one = 1.0f;
    if (t0 > 0.0f) {
        float x = (t0 - cfg->riseBias) * cfg->riseScale;
        Clamp01(&x, &one);
        for (int i = 0; i < nBands; i++)
            tmp[i] = _mm_add_ps(_mm_mul_ps(_mm_sub_ps(dayCoeffs[i], nightCoeffs[i]), _mm_set1_ps(x)), nightCoeffs[i]);
    } else {
        float x = (-t0 - cfg->setBias) * cfg->setScale;
        Clamp01(&x, &one);
        for (int i = 0; i < nBands; i++)
            tmp[i] = _mm_mul_ps(_mm_set1_ps(1.0f - x), nightCoeffs[i]);
        blend = x;
    }

    Vec3f d;
    d.x = lightPos[0] - out->pos.x;
    d.y = lightPos[1] - out->pos.y;
    d.z = lightPos[2] - out->pos.z;
    float inv = 1.0f / (float)sqrt(d.x * d.x + d.y * d.y + d.z * d.z);
    float c = (dir->z * (d.z * inv) + dir->y * (d.y * inv)) + dir->x * (inv * d.x);
    float c2 = c * c;
    __m128 cc = _mm_set1_ps(c);
    R = _mm_add_ps(_mm_add_ps(_mm_mul_ps(_mm_mul_ps(_mm_set1_ps(g_0162991c), tmp[1]), cc),
                              _mm_mul_ps(_mm_set1_ps(g_016299f4), tmp[0])),
                   _mm_mul_ps(_mm_mul_ps(_mm_set1_ps(g_01629ad8), tmp[2]), _mm_set1_ps(c2 * 3.0f - 1.0f)));
    R = _mm_add_ps(R, _mm_mul_ps(_mm_mul_ps(_mm_mul_ps(_mm_set1_ps(g_01629928), tmp[3]), cc),
                                 _mm_set1_ps(c2 * 5.0f - 3.0f)));

    if (blend < 1.0f) {
        if (out->groundFlag >= 0 && ground != 0 &&
            (out->pos.x * out->pos.x + out->pos.y * out->pos.y) + out->pos.z * out->pos.z > 10.0f) {
            Vec3f d2;
            d2.x = m.m[0] * dir->x + m.m[1] * dir->y + m.m[2] * dir->z;
            d2.y = m.m[3] * dir->x + m.m[4] * dir->y + m.m[5] * dir->z;
            d2.z = m.m[6] * dir->x + m.m[7] * dir->y + m.m[8] * dir->z;
            SH_Accumulate(&d2.x, nBands, tmp, buf490);
            V4Ret g = ground->Query(&out->pos);
            __m128 P = _mm_set_ps(g.f(3), g.f(2), g.f(1), g.f(0));
            __m128 va = _mm_mul_ps(_mm_set1_ps(cfg->groundScaleA), P);
            __m128 vb = _mm_mul_ps(_mm_set1_ps(cfg->groundScaleB), P);
            SH_AddGroundBounce(nBands, buf490, &vb, &va);
            SH_Rotate(&m, nBands, buf490, buf180);
        } else {
            SH_Accumulate(&dir->x, nBands, tmp, buf180);
        }
    }

    if (blend > 0.0f) {
        SH_ZonalCoeffs(cfg->zhColor[3], zh);
        for (int i = 0; i < nBands; i++) {
            float z = zh[i];
            float r0 = z * (cfg->zhColor[0] * blend);
            float r1 = z * (blend * cfg->zhColor[1]);
            float r2 = z * (blend * cfg->zhColor[2]);
            float r3 = z * (blend * cfg->zhColor[3]);
            rz[i] = _mm_set_ps(r3, r2, r1, r0);
        }
        if (blend >= 1.0f)
            SH_Accumulate(&m.m[6], nBands, rz, buf180);
        else
            SH_RotateZHAdd(&m.m[6], nBands, rz, buf180);
    }

    SH_ApplyNormalizationConstants(nBands, buf180);
    out->bandsByte = (unsigned char)nOut;
    for (int i = 0; i < nOut; i++)
        out->coeffs[i] = buf180[i];
    out->sunDir = *dir;
    out->blendA = (cfg->baseB - cfg->baseA) * blend + cfg->baseA;
    out->hdr = R;
    ((float*)&out->hdr)[3] = blend;

    LightCfg* c3 = this->cfg;
    if (c3->vecBegin != c3->vecEnd) {
        int cnt = (int)(c3->vecEnd - c3->vecBegin);
        const int* pm = (nOut < cnt) ? &nOut : &cnt;
        for (int i = 0; i < *pm; i++)
            out->coeffs[i] = _mm_add_ps(this->cfg->vecBegin[i], out->coeffs[i]);
    }
}

// ==========================================================================
// @ 0x00706b50  PARTIAL: vector push_back of 0xb0-byte records
// ==========================================================================
void FUN_00706b50(void* self, void* a) { (void)self; (void)a; }

// ==========================================================================
// @ 0x00706dd0  PARTIAL: 756-byte SP::cLightingConfig constructor
// ==========================================================================
void FUN_00706dd0(void* self) { (void)self; }
