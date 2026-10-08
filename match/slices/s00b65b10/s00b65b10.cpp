// Slice s00b65b10 -- 0x00b65b10, 2376 bytes.
//
// Radial (planet "up") ray query.  r = { position xyzw, float h0, float h1 }: a ray starting
// h0 along the radial direction of the position and ending h1 along it.  With a body (obj) the ray is
// moved into the body's local space and shot at the body's shape (hkShape::castRay, vtable slot 5); without
// one, and when `useWorld` is set, the world is queried (hkWorld::castRay with a closest-hit collector).
// The hit result is written to *out:
//   +0x00 status (3 = hit, 0 = miss)    +0x10 hit position (hkVector4)   +0x20 float* normalOut
//   +0x24 float* distOut  (hit distance minus h0)   +0x28 userdata of the hit entity   +0x2c hit entity
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (SSE scalar math; x87 only for sqrt and fabs).

#include "types.h"
#include <math.h>

typedef float hkReal;

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
    hkVector4() {}
    hkVector4(const hkVector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    void operator=(const hkVector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    void setTransformedPos(const class hkTransform& t, const hkVector4& v);          // 0x01081360
    void setTransformedInversePos(const class hkTransform& t, const hkVector4& v);   // 0x010813d0
};

class hkTransform {
public:
    hkVector4 m_col0, m_col1, m_col2, m_translation;
};

class hkBool {
public:
    hkBool() {}
    hkBool(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
private:
    char m_bool;
};

extern const hkVector4 g_hkQuadRealMinusHalf;     // 0x0149d620 (-0.5 x4)

struct hkQuaternion {
    hkVector4 m_vec;
};

static __forceinline hkReal hkSqrtInverse(hkReal r) { return (hkReal)(1.0f / sqrt(r)); }

// Rotates v (four lanes wide) by the conjugate of q: world to local direction.
static __forceinline void rotateByInverseQuat(hkVector4& out, const hkQuaternion& q, const hkVector4& v)
{
    const hkReal qw = q.m_vec.w;
    const hkReal q2 = qw * qw;
    hkVector4 ret = g_hkQuadRealMinusHalf;
    ret.x = (ret.x + q2) * v.x;
    ret.y = (ret.y + q2) * v.y;
    ret.z = (ret.z + q2) * v.z;
    ret.w = (ret.w + q2) * v.w;
    const hkReal dot = (v.y * q.m_vec.y + v.z * q.m_vec.z) + q.m_vec.x * v.x;
    ret.x += q.m_vec.x * dot;
    ret.y += q.m_vec.y * dot;
    ret.z += q.m_vec.z * dot;
    ret.w += q.m_vec.w * dot;
    hkVector4 c;
    c.x = v.y * q.m_vec.z - v.z * q.m_vec.y;
    c.y = v.z * q.m_vec.x - q.m_vec.z * v.x;
    c.z = q.m_vec.y * v.x - v.y * q.m_vec.x;
    c.w = 0.0f;
    ret.x += c.x * qw;
    ret.y += c.y * qw;
    ret.z += c.z * qw;
    ret.w += c.w * qw;
    out.x = ret.x * 2.0f; out.y = ret.y * 2.0f; out.z = ret.z * 2.0f; out.w = ret.w * 2.0f;
}

// Rotates v by q: local to world direction.
static __forceinline void rotateByQuat(hkVector4& out, const hkQuaternion& q, const hkVector4& v)
{
    const hkReal qw = q.m_vec.w;
    const hkReal q2 = qw * qw;
    hkVector4 ret = g_hkQuadRealMinusHalf;
    ret.x = (ret.x + q2) * v.x;
    ret.y = (ret.y + q2) * v.y;
    ret.z = (ret.z + q2) * v.z;
    ret.w = (ret.w + q2) * v.w;
    const hkReal dot = (q.m_vec.x * v.x + v.y * q.m_vec.y) + v.z * q.m_vec.z;
    ret.x += q.m_vec.x * dot;
    ret.y += q.m_vec.y * dot;
    ret.z += q.m_vec.z * dot;
    ret.w += q.m_vec.w * dot;
    hkVector4 c;
    c.x = v.z * q.m_vec.y - v.y * q.m_vec.z;
    c.y = q.m_vec.z * v.x - v.z * q.m_vec.x;
    c.z = v.y * q.m_vec.x - q.m_vec.y * v.x;
    c.w = 0.0f;
    ret.x += c.x * qw;
    ret.y += c.y * qw;
    ret.z += c.z * qw;
    ret.w += c.w * qw;
    out.x = ret.x * 2.0f; out.y = ret.y * 2.0f; out.z = ret.z * 2.0f; out.w = ret.w * 2.0f;
}

struct hkShapeRayCastInput {
    hkVector4 m_from;
    hkVector4 m_to;
    uint32_t m_filterInfo;                         // +0x20
    const void* m_rayShapeCollectionFilter;        // +0x24
};

struct hkShapeRayCastOutput {
    hkVector4 m_normal;
    int m_extraInfo;
    hkReal m_hitFraction;
    hkShapeRayCastOutput() : m_hitFraction(1.0f) {}
};

struct hkWorldRayCastInput {
    hkVector4 m_from;
    hkVector4 m_to;
    bool m_enableShapeCollectionFilter;            // +0x20
    uint32_t m_filterInfo;                         // +0x24
};

struct hkWorldRayCastOutput : hkShapeRayCastOutput {
    const struct hkCollidable* m_rootCollidable;
    hkWorldRayCastOutput() : m_rootCollidable(0) {}
};

struct hkRayHitCollector {
    hkReal m_earlyOutHitFraction;
    hkRayHitCollector() : m_earlyOutHitFraction(1.0f) {}
};

struct hkClosestRayHitCollector : hkRayHitCollector {
    virtual void addRayHit(const hkShapeRayCastOutput& hitInfo);   // vtable 0x01464944
    hkWorldRayCastOutput m_rayHit;
};

struct hkShape {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const;   // slot 5
};

struct hkPropertyValue {
    uint32_t type, value;
    hkPropertyValue() {}
};

class hkEntity {
public:
    uint32_t pad00[3];
    void* m_userData;                      // +0x0c
    uint32_t pad10[3];
    hkShape* m_shape;                      // +0x1c
    uint32_t pad20[(0x58 - 0x20) / 4];
    struct hkMotion* m_motion;             // +0x58
    hkPropertyValue getProperty(uint32_t key) const;     // 0x00496140
};

struct hkMotion {
    uint32_t pad00[4];
    hkTransform m_transform;               // +0x10
    uint32_t pad50[(0x80 - 0x50) / 4];
    hkQuaternion m_rotation;               // +0x80
};

struct hkCollidable {
    uint32_t pad00[4];
    int m_ownerOffset;                     // +0x10
    uint32_t pad14;
    uint8_t m_broadPhaseType;              // +0x18 (1 = entity)
    hkEntity* getOwner() const { return (hkEntity*)((char*)this + m_ownerOffset); }
};

struct hkWorld {
    uint32_t pad00[0x7c / 4];
    void* m_collisionFilter;               // +0x7c
    void castRay(const hkWorldRayCastInput& input, hkClosestRayHitCollector& output) const;   // 0x01082990
};

struct RayObj {
    uint32_t pad00[3];
    hkEntity* m_entity;                    // +0x0c
};

struct RadialRay {
    hkVector4 m_pos;
    hkReal m_h0, m_h1;
};

struct RayHitResult {
    int m_status;                          // +0x00
    uint32_t pad04[3];
    hkVector4 m_pos;                       // +0x10
    hkVector4* m_normalOut;                // +0x20
    hkReal* m_distOut;                     // +0x24
    void* m_userData;                      // +0x28
    hkEntity* m_entity;                    // +0x2c
};

void __cdecl FUN_00b65710(hkVector4* up, const RadialRay* ray);

// @ 0x00b65b10
void __cdecl FUN_00b65b10(const RadialRay* r, hkWorld* world, RayObj* obj, bool useWorld, uint32_t filterInfo,
                          RayHitResult* out)
{
    const hkReal h0 = r->m_h0;
    const hkReal h1 = r->m_h1;
    const hkReal span = (hkReal)fabs(h0 - h1);
    if (obj)
    {
        hkEntity* ent = obj->m_entity;

        // radial direction of the position, rotated into the body's local frame
        hkVector4 d(r->m_pos);
        const hkReal lenSq = d.x * d.x + d.z * d.z + d.y * d.y;
        const hkReal inv = (lenSq == 0.0f) ? 0.0f : hkSqrtInverse(lenSq);
        d.x *= inv; d.y *= inv; d.z *= inv; d.w *= inv;
        hkVector4 dir;
        rotateByInverseQuat(dir, ent->m_motion->m_rotation, d);

        hkVector4 local;
        local.setTransformedInversePos(ent->m_motion->m_transform, r->m_pos);

        hkShapeRayCastInput input;
        input.m_rayShapeCollectionFilter =
            world->m_collisionFilter ? (const void*)((char*)world->m_collisionFilter + 0x10) : 0;
        input.m_from.x = r->m_h0 * dir.x + local.x;
        input.m_from.y = dir.y * r->m_h0 + local.y;
        input.m_from.z = dir.z * r->m_h0 + local.z;
        input.m_from.w = dir.w * r->m_h0 + local.w;
        input.m_to.x = r->m_h1 * dir.x + local.x;
        input.m_to.y = dir.y * r->m_h1 + local.y;
        input.m_to.z = dir.z * r->m_h1 + local.z;
        input.m_to.w = dir.w * r->m_h1 + local.w;
        input.m_filterInfo = filterInfo;

        hkShapeRayCastOutput result;
        ent->m_shape->castRay(input, result);
        if (result.m_hitFraction < 1.0f)
        {
            out->m_status = 3;
            if (out->m_distOut)
                *out->m_distOut = result.m_hitFraction * span - r->m_h0;
            const hkReal t = result.m_hitFraction;
            const hkReal s = 1.0f - t;
            hkVector4 p;
            p.x = s * input.m_from.x + t * input.m_to.x;
            p.y = t * input.m_to.y + s * input.m_from.y;
            p.z = t * input.m_to.z + s * input.m_from.z;
            p.w = t * input.m_to.w + s * input.m_from.w;
            out->m_pos.setTransformedPos(ent->m_motion->m_transform, p);
            if (out->m_normalOut)
                rotateByQuat(*out->m_normalOut, ent->m_motion->m_rotation, result.m_normal);
            if (ent->getProperty(0).type == 3)
                out->m_userData = ent->m_userData;
            out->m_entity = ent;
        }
        else
            out->m_status = 0;
        return;
    }
    if (!useWorld)
    {
        out->m_status = 0;
        return;
    }

    hkVector4 up;
    FUN_00b65710(&up, r);
    hkWorldRayCastInput input;
    input.m_from.x = up.x * h0 + r->m_pos.x;
    input.m_from.y = up.y * h0 + r->m_pos.y;
    input.m_from.z = up.z * h0 + r->m_pos.z;
    input.m_from.w = up.w * h0 + r->m_pos.w;
    input.m_to.x = up.x * h1 + r->m_pos.x;
    input.m_to.y = up.y * h1 + r->m_pos.y;
    input.m_to.z = up.z * h1 + r->m_pos.z;
    input.m_to.w = up.w * h1 + r->m_pos.w;
    input.m_filterInfo = filterInfo;
    input.m_enableShapeCollectionFilter = false;

    hkClosestRayHitCollector collector;
    world->castRay(input, collector);
    const hkCollidable* hit = collector.m_rayHit.m_rootCollidable;
    if (hit)
    {
        out->m_status = 3;
        if (out->m_distOut)
            *out->m_distOut = collector.m_rayHit.m_hitFraction * span - r->m_h0;
        const hkReal t = collector.m_rayHit.m_hitFraction;
        const hkReal s = 1.0f - t;
        out->m_pos.x = t * input.m_to.x + s * input.m_from.x;
        out->m_pos.y = t * input.m_to.y + s * input.m_from.y;
        out->m_pos.z = t * input.m_to.z + s * input.m_from.z;
        out->m_pos.w = t * input.m_to.w + s * input.m_from.w;
        if (out->m_normalOut)
            *out->m_normalOut = collector.m_rayHit.m_normal;
        if (hit->m_broadPhaseType == 1)
        {
            hkEntity* ent = hit->getOwner();
            if (ent)
            {
                if (ent->getProperty(0).type == 3)
                    out->m_userData = ent->m_userData;
            }
            out->m_entity = ent;
        }
        else
            out->m_entity = 0;
    }
    else
        out->m_status = 0;
}
