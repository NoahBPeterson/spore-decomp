// Havok 3.1.0 slice s010e7590: hkBvAgent static queries, hkSymmetricAgent<hkBvAgent>, hkShapeCollection,
// shape-type helpers (SporeApp.exe 0x010e7590..0x010e86bc).
//
// Layout notes: class stubs carry members at the offsets seen in the 32-bit binary. Pointer members make the
// 64-bit offsets differ; behaviour (not layout) is what is ported. Shared declarations come from the batch's
// hk31_b005.h (memory, monitor stream, shapes, rays); collision-agent pieces are copied from slices s010df100 and
// s010dcd40.
#include "../s010cbaa0/hk31_b005.h"

// ---- monitor stream: 16-byte "list begin" command (name + sub-name) and the "list end" tag at 0x00143cd94 ------------
extern const char hkMonitorListEndTag[];     // string at 0x00143cd94 (end of a timer list)
struct hkMonitorCommandList { const char* m_commandAndMonitor; uint32_t m_time0; uint32_t m_pad; const char* m_secondCommand; };   // 16 bytes (32-bit)
#define HK_TIMER_BEGIN_LIST(a, b) do { \
	void* hkEnd_ = hkTlsGet(g_hkMonitorStreamEndTls); \
	if (hkTlsGet(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
		hkMonitorCommandList* c_ = (hkMonitorCommandList*)hkTlsGet(g_hkMonitorStreamCurrentTls); \
		c_->m_commandAndMonitor = a; c_->m_secondCommand = b; \
		c_->m_time0 = HK_RDTSC32(); \
		hkTlsSet(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_SPLIT_LIST(name) HK_TIMER_COMMAND(name)
#define HK_TIMER_END_LIST() HK_TIMER_COMMAND(hkMonitorListEndTag)

#define HK_REAL_MAX 3.40282e+38f      // 0x7f7fffee in this build (not FLT_MAX)

typedef uint32_t hkShapeKey;
#define HK_INVALID_SHAPE_KEY 0xffffffffu

// ---- shape types (names from the string table in hkShapeType_toString) -----------------------------------------------
enum hkShapeType
{
	HK_SHAPE_ALL = -1,
	HK_SHAPE_CONVEX = 1, HK_SHAPE_COLLECTION = 2, HK_SHAPE_BV_TREE = 3, HK_SHAPE_SPHERE = 4, HK_SHAPE_CYLINDER = 5,
	HK_SHAPE_TRIANGLE = 6, HK_SHAPE_BOX = 7, HK_SHAPE_CAPSULE = 8, HK_SHAPE_CONVEX_VERTICES = 9, HK_SHAPE_CONVEX_PIECE = 10,
	HK_SHAPE_MULTI_SPHERE = 11, HK_SHAPE_LIST = 12, HK_SHAPE_CONVEX_LIST = 13, HK_SHAPE_CONVEX_TRANSLATE = 14,
	HK_SHAPE_CONVEX_TRANSFORM = 15, HK_SHAPE_TRIANGLE_COLLECTION = 16, HK_SHAPE_MULTI_RAY = 17, HK_SHAPE_HEIGHT_FIELD = 18,
	HK_SHAPE_SAMPLED_HEIGHT_FIELD = 19, HK_SHAPE_TRI_PATCH = 20, HK_SHAPE_SPHERE_REP = 21, HK_SHAPE_BV = 22,
	HK_SHAPE_PLANE = 23, HK_SHAPE_MOPP = 24, HK_SHAPE_TRANSFORM = 25, HK_SHAPE_PHANTOM_CALLBACK = 26, HK_SHAPE_USER0 = 27,
	HK_SHAPE_USER1 = 28, HK_SHAPE_USER2 = 29
};

// ---- contact points / collision inputs / collectors (copied from s010df100) ------------------------------------------
typedef uint16_t hkContactPointId;
struct hkContactPoint
{
	hkVector4 m_position;
	hkVector4 m_separatingNormal;   // w = distance
	void setFlipped(const hkContactPoint& other);   // 0x010CECF0
};
struct hkProcessCdPoint { hkContactPoint m_contact; uint32_t m_extra[4]; };   // 0x30 bytes

struct hkContactMgr;
struct hkCollisionDispatcher;
struct hkCollisionInput
{
	hkCollisionDispatcher* m_dispatcher;       // +0
	uint32_t m_pad[3];
};
struct hkProcessCollisionInput : hkCollisionInput {};
struct hkLinearCastCollisionInput : hkCollisionInput
{
	hkVector4 m_path;                          // +0x10
	uint32_t m_pad3[4];                        // total 0x30 bytes
};
struct hkCdPoint { hkContactPoint m_contact; const hkCdBody* m_cdBodyA; const hkCdBody* m_cdBodyB; };
struct hkCdPointCollector
{
	virtual void v0();
	virtual void addCdPoint(const hkCdPoint& point);
	float m_earlyOutDistance;                  // +4
};
struct hkCdBodyPairCollector
{
	virtual void v0();
	virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b);   // slot 1 (+4)
	char m_earlyOut;                           // +4
};
struct hkProcessCollisionOutput
{
	hkProcessCdPoint* m_firstFreeContactPoint; // +0
	uint32_t m_pad0[3];
	hkContactPoint m_toiContact;               // +0x10
	hkProcessCdPoint m_contactPoints[256];     // +0x30
	uint32_t m_toiProperties;                  // +0x3030
	float m_toiTime;                           // +0x3034
};

// vtable 0x014a4abc: sets m_earlyOut when a body pair is reported (addCdBodyPair @ 0x010EDDC0, other slice)
struct hkFlagCdBodyPairCollector : hkCdBodyPairCollector
{
	hkFlagCdBodyPairCollector() { m_earlyOut = 0; }
	virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b);
};

// Flip helpers (hkSymmetricAgent): vtables 0x014a43a4 / 0x014a43b4 / 0x014a43ac.
struct hkSymmetricAgentFlipCollector : hkCdPointCollector
{
	hkCdPointCollector& m_original;                                       // +8
	hkSymmetricAgentFlipCollector(hkCdPointCollector& c) : m_original(c) { m_earlyOutDistance = HK_REAL_MAX; }
	virtual void addCdPoint(const hkCdPoint& point);                       // 0x010EBBB0
};
struct hkSymmetricAgentFlipBodyCollector : hkCdBodyPairCollector
{
	hkCdBodyPairCollector& m_original;                                    // +8
	hkSymmetricAgentFlipBodyCollector(hkCdBodyPairCollector& c) : m_original(c) { m_earlyOut = 0; }
	virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b);      // 0x010EBC50
};
struct hkSymmetricAgentFlipCastCollector : hkCdPointCollector
{
	uint32_t m_pad[2];
	hkVector4 m_path;                                                     // +0x10
	hkCdPointCollector* m_original;                                       // +0x20
	hkSymmetricAgentFlipCastCollector(const hkVector4& path, hkCdPointCollector* c) : m_path(path), m_original(c) { m_earlyOutDistance = HK_REAL_MAX; }
	virtual void addCdPoint(const hkCdPoint& point);                       // 0x010EBC00
};

// ---- collision dispatcher (only what the static agent functions touch; 32-bit offsets) -------------------------------
struct hkCollisionAgent;
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
struct hkCollisionDispatcher
{
	char m_pad0[0x190];
	uint8_t m_agent2Types[32][32];             // +0x190: [typeA][typeB] -> agent index
	uint8_t m_agent2TypesPredictive[32][32];   // +0x590
	hkAgentFuncs m_agent2Func[1];              // +0x990 (stride 0x14 in the binary)
	void registerAlternateShapeType(int primaryType, int alternateType);   // 0x010CD630
};

// ---- collision agents ------------------------------------------------------------------------------------------------
struct hkCollisionAgent : hkReferencedObject
{
	hkContactMgr* m_contactMgr;                // +8
	virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);                                  // 2 (+8)
	virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);                                    // 3
	virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);           // 4
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);                       // 5
};

// hkBvShape: the bounding-volume shape at +0xc and the real child at +0x10.
struct hkBvShape : hkShape
{
	const hkShape* m_boundingVolumeShape;      // +0xc
	const hkShape* m_childShape;               // +0x10
};

// hkBvAgent, 0x14 bytes: hkCollisionAgent + the agent between the BV shape and body B + the agent for the child.
struct hkBvAgent : hkCollisionAgent
{
	hkCollisionAgent* m_bvAgent;               // +0xc
	hkCollisionAgent* m_childAgent;            // +0x10
	hkBvAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010E6C00
	virtual void getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector);          // 0x010E7750
	virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);                                          // 0x010E7390
	virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);                 // 0x010E6F90
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);                             // 0x010E6D90
	static void staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector);       // 0x010E7590
	static void staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector);     // 0x010E7830
	static hkCollisionAgent* createShapeBvAgent(const hkCdBody& A, const hkCdBody& B, const hkCollisionInput& input, hkContactMgr* mgr);                   // 0x010E7CA0
};

// hkSymmetricAgent<hkBvAgent>: vtable 0x014A4F1C, same size as hkBvAgent.
struct hkSymmetricAgent_hkBvAgent : hkBvAgent
{
	hkSymmetricAgent_hkBvAgent(const hkCdBody& A, const hkCdBody& B, const hkCollisionInput& input, hkContactMgr* mgr)
		: hkBvAgent(B, A, input, mgr) {}
	virtual void getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector);          // 0x010E7930
	virtual void getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector);            // 0x010E79B0
	virtual void linearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input, hkCdPointCollector& collector,
	                        hkCdPointCollector* startCollector);                                                                                           // 0x010E7BB0
	virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkProcessCollisionInput& input, hkProcessCollisionOutput& result);  // 0x010E7B30
};

// ---- shape collection ------------------------------------------------------------------------------------------------
// hkShapeBuffer: 512 bytes of scratch for getChildShape (stack allocated, 16-byte aligned frame).
#if defined(_MSC_VER)
__declspec(align(16)) struct hkShapeBuffer { uint32_t m_storage[128]; };
#else
struct __attribute__((aligned(16))) hkShapeBuffer { uint32_t m_storage[128]; };
#endif

struct hkShapeCollection;
// Ray filter: slot 0 isCollisionEnabled returns hkBool through a hidden pointer (hkBool is non-POD here).
struct hkRayShapeCollectionFilter
{
	virtual hkBool isCollisionEnabled(const hkShapeRayCastInput& input, const hkShapeCollection& collection, hkShapeKey key) const = 0;
};

struct hkShapeCollection : hkShape
{
	char m_disableWelding;                     // +0xc
	hkShapeCollection();                       // 0x010E7FD0
	virtual void calcStatistics(hkStatisticsCollector* c) const;                                                   // 1, 0x010E7FB0
	virtual int getType() const { return HK_SHAPE_COLLECTION; }                                                    // 2 (0x00DD3D10 returns the constant)
	virtual void getAabb(const hkTransform& localToWorld, float tolerance, hkAabb& out) const;                      // 3, 0x010E8190
	virtual float getMaximumProjection(const hkVector4& direction) const;                                          // 4, 0x010E8390
	virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const;                  // 5, 0x010E8000
	virtual void castRayWithCollector(const hkShapeRayCastInput& input, const hkCdBody& cdBody,
	                                  hkRayHitCollector& collector) const;                                         // 6, 0x010E84A0
	virtual int getNumChildShapes() const;                                                                         // 7, 0x010E7F80
	virtual hkShapeKey getFirstKey() const = 0;                                                                    // 8 (pure)
	virtual hkShapeKey getNextKey(hkShapeKey oldKey) const = 0;                                                    // 9 (pure)
	virtual const hkShape* getChildShape(hkShapeKey key, hkShapeBuffer& buffer) const = 0;                         // 10 (pure)
};

struct hkBvTreeShape : hkShape
{
	const hkShapeCollection* m_child;          // +0xc
	virtual void calcStatistics(hkStatisticsCollector* c) const;                                                   // 1, 0x010E8630
};

// vtable 0x014A5258: collects the closest hit of castRayWithCollector into the caller's output (addRayHit elsewhere).
struct hkSingleShapeRayCastCollector : hkRayHitCollector
{
	char m_hit;                                // +8
	hkShapeRayCastOutput* m_output;            // +0xc
	virtual void addRayHit(const hkCdBody& cdBody, const hkShapeRayCastOutput& hitInfo);
};

// hkSampledHeightFieldShape: only slot 6 (castRayWithCollector) is used here.
struct hkSampledHeightFieldShape : hkShape
{
	virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const;                  // 5, 0x010E8680
};

// =====================================================================================================================

static inline void hkCdBody_set(hkCdBody& b, const hkShape* shape, uint32_t key, const void* motion, const hkCdBody* parent)
{
	b.m_shape = shape;
	b.m_shapeKey = key;
	b.m_motion = motion;
	b.m_parent = parent;
}

// @ 0x010e7590
void hkBvAgent::staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector)
{
	HK_TIMER_BEGIN_LIST("LthkBvAgent", "checkBvShape");

	const hkBvShape* bvShape = (const hkBvShape*)bodyA.m_shape;
	hkCdBody newBodyA;
	hkCdBody_set(newBodyA, bvShape->m_boundingVolumeShape, bodyA.m_shapeKey, bodyA.m_motion, &bodyA);

	int typeA = newBodyA.m_shape->getType();
	int typeB = bodyB.m_shape->getType();
	const hkCollisionDispatcher* d = input.m_dispatcher;
	hkFlagCdBodyPairCollector flagCollector;
	d->m_agent2Func[d->m_agent2Types[typeA][typeB]].m_getPenetrationsFunc(newBodyA, bodyB, input, flagCollector);

	if (flagCollector.m_earlyOut)
	{
		HK_TIMER_SPLIT_LIST("Stchild");
		hkCdBody childBodyA;
		hkCdBody_set(childBodyA, bvShape->m_childShape, bodyA.m_shapeKey, newBodyA.m_motion, newBodyA.m_parent);
		int childType = childBodyA.m_shape->getType();
		d->m_agent2Func[d->m_agent2Types[childType][typeB]].m_getClosestPointFunc(childBodyA, bodyB, input, collector);
	}
	HK_TIMER_END_LIST();
}

// @ 0x010e7750
void hkBvAgent::getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
	HK_TIMER_BEGIN("TthkBvAgent");
	const hkBvShape* bvShape = (const hkBvShape*)bodyA.m_shape;
	hkCdBody newBodyA;
	hkCdBody_set(newBodyA, bvShape->m_boundingVolumeShape, bodyA.m_shapeKey, bodyA.m_motion, &bodyA);
	m_bvAgent->getPenetrations(newBodyA, bodyB, input, collector);
	HK_TIMER_END();
}

// @ 0x010e7830
void hkBvAgent::staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
	HK_TIMER_BEGIN("TthkBvAgent");
	const hkBvShape* bvShape = (const hkBvShape*)bodyA.m_shape;
	hkCdBody newBodyA;
	hkCdBody_set(newBodyA, bvShape->m_boundingVolumeShape, bodyA.m_shapeKey, bodyA.m_motion, &bodyA);
	int typeA = newBodyA.m_shape->getType();
	int typeB = bodyB.m_shape->getType();
	const hkCollisionDispatcher* d = input.m_dispatcher;
	d->m_agent2Func[d->m_agent2Types[typeA][typeB]].m_getPenetrationsFunc(newBodyA, bodyB, input, collector);
	HK_TIMER_END();
}

// @ 0x010e7930  hkSymmetricAgent<hkBvAgent>::getPenetrations
void hkSymmetricAgent_hkBvAgent::getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
	hkSymmetricAgentFlipBodyCollector flip(collector);
	hkBvAgent::getPenetrations(bodyB, bodyA, input, flip);
}

// @ 0x010e79b0  hkSymmetricAgent<hkBvAgent>::getClosestPoints
void hkSymmetricAgent_hkBvAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector)
{
	hkSymmetricAgentFlipCollector flip(collector);
	hkBvAgent::getClosestPoints(bodyB, bodyA, input, flip);
}

// @ 0x010e7b30  hkSymmetricAgent<hkBvAgent>::processCollision
void hkSymmetricAgent_hkBvAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkProcessCollisionInput& input, hkProcessCollisionOutput& result)
{
	hkProcessCdPoint* pp = result.m_firstFreeContactPoint;
	float oldToi = result.m_toiTime;
	hkBvAgent::processCollision(bodyB, bodyA, input, result);
	for (; pp < result.m_firstFreeContactPoint; pp++)
		pp->m_contact.setFlipped(pp->m_contact);
	// fucompp + test ah,0x44 / jnp: flip when oldToi != toiTime (a NaN compares unordered and flips too)
	if (oldToi != result.m_toiTime)
	{
		result.m_toiContact.m_separatingNormal.x = -result.m_toiContact.m_separatingNormal.x;
		result.m_toiContact.m_separatingNormal.y = -result.m_toiContact.m_separatingNormal.y;
		result.m_toiContact.m_separatingNormal.z = -result.m_toiContact.m_separatingNormal.z;
	}
}

// @ 0x010e7bb0  hkSymmetricAgent<hkBvAgent>::linearCast
void hkSymmetricAgent_hkBvAgent::linearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input, hkCdPointCollector& collector, hkCdPointCollector* startCollector)
{
	hkLinearCastCollisionInput flippedInput = input;
	flippedInput.m_path.x = -input.m_path.x;           // setNeg4
	flippedInput.m_path.y = -input.m_path.y;
	flippedInput.m_path.z = -input.m_path.z;
	flippedInput.m_path.w = -input.m_path.w;
	hkSymmetricAgentFlipCastCollector flip(input.m_path, &collector);
	if (startCollector)
	{
		hkSymmetricAgentFlipCastCollector startFlip(input.m_path, startCollector);
		hkBvAgent::linearCast(bodyB, bodyA, flippedInput, flip, &startFlip);
	}
	else
	{
		hkBvAgent::linearCast(bodyB, bodyA, flippedInput, flip, 0);
	}
}

// @ 0x010e7ca0
hkCollisionAgent* hkBvAgent::createShapeBvAgent(const hkCdBody& A, const hkCdBody& B, const hkCollisionInput& input, hkContactMgr* mgr)
{
	// HK_DECLARE_CLASS_ALLOCATOR (0x14 bytes, memory class 0x1c), then the swapped-argument constructor
	return new hkSymmetricAgent_hkBvAgent(A, B, input, mgr);
}

// @ 0x010e7d70  (name from the 6.x hkAgentRegisterUtil; a cdecl function taking the dispatcher)
struct hkAgentRegisterUtil { static void registerAlternateShapeTypes(hkCollisionDispatcher* dispatcher); };
void hkAgentRegisterUtil::registerAlternateShapeTypes(hkCollisionDispatcher* dispatcher)
{
	dispatcher->registerAlternateShapeType(HK_SHAPE_SPHERE, HK_SHAPE_CONVEX);
	dispatcher->registerAlternateShapeType(HK_SHAPE_TRIANGLE, HK_SHAPE_CONVEX);
	dispatcher->registerAlternateShapeType(HK_SHAPE_BOX, HK_SHAPE_CONVEX);
	dispatcher->registerAlternateShapeType(HK_SHAPE_CAPSULE, HK_SHAPE_CONVEX);
	dispatcher->registerAlternateShapeType(HK_SHAPE_CYLINDER, HK_SHAPE_CONVEX);
	dispatcher->registerAlternateShapeType(HK_SHAPE_CONVEX_VERTICES, HK_SHAPE_CONVEX);
	dispatcher->registerAlternateShapeType(HK_SHAPE_CONVEX_TRANSLATE, HK_SHAPE_CONVEX);
	dispatcher->registerAlternateShapeType(HK_SHAPE_CONVEX_TRANSFORM, HK_SHAPE_CONVEX);
	dispatcher->registerAlternateShapeType(HK_SHAPE_CONVEX_PIECE, HK_SHAPE_CONVEX);
	dispatcher->registerAlternateShapeType(HK_SHAPE_TRIANGLE_COLLECTION, HK_SHAPE_COLLECTION);
	dispatcher->registerAlternateShapeType(HK_SHAPE_LIST, HK_SHAPE_COLLECTION);
	dispatcher->registerAlternateShapeType(HK_SHAPE_CONVEX_LIST, HK_SHAPE_LIST);
	dispatcher->registerAlternateShapeType(HK_SHAPE_MOPP, HK_SHAPE_BV_TREE);
	dispatcher->registerAlternateShapeType(HK_SHAPE_CONVEX, HK_SHAPE_SPHERE_REP);
	dispatcher->registerAlternateShapeType(HK_SHAPE_PLANE, HK_SHAPE_HEIGHT_FIELD);
	dispatcher->registerAlternateShapeType(HK_SHAPE_SAMPLED_HEIGHT_FIELD, HK_SHAPE_HEIGHT_FIELD);
}

// @ 0x010e7e30  (name inferred) hkShapeType -> debug string
const char* hkShapeType_toString(int type)
{
	switch (type)
	{
	case HK_SHAPE_ALL: return "HK_SHAPE_ALL";
	case HK_SHAPE_CONVEX: return "HK_SHAPE_CONVEX";
	case HK_SHAPE_COLLECTION: return "HK_SHAPE_COLLECTION";
	case HK_SHAPE_BV_TREE: return "HK_SHAPE_BV_TREE";
	case HK_SHAPE_SPHERE: return "HK_SHAPE_SPHERE";
	case HK_SHAPE_CYLINDER: return "HK_SHAPE_CYLINDER";
	case HK_SHAPE_TRIANGLE: return "HK_SHAPE_TRIANGLE";
	case HK_SHAPE_BOX: return "HK_SHAPE_BOX";
	case HK_SHAPE_CAPSULE: return "HK_SHAPE_CAPSULE";
	case HK_SHAPE_CONVEX_VERTICES: return "HK_SHAPE_CONVEX_VERTICES";
	case HK_SHAPE_CONVEX_PIECE: return "HK_SHAPE_CONVEX_PIECE";
	case HK_SHAPE_MULTI_SPHERE: return "HK_SHAPE_MULTI_SPHERE";
	case HK_SHAPE_LIST: return "HK_SHAPE_LIST";
	case HK_SHAPE_CONVEX_LIST: return "HK_SHAPE_CONVEX_LIST";
	case HK_SHAPE_CONVEX_TRANSLATE: return "HK_SHAPE_CONVEX_TRANSLATE";
	case HK_SHAPE_CONVEX_TRANSFORM: return "HK_SHAPE_CONVEX_TRANSFORM";
	case HK_SHAPE_TRIANGLE_COLLECTION: return "HK_SHAPE_TRIANGLE_COLLECTION";
	case HK_SHAPE_MULTI_RAY: return "HK_SHAPE_MULTI_RAY";
	case HK_SHAPE_HEIGHT_FIELD: return "HK_SHAPE_HEIGHT_FIELD";
	case HK_SHAPE_SAMPLED_HEIGHT_FIELD: return "HK_SHAPE_SAMPLED_HEIGHT_FIELD";
	case HK_SHAPE_TRI_PATCH: return "HK_SHAPE_TRI_PATCH";
	case HK_SHAPE_SPHERE_REP: return "HK_SHAPE_SPHERE_REP";
	case HK_SHAPE_BV: return "HK_SHAPE_BV";
	case HK_SHAPE_PLANE: return "HK_SHAPE_PLANE";
	case HK_SHAPE_MOPP: return "HK_SHAPE_MOPP";
	case HK_SHAPE_TRANSFORM: return "HK_SHAPE_TRANSFORM";
	case HK_SHAPE_PHANTOM_CALLBACK: return "HK_SHAPE_PHANTOM_CALLBACK";
	case HK_SHAPE_USER0: return "HK_SHAPE_USER0";
	case HK_SHAPE_USER1: return "HK_SHAPE_USER1";
	case HK_SHAPE_USER2: return "HK_SHAPE_USER2";
	default: return "unknown";
	}
}

// @ 0x010e7f80
int hkShapeCollection::getNumChildShapes() const
{
	int n = 0;
	for (hkShapeKey key = getFirstKey(); key != HK_INVALID_SHAPE_KEY; key = getNextKey(key))
		++n;
	return n;
}

// @ 0x010e7fb0
void hkShapeCollection::calcStatistics(hkStatisticsCollector* c) const
{
	c->beginObject("Collection", 1, this);
	c->endObject();
}

// @ 0x010e7fd0
hkShapeCollection::hkShapeCollection()
{
	// hkReferencedObject: m_referenceCount = 1; hkShape: m_userData = 0 (both in the base constructors)
	m_disableWelding = 0;
}

// @ 0x010e8000
hkBool hkShapeCollection::castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const
{
	HK_TIMER_BEGIN("TtrcShpCollect");
	bool hit = false;
	hkShapeBuffer buffer;
	const hkRayShapeCollectionFilter* filter = (const hkRayShapeCollectionFilter*)input.m_rayShapeCollectionFilter;
	if (filter == 0)
	{
		for (hkShapeKey key = getFirstKey(); key != HK_INVALID_SHAPE_KEY; key = getNextKey(key))
		{
			const hkShape* child = getChildShape(key, buffer);
			if (child->castRay(input, output))
			{
				hit = true;
				output.m_shapeKey = key;
			}
		}
	}
	else
	{
		for (hkShapeKey key = getFirstKey(); key != HK_INVALID_SHAPE_KEY; key = getNextKey(key))
		{
			if (filter->isCollisionEnabled(input, *this, key))
			{
				const hkShape* child = getChildShape(key, buffer);
				if (child->castRay(input, output))
				{
					hit = true;
					output.m_shapeKey = key;
				}
			}
		}
	}
	HK_TIMER_END();
	return hkBool(hit);
}

// @ 0x010e8190
void hkShapeCollection::getAabb(const hkTransform& localToWorld, float tolerance, hkAabb& out) const
{
	HK_TIMER_BEGIN("TthkShapeCollection::getAabb");
	out.m_min.x = 0.0f; out.m_min.y = 0.0f; out.m_min.z = 0.0f; out.m_min.w = 0.0f;
	out.m_max.x = 0.0f; out.m_max.y = 0.0f; out.m_max.z = 0.0f; out.m_max.w = 0.0f;
	hkShapeKey key = getFirstKey();
	if (key != HK_INVALID_SHAPE_KEY)
	{
		hkShapeBuffer buffer;
		// the first child is written straight into `out` ...
		getChildShape(key, buffer)->getAabb(localToWorld, tolerance, out);
		// ... and then visited again by the loop below (the binary does the first key twice)
		do
		{
			hkAabb childAabb;
			getChildShape(key, buffer)->getAabb(localToWorld, tolerance, childAabb);
			// hkMath min / max merges: fcomp + test ah,5 / jp  =>  (a < b) ? a : b ;  test ah,0x41 / jne  =>  (a > b) ? a : b
			out.m_min.x = (out.m_min.x < childAabb.m_min.x) ? out.m_min.x : childAabb.m_min.x;
			out.m_min.y = (out.m_min.y < childAabb.m_min.y) ? out.m_min.y : childAabb.m_min.y;
			out.m_min.z = (out.m_min.z < childAabb.m_min.z) ? out.m_min.z : childAabb.m_min.z;
			out.m_min.w = (out.m_min.w < childAabb.m_min.w) ? out.m_min.w : childAabb.m_min.w;
			out.m_max.x = (out.m_max.x > childAabb.m_max.x) ? out.m_max.x : childAabb.m_max.x;
			out.m_max.y = (out.m_max.y > childAabb.m_max.y) ? out.m_max.y : childAabb.m_max.y;
			out.m_max.z = (out.m_max.z > childAabb.m_max.z) ? out.m_max.z : childAabb.m_max.z;
			out.m_max.w = (out.m_max.w > childAabb.m_max.w) ? out.m_max.w : childAabb.m_max.w;
			key = getNextKey(key);
		} while (key != HK_INVALID_SHAPE_KEY);
	}
	HK_TIMER_END();
}

// @ 0x010e8390
float hkShapeCollection::getMaximumProjection(const hkVector4& direction) const
{
	HK_TIMER_BEGIN("TthkShapeCollection::getMaximumProjection");
	float maxProjection = -3.40282e+38f;      // 0xff7fffee
	hkShapeBuffer buffer;
	for (hkShapeKey key = getFirstKey(); key != HK_INVALID_SHAPE_KEY; key = getNextKey(key))
	{
		// X87-PRECISION: the child's result arrives unrounded in st(0); the compare uses it before the float store.
		hkX87Real projection = getChildShape(key, buffer)->getMaximumProjection(direction);
		if (!(maxProjection > projection))     // fcomp / test ah,0x41 / je  (NaN takes the store)
			maxProjection = (float)projection;
	}
	HK_TIMER_END();
	return maxProjection;
}

// @ 0x010e84a0
void hkShapeCollection::castRayWithCollector(const hkShapeRayCastInput& input, const hkCdBody& cdBody, hkRayHitCollector& collector) const
{
	HK_TIMER_BEGIN("TtrcShpCollect");
	hkShapeBuffer buffer;
	const hkRayShapeCollectionFilter* filter = (const hkRayShapeCollectionFilter*)input.m_rayShapeCollectionFilter;
	if (filter == 0)
	{
		for (hkShapeKey key = getFirstKey(); key != HK_INVALID_SHAPE_KEY; key = getNextKey(key))
		{
			const hkShape* child = getChildShape(key, buffer);
			hkCdBody childBody;
			hkCdBody_set(childBody, child, key, cdBody.m_motion, &cdBody);
			child->castRayWithCollector(input, childBody, collector);
		}
	}
	else
	{
		for (hkShapeKey key = getFirstKey(); key != HK_INVALID_SHAPE_KEY; key = getNextKey(key))
		{
			if (filter->isCollisionEnabled(input, *this, key))
			{
				const hkShape* child = getChildShape(key, buffer);
				hkCdBody childBody;
				hkCdBody_set(childBody, child, key, cdBody.m_motion, &cdBody);
				child->castRayWithCollector(input, childBody, collector);
			}
		}
	}
	HK_TIMER_END();
}

// @ 0x010e8630
void hkBvTreeShape::calcStatistics(hkStatisticsCollector* c) const
{
	c->beginObject("BvTreeShape", 1, this);
	c->addReferencedObject("Collection", 1, m_child);
	c->endObject();
}

// @ 0x010e8680
hkBool hkSampledHeightFieldShape::castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const
{
	hkSingleShapeRayCastCollector collector;
	collector.m_earlyOutHitFraction = output.m_hitFraction;
	collector.m_hit = 0;
	collector.m_output = &output;
	castRayWithCollector(input, *(const hkCdBody*)0, collector);   // cdBody argument is a null reference in the binary
	return hkBool(collector.m_hit != 0);
}
