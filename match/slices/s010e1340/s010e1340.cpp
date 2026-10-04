// Havok 3.1.0 slice s010e1340: hkShapeCollectionAgent factories and symmetric linear cast, hkBvTreeAgent (cleanup, time
// callbacks, shape-collection filter update, linear-cast aabb, statistics, constructor, factories, registration),
// hkMoppAgent (static linear cast, BV/BV factory) and the hkSymmetricAgent<hkMoppAgent> wrappers.
// Equivalent portable source (not byte-exact). Operation order of the x87 math is taken from the disassembly.
#include "hk31_agents.h"
#include <math.h>

struct hkThreadMemory { void deallocateChunk(void* p, int nbytes, int memClass); };      // 0x0107DB10
static inline hkThreadMemory* getThreadMemory() { return (hkThreadMemory*)hkTlsGet(g_hkThreadMemoryTls); }

// ---------------------------------------------------------------------------------------------------------
// hkShapeCollectionAgent
// ---------------------------------------------------------------------------------------------------------
// @ 0x010e1380  (scalar deleting destructor: the compiler-generated one for this class, which hkMultiSphereAgent shares)
hkShapeCollectionAgent::~hkShapeCollectionAgent()
{
	if (m_agents.m_capacityAndFlags >= 0)
		getThreadMemory()->deallocateChunk(m_agents.m_data, (m_agents.m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) << 3, HK_MEMORY_CLASS_ARRAY);
}

// @ 0x010e1340
hkCollisionAgent* hkShapeCollectionAgent::createListAAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr)
{
	return new hkShapeCollectionAgent(a, b, input, mgr);
}

// @ 0x010e14d0
hkCollisionAgent* hkShapeCollectionAgent::createListBAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr)
{
	return new hkSymmetricAgent<hkShapeCollectionAgent>(b, a, input, mgr);
}

// ---------------------------------------------------------------------------------------------------------
// hkSymmetricAgent<AGENT> (template bodies are in hk31_agents.h)
// ---------------------------------------------------------------------------------------------------------
// @ 0x010e13e0 (AGENT = hkShapeCollectionAgent) hkSymmetricAgent::linearCast
template void hkSymmetricAgent<hkShapeCollectionAgent>::linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
// @ 0x010e1ae0 (AGENT = hkMoppAgent) hkSymmetricAgent::linearCast
template void hkSymmetricAgent<hkMoppAgent>::linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
// @ 0x010e1aa0 (AGENT = hkMoppAgent) hkSymmetricAgent::getPenetrations
template void hkSymmetricAgent<hkMoppAgent>::getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);

// ---------------------------------------------------------------------------------------------------------
// hkBvTreeAgent
// ---------------------------------------------------------------------------------------------------------
// @ 0x010e1a50  (destructor body; 0x010e19f0 is the scalar deleting destructor generated from it)
hkBvTreeAgent::~hkBvTreeAgent()
{
	if (m_collisionPartners.m_capacityAndFlags >= 0)
		getThreadMemory()->deallocateChunk(m_collisionPartners.m_data, (m_collisionPartners.m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) * 12, HK_MEMORY_CLASS_ARRAY);
}

// @ 0x010e21a0
hkBvTreeAgent::hkBvTreeAgent(hkContactMgr* mgr)
	: hkCollisionAgent(mgr)
{
	m_collisionPartners.m_capacityAndFlags = (int)0x80000000;
	m_collisionPartners.m_data = 0;
	m_collisionPartners.m_size = 0;
	m_cachedAabb.m_max.x = hkRealMax();
	m_cachedAabb.m_max.y = hkRealMax();
	m_cachedAabb.m_max.z = hkRealMax();
	m_cachedAabb.m_max.w = hkRealMax();
	m_cachedAabb.m_min.x = hkRealMax();
	m_cachedAabb.m_min.y = hkRealMax();
	m_cachedAabb.m_min.z = hkRealMax();
	m_cachedAabb.m_min.w = hkRealMax();
}

// @ 0x010e21f0
hkCollisionAgent* hkBvTreeAgent::createShapeBvAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr)
{
	return new hkBvTreeAgent(mgr);
}

// @ 0x010e1d30
void hkBvTreeAgent::cleanup()
{
	hkBvAgentEntryInfo* entry = m_collisionPartners.m_data;
	hkBvAgentEntryInfo* end = entry + m_collisionPartners.m_size;
	for (; entry != end; ++entry)
	{
		if (entry->m_collisionAgent)
			entry->m_collisionAgent->cleanup();
	}
	delete this;
}

// @ 0x010e1d70
void hkBvTreeAgent::invalidateTim(hkCollisionInput& input)
{
	hkBvAgentEntryInfo* entry = m_collisionPartners.m_data;
	hkBvAgentEntryInfo* end = entry + m_collisionPartners.m_size;
	for (; entry != end; ++entry)
	{
		if (entry->m_collisionAgent)
			entry->m_collisionAgent->invalidateTim(input);
	}
}

// @ 0x010e1db0
void hkBvTreeAgent::warpTime(float oldTime, float newTime, hkCollisionInput& input)
{
	hkBvAgentEntryInfo* entry = m_collisionPartners.m_data;
	hkBvAgentEntryInfo* end = entry + m_collisionPartners.m_size;
	for (; entry != end; ++entry)
	{
		if (entry->m_collisionAgent)
			entry->m_collisionAgent->warpTime(oldTime, newTime, input);
	}
}

// @ 0x010e1e00
void hkBvTreeAgent::updateShapeCollectionFilter(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input)
{
	const hkShapeCollection* container = static_cast<const hkBvTreeShape*>(bodyB.m_shape)->m_shapeCollection;
	for (int i = 0; i < m_collisionPartners.m_size; ++i)
	{
		hkShapeBuffer shapeBuffer;
		unsigned int key = m_collisionPartners.m_data[i].m_key;
		const hkShape* childShape = container->getChildShape(key, &shapeBuffer);

		hkCdBody childBody;
		childBody.m_parent = &bodyB;
		childBody.m_motion = bodyB.m_motion;
		childBody.m_shapeKey = m_collisionPartners.m_data[i].m_key;
		childBody.m_shape = childShape;

		hkBool enabled = input.m_filter->isCollisionEnabled(input, bodyA, bodyB, *container, m_collisionPartners.m_data[i].m_key);
		hkCollisionAgent* nullAgent;
		if (enabled)
		{
			hkCollisionAgent* agent = m_collisionPartners.m_data[i].m_collisionAgent;
			nullAgent = hkNullAgent_getNullAgent();
			if (agent == nullAgent)
			{
				hkContactMgr* mgr = m_contactMgr;
				hkCollisionDispatcher* dispatcher = (hkCollisionDispatcher*)input.m_dispatcher;
				int typeA = bodyA.m_shape->getType();
				int typeB = childBody.m_shape->getType();
				const uint8_t (*table)[32] = input.m_createPredictiveAgents ? dispatcher->m_agent2TypesPred : dispatcher->m_agent2Types;
				hkCollisionAgent* created = dispatcher->m_agent2Func[table[typeA][typeB]].m_createFunc(bodyA, childBody, input, mgr);
				m_collisionPartners.m_data[i].m_collisionAgent = created;
			}
			else
			{
				agent->updateShapeCollectionFilter(bodyA, childBody, input);
			}
		}
		else
		{
			hkCollisionAgent* agent = m_collisionPartners.m_data[i].m_collisionAgent;
			nullAgent = hkNullAgent_getNullAgent();
			if (agent != nullAgent)
			{
				agent->cleanup();
				hkBvAgentEntryInfo* entry = &m_collisionPartners.m_data[i];
				entry->m_collisionAgent = hkNullAgent_getNullAgent();
			}
		}
	}
}

// @ 0x010e1f90
// Extends the aabb of body A (in B's local space) by the linear cast path: the negative path components extend the
// minimum and the positive ones the maximum.
void hkBvTreeAgent::calcAabbLinearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input, hkAabb& aabbOut)
{
	hkTransform bTa;
	bTa.setMulInverseMul(*(const hkTransform*)bodyB.m_motion, *(const hkTransform*)bodyA.m_motion);
	bodyA.m_shape->getAabb(bTa, input.m_tolerance, aabbOut);

	hkVector4 pathB;
	pathB.setRotatedInverseDir(*(const hkRotation*)bodyB.m_motion, input.m_path);

	// min4(0, pathB): "0 < p ? 0 : p"; max4(0, pathB): "0 > p ? 0 : p"
	float minX = (0.0f < pathB.x) ? 0.0f : pathB.x;
	float minY = (0.0f < pathB.y) ? 0.0f : pathB.y;
	float minZ = (0.0f < pathB.z) ? 0.0f : pathB.z;
	float minW = (0.0f < pathB.w) ? 0.0f : pathB.w;
	float maxX = (0.0f > pathB.x) ? 0.0f : pathB.x;
	float maxY = (0.0f > pathB.y) ? 0.0f : pathB.y;
	float maxZ = (0.0f > pathB.z) ? 0.0f : pathB.z;
	float maxW = (0.0f > pathB.w) ? 0.0f : pathB.w;

	aabbOut.m_min.x = minX + aabbOut.m_min.x;
	aabbOut.m_min.y = minY + aabbOut.m_min.y;
	aabbOut.m_min.z = minZ + aabbOut.m_min.z;
	aabbOut.m_min.w = minW + aabbOut.m_min.w;
	aabbOut.m_max.x = maxX + aabbOut.m_max.x;
	aabbOut.m_max.y = maxY + aabbOut.m_max.y;
	aabbOut.m_max.z = maxZ + aabbOut.m_max.z;
	aabbOut.m_max.w = maxW + aabbOut.m_max.w;
}

// @ 0x010e2110
void hkBvTreeAgent::calcStatistics(hkStatisticsCollector* c) const
{
	c->beginObject("BvTreeAgt", 8, this);
	if (m_collisionPartners.m_capacityAndFlags >= 0)
	{
		c->addArray("AgentPtrs", 8, m_collisionPartners.m_data, m_collisionPartners.m_size * 12,
		            (m_collisionPartners.m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) * 12);
	}
	const hkBvAgentEntryInfo* entry = m_collisionPartners.m_data;
	const hkBvAgentEntryInfo* end = entry + m_collisionPartners.m_size;
	for (; entry != end; ++entry)
	{
		if (entry->m_collisionAgent)
			c->addReferencedObject("Agent", 8, entry->m_collisionAgent);
	}
	// (the binary has no endObject call here)
}

// ---------------------------------------------------------------------------------------------------------
// hkMoppAgent
// ---------------------------------------------------------------------------------------------------------
// @ 0x010e1c00
hkCollisionAgent* hkMoppAgent::createBvBvAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr)
{
	const hkMoppBvTreeShape* shapeA = static_cast<const hkMoppBvTreeShape*>(a.m_shape);
	const hkMoppBvTreeShape* shapeB = static_cast<const hkMoppBvTreeShape*>(b.m_shape);
	if (shapeA->m_code->m_data.m_size < shapeB->m_code->m_data.m_size)
		return new hkMoppAgent(mgr);
	return new hkSymmetricAgent<hkMoppAgent>(mgr);
}

// @ 0x010e17e0
void hkMoppAgent::staticLinearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input,
                                   hkCdPointCollector& castCollector, hkCdPointCollector* startCollector)
{
	HK_TIMER_BEGIN("TtMopp");

	hkTransform bTa;
	bTa.setMulInverseMul(*(const hkTransform*)bodyB.m_motion, *(const hkTransform*)bodyA.m_motion);
	hkAabb aabb;
	bodyA.m_shape->getAabb(bTa, input.m_tolerance, aabb);
	hkVector4 pathB;
	pathB.setRotatedInverseDir(*(const hkRotation*)bodyB.m_motion, input.m_path);
	float tolerance = input.m_tolerance;

	hkMoppAabbCastInput cast;
	// X87-PRECISION: every (a + b) feeds fmul 0.5 on the stack before the store; the extent differences of x and y stay on
	// the stack, z and w are stored first.
	cast.m_from.x = (float)(((hkX87Real)aabb.m_min.x + aabb.m_max.x) * 0.5f);
	cast.m_input = &input;
	cast.m_bodyA = &bodyA;
	cast.m_bodyB = &bodyB;
	cast.m_from.y = (float)(((hkX87Real)aabb.m_max.y + aabb.m_min.y) * 0.5f);
	cast.m_from.z = (float)(((hkX87Real)aabb.m_max.z + aabb.m_min.z) * 0.5f);
	cast.m_from.w = (float)(((hkX87Real)aabb.m_max.w + aabb.m_min.w) * 0.5f);
	cast.m_to.x = pathB.x + cast.m_from.x;
	cast.m_to.y = pathB.y + cast.m_from.y;
	cast.m_to.z = pathB.z + cast.m_from.z;
	cast.m_to.w = pathB.w + cast.m_from.w;

	hkX87Real extentX = (hkX87Real)aabb.m_max.x - aabb.m_min.x;
	hkX87Real extentY = (hkX87Real)aabb.m_max.y - aabb.m_min.y;
	float extentZ = (float)((hkX87Real)aabb.m_max.z - aabb.m_min.z);
	float extentW = (float)((hkX87Real)aabb.m_max.w - aabb.m_min.w);
	float halfX = (float)(extentX * 0.5f);
	hkX87Real halfY = extentY * 0.5f;
	hkX87Real halfZ = (hkX87Real)extentZ * 0.5f;
	float halfW = (float)((hkX87Real)extentW * 0.5f);
	cast.m_extents.x = (float)((hkX87Real)halfX + tolerance);
	cast.m_extents.y = (float)(halfY + tolerance);
	cast.m_extents.z = (float)(halfZ + tolerance);
	cast.m_extents.w = (float)((hkX87Real)halfW + tolerance);

	hkMoppAabbCastVirtualMachine machine;
	machine.aabbCast(cast, castCollector, startCollector);
	HK_TIMER_END();
}

// ---------------------------------------------------------------------------------------------------------
// registration with the collision dispatcher
// ---------------------------------------------------------------------------------------------------------
// Shape type values as they appear in the binary: 0x18 is the BV tree type, -1 means "any shape", 1 the convex base type.
enum { HK_SHAPE_ANY = -1, HK_SHAPE_CONVEX_TYPE = 1, HK_SHAPE_BV_TREE_TYPE = 0x18 };

// Functions registered below that live in other slices.
void HK_CALL hkBvTreeAgent_flippedStaticGetPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);          // 0x010E15A0
void HK_CALL hkBvTreeAgent_flippedStaticGetClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);           // 0x010E15E0
void HK_CALL hkBvTreeAgent_flippedStaticLinearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);   // 0x010E1620
void HK_CALL hkBvTreeAgent_staticGetPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);                // 0x010E5130
void HK_CALL hkBvTreeAgent_staticGetClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);                  // 0x010E4D50
hkCollisionAgent* HK_CALL hkBvTreeStreamAgent_createBvTreeShapeAgent(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkContactMgr*);       // 0x010CEEA0
hkCollisionAgent* HK_CALL hkBvTreeStreamAgent_createShapeBvAgent(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkContactMgr*);          // 0x010CEB50

// @ 0x010e1c70
void hkBvTreeAgent::registerAgent(hkCollisionDispatcher* dispatcher)
{
	hkAgentFuncs funcs;
	funcs.m_createFunc = hkBvTreeAgent::createBvTreeShapeAgent;
	funcs.m_getPenetrationsFunc = hkBvTreeAgent_flippedStaticGetPenetrations;
	funcs.m_getClosestPointFunc = hkBvTreeAgent_flippedStaticGetClosestPoints;
	funcs.m_linearCastFunc = hkBvTreeAgent_flippedStaticLinearCast;
	funcs.m_isFlipped = hkBool(true);
	funcs.m_isPredictive = hkBool(false);
	dispatcher->registerCollisionAgent(funcs, HK_SHAPE_BV_TREE_TYPE, HK_SHAPE_ANY);

	funcs.m_createFunc = hkBvTreeAgent::createShapeBvAgent;
	funcs.m_getPenetrationsFunc = hkBvTreeAgent_staticGetPenetrations;
	funcs.m_getClosestPointFunc = hkBvTreeAgent_staticGetClosestPoints;
	funcs.m_linearCastFunc = hkMoppAgent::staticLinearCast;
	funcs.m_isFlipped = hkBool(false);
	funcs.m_isPredictive = hkBool(false);
	dispatcher->registerCollisionAgent(funcs, HK_SHAPE_ANY, HK_SHAPE_BV_TREE_TYPE);

	funcs.m_createFunc = hkMoppAgent::createBvBvAgent;
	funcs.m_getPenetrationsFunc = hkBvTreeAgent_staticGetPenetrations;
	funcs.m_getClosestPointFunc = hkBvTreeAgent_staticGetClosestPoints;
	funcs.m_linearCastFunc = hkMoppAgent::staticLinearCast;
	funcs.m_isFlipped = hkBool(false);
	funcs.m_isPredictive = hkBool(true);
	dispatcher->registerCollisionAgent(funcs, HK_SHAPE_BV_TREE_TYPE, HK_SHAPE_BV_TREE_TYPE);
}

// @ 0x010e1720  (the predictive-agent set: factories of the BV-tree stream agent, static functions of hkBvTreeAgent)
void hkBvTreeAgent::registerPredictiveAgent(hkCollisionDispatcher* dispatcher)
{
	hkAgentFuncs funcs;
	funcs.m_createFunc = hkBvTreeStreamAgent_createBvTreeShapeAgent;
	funcs.m_getPenetrationsFunc = hkBvTreeAgent_flippedStaticGetPenetrations;
	funcs.m_getClosestPointFunc = hkBvTreeAgent_flippedStaticGetClosestPoints;
	funcs.m_linearCastFunc = hkBvTreeAgent_flippedStaticLinearCast;
	funcs.m_isFlipped = hkBool(true);
	funcs.m_isPredictive = hkBool(true);
	dispatcher->registerCollisionAgent(funcs, HK_SHAPE_BV_TREE_TYPE, HK_SHAPE_CONVEX_TYPE);

	funcs.m_createFunc = hkBvTreeStreamAgent_createShapeBvAgent;
	funcs.m_getPenetrationsFunc = hkBvTreeAgent_staticGetPenetrations;
	funcs.m_getClosestPointFunc = hkBvTreeAgent_staticGetClosestPoints;
	funcs.m_linearCastFunc = hkMoppAgent::staticLinearCast;
	funcs.m_isFlipped = hkBool(false);
	funcs.m_isPredictive = hkBool(true);
	dispatcher->registerCollisionAgent(funcs, HK_SHAPE_CONVEX_TYPE, HK_SHAPE_BV_TREE_TYPE);

	funcs.m_createFunc = hkMoppAgent::createBvBvAgent;
	funcs.m_getPenetrationsFunc = hkBvTreeAgent_staticGetPenetrations;
	funcs.m_getClosestPointFunc = hkBvTreeAgent_staticGetClosestPoints;
	funcs.m_linearCastFunc = hkMoppAgent::staticLinearCast;
	funcs.m_isFlipped = hkBool(false);
	funcs.m_isPredictive = hkBool(true);
	dispatcher->registerCollisionAgent(funcs, HK_SHAPE_BV_TREE_TYPE, HK_SHAPE_BV_TREE_TYPE);
}

// ---------------------------------------------------------------------------------------------------------
// 32-bit layout checks against the binary
// ---------------------------------------------------------------------------------------------------------
#if defined(_M_IX86)
#define HK_LAYOUT_CHECK(name, cond) typedef char hkLayoutCheck_##name[(cond) ? 1 : -1]
HK_LAYOUT_CHECK(shapeCollAgent, sizeof(hkShapeCollectionAgent) == 0x38 && offsetof(hkShapeCollectionAgent, m_agents) == 0xc);
HK_LAYOUT_CHECK(bvTreeAgent, sizeof(hkBvTreeAgent) == 0x40 && offsetof(hkBvTreeAgent, m_collisionPartners) == 0xc && offsetof(hkBvTreeAgent, m_cachedAabb) == 0x20);
HK_LAYOUT_CHECK(entry, sizeof(hkBvAgentEntryInfo) == 12 && sizeof(hkShapeCollectionKeyAgentPair) == 8);
HK_LAYOUT_CHECK(flipCollector, sizeof(hkSymmetricAgentFlipCastCollector) == 0x30 && offsetof(hkSymmetricAgentFlipCastCollector, m_original) == 0x20);
HK_LAYOUT_CHECK(castInput, sizeof(hkLinearCastCollisionInput) == 0x30 && sizeof(hkMoppAabbCastInput) == 0x40);
HK_LAYOUT_CHECK(funcs, sizeof(hkAgentFuncs) == 0x14 && offsetof(hkCollisionDispatcher, m_agent2Func) == 0x990);
#endif
