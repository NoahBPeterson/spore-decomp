// Slice s00f5e910: 0x00F5EBF0, EA::Swarm particles effect: initialise one newly emitted particle.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Behaviour (in original order):
//   * age = 0, life = random in the description's life range;
//   * frame = effect frame start (+ random frame, optionally times the tile stride);
//   * position: if the description has the "follow path" flag (bit 31) the particle is placed on the
//     effect's path (own path points, or the description's when the effect has none, 0x00a79660); otherwise
//     a random point of the emission volume (torus when torusWidth >= 0, ellipsoid for flag bit 4, else box),
//     an optional surface placement (0x00f59e40, may reject the particle -> return false), a random
//     direction from the emit-direction box scaled to a random emit speed, plus the radial force push;
//   * size / aspect / alpha / colour = random variation around 1 (size times the current size scale);
//   * the emission colour map (if any) tints colour/alpha at the (optionally world-space) position;
//   * rotation = random +-rotationVary (1 when no variation);
//   * position and velocity are moved into the source transform's space (rotation if flag 2, scale,
//     translation);
//   * for the "stretch" flag (bit 3, not on a path) the position is pushed half a screen-space step along
//     the velocity;
//   * the first matching surface (if pinning to surfaces) snaps the position, offset by pinOffset along
//     its normal;
//   * the previous position = position, the 4 per-particle force vectors are cleared, flag +0x84 = false.
//
// NAMING NOTE: no symbol is known for 0x00F5EBF0. Layouts follow the dev PDB (EA::Swarm::cParticlesEffect,
// cParticle) and the ModAPI Swarm headers (ParticleEffect description, ISurface, IEffectMap, cSurfaceInfo),
// shifted to the retail offsets seen in the binary. Member names are taken from those sources where the
// field clearly corresponds; names marked "(name guessed)" are Claude-coined.
#include "types.h"
#include <math.h>

namespace rw { namespace math { namespace fpu {

struct Vector2
{
    float x, y;
    Vector2() {}
    Vector2(float ax, float ay) : x(ax), y(ay) {}
    Vector2(const Vector2& v) : x(v.x), y(v.y) {}
};

struct Vector3
{
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}

    float SquaredLength() const { return x * x + y * y + z * z; }
    Vector3 operator-(const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
};

}}} // namespace rw::math::fpu

typedef rw::math::fpu::Vector2 Vector2;
typedef rw::math::fpu::Vector3 Vector3;

namespace EA {

namespace Random {
struct RandomLinearCongruential
{
    uint32_t mnSeed;
    double   RandomDoubleUniform();                 // 0x009360d0
    uint32_t RandomUint32Uniform(uint32_t nLimit);  // 0x00a68fb0
};
} // namespace Random

namespace SP { extern Random::RandomLinearCongruential sMathRandom; }   // 0x01601760

namespace Swarm {

extern Random::RandomLinearCongruential sRandom;    // 0x016778dc
extern uint32_t kSurfaceEmitFlags;                  // 0x015b0c60 (0xe0)  (name guessed)
extern uint32_t kSurfacePinFlags;                   // 0x015b0c3c (0x0e)  (name guessed)

struct ColorRGBA { float r, g, b, a; };

struct cBoundingBox { Vector3 mMin, mMax; };

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
static __forceinline double RandomRange(const Vector2& range) { return RandomRange(range.x, range.y); }
static __forceinline double RandomVary(float vary) { return RandomRange(1.0f - vary, 1.0f + vary); }

static inline bool TestBit(uint32_t flags, int bit) { return ((flags >> bit) & 1) != 0; }

float   RandomInRange(const Vector2& range);                                    // 0x004df2d0
float   RandomSymmetric(float range);                                           // 0x00572a60 (name guessed)
Vector3 RandomPointInBox(const cBoundingBox& box);                              // 0x007cdbe0 (name guessed)
Vector3 RandomPointInEllipsoid(const cBoundingBox& box);                        // 0x00a816d0 (name guessed)
Vector3 RandomPointInTorus(const cBoundingBox& box, float width);               // 0x00a817c0 (name guessed)

struct cPathPoint;
struct cPathPoints { cPathPoint* mpBegin; cPathPoint* mpEnd; cPathPoint* mpCapacity; uint32_t mAllocator; };

struct cParticleBase                // +0x08 in cParticle
{
    float   mAge;
    float   mLife;
    Vector3 mPosition;
    Vector3 mVelocity;
};

bool PlaceParticleOnPath(cParticleBase* particle, const cPathPoints* path);    // 0x00a79660 (name guessed)

struct cParticle                    // 0x88 (retail)
{
    void*         mpNext;           // +0x00 intrusive_list_node
    void*         mpPrev;
    cParticleBase mBase;            // +0x08
    float         mSize;            // +0x28
    float         mAspectRatio;     // +0x2c
    float         mRotation;        // +0x30
    float         mAlpha;           // +0x34
    Vector3       mColor;           // +0x38
    uint8_t       mFrame;           // +0x44
    uint8_t       mUnused[3];
    Vector3       mPrevPosition;    // +0x48 (name guessed)
    Vector3       mForces[4];       // +0x54 (name guessed)
    bool          mCollided;        // +0x84 (name guessed)
};

struct cSurfaceInfo
{
    uint32_t mFlags;                // +0x00
    uint32_t mPad[7];
    float    mPinOffset;            // +0x20
};

struct ISurface
{
    virtual int  Release() = 0;
    virtual int  AddRef() = 0;
    virtual bool ApplySurface(float, const Vector3&, Vector3&, Vector3&, void*, void*) = 0;
    virtual float DistanceFromSurface(const Vector3& srcPoint, void*, void*) = 0;
    virtual bool FindClosestSurfacePoint(const Vector3& srcPoint, Vector3& dst, Vector3* normal,
                                         void* orientation, void* stateData, void* particleData) = 0;
};

struct cSurfaceRec                  // 0x18
{
    ISurface*     mpSurface;
    cSurfaceInfo* mpInfo;
    int           mHasStateData;    // (name guessed)
    int           mStateDataOffset; // (name guessed)
    uint32_t      mPad[2];
};

struct IEffectMap
{
    virtual int  AddRef() = 0;
    virtual int  Release() = 0;
    virtual void Start() = 0;
    virtual void Finish() = 0;
    virtual int  ModificationCount() = 0;
    virtual cBoundingBox GetBounds() = 0;
    virtual bool PointInMap(const Vector3& position) = 0;
    virtual bool InWorldSpace() = 0;
    virtual float Height(const Vector3& position) = 0;
    virtual Vector3 Normal(const Vector3& position) = 0;
    virtual Vector3 Velocity(const Vector3& position) = 0;
    virtual ColorRGBA ColorAlpha(const Vector3& position) = 0;
};

struct cTransform                   // 0x38
{
    uint16_t mFlags;                // +0x00 (bit 1: has rotation)
    uint16_t mPad;
    Vector3  mTranslation;          // +0x04
    float    mScale;                // +0x10
    float    mRotation[3][3];       // +0x14 (row vectors)

    void Transform(Vector3& v) const;   // 0x007cdee0 (name guessed)

    Vector3 Rotate(const Vector3& v) const
    {
        return Vector3(mRotation[1][0] * v.y + mRotation[2][0] * v.z + v.x * mRotation[0][0],
                       mRotation[0][1] * v.x + mRotation[1][1] * v.y + mRotation[2][1] * v.z,
                       mRotation[0][2] * v.x + mRotation[1][2] * v.y + mRotation[2][2] * v.z);
    }
};

struct cGlobalParams
{
    uint32_t mPad[0x17];
    Vector3  mCameraRight;          // +0x5c (name guessed)
    uint32_t mPad2[3];
    Vector3  mCameraUp;             // +0x74 (name guessed)
};

struct cParticlesDescription        // ModAPI Swarm::Components::ParticleEffect, retail offsets
{
    uint32_t mPad0[2];
    uint32_t mFlags;                // +0x08
    Vector2  mLife;                 // +0x0c
    uint32_t mPad14[5];
    cBoundingBox mEmitDirection;    // +0x28
    Vector2  mEmitSpeed;            // +0x40
    cBoundingBox mEmitVolume;       // +0x48
    float    mTorusWidth;           // +0x60
    uint32_t mPad64[8];
    float*   mSizeCurve;            // +0x84 eastl::vector<float>::mpBegin
    uint32_t mPad88[4];
    float    mSizeVary;             // +0x98
    uint32_t mPad9c[5];
    float    mAspectRatioVary;      // +0xb0
    uint32_t mPadb4[5];
    float    mRotationVary;         // +0xc8
    uint32_t mPadcc[6];
    float    mColorVary[3];         // +0xe4
    uint32_t mPadf0[5];
    float    mAlphaVary;            // +0x104
    uint32_t mPad108[9];
    uint16_t mPad12c;
    uint8_t  mFrameStride;          // +0x12e (name guessed)
    uint8_t  mFrameRandom;          // +0x12f (name guessed)
    uint32_t mPad130[6];
    float    mRadialForce;          // +0x148
    Vector3  mRadialForceLocation;  // +0x14c
    float    mPad158;
    float    mStretchScale;         // +0x15c (name guessed)
    uint32_t mPad160[61];
    cPathPoints mPathPoints;        // +0x254
};

class cParticlesEffect
{
public:
    uint32_t               mPad0[9];
    cParticlesDescription* mDesc;               // +0x24
    uint32_t               mPad28[3];
    cGlobalParams*         mGlobalParams;       // +0x34
    uint32_t               mPad38[38];
    cTransform             mSourceTransform;    // +0xd0
    cTransform             mRigidTransform;     // +0x108
    uint32_t               mPad140[10];
    float                  mEmitVelocityScale;  // +0x168
    uint32_t               mPad16c[7];
    uint8_t                mFrameStart;         // +0x188
    uint8_t                mPad189[3];
    uint32_t               mPad18c[3];
    float                  mCurrentSizeScale;   // +0x198
    uint32_t               mPad19c[9];
    IEffectMap*            mEmitColorMap;       // +0x1c0
    bool                   mPad1c4[2];
    bool                   mEmitColorMapInWorldSpace;   // +0x1c6
    bool                   mPad1c7;
    cBoundingBox           mEmissionVolume;     // +0x1c8
    uint32_t               mPad1e0[3];
    cSurfaceRec*           mSurfaceRecsBegin;   // +0x1ec
    cSurfaceRec*           mSurfaceRecsEnd;     // +0x1f0
    uint32_t               mPad1f4[4];
    uint8_t*               mSurfaceStateData;   // +0x204
    uint32_t               mPad208[4];
    bool                   mHaveSurfacePin;     // +0x218
    uint8_t                mPad219[3];
    cPathPoints            mPathPoints;         // +0x21c

    bool PlaceParticleOnSurface(cParticle* particle);   // 0x00f59e40 (name guessed)
    bool InitParticle(cParticle* particle);             // 0x00f5ebf0 (name guessed)
};

bool cParticlesEffect::InitParticle(cParticle* particle)
{
    particle->mBase.mAge = 0.0f;
    particle->mBase.mLife = (float)RandomRange(mDesc->mLife);

    particle->mFrame = mFrameStart;
    if (mDesc->mFrameRandom > 0)
    {
        if (mDesc->mFrameStride > 0)
            particle->mFrame += (uint8_t)(sRandom.RandomUint32Uniform(mDesc->mFrameRandom) * mDesc->mFrameStride);
        else
            particle->mFrame += (uint8_t)sRandom.RandomUint32Uniform(mDesc->mFrameRandom);
    }

    bool onPath;
    float speed;
    if (TestBit(mDesc->mFlags, 31))
    {
        const cPathPoints* path = &mPathPoints;
        if (mPathPoints.mpBegin == mPathPoints.mpEnd)
            path = &mDesc->mPathPoints;
        if (PlaceParticleOnPath(&particle->mBase, path))
        {
            onPath = true;
            goto Properties;
        }
    }

    onPath = false;
    if (mDesc->mTorusWidth >= 0.0f)
        particle->mBase.mPosition = RandomPointInTorus(mEmissionVolume, mDesc->mTorusWidth);
    else if (TestBit(mDesc->mFlags, 4))
        particle->mBase.mPosition = RandomPointInEllipsoid(mEmissionVolume);
    else
        particle->mBase.mPosition = RandomPointInBox(mEmissionVolume);

    if ((mDesc->mFlags & kSurfaceEmitFlags) != 0 && !PlaceParticleOnSurface(particle))
        return false;

    particle->mBase.mVelocity = RandomPointInBox(mDesc->mEmitDirection);
    speed = RandomInRange(Vector2(mDesc->mEmitSpeed)) * mEmitVelocityScale;
    {
        Vector3& vel = particle->mBase.mVelocity;
        float lengthSq = vel.SquaredLength();
        if (lengthSq > 0.0f)
            vel *= speed / sqrtf(lengthSq);
    }
    {
        float radial = mDesc->mRadialForce;
        if (radial != 0.0f)
        {
            Vector3 d = particle->mBase.mPosition - mDesc->mRadialForceLocation;
            float lengthSq = d.SquaredLength();
            if (lengthSq > 0.0f)
                particle->mBase.mVelocity += d * (radial / sqrtf(lengthSq));
        }
    }

Properties:
    particle->mSize = (float)(RandomVary(mDesc->mSizeVary) * mCurrentSizeScale);
    particle->mAspectRatio = (float)RandomVary(mDesc->mAspectRatioVary);
    particle->mAlpha = (float)RandomVary(mDesc->mAlphaVary);
    particle->mColor.x = (float)RandomVary(mDesc->mColorVary[0]);
    particle->mColor.y = (float)RandomVary(mDesc->mColorVary[1]);
    particle->mColor.z = (float)RandomVary(mDesc->mColorVary[2]);

    if (mEmitColorMap)
    {
        Vector3 p = particle->mBase.mPosition;
        if (mEmitColorMapInWorldSpace)
        {
            mSourceTransform.Transform(p);
            mRigidTransform.Transform(p);
        }
        if (mEmitColorMap->PointInMap(p))
        {
            ColorRGBA c = mEmitColorMap->ColorAlpha(p);
            particle->mAlpha = particle->mAlpha * c.a;
            particle->mColor = Vector3(particle->mColor.x * c.r, c.g * particle->mColor.y,
                                       c.b * particle->mColor.z);
        }
    }

    {
        float rotationVary = mDesc->mRotationVary;
        if (rotationVary > 0.0f)
            particle->mRotation = RandomSymmetric(rotationVary);
        else
            particle->mRotation = 1.0f;
    }

    Vector3& pos = particle->mBase.mPosition;
    if (mSourceTransform.mFlags & 2)
        pos = mSourceTransform.Rotate(pos);
    {
        float s = mSourceTransform.mScale;
        pos.x = s * pos.x;
        pos.y = s * pos.y;
        pos.z = s * pos.z;
    }
    pos.x = mSourceTransform.mTranslation.x + pos.x;
    pos.y = mSourceTransform.mTranslation.y + pos.y;
    pos.z = mSourceTransform.mTranslation.z + pos.z;
    if (mSourceTransform.mFlags & 2)
        particle->mBase.mVelocity = mSourceTransform.Rotate(particle->mBase.mVelocity);

    if (!onPath && TestBit(mDesc->mFlags, 3))
    {
        const cGlobalParams* gp = mGlobalParams;
        const Vector3& v = particle->mBase.mVelocity;
        float up = v.x * gp->mCameraUp.x + v.z * gp->mCameraUp.z + v.y * gp->mCameraUp.y;
        float right = v.x * gp->mCameraRight.x + v.z * gp->mCameraRight.z + v.y * gp->mCameraRight.y;
        float invSpeed = 1.0f / speed;
        float screen = sqrtf(right * right + up * up) / mDesc->mStretchScale;
        float size0 = *mDesc->mSizeCurve;
        pos.x = v.x * 0.5f * screen * size0 * invSpeed + pos.x;
        pos.y = pos.y + v.y * 0.5f * screen * size0 * invSpeed;
        pos.z = pos.z + v.z * 0.5f * screen * size0 * invSpeed;
    }

    if (mHaveSurfacePin)
    {
        uint8_t* stateData = mSurfaceStateData;
        for (cSurfaceRec* rec = mSurfaceRecsBegin; rec != mSurfaceRecsEnd; ++rec)
        {
            if ((rec->mpInfo->mFlags & kSurfacePinFlags) == 0)
                continue;
            void* state = rec->mHasStateData ? stateData + rec->mStateDataOffset : 0;
            Vector3 normal;
            if (rec->mpSurface->FindClosestSurfacePoint(pos, pos, &normal, 0, state, 0))
            {
                float offset = rec->mpInfo->mPinOffset;
                if (offset != 0.0f)
                {
                    pos.x = pos.x + normal.x * offset;
                    pos.y = normal.y * offset + pos.y;
                    pos.z = normal.z * offset + pos.z;
                }
                break;
            }
        }
    }

    particle->mPrevPosition = pos;
    particle->mForces[0] = Vector3(0.0f, 0.0f, 0.0f);
    particle->mForces[1] = Vector3(0.0f, 0.0f, 0.0f);
    particle->mForces[2] = Vector3(0.0f, 0.0f, 0.0f);
    particle->mForces[3] = Vector3(0.0f, 0.0f, 0.0f);
    particle->mCollided = false;
    return true;
}

}} // namespace EA::Swarm
