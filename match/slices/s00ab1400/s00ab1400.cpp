// Slice s00ab1400: EA::Swarm::cParticlesEffect::ApplyEffect @ 0x00AB18D0 (2578 bytes).
// Name from the 2008 dev build (work/devbuild/symbols.json: ParticlesEffect.obj
// EA::Swarm::cParticlesEffect::ApplyEffect, 2534 bytes at dev 0x0144D310, same body and callees:
// cTransform::TransformPoint, cTransform::BackTransformVector, cRWState::AccumulateForce,
// sPhysicsUpdate[], UpdatePhysicsTimeStep, DestroyParticle, GenerateNewParticles,
// cBoundingBox::Transform, cRWState::Update).
// It overrides a cIComponent virtual, so `this` is the cComponentBase subobject (effect + 8) and
// member offsets in the disassembly are the dev-PDB offsets minus 8.
// Retail layout = dev PDB cParticlesEffect / cParticlesDescription with 0x14-byte eastl vectors
// (description offsets after mRateCurve shift by 4 per vector).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace EA { namespace Swarm {

struct Vector3
{
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    Vector3 operator+(const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
    Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    void Set(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }
    Vector3& operator+=(const Vector3& v) { Set(v.x + x, v.y + y, v.z + z); return *this; }
    Vector3& operator*=(float s) { Set(x * s, y * s, z * s); return *this; }
    float SquaredLength() const { return x * x + y * y + z * z; }
};
struct Vector2
{
    float x, y;
    float Lerp(float t) const { return (y - x) * t + x; }
};

extern float kFXMaxFloat;                    // 0x01565620
extern float kEmitFrameMoveLimitSqr;         // 0x01565634 (35^2)

struct cBoundingBox
{
    Vector3 mMin;
    Vector3 mMax;
    void Reset()
    {
        mMin = Vector3(kFXMaxFloat, kFXMaxFloat, kFXMaxFloat);
        mMax = Vector3(-kFXMaxFloat, -kFXMaxFloat, -kFXMaxFloat);
    }
    void AddPoint(const Vector3& p)
    {
        if (p.x < mMin.x) mMin.x = p.x;
        if (p.x > mMax.x) mMax.x = p.x;
        if (p.y < mMin.y) mMin.y = p.y;
        if (p.y > mMax.y) mMax.y = p.y;
        if (p.z < mMin.z) mMin.z = p.z;
        if (p.z > mMax.z) mMax.z = p.z;
    }
    void Transform(const struct cTransform& xf);                 // 0x006E95A0
};

struct cTransform
{
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3 mTranslation;                                         // +0x04
    float mScale;                                                 // +0x10
    float mRotation[9];                                           // +0x14
    void TransformPoint(Vector3& v) const;                        // 0x007CDEE0
    void BackTransformVector(Vector3& v) const;                   // 0x00A78E90
};

template<int N> struct bitset
{
    uint32_t mWord[(N + 31) / 32];
    bool test(int i) const { return ((mWord[i >> 5] >> (i & 31)) & 1) != 0; }
};

template<class T> struct vector
{
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    T* begin() const { return mpBegin; }
    T* end() const { return mpEnd; }
};

struct cRandomWalk { uint32_t pad[0x34 / 4]; };

struct cRWState
{
    float mNextTime;
    float mStrengthV;
    float mStrengthH;
    float mTheta;
    float mGamma;
    uint32_t mTurnCounter;
    void Update(const cRandomWalk& rw);                           // 0x00A790A0
    void AccumulateForce(Vector3& force);                         // 0x00A79300
};

enum
{
    kParticleFlagIgnoreLOD0 = 0,
    kParticleFlagIgnoreLOD1 = 1,
    kParticleFlagSizeScaleTransform = 11,
    kParticleFlagRandomWalk = 19,
    kParticleFlagModelStats = 21,
    kParticleFlagAttractor = 24,
    kParticleFlagScaleSizeOnly = 25,
    kParticleFlagSingleCycle = 28
};

struct cParticlesDescription
{
    uint32_t pad_00[2];
    bitset<34> mFlags;                                            // +0x08
    Vector2 mParticleLifetime;                                    // +0x10
    float mPrerollTime;                                           // +0x18
    uint32_t pad_1c[(0x24 - 0x1C) / 4];
    Vector2 mEmitInterval;                                        // +0x24 (random interval, in cycles)
    uint32_t pad_2c[(0x68 - 0x2C) / 4];
    vector<float> mRateCurve;                                     // +0x68
    float mRateCurveTime;                                         // +0x7C
    uint16_t mMaxCycles;                                          // +0x80 (0 = unlimited)
    uint8_t pad_82[0x130 - 0x82];
    uint8_t mPhysicsType;                                         // +0x130
    uint8_t pad_131[0x13C - 0x131];
    Vector3 mDirectionalForcesSum;                                // +0x13C
    float mWindStrength;                                          // +0x148
    float mGravityStrength;                                       // +0x14C
    float mRadialForce;                                           // +0x150
    Vector3 mRadialForceLocation;                                 // +0x154
    float mDrag;                                                  // +0x160
    uint32_t pad_164[(0x200 - 0x164) / 4];
    cRandomWalk mRandomWalk;                                      // +0x200
    Vector3 mAttractorOrigin;                                     // +0x234
};

struct cGlobalParams
{
    float mParticleDensity;                                       // +0x00
    float mParticleScale;                                         // +0x04
    int mParticleMultThreshold;                                   // +0x08
    uint32_t pad_0c[(0xBC - 0x0C) / 4];
    Vector3 mWindDirection;                                       // +0xBC
    float mWindPointStrength;                                     // +0xC8
    Vector3 mWindPoint;                                           // +0xCC
    Vector3 mGravityDirection;                                    // +0xD8
};

struct cParticle
{
    cParticle* mpNext;                                            // intrusive_list_node
    cParticle* mpPrev;
    float mAge;                                                   // +0x08
    float mLifeTime;                                              // +0x0C
    Vector3 mPosition;                                            // +0x10
    Vector3 mVelocity;                                            // +0x1C
};

struct intrusive_list
{
    cParticle* mpNext;
    cParticle* mpPrev;
    cParticle* begin() { return mpNext; }
    cParticle* end() { return (cParticle*)this; }
    cParticle* erase(cParticle* pNode)
    {
        cParticle* const pPrev = pNode->mpPrev;
        cParticle* const pNext = pNode->mpNext;
        pPrev->mpNext = pNext;
        pNext->mpPrev = pPrev;
        pNode->mpNext = 0;
        pNode->mpPrev = 0;
        return pNext;
    }
};

// Free-list allocator the effect draws its cParticle nodes from
// (dev: EA::Allocator::FixedAllocatorBase_s0092_6410, global pool + free-list head).
struct cParticlePool
{
    uint32_t pad_00[4];                                           // +0x00
    cParticle* mpFreeList;                                        // +0x10
    bool AddCore(void* pCore, uint32_t count);                    // 0x00926650
    cParticle* Allocate()
    {
        cParticle* p;
        while ((p = mpFreeList) == 0) {
            if (!AddCore(0, 0))
                return 0;
        }
        mpFreeList = p->mpNext;
        p->mpPrev = 0;
        p->mpNext = 0;
        return p;
    }
};
#define g_ParticlePool (*(cParticlePool*)0x01679480)

// Global random stream the effect schedules its next emission with.
struct cRandomGlobal
{
    double RandomDouble();                                        // 0x009360D0
};
#define g_Random (*(cRandomGlobal*)0x016778DC)

// Havok constants the compiler shared with its own literal pool (1.0f, 0.0f, 0.5f)
// and the effect's own link-time constants.
#define HK_ONE            (*(const float*)0x01485720)
#define HK_ZERO           (*(const float*)0x01485378)
#define HK_HALF           (*(const float*)0x01471064)
#define K_DRAG_TIME_LIMIT (*(const float*)0x013EC478)             // 0.05f
#define K_EMIT_TIME_EPS   (*(const float*)0x013EB960)             // 0.01f

// Debug operator new[] the effect object is allocated with.
void* __cdecl SwarmAllocDebug(size_t size, const char* pName, int flags, int debugFlags,
                              const char* file, int line);        // 0x00F473A0
#define K_SWARM_ALLOC_NAME ((const char*)0x013F1FDC)              // "Swarm"
#define K_PARTICLES_EFFECT_SIZE 0x240

class cIRenderer
{ public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void UpdateTextureParticles(int id, const cBoundingBox& box, float maxSize);   // +0x20
    virtual void StopTextureParticles(int id, int arg);                                    // +0x24
    virtual void v28(); virtual void v2c(); virtual void v30();
    virtual void UpdateModelParticles(int id, const cBoundingBox& box, float maxSize);     // +0x34
    virtual void StopModelParticles(int id, int arg);                                      // +0x38
};

class cIEffectsWorld
{ public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual cIRenderer* GetRenderer();                                                     // +0x20
};

struct cSurfaceInfo;
struct cSurfaceRec
{
    struct cISurface
    {
        virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
        virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
        virtual void InitState(cSurfaceInfo* info, const cTransform& src, const cTransform& rigid, uint8_t* state); // +0x20
    };
    cISurface* mpSurface;                                         // +0x00
    cSurfaceInfo* mpInfo;                                         // +0x04
    uint32_t field_8;
    uint32_t mStateOffset;                                        // +0x0C
    uint32_t field_10;
    uint32_t field_14;
};

struct cStats
{
    uint32_t pad_00[4];
    int mTextureParticles;                                        // +0x10
    int mTextureParticlesRendered;                                // +0x14
    int mModelParticles;                                          // +0x18
    int mModelParticlesRendered;                                  // +0x1C
};

class cParticlesEffect;
typedef bool (*PhysicsUpdateFn)(cParticle* p, float dt, cParticlesDescription* desc, cParticlesEffect* effect);
extern PhysicsUpdateFn sPhysicsUpdate[];                          // 0x015655DC
bool UpdatePhysicsTimeStep(cParticle* p, float dt, cParticlesDescription* desc, cParticlesEffect* effect); // 0x00AAE900

class cITextureParticleStreamer { public: virtual void StreamTextureParticles(); };
class cIModelParticleStreamer { public: virtual void StreamModelParticles(); };
class cIComponent
{ public:
    virtual void c00();
    virtual void c04();
    virtual void c08();
    virtual bool Stop(bool hard);                                 // +0x0C
    virtual void ApplyEffect(float deltaTime, float lodFactor, cStats* stats);
};
class cComponentBase : public cIComponent { public: uint32_t mRefCountBase[2]; };

class cParticlesEffect : public cITextureParticleStreamer, public cIModelParticleStreamer, public cComponentBase
{
public:
    bool mStarted;                                                // +0x14
    bool mDelayedStopActive;                                      // +0x15
    bool mIsVisible;                                              // +0x16
    intrusive_list mParticles;                                    // +0x18
    int mParticleCount;                                           // +0x20
    cParticlesDescription* mDesc;                                 // +0x24
    int mCollectionIndex;                                         // +0x28
    cIEffectsWorld* mWorld;                                       // +0x2C
    cGlobalParams* mGlobalParams;                                 // +0x30
    uint32_t pad_34;
    double mOverallTime;                                          // +0x38
    bool mPreroll;                                                // +0x40
    double mParticleSystemTime;                                   // +0x48
    int mCurrentCycle;                                            // +0x50
    double mInverseRateCurveTime;                                 // +0x58
    float mParticlesToGenerate;                                   // +0x60
    Vector3 mDirectionalForcesSum;                                // +0x64
    cRWState mRandomWalkState;                                    // +0x70
    float mAttractorForce;                                        // +0x88
    Vector3 mAttractorLocation;                                   // +0x8C
    float mAttractorIntensity;                                    // +0x98
    float mRetriggerTime;                                         // +0x9C
    cBoundingBox mBoundingBox;                                    // +0xA0
    float mMaxParticleSize;                                       // +0xB8
    Vector3 mLocation;                                            // +0xBC
    cTransform mSourceTransform;                                  // +0xC8
    cTransform mRigidTransform;                                   // +0x100
    Vector3 mLastEmitLocation;                                    // +0x138
    uint16_t mRenderCount;                                        // +0x144
    uint16_t mLastRenderCount;                                    // +0x146
    Vector2 mLODEmitScale;                                        // +0x148
    Vector2 mLODSizeScale;                                        // +0x150
    Vector2 mLODAlphaScale;                                       // +0x158
    float mEmitVelocityScale;                                     // +0x160
    float mEmitScale;                                             // +0x164
    float mLifeScale;                                             // +0x168
    float mSizeScale;                                             // +0x16C
    float mAlphaScale;                                            // +0x170
    Vector3 mColorScale;                                          // +0x174
    float mMapForceScale;                                         // +0x180
    int mFrameStart;                                              // +0x184
    Vector2 mParamAltitudeRange;                                  // +0x188
    float mCurrentEmitRateScale;                                  // +0x190
    float mCurrentEmitSizeScale;                                  // +0x194
    float mCurrentSizeScale;                                      // +0x198
    float mCurrentAlphaScale;                                     // +0x19C
    float mCurrentMapForceScale;                                  // +0x1A0
    Vector3 mCurrentColorScale;                                   // +0x1A4
    uint32_t pad_1b0[(0x1E4 - 0x1B0) / 4];
    vector<cSurfaceRec> mSurfaceRecs;                             // +0x1E4
    bool mSurfaceStateDataValid;                                  // +0x1F8
    vector<uint8_t> mSurfaceStateData;                            // +0x1FC
    uint32_t pad_210[(0x228 - 0x210) / 4];
    cParticlesEffect* mChainSystem;                               // +0x228
    bool mSuppressEmission;                                       // +0x22C
    int mModelParticlesID;                                        // +0x230
    int mTextureParticlesID;                                      // +0x234

    void DestroyParticle(cParticle* p);                           // 0x00AAF670
    void RemoveParticle(cParticle* p)
    {
        --mParticleCount;
        DestroyParticle(p);
    }
    bool InitParticle(cParticle* p);                              // 0x00AAEB90
    void StepFrame();                                             // 0x00AB0720
    void Emit(float deltaTime);                                   // 0x00AB0590
    void Update(float deltaTime);                                 // 0x00AB0D90
    void AddRateCurveParticles(float deltaTime);                  // 0x00AB1400
    cParticlesEffect* ConstructInPlace(uint32_t a, uint32_t b);   // 0x00AB0790
    void GenerateNewParticles(float deltaTime);                   // 0x00AB1840
    virtual void ApplyEffect(float deltaTime, float lodFactor, cStats* stats);
};

// Inlined here (dev: EA::Swarm::UpdatePhysicsSimple).
__forceinline bool UpdatePhysicsSimple(cParticle* p, float dt, cParticlesDescription* desc, cParticlesEffect* effect)
{
    p->mAge += dt;
    if (p->mAge >= p->mLifeTime)
        return false;
    Vector3 oldVelocity = p->mVelocity;
    p->mVelocity += effect->mDirectionalForcesSum * dt;
    p->mVelocity *= 1.0f - desc->mDrag * dt;
    p->mPosition += (p->mVelocity + oldVelocity) * (dt * 0.5f);
    return true;
}

// @ 0x00AB18D0
void cParticlesEffect::ApplyEffect(float deltaTime, float lodFactor, cStats* stats)
{
    if (mPreroll) {
        if (mDesc->mFlags.test(kParticleFlagSingleCycle)) {
            mParticleSystemTime = 1.0;
            mPreroll = false;
        } else {
            deltaTime += mDesc->mPrerollTime;
            mPreroll = false;
        }
    } else if (mRenderCount > mLastRenderCount) {
        int n = (mRenderCount - mLastRenderCount) * mParticleCount;
        if (mDesc->mFlags.test(kParticleFlagModelStats))
            stats->mModelParticlesRendered += n;
        else
            stats->mTextureParticlesRendered += n;
        mLastRenderCount = mRenderCount;
    }

    if (deltaTime < 0.0f)
        return;

    if (mDesc->mFlags.test(kParticleFlagSingleCycle) && !mDelayedStopActive) {
        float timeLeft = (float)(1.0 - mParticleSystemTime) * mDesc->mRateCurveTime - 0.01f;
        if (timeLeft <= 0.0f)
            deltaTime = 0.0f;
        else if (deltaTime > timeLeft)
            deltaTime = timeLeft;
    }

    Vector3 location = mSourceTransform.mTranslation;
    if ((location - mLastEmitLocation).SquaredLength() > kEmitFrameMoveLimitSqr)
        mLastEmitLocation = location;

    mCurrentEmitRateScale = mLODEmitScale.Lerp(lodFactor) * mEmitScale;
    float sizeScale = mLODSizeScale.Lerp(lodFactor) * mSizeScale;
    mCurrentAlphaScale = mLODAlphaScale.Lerp(lodFactor) * mAlphaScale;
    mCurrentColorScale = mColorScale;
    if (mDesc->mFlags.test(kParticleFlagScaleSizeOnly)) {
        mCurrentEmitSizeScale = 1.0f;
        mCurrentSizeScale = sizeScale;
    } else {
        mCurrentEmitSizeScale = sizeScale;
        mCurrentSizeScale = 1.0f;
    }
    if (mDesc->mFlags.test(kParticleFlagSizeScaleTransform))
        mCurrentEmitSizeScale *= mSourceTransform.mScale;

    if (!(mDesc->mFlags.test(kParticleFlagIgnoreLOD0) || mDesc->mFlags.test(kParticleFlagIgnoreLOD1)) ||
        mDesc->mRateCurve[0] > (float)mGlobalParams->mParticleMultThreshold) {
        mCurrentEmitSizeScale *= mGlobalParams->mParticleScale;
        mCurrentEmitRateScale *= mGlobalParams->mParticleDensity;
    }

    if (mDesc->mFlags.test(kParticleFlagAttractor)) {
        mAttractorLocation = mDesc->mAttractorOrigin;
        mSourceTransform.TransformPoint(mAttractorLocation);
        mAttractorIntensity = 1.0f;
    }

    mOverallTime += deltaTime;

    mDirectionalForcesSum = mGlobalParams->mGravityDirection * mDesc->mGravityStrength;
    mDirectionalForcesSum += mGlobalParams->mWindDirection * mDesc->mWindStrength;
    mRigidTransform.BackTransformVector(mDirectionalForcesSum);
    mDirectionalForcesSum += mDesc->mDirectionalForcesSum;
    if (mDesc->mFlags.test(kParticleFlagRandomWalk))
        mRandomWalkState.AccumulateForce(mDirectionalForcesSum);

    if (!mSurfaceStateData.empty() && !mSurfaceStateDataValid) {
        for (cSurfaceRec* rec = mSurfaceRecs.begin(); rec != mSurfaceRecs.end(); ++rec)
            rec->mpSurface->InitState(rec->mpInfo, mSourceTransform, mRigidTransform,
                                      &mSurfaceStateData[rec->mStateOffset]);
        mSurfaceStateDataValid = true;
    }

    cParticle* it = mParticles.begin();
    mBoundingBox.Reset();

    // UpdateParticlePhysics (dev) inlined, with its branch hoisted out of the particle loop.
    if (sPhysicsUpdate[mDesc->mPhysicsType]) {
        while (it != mParticles.end()) {
            cParticle* p = it;
            if (sPhysicsUpdate[mDesc->mPhysicsType](p, deltaTime, mDesc, this)) {
                mBoundingBox.AddPoint(p->mPosition);
                it = it->mpNext;
            } else {
                it = mParticles.erase(it);
                RemoveParticle(p);
            }
        }
    } else if (mDesc->mDrag * deltaTime > 0.05f) {
        while (it != mParticles.end()) {
            cParticle* p = it;
            if (UpdatePhysicsTimeStep(p, deltaTime, mDesc, this)) {
                mBoundingBox.AddPoint(p->mPosition);
                it = it->mpNext;
            } else {
                it = mParticles.erase(it);
                RemoveParticle(p);
            }
        }
    } else {
        while (it != mParticles.end()) {
            cParticle* p = it;
            if (UpdatePhysicsSimple(p, deltaTime, mDesc, this)) {
                mBoundingBox.AddPoint(p->mPosition);
                it = it->mpNext;
            } else {
                it = mParticles.erase(it);
                RemoveParticle(p);
            }
        }
    }

    if (!mDelayedStopActive && !mSuppressEmission)
        GenerateNewParticles(deltaTime);

    float maxSize = mRigidTransform.mScale * mMaxParticleSize * mCurrentSizeScale * mCurrentEmitSizeScale;
    mBoundingBox.Transform(mRigidTransform);
    if (mTextureParticlesID >= 0)
        mWorld->GetRenderer()->UpdateTextureParticles(mTextureParticlesID, mBoundingBox, maxSize);
    else if (mModelParticlesID >= 0)
        mWorld->GetRenderer()->UpdateModelParticles(mModelParticlesID, mBoundingBox, maxSize);

    if (mParticleCount == 0 && mDelayedStopActive) {
        mStarted = false;
        if (mTextureParticlesID >= 0)
            mWorld->GetRenderer()->StopTextureParticles(mTextureParticlesID, 0);
        else if (mModelParticlesID >= 0)
            mWorld->GetRenderer()->StopModelParticles(mModelParticlesID, 0);
        if (mChainSystem)
            mChainSystem->Stop(false);
        return;
    }

    if (mDesc->mFlags.test(kParticleFlagRandomWalk)) {
        mRandomWalkState.mNextTime -= deltaTime;
        while (mRandomWalkState.mNextTime < 0.0f)
            mRandomWalkState.Update(mDesc->mRandomWalk);
    }

    mLastEmitLocation = location;
    if (mDesc->mFlags.test(kParticleFlagModelStats))
        stats->mModelParticles += mParticleCount;
    else
        stats->mTextureParticles += mParticleCount;
}

// Rate-curve emission (dev: EA::Swarm::cParticlesEffect::AddRateCurveParticles): advances the
// system time, then walks whole emission cycles up to the current time, spawning
// mRateCurve[0] * mCurrentEmitRateScale particles per cycle and re-scheduling the system time
// backwards by a random interval drawn from mEmitInterval.
// @ 0x00AB1400
void cParticlesEffect::AddRateCurveParticles(float deltaTime)
{
    mParticleSystemTime = deltaTime * mInverseRateCurveTime + mParticleSystemTime;
    if ((double)mCurrentCycle > mParticleSystemTime)
        return;

    // The 2008 build inlines ceilf here (cvtss2si + cvtsi2ss + ucomiss + cmovb).
    float rate = mDesc->mRateCurve[0] * mCurrentEmitRateScale;
    int whole = (int)rate;
    int count = ((float)whole < rate) ? whole + 1 : whole;

    while (mParticleSystemTime >= (double)mCurrentCycle) {
        if (mDesc->mFlags.test(27))
            StepFrame();

        float frameTime = (float)(mParticleSystemTime - (double)mCurrentCycle) * mDesc->mRateCurveTime;
        if (frameTime < mDesc->mParticleLifetime.y && count > 0) {
            int n = count;
            do {
                cParticle* p = g_ParticlePool.Allocate();
                if (!InitParticle(p)) {
                    DestroyParticle(p);
                } else {
                    PhysicsUpdateFn fn = sPhysicsUpdate[mDesc->mPhysicsType];
                    bool alive;
                    if (fn) {
                        alive = fn(p, frameTime, mDesc, this);
                    } else if (mDesc->mDrag * frameTime > K_DRAG_TIME_LIMIT) {
                        alive = UpdatePhysicsTimeStep(p, frameTime, mDesc, this);
                    } else {
                        // dev: EA::Swarm::UpdatePhysicsSimple, inlined.
                        p->mAge += frameTime;
                        if (p->mAge >= p->mLifeTime) {
                            alive = false;
                        } else {
                            Vector3 oldVelocity = p->mVelocity;
                            p->mVelocity += mDirectionalForcesSum * frameTime;
                            p->mVelocity *= HK_ONE - mDesc->mDrag * frameTime;
                            p->mPosition += (p->mVelocity + oldVelocity) * (frameTime * HK_HALF);
                            alive = true;
                        }
                    }
                    if (!alive) {
                        DestroyParticle(p);
                    } else {
                        p->mpPrev = mParticles.mpPrev;
                        p->mpNext = (cParticle*)&mParticles;
                        mParticles.mpPrev = p;
                        p->mpPrev->mpNext = p;
                        ++mParticleCount;
                        mBoundingBox.AddPoint(p->mPosition);
                    }
                }
            } while (--n != 0);
        }

        ++mCurrentCycle;
        if (mDesc->mMaxCycles != 0 && mCurrentCycle >= (int)mDesc->mMaxCycles) {
            if (mDesc->mFlags.test(kParticleFlagSingleCycle))
                return;
            static_cast<cIComponent*>(this)->Stop(false);
            return;
        }

        if (mDesc->mEmitInterval.x >= HK_ZERO) {
            // The 2008 build does this lerp in double (x87) precision, not in float.
            double lo = mDesc->mEmitInterval.x;
            double hi = mDesc->mEmitInterval.y;
            double interval = g_Random.RandomDouble() * (hi - lo) + lo;
            if (interval > hi)
                interval = hi;
            else if (interval < lo)
                interval = lo;
            mParticleSystemTime -= interval * mInverseRateCurveTime;
            if (mParticleSystemTime < (double)mCurrentCycle) {
                mRetriggerTime = mDesc->mRateCurveTime *
                                 (float)((double)mCurrentCycle - mParticleSystemTime);
                mParticleSystemTime = (double)mCurrentCycle;
                return;
            }
        }
    }
}

// Component factory: allocate a cParticlesEffect out of the Swarm bucket, construct it in
// place and hand back its cComponentBase subobject (the CDB-visible component).
// @ 0x00AB17E0
cComponentBase* __cdecl CreateParticlesEffect(uint32_t a, uint32_t b)
{
    cParticlesEffect* pEffect =
        (cParticlesEffect*)SwarmAllocDebug(K_PARTICLES_EFFECT_SIZE, K_SWARM_ALLOC_NAME, 0, 0, 0, 0);
    if (pEffect != 0) {
        pEffect = pEffect->ConstructInPlace(a, b);
        if (pEffect != 0)
            return static_cast<cComponentBase*>(pEffect);
    }
    return 0;
}

// dev: EA::Swarm::cParticlesEffect::GenerateNewParticles -- picks the emission routine from the
// LOD flags (Emit / AddRateCurveParticles / Update) after honouring the retrigger delay.
// @ 0x00AB1840
void cParticlesEffect::GenerateNewParticles(float deltaTime)
{
    if (mRetriggerTime > 0.0f) {
        mRetriggerTime -= deltaTime;
        if (mRetriggerTime > 0.0f)
            return;
        deltaTime = -mRetriggerTime;
    }

    if (mDesc->mPrerollTime > K_EMIT_TIME_EPS) {
        float preroll = mDesc->mPrerollTime - K_EMIT_TIME_EPS;
        if (preroll < deltaTime)
            deltaTime = preroll;
    }

    uint32_t flags = mDesc->mFlags.mWord[0];
    int lodEmit = (flags >> 1) & 1;
    if (lodEmit)
        Emit(deltaTime);
    else if (flags & 1)
        AddRateCurveParticles(deltaTime);
    else
        Update(deltaTime);
}

} }
