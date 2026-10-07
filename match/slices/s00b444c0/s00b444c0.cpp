// Slice s00b444c0 — planet correction for a cLocomotiveObject (3236 bytes).
// Moves/orients a locomotive object onto the planet according to its
// ePlanetCorrection mode (retail +0x1f0), then refreshes its water state.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct Quaternion { float x, y, z, w; };

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
    Vector3 operator-() const { return Vector3(-x, -y, -z); }
    Vector3 Cross(const Vector3& b) const
    {
        return Vector3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
    }
};

struct BoundingBox { Vector3 lower, upper; };
struct Matrix3 { float m[3][3]; };

struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3 mTranslation;
    float mScale;
    Matrix3 mRotation;
    cSPTransform();                                  // 00409930
    void BackTransformPoint(Vector3& p) const;       // 004ff6d0
};

Vector3 Normalize(const Vector3& v);                 // 00436ce0
Vector3 normalized_safe(const Vector3& v);           // 00449c20
float LengthSquared(const Vector3& v);               // 004885d0
float Dot(const Vector3& a, const Vector3& b);       // 00455cc0
Matrix3 MatrixFromAxes(const Vector3& forward, const Vector3& up, const Vector3& right);   // 00afa0c0
Quaternion QuaternionFromMatrix(const Matrix3& m);   // 0046d660
bool IsBoxUnderwater(const Vector3& p, float waterHeight, const BoundingBox& box);        // 00743fb0

template <class T> inline const T& max_(const T& a, const T& b) { return (a < b) ? b : a; }

namespace SP {

class cPlanetModel {
public:
    bool HasWater();                                                          // 00b7ec40
    float GetWaterHeight();                                                   // 00b7e390
    float GetRadiusAt(const Vector3& pos);                                    // 00b7ef70
    Vector3 ProjectToWaterSurface(const Vector3& pos);                        // 00b81630
    Vector3 DirectionToSurfacePosition(const Vector3& pos);                   // 00b815a0
    Quaternion GetUprightOrientation(const Vector3& pos, const Quaternion& q);           // 00b7f1f0
    Quaternion GetPitchedOrientation(const Vector3& pos, const Quaternion& q, float k);  // 00b7f2b0
};
cPlanetModel* PlanetModel();   // 00b3d350

struct cSPLivingUniverse { static void* GetUniverseContext(); };   // 01021080

class cSpatialObject {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();                  // 0x2c
    virtual const Quaternion& GetOrientation();            // 0x30
    virtual float GetScale();                              // 0x34
    virtual void SetPosition(const Vector3& p);            // 0x38
    virtual void SetOrientation(const Quaternion& q);      // 0x3c
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58();
    virtual Vector3 GetDirection();                        // 0x5c
    virtual void v60(); virtual void v64();
    virtual const BoundingBox& GetLocalExtents();          // 0x68
    virtual void v6c(); virtual void v70();
    virtual float GetFootprintRadius();                    // 0x74

    void LocalToWorldTransform(cSPTransform& out);         // 00c897e0

    uint32_t pad04[0x13];
    uint32_t mFlags;          // +0x50
    uint32_t pad54[8];
    bool mbTransformDirty;    // +0x74
    bool mbEnabled;
    bool mbInView;
    bool mbSupported;         // +0x77
};

class cLocomotiveObject : public cSpatialObject {
public:
    const Vector3& GetVelocity();                          // 00d20610
    uint32_t pad78[0x5e];
    int mPlanetCorrection;    // +0x1f0 (ePlanetCorrection)
    uint32_t pad1f4[0x1d];
    bool mbSelfPowered;       // +0x268
};

enum ePlanetCorrection {
    kSnapToGroundUpright = 0,
    kSnapToGroundPitched = 1,
    kWarpFlightPath = 2,
    kGroundCollisionCorrection = 3,
    kNoCorrection = 4,
    kNoCorrectionOrGravity = 5,
    kSnapToWater = 6,
    kSnapToGroundTranslateOnly = 7,
    kSnapToGroundMultiSample = 8,
};

void UpdateWaterState(cLocomotiveObject* obj, bool bUnderwater, const Vector3& pos, const Quaternion& q);   // 00b421b0

} // namespace SP

using namespace SP;

extern bool g_b0167eb74;          // planet-wide mode flag (0x0167eb74)
extern Vector3 g_v0167eb8c;       // probe point in local space (0x0167eb8c)

inline void NoteTransform(const Vector3&, const Quaternion&) {}

void ApplyPlanetCorrection(const Vector3& pos, cLocomotiveObject* obj)
{
    cPlanetModel* planet = PlanetModel();
    float waterHeight;
    int mode;
    if (cSPLivingUniverse::GetUniverseContext() == 0 && planet != 0 && planet->HasWater()) {
        waterHeight = planet->GetWaterHeight();
        mode = obj->mPlanetCorrection;
    } else {
        waterHeight = 0.0f;
        mode = kNoCorrection;
    }

    switch (mode) {
    case kSnapToGroundUpright:
        if (g_b0167eb74) {
            obj->SetPosition(planet->ProjectToWaterSurface(pos));
        } else {
            float radius = planet->GetRadiusAt(pos);
            const BoundingBox& ext = obj->GetLocalExtents();
            float height = waterHeight - (ext.upper.z - ext.lower.z) * 0.55f;
            height = max_(radius, height);
            obj->SetPosition(normalized_safe(pos) * height);
        }
        obj->SetOrientation(planet->GetUprightOrientation(obj->GetPosition(), obj->GetOrientation()));
        break;

    case kSnapToGroundPitched:
        if (g_b0167eb74) {
            obj->SetPosition(planet->ProjectToWaterSurface(pos));
        } else {
            float radius = planet->GetRadiusAt(pos);
            const BoundingBox& ext = obj->GetLocalExtents();
            float height = waterHeight - (ext.upper.z - ext.lower.z) * 0.55f;
            height = max_(radius, height);
            obj->SetPosition(normalized_safe(pos) * height);
        }
        obj->SetOrientation(planet->GetPitchedOrientation(obj->GetPosition(), obj->GetOrientation(), 5.0f));
        break;

    case kWarpFlightPath: {
        Vector3 cur = obj->GetPosition();
        Vector3 dir = Normalize(pos);
        Vector3 curDir = Normalize(cur);
        float len = sqrtf(cur.x * cur.x + cur.y * cur.y + cur.z * cur.z);
        float k = len / (dir.x * curDir.x + dir.y * curDir.y + dir.z * curDir.z) - len;
        obj->SetPosition(pos - dir * k);
        break;
    }

    case kGroundCollisionCorrection: {
        float distSq = pos.x * pos.x + pos.y * pos.y + pos.z * pos.z;
        float radius = planet->GetRadiusAt(pos);
        if (radius * radius > distSq || (g_b0167eb74 && waterHeight * waterHeight > distSq)) {
            if (Dot(pos, Normalize(obj->GetVelocity())) < 0.0f) {
                Vector3 newPos;
                if (g_b0167eb74)
                    newPos = normalized_safe(pos) * waterHeight;
                else
                    newPos = normalized_safe(pos) * radius;
                obj->SetPosition(newPos);
                obj->SetOrientation(planet->GetUprightOrientation(obj->GetPosition(), obj->GetOrientation()));
                bool bUnderwater = !g_b0167eb74 && LengthSquared(obj->GetPosition()) <= waterHeight * waterHeight;
                UpdateWaterState(obj, bUnderwater, obj->GetPosition(), obj->GetOrientation());
                obj->mbSupported = true;
                return;
            }
        }
        if (g_b0167eb74) {
            obj->SetPosition(pos);
            NoteTransform(obj->GetPosition(), obj->GetOrientation());
            obj->mFlags &= ~0x1000;
            return;
        }
        if (obj->mbSelfPowered) {
            const BoundingBox& ext = obj->GetLocalExtents();
            float height = waterHeight - (ext.upper.z - ext.lower.z) * 0.55f;
            height = max_(radius, height);
            if (distSq > height * height)
                obj->SetPosition(pos);
            else
                obj->SetPosition(normalized_safe(pos) * height);
        } else {
            obj->SetPosition(pos);
        }
        const BoundingBox& ext = obj->GetLocalExtents();
        cSPTransform xf;
        obj->LocalToWorldTransform(xf);
        Vector3 probe = g_v0167eb8c;
        xf.BackTransformPoint(probe);
        bool bUnderwater = IsBoxUnderwater(probe, waterHeight, ext);
        UpdateWaterState(obj, bUnderwater, obj->GetPosition(), obj->GetOrientation());
        return;
    }

    case kNoCorrection:
        obj->SetPosition(pos);
        break;

    case kNoCorrectionOrGravity:
        obj->SetPosition(pos);
        return;

    case kSnapToWater:
        obj->SetPosition(planet->ProjectToWaterSurface(pos));
        obj->SetOrientation(planet->GetUprightOrientation(obj->GetPosition(), obj->GetOrientation()));
        UpdateWaterState(obj, !g_b0167eb74, obj->GetPosition(), obj->GetOrientation());
        return;

    case kSnapToGroundTranslateOnly:
    {
        obj->SetPosition(g_b0167eb74 ? planet->ProjectToWaterSurface(pos)
                                     : planet->DirectionToSurfacePosition(pos));
        bool bUnderwater = !g_b0167eb74 && LengthSquared(obj->GetPosition()) <= waterHeight * waterHeight;
        UpdateWaterState(obj, bUnderwater, obj->GetPosition(), obj->GetOrientation());
        return;
    }

    case kSnapToGroundMultiSample: {
        float r = obj->GetFootprintRadius();
        Vector3 dir = obj->GetDirection();
        Vector3 up = normalized_safe(pos);
        Vector3 side = dir.Cross(up);
        Vector3 front = pos + dir * r;
        Vector3 left = pos + normalized_safe(side - dir) * r;
        Vector3 right = pos + normalized_safe(-side - dir) * r;
        up = -normalized_safe(front - left).Cross(normalized_safe(front - right));
        side = dir.Cross(up);
        Matrix3 m = MatrixFromAxes(dir, up, side);
        obj->SetOrientation(QuaternionFromMatrix(m));
        obj->SetPosition(planet->DirectionToSurfacePosition(pos));
        return;
    }

    default:
        return;
    }

    bool bUnderwater = !g_b0167eb74 && LengthSquared(obj->GetPosition()) <= waterHeight * waterHeight;
    UpdateWaterState(obj, bUnderwater, obj->GetPosition(), obj->GetOrientation());
}
