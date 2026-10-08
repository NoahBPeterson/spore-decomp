// Slice s010d18c0: Havok 3.1.0 hkMultiSphereTriangleAgent::getPenetrations (0x010d18c0, member, uses the agent's
// cached triangle terms) and ::staticGetPenetrations (0x010d1f40, builds the cache on the stack).
// Both transform the triangle's 3 vertices and the multi-sphere's spheres into world space (hkVector4Util::
// transformPoints, unrolled by 4 in the binary) and report the pair to the collector on the first sphere whose
// closest-point distance to the triangle is below (sphere radius + triangle radius).
// MSVC 2008 SP1, x87 floats, 16-byte aligned frame.
#include "types.h"

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
struct hkCollisionInput { int pad; };
class hkCdBodyPairCollector
{
public:
    virtual ~hkCdBodyPairCollector() {}
    virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b) = 0;     // slot 1
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
    virtual void getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input,
                                 hkCdBodyPairCollector& collector);                       // 0x010d18c0
    static void staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input,
                                      hkCdBodyPairCollector& collector);                  // 0x010d1f40
    int m_pad[2];                                                                          // +4 refcount, +8 contactMgr
    hkCollideTriangleUtil::ClosestPointTriangleCache m_closestPointTriangleCache;         // +0xc
};

// @ 0x010d18c0
void hkMultiSphereTriangleAgent::getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                 const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
    const hkMultiSphereShape* sphereShapeA = (const hkMultiSphereShape*)bodyA.m_shape;
    const hkTriangleShape* triangleShapeB = (const hkTriangleShape*)bodyB.m_shape;

    hkVector4 vertices[3];
    transformPoints(*bodyB.m_motion, triangleShapeB->m_vertices, 3, vertices);

    const int numSpheres = sphereShapeA->m_numSpheres;
    hkVector4 spheres[8];
    transformPoints(*bodyA.m_motion, sphereShapeA->m_spheres, numSpheres, spheres);

    hkCollideTriangleUtil::ClosestPointTriangleResult result;
    for (int i = 0; i < numSpheres; i++)
    {
        const float radiusSum = sphereShapeA->m_spheres[i].w + triangleShapeB->m_radius;
        hkCollideTriangleUtil::closestPointTriangle(spheres[i], vertices, m_closestPointTriangleCache, result);
        if (result.distance < radiusSum)
        {
            collector.addCdBodyPair(bodyA, bodyB);
            return;
        }
    }
}

// @ 0x010d1f40
void hkMultiSphereTriangleAgent::staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                       const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
    const hkMultiSphereShape* sphereShapeA = (const hkMultiSphereShape*)bodyA.m_shape;
    const hkTriangleShape* triangleShapeB = (const hkTriangleShape*)bodyB.m_shape;

    hkVector4 vertices[3];
    transformPoints(*bodyB.m_motion, triangleShapeB->m_vertices, 3, vertices);

    const int numSpheres = sphereShapeA->m_numSpheres;
    hkVector4 spheres[8];
    transformPoints(*bodyA.m_motion, sphereShapeA->m_spheres, numSpheres, spheres);

    hkCollideTriangleUtil::ClosestPointTriangleCache cache;
    hkCollideTriangleUtil::setupClosestPointTriangleCache(triangleShapeB->m_vertices, cache);

    hkCollideTriangleUtil::ClosestPointTriangleResult result;
    for (int i = 0; i < numSpheres; i++)
    {
        const float radiusSum = sphereShapeA->m_spheres[i].w + triangleShapeB->m_radius;
        hkCollideTriangleUtil::closestPointTriangle(spheres[i], vertices, cache, result);
        if (result.distance < radiusSum)
        {
            collector.addCdBodyPair(bodyA, bodyB);
            return;
        }
    }
}
