// Slice s00ab0590: 0x00AB0D90, EA::Swarm::cParticlesEffect::Update (emit + age one time slice).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Same function as the copy at 0x00F60F00 (slice s00f60f00) from an older/other build of the effect
// class, with different field offsets (this copy has no chain-system handling: a dead particle is
// handed to DestroyParticle). Behaviour: advance the effect by `dt` seconds in steps of at most
// 1/15 s. Per step the emission rate curve (frame counter + double time accumulator, optionally
// looping / ending the effect) is sampled and scaled by the effect scale (flag bits 8..10), the
// source speed (rateSpeedScale) and the step; the fractional particle count accumulates in
// mParticlesToGenerate and that many particles are taken from the global particle pool, initialised
// (InitParticle 0x00aaeb90), back-dated by their spawn time, moved by the physics type's update
// function (table 0x015655dc; default 0x00aae900, or a simple inlined Euler step with drag for small
// drag*dt), linked into the live list while the effect's bounding box grows. After a step that
// emitted, a random retrigger delay is subtracted from dt.
// Names follow the dev PDB (cParticlesEffect / cParticlesDescription), offsets are the retail ones.
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

#define PV(n) virtual void pv##n();

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
namespace Allocator {
class FixedAllocatorBase { public: bool AddCore(int pCore, int nSize); };      // 0x00926650
}

namespace Swarm {

extern Random::RandomLinearCongruential sRandom_Swarm;     // 0x016778dc
extern Allocator::FixedAllocatorBase sParticlePool;        // 0x01679480 (name guessed)
struct cParticle;
extern cParticle* sFreeParticles;                          // 0x01679490 (name guessed)

// Random in [lo, hi], clamped (inlined everywhere in the original)
static __forceinline double RandomRange(double lo, double hi)
{
    double v = sRandom_Swarm.RandomDoubleUniform() * (hi - lo) + lo;
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

class cParticlesEffect;

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
    uint32_t mPad0c[6];
    float    mRetriggerMin;         // +0x24
    float    mRetriggerMax;         // +0x28
    uint32_t mPad2c[15];
    FloatVector mRate;              // +0x68 eastl::vector<float> (begin, end)
    uint32_t mPad70[3];
    float    mRateLoop;             // +0x7c (mRateCurveTime)
    uint16_t mRateCurveCycles;      // +0x80
    uint16_t mPad82;
    float    mRateSpeedScale;       // +0x84
    uint32_t mPad88[(0x130 - 0x88) / 4];
    uint8_t  mPhysicsType;          // +0x130
    uint8_t  mPad131[3];
    uint32_t mPad134[(0x160 - 0x134) / 4];
    float    mDrag;                 // +0x160
};

typedef bool (__cdecl *tUpdateParticleFn)(cParticle* particle, float dt, cParticlesDescription* desc,
                                          cParticlesEffect* effect);
extern tUpdateParticleFn kUpdateFns[];                      // 0x015655dc (name guessed)
extern const float kMaxStep;                                // 0x01459420 (1/15)
extern const float kHalf;                                   // 0x01471064
extern const float kOne;                                    // 0x01485720
extern const float kPoolStepThreshold;                      // 0x013ec478 (0.05)
extern const float kRateEpsilon;                            // 0x013f11c8 (1e-6)

struct IStoppable
{
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void Stop(int nStop);                           // slot 3 (0x00ab0cf0)
};

// The effect is the complete object; IStoppable is its sub-object at +0x08 (Stop casts back down).
struct CEffectBase0 { virtual void b0s0(); };
struct CEffectBase1 { virtual void b1s0(); };

struct IAudioHandle
{
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual void StopFirst(int nID, int nFlags);            // +0x24
    PV(10) PV(11) PV(12) PV(13)
    virtual void StopSecond(int nID, int nFlags);           // +0x38
};
struct IAudioSource
{
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
    virtual IAudioHandle* GetHandle();                      // +0x20
};
struct IStopSink
{
    PV(0) PV(1) PV(2)
    virtual void OnStop(int nStop);                         // +0x0c
    PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    virtual void Release();                                 // +0x38
};
struct IRefCounted
{
    PV(0)
    virtual void Release();                                 // +0x04
};
struct RefVertex;
template <class T>
struct SpVector {                                           // eastl vector with the SP allocator
    T*   mpBegin;                                           // +0x00
    T*   mpEnd;                                             // +0x04
    T*   mpCapacity;                                        // +0x08
    char mAllocator[12];                                    // +0x0c
    ~SpVector();                                            // 0x00a8c440
};
struct StopSinkHolder
{
    char       pad00[8];
    IStopSink  mSink;                                       // +0x08
};

class cParticlesEffect : public CEffectBase0, public CEffectBase1, public IStoppable
{ public:
    uint32_t               mPad0c[2];
    bool                   mStarted;                        // +0x14
    bool                   mDelayedStopActive;              // +0x15
    uint8_t                mPad16[2];
    cParticle*             mParticlesNext;                  // +0x18 intrusive_list sentinel
    cParticle*             mParticlesPrev;                  // +0x1c
    int                    mParticleCount;                  // +0x20
    cParticlesDescription* mDesc;                           // +0x24
    void*                  mpOwner;                         // +0x28
    IAudioSource*          mpAudioSource;                   // +0x2c
    uint32_t               mPad30[6];
    double                 mParticleSystemTime;             // +0x48
    int                    mCurrentCycle;                   // +0x50
    uint32_t               mPad54;
    double                 mInverseRateCurveTime;           // +0x58
    float                  mParticlesToGenerate;            // +0x60
    Vector3                mDirectionalForcesSum;           // +0x64
    uint32_t               mPad70[(0x9c - 0x70) / 4];
    float                  mRetriggerTime;                  // +0x9c
    Vector3                mBoundsMin;                      // +0xa0 (x, y, z)
    Vector3                mBoundsMax;                      // +0xac
    uint32_t               mPadb8[(0xcc - 0xb8) / 4];
    Vector3                mLocation;                       // +0xcc (source transform translation)
    float                  mScale;                          // +0xd8
    uint32_t               mPaddc[(0x138 - 0xdc) / 4];
    Vector3                mLastEmitLocation;               // +0x138
    uint32_t               mPad144[(0x190 - 0x144) / 4];
    float                  mCurrentEmitRateScale;           // +0x190
    uint32_t               mPad194[(0x1b0 - 0x194) / 4];
    IRefCounted*           mpSegmentA;                      // +0x1b0
    IRefCounted*           mpSegmentB;                      // +0x1b4
    IRefCounted*           mpSegmentC;                      // +0x1b8
    uint32_t               mPad1bc[(0x1e4 - 0x1bc) / 4];
    SpVector<RefVertex>    mVertices;                       // +0x1e4
    void*                  mpBufferA;                       // +0x1fc (counted buffer, header at -4)
    uint32_t               mPad200[(0x214 - 0x200) / 4];
    void*                  mpBufferB;                       // +0x214
    uint32_t               mPad218[(0x228 - 0x218) / 4];
    StopSinkHolder*        mpStopSlot;                      // +0x228
    uint32_t               mPad22c;                         // +0x22c
    int                    mSoundIndex2;                    // +0x230
    int                    mSoundIndex;                     // +0x234

    cParticlesEffect(cParticlesDescription* pDesc, void* pOwner);   // 0x00ab0790
    ~cParticlesEffect();                                            // 0x00ab0c30
    void Update(float dt);                                  // 0x00ab0d90
    void Emit(float dt);                                    // 0x00ab0590
    void StepFrame();                                       // 0x00ab0720
    bool InitParticle(cParticle* p);                        // 0x00aaeb90
    bool StepParticle(cParticle* p, float dt);              // 0x00aaeb20
    void DestroyParticle(cParticle* p);                     // 0x00aaf670
};
bool __cdecl UpdatePhysicsTimeStep(cParticle* particle, float dt, cParticlesDescription* desc,
                                   cParticlesEffect* effect);   // 0x00aae900
void operator delete(void* p);                                  // 0x00f47380 (CRT)

// @ 0x00ab0790
cParticlesEffect::cParticlesEffect(cParticlesDescription* pDesc, void* pOwner)
{
    mStarted = false;
    mDelayedStopActive = false;
    mPad16[0] = 1;                                          // +0x16: enabled
    mPad16[1] = 0;
    mParticlesNext = (cParticle*)&mParticlesNext;           // intrusive list head
    mParticlesPrev = (cParticle*)&mParticlesNext;
    mParticleCount = 0;
    mDesc = pDesc;
    mpOwner = pOwner;
    mpAudioSource = 0;
    mParticleSystemTime = 0.0;
    mCurrentCycle = 0;
    mInverseRateCurveTime = -1.0;
    mParticlesToGenerate = 0.0f;
    mDirectionalForcesSum = Vector3(0.0f, 0.0f, 0.0f);
    mRetriggerTime = 0.0f;
    mBoundsMin = Vector3(0.0f, 0.0f, 0.0f);
    mBoundsMax = Vector3(0.0f, 0.0f, 0.0f);
    mLocation = Vector3(0.0f, 0.0f, 0.0f);
    mScale = 0.0f;
    mLastEmitLocation = Vector3(0.0f, 0.0f, 0.0f);
    mCurrentEmitRateScale = 0.0f;
    mpSegmentA = 0;
    mpSegmentB = 0;
    mpSegmentC = 0;
    mVertices.mpBegin = 0;
    mVertices.mpEnd = 0;
    mVertices.mpCapacity = 0;
    mpBufferA = 0;
    mpBufferB = 0;
    mpStopSlot = 0;
    mPad22c = 0;
    mSoundIndex2 = -1;
    mSoundIndex = -1;
}

// @ 0x00ab0c30
cParticlesEffect::~cParticlesEffect()
{
    if (mpStopSlot)
        mpStopSlot->mSink.Release();                        // vtable slot +0x38
    if (mpBufferA)
        operator delete(mpBufferA);
    if (mpBufferB)
        operator delete(mpBufferB);
    // mVertices (SpVector<RefVertex>, dtor 0x00a8c440) and the particle list head (IntrusiveList,
    // dtor 0x00620230) are destroyed by their own member destructors, then the base vptrs are reset.
    if (mpSegmentC)
        mpSegmentC->Release();
    if (mpSegmentB)
        mpSegmentB->Release();
    if (mpSegmentA)
        mpSegmentA->Release();
}

template <class T> static inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
static inline bool TestBit(uint32_t flags, int bit) { return ((flags >> bit) & 1) != 0; }

// @ 0x00ab0d90
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
        emitRate = ((sqrtf(dz * dz + (dy * dy + dx * dx)) / dt) * speedScale + 1.0f) * emitRate;

    bool emitted = false;
    const float totalDt = dt;
    do {
        float step = Min(dt, kMaxStep);

        int nextCycle = mCurrentCycle + 1;
        mParticleSystemTime = step * mInverseRateCurveTime + mParticleSystemTime;
        if (mParticleSystemTime > (double)nextCycle) {
            mCurrentCycle = nextCycle;
            if (TestBit(mDesc->mFlags, 27))
                StepFrame();
            cParticlesDescription* desc = mDesc;
            if (desc->mRateCurveCycles > 0 && mCurrentCycle == desc->mRateCurveCycles) {
                if (TestBit(desc->mFlags, 2)) {
                    mCurrentCycle = desc->mRateCurveCycles - 1;
                    mParticleSystemTime = (double)desc->mRateCurveCycles - kRateEpsilon;
                } else {
                    if (TestBit(mDesc->mFlags, 28))
                        return;
                    static_cast<IStoppable&>(*this).Stop(false);
                    return;
                }
            } else if (desc->mRetriggerMin >= 0.0f) {
                emitted = true;
                step = (float)((double)step - (mParticleSystemTime - (double)mCurrentCycle) * desc->mRateLoop);
                mParticleSystemTime = (double)mCurrentCycle;
            }
        }

        // sample the emission rate curve
        FloatVector& curve = mDesc->mRate;
        unsigned count = curve.size() - 1;
        double curveTime = mParticleSystemTime - (double)mCurrentCycle;
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
        int n = (int)mParticlesToGenerate;
        mParticlesToGenerate = mParticlesToGenerate - (float)n;
        // align(16) is a codegen lever only: the original has a 16-byte-aligned ebp frame (and esp,-16) from a
        // local we could not identify; any aligned local reproduces that prologue and avoids the tail-call jmp
        // for the Stop() call that the unaligned frame allows.
        __declspec(align(16)) float stepPer = step / (float)n;

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
                    alive = UpdatePhysicsTimeStep(p, spawnTime, pd, this);
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
            } else {
                DestroyParticle(p);
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

// @ 0x00ab0720
void cParticlesEffect::StepFrame()
{
    cParticle* pHead = (cParticle*)&mParticlesNext;
    cParticle* p = pHead->mpNext;
    while (p != pHead) {
        cParticle* const pPrev = p->mpPrev;
        cParticle* const pNext = p->mpNext;
        pPrev->mpNext = pNext;
        pNext->mpPrev = pPrev;
        p->mpNext = 0;
        p->mpPrev = 0;
        --mParticleCount;
        DestroyParticle(p);
        p = pNext;
    }
    for (cParticle* q = pHead->mpNext; q != pHead; ) {
        cParticle* qNext = q->mpNext;
        q->mpPrev = 0;
        q->mpNext = 0;
        q = qNext;
    }
    pHead->mpNext = pHead;
    pHead->mpPrev = pHead;
}

// @ 0x00ab0590
void cParticlesEffect::Emit(float dt)
{
    double t = (double)dt * mInverseRateCurveTime + mParticleSystemTime;
    mParticleSystemTime = t;
    if ((double)mCurrentCycle > t)
        return;

    float rate = mDesc->mRate.mpBegin[0] * mCurrentEmitRateScale;
    // The original inlines ceil() through the SSE rounding conversion (cvtss2si) plus a fix-up.
    int n = _mm_cvt_ss2si(_mm_set_ss(rate));
    if ((float)n < rate)
        ++n;
    n -= mParticleCount;
    for (; n > 0; --n) {
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

        if (InitParticle(p) && StepParticle(p, dt)) {
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
        } else {
            DestroyParticle(p);
        }
    }
}

// @ 0x00ab0cf0
void IStoppable::Stop(int nStop)
{
    // IStoppable is the sub-object at +0x08 of cParticlesEffect (see the class bases above); the
    // adjustment is written at each use so the compiler keeps `this` as the base pointer.
#define PE (*((cParticlesEffect*)((char*)this - 8)))
    if (!PE.mStarted)
        return;
    if (PE.mpStopSlot && PE.mParticleCount == 0)
        PE.mpStopSlot->mSink.OnStop(nStop);
    PE.mDelayedStopActive = (nStop == 0);
    if (PE.mDelayedStopActive)
        return;
    PE.mStarted = false;
    PE.StepFrame();
    if (PE.mSoundIndex >= 0) {
        IAudioHandle* pHandle = PE.mpAudioSource->GetHandle();
        pHandle->StopFirst(PE.mSoundIndex, 0);
        return;
    }
    if (PE.mSoundIndex2 >= 0) {
        IAudioHandle* pHandle = PE.mpAudioSource->GetHandle();
        pHandle->StopSecond(PE.mSoundIndex2, 0);
    }
#undef PE
}

}} // namespace EA::Swarm
