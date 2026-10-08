// Slice s010d0920: Havok 3.1.0 hkMultiSphereTriangleAgent::getClosestPoints (0x010d0920, member: uses the agent's
// cached triangle terms) and ::staticGetClosestPoints (0x010d1100, builds the cache on the stack).
// Both open a "TtMultiSphereTriangle" monitor timer, transform the triangle's 3 vertices and the multi-sphere's
// spheres into world space (hkVector4Util::transformPoints, unrolled by 4 in the binary), then for every sphere
// compute the closest point on the triangle and, if the distance is below (sphere radius + triangle radius +
// tolerance), report a hkCdPoint (position = sphere + hitDirection * (triRadius - distance), separating normal =
// hitDirection with w = distance - radiusSum) to the collector.  MSVC 2008 SP1, x87 floats, 16-byte aligned frame.
// Flags: /O2 /MD /Gy /TP.
#include "types.h"
#include <intrin.h>
#pragma intrinsic(__rdtsc)

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorTimerEndTag[];           // 0x0149cc34 ("Et")
extern const char hkTtMultiSphereTriangle[];        // 0x014a4584 ("TtMultiSphereTriangle")
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

class __declspec(align(16)) hkVector4 { public: float x, y, z, w; };
struct hkVector3 { float x, y, z; };
struct hkTransform { hkVector4 m_col0, m_col1, m_col2, m_translation; };   // 0x40 bytes

// ---- shapes ----
struct hkShape { virtual ~hkShape(); int m_pad[2]; };                                         // 0xc bytes
struct hkConvexShape : hkShape { float m_radius; };                                              // radius +0xc
struct hkTriangleShape : hkConvexShape { hkVector4 m_vertices[3]; };                              // vertices +0x10
struct hkMultiSphereShape : hkShape { int m_numSpheres; hkVector4 m_spheres[8]; };               // count +0xc, spheres +0x10

class hkCdBody
{
public:
    const hkShape* m_shape;        // +0
    unsigned       m_shapeKey;     // +4
    const hkTransform* m_motion;   // +8
    const hkCdBody* m_parent;      // +0xc
};
struct hkCollisionInput { int pad[2]; float m_tolerance; };   // tolerance +8
struct hkContactPoint { hkVector4 m_position; hkVector4 m_separatingNormal; };   // w = distance
struct hkCdPoint { hkContactPoint m_contact; const hkCdBody* m_cdBodyA; const hkCdBody* m_cdBodyB; };   // 0x28 bytes
class hkCdPointCollector
{
public:
    virtual ~hkCdPointCollector() {}
    virtual void addCdPoint(const hkCdPoint& point) = 0;                     // slot 1
    float m_earlyOutDistance;
};

struct hkCollideTriangleUtil
{
    struct ClosestPointTriangleCache { float m_QQ, m_RR, m_QR, m_invTriNormal; };
    struct ClosestPointTriangleResult { hkVector4 hitDirection; float distance; };
    enum ClosestPointTriangleStatus { HIT_TRIANGLE_FACE = 0, HIT_TRIANGLE_EDGE };
    static void __cdecl setupClosestPointTriangleCache(const hkVector4* triangle, ClosestPointTriangleCache& cache);   // 0x01105d80
    static ClosestPointTriangleStatus __cdecl closestPointTriangle(const hkVector4& position, const hkVector4* tri,
        const ClosestPointTriangleCache& cache, ClosestPointTriangleResult& result);                                     // 0x01106010
};

// hkVector4Util::transformPoints: out[i] = R * in[i] + t, w cleared. The transform is copied to scalars first
// (x87 build, unrolled by 4 as in the binary).
#define HK_XFORM_ONE(O, I) { \
        const float x = (I).x, y = (I).y, z = (I).z; \
        (O).x = (m00 * x + (m10 * y + m20 * z)) + tx; \
        (O).y = (m01 * x + (m11 * y + m21 * z)) + ty; \
        (O).z = (m02 * x + (m12 * y + m22 * z)) + tz; \
        (O).w = 0.0f; }
static __forceinline void transformPoints(const hkTransform& t, const hkVector4* in, int n, hkVector4* out)
{
    const float m00 = t.m_col0.x, m01 = t.m_col0.y, m02 = t.m_col0.z;
    const float m10 = t.m_col1.x, m11 = t.m_col1.y, m12 = t.m_col1.z;
    const float m20 = t.m_col2.x, m21 = t.m_col2.y, m22 = t.m_col2.z;
    const float tx = t.m_translation.x, ty = t.m_translation.y, tz = t.m_translation.z;
    int i = 0;
    if (n >= 4)
    {
        int blocks = ((n - 4) >> 2) + 1;
        i = blocks * 4;
        const hkVector4* p = in;
        hkVector4* q = out;
        do {
            HK_XFORM_ONE(q[0], p[0]) HK_XFORM_ONE(q[1], p[1]) HK_XFORM_ONE(q[2], p[2]) HK_XFORM_ONE(q[3], p[3])
            p += 4; q += 4;
        } while (--blocks);
    }
    for (; i < n; ++i)
        HK_XFORM_ONE(out[i], in[i])
}

class hkMultiSphereTriangleAgent
{
public:
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input,
                                  hkCdPointCollector& collector);                          // 0x010d0920
    static void staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input,
                                       hkCdPointCollector& collector);                     // 0x010d1100
    int m_pad[2];                                                                          // +4 refcount, +8 contactMgr
    hkCollideTriangleUtil::ClosestPointTriangleCache m_closestPointTriangleCache;         // +0xc
};

#define HK_REPORT_CLOSEST(SPH, I, CACHE) \
    { \
        volatile float radiusSum = sphereShapeA->m_spheres[I].w + triangleShapeB->m_radius; \
        hkCollideTriangleUtil::closestPointTriangle(SPH[I], vertices, CACHE, result); \
        if (result.distance < radiusSum + input.m_tolerance) \
        { \
            const float k = triangleShapeB->m_radius - result.distance; \
            point.m_contact.m_position.x = result.hitDirection.x * k + SPH[I].x; \
            point.m_contact.m_position.y = result.hitDirection.y * k + SPH[I].y; \
            point.m_contact.m_position.z = result.hitDirection.z * k + SPH[I].z; \
            point.m_contact.m_position.w = result.hitDirection.w * k + SPH[I].w; \
            point.m_contact.m_separatingNormal.x = result.hitDirection.x; \
            point.m_contact.m_separatingNormal.y = result.hitDirection.y; \
            point.m_contact.m_separatingNormal.z = result.hitDirection.z; \
            point.m_contact.m_separatingNormal.w = result.distance - radiusSum; \
            collector.addCdPoint(point); \
        } \
    }

// @ 0x010d0920
void hkMultiSphereTriangleAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                  const hkCollisionInput& input, hkCdPointCollector& collector)
{
    hkTimerCommand(hkTtMultiSphereTriangle);

    const hkMultiSphereShape* sphereShapeA = (const hkMultiSphereShape*)bodyA.m_shape;
    const hkTriangleShape* triangleShapeB = (const hkTriangleShape*)bodyB.m_shape;

    hkVector4 vertices[3];
    transformPoints(*bodyB.m_motion, triangleShapeB->m_vertices, 3, vertices);

    const int numSpheres = sphereShapeA->m_numSpheres;
    hkVector4 spheres[8];
    transformPoints(*bodyA.m_motion, sphereShapeA->m_spheres, numSpheres, spheres);

    hkCdPoint point;
    point.m_cdBodyA = &bodyA;
    point.m_cdBodyB = &bodyB;

    hkCollideTriangleUtil::ClosestPointTriangleResult result;
    for (int i = 0; i < numSpheres; i++)
        HK_REPORT_CLOSEST(spheres, i, m_closestPointTriangleCache)

    hkTimerCommand(hkMonitorTimerEndTag);
}

// @ 0x010d1100
void hkMultiSphereTriangleAgent::staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                        const hkCollisionInput& input, hkCdPointCollector& collector)
{
    hkTimerCommand(hkTtMultiSphereTriangle);

    const hkMultiSphereShape* sphereShapeA = (const hkMultiSphereShape*)bodyA.m_shape;
    const hkTriangleShape* triangleShapeB = (const hkTriangleShape*)bodyB.m_shape;

    hkVector4 vertices[3];
    transformPoints(*bodyB.m_motion, triangleShapeB->m_vertices, 3, vertices);

    const int numSpheres = sphereShapeA->m_numSpheres;
    hkVector4 spheres[8];
    transformPoints(*bodyA.m_motion, sphereShapeA->m_spheres, numSpheres, spheres);

    hkCdPoint point;
    point.m_cdBodyA = &bodyA;
    point.m_cdBodyB = &bodyB;

    hkCollideTriangleUtil::ClosestPointTriangleCache cache;
    hkCollideTriangleUtil::setupClosestPointTriangleCache(triangleShapeB->m_vertices, cache);

    hkCollideTriangleUtil::ClosestPointTriangleResult result;
    for (int i = 0; i < numSpheres; i++)
        HK_REPORT_CLOSEST(spheres, i, cache)

    hkTimerCommand(hkMonitorTimerEndTag);
}
