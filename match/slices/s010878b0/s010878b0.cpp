// Havok 3.1.0 slice s010878b0 (0x010878B0..0x010888C0): hkRigidBody ctor / getCinfo / clone, hkRigidBodyCinfo
// defaults, hkWorldObject::copyProperties, hkWorldCinfo, hkRigidMotion (mass, impulse, step) and the
// hkMotionState / hkSweptTransform copy operators. Functionally equivalent portable source (not byte exact).
// Float math: hkRigidMotion::step is x87 code with inline fsqrt; values kept on the x87 stack without
// storing are typed hkX87Real and marked "X87-PRECISION". No sin/cos/atan2 (the half-angle quaternion is a
// polynomial approximation).
#include "s010878b0.h"

// ---- layouts used here (32-bit offsets in comments) -------------------------------------------------------------------
class hkShape;
class hkEntityDeactivator
{
public:
    virtual ~hkEntityDeactivator() {}
    virtual void v1(); virtual void v2(); virtual void v3();
    virtual int getDeactivatorType() const;                       // 4 (+0x10)
};
struct hkMaterial
{
    enum ResponseType { RESPONSE_INVALID = 0, RESPONSE_SIMPLE_CONTACT = 1, RESPONSE_REPORTING = 2, RESPONSE_NONE = 3 };
    int8_t m_responseType;     // +0x00
    float m_friction;          // +0x04
    float m_restitution;       // +0x08
};
struct hkProperty { hkUint32 m_key; hkUint32 m_pad; hkUint32 m_value[2]; };   // 0x10 bytes
struct hkConstraintInternal { hkUint32 m_data[7]; };                           // 0x1c bytes
class hkConstraintInstance; class hkCollisionListener; class hkEntityActivationListener;
class hkEntityListener; class hkAction; class hkSimulationIsland;

struct hkMultiThreadLockStub { hkUint32 m_threadId; int32_t m_lockCount; };    // 8 bytes

// hkLinkedCollidable (0x30 bytes at hkWorldObject +0x1c)
struct hkLinkedCollidable
{
    hkShape* m_shape;                     // +0x1c
    hkUint32 m_shapeKey;                  // +0x20
    hkMotionState* m_motion;              // +0x24
    void* m_parent;                       // +0x28
    int m_ownerOffset;                    // +0x2c
    hkUint32 m_handleId;                  // +0x30
    int8_t m_handleType;                  // +0x34
    int8_t m_handleOwnerOffset;           // +0x35
    hkUint16 m_objectQualityType;         // +0x36
    hkUint32 m_collisionFilterInfo;       // +0x38
    float m_allowedPenetrationDepth;      // +0x3c
    hkUint32 m_collisionEntries[3];       // +0x40
};

class hkWorldObject : public hkReferencedObject
{
public:
    hkWorldObject(hkFinishLoadedObjectFlag);                                       // 0x010826E0
    virtual hkResult setShape(hkShape* s);                                     // 2
    virtual hkMotionState* getMotionState();                                   // 3
    void copyProperties(const hkWorldObject* other);                               // 0x01087CA0

    void* m_world;                                                                 // +0x08
    void* m_userData;                                                              // +0x0c
    const char* m_name;                                                            // +0x10
    hkMultiThreadLockStub m_multithreadLock;                                       // +0x14
    hkLinkedCollidable m_collidable;                                               // +0x1c
    hkArray<hkProperty> m_properties;                                              // +0x4c
};

class hkEntity : public hkWorldObject
{
public:
    hkEntity(const hkShape* shape);                                                // 0x01088D20
    hkEntity(hkFinishLoadedObjectFlag);                                            // 0x01087D50
    virtual void deallocateInternalArrays();                                       // 4
    virtual hkEntity* clone() const;                                           // 5
    void activate();                                                               // 0x01088AE0

    hkRigidMotion* m_motion;                                                       // +0x58 (the retail code uses the rigid-motion fields directly)
    hkSimulationIsland* m_simulationIsland;                                        // +0x5c
    hkMaterial m_material;                                                         // +0x60
    hkEntityDeactivator* m_deactivator;                                            // +0x6c
    hkArray<hkConstraintInternal> m_constraintsMaster;                             // +0x70
    hkArray<hkConstraintInstance*> m_constraintsSlave;                             // +0x7c
    hkArray<hkUint8> m_constraintRuntime;                                          // +0x88
    hkUint16 m_storageIndex;                                                       // +0x94
    hkUint16 m_processContactCallbackDelay;                                        // +0x96
    int8_t m_autoRemoveLevel;                                                      // +0x98
    bool m_fixed;                                                                // +0x99
    bool m_isFixedOrKeyframed;                                                   // +0x9a
    bool m_internalCollideFlag;                                                  // +0x9b
    hkArray<hkCollisionListener*> m_collisionListeners;                            // +0x9c
    hkArray<hkEntityActivationListener*> m_activationListeners;                    // +0xa8
    hkArray<hkEntityListener*> m_entityListeners;                                  // +0xb4
    hkArray<hkAction*> m_actions;                                                  // +0xc0
    hkUint32 m_uid;                                                                // +0xcc
};

// hkRigidBodyCinfo (0xc0 bytes)
struct hkRigidBodyCinfo
{
    hkRigidBodyCinfo();                                                            // 0x01087ED0
    hkUint32 m_collisionFilterInfo;      // +0x00
    hkShape* m_shape;                    // +0x04
    int8_t m_collisionResponse;          // +0x08
    hkUint16 m_processContactCallbackDelay;   // +0x0a
    hkVector4 m_position;                // +0x10
    hkQuaternion m_rotation;             // +0x20
    hkVector4 m_linearVelocity;          // +0x30
    hkVector4 m_angularVelocity;         // +0x40
    hkMatrix3 m_inertiaTensor;           // +0x50
    hkVector4 m_centerOfMass;            // +0x80
    float m_mass;                        // +0x90
    float m_linearDamping;               // +0x94
    float m_angularDamping;              // +0x98
    float m_friction;                    // +0x9c
    float m_restitution;                 // +0xa0
    float m_maxLinearVelocity;           // +0xa4
    float m_maxAngularVelocity;          // +0xa8
    float m_allowedPenetrationDepth;     // +0xac
    int8_t m_motionType;                 // +0xb0
    int8_t m_rigidBodyDeactivatorType;   // +0xb1
    int8_t m_solverDeactivation;         // +0xb2
    int8_t m_qualityType;                // +0xb3
    int8_t m_autoRemoveLevel;            // +0xb4
};

class hkRigidBody : public hkEntity
{
public:
    HK_DECLARE_CLASS_ALLOCATOR_B(0x2a)
    hkRigidBody(const hkRigidBodyCinfo& info);                                     // 0x010878B0
    hkRigidBody(hkFinishLoadedObjectFlag f) : hkEntity(f) {}                       // inlined in 0x01087E20
    virtual hkResult setShape(hkShape* s);                                         // 0x01087590
    virtual hkMotionState* getMotionState();                                       // 0x010871D0
    virtual hkEntity* clone() const;                                               // 0x01087E40
    void getCinfo(hkRigidBodyCinfo& info) const;                                   // 0x01087B00
    void setDeactivator(int deactivatorType);                                      // 0x010876D0
};

// Cross-slice helpers (custom register conventions in the binary).
hkRigidMotion* hkRigidBody_createMotion(int motionType, const hkVector4& position, const hkQuaternion& rotation,
                                        float mass, const hkMatrix3& inertiaTensor, const hkVector4& centerOfMass,
                                        float maxLinearVelocity, float maxAngularVelocity);   // 0x01087290 (cdecl)
void hkRigidBody_calcShapeExtent(const hkShape* shape, hkEntity* entity, hkVector4* extentOut);   // 0x01087050: ECX=shape, ESI=extentOut, [esp+4]=entity; also sets motion radius (+0xb0)
void hkRigidBody_setAllowedPenetrationFromExtent(const hkVector4* extent, hkLinkedCollidable* c);   // 0x01087240: ECX=extent, EDX=collidable

static const float HK_REAL_MAX = 3.40282e+38f;     // 0x7f7fffee

// ---- hkWorldCinfo (0xa0 bytes) -------------------------------------------------------------------------------------
class hkWorldCinfo : public hkReferencedObject
{
public:
    enum SolverType { SOLVER_TYPE_INVALID = 0, SOLVER_TYPE_2ITERS_SOFT = 1, SOLVER_TYPE_2ITERS_MEDIUM = 2, SOLVER_TYPE_2ITERS_HARD = 3,
        SOLVER_TYPE_4ITERS_SOFT = 4, SOLVER_TYPE_4ITERS_MEDIUM = 5, SOLVER_TYPE_4ITERS_HARD = 6,
        SOLVER_TYPE_8ITERS_SOFT = 7, SOLVER_TYPE_8ITERS_MEDIUM = 8, SOLVER_TYPE_8ITERS_HARD = 9 };
    hkWorldCinfo();                                  // 0x010880E0
    hkWorldCinfo(hkFinishLoadedObjectFlag);          // 0x01088200 (via finishLoadedObject_hkWorldCinfo)
    void setSolverType(SolverType t);                // 0x01087FD0
    void setBroadPhaseWorldSize(float size);         // 0x010881D0

    hkVector4 m_gravity;                             // +0x10
    int32_t m_broadPhaseQuerySize;                   // +0x20
    float m_contactRestingVelocity;                  // +0x24
    int8_t m_broadPhaseBorderBehaviour;              // +0x28 (the ctor writes one byte)
    hkUint8 m_pad29[7];                              // +0x29
    hkVector4 m_broadPhaseWorldAabbMin;              // +0x30
    hkVector4 m_broadPhaseWorldAabbMax;              // +0x40
    float m_collisionTolerance;                      // +0x50
    void* m_collisionFilter;                         // +0x54
    float m_expectedMaxLinearVelocity;               // +0x58
    float m_expectedMinPsiDeltaTime;                 // +0x5c
    void* m_memoryWatchDog;                          // +0x60
    int32_t m_broadPhaseNumMarkers;                  // +0x64
    int8_t m_contactPointGeneration;                 // +0x68 (one byte written)
    hkUint8 m_pad69[3];                              // +0x69
    float m_solverTau;                               // +0x6c
    float m_solverDamp;                              // +0x70
    int32_t m_solverIterations;                      // +0x74
    hkUint32 m_unusedPadding;                        // +0x78
    float m_iterativeLinearCastEarlyOutDistance;     // +0x7c
    int32_t m_iterativeLinearCastMaxIterations;      // +0x80
    float m_highFrequencyDeactivationPeriod;         // +0x84
    float m_lowFrequencyDeactivationPeriod;          // +0x88
    bool m_shouldActivateOnRigidBodyTransformChange;   // +0x8c
    hkUint8 m_pad8d[3];                              // +0x8d
    float m_toiCollisionResponseRotateNormal;        // +0x90
    bool m_enableDeactivation;                     // +0x94
    int8_t m_simulationType;                         // +0x95
    bool m_enableSimulationIslands;                // +0x96
    bool m_processActionsInSingleThread;           // +0x97
    bool m_synchronizeFrameAndPhysicsTime;         // +0x98
};

// =====================================================================================================================
// hkRigidBody
// =====================================================================================================================

// @ 0x010878b0
hkRigidBody::hkRigidBody(const hkRigidBodyCinfo& info)
    : hkEntity(info.m_shape)
{
    m_material.m_responseType = info.m_collisionResponse;
    m_processContactCallbackDelay = info.m_processContactCallbackDelay;
    m_collidable.m_collisionFilterInfo = info.m_collisionFilterInfo;
    m_fixed = (info.m_motionType == hkMotion::MOTION_FIXED);

    if (m_fixed)
    {
        hkFixedRigidMotion* motion = new hkFixedRigidMotion(info.m_position, info.m_rotation);   // class 0x2b, size 0x100
        m_motion = motion;
        motion->m_motionState.m_maxLinearVelocity = info.m_maxLinearVelocity;     // motion + 0xb4
        motion->m_motionState.m_maxAngularVelocity = info.m_maxAngularVelocity;   // motion + 0xb8
        motion->setDeactivationClass(1);
        m_collidable.m_motion = &m_motion->m_motionState;
        // fixed bodies: a penetration depth <= 0 means "unlimited"; NaN is kept as given
        if (!(info.m_allowedPenetrationDepth <= 0.0f))
            m_collidable.m_allowedPenetrationDepth = info.m_allowedPenetrationDepth;
        else
            m_collidable.m_allowedPenetrationDepth = HK_REAL_MAX;
    }
    else
    {
        hkRigidMotion* motion = hkRigidBody_createMotion(info.m_motionType, info.m_position, info.m_rotation,
                                                         info.m_mass, info.m_inertiaTensor, info.m_centerOfMass,
                                                         info.m_maxLinearVelocity, info.m_maxAngularVelocity);
        motion->setDeactivationClass((hkUint16)(int)info.m_solverDeactivation);   // movsx byte -> word
        m_motion = motion;
        activate();
        m_motion->setLinearVelocity(info.m_linearVelocity);
        activate();
        m_motion->setAngularVelocity(info.m_angularVelocity);
        m_collidable.m_motion = &m_motion->m_motionState;
        setDeactivator(info.m_rigidBodyDeactivatorType);
        m_collidable.m_allowedPenetrationDepth = info.m_allowedPenetrationDepth;
    }
    m_motion->m_linearDamping = info.m_linearDamping;      // motion + 0xc8
    m_motion->m_angularDamping = info.m_angularDamping;    // motion + 0xcc

    if (m_collidable.m_shape != 0)
    {
        hkVector4 extent;
        hkRigidBody_calcShapeExtent(m_collidable.m_shape, this, &extent);
        // penetration depth <= 0 (ordered; not for NaN) -> derive from the shape extent
        if (m_collidable.m_allowedPenetrationDepth <= 0.0f)
            hkRigidBody_setAllowedPenetrationFromExtent(&extent, &m_collidable);
    }

    if (info.m_qualityType != 0)
        m_collidable.m_objectQualityType = (hkUint16)(hkInt16)(int)info.m_qualityType;
    else if (m_fixed)
        m_collidable.m_objectQualityType = 1;
    else
        m_collidable.m_objectQualityType = (hkUint16)((info.m_motionType != hkMotion::MOTION_KEYFRAMED) + 2);

    m_autoRemoveLevel = info.m_autoRemoveLevel;
    m_material.m_friction = info.m_friction;
    m_material.m_restitution = info.m_restitution;

    if (m_fixed || m_motion->getType() == hkMotion::MOTION_KEYFRAMED)
        m_isFixedOrKeyframed = true;
    else
        m_isFixedOrKeyframed = false;
}

// @ 0x01087b00
void hkRigidBody::getCinfo(hkRigidBodyCinfo& info) const
{
    info.m_autoRemoveLevel = m_autoRemoveLevel;
    info.m_processContactCallbackDelay = m_processContactCallbackDelay;
    info.m_rigidBodyDeactivatorType = (m_deactivator != 0) ? (int8_t)m_deactivator->getDeactivatorType() : (int8_t)1;
    info.m_friction = m_material.m_friction;
    info.m_collisionResponse = m_material.m_responseType;
    info.m_restitution = m_material.m_restitution;
    const hkRigidMotion* motion = m_motion;
    info.m_linearDamping = motion->m_linearDamping;
    info.m_angularDamping = motion->m_angularDamping;
    memcpy(&info.m_linearVelocity, &motion->m_linearVelocity, sizeof(hkVector4));      // dword copies
    memcpy(&info.m_angularVelocity, &motion->m_angularVelocity, sizeof(hkVector4));
    info.m_mass = m_motion->getMass();
    m_motion->getInertiaLocal(info.m_inertiaTensor);
    info.m_motionType = (int8_t)m_motion->getType();
    info.m_solverDeactivation = (int8_t)m_motion->m_motionState.m_deactivationClass;
    info.m_maxLinearVelocity = m_motion->m_motionState.m_maxLinearVelocity;
    info.m_maxAngularVelocity = m_motion->m_motionState.m_maxAngularVelocity;
    memcpy(&info.m_position, &m_motion->m_motionState.m_transform.m[12], sizeof(hkVector4));   // translation (motion + 0x40)
    memcpy(&info.m_rotation, &m_motion->m_motionState.m_sweptTransform.m_rotation1, sizeof(hkQuaternion));   // motion + 0x80
    memcpy(&info.m_centerOfMass, &m_motion->m_motionState.m_sweptTransform.m_centerOfMassLocal, sizeof(hkVector4));   // motion + 0x90
    info.m_shape = m_collidable.m_shape;
    info.m_collisionFilterInfo = m_collidable.m_collisionFilterInfo;
    info.m_allowedPenetrationDepth = m_collidable.m_allowedPenetrationDepth;
    info.m_qualityType = (int8_t)m_collidable.m_objectQualityType;
}

// @ 0x01087ca0
void hkWorldObject::copyProperties(const hkWorldObject* other)
{
    if ((m_properties.m_capacityAndFlags & 0x3fffffff) < other->m_properties.m_size)
    {
        if (m_properties.m_capacityAndFlags >= 0)
            hkThreadMemory::getInstance().deallocateChunk(m_properties.m_data,
                (m_properties.m_capacityAndFlags & 0x3fffffff) * (int)sizeof(hkProperty), HK_MEMORY_CLASS_ARRAY);
        m_properties.m_data = (hkProperty*)hkThreadMemory::getInstance().allocateChunk(
                other->m_properties.m_size * (int)sizeof(hkProperty), HK_MEMORY_CLASS_ARRAY);
        m_properties.m_capacityAndFlags = (m_properties.m_capacityAndFlags & 0x40000000) | other->m_properties.m_size;
    }
    int count = other->m_properties.m_size;
    m_properties.m_size = count;
    for (int i = 0; i < count; ++i)
        memcpy(&m_properties.m_data[i], &other->m_properties.m_data[i], sizeof(hkProperty));   // 4 dword copies
}

// @ 0x01087d50
hkEntity::hkEntity(hkFinishLoadedObjectFlag flag)
    : hkWorldObject(flag)
{
    // the member arrays are default constructed to {data 0, size 0, capacity 0 | DONT_DEALLOCATE}
}

// @ 0x01087e20
void finishLoadedObject_hkRigidBody(void* p)
{
    if (p != 0)
    {
        hkFinishLoadedObjectFlag flag; flag.m_finishing = 1;
        // placement-constructs the hkEntity part, then installs the hkRigidBody vtable
        new (p) hkRigidBody(flag);
    }
}

// @ 0x01087e40
hkEntity* hkRigidBody::clone() const
{
    hkRigidBodyCinfo info;
    getCinfo(info);
    hkRigidBody* c = new hkRigidBody(info);
    if (c->m_motion != 0)
        delete c->m_motion;                      // direct deleting-destructor call (not a ref-count release)
    c->m_motion = static_cast<hkRigidMotion*>(m_motion->clone());
    c->m_collidable.m_motion = c->getMotionState();
    c->copyProperties(this);
    c->m_name = m_name;
    c->m_userData = m_userData;
    return c;
}

// @ 0x01087ed0
hkRigidBodyCinfo::hkRigidBodyCinfo()
{
    m_position.x = 0.0f; m_position.y = 0.0f; m_position.z = 0.0f; m_position.w = 0.0f;
    m_rotation.x = 0.0f; m_rotation.y = 0.0f; m_rotation.z = 0.0f; m_rotation.w = 1.0f;
    m_linearVelocity.x = 0.0f; m_linearVelocity.y = 0.0f; m_linearVelocity.z = 0.0f; m_linearVelocity.w = 0.0f;
    m_angularVelocity.x = 0.0f; m_angularVelocity.y = 0.0f; m_angularVelocity.z = 0.0f; m_angularVelocity.w = 0.0f;
    for (int i = 0; i < 3; ++i)                  // identity inertia tensor (columns)
    {
        m_inertiaTensor.m_col[i].x = (i == 0) ? 1.0f : 0.0f;
        m_inertiaTensor.m_col[i].y = (i == 1) ? 1.0f : 0.0f;
        m_inertiaTensor.m_col[i].z = (i == 2) ? 1.0f : 0.0f;
        m_inertiaTensor.m_col[i].w = 0.0f;
    }
    m_centerOfMass.x = 0.0f; m_centerOfMass.y = 0.0f; m_centerOfMass.z = 0.0f; m_centerOfMass.w = 0.0f;
    m_mass = 1.0f;
    m_maxLinearVelocity = 200.0f;                // 0x43480000
    m_maxAngularVelocity = 200.0f;
    m_linearDamping = 0.0f;
    m_angularDamping = 0.05000000074505806f;     // 0x3d4ccccd
    m_friction = 0.5f;
    m_restitution = 0.4000000059604645f;         // 0x3ecccccd
    m_allowedPenetrationDepth = -1.0f;
    m_motionType = 1;                            // MOTION_DYNAMIC
    m_rigidBodyDeactivatorType = 2;
    m_solverDeactivation = 2;
    m_qualityType = 0;
    m_collisionResponse = 1;                     // RESPONSE_SIMPLE_CONTACT
    m_processContactCallbackDelay = 0xffff;
    m_collisionFilterInfo = 0;
    m_shape = 0;
    m_autoRemoveLevel = 0;
}

// =====================================================================================================================
// hkWorldCinfo
// =====================================================================================================================

// @ 0x01087fd0
void hkWorldCinfo::setSolverType(SolverType t)
{
    switch (t)
    {
    case SOLVER_TYPE_2ITERS_SOFT:   m_solverTau = 0.30000001192092896f; m_solverDamp = 0.8999999761581421f; m_solverIterations = 2; return;
    case SOLVER_TYPE_2ITERS_MEDIUM: m_solverTau = 0.6000000238418579f;  m_solverDamp = 1.0f;                m_solverIterations = 2; return;
    case SOLVER_TYPE_2ITERS_HARD:   m_solverIterations = 2; m_solverTau = 0.8999999761581421f; m_solverDamp = 1.100000023841858f; return;
    case SOLVER_TYPE_4ITERS_SOFT:   m_solverTau = 0.30000001192092896f; m_solverDamp = 0.8999999761581421f; m_solverIterations = 4; return;
    case SOLVER_TYPE_4ITERS_MEDIUM: m_solverTau = 0.6000000238418579f;  m_solverDamp = 1.0f;                m_solverIterations = 4; return;
    case SOLVER_TYPE_4ITERS_HARD:   m_solverIterations = 4; m_solverTau = 0.8999999761581421f; m_solverDamp = 1.100000023841858f; return;
    case SOLVER_TYPE_8ITERS_SOFT:   m_solverTau = 0.30000001192092896f; m_solverDamp = 0.8999999761581421f; m_solverIterations = 8; return;
    case SOLVER_TYPE_8ITERS_MEDIUM: m_solverTau = 0.6000000238418579f;  m_solverDamp = 1.0f;                m_solverIterations = 8; return;
    case SOLVER_TYPE_8ITERS_HARD:   m_solverIterations = 8; m_solverTau = 0.8999999761581421f; m_solverDamp = 1.100000023841858f; return;
    default: return;
    }
}

// @ 0x010880e0
hkWorldCinfo::hkWorldCinfo()
{
    m_gravity.x = 0.0f;
    m_gravity.y = -9.800000190734863f;           // 0xc11ccccd
    m_gravity.z = 0.0f;
    m_gravity.w = 0.0f;
    m_enableSimulationIslands = true;
    m_broadPhaseQuerySize = 0x400;
    m_broadPhaseWorldAabbMin.w = 0.0f;
    m_broadPhaseWorldAabbMin.x = -500.0f;        // 0xc3fa0000
    m_broadPhaseWorldAabbMin.y = -500.0f;
    m_broadPhaseWorldAabbMin.z = -500.0f;
    m_broadPhaseWorldAabbMax.w = 0.0f;
    m_broadPhaseWorldAabbMax.x = 500.0f;         // 0x43fa0000
    m_broadPhaseWorldAabbMax.y = 500.0f;
    m_broadPhaseWorldAabbMax.z = 500.0f;
    m_collisionTolerance = 0.10000000149011612f; // 0x3dcccccd
    m_collisionFilter = 0;
    m_broadPhaseNumMarkers = 0;
    m_solverTau = 0.6000000238418579f;           // 0x3f19999a
    m_solverDamp = 1.0f;
    m_contactRestingVelocity = HK_REAL_MAX;
    m_solverIterations = 4;
    m_broadPhaseBorderBehaviour = 0;
    m_toiCollisionResponseRotateNormal = 0.20000000298023224f;   // 0x3e4ccccd
    m_expectedMaxLinearVelocity = 200.0f;
    m_expectedMinPsiDeltaTime = 0.03333333507180214f;            // 0x3d088889
    m_iterativeLinearCastEarlyOutDistance = 0.009999999776482582f;   // 0x3c23d70a
    m_iterativeLinearCastMaxIterations = 20;
    m_enableDeactivation = true;
    m_shouldActivateOnRigidBodyTransformChange = true;
    m_highFrequencyDeactivationPeriod = 0.10000000149011612f;
    m_lowFrequencyDeactivationPeriod = 1.0f;
    m_contactPointGeneration = 2;
    m_simulationType = 4;
    m_processActionsInSingleThread = true;
    m_synchronizeFrameAndPhysicsTime = true;
    m_memoryWatchDog = 0;
}

// @ 0x010881d0
void hkWorldCinfo::setBroadPhaseWorldSize(float size)
{
    float lo = size * -0.5f;                     // 0x13ec488
    m_broadPhaseWorldAabbMin.x = lo;
    m_broadPhaseWorldAabbMin.y = lo;
    m_broadPhaseWorldAabbMin.z = lo;
    m_broadPhaseWorldAabbMin.w = lo;
    float hi = size * 0.5f;                      // 0x1471064
    m_broadPhaseWorldAabbMax.x = hi;
    m_broadPhaseWorldAabbMax.y = hi;
    m_broadPhaseWorldAabbMax.z = hi;
    m_broadPhaseWorldAabbMax.w = hi;
}

// @ 0x01088200
hkWorldCinfo::hkWorldCinfo(hkFinishLoadedObjectFlag)
{
    // (finish-loaded constructor: only the reference count and vtable are reset)
    if (m_contactRestingVelocity == 0.0f)
        m_contactRestingVelocity = HK_REAL_MAX;
}
void finishLoadedObject_hkWorldCinfo(void* p)
{
    if (p != 0)
    {
        hkFinishLoadedObjectFlag flag; flag.m_finishing = 1;
        new (p) hkWorldCinfo(flag);
    }
}

// =====================================================================================================================
// hkRigidMotion
// =====================================================================================================================

// @ 0x01088230
void hkRigidMotion::setMass(float m)
{
    float massInv = (m == 0.0f) ? 0.0f : 1.0f / m;
    setMassInv(massInv);                         // tail jump through vtable slot 10
}

// @ 0x01088270
float hkRigidMotion::getMass() const
{
    // X87-PRECISION: the asm returns the quotient in ST(0) without rounding to float.
    if (m_massInv == 0.0f)
        return 0.0f;
    return 1.0f / m_massInv;
}

// @ 0x01088310
void hkRigidMotion::setPositionAndRotation(const hkVector4& pos, const hkQuaternion& rot)
{
    hkSweptTransformUtil::warpTo(pos, rot, m_motionState);
}

// @ 0x01088350
void hkRigidMotion::setDeactivationClass(hkUint16 c)
{
    m_motionState.m_deactivationClass = c;
}

// @ 0x010883c0
void hkRigidMotion::applyLinearImpulse(const hkVector4& imp)
{
    // X87-PRECISION: massInv * imp is added to the velocity without an intermediate float store.
    hkX87Real mInv = m_massInv;
    m_linearVelocity.x = (float)(mInv * imp.x + m_linearVelocity.x);
    m_linearVelocity.y = (float)(mInv * imp.y + m_linearVelocity.y);
    m_linearVelocity.z = (float)(mInv * imp.z + m_linearVelocity.z);
    m_linearVelocity.w = (float)(mInv * imp.w + m_linearVelocity.w);
}

// @ 0x01088410
// hkTransform::operator= compiled out of line: 16 dword copies.
hkTransform* hkTransform_assign(hkTransform* self, const hkTransform& o)
{
    memcpy(self, &o, sizeof(hkTransform));
    return self;
}

// @ 0x01088480
hkSweptTransform& hkSweptTransform::operator=(const hkSweptTransform& o)
{
    memcpy(this, &o, 0x50);                      // 20 dword copies
    return *this;
}

// @ 0x01088500
hkRigidMotion::hkRigidMotion(const hkVector4& position, const hkQuaternion& rotation)
{
    m_solverData = 0;
    m_linearVelocity.x = 0.0f; m_linearVelocity.y = 0.0f; m_linearVelocity.z = 0.0f; m_linearVelocity.w = 0.0f;
    m_angularVelocity.x = 0.0f; m_angularVelocity.y = 0.0f; m_angularVelocity.z = 0.0f; m_angularVelocity.w = 0.0f;
    hkMotionState_initMotionState(&m_motionState, position, rotation);
    m_linearDamping = 0.0f;
    m_angularDamping = 0.0f;
    // m_massInv / m_particleMinInertiaDiagInv are left to the derived class
}

// @ 0x01088570
void hkRigidMotion::step(const hkStepInfo& stepInfo)
{
    hkMotionState& ms = m_motionState;
    hkSweptTransform& st = ms.m_sweptTransform;

    // center of mass 0 = previous center of mass 1, with the step start time in w
    memcpy(&st.m_centerOfMass0, &st.m_centerOfMass1, sizeof(hkVector4));
    st.m_centerOfMass0.w = stepInfo.m_startTime;

    // clamp the linear velocity to maxLinearVelocity
    {
        // X87-PRECISION: the squared length stays on the x87 stack (products and sums are not stored).
        hkX87Real lenSq = ((hkX87Real)m_linearVelocity.x * m_linearVelocity.x
                           + (hkX87Real)m_linearVelocity.y * m_linearVelocity.y)
                          + (hkX87Real)m_linearVelocity.z * m_linearVelocity.z;
        hkX87Real maxSq = (hkX87Real)ms.m_maxLinearVelocity * ms.m_maxLinearVelocity;
        if (lenSq > maxSq)          // fcompp; skipped for <= or NaN
        {
            hkX87Real f = (hkX87Real)ms.m_maxLinearVelocity / hkX87Sqrt(lenSq);   // inline fsqrt, fdivr
            m_linearVelocity.x = (float)(f * m_linearVelocity.x);
            m_linearVelocity.y = (float)(f * m_linearVelocity.y);
            m_linearVelocity.z = (float)(f * m_linearVelocity.z);
            m_linearVelocity.w = (float)(f * m_linearVelocity.w);
        }
    }

    // integrate the center of mass: com1 += dt * v
    {
        hkX87Real dt = stepInfo.m_deltaTime;       // X87-PRECISION: dt*v is added without a float store
        st.m_centerOfMass1.x = (float)(dt * m_linearVelocity.x + st.m_centerOfMass1.x);
        st.m_centerOfMass1.y = (float)(dt * m_linearVelocity.y + st.m_centerOfMass1.y);
        st.m_centerOfMass1.z = (float)(dt * m_linearVelocity.z + st.m_centerOfMass1.z);
        st.m_centerOfMass1.w = (float)(dt * m_linearVelocity.w + st.m_centerOfMass1.w);
    }
    st.m_centerOfMass1.w = stepInfo.m_endTime;

    // rotation0 = rotation1, q = rotation1
    hkQuaternion q;
    memcpy(&q, &st.m_rotation1, sizeof(hkQuaternion));
    memcpy(&st.m_rotation0, &st.m_rotation1, sizeof(hkQuaternion));

    // half-angle vector h = (dt/2) * angularVelocity
    hkX87Real hdt = (hkX87Real)stepInfo.m_deltaTime * 0.5f;      // X87-PRECISION (register value)
    float hx = (float)(hdt * m_angularVelocity.x);
    float hy = (float)(hdt * m_angularVelocity.y);
    hkX87Real hzReg = hdt * m_angularVelocity.z;                 // fst: stored copy and live register
    float hz = (float)hzReg;
    // len2 = (hz*hz + hy*hy + hx*hx) * 4/pi^2   (x87 products and sums unrounded, final store rounded)
    hkX87Real sum = hzReg * hz;                                  // X87-PRECISION
    sum = sum + (hkX87Real)hy * hy;
    sum = sum + (hkX87Real)hx * hx;
    float len2 = (float)(sum * 0.40528470277786255f);            // 0x149e068 = 0x3ecf817a

    // limit the rotation per step: min(maxAngularVelocity * dt, 0.9)
    hkX87Real limit = (hkX87Real)ms.m_maxAngularVelocity * stepInfo.m_deltaTime;   // X87-PRECISION
    if (0.8999999761581421f < limit)                              // 0x13ec4b4 = 0x3f666666
        limit = 0.8999999761581421f;
    float limitSq = (float)(limit * limit);
    if (!(len2 <= limitSq))                                       // greater, or unordered
    {
        hkX87Real f = limit / hkX87Sqrt((hkX87Real)len2);          // fsqrt, fdivp
        m_angularVelocity.x = (float)(f * m_angularVelocity.x);
        m_angularVelocity.y = (float)(f * m_angularVelocity.y);
        m_angularVelocity.z = (float)(f * m_angularVelocity.z);
        m_angularVelocity.w = (float)(f * m_angularVelocity.w);
        len2 = limitSq;
        hx = (float)(hx * f);
        hy = (float)(hy * f);
        hz = (float)(hz * f);
    }

    // hw ~ cos(theta/2) polynomial: ((1 - len2*a) - len2^2*b) - len2^3*c
    // X87-PRECISION: every intermediate stays on the x87 stack.
    hkX87Real l2 = len2;
    hkX87Real l2sq = l2 * l2;
    hkX87Real t = 1.0f - l2 * 0.8229479789733887f;               // 0x149e064 = 0x3f52acb8
    t = t - l2sq * 0.1305290013551712f;                          // 0x149e060 = 0x3e05a965
    t = t - (l2sq * l2) * 0.04440800100564957f;                  // 0x149e05c = 0x3d35e52a
    hkQuaternion h;
    h.x = hx; h.y = hy; h.z = hz;
    h.w = (float)t;

    q.setMul(h, q);                                               // q = h * q
    q.normalize();

    ms.m_deltaAngle.x = hx + hx;
    ms.m_deltaAngle.y = hy + hy;
    ms.m_deltaAngle.z = hz + hz;
    ms.m_deltaAngle.w = h.w + h.w;                                // overwritten right below (dead store kept)
    ms.m_deltaAngle.w = (float)(hkX87Sqrt((hkX87Real)len2) * 3.1415927410125732f);   // 0x149e058 = pi

    memcpy(&st.m_rotation1, &q, sizeof(hkQuaternion));
    hkRotation_set(&ms.m_transform, st.m_rotation1);

    // translation = com1 - R * centerOfMassLocal
    hkX87Real cx = st.m_centerOfMassLocal.x;
    hkX87Real cy = st.m_centerOfMassLocal.y;
    hkX87Real cz = st.m_centerOfMassLocal.z;
    const float* m = ms.m_transform.m;
    float r0 = (float)((cz * m[8] + cy * m[4]) + cx * m[0]);     // stored to a float slot
    float r1 = (float)((cz * m[9] + cy * m[5]) + cx * m[1]);
    hkX87Real r2 = (cz * m[10] + cy * m[6]) + cx * m[2];         // X87-PRECISION: not stored
    ms.m_transform.m[12] = st.m_centerOfMass1.x - r0;
    ms.m_transform.m[13] = st.m_centerOfMass1.y - r1;
    ms.m_transform.m[14] = (float)(st.m_centerOfMass1.z - r2);
    memcpy(&ms.m_transform.m[15], &st.m_centerOfMass1.w, sizeof(float));
}

// @ 0x010888c0
hkMotionState& hkMotionState::operator=(const hkMotionState& o)
{
    hkTransform_assign(&m_transform, o.m_transform);
    m_sweptTransform = o.m_sweptTransform;
    memcpy(&m_deltaAngle, &o.m_deltaAngle, sizeof(hkVector4));           // dword copies +0x90..+0x9c
    memcpy(&m_objectRadius, &o.m_objectRadius, 3 * sizeof(float));       // +0xa0, +0xa4, +0xa8
    m_deactivationClass = o.m_deactivationClass;
    m_deactivationCounter = o.m_deactivationCounter;
    return *this;
}
