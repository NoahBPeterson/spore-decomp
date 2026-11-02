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
struct cAppHasState {
    char pad00[0x18];
    bool Check();                     // @ 0x007d9380
};
struct BaseObj { void SomeBaseDestructor(); };
// ---- items of slice s007d85b0 end

// ---- items of slice s007d9460 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* Sub_6a3430(void* out, const float* m);          // matrix assignment
void* Sub_4a9b40(void* out, const float* q);          // quaternion -> transform
void  Matrix3_Assign(void* dst, const void* src);     // 0x0041cb40
float* Property_GetFloat(void* prop);                 // 0x0041ea70
char*  Property_GetBool(void* prop);                  // 0x0041e920
struct Vec3 { float x, y, z; };
struct tLerpAngle  { float mCurrent; float mTarget; int mSteps; float mMinChange; };   // 0x10
struct tLerpVector { Vec3 mCurrent; Vec3 mTarget; int mSteps; float mMinChange; };     // 0x20
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
    union {
        bool   mZUp;                      // +0x44
        float  mCameraThetaPre;           // +0x44 (quaternion setter alias)
    };
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
extern "C" unsigned __int64 __rdtsc(void);   // 0x00f47582 (crt lib_)
extern "C" long _InterlockedExchange(volatile long* Target, long Value);  // 0x00f4711d (crt lib_)
#pragma intrinsic(expf, fabsf)
#pragma intrinsic(__rdtsc)
#pragma intrinsic(_InterlockedExchange)
namespace rw {
namespace math {
namespace fpu {
class Vector3Template_s007d_a2d0 { public:
    float x, y, z;
};
}
}
}
namespace rw {
namespace math {
namespace fpu {
class Matrix33Template_s007d_a2d0 { public:
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
struct cViewerArg {
    void SetNearFarClipPlane(float);          // 0x007c5350
    void SetClipPlane1(float);                // 0x007c4ba0
    void SetClipPlane2(float);                // 0x007c4bc0
    void ApplyTransformToScene(cTransform*);  // 0x007c4d00
};
static const float kPi      = 3.1415927410125732f;
static const float kNegFour = -4.0f;
static const float k0025    = 0.0024999999441206455f;
static const float k01      = 0.10000000149011612f;
static const float kRadToDeg = 57.295780181884766f;
extern const cSPMatrix3_s007d_a2d0 g_identity3;      // 0x01637eb8
void* EAllocApp(int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
struct ControllerCtor {
    void* Init(void* arg);   // 0x007d9fb0
};
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

// @ 0x007d9380
bool cAppHasState::Check()
{
    int i = 0;
    int* p = (int*)((char*)this + 0x18);
    for (; i < 3; ++i, ++p) {
        if (*p == 0x1c)
            return true;
    }
    return false;
}

// @ 0x007d93a0
void BaseObj::SomeBaseDestructor()
{
    void* self = this;
    *(void**)self = (void*)0x014128a8;
    *(void**)((char*)self + 4) = (void*)0x01412894;
    *(void**)((char*)self + 8) = (void*)0x01412890;
    void* p = *(void**)((char*)self + 0x24);
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    *(void**)((char*)self + 8) = (void*)0x013ef094;
    *(void**)((char*)self + 4) = (void*)0x013eb394;
    *(void**)self = (void*)0x013eb938;
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

// @ 0x007d9a50
void* QuatToMatrix(void* out, const float* q)
{
    float x = q[0], y = q[1], z = q[2], w = q[3];
    float m[9];
    m[0] = 1.0f - (z * z + y * y) * 2.0f;
    m[1] = (w * z + y * x) * 2.0f;
    m[2] = (z * x - w * y) * 2.0f;
    m[3] = (y * x - w * z) * 2.0f;
    m[4] = 1.0f - (z * z + x * x) * 2.0f;
    m[5] = (w * x + z * y) * 2.0f;
    m[6] = (w * y + z * x) * 2.0f;
    m[7] = (z * y - w * x) * 2.0f;
    m[8] = 1.0f - (y * y + x * x) * 2.0f;
    Sub_6a3430(out, m);
    return out;
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

// @ 0x007d9c40
bool cMouseCameraController::SetConfigValue(unsigned id, const void* value)
{
    const float* p = (const float*)value;
    switch (id) {
    case 0x101b534:
        mSubjectPosition.mCurrent.z = p[0];
        mSubjectPosition.mTarget.x = p[1];
        mSubjectPosition.mTarget.y = p[2];
        mFieldOfView.mMinChange = 0.0f;
        mCamOffset.mCurrent.x = 0.0f;
        mCamOffset.mCurrent.y = mCamOffset.mTarget.y;
        mCamOffset.mCurrent.z = 0.0f;
        mCamOffset.mTarget.x = 0.0f;
        return true;
    case 0x101b537:
        mSubjectPosition.mCurrent.z = p[0];
        mSubjectPosition.mTarget.x = p[1];
        mSubjectPosition.mTarget.y = p[2];
        mCameraBaseOrientation.m[8] = p[0];
        mSubjectPosition.mCurrent.x = p[1];
        mSubjectPosition.mCurrent.y = p[2];
        mFieldOfView.mMinChange = 0.0f;
        mCamOffset.mCurrent.x = 0.0f;
        mCamOffset.mCurrent.y = mCamOffset.mTarget.y;
        mCamOffset.mCurrent.z = 0.0f;
        mCamOffset.mTarget.x = 0.0f;
        return true;
    case 0x101b543:
    case 0x101d576: {
        float m[9];
        QuatToMatrix(m, p);
        mCameraPhi.mCurrent = -m[0];
        mCameraTheta.mCurrent = -m[2];
        mCameraRoll.mCurrent = -m[1];
        return true;
    }
    case 0x101d445:
        mCamOffset.mCurrent.y = p[0];
        mCamOffset.mTarget.y = p[0];
        return true;
    case 0x101d4c7:
        mCamOffset.mTarget.y = p[0];
        return true;
    case 0x101d51f: {
        float m[9];
        QuatToMatrix(m, p);
        mCameraThetaPre = -m[2];
        mCameraTheta.mCurrent = -m[2];
        mCameraTheta.mMinChange = -m[0];
        mCameraPhi.mCurrent = -m[0];
        mCameraPhi.mMinChange = -m[1];
        mCameraRoll.mCurrent = -m[1];
        return true;
    }
    case 0x109d174:
        mFieldOfView.mCurrent = p[0];
        return true;
    case 0x109d1aa:
    case 0x109d372:
        mCameraMaxPitch = p[0];
        return true;
    case 0x109d1af:
    case 0x109d375:
        mNearClip = p[0];
        return true;
    case 0x109d352:
        mFieldOfView.mCurrent = p[0];
        mSubjectPosition.mMinChange = p[0];
        return true;
    case 0x479c05b: {
        float q[4] = { p[0], p[1], p[2], p[3] };
        float m[9];
        Sub_4a9b40(m, q);
        float* dst = &mCameraRoll.mMinChange;
        for (int i = 0; i < 9; ++i)
            dst[i] = m[i];
        return true;
    }
    default:
        return false;
    }
}

// @ 0x007d9fb0
cMouseCameraController::cMouseCameraController(cPropertyList* config)
{
    mHandlerVtbl = (void**)0x013eb384;
    mRefVtbl = (void**)0x013ef094;
    mUnk0c = 0;
    mIfaceVtbl = (void**)0x014128a8;
    mHandlerVtbl = (void**)0x01412894;
    mRefVtbl = (void**)0x01412890;
    mIsMayaStyle = false;
    mExponential = false;
    mPanSubjectPos = false;
    mPrevModIndex = 0;
    mConfig = config;
    if (config != 0)
        ((void(__thiscall*)(void*))(*(void***)config)[0])(config);
    mZoomScale = 1.0f;
    mWheelZoomScale = 1.0f;
    mTranslateScale = 1.0f;
    mExponentialPanScale = 1.0f;
    mRotateScale = 1.0f;
    mAnchorX = 0.0f;
    mAnchorY = 0.0f;
    mZUp = true;
    ((void(__thiscall*)(void*, const void*))Matrix3_Assign)(&mCameraBaseOrientation, (const void*)0x01637eb8);
    mCameraMinZoomDistance = 1.0f;
    mCameraMaxZoomDistance = 10000.0f;
    mStartCameraTheta = 0.0f;
    mStartCameraPhi = 0.0f;
    mStartCameraDistance = 0.0f;
    mStartCameraOffsetX = 0.0f;
    mStartCameraOffsetY = 0.0f;
    mCameraMaxPitch = 1.5707964f;
    mCameraMinPitch = -1.5707964f;
    mNearClip = -1.0f;
    mFarClip = -1.0f;
    mPreviousModifiers[0] = 0;
    mPreviousModifiers[1] = 0;
    mPreviousModifiers[2] = 0;
    mCameraTheta.mCurrent = 0.0f;
    mCameraTheta.mTarget = 0.0f;
    mCameraTheta.mMinChange = 0.001f;
    mCameraTheta.mSteps = 20;
    mCameraPhi.mCurrent = 0.0f;
    mCameraPhi.mTarget = 0.0f;
    mCameraPhi.mMinChange = 0.001f;
    mCameraPhi.mSteps = 20;
    mCameraRoll.mCurrent = 0.0f;
    mCameraRoll.mTarget = 0.0f;
    mCameraRoll.mMinChange = 0.001f;
    mCameraRoll.mSteps = 20;
    mFieldOfView.mCurrent = -1.0f;
    mFieldOfView.mTarget = -1.0f;
    mFieldOfView.mMinChange = 0.001f;
    mFieldOfView.mSteps = 20;
    mSubjectPosition.mCurrent.x = 0.0f;
    mSubjectPosition.mCurrent.y = 0.0f;
    mSubjectPosition.mCurrent.z = 0.0f;
    mSubjectPosition.mTarget.x = 0.0f;
    mSubjectPosition.mTarget.y = 0.0f;
    mSubjectPosition.mTarget.z = 0.0f;
    mSubjectPosition.mMinChange = 0.01f;
    mSubjectPosition.mSteps = 20;
    mCamOffset.mCurrent.x = 0.0f;
    mCamOffset.mCurrent.y = 0.0f;
    mCamOffset.mCurrent.z = 10.0f;
    mCamOffset.mTarget.x = 0.0f;
    mCamOffset.mTarget.y = 0.0f;
    mCamOffset.mTarget.z = 10.0f;
    mCamOffset.mMinChange = 0.01f;
    mCamOffset.mSteps = 20;
    if (mConfig != 0)
        ConfigUpdated();
}

// @ 0x007da790
void* SP_CreateMouseCameraController(void* arg)
{
    SP::cMouseCameraController_s007d_a2d0* p =
        (SP::cMouseCameraController_s007d_a2d0*)EAllocApp(0x124, "App", 0, 0, 0, 0);
    if (p) {
        return ((ControllerCtor*)p)->Init(arg);
    }
    return 0;
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
        ((cViewerArg*)ed)->SetNearFarClipPlane(mFieldOfView.mCurrent * kRadToDeg);
    if (mNearClip > 0.0f)
        ((cViewerArg*)ed)->SetClipPlane1(mNearClip);
    if (mFarClip > 0.0f)
        ((cViewerArg*)ed)->SetClipPlane2(mFarClip);

    cTransform t;
    t.mFlags = 0;
    t.mModificationCount = 0;
    t.mTranslation.x = g_subjectOrigin[0];
    t.mTranslation.y = g_subjectOrigin[1];
    t.mTranslation.z = g_subjectOrigin[2];
    t.mScale = 1.0f;
    t.mRotation.Assign(g_identity3);

    BuildTransform(&t);
    ((cViewerArg*)ed)->ApplyTransformToScene(&t);

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
