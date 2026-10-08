// Slice s00c423d0: SP::cLocomotiveObject::EvaluateForces (0x00c42710).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// Sums the steering-force list (tForceData, 0x2c bytes each) of a tSteeringData into *out:
// 0 = smooth repulsion from a point, 1 = smooth attraction (inverted falloff), 2 = constant force,
// 3 = repulsion around a line segment (swirl when nearest to the interior), 4 = unsmoothed repulsion.
#include "types.h"
#include <math.h>

#pragma warning(disable : 4035)

struct Vec3 { float x, y, z; };
struct SVec : Vec3 {       // cSPVector3 passed by value: user copy ctor, inline math
    SVec() {}
    SVec(const SVec& o) { x = o.x; y = o.y; z = o.z; }
    SVec(float a, float b, float c) { x = a; y = b; z = c; }
};
inline SVec Sub3(SVec a, SVec b) { return SVec(a.x - b.x, a.y - b.y, a.z - b.z); }
inline float Length3(SVec v) { return sqrtf(v.z * v.z + v.y * v.y + v.x * v.x); }
struct OutVec : Vec3 {      // cSPVector3: user copy semantics (movss copies)
    OutVec& operator=(const Vec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

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

struct ForceData {          // SP::tForceData, 0x2c bytes
    uint32_t type;
    uint32_t priority;
    union {
        struct { Vec3 center; float magnitude; float innerRadius; float outerRadius; } sphere;   // types 0, 1, 4
        struct { Vec3 dir; } constant;                                                           // type 2
        struct { Vec3 a; Vec3 b; float magnitude; float innerRadius; float outerRadius; } line;  // type 3
    };
};

struct SteeringData {       // SP::tSteeringData
    Vec3 curPosition;
    char pad0[0x84 - 0xc];
    ForceData* forcesBegin;
    ForceData* forcesEnd;
};

extern Vec3 kZeroVec;       // 0x0168e7e4
extern float kEpsilon;      // 0x013ec4b8 (1e-8)

Vec3* __cdecl normalized_safe(Vec3* out, const Vec3* in);                              // 0x00449c20
float __cdecl PointSegmentDistance(const Vec3* p, const Vec3* a, const Vec3* b, int* region);  // 0x00698ca0

static inline float SmoothFalloff(float dist, float lo, float hi)
{
    float c = Clamp(dist, lo, hi);
    float t = (c - lo) / (hi - lo);
    return (3.0f - t * 2.0f) * t * t;
}

// @ 0x00c42710
OutVec* __stdcall EvaluateForces(OutVec* out, SteeringData* sd)
{
    int count = (int)(sd->forcesEnd - sd->forcesBegin);
    *out = kZeroVec;
    if (count != 0) {
        int off = 0;
        do {
            ForceData* f = (ForceData*)((char*)sd->forcesBegin + off);
            Vec3 r;
            switch (f->type) {
            case 0: {
                SVec d = Sub3(*(SVec*)&sd->curPosition, *(SVec*)&f->sphere.center);
                float dx = d.x, dy = d.y, dz = d.z;
                float lo = f->sphere.innerRadius, hi = f->sphere.outerRadius;
                float len = Length3(d);
                float s = SmoothFalloff(len, lo, hi);
                if (s != 0.0f) {
                    float inv = 1.0f / (len + kEpsilon);
                    float m = f->sphere.magnitude;
                    r.y = dy * inv * s * m;
                    r.z = dz * inv * s * m;
                    r.x = m * (inv * dx * s);
                } else {
                    r = kZeroVec;
                }
                break;
            }
            case 1: {
                SVec d = Sub3(*(SVec*)&sd->curPosition, *(SVec*)&f->sphere.center);
                float dx = d.x, dy = d.y, dz = d.z;
                float lo = f->sphere.innerRadius, hi = f->sphere.outerRadius;
                float len = Length3(d);
                float s = 1.0f - SmoothFalloff(len, lo, hi);
                if (s != 0.0f) {
                    float inv = 1.0f / (len + kEpsilon);
                    float m = f->sphere.magnitude;
                    r.y = dy * inv * s * m;
                    r.z = dz * inv * s * m;
                    r.x = m * (inv * dx * s);
                } else {
                    r = kZeroVec;
                }
                break;
            }
            case 2:
                r.y = f->constant.dir.y;
                r.z = f->constant.dir.z;
                r.x = f->constant.dir.x;
                break;
            case 3: {
                SVec a = *(SVec*)&f->line.a;
                SVec b = *(SVec*)&f->line.b;
                int region;
                float dist = PointSegmentDistance(&sd->curPosition, &a, &b, &region);
                float s = 1.0f - SmoothFalloff(dist, f->line.innerRadius, f->line.outerRadius);
                if (s != 0.0f) {
                    Vec3 v;
                    if (region == 0) {
                        SVec ab = Sub3(b, a);
                        Vec3 n1, n2;
                        Vec3* p1 = normalized_safe(&n1, &a);
                        Vec3* p2 = normalized_safe(&n2, &ab);
                        v.x = (p2->y * p1->z - p2->z * p1->y) * dist;
                        v.y = (p1->x * p2->z - p2->x * p1->z) * dist;
                        v.z = (p2->x * p1->y - p1->x * p2->y) * dist;
                    } else if (region == 1) {
                        v.x = sd->curPosition.x - a.x;
                        v.y = sd->curPosition.y - a.y;
                        v.z = sd->curPosition.z - a.z;
                    } else {
                        v.x = sd->curPosition.x - b.x;
                        v.y = sd->curPosition.y - b.y;
                        v.z = sd->curPosition.z - b.z;
                    }
                    float inv = 1.0f / (dist + kEpsilon);
                    float m = f->line.magnitude;
                    r.y = v.y * inv * s * m;
                    r.z = v.z * inv * s * m;
                    r.x = m * (inv * v.x * s);
                } else {
                    r = kZeroVec;
                }
                break;
            }
            case 4: {
                SVec d = Sub3(*(SVec*)&sd->curPosition, *(SVec*)&f->sphere.center);
                float dx = d.x, dy = d.y, dz = d.z;
                float inv = 1.0f / sqrtf((dx * dx + (dy * dy + dz * dz)) + kEpsilon);
                float m = f->sphere.magnitude;
                r.y = dy * inv * m;
                r.z = dz * inv * m;
                r.x = inv * dx * m;
                break;
            }
            default:
                r = kZeroVec;
                break;
            }
            off += 0x2c;
            --count;
            out->y = r.y + out->y;
            out->x = out->x + r.x;
            out->z = out->z + r.z;
        } while (count != 0);
    }
    return out;
}
