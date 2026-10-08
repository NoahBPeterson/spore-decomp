// Slice s01019090 -- space-stage planet camera controller helpers:
//   0x01019090 SP::cSPSpacePlanetCameraController::UpdateYaw(float seconds)
//   0x01019950 SP::cSPSpacePlanetCameraController::UpdateCameraPitchRotation(float seconds, float pitch,
//                                                                            Vector3* lookAt, Vector3* eye)
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), x87 sqrt / fsin / fcos / _CIacos with SSE
// scalar arithmetic, like the neighbouring 0x0101d130 (Update).
//
// The retail layout does NOT follow the 2008 dev-PDB layout; members are named by retail offset (see
// s0101d130 for the other users of the same fields).
//
// UpdateYaw: keep the camera's eye direction (mEyeDirection, +0x94) tangent to the planet at the UFO's
// position (orthonormalized against the planet normal), re-aim it along the UFO's heading while the UFO
// is moving, apply the yaw rotation input (+0x90) about the planet normal and, when the UFO is flying
// away from the camera (flag bit 1), rotate the eye direction towards the UFO's heading.
// UpdateCameraPitchRotation: lerp the pitch (+0x78) towards the wanted pitch (or clamp it to the angle
// between the eye and the horizon), then rotate the eye around the look-at point about the horizontal
// axis through the look-at point.
#include "types.h"

#include <math.h>

struct Vector3 {
    float x, y, z;
};

struct Quaternion {
    float x, y, z, w;
};

inline Vector3 operator-(const Vector3& a, const Vector3& b) { Vector3 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r; }
inline const float& Min(const float& a, const float& b) { return (b < a) ? b : a; }
inline const float& Max(const float& a, const float& b) { return (a < b) ? b : a; }
// maxss / minss semantics (the second operand wins when either is NaN)
inline float MaxSS(float a, float b) { return (a > b) ? a : b; }
inline float MinSS(float a, float b) { return (a < b) ? a : b; }

// ---- external helpers (cdecl unless noted) ---------------------------------------------
Vector3*    QuaternionRotate(Vector3* out, const Vector3* v, const Quaternion* q);   // 0x0059aed0
Vector3*    RotateTowards(Vector3* out, const Vector3* from, const Vector3* to, float t); // 0x00b0fd00
float       PlanetRadiusAt(const Vector3* p);                                         // 0x00c375d0

extern const Vector3    kUFOForward;       // 0x015b6de8
extern float gPlanetCamSnapDistance;       // 0x016dd410 (added to the planet radius)

namespace SP {

struct cGameTimeManager {
    uint32_t pad0[0x48 / 4];
    uint8_t  mFlags;   // +0x48, bit 0 = paused
};
cGameTimeManager* GameTimeManager();       // 0x00b3d380

struct IGameInputManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual bool IsRotateInputActive(int arg);   // +0x18
};
IGameInputManager* GameInputManager();     // 0x00b3d250

struct cSpatialObject {   // the UFO's spatial base (cSPGameDataUFO + 0x34)
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3*    GetPosition();      // +0x2c
    virtual const Quaternion* GetOrientation();   // +0x30
};

struct cSPGameDataUFO {
    uint32_t pad0[0x34 / 4];
    cSpatialObject mSpatialStorage;                 // +0x34 (used through Spatial())
    float GetMaxGroundSpeed();                      // 0x00c38840
    cSpatialObject* Spatial() { return reinterpret_cast<cSpatialObject*>(reinterpret_cast<char*>(this) + 0x34); }
    template <typename T> T& At(int off) { return *reinterpret_cast<T*>(reinterpret_cast<char*>(this) + off); }
};

struct cSPSimulatorSpaceGame {
    cSPGameDataUFO* GetPlayerInventory();           // 0x00a1ad60
};
cSPSimulatorSpaceGame* GetUFOSimulator();           // 0x00ffbe50

class cSPSpacePlanetCameraController {
public:
    void UpdateYaw(float seconds);                                                       // 0x01019090
    void UpdateCameraPitchRotation(float seconds, float pitch, Vector3* lookAt, Vector3* eye);  // 0x01019950

    // ---- retail layout (offsets verified against 0x0101d130 / 0x01019090 / 0x01019950) ----
    uint32_t pad00[0x78 / 4];
    float    mPitch;                   // +0x78 (camera pitch angle)
    uint32_t pad7c[(0x90 - 0x7c) / 4];
    float    mYawInput;                // +0x90 (yaw rotation input, radians)
    Vector3  mEyeDirection;            // +0x94
    uint32_t padA0[(0xcc - 0xa0) / 4];
    bool     mZooming;                 // +0xcc
    uint8_t  padCD[(0x13c - 0xcd)];
    bool     mApproachFollow;          // +0x13c
    uint8_t  pad13d[(0x198 - 0x13d)];
    uint32_t mFlags;                   // +0x198 (bit 0 = pitch tracking, bit 1 = yaw follow)
};

} // namespace SP

using namespace SP;

// @ 0x01019090
void SP::cSPSpacePlanetCameraController::UpdateYaw(float seconds)
{
    cSPGameDataUFO* ufo = GetUFOSimulator()->GetPlayerInventory();
    cSPGameDataUFO* posUfo = GetUFOSimulator()->GetPlayerInventory();

    const Vector3* pPos;
    if (posUfo->At<bool>(0x74c) && !(GameTimeManager()->mFlags & 1))
        pPos = &posUfo->At<Vector3>(0x750);
    else
        pPos = posUfo->Spatial()->GetPosition();

    // Planet normal at the camera anchor.
    Vector3 p;
    p.x = pPos->x;
    p.y = pPos->y;
    p.z = pPos->z;
    float inv = 1.0f / sqrtf(p.x * p.x + p.y * p.y + p.z * p.z);
    Vector3 n;
    n.x = p.x * inv;
    n.y = p.y * inv;
    n.z = p.z * inv;

    // Keep the eye direction tangent: dir = normalize(p x (eyeDir x n)).
    Vector3& dir = mEyeDirection;
    Vector3 side;
    side.x = n.z * dir.y - n.y * dir.z;
    side.y = dir.z * n.x - n.z * dir.x;
    side.z = n.y * dir.x - dir.y * n.x;
    Vector3 t;
    t.x = side.z * p.y - side.y * p.z;
    t.y = p.z * side.x - side.z * p.x;
    t.z = side.y * p.x - p.y * side.x;
    float tInv = 1.0f / sqrtf(t.x * t.x + t.z * t.z + t.y * t.y);
    t.x = tInv * t.x;
    t.y = t.y * tInv;
    t.z = t.z * tInv;
    dir = t;

    if (!(GameTimeManager()->mFlags & 1) && !(mFlags & 2))
    {
        // Follow the UFO's heading projected onto the tangent plane.
        Vector3 fwd;
        const Vector3* f = QuaternionRotate(&fwd, &kUFOForward, ufo->Spatial()->GetOrientation());
        float d = (f->z * n.z + f->y * n.y) + f->x * n.x;
        Vector3 h;
        h.x = f->x - d * n.x;
        h.y = f->y - n.y * d;
        h.z = f->z - n.z * d;
        float hInv = 1.0f / sqrtf(h.x * h.x + h.z * h.z + h.y * h.y + 1e-08f);
        h.x = hInv * h.x;
        h.y = hInv * h.y;
        h.z = hInv * h.z;
        dir = h;
    }
    else if (!(GameTimeManager()->mFlags & 1) && (mFlags & 2) && (mApproachFollow || ufo->At<bool>(0x74c)))
    {
        mApproachFollow = true;
        Vector3 fwd;
        const Vector3* f = QuaternionRotate(&fwd, &kUFOForward, ufo->Spatial()->GetOrientation());
        float d = (n.z * f->z + n.y * f->y) + f->x * n.x;
        Vector3 h;
        h.x = f->x - d * n.x;
        h.y = f->y - n.y * d;
        h.z = f->z - n.z * d;
        float hInv = 1.0f / sqrtf(h.x * h.x + h.z * h.z + h.y * h.y + 1e-08f);

        float e = (dir.x * n.x + n.y * dir.y) + n.z * dir.z;
        Vector3 w;
        w.x = dir.x - e * n.x;
        w.y = dir.y - n.y * e;
        w.z = dir.z - n.z * e;
        float wInv = 1.0f / sqrtf(w.x * w.x + w.z * w.z + w.y * w.y + 1e-08f);

        float c = (((wInv * w.x) * (hInv * h.x) + (wInv * w.z) * (hInv * h.z)) + (wInv * w.y) * (hInv * h.y));
        float lo = -1.0f;
        float hi = 1.0f;
        c = MinSS(MaxSS(c, lo), hi);
        float angle = (float)acos(c);
        float threshold = (ufo->At<float>(0x604) == 0.0f) ? 0.02f : 0.1f;
        if (fabsf(angle) < threshold)
            mFlags &= ~2u;
    }

    if (mYawInput != 0.0f)
    {
        float half = mYawInput * 0.5f;
        float s = sinf(half);
        Quaternion q;
        q.x = n.x * s;
        q.y = n.y * s;
        q.z = n.z * s;
        float c = cosf(half);
        volatile float cMem = c;
        float qInv = 1.0f / sqrtf(c * c + q.z * q.z + q.x * q.x + q.y * q.y);
        Quaternion qn;
        qn.x = qInv * q.x;
        qn.y = qInv * q.y;
        qn.z = qInv * q.z;
        qn.w = qInv * cMem;
        Vector3 rotated;
        const Vector3* r = QuaternionRotate(&rotated, &dir, &qn);
        dir.x = r->x;
        dir.y = r->y;
        dir.z = r->z;
    }

    // Steer the eye direction towards the UFO when it is moving away from the anchor.
    Vector3 anchorToUfo;
    anchorToUfo.x = pPos->x - ufo->At<float>(0x750);
    anchorToUfo.y = pPos->y - ufo->At<float>(0x754);
    anchorToUfo.z = pPos->z - ufo->At<float>(0x758);
    float dist = sqrtf(anchorToUfo.x * anchorToUfo.x + anchorToUfo.z * anchorToUfo.z + anchorToUfo.y * anchorToUfo.y);
    if (dist > 1.5258789e-05f)
    {
        float invDist = 1.0f / dist;
        Vector3 u;
        u.x = invDist * (ufo->At<float>(0x750) - pPos->x);
        u.y = invDist * (ufo->At<float>(0x754) - pPos->y);
        u.z = invDist * (ufo->At<float>(0x758) - pPos->z);
        float dp = (n.z * u.z + n.y * u.y) + u.x * n.x;
        if (fabsf(dp) < (float)cos(0.8726646192371845))
        {
            Vector3 v;
            v.x = u.x - n.x * dp;
            v.y = u.y - n.y * dp;
            v.z = u.z - n.z * dp;
            float vInv = 1.0f / sqrtf(v.x * v.x + v.z * v.z + v.y * v.y);
            Vector3 target;
            target.x = vInv * v.x;
            target.y = vInv * v.y;
            target.z = vInv * v.z;

            const Vector3& vel = ufo->At<Vector3>(0x724);
            float speed = sqrtf((vel.x * vel.x + vel.y * vel.y) + vel.z * vel.z);
            float one = 1.0f;
            float ratio = speed / ufo->GetMaxGroundSpeed();
            const float& step = Min(ratio, one);
            if (!(0.0f > (dir.z * target.z + dir.y * target.y) + target.x * dir.x) && !ufo->At<bool>(0x608) &&
                sqrtf(pPos->x * pPos->x + pPos->y * pPos->y + pPos->z * pPos->z) < PlanetRadiusAt(pPos) + gPlanetCamSnapDistance)
            {
                Vector3 toward;
                const Vector3* r = RotateTowards(&toward, &dir, &target, step * seconds);
                dir = *r;
            }
        }
    }
}

// Rotate the eye about the lookAt point around cross(lookAt, eye) by `angle` (inlined twice by cl).
static __forceinline void RotateEyeAroundLookAt(float angle, const Vector3* lookAt, Vector3* eye)
{
    Vector3 ax;
    ax.x = lookAt->y * eye->z - lookAt->z * eye->y;
    ax.y = lookAt->z * eye->x - lookAt->x * eye->z;
    ax.z = eye->y * lookAt->x - lookAt->y * eye->x;
    float axInv = 1.0f / sqrtf(ax.z * ax.z + ax.y * ax.y + ax.x * ax.x);
    float half = angle * 0.5f;
    Vector3 an;
    an.x = axInv * ax.x;
    an.y = axInv * ax.y;
    an.z = axInv * ax.z;
    float s = sinf(half);
    Quaternion q;
    q.x = s * an.x;
    q.y = s * an.y;
    q.z = s * an.z;
    float c = cosf(half);
    volatile float cMem = c;    // the original rounds cos() to float before the final multiply
    Vector3 toEye;
    toEye.x = eye->x - lookAt->x;
    toEye.y = eye->y - lookAt->y;
    toEye.z = eye->z - lookAt->z;
    volatile float qInvMem = 1.0f / sqrtf(c * c + q.x * q.x + q.z * q.z + q.y * q.y);
    float qInv = qInvMem;
    Quaternion qn;
    qn.x = qInv * q.x;
    qn.y = qInv * q.y;
    qn.z = qInv * q.z;
    qn.w = qInv * cMem;
    Vector3 rotated;
    const Vector3* r = QuaternionRotate(&rotated, &toEye, &qn);
    Vector3 origin = *lookAt;
    eye->x = r->x + origin.x;
    eye->y = r->y + origin.y;
    eye->z = r->z + origin.z;
}

// @ 0x01019950
void SP::cSPSpacePlanetCameraController::UpdateCameraPitchRotation(float seconds, float pitch, Vector3* lookAt, Vector3* eye)
{
    cSPGameDataUFO* ufo = GetUFOSimulator()->GetPlayerInventory();

    if (mFlags & 1)
    {
        // Pitch tracks the angle between the eye and the horizon; clamp the stored pitch to it.
        Vector3 d = *eye - *lookAt;
        float dInv = 1.0f / sqrtf(d.y * d.y + d.z * d.z + d.x * d.x);
        Vector3 dn;
        dn.x = dInv * d.x;
        dn.y = d.y * dInv;
        dn.z = d.z * dInv;
        float lInv = 1.0f / sqrtf(lookAt->z * lookAt->z + lookAt->y * lookAt->y + lookAt->x * lookAt->x);
        Vector3 ln;
        ln.x = lookAt->x * lInv;
        ln.y = lookAt->y * lInv;
        ln.z = lookAt->z * lInv;
        float dot = (ln.x * dn.x + ln.z * dn.z) + ln.y * dn.y;
        float c = ((((dn.x - ln.x * dot) * -1.0f) * dn.x + ((dn.z - ln.z * dot) * -1.0f) * dn.z) +
                   ((dn.y - ln.y * dot) * -1.0f) * dn.y);
        float lo = -1.0f;
        float hi = 1.0f;
        c = MinSS(MaxSS(c, lo), hi);
        double angle = acos(c);
        float cur = mPitch;
        float minPitch = (float)(1.5882496f - angle);
        float maxPitch = (float)(3.1241393f - angle);
        mPitch = MinSS(MaxSS(cur, minPitch), maxPitch);

        RotateEyeAroundLookAt(mPitch, lookAt, eye);

        if (!ufo->At<bool>(0x74c) && mZooming && !GameInputManager()->IsRotateInputActive(0xcdcdcdcd))
            mFlags &= ~1u;
    }
    else
    {
        float one = 1.0f;
        float t = seconds * 2.0f;
        const float& ratio = (1.0f > t) ? t : one;
        float cur = mPitch;
        mPitch = (pitch - cur) * ratio + cur;

        RotateEyeAroundLookAt(mPitch, lookAt, eye);
    }
}
