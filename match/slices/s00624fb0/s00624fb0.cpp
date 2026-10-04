// slice s00624fb0: cCreatureCameraBase mouse input, message handling, camera data init/update
#include <new>
#include <string.h>
#include <math.h>
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2

__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

struct cSPVector3 {
    float x, y, z;
};
struct Vector3Copy {   // Math::Vector3 with a user copy ctor (per-field copy, movss)
    float x, y, z;
    Vector3Copy() {}
    Vector3Copy(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3Copy(const Vector3Copy& v) : x(v.x), y(v.y), z(v.z) {}
};
static inline Vector3Copy NegateVecC(const Vector3Copy& v)
{
    Vector3Copy r(v);
    r.x = -r.x;
    r.y = -r.y;
    r.z = -r.z;
    return r;
}
struct cSPQuaternion {
    float x, y, z, w;
};
struct cSPBoundingBox {
    cSPVector3 mMin;
    cSPVector3 mMax;
};

static inline cSPVector3 NegateVec(const cSPVector3& v)
{
    cSPVector3 r;
    r.x = -v.x;
    r.y = -v.y;
    r.z = -v.z;
    return r;
}
extern const cSPVector3 kZeroVector;           // 0x15f65fc
extern const cSPQuaternion kIdentityQuat;      // 0x1521a70
extern const cSPVector3 kAvatarCameraOffset;   // 0x15f6774
extern const cSPVector3 kAvatarUp;             // 0x15f66f8
extern const float kLookHeightScale;           // 0x13fdf1c  (= -0.30103 = log10(0.5))
extern const float kHalfLifeTime;              // 0x1521884
extern const float kVelocityRate;              // 0x1521880
extern const float kVelocityAccel;             // 0x152187c
extern const float kMaxAngleDelta;             // 0x13fdefc
extern const float kHalfTurn;                  // 0x15f6770
extern const float kMouseDeltaLimitMax;        // 0x13eecd8
extern const float kMouseDeltaLimitMin;        // 0x13fdf18

namespace SP {

struct tAvatarData {
    cSPVector3 mPosition;       // +0x00
    cSPQuaternion mOrientaion;  // +0x0c
    cSPBoundingBox mLocalExtents;   // +0x1c
    cSPVector3 mVelocity;       // +0x34
    Vector3Copy mDestination;   // +0x40
    cSPVector3 mWASDDirection;  // +0x4c
    bool mbWASD;
    bool mbWASDTurning;
};

struct cAnimatingCreature {
    int pad0;
    Vector3Copy mPos;   // +4
};

class cCreatureCameraDepends {
public:
    tAvatarData mAvatar;                       // +0x00
    cSPVector3 mTargetCameraPositionOffset;    // +0x5c
    cSPVector3 mActualCameraPositionOffset;    // +0x68
    cAnimatingCreature* mAnimCreature;         // +0x74
    void InitAvatarData();                     // 0x6256a0
    void FUN_006280d0(Vector3Copy v, int flag); // slice s00627d50
    void UpdateOffsets(float dt);              // 0x625750
};

struct IMessageServer {
    PV4 PV
    virtual void PostMessage(unsigned a, unsigned b, int c);   // +0x14
};
IMessageServer* __cdecl MessageServer();

class cICameraController { public: virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); };
class IRef2 { public: virtual void r0(); virtual void r1(); };

struct tCameraData {
    float dt;                                   // +0x00
    cSPVector3 platformPosition;                // +0x04
    cSPVector3 platformVelocity;                // +0x10
    cSPQuaternion platformOrientation;          // +0x1c
    cSPVector3 avatarPosition;                  // +0x2c
    float currentPlayerTheta;                   // +0x38
    float currentPlayerPitch;                   // +0x3c
    float currentPlayerDistance;                // +0x40
    cSPVector3 desiredPosition;                 // +0x44
    cSPVector3 desiredLookAt;                   // +0x50
    float mDesiredLookAtXOffset;                // +0x5c
    float mDesiredLookAtYOffset;                // +0x60
    cSPVector3 newPlatformPosition;             // +0x64
    cSPVector3 newPlatformVelocity;             // +0x70
    cSPQuaternion newPlatformOrientation;       // +0x7c
    float desiredPlayerTheta;                   // +0x8c
    float desiredPlayerPitch;                   // +0x90
    float desiredPlayerDistance;                // +0x94
    float nonPenetratingPhi;                    // +0x98
    bool bPenetrating;                          // +0x9c
    cSPVector3 currentPreTranslate;             // +0xa0
    cSPVector3 desiredPreTranslate;             // +0xac
    bool bTransitioning;                        // +0xb8
};

class cCreatureCameraBase : public cICameraController, public IRef2 {
public:
    enum eCameraInputState { kCameraInputStateNormal_ = 0, kCameraInputStateSwingLeft_ = 1, kCameraInputStateSwingRight_ = 2, kCameraInputStateReset_ = 3, kCameraInputStateZoomIn_ = 4, kCameraInputStateZoomOut_ = 5, kCameraInputStateSwingUp_ = 6, kCameraInputStateSwingDown_ = 7 };
    int padA[2];
    cCreatureCameraDepends mDepends;            // +0x10
    eCameraInputState mCameraInputState;        // +0x88
    int mCameraState;                           // +0x8c
    int mCameraMode;                            // +0x90
    int mDesiredCameraMode;                     // +0x94
    tCameraData mCameraData;                    // +0x98
    float mMouseSensitivityX;                   // +0x154
    float mMouseSensitivityY;                   // +0x158
    float mMouseSensitivityZ;                   // +0x15c
    float mMinCameraPhi;                        // +0x160
    float mMaxCameraPhi;                        // +0x164
    float mMinCameraDistance;                   // +0x168
    float mMaxCameraDistance;                   // +0x16c
    char padC[0x1cc - 0x170];
    bool mTransformNeedsUpdating;               // +0x1cc
    char padD[0x1e4 - 0x1d0];
    float mMouseX;                              // +0x1e4
    float mMouseY;                              // +0x1e8
    bool mMouseLeftButton;                      // +0x1ec
    bool mMouseMiddleButton;                    // +0x1ed
    bool mMouseRightButton;                     // +0x1ee
    bool mbActive;                              // +0x1ef
    bool mbEnabled;                             // +0x1f0
    char padE[3];
    float (__cdecl* mpHeightFn)(void* pUser, cSPVector3* pPos);   // +0x1f4
    void* mpHeightUser;                         // +0x1f8
    float mCachedHeight;                        // +0x1fc

    bool OnMouseUp(int button, float x, float y, int state);
    bool OnMouseMove(float x, float y, int state);
    bool OnMouseWheel(int delta, float x, float y, int state);
    bool OnMouseDown(int button, float x, float y, int state);
    void AddDistanceScale(float f);
    void AddTheta(float f);
    void NormalizeTheta();
    void SetHeightCallback(void* fn, void* pUser);
    bool HandleMessage(unsigned messageID, void* pMsg);
    float QueryHeight(const cSPVector3* pPos);
    void SetCurrentCamera(float theta, float phi, float dist);
    void InitCameraData();
    void UpdateAvatarLookAt();
    void UpdateVelocity();
};

// @ 0x00624fb0
bool cCreatureCameraBase::OnMouseUp(int button, float x, float y, int state)
{
    if (!mbEnabled)
        return true;
    switch (button) {
    case 1000:
        mMouseLeftButton = false;
        break;
    case 0x3e9:
        mMouseMiddleButton = false;
        break;
    case 0x3ea:
        mMouseRightButton = false;
        break;
    }
    mMouseX = x;
    mMouseY = y;
    return false;
}

// @ 0x00625010
bool cCreatureCameraBase::OnMouseMove(float x, float y, int state)
{
    float oldX = mMouseX;
    float oldY = mMouseY;
    mMouseX = x;
    mMouseY = y;
    if ((mMouseRightButton || mMouseMiddleButton) && !mMouseLeftButton) {
        float dx = x - oldX;
        float dy = y - oldY;
        float yaw = -(mMouseSensitivityX * Clamp(dx, -20.0f, 20.0f));
        float pitch = mMouseSensitivityY * Clamp(dy, -20.0f, 20.0f);
        if (yaw < 0.0f)
            mCameraState = 1;
        else if (yaw > 0.0f)
            mCameraState = 2;
        else if (pitch > 0.0f)
            mCameraState = 6;
        else if (pitch < 0.0f)
            mCameraState = 7;
        else
            mCameraState = 0;
        mCameraData.desiredPlayerTheta += yaw;
        if (dy < 0.0f && mCameraData.bPenetrating && mCameraData.nonPenetratingPhi > 0.0f)
            pitch = 0.0f;
        mCameraData.desiredPlayerPitch = Clamp(mCameraData.desiredPlayerPitch + pitch, mMinCameraPhi, mMaxCameraPhi);
        MessageServer()->PostMessage(0x52f180, 0x1c, 0);
    }
    return false;
}

// @ 0x006251f0
bool cCreatureCameraBase::OnMouseWheel(int delta, float x, float y, int state)
{
    if (!mbEnabled)
        return true;
    if (state == 0) {
        if (delta > 0)
            mCameraState = 4;
        else
            mCameraState = ((delta >= 0) - 1) & 5;
        mCameraData.desiredPlayerDistance = (1.0f - (float)delta * mMouseSensitivityZ) * mCameraData.desiredPlayerDistance;
        MessageServer()->PostMessage(0x52f180, 0x1d, 0);
    }
    return false;
}

// @ 0x00625270
void cCreatureCameraBase::AddDistanceScale(float f)
{
    mCameraData.desiredPlayerDistance = (f + 1.0f) * mCameraData.desiredPlayerDistance;
}

// @ 0x006252a0
void cCreatureCameraBase::AddTheta(float f)
{
    mCameraData.desiredPlayerTheta = f + mCameraData.desiredPlayerTheta;
}

// @ 0x006252c0
void cCreatureCameraBase::NormalizeTheta()
{
    float t = mCameraData.desiredPlayerTheta;
    float c = mCameraData.currentPlayerTheta;
    if (fabsf(t - c) < 1.52587890625e-05f) {
        if (kHalfTurn < c && kHalfTurn < t) {
            c = c - kHalfTurn;
            mCameraData.desiredPlayerTheta = t - kHalfTurn;
            mCameraData.currentPlayerTheta = c;
            return;
        }
        if (c < -kHalfTurn && t < -kHalfTurn) {
            c = c + kHalfTurn;
            mCameraData.desiredPlayerTheta = t + kHalfTurn;
            mCameraData.currentPlayerTheta = c;
        }
    }
}

// @ 0x00625350
void cCreatureCameraBase::SetHeightCallback(void* fn, void* pUser)
{
    *(void**)&mpHeightFn = fn;
    mpHeightUser = pUser;
    mCachedHeight = 0.0f;
}

// @ 0x00625380
bool cCreatureCameraBase::HandleMessage(unsigned messageID, void* pMsg)
{
    unsigned v = 0;
    switch (messageID) {
    case 0x3d72520:
    case 0x3d7252c:
    case 0x3d7253e:
    case 0x3d72548:
        v = *(unsigned*)((char*)pMsg + 8);
    }
    cAnimatingCreature* pAnim;
    switch (messageID) {
    case 0x3d72520:
        mDepends.mAnimCreature = (cAnimatingCreature*)(unsigned)(0 < v);
        mCameraInputState = (eCameraInputState)(unsigned)mDepends.mAnimCreature;
        return false;
    case 0x3d7252c:
        pAnim = (cAnimatingCreature*)(0 < v ? 2 : 0);
        mDepends.mAnimCreature = pAnim;
        mCameraInputState = (eCameraInputState)(unsigned)pAnim;
        return false;
    case 0x3d7253e:
        pAnim = (cAnimatingCreature*)(0 < v ? 4 : 0);
        mDepends.mAnimCreature = pAnim;
        mCameraInputState = (eCameraInputState)(unsigned)pAnim;
        return false;
    case 0x3d72548:
        pAnim = (cAnimatingCreature*)(0 < v ? 5 : 0);
        mDepends.mAnimCreature = pAnim;
        mCameraInputState = (eCameraInputState)(unsigned)pAnim;
        return false;
    case 0x3d72502:
        mDepends.mAnimCreature = (cAnimatingCreature*)3;
        break;
    }
    mCameraInputState = (eCameraInputState)(unsigned)mDepends.mAnimCreature;
    return false;
}

// @ 0x006254f0
bool cCreatureCameraBase::OnMouseDown(int button, float x, float y, int state)
{
    if (!mbEnabled)
        return true;
    switch (button) {
    case 1000:
        mMouseLeftButton = true;
        break;
    case 0x3e9:
        mMouseMiddleButton = true;
        break;
    case 0x3ea:
        mMouseRightButton = true;
        break;
    }
    mMouseX = x;
    mMouseY = y;
    if (mMouseLeftButton)
        mDesiredCameraMode = 0;
    return true;
}

// @ 0x00625560
template <class T> const T& max_(const T& a, const T& b) { return (a < b) ? b : a; }
void cCreatureCameraBase::SetCurrentCamera(float theta, float phi, float dist)
{
    mCameraData.currentPlayerTheta = theta;
    mCameraData.currentPlayerPitch = Clamp(phi, mMinCameraPhi, mMaxCameraPhi);
    float d = max_(0.1f, dist);
    mTransformNeedsUpdating = true;
    mCameraData.currentPlayerDistance = d;
}

// @ 0x00625600
float cCreatureCameraBase::QueryHeight(const cSPVector3* pPos)
{
    float r = 0.0f;
    if (mpHeightFn && mpHeightUser) {
        Vector3Copy tmp = *(const Vector3Copy*)pPos;
        float h = mpHeightFn(mpHeightUser, (cSPVector3*)&tmp);
        r = h;
        if (h >= 0.4f)
            r = mCachedHeight;
    }
    mCachedHeight = r;
    return r;
}

// @ 0x006256a0
void cCreatureCameraDepends::InitAvatarData()
{
    mAvatar.mPosition.x = 0.0f;
    mAvatar.mPosition.y = 0.0f;
    mAvatar.mPosition.z = 0.0f;
    Vector3Copy facing = NegateVecC(*(const Vector3Copy*)&kAvatarCameraOffset);
    cSPQuaternion q;
    extern cSPQuaternion* __cdecl QuaternionFromFacingAndUp(cSPQuaternion* out, const Vector3Copy* facing, const cSPVector3* up);
    mAvatar.mOrientaion = *QuaternionFromFacingAndUp(&q, &facing, &kAvatarUp);
    mAvatar.mDestination = Vector3Copy(0.0f, 0.0f, 0.0f);
}

// @ 0x00625750
void cCreatureCameraDepends::UpdateOffsets(float dt)
{
    if (mAnimCreature) {
        FUN_006280d0(mAnimCreature->mPos, 0);
    }
    float t = Clamp(dt, 0.01f, 0.15f);
    mActualCameraPositionOffset.x = mActualCameraPositionOffset.x + (mTargetCameraPositionOffset.x - mActualCameraPositionOffset.x) * t * 10.0f;
    mActualCameraPositionOffset.y = (mTargetCameraPositionOffset.y - mActualCameraPositionOffset.y) * t * 10.0f + mActualCameraPositionOffset.y;
    mActualCameraPositionOffset.z = (mTargetCameraPositionOffset.z - mActualCameraPositionOffset.z) * t * 10.0f + mActualCameraPositionOffset.z;
}

// @ 0x00625830
void cCreatureCameraBase::InitCameraData()
{
    mCameraData.newPlatformPosition = kZeroVector;
    mCameraData.newPlatformVelocity = kZeroVector;
    mCameraData.newPlatformOrientation = kIdentityQuat;
    mCameraData.currentPreTranslate = kZeroVector;
    mCameraData.desiredPreTranslate = kZeroVector;
    cCreatureCameraDepends* pDep = &mDepends;
    pDep->InitAvatarData();
    if (!pDep->mAnimCreature) {
        pDep->mActualCameraPositionOffset = kZeroVector;
        pDep->mTargetCameraPositionOffset = kZeroVector;
    }
    mCameraData.platformPosition.x = pDep->mAvatar.mPosition.x - kAvatarCameraOffset.x;
    mCameraData.platformPosition.y = pDep->mAvatar.mPosition.y - kAvatarCameraOffset.y;
    mCameraData.platformPosition.z = pDep->mAvatar.mPosition.z - kAvatarCameraOffset.z;
    mCameraData.platformOrientation = pDep->mAvatar.mOrientaion;
    mCameraData.platformVelocity = kZeroVector;
    float h = pDep->mAvatar.mLocalExtents.mMax.z;
    mCameraData.avatarPosition.x = pDep->mAvatar.mPosition.x + h * kAvatarUp.x;
    mCameraData.avatarPosition.y = pDep->mAvatar.mPosition.y + h * kAvatarUp.y;
    mCameraData.avatarPosition.z = pDep->mAvatar.mPosition.z + h * kAvatarUp.z;
    mCameraData.desiredLookAt = mCameraData.avatarPosition;
    mCameraData.mDesiredLookAtYOffset = 0.0f;
    mCameraData.mDesiredLookAtXOffset = 0.0f;
    mCameraData.desiredPosition.x = mCameraData.avatarPosition.x - kAvatarCameraOffset.x;
    mCameraData.desiredPosition.y = mCameraData.avatarPosition.y - kAvatarCameraOffset.y;
    mCameraData.desiredPosition.z = mCameraData.avatarPosition.z - kAvatarCameraOffset.z;
}

// @ 0x00625a90
void cCreatureCameraBase::UpdateAvatarLookAt()
{
    float d = mDepends.mAvatar.mLocalExtents.mMax.z * 0.5f;
    float e = d * 0.25f + d;
    float ax = kAvatarUp.x * e + mDepends.mAvatar.mPosition.x;
    float ay = mDepends.mAvatar.mPosition.y + kAvatarUp.y * e;
    float az = mDepends.mAvatar.mPosition.z + kAvatarUp.z * e;
    float t = (mCameraData.currentPlayerDistance - mMinCameraDistance) / (mMaxCameraDistance - mMinCameraDistance);
    t = Clamp(t, 0.0f, 1.0f);
    mCameraData.avatarPosition.x = ((mDepends.mAvatar.mPosition.x + kAvatarUp.x * d) - ax) * t + ax;
    mCameraData.avatarPosition.y = ((mDepends.mAvatar.mPosition.y + kAvatarUp.y * d) - ay) * t + ay;
    mCameraData.avatarPosition.z = ((mDepends.mAvatar.mPosition.z + kAvatarUp.z * d) - az) * t + az;
}

// @ 0x00625bf0
void cCreatureCameraBase::UpdateVelocity()
{
    float f = (float)exp((double)(mCameraData.dt / kHalfLifeTime) * (double)-0.30103f);
    mCameraData.newPlatformVelocity.x = mCameraData.platformVelocity.x * f;
    mCameraData.newPlatformVelocity.y = mCameraData.platformVelocity.y * f;
    mCameraData.newPlatformVelocity.z = mCameraData.platformVelocity.z * f;
    if (sqrtf(mCameraData.newPlatformVelocity.x * mCameraData.newPlatformVelocity.x +
              mCameraData.newPlatformVelocity.y * mCameraData.newPlatformVelocity.y +
              mCameraData.newPlatformVelocity.z * mCameraData.newPlatformVelocity.z) < 0.01f) {
        mCameraData.newPlatformVelocity = kZeroVector;
    }
    float dx = mCameraData.desiredPosition.x - mCameraData.platformPosition.x;
    float dy = mCameraData.desiredPosition.y - mCameraData.platformPosition.y;
    float dz = mCameraData.desiredPosition.z - mCameraData.platformPosition.z;
    if (0.01f < sqrtf(dz * dz + dy * dy + dx * dx)) {
        float inv = 1.0f / kVelocityRate;
        float maxDelta = kVelocityAccel * mCameraData.dt;
        float vz = dz * inv - mCameraData.newPlatformVelocity.z;
        float vx = inv * dx - mCameraData.newPlatformVelocity.x;
        float vy = dy * inv - mCameraData.newPlatformVelocity.y;
        float lenSq = vz * vz + vy * vy + vx * vx;
        if (maxDelta * maxDelta < lenSq) {
            float s = maxDelta / sqrtf(lenSq);
            vx = vx * s;
            vy = vy * s;
            vz = s * vz;
        }
        mCameraData.newPlatformVelocity.x = vx + mCameraData.newPlatformVelocity.x;
        mCameraData.newPlatformVelocity.y = vy + mCameraData.newPlatformVelocity.y;
        mCameraData.newPlatformVelocity.z = vz + mCameraData.newPlatformVelocity.z;
    }
    float dt = mCameraData.dt;
    mCameraData.newPlatformPosition.x = mCameraData.platformPosition.x + dt * mCameraData.newPlatformVelocity.x;
    mCameraData.newPlatformPosition.y = mCameraData.platformPosition.y + mCameraData.newPlatformVelocity.y * dt;
    mCameraData.newPlatformPosition.z = mCameraData.platformPosition.z + mCameraData.newPlatformVelocity.z * dt;
}
}
