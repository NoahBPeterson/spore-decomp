// Slice s00f61b40: Swarm particle-effect per-frame update (vtable 0x0148f09c slot 6).
// The method belongs to the effect's secondary base at +8, so `this` is the base subobject
// and the owning effect is this-8 (passed to the particle callbacks and the free routine).
// /O2 /arch:SSE /fp:fast module.
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3 operator-(const Vector3& o) const { return Vector3(x - o.x, y - o.y, z - o.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    Vector3& operator+=(const Vector3& o) { x += o.x; y += o.y; z += o.z; return *this; }
    float SquaredLength() const { return z * z + y * y + x * x; }
};

struct BoundingBox {
    Vector3 lower;
    Vector3 upper;
    void Transform(const struct Transform& t);             // 0x006e95a0
    void AddPoint(const Vector3& p)
    {
        if (lower.x > p.x) lower.x = p.x;
        if (p.x > upper.x) upper.x = p.x;
        if (lower.y > p.y) lower.y = p.y;
        if (p.y > upper.y) upper.y = p.y;
        if (lower.z > p.z) lower.z = p.z;
        if (p.z > upper.z) upper.z = p.z;
    }
};

struct Transform {                                         // size 0x38
    uint16_t mFlags;
    uint16_t mRefCount;
    Vector3 mOffset;
    float mfScale;
    float mRotation[9];
    void TransformVector(Vector3& v) const;                // 0x007cdee0
    void Rotate(Vector3& v) const;                         // 0x00a78e90
    void InverseTransformPoint(Vector3& v) const;          // 0x007cda70
};

extern float g_fMinMoveSquared;                            // 0x015b0c58
extern float g_fMaxFloat;                                  // 0x015b0c34

struct cParticle {
    cParticle* mpNext;
    cParticle* mpPrev;
    float mfAge;                                           // +0x08
    float mfLifetime;                                      // +0x0c
    Vector3 mPosition;                                     // +0x10
    Vector3 mVelocity;                                     // +0x1c
};

struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(float ax, float ay) : x(ax), y(ay) {}
    Vector2(const Vector2& o) : x(o.x), y(o.y) {}
};

// eastl::vector<T, sp_vector_allocator>: begin/end/capacity plus a two-word allocator.
struct FloatVector {
    float* mpBegin;                                        // +0x00
    float* mpEnd;                                          // +0x04
    float* mpCapacity;                                     // +0x08
    uint32_t mAllocator[2];                                // +0x0c
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
};

// Description entry consumed by 0xa7fc10 to build one surface record (0x58 bytes).
struct cEffectEntry {
    uint32_t pad00[2];
    int mnEffectIdA;                                       // +0x08
    int mnEffectIdB;                                       // +0x0c
    uint32_t pad10[18];                                    // +0x10
};

struct EffectListVector {
    cEffectEntry* mpBegin;                                 // +0x00
    cEffectEntry* mpEnd;                                   // +0x04
    cEffectEntry* mpCapacity;                              // +0x08
    uint32_t mAllocator[2];                                // +0x0c
};

// Low/high halves of a 64-bit map resource id pair (all-ones means "unbound").
struct MapID {
    uint32_t mIdA;
    uint32_t mIdB;
};

struct cSurfaceRec {
    void* mpSurface;                                       // +0x00
    void* mpSurfaceInfo;                                   // +0x04
    int mnStateBytes;                                      // +0x08
    int mnStateDataOffset;                                 // +0x0c
    int mnParticleBytes;                                   // +0x10
    int mnParticleDataOffset;                              // +0x14
};

struct SurfaceRecVector {
    cSurfaceRec* mpBegin;                                  // +0x00
    cSurfaceRec* mpEnd;                                    // +0x04
    cSurfaceRec* mpCapacity;                               // +0x08
    uint32_t mAllocator[2];                                // +0x0c
    cSurfaceRec* erase(cSurfaceRec* first, cSurfaceRec* last);   // 0x00a8d020
};

extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);

// eastl::vector<unsigned char, sp_vector_allocator> (effect's surface state buffer).
struct ByteVector {
    unsigned char* mpBegin;                                // +0x00
    unsigned char* mpEnd;                                  // +0x04
    unsigned char* mpCapacity;                             // +0x08
    uint32_t mAllocator[2];                                // +0x0c
    void DoInsertValues(unsigned char* pos, unsigned int n, const bool* value);  // 0x004c10e0
    void resize(unsigned int count)
    {
        unsigned int size = (unsigned int)(mpEnd - mpBegin);
        if (count > size) {
            bool value = false;
            DoInsertValues(mpEnd, count - size, &value);
        } else {
            unsigned char* first = mpBegin + count;
            unsigned char* last = mpEnd;
            memcpy(first, last, (unsigned int)(mpEnd - last));
            mpEnd -= (last - first);
        }
    }
};

struct cParticleDescription {
    uint32_t pad0[2];
    uint32_t mFlags;                                       // +0x08
    uint32_t pad1[2];
    float mfPreroll;                                       // +0x14
    uint32_t pad2a[12];                                    // +0x18
    BoundingBox mEmitVolume;                               // +0x48
    float mfEmitTorusWidth;                                // +0x60
    FloatVector mRateCurve;                                // +0x64
    float mRateCurveTime;                                  // +0x78
    uint16_t mRateCurveCycles;                             // +0x7c
    uint16_t pad7e;
    float mRateSpeedScale;                                 // +0x80
    FloatVector mSizeCurve;                                // +0x84
    uint32_t pad4b[36];                                    // +0x98
    uint8_t mUpdateMode;                                   // +0x128
    uint8_t pad5a[4];                                      // +0x129
    uint8_t mFrameStart;                                   // +0x12d
    uint8_t pad5b[6];                                      // +0x12e
    Vector3 mWind;                                         // +0x134
    float mfWindStrength;                                  // +0x140
    float mfGravityStrength;                               // +0x144
    uint32_t pad6[4];
    float mfDrag;                                          // +0x158
    uint32_t pad7a[19];                                    // +0x15c
    EffectListVector mEffectList;                          // +0x1a8
    uint32_t pad7b[2];                                     // +0x1bc
    float mfAlphaScale;                                    // +0x1c4
    uint32_t pad8a[4];                                     // +0x1c8
    Vector2 mAltitudeRange;                                // +0x1d8
    MapID mForceMapID;                                     // +0x1e0
    MapID mEmitRateMapID;                                  // +0x1e8
    MapID mEmitColorMapID;                                 // +0x1f0
    struct Curve { uint32_t pad[13]; } mEmitCurve;         // +0x1f8
    Vector3 mDirection;                                    // +0x22c

    bool Flag(int bit) const { return (mFlags >> bit) & 1; }
};

struct cParticleSource {
    float mfSizeScale;                                     // +0x00
    float mfColorScale;                                    // +0x04
    int mnLevel;                                           // +0x08
    uint32_t pad[44];
    Vector3 mWindDir;                                      // +0xbc
    uint32_t pad2[4];
    Vector3 mGravityDir;                                   // +0xd8
};

struct cParticleStats {
    uint32_t pad[4];
    int mnParticles;                                       // +0x10
    int mnSpawned;                                         // +0x14
    int mnScreenParticles;                                 // +0x18
    int mnScreenSpawned;                                   // +0x1c
};

struct cEmitTimer {
    float mfTime;
    uint32_t pad[6];
    void Advance(Vector3& accel);                          // 0x00a79300
    void Step(cParticleDescription::Curve& curve);         // 0x00a790a0
};

struct IParticleRenderer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void UpdateBounds(int id, const BoundingBox& b, float alpha);   // 0x20
    virtual void Hide(int id, int flags);                                   // 0x24
    virtual void v28(); virtual void v2c(); virtual void v30();
    virtual void UpdateBounds2(int id, const BoundingBox& b, float alpha);  // 0x34
    virtual void Hide2(int id, int flags);                                  // 0x38
};

struct cEffectsWorld {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual IParticleRenderer* GetRenderer();              // 0x20
};

struct IAttachment {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void Attach(int id, const Transform* a, const Transform* b, char* data);  // 0x20
};

struct cAttachment {                                       // size 0x18
    IAttachment* mpTarget;
    int mnId;
    uint32_t pad;
    int mnDataOffset;
    uint32_t pad2[2];
};

struct IEffectCallback {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void OnFinished(int flags);                    // 0x0c
};
struct cEffectOwner {
    uint32_t pad[2];
    IEffectCallback mCallback;                             // +0x08
};

// Map resource interface: slots 0/1 are AddRef/Release, 8 Prepare, 0x1c IsEnabled.
struct cIRefObj {
    virtual void AddRef();                                 // +0x00
    virtual void Release();                                // +0x04
};
struct cIMap : cIRefObj {
    virtual void Prepare();                                // +0x08
    virtual void v0c();
    virtual int GetValue();                                // +0x10
    virtual void v14();
    virtual void v18();
    virtual bool IsEnabled();                              // +0x1c
};

// Effects manager; CreateMap sits at vtable offset 0x8c.
struct cIEffectsManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88();
    virtual cIMap* CreateMap(uint32_t idA, uint32_t idB);  // +0x8c
};

// Builds one surface record per description entry, accumulating count/total.
void BuildSurfaceRecs(cIEffectsManager* mgr, EffectListVector* list, SurfaceRecVector* recs,
                      int* count, int* total, bool* haveSurfacePin);  // 0x00a7fc10

extern const float kRealEpsilon;                           // 0x013f11c8 (1e-6)
extern const float kRealOne;                               // 0x01485720
extern const Vector3 kVector3Zero;                         // 0x016c9434

struct cAttachment;

class cParticleEffect;
typedef bool (*ParticleUpdateFn)(cParticle* p, float dt, cParticleDescription* desc,
                                 cParticleEffect* effect);
extern ParticleUpdateFn g_particleUpdateFns[];             // 0x015b0c00
bool UpdateParticleFull(cParticle* p, float dt, cParticleDescription* desc,
                        cParticleEffect* effect);          // 0x00f5e910

struct cParticleEffectBase {
    virtual void v00();
    uint32_t m4;
};

struct IParticleUpdater {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void Update(float dt, float t, cParticleStats* stats) = 0;   // 0x18
};

// Offsets in comments are relative to the IParticleUpdater subobject (this+8 of the effect).
class cParticleEffect : public cParticleEffectBase, public IParticleUpdater {
public:
    virtual void Update(float dt, float t, cParticleStats* stats);
    void Init(cIEffectsManager* mgr);                      // 0x00f62580
    void FreeParticle(cParticle* p);                       // 0x00f5f770
    void Spawn(float dt);                                  // 0x00f61ab0

    uint32_t pad04[2];
    bool mbVisible;                                        // +0x0c
    bool mbStopping;                                       // +0x0d
    cParticle* mpHead;                                     // +0x10 (list sentinel next)
    cParticle* mpTail;                                     // +0x14
    int mnParticles;                                       // +0x18
    cParticleDescription* mpDesc;                          // +0x1c
    cParticleDescription* mpBaseDesc;                      // +0x20
    uint32_t pad24;
    cEffectsWorld* mpWorld;                                // +0x28
    cParticleSource* mpSource;                             // +0x2c
    float mfAge;                                           // +0x30
    uint32_t pad34;
    double mdTime;                                         // +0x38
    bool mbFirstUpdate;                                    // +0x40
    double mdProgress;                                     // +0x48
    int mCurrentCycle;                                     // +0x50
    double mdInvRateCurveTime;                             // +0x58
    float mfParticlesToGenerate;                           // +0x60
    Vector3 mAccel;                                        // +0x64
    cEmitTimer mEmitTimer;                                 // +0x70
    Vector3 mDirection;                                    // +0x8c
    float mfDirectionW;                                    // +0x98
    uint32_t pad9c;
    BoundingBox mBounds;                                   // +0xa0
    float mfMaxParticleSize;                               // +0xb8
    uint32_t padbc[3];
    Transform mTransform;                                  // +0xc8
    Transform mWorldTransform;                             // +0x100
    Vector3 mLastPosition;                                 // +0x138
    uint16_t mnSpawned;                                    // +0x144
    uint16_t mnCounted;                                    // +0x146
    float mSizeRange[2];                                   // +0x148
    float mAlphaRange[2];                                  // +0x150
    float mAspectRange[2];                                 // +0x158
    float mfSizeScale;                                     // +0x160 unused here
    float mfSize;                                          // +0x164
    float mfAlphaMul;                                      // +0x168
    float mfAspect;                                        // +0x16c
    float mfAlphaBase;                                     // +0x170
    uint32_t mColor[3];                                    // +0x174
    int mFrameStart;                                       // +0x180
    Vector2 mParamAltitudeRange;                           // +0x184
    float mfOutSize;                                       // +0x18c
    float mfOutAlpha;                                      // +0x190
    float mfOutFade;                                       // +0x194
    float mfOutAspect;                                     // +0x198
    float mfOutAlphaBase;                                  // +0x19c
    uint32_t mOutColor[3];                                 // +0x1a0
    uint32_t pad1ac;                                       // +0x1ac
    cIMap* mpForceMap;                                     // +0x1b0
    cIMap* mpEmitRateMap;                                  // +0x1b4
    cIMap* mpEmitColorMap;                                 // +0x1b8
    bool mbForceMapInWorldSpace;                           // +0x1bc
    bool mbEmitMapInWorldSpace;                            // +0x1bd
    bool mbEmitColorMapInWorldSpace;                       // +0x1be
    uint8_t pad1bf;
    BoundingBox mEmissionVolume;                           // +0x1c0
    uint64_t mOverrideID;                                  // +0x1d8
    uint32_t mpTargetPoint;                                // +0x1e0
    union {
        struct { cAttachment* mpAttachBegin; cAttachment* mpAttachEnd; };
        SurfaceRecVector mSurfaceRecs;                     // +0x1e4
    };
    bool mbAttached;                                       // +0x1f8
    union {
        struct { char* mpDataBegin; char* mpDataEnd; };
        ByteVector mSurfaceStateData;                      // +0x1fc
    };
    bool mbHaveSurfacePin;                                 // +0x210
    uint8_t pad211[3];
    uint32_t pad21c[5];
    cEffectOwner* mpOwner;                                 // +0x228
    bool mbNoSpawn;                                        // +0x22c
    int mnRenderId2;                                       // +0x230
    int mnRenderId;                                        // +0x234

    cParticle* ListEnd() { return (cParticle*)&mpHead; }
    cParticle* RemoveParticle(cParticle* p)
    {
        cParticle* prev = p->mpPrev;
        cParticle* next = p->mpNext;
        prev->mpNext = next;
        next->mpPrev = prev;
        p->mpNext = 0;
        p->mpPrev = 0;
        --mnParticles;
        return next;
    }
};

// @ 0x00f61b40
void cParticleEffect::Update(float dt, float t, cParticleStats* stats)
{
    if (mbFirstUpdate) {
        if (mpDesc->Flag(28)) {
            mdProgress = 1.0;
            mbFirstUpdate = false;
        } else {
            dt = mpDesc->mfPreroll + dt;
            mbFirstUpdate = false;
        }
    } else if (mnSpawned > mnCounted) {
        int n = (mnSpawned - mnCounted) * mnParticles;
        if (mpDesc->Flag(21))
            stats->mnScreenSpawned += n;
        else
            stats->mnSpawned += n;
        mnCounted = mnSpawned;
    }

    if (dt < 0.0f)
        return;

    cParticleDescription* desc = mpDesc;
    if (desc->Flag(28) && !mbStopping) {
        float limit = (float)(1.0 - mdProgress) * desc->mRateCurveTime - 0.01f;
        if (limit <= 0.0f)
            dt = 0.0f;
        else if (dt > limit)
            dt = limit;
    }

    Vector3 position(mTransform.mOffset);
    if ((position - mLastPosition).SquaredLength() > g_fMinMoveSquared)
        mLastPosition = position;

    mfOutSize = ((mSizeRange[1] - mSizeRange[0]) * t + mSizeRange[0]) * mfSize;
    float alpha = ((mAlphaRange[1] - mAlphaRange[0]) * t + mAlphaRange[0]) * mfAlphaMul;
    mOutColor[0] = mColor[0];
    mOutColor[1] = mColor[1];
    mfOutAspect = ((mAspectRange[1] - mAspectRange[0]) * t + mAspectRange[0]) * mfAspect;
    mOutColor[2] = mColor[2];
    mfOutAlphaBase = desc->mfAlphaScale * mfAlphaBase;
    if (desc->Flag(25)) {
        mfOutAlpha = 1.0f;
        mfOutFade = alpha;
    } else {
        mfOutAlpha = alpha;
        mfOutFade = 1.0f;
    }
    if (desc->Flag(11))
        mfOutAlpha = mTransform.mfScale * mfOutAlpha;

    cParticleSource* source;
    uint32_t flags = desc->mFlags;
    if ((!(flags & 1) && !((flags >> 1) & 1))
        || (source = mpSource, *desc->mRateCurve.mpBegin > (float)source->mnLevel))
    {
        source = mpSource;
        mfOutAlpha = source->mfColorScale * mfOutAlpha;
        mfOutSize = mfOutSize * source->mfSizeScale;
    }

    if (((uint8_t*)&desc->mFlags)[3] & 1) {
        mDirection = desc->mDirection;
        mTransform.TransformVector(mDirection);
        mfDirectionW = 1.0f;
    }

    source = mpSource;
    mdTime = dt + mdTime;
    mAccel = source->mGravityDir * mpDesc->mfGravityStrength;
    mAccel += source->mWindDir * mpDesc->mfWindStrength;
    mWorldTransform.Rotate(mAccel);
    mAccel += mpDesc->mWind;
    if (mpDesc->Flag(19))
        mEmitTimer.Advance(mAccel);

    if (mpDataBegin != mpDataEnd && !mbAttached) {
        for (cAttachment* it = mpAttachBegin; it != mpAttachEnd; ++it)
            it->mpTarget->Attach(it->mnId, &mTransform, &mWorldTransform, mpDataBegin + it->mnDataOffset);
        mbAttached = true;
    }

    if (mpDesc != mpBaseDesc)
        mfAge += dt;

    float big = g_fMaxFloat;
    mBounds.lower = Vector3(big, big, big);
    mBounds.upper = Vector3(-big, -big, -big);

    cParticle* p = mpHead;
    if (g_particleUpdateFns[mpDesc->mUpdateMode]) {
        cParticleEffect* effect = this;
        while (p != ListEnd()) {
            cParticle* cur = p;
            if (g_particleUpdateFns[mpDesc->mUpdateMode](p, dt, mpDesc, effect)) {
                mBounds.AddPoint(p->mPosition);
                p = p->mpNext;
            } else {
                p = effect->RemoveParticle(p);
                effect->FreeParticle(cur);
            }
        }
    } else if (mpDesc->mfDrag * dt > 0.05f) {
        cParticleEffect* effect = this;
        while (p != ListEnd()) {
            cParticle* cur = p;
            if (UpdateParticleFull(p, dt, mpDesc, effect)) {
                mBounds.AddPoint(p->mPosition);
                p = p->mpNext;
            } else {
                p = effect->RemoveParticle(p);
                effect->FreeParticle(cur);
            }
        }
    } else {
        while (p != ListEnd()) {
            cParticleDescription* d = mpDesc;
            p->mfAge += dt;
            cParticle* cur = p;
            if (p->mfAge >= p->mfLifetime) {
                p = RemoveParticle(p);
                FreeParticle(cur);
            } else {
                Vector3 oldVel(p->mVelocity);
                p->mVelocity += mAccel * dt;
                float damp = 1.0f - d->mfDrag * dt;
                p->mVelocity.x = damp * p->mVelocity.x;
                p->mVelocity.y = damp * p->mVelocity.y;
                p->mVelocity.z = damp * p->mVelocity.z;
                float half = dt * 0.5f;
                p->mPosition.x = (oldVel.x + p->mVelocity.x) * half + p->mPosition.x;
                p->mPosition.y = (oldVel.y + p->mVelocity.y) * half + p->mPosition.y;
                p->mPosition.z = (oldVel.z + p->mVelocity.z) * half + p->mPosition.z;
                mBounds.AddPoint(p->mPosition);
                p = p->mpNext;
            }
        }
    }

    if (!mbStopping && !mbNoSpawn)
        Spawn(dt);

    mBounds.Transform(mWorldTransform);
    float renderAlpha = mWorldTransform.mfScale * mfMaxParticleSize * mfOutAlpha * mfOutFade;
    if (mnRenderId >= 0)
        mpWorld->GetRenderer()->UpdateBounds(mnRenderId, mBounds, renderAlpha);
    else if (mnRenderId2 >= 0)
        mpWorld->GetRenderer()->UpdateBounds2(mnRenderId2, mBounds, renderAlpha);

    if (mnParticles == 0 && mbStopping) {
        mbVisible = false;
        if (mnRenderId >= 0)
            mpWorld->GetRenderer()->Hide(mnRenderId, 0);
        else if (mnRenderId2 >= 0)
            mpWorld->GetRenderer()->Hide2(mnRenderId2, 0);
        if (mpOwner)
            mpOwner->mCallback.OnFinished(0);
        return;
    }

    if (mpDesc->Flag(19)) {
        mEmitTimer.mfTime = mEmitTimer.mfTime - dt;
        while (mEmitTimer.mfTime < 0.0f)
            mEmitTimer.Step(mpDesc->mEmitCurve);
    }
    mLastPosition = position;
    if (mpDesc->Flag(21))
        stats->mnScreenParticles += mnParticles;
    else
        stats->mnParticles += mnParticles;
}

// Assigns a map reference-counted interface pointer, AddRef'ing the new object before the old one
// is released. A resource id pair of all-ones means "not bound", so the slot is left alone.
static void AssignMapRef(cIMap*& slot, cIEffectsManager* mgr, uint32_t idA, uint32_t idB)
{
    if ((idA & idB) == 0xffffffff)
        return;
    cIMap* p = mgr->CreateMap(idA, idB);
    cIMap* old = slot;
    if (p == old)
        return;
    if (p)
        p->AddRef();
    slot = p;
    if (old)
        old->Release();
}

// @ 0x00f62580
void cParticleEffect::Init(cIEffectsManager* mgr)
{
    float local = 1e-6f;
    const float* pf = &mpDesc->mRateCurveTime;
    if (!(mpDesc->mRateCurveTime > local))
        pf = &local;
    mdInvRateCurveTime = 1.0 / *pf;

    mParamAltitudeRange = mpDesc->mAltitudeRange;
    mFrameStart = mpDesc->mFrameStart;

    if (mpDesc->Flag(24)) {
        mDirection = mpDesc->mDirection;
        mWorldTransform.InverseTransformPoint(mDirection);
        mfDirectionW = 1.0f;
    } else {
        mDirection = kVector3Zero;
        mfDirectionW = 0.0f;
    }

    const BoundingBox& srcVolume = mpDesc->mEmitVolume;
    mEmissionVolume.upper = srcVolume.upper;
    mEmissionVolume.lower = srcVolume.lower;

    mfMaxParticleSize = mpDesc->mSizeCurve.mpBegin[0];
    for (uint32_t i = 1; i < mpDesc->mSizeCurve.size(); ++i) {
        float v = mpDesc->mSizeCurve.mpBegin[i];
        if (v > mfMaxParticleSize)
            mfMaxParticleSize = v;
    }

    AssignMapRef(mpForceMap, mgr, mpDesc->mForceMapID.mIdA, mpDesc->mForceMapID.mIdB);
    AssignMapRef(mpEmitRateMap, mgr, mpDesc->mEmitRateMapID.mIdA, mpDesc->mEmitRateMapID.mIdB);
    AssignMapRef(mpEmitColorMap, mgr, mpDesc->mEmitColorMapID.mIdA, mpDesc->mEmitColorMapID.mIdB);

    if (mpForceMap) {
        mpForceMap->Prepare();
        mbForceMapInWorldSpace = mpForceMap->IsEnabled();
    }
    if (mpEmitRateMap) {
        mpEmitRateMap->Prepare();
        mbEmitMapInWorldSpace = mpEmitRateMap->IsEnabled();
    }
    if (mpEmitColorMap) {
        mpEmitColorMap->Prepare();
        mbEmitColorMapInWorldSpace = mpEmitColorMap->IsEnabled();
    }

    mSurfaceRecs.erase(mSurfaceRecs.mpBegin, mSurfaceRecs.mpEnd);

    if (mpDesc->mEffectList.mpBegin != mpDesc->mEffectList.mpEnd) {
        int count = 0;
        int total = 0;
        BuildSurfaceRecs(mgr, &mpDesc->mEffectList, &mSurfaceRecs, &count, &total, &mbHaveSurfacePin);
        mbAttached = false;
        mSurfaceStateData.resize(count);
    } else {
        mSurfaceStateData.resize(0);
        mbHaveSurfacePin = false;
    }
}
