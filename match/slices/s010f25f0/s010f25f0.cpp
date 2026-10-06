// Havok 3.1.0 (statically linked, ~2005 MSVC x87 build): hkLs_localizedSolveToi (0x010F25F0).
//
// The "localized solver" TOI response: confirms the TOI contact point, applies the simple collision
// response, then grows a local constraint system around the two TOI bodies (StExpandSystem), builds
// accumulators/jacobians for it, solves it, solves the "forced" (TOI-priority) constraints until they
// are satisfied, and finally integrates the touched bodies and invalidates their TIMs. When the solver
// resources run out the hkToiResourceMgr decides between "stop expanding" and "backstep the island".
//
// Complete, behaviourally equivalent rewrite. Compile flags: /O2 /MD /Gy /TP /GS- (x87 module, no /EHsc,
// no cookie although the frame holds 0x828 bytes of in-place arrays). The original comes from an older
// compiler than cl 15.00 (see s010f3460), so this is not byte-exact; see nonmatching.txt.
// Layouts are the retail 32-bit ones recovered from this function and its callees.
#include "types.h"
#include <intrin.h>

typedef float hkReal;

// ---------------------------------------------------------------------------------------------
// monitor stream timers (HK_TIMER_SPLIT): inlined TLS monitor-stream appends
// ---------------------------------------------------------------------------------------------
extern unsigned long g_hkMonitorStreamEndTls;      // 0x016e42a8
extern unsigned long g_hkMonitorStreamCurTls;      // 0x016e42a4
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);

struct hkMonitorStreamRecord { const char* m_name; uint32_t m_time; uint32_t m_pad; };

static __forceinline void HK_TIMER_SPLIT(const char* name)
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    void* cur = TlsGetValue(g_hkMonitorStreamCurTls);
    if (cur < end) {
        hkMonitorStreamRecord* r = (hkMonitorStreamRecord*)TlsGetValue(g_hkMonitorStreamCurTls);
        r->m_name = name;
        r->m_time = (uint32_t)__rdtsc();
        TlsSetValue(g_hkMonitorStreamCurTls, r + 1);
    }
}

// ---------------------------------------------------------------------------------------------
// hkThreadMemory (stack allocator) and hkArray family
// ---------------------------------------------------------------------------------------------
extern unsigned long g_hkThreadMemoryTls;      // 0x016e4174

struct hkThreadMemory {
    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    virtual void* onStackOverflow(int numBytes);         // +0x0c
    virtual void onStackUnderflow(void* p);               // +0x10
    uint32_t pad04[7];        // +0x04 .. +0x1f
    char* m_stackCurrent;     // +0x20
    char* m_stackPrev;        // +0x24
    char* m_stackBase;        // +0x28
    char* m_stackEnd;         // +0x2c
    void deallocateChunk(void* p, int numBytes, int memoryClass);          // 0x0107DB10

    static __forceinline hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls); }
};
enum { HK_MEMORY_CLASS_ARRAY = 0x14 };

template <typename T> __forceinline T* hkAllocateStack(int n)
{
    hkThreadMemory& tm = hkThreadMemory::getInstance();
    int size = (n * (int)sizeof(T) + 0x10) & ~0xf;
    char* cur = tm.m_stackCurrent;
    char* next = cur + size;
    if ((uint32_t)next > (uint32_t)tm.m_stackEnd)
        return (T*)tm.onStackOverflow(size);
    tm.m_stackCurrent = next;
    return (T*)cur;
}
template <typename T> __forceinline void hkDeallocateStack(T* p)
{
    hkThreadMemory& tm = hkThreadMemory::getInstance();
    tm.m_stackCurrent = (char*)p;
    if ((char*)p == tm.m_stackBase)
        tm.onStackUnderflow(p);
}

struct hkArrayUtil {
    static void _reserveExactly(void* array, int newCapacity, int elemSize);   // 0x0107F4A0
};

template <typename T> struct hkArray {
    enum { CAPACITY_MASK = 0x3fffffff, DONT_DEALLOCATE_FLAG = 0x80000000 };
    T* m_data;
    int m_size;
    int m_capacityAndFlags;

    hkArray() : m_data(0), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}
    hkArray(T* buffer, int size, int capacity) : m_data(buffer), m_size(size), m_capacityAndFlags(capacity | DONT_DEALLOCATE_FLAG) {}
    __forceinline ~hkArray() { releaseMemory(); }
    __forceinline void releaseMemory()
    {
        if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
            hkThreadMemory::getInstance().deallocateChunk(m_data, getCapacity() * sizeof(T), HK_MEMORY_CLASS_ARRAY);
    }
    int getSize() const { return m_size; }
    int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
    T& operator[](int i) { return m_data[i]; }
    void clear() { m_size = 0; }
    __forceinline void pushBackUnchecked(const T& t) { m_data[m_size] = t; m_size++; }
    __forceinline void removeAt(int index) { m_data[index] = m_data[--m_size]; }
    __forceinline void reserve(int n)
    {
        if (getCapacity() < n) {
            int cap2 = 2 * getCapacity();
            int newSize = (n < cap2) ? cap2 : n;
            hkArrayUtil::_reserveExactly(this, newSize, sizeof(T));
        }
    }
    void insertAt(int index, const hkArray<T>& a);       // 0x010FBB80 (hkArray<T*> instance)
};

template <typename T, int N> struct hkInplaceArray : hkArray<T> {
    T m_storage[N];
    __forceinline hkInplaceArray() : hkArray<T>(m_storage, 0, N) {}
};

template <typename T> struct hkLocalArray : hkArray<T> {
    T* m_localMemory;
    __forceinline hkLocalArray(int capacity)
    {
        this->m_data = hkAllocateStack<T>(capacity);
        this->m_capacityAndFlags = capacity | hkArray<T>::DONT_DEALLOCATE_FLAG;
        m_localMemory = this->m_data;
    }
    __forceinline ~hkLocalArray() { hkDeallocateStack(m_localMemory); }
};

template <typename T> struct hkFixedArray { T* m_data; T& operator[](int i) { return m_data[i]; } };

struct hkBool {
    char m_bool;
    operator bool() const { return m_bool != 0; }
};

// ---------------------------------------------------------------------------------------------
// dynamics types (only the members used here)
// ---------------------------------------------------------------------------------------------
struct hkStepInfo;
struct hkSolverInfo;
struct hkVelocityAccumulator;
struct hkConstraintInstance;
struct hkSimulationIsland;
struct hkTransform;
struct hkSweptTransform;
struct hkCollidable;

struct hkMotionState {
    char m_transform[0x40];                          // +0x00 hkTransform
    char m_sweptTransform[0x50];                     // +0x40 hkSweptTransform
};

struct hkMotion {
    virtual void vslot0();
    virtual void vslot1();
    virtual int getType();                           // +0x08
    int pad04[3];
    hkMotionState m_motionState;                     // +0x10
};
enum { HK_MOTION_FIXED = 6 };

struct hkEntity {
    char pad00[0x1c];
    char m_collidable[0x30];                         // +0x1c hkLinkedCollidable
    char pad4c[0x58 - 0x4c];
    hkMotion* m_motion;                              // +0x58
    hkSimulationIsland* m_simulationIsland;          // +0x5c
    char pad60[0x94 - 0x60];
    uint16_t m_storageIndex;                         // +0x94
    char pad96[0x99 - 0x96];
    bool m_fixed;                                    // +0x99
    char pad9a[0xa0 - 0x9a];
    void* m_contactPointConfirmedListeners;          // +0xa0 (array data; non-null = has listeners)
    const hkCollidable* getCollidable() const { return (const hkCollidable*)m_collidable; }
};

struct hkSimulationIsland {
    char pad00[0x3c];
    hkArray<hkEntity*> m_entities;                   // +0x3c
};

struct hkProcessCollisionInput;

struct hkWorld {
    char pad00[0x78];
    hkProcessCollisionInput* m_collisionInput;       // +0x78
    char pad7c[0xc0 - 0x7c];
    hkReal m_toiCollisionResponseRotateNormal;       // +0xc0
};

struct hkContactPoint;
struct hkContactPointMaterial { void* m_userData; uint16_t m_friction; uint8_t m_restitution; uint8_t m_flags; };

struct hkToiEvent {                                  // 0x40
    hkReal m_time;                                   // +0x00
    hkEntity* m_entities[2];                         // +0x04
    hkReal m_seperatingVelocity;                     // +0x0c
    hkContactPointMaterial m_material;               // +0x10
    void* m_contactMgr;                              // +0x18
    uint32_t pad1c;
    char m_contactPoint[0x20];                       // +0x20 hkContactPoint
};

struct hkToiResources {                              // 0x20
    int m_priority;                                  // +0x00 hkConstraintInstance::ConstraintPriority used for the expansion
    int m_maxNumActiveEntities;                      // +0x04
    int m_maxNumEntities;                            // +0x08
    int m_maxNumConstraints;                         // +0x0c
    int m_numToiSolverIterations;                    // +0x10
    int m_numForcedToiFinalSolverIterations;         // +0x14
    char* m_scratchpad;                              // +0x18
    int m_scratchpadSize;                            // +0x1c
};

struct hkConstraintSchemaInfo {                      // 12 bytes
    hkConstraintInstance* m_constraint;
    void* m_schema;
    hkReal m_allowedPenetrationDepth;
};

struct hkSchemaStream { void* m_begin; void* m_f04; void* m_current; void* m_f0c; };

struct hkConstraintSolverResources {
    hkStepInfo* m_stepInfo;                          // +0x00
    hkSolverInfo* m_solverInfo;                      // +0x04
    void* m_constraintQueryIn;                       // +0x08
    hkVelocityAccumulator* m_accumulators;           // +0x0c
    void* m_accumulatorsCurrent;                     // +0x10
    void* m_elemTemp;                                // +0x14
    void* m_elemTempCurrent;                         // +0x18
    void* m_solverResults;                           // +0x1c
    void* m_f20;                                     // +0x20
    hkSchemaStream m_schemas[2];                     // +0x24 (normal priority), +0x34 (TOI priority)
};

struct hkContactPointConfirmedEvent {                // 0x24
    const hkCollidable* m_collidableA;               // +0x00
    const hkCollidable* m_collidableB;               // +0x04
    hkEntity* m_callbackFiredFrom;                   // +0x08 (set by the fire functions)
    hkContactPoint* m_contactPoint;                  // +0x0c
    hkContactPointMaterial* m_contactPointMaterial;  // +0x10
    hkReal m_rotateNormal;                           // +0x14
    hkReal m_projectedVelocity;                      // +0x18
    int m_type;                                      // +0x1c (0 = TYPE_TOI)
    void* m_contactData;                             // +0x20
    hkContactPointConfirmedEvent(int type, const hkCollidable* a, const hkCollidable* b, void* data,
                                 hkContactPoint* cp, hkContactPointMaterial* cpm, hkReal rotateNormal, hkReal projectedVelocity)
        : m_collidableA(a), m_collidableB(b), m_contactPoint(cp), m_contactPointMaterial(cpm),
          m_rotateNormal(rotateNormal), m_projectedVelocity(projectedVelocity), m_type(type), m_contactData(data) {}
};

struct hkConstraintViolationInfo { hkConstraintInstance* m_constraint; void* m_contactPoint; void* m_contactPointProperties; };

enum hkToiResourceMgrResponse {
    HK_TOI_RESOURCE_MGR_RESPONSE_CONTINUE = 0,
    HK_TOI_RESOURCE_MGR_RESPONSE_DO_NOT_EXPAND_AND_CONTINUE = 1,
    HK_TOI_RESOURCE_MGR_RESPONSE_BACKSTEP = 2
};

struct hkToiResourceMgr {
    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    virtual void vslot3();                           // +0x0c beginToiAndSetupResources
    virtual hkToiResourceMgrResponse cannotSolve(hkArray<hkConstraintViolationInfo>& violatedConstraints);   // +0x10
    virtual hkToiResourceMgrResponse resourcesDepleted();                                                   // +0x14
};

// flags[entity->m_storageIndex] states
enum {
    HK_ENTITY_STATE_NOT_ACTIVE = 0,
    HK_ENTITY_STATE_TRANSFORM_UPDATED = 1,
    HK_ENTITY_STATE_ACTIVE = 2,
    HK_ENTITY_STATE_FROZEN = 8
};

// ---------------------------------------------------------------------------------------------
// callees
// ---------------------------------------------------------------------------------------------
struct hkWorldCallbackUtil {
    static void fireContactPointConfirmed(hkWorld* world, hkContactPointConfirmedEvent& event);              // 0x0109F0D0
};
struct hkEntityCallbackUtil {
    static void fireContactPointConfirmedInternal(hkEntity* entity, hkContactPointConfirmedEvent& event);    // 0x0109E850
};
struct hkSweptTransformUtil {
    static void lerp2(const hkSweptTransform& sweptTrans, hkReal t, hkTransform& transformOut);             // 0x01209C50
    static void backStepMotionState(hkReal time, hkMotionState& motionState);                               // 0x0120A260
};
struct hkConstraintSolverSetup {
    static void internalAddAccumulators(hkConstraintSolverResources& r, hkEntity** entities, int n);        // 0x010A4D10
    static hkBool internalIsMemoryOkForNewAccumulators(hkConstraintSolverResources& r, hkEntity** entities, int n);   // 0x010A4DE0
    static void internalAddJacobianElements(hkConstraintSolverResources& r, hkConstraintInstance** constraints, int n,
                                            hkArray<hkConstraintSchemaInfo>& schemas);                     // 0x010A4E40
    static hkBool internalIsMemoryOkForNewJacobianElements(hkConstraintSolverResources& r, hkConstraintInstance** c, int n);   // 0x010A4FB0
    static void oneStepIntegrate(const hkStepInfo& info, hkEntity** entities, int n, hkVelocityAccumulator* acc);   // 0x010A4CA0
    static void resetSolverBuffers(hkConstraintSolverResources& r, int flag);                               // 0x010A49E0
};
void hkSolver_solveJacobianSchemas(hkSolverInfo* info, void* schemas, hkVelocityAccumulator* accumulators,
                                   void* elemTemp, void* results);                                         // 0x010B48B0
void hkConstraintSolverResources_noop();                                                                   // 0x00C2E4E0 (empty)

void hkLs_doSimpleCollisionResponse(hkWorld* world, const hkToiEvent& event, hkReal rotateNormal,
                                    hkArray<hkEntity*>& toBeActivated);                                    // 0x010F03D0
void hkLs_toiCheckValidityOfConstraints(hkConstraintSolverResources& r, hkProcessCollisionInput& input,
                                        hkArray<hkConstraintSchemaInfo>& schemas, int& firstNonActiveSchema,
                                        int priority, hkFixedArray<unsigned char>& flags,
                                        const hkArray<hkEntity*>& activeEntities, hkArray<hkEntity*>& toBeActivated);   // 0x010F0F90
void hkLs_toiActivateEntitiesAndCheckConstraints(hkProcessCollisionInput& input, int priority, hkReal time,
                                                 const hkArray<hkEntity*>& toBeActivated, hkFixedArray<unsigned char>& flags,
                                                 hkArray<hkEntity*>& newEntities, hkArray<hkConstraintInstance*>& newConstraints);   // 0x010F1350
void hkLs_backstepAndFreezeEntireIsland(hkReal time, hkSimulationIsland* island, hkFixedArray<unsigned char>& flags,
                                        hkArray<hkEntity*>& entitiesOut);                                  // 0x010F17F0
void hkLs_restoreTransformOnBodiesWithUpdatedTransform(hkSimulationIsland* island, hkFixedArray<unsigned char>& flags);   // 0x010F18D0
void hkLs_sortSchemasOfFixedEntitiesFirst(hkArray<hkConstraintSchemaInfo>& schemas, int& firstNonActiveSchema, int numNew);   // 0x010F0610
void hkLs_sortSchemasOfFrozenEntitiesFirst(hkArray<hkConstraintSchemaInfo>& schemas, int& firstNonActiveSchema,
                                           hkFixedArray<unsigned char>& flags);                            // 0x010F06D0
void hkLs_copyVelocitiesToAccumulators(hkConstraintSolverResources& r, hkArray<hkEntity*>& entities);      // 0x010F0790
hkBool hkLs_areConstraintsSatisfied(hkConstraintSolverResources& r, hkArray<hkConstraintSchemaInfo>& schemas,
                                    hkProcessCollisionInput* input, hkArray<hkConstraintViolationInfo>* violatedOut);   // 0x010F1690
void hkLs_invalidateTimsOfEntity(hkEntity* entity, hkProcessCollisionInput* input);                        // 0x010A3890

static __forceinline void hkLs_invalidateTims(hkArray<hkEntity*>& entities, hkWorld* world)
{
    for (int i = 0; i < entities.getSize(); i++)
        hkLs_invalidateTimsOfEntity(entities[i], world->m_collisionInput);
}

// ---------------------------------------------------------------------------------------------
// @ 0x010F25F0
// ---------------------------------------------------------------------------------------------
void hkLs_localizedSolveToi(const hkToiResources& toiResources, hkConstraintSolverResources& solverResources,
                            hkToiEvent& event, hkToiResourceMgr& toiResourceMgr, hkWorld* world,
                            hkArray<hkEntity*>& entitiesOut, hkFixedArray<unsigned char>& entityState)
{
    // confirm the TOI contact point
    {
        hkContactPointConfirmedEvent cpEvent(0, event.m_entities[0]->getCollidable(), event.m_entities[1]->getCollidable(), 0,
                                             (hkContactPoint*)event.m_contactPoint, &event.m_material,
                                             world->m_toiCollisionResponseRotateNormal, event.m_seperatingVelocity);
        hkWorldCallbackUtil::fireContactPointConfirmed(world, cpEvent);
        if (event.m_entities[0]->m_contactPointConfirmedListeners)
            hkEntityCallbackUtil::fireContactPointConfirmedInternal(event.m_entities[0], cpEvent);
        if (event.m_entities[1]->m_contactPointConfirmedListeners)
            hkEntityCallbackUtil::fireContactPointConfirmedInternal(event.m_entities[1], cpEvent);
    }

    hkEntity* entityA = event.m_entities[0];
    hkEntity* entityB = event.m_entities[1];
    hkSimulationIsland* island = !entityA->m_fixed ? entityA->m_simulationIsland : entityB->m_simulationIsland;

    hkLocalArray<hkEntity*> activeEntities(island->m_entities.getSize());
    hkInplaceArray<hkConstraintSchemaInfo, 64> schemas;
    int firstNonActiveSchema = 0;

    HK_TIMER_SPLIT("St2BodyCollide");

    if (!entityA->m_fixed) {
        activeEntities.pushBackUnchecked(entityA);
        hkReal t = event.m_time;
        unsigned char& state = entityState[entityA->m_storageIndex];
        if (state == HK_ENTITY_STATE_NOT_ACTIVE) {
            state = HK_ENTITY_STATE_TRANSFORM_UPDATED;
            hkMotionState& ms = entityA->m_motion->m_motionState;
            hkSweptTransformUtil::lerp2(*(hkSweptTransform*)ms.m_sweptTransform, t, *(hkTransform*)ms.m_transform);
        }
        entityState[entityA->m_storageIndex] = HK_ENTITY_STATE_ACTIVE;
    }
    if (!entityB->m_fixed) {
        activeEntities.pushBackUnchecked(entityB);
        hkReal t = event.m_time;
        unsigned char& state = entityState[entityB->m_storageIndex];
        if (state == HK_ENTITY_STATE_NOT_ACTIVE) {
            state = HK_ENTITY_STATE_TRANSFORM_UPDATED;
            hkMotionState& ms = entityB->m_motion->m_motionState;
            hkSweptTransformUtil::lerp2(*(hkSweptTransform*)ms.m_sweptTransform, t, *(hkTransform*)ms.m_transform);
        }
        entityState[entityB->m_storageIndex] = HK_ENTITY_STATE_ACTIVE;
    }

    hkInplaceArray<hkEntity*, 64> toBeActivated;
    hkLs_doSimpleCollisionResponse(world, event, world->m_toiCollisionResponseRotateNormal, toBeActivated);
    hkEntity* touchedA = toBeActivated[0];
    hkEntity* touchedB = (toBeActivated.getSize() > 1) ? toBeActivated[1] : 0;

    hkConstraintSolverResources_noop();
    hkConstraintSolverSetup::internalAddAccumulators(solverResources, activeEntities.m_data, activeEntities.getSize());

    {
        hkInplaceArray<hkEntity*, 64> newEntities;
        hkInplaceArray<hkConstraintInstance*, 64> newConstraints;
        bool firstIteration = true;
        bool expand = true;

        for (int iterations = toiResources.m_numToiSolverIterations; iterations > 0; iterations--) {
            if (expand) {
                for (;;) {
                    HK_TIMER_SPLIT("StExpandSystem");
                    newConstraints.clear();
                    newEntities.clear();
                    int newFirstNonActiveSchema = firstNonActiveSchema;
                    if (!firstIteration) {
                        if (firstNonActiveSchema >= schemas.getSize()) {
                            expand = false;
                            break;
                        }
                        toBeActivated.clear();
                        hkLs_toiCheckValidityOfConstraints(solverResources, *world->m_collisionInput, schemas, newFirstNonActiveSchema,
                                                           toiResources.m_priority, entityState, activeEntities, toBeActivated);
                        if (toBeActivated.getSize() == 0)
                            break;
                    }

                    hkLs_toiActivateEntitiesAndCheckConstraints(*world->m_collisionInput, toiResources.m_priority, event.m_time,
                                                                toBeActivated, entityState, newEntities, newConstraints);

                    HK_TIMER_SPLIT("StbuildAcc+Jac");
                    if (!hkConstraintSolverSetup::internalIsMemoryOkForNewAccumulators(solverResources, newEntities.m_data, newEntities.getSize()) ||
                        !hkConstraintSolverSetup::internalIsMemoryOkForNewJacobianElements(solverResources, newConstraints.m_data, newConstraints.getSize()) ||
                        toiResources.m_maxNumConstraints < newConstraints.getSize() + schemas.getSize() ||
                        toiResources.m_maxNumActiveEntities < entitiesOut.getSize() + newEntities.getSize() + activeEntities.getSize() ||
                        toiResources.m_maxNumEntities < entitiesOut.getSize() + toBeActivated.getSize()) {
                        // undo the activation of this expansion step
                        for (int i = 0; i < toBeActivated.getSize(); i++)
                            entityState[toBeActivated[i]->m_storageIndex] = HK_ENTITY_STATE_ACTIVE;
                        for (int j = 0; j < newEntities.getSize(); j++)
                            entityState[newEntities[j]->m_storageIndex] = HK_ENTITY_STATE_TRANSFORM_UPDATED;

                        hkToiResourceMgrResponse response = toiResourceMgr.resourcesDepleted();
                        if (response == HK_TOI_RESOURCE_MGR_RESPONSE_DO_NOT_EXPAND_AND_CONTINUE) {
                            expand = false;
                        } else if (response == HK_TOI_RESOURCE_MGR_RESPONSE_BACKSTEP) {
                            HK_TIMER_SPLIT("StBackstep");
                            hkLs_backstepAndFreezeEntireIsland(event.m_time, island, entityState, entitiesOut);
                            HK_TIMER_SPLIT("StInvalidTIMs");
                            hkLs_invalidateTims(entitiesOut, world);
                            entitiesOut.clear();
                            return;
                        }
                        break;
                    }

                    hkConstraintSolverSetup::internalAddAccumulators(solverResources, newEntities.m_data, newEntities.getSize());
                    hkConstraintSolverSetup::internalAddJacobianElements(solverResources, newConstraints.m_data, newConstraints.getSize(), schemas);
                    firstNonActiveSchema = newFirstNonActiveSchema;

                    // drop the frozen entities from the active set
                    for (int i = 0; i < activeEntities.getSize(); i++) {
                        if (entityState[activeEntities[i]->m_storageIndex] == HK_ENTITY_STATE_FROZEN) {
                            activeEntities.removeAt(i);
                            i--;
                        }
                    }
                    entitiesOut.insertAt(entitiesOut.getSize(), toBeActivated);

                    activeEntities.reserve(activeEntities.getSize() + newEntities.getSize());
                    for (int k = 0; k < newEntities.getSize(); k++) {
                        if (newEntities[k]->m_motion->getType() != HK_MOTION_FIXED)
                            activeEntities.pushBackUnchecked(newEntities[k]);
                    }

                    hkLs_sortSchemasOfFixedEntitiesFirst(schemas, firstNonActiveSchema, newConstraints.getSize());
                    hkLs_sortSchemasOfFrozenEntitiesFirst(schemas, firstNonActiveSchema, entityState);
                    hkConstraintSolverSetup::resetSolverBuffers(solverResources, 1);

                    if (newConstraints.getSize() == 0 && newEntities.getSize() == 0)
                        break;
                    firstIteration = false;
                }
            }
            firstIteration = false;

            HK_TIMER_SPLIT("StSolver");
            if (solverResources.m_schemas[0].m_begin != solverResources.m_schemas[0].m_current)
                hkSolver_solveJacobianSchemas(solverResources.m_solverInfo, solverResources.m_schemas[0].m_begin,
                                              solverResources.m_accumulators, solverResources.m_elemTemp, solverResources.m_solverResults);
            if (solverResources.m_schemas[1].m_begin != solverResources.m_schemas[1].m_current)
                hkSolver_solveJacobianSchemas(solverResources.m_solverInfo, solverResources.m_schemas[1].m_begin,
                                              solverResources.m_accumulators, solverResources.m_elemTemp, solverResources.m_solverResults);
        }

        // solve the forced (TOI priority) constraints until they are satisfied
        HK_TIMER_SPLIT("StForcedConstr");
        if (solverResources.m_schemas[1].m_begin != solverResources.m_schemas[1].m_current) {
            hkLs_copyVelocitiesToAccumulators(solverResources, activeEntities);
            hkBool ok = hkLs_areConstraintsSatisfied(solverResources, schemas, world->m_collisionInput, 0);
            if (!ok) {
                int n = toiResources.m_numForcedToiFinalSolverIterations;
                while (n-- != 0) {
                    hkSolver_solveJacobianSchemas(solverResources.m_solverInfo, solverResources.m_schemas[1].m_begin,
                                                  solverResources.m_accumulators, solverResources.m_elemTemp, solverResources.m_solverResults);
                    hkLs_copyVelocitiesToAccumulators(solverResources, activeEntities);
                    ok = hkLs_areConstraintsSatisfied(solverResources, schemas, world->m_collisionInput, 0);
                    if (ok)
                        break;
                }
                if (!ok) {
                    hkInplaceArray<hkConstraintViolationInfo, 32> violatedConstraints;
                    hkLs_areConstraintsSatisfied(solverResources, schemas, world->m_collisionInput, &violatedConstraints);
                    if (toiResourceMgr.cannotSolve(violatedConstraints) == HK_TOI_RESOURCE_MGR_RESPONSE_BACKSTEP) {
                        HK_TIMER_SPLIT("StBackstep");
                        hkLs_backstepAndFreezeEntireIsland(event.m_time, island, entityState, entitiesOut);
                        HK_TIMER_SPLIT("StInvalidTIMs");
                        hkLs_invalidateTims(entitiesOut, world);
                        entitiesOut.clear();
                        return;
                    }
                }
            }
        }

        // nothing else was touched: at least move the two bodies hit by the simple collision response
        if (entitiesOut.getSize() == 0) {
            entitiesOut.insertAt(0, hkArray<hkEntity*>(&touchedA, 1, 1));
            entityState[entitiesOut[0]->m_storageIndex] = HK_ENTITY_STATE_FROZEN;
            if (touchedB) {
                entitiesOut.insertAt(1, hkArray<hkEntity*>(&touchedB, 1, 1));
                entityState[entitiesOut[1]->m_storageIndex] = HK_ENTITY_STATE_FROZEN;
            }
        }

        HK_TIMER_SPLIT("StIntegMotions");
        for (int i = 0; i < entitiesOut.getSize(); i++)
            hkSweptTransformUtil::backStepMotionState(event.m_time, entitiesOut[i]->m_motion->m_motionState);
        hkConstraintSolverSetup::oneStepIntegrate(*solverResources.m_stepInfo, entitiesOut.m_data, entitiesOut.getSize(),
                                                  solverResources.m_accumulators);
        hkLs_restoreTransformOnBodiesWithUpdatedTransform(island, entityState);

        HK_TIMER_SPLIT("StInvalidTIMs");
        hkLs_invalidateTims(entitiesOut, world);
    }
}
