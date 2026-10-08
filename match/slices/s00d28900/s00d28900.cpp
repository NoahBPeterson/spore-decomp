// Slice s00d28900: SP::cCreatureCamera::cCreatureCamera(IRefObject*) (0x00d28e60, 1772 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same module as the other cSP camera code).
//
// A long constructor: base vptrs, input/tuning limits (angles in radians, distances, interpolation
// times), the camera transform, the local input state, the owner reference (AddRef'd), the message
// tree anchor, and the per-frame camera data block (all vectors zeroed, quaternions identity).
// Retail offsets: the 2008 PDB layout minus 8 from +0x200 on and minus 0x10 from +0x2cc on.
#include "types.h"
#include <float.h>
#include <new>

struct Vector2 {
    float x, y;
    Vector2() {}
    Vector2(const Vector2& o) : x(o.x), y(o.y) {}
};
struct Vector3 {                         // user copy ctor: float copies go through movss
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct SPVector3 { float x, y, z; };     // POD: copies are dword moves
struct SPQuaternion { float x, y, z, w; };

struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& other);       // 0x0041cb40
};

// cSPTransform (0x38 bytes); its constructor is inlined into the camera constructor body
struct Transform {
    uint16_t mFlags;
    uint16_t mChangeCount;
    Vector3 mOffset;
    float mScale;
    Matrix3 mRotation;
};
extern const Vector3 kZero3;             // 0x0169deb0
extern const Matrix3 kIdentity3;         // 0x0169df20

extern const Vector2 kInputConst;        // 0x0169dea8
extern const Vector2 kPitchLimits;       // 0x01582868
extern const SPVector3 kZeroVec;         // 0x0169deb0
extern const SPQuaternion kIdentityQuat; // 0x01582838


struct IRefObject {
    virtual int AddRef();
};

struct cLocalInputState {
    char data[0x48];
    cLocalInputState();                  // 0x00697960
};

// eastl::rbtree anchor (right, left, parent, color) + size, default-constructed inline
struct RbTreeAnchor {
    RbTreeAnchor* mpRight;
    RbTreeAnchor* mpLeft;
    RbTreeAnchor* mpParent;
    uint32_t mColor;
    uint32_t mnSize;
};

inline SPVector3 MakeVec(float x, float y, float z)
{
    SPVector3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

extern void* g_vtblGB1;                  // 0x013eb384
extern void* g_vtblRefCount;             // 0x013ec458
extern void* g_vtblCam0;                 // 0x0147a3a8
extern void* g_vtblCam1;                 // 0x0147a398
extern void* g_vtblCam2;                 // 0x0147a388

struct ICamBase { void* mVptr; };                     // vptr +0x00 (abstract interface, no ctor stores)
struct IGB1 {                                         // vptr +0x04
    void* mVptr;
    IGB1() { mVptr = &g_vtblGB1; }
};
struct RefCountV {                                    // vptr +0x08, count +0x0c
    void* mVptr;
    int mRefCount;
    RefCountV() { mVptr = &g_vtblRefCount; mRefCount = 0; }
};

class cCreatureCamera : public ICamBase, public IGB1, public RefCountV {
public:
    void SetVptrs()
    {
        ICamBase::mVptr = &g_vtblCam0;
        IGB1::mVptr = &g_vtblCam1;
        RefCountV::mVptr = &g_vtblCam2;
    }
    static bool Prepare(cCreatureCamera* self) { self->SetVptrs(); return true; }
    bool mbEnableInput;                  // +0x10
    bool mbSkipInit;                     // +0x11
    Vector2 mInputConst;                 // +0x14
    // per-frame camera data block (+0x1c .. +0x1ec)
    float mDt, mOscillationTime, mBreathOffset;                 // +0x1c
    SPVector3 mShakeOffset;                                     // +0x28
    float mRoll;                                                // +0x34
    SPVector3 mReferenceHeading;                                // +0x38
    float mWantInterpolationTimer;                              // +0x44
    SPVector3 mV48;                                             // +0x48
    SPVector3 mV54;                                             // +0x54
    SPQuaternion mQ60;                                          // +0x60
    SPVector3 mV70, mV7c, mV88, mV94, mVa0, mVac, mVb8, mVc4;   // +0x70 ..
    SPVector3 mBoundsMin;                                       // +0xd0
    SPVector3 mBoundsMax;                                       // +0xdc
    bool mbE8, mbE9;                                            // +0xe8
    float mFieldEC, mFieldF0, mFieldF4, mFieldF8, mFieldFC;     // +0xec
    float mField100;                                            // +0x100
    bool mb104, mb105;                                          // +0x104
    SPVector3 mV108, mV114, mV120;                              // +0x108
    float mF12C, mF130, mF134, mF138;                           // +0x12c
    SPVector3 mV13C, mV148;                                     // +0x13c
    SPQuaternion mQ154;                                         // +0x154
    bool mb164;                                                 // +0x164
    SPVector3 mV168;                                            // +0x168
    float mF174, mF178, mF17C, mF180, mF184, mF188, mF18C, mF190;  // +0x174
    float mF194, mF198;                                         // +0x194
    bool mb19C, mb19D;                                          // +0x19c
    float mF1A0, mF1A4, mF1A8;                                  // +0x1a0
    float mPad1AC[(0x1e4 - 0x1ac) / 4];
    float mF1E4;                                                // +0x1e4
    uint32_t mI1E8, mI1EC, mI1F0;                               // +0x1e8
    bool mb1F4;                                                 // +0x1f4
    float mMouseSensitivityX, mMouseSensitivityY;               // +0x1f8
    float mMouseSensitivityZ;                                   // +0x200
    float mMaxAnchorDistance;                                   // +0x204
    Vector2 mPitchLimits;                                       // +0x208
    float mMinCameraPhi;                                        // +0x210
    float mMaxCameraPhi;                                        // +0x214
    float mMinCameraDistance;                                   // +0x218
    float mMaxCameraDistance;                                   // +0x21c
    float mInitialDistance;                                     // +0x220
    float mInitialRotation;                                     // +0x224
    float mNearClip, mFarClip, mInterpolateAnchorTime;          // +0x228
    float mInterpolateOrientationTime;                          // +0x234
    float mInterpolateThetaTime;                                // +0x238
    bool mbAutoPitchActive;                                     // +0x23c
    float mInterpolatePitchTime;                                // +0x240
    float mInterpolateDistanceTime;                             // +0x244
    float mAutoPitch248;                                        // +0x248
    float mAutoPitch24C;                                        // +0x24c
    float mAutoPitch250;                                        // +0x250
    float mAutoPitch254;                                        // +0x254
    float mInterpolateAnchorMultiplier;                         // +0x258
    float mField25C;                                            // +0x25c
    Transform mCameraToWorld;                                   // +0x260
    bool mTransformNeedsUpdating;                               // +0x298
    bool mCameraReverse;                                        // +0x299
    uint32_t mMsgReg[5];                                        // +0x29c
    bool mbCanToggleFirstPersonView;                            // +0x2b0
    bool mbLockOutPlayerDeltas, mbAllowRealignment, mbRealignAvatar, mbB4;  // +0x2b1
    float mLftMouseDownDuration;                                // +0x2b8
    char mLocalInputState[0x48];                                // +0x2bc (cLocalInputState)
    bool mbActive;                                              // +0x304
    IRefObject* mConfig;                                        // +0x308
    char pad30c[0x314 - 0x30c];
    bool mb314, mb315;                                          // +0x314
    uint32_t pad318;
    RbTreeAnchor mTree;                                         // +0x31c

    cCreatureCamera(IRefObject* pConfig);
};

// @ 0x00d28e60
cCreatureCamera::cCreatureCamera(IRefObject* pConfig)
    : mbEnableInput(Prepare(this)), mbSkipInit(false), mInputConst(kInputConst),
      mBoundsMin(MakeVec(FLT_MAX, FLT_MAX, FLT_MAX)),
      mBoundsMax(MakeVec(-FLT_MAX, -FLT_MAX, -FLT_MAX))
{
    mMouseSensitivityX = 0.017453292f;
    mMouseSensitivityY = 0.0043633231f;
    mMouseSensitivityZ = 0.001f;
    mMaxAnchorDistance = 30.0f;
    mPitchLimits = kPitchLimits;
    mMinCameraPhi = 5.0f;
    mMaxCameraPhi = 25.0f;
    mMinCameraDistance = 10.0f;
    mMaxCameraDistance = 0.39269909f;
    mInitialDistance = 1.0f;
    mInitialRotation = 10000.0f;
    mNearClip = 0.5f;
    mFarClip = 0.5f;
    mInterpolateAnchorTime = 0.5f;
    mI1E8 = 0;
    mI1EC = 0;
    mI1F0 = 0;
    mb1F4 = false;
    mInterpolateOrientationTime = 1.0f;
    mInterpolateThetaTime = 1.0f;
    mbAutoPitchActive = false;
    mInterpolatePitchTime = -5.0f;
    mInterpolateDistanceTime = 10.0f;
    mAutoPitch248 = 0.0f;
    mAutoPitch24C = 5.0f;
    mAutoPitch250 = 0.01f;
    mAutoPitch254 = 0.1f;
    mInterpolateAnchorMultiplier = 30.0f;
    mField25C = 30.0f;

    mCameraToWorld.mChangeCount = 0;
    mCameraToWorld.mFlags = 0;
    ::new ((void*)&mCameraToWorld.mOffset) Vector3(kZero3);
    mCameraToWorld.mScale = 1.0f;
    ::new ((void*)&mCameraToWorld.mRotation) Matrix3(kIdentity3);
    mTransformNeedsUpdating = true;
    mCameraReverse = false;
    mMsgReg[0] = 0;
    mMsgReg[1] = 0;
    mMsgReg[2] = 0;
    mMsgReg[3] = 0;
    mMsgReg[4] = 0;
    mbCanToggleFirstPersonView = true;
    mbLockOutPlayerDeltas = false;
    mbAllowRealignment = false;
    mbRealignAvatar = false;
    mbB4 = false;
    mLftMouseDownDuration = 0.0f;

    ::new ((void*)mLocalInputState) cLocalInputState();
    mbActive = false;
    mConfig = pConfig;
    if (pConfig)
        pConfig->AddRef();
    mb314 = false;
    mb315 = false;

    mTree.mpLeft = 0;
    mTree.mpParent = 0;
    mTree.mColor = 0;
    mTree.mpParent = 0;
    *(uint8_t*)&mTree.mColor = 0;
    mTree.mnSize = 0;
    mTree.mpRight = &mTree;
    mTree.mpLeft = &mTree;

    mDt = 0.0f;
    mOscillationTime = 0.0f;
    mBreathOffset = 0.0f;
    mShakeOffset = kZeroVec;
    mRoll = 0.0f;
    mReferenceHeading = kZeroVec;
    mWantInterpolationTimer = 0.0f;
    mV48 = kZeroVec;
    mV54 = kZeroVec;
    mQ60 = kIdentityQuat;
    mV70 = kZeroVec;
    mV7c = kZeroVec;
    mV88 = kZeroVec;
    mV94 = kZeroVec;
    mVa0 = kZeroVec;
    mVac = kZeroVec;
    mVb8 = kZeroVec;
    mVc4 = kZeroVec;
    mbE8 = false;
    mbE9 = false;
    mFieldEC = 0.0f;
    mFieldF0 = 0.0f;
    mFieldF4 = 0.0f;
    mFieldF8 = 0.0f;
    mFieldFC = 0.0f;
    mField100 = mMinCameraPhi;
    mb104 = false;
    mb105 = false;
    mV108 = kZeroVec;
    mV114 = kZeroVec;
    mV120 = kZeroVec;
    mF12C = 0.0f;
    mF130 = 0.0f;
    mF134 = 0.0f;
    mF138 = 0.0f;
    mV13C = kZeroVec;
    mV148 = kZeroVec;
    mQ154 = kIdentityQuat;
    mb164 = false;
    mV168 = kZeroVec;
    mF174 = 0.0f;
    mF178 = 0.0f;
    mF17C = 0.0f;
    mF180 = 0.0f;
    mb19C = false;
    mb19D = false;
    mF184 = 0.0f;
    mF188 = 0.0f;
    mF18C = 0.0f;
    mF190 = 0.0f;
    mF194 = mMinCameraPhi;
    mF198 = 0.0f;
    mF1A0 = 0.0f;
    mF1A4 = 0.0f;
    mF1A8 = 0.0f;
    mF1E4 = 0.0f;
}
