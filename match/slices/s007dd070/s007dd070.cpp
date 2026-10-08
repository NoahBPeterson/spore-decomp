// Slice s007dd070: SP::cSmoothCameraController::Update (0x007dd070, 2049 bytes).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast.
//
// ICamera::Update(int deltaTime, cViewer* viewer), __thiscall, ret 8.  Per-frame update of the smooth
// camera: when a modal dialog loop is running the keyboard inputs are cleared, then every buffered value
// (tLerpScalar / tLerpVector3 / tLerpAngle / tLerpQuaternion members) takes one step of 0.1 towards its
// target (scalars snap to the target when closer than mMinChange), the discrete orientation index is
// wrapped, and, if a viewer was passed, the camera position/orientation is evaluated on the camera curve
// (virtual slot 55), and near/far plane, view angle and camera transform are pushed into the viewer.
// The layout is the retail one (see s007dd880.h: every eastl vector has one extra dword vs the 2008 PDB).
#include "types.h"
#include <math.h>

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
struct tLerpScalar {                                                                                 // 0x10
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
struct tLerpVector3 { Vec3 mCurrent; Vec3 mTarget; int mSteps; float mMinChange; };              // 0x20
struct tLerpQuaternion { Quat mCurrent; Quat mTarget; int mSteps; float mMinChange; };           // 0x28

struct FloatVec {                                   // eastl::vector<float>, 5 words
    float* mpBegin; float* mpEnd; float* mpCapacity; const char* mpName; int mpAllocExtra;
    int size() const { return (int)(mpEnd - mpBegin); }
    float& operator[](int i) { return mpBegin[i]; }
};

// ---- globals (constants in .data) ----
extern Vec3 g_kVec3Zero3;               // 0x016389dc
extern Quat g_kQuatIdent;               // 0x016389f8
extern Matrix3 g_kMatrix3Identity;      // 0x01638b1c
extern bool g_cameraDebug;              // 0x016389d0 (debug flag, name coined)
extern const float kPi;                 // 0x0153efc8 (literal 3.1415927f)

// ---- Transform (retail layout, size 0x38) ----
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

struct cSmoothCameraController : cICameraControllerBase, cIHandlerBase, cRefCountBase {
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
    tLerpScalar mBufferedHeading;               // +0x98 (angle, wrapped to [-pi, pi))
    tLerpScalar mBufferedDistanceAlongCurve;    // +0xa8
    tLerpScalar mBufferedNearClip;              // +0xb8
    tLerpScalar mBufferedFarClip;               // +0xc8
    tLerpScalar mBufferedFOV;                   // +0xd8
    tLerpScalar mBufferedPitchParam;            // +0xe8
    tLerpVector3 mBufferedSubjectPosition;      // +0xf8
    tLerpVector3 mBufferedLookAtPosition;       // +0x118
    FloatVec mFOVLevels;                        // +0x138
    FloatVec mOrientations;                     // +0x14c
    int mCurrentOrientation;                    // +0x160
    Vec3 mDraggedVelocity;                      // +0x164
    unsigned mPositionInterpolationSteps;       // +0x170
    float mTranslationInputVelocity;            // +0x174
    Vec3 mxyzSubjectOffset;                     // +0x178
    tLerpQuaternion mRelativeOrientation;       // +0x184
    float mHeadingRelative;                     // +0x1ac
    bool mTracking, mReadFromStream, mAdjustablePitch, mbInModalDialogLoop;   // +0x1b0
    int mStartMouseWheelLevel;                  // +0x1b4
    tLerpScalar mKeyboardRotation;              // +0x1b8
    tLerpScalar mKeyboardZoomDelta;             // +0x1c8
    tLerpVector3 mKeyboardTranslation;          // +0x1d8

    void Update(int deltaTime, cViewer* viewer);
};

static const float kRadToDeg = 57.29578f;       // literal at 0x01412aa4

// @ 0x007dd070
void cSmoothCameraController::Update(int deltaTime, cViewer* viewer)
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
