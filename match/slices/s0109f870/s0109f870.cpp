// Havok 3.1.0 slice s0109f870: hkWorldOperationUtil (islands, constraints, motion replacement), the
// hkSimpleConstraintOwner info accumulators and hkWorldCallbackUtil::fireInactiveEntityMoved
// (SporeApp.exe 0x0109f870..0x010a07bf).
//
// Layout notes: struct stubs carry members at the offsets seen in the 32-bit binary (comments give the x86 byte
// offsets); pointer members make the 64-bit layout differ. Names marked "(inferred)" come from how the code uses
// a field (the Havok 6.x headers were used only as a naming hint, never for layout).
#include "../s010cbaa0/hk31_b005.h"

typedef uint16_t hkUint16;
typedef uint8_t hkUint8;

// ---- math / motion state --------------------------------------------------------------------------------------------
struct hkQuaternion { float x, y, z, w; };
struct hkMatrix3 { hkVector4 m_col0, m_col1, m_col2; };   // 0x30 bytes

struct hkSweptTransform                                   // 0x50 bytes
{
	hkVector4 m_centerOfMass0;      // +0   (w = time0)
	hkVector4 m_centerOfMass1;      // +0x10 (w = invDeltaTime)
	hkQuaternion m_rotation0;       // +0x20
	hkQuaternion m_rotation1;       // +0x30
	hkVector4 m_centerOfMassLocal;  // +0x40
};
struct hkMotionState                                      // 0xb0 bytes
{
	hkTransform m_transform;        // +0
	hkSweptTransform m_sweptTransform;   // +0x40
	hkVector4 m_deltaAngle;         // +0x90
	float m_objectRadius;           // +0xa0
	float m_linearDamping;          // +0xa4
	float m_angularDamping;         // +0xa8
	float m_pad;                    // +0xac
	hkMotionState& operator=(const hkMotionState&);       // 0x010888C0 (0xb0-byte copy)
};
struct hkSweptTransformUtil
{
	static void setTimeInformation(float time0, float time1, hkMotionState& ms);   // 0x01209B70
	static void freezeMotionState(float time, hkMotionState& ms);                  // 0x0120A570
};

// hkMotion (rigid body motion): x86 offsets. Slots used here: 0 deleting dtor, 2 getType, 11 getInertiaLocal,
// 22 setLinearVelocity, 23 setAngularVelocity, 30 getMotionStateAndVelocities.
struct hkMotion
{
	virtual void* destroy(unsigned flags);                                   // 0
	virtual void s1();
	virtual int getType() const;                                             // 2 (+8)
	virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10();
	virtual void getInertiaLocal(hkMatrix3& out) const;                      // 11 (+0x2c)
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
	virtual void s19(); virtual void s20(); virtual void s21();
	virtual void setLinearVelocity(const hkVector4& v);                      // 22 (+0x58)
	virtual void setAngularVelocity(const hkVector4& v);                     // 23 (+0x5c)
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
	virtual void getMotionStateAndVelocities(hkMotion* motionOut) const;     // 30 (+0x78)

	char m_pad8[0x10 - 8];
	hkMotionState m_motionState;     // +0x10
	float getMass() const;           // 0x01088270 (hkRigidMotion::getMass: 0 if inverse mass is 0, else 1/inverseMass)
	// members behind the motion state (inverse mass at +0xc0, saved motion at +0xf0, ...) are read through the
	// HK_MOTION_* accessors below
};
// Raw field access for members behind the stub padding (x86 offsets).
#define HK_MOTION_F32(m, off)  (*(float*)((char*)(m) + (off)))
#define HK_MOTION_U32(m, off)  (*(uint32_t*)((char*)(m) + (off)))
#define HK_MOTION_PTR(m, off)  (*(hkMotion**)((char*)(m) + (off)))

struct hkFixedRigidMotion { static hkMotion* construct(void* mem, const hkVector4& position, const hkQuaternion& rotation); };       // ctor @ 0x01097110
struct hkKeyframedRigidMotion { static hkMotion* construct(void* mem, const hkVector4& position, const hkQuaternion& rotation); };    // ctor @ 0x01095B60
// 0x01087290 (name unknown): builds a new motion of the requested MotionType from the old one's data.
hkMotion* hkRigidBody_createMotion(int motionType, const hkVector4& position, const hkQuaternion& rotation, float mass, const hkMatrix3& inertiaLocal,
                          const hkVector4& centerOfMassLocal, float linearDamping, float angularDamping);

// ---- world objects ---------------------------------------------------------------------------------------------------
struct hkWorld;
struct hkSimulationIsland;
struct hkAgentNnEntry;
struct hkConstraintInstance;
struct hkAction;
struct hkEntity;

// Agent track (hkAgentNnTrack): opaque here; the two helpers append a copy of an entry / remove an entry.
struct hkAgentNnTrack { char m_pad[0x24]; };
void hkAgentNnTrack_appendCopy(hkAgentNnTrack* track, hkAgentNnEntry* entry);   // 0x010FBD10 (name inferred)
void hkAgentNnTrack_remove(hkAgentNnTrack* track, hkAgentNnEntry* entry);       // 0x010FBC50 (name inferred)
void hkAgentNnMachine_AppendTrack(hkAgentNnTrack* dst, hkAgentNnTrack* src);    // 0x010FC090
struct hkWorldAgentUtil
{
	static hkSimulationIsland* getIslandFromAgentEntry(hkAgentNnEntry* entry, hkSimulationIsland* a, hkSimulationIsland* b);   // 0x010A3810 (6.x name)
	static void warpTime(hkSimulationIsland* island, float oldTime, float newTime, struct hkCollisionInputStub* input);       // 0x010A38C0 (6.x name)
};
struct hkCollisionInputStub { char m_pad[1]; };

struct hkCollidable { char m_pad0[0x10]; int m_ownerOffset; };   // +0x10: offset from the collidable to its owner entity
struct hkCollisionEntry { hkAgentNnEntry* m_agentEntry; hkCollidable* m_partner; };   // 8 bytes (32-bit)

struct hkConstraintInternalStub { hkConstraintInstance* m_constraint; char m_pad[0x1c - 4]; };   // 0x1c bytes per entry

struct hkEntity
{
	char m_pad0[8];
	hkWorld* m_world;                                   // +8
	char m_pad1[0x24 - 0xc];
	hkMotionState* m_motionStatePtr;                    // +0x24
	char m_pad2[0x36 - 0x28];
	hkUint16 m_broadPhaseHandleType;                    // +0x36 (inferred; 1 = fixed, 2 = moving)
	char m_pad3[0x40 - 0x38];
	hkCollisionEntry* m_collisionEntriesData;           // +0x40
	int m_collisionEntriesSize;                         // +0x44
	char m_pad4[0x58 - 0x48];
	hkMotion* m_motion;                                 // +0x58
	hkSimulationIsland* m_island;                       // +0x5c
	char m_pad5[0x70 - 0x60];
	hkConstraintInternalStub* m_constraintsMasterData;  // +0x70
	int m_constraintsMasterSize;                        // +0x74
	int m_constraintsMasterCap;                         // +0x78
	hkConstraintInstance** m_constraintsSlaveData;      // +0x7c
	int m_constraintsSlaveSize;                         // +0x80
	char m_pad6[0x94 - 0x84];
	hkUint16 m_storageIndex;                            // +0x94 (index inside the island's entity array)
	char m_pad7[0x99 - 0x96];
	hkUint8 m_isFixed;                                  // +0x99
	hkUint8 m_isFixedOrKeyframed;                       // +0x9a
	char m_pad8[0xc0 - 0x9b];
	hkAction** m_actionsData;                           // +0xc0
	int m_actionsSize;                                  // +0xc4
};

struct hkSimpleConstraintOwner
{
	virtual void* destroy(unsigned flags);               // 0 (scalar deleting destructor)
	virtual void v1(); virtual void v2();
	virtual void addConstraintInfo(hkConstraintInstance* c, struct hkConstraintInfo& info);   // 3, 0x0109F9C0
	virtual void subConstraintInfo(hkConstraintInstance* c, struct hkConstraintInfo& info);   // 4, 0x0109F900
	int m_pad4;                                         // +4
	int m_maxSizeOfJacobians;                           // +8
	int m_sizeOfJacobians;                              // +0xc
	int m_sizeOfSchemas;                                // +0x10
	int m_numMotionInfo;                                // +0x14 (inferred, addMotionInfo/subMotionInfo)
	int m_numSolverResults;                             // +0x18
};
struct hkConstraintInfo { int m_maxSizeOfJacobians, m_sizeOfJacobians, m_sizeOfSchemas, m_numSolverResults; };

struct hkAction
{
	char m_pad0[4];
	hkUint16 m_memSizeAndFlags;                         // +4
	hkUint16 m_referenceCount;                          // +6
	char m_pad1[4];
	hkSimulationIsland* m_island;                       // +0xc
};

struct hkSimulationIsland : hkSimpleConstraintOwner
{
	hkWorld* m_world;                                   // +0x1c
	hkUint16 m_storageIndex;                            // +0x20
	hkUint16 m_dirtyListIndex;                          // +0x22 (0xffff = not on the dirty list)
	hkUint8 m_activeCounter0;                           // +0x24 (inferred, merged with min())
	hkUint8 m_activeCounter1;                           // +0x25 (inferred, merged with min())
	hkUint8 m_actionListCleanupNeeded;                  // +0x26
	hkUint8 m_splitCheckRequested;                      // +0x27
	hkUint8 m_activeMark;                               // +0x28 (inferred)
	hkUint8 m_active;                                   // +0x29 (1 = in the world's active islands array)
	char m_pad2a[0x34 - 0x2a];
	int m_pad34;                                        // +0x34 cleared on activation (inferred timers)
	int m_pad38;                                        // +0x38
	hkEntity** m_entitiesData;                          // +0x3c
	int m_entitiesSize;                                 // +0x40
	int m_entitiesCap;                                  // +0x44
	char m_pad48[0x4c - 0x48];
	hkAgentNnTrack m_agentTrack;                        // +0x4c (data, size, cap, inplace, bytes used, stride...)
	// the remaining fields (+0x64 actions array, +0x70 time) are addressed through the accessor macros below
};
// x86 offsets for the island members behind the agent track.
#define HK_ISLAND_ACTIONS_DATA(i)  (*(hkAction***)((char*)(i) + 0x64))
#define HK_ISLAND_ACTIONS_SIZE(i)  (*(int*)((char*)(i) + 0x68))
#define HK_ISLAND_ACTIONS_CAP(i)   (*(int*)((char*)(i) + 0x6c))
#define HK_ISLAND_TIME(i)          (*(float*)((char*)(i) + 0x70))
#define HK_ISLAND_AGENT_TRACK(i)   ((hkAgentNnTrack*)((char*)(i) + 0x4c))

struct hkEntityListenerStub { virtual void v0(); virtual void v1(); virtual void inactiveEntityMovedCallback(hkEntity* entity); };   // slot 2

struct hkWorld
{
	char m_pad0[0xc];
	float m_currentTime;                                // +0xc (inferred)
	char m_pad1[0x30 - 0x10];
	hkSimulationIsland* m_fixedIsland;                  // +0x30
	hkEntity* m_fixedRigidBody;                         // +0x34
	hkArray<hkSimulationIsland*> m_activeSimulationIslands;     // +0x38
	hkArray<hkSimulationIsland*> m_inactiveSimulationIslands;   // +0x44
	hkArray<hkSimulationIsland*> m_dirtySimulationIslands;      // +0x50
	char m_pad2[0x78 - 0x5c];
	hkCollisionInputStub* m_collisionInput;             // +0x78
	char m_pad3[0x88 - 0x7c];
	int m_pendingOperationQueueCount;                   // +0x88 (inferred)
	int m_criticalOperationsLockCount;                  // +0x8c
	char m_pad4[0x94 - 0x90];
	hkUint8 m_blockExecutingPendingOperations;          // +0x94
	char m_pad5[0xb4 - 0x95];
	hkUint8 m_wantSimulationIslands;                    // +0xb4
	char m_pad6[0x100 - 0xb5];
	void* m_constraintListenersData;                    // +0x100 first dword of the listener array (tested for non-zero)
	char m_pad7[0x120 - 0x104];
	hkEntityListenerStub** m_entityListenersData;       // +0x120 (inferred)
	int m_entityListenersSize;                          // +0x124
	char m_pad8[0x170 - 0x128];
	float m_simulationTime;                             // +0x170 (hkTime, inferred)
	void executePendingOperations();                    // 0x01082BF0
};

#define HK_INLINE_ENTER_CRITICAL(world) \
	((world)->m_criticalOperationsLockCount = 1)
// hkWorld::unlockCriticalOperations-style tail: leave the lock and run queued operations when nothing else holds it.
static inline void hkWorld_leaveCritical(hkWorld* world)
{
	int n = world->m_criticalOperationsLockCount - 1;
	world->m_criticalOperationsLockCount = n;
	if (n == 0 && world->m_pendingOperationQueueCount != 0 && world->m_blockExecutingPendingOperations == 0)
		world->executePendingOperations();
}

struct hkWorldConstraintUtil
{
	static void addConstraint(hkWorld* world, hkConstraintInstance* c);        // 0x010A6860
	static void removeConstraint(hkConstraintInstance* c);                     // 0x010A6640
};
struct hkWorldCallbackUtil
{
	static void fireInactiveEntityMoved(hkWorld* world, hkEntity* entity);     // 0x0109F870
	static void fireConstraintAdded(hkWorld* world, hkConstraintInstance* c);  // 0x0109EF20
	static void fireConstraintRemoved(hkWorld* world, hkConstraintInstance* c);// 0x0109EFB0
	static void fireIslandActivated(hkWorld* world, hkSimulationIsland* i);    // 0x0109F300
	static void fireIslandDeactivated(hkWorld* world, hkSimulationIsland* i);  // 0x0109F450
};
void hkConstraintInstance_fixNullEntities(hkConstraintInstance* c);            // 0x0108BFF0 (name inferred): empty entity slot := world's fixed rigid body
extern hkVector4 g_hkVector4Zero;                                              // 0x016E42D0 (static zero vector, set up elsewhere)

// hkSimulationIsland methods implemented elsewhere (names: 0x010A2040 is named in the binary, the other two inferred).
void hkSimulationIsland_internalAddEntity(hkSimulationIsland* island, hkEntity* e);   // 0x010A2250 (thiscall)
void hkSimulationIsland_internalRemoveEntity(hkSimulationIsland* island, hkEntity* e);// 0x010A2040 (thiscall)
void hkSimulationIsland_removeAction(hkSimulationIsland* island, hkAction* a);        // 0x010A20B0 (thiscall, name inferred)
void hkSimulationIsland_construct(void* mem, hkWorld* world);                          // 0x010A2810 (ctor, thiscall)

// ---- hkWorldOperationUtil ---------------------------------------------------------------------------------------------
struct hkWorldOperationUtil
{
	static hkConstraintInstance* addConstraintImmediately(hkWorld* world, hkConstraintInstance* constraint, int fireCallbacks);   // 0x0109F930
	static void removeConstraintImmediately(hkWorld* world, hkConstraintInstance* constraint, int fireCallbacks);                  // 0x0109FA10
	static void removeAttachedAgentsConnectingTheEntityAndAFixedPartnerEntityPlus(hkAgentNnTrack& trackToScan, hkEntity* entity,
	                                                                              hkAgentNnTrack& agentsRemoved, int newMotionType);   // 0x0109FAB0
	static void removeIslandFromDirtyList(hkWorld* world, hkSimulationIsland* island);   // 0x0109FB40
	static void addEntitySI(hkWorld* world, hkEntity* entity, int initialActivationState);   // 0x0109FB70
	static void removeAttachedActionsFromFixedIsland(hkWorld* world, hkEntity* entity, hkArray<hkAction*>& actionsToBeMoved);   // 0x0109FC70
	static void removeIsland(hkWorld* world, hkSimulationIsland* island);                // 0x0109FD50
	static void removeAttachedConstraints(hkEntity* entity, hkArray<hkConstraintInstance*>& constraintsToBeMoved);   // 0x0109FDD0
	static void internalActivateIsland(hkWorld* world, hkSimulationIsland* island);      // 0x0109FF50
	static void internalDeactivateIsland(hkWorld* world, hkSimulationIsland* island);    // 0x010A0020
	static void markIslandInactive(hkWorld* world, hkSimulationIsland* island);          // 0x010A00E0
	static void markIslandActive(hkWorld* world, hkSimulationIsland* island);            // 0x010A0130
	static void replaceMotionObject(struct hkRigidBody* body, int newMotionType, hkBool newStateNeedsInertia, hkBool oldStateNeedsInertia, hkWorld* world);   // 0x010A0190
	static void removeEntitySI(hkWorld* world, hkEntity* entity);                        // 0x010A03C0
	static hkSimulationIsland* internalMergeTwoIslands(hkWorld* world, hkSimulationIsland* islandA, hkSimulationIsland* islandB);   // 0x010A0410
	static inline void putIslandOnDirtyList(hkWorld* world, hkSimulationIsland* island);
};

// hkRigidBody shares hkEntity's layout up to the fields used here.
struct hkRigidBody : hkEntity {};

static inline void hkWorldOperationUtil_pushIsland(hkArray<hkSimulationIsland*>& a, hkSimulationIsland* island)
{
	if (a.m_size == (a.m_capacityAndFlags & 0x3fffffff))
		hkArrayUtil::_reserveMore(&a, 4);
	a.m_data[a.m_size] = island;
	a.m_size = a.m_size + 1;
}

inline void hkWorldOperationUtil::putIslandOnDirtyList(hkWorld* world, hkSimulationIsland* island)
{
	island->m_dirtyListIndex = (hkUint16)world->m_dirtySimulationIslands.m_size;
	hkWorldOperationUtil_pushIsland(world->m_dirtySimulationIslands, island);
}

// ===========================================================================================================================

// @ 0x0109f870
void hkWorldCallbackUtil::fireInactiveEntityMoved(hkWorld* world, hkEntity* entity)
{
	for (int i = world->m_entityListenersSize - 1; i >= 0; i--)
	{
		hkEntityListenerStub* l = world->m_entityListenersData[i];
		if (l != 0)
			l->inactiveEntityMovedCallback(entity);
	}
	// HK_UTIL_REMOVE_NULL_LISTENERS: drop the null entries (index re-read after every removal)
	for (int i = world->m_entityListenersSize - 1; i >= 0; i--)
	{
		if (world->m_entityListenersData[i] == 0)
		{
			int last = world->m_entityListenersSize - 1;
			world->m_entityListenersSize = last;
			for (int j = i; j < world->m_entityListenersSize; j++)
				world->m_entityListenersData[j] = world->m_entityListenersData[j + 1];
		}
	}
}

// @ 0x0109f900
void hkSimpleConstraintOwner::subConstraintInfo(hkConstraintInstance*, hkConstraintInfo& info)
{
	m_sizeOfJacobians -= info.m_sizeOfJacobians;
	m_sizeOfSchemas -= info.m_sizeOfSchemas;
	m_numSolverResults -= info.m_numSolverResults;
}

// @ 0x0109f930
hkConstraintInstance* hkWorldOperationUtil::addConstraintImmediately(hkWorld* world, hkConstraintInstance* constraint, int fireCallbacks)
{
	hkConstraintInstance_fixNullEntities(constraint);
	if (world->m_criticalOperationsLockCount == 0)
	{
		HK_INLINE_ENTER_CRITICAL(world);
		hkWorldConstraintUtil::addConstraint(world, constraint);
		if (fireCallbacks)
			hkWorldCallbackUtil::fireConstraintAdded(world, constraint);
		hkWorld_leaveCritical(world);
		return constraint;
	}
	hkWorldConstraintUtil::addConstraint(world, constraint);
	if (fireCallbacks)
		hkWorldCallbackUtil::fireConstraintAdded(world, constraint);
	return constraint;
}

// @ 0x0109f9c0
void hkSimpleConstraintOwner::addConstraintInfo(hkConstraintInstance*, hkConstraintInfo& info)
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

// @ 0x0109fa10
void hkWorldOperationUtil::removeConstraintImmediately(hkWorld* world, hkConstraintInstance* constraint, int fireCallbacks)
{
	if (world->m_criticalOperationsLockCount == 0)
	{
		HK_INLINE_ENTER_CRITICAL(world);
		if (fireCallbacks && world->m_constraintListenersData != 0)
			hkWorldCallbackUtil::fireConstraintRemoved(world, constraint);
		hkWorldConstraintUtil::removeConstraint(constraint);
		hkWorld_leaveCritical(world);
		return;
	}
	if (fireCallbacks && world->m_constraintListenersData != 0)
		hkWorldCallbackUtil::fireConstraintRemoved(world, constraint);
	hkWorldConstraintUtil::removeConstraint(constraint);
}

// @ 0x0109fab0
void hkWorldOperationUtil::removeAttachedAgentsConnectingTheEntityAndAFixedPartnerEntityPlus(hkAgentNnTrack& trackToScan, hkEntity* entity,
                                                                                            hkAgentNnTrack& agentsRemoved, int newMotionType)
{
	for (int i = 0; i < entity->m_collisionEntriesSize; i++)
	{
		hkCollisionEntry* entry = &entity->m_collisionEntriesData[i];
		hkEntity* partner = (hkEntity*)((char*)entry->m_partner + entry->m_partner->m_ownerOffset);
		if (partner->m_isFixed)
		{
			hkAgentNnEntry* agent = entry->m_agentEntry;
			hkAgentNnTrack_appendCopy(&agentsRemoved, agent);
			hkAgentNnTrack_remove(&trackToScan, agent);
		}
		else if (newMotionType == 7)
		{
			if (hkWorldAgentUtil::getIslandFromAgentEntry(entry->m_agentEntry, entity->m_island, partner->m_island) == entity->m_island)
			{
				hkAgentNnEntry* agent = entry->m_agentEntry;
				hkAgentNnTrack_appendCopy(HK_ISLAND_AGENT_TRACK(partner->m_island), agent);
				hkAgentNnTrack_remove(&trackToScan, agent);
			}
		}
	}
}

// @ 0x0109fb40
void hkWorldOperationUtil::removeIslandFromDirtyList(hkWorld* world, hkSimulationIsland* island)
{
	if (island->m_dirtyListIndex != 0xffff)
	{
		world->m_dirtySimulationIslands.m_data[island->m_dirtyListIndex] = 0;
		island->m_dirtyListIndex = 0xffff;
	}
}

// @ 0x0109fb70
void hkWorldOperationUtil::addEntitySI(hkWorld* world, hkEntity* entity, int initialActivationState)
{
	entity->m_world = world;
	if (entity->m_isFixed)
	{
		hkSimulationIsland_internalAddEntity(world->m_fixedIsland, entity);
		return;
	}
	if (world->m_wantSimulationIslands)
	{
		// HK_DECLARE_CLASS_ALLOCATOR: 0x74 bytes, memory class 0x2f, size recorded at +4 before the constructor runs
		void* mem = hkMemory::s_instance->allocateChunk(0x74, 0x2f);
		((hkReferencedObject*)mem)->m_memSizeAndFlags = 0x74;
		hkSimulationIsland* island = (hkSimulationIsland*)mem;
		hkSimulationIsland_construct(island, world);
		if (initialActivationState == 1)
		{
			island->m_activeMark = 1;
			island->m_active = 1;
			island->m_storageIndex = (hkUint16)world->m_activeSimulationIslands.m_size;
			hkWorldOperationUtil_pushIsland(world->m_activeSimulationIslands, island);
		}
		else
		{
			island->m_activeMark = 0;
			island->m_active = 0;
			island->m_storageIndex = (hkUint16)world->m_inactiveSimulationIslands.m_size;
			hkWorldOperationUtil_pushIsland(world->m_inactiveSimulationIslands, island);
		}
		hkSimulationIsland_internalAddEntity(island, entity);
		return;
	}
	if (initialActivationState == 1)
		hkSimulationIsland_internalAddEntity(world->m_activeSimulationIslands.m_data[0], entity);
}

// @ 0x0109fc70
void hkWorldOperationUtil::removeAttachedActionsFromFixedIsland(hkWorld* world, hkEntity* entity, hkArray<hkAction*>& actionsToBeMoved)
{
	for (int i = 0; i < entity->m_actionsSize; i++)
	{
		hkAction* action = entity->m_actionsData[i];
		if (action != 0 && action->m_island == world->m_fixedIsland)
		{
			if (actionsToBeMoved.m_size == (actionsToBeMoved.m_capacityAndFlags & 0x3fffffff))
				hkArrayUtil::_reserveMore(&actionsToBeMoved, 4);
			actionsToBeMoved.m_data[actionsToBeMoved.m_size] = action;
			actionsToBeMoved.m_size = actionsToBeMoved.m_size + 1;
			((hkReferencedObject*)action)->addReference();
			hkSimulationIsland_removeAction(world->m_fixedIsland, action);
			world->m_fixedIsland->m_splitCheckRequested = 1;
			hkSimulationIsland* fixedIsland = world->m_fixedIsland;
			if (fixedIsland->m_dirtyListIndex == 0xffff)
				hkWorldOperationUtil::putIslandOnDirtyList(world, fixedIsland);
		}
	}
}

// @ 0x0109fd50
void hkWorldOperationUtil::removeIsland(hkWorld* world, hkSimulationIsland* island)
{
	hkArray<hkSimulationIsland*>& arr = island->m_active ? world->m_activeSimulationIslands : world->m_inactiveSimulationIslands;
	arr.m_data[island->m_storageIndex] = arr.m_data[arr.m_size - 1];
	arr.m_data[island->m_storageIndex]->m_storageIndex = island->m_storageIndex;
	arr.m_size = arr.m_size - 1;
	if (island->m_dirtyListIndex != 0xffff)
	{
		world->m_dirtySimulationIslands.m_data[island->m_dirtyListIndex] = 0;
		island->m_dirtyListIndex = 0xffff;
	}
}

// @ 0x0109fdd0
void hkWorldOperationUtil::removeAttachedConstraints(hkEntity* entity, hkArray<hkConstraintInstance*>& constraintsToBeMoved)
{
	hkWorld* world = entity->m_world;
	// master constraints (0x1c-byte hkConstraintInternal entries; the instance pointer comes first), last to first
	for (int i = entity->m_constraintsMasterSize - 1; i >= 0; --i)
	{
		hkConstraintInstance* c = entity->m_constraintsMasterData[i].m_constraint;
		((hkReferencedObject*)c)->addReference();
		if (world->m_criticalOperationsLockCount == 0)
		{
			HK_INLINE_ENTER_CRITICAL(world);
			hkWorldConstraintUtil::removeConstraint(c);
			hkWorld_leaveCritical(world);
		}
		else
		{
			hkWorldConstraintUtil::removeConstraint(c);
		}
		if (constraintsToBeMoved.m_size == (constraintsToBeMoved.m_capacityAndFlags & 0x3fffffff))
			hkArrayUtil::_reserveMore(&constraintsToBeMoved, 4);
		constraintsToBeMoved.m_data[constraintsToBeMoved.m_size] = c;
		constraintsToBeMoved.m_size = constraintsToBeMoved.m_size + 1;
	}
	// slave constraints (plain pointers), last to first
	for (int i = entity->m_constraintsSlaveSize - 1; i >= 0; --i)
	{
		hkConstraintInstance* c = entity->m_constraintsSlaveData[i];
		((hkReferencedObject*)c)->addReference();
		if (world->m_criticalOperationsLockCount == 0)
		{
			HK_INLINE_ENTER_CRITICAL(world);
			hkWorldConstraintUtil::removeConstraint(c);
			hkWorld_leaveCritical(world);
		}
		else
		{
			hkWorldConstraintUtil::removeConstraint(c);
		}
		if (constraintsToBeMoved.m_size == (constraintsToBeMoved.m_capacityAndFlags & 0x3fffffff))
			hkArrayUtil::_reserveMore(&constraintsToBeMoved, 4);
		constraintsToBeMoved.m_data[constraintsToBeMoved.m_size] = c;
		constraintsToBeMoved.m_size = constraintsToBeMoved.m_size + 1;
	}
}

// @ 0x0109ff50
void hkWorldOperationUtil::internalActivateIsland(hkWorld* world, hkSimulationIsland* island)
{
	hkWorldOperationUtil_pushIsland(world->m_activeSimulationIslands, island);
	// remove from the inactive array: last element takes this one's slot
	hkArray<hkSimulationIsland*>& inactive = world->m_inactiveSimulationIslands;
	inactive.m_data[island->m_storageIndex] = inactive.m_data[inactive.m_size - 1];
	inactive.m_data[island->m_storageIndex]->m_storageIndex = island->m_storageIndex;
	inactive.m_size = inactive.m_size - 1;
	island->m_storageIndex = (hkUint16)(world->m_activeSimulationIslands.m_size - 1);
	island->m_active = 1;
	island->m_pad34 = 0;
	island->m_pad38 = 0;
	for (int i = 0; i < island->m_entitiesSize; i++)
		hkSweptTransformUtil::setTimeInformation(0.0f, 0.0f, island->m_entitiesData[i]->m_motion->m_motionState);
	hkWorldAgentUtil::warpTime(island, HK_ISLAND_TIME(island), world->m_simulationTime, world->m_collisionInput);
	hkWorldCallbackUtil::fireIslandActivated(world, island);
}

// @ 0x010a0020
void hkWorldOperationUtil::internalDeactivateIsland(hkWorld* world, hkSimulationIsland* island)
{
	hkWorldOperationUtil_pushIsland(world->m_inactiveSimulationIslands, island);
	hkArray<hkSimulationIsland*>& active = world->m_activeSimulationIslands;
	active.m_data[island->m_storageIndex] = active.m_data[active.m_size - 1];
	active.m_data[island->m_storageIndex]->m_storageIndex = island->m_storageIndex;
	active.m_size = active.m_size - 1;
	island->m_storageIndex = (hkUint16)(world->m_inactiveSimulationIslands.m_size - 1);
	island->m_active = 0;
	HK_ISLAND_TIME(island) = world->m_simulationTime;
	for (int i = 0; i < island->m_entitiesSize; i++)
	{
		hkEntity* e = island->m_entitiesData[i];
		hkSweptTransformUtil::freezeMotionState(HK_ISLAND_TIME(island), e->m_motion->m_motionState);
		e->m_motion->setLinearVelocity(g_hkVector4Zero);
		e->m_motion->setAngularVelocity(g_hkVector4Zero);
	}
	hkWorldCallbackUtil::fireIslandDeactivated(world, island);
}

// @ 0x010a00e0
void hkWorldOperationUtil::markIslandInactive(hkWorld* world, hkSimulationIsland* island)
{
	island->m_activeMark = 0;
	if (island->m_dirtyListIndex == 0xffff)
		putIslandOnDirtyList(world, island);
}

// @ 0x010a0130
void hkWorldOperationUtil::markIslandActive(hkWorld* world, hkSimulationIsland* island)
{
	island->m_activeMark = 1;
	island->m_activeCounter1 = 0;
	island->m_activeCounter0 = 0;
	if (island->m_dirtyListIndex == 0xffff)
		putIslandOnDirtyList(world, island);
}

// @ 0x010a0190
void hkWorldOperationUtil::replaceMotionObject(hkRigidBody* body, int newMotionType, hkBool newStateNeedsInertia, hkBool oldStateNeedsInertia, hkWorld* world)
{
	if (!newStateNeedsInertia)
	{
		hkMotion* oldMotion = body->m_motion;
		hkMotion* newMotion;
		void* mem = hkMemory::s_instance->allocateChunk(0x100, 0x2b);
		if (newMotionType == 7)
		{
			((hkReferencedObject*)mem)->m_memSizeAndFlags = 0x100;
			newMotion = hkFixedRigidMotion::construct(mem, body->m_motion->m_motionState.m_transform.m_trans,
			                                         *(const hkQuaternion*)&body->m_motion->m_motionState.m_sweptTransform.m_rotation1);
			newMotion->m_motionState = oldMotion->m_motionState;
			// fucompp with 0.0 + test ah,0x44 / jnp: skip only when invDeltaTime == 0 (a NaN does the freeze)
			if (!(oldMotion->m_motionState.m_sweptTransform.m_centerOfMass1.w == 0.0f))
			{
				float time;
				if (world == 0)
				{
					// X87-PRECISION: 1.0f / invDeltaTime is added to time0 unrounded, rounded at the float store.
					time = (float)((hkX87Real)1.0f / oldMotion->m_motionState.m_sweptTransform.m_centerOfMass1.w +
					               oldMotion->m_motionState.m_sweptTransform.m_centerOfMass0.w);
				}
				else
				{
					time = world->m_currentTime;
				}
				hkSweptTransformUtil::freezeMotionState(time, newMotion->m_motionState);
			}
		}
		else
		{
			((hkReferencedObject*)mem)->m_memSizeAndFlags = 0x100;
			newMotion = hkKeyframedRigidMotion::construct(mem, body->m_motion->m_motionState.m_transform.m_trans,
			                                             *(const hkQuaternion*)&body->m_motion->m_motionState.m_sweptTransform.m_rotation1);
			oldMotion->getMotionStateAndVelocities(newMotion);
		}

		if (oldStateNeedsInertia)
		{
			HK_MOTION_PTR(newMotion, 0xf0) = oldMotion;
			HK_MOTION_U32(newMotion, 0xf4) = (uint32_t)body->m_broadPhaseHandleType;
			body->m_motion = newMotion;
		}
		else
		{
			HK_MOTION_PTR(newMotion, 0xf0) = HK_MOTION_PTR(oldMotion, 0xf0);
			HK_MOTION_U32(newMotion, 0xf4) = HK_MOTION_U32(oldMotion, 0xf4);
			body->m_motion = newMotion;
			oldMotion->destroy(1);
		}
		body->m_broadPhaseHandleType = (hkUint16)((newMotionType != 7) + 1);
	}
	else
	{
		if (!oldStateNeedsInertia)
		{
			hkMotion* oldMotion = body->m_motion;
			hkMotion* saved = HK_MOTION_PTR(oldMotion, 0xf0);
			body->m_motion = saved;
			body->m_broadPhaseHandleType = (hkUint16)HK_MOTION_U32(oldMotion, 0xf4);
			oldMotion->getMotionStateAndVelocities(saved);
			HK_MOTION_PTR(oldMotion, 0xf0) = 0;
			oldMotion->destroy(1);
		}
		if (body->m_motion->getType() != newMotionType && newMotionType != 1)
		{
			hkMotion* oldMotion = body->m_motion;
			hkMatrix3 inertiaLocal;
			oldMotion->getInertiaLocal(inertiaLocal);
			float mass = oldMotion->getMass();
			hkMotion* newMotion = hkRigidBody_createMotion(newMotionType, oldMotion->m_motionState.m_transform.m_trans,
			                                      *(const hkQuaternion*)&oldMotion->m_motionState.m_sweptTransform.m_rotation1, mass,
			                                      inertiaLocal, oldMotion->m_motionState.m_sweptTransform.m_centerOfMassLocal,
			                                      oldMotion->m_motionState.m_linearDamping, oldMotion->m_motionState.m_angularDamping);
			oldMotion->getMotionStateAndVelocities(newMotion);
			HK_MOTION_U32(newMotion, 0xc8) = HK_MOTION_U32(oldMotion, 0xc8);
			HK_MOTION_U32(newMotion, 0xcc) = HK_MOTION_U32(oldMotion, 0xcc);
			body->m_motion = newMotion;
			oldMotion->destroy(1);
		}
	}
	body->m_motionStatePtr = &body->m_motion->m_motionState;
	body->m_isFixed = (newMotionType == 7);
	body->m_isFixedOrKeyframed = (newMotionType == 7 || newMotionType == 6) ? 1 : 0;
}

// @ 0x010a03c0
void hkWorldOperationUtil::removeEntitySI(hkWorld* world, hkEntity* entity)
{
	hkSimulationIsland* island = entity->m_island;
	entity->m_world = 0;
	hkSimulationIsland_internalRemoveEntity(island, entity);
	if (island->m_storageIndex != 0xffff && island->m_entitiesSize == 0 && world->m_wantSimulationIslands)
	{
		removeIsland(world, island);
		island->destroy(1);     // scalar deleting destructor, vtable slot 0
	}
}

// @ 0x010a0410
hkSimulationIsland* hkWorldOperationUtil::internalMergeTwoIslands(hkWorld* world, hkSimulationIsland* islandA, hkSimulationIsland* islandB)
{
	HK_TIMER_BEGIN("TtMergeIsle");
	hkSimulationIsland* small = islandB;
	hkSimulationIsland* big = islandA;
	if (islandA->m_entitiesSize < islandB->m_entitiesSize)
	{
		small = islandA;
		big = islandB;
	}
	world->m_criticalOperationsLockCount = world->m_criticalOperationsLockCount + 1;

	bool anyActive = !(big->m_active == 0 && small->m_active == 0);
	hkUint8 activeMark = (big->m_activeMark != 0 || small->m_activeMark != 0) ? 1 : 0;
	if (anyActive)
	{
		if (big->m_active == 0)
		{
			big->m_activeMark = 1;
			internalActivateIsland(world, big);
			big->m_activeCounter0 = small->m_activeCounter0;
			big->m_activeCounter1 = small->m_activeCounter1;
		}
		else if (small->m_active == 0)
		{
			small->m_activeMark = 1;
			internalActivateIsland(world, small);
		}
		else
		{
			hkUint8 v = small->m_activeCounter0;
			if (big->m_activeCounter0 < small->m_activeCounter0)
				v = big->m_activeCounter0;
			big->m_activeCounter0 = v;
			v = small->m_activeCounter1;
			if (big->m_activeCounter1 < small->m_activeCounter1)
				v = big->m_activeCounter1;
			big->m_activeCounter1 = v;
		}
	}

	hkAgentNnMachine_AppendTrack(HK_ISLAND_AGENT_TRACK(big), HK_ISLAND_AGENT_TRACK(small));

	// entities
	{
		hkArray<hkEntity*>* bigEntities = (hkArray<hkEntity*>*)&big->m_entitiesData;
		hkArray<hkEntity*>* smallEntities = (hkArray<hkEntity*>*)&small->m_entitiesData;
		unsigned int index = (unsigned int)big->m_entitiesSize;
		int newSize = small->m_entitiesSize + (int)index;
		int cap = big->m_entitiesCap & 0x3fffffff;
		if (cap < newSize)
		{
			int newCap = cap * 2;
			if (newCap <= newSize)
				newCap = newSize;
			hkArrayUtil::_reserveExactly(bigEntities, newCap, 4);
		}
		big->m_entitiesSize = newSize;
		for (int i = 0; i < small->m_entitiesSize; i++)
		{
			bigEntities->m_data[index & 0xffff] = smallEntities->m_data[i];
			smallEntities->m_data[i]->m_island = big;
			smallEntities->m_data[i]->m_storageIndex = (hkUint16)index;
			index++;
		}
	}

	// actions (null entries of the small island are dropped)
	{
		int idx = HK_ISLAND_ACTIONS_SIZE(big);
		int newCount = HK_ISLAND_ACTIONS_SIZE(small) + idx;
		int cap = HK_ISLAND_ACTIONS_CAP(big) & 0x3fffffff;
		if (cap < newCount)
		{
			int doubled = cap * 2;
			int newCap = newCount;
			if (newCount < doubled)
				newCap = doubled;
			hkArrayUtil::_reserveExactly(&HK_ISLAND_ACTIONS_DATA(big), newCap, 4);
		}
		HK_ISLAND_ACTIONS_SIZE(big) = newCount;
		for (int i = 0; i < HK_ISLAND_ACTIONS_SIZE(small); i++)
		{
			hkAction* action = HK_ISLAND_ACTIONS_DATA(small)[i];
			if (action != 0)
			{
				HK_ISLAND_ACTIONS_DATA(big)[idx] = action;
				HK_ISLAND_ACTIONS_DATA(big)[idx]->m_island = big;
				idx++;
			}
		}
		if ((HK_ISLAND_ACTIONS_CAP(big) & 0x3fffffff) < idx)
		{
			int newCap = (HK_ISLAND_ACTIONS_CAP(big) & 0x3fffffff) * 2;
			if (newCap <= idx)
				newCap = idx;
			hkArrayUtil::_reserveExactly(&HK_ISLAND_ACTIONS_DATA(big), newCap, 4);
		}
		HK_ISLAND_ACTIONS_SIZE(big) = idx;
	}

	// constraints: every master constraint of the moved entities now belongs to the big island
	for (int i = 0; i < small->m_entitiesSize; i++)
	{
		hkEntity* e = small->m_entitiesData[i];
		hkConstraintInternalStub* ci = e->m_constraintsMasterData;
		for (int n = e->m_constraintsMasterSize; n > 0; --n, ++ci)
			*(hkSimulationIsland**)((char*)ci->m_constraint + 8) = big;       // hkConstraintInstance::m_owner (+8)
	}

	// constraint info
	{
		int v = small->m_maxSizeOfJacobians;
		if (v < big->m_maxSizeOfJacobians)
			v = big->m_maxSizeOfJacobians;
		big->m_maxSizeOfJacobians = v;
		big->m_sizeOfJacobians += small->m_sizeOfJacobians;
		big->m_sizeOfSchemas += small->m_sizeOfSchemas;
		big->m_numSolverResults += small->m_numSolverResults;
		big->m_numMotionInfo += small->m_numMotionInfo;
	}

	// remove the small island from the world array that holds it (the swap only happens when it is not last)
	{
		hkUint16 smallIndex = small->m_storageIndex;
		hkArray<hkSimulationIsland*>& arr = small->m_active ? world->m_activeSimulationIslands : world->m_inactiveSimulationIslands;
		if ((int)smallIndex < arr.m_size - 1)
		{
			arr.m_data[smallIndex] = arr.m_data[arr.m_size - 1];
			arr.m_data[smallIndex]->m_storageIndex = smallIndex;
		}
		arr.m_size = arr.m_size - 1;
	}

	big->m_actionListCleanupNeeded = (big->m_actionListCleanupNeeded == 0 && small->m_actionListCleanupNeeded == 0) ? 0 : 1;
	big->m_splitCheckRequested = (big->m_splitCheckRequested == 0 && small->m_splitCheckRequested == 0) ? 0 : 1;
	big->m_activeMark = activeMark;

	if (small->m_dirtyListIndex != 0xffff && big->m_dirtyListIndex == 0xffff)
		putIslandOnDirtyList(world, big);
	if (small->m_dirtyListIndex != 0xffff)
	{
		world->m_dirtySimulationIslands.m_data[small->m_dirtyListIndex] = 0;
		small->m_dirtyListIndex = 0xffff;
	}
	small->destroy(1);     // scalar deleting destructor, vtable slot 0
	HK_TIMER_END();
	hkWorld_leaveCritical(world);
	return big;
}
