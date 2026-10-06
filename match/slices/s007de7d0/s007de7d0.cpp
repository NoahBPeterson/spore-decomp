// Slice s007de7d0 (w2g5 slice 24): SP::cSmoothCameraController reset / pitch / edge / ctor / factory
// plus the (byte-exact) Cam24 zoom/clip setters.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE2 /fp:fast
#include "types.h"
#include "../s007dd880/s007dd880.h"

// ---- Cam24: minimal view used by the two byte-exact setters (vtable slots 0x70 / 0x78) ----
struct FVec { void* b; void* e; void* c; void* a; FVec& operator=(const FVec&); };

struct Cam24 {
    char pad0[0x30];        // +0x00
    FVec mZoomLevels;       // +0x30
    char pad1[4];           // +0x40
    FVec mNearClip;         // +0x44
    char pad2[4];           // +0x54
    FVec mFarClip;          // +0x58
    char pad3[0x138 - 0x68];// +0x68
    FVec mOrientations;     // +0x138

    void SetZoomLevels(const FVec& a, const FVec& b);   // 007df6a0
    void SetClipPlanes(const FVec& a, const FVec& b);   // 007df6d0
};

void Cam24::SetZoomLevels(const FVec& a, const FVec& b)
{
    mZoomLevels = a;
    mOrientations = b;
}

void Cam24::SetClipPlanes(const FVec& a, const FVec& b)
{
    mNearClip = a;
    mFarClip = b;
}

// ---- constants ----
static const float kDegToRad = 0.017453292f;
static inline float F(unsigned bits) { union { unsigned u; float f; } x; x.u = bits; return x.f; }

extern Vec3 g_kVec3Zero3;     // 0x016389dc (3-float constant triple)
extern Quat g_kQuatIdent;     // 0x0153f058 (identity quaternion)
extern const float g_kPiOver6; // 0x0153f194 (0.5235988)
extern const float g_kPiOver4; // 0x0153f198 (0.7853982)

// EA 6-argument operator new / matching delete (EA "App" allocator)
void* __cdecl operator new(size_t size, const char* pName, int flags, int dbgFlags, int file, int line);
void  __cdecl operator delete(void*, const char*, int, int, int, int);

// @ 0x007df230  SP::cSmoothCameraController::SetPitchAngles
void cSmoothCameraController::SetPitchAngles(const FloatVec& minDeg, const FloatVec& maxDeg)
{
    mMinPitches.erase_all();
    mMaxPitches.erase_all();
    int n = (int)minDeg.size();
    for (int i = 0; i < n; ++i) {
        mMinPitches.push_back(minDeg.mpBegin[i] * kDegToRad);
        mMaxPitches.push_back(maxDeg.mpBegin[i] * kDegToRad);
    }
}

// @ 0x007df330  edge-constraint ramp setter (vtable slot 0xac)
void cSmoothCameraController::SetEdgeConstraints(float a, float b, float c, float d)
{
    if (a + c < 1.0f && b + d < 1.0f) {
        mEdgeConstraints.erase_all();
        mEdgeConstraints.push_back(a);
        mEdgeConstraints.push_back(b);
        mEdgeConstraints.push_back(c);
        mEdgeConstraints.push_back(d);
    }
}

// @ 0x007de7d0  SP::cSmoothCameraController::Reset
void cSmoothCameraController::Reset()
{
    mKeyboardRotation.mTarget = 0.0f;
    mKeyboardRotation.mCurrent = 0.0f;
    mKeyboardRotation.mMinChange = 0.05f;
    mKeyboardRotationSpeed = 5.0f;
    mKeyboardRotation.mSteps = 20;
    mKeyboardTranslation.mTarget = g_kVec3Zero3;
    mKeyboardTranslation.mCurrent = g_kVec3Zero3;
    mKeyboardTranslationSpeed = 0.0f;
    mKeyboardZoomDelta.mTarget = 0.0f;
    mKeyboardZoomDelta.mCurrent = 0.0f;
    mKeyboardTranslation.mMinChange = 0.05f;
    mKeyboardTranslation.mSteps = 20;
    mKeyboardZoomDelta.mMinChange = 0.05f;
    mKeyboardZoomDelta.mSteps = 20;
    mKeyboardZoomSpeed = 5.0f;
    mKeyboardZoomScale = 1.0f;
    v26_Unk(0);

    mxyzSubjectOffset = g_kVec3Zero3;
    mViewSlope = 0.7f;
    mStartMouseWheelLevel = 0;
    mDraggedVelocity = g_kVec3Zero3;
    mBufferedHeading.mTarget = g_kPiOver4;
    mPositionInterpolationSteps = 7;
    mTranslationInputVelocity = 1.0f;
    mReadFromStream = false;
    mbInModalDialogLoop = false;
    mBufferedSubjectPosition.mSteps = 7;
    mBufferedSubjectPosition.mMinChange = 0.01f;
    mBufferedLookAtPosition.mSteps = 7;
    mBufferedLookAtPosition.mMinChange = 0.01f;
    mBufferedHeading.mSteps = 8;
    mBufferedHeading.mMinChange = 0.01f;
    mBufferedDistanceAlongCurve.mSteps = 7;
    mBufferedDistanceAlongCurve.mMinChange = 0.01f;
    mBufferedDistanceAlongCurve.mTarget = 0.0f;
    mContinuousZoomDistance = 0.0f;
    mBufferedNearClip.mSteps = 7;
    mBufferedNearClip.mMinChange = 0.01f;
    mBufferedNearClip.mTarget = 1.0f;
    mBufferedFarClip.mSteps = 7;
    mBufferedFarClip.mTarget = 100.0f;
    mBufferedFOV.mTarget = g_kPiOver6;
    mBufferedFarClip.mMinChange = 0.01f;
    mBufferedFOV.mMinChange = 0.01f;
    mBufferedPitchParam.mMinChange = 0.01f;
    mBufferedFOV.mSteps = 7;
    mBufferedPitchParam.mSteps = 7;
    mBufferedPitchParam.mTarget = 0.5f;
    mRelativeOrientation.mCurrent = g_kQuatIdent;
    mRelativeOrientation.mTarget = g_kQuatIdent;
    mRelativeOrientation.mMinChange = 0.01f;
    mCameraPitchScaling = 0.005f;
    mRelativeOrientation.mSteps = 7;
    mHeadingRelative = 0.0f;
    mRotationPitchRatioMax = 1.0f;
    mContinuousRotationScaling = 0.003f;

    FloatVec zoom(5, 0);       // zoom distances
    FloatVec fov(5, 0);        // FOV levels (radians)
    FloatVec nearClip(5, 0);
    FloatVec farClip(5, 0);
    FloatVec minPitch(5, 0);   // degrees
    FloatVec maxPitch(5, 0);   // degrees

    zoom[0] = 68.0f; fov[0] = 0.56199604f; nearClip[0] = 1.0f; farClip[0] = 500.0f;
    minPitch[0] = 30.0f; maxPitch[0] = 40.0f;
    zoom[1] = 49.0f; fov[1] = 0.49916416f; nearClip[1] = 1.0f; farClip[1] = 500.0f;
    minPitch[1] = 26.0f; maxPitch[1] = 45.0f;
    zoom[2] = 28.0f; fov[2] = 0.40142572f; nearClip[2] = 1.0f; farClip[2] = 500.0f;
    minPitch[2] = 22.5f; maxPitch[2] = 50.0f;
    zoom[3] = 18.3f; fov[3] = 0.3892084f; nearClip[3] = 1.0f; farClip[3] = 500.0f;
    minPitch[3] = 19.0f; maxPitch[3] = 55.0f;
    zoom[4] = 12.0f; fov[4] = 0.38048175f; nearClip[4] = 1.0f; farClip[4] = 500.0f;
    minPitch[4] = 15.0f; maxPitch[4] = 60.0f;

    FloatVec orient(8, 0);     // discrete orientations (radians)
    orient[0] = 0.17453292f; orient[1] = 0.9599311f; orient[2] = 1.7453293f; orient[3] = 2.5307274f;
    orient[4] = 3.3161256f; orient[5] = 4.101524f; orient[6] = 4.886922f; orient[7] = 5.67232f;

    SetZoomLevels(zoom, fov);
    SetCurrentZoomLevel(0);
    mFarClipPlanes.erase_all();
    mNearClipPlanes.erase_all();
    mMinPitches.erase_all();
    mMaxPitches.erase_all();
    SetOrientations(orient);
    SetCurrentDiscreteOrientation(1);
    SetClipPlanes(nearClip, farClip);
    SetPitchAngles(minPitch, maxPitch);

    orient[0] = 10.0f;
    orient[1] = 55.0f;
    orient[2] = 100.0f;
    orient[3] = 145.0f;
    orient[4] = 190.0f;

    for (int i = 0; i < 7; ++i)
        mCameraPositions[i].mValid = false;
    mSubjectTrackingDeadZoneMagnitude = 1.0f;
    v49_Refresh();
}

// @ 0x007df450  SP::cSmoothCameraController::cSmoothCameraController
cSmoothCameraController::cSmoothCameraController(cPropertyList* config)
    : mConfig(config),
      mCurrentZoomLevel(0),
      mContinuousZoomDistance(0.0f),
      mViewSlope(0.0f),
      mCurrentOrientation(0),
      mPositionInterpolationSteps(0),
      mTranslationInputVelocity(0.0f),
      mHeadingRelative(0.0f),
      mTracking(false), mReadFromStream(false), mAdjustablePitch(false), mbInModalDialogLoop(false),
      mStartMouseWheelLevel(0),
      mKeyboardRotationSpeed(0.0f),
      mKeyboardZoomSpeed(0.0f),
      mKeyboardZoomScale(0.0f),
      mKeyboardTranslationSpeed(0.0f),
      mSubjectTrackingDeadZoneMagnitude(0.0f),
      mRotationPitchRatioMax(0.0f),
      mCameraPitchScaling(0.0f),
      mContinuousRotationScaling(0.0f),
      mMaxRotationDelta(0.0f)
{
    Reset();
    if (mConfig.mpObject)
        ConfigUpdated();
}

// @ 0x007df710  SP::CreateSmoothCameraController
cSmoothCameraController* __cdecl CreateSmoothCameraController(cPropertyList* config)
{
    return new ("App", 0, 0, 0, 0) cSmoothCameraController(config);
}
