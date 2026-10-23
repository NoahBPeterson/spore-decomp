// Havok 3.1.0 slice s010a07c0: hkWorldOperationUtil broad-phase bookkeeping (cleanupDirtyIslands,
// updateEntityBP / addEntityBP / addPhantomBP / removeEntityBP / removePhantomBP), the simulation-island
// action moves (removeAttachedActionsFromDynamicIsland, mergeIslands, addActionsToEntitysIsland) and
// hkSimulation::removeEntity.
// Flags: /vc71 /O2 /MD /Gy /TP
#include "../s010869e0/hk31_world.h"

// ---------------------------------------------------------------------------------------------------------
// hkThreadMemory stack allocator, hkLocalArray and an in-place array with a constructor
// ---------------------------------------------------------------------------------------------------------
struct hkThreadMemoryRaw
{
	virtual void vslot0();
	virtual void vslot1();
	virtual void vslot2();
	virtual void* onStackOverflow(int nbytes);           // +0x0c
	virtual void onStackUnderflow(void* p);               // +0x10
	uint32_t pad04[7];
	char* m_stackCurrent;                                 // +0x20
	char* m_stackPrev;                                    // +0x24
	char* m_stackBase;                                    // +0x28
	char* m_stackEnd;                                     // +0x2c
	void deallocateChunk(void* p, int nbytes, int cl);    // 0x0107DB10
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

// hkArray<T> with the Havok destructor (frees the heap block unless the DONT_DEALLOCATE flag is set).
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

// In-place array (data points at the inline storage, so the destructor never frees).
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

// ---------------------------------------------------------------------------------------------------------
// classes the shared header only forward-declares
// ---------------------------------------------------------------------------------------------------------
class hkAction : public hkReferencedObject
{
public:
	virtual void actionSlot2();
	virtual void getEntities(hkArray<hkEntity*>& entities);   // 3 (+0xc)
};

class hkPhantom : public hkWorldObject
{
public:
	virtual void phantomSlot4();
	virtual void calcAabb(hkAabb& aabb);                      // 5 (+0x14)
};

struct hkTypedBroadPhaseHandlePair { hkTypedBroadPhaseHandle* m_a; hkTypedBroadPhaseHandle* m_b; };

class hkBroadPhase
{
public:
	virtual void bpSlot0();
	virtual void bpSlot1();
	virtual void addEntity(hkTypedBroadPhaseHandle* handle, const hkAabb& aabb, hkArray<hkTypedBroadPhaseHandlePair>& pairs);   // 2 (+0x08)
	virtual void bpSlot3();
	virtual void removeEntity(hkTypedBroadPhaseHandle* handle, hkArray<hkTypedBroadPhaseHandlePair>& pairs);                      // 4 (+0x10)
	virtual void bpSlot5();
	virtual void bpSlot6();
	virtual void sweep(hkTypedBroadPhaseHandle** handles, const hkAabb& aabb, int numHandles,
	                   hkArray<hkTypedBroadPhaseHandlePair>& newPairs, hkArray<hkTypedBroadPhaseHandlePair>& lostPairs);           // 7 (+0x1c)
};

class hkTypedBroadPhaseDispatcher
{
public:
	void addPairs(hkTypedBroadPhaseHandlePair* pairs, int numPairs, const hkCollidableCollidableFilter* filter);   // 0x010CC410
	void removePairs(hkTypedBroadPhaseHandlePair* pairs, int numPairs);                                           // 0x010CC480
	static void removeDuplicates(hkArray<hkTypedBroadPhaseHandlePair>& newPairs, hkArray<hkTypedBroadPhaseHandlePair>& lostPairs);   // 0x010CC560
};

// hkSimulation's data members (the shared header only spells out its vtable).
struct hkSimulationEntityEntry
{
	uint32_t m_type;            // +0
	hkEntity* m_entityA;        // +4
	hkEntity* m_entityB;        // +8
	uint32_t m_f3, m_f4, m_f5, m_f6, m_f7, m_f8, m_f9, m_f10, m_f11, m_f12, m_f13, m_f14, m_f15;   // +0xc..+0x3f
};
struct hkSimulationArrays { hkSimulationEntityEntry* m_entries; int m_numEntries; };

// hkSimulationIsland methods the shared header does not declare.
class hkSimulationIslandX : public hkSimulationIsland
{
public:
	void addAction(hkAction* action);      // 0x010A24B0
	void removeAction(hkAction* action);   // 0x010A20B0
};

// m_broadPhaseQuerySize (+0x2e4) lies past the part of hkWorld the shared header spells out.
inline int& hkWorldBroadPhaseQuerySize(hkWorld* w) { return *(int*)((char*)w + 0x2e4); }

namespace hkWorldOperation
{
	struct UpdateEntityBP : BaseOperation { hkEntity* m_entity; };                       // type 3
	struct MergeIslands : BaseOperation { hkEntity* m_entityA; hkEntity* m_entityB; };   // type 0xc
}

class hkWorldOperationUtil
{
public:
	static void cleanupDirtyIslands(hkWorld* world);                                                                              // 0x010A07C0
	static void updateEntityBP(hkWorld* world, hkEntity* entity);                                                                  // 0x010A0970
	static void addEntityBP(hkWorld* world, hkEntity* entity);                                                                     // 0x010A0BE0
	static void addPhantomBP(hkWorld* world, hkPhantom* phantom);                                                                  // 0x010A0D10
	static void removeEntityBP(hkWorld* world, hkEntity* entity);                                                                  // 0x010A0E20
	static void removePhantomBP(hkWorld* world, hkPhantom* phantom);                                                               // 0x010A0F20
	static void removeAttachedActionsFromDynamicIsland(hkWorld* world, hkEntity* entity, hkArray<hkAction*>& actionsToBeMoved);    // 0x010A1010
	static void mergeIslands(hkWorld* world, hkEntity* entityA, hkEntity* entityB);                                                // 0x010A1170
	static void addActionsToEntitysIsland(hkWorld* world, hkEntity* entity, hkArray<hkAction*>& actions);                          // 0x010A11D0
	// callees defined in other slices
	static void internalActivateIsland(hkWorld* world, hkSimulationIsland* island);                                                // 0x0109FF50
	static void internalDeactivateIsland(hkWorld* world, hkSimulationIsland* island);                                              // 0x010A0020
	static hkSimulationIsland* internalMergeTwoIslands(hkWorld* world, hkSimulationIsland* islandA, hkSimulationIsland* islandB);  // 0x010A0410
};

// =========================================================================================================
// 0x010A07C0
// =========================================================================================================
// @ 0x010a07c0 hkWorldOperationUtil::cleanupDirtyIslands
void hkWorldOperationUtil::cleanupDirtyIslands(hkWorld* world)
{
	while (world->m_dirtySimulationIslands.m_size != 0)
	{
		hkSimulationIsland* island = world->m_dirtySimulationIslands.m_data[world->m_dirtySimulationIslands.m_size - 1];
		world->m_dirtySimulationIslands.m_size = world->m_dirtySimulationIslands.m_size - 1;
		if (island == 0)
			continue;
		island->m_dirtyListIndex = (uint16_t)0xffff;
		if (island->m_actionListCleanupNeeded)
		{
			hkArray<void*>& actions = island->m_actions;
			int write = -1;
			int read = 0;
			for (; read < actions.m_size; read++)
			{
				if (actions.m_data[read] == 0)
				{
					write = read;
					read++;
					break;
				}
			}
			for (; read < actions.m_size; read++)
			{
				if (actions.m_data[read] != 0)
					actions.m_data[write++] = actions.m_data[read];
			}
			if (write != -1)
				actions.setSize(write);
			island->m_actionListCleanupNeeded = 0;
		}
		if (island->m_active != (island->m_isInActiveIslandsArray != 0))
		{
			if (island->m_active)
				internalActivateIsland(world, island);
			else
				internalDeactivateIsland(world, island);
		}
	}
}

// =========================================================================================================
// 0x010A08B0
// =========================================================================================================
// @ 0x010a08b0 hkSimulation_removeEntity
void hkSimulation_removeEntity(hkSimulation* sim, hkEntity* entity)
{
	hkSimulationArrays& arr = *(hkSimulationArrays*)((char*)sim + 0x18);
	for (int i = 0; i < arr.m_numEntries; i++)
	{
		if (arr.m_entries[i].m_entityA == entity || arr.m_entries[i].m_entityB == entity)
		{
			arr.m_numEntries = arr.m_numEntries - 1;
			arr.m_entries[i] = arr.m_entries[arr.m_numEntries];
			i--;
		}
	}
}

// =========================================================================================================
// 0x010A0970
// =========================================================================================================
// @ 0x010a0970 hkWorldOperationUtil::updateEntityBP
void hkWorldOperationUtil::updateEntityBP(hkWorld* world, hkEntity* entity)
{
	if (world->m_lockCount != 0)
	{
		hkWorldOperation::UpdateEntityBP op;
		op.m_type = 3;
		op.m_entity = entity;
		world->queueOperation(op);
		return;
	}
	const hkShape* shape = entity->m_collidable.m_shape;
	world->m_lockCount = 1;
	if (shape != 0)
	{
		hkLocalArray<hkTypedBroadPhaseHandlePair> newPairs(hkWorldBroadPhaseQuerySize(world));
		hkLocalArray<hkTypedBroadPhaseHandlePair> lostPairs(hkWorldBroadPhaseQuerySize(world));
		hkAabb aabb;
		entity->m_collidable.m_shape->getAabb(*(const hkTransform*)entity->m_collidable.m_motion,
		                                      world->m_collisionInput->m_tolerance * 0.5f, aabb);
		hkTypedBroadPhaseHandle* handles[1];
		handles[0] = &entity->m_collidable.m_broadPhaseHandle;
		world->m_broadPhase->sweep(handles, aabb, 1, newPairs, lostPairs);
		if (newPairs.m_size + lostPairs.m_size > 0)
		{
			hkTypedBroadPhaseDispatcher::removeDuplicates(newPairs, lostPairs);
			((hkTypedBroadPhaseDispatcher*)world->m_broadPhaseDispatcher)->removePairs(lostPairs.m_data, lostPairs.m_size);
			((hkTypedBroadPhaseDispatcher*)world->m_broadPhaseDispatcher)->addPairs(newPairs.m_data, newPairs.m_size,
			    world->m_collisionFilter ? static_cast<const hkCollidableCollidableFilter*>(world->m_collisionFilter) : 0);
		}
	}
	world->m_lockCount = world->m_lockCount - 1;
	if (world->m_lockCount == 0 && world->m_pendingOperationsCount != 0 && !world->m_blockExecutingPendingOperations)
		world->executePendingOperations();
}

// =========================================================================================================
// 0x010A0BE0
// =========================================================================================================
// @ 0x010a0be0 hkWorldOperationUtil::addEntityBP
void hkWorldOperationUtil::addEntityBP(hkWorld* world, hkEntity* entity)
{
	if (entity->m_collidable.m_shape == 0)
		return;
	hkLocalArray<hkTypedBroadPhaseHandlePair> pairs(hkWorldBroadPhaseQuerySize(world));
	hkAabb aabb;
	entity->m_collidable.m_shape->getAabb(*(const hkTransform*)entity->m_collidable.m_motion,
	                                      world->m_collisionInput->m_tolerance * 0.5f, aabb);
	world->m_broadPhase->addEntity(&entity->m_collidable.m_broadPhaseHandle, aabb, pairs);
	if (pairs.m_size > 0)
		((hkTypedBroadPhaseDispatcher*)world->m_broadPhaseDispatcher)->addPairs(pairs.m_data, pairs.m_size,
		    world->m_collisionFilter ? static_cast<const hkCollidableCollidableFilter*>(world->m_collisionFilter) : 0);
}

// =========================================================================================================
// 0x010A0D10
// =========================================================================================================
// @ 0x010a0d10 hkWorldOperationUtil::addPhantomBP
void hkWorldOperationUtil::addPhantomBP(hkWorld* world, hkPhantom* phantom)
{
	hkLocalArray<hkTypedBroadPhaseHandlePair> pairs(hkWorldBroadPhaseQuerySize(world));
	hkAabb aabb;
	phantom->calcAabb(aabb);
	world->m_broadPhase->addEntity(&phantom->m_collidable.m_broadPhaseHandle, aabb, pairs);
	if (pairs.m_size != 0)
		((hkTypedBroadPhaseDispatcher*)world->m_broadPhaseDispatcher)->addPairs(pairs.m_data, pairs.m_size,
		    world->m_collisionFilter ? static_cast<const hkCollidableCollidableFilter*>(world->m_collisionFilter) : 0);
}

// =========================================================================================================
// 0x010A0E20
// =========================================================================================================
// @ 0x010a0e20 hkWorldOperationUtil::removeEntityBP
void hkWorldOperationUtil::removeEntityBP(hkWorld* world, hkEntity* entity)
{
	hkLocalArray<hkTypedBroadPhaseHandlePair> pairs(hkWorldBroadPhaseQuerySize(world));
	if (entity->m_collidable.m_shape != 0)
	{
		world->m_broadPhase->removeEntity(&entity->m_collidable.m_broadPhaseHandle, pairs);
		if (pairs.m_size > 0)
			((hkTypedBroadPhaseDispatcher*)world->m_broadPhaseDispatcher)->removePairs(pairs.m_data, pairs.m_size);
	}
}

// =========================================================================================================
// 0x010A0F20
// =========================================================================================================
// @ 0x010a0f20 hkWorldOperationUtil::removePhantomBP
void hkWorldOperationUtil::removePhantomBP(hkWorld* world, hkPhantom* phantom)
{
	hkLocalArray<hkTypedBroadPhaseHandlePair> pairs(hkWorldBroadPhaseQuerySize(world));
	world->m_broadPhase->removeEntity(&phantom->m_collidable.m_broadPhaseHandle, pairs);
	if (pairs.m_size != 0)
		((hkTypedBroadPhaseDispatcher*)world->m_broadPhaseDispatcher)->removePairs(pairs.m_data, pairs.m_size);
}

// =========================================================================================================
// 0x010A1010
// =========================================================================================================
// @ 0x010a1010 hkWorldOperationUtil::removeAttachedActionsFromDynamicIsland
void hkWorldOperationUtil::removeAttachedActionsFromDynamicIsland(hkWorld* world, hkEntity* entity, hkArray<hkAction*>& actionsToBeMoved)
{
	hkSimulationIsland* island = entity->m_simulationIsland;
	hkInplaceArrayD<hkEntity*, 16> entities;
	for (int i = 0; i < entity->m_actions.m_size; i++)
	{
		hkAction* action = (hkAction*)entity->m_actions.m_data[i];
		if (action == 0)
			continue;
		action->getEntities(entities);
		int j = 0;
		for (; j < entities.m_size; j++)
		{
			hkEntity* e = entities.m_data[j];
			if (!e->m_fixed && e != entity)
				break;
		}
		if (j < entities.m_size)
			continue;
		actionsToBeMoved.pushBack(action);
		action->addReference();
		((hkSimulationIslandX*)island)->removeAction(action);
		island->m_actionListCleanupNeeded = 1;
		if (island->m_dirtyListIndex == 0xffff)
		{
			island->m_dirtyListIndex = (uint16_t)world->m_dirtySimulationIslands.m_size;
			world->m_dirtySimulationIslands.pushBack(island);
		}
	}
}

// =========================================================================================================
// 0x010A1170
// =========================================================================================================
// @ 0x010a1170 hkWorldOperationUtil::mergeIslands
void hkWorldOperationUtil::mergeIslands(hkWorld* world, hkEntity* entityA, hkEntity* entityB)
{
	hkSimulationIsland* islandA = entityA->m_simulationIsland;
	hkSimulationIsland* islandB = entityB->m_simulationIsland;
	if (world->m_lockCount != 0)
	{
		hkWorldOperation::MergeIslands op;
		op.m_type = 0xc;
		op.m_entityA = entityA;
		op.m_entityB = entityB;
		world->queueOperation(op);
		return;
	}
	internalMergeTwoIslands(world, islandA, islandB);
}

// =========================================================================================================
// 0x010A11D0
// =========================================================================================================
// @ 0x010a11d0 hkWorldOperationUtil::addActionsToEntitysIsland
void hkWorldOperationUtil::addActionsToEntitysIsland(hkWorld* world, hkEntity* entity, hkArray<hkAction*>& actions)
{
	hkSimulationIsland* island = entity->m_simulationIsland;
	hkInplaceArrayD<hkEntity*, 16> entities;
	for (int i = 0; i < actions.m_size; i++)
	{
		hkAction* action = actions.m_data[i];
		if (island == world->m_fixedIsland)
		{
			((hkSimulationIslandX*)world->m_fixedIsland)->addAction(action);
			action->removeReference();
		}
		else
		{
			((hkSimulationIslandX*)island)->addAction(action);
			action->removeReference();
			entities.m_size = 0;
			action->getEntities(entities);
			for (int j = 0; j < entities.m_size; j++)
			{
				hkEntity* e = entities.m_data[j];
				if (!e->m_fixed && e != entity && !entity->m_fixed && e->m_simulationIsland != entity->m_simulationIsland)
					mergeIslands(e->m_world, e, entity);
			}
		}
	}
}
