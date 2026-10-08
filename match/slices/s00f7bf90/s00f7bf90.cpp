// Slice s00f7bf90: 0x00F7BF90, EA::Swarm particles effect (older cParticlesEffect.obj copy, like
// s00f79bb0 / s00f7caf0): emit new particles for a time step and advance them.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Older-layout twin of cParticlesEffect::GenerateNewParticles (0x00ab1840, called from
// ApplyEffect, whose older twin 0x00f7caf0 calls this function at the same place).  NAMING NOTE:
// no symbol is known for 0x00F7BF90; the class is called cParticlesEffectOld (Claude-coined, as in
// s00f79bb0) and the method follows the newer twin's name.
//
// The emission rate follows a rate curve over the cycle time; for every step of at most 1/15 s
// the integer part of the accumulated emission count becomes new particles (each initialised by
// InitParticle, back-dated along the emitter's movement, then advanced by the physics callback or
// the inline default physics and linked into the live list with the bounding box grown).  When the
// effect restarts (cycle wrap with a random restart delay) the remaining time is reduced by that
// delay; a negative remainder is stored as the leftover (+0x84).
#include "types.h"

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

struct Vector3 {
    float x, y, z;
};

namespace EA {
namespace Random {
struct RandomLinearCongruential {
    uint32_t mnSeed;
    double RandomDoubleUniform();                 // 0x009360d0
};
}  // namespace Random
namespace SP { extern Random::RandomLinearCongruential sMathRandom; }   // 0x01601760
}  // namespace EA

// float -> int, rounding toward minus infinity (the module's asm helper: cvtss2si + cmovb)
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

// Random in [lo, hi], clamped (inlined in the original)
static __forceinline double RandomRangeM(double lo, double hi)
{
    double v = EA::SP::sMathRandom.RandomDoubleUniform() * (hi - lo) + lo;
    if (v >= hi)
        return hi;
    if (lo > v)
        return lo;
    return v;
}

static inline bool TestBit(uint32_t flags, int bit) { return ((flags >> bit) & 1) != 0; }

template <class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }

static const float kMaxStep = 0.06666667f;       // 0x0148feb0 (1/15 s)
static const float kCycleEpsilon = 1e-06f;       // 0x013f11c8

struct cParticle {
    cParticle* mpNext;                           // +0x00 intrusive_list_node
    cParticle* mpPrev;                           // +0x04
    float      mAge;                             // +0x08
    float      mLife;                            // +0x0c
    Vector3    mPosition;                        // +0x10
    Vector3    mVelocity;                        // +0x1c
};

// Fixed-size particle pool (global at 0x016c9b58): free list head at +0x10.
struct cParticlePool {
    uint32_t   mPad[4];
    cParticle* mpFreeHead;                       // +0x10 (0x016c9b68)
    bool AddCore(int a, int b);                  // 0x00926650 EA::Allocator::FixedAllocatorBase::AddCore
};
extern cParticlePool sParticlePool;              // 0x016c9b58

struct cParticlesDescription {
    uint32_t mPad0[2];
    uint32_t mFlags;                             // +0x08 (bit 2: loop, 8/9/10: scale by emitter scale,
                                                 //        27: kill on spawn, 28: no auto stop)
    uint32_t mPad0c[(0x24 - 0x0c) / 4];
    float    mRestartMin;                        // +0x24 (>= 0: restart with random delay)
    float    mRestartMax;                        // +0x28
    uint32_t mPad2c[(0x68 - 0x2c) / 4];
    float*   mRateCurveBegin;                    // +0x68 eastl::vector<float>
    float*   mRateCurveEnd;                      // +0x6c
    uint32_t mPad70[(0x7c - 0x70) / 4];
    float    mRestartBackdate;                   // +0x7c
    uint16_t mNumCycles;                         // +0x80
    uint16_t mPad82;
    float    mVelocityScale;                     // +0x84
    uint32_t mPad88[(0x130 - 0x88) / 4];
    uint8_t  mPhysicsType;                       // +0x130
    uint8_t  mPad131[3];
    uint32_t mPad134[(0x160 - 0x134) / 4];
    float    mDrag;                              // +0x160
};

class cParticlesEffectOld;
typedef bool (*PhysicsUpdateFn)(cParticle* p, float dt, cParticlesDescription* desc, cParticlesEffectOld* effect);
extern PhysicsUpdateFn sPhysicsUpdate[];         // 0x015B0EBC

struct IComponent {
    virtual void c00();
    virtual void c04();
    virtual void c08();
    virtual bool Stop(bool hard);                // +0x0C
};

class cParticlesEffectOld {
public:
    char       mPad0[8];
    IComponent mComponent;                       // +0x08 (vptr only)
    char       mPad0c[0x15 - 0x0c];
    bool       mDelayedStopActive;               // +0x15
    char       mPad16[0x18 - 0x16];
    cParticle* mpListNext;                       // +0x18 intrusive_list sentinel
    cParticle* mpListPrev;                       // +0x1c
    int        mParticleCount;                   // +0x20
    cParticlesDescription* mDesc;                // +0x24
    char       mPad28[0x48 - 0x28];
    double     mParticleSystemTime;              // +0x48
    int        mCycle;                           // +0x50
    char       mPad54[4];
    double     mCycleRate;                       // +0x58
    float      mEmitAccumulator;                 // +0x60
    Vector3    mDirectionalForcesSum;            // +0x64
    char       mPad70[0x84 - 0x70];
    float      mLeftoverTime;                    // +0x84
    Vector3    mBBMin;                           // +0x88
    Vector3    mBBMax;                           // +0x94
    char       mPada0[0xb4 - 0xa0];
    Vector3    mSourcePosition;                  // +0xb4
    float      mSourceScale;                     // +0xc0
    char       mPadc4[0x120 - 0xc4];
    Vector3    mLastEmitLocation;                // +0x120
    char       mPad12c[0x174 - 0x12c];
    float      mCurrentEmitRateScale;            // +0x174
    char       mPad178[0x218 - 0x178];
    cParticlesEffectOld* mChainSystem;           // +0x218

    bool InitParticle(cParticle* p);             // 0x00f79bf0
    void FUN_00f7bd70();
    void FUN_00f7a5d0(cParticle* p);
    void GenerateNewParticles(float deltaTime);  // 0x00f7bf90
};

// @ 0x00f7bf90
void cParticlesEffectOld::GenerateNewParticles(float dt)
{
    if (0.0f >= dt)
        return;

    cParticlesDescription* desc = mDesc;
    uint32_t flags = desc->mFlags;
    float scale = mCurrentEmitRateScale;
    if (TestBit(flags, 8)) {
        scale = mSourceScale * scale;
    } else if (TestBit(flags, 9)) {
        float s = mSourceScale;
        scale = (s * s) * scale;
    } else if (TestBit(flags, 10)) {
        float s = mSourceScale;
        scale = ((s * s) * s) * scale;
    }

    // Distance the emitter moved since the last emission.
    Vector3 delta;
    delta.x = mSourcePosition.x - mLastEmitLocation.x;
    delta.y = mSourcePosition.y - mLastEmitLocation.y;
    delta.z = mSourcePosition.z - mLastEmitLocation.z;
    float velocityScale = desc->mVelocityScale;
    if (0.0f < velocityScale)
        scale = (((float)(sqrt(delta.y * delta.y + delta.x * delta.x + delta.z * delta.z) / dt)) * velocityScale + 1.0f) * scale;

    const float totalTime = dt;
    bool restarted = false;
    do {
        float step = Min(dt, kMaxStep);

        // Advance the cycle clock.
        int nextCycle = mCycle + 1;
        double t = (double)step * mCycleRate + mParticleSystemTime;
        mParticleSystemTime = t;
        if (t > (double)nextCycle) {
            mCycle = nextCycle;
            if (TestBit(mDesc->mFlags, 27))
                FUN_00f7bd70();
            cParticlesDescription* d = mDesc;
            unsigned short numCycles = d->mNumCycles;
            if (numCycles > 0 && mCycle == numCycles) {
                if (!TestBit(d->mFlags, 2)) {
                    if (!TestBit(mDesc->mFlags, 28))
                        mComponent.Stop(false);
                    return;
                }
                mCycle = numCycles - 1;
                mParticleSystemTime = numCycles - kCycleEpsilon;
            } else if (d->mRestartMin >= 0.0f) {
                restarted = true;
                step = (float)(step - (mParticleSystemTime - mCycle) * d->mRestartBackdate);
                mParticleSystemTime = (double)mCycle;
            }
        }

        // Emission rate from the rate curve at the current cycle position.
        cParticlesDescription* cd = mDesc;
        double frac = mParticleSystemTime - mCycle;
        uint32_t n = (uint32_t)(cd->mRateCurveEnd - cd->mRateCurveBegin) - 1;
        float rate;
        if (n == 0) {
            rate = cd->mRateCurveBegin[0];
        } else {
            float f = (float)n * frac;
            int i = (int)f;
            float fr = f - (float)i;
            if (fr > 0.0f) {
                float a = cd->mRateCurveBegin[i];
                rate = (cd->mRateCurveBegin[i + 1] - a) * fr + a;
            } else {
                rate = cd->mRateCurveBegin[i];
            }
        }

        mEmitAccumulator = rate * step * scale + mEmitAccumulator;
        int count = FloorToInt(mEmitAccumulator);
        mEmitAccumulator = mEmitAccumulator - (float)count;
        float stepPerParticle = step / (float)count;
        float tLeft = dt;
        for (int i = 0; i < count; i++) {
            // Take a particle from the pool (growing it when empty).
            cParticle* p;
            for (;;) {
                p = sParticlePool.mpFreeHead;
                if (p) {
                    sParticlePool.mpFreeHead = p->mpNext;
                    p->mpPrev = 0;
                    p->mpNext = 0;
                    break;
                }
                if (!sParticlePool.AddCore(0, 0)) {
                    p = 0;
                    break;
                }
            }

            if (!InitParticle(p)) {
                if (!mChainSystem || (p->mAge < p->mLife && !TestBit(mDesc->mFlags, 27))) {
                    p->mpNext = sParticlePool.mpFreeHead;
                    sParticlePool.mpFreeHead = p;
                } else {
                    goto kill;
                }
            } else {
                float ratio = tLeft / totalTime;
                p->mPosition.x = p->mPosition.x - delta.x * ratio;
                p->mPosition.y = p->mPosition.y - delta.y * ratio;
                p->mPosition.z = p->mPosition.z - delta.z * ratio;

                cParticlesDescription* pd = mDesc;
                bool alive;
                if (sPhysicsUpdate[pd->mPhysicsType]) {
                    alive = sPhysicsUpdate[pd->mPhysicsType](p, tLeft, pd, this);
                } else {
                    float age = p->mAge;
                    p->mAge = age + tLeft;
                    if (age + tLeft < p->mLife) {
                        float fy = mDirectionalForcesSum.y;
                        float fz = mDirectionalForcesSum.z;
                        float oldVz = p->mVelocity.z;
                        float oldVx = p->mVelocity.x;
                        float oldVy = p->mVelocity.y;
                        float vx = mDirectionalForcesSum.x * tLeft + oldVx;
                        p->mVelocity.x = vx;
                        float vz = fz * tLeft + p->mVelocity.z;
                        p->mVelocity.z = vz;
                        float vy = fy * tLeft + oldVy;
                        p->mVelocity.y = vy;
                        float damp = 1.0f - pd->mDrag * tLeft;
                        vx = vx * damp;
                        p->mVelocity.x = vx;
                        vy = vy * damp;
                        p->mVelocity.y = vy;
                        vz = vz * damp;
                        p->mVelocity.z = vz;
                        float half = tLeft * 0.5f;
                        p->mPosition.y = p->mPosition.y + (vy + oldVy) * half;
                        p->mPosition.x = (vx + oldVx) * half + p->mPosition.x;
                        p->mPosition.z = p->mPosition.z + (vz + oldVz) * half;
                        alive = true;
                    } else {
                        alive = false;
                    }
                }

                if (alive) {
                    // Link at the tail of the live list and grow the bounding box.
                    p->mpPrev = mpListPrev;
                    p->mpNext = (cParticle*)&mpListNext;
                    ((cParticle*)&mpListNext)->mpPrev = p;
                    p->mpPrev->mpNext = p;
                    mParticleCount++;
                    if (mBBMin.x > p->mPosition.x) mBBMin.x = p->mPosition.x;
                    if (p->mPosition.x > mBBMax.x) mBBMax.x = p->mPosition.x;
                    if (mBBMin.y > p->mPosition.y) mBBMin.y = p->mPosition.y;
                    if (p->mPosition.y > mBBMax.y) mBBMax.y = p->mPosition.y;
                    if (mBBMin.z > p->mPosition.z) mBBMin.z = p->mPosition.z;
                    if (p->mPosition.z > mBBMax.z) mBBMax.z = p->mPosition.z;
                } else if (mChainSystem && (p->mAge >= p->mLife || TestBit(mDesc->mFlags, 27))) {
                    goto kill;
                } else {
                    p->mpNext = sParticlePool.mpFreeHead;
                    sParticlePool.mpFreeHead = p;
                }
            }
            goto next;
        kill:
            FUN_00f7a5d0(p);
            if (mChainSystem && mParticleCount == 0 && mDelayedStopActive)
                mChainSystem->mComponent.Stop(false);
        next:
            tLeft = tLeft - stepPerParticle;
        }

        dt = dt - step;
        if (restarted) {
            cParticlesDescription* rd = mDesc;
            double v = RandomRangeM((double)rd->mRestartMin, (double)rd->mRestartMax);
            double nd = (double)dt - v;
            dt = (float)nd;
            if (nd < 0.0) {
                mLeftoverTime = -dt;
                return;
            }
        }
    } while (dt > 0.0f);
}
