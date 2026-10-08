// Slice s00b52690 -- 0x00b52690, 1892 bytes (__cdecl, 7 stack args).
//
// Puts a spatial object (`obj`) back on the planet surface: it (1) re-orients the object on the
// terrain according to `orientMode` (1 surface orientation, 2 pitched surface orientation, 3 surface
// normal orientation), (2) lets the sibling routine 0x00b523e0 sync the Havok body `body`, (3) works
// out the lowest point of the body's shape in the surface frame (shape AABB under the rotation
// surface-orientation^-1 * body rotation, plus the rotated center of the object's local extents),
// (4) projects the body position onto the planet surface (0x00b82df0, three bool-like options) and
// (5) sweeps a temporary hkSimpleShapePhantom (same shape and transform as the body) along the
// radial line from (distance - height offset) to (distance - 0.05) with setPositionAndLinearCast.  If
// the cast hits, the body is moved to the hit position, its velocities are zeroed and 0x00b52230
// finishes the sync.  `useCenterDistance` replaces the surface distance by the body's distance to
// the planet center.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (SSE scalar math; sqrt chains in x87).
#include "types.h"

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef float hkReal;

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// ---- math -----------------------------------------------------------------------------------------
struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
struct BoundingBox { Vector3 lower, upper; };

// ---- Havok 3.1 (only what this function needs) ----------------------------------------------------
struct __declspec(align(16)) hkVector4 {
    float x, y, z, w;
    hkVector4() {}
    hkVector4(const hkVector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    hkVector4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
    void operator=(const hkVector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
};
struct hkQuaternion { float x, y, z, w; };
struct __declspec(align(16)) hkRotation {
    hkVector4 m_col0, m_col1, m_col2;
    hkRotation() {}
    void set(const hkQuaternion& q);                                         // 0x010824a0
};
struct __declspec(align(16)) hkTransform {
    hkRotation m_rotation;
    hkVector4 m_translation;
    hkTransform() {}
};
struct hkAabb { hkVector4 m_min, m_max; };

class hkMemory {
public:
    PV4
    virtual void* allocateChunk(int nbytes, int cl);                         // 0x10
    static hkMemory* s_instance;                                             // 0x016e4178
    static hkMemory& getInstance() { return *s_instance; }
};

class hkReferencedObject {
public:
    virtual ~hkReferencedObject();                                           // 0x00
    u16 m_memSizeAndFlags;                                                   // 0x04
    u16 m_referenceCount;                                                    // 0x06
};

class hkShape : public hkReferencedObject {
public:
    PV2
    virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;   // 0x0c
};

class hkWorldObject : public hkReferencedObject {
public:
    void* m_world;                                                           // 0x08
    void* m_userData;                                                        // 0x0c
    void removeReference();                                                  // 0x0109ae60 (out of line here)
};

class hkMotion {
public:
    PV8 PV8 PV4 PV2                                                          // slots 0..21
    virtual void setAngularVelocity(const hkVector4& v);                     // 0x58
    virtual void setLinearVelocity(const hkVector4& v);                      // 0x5c
    u8 pad[0x80 - 4];                                                        // motion state: transform at +0x10 (position +0x40)
    hkQuaternion m_rotation;                                                 // 0x80
};

extern const hkVector4 hkVector4_zero;                                       // 0x016e42d0
extern const hkVector4 kHalf;                                                // 0x0149d620 (-0.5 x4)

class hkRigidBody : public hkWorldObject {
public:
    u8 pad10[0x1c - 0x10];
    hkShape* m_shape;                                                        // 0x1c (collidable's shape)
    u8 pad20[0x58 - 0x20];
    hkMotion* m_motion;                                                      // 0x58
    void setPosition(const hkVector4& p);                                    // 0x01087820
    void activate();                                                         // 0x01088ae0
    __forceinline void setLinearVelocity(const hkVector4& v)
    {
        activate();
        m_motion->setLinearVelocity(v);
    }
    __forceinline void setAngularVelocity(const hkVector4& v)
    {
        activate();
        m_motion->setAngularVelocity(v);
    }
};

struct hkLinearCastInput {
    hkVector4 m_to;
    hkReal m_maxExtraPenetration;
    hkReal m_startPointTolerance;
    hkLinearCastInput() {}
};

struct hkRootCdPoint {
    hkVector4 m_position;
    hkVector4 m_separatingNormal;   // w = distance
    const void* m_rootCollidableA;
    unsigned m_shapeKeyA;
    const void* m_rootCollidableB;
    unsigned m_shapeKeyB;
};

class hkCdPointCollector {
public:
    hkReal m_earlyOutDistance;
    virtual ~hkCdPointCollector() {}
    virtual void addCdPoint(const void* event) = 0;
    virtual void reset();
};
class hkClosestCdPointCollector : public hkCdPointCollector {   // vtable 0x013ef52c
public:
    hkRootCdPoint m_hitPoint;                                    // +0x10
    __forceinline hkClosestCdPointCollector()
    {
        m_hitPoint.m_rootCollidableA = 0;
        m_hitPoint.m_separatingNormal.w = 3.40282e+038f;
        m_earlyOutDistance = 3.40282e+038f;
    }
    virtual ~hkClosestCdPointCollector() {}
    virtual void addCdPoint(const void* event);
    virtual void reset();
    bool hasHit() const { return m_hitPoint.m_rootCollidableA != 0; }
};

class hkPhantom : public hkWorldObject {};
class hkSimpleShapePhantom : public hkPhantom {
public:
    void* operator new(size_t nbytes)
    {
        hkReferencedObject* b = (hkReferencedObject*)hkMemory::getInstance().allocateChunk((int)nbytes, 0x2e);
        b->m_memSizeAndFlags = (u16)nbytes;
        return b;
    }
    void operator delete(void*) {}
    hkSimpleShapePhantom(const hkShape* shape, const hkTransform& transform, u32 collisionFilterInfo);   // 0x0108c750
    PV8 PV2 PV                                                               // slots 1..11 (own)
    virtual void setPositionAndLinearCast(const hkVector4& position, const hkLinearCastInput& input,
                                          hkCdPointCollector& castCollector,
                                          hkCdPointCollector* startCollector);   // 0x30
    u8 pad[0x130 - 0x10];
};

class hkWorld {
public:
    hkPhantom* addPhantom(hkPhantom* phantom);                               // 0x01083320
    void removePhantom(hkPhantom* phantom);                                  // 0x01083400
};
extern hkWorld* g_hkWorld;                                                   // 0x0167ecd0

// ---- Spore ----------------------------------------------------------------------------------------
class cSpatialObject {
public:
    PV8 PV2 PV
    virtual const Vector3& GetPosition();                                    // 0x2c
    virtual const Quaternion& GetOrientation();                              // 0x30
    virtual float GetScale();                                                // 0x34
    virtual void SetPosition(const Vector3& v);                              // 0x38
    virtual void SetOrientation(const Quaternion& q);                        // 0x3c
    PV8 PV2
    virtual const BoundingBox& GetLocalExtents();                            // 0x68
    virtual int slot6C(int);                                                 // 0x6c
    virtual float GetBoundingRadius();                                       // 0x70
};

class cPlanetModel {
public:
    u8 pad[0x20];
    Quaternion* BuildSurfaceOrientation(Quaternion* out, const Vector3* pos);                      // 0x00b7f190
    Quaternion* BuildSurfaceOrientation(Quaternion* out, const Vector3* pos, const Quaternion* orient);   // 0x00b7f1f0
    Quaternion* BuildPitchedSurfaceOrientation(Quaternion* out, const Vector3* pos,
                                               const Quaternion* orient, float pitch);             // 0x00b7f2b0
    Quaternion* BuildSurfaceNormalOrientation(Quaternion* out, const Vector3* pos,
                                              const Quaternion* orient, float pitch);              // 0x00b7f320
    // options are bool-like dwords tested as bytes by the callee
    Vector3* ProjectToSurface(Vector3* out, const Vector3* pos, int a, int b, int c, int d);       // 0x00b82df0
};
cPlanetModel* PlanetModel();                                                 // 0x00b3d350
void SyncBodyBefore(cSpatialObject* obj, hkRigidBody* body);                 // 0x00b523e0
void SyncBodyAfter(cSpatialObject* obj, hkRigidBody* body);                  // 0x00b52230

// @ 0x00b52690
void PlaceObjectOnSurface(cSpatialObject* obj, hkRigidBody* body, bool useCenterDistance, int orientMode,
                          int optA, int optB, int optC)
{
    cPlanetModel* planet = PlanetModel();

    Quaternion tmp1, tmp2, tmp3;
    const Quaternion* r;
    switch (orientMode) {
    case 3:
        r = planet->BuildSurfaceNormalOrientation(&tmp3, &obj->GetPosition(), &obj->GetOrientation(),
                                                  obj->GetBoundingRadius());
        break;
    case 2:
        r = planet->BuildPitchedSurfaceOrientation(&tmp2, &obj->GetPosition(), &obj->GetOrientation(),
                                                   obj->GetBoundingRadius());
        break;
    case 1:
        r = planet->BuildSurfaceOrientation(&tmp1, &obj->GetPosition(), &obj->GetOrientation());
        break;
    default:
        goto sync;
    }
    {
        Quaternion q = *r;
        obj->SetOrientation(q);
    }
sync:
    SyncBodyBefore(obj, body);

    hkMotion* motion = body->m_motion;

    // rotation of the body relative to the surface orientation at its position
    Quaternion surfTmp;
    Quaternion* sq = planet->BuildSurfaceOrientation(&surfTmp, (const Vector3*)((char*)motion + 0x40));
    float ax = sq->x, ay = sq->y, az = sq->z, aw = sq->w;
    motion = body->m_motion;
    hkQuaternion rel;
    rel.w = ((aw * motion->m_rotation.w + motion->m_rotation.y * ay) + motion->m_rotation.x * ax) +
            az * motion->m_rotation.z;
    rel.x = (motion->m_rotation.x * aw + (az * motion->m_rotation.y - ay * motion->m_rotation.z)) -
            motion->m_rotation.w * ax;
    rel.y = (aw * motion->m_rotation.y + (motion->m_rotation.z * ax - az * motion->m_rotation.x)) -
            ay * motion->m_rotation.w;
    rel.z = (aw * motion->m_rotation.z + (ay * motion->m_rotation.x - motion->m_rotation.y * ax)) -
            az * motion->m_rotation.w;

    hkTransform tx;
    tx.m_rotation.m_col0 = hkVector4(1.0f, 0.0f, 0.0f, 0.0f);
    tx.m_rotation.m_col1 = hkVector4(0.0f, 1.0f, 0.0f, 0.0f);
    tx.m_rotation.m_col2 = hkVector4(0.0f, 0.0f, 1.0f, 0.0f);
    tx.m_translation = hkVector4(0.0f, 0.0f, 0.0f, 0.0f);
    tx.m_rotation.set(rel);

    hkAabb aabb;
    body->m_shape->getAabb(tx, 0.0f, aabb);

    // lowest point of the shape: AABB minimum plus the rotated center of the local extents
    const BoundingBox* ext = &obj->GetLocalExtents();
    float cx = (ext->upper.x + ext->lower.x) * 0.5f;
    float cy = (ext->upper.y + ext->lower.y) * 0.5f;
    float cz = (ext->upper.z + ext->lower.z) * 0.5f;
    hkVector4 k = kHalf;
    float dot = (cz * rel.z + cy * rel.y) + cx * rel.x;
    float rotatedZ = ((dot * rel.z + (rel.w * rel.w + k.z) * cz) + (cy * rel.x - rel.y * cx) * rel.w) * 2.0f;
    float heightOffset = aabb.m_min.z + rotatedZ;

    Vector3 up;
    planet->ProjectToSurface(&up, (const Vector3*)((char*)body->m_motion + 0x40), optA, optB, optC, 0);
    float dist = (float)sqrt((double)up.y * up.y + (double)up.z * up.z + (double)up.x * up.x);
    obj->GetBoundingRadius();
    float inv = 1.0f / dist;
    float nx = inv * up.x;
    float ny = up.y * inv;
    float nz = up.z * inv;
    float nw = inv * 0.0f;
    if (useCenterDistance) {
        hkMotion* m = body->m_motion;
        const float* p = (const float*)((char*)m + 0x40);
        dist = (float)sqrt((double)p[0] * p[0] + (double)p[1] * p[1] + (double)p[2] * p[2]);
    }
    float d1 = dist - heightOffset;
    float d2 = dist - 0.05f;
    hkVector4 from(nx * d1, ny * d1, nz * d1, nw * d1);
    hkVector4 to(nx * d2, ny * d2, nz * d2, nw * d2);

    hkSimpleShapePhantom* phantom =
        new hkSimpleShapePhantom(body->m_shape, *(const hkTransform*)((char*)body->m_motion + 0x10), 0xc);
    g_hkWorld->addPhantom(phantom);
    phantom->removeReference();

    hkLinearCastInput input;
    input.m_to = to;
    input.m_maxExtraPenetration = 0.05f;
    input.m_startPointTolerance = 0.05f;
    hkClosestCdPointCollector collector;
    phantom->setPositionAndLinearCast(from, input, collector, 0);
    if (collector.hasHit()) {
        float t = collector.m_hitPoint.m_separatingNormal.w;
        float s = 1.0f - t;
        hkVector4 hit;
        hit.x = t * to.x + s * from.x;
        hit.y = t * to.y + s * from.y;
        hit.z = t * to.z + s * from.z;
        hit.w = t * to.w + s * from.w;
        body->setPosition(hit);
        SyncBodyAfter(obj, body);
        body->setLinearVelocity(hkVector4_zero);
        body->setAngularVelocity(hkVector4_zero);
    }
    ((hkWorld*)phantom->m_world)->removePhantom(phantom);
}
