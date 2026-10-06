// Slice s0101d130 -- FUN_0101d130 (0x0101d130, 6925 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc). Optimized frame (ebx = this),
// 16-byte aligned stack (and esp,-16) from the aligned Matrix44 local.
//
// Space-stage planet camera per-frame update. `this` is the retail
// SP::cSPSpacePlanetCameraController (the PDB candidate "cSPUISpace::CreateToolButtons" is a
// mis-scored caller match). The retail layout does NOT follow the 2008 dev-PDB layout, so the
// members below are named by retail offset, with the role that the code shows.
//
// Arguments: deltaTime (milliseconds, unsigned), viewer (App::cViewer, receives the camera
// transform at the end).
//
// Flow: advance the UFO simulation clock, project the UFO onto the planet surface, choose a
// camera tuning set (normal / near-ground / avatar), lerp the camera tuning towards it,
// orbit the eye around the look-at point, run the "approach planet" day-side transition,
// build the camera-to-world matrix and hand it to the viewer, then update the audio listener
// and the altitude-driven property.
#include "types.h"

#include <math.h>

namespace {

struct Vector3 {
    float x, y, z;
};

struct Quaternion {
    float x, y, z, w;
};

struct Matrix3 {
    float m[3][3];
};

struct Matrix44Raw {
    float m[4][4];
};

struct __declspec(align(16)) Matrix44 {
    float m[4][4];
    Matrix44() {}
    explicit Matrix44(const Matrix3& rot);   // rw::math::fpu::Matrix44Template<float,0>(Matrix33)
};

inline float Min(const float& a, const float& b) { return (b < a) ? b : a; }
inline float Max(const float& a, const float& b) { return (a < b) ? b : a; }

inline Vector3 Cross(const Vector3& a, const Vector3& b)
{
    Vector3 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    return r;
}

inline Vector3 Negate(const Vector3& a)
{
    Vector3 r;
    r.x = -a.x;
    r.y = -a.y;
    r.z = -a.z;
    return r;
}

} // namespace

// ---- external helpers (cdecl unless noted) ---------------------------------------------
Vector3*    Vector3_Normalize(Vector3* out, const Vector3* v);                       // 0x00436ce0
Vector3*    normalized_safe(Vector3* out, const Vector3* v);                         // 0x00449c20
Vector3*    QuaternionRotate(Vector3* out, const Vector3* v, const Quaternion* q);   // 0x0059aed0
Quaternion* QuaternionSlerp(Quaternion* out, const Quaternion* a, const Quaternion* b, float t);     // 0x005b2500
Quaternion* QuaternionSlerpShortest(Quaternion* out, const Quaternion* a, const Quaternion* b, float t); // 0x005b26f0
float       AngleWrap(float a);                                                      // 0x005b4f20
Quaternion* QuaternionFromDirections(Quaternion* out, const Vector3* from, const Vector3* to);      // 0x00698180
float       SignedAngleAround(const Vector3* a, const Vector3* b, const Vector3* axis); // 0x006994a0
Matrix3*    Matrix3FromFacingAndUp(Matrix3* out, const Vector3* facing, const Vector3* up); // 0x0069b440
Quaternion* QuaternionFromMatrix33(Quaternion* out, const Matrix3* m, float eps);    // 0x00472b80
void        ApplyStateFromProperty(int prop, float altitude);                         // 0x006f32e0
Vector3*    RotateTowards(Vector3* out, const Vector3* from, const Vector3* to, float t); // 0x00b0fd00
Matrix3*    Matrix3FromQuaternion(Matrix3* out, const Quaternion* q);                // 0x00bd7270
float       CameraTuningHeight(int tuning, uint32_t key, float height, int which);   // 0x010433e0
float       CameraTuningValue(int tuning, uint32_t key, float height, int which);    // 0x01043310
void        ListenerFromPosition(Vector3* out, const Vector3* eye);                  // 0x01042480

extern const Vector3    kWorldUp;          // 0x015b6df4
extern const float      kSunDistance;      // 0x015b6dc0
extern const Vector3    kUFOForward;       // 0x015b6de8
extern const Quaternion kIdentityQuat;     // 0x016dd450
extern bool  gPlanetCamNearGroundEnable;   // 0x016dd389
extern bool  gPlanetCamApproachFromSun;    // 0x016dd38a
extern bool  gPlanetCamApproachUseSunDir;  // 0x016dd38b
extern float gPlanetCamTuningTolerance;    // 0x016dd3d4
extern float gPlanetCamTuningInRate;       // 0x016dd3d8
extern float gPlanetCamApproachFOV;        // 0x016dd3dc
extern float gPlanetCamApproachTopHeight;  // 0x016dd3e8
extern float gPlanetCamTuningLerpDist;     // 0x016dd404
extern float gPlanetCamTuningLerpRate;     // 0x016dd408
extern bool  gPlanetCamApproachEnable;     // 0x016dd441

namespace SP {

struct cGameTimeManager {
    uint32_t pad0[0x48 / 4];
    uint8_t  mFlags;   // +0x48, bit 0 = paused
};
cGameTimeManager* GameTimeManager();

struct cSpatialObject {   // the UFO's spatial base (cSPGameDataUFO + 0x34)
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3*    GetPosition();      // +0x2c
    virtual const Quaternion* GetOrientation();   // +0x30
    void UpdateWhilePaused(uint32_t deltaTime);   // 0x00c431a0
};

struct cSPGameDataUFO {
    float GetSimTime();                             // 0x00c37120
    float GetMaxGroundSpeed();                      // 0x00c38840
    void  SetCameraAnchor(const Vector3* p);        // 0x00c3be70
    void  PopToDestination();                       // 0x00c37e60
    cSpatialObject* Spatial() { return reinterpret_cast<cSpatialObject*>(reinterpret_cast<char*>(this) + 0x34); }
    const Vector3& Velocity() { return *reinterpret_cast<Vector3*>(reinterpret_cast<char*>(this) + 0x724); }
};

struct cSPSimulatorSpaceGame {
    cSPGameDataUFO* GetPlayerInventory();           // 0x00a1ad60
};
cSPSimulatorSpaceGame* GetUFOSimulator();           // 0x00ffbe50

struct cSPPlanetCamera {                            // returned by 0x00c37360
    float GetHoverHeight();                         // 0x00fb7ba0
    float GetApproachHeight();                      // 0x00a0ab60
};
cSPPlanetCamera* PlanetCamera();                    // 0x00c37360

struct cPlanetModel {
    Vector3* ProjectToSurface(Vector3* out, const Vector3* p);   // 0x00b81630
    float    GetRadius();                                        // 0x00b7e4d0
    float    GetWaterHeight();                                   // 0x00b7e390
};
cPlanetModel* PlanetModel();                        // 0x00b3d350

struct cPlanet;
cPlanet* cSPLivingUniverse_GetActivePlanet();        // 0x01021260
bool PlanetIsHomeworld(cPlanet* p);                 // 0x0102adf0
bool PlanetIsColonized(cPlanet* p);                 // 0x0102c600

struct cAvatar {
    bool IsOnPlanetSurface();                       // 0x00ff6550
};
struct cGameNounManager {
    cAvatar* GetAvatar();                           // 0x00b1fdb0
};
cGameNounManager* SpaceGameGet();                   // 0x01002bd0

struct cTimeOfDay {
    static cTimeOfDay* Instance();                  // 0x00bc30b0
    void GetSunDirection(Vector3* out);             // 0x00bc2c00
};

struct cAudioListener {
    void SetPosition(float y, float z, float scale); // 0x00b10540
};
cAudioListener* AudioListener();                    // 0x00b3d280

struct cViewer {
    void SetNearClip(float v);                      // 0x007c4ba0
    void SetFarClip(float v);                       // 0x007c4bc0
    void SetViewAngle(float v);                     // 0x007c5350
    void SetCameraToWorld(const Matrix44* m);       // 0x007c4c40
};

class cSPSpacePlanetCameraController {
public:
    void Update(uint32_t deltaTime, cViewer* viewer);

    // helpers of the same class (thiscall)
    void  AdvanceSimulation(float seconds);                         // 0x0101b670
    float GetDefaultPullOut();                                      // 0x01017d30
    float GetReferenceHeight();                                     // 0x01017bb0
    void  GetUFOAnchor(float seconds, Vector3* out);                // 0x01017ce0
    void  UpdateYaw(float seconds);                                 // 0x01019090
    void  UpdateCameraPitchRotation(float seconds, float pitch, Vector3* lookAt, Vector3* eye); // 0x01019950
    void  ApplyZoom(float seconds, Vector3* eye, Vector3* lookAt, Vector3* up, Vector3* anchor,
                    float maxZoom, float zoomDelta, float extra);   // 0x0101c780
    void  ComputeApproachFrame(Vector3* outAxis, const Vector3* worldUp, float radius,
                               float distance, float fov, float approachFOV,
                               Vector3* outEye, Vector3* outLookAt, Vector3* outUp); // 0x01018810
    void  SetSourceInterpolation(cViewer* viewer, float weight);    // 0x01019f50
    void  UpdateEffects();                                          // 0x0101ad50

    // ---- retail layout (offsets verified against 0x0101d130) ----
    uint32_t pad00[0x10 / 4];
    int      mAltitudeProperty;        // +0x10
    int      mTuning;                  // +0x14  camera tuning table handle
    uint32_t pad18[(0x68 - 0x18) / 4];
    bool     mSnapTuning;              // +0x68
    uint8_t  pad69[3];
    float    mDistance;                // +0x6c
    float    mFOV;                     // +0x70
    float    mSurfaceDistance;         // +0x74
    float    mZoom;                    // +0x78
    float    mMaxZoom;                 // +0x7c
    float    mLookAtHeight;            // +0x80
    float    mPitch;                   // +0x84
    float    mPullOut;                 // +0x88 (unused here)
    float    mPullOutRight;            // +0x8c
    float    mPullOutUp;               // +0x90
    Vector3  mEyeDirection;            // +0x94
    uint32_t padA0[(0xb4 - 0xa0) / 4];
    Vector3  mEye;                     // +0xb4
    Vector3  mLookAt;                  // +0xc0
    bool     mZooming;                 // +0xcc
    uint8_t  padCD[3];
    float    mTuningBlend;             // +0xd0
    Vector3  mPrevEye;                 // +0xd4
    Quaternion mPrevOrientation;       // +0xe0
    float    mBlendIn;                 // +0xf0
    float    mBlendInTime;             // +0xf4
    Matrix44Raw mCameraToWorld;        // +0xf8 last matrix handed to the viewer (row 3 = eye, w)
    int      mMode;                    // +0x138 0 = normal, 3 = near ground, 4 = avatar
    bool     pad13c;
    bool     mRotateLeft;              // +0x13d
    bool     mRotateRight;             // +0x13e
    bool     mApproachStart;           // +0x13f
    bool     mApproaching;             // +0x140
    uint8_t  pad141[3];
    Vector3  mApproachFrom;            // +0x144
    Vector3  mApproachTo;              // +0x150
    uint32_t pad15c[(0x168 - 0x15c) / 4];
    Vector3  mApproachUp;              // +0x168
    Quaternion mApproachOrientation;   // +0x174
    float    mApproachTwist;           // +0x184
    Vector3  mApproachAnchor;          // +0x188
    bool     mApproachDone;            // +0x194
};

} // namespace SP

using namespace SP;

// @ 0x0101d130
void SP::cSPSpacePlanetCameraController::Update(uint32_t deltaTime, cViewer* viewer)
{
    bool paused = (GameTimeManager()->mFlags & 1) != 0;
    cSPGameDataUFO* ufo = GetUFOSimulator()->GetPlayerInventory();

    float simTimeBefore = ufo->GetSimTime();
    if (!paused)
        AdvanceSimulation((float)deltaTime * 0.001f);
    float simTimeAfter = ufo->GetSimTime();
    float simTimeDelta = simTimeAfter - simTimeBefore;
    if (paused)
        ufo->Spatial()->UpdateWhilePaused(deltaTime);
    if (!ufo)
        return;

    float deltaMs = (float)deltaTime;
    float seconds = deltaMs * 0.001f;

    float pullOut = mPullOutRight;
    if (pullOut == 0.0f)
        pullOut = GetDefaultPullOut();

    cSPPlanetCamera* planetCam = PlanetCamera();
    cSpatialObject* spatial = ufo->Spatial();

    // Hover height: smoothstep of the UFO's tangential speed over its maximum.
    const Vector3& pos = *spatial->GetPosition();
    Vector3 p = pos;
    float invLen = 1.0f / sqrtf(p.x * p.x + p.y * p.y + p.z * p.z + 1e-08f);
    Vector3 n;
    n.x = p.x * invLen;
    n.y = p.y * invLen;
    n.z = p.z * invLen;
    const Vector3& vel = ufo->Velocity();
    float radial = vel.x * n.x + vel.y * n.y + vel.z * n.z;
    Vector3 tangent;
    tangent.x = vel.x - n.x * radial;
    tangent.y = vel.y - n.y * radial;
    tangent.z = vel.z - n.z * radial;
    float zero = 0.0f;
    float maxSpeed = ufo->GetMaxGroundSpeed();
    float speed = sqrtf(tangent.z * tangent.z + tangent.y * tangent.y + tangent.x * tangent.x);
    speed = Min(Max(speed, zero), maxSpeed);
    float t = speed / maxSpeed;
    float hover = planetCam->GetHoverHeight();
    float targetHeight = (3.0f - (t + t)) * t * t * hover;
    targetHeight = GetReferenceHeight() + targetHeight;

    bool nearGroundPlanet;
    if (PlanetIsHomeworld(cSPLivingUniverse_GetActivePlanet()))
        nearGroundPlanet = true;
    else
        nearGroundPlanet = PlanetIsColonized(cSPLivingUniverse_GetActivePlanet());

    bool avatarOnSurface = SpaceGameGet()->GetAvatar() ? SpaceGameGet()->GetAvatar()->IsOnPlanetSurface()
                                                       : false;

    // Camera mode: 4 = avatar on surface, 3 = near-ground camera, 0 = normal.
    if (!paused) {
        int mode = mMode;
        if (mode != 4 && avatarOnSurface) {
            mMode = 4;
            mZooming = true;
        } else if (mode == 4 && !avatarOnSurface) {
            mZooming = true;
            mMode = 0;
        } else {
            bool nearGround = gPlanetCamNearGroundEnable;
            if (mode != 3 && nearGroundPlanet && nearGround)
                mMode = 3;
            else if (mode == 3 && !(nearGroundPlanet && nearGround))
                mMode = 0;
        }
    }

    uint32_t key;
    switch (mMode) {
    case 3:  key = 0x6046db4; break;
    case 4:  key = 0x6046db5; break;
    default: key = 0x195a060; break;
    }

    float tunedHeight = CameraTuningHeight(mTuning, key, targetHeight, 0);
    float wantDistance = CameraTuningValue(mTuning, key, tunedHeight, 1);
    float wantLookAtHeight = CameraTuningValue(mTuning, key, tunedHeight, 2);
    float wantPitch = CameraTuningValue(mTuning, key, tunedHeight, 3) * 0.017453292f;

    Vector3 anchor;
    GetUFOAnchor(seconds, &anchor);
    Vector3 surface;
    const Vector3* s = PlanetModel()->ProjectToSurface(&surface, &anchor);
    float wantSurfaceDistance = sqrtf(s->x * s->x + s->y * s->y + s->z * s->z);

    static float sLastZoom = mZoom;

    if (mSnapTuning) {
        mDistance = wantDistance;
        mSurfaceDistance = wantSurfaceDistance;
        mTuningBlend = 0.0f;
        Vector3 dir;
        const Vector3* r = QuaternionRotate(&dir, &kUFOForward, spatial->GetOrientation());
        Vector3 d = *r;
        mSnapTuning = false;
        float inv = 1.0f / sqrtf(d.z * d.z + d.y * d.y + d.x * d.x);
        d.x = inv * d.x;
        d.y = inv * d.y;
        d.z = inv * d.z;
        sLastZoom = mZoom;
        mEyeDirection.x = d.x;
        mLookAtHeight = wantLookAtHeight;
        mEyeDirection.y = d.y;
        mEyeDirection.z = d.z;
        mPitch = wantPitch;
    } else {
        if (!mZooming)
            mZooming = mRotateLeft || mRotateRight || fabsf(pullOut) > 1.5258789e-05f;

        bool blendIn = mZooming;
        if (!blendIn) {
            float h = CameraTuningHeight(mTuning, key, planetCam->GetHoverHeight() * 2.0f, 0);
            float d = CameraTuningValue(mTuning, key, h, 1);
            if (d > mDistance && wantDistance > mDistance)
                blendIn = true;
        }

        float one = 1.0f;
        float rate = gPlanetCamTuningInRate * seconds;
        float v;
        bool reversed = fabsf(pullOut) > 1.5258789e-05f && fabsf(simTimeDelta) > 0.0f &&
                        (pullOut > 0.0f) == (simTimeAfter > simTimeBefore);
        if (reversed)
            mZooming = false;

        if (!reversed && blendIn &&
            (fabsf((mDistance - wantDistance) / wantDistance) > gPlanetCamTuningTolerance ||
             fabsf((mLookAtHeight - wantLookAtHeight) / wantLookAtHeight) > gPlanetCamTuningTolerance ||
             fabsf((mSurfaceDistance - wantSurfaceDistance) / wantSurfaceDistance) > gPlanetCamTuningTolerance ||
             fabsf((mPitch - wantPitch) / wantPitch) > gPlanetCamTuningTolerance) &&
            (v = Min(gPlanetCamTuningInRate * seconds + mTuningBlend, one)) > 0.0f) {
            mTuningBlend = v;
        } else {
            v = mTuningBlend - rate;
            mTuningBlend = Max(v, zero);
        }

        float blend = mTuningBlend;
        if (blend > 0.0f) {
            float a = Min(blend * gPlanetCamTuningLerpRate * seconds, one);
            mDistance = (wantDistance - mDistance) * a + mDistance;
            mLookAtHeight = (wantLookAtHeight - mLookAtHeight) * a + mLookAtHeight;
            mPitch = (wantPitch - mPitch) * a + mPitch;
            float b = Min(blend * gPlanetCamTuningLerpDist * seconds, one);
            mSurfaceDistance = (wantSurfaceDistance - mSurfaceDistance) * b + mSurfaceDistance;
        }
    }

    UpdateYaw(seconds);

    // Look-at point above the anchor, eye behind it along mEyeDirection, then pitched about
    // the horizontal axis through the look-at point.
    float inv = 1.0f / sqrtf(anchor.x * anchor.x + anchor.z * anchor.z + anchor.y * anchor.y + 1e-08f);
    Vector3 up;
    up.x = inv * anchor.x;
    up.y = inv * anchor.y;
    up.z = inv * anchor.z;
    Vector3 lookAt;
    lookAt.x = up.x * mLookAtHeight + anchor.x;
    lookAt.y = up.y * mLookAtHeight + anchor.y;
    lookAt.z = up.z * mLookAtHeight + anchor.z;
    Vector3 lookAtCopy = lookAt;
    float back = mDistance * -1.0f;
    Vector3 eye;
    eye.x = mEyeDirection.x * back + lookAt.x;
    eye.y = mEyeDirection.y * back + lookAt.y;
    eye.z = mEyeDirection.z * back + lookAt.z;
    Vector3 axis = Cross(lookAt, eye);
    Vector3 toEye;
    toEye.x = eye.x - lookAt.x;
    toEye.y = eye.y - lookAt.y;
    toEye.z = eye.z - lookAt.z;
    float axisInv = 1.0f / sqrtf(axis.x * axis.x + axis.z * axis.z + axis.y * axis.y);
    float halfPitch = -mPitch * 0.5f;
    Vector3 an;
    an.x = axisInv * axis.x;
    an.y = axisInv * axis.y;
    an.z = axisInv * axis.z;
    float sn = sinf(halfPitch);
    Quaternion pitchQ;
    pitchQ.x = sn * an.x;
    pitchQ.y = sn * an.y;
    pitchQ.z = sn * an.z;
    pitchQ.w = cosf(halfPitch);
    float qInv = 1.0f / sqrtf(pitchQ.x * pitchQ.x + pitchQ.w * pitchQ.w + pitchQ.z * pitchQ.z + pitchQ.y * pitchQ.y);
    pitchQ.x = qInv * pitchQ.x;
    pitchQ.y = qInv * pitchQ.y;
    pitchQ.z = qInv * pitchQ.z;
    pitchQ.w = qInv * pitchQ.w;
    Vector3 rotated;
    const Vector3* re = QuaternionRotate(&rotated, &toEye, &pitchQ);
    eye.x = lookAtCopy.x + re->x;
    eye.y = lookAtCopy.y + re->y;
    eye.z = lookAtCopy.z + re->z;

    UpdateCameraPitchRotation(seconds, 0.0f, &lookAt, &eye);
    ApplyZoom(seconds, &eye, &lookAt, &up, &anchor, mMaxZoom, mZoom - sLastZoom, 0.0f);
    sLastZoom = mZoom;

    // Approach-planet transition: below the approach height, swing the camera from the sun
    // side down onto the UFO.
    if (gPlanetCamApproachEnable) {
        float approachHeight = PlanetCamera()->GetApproachHeight();
        if (targetHeight > approachHeight && !(GameTimeManager()->mFlags & 1)) {
            if (mApproachStart || !mApproaching) {
                mApproaching = true;
                Vector3 sun;
                cTimeOfDay::Instance()->GetSunDirection(&sun);
                Vector3 fromEye, fromLookAt, fromUp;
                if (mApproachStart) {
                    mApproachStart = false;
                    mApproachDone = false;
                    Vector3 tmp;
                    const Vector3* r = Vector3_Normalize(&tmp, spatial->GetPosition());
                    mApproachTo = *r;
                    if (gPlanetCamApproachUseSunDir)
                        r = Vector3_Normalize(&tmp, &sun);
                    mApproachAnchor = *r;
                    float h = CameraTuningHeight(mTuning, 0x195a060, approachHeight, 0);
                    float dist = CameraTuningValue(mTuning, 0x195a060, h, 1);
                    float fov = CameraTuningValue(mTuning, 0x195a060, h, 2) * 0.017453292f;
                    ComputeApproachFrame(&mApproachAnchor, &kWorldUp, PlanetModel()->GetRadius(), dist, fov,
                                         gPlanetCamApproachFOV, &fromEye, &fromLookAt, &fromUp);
                    ufo->SetCameraAnchor(&kWorldUp);
                    GetUFOSimulator()->GetPlayerInventory()->PopToDestination();
                } else {
                    fromEye = eye;
                    fromLookAt = lookAt;
                    fromUp = up;
                    Vector3 tmp;
                    mApproachAnchor = *Vector3_Normalize(&tmp, spatial->GetPosition());
                    if (gPlanetCamApproachFromSun) {
                        Vector3 sunPos;
                        sunPos.x = kWorldUp.x * kSunDistance;
                        sunPos.y = kWorldUp.y * kSunDistance;
                        sunPos.z = kWorldUp.z * kSunDistance;
                        const Vector3* sn2 = Vector3_Normalize(&tmp, &sun);
                        sunPos.x = -sn2->x + sunPos.x;
                        sunPos.y = -sn2->y + sunPos.y;
                        sunPos.z = -sn2->z + sunPos.z;
                        Vector3 tmp2;
                        mApproachTo = *Vector3_Normalize(&tmp2, &sunPos);
                    } else {
                        Vector3 w;
                        w.x = mApproachFrom.x - sun.x * 0.001f;
                        w.y = mApproachFrom.y - sun.y * 0.001f;
                        w.z = mApproachFrom.z - sun.z * 0.001f;
                        Vector3 sunPos;
                        sunPos.x = kWorldUp.x * kSunDistance;
                        sunPos.y = kWorldUp.y * kSunDistance;
                        sunPos.z = kWorldUp.z * kSunDistance;
                        float d = w.z * kWorldUp.z + w.y * kWorldUp.y + w.x * kWorldUp.x;
                        w.x = w.x - d * kWorldUp.x;
                        w.y = w.y - d * kWorldUp.y;
                        w.z = w.z - d * kWorldUp.z;
                        Vector3 tmp2;
                        const Vector3* wn = Vector3_Normalize(&tmp2, &w);
                        w.x = wn->x + sunPos.x;
                        w.y = wn->y + sunPos.y;
                        w.z = wn->z + sunPos.z;
                        mApproachTo = *Vector3_Normalize(&sunPos, &w);
                    }
                }

                Vector3 tmp;
                mApproachFrom = *Vector3_Normalize(&tmp, &fromEye);
                Quaternion fromToQ;
                QuaternionFromDirections(&fromToQ, &mApproachFrom, &mApproachTo);

                Vector3 view;
                view.x = fromLookAt.x - fromEye.x;
                view.y = fromLookAt.y - fromEye.y;
                view.z = fromLookAt.z - fromEye.z;
                Vector3 viewN;
                Vector3_Normalize(&viewN, &view);
                Vector3 negFrom = Negate(mApproachFrom);
                Quaternion q;
                mApproachOrientation = *QuaternionFromDirections(&q, &negFrom, &viewN);

                Vector3 negTo = Negate(mApproachTo);
                Vector3 side = Cross(viewN, fromUp);
                Vector3 trueUp = Cross(side, viewN);
                normalized_safe(&fromUp, &trueUp);
                Vector3 rotUp = *QuaternionRotate(&tmp, &fromUp, &fromToQ);

                Vector3 side2 = Cross(negTo, kWorldUp);
                Vector3 trueUp2 = Cross(side2, negTo);
                mApproachUp = *normalized_safe(&tmp, &trueUp2);

                Vector3 negTo2 = Negate(mApproachTo);
                mApproachTwist = AngleWrap(SignedAngleAround(&mApproachUp, &rotUp, &negTo2));
            }

            float frac = (targetHeight - approachHeight) / (gPlanetCamApproachTopHeight - approachHeight);
            Vector3 dirNow;
            RotateTowards(&dirNow, &mApproachFrom, &mApproachTo, frac);
            Quaternion orient;
            QuaternionSlerpShortest(&orient, &mApproachOrientation, &kIdentityQuat, frac);
            Vector3 negDir = Negate(dirNow);
            Vector3 tmp;
            Vector3 viewDir = *QuaternionRotate(&tmp, &negDir, &orient);
            Quaternion toNow;
            QuaternionFromDirections(&toNow, &mApproachTo, &dirNow);
            Vector3 upNow = *QuaternionRotate(&tmp, &mApproachUp, &toNow);

            float halfTwist = (1.0f - frac) * mApproachTwist * 0.5f;
            float st = sinf(halfTwist);
            Quaternion twist;
            twist.x = st * viewDir.x;
            twist.y = viewDir.y * st;
            twist.z = viewDir.z * st;
            twist.w = cosf(halfTwist);

            float eyeLen = sqrtf(eye.y * eye.y + eye.z * eye.z + eye.x * eye.x);
            eye.x = eyeLen * dirNow.x;
            eye.y = dirNow.y * eyeLen;
            eye.z = dirNow.z * eyeLen;
            lookAt.x = eye.x + viewDir.x;
            lookAt.y = eye.y + viewDir.y;
            lookAt.z = eye.z + viewDir.z;
            up = *QuaternionRotate(&tmp, &upNow, &twist);

            if (!mApproachDone) {
                ufo->SetCameraAnchor(&mApproachAnchor);
                mEyeDirection = viewDir;
            } else {
                ufo->SetCameraAnchor(&kWorldUp);
            }
        } else {
            if (mApproaching) {
                mApproaching = false;
                SetSourceInterpolation(viewer, 1.0f);
            }
            mApproachStart = false;
            mApproachDone = true;
        }
    }

    // Orientation from the view frame, blended in from the previous frame's camera.
    Vector3 facing;
    facing.x = lookAt.x - eye.x;
    facing.y = lookAt.y - eye.y;
    facing.z = lookAt.z - eye.z;
    Matrix3 frame;
    Quaternion qtmp;
    const Quaternion* fq = QuaternionFromMatrix33(&qtmp, Matrix3FromFacingAndUp(&frame, &facing, &up), 0.0f);
    Quaternion orientation = *fq;

    mBlendIn = deltaMs / (mBlendInTime * 1000.0f) + mBlendIn;
    Vector3 camPos = eye;
    float one = 1.0f;
    float blend = Min(mBlendIn, one);
    mBlendIn = blend;
    if (blend != 1.0f) {
        camPos.x = (eye.x - mPrevEye.x) * blend + mPrevEye.x;
        camPos.y = (eye.y - mPrevEye.y) * blend + mPrevEye.y;
        camPos.z = (eye.z - mPrevEye.z) * blend + mPrevEye.z;
        orientation = *QuaternionSlerp(&qtmp, &mPrevOrientation, &orientation, blend);
    }

    Matrix3 rot;
    Matrix44 m(*Matrix3FromQuaternion(&rot, &orientation));
    Matrix44 cameraToWorld = m;
    cameraToWorld.m[3][0] = camPos.x;
    cameraToWorld.m[3][1] = camPos.y;
    cameraToWorld.m[3][2] = camPos.z;

    mEye = eye;
    mLookAt = lookAt;

    viewer->SetNearClip(2.0f);
    viewer->SetFarClip(3000.0f);
    viewer->SetViewAngle(mFOV);
    viewer->SetCameraToWorld(&cameraToWorld);
    mCameraToWorld = reinterpret_cast<const Matrix44Raw&>(cameraToWorld);

    UpdateEffects();

    Vector3 listener;
    ListenerFromPosition(&listener, &eye);
    if (AudioListener())
        AudioListener()->SetPosition(listener.y, listener.z, listener.x * 0.5f);

    const float* row3 = mCameraToWorld.m[3];
    int prop = mAltitudeProperty;
    float camDist = sqrtf(row3[0] * row3[0] + row3[3] * row3[3] + row3[2] * row3[2] + row3[1] * row3[1]);
    ApplyStateFromProperty(prop, camDist - PlanetModel()->GetWaterHeight());

    mPullOutUp = 0.0f;
    mPullOutRight = 0.0f;
}
