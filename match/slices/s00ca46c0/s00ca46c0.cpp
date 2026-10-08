// Camera orientation follow step (0x00ca46c0): turns the camera orientation toward a target
// point. Builds a local up/right/forward basis from the camera position, measures four signed
// angles against it, advances each angle toward its goal at a per-axis rate, applies the three
// rotation deltas about fixed axes to the camera quaternion, renormalizes it, and writes it
// back. Returns true when already pointing at the target, or when the yaw error is < 0.1.
#include "types.h"
#include <math.h>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct Quaternion { float x, y, z, w; };

extern float g_RateA;       // 0x0169a274 (base rate; x2 or x4)
extern float g_RateB;       // 0x0169a278
extern float g_RateC;       // 0x0169a27c
extern float g_TwoPiA;      // 0x0169a280
extern Vector3 g_AxisYaw;   // 0x0169a28c
extern Vector3 g_AxisPitch; // 0x0169a298
extern Vector3 g_AxisRoll;  // 0x0169a2a4
extern float g_PiA;         // 0x0157c728
extern float g_TwoPiB;      // 0x0157c710
extern float g_PiB;         // 0x01474998

float __cdecl SignedAngle(const Vector3* a, const Vector3* b, const Vector3* axis);   // 0x0069b760
float __cdecl ApproachAngle(float current, float target, float step);                 // 0x0069b840
Vector3* __cdecl RotateByQuat(Vector3* out, const Vector3* v, const Quaternion* q);   // 0x0059aed0
Quaternion* __cdecl QuatMul(Quaternion* out, const Quaternion* a, const Quaternion* b); // 0x007dcb00

struct ICameraState {
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
    virtual void s8();  virtual void s9();  virtual void s10();
    virtual const Vector3* GetPosition();                  // +0x2c
    virtual const Quaternion* GetOrientation();            // +0x30
    virtual void s13(); virtual void s14();
    virtual void SetOrientation(const Quaternion* q);      // +0x3c
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual void GetUpReference(Vector3* out);             // +0x5c
};

struct CameraOwner {
    uint32_t pad[13];
    ICameraState mState;   // +0x34
};

struct cCameraFollow {
    uint32_t pad[4];
    CameraOwner* mpOwner;  // +0x10
    int mMode;             // +0x14
    bool Step(const Vector3* pTarget, float dt);
};

__forceinline float WrapSigned(float v)
{
    float r = (float)fmod((double)v, (double)g_TwoPiA);
    if (r > g_PiA)
        r -= g_TwoPiA;
    else if (-g_PiA > r)
        r += g_TwoPiA;
    return r;
}

__forceinline float WrapDelta(float v)
{
    float r = (float)fmod((double)v, (double)g_TwoPiB);
    if (r >= g_PiB)
        r -= g_TwoPiB;
    return r;
}

__forceinline void RotateAbout(Quaternion& cur, const Vector3& axis, float angle)
{
    float s = (float)sin((double)(angle * 0.5f));
    float c = (float)cos((double)(angle * 0.5f));
    Quaternion q;
    q.x = s * axis.x;
    q.y = s * axis.y;
    q.z = s * axis.z;
    q.w = c;
    Quaternion out;
    cur = *QuatMul(&out, &cur, &q);
}

// @ 0x00ca46c0
bool cCameraFollow::Step(const Vector3* pTarget, float dt)
{
    const Vector3* pPos = mpOwner->mState.GetPosition();
    float px = pPos->x, py = pPos->y, pz = pPos->z;
    float dy = pTarget->y - py;
    float dz = pTarget->z - pz;
    float dx = pTarget->x - px;
    float len = (float)sqrt((dy * dy + dz * dz) + dx * dx);
    if (len < 0.01)
        return true;
    float inv = 1.0f / len;
    Vector3 dir;
    dir.x = inv * dx;
    dir.y = dy * inv;
    dir.z = dz * inv;

    Vector3 look;
    mpOwner->mState.GetUpReference(&look);

    float ninv = 1.0f / (float)sqrt(((px * px + pz * pz) + py * py) + 1e-8f);
    Vector3 up;
    up.x = ninv * px;
    up.y = py * ninv;
    up.z = pz * ninv;

    Vector3 right;
    right.x = look.y * up.z - look.z * up.y;
    right.y = look.z * up.x - up.z * look.x;
    right.z = up.y * look.x - look.y * up.x;
    Vector3 fwd;
    fwd.x = right.z * up.y - right.y * up.z;
    fwd.y = up.z * right.x - right.z * up.x;
    fwd.z = right.y * up.x - up.y * right.x;

    Vector3 tmp;
    Vector3 ref = *RotateByQuat(&tmp, &g_AxisPitch, mpOwner->mState.GetOrientation());

    float rate = mMode == 2 ? g_RateA * 2.0f : g_RateA * 4.0f;

    float a0 = WrapSigned(SignedAngle(&fwd, &look, &right));

    float rd = (ref.z * fwd.z + ref.y * fwd.y) + ref.x * fwd.x;
    ref.x = ref.x - rd * fwd.x;
    ref.y = ref.y - rd * fwd.y;
    ref.z = ref.z - rd * fwd.z;
    float a1 = WrapSigned(SignedAngle(&right, &ref, &fwd));

    float a2 = WrapSigned(SignedAngle(&fwd, &look, &up));

    float dd = (up.z * dir.z + up.y * dir.y) + up.x * dir.x;
    dir.x = dir.x - dd * up.x;
    dir.y = dir.y - dd * up.y;
    dir.z = dir.z - dd * up.z;
    float a3 = WrapSigned(SignedAngle(&fwd, &dir, &up));

    float d0 = WrapDelta(ApproachAngle(a0, 0.0f, g_RateB * dt) - a0);
    float d1 = WrapDelta(ApproachAngle(a1, 0.0f, g_RateC * dt) - a1);
    float d2 = WrapDelta(ApproachAngle(a2, a3, rate * dt) - a2);

    const Quaternion* pq = mpOwner->mState.GetOrientation();
    Quaternion q;
    q.x = pq->x; q.y = pq->y; q.z = pq->z; q.w = pq->w;
    if (d2 != 0.0f)
        RotateAbout(q, g_AxisRoll, d2);
    if (d0 != 0.0f)
        RotateAbout(q, g_AxisPitch, d0);
    if (d1 != 0.0f)
        RotateAbout(q, g_AxisYaw, d1);

    float qinv = 1.0f / (float)sqrt(((q.x * q.x + q.w * q.w) + q.z * q.z) + q.y * q.y);
    q.x = qinv * q.x;
    q.w = q.w * qinv;
    q.y = q.y * qinv;
    q.z = q.z * qinv;
    mpOwner->mState.SetOrientation(&q);
    return fabs(a2 - a3) < 0.1f;
}
