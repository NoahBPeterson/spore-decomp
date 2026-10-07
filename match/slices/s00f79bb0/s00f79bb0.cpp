// Slice s00f79bb0: 0x00F79BF0, EA::Swarm particles effect (older cParticlesEffect.obj copy, like the
// quad streamers in s00f77940/s00f78a60): initialise one newly emitted particle.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Same algorithm as cParticlesEffect::InitParticle (0x00f5ebf0, slice s00f5e910) on an older
// effect/description/particle layout, with these differences (all read off the asm):
//   * the surface placement result (0x00f75c10) does not reject the particle: it becomes the
//     particle's initial alpha (1 when placed, 0 when not); there is no alpha variation;
//   * the life range uses SP::sMathRandom, the size/aspect/colour variations use Swarm::sRandom;
//   * the surface-emission test is a 64-bit flag mask (description +0x08/+0x0c vs 0x016c9b94);
//   * surface pinning also stores the surface normal in the particle (+0x48), and the function
//     ends there: no previous-position / force / collided resets.
//
// NAMING NOTE: no symbol is known for 0x00F79BF0; the class is called cParticlesEffectOld here
// (Claude-coined) and InitParticle follows the sibling's (guessed) name. Layout names follow
// s00f5e910 at the older offsets.
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
extern uint64_t kSurfaceEmitFlags;                  // 0x016c9b94 (64-bit flag mask)  (name guessed)
extern uint32_t kSurfacePinFlags;                   // 0x015b0ee4  (name guessed)

struct ColorRGBA { float r, g, b, a; };

struct cBoundingBox { Vector3 mMin, mMax; };

// Random in [lo, hi], clamped (inlined everywhere in the original)
static __forceinline double RandomRangeM(double lo, double hi)
{
    double v = SP::sMathRandom.RandomDoubleUniform() * (hi - lo) + lo;
    if (v >= hi)
        return hi;
    if (lo > v)
        return lo;
    return v;
}
static __forceinline double RandomRangeS(double lo, double hi)
{
    double v = sRandom.RandomDoubleUniform() * (hi - lo) + lo;
    if (v >= hi)
        return hi;
    if (lo > v)
        return lo;
    return v;
}
static __forceinline double RandomRange(Vector2 range) { return RandomRangeM(range.x, range.y); }
static __forceinline double RandomVary(float vary) { return RandomRangeS(1.0f - vary, 1.0f + vary); }

static inline bool TestBit(uint32_t flags, int bit) { return ((flags >> bit) & 1) != 0; }

float   RandomInRange(const Vector2& range);                                    // 0x004df2d0
float   RandomSymmetric(float range);                                           // 0x00a78f80: random in [-range, range] from Swarm::sRandom (name guessed; 0x00572a60 is the sMathRandom twin)
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

struct cParticle                    // older layout
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
    Vector3       mSurfaceNormal;   // +0x48 (name guessed)
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

struct cParticlesDescription        // older layout of the description (ModAPI ParticleEffect)
{
    uint32_t mPad0[2];
    uint64_t mFlags;                // +0x08 (bit 31: follow path; bit 4: ellipsoid; bit 3: stretch)
    Vector2  mLife;                 // +0x10
    uint32_t mPad18[5];
    cBoundingBox mEmitDirection;    // +0x2c
    Vector2  mEmitSpeed;            // +0x44
    uint32_t mPad4c[6];
    float    mTorusWidth;           // +0x64
    uint32_t mPad68[8];
    float*   mSizeCurve;            // +0x88 eastl::vector<float>::mpBegin
    uint32_t mPad8c[4];
    float    mSizeVary;             // +0x9c
    uint32_t mPada0[5];
    float    mAspectRatioVary;      // +0xb4
    uint32_t mPadb8[5];
    float    mRotationVary;         // +0xcc
    uint32_t mPadd0[6];
    float    mColorVary[3];         // +0xe8
    uint32_t mPadf4[16];
    uint16_t mPad134;
    uint8_t  mFrameStride;          // +0x136 (name guessed)
    uint8_t  mFrameRandom;          // +0x137 (name guessed)
    uint32_t mPad138[6];
    float    mRadialForce;          // +0x150
    Vector3  mRadialForceLocation;  // +0x154
    float    mPad160;
    float    mStretchScale;         // +0x164 (name guessed)
    uint32_t mPad168[61];
    cPathPoints mPathPoints;        // +0x25c
};

class cParticlesEffectOld
{
public:
    uint32_t               mPad0[9];
    cParticlesDescription* mDesc;               // +0x24
    uint32_t               mPad28[2];
    cGlobalParams*         mGlobalParams;       // +0x30
    uint32_t               mPad34[31];
    cTransform             mSourceTransform;    // +0xb0
    cTransform             mRigidTransform;     // +0xe8
    uint32_t               mPad120[10];
    float                  mEmitVelocityScale;  // +0x148
    uint32_t               mPad14c[7];
    uint8_t                mFrameStart;         // +0x168
    uint8_t                mPad169[3];
    uint32_t               mPad16c[3];
    float                  mCurrentSizeScale;   // +0x178
    uint32_t               mPad17c[8];
    IEffectMap*            mEmitColorMap;       // +0x19c
    bool                   mPad1a0[2];
    bool                   mEmitColorMapInWorldSpace;   // +0x1a2
    bool                   mPad1a3;
    uint32_t               mPad1a4[2];
    cBoundingBox           mEmissionVolume;     // +0x1ac
    uint32_t               mPad1c4[4];
    cSurfaceRec*           mSurfaceRecsBegin;   // +0x1d4
    cSurfaceRec*           mSurfaceRecsEnd;     // +0x1d8
    uint32_t               mPad1dc[4];
    uint8_t*               mSurfaceStateData;   // +0x1ec
    uint32_t               mPad1f0[4];
    bool                   mHaveSurfacePin;     // +0x200
    uint8_t                mPad201[3];
    cPathPoints            mPathPoints;         // +0x204

    bool PlaceParticleOnSurface(cParticle* particle);   // 0x00f75c10 (name guessed)
    bool InitParticle(cParticle* particle);             // 0x00f79bf0 (name guessed)

    bool PlaceOnPath(cParticle* particle)
    {
        const cPathPoints* path = &mPathPoints;
        if (mPathPoints.mpBegin == mPathPoints.mpEnd)
            path = &mDesc->mPathPoints;
        return PlaceParticleOnPath(&particle->mBase, path);
    }
};

// @ 0x00f79bf0
bool cParticlesEffectOld::InitParticle(cParticle* particle)
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

    const bool onPath = TestBit((uint32_t)mDesc->mFlags, 31) && PlaceOnPath(particle);
    bool placed = true;
    float speed;
    if (!onPath)
    {
        if (mDesc->mTorusWidth >= 0.0f)
            particle->mBase.mPosition = RandomPointInTorus(mEmissionVolume, mDesc->mTorusWidth);
        else if (TestBit((uint32_t)mDesc->mFlags, 4))
            particle->mBase.mPosition = RandomPointInEllipsoid(mEmissionVolume);
        else
            particle->mBase.mPosition = RandomPointInBox(mEmissionVolume);

        if ((mDesc->mFlags & kSurfaceEmitFlags) != 0)
            placed = PlaceParticleOnSurface(particle);

        particle->mBase.mVelocity = RandomPointInBox(mDesc->mEmitDirection);
        speed = RandomInRange(Vector2(mDesc->mEmitSpeed)) * mEmitVelocityScale;
        {
            float lengthSq = particle->mBase.mVelocity.SquaredLength();
            if (lengthSq > 0.0f)
                particle->mBase.mVelocity *= speed / sqrtf(lengthSq);
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
    }

    particle->mSize = (float)(RandomVary(mDesc->mSizeVary) * mCurrentSizeScale);
    particle->mAspectRatio = (float)RandomVary(mDesc->mAspectRatioVary);
    particle->mAlpha = placed ? 1.0f : 0.0f;
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
            particle->mColor = Vector3(particle->mColor.x * c.r, particle->mColor.y * c.g,
                                       particle->mColor.z * c.b);
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

    if (!onPath && TestBit((uint32_t)mDesc->mFlags, 3))
    {
        const cGlobalParams* gp = mGlobalParams;
        const Vector3& v = particle->mBase.mVelocity;
        float up = v.x * gp->mCameraUp.x + v.z * gp->mCameraUp.z + v.y * gp->mCameraUp.y;
        float right = v.x * gp->mCameraRight.x + v.z * gp->mCameraRight.z + v.y * gp->mCameraRight.y;
        float invSpeed = 1.0f / speed;
        float screen = sqrtf(right * right + up * up) / mDesc->mStretchScale;
        float size0 = *mDesc->mSizeCurve;
        pos += v * 0.5f * screen * size0 * invSpeed;
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
                particle->mSurfaceNormal = normal;
                return true;
            }
        }
    }
    return true;
}

}} // namespace EA::Swarm
