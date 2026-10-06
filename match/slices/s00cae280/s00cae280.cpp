// Slice s00cae280 -- locomotive steering update (0x00cae280, 5072 bytes).
//
// Per-frame steering of a creature's locomotion: from the goal (target point, arrival facing,
// mode) it picks a desired direction and speed (straight at the goal, along a turning circle
// tangent when the creature has to arc around to reach the goal facing, or towards the next path
// point), turns the creature's facing towards it at a limited turn rate, writes the new
// orientation (snapped to the planet surface) and finally accelerates params->mVelocity towards
// the desired velocity, limited by the max acceleration and max speed.
//
// Module flags: /O2 /arch:SSE /fp:fast (scalar SSE math, x87 sqrt/acos, __asm Clamp helper that
// forces the ebp frame with 16-byte alignment).
#include "types.h"
#include <math.h>

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

// eastl::min / eastl::max
template <typename T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
template <typename T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    float SquaredLength() const { return x * x + y * y + z * z; }
    float Dot(const Vector3& b) const { return x * b.x + y * b.y + z * b.z; }
    Vector3 Cross(const Vector3& b) const
    {
        return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
    Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
};
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
inline Vector3 operator-(const Vector3& a) { return Vector3(-a.x, -a.y, -a.z); }

struct Quaternion { float x, y, z, w; };

// ---- callees (cdecl unless noted) ----
Vector3 normalized_safe(const Vector3& v);                                   // 0x00449c20
bool operator!=(const Vector3& a, const Vector3& b);                         // 0x0041dd30
float Dot3(const Vector3& v);                                                // 0x004885d0 (squared length)
Vector3 RotateTowards(const Vector3& from, const Vector3& to, float t);      // 0x00b0fd00
Vector3 CircleTangentPoint(const Vector3& center, float radius,
                           const Vector3& from, const Vector3& dir);        // 0x00699800
Quaternion QuaternionFromFacingAndUp(const Vector3& facing, const Vector3& up); // 0x0069b600

struct cPlanetModel {
    Quaternion SnapOrientationToSurface(const Vector3& pos, const Quaternion& q, float height); // 0x00b7f320
    Quaternion AlignOrientationToSurface(const Vector3& pos, const Quaternion& q);             // 0x00b7f1f0
};
cPlanetModel* PlanetModel();                                                 // 0x00b3d350

extern const Vector3 kZeroVector;          // 0x0169a37c
extern float kTurnCircleTolerance;         // 0x0157d334 (0.9)
extern float kGoalCircleTolerance;         // 0x0157d330 (0.9)
extern float kSlowTurnAngle;               // 0x0157d32c (0.1)

struct LocoGoal {
    Vector3* mpBegin;          // +0x00 path points
    Vector3* mpEnd;            // +0x04
    uint32_t pad08[3];
    Vector3 mTarget;           // +0x14
    uint32_t pad20[12];
    Vector3 mFacing;           // +0x50 arrival facing
    int mMode;                 // +0x5c
    float mStopDistance;       // +0x60
    const Vector3* GetNextPoint();   // 0x00c423c0
};

struct cLocomotiveObject {
    PV8 PV2 PV
    virtual const Vector3& GetPosition();            // +0x2c
    PV8 PV8 PV8 PV8 PV2
    virtual void* Cast(uint32_t type);               // +0xb8
    uint32_t pad04[0x9b];
    int mFlags;                                      // +0x270
    LocoGoal* GetGoal();                             // 0x00c41ec0
    bool IsNearGoal();                               // 0x00c42e20
};

struct ILocomotion {
    PV8 PV4 PV2 PV
    virtual void SetOrientation(const Quaternion& q); // +0x3c
    PV4 PV2 PV
    virtual Vector3 GetFacing();                     // +0x5c
    PV8 PV8 PV8 PV2
    virtual float GetMaxSpeed();                     // +0xc8
    PV
    virtual float GetMaxAcceleration();              // +0xd0
};

struct cCreatureLocomotion {
    uint32_t pad00[0xd];
    ILocomotion mLocomotion;                         // +0x34
    uint32_t pad38[0x79];
    float mTurnRate;                                 // +0x21c
    uint32_t pad220[0x236];
    uint8_t mFlagsAF8;                               // +0xaf8
    uint8_t padaf9[0x23];
    int mbB1C;                                       // +0xb1c
    uint8_t padb20[0xad];
    bool mbBCD;                                      // +0xbcd
    float GetSpeedA();                               // 0x00c9ee90
    float GetSpeedB();                               // 0x00c9f380
};

struct LocoSteerParams {
    Vector3 mVelocity;         // +0x00 (in/out)
    float mUnk0c;
    float mDeltaTime;          // +0x10
    cLocomotiveObject* mpObject; // +0x14
};

static __forceinline float ArrivalSpeed(float maxSpeed, float dist, float dt, float accel)
{
    return Min(maxSpeed, Min(dist / dt, sqrtf(accel * dist)));
}

// @ 0x00cae280
void LocomotiveSteer(LocoSteerParams* params)
{
    cLocomotiveObject* object = params->mpObject;
    cCreatureLocomotion* owner = object ? (cCreatureLocomotion*)object->Cast(0x137e8e0) : 0;
    bool slowTurn = owner->mbB1C != 0 || (owner->mFlagsAF8 & 4) != 0;

    float speed = params->mVelocity.Length();
    float dt = params->mDeltaTime;
    ILocomotion* loco = &owner->mLocomotion;
    float maxSpeed = loco->GetMaxSpeed();
    float speedA = owner->GetSpeedA();
    float speedB = owner->GetSpeedB() * 0.2f;
    const float& refSpeed = Max(speedB, speedA);
    float turnScale;
    if (slowTurn && refSpeed > 0.0f)
        turnScale = Clamp(speed / refSpeed, 0.1f, 1.0f);
    else
        turnScale = 1.0f;
    float maxTurnRate = owner->mTurnRate * turnScale;
    float speedRatio = speed / maxTurnRate;
    float radius = Max(1.0f, speedRatio);

    const Vector3& pos = object->GetPosition();
    Vector3 facing = loco->GetFacing();
    LocoGoal* goal = object->GetGoal();
    bool hasMode = goal->mMode != 0;
    bool nearGoal = object->IsNearGoal();
    Vector3 toGoal = goal->mTarget - pos;
    float distToGoal = toGoal.Length();
    const Vector3& nextPoint = *goal->GetNextPoint();
    float stopDistance = goal->mStopDistance;
    bool pathEmpty = goal->mpBegin == goal->mpEnd;
    int flags = object->mFlags;
    Vector3 desiredVelocity = kZeroVector;
    Vector3 newFacing = facing;
    float distToNext = (nextPoint - pos).Length();
    float accel = loco->GetMaxAcceleration();

    if (owner->mbBCD) {
        accel = owner->GetSpeedB() * 4.0f;
    } else if (((flags >> 2) & 1) != 0 || !hasMode || nearGoal) {
        accel *= 2.0f;
    } else {
        Vector3 dir = normalized_safe(distToGoal > 1.5258789e-05f ? toGoal : params->mVelocity);
        if (pathEmpty) {
            switch (goal->mMode) {
            case 1:
            case 4: {
                float s = ArrivalSpeed(maxSpeed, distToNext, dt, accel);
                desiredVelocity = dir * s;
                if (stopDistance > distToNext)
                    accel *= 16.0f;
                break;
            }
            case 2:
                desiredVelocity = dir * maxSpeed;
                break;
            case 3: {
                // arc around a turning circle so that we arrive with the goal facing
                Vector3 up = normalized_safe(goal->mTarget);
                Vector3 side = goal->mFacing.Cross(up);
                if (side.Dot(dir) > 0.0f)
                    side = -side;
                Vector3 center = goal->mTarget + side * radius;
                if (kTurnCircleTolerance * radius <= (pos - center).Length()) {
                    Vector3 aim;
                    if (goal->mFacing.Dot(dir) < 0.0f)
                        aim = goal->mTarget + side * (radius * 2.0f);
                    else
                        aim = goal->mTarget - goal->mFacing * (distToNext * 0.5f);
                    Vector3 tangent = CircleTangentPoint(center, radius, pos, normalized_safe(aim - pos));
                    if (tangent != kZeroVector) {
                        Vector3 toTangent = tangent - pos;
                        dir = normalized_safe(toTangent);
                        distToNext = (tangent - goal->mTarget).Length() + toTangent.Length();
                    }
                }
                float s = ArrivalSpeed(maxSpeed, distToNext, dt, accel);
                desiredVelocity = dir * s;
                if (stopDistance > distToNext)
                    accel *= 16.0f;
                break;
            }
            }
        } else {
            // approach the goal on a circle tangent to the first path segment
            float goalRadius = Max(1.0f, speedRatio);
            Vector3 up = normalized_safe(goal->mTarget);
            Vector3 toFirst = *goal->mpBegin - goal->mTarget;
            Vector3 along = normalized_safe(toFirst - up * up.Dot(toFirst));
            Vector3 side = along.Cross(up);
            if (side.Dot(dir) > 0.0f)
                side = -side;
            Vector3 center = goal->mTarget + side * goalRadius;
            if (goalRadius * kGoalCircleTolerance <= (pos - center).Length()) {
                Vector3 aim;
                if (along.Dot(dir) < 0.0f)
                    aim = goal->mTarget + side * (goalRadius * 2.0f);
                else
                    aim = goal->mTarget - along * (distToGoal * 0.5f);
                Vector3 tangent = CircleTangentPoint(center, goalRadius, pos, normalized_safe(aim - pos));
                if (tangent != kZeroVector) {
                    Vector3 toTangent = tangent - pos;
                    dir = normalized_safe(toTangent);
                    distToGoal = (tangent - goal->mTarget).Length() + toTangent.Length();
                }
            }
            float s = ArrivalSpeed(maxSpeed, distToNext, dt, accel);
            desiredVelocity = dir * s;
        }

        if (goal->mMode != 4) {
            if (stopDistance > distToNext && Dot3(goal->mFacing) > 1.5258789e-05f)
                newFacing = goal->mFacing;
            else if (desiredVelocity.SquaredLength() > 1.5258789e-05f)
                newFacing = normalized_safe(desiredVelocity);

            float angle = acosf(Clamp(newFacing.Dot(facing), -1.0f, 1.0f));
            if (angle > 1.5258789e-05f) {
                float turnRate = owner->mTurnRate;
                float timeToGoal = maxSpeed > 1.5258789e-05f ? distToGoal / maxSpeed : 1.0f;
                if (timeToGoal > 1.5258789e-05f)
                    turnRate = angle / timeToGoal * 2.0f;
                float t = Min(maxTurnRate, turnRate) * dt / angle;
                facing = RotateTowards(facing, newFacing, Min(1.0f, t));
            } else {
                facing = newFacing;
            }
            facing = normalized_safe(facing);
            Vector3 up = normalized_safe(pos);
            Quaternion q = QuaternionFromFacingAndUp(facing, up);
            Quaternion orientation;
            if (owner->mbB1C == 0)
                orientation = PlanetModel()->SnapOrientationToSurface(pos, q, 5.0f);
            else
                orientation = PlanetModel()->AlignOrientationToSurface(pos, q);
            loco->SetOrientation(orientation);
        }
    }

    float turnAngle = acosf(Clamp(newFacing.Dot(facing), -1.0f, 1.0f));
    Vector3 targetVelocity = desiredVelocity;
    if (slowTurn && goal->mMode != 4 && turnAngle > kSlowTurnAngle)
        targetVelocity = facing * desiredVelocity.Length();
    Vector3 accelVec = (targetVelocity - params->mVelocity) * (1.0f / dt);
    if (accelVec.Dot(facing) > 0.0f) {
        float len = accelVec.Length();
        if (len > accel)
            accelVec *= accel / len;
    }
    Vector3 velocity = accelVec * dt + params->mVelocity;
    params->mVelocity = velocity;
    float len = velocity.Length();
    if (len > maxSpeed)
        params->mVelocity = velocity * (maxSpeed / len);
    if (slowTurn && goal->mMode != 4 && turnAngle > kSlowTurnAngle)
        params->mVelocity = facing * params->mVelocity.Length();
}
