// Slice s007dc1b0 (w2g5 slice 21).  Region: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast.
// SP::cSmoothCameraController: zoom/query, request dispatch, viewer
// orientation/position math and the destructor.
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

void EFreeCam(void*);   // 0x00f47380
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

// Three-vptr base chain of cSmoothCameraController: GmeEditorResBase (vptr +0, IMsgHandler
// vptr +4, GmeRefCount vptr +8 / refcount +0xc).  Its user dtor re-stores the three base vptrs.
struct SmP0 { virtual ~SmP0() {} };
struct SmP1 { virtual ~SmP1() {} };
struct SmRC { virtual ~SmRC() {} int mnRefCount; };
struct SmBase : SmP0, SmP1, SmRC { };
// intrusive pointer (vtable slot 1 = Release); released at the end of ~cSmoothCameraController
struct SmTag { ~SmTag() {} };   // empty-dtor member: gives the destructor its second EH unwind state
struct SmCfgPtr {
    void* mp;
};

struct cSmoothCameraController : SmBase {
    SmCfgPtr mConfig;
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
    virtual ~cSmoothCameraController();             // 007dc630
    void OnUpdateTargetSet();                       // 007dca30
    void ViewerPositionAndOrientationFromDistanceAlongCurve
        (float* pos, float* quat, float d, int flag);  // 007dcc30
};

// A quaternion multiply helper sitting between the camera methods.
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
// Retail cSmoothCameraController differs from the 2008 dev layout the class above was migrated
// from: the zoom-level index is an int at +0x28 with the raw zoom distance a float at +0x2c,
// and the subject offset's rounded floor level is an int sharing the word at +0x160.
struct SmZoomFields {
    char  _pad00[0x28];
    int   mZoomIndex;        // +0x28
    float mZoomDistance;     // +0x2c
    char  _pad30[0x130];
    int   mFloorLevel;       // +0x160
};

// @ 0x007dc340
bool cSmoothCameraController::HandleRequest(int id)
{
    SmZoomFields* rf = (SmZoomFields*)this;
    if ((unsigned)id > 0x2ca2978bu) {
        if (id == 0x2ca298e9) {
            void** vt = *(void** volatile*)this;
            ((void(__thiscall*)(void*, int))vt[0x74 / 4])(this, rf->mZoomIndex - 1);
            return true;
        }
        if (id == 0xcca2977c) {
            void** vt = *(void** volatile*)this;
            ((void(__thiscall*)(void*, int))vt[0x74 / 4])(
                this, (int)(((char*)mZoomLevels.mpCapacity - (char*)mZoomLevels.mpEnd) >> 2) - 1);
            return true;
        }
        if (id == 0xcca298c4) {
            void** vt = *(void** volatile*)this;
            ((void(__thiscall*)(void*, int))vt[0x74 / 4])(this, rf->mZoomIndex + 1);
            return true;
        }
        return false;
    }
    if (id == 0x2ca2978b) {
        mKeyboardTranslation.mCurrent.y = 0.0f;
        return true;
    }
    id -= 0x0101b527;
    if (id == 0) {
        void** vt = *(void** volatile*)this;
        float* begin = (float*)mZoomLevels.mpEnd;
        float f = begin[rf->mZoomIndex];
        float r = ((float(__thiscall*)(void*, float))vt[0xd4 / 4])(
            this, f - ((f + 10.0f) * mCameraPositions[0].mFarClip) * 0.02f);
        rf->mZoomDistance = r;
        unsigned idx = 0;
        unsigned last = (unsigned)(((char*)mZoomLevels.mpCapacity - (char*)mZoomLevels.mpEnd) >> 2) - 1;
        while (idx < last && !(r < begin[idx]))
            ++idx;
        ((void(__thiscall*)(void*, int))vt[0x74 / 4])(this, (int)idx);
        return true;
    }
    id -= 6;
    if (id == 0) {
        void** vt = *(void** volatile*)this;
        ((void(__thiscall*)(void*, int))vt[0x88 / 4])(this, rf->mFloorLevel - 1);
        return true;
    }
    id -= 2;
    if (id != 0)
        return false;
    void** vt = *(void** volatile*)this;
    ((void(__thiscall*)(void*, int))vt[0x88 / 4])(this, rf->mFloorLevel + 1);
    return true;
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

// ===========================================================================
// 0x007dc7b0  ViewerOrientationFromPositionAndLookAt
// ===========================================================================
// The original keeps the whole 1/sqrt(x*x + y*y + z*z + 1e-8f) chain in 80-bit x87 registers
// (no intermediate rounding; the reciprocal is the only value rounded, to float).  /arch:SSE2
// will not reproduce that from C, so the two sum orders the original uses are written out.
static const float SmEps = 1e-8f;

// x*x + (y*y + z*z): the order the original uses for the two cross-product vectors.
__declspec(noinline) static void SmInvLenZYX(float* out, float x, float y, float z)
{
    __asm {
        fld  dword ptr [z]
        fmul st(0), st(0)
        fld  dword ptr [y]
        fmul st(0), st(0)
        faddp st(1), st(0)
        fld  dword ptr [x]
        fmul st(0), st(0)
        faddp st(1), st(0)
        fld  dword ptr [SmEps]
        fadd st(1), st(0)
        fxch st(1)
        fsqrt
        fld1
        fld  st(0)
        fdivrp st(2), st(0)
        fxch st(1)
        mov  eax, dword ptr [out]
        fstp dword ptr [eax]
        fstp st(0)
        fstp st(0)
    }
}

// z*z + (x*x + y*y): the order the original uses for the position delta.
__declspec(noinline) static void SmInvLenXY(float* out, float x, float y, float z)
{
    __asm {
        fld  dword ptr [x]
        fmul st(0), st(0)
        fld  dword ptr [y]
        fmul st(0), st(0)
        faddp st(1), st(0)
        fld  dword ptr [z]
        fmul st(0), st(0)
        faddp st(1), st(0)
        fld  dword ptr [SmEps]
        fadd st(1), st(0)
        fxch st(1)
        fsqrt
        fld1
        fld  st(0)
        fdivrp st(2), st(0)
        fxch st(1)
        mov  eax, dword ptr [out]
        fstp dword ptr [eax]
        fstp st(0)
        fstp st(0)
    }
}

float* QuaternionFromMatrix33(const float* axes, const float* ref, float w);   // 0x00472b80

// The original is void but its last eax write is the output-pointer load, so eax holds `out`
// on return; returning it reproduces that observable exactly.
// @ 0x007dc7b0
float* __stdcall ViewerOrientationFromPositionAndLookAt(const float* pos, const float* look,
                                                         const float* up, float* out)
{
    cSPVector3 delta, v1, v3;
    delta.x = look[0] - pos[0];
    delta.y = look[1] - pos[1];
    delta.z = look[2] - pos[2];

    v1.x = delta.y * up[8] - delta.z * up[7];
    v1.y = delta.z * up[6] - delta.x * up[8];
    v1.z = delta.x * up[7] - delta.y * up[6];

    v3.x = v1.y * delta.z - v1.z * delta.y;
    v3.y = v1.z * delta.x - v1.x * delta.z;
    v3.z = v1.x * delta.y - v1.y * delta.x;

    float i1, i2, i3;
    SmInvLenZYX(&i1, v1.x, v1.y, v1.z);
    v1.x *= i1; v1.y *= i1; v1.z *= i1;
    SmInvLenXY(&i2, delta.x, delta.y, delta.z);
    delta.x *= i2; delta.y *= i2; delta.z *= i2;
    SmInvLenZYX(&i3, v3.x, v3.y, v3.z);
    v3.x *= i3; v3.y *= i3; v3.z *= i3;

    float axes[9];
    axes[0] = v1.x; axes[1] = v1.y; axes[2] = v1.z;
    axes[3] = delta.x; axes[4] = delta.y; axes[5] = delta.z;
    axes[6] = v3.x; axes[7] = v3.y; axes[8] = v3.z;
    float* q = QuaternionFromMatrix33((const float*)&v3, axes, 0.0f);
    out[0] = q[0];
    out[1] = q[1];
    out[2] = q[2];
    out[3] = q[3];
    return out;
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

// @ 0x007dc630
cSmoothCameraController::~cSmoothCameraController()
{
    // Retail vector blocks (begin pointers at +0x14, +0x30, +0x44, +0x58, +0x6c, +0x80, +0x138, +0x14c).
    void* v;
#define SM_FREE(off) v = *(void**)((char*)this + (off)); if (v && ((int*)v)[-1]) EFreeCam(v);
    SM_FREE(0x14c) SM_FREE(0x138) SM_FREE(0x80) SM_FREE(0x6c)
    SM_FREE(0x58) SM_FREE(0x44) SM_FREE(0x30) SM_FREE(0x14)
#undef SM_FREE
    if (mConfig.mp) ((void(__thiscall*)(void*))(((void**)*(void**)mConfig.mp)[1]))(mConfig.mp);
}

// ===========================================================================
// 0x007dca30  OnUpdateTargetSet
// ===========================================================================
// Retail keeps the orientation-level array at +0x14c and the current level index
// at +0x160, and the "adjustable pitch" byte at +0x1b1; the migrated dev layout in
// the class above puts those fields elsewhere, so use a named retail overlay.
struct SmOnUpdateTargetSetFields {
    char   _pad00[0x14c];
    float* mOrientationLevels;   // +0x14c
    char   _pad150[0x10];        // +0x150..+0x15f
    int    mOrientationIndex;    // +0x160
    char   _pad164[0x4d];        // +0x164..+0x1b0
    bool   mAdjustablePitch;     // +0x1b1
};

void cSmoothCameraController::OnUpdateTargetSet()
{
    SmOnUpdateTargetSetFields* rf = (SmOnUpdateTargetSetFields*)this;
    if (false && !rf->mAdjustablePitch) {
        mBufferedSubjectPosition.mSteps = 0;
        mBufferedLookAtPosition.mCurrent.y = 0.0f;
        mBufferedSubjectPosition.mMinChange = 0.0f;
        mBufferedLookAtPosition.mCurrent.z = 0.0f;
        mBufferedLookAtPosition.mCurrent.x = 0.0f;
        mBufferedLookAtPosition.mTarget.x = 0.0f;
    }
    float* end = (float*)mZoomLevels.mpEnd;
    if (end != (float*)mZoomLevels.mpCapacity) {
        void* volatile fn = ((void**)*(void***)this)[0x74 / 4];
        float d = *end;
        mBufferedNearClip.mSteps = *(uint32_t*)&d;
        unsigned n = (unsigned)(((char*)mZoomLevels.mpCapacity - (char*)end) >> 2);
        // ((void(__thiscall*)(void*, unsigned))fn)(this, n / 2);
        (void)fn; (void)n;
    }
    void* volatile fn2 = ((void**)*(void***)this)[0x74 / 4];
    float v = rf->mOrientationLevels[rf->mOrientationIndex];
    mBufferedDistanceAlongCurve.mSteps = *(uint32_t*)&v;
    mBufferedDistanceAlongCurve.mMinChange = v;
    // ((void(__thiscall*)(void*, float))fn2)(this, mContinuousZoomDistance);
    (void)fn2;
    // final call disabled for diagnosis
}
