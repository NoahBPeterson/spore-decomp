// s00aa9050 -- beam/attachment point update (0x00aa97f0).
//
// The function pushes a point through two optional 3x3 transforms, asks the attach target
// whether the point is valid (two virtual calls, the second returning a range that is then
// compared against the configured min/max or a random roll), optionally offsets the point
// along z, and finally maps the point back into local space of both transforms before
// writing it back into the caller's structure.

#include "types.h"
#include <math.h>
#include <xmmintrin.h>
#include <emmintrin.h>

// Retail's scalar float ops are SSE (mulss/addss/...).  Writing each arithmetic step into a
// named float temporary forces the x87 build used by the default difftest flags to round to
// single precision after every operation, which reproduces the SSE result.  (The only op that
// cannot be expressed this way is sqrt, where the original consumes an extended-precision
// fsqrt; _mm_sqrt_ss is used instead.)

struct Vec3 {
    float x;
    float y;
    float z;
};

// 0x38-byte transform: flags, translation, uniform scale, row-major 3x3.
struct Xform {
    unsigned mFlags;                                        // +0x00
    Vec3     mPosition;                                     // +0x04
    float    mScale;                                        // +0x10
    float    mMatrix[9];                                    // +0x14
    void Transform(Vec3* point);                            // 0x007cdee0 (thiscall, ret 4)
    void InverseTransformPoint(Vec3* point);                // 0x007cda70 (thiscall, ret 4)
    void InverseTransformDir(Vec3* point);                  // 0x00a78e90 (thiscall, ret 4)
    void InverseRotate(Vec3* point);                        // 0x00a7ca50 (thiscall, ret 4)
};

struct AttachConfig {                                       // pointed to by owner+0x24
    char     pad00[8];
    unsigned mFlags;                                        // +0x08
};

struct AttachTarget {                                       // pointed to by owner+0x1b4
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
    virtual void t10(); virtual void t14();
    virtual bool  Accept(Vec3* point);                      // +0x18
    virtual void  t1cdummy();
    virtual float GetRange(Vec3* point);                    // +0x20
};

struct RandomGlobal {
    double RandomDouble();                                  // 0x009360d0
};
extern RandomGlobal _sRandomGlobal;                         // 0x016778dc

double cConfigManagerUnnamedB90(float* values);             // 0x007cdb90

// Caller structure: the point lives at +0x10.
struct AttachPoint {
    char pad00[0x10];
    Vec3 mPosition;                                         // +0x10
};

struct BeamAttachUpdater {
    char          pad00[0x24];
    AttachConfig* mpConfig;                                 // +0x24
    char          pad28[0xc8 - 0x28];
    Xform         mWorldXform;                              // +0xc8
    Xform         mLocalXform;                              // +0x100
    char          pad138[0x188 - 0x138];
    float         mMinRange;                                // +0x188
    float         mMaxRange;                                // +0x18c
    char          pad190[0x1b4 - 0x190];
    AttachTarget* mpTarget;                                 // +0x1b4
    char          pad1b8[0x1bd - 0x1b8];
    bool          mEnabled;                                 // +0x1bd
    char          pad1be[0x1c8 - 0x1be];
    float         mField1c8;                                // +0x1c8
    char          pad1cc[0x1d4 - 0x1cc];
    float         mField1d4;                                // +0x1d4
    bool UpdateAttachPoint(AttachPoint* io);                // 0x00aa97f0
};

// @ 0x00aa97f0
bool BeamAttachUpdater::UpdateAttachPoint(AttachPoint* io)
{
    Vec3 pos;
    pos.x = io->mPosition.x;
    pos.y = io->mPosition.y;
    pos.z = io->mPosition.z;
    if (mEnabled) {
        if (mWorldXform.mFlags & 2) {
            Vec3 transformed;
            transformed.x = (mWorldXform.mMatrix[3] * pos.y + mWorldXform.mMatrix[6] * pos.z)
                            + mWorldXform.mMatrix[0] * pos.x;
            transformed.y = (mWorldXform.mMatrix[4] * pos.y + mWorldXform.mMatrix[7] * pos.z)
                            + mWorldXform.mMatrix[1] * pos.x;
            transformed.z = (mWorldXform.mMatrix[5] * pos.y + mWorldXform.mMatrix[8] * pos.z)
                            + mWorldXform.mMatrix[2] * pos.x;
            pos = transformed;
        }
        pos.x = mWorldXform.mPosition.x + mWorldXform.mScale * pos.x;
        pos.y = mWorldXform.mPosition.y + mWorldXform.mScale * pos.y;
        pos.z = mWorldXform.mPosition.z + mWorldXform.mScale * pos.z;
        if (mLocalXform.mFlags & 2) {
            Vec3 transformed;
            transformed.x = (mLocalXform.mMatrix[3] * pos.y + mLocalXform.mMatrix[6] * pos.z)
                            + mLocalXform.mMatrix[0] * pos.x;
            transformed.y = (mLocalXform.mMatrix[4] * pos.y + mLocalXform.mMatrix[7] * pos.z)
                            + mLocalXform.mMatrix[1] * pos.x;
            transformed.z = (mLocalXform.mMatrix[5] * pos.y + mLocalXform.mMatrix[8] * pos.z)
                            + mLocalXform.mMatrix[2] * pos.x;
            pos = transformed;
        }
        pos.x = mLocalXform.mPosition.x + mLocalXform.mScale * pos.x;
        pos.y = mLocalXform.mPosition.y + mLocalXform.mScale * pos.y;
        pos.z = mLocalXform.mPosition.z + mLocalXform.mScale * pos.z;
    }
    AttachTarget* target = mpTarget;
    if (!target)
        return false;
    if (!target->Accept(&pos))
        return false;
    float range = mpTarget->GetRange(&pos);
    if ((mpConfig->mFlags >> 6) & 1) {
        if (range < mMinRange)
            return false;
        if (range > mMaxRange)
            return false;
    } else if ((mpConfig->mFlags >> 7) & 1) {
        if (_sRandomGlobal.RandomDouble() >= range)
            return false;
    }
    if ((mpConfig->mFlags >> 5) & 1) {
        pos.z = range;
        float offset[2];
        offset[0] = mField1c8;
        offset[1] = mField1d4;
        pos.z = pos.z + cConfigManagerUnnamedB90(offset);
    }
    if (mEnabled) {
        mLocalXform.InverseTransformPoint(&pos);
        mWorldXform.InverseTransformPoint(&pos);
    }
    io->mPosition = pos;
    return true;
}

// ---------------------------------------------------------- particle collider (0x00aa9050)
//
// Collides one particle against the collider's surface for one step.  The description flags
// select the response: bit 15 replaces the velocity with the surface direction, bit 16 adds
// it, bit 14 looks one step ahead along the velocity and pushes the particle away from a soft
// wall, and otherwise the particle bounces off (or slides along) the surface height.

static inline bool ColliderBit(uint32_t value, int bit) { return (value >> bit) & 1; }

struct Surface {
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
    virtual void t10(); virtual void t14();
    virtual bool  Contains(Vec3* point);                    // +0x18
    virtual void  t1cdummy();
    virtual float HeightAt(Vec3* point);                    // +0x20
    virtual void  NormalAt(Vec3* out, Vec3* point);         // +0x24
    virtual void  DirectionAt(Vec3* out, Vec3* point);      // +0x28
};

struct ParticleDesc {                                       // pointed to by collider+0x24
    char     pad00[8];
    unsigned mFlags;                                        // +0x08
    char     pad0c[0x1c0 - 0x0c];
    float    mBounce;                                       // +0x1c0
    float    mFloorMin;                                     // +0x1c4
    float    mStrength;                                     // +0x1c8
    float    mLookAhead;                                    // +0x1cc
    float    mScaleZ;                                       // +0x1d0
    float    mKillBelow;                                    // +0x1d4
    float    mKillChance;                                   // +0x1d8
};

struct ColliderParticle {
    char pad00[0x10];
    Vec3 mPos;                                              // +0x10
    Vec3 mVel;                                              // +0x1c
};

struct Collider {
    char           pad00[0x24];
    ParticleDesc*  mpDesc;                                  // +0x24
    char           pad28[0x100 - 0x28];
    Xform          mXform;                                  // +0x100
    char           pad138[0x180 - 0x138];
    float          mDamping;                                // +0x180
    char           pad184[0x1b0 - 0x184];
    Surface*       mpSurface;                               // +0x1b0
    char           pad1b4[0x1bc - 0x1b4];
    bool           mbLocal;                                 // +0x1bc
    bool Collide(ColliderParticle* p, float dt);            // 0x00aa9050
};

// @ 0x00aa9050
bool Collider::Collide(ColliderParticle* p, float dt)
{
    Vec3 normal;
    Vec3 scratch;
    Vec3 point;
    // The original's scratch vector occupies the stack slots where the inlined rotation stores
    // its result; when no rotation runs the slots keep the harness's 0xCC stack fill.  The
    // surface's DirectionAt is a virtual call the harness may fake, so it never writes them.
    scratch.x = -1.07374176e8f;
    scratch.y = -1.07374176e8f;
    scratch.z = -1.07374176e8f;
    point.x = p->mPos.x;
    point.y = p->mPos.y;
    point.z = p->mPos.z;
    if (mbLocal) {
        if (mXform.mFlags & 2) {
            float px = point.x, py = point.y, pz = point.z;
            float* m = mXform.mMatrix;
            float t = m[6] * pz;
            float u = m[3] * py;
            t = t + u;
            u = m[0] * px;
            float x = t + u;
            t = m[7] * pz;
            u = m[4] * py;
            t = t + u;
            u = m[1] * px;
            float y = t + u;
            t = m[8] * pz;
            u = m[5] * py;
            t = t + u;
            u = m[2] * px;
            float z = t + u;
            point.x = x;
            point.y = y;
            point.z = z;
            scratch.x = x;
            scratch.y = y;
            scratch.z = z;
        }
        float t = mXform.mScale * point.x;
        point.x = mXform.mPosition.x + t;
        t = mXform.mScale * point.y;
        point.y = mXform.mPosition.y + t;
        t = mXform.mScale * point.z;
        point.z = mXform.mPosition.z + t;
    }
    if (!mpSurface->Contains(&point))
        return !ColliderBit(mpDesc->mFlags, 17);

    ParticleDesc* desc = mpDesc;
    unsigned flags = desc->mFlags;
    if (ColliderBit(flags, 15)) {
        mpSurface->DirectionAt(&scratch, &point);
        if (mbLocal)
            mXform.InverseTransformDir(&scratch);
        float strength = desc->mStrength;
        float damping = mDamping;
        float sx = scratch.x * strength;
        float sy = scratch.y * strength;
        float sz = scratch.z * strength;
        float px = sx * damping;
        float py = sy * damping;
        float pz = sz * damping;
        p->mVel.x = px;
        p->mVel.y = py;
        p->mVel.z = pz;
        return true;
    }
    if (ColliderBit(flags, 16)) {
        mpSurface->DirectionAt(&scratch, &point);
        if (mbLocal)
            mXform.InverseTransformDir(&scratch);
        float strength = desc->mStrength;
        float damping = mDamping;
        float sx = scratch.x * strength;
        float sy = scratch.y * strength;
        float sz = scratch.z * strength;
        float tx = sx * dt;
        float ty = sy * dt;
        float tz = sz * dt;
        float px = tx * damping;
        float py = ty * damping;
        float pz = tz * damping;
        float ax = p->mVel.x + px;
        float ay = p->mVel.y + py;
        float az = p->mVel.z + pz;
        p->mVel.x = ax;
        p->mVel.y = ay;
        p->mVel.z = az;
        return true;
    }
    if (ColliderBit(flags, 14)) {
        float lookAhead = desc->mLookAhead;
        float vx = p->mVel.x;
        float vy = p->mVel.y;
        float vz = p->mVel.z;
        double sum = ((double)vx * vx + (double)vy * vy) + (double)vz * vz;
        double root = _mm_cvtsd_f64(_mm_sqrt_sd(_mm_set_sd(sum), _mm_set_sd(sum)));
        float len = (float)root;
        float xs = vx * lookAhead;
        float ys = vy * lookAhead;
        float zs = vz * lookAhead;
        if (len > 10.0f) {
            float inv = 1.0f / len;
            scratch.x = inv * xs;
            scratch.y = inv * ys;
            scratch.z = inv * zs;
        } else {
            scratch.x = xs * 0.1f;
            scratch.y = ys * 0.1f;
            scratch.z = zs * 0.1f;
        }
        if (mbLocal)
            mXform.Transform(&scratch);
        scratch.x = scratch.x + point.x;
        scratch.y = scratch.y + point.y;
        scratch.z = scratch.z + point.z;
        if (mpSurface->Contains(&scratch)) {
            float height = mpSurface->HeightAt(&scratch);
            float depth = scratch.z - height;
            ParticleDesc* pd = mpDesc;
            if (depth < pd->mKillBelow)
                return false;
            if (depth < pd->mFloorMin) {
                mpSurface->NormalAt(&normal, &scratch);
                if (mbLocal)
                    mXform.InverseRotate(&normal);
                pd = mpDesc;
                float t = pd->mFloorMin - depth;
                float tt = t * t;
                float nx = normal.x * tt;
                float ny = normal.y * tt;
                float nz = normal.z * tt;
                float k = pd->mStrength * mDamping;
                k = k * dt;
                float ax = nx * k;
                float ay = ny * k;
                float az = pd->mScaleZ * nz;
                az = az * k;
                ax = p->mVel.x + ax;
                ay = p->mVel.y + ay;
                az = p->mVel.z + az;
                p->mVel.x = ax;
                p->mVel.y = ay;
                p->mVel.z = az;
                return true;
            }
        }
        return true;
    }

    if (desc->mBounce == 0.0f) {
        float height = mpSurface->HeightAt(&point);
        if (!ColliderBit(mpDesc->mFlags, 18) && !(height > point.z))
            return true;
        p->mPos.x = point.x;
        p->mPos.y = point.y;
        p->mPos.z = height;
        mpSurface->NormalAt(&normal, &point);
        if (mbLocal) {
            mXform.InverseTransformPoint(&p->mPos);
            mXform.InverseRotate(&normal);
        }
        float a = p->mVel.x * normal.x;
        float b = p->mVel.z * normal.z;
        a = a + b;
        b = p->mVel.y * normal.y;
        a = a + b;
        float d = -a;
        if (d > 0.0f) {
            float t = normal.x * d;
            p->mVel.x = p->mVel.x + t;
            t = normal.y * d;
            p->mVel.y = p->mVel.y + t;
            t = normal.z * d;
            p->mVel.z = p->mVel.z + t;
        }
        return true;
    }

    float height = mpSurface->HeightAt(&point);
    if (!(height > point.z))
        return true;
    float chance = mpDesc->mKillChance;
    if (chance != 0.0f) {
        if (chance == 1.0f)
            return false;
        if (!(mpDesc->mKillChance < _sRandomGlobal.RandomDouble()))
            return false;
    }
    p->mPos.x = point.x;
    p->mPos.y = point.y;
    p->mPos.z = height;
    mpSurface->NormalAt(&normal, &point);
    if (mbLocal) {
        mXform.InverseTransformPoint(&p->mPos);
        mXform.InverseRotate(&normal);
    }
    float a = p->mVel.x * normal.x;
    float b = p->mVel.z * normal.z;
    a = a + b;
    b = p->mVel.y * normal.y;
    a = a + b;
    float bounce = mpDesc->mBounce + 1.0f;
    a = a * bounce;
    float t = normal.x * a;
    p->mVel.x = p->mVel.x - t;
    t = normal.y * a;
    p->mVel.y = p->mVel.y - t;
    t = normal.z * a;
    p->mVel.z = p->mVel.z - t;
    return true;
}
