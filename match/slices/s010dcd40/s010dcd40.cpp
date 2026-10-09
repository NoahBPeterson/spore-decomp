// Slice s010dcd40: hkSymmetricAgent<hkHeightFieldAgent> flips, hkConvexListConvexShape, hkConvexListAgent.
// Everything here is x87 era Havok 3.1; operation order is kept exactly as in the binary.
#include "s010dcd40.h"

// ---------------------------------------------------------------------------------------------------
// hkSymmetric* flip helpers (collectors that swap bodies back / negate the path)
// ---------------------------------------------------------------------------------------------------
struct hkSymmetricAgentFlipCollector : hkCdPointCollector {            // vtable 0x014a43a4
    hkCdPointCollector& m_original;                                     // +8
    hkSymmetricAgentFlipCollector(hkCdPointCollector& c) : m_original(c) { m_earlyOutDistance = HK_REAL_MAX; }
    virtual void addCdPoint(const hkCdPoint& point);
};
struct hkSymmetricAgentFlipBodyCollector : hkCdBodyPairCollector {     // vtable 0x014a43b4
    hkCdBodyPairCollector& m_original;                                  // +8
    hkSymmetricAgentFlipBodyCollector(hkCdBodyPairCollector& c) : m_original(c) { m_earlyOut = 0; }
    virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b);
};
struct hkSymmetricAgentFlipCastCollector : hkCdPointCollector {        // vtable 0x014a43ac
    uint32_t m_pad[2];
    hkVector4 m_path;                                                   // +0x10
    hkCdPointCollector* m_original;                                     // +0x20
    hkSymmetricAgentFlipCastCollector(const hkVector4& path, hkCdPointCollector* c) : m_path(path), m_original(c) { m_earlyOutDistance = HK_REAL_MAX; }
    virtual void addCdPoint(const hkCdPoint& point);
};

// hkSymmetricAgent<hkHeightFieldAgent> / hkSymmetricAgentLinearCast<hkHeightFieldAgent>
struct hkSymmetricAgentLinearCast_hkHeightFieldAgent : hkHeightFieldAgent {
    hkSymmetricAgentLinearCast_hkHeightFieldAgent(const hkCdBody& A, const hkCdBody& B, const hkCollisionInput& input, hkContactMgr* mgr)
        : hkHeightFieldAgent(B, A, input, mgr) {}
    HK_DECLARE_AGENT_ALLOCATOR
    virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkProcessCollisionInput& input, hkProcessCollisionOutput& result);
    static void __stdcall staticGetClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
    static void __stdcall staticLinearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
};
extern void __cdecl hkHeightFieldAgent_staticGetClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);   // FUN_010db380
extern void __cdecl hkHeightFieldAgent_staticLinearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*); // FUN_010dbd30

// @ 0x010dcd40  hkSymmetricAgentLinearCast<hkHeightFieldAgent>::processCollision
void hkSymmetricAgentLinearCast_hkHeightFieldAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkProcessCollisionInput& input, hkProcessCollisionOutput& result)
{
    hkProcessCdPoint* pp = result.m_firstFreeContactPoint;
    hkTime oldToi = result.m_toiTime;
    hkHeightFieldAgent::processCollision(bodyB, bodyA, input, result);
    for (; pp < result.m_firstFreeContactPoint; pp++) {
        pp->m_contact.setFlipped(pp->m_contact);
    }
    // binary: fucompp + test ah,0x44 / jnp  => taken when (oldToi != toiTime) including NaN
    if (oldToi != result.m_toiTime) {
        // hkToiEvent::flip(): negate the separating normal xyz (distance in w is kept)
        result.m_toiContact.m_separatingNormal.x = -result.m_toiContact.m_separatingNormal.x;
        result.m_toiContact.m_separatingNormal.y = -result.m_toiContact.m_separatingNormal.y;
        result.m_toiContact.m_separatingNormal.z = -result.m_toiContact.m_separatingNormal.z;
    }
}

// @ 0x010dce00  hkSymmetricAgentLinearCast<hkHeightFieldAgent>::staticGetClosestPoints
void __stdcall hkSymmetricAgentLinearCast_hkHeightFieldAgent::staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector)
{
    hkSymmetricAgentFlipCollector flip(collector);
    hkHeightFieldAgent_staticGetClosestPoints(bodyB, bodyA, input, flip);
}

// @ 0x010dce40  hkSymmetricAgentLinearCast<hkHeightFieldAgent>::staticLinearCast
void __stdcall hkSymmetricAgentLinearCast_hkHeightFieldAgent::staticLinearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input, hkCdPointCollector& collector, hkCdPointCollector* startCollector)
{
    hkLinearCastCollisionInput flippedInput = input;
    // setNeg4: each of x,y,z,w negated (fchs)
    flippedInput.m_path.x = -input.m_path.x;
    flippedInput.m_path.y = -input.m_path.y;
    flippedInput.m_path.z = -input.m_path.z;
    flippedInput.m_path.w = -input.m_path.w;

    hkSymmetricAgentFlipCastCollector flip(input.m_path, &collector);
    if (startCollector) {
        hkSymmetricAgentFlipCastCollector startFlip(input.m_path, startCollector);
        hkHeightFieldAgent_staticLinearCast(bodyB, bodyA, flippedInput, flip, &startFlip);
    } else {
        hkHeightFieldAgent_staticLinearCast(bodyB, bodyA, flippedInput, flip, 0);
    }
}

// @ 0x010dcf80  hkHeightFieldAgent::createHeightFieldAAgent  (allocates the symmetric wrapper, 0x18 bytes)
struct hkHeightFieldAgentCreator {
    static hkCollisionAgent* createHeightFieldAAgent(const hkCdBody& A, const hkCdBody& B, const hkCollisionInput& input, hkContactMgr* mgr);
};
hkCollisionAgent* hkHeightFieldAgentCreator::createHeightFieldAAgent(const hkCdBody& A, const hkCdBody& B, const hkCollisionInput& input, hkContactMgr* mgr)
{
    return new hkSymmetricAgentLinearCast_hkHeightFieldAgent(A, B, input, mgr);
}

// ---------------------------------------------------------------------------------------------------
// hkConvexListConvexShape
// ---------------------------------------------------------------------------------------------------
// @ 0x010dd050  hkConvexListConvexShape::getFirstVertex
void hkConvexListConvexShape::getFirstVertex(hkVector4& v) const
{
    m_subShapesData[0].m_shape->getFirstVertex(v);
}

// @ 0x010dd060  hkConvexListConvexShape::getCollisionSpheres
const hkSphere* hkConvexListConvexShape::getCollisionSpheres(hkSphere* sphereBuffer) const
{
    hkSphere* buf = sphereBuffer;
    for (int i = 0; i < m_subShapesSize; i++) {
        const hkConvexShape* child = m_subShapesData[i].m_shape;
        hkCollisionSpheresInfo info;
        child->getCollisionSpheres(buf);
        child->getCollisionSpheresInfo(info);
        buf += info.m_numSpheres;
    }
    return sphereBuffer;
}

// @ 0x010dd380  hkConvexListConvexShape::getCollisionSpheresInfo
void hkConvexListConvexShape::getCollisionSpheresInfo(hkCollisionSpheresInfo& infoOut) const
{
    infoOut.m_numSpheres = 0;
    infoOut.m_useBuffer = 1;
    for (int i = 0; i < m_subShapesSize; i++) {
        hkCollisionSpheresInfo info;
        m_subShapesData[i].m_shape->getCollisionSpheresInfo(info);
        infoOut.m_numSpheres += info.m_numSpheres;
    }
}

// @ 0x010dd300  hkConvexListConvexShape::convertVertexIdsToVertices
// vertex id: high byte = sub shape index, low byte = vertex id inside the sub shape
void hkConvexListConvexShape::convertVertexIdsToVertices(const uint16_t* ids, int numIds, hkCdVertex* verticesOut) const
{
    for (int i = 0; i < numIds; i++) {
        uint32_t idx = (uint16_t)(*ids) >> 8;
        uint32_t localId = (uint32_t)(*ids) & 0xff;
        m_subShapesData[idx].m_shape->convertVertexIdsToVertices((const uint16_t*)&localId, 1, verticesOut);
        verticesOut->wBits = ((verticesOut->wBits & 0xc0ffffff) + (idx << 8)) | 0x3f000000;
        ids++;
        verticesOut++;
    }
}

// @ 0x010dd580  hkConvexListConvexShape::getSupportingVertex
void hkConvexListConvexShape::getSupportingVertex(const hkVector4& dir, hkCdVertex& out) const
{
    float best = -3.40282e+38f;     // 0xff7fffee
    int bestIdx = 0;
    for (int i = 0; i < m_subShapesSize; i++) {
        hkCdVertex v;
        m_subShapesData[i].m_shape->getSupportingVertex(dir, v);
        // X87-PRECISION: ((vx*dx)+(vy*dy))+(vz*dz) stays in an 80-bit register and is compared against the
        // float 'best' without being rounded first; only the winning value is stored (rounded) into best.
        float d = (v.x * dir.x + v.y * dir.y) + v.z * dir.z;
        if (best < d) {
            out = v;
            best = d;
            bestIdx = i;
        }
    }
    out.wBits = ((out.wBits & 0xc0ffffff) + (bestIdx << 8)) | 0x3f000000;
}

// ---------------------------------------------------------------------------------------------------
// hkProcessCollisionOutputBackup
// ---------------------------------------------------------------------------------------------------
struct hkProcessCollisionOutputBackup {
    hkProcessCdPoint* m_firstFreeContactPoint;     // +0
    uint32_t m_potentialContacts[0x402 - 1];       // +4 .. 0x100c  (0x402 dwords copied starting at +4)
    uint32_t m_pad;                                // +0x100c (not touched)
    uint32_t m_toiContact[8];                      // +0x1010 .. 0x102c
    hkTime   m_toiTime;                            // +0x1030
    uint32_t m_toiProperties;                      // +0x1034
    hkProcessCollisionOutputBackup(const hkProcessCollisionOutput& out);
    void restore(hkProcessCollisionOutput& out);
};
// @ 0x010dd1d0  hkProcessCollisionOutputBackup::hkProcessCollisionOutputBackup
hkProcessCollisionOutputBackup::hkProcessCollisionOutputBackup(const hkProcessCollisionOutput& out)
{
    m_firstFreeContactPoint = out.m_firstFreeContactPoint;
    m_toiTime = out.m_toiTime;
    const uint32_t* src = (const uint32_t*)&out.m_toiContact;
    for (int i = 0; i < 8; i++) m_toiContact[i] = src[i];
    m_toiProperties = out.m_toiProperties;
    if (out.m_potentialContacts) {
        const uint32_t* s = out.m_potentialContacts;
        uint32_t* d = (uint32_t*)this + 1;
        for (int i = 0; i < 0x402; i++) d[i] = s[i];
    }
}
// @ 0x010dd260  hkProcessCollisionOutputBackup::restore
void hkProcessCollisionOutputBackup::restore(hkProcessCollisionOutput& out)
{
    out.m_firstFreeContactPoint = m_firstFreeContactPoint;
    out.m_toiTime = m_toiTime;
    uint32_t* dst = (uint32_t*)&out.m_toiContact;
    for (int i = 0; i < 8; i++) dst[i] = m_toiContact[i];
    out.m_toiProperties = m_toiProperties;
    if (out.m_potentialContacts) {
        uint32_t* d = out.m_potentialContacts;
        const uint32_t* s = (const uint32_t*)this + 1;
        for (int i = 0; i < 0x402; i++) d[i] = s[i];
    }
}

// ---------------------------------------------------------------------------------------------------
// hkConvexListAgent
// ---------------------------------------------------------------------------------------------------
struct hkClosestCdPointCollector : hkCdPointCollector {                // vtable 0x013ef52c
    uint32_t m_pad[2];
    hkContactPoint m_hitContact;                                        // +0x10 (distance = w @ +0x2c)
    const hkCdBody* m_hitRootA;                                         // +0x30 (null: no hit)
    uint32_t m_pad3[3];
    hkClosestCdPointCollector() { m_earlyOutDistance = HK_REAL_MAX; m_hitContact.m_separatingNormal.w = HK_REAL_MAX; m_hitRootA = 0; }
    virtual void addCdPoint(const hkCdPoint& point);
};
struct hkConvexListHullPenetrationCollector : hkCdBodyPairCollector {   // vtable 0x014a4abc
    hkConvexListHullPenetrationCollector() { m_earlyOut = 0; }
    virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b);
};
struct hkConvexListHullCastCollector : hkCdPointCollector {            // vtable 0x014a4ac4
    hkBool m_hit;                                                       // +8
    uint32_t m_pad[0xa - 3];
    hkContactPoint m_contact;                                           // +0x10 (distance w @ +0x2c)
    hkConvexListHullCastCollector() { m_earlyOutDistance = HK_REAL_MAX; m_hit = 0; m_contact.m_separatingNormal.w = HK_REAL_MAX; }
    virtual void addCdPoint(const hkCdPoint& point);
};

struct hkConvexListAgent : hkPredGskfAgent {
    hkCollisionDispatcher* m_dispatcher;        // +0x80
    hkBool m_inGskMode;                         // +0x84
    uint8_t m_pad3[3];
    uint32_t m_pad4[2];                         // object size 0x90
    HK_DECLARE_AGENT_ALLOCATOR
    hkConvexListAgent(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkContactMgr* mgr);
    virtual void invalidateTim(hkCollisionInput& input);
    virtual void warpTime(hkTime oldTime, hkTime newTime, hkCollisionInput& input);
    virtual void cleanup();
    virtual void removePoint(hkContactPointId id);
    virtual void commitPotential(hkContactPointId id);
    virtual void createZombie(hkContactPointId id);
    static hkCollisionAgent* createConvexListAgent(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkContactMgr*);
    static hkCollisionAgent* createListConvexAgent(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkContactMgr*);
    static void staticGetClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
    static void staticGetPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
    static void staticLinearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
};
// the symmetric wrapper used for list-vs-convex pairs (vtable 0x014a4b70, derived from hkConvexListAgent)
struct hkSymmetricAgent_hkConvexListAgent : hkConvexListAgent {
    hkSymmetricAgent_hkConvexListAgent(const hkCdBody& A, const hkCdBody& B, const hkCollisionInput& input, hkContactMgr* mgr)
        : hkConvexListAgent(B, A, input, mgr) {}
    HK_DECLARE_AGENT_ALLOCATOR
    virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);
};

// callees (not part of this slice)
extern void __cdecl hkAgent1nMachine_InvalidateTim(void* track, hkCollisionInput& input);                 // FUN_01103850
extern void __cdecl hkAgent1nMachine_WarpTime(void* track, hkTime oldTime, hkTime newTime, hkCollisionInput& input);   // FUN_01103930
extern void __cdecl hkAgent1nMachine_Destroy(void* track, hkCollisionDispatcher* dispatcher, hkContactMgr* mgr);       // FUN_01104760
extern void __cdecl hkGskManifold_cleanup(hkGskManifold* manifold, hkContactMgr* mgr);                    // _hkGskManifold_cleanup
extern void __cdecl hkAgent1nMachine_RemovePoint(void* track, int index);                                  // 0x0110fd70 (hkGskManifold_removePoint)
extern void __cdecl hkShapeCollectionAgent_staticGetClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
extern void __cdecl hkShapeCollectionAgent_staticGetPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
extern void __cdecl hkConvexListAgent_staticGetClosestPointsChildren(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);   // FUN_010dd410
extern void __cdecl hkConvexListAgent_staticLinearCastChildren(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*); // FUN_010dd450

// @ 0x010dd0c0  hkConvexListAgent::invalidateTim
void hkConvexListAgent::invalidateTim(hkCollisionInput& input)
{
    if (m_inGskMode) {
        hkGskBaseAgent::invalidateTim(input);
        return;
    }
    hkAgent1nMachine_InvalidateTim((char*)this + 0x30, input);
}

// @ 0x010dd0f0  hkConvexListAgent::warpTime
void hkConvexListAgent::warpTime(hkTime oldTime, hkTime newTime, hkCollisionInput& input)
{
    if (m_inGskMode) {
        hkGskBaseAgent::warpTime(oldTime, newTime, input);
        return;
    }
    hkAgent1nMachine_WarpTime((char*)this + 0x30, oldTime, newTime, input);
}

// @ 0x010dd120  hkConvexListAgent::removePoint
void hkConvexListAgent::removePoint(hkContactPointId id)
{
    if (m_inGskMode) {
        hkGskfAgent::removePoint(id);
    }
}

// @ 0x010dd140  hkConvexListAgent::commitPotential
void hkConvexListAgent::commitPotential(hkContactPointId id)
{
    if (m_inGskMode) {
        hkGskfAgent::commitPotential(id);
    }
}

// @ 0x010dd160  hkConvexListAgent::createZombie
void hkConvexListAgent::createZombie(hkContactPointId id)
{
    if (m_inGskMode) {
        hkGskfAgent::createZombie(id);
    }
}

// @ 0x010dd180  hkConvexListAgent::cleanup
void hkConvexListAgent::cleanup()
{
    if (m_inGskMode) {
        hkGskManifold_cleanup(&m_manifold, m_contactMgr);
        hkReferencedObject_deletingDtor(1);      // virtual deleting destructor, flag 1 (vtable slot 0)
        return;
    }
    hkAgent1nMachine_Destroy((char*)this + 0x30, m_dispatcher, m_contactMgr);
    hkReferencedObject_deletingDtor(1);
}

// temporary "body B as one convex hull" : hkCdBody whose shape is a temp hkConvexListConvexShape view of B's list
struct hkConvexListHullBody : hkCdBody {
    hkConvexListConvexShape m_hull;
    hkConvexListHullBody(const hkCdBody& B) : m_hull(*(const hkConvexListShape*)B.m_shape)
    {
        m_shape = &m_hull;
        m_shapeKey = B.m_shapeKey;
        m_motion = B.m_motion;
        m_parent = &B;
    }
};

// @ 0x010dd640  hkConvexListAgent::hkConvexListAgent
hkConvexListAgent::hkConvexListAgent(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkContactMgr* mgr)
    : hkPredGskfAgent(bodyA, hkConvexListHullBody(bodyB), mgr)
{
    m_dispatcher = input.m_dispatcher;
    m_inGskMode = 1;
    hkConvexListHullBody hullB(bodyB);
    hkTransform aTb;
    aTb.setMulInverseMul(*bodyA.m_motion, *bodyB.m_motion);
    m_cache.init((const hkConvexShape*)bodyA.m_shape, &hullB.m_hull, aTb);
    m_separatingNormal.w = -1.0f;            // 0xbf800000
    m_timeOfSeparatingNormal = -1.0f;
}

// @ 0x010dd750  hkConvexListAgent::createConvexListAgent
hkCollisionAgent* hkConvexListAgent::createConvexListAgent(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkContactMgr* mgr)
{
    if (mgr) {
        return new hkConvexListAgent(bodyA, bodyB, input, mgr);
    }
    return new hkGskBaseAgent(bodyA, bodyB, 0);
}

// @ 0x010de010  hkConvexListAgent::createListConvexAgent
hkCollisionAgent* hkConvexListAgent::createListConvexAgent(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkContactMgr* mgr)
{
    if (mgr) {
        return new hkSymmetricAgent_hkConvexListAgent(bodyA, bodyB, input, mgr);
    }
    return new hkGskBaseAgent(bodyA, bodyB, 0);
}

// @ 0x010dd7b0  hkConvexListAgent::staticGetClosestPoints
void hkConvexListAgent::staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector)
{
    HK_TIMER_BEGIN_LIST("LtCvxList", "checkHull");
    hkConvexListHullBody hullB(bodyB);
    hkConvexListHullPenetrationCollector penetration;
    hkGskBaseAgent::staticGetPenetrations(bodyA, hullB, input, penetration);
    if (penetration.m_earlyOut) {
        // hull is penetrated: query the children
        HK_TIMER_SPLIT_LIST("Stchildren");
        hkSymmetricAgentFlipCollector flip(collector);
        hkShapeCollectionAgent_staticGetClosestPoints(bodyB, bodyA, input, flip);
    } else {
        hkClosestCdPointCollector hull;
        hkGskBaseAgent::staticGetClosestPoints(bodyA, hullB, input, hull);
        if (hull.m_hitRootA) {
            const hkConvexListShape* list = (const hkConvexListShape*)bodyB.m_shape;
            // binary: fcomp + test ah,0x41 / jne => children path unless (hullDistance > minDistance), NaN goes to children
            if (hull.m_hitContact.m_separatingNormal.w > list->m_minDistanceToUseConvexHullForGsk) {
                hkCdPoint point;
                point.m_contact = hull.m_hitContact;
                point.m_cdBodyA = &bodyA;
                point.m_cdBodyB = &bodyB;
                collector.addCdPoint(point);
            } else {
                HK_TIMER_SPLIT_LIST("Stchildren");
                hkConvexListAgent_staticGetClosestPointsChildren(bodyA, bodyB, input, collector);
            }
        }
    }
    HK_TIMER_END_LIST();
}

// @ 0x010dda70  hkConvexListAgent::staticGetPenetrations
void hkConvexListAgent::staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
    HK_TIMER_BEGIN_LIST("LtCvxList", "checkHull");
    hkConvexListHullBody hullB(bodyB);
    hkConvexListHullPenetrationCollector penetration;
    hkGskBaseAgent::staticGetPenetrations(bodyA, hullB, input, penetration);
    if (penetration.m_earlyOut) {
        HK_TIMER_SPLIT_LIST("Stchildren");
        hkSymmetricAgentFlipBodyCollector flip(collector);
        hkShapeCollectionAgent_staticGetPenetrations(bodyB, bodyA, input, flip);
    }
    HK_TIMER_END_LIST();
}

// @ 0x010ddc30  hkConvexListAgent::staticLinearCast
void hkConvexListAgent::staticLinearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input, hkCdPointCollector& collector, hkCdPointCollector* startCollector)
{
    HK_TIMER_BEGIN_LIST("LtCvsListAgent", "checkHull");
    hkConvexListHullBody hullB(bodyB);
    hkConvexListHullCastCollector hull;
    hkGskBaseAgent::staticLinearCast(bodyA, hullB, input, hull, &hull);
    if (hull.m_hit) {
        HK_TIMER_SPLIT_LIST("Stchild");
        hkConvexListAgent_staticLinearCastChildren(bodyA, bodyB, input, collector, startCollector);
    }
    HK_TIMER_END_LIST();
}

// @ 0x010ddde0  tail forwarder to hkConvexListAgent::staticLinearCast (same 5 stdcall args)
void __stdcall hkConvexListAgent_staticLinearCastForwarder(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input, hkCdPointCollector& collector, hkCdPointCollector* startCollector)
{
    hkConvexListAgent::staticLinearCast(bodyA, bodyB, input, collector, startCollector);
}

// @ 0x010dde90  flipped getClosestPoints for the symmetric wrapper (bodies swapped, collector flipped)
void __stdcall hkSymmetricAgent_hkConvexListAgent_staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector)
{
    hkSymmetricAgentFlipCollector flip(collector);
    hkConvexListAgent::staticGetClosestPoints(bodyB, bodyA, input, flip);
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
