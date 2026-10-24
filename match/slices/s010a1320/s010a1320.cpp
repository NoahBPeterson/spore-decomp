// Havok 3.1.0 slice s010a1320: hkWorldOperationUtil::splitSimulationIslands (0x010a1320, 2052 bytes).
//
// For every active island whose "split check" flag is set, builds a union-find over its entities, and if the
// island is not fully connected distributes the entities, constraints, actions and agents over new islands.
// Struct stubs carry members at the x86 offsets of the 32-bit binary (comments); VC .NET 2003 build (/vc71).
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP
#include "../s010cbaa0/hk31_b005.h"
#include <new>

// vc71 (Havok is VC .NET 2003) has no stdint in scope here; keep it simple.
#ifndef _STDINT_DONE_
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
#endif

typedef uint16_t hkUint16;
typedef uint8_t hkUint8;

class hkWorld;
class hkSimulationIsland;
class hkEntity;
class hkUnionFind;
struct hkAgentNnEntry;
class hkConstraintInstance;
class hkEntityDeactivator;

// hkArrayUtil::_reduce (cdecl): shrinks a heap array to its size, back to the inplace storage when it fits.
void hkArrayUtil_reduce(void* array, int elemSize, void* inplaceStorage, int inplaceCapacity);   // 0x0107F5D0

// ---- hkThreadMemory stack allocator / hkLocalArray / hkInplaceArray ------------------------------------------------
struct hkThreadMemoryRaw
{
	virtual void vslot0();
	virtual void vslot1();
	virtual void vslot2();
	virtual void* onStackOverflow(int nbytes);          // +0x0c
	virtual void onStackUnderflow(void* p);              // +0x10
	uint32_t pad04[7];
	char* m_stackCurrent;                                // +0x20
	char* m_stackPrev;                                   // +0x24
	char* m_stackBase;                                   // +0x28
	char* m_stackEnd;                                    // +0x2c
	void deallocateChunk(void* p, int nbytes, int cl);   // 0x0107DB10
	static __forceinline hkThreadMemoryRaw& getInstance() { return *(hkThreadMemoryRaw*)TlsGetValue(g_hkThreadMemoryTls); }
};

template <typename T> __forceinline T* hkAllocateStack(int n)
{
	hkThreadMemoryRaw& tm = hkThreadMemoryRaw::getInstance();
	int size = (n * (int)sizeof(T) + 0x10) & ~0xf;
	char* cur = tm.m_stackCurrent;
	char* next = cur + size;
	if ((uint32_t)next <= (uint32_t)tm.m_stackEnd)
	{
		tm.m_stackCurrent = next;
		return (T*)cur;
	}
	return (T*)tm.onStackOverflow(size);
}
template <typename T> __forceinline void hkDeallocateStack(T* p)
{
	hkThreadMemoryRaw& tm = hkThreadMemoryRaw::getInstance();
	tm.m_stackCurrent = (char*)p;
	if ((char*)p == tm.m_stackBase)
		tm.onStackUnderflow(p);
}

// hkArray<T> with the Havok destructor (frees the heap block unless DONT_DEALLOCATE is set).
template <typename T>
struct hkArrayD : hkArray<T>
{
	enum { DONT_DEALLOCATE_FLAG = (int)0x80000000 };
	__forceinline hkArrayD() { this->m_data = 0; this->m_size = 0; this->m_capacityAndFlags = DONT_DEALLOCATE_FLAG; }
	__forceinline ~hkArrayD()
	{
		if ((this->m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
			hkThreadMemoryRaw::getInstance().deallocateChunk(this->m_data, (this->m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
	}
};

template <typename T>
struct hkLocalArray : hkArrayD<T>
{
	T* m_localMemory;                                    // +0x0c
	__forceinline hkLocalArray(int capacity)
	{
		this->m_data = hkAllocateStack<T>(capacity);
		this->m_capacityAndFlags = capacity | (int)0x80000000;
		m_localMemory = this->m_data;
	}
	__forceinline ~hkLocalArray() { hkDeallocateStack(m_localMemory); }
};

// Same, but the destructor first clears the size (used for the agent track's sector list).
template <typename T, int N>
struct hkInplaceArrayZ : hkArray<T>
{
	T m_storage[N];                                      // +0x0c
	__forceinline hkInplaceArrayZ()
	{
		this->m_data = m_storage;
		this->m_size = 0;
		this->m_capacityAndFlags = N | (int)0x80000000;
	}
	__forceinline ~hkInplaceArrayZ()
	{
		this->m_size = 0;
		if ((this->m_capacityAndFlags & (int)0x80000000) == 0)
			hkThreadMemoryRaw::getInstance().deallocateChunk(this->m_data, (this->m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
	}
};

template <typename T, int N>
struct hkInplaceArrayD : hkArrayD<T>
{
	T m_storage[N];                                      // +0x0c
	__forceinline hkInplaceArrayD()
	{
		this->m_data = m_storage;
		this->m_size = 0;
		this->m_capacityAndFlags = N | (int)0x80000000;
	}
};

// HK_TIMER_BEGIN_LIST(list, firstSplit): 16-byte monitor-stream record.
struct hkMonitorListCommand { const char* m_name; uint32_t m_time; uint32_t m_pad; const char* m_firstSplit; };
static __forceinline void hkTimerBeginList(const char* name, const char* firstSplit)
{
	void* end = hkTlsGet(g_hkMonitorStreamEndTls);
	if (hkTlsGet(g_hkMonitorStreamCurrentTls) < end)
	{
		hkMonitorListCommand* c = (hkMonitorListCommand*)hkTlsGet(g_hkMonitorStreamCurrentTls);
		c->m_name = name;
		c->m_firstSplit = firstSplit;
		uint32_t t;
		__asm { rdtsc
		        mov t, eax }
		c->m_time = t;
		hkTlsSet(g_hkMonitorStreamCurrentTls, c + 1);
	}
}

// ---- world objects --------------------------------------------------------------------------------------------------
class hkUnionFind
{
public:
	hkUnionFind(hkArray<int>& parents, int numElements);        // 0x01209660
	void assignGroups(hkArray<int>& groupSizesOut);             // 0x012096C0
	hkArray<int>* m_parents;
	int m_numElements;
};

// Agent track: a list of sectors, each a run of variable-size hkAgentNnEntry records.
struct hkAgentNnEntry
{
	hkUint8 m_streamCommand, m_agentType, m_numContactPoints, m_size;   // +0
	uint32_t m_pad04[4];
	struct hkLinkedCollidableStub* m_collidable[2];             // +0x14
};
struct hkLinkedCollidableStub { char m_pad0[0x10]; int m_ownerOffset; };   // +0x10: owner = this + m_ownerOffset

struct hkAgentNnTrack
{
	hkInplaceArrayZ<char*, 1> m_sectors;                        // +0 (inplace storage of 1 at +0xc)
	unsigned m_bytesUsedInLastSector;                           // +0x10
	hkUint16 m_agentSize;                                       // +0x14
	hkUint16 m_sectorSize;                                      // +0x16
};
void hkAgentNnTrack_appendCopy(hkAgentNnTrack* track, hkAgentNnEntry* entry);   // 0x010FBD10 (cdecl, name inferred)
void hkAgentNnTrack_remove(hkAgentNnTrack* track, hkAgentNnEntry* entry);       // 0x010FBC50 (cdecl, name inferred)

struct hkConstraintInfo { int m_maxSizeOfJacobians, m_sizeOfJacobians, m_sizeOfSchemas, m_numSolverResults; };
class hkConstraintData
{ public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void getConstraintInfo(hkConstraintInfo& out) const;   // 8 (+0x20)
};
class hkConstraintInstance : public hkReferencedObject
{
public:
	void fixNullEntities();                                     // 0x0108BFF0
	hkSimulationIsland* m_owner;                                // +8
};
struct hkConstraintInternal                                     // 0x1c bytes
{
	hkConstraintInstance* m_constraint;                         // +0
	char m_pad4[0xc - 4];
	hkConstraintData* m_data;                                   // +0xc
	char m_pad10[0x1c - 0x10];
};

// hkMotionState: the transform at +0, the swept transform at +0x40 (0xb0 bytes, see hkReflectedClasses.h).
// hkBool without the ?: in the constructor: the binary stores the incoming bool byte unchanged.
class hkBoolArg
{
public:
	hkBoolArg(bool b) : m_bool(b) {}
	operator bool() const { return m_bool != 0; }
private:
	char m_bool;
};

class hkMotionState
{
public:
	float m_transform[16];                                      // +0x00 (hkTransform)
	char m_sweptTransform[0x50];                                // +0x40
	float m_deltaAngle[4];                                      // +0x90 (hkVector4)
	float m_objectRadius;                                       // +0xa0
	float m_maxLinearVelocity;                                  // +0xa4
	float m_maxAngularVelocity;                                 // +0xa8
	hkUint16 m_deactivationClass;                               // +0xac
	hkUint16 m_deactivationCounter;                             // +0xae
};

// hkMotion / hkRigidMotion / hkKeyframedRigidMotion: motion state at +0x10, m_savedMotion at +0xf0.
class hkMotion
{
public:
	enum MotionType
	{
		MOTION_INVALID = 0, MOTION_DYNAMIC = 1, MOTION_SPHERE_INERTIA = 2,
		MOTION_STABILIZED_SPHERE_INERTIA = 3, MOTION_BOX_INERTIA = 4,
		MOTION_STABILIZED_BOX_INERTIA = 5, MOTION_KEYFRAMED = 6, MOTION_FIXED = 7,
		MOTION_THIN_BOX_INERTIA = 8, MOTION_MAX_ID = 9
	};
	virtual void s0(); virtual void s1(); virtual int getType(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6();
	virtual int getSolverSize();                                // 7 (+0x1c)
	hkInt16 m_memSizeAndFlags;                                  // +4
	hkInt16 m_referenceCount;                                   // +6
	char m_pad08[8];
	hkMotionState m_motionState;                                // +0x10
	float m_massInv;                                            // +0xc0
	float m_particleMinInertiaDiagInv;                          // +0xc4
	float m_linearDamping;                                      // +0xc8
	float m_angularDamping;                                     // +0xcc
	float m_linearVelocity[4];                                 // +0xd0 (hkVector4)
	float m_angularVelocity[4];                                // +0xe0 (hkVector4)
	hkMotion* m_savedMotion;                                    // +0xf0
};

class hkAction
{
public:
	virtual void s0(); virtual void s1(); virtual void s2();
	virtual void getEntities(hkArray<hkEntity*>& out);          // 3 (+0xc)
	hkInt16 m_memSizeAndFlags; hkInt16 m_referenceCount;        // +4
	char m_pad8[4];
	hkSimulationIsland* m_island;                               // +0xc
};

struct hkCollisionEntry { hkAgentNnEntry* m_agentEntry; hkLinkedCollidableStub* m_partner; };   // 8 bytes

class hkEntity
{
public:
	void addReference();                                        // 0x01082590 (hkReferencedObject::addReference)
	void removeReference();                                     // 0x0109AE60 (hkWorldObject::removeReference)
	char m_pad0[8];
	hkWorld* m_world;                                           // +0x08
	char m_pad0c[0x40 - 0x0c];
	hkArray<hkCollisionEntry> m_collisionEntries;               // +0x40
	char m_pad4c[0x58 - 0x4c];
	hkMotion* m_motion;                                         // +0x58
	hkSimulationIsland* m_simulationIsland;                     // +0x5c
	char m_pad60[0x6c - 0x60];
	hkEntityDeactivator* m_deactivator;                         // +0x6c
	hkConstraintInternal* m_constraintsMasterData;              // +0x70
	int m_constraintsMasterSize;                                // +0x74
	char m_pad78[0x94 - 0x78];
	hkUint16 m_storageIndex;                                    // +0x94
	char m_pad96[0x99 - 0x96];
	hkUint8 m_isFixed;                                          // +0x99
	hkUint8 m_isFixedOrKeyframed;                               // +0x9a
};

class hkRigidBody : public hkEntity { public: };

class hkSimulationIsland
{
public:
	virtual void v0();
	hkInt16 m_memSizeAndFlags;                                  // +4
	hkInt16 m_referenceCount;
	int m_maxSizeOfJacobians;                                   // +8
	int m_sizeOfJacobians;                                      // +0xc
	int m_sizeOfSchemas;                                        // +0x10
	int m_sumSizeOfMotions;                                     // +0x14
	int m_numSolverResults;                                     // +0x18
	hkWorld* m_world;                                           // +0x1c
	hkUint16 m_storageIndex;                                    // +0x20
	hkUint16 m_dirtyListIndex;                                  // +0x22
	hkUint8 m_highFrequencyCounter, m_lowFrequencyCounter;      // +0x24
	hkUint8 m_splitCheckRequested;                              // +0x26
	hkUint8 m_actionListCleanupNeeded;                          // +0x27
	char m_pad28[0x3c - 0x28];
	hkEntity** m_entitiesData;                                  // +0x3c
	int m_entitiesSize;                                         // +0x40
	int m_entitiesCapacityAndFlags;                             // +0x44
	char m_entitiesInplace[4];                                  // +0x48
	hkAgentNnTrack m_agentTrack;                                // +0x4c
	hkAction** m_actionsData;                               // +0x64
	int m_actionsSize;                                          // +0x68
	int m_actionsCapacityAndFlags;                              // +0x6c
	float m_timeOfDeactivation;                                 // +0x70

	hkSimulationIsland(hkWorld* world);                         // 0x010A2810
	static void* operator new(size_t nbytes)                    // memory class 0x2f
	{
		void* p = hkMemory::s_instance->allocateChunk((int)nbytes, 0x2f);
		((hkSimulationIsland*)p)->m_memSizeAndFlags = (hkInt16)nbytes;
		return p;
	}
	void subConstraintInfo(hkConstraintInfo& info)
	{
		m_sizeOfJacobians -= info.m_sizeOfJacobians;
		m_sizeOfSchemas -= info.m_sizeOfSchemas;
		m_numSolverResults -= info.m_numSolverResults;
	}
	void addConstraintInfo(hkConstraintInfo& info)
	{
		int v = info.m_maxSizeOfJacobians;
		if (v < m_maxSizeOfJacobians)
			v = m_maxSizeOfJacobians;
		m_maxSizeOfJacobians = v;
		if (v <= info.m_sizeOfJacobians)
			v = info.m_sizeOfJacobians;
		m_maxSizeOfJacobians = v;
		m_sizeOfJacobians += info.m_sizeOfJacobians;
		m_sizeOfSchemas += info.m_sizeOfSchemas;
		m_numSolverResults += info.m_numSolverResults;
	}
	hkBool isFullyConnected(hkUnionFind& uf);                   // 0x010A2590 (protected in Havok)
};

class hkCollisionDispatcher
{
public:
	char m_pad[0x1bf8];
	int m_agent3SectorSize;                                     // +0x1bf8
	int m_agent3AgentSize;                                      // +0x1bfc
};

// hkStepInfo (0x10 bytes): the start time at +0, the delta time at +8.
class hkStepInfo
{
public:
	float m_startTime;  // +0
	float m_endTime;    // +4
	float m_deltaTime;  // +8
	float m_invDeltaTime;   // +0xc
};
class hkWorldDynamicsStepInfo
{
public:
	hkStepInfo m_stepInfo;                                      // +0
	char m_solverInfo[0x150 - 0x10];                            // +0x10
};

enum hkEntityActivation
{
	HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE = 0,
	HK_ENTITY_ACTIVATION_ACTIVATE = 1
};
enum hkUpdateCollisionFilterOnEntityMode
{
	HK_UPDATE_FILTER_ON_ENTITY_FULL_CHECK = 0,
	HK_UPDATE_FILTER_ON_ENTITY_DISABLE_ENTITY_ENTITY_COLLISIONS_ONLY = 1
};

// hkSimulation: only vtable slot 12 is called (re-collide a list of entities after a warp).
class hkSimulation
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void collideEntities(hkEntity** entities, int numEntities, hkWorld* world);   // 12 (+0x30)
};

class hkWorld
{
public:
	char m_pad00[0x08];                                         // +0x00 (vtable, refcount)
	hkSimulation* m_simulation;                                 // +0x08
	char m_pad0c[0x30 - 0x0c];
	hkSimulationIsland* m_fixedIsland;                          // +0x30
	char m_pad34[4];
	hkArray<hkSimulationIsland*> m_activeSimulationIslands;     // +0x38
	char m_pad44[0x80 - 0x44];
	hkCollisionDispatcher* m_collisionDispatcher;               // +0x80
	char m_pad84[0x88 - 0x84];
	int m_pendingOperationsCount;                               // +0x88
	int m_lockCount;                                            // +0x8c
	char m_pad90[0x94 - 0x90];
	hkUint8 m_blockExecutingPendingOperations;                  // +0x94 (hkBool)
	hkUint8 m_criticalOperationsAllowed;                        // +0x95 (hkBool)
	char m_pad96[0xb4 - 0x96];
	hkUint8 m_wantSimulationIslands;                            // +0xb4
	char m_padB5[3];                                            // +0xb5
	float m_highFrequencyLimit;                                 // +0xb8
	float m_lowFrequencyLimit;                                  // +0xbc
	char m_padC0[0xc4 - 0xc0];
	int m_simulationType;                                       // +0xc4
	char m_padC8[0x170 - 0xc8];
	hkWorldDynamicsStepInfo m_dynamicsStepInfo;                 // +0x170

	void updateCollisionFilterOnEntity(hkEntity* entity, hkUpdateCollisionFilterOnEntityMode updateMode,
	                                   hkUint8 updateShapeCollectionFilter);   // 0x01084FA0 (thiscall)
	void executePendingOperations();                            // 0x01082BF0
};

struct hkWorldOperationUtil
{
	static void splitSimulationIslands(hkWorld* world);          // 0x010A1320
	static void setRigidBodyMotionType(hkRigidBody* body, hkMotion::MotionType newState,
	                                   hkEntityActivation activation,
	                                   hkUpdateCollisionFilterOnEntityMode mode);   // 0x010A1B30
	static void replaceMotionObject(hkRigidBody* body, hkMotion::MotionType newState,
	                                hkBoolArg newStateNeedsInertia, hkBoolArg oldStateNeedsInertia,
	                                hkWorld* world);             // 0x010A0190
	static void removeAttachedConstraints(hkEntity* entity, hkArray<hkConstraintInstance*>& constraintsToBeMoved);   // 0x0109FDD0
	static void removeAttachedActionsFromFixedIsland(hkWorld* world, hkEntity* entity,
	                                                 hkArray<hkAction*>& actionsToBeMoved);   // 0x0109FC70
	static void removeAttachedActionsFromDynamicIsland(hkWorld* world, hkEntity* entity,
	                                                   hkArray<hkAction*>& actionsToBeMoved); // 0x010A1010
	static void removeAttachedAgentsConnectingTheEntityAndAFixedPartnerEntityPlus(
		hkAgentNnTrack& trackToScan, hkEntity* entity, hkAgentNnTrack& agentsRemoved,
		hkMotion::MotionType newState);                          // 0x0109FAB0
	static void removeEntitySI(hkWorld* world, hkEntity* entity);                     // 0x010A03C0
	static void addEntitySI(hkWorld* world, hkEntity* entity, hkEntityActivation activation);   // 0x0109FB70
	static void addActionsToEntitysIsland(hkWorld* world, hkEntity* entity,
	                                      hkArray<hkAction*>& actionsToBeMoved);     // 0x010A11D0
	static void mergeIslands(hkWorld* world, hkEntity* entityA, hkEntity* entityB);    // 0x010A1170
};

struct hkWorldConstraintUtil
{
	static void addConstraint(hkWorld* world, hkConstraintInstance* constraint);      // 0x010A6860
};

struct hkWorldCallbackUtil
{
	static void fireInactiveEntityMoved(hkWorld* world, hkEntity* entity);            // 0x0109F870
};

struct hkDiscreteSimulation
{
	static void collideEntitiesBroadPhaseDiscrete(hkEntity** entities, int numEntities, hkWorld* world);   // 0x01099CD0
};

struct hkSweptTransformUtil
{
	static void freezeMotionState(float time, hkMotionState& motionState);            // 0x0120A570
};

void hkAgentNnMachine_AppendTrack(hkAgentNnTrack* dst, hkAgentNnTrack* src);         // 0x010FC090
void FUN_010a08b0(hkSimulation* simulation, hkEntity* entity);                       // 0x010A08B0 (removes entity from a sim list)


// The island an agent entry belongs to: that of collidable 0, or of collidable 1 when collidable 0 is on the fixed island.
static __forceinline hkSimulationIsland* hkGetIslandFromAgentEntry(hkAgentNnEntry* entry)
{
	hkLinkedCollidableStub* c0 = entry->m_collidable[0];
	hkSimulationIsland* island = ((hkEntity*)((char*)c0 + c0->m_ownerOffset))->m_simulationIsland;
	if (island->m_storageIndex == 0xffff)
	{
		hkLinkedCollidableStub* c1 = entry->m_collidable[1];
		island = ((hkEntity*)((char*)c1 + c1->m_ownerOffset))->m_simulationIsland;
	}
	return island;
}

// ===========================================================================================================================

// @ 0x010a1320
void hkWorldOperationUtil::splitSimulationIslands(hkWorld* world)
{
	if (!world->m_wantSimulationIslands)
		return;

	for (int i = world->m_activeSimulationIslands.m_size - 1; i >= 0; i--)
	{
		hkSimulationIsland* island = world->m_activeSimulationIslands.m_data[i];
		if (!island->m_splitCheckRequested)
			continue;
		island->m_splitCheckRequested = 0;

		hkLocalArray<int> parents(island->m_entitiesSize);
		hkUnionFind unionFind(parents, island->m_entitiesSize);
		hkBool fullyConnected = island->isFullyConnected(unionFind);
		if (fullyConnected)
			continue;

		hkTimerBeginList("Ltsplit", "createGroups");

		// groupSizes[g] = number of entities in group g; group 0 stays in the original island.
		hkInplaceArrayD<int, 32> groupSizes;
		unionFind.assignGroups(groupSizes);
		int numEntitiesInGroup0 = groupSizes.m_data[0];
		int numEntities = island->m_entitiesSize;

		hkInplaceArrayD<hkSimulationIsland*, 32> newIslands;
		newIslands.pushBack(island);

		for (int g = 1; g < groupSizes.m_size; g++)
		{
			hkSimulationIsland* ni = new hkSimulationIsland(world);
			world->m_activeSimulationIslands.pushBack(ni);
			ni->m_storageIndex = (hkUint16)(world->m_activeSimulationIslands.m_size - 1);
			newIslands.pushBack(ni);
			int need = groupSizes.m_data[g];
			if ((ni->m_entitiesCapacityAndFlags & HK_ARRAY_CAPACITY_MASK) < need)
				hkArrayUtil::_reserveExactly(&ni->m_entitiesData, need, 4);
		}

		// move the entities (and their constraints) to their new islands
		hkEntity** oldEntities = island->m_entitiesData;
		int oldNum = island->m_entitiesSize;
		island->m_entitiesSize = 0;
		for (int j = 0; j < oldNum; j++)
		{
			hkSimulationIsland* ni = newIslands.m_data[parents.m_data[j]];
			hkEntity* entity = oldEntities[j];
			entity->m_simulationIsland = ni;
			entity->m_storageIndex = (hkUint16)ni->m_entitiesSize;
			hkArray<hkEntity*>& niEntities = *(hkArray<hkEntity*>*)&ni->m_entitiesData;
			niEntities.pushBack(entity);
			if (island != ni)
			{
				int sz = entity->m_motion->getSolverSize();
				island->m_sumSizeOfMotions -= sz;
				ni->m_sumSizeOfMotions += sz;
				hkConstraintInternal* ci = entity->m_constraintsMasterData;
				for (int k = 0; k < entity->m_constraintsMasterSize; k++, ci++)
				{
					hkConstraintInfo info;
					ci->m_data->getConstraintInfo(info);
					island->subConstraintInfo(info);
					info.m_maxSizeOfJacobians = island->m_maxSizeOfJacobians;
					ni->addConstraintInfo(info);
					ci->m_constraint->m_owner = ni;
				}
			}
		}

		// move the actions: they go to the island of their entities (the first non-fixed one)
		hkSimulationIsland* fixedIsland = world->m_fixedIsland;
		hkAction** oldActions = island->m_actionsData;
		int oldNumActions = island->m_actionsSize;
		island->m_actionsSize = 0;
		for (int k = 0; k < oldNumActions; k++)
		{
			hkAction* action = oldActions[k];
			if (!action)
				continue;
			hkSimulationIsland* actionIsland;
			{
				hkInplaceArrayD<hkEntity*, 16> entities;
				action->getEntities(entities);
				actionIsland = 0;
				for (int e = 0; e < entities.m_size; e++)
				{
					actionIsland = entities.m_data[e]->m_simulationIsland;
					if (actionIsland != fixedIsland)
						break;
				}
			}
			action->m_island = actionIsland;
			hkArray<hkAction*>& acts = *(hkArray<hkAction*>*)&actionIsland->m_actionsData;
			acts.pushBack(action);
		}

		// move the agents
		if ((numEntities - numEntitiesInGroup0) * 8 < numEntities)
		{
			// few entities leave: move the affected agents one by one
			hkAgentNnTrack& track = island->m_agentTrack;
			int sectorIndex = 0;
			while (sectorIndex < track.m_sectors.m_size)
			{
				char* sectorStart = track.m_sectors.m_data[sectorIndex];
				hkAgentNnEntry* entry = (hkAgentNnEntry*)sectorStart;
				int next = sectorIndex + 1;
				for (;;)
				{
					unsigned used = (next == track.m_sectors.m_size) ? track.m_bytesUsedInLastSector : track.m_sectorSize;
					if ((char*)entry >= sectorStart + used)
						break;
					hkSimulationIsland* agentIsland = hkGetIslandFromAgentEntry(entry);
					if (agentIsland == island)
					{
						entry = (hkAgentNnEntry*)((char*)entry + entry->m_size);
						continue;
					}
					hkAgentNnTrack_appendCopy(&agentIsland->m_agentTrack, entry);
					hkAgentNnTrack_remove(&track, entry);
					if (sectorIndex < track.m_sectors.m_size)
						continue;
					break;
				}
				sectorIndex = next;
			}
		}
		else
		{
			// many entities leave: take the whole track away and redistribute every agent
			hkCollisionDispatcher* disp = world->m_collisionDispatcher;
			hkAgentNnTrack oldTrack;
			hkUint16 sectorSize = (hkUint16)disp->m_agent3SectorSize;
			oldTrack.m_bytesUsedInLastSector = sectorSize;
			oldTrack.m_agentSize = (hkUint16)disp->m_agent3AgentSize;
			oldTrack.m_sectorSize = sectorSize;

			hkAgentNnTrack& track = island->m_agentTrack;
			int n = track.m_sectors.m_size;
			if (n == 1)
			{
				oldTrack.m_sectors.m_storage[0] = track.m_sectors.m_data[0];
				track.m_sectors.m_size = 0;
				oldTrack.m_sectors.m_size = n;
			}
			else if (n > 0)
			{
				hkArrayUtil::_reserveExactly(&oldTrack.m_sectors, 2, 4);
				char** d = oldTrack.m_sectors.m_data;
				int c = oldTrack.m_sectors.m_size;
				int cf = oldTrack.m_sectors.m_capacityAndFlags;
				oldTrack.m_sectors.m_data = track.m_sectors.m_data;
				oldTrack.m_sectors.m_capacityAndFlags = track.m_sectors.m_capacityAndFlags;
				track.m_sectors.m_data = d;
				track.m_sectors.m_size = c;
				track.m_sectors.m_capacityAndFlags = cf;
				oldTrack.m_sectors.m_size = n;
			}
			unsigned used0 = track.m_bytesUsedInLastSector;
			track.m_bytesUsedInLastSector = oldTrack.m_bytesUsedInLastSector;
			oldTrack.m_bytesUsedInLastSector = used0;

			for (int s = 0; s < oldTrack.m_sectors.m_size; )
			{
				char* sector = oldTrack.m_sectors.m_data[s];
				s++;
				unsigned used = (s == oldTrack.m_sectors.m_size) ? oldTrack.m_bytesUsedInLastSector : oldTrack.m_sectorSize;
				for (hkAgentNnEntry* e = (hkAgentNnEntry*)sector; e < (hkAgentNnEntry*)(sector + used); e = (hkAgentNnEntry*)((char*)e + e->m_size))
					hkAgentNnTrack_appendCopy(&hkGetIslandFromAgentEntry(e)->m_agentTrack, e);
				hkMemory::s_instance->deallocateChunk(sector, oldTrack.m_sectorSize, 0x24);
			}
		}

		{
			hkArray<char*>& sectors = island->m_agentTrack.m_sectors;
			if ((sectors.m_capacityAndFlags & (int)0x80000000) == 0)
				if (sectors.m_size < 1 || sectors.m_size * 2 < (sectors.m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK))
					hkArrayUtil_reduce(&sectors, 4, (char*)&sectors + 0xc, 1);
		}
	}
}

// ===========================================================================================================================
// Declarations for the rest of the slice (all defined below).
// ===========================================================================================================================

class hkMotion;

// hkWorld::removeConstraint(hkConstraintInstance**, hkConstraintInstance*) -- 0x01086E90 (thiscall: ecx = world).
class hkWorldView
{
public:
	void removeConstraint(hkConstraintInstance** outSlot, hkConstraintInstance* constraint);   // 0x01086E90
};

// hkArrayUtil::_reserveMore(hkArrayBase*, int elemSize) -- 0x0107F530.
void hkArrayUtil_reserveMore(void* arrayBase, int elemSize);                      // 0x0107F530

// Motion owning a solver-size query: vtable slot 7 (+0x1c) returns the solver size.
class hkMotionSized
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6();
	virtual int getSolverSize();                                   // 7 (+0x1c)
};

// Deactivation check helpers carried by an entity at +0x6c (vtable slots +8 / +0xc).
// Both get the entity and return hkBool (hidden return pointer), exactly as the binary calls them.
class hkEntityDeactivator
{
public:
	virtual void s0(); virtual void s1();
	virtual hkBool isDeactivating(hkEntity* entity);               // 2 (+8)
	virtual hkBool isDeactivatingLow(hkEntity* entity);            // 3 (+0xc)
};

// hkSimulationIsland::addMotionInfo / subMotionInfo (plain members; the vtable slots live on the island).
struct hkSimpleConstraintOwner
{
	int m_sumSizeOfMotions;                                        // +0x14
};

// hkSimulationIsland: the full member set used by this slice (0x010a2000..0x010a22a3).
class hkSimulationIslandFull
{
public:
	virtual void v0();                                                 // +0
	virtual void v1();                                                 // +4 (0x010a2000 removeConstraint)
	virtual void v2();                                                 // +8
	virtual void v3();                                                 // +0xc
	virtual void v4();                                                 // +0x10
	virtual void addMotionInfo(int n);                                 // +0x14
	hkInt16 m_memSizeAndFlags;                                         // +4
	hkInt16 m_referenceCount;                                          // +6
	int m_maxSizeOfJacobians;                                          // +8
	int m_sizeOfJacobians;                                             // +0xc
	int m_sizeOfSchemas;                                               // +0x10
	int m_sumSizeOfMotions;                                            // +0x14
	int m_numSolverResults;                                            // +0x18
	hkWorld* m_world;                                                  // +0x1c
	hkUint16 m_storageIndex;                                           // +0x20
	hkUint16 m_dirtyListIndex;                                         // +0x22
	hkUint8 m_highFrequencyCounter;                                    // +0x24
	hkUint8 m_lowFrequencyCounter;                                     // +0x25
	hkUint8 m_splitCheckRequested;                                     // +0x26
	hkUint8 m_actionListCleanupNeeded;                                 // +0x27
	char m_pad28[0x34 - 0x28];
	float m_highFrequencyDeactivationTime;                             // +0x34
	float m_lowFrequencyDeactivationTime;                              // +0x38
	hkEntity** m_entitiesData;                                         // +0x3c
	int m_entitiesSize;                                                // +0x40
	int m_entitiesCapacityAndFlags;                                    // +0x44
	hkEntity* m_entitiesInplace[1];                                    // +0x48
	hkAgentNnTrack m_agentTrack;                                       // +0x4c
	hkAction** m_actionsData;                                          // +0x64
	int m_actionsSize;                                                 // +0x68
	int m_actionsCapacityAndFlags;                                     // +0x6c
	float m_timeOfDeactivation;                                        // +0x70

	void removeConstraint(hkConstraintInstance* c);                    // 0x010a2000
	void subMotionInfo(int n);                                         // 0x010a2030
	void internalRemoveEntity(hkEntity* e);                            // 0x010a2040
	bool removeAction(hkAction* a);                                    // 0x010a20b0
	hkBool shouldDeactivate(const hkStepInfo& step);                   // 0x010a20f0
	void internalAddEntity(hkEntity* e);                               // 0x010a2250
};

// Entity motion accessor used by internalAddEntity / internalRemoveEntity (slot 7 = solver size).
static __forceinline int hkEntity_getSolverSize(hkEntity* e)
{
	return ((hkMotionSized*)e->m_motion)->getSolverSize();
}

// ===========================================================================================================================

// @ 0x010a2000
void hkSimulationIslandFull::removeConstraint(hkConstraintInstance* c)
{
	((hkWorldView*)m_world)->removeConstraint(&c, c);
}

// @ 0x010a2020
void hkSimulationIslandFull::addMotionInfo(int n)
{
	m_sumSizeOfMotions += n;
}

// @ 0x010a2030
void hkSimulationIslandFull::subMotionInfo(int n)
{
	m_sumSizeOfMotions -= n;
}

// @ 0x010a2040
void hkSimulationIslandFull::internalRemoveEntity(hkEntity* e)
{
	hkArray<hkEntity*>& ents = *(hkArray<hkEntity*>*)&m_entitiesData;
	ents.m_data[e->m_storageIndex] = ents.m_data[ents.m_size - 1];
	ents.m_data[e->m_storageIndex]->m_storageIndex = e->m_storageIndex;
	ents.m_size--;
	e->m_simulationIsland = 0;
	e->m_storageIndex = 0xffff;
	addMotionInfo(-hkEntity_getSolverSize(e));
	m_splitCheckRequested = 1;
}

// @ 0x010a20b0
bool hkSimulationIslandFull::removeAction(hkAction* a)
{
	int index = 0;
	int size = m_actionsSize;
	if (size > 0)
	{
		hkAction** p = m_actionsData;
		do
		{
			if (*p == a)
				goto found;
			++index;
			++p;
		} while (index < size);
	}
	index = -1;
found:
	m_actionsData[index] = 0;
	a->m_island = 0;
	m_splitCheckRequested = 1;
	m_actionListCleanupNeeded = 1;
	return true;
}

// @ 0x010a20f0
hkBool hkSimulationIslandFull::shouldDeactivate(const hkStepInfo& step)
{
	// World keeps the two deactivation time limits at +0xb8 (high freq) and +0xbc (low freq).
	float highTime = m_highFrequencyDeactivationTime + step.m_deltaTime;
	m_highFrequencyDeactivationTime = highTime;
	float lowTime = m_lowFrequencyDeactivationTime + step.m_deltaTime;
	m_lowFrequencyDeactivationTime = lowTime;

	bool highElapsed = m_highFrequencyDeactivationTime > m_world->m_highFrequencyLimit;
	bool lowElapsed = lowTime > m_world->m_lowFrequencyLimit;

	if (highElapsed)
	{
		m_highFrequencyDeactivationTime -= m_world->m_highFrequencyLimit;
		bool all = true;
		for (int i = 0; i < m_entitiesSize; ++i)
		{
			hkEntity* e = m_entitiesData[i];
			if (e->m_deactivator == 0 || !e->m_deactivator->isDeactivating(e))
				all = false;
		}
		if (all)
		{
			m_highFrequencyCounter++;
			if (m_highFrequencyCounter >= 5)
			{
				m_highFrequencyCounter = 0;
				return hkBool(true);
			}
		}
		else
		{
			m_highFrequencyCounter = 0;
			return hkBool(false);
		}
	}
	else if (lowElapsed)
	{
		m_lowFrequencyDeactivationTime = lowTime - m_world->m_lowFrequencyLimit;
		bool all = true;
		for (int i = 0; i < m_entitiesSize; ++i)
		{
			if (m_entitiesData[i]->m_deactivator == 0 ||
				!m_entitiesData[i]->m_deactivator->isDeactivatingLow(m_entitiesData[i]))
				all = false;
		}
		if (all)
		{
			m_lowFrequencyCounter++;
			if (m_lowFrequencyCounter >= 5)
			{
				m_lowFrequencyCounter = 0;
				return hkBool(true);
			}
		}
		else
		{
			m_lowFrequencyCounter = 0;
			return hkBool(false);
		}
	}

	return hkBool(false);
}

// @ 0x010a2250
void hkSimulationIslandFull::internalAddEntity(hkEntity* e)
{
	e->m_simulationIsland = (hkSimulationIsland*)this;
	e->m_storageIndex = (hkUint16)m_entitiesSize;
	hkArray<hkEntity*>& ents = *(hkArray<hkEntity*>*)&m_entitiesData;
	if (ents.m_size == (ents.m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK))
		hkArrayUtil_reserveMore(&ents, 4);
	ents.m_data[ents.m_size++] = e;
	addMotionInfo(hkEntity_getSolverSize(e));
}

// @ 0x010a1b30
void hkWorldOperationUtil::setRigidBodyMotionType(hkRigidBody* body, hkMotion::MotionType newState,
                                                   hkEntityActivation activation,
                                                   hkUpdateCollisionFilterOnEntityMode mode)
{
	hkMotion::MotionType oldState = (hkMotion::MotionType)body->m_motion->getType();
	if (oldState == newState)
		return;

	hkBoolArg newNeedsInertia(newState != hkMotion::MOTION_FIXED && newState != hkMotion::MOTION_KEYFRAMED);
	hkBoolArg oldNeedsInertia(oldState != hkMotion::MOTION_FIXED && oldState != hkMotion::MOTION_KEYFRAMED);
	if (newNeedsInertia && !oldNeedsInertia && body->m_motion->m_savedMotion == 0)
		return;

	body->addReference();
	hkWorld* world = body->m_world;

	if (world != 0 && (oldState == hkMotion::MOTION_FIXED) != (newState == hkMotion::MOTION_FIXED))
	{
		hkAgentNnTrack agentsRemoved;
		hkInplaceArrayD<hkConstraintInstance*, 16> constraintsToBeMoved;
		hkInplaceArrayD<hkAction*, 16> actionsToBeMoved;

		world->m_blockExecutingPendingOperations = 1;
		world->m_criticalOperationsAllowed = 0;

		hkCollisionDispatcher* dispatcher = world->m_collisionDispatcher;
		agentsRemoved.m_agentSize = dispatcher->m_agent3AgentSize;
		agentsRemoved.m_sectorSize = dispatcher->m_agent3SectorSize;
		agentsRemoved.m_bytesUsedInLastSector = agentsRemoved.m_sectorSize;

		removeAttachedConstraints(body, constraintsToBeMoved);
		if (newState != hkMotion::MOTION_FIXED)
			removeAttachedActionsFromFixedIsland(world, body, actionsToBeMoved);
		else
			removeAttachedActionsFromDynamicIsland(world, body, actionsToBeMoved);

		removeAttachedAgentsConnectingTheEntityAndAFixedPartnerEntityPlus(
			body->m_simulationIsland->m_agentTrack, body, agentsRemoved, newState);

		if (oldState != hkMotion::MOTION_FIXED && body->m_simulationIsland->m_entitiesSize > 2)
			body->m_simulationIsland->m_splitCheckRequested = 1;

		removeEntitySI(world, body);
		replaceMotionObject(body, newState, newNeedsInertia, oldNeedsInertia, world);
		addEntitySI(world, body, activation);
		addActionsToEntitysIsland(world, body, actionsToBeMoved);
		world->m_criticalOperationsAllowed = 1;

		for (int i = 0; i < constraintsToBeMoved.m_size; ++i)
		{
			hkConstraintInstance* constraint = constraintsToBeMoved.m_data[i];
			constraint->fixNullEntities();
			if (world->m_lockCount != 0)
				hkWorldConstraintUtil::addConstraint(world, constraint);
			else
			{
				world->m_lockCount = 1;
				hkWorldConstraintUtil::addConstraint(world, constraint);
				if (--world->m_lockCount == 0 && world->m_pendingOperationsCount != 0 &&
					!world->m_blockExecutingPendingOperations)
					world->executePendingOperations();
			}
			constraint->removeReference();
		}

		if (newState != hkMotion::MOTION_FIXED)
		{
			for (int i = 0; i < body->m_collisionEntries.m_size; ++i)
			{
				hkCollisionEntry& entry = body->m_collisionEntries.m_data[i];
				hkEntity* partner = (hkEntity*)((char*)entry.m_partner + entry.m_partner->m_ownerOffset);
				if (!body->m_isFixed && !partner->m_isFixed &&
					body->m_simulationIsland != partner->m_simulationIsland)
					mergeIslands(body->m_world, body, partner);
			}
		}

		hkAgentNnMachine_AppendTrack(&body->m_simulationIsland->m_agentTrack, &agentsRemoved);

		if (newState == hkMotion::MOTION_FIXED)
		{
			hkSweptTransformUtil::freezeMotionState(world->m_dynamicsStepInfo.m_stepInfo.m_startTime,
			                                        body->m_motion->m_motionState);
			world->m_lockCount++;
			hkDiscreteSimulation::collideEntitiesBroadPhaseDiscrete((hkEntity**)&body, 1, world);
			world->m_simulation->collideEntities((hkEntity**)&body, 1, world);
			hkWorldCallbackUtil::fireInactiveEntityMoved(world, body);
			world->m_lockCount--;
		}

		world->updateCollisionFilterOnEntity(body, mode, 1);
		world->m_blockExecutingPendingOperations = 0;		if (world->m_lockCount == 0 && world->m_pendingOperationsCount != 0)
			world->executePendingOperations();

		body->removeReference();
		return;
	}

	replaceMotionObject(body, newState, newNeedsInertia, oldNeedsInertia, world);
	if (world != 0)
	{
		world->m_criticalOperationsAllowed = 0;
		if (world->m_simulationType >= 4 && newState == hkMotion::MOTION_KEYFRAMED)
			FUN_010a08b0(world->m_simulation, body);
		world->m_criticalOperationsAllowed = 1;
		world->updateCollisionFilterOnEntity(body, mode, 1);
	}
	body->removeReference();
}
