// Slice s007dd880: SP::cSmoothCameraController::ConfigUpdated (property-driven reconfiguration).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"
#include "s007dd880.h"

float    g_defaultFloat;
unsigned g_defaultUInt;

static const float kDegToRad = 0.017453292f;

// @ 0x007dd880
void cSmoothCameraController::ConfigUpdated()
{
    size_type numLevels = 5;   // zoom-level count; set from the zoom property, reused for clip planes and pitch
    if (mConfig->HasProperty(0xf75fb6)) {
        float f = *mConfig->GetProperty(0xf75fb6)->GetFloat();
        mKeyboardRotation.mMinChange = f;
        mKeyboardTranslation.mMinChange = f;
        mKeyboardZoomDelta.mMinChange = f;
        mBufferedSubjectPosition.mMinChange = f;
        mBufferedLookAtPosition.mMinChange = f;
        mBufferedHeading.mMinChange = f;
        mBufferedDistanceAlongCurve.mMinChange = f;
        mBufferedNearClip.mMinChange = f;
        mBufferedFarClip.mMinChange = f;
        mBufferedFOV.mMinChange = f;
        mBufferedPitchParam.mMinChange = f;
    }
    if (mConfig->HasProperty(0xf761e5))
        mKeyboardRotationSpeed = *mConfig->GetProperty(0xf761e5)->GetFloat();
    if (mConfig->HasProperty(0xf761ee) && mConfig->HasProperty(0xf761f4)) {
        mKeyboardRotation.mSteps = *mConfig->GetProperty(0xf761ee)->GetUInt();
        mKeyboardRotation.mMinChange = *mConfig->GetProperty(0xf761f4)->GetFloat();
    }
    if (mConfig->HasProperty(0xf761fb))
        mKeyboardTranslationSpeed = *mConfig->GetProperty(0xf761fb)->GetFloat();
    if (mConfig->HasProperty(0xf761ff) && mConfig->HasProperty(0xf76204)) {
        mKeyboardTranslation.mSteps = *mConfig->GetProperty(0xf761ff)->GetUInt();
        mKeyboardTranslation.mMinChange = *mConfig->GetProperty(0xf76204)->GetFloat();
    }
    if (mConfig->HasProperty(0xf76208))
        mKeyboardZoomSpeed = *mConfig->GetProperty(0xf76208)->GetFloat();
    if (mConfig->HasProperty(0xf7620d) && mConfig->HasProperty(0xf76211)) {
        mKeyboardZoomDelta.mSteps = *mConfig->GetProperty(0xf7620d)->GetUInt();
        mKeyboardZoomDelta.mMinChange = *mConfig->GetProperty(0xf76211)->GetFloat();
    }
    if (mConfig->HasProperty(0xf76215))
        mKeyboardZoomScale = *mConfig->GetProperty(0xf76215)->GetFloat();
    if (mConfig->HasProperty(0xf76218))
        mSubjectTrackingDeadZoneMagnitude = *mConfig->GetProperty(0xf76218)->GetFloat();
    if (mConfig->HasProperty(0xfc4b86))
        mRotationPitchRatioMax = *mConfig->GetProperty(0xfc4b86)->GetFloat();
    if (mConfig->HasProperty(0xfc4c71))
        mCameraPitchScaling = *mConfig->GetProperty(0xfc4c71)->GetFloat();
    if (mConfig->HasProperty(0xfc4c7f))
        mContinuousRotationScaling = *mConfig->GetProperty(0xfc4c7f)->GetFloat();
    if (mConfig->HasProperty(0xfc4ca3))
        mMaxRotationDelta = *mConfig->GetProperty(0xfc4ca3)->GetFloat();

    // zoom distances + FOV (degrees -> radians)
    if (mConfig->HasProperty(0xfc5228) && mConfig->HasProperty(0xfc6857)) {
        Property* pZoom = mConfig->GetProperty(0xfc5228);
        Property* pFov = mConfig->GetProperty(0xfc6857);
        numLevels = pZoom->GetArrayCount();
        size_type n = numLevels;
        float* zoom = (float*)pZoom->GetStorage();
        float* fov = (float*)pFov->GetStorage();
        FloatVec zoomLevels(n);
        FloatVec fovLevels(n);
        for (int i = 0; i < (int)n; ++i) {
            zoomLevels[i] = zoom[i];
            fovLevels[i] = fov[i] * kDegToRad;
        }
        SetZoomLevels(zoomLevels, fovLevels);
    }
    // near / far clip planes
    if (mConfig->HasProperty(0xfc7047) && mConfig->HasProperty(0xfc704c)) {
        Property* pNear = mConfig->GetProperty(0xfc7047);
        Property* pFar = mConfig->GetProperty(0xfc704c);
        size_type n = numLevels;
        float* nearP = (float*)pNear->GetStorage();
        float* farP = (float*)pFar->GetStorage();
        FloatVec nearClip(n);
        FloatVec farClip(n);
        for (int i = 0; i < (int)n; ++i) {
            nearClip[i] = nearP[i];
            farClip[i] = farP[i];
        }
        SetClipPlanes(nearClip, farClip);
    }
    // min / max pitch (degrees; SetPitchAngles converts)
    if (mConfig->HasProperty(0xfc71fc) && mConfig->HasProperty(0xfc7205)) {
        Property* pMin = mConfig->GetProperty(0xfc71fc);
        Property* pMax = mConfig->GetProperty(0xfc7205);
        size_type n = numLevels;
        float* minP = (float*)pMin->GetStorage();
        float* maxP = (float*)pMax->GetStorage();
        FloatVec minDeg(n);
        FloatVec maxDeg(n);
        for (int i = 0; i < (int)n; ++i) {
            minDeg[i] = minP[i];
            maxDeg[i] = maxP[i];
        }
        SetPitchAngles(minDeg, maxDeg);
    }
    // discrete orientations (degrees -> radians)
    if (mConfig->HasProperty(0xfc78e7)) {
        Property* pOri = mConfig->GetProperty(0xfc78e7);
        size_type n = pOri->GetArrayCount();
        float* ori = (float*)pOri->GetStorage();
        FloatVec orientations(n);
        for (int i = 0; i < (int)n; ++i)
            orientations[i] = ori[i] * kDegToRad;
        SetOrientations(orientations);
    }
}
