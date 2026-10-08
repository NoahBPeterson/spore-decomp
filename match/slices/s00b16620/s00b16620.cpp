// Slice s00b16620: FUN_00b16620 (cdecl), "does the moving shape `q` touch the spatial object
// `obj`?" Cheap bounding-sphere reject, then the shape's reference point and its 9 sample
// points are tested against the object's local-space box (the object's transform inverted).
// When `out` is given it receives the push-out direction scaled by how deep the shape
// sits (ray from outside the box back along the direction, box slab test at 0x00698880).
// Class and field names are Claude-coined from usage.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };          // plain POD: copies go through integer registers
struct Matrix3 {
    float m[9];
    void Assign(const Matrix3* src);     // 0x0041CB40 (thiscall ret 4)
};

extern Vec3 kTransformOrigin;            // 0x0167BDB4
extern Matrix3 kIdentity;                // 0x0167BE00

// Local-to-world transform of a spatial object (0x38 bytes).
struct PartTransform {
    union {
        uint32_t flags;                  // bit 1: has rotation
        struct { uint16_t flagsLo, flagsHi; };
    };
    Vec3 pos;                            // +0x04
    float scale;                         // +0x10
    Matrix3 mat;                         // +0x14
    PartTransform()
    {
        pos.x = kTransformOrigin.x;
        pos.y = kTransformOrigin.y;
        flagsHi = 0;
        pos.z = kTransformOrigin.z;
        flagsLo = 0;
        scale = 1.0f;
        mat.Assign(&kIdentity);
    }
    void Invert();                       // 0x0040EFA0
};

#define V(n) virtual void v##n()
struct cSpatialObject {
    V(00); V(04); V(08); V(0c); V(10); V(14); V(18); V(1c); V(20); V(24); V(28);
    virtual const Vec3* GetPosition();                               // +0x2C
    V(30); V(34); V(38); V(3c); V(40); V(44); V(48); V(4c); V(50); V(54); V(58); V(5c);
    V(60); V(64);
    virtual const float* GetBounds();                                // +0x68 (min[3], max[3])
    V(6c);
    virtual float GetRadius();                                       // +0x70
    uint32_t pad_04[(0x50 - 0x04) / 4];
    uint32_t mFlags;                                                 // +0x50
    void LocalToWorldTransform(PartTransform* out);                  // 0x00C897E0
};

struct cShape {
    Vec3 pts[9];                         // +0x00; pts[4] (+0x30) is the reference point
};
struct cQuery {
    Vec3 mDir;                           // +0x00
    uint8_t pad_0c[0x48 - 0x0C];
    cShape* mpShape;                     // +0x48
    uint8_t pad_4c[0xCC - 0x4C];
    float mRadius;                       // +0xCC
};

Vec3* normalized_safe(Vec3* dst, const Vec3* src);                   // 0x00449C20 (cdecl)
bool RayBoxHit(const Vec3* origin, const Vec3* dir, const float* box, float* tOut);   // 0x00698880 (cdecl)

// @ 0x00B16620
bool TestShapeHitsObject(cQuery* q, cSpatialObject* obj, Vec3* out)
{
    uint32_t objFlags = obj->mFlags;
    if ((objFlags & 0x10) && !(objFlags & 0x20))
        return false;

    const float* b0 = obj->GetBounds();
    float half = (b0[5] - b0[2]) * 0.5f;
    const Vec3* oc = obj->GetPosition();
    cShape* shape = q->mpShape;
    Vec3 d, p, e, nd;
    float t;
    d.x = shape->pts[4].x - (oc->x + half);
    d.y = shape->pts[4].y - (oc->y + half);
    d.z = shape->pts[4].z - (oc->z + half);
    float r = obj->GetRadius() * 2.0f + q->mRadius;
    float rr = r * r;
    float d2 = (d.x * d.x + d.z * d.z) + d.y * d.y;
    if (!(rr > d2))
        return false;

    const float* box = obj->GetBounds();
    PartTransform T;
    obj->LocalToWorldTransform(&T);
    T.Invert();
    bool rot = (T.flags & 2) != 0;

    // reference direction of the query, into the object's space
    float ax = q->mDir.x, ay = q->mDir.y, az = q->mDir.z;
    if (rot) {
        float nx = (T.mat.m[6] * az + T.mat.m[3] * ay) + T.mat.m[0] * ax;
        float ny = (ax * T.mat.m[1] + ay * T.mat.m[4]) + az * T.mat.m[7];
        float nz = (ax * T.mat.m[2] + ay * T.mat.m[5]) + az * T.mat.m[8];
        ax = nx; ay = ny; az = nz;
    }
    p.x = T.pos.x + T.scale * ax;
    p.y = T.pos.y + ay * T.scale;
    p.z = T.pos.z + az * T.scale;
    if (box[0] <= p.x && p.x <= box[3] && box[1] <= p.y && p.y <= box[4] && box[2] <= p.z && p.z <= box[5]) {
        if (out) {
            const Vec3* c = obj->GetPosition();
            d.x = shape->pts[4].x - c->x;
            d.y = shape->pts[4].y - c->y;
            d.z = shape->pts[4].z - c->z;
            *out = *normalized_safe(&nd, &d);
            float vx = out->x, vy = out->y, vz = out->z;
            if (rot) {
                float nx = (vx * T.mat.m[0] + vz * T.mat.m[6]) + vy * T.mat.m[3];
                float ny = (vx * T.mat.m[1] + vy * T.mat.m[4]) + vz * T.mat.m[7];
                float nz = (vx * T.mat.m[2] + vy * T.mat.m[5]) + vz * T.mat.m[8];
                vx = nx; vy = ny; vz = nz;
            }
            float ex = box[3] - box[0], ey = box[4] - box[1], ez = box[5] - box[2];
            float len = sqrtf((ez * ez + ey * ey) + ex * ex);
            e.x = vx * len + p.x;
            e.y = vy * len + p.y;
            e.z = vz * len + p.z;
            nd.x = -vx; nd.y = -vy; nd.z = -vz;
            if (RayBoxHit(&e, &nd, box, &t)) {
                float s = len - t;
                out->x = s * out->x;
                out->y = out->y * s;
                out->z = out->z * s;
            }
        }
        return true;
    }

    for (int i = 8; i >= 0; --i) {
        const Vec3& sp = shape->pts[i];
        float sx = sp.x, sy = sp.y, sz = sp.z;
        if (rot) {
            float nx = (sx * T.mat.m[0] + sz * T.mat.m[6]) + sy * T.mat.m[3];
            float ny = (sx * T.mat.m[1] + sy * T.mat.m[4]) + sz * T.mat.m[7];
            float nz = (sx * T.mat.m[2] + sy * T.mat.m[5]) + sz * T.mat.m[8];
            sx = nx; sy = ny; sz = nz;
        }
        p.x = T.pos.x + T.scale * sx;
        p.y = T.pos.y + sy * T.scale;
        p.z = T.pos.z + sz * T.scale;
        if (box[0] <= p.x && p.x <= box[3] && box[1] <= p.y && p.y <= box[4] && box[2] <= p.z && p.z <= box[5]) {
            if (!out)
                return true;
            const Vec3* c = obj->GetPosition();
            float dx = shape->pts[4].x - c->x;
            float dz = shape->pts[4].z - c->z;
            float dy = shape->pts[4].y - c->y;
            float inv = 1.0f / sqrtf(((dx * dx + dz * dz) + dy * dy) + 1e-8f);
            out->x = inv * dx;
            out->y = dy * inv;
            out->z = dz * inv;
            float vx = out->x, vy = out->y, vz = out->z;
            if (rot) {
                float nx = (vx * T.mat.m[0] + vz * T.mat.m[6]) + vy * T.mat.m[3];
                float ny = (vx * T.mat.m[1] + vy * T.mat.m[4]) + vz * T.mat.m[7];
                float nz = (vx * T.mat.m[2] + vy * T.mat.m[5]) + vz * T.mat.m[8];
                vx = nx; vy = ny; vz = nz;
            }
            float ex = box[3] - box[0], ey = box[4] - box[1], ez = box[5] - box[2];
            float len = sqrtf((ez * ez + ey * ey) + ex * ex);
            e.x = vx * len + p.x;
            e.y = vy * len + p.y;
            e.z = vz * len + p.z;
            nd.x = -vx; nd.y = -vy; nd.z = -vz;
            if (!RayBoxHit(&e, &nd, box, &t))
                return true;
            float s = len - t;
            out->x = s * out->x;
            out->y = out->y * s;
            out->z = out->z * s;
            return true;
        }
    }
    return false;
}
