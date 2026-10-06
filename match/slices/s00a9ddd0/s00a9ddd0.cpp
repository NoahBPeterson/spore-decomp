// s00a9ddd0: Swarm particle spawner, "initialise one new particle" (cl1_new slice 24).
// Class and field names are Claude-coined from usage (retail layout differs from the 2008 PDB's
// EA::Swarm::cParticlesEffect, which has mDesc at +0x24); particle layout matches EA::Swarm::cParticle.
#include "types.h"
#include <math.h>
// flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast

struct Vec3 { float x, y, z; };
static inline bool Bit(uint32_t v, int n) { return (v >> n) & 1; }
struct Vec4 { float x, y, z, w; };

struct RandomLinearCongruential { double RandomDoubleUniform(); };
extern RandomLinearCongruential g_Random;   // 0x016778dc (sRandom_Swarm)

// Uniform random in [lo, hi], clamped (inlined helper in the original).
static inline double RandRange(double lo, double hi)
{
    double r = g_Random.RandomDoubleUniform();
    double v = r * (hi - lo) + lo;
    if (v < hi) {
        if (v < lo) return lo;
        return v;
    }
    return hi;
}

// 3x3 + translation transform (flags bit 1 = has rotation).
struct Xform {
    uint32_t flags;      // +0x00 (this+0x30)
    Vec3 t;              // +0x04
    float scale;         // +0x10
    float m[9];          // +0x14 (this+0x44)
    void Transform(Vec3* v);   // FUN_007cdee0 (thiscall)
};

// Particle effect instance (object returned by the factory, a refcounted COM-like object).
struct FxObj {
    virtual void v0();
    virtual void v1();
    virtual void v2(int a);                                  // +0x08
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6(void* s, Xform* x);                      // +0x18
    virtual void v7();
    virtual void v8(int idx, uint32_t* p, int n);            // +0x20
    virtual void v9(int a, uint32_t b);                      // +0x24
    virtual void v10(int a);                                 // +0x28
    virtual void v11();
    virtual void v12();
    virtual void AddRef();                                   // +0x34
    virtual void Release();                                  // +0x38
};

struct FxFactory {
    FxObj* Create(uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // FUN_00a714f0
};

struct FxSub { uint32_t w[13]; };                // 0x34 bytes (desc+0x200 array)
struct FxState { uint32_t w[6]; };               // 0x18 bytes (particle+0x4c array)
void FxStateInit(FxState* st, FxSub* sub, Vec3* dir, int flag);   // FUN_00a79430 (thiscall, see below)

struct Desc {
    uint32_t pad0[2];
    uint32_t flags[2];       // +0x08 (64-bit bitset: low word, high word)
    float lifeMin;           // +0x10
    float lifeMax;           // +0x14
    uint32_t pad18[5];
    uint32_t emitDir[6];     // +0x2c
    uint32_t emitSpeed[8];   // +0x44
    float f64;               // +0x64
    uint32_t pad68[7];
    float* p84;              // +0x84
    uint32_t pad88[4];
    float sizeVary;          // +0x98
    uint32_t pad9c[15];
    float fd8, fdc, fe0;     // +0xd8
    uint32_t pade4[8];
    float vary104, vary108, vary10c;   // +0x104
    uint32_t pad110[5];
    float vary124;           // +0x124
    uint32_t key128;         // +0x128
    uint32_t key12c;         // +0x12c
    uint32_t pad130;
    uint8_t mode134;         // +0x134
    uint8_t pad135[3];
    uint32_t pad138[8];
    float attract;           // +0x158
    Vec3 attractPos;         // +0x15c
    uint32_t pad168[38];
    FxSub subs[2];           // +0x200
    uint32_t pad268[16];
    uint32_t obj2a8[1];      // +0x2a8
};

struct Particle {
    uint32_t node[2];
    float age;               // +0x08
    float life;              // +0x0c
    Vec3 pos;                // +0x10
    Vec3 vel;                // +0x1c
    float size;              // +0x28
    float aspect;            // +0x2c
    float rotation;          // +0x30
    float alpha;             // +0x34
    Vec3 color;              // +0x38
    uint32_t pad44;
    float f48;               // +0x48
    FxState st[2];           // +0x4c
    FxObj* fx;               // +0x7c
    float quat[4];           // +0x80
    int index;               // +0x90
    float f94, f98, f9c;     // +0x94
};

struct Sampler {             // vtable object at this+0x19c
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(); virtual void s4(); virtual void s5();
    virtual bool Contains(Vec3* p);                 // +0x18
    virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10();
    virtual Vec4* Sample(Vec4* out, Vec3* p);       // +0x2c
};

struct HitObj {              // SpawnRec::a
    virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3();
    virtual bool Collide(Vec3* a, Vec3* b, Vec3* out, float* quat, int pa, int pb);   // +0x10
    virtual void h5(); virtual void h6(); virtual void h7(); virtual void h8(); virtual void h9();
    virtual void h10();
    virtual void Apply(uint32_t* spec, int dst, void* arg);                           // +0x2c
};

struct SpawnRec {
    HitObj* a;               // +0x00
    uint32_t* b;             // +0x04
    int has8;                // +0x08
    int c;                   // +0x0c
    int has10;               // +0x10
    int c14;                 // +0x14
};

// Callees (unnamed)
bool FUN_00a79660(void* base, void* v);                   // cdecl
Vec3* FUN_00a817c0(Vec3* out, Vec3* in, float f);         // cdecl
Vec3* FUN_00a81580(Vec3* out, Vec3* in);                  // cdecl
Vec3* FUN_007cdbe0(Vec3* out, void* in);                  // cdecl
float FUN_007cdb90(void* in);                             // cdecl
float FUN_00a78f80(float f);                              // cdecl
float* QuatFromMatrix33(float* out, float* m, float z);   // 0x472b80 cdecl

extern uint32_t g_Mask[2];     // 0x01678f3c (bitset mask)
extern const float kZero;      // 0x01485378
extern const float kOne;       // 0x01485720
extern uint32_t g_Mask5430;    // 0x01565430
extern float g_HalfPi;         // 0x01565424
extern float g_Inv;            // 0x01678ffc
extern float g_Mat9[9];        // 0x01679010

struct SpawnArgs {
    short kind, one;
    Vec3 pos;
    float s;
    float m[9];
};

struct ParticleEmitter {
    uint32_t pad0[3];
    Desc* desc;                  // +0x0c
    uint32_t u10;                // +0x10
    FxFactory* factory;          // +0x14
    uint32_t pad18;
    uint32_t u1c;                // +0x1c
    uint8_t pad20[2];
    uint8_t b22;                 // +0x22
    uint8_t pad23[0xd];
    Xform xf30;                  // +0x30
    Xform xf68;                  // +0x68
    uint32_t pada0[(0x13c - 0xa0) / 4];
    float f13c;                  // +0x13c
    uint32_t pad140;
    float f144;                  // +0x144
    uint32_t pad148[(0x19c - 0x148) / 4];
    Sampler* sampler;            // +0x19c
    uint8_t pad1a0[2];
    uint8_t b1a2;                // +0x1a2
    uint8_t pad1a3;
    Vec3 v1a4;                   // +0x1a4
    uint32_t pad1b0[3];
    SpawnRec* recBegin;          // +0x1bc
    SpawnRec* recEnd;            // +0x1c0
    uint32_t pad1c4[4];
    int i1d4;                    // +0x1d4
    uint32_t pad1d8[4];
    int i1e8;                    // +0x1e8
    uint32_t pad1ec[4];
    int i1fc;                    // +0x1fc
    uint32_t pad200[5];
    uint8_t b214;                // +0x214
    uint8_t pad215[3];
    uint32_t p218, p21c;         // +0x218
    uint32_t pad220[3];
    uint8_t b22c;                // +0x22c
    uint8_t pad22d[3];
    uint32_t u230;               // +0x230
    int i234;                    // +0x234
    uint32_t u238, u23c;         // +0x238
    uint32_t u240, u244;         // +0x240

    bool CheckSpawn(Particle* p);          // FUN_00a9c710
    bool InitParticle(Particle* p);        // @ 0x00a9ddd0
};

static inline float AtanApprox(float y, float x)
{
    float ay = fabsf(y) + 1e-10f;
    float ax = fabsf(x);
    float r = (ay - ax) / (ax + ay);
    r = (0.9817f - (r * r) * 0.1963f) * r;
    if (x < 0.0f) r = g_HalfPi * 3.0f - r;
    else r = r + g_HalfPi;
    if (y < 0.0f) r = -r;
    return r;
}

// @ 0x00a9ddd0
bool ParticleEmitter::InitParticle(Particle* p)
{
    bool fromVolume;
    bool hasQuat;
    Vec3 tmp;
    Vec3 dir;
    float spd;
    float nx, ny, nz;
    Vec4 col;
    Vec3 hit;

    p->age = 0.0f;
    p->life = (float)(RandRange(desc->lifeMin, desc->lifeMax) * f144);

    if (Bit(desc->flags[0], 0x1a)) {
        uint32_t* r = &p218;
        if (p218 == p21c) r = (uint32_t*)((char*)desc + 0x2a8);
        if (FUN_00a79660(&p->age, r)) {
            fromVolume = true;
            goto after_pos;
        }
    }
    fromVolume = false;
    {
        Desc* d = desc;
        Vec3* v;
        if (d->f64 >= kZero) {
            p->pos = *FUN_00a817c0(&tmp, &v1a4, d->f64);
        } else {
            if (Bit(d->flags[0], 4))
                v = FUN_00a81580(&tmp, &v1a4);
            else
                v = FUN_007cdbe0(&tmp, &v1a4);
            p->pos = *v;
        }
    }

    if ((desc->flags[0] & g_Mask[0]) | (desc->flags[1] & g_Mask[1])) {
        if (!CheckSpawn(p))
            return false;
    }

    {
        Vec3* v = FUN_007cdbe0(&tmp, desc->emitDir);
        dir = *v;
        spd = FUN_007cdb90(desc->emitSpeed) * f13c;
        p->vel = dir;
        float l2 = (p->vel.x * p->vel.x + p->vel.y * p->vel.y) + p->vel.z * p->vel.z;
        if (l2 > 0.0f) {
            float s = spd / sqrtf(l2);
            p->vel.x = p->vel.x * s;
            p->vel.y = p->vel.y * s;
            p->vel.z = s * p->vel.z;
        }
        Desc* d = desc;
        float k = d->attract;
        if (k != 0.0f) {
            float dy = p->pos.y - d->attractPos.y;
            float dz = p->pos.z - d->attractPos.z;
            float dx = p->pos.x - d->attractPos.x;
            float m2 = (dz * dz + dy * dy) + dx * dx;
            if (m2 > 1e-6f) {
                float s = k / sqrtf(m2);
                p->vel.x = p->vel.x + dx * s;
                p->vel.y = dy * s + p->vel.y;
                p->vel.z = dz * s + p->vel.z;
            }
        }
    }

after_pos:
    {
        float v;
        v = desc->sizeVary;
        p->size = (float)RandRange(1.0 - v, v + 1.0);
        v = desc->vary124;
        p->alpha = (float)RandRange(1.0 - v, v + 1.0);
        v = desc->vary104;
        p->color.x = (float)RandRange(1.0 - v, v + 1.0);
        v = desc->vary108;
        p->color.y = (float)RandRange(1.0 - v, v + 1.0);
        v = desc->vary10c;
        p->color.z = (float)RandRange(1.0 - v, v + 1.0);
    }

    if (sampler) {
        tmp = p->pos;
        if (b1a2) {
            xf30.Transform(&tmp);
            xf68.Transform(&tmp);
        }
        if (sampler->Contains(&tmp)) {
            sampler->Sample(&col, &p->pos);
            p->alpha = col.w * p->alpha;
            p->color.x = p->color.x * col.x;
            p->color.y = p->color.y * col.y;
            p->color.z = p->color.z * col.z;
        }
    }

    {
        float v = desc->fd8;
        p->f98 = (v > kZero) ? FUN_00a78f80(v) : kOne;
        v = desc->fdc;
        p->f9c = (v > kZero) ? FUN_00a78f80(v) : kOne;
        v = desc->fe0;
        p->f94 = (v > kZero) ? FUN_00a78f80(v) : kOne;
    }

    if (Bit(desc->flags[0], 0xb))
        p->size = xf30.scale * p->size;

    Vec3* pv = &p->pos;
    if (xf30.flags & 2) {
        float y = pv->y, z = pv->z, x = pv->x;
        nx = (xf30.m[3] * y + xf30.m[6] * z) + xf30.m[0] * x;
        ny = (xf30.m[1] * x + xf30.m[4] * y) + xf30.m[7] * z;
        nz = (xf30.m[2] * x + xf30.m[5] * y) + xf30.m[8] * z;
        pv->x = nx; pv->y = ny; pv->z = nz;
    }
    {
        float s = xf30.scale;
        float x = pv->x;
        pv->z = pv->z * s;
        pv->y = s * pv->y;
        pv->x = x * s;
        pv->x = pv->x + xf30.t.x;
        pv->y = xf30.t.y + pv->y;
        pv->z = xf30.t.z + pv->z;
    }

    {
        FxObj* n = factory->Create(desc->key12c, desc->key128, u10, u1c);
        FxObj* old = p->fx;
        if (n != old) {
            if (n) n->AddRef();
            p->fx = n;
            if (old) old->Release();
        }
    }

    if (i1fc != 0) {
        void* arg = 0;
        if (desc->key12c == 0) {
            if (p->fx) arg = (char*)p->fx - 4;
        }
        int off = p->index * i1fc + i1e8;
        for (SpawnRec* r = recBegin; r != recEnd; r++) {
            if (r->has10)
                r->a->Apply(r->b, r->c14 + off, arg);
        }
    }

    p->quat[3] = kOne;
    hasQuat = false;
    if (b214) {
        int baseA = i1d4;
        int baseB = p->index * i1fc + i1e8;
        for (SpawnRec* r = recBegin; r != recEnd; r++) {
            if ((*r->b & g_Mask5430) == 0)
                continue;
            int pa = r->has8 ? r->c + baseA : 0;
            int pb = r->has10 ? r->c14 + baseB : 0;
            if (Bit(desc->flags[1], 2) == 0) {
                if (r->a->Collide(pv, pv, &hit, 0, pa, pb)) {
                    float sc = ((float*)r->b)[8];
                    if (sc != 0.0f) {
                        pv->x = pv->x + hit.x * sc;
                        pv->y = hit.y * sc + pv->y;
                        pv->z = hit.z * sc + pv->z;
                    }
                    break;
                }
            } else {
                if (r->a->Collide(pv, pv, &hit, p->quat, pa, pb)) {
                    float sc = ((float*)r->b)[8];
                    if (sc != 0.0f) {
                        pv->x = hit.x * sc + pv->x;
                        pv->y = hit.y * sc + pv->y;
                        pv->z = hit.z * sc + pv->z;
                    }
                    if (Bit(desc->flags[1], 3)) {
                        float* q = QuatFromMatrix33((float*)&col, xf30.m, 0.0f);
                        p->quat[0] = q[0];
                        p->quat[1] = q[1];
                        p->quat[2] = q[2];
                        p->quat[3] = q[3];
                    }
                    float qx = p->quat[0], qy = p->quat[1], qz = p->quat[2], qw = p->quat[3];
                    float zy = qz * qy;
                    float yx = qy * qx;
                    float wy = qw * qy;
                    float vx = p->vel.x;
                    nx = ((wy + qz * qx) * p->vel.z + (yx - qw * qz) * p->vel.y) * 2.0f
                         + (1.0f - (qz * qz + qy * qy) * 2.0f) * vx;
                    ny = ((qw * qz + yx) * vx + (zy - qw * qx) * p->vel.z) * 2.0f
                         + (1.0f - (qz * qz + qx * qx) * 2.0f) * p->vel.y;
                    nz = ((qz * qx - wy) * vx + (qw * qx + zy) * p->vel.y) * 2.0f
                         + (1.0f - (qy * qy + qx * qx) * 2.0f) * p->vel.z;
                    hasQuat = true;
                    goto store_vel;
                }
            }
        }
    }
    if (xf30.flags & 2) {
        float y = p->vel.y, z = p->vel.z, x = p->vel.x;
        nx = (xf30.m[3] * y + xf30.m[6] * z) + x * xf30.m[0];
        ny = (xf30.m[1] * x + xf30.m[4] * y) + xf30.m[7] * z;
        nz = (xf30.m[2] * x + xf30.m[5] * y) + xf30.m[8] * z;
store_vel:
        p->vel.x = nx;
        p->vel.y = ny;
        p->vel.z = nz;
    }

    if (!fromVolume && Bit(desc->flags[0], 3)) {
        float g = **(float**)&desc->p84;
        float inv = 1.0f / spd;
        pv->x = ((p->vel.x * 0.5f) * g) * inv + pv->x;
        pv->y = ((p->vel.y * 0.5f) * g) * inv + pv->y;
        pv->z = ((p->vel.z * 0.5f) * g) * inv + pv->z;
    }

    if (!hasQuat && desc->mode134 == 1) {
        float inv = 1.0f / g_Inv;
        p->f9c = inv * AtanApprox(xf30.m[1], xf30.m[0]) + p->f9c;
        p->f98 = inv * AtanApprox(xf30.m[1], xf30.m[0]) + p->f98;
        p->f94 = inv * AtanApprox(xf30.m[1], xf30.m[0]) + p->f94;
    }

    {
        uint8_t m = desc->mode134;
        if (m < 2 || m > 4) {
            if (!hasQuat)
                p->f48 = (1.0f / g_Inv) * AtanApprox(xf30.m[1], xf30.m[0]);
        } else {
            *(uint32_t*)&p->f48 = 0xc479c000;
        }
    }

    if (p->fx) {
        if (b22c)
            p->fx->v9(0, u230);
        if ((u238 & u23c) != 0xffffffff)
            p->fx->v8(0, &u238, 1);
        if ((u240 & u244) != 0xffffffff)
            p->fx->v8(1, &u240, 1);
        if (i234 >= 0)
            p->fx->v8(2, (uint32_t*)&i234, 1);
        SpawnArgs a;
        a.kind = 4;
        a.one = 1;
        a.pos = *pv;
        a.s = 1.0f;
        for (int i = 0; i < 9; i++) a.m[i] = g_Mat9[i];
        p->fx->v6(&a, &xf68);
        if (!b22)
            p->fx->v10(0);
        p->fx->v2(0);
    }

    if (!fromVolume && Bit(desc->flags[0], 0x14)) {
        int f = (desc->flags[0] >> 0x15) & 1;
        for (int i = 0; i < 2; i++)
            FxStateInit(&p->st[i], &desc->subs[i], &dir, f);
    }
    return true;
}
