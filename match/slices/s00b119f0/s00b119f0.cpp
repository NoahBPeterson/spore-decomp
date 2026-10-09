// SP::cTerrainCameraController::UpdateInterpolation (0x00b119f0, 3732 bytes; name guessed).
// Per-frame camera update: smooths the pre-rotate angles, re-targets the six
// cInterpolationData blocks whose target changed (timing from InterpByAngle), then advances each
// block either along its Hermite segment (Bezier/Hermite helpers) or, in ballistic mode, along
// the precomputed spline, and finally clears mBallisticMotion when no spline was used.
// Layout: 2008 PDB SP::cTerrainCameraController up to +0x16c; the retail splines are 0x3c bytes,
// so everything after them sits 0x30 bytes later than in the PDB (mLastDeltaTime +0x22c -> +0x25c).
//
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& o) : x(o.x), y(o.y), z(o.z) {}
    float Dot(const cSPVector3& o) const { return x * o.x + y * o.y + z * o.z; }
    float LengthSq() const { return x * x + y * y + z * z; }
    cSPVector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
    float Normalize() { float len = sqrtf(LengthSq()); float inv = 1.0f / len; x *= inv; y *= inv; z *= inv; return len; }
    bool operator==(const cSPVector3& o) const { return x == o.x && y == o.y && z == o.z; }
};
inline cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b) { return cSPVector3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline cSPVector3 operator*(const cSPVector3& a, float s) { return cSPVector3(a.x * s, a.y * s, a.z * s); }
inline cSPVector3 operator*(float s, const cSPVector3& a) { return cSPVector3(s * a.x, s * a.y, s * a.z); }

struct cSPQuaternion {
    float x, y, z, w;
    cSPQuaternion() {}
    cSPQuaternion(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
    cSPQuaternion(const cSPQuaternion& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
    float Dot(const cSPQuaternion& o) const { return x * o.x + y * o.y + z * o.z + w * o.w; }
    float LengthSq() const { return x * x + y * y + z * z + w * w; }
    cSPQuaternion& operator*=(float s) { x *= s; y *= s; z *= s; w *= s; return *this; }
    float Normalize() { float len = sqrtf(LengthSq()); float inv = 1.0f / len; x *= inv; y *= inv; z *= inv; w *= inv; return len; }
};
inline cSPQuaternion operator-(const cSPQuaternion& a, const cSPQuaternion& b) { return cSPQuaternion(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
inline cSPQuaternion operator*(const cSPQuaternion& a, float s) { return cSPQuaternion(a.x * s, a.y * s, a.z * s, a.w * s); }
inline cSPQuaternion operator*(float s, const cSPQuaternion& a) { return cSPQuaternion(s * a.x, s * a.y, s * a.z, s * a.w); }

extern const cSPVector3 kZeroVector;          // 0x0167bbf8
extern const cSPQuaternion kZeroQuaternion;   // 0x0167bc04

template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

float Lerp(float from, float to, float t);   // 0x00b0f0c0
float BezierEval(float* current, float* velocity, const float* end, const float* targetVelocity,
                 float remaining, float dt);   // 0x00b0fc40
cSPVector3 HermiteEval(const cSPVector3* current, const cSPVector3* velocity, const cSPVector3* end,
                       const cSPVector3* targetVelocity, float remaining, float dt);   // 0x00b10e50
cSPQuaternion HermiteEval(const cSPQuaternion* current, const cSPQuaternion* velocity, const cSPQuaternion* end,
                          const cSPQuaternion* targetVelocity, float remaining, float dt);   // 0x00b11160

namespace SP {

template <class T> struct cHermiteSplineInterpolation {   // retail size 0x3c
    T Evaluate(float t);                                   // 0x0069a5f0 / 0x0069a9a0 / 0x0069aee0
    uint32_t data[15];
};

class cTerrainMapSet {
public:
    float GetHeightAt(const cSPVector3& pos);              // 0x00f927c0
};

class cDistGrid {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual cTerrainMapSet* GetTerrainMapSet();            // slot 3 (+0xc)
};
cDistGrid* GetDistGrid();                                  // 0x00f48aa0

class cTerrainCameraController {
public:
    template <class T> struct cInterpolationData {
        bool targetChanged;         // +0x0
        bool targetMoving;          // +0x1
        float currentTime;          // +0x4
        float targetTime;           // +0x8
        T start;
        T current;
        T end;
        T target;
        T velocity;
        T targetVelocity;

        void Retarget(float time)
        {
            targetTime = time;
            targetVelocity *= 0.0f;
            end = target;
            currentTime = 0.0f;
            targetChanged = false;
        }
    };

    float InterpByAngle();                                 // 0x00b0f880
    void UpdateInterpolation(float deltaTime);

    void* vtbl;                                            // +0x0 (cICameraController)
    uint32_t base[3];                                      // +0x4
    bool mDoEdgeScroll;                                    // +0x10
    bool mMouseScrollIsActive;
    bool mStopCameraTarget;
    bool mUIZoomIn;
    bool mUIZoomOut;
    bool mUIRotateR;
    bool mUIRotateL;
    cInterpolationData<float> mCameraAnchorRadius;               // +0x18
    cInterpolationData<cSPVector3> mCameraAnchorDirection;       // +0x3c
    cInterpolationData<cSPQuaternion> mCameraAnchorOrientation;  // +0x90
    cInterpolationData<float> mCameraDistance;                   // +0xfc
    cInterpolationData<float> mCameraPitch;                      // +0x120
    cInterpolationData<float> mCameraYaw;                        // +0x144
    bool mBallisticMotion;                                       // +0x168
    bool mAltZoomMode;                                           // +0x169
    cHermiteSplineInterpolation<float> mDistanceSpline;          // +0x16c
    cHermiteSplineInterpolation<float> mPitchSpline;             // +0x1a8
    cHermiteSplineInterpolation<cSPVector3> mDirectionSpline;    // +0x1e4
    cHermiteSplineInterpolation<cSPQuaternion> mOrientationSpline; // +0x220
    float mLastDeltaTime;                                        // +0x25c
    float mLastZoomEffort;                                       // +0x260
    float mTargetCameraPreRotateX;                               // +0x264
    float mTargetCameraPreRotateZ;                               // +0x268
    float mCurrentCameraPreRotateX;                              // +0x26c
    float mCurrentCameraPreRotateZ;                              // +0x270
    float mCurrentCameraHeightAboveWater;                        // +0x274
    float mAnchorInterpolationTime;                              // +0x278
    float mOrientationInterpolationTime;                         // +0x27c
    float mThetaInterpolationTime;                               // +0x280
    float mPhiInterpolationTime;                                 // +0x284
    float mDistanceInterpolationTime;                            // +0x288
};

static const float kSettleEpsilon = 1.5258789e-05f;   // 2^-16

void cTerrainCameraController::UpdateInterpolation(float deltaTime)
{
    const float kDecay = -0.30103f;
    float preRotateBlend = 1.0f - expf(deltaTime / mOrientationInterpolationTime * kDecay);
    float distanceBlend = 1.0f - expf(deltaTime / mDistanceInterpolationTime * kDecay);
    mCurrentCameraPreRotateX = Lerp(mCurrentCameraPreRotateX, mTargetCameraPreRotateX, preRotateBlend);
    mCurrentCameraPreRotateZ = Lerp(mCurrentCameraPreRotateZ, mTargetCameraPreRotateZ, preRotateBlend);

    if (!mBallisticMotion) {
        float time = -1.0f;
        if (mCameraAnchorDirection.targetChanged) {
            time = InterpByAngle();
            mCameraAnchorDirection.Retarget(time);
            if (mCameraAnchorDirection.targetVelocity == kZeroVector)
                mCameraAnchorDirection.targetTime = time;
            mCameraAnchorDirection.targetMoving = false;
            mCameraAnchorRadius.targetMoving = false;
            mCameraAnchorOrientation.targetMoving = false;
        }
        if (mCameraDistance.targetChanged) {
            if (time < 0.0f)
                time = InterpByAngle();
            mCameraDistance.Retarget(time);
            mCameraDistance.targetVelocity = 0.0f;
        }
        if (mCameraPitch.targetChanged)
            mCameraPitch.Retarget(0.65f);
        if (mCameraYaw.targetChanged)
            mCameraYaw.Retarget(0.2f);
        if (mCameraAnchorRadius.targetChanged) {
            if (time < 0.0f)
                time = InterpByAngle();
            mCameraAnchorRadius.Retarget(time);
        }
        if (mCameraAnchorOrientation.targetChanged) {
            if (time < 0.0f)
                time = InterpByAngle();
            mCameraAnchorOrientation.Retarget(time * 1.12f);
        }
    }

    bool finished = true;

    // anchor direction
    if (mCameraAnchorDirection.currentTime < mCameraAnchorDirection.targetTime) {
        cInterpolationData<cSPVector3>& d = mCameraAnchorDirection;
        float t = d.currentTime + deltaTime;
        d.currentTime = t;
        cSPVector3 old = d.current;
        if (mBallisticMotion) {
            d.current = mDirectionSpline.Evaluate(t);
            finished = false;
        } else {
            float k = (d.targetMoving || d.targetVelocity.LengthSq() > kSettleEpsilon) ? 1.0f : 0.95f;
            float remaining = (d.targetTime - t) * k;
            d.current = HermiteEval(&d.current, &d.velocity, &d.end, &d.targetVelocity,
                                    Max(deltaTime, remaining), deltaTime);
        }
        d.current.Normalize();
        float rdt = 1.0f / deltaTime;
        d.velocity = (d.current - old) * rdt;
        d.velocity = d.velocity - d.current * d.current.Dot(d.velocity);
    } else {
        mCameraAnchorDirection.velocity = kZeroVector;
        mCameraAnchorDirection.targetVelocity = kZeroVector;
    }

    // anchor orientation
    if (mCameraAnchorOrientation.currentTime < mCameraAnchorOrientation.targetTime) {
        cInterpolationData<cSPQuaternion>& d = mCameraAnchorOrientation;
        float t = d.currentTime + deltaTime;
        d.currentTime = t;
        cSPQuaternion old = d.current;
        if (mBallisticMotion) {
            d.current = mOrientationSpline.Evaluate(t);
            finished = false;
        } else {
            cSPQuaternion& end = d.end;
            if (d.current.w * end.w + d.current.z * end.z + d.current.y * end.y + d.current.x * end.x < 0.0f) {
                end.x = -end.x;
                end.y = -end.y;
                end.z = -end.z;
                end.w = -end.w;
            }
            float k = (d.targetMoving || d.targetVelocity.LengthSq() > kSettleEpsilon) ? 1.0f : 0.95f;
            float remaining = (d.targetTime - d.currentTime) * k;
            d.current = HermiteEval(&d.current, &d.velocity, &end, &d.targetVelocity,
                                    Max(deltaTime, remaining), deltaTime);
        }
        d.current.Normalize();
        float rdt = 1.0f / deltaTime;
        d.velocity = (d.current - old) * rdt;
        d.velocity = d.velocity - d.current * d.current.Dot(d.velocity);
    } else {
        mCameraAnchorOrientation.velocity = kZeroQuaternion;
        mCameraAnchorOrientation.targetVelocity = kZeroQuaternion;
    }

    // distance
    if (mCameraDistance.currentTime < mCameraDistance.targetTime) {
        cInterpolationData<float>& d = mCameraDistance;
        float t = d.currentTime + deltaTime;
        d.currentTime = t;
        float old = d.current;
        if (mBallisticMotion) {
            d.current = mDistanceSpline.Evaluate(t);
            finished = false;
        } else {
            float k = (d.targetMoving || fabsf(d.targetVelocity) > kSettleEpsilon) ? 1.0f : 0.95f;
            float remaining = (d.targetTime - t) * k;
            d.current = BezierEval(&d.current, &d.velocity, &d.end, &d.targetVelocity,
                                   Max(deltaTime, remaining), deltaTime);
        }
        d.velocity = (d.current - old) / deltaTime;
    } else {
        float end = mCameraDistance.end;
        mCameraDistance.velocity = 0.0f;
        mCameraDistance.targetVelocity = 0.0f;
        float cur = mCameraDistance.current;
        if (fabsf(end - cur) > kSettleEpsilon)
            mCameraDistance.current = (end - cur) * distanceBlend + cur;
        else
            mCameraDistance.current = end;
    }

    // pitch
    if (mCameraPitch.currentTime < mCameraPitch.targetTime) {
        cInterpolationData<float>& d = mCameraPitch;
        float t = d.currentTime + deltaTime;
        d.currentTime = t;
        float old = d.current;
        if (mBallisticMotion) {
            d.current = mPitchSpline.Evaluate(t);
            finished = false;
        } else {
            float k = (d.targetMoving || fabsf(d.targetVelocity) > kSettleEpsilon) ? 1.0f : 0.95f;
            float remaining = (d.targetTime - t) * k;
            d.current = BezierEval(&d.current, &d.velocity, &d.end, &d.targetVelocity,
                                   Max(deltaTime, remaining), deltaTime);
        }
        d.velocity = (d.current - old) / deltaTime;
    } else {
        mCameraPitch.velocity = 0.0f;
        mCameraPitch.targetVelocity = 0.0f;
    }

    // yaw (never ballistic)
    if (mCameraYaw.currentTime < mCameraYaw.targetTime) {
        cInterpolationData<float>& d = mCameraYaw;
        float t = d.currentTime + deltaTime;
        d.currentTime = t;
        float old = d.current;
        float k = (d.targetMoving || fabsf(d.targetVelocity) > kSettleEpsilon) ? 1.0f : 0.95f;
        float remaining = (d.targetTime - t) * k;
        d.current = BezierEval(&d.current, &d.velocity, &d.end, &d.targetVelocity,
                               Max(deltaTime, remaining), deltaTime);
        d.velocity = (d.current - old) / deltaTime;
    } else {
        mCameraYaw.velocity = 0.0f;
        mCameraYaw.targetVelocity = 0.0f;
    }

    // anchor radius: never below the terrain under the anchor
    if (mCameraAnchorRadius.currentTime < mCameraAnchorRadius.targetTime) {
        cInterpolationData<float>& d = mCameraAnchorRadius;
        float end = d.end;
        if (!mBallisticMotion) {
            cDistGrid* grid = GetDistGrid();
            if (grid) {
                float height = grid->GetTerrainMapSet()->GetHeightAt(mCameraAnchorDirection.current);
                end = Max(height, end);
            }
        }
        float old = d.current;
        float t = d.currentTime + deltaTime;
        float remaining = d.targetTime - t;
        d.currentTime = t;
        d.current = BezierEval(&d.current, &d.velocity, &end, &d.targetVelocity,
                               Max(deltaTime, remaining), deltaTime);
        d.velocity = (d.current - old) / deltaTime;
    } else {
        mCameraAnchorRadius.velocity = 0.0f;
        mCameraAnchorRadius.targetVelocity = 0.0f;
    }

    mLastDeltaTime = deltaTime;
    if (finished)
        mBallisticMotion = false;
}

}  // namespace SP
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
