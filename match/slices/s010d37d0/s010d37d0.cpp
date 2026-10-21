// Slice s010d37d0: Havok 3.1.0 capsule-triangle / capsule-capsule collision agents.
//
//  010d37d0  hkCapsuleTriangleAgent::getPenetrations
//  010d3c10  hkCapsuleTriangleAgent::staticGetPenetrations
//  010d4070  hkCapsuleTriangleAgent::getPenetrations wrapper
//  010d40f0  hkCapsuleTriangleAgent::getClosestPoints wrapper
//  010d4170  hkCapsuleTriangleAgent::processCollision thunk
//  010d4280  hkCapsuleCapsuleAgent::createCapsuleCapsuleAgent
//  010d42c0  hkCapsuleCapsuleAgent::processCollision
//
// Flags: /vc71 /O2 /MD /Gy /TP (Havok 3.1.0 was built by VC .NET 2003, x87
// floats, 16-byte aligned frames).
#include "types.h"
#include <intrin.h>

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkTtrcCapsTriangle[];             // 0x014a4630 ("TtCapsTriangle")
extern const char hkTtrcCapsCaps[];                 // 0x014a4688 ("TtCapsCaps")
extern const char hkTtrcEnd[];                      // 0x0149cc34

// Monitor-stream scope guard: push the timer tag on the thread-local monitor
// stream when the current pointer has not yet reached the end pointer.
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
class hkBool
{
public:
    char m_bool;
    hkBool() {}
    hkBool(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
};

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

struct hkContactPoint
{
    hkVector4 m_position;           // +0
    hkVector4 m_separatingNormal;   // +0x10
    void setFlipped(const hkContactPoint& other);   // 0x010cecf0
};

class hkCdBodyPairCollector
{
public:
    virtual ~hkCdBodyPairCollector() {}
    virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b) = 0;   // slot 1
    hkBool m_earlyOut;              // +4
    const void* m_extra;            // +8
};

class hkCdPointCollector
{
public:
    virtual ~hkCdPointCollector() {}
    virtual void addCdPoint(const void* point) = 0;   // slot 1
    float m_earlyOutDistance;       // +4
};

// Capsule-vs-triangle manifold: contacts at +0, +0x20; allocate room for a
// third (the util may write it; the original simply ignores it).
struct hkCapsTriangleManifold
{
    hkContactPoint m_contact[3];    // +0, +0x20, +0x40
};

// hkCollideCapsuleUtil::manifoldCapsVsTriangle (0x01107270)
extern "C" void __cdecl hkCollideCapsuleUtilManifoldCapsVsTriangle(
    const hkVector4* capSegment, float capRadius,
    const hkVector4* triangle, float triRadius,
    const void* cache, float extraRadius, int singleCheck,
    void* out);                                              // 0x01107270

// hkCollideCapsuleUtil::manifoldCapsVsCapsule (0x01106490)
extern "C" void __cdecl hkCollideCapsuleUtilManifoldCapsVsCapsule(
    const hkVector4* capA, float radiusA, const hkVector4* capB, float radiusB,
    void* out);                                              // 0x01106490

// Capsule-vs-capsule manifold: 3 contacts, distance in the normal .w of each.
struct hkContactManifold
{
    hkContactPoint m_contact[3];    // +0, +0x20, +0x40
};

// hkContactMgr: agent+8; vtable slot 2 = addPoint(bodyA,bodyB,input,contact)->key,
// slot 4 = removePoint(key).
struct hkContactMgr
{
    virtual void v0();                                                                   // +0x00
    virtual void v1();                                                                   // +0x04
    virtual unsigned short addPoint(const void*, const void*, const void*, const void*); // +0x08
    virtual void v3();                                                                   // +0x0c
    virtual void removePoint(unsigned short key);                                        // +0x10
};

// hkCapsuleTriangleUtil::setUpCache (0x01105e90)
extern "C" void __cdecl hkCapsuleTriangleUtilSetUpCache(const hkVector4* triangle, void* cache);  // 0x01105e90

// hkCapsuleTriangleAgent::processCollision (0x010d28c0) - thiscall
class hkCapsuleTriangleAgent;

// ---------------------------------------------------------------------------
// agent class with the ordering-vtable used by the wrappers
// ---------------------------------------------------------------------------
class hkCollisionAgent
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
};

class hkCapsuleTriangleAgent : public hkCollisionAgent
{
public:
    void getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                         const hkCollisionInput& input, hkCdBodyPairCollector& collector);   // 0x010d37d0
    static void staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                      const hkCollisionInput& input, hkCdBodyPairCollector& collector);  // 0x010d3c10
    void getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                          const hkCollisionInput& input, hkCdPointCollector& collector);    // 0x010d2d80
    void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                          const void* input, void* output);                                  // 0x010d28c0
    void getPenetrationsWrapper(const void* bodyA, const void* bodyB,
                                const void* input, void* collector);                     // 0x010d4070
    void getClosestPointsWrapper(const void* bodyA, const void* bodyB,
                                 const void* input, void* collector);                    // 0x010d40f0
    void processCollisionThunk(const void* bodyA, const void* bodyB,
                               const void* input, void* output);                         // 0x010d4170
};

// ---------------------------------------------------------------------------
// @ 0x010d4070
// Builder for the temporary body-pair collector; forwards to getPenetrations
// with (bodyB, bodyA) swapped.  __thiscall: ecx = this.
// ---------------------------------------------------------------------------
struct hkTempPairCollector
{
    const void* m_vtbl;             // +0
    char        m_earlyOut;         // +4
    const void* m_extra;            // +8
};

void hkCapsuleTriangleAgent::getPenetrationsWrapper(const void* bodyA, const void* bodyB,
                                                    const void* input, void* collector)
{
    hkTempPairCollector tmp;
    tmp.m_extra = collector;
    tmp.m_earlyOut = 0;
    tmp.m_vtbl = (const void*)0x014a43b4;
    getPenetrations(*(const hkCdBody*)bodyB, *(const hkCdBody*)bodyA,
                    *(const hkCollisionInput*)input, *(hkCdBodyPairCollector*)&tmp);
}

// ---------------------------------------------------------------------------
// @ 0x010d40f0
// ---------------------------------------------------------------------------
struct hkTempPointCollector
{
    const void* m_vtbl;             // +0
    unsigned    m_earlyOutDistance; // +4
    const void* m_extra;            // +8
};

void hkCapsuleTriangleAgent::getClosestPointsWrapper(const void* bodyA, const void* bodyB,
                                                     const void* input, void* collector)
{
    hkTempPointCollector tmp;
    tmp.m_extra = collector;
    tmp.m_earlyOutDistance = 0x7f7fffeeu;
    tmp.m_vtbl = (const void*)0x014a43a4;
    getClosestPoints(*(const hkCdBody*)bodyB, *(const hkCdBody*)bodyA,
                     *(const hkCollisionInput*)input, *(hkCdPointCollector*)&tmp);
}

// ---------------------------------------------------------------------------
// @ 0x010d4170
// Snapshot the contact-point count, forward to the triangle agent's
// processCollision with (bodyB, bodyA) swapped, flip every newly added contact
// point, and negate the separating normal if the count changed.
// ---------------------------------------------------------------------------
void hkCapsuleTriangleAgent::processCollisionThunk(const void* bodyA, const void* bodyB,
                                                   const void* input, void* output)
{
    float oldNormal = *(float*)((char*)output + 0x3034);
    const void* first = *(const void**)output;
    processCollision(*(const hkCdBody*)bodyB, *(const hkCdBody*)bodyA, input, output);
    for (unsigned cp = (unsigned)first; cp < *(unsigned*)output; cp += 0x30)
        ((hkContactPoint*)cp)->setFlipped(*(const hkContactPoint*)cp);
    if (oldNormal != *(float*)((char*)output + 0x3034))
    {
        float* n = (float*)((char*)output + 0x20);
        n[0] = -n[0];
        n[1] = -n[1];
        n[2] = -n[2];
    }
}

// ---------------------------------------------------------------------------
// @ 0x010d4280  ?createCapsuleCapsuleAgent@hkCapsuleCapsuleAgent@@KA...
// Allocates a 0x1c-byte agent, stores the collision-agent vtable and the
// object size / flags.
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
extern hkMemory* g_hkMemory;                     // 0x016e4178

class hkCapsuleCapsuleAgent : public hkCollisionAgent
{
public:
    void processCollision(const void* bodyA, const void* bodyB,
                          const void* input, void* output);   // 0x010d42c0
    int m_pad[2];                                             // +4 refcount, +8 mgr
    unsigned short m_keys[3];                                 // +0xc, +0xe, +0x10
};

extern "C" void* hkCapsuleCapsuleAgent__create(const void* bodyA, const void* bodyB,
                                               const void* input, void* contactMgr);  // 0x010d4280

void* hkCapsuleCapsuleAgent__create(const void* bodyA, const void* bodyB,
                                    const void* input, void* contactMgr)
{
    hkCapsuleCapsuleAgent* agent = (hkCapsuleCapsuleAgent*)g_hkMemory->alloc(0x14, 0x1c);
    *(void**)((char*)agent + 8) = contactMgr;
    *(unsigned short*)((char*)agent + 4) = 0x14;
    *(unsigned short*)((char*)agent + 6) = 1;
    *(void**)agent = (void*)0x014a4654;
    *(unsigned short*)((char*)agent + 0xc) = 0xffff;
    *(unsigned short*)((char*)agent + 0xe) = 0xffff;
    *(unsigned short*)((char*)agent + 0x10) = 0xffff;
    return agent;
}

// ---------------------------------------------------------------------------
// capsule / triangle shapes
// ---------------------------------------------------------------------------
struct hkTransform
{
    hkVector4 m_basis[3];           // +0, +0x10, +0x20
    hkVector4 m_translation;        // +0x30
};

struct hkCapsuleShape
{
    char      m_pad[0xc];
    float     m_radius;             // +0xc
    hkVector4 m_vertexA;            // +0x10
    hkVector4 m_vertexB;            // +0x20
};

struct hkTriangleShape
{
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

// ---------------------------------------------------------------------------
// @ 0x010d37d0
// ---------------------------------------------------------------------------
void hkCapsuleTriangleAgent::getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                             const hkCollisionInput& input,
                                             hkCdBodyPairCollector& collector)
{
    hkTimerCommand(hkTtrcCapsTriangle);

    const hkTransform& capXf = *(const hkTransform*)bodyA.m_motion;
    const hkTransform& triXf = *(const hkTransform*)bodyB.m_motion;
    const hkCapsuleShape*  cap = (const hkCapsuleShape*)bodyA.m_shape;
    const hkTriangleShape* tri = (const hkTriangleShape*)bodyB.m_shape;

    hkVector4 capSeg[2];
    HK_XFORM_ONE(capSeg[0], cap->m_vertexA, capXf)
    HK_XFORM_ONE(capSeg[1], cap->m_vertexB, capXf)

    hkVector4 triVerts[3];
    HK_XFORM_ONE(triVerts[0], tri->m_vertexA, triXf)
    HK_XFORM_ONE(triVerts[1], tri->m_vertexB, triXf)
    HK_XFORM_ONE(triVerts[2], tri->m_vertexC, triXf)

    hkCapsTriangleManifold manifold;
    hkCollideCapsuleUtilManifoldCapsVsTriangle(capSeg, cap->m_radius, triVerts, tri->m_radius,
                                               (const char*)this + 0x14, input.m_tolerance, 0,
                                               &manifold);
    if (manifold.m_contact[0].m_separatingNormal.w < 0.0f ||
        manifold.m_contact[1].m_separatingNormal.w < 0.0f)
    {
        collector.addCdBodyPair(bodyA, bodyB);
    }
    hkTimerCommand(hkTtrcEnd);
}

// ---------------------------------------------------------------------------
// @ 0x010d3c10
// ---------------------------------------------------------------------------
void hkCapsuleTriangleAgent::staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                   const hkCollisionInput& input,
                                                   hkCdBodyPairCollector& collector)
{
    hkTimerCommand(hkTtrcCapsTriangle);

    const hkTransform& capXf = *(const hkTransform*)bodyA.m_motion;
    const hkTransform& triXf = *(const hkTransform*)bodyB.m_motion;
    const hkCapsuleShape*  cap = (const hkCapsuleShape*)bodyA.m_shape;
    const hkTriangleShape* tri = (const hkTriangleShape*)bodyB.m_shape;

    hkVector4 triLocal[3];
    triLocal[0] = tri->m_vertexA;
    triLocal[1] = tri->m_vertexB;
    triLocal[2] = tri->m_vertexC;

    char cache[0x40];
    hkCapsuleTriangleUtilSetUpCache(triLocal, cache);   // 0x01105e90

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

    if (manifold.m_contact[0].m_separatingNormal.w < 0.0f ||
        manifold.m_contact[1].m_separatingNormal.w < 0.0f)
    {
        collector.addCdBodyPair(bodyA, bodyB);
    }
    hkTimerCommand(hkTtrcEnd);
}

// ---------------------------------------------------------------------------
// @ 0x010d42c0
// ---------------------------------------------------------------------------
struct hkProcessCollisionInput
{
    int   m_pad0;                   // +0
    int   m_pad1;                   // +4
    float m_tolerance;              // +8
    int   m_pad2[6];                // +0xc ..
    float m_radius;                 // +0x24
};

struct hkProcessCollisionOutput
{
    void*     m_firstContactPoint;  // +0
    int       m_pad[7];
    hkVector4 m_separatingNormal;   // +0x20
    int       m_contactPointCount;  // +0x3034
};

void hkCapsuleCapsuleAgent::processCollision(const void* bodyA, const void* bodyB,
                                             const void* input, void* output)
{
    hkTimerCommand(hkTtrcCapsCaps);

    const hkTransform& xfA = *(const hkTransform*)((const hkCdBody*)bodyA)->m_motion;
    const hkTransform& xfB = *(const hkTransform*)((const hkCdBody*)bodyB)->m_motion;
    const hkCapsuleShape* capA = (const hkCapsuleShape*)((const hkCdBody*)bodyA)->m_shape;
    const hkCapsuleShape* capB = (const hkCapsuleShape*)((const hkCdBody*)bodyB)->m_shape;

    hkVector4 segA[2], segB[2];
    HK_XFORM_ONE(segA[0], capA->m_vertexA, xfA)
    HK_XFORM_ONE(segA[1], capA->m_vertexB, xfA)
    HK_XFORM_ONE(segB[0], capB->m_vertexA, xfB)
    HK_XFORM_ONE(segB[1], capB->m_vertexB, xfB)

    hkContactManifold manifold;
    const float tol = *(const float*)((const char*)input + 8);
    manifold.m_contact[0].m_separatingNormal.w = tol;
    manifold.m_contact[1].m_separatingNormal.w = tol;
    manifold.m_contact[2].m_separatingNormal.w = tol;
    hkCollideCapsuleUtilManifoldCapsVsCapsule(segA, capA->m_radius, segB, capB->m_radius, &manifold);

    hkContactMgr* mgr = *(hkContactMgr**)((char*)this + 8);
    for (int i = 0; i < 3; i++)
    {
        if (tol <= manifold.m_contact[i].m_separatingNormal.w)
        {
            if (m_keys[i] != 0xffff)
            {
                mgr->removePoint(m_keys[i]);
                m_keys[i] = 0xffff;
            }
        }
        else
        {
            if (m_keys[i] == 0xffff)
            {
                unsigned short k = mgr->addPoint(bodyA, bodyB, input, &manifold.m_contact[i]);
                m_keys[i] = k;
                if (k == 0xffff)
                    continue;
            }
            hkContactPoint* p = (hkContactPoint*)*(void**)output;
            *(char**)output = (char*)p + 0x30;
            p->m_position = manifold.m_contact[i].m_position;
            p->m_separatingNormal = manifold.m_contact[i].m_separatingNormal;
            *(unsigned short*)((char*)p + 0x20) = m_keys[i];
        }
    }
    hkTimerCommand(hkTtrcEnd);
}
