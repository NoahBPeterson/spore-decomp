// Havok 3.1.0 slice s010e6530: hkMultiSphereAgent (constructor, factories), the hkSymmetricAgent<hkMultiSphereAgent>
// wrappers and hkBvAgent (constructor, factory, cleanup/time/point callbacks, filter update, processCollision,
// linearCast, staticLinearCast, getClosestPoints).
// Equivalent portable source (not byte-exact). Operation order of the x87 math is taken from the disassembly.
#include "../s010e1340/hk31_agents.h"
#include <math.h>

// ---------------------------------------------------------------------------------------------------------
// monitor stream: the list timer (command 'L' + name, with the name of the first split) and the list end
// ---------------------------------------------------------------------------------------------------------
extern const char hkMonitorListEndTag[];                  // string "lt" at 0x0143CD94
struct hkMonitorListCommand { const char* m_commandAndMonitor; uint32_t m_time0; uint32_t m_time1; const char* m_nameOfFirstSplit; };   // 0x10 bytes (32-bit)
#define HK_TIMER_BEGIN_LIST(name, firstSplit) do { \
	void* hkEnd_ = hkTlsGet(g_hkMonitorStreamEndTls); \
	if (hkTlsGet(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
		hkMonitorListCommand* c_ = (hkMonitorListCommand*)hkTlsGet(g_hkMonitorStreamCurrentTls); \
		c_->m_commandAndMonitor = name; \
		c_->m_nameOfFirstSplit = firstSplit; \
		c_->m_time0 = HK_RDTSC32(); \
		hkTlsSet(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_SPLIT_LIST(name) HK_TIMER_COMMAND(name)
#define HK_TIMER_END_LIST()       HK_TIMER_COMMAND(hkMonitorListEndTag)

// ---------------------------------------------------------------------------------------------------------
// helpers
// ---------------------------------------------------------------------------------------------------------
// The agent factory lookup used by the compound agents: the type pair indexes the 32x32 agent table (the predictive table
// when the input asks for predictive agents) and the entry selects the factory in hkCollisionDispatcher::m_agent2Func.
static inline hkCollisionAgent* hkCreateAgent(const hkCollisionInput& input, const hkCdBody& a, const hkCdBody& b, hkContactMgr* mgr)
{
	hkCollisionDispatcher* dispatcher = (hkCollisionDispatcher*)input.m_dispatcher;
	int typeA = a.m_shape->getType();
	int typeB = b.m_shape->getType();
	const uint8_t (*table)[32] = input.m_createPredictiveAgents ? dispatcher->m_agent2TypesPred : dispatcher->m_agent2Types;
	return dispatcher->m_agent2Func[table[typeA][typeB]].m_createFunc(a, b, input, mgr);
}

// The stack-allocated collectors of hkBvAgent (vtable 0x014A4ABC and 0x014A4AC4 in the binary).
class hkAnyCdBodyPairCollector : public hkCdBodyPairCollector
{
public:
	hkAnyCdBodyPairCollector() { m_earlyOut = hkBool(false); }
	virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b);          // 0x010EDDC0: marks "something overlaps"
};
class hkSimpleClosestContactCollector : public hkCdPointCollector
{
public:
	hkSimpleClosestContactCollector() : m_hitPointSet(false)
	{
		m_earlyOutDistance = hkRealMax();
		m_contact.m_separatingNormal.w = hkRealMax();
	}
	virtual void addCdPoint(const hkCdPoint& point);                           // 0x010EDDD0
	hkBool m_hitPointSet;                                                       // +8
	hkContactPoint m_contact;                                                   // +0x10
};

// ---------------------------------------------------------------------------------------------------------
// hkMultiSphereAgent
// ---------------------------------------------------------------------------------------------------------
// @ 0x010e6530
// One sub agent per sphere of the multi sphere shape of body A: each pairs a temporary sphere body (placed at the sphere
// centre through a copy of A's motion state) against body B.
hkMultiSphereAgent::hkMultiSphereAgent(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkContactMgr* mgr)
	: hkCollisionAgent(mgr)
{
	m_agents.m_data = m_agents.m_storage;
	m_agents.m_size = 0;
	m_agents.m_capacityAndFlags = (int)0x80000004;

	const hkMultiSphereShapeView* multiSphere = (const hkMultiSphereShapeView*)bodyA.m_shape;
	int numSpheres = multiSphere->m_numSpheres;
	if (m_agents.getCapacity() < numSpheres)
	{
		int newCapacity = m_agents.getCapacity() * 2;
		if (numSpheres >= newCapacity)
			newCapacity = numSpheres;
		hkArrayUtil::_reserveExactly(&m_agents, newCapacity, 8);
	}

	hkSphereShape sphere(0.0f);
	hkMotionState motionCopy;
	motionCopy = *(const hkMotionState*)bodyA.m_motion;
	const hkMotionState* motionA = (const hkMotionState*)bodyA.m_motion;

	hkCdBody sphereBody;
	sphereBody.m_motion = &motionCopy;
	sphereBody.m_parent = &bodyA;

	const hkVector4* spheres = multiSphere->m_spheres;
	for (int i = 0; i < numSpheres; ++i)
	{
		// X87-PRECISION: the products and partial sums stay on the x87 stack; x and y are stored once, z is kept on the stack.
		hkX87Real cx = spheres[i].x;
		hkX87Real cy = spheres[i].y;
		hkX87Real cz = spheres[i].z;
		float xr = (float)((cz * motionCopy.m_transform.m_rot[2].x + cy * motionCopy.m_transform.m_rot[1].x) + cx * motionCopy.m_transform.m_rot[0].x);
		float yr = (float)((cz * motionCopy.m_transform.m_rot[2].y + cy * motionCopy.m_transform.m_rot[1].y) + cx * motionCopy.m_transform.m_rot[0].y);
		hkX87Real zr = (cz * motionCopy.m_transform.m_rot[2].z + cy * motionCopy.m_transform.m_rot[1].z) + cx * motionCopy.m_transform.m_rot[0].z;

		motionCopy.m_transform.m_trans.x = xr + motionA->m_transform.m_trans.x;
		motionCopy.m_transform.m_trans.y = yr + motionA->m_transform.m_trans.y;
		motionCopy.m_transform.m_trans.z = (float)(zr + motionA->m_transform.m_trans.z);
		memcpy(&motionCopy.m_transform.m_trans.w, &motionA->m_transform.m_trans.w, sizeof(float));       // raw dword copy
		motionCopy.m_sweptTransform.m_centerOfMass0.x = xr + motionA->m_sweptTransform.m_centerOfMass0.x;
		motionCopy.m_sweptTransform.m_centerOfMass0.y = yr + motionA->m_sweptTransform.m_centerOfMass0.y;
		motionCopy.m_sweptTransform.m_centerOfMass0.z = (float)(zr + motionA->m_sweptTransform.m_centerOfMass0.z);
		memcpy(&motionCopy.m_sweptTransform.m_centerOfMass0.w, &motionA->m_sweptTransform.m_centerOfMass0.w, sizeof(float));
		motionCopy.m_sweptTransform.m_centerOfMass1.x = xr + motionA->m_sweptTransform.m_centerOfMass1.x;
		motionCopy.m_sweptTransform.m_centerOfMass1.y = yr + motionA->m_sweptTransform.m_centerOfMass1.y;
		motionCopy.m_sweptTransform.m_centerOfMass1.z = (float)(zr + motionA->m_sweptTransform.m_centerOfMass1.z);
		memcpy(&motionCopy.m_sweptTransform.m_centerOfMass1.w, &motionA->m_sweptTransform.m_centerOfMass1.w, sizeof(float));

		sphere.m_radius = spheres[i].w;
		sphereBody.m_shape = &sphere;
		hkShapeCollectionKeyAgentPair* entry = &m_agents.m_data[m_agents.m_size];
		m_agents.m_size = m_agents.m_size + 1;
		sphereBody.m_shapeKey = (unsigned int)i;
		hkCollisionAgent* agent = hkCreateAgent(input, sphereBody, bodyB, mgr);
		entry->m_agent = agent;
		entry->m_key = (unsigned int)i;
	}
}

// @ 0x010e68d0
hkCollisionAgent* hkMultiSphereAgent::createListAAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr)
{
	return new hkMultiSphereAgent(a, b, input, mgr);
}

// @ 0x010e6a30
hkCollisionAgent* hkMultiSphereAgent::createListBAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr)
{
	return new hkSymmetricAgent<hkMultiSphereAgent>(b, a, input, mgr);
}

// hkSymmetricAgent<hkMultiSphereAgent> (vtable 0x014A4E88); the template bodies are in hk31_agents.h
// @ 0x010e67d0 getPenetrations
template void hkSymmetricAgent<hkMultiSphereAgent>::getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
// @ 0x010e6810 getClosestPoints
template void hkSymmetricAgent<hkMultiSphereAgent>::getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
// @ 0x010e6850 processCollision
template void hkSymmetricAgent<hkMultiSphereAgent>::processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);
// @ 0x010e6910 linearCast
template void hkSymmetricAgent<hkMultiSphereAgent>::linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);

// ---------------------------------------------------------------------------------------------------------
// hkBvAgent
// ---------------------------------------------------------------------------------------------------------
// @ 0x010e6c00
hkBvAgent::hkBvAgent(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkContactMgr* mgr)
	: hkCollisionAgent(mgr)
{
	const hkBvShapeView* bvShape = (const hkBvShapeView*)bodyA.m_shape;
	hkCdBody bvBody;
	bvBody.m_parent = &bodyA;
	bvBody.m_motion = bodyA.m_motion;
	bvBody.m_shapeKey = bodyA.m_shapeKey;
	bvBody.m_shape = bvShape->m_boundingVolumeShape;
	m_boundingVolumeAgent = hkCreateAgent(input, bvBody, bodyB, mgr);
	m_childAgent = 0;
}

// @ 0x010e6cb0
hkCollisionAgent* hkBvAgent::createBvShapeAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr)
{
	return new hkBvAgent(a, b, input, mgr);
}

// @ 0x010e6b00
void hkBvAgent::cleanup()
{
	m_boundingVolumeAgent->cleanup();
	if (m_childAgent)
	{
		m_childAgent->cleanup();
		m_childAgent = 0;
	}
	delete this;
}

// @ 0x010e6b30
void hkBvAgent::invalidateTim(hkCollisionInput& input)
{
	m_boundingVolumeAgent->invalidateTim(input);
	if (m_childAgent)
		m_childAgent->invalidateTim(input);
}

// @ 0x010e6b60
void hkBvAgent::warpTime(float oldTime, float newTime, hkCollisionInput& input)
{
	m_boundingVolumeAgent->warpTime(oldTime, newTime, input);
	if (m_childAgent)
		m_childAgent->warpTime(oldTime, newTime, input);
}

// @ 0x010e6ba0
void hkBvAgent::removePoint(unsigned short contactPointId)
{
	if (m_childAgent)
		m_childAgent->removePoint(contactPointId);
}

// @ 0x010e6bc0
void hkBvAgent::commitPotential(unsigned short contactPointId)
{
	if (m_childAgent)
		m_childAgent->commitPotential(contactPointId);
}

// @ 0x010e6be0
void hkBvAgent::createZombie(unsigned short contactPointId)
{
	if (m_childAgent)
		m_childAgent->createZombie(contactPointId);
}

// @ 0x010e6cf0
void hkBvAgent::updateShapeCollectionFilter(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input)
{
	const hkBvShapeView* bvShape = (const hkBvShapeView*)bodyA.m_shape;
	hkCdBody body;
	body.m_parent = &bodyA;
	body.m_motion = bodyA.m_motion;
	body.m_shapeKey = bodyA.m_shapeKey;
	body.m_shape = bvShape->m_boundingVolumeShape;
	m_boundingVolumeAgent->updateShapeCollectionFilter(body, bodyB, input);
	if (m_childAgent)
	{
		body.m_shapeKey = bodyA.m_shapeKey;
		body.m_shape = bvShape->m_childShape;
		m_childAgent->updateShapeCollectionFilter(body, bodyB, input);
	}
}

// @ 0x010e6d90
void hkBvAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkProcessCollisionInput& input, hkProcessCollisionOutput& output)
{
	HK_TIMER_BEGIN_LIST("LthkBvAgent", "checkBvShape");
	const hkBvShapeView* bvShape = (const hkBvShapeView*)bodyA.m_shape;
	hkCdBody bvBody;
	bvBody.m_parent = &bodyA;
	bvBody.m_motion = bodyA.m_motion;
	bvBody.m_shapeKey = bodyA.m_shapeKey;
	bvBody.m_shape = bvShape->m_boundingVolumeShape;
	hkAnyCdBodyPairCollector collector;
	m_boundingVolumeAgent->getPenetrations(bvBody, bodyB, input, collector);
	if (collector.m_earlyOut)
	{
		HK_TIMER_SPLIT_LIST("Stchild");
		bvBody.m_shapeKey = bodyA.m_shapeKey;
		bvBody.m_shape = bvShape->m_childShape;
		if (m_childAgent == 0)
			m_childAgent = hkCreateAgent(input, bvBody, bodyB, m_contactMgr);
		m_childAgent->processCollision(bvBody, bodyB, input, output);
	}
	else if (m_childAgent)
	{
		m_childAgent->cleanup();
		m_childAgent = 0;
	}
	HK_TIMER_END_LIST();
}

// @ 0x010e6f90
void hkBvAgent::linearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input,
                           hkCdPointCollector& castCollector, hkCdPointCollector* startCollector)
{
	HK_TIMER_BEGIN_LIST("LthkBvAgent", "checkBvShape");
	const hkBvShapeView* bvShape = (const hkBvShapeView*)bodyA.m_shape;
	hkCdBody bvBody;
	bvBody.m_parent = &bodyA;
	bvBody.m_motion = bodyA.m_motion;
	bvBody.m_shapeKey = bodyA.m_shapeKey;
	bvBody.m_shape = bvShape->m_boundingVolumeShape;
	hkSimpleClosestContactCollector collector;
	m_boundingVolumeAgent->linearCast(bvBody, bodyB, input, collector, &collector);
	if (collector.m_hitPointSet)
	{
		HK_TIMER_SPLIT_LIST("Stchild");
		bvBody.m_shapeKey = bodyA.m_shapeKey;
		bvBody.m_shape = bvShape->m_childShape;
		if (m_childAgent == 0)
			m_childAgent = hkCreateAgent(input, bvBody, bodyB, m_contactMgr);
		m_childAgent->linearCast(bvBody, bodyB, input, castCollector, startCollector);
	}
	else if (m_childAgent)
	{
		m_childAgent->cleanup();
		m_childAgent = 0;
	}
	HK_TIMER_END_LIST();
}

// @ 0x010e71b0
void hkBvAgent::staticLinearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input,
                                 hkCdPointCollector& castCollector, hkCdPointCollector* startCollector)
{
	HK_TIMER_BEGIN_LIST("LthkBvAgent", "checkBvShape");
	const hkBvShapeView* bvShape = (const hkBvShapeView*)bodyA.m_shape;
	hkCdBody bvBody;
	bvBody.m_parent = &bodyA;
	bvBody.m_motion = bodyA.m_motion;
	bvBody.m_shapeKey = bodyA.m_shapeKey;
	bvBody.m_shape = bvShape->m_boundingVolumeShape;
	hkCollisionDispatcher* dispatcher = (hkCollisionDispatcher*)input.m_dispatcher;
	int typeA = bvBody.m_shape->getType();
	int typeB = bodyB.m_shape->getType();
	hkSimpleClosestContactCollector collector;
	dispatcher->m_agent2Func[dispatcher->m_agent2Types[typeA][typeB]].m_linearCastFunc(bvBody, bodyB, input, collector, &collector);
	if (collector.m_hitPointSet)
	{
		HK_TIMER_SPLIT_LIST("Stchild");
		bvBody.m_shape = bvShape->m_childShape;
		bvBody.m_shapeKey = bodyA.m_shapeKey;
		int childType = bvBody.m_shape->getType();
		dispatcher->m_agent2Func[dispatcher->m_agent2Types[childType][typeB]].m_linearCastFunc(bvBody, bodyB, input, castCollector, startCollector);
	}
	HK_TIMER_END_LIST();
}

// @ 0x010e7390
void hkBvAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector)
{
	HK_TIMER_BEGIN_LIST("LthkBvAgent", "checkBvShape");
	const hkBvShapeView* bvShape = (const hkBvShapeView*)bodyA.m_shape;
	hkCdBody bvBody;
	bvBody.m_parent = &bodyA;
	bvBody.m_motion = bodyA.m_motion;
	bvBody.m_shapeKey = bodyA.m_shapeKey;
	bvBody.m_shape = bvShape->m_boundingVolumeShape;
	hkAnyCdBodyPairCollector overlap;
	m_boundingVolumeAgent->getPenetrations(bvBody, bodyB, input, overlap);
	if (overlap.m_earlyOut)
	{
		HK_TIMER_SPLIT_LIST("Stchild");
		bvBody.m_shapeKey = bodyA.m_shapeKey;
		bvBody.m_shape = bvShape->m_childShape;
		if (m_childAgent == 0)
			m_childAgent = hkCreateAgent(input, bvBody, bodyB, m_contactMgr);
		m_childAgent->getClosestPoints(bvBody, bodyB, input, collector);
	}
	else if (m_childAgent)
	{
		m_childAgent->cleanup();
		m_childAgent = 0;
	}
	HK_TIMER_END_LIST();
}

// ---------------------------------------------------------------------------------------------------------
// 32-bit layout checks against the binary
// ---------------------------------------------------------------------------------------------------------
#if defined(_M_IX86)
#define HK_LAYOUT_CHECK(name, cond) typedef char hkLayoutCheck_##name[(cond) ? 1 : -1]
HK_LAYOUT_CHECK(multiSphereAgent, sizeof(hkMultiSphereAgent) == 0x38 && offsetof(hkMultiSphereAgent, m_agents) == 0xc);
HK_LAYOUT_CHECK(bvAgent, sizeof(hkBvAgent) == 0x14 && offsetof(hkBvAgent, m_childAgent) == 0x10);
HK_LAYOUT_CHECK(multiSphereShape, sizeof(hkMultiSphereShapeView) == 0x90 && sizeof(hkSphereShape) == 0x10);
HK_LAYOUT_CHECK(collector, offsetof(hkSimpleClosestContactCollector, m_contact) == 0x10 && sizeof(hkSimpleClosestContactCollector) == 0x30);
HK_LAYOUT_CHECK(output, offsetof(hkProcessCollisionOutput, m_toiTime) == 0x3034 && offsetof(hkProcessCollisionOutput, m_contactPoints) == 0x30);
#endif
// --- equivalence checker address annotations
    extern unsigned long g_hkMonitorStreamCurrentTls; // 0x016e42a4
    extern unsigned long g_hkMonitorStreamEndTls; // 0x016e42a8

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct hkSphereShape {
    hkSphereShape(float); // 0x010c3770
};
}
