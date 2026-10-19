// src/game/SPEngine/SPAppMouseCamera.cpp -- migrated from slice(s) s007da2d0, s007d9460, s007d85b0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppMouseCamera.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include "SP/cPropertyList.h"
#include <math.h>
#include "EA/Stopwatch.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Swarm/cTransform.h"
#include <stdio.h>

// ---- items of slice s007d85b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cAppToggleHandler {
    char pad00[0x10];
    bool mFlag;            // +0x10
    bool Handle(int msg, int data);   // @ 0x007d9350
};
// ---- items of slice s007d85b0 end

// ---- items of slice s007d9460 begin (TODO(rewrite): local stubs, replace by canonical classes)
float* Property_GetFloat(void* prop);                 // 0x0041ea70
char*  Property_GetBool(void* prop);                  // 0x0041e920
struct Vec3 { float x, y, z; };
struct tLerpAngle  { float mCurrent; float mTarget; int mSteps; float mMinChange; };   // 0x10
struct tLerpVector { Vec3 mCurrent; Vec3 mTarget; float mMinChange; int mSteps; };     // 0x20
struct cSPMatrix3_s007d_9460 { float m[9]; };
struct cPropertyList { void** vftable; };
struct cMouseCameraController {           // size 0x124
    void** mIfaceVtbl;                    // +0x00
    void** mHandlerVtbl;                  // +0x04
    void** mRefVtbl;                      // +0x08
    void*  mUnk0c;                        // +0x0c
    bool   mIsMayaStyle;                  // +0x10
    bool   mExponential;                  // +0x11
    bool   mPanSubjectPos;                // +0x12
    char   pad13;
    int    mPrevModIndex;                 // +0x14
    unsigned mPreviousModifiers[3];       // +0x18
    cPropertyList* mConfig;               // +0x24
    float  mZoomScale;                    // +0x28
    float  mWheelZoomScale;               // +0x2c
    float  mTranslateScale;               // +0x30
    float  mExponentialPanScale;          // +0x34
    float  mRotateScale;                  // +0x38
    float  mAnchorX;                      // +0x3c
    float  mAnchorY;                      // +0x40
    bool   mZUp;                          // +0x44
    char   pad45[3];
    tLerpAngle  mCameraTheta;             // +0x48
    tLerpAngle  mCameraPhi;               // +0x58
    tLerpAngle  mCameraRoll;              // +0x68
    cSPMatrix3_s007d_9460  mCameraBaseOrientation;   // +0x78
    tLerpVector mSubjectPosition;         // +0x9c
    tLerpAngle  mFieldOfView;             // +0xbc
    tLerpVector mCamOffset;               // +0xcc
    float  mStartCameraTheta;             // +0xec
    float  mStartCameraPhi;               // +0xf0
    float  mStartCameraDistance;          // +0xf4
    float  mStartCameraOffsetX;           // +0xf8
    float  mStartCameraOffsetY;           // +0xfc
    Vec3   mStartSubjectPosition;         // +0x100
    float  mCameraMinZoomDistance;        // +0x10c
    float  mCameraMaxZoomDistance;        // +0x110
    float  mCameraMinPitch;               // +0x114
    float  mCameraMaxPitch;               // +0x118
    float  mNearClip;                     // +0x11c
    float  mFarClip;                      // +0x120

    void ConfigUpdated();                                 // 0x007d9460
    bool SetConfigValue(unsigned id, const void* value);  // 0x007d9c40
    bool Begin(int unused, float anchorX, float anchorY, int unused2); // 0x007d9bd0
    cMouseCameraController(cPropertyList* config);          // 0x007d9fb0
};
static bool ConfigGetFloat(cPropertyList* cfg, unsigned id, float* out) {
    if (cfg == 0)
        return false;
    if (!((bool(__thiscall*)(void*, unsigned))(*(void***)cfg)[0x1c / 4])(cfg, id))
        return false;
    unsigned* rec = (unsigned*)((unsigned(__thiscall*)(void*, unsigned))(*(void***)cfg)[0x28 / 4])(cfg, id);
    unsigned short t = *(unsigned short*)((char*)rec + 0x12);
    float* p;
    if (t == 0xd || t == 0x10) {
        if ((*(unsigned char*)((char*)rec + 0x10) & 0x30) == 0)
            p = (float*)(-(unsigned)(t != 0) & (unsigned)(size_t)rec);
        else
            p = (float*)(size_t)(*rec);
    } else {
        p = (float*)0x015d1168;
    }
    *out = *p;
    return true;
}
// ---- items of slice s007d9460 end

// ---- items of slice s007da2d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_subjectOrigin[3];          // 0x01637d78
#pragma intrinsic(expf, fabsf)
namespace rw {
namespace math {
namespace fpu {
struct Vector3Template_s007d_a2d0 {
    float x, y, z;
};
}
}
}
namespace rw {
namespace math {
namespace fpu {
struct Matrix33Template_s007d_a2d0 {
    float m[9];
    void Assign(const Matrix33Template_s007d_a2d0&);   // 0x0041cb40
};
}
}
}
typedef rw::math::fpu::Vector3Template_s007d_a2d0 cSPVector3_s007d_a2d0;
namespace SP {
struct tLerpAngle_s007d_a2d0 {
    float mCurrent;     // +0x0
    float mTarget;      // +0x4
    uint32_t mSteps;    // +0x8
    float mMinChange;   // +0xc
};
}
namespace SP {
struct tLerpScalar {
    float mCurrent;     // +0x0
    float mTarget;      // +0x4
    uint32_t mSteps;    // +0x8
    float mMinChange;   // +0xc
};
}
namespace SP {
struct tLerpVector3 {
    cSPVector3_s007d_a2d0 mCurrent;    // +0x0
    cSPVector3_s007d_a2d0 mTarget;     // +0xc
    uint32_t mSteps;        // +0x18
    float mMinChange;       // +0x1c
};
}
struct cSPMatrix3_s007d_a2d0 : rw::math::fpu::Matrix33Template_s007d_a2d0 {};   // size 0x24
struct cTransform {
    uint16_t mFlags;                 // +0x0
    uint16_t mModificationCount;     // +0x2
    cSPVector3_s007d_a2d0 mTranslation;         // +0x4
    float mScale;                    // +0x10
    rw::math::fpu::Matrix33Template_s007d_a2d0 mRotation;  // +0x14
    cTransform();                            // 0x00409930
    void SetRotation(const cSPMatrix3_s007d_a2d0&);     // 0x005b51b0
    void RotateY(float);                     // 0x004099b0
    void PreRotateX(float);                  // 0x005a2d90
    void Rotate(float);                      // 0x006b9050
};
namespace SP {
class cMouseCameraController_s007d_a2d0 {
public:
    char mBase[0x10];                        // +0x0  (cICameraController + RefCount)
    bool mIsMayaStyle;                       // +0x10
    bool mExponential;                       // +0x11
    bool mPanSubjectPos;                     // +0x12
    char mPad13;                             // +0x13
    int mPrevModIndex;                       // +0x14
    uint32_t mPreviousModifiers[3];          // +0x18
    void* mConfig;                           // +0x24
    float mZoomScale;                        // +0x28
    float mWheelZoomScale;                   // +0x2c
    float mTranslateScale;                   // +0x30
    float mExponentialPanScale;              // +0x34
    float mRotateScale;                      // +0x38
    float mAnchorX;                          // +0x3c
    float mAnchorY;                          // +0x40
    bool mZUp;                               // +0x44
    char mPad45[3];                          // +0x45
    tLerpAngle_s007d_a2d0 mCameraTheta;                 // +0x48
    tLerpAngle_s007d_a2d0 mCameraPhi;                   // +0x58
    tLerpAngle_s007d_a2d0 mCameraRoll;                  // +0x68
    cSPMatrix3_s007d_a2d0 mCameraBaseOrientation;       // +0x78
    tLerpVector3 mSubjectPosition;           // +0x9c
    tLerpScalar mFieldOfView;                // +0xbc
    tLerpVector3 mCamOffset;                 // +0xcc
    float mStartCameraTheta;                 // +0xec
    float mStartCameraPhi;                   // +0xf0
    float mStartCameraDistance;              // +0xf4
    float mStartCameraOffsetX;               // +0xf8
    float mStartCameraOffsetY;               // +0xfc
    cSPVector3_s007d_a2d0 mStartSubjectPosition;        // +0x100
    float mCameraMinZoomDistance;            // +0x10c
    float mCameraMaxZoomDistance;            // +0x110
    float mCameraMinPitch;                   // +0x114
    float mCameraMaxPitch;                   // +0x118
    float mNearClip;                         // +0x11c
    float mFarClip;                          // +0x120

    void ApplyMotion(int mode, float a, float b);      // 0x007da2d0
    void BuildTransform(cTransform* out);              // 0x007da5f0
    bool ProcessInput(float x, float y, int modifier); // 0x007da800
    bool StartDrag(int a, int b, int c, int d);        // 0x007da910
    void Update(int a, void* ed);                      // 0x007da9f0
};  // namespace SP
}
void SetNearFarClipPlane(void*, float);   // 0x007c5350
void SetClipPlane1(void*, float);         // 0x007c4ba0
void SetClipPlane2(void*, float);         // 0x007c4bc0
void ApplyTransformToScene(void*, cTransform*);  // 0x007c4d00
static const float kPi      = 3.1415927410125732f;
static const float kNegFour = -4.0f;
static const float k0025    = 0.0024999999441206455f;
static const float k01      = 0.10000000149011612f;
static const float kRadToDeg = 57.295780181884766f;
extern const cSPMatrix3_s007d_a2d0 g_identity3;      // 0x01637eb8
// ---- items of slice s007da2d0 end

// @ 0x007d9350
bool cAppToggleHandler::Handle(int msg, int data)
{
    if (msg == 0x4d && data == 0) {
        mFlag = (mFlag == 0);
        return true;
    }
    return false;
}

// @ 0x007d9460
void cMouseCameraController::ConfigUpdated()
{
    float f;
    if (ConfigGetFloat(mConfig, 0xc7c4f8, &f)) mZoomScale = f;
    if (ConfigGetFloat(mConfig, 0x15e688f, &f)) mWheelZoomScale = f;
    else mWheelZoomScale = mZoomScale;
    if (ConfigGetFloat(mConfig, 0xc7c4fa, &f)) mTranslateScale = f;
    if (ConfigGetFloat(mConfig, 0xc7c4f9, &f)) mRotateScale = f;
    if (ConfigGetFloat(mConfig, 0xc7c4fb, &f)) {
        mCamOffset.mCurrent.z = f;
        mCamOffset.mTarget.z = f;
    }
    if (ConfigGetFloat(mConfig, 0xc7c4fc, &f)) {
        mCameraPhi.mCurrent = f * 0.017453292f;
        mCameraPhi.mTarget = f * 0.017453292f;
    }
    if (ConfigGetFloat(mConfig, 0xc7c4fd, &f)) {
        mCameraTheta.mCurrent = f * 0.017453292f;
        mCameraTheta.mTarget = f * 0.017453292f;
    }
    if (ConfigGetFloat(mConfig, 0x6fda2e1c, &f)) {
        mCamOffset.mCurrent.x = f;
        mCamOffset.mTarget.x = f;
    }
    if (ConfigGetFloat(mConfig, 0x8fda2e23, &f)) {
        mCamOffset.mCurrent.y = f;
        mCamOffset.mTarget.y = mCamOffset.mCurrent.x;
    }
    if (ConfigGetFloat(mConfig, 0xfe243b, &f)) mCameraMinPitch = f * 0.017453292f;
    if (ConfigGetFloat(mConfig, 0xfe243f, &f)) mCameraMaxPitch = f * 0.017453292f;

    // Property-list query form (vtable[0x24] returns a record).
    if (mConfig != 0) {
        void* rec = 0;
        if (((bool(__thiscall*)(void*, unsigned, void**))(*(void***)mConfig)[0x24 / 4])(mConfig, 0x1102b20, &rec)
            && *(unsigned short*)((char*)rec + 0x12) == 0xd)
            mNearClip = *Property_GetFloat(rec);
        if (((bool(__thiscall*)(void*, unsigned, void**))(*(void***)mConfig)[0x24 / 4])(mConfig, 0x1102b2f, &rec)
            && *(unsigned short*)((char*)rec + 0x12) == 0xd)
            mFarClip = *Property_GetFloat(rec);
        if (((bool(__thiscall*)(void*, unsigned, void**))(*(void***)mConfig)[0x24 / 4])(mConfig, 0xfe23b2, &rec)
            && *(unsigned short*)((char*)rec + 0x12) == 0xd)
            mCameraMinZoomDistance = *Property_GetFloat(rec);
        if (((bool(__thiscall*)(void*, unsigned, void**))(*(void***)mConfig)[0x24 / 4])(mConfig, 0xfe2437, &rec)
            && *(unsigned short*)((char*)rec + 0x12) == 0xd)
            mCameraMaxZoomDistance = *Property_GetFloat(rec);
        if (((bool(__thiscall*)(void*, unsigned, void**))(*(void***)mConfig)[0x24 / 4])(mConfig, 0x15e0f54, &rec)
            && *(unsigned short*)((char*)rec + 0x12) == 1)
            mExponential = *Property_GetBool(rec) != 0;
        if (((bool(__thiscall*)(void*, unsigned, void**))(*(void***)mConfig)[0x24 / 4])(mConfig, 0x15e6baa, &rec)
            && *(unsigned short*)((char*)rec + 0x12) == 0xd)
            mExponentialPanScale = *Property_GetFloat(rec);
        if (((bool(__thiscall*)(void*, unsigned, void**))(*(void***)mConfig)[0x24 / 4])(mConfig, 0x15e84cd, &rec)
            && *(unsigned short*)((char*)rec + 0x12) == 1)
            mPanSubjectPos = *Property_GetBool(rec) != 0;
        if (((bool(__thiscall*)(void*, unsigned, void**))(*(void***)mConfig)[0x24 / 4])(mConfig, 0xdfb41e3f, &rec)
            && *(unsigned short*)((char*)rec + 0x12) == 1)
            mIsMayaStyle = *Property_GetBool(rec) != 0;
    }
    if (ConfigGetFloat(mConfig, 0x44c6220, &f))
        mFieldOfView.mCurrent = f;
}

// @ 0x007d9bd0
bool cMouseCameraController::Begin(int, float anchorX, float anchorY, int)
{
    mStartCameraTheta = mCameraTheta.mCurrent;
    mAnchorX = anchorX;
    mStartCameraPhi = mCameraPhi.mCurrent;
    mAnchorY = anchorY;
    mStartCameraOffsetX = mCamOffset.mCurrent.x;
    mStartCameraOffsetY = mCamOffset.mCurrent.y;
    mStartSubjectPosition = mSubjectPosition.mCurrent;
    mStartCameraDistance = mCamOffset.mCurrent.z;
    return true;
}

// @ 0x007da910
bool SP::cMouseCameraController_s007d_a2d0::StartDrag(int a, int b, int c, int d)
{
    mStartCameraTheta    = mCameraTheta.mCurrent;
    mStartCameraPhi      = mCameraPhi.mCurrent;
    mStartCameraOffsetX  = mCamOffset.mCurrent.x;
    mStartCameraOffsetY  = mCamOffset.mCurrent.y;
    mStartCameraDistance = mCamOffset.mCurrent.z;
    mStartSubjectPosition.x = mSubjectPosition.mCurrent.x;
    mStartSubjectPosition.y = mSubjectPosition.mCurrent.y;
    mStartSubjectPosition.z = mSubjectPosition.mCurrent.z;

    float v = ((float)a * mWheelZoomScale) * k0025 * kNegFour;
    if (mExponential) {
        mFieldOfView.mCurrent = expf(v) * mStartCameraDistance;
        mFieldOfView.mTarget  = mFieldOfView.mCurrent;
    } else {
        mFieldOfView.mCurrent = mStartCameraDistance + v;
        mFieldOfView.mTarget  = mFieldOfView.mCurrent;
    }
    return false;
}

// @ 0x007da9f0
void SP::cMouseCameraController_s007d_a2d0::Update(int a, void* ed)
{
    if (mFieldOfView.mCurrent > 0.0f)
        SetNearFarClipPlane(ed, mFieldOfView.mCurrent * kRadToDeg);
    if (mNearClip > 0.0f)
        SetClipPlane1(ed, mNearClip);
    if (mFarClip > 0.0f)
        SetClipPlane2(ed, mFarClip);

    cTransform t;
    t.mFlags = 0;
    t.mModificationCount = 0;
    t.mTranslation.x = g_subjectOrigin[0];
    t.mTranslation.y = g_subjectOrigin[1];
    t.mTranslation.z = g_subjectOrigin[2];
    t.mScale = 1.0f;
    t.mRotation.Assign(g_identity3);

    BuildTransform(&t);
    ApplyTransformToScene(ed, &t);

    float lo = -kPi;
    float range = kPi - lo;

    float d = mCameraTheta.mTarget - mCameraTheta.mCurrent;
    if (0.0f < range) {
        while (d < lo) d += range;
        while (kPi <= d) d -= range;
    }
    mCameraTheta.mCurrent = d * k01 + mCameraTheta.mCurrent;

    d = mCameraPhi.mTarget - mCameraPhi.mCurrent;
    if (0.0f < range) {
        while (d < lo) d += range;
        while (kPi <= d) d -= range;
    }
    mCameraPhi.mCurrent = d * k01 + mCameraPhi.mCurrent;

    d = mCameraRoll.mTarget - mCameraRoll.mCurrent;
    if (0.0f < range) {
        while (d < lo) d += range;
        while (kPi <= d) d -= range;
    }
    mCameraRoll.mCurrent = d * k01 + mCameraRoll.mCurrent;

    mCamOffset.mCurrent.x += (mCamOffset.mTarget.x - mCamOffset.mCurrent.x) * k01;
    mCamOffset.mCurrent.y += (mCamOffset.mTarget.y - mCamOffset.mCurrent.y) * k01;
    mCamOffset.mCurrent.z += (mCamOffset.mTarget.z - mCamOffset.mCurrent.z) * k01;

    mSubjectPosition.mCurrent.x +=
        (mSubjectPosition.mTarget.x - mSubjectPosition.mCurrent.x) * k01;
    mSubjectPosition.mCurrent.y +=
        (mSubjectPosition.mTarget.y - mSubjectPosition.mCurrent.y) * k01;
    mSubjectPosition.mCurrent.z +=
        (mSubjectPosition.mTarget.z - mSubjectPosition.mCurrent.z) * k01;

    if (mFieldOfView.mCurrent == -1.0f) {
        if (mFieldOfView.mTarget > 0.0f) {
            mFieldOfView.mCurrent = mFieldOfView.mTarget;
            return;
        }
    }
    if (mFieldOfView.mTarget == -1.0f && mFieldOfView.mCurrent > 0.0f) {
        mFieldOfView.mTarget = mFieldOfView.mCurrent;
        return;
    }
    float diff = mFieldOfView.mTarget - mFieldOfView.mCurrent;
    if (fabsf(diff) >= mFieldOfView.mMinChange)
        mFieldOfView.mCurrent += diff * k01;
    else
        mFieldOfView.mCurrent = mFieldOfView.mTarget;
}
