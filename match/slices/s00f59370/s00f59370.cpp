// Slice s00f59370: 0x00F595E0, EA::Swarm particles effect: apply the force map to one particle.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Behaviour (position P = the particle position, moved into map space when the map is in world space:
// P = translation + scale * rotation(P)):
//   * P outside the map: nothing else happens; the particle survives unless description flag bit 17 is set;
//   * flag bit 15: velocity = mapVelocity(P) * mapRepulseStrength * mCurrentMapForceScale (replaces velocity);
//   * flag bit 16: velocity += mapVelocity(P) * mCurrentMapForceScale * dt;
//   * flag bit 14 (repulsion): probe point P + scoutDistance * (velocity normalized when faster than 10, else
//     velocity * 0.1); outside the map nothing happens; below the kill height the particle dies; within the
//     repulse height velocity += normal * (repulseHeight - height)^2 * strength * scale * dt (z also times
//     mapRepulseDistance);
//   * otherwise (surface): without bounce the particle is lifted onto the map height when below it (or always
//     with flag bit 18) and the velocity component into the surface is cancelled; with bounce a particle below the
//     surface dies with probabilityDeath, else it is placed on the map and its velocity reflected
//     (v -= n * dot(n, v) * (1 + bounce));
//   * finally the position trail (5 entries at +0x48, count byte at +0x84) gets the map-space position when
//     the particle moved more than 0.005 from the last entry (oldest entry dropped when full).
// NAMING NOTE: no symbol is known for 0x00F595E0. Layouts follow the dev PDB (cParticlesEffect), ModAPI
// ParticleEffect / IEffectMap, shifted to the retail offsets seen in the binary; names marked "(name guessed)"
// are Claude-coined.
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

}}} // namespace rw::math::fpu

typedef rw::math::fpu::Vector3 Vector3;

namespace EA { namespace Random {
class RandomLinearCongruential
{ public:
    uint32_t mnSeed;
    double   RandomDoubleUniform();                 // 0x009360d0
};
}} // namespace EA::Random

namespace SP {
extern EA::Random::RandomLinearCongruential sMathRandom;   // 0x01601760
}

namespace EA { namespace Swarm {

struct cTransform                   // 0x38
{
    uint16_t mFlags;                // +0x00 (bit 1: has rotation)
    uint16_t mPad;
    Vector3  mTranslation;          // +0x04
    float    mScale;                // +0x10
    float    mRotation[3][3];       // +0x14 (row vectors)

    void TransformDirection(Vector3* v) const;          // 0x007cdee0 (name guessed)
    void InverseTransformPoint(Vector3* v) const;       // 0x007cda70 (name guessed)
    void InverseTransformVector(Vector3* v) const;      // 0x00a78e90 (name guessed)
    void InverseRotateVector(Vector3* v) const;         // 0x00a7ca50 (name guessed)
};

struct IEffectMap
{
    virtual int  AddRef() = 0;
    virtual int  Release() = 0;
    virtual void Start() = 0;
    virtual void Finish() = 0;
    virtual int  ModificationCount() = 0;
    virtual void GetBounds(void* out) = 0;
    virtual bool PointInMap(const Vector3& position) = 0;
    virtual bool InWorldSpace() = 0;
    virtual float Height(const Vector3& position) = 0;
    virtual Vector3 Normal(const Vector3& position) = 0;
    virtual Vector3 Velocity(const Vector3& position) = 0;
};

struct cParticlesDescription        // retail offsets
{
    uint32_t mPad0[2];
    uint32_t mFlags;                // +0x08
    char     mPad0c[0x1bc - 0x0c];
    float    mMapBounce;            // +0x1bc
    float    mMapRepulseHeight;     // +0x1c0
    float    mMapRepulseStrength;   // +0x1c4
    float    mMapRepulseScoutDistance;  // +0x1c8
    float    mMapRepulseDistance;   // +0x1cc
    float    mMapRepulseKillHeight; // +0x1d0
    float    mProbabilityDeath;     // +0x1d4
};

struct cParticle                    // 0x88 (retail)
{
    char    mPad0[0x10];
    Vector3 mPosition;              // +0x10
    Vector3 mVelocity;              // +0x1c
    char    mPad28[0x48 - 0x28];
    Vector3 mTrail[5];              // +0x48 recent positions (name guessed)
    uint8_t mTrailCount;            // +0x84 index of the newest trail entry (name guessed)
};

class cParticlesEffect
{
public:
    char                   mPad0[0x24];
    cParticlesDescription* mDesc;                   // +0x24
    char                   mPad28[0x108 - 0x28];
    cTransform             mRigidTransform;         // +0x108
    char                   mPad140[0x1a4 - 0x140];
    float                  mCurrentMapForceScale;   // +0x1a4
    char                   mPad1a8[0x1b8 - 0x1a8];
    IEffectMap*            mForceMap;               // +0x1b8
    char                   mPad1bc[0x1c4 - 0x1bc];
    bool                   mForceMapInWorldSpace;   // +0x1c4

    bool ApplyForceMap(cParticle* particle, float dt);   // 0x00f595e0 (name guessed)
};

}} // namespace EA::Swarm

namespace EA { namespace Swarm {

// @ 0x00f595e0
bool cParticlesEffect::ApplyForceMap(cParticle* particle, float dt)
{
    Vector3 P(particle->mPosition.x, particle->mPosition.y, particle->mPosition.z);
    // Rotation scratch.  The branch-local result below is copy-initialised, so cl
    // hands its address to Velocity as the hidden return buffer; the stack allocator
    // then reuses this dead rotation slot for it, which is what the retail build did.
    Vector3 rot;

    if (mForceMapInWorldSpace)
    {
        if (mRigidTransform.mFlags & 2)
        {
            const float (&Rm)[3][3] = mRigidTransform.mRotation;
            rot.x = (Rm[2][0] * P.z + Rm[1][0] * P.y) + Rm[0][0] * P.x;
            rot.y = (Rm[0][1] * P.x + Rm[2][1] * P.z) + Rm[1][1] * P.y;
            rot.z = (Rm[0][2] * P.x + Rm[2][2] * P.z) + Rm[1][2] * P.y;
            P = rot;
        }
        float s = mRigidTransform.mScale;
        P.x = mRigidTransform.mTranslation.x + s * P.x;
        P.y = mRigidTransform.mTranslation.y + P.y * s;
        P.z = mRigidTransform.mTranslation.z + P.z * s;
    }

    if (!mForceMap->PointInMap(P))
        return ((mDesc->mFlags >> 17) & 1) == 0;

    Vector3 oldPos(particle->mPosition.x, particle->mPosition.y, particle->mPosition.z);
    uint32_t flags = mDesc->mFlags;

    if ((flags >> 15) & 1)
    {
        Vector3 v = mForceMap->Velocity(P);
        if (mForceMapInWorldSpace)
            mRigidTransform.InverseTransformVector(&v);
        float k = mDesc->mMapRepulseStrength;
        float s = mCurrentMapForceScale;
        particle->mVelocity.x = s * (k * v.x);
        particle->mVelocity.y = (v.y * k) * s;
        particle->mVelocity.z = (v.z * k) * s;
    }
    else if ((flags >> 16) & 1)
    {
        Vector3 v = mForceMap->Velocity(P);
        if (mForceMapInWorldSpace)
            mRigidTransform.InverseTransformVector(&v);
        float s = mCurrentMapForceScale;
        particle->mVelocity.x = particle->mVelocity.x + (s * v.x) * dt;
        particle->mVelocity.y = (v.y * s) * dt + particle->mVelocity.y;
        particle->mVelocity.z = (v.z * s) * dt + particle->mVelocity.z;
    }
    else if ((flags >> 14) & 1)
    {
        float scout = mDesc->mMapRepulseScoutDistance;
        float vx = particle->mVelocity.x;
        float vy = particle->mVelocity.y;
        float vz = particle->mVelocity.z;
        float len = sqrtf(vx * vx + vz * vz + vy * vy);
        Vector3 d;
        if (len > 10.0f)
        {
            float inv = 1.0f / len;
            d.x = inv * (scout * vx);
            d.y = inv * (scout * vy);
            d.z = inv * (scout * vz);
        }
        else
        {
            d.x = (scout * vx) * 0.1f;
            d.y = (scout * vy) * 0.1f;
            d.z = (scout * vz) * 0.1f;
        }
        if (mForceMapInWorldSpace)
            mRigidTransform.TransformDirection(&d);
        Vector3 Q(d.x + P.x, d.y + P.y, d.z + P.z);
        if (mForceMap->PointInMap(Q))
        {
            float h = mForceMap->Height(Q);
            float dist = Q.z - h;
            if (mDesc->mMapRepulseKillHeight > dist)
                return false;
            if (mDesc->mMapRepulseHeight > dist)
            {
                Vector3 n = mForceMap->Normal(Q);
                if (mForceMapInWorldSpace)
                    mRigidTransform.InverseRotateVector(&n);
                float t = mDesc->mMapRepulseHeight - dist;
                t = t * t;
                float nx = n.x * t;
                float ny = n.y * t;
                float nz = n.z * t;
                float k = (mDesc->mMapRepulseStrength * mCurrentMapForceScale) * dt;
                particle->mVelocity.x = particle->mVelocity.x + nx * k;
                particle->mVelocity.y = ny * k + particle->mVelocity.y;
                particle->mVelocity.z = (mDesc->mMapRepulseDistance * nz) * k + particle->mVelocity.z;
            }
        }
    }
    else if (mDesc->mMapBounce == 0.0f)
    {
        float h = mForceMap->Height(P);
        if (((mDesc->mFlags >> 18) & 1) || h > P.z)
        {
            particle->mPosition.x = P.x;
            particle->mPosition.y = P.y;
            particle->mPosition.z = h;
            Vector3 n = mForceMap->Normal(P);
            if (mForceMapInWorldSpace)
            {
                mRigidTransform.InverseTransformPoint(&particle->mPosition);
                mRigidTransform.InverseRotateVector(&n);
            }
            float vx = particle->mVelocity.x;
            float vy = particle->mVelocity.y;
            float vz = particle->mVelocity.z;
            float d = -((vz * n.z + vy * n.y) + vx * n.x);
            if (d > 0.0f)
            {
                particle->mVelocity.x = n.x * d + vx;
                particle->mVelocity.y = n.y * d + vy;
                particle->mVelocity.z = n.z * d + vz;
            }
        }
    }
    else
    {
        float h = mForceMap->Height(P);
        if (h > P.z)
        {
            float death = mDesc->mProbabilityDeath;
            if (death != 0.0f)
            {
                if (death == 1.0f)
                    return false;
                if (SP::sMathRandom.RandomDoubleUniform() <= mDesc->mProbabilityDeath)
                    return false;
            }
            particle->mPosition.x = P.x;
            particle->mPosition.y = P.y;
            particle->mPosition.z = h;
            Vector3 n = mForceMap->Normal(P);
            if (mForceMapInWorldSpace)
            {
                mRigidTransform.InverseTransformPoint(&particle->mPosition);
                mRigidTransform.InverseRotateVector(&n);
            }
            float vx = particle->mVelocity.x;
            float vy = particle->mVelocity.y;
            float vz = particle->mVelocity.z;
            float e = ((n.z * vz + n.y * vy) + n.x * vx) * (mDesc->mMapBounce + 1.0f);
            particle->mVelocity.x = vx - n.x * e;
            particle->mVelocity.y = vy - n.y * e;
            particle->mVelocity.z = vz - n.z * e;
        }
    }

    // position trail
    int idx = particle->mTrailCount;
    const Vector3& last = particle->mTrail[idx];
    float dx = oldPos.x - last.x;
    float dy = oldPos.y - last.y;
    float dz = oldPos.z - last.z;
    if (sqrtf((dz * dz + dy * dy) + dx * dx) >= 0.005f)
    {
        int n = idx + 1;
        if (n >= 5)
        {
            particle->mTrail[0] = particle->mTrail[1];
            particle->mTrail[1] = particle->mTrail[2];
            particle->mTrail[2] = particle->mTrail[3];
            particle->mTrail[3] = particle->mTrail[4];
            particle->mTrail[particle->mTrailCount] = P;
            return true;
        }
        particle->mTrail[n] = P;
        particle->mTrailCount = (uint8_t)n;
    }
    return true;
}

}} // namespace EA::Swarm

// ===========================================================================
// 00f59370 / 00f59e40 -- particle force-map transform step and evaluation
// ===========================================================================
namespace EA { namespace Swarm {

// 0x38-byte transform with the out-of-line assignment helper 0x00537dc0.
struct cSPTransformOps : cTransform
{
    cSPTransformOps* Assign(const void* src);       // 0x00537dc0
};

// Object 8 bytes before the evaluation object (00f59370's `this`), used by 0x00f58b70.
struct cParticlesOwner
{
    void Release(void* block);                      // 0x00f58b70
};

// 00f59370's view of the effect (its `this` is the evaluation object + 8).
struct cParticlesForceStep
{
    char           mPad00[0xa0];                    // +0x00 .. +0x9f
    float          mAccA0X;                         // +0xa0
    float          mAccA0Y;                         // +0xa4
    float          mAccA0Z;                         // +0xa8
    float          mAccAcX;                         // +0xac
    float          mAccAcY;                         // +0xb0
    float          mAccAcZ;                         // +0xb4
    Vector3        mVelocity;                       // +0xbc
    cSPTransformOps mXformA;                        // +0xc8
    cSPTransformOps mXformB;                        // +0x100
    char           mPad138[0x1e0 - 0x138];          // +0x138 .. +0x1df
    void*          mPtr1e0;                         // +0x1e0
    char           mPad1e4[0x1f8 - 0x1e4];          // +0x1e4 .. +0x1f7
    uint8_t        mFlag1f8;                        // +0x1f8

    void Step(const void* srcA, const void* srcB);  // 0x00f59370
};

extern "C" const float g_noDirection;               // 0x015b0c34

// @ 0x00f59370
void cParticlesForceStep::Step(const void* srcA, const void* srcB)
{
    mXformA.Assign(srcA);
    mXformB.Assign(srcB);
    if (mPtr1e0)
        ((cParticlesOwner*)((char*)this - 8))->Release(mPtr1e0);
    mFlag1f8 = 0;

    Vector3 prev = mVelocity;
    mVelocity = mXformA.mTranslation;

    if (mXformB.mFlags & 2)
    {
        float x = mVelocity.x;
        float y = mVelocity.y;
        float z = mVelocity.z;
        const float (&R)[3][3] = mXformB.mRotation;
        mVelocity.x = (R[1][0] * y + R[2][0] * z) + R[0][0] * x;
        mVelocity.y = (R[0][1] * x + R[1][1] * y) + R[2][1] * z;
        mVelocity.z = (R[0][2] * x + R[1][2] * y) + R[2][2] * z;
    }

    float s = mXformB.mScale;
    mVelocity.z = mVelocity.z * s;
    mVelocity.y = s * mVelocity.y;
    mVelocity.x = s * mVelocity.x;
    mVelocity.x = mXformB.mTranslation.x + mVelocity.x;
    mVelocity.y = mXformB.mTranslation.y + mVelocity.y;
    mVelocity.z = mXformB.mTranslation.z + mVelocity.z;

    float noDir = g_noDirection;
    if (mAccA0X == noDir)
        return;
    float dx = mVelocity.x - prev.x;
    float dy = mVelocity.y - prev.y;
    float dz = mVelocity.z - prev.z;
    if (mAccA0X == noDir || mAccA0X == -noDir)
        return;
    mAccA0X = mAccA0X + dx;
    mAccA0Y = dy + mAccA0Y;
    mAccA0Z = dz + mAccA0Z;
    mAccAcX = mAccAcX + dx;
    mAccAcY = dy + mAccAcY;
    mAccAcZ = dz + mAccAcZ;
}

// Two-component float range of the random height offset.
struct Vector2
{
    float x, y;
};

extern "C" float __cdecl RandomInRange(const Vector2& range);     // 0x004df2d0

// 00f59e40's view of the effect.
struct cParticlesForceEval
{
    char                 mPad00[0x24];              // +0x00 .. +0x23
    cParticlesDescription* mDesc;                   // +0x24
    char                 mPad28[0xd0 - 0x28];       // +0x28 .. +0xcf
    cSPTransformOps      mXformA;                   // +0xd0
    cSPTransformOps      mXformB;                   // +0x108
    char                 mPad140[0x18c - 0x140];    // +0x140 .. +0x18b
    float                mMinHeight;                // +0x18c
    float                mMaxHeight;                // +0x190
    char                 mPad194[0x1bc - 0x194];    // +0x194 .. +0x1bb
    IEffectMap*          mForceMap;                 // +0x1bc
    char                 mPad1c0[0x1c5 - 0x1c0];    // +0x1c0 .. +0x1c4
    bool                 mForceMapInWorldSpace;     // +0x1c5
    char                 mPad1c6[0x1d0 - 0x1c6];    // +0x1c6 .. +0x1cf
    float                mRangeMin;                 // +0x1d0
    char                 mPad1d4[0x1dc - 0x1d4];    // +0x1d4 .. +0x1db
    float                mRangeMax;                 // +0x1dc

    bool Evaluate(cParticle* particle);             // 0x00f59e40
};

// @ 0x00f59e40
bool cParticlesForceEval::Evaluate(cParticle* particle)
{
    Vector3 p(particle->mPosition.x, particle->mPosition.y, particle->mPosition.z);

    if (mForceMapInWorldSpace)
    {
        if (mXformA.mFlags & 2)
        {
            float x = p.x;
            float y = p.y;
            float z = p.z;
            const float (&R)[3][3] = mXformA.mRotation;
            p.x = (R[1][0] * y + R[2][0] * z) + R[0][0] * x;
            p.y = (R[0][1] * x + R[1][1] * y) + R[2][1] * z;
            p.z = (R[0][2] * x + R[1][2] * y) + R[2][2] * z;
        }
        float s = mXformA.mScale;
        Vector3 q(mXformA.mTranslation.x + s * p.x,
                  mXformA.mTranslation.y + s * p.y,
                  mXformA.mTranslation.z + s * p.z);
        if (mXformB.mFlags & 2)
        {
            float x = q.x;
            float y = q.y;
            float z = q.z;
            const float (&R)[3][3] = mXformB.mRotation;
            q.x = (R[1][0] * y + R[2][0] * z) + R[0][0] * x;
            q.y = (R[0][1] * x + R[1][1] * y) + R[2][1] * z;
            q.z = (R[0][2] * x + R[1][2] * y) + R[2][2] * z;
        }
        float s2 = mXformB.mScale;
        p.x = mXformB.mTranslation.x + s2 * q.x;
        p.y = mXformB.mTranslation.y + s2 * q.y;
        p.z = mXformB.mTranslation.z + s2 * q.z;
    }

    if (!mForceMap || !mForceMap->PointInMap(p))
        return false;

    float h = mForceMap->Height(p);
    p.z = h;
    uint32_t flags = mDesc->mFlags;
    if ((flags >> 6) & 1)
    {
        if (mMinHeight > h)
            return false;
        if (h > mMaxHeight)
            return false;
    }
    else if ((flags >> 7) & 1)
    {
        if (!(h > SP::sMathRandom.RandomDoubleUniform()))
            return false;
    }
    if ((mDesc->mFlags >> 5) & 1)
    {
        Vector2 range;
        range.x = mRangeMin;
        range.y = mRangeMax;
        p.z = h + RandomInRange(range);
    }
    if (mForceMapInWorldSpace)
    {
        mXformB.InverseTransformPoint(&p);
        mXformA.InverseTransformPoint(&p);
    }
    particle->mPosition.x = p.x;
    particle->mPosition.y = p.y;
    particle->mPosition.z = p.z;
    return true;
}

}} // namespace EA::Swarm

// ===========================================================================
// 00f5a1c0 -- EA::Allocator fixed-allocator free-list pop
// ===========================================================================
namespace EA { namespace Allocator {
struct FixedAllocatorBase
{
    bool AddCore(void* block, unsigned count);      // 0x00926650
};
}}

extern "C" void** g_pAllocFreeList;                                 // 0x016c9478
extern "C" EA::Allocator::FixedAllocatorBase g_allocatorCore;       // 0x016c9468

// @ 0x00f5a1c0
void** __cdecl FUN_00f5a1c0()
{
    void** node = g_pAllocFreeList;
    while (node == 0)
    {
        if (!g_allocatorCore.AddCore(0, 0))
            return 0;
        node = g_pAllocFreeList;
    }
    g_pAllocFreeList = (void**)*node;
    node[1] = 0;
    node[0] = 0;
    return node;
}
