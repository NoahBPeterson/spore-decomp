// Slice s00d98140 -- SP::CitizenTree::UpdateStream (0x00d98140, 3932 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Updates a citizen's "stream" effect (an arcing ribbon of 32 points between two planet
// surface positions). On first use it creates the two visual effects (0xc31f1a6c ribbon,
// 0xbc1d5221 end-point effect). Every 3 s it picks a new target (a random entry of the owner's
// point list, or owner position + offset), snaps it to the ground and rebuilds the 32 target
// points along a parabola; the displayed points ease toward the targets every frame, are fed to
// the ribbon (param 13, 96 floats) and the end effect is oriented along the last segment.
#include <math.h>
#include "types.h"

#define PV(n) virtual void pv##n();

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3& operator+=(const cSPVector3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    cSPVector3 Normalized() const
    {
        float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f);
        return cSPVector3(inv * x, y * inv, z * inv);
    }
};
inline cSPVector3 operator+(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline cSPVector3 operator*(const cSPVector3& a, float s) { return cSPVector3(a.x * s, a.y * s, a.z * s); }

struct cSPMatrix3 { float m[9]; };

// Transform (ModAPI layout): flags, count, offset, scale, rotation.
struct Transform {
    enum { kFlagScale = 1, kFlagRotation = 2, kFlagOffset = 4 };
    int16_t mnFlags;
    int16_t mnTransformCount;
    cSPVector3 mOffset;
    float mfScale;
    cSPMatrix3 mRotation;
    Transform();   // 0x00434040 (out-of-line /Od copy)
    struct InlineInit {};
    // The same default constructor, inlined from this TU (uses this TU's copies of the
    // zero vector / identity matrix statics).
    inline Transform(InlineInit);
    void SetOffset(const cSPVector3& v) { mOffset = v; mnFlags |= kFlagOffset; ++mnTransformCount; }
    void SetRotation(const cSPMatrix3& m) { mRotation = m; mnFlags |= kFlagRotation; ++mnTransformCount; }
};

extern cSPVector3 sZeroVector;      // 0x0169f28c
extern cSPMatrix3 sIdentityMatrix;  // 0x0169f268
inline Transform::Transform(InlineInit)
    : mnFlags(0), mnTransformCount(0), mOffset(sZeroVector), mfScale(1.0f), mRotation(sIdentityMatrix) {}

cSPMatrix3 RotationFromTo(const cSPVector3& from, const cSPVector3& to);   // 0x0069b1c0

namespace EA { namespace Random {
struct RandomLinearCongruential {
    uint32_t RandomUint32Uniform(uint32_t limit);   // 0x00a68fb0
};
}}
extern EA::Random::RandomLinearCongruential sMathRandom;   // 0x01601760

namespace SP {

class IVisualEffect {
public:
    PV(0)
    virtual int Release();                                   // +0x04
    virtual void Start(int hardStart);                       // +0x08
    PV(3) PV(4) PV(5)
    virtual void SetTransform(const Transform& t);           // +0x18
    PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
    virtual void SetParams(int id, const float* data, int count);   // +0x44
};

template <class T> struct AutoRefCount {
    T* mpObject;
    void reset()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
    }
    T* operator->() const { return mpObject; }
};

class IEffectsManager {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool CreateVisualEffect(uint32_t instanceID, uint32_t groupID, AutoRefCount<IVisualEffect>* dst);   // +0x2c
};
IEffectsManager* EffectsManager();   // 0x0067ddd0

class cPlanetModel {
public:
    cSPVector3 DirectionToSurfacePosition(const cSPVector3& dir);   // 0x00b815a0
};
cPlanetModel* PlanetModel();   // 0x00b3d350

class cSpatialObject {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const cSPVector3& GetPosition();   // +0x2c
};

class cModel {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
    virtual void GetTransform(Transform& out);   // +0x20
};

class cOffsetSource {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
    virtual cSPVector3 GetOffset();   // +0x20
};

struct StreamPoint {   // 0x38-byte entry of the owner's point list
    uint32_t pad0;
    cSPVector3 mPosition;   // +0x4
    uint32_t pad10[10];
};

class cOwnerBase0 { public: virtual void ob0(); uint32_t pad4[12]; };   // 0x34 bytes
class cCitizenOwner : public cOwnerBase0, public cSpatialObject {
public:
    uint32_t pad38[58];         // +0x38
    cOffsetSource mOffsetSource; // +0x120
    uint32_t pad124[121];       // +0x124
    StreamPoint* mPointsBegin;  // +0x308
    StreamPoint* mPointsEnd;    // +0x30c
};

class cGroundSnapper {
public:
    bool SnapToGround(cSpatialObject* obj, const cSPVector3& from, const cSPVector3& to, cSPVector3& out);   // 0x00b35bf0
};
cGroundSnapper* GroundSnapper();   // 0x00b3d240

struct Vector3Vector {   // eastl::vector<cSPVector3>
    cSPVector3* mpBegin;
    cSPVector3* mpEnd;
    cSPVector3* mpCapacity;
    uint32_t mAllocator;
    void resize(uint32_t n);   // 0x00473810
    cSPVector3& operator[](int i) { return mpBegin[i]; }
};

struct CitizenStream {
    uint32_t pad0[3];
    cCitizenOwner* mpOwner;                 // +0x0c
    cModel* mpModel;                        // +0x10
    AutoRefCount<IVisualEffect> mpStream;   // +0x14
    AutoRefCount<IVisualEffect> mpEnd;      // +0x18
    uint32_t pad1c[3];
    Vector3Vector mPoints;                  // +0x28
    uint32_t pad38;
    Vector3Vector mTargets;                 // +0x3c
    uint32_t pad4c;
    float mTimer;                           // +0x50
    cSPVector3 mTarget;                     // +0x54
    cSPVector3 mOrigin;                     // +0x60
};

namespace CitizenTree {

enum { kNumPoints = 32 };

void UpdateStream(CitizenStream* s, float dt)
{
    bool created = false;
    if (s->mpStream.mpObject == 0) {
        if (s->mpModel != 0) {
            IEffectsManager* mgr = EffectsManager();
            s->mpStream.reset();
            if (mgr->CreateVisualEffect(0xc31f1a6c, 0, &s->mpStream)) {
                Transform xf;
                s->mpModel->GetTransform(xf);
                s->mpStream->SetTransform(xf);
                s->mpStream->Start(0);
                s->mOrigin = xf.mOffset;
                s->mPoints.resize(kNumPoints);
                s->mTargets.resize(kNumPoints);
                created = true;
            }
            IEffectsManager* mgr2 = EffectsManager();
            s->mpEnd.reset();
            if (mgr2->CreateVisualEffect(0xbc1d5221, 0, &s->mpEnd))
                s->mpEnd->Start(0);
        }
        if (s->mpStream.mpObject == 0)
            return;
    }

    s->mTimer -= dt;
    if (s->mTimer <= 0.0f) {
        cCitizenOwner* owner = s->mpOwner;
        if (owner->mPointsBegin == owner->mPointsEnd) {
            s->mTarget = owner->GetPosition() + owner->mOffsetSource.GetOffset();
        } else {
            uint32_t idx = sMathRandom.RandomUint32Uniform(owner->mPointsEnd - owner->mPointsBegin);
            s->mTarget = owner->mPointsBegin[idx].mPosition;
        }
        GroundSnapper()->SnapToGround(s->mpOwner, s->mOrigin, s->mTarget, s->mTarget);

        cSPVector3 from = PlanetModel()->DirectionToSurfacePosition(s->mOrigin);
        cSPVector3 to = PlanetModel()->DirectionToSurfacePosition(s->mTarget);
        cSPVector3 delta = to - from;
        float len = delta.Length();
        float halfSpan = len * 0.9f;
        float height = (s->mTarget - to).Length() * 1.1f;
        cSPVector3 dir = delta.Normalized();
        float step = len * 0.03125f;
        cSPVector3 mid = from + dir * halfSpan;
        float t = -halfSpan;
        cSPVector3 up = from.Normalized();
        float r = sqrtf(height) / halfSpan;
        float k = -(r * r);
        for (int i = 0; i < kNumPoints; ++i) {
            float h = t * t * k + height;
            s->mTargets[i] = (dir * t + mid) + up * h;
            if (created)
                s->mPoints[i] = s->mTargets[i];
            t += step;
        }
        s->mTimer = 3.0f;
    }

    for (int i = 0; i < kNumPoints; ++i) {
        cSPVector3& cur = s->mPoints[i];
        const cSPVector3& tgt = s->mTargets[i];
        double dx = (double)tgt.x - cur.x;
        double dy = (double)tgt.y - cur.y;
        double dz = (double)tgt.z - cur.z;
        cSPVector3 d((float)dx, (float)dy, (float)dz);
        float dist = (float)sqrt(dx * dx + dy * dy + dz * dz);
        if (dist > 0.0f) {
            float maxMove = ((float)i * 0.1f) * (dt * 2.0f);
            if (maxMove >= dist) {
                cur = tgt;
            } else {
                float f = maxMove / dist;
                cur += d * f;
            }
        }
    }
    s->mpStream->SetParams(13, &s->mPoints.mpBegin->x, kNumPoints * 3);

    if (s->mpEnd.mpObject != 0) {
        Transform xf2((Transform::InlineInit()));
        const cSPVector3& last = s->mPoints[kNumPoints - 1];
        xf2.SetOffset(last);
        cSPVector3 fwd = (last - s->mPoints[kNumPoints - 2]).Normalized();
        cSPVector3 upDir = last.Normalized();
        xf2.SetRotation(RotationFromTo(upDir, fwd));
        s->mpEnd->SetTransform(xf2);
    }
}

}  // namespace CitizenTree
}  // namespace SP
