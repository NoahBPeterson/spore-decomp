// src/game/SPEngine/SPAppSmoothCamera.cpp -- migrated from slice(s) s007dd880, s007dd070, s007dc1b0, s007db1b0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppSmoothCamera.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern int g_16389dc, g_16389e0, g_16389e4;
extern int g_16389d0;
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "SP/cViewer.h"
#include "SP/cPropertyList.h"

// ---- items of slice s007db1b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPVector3_s007d_b1b0 { float x, y, z; };
struct cSPQuaternion_s007d_b1b0 { float x, y, z, w; };
namespace SP2 {
struct tLerpAngle   { float mCurrent; float mTarget; uint32_t mSteps; float mMinChange; };
}
namespace SP2 {
struct tLerpScalar  { float mCurrent; float mTarget; uint32_t mSteps; float mMinChange; };
}
namespace SP2 {
struct tLerpVector3 { cSPVector3_s007d_b1b0 mCurrent; cSPVector3_s007d_b1b0 mTarget; uint32_t mSteps; float mMinChange; };
}
namespace SP2 {
struct tLerpQuaternion { cSPQuaternion_s007d_b1b0 mCurrent; cSPQuaternion_s007d_b1b0 mTarget; uint32_t mSteps; float mMinChange; };
}
namespace SP2 {
struct tSavedCameraPosition {
    bool mValid;                // +0x0
    int mCurrentZoomLevel;      // +0x4
    float mDistance;            // +0x8
    int mCurrentOrientation;    // +0xc
    float mHeading;             // +0x10
    float mNearClip;            // +0x14
    float mFarClip;             // +0x18
    float mFOV;                 // +0x1c
    float mPitchParam;          // +0x20
    cSPVector3_s007d_b1b0 mSubjectPosition;// +0x24
    int mFloorLevel;            // +0x30
    int mWallMode;              // +0x34
};
}
struct Vec16 { void* mpBegin; void* mpEnd; void* mpCapacity; void* mAlloc; };
struct cSmoothCameraController {
    void* mVtbl;                    // +0x0
    char mPad04[0xc];               // +0x4
    void* mConfig;                  // +0x10
    Vec16 mEdgeConstraints;         // +0x14
    int mCurrentZoomLevel;          // +0x24
    float mContinuousZoomDistance;  // +0x28
    Vec16 mZoomLevels;              // +0x2c
    Vec16 mNearClipPlanes;          // +0x3c
    Vec16 mFarClipPlanes;           // +0x4c
    Vec16 mMinPitches;              // +0x5c
    Vec16 mMaxPitches;              // +0x6c
    float mViewSlope;               // +0x7c
    SP2::tLerpAngle mBufferedHeading;    // +0x80
    SP2::tLerpScalar mBufferedDistanceAlongCurve;  // +0x90
    SP2::tLerpScalar mBufferedNearClip;  // +0xa0
    SP2::tLerpScalar mBufferedFarClip;   // +0xb0
    SP2::tLerpScalar mBufferedFOV;       // +0xc0
    SP2::tLerpScalar mBufferedPitchParam;// +0xd0
    SP2::tLerpVector3 mBufferedSubjectPosition;   // +0xe0
    SP2::tLerpVector3 mBufferedLookAtPosition;    // +0x100
    Vec16 mFOVLevels;               // +0x120
    Vec16 mOrientations;            // +0x130
    int mCurrentOrientation;        // +0x140
    cSPVector3_s007d_b1b0 mDraggedVelocity;    // +0x144
    uint32_t mPositionInterpolationSteps; // +0x150
    float mTranslationInputVelocity;// +0x154
    cSPVector3_s007d_b1b0 mxyzSubjectOffset;   // +0x158
    SP2::tLerpQuaternion mRelativeOrientation;  // +0x164
    float mHeadingRelative;         // +0x18c
    bool mTracking;                 // +0x190
    bool mReadFromStream;           // +0x191
    bool mAdjustablePitch;          // +0x192
    bool mbInModalDialogLoop;       // +0x193
    int mStartMouseWheelLevel;      // +0x194
    SP2::tLerpScalar mKeyboardRotation;  // +0x198
    SP2::tLerpScalar mKeyboardZoomDelta; // +0x1a8
    SP2::tLerpVector3 mKeyboardTranslation; // +0x1b8
    float mKeyboardRotationSpeed;   // +0x1d8
    float mKeyboardZoomSpeed;       // +0x1dc
    float mKeyboardZoomScale;       // +0x1e0
    float mKeyboardTranslationSpeed;// +0x1e4
    SP2::tSavedCameraPosition mCameraPositions[7]; // +0x1e8
    float mSubjectTrackingDeadZoneMagnitude;  // +0x370
    float mRotationPitchRatioMax;   // +0x374
    float mCameraPitchScaling;      // +0x378
    float mContinuousRotationScaling; // +0x37c
    float mMaxRotationDelta;        // +0x380

    bool Init(int arg);                              // 007db920
    bool HandleMessage(int msg, void* data);         // 007db950
    bool OnKeyDown(int key, int arg);                // 007dbc30
    void SetFocus(int arg);                          // 007dbcb0
    void SetZoomDuration(uint32_t bits);             // 007dbd90
    void* GetSavedCamera();                          // 007dbdd0
    void SetSavedCamera(float* src);                 // 007dbdf0
    void StopMotion();                               // 007dbe50
    void SaveCameraPosition(int index);              // 007dbea0
    void RestoreCameraPosition(int index);           // 007dbf20
    void SetCurrentZoomLevel(int level);             // 007dbfe0
    void SetCurrentDiscreteOrientation(int orient);  // 007dc140
};
extern int g_16389dc, g_16389e0, g_16389e4;
extern int g_16389d0;
bool cSmoothCameraController::Init(int)
{
    ((void(__thiscall*)(void*))(((void**)*(void**)this)[0x60 / 4]))(this);
    return false;
}
void cSmoothCameraController::StopMotion()
{
    mBufferedDistanceAlongCurve.mSteps = (uint32_t)mBufferedDistanceAlongCurve.mMinChange;
    float y = mBufferedLookAtPosition.mCurrent.y;
    mBufferedNearClip.mSteps = (uint32_t)mBufferedNearClip.mMinChange;
    mBufferedSubjectPosition.mSteps = (uint32_t)y;
    mBufferedFarClip.mSteps = (uint32_t)mBufferedFarClip.mMinChange;
    mBufferedFOV.mSteps = (uint32_t)mBufferedFOV.mMinChange;
    mBufferedSubjectPosition.mMinChange = mBufferedLookAtPosition.mCurrent.z;
    mBufferedLookAtPosition.mCurrent.x = mBufferedLookAtPosition.mTarget.x;
    mBufferedPitchParam.mSteps = (uint32_t)mBufferedPitchParam.mMinChange;
    mBufferedSubjectPosition.mCurrent.z = mBufferedSubjectPosition.mTarget.x;
}
void cSmoothCameraController::SaveCameraPosition(int index)
{
    if (index >= 7)
        return;
    SP2::tSavedCameraPosition* p = &mCameraPositions[index];
    p->mValid = 1;
    p->mCurrentZoomLevel = (int)mContinuousZoomDistance;
    p->mDistance = (float)mBufferedNearClip.mSteps;
    p->mCurrentOrientation = (int)mxyzSubjectOffset.z;
    p->mHeading = (float)mBufferedDistanceAlongCurve.mSteps;
    p->mNearClip = (float)mBufferedFarClip.mSteps;
    p->mFarClip = (float)mBufferedFOV.mSteps;
    p->mFOV = (float)mBufferedPitchParam.mSteps;
    p->mPitchParam = mBufferedSubjectPosition.mCurrent.z;
    p->mSubjectPosition.x = (float)mBufferedSubjectPosition.mSteps;
    p->mSubjectPosition.y = mBufferedSubjectPosition.mMinChange;
    p->mSubjectPosition.z = mBufferedLookAtPosition.mCurrent.x;
    p->mFloorLevel = 0;
    p->mWallMode = 0;
}
void cSmoothCameraController::RestoreCameraPosition(int index)
{
    if (index >= 7)
        return;
    SP2::tSavedCameraPosition* p = &mCameraPositions[index];
    if (!p->mValid)
        return;
    void** vt = *(void***)this;
    ((void(__thiscall*)(void*, int))vt[0x74 / 4])(this, p->mCurrentZoomLevel);
    ((void(__thiscall*)(void*, float))vt[0xd4 / 4])(this, p->mDistance);
    ((void(__thiscall*)(void*, int))vt[0x88 / 4])(this, p->mCurrentOrientation);
    ((void(__thiscall*)(void*, float))vt[0xb8 / 4])(this, p->mNearClip);
    ((void(__thiscall*)(void*, void*))vt[0x68 / 4])(this, (void*)0);
}
void cSmoothCameraController::SetCurrentZoomLevel(int level)
{
    mCurrentZoomLevel = level;
    if (level < 0) {
        mCurrentZoomLevel = 0;
    } else if (level >= (int)(((char*)mZoomLevels.mpEnd - (char*)mZoomLevels.mpBegin) >> 2)) {
        mCurrentZoomLevel =
            (int)(((char*)mZoomLevels.mpEnd - (char*)mZoomLevels.mpBegin) >> 2) - 1;
    }
    float t = ((float*)mZoomLevels.mpBegin)[mCurrentZoomLevel];
    void** vt = *(void***)this;
    ((void(__thiscall*)(void*, float))vt[0xd4 / 4])(this, t);
    (void)vt;
    mBufferedNearClip.mMinChange = t;
    mBufferedFarClip.mMinChange = t;
    mBufferedFOV.mMinChange = t;
    mBufferedPitchParam.mMinChange = t;
}
void cSmoothCameraController::SetCurrentDiscreteOrientation(int orient)
{
    mxyzSubjectOffset.z = (float)orient;
    int n = (int)((char*)mOrientations.mpEnd - (char*)mOrientations.mpBegin) >> 2;
    if (n <= 0)
        return;
    while ((int)mxyzSubjectOffset.z < 0)
        mxyzSubjectOffset.z += (float)n;
    while ((int)mxyzSubjectOffset.z >= n)
        mxyzSubjectOffset.z -= (float)n;
}
struct cPackManager {
    char mPad00[0xc];
    void* mAvailablePacks[3];  // +0xc
    char mPad18[0xc];
    bool Init();
};
// ---- items of slice s007db1b0 end

// ---- items of slice s007dc1b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPVector3_s007d_c1b0 { float x, y, z; };
struct cSPQuaternion_s007d_c1b0 { float x, y, z, w; };
struct tLerpAngle_s007d_c1b0   { float mCurrent; float mTarget; uint32_t mSteps; float mMinChange; };
struct tLerpScalar_s007d_c1b0  { float mCurrent; float mTarget; uint32_t mSteps; float mMinChange; };
struct tLerpVector3_s007d_c1b0 { cSPVector3_s007d_c1b0 mCurrent; cSPVector3_s007d_c1b0 mTarget; uint32_t mSteps; float mMinChange; };
struct tLerpQuaternion_s007d_c1b0 { cSPQuaternion_s007d_c1b0 mCurrent; cSPQuaternion_s007d_c1b0 mTarget; uint32_t mSteps; float mMinChange; };
struct tSavedCameraPosition_s007d_c1b0 {
    bool mValid; int mCurrentZoomLevel; float mDistance; int mCurrentOrientation;
    float mHeading, mNearClip, mFarClip, mFOV, mPitchParam;
    cSPVector3_s007d_c1b0 mSubjectPosition; int mFloorLevel, mWallMode;
};
struct cSmoothCameraController_s007d_c1b0 {
    void* mVtbl; char mPad04[0xc]; void* mConfig;
    Vec16 mEdgeConstraints; int mCurrentZoomLevel; float mContinuousZoomDistance;
    Vec16 mZoomLevels; Vec16 mNearClipPlanes; Vec16 mFarClipPlanes;
    Vec16 mMinPitches; Vec16 mMaxPitches; float mViewSlope;
    tLerpAngle_s007d_c1b0 mBufferedHeading; tLerpScalar_s007d_c1b0 mBufferedDistanceAlongCurve;
    tLerpScalar_s007d_c1b0 mBufferedNearClip; tLerpScalar_s007d_c1b0 mBufferedFarClip;
    tLerpScalar_s007d_c1b0 mBufferedFOV; tLerpScalar_s007d_c1b0 mBufferedPitchParam;
    tLerpVector3_s007d_c1b0 mBufferedSubjectPosition; tLerpVector3_s007d_c1b0 mBufferedLookAtPosition;
    Vec16 mFOVLevels; Vec16 mOrientations; int mCurrentOrientation;
    cSPVector3_s007d_c1b0 mDraggedVelocity; uint32_t mPositionInterpolationSteps;
    float mTranslationInputVelocity; cSPVector3_s007d_c1b0 mxyzSubjectOffset;
    tLerpQuaternion_s007d_c1b0 mRelativeOrientation; float mHeadingRelative;
    bool mTracking; bool mReadFromStream; bool mAdjustablePitch; bool mbInModalDialogLoop;
    int mStartMouseWheelLevel;
    tLerpScalar_s007d_c1b0 mKeyboardRotation; tLerpScalar_s007d_c1b0 mKeyboardZoomDelta;
    tLerpVector3_s007d_c1b0 mKeyboardTranslation;
    float mKeyboardRotationSpeed, mKeyboardZoomSpeed, mKeyboardZoomScale, mKeyboardTranslationSpeed;
    tSavedCameraPosition_s007d_c1b0 mCameraPositions[7];
    float mSubjectTrackingDeadZoneMagnitude, mRotationPitchRatioMax, mCameraPitchScaling;
    float mContinuousRotationScaling, mMaxRotationDelta;

    float Zoom();                                   // 007dc1b0 0x007dc1b0
    bool ZoomRange(float* lo, float* hi);           // 007dc230 0x007dc230
    void UpdateSubjectMotion(float dt);             // 007dc260 0x007dc260
    bool HandleRequest(int id);                     // 007dc340 0x007dc340
    void ZoomInterpolationParamsFromDistanceAlongCurve
        (uint32_t* a, uint32_t* b, float* t, float d);  // 007dc510
    float ConstrainDistanceAlongCurve(float d);     // 007dc5e0 0x007dc5e0
    ~cSmoothCameraController_s007d_c1b0();                     // 007dc630
    void OnUpdateTargetSet();                       // 007dca30 0x007dca30
    void ViewerPositionAndOrientationFromDistanceAlongCurve
        (float* pos, float* quat, float d, int flag);  // 007dcc30
};
void EFreeCam(void*);   // 0x00f47380
cSmoothCameraController_s007d_c1b0::~cSmoothCameraController_s007d_c1b0()
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
// ---- items of slice s007dc1b0 end

// ---- items of slice s007dd070 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool g_cameraDebug;              // 0x016389d0 (debug flag, name coined)
extern const float kPi;                 // 0x0153efc8 (literal 3.1415927f)
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}      // user copy ctor: copies through xmm (operator= stays a plain dword copy)
    float Length() const { return sqrtf(x * x + y * y + z * z); }
};
static inline Vec3 operator-(const Vec3& a, const Vec3& b) { return Vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
static inline Vec3 operator+(const Vec3& a, const Vec3& b) { return Vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
static inline Vec3 operator*(const Vec3& a, float f) { return Vec3(a.x * f, a.y * f, a.z * f); }
struct Quat { float x, y, z, w; };
struct Matrix3 {
    float m[9];
    Matrix3& Assign(const Matrix3& other);                 // 0x0041cb40 (thiscall, ret 4)
};
static const float kLerpFactor = 0.1f;          // literal at 0x01412ad4
struct tLerpScalar_s007d_d070 {                                                                                 // 0x10
    float mCurrent; float mTarget; int mSteps; float mMinChange;
    __forceinline void Step()
    {
        float diff = mTarget - mCurrent;
        if ((float)fabs(diff) < mMinChange)
            mCurrent = mTarget;
        else
            mCurrent = mCurrent + diff * kLerpFactor;
    }
};
struct tLerpVector3_s007d_d070 { Vec3 mCurrent; Vec3 mTarget; int mSteps; float mMinChange; };              // 0x20
struct tLerpQuaternion_s007d_d070 { Quat mCurrent; Quat mTarget; int mSteps; float mMinChange; };           // 0x28
struct FloatVec {                                   // eastl::vector<float>, 5 words
    float* mpBegin; float* mpEnd; float* mpCapacity; const char* mpName; int mpAllocExtra;
    int size() const { return (int)(mpEnd - mpBegin); }
    float& operator[](int i) { return mpBegin[i]; }
};
extern Vec3 g_kVec3Zero3;               // 0x016389dc
extern Quat g_kQuatIdent;               // 0x016389f8
extern Matrix3 g_kMatrix3Identity;      // 0x01638b1c
struct Transform {
    short mnFlags;                      // +0x00
    short mnTransformCount;             // +0x02
    Vec3 mOffset;                       // +0x04
    float mfScale;                      // +0x10
    Matrix3 mRotation;                  // +0x14
    Transform() : mnFlags(0), mnTransformCount(0), mOffset(g_kVec3Zero3), mfScale(1.0f)
    {
        mRotation.Assign(g_kMatrix3Identity);
    }
    void SetOffset(const Vec3& v)
    {
        mOffset = v;
        mnFlags |= 4;
        mnTransformCount++;
    }
    void SetRotation(const Matrix3& m)
    {
        mRotation = m;
        mnFlags |= 2;
        mnTransformCount++;
    }
};
Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quat* q);                         // 0x0059c190 (cdecl)
Quat* Slerp(Quat* out, const Quat* a, const Quat* b, float t);                       // 0x005b2500 (cdecl)
struct cViewer {
    float GetNearPlane();                       // 0x007c3c90
    float GetFarPlane();                        // 0x007c3ca0
    float GetViewAngle();                       // 0x007c4050 (degrees)
    void GetViewTransform(Transform* out);      // 0x007c40f0 (hidden return pointer, ret 4)
    void SetNearPlane(float v);                 // 0x007c4ba0
    void SetFarPlane(float v);                  // 0x007c4bc0
    void SetCameraTransform(const Transform& t);// 0x007c4d00
    void SetViewAngle(float degrees);           // 0x007c5350
};
struct __declspec(novtable) cICameraControllerBase { virtual void slot0(); };
struct cIHandlerBase { cIHandlerBase() {} virtual ~cIHandlerBase() {} virtual void hslot0(); };
struct cRefCountBase { cRefCountBase() : mRefCount(0) {} virtual ~cRefCountBase() {} virtual void rslot0(); int mRefCount; };
struct cSmoothCameraController_s007d_d070 : cICameraControllerBase, cIHandlerBase, cRefCountBase {
    virtual void v1();  virtual void v2();  virtual void v3();  virtual void v4();  virtual void v5();
    virtual void v6();  virtual void v7();  virtual void v8();  virtual void v9();  virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25();
    virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40();
    virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45();
    virtual void v46();
    virtual void OnTimeStep(int deltaTime);                                                           // 0xbc
    virtual void Notify(unsigned id);                                                                 // 0xc0
    virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53();
    virtual void ApplyHeading();                                                                      // 0xd8
    virtual void GetCurvePoint(Vec3& pos, Quat& rot, float distance, bool flag);                      // 0xdc
    virtual void DebugCurvePoint(const Vec3& pos, const Vec3& lookAt, Matrix3& rot, const Quat& q);   // 0xe0
    virtual void v57();

    void* mConfig;                              // +0x10
    FloatVec mEdgeConstraints;                  // +0x14
    int mCurrentZoomLevel;                      // +0x28
    float mContinuousZoomDistance;              // +0x2c
    FloatVec mZoomLevels;                       // +0x30
    FloatVec mNearClipPlanes;                   // +0x44
    FloatVec mFarClipPlanes;                    // +0x58
    FloatVec mMinPitches;                       // +0x6c
    FloatVec mMaxPitches;                       // +0x80
    float mViewSlope;                           // +0x94
    tLerpScalar_s007d_d070 mBufferedHeading;               // +0x98 (angle, wrapped to [-pi, pi))
    tLerpScalar_s007d_d070 mBufferedDistanceAlongCurve;    // +0xa8
    tLerpScalar_s007d_d070 mBufferedNearClip;              // +0xb8
    tLerpScalar_s007d_d070 mBufferedFarClip;               // +0xc8
    tLerpScalar_s007d_d070 mBufferedFOV;                   // +0xd8
    tLerpScalar_s007d_d070 mBufferedPitchParam;            // +0xe8
    tLerpVector3_s007d_d070 mBufferedSubjectPosition;      // +0xf8
    tLerpVector3_s007d_d070 mBufferedLookAtPosition;       // +0x118
    FloatVec mFOVLevels;                        // +0x138
    FloatVec mOrientations;                     // +0x14c
    int mCurrentOrientation;                    // +0x160
    Vec3 mDraggedVelocity;                      // +0x164
    unsigned mPositionInterpolationSteps;       // +0x170
    float mTranslationInputVelocity;            // +0x174
    Vec3 mxyzSubjectOffset;                     // +0x178
    tLerpQuaternion_s007d_d070 mRelativeOrientation;       // +0x184
    float mHeadingRelative;                     // +0x1ac
    bool mTracking, mReadFromStream, mAdjustablePitch, mbInModalDialogLoop;   // +0x1b0
    int mStartMouseWheelLevel;                  // +0x1b4
    tLerpScalar_s007d_d070 mKeyboardRotation;              // +0x1b8
    tLerpScalar_s007d_d070 mKeyboardZoomDelta;             // +0x1c8
    tLerpVector3_s007d_d070 mKeyboardTranslation;          // +0x1d8

    void Update(int deltaTime, cViewer* viewer);  // 0x007dd070 (cSmoothCameraController::Update)
};
static const float kRadToDeg = 57.29578f;       // literal at 0x01412aa4
// ---- items of slice s007dd070 end

// ---- items of slice s007dd880 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memset(void*, int, size_t);
extern "C" void* __cdecl memcpy(void*, const void*, size_t);
extern float    g_defaultFloat;     // 0x015d1168
extern unsigned g_defaultUInt;      // 0x015d1164
#pragma intrinsic(memset)
typedef unsigned int size_type;
#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void* __cdecl EA_Alloc(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
void  __cdecl EA_Free(void* p) throw();                                                                                       // 0x00f47380
inline void* operator new(size_t, void* p) { return p; }
struct FloatVec_s007d_d880 {
    float* mpBegin; float* mpEnd; float* mpCapacity; const char* mpName; int mpAllocExtra;

    FloatVec_s007d_d880() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    // vector(n): allocate n floats and zero-fill (variable n compiles to `rep stosd`)
    __forceinline FloatVec_s007d_d880(size_type n)
    {
        mpBegin = n ? (float*)EA_Alloc(n * 4, "App", 0, 0, ALLOC_FILE, 0xd1) : 0;
        mpCapacity = mpBegin + n;
        for (size_type i = 0; i < n; ++i) mpBegin[i] = 0.0f;
        mpEnd = mpBegin + n;
    }
    // same, for compile-time sizes (inline memset: integer-register zero stores)
    __forceinline FloatVec_s007d_d880(size_type n, int)
    {
        mpBegin = n ? (float*)EA_Alloc(n * 4, "App", 0, 0, ALLOC_FILE, 0xd1) : 0;
        mpCapacity = mpBegin + n;
        memset(mpBegin, 0, n * 4);
        mpEnd = mpBegin + n;
    }
    ~FloatVec_s007d_d880() { if (mpBegin) { if (((int*)mpBegin)[-1]) EA_Free(mpBegin); } }
    float& operator[](size_type i) { return mpBegin[i]; }
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    void DoInsertValue(float* pos, const float& v);              // 0x00455660 (push_back slow path)
    void push_back(const float& v)
    {
        if (mpEnd < mpCapacity) ::new((void*)mpEnd++) float(v);
        else DoInsertValue(mpEnd, v);
    }
    void erase_all()
    {
        float* first = mpBegin; float* last = mpEnd;
        memcpy(first, last, (size_t)((char*)mpEnd - (char*)last));
        mpEnd -= (last - first);
    }
};
struct Property {
    void* data; unsigned count; unsigned short flags; unsigned short type;
    void* GetStorage() { if (flags & 0x30) return data; return type ? (void*)this : (void*)0; }
    unsigned GetArrayCount() { if (flags & 0x30) return count; return type != 0; }
    float* GetFloat() { if (type == 0xd || type == 0x10) return (float*)GetStorage(); return &g_defaultFloat; }
    unsigned* GetUInt() { if (type == 0xa || type == 0x10) return (unsigned*)GetStorage(); return &g_defaultUInt; }
};
struct cPropertyList {
    virtual void AddRef();                  // 0x00
    virtual void Release();                 // 0x04
    virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual bool HasProperty(unsigned id);  // 0x1c
    virtual void s8(); virtual void s9();
    virtual Property* GetProperty(unsigned id); // 0x28
};
struct Vec3_s007d_d880 { float x, y, z; };
struct tLerpScalar_s007d_d880  { float mCurrent; float mTarget; int mSteps; float mMinChange;      // 0x10
    tLerpScalar_s007d_d880() { memset(this, 0, 16); } };
struct tLerpVector3_s007d_d880 { Vec3_s007d_d880 mCurrent; Vec3_s007d_d880 mTarget; int mSteps; float mMinChange; };        // 0x20
struct tLerpQuaternion_s007d_d880 { Quat mCurrent; Quat mTarget; int mSteps; float mMinChange; };    // 0x28
struct tSavedCameraPosition_s007d_d880 {                                                              // 0x38
    bool mValid; int mCurrentZoomLevel; float mDistance; int mCurrentOrientation;
    float mHeading, mNearClip, mFarClip, mFOV, mPitchParam;
    Vec3_s007d_d880 mSubjectPosition; int mFloorLevel; int mWallMode;
};
struct AutoRefCountPL {
    cPropertyList* mpObject;
    AutoRefCountPL(cPropertyList* p) : mpObject(p) { if (p) p->AddRef(); }
    ~AutoRefCountPL() { if (mpObject) mpObject->Release(); }
    cPropertyList* operator->() const { return mpObject; }
};
struct cSmoothCameraController_s007d_d880 : cICameraControllerBase, cIHandlerBase, cRefCountBase {
    // vtable slot N is at byte offset N*4 (slot 0 = cICameraControllerBase::slot0)
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void ConfigUpdated();   // 0x50  @ 0x007dd880
    virtual void v21();
    virtual void Reset();                // 0x58  @ 0x007de7d0
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26_Unk(int);           // 0x68
    virtual void v27();
    virtual void SetZoomLevels(const FloatVec_s007d_d880& zoom, const FloatVec_s007d_d880& fov);             // 0x70 @ 0x007df6a0
    virtual void SetCurrentZoomLevel(int level);                                       // 0x74 0x007dbfe0
    virtual void SetClipPlanes(const FloatVec_s007d_d880& nearClip, const FloatVec_s007d_d880& farClip);     // 0x78 @ 0x007df6d0
    virtual void SetPitchAngles(const FloatVec_s007d_d880& minDeg, const FloatVec_s007d_d880& maxDeg);      // 0x7c @ 0x007df230
    virtual void v32();
    virtual void SetOrientations(const FloatVec_s007d_d880& v);                                   // 0x84 @ 0x007df700
    virtual void SetCurrentDiscreteOrientation(int i);                                 // 0x88 0x007dc140
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void SetEdgeConstraints(float a, float b, float c, float d);              // 0xac @ 0x007df330
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49_Refresh();           // 0xc4
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();

    AutoRefCountPL mConfig;               // +0x10
    FloatVec_s007d_d880 mEdgeConstraints; // +0x14
    int mCurrentZoomLevel;                // +0x28
    float mContinuousZoomDistance;        // +0x2c
    FloatVec_s007d_d880 mZoomLevels;      // +0x30
    FloatVec_s007d_d880 mNearClipPlanes;  // +0x44
    FloatVec_s007d_d880 mFarClipPlanes;   // +0x58
    FloatVec_s007d_d880 mMinPitches;      // +0x6c
    FloatVec_s007d_d880 mMaxPitches;      // +0x80
    float mViewSlope;                     // +0x94
    tLerpScalar_s007d_d880 mBufferedHeading;         // +0x98
    tLerpScalar_s007d_d880 mBufferedDistanceAlongCurve; // +0xa8
    tLerpScalar_s007d_d880 mBufferedNearClip;        // +0xb8
    tLerpScalar_s007d_d880 mBufferedFarClip;         // +0xc8
    tLerpScalar_s007d_d880 mBufferedFOV;             // +0xd8
    tLerpScalar_s007d_d880 mBufferedPitchParam;      // +0xe8
    tLerpVector3_s007d_d880 mBufferedSubjectPosition; // +0xf8
    tLerpVector3_s007d_d880 mBufferedLookAtPosition;  // +0x118
    FloatVec_s007d_d880 mFOVLevels;     // +0x138
    FloatVec_s007d_d880 mOrientations;   // +0x14c
    int mCurrentOrientation;              // +0x160
    Vec3_s007d_d880 mDraggedVelocity;                // +0x164
    unsigned mPositionInterpolationSteps; // +0x170
    float mTranslationInputVelocity;      // +0x174
    Vec3_s007d_d880 mxyzSubjectOffset;               // +0x178
    tLerpQuaternion_s007d_d880 mRelativeOrientation; // +0x184
    float mHeadingRelative;               // +0x1ac
    bool mTracking, mReadFromStream, mAdjustablePitch, mbInModalDialogLoop; // +0x1b0
    int mStartMouseWheelLevel;            // +0x1b4
    tLerpScalar_s007d_d880 mKeyboardRotation;        // +0x1b8
    tLerpScalar_s007d_d880 mKeyboardZoomDelta;       // +0x1c8
    tLerpVector3_s007d_d880 mKeyboardTranslation;    // +0x1d8
    float mKeyboardRotationSpeed;         // +0x1f8
    float mKeyboardZoomSpeed;             // +0x1fc
    float mKeyboardZoomScale;             // +0x200
    float mKeyboardTranslationSpeed;      // +0x204
    tSavedCameraPosition_s007d_d880 mCameraPositions[7]; // +0x208
    float mSubjectTrackingDeadZoneMagnitude;  // +0x390
    float mRotationPitchRatioMax;         // +0x394
    float mCameraPitchScaling;            // +0x398
    float mContinuousRotationScaling;     // +0x39c
    float mMaxRotationDelta;              // +0x3a0

    cSmoothCameraController_s007d_d880(cPropertyList* config);   // @ 0x007df450
};
float    g_defaultFloat;
unsigned g_defaultUInt;
static const float kDegToRad = 0.017453292f;
// ---- items of slice s007dd880 end

// @ 0x007db920
bool cPackManager::Init()
{
    // Collects all pack property lists from the resource manager and builds the
    // available-pack list, sorted by sequence number.
    return true;
}




// @ 0x007db950
bool cSmoothCameraController::HandleMessage(int msg, void* data)
{
    float* d = (float*)data;
    switch (msg) {
    case 0x101d51f:
        *(float*)&mTracking = d[0];
        mStartMouseWheelLevel = (int)d[1];
        mKeyboardRotation.mCurrent = d[2];
        mKeyboardRotation.mTarget = d[3];
        mRelativeOrientation.mCurrent.w = d[0];
        mRelativeOrientation.mSteps = (uint32_t)d[1];
        mRelativeOrientation.mMinChange = d[2];
        mHeadingRelative = d[3];
        break;
    case 0x101b542:
        mBufferedLookAtPosition.mTarget.z = d[0];
        mBufferedLookAtPosition.mSteps = (uint32_t)d[1];
        mBufferedLookAtPosition.mMinChange = d[2];
        mFOVLevels.mpBegin = *(void**)&d[0];
        mFOVLevels.mpEnd = *(void**)&d[1];
        mFOVLevels.mpCapacity = *(void**)&d[2];
        g_16389d0 = 1;
        break;
    case 0x101b534:
        mBufferedLookAtPosition.mCurrent.x = d[0];
        mBufferedLookAtPosition.mCurrent.y = d[1];
        mBufferedLookAtPosition.mCurrent.z = d[2];
        break;
    case 0x101b537:
        mBufferedSubjectPosition.mTarget.z = d[0];
        mBufferedSubjectPosition.mSteps = (uint32_t)d[1];
        mBufferedSubjectPosition.mMinChange = d[2];
        mBufferedLookAtPosition.mCurrent.x = d[0];
        mBufferedLookAtPosition.mCurrent.y = d[1];
        mBufferedLookAtPosition.mCurrent.z = d[2];
        break;
    case 0x101b543:
        *(float*)&mTracking = d[0];
        mStartMouseWheelLevel = (int)d[1];
        mKeyboardRotation.mCurrent = d[2];
        mKeyboardRotation.mTarget = d[3];
        break;
    case 0x101d445:
        mContinuousZoomDistance = d[0];
        mBufferedNearClip.mTarget = d[0];
        break;
    case 0x101d4c7:
        mContinuousZoomDistance = d[0];
        break;
    case 0x109d1af:
        if (d[0] > 0.0f) mBufferedFOV.mSteps = (uint32_t)d[0];
        break;
    case 0x109d174:
        if (d[0] > 0.0f) mBufferedPitchParam.mSteps = (uint32_t)d[0];
        break;
    case 0x109d1aa:
        if (d[0] > 0.0f) mBufferedFarClip.mSteps = (uint32_t)d[0];
        break;
    case 0x109d352:
        if (d[0] > 0.0f) {
            mBufferedPitchParam.mTarget = d[0];
            mBufferedPitchParam.mSteps = (uint32_t)d[0];
        }
        break;
    case 0x109d372:
        if (d[0] > 0.0f) {
            mBufferedFarClip.mSteps = (uint32_t)d[0];
            mBufferedFarClip.mTarget = d[0];
        }
        break;
    case 0x109d375:
        if (d[0] > 0.0f) {
            mBufferedFOV.mSteps = (uint32_t)d[0];
            mBufferedFOV.mTarget = d[0];
        }
        break;
    default:
        break;
    }
    return false;
}




// @ 0x007dbc30
bool cSmoothCameraController::OnKeyDown(int key, int)
{
    if (key == 0xbc) {
        ((void(__thiscall*)(void*, void*))(((void**)*(void**)this)[0xc0 / 4]))(
            this, (void*)0x0101b52d);
        return true;
    }
    if (key == 0xbe) {
        ((void(__thiscall*)(void*, void*))(((void**)*(void**)this)[0xc0 / 4]))(
            this, (void*)0x0101b52f);
        return true;
    }
    if (key == 0xbb) {
        ((void(__thiscall*)(void*, void*))(((void**)*(void**)this)[0xc0 / 4]))(
            this, (void*)0xcca298c4);
        return true;
    }
    if (key == 0xbd) {
        ((void(__thiscall*)(void*, void*))(((void**)*(void**)this)[0xc0 / 4]))(
            this, (void*)0x2ca298e9);
        return true;
    }
    return false;
}




// @ 0x007dbcb0
void cSmoothCameraController::SetFocus(int)
{
    mKeyboardTranslation.mCurrent.y = 0.0f;
    mKeyboardTranslation.mCurrent.x = 0.0f;
    *(int*)&mKeyboardTranslationSpeed = g_16389dc;
    *(int*)&mCameraPositions[0].mValid = g_16389e0;
    mCameraPositions[0].mCurrentZoomLevel = g_16389e4;
    *(int*)&mKeyboardRotationSpeed = g_16389dc;
    *(int*)&mKeyboardZoomSpeed = g_16389e0;
    *(int*)&mKeyboardZoomScale = g_16389e4;
    mKeyboardTranslation.mTarget.z = 0.0f;
    mKeyboardTranslation.mTarget.y = 0.0f;
    *(int*)&mRelativeOrientation.mCurrent.x = g_16389dc;
    *(int*)&mRelativeOrientation.mCurrent.y = g_16389e0;
    *(int*)&mRelativeOrientation.mCurrent.z = g_16389e4;
}




// @ 0x007dbd90
void cSmoothCameraController::SetZoomDuration(uint32_t bits)
{
    *(uint32_t*)&mRelativeOrientation.mCurrent.w = bits;
    *(uint32_t*)&mBufferedFarClip.mCurrent = bits;
    *(uint32_t*)&mBufferedFOV.mCurrent = bits;
    *(uint32_t*)&mBufferedPitchParam.mCurrent = bits;
}




// @ 0x007dbdd0
void* cSmoothCameraController::GetSavedCamera()
{
    ((void(__thiscall*)(void*, int))(((void**)*(void**)this)[0xc8 / 4]))(this, 0);
    return &mCameraPositions[0].mPitchParam;
}




// @ 0x007dbdf0
void cSmoothCameraController::SetSavedCamera(float* src)
{
    void** vt = *(void***)this;
    memcpy(&mCameraPositions[0].mPitchParam, src, 0x38);
    ((void(__thiscall*)(void*, int))vt[0xcc / 4])(this, 0);
}



// @ 0x007dc1b0
float cSmoothCameraController_s007d_c1b0::Zoom()
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



// @ 0x007dc230
bool cSmoothCameraController_s007d_c1b0::ZoomRange(float* lo, float* hi)
{
    if (mZoomLevels.mpEnd == mZoomLevels.mpCapacity)
        return false;
    *lo = ((float*)mZoomLevels.mpCapacity)[-1];
    *hi = ((float*)mZoomLevels.mpEnd)[0];
    return true;
}



// @ 0x007dc260
void cSmoothCameraController_s007d_c1b0::UpdateSubjectMotion(float dt)
{
    float z = mRelativeOrientation.mCurrent.z;
    float y = mRelativeOrientation.mCurrent.y;
    float x = mRelativeOrientation.mCurrent.x;
    if (sqrtf(x * x + y * y + z * z) > 0.001f) {
        float s = (float)(int)mRelativeOrientation.mCurrent.w;
        if ((int)mRelativeOrientation.mCurrent.w < 0)
            s = s + 4294967296.0f;
        cSPVector3_s007d_c1b0 v;
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



// @ 0x007dc340
bool cSmoothCameraController_s007d_c1b0::HandleRequest(int id)
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



// @ 0x007dc510
void cSmoothCameraController_s007d_c1b0::ZoomInterpolationParamsFromDistanceAlongCurve (uint32_t* a, uint32_t* b, float* t, float d)
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



// @ 0x007dc5e0
float cSmoothCameraController_s007d_c1b0::ConstrainDistanceAlongCurve(float d)
{
    float* begin = (float*)mZoomLevels.mpBegin;
    int n = (int)(((char*)mZoomLevels.mpEnd - (char*)mZoomLevels.mpBegin) >> 2);
    float lo = begin[n - 1];
    float hi = begin[0];
    if (d < lo) d = lo;
    if (d > hi) d = hi;
    return d;
}



// @ 0x007dc7b0
void ViewerOrientationFromPositionAndLookAt(const float* pos, const float* look, const float* up, float* out)
{
    float dx = look[0] - pos[0];
    float dy = look[1] - pos[1];
    float dz = look[2] - pos[2];
    (void)up; (void)dx; (void)dy; (void)dz;
    out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 1.0f;
}



// @ 0x007dca30
void cSmoothCameraController_s007d_c1b0::OnUpdateTargetSet()
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



// @ 0x007dcb00
void FUN_007dcb00(float* out, const float* a, const float* b)
{
    float b1 = b[1], b2 = b[2], a1 = a[1], a2 = a[2];
    float b0 = b[0], a0 = a[0], b3 = b[3], a3 = a[3];
    out[2] = (a3 * b2 + b3 * a2) + (a0 * b1 - b0 * a1);
    out[0] = (a3 * b0 + b3 * a0) + (b2 * a1 - b1 * a2);
    out[1] = (a3 * b1 + b3 * a1) + (b0 * a2 - b2 * a0);
    out[3] = a3 * b3 - ((b0 * a0 + b2 * a2) + b1 * a1);
}



// @ 0x007dcc30
void cSmoothCameraController_s007d_c1b0::ViewerPositionAndOrientationFromDistanceAlongCurve (float* pos, float* quat, float d, int flag)
{
    float* src = flag ? &mBufferedLookAtPosition.mCurrent.x : &mBufferedSubjectPosition.mCurrent.x;
    pos[0] = src[0];
    pos[1] = src[1];
    pos[2] = src[2];
    quat[0] = 0.0f; quat[1] = 0.0f; quat[2] = 0.0f; quat[3] = 1.0f;
    (void)d;
}


// @ 0x007dd070
void cSmoothCameraController_s007d_d070::Update(int deltaTime, cViewer* viewer)
{
    if (mbInModalDialogLoop)
    {
        mKeyboardRotation.mTarget = 0.0f;
        mKeyboardRotation.mCurrent = 0.0f;
        mKeyboardTranslation.mTarget = g_kVec3Zero3;
        mKeyboardTranslation.mCurrent = g_kVec3Zero3;
        mKeyboardZoomDelta.mTarget = 0.0f;
        mKeyboardZoomDelta.mCurrent = 0.0f;
        mDraggedVelocity = g_kVec3Zero3;
    }

    mKeyboardRotation.Step();
    Notify(0x101b52a);

    float oldZoom = mKeyboardZoomDelta.mCurrent;
    mKeyboardZoomDelta.Step();
    if (oldZoom != 0.0f)
        Notify(0x101b527);

    Vec3 oldTranslation = mKeyboardTranslation.mCurrent;
    {
        float dx = mKeyboardTranslation.mTarget.x - mKeyboardTranslation.mCurrent.x;
        float dy = mKeyboardTranslation.mTarget.y - mKeyboardTranslation.mCurrent.y;
        float dz = mKeyboardTranslation.mTarget.z - mKeyboardTranslation.mCurrent.z;
        mKeyboardTranslation.mCurrent.x = mKeyboardTranslation.mCurrent.x + dx * kLerpFactor;
        mKeyboardTranslation.mCurrent.y = mKeyboardTranslation.mCurrent.y + dy * kLerpFactor;
        mKeyboardTranslation.mCurrent.z = mKeyboardTranslation.mCurrent.z + dz * kLerpFactor;
    }
    if (oldTranslation.Length() != 0.0f)
        Notify(0x101b540);

    OnTimeStep(deltaTime);

    // wrap the discrete orientation index into [0, count)
    int count = mOrientations.size();
    if (count > 0)
    {
        while (mCurrentOrientation < 0)
            mCurrentOrientation += count;
        while (mCurrentOrientation >= count)
            mCurrentOrientation -= count;
    }
    mBufferedHeading.mTarget = mOrientations[mCurrentOrientation];
    ApplyHeading();

    mBufferedPitchParam.Step();
    mBufferedDistanceAlongCurve.Step();

    {
        float dx = mBufferedSubjectPosition.mTarget.x - mBufferedSubjectPosition.mCurrent.x;
        float dy = mBufferedSubjectPosition.mTarget.y - mBufferedSubjectPosition.mCurrent.y;
        float dz = mBufferedSubjectPosition.mTarget.z - mBufferedSubjectPosition.mCurrent.z;
        mBufferedSubjectPosition.mCurrent.x = mBufferedSubjectPosition.mCurrent.x + dx * kLerpFactor;
        mBufferedSubjectPosition.mCurrent.y = mBufferedSubjectPosition.mCurrent.y + dy * kLerpFactor;
        mBufferedSubjectPosition.mCurrent.z = mBufferedSubjectPosition.mCurrent.z + dz * kLerpFactor;
    }

    {
        float dx = mBufferedLookAtPosition.mTarget.x - mBufferedLookAtPosition.mCurrent.x;
        float dy = mBufferedLookAtPosition.mTarget.y - mBufferedLookAtPosition.mCurrent.y;
        float dz = mBufferedLookAtPosition.mTarget.z - mBufferedLookAtPosition.mCurrent.z;
        mBufferedLookAtPosition.mCurrent.x = mBufferedLookAtPosition.mCurrent.x + dx * kLerpFactor;
        mBufferedLookAtPosition.mCurrent.y = mBufferedLookAtPosition.mCurrent.y + dy * kLerpFactor;
        mBufferedLookAtPosition.mCurrent.z = mBufferedLookAtPosition.mCurrent.z + dz * kLerpFactor;
    }

    // heading: shortest way around the circle
    {
        float cur = mBufferedHeading.mCurrent;
        float lo = -kPi;
        float hi = kPi;
        float range = hi - lo;
        float diff = mBufferedHeading.mTarget - cur;
        if (range > 0.0f)
        {
            while (diff < lo)
                diff += range;
            while (diff >= hi)
                diff -= range;
        }
        mBufferedHeading.mCurrent = cur + diff * kLerpFactor;
    }

    mBufferedNearClip.Step();
    mBufferedFarClip.Step();
    mBufferedFOV.Step();

    {
        Quat out;
        Quat tmp = *Slerp(&out, &mRelativeOrientation.mCurrent, &mRelativeOrientation.mTarget, kLerpFactor);
        mRelativeOrientation.mCurrent = tmp;
    }

    if (viewer)
    {
        Vec3 pos = g_kVec3Zero3;
        Quat rot = g_kQuatIdent;
        GetCurvePoint(pos, rot, mBufferedDistanceAlongCurve.mCurrent, true);

        Transform t;
        viewer->GetViewTransform(&t);
        if (g_cameraDebug)
            DebugCurvePoint(pos, mBufferedLookAtPosition.mCurrent, t.mRotation, rot);

        float nearPlane = mBufferedNearClip.mCurrent;
        if (viewer->GetNearPlane() != nearPlane)
            viewer->SetNearPlane(nearPlane);
        float farPlane = mBufferedFarClip.mCurrent;
        if (viewer->GetFarPlane() != farPlane)
            viewer->SetFarPlane(farPlane);
        float angle = mBufferedFOV.mCurrent * kRadToDeg;
        if (viewer->GetViewAngle() != angle)
            viewer->SetViewAngle(mBufferedFOV.mCurrent * kRadToDeg);

        t.SetOffset(pos);
        Matrix3 rotMatrix;
        t.SetRotation(*Matrix3FromQuaternion(&rotMatrix, &rot));
        viewer->SetCameraTransform(t);
    }
}

// @ 0x007dd880
void cSmoothCameraController_s007d_d880::ConfigUpdated()
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
        FloatVec_s007d_d880 zoomLevels(n);
        FloatVec_s007d_d880 fovLevels(n);
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
        FloatVec_s007d_d880 nearClip(n);
        FloatVec_s007d_d880 farClip(n);
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
        FloatVec_s007d_d880 minDeg(n);
        FloatVec_s007d_d880 maxDeg(n);
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
        FloatVec_s007d_d880 orientations(n);
        for (int i = 0; i < (int)n; ++i)
            orientations[i] = ori[i] * kDegToRad;
        SetOrientations(orientations);
    }
}
