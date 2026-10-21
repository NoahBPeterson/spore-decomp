// Slice s010d6420: Havok 3.1.0 sphere-vs-triangle collision agent plus the
// symmetric sphere/box flip wrappers.
//
//  010d6420  hkSymmetricAgent<hkSphereBoxAgent>::processCollision  (flip wrapper)
//  010d6530  hkSphereTriangleAgent::createSphereTriangleAgent
//  010d6680  hkSphereTriangleAgent::createTriangleSphereAgent
//  010d66e0  hkSphereTriangleAgent::processCollision
//  010d6a80  hkSphereTriangleAgent::getClosestPoints
//  010d6e00  hkSphereTriangleAgent::staticGetClosestPoints
//  010d7190  hkSphereTriangleAgent::getPenetrations
//  010d7300  hkSphereTriangleAgent::staticGetPenetrations
//  010d7470  hkSymmetricAgent<hkSphereTriangleAgent>::getPenetrations wrapper
//  010d74f0  hkSymmetricAgent<hkSphereTriangleAgent>::getClosestPoints wrapper
//
// Flags: /vc71 /O2 /MD /Gy /TP  (Havok 3.1.0 was built by VC .NET 2003).
#include "types.h"
#include <intrin.h>

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkTtrcSphereTri[];                // 0x014a47b0 ("TtSphereTri")
extern const char hkTtrcEnd[];                      // 0x0149cc34

// ---------------------------------------------------------------------------
// Monitor-stream scope guard (shared with the other Havok collision slices).
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// shared types
// ---------------------------------------------------------------------------
struct __declspec(align(16)) hkVector4
{
    float x, y, z, w;
};

struct hkCdBody
{
    const void*     m_shape;        // +0
    unsigned        m_shapeKey;     // +4
    const void*     m_motion;       // +8
    const hkCdBody* m_parent;       // +0xc
};

struct hkCollisionInput
{
    int   m_pad0;                   // +0
    int   m_pad1;                   // +4
    float m_tolerance;              // +8
};

struct hkTransform
{
    hkVector4 m_basis[3];           // +0, +0x10, +0x20
    hkVector4 m_translation;        // +0x30
};

// sphere shape: radius at +0xc, center is the motion translation.
struct hkSphereShape
{
    char  m_pad[0xc];
    float m_radius;                 // +0xc
};

// triangle shape: radius at +0xc, three local vertices at +0x10/+0x20/+0x30.
struct hkTriangleShape
{
    char      m_pad[0xc];
    float     m_radius;             // +0xc
    hkVector4 m_vertex[3];          // +0x10, +0x20, +0x30
};

class hkCdPointCollector
{
public:
    virtual ~hkCdPointCollector() {}
    virtual void addCdPoint(const void* point) = 0;   // slot 1
    float m_earlyOutDistance;       // +4
};

class hkCdBodyPairCollector
{
public:
    virtual ~hkCdBodyPairCollector() {}
    virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b) = 0;   // slot 1
    char m_earlyOut;                // +4
    const void* m_extra;            // +8
};

class hkCollisionAgent
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
};

// hkContactPoint (0x30 with the separating normal at +0x10).
struct hkContactPoint
{
    hkVector4 m_position;           // +0
    hkVector4 m_separatingNormal;   // +0x10 (w = distance)
    hkVector4 m_pad;                // +0x20
    void setFlipped(const hkContactPoint& other);    // 0x010cecf0
};

struct hkProcessCdPoint { hkContactPoint m_contact; };  // 0x30 bytes (contact is 0x30)

typedef float hkTime;

struct hkProcessCollisionInput
{
    char  m_pad0[8];
    float m_tolerance;              // +8
};

struct hkProcessCollisionOutput
{
    hkProcessCdPoint* m_firstFreeContactPoint;  // +0
    char              m_pad0[0x10 - 4];
    hkContactPoint    m_toiContact;             // +0x10
    hkProcessCdPoint  m_contactPoints[256];     // +0x30
    hkTime            m_toiTime;                // +0x3034
};

// ---------------------------------------------------------------------------
// hkContactMgr: the agent holds a cached contact point index for the pair.
// ---------------------------------------------------------------------------
class hkContactMgr
{
public:
    virtual void v0();                                          // +0
    virtual void v1();                                          // +4
    virtual unsigned short createContactPoint(const hkCdBody&, const hkCdBody&,
                                              const hkProcessCollisionInput&,
                                              hkContactPoint*);  // +8
    virtual void v3();                                          // +0xc
    virtual void removeContactPoint(unsigned short index);      // +0x10
};

// ---------------------------------------------------------------------------
// hkMemory (allocates the collision agents)
// ---------------------------------------------------------------------------
class hkMemory
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void* alloc(int size, int cls);      // +0x10
};
extern hkMemory* hkMemory_s_instance;            // 0x016e4178

// ---------------------------------------------------------------------------
// hkCollideTriangleUtil
// ---------------------------------------------------------------------------
class hkCollideTriangleUtil
{
public:
    struct ClosestPointTriangleCache
    {
        hkVector4 m_rows[5];        // +0 .. +0x4f
    };

    struct ClosestPointTriangleResult
    {
        hkVector4 m_closestPoint;   // +0
        float     m_distance;       // +0x10
    };

    enum ClosestPointTriangleStatus { CPT_OK = 0 };

    static void setupClosestPointTriangleCache(const hkVector4* verts,
                                               ClosestPointTriangleCache& cache);  // 0x01105d80
    static ClosestPointTriangleStatus closestPointTriangle(const hkVector4& point,
                                                           const hkVector4* verts,
                                                           const ClosestPointTriangleCache& cache,
                                                           ClosestPointTriangleResult& result); // 0x01106010
};

// ---------------------------------------------------------------------------
// hkSphereTriangleAgent
// ---------------------------------------------------------------------------
class hkSphereTriangleAgent : public hkCollisionAgent
{
public:
    unsigned short  m_shapeType;                // +4
    unsigned short  m_isFlipped;                // +6
    hkContactMgr*   m_contactMgr;               // +8
    unsigned short  m_contactPointIndex;        // +0xc (-1 when none cached)
    char            m_pad0[2];
    hkCollideTriangleUtil::ClosestPointTriangleCache m_cache;   // +0x10

    static hkCollisionAgent* createSphereTriangleAgent(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                       const hkCollisionInput& input,
                                                       hkContactMgr* mgr);         // 0x010d6530
    static hkCollisionAgent* createTriangleSphereAgent(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                       const hkCollisionInput& input,
                                                       hkContactMgr* mgr);         // 0x010d6680

    void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                          const hkProcessCollisionInput& input,
                          hkProcessCollisionOutput& output);                       // 0x010d66e0
    void getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                          const hkCollisionInput& input, hkCdPointCollector& collector);   // 0x010d6a80
    static void staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                       const hkCollisionInput& input,
                                       hkCdPointCollector& collector);             // 0x010d6e00
    void getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                         const hkCollisionInput& input,
                         hkCdBodyPairCollector& collector);                        // 0x010d7190
    static void staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                      const hkCollisionInput& input,
                                      hkCdBodyPairCollector& collector);           // 0x010d7300
};

// ===========================================================================
// hkSymmetricAgent<hkSphereBoxAgent>::processCollision: run the wrapped agent
// with the bodies swapped, then flip every contact point it appended and, if
// the output separation changed, flip the output normal too.
// ===========================================================================
// hkSphereBoxAgent::processCollision (0x010d53d0) - declared as the real member
// so the equivalence checker resolves the call to the binary's own function.
class hkSphereBoxAgent : public hkCollisionAgent
{
public:
    virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                  const hkProcessCollisionInput& input,
                                  hkProcessCollisionOutput& output);      // 0x010d53d0
};

// @ 0x010d6420
void hkSymmetricSphereBoxAgent__processCollision(hkCollisionAgent* self,
                                                 const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                 const hkProcessCollisionInput& input,
                                                 hkProcessCollisionOutput& output)
{
    hkProcessCdPoint* pp = output.m_firstFreeContactPoint;
    hkTime oldToi = output.m_toiTime;

    ((hkSphereBoxAgent*)self)->hkSphereBoxAgent::processCollision(bodyB, bodyA, input, output);

    for (; pp < output.m_firstFreeContactPoint; pp++)
    {
        pp->m_contact.setFlipped(pp->m_contact);
    }

    if (oldToi != output.m_toiTime)
    {
        output.m_toiContact.m_separatingNormal.x = -output.m_toiContact.m_separatingNormal.x;
        output.m_toiContact.m_separatingNormal.y = -output.m_toiContact.m_separatingNormal.y;
        output.m_toiContact.m_separatingNormal.z = -output.m_toiContact.m_separatingNormal.z;
    }
}

// ===========================================================================
// @ 0x010d6530
// hkSphereTriangleAgent::createSphereTriangleAgent: allocate the agent (0x20
// bytes), point it at the sphere/triangle vtable, cache the contact manager and
// build the triangle cache from the triangle body's local vertices.
// ===========================================================================
hkCollisionAgent* hkSphereTriangleAgent::createSphereTriangleAgent(const hkCdBody& bodyA,
                                                                   const hkCdBody& bodyB,
                                                                   const hkCollisionInput& input,
                                                                   hkContactMgr* mgr)
{
    hkSphereTriangleAgent* agent = (hkSphereTriangleAgent*)hkMemory_s_instance->alloc(0x20, 0x1c);
    agent->m_contactMgr = mgr;
    *(unsigned short*)((char*)agent + 4) = 0x20;
    *(unsigned short*)((char*)agent + 6) = 1;
    *(void**)agent = (void*)0x014a4748;
    *(unsigned short*)((char*)agent + 0xc) = 0xffff;
    hkCollideTriangleUtil::setupClosestPointTriangleCache(
        (const hkVector4*)((const char*)bodyB.m_shape + 0x10), agent->m_cache);
    return agent;
}

// ===========================================================================
// @ 0x010d6680
// hkSphereTriangleAgent::createTriangleSphereAgent: same as above but the
// resulting agent is flipped (trailing vtable store).
// ===========================================================================
hkCollisionAgent* hkSphereTriangleAgent::createTriangleSphereAgent(const hkCdBody& bodyA,
                                                                   const hkCdBody& bodyB,
                                                                   const hkCollisionInput& input,
                                                                   hkContactMgr* mgr)
{
    hkSphereTriangleAgent* agent = (hkSphereTriangleAgent*)hkMemory_s_instance->alloc(0x20, 0x1c);
    agent->m_contactMgr = mgr;
    *(unsigned short*)((char*)agent + 4) = 0x20;
    *(unsigned short*)((char*)agent + 6) = 1;
    *(void**)agent = (void*)0x014a4748;
    *(unsigned short*)((char*)agent + 0xc) = 0xffff;
    hkCollideTriangleUtil::setupClosestPointTriangleCache(
        (const hkVector4*)((const char*)bodyA.m_shape + 0x10), agent->m_cache);
    *(void**)agent = (void*)0x014a477c;
    return agent;
}

// out = M.basis * v + M.translation: a triangle vertex in world space.
static __forceinline void hkTriXformVertex(hkVector4& out, const hkVector4& v,
                                           const hkTransform& m)
{
    out.x = m.m_basis[0].x * v.x + (m.m_basis[1].x * v.y + m.m_basis[2].x * v.z) + m.m_translation.x;
    out.y = m.m_basis[0].y * v.x + (m.m_basis[1].y * v.y + m.m_basis[2].y * v.z) + m.m_translation.y;
    out.z = m.m_basis[0].z * v.x + (m.m_basis[1].z * v.y + m.m_basis[2].z * v.z) + m.m_translation.z;
    out.w = 0.0f;
}

// Sphere centre delta (p - triTranslation) rotated by the triangle transform's
// basis rows: the sphere centre in the triangle body's local frame.
static __forceinline void hkTriLocalPoint(hkVector4& out, const hkVector4& p,
                                          const hkTransform& m)
{
    const float dx = p.x - m.m_translation.x;
    const float dy = p.y - m.m_translation.y;
    const float dz = p.z - m.m_translation.z;
    out.x = dx * m.m_basis[0].x + (dy * m.m_basis[0].y + dz * m.m_basis[0].z);
    out.y = dx * m.m_basis[1].x + (dy * m.m_basis[1].y + dz * m.m_basis[1].z);
    out.z = dx * m.m_basis[2].x + (dy * m.m_basis[2].y + dz * m.m_basis[2].z);
    out.w = 0.0f;
}

// ===========================================================================
// @ 0x010d66e0
// hkSphereTriangleAgent::processCollision: world-space triangle, closest point
// to the sphere centre, then either drop the cached contact (too far apart) or
// create/refresh it and write the manifold point into the output.
// ===========================================================================
void hkSphereTriangleAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                             const hkProcessCollisionInput& input,
                                             hkProcessCollisionOutput& output)
{
    hkTimerCommand(hkTtrcSphereTri);

    const hkSphereShape*   sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkTriangleShape* tri    = (const hkTriangleShape*)bodyB.m_shape;
    const hkTransform&     triXf  = *(const hkTransform*)bodyB.m_motion;
    const hkTransform&     sphXf  = *(const hkTransform*)bodyA.m_motion;

    hkVector4 verts[3];
    hkTriXformVertex(verts[0], tri->m_vertex[0], triXf);
    hkTriXformVertex(verts[1], tri->m_vertex[1], triXf);
    hkTriXformVertex(verts[2], tri->m_vertex[2], triXf);

    hkCollideTriangleUtil::ClosestPointTriangleResult res;
    hkCollideTriangleUtil::closestPointTriangle(sphXf.m_translation, verts, m_cache, res);

    hkTime rsum = sphere->m_radius + tri->m_radius;

    if (rsum + input.m_tolerance <= res.m_distance)
    {
        if (m_contactPointIndex != 0xffff)
        {
            m_contactMgr->removeContactPoint(m_contactPointIndex);
            m_contactPointIndex = 0xffff;
        }
    }
    else
    {
        float* cp = (float*)output.m_firstFreeContactPoint;
        float scale = tri->m_radius - res.m_distance;

        cp[0] = sphXf.m_translation.x;
        cp[1] = sphXf.m_translation.y;
        cp[2] = sphXf.m_translation.z;
        cp[3] = sphXf.m_translation.w;
        cp[0] = res.m_closestPoint.x * scale + cp[0];
        cp[1] = res.m_closestPoint.y * scale + cp[1];
        cp[2] = res.m_closestPoint.z * scale + cp[2];
        cp[3] = res.m_closestPoint.w * scale + cp[3];
        cp[4] = res.m_closestPoint.x;
        cp[5] = res.m_closestPoint.y;
        cp[6] = res.m_closestPoint.z;
        cp[7] = res.m_closestPoint.w;
        cp[7] = res.m_distance - rsum;

        if (m_contactPointIndex == 0xffff)
        {
            m_contactPointIndex = (unsigned short)m_contactMgr->createContactPoint(
                bodyA, bodyB, input, (hkContactPoint*)cp);
        }
        if (m_contactPointIndex != 0xffff)
        {
            *(unsigned short*)(cp + 8) = m_contactPointIndex;
            output.m_firstFreeContactPoint = (hkProcessCdPoint*)(cp + 0xc);
        }
    }

    hkTimerCommand(hkTtrcEnd);
}

// ===========================================================================
// @ 0x010d6a80
// hkSphereTriangleAgent::getClosestPoints: report the closest point between the
// sphere centre and the world-space triangle when they are within touching
// distance (plus tolerance), using the agent's cached triangle.
// ===========================================================================
void hkSphereTriangleAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                             const hkCollisionInput& input,
                                             hkCdPointCollector& collector)
{
    hkTimerCommand(hkTtrcSphereTri);

    const hkSphereShape*   sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkTriangleShape* tri    = (const hkTriangleShape*)bodyB.m_shape;
    const hkTransform&     triXf  = *(const hkTransform*)bodyB.m_motion;
    const hkTransform&     sphXf  = *(const hkTransform*)bodyA.m_motion;

    hkVector4 verts[3];
    hkTriXformVertex(verts[0], tri->m_vertex[0], triXf);
    hkTriXformVertex(verts[1], tri->m_vertex[1], triXf);
    hkTriXformVertex(verts[2], tri->m_vertex[2], triXf);

    hkCollideTriangleUtil::ClosestPointTriangleResult res;
    hkCollideTriangleUtil::closestPointTriangle(sphXf.m_translation, verts, m_cache, res);

    float rsum = sphere->m_radius + tri->m_radius;
    if (res.m_distance < rsum + input.m_tolerance)
    {
        hkVector4 normal = res.m_closestPoint;
        float scale = tri->m_radius - res.m_distance;

        hkVector4 point = sphXf.m_translation;
        point.x += normal.x * scale;
        point.y += normal.y * scale;
        point.z += normal.z * scale;
        point.w += normal.w * scale;

        collector.addCdPoint(&point);
    }

    hkTimerCommand(hkTtrcEnd);
}

// ===========================================================================
// @ 0x010d6e00
// hkSphereTriangleAgent::staticGetClosestPoints: same query but the triangle
// cache is rebuilt rather than taken from the agent.
// ===========================================================================
void hkSphereTriangleAgent::staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                   const hkCollisionInput& input,
                                                   hkCdPointCollector& collector)
{
    hkTimerCommand(hkTtrcSphereTri);

    const hkSphereShape*   sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkTriangleShape* tri    = (const hkTriangleShape*)bodyB.m_shape;
    const hkTransform&     triXf  = *(const hkTransform*)bodyB.m_motion;
    const hkTransform&     sphXf  = *(const hkTransform*)bodyA.m_motion;

    hkCollideTriangleUtil::ClosestPointTriangleCache cache;
    hkCollideTriangleUtil::setupClosestPointTriangleCache(
        (const hkVector4*)((const char*)bodyB.m_shape + 0x10), cache);

    hkVector4 verts[3];
    hkTriXformVertex(verts[0], tri->m_vertex[0], triXf);
    hkTriXformVertex(verts[1], tri->m_vertex[1], triXf);
    hkTriXformVertex(verts[2], tri->m_vertex[2], triXf);

    hkCollideTriangleUtil::ClosestPointTriangleResult res;
    hkCollideTriangleUtil::closestPointTriangle(sphXf.m_translation, verts, cache, res);

    float rsum = sphere->m_radius + tri->m_radius;
    if (res.m_distance < rsum + input.m_tolerance)
    {
        hkVector4 normal = res.m_closestPoint;
        float scale = tri->m_radius - res.m_distance;

        hkVector4 point = sphXf.m_translation;
        point.x += normal.x * scale;
        point.y += normal.y * scale;
        point.z += normal.z * scale;
        point.w += normal.w * scale;

        collector.addCdPoint(&point);
    }

    hkTimerCommand(hkTtrcEnd);
}

// ===========================================================================
// @ 0x010d7190
// hkSphereTriangleAgent::getPenetrations: closest point between the sphere and
// the world-space triangle; report the body pair when it overlaps.
// ===========================================================================
void hkSphereTriangleAgent::getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                            const hkCollisionInput& input,
                                            hkCdBodyPairCollector& collector)
{
    hkTimerCommand(hkTtrcSphereTri);

    const hkSphereShape*   sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkTriangleShape* tri    = (const hkTriangleShape*)bodyB.m_shape;
    const hkTransform&     triXf  = *(const hkTransform*)bodyB.m_motion;
    const hkTransform&     sphXf  = *(const hkTransform*)bodyA.m_motion;

    hkVector4 localPoint;
    hkTriLocalPoint(localPoint, sphXf.m_translation, triXf);

    float rsum = sphere->m_radius + tri->m_radius;

    hkCollideTriangleUtil::ClosestPointTriangleResult res;
    hkCollideTriangleUtil::closestPointTriangle(localPoint, (const hkVector4*)((const char*)bodyB.m_shape + 0x10), m_cache, res);

    if (res.m_distance < rsum)
    {
        collector.addCdBodyPair(bodyA, bodyB);
    }

    hkTimerCommand(hkTtrcEnd);
}

// ===========================================================================
// @ 0x010d7300
// hkSphereTriangleAgent::staticGetPenetrations (cache rebuilt each call).
// ===========================================================================
void hkSphereTriangleAgent::staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                  const hkCollisionInput& input,
                                                  hkCdBodyPairCollector& collector)
{
    hkTimerCommand(hkTtrcSphereTri);

    const hkSphereShape*   sphere = (const hkSphereShape*)bodyA.m_shape;
    const hkTriangleShape* tri    = (const hkTriangleShape*)bodyB.m_shape;
    const hkTransform&     triXf  = *(const hkTransform*)bodyB.m_motion;
    const hkTransform&     sphXf  = *(const hkTransform*)bodyA.m_motion;

    hkCollideTriangleUtil::ClosestPointTriangleCache cache;
    hkCollideTriangleUtil::setupClosestPointTriangleCache(
        (const hkVector4*)((const char*)bodyB.m_shape + 0x10), cache);

    hkVector4 localPoint;
    hkTriLocalPoint(localPoint, sphXf.m_translation, triXf);

    float rsum = sphere->m_radius + tri->m_radius;

    hkCollideTriangleUtil::ClosestPointTriangleResult res;
    hkCollideTriangleUtil::closestPointTriangle(localPoint, (const hkVector4*)((const char*)bodyB.m_shape + 0x10), cache, res);

    if (res.m_distance < rsum)
    {
        collector.addCdBodyPair(bodyA, bodyB);
    }

    hkTimerCommand(hkTtrcEnd);
}

// ===========================================================================
// hkSymmetricAgent<hkSphereTriangleAgent>::getPenetrations wrapper: stack
// collector whose vtable forwards to the real collector stored at +8.
// ===========================================================================
struct hkSymPairCollectorLocal
{
    void*                  m_vtable;        // +0
    unsigned char          m_earlyOut;      // +4
    hkCdBodyPairCollector* m_forward;       // +8
};

// hkSymmetricAgent<hkSphereTriangleAgent>: same layout as the wrapped agent.
class hkSymmetricSphereTriangleAgent : public hkSphereTriangleAgent
{
public:
    void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&,
                         hkCdBodyPairCollector&);                       // 0x010d7470
    void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&,
                          hkCdPointCollector&);                         // 0x010d74f0
};

// @ 0x010d7470
void hkSymmetricSphereTriangleAgent::getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                     const hkCollisionInput& input,
                                                     hkCdBodyPairCollector& collector)
{
    hkSymPairCollectorLocal sym;
    sym.m_forward = &collector;
    sym.m_earlyOut = 0;
    sym.m_vtable = (void*)0x014a43b4;

    hkSphereTriangleAgent::getPenetrations(bodyB, bodyA, input,
                                           *(hkCdBodyPairCollector*)&sym);
}

// ===========================================================================
// hkSymmetricAgent<hkSphereTriangleAgent>::getClosestPoints wrapper.
// ===========================================================================
struct hkSymPointCollectorLocal
{
    void*               m_vtable;       // +0
    unsigned            m_earlyOut;     // +4 (bit pattern 0x7f7fffee)
    hkCdPointCollector* m_forward;      // +8
};

// @ 0x010d74f0
void hkSymmetricSphereTriangleAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                      const hkCollisionInput& input,
                                                      hkCdPointCollector& collector)
{
    hkSymPointCollectorLocal sym;
    sym.m_forward = &collector;
    sym.m_earlyOut = 0x7f7fffeeu;
    sym.m_vtable = (void*)0x014a43a4;

    hkSphereTriangleAgent::getClosestPoints(bodyB, bodyA, input,
                                            *(hkCdPointCollector*)&sym);
}



