// Slice s010c2890: Havok 3.1.0 hkCapsuleShape::castRay (0x010c2e30).
// Ray against a capsule (segment A..B plus radius r), x87 build. If the ray start is inside the capsule the cast
// fails. Otherwise the ray is intersected with the infinite cylinder around the segment (closest approach of the two
// infinite lines gives the entry fraction); the hit is accepted when it falls between the two end points of the
// segment and in front of the best fraction so far. A miss of the cylinder body falls back to a ray cast against a
// temporary hkSphereShape placed at the nearer end point (A when the along-axis position is <= 0, else B).
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP (Havok objects were built by VC .NET 2003).
#include "types.h"
#include <intrin.h>
#include <math.h>

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorTimerEndTag[];           // 0x0149cc34
extern const char hkTtrcCapsule[];                  // 0x014a28bc ("TtrcCapsule")
struct hkMonitorCommand { const char* m_command; uint32_t m_time0; uint32_t m_pad; };
static __forceinline void hkTimerCommand(const char* name)
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end)
    {
        hkMonitorCommand* c = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls);
        c->m_command = name;
        volatile uint32_t t = (uint32_t)__rdtsc();
        c->m_time0 = t;
        TlsSetValue(g_hkMonitorStreamCurrentTls, c + 1);
    }
}

class hkBool
{
public:
    hkBool() {}
    hkBool(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
    char m_bool;
};

class __declspec(align(16)) hkVector4 { public: float x, y, z, w; };

struct hkShapeRayCastInput
{
    hkVector4 m_from;            // +0
    hkVector4 m_to;              // +0x10
    uint32_t m_filterInfo;       // +0x20
    void* m_rayShapeCollectionFilter;   // +0x24
};
struct hkShapeRayCastOutput
{
    float m_normal[4];           // +0
    uint32_t m_shapeKey;         // +0x10
    float m_hitFraction;         // +0x14
};

class hkShape
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const;   // slot 5
    uint32_t m_memSizeAndFlags;
    uint32_t m_userData;
};

class hkSphereShape : public hkShape
{
public:
    hkSphereShape(float radius);   // 0x010c3770                                                      // 0x010c3770
    virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const;   // 0x010c3880
    float m_radius;
};

class hkCapsuleShape : public hkShape
{
public:
    virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const;   // slot 5
    // 0x010c2ad0 (cdecl): closest point on segment A..B to p
    static void closestPointLineSeg(const hkVector4& p, const hkVector4& a, const hkVector4& b, hkVector4& out);
    // 0x010c2890 (cdecl): closest points between two infinite lines (A + s*dA, B + t*dB)
    static void closestInfLineSegInfLineSeg(const hkVector4& a, const hkVector4& dA, const hkVector4& b,
                                            const hkVector4& dB, float& distSq, float& s, float& t,
                                            hkVector4& pA, hkVector4& pB);
    float m_radius;              // +0x0c
    hkVector4 m_vertexA;         // +0x10
    hkVector4 m_vertexB;         // +0x20
};

#define HK_EPS 1.1920929e-07f

// @ 0x010c2e30
hkBool hkCapsuleShape::castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const
{
    hkTimerCommand(hkTtrcCapsule);

    const hkVector4& A = m_vertexA;
    const hkVector4& B = m_vertexB;
    const hkVector4& from = input.m_from;
    const hkVector4& to = input.m_to;

    {
        hkVector4 pt;
        hkCapsuleShape::closestPointLineSeg(from, A, B, pt);
        const float dx = from.x - pt.x, dy = from.y - pt.y, dz = from.z - pt.z;
        const float dist = (float)sqrt(dx * dx + dz * dz + dy * dy);
        if (dist < m_radius)
            goto fail;
    }

    {
        hkVector4 d;
        d.x = to.x - from.x; d.y = to.y - from.y; d.z = to.z - from.z; d.w = to.w - from.w;
        hkVector4 e;
        e.x = B.x - A.x; e.y = B.y - A.y; e.z = B.z - A.z; e.w = B.w - A.w;

        float distSq = 3.40282e+38f;
        float tRay, tSeg;
        hkVector4 pA, pB;
        hkCapsuleShape::closestInfLineSegInfLineSeg(from, d, A, e, distSq, tRay, tSeg, pA, pB);

        const float r2 = m_radius * m_radius;
        if (distSq > r2)
            goto fail;

        // unit axis a and its length
        float ax, ay, az, len;
        const float len2 = e.x * e.x + e.z * e.z + e.y * e.y;
        if (len2 > HK_EPS)
        {
            len = (float)sqrt(len2);
            const float inv = 1.0f / len;
            ax = e.x * inv; ay = e.y * inv; az = e.z * inv;
        }
        else
        {
            ax = 0.0f; ay = 0.0f; az = 0.0f;
            len = 0.0f;
        }

        // component of the ray direction perpendicular to the axis
        const float s = -(d.x * ax + d.z * az + d.y * ay);
        const float px = ax * s + d.x;
        const float py = ay * s + d.y;
        const float pz = az * s + d.z;
        const float h = (float)sqrt(m_radius * m_radius - distSq);
        const float q = px * px + pz * pz + py * py;
        float invq;
        if (q == 0.0f) invq = 0.0f; else invq = 1.0f / (float)sqrt(q);
        const float f = tRay - invq * h;           // entry fraction on the cylinder

        float along;
        if (!(f >= output.m_hitFraction))
        {
            const float ap = az * A.z + ay * A.y + ax * A.x;
            const float omf = 1.0f - f;
            hkVector4 hit;
            hit.x = omf * from.x + f * to.x;
            hit.y = f * to.y + omf * from.y;
            hit.z = f * to.z + omf * from.z;
            hit.w = f * to.w + omf * from.w;
            along = (hit.x * ax + hit.z * az + hit.y * ay) - ap;

            if (f >= 0.0f && along > 0.0f && along < len)
            {
                const float u = along / len;
                const float omu = 1.0f - u;
                hkVector4 sp;
                sp.x = u * B.x + omu * A.x;
                sp.y = omu * A.y + u * B.y;
                sp.z = omu * A.z + u * B.z;
                sp.w = omu * A.w + u * B.w;
                hkVector4 nrm;
                nrm.x = hit.x - sp.x;
                nrm.y = hit.y - sp.y;
                nrm.z = hit.z - sp.z;
                nrm.w = hit.w - sp.w;
                const float nq = nrm.x * nrm.x + nrm.z * nrm.z + nrm.y * nrm.y;
                float invn;
                if (nq == 0.0f) invn = 0.0f; else invn = 1.0f / (float)sqrt(nq);
                output.m_shapeKey = 0xffffffff;
                nrm.y = nrm.y * invn; output.m_normal[1] = nrm.y;
                nrm.z = nrm.z * invn; output.m_normal[2] = nrm.z;
                output.m_hitFraction = f;
                nrm.w = nrm.w * invn; output.m_normal[3] = nrm.w;
                output.m_normal[0] = nrm.x * invn;
                hkTimerCommand(hkMonitorTimerEndTag);
                return true;
            }

            // missed the cylinder body: test the nearer end cap sphere
            const float v = ((ax * from.x + az * from.z + ay * from.y) - ap) / len;
            const float omv = 1.0f - v;
            hkVector4 cp;
            cp.x = omv * A.x + v * B.x;
            cp.y = omv * A.y + v * B.y;
            cp.z = omv * A.z + v * B.z;
            const float ex = from.x - cp.x, ey = from.y - cp.y, ez = from.z - cp.z;
            const float cd = (float)sqrt(ez * ez + ey * ey + ex * ex);
            if (cd > m_radius && f < 0.0f)
                goto fail;

            hkShapeRayCastInput sin;
            sin.m_filterInfo = 0;
            sin.m_rayShapeCollectionFilter = 0;
            const hkVector4& c = (along <= 0.0f) ? A : B;
            sin.m_from.x = from.x - c.x; sin.m_from.y = from.y - c.y; sin.m_from.z = from.z - c.z; sin.m_from.w = from.w - c.w;
            sin.m_to.x = to.x - c.x; sin.m_to.y = to.y - c.y; sin.m_to.z = to.z - c.z; sin.m_to.w = to.w - c.w;
            hkSphereShape sphere(m_radius);
            hkTimerCommand(hkMonitorTimerEndTag);
            return sphere.castRay(sin, output);
        }
    }

fail:
    hkTimerCommand(hkMonitorTimerEndTag);
    return false;
}
