// Slice s00f60f00: 0x00F60F00, EA::Swarm particles effect update (emit + age one time slice).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Behaviour: advance the effect by `dt` seconds in steps of at most 1/15 s. Per step the emission
// rate curve (own frame counter + double time accumulator, optionally looping / ending the effect) is
// sampled, scaled by the effect scale (flag bits 8..10), the source speed (rateSpeedScale) and the
// step, the fractional particle count accumulates in mParticlesToGenerate and that many particles are
// taken from the global particle pool, initialised (InitParticle 0x00f5ebf0), back-dated by their
// spawn time, moved by the type's update function (table 0x015b0c00; default 0x00f5e910, or a simple
// inlined Euler step with drag for small drag*dt), and linked into the live list while the effect's
// bounding box grows. Dead / rejected particles go back to the pool (or through ReleaseParticle when a
// chain effect exists). After a step that emitted, a random retrigger delay is subtracted from dt.
//
// NAMING NOTE: no PDB symbol is known for 0x00F60F00 (it is the cParticlesEffect update, the dev PDB
// name is not matched). Layouts follow s00f5e910 (retail offsets); names marked "(name guessed)" are
// Claude-coined (dev PDB names where the field clearly corresponds).
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

// round-down float -> int: the module's asm helper (cvtss2si + cmovb), result in eax.
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

namespace EA {

namespace Random {
struct RandomLinearCongruential
{
    uint32_t mnSeed;
    double   RandomDoubleUniform();                 // 0x009360d0
};
}
namespace SP { extern Random::RandomLinearCongruential sMathRandom; }   // 0x01601760

namespace Allocator {
struct FixedAllocatorBase { bool AddCore(int pCore, int nSize); };      // 0x00926650
}

namespace Swarm {

extern Allocator::FixedAllocatorBase sParticlePool;       // 0x016c9468 (name guessed)
struct cParticle;
extern cParticle* sFreeParticles;                          // 0x016c9478 (name guessed)

// Random in [lo, hi], clamped (inlined everywhere in the original)
static __forceinline double RandomRange(double lo, double hi)
{
    double v = SP::sMathRandom.RandomDoubleUniform() * (hi - lo) + lo;
    if (v >= hi)
        return hi;
    if (lo > v)
        return lo;
    return v;
}

struct cParticle                    // 0x88 (retail)
{
    cParticle* mpNext;              // +0x00 intrusive_list_node
    cParticle* mpPrev;              // +0x04
    float      mAge;                // +0x08
    float      mLife;               // +0x0c
    Vector3    mPosition;           // +0x10
    Vector3    mVelocity;           // +0x1c
};

struct cParticlesEffect;

struct FloatVector                  // eastl::vector<float> (begin/end only)
{
    float* mpBegin;
    float* mpEnd;
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    float& operator[](unsigned i) { return mpBegin[i]; }
};

struct cParticlesDescription        // retail offsets
{
    uint32_t mPad0[2];
    uint32_t mFlags;                // +0x08
    uint32_t mPad0c[5];
    float    mRetriggerMin;         // +0x20 (name guessed)
    float    mRetriggerMax;         // +0x24 (name guessed)
    uint32_t mPad28[15];
    FloatVector mRate;              // +0x64 eastl::vector<float> (begin, end)
    uint32_t mPad6c[3];
    float    mRateLoop;             // +0x78 (name guessed)
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
extern tUpdateParticleFn kUpdateFns[];                      // 0x015b0c00 (name guessed)
extern const float kMaxStep;                                // 0x0148f074 (1/15)
extern const float kHalf;                                   // 0x01471064
extern const float kOne;                                    // 0x01485720
extern const float kPoolStepThreshold;                      // 0x013ec478 (0.05)
extern const float kRateEpsilon;                            // 0x013f11c8 (1e-6)

struct IStoppable
{
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void Stop(bool immediate);                      // slot 3
};

struct cParticlesEffect
{
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
    double                 mTime;                           // +0x50 rate-curve time (name guessed)
    int                    mFrame;                          // +0x58
    uint32_t               mPad5c;
    double                 mRate;                           // +0x60 (name guessed)
    float                  mParticlesToGenerate;            // +0x68
    Vector3                mDirectionalForcesSum;           // +0x6c
    uint32_t               mPad78[11];
    float                  mRetriggerTime;                  // +0xa4
    Vector3                mBoundsMin;                      // +0xa8
    Vector3                mBoundsMax;                      // +0xb4
    uint32_t               mPadc0[5];
    Vector3                mLocation;                       // +0xd4 (source transform translation)
    float                  mScale;                          // +0xe0
    uint32_t               mPade4[0x140 / 4 - 0x39];
    Vector3                mLastEmitLocation;               // +0x140
    uint32_t               mPad14c[0x194 / 4 - 0x53];
    float                  mCurrentEmitRateScale;           // +0x194
    uint32_t               mPad198[0x230 / 4 - 0x66];
    cParticlesEffect*      mChainSystem;                    // +0x230

    void Update(float dt);
    void StepFrame();                                       // 0x00f60810 (name guessed)
    bool InitParticle(cParticle* p);                        // 0x00f5ebf0
    void ReleaseParticle(cParticle* p);                     // 0x00f5f6a0 (name guessed)
};
bool __cdecl DefaultUpdateParticle(cParticle* particle, float dt, cParticlesDescription* desc,
                                   cParticlesEffect* effect);   // 0x00f5e910

template <class T> static inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
static inline bool TestBit(uint32_t flags, int bit) { return ((flags >> bit) & 1) != 0; }

// @ 0x00f60f00
void cParticlesEffect::Update(float dt)
{
    if (dt <= 0.0f)
        return;

    float emitRate = mCurrentEmitRateScale;
    if (TestBit(mDesc->mFlags, 8))
        emitRate = mScale * emitRate;
    else if (TestBit(mDesc->mFlags, 9))
        emitRate = (mScale * mScale) * emitRate;
    else if (TestBit(mDesc->mFlags, 10))
        emitRate = (mScale * mScale * mScale) * emitRate;

    float dx = mLocation.x - mLastEmitLocation.x;
    float dy = mLocation.y - mLastEmitLocation.y;
    float dz = mLocation.z - mLastEmitLocation.z;
    float speedScale = mDesc->mRateSpeedScale;
    if (speedScale > 0.0f)
        emitRate = ((sqrtf(dx * dx + (dy * dy + dz * dz)) / dt) * speedScale + 1.0f) * emitRate;

    bool emitted = false;
    const float totalDt = dt;
    do {
        float step = Min(dt, kMaxStep);

        int nextFrame = mFrame + 1;
        mTime = step * mRate + mTime;
        if (mTime > (double)nextFrame) {
            mFrame = nextFrame;
            if (TestBit(mDesc->mFlags, 27))
                StepFrame();
            cParticlesDescription* desc = mDesc;
            if (desc->mRateCurveCycles > 0 && mFrame == desc->mRateCurveCycles) {
                if (TestBit(desc->mFlags, 2)) {
                    mFrame = desc->mRateCurveCycles - 1;
                    mTime = (double)desc->mRateCurveCycles - kRateEpsilon;
                } else {
                    if (TestBit(mDesc->mFlags, 28))
                        return;
                    mComponent.Stop(false);
                    return;
                }
            } else if (desc->mRetriggerMin >= 0.0f) {
                emitted = true;
                step = (float)((double)step - (mTime - (double)mFrame) * desc->mRateLoop);
                mTime = (double)mFrame;
            }
        }

        // sample the emission rate curve
        FloatVector& curve = mDesc->mRate;
        unsigned count = curve.size() - 1;
        double curveTime = mTime - (double)mFrame;
        float rate;
        if (count == 0) {
            rate = curve[0];
        } else {
            float t = (float)count * curveTime;
            int idx = (int)t;
            float frac = t - (float)idx;
            if (frac > 0.0f) {
                float* pa = &curve[idx];
                float a = pa[0];
                rate = (pa[1] - a) * frac + a;
            } else {
                rate = curve[idx];
            }
        }

        mParticlesToGenerate = rate * step * emitRate + mParticlesToGenerate;
        int n = FloorToInt(mParticlesToGenerate);
        mParticlesToGenerate = mParticlesToGenerate - (float)n;
        float stepPer = step / (float)n;

        float spawnTime = dt;
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
                float f = spawnTime / totalDt;
                p->mPosition.x = p->mPosition.x - dx * f;
                p->mPosition.y = p->mPosition.y - dy * f;
                p->mPosition.z = p->mPosition.z - dz * f;

                cParticlesDescription* pd = mDesc;
                tUpdateParticleFn fn = kUpdateFns[pd->mPhysicsType];
                if (fn) {
                    alive = fn(p, spawnTime, pd, this);
                } else if (pd->mDrag * spawnTime > kPoolStepThreshold) {
                    alive = DefaultUpdateParticle(p, spawnTime, pd, this);
                } else {
                    float age = p->mAge;
                    p->mAge = age + spawnTime;
                    if (age + spawnTime < p->mLife) {
                        Vector3 v0 = p->mVelocity;
                        p->mVelocity.z = mDirectionalForcesSum.z * spawnTime + p->mVelocity.z;
                        p->mVelocity.y = mDirectionalForcesSum.y * spawnTime + p->mVelocity.y;
                        p->mVelocity.x = v0.x + mDirectionalForcesSum.x * spawnTime;
                        float damp = kOne - pd->mDrag * spawnTime;
                        p->mVelocity.x = p->mVelocity.x * damp;
                        p->mVelocity.y = p->mVelocity.y * damp;
                        p->mVelocity.z = p->mVelocity.z * damp;
                        float half = spawnTime * kHalf;
                        p->mPosition.x = (p->mVelocity.x + v0.x) * half + p->mPosition.x;
                        p->mPosition.y = p->mPosition.y + (p->mVelocity.y + v0.y) * half;
                        p->mPosition.z = p->mPosition.z + (p->mVelocity.z + v0.z) * half;
                        alive = true;
                    } else {
                        alive = false;
                    }
                }
            }

            if (alive) {
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
            } else if (mChainSystem && (p->mLife <= p->mAge || TestBit(mDesc->mFlags, 27))) {
                ReleaseParticle(p);
                if (mChainSystem && mParticleCount == 0 && mDelayedStopActive)
                    mChainSystem->mComponent.Stop(false);
            } else {
                p->mpNext = sFreeParticles;
                sFreeParticles = p;
            }
            spawnTime = spawnTime - stepPer;
        }

        dt = dt - step;
        if (emitted) {
            double r = RandomRange(mDesc->mRetriggerMin, mDesc->mRetriggerMax);
            double nd = (double)dt - r;
            dt = (float)nd;
            if (nd < 0.0) {
                mRetriggerTime = -dt;
                return;
            }
        }
    } while (dt > 0.0f);
}

}} // namespace EA::Swarm
