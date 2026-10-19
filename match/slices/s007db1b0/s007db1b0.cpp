// Slice s007db1b0 (w2g5 slice 20).  Region: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast.
// SP::cSmoothCameraController and the pack-manager / automate command cluster
// that surrounds it.
#include "types.h"
#include <stdio.h>
#include <string.h>

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
extern bool g_16389d0;

bool cSmoothCameraController::Init(int)
{
    ((void(__thiscall*)(void*))(((void**)*(void**)this)[0x60 / 4]))(this);
    return false;
}

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

void cSmoothCameraController::SetZoomDuration(uint32_t bits)
{
    *(uint32_t*)&mRelativeOrientation.mCurrent.w = bits;
    *(uint32_t*)&mBufferedFarClip.mCurrent = bits;
    *(uint32_t*)&mBufferedFOV.mCurrent = bits;
    *(uint32_t*)&mBufferedPitchParam.mCurrent = bits;
}

void* cSmoothCameraController::GetSavedCamera()
{
    ((void(__thiscall*)(void*, int))(((void**)*(void**)this)[0xc8 / 4]))(this, 0);
    return &mCameraPositions[0].mPitchParam;
}

void cSmoothCameraController::SetSavedCamera(float* src)
{
    void** vt = *(void***)this;
    memcpy(&mCameraPositions[0].mPitchParam, src, 0x38);
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

// Retail field offsets differ from the 2008 PDB layout above in this region, so the two
// functions below address the object by retail offset.
#define CF(T, off) (*(T*)((char*)this + (off)))
#define CVT(off, R, ...) ((R(__thiscall*)(void*, ##__VA_ARGS__))(*(void***)this)[(off) / 4])

// @ 0x007dbf20
void cSmoothCameraController::RestoreCameraPosition(int index)
{
    if ((unsigned)index > 6)
        return;
    char* p = (char*)this + index * 56 + 0x208;
    if (!*p)
        return;
    CVT(0x74, void, int)(this, *(int*)(p + 4));
    float r = CVT(0xd4, float, float)(this, *(float*)(p + 8));
    CF(float, 0x2c) = r;
    CVT(0x88, void, int)(this, *(int*)(p + 0xc));
    CF(float, 0x9c) = *(float*)(p + 0x10);
    void (__thiscall* setPos)(void*, void*) = CVT(0xb8, void, void*);
    CF(float, 0xbc) = *(float*)(p + 0x14);
    CF(float, 0xcc) = *(float*)(p + 0x18);
    CF(float, 0xdc) = *(float*)(p + 0x1c);
    CF(float, 0xec) = *(float*)(p + 0x20);
    CF(float, 0xac) = r;
    setPos(this, p + 0x24);
    CVT(0x68, void, int)(this, 0);
}

struct FVec {                                 // eastl::vector<float, sp_vector_allocator>
    float* mpBegin; float* mpEnd; float* mpCapacity; void* mAlloc;
    int size() const { return (int)(mpEnd - mpBegin); }
};
// @ 0x007dbfe0
void cSmoothCameraController::SetCurrentZoomLevel(int level)
{
    FVec& zoom = CF(FVec, 0x30);
    FVec& nearP = CF(FVec, 0x44);
    FVec& farP = CF(FVec, 0x58);
    FVec& fovL = CF(FVec, 0x138);
    CF(int, 0x28) = level;
    if (level < 0) {
        CF(int, 0x28) = 0;
    } else if (level >= zoom.size()) {
        CF(int, 0x28) = zoom.size() - 1;
    }
    float t = zoom.mpBegin[CF(int, 0x28)];
    float r = CVT(0xd4, float, float)(this, t);
    CF(float, 0xac) = r;
    int idx, idx2;
    float& frac = *(float*)&level;
    CVT(0xd0, void, int*, int*, float*, float)(this, &idx, &idx2, &frac, r);
    float nearc = 1.0f;
    float farc = 100.0f;
    if (nearP.size() == zoom.size() && zoom.size() == farP.size()) {
        float n0 = nearP.mpBegin[idx];
        float f0 = farP.mpBegin[idx];
        nearc = (nearP.mpBegin[idx + 1] - n0) * frac + n0;
        farc = (farP.mpBegin[idx + 1] - f0) * frac + f0;
    }
    CF(float, 0xbc) = nearc;
    CF(float, 0xcc) = farc;
    float fov = 1.0471976f;
    if (zoom.size() == fovL.size()) {
        float o0 = fovL.mpBegin[idx];
        fov = (fovL.mpBegin[idx + 1] - o0) * frac + o0;
    }
    CF(float, 0xdc) = fov;
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
    unsigned int* p = (unsigned int*)data;
    switch ((unsigned int)msg) {
    case 0x101b534:                                   // buffered look-at current
        *(unsigned int*)((char*)this + 0x100) = p[0];
        *(unsigned int*)((char*)this + 0x104) = p[1];
        *(unsigned int*)((char*)this + 0x108) = p[2];
        return false;
    case 0x101b537:                                   // subject target + look-at current
        *(unsigned int*)((char*)this + 0x0f4) = p[0];
        *(unsigned int*)((char*)this + 0x0f8) = p[1];
        *(unsigned int*)((char*)this + 0x0fc) = p[2];
        *(unsigned int*)((char*)this + 0x100) = p[0];
        *(unsigned int*)((char*)this + 0x104) = p[1];
        *(unsigned int*)((char*)this + 0x108) = p[2];
        return false;
    case 0x101b541:                                   // look-at target
        *(unsigned int*)((char*)this + 0x114) = p[0];
        *(unsigned int*)((char*)this + 0x118) = p[1];
        *(unsigned int*)((char*)this + 0x11c) = p[2];
        g_16389d0 = 1;
        return false;
    case 0x101b542:                                   // look-at target + FOV levels
        *(unsigned int*)((char*)this + 0x114) = p[0];
        *(unsigned int*)((char*)this + 0x118) = p[1];
        *(unsigned int*)((char*)this + 0x11c) = p[2];
        *(unsigned int*)((char*)this + 0x120) = p[0];
        *(unsigned int*)((char*)this + 0x124) = p[1];
        *(unsigned int*)((char*)this + 0x128) = p[2];
        g_16389d0 = 1;
        return false;
    case 0x101b543:
    case 0x101d576:                                   // orientation (4 words)
        *(unsigned int*)((char*)this + 0x190) = p[0];
        *(unsigned int*)((char*)this + 0x194) = p[1];
        *(unsigned int*)((char*)this + 0x198) = p[2];
        *(unsigned int*)((char*)this + 0x19c) = p[3];
        return false;
    case 0x101d445:                                   // continuous zoom distance + near clip
        *(float*)((char*)this + 0x28) = *(float*)data;
        *(float*)((char*)this + 0xa4) = *(float*)data;
        return false;
    case 0x101d4c7:
        *(float*)((char*)this + 0x28) = *(float*)data;
        return false;
    case 0x101d51f:                                   // tracking + buffered look-at
        *(unsigned int*)((char*)this + 0x190) = p[0];
        *(unsigned int*)((char*)this + 0x194) = p[1];
        *(unsigned int*)((char*)this + 0x198) = p[2];
        *(unsigned int*)((char*)this + 0x19c) = p[3];
        *(unsigned int*)((char*)this + 0x180) = p[0];
        *(unsigned int*)((char*)this + 0x184) = p[1];
        *(unsigned int*)((char*)this + 0x188) = p[2];
        *(unsigned int*)((char*)this + 0x18c) = p[3];
        return false;
    case 0x109d1af:
        if (*(float*)data > 0.0f) *(float*)((char*)this + 0xc8) = *(float*)data;
        return false;
    case 0x109d574:
        if (*(float*)data > 0.0f) *(float*)((char*)this + 0xd8) = *(float*)data;
        return false;
    case 0x109d5aa:
        if (*(float*)data > 0.0f) *(float*)((char*)this + 0xb8) = *(float*)data;
        return false;
    case 0x109d352:
        if (*(float*)data > 0.0f) {
            *(float*)((char*)this + 0xd4) = *(float*)data;
            *(float*)((char*)this + 0xd8) = *(float*)data;
        }
        return false;
    case 0x109d372:
        if (*(float*)data > 0.0f) {
            *(float*)((char*)this + 0xb8) = *(float*)data;
            *(float*)((char*)this + 0xb4) = *(float*)data;
        }
        return false;
    case 0x109d375:
        if (*(float*)data > 0.0f) {
            *(float*)((char*)this + 0xc8) = *(float*)data;
            *(float*)((char*)this + 0xc4) = *(float*)data;
        }
        return false;
    default:
        return false;
    }
}

// ---------------------------------------------------------------------------
// Command-line / plugin automation cluster (EH-heavy; best-effort).
// ---------------------------------------------------------------------------
struct IConfigManager2 {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11(int);
    virtual unsigned int v12(unsigned int);   // slot 12 (0x30), returns an id
};
void* SP_ConfigManager();   // 0x0067dd30

void EDealloc(void* p);      // 0x00f47380
struct Str {                 // EA::string8 (cString8)
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mAlloc;
    ~Str() { if ((int)(mpCapacity - mpBegin) > 1 && mpBegin != 0) EDealloc(mpBegin); }
};

void Sprintf8(char*, const char*, ...);      // 0x00938470

int g_1638280;
int g_1638284;

// ---------------------------------------------------------------------------
// 0x007db060  ManifestSource::Load (shared with slice 19)
// ---------------------------------------------------------------------------
struct ManifestSource2 {
    char pad[8];
    void* (*mNext)();
    void Load();
};

void ManifestSource2::Load()
{
    IConfigManager2* cm = (IConfigManager2*)SP_ConfigManager();
    if (!cm)
        return;
    int* entry = (int*)mNext();
    while (entry) {
        int value;
        sscanf(*(const char**)((char*)entry + 4), "%x", &value);
        cm->v11(value);
        entry = (int*)mNext();
    }
}

// ---------------------------------------------------------------------------
// 0x007db1b0 / 0x007db2a0  run config-configured automate commands.
// ---------------------------------------------------------------------------
void EDealloc(void* p);      // 0x00f47380
struct SimVecU {             // SP::SimpleVector<unsigned int> (0x004cd3c0 = resize)
    unsigned int* mpBegin;
    unsigned int* mpEnd;
    unsigned int* mpCapacity;
    void resize(unsigned int n);          // 0x004cd3c0
    ~SimVecU() { if (mpBegin[-1] != 0) EDealloc(mpBegin); }
};

struct AutomateRunner {
    char pad0[0xc];
    void (__cdecl* mLog2)(void*);                          // +0xc
    void (__cdecl* mLog1)(char*, int, unsigned int*);      // +0x10
    char pad1[0x18];
    HMODULE mModule;        // +0x2c
    void ListCommands();    // 007db1b0
    void ListCommands2();   // 007db2a0
};
void SP_PluginLoad(void*, const char*, int);   // 007db0c0
void* SP_PluginManagerGlobal;                  // 0x1638254

void AutomateRunner::ListCommands()
{
    IConfigManager2* cm = (IConfigManager2*)SP_ConfigManager();
    if (!cm)
        return;
    SimVecU v;
    v.mpBegin = 0; v.mpEnd = 0; v.mpCapacity = 0;
    v.resize(9);
    v.mpBegin[0] = 0x046170a6;
    v.mpBegin[1] = 0x0461709e;
    v.mpBegin[2] = 0x0461709f;
    unsigned int n = (unsigned int)(((int)v.mpEnd - (int)v.mpBegin) >> 2);
    for (unsigned int i = 0; i < n; ++i) {
        unsigned int id = cm->v12(v.mpBegin[i]);
        char buf[36];
        Sprintf8(buf, "%x", v.mpBegin[i]);
        mLog1(buf, 2, &id);
    }
}

struct CmdMsg {
    int mType;        // +0x00
    char* mText;      // +0x04
    int a08;          // +0x08
    int a0c;          // +0x0c
    int a10;          // +0x10
    int a14;          // +0x14
    int a18;          // +0x18
    int a1c;          // +0x1c
    int a20;          // +0x20
    char pad[0x14];   // +0x24 .. +0x38
};

void AutomateRunner::ListCommands2()
{
    IConfigManager2* cm = (IConfigManager2*)SP_ConfigManager();
    if (!cm)
        return;
    SimVecU v;
    v.mpBegin = 0; v.mpEnd = 0; v.mpCapacity = 0;
    v.resize(9);
    v.mpBegin[0] = 0x046170a6;
    v.mpBegin[1] = 0x0461709e;
    v.mpBegin[2] = 0x0461709f;
    unsigned int n = (unsigned int)(((int)v.mpEnd - (int)v.mpBegin) >> 2);
    for (unsigned int i = 0; i < n; ++i) {
        char buf[32];
        Sprintf8(buf, "%x", v.mpBegin[i]);
        CmdMsg m = {};
        m.mType = 2;
        m.mText = buf;
        m.a10 = 1;
        m.a18 = 3;
        m.a20 = 3;
        mLog2(&m);
    }
}

// ---------------------------------------------------------------------------
// 0x007db3a0  CommandRunner::Run  (parse "-openautomate ...")
// ---------------------------------------------------------------------------
int FUN_0092b200(const wchar_t*, int, int, int, int);  // 0x0092b200
int FUN_008d3ac0();                                    // 0x008d3ac0
void* FUN_0092b1b0(int);                               // 0x0092b1b0
void  EA_ConvertToString8(void*, void*);               // 0x0093c570
extern "C" int __stdcall FreeLibrary(void*);           // kernel32

struct WideStr {                 // EA::string16-like object returned by 0x0092b1b0
    const wchar_t* mpBegin;
    const wchar_t* mpEnd;
};

struct PluginLoader {            // 0x007db0c0  (Loads a plugin DLL by name)
    bool Load(const char* name, char* afterSemi);
};

struct CommandRunner {
    char pad0[4];
    int (__cdecl* mReadCmd)(int*);   // +0x4
    char pad2[0x24];
    HMODULE mModule;                 // +0x2c
    bool Run(const char* args, char* flagOut);
};

bool CommandRunner::Run(const char* args, char* flagOut)
{
    (void)args;
    *flagOut = 0;
    int idx = FUN_0092b200(L"-openautomate", 1, 0, 0, 0);
    if (idx == -1)
        return false;
    if (idx + 1 >= FUN_008d3ac0())
        return false;
    *flagOut = 1;
    WideStr* ws = (WideStr*)FUN_0092b1b0(idx + 1);
    const wchar_t* wp = ws->mpBegin;
    unsigned int wcount = (unsigned int)(ws->mpEnd - wp) >> 1;
    int semi = -1;
    for (unsigned int k = 0; k < wcount; ++k) {
        if (wp[k] == L';') { semi = (int)k; break; }
    }
    Str s;
    EA_ConvertToString8(&s, ws);
    char buf[1024];
    strcpy(buf, s.mpBegin);
    char* rest = buf + (int)(s.mpEnd - s.mpBegin);
    if (semi >= 0) {
        buf[semi] = 0;
        rest = buf + semi + 1;
    }
    if (((PluginLoader*)this)->Load(buf, rest)) {
        *flagOut = 0;
        int c = 0;
        for (;;) {
            c = 0;
            c = ((int (__cdecl*)(int*))*(void**)((char*)this + 4))(&c);
            switch (c) {
            case 0: *flagOut = 1; goto flush;
            case 2: ((AutomateRunner*)this)->ListCommands2(); break;
            case 3: ((AutomateRunner*)this)->ListCommands(); break;
            case 4: ((ManifestSource2*)this)->Load(); break;
            }
            if (*flagOut) goto flush;
            if (c == 1) break;
        }
flush:
        if (mModule) {
            FreeLibrary(mModule);
            mModule = 0;
            memset(this, 0, 0x2c);
        }
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x007db570  automation entry point (registers an atexit handler).
// ---------------------------------------------------------------------------
extern "C" void __cdecl SporeAutomateAtExit();
extern "C" int  __cdecl atexit(void (__cdecl*)(void));

void SP_AutomateEntry(int a, int b)
{
    if (!(g_1638284 & 1)) {
        g_1638284 |= 1;
        g_1638280 = 0;
        atexit(SporeAutomateAtExit);
    }
    ((CommandRunner*)&SP_PluginManagerGlobal)->Run((const char*)a, (char*)b);
}

// ---------------------------------------------------------------------------
// 0x007db650  cPackManager::Init
// ---------------------------------------------------------------------------
extern void* vtPropFilter[];                  // 0x013f662c
extern void* vtIMsgHandler[];                 // 0x013eb394
extern int g_153ed8c;                         // filter argument
void* __cdecl operator new(unsigned int, const char*, int, int, const char*, int) throw(); // 0x00f473a0
void __cdecl operator delete(void*, const char*, int, int, const char*, int) throw(); // 0x00f47380 placement delete
void __cdecl EDealloc(void*);                 // 0x00f47380

struct PackKey3 { uint32_t a, b, c; PackKey3() { a = 0; b = 0; c = 0; } };
struct PackCString {                          // SP::cString (0x14 bytes)
    uint32_t d[5];
    PackCString();                            // 0x006b5060
};
struct PackLocStr {                           // SP::cLocalizedString-like: 3 words, then the placeholder cString
    uint32_t a, b, c;
    PackCString mPlaceholderId;               // +0xc (absolute +0x24)
    PackLocStr() : a(0), b(0), c(0) {}
};
struct PackInfo {
    int mPackId;                // +0x0
    int mSequenceNumber;        // +0x4
    uint32_t mLayoutID;         // +0x8
    PackKey3 mButtonIconKey;    // +0xc
    PackLocStr mName;           // +0x18
};

struct PackVariant { uint32_t f0, f4, f8, fc; uint16_t flags, typeId; };
struct IPackProps {
    virtual void AddRef();                    // +0x0
    virtual void Release();                   // +0x4
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, PackVariant** out);   // +0x24
};
struct IPackPropMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void GetPropList(uint32_t inst, uint32_t grp, IPackProps** out);   // +0x2c
};
struct IPackResMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual int GetRecordKeyList(void* outVec, void* filter, void* dbs);       // +0x38
};
IPackResMgr* __cdecl PackGetManager();        // 0x0067dcd0  EA::ResourceMan::GetManager
IPackPropMgr* __cdecl PackPropertyManager();  // 0x0067de30  SP::PropertyManager
void __cdecl GetPropertyAsText(IPackProps*, uint32_t, void*);        // 0x006a1360
void __cdecl GetPropertyAsKeyInstance(IPackProps*, uint32_t, void*); // 0x006a12a0
void __cdecl GetPropertyAsKey(IPackProps*, uint32_t, void*);         // 0x006a1250

struct PackAutoRef {                          // EA::AutoRefCount<IPackProps>
    IPackProps* p;
    PackAutoRef() { p = 0; }
    ~PackAutoRef() { if (p) p->Release(); }
    IPackProps** Out() { if (p) { IPackProps* t = p; p = 0; t->Release(); } return &p; }
};

struct PackKeyVec {
    PackKey3* b; PackKey3* e; PackKey3* c;
    ~PackKeyVec() { if (b && ((int*)b)[-1]) EDealloc(b); }
};
struct PackFilter {
    void* vt; uint32_t id; int arg;
    ~PackFilter() { vt = vtIMsgHandler; }
};

struct PackInfoVec2 {
    PackInfo** mpBegin; PackInfo** mpEnd; PackInfo** mpCapacity;
    void DoInsertValue(PackInfo** pos, PackInfo* const& v);   // 0x00690b80
};

struct cPackManager {
    PackInfoVec2 mAvailablePacks;   // +0x0 (retail: stored at +0 of the manager object)
    bool Init();
};

// @ 0x007db650
bool cPackManager::Init()
{
    PackKeyVec keys;
    keys.b = 0; keys.e = 0; keys.c = 0;
    PackFilter filt;
    filt.vt = vtPropFilter;
    filt.id = 0xb1b104;
    filt.arg = g_153ed8c;
    PackGetManager()->GetRecordKeyList(&keys, &filt, 0);
    PackKey3* end = keys.e;
    for (PackKey3* it = keys.b; it != end; ++it) {
        PackKey3 key;
        key.a = it->a; key.b = it->b; key.c = it->c;
        PackAutoRef list;
        IPackPropMgr* pm = PackPropertyManager();
        pm->GetPropList(key.a, key.c, list.Out());
        if (list.p) {
            PackInfo* info = new ("App", 0, 0, 0, 0) PackInfo();
            info->mPackId = key.a;
            GetPropertyAsText(list.p, 0xfe1e2bc2, &info->mName.mPlaceholderId);
            PackVariant* v;
            if (list.p && list.p->GetProperty(0x5d1a718, &v) && v->typeId == 9) {
                int* val = (int*)v;
                if (v->flags & 0x30)
                    val = *(int**)v;
                info->mSequenceNumber = *val;
            }
            GetPropertyAsKeyInstance(list.p, 0x5dfef47, &info->mLayoutID);
            GetPropertyAsKey(list.p, 0x5e4de4e, &info->mButtonIconKey);
            GetPropertyAsKey(list.p, 0x5dfef48, &info->mName);
            PackInfo** e2 = mAvailablePacks.mpEnd;
            PackInfo** pos;
            for (pos = mAvailablePacks.mpBegin; pos != e2; ++pos) {
                if (info->mSequenceNumber < (*pos)->mSequenceNumber)
                    break;
            }
            if (pos == e2 && e2 < mAvailablePacks.mpCapacity) {
                mAvailablePacks.mpEnd = e2 + 1;
                if (e2) *e2 = info;
            } else {
                mAvailablePacks.DoInsertValue(pos, info);
            }
        }
    }
    return true;
}
