// Havok 3.1.0 slice s010e0320: hkShapeCollectionAgent (and its hkSymmetricAgent wrappers) plus
// hkTransformAgent::createTransformBAgent and hkSymmetricAgent<hkTransformAgent>::linearCast
// (SporeApp.exe 0x010e0320..0x010e1311).
//
// Layout notes: class stubs carry members at the offsets seen in the 32-bit binary. Shared declarations come from
// the batch's hk31_b005.h; collision-agent / collector pieces are copied from slices s010e7590 and s010df100.
//
// Flags: /vc71 /O2 /MD /Gy /TP
#include "../s010cbaa0/hk31_b005.h"

typedef float hkTime;
typedef uint32_t hkShapeKey;
#define HK_INVALID_SHAPE_KEY 0xffffffffu
#define HK_REAL_MAX 3.40282e+38f      // 0x7f7fffee in this build (not FLT_MAX)

// ---- shapes ----------------------------------------------------------------------------------------------------------
// hkShapeBuffer: 512 bytes of scratch for getChildShape (stack allocated, 16-byte aligned frame).
#if defined(_MSC_VER)
__declspec(align(16)) struct hkShapeBuffer { uint32_t m_storage[128]; };
#else
struct __attribute__((aligned(16))) hkShapeBuffer { uint32_t m_storage[128]; };
#endif

class hkShapeCollection;
class hkCollisionInput;

// slot 0: hidden hkBool return pointer (hkBool is non-POD), then input, collA, collB, container, key.
class hkShapeCollectionFilter
{ public:
	virtual hkBool isCollisionEnabled(const hkCollisionInput& input, const hkCdBody& collA, const hkCdBody& collB,
	                                  const hkShapeCollection& bContainer, hkShapeKey bKey) const = 0;
};

class hkShapeCollection : public hkShape
{ public:
	char m_disableWelding;                     // +0xc
	virtual int getNumChildShapes() const;                                             // 7 (+0x1c)
	virtual hkShapeKey getFirstKey() const = 0;                                        // 8 (+0x20)
	virtual hkShapeKey getNextKey(hkShapeKey oldKey) const = 0;                        // 9 (+0x24)
	virtual const hkShape* getChildShape(hkShapeKey key, hkShapeBuffer& buffer) const = 0;  // 10 (+0x28)
};

// hkTransformShape: the child shape at +0xc, then the shape-relative rotation (quaternion) and transform.
struct hkTransformShape : hkShape
{
	const hkShape* m_childShape;               // +0xc
	hkVector4 m_rotation;                      // +0x10
	hkTransform m_transform;                   // +0x20
};

// ---- collision input / contact points / collectors -------------------------------------------------------------------
struct hkContactMgr;
class hkCollisionDispatcher;

struct hkCollisionInput
{
	hkCollisionDispatcher* m_dispatcher;       // +0
	hkShapeCollectionFilter* m_filter;         // +4
	float m_tolerance;                         // +8
	char m_createPredictiveAgents;             // +0xc
	char m_pad[3];
};
struct hkProcessCollisionInput : hkCollisionInput {};
struct hkLinearCastCollisionInput : hkCollisionInput
{
	hkVector4 m_path;                          // +0x10
	uint32_t m_pad3[4];                        // total 0x30 bytes
};

class hkContactPoint
{ public:
	hkVector4 m_position;
	hkVector4 m_separatingNormal;              // w = distance
	void setFlipped(const hkContactPoint& other);   // 0x010CECF0
};
struct hkProcessCdPoint { hkContactPoint m_contact; uint32_t m_extra[4]; };   // 0x30 bytes
struct hkCdPoint { hkContactPoint m_contact; const hkCdBody* m_cdBodyA; const hkCdBody* m_cdBodyB; };

class hkCdPointCollector
{ public:
	hkCdPointCollector() { m_earlyOutDistance = HK_REAL_MAX; }
	virtual void v0();
	virtual void addCdPoint(const hkCdPoint& point);   // slot 1 (+4)
	float m_earlyOutDistance;                          // +4
};
class hkCdBodyPairCollector
{ public:
	hkCdBodyPairCollector() { m_earlyOut = 0; }
	virtual void v0();
	virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b);   // slot 1 (+4)
	char m_earlyOut;                                   // +4
};
struct hkProcessCollisionOutput
{
	hkProcessCdPoint* m_firstFreeContactPoint; // +0
	uint32_t m_pad0[3];
	hkContactPoint m_toiContact;               // +0x10
	hkProcessCdPoint m_contactPoints[256];     // +0x30
	uint32_t m_toiProperties;                  // +0x3030
	hkTime   m_toiTime;                        // +0x3034
};

// ---- flip helpers (hkSymmetricAgent): vtables 0x014a43a4 / 0x014a43b4 / 0x014a43ac --------------------------------------
class hkSymmetricAgentFlipCollector : public hkCdPointCollector { public:
	hkCdPointCollector& m_original;                                       // +8
	hkSymmetricAgentFlipCollector(hkCdPointCollector& c) : m_original(c) {}
	virtual void addCdPoint(const hkCdPoint& point);                       // 0x010EBBB0
};
class hkSymmetricAgentFlipBodyCollector : public hkCdBodyPairCollector { public:
	hkCdBodyPairCollector& m_original;                                    // +8
	hkSymmetricAgentFlipBodyCollector(hkCdBodyPairCollector& c) : m_original(c) {}
	virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b);      // 0x010EBC50
};
class hkSymmetricAgentFlipCastCollector : public hkCdPointCollector { public:
	uint32_t m_pad[2];
	hkVector4 m_path;                                                     // +0x10
	hkCdPointCollector* m_original;                                       // +0x20
	hkSymmetricAgentFlipCastCollector(const hkVector4& path, hkCdPointCollector* c) : m_path(path), m_original(c) {}
	virtual void addCdPoint(const hkCdPoint& point);                       // 0x010EBC00
};

// ---- collision dispatcher (only what this slice touches; 32-bit offsets) ---------------------------------------------
class hkCollisionAgent;
typedef hkCollisionAgent* (__cdecl *hkAgentCreateFunc)(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkContactMgr*);
typedef void (__cdecl *hkAgentGetPenetrationsFunc)(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
typedef void (__cdecl *hkAgentGetClosestPointsFunc)(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
typedef void (__cdecl *hkAgentLinearCastFunc)(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
struct hkAgentFuncs   // hkCollisionDispatcher::AgentFuncs, 0x14 bytes in the 32-bit binary
{
	hkAgentCreateFunc m_createFunc;                         // +0
	hkAgentGetPenetrationsFunc m_getPenetrationsFunc;       // +4
	hkAgentGetClosestPointsFunc m_getClosestPointFunc;      // +8
	hkAgentLinearCastFunc m_linearCastFunc;                 // +0xc
	char m_isFlipped;                                       // +0x10
	char m_isPredictive;                                    // +0x11
};
class hkCollisionDispatcher
{ public:
	char m_pad0[0x190];
	uint8_t m_agent2Types[32][32];             // +0x190: [typeA][typeB] -> agent index
	uint8_t m_agent2TypesPredictive[32][32];   // +0x590
	hkAgentFuncs m_agent2Func[1];              // +0x990 (stride 0x14 in the binary)
};

// ---- collision agents ------------------------------------------------------------------------------------------------
class hkCollisionAgent : public hkReferencedObject { public:
	hkContactMgr* m_contactMgr;                // +8
	virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);                                   // +8
	virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);                                     // +0xc
	virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);           // +0x10
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);                       // +0x14
	virtual void cleanup();                                                                                                                            // +0x18
	virtual void updateShapeCollectionFilter(const hkCdBody&, const hkCdBody&, const hkCollisionInput&);                                               // +0x1c
	virtual void invalidateTim(hkCollisionInput&);                                                                                                     // +0x20
	virtual void warpTime(hkTime t0, hkTime t1, hkCollisionInput&);                                                                                    // +0x24
};

// ---- motion state (0xb0 bytes); hkCdBody::m_motion points at one -------------------------------------------------------
class hkMotionState
{ public:
	hkTransform m_transform;                   // +0
	hkVector4 m_centerOfMass0;                 // +0x40
	hkVector4 m_centerOfMass1;                 // +0x50
	hkVector4 m_rotation0;                     // +0x60
	hkVector4 m_rotation1;                     // +0x70
	hkVector4 m_centerOfMassLocal;             // +0x80
	uint32_t m_misc[7];                        // +0x90 .. 0xab
	uint16_t m_h0;                             // +0xac
	uint16_t m_h1;                             // +0xae
	hkMotionState& operator=(const hkMotionState& other);   // 0x010DF5D0
};

// hk31_b005.h's hkTransform only declares setMulInverseMul; add setMul (0x01080EF0) for this slice.
struct hkTransformExtra : hkTransform { public:
	void setMul(const hkTransform& a, const hkTransform& b);
};

// ---- hkShapeCollectionAgent -------------------------------------------------------------------------------------------
class hkShapeCollectionAgent : public hkCollisionAgent
{ public:
	struct Child { hkShapeKey m_key; hkCollisionAgent* m_agent; };   // 8 bytes
	hkArray<Child> m_children;                 // +0xc (m_data / m_size / m_capacityAndFlags)
	Child m_inlineStorage[4];                  // +0x18 (capacity 4, memory not owned)
	hkShapeCollectionAgent(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkContactMgr* mgr);
	virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
	virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
	virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);
	virtual void updateShapeCollectionFilter(const hkCdBody&, const hkCdBody&, const hkCollisionInput&);
	virtual void invalidateTim(hkCollisionInput& input);
	virtual void warpTime(hkTime t0, hkTime t1, hkCollisionInput& input);
	static void staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector);
	static void staticLinearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input, hkCdPointCollector& collector, hkCdPointCollector* startCollector);
	static void staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector);
};

// hkSymmetricAgent<hkShapeCollectionAgent>: vtable 0x014A4D24-ish wrappers that swap bodyA / bodyB.
struct hkSymmetricAgent_hkShapeCollectionAgent : hkShapeCollectionAgent
{
	hkSymmetricAgent_hkShapeCollectionAgent(const hkCdBody& A, const hkCdBody& B, const hkCollisionInput& input, hkContactMgr* mgr)
		: hkShapeCollectionAgent(B, A, input, mgr) {}
	virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);   // 0x010E1220
	virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);     // 0x010E1260
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);  // 0x010E12A0
};

// ---- hkTransformAgent / hkTransformBAgent ----------------------------------------------------------------------------
struct hkTransformAgent : hkCollisionAgent
{
	hkCollisionAgent* m_childAgent;            // +0xc
	__forceinline hkTransformAgent(const hkCdBody& transformBody, const hkCdBody& otherBody, const hkCollisionInput& input, hkContactMgr* mgr)
	{
		m_contactMgr = mgr;
		const hkTransformShape* shape = (const hkTransformShape*)transformBody.m_shape;
		const hkShape* child = shape->m_childShape;
		hkMotionState tmpMotion;
		tmpMotion = *(const hkMotionState*)transformBody.m_motion;
		((hkTransformExtra&)tmpMotion.m_transform).setMul(((const hkMotionState*)transformBody.m_motion)->m_transform, shape->m_transform);
		hkCdBody childBody;
		childBody.m_parent = &transformBody;
		childBody.m_motion = &tmpMotion;
		childBody.m_shapeKey = transformBody.m_shapeKey;
		childBody.m_shape = child;
		hkCollisionDispatcher* dispatcher = input.m_dispatcher;
		int typeA = child->getType();
		int typeB = otherBody.m_shape->getType();
		const uint8_t (*table)[32] = input.m_createPredictiveAgents ? dispatcher->m_agent2TypesPredictive : dispatcher->m_agent2Types;
		uint8_t agentType = table[typeA][typeB];
		m_childAgent = dispatcher->m_agent2Func[agentType].m_createFunc(childBody, otherBody, input, mgr);
	}
	static hkCollisionAgent* createTransformBAgent(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010E0410
};

// The B agent is a hkTransformAgent whose transform body is body B; the two vtable stores (base then derived) come from
// the base-class constructor running before the derived-class body.
struct hkTransformBAgent : hkTransformAgent
{
	__forceinline hkTransformBAgent(const hkCdBody& A, const hkCdBody& B, const hkCollisionInput& input, hkContactMgr* mgr)
		: hkTransformAgent(B, A, input, mgr) {}
};

// hkSymmetricAgent<hkTransformAgent>::linearCast (0x010E0320).
struct hkSymmetricAgent_hkTransformAgent : hkTransformAgent
{
	hkSymmetricAgent_hkTransformAgent(const hkCdBody& A, const hkCdBody& B, const hkCollisionInput& input, hkContactMgr* mgr)
		: hkTransformAgent(B, A, input, mgr) {}
	virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
};

// =====================================================================================================================

// @ 0x010e0320  hkSymmetricAgent<hkTransformAgent>::linearCast
void hkSymmetricAgent_hkTransformAgent::linearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input, hkCdPointCollector& collector, hkCdPointCollector* startCollector)
{
	hkLinearCastCollisionInput flippedInput = input;
	flippedInput.m_path.x = -input.m_path.x;
	flippedInput.m_path.y = -input.m_path.y;
	flippedInput.m_path.z = -input.m_path.z;
	flippedInput.m_path.w = -input.m_path.w;
	hkSymmetricAgentFlipCastCollector flip(input.m_path, &collector);
	if (startCollector)
	{
		hkSymmetricAgentFlipCastCollector startFlip(input.m_path, startCollector);
		hkTransformAgent::linearCast(bodyB, bodyA, flippedInput, flip, &startFlip);
	}
	else
	{
		hkTransformAgent::linearCast(bodyB, bodyA, flippedInput, flip, 0);
	}
}

// @ 0x010e0410  hkTransformAgent::createTransformBAgent
hkCollisionAgent* hkTransformAgent::createTransformBAgent(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkContactMgr* mgr)
{
	return new hkTransformBAgent(bodyA, bodyB, input, mgr);
}

// @ 0x010e0590  hkShapeCollectionAgent::invalidateTim
void hkShapeCollectionAgent::invalidateTim(hkCollisionInput& input)
{
	for (int i = 0; i < m_children.m_size; i++)
		m_children.m_data[i].m_agent->invalidateTim(input);
}

// @ 0x010e05c0  hkShapeCollectionAgent::warpTime
void hkShapeCollectionAgent::warpTime(hkTime t0, hkTime t1, hkCollisionInput& input)
{
	for (int i = 0; i < m_children.m_size; i++)
		m_children.m_data[i].m_agent->warpTime(t0, t1, input);
}

// @ 0x010e0610  hkShapeCollectionAgent::processCollision
void hkShapeCollectionAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkProcessCollisionInput& input, hkProcessCollisionOutput& output)
{
	HK_TIMER_BEGIN("TtShapeCollection");
	const hkShapeCollection* collection = (const hkShapeCollection*)bodyA.m_shape;
	hkShapeBuffer buffer;
	for (int i = 0; i < m_children.m_size; i++)
	{
		hkShapeKey key = m_children.m_data[i].m_key;
		const hkShape* child = collection->getChildShape(key, buffer);
		hkCdBody childBody;
		childBody.m_shape = child;
		childBody.m_shapeKey = key;
		childBody.m_motion = bodyA.m_motion;
		childBody.m_parent = &bodyA;
		m_children.m_data[i].m_agent->processCollision(childBody, bodyB, input, output);
	}
	HK_TIMER_END();
}

// @ 0x010e0730  hkShapeCollectionAgent::getClosestPoints
void hkShapeCollectionAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector)
{
	HK_TIMER_BEGIN("TtShapeCollection");
	const hkShapeCollection* collection = (const hkShapeCollection*)bodyA.m_shape;
	hkShapeBuffer buffer;
	for (int i = 0; i < m_children.m_size; i++)
	{
		hkShapeKey key = m_children.m_data[i].m_key;
		const hkShape* child = collection->getChildShape(key, buffer);
		hkCdBody childBody;
		childBody.m_shape = child;
		childBody.m_shapeKey = key;
		childBody.m_motion = bodyA.m_motion;
		childBody.m_parent = &bodyA;
		m_children.m_data[i].m_agent->getClosestPoints(childBody, bodyB, input, collector);
	}
	HK_TIMER_END();
}

// @ 0x010e0850  hkShapeCollectionAgent::staticGetClosestPoints
void hkShapeCollectionAgent::staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector)
{
	HK_TIMER_BEGIN("TtShapeCollection");
	const hkShapeCollection* collection = (const hkShapeCollection*)bodyA.m_shape;
	int typeB = bodyB.m_shape->getType();
	hkShapeBuffer buffer;
	for (hkShapeKey key = collection->getFirstKey(); key != HK_INVALID_SHAPE_KEY; key = collection->getNextKey(key))
	{
		if (input.m_filter->isCollisionEnabled(input, bodyB, bodyA, *collection, key))
		{
			const hkShape* child = collection->getChildShape(key, buffer);
			hkCdBody childBody;
			childBody.m_shape = child;
			childBody.m_shapeKey = key;
			childBody.m_motion = bodyA.m_motion;
			childBody.m_parent = &bodyA;
			hkCollisionDispatcher* dispatcher = input.m_dispatcher;
			uint8_t agentType = dispatcher->m_agent2Types[child->getType()][typeB];
			dispatcher->m_agent2Func[agentType].m_getClosestPointFunc(childBody, bodyB, input, collector);
		}
	}
	HK_TIMER_END();
}

// @ 0x010e09b0  hkShapeCollectionAgent::linearCast
void hkShapeCollectionAgent::linearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input, hkCdPointCollector& collector, hkCdPointCollector* startCollector)
{
	HK_TIMER_BEGIN("TtShapeCollection");
	const hkShapeCollection* collection = (const hkShapeCollection*)bodyA.m_shape;
	hkShapeBuffer buffer;
	for (int i = 0; i < m_children.m_size; i++)
	{
		hkShapeKey key = m_children.m_data[i].m_key;
		const hkShape* child = collection->getChildShape(key, buffer);
		hkCdBody childBody;
		childBody.m_shape = child;
		childBody.m_shapeKey = key;
		childBody.m_motion = bodyA.m_motion;
		childBody.m_parent = &bodyA;
		m_children.m_data[i].m_agent->linearCast(childBody, bodyB, input, collector, startCollector);
	}
	HK_TIMER_END();
}

// @ 0x010e0ad0  hkShapeCollectionAgent::staticLinearCast
void hkShapeCollectionAgent::staticLinearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input, hkCdPointCollector& collector, hkCdPointCollector* startCollector)
{
	HK_TIMER_BEGIN("TtShapeCollection");
	const hkShapeCollection* collection = (const hkShapeCollection*)bodyA.m_shape;
	int typeB = bodyB.m_shape->getType();
	hkShapeBuffer buffer;
	for (hkShapeKey key = collection->getFirstKey(); key != HK_INVALID_SHAPE_KEY; key = collection->getNextKey(key))
	{
		if (input.m_filter->isCollisionEnabled(input, bodyB, bodyA, *collection, key))
		{
			const hkShape* child = collection->getChildShape(key, buffer);
			hkCdBody childBody;
			childBody.m_shape = child;
			childBody.m_shapeKey = key;
			childBody.m_motion = bodyA.m_motion;
			childBody.m_parent = &bodyA;
			hkCollisionDispatcher* dispatcher = input.m_dispatcher;
			uint8_t agentType = dispatcher->m_agent2Types[child->getType()][typeB];
			dispatcher->m_agent2Func[agentType].m_linearCastFunc(childBody, bodyB, input, collector, startCollector);
		}
	}
	HK_TIMER_END();
}

// @ 0x010e0c30  hkShapeCollectionAgent::getPenetrations
void hkShapeCollectionAgent::getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
	HK_TIMER_BEGIN("TtShapeCollection");
	const hkShapeCollection* collection = (const hkShapeCollection*)bodyA.m_shape;
	hkShapeBuffer buffer;
	for (int i = 0; i < m_children.m_size; i++)
	{
		hkShapeKey key = m_children.m_data[i].m_key;
		const hkShape* child = collection->getChildShape(key, buffer);
		hkCdBody childBody;
		childBody.m_shape = child;
		childBody.m_shapeKey = key;
		childBody.m_motion = bodyA.m_motion;
		childBody.m_parent = &bodyA;
		m_children.m_data[i].m_agent->getPenetrations(childBody, bodyB, input, collector);
		if (collector.m_earlyOut)
			break;
	}
	HK_TIMER_END();
}

// @ 0x010e0d50  hkShapeCollectionAgent::staticGetPenetrations
void hkShapeCollectionAgent::staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
	HK_TIMER_BEGIN("TtShapeCollection");
	const hkShapeCollection* collection = (const hkShapeCollection*)bodyA.m_shape;
	int typeB = bodyB.m_shape->getType();
	hkShapeBuffer buffer;
	for (hkShapeKey key = collection->getFirstKey(); key != HK_INVALID_SHAPE_KEY; key = collection->getNextKey(key))
	{
		if (input.m_filter->isCollisionEnabled(input, bodyB, bodyA, *collection, key))
		{
			const hkShape* child = collection->getChildShape(key, buffer);
			hkCdBody childBody;
			childBody.m_shape = child;
			childBody.m_shapeKey = key;
			childBody.m_motion = bodyA.m_motion;
			childBody.m_parent = &bodyA;
			hkCollisionDispatcher* dispatcher = input.m_dispatcher;
			uint8_t agentType = dispatcher->m_agent2Types[child->getType()][typeB];
			dispatcher->m_agent2Func[agentType].m_getPenetrationsFunc(childBody, bodyB, input, collector);
			if (collector.m_earlyOut)
				break;
		}
	}
	HK_TIMER_END();
}

// @ 0x010e0ec0  hkShapeCollectionAgent::updateShapeCollectionFilter
void hkShapeCollectionAgent::updateShapeCollectionFilter(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input)
{
	const hkShapeCollection* collection = (const hkShapeCollection*)bodyA.m_shape;
	int numChild = collection->getNumChildShapes();
	if (numChild <= 0)
		return;
	hkShapeBuffer buffer;
	hkShapeKey key = collection->getFirstKey();
	int remaining = numChild;
	do
	{
		int found = -1;
		for (int j = 0; j < m_children.m_size; j++)
		{
			if (m_children.m_data[j].m_key == key)
			{
				found = j;
				break;
			}
		}
		if (input.m_filter->isCollisionEnabled(input, bodyB, bodyA, *collection, key))
		{
			const hkShape* child = collection->getChildShape(key, buffer);
			hkCdBody childBody;
			childBody.m_shape = child;
			childBody.m_shapeKey = key;
			childBody.m_motion = bodyA.m_motion;
			childBody.m_parent = &bodyA;
			if (found == -1)
			{
				if (m_children.m_size == m_children.getCapacity())
					hkArrayUtil::_reserveMore(&m_children, 8);
				Child& entry = m_children.m_data[m_children.m_size];
				m_children.m_size = m_children.m_size + 1;
				entry.m_key = key;
				hkCollisionDispatcher* dispatcher = input.m_dispatcher;
				const uint8_t (*table)[32] = input.m_createPredictiveAgents ? dispatcher->m_agent2TypesPredictive : dispatcher->m_agent2Types;
				uint8_t agentType = table[child->getType()][bodyB.m_shape->getType()];
				entry.m_agent = dispatcher->m_agent2Func[agentType].m_createFunc(childBody, bodyB, input, m_contactMgr);
			}
			else
			{
				m_children.m_data[found].m_agent->updateShapeCollectionFilter(childBody, bodyB, input);
			}
		}
		else if (found != -1)
		{
			m_children.m_data[found].m_agent->cleanup();
			m_children.m_size = m_children.m_size - 1;
			m_children.m_data[found] = m_children.m_data[m_children.m_size];
		}
		key = collection->getNextKey(key);
	} while (--remaining != 0);
}

// @ 0x010e1090  hkShapeCollectionAgent::hkShapeCollectionAgent
hkShapeCollectionAgent::hkShapeCollectionAgent(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkContactMgr* mgr)
{
	m_contactMgr = mgr;
	m_children.m_data = m_inlineStorage;
	m_children.m_size = 0;
	m_children.m_capacityAndFlags = 0x80000004;
	const hkShapeCollection* collection = (const hkShapeCollection*)bodyA.m_shape;
	int numChild = collection->getNumChildShapes();
	if (m_children.getCapacity() < numChild)
	{
		int newCap = m_children.getCapacity() * 2;
		if (newCap <= numChild)
			newCap = numChild;
		hkArrayUtil::_reserveExactly(&m_children, newCap, 8);
	}
	if (numChild > 0)
	{
		hkShapeBuffer buffer;
		hkShapeKey key = collection->getFirstKey();
		int remaining = numChild;
		do
		{
			const hkShape* child = collection->getChildShape(key, buffer);
			if (input.m_filter->isCollisionEnabled(input, bodyB, bodyA, *collection, key))
			{
				Child& entry = m_children.m_data[m_children.m_size];
				m_children.m_size = m_children.m_size + 1;
				hkCollisionDispatcher* dispatcher = input.m_dispatcher;
				const uint8_t (*table)[32] = input.m_createPredictiveAgents ? dispatcher->m_agent2TypesPredictive : dispatcher->m_agent2Types;
				uint8_t agentType = table[child->getType()][bodyB.m_shape->getType()];
				hkCdBody childBody;
				childBody.m_shape = child;
				childBody.m_shapeKey = key;
				childBody.m_motion = bodyA.m_motion;
				childBody.m_parent = &bodyA;
				entry.m_agent = dispatcher->m_agent2Func[agentType].m_createFunc(childBody, bodyB, input, mgr);
				entry.m_key = key;
			}
			key = collection->getNextKey(key);
		} while (--remaining != 0);
	}
}

// @ 0x010e1220  hkSymmetricAgent<hkShapeCollectionAgent>::getPenetrations
void hkSymmetricAgent_hkShapeCollectionAgent::getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
	hkSymmetricAgentFlipBodyCollector flip(collector);
	hkShapeCollectionAgent::getPenetrations(bodyB, bodyA, input, flip);
}

// @ 0x010e1260  hkSymmetricAgent<hkShapeCollectionAgent>::getClosestPoints
void hkSymmetricAgent_hkShapeCollectionAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector)
{
	hkSymmetricAgentFlipCollector flip(collector);
	hkShapeCollectionAgent::getClosestPoints(bodyB, bodyA, input, flip);
}

// @ 0x010e12a0  hkSymmetricAgent<hkShapeCollectionAgent>::processCollision
void hkSymmetricAgent_hkShapeCollectionAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkProcessCollisionInput& input, hkProcessCollisionOutput& result)
{
	hkProcessCdPoint* pp = result.m_firstFreeContactPoint;
	float oldToi = result.m_toiTime;
	hkShapeCollectionAgent::processCollision(bodyB, bodyA, input, result);
	for (; pp < result.m_firstFreeContactPoint; pp++)
		pp->m_contact.setFlipped(pp->m_contact);
	// fucompp + test ah,0x44 / jnp: flip when (oldToi != toiTime), NaN included
	if (oldToi != result.m_toiTime)
	{
		result.m_toiContact.m_separatingNormal.x = -result.m_toiContact.m_separatingNormal.x;
		result.m_toiContact.m_separatingNormal.y = -result.m_toiContact.m_separatingNormal.y;
		result.m_toiContact.m_separatingNormal.z = -result.m_toiContact.m_separatingNormal.z;
	}
}

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
