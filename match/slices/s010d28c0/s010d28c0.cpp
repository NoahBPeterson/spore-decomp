// Slice s010d28c0: Havok 3.1.0 capsule-triangle collision agent (VC .NET 2003 build).
//
//   010d28c0  hkCapsuleTriangleAgent::processCollision        (virtual)
//   010d2d80  hkCapsuleTriangleAgent::getClosestPoints        (virtual)
//   010d32a0  hkCapsuleTriangleAgent::staticGetClosestPoints  (static)
//
// Flags: /vc71 /O2 /MD /Gy /TP   (Havok was built by VC .NET 2003: x87 floats,
// 16-byte aligned frames, no /GS cookie).
//
// All three build the capsule segment and the triangle vertices in world space
// (row-of-a-column-major transform), call hkCollideCapsuleUtilManifoldCapsVsTriangle
// (0x01107270) and then consume the resulting manifold.
#include "types.h"
#include <intrin.h>

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkTtrcCapsuleTri[];               // 0x014a4620 ("TtCapsuleTri")
extern const char hkTtrcCapsTriangle[];             // 0x014a4630 ("TtCapsTriangle")
extern const char hkTtrcEnd[];                      // 0x0149cc34

// Monitor-stream timer command: push a (tag, rdtsc) pair on the thread-local
// monitor stream when the current pointer has not reached the end pointer.
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

struct __declspec(align(16)) hkVector4
{
    float x, y, z, w;
};

class hkCdBody
{
public:
    const void*     m_shape;        // +0
    unsigned        m_shapeKey;     // +4
    const void*     m_motion;       // +8  (the hkTransform)
    const hkCdBody* m_parent;       // +0xc
};

struct hkCollisionInput
{
    int   m_pad0;                   // +0
    int   m_pad1;                   // +4
    float m_tolerance;              // +8
};

struct hkProcessCollisionInput
{
    int   m_pad0;                   // +0
    int   m_pad1;                   // +4
    float m_tolerance;              // +8
};

struct hkProcessCollisionOutput
{
    void* m_firstContactPoint;      // +0
    int   m_pad[7];
    hkVector4 m_separatingNormal;   // +0x20
    int   m_contactPointCount;      // +0x3034
};

class hkContactPoint
{
public:
    hkVector4 m_position;           // +0
    hkVector4 m_separatingNormal;   // +0x10
};

class hkCdPointCollector
{
public:
    virtual ~hkCdPointCollector() {}
    virtual void addCdPoint(const void* point) = 0;   // slot 1 (+4)
    float m_earlyOutDistance;                         // +4
};

// agent+8 = contact manager; slots 2 (+8) addPoint, 4 (+0x10) removePoint.
class hkContactMgr
{
public:
    virtual void v0();                                                                   // +0x00
    virtual void v1();                                                                   // +0x04
    virtual unsigned short addPoint(const void*, const void*, const void*, const void*); // +0x08
    virtual void v3();                                                                   // +0x0c
    virtual void removePoint(unsigned short key);                                        // +0x10
};

// capsule-vs-triangle manifold: three 0x20-byte contacts (position + normal).
struct hkCapsTriangleManifold
{
    hkContactPoint m_contact[3];    // +0, +0x20, +0x40
};

class hkTransform
{
public:
    hkVector4 m_basis[3];           // +0, +0x10, +0x20
    hkVector4 m_translation;        // +0x30
};

class hkCapsuleShape
{
public:
    char      m_pad[0xc];
    float     m_radius;             // +0xc
    hkVector4 m_vertexA;            // +0x10
    hkVector4 m_vertexB;            // +0x20
};

class hkTriangleShape
{
public:
    char      m_pad[0xc];
    float     m_radius;             // +0xc
    hkVector4 m_vertexA;            // +0x10
    hkVector4 m_vertexB;            // +0x20
    hkVector4 m_vertexC;            // +0x30
};

// out = R * v + t (transform copied to scalars first, w cleared), x87 spelling.
#define HK_XFORM_ONE(O, I, T) { \
        const float x = (I).x, y = (I).y, z = (I).z; \
        const float m00 = (T).m_basis[0].x, m01 = (T).m_basis[0].y, m02 = (T).m_basis[0].z; \
        const float m10 = (T).m_basis[1].x, m11 = (T).m_basis[1].y, m12 = (T).m_basis[1].z; \
        const float m20 = (T).m_basis[2].x, m21 = (T).m_basis[2].y, m22 = (T).m_basis[2].z; \
        const float tx = (T).m_translation.x, ty = (T).m_translation.y, tz = (T).m_translation.z; \
        (O).x = (m00 * x + (m10 * y + m20 * z)) + tx; \
        (O).y = (m01 * x + (m11 * y + m21 * z)) + ty; \
        (O).z = (m02 * x + (m12 * y + m22 * z)) + tz; \
        (O).w = 0.0f; }

// hkCollideCapsuleUtil::manifoldCapsVsTriangle, cdecl.
extern "C" void __cdecl hkCollideCapsuleUtilManifoldCapsVsTriangle(
    const hkVector4* capSegment, float capRadius,
    const hkVector4* triangle, float triRadius,
    const void* cache, float extraRadius, int singleCheck,
    void* out);                                          // 0x01107270

// hkCollideTriangleUtil::setupPointTriangleDistanceCache, cdecl.
extern "C" void __cdecl hkCollideTriangleUtilSetupCache(const hkVector4* triangle, void* cache);  // 0x01105e90

class hkCapsuleTriangleAgent
{
public:
    virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                  const hkProcessCollisionInput& input,
                                  hkProcessCollisionOutput& output);            // 0x010d28c0
    virtual void getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                  const hkCollisionInput& input,
                                  hkCdPointCollector& collector);               // 0x010d2d80
    static void staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                       const hkCollisionInput& input,
                                       hkCdPointCollector& collector);          // 0x010d32a0

    int            m_pad4;              // +4
    hkContactMgr*  m_contactMgr;        // +8
    unsigned short m_keys[3];           // +0xc
    unsigned short m_pad12;             // +0x12
    char           m_cache[0x40];       // +0x14  (hkCapsuleTriangleUtil::ShapeCache)
};

// ===========================================================================
// @ 0x010d28c0
// processCollision: build world-space capsule segment + triangle, run the
// capsule-vs-triangle manifold util, then reconcile the three contacts with
// the contact manager (add on a new penetrating contact, remove when separated)
// and append each new contact point to the output buffer (stride 0x30).
// ===========================================================================
void hkCapsuleTriangleAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                              const hkProcessCollisionInput& input,
                                              hkProcessCollisionOutput& output)
{
    hkTimerCommand(hkTtrcCapsuleTri);

    const hkCapsuleShape*  cap = (const hkCapsuleShape*)bodyA.m_shape;
    const hkTriangleShape* tri = (const hkTriangleShape*)bodyB.m_shape;
    const hkTransform& capXf = *(const hkTransform*)bodyA.m_motion;
    const hkTransform& triXf = *(const hkTransform*)bodyB.m_motion;

    hkVector4 capSeg[2];
    HK_XFORM_ONE(capSeg[0], cap->m_vertexA, capXf)
    HK_XFORM_ONE(capSeg[1], cap->m_vertexB, capXf)

    hkVector4 triVerts[3];
    HK_XFORM_ONE(triVerts[0], tri->m_vertexA, triXf)
    HK_XFORM_ONE(triVerts[1], tri->m_vertexB, triXf)
    HK_XFORM_ONE(triVerts[2], tri->m_vertexC, triXf)

    hkCapsTriangleManifold manifold;
    hkCollideCapsuleUtilManifoldCapsVsTriangle(capSeg, cap->m_radius, triVerts, tri->m_radius,
                                               (char*)this + 0x14, input.m_tolerance, 1, &manifold);

    hkContactMgr* mgr = *(hkContactMgr**)((char*)this + 8);
    unsigned short* keys = (unsigned short*)((char*)this + 0xc);
    for (int i = 0; i < 3; i++, keys++)
    {
        const hkContactPoint& c = manifold.m_contact[i];
        if (c.m_separatingNormal.w < input.m_tolerance)
        {
            if (*keys == 0xffff)
            {
                unsigned short k = mgr->addPoint(&bodyA, &bodyB, &input, &c);
                *keys = k;
                if (k == 0xffff)
                    continue;
            }
            hkContactPoint* p = (hkContactPoint*)output.m_firstContactPoint;
            output.m_firstContactPoint = (char*)p + 0x30;
            p->m_position = c.m_position;
            p->m_separatingNormal = c.m_separatingNormal;
            *(unsigned short*)((char*)p + 0x20) = *keys;
        }
        else
        {
            if (*keys != 0xffff)
            {
                mgr->removePoint(*keys);
                *keys = 0xffff;
            }
        }
    }

    hkTimerCommand(hkTtrcEnd);
}

// ===========================================================================
// @ 0x010d2d80
// getClosestPoints: same manifold build; report the deeper of the first two
// contacts through the point collector when it is within tolerance.
// ===========================================================================
void hkCapsuleTriangleAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                              const hkCollisionInput& input,
                                              hkCdPointCollector& collector)
{
    hkTimerCommand(hkTtrcCapsTriangle);

    const hkCapsuleShape*  cap = (const hkCapsuleShape*)bodyA.m_shape;
    const hkTriangleShape* tri = (const hkTriangleShape*)bodyB.m_shape;
    const hkTransform& capXf = *(const hkTransform*)bodyA.m_motion;
    const hkTransform& triXf = *(const hkTransform*)bodyB.m_motion;

    hkVector4 capSeg[2];
    HK_XFORM_ONE(capSeg[0], cap->m_vertexA, capXf)
    HK_XFORM_ONE(capSeg[1], cap->m_vertexB, capXf)

    hkVector4 triVerts[3];
    HK_XFORM_ONE(triVerts[0], tri->m_vertexA, triXf)
    HK_XFORM_ONE(triVerts[1], tri->m_vertexB, triXf)
    HK_XFORM_ONE(triVerts[2], tri->m_vertexC, triXf)

    hkCapsTriangleManifold manifold;
    hkCollideCapsuleUtilManifoldCapsVsTriangle(capSeg, cap->m_radius, triVerts, tri->m_radius,
                                               (char*)this + 0x14, input.m_tolerance, 0, &manifold);

    if (manifold.m_contact[1].m_separatingNormal.w < manifold.m_contact[0].m_separatingNormal.w)
    {
        if (manifold.m_contact[1].m_separatingNormal.w < input.m_tolerance)
            collector.addCdPoint(&manifold.m_contact[1]);
    }
    else
    {
        if (manifold.m_contact[0].m_separatingNormal.w < input.m_tolerance)
            collector.addCdPoint(&manifold.m_contact[0]);
    }

    hkTimerCommand(hkTtrcEnd);
}

// ===========================================================================
// @ 0x010d32a0
// staticGetClosestPoints: identical to getClosestPoints but the triangle
// shape's local vertices are cached first (this has no agent state).
// ===========================================================================
void hkCapsuleTriangleAgent::staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                    const hkCollisionInput& input,
                                                    hkCdPointCollector& collector)
{
    hkTimerCommand(hkTtrcCapsTriangle);

    const hkCapsuleShape*  cap = (const hkCapsuleShape*)bodyA.m_shape;
    const hkTriangleShape* tri = (const hkTriangleShape*)bodyB.m_shape;
    const hkTransform& capXf = *(const hkTransform*)bodyA.m_motion;
    const hkTransform& triXf = *(const hkTransform*)bodyB.m_motion;

    char cache[0x40];
    hkCollideTriangleUtilSetupCache((const hkVector4*)((const char*)bodyB.m_shape + 0x10), cache);

    hkVector4 capSeg[2];
    HK_XFORM_ONE(capSeg[0], cap->m_vertexA, capXf)
    HK_XFORM_ONE(capSeg[1], cap->m_vertexB, capXf)

    hkVector4 triVerts[3];
    HK_XFORM_ONE(triVerts[0], tri->m_vertexA, triXf)
    HK_XFORM_ONE(triVerts[1], tri->m_vertexB, triXf)
    HK_XFORM_ONE(triVerts[2], tri->m_vertexC, triXf)

    hkCapsTriangleManifold manifold;
    hkCollideCapsuleUtilManifoldCapsVsTriangle(capSeg, cap->m_radius, triVerts, tri->m_radius,
                                               cache, input.m_tolerance, 0, &manifold);

    if (manifold.m_contact[1].m_separatingNormal.w < manifold.m_contact[0].m_separatingNormal.w)
    {
        if (manifold.m_contact[1].m_separatingNormal.w < input.m_tolerance)
            collector.addCdPoint(&manifold.m_contact[1]);
    }
    else
    {
        if (manifold.m_contact[0].m_separatingNormal.w < input.m_tolerance)
            collector.addCdPoint(&manifold.m_contact[0]);
    }

    hkTimerCommand(hkTtrcEnd);
}
