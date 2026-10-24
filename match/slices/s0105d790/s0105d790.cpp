// Slice s0105d790: SP::cUFOLocomotion::CollideWithObject (0x0105dc60), __thiscall ret 8.
// The UFO is treated as a capsule-like body (radius from GetRadius, half height / half width from
// its bounding box) and pushed out of a query object described by a segment (+0x38 vector extended
// by +0x4c) with radii at +0x44 / +0x48.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (same module as s01060150)

#include "types.h"

#pragma pack(push, 8)

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
#pragma intrinsic(sqrt, fabs, sin, cos)
inline float sqrtf(float x) { return (float)sqrt((double)x); }
inline float fabsf(float x) { return (float)fabs((double)x); }
inline float sinf(float x) { return (float)sin((double)x); }
inline float cosf(float x) { return (float)cos((double)x); }

struct RawVec { unsigned int x, y, z; };      // integer-register copy of a vector

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    Vector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 operator*(float f) const { return Vector3(x * f, y * f, z * f); }
    float Dot(const Vector3& b) const { return x * b.x + y * b.y + z * b.z; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    Vector3 Normalized() const { float inv = 1.0f / sqrtf(x * x + y * y + z * z); return Vector3(x * inv, y * inv, z * inv); }
};

namespace SP {

struct cBoundingBox {
    Vector3 mMin;
    Vector3 mMax;
};

// A local-to-world transform.  Only the pieces the retail code touches are named:
// +0x00 flags (bit 1 = the linear part must be applied), +0x04 translation,
// +0x10 uniform scale, +0x14 the 3x3 matrix (column 0 then column 1 then column 2).
struct Matrix3 {
    float m[9];
    void Assign(const float* pSource);              // 0x0041cb40 (ret 4)
};

struct cSPTransform {
    uint32_t mFlags;                    // +0x00
    Vector3  mTranslation;              // +0x04
    float    mScale;                    // +0x10
    Matrix3  mMatrix;                   // +0x14
    void Invert();                      // 0x0040efa0
};

extern const float kIdentityMatrix[9];                      // 0x016e216c
extern const Vector3 kSteerTranslation;                     // 0x016e2114

class cSpatialObject {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28();
    virtual const Vector3* GetAnchor();                              // +0x2c
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4c();
    virtual void _v50(); virtual void _v54(); virtual void _v58(); virtual void _v5c();
    virtual void _v60(); virtual void _v64();
    virtual const cBoundingBox* GetBoundingBox();                    // +0x68
    void LocalToWorldTransform(cSPTransform* pOut);                  // 0x00c897e0
};

// Objects returned by the spatial query.
struct cQueryObject {
    uint32_t pad00[0x38 / 4];
    Vector3 mSegment;                           // +0x38
    float mfRadiusA;                            // +0x44
    float mfRadiusB;                            // +0x48
    float mfExtend;                             // +0x4c
    uint32_t pad50[(0x88 - 0x50) / 4];
    int mnPushMode;                             // +0x88
};

// A steered body.  The UFO and the other steered objects share this prefix (position, velocity,
// aim quaternion, up vector), so both go through the same ApplyPush / KeepInsideObject helpers.
struct cSteered {
    uint32_t   pad00[0x34 / 4];
    cSpatialObject mSpatial;                // +0x34
    uint32_t   pad38[(0x718 - 0x38) / 4];
    Vector3    mPos;                        // +0x718
    Vector3    mVel;                        // +0x724
    float      mQuat[4];                    // +0x730
    Vector3    mUp;                         // +0x740
    uint8_t    pad74c[3];
    uint8_t    mbAimValid;                  // +0x74c
    float GetRadius();                      // 0x00c3be10
    void SetUp(const Vector3* pUp);         // 0x00c381e0
};

class cSpaceToolUFO : public cSteered {
public:
    void QueueMove(int mode, const Vector3* pVec);                   // 0x00c3db50
};

float PointSegmentDistanceKind(const Vector3* p, const Vector3* a, const Vector3* b, int* pKind);  // 0x00698ca0
float PointSegmentDistance(const Vector3* p, const Vector3* a, const Vector3* b);                  // 0x00698b30
Vector3* normalized_safe(Vector3* out, const Vector3* v);                                           // 0x00449c20
bool RayBoxHit(const Vector3* pFar, const Vector3* pDir, const float* pBox, float* pT);             // 0x00698880
extern const float kMinSpeed;                                                                       // 0x015b8df8

class cUFOLocomotion {
public:
    void ApplyPush(cSteered* pBody, const Vector3& push, const Vector3& dir, int reason); // 0x0105c9d0
    void CollideWithObject(cSpaceToolUFO* pUFO, cQueryObject* pObject);                      // 0x0105dc60
    void KeepInsideObject(cSteered* pSteered, cSpatialObject* pObject, int reason);         // 0x0105d790
};

// ---- Support objects for the aim update (0x0105e290) ----

struct Quaternion { float x, y, z, w; };

Quaternion* QuaternionFromFacingAndUp(Quaternion* pOut, const Vector3* pFacing,
                                      const Vector3* pUp);                     // 0x0069b600
Vector3* FUN_0059aed0(Vector3* pOut, const Vector3* pPos, const Vector3* pAxis); // 0x0059aed0
void* FUN_01021230();                                                          // 0x01021230
int   cStar_GetType(void* pStar);                                              // 0x00c8b550

// App() -> feature (+0x50) -> subsystem (+0x38) -> lookup (+0x0c).
class cSubsystem {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08();
    virtual void* FindProperty(uint32_t id);                                   // +0x0c
};
class cAppFeature {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34();
    virtual cSubsystem* GetSubsystem();                                        // +0x38
};
class cApp {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4c();
    virtual cAppFeature* GetFeature();                                         // +0x50
};
cApp* App();                                                                   // 0x0067dd10

struct cPropertyValue {
    uint32_t pad00[0xbc / 4];
    float    mfValue;                                                          // +0xbc
};

// The wrapper whose +0x14 points at the steered body's spatial member (body + 0x34).
struct cBodyRef {
    uint32_t pad00[0x14 / 4];
    char*    mpBody;                                                           // +0x14
};

extern const Vector3 kAxis;              // 0x015b8da8  (fallback position)
extern const Vector3 kUnit;              // 0x015b8db4  (reference unit vector)
extern const float kSpinMin;             // 0x015b8dfc
extern const float kSpinMax;             // 0x015b8e00
extern const float kUpBlend;             // 0x015b8e04
extern const float kFalloff;             // 0x015b8e08
extern const float kCapMax;              // 0x015b8e0c
extern const float kCapMin;              // 0x015b8e10
extern const float kMagnitudeScale;      // 0x013f9428
extern const float kHalf;                // 0x01471064
extern const float kNegOne;              // 0x013eb1bc
extern const float kMinLength;           // 0x0149bfc0 = 1.5258789e-05

// @ 0x0105d790
void cUFOLocomotion::KeepInsideObject(cSteered* pSteered, cSpatialObject* pObject, int reason)
{
    const cBoundingBox* pBox = pObject->GetBoundingBox();
    Vector3 vMin = pBox->mMin;
    Vector3 vMax = pBox->mMax;
    float radius = pSteered->GetRadius();
    vMin.x -= radius; vMin.y -= radius; vMin.z -= radius;
    vMax.x += radius; vMax.y += radius; vMax.z += radius;

    cSPTransform xform;
    xform.mFlags = 0;
    xform.mTranslation = kSteerTranslation;
    xform.mScale = 1.0f;
    xform.mMatrix.Assign(kIdentityMatrix);

    pObject->LocalToWorldTransform(&xform);
    xform.Invert();

    const float* m = xform.mMatrix.m;
    const Vector3& p = pSteered->mPos;
    Vector3 local = p;
    if (xform.mFlags & 2) {
        local = Vector3(m[0] * p.x + m[3] * p.y + m[6] * p.z,
                        m[1] * p.x + m[4] * p.y + m[7] * p.z,
                        m[2] * p.x + m[5] * p.y + m[8] * p.z);
    }
    Vector3 world(xform.mTranslation.x + xform.mScale * local.x,
                  xform.mTranslation.y + xform.mScale * local.y,
                  xform.mTranslation.z + xform.mScale * local.z);

    if (world.x < vMin.x || world.x > vMax.x ||
        world.y < vMin.y || world.y > vMax.y ||
        world.z < vMin.z || world.z > vMax.z)
        return;

    const Vector3* pAnchor = pObject->GetAnchor();
    Vector3 v(p.x - pAnchor->x, p.y - pAnchor->y, p.z - pAnchor->z);
    float inv = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + 1e-8f);
    Vector3 dir(v.x * inv, v.y * inv, v.z * inv);

    Vector3 probeDir = dir;
    if (xform.mFlags & 2) {
        probeDir = Vector3(m[0] * dir.x + m[3] * dir.y + m[6] * dir.z,
                           m[1] * dir.x + m[4] * dir.y + m[7] * dir.z,
                           m[2] * dir.x + m[5] * dir.y + m[8] * dir.z);
    }

    Vector3 span(vMax.x - vMin.x, vMax.y - vMin.y, vMax.z - vMin.z);
    float extent = sqrtf(span.x * span.x + span.y * span.y + span.z * span.z);

    Vector3 probe(world.x + probeDir.x * extent,
                  world.y + probeDir.y * extent,
                  world.z + probeDir.z * extent);
    Vector3 back(-probeDir.x, -probeDir.y, -probeDir.z);

    float t = 0.0f;
    Vector3 push = dir;
    if (RayBoxHit(&probe, &back, (const float*)&vMin, &t)) {
        float remain = extent - t;
        push = Vector3(dir.x * remain, dir.y * remain, dir.z * remain);
    }
    ApplyPush(pSteered, push, dir, reason);
}

// @ 0x0105e290
void __stdcall FUN_0105e290(void* pWrapper, int nMagnitude)
{
    float mag = (float)(uint32_t)nMagnitude;
    float scaled = mag * kMagnitudeScale;

    cBodyRef* pRef = (cBodyRef*)pWrapper;
    cSteered* p = (cSteered*)(pRef->mpBody - 0x34);

    cAppFeature* pFeature = App()->GetFeature();
    cSubsystem* pSub = pFeature->GetSubsystem();
    if (!pSub)
        return;
    cPropertyValue* pProp = (cPropertyValue*)pSub->FindProperty(0x303154cc);
    if (!pProp)
        return;
    float cap = pProp->mfValue;

    Vector3 pos = p->mPos;
    float norm = sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
    if (norm < kMinLength)
        pos = kAxis;

    float invCap = 1.0f / kCapMax;
    float blend = ((kCapMax - kCapMin) * cap + kCapMin) - norm;
    float f1 = scaled / ((fabsf(blend) * invCap) * kFalloff);
    float c1 = (1.0f <= f1) ? 1.0f : f1;
    float newDist = blend * c1 + norm;

    float inv = 1.0f / sqrtf(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + 1e-8f);
    pos = Vector3(pos.x * inv * newDist, pos.y * inv * newDist, pos.z * inv * newDist);

    float f2 = invCap * newDist;
    float c2 = (1.0f <= f2) ? 1.0f : f2;

    Vector3 up = p->mUp;
    float t = kUpBlend * c2;
    Vector3 newUp((kUnit.x * t - up.x) * c1 + up.x,
                  (kUnit.y * t - up.y) * c1 + up.y,
                  (kUnit.z * t - up.z) * c1 + up.z);
    p->SetUp(&newUp);

    float sign = (cStar_GetType(FUN_01021230()) == 3) ? kNegOne : 1.0f;
    float angle = (((1.0f - c2) * (kSpinMin * kSpinMax - kSpinMax) + kSpinMax) * mag * sign) * kHalf;

    float s = sinf(angle);
    float c = cosf(angle);
    Vector3 axisRot(s * kUnit.x, s * kUnit.y, s * kUnit.z);

    Vector3 outPos;
    FUN_0059aed0(&outPos, &pos, &axisRot);
    p->mPos = outPos;
    (void)c;

    const Vector3& pp = p->mPos;
    float cx = pp.y * kUnit.z - pp.z * kUnit.y;
    float cy = pp.z * kUnit.x - pp.x * kUnit.z;
    float cz = pp.x * kUnit.y - pp.y * kUnit.x;
    float invCross = 1.0f / sqrtf(cx * cx + cy * cy + cz * cz);
    Vector3 facing(invCross * cx * sign, invCross * cy * sign, invCross * cz * sign);

    Quaternion q;
    QuaternionFromFacingAndUp(&q, &facing, &kUnit);
    p->mQuat[0] = q.x;
    p->mQuat[1] = q.y;
    p->mQuat[2] = q.z;
    p->mQuat[3] = q.w;
    p->mbAimValid = 1;
}

// @ 0x0105dc60
void cUFOLocomotion::CollideWithObject(cSpaceToolUFO* pUFO, cQueryObject* pObject)
{
    Vector3& pos = pUFO->mPos;
    Vector3 dir = pos.Normalized();
    Vector3 t = dir;
    float ufoRadius = pUFO->GetRadius();

    const cBoundingBox* pBox = pUFO->mSpatial.GetBoundingBox();
    Vector3 v = pBox->mMax - pBox->mMin;
    float halfHeight = v.z * 0.5f;
    const float* pWide = &v.y;
    if (!(v.y > v.x))
        pWide = &v.x;
    float halfWidth = *pWide * 0.5f;

    const Vector3& seg = pObject->mSegment;
    int kind = 1;
    float extent = seg.Length() + pObject->mfExtend;
    Vector3 end = seg.Normalized() * extent;
    Vector3 mid = (seg + end) * 0.5f;
    float reachA = pObject->mfRadiusB + ufoRadius;
    float dist = PointSegmentDistanceKind(&pos, &mid, &end, &kind);
    float depth;

    if (reachA > dist) {
        if (kind == 2) {
            if (!(halfHeight > dist))
                return;
            v = pos - end;
            depth = halfHeight - dist;
            *(RawVec*)&dir = *(const RawVec*)normalized_safe(&t, &v);
        } else {
            float reachB = pObject->mfRadiusB + halfWidth;
            if (!(reachB > dist))
                return;
            float d = (end.x - pos.x) * dir.x + (end.z - pos.z) * dir.z + (end.y - pos.y) * dir.y + halfHeight;
            if (d > 0.0f && d < reachB - dist) {
                *(RawVec*)&dir = *(const RawVec*)&t;
                depth = d;
            } else {
                depth = reachB - dist;
                v = pos - mid;
                float k = v.x * dir.x + v.z * dir.z + v.y * dir.y;
                v = Vector3(v.x - k * dir.x, v.y - dir.y * k, v.z - dir.z * k);
                *(RawVec*)&dir = *(const RawVec*)normalized_safe(&t, &v);
            }
        }
    } else {
        float reachC = pObject->mfRadiusA + halfWidth;
        float d2 = PointSegmentDistance(&pos, &seg, &mid);
        if (!(reachC > d2))
            return;
        v = pos - seg;
        depth = reachC - d2;
        float k = v.x * dir.x + v.z * dir.z + v.y * dir.y;
        Vector3 w(v.x - k * dir.x, v.y - dir.y * k, v.z - dir.z * k);
        float inv = 1.0f / sqrtf(w.x * w.x + (w.y * w.y + w.z * w.z) + 1e-8f);
        t = w * inv;
        *(RawVec*)&dir = *(const RawVec*)&t;
    }

    if (pObject->mnPushMode == 0) {
        if (pUFO->mVel.Length() > kMinSpeed) {
            t = dir * depth;
            v = t;
            const Vector3* n = normalized_safe(&dir, &v);
            v = (t + pos) - *n * ufoRadius;
            pUFO->QueueMove(2, &v);
        }
    } else {
        v = dir * depth;
        ApplyPush(pUFO, v, dir, 3);
    }
}

}  // namespace SP

#pragma pack(pop)
