// Slice s00f60f00 (continued): particle-effect factories and the frame-stepped update variant.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

namespace rw { namespace math { namespace fpu {
struct Vector3
{
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
}}}
typedef rw::math::fpu::Vector3 Vector3;

namespace EA {

namespace Random {
class RandomLinearCongruential
{ public:
    uint32_t mnSeed;
    double   RandomDoubleUniform();                 // 0x009360d0
};
}
namespace SP { extern Random::RandomLinearCongruential sMathRandom; }   // 0x01601760

namespace Allocator {
class FixedAllocatorBase { public: bool AddCore(int pCore, int nSize); };      // 0x00926650
}

namespace Swarm {

extern Allocator::FixedAllocatorBase sParticlePool;       // 0x016c9468
struct cParticle;
extern cParticle* sFreeParticles;                          // 0x016c9478

static __forceinline double RandomRange(double lo, double hi)
{
    double v = SP::sMathRandom.RandomDoubleUniform() * (hi - lo) + lo;
    if (v >= hi)
        return hi;
    if (lo > v)
        return lo;
    return v;
}

struct cParticle                    // 0x88
{
    cParticle* mpNext;              // +0x00
    cParticle* mpPrev;              // +0x04
    float      mAge;                // +0x08
    float      mLife;               // +0x0c
    Vector3    mPosition;           // +0x10
    Vector3    mVelocity;           // +0x1c
};

class cParticlesEffect;

struct FloatVector                  // eastl::vector<float> (begin/end only)
{
    float* mpBegin;
    float* mpEnd;
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    float& operator[](unsigned i) { return mpBegin[i]; }
};

struct cParticlesDescription
{
    uint32_t mPad0[2];
    uint32_t mFlags;                // +0x08
    uint32_t mPad0c;
    float    mSpawnTimeLimit;       // +0x10 (name guessed)
    float    mMaxTimeSlice;         // +0x14 (name guessed)
    uint32_t mPad18[2];
    float    mRetriggerMin;         // +0x20
    float    mRetriggerMax;         // +0x24
    uint32_t mPad28[15];
    FloatVector mRate;              // +0x64 eastl::vector<float> (begin, end)
    uint32_t mPad6c[3];
    float    mRateLoop;             // +0x78
    uint16_t mRateCurveCycles;      // +0x7c
    uint16_t mPad7e;
    float    mRateSpeedScale;       // +0x80
    uint32_t mPad84[0x128 / 4 - 0x21];
    uint8_t  mPhysicsType;          // +0x128
    uint8_t  mPad129[3];
    uint32_t mPad12c[0x158 / 4 - 0x4b];
    float    mDrag;                 // +0x158
};

typedef bool (__cdecl *tUpdateParticleFn)(cParticle* particle, float dt, cParticlesDescription* desc,
                                          cParticlesEffect* effect);
extern tUpdateParticleFn kUpdateFns[];                      // 0x015b0c00
extern const float kHalf;                                   // 0x01471064
extern const float kOne;                                    // 0x01485720
extern const float kPoolStepThreshold;                      // 0x013ec478 (0.05)
extern const float kZeroTime;                               // 0x01485378 (0.0)
extern const float kRetriggerEpsilon;                       // 0x013eb960 (0.01)
extern const float kSignalMask;                             // 0x013eb8b0 sign bit

struct IStoppable
{
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void Stop(bool immediate);                      // slot 3
};

class cParticlesEffect
{ public:
    uint32_t               mPad0[2];
    IStoppable             mComponent;                      // +0x08 (vtable only)
    uint32_t               mPad0c[2];
    bool                   mStarted;                        // +0x14
    bool                   mDelayedStopActive;              // +0x15
    uint8_t                mPad16[2];
    cParticle*             mParticlesNext;                  // +0x18 intrusive_list sentinel
    cParticle*             mParticlesPrev;                  // +0x1c
    int                    mParticleCount;                  // +0x20
    cParticlesDescription* mDesc;                           // +0x24
    uint32_t               mPad28[10];
    double                 mTime;                           // +0x50 rate-curve time
    int                    mFrame;                          // +0x58
    uint32_t               mPad5c;
    double                 mRate;                           // +0x60
    float                  mParticlesToGenerate;            // +0x68
    Vector3                mDirectionalForcesSum;           // +0x6c
    uint32_t               mPad78[11];
    float                  mRetriggerTime;                  // +0xa4
    Vector3                mBoundsMin;                      // +0xa8
    Vector3                mBoundsMax;                      // +0xb4
    uint32_t               mPadc0[5];
    Vector3                mLocation;                       // +0xd4
    float                  mScale;                          // +0xe0
    uint32_t               mPade4[0x140 / 4 - 0x39];
    Vector3                mLastEmitLocation;               // +0x140
    uint32_t               mPad14c[0x194 / 4 - 0x53];
    float                  mCurrentEmitRateScale;           // +0x194
    uint32_t               mPad198[0x230 / 4 - 0x66];
    cParticlesEffect*      mChainSystem;                    // +0x230

    void Update(float dt);                                  // 0x00f60f00
    void UpdateByFrames(float dt);                          // 0x00f61600
    void UpdateByType(float dt);                            // 0x00f60630
    void TickRetrigger(float dt);                           // 0x00f61ab0
    void StepFrame();                                       // 0x00f60810
    bool InitParticle(cParticle* p);                        // 0x00f5ebf0
    void ReleaseParticle(cParticle* p);                     // 0x00f5f6a0
};
bool __cdecl DefaultUpdateParticle(cParticle* particle, float dt, cParticlesDescription* desc,
                                   cParticlesEffect* effect);   // 0x00f5e910

static inline bool TestBit(uint32_t flags, int bit) { return ((flags >> bit) & 1) != 0; }

}} // namespace EA::Swarm

// ---------------------------------------------------------------------------------------
// 0x00f473a0 (name guessed): the module's sized operator new with a tag string.
void* FUN_00f473a0(uint32_t size, const char* tag, uint32_t a, uint32_t b, uint32_t c, uint32_t d);

// Object header carrying the sub-object factory entry point at 0x00f608c0.
class cSwarmEffectAlloc
{
public:
    char* FUN_00f608c0(uint32_t a, uint32_t b);            // 0x00f608c0, ret 8
};

void FUN_00f5eb30();                                       // 0x00f5eb30

extern void* gSwarmEffectFactory;                          // 0x01676418
extern void* gSwarmEffectUpdate;                           // 0x01676410

// @ 0x00f61a30
int FUN_00f61a30(uint32_t a, uint32_t b)
{
    char* mem = (char*)FUN_00f473a0(0x248, "Swarm", 0, 0, 0, 0);
    if (mem) {
        char* r = ((cSwarmEffectAlloc*)mem)->FUN_00f608c0(a, b);
        if (r)
            return (int)(r + 8);
    }
    return 0;
}

// @ 0x00f61a70
void FUN_00f61a70()
{
    gSwarmEffectFactory = (void*)&FUN_00f61a30;
    gSwarmEffectUpdate = (void*)&FUN_00f5eb30;
}

// @ 0x00f61ab0
void EA::Swarm::cParticlesEffect::TickRetrigger(float dt)
{
    if (mRetriggerTime > 0.0f) {
        dt = mRetriggerTime - dt;
        mRetriggerTime = dt;
        if (dt > 0.0f)
            return;
        dt = -dt;
    }

    float limit = mDesc->mMaxTimeSlice;
    if (limit > kRetriggerEpsilon) {
        limit = limit - kRetriggerEpsilon;
        if (dt > limit)
            dt = limit;
    }

    uint32_t flags = mDesc->mFlags;
    if (TestBit(flags, 1))
        UpdateByType(dt);
    else if (TestBit(flags, 0))
        UpdateByFrames(dt);
    else
        Update(dt);
}

// @ 0x00f61600
void EA::Swarm::cParticlesEffect::UpdateByFrames(float dt)
{
    mTime = dt * mRate + mTime;
    if (mTime < (double)mFrame)
        return;

    float rate = mDesc->mRate.mpBegin[0] * mCurrentEmitRateScale;
    int n = (int)rate;
    if ((float)n < rate)
        n++;

    while (mTime >= (double)mFrame) {
        if (TestBit(mDesc->mFlags, 27))
            StepFrame();

        float step = (float)((mTime - (double)mFrame) * mDesc->mRateLoop);
        if (step < mDesc->mSpawnTimeLimit) {
            for (int i = 0; i < n; i++) {
                cParticle* p;
                for (;;) {
                    p = sFreeParticles;
                    if (!p) {
                        if (sParticlePool.AddCore(0, 0))
                            continue;
                        p = 0;
                    } else {
                        sFreeParticles = p->mpNext;
                        p->mpPrev = 0;
                        p->mpNext = 0;
                    }
                    break;
                }

                bool alive;
                if (!InitParticle(p)) {
                    alive = false;
                } else {
                    cParticlesDescription* pd = mDesc;
                    tUpdateParticleFn fn = kUpdateFns[pd->mPhysicsType];
                    if (fn) {
                        alive = fn(p, step, pd, this);
                    } else if (pd->mDrag * step > kPoolStepThreshold) {
                        alive = DefaultUpdateParticle(p, step, pd, this);
                    } else {
                        float age = p->mAge;
                        p->mAge = age + step;
                        if (age + step < p->mLife) {
                            Vector3 v0 = p->mVelocity;
                            p->mVelocity.z = mDirectionalForcesSum.z * step + p->mVelocity.z;
                            p->mVelocity.y = mDirectionalForcesSum.y * step + p->mVelocity.y;
                            p->mVelocity.x = v0.x + mDirectionalForcesSum.x * step;
                            float damp = kOne - pd->mDrag * step;
                            p->mVelocity.x = p->mVelocity.x * damp;
                            p->mVelocity.y = p->mVelocity.y * damp;
                            p->mVelocity.z = p->mVelocity.z * damp;
                            float half = step * kHalf;
                            p->mPosition.x = (p->mVelocity.x + v0.x) * half + p->mPosition.x;
                            p->mPosition.y = p->mPosition.y + (p->mVelocity.y + v0.y) * half;
                            p->mPosition.z = p->mPosition.z + (p->mVelocity.z + v0.z) * half;
                            alive = true;
                        } else {
                            alive = false;
                        }
                    }
                }

                if (!alive) {
                    if (!mChainSystem || (p->mAge < p->mLife && !TestBit(mDesc->mFlags, 27))) {
                        p->mpNext = sFreeParticles;
                        sFreeParticles = p;
                    } else {
                        ReleaseParticle(p);
                        if (mChainSystem && mParticleCount == 0 && mDelayedStopActive)
                            mChainSystem->mComponent.Stop(false);
                    }
                } else {
                    p->mpPrev = mParticlesPrev;
                    p->mpNext = (cParticle*)&mParticlesNext;
                    ((cParticle*)((char*)&mParticlesNext))->mpPrev = p;
                    p->mpPrev->mpNext = p;
                    mParticleCount++;
                    if (p->mPosition.x < mBoundsMin.x) mBoundsMin.x = p->mPosition.x;
                    if (p->mPosition.x > mBoundsMax.x) mBoundsMax.x = p->mPosition.x;
                    if (p->mPosition.y < mBoundsMin.y) mBoundsMin.y = p->mPosition.y;
                    if (p->mPosition.y > mBoundsMax.y) mBoundsMax.y = p->mPosition.y;
                    if (p->mPosition.z < mBoundsMin.z) mBoundsMin.z = p->mPosition.z;
                    if (p->mPosition.z > mBoundsMax.z) mBoundsMax.z = p->mPosition.z;
                }
            }
        }

        mFrame++;
        cParticlesDescription* desc = mDesc;
        if (desc->mRateCurveCycles != 0 && mFrame >= (int)desc->mRateCurveCycles) {
            if (TestBit(desc->mFlags, 28))
                return;
            mComponent.Stop(false);
            return;
        }
        if (desc->mRetriggerMin >= 0.0f) {
            double r = RandomRange(desc->mRetriggerMin, desc->mRetriggerMax);
            mTime = mTime - r * mRate;
            if (mTime < (double)mFrame) {
                mRetriggerTime = (float)((double)desc->mRateLoop * ((double)mFrame - mTime));
                mTime = (double)mFrame;
                return;
            }
        }
    }
}
