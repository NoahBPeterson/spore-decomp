// Slice s010d4730: Havok 3.1.0 capsule-vs-capsule collision agent, closest
// points / penetrations.
//
//  010d4730  hkCapsuleCapsuleAgent::getClosestPoints        (virtual, ret 0x10)
//  010d4b00  hkCapsuleCapsuleAgent::staticGetClosestPoints  (static, ret)
//  010d4ed0  hkCapsuleCapsuleAgent::staticGetPenetrations   (static, ret)
//
// Flags: /vc71 /O2 /MD /Gy /TP  (Havok 3.1.0 was built by VC .NET 2003; the
// 16-byte-aligned frame and x87 operand order are that compiler's).
#include "types.h"
#include <intrin.h>

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkTtrcCapsCaps[];                 // 0x014a4688 ("TtCapsCaps")
extern const char hkTtrcEnd[];                      // 0x0149cc34

// ---------------------------------------------------------------------------
// Monitor-stream scope guard (shared with the other Havok collision slices):
// push the timer tag on the thread-local monitor stream when the current
// pointer has not yet reached the end pointer.
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

class hkCapsuleCapsuleAgent : public hkCollisionAgent
{
public:
    void getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                          const hkCollisionInput& input, hkCdPointCollector& collector);          // 0x010d4730
    static void staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                       const hkCollisionInput& input, hkCdPointCollector& collector); // 0x010d4b00
    static void staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                      const hkCollisionInput& input, hkCdBodyPairCollector& collector); // 0x010d4ed0
};

// ---------------------------------------------------------------------------
// shapes
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

// out = R * v + t, one lane at a time with the transform's rows bound to named
// scalars first (this is the shape cl 13.10 emits; the stack offsets of the
// named locals line up with the original's frame).
#define HK_XFORM_ONE(O, I, T) { \
        const float v0 = (I).x, v1 = (I).y, v2 = (I).z; \
        const float xx = (T).m_basis[0].x, xy = (T).m_basis[0].y, xz = (T).m_basis[0].z; \
        const float yx = (T).m_basis[1].x, yy = (T).m_basis[1].y, yz = (T).m_basis[1].z; \
        const float zx = (T).m_basis[2].x, zy = (T).m_basis[2].y, zz = (T).m_basis[2].z; \
        const float tx = (T).m_translation.x, ty = (T).m_translation.y, tz = (T).m_translation.z; \
        (O).x = (v0 * xx + (v1 * yx + v2 * zx)) + tx; \
        (O).y = (v0 * xy + (v1 * yy + v2 * zy)) + ty; \
        (O).z = (v0 * xz + (v1 * yz + v2 * zz)) + tz; \
        (O).w = 0.0f; }

// capsule-vs-capsule penetration manifold (distance arranged in .w)
struct hkContactPoint
{
    hkVector4 m_position;           // +0
    hkVector4 m_separatingNormal;   // +0x10
};

// Result block written by hkCollideCapsuleUtilClostestPointCapsVsCaps: two
// closest points and a squared distance (mirrors ClosestLineSegLineSegResult).
struct hkCapsCapsClosestPointResult
{
    hkVector4 m_closestPointA;      // +0
    hkVector4 m_closestPointB;      // +0x10
    float     m_distanceSquared;    // +0x20
    float     m_pad0;               // +0x24
};

// hkCollideCapsuleUtil::clostestPointCapsVsCaps (0x01106f80)
extern "C" int __cdecl hkCollideCapsuleUtilClostestPointCapsVsCaps(
    const hkVector4* capA, float radiusA, const hkVector4* capB, float radiusB,
    float tolerance, hkCapsCapsClosestPointResult* out);         // 0x01106f80

// hkMemory (allocates the collision agents)
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

struct hkContactMgr;

// hkCollisionDispatcher::AgentFuncs
typedef hkCollisionAgent* (__cdecl *hkAgentCreateFunc)(const hkCdBody&, const hkCdBody&,
                                                       const hkCollisionInput&, hkContactMgr*);
typedef void (__cdecl *hkAgentGetPenetrationsFunc)(const hkCdBody&, const hkCdBody&,
                                                   const hkCollisionInput&, hkCdBodyPairCollector&);
typedef void (__cdecl *hkAgentGetClosestPointsFunc)(const hkCdBody&, const hkCdBody&,
                                                    const hkCollisionInput&, hkCdPointCollector&);
typedef void (__cdecl *hkAgentLinearCastFunc)(const hkCdBody&, const hkCdBody&, const void*,
                                              hkCdPointCollector&, hkCdPointCollector*);

struct hkAgentFuncs
{
    hkAgentCreateFunc            m_createFunc;          // +0
    hkAgentGetPenetrationsFunc   m_getPenetrationsFunc; // +4
    hkAgentGetClosestPointsFunc  m_getClosestPointFunc; // +8
    hkAgentLinearCastFunc        m_linearCastFunc;      // +0xc
    char                         m_isFlipped;           // +0x10
    char                         m_isPredictive;        // +0x11
    short                        m_pad0;                // +0x12
    unsigned                     m_flags;               // +0x14 (0x18-byte struct in the retail build)
};

struct hkCollisionDispatcher
{
    char          m_pad0[0x190];
    unsigned char m_agent2Types[32][32];               // +0x190
    unsigned char m_agent2TypesPredictive[32][32];     // +0x590
    hkAgentFuncs  m_agent2Func[1];                     // +0x990
    void registerCollisionAgent(hkAgentFuncs& funcs, int typeA, int typeB);   // 0x010cd3e0
};

// hkCollideTriangleUtil::closestLineSegLineSeg (0x01105940)
class hkCollideTriangleUtil
{
public:
    struct ClosestLineSegLineSegResult
    {
        hkVector4 m_closestPointA;      // +0
        hkVector4 m_closestPointB;      // +0x10
        float     m_distanceSquared;    // +0x20 (single float, result block is 0x24 bytes)
    };
    static int closestLineSegLineSeg(const hkVector4& A, const hkVector4& dA, const hkVector4& B,
                                     const hkVector4& dB, ClosestLineSegLineSegResult& result); // 0x01105940
};

// ---------------------------------------------------------------------------
// @ 0x010d4730
// Virtual entry point: timing scope, transform the two capsules' segments into
// world space, ask the capsule/capsule util for the closest points and forward
// them to the collector when the pair actually intersects.
// ---------------------------------------------------------------------------
void hkCapsuleCapsuleAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                             const hkCollisionInput& input,
                                             hkCdPointCollector& collector)
{
    hkTimerCommand(hkTtrcCapsCaps);

    const hkTransform& xfA = *(const hkTransform*)bodyA.m_motion;
    const hkTransform& xfB = *(const hkTransform*)bodyB.m_motion;
    const hkCapsuleShape* capA = (const hkCapsuleShape*)bodyA.m_shape;
    const hkCapsuleShape* capB = (const hkCapsuleShape*)bodyB.m_shape;

    hkVector4 segA[2];
    HK_XFORM_ONE(segA[0], capA->m_vertexA, xfA)
    HK_XFORM_ONE(segA[1], capA->m_vertexB, xfA)

    hkVector4 segB[2];
    HK_XFORM_ONE(segB[0], capB->m_vertexA, xfB)
    HK_XFORM_ONE(segB[1], capB->m_vertexB, xfB)

    hkCapsCapsClosestPointResult result;
    if (hkCollideCapsuleUtilClostestPointCapsVsCaps(segA, capA->m_radius, segB, capB->m_radius,
                                                    input.m_tolerance, &result) == 0)
    {
        collector.addCdPoint(&result);
    }

    hkTimerCommand(hkTtrcEnd);
}

// ---------------------------------------------------------------------------
// @ 0x010d4b00
// Static twin of the above (same body, no `this`).
// ---------------------------------------------------------------------------
void hkCapsuleCapsuleAgent::staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                   const hkCollisionInput& input,
                                                   hkCdPointCollector& collector)
{
    hkTimerCommand(hkTtrcCapsCaps);

    const hkTransform& xfA = *(const hkTransform*)bodyA.m_motion;
    const hkTransform& xfB = *(const hkTransform*)bodyB.m_motion;
    const hkCapsuleShape* capA = (const hkCapsuleShape*)bodyA.m_shape;
    const hkCapsuleShape* capB = (const hkCapsuleShape*)bodyB.m_shape;

    hkVector4 segA[2];
    HK_XFORM_ONE(segA[0], capA->m_vertexA, xfA)
    HK_XFORM_ONE(segA[1], capA->m_vertexB, xfA)

    hkVector4 segB[2];
    HK_XFORM_ONE(segB[0], capB->m_vertexA, xfB)
    HK_XFORM_ONE(segB[1], capB->m_vertexB, xfB)

    hkCapsCapsClosestPointResult result;
    if (hkCollideCapsuleUtilClostestPointCapsVsCaps(segA, capA->m_radius, segB, capB->m_radius,
                                                    input.m_tolerance, &result) == 0)
    {
        collector.addCdPoint(&result);
    }

    hkTimerCommand(hkTtrcEnd);
}

// ---------------------------------------------------------------------------
// @ 0x010d4ed0
// Penetration test: world-space segments and their direction vectors, then
// closestLineSegLineSeg; report the pair when the segment distance squared is
// below (rA + rB)^2.
// ---------------------------------------------------------------------------
void hkCapsuleCapsuleAgent::staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                  const hkCollisionInput& input,
                                                  hkCdBodyPairCollector& collector)
{
    hkTimerCommand(hkTtrcCapsCaps);

    const hkTransform& xfA = *(const hkTransform*)bodyA.m_motion;
    const hkTransform& xfB = *(const hkTransform*)bodyB.m_motion;
    const hkCapsuleShape* capA = (const hkCapsuleShape*)bodyA.m_shape;
    const hkCapsuleShape* capB = (const hkCapsuleShape*)bodyB.m_shape;

    hkVector4 segA[2];
    HK_XFORM_ONE(segA[0], capA->m_vertexA, xfA)
    HK_XFORM_ONE(segA[1], capA->m_vertexB, xfA)

    hkVector4 segB[2];
    HK_XFORM_ONE(segB[0], capB->m_vertexA, xfB)
    HK_XFORM_ONE(segB[1], capB->m_vertexB, xfB)

    hkVector4 dirA, dirB;
    dirA.x = segA[1].x - segA[0].x; dirA.y = segA[1].y - segA[0].y; dirA.z = segA[1].z - segA[0].z;
    dirB.x = segB[1].x - segB[0].x; dirB.y = segB[1].y - segB[0].y; dirB.z = segB[1].z - segB[0].z;

    hkCollideTriangleUtil::ClosestLineSegLineSegResult res;
    hkCollideTriangleUtil::closestLineSegLineSeg(segA[0], dirA, segB[0], dirB, res);

    float rsum = capB->m_radius + capA->m_radius;
    if (res.m_distanceSquared < rsum * rsum)
    {
        collector.addCdBodyPair(bodyA, bodyB);
    }

    hkTimerCommand(hkTtrcEnd);
}

// ---------------------------------------------------------------------------
// @ 0x010d5320
// Static registration helper: builds the AgentFuncs block for the
// capsule/capsule pair and hands it to the dispatcher (shape types 8/8).
// ---------------------------------------------------------------------------
void __cdecl hkCapsuleCapsuleAgent__registerAgent(hkCollisionDispatcher& dispatcher)
{
    hkAgentFuncs funcs;
    funcs.m_isFlipped = 0;
    funcs.m_isPredictive = 0;
    funcs.m_createFunc = (hkAgentCreateFunc)0x010d4280;
    funcs.m_getPenetrationsFunc = (hkAgentGetPenetrationsFunc)0x010d4ed0;
    funcs.m_getClosestPointFunc = (hkAgentGetClosestPointsFunc)0x010d4b00;
    funcs.m_linearCastFunc = (hkAgentLinearCastFunc)0x010ebc80;
    dispatcher.registerCollisionAgent(funcs, 8, 8);
}
// ---------------------------------------------------------------------------
// @ 0x010d5370
// hkSphereBoxAgent::createSphereBoxAgent (ordering vtable 0x014a46b8).
// ---------------------------------------------------------------------------
extern "C" void* hkSphereBoxAgent__create(const void* bodyA, const void* bodyB,
                                          const void* input, void* contactMgr)
{
    void* agent = hkMemory_s_instance->alloc(0x10, 0x1c);
    *(unsigned short*)((char*)agent + 4) = 0x10;
    *(unsigned short*)((char*)agent + 6) = 1;
    *(void**)((char*)agent + 8) = contactMgr;
    *(void**)agent = (void*)0x014a46b8;
    *(unsigned short*)((char*)agent + 0xc) = 0xffff;
    return agent;
}

// ---------------------------------------------------------------------------
// @ 0x010d53a0
// hkSymmetricAgent<hkSphereBoxAgent>::createSymmetricAgent (vtable 0x014a46ec).
// ---------------------------------------------------------------------------
extern "C" void* hkSymmetricSphereBoxAgent__create(const void* bodyA, const void* bodyB,
                                                   const void* input, void* contactMgr)
{
    void* agent = hkMemory_s_instance->alloc(0x10, 0x1c);
    *(unsigned short*)((char*)agent + 4) = 0x10;
    *(unsigned short*)((char*)agent + 6) = 1;
    *(void**)((char*)agent + 8) = contactMgr;
    *(unsigned short*)((char*)agent + 0xc) = 0xffff;
    *(void**)agent = (void*)0x014a46ec;
    return agent;
}
