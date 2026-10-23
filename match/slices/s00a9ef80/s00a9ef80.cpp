// s00a9ef80: Swarm particle emitter - "spawn one particle": randomise the new particle's
// lifetime from the owned emitter's descriptor, build/attach its effect object, run the
// per-particle init, then push it onto the owned emitter's active list.
// Companion of s00a9ddd0 (ParticleEmitter::InitParticle). Class/field names are
// Claude-coined from usage (offsets taken from the retail layout).
// flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

struct Vec3 { float x, y, z; };

static inline bool Bit(uint32_t v, int n) { return (v >> n) & 1; }

struct RandomLinearCongruential { double RandomDoubleUniform(); };
extern RandomLinearCongruential g_Random;                 // 0x016778dc (sRandom_Swarm)

// Uniform random in [lo, hi], clamped (inlined helper in the original, see s00a9ddd0).
static inline double RandRange(double lo, double hi)
{
    double r = g_Random.RandomDoubleUniform();
    double v = r * (hi - lo) + lo;
    if (v >= hi) return hi;
    if (v < lo) return lo;
    return v;
}

// Transform-update message (0x38 bytes); default ctor at 0x00434040.
struct Matrix3 { float m[9]; Matrix3(); };
struct XformMsg {
    uint16_t flags;
    uint16_t count;
    Vec3     pos;
    float    scale;
    Matrix3  rot;
    XformMsg();
};

// Particle descriptor (only the fields this slice touches; see s00a9ddd0 for the full one).
struct Desc {
    uint8_t  pad00[8];
    uint32_t flags[2];         // +0x08 (64-bit bitset)
    float    lifeMin;          // +0x10
    float    lifeMax;          // +0x14
    uint8_t  pad18[0x128 - 0x18];
    uint32_t key128;           // +0x128
    uint32_t key12c;           // +0x12c
};

// Effect-object interface reached through Particle::fx.p (2nd base sub-object).
struct FxObj {
    virtual void v0();
    virtual void v1();
    virtual void v2(uint32_t a);                          // +0x08
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6(void* src, void* xform);              // +0x18
    virtual void v7();
    virtual void v8();
    virtual void v9(uint32_t a, uint32_t b);              // +0x24
    virtual void v10(uint8_t a);                          // +0x28
    virtual void v11();
    virtual void v12();
    virtual void AddRef();                                // +0x34
    virtual void Release();                               // +0x38
};

// The 1st base sub-object, found at (char*)Particle::fx.p - 4.
struct FxBase {
    virtual void b0();
    virtual void b1();
    virtual void b2();
    virtual void b3(uint32_t key);                        // +0x0c
    virtual void b4();
    virtual void b5();
    virtual void b6();
    virtual void b7(void* msg);                           // +0x1c
    virtual void b8(void* msg);                           // +0x20
};

struct FxFactory {
    FxObj* Create(uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // FUN_00a714f0
};

struct Particle;

// Refcounted smart pointer stored in Particle::fx; assignment helper 0x007d4590.
struct FxPtr {
    FxObj* p;                                             // +0x00
    void Assign(FxObj* o);                                // FUN_007d4590 (out of line)
    void Reset() { FxObj* old = p; if (old) { p = 0; old->Release(); } }
};

// EA::Swarm::cParticle (layout per s00a9ddd0).
struct Particle {
    void*   node[2];                                      // +0x00 / +0x04 intrusive links
    float   age;                                          // +0x08
    float   life;                                         // +0x0c
    uint8_t pad10[0x7c - 0x10];
    FxPtr   fx;                                           // +0x7c
};

// The emitter. Has its own descriptor at +0x0c and owns a child emitter at +0x248.
struct Emitter {
    virtual void v0();                                    // vtable at +0x00
    virtual void v1();
    virtual void v2(int a);                               // +0x08
    virtual void v3();
    virtual bool v4();                                    // +0x10
    uint32_t   u04;
    uint32_t   u08;
    Desc*      desc;                                      // +0x0c
    uint32_t   u10;                                       // +0x10
    FxFactory* factory;                                   // +0x14
    uint32_t   u18;                                       // +0x18
    uint32_t   u1c;                                       // +0x1c
    uint16_t   u20;                                       // +0x20
    uint8_t    b22;                                       // +0x22
    uint8_t    pad23;
    void*      head;                                      // +0x24 active-list head
    uint32_t   u28;                                       // +0x28
    uint32_t   count;                                     // +0x2c
    uint8_t    pad30[0x124 - 0x30];
    uint32_t   u124;                                      // +0x124
    int32_t    i128;                                      // +0x128
    uint8_t    pad12c[0x144 - 0x12c];
    float      f144;                                      // +0x144
    uint8_t    pad148[0x22c - 0x148];
    uint8_t    b22c;                                      // +0x22c
    uint8_t    pad22d[3];
    uint32_t   u230;                                      // +0x230
    uint8_t    pad234[0x248 - 0x234];
    Emitter*   pool;                                      // +0x248 owned child emitter

    bool InitParticle(Particle* p);                       // FUN_00a9ddd0
    void FUN_00a9ef80(Particle* p);                       // @ 0x00a9ef80
};

// @ 0x00a9ef80
void Emitter::FUN_00a9ef80(Particle* p)
{
    Desc* d = pool->desc;

    p->age = 0.0f;
    p->life = (float)(RandRange(d->lifeMin, d->lifeMax) * f144);

    if ((int32_t)d->key128 >= 0 && d->key128 != desc->key128 && d->key12c == 0) {
        FxBase* fx = p->fx.p ? (FxBase*)((char*)p->fx.p - 4) : 0;
        XformMsg a;
        XformMsg b;
        if (p->fx.p) {
            fx->b7(&a);
            fx->b8(&b);
            fx->b3((uint32_t)i128);
            p->fx.Reset();
        }
        p->fx.Assign(factory->Create(d->key12c, d->key128, u10, (uint32_t)u1c));
        if (p->fx.p) {
            p->fx.p->v6(&b, &a);
            if (b22c) p->fx.p->v9(0, u230);
            p->fx.p->v10(b22);
            p->fx.p->v2(u124);
        }
    }

    if (!pool->v4())
        pool->v2(0);

    if (Bit(d->flags[0], 0x1d))
        pool->InitParticle(p);

    Emitter* em = pool;
    Particle* first = (Particle*)em->head;
    p->node[0] = first;
    p->node[1] = (void*)&em->head;
    em->head = p;
    ((Particle*)p->node[0])->node[1] = p;
    em->count++;
}
