// Slice s00d2aec0: SP::cCreatureCamera::Update(unsigned ticks, ICameraHelper* helper)  (retail layout, raw offsets)
// Frame: exponential-decay interpolation of the anchor/orientation/theta/pitch/distance targets, theta wrap
// (+-kWrap), planet-height effect hook, anchor-vector and orientation easing toward their targets, then the
// camera-to-world matrix and the helper (projection owner) updates.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include <math.h>
#include "types.h"

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
template<class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct cSPVector3 : Vector3 {
    cSPVector3() {}
    cSPVector3(const Vector3& v) : Vector3(v) {}
};
struct cSPQuaternion {
    float x, y, z, w;
    cSPQuaternion() {}
    cSPQuaternion(const cSPQuaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
};

extern float kWrap;   // 0x0169df68

namespace SP {
cSPVector3 normalized_safe(const cSPVector3& v);                                         // 0x00449c20
cSPVector3 RotateTowards(const cSPVector3& from, const cSPVector3& to, float t);        // 0x00b0fd00
cSPQuaternion SlerpWrap(const cSPQuaternion& a, const cSPQuaternion& b, float t);        // 0x005b26f0
void* GetCurrentGameMode();                                                              // 0x00b5b800
}
bool FUN_00809970();                                                                     // 0x00809970
bool FUN_00d21ca0(const Vector3& a, const Vector3& b, float tolerance);                  // 0x00d21ca0
float VectorLength(const Vector3* v);                                                    // 0x0040ae50
void ApplyStateFromProperty(void* obj, float h);                                         // 0x006f32e0
extern char g_Mode_1654c01;

struct ICameraHelper {
    float GetFovBase();                         // 0x7c40a0
    float GetFovAspect();                       // 0x7c40e0
    void SetViewMatrix(void* pMatrix);          // 0x7c4d00
    void SetNearClip(float f);                  // 0x7c4ba0
    void SetFarClip(float f);                   // 0x7c4bc0
};
struct cCreatureModeStrategy {
    static cCreatureModeStrategy* Instance();   // 0x00d38840
    bool FUN_00d38880();
};
struct IPlanetTerrain {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual float* GetRadiusInfo();             // +0x0c: floats at +0x34, +0x38, +0x3c
};
struct cPlanetModel {
    char pad[0x24];
    IPlanetTerrain* mpTerrain;                  // +0x24
};
cPlanetModel* PlanetModel();                    // 0x00b3d350

namespace SP {
class cCreatureCamera {
public:
    void Update(unsigned ticks, ICameraHelper* pHelper);
    void SetTransform(float dt);                // 0x00d2a980
    void CalculateCameraToWorldMatrix();        // 0x00d26c90
    void FUN_00d23320();                        // 0x00d23320
    void UpdateAvatarAlpha();                   // 0x00d25e10
    void PrintDebug(ICameraHelper* pHelper);    // 0x00d2a520

    char pad0[0xf8];
    /* 0f8 */ float mBoundMaxY;
    char pad0fc[0x180 - 0xfc];
    /* 180 */ cSPVector3 mAltPos;
    /* 18c */ float mDesiredTheta;
    /* 190 */ float mDesiredPitch;
    /* 194 */ float mDesiredDistance;
    /* 198 */ float mTargetTheta;
    char pad19c[0x1ac - 0x19c];
    /* 1ac */ cSPVector3 mVecB;
    /* 1b8 */ cSPQuaternion mQuatR;
    /* 1c8 */ cSPVector3 mVecA;
    /* 1d4 */ cSPQuaternion mQuatQ;
    char pad1e4[0x204 - 0x1e4];
    /* 204 */ float mMouseSensitivityY;
    char pad208[0x220 - 0x208];
    /* 220 */ float mInitialDistance;
    /* 224 */ float mInitialRotation;
    /* 228 */ float mTimeNear;
    /* 22c */ float mTimeFar;
    /* 230 */ float mTimeAnchor;
    /* 234 */ float mTimeOrientation;
    /* 238 */ float mTimeTheta;
    char pad23c[0x258 - 0x23c];
    /* 258 */ float mFovX;
    /* 25c */ float mFovY;
    /* 260 */ float mCameraToWorld[10];
    char pad288[0x308 - 0x288];
    /* 308 */ void* mpStateObj;
};

static inline float Decay(float dt, float time)
{
    return (float)exp((double)(dt / time) * (double)-0.30103f);
}

// @ 0x00d2aec0
void cCreatureCamera::Update(unsigned ticks, ICameraHelper* pHelper)
{
    if (FUN_00809970()) {
        if (GetCurrentGameMode() != &g_Mode_1654c01)
            return;
        if (!cCreatureModeStrategy::Instance()->FUN_00d38880())
            return;
    }
    float dt = (float)ticks * 0.001f;
    float a = pHelper->GetFovBase();
    float b = pHelper->GetFovAspect();
    mFovX = b * a * 0.017453292f;
    mFovY = pHelper->GetFovBase() * 0.017453292f;
    SetTransform(dt);
    cPlanetModel* pPlanet = PlanetModel();

    float aNear = 1.0f - Decay(dt, mTimeNear);
    float aFar = 1.0f - Decay(dt, mTimeFar);
    float aAnchor = 1.0f - Decay(dt, mTimeAnchor);
    mDesiredTheta = mDesiredTheta + (mAltPos.x - mDesiredTheta) * aAnchor;
    float aOri = 1.0f - Decay(dt, mTimeOrientation);
    float pitch = mDesiredPitch + (mAltPos.y - mDesiredPitch) * aOri;
    mDesiredPitch = pitch;
    mTargetTheta = pitch;
    float aTheta = 1.0f - Decay(dt, mTimeTheta);
    mDesiredDistance = mDesiredDistance + (mAltPos.z - mDesiredDistance) * aTheta;

    // wrap the three angles into +-kWrap
    float wrap = kWrap;
    if (Min(Min(mDesiredTheta, mAltPos.x), mBoundMaxY) > wrap) {
        mDesiredTheta = mDesiredTheta - wrap;
        mAltPos.x = mAltPos.x - wrap;
        mBoundMaxY = mBoundMaxY - wrap;
    } else if (-wrap > Max(Max(mDesiredTheta, mAltPos.x), mBoundMaxY)) {
        mDesiredTheta = mDesiredTheta + wrap;
        mAltPos.x = mAltPos.x + wrap;
        mBoundMaxY = wrap + mBoundMaxY;
    }

    if (pPlanet && pPlanet->mpTerrain) {
        float len = sqrtf((mCameraToWorld[1] * mCameraToWorld[1] + mCameraToWorld[2] * mCameraToWorld[2]) + mCameraToWorld[3] * mCameraToWorld[3]);
        float* info = pPlanet->mpTerrain->GetRadiusInfo();
        ApplyStateFromProperty(mpStateObj, len - (info[0x3c / 4] * info[0x38 / 4] + info[0x34 / 4]));

        if (mVecA.x * mVecA.x + mVecA.y * mVecA.y + mVecA.z * mVecA.z <= 1.5258789e-05f ||
            mVecB.x * mVecB.x + mVecB.y * mVecB.y + mVecB.z * mVecB.z <= 1.5258789e-05f) {
            mVecA = mVecB;
        } else {
            cSPVector3 nA = normalized_safe(mVecA);
            cSPVector3 nB = normalized_safe(mVecB);
            if (FUN_00d21ca0(nA, nB, 1.5258789e-05f)) {
                mVecA = mVecB;
            } else {
                float t = Clamp(aNear, 0.0f, 1.0f);
                cSPVector3 r = RotateTowards(cSPVector3(nA), nB, t);
                float la = VectorLength(&mVecA);
                float lb = VectorLength(&mVecB);
                float s = (lb - la) * aNear + la;
                mVecA.x = r.x * s;
                mVecA.y = r.y * s;
                mVecA.z = r.z * s;
            }
        }

        float dx = mVecA.x - mVecB.x;
        float dy = mVecA.y - mVecB.y;
        float dz = mVecA.z - mVecB.z;
        if (mMouseSensitivityY < sqrtf((dz * dz + dy * dy) + dx * dx)) {
            Vector3 d(mVecA.x - mVecB.x, mVecA.y - mVecB.y, mVecA.z - mVecB.z);
            cSPVector3 n = normalized_safe(d);
            mVecA.x = mMouseSensitivityY * n.x + mVecB.x;
            mVecA.y = mVecB.y + n.y * mMouseSensitivityY;
            mVecA.z = mVecB.z + n.z * mMouseSensitivityY;
        }

        float d0 = mQuatQ.x - mQuatR.x;
        if (d0 < 0.0f) d0 = -d0;
        bool same = false;
        if (d0 <= 1.5258789e-05f) {
            float d1 = mQuatQ.y - mQuatR.y;
            if (d1 < 0.0f) d1 = -d1;
            if (d1 <= 1.5258789e-05f) {
                float d2 = mQuatQ.z - mQuatR.z;
                if (d2 < 0.0f) d2 = -d2;
                if (d2 <= 1.5258789e-05f) {
                    float d3 = mQuatQ.w - mQuatR.w;
                    if (d3 < 0.0f) d3 = -d3;
                    if (d3 <= 1.5258789e-05f)
                        same = true;
                }
            }
        }
        if (same) {
            mQuatQ.x = mQuatR.x;
            mQuatQ.y = mQuatR.y;
            mQuatQ.z = mQuatR.z;
            mQuatQ.w = mQuatR.w;
        } else {
            mQuatQ = SlerpWrap(cSPQuaternion(mQuatQ), mQuatR, Clamp(aFar, 0.0f, 1.0f));
        }
    }

    CalculateCameraToWorldMatrix();
    FUN_00d23320();
    if (GetCurrentGameMode() == &g_Mode_1654c01)
        UpdateAvatarAlpha();
    pHelper->SetViewMatrix(&mCameraToWorld[0]);
    pHelper->SetNearClip(mInitialDistance);
    pHelper->SetFarClip(mInitialRotation);
    PrintDebug(pHelper);
}

}  // namespace SP
