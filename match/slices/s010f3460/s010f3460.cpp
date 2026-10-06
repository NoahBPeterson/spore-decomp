// Havok 3.1.0 (statically linked, ~2005 MSVC x87 build): hkContinuousSimulation
//   reintegrateAndRecollideEntities (0x010F3460), collide (0x010F3600), simulateToi (0x010F3A40).
//
// Complete, behaviourally equivalent rewrite (every path, call and side effect of the originals).
// Compile flags: /O2 /MD /Gy /TP /GS- (x87, no /EHsc; /GS- because simulateToi has stack arrays but no cookie). Layouts are the retail 32-bit ones (dev PDB where
// it has the type; hkToiEvent / hkToiResources / hkConstraintQueryIn are recovered from the asm).
// The original x87 code comes from an older compiler (float constants loaded from the constant pool),
// so these are not byte-exact; see nonmatching.txt.
#include "types.h"
#include <intrin.h>
#include <stddef.h>

#ifndef _WIN64
#define HK_OFFSET_CHECK(name, cond) typedef char name[(cond) ? 1 : -1]
#else
#define HK_OFFSET_CHECK(name, cond)
#endif

typedef float hkReal;
#define HK_REAL_MAX 3.40282e+38f      // 0x7f7fffee in this build (not FLT_MAX)

template <typename T> struct hkArray { T* m_data; int32_t m_size; int32_t m_capacityAndFlags; };

// ---------------------------------------------------------------------------------------------
// monitor stream timers (HK_TIMER_BEGIN / SPLIT / END): inlined TLS monitor-stream appends
// ---------------------------------------------------------------------------------------------
extern unsigned long g_hkMonitorStreamEndTls;      // 0x016e42a8
extern unsigned long g_hkMonitorStreamCurTls;      // 0x016e42a4
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);

struct hkMonitorStreamRecord { const char* m_name; uint32_t m_time; uint32_t m_pad; };
struct hkMonitorStreamListRecord { const char* m_name; uint32_t m_time; uint32_t m_pad; const char* m_nameOfFirstSplit; };

// 12-byte record: timer begin / split ("Tt..", "St..") and end ("Et", "lt")
static inline void hkMonitorStamp(const char* name)
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
// 16-byte record: HK_TIMER_BEGIN_LIST(list, firstSplit)
static inline void hkMonitorStampList(const char* listName, const char* firstSplit)
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    void* cur = TlsGetValue(g_hkMonitorStreamCurTls);
    if (cur < end) {
        hkMonitorStreamListRecord* r = (hkMonitorStreamListRecord*)TlsGetValue(g_hkMonitorStreamCurTls);
        r->m_name = listName;
        r->m_nameOfFirstSplit = firstSplit;
        r->m_time = (uint32_t)__rdtsc();
        TlsSetValue(g_hkMonitorStreamCurTls, r + 1);
    }
}

// ---------------------------------------------------------------------------------------------
// hkMemory / hkThreadMemory (stack allocator used by hkAllocateStack / hkDeallocateStack)
// ---------------------------------------------------------------------------------------------
struct hkMemory {
    void** vftable;                    // +0x00
    int m_memoryState;                 // +0x04 (1 = MEMORY_STATE_OUT_OF_MEMORY)
    int m_criticalMemoryLimit;         // +0x08
    int m_referenceCount;              // +0x0c
    int m_sysAllocs0;                  // +0x10
    int m_sysAllocsSize;               // +0x14
    int m_stats8, m_stats0c, m_stats10, m_stats14;   // +0x18..+0x27
    int m_pageMemoryUsed;              // +0x28
};
extern hkMemory* g_hkMemoryInstance;           // 0x016e4178 (hkMemory::s_instance)
extern unsigned long g_hkThreadMemoryTls;      // 0x016e4174

// Only the fields the stack allocator touches are modelled.
struct hkThreadMemoryRaw {
    void** vftable;           // +0x00
    char pad[0x1c];           // +0x04 .. +0x1f
    char* m_stackCurrent;     // +0x20
    char* m_stackPrev;        // +0x24
    char* m_stackBase;        // +0x28
    char* m_stackEnd;         // +0x2c
    void deallocateChunk(void* p, int numBytes, int memoryClass);          // 0x0107DB10
};

static inline hkThreadMemoryRaw* hkThreadMemoryGet() { return (hkThreadMemoryRaw*)TlsGetValue(g_hkThreadMemoryTls); }

// hkAllocateStack<char>(n): bump allocation, 16-byte rounded, falls back to onStackOverflow
static inline char* hkAllocateStackChars(int n)
{
    hkThreadMemoryRaw* tm = hkThreadMemoryGet();
    int size = (n + 0x10) & ~0xf;
    char* cur = tm->m_stackCurrent;
    char* next = cur + size;
    if ((uint32_t)next > (uint32_t)tm->m_stackEnd)
        return (char*)((void* (__thiscall*)(hkThreadMemoryRaw*, int))((void**)tm->vftable)[3])(tm, size);
    tm->m_stackCurrent = next;
    return cur;
}
static inline void hkDeallocateStackChars(char* p)
{
    hkThreadMemoryRaw* tm = hkThreadMemoryGet();
    tm->m_stackCurrent = p;
    if (p == tm->m_stackBase)
        ((void(__thiscall*)(hkThreadMemoryRaw*, char*))((void**)tm->vftable)[4])(tm, p);
}
// hkArray<T> destructor for arrays that may live on the heap (flag 0x80000000 = DONT_DEALLOCATE)
static inline void hkArrayDeallocate(void* data, int capacityAndFlags, int elemSize)
{
    if (capacityAndFlags >= 0)
        hkThreadMemoryGet()->deallocateChunk(data, (capacityAndFlags & 0x3fffffff) * elemSize, 0x14);
}

void hkString_memSet(void* dst, int value, int n);                       // 0x0107F470 (cdecl)

// ---------------------------------------------------------------------------------------------
// math / solver types
// ---------------------------------------------------------------------------------------------
extern const float hkRealZero;     // 0x01485378 (0.0f): pooled constant the original loads from memory
extern const float hkRealOne;      // 0x01485720 (1.0f)

__declspec(align(16)) struct hkVector4 { float x, y, z, w; };

struct hkStepInfo {
    float m_startTime;      // +0x0
    float m_endTime;        // +0x4
    float m_deltaTime;      // +0x8
    float m_invDeltaTime;   // +0xc
    hkStepInfo() {}
    hkStepInfo(float startTime, float endTime);                          // 0x01099430 (out of line)
};

struct hkSolverInfo {                    // 0x140 bytes
    float m_one;                         // +0x00
    float m_tau;                         // +0x04
    float m_damping;                     // +0x08
    float m_frictionTau;                 // +0x0c
    hkVector4 m_globalAccelerationPerSubStep;   // +0x10
    hkVector4 m_globalAccelerationPerStep;      // +0x20
    char pad30[0x54 - 0x30];
    float m_tauDivDamp;                  // +0x54
    float m_dampDivFrictionTau;          // +0x58
    float m_frictionTauDivDamp;          // +0x5c
    char pad60[0x124 - 0x60];
    float m_deltaTime;                   // +0x124
    float m_invDeltaTime;                // +0x128
    int m_numSteps;                      // +0x12c
    float m_invNumSteps;                 // +0x130
    char pad134[0x140 - 0x134];
    hkSolverInfo& operator=(const hkSolverInfo& other);                  // 0x010F0260 (out of line)
    void setTauAndDamping(float tau, float damping);                     // 0x01082890
};
HK_OFFSET_CHECK(hkSolverInfo_size, sizeof(hkSolverInfo) == 0x140);

struct hkConstraintSolverResources { char m_data[0x30]; };               // layout owned by hkConstraintSolverSetup
void hkConstraintSolverResources_destruct(hkConstraintSolverResources*); // 0x00C2E4E0 (empty body, `ret`)

struct hkConstraintQueryIn {
    float m_substepDeltaTime;            // +0x00
    float m_substepInvDeltaTime;         // +0x04
    float m_frameDeltaTime;              // +0x08
    float m_frameInvDeltaTime;           // +0x0c
    float m_virtualMassFactor;           // +0x10 (solverInfo.m_invNumSteps)
    float m_rhsFactor;                   // +0x14 (tauDivDamp * invDeltaTime)
    float m_dampingFactor;               // +0x18 (damping)
    float m_frictionRhsFactor;           // +0x1c (frictionTauDivDamp * invDeltaTime)
    void* m_resultsBegin;                // +0x20 (copied from the solver resources)
    int m_resultsSize;                   // +0x24
    char pad28[0x38 - 0x28];
    float m_tau;                         // +0x38
    float m_damping;                     // +0x3c
    char pad40[0x48 - 0x40];
};

struct hkConstraintSolverSetup {
    static void initializeSolverState(hkStepInfo& stepInfo, hkSolverInfo& solverInfo, hkConstraintQueryIn& queryIn,
                                      char* buffer, int bufferSize, hkConstraintSolverResources& resources);   // 0x010A48F0
};

// ---------------------------------------------------------------------------------------------
// collision / world types
// ---------------------------------------------------------------------------------------------
struct hkContactPoint { hkVector4 m_position; hkVector4 m_separatingNormal; };      // 0x20
struct hkContactPointMaterial { void* m_userData; uint16_t m_friction; uint8_t m_restitution; uint8_t m_flags; };   // 8
struct hkProcessCdPoint { hkContactPoint m_contact; uint16_t m_contactPointId; char pad[14]; };                   // 0x30

struct hkProcessCollisionOutput {                    // hkProcessCollisionData + m_potentialContacts, 0x3050
    hkProcessCdPoint* m_firstFreeContactPoint;       // +0x0000
    hkContactPoint m_toiContactPoint;                // +0x0010
    hkProcessCdPoint m_contactPoints[256];           // +0x0030
    float m_toiSeperatingVelocity;                   // +0x3030
    float m_toi;                                     // +0x3034
    hkContactPointMaterial m_toiMaterial;            // +0x3038
    void* m_potentialContacts;                       // +0x3040
    hkProcessCollisionOutput() {}
};
HK_OFFSET_CHECK(hkProcessCollisionOutput_size, sizeof(hkProcessCollisionOutput) == 0x3050);

struct hkCollisionQualityInfo {                      // 0x3c
    char pad00[0x10];
    bool m_useContinuousPhysics;                     // +0x10
    char pad11[0x3c - 0x11];
};
struct hkCollisionDispatcher {
    char pad[0x1a14];
    hkCollisionQualityInfo m_collisionQualityInfo[8];   // +0x1a14
};
struct hkProcessCollisionInput {
    hkCollisionDispatcher* m_dispatcher;             // +0x00
    void* m_filter;                                  // +0x04
    float m_tolerance;                               // +0x08
    bool m_createPredictiveAgents;                   // +0x0c
    hkStepInfo m_stepInfo;                           // +0x10
    void* m_config;                                  // +0x20
    void* m_dynamicsInfo;                            // +0x24
    hkCollisionQualityInfo* m_collisionQualityInfo;  // +0x28
};

struct hkEntity;
struct hkSimulationIsland;
struct hkWorld;
struct hkContactMgr;
struct hkLinkedCollidable;

struct hkCollisionEntry { struct hkAgentNnEntry* m_agentEntry; hkLinkedCollidable* m_partner; };

struct hkLinkedCollidable {                          // hkCollidable (0x24) + entries
    char pad00[0x10];
    int m_ownerOffset;                               // +0x10
    char pad14[0x24 - 0x14];
    hkArray<hkCollisionEntry> m_collisionEntries;    // +0x24
    hkEntity* getOwner() { return (hkEntity*)((char*)this + m_ownerOffset); }
};

struct hkAgentNnEntry {
    uint8_t m_streamCommand, m_agentType, m_numContactPoints, m_size;   // +0x00
    uint32_t m_userData;                             // +0x04
    int8_t m_collisionQualityIndex;                  // +0x08
    char pad09[3];
    uint16_t m_agentIndexOnCollidable[2];            // +0x0c
    hkContactMgr* m_contactMgr;                      // +0x10
    hkLinkedCollidable* m_collidable[2];             // +0x14
};

struct hkContactMgr {
    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    virtual void vslot3();
    virtual void vslot4();
    virtual void processContact(hkLinkedCollidable& a, hkLinkedCollidable& b, hkProcessCollisionInput& input,
                                hkProcessCollisionOutput& output);     // +0x14
};

struct hkMotionState;
struct hkMotion {
    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    virtual void step(const hkStepInfo& stepInfo);                      // +0x0c (hkRigidMotion::step, 0x01088570)
};

struct hkEntity {
    char pad00[0x08];
    hkWorld* m_world;                                // +0x08
    char pad0c[0x1c - 0x0c];
    hkLinkedCollidable m_collidable;                 // +0x1c
    char pad4c[0x58 - 0x4c];
    hkMotion* m_motion;                              // +0x58
    hkSimulationIsland* m_simulationIsland;          // +0x5c
    char pad60[0x94 - 0x60];
    uint16_t m_storageIndex;                         // +0x94
    char pad96[0x99 - 0x96];
    bool m_fixed;                                    // +0x99
    char pad9a[0x9c - 0x9a];
    hkArray<void*> m_collisionListeners;             // +0x9c
};
HK_OFFSET_CHECK(hkEntity_collidable, sizeof(hkLinkedCollidable) == 0x30);

struct hkSimulationIsland {
    char pad00[0x3c];
    hkArray<hkEntity*> m_entities;                   // +0x3c (hkInplaceArray<hkEntity*,1>)
};

struct hkContactPointRemovedEvent {                  // 0x18
    uint16_t m_contactPointId;                       // +0x00
    hkContactPointMaterial* m_contactPointMaterial;  // +0x04
    hkEntity* m_entityA;                             // +0x08
    hkEntity* m_entityB;                             // +0x0c
    hkEntity* m_callbackFiredFrom;                   // +0x10
    hkContactMgr* m_internalContactMgr;              // +0x14
};

struct hkToiEvent {                                  // 0x40
    float m_time;                                    // +0x00
    hkEntity* m_entities[2];                         // +0x04
    float m_seperatingVelocity;                      // +0x0c
    hkContactPointMaterial m_material;               // +0x10
    hkContactMgr* m_contactMgr;                      // +0x18
    hkContactPoint m_contactPoint;                   // +0x20 (16-aligned: 4 bytes of padding at +0x1c)
};
HK_OFFSET_CHECK(hkToiEvent_size, sizeof(hkToiEvent) == 0x40);

struct hkToiResources {                              // 0x20
    int m_f00, m_f04, m_f08, m_f0c, m_f10, m_f14;
    char* m_solverBuffer;                            // +0x18
    int m_solverBufferSize;                          // +0x1c
    hkToiResources() : m_f00(2), m_f04(1000), m_f08(1000), m_f0c(1000), m_f10(4), m_f14(4), m_solverBuffer(0), m_solverBufferSize(0) {}
};

struct hkToiResourceMgr {
    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    // returns 1 when the TOI is rejected
    virtual int beginToiAndSetupResources(hkToiEvent& event, hkArray<hkToiEvent>& toiEvents, hkToiResources& resources);   // +0x0c
    virtual void vslot4();
    virtual void vslot5();
    virtual void cleanupResources(hkToiEvent& event, hkArray<hkToiEvent>& toiEvents, hkToiResources& resources);           // +0x18
};

template <typename T> struct hkFixedArray { T* m_data; };

typedef hkArray<hkEntity*> hkEntityArray;

struct hkWorldCallbackUtil {
    static void firePostCollideCallback(hkWorld* world, const hkStepInfo& stepInfo);                                 // 0x0109F6C0
    static void fireIslandPostCollideCallback(hkWorld* world, hkSimulationIsland* island, const hkStepInfo& stepInfo); // 0x0109F7E0
    static void fireContactPointRemoved(hkWorld* world, hkContactPointRemovedEvent& event);                           // 0x0109F160
};
struct hkEntityCallbackUtil {
    static void fireContactPointRemovedInternal(hkEntity* entity, hkContactPointRemovedEvent& event);                 // 0x0109E8E0
};

struct hkWorld {
    char pad0[0xc];
    float m_currentTime;                             // +0x0c
    char pad10[0x08];
    float m_timeOfNextPsi;                           // +0x18
    char pad1c[0x38 - 0x1c];
    hkArray<hkSimulationIsland*> m_activeSimulationIslands;    // +0x38
    char pad44[0x78 - 0x44];
    hkProcessCollisionInput* m_collisionInput;       // +0x78
    char pad7c[0x88 - 0x7c];
    int m_pendingOperationsCount;                    // +0x88
    int m_lockCount;                                 // +0x8c
    char pad90[4];
    bool m_blockExecutingPendingOperations;          // +0x94
    char pad95[0x138 - 0x95];
    hkArray<void*> m_worldPostCollideListeners;      // +0x138
    char pad144[0x150 - 0x144];
    hkArray<void*> m_islandPostCollideListeners;     // +0x150
    char pad15c[0x170 - 0x15c];
    hkStepInfo m_dynamicsStepInfoStepInfo;           // +0x170 (hkWorldDynamicsStepInfo::m_stepInfo)
    hkSolverInfo m_dynamicsStepInfoSolverInfo;       // +0x180

    void queueOperation(const void* op);             // 0x010829D0
    void executePendingOperations();                 // 0x01082BF0
    void lockCriticalOperations() { ++m_lockCount; }
    void unlockAndAttemptToExecutePendingOperations()
    {
        if (--m_lockCount == 0 && m_pendingOperationsCount != 0 && !m_blockExecutingPendingOperations)
            executePendingOperations();
    }
};
HK_OFFSET_CHECK(hkWorld_solverInfo, sizeof(hkWorld) == 0x180 + 0x140);

struct hkQueuedReintegrateOperation {                // hkWorldOperation::ReintegrateAndRecollideEntities (0x14 bytes)
    uint8_t m_type;                                  // +0x00 (0x16)
    hkEntity** m_entities;                           // +0x04
    int16_t m_numEntities;                           // +0x08
    char pad0a[0x14 - 0x0a];
};

void hkSweptTransformUtil_backStepMotionState(float time, hkMotionState& ms);   // 0x0120A260 (cdecl)

bool hkSolverCheckKeycode(int level);                                            // 0x010BFBE0 (cdecl)
extern bool g_hkSolverKeycodeValid;                                              // 0x016E5ABD

struct hkToiResourceMgr;
void hkLs_localizedSolveToi(const hkToiResources& toiResources, hkConstraintSolverResources& solverResources,
                            hkToiEvent& event, hkToiResourceMgr& mgr, hkWorld* world,
                            hkEntityArray& entitiesOut, hkFixedArray<unsigned char>& flags);   // 0x010F25F0

void hkAgentNnMachine_processAgent(hkAgentNnEntry* entry, hkProcessCollisionInput& input,
                                   hkProcessCollisionOutput& output);            // 0x010FC180 (cdecl)

// ---------------------------------------------------------------------------------------------
// hkContinuousSimulation
// ---------------------------------------------------------------------------------------------
class hkContinuousSimulation {
public:
    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    virtual void vslot3();
    virtual void vslot4();
    virtual void vslot5();
    virtual void vslot6();
    virtual void vslot7();
    virtual void vslot8();
    virtual void vslot9();
    virtual void vslot10();
    virtual void vslot11();
    virtual void resetCollisionInformationForEntities(hkEntity** entities, int numEntities, hkWorld* world);   // +0x30 (0x010F1A60)
    virtual void reintegrateAndRecollideEntities(hkEntity** entities, int numEntities, hkWorld* world);       // 0x010F3460

    char pad04[0x18 - 0x04];
    hkArray<hkToiEvent> m_toiEvents;                 // +0x18 .. +0x23
    hkToiResourceMgr* m_toiResourceMgr;              // +0x24

    void collideEntitiesBroadPhaseContinuous(hkEntity** entities, int numEntities, hkWorld* world, int flag);   // 0x010F1DF0
    void processAgentsOfEntities(hkEntity** entities, int numEntities, hkProcessCollisionInput* input,
                                 void (hkContinuousSimulation::*cb)(hkAgentNnEntry*, const hkProcessCollisionInput&, hkProcessCollisionOutput&)); // 0x01099BE0
    void processAgentCollideContinuous(hkAgentNnEntry* entry, const hkProcessCollisionInput& input, hkProcessCollisionOutput& output); // 0x010F1CC0
    void collideIslandNarrowPhaseContinuous(hkSimulationIsland* island, const hkProcessCollisionInput& input);   // 0x010F1A90
    void addToiEvent(const hkProcessCollisionOutput& output, hkAgentNnEntry& entry);                            // 0x010F0B00
    void collide(hkWorld* world, const hkStepInfo& stepInfo);                      // 0x010F3600
    void simulateToi(hkWorld* world, hkToiEvent& event, hkReal physicsDeltaTime);  // 0x010F3A40
};

// @ 0x010f3460
void hkContinuousSimulation::reintegrateAndRecollideEntities(hkEntity** entities, int numEntities, hkWorld* world)
{
    if (world->m_lockCount != 0) {
        hkQueuedReintegrateOperation op;
        op.m_type = 0x16;
        op.m_entities = entities;
        op.m_numEntities = (int16_t)numEntities;
        world->queueOperation(&op);
        return;
    }
    world->lockCriticalOperations();

    hkStepInfo& collisionStepInfo = world->m_collisionInput->m_stepInfo;
    const hkStepInfo oldStepInfo = collisionStepInfo;
    const hkStepInfo stepInfo(world->m_currentTime, world->m_timeOfNextPsi);
    collisionStepInfo = stepInfo;

    for (int i = 0; i < numEntities; ++i) {
        hkEntity* entity = entities[i];
        hkSweptTransformUtil_backStepMotionState(world->m_currentTime, *(hkMotionState*)((char*)entity->m_motion + 0x10));
        entity->m_motion->step(stepInfo);
    }

    collideEntitiesBroadPhaseContinuous(entities, numEntities, world, 0);
    resetCollisionInformationForEntities(entities, numEntities, world);
    processAgentsOfEntities(entities, numEntities, world->m_collisionInput, &hkContinuousSimulation::processAgentCollideContinuous);

    world->unlockAndAttemptToExecutePendingOperations();
    world->m_collisionInput->m_stepInfo = oldStepInfo;
}

// @ 0x010f3600
void hkContinuousSimulation::collide(hkWorld* world, const hkStepInfo& stepInfo)
{
    hkMonitorStamp("TtCollide");

    world->m_dynamicsStepInfoStepInfo = stepInfo;
    world->m_collisionInput->m_stepInfo = stepInfo;
    world->m_dynamicsStepInfoSolverInfo.m_deltaTime = world->m_dynamicsStepInfoSolverInfo.m_invNumSteps * stepInfo.m_deltaTime;
    world->m_dynamicsStepInfoSolverInfo.m_invDeltaTime = (float)world->m_dynamicsStepInfoSolverInfo.m_numSteps * stepInfo.m_invDeltaTime;

    world->lockCriticalOperations();

    // broad phase: refresh every active island's entities
    for (int i = 0; i < world->m_activeSimulationIslands.m_size; ++i) {
        hkSimulationIsland* island = world->m_activeSimulationIslands.m_data[i];
        collideEntitiesBroadPhaseContinuous(island->m_entities.m_data, island->m_entities.m_size, world, 0);
        if (g_hkMemoryInstance->m_memoryState == 1) {
            world->unlockAndAttemptToExecutePendingOperations();
            hkMonitorStamp("Et");
            return;
        }
    }
    world->unlockAndAttemptToExecutePendingOperations();

    // narrow phase
    world->lockCriticalOperations();
    for (int i = 0; i < world->m_activeSimulationIslands.m_size; ++i) {
        hkSimulationIsland* island = world->m_activeSimulationIslands.m_data[i];
        collideIslandNarrowPhaseContinuous(island, *world->m_collisionInput);
        if (g_hkMemoryInstance->m_memoryState == 1) {
            world->unlockAndAttemptToExecutePendingOperations();
            hkMonitorStamp("Et");
            return;
        }
        if (world->m_islandPostCollideListeners.m_size != 0) {
            hkMonitorStamp("TtIslandPostCollideCb");
            hkWorldCallbackUtil::fireIslandPostCollideCallback(world, island, stepInfo);
            hkMonitorStamp("Et");
        }
    }
    world->unlockAndAttemptToExecutePendingOperations();

    if (world->m_worldPostCollideListeners.m_size != 0) {
        hkMonitorStamp("TtPostCollideCB");
        hkWorldCallbackUtil::firePostCollideCallback(world, stepInfo);
        hkMonitorStamp("Et");
    }
    hkMonitorStamp("Et");
}

// @ 0x010f3a40
void hkContinuousSimulation::simulateToi(hkWorld* world, hkToiEvent& event, hkReal physicsDeltaTime)
{
    if (!g_hkSolverKeycodeValid) {
        g_hkSolverKeycodeValid = hkSolverCheckKeycode(3);
        if (!g_hkSolverKeycodeValid)
            return;
    }

    hkToiResources toiResources;
    if (m_toiResourceMgr->beginToiAndSetupResources(event, m_toiEvents, toiResources) == 1)
        return;

    world->lockCriticalOperations();

    // step info from the TOI time to the end of the PSI
    hkConstraintQueryIn queryIn;
    queryIn.m_resultsBegin = 0;
    queryIn.m_resultsSize = 0;
    hkStepInfo stepInfo;
    stepInfo.m_startTime = event.m_time;
    stepInfo.m_endTime = world->m_timeOfNextPsi;
    stepInfo.m_deltaTime = stepInfo.m_endTime - stepInfo.m_startTime;
    stepInfo.m_invDeltaTime = hkRealOne / stepInfo.m_deltaTime;

    // single-step solver info derived from the world's
    hkSolverInfo solverInfo;
    solverInfo = world->m_dynamicsStepInfoSolverInfo;
    solverInfo.m_deltaTime = physicsDeltaTime;
    solverInfo.m_invDeltaTime = hkRealOne / physicsDeltaTime;
    solverInfo.m_numSteps = 1;
    solverInfo.m_invNumSteps = 1.0f;
    solverInfo.m_globalAccelerationPerSubStep.x = 0.0f; solverInfo.m_globalAccelerationPerSubStep.y = 0.0f;
    solverInfo.m_globalAccelerationPerSubStep.z = 0.0f; solverInfo.m_globalAccelerationPerSubStep.w = 0.0f;
    solverInfo.m_globalAccelerationPerStep.x = 0.0f; solverInfo.m_globalAccelerationPerStep.y = 0.0f;
    solverInfo.m_globalAccelerationPerStep.z = 0.0f; solverInfo.m_globalAccelerationPerStep.w = 0.0f;
    solverInfo.setTauAndDamping(0.5f, 1.4f);

    queryIn.m_substepDeltaTime = solverInfo.m_deltaTime;
    queryIn.m_substepInvDeltaTime = solverInfo.m_invDeltaTime;
    queryIn.m_frameDeltaTime = stepInfo.m_deltaTime;
    queryIn.m_frameInvDeltaTime = stepInfo.m_invDeltaTime;
    queryIn.m_virtualMassFactor = solverInfo.m_invNumSteps;
    queryIn.m_rhsFactor = solverInfo.m_tauDivDamp * solverInfo.m_invDeltaTime;
    queryIn.m_dampingFactor = solverInfo.m_damping;
    queryIn.m_frictionRhsFactor = solverInfo.m_frictionTauDivDamp * solverInfo.m_invDeltaTime;
    queryIn.m_tau = solverInfo.m_tau;
    queryIn.m_damping = solverInfo.m_damping;

    hkConstraintSolverResources solverResources;
    hkConstraintSolverSetup::initializeSolverState(stepInfo, solverInfo, queryIn,
                                                   toiResources.m_solverBuffer, toiResources.m_solverBufferSize, solverResources);
    queryIn.m_resultsBegin = *(void**)(solverResources.m_data + 0x24);
    queryIn.m_resultsSize = *(int*)(solverResources.m_data + 0x2c);

    hkMonitorStampList("LtTOI", "SolveToi");

    // the island of the (first) non-fixed entity of the event
    hkSimulationIsland* island = event.m_entities[0]->m_fixed ? event.m_entities[1]->m_simulationIsland
                                                              : event.m_entities[0]->m_simulationIsland;
    const int numIslandEntities = island->m_entities.m_size;
    char* flags = hkAllocateStackChars(numIslandEntities);
    hkString_memSet(flags, 0, numIslandEntities);

    // solve; collects the entities moved to the TOI and flags (value 8) those of this island
    hkFixedArray<unsigned char> flagArray;
    flagArray.m_data = (unsigned char*)flags;
    hkEntity* inplaceStorage[64];
    hkEntityArray involved;
    involved.m_data = inplaceStorage;
    involved.m_size = 0;
    involved.m_capacityAndFlags = 0x80000040;
    hkLs_localizedSolveToi(toiResources, solverResources, event, *m_toiResourceMgr, world, involved, flagArray);
    hkConstraintSolverResources_destruct(&solverResources);

    // drop the queued TOI events of the entities that were just solved
    hkMonitorStamp("StEvtCleanup");
    for (int i = m_toiEvents.m_size - 1; i >= 0; --i) {
        hkToiEvent& e = m_toiEvents.m_data[i];
        if ((e.m_entities[0]->m_simulationIsland == island && flags[e.m_entities[0]->m_storageIndex] == 8)
            || (e.m_entities[1]->m_simulationIsland == island && flags[e.m_entities[1]->m_storageIndex] == 8)) {
            hkContactPointRemovedEvent removed;
            removed.m_contactPointId = 0xffff;
            removed.m_contactPointMaterial = &e.m_material;
            removed.m_entityA = e.m_entities[0];
            removed.m_entityB = e.m_entities[1];
            removed.m_internalContactMgr = e.m_contactMgr;
            hkWorldCallbackUtil::fireContactPointRemoved(e.m_entities[0]->m_world, removed);
            if (e.m_entities[0]->m_collisionListeners.m_size != 0)
                hkEntityCallbackUtil::fireContactPointRemovedInternal(e.m_entities[0], removed);
            if (e.m_entities[1]->m_collisionListeners.m_size != 0)
                hkEntityCallbackUtil::fireContactPointRemovedInternal(e.m_entities[1], removed);
            // removeAt(i): move the last element into the hole
            --m_toiEvents.m_size;
            m_toiEvents.m_data[i] = m_toiEvents.m_data[m_toiEvents.m_size];
        }
    }

    // recollide everything that moved
    hkMonitorStamp("StCollide");
    const hkStepInfo collideStepInfo(event.m_time, world->m_timeOfNextPsi);
    hkProcessCollisionInput* input = world->m_collisionInput;
    input->m_stepInfo = collideStepInfo;

    hkEntity** const movedEntities = involved.m_data;
    const int numMoved = involved.m_size;
    if (numMoved != 0) {
        collideEntitiesBroadPhaseContinuous(movedEntities, numMoved, world, 0);
        if (g_hkMemoryInstance->m_memoryState != 1) {
            hkSimulationIsland* const movedIsland = movedEntities[0]->m_simulationIsland;
            const int numMovedIslandEntities = movedIsland->m_entities.m_size;
            char* touched = hkAllocateStackChars(numMovedIslandEntities);
            int touchedCapacityAndFlags = numMovedIslandEntities | 0x80000000;
            hkString_memSet(touched, 0, numMovedIslandEntities);

            hkProcessCollisionOutput output;
            output.m_toi = HK_REAL_MAX;

            bool outOfMemory = false;
            for (int i = 0; i < numMoved && !outOfMemory; ++i) {
                hkEntity* entity = movedEntities[i];
                touched[entity->m_storageIndex] = 1;
                for (int j = 0; j < entity->m_collidable.m_collisionEntries.m_size; ++j) {
                    hkCollisionEntry& ce = entity->m_collidable.m_collisionEntries.m_data[j];
                    hkEntity* partner = ce.m_partner->getOwner();
                    if (partner->m_simulationIsland == movedIsland && touched[partner->m_storageIndex] != 0)
                        continue;
                    hkAgentNnEntry* agent = ce.m_agentEntry;

                    output.m_firstFreeContactPoint = output.m_contactPoints;
                    output.m_toi = HK_REAL_MAX;
                    output.m_potentialContacts = 0;
                    input->m_collisionQualityInfo = &input->m_dispatcher->m_collisionQualityInfo[agent->m_collisionQualityIndex];
                    input->m_createPredictiveAgents = input->m_collisionQualityInfo->m_useContinuousPhysics;

                    hkAgentNnMachine_processAgent(agent, *input, output);

                    // out-of-memory watchdog
                    {
                        hkMemory* mem = g_hkMemoryInstance;
                        int used = mem->m_pageMemoryUsed + mem->m_sysAllocsSize;
                        if (mem->m_criticalMemoryLimit <= used || (mem->m_criticalMemoryLimit - used) == 0)
                            mem->m_memoryState = 1;
                    }
                    if (g_hkMemoryInstance->m_memoryState == 1) {
                        outOfMemory = true;
                        break;
                    }
                    if (output.m_firstFreeContactPoint != output.m_contactPoints)
                        agent->m_contactMgr->processContact(*agent->m_collidable[0], *agent->m_collidable[1], *input, output);
                    if (output.m_toi < HK_REAL_MAX)
                        addToiEvent(output, *agent);
                }
            }

            hkDeallocateStackChars(touched);
            hkArrayDeallocate(touched, touchedCapacityAndFlags, 1);
        }
    }

    hkArrayDeallocate(involved.m_data, involved.m_capacityAndFlags, sizeof(hkEntity*));
    hkDeallocateStackChars(flags);

    m_toiResourceMgr->cleanupResources(event, m_toiEvents, toiResources);
    world->unlockAndAttemptToExecutePendingOperations();
    hkMonitorStamp("lt");
}

// layout checks (offsets recovered from the asm / dev PDB)
HK_OFFSET_CHECK(chk_entity_motion, offsetof(hkEntity, m_motion) == 0x58);
HK_OFFSET_CHECK(chk_entity_island, offsetof(hkEntity, m_simulationIsland) == 0x5c);
HK_OFFSET_CHECK(chk_entity_storage, offsetof(hkEntity, m_storageIndex) == 0x94);
HK_OFFSET_CHECK(chk_entity_fixed, offsetof(hkEntity, m_fixed) == 0x99);
HK_OFFSET_CHECK(chk_entity_listeners, offsetof(hkEntity, m_collisionListeners) == 0x9c);
HK_OFFSET_CHECK(chk_entity_entries, offsetof(hkEntity, m_collidable) + offsetof(hkLinkedCollidable, m_collisionEntries) == 0x40);
HK_OFFSET_CHECK(chk_world_lock, offsetof(hkWorld, m_lockCount) == 0x8c);
HK_OFFSET_CHECK(chk_world_block, offsetof(hkWorld, m_blockExecutingPendingOperations) == 0x94);
HK_OFFSET_CHECK(chk_world_solver, offsetof(hkWorld, m_dynamicsStepInfoSolverInfo) == 0x180);
HK_OFFSET_CHECK(chk_world_post, offsetof(hkWorld, m_worldPostCollideListeners) == 0x138);
HK_OFFSET_CHECK(chk_world_ipost, offsetof(hkWorld, m_islandPostCollideListeners) == 0x150);
HK_OFFSET_CHECK(chk_sim_events, offsetof(hkContinuousSimulation, m_toiEvents) == 0x18);
HK_OFFSET_CHECK(chk_sim_mgr, offsetof(hkContinuousSimulation, m_toiResourceMgr) == 0x24);
HK_OFFSET_CHECK(chk_solver_dt, offsetof(hkSolverInfo, m_deltaTime) == 0x124);
HK_OFFSET_CHECK(chk_out_toi, offsetof(hkProcessCollisionOutput, m_toi) == 0x3034);
HK_OFFSET_CHECK(chk_out_pot, offsetof(hkProcessCollisionOutput, m_potentialContacts) == 0x3040);
HK_OFFSET_CHECK(chk_toi_contact, offsetof(hkToiEvent, m_contactPoint) == 0x20);
HK_OFFSET_CHECK(chk_mem_pages, offsetof(hkMemory, m_pageMemoryUsed) == 0x28 && offsetof(hkMemory, m_sysAllocsSize) == 0x14);
HK_OFFSET_CHECK(chk_tm_stack, offsetof(hkThreadMemoryRaw, m_stackCurrent) == 0x20 && offsetof(hkThreadMemoryRaw, m_stackEnd) == 0x2c);
HK_OFFSET_CHECK(chk_toi_events_size, sizeof(hkQueuedReintegrateOperation) == 0x14);
