// Slice s00caded0: Simulator::cFlyingLocomotion flight helpers.
//   0x00CADED0  Simulator::cFlyingLocomotion::cFlyingLocomotion
//   0x00CADF50  TurnTowards              (steer `from` towards `to`, rate-limited by turnRate*dt)
//   0x00CAE0E0  ProjectToFlightSurface   (drop `pos` onto the flight surface around a creature flyer)
//
// Flags region: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (float math through x87: fsqrt / fmodf->_CIfmod).
//
// The ctor is the standard MSVC pattern for a class with a polymorphic primary base and one
// polymorphic secondary base (EA::RefCountVTemplate<int> at +0x08): the inlined RefCount base
// ctor stamps its own vtable at +0x08 and zeroes the refcount at +0x0c, then the derived ctor
// stamps the primary vtable at +0x00 and its own vtable for the RefCount sub-object at +0x08,
// and finally the member-init stores run.  (MSVC elides the primary base's own vptr store; the
// primary base's +0x04 member is left uninitialised.)  Modelled as two real polymorphic base
// classes -- explicit vfptr members instead get their first store dead-store-eliminated.
#include <math.h>

typedef unsigned int uint32_t;

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float Dot(const Vector3& b) const { return x * b.x + y * b.y + z * b.z; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    Vector3 Cross(const Vector3& b) const
    {
        return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
    Vector3 Normalized() const
    {
        float inv = 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f);
        return Vector3(x * inv, y * inv, z * inv);
    }
};
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }

// ---- globals ----
extern Vector3 kZeroVector;         // 0x0169A37C (0, 0, 0)
extern float kPI;                   // 0x0157D2E8
extern float kTwoPI;                // 0x0169A3F8

// ---- callees ----
float SignedAngle(const Vector3& from, const Vector3& to, const Vector3& axis);            // 0x006994A0
Vector3 RotateTowards(const Vector3& from, const Vector3& to, float t);                     // 0x00B0FD00

struct cLocomotiveObject {
    uint32_t pad00[0x34 / 4];
};
struct cCreatureFlyer {
    uint32_t pad00[0x34 / 4];
    cLocomotiveObject mLocomotion;                    // +0x34
    float GetGroundRadius(const Vector3& pos);                                  // 0x00C9FFD0
};
bool SweepTest(cLocomotiveObject* pObject, const Vector3& from, const Vector3& to,
               Vector3* pHit, int flags);                                       // 0x00B53BC0

namespace Simulator {

// Polymorphic primary base: it owns the vfptr slot the derived class shares.
class cFlyLocoPrimaryBase {
public:
    cFlyLocoPrimaryBase() {}
    virtual ~cFlyLocoPrimaryBase();
    int mUnk04;                                    // +0x04  (left uninitialised by the ctor)
};

// Polymorphic refcount base: MSVC gives it a vtable (deleting dtor at slot 0) and one int.
class RefCountVTemplateInt {                       // EA::RefCountVTemplate<int>
public:
    RefCountVTemplateInt() : mRefCount(0) {}
    virtual ~RefCountVTemplateInt();
    int mRefCount;                                 // +0x0c
};

class cFlyingLocomotion : public cFlyLocoPrimaryBase, public RefCountVTemplateInt {
public:
    float   mUnk10;        // +0x10
    Vector3 mUnk14;        // +0x14
    Vector3 mUnk20;        // +0x20
    float   mUnk2c;        // +0x2c  (left uninitialised by the ctor)
    int     mUnk30;        // +0x30
    bool    mbAligned;     // +0x34
    float   mLift;         // +0x38

    cFlyingLocomotion();
    virtual void Update();
};

} // namespace Simulator

// @ 0x00CADED0
Simulator::cFlyingLocomotion::cFlyingLocomotion()
    : mUnk10(0.0f)
    , mUnk14(kZeroVector)
    , mUnk20(kZeroVector)
    , mUnk30(0)
    , mbAligned(false)
    , mLift(0.0f)
{
}

// @ 0x00CADF50
Vector3 TurnTowards(const Vector3& from, const Vector3& to, float turnRate, float dt)
{
    Vector3 result = to;
    Vector3 axis = from.Cross(to);
    axis = axis.Normalized();
    float angle = fmodf(SignedAngle(from, to, axis), kTwoPI);
    if (angle > kPI)
        angle -= kTwoPI;
    else if (angle < -kPI)
        angle += kTwoPI;
    float mag = fabsf(angle);
    float limit = turnRate * dt;
    if (limit < mag) {
        axis = RotateTowards(from, to, limit / mag);
        result = axis;
    }
    return result;
}

// @ 0x00CAE0E0
Vector3 ProjectToFlightSurface(const Vector3& pos, cCreatureFlyer* pFlyer)
{
    float radius = pFlyer->GetGroundRadius(pos);
    Vector3 dir = pos.Normalized();
    Vector3 from = dir * (radius + 128.0f);
    Vector3 to = dir * radius;
    Vector3 hit;
    if (SweepTest(pFlyer ? &pFlyer->mLocomotion : 0, from, to, &hit, 1)) {
        float dist = hit.Length() + 5.0f;
        return dir * dist;
    }
    return to;
}