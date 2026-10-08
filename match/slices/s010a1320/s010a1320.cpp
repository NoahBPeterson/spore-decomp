// Havok 3.1.0 slice s010a1320: hkWorldOperationUtil::splitSimulationIslands (0x010a1320, 2052 bytes).
//
// For every active island whose "split check" flag is set, builds a union-find over its entities, and if the
// island is not fully connected distributes the entities, constraints, actions and agents over new islands.
// Struct stubs carry members at the x86 offsets of the 32-bit binary (comments); VC .NET 2003 build (/vc71).
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP
#include "../s010cbaa0/hk31_b005.h"
#include <new>

typedef uint16_t hkUint16;
typedef uint8_t hkUint8;

class hkWorld;
class hkSimulationIsland;
class hkEntity;
class hkUnionFind;
struct hkAgentNnEntry;
struct hkConstraintInstance;

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
struct hkConstraintData
{
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void getConstraintInfo(hkConstraintInfo& out) const;   // 8 (+0x20)
};
struct hkConstraintInstance { char m_pad0[8]; hkSimulationIsland* m_owner; };   // +8
struct hkConstraintInternal                                     // 0x1c bytes
{
	hkConstraintInstance* m_constraint;                         // +0
	char m_pad4[0xc - 4];
	hkConstraintData* m_data;                                   // +0xc
	char m_pad10[0x1c - 0x10];
};

class hkMotion
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6();
	virtual int getSolverSize();                                // 7 (+0x1c)
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

class hkEntity
{
public:
	char m_pad0[0x58];
	hkMotion* m_motion;                                         // +0x58
	hkSimulationIsland* m_simulationIsland;                     // +0x5c
	char m_pad60[0x70 - 0x60];
	hkConstraintInternal* m_constraintsMasterData;              // +0x70
	int m_constraintsMasterSize;                                // +0x74
	char m_pad78[0x94 - 0x78];
	hkUint16 m_storageIndex;                                    // +0x94
};

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

class hkWorld
{
public:
	char m_pad0[0x30];
	hkSimulationIsland* m_fixedIsland;                          // +0x30
	char m_pad34[4];
	hkArray<hkSimulationIsland*> m_activeSimulationIslands;     // +0x38
	char m_pad44[0x80 - 0x44];
	hkCollisionDispatcher* m_collisionDispatcher;               // +0x80
	char m_pad84[0xb4 - 0x84];
	hkUint8 m_wantSimulationIslands;                            // +0xb4
};

struct hkWorldOperationUtil
{
	static void splitSimulationIslands(hkWorld* world);          // 0x010A1320
};

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
