// Havok 3.1.0 slice s010e4840: the hkBvTreeAgent traversal entry points (the three virtual ones and the two
// static key-gathering ones), the two BV-tree factories, the hkShapeCollectionAgent cleanup loop, the BV-tree
// dispatcher registration and the hkSymmetricAgent<hkMoppAgent> wrappers that go with them.
// Toolchain: Visual C++ .NET 2003 (cl 13.10.3052, /vc71) -- the retail binary is VC7.1 (/O2 /MD /Gy /EHsc).
// Member names follow the Havok 6.x headers (hkpBvTreeAgent etc.); all layouts come from the 32-bit binary.
#include "hk31_agents.h"

// ---------------------------------------------------------------------------------------------------------
// Layout checks against the 32-bit binary
// ---------------------------------------------------------------------------------------------------------
#define HK_LAYOUT_CHECK(name, cond) typedef char hkLayoutCheck_##name[(cond) ? 1 : -1]
HK_LAYOUT_CHECK(bvTreeAgent, sizeof(hkBvTreeAgent) == 0x40 && offsetof(hkBvTreeAgent, m_collisionPartners) == 0xc &&
                             offsetof(hkBvTreeAgent, m_cachedAabb) == 0x20);
HK_LAYOUT_CHECK(entryInfo, sizeof(hkBvAgentEntryInfo) == 12);
HK_LAYOUT_CHECK(agentFuncs, sizeof(hkAgentFuncs) == 0x14 && offsetof(hkAgentFuncs, m_isFlipped) == 0x10 &&
                            offsetof(hkAgentFuncs, m_isPredictive) == 0x11);
HK_LAYOUT_CHECK(flipCollector, sizeof(hkFlipCollectorFixed) == 0xc && offsetof(hkFlipCollectorFixed, m_original) == 8);
HK_LAYOUT_CHECK(shapeBuffer, sizeof(hkShapeBuffer) == 0x200);

// ---------------------------------------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------------------------------------
class hkThreadMemory { public: void deallocateChunk(void* p, int nbytes, int memClass); };      // 0x0107DB10
static inline hkThreadMemory* getThreadMemory() { return (hkThreadMemory*)hkTlsGet(g_hkThreadMemoryTls); }

// The dispatcher registrations below each build an hkAgentFuncs on the stack. The binary reserves a
// 0x18-byte frame for them even though hkAgentFuncs is only 0x14 bytes (the same 0x18 frame shows up in
// hkBvTreeAgent::registerAgent and in the other dispatcher registrations), so the local is modelled with
// the extra word the compiler keeps.
struct hkAgentFuncsLocal { hkAgentFuncs m_funcs; unsigned int m_reserved; };

// The BV-tree traversal entry points open the monitor stream with *two* commands: "LtBvTree" at +0 and
// "QueryTree" at +0xc, after which the write pointer moves to +0x10. The shared 12-byte HK_TIMER_COMMAND
// macro cannot express that, so the two-command form is spelled out here.
#define HK_TIMER_BEGIN_2CMD() do { \
	void* hkEnd_ = hkTlsGet(g_hkMonitorStreamEndTls); \
	if (hkTlsGet(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
		hkMonitorCommand* c_ = (hkMonitorCommand*)hkTlsGet(g_hkMonitorStreamCurrentTls); \
		c_[0].m_commandAndMonitor = "LtBvTree"; \
		c_[1].m_commandAndMonitor = "QueryTree"; \
		c_[0].m_time0 = HK_RDTSC32(); \
		hkTlsSet(g_hkMonitorStreamCurrentTls, (char*)c_ + 0x10); } } while (0)

// Shape types the registration below uses (see hkShapeType in the binary).
enum { HK_SHAPE_ALL_TYPE = -1, HK_SHAPE_BV_TREE_TYPE = 3 };

// ---------------------------------------------------------------------------------------------------------
// Agent entry points registered here but owned by other slices (flipped / other-class variants).
// ---------------------------------------------------------------------------------------------------------
void HK_CALL hkBvTreeAgent_flippedStaticGetPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&,
                                                        hkCdBodyPairCollector&);                     // 0x010E15A0
void HK_CALL hkBvTreeAgent_flippedStaticGetClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&,
                                                         hkCdPointCollector&);                       // 0x010E15E0
void HK_CALL hkShapeCollectionAgent_flippedStaticLinearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&,
                                                            hkCdPointCollector&, hkCdPointCollector*);   // 0x010CDB20

// =========================================================================================================
// hkBvTreeAgent traversal
// =========================================================================================================
// Every traversal walks the collision partners prepared for the BV-tree shape of bodyB. Each partner's child
// shape is fetched into a scratch buffer and wrapped into a child hkCdBody that keeps bodyB's motion state and
// points back at bodyB as its parent.

// @ 0x010e4840
void hkBvTreeAgent::linearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input,
                               hkCdPointCollector& castCollector, hkCdPointCollector* startCollector)
{
	HK_TIMER_BEGIN_2CMD();
	prepareCollisionPartnersLinearCast(bodyA, bodyB, input);
	HK_TIMER_COMMAND("StNarrowPhase");

	const hkShapeCollection* container = static_cast<const hkBvTreeShape*>(bodyB.m_shape)->m_shapeCollection;
	hkShapeBuffer shapeBuffer;

	hkBvAgentEntryInfo* entry = m_collisionPartners.m_data;
	hkBvAgentEntryInfo* entryEnd = entry + m_collisionPartners.m_size;
	while (entry != entryEnd)
	{
		hkCdBody childBody;
		childBody.m_motion = bodyB.m_motion;
		childBody.m_parent = &bodyB;
		childBody.m_shape = container->getChildShape(entry->m_key, &shapeBuffer);
		childBody.m_shapeKey = entry->m_key;
		entry->m_collisionAgent->linearCast(bodyA, childBody, input, castCollector, startCollector);
		++entry;
	}
	HK_TIMER_END();
}

// @ 0x010e4be0
void hkBvTreeAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input,
                                     hkCdPointCollector& collector)
{
	HK_TIMER_BEGIN_2CMD();
	prepareCollisionPartners(bodyA, bodyB, input);
	HK_TIMER_COMMAND("StNarrowPhase");

	const hkShapeCollection* container = static_cast<const hkBvTreeShape*>(bodyB.m_shape)->m_shapeCollection;
	hkShapeBuffer shapeBuffer;

	hkBvAgentEntryInfo* entry = m_collisionPartners.m_data;
	hkBvAgentEntryInfo* entryEnd = entry + m_collisionPartners.m_size;
	while (entry != entryEnd)
	{
		hkCdBody childBody;
		childBody.m_motion = bodyB.m_motion;
		childBody.m_parent = &bodyB;
		childBody.m_shape = container->getChildShape(entry->m_key, &shapeBuffer);
		childBody.m_shapeKey = entry->m_key;
		entry->m_collisionAgent->getClosestPoints(bodyA, childBody, input, collector);
		++entry;
	}
	HK_TIMER_END();
}

// @ 0x010e4fb0
void hkBvTreeAgent::getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input,
                                    hkCdBodyPairCollector& collector)
{
	HK_TIMER_BEGIN_2CMD();
	prepareCollisionPartners(bodyA, bodyB, input);
	HK_TIMER_COMMAND("StNarrowPhase");

	const hkShapeCollection* container = static_cast<const hkBvTreeShape*>(bodyB.m_shape)->m_shapeCollection;
	hkShapeBuffer shapeBuffer;

	hkBvAgentEntryInfo* entry = m_collisionPartners.m_data;
	hkBvAgentEntryInfo* entryEnd = entry + m_collisionPartners.m_size;
	while (entry != entryEnd)
	{
		hkCdBody childBody;
		childBody.m_motion = bodyB.m_motion;
		childBody.m_parent = &bodyB;
		childBody.m_shape = container->getChildShape(entry->m_key, &shapeBuffer);
		childBody.m_shapeKey = entry->m_key;
		entry->m_collisionAgent->getPenetrations(bodyA, childBody, input, collector);
		if (collector.m_earlyOut)
			break;
		++entry;
	}
	HK_TIMER_END();
}

// The static entry points are the ones the dispatcher calls for (shape, BV tree) pairs: they gather the child
// keys of the BV tree that overlap the query volume and then hand each child to the agent the dispatcher has
// registered for (bodyA shape type, child shape type).

// @ 0x010e49c0
void hkBvTreeAgent::staticLinearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input,
                                     hkCdPointCollector& castCollector, hkCdPointCollector* startCollector)
{
	HK_TIMER_BEGIN_2CMD();

	hkAabb aabb;
	calcAabbLinearCast(bodyA, bodyB, input, aabb);

	hkInplaceArray<unsigned int, 128> keys;
	keys.m_data = keys.m_storage;
	keys.m_size = 0;
	keys.m_capacityAndFlags = (int)0x80000080;

	// the static entry points are handed the BV tree body itself, whose shape is the collection the keys are
	// gathered from (the virtual entry points below navigate through hkBvTreeShape::m_shapeCollection instead)
	hkShapeCollection* container = static_cast<hkShapeCollection*>(const_cast<hkShape*>(bodyB.m_shape));
	container->shapeCollectionSlot9(aabb, keys);

	HK_TIMER_COMMAND("StNarrowPhase");

	const int typeA = bodyA.m_shape->getType();
	hkCollisionDispatcher* dispatcher = static_cast<hkCollisionDispatcher*>(input.m_dispatcher);
	hkShapeBuffer shapeBuffer;

	const unsigned int* key = keys.m_data;
	const unsigned int* keyEnd = keys.m_data + keys.m_size;
	while (key != keyEnd)
	{
		if (input.m_filter->isCollisionEnabled(input, bodyA, bodyB, *container, *key))
		{
			hkCdBody childBody;
			childBody.m_motion = bodyB.m_motion;
			childBody.m_parent = &bodyB;
			childBody.m_shape = container->getChildShape(*key, &shapeBuffer);
			childBody.m_shapeKey = *key;
			const int typeB = childBody.m_shape->getType();
			dispatcher->m_agent2Func[dispatcher->m_agent2Types[typeA][typeB]].m_linearCastFunc(bodyA, childBody, input,
			                                                                                  castCollector, startCollector);
		}
		++key;
	}
	HK_TIMER_END();

	if (keys.m_capacityAndFlags >= 0)
		getThreadMemory()->deallocateChunk(keys.m_data, keys.getCapacity() * 4, HK_MEMORY_CLASS_ARRAY);
}

// @ 0x010e4d50
void hkBvTreeAgent::staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input,
                                           hkCdPointCollector& collector)
{
	HK_TIMER_BEGIN_2CMD();

	// the query volume is bodyA's aabb, grown by the tolerance, expressed in bodyB's space
	hkTransform bodyBToA;
	bodyBToA.setMulInverseMul(*(const hkTransform*)bodyB.m_motion, *(const hkTransform*)bodyA.m_motion);
	hkAabb aabb;
	bodyA.m_shape->getAabb(bodyBToA, input.m_tolerance, aabb);

	hkInplaceArray<unsigned int, 128> keys;
	keys.m_data = keys.m_storage;
	keys.m_size = 0;
	keys.m_capacityAndFlags = (int)0x80000080;

	// the static entry points are handed the BV tree body itself, whose shape is the collection the keys are
	// gathered from (the virtual entry points below navigate through hkBvTreeShape::m_shapeCollection instead)
	hkShapeCollection* container = static_cast<hkShapeCollection*>(const_cast<hkShape*>(bodyB.m_shape));
	container->shapeCollectionSlot9(aabb, keys);

	HK_TIMER_COMMAND("StNarrowPhase");

	const int typeA = bodyA.m_shape->getType();
	hkCollisionDispatcher* dispatcher = static_cast<hkCollisionDispatcher*>(input.m_dispatcher);
	hkShapeBuffer shapeBuffer;

	const unsigned int* key = keys.m_data;
	const unsigned int* keyEnd = keys.m_data + keys.m_size;
	while (key != keyEnd)
	{
		if (input.m_filter->isCollisionEnabled(input, bodyA, bodyB, *container, *key))
		{
			hkCdBody childBody;
			childBody.m_motion = bodyB.m_motion;
			childBody.m_parent = &bodyB;
			childBody.m_shape = container->getChildShape(*key, &shapeBuffer);
			childBody.m_shapeKey = *key;
			const int typeB = childBody.m_shape->getType();
			dispatcher->m_agent2Func[dispatcher->m_agent2Types[typeA][typeB]].m_getClosestPointFunc(bodyA, childBody,
			                                                                                        input, collector);
		}
		++key;
	}
	HK_TIMER_END();

	if (keys.m_capacityAndFlags >= 0)
		getThreadMemory()->deallocateChunk(keys.m_data, keys.getCapacity() * 4, HK_MEMORY_CLASS_ARRAY);
}

// @ 0x010e5130
void hkBvTreeAgent::staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input,
                                          hkCdBodyPairCollector& collector)
{
	HK_TIMER_BEGIN_2CMD();

	hkTransform bodyBToA;
	bodyBToA.setMulInverseMul(*(const hkTransform*)bodyB.m_motion, *(const hkTransform*)bodyA.m_motion);
	hkAabb aabb;
	bodyA.m_shape->getAabb(bodyBToA, input.m_tolerance, aabb);

	hkInplaceArray<unsigned int, 128> keys;
	keys.m_data = keys.m_storage;
	keys.m_size = 0;
	keys.m_capacityAndFlags = (int)0x80000080;

	// the static entry points are handed the BV tree body itself, whose shape is the collection the keys are
	// gathered from (the virtual entry points below navigate through hkBvTreeShape::m_shapeCollection instead)
	hkShapeCollection* container = static_cast<hkShapeCollection*>(const_cast<hkShape*>(bodyB.m_shape));
	container->shapeCollectionSlot9(aabb, keys);

	HK_TIMER_COMMAND("StNarrowPhase");

	const int typeA = bodyA.m_shape->getType();
	hkCollisionDispatcher* dispatcher = static_cast<hkCollisionDispatcher*>(input.m_dispatcher);
	hkShapeBuffer shapeBuffer;

	const unsigned int* key = keys.m_data;
	const unsigned int* keyEnd = keys.m_data + keys.m_size;
	while (key != keyEnd)
	{
		if (input.m_filter->isCollisionEnabled(input, bodyA, bodyB, *container, *key))
		{
			hkCdBody childBody;
			childBody.m_motion = bodyB.m_motion;
			childBody.m_parent = &bodyB;
			childBody.m_shape = container->getChildShape(*key, &shapeBuffer);
			childBody.m_shapeKey = *key;
			const int typeB = childBody.m_shape->getType();
			dispatcher->m_agent2Func[dispatcher->m_agent2Types[typeA][typeB]].m_getPenetrationsFunc(bodyA, childBody,
			                                                                                        input, collector);
			if (collector.m_earlyOut)
				break;
		}
		++key;
	}
	HK_TIMER_END();

	if (keys.m_capacityAndFlags >= 0)
		getThreadMemory()->deallocateChunk(keys.m_data, keys.getCapacity() * 4, HK_MEMORY_CLASS_ARRAY);
}

// =========================================================================================================
// hkSymmetricAgent<hkMoppAgent> wrappers (vtable 0x014A4E0C slots 3 and 5)
// =========================================================================================================
// @ 0x010e5390
template void hkSymmetricAgent<hkMoppAgent>::getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&,
                                                              hkCdPointCollector&);

// @ 0x010e53d0
template void hkSymmetricAgent<hkMoppAgent>::processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&,
                                                              hkProcessCollisionOutput&);

// =========================================================================================================
// Factories
// =========================================================================================================
// @ 0x010e5450
hkCollisionAgent* hkBvTreeAgent::createBvTreeShapeAgent(const hkCdBody&, const hkCdBody&, const hkCollisionInput&,
                                                        hkContactMgr* mgr)
{
	// the binary builds the hkSymmetricAgent<hkMoppAgent> here with its constructor inlined: the vtable
	// (0x014A4E0C) and every member are written straight into the freshly allocated chunk, the vtable last.
	return new hkSymmetricAgent<hkMoppAgent>(mgr);
}

// @ 0x010e54b0
hkCollisionAgent* hkBvTreeAgent::createBvBvAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput&,
                                                 hkContactMgr* mgr)
{
	// the smaller body is the one whose BV tree is walked, so a plain BV/BV agent only works when bodyB is not
	// the larger one; otherwise the bodies are run through the symmetric wrapper.
	const hkMotionState* motionA = (const hkMotionState*)a.m_motion;
	const hkMotionState* motionB = (const hkMotionState*)b.m_motion;
	if (motionA->m_objectRadius < motionB->m_objectRadius)
		return new hkBvTreeAgent(mgr);
	return new hkSymmetricAgent<hkMoppAgent>(mgr);
}

// =========================================================================================================
// Dispatcher registration
// =========================================================================================================
// The dispatcher init calls this next to hkBvTreeAgent::registerAgent (0x010E1C70), which registers the MOPP
// variants of the same factories. The name is descriptive; the binary has no symbol for 0x010E5540.
// @ 0x010e5540
void hkBvTreeAgent_registerBvTreeAgents(hkCollisionDispatcher* dispatcher)
{
	// (BV tree, anything): the BV tree is bodyB, so the symmetric wrapper flips the bodies around the
	// ordinary hkBvTreeAgent entry points. Predictive agents are allowed because the tree query is exact.
	{
		hkAgentFuncsLocal local;
		hkAgentFuncs& funcs = local.m_funcs;
		funcs.m_createFunc = hkBvTreeAgent::createBvTreeShapeAgent;
		funcs.m_getPenetrationsFunc = hkBvTreeAgent_flippedStaticGetPenetrations;
		funcs.m_getClosestPointFunc = hkBvTreeAgent_flippedStaticGetClosestPoints;
		funcs.m_linearCastFunc = hkShapeCollectionAgent_flippedStaticLinearCast;
		funcs.m_isFlipped = hkBool(true);
		funcs.m_isPredictive = hkBool(true);
		dispatcher->registerCollisionAgent(funcs, HK_SHAPE_BV_TREE_TYPE, HK_SHAPE_ALL_TYPE);
	}

	// (anything, BV tree): bodyB is the BV tree, walk it directly.
	{
		hkAgentFuncsLocal local;
		hkAgentFuncs& funcs = local.m_funcs;
		funcs.m_createFunc = hkBvTreeAgent::createShapeBvAgent;
		funcs.m_getPenetrationsFunc = hkBvTreeAgent::staticGetPenetrations;
		funcs.m_getClosestPointFunc = hkBvTreeAgent::staticGetClosestPoints;
		funcs.m_linearCastFunc = hkBvTreeAgent::staticLinearCast;
		funcs.m_isFlipped = hkBool(false);
		funcs.m_isPredictive = hkBool(true);
		dispatcher->registerCollisionAgent(funcs, HK_SHAPE_ALL_TYPE, HK_SHAPE_BV_TREE_TYPE);
	}

	// (BV tree, BV tree): both are trees, so only the BV/BV factory has to pick which one to walk.
	{
		hkAgentFuncsLocal local;
		hkAgentFuncs& funcs = local.m_funcs;
		funcs.m_createFunc = hkBvTreeAgent::createBvBvAgent;
		funcs.m_getPenetrationsFunc = hkBvTreeAgent::staticGetPenetrations;
		funcs.m_getClosestPointFunc = hkBvTreeAgent::staticGetClosestPoints;
		funcs.m_linearCastFunc = hkBvTreeAgent::staticLinearCast;
		funcs.m_isFlipped = hkBool(false);
		funcs.m_isPredictive = hkBool(true);
		dispatcher->registerCollisionAgent(funcs, HK_SHAPE_BV_TREE_TYPE, HK_SHAPE_BV_TREE_TYPE);
	}
}

// =========================================================================================================
// hkShapeCollectionAgent
// =========================================================================================================
// @ 0x010e5600
void hkShapeCollectionAgent::cleanup()
{
	for (int i = 0; i < m_agents.m_size; ++i)
		m_agents.m_data[i].m_agent->cleanup();
	delete this;
}
