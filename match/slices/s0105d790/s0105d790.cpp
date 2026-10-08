// Slice s0105d790: SP::cUFOLocomotion::CollideWithObject (0x0105dc60), __thiscall ret 8.
// The UFO is treated as a capsule-like body (radius from GetRadius, half height / half width from
// its bounding box) and pushed out of a query object described by a segment (+0x38 vector extended
// by +0x4c) with radii at +0x44 / +0x48.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (same module as s01060150)

#include "types.h"

#pragma pack(push, 8)

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline float sqrtf(float x) { return (float)sqrt((double)x); }

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

class cSpatialObject {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2c();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3c();
    virtual void _v40(); virtual void _v44(); virtual void _v48(); virtual void _v4c();
    virtual void _v50(); virtual void _v54(); virtual void _v58(); virtual void _v5c();
    virtual void _v60(); virtual void _v64();
    virtual const cBoundingBox* GetBoundingBox();                    // +0x68
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

class cSpaceToolUFO {
public:
    uint32_t pad00[0x34 / 4];
    cSpatialObject mSpatial;                    // +0x34
    uint32_t pad38[(0x718 - 0x38) / 4];
    Vector3 mPosition;                          // +0x718
    Vector3 mVelocity;                          // +0x724
    float GetRadius();                                               // 0x00c3be10
    void QueueMove(int mode, const Vector3* pVec);                   // 0x00c3db50
};

float PointSegmentDistanceKind(const Vector3* p, const Vector3* a, const Vector3* b, int* pKind);  // 0x00698ca0
float PointSegmentDistance(const Vector3* p, const Vector3* a, const Vector3* b);                  // 0x00698b30
Vector3* normalized_safe(Vector3* out, const Vector3* v);                                           // 0x00449c20
extern const float kMinSpeed;                                                                       // 0x015b8df8

class cUFOLocomotion {
public:
    void ApplyPush(cSpaceToolUFO* pUFO, const Vector3& push, const Vector3& dir, int reason);  // 0x0105c9d0
    void CollideWithObject(cSpaceToolUFO* pUFO, cQueryObject* pObject);                      // 0x0105dc60
};

// @ 0x0105dc60
void cUFOLocomotion::CollideWithObject(cSpaceToolUFO* pUFO, cQueryObject* pObject)
{
    Vector3& pos = pUFO->mPosition;
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
        if (pUFO->mVelocity.Length() > kMinSpeed) {
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
