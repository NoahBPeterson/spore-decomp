// Slice s00cb02f0: Simulator::cFlyingLocomotion steering update (0x00CB02F0, 3608 bytes),
// vtable slot 3 of vtbl_Simulator::cFlyingLocomotion (0x01475124).
// Flags region: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE math, x87 sqrt/fmod).
//
// Per-frame flight steering of a flying creature along its locomotion request (path):
//  - after a reset, re-projects every path point and the current goal onto the flight surface;
//  - without an active request it just flies to the projected current position;
//  - advances to the next path point when the current one is reached (or when it has been
//    stalled for more than half a second inside the acceptable stop distance);
//  - once the flight direction is (anti)parallel to the local up vector it latches the
//    "aligned" flag and hands over to the simple fly-to-target helper;
//  - otherwise it builds a lateral steering direction (the goal direction projected onto the
//    tangent plane, or the facing's side vector), adds a lift component when an obstacle lies
//    ahead (raycast / planet intersection within the look-ahead distance) or a descent component
//    when above the ground, turns the facing towards it at the creature's turn rate, and
//    accelerates towards a desired speed limited by distance and turning angle.
#include "types.h"
#include <math.h>

#pragma pack(push, 4)

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// eastl::min / eastl::max
template <typename T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
template <typename T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float Length() const { return sqrtf(x * x + y * y + z * z); }
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
    bool operator==(const Vector3& b) const { return x == b.x && y == b.y && z == b.z; }
};
inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
inline Vector3 operator-(const Vector3& a) { return Vector3(-a.x, -a.y, -a.z); }

// ---- globals ----
extern float kFlyAlignThreshold;            // 0x0157D33C (0.97)
extern float kFlyLiftRate;                  // 0x0157D338 (2.0)
extern float kPI;                           // 0x0157D2E8
extern float kTwoPI;                        // 0x0169A3F8
extern Vector3 kZeroVector;                 // 0x0169A37C

// ---- callees ----
Vector3 normalized_safe(const Vector3& v);                                  // 0x00449C20
float SignedAngle(const Vector3& from, const Vector3& to, const Vector3& axis); // 0x006994A0

struct cPlanetModel {
    Vector3 IntersectRay(const Vector3& origin, const Vector3& dir);         // 0x00B82110
};
cPlanetModel* PlanetModel();                                                // 0x00B3D350

// One path point of a locomotion request (0x3C bytes).
struct LocoWaypoint {
    Vector3 mPosition;              // +0x00
    float mGoalStopDistance;        // +0x0C
    uint32_t pad10[11];
};

// Simulator::cLocomotionRequest
struct cLocomotionRequest {
    LocoWaypoint* mpBegin;          // +0x00
    LocoWaypoint* mpEnd;            // +0x04
    uint32_t pad08[3];
    LocoWaypoint mGoal;             // +0x14
    uint32_t pad50[3];
    int mMode;                      // +0x5C
    float mAcceptableStopDistance;  // +0x60
    float field_64;                 // +0x64
    float mLastDistance;            // +0x68
    float mStallTime;               // +0x6C
    void erase(LocoWaypoint* it);                                           // 0x00B47520
};

struct cCreatureFlyer;

struct cLocomotiveObject {
    PV8 PV2 PV
    virtual const Vector3* GetPosition();            // +0x2c
    PV8 PV2 PV
    virtual Vector3 GetFacing();                     // +0x5c
    PV4 PV
    virtual float GetHoverHeight();                  // +0x74
    PV8 PV8
    virtual cCreatureFlyer* Cast(uint32_t type);     // +0xb8
    PV8 PV4
    virtual void StopMovement();                     // +0xec
    cLocomotionRequest* GetRequest();                                       // 0x00C41EC0
    const Vector3* GetVelocity();                                           // 0x00D20610
};

struct cCreatureFlyer {
    uint32_t pad00[0x34 / 4];
    cLocomotiveObject mLocomotion;                   // +0x34
    uint32_t pad38[(0x21C - 0x38) / 4];
    float mTurnRate;                                 // +0x21C
    float GetMaxSpeed();                                                    // 0x00C9F380
    float GetGroundRadius(const Vector3& pos);                              // 0x00C9FFD0
};

Vector3 ProjectToFlightSurface(const Vector3& pos, cCreatureFlyer* pFlyer);         // 0x00CAE0E0
Vector3 AvoidSurface(const Vector3& pos, cCreatureFlyer* pFlyer);                   // 0x00CADB90
Vector3 TurnTowards(const Vector3& from, const Vector3& to, float turnRate, float dt); // 0x00CADF50
bool SweepTest(cLocomotiveObject* pObject, const Vector3& from, const Vector3& to, Vector3* pHit, int flags); // 0x00B53BC0

struct LocoSteerParams {
    Vector3 mVelocity;              // +0x00 (out)
    float mUnk0c;
    float mDeltaTime;               // +0x10
    cLocomotiveObject* mpObject;    // +0x14
};

struct cFlyingLocomotion {
    void* vtable;
    bool mbReset;                   // +0x04
    uint8_t pad05[0x34 - 5];
    bool mbAligned;                 // +0x34
    float mLift;                    // +0x38

    void FlyTo(cCreatureFlyer* pFlyer, const Vector3& target, LocoSteerParams* params); // 0x00CAFE90
    void ApplyFacing(cCreatureFlyer* pFlyer, const Vector3& dir, float dt);             // 0x00CAF650
    void Update(LocoSteerParams* params);
};

// @ 0x00CB02F0
void cFlyingLocomotion::Update(LocoSteerParams* params)
{
    if (mbReset) {
        cCreatureFlyer* pFlyer = params->mpObject ? params->mpObject->Cast(0x137E8E0) : 0;
        cLocomotionRequest* request = params->mpObject->GetRequest();
        if (request->mMode != 0) {
            int count = (int)(request->mpEnd - request->mpBegin);
            for (int i = 0; i < count; i++) {
                LocoWaypoint& point = request->mpBegin[i];
                point.mPosition = ProjectToFlightSurface(point.mPosition, pFlyer);
            }
            request->mGoal.mPosition = ProjectToFlightSurface(request->mGoal.mPosition, pFlyer);
        }
        request->mLastDistance = 0.0f;
        mbReset = false;
    }

    cCreatureFlyer* pFlyer = params->mpObject ? params->mpObject->Cast(0x137E8E0) : 0;
    cLocomotiveObject* loco = &pFlyer->mLocomotion;
    cLocomotionRequest* request = loco->GetRequest();
    if (request->mMode == 0) {
        Vector3 target = ProjectToFlightSurface(*loco->GetPosition(), pFlyer);
        FlyTo(pFlyer, target, params);
        return;
    }

    Vector3 pos = *loco->GetPosition();
    Vector3 up = pos.Normalized();
    Vector3 facing = loco->GetFacing();
    Vector3 target = request->mGoal.mPosition;
    Vector3 toTarget = target - pos;
    float dist = toTarget.Length();
    if (request->mGoal.mGoalStopDistance > dist ||
        (request->mStallTime > 0.5f && request->mAcceptableStopDistance > dist)) {
        mbAligned = false;
        if (request->mpBegin == request->mpEnd) {
            loco->StopMovement();
            FlyTo(pFlyer, target, params);
            return;
        }
        request->mGoal = *request->mpBegin;
        request->erase(request->mpBegin);
        target = request->mGoal.mPosition;
        request->mStallTime = 0.0f;
        dist = (target - pos).Length();
    }
    else {
        if (dist >= request->mLastDistance)
            request->mStallTime += params->mDeltaTime;
        else
            request->mStallTime = 0.0f;
        request->mLastDistance = dist;
    }

    toTarget = target - pos;
    Vector3 dir = toTarget.Normalized();
    if (pos.Normalized().Dot(up) < 0.97f) {
        Vector3 avoid = AvoidSurface(pos + dir * 16.0f, pFlyer);
        dir = (avoid - pos).Normalized();
        target = avoid;
    }

    float alignment = dir.Dot(up);
    if (!mbAligned && (alignment > kFlyAlignThreshold || alignment < -kFlyAlignThreshold))
        mbAligned = true;
    if (mbAligned) {
        FlyTo(pFlyer, target, params);
        return;
    }

    float hover = loco->GetHoverHeight();
    float lookAhead = Min(dist, pFlyer->GetMaxSpeed() * 2.0f + hover);
    float clearance = Min(dist, pFlyer->GetMaxSpeed() * 4.0f);
    float altitude = pos.Length() - Max(pFlyer->GetGroundRadius(pos), target.Length());

    Vector3 lateral = (dir - up * dir.Dot(up)).Normalized();
    Vector3 side = facing.Cross(up).Normalized();
    Vector3 forward = (facing - up * facing.Dot(up)).Normalized();
    Vector3 steer;
    if (forward.Dot(lateral) > 0.0f)
        steer = lateral;
    else if (side.Dot(lateral) < 0.0f)
        steer = -side;
    else
        steer = side;

    Vector3 hitPos;
    float liftTarget = kFlyLiftRate;
    if (!SweepTest(loco, pos, pos + dir * lookAhead, &hitPos, 0)) {
        Vector3 groundHit = PlanetModel()->IntersectRay(pos, dir);
        if (groundHit == kZeroVector || (groundHit - pos).Length() >= clearance)
            liftTarget = 0.0f;
    }

    if (mLift > liftTarget) {
        mLift -= params->mDeltaTime;
        if (mLift < 0.0f)
            mLift = 0.0f;
    }
    else if (mLift < liftTarget) {
        mLift += params->mDeltaTime;
        if (mLift > liftTarget)
            mLift = liftTarget;
    }

    if (mLift > 0.0f) {
        steer = (steer + up * mLift).Normalized();
    }
    else if (altitude > 0.0f) {
        float descent = Min(altitude, 5.0f) * 0.2f;
        steer = normalized_safe(steer - up * descent);
    }

    steer = TurnTowards(facing, steer, pFlyer->mTurnRate, params->mDeltaTime);
    float speed = loco->GetVelocity()->Length();
    float maxSpeed = pFlyer->GetMaxSpeed();
    float desiredSpeed = maxSpeed;
    if (request->mpBegin == request->mpEnd && maxSpeed > dist)
        desiredSpeed = dist;
    float angle = fmodf(SignedAngle(facing, dir, up), kTwoPI);
    if (angle > kPI)
        angle -= kTwoPI;
    else if (angle < -kPI)
        angle += kTwoPI;
    float turnSpeed = pFlyer->mTurnRate / fabsf(angle) * dist;
    if (turnSpeed < maxSpeed)
        desiredSpeed = turnSpeed;
    float accel = maxSpeed * 0.5f;
    if (desiredSpeed > speed) {
        speed += accel * params->mDeltaTime;
        if (speed > desiredSpeed)
            speed = desiredSpeed;
    }
    else if (speed > desiredSpeed) {
        speed -= accel * params->mDeltaTime;
        if (speed < desiredSpeed)
            speed = desiredSpeed;
    }
    params->mVelocity = steer * speed;
    ApplyFacing(pFlyer, steer, params->mDeltaTime);
}

#pragma pack(pop)
