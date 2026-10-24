// s00aae8c0 (part 2): EA::Swarm swarm-module helpers around the particle pool and the
// cParticlesEffect "chain system" (spawn/kill a particle, physics step, module init).
// Class and field names follow the 2008 dev PDB (EA::Swarm::cParticlesEffect /
// cParticlesDescription); retail offsets were taken from the disassembly and differ from the PDB.
// flags: /vc71 /O2 /MD /Gy /TP
#include "types.h"
#include <math.h>
#include <string.h>

struct Vec3 { float x, y, z; };

struct Particle {                 // matched to the original 0x88-byte particle
    Particle* next;               // +0x00 intrusive-list next
    Particle* prev;               // +0x04 intrusive-list prev
    float age;                    // +0x08
    float life;                   // +0x0c
    Vec3 pos;                     // +0x10
    Vec3 vel;                     // +0x1c
    float size;                   // +0x28
    float aspect;                 // +0x2c
    float f30;                    // +0x30
    float alpha;                  // +0x34
    Vec3 color;                   // +0x38
    uint8_t b44;                  // +0x44
};

struct ImpulseTable {             // impulse falloff description at Desc+0x240
    float* begin;                 // +0x00 keyed speed table
    float* end;                   // +0x04
    int    pad0[3];               // +0x08
    float  speed;                 // +0x14 distance the table spans
    float  threshold;             // +0x18 below this the impulse is dropped
};

struct ParticleFlags {            // 64-bit particle flag set (EA::Swarm::cParticlesDescription)
    volatile uint32_t lo;         // +0x00 bits 0..31
    volatile uint32_t hi;         // +0x04 bits 32..63
};

struct Desc {                     // EA::Swarm::cParticlesDescription (retail offsets)
    uint32_t pad0[2];             // +0x00
    ParticleFlags flags;          // +0x08 64-bit particle flag set
    float lifeMin;                // +0x10
    float lifeMax;                // +0x14
    uint32_t pad18[5];            // +0x18
    uint32_t emitDir[6];          // +0x2c
    uint32_t emitSpeed[8];        // +0x44
    float f64;                    // +0x64
    uint32_t pad68[8];            // +0x68
    float* p88;                   // +0x88
    uint32_t pad8c[4];            // +0x8c
    float vary9c;                 // +0x9c
    uint32_t pada0[5];            // +0xa0
    float varyb4;                 // +0xb4
    uint32_t padb8[5];            // +0xb8
    float fcc;                    // +0xcc
    uint32_t padd0[6];            // +0xd0
    float varye8, varyec, varyf0; // +0xe8
    uint32_t padf4[5];            // +0xf4
    float vary108;                // +0x108
    uint8_t pad10c[0x24];         // +0x10c
    uint8_t physicsType;          // +0x130 index into the update-function table
    uint8_t pad131[5];            // +0x131
    uint8_t countMul;             // +0x136
    uint8_t countRand;            // +0x137
    uint32_t pad138[6];           // +0x138
    float attract;                // +0x150
    Vec3 attractPos;              // +0x154
    float drag;                   // +0x160
    float f164;                   // +0x164
    uint32_t pad168[0x36];        // +0x168
    ImpulseTable impulseTable;    // +0x240 embedded impulse table
    uint32_t vol25c[1];           // +0x25c
};

struct EffectBase0 { virtual void b0(); };
struct EffectBase1 { virtual void b1(); };
struct IComponentBase {
    virtual void c0();
    virtual void c1();
    virtual void Start(int nStop);   // vtable +0x08
    virtual void Stop(int nStop);    // vtable +0x0c
    virtual bool IsActive();         // vtable +0x10
};
struct EffectRefCount {
    virtual void r0();
    int mRefCount;                   // +0x10
};

class ParticleEffectB : public EffectBase0, public EffectBase1, public IComponentBase, public EffectRefCount
{ public:
    uint8_t mStarted;                // +0x14
    uint8_t mDelayedStopActive;      // +0x15
    uint8_t mIsVisible;              // +0x16
    uint8_t pad17;                   // +0x17
    Particle* mParticlesNext;        // +0x18 intrusive-list sentinel
    Particle* mParticlesPrev;        // +0x1c
    int mParticleCount;              // +0x20
    Desc* desc;                      // +0x24
    uint32_t pad28[2];               // +0x28
    void* camera;                    // +0x30
    uint32_t pad34[(0x64 - 0x34) / 4];
    Vec3 directionalForces;          // +0x64
    uint32_t pad70[(0x8c - 0x70) / 4];
    Vec3 attractorLocation;          // +0x8c
    float attractorIntensity;        // +0x98
    uint32_t pad9c[(0x160 - 0x9c) / 4];
    float emitVelocityScale;         // +0x160
    uint32_t pad164;
    float lifeScale;                 // +0x168
    uint32_t pad16c[(0x1b0 - 0x16c) / 4];
    void* forceMap;                  // +0x1b0
    uint32_t pad1b4;
    uint32_t pad1b8[(0x228 - 0x1b8) / 4];
    ParticleEffectB* mChainSystem;   // +0x228

    bool InitParticle(Particle* p);                    // 0x00aaeb90
    void SpawnChainParticle(Particle* p);              // 0x00aaf560
    bool StepParticle(Particle* p, float dt);          // 0x00aaeb20
    void KillParticle(Particle* p);                    // 0x00aaf670
    bool ApplyForceMap(Particle* p, Vec3* oldPos);     // 0x00aa88c0
    bool SampleForceMap(Particle* p, float dt);        // 0x00aa9050
};

struct RandomLinearCongruential {
    double RandomDoubleUniform();                      // 0x009360d0
};
extern RandomLinearCongruential g_Random;              // 0x016778dc (sRandom_Swarm)

struct FixedAllocatorBase {
    bool AddCore(void* pCore, unsigned int nSize);     // 0x00926650
};
extern FixedAllocatorBase sParticlePool;               // 0x01679480
extern Particle* sFreeParticles;                       // 0x01679490

typedef bool (__cdecl* tUpdateParticleFn)(Particle*, float, Desc*, ParticleEffectB*);
extern tUpdateParticleFn kUpdateFns[];                 // 0x015655dc

extern const float kMaxStep;                           // 0x01459420 (1/15)
extern const float kZero;                              // 0x01485378
extern const float kOne;                               // 0x01485720

bool __cdecl FUN_00aa83b0(Particle* p, float dt, Desc* d, ParticleEffectB* e);  // 0x00aa83b0
bool __cdecl ApplyDirectedImpulse(const ImpulseTable* table, const Vec3* dir, float scale, Vec3* out);  // 0x00a79500

// Uniform random in [lo, hi], clamped (inlined helper in the original).
static inline double RandRange(double lo, double hi)
{
    double r = g_Random.RandomDoubleUniform();
    double v = r * (hi - lo) + lo;
    if (v >= hi) return hi;
    if (v < lo) return lo;
    return v;
}

template <class T> static inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }

// Swarm module static initialiser: zero-fill the 0x80-byte renderer/streamer descriptor block and
// install its three entry points.
struct SwarmInitBlock {
    void* p0;                        // +0x00
    uint32_t pad4;                   // +0x04
    void* p8;                        // +0x08
    void* pC;                        // +0x0c
    uint32_t pad10[0x1c];            // +0x10
};
extern SwarmInitBlock g_swarmInitBlock;    // 0x016793a0

// @ 0x00aae8c0
void SwarmModuleInit(char flag)
{
    if (flag) {
        memset(&g_swarmInitBlock, 0, sizeof(g_swarmInitBlock));
        g_swarmInitBlock.p0 = (void*)0x00aaa110;
        g_swarmInitBlock.p8 = (void*)0x00aabc20;
        g_swarmInitBlock.pC = (void*)0x00aad240;
    }
}

// @ 0x00aae900
bool UpdatePhysicsTimeStep(Particle* p, float dt, Desc* d, ParticleEffectB* e)
{
    float age = dt + p->age;
    p->age = age;
    if (p->life <= age)
        return false;

    do {
        float step = Min(dt, kMaxStep);
        Vec3 oldPos = p->pos;
        p->pos.x = p->pos.x + p->vel.x * step;
        p->pos.y = p->pos.y + p->vel.y * step;
        p->pos.z = p->pos.z + p->vel.z * step;
        Vec3 force = e->directionalForces;
        if ((d->flags.lo >> 23) & 1) {
            Vec3 attr;
            attr.x = e->attractorLocation.x - p->pos.x;
            attr.y = e->attractorLocation.y - p->pos.y;
            attr.z = e->attractorLocation.z - p->pos.z;
            if (!ApplyDirectedImpulse(&d->impulseTable, &attr, e->attractorIntensity, &force))
                return false;
        }
        p->vel.x = p->vel.x + force.x * step;
        p->vel.y = p->vel.y + force.y * step;
        p->vel.z = p->vel.z + force.z * step;
        float damp = kOne - d->drag * step;
        p->vel.x = p->vel.x * damp;
        p->vel.y = p->vel.y * damp;
        p->vel.z = p->vel.z * damp;
        if ((((d->flags.lo >> 12) & 1) && !e->ApplyForceMap(p, &oldPos)) ||
            (e->forceMap != 0 && !e->SampleForceMap(p, step)))
            return false;
        dt = dt - step;
    } while (dt > kZero);
    return true;
}

// @ 0x00aaeb20
bool ParticleEffectB::StepParticle(Particle* p, float dt)
{
    Desc* d = desc;
    if (kUpdateFns[d->physicsType])
        return kUpdateFns[desc->physicsType](p, dt, d, this);
    if (d->drag * dt > 0.05f)
        return UpdatePhysicsTimeStep(p, dt, d, this);
    return FUN_00aa83b0(p, dt, d, this);
}

// @ 0x00aaf560
void ParticleEffectB::SpawnChainParticle(Particle* p)
{
    Desc* d = mChainSystem->desc;
    p->age = 0.0f;
    p->life = (float)(RandRange(d->lifeMin, d->lifeMax) * lifeScale);
    if (!mChainSystem->IsActive())
        mChainSystem->Start(0);
    if ((d->flags.lo >> 26) & 1)
        mChainSystem->InitParticle(p);
    ParticleEffectB* chain = mChainSystem;
    p->prev = chain->mParticlesPrev;
    p->next = (Particle*)&chain->mParticlesNext;
    p->next->prev = p;
    p->prev->next = p;
    chain->mParticleCount++;
}

// @ 0x00aaf630
Particle* AllocateParticle()
{
    Particle* p;
    do {
        p = sFreeParticles;
        if (p) {
            sFreeParticles = p->next;
            p->prev = 0;
            p->next = 0;
            return p;
        }
    } while (sParticlePool.AddCore(0, 0));
    return 0;
}

// @ 0x00aaf670
void ParticleEffectB::KillParticle(Particle* p)
{
    if (mChainSystem && mChainSystem->desc) {
        uint32_t f = desc->flags.hi;
        if ((f & 1) || (((f >> 1) & 1) ^ (p->age >= p->life))) {
            SpawnChainParticle(p);
            ParticleEffectB* chain = mChainSystem;
            if (chain && mParticleCount == 0 && mDelayedStopActive)
                chain->Stop(0);
            return;
        }
    }
    p->next = sFreeParticles;
    sFreeParticles = p;
}
