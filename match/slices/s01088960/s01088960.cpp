// Havok 3.1.0 physics: hkEntity (listeners, activation, statistics, ctor/dtor), hkRigidMotion state
// copy, hkConstraintConstructionKit and hkGenericConstraintData helpers, and the generic-constraint
// linear-DOF command handlers (including the atan2 angle helper).
// Equivalent portable source, not byte-exact.
#include <stddef.h>
#include "types.h"

// Value kept on the x87 stack in 80-bit precision in the original (never stored to memory).
// X87-PRECISION: switch this typedef to experiment (float / double / long double).
typedef double hkX87Real;

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
enum { HK_ARRAY_FLAG_MASK = 0x3fffffff, HK_ARRAY_DONT_DEALLOCATE = (int)0x80000000 };
struct hkArrayUtil { static void _reserveMore(void* arr, int elemSize); };
struct hkThreadMemory { void deallocateChunk(void* p, int nbytes, int memClass); };
extern unsigned long g_hkThreadMemoryTlsIndex;       // 0x16e4174
static inline hkThreadMemory* getThreadMemory() { return (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }

template <typename T>
struct hkArray {
    T* m_data; int m_size; int m_capacityAndFlags;
    void pushBack(const T& t) {
        if (m_size == (m_capacityAndFlags & HK_ARRAY_FLAG_MASK)) hkArrayUtil::_reserveMore(this, (int)sizeof(T));
        m_data[m_size] = t;
        m_size = m_size + 1;
    }
    int indexOf(const T& t) const {
        int i = 0;
        while (i < m_size) { if (m_data[i] == t) return i; ++i; }
        return -1;
    }
    // frees the buffer if owned (flag bit clear)
    void freeBuffer(int elemSize) {
        if (m_capacityAndFlags >= 0)
            getThreadMemory()->deallocateChunk(m_data, (m_capacityAndFlags & HK_ARRAY_FLAG_MASK) * elemSize, 0x14);
    }
    // hkArray::clearAndDeallocate (size must be 0)
    void clearAndDeallocate(int elemSize) {
        freeBuffer(elemSize);
        m_data = 0;
        m_size = 0;
        m_capacityAndFlags = (int)(((unsigned)m_capacityAndFlags & 0xc0000000u) | 0x80000000u);
    }
};

struct hkVector4 { float x, y, z, w; };
struct hkReferencedObject {
    uint16_t m_memSizeAndFlags;
    uint16_t m_referenceCount;
    hkReferencedObject() : m_referenceCount(1) {}
    virtual ~hkReferencedObject() {}
    virtual void calcStatistics(struct hkStatisticsCollector* c) const {}
    void addReference() { if (m_memSizeAndFlags != 0) m_referenceCount = (uint16_t)(m_referenceCount + 1); }
    void removeReference() {
        if (m_memSizeAndFlags != 0) {
            m_referenceCount = (uint16_t)(m_referenceCount - 1);
            if (m_referenceCount == 0) delete this;
        }
    }
};
struct hkStatisticsCollector {
    virtual void s0();
    virtual void beginObject(const char* name, int mode, const void* obj);                                     // +4
    virtual void addArray(const char* name, int elemSize, const void* ptr, int usedBytes, int allocBytes);    // +8
    virtual void addReferencedObject(const char* name, int mode, const void* obj);                             // +0xc
    virtual void s4(); virtual void s5();
    virtual void endObject();                                                                                  // +0x18
};

// ------------------------------------------------------------ motion
struct hkMotionState { char m_data[0xb0]; };
void hkMotionState_assign(hkMotionState* dst, const hkMotionState* src);    // FUN_010888c0: hkMotionState::operator=
struct hkMotion : hkReferencedObject { int m_solverData; };
struct hkRigidMotion : hkMotion {
    hkMotionState m_motionState;          // +0x10
    float m_massInv;                      // +0xc0
    float m_particleMinInertiaDiagInv;    // +0xc4
    float m_linearDamping;                // +0xc8
    float m_angularDamping;               // +0xcc
    uint32_t m_linearVelocity[4];         // +0xd0 (copied as raw bits)
    uint32_t m_angularVelocity[4];        // +0xe0
    virtual void getMotionStateAndVelocities(hkMotion* motionOut);
};

// @ 0x01088960
void hkRigidMotion::getMotionStateAndVelocities(hkMotion* motionOut)
{
    hkRigidMotion* out = static_cast<hkRigidMotion*>(motionOut);
    hkMotionState_assign(&out->m_motionState, &m_motionState);
    out->m_linearVelocity[0] = m_linearVelocity[0];
    out->m_linearVelocity[1] = m_linearVelocity[1];
    out->m_linearVelocity[2] = m_linearVelocity[2];
    out->m_linearVelocity[3] = m_linearVelocity[3];
    out->m_angularVelocity[0] = m_angularVelocity[0];
    out->m_angularVelocity[1] = m_angularVelocity[1];
    out->m_angularVelocity[2] = m_angularVelocity[2];
    out->m_angularVelocity[3] = m_angularVelocity[3];
}

// ------------------------------------------------------------ hkWorldObject (as needed here)
struct hkShape;
struct hkMultiThreadLock { uint32_t m_threadId; int m_lockCount; };
struct hkLinkedCollidable {
    hkShape* m_shape; uint32_t m_shapeKey; void* m_motion; void* m_parent; int m_ownerOffset;
    uint32_t m_handle[3]; float m_allowedPenetrationDepth;
    hkArray<void*[2]> m_collisionEntries;       // +0x24 (8-byte entries)
};
struct hkProperty { uint32_t m_key, m_pad, m_lo, m_hi; };
struct hkWorldObject : hkReferencedObject {
    void* m_world;                      // +0x08
    void* m_userData;                   // +0x0c
    const char* m_name;                 // +0x10
    hkMultiThreadLock m_multithreadLock;// +0x14
    hkLinkedCollidable m_collidable;    // +0x1c
    hkArray<hkProperty> m_properties;   // +0x4c
    hkWorldObject(const hkShape* shape, int broadPhaseType);      // 0x01082800
    virtual ~hkWorldObject();                                     // 0x01082770
    virtual void calcStatistics(hkStatisticsCollector* c) const;  // 0x01082660
    virtual void slot2() {}
    virtual void* getMotionState() = 0;
    virtual void slot4() = 0;
};

// ------------------------------------------------------------ hkEntity
struct hkSimulationIsland { char pad[0x28]; uint8_t m_active; };
struct hkEntityDeactivator : hkReferencedObject {};
struct hkMaterial { uint8_t m_responseType; float m_friction; float m_restitution; };
struct hkEntityListener; struct hkCollisionListener; struct hkEntityActivationListener; struct hkAction;
struct hkConstraintInternal { char pad[0x1c]; };
struct hkConstraintInstance;
struct hkWorld;
struct hkBool { uint8_t b; };
struct hkMotionBase;

struct hkWorldOperationUtil {
    static void markIslandActive(hkWorld* w, hkSimulationIsland* i);     // 0x010a0130
    static void markIslandInactive(hkWorld* w, hkSimulationIsland* i);   // 0x010a00e0
};
struct hkEntityCallbackUtil { static void fireEntityDeleted(struct hkEntity* e); };    // 0x0109e790

struct hkEntity : hkWorldObject {
    hkMotionBase* m_motion;                              // +0x58
    hkSimulationIsland* m_simulationIsland;              // +0x5c
    hkMaterial m_material;                               // +0x60
    hkEntityDeactivator* m_deactivator;                  // +0x6c
    hkArray<hkConstraintInternal> m_constraintsMaster;   // +0x70 (0x1c-byte entries)
    hkArray<hkConstraintInstance*> m_constraintsSlave;   // +0x7c
    hkArray<uint8_t> m_constraintRuntime;                // +0x88
    uint16_t m_storageIndex;                             // +0x94
    uint16_t m_processContactCallbackDelay;              // +0x96
    char m_autoRemoveLevel;                              // +0x98
    uint8_t m_fixed;                                     // +0x99
    uint8_t m_isFixedOrKeyframed;                        // +0x9a
    uint8_t m_internalCollideFlag;                       // +0x9b
    hkArray<hkCollisionListener*> m_collisionListeners;  // +0x9c
    hkArray<hkEntityActivationListener*> m_activationListeners;  // +0xa8
    hkArray<hkEntityListener*> m_entityListeners;        // +0xb4
    hkArray<hkAction*> m_actions;                        // +0xc0
    uint32_t m_uid;                                      // +0xcc

    explicit hkEntity(const hkShape* shape);
    ~hkEntity();
    virtual void calcStatistics(hkStatisticsCollector* c) const;
    virtual void deallocateInternalArrays();
    void setDeactivator(hkEntityDeactivator* d);
    void removeEntityListener(hkEntityListener* l);
    void removeCollisionListener(hkCollisionListener* l);
    hkBool isActive() const;
    void activate();
    void deactivate();
    void addEntityListener(hkEntityListener* l);
    void addCollisionListener(hkCollisionListener* l);
};

// @ 0x010889e0
void hkEntity::setDeactivator(hkEntityDeactivator* d)
{
    if (d != 0) d->addReference();
    if (m_deactivator != 0) m_deactivator->removeReference();
    m_deactivator = d;
}

// @ 0x01088a20
// (assert compiled out: writes data[-1] when the listener is absent, as the original does)
void hkEntity::removeEntityListener(hkEntityListener* l)
{
    int i = m_entityListeners.indexOf(l);
    m_entityListeners.m_data[i] = 0;
}

// @ 0x01088a70
void hkEntity::removeCollisionListener(hkCollisionListener* l)
{
    int i = m_collisionListeners.indexOf(l);
    m_collisionListeners.m_data[i] = 0;
}

// @ 0x01088ac0
hkBool hkEntity::isActive() const
{
    hkBool r;
    if (m_simulationIsland == 0) { r.b = 0; return r; }
    r.b = m_simulationIsland->m_active;
    return r;
}

// @ 0x01088ae0
void hkEntity::activate()
{
    if (m_simulationIsland != 0 && m_simulationIsland->m_active != 0) return;
    if (m_fixed != 0) return;
    if (m_world != 0)
        hkWorldOperationUtil::markIslandActive((hkWorld*)m_world, m_simulationIsland);
}

// @ 0x01088b10
void hkEntity::deactivate()
{
    if (m_simulationIsland != 0 && m_simulationIsland->m_active != 0)
        hkWorldOperationUtil::markIslandInactive((hkWorld*)m_world, m_simulationIsland);
}

// @ 0x01088b30
void hkEntity::calcStatistics(hkStatisticsCollector* c) const
{
    c->beginObject("Entity", 2, this);
    hkWorldObject::calcStatistics(c);
    c->addReferencedObject("Motion", 4, m_motion);
    c->addReferencedObject("Deactivator", 4, m_deactivator);
    if (-1 < m_collisionListeners.m_capacityAndFlags)
        c->addArray("CollisionListnr", 4, m_collisionListeners.m_data,
                    m_collisionListeners.m_size << 2, m_collisionListeners.m_capacityAndFlags << 2);
    if (-1 < m_activationListeners.m_capacityAndFlags)
        c->addArray("ActLstnrPtrs", 4, m_activationListeners.m_data,
                    m_activationListeners.m_size << 2, m_activationListeners.m_capacityAndFlags << 2);
    if (-1 < m_entityListeners.m_capacityAndFlags)
        c->addArray("ListenerPtrs.", 4, m_entityListeners.m_data,
                    m_entityListeners.m_size << 2, m_entityListeners.m_capacityAndFlags << 2);
    c->endObject();
}

// @ 0x01088c20
// Re-use the first empty slot, else append.
void hkEntity::addEntityListener(hkEntityListener* l)
{
    int i = 0;
    if (0 < m_entityListeners.m_size) {
        hkEntityListener** p = m_entityListeners.m_data;
        do {
            if (*p == 0) {
                if (-1 < i) { m_entityListeners.m_data[i] = l; return; }
                break;
            }
            ++i; ++p;
        } while (i < m_entityListeners.m_size);
    }
    m_entityListeners.pushBack(l);
}

// @ 0x01088c90
void hkEntity::addCollisionListener(hkCollisionListener* l)
{
    int i = 0;
    if (0 < m_collisionListeners.m_size) {
        hkCollisionListener** p = m_collisionListeners.m_data;
        do {
            if (*p == 0) {
                if (-1 < i) { m_collisionListeners.m_data[i] = l; return; }
                break;
            }
            ++i; ++p;
        } while (i < m_collisionListeners.m_size);
    }
    m_collisionListeners.pushBack(l);
}

// @ 0x01088d00
// Deletes an entity through its scalar deleting destructor (no-op for null).
void hkEntity_delete(hkEntity* e)
{
    if (e != 0) delete e;
}

// @ 0x01088d20
hkEntity::hkEntity(const hkShape* shape) : hkWorldObject(shape, 1 /* BROAD_PHASE_ENTITY */)
{
    m_material.m_friction = 0.5f;                 // 0x3f000000
    m_material.m_restitution = 0.4f;              // 0x3ecccccd
    m_constraintsMaster.m_data = 0; m_constraintsMaster.m_size = 0; m_constraintsMaster.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_constraintsSlave.m_data = 0;  m_constraintsSlave.m_size = 0;  m_constraintsSlave.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_constraintRuntime.m_data = 0; m_constraintRuntime.m_size = 0; m_constraintRuntime.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_collisionListeners.m_data = 0; m_collisionListeners.m_size = 0; m_collisionListeners.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_activationListeners.m_data = 0; m_activationListeners.m_size = 0; m_activationListeners.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_entityListeners.m_data = 0; m_entityListeners.m_size = 0; m_entityListeners.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_actions.m_data = 0; m_actions.m_size = 0; m_actions.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_simulationIsland = 0;
    m_deactivator = 0;
    m_storageIndex = 0xffff;
    m_uid = 0xffffffffu;
}

// @ 0x01088de0
hkEntity::~hkEntity()
{
    hkEntityCallbackUtil::fireEntityDeleted(this);
    if (m_deactivator != 0) m_deactivator->removeReference();
    m_actions.freeBuffer(4);
    m_entityListeners.freeBuffer(4);
    m_activationListeners.freeBuffer(4);
    m_collisionListeners.freeBuffer(4);
    m_constraintRuntime.freeBuffer(1);
    m_constraintsSlave.freeBuffer(4);
    m_constraintsMaster.freeBuffer(0x1c);
}

// @ 0x01088f70
void hkEntity::deallocateInternalArrays()
{
    if (m_collidable.m_collisionEntries.m_size == 0)
        m_collidable.m_collisionEntries.clearAndDeallocate(8);
    if (m_constraintsMaster.m_size == 0)
        m_constraintsMaster.clearAndDeallocate(0x1c);
    if (m_constraintsSlave.m_size == 0)
        m_constraintsSlave.clearAndDeallocate(4);
    if (m_constraintRuntime.m_size == 0)
        m_constraintRuntime.clearAndDeallocate(1);

    // listener arrays: only released when every slot is empty
    int i = 0;
    for (; i < m_collisionListeners.m_size; ++i)
        if (m_collisionListeners.m_data[i] != 0) goto L_act;
    m_collisionListeners.clearAndDeallocate(4);
L_act:
    for (i = 0; i < m_activationListeners.m_size; ++i)
        if (m_activationListeners.m_data[i] != 0) goto L_ent;
    m_activationListeners.clearAndDeallocate(4);
L_ent:
    for (i = 0; i < m_entityListeners.m_size; ++i)
        if (m_entityListeners.m_data[i] != 0) goto L_act2;
    m_entityListeners.clearAndDeallocate(4);
L_act2:
    for (i = 0; i < m_actions.m_size; ++i)
        if (m_actions.m_data[i] != 0) return;
    m_actions.clearAndDeallocate(4);
}

// ------------------------------------------------------------ constraint construction kit
struct hkConstraintInfo { int m_maxSizeOfJacobians, m_sizeOfJacobians, m_sizeOfSchemas, m_numSolverResults; };
struct hkGenericConstraintDataScheme {
    hkConstraintInfo m_info;                 // +0x00
    hkArray<hkVector4> m_data;               // +0x10
    hkArray<int> m_commands;                 // +0x1c
    void* m_modifiers[3];                    // +0x28
    void* m_motors[3];                       // +0x34
};
struct hkConstraintData : hkReferencedObject { };
struct hkGenericConstraintData : hkConstraintData {
    hkGenericConstraintDataScheme m_scheme;  // +0x0c
    virtual void getConstraintInfo(hkConstraintInfo& out) const;
    struct RuntimeInfo { int m_sizeOfExternalRuntime; int m_numSolverResults; };
    virtual void getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& infoOut) const;
};
static inline void copyVec4(hkVector4* dst, const hkVector4* src)
{
    // raw 32-bit copies (no x87 load/store, so signalling NaN payloads survive)
    const uint32_t* s = (const uint32_t*)src; uint32_t* d = (uint32_t*)dst;
    d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3];
}

enum {
    CMD_END = 0, CMD_SET_PIVOT_A = 1, CMD_SET_PIVOT_B = 2, CMD_SET_LINEAR_DOF_WORLD = 5, CMD_CONSTRAIN_LINEAR_DOF = 6,
    CMD_SET_BASIS_A_BODY_FRAME = 10, CMD_SET_BASIS_B_BODY_FRAME = 11, CMD_CONSTRAIN_TO_ANGULAR_DOF = 12
};

struct hkConstraintConstructionKit {
    hkGenericConstraintData* m_constraint;       // +0x00
    hkGenericConstraintDataScheme* m_scheme;     // +0x04
    int m_stiffnessReference;                    // +0x08
    int m_dampingReference;                      // +0x0c
    uint8_t m_linearDofSpecifiedA[3];            // +0x10
    uint8_t m_linearDofSpecifiedB[3];            // +0x13
    uint8_t m_angularBasisSpecifiedA;            // +0x16
    uint8_t m_angularBasisSpecifiedB;            // +0x17
    uint8_t m_pivotSpecifiedA;                   // +0x18
    uint8_t m_pivotSpecifiedB;                   // +0x19
    void begin(hkGenericConstraintData* data);
    int setLinearDofWorld(const hkVector4& dof, int index);
    void constrainLinearDof(int index);
    void setAngularBasisABodyFrame();
    void setAngularBasisBBodyFrame();
    void constrainToAngularDof(int index);
    int setPivotA(const hkVector4& pivot);
    int setPivotB(const hkVector4& pivot);
    void end();
};

// @ 0x01089280
void hkConstraintConstructionKit::begin(hkGenericConstraintData* data)
{
    m_scheme = &data->m_scheme;                  // FUN_008dc790: lea eax,[ecx+0xc]
    m_constraint = data;
    m_stiffnessReference = 0;
    m_dampingReference = 0;
    m_linearDofSpecifiedA[0] = 0; m_linearDofSpecifiedA[1] = 0; m_linearDofSpecifiedA[2] = 0;
    m_linearDofSpecifiedB[0] = 0; m_linearDofSpecifiedB[1] = 0; m_linearDofSpecifiedB[2] = 0;
    m_pivotSpecifiedA = 0;
    m_pivotSpecifiedB = 0;
    m_angularBasisSpecifiedA = 0;
    m_angularBasisSpecifiedB = 0;
}

// @ 0x010892c0
int hkConstraintConstructionKit::setLinearDofWorld(const hkVector4& dof, int index)
{
    m_scheme->m_commands.pushBack(CMD_SET_LINEAR_DOF_WORLD);
    m_scheme->m_commands.pushBack(index);
    int dataIndex = m_scheme->m_data.m_size;
    hkVector4 v; copyVec4(&v, &dof);
    m_scheme->m_data.pushBack(v);
    m_linearDofSpecifiedA[index] = 1;
    m_linearDofSpecifiedB[index] = 1;
    return dataIndex;
}

// @ 0x01089390
void hkConstraintConstructionKit::constrainLinearDof(int index)
{
    m_scheme->m_commands.pushBack(CMD_CONSTRAIN_LINEAR_DOF);
    m_scheme->m_commands.pushBack(index);
    hkConstraintInfo& info = m_scheme->m_info;
    info.m_sizeOfSchemas += 4;
    info.m_sizeOfJacobians += 0x30;
    info.m_numSolverResults += 1;
}

// @ 0x01089420
void hkConstraintConstructionKit::setAngularBasisABodyFrame()
{
    m_scheme->m_commands.pushBack(CMD_SET_BASIS_A_BODY_FRAME);
    m_angularBasisSpecifiedA = 1;
}

// @ 0x01089460
void hkConstraintConstructionKit::setAngularBasisBBodyFrame()
{
    m_scheme->m_commands.pushBack(CMD_SET_BASIS_B_BODY_FRAME);
    m_angularBasisSpecifiedB = 1;
}

// @ 0x010894a0
void hkConstraintConstructionKit::constrainToAngularDof(int index)
{
    m_scheme->m_commands.pushBack(CMD_CONSTRAIN_TO_ANGULAR_DOF);
    m_scheme->m_commands.pushBack(index);
    hkConstraintInfo* info = &m_scheme->m_info;
    info->m_sizeOfSchemas += 4;
    info->m_sizeOfJacobians += 0x20;
    info->m_numSolverResults += 1;
    info = &m_scheme->m_info;
    info->m_sizeOfJacobians += 0x20;
    info->m_sizeOfSchemas += 4;
    info->m_numSolverResults += 1;
}

// @ 0x01089550
int hkConstraintConstructionKit::setPivotA(const hkVector4& pivot)
{
    m_scheme->m_commands.pushBack(CMD_SET_PIVOT_A);
    int dataIndex = m_scheme->m_data.m_size;
    hkVector4 v; copyVec4(&v, &pivot);
    m_scheme->m_data.pushBack(v);
    m_pivotSpecifiedA = 1;
    return dataIndex;
}

// @ 0x010895e0
int hkConstraintConstructionKit::setPivotB(const hkVector4& pivot)
{
    m_scheme->m_commands.pushBack(CMD_SET_PIVOT_B);
    int dataIndex = m_scheme->m_data.m_size;
    hkVector4 v; copyVec4(&v, &pivot);
    m_scheme->m_data.pushBack(v);
    m_pivotSpecifiedB = 1;
    return dataIndex;
}

// @ 0x01089670
void hkConstraintConstructionKit::end()
{
    m_scheme->m_commands.pushBack(CMD_END);
}

// @ 0x010896b0
void hkGenericConstraintData::getConstraintInfo(hkConstraintInfo& out) const
{
    out.m_maxSizeOfJacobians = 0; out.m_sizeOfJacobians = 0; out.m_sizeOfSchemas = 0; out.m_numSolverResults = 0;
    out.m_maxSizeOfJacobians = m_scheme.m_info.m_maxSizeOfJacobians;
    out.m_sizeOfJacobians = m_scheme.m_info.m_sizeOfJacobians;
    out.m_sizeOfSchemas = m_scheme.m_info.m_sizeOfSchemas;
    out.m_numSolverResults = m_scheme.m_info.m_numSolverResults;
}

// @ 0x010896e0
void hkGenericConstraintData::getRuntimeInfo(hkBool, RuntimeInfo& infoOut) const
{
    int n = m_scheme.m_info.m_numSolverResults;
    infoOut.m_numSolverResults = n;
    infoOut.m_sizeOfExternalRuntime = n << 3;
}

// ------------------------------------------------------------ generic constraint command handlers
struct hk1dLinearBilateralConstraintInfo {
    uint32_t m_pivotA[4];            // copied raw from the parameter block
    uint32_t m_pivotB[4];
    uint32_t m_constrainedDofW[4];
};
struct hkConstraintQueryIn; struct hkConstraintQueryOut;
// cdecl in the binary (caller cleans the three pushed arguments)
void hk1dLinearBilateralConstraintBuildJacobian(const hk1dLinearBilateralConstraintInfo* info,
                                                const hkConstraintQueryIn* in, hkConstraintQueryOut* out);
struct hkGenericConstraintParameters {
    uint32_t m_vec[4 * 2];           // +0x00: pivotA, pivotB (two hkVector4); further hkVector4 entries follow
    uint32_t m_more[0xb8 / 4 - 8];
    int m_numJacobians;              // +0xb8 (running count of built jacobians)
};

// @ 0x01089700
// Build the three world-axis linear jacobians (1,0,0), (0,1,0), (0,0,1); bump the jacobian count by 3.
void __stdcall hkGenericConstraint_buildLinearBasisWorld(int, int, int, hkGenericConstraintParameters* p,
                                                         const hkConstraintQueryIn* in, hkConstraintQueryOut* out)
{
    hk1dLinearBilateralConstraintInfo info;
    for (int i = 0; i < 4; ++i) { info.m_pivotA[i] = p->m_vec[i]; info.m_pivotB[i] = p->m_vec[4 + i]; }
    info.m_constrainedDofW[3] = 0;
    info.m_constrainedDofW[2] = 0;
    info.m_constrainedDofW[1] = 0;
    info.m_constrainedDofW[0] = 0x3f800000;            // 1.0f
    hk1dLinearBilateralConstraintBuildJacobian(&info, in, out);
    info.m_constrainedDofW[0] = 0;
    info.m_constrainedDofW[1] = 0x3f800000;
    hk1dLinearBilateralConstraintBuildJacobian(&info, in, out);
    info.m_constrainedDofW[1] = 0;
    info.m_constrainedDofW[2] = 0x3f800000;
    hk1dLinearBilateralConstraintBuildJacobian(&info, in, out);
    p->m_numJacobians = p->m_numJacobians + 3;
}

// @ 0x010897d0
// CMD_CONSTRAIN_LINEAR_DOF handler: advance the command stream by one int, take the DOF vector at
// parameter vector [command + 2], build one jacobian.
void __stdcall hkGenericConstraint_buildLinearDof(int** commands, int, int, hkGenericConstraintParameters* p,
                                                  const hkConstraintQueryIn* in, hkConstraintQueryOut* out)
{
    *commands += 1;
    int idx = **commands;
    const uint32_t* dof = (const uint32_t*)p + (idx + 2) * 4;
    hk1dLinearBilateralConstraintInfo info;
    info.m_constrainedDofW[0] = dof[0]; info.m_constrainedDofW[1] = dof[1];
    info.m_constrainedDofW[2] = dof[2]; info.m_constrainedDofW[3] = dof[3];
    for (int i = 0; i < 4; ++i) { info.m_pivotA[i] = p->m_vec[i]; info.m_pivotB[i] = p->m_vec[4 + i]; }
    hk1dLinearBilateralConstraintBuildJacobian(&info, in, out);
    p->m_numJacobians = p->m_numJacobians + 1;
}

// @ 0x01089870
// Angle of body B's axis frame about axis 'axis' relative to A: dot products of rows of a
// 3-row-per-body transform array (row index bases 5 and 8), then hkMath::atan2fApproximation.
// Private register convention in the binary: ECX = axis (0..2), EDX = array of hkVector4 rows.
namespace hkMath { float atan2fApproximation(float y, float x); }     // 0x0120adb0 (cdecl)
static const int s_mod3[5] = { 0, 1, 2, 0, 1 };                       // 0x015b9b80 (axis + 1, axis + 2 mod 3)
float hkGenericConstraint_calcAngle(int axis, const hkVector4* rows)
{
    int a = s_mod3[axis + 1];
    int b = s_mod3[axis + 2];
    const hkVector4& w = rows[a + 5];
    const hkVector4& v1 = rows[b + 8];
    const hkVector4& v2 = rows[a + 8];
    // X87-PRECISION: each dot product accumulates ((z*z' + y*y') + x*x') in extended precision and is
    // rounded to float only once, when stored to the stack slot before the call.
    float d1 = (float)((((hkX87Real)v1.z * w.z) + ((hkX87Real)v1.y * w.y)) + ((hkX87Real)v1.x * w.x));
    float d2 = (float)((((hkX87Real)v2.z * w.z) + ((hkX87Real)v2.y * w.y)) + ((hkX87Real)v2.x * w.x));
    return hkMath::atan2fApproximation(d1, d2);
}
