// s00aae8c0: Swarm particle effect, "initialise one new particle" @ 0x00aaeb90 (2510 bytes).
// Sister of ParticleEmitter::InitParticle @ 0x00a9ddd0 (slice s00a9ddd0): the same spawn steps
// (life, emit volume, spawn check, velocity, attractor, per-particle variances, colour sampler,
// emitter transform, collision surfaces) for a second effect class whose fields sit at other
// offsets. Class, field and helper names are Claude-coined from usage; the particle layout matches
// EA::Swarm::cParticle.
// flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Vec4 { float x, y, z, w; };
static inline bool Bit(uint32_t v, int n) { return (v >> n) & 1; }
static inline bool TestAny(const uint32_t* w, const uint32_t* m) { return ((w[0] & m[0]) | (w[1] & m[1])) != 0; }

struct RandomLinearCongruential {
    double RandomDoubleUniform();                     // 0x009360d0
    uint32_t RandomUint32Uniform(uint32_t nLimit);    // 0x00a68fb0
};
extern RandomLinearCongruential g_Random;   // 0x016778dc (sRandom_Swarm)

// Uniform random in [lo, hi], clamped (inlined helper in the original).
static inline double RandRange(double lo, double hi)
{
    double r = g_Random.RandomDoubleUniform();
    double v = r * (hi - lo) + lo;
    if (v >= hi) return hi;
    if (v < lo) return lo;
    return v;
}

// 3x3 + translation transform (flags bit 1 = has rotation).
struct Xform {
    uint32_t flags;      // +0x00
    Vec3 t;              // +0x04
    float scale;         // +0x10
    float m[9];          // +0x14
    void Transform(Vec3* v);   // FUN_007cdee0 (thiscall)
    Vec3 Rotate(const Vec3& v) const {
        float y = v.y, z = v.z, x = v.x;
        return Vec3((m[3] * y + m[6] * z) + x * m[0],
                    (m[1] * x + m[4] * y) + m[7] * z,
                    (m[2] * x + m[5] * y) + m[8] * z);
    }
};

struct Sampler {             // colour/alpha sampler at this+0x1b8
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(); virtual void s4(); virtual void s5();
    virtual bool Contains(Vec3* p);                 // +0x18
    virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10();
    virtual Vec4* Sample(Vec4* out, Vec3* p);       // +0x2c
};

struct HitObj {              // SpawnRec::a
    virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3();
    virtual bool Collide(Vec3* a, Vec3* b, Vec3* out, float* quat, int pa, int pb);   // +0x10
};

struct SpawnRec {            // 0x18 bytes
    HitObj* a;               // +0x00
    uint32_t* b;             // +0x04 (b[8] is the push-out scale, a float)
    int has8;                // +0x08
    int c;                   // +0x0c
    int has10;               // +0x10
    int c14;                 // +0x14
};

struct Desc {
    uint32_t pad0[2];
    uint32_t flags[2];       // +0x08 (64-bit bitset: low word, high word)
    float lifeMin;           // +0x10
    float lifeMax;           // +0x14
    uint32_t pad18[5];
    uint32_t emitDir[6];     // +0x2c
    uint32_t emitSpeed[8];   // +0x44
    float f64;               // +0x64
    uint32_t pad68[8];
    float* p88;              // +0x88
    uint32_t pad8c[4];
    float vary9c;            // +0x9c
    uint32_t pada0[5];
    float varyb4;            // +0xb4
    uint32_t padb8[5];
    float fcc;               // +0xcc
    uint32_t padd0[6];
    float varye8, varyec, varyf0;   // +0xe8
    uint32_t padf4[5];
    float vary108;           // +0x108
    uint32_t pad10c[10];
    uint8_t pad134[2];
    uint8_t countMul;        // +0x136
    uint8_t countRand;       // +0x137
    uint32_t pad138[6];
    float attract;           // +0x150
    Vec3 attractPos;         // +0x154
    float f160;              // +0x160
    float f164;              // +0x164
    uint32_t pad168[61];
    uint32_t vol25c[1];      // +0x25c
};

struct Particle {
    uint32_t node[2];
    float age;               // +0x08
    float life;              // +0x0c
    Vec3 pos;                // +0x10
    Vec3 vel;                // +0x1c
    float size;              // +0x28
    float aspect;            // +0x2c
    float f30;               // +0x30
    float alpha;             // +0x34
    Vec3 color;              // +0x38
    uint8_t b44;             // +0x44
};

struct Camera {
    uint32_t pad0[23];
    float m5c, m60, m64;     // +0x5c
    uint32_t pad68[3];
    float m74, m78, m7c;     // +0x74
};

// Callees (unnamed)
bool FUN_00a79660(void* base, void* v);                   // cdecl
Vec3* FUN_00a817c0(Vec3* out, Vec3* in, float f);         // cdecl
Vec3* FUN_00a816d0(Vec3* out, Vec3* in);                  // cdecl
Vec3* FUN_007cdbe0(Vec3* out, void* in);                  // cdecl
float FUN_007cdb90(void* in);                             // cdecl
float FUN_00a78f80(float f);                              // cdecl

extern uint32_t g_SpawnMask[2];   // 0x0167946c (bitset mask)
extern uint32_t g_SurfaceMask;    // 0x01565630
extern const float kZero;         // 0x01485378
extern const float kOne;          // 0x01485720
extern const float kHalf;         // 0x01471064

struct ParticleEffectB {
    uint32_t pad0[9];
    Desc* desc;                  // +0x24
    uint32_t pad28[2];
    Camera* camera;              // +0x30
    uint32_t pad34[(0xc8 - 0x34) / 4];
    Xform xfC8;                  // +0xc8
    Xform xf100;                 // +0x100
    uint32_t pad138[(0x160 - 0x138) / 4];
    float speedScale;            // +0x160
    uint32_t pad164;
    float lifeScale;             // +0x168
    uint32_t pad16c[(0x184 - 0x16c) / 4];
    uint8_t b184;                // +0x184
    uint8_t pad185[3];
    uint32_t pad188[3];
    float sizeScale;             // +0x194
    uint32_t pad198[(0x1b8 - 0x198) / 4];
    Sampler* sampler;            // +0x1b8
    uint8_t pad1bc[2];
    uint8_t b1be;                // +0x1be
    uint8_t pad1bf;
    Vec3 v1c0;                   // +0x1c0
    uint32_t pad1cc[(0x1e4 - 0x1cc) / 4];
    SpawnRec* recBegin;          // +0x1e4
    SpawnRec* recEnd;            // +0x1e8
    uint32_t pad1ec[4];
    int i1fc;                    // +0x1fc
    uint32_t pad200[4];
    uint8_t b210;                // +0x210
    uint8_t pad211[3];
    uint32_t p214, p218;         // +0x214

    bool CheckSpawn(Particle* p);          // FUN_00aa97f0
    bool InitParticle(Particle* p);        // @ 0x00aaeb90
};

// @ 0x00aaeb90
bool ParticleEffectB::InitParticle(Particle* p)
{
    bool fromVolume;
    Vec3 tmp;
    float spd;

    p->age = 0.0f;
    p->life = (float)(RandRange(desc->lifeMin, desc->lifeMax) * lifeScale);

    p->b44 = b184;
    uint8_t n = desc->countRand;
    if (n > 0) {
        if (desc->countMul > 0)
            p->b44 += (uint8_t)(g_Random.RandomUint32Uniform(n) * desc->countMul);
        else
            p->b44 += (uint8_t)g_Random.RandomUint32Uniform(n);
    }

    if (Bit(desc->flags[0], 0x1f)) {
        uint32_t* r = &p214;
        if (p214 == p218) r = desc->vol25c;
        if (FUN_00a79660(&p->age, r)) {
            fromVolume = true;
            goto after_pos;
        }
    }
    fromVolume = false;
    if (desc->f64 >= kZero) {
        p->pos = *FUN_00a817c0(&tmp, &v1c0, desc->f64);
    } else {
        Desc* d = desc;
        p->pos = *(Bit(d->flags[0], 4) ? FUN_00a816d0(&tmp, &v1c0) : FUN_007cdbe0(&tmp, &v1c0));
    }

    if (TestAny(desc->flags, g_SpawnMask)) {
        if (!CheckSpawn(p))
            return false;
    }

    {
        p->vel = *FUN_007cdbe0(&tmp, desc->emitDir);
        spd = FUN_007cdb90(desc->emitSpeed) * speedScale;
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
            if (m2 > 0.0f) {
                k = k / sqrtf(m2);
                p->vel.x = dx * k + p->vel.x;
                p->vel.y = dy * k + p->vel.y;
                p->vel.z = dz * k + p->vel.z;
            }
        }
    }

after_pos:
    {
        float v;
        v = desc->vary9c;
        p->size = (float)(RandRange(1.0 - v, v + 1.0) * sizeScale);
        v = desc->varyb4;
        p->aspect = (float)RandRange(1.0 - v, v + 1.0);
        v = desc->vary108;
        p->alpha = (float)RandRange(1.0 - v, v + 1.0);
        v = desc->varye8;
        p->color.x = (float)RandRange(1.0 - v, v + 1.0);
        v = desc->varyec;
        p->color.y = (float)RandRange(1.0 - v, v + 1.0);
        v = desc->varyf0;
        p->color.z = (float)RandRange(1.0 - v, v + 1.0);
    }

    if (sampler) {
        Vec3 pt(p->pos);
        if (b1be) {
            xfC8.Transform(&pt);
            xf100.Transform(&pt);
        }
        if (sampler->Contains(&pt)) {
            Vec4 col;
            sampler->Sample(&col, &pt);
            p->alpha = p->alpha * col.w;
            p->color = Vec3(p->color.x * col.x, p->color.y * col.y, p->color.z * col.z);
        }
    }

    {
        float v = desc->fcc;
        p->f30 = (v > kZero) ? FUN_00a78f80(v) : kOne;
    }

    Vec3* pv = &p->pos;
    if (xfC8.flags & 2) {
        *pv = xfC8.Rotate(*pv);
    }
    {
        float s = xfC8.scale;
        pv->x = s * pv->x;
        pv->y = s * pv->y;
        pv->z = pv->z * s;
        pv->x = xfC8.t.x + pv->x;
        pv->y = xfC8.t.y + pv->y;
        pv->z = xfC8.t.z + pv->z;
    }
    if (xfC8.flags & 2) {
        p->vel = xfC8.Rotate(p->vel);
    }

    if (!fromVolume && Bit(desc->flags[0], 3)) {
        Camera* c = camera;
        float a = (p->vel.z * c->m7c + p->vel.y * c->m78) + c->m74 * p->vel.x;
        float b = (p->vel.z * c->m64 + p->vel.y * c->m60) + p->vel.x * c->m5c;
        float inv = kOne / spd;
        float r = sqrtf(b * b + a * a) / desc->f164;
        float g = *desc->p88;
        pv->x = (g * ((p->vel.x * kHalf) * r)) * inv + pv->x;
        pv->y = (g * ((p->vel.y * kHalf) * r)) * inv + pv->y;
        pv->z = (g * ((p->vel.z * kHalf) * r)) * inv + pv->z;
    }

    if (b210) {
        int base = i1fc;
        for (SpawnRec* r = recBegin; r != recEnd; r++) {
            if ((*r->b & g_SurfaceMask) == 0)
                continue;
            int pa = r->has8 ? r->c + base : 0;
            Vec3 hit;
            if (r->a->Collide(pv, pv, &hit, 0, pa, 0)) {
                float sc = ((float*)r->b)[8];
                if (sc != kZero) {
                    pv->x = pv->x + hit.x * sc;
                    pv->y = hit.y * sc + pv->y;
                    pv->z = hit.z * sc + pv->z;
                }
                return true;
            }
        }
    }
    return true;
}
