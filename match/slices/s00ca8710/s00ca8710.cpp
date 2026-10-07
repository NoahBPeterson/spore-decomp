// Slice s00ca8710 -- path-following locomotion update (0x00ca8b10, 2699 bytes).
//
// Per-frame update of a locomotion behavior that follows a path of waypoints: it handles a pending
// (re)start, accelerates/decelerates its current speed towards the speed of the current path span
// (slowing down to brake before the end of the path), advances its parameter along the path,
// consumes waypoints, writes the resulting velocity into params->mVelocity and finally orients the
// owner (surface-aligned orientation, a facing basis, or a forwarded steering helper per mode).
//
// Module flags: /O2 /arch:SSE /fp:fast (scalar SSE math, x87 sqrt and float returns).
// The original was built with whole-program optimization (edx survives calls to 0x00c9eaf0), so
// it is not expected to match byte-exact.
#include "types.h"
#include <math.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// maxss then minss (SSE NaN semantics: a NaN value yields lo).
inline float Clamp(float value, float minValue, float maxValue)
{
    value = value > minValue ? value : minValue;
    value = value < maxValue ? value : maxValue;
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
    Vector3 Cross(const Vector3& b) const
    {
        return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
};

struct Quaternion { float x, y, z, w; };
struct Matrix3 { float m[9]; };

// ---- callees ----
Matrix3 MakeMatrixRows(const Vector3& a, const Vector3& b, const Vector3& c);   // 0x00afa0c0 (rows c, a, b)
Quaternion QuaternionFromMatrix(const Matrix3& m);                              // 0x0046d660
Quaternion NormalizedQuaternion(const Quaternion& q);                           // 0x00c64ad0

struct cPlanetModel {
    uint8_t pad00[0xf0];
    bool mbF0;                                                                  // +0xf0
    Vector3 GetSurfaceNormal(const Vector3& pos);                               // 0x00b7e3b0
    Quaternion BuildSurfaceOrientation(const Vector3& pos, const Vector3& dir); // 0x00b7f250
};
cPlanetModel* PlanetModel();                                                    // 0x00b3d350

extern const Vector3 kZeroVector;      // 0x01699b08
extern const Vector3 kDefaultFacing;   // 0x0169a28c

struct Waypoint { uint32_t data[15]; };  // 0x3c bytes

struct LocoGoal {
    Waypoint* mpBegin;         // +0x00 queued path waypoints
    Waypoint* mpEnd;           // +0x04
    uint32_t pad08[3];
    Waypoint mCurrent;         // +0x14
    Vector3 mFacing;           // +0x50
    int mMode;                 // +0x5c
    Waypoint* erase(Waypoint* it);   // 0x00b47520 (vector::erase)
};

struct ILocomotion {
    PV8 PV2 PV
    virtual const Vector3& GetPosition();            // +0x2c
    PV2 PV
    virtual void SetOrientation(const Quaternion& q); // +0x3c
    PV4 PV2 PV
    virtual Vector3 GetFacing();                     // +0x5c
    PV8 PV8 PV8 PV2
    virtual float GetMaxSpeed();                     // +0xc8
    PV
    virtual float GetMaxAcceleration();              // +0xd0
    PV4 PV2
    virtual void OnPathFailed();                     // +0xec
    LocoGoal* GetGoal();                             // 0x00c41ec0
};

struct cLocomotionOwner {
    uint32_t pad00[0xd];
    ILocomotion mLocomotion;                         // +0x34
    uint32_t pad38[0x9b];
    uint32_t mFlags;                                 // +0x2a4
    uint8_t pad2a8[0x84c];
    bool mbStopped;                                  // +0xaf4
    uint8_t padaf5[7];
    bool mbAFC;                                      // +0xafc
    int GetMoveType();                               // 0x00c9eaf0
    void ExecutePath();                              // 0x00ca72a0
    void GetOrbit(const Vector3* pos, float* radius, float* other); // 0x00c9ff40
};

void StartPathMode1(LocoGoal* goal);                 // 0x00c9f130

struct LocoUpdateParams {
    Vector3 mVelocity;         // +0x00 (out)
    float mUnk0c;
    float mDeltaTime;          // +0x10
};

struct cPathLocomotion {
    uint32_t vtbl;
    bool mbRestart;                                  // +0x04
    uint8_t pad05[0xb];
    cLocomotionOwner* mpOwner;                       // +0x10
    int mMode;                                       // +0x14
    float mSpeed;                                    // +0x18
    bool mbWaiting;                                  // +0x1c
    uint8_t pad1d[3];
    uint32_t mPath[0xe];                             // +0x20
    float mSpeedOffSpan;                             // +0x58
    float mSpeedOnSpan;                              // +0x5c
    uint32_t pad60[8];
    float mSpanStart;                                // +0x80
    uint32_t pad84;
    float mSpanLength;                               // +0x88
    float mPathEnd;                                  // +0x8c
    uint32_t pad90[0x10];
    float mT;                                        // +0xd0

    void StartPathMode2(LocoGoal* goal);                                        // 0x00ca1c60
    void Evaluate(void* path, float t, Vector3* pos, Vector3* dir);             // 0x00ca1dc0
    bool NextSegment();                                                         // 0x00ca2370
    bool ShouldStop(float dt);                                                  // 0x00ca28a0
    bool WaitAtWaypoint(Waypoint* wp, float dt);                                // 0x00ca46c0
    void Steer(Vector3 dir, float dt, float speed, int accelSign);              // 0x00ca4f90
    void Turn(Vector3 dir, float dt);                                           // 0x00ca5b10

    void Update(LocoUpdateParams* params);
};

// @ 0x00ca8b10
void cPathLocomotion::Update(LocoUpdateParams* params)
{
    LocoGoal* goal = mpOwner->mLocomotion.GetGoal();
    if (mMode == 1 && PlanetModel()->mbF0)
        return;

    if ((mpOwner->mFlags & 4) && mpOwner->mLocomotion.GetMaxSpeed() == 0.0f) {
        mpOwner->mbStopped = true;
        params->mVelocity = kZeroVector;
        return;
    }

    bool active = goal->mMode != 0;
    if (mbRestart) {
        mbWaiting = false;
        if (active) {
            if (mMode == 1)
                StartPathMode1(goal);
            else if (mMode == 2)
                StartPathMode2(goal);
            if (1.5258789e-05f > mSpeed &&
                (mpOwner->GetMoveType() == 5 || mpOwner->GetMoveType() == 1 || mpOwner->GetMoveType() == 6)) {
                mbWaiting = true;
            } else if (!NextSegment()) {
                mpOwner->mLocomotion.OnPathFailed();
                mpOwner->mFlags |= 8;
                active = false;
            }
        } else {
            mpOwner->ExecutePath();
        }
        mbRestart = false;
    }

    if (!active) {
        mSpeed = 0.0f;
        params->mVelocity = kZeroVector;
        mpOwner->mbStopped = active;
        if (mMode == 2) {
            Vector3 pos = mpOwner->mLocomotion.GetPosition();
            float len = sqrtf(pos.z * pos.z + pos.y * pos.y + pos.x * pos.x + 1e-8f);
            float inv = 1.0f / len;
            float nx = inv * pos.x;
            float ny = pos.y * inv;
            float nz = pos.z * inv;
            float radius, other;
            mpOwner->GetOrbit(&pos, &radius, &other);
            float invDt = 1.0f / params->mDeltaTime;
            params->mVelocity.x = (nx * radius - pos.x) * invDt;
            params->mVelocity.y = (ny * radius - pos.y) * invDt;
            params->mVelocity.z = (nz * radius - pos.z) * invDt;
            Vector3 n(nx, ny, nz);
            Vector3 a = mpOwner->mLocomotion.GetFacing().Cross(n);
            Vector3 b = n.Cross(a);
            float s = 1.0f / sqrtf(b.x * b.x + b.y * b.y + b.z * b.z + 1e-8f);
            Steer(Vector3(s * b.x, s * b.y, s * b.z), params->mDeltaTime, 0.0f, 0);
        }
        return;
    }

    if (mbWaiting) {
        if (!WaitAtWaypoint(&goal->mCurrent, params->mDeltaTime)) {
            params->mVelocity = kZeroVector;
            return;
        }
        mbWaiting = false;
        if (!NextSegment()) {
            mpOwner->mLocomotion.OnPathFailed();
            mpOwner->mFlags |= 8;
        }
    }

    float remaining = params->mDeltaTime;
    Vector3 pos = kZeroVector;
    Vector3 dir = kDefaultFacing;
    float accel = mpOwner->mLocomotion.GetMaxAcceleration();
    int accelSign = 0;
    float t = mT;
    float targetSpeed;
    if (mSpanStart > t || t > mSpanLength + mSpanStart)
        targetSpeed = mSpeedOffSpan;
    else
        targetSpeed = mSpeedOnSpan;

    if (goal->mpBegin == goal->mpEnd) {
        float distLeft = mPathEnd - t;
        float brakeDist;
        if (mpOwner->mbAFC)
            brakeDist = targetSpeed / accel * targetSpeed * 0.5f;
        else
            brakeDist = accel * 0.25f;
        if (brakeDist > distLeft) {
            float speed = Clamp(distLeft / brakeDist, 0.0f, 1.0f) * targetSpeed;
            if (!mpOwner->mbAFC) {
                float lo, hi;
                if (targetSpeed > 5.0f) {
                    lo = 5.0f;
                    hi = targetSpeed;
                } else {
                    lo = targetSpeed;
                    hi = 5.0f;
                }
                speed = Clamp(speed, lo, hi);
            }
            targetSpeed = speed;
        }
    }

    mpOwner->mbStopped = ShouldStop(params->mDeltaTime);
    if (mpOwner->mbStopped)
        targetSpeed = 0.0f;

    float speed = mSpeed;
    if (targetSpeed > speed) {
        float next = params->mDeltaTime * accel + speed;
        mSpeed = Min(next, targetSpeed);
        accelSign = 1;
    } else if (speed > targetSpeed) {
        float next = speed - params->mDeltaTime * accel;
        mSpeed = Max(next, targetSpeed);
        accelSign = -1;
    }

    while (remaining > 0.0f) {
        float end = mPathEnd;
        float nextT = params->mDeltaTime * mSpeed + mT;
        if (end > nextT) {
            Evaluate(mPath, nextT, &pos, &dir);
            mT = nextT;
            break;
        }
        remaining -= (end - mT) / mSpeedOnSpan;
        mT = end;
        Evaluate(mPath, end, &pos, &dir);
        if (goal->mpBegin == goal->mpEnd) {
            mpOwner->mLocomotion.OnPathFailed();
            break;
        }
        Waypoint* first = goal->mpBegin;
        goal->mCurrent = *first;
        goal->erase(first);
        if (!NextSegment()) {
            mpOwner->mLocomotion.OnPathFailed();
            break;
        }
    }

    const Vector3& cur = mpOwner->mLocomotion.GetPosition();
    float dt = params->mDeltaTime;
    float invDt = 1.0f / dt;
    Vector3 velocity(invDt * (pos.x - cur.x), invDt * (pos.y - cur.y), invDt * (pos.z - cur.z));
    params->mVelocity = velocity;

    switch (mMode) {
    case 0:
        if (mpOwner->GetMoveType() == 6) {
            mpOwner->mLocomotion.SetOrientation(PlanetModel()->BuildSurfaceOrientation(pos, dir));
            return;
        }
        if (mpOwner->GetMoveType() == 0) {
            Vector3 forward = dir;
            Vector3 up = PlanetModel()->GetSurfaceNormal(pos);
            Vector3 side = forward.Cross(up);
            forward = up.Cross(side);
            Quaternion q = QuaternionFromMatrix(MakeMatrixRows(forward, up, side));
            q = NormalizedQuaternion(q);
            mpOwner->mLocomotion.SetOrientation(q);
            return;
        }
        Turn(dir, dt);
        break;
    case 1:
        mpOwner->mLocomotion.SetOrientation(PlanetModel()->BuildSurfaceOrientation(pos, dir));
        return;
    case 2:
        Steer(dir, dt,
              sqrtf(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z),
              accelSign);
        return;
    }
}
