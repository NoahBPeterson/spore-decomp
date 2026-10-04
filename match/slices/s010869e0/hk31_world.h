#pragma once
// Havok 3.1.0 world/entity/motion class declarations shared by batch b005 slices s010869e0, s010e1340 and
// s010e6530. Layouts come from the dev PDB (tools/pdb_type.py, offsets confirmed against the disassembly),
// vtable slot numbers from vtable dumps of the retail binary. "(32-bit layout)" comments flag offsets that only hold
// for 4-byte pointers. This header is self-contained apart from the shared base header.
#include "../s010cbaa0/hk31_b005.h"
#include <string.h>

// ---------------------------------------------------------------------------------------------------------
// broad phase handle / collidable / filters
// ---------------------------------------------------------------------------------------------------------
struct hkBroadPhaseHandle { uint32_t m_id; };
struct hkTypedBroadPhaseHandle : hkBroadPhaseHandle
{
	signed char m_type;               // +4
	signed char m_ownerOffset;        // +5
	uint16_t m_objectQualityType;     // +6
	uint32_t m_collisionFilterInfo;   // +8
};
struct hkCollidable : hkCdBody
{
	int m_ownerOffset;                              // +0x10
	hkTypedBroadPhaseHandle m_broadPhaseHandle;     // +0x14
	float m_allowedPenetrationDepth;                // +0x20
};
struct hkAgentNnEntry;
struct hkLinkedCollidable : hkCollidable
{
	hkArray<void*[2]> m_collisionEntries;           // +0x24 (8-byte entries: partner collidable, agent entry; 32-bit layout)
};

class hkShapeCollection;
struct hkCollisionInput;
// The shape-collection filters have no virtual destructor: slot 0 is the first isCollisionEnabled overload.
class hkShapeCollectionFilter
{
public:
	virtual hkBool isCollisionEnabled(const hkCollisionInput& input, const hkCdBody& collA, const hkCdBody& collB,
	                                  const hkShapeCollection& bContainer, unsigned int bKey) const = 0;           // 0
	virtual hkBool isCollisionEnabled(const hkCdBody& collA, const hkShapeCollection& aContainer, const hkCdBody& collB,
	                                  const hkShapeCollection& bContainer, unsigned int aKey, unsigned int bKey) const = 0;   // 1
};
class hkRayShapeCollectionFilter
{
public:
	virtual hkBool isCollisionEnabled(const hkShapeRayCastInput& input, const hkShapeCollection& container, unsigned int key) const = 0;   // 0
};
class hkCollidableCollidableFilter
{
public:
	virtual ~hkCollidableCollidableFilter() {}                                                              // 0
	virtual hkBool isCollisionEnabled(const hkCollidable& a, const hkCollidable& b) const = 0;              // 1 (+4)
};
class hkRayCollidableFilter
{
public:
	virtual ~hkRayCollidableFilter() {}                                                                      // 0
	virtual hkBool isCollisionEnabled(const hkWorldRayCastInput& a, const hkCollidable& b) const = 0;       // 1
};
// Base order gives the binary's offsets: +8 collidable pair, +0xc shape collection, +0x10 ray shape collection,
// +0x14 ray/collidable (32-bit layout). Size 0x18.
class hkCollisionFilter : public hkReferencedObject, public hkCollidableCollidableFilter, public hkShapeCollectionFilter,
	public hkRayShapeCollectionFilter, public hkRayCollidableFilter { };

// ---------------------------------------------------------------------------------------------------------
// motions
// ---------------------------------------------------------------------------------------------------------
struct hkMatrix3 { hkVector4 m_col0, m_col1, m_col2; };   // 0x30 bytes
typedef hkVector4 hkQuaternion;                           // x,y,z,w

struct hkMotionState                                      // 0xb0 bytes
{
	hkTransform m_transform;                              // +0
	struct hkSweptTransform
	{
		hkVector4 m_centerOfMass0;                        // +0x40
		hkVector4 m_centerOfMass1;                        // +0x50
		hkVector4 m_rotation0;                            // +0x60 (hkQuaternion)
		hkVector4 m_rotation1;                            // +0x70
		hkVector4 m_centerOfMassLocal;                    // +0x80
	} m_sweptTransform;                                   // +0x40 (0x50 bytes)
	hkVector4 m_deltaAngle;                               // +0x90
	float m_objectRadius;                                 // +0xa0
	float m_maxLinearVelocity;                            // +0xa4
	float m_maxAngularVelocity;                           // +0xa8
	uint16_t m_deactivationClass;                         // +0xac
	uint16_t m_deactivationCounter;                       // +0xae
	hkMotionState& operator=(const hkMotionState& other);  // 0x010DF5D0 (out-of-line member-wise copy)
};

class hkVelocityAccumulator;
struct hkStepInfo;
class hkMotion : public hkReferencedObject
{
public:
	enum MotionType
	{
		MOTION_INVALID = 0, MOTION_DYNAMIC = 1, MOTION_SPHERE_INERTIA = 2, MOTION_STABILIZED_SPHERE_INERTIA = 3,
		MOTION_BOX_INERTIA = 4, MOTION_STABILIZED_BOX_INERTIA = 5, MOTION_KEYFRAMED = 6, MOTION_FIXED = 7,
		MOTION_THIN_BOX_INERTIA = 8
	};
	static void* operator new(size_t nbytes)                           // memory class 0x2b
	{
		void* p = hkMemory::s_instance->allocateChunk((int)nbytes, 0x2b);
		((hkReferencedObject*)p)->m_memSizeAndFlags = (hkInt16)nbytes;
		return p;
	}
	static void operator delete(void* p) { hkMemory::s_instance->deallocateChunk(p, ((hkReferencedObject*)p)->m_memSizeAndFlags, 0x2b); }
	static void* operator new(size_t, void* p) { return p; }
	static void operator delete(void*, void*) {}
	virtual int getType() const;                                       // 2 (+8)
	virtual void step(const hkStepInfo&);                              // 3
	virtual void applyForcesAndStep(const hkStepInfo&, const hkVector4&);   // 4
	virtual void* applyForcesAndBuildAccumulator(const hkStepInfo&, hkVelocityAccumulator*);   // 5
	virtual const hkVelocityAccumulator* applyAccumulator(const hkStepInfo&, const hkVelocityAccumulator*);   // 6
	virtual void motionSlot7();                                        // 7
	virtual hkMotion* clone() const;                                   // 8
	virtual void setMass(float m);                                     // 9  (+0x24)
	virtual void setMassInv(float m);                                  // 10
	virtual void getInertiaLocal(hkMatrix3& out) const;                // 11 (+0x2c)
	virtual void getInertiaWorld(hkMatrix3& out) const;                // 12
	virtual void setInertiaLocal(const hkMatrix3& inertia);            // 13 (+0x34)
	virtual void setInertiaInvLocal(const hkMatrix3& inertia);         // 14
	virtual void getInertiaInvLocal(hkMatrix3& out) const;             // 15
	virtual void getInertiaInvWorld(hkMatrix3& out) const;             // 16
	virtual void setCenterOfMassInLocal(const hkVector4& com);         // 17 (+0x44)
	virtual void setPosition(const hkVector4& position);               // 18 (+0x48)
	virtual void setRotation(const hkQuaternion& rotation);            // 19 (+0x4c)
	virtual void setPositionAndRotation(const hkVector4& position, const hkQuaternion& rotation);   // 20 (+0x50)
	virtual void setTransform(const hkTransform& transform);           // 21 (+0x54)
	virtual void setLinearVelocity(const hkVector4&);                  // 22
	virtual void setAngularVelocity(const hkVector4&);                 // 23
	virtual void applyLinearImpulse(const hkVector4&);                 // 24
	virtual void applyPointImpulse(const hkVector4&, const hkVector4&);// 25
	virtual void applyAngularImpulse(const hkVector4&);                // 26
	virtual void motionSlot27();                                       // 27
	virtual void motionSlot28();                                       // 28
	virtual void motionSlot29();                                       // 29
	virtual void getMotionStateAndVelocities(hkMotion* out);           // 30 (+0x78)
	int m_solverData;                                                  // +8
};

class hkRigidMotion : public hkMotion
{
public:
	hkRigidMotion(const hkVector4& position, const hkQuaternion& rotation);   // 0x01088500
	hkMotionState m_motionState;                                       // +0x10
	float m_massInv;                                                   // +0xc0
	float m_particleMinInertiaDiagInv;                                 // +0xc4
	float m_linearDamping;                                             // +0xc8
	float m_angularDamping;                                            // +0xcc
	hkVector4 m_linearVelocity;                                        // +0xd0
	hkVector4 m_angularVelocity;                                       // +0xe0
};
class hkSphereMotion : public hkRigidMotion                            // vtable 0x0149DF10
{
public:
	hkSphereMotion(const hkVector4& position, const hkQuaternion& rotation);   // 0x01087010
};
class hkStabilizedSphereMotion : public hkSphereMotion                 // vtable 0x0149DF90
{
public:
	hkStabilizedSphereMotion(const hkVector4& position, const hkQuaternion& rotation);   // 0x01087030
};
class hkBoxMotion : public hkRigidMotion                               // vtable 0x014A18B8
{
public:
	hkBoxMotion(const hkVector4& position, const hkQuaternion& rotation);                  // 0x01098140
};
class hkThinBoxMotion : public hkBoxMotion                             // vtable 0x014A1838
{
public:
	hkThinBoxMotion(const hkVector4& position, const hkQuaternion& rotation);              // 0x0108F3E0
};
class hkStabilizedBoxMotion : public hkBoxMotion                       // vtable 0x014A1990
{
public:
	hkStabilizedBoxMotion(const hkVector4& position, const hkQuaternion& rotation);        // 0x01090370
};
class hkKeyframedRigidMotion : public hkRigidMotion                    // vtable 0x014A1C08, size 0x100
{
public:
	hkKeyframedRigidMotion(const hkVector4& position, const hkQuaternion& rotation);       // 0x01095B60
	hkMotion* m_savedMotion;                                           // +0xf0 (refcounted, may be null)
	uint32_t m_savedQualityTypeAndPad[3];                              // +0xf4..0xff
};
class hkFixedRigidMotion : public hkKeyframedRigidMotion               // vtable 0x014A1D08
{
public:
	hkFixedRigidMotion(const hkVector4& position, const hkQuaternion& rotation);           // 0x01097110
};

// ---------------------------------------------------------------------------------------------------------
// world objects
// ---------------------------------------------------------------------------------------------------------
class hkWorld;
class hkSimulationIsland;
class hkEntity;
class hkConstraintInstance;
class hkConstraintOwner;
struct hkProperty { uint32_t m_key, m_pad, m_lo, m_hi; };
struct hkMultiThreadLock { uint32_t m_threadId; int m_lockCount; };

namespace hkWorldOperation { enum Result { POSTPONED = 0, DONE = 1 }; }

class hkWorldObject : public hkReferencedObject
{
public:
	virtual hkWorldOperation::Result setShape(const hkShape* shape) = 0;   // 2
	virtual void woSlot3() = 0;                                              // 3 (0x010871D0 in the rigid body vtable)
	hkWorld* m_world;                          // +8
	void* m_userData;                          // +0xc
	const char* m_name;                        // +0x10
	hkMultiThreadLock m_multithreadLock;       // +0x14
	hkLinkedCollidable m_collidable;           // +0x1c
	hkArray<hkProperty> m_properties;          // +0x4c
};

class hkEntityDeactivator : public hkReferencedObject
{
public:
	virtual hkBool shouldDeactivateHighFrequency(const hkEntity*) const = 0;   // 2
	virtual hkBool shouldDeactivateLowFrequency(const hkEntity*) const = 0;    // 3
	virtual int getDeactivatorType() const = 0;                                 // 4 (+0x10)
};
class hkRigidBodyDeactivator : public hkEntityDeactivator
{
public:
	enum DeactivatorType { DEACTIVATOR_INVALID = 0, DEACTIVATOR_NEVER = 1, DEACTIVATOR_SPATIAL = 2 };
};
// hkSpatialRigidBodyDeactivator: 0x70 bytes, memory class 0x28 (ctor 0x01091670).
class hkSpatialRigidBodyDeactivator : public hkRigidBodyDeactivator
{
public:
	hkSpatialRigidBodyDeactivator();                                // 0x01091670
	static void* operator new(size_t n)                             // memory class 0x28
	{
		void* p = hkMemory::s_instance->allocateChunk((int)n, 0x28);
		((hkReferencedObject*)p)->m_memSizeAndFlags = (hkInt16)n;
		return p;
	}
	static void operator delete(void* p) { hkMemory::s_instance->deallocateChunk(p, ((hkReferencedObject*)p)->m_memSizeAndFlags, 0x28); }
	virtual hkBool shouldDeactivateHighFrequency(const hkEntity*) const;   // 0x010916E0
	virtual hkBool shouldDeactivateLowFrequency(const hkEntity*) const;    // 0x010917E0
	virtual int getDeactivatorType() const;
};
// The static "never deactivate" instance at 0x015BA098 (vtable 0x014A1D8C, memSize 0, refcount 1).
extern char g_hkRigidBodyDeactivatorNever[];    // 0x015BA098: the object itself (an hkRigidBodyDeactivator-derived static instance)

struct hkMaterial { uint32_t m_data[3]; };

class hkEntity : public hkWorldObject
{
public:
	virtual void deallocateInternalArrays();                       // 4 (0x01088F70)
	virtual hkEntity* entityClone() const = 0;                     // 5 (hkRigidBody::clone 0x01087E40)
	void setDeactivator(hkEntityDeactivator* d);                   // 0x010889E0
	hkBool isActive() const;                                       // 0x01088AC0
	void activate();                                               // 0x01088AE0
	hkMotion* m_motion;                                            // +0x58
	hkSimulationIsland* m_simulationIsland;                        // +0x5c
	hkMaterial m_material;                                         // +0x60
	hkEntityDeactivator* m_deactivator;                            // +0x6c
	hkArray<char[0x28]> m_constraintsMaster;                       // +0x70
	hkArray<hkConstraintInstance*> m_constraintsSlave;             // +0x7c
	hkArray<unsigned char> m_constraintRuntime;                    // +0x88
	uint16_t m_storageIndex;                                       // +0x94
	uint16_t m_processContactCallbackDelay;                        // +0x96
	char m_autoRemoveLevel;                                        // +0x98
	hkBool m_fixed;                                                // +0x99
	hkBool m_isFixedOrKeyframed;                                   // +0x9a
	hkBool m_internalCollideFlag;                                  // +0x9b
	hkArray<void*> m_collisionListeners;                           // +0x9c
	hkArray<void*> m_activationListeners;                          // +0xa8
	hkArray<void*> m_entityListeners;                              // +0xb4
	hkArray<void*> m_actions;                                      // +0xc0
	uint32_t m_uid;                                                // +0xcc
protected:
	~hkEntity();                                                   // 0x01088DE0
};

enum hkEntityActivation { HK_ENTITY_DO_NOT_ACTIVATE = 0, HK_ENTITY_DO_ACTIVATE = 1 };
enum hkUpdateCollisionFilterOnEntityMode { HK_UPDATE_FILTER_ON_ENTITY_FULL_CHECK = 0, HK_UPDATE_FILTER_ON_ENTITY_DISABLE_ENTITY_ENTITY_COLLISIONS_ONLY = 1 };
enum hkUpdateCollisionFilterOnWorldMode { HK_UPDATE_FILTER_ON_WORLD_FULL_CHECK = 0, HK_UPDATE_FILTER_ON_WORLD_DISABLE_ENTITY_ENTITY_COLLISIONS_ONLY = 1 };
enum hkUpdateCollectionFilterMode { HK_UPDATE_COLLECTION_FILTER_IGNORE_SHAPE_COLLECTIONS = 0, HK_UPDATE_COLLECTION_FILTER_PROCESS_SHAPE_COLLECTIONS = 1 };

class hkRigidBody : public hkEntity
{
public:
	virtual ~hkRigidBody();                                                          // 0 (body 0x01087140)
	virtual hkWorldOperation::Result setShape(const hkShape* shape);                 // 2 (0x01087590)
	virtual void woSlot3();
	virtual hkEntity* entityClone() const;
	void setDeactivator(hkRigidBodyDeactivator::DeactivatorType type);               // 0x010876D0
	void setMotionType(hkMotion::MotionType newState, hkEntityActivation preferredActivationState,
	                   hkUpdateCollisionFilterOnEntityMode collisionFilterUpdateMode); // 0x01087520
	void setPosition(const hkVector4& position);                                     // 0x01087820
	void setRotation(const hkQuaternion& rotation);                                  // 0x01087840
	void setPositionAndRotation(const hkVector4& position, const hkQuaternion& rotation);   // 0x01087860
	void setTransform(const hkTransform& transform);                                 // 0x01087890
	static void updateBroadphaseAndResetCollisionInformationOfWarpedBody(hkEntity* entity);   // 0x01087750
};

// ---------------------------------------------------------------------------------------------------------
// simulation islands, agent tracks, world
// ---------------------------------------------------------------------------------------------------------
struct hkAgentNnEntry                                          // 0x1c bytes in the 32-bit binary
{
	uint8_t m_streamCommand;       // +0
	uint8_t m_agentType;           // +1
	uint8_t m_numContactPoints;    // +2
	uint8_t m_size;                // +3 (byte size of this entry in the track)
	uintptr_t m_userData;          // +4
	uint8_t m_collisionQualityIndex;   // +8
	uint8_t m_padding[3];          // +9
	uint16_t m_agentIndexOnCollidable[2];   // +0xc
	void* m_contactMgr;            // +0x10
	hkLinkedCollidable* m_collidable[2];    // +0x14
};
template <typename T, int N>
struct hkInplaceArray : hkArray<T>
{
	T m_storage[N];                // +0xc
};
struct hkAgentNnTrack                                          // 0x18 bytes
{
	hkInplaceArray<char*, 1> m_sectors;     // +0 (data, size, capacity, inline storage)
	unsigned int m_bytesUsedInLastSector;   // +0x10
	unsigned short m_agentSize;             // +0x14
	unsigned short m_sectorSize;            // +0x16
};
class hkSimpleConstraintOwner : public hkReferencedObject
{
public:
	int m_maxSizeOfJacobians, m_sumSizeOfJacobians, m_sumSizeOfSchemas, m_sumSizeOfMotions, m_sumNumSolverResults;   // +8..+0x1b
};
class hkSimulationIsland : public hkSimpleConstraintOwner      // size 0x74
{
public:
	hkWorld* m_world;                           // +0x1c
	uint16_t m_storageIndex;                    // +0x20
	uint16_t m_dirtyListIndex;                  // +0x22
	uint8_t m_highFrequencyDeactivationCounter; // +0x24
	uint8_t m_lowFrequencyDeactivationCounter;  // +0x25
	hkBool m_splitCheckRequested;               // +0x26
	hkBool m_actionListCleanupNeeded;           // +0x27
	hkBool m_active;                            // +0x28
	hkBool m_isInActiveIslandsArray;            // +0x29
	uint16_t m_pad2a;                           // +0x2a
	hkMultiThreadLock m_multiThreadLock;        // +0x2c
	float m_timeSinceLastHighFrequencyCheck;    // +0x34
	float m_timeSinceLastLowFrequencyCheck;     // +0x38
	hkInplaceArray<hkEntity*, 1> m_entities;    // +0x3c
	hkAgentNnTrack m_agentTrack;                // +0x4c
	hkArray<void*> m_actions;                   // +0x64
	float m_timeOfDeactivation;                 // +0x70
};

class hkPhantom;
class hkAction;
struct hkCollisionInput
{
	void* m_dispatcher;                        // +0 (hkCollisionDispatcher*)
	const hkShapeCollectionFilter* m_filter;   // +4
	float m_tolerance;                         // +8
	hkBool m_createPredictiveAgents;           // +0xc
	hkCollisionInput() : m_dispatcher(0), m_filter(0), m_tolerance(0), m_createPredictiveAgents(false) {}
};
struct hkProcessCollisionInput : hkCollisionInput   // size 0x2c
{
	uint32_t m_stepInfo[4];                    // +0x10 (hkStepInfo)
	void* m_config;                            // +0x20
	void* m_dynamicsInfo;                      // +0x24
	void* m_collisionQualityInfo;              // +0x28
};
class hkCollisionAgent;
class hkContactMgr;
class hkCdPointCollector;
class hkCdBodyPairCollector;
struct hkLinearCastCollisionInput;
typedef hkCollisionAgent* (HK_CALL *hkAgentCreateFunc)(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkContactMgr*);
typedef void (HK_CALL *hkAgentGetPenetrationsFunc)(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
typedef void (HK_CALL *hkAgentGetClosestPointsFunc)(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
typedef void (HK_CALL *hkAgentLinearCastFunc)(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
struct hkAgentFuncs                            // hkCollisionDispatcher::AgentFuncs, 0x14 bytes in the 32-bit binary
{
	hkAgentCreateFunc m_createFunc;                         // +0
	hkAgentGetPenetrationsFunc m_getPenetrationsFunc;       // +4
	hkAgentGetClosestPointsFunc m_getClosestPointFunc;      // +8
	hkAgentLinearCastFunc m_linearCastFunc;                 // +0xc
	hkBool m_isFlipped;                                     // +0x10
	hkBool m_isPredictive;                                  // +0x11
	hkAgentFuncs() : m_createFunc(0), m_getPenetrationsFunc(0), m_getClosestPointFunc(0), m_linearCastFunc(0), m_isFlipped(false), m_isPredictive(false) {}
};
struct hkCollisionDispatcher                   // size 0x1c28 (32-bit layout); spelled out up to the quality table
{
	void* m_vptr_and_refcount[2];              // +0
	void* m_defaultCollisionAgent;             // +8 (hkCollisionDispatcher is an hkReferencedObject; first 8 bytes)
	uint8_t m_pad0c[0x190 - 0xc];
	uint8_t m_agent2Types[32][32];             // +0x190
	uint8_t m_agent2TypesPred[32][32];         // +0x590
	hkAgentFuncs m_agent2Func[64];             // +0x990 (stride 0x14 in the 32-bit binary)
	uint8_t m_pad0e90[0x19d4 - 0xe90];         // (agent3 tables)
	char m_collisionQualityTable[8][8];        // +0x19d4
	void registerCollisionAgent(hkAgentFuncs& funcs, int typeA, int typeB);   // 0x010CD3E0
};
class hkBroadPhase;
class hkWorldOperationQueue;
class hkSimulation
{
public:
	virtual void simSlot0();                                    // 0
	virtual void simSlot1();                                    // 1
	virtual int stepDeltaTime(hkWorld* world, hkReal physicsDeltaTime, hkReal frameDeltaTime);   // 2
	virtual void simSlot3(); virtual void simSlot4(); virtual void simSlot5(); virtual void simSlot6(); virtual void simSlot7();
	virtual void simSlot8(); virtual void simSlot9(); virtual void simSlot10(); virtual void simSlot11();
	virtual void resetCollisionInformationForEntities(hkEntity** entities, int numEntities, hkWorld* world);   // 12 (+0x30)
};

// Queued operations (the first byte is the type; the payload starts at +4 in the 32-bit binary).
namespace hkWorldOperation
{
	enum Type
	{
		WORLD_OP_ADD_CONSTRAINT = 8, WORLD_OP_REMOVE_CONSTRAINT = 9, WORLD_OP_REMOVE_ACTION = 0xb,
		WORLD_OP_SET_RIGID_BODY_MOTION_TYPE = 4, WORLD_OP_SET_SHAPE = 5, WORLD_OP_UPDATE_FILTER_ON_WORLD = 0x14,
		WORLD_OP_UPDATE_MOVED_BODY_INFO = 0x15
	};
	struct BaseOperation { uint8_t m_type; };
	struct UpdateFilterOnWorld : BaseOperation { uint8_t m_updateMode; uint8_t m_updateShapeCollections; };
	struct AddConstraint : BaseOperation { hkConstraintInstance* m_constraint; };                      // +4
	struct RemoveConstraint : BaseOperation { hkConstraintInstance* m_constraint; };                   // +4
	struct RemoveAction : BaseOperation { hkAction* m_action; };                                       // +4
	struct SetRigidBodyMotionType : BaseOperation { hkRigidBody* m_rigidBody; uint8_t m_motionType, m_activation, m_filterMode; };
	struct SetShape : BaseOperation { hkEntity* m_entity; const hkShape* m_shape; };
	struct UpdateMovedBodyInfo : BaseOperation { hkEntity* m_entity; };
}
class hkWorldOperationQueue
{
public:
	void queueOperation(const hkWorldOperation::BaseOperation& op);   // 0x0109AFE0
};

// hkWorld, PDB layout (size 0x2f0). Only the first 0x168 bytes are spelled out.
class hkWorld : public hkReferencedObject
{
public:
	hkSimulation* m_simulation;                                  // +0x8
	float m_currentTime, m_timeOfNextFrame, m_timeOfLastPsi, m_timeOfNextPsi;   // +0xc..+0x1b
	uint32_t m_pad1c;                                            // +0x1c
	hkVector4 m_gravity;                                         // +0x20
	hkSimulationIsland* m_fixedIsland;                           // +0x30
	hkRigidBody* m_fixedRigidBody;                               // +0x34
	hkArray<hkSimulationIsland*> m_activeSimulationIslands;      // +0x38
	hkArray<hkSimulationIsland*> m_inactiveSimulationIslands;    // +0x44
	hkArray<hkSimulationIsland*> m_dirtySimulationIslands;       // +0x50
	void* m_maintenanceMgr;                                      // +0x5c
	void* m_memoryWatchDog;                                      // +0x60
	hkBroadPhase* m_broadPhase;                                  // +0x64
	void* m_broadPhaseDispatcher;                                // +0x68
	void* m_phantomBroadPhaseListener;                           // +0x6c
	void* m_entityEntityBroadPhaseListener;                      // +0x70
	void* m_broadPhaseBorderListener;                            // +0x74
	hkProcessCollisionInput* m_collisionInput;                   // +0x78
	hkCollisionFilter* m_collisionFilter;                        // +0x7c
	hkCollisionDispatcher* m_collisionDispatcher;                // +0x80
	hkWorldOperationQueue* m_pendingOperations;                  // +0x84
	int m_pendingOperationsCount;                                // +0x88
	int m_lockCount;                                             // +0x8c
	int m_lockCountForPhantoms;                                  // +0x90
	hkBool m_blockExecutingPendingOperations;                    // +0x94
	hkBool m_criticalOperationsAllowed;                          // +0x95
	uint16_t m_pad96;                                            // +0x96
	void* m_pendingOperationQueues;                              // +0x98
	int m_pendingOperationQueueCount;                            // +0x9c
	hkMultiThreadLock m_multiThreadLock;                         // +0xa0
	hkBool m_processActionsInSingleThread;                       // +0xa8
	uint8_t m_pada9[3];
	void* m_modifyConstraintCriticalSection;                     // +0xac
	void* m_worldLock;                                           // +0xb0
	hkBool m_wantSimulationIslands;                              // +0xb4
	hkBool m_wantDeactivation;                                   // +0xb5
	hkBool m_shouldActivateOnRigidBodyTransformChange;           // +0xb6
	uint8_t m_padb7;
	float m_highFrequencyDeactivationPeriod, m_lowFrequencyDeactivationPeriod, m_toiCollisionResponseRotateNormal;   // +0xb8..
	int m_simulationType;                                        // +0xc4
	unsigned int m_lastEntityUid;                                // +0xc8
	hkArray<hkPhantom*> m_phantoms;                              // +0xcc

	// functions of this slice
	void updateCollisionFilterOnWorld(hkUpdateCollisionFilterOnWorldMode updateMode, hkUpdateCollectionFilterMode updateShapeCollections);   // 0x010869E0
	hkConstraintInstance* addConstraint(hkConstraintInstance* constraint);   // 0x01086DA0
	hkBool removeConstraint(hkConstraintInstance* constraint);              // 0x01086E90
	void removeAction(hkAction* action);                                    // 0x01086F40
	void setCollisionFilter(hkCollisionFilter* filter, hkBool runUpdateFilterOnWorld,
	                        hkUpdateCollisionFilterOnWorldMode updateMode, hkUpdateCollectionFilterMode updateShapeCollections);   // 0x01086F80

	// callees defined elsewhere
	void executePendingOperations();                                        // 0x01082BF0
	void queueOperation(const hkWorldOperation::BaseOperation& op);         // 0x010829D0
	void removeActionImmediately(hkAction* action);                         // 0x01086030
	hkAction* addAction(hkAction* action);                                  // 0x01085E60
	void updateCollisionFilterOnEntity(hkEntity* entity, hkUpdateCollisionFilterOnEntityMode mode, hkUpdateCollectionFilterMode shapeMode);   // 0x01084FA0
	void updateCollisionFilterOnPhantom(hkPhantom* phantom, hkUpdateCollectionFilterMode shapeMode);   // 0x01084CF0
};
