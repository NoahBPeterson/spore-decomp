// Slice s007da2d0 (w2g5 slice 19).  Region: /O2 /MD /Gy /EHsc /TP /arch:SSE2.
// SP::cMouseCameraController methods (camera motion/mouse handling), plus the
// Swarm offline-world runner and the plugin loader helpers that follow it.
#include "types.h"
#include <math.h>
#include <stdio.h>
#pragma intrinsic(expf, fabsf)

typedef void* HMODULE;
typedef const char* LPCSTR;
typedef int BOOL;
typedef void* FARPROC;

// ---------------------------------------------------------------------------
// Swarm math types (layouts from the 2008 dev-build PDB).
// ---------------------------------------------------------------------------
namespace rw { namespace math { namespace fpu {
struct Vector3Template {
    float x, y, z;
};
struct Matrix33Template {
    float m[9];
    void Assign(const Matrix33Template&);   // 0x0041cb40
};
}}}  // namespace rw::math::fpu

typedef rw::math::fpu::Vector3Template cSPVector3;

namespace SP {
struct tLerpAngle {
    float mCurrent;     // +0x0
    float mTarget;      // +0x4
    uint32_t mSteps;    // +0x8
    float mMinChange;   // +0xc
};
struct tLerpScalar {
    float mCurrent;     // +0x0
    float mTarget;      // +0x4
    uint32_t mSteps;    // +0x8
    float mMinChange;   // +0xc
};
struct tLerpVector3 {
    cSPVector3 mCurrent;    // +0x0
    cSPVector3 mTarget;     // +0xc
    uint32_t mSteps;        // +0x18
    float mMinChange;       // +0x1c
};
}  // namespace SP

struct cSPMatrix3 : rw::math::fpu::Matrix33Template {};   // size 0x24

// EA::Swarm::cTransform (size 0x38).
struct cTransform {
    uint16_t mFlags;                 // +0x0
    uint16_t mModificationCount;     // +0x2
    cSPVector3 mTranslation;         // +0x4
    float mScale;                    // +0x10
    rw::math::fpu::Matrix33Template mRotation;  // +0x14
    cTransform();                            // 0x00409930
    void SetRotation(const cSPMatrix3&);     // 0x005b51b0
    void RotateY(float);                     // 0x004099b0
    void PreRotateX(float);                  // 0x005a2d90
    void Rotate(float);                      // 0x006b9050
};

// ---------------------------------------------------------------------------
// Globals / helpers from the binary.
// ---------------------------------------------------------------------------
struct RandomLinearCongruential {
    void SetSeed(int);                       // 0x00936090
    uint32_t RandomUint32Uniform();          // 0x009360b0
};
extern RandomLinearCongruential g_sRandom;

void* SP_ConfigManager();                    // 0x0067dd30

// The class under test.
namespace SP {

class cMouseCameraController {
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
    tLerpAngle mCameraTheta;                 // +0x48
    tLerpAngle mCameraPhi;                   // +0x58
    tLerpAngle mCameraRoll;                  // +0x68
    cSPMatrix3 mCameraBaseOrientation;       // +0x78
    tLerpVector3 mSubjectPosition;           // +0x9c
    tLerpScalar mFieldOfView;                // +0xbc
    tLerpVector3 mCamOffset;                 // +0xcc
    float mStartCameraTheta;                 // +0xec
    float mStartCameraPhi;                   // +0xf0
    float mStartCameraDistance;              // +0xf4
    float mStartCameraOffsetX;               // +0xf8
    float mStartCameraOffsetY;               // +0xfc
    cSPVector3 mStartSubjectPosition;        // +0x100
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
};

}  // namespace SP

// External editor/UI object used by 007da9f0 (only offsets matter).
struct cSwarmEditor {
    char pad[0x1c9];
};

void SetNearFarClipPlane(void*, float);   // 0x007c5350
void SetClipPlane1(void*, float);         // 0x007c4ba0
void SetClipPlane2(void*, float);         // 0x007c4bc0
void ApplyTransformToScene(void*, cTransform*);  // 0x007c4d00

static const float kPi      = 3.1415927410125732f;
static const float kNegFour = -4.0f;
static const float kFour    = 4.0f;
static const float k0025    = 0.0024999999441206455f;
static const float k01      = 0.10000000149011612f;
static const float kRadToDeg = 57.295780181884766f;

extern float g_subjectOrigin[3];          // 0x01637d78
extern const cSPMatrix3 g_identity3;      // 0x01637eb8

// ===========================================================================
// 0x007da2d0  cMouseCameraController::ApplyMotion
// ===========================================================================
void SP::cMouseCameraController::ApplyMotion(int mode, float a, float b)
{
    switch (mode) {
    case 0:
        mCameraTheta.mCurrent = mStartCameraTheta + kPi * a;
        mCameraTheta.mTarget  = mCameraTheta.mCurrent;
        mCameraPhi.mCurrent = mStartCameraPhi - kPi * b;
        if (mCameraPhi.mCurrent < mCameraMinPitch) mCameraPhi.mCurrent = mCameraMinPitch;
        if (mCameraPhi.mCurrent > mCameraMaxPitch) mCameraPhi.mCurrent = mCameraMaxPitch;
        mCameraPhi.mTarget = mCameraPhi.mCurrent;
        return;

    case 1: {
        a = a * kNegFour;
        b = b * kNegFour;
        if (mExponential) {
            float s = mStartCameraDistance * mExponentialPanScale;
            a = s * a;
            b = s * b;
        }
        if (mPanSubjectPos) {
            cTransform t;
            t.SetRotation(mCameraBaseOrientation);
            t.RotateY(-mCameraTheta.mCurrent);
            t.PreRotateX(mCameraPhi.mCurrent);
            t.Rotate(mCameraRoll.mCurrent);
            float* r = t.mRotation.m;
            mSubjectPosition.mCurrent.x = mStartSubjectPosition.x + r[0] * a - r[6] * b;
            mSubjectPosition.mCurrent.y = mStartSubjectPosition.y + r[1] * a - r[7] * b;
            mSubjectPosition.mCurrent.z = mStartSubjectPosition.z + r[2] * a - r[8] * b;
            mSubjectPosition.mTarget = mSubjectPosition.mCurrent;
        } else {
            mCamOffset.mCurrent.x = mStartCameraOffsetX + a;
            mCamOffset.mTarget.x  = mCamOffset.mCurrent.x;
            mCamOffset.mCurrent.y = mStartCameraOffsetY + b;
            mCamOffset.mTarget.y  = mCamOffset.mCurrent.y;
        }
        return;
    }

    case 2:
        a = a * kFour;
        break;
    case 3:
        a = b * kNegFour;
        break;
    case 4:
        if (fabsf(b) <= fabsf(a))
            a = a * kNegFour;
        else
            a = b * kNegFour;
        break;
    default:
        return;
    }

    if (mExponential) {
        mFieldOfView.mCurrent = expf(a) * mStartCameraDistance;
        mFieldOfView.mTarget  = mFieldOfView.mCurrent;
    } else {
        mFieldOfView.mCurrent = mStartCameraDistance + a;
        mFieldOfView.mTarget  = mFieldOfView.mCurrent;
    }
}

// ===========================================================================
// 0x007da5f0  cMouseCameraController::BuildTransform
// ===========================================================================
void SP::cMouseCameraController::BuildTransform(cTransform* out)
{
    if (mCamOffset.mCurrent.z < mCameraMinZoomDistance)
        mCamOffset.mCurrent.z = mCameraMinZoomDistance;
    if (mCamOffset.mCurrent.z > mCameraMaxZoomDistance)
        mCamOffset.mCurrent.z = mCameraMaxZoomDistance;

    out->SetRotation(mCameraBaseOrientation);
    out->RotateY(-mCameraTheta.mCurrent);
    out->PreRotateX(mCameraPhi.mCurrent);
    out->Rotate(mCameraRoll.mCurrent);

    float scale = out->mScale;
    float a = scale * mCamOffset.mCurrent.x;
    float b = scale * -mCamOffset.mCurrent.y;
    float c = scale * -mCamOffset.mCurrent.z;
    float* r = out->mRotation.m;
    out->mTranslation.x = ((r[6] * b + r[3] * c) + r[0] * a) + out->mTranslation.x;
    out->mTranslation.y = ((r[7] * b + r[4] * c) + r[1] * a) + out->mTranslation.y;
    out->mTranslation.z = ((r[8] * b + r[5] * c) + r[2] * a) + out->mTranslation.z;
    out->mFlags |= 4;
    out->mModificationCount += 1;

    out->mTranslation.x += mSubjectPosition.mCurrent.x;
    out->mTranslation.y += mSubjectPosition.mCurrent.y;
    out->mTranslation.z += mSubjectPosition.mCurrent.z;
    out->mFlags |= 4;
    out->mModificationCount += 1;
}

// ===========================================================================
// 0x007da790  SP::CreateMouseCameraController
// ===========================================================================
void* EAllocApp(int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
SP::cMouseCameraController* ConstructController(SP::cMouseCameraController*, void*);  // 0x007d9fb0

void* SP_CreateMouseCameraController(void* arg)
{
    SP::cMouseCameraController* p =
        (SP::cMouseCameraController*)EAllocApp(0x124, "App", 0, 0, 0, 0);
    if (p) {
        return ConstructController(p, arg);
    }
    return 0;
}

// ===========================================================================
// 0x007da800  cMouseCameraController::ProcessInput
// ===========================================================================
bool SP::cMouseCameraController::ProcessInput(float x, float y, int modifier)
{
    if (modifier == 0)
        return false;

    int mode = 0;
    float scale;
    if (!mIsMayaStyle) {
        if (modifier == 0x10 || modifier == 0x0a) {
            scale = mTranslateScale;
            mode = 1;
        } else if (modifier == 0x20 || modifier == 9) {
            scale = mZoomScale;
            mode = 3;
        } else if (modifier == 8) {
            scale = mRotateScale;
            mode = 0;
        } else {
            goto tail;
        }
    } else {
        if (modifier == 0x1c || modifier == 0x24) {
            scale = mZoomScale;
            mode = 4;
        } else if (modifier == 0x14) {
            scale = mTranslateScale;
            if (mPreviousModifiers[0] == 0x1c ||
                mPreviousModifiers[1] == 0x1c ||
                mPreviousModifiers[2] == 0x1c)
                goto tail;
        } else if (modifier == 0x0c) {
            scale = mRotateScale;
            if (mPreviousModifiers[0] == 0x1c ||
                mPreviousModifiers[1] == 0x1c ||
                mPreviousModifiers[2] == 0x1c)
                goto tail;
        } else {
            goto tail;
        }
    }

    ApplyMotion(mode,
                (x - mAnchorX) * scale * k0025,
                (y - mAnchorY) * scale * k0025);

tail:
    mPrevModIndex += 1;
    if (mPrevModIndex >= 3)
        mPrevModIndex = 0;
    mPreviousModifiers[mPrevModIndex] = modifier;
    return true;
}

// ===========================================================================
// 0x007da910  cMouseCameraController::StartDrag
// ===========================================================================
bool SP::cMouseCameraController::StartDrag(int a, int b, int c, int d)
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

// ===========================================================================
// 0x007da9f0  cMouseCameraController::Update
// ===========================================================================
void SP::cMouseCameraController::Update(int a, void* ed)
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

// ===========================================================================
// 0x007dad80  create/obtain an offline effect object
// ===========================================================================
struct IOfflineHost;
struct IOfflineEffect {
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual void v03(int);
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14(); virtual void v15();
    virtual void v16();
};
struct IOfflineHost {
    virtual IOfflineEffect* v00(int);
    virtual void v01(); virtual void v02();
    virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18();
    virtual IOfflineEffect* v19(int, const char*);
    virtual void v20();
    virtual IOfflineEffect* v21(int);
};

IOfflineEffect* FUN_007dad80(IOfflineHost* host)
{
    IOfflineEffect* e = host->v21(0x264fc2b);
    if (!e) {
        e = host->v19(0x264fc2b, "OfflineEffects");
        e->v03(4);
    }
    e->v13();
    e->v16();
    return e;
}

// ===========================================================================
// 0x007dade0  SP::SetEffectSeed
// ===========================================================================
void SP_SetEffectSeed(int seed)
{
    if (seed == 0 || seed == -1)
        seed = 0xdeadbeef;
    g_sRandom.SetSeed(seed);
    g_sRandom.RandomUint32Uniform();
    g_sRandom.RandomUint32Uniform();
    g_sRandom.RandomUint32Uniform();
}

// ===========================================================================
// 0x007db060  manifest callback loader
// ===========================================================================
struct IConfigManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual void v11(int, int);
};

struct ManifestSource {
    char pad[8];
    void* (*mNext)();      // +0x8
    void Load();
};

void ManifestSource::Load()
{
    IConfigManager* cm = (IConfigManager*)SP_ConfigManager();
    if (!cm)
        return;
    int* entry = (int*)mNext();
    while (entry) {
        int value;
        sscanf(*(const char**)((char*)entry + 4), "%x", &value);
        cm->v11(value, *(int*)((char*)entry + 8));
        entry = (int*)mNext();
    }
}

// ===========================================================================
// 0x007db0c0  plugin loader
// ===========================================================================
typedef HMODULE (__stdcall *LoadLibraryAFn)(LPCSTR);
typedef FARPROC (__stdcall *GetProcAddressFn)(HMODULE, LPCSTR);
typedef BOOL    (__stdcall *FreeLibraryFn)(HMODULE);

extern "C" __declspec(dllimport) HMODULE __stdcall LoadLibraryA(LPCSTR);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, LPCSTR);
extern "C" __declspec(dllimport) BOOL    __stdcall FreeLibrary(HMODULE);
void* __cdecl OpNewPlugin(void*, int, int);      // 0x011e073e
void  __cdecl VecDoInsertPlugin(void*, void*, int);  // 0x011e0744

struct PluginManager {
    char pad[0x2c];
    HMODULE mModule;        // +0x2c
    bool Load(const char* name, int param);
};

struct PluginInitArgs {
    int a, b, c, d;
};

bool PluginManager::Load(const char* name, int param)
{
    if (mModule) {
        FreeLibrary(mModule);
        mModule = 0;
        OpNewPlugin(this, 0, 0x2c);
    }
    mModule = LoadLibraryA(name);
    if (mModule) {
        OpNewPlugin(this, 0, 0x2c);
        FARPROC fn = GetProcAddress(mModule, "oaPluginInit");
        if (fn) {
            int result;
            int ret = ((int(__cdecl*)(int, int*, int, int, int, int))fn)
                          (param, &result, 0, 2, 0, 6);
            if (ret && result == 0) {
                int value = *(int*)ret;
                if (value >= 0x2c)
                    value = 0x2c;
                VecDoInsertPlugin(this, (void*)ret, value);
                return true;
            }
        }
    }
    if (mModule) {
        FreeLibrary(mModule);
        mModule = 0;
        OpNewPlugin(this, 0, 0x2c);
    }
    return false;
}

// ===========================================================================
// 0x007dae20  SP::RunOfflineWorld
// ===========================================================================
struct EA_Stopwatch {
    char mData[0x18];
    EA_Stopwatch(int mode, int flag);       // 0x0093a560
    int64_t GetTicks();                     // 0x0093a3a0
};

void* EA_GetMessagingServer();              // 0x00883860

// The vtable-bearing simulator / world objects are only accessed through their
// virtual slots; the slot offsets in the comments are the real ones.
struct SimObject {
    virtual void v00(); virtual void v01();
    virtual void v02(int);
    virtual void v03(int);
    virtual char v04();
};
struct WorldObject {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15(float, float, void*);
};

int SP_RunOfflineWorld(WorldObject* world, SimObject* sim, int seed, int dtMs,
                       float maxSeconds, int unused, float* outElapsed,
                       char verbose, void* effectName)
{
    if (seed == 0 || seed == -1)
        seed = 0xdeadbeef;
    g_sRandom.SetSeed(seed);
    g_sRandom.RandomUint32Uniform();
    g_sRandom.RandomUint32Uniform();
    g_sRandom.RandomUint32Uniform();

    int totalMs = 0;
    EA_Stopwatch sw(5, 0);
    sim->v02(0);

    float dt = (float)dtMs * 0.001f;
    float elapsed = 0.0f;
    char buffer[0x80];
    for (;;) {
        world->v15(dt, dt, buffer);
        totalMs += dtMs;
        elapsed = (float)sw.GetTicks();
        if (!sim->v04())
            break;
        if (!(maxSeconds > elapsed))
            break;
    }
    sim->v03(1);
    if (outElapsed)
        *outElapsed = elapsed;
    world->v13();
    if (verbose) {
        char text[512];
        sprintf(text, "Effect: %s, Duration: %d virtual ms in %g s (%g x)\n",
                effectName, totalMs, elapsed, (double)totalMs / (elapsed * 1000.0));
        void* server = EA_GetMessagingServer();
        ((void(__thiscall*)(void*, void*, const void*, int, int, char))
             (*(void***)server)[0x14 / 4])(server, text, NULL, 0, 0, 1);
    }
    return totalMs;
}

