// Havok 3.1.0 slice s010869e0: hkWorld (updateCollisionFilterOnWorld, addConstraint, removeConstraint, removeAction,
// setCollisionFilter) and hkRigidBody (motion creation, shape/deactivator/motion-type setters, warping setters).
// Equivalent portable source (not byte-exact). Operation order of the x87 math is taken from the disassembly.
#include "hk31_world.h"
#include <math.h>

// ---------------------------------------------------------------------------------------------------------
// external classes seen only through a few members
// ---------------------------------------------------------------------------------------------------------
class hkConstraintData : public hkReferencedObject
{
public:
	struct RuntimeInfo { int m_sizeOfExternalRuntime; int m_numSolverResults; };
	enum { CONSTRAINT_TYPE_BREAKABLE = 0xc };
	virtual void cdSlot2();
	virtual int getType() const;                                                  // 3 (+0xc)
	virtual void getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& infoOut) const;  // +0x10
	virtual void dataSlot5(); virtual void dataSlot6(); virtual void dataSlot7(); virtual void dataSlot8();
	virtual void dataSlot9();                                                      // +0x24 (chain constraint data hook)
};
struct hkBreakableConstraintDataView
{
	uint32_t m_vptr; int16_t m_memSize, m_refCount;     // +0
	uint32_t m_pad8;                                    // +8
	hkConstraintData* m_constraintData;                 // +0xc (wrapped child)
	uint16_t m_childRuntimeSize;                        // +0x10
	uint16_t m_childNumSolverResults;                   // +0x12
};
class hkAction : public hkReferencedObject
{
public:
	hkWorld* m_world;                                   // +8
};
class hkConstraintInstance : public hkReferencedObject
{
public:
	enum InstanceType { TYPE_NORMAL = 0, TYPE_CHAIN = 1 };
	virtual void ciSlot2(); virtual void ciSlot3(); virtual void ciSlot4();
	virtual int getType() const;                         // 5 (+0x14)
	hkConstraintOwner* m_owner;                          // +8
	hkConstraintData* m_data;                            // +0xc
	// ... (the chain subclass keeps its hkConstraintChainInstanceAction* at +0x34)
};
struct hkConstraintChainInstanceView : hkConstraintInstance
{
	uint32_t m_pad10[9];                                 // +0x10..0x33
	hkAction* m_action;                                  // +0x34
};

struct hkWorldOperationUtil
{
	static hkConstraintInstance* addConstraintImmediately(hkWorld* world, hkConstraintInstance* c, int);    // 0x0109F930
	static void removeConstraintImmediately(hkWorld* world, hkConstraintInstance* c, int);                  // 0x0109FA10
	static void addEntityBP(hkWorld*, hkEntity*);                                                           // 0x010A0BE0
	static void removeEntityBP(hkWorld*, hkEntity*);                                                        // 0x010A0E20
	static void setRigidBodyMotionType(hkRigidBody* body, hkMotion::MotionType newType, hkEntityActivation activation,
	                                   hkUpdateCollisionFilterOnEntityMode mode);                           // 0x010A1B30
};
struct hkWorldAgentUtil { static void removeAgent(hkAgentNnEntry* entry); };                                // 0x010A39F0
extern "C" void _hkAgentNnMachine_UpdateShapeCollectionFilter(hkAgentNnEntry* entry, const hkCollisionInput& input);   // 0x010FB9C0
struct hkWorldCallbackUtil
{
	static void fireEntityShapeSet(hkWorld* world, hkEntity* entity);                                       // 0x0109ECE0
	static void fireInactiveEntityMoved(hkWorld* world, hkEntity* entity);                                  // 0x0109F870
};
struct hkEntityCallbackUtil { static void fireEntityShapeSet(hkEntity* entity); };                          // 0x0109E760
struct hkDiscreteSimulation { static void collideEntitiesBroadPhaseDiscrete(hkEntity** entities, int numEntities, hkWorld* world); };   // 0x01099CD0
struct hkThreadMemory { void deallocateChunk(void* p, int nbytes, int memClass); };                         // 0x0107DB10

// ---------------------------------------------------------------------------------------------------------
// hkWorld::updateCollisionFilterOnWorld
// ---------------------------------------------------------------------------------------------------------
// @ 0x010869e0
void hkWorld::updateCollisionFilterOnWorld(hkUpdateCollisionFilterOnWorldMode updateMode, hkUpdateCollectionFilterMode updateShapeCollections)
{
	if (m_lockCount != 0)
	{
		hkWorldOperation::UpdateFilterOnWorld op;
		op.m_type = hkWorldOperation::WORLD_OP_UPDATE_FILTER_ON_WORLD;
		op.m_updateMode = (uint8_t)updateMode;
		op.m_updateShapeCollections = (uint8_t)updateShapeCollections;
		m_pendingOperations->queueOperation(op);
		return;
	}

	m_blockExecutingPendingOperations = hkBool(true);
	HK_TIMER_BEGIN("TtUpdateFilterOnWorld");

	if (updateMode == HK_UPDATE_FILTER_ON_WORLD_FULL_CHECK)
	{
		for (int i = 0; i < m_activeSimulationIslands.m_size; ++i)
		{
			hkSimulationIsland* island = m_activeSimulationIslands.m_data[i];
			for (int j = 0; j < island->m_entities.m_size; ++j)
				updateCollisionFilterOnEntity(island->m_entities.m_data[j], HK_UPDATE_FILTER_ON_ENTITY_FULL_CHECK, updateShapeCollections);
		}
		for (int i = 0; i < m_inactiveSimulationIslands.m_size; ++i)
		{
			hkSimulationIsland* island = m_inactiveSimulationIslands.m_data[i];
			for (int j = 0; j < island->m_entities.m_size; ++j)
				updateCollisionFilterOnEntity(island->m_entities.m_data[j], HK_UPDATE_FILTER_ON_ENTITY_FULL_CHECK, updateShapeCollections);
		}
		for (int i = 0; i < m_phantoms.m_size; ++i)
			updateCollisionFilterOnPhantom(m_phantoms.m_data[i], updateShapeCollections);
	}
	else
	{
		// "disable entity-entity collisions only": remove the narrow phase agents whose pair is no longer allowed
		m_lockCount = m_lockCount + 1;
		hkArray<hkSimulationIsland*>* islandArrays[2];
		islandArrays[0] = &m_activeSimulationIslands;
		islandArrays[1] = &m_inactiveSimulationIslands;
		for (int which = 0; which < 2; ++which)
		{
			hkArray<hkSimulationIsland*>* islands = islandArrays[which];
			hkInplaceArray<hkAgentNnEntry*, 32> agentsToRemove;      // inline storage of 32 pointers
			agentsToRemove.m_data = agentsToRemove.m_storage;
			agentsToRemove.m_size = 0;
			agentsToRemove.m_capacityAndFlags = (int)(0x80000000u | 32);
			for (int i = 0; i < islands->m_size; ++i)
			{
				hkSimulationIsland* island = islands->m_data[i];
				agentsToRemove.m_size = 0;
				hkAgentNnTrack& track = island->m_agentTrack;
				for (int sector = 0; sector < track.m_sectors.m_size; )
				{
					char* sectorStart = track.m_sectors.m_data[sector];
					++sector;
					uintptr_t usedBytes = (sector == track.m_sectors.m_size) ? track.m_bytesUsedInLastSector : (uintptr_t)track.m_sectorSize;
					char* sectorEnd = sectorStart + usedBytes;
					for (char* p = sectorStart; p < sectorEnd; p += ((hkAgentNnEntry*)p)->m_size)
					{
						hkAgentNnEntry* entry = (hkAgentNnEntry*)p;
						hkCollidableCollidableFilter* pairFilter = m_collisionFilter;
						hkBool enabled = pairFilter->isCollisionEnabled(*entry->m_collidable[0], *entry->m_collidable[1]);
						bool keep = false;
						if (enabled)
						{
							int qualityA = entry->m_collidable[0]->m_broadPhaseHandle.m_objectQualityType;
							int qualityB = entry->m_collidable[1]->m_broadPhaseHandle.m_objectQualityType;
							keep = m_collisionDispatcher->m_collisionQualityTable[qualityA][qualityB] != 0;
						}
						if (!keep)
						{
							if (agentsToRemove.m_size == agentsToRemove.getCapacity())
								hkArrayUtil::_reserveMore(&agentsToRemove, 4);
							agentsToRemove.m_data[agentsToRemove.m_size] = entry;
							agentsToRemove.m_size = agentsToRemove.m_size + 1;
							island->m_splitCheckRequested = hkBool(true);
						}
						else if (updateShapeCollections == HK_UPDATE_COLLECTION_FILTER_PROCESS_SHAPE_COLLECTIONS)
						{
							_hkAgentNnMachine_UpdateShapeCollectionFilter(entry, *m_collisionInput);
						}
					}
				}
				while (agentsToRemove.m_size != 0)
				{
					hkAgentNnEntry* e = agentsToRemove.m_data[agentsToRemove.m_size - 1];
					agentsToRemove.m_size = agentsToRemove.m_size - 1;
					hkWorldAgentUtil::removeAgent(e);
				}
			}
			if (agentsToRemove.m_capacityAndFlags >= 0)
			{
				hkThreadMemory* tm = (hkThreadMemory*)hkTlsGet(g_hkThreadMemoryTls);
				tm->deallocateChunk(agentsToRemove.m_data, (agentsToRemove.m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) << 2, HK_MEMORY_CLASS_ARRAY);
			}
		}
		m_lockCount = m_lockCount - 1;
	}

	m_blockExecutingPendingOperations = hkBool(false);
	if (m_lockCount == 0 && m_pendingOperationsCount != 0)
		executePendingOperations();
	HK_TIMER_END();
}

// ---------------------------------------------------------------------------------------------------------
// hkWorld constraints / actions / collision filter
// ---------------------------------------------------------------------------------------------------------
// @ 0x01086da0
hkConstraintInstance* hkWorld::addConstraint(hkConstraintInstance* constraint)
{
	if (m_lockCount != 0)
	{
		hkWorldOperation::AddConstraint op;
		op.m_type = hkWorldOperation::WORLD_OP_ADD_CONSTRAINT;
		op.m_constraint = constraint;
		m_pendingOperations->queueOperation(op);
		return 0;
	}

	hkConstraintData* data = constraint->m_data;
	if (data->getType() == hkConstraintData::CONSTRAINT_TYPE_BREAKABLE)
	{
		hkBreakableConstraintDataView* breakable = (hkBreakableConstraintDataView*)constraint->m_data;
		if (breakable->m_childRuntimeSize == 0)
		{
			hkConstraintData::RuntimeInfo info;
			breakable->m_constraintData->getRuntimeInfo(hkBool(true), info);
			breakable->m_childRuntimeSize = (uint16_t)info.m_sizeOfExternalRuntime;
			breakable->m_childNumSolverResults = (uint16_t)info.m_numSolverResults;
		}
	}

	m_blockExecutingPendingOperations = hkBool(true);
	hkConstraintInstance* result = hkWorldOperationUtil::addConstraintImmediately(this, constraint, 1);
	if (constraint->getType() == hkConstraintInstance::TYPE_CHAIN)
	{
		hkAction* action = static_cast<hkConstraintChainInstanceView*>(constraint)->m_action;
		if (action->m_world == 0)
			addAction(action);
		constraint->m_data->dataSlot9();
	}
	m_blockExecutingPendingOperations = hkBool(false);
	if (m_lockCount == 0 && m_pendingOperationsCount != 0)
		executePendingOperations();
	return result;
}

// @ 0x01086e90
hkBool hkWorld::removeConstraint(hkConstraintInstance* constraint)
{
	if (m_lockCount != 0)
	{
		hkWorldOperation::RemoveConstraint op;
		op.m_type = hkWorldOperation::WORLD_OP_REMOVE_CONSTRAINT;
		op.m_constraint = constraint;
		m_pendingOperations->queueOperation(op);
		return hkBool(false);
	}

	m_lockCount = 1;
	if (constraint->getType() == hkConstraintInstance::TYPE_CHAIN)
	{
		hkAction* action = static_cast<hkConstraintChainInstanceView*>(constraint)->m_action;
		if (action->m_world == this)
			removeActionImmediately(action);
	}
	hkWorldOperationUtil::removeConstraintImmediately(this, constraint, 1);
	m_lockCount = m_lockCount - 1;
	if (m_lockCount == 0 && m_pendingOperationsCount != 0 && !m_blockExecutingPendingOperations)
		executePendingOperations();
	return hkBool(true);
}

// @ 0x01086f40
void hkWorld::removeAction(hkAction* action)
{
	if (m_lockCount != 0)
	{
		hkWorldOperation::RemoveAction op;
		op.m_type = hkWorldOperation::WORLD_OP_REMOVE_ACTION;
		op.m_action = action;
		m_pendingOperations->queueOperation(op);
		return;
	}
	removeActionImmediately(action);
}

// hkNullCollisionFilter (size 0x18, memory class 0x24); its constructor 0x01082d20 stores the five vtables of
// the hkCollisionFilter bases (hkReferencedObject, hkCollidableCollidableFilter, hkShapeCollectionFilter,
// hkRayShapeCollectionFilter, hkRayCollidableFilter).
class hkNullCollisionFilter : public hkCollisionFilter
{
public:
	hkNullCollisionFilter();                                                                           // 0x01082D20
	virtual hkBool isCollisionEnabled(const hkCollidable& a, const hkCollidable& b) const;
	virtual hkBool isCollisionEnabled(const hkWorldRayCastInput& a, const hkCollidable& b) const;
	virtual hkBool isCollisionEnabled(const hkCollisionInput& input, const hkCdBody& collA, const hkCdBody& collB,
	                                  const hkShapeCollection& bContainer, unsigned int bKey) const;
	virtual hkBool isCollisionEnabled(const hkCdBody& collA, const hkShapeCollection& aContainer, const hkCdBody& collB,
	                                  const hkShapeCollection& bContainer, unsigned int aKey, unsigned int bKey) const;
	virtual hkBool isCollisionEnabled(const hkShapeRayCastInput& input, const hkShapeCollection& container, unsigned int key) const;
	static void* operator new(size_t n)
	{
		void* p = hkMemory::s_instance->allocateChunk((int)n, 0x24);
		((hkReferencedObject*)p)->m_memSizeAndFlags = (hkInt16)n;
		return p;
	}
	static void operator delete(void* p) { hkMemory::s_instance->deallocateChunk(p, ((hkReferencedObject*)p)->m_memSizeAndFlags, 0x24); }
};

// @ 0x01086f80
void hkWorld::setCollisionFilter(hkCollisionFilter* filter, hkBool runUpdateFilterOnWorld,
                                 hkUpdateCollisionFilterOnWorldMode updateMode, hkUpdateCollectionFilterMode updateShapeCollections)
{
	if (filter == 0)
		filter = new hkNullCollisionFilter();
	else
		filter->addReference();

	m_collisionFilter->removeReference();
	m_collisionFilter = filter;
	m_collisionInput->m_filter = filter ? static_cast<hkShapeCollectionFilter*>(filter) : 0;
	if (runUpdateFilterOnWorld)
		updateCollisionFilterOnWorld(updateMode, updateShapeCollections);
}

// ---------------------------------------------------------------------------------------------------------
// motion constructors (the sphere family; the remaining motion constructors live in other slices)
// ---------------------------------------------------------------------------------------------------------
// hkRigidMotion(position, rotation) (0x01088500) followed by the vtable store (0x0149DF10 / 0x0149DF90).
// @ 0x01087010
hkSphereMotion::hkSphereMotion(const hkVector4& position, const hkQuaternion& rotation)
	: hkRigidMotion(position, rotation)
{
}
// @ 0x01087030  (the base constructor is hkRigidMotion's directly: the hkSphereMotion constructor is inlined)
hkStabilizedSphereMotion::hkStabilizedSphereMotion(const hkVector4& position, const hkQuaternion& rotation)
	: hkSphereMotion(position, rotation)
{
}

// ---------------------------------------------------------------------------------------------------------
// hkMath::min2<float>  (0x010871f0): "a < b ? a : b"; NaN in either operand returns b
// ---------------------------------------------------------------------------------------------------------
namespace hkMath { template <typename T> T min2(T a, T b) { return (a < b) ? a : b; } }
// @ 0x010871f0
template float hkMath::min2<float>(float a, float b);

// ---------------------------------------------------------------------------------------------------------
// hkRigidBody helpers split out of the constructor / setShape by whole-program optimisation
// ---------------------------------------------------------------------------------------------------------
// Shape extents and the bounding-sphere radius stored in the motion state. The original takes the shape in ECX and the
// extents output in ESI (custom register convention), the body on the stack; it is a normal function.
extern const hkTransform g_hkTransformIdentity;     // 0x015B9B20 (rows (1,0,0,0) ...)

// @ 0x01087050
static void hkRigidBody_calcExtentsAndObjectRadius(const hkShape* shape, hkVector4* extents, hkEntity* body)
{
	hkAabb aabb;
	shape->getAabb(g_hkTransformIdentity, 0.0f, aabb);

	// extents = max - min (the first three results stay on the x87 stack for the length below)
	// X87-PRECISION: ex/ey/ez are kept on the stack after being stored to the output.
	hkX87Real ex = (hkX87Real)aabb.m_max.x - aabb.m_min.x;
	extents->x = (float)ex;
	hkX87Real ey = (hkX87Real)aabb.m_max.y - aabb.m_min.y;
	extents->y = (float)ey;
	hkX87Real ez = (hkX87Real)aabb.m_max.z - aabb.m_min.z;
	extents->z = (float)ez;
	extents->w = aabb.m_max.w - aabb.m_min.w;

	hkRigidMotion* motion = static_cast<hkRigidMotion*>(body->m_motion);
	const hkVector4& centerOfMassLocal = motion->m_motionState.m_sweptTransform.m_centerOfMassLocal;   // motion +0x90
	// center = (min + max) * 0.5 minus the local center of mass; each component is stored to a float before squaring.
	// X87-PRECISION: the sum and the *0.5 stay on the stack; x and z are stored once (z before the *0.5, x after).
	float xHalf = (float)(((hkX87Real)aabb.m_min.x + aabb.m_max.x) * 0.5f);
	hkX87Real yHalf = ((hkX87Real)aabb.m_min.y + aabb.m_max.y) * 0.5f;
	float zSum = (float)((hkX87Real)aabb.m_min.z + aabb.m_max.z);
	hkX87Real zHalf = (hkX87Real)zSum * 0.5f;
	float dx = (float)((hkX87Real)xHalf - centerOfMassLocal.x);
	float dy = (float)(yHalf - centerOfMassLocal.y);
	float dz = (float)(zHalf - centerOfMassLocal.z);

	// |extents| * 0.5 (sum order: (ez*ez + ey*ey) + ex*ex, then fsqrt, kept on the stack)
	hkX87Real extentLength = sqrt((ez * ez + ey * ey) + ex * ex);
	hkX87Real halfExtentLength = extentLength * 0.5f;
	// |d| from the stored floats: (dz*dz + dy*dy) + dx*dx
	hkX87Real centerLength = sqrt(((hkX87Real)dz * dz + (hkX87Real)dy * dy) + (hkX87Real)dx * dx);
	motion->m_motionState.m_objectRadius = (float)(centerLength + halfExtentLength);
}

// @ 0x01087240  (extents in ECX, collidable in EDX)
// Automatic allowed penetration depth: 0.2 * the smallest extent when that is below 0.5, else 0.1.
static void hkRigidBody_calcAllowedPenetrationDepth(const hkVector4* extents, hkCollidable* collidable)
{
	float minExtent = hkMath::min2<float>(extents->x, extents->y);
	minExtent = hkMath::min2<float>(minExtent, extents->z);
	if (minExtent < 0.5f)
		collidable->m_allowedPenetrationDepth = minExtent * 0.2f;
	else
		collidable->m_allowedPenetrationDepth = 0.1f;
}

// ---------------------------------------------------------------------------------------------------------
// hkRigidBody
// ---------------------------------------------------------------------------------------------------------
// @ 0x01087140
hkRigidBody::~hkRigidBody()
{
	hkKeyframedRigidMotion* keyframed = static_cast<hkKeyframedRigidMotion*>(m_motion);
	if (m_motion->getType() == hkMotion::MOTION_KEYFRAMED)
	{
		if (keyframed->m_savedMotion)
			keyframed->m_savedMotion->removeReference();
	}
	if (m_motion->getType() == hkMotion::MOTION_FIXED)
	{
		if (keyframed->m_savedMotion)
			keyframed->m_savedMotion->removeReference();
	}
	keyframed->removeReference();
	// ~hkEntity (0x01088DE0) runs as the base destructor
}

// Creates the motion object for a rigid body (constructor and hkWorldOperationUtil::replaceMotionObject share it).
// Parameter roles: the stack arguments in order are the motion type, position, rotation, mass, the local inertia tensor,
// the local center of mass and the two velocity limits. The two limits are overwritten with 1e6 for keyframed bodies.
// @ 0x01087290
hkMotion* hkRigidBody_createMotion(hkMotion::MotionType motionType, const hkVector4& position, const hkQuaternion& rotation,
                                   float mass, const hkMatrix3& inertiaTensor, const hkVector4& centerOfMass,
                                   float maxLinearVelocity, float maxAngularVelocity)
{
	hkMotion* motion;
	switch (motionType)
	{
	case hkMotion::MOTION_DYNAMIC:
	{
		float a = inertiaTensor.m_col1.y;
		float b = inertiaTensor.m_col2.z;
		float c = inertiaTensor.m_col0.x;
		float t = (a > b) ? a : b;
		float maxInertia = (c > t) ? c : t;
		float t2 = (a < b) ? a : b;
		float minInertia = (c < t2) ? c : t2;
		// X87-PRECISION: the scaled maximum stays on the x87 stack for the compare.
		if ((hkX87Real)minInertia > (hkX87Real)maxInertia * 0.8f)
			motion = new hkSphereMotion(position, rotation);
		else if ((hkX87Real)minInertia > (hkX87Real)maxInertia * 0.1f)
			motion = new hkBoxMotion(position, rotation);
		else
			motion = new hkThinBoxMotion(position, rotation);
		break;
	}
	case hkMotion::MOTION_SPHERE_INERTIA:
		motion = new hkSphereMotion(position, rotation);
		break;
	case hkMotion::MOTION_STABILIZED_SPHERE_INERTIA:
		motion = new hkStabilizedSphereMotion(position, rotation);
		break;
	case hkMotion::MOTION_BOX_INERTIA:
		motion = new hkBoxMotion(position, rotation);
		break;
	case hkMotion::MOTION_STABILIZED_BOX_INERTIA:
		motion = new hkStabilizedBoxMotion(position, rotation);
		break;
	case hkMotion::MOTION_KEYFRAMED:
		maxLinearVelocity = 1000000.0f;                    // 0x49742400
		maxAngularVelocity = 1000000.0f;
		motion = new hkKeyframedRigidMotion(position, rotation);
		break;
	case hkMotion::MOTION_THIN_BOX_INERTIA:
		motion = new hkThinBoxMotion(position, rotation);
		break;
	default:
		motion = new hkFixedRigidMotion(position, rotation);
		break;
	}
	if (motionType != hkMotion::MOTION_KEYFRAMED)
	{
		motion->setInertiaLocal(inertiaTensor);
		motion->setCenterOfMassInLocal(centerOfMass);
		motion->setMass(mass);
	}
	hkRigidMotion* rigid = static_cast<hkRigidMotion*>(motion);
	rigid->m_motionState.m_deactivationCounter = 0x14;
	rigid->m_motionState.m_maxLinearVelocity = maxLinearVelocity;
	rigid->m_motionState.m_maxAngularVelocity = maxAngularVelocity;
	return motion;
}

// @ 0x01087520
void hkRigidBody::setMotionType(hkMotion::MotionType newState, hkEntityActivation preferredActivationState,
                                hkUpdateCollisionFilterOnEntityMode collisionFilterUpdateMode)
{
	if (m_world != 0 && m_world->m_lockCount != 0)
	{
		hkWorldOperation::SetRigidBodyMotionType op;
		op.m_type = hkWorldOperation::WORLD_OP_SET_RIGID_BODY_MOTION_TYPE;
		op.m_rigidBody = this;
		op.m_motionType = (uint8_t)newState;
		op.m_activation = (uint8_t)preferredActivationState;
		op.m_filterMode = (uint8_t)collisionFilterUpdateMode;
		m_world->queueOperation(op);
		return;
	}
	hkWorldOperationUtil::setRigidBodyMotionType(this, newState, preferredActivationState, collisionFilterUpdateMode);
}

// @ 0x01087590
hkWorldOperation::Result hkRigidBody::setShape(const hkShape* shape)
{
	hkWorld* world = m_world;
	if (world != 0)
	{
		if (world->m_lockCount != 0)
		{
			hkWorldOperation::SetShape op;
			op.m_type = hkWorldOperation::WORLD_OP_SET_SHAPE;
			op.m_entity = this;
			op.m_shape = shape;
			world->queueOperation(op);
			return hkWorldOperation::POSTPONED;
		}
		world->m_lockCount = world->m_lockCount + 1;
		hkWorldOperationUtil::removeEntityBP(m_world, this);
	}

	const hkShape* oldShape = m_collidable.m_shape;
	hkBool hadShape = (oldShape != 0);
	if (oldShape)
		const_cast<hkShape*>(oldShape)->removeReference();
	m_collidable.m_shape = shape;
	const_cast<hkShape*>(shape)->addReference();

	hkVector4 extents;
	hkRigidBody_calcExtentsAndObjectRadius(shape, &extents, this);

	if (hadShape)
	{
		// the allowed penetration depth is compared as raw bits against HK_REAL_MAX (0x7f7fffee)
		uint32_t depthBits;
		memcpy(&depthBits, &m_collidable.m_allowedPenetrationDepth, sizeof(depthBits));
		if (depthBits != 0x7f7fffeeu)
			m_collidable.m_allowedPenetrationDepth = -1.0f;      // 0xbf800000: recompute below
	}
	if (m_collidable.m_allowedPenetrationDepth <= 0.0f)
		hkRigidBody_calcAllowedPenetrationDepth(&extents, &m_collidable);

	if (m_world != 0)
		hkWorldCallbackUtil::fireEntityShapeSet(m_world, this);
	hkEntityCallbackUtil::fireEntityShapeSet(this);

	if (m_world != 0)
	{
		hkWorldOperationUtil::addEntityBP(m_world, this);
		hkWorld* w = m_world;
		w->m_lockCount = w->m_lockCount - 1;
		if (w->m_lockCount == 0 && w->m_pendingOperationsCount != 0 && !w->m_blockExecutingPendingOperations)
			w->executePendingOperations();
	}
	return hkWorldOperation::DONE;
}

// @ 0x010876d0
void hkRigidBody::setDeactivator(hkRigidBodyDeactivator::DeactivatorType type)
{
	if (m_deactivator == 0 || m_deactivator->getDeactivatorType() != type)
	{
		if (type == hkRigidBodyDeactivator::DEACTIVATOR_NEVER)
		{
			hkEntity::setDeactivator((hkEntityDeactivator*)g_hkRigidBodyDeactivatorNever);
		}
		else if (type == hkRigidBodyDeactivator::DEACTIVATOR_SPATIAL)
		{
			hkSpatialRigidBodyDeactivator* d = new hkSpatialRigidBodyDeactivator();
			hkEntity::setDeactivator(d);
			d->removeReference();
		}
	}
}

// @ 0x01087750
void hkRigidBody::updateBroadphaseAndResetCollisionInformationOfWarpedBody(hkEntity* entity)
{
	hkWorld* world = entity->m_world;
	if (world == 0)
		return;
	if (world->m_lockCount != 0)
	{
		hkWorldOperation::UpdateMovedBodyInfo op;
		op.m_type = hkWorldOperation::WORLD_OP_UPDATE_MOVED_BODY_INFO;
		op.m_entity = entity;
		world->queueOperation(op);
		return;
	}
	world->m_lockCount = 1;
	hkEntity* entities[1];
	entities[0] = entity;
	if (entity->m_collidable.m_shape != 0)
		hkDiscreteSimulation::collideEntitiesBroadPhaseDiscrete(entities, 1, world);
	world->m_simulation->resetCollisionInformationForEntities(entities, 1, world);
	if (!entity->isActive())
	{
		if (world->m_shouldActivateOnRigidBodyTransformChange && !entity->m_fixed)
			entity->activate();
		hkWorldCallbackUtil::fireInactiveEntityMoved(world, entity);
	}
	world->m_lockCount = world->m_lockCount - 1;
	if (world->m_lockCount == 0 && world->m_pendingOperationsCount != 0 && !world->m_blockExecutingPendingOperations)
		world->executePendingOperations();
}

// @ 0x01087820
void hkRigidBody::setPosition(const hkVector4& position)
{
	m_motion->setPosition(position);
	updateBroadphaseAndResetCollisionInformationOfWarpedBody(this);
}

// @ 0x01087840
void hkRigidBody::setRotation(const hkQuaternion& rotation)
{
	m_motion->setRotation(rotation);
	updateBroadphaseAndResetCollisionInformationOfWarpedBody(this);
}

// @ 0x01087860
void hkRigidBody::setPositionAndRotation(const hkVector4& position, const hkQuaternion& rotation)
{
	m_motion->setPositionAndRotation(position, rotation);
	updateBroadphaseAndResetCollisionInformationOfWarpedBody(this);
}

// @ 0x01087890
void hkRigidBody::setTransform(const hkTransform& transform)
{
	m_motion->setTransform(transform);
	updateBroadphaseAndResetCollisionInformationOfWarpedBody(this);
}

// ---------------------------------------------------------------------------------------------------------
// 32-bit layout checks against the binary / PDB
// ---------------------------------------------------------------------------------------------------------
#if defined(_M_IX86)
#define HK_LAYOUT_CHECK(name, cond) typedef char hkLayoutCheck_##name[(cond) ? 1 : -1]
HK_LAYOUT_CHECK(world, offsetof(hkWorld, m_lockCount) == 0x8c && offsetof(hkWorld, m_pendingOperations) == 0x84 && offsetof(hkWorld, m_collisionFilter) == 0x7c
                       && offsetof(hkWorld, m_blockExecutingPendingOperations) == 0x94 && offsetof(hkWorld, m_shouldActivateOnRigidBodyTransformChange) == 0xb6
                       && offsetof(hkWorld, m_phantoms) == 0xcc && offsetof(hkWorld, m_inactiveSimulationIslands) == 0x44);
HK_LAYOUT_CHECK(entity, offsetof(hkEntity, m_motion) == 0x58 && offsetof(hkEntity, m_deactivator) == 0x6c && offsetof(hkEntity, m_fixed) == 0x99
                        && offsetof(hkWorldObject, m_collidable) == 0x1c && offsetof(hkWorldObject, m_world) == 8 && sizeof(hkWorldObject) == 0x58);
HK_LAYOUT_CHECK(collidable, sizeof(hkLinkedCollidable) == 0x30 && offsetof(hkCollidable, m_allowedPenetrationDepth) == 0x20);
HK_LAYOUT_CHECK(motion, sizeof(hkMotionState) == 0xb0 && sizeof(hkRigidMotion) == 0xf0 && offsetof(hkRigidMotion, m_motionState) == 0x10
                        && sizeof(hkKeyframedRigidMotion) == 0x100 && offsetof(hkKeyframedRigidMotion, m_savedMotion) == 0xf0);
HK_LAYOUT_CHECK(island, offsetof(hkSimulationIsland, m_agentTrack) == 0x4c && offsetof(hkSimulationIsland, m_entities) == 0x3c
                        && offsetof(hkSimulationIsland, m_splitCheckRequested) == 0x26 && sizeof(hkAgentNnTrack) == 0x18
                        && offsetof(hkAgentNnTrack, m_sectorSize) == 0x16);
HK_LAYOUT_CHECK(agentEntry, sizeof(hkAgentNnEntry) == 0x1c && offsetof(hkAgentNnEntry, m_collidable) == 0x14);
HK_LAYOUT_CHECK(dispatcher, offsetof(hkCollisionDispatcher, m_collisionQualityTable) == 0x19d4 && offsetof(hkCollisionDispatcher, m_agent2Func) == 0x990);
HK_LAYOUT_CHECK(filter, sizeof(hkCollisionFilter) == 0x18);
HK_LAYOUT_CHECK(matrix, sizeof(hkMatrix3) == 0x30);
#endif
