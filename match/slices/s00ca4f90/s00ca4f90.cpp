// Slice s00ca4f90 -- cPathLocomotion::Steer (0x00ca4f90, 2939 bytes).
//
// Orients a path-following creature towards a desired direction: builds the owner's local frame
// (forward/right/up from its facing and its position on the planet), measures the current pitch and
// roll of the owner's orientation and the desired pitch/pitch of `dir`, adds a banking roll when the
// creature is outside the current path span (mode 5 also tilts on acceleration), steps pitch and roll
// toward their targets at a bounded rate, and applies the three rotations to the orientation.
//
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (scalar SSE math, x87 sqrt/fsin/fcos/fmod).
// The class layout and callee names follow slice s00ca8710 (cPathLocomotion::Update calls this).
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
};

struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    Quaternion(const Quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}

    Quaternion operator*(const Quaternion& b) const
    {
        Vector3 av(x, y, z);
        Vector3 bv(b.x, b.y, b.z);
        Vector3 c = av.Cross(bv);
        return Quaternion(w * b.x + b.w * x + c.x,
                          w * b.y + b.w * y + c.y,
                          w * b.z + b.w * z + c.z,
                          w * b.w - av.Dot(bv));
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
extern const float kQuarterPi;   // 0x0157c720
extern const float kTwoPi;       // 0x0157c710
extern const float kPiB;         // 0x01474998
extern float gTurnRateScale;     // 0x0157c708 (1.0f)

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
    uint8_t pad38[0xac4];
    bool mbAFC;                                      // +0xafc
    int GetMoveType();                               // 0x00c9eaf0
};

struct cPathLocomotion {
    uint32_t vtbl;
    uint32_t pad04[3];
    cLocomotionOwner* mpOwner;                       // +0x10
    uint32_t pad14[0xf];
    bool mbBankBefore;                               // +0x50
    bool mbBankAfter;                                // +0x51
    uint8_t pad52[0x2e];
    float mSpanStart;                                // +0x80
    float mBankAfter;                                // +0x84
    float mSpanLength;                               // +0x88
    uint32_t pad8c[0x11];
    float mT;                                        // +0xd0

    void Steer(Vector3 dir, float dt, float speed, int accelSign);
};

// fmod into (-pi, pi] using the module's 2*pi.
static inline float WrapAngleMod(float a)
{
    float x = (float)fmod((double)a, (double)gTwoPi);
    if (x > kPi)
        x -= gTwoPi;
    else if (x < -kPi)
        x += gTwoPi;
    return x;
}

// fmod into [-pi, pi).
static inline float WrapAngle(float x)
{
    x = (float)fmod((double)x, (double)kTwoPi);
    if (kPiB <= x)
        x -= kTwoPi;
    return x;
}

static inline Vector3 RejectFrom(const Vector3& v, const Vector3& n)
{
    float d = v.Dot(n);
    return Vector3(v.x - d * n.x, v.y - n.y * d, v.z - n.z * d);
}

// @ 0x00ca4f90
void cPathLocomotion::Steer(Vector3 dir, float dt, float speed, int accelSign)
{
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
    float turn = SignedAngleNormalized(forward, RejectFrom(dir, up), up);

    bool before = mT < mSpanStart;
    bool after = mT > mSpanLength + mSpanStart && mBankAfter > 0.0f;
    float targetRoll = 0.0f;
    if (speed > 0.0f && (before || after) && mpOwner->GetMoveType() != 4) {
        bool bank = before ? mbBankBefore : mbBankAfter;
        targetRoll = kQuarterPi;
        if (!bank)
            targetRoll = -targetRoll;
    }

    float targetPitch = SignedAngleNormalized(forward, RejectFrom(dir, right), right);
    if (mpOwner->GetMoveType() == 5) {
        if (accelSign > 0)
            targetPitch -= kQuarterPi * 0.75f;
        else if (accelSign < 0)
            targetPitch += kQuarterPi * 0.1f;
    }

    float pitchStep = (mpOwner->mbAFC ? gTurnRateScale : 1.0f) * gPitchRate * dt;
    float rollRate = (mpOwner->mbAFC ? gTurnRateScale : 1.0f) * gRollRate;
    pitch = WrapAngle(AngleStepToward(pitch, targetPitch, pitchStep) - pitch);
    roll = WrapAngle(AngleStepToward(roll, targetRoll, rollRate * dt) - roll);

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
