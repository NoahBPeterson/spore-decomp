// Slice s00caf650: Simulator::cFlyingLocomotion::ApplyFacing (0x00CAF650, 2105 bytes).
// Flags region: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE math, x87 sqrt/fmod, __asm Clamp helper).
//
// Called at the end of cFlyingLocomotion::Update with the final steering direction. It banks the flyer (a signed
// bank amount, mBank, that follows how far the desired direction lies to the side of the facing), builds the
// orientation that looks along 'dir' with the "up" vector tilted by the bank, limits the yaw change per frame
// (pi/4 per second) and writes the resulting quaternion back to the creature's locomotive object.
#include "types.h"
#include <math.h>

#pragma pack(push, 4)

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float Dot(const Vector3& b) const { return x * b.x + y * b.y + z * b.z; }
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
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }

struct Quaternion { float x, y, z, w; };
struct Matrix33 { float m[9]; };      // three rows of three floats

// ---- globals ----
extern float kRotateTowardsT;       // 0x0157D2D4 (0.5)
extern float kBankSideScale;        // 0x0157D2D8 (0.3)
extern float kMaxTurnRate;          // 0x0157D2E4 (pi/4 per second)
extern float kPI;                   // 0x0157D2E8
extern float kTwoPI;                // 0x0169A3F8
extern Vector3 kLocalAxis;          // 0x0169A3EC (copy of 0x0157D2EC), rotated by the orientation to get the lateral axis

// ---- callees (cdecl) ----
float SignedAngle(const Vector3& from, const Vector3& to, const Vector3& axis);          // 0x006994A0
Vector3 RotateTowards(const Vector3& from, const Vector3& to, float t);                  // 0x00B0FD00
Vector3 RotateByQuat(const Vector3& v, const Quaternion& q);                             // 0x0059AED0 (out pointer first)
namespace rw { namespace math { namespace fpu {
Quaternion QuaternionFromMatrix33(const Matrix33& m, float tolerance);                   // 0x00472B80 (out pointer first)
} } }

struct cLocomotiveObject {
    PV8 PV2 PV
    virtual const Vector3* GetPosition();                 // +0x2c
    virtual const Quaternion* GetOrientation();           // +0x30
    PV2
    virtual void SetOrientation(const Quaternion& q);     // +0x3c
    PV4 PV2 PV
    virtual Vector3 GetFacing();                          // +0x5c
};

struct cCreatureFlyer {
    uint32_t pad00[0x34 / 4];
    cLocomotiveObject mLocomotion;                        // +0x34
    uint32_t pad38[(0xF0 - 0x38) / 4];
    int mField_F0;                                        // +0xF0 (> 0 selects the softened side direction)
};

struct cFlyingLocomotion {
    void* vtable;
    uint32_t pad04[3];
    float mBank;                                          // +0x10

    void ApplyFacing(cCreatureFlyer* pFlyer, const Vector3& dir, float dt);             // 0x00CAF650
};

// @ 0x00CAF650
void cFlyingLocomotion::ApplyFacing(cCreatureFlyer* pFlyer, const Vector3& dir, float dt)
{
    bool soften = pFlyer->mField_F0 > 0;
    cLocomotiveObject* loco = &pFlyer->mLocomotion;
    Vector3 facing = loco->GetFacing();
    Vector3 up = loco->GetPosition()->Normalized();
    Vector3 lateral = RotateByQuat(kLocalAxis, *loco->GetOrientation());
    Vector3 side = facing.Cross(up);

    Vector3 tangent = (dir - up * dir.Dot(up)).Normalized();
    float sideness = tangent.Dot(side);
    Vector3 d = dir;
    if (soften)
        d = RotateTowards(tangent, dir, kRotateTowardsT);

    float bank;
    if (sideness > 0.01f)
        bank = mBank + dt;
    else if (sideness < -0.01f)
        bank = mBank - dt;
    else {
        bank = mBank;
        if (bank > dt)
            bank -= dt;
        else if (bank < -dt)
            bank += dt;
        else
            bank = 0.0f;
    }
    mBank = bank;
    bank = Clamp(bank, -0.3f, 0.3f);
    mBank = bank;

    float scale = soften ? kBankSideScale : 1.0f;
    Vector3 v;
    if (bank > 0.2f)
        v = (side - up * scale).Normalized();
    else if (bank < -0.2f)
        v = (side + up * scale).Normalized();
    else
        v = side;

    float angle = fmodf(SignedAngle(v, lateral, facing), kTwoPI);
    if (angle > kPI)
        angle -= kTwoPI;
    else if (angle < -kPI)
        angle += kTwoPI;
    float maxTurn = kMaxTurnRate * dt;
    if (fabsf(angle) > maxTurn)
        v = RotateTowards(lateral, v, maxTurn / fabsf(angle));

    Vector3 x = v.Cross(d).Normalized();
    Vector3 y = d.Cross(x).Normalized();
    Matrix33 m;
    m.m[0] = y.x; m.m[1] = y.y; m.m[2] = y.z;
    m.m[3] = d.x; m.m[4] = d.y; m.m[5] = d.z;
    m.m[6] = x.x; m.m[7] = x.y; m.m[8] = x.z;
    Quaternion q = rw::math::fpu::QuaternionFromMatrix33(m, 0.0f);
    float inv = 1.0f / sqrtf(q.x * q.x + q.w * q.w + q.z * q.z + q.y * q.y);
    Quaternion qn;
    qn.x = q.x * inv; qn.y = q.y * inv; qn.z = q.z * inv; qn.w = q.w * inv;
    loco->SetOrientation(qn);
}

#pragma pack(pop)
