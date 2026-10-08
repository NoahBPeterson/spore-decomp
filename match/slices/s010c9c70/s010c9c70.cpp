// Havok 3.1.0 hkCylinderShape::castRay (0x010c9c70, 2314 bytes).
// Casts a ray against the capsule-like cylinder: the two end vertices are first shrunk by the convex
// radius along the axis (perpendicular1 x perpendicular2), then the ray is tested against the infinite
// cylinder (closestInfLineSegInfLineSeg) and, if it misses the lateral surface, against the two end caps.
// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
#include <math.h>
#include <intrin.h>

typedef float hkReal;
#define HK_REAL_MAX 3.40282e+38f

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long index, void* value);

// ---- monitor stream (HK_TIMER_BEGIN / HK_TIMER_END). TLS @0x016e42a4 = current pointer, @0x016e42a8 = end.
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorTimerEndTag[];           // "Et" at 0x0149cc34
struct hkMonitorCommand { const char* m_commandAndMonitor; uint32_t m_time0; uint32_t m_pad; };
#define HK_TIMER_COMMAND(name) do { \
    void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
        hkMonitorCommand* c_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_commandAndMonitor = name; \
        uint32_t t_; \
        __asm { rdtsc } \
        __asm { mov t_, eax } \
        c_->m_time0 = t_; \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_BEGIN(name) HK_TIMER_COMMAND(name)
#define HK_TIMER_END()       HK_TIMER_COMMAND(hkMonitorTimerEndTag)

class hkBool {
public:
    hkBool(bool b) : m_bool(b ? 1 : 0) {}
private:
    char m_bool;
};

struct hkVector4Mem {                   // unaligned storage inside heap objects / caller structs
    hkReal x, y, z, w;
};
class __declspec(align(16)) hkVector4 : public hkVector4Mem {
public:
    void setCross(const hkVector4Mem& a, const hkVector4Mem& b) {
        hkReal cx = a.y * b.z - a.z * b.y;
        hkReal cy = a.z * b.x - a.x * b.z;
        hkReal cz = a.x * b.y - a.y * b.x;
        x = cx; y = cy; z = cz; w = 0.0f;
    }
    void mul4(hkReal r) { x *= r; y *= r; z *= r; w *= r; }
    void setAdd4(const hkVector4Mem& a, const hkVector4Mem& b) { x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; w = a.w + b.w; }
    void setSub4(const hkVector4Mem& a, const hkVector4Mem& b) { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
};

struct hkShapeRayCastInput {
    hkVector4Mem m_from;                // +0x00
    hkVector4Mem m_to;                  // +0x10
};
struct hkShapeRayCastOutput {
    hkVector4Mem m_normal;              // +0x00
    uint32_t m_shapeKey;                // +0x10
    hkReal m_hitFraction;               // +0x14
};

class hkCapsuleShape {
public:
    static void closestPointLineSeg(const hkVector4& point, const hkVector4& a, const hkVector4& b, hkVector4& closest);   // 0x010c2ad0
    static void closestInfLineSegInfLineSeg(const hkVector4& a, const hkVector4& da, const hkVector4& b, const hkVector4& db,
                                            hkReal& distSqrd, hkReal& t, hkReal& u, hkVector4& closestA, hkVector4& closestB);   // 0x010c2890
};

// Forces the float rounding of a value the original keeps in memory (x87 spill).
static __forceinline hkReal hkRound(hkReal v) { volatile hkReal t = v; return t; }

extern const hkReal kZero;      // 0x01485378
extern const hkReal kOne;       // 0x01485720
extern const hkReal kMinusOne;  // 0x013eb1bc
extern const hkReal kEpsilon;   // 0x014a40b0

class hkCylinderShape {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const;   // slot 5
    uint32_t m_pad04[2];
    hkReal m_radius;                    // +0x0c
    hkReal m_cylRadius;                 // +0x10
    uint32_t m_pad14[3];
    hkVector4Mem m_vertexA;             // +0x20
    hkVector4Mem m_vertexB;             // +0x30
    hkVector4Mem m_perpendicular1;      // +0x40
    hkVector4Mem m_perpendicular2;      // +0x50
};

// @ 0x010c9c70
hkBool hkCylinderShape::castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const
{
    HK_TIMER_BEGIN("TtrcCylinder");

    hkReal radius = m_radius;

    // axis = perp2 x perp1 scaled by the convex radius (w stays 0)
    hkVector4 off;
    off.setCross(m_perpendicular2, m_perpendicular1);
    off.mul4(radius);

    hkVector4 a;                        // shrunk end A
    a.setAdd4(m_vertexA, off);
    hkVector4 b;                        // shrunk end B
    b.setSub4(m_vertexB, off);

    const hkReal totalRadius = hkRound(m_cylRadius + m_radius);

    // Start point inside the cylinder: no hit.
    hkVector4 closest;
    hkCapsuleShape::closestPointLineSeg((const hkVector4&)input.m_from, a, b, closest);
    {
        hkReal dx = input.m_from.x - closest.x;
        hkReal dy = input.m_from.y - closest.y;
        hkReal dz = input.m_from.z - closest.z;
        hkReal dist = sqrtf((dz * dz + dy * dy) + dx * dx);
        if (dist < totalRadius) {
            hkReal ux = b.x - a.x, uy = b.y - a.y, uz = b.z - a.z;
            hkReal vx = input.m_from.x - a.x, vy = input.m_from.y - a.y, vz = input.m_from.z - a.z;
            if ((vx * ux + vz * uz) + vy * uy > kZero) {
                hkReal wx = input.m_from.x - b.x, wy = input.m_from.y - b.y, wz = input.m_from.z - b.z;
                if ((wx * ux + wz * uz) + wy * uy < kZero)
                    goto miss;
            }
        }
    }

    {
        hkVector4 dir;
        dir.x = input.m_to.x - input.m_from.x;
        dir.y = input.m_to.y - input.m_from.y;
        dir.z = input.m_to.z - input.m_from.z;
        dir.w = input.m_to.w - input.m_from.w;
        hkReal distSqrd = HK_REAL_MAX;
        hkVector4 axis;                 // b - a
        axis.x = b.x - a.x;
        axis.y = b.y - a.y;
        axis.z = b.z - a.z;
        axis.w = b.w - a.w;
        hkReal t;
        hkReal u;
        hkVector4 closestRay, closestAxis;
        hkCapsuleShape::closestInfLineSegInfLineSeg((const hkVector4&)input.m_from, dir, a, axis, distSqrd, t, u, closestRay, closestAxis);

        const hkReal radiusSqrd = hkRound(totalRadius * totalRadius);
        if (!(distSqrd > radiusSqrd)) {
            hkReal axisLenSqrd = (axis.x * axis.x + axis.z * axis.z) + axis.y * axis.y;
            if (axisLenSqrd > kEpsilon) {
                hkReal axisLen = hkRound(sqrtf(axisLenSqrd));
                hkVector4 rayDir;               // memory copy of dir (kept as a separate object, not forwarded)
                rayDir.z = ((volatile hkVector4Mem&)dir).z;
                rayDir.y = ((volatile hkVector4Mem&)dir).y;
                rayDir.x = ((volatile hkVector4Mem&)dir).x;
                rayDir.w = ((volatile hkVector4Mem&)dir).w;
                hkReal invAxisLenExt = kOne / axisLen;
                hkReal invAxisLen = hkRound(invAxisLenExt);
                hkVector4 n;            // unit axis
                n.x = hkRound(axis.x * invAxisLenExt);
                n.y = hkRound(axis.y * invAxisLenExt);
                n.z = hkRound(axis.z * invAxisLenExt);
                n.w = hkRound(axis.w * invAxisLenExt);

                hkReal proj = -((rayDir.z * n.z + rayDir.y * n.y) + rayDir.x * n.x);
                hkVector4 perp;
                perp.x = n.x * proj + rayDir.x;
                perp.y = n.y * proj + rayDir.y;
                perp.z = n.z * proj + rayDir.z;
                hkReal chord = hkRound(sqrtf(radiusSqrd - distSqrd));
                hkReal perpLenSqrd = (perp.x * perp.x + perp.z * perp.z) + perp.y * perp.y;
                hkReal invPerpLen = (perpLenSqrd == kZero) ? kZero : kOne / sqrtf(perpLenSqrd);

                hkReal hit = hkRound(t - invPerpLen * chord);
                if (!(hit >= output.m_hitFraction)) {
                    hkReal aProj = hkRound((n.x * a.x + n.z * a.z) + n.y * a.y);
                    hkReal omh = kOne - hit;
                    hkVector4 p;
                    p.x = hkRound(omh * input.m_from.x + hit * input.m_to.x);
                    p.y = hkRound(hit * input.m_to.y + omh * input.m_from.y);
                    p.z = hkRound(hit * input.m_to.z + omh * input.m_from.z);
                    p.w = hkRound(hit * input.m_to.w + omh * input.m_from.w);
                    hkReal s = hkRound(((p.z * n.z + p.y * n.y) + p.x * n.x) - aProj);
                    if (hit >= kZero && s > kZero && s < axisLen) {
                        hkReal f = invAxisLen * s;
                        hkReal omf = kOne - f;
                        hkVector4 q;
                        q.x = hkRound(omf * a.x + f * b.x);
                        q.y = hkRound(a.y * omf + b.y * f);
                        q.z = hkRound(a.z * omf + b.z * f);
                        q.w = a.w * omf + b.w * f;
                        hkReal nx = hkRound(p.x - q.x);
                        hkReal ny = hkRound(p.y - q.y);
                        hkReal nz = hkRound(p.z - q.z);
                        hkReal nlen = (nx * nx + nz * nz) + ny * ny;
                        hkReal inv = (nlen == kZero) ? kZero : kOne / sqrtf(nlen);
                        output.m_shapeKey = 0xffffffff;
                        output.m_normal.y = ny * inv;
                        output.m_normal.z = nz * inv;
                        output.m_hitFraction = hit;
                        output.m_normal.w = (p.w - q.w) * inv;
                        output.m_normal.x = nx * inv;
                        HK_TIMER_END();
                        return true;
                    }

                    // Ray misses the lateral surface: test the end caps.
                    hkReal fromProj = (n.x * input.m_from.x + n.z * input.m_from.z) + n.y * input.m_from.y;
                    hkVector4 e;
                    hkReal sign;
                    if (fromProj < aProj) {
                        e.x = a.x; e.y = a.y; e.z = a.z;
                        sign = -1.0f;
                    } else {
                        if (!(fromProj > axisLen + aProj))
                            goto miss;
                        e.x = b.x; e.y = b.y; e.z = b.z;
                        sign = 1.0f;
                    }
                    volatile hkReal numer = (((e.x - input.m_from.x) * n.x + (e.z - input.m_from.z) * n.z)
                                    + (e.y - input.m_from.y) * n.y) * sign * kMinusOne;
                    if (!(numer < kZero)) {
                        hkReal denom = (((n.z * dir.z + n.y * dir.y) + dir.x * n.x) * sign) * kMinusOne;
                        if (!(denom * output.m_hitFraction <= numer)) {
                            hkReal tc = numer / denom;
                            hkReal omt = kOne - tc;
                            hkVector4 c;
                            hkReal c0 = tc * input.m_to.x + omt * input.m_from.x;
                            c.y = hkRound(tc * input.m_to.y + omt * input.m_from.y);
                            c.z = hkRound(tc * input.m_to.z + omt * input.m_from.z);
                            hkReal cx = c0 - e.x;
                            hkReal cy = c.y - e.y;
                            hkReal cz = c.z - e.z;
                            if (!(cx * cx + cy * cy + cz * cz > radiusSqrd)) {
                                output.m_shapeKey = 0xffffffff;
                                output.m_normal.x = n.x * sign;
                                output.m_normal.y = n.y * sign;
                                output.m_normal.z = n.z * sign;
                                output.m_normal.w = n.w * sign;
                                output.m_hitFraction = tc;
                                HK_TIMER_END();
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
miss:
    HK_TIMER_END();
    return false;
}
