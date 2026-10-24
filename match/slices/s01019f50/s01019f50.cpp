// Slice s01019f50 — SP space-game planet camera controller: source-interpolation
// setup, the shared camera-controller base constructor, two derived constructors,
// and the per-frame effect update.  /O2 /MD /Gy /EHsc /TP /arch:SSE.
#include "types.h"
#include <intrin.h>
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

// ---------------------------------------------------------------------------------------------
// math value types (rw::math::fpu)
// ---------------------------------------------------------------------------------------------
struct Vec4 { float x, y, z, w; };

struct Matrix34 {
    Vec4 xAxis;    // +0x00
    Vec4 yAxis;    // +0x10
    Vec4 zAxis;    // +0x20
};

struct Vec3Row {
    float x, y, z;
    Vec3Row() {}
    Vec3Row(const Vec4& v) : x(v.x), y(v.y), z(v.z) {}
};

struct Matrix33 {
    Vec3Row xAxis, yAxis, zAxis;
    Matrix33() {}
    Matrix33(const Matrix34& m) : xAxis(m.xAxis), yAxis(m.yAxis), zAxis(m.zAxis) {}
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3& operator=(const Vector3& o) {
        *(int*)&x = *(const int*)&o.x;
        *(int*)&y = *(const int*)&o.y;
        *(int*)&z = *(const int*)&o.z;
        return *this;
    }
};

struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(const Quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
};

Quaternion& QuaternionFromMatrix33(Quaternion& out, const Matrix33& m, float tolerance);   // 0x00472b80

// ---------------------------------------------------------------------------------------------
// SP::cViewer — the camera-to-world 3x4 rotation/axes followed by the eye position.
// ---------------------------------------------------------------------------------------------
struct cViewer {
    Matrix34 mCameraToWorldTransform;              // +0x00
    Vector3  mEye;                                 // +0x30
};

// ---------------------------------------------------------------------------------------------
// camera-controller base: listener + content-validation secondary vtables, an AddRef'd target,
// and a stopwatch.  Only the layout/initialization order of the constructors matters here.
// ---------------------------------------------------------------------------------------------
namespace EA {
class Stopwatch {
public:
    enum Units { kUnitsCycles = 0, kUnitsSeconds = 5 };
    Stopwatch() {}
    Stopwatch(int units, bool bStartImmediately);       // 0x0093a560
    uint64_t mnStartTime;                               // +0x00
    uint64_t mnTotalElapsedTime;                        // +0x08
    int      mnUnits;                                   // +0x10
    float    mfStopwatchCyclesToUnitsCoefficient;       // +0x14
};
}

struct IRefCounted {
    virtual void AddRef();
    virtual void Release();
};

// Three polymorphic base subobjects: the controller's primary interface, the listener interface
// (secondary vtable at +0x04) and the content-validation summarizer (secondary at +0x08).
struct cCameraControllerPrimary {
    virtual void p0();
};

struct cListenerBase {
    virtual void l0();
    virtual void l1();
    virtual void l2();
    virtual void l3();
};

struct cContentValidationSummarizer {
    virtual void c0();
    virtual void c1();
    virtual void c2();
    virtual void c3();
    void* mpOwner;                                      // +0x04 within this subobject
    cContentValidationSummarizer() : mpOwner(0) {}
};

// Member that takes its own reference on the target (the retail constructor's AddRef call).
struct CCameraTargetRef {
    IRefCounted* mpTarget;
    CCameraTargetRef(IRefCounted* p) : mpTarget(p) {
        if (p != 0)
            p->AddRef();
    }
};

// First init-list element: its initialization slot precedes the six zeroed pointer fields, so the
// compiler keeps it out of the hoisted group and emits it right before the Stopwatch argument setup.
struct CField14Seed {
    void* mValue;
    CField14Seed() : mValue(0) {
    }
};

struct cCameraControllerBase : cCameraControllerPrimary, cListenerBase, cContentValidationSummarizer {
    CCameraTargetRef mTarget;                           // +0x10
    CField14Seed mField14;                              // +0x14
    void*        m18;                                   // +0x18
    void*        m1c;                                   // +0x1c
    void*        m20;                                   // +0x20
    void*        m24;                                   // +0x24
    void*        m28;                                   // +0x28
    uint32_t     m2c;                                   // +0x2c
    EA::Stopwatch mStopwatch;                           // +0x30
    void*        m48;                                   // +0x48
    void*        m4c;                                   // +0x4c
    void*        m50;                                   // +0x50
    uint32_t     m54;                                   // +0x54
    uint32_t     m58;                                   // +0x58
    void*        m5c;                                   // +0x5c
    float        m60;                                   // +0x60
    float        m64;                                   // +0x64

    cCameraControllerBase(IRefCounted* target);

    virtual void l0();                                  // override cListenerBase
    virtual void c0();                                  // override cContentValidationSummarizer
};

// @ 0x0101a070
cCameraControllerBase::cCameraControllerBase(IRefCounted* target)
    : mTarget(target),
      mField14(), m18(0), m1c(0), m20(0), m24(0), m28(0),
      mStopwatch(EA::Stopwatch::kUnitsCycles, false),
      m48(0), m4c(0), m50(0), m5c(0), m60(0.0f), m64(0.0f) {
}

// ---------------------------------------------------------------------------------------------
// SP::cSPSpacePlanetCameraController (tail of the layout used by this slice)
// ---------------------------------------------------------------------------------------------
extern const float kFloatOne;           // 0x01485720 (_HK_REAL_ONE)
extern const float kFacingDefaultX;     // 0x016dd444
extern const float kFacingDefaultY;     // 0x016dd448
extern const float kFacingDefaultZ;     // 0x016dd44c
extern const float kCamDistance;        // 0x01465544 (1000.0f)
extern const float kCamFOV;             // 0x013f1cac (50.0f)
extern const float kCamMaxZoom;         // 0x01488874 (0.1f)
extern const Vector3 kUFOForward;       // 0x015b6de8
extern const Vector3 kWorldUp;          // 0x015b6df4
extern const Quaternion kIdentityOrient;// 0x015b6e00

struct Matrix44Raw { float m[16]; };    // +0xf8 .. +0x137 (not initialized by the constructor)

struct cSPSpacePlanetCameraController : cCameraControllerBase {
    bool     mSnapTuning;          // +0x68
    uint8_t  pad069[3];
    float    mDistance;            // +0x6c
    float    mFOV;                 // +0x70
    float    mSurfaceDistance;     // +0x74
    float    mZoom;                // +0x78
    float    mMaxZoom;             // +0x7c
    float    mLookAtHeight;        // +0x80
    float    mPitch;               // +0x84
    float    mPullOut;             // +0x88
    float    mPullOutRight;        // +0x8c
    float    mPullOutUp;           // +0x90
    Vector3  mEyeDirection;        // +0x94
    Vector3  mAnchorDir;           // +0xa0
    float    mAC;                  // +0xac
    float    mB0;                  // +0xb0
    Vector3  mEye;                 // +0xb4
    Vector3  mLookAt;              // +0xc0
    bool     mZooming;             // +0xcc
    uint8_t  pad0cd[3];
    float    mTuningBlend;         // +0xd0
    Vector3  mPrevEye;             // +0xd4
    Quaternion mPrevOrientation;   // +0xe0
    float    mBlendIn;             // +0xf0
    float    mBlendInTime;         // +0xf4
    Matrix44Raw mCameraToWorld;    // +0xf8
    int      mMode;                // +0x138
    bool     mFlag13c;             // +0x13c
    bool     mRotateLeft;          // +0x13d
    bool     mRotateRight;         // +0x13e
    bool     mApproachStart;       // +0x13f
    bool     mApproaching;         // +0x140
    uint8_t  pad141[3];
    Vector3  mApproachFrom;        // +0x144
    Vector3  mApproachTo;          // +0x150
    Vector3  mApproachBase;        // +0x15c
    Vector3  mApproachUp;          // +0x168
    Quaternion mApproachOrientation;// +0x174
    float    mApproachTwist;       // +0x184
    Vector3  mApproachAnchor;      // +0x188
    bool     mApproachDone;        // +0x194
    uint8_t  pad195[3];
    int      m198;                 // +0x198

    cSPSpacePlanetCameraController(IRefCounted* target);

    void SetSourceInterpolation(cViewer* viewer, float weight);
    void UpdateEffects();
};

// @ 0x01019f50
void cSPSpacePlanetCameraController::SetSourceInterpolation(cViewer* viewer, float weight) {
    mPrevEye = viewer->mEye;
    Matrix33 m(viewer->mCameraToWorldTransform);
    Quaternion tmp;
    Quaternion q = QuaternionFromMatrix33(tmp, m, 0.0f);
    mPrevOrientation = q;
    mBlendInTime = weight;
    mBlendIn = 0.0f;
}

// @ 0x0101a9d0
cSPSpacePlanetCameraController::cSPSpacePlanetCameraController(IRefCounted* target)
    : cCameraControllerBase(target) {
    float dist = kCamDistance;
    mFOV = kCamFOV;
    mDistance = dist;
    mSurfaceDistance = dist;
    mPullOut = dist;
    mZoom = 0.0f;
    mLookAtHeight = 0.0f;
    mPullOutRight = 0.0f;
    mPullOutUp = 0.0f;
    float maxZoom = kCamMaxZoom;
    mMaxZoom = maxZoom;
    mPitch = maxZoom;
    mSnapTuning = false;
    mEyeDirection.x = kUFOForward.x;
    mEyeDirection.y = kUFOForward.y;
    mEyeDirection.z = kUFOForward.z;
    mAnchorDir.x = kFacingDefaultX;
    mAnchorDir.y = kFacingDefaultY;
    mAnchorDir.z = kFacingDefaultZ;
    mAC = 0.0f;
    mB0 = 0.0f;
    mEye.x = kFacingDefaultX;
    mEye.y = kFacingDefaultY;
    mEye.z = kFacingDefaultZ;
    mLookAt.x = kFacingDefaultX;
    mLookAt.y = kFacingDefaultY;
    mLookAt.z = kFacingDefaultZ;
    mZooming = false;
    mTuningBlend = 0.0f;
    mPrevEye.x = kFacingDefaultX;
    mPrevEye.y = kFacingDefaultY;
    mPrevEye.z = kFacingDefaultZ;
    mPrevOrientation.x = kIdentityOrient.x;
    mPrevOrientation.y = kIdentityOrient.y;
    mPrevOrientation.z = kIdentityOrient.z;
    mPrevOrientation.w = kIdentityOrient.w;
    mBlendIn = 0.0f;
    mBlendInTime = 0.0f;
    mMode = 0;
    mRotateLeft = false;
    mRotateRight = false;
    mApproachStart = false;
    mApproaching = false;
    mFlag13c = true;
    mApproachFrom.x = kFacingDefaultX;
    mApproachFrom.y = kFacingDefaultY;
    mApproachFrom.z = kFacingDefaultZ;
    mApproachTo.x = kFacingDefaultX;
    mApproachTo.y = kFacingDefaultY;
    mApproachTo.z = kFacingDefaultZ;
    mApproachBase.x = kWorldUp.x;
    mApproachBase.y = kWorldUp.y;
    mApproachBase.z = kWorldUp.z;
    mApproachUp.x = kWorldUp.x;
    mApproachUp.y = kWorldUp.y;
    mApproachUp.z = kWorldUp.z;
    mApproachOrientation.x = kIdentityOrient.x;
    mApproachOrientation.y = kIdentityOrient.y;
    mApproachOrientation.z = kIdentityOrient.z;
    mApproachOrientation.w = kIdentityOrient.w;
    mApproachTwist = 0.0f;
    mApproachAnchor.x = kFacingDefaultX;
    mApproachAnchor.y = kFacingDefaultY;
    mApproachAnchor.z = kFacingDefaultZ;
    m198 = 0;
    mApproachDone = true;
}

// ---------------------------------------------------------------------------------------------
// SP::cSPSpaceCameraController — secondary derivation of the same camera-controller base.
// ---------------------------------------------------------------------------------------------
struct cSPSpaceCameraController : cCameraControllerBase {
    Vector3  m68;                                  // +0x68
    Vector3  m74;                                  // +0x74 (not initialized by the constructor)
    float    m80;                                  // +0x80
    volatile uint32_t m84;                         // +0x84
    volatile uint32_t m88;                         // +0x88
    Vector3  m8c;                                  // +0x8c
    Vector3  m98;                                  // +0x98
    Vector3  ma4;                                  // +0xa4
    float    mb0;                                  // +0xb0
    float    mb4;                                  // +0xb4
    float    mb8;                                  // +0xb8
    float    mbc;                                  // +0xbc
    float    mc0;                                  // +0xc0
    float    mc4;                                  // +0xc4
    float    mc8;                                  // +0xc8
    float    mcc;                                  // +0xcc
    float    md0;                                  // +0xd0
    uint8_t  md4[7];                               // +0xd4

    cSPSpaceCameraController(IRefCounted* target);
};

// @ 0x0101a130
cSPSpaceCameraController::cSPSpaceCameraController(IRefCounted* target)
    : cCameraControllerBase(target) {
    m68.x = kFacingDefaultX;
    m68.y = kFacingDefaultY;
    m68.z = kFacingDefaultZ;
    m80 = 0.0f;
    m84 = 0;
    m88 = 0;
    m8c.x = kFacingDefaultX;
    m8c.y = kFacingDefaultY;
    m8c.z = kFacingDefaultZ;
    m98.x = kFacingDefaultX;
    m98.y = kFacingDefaultY;
    m98.z = kFacingDefaultZ;
    ma4.x = kFacingDefaultX;
    ma4.y = kFacingDefaultY;
    ma4.z = kFacingDefaultZ;
    mb0 = 0.0f;
    mb4 = 0.0f;
    mb8 = 0.0f;
    mbc = 0.0f;
    mc0 = 0.0f;
    mc4 = 0.0f;
    mc8 = 0.0f;
    mcc = 0.0f;
    md0 = kFloatOne;
    md4[0] = 0; md4[1] = 0; md4[2] = 0; md4[3] = 0; md4[4] = 0; md4[5] = 0; md4[6] = 0;
}

// ---------------------------------------------------------------------------------------------
// SP::cSPSpacePlanetCameraController::UpdateEffects — tells the UI how far the camera is from the
// planet surface so the "too far away" effects can fade out.
// ---------------------------------------------------------------------------------------------
extern char vtbl_BehaviorMessage[];     // 0x013eb90c (UI::BehaviorMessage base vtable)
extern char vtbl_SlotMessage[];         // 0x013eb844 (SlotMessage derived vtable)
extern const float kEffectMaxDistance;  // 0x013fec70 (1500.0f)

// 0x3c-byte listener-slot message built on the stack (vtable 0x013eb844, destructor 0x00421cf0).
struct SlotMessage {
    void*         mVtable;        // +0x00
    volatile long mRefCount;      // +0x04
    float         mPayloadA;      // +0x08 distance to the surface
    uint32_t      mPayloadGap;    // +0x0c
    float         mPayloadB;      // +0x10 maximum distance
    uint32_t      mBody[7];       // +0x14 .. +0x2f listener slots
    uint32_t      mArg;           // +0x30
    uint32_t      mPad34;         // +0x34
    uint32_t      mListenerMask;  // +0x38

    void Destruct();              // 0x00421cf0
};

struct MessageServerT {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4();
    virtual void Post(uint32_t id, SlotMessage* msg, uint32_t extra);   // +0x14
};
MessageServerT* MessageServer();          // 0x0067dcc0

// PlanetModel()->mUFO->v3() yields the current camera target whose +0x34 float is the altitude.
struct CameraAltitude {
    uint8_t pad[0x34];
    float   mAltitude;                    // +0x34
};
struct PlanetModelUFO {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual CameraAltitude* v3();         // +0x0c
};
struct PlanetModelRoot {
    uint8_t        pad[0x24];
    PlanetModelUFO* mUFO;                 // +0x24
};
PlanetModelRoot* PlanetModel();          // 0x00b3d350

// The player's inventory carries the ship position in its base subobject at +0x34.
struct InventoryBase {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual Vector3* GetPosition();       // +0x2c
};
struct PlayerInventory {
    uint8_t       pad00[0x34];
    InventoryBase mBase;                  // +0x34
    uint8_t       pad38[0x74c - 0x38];
    uint8_t       mShipLocked;            // +0x74c
    uint8_t       pad74d[3];
    Vector3       mShipPosition;          // +0x750
};
struct cSPSimulatorSpaceGame {
    PlayerInventory* GetPlayerInventory();// 0x00a1ad60
};
cSPSimulatorSpaceGame* GetUFOSimulator(); // 0x00ffbe50

struct EffectGameTimeManager {
    uint8_t pad[0x48];
    uint8_t mFlags;                       // +0x48 bit 0 = paused
};
EffectGameTimeManager* EffectGameTimeManagerFn();   // 0x00b3d380

// @ 0x0101ad50
void cSPSpacePlanetCameraController::UpdateEffects() {
    MessageServerT* server = MessageServer();
    if (server == 0)
        return;

    float altitude = 0.0f;
    PlanetModelUFO* ufo = PlanetModel()->mUFO;
    if (ufo != 0)
        altitude = ufo->v3()->mAltitude;

    GetUFOSimulator()->GetPlayerInventory();
    PlayerInventory* inv = GetUFOSimulator()->GetPlayerInventory();

    Vector3* position;
    if (inv->mShipLocked != 0 && (EffectGameTimeManagerFn()->mFlags & 1) == 0)
        position = &inv->mShipPosition;
    else
        position = inv->mBase.GetPosition();

    double sum = (double)position->x * (double)position->x
               + (double)position->y * (double)position->y
               + (double)position->z * (double)position->z;
    float maxDistance = kEffectMaxDistance;
    float distance = (float)sqrt(sum) - altitude;
    if (distance > kEffectMaxDistance)
        distance = kEffectMaxDistance;

    SlotMessage msg;
    msg.mArg = 0;
    msg.mVtable = vtbl_BehaviorMessage;
    _InterlockedExchange(&msg.mRefCount, 0);
    msg.mVtable = vtbl_SlotMessage;
    msg.mListenerMask = 0;
    msg.mPayloadA = distance;
    msg.mPayloadB = maxDistance;
    server->Post(0x60e4e46e, &msg, 0);
    msg.Destruct();
}
