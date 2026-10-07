// Slice s0101ed80 -- FUN_0101ed80 (0x0101ed80, 3510 bytes).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// A second per-frame update of the space-stage planet camera controller (the same retail
// class as 0x0101d130, see match/slices/s0101d130: same member offsets for distance, FOV,
// pull-out, eye direction, eye, look-at, zooming flag and tuning blend). This one is the
// free orbit camera around a fixed look-at point:
//   - on the first frame (eye still at the "unset" sentinel) it runs the planet camera
//     Update once with mSnapTuning set, to seed eye/look-at;
//   - the pull-out input zooms the wanted distance (clamped to 50..500), which mDistance then
//     blends towards;
//   - the yaw input rotates the eye direction about the look-at's up axis;
//   - the eye is pitched about the horizontal axis, and with flag bit 0 of +0x198 the extra
//     orbit angle at +0x78 is clamped to keep the view between 92 and 178 degrees from the
//     eye direction;
//   - near the planet surface the eye/look-at go through the viewer's water clearance check;
//   - the camera-to-world matrix goes to the viewer, then effects and the audio listener.
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

struct Matrix44 {
    float m[4][4];
    Matrix44() {}
    explicit Matrix44(const Matrix3& rot);   // rw::math::fpu::Matrix44Template<float,0>(Matrix33) 0x0045dca0
};

inline float Min(const float& a, const float& b) { return (b < a) ? b : a; }
inline float Max(const float& a, const float& b) { return (a < b) ? b : a; }

// maxss then minss (inline-asm helper of the /arch:SSE modules).
inline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

} // namespace

// ---- external helpers (cdecl unless noted) ---------------------------------------------
Vector3*    QuaternionRotate(Vector3* out, const Vector3* v, const Quaternion* q);   // 0x0059aed0
Matrix3*    Matrix3FromFacingAndUp(Matrix3* out, const Vector3* facing, const Vector3* up); // 0x0069b440
Quaternion* QuaternionFromMatrix33(Quaternion* out, const Matrix3* m, float eps);    // 0x00472b80
Matrix3*    Matrix3FromQuaternion(Matrix3* out, const Quaternion* q);                // 0x00bd7270
void        ListenerFromPosition(Vector3* out, const Vector3* eye);                  // 0x01042480
void        EASTLFree(void* p);                                                      // 0x00f47380 operator delete[]

extern const Vector3 kUnsetCameraEye;     // 0x016dd444
extern float gOrbitCamZoomRate;           // 0x016dd414
extern float gPlanetCamTuningTolerance;   // 0x016dd3d4
extern float gPlanetCamTuningInRate;      // 0x016dd3d8
extern float gPlanetCamTuningLerpRate;    // 0x016dd408

namespace SP {

struct cSpatialObject {   // the UFO's spatial base (cSPGameDataUFO + 0x34)
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3* GetPosition();   // +0x2c
};

struct cSPGameDataUFO {
    uint32_t pad0[0x34 / 4];
    cSpatialObject mSpatial;                 // +0x34
    uint32_t pad38[(0x74c - 0x38) / 4];
    bool     mbDestroyed;                    // +0x74c
};

struct cSPSimulatorSpaceGame {
    cSPGameDataUFO* GetPlayerInventory();    // 0x00a1ad60
};
cSPSimulatorSpaceGame* GetUFOSimulator();    // 0x00ffbe50

struct cPlanetModel {
    float GetRadius();                       // 0x00b7e4d0
};
cPlanetModel* PlanetModel();                 // 0x00b3d350

struct cAudioListener {
    void SetPosition(float y, float z, float scale); // 0x00b10540
};
cAudioListener* AudioListener();             // 0x00b3d280

struct cViewer {
    void SetNearClip(float v);               // 0x007c4ba0
    void SetFarClip(float v);                // 0x007c4bc0
    void SetViewAngle(float v);              // 0x007c5350
    void SetCameraToWorld(const Matrix44* m); // 0x007c4c40
};

// Camera location snapshot taken from a viewer (ctor 0x00b16dc0 fills position and frame
// through cViewer::GetCameraLocationInfo); used for the water clearance test.
struct cCameraLocation {
    Vector3  mPosition;     // +0x00
    Vector3  mDirection;    // +0x0c
    Vector3  mUp;           // +0x18
    Vector3  mRight;        // +0x24
    float    f30, f34, f38;
    Vector3  mLookAt;       // +0x3c
    char*    mpBuffer;      // +0x48
    uint32_t pad4c[(0xd8 - 0x4c) / 4];

    explicit cCameraLocation(cViewer* viewer);  // 0x00b16dc0
    ~cCameraLocation()
    {
        if (mpBuffer && reinterpret_cast<int*>(mpBuffer)[-1] != 0)
            EASTLFree(mpBuffer);
    }
    void Commit(int flag);                      // 0x00b17790
};
bool WaterClearance(cCameraLocation* loc, float* clearance);     // 0x00b181d0
void ApplyWaterClearance(cCameraLocation* loc, float clearance);  // 0x00b16490

class cSPSpacePlanetCameraController {
public:
    void Update(uint32_t deltaTime, cViewer* viewer);       // 0x0101d130
    void UpdateOrbit(uint32_t deltaTime, cViewer* viewer);  // 0x0101ed80

    float GetDefaultPullOut();                              // 0x01017d30
    void  UpdateEffects();                                  // 0x0101ad50

    // ---- retail layout (offsets as in 0x0101d130) ----
    uint32_t pad00[0x68 / 4];
    bool     mSnapTuning;              // +0x68
    uint8_t  pad69[3];
    float    mDistance;                // +0x6c
    float    mFOV;                     // +0x70
    float    mSurfaceDistance;         // +0x74
    float    mOrbitAngle;              // +0x78
    float    mMaxZoom;                 // +0x7c
    float    mLookAtHeight;            // +0x80
    float    mPitch;                   // +0x84
    float    mPullOut;                 // +0x88 wanted distance
    float    mPullOutRight;            // +0x8c zoom input
    float    mPullOutUp;               // +0x90 yaw input
    Vector3  mEyeDirection;            // +0x94
    uint32_t padA0[(0xb4 - 0xa0) / 4];
    Vector3  mEye;                     // +0xb4
    Vector3  mLookAt;                  // +0xc0
    bool     mZooming;                 // +0xcc
    uint8_t  padCD[3];
    float    mTuningBlend;             // +0xd0
    uint32_t padD4[(0x198 - 0xd4) / 4];
    uint8_t  mOrbitFlags;              // +0x198 bit 0 = clamp the orbit angle
};

} // namespace SP

using namespace SP;

// @ 0x0101ed80
void SP::cSPSpacePlanetCameraController::UpdateOrbit(uint32_t deltaTime, cViewer* viewer)
{
    Vector3& curEye = mEye;
    if (curEye.x == kUnsetCameraEye.x && curEye.y == kUnsetCameraEye.y && curEye.z == kUnsetCameraEye.z) {
        mSnapTuning = true;
        Update(deltaTime, viewer);
    }

    cSPGameDataUFO* ufo = GetUFOSimulator()->GetPlayerInventory();
    if (!ufo->mbDestroyed)
        ufo->mSpatial.GetPosition();

    float seconds = (float)deltaTime * 0.001f;

    float zoom;
    if (mPullOutRight != 0.0f)
        zoom = mPullOutRight;
    else
        zoom = GetDefaultPullOut();
    if (fabsf(zoom) > 1.5258789e-05f) {
        mPullOut = Clamp(mPullOut - gOrbitCamZoomRate * zoom * seconds, 50.0f, 500.0f);
        mZooming = true;
    }
    float one = 1.0f;
    mPullOutRight = 0.0f;

    if (mZooming) {
        float dist = mDistance;
        float want = mPullOut;
        float blend = 0.0f;
        if (fabsf((dist - want) / want) > gPlanetCamTuningTolerance) {
            float v = gPlanetCamTuningInRate * seconds + mTuningBlend;
            blend = Min(v, one);
        }
        mTuningBlend = blend;
        if (blend > 0.0f) {
            float a = Min(gPlanetCamTuningLerpRate * blend * seconds, one);
            mDistance = (want - dist) * a + dist;
        } else {
            mZooming = false;
        }
    }

    Vector3 lookAt = mLookAt;
    float inv = 1.0f / sqrtf(lookAt.x * lookAt.x + lookAt.z * lookAt.z + lookAt.y * lookAt.y + 1e-08f);
    Vector3 up;
    up.x = inv * lookAt.x;
    up.y = inv * lookAt.y;
    up.z = inv * lookAt.z;

    // Yaw: rotate the eye direction about the up axis.
    if (mPullOutUp != 0.0f) {
        float halfYaw = mPullOutUp * 0.5f;
        float s = sinf(halfYaw);
        Quaternion q;
        q.x = s * up.x;
        q.y = s * up.y;
        q.z = s * up.z;
        q.w = cosf(halfYaw);
        float qInv = 1.0f / sqrtf(q.w * q.w + q.z * q.z + q.y * q.y + q.x * q.x);
        q.x = qInv * q.x;
        q.y = qInv * q.y;
        q.z = qInv * q.z;
        q.w = qInv * q.w;
        Vector3 tmp;
        const Vector3* r = QuaternionRotate(&tmp, &mEyeDirection, &q);
        mEyeDirection.x = r->x;
        mEyeDirection.y = r->y;
        mEyeDirection.z = r->z;
        mPullOutUp = 0.0f;
    }

    // Eye behind the look-at point, then pitched about the horizontal axis.
    float back = mDistance * -1.0f;
    Vector3 eye;
    eye.x = back * mEyeDirection.x + lookAt.x;
    eye.y = mEyeDirection.y * back + lookAt.y;
    eye.z = mEyeDirection.z * back + lookAt.z;
    Vector3 axis;
    axis.x = eye.z * lookAt.y - eye.y * lookAt.z;
    axis.y = eye.x * lookAt.z - eye.z * lookAt.x;
    axis.z = eye.y * lookAt.x - eye.x * lookAt.y;
    float axisInv = 1.0f / sqrtf(axis.z * axis.z + axis.y * axis.y + axis.x * axis.x);
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
    float qInv = 1.0f / sqrtf(pitchQ.w * pitchQ.w + pitchQ.z * pitchQ.z + pitchQ.y * pitchQ.y + pitchQ.x * pitchQ.x);
    pitchQ.x = qInv * pitchQ.x;
    pitchQ.y = qInv * pitchQ.y;
    pitchQ.z = qInv * pitchQ.z;
    pitchQ.w = qInv * pitchQ.w;
    Vector3 toEye;
    toEye.x = eye.x - lookAt.x;
    toEye.y = eye.y - lookAt.y;
    toEye.z = eye.z - lookAt.z;
    Vector3 tmp;
    const Vector3* re = QuaternionRotate(&tmp, &toEye, &pitchQ);
    eye.x = re->x + lookAt.x;
    eye.y = re->y + lookAt.y;
    eye.z = re->z + lookAt.z;

    Vector3 offset;
    offset.x = eye.x - lookAt.x;
    offset.y = eye.y - lookAt.y;
    offset.z = eye.z - lookAt.z;
    float offInv = 1.0f / sqrtf(offset.z * offset.z + offset.y * offset.y + offset.x * offset.x + 1e-08f);
    Vector3 offDir;
    offDir.x = offInv * offset.x;
    offDir.y = offInv * offset.y;
    offDir.z = offInv * offset.z;
    Vector3 finalEye = eye;

    if (mOrbitFlags & 1) {
        // Keep the view between 92 and 178 degrees away from the eye direction.
        float c = mEyeDirection.z * offDir.z + mEyeDirection.y * offDir.y + offDir.x * mEyeDirection.x;
        float angle = acosf(Clamp(c, -1.0f, 1.0f));
        float orbit = Clamp(mOrbitAngle, 1.6057029f - angle, 3.1066861f - angle);
        Vector3 ax;
        ax.x = eye.z * lookAt.y - eye.y * lookAt.z;
        ax.y = eye.x * lookAt.z - eye.z * lookAt.x;
        ax.z = eye.y * lookAt.x - eye.x * lookAt.y;
        mOrbitAngle = orbit;
        float axInv = 1.0f / sqrtf(ax.z * ax.z + ax.y * ax.y + ax.x * ax.x);
        float half = orbit * 0.5f;
        float so = sinf(half);
        Quaternion oq;
        oq.x = so * (axInv * ax.x);
        oq.y = so * (axInv * ax.y);
        oq.z = so * (axInv * ax.z);
        oq.w = cosf(half);
        float oInv = 1.0f / sqrtf(oq.w * oq.w + oq.z * oq.z + oq.y * oq.y + oq.x * oq.x);
        oq.x = oInv * oq.x;
        oq.y = oInv * oq.y;
        oq.z = oInv * oq.z;
        oq.w = oInv * oq.w;
        const Vector3* ro = QuaternionRotate(&tmp, &offset, &oq);
        finalEye.x = lookAt.x + ro->x;
        finalEye.y = ro->y + lookAt.y;
        finalEye.z = ro->z + lookAt.z;
    }

    float eyeDist = sqrtf(finalEye.x * finalEye.x + finalEye.y * finalEye.y + finalEye.z * finalEye.z);
    if (eyeDist < PlanetModel()->GetRadius() + 200.0f) {
        cCameraLocation loc(viewer);
        Vector3 d;
        d.x = lookAt.x - finalEye.x;
        d.y = lookAt.y - finalEye.y;
        d.z = lookAt.z - finalEye.z;
        loc.mPosition = finalEye;
        float dInv = 1.0f / sqrtf(d.z * d.z + d.y * d.y + d.x * d.x);
        d.x = dInv * d.x;
        d.y = d.y * dInv;
        d.z = d.z * dInv;
        Vector3 right;
        right.x = d.y * up.z - d.z * up.y;
        right.y = d.z * up.x - d.x * up.z;
        right.z = d.x * up.y - d.y * up.x;
        loc.mDirection = d;
        float rInv = 1.0f / sqrtf(right.z * right.z + right.y * right.y + right.x * right.x);
        right.x = rInv * right.x;
        right.y = right.y * rInv;
        right.z = right.z * rInv;
        Vector3 u;
        u.x = right.y * d.z - right.z * d.y;
        u.y = right.z * d.x - right.x * d.z;
        u.z = right.x * d.y - right.y * d.x;
        loc.mRight = right;
        float uInv = 1.0f / sqrtf(u.z * u.z + u.y * u.y + u.x * u.x);
        u.x = uInv * u.x;
        u.y = u.y * uInv;
        u.z = u.z * uInv;
        loc.mUp = u;
        loc.mLookAt = lookAt;
        float clearance = 0.0f;
        if (WaterClearance(&loc, &clearance)) {
            ApplyWaterClearance(&loc, clearance);
            loc.Commit(1);
            finalEye = loc.mPosition;
            lookAt = loc.mLookAt;
        }
    }

    Vector3 facing;
    facing.x = lookAt.x - finalEye.x;
    facing.y = lookAt.y - finalEye.y;
    facing.z = lookAt.z - finalEye.z;
    Matrix3 frame;
    Quaternion qtmp;
    const Quaternion* fq = QuaternionFromMatrix33(&qtmp, Matrix3FromFacingAndUp(&frame, &facing, &up), 0.0f);
    Quaternion orientation = *fq;
    Vector3 camPos = finalEye;

    Matrix3 rot;
    Matrix44 m(*Matrix3FromQuaternion(&rot, &orientation));
    Matrix44 cameraToWorld = m;
    cameraToWorld.m[3][0] = camPos.x;
    cameraToWorld.m[3][1] = camPos.y;
    cameraToWorld.m[3][2] = camPos.z;

    curEye = finalEye;
    mLookAt = lookAt;

    viewer->SetNearClip(2.0f);
    viewer->SetFarClip(3000.0f);
    viewer->SetViewAngle(mFOV);
    viewer->SetCameraToWorld(&cameraToWorld);

    UpdateEffects();

    Vector3 listener;
    ListenerFromPosition(&listener, &curEye);
    if (AudioListener())
        AudioListener()->SetPosition(listener.y, listener.z, listener.x * 0.5f);
}
