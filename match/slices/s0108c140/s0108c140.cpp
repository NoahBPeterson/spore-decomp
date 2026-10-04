// Havok 3.1.0 dynamics, part: hkSimpleShapePhantom, hkResponseModifier::setInvMassScalingForContact,
// hkMovingSurfaceConstraintData, hkSimpleContactConstraintData destructor body, hkRigidBody::getPointVelocity,
// hkContactPointConfirmedEvent::getContactPointId, hkSimpleConstraintContactMgr::reserveContactPoints
// (0x0108C140..0x0108D0A0). Equivalent portable source. Offsets are the 32-bit ones; layouts come from the dev PDB
// (tools/pdb_type.py) where available and are confirmed against the disassembly.
#include "../s010eb310/hk31_math.h"

#ifdef _WIN32
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);
#endif

// ---- shared class stubs ---------------------------------------------------------------------------------------
struct hkWorld;
struct hkCollidable;
struct hkPhantom;

struct hkTypedBroadPhaseHandle
{
	uint32_t m_id;                    // +0
	char m_type;                      // +4
	char m_ownerOffset;               // +5
	uint16_t m_objectQualityType;     // +6
	uint32_t m_collisionFilterInfo;   // +8
};
struct hkCollidable : hkCdBody       // size 0x24
{
	int m_ownerOffset;                      // +0x10
	hkTypedBroadPhaseHandle m_broadPhaseHandle;   // +0x14
	hkReal m_allowedPenetrationDepth;       // +0x20
};
struct hkLinkedCollidable : hkCollidable   // size 0x30
{
	hkArray<int> m_collisionEntries;        // +0x24 (element type not needed here)
};

enum hkCollidableAccept { HK_COLLIDABLE_ACCEPT = 0, HK_COLLIDABLE_REJECT = 1 };
struct hkCollidableRemovedEvent
{
	hkPhantom* m_phantom;                   // +0
	const hkCollidable* m_collidable;       // +4
	hkBool m_collidableRemoved;             // +8
};
struct hkPhantomOverlapListener
{
	virtual void collidableAddedCallback(void* event);                              // 0
	virtual void collidableRemovedCallback(const hkCollidableRemovedEvent& event);  // 1
};
struct hkStatisticsCollector
{
	virtual void sc0();
	virtual void beginObject(const char* name, int memClass, const void* object);                     // 1
	virtual void addArray(const char* name, int memClass, const void* data, int usedBytes, int allocBytes);   // 2
	virtual void sc3(); virtual void sc4(); virtual void sc5();
	virtual void endObject();                                                                        // 6
};

struct hkFinishLoadedObjectFlag { int m_finishing; };   // passed by value (one stack dword)

struct hkWorldObject : hkReferencedObject    // size 0x58
{
	hkWorld* m_world;                       // +8
	void* m_userData;                       // +0xc
	char* m_name;                           // +0x10
	char m_multithreadLock[8];              // +0x14 hkMultiThreadLock
	hkLinkedCollidable m_collidable;        // +0x1c
	hkArray<int> m_properties;              // +0x4c
	hkWorldObject(hkFinishLoadedObjectFlag f);          // 0x010826E0 (the "hkWorldObject_finishLoaded" function, thiscall)
	hkWorldObject() {}
	void copyProperties(const hkWorldObject* other);   // 0x01087CA0
};
struct hkPhantom : hkWorldObject             // size 0x70
{
	hkArray<hkPhantomOverlapListener*> m_overlapListeners;   // +0x58
	hkArray<void*> m_phantomListeners;                       // +0x64
	hkPhantom() {}
	hkPhantom(hkFinishLoadedObjectFlag f) : hkWorldObject(f)
	{
		m_overlapListeners.m_data = 0; m_overlapListeners.m_size = 0; m_overlapListeners.m_capacityAndFlags = (int)0x80000000;
		m_phantomListeners.m_data = 0; m_phantomListeners.m_size = 0; m_phantomListeners.m_capacityAndFlags = (int)0x80000000;
	}
	virtual ~hkPhantom();                                                           // 0x0108E550
	hkCollidableAccept fireCollidableAdded(const hkCollidable* c);                  // 0x0108C0B0
	void fireCollidableRemoved(const hkCollidable* c, hkBool collidableRemoved);    // 0x0108C100
	void updateBroadPhase(const hkAabb& aabb);                                      // 0x0108E680
	void calcContentStatistics(hkStatisticsCollector* c) const;                     // 0x0108E4E0
};
struct hkShapePhantom : hkPhantom            // size 0x120
{
	hkMotionState m_motionState;            // +0x70
	hkShapePhantom(const hkShape* shape, const hkTransform& transform);   // 0x0108DD40
	hkShapePhantom(hkFinishLoadedObjectFlag f) : hkPhantom(f) {}
	virtual void deallocateInternalArrays();                              // 0x0108DB40 (base implementation)
};
struct hkLinearCastInput
{
	hkVector4 m_to;                         // +0
	hkReal m_maxExtraPenetration;           // +0x10
	hkReal m_startPointTolerance;           // +0x14
};

struct hkCriticalSection
{
	char m_cs[24];            // CRITICAL_SECTION
	hkUint64 m_owner;         // +0x18: thread id while locked, -1 otherwise
	void enter();             // 0x0107F820
	void leave()
	{
#ifdef _WIN32
		m_owner = (hkUint64)-1;
		LeaveCriticalSection(m_cs);
#endif
	}
};

// The world as far as these functions see it (offsets from the dev PDB; 32-bit pointer layout).
struct hkWorld : hkReferencedObject
{
	char m_pad08[0x78 - 8];                        // +0x8..+0x77 (simulation .. broadphase listeners)
	hkProcessCollisionInput* m_collisionInput;     // +0x78
	void* m_collisionFilter;                       // +0x7c
	hkCollisionDispatcher* m_collisionDispatcher;  // +0x80
	char m_pad84[0xac - 0x84];
	hkCriticalSection* m_modifyConstraintCriticalSection;   // +0xac
};

// ---- hkSimpleShapePhantom ---------------------------------------------------------------------------------------
struct hkSimpleShapePhantom : hkShapePhantom    // size 0x130
{
	struct hkCollisionDetail { hkCollidable* m_collidable; };
	hkArray<hkCollisionDetail> m_collisionDetails;   // +0x120

	hkSimpleShapePhantom(const hkShape* shape, const hkTransform& transform, hkUint32 collisionFilterInfo);   // 0x0108C750
	hkSimpleShapePhantom(hkFinishLoadedObjectFlag f) : hkShapePhantom(f)
	{
		m_collisionDetails.m_data = 0; m_collisionDetails.m_size = 0; m_collisionDetails.m_capacityAndFlags = (int)0x80000000;
	}
	virtual ~hkSimpleShapePhantom();                                                         // 0x0108C790 / scalar deleting 0x0108C9D0
	virtual void calcStatistics(hkStatisticsCollector* c) const;                              // 0x0108C670
	virtual void addOverlappingCollidable(hkCollidable* c);                                   // 0x0108C620
	virtual hkBool isOverlappingCollidableAdded(hkCollidable* c);                             // 0x0108C550
	virtual void removeOverlappingCollidable(hkCollidable* c);                                // 0x0108C590
	virtual hkSimpleShapePhantom* clone() const;                                              // 0x0108C7E0 (name guessed from the copy logic)
	virtual void deallocateInternalArrays();                                                  // 0x0108C950
	virtual void setPositionAndLinearCast(const hkVector4& position, const hkLinearCastInput& input,
	                                      hkCdPointCollector& castCollector, hkCdPointCollector* startCollector);   // 0x0108C140
	virtual void getClosestPoints(hkCdPointCollector& collector);                            // 0x0108C430
	virtual void getPenetrations(hkCdBodyPairCollector& collector);                          // 0x0108C4C0

	static void finishLoadedObject(void* p, int finishing);                                  // 0x0108C700 (name guessed)
	static void* operator new(size_t n)
	{
		void* p = hkMemory::s_instance->allocateChunk((int)n, HK_MEMORY_CLASS_PHANTOM_T);
		((hkReferencedObject*)p)->m_memSizeAndFlags = (hkInt16)n;
		return p;
	}
	static void* operator new(size_t, void* p) { return p; }
	static void operator delete(void*, void*) {}
	static void operator delete(void* p)
	{
		hkMemory::s_instance->deallocateChunk(p, (uint16_t)((hkReferencedObject*)p)->m_memSizeAndFlags, HK_MEMORY_CLASS_PHANTOM_T);
	}
};

// @ 0x0108c140
void hkSimpleShapePhantom::setPositionAndLinearCast(const hkVector4& position, const hkLinearCastInput& input,
                                                    hkCdPointCollector& castCollector, hkCdPointCollector* startCollector)
{
	// Move the phantom to the start position (translation of the motion state transform).
	m_motionState.m_transform.m_trans = position;

	// Broad phase AABB of the swept shape: AABB at the start position, grown by the movement vector.
	hkAabb aabb;
	// X87-PRECISION: tolerance * 0.5 and the add stay on the x87 stack until stored to the float argument.
	hkReal tolerance = (float)((hkX87Real)m_world->m_collisionInput->m_tolerance * 0.5f + input.m_startPointTolerance);
	m_collidable.m_shape->getAabb(m_motionState.m_transform, tolerance, aabb);

	hkVector4 d;
	d.x = input.m_to.x - position.x;
	d.y = input.m_to.y - position.y;
	d.z = input.m_to.z - position.z;
	d.w = input.m_to.w - position.w;
	// per component min(0, d) (grows the min) and max(0, d) (grows the max); a compare with NaN picks d
	float lox = (0.0f < d.x) ? 0.0f : d.x;
	float loy = (0.0f < d.y) ? 0.0f : d.y;
	float loz = (0.0f < d.z) ? 0.0f : d.z;
	float low = (0.0f < d.w) ? 0.0f : d.w;
	float hix = (0.0f > d.x) ? 0.0f : d.x;
	float hiy = (0.0f > d.y) ? 0.0f : d.y;
	float hiz = (0.0f > d.z) ? 0.0f : d.z;
	float hiw = (0.0f > d.w) ? 0.0f : d.w;
	aabb.m_min.x = lox + aabb.m_min.x;
	aabb.m_min.y = aabb.m_min.y + loy;
	aabb.m_min.z = aabb.m_min.z + loz;
	aabb.m_min.w = aabb.m_min.w + low;
	aabb.m_max.x = aabb.m_max.x + hix;
	aabb.m_max.y = aabb.m_max.y + hiy;
	aabb.m_max.z = aabb.m_max.z + hiz;
	aabb.m_max.w = aabb.m_max.w + hiw;
	updateBroadPhase(aabb);

	// Linear cast input for the agents: the world's collision input with the tolerance replaced.
	hkLinearCastCollisionInput lci;
	const hkProcessCollisionInput* worldInput = m_world->m_collisionInput;
	lci.m_dispatcher = worldInput->m_dispatcher;
	lci.m_filter = worldInput->m_filter;
	lci.m_tolerance = worldInput->m_tolerance;
	lci.m_createPredictiveAgents = worldInput->m_createPredictiveAgents;
	lci.m_tolerance = input.m_startPointTolerance;
	lci.m_path = d;
	lci.m_maxExtraPenetration = input.m_maxExtraPenetration;
	// inline fsqrt of ((z*z + y*y) + x*x)
	lci.m_cachedPathLength = (float)sqrt(((hkX87Real)d.z * d.z + (hkX87Real)d.y * d.y) + (hkX87Real)d.x * d.x);
	lci.m_config = worldInput->m_config;
	hkCollisionDispatcher* dispatcher = m_world->m_collisionDispatcher;

	for (int i = m_collisionDetails.m_size - 1; i >= 0; --i)
	{
		hkCollidable* other = m_collisionDetails.m_data[i].m_collidable;
		int typeOther = other->m_shape->getType();
		int typeThis = m_collidable.m_shape->getType();
		uint8_t agentType = dispatcher->m_agent2TypesDiscrete[typeThis][typeOther];
		dispatcher->m_agent2Func[agentType].m_linearCastFunc(m_collidable, *other, lci, castCollector, startCollector);
	}
}

// @ 0x0108c430
void hkSimpleShapePhantom::getClosestPoints(hkCdPointCollector& collector)
{
	hkProcessCollisionInput* input = m_world->m_collisionInput;
	hkCollisionDispatcher* dispatcher = input->m_dispatcher;
	for (int i = m_collisionDetails.m_size - 1; i >= 0; --i)
	{
		hkCollidable* other = m_collisionDetails.m_data[i].m_collidable;
		int typeOther = other->m_shape->getType();
		int typeThis = m_collidable.m_shape->getType();
		uint8_t agentType = dispatcher->m_agent2TypesDiscrete[typeThis][typeOther];
		dispatcher->m_agent2Func[agentType].m_getClosestPointFunc(m_collidable, *other, *input, collector);
	}
}

// @ 0x0108c4c0
void hkSimpleShapePhantom::getPenetrations(hkCdBodyPairCollector& collector)
{
	hkProcessCollisionInput* input = m_world->m_collisionInput;
	hkCollisionDispatcher* dispatcher = input->m_dispatcher;
	for (int i = m_collisionDetails.m_size - 1; i >= 0; --i)
	{
		hkCollidable* other = m_collisionDetails.m_data[i].m_collidable;
		int typeOther = other->m_shape->getType();
		int typeThis = m_collidable.m_shape->getType();
		uint8_t agentType = dispatcher->m_agent2TypesDiscrete[typeThis][typeOther];
		dispatcher->m_agent2Func[agentType].m_getPenetrationsFunc(m_collidable, *other, *input, collector);
		if (collector.m_earlyOut)
			return;
	}
}

// @ 0x0108c550
hkBool hkSimpleShapePhantom::isOverlappingCollidableAdded(hkCollidable* c)
{
	for (int i = 0; i < m_collisionDetails.m_size; ++i)
	{
		if (m_collisionDetails.m_data[i].m_collidable == c)
			return hkBool(true);
	}
	return hkBool(false);
}

// @ 0x0108c590
void hkSimpleShapePhantom::removeOverlappingCollidable(hkCollidable* c)
{
	if (c->m_shape != 0)
	{
		for (int i = m_collisionDetails.m_size - 1; i >= 0; --i)
		{
			if (m_collisionDetails.m_data[i].m_collidable == c)
			{
				fireCollidableRemoved(c, hkBool(true));
				int last = m_collisionDetails.m_size - 1;
				m_collisionDetails.m_size = last;
				m_collisionDetails.m_data[i] = m_collisionDetails.m_data[last];
				return;
			}
		}
		// Not found: tell the overlap listeners the collidable went away without being tracked.
		hkCollidableRemovedEvent event;
		event.m_phantom = this;
		event.m_collidable = c;
		event.m_collidableRemoved = hkBool(false);
		for (int i = m_overlapListeners.m_size - 1; i >= 0; --i)
		{
			hkPhantomOverlapListener* l = m_overlapListeners.m_data[i];
			if (l != 0)
				l->collidableRemovedCallback(event);
		}
	}
}

// @ 0x0108c620
void hkSimpleShapePhantom::addOverlappingCollidable(hkCollidable* c)
{
	if (c->m_shape != 0)
	{
		if (fireCollidableAdded(c) == HK_COLLIDABLE_ACCEPT)
		{
			hkCollisionDetail detail;
			detail.m_collidable = c;
			m_collisionDetails.pushBack(detail);
		}
	}
}

// @ 0x0108c670
void hkSimpleShapePhantom::calcStatistics(hkStatisticsCollector* c) const
{
	c->beginObject("SimplePhantm", 2, this);
	calcContentStatistics(c);
	if (m_collisionDetails.m_capacityAndFlags >= 0)
	{
		c->addArray("OverlapPtr", 8, m_collisionDetails.m_data, m_collisionDetails.m_size << 2,
		            (m_collisionDetails.m_capacityAndFlags & hkArray<hkCollisionDetail>::CAPACITY_MASK) << 2);
	}
	c->endObject();
}

// @ 0x0108c700
// Havok "finish loaded object" hook: re-initialises a just-deserialized hkSimpleShapePhantom in place
// (world object fix-up, empty listener/overlap arrays, vtable).
void hkSimpleShapePhantom::finishLoadedObject(void* p, int finishing)
{
	if (p != 0)
	{
		hkFinishLoadedObjectFlag f;
		f.m_finishing = 1;
		new (p) hkSimpleShapePhantom(f);
	}
}

// @ 0x0108c750
// NOTE: symbols/havok_names.txt labels this address hkCachingShapePhantom::hkCachingShapePhantom, but the vtable it
// stores (0x0149E3B8) and the 4-byte element array at +0x120 are hkSimpleShapePhantom's.
hkSimpleShapePhantom::hkSimpleShapePhantom(const hkShape* shape, const hkTransform& transform, hkUint32 collisionFilterInfo)
	: hkShapePhantom(shape, transform)
{
	m_collisionDetails.m_data = 0;
	m_collisionDetails.m_size = 0;
	m_collisionDetails.m_capacityAndFlags = (int)0x80000000;
	m_collidable.m_broadPhaseHandle.m_collisionFilterInfo = collisionFilterInfo;
}

// @ 0x0108c790
hkSimpleShapePhantom::~hkSimpleShapePhantom()
{
	if (m_collisionDetails.m_capacityAndFlags >= 0)
	{
		hkThreadMemory_getInstance()->deallocateChunk(m_collisionDetails.m_data,
			(m_collisionDetails.m_capacityAndFlags & hkArray<hkCollisionDetail>::CAPACITY_MASK) * 4, HK_MEMORY_CLASS_ARRAY_T);
	}
	// ~hkPhantom runs next (tail call in the binary). The scalar deleting destructor 0x0108C9D0 is the compiler-generated
	// wrapper: destructor body, then hkMemory::deallocateChunk(this, memSize, 0x2e) when the delete flag is set.
}

// Copies one listener array: reallocates when the destination's capacity is too small, then copies the pointers.
static inline void copyPointerArray(hkArray<hkPhantomOverlapListener*>& dst, const hkArray<hkPhantomOverlapListener*>& src)
{
	if ((dst.m_capacityAndFlags & hkArray<hkPhantomOverlapListener*>::CAPACITY_MASK) < src.m_size)
	{
		if (dst.m_capacityAndFlags >= 0)
		{
			hkThreadMemory_getInstance()->deallocateChunk(dst.m_data,
				(dst.m_capacityAndFlags & hkArray<hkPhantomOverlapListener*>::CAPACITY_MASK) * 4, HK_MEMORY_CLASS_ARRAY_T);
		}
		dst.m_data = (hkPhantomOverlapListener**)hkThreadMemory_getInstance()->allocateChunk(src.m_size * 4, HK_MEMORY_CLASS_ARRAY_T);
		dst.m_capacityAndFlags = (dst.m_capacityAndFlags & 0x40000000) | src.m_size;
	}
	dst.m_size = src.m_size;
	for (int i = 0; i < src.m_size; ++i)
		dst.m_data[i] = src.m_data[i];
}
static inline void copyPointerArray(hkArray<void*>& dst, const hkArray<void*>& src)
{
	if ((dst.m_capacityAndFlags & hkArray<void*>::CAPACITY_MASK) < src.m_size)
	{
		if (dst.m_capacityAndFlags >= 0)
		{
			hkThreadMemory_getInstance()->deallocateChunk(dst.m_data,
				(dst.m_capacityAndFlags & hkArray<void*>::CAPACITY_MASK) * 4, HK_MEMORY_CLASS_ARRAY_T);
		}
		dst.m_data = (void**)hkThreadMemory_getInstance()->allocateChunk(src.m_size * 4, HK_MEMORY_CLASS_ARRAY_T);
		dst.m_capacityAndFlags = (dst.m_capacityAndFlags & 0x40000000) | src.m_size;
	}
	dst.m_size = src.m_size;
	for (int i = 0; i < src.m_size; ++i)
		dst.m_data[i] = src.m_data[i];
}

// @ 0x0108c7e0
// Creates a copy of this phantom: same shape, transform and collision filter, copies of the two listener arrays and
// of the world object properties. (The overlap array is not copied.)
hkSimpleShapePhantom* hkSimpleShapePhantom::clone() const
{
	hkSimpleShapePhantom* p = new hkSimpleShapePhantom(m_collidable.m_shape, m_motionState.m_transform,
	                                                   m_collidable.m_broadPhaseHandle.m_collisionFilterInfo);
	copyPointerArray(p->m_overlapListeners, m_overlapListeners);
	copyPointerArray(p->m_phantomListeners, m_phantomListeners);
	p->copyProperties(this);
	return p;
}

// @ 0x0108c950
void hkSimpleShapePhantom::deallocateInternalArrays()
{
	if (m_collisionDetails.m_size == 0)
	{
		if (m_collisionDetails.m_capacityAndFlags >= 0)
		{
			hkThreadMemory_getInstance()->deallocateChunk(m_collisionDetails.m_data,
				(m_collisionDetails.m_capacityAndFlags & hkArray<hkCollisionDetail>::CAPACITY_MASK) * 4, HK_MEMORY_CLASS_ARRAY_T);
		}
		m_collisionDetails.m_data = 0;
		m_collisionDetails.m_size = 0;
		m_collisionDetails.m_capacityAndFlags = (m_collisionDetails.m_capacityAndFlags & (int)0xc0000000) | (int)0x80000000;
	}
	hkShapePhantom::deallocateInternalArrays();
}

// ---- hkResponseModifier ---------------------------------------------------------------------------------------------
struct hkRigidBody;
struct hkEntity;
struct hkConstraintInfo
{
	int m_maxSizeOfJacobians;    // +0
	int m_sizeOfJacobians;       // +4
	int m_sizeOfSchemas;         // +8
	int m_numSolverResults;      // +0xc
};
struct hkConstraintInstance;
struct hkConstraintOwner
{
	virtual void co0(); virtual void co1(); virtual void co2();
	virtual void addConstraintInfo(hkConstraintInstance* c, hkConstraintInfo& delta);   // 3 (0xc) (name guessed)
	char m_pad[0x1c - 2 * sizeof(void*)];
	hkWorld* m_world;            // +0x1c (32-bit offset)
};
struct hkConstraintInstance : hkReferencedObject    // size 0x28
{
	hkConstraintOwner* m_owner;      // +8
	void* m_data;                    // +0xc
	hkEntity* m_entities[2];         // +0x10
};
struct hkDynamicsContactMgr : hkReferencedObject    // size 0xc (hkContactMgr is 8)
{
	hkWorld* m_world;                // +8
};
// Contact manager "type" values live in two globals (names guessed): the manager is switched from the first state to
// the second once its inverse-mass scaling is overridden.
extern int g_contactMgrTypeNormal;       // 0x016E4518
extern int g_contactMgrTypeScaled;       // 0x016E43E0
struct hkSimpleConstraintContactMgr : hkDynamicsContactMgr
{
	uint16_t m_reservedContactPoints;     // +0xc
	uint16_t m_pad0e;
	int m_type;                           // +0x10
	char m_pad14[0x3c - 0x14];
	hkReal m_invMassScaleA;               // +0x3c
	hkReal m_invMassScaleB;               // +0x40
	char m_pad44[0x4c - 0x44];
	int m_numContactPoints;               // +0x4c
	char m_pad50[0x74 - 0x50];
	hkConstraintInstance m_constraint;    // +0x74
	virtual hkResult reserveContactPoints(int numPoints);   // 0x0108D070
};

struct hkResponseModifier
{
	static void setInvMassScalingForContact(hkDynamicsContactMgr* manager, hkRigidBody* bodyA, hkRigidBody* bodyB,
	                                        hkReal factorA, hkReal factorB);   // 0x0108CA40
};

// @ 0x0108ca40
void hkResponseModifier::setInvMassScalingForContact(hkDynamicsContactMgr* manager, hkRigidBody* bodyA, hkRigidBody* bodyB,
                                                     hkReal factorA, hkReal factorB)
{
	hkSimpleConstraintContactMgr* mgr = static_cast<hkSimpleConstraintContactMgr*>(manager);
	if (mgr->m_type == g_contactMgrTypeNormal)
	{
		if ((hkEntity*)bodyA == mgr->m_constraint.m_entities[0])
		{
			mgr->m_invMassScaleA = factorA;
			mgr->m_invMassScaleB = factorB;
		}
		else
		{
			mgr->m_invMassScaleA = factorB;
			mgr->m_invMassScaleB = factorA;
		}
		hkConstraintOwner* owner = mgr->m_constraint.m_owner;
		if (owner != 0)
		{
			// The expanded manager needs two more jacobians and schema blocks.
			hkConstraintInfo delta;
			delta.m_maxSizeOfJacobians = 0;
			delta.m_sizeOfJacobians = 0x40;
			delta.m_sizeOfSchemas = 0x20;
			delta.m_numSolverResults = 0;
			hkCriticalSection* cs = owner->m_world->m_modifyConstraintCriticalSection;
			if (cs != 0)
			{
				cs->enter();
				owner->addConstraintInfo(&mgr->m_constraint, delta);
				cs->leave();
			}
			else
			{
				owner->addConstraintInfo(&mgr->m_constraint, delta);
			}
		}
		mgr->m_type = g_contactMgrTypeScaled;
	}
}

// @ 0x0108d070
hkResult hkSimpleConstraintContactMgr::reserveContactPoints(int numPoints)
{
	if (m_numContactPoints + (int)m_reservedContactPoints + numPoints > 0xfe)
		return HK_FAILURE;
	m_reservedContactPoints = (uint16_t)(uint8_t)((uint8_t)m_reservedContactPoints + (uint8_t)numPoints);
	return HK_SUCCESS;
}

// ---- hkSimpleContactConstraintData / hkMovingSurfaceConstraintData ---------------------------------------------------------
struct hkConstraintData : hkReferencedObject
{
	hkUint32 m_userData;    // +8
};
struct hkConstraintQueryOut;
struct hkVelocityAccumulator
{
	char m_pad[0x10];
	hkVector4 m_linearVelocity;   // +0x10 (the 4 floats the callbacks update)
};
struct hkConstraintQueryIn
{
	char m_pad[0x28];                   // hkConstraintQueryStepInfo (0x20) + buffer roots (0x20..0x27)
	hkVelocityAccumulator* m_bodyA;     // +0x28 (32-bit offset)
};
struct hkBodyVelocity { hkVector4 m_linearVelocity; };   // first member only (name guessed)
struct hkSimpleConstraintInfoInitInput;
struct hkJacobianBlock { char m_data[0x14]; };

// C helpers (cdecl) of the constraint solver, symbols _hkInitHeader and _hkAddVelocityBuildJacobian.
extern "C" void hkInitHeader(const hkConstraintQueryIn& in, const void* schemaData, int sizeOfElement, hkConstraintQueryOut& out);
extern "C" void hkAddVelocityBuildJacobian(const hkVector4* velocity, const hkConstraintQueryIn& in, hkConstraintQueryOut& out);

struct hkSimpleContactConstraintData : hkConstraintData
{
	hkArray<uint8_t> m_contactPointIds;           // +0xc (name guessed: byte ids, see hkContactPointConfirmedEvent::getContactPointId)
	char m_pad18[0x20 - 0x18];                    // 32-bit: array header is 12 bytes
	hkArray<hkContactPoint> m_contactPoints;      // +0x20 (0x20 bytes each)
	const hkVector4* m_pointer2c;                 // +0x2c  used by hkMovingSurfaceConstraintData as the surface velocity
	hkReal m_float30;                             // +0x30  ... and its scale
	int m_pad34;
	hkArray<hkJacobianBlock> m_array38;           // +0x38 (0x14 bytes each)

	virtual ~hkSimpleContactConstraintData();                                              // body at 0x0108CB20 (name guessed)
	virtual void getConstraintInfo(hkConstraintInfo& info) const;                          // 0x010A3E70
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);  // 0x010A3ED0
};

// @ 0x0108cb20
hkSimpleContactConstraintData::~hkSimpleContactConstraintData()
{
	if (m_array38.m_capacityAndFlags >= 0)
	{
		hkThreadMemory_getInstance()->deallocateChunk(m_array38.m_data,
			(m_array38.m_capacityAndFlags & hkArray<hkJacobianBlock>::CAPACITY_MASK) * 0x14, HK_MEMORY_CLASS_ARRAY_T);
	}
	if (m_contactPoints.m_capacityAndFlags >= 0)
	{
		hkThreadMemory_getInstance()->deallocateChunk(m_contactPoints.m_data,
			(m_contactPoints.m_capacityAndFlags & hkArray<hkContactPoint>::CAPACITY_MASK) << 5, HK_MEMORY_CLASS_ARRAY_T);
	}
	if (m_contactPointIds.m_capacityAndFlags >= 0)
	{
		hkThreadMemory_getInstance()->deallocateChunk(m_contactPointIds.m_data,
			m_contactPointIds.m_capacityAndFlags & hkArray<uint8_t>::CAPACITY_MASK, HK_MEMORY_CLASS_ARRAY_T);
	}
	// base vtable restore: hkConstraintData's (the 0x013EF094 table), done by the compiler-generated epilogue
}

struct hkMovingSurfaceConstraintData : hkSimpleContactConstraintData
{
	virtual void getConstraintInfo(hkConstraintInfo& info) const;                          // 0x0108CBB0
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);  // 0x0108CDB0
	virtual void toiCollisionResponseBeginCallback(const hkContactPoint& cp, hkSimpleConstraintInfoInitInput& inA, hkBodyVelocity& velA,
	                                               hkSimpleConstraintInfoInitInput& inB, hkBodyVelocity& velB);          // 0x0108CBE0
	virtual void toiCollisionResponseEndCallback(const hkContactPoint& cp, hkReal t, hkSimpleConstraintInfoInitInput& inA, hkBodyVelocity& velA,
	                                             hkSimpleConstraintInfoInitInput& inB, hkBodyVelocity& velB);            // 0x0108CCC0
};

// @ 0x0108cbb0
void hkMovingSurfaceConstraintData::getConstraintInfo(hkConstraintInfo& info) const
{
	hkSimpleContactConstraintData::getConstraintInfo(info);
	info.m_sizeOfSchemas += 0x20;
	info.m_sizeOfJacobians += 0x20;
}

// The tangential part of the surface velocity (velocity minus its component along the contact normal), shared by the
// two TOI callbacks. xs, ys, d and d*xs stay on the x87 stack in the binary.
#define HK_MOVING_SURFACE_TANGENT \
	const hkVector4* V = m_pointer2c; \
	hkReal s = m_float30; \
	hkX87Real xs = (hkX87Real)V->x * s;                                  /* X87-PRECISION */ \
	hkX87Real ys = (hkX87Real)V->y * s;                                  /* X87-PRECISION */ \
	float zs = (float)((hkX87Real)V->z * s);                            /* [esp+0x18] */ \
	float ws = (float)((hkX87Real)V->w * s);                            /* [esp+0x1c] */ \
	hkX87Real d = ((hkX87Real)zs * cp.m_separatingNormal.z + ys * cp.m_separatingNormal.y) + xs * cp.m_separatingNormal.x; \
	float Ty = (float)(d * ys);                                          /* [esp+0x24] */ \
	float Tz = (float)((hkX87Real)zs * d);                               /* [esp+0x28] */ \
	float Tw = (float)((hkX87Real)ws * d);                               /* [esp+0x2c] */ \
	float Rx = (float)(xs - d * xs);                                     /* [esp+0x10] */ \
	hkX87Real Ry = ys - Ty;                                              /* X87-PRECISION: not stored */ \
	hkX87Real Rz = (hkX87Real)zs - Tz;                                   /* X87-PRECISION: not stored */ \
	float Rw = (float)((hkX87Real)ws - Tw);                              /* [esp+0x1c] */

// @ 0x0108cbe0
void hkMovingSurfaceConstraintData::toiCollisionResponseBeginCallback(const hkContactPoint& cp, hkSimpleConstraintInfoInitInput& inA, hkBodyVelocity& velA,
                                                                      hkSimpleConstraintInfoInitInput& inB, hkBodyVelocity& velB)
{
	HK_MOVING_SURFACE_TANGENT
	velB.m_linearVelocity.x = (float)(Rx + velB.m_linearVelocity.x);
	velB.m_linearVelocity.y = (float)(Ry + velB.m_linearVelocity.y);
	velB.m_linearVelocity.z = (float)(Rz + velB.m_linearVelocity.z);
	velB.m_linearVelocity.w = (float)((hkX87Real)Rw + velB.m_linearVelocity.w);
}

// @ 0x0108ccc0
void hkMovingSurfaceConstraintData::toiCollisionResponseEndCallback(const hkContactPoint& cp, hkReal t, hkSimpleConstraintInfoInitInput& inA, hkBodyVelocity& velA,
                                                                    hkSimpleConstraintInfoInitInput& inB, hkBodyVelocity& velB)
{
	HK_MOVING_SURFACE_TANGENT
	velB.m_linearVelocity.x = (float)((hkX87Real)velB.m_linearVelocity.x - Rx);
	velB.m_linearVelocity.y = (float)((hkX87Real)velB.m_linearVelocity.y - Ry);
	velB.m_linearVelocity.z = (float)((hkX87Real)velB.m_linearVelocity.z - Rz);
	velB.m_linearVelocity.w = (float)((hkX87Real)velB.m_linearVelocity.w - Rw);
}

// @ 0x0108cdb0
void hkMovingSurfaceConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	hkInitHeader(in, m_array38.m_data, 0x14, out);
	hkVelocityAccumulator* body = in.m_bodyA;
	const hkContactPoint& cp = m_contactPoints.m_data[0];
	const hkVector4& n = cp.m_separatingNormal;
	const hkVector4* V = m_pointer2c;
	hkReal s = m_float30;

	// dp = (n.x*V.x + n.z*V.z) + n.y*V.y, stored as a float
	float dp = (float)(((hkX87Real)n.x * V->x + (hkX87Real)n.z * V->z) + (hkX87Real)n.y * V->y);
	float Rx = (float)((hkX87Real)V->x - (hkX87Real)n.x * dp);                   // stored
	hkX87Real Ry = (hkX87Real)V->y - (hkX87Real)n.y * dp;                       // X87-PRECISION: not stored
	hkX87Real Rz = (hkX87Real)V->z - (hkX87Real)n.z * dp;                       // X87-PRECISION: not stored
	float Rw = (float)((hkX87Real)V->w - (hkX87Real)n.w * dp);                  // stored
	hkVector4 w;
	w.x = -(float)((hkX87Real)Rx * s);
	w.y = -(float)(Ry * s);
	w.z = -(float)(Rz * s);
	w.w = -(float)((hkX87Real)Rw * s);
	hkAddVelocityBuildJacobian(&w, in, out);

	body->m_linearVelocity.x = w.x + body->m_linearVelocity.x;
	body->m_linearVelocity.y = w.y + body->m_linearVelocity.y;
	body->m_linearVelocity.z = w.z + body->m_linearVelocity.z;
	body->m_linearVelocity.w = w.w + body->m_linearVelocity.w;
	hkSimpleContactConstraintData::buildJacobian(in, out);
	body->m_linearVelocity.x = body->m_linearVelocity.x - w.x;
	body->m_linearVelocity.y = body->m_linearVelocity.y - w.y;
	body->m_linearVelocity.z = body->m_linearVelocity.z - w.z;
	body->m_linearVelocity.w = body->m_linearVelocity.w - w.w;
	w.x = -w.x;
	w.y = -w.y;
	w.z = -w.z;
	w.w = -w.w;
	hkAddVelocityBuildJacobian(&w, in, out);
}

// ---- hkRigidBody / hkContactPointConfirmedEvent -----------------------------------------------------------------------------
struct hkMotion : hkReferencedObject { int m_solverData; };     // +8
struct hkRigidMotion : hkMotion                                  // size 0xf0
{
	int m_pad0c;
	hkMotionState m_motionState;     // +0x10
	hkReal m_massInv;                // +0xc0
	hkReal m_particleMinInertiaDiagInv;   // +0xc4
	hkReal m_linearDamping;          // +0xc8
	hkReal m_angularDamping;         // +0xcc
	hkVector4 m_linearVelocity;      // +0xd0
	hkVector4 m_angularVelocity;     // +0xe0
};
struct hkEntity : hkWorldObject            // size 0xd0
{
	hkMotion* m_motion;                     // +0x58
};
struct hkRigidBody : hkEntity
{
	void getPointVelocity(const hkVector4& p, hkVector4& out) const;   // 0x0108CF90
};

// @ 0x0108cf90
// out = v + w x (p - centerOfMass), the velocity of a world space point attached to the body.
void hkRigidBody::getPointVelocity(const hkVector4& p, hkVector4& out) const
{
	const hkRigidMotion* motion = static_cast<const hkRigidMotion*>(m_motion);
	const hkVector4& com = motion->m_motionState.m_centerOfMass1;
	const hkVector4& w = motion->m_angularVelocity;
	// X87-PRECISION: the three differences stay on the x87 stack.
	hkX87Real dx = (hkX87Real)p.x - com.x;
	hkX87Real dy = (hkX87Real)p.y - com.y;
	hkX87Real dz = (hkX87Real)p.z - com.z;
	float oy = (float)(dx * w.z - dz * w.x);     // [esp+8]
	float oz = (float)(dy * w.x - dx * w.y);     // [esp+0xc]
	float ox = (float)(dz * w.y - dy * w.z);
	out.y = oy;
	out.z = oz;
	out.w = 0.0f;
	out.x = ox;
	const hkVector4& v = motion->m_linearVelocity;
	out.x = (float)((hkX87Real)v.x + out.x);
	out.y = (float)((hkX87Real)oy + v.y);
	out.z = (float)((hkX87Real)oz + v.z);
	out.w = v.w;
}

struct hkContactPointMaterial;
struct hkContactPointConfirmedEvent
{
	hkCollidable* m_collidableA;                 // +0
	hkCollidable* m_collidableB;                 // +4
	hkEntity* m_callbackFiredFrom;               // +8
	hkContactPoint* m_contactPoint;              // +0xc
	hkContactPointMaterial* m_contactPointMaterial;   // +0x10
	hkReal m_rotateNormal;                       // +0x14
	hkReal m_projectedVelocity;                  // +0x18
	int m_type;                                  // +0x1c (hkContactPointAddedEvent::Type)
	hkSimpleContactConstraintData* m_contactData;   // +0x20
	hkContactPointId getContactPointId() const;  // 0x0108D040
};

// @ 0x0108d040
// Looks up the id of the event's contact point: its index in the contact point array, found among the id bytes.
hkContactPointId hkContactPointConfirmedEvent::getContactPointId() const
{
	if (m_type == 0)
		return 0xffff;
	const hkSimpleContactConstraintData* data = m_contactData;
	int index = (int)((const char*)m_contactPoint - (const char*)data->m_contactPoints.m_data) >> 5;
	int i = data->m_contactPointIds.m_size - 1;
	for (; i >= 0; --i)
	{
		if ((int)data->m_contactPointIds.m_data[i] == index)
			return (hkContactPointId)i;
	}
	return (hkContactPointId)i;
}
