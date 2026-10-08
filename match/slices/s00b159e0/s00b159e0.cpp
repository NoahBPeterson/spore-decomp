// Slice s00b159e0 (batch bfs1) — 8 functions.
// Module "Spore"; SP::cTerrainCameraController input/scroll handlers + helpers.
// Each block starts with its original address.

#include "s00b159e0.h"
#include <math.h>
#include <xmmintrin.h>
#pragma intrinsic(acos, fabs)

extern "C" void* GonzagoModelWorld_00b3d520();
extern "C" float FUN_00b0f880(void*);
extern "C" void FUN_00b14370(void*, unsigned, void*);
extern "C" void* eastl_copy_runinfo(void*, void*, void*);

struct cTerrainSphere { float GetRadius(); };      // 0x00f987f0 (thiscall, float in st0)
cTerrainSphere* GetActiveTerrainSphere();           // 0x00f48aa0 (cdecl)

static inline void* g_vt(void* p) { return *(void**)p; }
static inline void* g_vfn(void* p, int off) { return *(void**)((char*)g_vt(p) + off); }
template<class R, class A1> static inline R vcall1(void* p, int off, A1 a1)
{ return ((R(__thiscall*)(void*, A1))g_vfn(p, off))(p, a1); }

// @ 0x00b159e0
void cTerrainCameraController::FUN_00b159e0(int n)
{
    FUN_00b148c0(0.0f, 0.0f, (float)n * m2a0, 0.0f);
    m13 = true;
    m294 = mCameraDistance.target;
}

// @ 0x00b15a20
// Resizes a vector<RunInfo> (stride 0x10) at this+0: grow via reserve helper, or
// shift the tail down with eastl::copy and shrink the end.
void cTerrainCameraController::FUN_00b15a20(unsigned n)
{
    char* v = (char*)this;
    unsigned cur = (unsigned)((*(char**)(v + 4) - *(char**)v) >> 4);
    if (cur < n)
    {
        char tmp[16];
        FUN_00b14370(*(void**)(v + 4), n - cur, tmp);
        return;
    }
    char* dst = *(char**)v + n * 16;
    char* e = *(char**)(v + 4);
    eastl_copy_runinfo(e, e, dst);
    *(char**)(v + 4) = e + ((e - dst) >> 4) * -16;
}

// @ 0x00b15a80
bool cTerrainCameraController::FUN_00b15a80(int delta, float x, float y, int flag)
{
    mInput.OnMouseWheel(delta, x, y, flag);
    if (flag == 0)
    {
        FUN_00b148c0(0.0f, 0.0f, (float)delta * m2a0, 0.0f);
        m294 = mCameraDistance.target;
        m13 = true;
    }
    return false;
}

// Rebuilds the four Hermite splines (distance, pitch, anchor direction, orientation) the
// terrain camera follows while a target is being approached. The mid knots of the distance and
// pitch splines are bent towards mTiltDistance / the maximum pitch by a smoothstep of the
// angle between the current and target anchor directions (scaled by the active sphere's size).
extern const float kMaxPitch;             // 0x0145d028
extern const float kMaxTiltAngle;         // 0x01567db4
extern const float kSlopeScale;           // 0x01567db0
Vector3* RotateTowards(Vector3* out, const Vector3* a, const Vector3* b, float t);   // 0x00b0fd00 cdecl
void SlerpOrientation(cSPQuaternion* out, const Vector3* p0, const Vector3* p1,
                      const cSPQuaternion* q0, const cSPQuaternion* q1);            // 0x00b12f90 cdecl

__forceinline float ClampF(float v, float lo, float hi)
{
    __asm {
        movss xmm0, v
        maxss xmm0, lo
        minss xmm0, hi
        movss v, xmm0
    }
    return v;
}

inline float DotWZYX(const cSPQuaternion& a, const cSPQuaternion& b)
{
    return ((a.w * b.w + a.z * b.z) + a.y * b.y) + b.x * a.x;
}
inline float DotYZWX(const cSPQuaternion& a, const cSPQuaternion& b)
{
    return ((a.y * b.y + a.z * b.z) + a.w * b.w) + a.x * b.x;
}
inline void Negate(cSPQuaternion& q)
{
    q.x = -q.x;
    q.y = -q.y;
    q.z = -q.z;
    q.w = -q.w;
}

// @ 0x00b15b00
void cTerrainCameraController::FUN_00b15b00()
{
    cTerrainSphere* sphere = GetActiveTerrainSphere();
    if (!sphere)
        return;

    float midDist = (mCameraDistance.current + mCameraDistance.target) * 0.5f;
    float midPitch = (mCameraPitch.current + mCameraPitch.target) * 0.5f;
    static float sMaxPitch = kMaxPitch;

    const Vector3& dirCur = mCameraAnchorDirection.current;
    const Vector3& dirTgt = mCameraAnchorDirection.target;
    float cosAngle = dirTgt.z * dirCur.z + dirTgt.y * dirCur.y + dirTgt.x * dirCur.x;
    cosAngle = ClampF(cosAngle, -1.0f, 1.0f);
    float angle = fabs((float)acos((double)cosAngle) * sphere->GetRadius());
    float minAngle = mTiltMinAngle;
    angle = ClampF(angle, minAngle, kMaxTiltAngle);
    float s = (angle - minAngle) / (kMaxTiltAngle - minAngle);
    s = ((3.0f - s * 2.0f) * s) * s;
    if (s == 0.0f) {
        mBallisticMotion = false;
        return;
    }
    midDist = (mTiltDistance - midDist) * s + midDist;
    midPitch = (sMaxPitch - midPitch) * s + midPitch;

    // distance spline
    mDistanceSpline.Clear();
    mDistanceSpline.times.resize(3);
    mDistanceSpline.times[0] = mCameraDistance.currentTime;
    mDistanceSpline.times[1] =
        (mCameraDistance.targetTime - mCameraDistance.currentTime) * 0.5f + mCameraDistance.currentTime;
    mDistanceSpline.times[2] = mCameraDistance.targetTime;
    mDistanceSpline.points.resize(3);
    mDistanceSpline.points[0] = mCameraDistance.current;
    mDistanceSpline.points[1] = midDist;
    mDistanceSpline.points[2] = mCameraDistance.target;
    mDistanceSpline.slopes.resize(3);
    mDistanceSpline.slopes[0] = mCameraDistance.velocity;
    mDistanceSpline.slopes[2] = mCameraDistance.targetVelocity;
    mDistanceSpline.ComputeSlopes();

    // pitch spline
    mPitchSpline.Clear();
    mPitchSpline.times.resize(5);
    mPitchSpline.times[0] = mCameraPitch.currentTime;
    mPitchSpline.times[1] = (mCameraPitch.targetTime - mCameraPitch.currentTime) * 0.15f + mCameraPitch.currentTime;
    mPitchSpline.times[2] = (mCameraPitch.targetTime - mCameraPitch.currentTime) * 0.5f + mCameraPitch.currentTime;
    mPitchSpline.times[3] = (mCameraPitch.targetTime - mCameraPitch.currentTime) * 0.85f + mCameraPitch.currentTime;
    mPitchSpline.times[4] = mCameraPitch.targetTime;
    mPitchSpline.points.resize(5);
    mPitchSpline.points[0] = mCameraPitch.current;
    mPitchSpline.points[1] = (midPitch - mCameraPitch.current) * 0.7f + mCameraPitch.current;
    mPitchSpline.points[2] = midPitch;
    mPitchSpline.points[3] = (midPitch - mCameraPitch.target) * 0.7f + mCameraPitch.target;
    mPitchSpline.points[4] = mCameraPitch.target;
    mPitchSpline.slopes.resize(5);
    mPitchSpline.slopes[0] = mCameraPitch.velocity;
    mPitchSpline.slopes[4] = mCameraPitch.targetVelocity;
    mPitchSpline.ComputeSlopes();

    // anchor direction spline
    mDirectionSpline.Clear();
    mDirectionSpline.times.resize(3);
    mDirectionSpline.times[0] = mCameraAnchorDirection.currentTime;
    mDirectionSpline.times[1] = (mCameraAnchorDirection.currentTime + mCameraAnchorDirection.targetTime) * 0.5f;
    mDirectionSpline.times[2] = mCameraAnchorDirection.targetTime;
    mDirectionSpline.points.resize(3);
    mDirectionSpline.points[0] = mCameraAnchorDirection.current;
    Vector3 tmp;
    mDirectionSpline.points[1] = *RotateTowards(&tmp, &mCameraAnchorDirection.current, &mCameraAnchorDirection.target, 0.5f);
    mDirectionSpline.points[2] = mCameraAnchorDirection.target;
    mDirectionSpline.slopes.resize(3);
    mDirectionSpline.slopes[0] = mCameraAnchorDirection.velocity;
    mDirectionSpline.slopes[2] = mCameraAnchorDirection.targetVelocity;
    mDirectionSpline.ComputeSlopes();
    float k = kSlopeScale;
    Vector3& dirSlope = mDirectionSpline.slopes[1];
    dirSlope.y = k * dirSlope.y;
    dirSlope.x = k * dirSlope.x;
    dirSlope.z = k * dirSlope.z;

    // orientation spline
    cSPQuaternion& q0 = mCameraAnchorOrientation.current;
    cSPQuaternion& q1 = mCameraAnchorOrientation.target;
    if (DotWZYX(q0, q1) < 0.0f)
        Negate(q1);
    __declspec(align(16)) cSPQuaternion goal;
    GetTargetOrientation(&goal);
    __declspec(align(16)) cSPQuaternion mid;
    SlerpOrientation(&mid, &mDirectionSpline.points[0], &mDirectionSpline.points[1], &q0, &goal);
    if (DotYZWX(q0, mid) < 0.0f)
        Negate(mid);
    mOrientationSpline.Clear();
    mOrientationSpline.times.resize(3);
    mOrientationSpline.times[0] = mCameraAnchorOrientation.currentTime;
    mOrientationSpline.times[1] = (mCameraAnchorOrientation.targetTime + mCameraAnchorOrientation.currentTime) * 0.5f;
    mOrientationSpline.times[2] = mCameraAnchorOrientation.targetTime;
    mOrientationSpline.points.resize(3);
    mOrientationSpline.points[0] = q0;
    mOrientationSpline.points[1] = mid;
    mOrientationSpline.points[2] = q1;
    mOrientationSpline.slopes.resize(3);
    mOrientationSpline.slopes[0] = mCameraAnchorOrientation.velocity;
    mOrientationSpline.slopes[2] = mCameraAnchorOrientation.targetVelocity;
    mOrientationSpline.ComputeSlopes();
    cSPQuaternion& oSlope = mOrientationSpline.slopes[1];
    oSlope.y = k * oSlope.y;
    oSlope.z = k * oSlope.z;
    oSlope.w = k * oSlope.w;
    oSlope.x = k * oSlope.x;
}

// @ 0x00b16270
void cTerrainCameraController::FUN_00b16270()
{
    char* self = (char*)this;
    if (*(char*)(self + 0x390) != 0) return;
    if (*(char*)(self + 0x3c) == 0) return;
    float t = FUN_00b0f880(self);
    *(char*)(self + 0x168) = 1;
    *(float*)(self + 0x44) = t;
    *(float*)(self + 0x84) = *(float*)(self + 0x84) * 0.0f;
    *(float*)(self + 0x88) = *(float*)(self + 0x88) * 0.0f;
    *(float*)(self + 0x8c) = *(float*)(self + 0x8c) * 0.0f;
    *(int*)(self + 0x60) = *(int*)(self + 0x6c);
    *(int*)(self + 0x64) = *(int*)(self + 0x70);
    *(int*)(self + 0x68) = *(int*)(self + 0x74);
    *(float*)(self + 0x40) = 0.0f;
    *(char*)(self + 0x3c) = 0;
    *(float*)(self + 0x104) = t;
    *(int*)(self + 0x110) = *(int*)(self + 0x114);
    *(float*)(self + 0x100) = 0.0f;
    *(char*)(self + 0xfc) = 0;
    *(float*)(self + 0x11c) = *(float*)(self + 0x11c) * 0.0f;
    *(int*)(self + 0x134) = *(int*)(self + 0x138);
    *(float*)(self + 0x128) = t;
    *(float*)(self + 0x124) = 0.0f;
    *(char*)(self + 0x120) = 0;
    *(float*)(self + 0x140) = *(float*)(self + 0x140) * 0.0f;
    *(float*)(self + 0x98) = t;
    *(float*)(self + 0xec) = *(float*)(self + 0xec) * 0.0f;
    *(float*)(self + 0xf0) = *(float*)(self + 0xf0) * 0.0f;
    *(float*)(self + 0xf4) = *(float*)(self + 0xf4) * 0.0f;
    *(float*)(self + 0xf8) = *(float*)(self + 0xf8) * 0.0f;
    *(int*)(self + 0xbc) = *(int*)(self + 0xcc);
    *(int*)(self + 0xc0) = *(int*)(self + 0xd0);
    *(int*)(self + 0xc4) = *(int*)(self + 0xd4);
    *(int*)(self + 0xc8) = *(int*)(self + 0xd8);
    *(float*)(self + 0x94) = 0.0f;
    *(char*)(self + 0x90) = 0;
    FUN_00b15b00();
    if (*(char*)(self + 0x18) != 0)
    {
        *(int*)(self + 0x2c) = *(int*)(self + 0x30);
        *(float*)(self + 0x20) = t;
        *(float*)(self + 0x38) = *(float*)(self + 0x38) * 0.0f;
        *(float*)(self + 0x1c) = 0.0f;
        *(char*)(self + 0x18) = 0;
    }
    *(char*)(self + 0x3d) = 0;
    *(char*)(self + 0x19) = 0;
    *(char*)(self + 0x91) = 0;
}

// @ 0x00b16450
void FUN_00b16450(float* v, int* list)
{
    if (list[0] != list[1])
    {
        float x = *(float*)((char*)list + 0x38);
        float y = *(float*)((char*)list + 0x3c);
        float z = *(float*)((char*)list + 0x40);
        v[0] += x;
        v[1] += y;
        v[2] += z;
    }
}

// @ 0x00b16490
void FUN_00b16490(float* v, float add)
{
    float x = v[0], y = v[1], z = v[2];
    float len = sqrtf(z * z + (y * y + x * x));
    float inv = 1.0f / len;
    float s = len + add;
    v[0] = x * inv * s;
    v[1] = y * inv * s;
    v[2] = z * inv * s;
}

// @ 0x00b16520
bool FUN_00b16520(int* world, float* a, float* b, bool flag, float* out)
{
    void* gw = GonzagoModelWorld_00b3d520();
    if (gw) vcall1<void, int>(gw, 0x0, 0);
    int h = vcall1<int, int>(world, 0xac, 0);
    if (!gw) return false;
    if (h)
    {
        char ok = vcall1<char, int>(gw, 0x44, 0);
        if (ok)
        {
            out[0] = a[0] + (b[0] - a[0]) * (float)h;
            out[1] = a[1] + (b[1] - a[1]) * (float)h;
            out[2] = a[2] + (b[2] - a[2]) * (float)h;
            vcall1<void, int>(gw, 0x4, 0);
            return true;
        }
    }
    vcall1<void, int>(gw, 0x4, 0);
    return false;
}