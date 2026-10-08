// Slice s010cfcf0 -- Havok 3.1.0 hkMultiSphereTriangleAgent::processCollision (0x010d0130).
// Opens a "TtMultiSphereTri" monitor timer, transforms the triangle's 3 vertices and the multi-sphere's
// spheres into world space, then for every sphere computes the closest point on the triangle.  If the distance
// is below (sphere radius + triangle radius + tolerance) it appends a contact point (position, separating normal
// with w = distance - radiusSum) to the output, asking the contact manager for a point id when the sphere has
// none yet; otherwise it releases the sphere's previously allocated contact point id.
// Note the agent's id slot for sphere i is m_contactPointId[numSpheres - 1 - i] in the binary.
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <intrin.h>
#pragma intrinsic(__rdtsc)

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorTimerEndTag[];           // 0x0149cc34 ("Et")
extern const char hkTtMultiSphereTri[];             // 0x014a4570 ("TtMultiSphereTri")
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

typedef unsigned short hkContactPointId;
struct hkProcessCollisionInput : hkCollisionInput { };
struct hkProcessCdPoint { hkContactPoint m_contact; hkContactPointId m_id; char m_pad[14]; };   // 0x30 bytes
struct hkProcessCollisionOutput { hkProcessCdPoint* m_firstFreeContactPoint; };                  // +0x0
class hkContactMgr
{
public:
    virtual void pad0();
    virtual void pad1();
    virtual hkContactPointId addContactPoint(const hkCdBody& a, const hkCdBody& b, const hkProcessCollisionInput& input,
                                             hkProcessCdPoint& cp);                  // +0x08
    virtual void pad3();
    virtual void removeContactPoint(hkContactPointId id);                            // +0x10
};

class hkMultiSphereTriangleAgent
{
public:
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkProcessCollisionInput& input,
                                  hkProcessCollisionOutput& result);                   // 0x010d0130
    int                m_pad4;                                                         // +4 refcount
    hkContactMgr*      m_contactMgr;                                                   // +8
    hkCollideTriangleUtil::ClosestPointTriangleCache m_closestPointTriangleCache;     // +0xc
    hkContactPointId   m_contactPointId[8];                                            // +0x1c
};

// @ 0x010d0130
void hkMultiSphereTriangleAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                  const hkProcessCollisionInput& input,
                                                  hkProcessCollisionOutput& result)
{
    hkTimerCommand(hkTtMultiSphereTri);

    const hkMultiSphereShape* sphereShapeA = (const hkMultiSphereShape*)bodyA.m_shape;
    const hkTriangleShape* triangleShapeB = (const hkTriangleShape*)bodyB.m_shape;

    hkVector4 vertices[3];
    transformPoints(*bodyB.m_motion, triangleShapeB->m_vertices, 3, vertices);

    const int numSpheres = sphereShapeA->m_numSpheres;
    hkVector4 spheres[8];
    transformPoints(*bodyA.m_motion, sphereShapeA->m_spheres, numSpheres, spheres);

    hkCollideTriangleUtil::ClosestPointTriangleResult res;
    for (int i = 0; i < numSpheres; i++)
    {
        hkContactPointId& id = m_contactPointId[numSpheres - 1 - i];
        float radiusSum = sphereShapeA->m_spheres[i].w + triangleShapeB->m_radius;
        hkCollideTriangleUtil::closestPointTriangle(spheres[i], vertices, m_closestPointTriangleCache, res);
        if (res.distance < radiusSum + input.m_tolerance)
        {
            const float k = triangleShapeB->m_radius - res.distance;
            hkProcessCdPoint* cp = result.m_firstFreeContactPoint;
            cp->m_contact.m_position = spheres[i];
            cp->m_contact.m_position.x = res.hitDirection.x * k + cp->m_contact.m_position.x;
            cp->m_contact.m_position.y = res.hitDirection.y * k + cp->m_contact.m_position.y;
            cp->m_contact.m_position.z = res.hitDirection.z * k + cp->m_contact.m_position.z;
            cp->m_contact.m_position.w = res.hitDirection.w * k + cp->m_contact.m_position.w;
            cp->m_contact.m_separatingNormal = res.hitDirection;
            cp->m_contact.m_separatingNormal.w = res.distance - radiusSum;
            if (id == 0xffff)
            {
                id = m_contactMgr->addContactPoint(bodyA, bodyB, input, *cp);
                if (id == 0xffff)
                    continue;
            }
            result.m_firstFreeContactPoint = (hkProcessCdPoint*)((char*)result.m_firstFreeContactPoint + 0x30);
            cp->m_id = id;
        }
        else if (id != 0xffff)
        {
            m_contactMgr->removeContactPoint(id);
            id = 0xffff;
        }
    }

    hkTimerCommand(hkMonitorTimerEndTag);
}
