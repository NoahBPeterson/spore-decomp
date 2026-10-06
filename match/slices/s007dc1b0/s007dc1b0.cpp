// Slice s007dc1b0 (w2g5 slice 21).  Region: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast.
// SP::cSmoothCameraController: zoom/query, request dispatch, viewer
// orientation/position math and the destructor.
#include "types.h"
#include <math.h>

struct cSPVector3 { float x, y, z; };
struct cSPQuaternion { float x, y, z, w; };
struct tLerpAngle   { float mCurrent; float mTarget; uint32_t mSteps; float mMinChange; };
struct tLerpScalar  { float mCurrent; float mTarget; uint32_t mSteps; float mMinChange; };
struct tLerpVector3 { cSPVector3 mCurrent; cSPVector3 mTarget; uint32_t mSteps; float mMinChange; };
struct tLerpQuaternion { cSPQuaternion mCurrent; cSPQuaternion mTarget; uint32_t mSteps; float mMinChange; };
struct tSavedCameraPosition {
    bool mValid; int mCurrentZoomLevel; float mDistance; int mCurrentOrientation;
    float mHeading, mNearClip, mFarClip, mFOV, mPitchParam;
    cSPVector3 mSubjectPosition; int mFloorLevel, mWallMode;
};
struct Vec16 { void* mpBegin; void* mpEnd; void* mpCapacity; void* mAlloc; };

struct cSmoothCameraController {
    void* mVtbl; char mPad04[0xc]; void* mConfig;
    Vec16 mEdgeConstraints; int mCurrentZoomLevel; float mContinuousZoomDistance;
    Vec16 mZoomLevels; Vec16 mNearClipPlanes; Vec16 mFarClipPlanes;
    Vec16 mMinPitches; Vec16 mMaxPitches; float mViewSlope;
    tLerpAngle mBufferedHeading; tLerpScalar mBufferedDistanceAlongCurve;
    tLerpScalar mBufferedNearClip; tLerpScalar mBufferedFarClip;
    tLerpScalar mBufferedFOV; tLerpScalar mBufferedPitchParam;
    tLerpVector3 mBufferedSubjectPosition; tLerpVector3 mBufferedLookAtPosition;
    Vec16 mFOVLevels; Vec16 mOrientations; int mCurrentOrientation;
    cSPVector3 mDraggedVelocity; uint32_t mPositionInterpolationSteps;
    float mTranslationInputVelocity; cSPVector3 mxyzSubjectOffset;
    tLerpQuaternion mRelativeOrientation; float mHeadingRelative;
    bool mTracking; bool mReadFromStream; bool mAdjustablePitch; bool mbInModalDialogLoop;
    int mStartMouseWheelLevel;
    tLerpScalar mKeyboardRotation; tLerpScalar mKeyboardZoomDelta;
    tLerpVector3 mKeyboardTranslation;
    float mKeyboardRotationSpeed, mKeyboardZoomSpeed, mKeyboardZoomScale, mKeyboardTranslationSpeed;
    tSavedCameraPosition mCameraPositions[7];
    float mSubjectTrackingDeadZoneMagnitude, mRotationPitchRatioMax, mCameraPitchScaling;
    float mContinuousRotationScaling, mMaxRotationDelta;

    float Zoom();                                   // 007dc1b0
    bool ZoomRange(float* lo, float* hi);           // 007dc230
    void UpdateSubjectMotion(float dt);             // 007dc260
    bool HandleRequest(int id);                     // 007dc340
    void ZoomInterpolationParamsFromDistanceAlongCurve
        (uint32_t* a, uint32_t* b, float* t, float d);  // 007dc510
    float ConstrainDistanceAlongCurve(float d);     // 007dc5e0
    ~cSmoothCameraController();                     // 007dc630
    void OnUpdateTargetSet();                       // 007dca30
    void ViewerPositionAndOrientationFromDistanceAlongCurve
        (float* pos, float* quat, float d, int flag);  // 007dcc30
};

// A quaternion multiply helper sitting between the camera methods.
void FUN_007dcb00(float* out, const float* a, const float* b)
{
    float b1 = b[1], b2 = b[2], a1 = a[1], a2 = a[2];
    float b0 = b[0], a0 = a[0], b3 = b[3], a3 = a[3];
    out[2] = (a3 * b2 + b3 * a2) + (a0 * b1 - b0 * a1);
    out[0] = (a3 * b0 + b3 * a0) + (b2 * a1 - b1 * a2);
    out[1] = (a3 * b1 + b3 * a1) + (b0 * a2 - b2 * a0);
    out[3] = a3 * b3 - ((b0 * a0 + b2 * a2) + b1 * a1);
}

// ===========================================================================
// 0x007dc1b0  Zoom
// ===========================================================================
float cSmoothCameraController::Zoom()
{
    float* end = (float*)mZoomLevels.mpEnd;
    float* cap = (float*)mZoomLevels.mpCapacity;
    if (end == cap)
        return 1.0f;
    float range = fabsf(end[0] - cap[-1]);
    if (range == 0.0f)
        return 1.0f;
    float t = (float)mBufferedNearClip.mSteps;
    if (end[0] <= t && t != end[0])
        return 0.0f;
    float c = cap[-1];
    if (c <= t)
        return 1.0f - (t - c) / range;
    return 1.0f;
}

// ===========================================================================
// 0x007dc230  ZoomRange
// ===========================================================================
bool cSmoothCameraController::ZoomRange(float* lo, float* hi)
{
    if (mZoomLevels.mpEnd == mZoomLevels.mpCapacity)
        return false;
    *lo = ((float*)mZoomLevels.mpCapacity)[-1];
    *hi = ((float*)mZoomLevels.mpEnd)[0];
    return true;
}

// ===========================================================================
// 0x007dc260  UpdateSubjectMotion
// ===========================================================================
void cSmoothCameraController::UpdateSubjectMotion(float dt)
{
    float z = mRelativeOrientation.mCurrent.z;
    float y = mRelativeOrientation.mCurrent.y;
    float x = mRelativeOrientation.mCurrent.x;
    if (sqrtf(x * x + y * y + z * z) > 0.001f) {
        float s = (float)(int)mRelativeOrientation.mCurrent.w;
        if ((int)mRelativeOrientation.mCurrent.w < 0)
            s = s + 4294967296.0f;
        cSPVector3 v;
        v.x = mBufferedSubjectPosition.mSteps + x * s;
        v.y = mBufferedSubjectPosition.mMinChange + y * s;
        v.z = mBufferedLookAtPosition.mCurrent.x + z * s;
        ((void(__thiscall*)(void*, void*))(((void**)*(void**)this)[0xb8 / 4]))(this, &v);
    } else {
        ((void(__thiscall*)(void*, void*))(((void**)*(void**)this)[0xb8 / 4]))(
            this, &mBufferedLookAtPosition.mCurrent);
    }
    (void)dt;
}

// ===========================================================================
// 0x007dc340  HandleRequest
// ===========================================================================
bool cSmoothCameraController::HandleRequest(int id)
{
    void** vt = *(void***)this;
    if (id == 0x2ca2978b) {
        mKeyboardTranslation.mCurrent.y = 0.0f;
        return true;
    }
    if (id == 0x0101b527) {
        float f = ((float*)mZoomLevels.mpEnd)[mCurrentZoomLevel];
        ((void(__thiscall*)(void*, float))vt[0xd4 / 4])(this, f);
        return true;
    }
    if (id == 0x0101b52d) return true;
    if (id == 0x0101b52f) return true;
    if (id == 0x2ca298e9) {
        ((void(__thiscall*)(void*, int))vt[0x74 / 4])(this, mCurrentZoomLevel - 1);
        return true;
    }
    if (id == 0xcca2977c) {
        ((void(__thiscall*)(void*, int))vt[0x74 / 4])(
            this, (int)(((char*)mZoomLevels.mpCapacity - (char*)mZoomLevels.mpEnd) >> 2) - 1);
        return true;
    }
    if (id == 0xcca298c4) {
        ((void(__thiscall*)(void*, int))vt[0x74 / 4])(this, mCurrentZoomLevel + 1);
        return true;
    }
    return false;
}

// ===========================================================================
// 0x007dc510  ZoomInterpolationParamsFromDistanceAlongCurve
// ===========================================================================
void cSmoothCameraController::ZoomInterpolationParamsFromDistanceAlongCurve
    (uint32_t* a, uint32_t* b, float* t, float d)
{
    int n = (int)(((char*)mZoomLevels.mpCapacity - (char*)mZoomLevels.mpEnd) >> 2);
    if (n < 2) {
        *a = 0; *b = 0; *t = 0.0f;
        return;
    }
    uint32_t i = 0;
    if (n != 0) {
        float* p = (float*)mZoomLevels.mpEnd;
        while (*p > d) {
            i++;
            p++;
            if (i >= (uint32_t)n)
                break;
        }
        if (i != 0)
            i--;
    }
    uint32_t j = i + 1;
    if ((uint32_t)n <= j)
        j = n - 1;
    float* p = (float*)mZoomLevels.mpEnd;
    float v = p[i];
    float r = (v - d) / (v - p[j]);
    if (r < 0.0f || r > 1.0f)
        r = 1.0f;
    *a = i; *b = j; *t = r;
}

// ===========================================================================
// 0x007dc5e0  ConstrainDistanceAlongCurve
// ===========================================================================
float cSmoothCameraController::ConstrainDistanceAlongCurve(float d)
{
    float* begin = (float*)mZoomLevels.mpBegin;
    int n = (int)(((char*)mZoomLevels.mpEnd - (char*)mZoomLevels.mpBegin) >> 2);
    float lo = begin[n - 1];
    float hi = begin[0];
    if (d < lo) d = lo;
    if (d > hi) d = hi;
    return d;
}

// ===========================================================================
// 0x007dc630  ~cSmoothCameraController
// ===========================================================================
void EFreeCam(void*);   // 0x00f47380

// ===========================================================================
// 0x007dc7b0  ViewerOrientationFromPositionAndLookAt  (partial)
// ===========================================================================
void ViewerOrientationFromPositionAndLookAt(const float* pos, const float* look,
                                            const float* up, float* out)
{
    float dx = look[0] - pos[0];
    float dy = look[1] - pos[1];
    float dz = look[2] - pos[2];
    (void)up; (void)dx; (void)dy; (void)dz;
    out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 1.0f;
}

// ===========================================================================
// 0x007dcc30  ViewerPositionAndOrientationFromDistanceAlongCurve  (partial)
// ===========================================================================
void cSmoothCameraController::ViewerPositionAndOrientationFromDistanceAlongCurve
    (float* pos, float* quat, float d, int flag)
{
    float* src = flag ? &mBufferedLookAtPosition.mCurrent.x : &mBufferedSubjectPosition.mCurrent.x;
    pos[0] = src[0];
    pos[1] = src[1];
    pos[2] = src[2];
    quat[0] = 0.0f; quat[1] = 0.0f; quat[2] = 0.0f; quat[3] = 1.0f;
    (void)d;
}

cSmoothCameraController::~cSmoothCameraController()
{
    void* v;
    v = mFOVLevels.mpCapacity;
    if (v && ((int*)v)[-1]) EFreeCam(v);
    v = mOrientations.mpCapacity;
    if (v && ((int*)v)[-1]) EFreeCam(v);
    v = mEdgeConstraints.mpBegin;
    if (v && ((int*)v)[-1]) EFreeCam(v);
    v = mMaxPitches.mpBegin;
    if (v && ((int*)v)[-1]) EFreeCam(v);
    v = mFarClipPlanes.mpBegin;
    if (v && ((int*)v)[-1]) EFreeCam(v);
    v = mNearClipPlanes.mpBegin;
    if (v && ((int*)v)[-1]) EFreeCam(v);
    v = mZoomLevels.mpBegin;
    if (v && ((int*)v)[-1]) EFreeCam(v);
    v = mConfig;
    if (v) ((void(__thiscall*)(void*))(((void**)*(void**)v)[1]))(v);
}

// ===========================================================================
// 0x007dca30  OnUpdateTargetSet
// ===========================================================================
void cSmoothCameraController::OnUpdateTargetSet()
{
    if (!mAdjustablePitch) {
        mBufferedSubjectPosition.mSteps = 0;
        mBufferedLookAtPosition.mCurrent.y = 0.0f;
        mBufferedSubjectPosition.mMinChange = 0.0f;
        mBufferedLookAtPosition.mCurrent.z = 0.0f;
        mBufferedLookAtPosition.mCurrent.x = 0.0f;
        mBufferedLookAtPosition.mTarget.x = 0.0f;
    }
    void** vt = *(void***)this;
    float* end = (float*)mZoomLevels.mpEnd;
    if (end != (float*)mZoomLevels.mpCapacity) {
        mBufferedDistanceAlongCurve.mSteps = *(uint32_t*)end;
        mBufferedDistanceAlongCurve.mMinChange = *end;
    }
    ((void(__thiscall*)(void*, float))vt[0x74 / 4])(this, mContinuousZoomDistance);
}
