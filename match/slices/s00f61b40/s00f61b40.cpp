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

struct cParticleDescription {
    uint32_t pad0[2];
    uint32_t mFlags;                                       // +0x08
    uint32_t pad1[2];
    float mfPreroll;                                       // +0x14
    uint32_t pad2[19];
    float* mpRateCurve;                                    // +0x64
    uint32_t pad3[4];
    float mfLifeLimit;                                     // +0x78
    uint32_t pad4[43];
    uint8_t mUpdateMode;                                   // +0x128
    uint8_t pad5[11];
    Vector3 mWind;                                         // +0x134
    float mfWindStrength;                                  // +0x140
    float mfGravityStrength;                               // +0x144
    uint32_t pad6[4];
    float mfDrag;                                          // +0x158
    uint32_t pad7[26];
    float mfAlphaScale;                                    // +0x1c4
    uint32_t pad8[12];
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
    uint32_t pad50[5];
    Vector3 mAccel;                                        // +0x64
    cEmitTimer mEmitTimer;                                 // +0x70
    Vector3 mDirection;                                    // +0x8c
    float mfDirectionW;                                    // +0x98
    uint32_t pad9c;
    BoundingBox mBounds;                                   // +0xa0
    float mfAlpha;                                         // +0xb8
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
    uint32_t pad180[3];
    float mfOutSize;                                       // +0x18c
    float mfOutAlpha;                                      // +0x190
    float mfOutFade;                                       // +0x194
    float mfOutAspect;                                     // +0x198
    float mfOutAlphaBase;                                  // +0x19c
    uint32_t mOutColor[3];                                 // +0x1a0
    uint32_t pad1ac[14];
    cAttachment* mpAttachBegin;                            // +0x1e4
    cAttachment* mpAttachEnd;                              // +0x1e8
    uint32_t pad1ec[3];
    bool mbAttached;                                       // +0x1f8
    char* mpDataBegin;                                     // +0x1fc
    char* mpDataEnd;                                       // +0x200
    uint32_t pad204[9];
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
        float limit = (float)(1.0 - mdProgress) * desc->mfLifeLimit - 0.01f;
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
        || (source = mpSource, *desc->mpRateCurve > (float)source->mnLevel))
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
    float renderAlpha = mWorldTransform.mfScale * mfAlpha * mfOutAlpha * mfOutFade;
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
