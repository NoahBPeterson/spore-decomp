// Slice s010df100: hkSymmetricAgent<hkListAgent>, hkPhantomAgent, hkTransformAgent, hkSymmetricAgent<hkTransformAgent>.
// x87-era Havok 3.1.  Operation order is kept as in the binary.
#include "s010df100.h"

// ---------------------------------------------------------------------------------------------------
// flip helpers (hkSymmetricAgent*)
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

// ---------------------------------------------------------------------------------------------------
// Object with an hkArray at +0xc (scalar deleting destructor; vptr reset to the hkReferencedObject vtable 0x013ef094)
// ---------------------------------------------------------------------------------------------------
struct hkThreadMemory { void deallocateChunk(void* p, int nbytes, int memClass); };      // 0x0107db10
extern unsigned long g_hkThreadMemoryTls;                                                // 0x016e4174
struct hkReferencedObjectWithArray : hkReferencedObject {
    uint32_t m_pad8;                           // +8
    uint32_t* m_data;                          // +0xc   hkArray: data (4 byte elements)
    int m_size;                                // +0x10
    int m_capacityAndFlags;                    // +0x14  (bit 31: do not deallocate)
    hkReferencedObjectWithArray* destroy(unsigned flags);
};
// @ 0x010df100
hkReferencedObjectWithArray* hkReferencedObjectWithArray::destroy(unsigned flags)
{
    if (m_capacityAndFlags >= 0) {
        hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
        tm->deallocateChunk(m_data, (m_capacityAndFlags & 0x3fffffff) << 2, 0x14);
    }
    if (flags & 1) {
        hkMemory::s_instance->deallocateChunk(this, (int)m_memSizeAndFlags, 0x1c);
    }
    return this;
}

// ---------------------------------------------------------------------------------------------------
// hkSymmetricAgent<hkListAgent>
// ---------------------------------------------------------------------------------------------------
struct hkListAgent : hkCollisionAgent {
    uint32_t* m_agentsData;                    // +0xc
    int m_agentsSize;                          // +0x10
    int m_agentsCapacityAndFlags;              // +0x14
    uint32_t m_pad[4];                         // object size 0x28
    hkListAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // FUN_010dedf0
    virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
};
struct hkSymmetricAgent_hkListAgent : hkListAgent {
    hkSymmetricAgent_hkListAgent(const hkCdBody& A, const hkCdBody& B, const hkCollisionInput& input, hkContactMgr* mgr)
        : hkListAgent(B, A, input, mgr) {}
    HK_DECLARE_AGENT_ALLOCATOR(0x28)
    virtual void linearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input, hkCdPointCollector& collector, hkCdPointCollector* startCollector);
    static hkCollisionAgent* createListBAgent(const hkCdBody& A, const hkCdBody& B, const hkCollisionInput& input, hkContactMgr* mgr);
};

// @ 0x010df160  hkSymmetricAgent<hkListAgent>::linearCast
void hkSymmetricAgent_hkListAgent::linearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input, hkCdPointCollector& collector, hkCdPointCollector* startCollector)
{
    hkLinearCastCollisionInput flippedInput = input;
    flippedInput.m_path.x = -input.m_path.x;           // setNeg4
    flippedInput.m_path.y = -input.m_path.y;
    flippedInput.m_path.z = -input.m_path.z;
    flippedInput.m_path.w = -input.m_path.w;
    hkSymmetricAgentFlipCastCollector flip(input.m_path, &collector);
    if (startCollector) {
        hkSymmetricAgentFlipCastCollector startFlip(input.m_path, startCollector);
        hkListAgent::linearCast(bodyB, bodyA, flippedInput, flip, &startFlip);
    } else {
        hkListAgent::linearCast(bodyB, bodyA, flippedInput, flip, 0);
    }
}

// @ 0x010df280  hkListAgent::createListBAgent  (allocates the symmetric wrapper, 0x28 bytes)
hkCollisionAgent* hkSymmetricAgent_hkListAgent::createListBAgent(const hkCdBody& A, const hkCdBody& B, const hkCollisionInput& input, hkContactMgr* mgr)
{
    return new hkSymmetricAgent_hkListAgent(A, B, input, mgr);
}

// ---------------------------------------------------------------------------------------------------
// hkPhantomAgent
// ---------------------------------------------------------------------------------------------------
static inline const hkCdBody* hkCdBody_getRoot(const hkCdBody* b)
{
    while (b->m_parent) b = b->m_parent;
    return b;
}
extern void __cdecl hkAgentDefaultFunc();            // 0x00c2e4e0 (shared no-op used for the unused function slots)

struct hkPhantomAgent : hkCollisionAgent {            // 0x24 bytes
    const hkCdBody* m_rootA;                           // +0xc
    const hkCdBody* m_rootB;                           // +0x10
    hkPhantomCallbackShape* m_phantomShapeA;           // +0x14
    hkPhantomCallbackShape* m_phantomShapeB;           // +0x18
    int m_shapeTypeA;                                  // +0x1c
    int m_shapeTypeB;                                  // +0x20
    HK_DECLARE_AGENT_ALLOCATOR(0x24)
    hkPhantomAgent(const hkCdBody& A, const hkCdBody& B, hkContactMgr* mgr);
    virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
    virtual void cleanup();
    static void __cdecl staticGetPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
    static hkCollisionAgent* __cdecl createPhantomAgent(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkContactMgr*);
    static void __cdecl registerAgent(hkCollisionDispatcher* dispatcher);
};

// @ 0x010df350  hkPhantomAgent::cleanup
void hkPhantomAgent::cleanup()
{
    if (m_shapeTypeA == HK_SHAPE_PHANTOM_CALLBACK) {
        m_phantomShapeA->phantomLeaveEvent(m_rootA, m_rootB);
    }
    if (m_shapeTypeB == HK_SHAPE_PHANTOM_CALLBACK) {
        m_phantomShapeB->phantomLeaveEvent(m_rootB, m_rootA);
    }
    hkReferencedObject_deletingDtor(1);
}

// @ 0x010df390  hkPhantomAgent::getPenetrations
void hkPhantomAgent::getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
    collector.addCdBodyPair(bodyA, bodyB);
}

// @ 0x010df3b0  hkPhantomAgent::staticGetPenetrations
void __cdecl hkPhantomAgent::staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
    collector.addCdBodyPair(bodyA, bodyB);
}

// @ 0x010df3d0  hkPhantomAgent::hkPhantomAgent
hkPhantomAgent::hkPhantomAgent(const hkCdBody& A, const hkCdBody& B, hkContactMgr* mgr)
{
    m_contactMgr = mgr;
    m_referenceCount = 1;
    m_rootA = hkCdBody_getRoot(&A);
    m_rootB = hkCdBody_getRoot(&B);
    m_shapeTypeA = A.m_shape->getType();
    m_shapeTypeB = B.m_shape->getType();
}

// @ 0x010df440  hkPhantomAgent::createPhantomAgent
hkCollisionAgent* __cdecl hkPhantomAgent::createPhantomAgent(const hkCdBody& A, const hkCdBody& B, const hkCollisionInput& input, hkContactMgr* mgr)
{
    hkPhantomAgent* agent = new hkPhantomAgent(A, B, mgr);
    if (agent->m_shapeTypeA == HK_SHAPE_PHANTOM_CALLBACK) {
        hkPhantomCallbackShape* shape = (hkPhantomCallbackShape*)A.m_shape;
        shape->phantomEnterEvent(hkCdBody_getRoot(&A), hkCdBody_getRoot(&B), &input);
        agent->m_phantomShapeA = shape;
    }
    if (agent->m_shapeTypeB == HK_SHAPE_PHANTOM_CALLBACK) {
        hkPhantomCallbackShape* shape = (hkPhantomCallbackShape*)B.m_shape;
        shape->phantomEnterEvent(hkCdBody_getRoot(&B), hkCdBody_getRoot(&A), &input);
        agent->m_phantomShapeB = shape;
    }
    return agent;
}

// @ 0x010df500  hkPhantomAgent::registerAgent
void __cdecl hkPhantomAgent::registerAgent(hkCollisionDispatcher* dispatcher)
{
    hkAgentFuncs f;
    f.m_isFlipped = 0;
    f.m_createFunc = &hkPhantomAgent::createPhantomAgent;
    f.m_getPenetrationsFunc = &hkPhantomAgent::staticGetPenetrations;
    f.m_getClosestPointFunc = (hkAgentGetClosestPointsFunc)&hkAgentDefaultFunc;
    f.m_linearCastFunc = (hkAgentLinearCastFunc)&hkAgentDefaultFunc;
    f.m_isPredictive = 1;
    dispatcher->registerCollisionAgent(f, HK_SHAPE_PHANTOM_CALLBACK, -1);
    dispatcher->registerCollisionAgent(f, -1, HK_SHAPE_PHANTOM_CALLBACK);
}

// ---------------------------------------------------------------------------------------------------
// hkTransformAgent: wraps a child agent that works on the child shape of a transform shape
// ---------------------------------------------------------------------------------------------------
struct hkTransformAgent : hkCollisionAgent {           // 0x10 bytes
    hkCollisionAgent* m_childAgent;                    // +0xc
    HK_DECLARE_AGENT_ALLOCATOR(0x10)
    virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
    virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
    virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
    virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);
    virtual void cleanup();
    virtual void updateShapeCollectionFilter(const hkCdBody&, const hkCdBody&, const hkCollisionInput&);
    static hkTransformAgent* __cdecl createTransformAAgent(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkContactMgr*);
    static void __cdecl staticLinearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
    static void __cdecl staticGetClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
    static void __cdecl staticGetPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
};

// the child body of a transform shape: child shape, same key / parent, motion = transform composed with the shape transform
struct hkTransformedChildBody : hkCdBody {
    hkTransform m_transform;
    hkTransformedChildBody(const hkCdBody& A)
    {
        const hkTransformShape* shape = (const hkTransformShape*)A.m_shape;
        m_transform.setMul(A.m_motion->m_transform, shape->m_transform);
        m_parent = &A;
        m_motion = (const hkMotionState*)&m_transform;
        m_shapeKey = A.m_shapeKey;
        m_shape = shape->m_childShape;
    }
};

// @ 0x010df5d0  hkMotionState::operator= (word-wise copy of 0xb0 bytes)
hkMotionState& hkMotionState::operator=(const hkMotionState& other)
{
    uint32_t* d = (uint32_t*)this;
    const uint32_t* s = (const uint32_t*)&other;
    for (int i = 0; i < 0x2b; i++) d[i] = s[i];     // dwords 0 .. 0xaa
    m_h0 = other.m_h0;
    m_h1 = other.m_h1;
    return *this;
}

// @ 0x010df560  hkTransformAgent::cleanup
void hkTransformAgent::cleanup()
{
    m_childAgent->cleanup();
    hkReferencedObject_deletingDtor(1);
}

// @ 0x010df6b0  hkTransformAgent::createTransformAAgent
hkTransformAgent* __cdecl hkTransformAgent::createTransformAAgent(const hkCdBody& A, const hkCdBody& B, const hkCollisionInput& input, hkContactMgr* mgr)
{
    hkTransformAgent* agent = new hkTransformAgent;
    agent->m_contactMgr = mgr;
    agent->m_referenceCount = 1;
    // body A with the child shape and the composed motion (the whole motion state is copied first)
    const hkTransformShape* shape = (const hkTransformShape*)A.m_shape;
    const hkShape* child = shape->m_childShape;
    hkMotionState tmpMotion;
    tmpMotion = *A.m_motion;
    tmpMotion.m_transform.setMul(A.m_motion->m_transform, shape->m_transform);
    hkCdBody childBody;
    childBody.m_shape = child;
    childBody.m_shapeKey = A.m_shapeKey;
    childBody.m_motion = &tmpMotion;
    childBody.m_parent = &A;
    hkCollisionDispatcher* dispatcher = input.m_dispatcher;
    int typeA = child->getType();
    int typeB = B.m_shape->getType();
    const uint8_t (*table)[32] = input.m_createPredictiveAgents ? dispatcher->m_agent2TypesPredictive : dispatcher->m_agent2Types;
    uint8_t agentType = table[typeA][typeB];
    agent->m_childAgent = dispatcher->m_agent2Func[agentType].m_createFunc(childBody, B, input, mgr);
    return agent;
}

// @ 0x010df7a0  hkTransformAgent::processCollision
void hkTransformAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkProcessCollisionInput& input, hkProcessCollisionOutput& result)
{
    HK_TIMER_BEGIN("TtTransform");
    const hkTransformShape* shape = (const hkTransformShape*)bodyA.m_shape;
    const hkMotionState* m = bodyA.m_motion;
    hkMotionState tmp;                                   // only the parts below are initialised (as in the binary)
    tmp.m_transform.setMul(m->m_transform, shape->m_transform);
    tmp.m_centerOfMass0 = m->m_centerOfMass0;
    tmp.m_centerOfMass1 = m->m_centerOfMass1;
    tmp.m_rotation0.setMul(m->m_rotation0, shape->m_rotation);
    tmp.m_rotation1.setMul(m->m_rotation1, shape->m_rotation);
    // centerOfMassLocal = R * (com - shapeTranslation), evaluated as ((c*R_i2) + (b*R_i1)) + (a*R_i0)
    // X87-PRECISION: a, b, c (the differences) and the partial sums stay in 80-bit registers; only the three results are stored as floats.
    float a = m->m_centerOfMassLocal.x - shape->m_transform.m_trans.x;
    float b = m->m_centerOfMassLocal.y - shape->m_transform.m_trans.y;
    float c = m->m_centerOfMassLocal.z - shape->m_transform.m_trans.z;
    const hkTransform& R = shape->m_transform;
    tmp.m_centerOfMassLocal.x = (c * R.m_rot[0].z + b * R.m_rot[0].y) + a * R.m_rot[0].x;
    tmp.m_centerOfMassLocal.y = (c * R.m_rot[1].z + b * R.m_rot[1].y) + a * R.m_rot[1].x;
    tmp.m_centerOfMassLocal.z = (c * R.m_rot[2].z + b * R.m_rot[2].y) + a * R.m_rot[2].x;
    tmp.m_centerOfMassLocal.w = 0.0f;
    tmp.m_misc[0] = m->m_misc[0];
    tmp.m_misc[1] = m->m_misc[1];
    tmp.m_misc[2] = m->m_misc[2];
    tmp.m_misc[3] = m->m_misc[3];
    tmp.m_misc[4] = m->m_misc[4];
    hkCdBody childBody;
    childBody.m_shape = shape->m_childShape;
    childBody.m_shapeKey = bodyA.m_shapeKey;
    childBody.m_motion = &tmp;
    childBody.m_parent = &bodyA;
    m_childAgent->processCollision(childBody, bodyB, input, result);
    HK_TIMER_END();
}

// @ 0x010df9e0  hkTransformAgent::linearCast
void hkTransformAgent::linearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input, hkCdPointCollector& collector, hkCdPointCollector* startCollector)
{
    HK_TIMER_BEGIN("TtTransform");
    hkTransformedChildBody childBody(bodyA);
    m_childAgent->linearCast(childBody, bodyB, input, collector, startCollector);
    HK_TIMER_END();
}

// @ 0x010dfae0  hkTransformAgent::staticLinearCast
void __cdecl hkTransformAgent::staticLinearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input, hkCdPointCollector& collector, hkCdPointCollector* startCollector)
{
    HK_TIMER_BEGIN("TtTransform");
    hkTransformedChildBody childBody(bodyA);
    hkCollisionDispatcher* dispatcher = input.m_dispatcher;
    int typeA = childBody.m_shape->getType();
    int typeB = bodyB.m_shape->getType();
    uint8_t agentType = dispatcher->m_agent2Types[typeA][typeB];
    dispatcher->m_agent2Func[agentType].m_linearCastFunc(childBody, bodyB, input, collector, startCollector);
    HK_TIMER_END();
}

// @ 0x010dfc00  hkTransformAgent::getClosestPoints
void hkTransformAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector)
{
    HK_TIMER_BEGIN("TtTransform");
    hkTransformedChildBody childBody(bodyA);
    m_childAgent->getClosestPoints(childBody, bodyB, input, collector);
    HK_TIMER_END();
}

// @ 0x010dfd00  hkTransformAgent::staticGetClosestPoints
void __cdecl hkTransformAgent::staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector)
{
    HK_TIMER_BEGIN("TtTransform");
    hkTransformedChildBody childBody(bodyA);
    hkCollisionDispatcher* dispatcher = input.m_dispatcher;
    int typeA = childBody.m_shape->getType();
    int typeB = bodyB.m_shape->getType();
    uint8_t agentType = dispatcher->m_agent2Types[typeA][typeB];
    dispatcher->m_agent2Func[agentType].m_getClosestPointFunc(childBody, bodyB, input, collector);
    HK_TIMER_END();
}

// @ 0x010dfe10  hkTransformAgent::getPenetrations  (the timer is closed BEFORE the child call in the binary)
void hkTransformAgent::getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
    HK_TIMER_BEGIN("TtTransform");
    hkTransformedChildBody childBody(bodyA);
    HK_TIMER_END();
    m_childAgent->getPenetrations(childBody, bodyB, input, collector);
}

// @ 0x010dff10  hkTransformAgent::staticGetPenetrations
void __cdecl hkTransformAgent::staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
    HK_TIMER_BEGIN("TtTransform");
    hkTransformedChildBody childBody(bodyA);
    hkCollisionDispatcher* dispatcher = input.m_dispatcher;
    int typeA = childBody.m_shape->getType();
    int typeB = bodyB.m_shape->getType();
    uint8_t agentType = dispatcher->m_agent2Types[typeA][typeB];
    dispatcher->m_agent2Func[agentType].m_getPenetrationsFunc(childBody, bodyB, input, collector);
    HK_TIMER_END();
}

// @ 0x010e0020  hkTransformAgent::updateShapeCollectionFilter
void hkTransformAgent::updateShapeCollectionFilter(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input)
{
    hkTransformedChildBody childBody(bodyA);
    m_childAgent->updateShapeCollectionFilter(childBody, bodyB, input);
}

// ---------------------------------------------------------------------------------------------------
// hkSymmetricAgent<hkTransformAgent>
// ---------------------------------------------------------------------------------------------------
struct hkSymmetricAgent_hkTransformAgent : hkTransformAgent {
    virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
    virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
    virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);
};

// @ 0x010e0200  hkSymmetricAgent<hkTransformAgent>::getPenetrations
void hkSymmetricAgent_hkTransformAgent::getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
    hkSymmetricAgentFlipBodyCollector flip(collector);
    hkTransformAgent::getPenetrations(bodyB, bodyA, input, flip);
}

// @ 0x010e0240  hkSymmetricAgent<hkTransformAgent>::getClosestPoints
void hkSymmetricAgent_hkTransformAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector)
{
    hkSymmetricAgentFlipCollector flip(collector);
    hkTransformAgent::getClosestPoints(bodyB, bodyA, input, flip);
}

// @ 0x010e0280  hkSymmetricAgent<hkTransformAgent>::processCollision
void hkSymmetricAgent_hkTransformAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkProcessCollisionInput& input, hkProcessCollisionOutput& result)
{
    hkProcessCdPoint* pp = result.m_firstFreeContactPoint;
    hkTime oldToi = result.m_toiTime;
    hkTransformAgent::processCollision(bodyB, bodyA, input, result);
    for (; pp < result.m_firstFreeContactPoint; pp++) {
        pp->m_contact.setFlipped(pp->m_contact);
    }
    // fucompp + test ah,0x44 / jnp: flip when (oldToi != toiTime), NaN included
    if (oldToi != result.m_toiTime) {
        result.m_toiContact.m_separatingNormal.x = -result.m_toiContact.m_separatingNormal.x;
        result.m_toiContact.m_separatingNormal.y = -result.m_toiContact.m_separatingNormal.y;
        result.m_toiContact.m_separatingNormal.z = -result.m_toiContact.m_separatingNormal.z;
    }
}
