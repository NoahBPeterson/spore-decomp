// slice s010d18c0 (part b): hkSymmetricAgent<hkMultiSphereTriangleAgent> flip wrappers and the
// capsule/triangle agent factories.
//   0x010d25b0  hkSymmetricAgent<hkMultiSphereTriangleAgent>::getPenetrations: wraps the collector in an
//               hkSymmetricAgentFlipBodyCollector (vtable 0x014a43b4) and calls the agent with the bodies swapped.
//   0x010d2630  hkSymmetricAgent<hkMultiSphereTriangleAgent>::getClosestPoints: same with the point collector
//               (vtable 0x014a43a4) and HK_REAL_MAX early-out.
//   0x010d26b0  hkSymmetricAgent<hkMultiSphereTriangleAgent>::processCollision: swapped call, flips the new
//               contact points and the toi normal when the toi time changed.
//   0x010d2800  hkCapsuleTriangleAgent::createCapsuleTriangleAgent: allocates the 0x28-byte agent (memory class
//               0x1c), caches the triangle's point-distance terms (triangle = bodyB).
//   0x010d2860  hkCapsuleTriangleAgent::createTriangleCapsuleAgent: same object, triangle = bodyA, other vtable.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "../s010cbaa0/hk31_b005.h"

#define HK_REAL_MAX 3.40282e+38f      // 0x7f7fffee in this build

typedef uint16_t hkContactPointId;

class hkContactPoint
{
public:
    hkVector4 m_position;                          // +0x00
    hkVector4 m_separatingNormal;                  // +0x10 (w = distance)
    void setFlipped(const hkContactPoint& other);  // 0x010cecf0
};
struct hkProcessCdPoint { hkContactPoint m_contact; uint32_t m_extra[4]; };   // 0x30 bytes

struct hkContactMgr
{
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void removePoint(hkContactPointId id);   // slot 4 (+0x10)
};
class hkCollisionDispatcher;
struct hkCollisionInput
{
    hkCollisionDispatcher* m_dispatcher;           // +0
    uint32_t m_pad[3];
};
struct hkProcessCollisionInput : hkCollisionInput {};

struct hkCdPoint { hkContactPoint m_contact; const hkCdBody* m_cdBodyA; const hkCdBody* m_cdBodyB; };
// The flip collectors are the shared Havok 3.1 0xc-byte aggregates: vftable, early-out value, wrapped collector.
// The binary's inlined constructors store the wrapped collector first, then the early-out value, then the vftable,
// so the collectors are plain locals and the stores keep that order.
struct hkCdPointCollector
{
    void* m_vftable;                               // +0
    float m_earlyOutDistance;                      // +4
};
struct hkCdBodyPairCollector
{
    void* m_vftable;                               // +0
    char  m_earlyOut;                              // +4
};
struct hkProcessCollisionOutput
{
    hkProcessCdPoint* m_firstFreeContactPoint;     // +0x0000
    uint32_t m_pad0[3];
    hkContactPoint m_toiContact;                   // +0x0010
    hkProcessCdPoint m_contactPoints[256];         // +0x0030
    uint32_t m_toiProperties;                      // +0x3030
    float m_toiTime;                               // +0x3034
};

// vtable 0x014a43a4
struct hkSymmetricAgentFlipCollector : hkCdPointCollector
{
    hkCdPointCollector* m_original;                // +8
};
// vtable 0x014a43b4
struct hkSymmetricAgentFlipBodyCollector : hkCdBodyPairCollector
{
    hkCdBodyPairCollector* m_original;             // +8
};

class hkCollisionAgent : public hkReferencedObject
{
public:
    hkContactMgr* m_contactMgr;                    // +8
    virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
    virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
    virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);
};

// hkShape layout: hkReferencedObject (0x8) + m_userData (0xc); a triangle convex shape has the radius at
// +0xc and the three vertices at +0x10.
class hkConvexShape : public hkShape { public: float m_radius; };
class hkTriangleShape : public hkConvexShape { public: hkVector4 m_vertices[3]; };

struct hkCollideTriangleUtil
{
    struct PointTriangleDistanceCache { float m_data[5]; };   // fills the agent's +0x14 slot
    static void setupPointTriangleDistanceCache(const hkVector4* triangle, PointTriangleDistanceCache& cache);   // 0x01105e90
};

// ---- the wrapped multi-sphere/triangle agent (bodies only; the wrappers call its out-of-line methods) -------------
class hkMultiSphereTriangleAgent
{
public:
    void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
    void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
    void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);
};

class hkSymmetricAgent_hkMultiSphereTriangleAgent : public hkMultiSphereTriangleAgent
{
public:
    void getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector);
    void getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector);
    void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkProcessCollisionInput& input, hkProcessCollisionOutput& result);
};

// ---- capsule/triangle agents (0x28 bytes: vptr8 + class id/points 0x14 + triangle cache 0x14) --------------------
class hkCapsuleTriangleAgent : public hkCollisionAgent
{
public:
    hkContactPointId m_contactPointId[3];          // +0x0c
    char             m_pad[2];                     // +0x12
    hkCollideTriangleUtil::PointTriangleDistanceCache m_triangleCache;   // +0x14

    hkCapsuleTriangleAgent(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkContactMgr* mgr)
    {
        m_contactPointId[0] = 0xffff;
        m_contactPointId[1] = 0xffff;
        m_contactPointId[2] = 0xffff;
        m_contactMgr = mgr;
        hkCollideTriangleUtil::setupPointTriangleDistanceCache(
            static_cast<const hkTriangleShape*>(bodyB.m_shape)->m_vertices, m_triangleCache);
    }

    static hkCollisionAgent* createCapsuleTriangleAgent(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                        const hkCollisionInput& input, hkContactMgr* mgr);
    static hkCollisionAgent* createTriangleCapsuleAgent(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                        const hkCollisionInput& input, hkContactMgr* mgr);
    void cleanup();
};

class hkTriangleCapsuleAgent : public hkCapsuleTriangleAgent
{
public:
    hkTriangleCapsuleAgent(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkContactMgr* mgr)
        : hkCapsuleTriangleAgent(bodyB, bodyA, input, mgr) {}
};

// @ 0x010d25b0
void hkSymmetricAgent_hkMultiSphereTriangleAgent::getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                                  const hkCollisionInput& input,
                                                                  hkCdBodyPairCollector& collector)
{
    hkSymmetricAgentFlipBodyCollector flip;
    flip.m_original = &collector;
    flip.m_earlyOut = 0;
    flip.m_vftable = (void*)0x014a43b4;
    hkMultiSphereTriangleAgent::getPenetrations(bodyB, bodyA, input, flip);
}

// @ 0x010d2630
void hkSymmetricAgent_hkMultiSphereTriangleAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                                   const hkCollisionInput& input,
                                                                   hkCdPointCollector& collector)
{
    hkSymmetricAgentFlipCollector flip;
    flip.m_original = &collector;
    flip.m_earlyOutDistance = HK_REAL_MAX;
    flip.m_vftable = (void*)0x014a43a4;
    hkMultiSphereTriangleAgent::getClosestPoints(bodyB, bodyA, input, flip);
}

// @ 0x010d26b0
void hkSymmetricAgent_hkMultiSphereTriangleAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                                   const hkProcessCollisionInput& input,
                                                                   hkProcessCollisionOutput& result)
{
    hkProcessCdPoint* pp = result.m_firstFreeContactPoint;
    float oldToi = result.m_toiTime;
    hkMultiSphereTriangleAgent::processCollision(bodyB, bodyA, input, result);
    for (; pp < result.m_firstFreeContactPoint; pp++)
        pp->m_contact.setFlipped(pp->m_contact);
    if (oldToi != result.m_toiTime)
    {
        result.m_toiContact.m_separatingNormal.x = -result.m_toiContact.m_separatingNormal.x;
        result.m_toiContact.m_separatingNormal.y = -result.m_toiContact.m_separatingNormal.y;
        result.m_toiContact.m_separatingNormal.z = -result.m_toiContact.m_separatingNormal.z;
    }
}

// @ 0x010d27c0
void hkCapsuleTriangleAgent::cleanup()
{
    for (int i = 0; i < 3; i++)
    {
        if (m_contactPointId[i] != (hkContactPointId)0xffff)
            m_contactMgr->removePoint(m_contactPointId[i]);
    }
    delete this;
}

// @ 0x010d2800
hkCollisionAgent* hkCapsuleTriangleAgent::createCapsuleTriangleAgent(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                                     const hkCollisionInput& input, hkContactMgr* mgr)
{
    return new hkCapsuleTriangleAgent(bodyA, bodyB, input, mgr);
}

// @ 0x010d2860
hkCollisionAgent* hkCapsuleTriangleAgent::createTriangleCapsuleAgent(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                                     const hkCollisionInput& input, hkContactMgr* mgr)
{
    return new hkTriangleCapsuleAgent(bodyA, bodyB, input, mgr);
}
