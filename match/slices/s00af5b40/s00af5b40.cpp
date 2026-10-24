// Slice s00af5b40: 0x00af5b40, point-versus-shape probe used by the planet-surface path tracer
// (called as ProbeHit from TracePlanetPath, slice s00af6bf0).
//
// The shape record has a type at +0x24 (0 sphere, 1 box in a local frame, 2 rounded polyline,
// 3 shell between two spheres/ellipsoids). The function tests whether the point `p` (param_3)
// is inside/near the shape. When `push` is set it may also move `p` out to the shape surface
// (plus `margin`) and raise *moved. Returns true when the point is affected by the shape.
//
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <float.h>
#include <string.h>

struct Vec3 { float x, y, z; };

// cSPTransform (embedded at +0x70 in the shape).
struct cSPTransform {
    void BackTransformPoint(Vec3* p);  // 0x004ff6d0 (thiscall, ret 4)
    void TransformPoint(Vec3* p);      // 0x0044d4f0 (thiscall, ret 4)
};

bool Vector3_NotEqual(const Vec3* a, const Vec3* b);                    // 0x0041dd30 (cdecl)
Vec3* normalized_safe(Vec3* out, const Vec3* v);                        // 0x00449c20 (cdecl)
float SegmentDistance(const Vec3* p, const Vec3* a, const Vec3* b);     // 0x00698b30 (cdecl, float in st0)
void ClosestOnSegment(Vec3* out, const Vec3* p, const Vec3* a, const Vec3* b);  // 0x00698e00 (cdecl)
bool PointInsidePolygon(const Vec3* verts, int count, const Vec3* p);  // 0x0069a050 (cdecl)

struct Shape {
    uint32_t pad0[9];        // 0x00
    int type;                // +0x24
    Vec3 center;             // +0x28
    uint32_t pad1[(0x48 - 0x34) / 4];
    Vec3 innerPt;            // +0x48
    float radius;            // +0x54
    Vec3 boxMin;             // +0x58
    Vec3 boxMax;             // +0x64
    cSPTransform xform;      // +0x70 (0x38 bytes)
    uint32_t padX[(0xa8 - 0x70 - 1) / 4];
    Vec3 pathRef;            // +0xa8
    int vertCount;           // +0xb4
    Vec3* verts;             // +0xb8
    uint32_t pad2[(0xc8 - 0xbc) / 4];
    float extraRadius;       // +0xc8
    uint32_t pad3[(0xe4 - 0xcc) / 4];
    Vec3 outerPt;            // +0xe4
};

static inline float Sq(float v) { return v * v; }

// @ 0x00af5b40
bool ProbeShape(Shape* s, const Vec3* q, Vec3* p, bool push, char* moved, float margin)
{
    bool result = false;
    switch (s->type) {
    case 0: {
        float dx = s->center.x - p->x;
        float dy = s->center.y - p->y;
        float dz = s->center.z - p->z;
        if (s->radius * s->radius <= (dx * dx + dy * dy) + dz * dz)
            return false;
        result = true;
        if (push) {
            Vec3 d, n;
            if (Vector3_NotEqual(p, &s->center)) {
                d.x = p->x - s->center.x;
                d.y = p->y - s->center.y;
                d.z = p->z - s->center.z;
                normalized_safe(&n, &d);
                float k = s->radius + margin;
                p->x = s->center.x + n.x * k;
                p->y = s->center.y + n.y * k;
                p->z = s->center.z + n.z * k;
                *moved = 1;
            }
            if (Vector3_NotEqual(q, &s->center)) {
                d.x = q->x - s->center.x;
                d.y = q->y - s->center.y;
                d.z = q->z - s->center.z;
                normalized_safe(&n, &d);
                float k = s->radius + margin;
                p->x = s->center.x + n.x * k;
                p->y = s->center.y + n.y * k;
                p->z = s->center.z + n.z * k;
                *moved = 1;
            }
        }
        return result;
    }
    case 1: {
        Vec3 t = *p;
        s->xform.BackTransformPoint(&t);
        if (p->x < s->boxMin.x) return false;
        if (s->boxMax.x < p->x) return false;
        if (p->y < s->boxMin.y) return false;
        if (s->boxMax.y < p->y) return false;
        if (p->z < s->boxMin.z) return false;
        if (s->boxMax.z < p->z) return false;
        result = true;
        if (push) *moved = 0;
        return result;
    }
    case 2: {
        Vec3 w = *p;
        float r = s->extraRadius + s->radius;
        float dx = s->center.x - w.x;
        float dz = s->center.z - w.z;
        float dy = s->center.y - w.y;
        if ((dx * dx + dz * dz) + dy * dy > r * r)
            return false;
        s->xform.BackTransformPoint(&w);
        w.z = 0.0f;
        float best = FLT_MAX;
        int bestIdx = 0;
        Vec3 prev = s->verts[0];
        int n = s->vertCount;
        for (int i = 1; i < n; ++i) {
            const Vec3* cur = (const Vec3*)((char*)s->verts + i * 12);
            float d = SegmentDistance(&w, &prev, cur);
            if (d < best) {
                best = d;
                bestIdx = i;
            }
            prev = *cur;
        }
        if (s->radius <= best && !PointInsidePolygon(s->verts, s->vertCount, &w))
            return false;
        result = true;
        if (push && bestIdx != 0) {
            Vec3 c;
            const Vec3* v = s->verts + bestIdx;
            ClosestOnSegment(&c, &w, v - 1, v);
            float dEnd = Sq(s->pathRef.x - c.x) + Sq(s->pathRef.z - c.z) + Sq(s->pathRef.y - c.y);
            float dPt = Sq(s->pathRef.x - w.x) + Sq(s->pathRef.z - w.z) + Sq(s->pathRef.y - w.y);
            Vec3 dir, nrm;
            if (dEnd > dPt) {
                dir.x = w.x - c.x;
                dir.y = w.y - c.y;
                dir.z = w.z - c.z;
            } else {
                dir.x = c.x - w.x;
                dir.y = c.y - w.y;
                dir.z = c.z - w.z;
            }
            dir = *normalized_safe(&nrm, &dir);
            float k = s->radius + margin;
            p->x = dir.x * k + c.x;
            p->y = dir.y * k + c.y;
            p->z = dir.z * k + c.z;
            s->xform.TransformPoint(p);
            *moved = 1;
        }
        return result;
    }
    case 3: {
        float ax = q->x, ay = q->y, az = q->z;
        float t1 = ((p->x - ax) * (p->x - ax) + (p->z - az) * (p->z - az)) + (p->y - ay) * (p->y - ay);
        float s1 = (Sq(s->innerPt.x - ax) + Sq(s->innerPt.z - az)) + Sq(s->innerPt.y - ay);
        if (t1 <= s1)
            return false;
        float s2 = (Sq(s->outerPt.x - ax) + Sq(s->outerPt.z - az)) + Sq(s->outerPt.y - ay);
        if (s2 <= t1)
            return false;
        result = true;
        if (push) *moved = 0;
        return result;
    }
    }
    return result;
}

// ---------------------------------------------------------------------------
// Shape copy assignment (0x00af6250).  The 0xf0-byte record is the same Shape
// layout used by ProbeShape; the embedded matrix at +0x84 has a non-trivial
// Assign at 0x0041cb40.
// ---------------------------------------------------------------------------

struct cSPMatrix3 {
    float m[9];                                        // +0x00
    cSPMatrix3& operator=(const cSPMatrix3& other) {
        Assign(other);
        return *this;
    }
    void Assign(const cSPMatrix3& other);              // 0x0041cb40
};

struct ShapeCopy {
    uint32_t m_head[8];                                // +0x00
    uint32_t m_field20;                                // +0x20
    uint32_t m_field24;                                // +0x24
    float m_field28;                                   // +0x28
    float m_field2c;                                   // +0x2c
    float m_field30;                                   // +0x30
    float m_field34;                                   // +0x34
    float m_field38;                                   // +0x38
    float m_field3c;                                   // +0x3c
    uint8_t m_field40;                                 // +0x40
    uint8_t m_pad41[3];                                // +0x41
    float m_field44;                                   // +0x44
    float m_inner0;                                    // +0x48
    float m_inner1;                                    // +0x4c
    float m_inner2;                                    // +0x50
    float m_radius;                                    // +0x54
    float m_boxMin0;                                   // +0x58
    float m_boxMin1;                                   // +0x5c
    float m_boxMin2;                                   // +0x60
    float m_boxMax0;                                   // +0x64
    float m_boxMax1;                                   // +0x68
    float m_boxMax2;                                   // +0x6c
    uint16_t m_field70;                                // +0x70
    uint16_t m_field72;                                // +0x72
    float m_field74;                                   // +0x74
    float m_field78;                                   // +0x78
    float m_field7c;                                   // +0x7c
    float m_field80;                                   // +0x80
    cSPMatrix3 m_matrix84;                             // +0x84
    float m_fielda8;                                   // +0xa8
    float m_fieldac;                                   // +0xac
    float m_fieldb0;                                   // +0xb0
    uint32_t m_fieldb4;                                // +0xb4
    uint32_t m_fieldb8;                                // +0xb8
    float m_fieldbc;                                   // +0xbc
    float m_fieldc0;                                   // +0xc0
    float m_fieldc4;                                   // +0xc4
    float m_fieldc8;                                   // +0xc8
    float m_fieldcc;                                   // +0xcc
    float m_fieldd0;                                   // +0xd0
    float m_fieldd4;                                   // +0xd4
    float m_fieldd8;                                   // +0xd8
    float m_fielddc;                                   // +0xdc
    float m_fielde0;                                   // +0xe0
    float m_fielde4;                                   // +0xe4
    float m_fielde8;                                   // +0xe8
    float m_fieldec;                                   // +0xec
    ShapeCopy& operator=(const ShapeCopy& other);
};

// @ 0x00af6250
ShapeCopy& ShapeCopy::operator=(const ShapeCopy& other)
{
    ShapeCopy* dst = this;
    const ShapeCopy* src = &other;

    memcpy(dst->m_head, src->m_head, sizeof(dst->m_head));

    dst->m_field20 = src->m_field20;
    dst->m_field24 = src->m_field24;
    dst->m_field28 = src->m_field28;
    dst->m_field2c = src->m_field2c;
    dst->m_field30 = src->m_field30;
    dst->m_field34 = src->m_field34;
    dst->m_field38 = src->m_field38;
    dst->m_field3c = src->m_field3c;
    dst->m_field40 = src->m_field40;
    dst->m_field44 = src->m_field44;
    dst->m_inner0 = src->m_inner0;
    dst->m_inner1 = src->m_inner1;
    dst->m_inner2 = src->m_inner2;
    dst->m_radius = src->m_radius;
    dst->m_boxMin0 = src->m_boxMin0;
    dst->m_boxMin1 = src->m_boxMin1;
    dst->m_boxMin2 = src->m_boxMin2;
    dst->m_boxMax0 = src->m_boxMax0;
    dst->m_boxMax1 = src->m_boxMax1;
    dst->m_boxMax2 = src->m_boxMax2;
    dst->m_field70 = src->m_field70;
    dst->m_field72 = src->m_field72;
    dst->m_field74 = src->m_field74;
    dst->m_field78 = src->m_field78;
    dst->m_field7c = src->m_field7c;
    dst->m_field80 = src->m_field80;
    dst->m_matrix84 = src->m_matrix84;
    dst->m_fielda8 = src->m_fielda8;
    dst->m_fieldac = src->m_fieldac;
    dst->m_fieldb0 = src->m_fieldb0;
    dst->m_fieldb4 = src->m_fieldb4;
    dst->m_fieldb8 = src->m_fieldb8;
    dst->m_fieldbc = src->m_fieldbc;
    dst->m_fieldc0 = src->m_fieldc0;
    dst->m_fieldc4 = src->m_fieldc4;
    dst->m_fieldc8 = src->m_fieldc8;
    dst->m_fieldcc = src->m_fieldcc;
    dst->m_fieldd0 = src->m_fieldd0;
    dst->m_fieldd4 = src->m_fieldd4;
    dst->m_fieldd8 = src->m_fieldd8;
    dst->m_fielddc = src->m_fielddc;
    dst->m_fielde0 = src->m_fielde0;
    dst->m_fielde4 = src->m_fielde4;
    dst->m_fielde8 = src->m_fielde8;
    dst->m_fieldec = src->m_fieldec;
    return *dst;
}
