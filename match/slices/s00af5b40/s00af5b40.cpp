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
