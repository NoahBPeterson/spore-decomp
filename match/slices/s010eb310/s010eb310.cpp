// Havok 3.1.0 collision, part: hkTriangleUtil::isNonDegenerate, hkConvexPieceShape, the hkAgent3Bridge agent3
// function table, hkSymmetricAgentFlip*Collector and hkIterativeLinearCastAgent::staticLinearCast
// (0x010EB310..0x010EC09F). Equivalent portable source; x87 semantics are noted per function.
#include "hk31_math.h"

// ---- external declarations --------------------------------------------------------------------------------
// The agent object a bridge entry points at. Slots from the binary (0x14..0x30 = 5..12).
struct hkCollisionAgent : hkReferencedObject
{
	hkContactMgr* m_contactMgr;   // +8
	virtual void s2(); virtual void s3(); virtual void s4();
	virtual void processCollision(const hkCdBody& a, const hkCdBody& b, const hkProcessCollisionInput& input, hkProcessCollisionOutput& out);   // 5
	virtual void cleanup();                                                                                    // 6
	virtual void updateShapeCollectionFilter(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input);   // 7
	virtual void invalidateTim(hkCollisionInput& input);                                                       // 8
	virtual void warpTime(hkTime oldTime, hkTime newTime, hkCollisionInput& input);                            // 9
	virtual void removePoint(hkContactPointId id);                                                             // 10
	virtual void commitPotential(hkContactPointId id);                                                         // 11
	virtual void createZombie(hkContactPointId id);                                                            // 12
};

struct hkSimpleClosestContactCollector : hkCdPointCollector   // vtable 0x014A4AC4, addCdPoint 0x010EDDD0
{
	hkBool m_hasHit;               // +8
	hkContactPoint m_hitContact;   // +0x10
	hkSimpleClosestContactCollector() { reset(); }
	void reset() { m_earlyOutDistance = HK_REAL_MAX; m_hasHit = hkBool(false); m_hitContact.m_separatingNormal.w = HK_REAL_MAX; }
	virtual void addCdPoint(const hkCdPoint& p);
};

struct hkAgentEntry
{
	uint8_t m_streamCommand;      // +0 (6 == bridge entry)
	hkCollisionAgent* m_agent;    // +4 (32-bit offset)
};
struct hkAgent3Input
{
	const hkCdBody* m_bodyA;
	const hkCdBody* m_bodyB;
	const hkCollisionInput* m_input;
	hkContactMgr* m_contactMgr;
};
struct hkAgent3ProcessInput
{
	const hkCdBody* m_bodyA;
	const hkCdBody* m_bodyB;
	const hkProcessCollisionInput* m_input;
};
enum { HK_AGENT3_BRIDGE_COMMAND = 6 };

// ---- hkTriangleUtil ------------------------------------------------------------------------------------------
struct hkTriangleUtil
{
	static hkBool isNonDegenerate(const hkVector4& a, const hkVector4& b, const hkVector4& c, hkReal tol);
};

// @ 0x010eb310
hkBool hkTriangleUtil::isNonDegenerate(const hkVector4& a, const hkVector4& b, const hkVector4& c, hkReal tol)
{
	// Edge products of (a,b,c) and (b,a,c) cross products; x87 keeps differences and the last component unstored.
	// X87-PRECISION: the a-b differences, a-c z difference and the third component stay on the x87 stack.
	hkX87Real x1 = (hkX87Real)a.x - b.x;
	hkX87Real y1 = (hkX87Real)a.y - b.y;
	hkX87Real z1 = (hkX87Real)a.z - b.z;
	float acx = a.x - c.x;   // fstp [esp]
	float acy = a.y - c.y;   // fstp [esp+4]
	hkX87Real acz = (hkX87Real)a.z - c.z;
	float n1x = (float)(acz * y1 - acy * z1);          // [esp+0x20]
	float n1y = (float)(z1 * acx - acz * x1);          // [esp+0x24]
	hkX87Real n1z = acy * x1 - y1 * acx;               // X87-PRECISION: not stored

	hkX87Real bax = (hkX87Real)b.x - a.x;
	hkX87Real bay = (hkX87Real)b.y - a.y;
	hkX87Real baz = (hkX87Real)b.z - a.z;
	float bcx = b.x - c.x;   // [esp+0x10]
	float bcy = b.y - c.y;   // [esp+0x14]
	hkX87Real bcz = (hkX87Real)b.z - c.z;
	float m2x = (float)(bcz * bay - bcy * baz);        // [esp]
	float m2y = (float)(baz * bcx - bcz * bax);        // [esp+4]
	float m2z = (float)(bcy * bax - bay * bcx);        // [esp+8]

	hkX87Real s1 = (n1z * n1z + (hkX87Real)n1y * n1y) + (hkX87Real)n1x * n1x;
	if (!(s1 < tol))      // fcomp / test ah,5 / jnp: only an ordered "less" rejects
	{
		hkX87Real s2 = ((hkX87Real)m2z * m2z + (hkX87Real)m2y * m2y) + (hkX87Real)m2x * m2x;
		if (!(s2 < tol))
			return hkBool(true);
	}
	return hkBool(false);
}

// ---- hkConvexPieceShape ----------------------------------------------------------------------------------------
// A convex piece of a shape collection: its vertices plus the triangle keys of the collection it was cut from.
class hkConvexPieceShape : public hkConvexShape
{
public:
	hkConvexPieceShape(hkReal radius);                                                                     // 0x010EB440
	virtual void getAabb(const hkTransform& t, hkReal tolerance, hkAabb& out) const;                       // 3  0x010EB570
	virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const;          // 5  0x010EB820
	virtual void getCollisionSpheresInfo(hkCollisionSpheresInfo& info) const;                              // 7  0x010EB430
	virtual const hkSphere* getCollisionSpheres(hkSphere* buffer) const;                                   // 8  0x010EB480
	virtual void getSupportingVertex(const hkVector4& dir, hkCdVertex& out) const;                         // 9  0x010EB730
	virtual void convertVertexIdsToVertices(const uint16_t* ids, int numIds, hkCdVertex* out) const;       // 10 0x010EB4D0
	virtual void getFirstVertex(hkVector4& v) const;                                                       // 11 0x010EB460

	const hkVector4* m_vertices;             // +0x10
	int m_numVertices;                       // +0x14
	const hkShapeCollection* m_collection;   // +0x18
	const hkShapeKey* m_keys;                // +0x1c
	int m_numKeys;                           // +0x20
};

// @ 0x010eb430
void hkConvexPieceShape::getCollisionSpheresInfo(hkCollisionSpheresInfo& info) const
{
	info.m_numSpheres = m_numVertices;
	info.m_useBuffer = hkBool(true);
}

// @ 0x010eb440
hkConvexPieceShape::hkConvexPieceShape(hkReal radius)
	: hkConvexShape(radius)
{
	// Sets refcount 1, userData 0, radius and the vtable (0x014A5274); the vertex/key members are filled by the owner.
}

// @ 0x010eb460
void hkConvexPieceShape::getFirstVertex(hkVector4& v) const
{
	const hkVector4* p = m_vertices;
	v.x = p->x; v.y = p->y; v.z = p->z; v.w = p->w;
}

// @ 0x010eb480
const hkSphere* hkConvexPieceShape::getCollisionSpheres(hkSphere* buffer) const
{
	for (int i = 0; i < m_numVertices; ++i)
	{
		const hkVector4& v = m_vertices[i];
		buffer[i].m_pos.x = v.x;
		buffer[i].m_pos.y = v.y;
		buffer[i].m_pos.z = v.z;
		buffer[i].m_pos.w = v.w;
		buffer[i].m_pos.w = m_radius;   // the radius overwrites the copied w
	}
	return buffer;
}

// @ 0x010eb4d0
void hkConvexPieceShape::convertVertexIdsToVertices(const uint16_t* ids, int numIds, hkCdVertex* out) const
{
	for (int n = numIds; n > 0; --n)
	{
		uint32_t id = *ids;
		int tri = (int)id / 3;
		int corner = (int)id % 3;
		uint8_t buffer[HK_SHAPE_BUFFER_SIZE];
		const hkShape* child = m_collection->getChildShape(m_keys[tri], buffer);
		// A triangle child keeps its three vertices at +0x10, +0x20, +0x30.
		const hkVector4* verts = (const hkVector4*)((const char*)child + 0x10);
		const hkVector4& v = verts[corner];
		out->x = v.x; out->y = v.y; out->z = v.z; out->w = v.w;
		out->wBits = id | 0x3f000000u;
		++ids;
		++out;
	}
}

// @ 0x010eb570
void hkConvexPieceShape::getAabb(const hkTransform& t, hkReal tolerance, hkAabb& out) const
{
	out.m_min.x = HK_REAL_MAX; out.m_min.y = HK_REAL_MAX; out.m_min.z = HK_REAL_MAX; out.m_min.w = HK_REAL_MAX;
	out.m_max.x = -HK_REAL_MAX; out.m_max.y = -HK_REAL_MAX; out.m_max.z = -HK_REAL_MAX; out.m_max.w = -HK_REAL_MAX;
	for (int i = 0; i < m_numVertices; ++i)
	{
		float x = m_vertices[i].x, y = m_vertices[i].y, z = m_vertices[i].z;
		float tx = (y * t.m_rot[1].x + (z * t.m_rot[2].x + x * t.m_rot[0].x)) + t.m_trans.x;   // [esp+0x10]
		float ty = (y * t.m_rot[1].y + (z * t.m_rot[2].y + x * t.m_rot[0].y)) + t.m_trans.y;   // [esp+0x14]
		hkX87Real tz = (y * t.m_rot[1].z + (z * t.m_rot[2].z + x * t.m_rot[0].z)) + t.m_trans.z;   // X87-PRECISION: kept on the x87 stack

		// Each min/max is a compare and select with the binary's exact operand order (NaN picks the second operand).
		out.m_min.x = (out.m_min.x < tx) ? out.m_min.x : tx;
		out.m_min.y = (out.m_min.y < ty) ? out.m_min.y : ty;
		out.m_min.z = (tz > out.m_min.z) ? out.m_min.z : (float)tz;
		out.m_min.w = (out.m_min.w < 0.0f) ? out.m_min.w : 0.0f;
		out.m_max.x = (out.m_max.x > tx) ? out.m_max.x : tx;
		out.m_max.y = (out.m_max.y > ty) ? out.m_max.y : ty;
		out.m_max.z = (tz < out.m_max.z) ? out.m_max.z : (float)tz;
		out.m_max.w = (out.m_max.w > 0.0f) ? out.m_max.w : 0.0f;
	}
	hkX87Real r = (hkX87Real)tolerance + m_radius;   // X87-PRECISION: stays on the x87 stack
	out.m_min.x = (float)(out.m_min.x - r);
	out.m_min.y = (float)(out.m_min.y - r);
	out.m_min.z = (float)(out.m_min.z - r);
	out.m_min.w = (float)(out.m_min.w - r);
	out.m_max.x = (float)(r + out.m_max.x);
	out.m_max.y = (float)(r + out.m_max.y);
	out.m_max.z = (float)(r + out.m_max.z);
	out.m_max.w = (float)(r + out.m_max.w);
}

// @ 0x010eb730
void hkConvexPieceShape::getSupportingVertex(const hkVector4& dir, hkCdVertex& out) const
{
	float best = -HK_REAL_MAX;
	uint32_t bestId = 0;
	for (int i = 0; i < m_numKeys; ++i)
	{
		uint8_t buffer[HK_SHAPE_BUFFER_SIZE];
		const hkConvexShape* child = static_cast<const hkConvexShape*>(m_collection->getChildShape(m_keys[i], buffer));
		hkCdVertex v;
		child->getSupportingVertex(dir, v);
		// X87-PRECISION: the dot product is compared before it is stored to best.
		hkX87Real dot = ((hkX87Real)v.x * dir.x + (hkX87Real)v.y * dir.y) + (hkX87Real)v.z * dir.z;
		if (dot > best)
		{
			out.x = v.x; out.y = v.y; out.z = v.z; out.wBits = v.wBits;
			int t = (int)(v.wBits & 0xc0ffffffu);
			bestId = (uint32_t)(((t + ((t >> 31) & 0xf)) >> 4) + 3 * i);
			best = (float)dot;
		}
	}
	out.wBits = bestId | 0x3f000000u;
}

// @ 0x010eb820
hkBool hkConvexPieceShape::castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const
{
	HK_TIMER_SPLIT_LIST("TtrcConvxPiece");
	hkShapeRayCastOutput local;     // only m_hitFraction is initialized (1.0)
	int hitIndex = -1;
	hkReal best = HK_REAL_MAX;
	for (int i = 0; i < m_numKeys; ++i)
	{
		const hkRayShapeCollectionFilter* filter = input.m_rayShapeCollectionFilter;
		if (filter == 0 || filter->isCollisionEnabled(input, *m_collection, m_keys[i]))
		{
			uint8_t buffer[HK_SHAPE_BUFFER_SIZE];
			const hkShape* child = m_collection->getChildShape(m_keys[i], buffer);
			if (child->castRay(input, local) && local.m_hitFraction < best)
			{
				best = local.m_hitFraction;
				output.m_normal = local.m_normal;
				output.m_extraInfo = local.m_extraInfo;
				output.m_hitFraction = local.m_hitFraction;
				hitIndex = i;
			}
		}
	}
	HK_TIMER_END_LIST();
	return hkBool(hitIndex != -1);
}

// ---- hkAgent3Bridge: agent3 entry points that forward to an hkCollisionAgent --------------------------------------
struct hkAgent3Bridge
{
	static void* process(const hkAgent3ProcessInput& in, hkAgentEntry* entry, void* agentData, hkVector4* sepNormal, hkProcessCollisionOutput& out);
	static void destroy(hkAgentEntry* entry, void* agentData, hkContactMgr* mgr);
	static void updateFilter(hkAgentEntry* entry, void* agentData, hkCdBody& a, hkCdBody& b, const hkCollisionInput& input);
	static void invalidateTim(hkAgentEntry* entry, void* agentData, hkCollisionInput& input);
	static void warpTime(hkAgentEntry* entry, void* agentData, hkTime oldTime, hkTime newTime, hkCollisionInput& input);
	static void removePoint(hkAgentEntry* entry, void* agentData, hkContactPointId id);
	static void commitPotential(hkAgentEntry* entry, void* agentData, hkContactPointId id);
	static void createZombie(hkAgentEntry* entry, void* agentData, hkContactPointId id);
	static void* create(const hkAgent3Input& in, hkAgentEntry* entry, void* agentData);
	static void registerBridgeAgent3(hkCollisionDispatcher* dispatcher);
};

// @ 0x010eb9b0
void* hkAgent3Bridge::process(const hkAgent3ProcessInput& in, hkAgentEntry* entry, void* agentData, hkVector4* sepNormal, hkProcessCollisionOutput& out)
{
	entry->m_agent->processCollision(*in.m_bodyA, *in.m_bodyB, *in.m_input, out);
	return agentData;
}

// @ 0x010eb9e0
void hkAgent3Bridge::destroy(hkAgentEntry* entry, void* agentData, hkContactMgr* mgr)
{
	// The binary tail-jumps into slot 6 (cleanup takes no arguments).
	entry->m_agent->cleanup();
}

// @ 0x010eb9f0
void hkAgent3Bridge::updateFilter(hkAgentEntry* entry, void* agentData, hkCdBody& a, hkCdBody& b, const hkCollisionInput& input)
{
	entry->m_agent->updateShapeCollectionFilter(a, b, input);
}

// @ 0x010eba10
void hkAgent3Bridge::invalidateTim(hkAgentEntry* entry, void* agentData, hkCollisionInput& input)
{
	entry->m_agent->invalidateTim(input);
}

// @ 0x010eba30
void hkAgent3Bridge::warpTime(hkAgentEntry* entry, void* agentData, hkTime oldTime, hkTime newTime, hkCollisionInput& input)
{
	entry->m_agent->warpTime(oldTime, newTime, input);
}

// @ 0x010eba50
void hkAgent3Bridge::removePoint(hkAgentEntry* entry, void* agentData, hkContactPointId id)
{
	entry->m_agent->removePoint(id);
}

// @ 0x010eba70
void hkAgent3Bridge::commitPotential(hkAgentEntry* entry, void* agentData, hkContactPointId id)
{
	entry->m_agent->commitPotential(id);
}

// @ 0x010eba90
void hkAgent3Bridge::createZombie(hkAgentEntry* entry, void* agentData, hkContactPointId id)
{
	entry->m_agent->createZombie(id);
}

// @ 0x010ebab0
void* hkAgent3Bridge::create(const hkAgent3Input& in, hkAgentEntry* entry, void* agentData)
{
	const hkCollisionInput* input = in.m_input;
	hkCollisionDispatcher* dispatcher = input->m_dispatcher;
	int typeA = in.m_bodyA->m_shape->getType();
	int typeB = in.m_bodyB->m_shape->getType();
	const uint8_t (*table)[32] = input->m_createPredictiveAgents ? dispatcher->m_agent2TypesPredictive : dispatcher->m_agent2TypesDiscrete;
	uint8_t agentType = table[typeA][typeB];
	hkCollisionAgent* agent = dispatcher->m_agent2Func[agentType].m_createFunc(*in.m_bodyA, *in.m_bodyB, *input, in.m_contactMgr);
	entry->m_agent = agent;
	entry->m_streamCommand = HK_AGENT3_BRIDGE_COMMAND;
	return agentData;
}

struct hkCollisionDispatcher::Agent3Funcs
{
	void* (*m_createFunc)(const hkAgent3Input&, hkAgentEntry*, void*);                                   // +0
	void (*m_destroyFunc)(hkAgentEntry*, void*, hkContactMgr*);                                          // +4
	void* m_cleanupFunc;                                                                                 // +8
	void (*m_removePointFunc)(hkAgentEntry*, void*, hkContactPointId);                                   // +0xc
	void (*m_commitPotentialFunc)(hkAgentEntry*, void*, hkContactPointId);                               // +0x10
	void (*m_createZombieFunc)(hkAgentEntry*, void*, hkContactPointId);                                  // +0x14
	void (*m_updateFilterFunc)(hkAgentEntry*, void*, hkCdBody&, hkCdBody&, const hkCollisionInput&);     // +0x18
	void (*m_invalidateTimFunc)(hkAgentEntry*, void*, hkCollisionInput&);                                // +0x1c
	void (*m_warpTimeFunc)(hkAgentEntry*, void*, hkTime, hkTime, hkCollisionInput&);                     // +0x20
	void* m_sepNormalFunc;                                                                               // +0x24
	void* (*m_processFunc)(const hkAgent3ProcessInput&, hkAgentEntry*, void*, hkVector4*, hkProcessCollisionOutput&);   // +0x28
	hkBool m_isPredictive;                                                                               // +0x2c
	hkBool m_reserved;                                                                                   // +0x2d
};

// @ 0x010ebb30
void hkAgent3Bridge::registerBridgeAgent3(hkCollisionDispatcher* dispatcher)
{
	hkCollisionDispatcher::Agent3Funcs funcs = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, hkBool(false), hkBool(false) };
	funcs.m_createFunc = &hkAgent3Bridge::create;
	funcs.m_destroyFunc = &hkAgent3Bridge::destroy;
	funcs.m_cleanupFunc = 0;
	funcs.m_removePointFunc = &hkAgent3Bridge::removePoint;
	funcs.m_commitPotentialFunc = &hkAgent3Bridge::commitPotential;
	funcs.m_createZombieFunc = &hkAgent3Bridge::createZombie;
	funcs.m_updateFilterFunc = &hkAgent3Bridge::updateFilter;
	funcs.m_invalidateTimFunc = &hkAgent3Bridge::invalidateTim;
	funcs.m_warpTimeFunc = &hkAgent3Bridge::warpTime;
	funcs.m_sepNormalFunc = 0;
	funcs.m_processFunc = &hkAgent3Bridge::process;
	funcs.m_isPredictive = hkBool(true);
	dispatcher->registerAgent3(funcs, -1, -1);
}

// ---- hkSymmetricAgent flip collectors --------------------------------------------------------------------------
struct hkSymmetricAgentFlipCollector : hkCdPointCollector
{
	hkCdPointCollector* m_collector;   // +8
	virtual void addCdPoint(const hkCdPoint& point);
};
struct hkSymmetricAgentFlipCastCollector : hkCdPointCollector
{
	uint32_t m_pad8[6];                // +8..+0x1f
	hkCdPointCollector* m_collector;   // +0x20
	virtual void addCdPoint(const hkCdPoint& point);
};
struct hkSymmetricAgentFlipBodyCollector : hkCdBodyPairCollector
{
	hkCdBodyPairCollector* m_collector;   // +8
	virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b);
};

// @ 0x010ebbb0
void hkSymmetricAgentFlipCollector::addCdPoint(const hkCdPoint& point)
{
	hkCdPoint flipped;
	flipped.m_cdBodyA = point.m_cdBodyB;
	flipped.m_cdBodyB = point.m_cdBodyA;
	flipped.m_contact.setFlipped(point.m_contact);
	m_collector->addCdPoint(flipped);
	m_earlyOutDistance = m_collector->m_earlyOutDistance;
}

// @ 0x010ebc00
void hkSymmetricAgentFlipCastCollector::addCdPoint(const hkCdPoint& point)
{
	hkCdPoint flipped;
	flipped.m_cdBodyA = point.m_cdBodyB;
	flipped.m_cdBodyB = point.m_cdBodyA;
	flipped.m_contact.setFlipped(point.m_contact);
	m_collector->addCdPoint(flipped);
	m_earlyOutDistance = m_collector->m_earlyOutDistance;
}

// @ 0x010ebc50
void hkSymmetricAgentFlipBodyCollector::addCdBodyPair(const hkCdBody& a, const hkCdBody& b)
{
	m_collector->addCdBodyPair(b, a);
	m_earlyOut = m_collector->m_earlyOut;
}

// ---- hkIterativeLinearCastAgent::staticLinearCast -----------------------------------------------------------------
struct hkIterativeLinearCastAgent
{
	static void staticLinearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input,
	                             hkCdPointCollector& castCollector, hkCdPointCollector* startCollector);
};

// @ 0x010ebc80
// Moves body A along the path, using getClosestPoints at each step to find the time of impact iteratively.
void hkIterativeLinearCastAgent::staticLinearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input,
                                                  hkCdPointCollector& castCollector, hkCdPointCollector* startCollector)
{
	// Closest-points input: the dispatcher/flags of the cast input with tolerance widened by the path length.
	hkCollisionInput closestInput;
	closestInput.m_dispatcher = input.m_dispatcher;
	closestInput.m_filter = input.m_filter;
	closestInput.m_tolerance = input.m_tolerance + input.m_cachedPathLength;
	closestInput.m_createPredictiveAgents = input.m_createPredictiveAgents;

	hkSimpleClosestContactCollector collector;
	int typeA = bodyA.m_shape->getType();
	int typeB = bodyB.m_shape->getType();
	hkAgent2GetClosestPointsFunc getClosestPoints =
		input.m_dispatcher->m_agent2Func[input.m_dispatcher->m_agent2TypesDiscrete[typeA][typeB]].m_getClosestPointFunc;
	getClosestPoints(bodyA, bodyB, closestInput, collector);
	if (!collector.m_hasHit)
		return;

	// Point reported to the caller: the closest point with the cd bodies replaced by the originals.
	hkCdPoint point;
	point.m_contact = collector.m_hitContact;
	point.m_cdBodyA = &bodyA;
	point.m_cdBodyB = &bodyB;
	float dist = collector.m_hitContact.m_separatingNormal.w;
	if (dist < input.m_tolerance && startCollector != 0)
		startCollector->addCdPoint(point);

	const hkVector4& n = collector.m_hitContact.m_separatingNormal;
	// X87-PRECISION: d is not stored; fVar3 is stored to a float local and reused.
	hkX87Real d = ((hkX87Real)n.x * input.m_path.x + (hkX87Real)n.z * input.m_path.z) + (hkX87Real)n.y * input.m_path.y;
	float distAfter = (float)(dist + d);
	if (distAfter > 0.0f)
		return;
	if (d + input.m_maxExtraPenetration >= 0.0)    // test ah,1 after fcomp: only "less" (or unordered) continues
		return;

	if (!(dist <= input.m_config->m_iterativeLinearCastEarlyOutDistance))      // jp: dist > early (or unordered) -> iterate
	{
		// Iterative refinement: sweep a copy of A's motion state forward and re-query the closest points.
		hkSimpleClosestContactCollector collector2;
		// fdivr result is stored (fstp) into the point's distance slot, which holds the current fraction.
		point.m_contact.m_separatingNormal.w = (float)((hkX87Real)dist / ((hkX87Real)dist - distAfter));

		hkMotionState movedMotion;
		movedMotion = *(const hkMotionState*)bodyA.m_motion;
		hkCdBody movedBody;
		movedBody.m_shape = bodyA.m_shape;
		movedBody.m_shapeKey = bodyA.m_shapeKey;
		movedBody.m_motion = &movedMotion;
		movedBody.m_parent = &bodyA;

		hkVector4* movedTrans = &movedMotion.m_transform.m_trans;
		const hkVector4* origTrans = &((const hkMotionState*)bodyA.m_motion)->m_transform.m_trans;
		for (int i = input.m_config->m_iterativeLinearCastMaxIterations - 1; i >= 0; --i)
		{
			collector2.reset();
			float f = point.m_contact.m_separatingNormal.w;
			movedTrans->x = f * input.m_path.x + origTrans->x;
			movedTrans->y = f * input.m_path.y + origTrans->y;
			movedTrans->z = f * input.m_path.z + origTrans->z;
			movedTrans->w = f * input.m_path.w + origTrans->w;
			getClosestPoints(movedBody, bodyB, closestInput, collector2);
			if (!collector2.m_hasHit)
				return;
			const hkVector4& n2 = collector2.m_hitContact.m_separatingNormal;
			// X87-PRECISION: dot, its negation and the extrapolated distance stay on the x87 stack.
			hkX87Real dot = ((hkX87Real)n2.y * input.m_path.y + (hkX87Real)n2.z * input.m_path.z) + (hkX87Real)n2.x * input.m_path.x;
			if (dot >= 0.0)
				return;
			float curDist = n2.w;
			hkX87Real negDot = -dot;
			if (negDot < (hkX87Real)f * negDot + curDist)
				return;
			hkX87Real newFrac = curDist / negDot + f;
			if (newFrac > castCollector.m_earlyOutDistance)
				return;
			point.m_contact.m_position = collector2.m_hitContact.m_position;
			point.m_contact.setSeparatingNormal(n2, (float)newFrac);
			if (curDist <= input.m_config->m_iterativeLinearCastEarlyOutDistance)
				break;
		}
		castCollector.addCdPoint(point);
		return;
	}

	if (dist <= 0.0f)
	{
		point.m_contact.m_separatingNormal.w = 0.0f;
		castCollector.addCdPoint(point);
		return;
	}
	// X87-PRECISION: the fraction is compared before it is stored into the point.
	hkX87Real frac = (hkX87Real)dist / ((hkX87Real)dist - distAfter);
	if (!(frac > castCollector.m_earlyOutDistance))
	{
		point.m_contact.m_separatingNormal.w = (float)frac;
		castCollector.addCdPoint(point);
	}
}
