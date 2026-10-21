// Slice s010a32c0: 0x010A32C0..0x010A3E70 -- Havok 3.1.0 (prebuilt lib, VS2008 cl 15.00).
//   0x010A32C0 hkHalfstepSimulation::stepDeltaTime, 0x010A3760 hkEntityEntityBroadPhaseListener ctor,
//   0x010A3780/0x010A37E0 add/removeCollisionPair, 0x010A3810..0x010A3A70 hkWorldAgentUtil,
//   0x010A3A90 hkInternalConstraintUtils::calcRelativeAngle, 0x010A3A70..0x010A3E70 constraint-data methods.
// Flags: /O2 /MD /Gy /TP /GS- /fp:fast (Havok: x87 floats, no EH frame, /GS-; see the memory-failure epilogues).
// Layouts: match/slices/s010840e0 (hkWorld/hkSimulation), match/slices/s010869e0/hk31_world.h
// (hkAgentNnEntry/hkAgentNnTrack/hkSimulationIsland), src/game/include/hkAgentNnEntry.h.
#include <stddef.h>
#include <math.h>
#include <intrin.h>
#include "types.h"

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern "C" void* __cdecl memset(void*, int, size_t);

typedef float hkReal;
typedef uint16_t hkUint16;
typedef uint8_t hkUint8;
typedef int8_t hkInt8;

// hkBool: one byte (retail; see match/slices/s010840e0).
class hkBool
{
public:
    hkBool() : m_bool(0) {}
    hkBool(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
    int8_t m_bool;
};

// ---------------------------------------------------------------------------------------------- core types
class hkReferencedObject
{
public:
    hkReferencedObject() { m_referenceCount = 1; }
    virtual ~hkReferencedObject() {}
    void addReference() { if (m_memSizeAndFlags != 0) m_referenceCount++; }
    void removeReference()
    {
        if (m_memSizeAndFlags != 0)
        {
            if ((*(volatile short*)&m_referenceCount += -1) == 0)
                delete this;
        }
    }
    void operator delete(void*) {}

    hkUint16 m_memSizeAndFlags;     // +0x4
    short    m_referenceCount;      // +0x6
};

struct __declspec(align(16)) hkVector4 { float x, y, z, w; };
class hkQuaternion { public: float x, y, z, w; };
class hkRotation { public: hkVector4 m_col0, m_col1, m_col2; };      // 0x30
class hkTransform { public: hkRotation m_rotation; hkVector4 m_translation; };   // 0x40
class hkMatrix3 { public: hkVector4 m_col0, m_col1, m_col2; void mul(hkReal v); };    // mul at 0x01081bb0
class hkStepInfo { public: hkReal m_startTime, m_endTime, m_deltaTime, m_invDeltaTime; };

namespace hkMath { float atan2fApproximation(float y, float x); }     // 0x0120adb0

class hkMemory
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void* allocateChunk(int nbytes, int cls);
    virtual void v5();
    virtual void* onRowEmpty(int row, int cls);
    virtual void deallocateChunk(void* p, int nbytes, int cls);
    virtual void v8();

    int m_numUsedChunks;                            // +0x04 (the sticky "out of memory" flag)
    int m_rowSize;                                  // +0x08
    int m_numBytesAllocated;                        // +0x14
    int m_numBytesAllocated2;                       // +0x28
    static hkMemory* s_instance;                    // 0x016e4178
};

extern unsigned long g_hkThreadMemoryTlsIndex;      // 0x016e4174

class hkThreadMemory
{ public:
    struct Elem { Elem* m_next; };
    uint32_t m_pad0[0xe];
    Elem*    m_freeListHead[17];    // +0x38
    int      m_freeListCount[17];   // +0x7c

    static hkThreadMemory* getInstance() { return (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }
    static int constSizeToRow(int nbytes) { return (nbytes - 1) >> 3; }
    void* allocateChunkConstSize(int nbytes, int cls)
    {
        int row = constSizeToRow(nbytes);
        Elem* p = m_freeListHead[row];
        if (p)
        {
            m_freeListCount[row]--;
            m_freeListHead[row] = p->m_next;
            return p;
        }
        return hkMemory::s_instance->onRowEmpty(row, cls);
    }
};

// ---------------------------------------------------------------------------------------------- monitor stream
// HK_TIMER_BEGIN / HK_TIMER_END of hkMonitorStream.h; the fast path is inlined. A timer command is
// 0x10 bytes (name ptr + rdtsc + the begin/end marker the writer puts after them).
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8

class hkMonitorStream
{
public:
    void startTimer(const char* name)
    {
        unsigned char* current = (unsigned char*)TlsGetValue(g_hkMonitorStreamCurrentTls);
        if (current < (unsigned char*)TlsGetValue(g_hkMonitorStreamEndTls))
        {
            *(const char**)(current) = name;
            *(uint32_t*)(current + 4) = __rdtsc();
            current[8] = 'B';
            TlsSetValue(g_hkMonitorStreamCurrentTls, current + 0xc);
        }
    }
    void endTimer(const char* marker)
    {
        unsigned char* current = (unsigned char*)TlsGetValue(g_hkMonitorStreamCurrentTls);
        if (current < (unsigned char*)TlsGetValue(g_hkMonitorStreamEndTls))
        {
            *(const char**)(current) = marker;
            *(uint32_t*)(current + 4) = __rdtsc();
            current[8] = 'E';
            TlsSetValue(g_hkMonitorStreamCurrentTls, current + 0xc);
        }
    }
};

// ---------------------------------------------------------------------------------------------- simulation
class hkWorld;
class hkSimulation : public hkReferencedObject          // 0xc
{
public:
    hkSimulation() {}
    virtual void simSlot0();
    virtual void simSlot1();
    virtual void step(hkWorld* world, const hkStepInfo& stepInfo, hkReal invDeltaTime);
    hkWorld* m_world;                       // +0x08
};

class hkAsynchronousSimulation : public hkSimulation    // 0x10
{
public:
    hkAsynchronousSimulation() { m_synchronizeFrameAndPhysicsTime.m_bool = 1; }
    hkBool m_synchronizeFrameAndPhysicsTime;    // +0x0c
};

enum hkStepResult { HK_STEP_RESULT_SUCCESS = 0, HK_STEP_RESULT_MEMORY_FAILURE = 1, HK_STEP_RESULT_BUSY = 2 };

// hkWorldDynamicsStepInfo = hkStepInfo (0x10) + hkSolverInfo (0x140) = 0x150. In the original the first
// argument of stepDeltaTime is the embedding hkWorld, and the psi step reaches the solver step through it.
struct hkWorldDynamicsStepInfo
{
    hkStepInfo m_stepInfo;                  // +0x00
    uint32_t   m_solverInfo[0x140 / 4];     // +0x10
};

class hkHalfstepSimulation : public hkAsynchronousSimulation   // 0x14
{
public:
    hkHalfstepSimulation();                 // 0x010a32a0
    virtual hkStepResult stepDeltaTime(hkWorld* world, hkReal physicsDeltaTime, hkReal frameDeltaTime);
    hkReal m_frameDeltaTime;                // +0x10
    int    m_simulationStep;                // +0x10 (slot reused: frame delta, then the half-step flag)
};

// ---------------------------------------------------------------------------------------------- hkWorld
class hkSimulationIsland;
class hkRigidBody;
class hkBroadPhase;
class hkProcessCollisionInput;
class hkCollisionFilter;
class hkCollisionDispatcher;
class hkContactMgrFactory;
class hkWorldOperationQueue;
class hkEntity;
class hkMultiThreadLock { public: unsigned int m_threadId; int m_lockCount; };

class hkWorld : public hkReferencedObject             // 0x2f0
{
public:
    hkSimulation*                     m_simulation;                 // +0x08
    hkReal                            m_currentTime;                // +0x0c
    hkReal                            m_timeOfNextFrame;            // +0x10
    hkReal                            m_timeOfLastPsi;              // +0x14
    hkReal                            m_timeOfNextPsi;              // +0x18
    uint32_t                          m_pad1c;
    hkVector4                         m_gravity;                    // +0x20
    hkSimulationIsland*               m_fixedIsland;                // +0x30
    hkRigidBody*                      m_fixedRigidBody;             // +0x34
    uint32_t                          m_activeSimulationIslands[3]; // +0x38
    uint32_t                          m_inactiveSimulationIslands[3];   // +0x44
    uint32_t                          m_dirtySimulationIslands[3];  // +0x50
    void*                             m_maintenanceMgr;             // +0x5c
    void*                             m_memoryWatchDog;             // +0x60
    hkBroadPhase*                     m_broadPhase;                 // +0x64
    void*                             m_broadPhaseDispatcher;       // +0x68
    void*                             m_phantomBroadPhaseListener;  // +0x6c
    void*                             m_entityEntityBroadPhaseListener;   // +0x70
    void*                             m_broadPhaseBorderListener;   // +0x74
    hkProcessCollisionInput*          m_collisionInput;             // +0x78
    hkCollisionFilter*                m_collisionFilter;            // +0x7c
    hkCollisionDispatcher*            m_collisionDispatcher;        // +0x80
    hkWorldOperationQueue*            m_pendingOperations;          // +0x84
    int                               m_pendingOperationsCount;     // +0x88
    int                               m_lockCount;                  // +0x8c
    int                               m_lockCountForPhantoms;       // +0x90
    hkBool                            m_blockExecutingPendingOperations;  // +0x94
    hkBool                            m_criticalOperationsAllowed;  // +0x95
    uint16_t                          m_pad96;
    void*                             m_pendingOperationQueues;     // +0x98
    int                               m_pendingOperationQueueCount; // +0x9c
    hkMultiThreadLock                 m_multiThreadLock;            // +0xa0
    hkBool                            m_processActionsInSingleThread;     // +0xa8
    uint8_t                           m_pada9[3];
    void*                             m_modifyConstraintCriticalSection;  // +0xac
    void*                             m_worldLock;                  // +0xb0
    hkBool                            m_wantSimulationIslands;      // +0xb4
    hkBool                            m_wantDeactivation;           // +0xb5
    hkBool                            m_shouldActivateOnRigidBodyTransformChange;   // +0xb6
    uint8_t                           m_padb7;
    hkReal                            m_highFrequencyDeactivationPeriod;  // +0xb8
    hkReal                            m_lowFrequencyDeactivationPeriod;   // +0xbc
    hkReal                            m_toiCollisionResponseRotateNormal; // +0xc0
    int                               m_simulationType;             // +0xc4
    unsigned int                      m_lastEntityUid;              // +0xc8
    uint32_t                          m_phantoms[3];                // +0xcc
    uint32_t                          m_actionListeners[3];         // +0xd8
    uint32_t                          m_entityListeners[3];         // +0xe4
    uint32_t                          m_phantomListeners[3];        // +0xf0
    uint32_t                          m_constraintListeners[3];     // +0xfc
    uint32_t                          m_worldDeletionListeners[3];  // +0x108
    uint32_t                          m_islandActivationListeners[3];    // +0x114
    uint32_t                          m_worldPostSimulationListeners[3]; // +0x120
    uint32_t                          m_worldPostIntegrateListeners[3];  // +0x12c
    uint32_t                          m_worldPostCollideListeners[3];    // +0x138
    uint32_t                          m_islandPostIntegrateListeners[3]; // +0x144
    uint32_t                          m_islandPostCollideListeners[3];   // +0x150
    uint32_t                          m_collisionListeners[3];      // +0x15c
    hkWorldDynamicsStepInfo           m_dynamicsStepInfo;           // +0x170
    uint32_t                          m_broadPhaseExtents[8];       // +0x2c0
    int                               m_broadPhaseNumMarkers;       // +0x2e0
    int                               m_broadPhaseQuerySize;        // +0x2e4
    int                               m_broadPhaseUpdateSize;       // +0x2e8
    hkInt8                            m_contactPointGeneration;     // +0x2ec
};

// ---------------------------------------------------------------------------------------------- agents
class hkCollidable
{ public:
    virtual ~hkCollidable();
    void* m_broadPhaseHandle;                  // +0x04
    void* m_shape;                             // +0x08
    void* m_motion;                            // +0x0c
    void* m_entity;                            // +0x10
};
class hkLinkedCollidable : public hkCollidable { public:
    void* m_pairInfo[2];                       // +0x14
};
struct hkAgentNnEntry                                          // 0x1c bytes (retail)
{
    uint8_t m_streamCommand;       // +0
    uint8_t m_agentType;           // +1
    uint8_t m_numContactPoints;    // +2
    uint8_t m_size;                // +3
    uint32_t m_userData;           // +4
    uint8_t m_collisionQualityIndex;   // +8
    uint8_t m_padding[3];          // +9
    uint16_t m_agentIndexOnCollidable[2];   // +0xc
    uint32_t m_contactMgr;         // +0x10
    hkLinkedCollidable* m_collidable[2];    // +0x14
};
class hkBroadPhaseHandle
{ public:
    virtual ~hkBroadPhaseHandle();
};
class hkTypedBroadPhaseHandle : public hkBroadPhaseHandle { public:
    int8_t m_type;                             // +0x04
    int8_t m_ownerOffset;                      // +0x05 (the original walks it as a signed byte)
    uint16_t m_objectQualityType;              // +0x06
    uint32_t m_collisionFilterInfo;            // +0x08
};
struct hkBroadPhasePair
{
    hkBroadPhaseHandle* m_a;                   // +0
    hkBroadPhaseHandle* m_b;                   // +4
    uint32_t m_0x8;
    uint32_t m_0xc;
};
struct hkTypedBroadPhaseHandlePair
{
    hkBroadPhaseHandle* m_a;                   // +0
    hkBroadPhaseHandle* m_b;                   // +4
};

struct hkAgentNnTrack                                          // 0x18 bytes
{
    char** m_sectorData;           // +0
    int m_numSectors;              // +4
    int m_sectorCapacity;          // +8
    char* m_inlineSector;          // +0xc
    unsigned int m_bytesUsedInLastSector;   // +0x10
    unsigned short m_agentSize;    // +0x14
    unsigned short m_sectorSize;   // +0x16
};

class hkMaterial { public: uint32_t m_data[3]; };

class hkEntity
{
public:
    virtual void deallocateInternalArrays();
    virtual hkEntity* entityClone() const;
    virtual void _v2(); virtual void _v3(); virtual void _v4(); virtual void _v5(); virtual void _v6();

    uint32_t m_vptr_memSize[2];                 // +0
    void* m_broadPhaseHandle;                   // +8
    uint8_t m_pad0c[0x10 - 0xc];
    uintptr_t m_0x10;                           // +0x10
    uint8_t m_pad14[0x58 - 0x14];
    void*              m_motion;                // +0x58
    hkSimulationIsland* m_simulationIsland;     // +0x5c
    hkMaterial         m_material;              // +0x60
    void*              m_deactivator;           // +0x6c
    uint32_t           m_constraintsMaster[3];  // +0x70
    uint32_t           m_constraintsSlave[3];   // +0x7c
    uint32_t           m_constraintRuntime[3];  // +0x88
    uint16_t           m_storageIndex;          // +0x94
    uint16_t           m_processContactCallbackDelay;   // +0x96
    char               m_autoRemoveLevel;       // +0x98
    hkBool             m_fixed;                 // +0x99
    hkBool             m_isFixedOrKeyframed;    // +0x9a
    hkBool             m_internalCollideFlag;   // +0x9b
};

class hkSimulationIsland : public hkReferencedObject          // 0x74 bytes (retail)
{
public:
    int m_maxSizeOfJacobians;           // +0x08
    int m_sumSizeOfJacobians;           // +0x0c
    int m_sumSizeOfSchemas;             // +0x10
    int m_sumSizeOfMotions;             // +0x14
    int m_sumNumSolverResults;          // +0x18
    hkWorld* m_world;                   // +0x1c
    uint16_t m_storageIndex;            // +0x20
    uint16_t m_dirtyListIndex;          // +0x22
    uint8_t m_highFrequencyDeactivationCounter;   // +0x24
    uint8_t m_lowFrequencyDeactivationCounter;    // +0x25
    hkBool m_splitCheckRequested;       // +0x26
    hkBool m_actionListCleanupNeeded;   // +0x27
    hkBool m_active;                    // +0x28
    hkBool m_isInActiveIslandsArray;    // +0x29
    uint16_t m_pad2a;
    hkMultiThreadLock m_multiThreadLock;    // +0x2c
    hkReal m_timeSinceLastHighFrequencyCheck;   // +0x34
    hkReal m_timeSinceLastLowFrequencyCheck;    // +0x38
    hkEntity** m_entityData;            // +0x3c
    int m_numEntities;                  // +0x40
    int m_entityCapacity;               // +0x44
    hkEntity* m_inlineEntity;           // +0x48
    hkAgentNnTrack m_agentTrack;        // +0x4c
};

// The 0x010A3890 loop reads [+0x40] (data) and [+0x44] (count) with a stride of 8 bytes per element;
// element+0 is the agent entry handed to InvalidateTimInAgent.
struct hkCollisionEntry { void* m_agentEntry; void* m_partner; };   // 8 bytes
struct hkEntityPerEntityView
{
    uint8_t m_pad00[0x40];
    hkCollisionEntry* m_entries;        // +0x40
    int m_numEntries;                   // +0x44
};

class hkContactMgr;
struct hkCollisionDispatcher                    // hkReferencedObject; only the tail tables matter here
{
    uint32_t m_vptr_memSize[2];                 // +0
    hkContactMgrFactory* m_contactMgrFactories[4];  // +8
    uint8_t m_pad18[0x80 - 0x18];
    int m_numContactPoints;                     // +0x80
    uint8_t m_pad84[0x19d4 - 0x84];
    char m_collisionQualityTable[8][8];         // +0x19d4
    uint8_t m_pad1a24[0x50];
    char m_agentTypeForCombination[8];          // +0x1a24 (indexed with quality*0x3c in the original)

    int calculateCombinedCollisionQuality(int qualityB);   // 0x010cd600
};

// The broad-phase handle's owner: ownerOffset at handle+5 selects the hkEntity inside the collidable.
class hkEntityEntityBroadPhaseListener
{
public:
    hkEntityEntityBroadPhaseListener(hkWorld* world);
    virtual void addCollisionPair(const hkBroadPhasePair& pair);
    virtual void removeCollisionPair(const hkBroadPhasePair& pair);

    uint16_t m_pad04;                   // +4
    uint16_t m_objectQualityType;       // +6
    hkWorld* m_world;                   // +8
};

// The hjWorld / agent-machine helpers this slice calls; the _hkAgentNnMachine_* set are ordinary functions
// of hkAgentNnMachine.cpp (hkAgentNnMachine.inl only holds __forceinline wrappers).
extern "C" void _hkAgentNnMachine_WarpTimeInAgent(hkAgentNnEntry* entry, hkReal time, const hkTransform* oldTransform, const hkTransform* newTransform);   // 0x010fba90
extern "C" void _hkAgentNnMachine_InvalidateTimInAgent(hkAgentNnEntry* entry, hkAgentNnEntry* other);   // 0x010fba10
extern "C" void _hkAgentNnMachine_GetAgentType(const void* a, const void* b, void* world, void* agentTypeOut, void* flippedOut);   // 0x010fb8f0
extern "C" void _hkAgentNnMachine_CreateAgent(hkAgentNnTrack* track, const void* a, const void* b, void* agentType, void* world, void* createArg);   // 0x010fbdb0
extern "C" void _hkAgentNnMachine_DestroyAgent(hkAgentNnTrack* track, hkAgentNnEntry* entry, int numContactPoints);   // 0x010fbf80
extern "C" void* hkAgentNnTrack_findAgent(void* collA, void* collB);   // 0x010fbb30

void hkWorld_integrateIslandsEntityMotion(hkWorld* world, hkReal startTime, hkReal endTime, hkReal invDeltaTime);     // 0x01099690
void hkWorld_performBroadphaseAndCollisionDetection(hkWorld* world, hkReal startTime, hkReal endTime, hkReal invDeltaTime);   // 0x0109a200
void hkWorldCallbackUtil_firePostSimulationCallback(hkWorld* world, hkReal startTime, hkReal endTime, hkReal invDeltaTime);   // 0x0109f5a0
void hkWorld_markIslandDirtyThreadSafe(hkWorld* world, hkSimulationIsland* islandA, hkSimulationIsland* islandB);   // 0x010a1170
int  hkWorld_calcMaxIslandSizeEstimate(const hkWorld* world);   // 0x01082ca0
int  hkMemoryWatchdog_getUsedMemory();                          // 0x01083060
int  hkMemoryWatchdog_getMaxAllowedMemory();                    // 0x01083080
void hkWorld_integrateIslandsAtPsi(hkWorld* world, const hkStepInfo& stepInfo, hkReal invDeltaTime);   // hkWorld.inl (through m_dynamicsStepInfo)

struct hkWorldAgentUtil;
void hkWorldAgentUtil_addAgent(hkAgentNnEntry* entryA, hkAgentNnEntry* entryB, hkCollisionDispatcher* dispatcher);   // 0x010a3920
void hkWorldAgentUtil_removeAgent(hkAgentNnEntry* entry);   // 0x010a39f0

// =============================================================================================================
// hkHalfstepSimulation::stepDeltaTime (0x010A32C0)
// =============================================================================================================
// @ 0x010a32c0
hkStepResult hkHalfstepSimulation::stepDeltaTime(hkWorld* world, hkReal physicsDeltaTime, hkReal frameDeltaTime)
{
    hkMonitorStream stream;
    stream.startTimer("TtSimulate");             // 0x014a1f8c

    m_frameDeltaTime = frameDeltaTime;
    world->m_timeOfNextFrame += physicsDeltaTime;

    const hkReal halfDelta = frameDeltaTime + frameDeltaTime;

    for (;;)
    {
        if (m_synchronizeFrameAndPhysicsTime
            && fabsf(world->m_timeOfNextFrame - world->m_timeOfNextPsi) < halfDelta * 0.01f
            && physicsDeltaTime / halfDelta > 0.1f)
        {
            world->m_timeOfNextFrame = world->m_timeOfNextPsi;
        }

        if (m_simulationStep == 0)
        {
            if (world->m_timeOfNextFrame > world->m_timeOfNextPsi)
                goto postSimulate;

            const int islandSizeEstimate = hkWorld_calcMaxIslandSizeEstimate(world);
            const hkThreadMemory* threadMemory = hkThreadMemory::getInstance();
            const int largestFreeChunk = threadMemory->m_freeListCount[0] - (int)threadMemory->m_freeListHead[0];
            if (largestFreeChunk - 0x10 < islandSizeEstimate)
            {
                if (islandSizeEstimate > hkMemoryWatchdog_getMaxAllowedMemory() - hkMemoryWatchdog_getUsedMemory())
                {
                    hkMemory::s_instance->m_numUsedChunks = 1;
                    stream.endTimer((const char*)0x0149cc34);
                    return HK_STEP_RESULT_MEMORY_FAILURE;
                }
            }

            const hkReal newPsi = world->m_timeOfNextPsi + halfDelta;
            world->m_timeOfLastPsi = world->m_timeOfNextPsi;
            world->m_timeOfNextPsi = newPsi;

            hkStepInfo psiStep;
            psiStep.m_startTime    = world->m_timeOfLastPsi;
            psiStep.m_endTime      = world->m_timeOfNextPsi;
            psiStep.m_deltaTime    = world->m_timeOfNextPsi - world->m_timeOfLastPsi;
            psiStep.m_invDeltaTime = 1.0f / psiStep.m_deltaTime;

            hkWorld_integrateIslandsAtPsi(world, psiStep, psiStep.m_invDeltaTime);
            world->m_currentTime = world->m_timeOfLastPsi;
            hkWorld_integrateIslandsEntityMotion(world, psiStep.m_startTime, psiStep.m_endTime, psiStep.m_invDeltaTime);
            m_simulationStep = 1;
            continue;
        }

        if (world->m_timeOfNextFrame <= (world->m_timeOfLastPsi + world->m_timeOfNextPsi) * 0.5f)
            break;

        hkStepInfo frameStep;
        frameStep.m_startTime    = world->m_timeOfLastPsi;
        frameStep.m_endTime      = world->m_timeOfNextPsi;
        frameStep.m_deltaTime    = world->m_timeOfNextPsi - world->m_timeOfLastPsi;
        frameStep.m_invDeltaTime = 1.0f / frameStep.m_deltaTime;

        hkWorld_performBroadphaseAndCollisionDetection(world, frameStep.m_startTime, frameStep.m_endTime, frameStep.m_invDeltaTime);
        if (hkMemory::s_instance->m_numUsedChunks == 1)
        {
            stream.endTimer((const char*)0x0149cc34);
            return HK_STEP_RESULT_BUSY;
        }

        m_simulationStep = 0;
        world->m_currentTime = (world->m_timeOfLastPsi + world->m_timeOfNextPsi) * 0.5f;
    }

postSimulate:
    world->m_currentTime = world->m_timeOfNextFrame;

    stream.startTimer("TtPostSimulateCb");       // 0x014a1f60

    hkStepInfo postStep;
    postStep.m_startTime    = world->m_timeOfNextFrame - physicsDeltaTime;
    postStep.m_endTime      = world->m_timeOfNextFrame;
    postStep.m_deltaTime    = postStep.m_endTime - postStep.m_startTime;
    postStep.m_invDeltaTime = 1.0f / postStep.m_deltaTime;

    hkWorldCallbackUtil_firePostSimulationCallback(world, postStep.m_startTime, postStep.m_endTime, postStep.m_invDeltaTime);
    stream.endTimer((const char*)0x0149cc34);
    stream.endTimer((const char*)0x0149cc34);
    return HK_STEP_RESULT_SUCCESS;
}

// =============================================================================================================
// hkEntityEntityBroadPhaseListener (0x010A3760..0x010A37E0)
// =============================================================================================================
// @ 0x010a3760
hkEntityEntityBroadPhaseListener::hkEntityEntityBroadPhaseListener(hkWorld* world)
{
    m_objectQualityType = 1;
    m_world = world;
}

// @ 0x010a3780
void hkEntityEntityBroadPhaseListener::addCollisionPair(const hkBroadPhasePair& pair)
{
    // Each handle's ownerOffset (a signed byte at +5) shifts it to an hkLinkedCollidable; +0 is its entity.
    hkLinkedCollidable* collA = (hkLinkedCollidable*)((const char*)pair.m_a + ((hkTypedBroadPhaseHandle*)pair.m_a)->m_ownerOffset);
    hkLinkedCollidable* collB = (hkLinkedCollidable*)((const char*)pair.m_b + ((hkTypedBroadPhaseHandle*)pair.m_b)->m_ownerOffset);
    hkEntity* entityA = (hkEntity*)collA->m_entity;
    hkEntity* entityB = (hkEntity*)collB->m_entity;

    hkCollisionDispatcher* dispatcher = m_world->m_collisionDispatcher;
    const char quality = dispatcher->m_collisionQualityTable[entityB->m_material.m_data[0]]
                            [dispatcher->calculateCombinedCollisionQuality(entityA->m_material.m_data[0])];
    if (quality != 0)
    {
        dispatcher->m_agentTypeForCombination[0] = dispatcher->m_agentTypeForCombination[quality * 0x3c];
        hkWorldAgentUtil_addAgent((hkAgentNnEntry*)entityA, (hkAgentNnEntry*)entityB, dispatcher);
    }
}

// @ 0x010a37e0
void hkEntityEntityBroadPhaseListener::removeCollisionPair(const hkBroadPhasePair& pair)
{
    hkLinkedCollidable* collA = (hkLinkedCollidable*)((const char*)pair.m_a + ((hkTypedBroadPhaseHandle*)pair.m_a)->m_ownerOffset);
    hkLinkedCollidable* collB = (hkLinkedCollidable*)((const char*)pair.m_b + ((hkTypedBroadPhaseHandle*)pair.m_b)->m_ownerOffset);
    hkAgentNnEntry* entry = (hkAgentNnEntry*)hkAgentNnTrack_findAgent(collA, collB);
    if (entry != 0)
        hkWorldAgentUtil_removeAgent(entry);
}

// =============================================================================================================
// hkWorldAgentUtil (0x010A3810..0x010A3A70)
// =============================================================================================================
// @ 0x010a3810
hkSimulationIsland* hkWorldAgentUtil_getIslandFromAgentEntry(void* entry, hkSimulationIsland* islandA, hkSimulationIsland* islandB)
{
    const bool aIsSmaller = islandA->m_numEntities <= islandB->m_numEntities;
    hkSimulationIsland* island = aIsSmaller ? islandA : islandB;
    bool containsEntry = false;

    const int numEntities = island->m_numEntities;
    if (numEntities > 0)
    {
        hkEntity** entities = island->m_entityData;
        for (int i = 0; i < numEntities; i++)
        {
            if ((uintptr_t)entry >= (uintptr_t)entities[i]
                && (uintptr_t)entry < (uintptr_t)entities[i] + island->m_agentTrack.m_sectorSize)
            {
                containsEntry = true;
                break;
            }
        }
    }
    // containsEntry != aIsSmaller -> keep the smaller island
    return (containsEntry != aIsSmaller) ? island : ((island == islandA) ? islandB : islandA);
}

// @ 0x010a3890
void hkWorldAgentUtil_invalidateTimOfEntity(hkEntityPerEntityView* view, hkAgentNnEntry* entry)
{
    for (int i = 0; i < view->m_numEntries; i++)
        _hkAgentNnMachine_InvalidateTimInAgent((hkAgentNnEntry*)view->m_entries[i].m_agentEntry, entry);
}

// @ 0x010a38c0
void hkWorldAgentUtil_warpTime(hkSimulationIsland* island, hkReal time, const hkTransform& oldTransform, const hkTransform& newTransform)
{
    const int numSectors = island->m_agentTrack.m_numSectors;
    for (int i = 0; i < numSectors; i++)
    {
        const uintptr_t sector = (uintptr_t)island->m_agentTrack.m_sectorData[i];
        const uintptr_t sectorEnd = sector
            + (((i + 1) == numSectors) ? island->m_agentTrack.m_bytesUsedInLastSector
                                       : island->m_agentTrack.m_sectorSize);
        for (uintptr_t agent = sector; agent < sectorEnd; agent += ((hkAgentNnEntry*)agent)->m_size)
        {
            _hkAgentNnMachine_WarpTimeInAgent((hkAgentNnEntry*)agent, time, &oldTransform, &newTransform);
        }
    }
}

// @ 0x010a3920
void hkWorldAgentUtil_addAgent(hkAgentNnEntry* entryA, hkAgentNnEntry* entryB, hkCollisionDispatcher* dispatcher)
{
    hkEntity* entityA = (hkEntity*)entryA;
    hkEntity* entityB = (hkEntity*)entryB;

    if (!entityA->m_fixed && !entityB->m_fixed && entityA->m_simulationIsland != entityB->m_simulationIsland)
        hkWorld_markIslandDirtyThreadSafe((hkWorld*)dispatcher, entityA->m_simulationIsland, entityB->m_simulationIsland);

    hkSimulationIsland* islandA = entityA->m_simulationIsland;
    hkSimulationIsland* islandB = entityB->m_simulationIsland;
    hkSimulationIsland* island = islandB;
    if ((uint16_t)0xffff == islandA->m_storageIndex)   // errors on the uninitialized (0xffff) island
        island = islandA;

    void* agentType = 0;
    uint32_t flipped = 0;
    _hkAgentNnMachine_GetAgentType(entryA, entryB, dispatcher, &agentType, &flipped);

    hkAgentNnEntry* first = entryA;
    hkAgentNnEntry* second = entryB;
    if (flipped != 0)
    {
        first = entryB;
        second = entryA;
    }

    void* agent = (*(void* (**)(void*, hkAgentNnEntry*, hkAgentNnEntry*))((char*)agentType + 8))(dispatcher, first, second);
    _hkAgentNnMachine_CreateAgent(&island->m_agentTrack, first, second, agentType, dispatcher, agent);
}

// @ 0x010a39f0
void hkWorldAgentUtil_removeAgent(hkAgentNnEntry* entry)
{
    hkLinkedCollidable* collA = entry->m_collidable[0];
    hkLinkedCollidable* collB = entry->m_collidable[1];
    hkEntity* entityA = (hkEntity*)collA->m_entity;
    hkEntity* entityB = (hkEntity*)collB->m_entity;

    hkSimulationIsland* island;
    if (entityA->m_simulationIsland == entityB->m_simulationIsland)
    {
        island = entityA->m_simulationIsland;
        island->m_splitCheckRequested.m_bool = 1;
    }
    else if (entityA->m_fixed)
    {
        island = entityB->m_simulationIsland;
    }
    else if (entityB->m_fixed)
    {
        island = entityA->m_simulationIsland;
    }
    else
    {
        island = hkWorldAgentUtil_getIslandFromAgentEntry(entry, entityA->m_simulationIsland, entityB->m_simulationIsland);
        entityA->m_simulationIsland->m_splitCheckRequested.m_bool = 1;
        entityB->m_simulationIsland->m_splitCheckRequested.m_bool = 1;
    }

    _hkAgentNnMachine_DestroyAgent(&island->m_agentTrack, entry,
        island->m_world->m_collisionDispatcher->m_numContactPoints);
    (*(void(**)(void))entry->m_userData)();
}

// =============================================================================================================
// hkInternalConstraintUtils (0x010A3A90)
// =============================================================================================================
// @ 0x010a3a90
void hkInternalConstraintUtils_calcRelativeAngle(const hkVector4& axisA, const hkVector4& axisB,
        const hkVector4& ref0, const hkVector4& ref1, hkVector4& axisOut, hkReal& angleOut)
{
    hkVector4 axis;
    axis.x = axisA.x + axisB.x;
    axis.y = axisA.y + axisB.y;
    axis.z = axisA.z + axisB.z;
    axis.w = sqrtf(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
    if (axis.w <= 1.0e-16f)
    {
        axis = axisB;
    }
    else
    {
        axis.w = 1.0f / axis.w;
        axis.x = axis.x * axis.w;
        axis.y = axis.y * axis.w;
        axis.z = axis.z * axis.w;
        axis.w = axis.w * (axisA.w + axisB.w);
    }

    const hkReal crossX = axis.y * ref1.z - axis.z * ref1.y;
    const hkReal crossY = axis.z * ref1.x - axis.x * ref1.z;
    const hkReal crossZ = axis.x * ref1.y - axis.y * ref1.x;

    angleOut = hkMath::atan2fApproximation(
        crossX * ref0.x + (crossZ * ref0.z + crossY * ref0.y),
        (crossX * axis.y - crossY * axis.x) * ref0.z
            + ((axis.x * crossZ - crossX * axis.z) * ref0.y + (crossY * axis.z - crossZ * axis.y) * ref0.x));

    axisOut = axis;
}

// =============================================================================================================
// constraint data (0x010A3A70..0x010A3E70)
// =============================================================================================================
// Real layout (match/include/havok31/hkReflectedClasses.h + tools/pdb_type.py).
struct hkConstraintInfo
{
    int m_maxSizeOfJacobians;      // +0x00
    int m_sizeOfJacobians;         // +0x04
    int m_sizeOfSchemas;           // +0x08
    int m_numSolverResults;        // +0x0c
};

struct hkConstraintData;      // +0x2c/+0x30/+0x3c used by the mass changer and the base info size calc

// hkConstraintQueryIn (dev PDB: 0x48, hkConstraintQueryStepInfo + body/transform pointers).
class hkConstraintQueryIn
{ public:
    hkReal  m_substepDeltaTime;        // +0x00
    hkReal  m_substepInvDeltaTime;     // +0x04
    hkReal  m_frameDeltaTime;          // +0x08
    hkReal  m_frameInvDeltaTime;       // +0x0c
    hkReal  m_invNumSteps;             // +0x10
    hkReal  m_rhsFactor;               // +0x14
    hkReal  m_virtMassFactor;          // +0x18
    hkReal  m_frictionRhsFactor;       // +0x1c
    void*   m_accumulatorBufferRoot;   // +0x20
    void*   m_jacobianBufferRoot;      // +0x24
    void*   m_bodyA;                   // +0x28 hkVelocityAccumulator*
    void*   m_bodyB;                   // +0x2c hkVelocityAccumulator*
    void*   m_transformA;              // +0x30
    void*   m_transformB;              // +0x34
    hkReal  m_tau;                     // +0x38
    hkReal  m_damping;                 // +0x3c
    void*   m_constraintInstance;      // +0x40
    void*   m_constraintRuntime;       // +0x44
};

// hkConstraintQueryOut: the solver output. m_accumulatorBufferRoot/m_jacobianBufferRoot are the two
// pointers the init/jacobian helpers walk forward (0x010a76d0, 0x010acb50).
struct hkConstraintQueryOut
{
    void* m_accumulatorBufferRoot;     // +0x00
    void* m_jacobianBufferRoot;        // +0x04
};

struct hkSimpleConstraintInfoInitInput
{
    uint8_t  m_pad00[0x10];
    hkMatrix3 m_transform;             // +0x10 (scaled by the mass)
    hkReal    m_scale;                 // +0x40 (scaled by the mass)
};

struct hkBodyVelocity
{
    hkVector4 m_linearVelocity;        // +0x00
    hkVector4 m_angularVelocity;       // +0x10
    uint8_t   m_pad20[0x20];
};

// hkConstraintData (dev PDB size 0xc: vptr + m_userData). The mass changer reuses the base's tail
// storage, so the shared tail fields live in the base class and the derived class only adds virtuals.
struct hkConstraintInstance;

class hkConstraintData
{
public:
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4();
    virtual void getConstraintInfo(hkConstraintInfo& info) const;      // 0x010a3e70 (base impl)
    virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9();
    virtual void c10(); virtual void c11(); virtual void c12();
    uint32_t m_pad04;
    uint32_t m_userData;               // +0x08
    uint8_t  m_pad0c[0x2c - 0x0c];
    hkReal   m_minLinearMass;          // +0x2c (hkMassChangerConstraintData)
    hkReal   m_maxLinearMass;          // +0x30
    uint8_t  m_pad34[0x3c - 0x34];
    int      m_numSolverElemTemps;     // +0x3c

    void addInstance(hkConstraintInstance* instance, void* runtime, int sizeOfRuntime) const;   // 0x010a3a70
};

// hkMassChangerConstraintData: adds no data of its own, overrides the three constraint callbacks.
class hkMassChangerConstraintData : public hkConstraintData
{
public:
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4();
    virtual void getConstraintInfo(hkConstraintInfo& info) const;      // 0x010a3c10
    virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9();
    virtual void c10(); virtual void c11(); virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);
    virtual void toiCollisionResponseBeginCallback(const void* cp, hkSimpleConstraintInfoInitInput& bodyA,
            hkSimpleConstraintInfoInitInput& bodyB, hkBodyVelocity& velA, hkBodyVelocity& velB);   // 0x010a3c40
};

struct hkConstraintRuntime
{
    int m_sizeOfExternalRuntime;       // +0x00
    int m_numSolverResults;            // +0x04
};

// hkSimpleContactConstraintData: only the runtime-info callback matters here.
class hkSimpleContactConstraintData
{
public:
    virtual void getRuntimeInfo(hkBool wantRuntime, hkConstraintRuntime& info) const;   // 0x010a3e30
};

// hkConstraintData::addInstance -- clears one instance's runtime scratch.
// @ 0x010a3a70
void hkConstraintData::addInstance(hkConstraintInstance* /*instance*/, void* runtime, int sizeOfRuntime) const
{
    if (runtime != 0)
        memset(runtime, 0, sizeOfRuntime);
}

// @ 0x010a3e70
void hkConstraintData::getConstraintInfo(hkConstraintInfo& info) const
{
    info.m_maxSizeOfJacobians = 0;
    info.m_sizeOfJacobians = 0;
    info.m_numSolverResults = 0;
    info.m_sizeOfSchemas = 0x18;

    const int n = m_numSolverElemTemps;
    const int n30 = n * 0x30;
    info.m_maxSizeOfJacobians = n30 + 0x80;
    info.m_sizeOfJacobians = (n + 2) * 0x30;
    info.m_sizeOfSchemas = n * 4 + 0x30;
    info.m_numSolverResults = n + 2;
    if (n >= 2)
    {
        info.m_sizeOfJacobians += 0x20;
        info.m_sizeOfSchemas += 4;
        info.m_numSolverResults += 1;
    }
}

// hkMassChangerConstraintData::getConstraintInfo -- delegate to the base, then add the class's own scratch.
// @ 0x010a3c10
void hkMassChangerConstraintData::getConstraintInfo(hkConstraintInfo& info) const
{
    hkConstraintData::getConstraintInfo(info);
    const hkConstraintInfo& src = info;
    const int sizeOfSchemas = src.m_sizeOfSchemas + 0x20;
    const int sizeOfJacobians = src.m_sizeOfJacobians + 0x40;
    hkConstraintInfo& dst = info;
    dst.m_sizeOfSchemas = sizeOfSchemas;
    dst.m_sizeOfJacobians = sizeOfJacobians;
}

// hkMassChangerConstraintData::toiCollisionResponseBeginCallback -- scale each body's transform by its mass.
// @ 0x010a3c40
void hkMassChangerConstraintData::toiCollisionResponseBeginCallback(const void* /*cp*/,
        hkSimpleConstraintInfoInitInput& bodyA, hkSimpleConstraintInfoInitInput& bodyB,
        hkBodyVelocity& /*velA*/, hkBodyVelocity& /*velB*/)
{
    const hkReal minMass = m_minLinearMass;
    const hkReal maxMass = m_maxLinearMass;
    bodyA.m_scale = minMass * bodyA.m_scale;
    bodyA.m_transform.mul(minMass);
    bodyB.m_scale = maxMass * bodyB.m_scale;
    bodyB.m_transform.mul(maxMass);
}

// hkConstraintQueryOut / Jacobian buffer helpers (interface headers: hkConstraintQueryStepInfo.inl).
void hkInitQueryOut(hkConstraintQueryIn& in, int sizeOfExternalRuntime, int numSolverResults,
        hkConstraintQueryOut& out);                                              // 0x010a76d0
void hkSetInvMassBuildJacobian(const hkVector4& invMassA, const hkVector4& invMassB,
        hkConstraintQueryIn& in, hkConstraintQueryOut& out);                     // 0x010acb50
void hkSimpleContactConstraintData_buildJacobian(void* self, const hkConstraintQueryIn& in,
        hkConstraintQueryOut& out);                                              // 0x010a3ed0

// hkMassChangerConstraintData::buildJacobian -- scale both bodies' accumulator velocities by their mass,
// build the jacobians from the scaled copies, and then rebuild them from the unscaled copies.
// @ 0x010a3c90
void hkMassChangerConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
    hkInitQueryOut(const_cast<hkConstraintQueryIn&>(in), 0, 0, out);

    // +0x30 of each velocity accumulator is the 4-float linear-velocity block scaled here.
    hkVector4* velA = (hkVector4*)((char*)in.m_bodyA + 0x30);
    hkVector4* velB = (hkVector4*)((char*)in.m_bodyB + 0x30);

    const hkVector4 savedA = *velA;
    const hkVector4 savedB = *velB;

    hkVector4 scaledA;
    scaledA.x = savedA.x * m_minLinearMass;
    scaledA.y = savedA.y * m_minLinearMass;
    scaledA.z = savedA.z * m_minLinearMass;
    scaledA.w = savedA.w * m_minLinearMass;
    hkVector4 scaledB;
    scaledB.x = savedB.x * m_maxLinearMass;
    scaledB.y = savedB.y * m_maxLinearMass;
    scaledB.z = savedB.z * m_maxLinearMass;
    scaledB.w = savedB.w * m_maxLinearMass;

    velA->x = savedA.x * m_minLinearMass;
    velA->y = savedA.y * m_minLinearMass;
    velA->z = savedA.z * m_minLinearMass;
    velA->w = savedA.w * m_minLinearMass;
    velB->x = savedB.x * m_maxLinearMass;
    velB->y = savedB.y * m_maxLinearMass;
    velB->z = savedB.z * m_maxLinearMass;
    velB->w = savedB.w * m_maxLinearMass;

    hkSetInvMassBuildJacobian(scaledA, scaledB, const_cast<hkConstraintQueryIn&>(in), out);
    hkSimpleContactConstraintData_buildJacobian(this, in, out);

    *velA = savedA;
    *velB = savedB;
    hkSetInvMassBuildJacobian(savedA, savedB, const_cast<hkConstraintQueryIn&>(in), out);
}

// hkSimpleContactConstraintData::getRuntimeInfo -- no external runtime, no solver results.
// @ 0x010a3e30
void hkSimpleContactConstraintData::getRuntimeInfo(hkBool /*wantRuntime*/, hkConstraintRuntime& info) const
{
    info.m_sizeOfExternalRuntime = 0;
    info.m_numSolverResults = 0;
}
