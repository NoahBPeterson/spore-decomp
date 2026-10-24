// Slice s00f7caf0: 0x00F7CAF0 (2261 bytes), EA::Swarm older-layout cParticlesEffect::ApplyEffect.
// Older copy (in the old cParticlesEffect.obj region next to the quad streamers s00f77940/s00f78a60) of
// ApplyEffect @ 0x00AB18D0 (slice s00ab1400). Differences read off the asm: no mRateCurve threshold in
// the LOD test, no random walk, 1.0 as the emit-move limit, an extra pair of "parameter" objects
// (+0x190/+0x194 vcall slot 0x10) whose results are cached and set a dirty byte, a 4-float colour scale,
// and the physics falls back to the inline simple integrator without the drag*dt test.
// `this` is the cComponentBase subobject (effect + 8). Layout names follow s00ab1400, offsets are the older ones.
// NAMING NOTE: class name cParticlesEffectOld is Claude-coined (like s00f79bb0).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);

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
    float SquaredLength() const { return y * y + z * z + x * x; }
    static Vector3 Scaled(float s, const Vector3& v) { return Vector3(s * v.x, s * v.y, s * v.z); }
};
struct Vector2
{
    float x, y;
    float Lerp(float t) const { return (y - x) * t + x; }
};

extern float kFXMaxFloat;                    // 0x015B0EDC

struct cBoundingBox
{
    Vector3 mMin;
    Vector3 mMax;
    void Reset()
    {
        float v = kFXMaxFloat;
        mMin = Vector3(v, v, v);
        mMax = Vector3(-v, -v, -v);
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
    void InverseTransformPoint(Vector3& v) const;                 // 0x007CDA70
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
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};

struct Color3 { float r, g, b; };
struct Color4 { float a; Color3 rgb; };

// 32-byte state block stored at cParticlesDescription::mStateBlock (+0x110).
struct cEffectStateBlock
{
    uint32_t mField00;                                            // +0x00
    uint32_t mField04;                                            // +0x04
    uint8_t mStatus;                                              // +0x08
    uint8_t mType;                                                // +0x09
    uint8_t pad_0a[2];
    uint32_t mField0c;                                            // +0x0C
    uint32_t mField10;                                            // +0x10
    uint32_t mField14;                                            // +0x14
    uint32_t mField18;                                            // +0x18
    uint32_t mField1c;                                            // +0x1C
};

// One 0x58-byte surface-parameter record in cParticlesDescription::mSurfaceParams.
struct cSurfaceParam
{
    uint32_t mFlags;                                              // +0x00
    uint32_t pad_04;
    uint32_t mIdA;                                                // +0x08
    uint32_t mIdB;                                                // +0x0C
    uint32_t pad_10[18];
};

struct cEffectRef
{
    uint32_t mField00;
    uint32_t mField04;
    uint32_t mField08;
    uint32_t mField0c;
    uint32_t mField10;
    uint32_t mField14;
};

// Surface-record vector at cParticlesEffectCore +0x1D4 (EffectVector::erase @ 0x00A8D020).
struct cEffectVector
{
    cEffectRef* mpBegin;
    cEffectRef* mpEnd;
    cEffectRef* mpCapacity;
    uint32_t mAllocator[2];
    cEffectRef* __thiscall erase(cEffectRef* first, cEffectRef* last);   // 0x00A8D020
};

// Byte-per-element bool vector at cParticlesEffectCore +0x1EC (eastl vector<bool>).
struct cBoolVector
{
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCapacity;
    uint32_t mAllocator[2];

    void erase_range(uint8_t* first, uint8_t* last)
    {
        memcpy(first, last, (unsigned int)(mpEnd - last));
        mpEnd -= last - first;
    }
    void clear() { erase_range(mpBegin, mpEnd); }
    void DoInsertValues(uint8_t* position, uint32_t count, const bool& value);   // 0x004C10E0
    void resize(uint32_t n)
    {
        uint32_t cur = (uint32_t)(mpEnd - mpBegin);
        if (n > cur)
            DoInsertValues(mpEnd, n - cur, false);
        else
            erase_range(mpBegin + n, mpEnd);
    }
};

struct cIParam { virtual void AddRef(); virtual void Release(); virtual void v08(); virtual void v0c();
                 virtual uint32_t GetValue();                         // +0x10
                 virtual void v14(); virtual void v18(); virtual bool IsReady();   // +0x1C
                 virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
                 virtual void v30(); };

// Particle-stream interface returned by cIEffectsWorld::GetRenderer and cParamFactory::v14.
struct cIParticleStream
{
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(uint8_t flags, uint8_t* out);                        // +0x10
    virtual void s14();
    virtual void s18(void* object, void* block, int* out);                // +0x18
    virtual void s1c();
    virtual void s20();
    virtual uint8_t s24(uint32_t a, uint32_t b, int c);                   // +0x24
    virtual void s28();
    virtual void s2c(void* base2, void* block, int* out);                 // +0x2C
};

// Parameter/resource manager passed to cParticlesEffectCore::F7d3d0.
struct cParamFactory
{
    virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0c();
    virtual void p10();
    virtual cIParticleStream* p14();                                      // +0x14
    virtual void p18(); virtual void p1c(); virtual void p20(); virtual void p24();
    virtual void p28(); virtual void p2c(); virtual void p30(); virtual void p34();
    virtual void p38(); virtual void p3c(); virtual void p40(); virtual void p44();
    virtual void p48(); virtual void p4c(); virtual void p50(); virtual void p54();
    virtual void p58(); virtual void p5c(); virtual void p60(); virtual void p64();
    virtual void p68(); virtual void p6c(); virtual void p70(); virtual void p74();
    virtual void p78(); virtual void p7c(); virtual void p80(); virtual void p84();
    virtual void p88();
    virtual cIParam* CreateParam(uint32_t idA, uint32_t idB);             // +0x8C
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
    uint32_t pad_1c[(0x4C - 0x1C) / 4];
    Vector3 mColorParams1;                                        // +0x4C
    Vector3 mColorParams2;                                        // +0x58
    uint32_t pad_64;
    vector<float> mRateCurve;                                     // +0x68
    float mRateCurveTime;                                         // +0x7C
    uint32_t pad_80[(0x88 - 0x80) / 4];
    vector<float> mSizeCurve;                                     // +0x88
    uint32_t pad_9c[(0x110 - 0x9C) / 4];
    cEffectStateBlock mStateBlock;                                // +0x110
    uint8_t mPhysicsType;                                         // +0x130
    uint8_t pad_131[0x135 - 0x131];
    uint8_t mPhysicsSubtype;                                      // +0x135
    uint8_t pad_136[0x13C - 0x136];
    Vector3 mDirectionalForcesSum;                                // +0x13C
    float mWindStrength;                                          // +0x148
    float mGravityStrength;                                       // +0x14C
    float mRadialForce;                                           // +0x150
    Vector3 mRadialForceLocation;                                 // +0x154
    float mDrag;                                                  // +0x160
    uint32_t pad_164[(0x1AC - 0x164) / 4];
    vector<cSurfaceParam> mSurfaceParams;                         // +0x1AC
    uint32_t pad_1c0[(0x1DC - 0x1C0) / 4];
    uint32_t mField1dc;                                           // +0x1DC
    uint32_t mField1e0;                                           // +0x1E0
    uint32_t pad_1e4;
    uint32_t mParamMask0A;                                        // +0x1E8
    uint32_t mParamMask0B;                                        // +0x1EC
    uint32_t mParamMask1A;                                        // +0x1F0
    uint32_t mParamMask1B;                                        // +0x1F4
    uint32_t mParamMask2A;                                        // +0x1F8
    uint32_t mParamMask2B;                                        // +0x1FC
    uint32_t pad_200[(0x234 - 0x200) / 4];
    Vector3 mAttractorOrigin;                                     // +0x234
};

struct cGlobalParams
{
    float mParticleDensity;                                       // +0x00
    float mParticleScale;                                         // +0x04
    int mParticleMultThreshold;                                   // +0x08
    uint32_t pad_0c[(0xBC - 0x0C) / 4];
    Vector3 mWindDirection;                                       // +0xBC
    uint32_t pad_c8[(0xD8 - 0xC8) / 4];
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
    virtual void v24(); virtual void v28();
    virtual cGlobalParams* GetGlobalParams();                                              // +0x2C
    virtual cParamFactory* GetParamFactory();                                              // +0x30
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
class cParticlesEffectCore;
typedef bool (*PhysicsUpdateFn)(cParticle* p, float dt, cParticlesDescription* desc, cParticlesEffect* effect);
extern PhysicsUpdateFn sPhysicsUpdate[];                          // 0x015B0EBC
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
    bool mParamsChanged;                                          // +0x17
    intrusive_list mParticles;                                    // +0x18
    int mParticleCount;                                           // +0x20
    cParticlesDescription* mDesc;                                 // +0x24
    uint32_t pad_28;
    cIEffectsWorld* mWorld;                                       // +0x2C
    cGlobalParams* mGlobalParams;                                 // +0x30
    uint32_t pad_34;
    double mOverallTime;                                          // +0x38
    bool mPreroll;                                                // +0x40
    double mParticleSystemTime;                                   // +0x48
    uint32_t pad_50[(0x64 - 0x50) / 4];
    Vector3 mDirectionalForcesSum;                                // +0x64
    uint32_t pad_70;
    Vector3 mAttractorLocation;                                   // +0x74
    float mAttractorIntensity;                                    // +0x80
    uint32_t pad_84;
    cBoundingBox mBoundingBox;                                    // +0x88
    float mMaxParticleSize;                                       // +0xA0
    uint32_t pad_a4[(0xB0 - 0xA4) / 4];
    cTransform mSourceTransform;                                  // +0xB0
    cTransform mRigidTransform;                                   // +0xE8
    Vector3 mLastEmitLocation;                                    // +0x120
    uint16_t mRenderCount;                                        // +0x12C
    uint16_t mLastRenderCount;                                    // +0x12E
    Vector2 mLODEmitScale;                                        // +0x130
    Vector2 mLODSizeScale;                                        // +0x138
    Vector2 mLODAlphaScale;                                       // +0x140
    uint32_t pad_148;
    float mEmitScale;                                             // +0x14C
    float mSizeScale;                                             // +0x150
    float mAlphaScale;                                            // +0x154
    Color4 mColorScale;                                           // +0x158
    uint32_t pad_168[3];
    float mCurrentEmitRateScale;                                  // +0x174
    float mCurrentEmitSizeScale;                                  // +0x178
    float mCurrentSizeScale;                                      // +0x17C
    float mCurrentAlphaScale;                                     // +0x180
    Color4 mCurrentColorScale;                                    // +0x184
    uint32_t pad_194;
    cIParam* mParamA;                                             // +0x198
    cIParam* mParamB;                                             // +0x19C
    uint32_t pad_1a0;
    uint32_t mCachedParamA;                                       // +0x1A4
    uint32_t mCachedParamB;                                       // +0x1A8
    uint32_t pad_1ac[(0x1D4 - 0x1AC) / 4];
    vector<cSurfaceRec> mSurfaceRecs;                             // +0x1D4
    bool mSurfaceStateDataValid;                                  // +0x1E8
    vector<uint8_t> mSurfaceStateData;                            // +0x1EC
    uint32_t pad_200[(0x218 - 0x200) / 4];
    cParticlesEffect* mChainSystem;                               // +0x218
    bool mSuppressEmission;                                       // +0x21C
    int mModelParticlesID;                                        // +0x220
    int mTextureParticlesID;                                      // +0x224

    void DestroyParticle(cParticle* p);                           // 0x00AAF670
    void RemoveParticle(cParticle* p)
    {
        --mParticleCount;
        DestroyParticle(p);
    }
    void GenerateNewParticles(float deltaTime);                   // 0x00AB1840
    virtual void ApplyEffect(float deltaTime, float lodFactor, cStats* stats);
};

// Complete-object view of the same effect (this = component - 8); the second base subobject sits at +4.
struct cParticleBase0 { virtual void b00(); };
struct cParticleBase1 { virtual void b10(); };

class cParticlesEffectCore : public cParticleBase0, public cParticleBase1
{
public:
    uint32_t pad_08[(0x24 - 0x08) / 4];
    cParticlesDescription* mDesc;                                 // +0x24
    uint32_t pad_28[(0x58 - 0x28) / 4];
    double mRateCurveTimeInv;                                     // +0x58
    uint32_t pad_60[(0x74 - 0x60) / 4];
    Vector3 mAttractorLocation;                                   // +0x74
    float mAttractorIntensity;                                    // +0x80
    uint32_t pad_84[(0xA0 - 0x84) / 4];
    float mMaxParticleSize;                                       // +0xA0
    uint32_t pad_a4[(0xE8 - 0xA4) / 4];
    cTransform mRigidTransform;                                   // +0xE8
    uint32_t pad_120[(0x168 - 0x120) / 4];
    uint32_t mPhysicsType;                                        // +0x168
    uint32_t mPhysicsField16c;                                    // +0x16C
    uint32_t mPhysicsField170;                                    // +0x170
    uint32_t pad_174[(0x194 - 0x174) / 4];
    cIParam* mParam0;                                             // +0x194
    cIParam* mParamA;                                             // +0x198
    cIParam* mParamB;                                             // +0x19C
    bool mParam0Ready;                                            // +0x1A0
    bool mParamAReady;                                            // +0x1A1
    bool mParamBReady;                                            // +0x1A2
    uint8_t pad_1a3;
    uint32_t mCachedParamA;                                       // +0x1A4
    uint32_t mCachedParamB;                                       // +0x1A8
    Vector3 mColorParams1;                                        // +0x1AC
    Vector3 mColorParams2;                                        // +0x1B8
    uint32_t pad_1c4[(0x1D4 - 0x1C4) / 4];
    cEffectVector mSurfaceRecs;                                   // +0x1D4
    bool mSurfaceStateDataValid;                                  // +0x1E8
    uint8_t pad_1e9[3];
    cBoolVector mSurfaceStateData;                                // +0x1EC
    bool mStateDirty;                                             // +0x200

    void F7d3d0(cParamFactory* mgr);                              // 0x00F7D3D0
};

// Component-subobject view of the effect (this = complete object + 8). All member offsets are the
// class offsets in cParticlesEffect minus 8, which is the convention both original functions use.
class cParticlesEffectView
{
public:
    virtual void v00();                                           // +0x00 component vftable
    uint32_t mRefCount[2];                                        // +0x04 (cComponentBase::mRefCountBase)
    uint32_t pad_0c[(0x1C - 0x0C) / 4];
    cParticlesDescription* mDesc;                                 // +0x1C
    uint32_t pad_20;
    cIEffectsWorld* mWorld;                                       // +0x24
    cGlobalParams* mGlobalParams;                                 // +0x28
    uint32_t pad_2c[(0x80 - 0x2C) / 4];
    cBoundingBox mBoundingBox;                                    // +0x80
    uint32_t pad_98[(0x1C0 - 0x98) / 4];
    uint32_t mSurfaceParamMaskA;                                  // +0x1C0
    uint32_t mSurfaceParamMaskB;                                  // +0x1C4
    uint32_t pad_1c8[(0x218 - 0x1C8) / 4];
    int mModelParticlesID;                                        // +0x218
    int mTextureParticlesID;                                      // +0x21C
    uint8_t mStreamState[5];                                      // +0x220
    uint8_t pad_225;
    uint8_t mStreamFlag;                                          // +0x226

    cParticlesEffectCore* core() { return (cParticlesEffectCore*)((char*)this - 8); }
    void F7d7a0(cIEffectsWorld* world, cParamFactory* mgr, void* unused);  // 0x00F7D7A0
    void F7d990(cParticlesDescription* desc);                     // 0x00F7D990
};

extern Vector3 gZeroVector;                                       // 0x016C9B28
void BuildSurfaceRecs(cParamFactory* mgr, vector<cSurfaceParam>* params, cEffectVector* recs,
                      int* size0, int* size1, bool* dirty);       // 0x00A7FC10

// @ 0x00F7D3D0
void __thiscall cParticlesEffectCore::F7d3d0(cParamFactory* mgr)
{
    const float minRate = 1e-6f;
    const float& rate = mDesc->mRateCurveTime > minRate ? mDesc->mRateCurveTime : minRate;
    mRateCurveTimeInv = 1.0 / rate;

    mPhysicsField16c = mDesc->mField1dc;
    mPhysicsField170 = mDesc->mField1e0;
    mPhysicsType = mDesc->mPhysicsSubtype;

    if (mDesc->mFlags.test(kParticleFlagAttractor)) {
        mAttractorLocation = mDesc->mAttractorOrigin;
        mRigidTransform.InverseTransformPoint(mAttractorLocation);
        mAttractorIntensity = 1.0f;
    } else {
        mAttractorLocation = gZeroVector;
        mAttractorIntensity = 0.0f;
    }

    mColorParams2 = mDesc->mColorParams2;
    mColorParams1 = mDesc->mColorParams1;

    mMaxParticleSize = mDesc->mSizeCurve[0];
    for (uint32_t i = 1; i < mDesc->mSizeCurve.size(); ++i) {
        if (mMaxParticleSize < mDesc->mSizeCurve[i])
            mMaxParticleSize = mDesc->mSizeCurve[i];
    }

    if ((mDesc->mParamMask0A & mDesc->mParamMask0B) != 0xffffffff) {
        cIParam* p = mgr->CreateParam(mDesc->mParamMask0A, mDesc->mParamMask0B);
        cIParam* old = mParam0;
        if (p != old) {
            if (p) p->AddRef();
            mParam0 = p;
            if (old) old->Release();
        }
    }
    if ((mDesc->mParamMask1A & mDesc->mParamMask1B) != 0xffffffff) {
        cIParam* p = mgr->CreateParam(mDesc->mParamMask1A, mDesc->mParamMask1B);
        cIParam* old = mParamA;
        if (p != old) {
            if (p) p->AddRef();
            mParamA = p;
            if (old) old->Release();
        }
    }
    if ((mDesc->mParamMask2A & mDesc->mParamMask2B) != 0xffffffff) {
        cIParam* p = mgr->CreateParam(mDesc->mParamMask2A, mDesc->mParamMask2B);
        cIParam* old = mParamB;
        if (p != old) {
            if (p) p->AddRef();
            mParamB = p;
            if (old) old->Release();
        }
    }

    if (mParam0) {
        mParam0->v08();
        mParam0Ready = mParam0->IsReady();
    }
    if (mParamA) {
        mParamA->v08();
        mParamAReady = mParamA->IsReady();
        mCachedParamA = mParamA->GetValue();
    }
    if (mParamB) {
        mParamB->v08();
        mParamBReady = mParamB->IsReady();
        mCachedParamB = mParamB->GetValue();
    }

    mSurfaceRecs.erase(mSurfaceRecs.mpBegin, mSurfaceRecs.mpEnd);

    vector<cSurfaceParam>& params = mDesc->mSurfaceParams;
    if (!params.empty()) {
        int size0 = 0;
        int size1 = 0;
        BuildSurfaceRecs(mgr, &params, &mSurfaceRecs, &size0, &size1, &mStateDirty);
        mSurfaceStateDataValid = false;
        mSurfaceStateData.resize((uint32_t)size0);
    } else {
        mSurfaceStateData.clear();
        mStateDirty = false;
    }
}

// @ 0x00F7D7A0
void __thiscall cParticlesEffectView::F7d7a0(cIEffectsWorld* world, cParamFactory* mgr, void* unused)
{
    mWorld = world;
    mGlobalParams = world->GetGlobalParams();
    mBoundingBox.Reset();
    core()->F7d3d0(mgr);

    cIParticleStream* p6 = mgr->p14();
    cIParticleStream* p7 = (cIParticleStream*)world->GetRenderer();
    if (!p7)
        return;

    cParticlesDescription* desc = mDesc;
    cEffectStateBlock block = desc->mStateBlock;
    uint32_t maskA = mSurfaceParamMaskA;
    uint32_t maskB = mSurfaceParamMaskB;
    if ((maskB & maskA) != 0xffffffff) {
        block.mField00 = maskA;
        block.mField04 = maskB;
    }

    if (desc->mFlags.test(kParticleFlagModelStats)) {
        if (block.mType == 0x0f)
            block.mStatus = p6->s24(block.mField18, block.mField1c, 9);
        else
            block.mStatus = 9;
        p7->s2c(static_cast<cParticleBase1*>(core()), &block, &mModelParticlesID);
        p7->s10(block.mStatus, &mStreamState[0]);
    } else {
        if (block.mType == 0x0f) {
            block.mStatus = 0x10;
            mStreamState[0] = 0;
            mStreamState[1] = 0x10;
            mStreamState[2] = 0x20;
            mStreamState[3] = 0x24;
            mStreamState[4] = 0x28;
        } else {
            block.mStatus = 0;
            p7->s10(0, &mStreamState[0]);
        }
        p7->s18(core(), &block, &mTextureParticlesID);
    }
    mStreamFlag = block.mStatus;
}

// @ 0x00F7D990
void __thiscall cParticlesEffectView::F7d990(cParticlesDescription* desc)
{
    mDesc = desc;
    cParamFactory* mgr = mWorld->GetParamFactory();
    core()->F7d3d0(mgr);
}

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

// @ 0x00F7CAF0
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

    if (mParamA) {
        uint32_t v = mParamA->GetValue();
        if (mCachedParamA != v) {
            mCachedParamA = v;
            mParamsChanged = true;
        }
    }
    if (mParamB) {
        uint32_t v = mParamB->GetValue();
        if (mCachedParamB != v) {
            mCachedParamB = v;
            mParamsChanged = true;
        }
    }

    if (mDesc->mFlags.test(kParticleFlagSingleCycle) && !mDelayedStopActive) {
        float timeLeft = (float)(1.0 - mParticleSystemTime) * mDesc->mRateCurveTime - 0.01f;
        if (timeLeft <= 0.0f)
            deltaTime = 0.0f;
        else if (deltaTime > timeLeft)
            deltaTime = timeLeft;
    }

    Vector3 location = mSourceTransform.mTranslation;
    if ((location - mLastEmitLocation).SquaredLength() > 1.0f)
        mLastEmitLocation = location;

    mCurrentEmitRateScale = mLODEmitScale.Lerp(lodFactor) * mEmitScale;
    float sizeScale = mLODSizeScale.Lerp(lodFactor) * mSizeScale;
    mCurrentAlphaScale = mLODAlphaScale.Lerp(lodFactor) * mAlphaScale;
    mCurrentColorScale.a = mColorScale.a;
    mCurrentColorScale.rgb = mColorScale.rgb;
    if (mDesc->mFlags.test(kParticleFlagScaleSizeOnly)) {
        mCurrentEmitSizeScale = 1.0f;
        mCurrentSizeScale = sizeScale;
    } else {
        mCurrentEmitSizeScale = sizeScale;
        mCurrentSizeScale = 1.0f;
    }
    if (mDesc->mFlags.test(kParticleFlagSizeScaleTransform))
        mCurrentEmitSizeScale *= mSourceTransform.mScale;

    uint32_t lodFlags = mDesc->mFlags.mWord[0];
    if (!((lodFlags & 1) || ((lodFlags >> 1) & 1))) {
        mCurrentEmitSizeScale *= mGlobalParams->mParticleScale;
        mCurrentEmitRateScale *= mGlobalParams->mParticleDensity;
    }

    if (mDesc->mFlags.test(kParticleFlagAttractor)) {
        mAttractorLocation = mDesc->mAttractorOrigin;
        mSourceTransform.TransformPoint(mAttractorLocation);
        mAttractorIntensity = 1.0f;
    }

    mOverallTime += deltaTime;

    mDirectionalForcesSum = Vector3::Scaled(mDesc->mGravityStrength, mGlobalParams->mGravityDirection);
    mDirectionalForcesSum += Vector3::Scaled(mDesc->mWindStrength, mGlobalParams->mWindDirection);
    mRigidTransform.BackTransformVector(mDirectionalForcesSum);
    mDirectionalForcesSum += mDesc->mDirectionalForcesSum;

    if (!mSurfaceStateData.empty() && !mSurfaceStateDataValid) {
        for (cSurfaceRec* rec = mSurfaceRecs.begin(); rec != mSurfaceRecs.end(); ++rec)
            rec->mpSurface->InitState(rec->mpInfo, mSourceTransform, mRigidTransform,
                                      &mSurfaceStateData[rec->mStateOffset]);
        mSurfaceStateDataValid = true;
    }

    cParticle* it = mParticles.begin();
    mBoundingBox.Reset();

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

    mLastEmitLocation = location;
    if (mDesc->mFlags.test(kParticleFlagModelStats))
        stats->mModelParticles += mParticleCount;
    else
        stats->mTextureParticles += mParticleCount;
    mParamsChanged = false;
}

} }
