// Slice s007db1b0 (w2g5 slice 20).  Region: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast.
// SP::cSmoothCameraController and the pack-manager / automate command cluster
// that surrounds it.
#include "types.h"
#include <stdio.h>

typedef void* HMODULE;
typedef const char* LPCSTR;
typedef int BOOL;
typedef void* FARPROC;

// ---------------------------------------------------------------------------
// Shared types (2008 dev-build PDB layouts).
// ---------------------------------------------------------------------------
typedef char uint8_t_;

struct cSPVector3 { float x, y, z; };
struct cSPQuaternion { float x, y, z, w; };

namespace SP2 {
struct tLerpAngle   { float mCurrent; float mTarget; uint32_t mSteps; float mMinChange; };
struct tLerpScalar  { float mCurrent; float mTarget; uint32_t mSteps; float mMinChange; };
struct tLerpVector3 { cSPVector3 mCurrent; cSPVector3 mTarget; uint32_t mSteps; float mMinChange; };
struct tLerpQuaternion { cSPQuaternion mCurrent; cSPQuaternion mTarget; uint32_t mSteps; float mMinChange; };
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
    cSPVector3 mSubjectPosition;// +0x24
    int mFloorLevel;            // +0x30
    int mWallMode;              // +0x34
};
}  // namespace SP2
using namespace SP2;

// eastl::vector<float, sp_vector_allocator>: 16 bytes.
struct Vec16 { void* mpBegin; void* mpEnd; void* mpCapacity; void* mAlloc; };

// ---------------------------------------------------------------------------
// 0x007db5b0 / 0x007db5e0 / 0x007db620  small pointer-vector helpers.
// ---------------------------------------------------------------------------
struct PtrVec {
    void** mpBegin;     // +0x0
    void** mpEnd;       // +0x4
    bool Contains(int key);     // 007db5b0
    void* Find(int key);        // 007db5e0
    void* At(int index);        // 007db620
};

bool PtrVec::Contains(int key)
{
    for (void** p = mpBegin; p != mpEnd; ++p) {
        if (*(int*)*p == key)
            return true;
    }
    return false;
}

void* PtrVec::Find(int key)
{
    int n = (int)(mpEnd - mpBegin);
    for (int i = 0; i < n; ++i) {
        if (*(int*)mpBegin[i] == key)
            return mpBegin[i];
    }
    return 0;
}

void* PtrVec::At(int index)
{
    if (index >= 0 && index < (int)(mpEnd - mpBegin))
        return mpBegin[index];
    return 0;
}

// ---------------------------------------------------------------------------
// 0x007db8b0  free the pack-info pointers held by a vector.
// ---------------------------------------------------------------------------
void SP_cString_Dtor(void*);                 // 0x006b5240
void  __cdecl SP_VecDoInsert(void*, void*, int);  // 0x011e0744
void  __cdecl EFree(void*);                  // 0x00f47380

struct cPackInfoVec {
    void** mpBegin;     // +0
    void** mpEnd;       // +4
    void** mpCapacity;  // +8
    void* mAlloc;       // +0xc
    bool Clear();
};

bool cPackInfoVec::Clear()
{
    int n = (int)(mpEnd - mpBegin);
    for (int i = 0; i < n; ++i) {
        char* p = (char*)mpBegin[i];
        if (p) {
            SP_cString_Dtor(p + 0x24);
            EFree(p);
        }
    }
    void* end = mpEnd;
    void* begin = mpBegin;
    SP_VecDoInsert(begin, end, 0);
    mpEnd = (void**)((char*)mpEnd + (int)((char*)mpEnd - (char*)mpBegin) * -1);
    return true;
}

// ---------------------------------------------------------------------------
// SP::cSmoothCameraController.
// ---------------------------------------------------------------------------
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
    tLerpAngle mBufferedHeading;    // +0x80
    tLerpScalar mBufferedDistanceAlongCurve;  // +0x90
    tLerpScalar mBufferedNearClip;  // +0xa0
    tLerpScalar mBufferedFarClip;   // +0xb0
    tLerpScalar mBufferedFOV;       // +0xc0
    tLerpScalar mBufferedPitchParam;// +0xd0
    tLerpVector3 mBufferedSubjectPosition;   // +0xe0
    tLerpVector3 mBufferedLookAtPosition;    // +0x100
    Vec16 mFOVLevels;               // +0x120
    Vec16 mOrientations;            // +0x130
    int mCurrentOrientation;        // +0x140
    cSPVector3 mDraggedVelocity;    // +0x144
    uint32_t mPositionInterpolationSteps; // +0x150
    float mTranslationInputVelocity;// +0x154
    cSPVector3 mxyzSubjectOffset;   // +0x158
    tLerpQuaternion mRelativeOrientation;  // +0x164
    float mHeadingRelative;         // +0x18c
    bool mTracking;                 // +0x190
    bool mReadFromStream;           // +0x191
    bool mAdjustablePitch;          // +0x192
    bool mbInModalDialogLoop;       // +0x193
    int mStartMouseWheelLevel;      // +0x194
    tLerpScalar mKeyboardRotation;  // +0x198
    tLerpScalar mKeyboardZoomDelta; // +0x1a8
    tLerpVector3 mKeyboardTranslation; // +0x1b8
    float mKeyboardRotationSpeed;   // +0x1d8
    float mKeyboardZoomSpeed;       // +0x1dc
    float mKeyboardZoomScale;       // +0x1e0
    float mKeyboardTranslationSpeed;// +0x1e4
    tSavedCameraPosition mCameraPositions[7]; // +0x1e8
    float mSubjectTrackingDeadZoneMagnitude;  // +0x370
    float mRotationPitchRatioMax;   // +0x374
    float mCameraPitchScaling;      // +0x378
    float mContinuousRotationScaling; // +0x37c
    float mMaxRotationDelta;        // +0x380

    bool Init(int arg);                              // 007db920
    bool HandleMessage(int msg, void* data);         // 007db950
    bool OnKeyDown(int key);                         // 007dbc30
    void SetFocus();                                 // 007dbcb0
    void SetZoomDuration(float d);                   // 007dbd90
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

bool cSmoothCameraController::OnKeyDown(int key)
{
    void** vt = *(void***)this;
    if (key == 0xbc) {
        ((void(__thiscall*)(void*, void*))vt[0xc0 / 4])(this, (void*)0x0101b52d);
        return true;
    }
    if (key == 0xbe) {
        ((void(__thiscall*)(void*, void*))vt[0xc0 / 4])(this, (void*)0x0101b52f);
        return true;
    }
    if (key == 0xbb) {
        ((void(__thiscall*)(void*, void*))vt[0xc0 / 4])(this, (void*)0xcca298c4);
        return true;
    }
    if (key == 0xbd) {
        ((void(__thiscall*)(void*, void*))vt[0xc0 / 4])(this, (void*)0x2ca298e9);
        return true;
    }
    return false;
}

void cSmoothCameraController::SetFocus()
{
    mKeyboardTranslation.mCurrent.x = 0.0f;
    mKeyboardTranslation.mCurrent.y = 0.0f;
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

void cSmoothCameraController::SetZoomDuration(float d)
{
    mRelativeOrientation.mCurrent.w = d;
    mBufferedFarClip.mCurrent = d;
    mBufferedFOV.mCurrent = d;
    mBufferedPitchParam.mCurrent = d;
}

void* cSmoothCameraController::GetSavedCamera()
{
    ((void(__thiscall*)(void*, int))(((void**)*(void**)this)[0xc8 / 4]))(this, 0);
    return &mCameraPositions[0].mPitchParam;
}

void cSmoothCameraController::SetSavedCamera(float* src)
{
    void** vt = *(void***)this;
    for (int i = 0; i < 0xe; ++i)
        (&mCameraPositions[0].mPitchParam)[i] = src[i];
    ((void(__thiscall*)(void*, int))vt[0xcc / 4])(this, 0);
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
    tSavedCameraPosition* p = &mCameraPositions[index];
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
    tSavedCameraPosition* p = &mCameraPositions[index];
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

// ---------------------------------------------------------------------------
// 0x007db950  cSmoothCameraController::HandleMessage
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Command-line / plugin automation cluster (EH-heavy; best-effort).
// ---------------------------------------------------------------------------
struct IConfigManager2 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11(int);
};
void* SP_ConfigManager();   // 0x0067dd30

struct Str {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mAlloc;
};

void Sprintf8(char*, const char*, ...);      // 0x00938470

int g_1638280;
int g_1638284;

void SP_PluginList1(void);   // 007db1b0
void SP_PluginList2(void);   // 007db2a0
void SP_PluginRun();         // 007db060 (ManifestSource::Load)
