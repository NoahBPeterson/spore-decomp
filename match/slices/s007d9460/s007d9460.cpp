// Slice s007d9460 (batch w2g5): SP::cMouseCameraController — config refresh,
// config-value setter, start-state capture, quaternion->matrix helper, ctor.
// Retail module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE
#include "types.h"
#include <math.h>

typedef unsigned int size_type;
typedef int ptrdiff_t;

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define ALLOC_NAME "App"

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
void* operator new(size_t, void* p) { return p; }
void ea_free(void* p);

// helpers defined elsewhere (masked relocations)
void* Sub_6a3430(void* out, const float* m);          // matrix assignment
void* Sub_4a9b40(void* out, const float* q);          // quaternion -> transform
void  Matrix3_Assign(void* dst, const void* src);     // 0x0041cb40
float* Property_GetFloat(void* prop);                 // 0x0041ea70
char*  Property_GetBool(void* prop);                  // 0x0041e920

struct Vec3 { float x, y, z; };
struct tLerpAngle  { float mCurrent; float mTarget; int mSteps; float mMinChange; };   // 0x10
struct tLerpVector { Vec3 mCurrent; Vec3 mTarget; float mMinChange; int mSteps; };     // 0x20
struct cSPMatrix3 { float m[9]; };

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
    cSPMatrix3  mCameraBaseOrientation;   // +0x78
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

    void ConfigUpdated();                                 // @ 0x007d9460
    bool SetConfigValue(unsigned id, const void* value);  // @ 0x007d9c40
    bool Begin(int unused, float anchorX, float anchorY, int unused2); // @ 0x007d9bd0
    cMouseCameraController(cPropertyList* config);          // @ 0x007d9fb0
};

// @ 0x007d9a50  quaternion (x,y,z,w) -> 3x3 matrix, then Sub_6a3430(out, matrix)
void* QuatToMatrix(void* out, const float* q) {
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
bool cMouseCameraController::Begin(int, float anchorX, float anchorY, int) {
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

// Config lookups: vtable[0x1c] tests existence, vtable[0x28] returns the record.
struct PropRec { void** vtbl; int unk4; unsigned short unk10; unsigned short mType; };

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

static bool ConfigGetBool(cPropertyList* cfg, unsigned id, bool* out) {
    if (cfg == 0)
        return false;
    void* rec = 0;
    if (!((bool(__thiscall*)(void*, unsigned, void**))(*(void***)cfg)[0x24 / 4])(cfg, id, &rec))
        return false;
    if (*(unsigned short*)((char*)rec + 0x12) != 1)
        return false;
    *out = *Property_GetBool(rec);
    return true;
}

// @ 0x007d9460
void cMouseCameraController::ConfigUpdated() {
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

// @ 0x007d9c40
bool cMouseCameraController::SetConfigValue(unsigned id, const void* value) {
    const float* p = (const float*)value;
    switch (id) {
    case 0x101b534:
        mSubjectPosition.mCurrent.x = p[0];
        mSubjectPosition.mTarget.x = p[0];
        mSubjectPosition.mCurrent.y = p[1];
        mSubjectPosition.mTarget.y = p[1];
        mSubjectPosition.mCurrent.z = p[2];
        mSubjectPosition.mTarget.z = p[2];
        mCamOffset.mCurrent.x = 0.0f;
        mCamOffset.mTarget.x = 0.0f;
        mCamOffset.mCurrent.y = 0.0f;
        mCamOffset.mTarget.y = 0.0f;
        mCamOffset.mCurrent.z = mCamOffset.mCurrent.z;
        mCamOffset.mTarget.z = mCamOffset.mCurrent.z;
        return true;
    case 0x101b537:
        mSubjectPosition.mCurrent.x = p[0];
        mSubjectPosition.mTarget.x = p[0];
        mSubjectPosition.mCurrent.y = p[1];
        mSubjectPosition.mTarget.y = p[1];
        mSubjectPosition.mCurrent.z = p[2];
        mSubjectPosition.mTarget.z = p[2];
        mCamOffset.mCurrent.z = mCamOffset.mCurrent.z;
        mCamOffset.mTarget.z = mCamOffset.mCurrent.z;
        return true;
    case 0x101b543:
    case 0x101d576: {
        float m[9];
        QuatToMatrix(m, p);
        mCameraTheta.mCurrent = -m[2];
        mCameraTheta.mTarget = -m[2];
        mCameraPhi.mCurrent = -m[1];
        mCameraPhi.mTarget = -m[1];
        mCameraRoll.mCurrent = -m[0];
        mCameraRoll.mTarget = -m[0];
        return true;
    }
    case 0x101d445:
        mCamOffset.mCurrent.z = p[0];
        mCamOffset.mTarget.z = p[0];
        return true;
    case 0x101d4c7:
        mCamOffset.mTarget.z = p[0];
        return true;
    case 0x101d51f: {
        float m[9];
        QuatToMatrix(m, p);
        mCameraRoll.mCurrent = -m[0];
        mCameraRoll.mTarget = -m[0];
        mCameraTheta.mCurrent = -m[2];
        mCameraTheta.mTarget = -m[2];
        mCameraPhi.mCurrent = -m[1];
        mCameraPhi.mTarget = -m[1];
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
        mCameraMinZoomDistance = p[0];
        return true;
    case 0x479c05b: {
        float m[9];
        Sub_4a9b40(m, p);
        for (int i = 0; i < 9; ++i)
            mCameraBaseOrientation.m[i] = m[i];
        return true;
    }
    default:
        return false;
    }
}

// @ 0x007d9fb0
cMouseCameraController::cMouseCameraController(cPropertyList* config) {
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
    {
        const float ident[9] = { 1,0,0, 0,1,0, 0,0,1 };
        Matrix3_Assign(&mCameraBaseOrientation, ident);
    }
    mCameraMinZoomDistance = 1.0f;
    mCameraMaxZoomDistance = 10000.0f;
    mStartCameraTheta = 0.0f;
    mStartCameraPhi = 0.0f;
    mStartCameraDistance = 0.0f;
    mStartCameraOffsetX = 0.0f;
    mStartCameraOffsetY = 0.0f;
    mCameraMaxPitch = 1.5533431f;
    mCameraMinPitch = -1.5533431f;
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
