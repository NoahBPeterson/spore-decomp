// Slice s0109d9c0 -- hkMultiThreadedSimulation::masterThreadFunc (0x0109d9c0, 2073 bytes), Havok 3.1.0.
//
// __thiscall, ret 0xc: (hkWorld* world, hkReal frameDeltaTime, hkReal physicsDeltaTime).  This is the
// top-level "step" of the multi-threaded continuous simulation, the 3.1 counterpart of
// hkContinuousSimulation::stepDeltaTime.  For every physics step (psi) that fits into the frame it
//   - advances world time, builds the hkStepInfo and copies it into the world / collision input,
//   - runs the maintenance manager and cleans dirty islands, puts the island with the largest
//     jacobian size first (that one is integrated first),
//   - recomputes the solver info (delta time, gravity per step / sub step),
//   - applies the actions on this thread if the world asks for it, queues the first integrate job,
//     leaves the job queue critical section, runs processJobs() on the master thread, re-enters,
//   - then handles the broad phase pairs that were collected: removeDuplicates, add agents (and
//     collide them immediately via processAgentEntry), remove agents,
//   - executes pending world operations and handles TOIs (continuous simulation).
// After the last psi it fires the post-simulation callbacks.  All parts are wrapped in Havok
// monitor-stream timer macros.
//
// Flags: /O2 /MD /Gy /TP /GS- (no /EHsc; locals are POD).  See nonmatching.txt.
#include "types.h"

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long index, void* value);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);

typedef float hkReal;
typedef uint32_t hkUint32;
typedef uint16_t hkUint16;
typedef uint8_t hkUint8;

#define HK_REAL_MAX 3.40282e+38f

// ---- monitor stream timers (TLS 0x016e42a4 = write pointer, 0x016e42a8 = end) ----------------------
extern volatile unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern volatile unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorEndListTag[];            // 0x0143cd94
extern const char hkMonitorEndTag[];                // 0x0149cc34

#define HK_TIMER_SET_TIME(field) { hkUint32 ticks_; __asm { rdtsc } __asm { mov ticks_, eax } field = ticks_; }

struct hkMonitorCommand { const char* m_commandAndMonitor; hkUint32 m_time0; hkUint32 m_time1; };
struct hkMonitorListCommand { const char* m_commandAndMonitor; hkUint32 m_time0; hkUint32 m_time1; const char* m_nameOfFirstSplit; };

#define HK_TIMER_COMMAND(name) do { \
    void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
        hkMonitorCommand* c_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_commandAndMonitor = name; \
        HK_TIMER_SET_TIME(c_->m_time0) \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_BEGIN_LIST(name, first) do { \
    void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
        hkMonitorListCommand* c_ = (hkMonitorListCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_commandAndMonitor = "Lt" name; \
        c_->m_nameOfFirstSplit = first; \
        HK_TIMER_SET_TIME(c_->m_time0) \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_BEGIN(name) HK_TIMER_COMMAND("Tt" name)
#define HK_TIMER_SPLIT_LIST(name) HK_TIMER_COMMAND("St" name)
#define HK_TIMER_END_LIST() HK_TIMER_COMMAND(hkMonitorEndListTag)
#define HK_TIMER_END() HK_TIMER_COMMAND(hkMonitorEndTag)

// ---- containers / math -----------------------------------------------------------------------------
template <class T>
struct hkArray {
    T* m_data;
    int m_size;
    int m_capacityAndFlags;
    int getSize() const { return m_size; }
    T& operator[](int i) { return m_data[i]; }
};

struct __declspec(align(16)) hkVector4 { hkReal x, y, z, w; };

struct hkStepInfo {
    hkReal m_startTime, m_endTime, m_deltaTime, m_invDeltaTime;
    hkStepInfo() {}
    __forceinline hkStepInfo(hkReal startTime, hkReal endTime)
    {
        m_startTime = startTime;
        m_endTime = endTime;
        m_deltaTime = endTime - startTime;
        m_invDeltaTime = (m_deltaTime == 0.0f) ? 0.0f : 1.0f / m_deltaTime;
    }
};

struct hkSolverInfo {                                              // size 0x140
    hkReal m_one, m_tau, m_damping, m_frictionTau;
    hkVector4 m_globalAccelerationPerSubStep;                      // +0x10
    hkVector4 m_globalAccelerationPerStep;                         // +0x20
    hkUint8 pad30[0x124 - 0x30];
    hkReal m_deltaTime;                                            // +0x124
    hkReal m_invDeltaTime;                                         // +0x128
    int m_numSteps;                                                // +0x12c
    hkReal m_invNumSteps;                                          // +0x130
    hkUint8 pad134[0x140 - 0x134];
};
struct hkWorldDynamicsStepInfo {
    hkStepInfo m_stepInfo;                                         // +0x00
    hkSolverInfo m_solverInfo;                                     // +0x10
};

// ---- world objects -----------------------------------------------------------------------------------
class hkAction {
public:
    virtual void pv00();
    virtual void pv04();
    virtual void applyAction(const hkStepInfo& stepInfo);          // 0x08
};

struct hkSimulationIsland {
    hkUint8 pad00[0x0c];
    int m_sumSizeOfJacobians;                                      // +0x0c
    hkUint8 pad10[0x20 - 0x10];
    hkUint16 m_storageIndex;                                       // +0x20
    hkUint8 pad22[0x64 - 0x22];
    hkArray<hkAction*> m_actions;                                  // +0x64
};

struct hkTypedBroadPhaseHandle {                                   // size 0xc
    hkUint32 m_id;
    char m_type;                                                   // +0x04
    char m_ownerOffset;                                            // +0x05
    hkUint16 m_objectQualityType;                                  // +0x06
    hkUint32 m_collisionFilterInfo;                                // +0x08
};
struct hkCollidable {                                              // size 0x24
    hkUint8 pad00[0x14];
    hkTypedBroadPhaseHandle m_broadPhaseHandle;                    // +0x14
    hkReal m_allowedPenetrationDepth;                              // +0x20
};
struct hkBroadPhaseHandlePair { hkTypedBroadPhaseHandle* m_a; hkTypedBroadPhaseHandle* m_b; };

struct hkCollisionQualityInfo { hkUint8 pad00[0x10]; hkUint8 m_createPredictiveAgents; hkUint8 pad11[0x3c - 0x11]; };
struct hkCollisionDispatcher {
    hkUint8 pad00[0x19d4];
    char m_collisionQualityTable[8][8];                            // +0x19d4
    hkCollisionQualityInfo m_collisionQualityInfo[8];              // +0x1a14
};
struct hkProcessCollisionInput {
    hkCollisionDispatcher* m_dispatcher;                           // +0x00
    hkUint8 pad04[0x0c - 0x04];
    hkUint8 m_createPredictiveAgents;                              // +0x0c
    hkUint8 pad0d[0x10 - 0x0d];
    hkStepInfo m_stepInfo;                                         // +0x10
    hkUint8 pad20[0x2c - 0x20];
};
struct __declspec(align(16)) hkProcessCollisionOutput {
    hkUint32 pad0000[0x3034 / 4];
    hkReal m_toi;                                                  // +0x3034
    hkUint32 pad3038[(0x3050 - 0x3038) / 4];
    __forceinline hkProcessCollisionOutput() { m_toi = HK_REAL_MAX; }
};
struct hkAgentNnEntry;

struct hkWorldMaintenanceMgr {
    virtual void pv00();
    virtual void pv04();
    virtual void pv08();
    virtual void performMaintenance(class hkWorld* world, const hkStepInfo& stepInfo);   // 0x0c
};
struct hkWorldOperationQueue {
    hkUint8 pad00[0x1c];
    hkUint8 m_flag1c;                                              // +0x1c
    hkUint8 pad1d[0x2c - 0x1d];
};

class hkWorld {
public:
    hkUint8 pad00[0x0c];
    hkReal m_currentTime;                                          // +0x0c
    hkReal m_timeOfNextFrame;                                      // +0x10
    hkReal m_timeOfLastPsi;                                        // +0x14
    hkReal m_timeOfNextPsi;                                        // +0x18
    hkUint8 pad1c[0x20 - 0x1c];
    hkVector4 m_gravity;                                           // +0x20
    hkUint8 pad30[0x38 - 0x30];
    hkArray<hkSimulationIsland*> m_activeSimulationIslands;        // +0x38
    hkUint8 pad44[0x5c - 0x44];
    hkWorldMaintenanceMgr* m_maintenanceMgr;                       // +0x5c
    hkUint8 pad60[0x78 - 0x60];
    hkProcessCollisionInput* m_collisionInput;                     // +0x78
    hkUint8 pad7c[0x84 - 0x7c];
    hkWorldOperationQueue* m_pendingOperations;                    // +0x84
    int m_pendingOperationsCount;                                  // +0x88
    int m_lockCount;                                               // +0x8c
    int m_lockCountForPhantoms;                                    // +0x90
    hkUint8 m_blockExecutingPendingOperations;                     // +0x94
    hkUint8 pad95[0xa8 - 0x95];
    hkUint8 m_processActionsInSingleThread;                        // +0xa8
    hkUint8 pada9[0x120 - 0xa9];
    hkArray<void*> m_worldPostSimulationListeners;                 // +0x120
    hkUint8 pad12c[0x170 - 0x12c];
    hkWorldDynamicsStepInfo m_dynamicsStepInfo;                    // +0x170

    void executePendingOperations();                               // 0x01082bf0
};

struct hkWorldOperationUtil { static void cleanupDirtyIslands(hkWorld* world); };                  // 0x010a07c0
struct hkWorldCallbackUtil { static void firePostSimulationCallback(hkWorld* world, const hkStepInfo& s); };   // 0x0109f5a0
struct hkTypedBroadPhaseDispatcher {
    static void removeDuplicates(hkArray<hkBroadPhaseHandlePair>& newPairs, hkArray<hkBroadPhaseHandlePair>& delPairs);   // 0x010cc560
};
hkAgentNnEntry* hkWorldAgentUtil_addAgent(hkCollidable* a, hkCollidable* b, hkProcessCollisionInput* input);   // 0x010a3920 (cdecl)
hkAgentNnEntry* hkAgentNnMachine_findAgent(hkCollidable* a, hkCollidable* b);                                  // 0x010fbb30 (cdecl)
void hkWorldAgentUtil_removeAgent(hkAgentNnEntry* entry);                                                      // 0x010a39f0 (cdecl)
class hkMultiThreadedSimulation;
void processAgentEntry(hkAgentNnEntry* entry, hkProcessCollisionInput* input, hkProcessCollisionOutput& output,
                       hkMultiThreadedSimulation* simulation);                                                   // 0x0109c5e0 (cdecl)
void hkNoOp();                                                                                                 // 0x00c2e4e0 (just `ret`)

// ---- critical section / job queue -----------------------------------------------------------------
struct hkCriticalSection {                                         // 0x20
    hkUint8 m_section[0x18];
    int m_ownerLo;                                                 // +0x18
    int m_ownerHi;                                                 // +0x1c
    void enter();                                                  // 0x0107f820
    __forceinline void leave()
    {
        m_ownerLo = -1;
        m_ownerHi = -1;
        LeaveCriticalSection(this);
    }
};

struct hkJobQueueEntry {
    int m_jobType;                                                 // +0x00
    hkUint16 m_islandIndex;                                        // +0x04
    int m_numIslands;                                              // +0x08
};
class hkJobQueue {
public:
    hkCriticalSection m_criticalSection;                           // +0x00
    void setInitialNumSpuJobs(int n);                              // 0x010a5820
    void addJob(hkJobQueueEntry& job, int priority, int b);        // 0x010a5ba0
};

struct hkMtThreadStructure {                                       // size 0x60
    hkMtThreadStructure(hkWorld* world, class hkMultiThreadedSimulation* sim, int threadType);   // 0x0109c730
    hkUint32 pad[0x18];
};

class hkToiResourceMgr {
public:
    virtual void pv00();
    virtual void pv04();
    virtual void resetForStep();                                   // 0x08 (name coined)
};

class hkContinuousSimulation {
public:
    virtual void vslot0();
    hkUint32 m_refCount;                                           // +0x04
    hkReal m_physicsDeltaTime;                                     // +0x08
    hkUint8 m_synchronizeFrameAndPhysicsTime;                      // +0x0c
    hkUint8 pad0d[0x18 - 0x0d];
    hkArray<void*> m_toiEvents;                                    // +0x18
    hkToiResourceMgr* m_toiResourceMgr;                            // +0x24
    hkUint8 pad28[0x2c - 0x28];

    int handleAllToisTill(hkWorld* world, hkReal time);            // 0x010f0830
};

class hkMultiThreadedSimulation : public hkContinuousSimulation {
public:
    hkWorld* m_world;                                              // +0x2c
    hkUint8 pad30[0x54 - 0x30];
    hkUint8 m_isDuringStep;                                        // +0x54 (name coined)
    hkArray<hkBroadPhaseHandlePair> m_addedPairs;                  // +0x58
    hkUint8 pad64[0x88 - 0x64];
    hkArray<hkBroadPhaseHandlePair> m_removedPairs;                // +0x88
    hkUint8 pad94[0xc4 - 0x94];
    hkUint8 m_morePsiSteps;                                        // +0xc4 (name coined)
    hkUint8 padc5[0x100 - 0xc5];
    hkJobQueue m_jobQueue;                                         // +0x100

    void processJobs(hkMtThreadStructure& tl);                     // 0x0109cba0
    void masterThreadFunc(hkWorld* world, hkReal frameDeltaTime, hkReal physicsDeltaTime);
};

#include <math.h>
static __forceinline hkReal hkFabs(hkReal x) { return (hkReal)fabs(x); }

// @ 0x0109d9c0
void hkMultiThreadedSimulation::masterThreadFunc(hkWorld* world, hkReal frameDeltaTime, hkReal physicsDeltaTime)
{
    HK_TIMER_BEGIN("Simulate");

    m_physicsDeltaTime = physicsDeltaTime;
    if (m_synchronizeFrameAndPhysicsTime
        && hkFabs(world->m_timeOfNextFrame - world->m_timeOfNextPsi) < physicsDeltaTime * 0.01f
        && frameDeltaTime / physicsDeltaTime > 0.1f)
    {
        world->m_timeOfNextFrame = world->m_timeOfNextPsi;
    }
    world->m_timeOfNextFrame = frameDeltaTime + world->m_timeOfNextFrame;
    m_morePsiSteps = world->m_timeOfNextPsi < world->m_timeOfNextFrame;

    do
    {
        m_isDuringStep = true;
        world->m_lockCount++;
        world->m_pendingOperations->m_flag1c = true;

        if (m_morePsiSteps)
        {
            if (m_toiEvents.getSize() == 0)
            {
                m_toiResourceMgr->resetForStep();

                world->m_timeOfLastPsi = world->m_timeOfNextPsi;
                world->m_timeOfNextPsi = physicsDeltaTime + world->m_timeOfNextPsi;
                hkStepInfo stepInfo(world->m_timeOfLastPsi, world->m_timeOfNextPsi);

                world->m_currentTime = world->m_timeOfLastPsi;
                world->m_dynamicsStepInfo.m_stepInfo = stepInfo;
                world->m_collisionInput->m_stepInfo = stepInfo;

                world->m_maintenanceMgr->performMaintenance(world, stepInfo);
                hkWorldOperationUtil::cleanupDirtyIslands(world);
                hkNoOp();

                // the island with the largest jacobian size goes first
                if (world->m_activeSimulationIslands.getSize() > 0)
                {
                    int maxValue = 0;
                    int maxIndex = 0;
                    for (int i = 0; i < world->m_activeSimulationIslands.getSize(); i++)
                    {
                        int v = world->m_activeSimulationIslands[i]->m_sumSizeOfJacobians;
                        if (v > maxValue)
                        {
                            maxValue = v;
                            maxIndex = i;
                        }
                    }
                    hkSimulationIsland** islands = world->m_activeSimulationIslands.m_data;
                    hkSimulationIsland* first = islands[0];
                    hkSimulationIsland* largest = islands[maxIndex];
                    islands[0] = largest;
                    islands[maxIndex] = first;
                    world->m_activeSimulationIslands[0]->m_storageIndex = 0;
                    world->m_activeSimulationIslands[maxIndex]->m_storageIndex = (hkUint16)maxIndex;
                }

                // solver info for this step
                world->m_dynamicsStepInfo.m_stepInfo = stepInfo;
                hkSolverInfo& solver = world->m_dynamicsStepInfo.m_solverInfo;
                solver.m_deltaTime = stepInfo.m_deltaTime * solver.m_invNumSteps;
                solver.m_invDeltaTime = (hkReal)solver.m_numSteps * stepInfo.m_invDeltaTime;
                hkReal subStep = stepInfo.m_deltaTime * solver.m_invNumSteps;
                solver.m_globalAccelerationPerSubStep.x = subStep * world->m_gravity.x;
                solver.m_globalAccelerationPerSubStep.y = subStep * world->m_gravity.y;
                solver.m_globalAccelerationPerSubStep.z = subStep * world->m_gravity.z;
                solver.m_globalAccelerationPerSubStep.w = subStep * world->m_gravity.w;
                solver.m_globalAccelerationPerStep.x = stepInfo.m_deltaTime * world->m_gravity.x;
                solver.m_globalAccelerationPerStep.y = stepInfo.m_deltaTime * world->m_gravity.y;
                solver.m_globalAccelerationPerStep.z = stepInfo.m_deltaTime * world->m_gravity.z;
                solver.m_globalAccelerationPerStep.w = stepInfo.m_deltaTime * world->m_gravity.w;

                if (world->m_activeSimulationIslands.getSize() > 0)
                {
                    if (world->m_processActionsInSingleThread)
                    {
                        world->m_lockCountForPhantoms--;
                        for (int i = 0; i < world->m_activeSimulationIslands.getSize(); i++)
                        {
                            hkArray<hkAction*>& actions = world->m_activeSimulationIslands[i]->m_actions;
                            for (int j = 0; j < actions.getSize(); j++)
                                actions[j]->applyAction(world->m_dynamicsStepInfo.m_stepInfo);
                        }
                        world->m_lockCountForPhantoms++;
                    }
                    hkJobQueueEntry job;
                    job.m_jobType = 0;
                    job.m_islandIndex = 0;
                    job.m_numIslands = world->m_activeSimulationIslands.getSize();
                    m_jobQueue.setInitialNumSpuJobs(world->m_activeSimulationIslands.getSize());
                    m_jobQueue.addJob(job, 1, 1);
                }

                m_jobQueue.m_criticalSection.leave();
                hkMtThreadStructure tl(world, this, 0);
                processJobs(tl);
                m_morePsiSteps = world->m_timeOfNextPsi < world->m_timeOfNextFrame;
                m_jobQueue.m_criticalSection.enter();
            }
        }
        if (!m_morePsiSteps)
            m_jobQueue.m_criticalSection.leave();

        if (m_removedPairs.getSize() + m_addedPairs.getSize() != 0)
        {
            HK_TIMER_BEGIN_LIST("InterIsland", "duplicates");
            hkTypedBroadPhaseDispatcher::removeDuplicates(m_addedPairs, m_removedPairs);

            HK_TIMER_SPLIT_LIST("addAgt");
            hkProcessCollisionOutput output;
            for (int i = 0; i < m_addedPairs.getSize(); i++)
            {
                hkTypedBroadPhaseHandle* ha = m_addedPairs[i].m_a;
                hkCollidable* collA = (hkCollidable*)((char*)ha + ha->m_ownerOffset);
                hkTypedBroadPhaseHandle* hb = m_addedPairs[i].m_b;
                hkCollidable* collB = (hkCollidable*)((char*)hb + hb->m_ownerOffset);
                hkProcessCollisionInput* input = m_world->m_collisionInput;
                hkCollisionDispatcher* dispatcher = input->m_dispatcher;
                int quality = dispatcher->m_collisionQualityTable[collA->m_broadPhaseHandle.m_objectQualityType]
                                                                 [collB->m_broadPhaseHandle.m_objectQualityType];
                if (quality != 0)
                {
                    input->m_createPredictiveAgents = dispatcher->m_collisionQualityInfo[quality].m_createPredictiveAgents;
                    hkAgentNnEntry* entry = hkWorldAgentUtil_addAgent(collA, collB, input);
                    if (entry)
                        processAgentEntry(entry, m_world->m_collisionInput, output, this);
                }
            }
            m_addedPairs.m_size = 0;

            HK_TIMER_SPLIT_LIST("removeAgt");
            for (int i = 0; i < m_removedPairs.getSize(); i++)
            {
                hkTypedBroadPhaseHandle* ha = m_removedPairs[i].m_a;
                hkTypedBroadPhaseHandle* hb = m_removedPairs[i].m_b;
                hkAgentNnEntry* entry = hkAgentNnMachine_findAgent((hkCollidable*)((char*)ha + ha->m_ownerOffset),
                                                                   (hkCollidable*)((char*)hb + hb->m_ownerOffset));
                if (entry)
                    hkWorldAgentUtil_removeAgent(entry);
            }
            m_removedPairs.m_size = 0;
            HK_TIMER_END_LIST();
        }

        m_isDuringStep = false;
        world->m_pendingOperations->m_flag1c = false;
        if (--world->m_lockCount == 0 && world->m_pendingOperationsCount != 0
            && !world->m_blockExecutingPendingOperations)
        {
            world->executePendingOperations();
        }

        if (m_toiEvents.getSize() != 0)
        {
            hkReal t = world->m_timeOfNextFrame;
            hkReal psi = world->m_timeOfNextPsi;
            if (psi < t)
                t = psi;
            handleAllToisTill(world, t);
        }
    } while (m_morePsiSteps);

    world->m_currentTime = world->m_timeOfNextFrame;
    HK_TIMER_END();

    if (world->m_worldPostSimulationListeners.getSize() != 0)
    {
        HK_TIMER_BEGIN("PostSimulateCb");
        hkStepInfo stepInfo(world->m_timeOfLastPsi, world->m_timeOfNextPsi);
        hkWorldCallbackUtil::firePostSimulationCallback(world, stepInfo);
        HK_TIMER_END();
    }
}
