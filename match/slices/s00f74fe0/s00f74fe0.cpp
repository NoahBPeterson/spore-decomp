// Slice s00f74fe0: 0x00F74FE0 (2480 bytes) and 0x00F75990 (627 bytes), EA::Swarm older-layout
// particle effect (the cParticlesEffect.obj copy next to s00f79bb0 / s00f7caf0, the same class
// family as the quad streamers s00f77940/s00f78a60).
//
// 0x00F74FE0 is a cdecl helper that ages one particle, re-randomises its emitted position inside
// the effect's emission volume / map, its colour and alpha: UpdateParticle(particle, dt, desc, effect).
// 0x00F75990 is the matching transform setter (this, sourceTransform, rigidTransform): it assigns
// the two transforms, recomputes the effect position through the rigid transform and shifts the
// bounding box / colour-mapped position by the same delta.
//
// NAMING NOTE: neither address has a PDB symbol; the helper names come from the sibling slices
// (cParticlesEffectOld / InitParticle / PlaceParticleOnSurface), the class name of 0x00F75990 is
// Claude-coined (cDistributeEffectOld) because its transforms sit 8 bytes before the particle
// effect's. Offsets are the retail ones.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

namespace EA { namespace Random {
class RandomLinearCongruential { public: double RandomDoubleUniform(); };   // 0x009360d0
} }
extern EA::Random::RandomLinearCongruential sRandom_Swarm;                  // 0x016778dc

extern float kFXMaxFloat;               // 0x015B0EDC (FLT_MAX, bounding-box sentinel)
extern float kFXRandThreshold;          // 0x015B0EE8 (0.5 random split)
extern float kFXHeightCutoff;           // 0x01471064 (height test for the emit map)
extern float kFXSampleEpsilon;          // 0x015B0EEC (radius epsilon of the sample jitter)
extern uint32_t kSurfacePinFlags;       // 0x015B0EE4 (surface record flag mask)

// Uniform random in [lo, hi], clamped (inlined helper in the original).
static __forceinline double RandRange(double lo, double hi)
{
    double r = sRandom_Swarm.RandomDoubleUniform();
    double v = r * (hi - lo) + lo;
    if (v >= hi) return hi;
    if (v < lo) return lo;
    return v;
}

// 0x007D45D0: float,float -> double (the same clamped range, out of line). NOTE: it is *not* the
// ?RandomRange@@YAMMM@Z at 0x00572A10 (RandomFloatRange), which also writes the RNG state
// 0x01601760 -- keep the FUN_<va> C name so the call target resolves to the original address.
extern "C" double FUN_007d45d0(float lo, float hi);

struct Vector2 { float x, y; Vector2() {} Vector2(float _x, float _y) : x(_x), y(_y) {} };
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
};
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
struct Vector4 { float x, y, z, w; };

struct cBoundingBox { Vector3 mMin; Vector3 mMax; };

struct cTransform {                     // 0x38 bytes (== cSPTransform)
    enum { kHasScale = 1, kHasRotation = 2, kHasTranslation = 4 };

    uint16_t mFlags;                    // +0x00
    uint16_t mModCount;                 // +0x02
    Vector3  mTranslation;              // +0x04
    float    mScale;                    // +0x10
    float    mRotation[3][3];           // +0x14 (row vectors)

    // out of line in the original
    void Assign(const void* pSrc);      // 0x00537DC0 (cSPTransformOps::Assign)
    void Transform(Vector3& v) const;   // 0x007CDEE0
    void InverseTransformPoint(Vector3& v) const;   // 0x007CDA70

    // row 0 is written as two statements so /fp:fast keeps the original ((r10*y + r20*z) + x*r00)
    // summation order (the binary does); rows 1 and 2 are plain left-to-right sums.
    Vector3 Rotate(const Vector3& v) const
    {
        float rx = mRotation[1][0] * v.y + mRotation[2][0] * v.z;
        rx += v.x * mRotation[0][0];
        return Vector3(rx,
                       mRotation[0][1] * v.x + mRotation[1][1] * v.y + mRotation[2][1] * v.z,
                       mRotation[0][2] * v.x + mRotation[1][2] * v.y + mRotation[2][2] * v.z);
    }
    // transform a point: rotate (when flagged), scale, translate
    Vector3 TransformPoint(const Vector3& v) const
    {
        Vector3 r = (mFlags & kHasRotation) ? Rotate(v) : v;
        return Vector3(mTranslation.x + r.x * mScale,
                       mTranslation.y + r.y * mScale,
                       mTranslation.z + r.z * mScale);
    }
};

struct cSurfaceInfo {
    uint32_t mFlags;                    // +0x00
    uint32_t mPad[7];
    float    mPinOffset;                // +0x20
};

struct ISurface {
    virtual int  Release() = 0;
    virtual int  AddRef() = 0;
    virtual bool ApplySurface(float, const Vector3&, Vector3&, Vector3&, void*, void*) = 0;
    virtual float DistanceFromSurface(const Vector3& srcPoint, void*, void*) = 0;
    virtual bool FindClosestSurfacePoint(const Vector3& srcPoint, Vector3& dst, Vector3* normal,
                                         void* orientation, void* stateData, void* particleData) = 0;
};

struct cSurfaceRec {                    // 0x18
    ISurface*     mpSurface;            // +0x00
    cSurfaceInfo* mpInfo;               // +0x04
    int           mHasStateData;        // +0x08
    int           mStateDataOffset;     // +0x0c
    uint32_t      mPad[2];
};

struct IEffectMap {
    virtual int   AddRef() = 0;
    virtual int   Release() = 0;
    virtual void  Start() = 0;
    virtual void  Finish() = 0;
    virtual int   ModificationCount() = 0;
    virtual cBoundingBox GetBounds() = 0;
    virtual bool  PointInMap(const Vector3& position) = 0;         // +0x18
    virtual bool  InWorldSpace() = 0;
    virtual float Height(const Vector3& position) = 0;             // +0x20
    virtual Vector3 Normal(const Vector3& position) = 0;
    virtual Vector3 Velocity(const Vector3& position) = 0;
    virtual Vector4* ColorAlpha(Vector4* pOut, const Vector3& position) = 0;   // +0x2c
};

struct cParticleBase {                  // +0x08 in cParticle
    float   mAge;                       // +0x00
    float   mLife;                      // +0x04
    Vector3 mPosition;                  // +0x08
    Vector3 mVelocity;                  // +0x14
};

struct cParticle {                      // older layout (s00f79bb0)
    void*         mpNext;               // +0x00
    void*         mpPrev;               // +0x04
    cParticleBase mBase;                // +0x08
    float         mSize;                // +0x28
    float         mAspectRatio;         // +0x2c
    float         mRotation;            // +0x30
    float         mAlpha;               // +0x34
    Vector3       mColor;               // +0x38
    uint8_t       mFrame;               // +0x44
    uint8_t       mPad45[3];
    Vector3       mSurfaceNormal;       // +0x48
};

struct cParticlesDescription {          // older layout (s00f79bb0), retail offsets
    enum {
        kFlagEllipsoid = 1 << 4,        // ellipsoid emission volume
        kFlagPinToMap  = 1 << 5         // emit map height/colour modulation
    };

    uint32_t mPad0[2];                  // +0x00
    uint32_t mFlags;                    // +0x08 (low half of the flag bitset)
    uint32_t mFlagsHigh;                // +0x0c
    uint32_t mPad10[21];                // +0x10
    float    mTorusWidth;               // +0x64 (negative: box/ellipsoid instead)
    uint32_t mPad68[32];                // +0x68
    float    mColorVary[3];             // +0xe8
};

class cParticlesEffectOld {             // older layout (s00f79bb0)
public:
    char                   mPad00[0x17];            // +0x00
    uint8_t                mForcePin;               // +0x17 (always place on surface; name guessed)
    uint32_t               mPad18[3];               // +0x18
    cParticlesDescription* mDesc;                   // +0x24
    uint32_t               mPad28[2];               // +0x28
    void*                  mGlobalParams;           // +0x30
    uint32_t               mPad34[31];              // +0x34
    cTransform             mSourceTransform;        // +0xb0
    cTransform             mRigidTransform;         // +0xe8
    uint32_t               mPad120[30];             // +0x120
    IEffectMap*            mEmitMap;                // +0x198
    IEffectMap*            mEmitColorMap;           // +0x19c
    uint8_t                mPad1a0;                 // +0x1a0
    uint8_t                mEmitMapInWorldSpace;    // +0x1a1 (name guessed)
    uint8_t                mEmitColorMapInWorldSpace;   // +0x1a2
    uint8_t                mPad1a3[9];              // +0x1a3
    cBoundingBox           mEmissionVolume;         // +0x1ac
    uint32_t               mPad1c4[4];              // +0x1c4
    cSurfaceRec*           mSurfaceRecsBegin;       // +0x1d4
    cSurfaceRec*           mSurfaceRecsEnd;         // +0x1d8
    uint32_t               mPad1dc[4];              // +0x1dc
    uint8_t*               mSurfaceStateData;       // +0x1ec
    uint32_t               mPad1f0[4];              // +0x1f0
    uint8_t                mHaveSurfacePin;         // +0x200 (name guessed)
    uint8_t                mPad201[3];
};

// Unnamed in the PDB: keep the FUN_<va> names so the difftest resolves the calls to the originals.
extern "C" Vector3 FUN_007cdbe0(const cBoundingBox& box);                  // random point in a box
extern "C" Vector3 FUN_00a816d0(const cBoundingBox& box);                  // random point in an ellipsoid
extern "C" Vector3 FUN_00a817c0(const cBoundingBox& box, float width);     // random point on a torus
extern "C" double  FUN_007cdb90(const Vector2& range);                     // random float of a pair
extern "C" void    FUN_00705290(Vector3* dst, const Vector4* src);         // component-wise colour mul

// ------------------------------------------------------------------ 0x00F74FE0
// @ 0x00f74fe0
bool UpdateParticle(cParticle* particle, float dt, const cParticlesDescription* desc,
                    cParticlesEffectOld* effect)
{
    particle->mBase.mAge += dt;
    if (!(particle->mBase.mAge < particle->mBase.mLife))
        return false;

    // emission anchor and particle point, both taken through the rigid transform
    Vector3 emit = effect->mRigidTransform.TransformPoint(effect->mSourceTransform.mTranslation);
    Vector3 pos = effect->mRigidTransform.TransformPoint(particle->mBase.mPosition);

    float distSqEmit = emit.x * emit.x + emit.z * emit.z + emit.y * emit.y;
    float distSqPos = pos.x * pos.x + pos.z * pos.z + pos.y * pos.y;
    const float eps = kFXSampleEpsilon;
    float dot = pos.x * emit.x + pos.z * emit.z + pos.y * emit.y;
    float limit = (distSqEmit / (eps * eps + distSqEmit)) * distSqEmit * distSqPos;
    float dotSq = dot * dot;

    if (dotSq < limit) {
        if ((float)sRandom_Swarm.RandomDoubleUniform() >= kFXRandThreshold) {
            // pull the particle towards the emission axis by a random fraction
            float s = dot / distSqEmit;
            double r = sRandom_Swarm.RandomDoubleUniform();
            float t = (s / (float)sqrt((double)(distSqPos - s * dot))) * eps;
            float f = (float)(2.0 * (r + (1.0 - r) * (double)t));
            particle->mBase.mPosition = Vector3((emit.x * s - pos.x) * f + pos.x,
                                                (emit.y * s - pos.y) * f + pos.y,
                                                (emit.z * s - pos.z) * f + pos.z);
        } else if (desc->mTorusWidth < 0.0f) {
            // random point in the emission volume, then into effect space
            Vector3 p = ((desc->mFlags & cParticlesDescription::kFlagEllipsoid) != 0)
                            ? FUN_00a816d0(effect->mEmissionVolume)
                            : FUN_007cdbe0(effect->mEmissionVolume);
            particle->mBase.mPosition = p;
            effect->mSourceTransform.Transform(particle->mBase.mPosition);
        } else {
            Vector3 p = FUN_00a817c0(effect->mEmissionVolume, desc->mTorusWidth);
            particle->mBase.mPosition = p;
            effect->mSourceTransform.Transform(particle->mBase.mPosition);
        }

        particle->mAlpha = 1.0f;

        if ((desc->mFlags & cParticlesDescription::kFlagPinToMap) != 0 && effect->mEmitMap != 0) {
            Vector3 p = particle->mBase.mPosition;
            if (effect->mEmitMapInWorldSpace)
                effect->mRigidTransform.Transform(p);
            else
                effect->mSourceTransform.InverseTransformPoint(p);
            if (effect->mEmitMap->PointInMap(p)) {
                float height = effect->mEmitMap->Height(p);
                Vector2 range(effect->mEmissionVolume.mMin.z, effect->mEmissionVolume.mMax.z);
                height += (float)FUN_007cdb90(range);
                p.z = height;
                if (effect->mEmitMapInWorldSpace)
                    effect->mRigidTransform.InverseTransformPoint(p);
                else
                    effect->mSourceTransform.Transform(p);
                particle->mBase.mPosition = p;
            }
        }

        particle->mColor.x = (float)FUN_007d45d0(1.0f, desc->mColorVary[0]);
        particle->mColor.y = (float)FUN_007d45d0(1.0f, desc->mColorVary[1]);
        particle->mColor.z = (float)FUN_007d45d0(1.0f, desc->mColorVary[2]);

        if (effect->mEmitColorMap != 0) {
            Vector3 p = particle->mBase.mPosition;
            if (effect->mEmitColorMapInWorldSpace)
                effect->mRigidTransform.Transform(p);
            else
                effect->mSourceTransform.InverseTransformPoint(p);
            if (effect->mEmitColorMap->PointInMap(p)) {
                Vector4 color;
                effect->mEmitColorMap->ColorAlpha(&color, p);
                particle->mAlpha *= color.w;
                FUN_00705290(&particle->mColor, &color);
            }
        }

        if (effect->mEmitMap != 0) {
            Vector3 p = particle->mBase.mPosition;
            if (effect->mEmitMapInWorldSpace)
                effect->mRigidTransform.Transform(p);
            else
                effect->mSourceTransform.InverseTransformPoint(p);
            float height = effect->mEmitMap->Height(p);
            if (kFXHeightCutoff > height)
                particle->mAlpha = 0.0f;
        }
    }

    if (!effect->mForcePin && !(dotSq < limit))
        return true;
    if (!effect->mHaveSurfacePin)
        return true;

    uint8_t* stateData = effect->mSurfaceStateData;
    for (cSurfaceRec* rec = effect->mSurfaceRecsBegin; rec != effect->mSurfaceRecsEnd; ++rec) {
        if ((rec->mpInfo->mFlags & kSurfacePinFlags) == 0)
            continue;
        void* state = rec->mHasStateData ? stateData + rec->mStateDataOffset : 0;
        Vector3 normal;
        if (rec->mpSurface->FindClosestSurfacePoint(particle->mBase.mPosition,
                                                    particle->mBase.mPosition, &normal, 0, state, 0)) {
            float pinOffset = rec->mpInfo->mPinOffset;
            if (pinOffset != 0.0f) {
                particle->mBase.mPosition.x += pinOffset * normal.x;
                particle->mBase.mPosition.y += pinOffset * normal.y;
                particle->mBase.mPosition.z += pinOffset * normal.z;
            }
            particle->mSurfaceNormal = normal;
            break;
        }
    }

    particle->mColor.x = (float)RandRange(1.0 - desc->mColorVary[0], 1.0 + desc->mColorVary[0]);
    particle->mColor.y = (float)RandRange(1.0 - desc->mColorVary[1], 1.0 + desc->mColorVary[1]);
    particle->mColor.z = (float)RandRange(1.0 - desc->mColorVary[2], 1.0 + desc->mColorVary[2]);

    if (effect->mEmitColorMap != 0) {
        Vector3 p = particle->mBase.mPosition;
        if (effect->mEmitColorMapInWorldSpace)
            effect->mRigidTransform.Transform(p);
        else
            effect->mSourceTransform.InverseTransformPoint(p);
        if (effect->mEmitColorMap->PointInMap(p)) {
            Vector4 color;
            effect->mEmitColorMap->ColorAlpha(&color, p);
            particle->mAlpha *= color.w;
            particle->mColor.x *= color.x;
            particle->mColor.y *= color.y;
            particle->mColor.z *= color.z;
        }
    }
    return true;
}

// ------------------------------------------------------------------ 0x00F75990
// A sibling of cParticlesEffectOld whose transforms sit 8 bytes earlier (+0xa8/+0xe0).
class cDistributeEffectOld {
public:
    uint32_t      mPad00[32];           // +0x00
    Vector3       mBoundsMin;           // +0x80 (name guessed: world bounding box)
    Vector3       mBoundsMax;           // +0x8c
    uint32_t      mPad98;               // +0x98
    Vector3       mPosition;            // +0x9c
    cTransform    mSourceTransform;     // +0xa8
    cTransform    mRigidTransform;      // +0xe0
    uint32_t      mPad118[50];          // +0x118
    uint8_t       mTransformDirty;      // +0x1e0 (cleared here; name guessed)
    uint8_t       mPad1e1[0x9f];        // +0x1e1

    void SetTransforms(const void* pSource, const void* pRigid);
};

// @ 0x00f75990
void cDistributeEffectOld::SetTransforms(const void* pSource, const void* pRigid)
{
    mSourceTransform.Assign(pSource);
    mRigidTransform.Assign(pRigid);

    const Vector3 oldPosition = mPosition;
    mPosition = mSourceTransform.mTranslation;
    mTransformDirty = 0;

    if (mRigidTransform.mFlags & cTransform::kHasRotation)
        mPosition = mRigidTransform.Rotate(mPosition);
    mPosition *= mRigidTransform.mScale;
    mPosition += mRigidTransform.mTranslation;

    if (mBoundsMin.x != kFXMaxFloat && mBoundsMin.x != -kFXMaxFloat) {
        Vector3 delta(mPosition.x - oldPosition.x, mPosition.y - oldPosition.y,
                      mPosition.z - oldPosition.z);
        mBoundsMin += delta;
        mBoundsMax += delta;
    }
}
