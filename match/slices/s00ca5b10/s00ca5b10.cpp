// Slice s00ca5b10 -- cPathLocomotion::Turn (0x00ca5b10, 2843 bytes).
//
// Turns a path-following creature in place: builds the owner's local frame (forward/right/up
// from its facing and its position on the planet), measures the current pitch, roll and yaw of
// that frame, evaluates the path 16 units ahead of the current parameter to get the desired
// heading, steps pitch and roll back toward zero and yaw toward the desired heading at bounded
// rates, and applies the three axis-angle rotations to the owner's orientation.
// The `dir` argument is not read.
//
// Sibling of cPathLocomotion::Steer (slice s00ca4f90); class layout and callee names follow
// slices s00ca4f90 / s00ca8710 (cPathLocomotion::Update calls Turn(dir, dt)).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
    Vector3 Cross(const Vector3& b) const
    {
        return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
    float Dot(const Vector3& b) const { return x * b.x + y * b.y + z * b.z; }
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
};
inline Vector3 operator*(float s, const Vector3& v) { return Vector3(s * v.x, s * v.y, s * v.z); }

struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    Quaternion(const Quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}

    Quaternion operator*(const Quaternion& b) const
    {
        Vector3 av(x, y, z);
        Vector3 bv(b.x, b.y, b.z);
        Vector3 v = w * bv + b.w * av + av.Cross(bv);
        return Quaternion(v.x, v.y, v.z, w * b.w - av.Dot(bv));
    }
    __forceinline Quaternion& operator*=(const Quaternion& b)
    {
        Quaternion r = *this * b;
        x = r.x; y = r.y; z = r.z; w = r.w;
        return *this;
    }
    Quaternion Normalized() const
    {
        float inv = 1.0f / sqrtf(w * w + z * z + y * y + x * x);
        return Quaternion(x * inv, y * inv, z * inv, w * inv);
    }
};

// Rotation of `angle` radians about the unit vector `axis`.
inline Quaternion AxisAngle(const Vector3& axis, float angle)
{
    float h = angle * 0.5f;
    float s = sinf(h);
    float c = cosf(h);
    return Quaternion(axis.x * s, axis.y * s, axis.z * s, c);
}

// ---- callees ----
Vector3 RotateByQuaternion(const Vector3& v, const Quaternion& q);                    // 0x0059aed0
float SignedAngleNormalized(const Vector3& a, const Vector3& b, const Vector3& axis);  // 0x0069b760
float AngleStepToward(float a, float b, float maxStep);                               // 0x0069b840

extern const float kPi;          // 0x0157c728
extern const float kTwoPi;       // 0x0157c710
extern const float kPiB;         // 0x01474998

// Module statics (dynamic-initialized).
extern float gPitchRate;           // 0x0169a278
extern float gRollRate;          // 0x0169a27c
extern float gTwoPi;             // 0x0169a280
extern const Vector3 kAxisRoll;  // 0x0169a28c
extern const Vector3 kAxisPitch;   // 0x0169a298 (also the reference heading)
extern const Vector3 kAxisTurn; // 0x0169a2a4

struct ILocomotion {
    PV8 PV2 PV
    virtual const Vector3& GetPosition();              // +0x2c
    virtual const Quaternion& GetOrientation();        // +0x30
    PV2
    virtual void SetOrientation(const Quaternion& q);  // +0x3c
    PV4 PV2 PV
    virtual Vector3 GetFacing();                       // +0x5c
};

struct cLocomotionOwner {
    uint32_t pad00[0xd];
    ILocomotion mLocomotion;                         // +0x34
};

struct cPathLocomotion {
    uint32_t vtbl;
    uint32_t pad04[3];
    cLocomotionOwner* mpOwner;                       // +0x10
    uint32_t pad14[3];
    uint32_t mPath[0xe];                             // +0x20
    uint32_t pad58[0x1e];
    float mT;                                        // +0xd0

    void Evaluate(void* path, float t, Vector3* pos, Vector3* dir);   // 0x00ca1dc0
    void Turn(Vector3 dir, float dt);
};

// fmod into (-pi, pi] using the module's 2*pi.
static inline float WrapAngleMod(float a)
{
    float x = (float)fmod((double)a, (double)gTwoPi);
    if (x > kPi)
        return x - gTwoPi;
    if (x < -kPi)
        return x + gTwoPi;
    return x;
}

// fmod into [-pi, pi).
static inline float WrapAngle(float x)
{
    float r = (float)fmod((double)x, (double)kTwoPi);
    if (kPiB <= r)
        return r - kTwoPi;
    return r;
}

static inline Vector3 RejectFrom(const Vector3& v, const Vector3& n)
{
    float d = v.Dot(n);
    return Vector3(v.x - d * n.x, v.y - n.y * d, v.z - n.z * d);
}

// @ 0x00ca5b10
void cPathLocomotion::Turn(Vector3 dir, float dt)
{
    static float sTurnRate = gTwoPi * 2.0f;   // 0x01699ac0 (guard 0x01699ac4)

    Vector3 facing = mpOwner->mLocomotion.GetFacing();
    const Vector3& pos = mpOwner->mLocomotion.GetPosition();
    float inv = 1.0f / sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + 1e-8f);
    Vector3 up(pos.x * inv, inv * pos.y, inv * pos.z);
    Vector3 right = facing.Cross(up);
    Vector3 forward = up.Cross(right);

    Vector3 heading;
    heading = RotateByQuaternion(kAxisPitch, mpOwner->mLocomotion.GetOrientation());
    float pitch = WrapAngleMod(SignedAngleNormalized(forward, facing, right));
    float roll = WrapAngleMod(SignedAngleNormalized(right, RejectFrom(heading, forward), forward));
    float turn = WrapAngleMod(SignedAngleNormalized(forward, facing, up));

    Vector3 pathPos, pathDir;
    Evaluate(mPath, mT + 16.0f, &pathPos, &pathDir);
    float targetTurn = WrapAngleMod(SignedAngleNormalized(forward, RejectFrom(pathDir, up), up));

    pitch = WrapAngle(AngleStepToward(pitch, 0.0f, gPitchRate * dt) - pitch);
    roll = WrapAngle(AngleStepToward(roll, 0.0f, gRollRate * dt) - roll);
    turn = WrapAngle(AngleStepToward(turn, targetTurn, sTurnRate * dt) - turn);

    Quaternion q = mpOwner->mLocomotion.GetOrientation();
    if (turn != 0.0f)
        q *= AxisAngle(kAxisTurn, turn);
    if (pitch != 0.0f)
        q *= AxisAngle(kAxisPitch, pitch);
    if (roll != 0.0f)
        q *= AxisAngle(kAxisRoll, roll);
    q = q.Normalized();
    mpOwner->mLocomotion.SetOrientation(q);
}
