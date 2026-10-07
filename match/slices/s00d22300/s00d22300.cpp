// @ 0x00d22300  SP::cCreatureCamera::ManageAutoCameraMovement(float dt)  (PDB candidate, caller-scored)
//
// Creature-stage auto camera: when the avatar moves, swing the camera's target theta (+0x174)
// toward the avatar's direction of travel, and ease the camera pitch (+0x178) toward the
// auto-pitch range while the avatar is moving.
// Retail layout of cCreatureCamera differs from the 2008 PDB inside tCameraData; the members
// used here are named by offset where the PDB doesn't pin them. From 0x23c on the retail
// layout is the PDB's shifted by -8 (mbAutoPitchActive 0x23c, mAvatarMovingAutoPitchFar 0x240,
// ...Close 0x248, ...InterpTime 0x250); mbActive stays at 0x314.
// Local names from the 2008 dev build's S_REGREL32 records (destination, cameraToAvatar,
// avatarToDest, pctRotating, distance, angleToDestination, desiredDir); that build differs (debug draw).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include <math.h>
#include "types.h"

// SSE clamp helper from the original headers (maxss then minss).
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

template<class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
// Math::Vector3 operators (out-of-line copies at 0x0041db10 / 0x0041dca0 / 0x0041dd30, see s0041d490)
inline Vector3 operator-(const Vector3& a, const Vector3& b)
{
    Vector3 r(a.x - b.x, a.y - b.y, a.z - b.z);
    return r;
}
inline Vector3 operator*(const Vector3& a, const float& s)
{
    Vector3 r(a.x * s, a.y * s, a.z * s);
    return r;
}
inline bool operator!=(const Vector3& a, const Vector3& b)
{
    return !(a.x == b.x && a.y == b.y && a.z == b.z);
}
struct Vector2 { float x, y; };

// SP-side vector type used by the camera data and SP::normalized_safe; built from Math::Vector3
// results (that conversion is the temp copy before each normalized_safe call).
struct cSPVector3 : Vector3 {
    cSPVector3() {}
    cSPVector3(const Vector3& v) : Vector3(v) {}
};
inline cSPVector3 Cross(const Vector3& a, const Vector3& b)
{
    cSPVector3 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    return r;
}


inline float Dot(const Vector3& a, const Vector3& b) { return a.x * b.x + (a.y * b.y + a.z * b.z); }
// v with its component along the unit vector n removed
inline Vector3 RemoveComponent(const Vector3& v, const Vector3& n) { return v - n * Dot(v, n); }

namespace SP {
cSPVector3 normalized_safe(const cSPVector3& v);                                       // 0x00449c20
float Dot3(const cSPVector3& v);                                                     // 0x004885d0 (v.v)
cSPVector3 RotateTowards(const cSPVector3& from, const cSPVector3& to, float t);          // 0x00b0fd00
bool FUN_00d21ca0(const Vector3& a, const Vector3& b, float tolerance);          // 0x00d21ca0
bool FUN_00805180();                                                              // 0x00805180

struct cLocomotionState { char pad[0x5c]; int field_5c; };
struct cAvatarLocomotion {
    const Vector3& GetPosition();          // 0x00c421f0
    cLocomotionState* GetState();          // 0x00c41ec0
};
struct cCreatureAnimal { char pad[0xc0]; cAvatarLocomotion mLocomotion; };
struct cGameNounManager { cCreatureAnimal* GetAvatar(); };   // 0x00b1fdb0
cGameNounManager* NounManager();                             // 0x00b3d300

struct cGameTimeManager { char pad[0x48]; uint8_t mPauseFlags; };
cGameTimeManager* GameTimeManager();                         // 0x00b3d380

struct ITerrain {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void ProjectPosition(Vector3& pos, int mode, Vector3 dir);   // +0x38
};
ITerrain* GetTerrain();                                      // 0x00b3d240

void* GetCurrentGameMode();                                  // 0x00b5b800
extern char g_1654c10;                                       // a game mode object

// statics of this module
extern Vector3 sCameraDefaultDir;          // 0x0169deb0
extern bool    sAvatarPosUnchanged;        // 0x0169de85
extern float   sAutoThetaSpeed;            // 0x0169de8c
extern Vector3 sLastAvatarPos;             // 0x0169df04
// tuning (cCreatureCamera::ReloadTuning, see s00d247f0)
extern float g_15827a4;   // theta catch-up rate
extern float g_15827a8;   // distance normalizer
extern float g_15827ac;   // max theta step
extern float g_15827b4;   // moving speed threshold
extern float g_15827dc;   // theta speed accel
extern float g_15827e0;   // theta speed decel
extern float g_1582870;   // max angle
extern float g_1582874;   // min angle

class cCreatureCamera {
public:
    void ManageAutoCameraMovement(float dt);

    char pad0[0x48];
    /* 048 */ cSPVector3 mVec48;
    char pad54[0xac - 0x54];
    /* 0ac */ cSPVector3 mAvatarVelocity;
    char padb8[0x100 - 0xb8];
    /* 100 */ float mCurrentDistance;
    char pad104[0x114 - 0x104];
    /* 114 */ cSPVector3 mVec114;
    char pad120[0x134 - 0x120];
    /* 134 */ float mField134;
    char pad138[0x174 - 0x138];
    /* 174 */ float mTargetTheta;
    /* 178 */ float mTargetPhi;
    char pad17c[0x1ec - 0x17c];
    /* 1ec */ int mField1ec;
    /* 1f0 */ int mField1f0;
    char pad1f4[0x214 - 0x1f4];
    /* 214 */ float mMaxCameraDistance;
    char pad218[0x23c - 0x218];
    /* 23c */ bool mbAutoPitchActive;
    /* 240 */ Vector2 mAvatarMovingAutoPitchFar;
    /* 248 */ Vector2 mAvatarMovingAutoPitchClose;
    /* 250 */ float mAvatarMovingAutoPitchInterpTime;
    char pad254[0x2b8 - 0x254];
    /* 2b8 */ float mField2b8;
    char pad2bc[0x314 - 0x2bc];
    /* 314 */ bool mbActive;
};

// @ 0x00d22300
void cCreatureCamera::ManageAutoCameraMovement(float dt)
{
    cCreatureAnimal* avatar = NounManager()->GetAvatar();
    if (!FUN_00805180() || !avatar)
        return;

    float pctRotating = 0.0f;
    cSPVector3 cameraToAvatar(sCameraDefaultDir);
    cSPVector3 avatarToDest(sCameraDefaultDir);
    cAvatarLocomotion* loco = &avatar->mLocomotion;
    {
    cSPVector3 destination(loco->GetPosition());
    if (destination != sLastAvatarPos) {
        sLastAvatarPos = destination;
        sAvatarPosUnchanged = false;
    }

    if (fabsf(mField134) <= 1.0f && mField2b8 > 2.0f) {
        GetTerrain()->ProjectPosition(destination, 1, sCameraDefaultDir);
        if (destination.z * destination.z + destination.y * destination.y + destination.x * destination.x > 0.0f) {
            cameraToAvatar = normalized_safe(mVec114 - mVec48);
            cameraToAvatar = normalized_safe(RemoveComponent(cameraToAvatar, normalized_safe(mVec48)));
            avatarToDest = normalized_safe(destination - mVec114);
            avatarToDest = normalized_safe(RemoveComponent(avatarToDest, normalized_safe(mVec114)));
            Vector3 off = mVec114 - destination;
            float distance = sqrtf(off.x * off.x + off.y * off.y + off.z * off.z);
            float angleToDestination = acosf(Clamp(Dot(avatarToDest, cameraToAvatar), -1.0f, 1.0f));
            if (distance > 1.5258789e-05f && angleToDestination <= g_1582870 && angleToDestination >= g_1582874
                && loco->GetState()->field_5c != 0)
                pctRotating = Min(distance / g_15827a8, 1.0f);
        }
    } else {
        if (loco->GetState()->field_5c != 0 && mField1ec != 1 && mField1f0 != 1
            && !(GameTimeManager()->mPauseFlags & 1) && !sAvatarPosUnchanged
            && destination.x * destination.x + destination.z * destination.z + destination.y * destination.y > 0.0f
            && Dot3(mAvatarVelocity) > g_15827b4 * g_15827b4) {
            cameraToAvatar = normalized_safe(mVec114 - mVec48);
            cameraToAvatar = normalized_safe(RemoveComponent(cameraToAvatar, normalized_safe(mVec114)));
            avatarToDest = normalized_safe(destination - mVec114);
            avatarToDest = normalized_safe(RemoveComponent(avatarToDest, normalized_safe(mVec114)));
            Vector3 off = mVec114 - destination;
            float distance = sqrtf(off.x * off.x + off.y * off.y + off.z * off.z);
            float angleToDestination = acosf(Clamp(Dot(avatarToDest, cameraToAvatar), -1.0f, 1.0f));
            if (angleToDestination <= g_1582870 && angleToDestination >= g_1582874
                && !FUN_00d21ca0(cameraToAvatar, avatarToDest, 1.5258789e-05f) && distance > 1.5258789e-05f)
                pctRotating = Min(distance / g_15827a8, 1.0f);
        }
    }
    }

    if (fabsf(pctRotating) > 1.5258789e-05f && !mbActive) {
        float rate = Min(1.0f, g_15827a4 * dt);
        sAutoThetaSpeed = Clamp(rate * pctRotating, sAutoThetaSpeed - g_15827e0, g_15827dc + sAutoThetaSpeed);
        float angleToDestination;
        {
            cSPVector3 desiredDir = normalized_safe(RotateTowards(cameraToAvatar, avatarToDest, Clamp(sAutoThetaSpeed, 0.0f, 1.0f)));
            angleToDestination = acosf(Clamp(Dot(desiredDir, cameraToAvatar), -1.0f, 1.0f));
        }
        float sign = (Dot(normalized_safe(Cross(cameraToAvatar, normalized_safe(mVec48))), avatarToDest) < 0.0f) ? 1.0f : -1.0f;
        mTargetTheta += Clamp(sign * angleToDestination, -g_15827ac, g_15827ac);
    } else {
        sAutoThetaSpeed = 0.0f;
    }

    if (!sAvatarPosUnchanged && !(GameTimeManager()->mPauseFlags & 1)) {
        if (!mbActive && mField1ec != 2 && Dot3(mAvatarVelocity) > g_15827b4 * g_15827b4
            && (mField2b8 > 2.0f || loco->GetState()->field_5c != 0))
            mbAutoPitchActive = true;
    } else {
        mbAutoPitchActive = false;
    }

    if (mbAutoPitchActive && GetCurrentGameMode() != &g_1654c10) {
        float t = Clamp((mMaxCameraDistance - mCurrentDistance) / mMaxCameraDistance, 0.0f, 1.0f);
        float hi = (mAvatarMovingAutoPitchClose.y - mAvatarMovingAutoPitchFar.y) * t + mAvatarMovingAutoPitchFar.y;
        float lo = (mAvatarMovingAutoPitchClose.x - mAvatarMovingAutoPitchFar.x) * t + mAvatarMovingAutoPitchFar.x;
        float target = Clamp(mTargetPhi, lo, hi);
        mTargetPhi = mTargetPhi + (target - mTargetPhi) * (1.0f - expf(dt / mAvatarMovingAutoPitchInterpTime * -0.30103f));
    }
}

}  // namespace SP
