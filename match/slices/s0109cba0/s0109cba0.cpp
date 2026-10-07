// Slice s0109cba0 -- hkMultiThreadedSimulation job loop (0x0109cba0, 3604 bytes), Havok 3.1.0.
// Flags: /O2 /MD /Gy /TP /GS- (no /EHsc: the hkInplaceArray locals have no EH frame).
//
// __thiscall with `ret 4`: this = hkMultiThreadedSimulation (m_jobQueue at +0x100), the argument is
// the thread's hkMtThreadStructure (ctor at 0x0109c730: m_world, m_simulation, m_threadType,
// m_collisionInput copy at +0x0c, m_constraintQueryIn at +0x38).  The function sits between
// ~hkMultiThreadedSimulation (0x0109cab0) and masterThreadFunc (0x0109d9c0); its real name is not in
// symbols/havok_names.txt, so it is called processJobs here.
//
// It takes jobs from the job queue until the queue reports that no job is left, and runs:
//   0 integrate:      apply the island's actions, then integrate a constraint-free island directly,
//                     solve it on this thread, or (multi-CPU) lay out the solver buffer and split it
//                     into a build-accumulators job and build-jacobian tasks;
//   1 build accumulators, 3 build jacobians, 4 solve, 5 write back + integrate + free the tasks,
//   6 broad phase (then split into narrow-phase jobs), 7 narrow phase over agent sectors.
// Each step is wrapped in the Havok monitor-stream timer macros.
#include "types.h"

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long index, void* value);

typedef float hkReal;
typedef uint32_t hkUint32;
typedef uint16_t hkUint16;
typedef uint8_t hkUint8;

#define HK_REAL_MAX 3.40282e+38f

enum {
    HK_MEMORY_CLASS_ARRAY = 0x14,
    HK_MEMORY_CLASS_CONSTRAINT_SOLVER = 0x29,
};

// ---- monitor stream timers (TLS 0x016e42a4 = write pointer, 0x016e42a8 = end) ----------------------
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorEndListTag[];            // 0x0143cd94 "lt"
extern const char hkMonitorEndTag[];                // 0x0149cc34 "Et"

// hkMonitorStream reads the time stamp counter with an inline-asm helper (rdtsc into a local).
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

// ---- memory --------------------------------------------------------------------------------------
class hkMemory {
public:
    virtual void pv00();
    virtual void pv04();
    virtual void pv08();
    virtual void pv0c();
    virtual void* allocate(int nbytes, int cl);                    // 0x10
    virtual void deallocate(void* p, int nbytes, int cl);          // 0x14
    virtual void* allocateRow(int row, int cl);                    // 0x18
    virtual void deallocateRow(void* p, int row, int cl);          // 0x1c
    static hkMemory* s_instance;                                   // 0x016e4178
    __forceinline static hkMemory& getInstance() { return *s_instance; }
};

extern unsigned long g_hkThreadMemoryTls;                          // 0x016e4174
class hkThreadMemory {
public:
    hkUint8 pad00[0x34];
    int m_maxNumElemsOnFreeList;                                   // 0x34
    void* m_freeListHead[17];                                      // 0x38
    int m_freeListCount[17];                                       // 0x7c

    void deallocateChunk(void* p, int nbytes, int cl);             // 0x0107db10
    __forceinline static hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls); }

    // constant-size row allocation (inlined)
    __forceinline void* allocateRow(int row, int cl)
    {
        void* p = m_freeListHead[row];
        if (p)
        {
            m_freeListCount[row]--;
            m_freeListHead[row] = *(void**)p;
            return p;
        }
        return hkMemory::getInstance().allocateRow(row, cl);
    }
    __forceinline void deallocateRow(void* p, int row, int cl)
    {
        if (m_freeListCount[row] < m_maxNumElemsOnFreeList)
        {
            m_freeListCount[row]++;
            *(void**)p = m_freeListHead[row];
            m_freeListHead[row] = p;
        }
        else
            hkMemory::getInstance().deallocateRow(p, row, cl);
    }
};

struct hkArrayUtil {
    static void _reserveMore(void* array, int elemSize);           // 0x0107f530
};

template <class T>
struct hkArray {
    T* m_data;
    int m_size;
    int m_capacityAndFlags;
    enum { CAPACITY_MASK = 0x3fffffff, DONT_DEALLOCATE_FLAG = 0x80000000 };
    int getSize() const { return m_size; }
    int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
    T& operator[](int i) { return m_data[i]; }
    __forceinline void pushBack(const T& e)
    {
        if (m_size == getCapacity())
            hkArrayUtil::_reserveMore(this, sizeof(T));
        m_data[m_size] = e;
        m_size++;
    }
    __forceinline ~hkArray()
    {
        if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
            hkThreadMemory::getInstance().deallocateChunk(m_data, getCapacity() * sizeof(T), HK_MEMORY_CLASS_ARRAY);
    }
};
template <class T, int N>
struct hkInplaceArray : hkArray<T> {
    T m_storage[N];
    __forceinline hkInplaceArray()
    {
        this->m_data = m_storage;
        this->m_size = 0;
        this->m_capacityAndFlags = N | hkArray<T>::DONT_DEALLOCATE_FLAG;
    }
};

// ---- dynamics ------------------------------------------------------------------------------------
struct __declspec(align(16)) hkVector4 { hkReal x, y, z, w; };
struct hkStepInfo { hkReal m_startTime, m_endTime, m_deltaTime, m_invDeltaTime; };
struct hkSolverInfo {
    hkReal m_one, m_tau, m_damping, m_frictionTau;
    hkVector4 m_globalAccelerationPerSubStep;                      // +0x10
    hkVector4 m_globalAccelerationPerStep;                         // +0x20
    hkUint8 pad30[0x140 - 0x30];
};
struct hkWorldDynamicsStepInfo {
    hkStepInfo m_stepInfo;                                         // +0x00
    hkSolverInfo m_solverInfo;                                     // +0x10
};

class hkAction {
public:
    virtual void pv00();
    virtual void pv04();
    virtual void applyAction(const hkStepInfo& stepInfo);          // 0x08
};

class hkMotion {
public:
    virtual void pv00();
    virtual void pv04();
    virtual void pv08();
    virtual void pv0c();
    virtual void integrate(const hkStepInfo& stepInfo, const hkVector4& gravityStep);   // 0x10
};

struct hkConstraintInternal {                                      // size 0x1c
    hkUint8 pad00[0x10];
    hkUint8 m_priority;                                            // +0x10
    hkUint8 pad11[0x1c - 0x11];
};

struct hkEntity {
    hkUint8 pad00[0x58];
    hkMotion* m_motion;                                            // +0x58
    hkUint8 pad5c[0x70 - 0x5c];
    hkConstraintInternal* m_constraintsMaster;                     // +0x70
    int m_numConstraintsMaster;                                    // +0x74
};

struct hkAgentNnEntry { hkUint8 m_type, m_nn, m_streamCommand, m_size; };   // m_size at +3
struct hkAgentNnTrack {
    hkUint8** m_sectors;                                           // +0x00 (hkInplaceArray<hkAgentNnSector*,1>)
    int m_numSectors;                                              // +0x04
    int m_sectorsCapacity;
    hkUint8* m_sectorsStorage;
    hkUint32 m_bytesUsedInLastSector;                              // +0x10
    hkUint16 m_agentSize;                                          // +0x14
    hkUint16 m_sectorSize;                                         // +0x16
};

struct hkSimulationIsland {
    hkUint8 pad00[0x0c];
    int m_sumSizeOfJacobians;                                      // +0x0c
    hkUint8 pad10[0x3c - 0x10];
    hkEntity** m_entities;                                         // +0x3c (hkInplaceArray<hkEntity*,1>)
    int m_numEntities;                                             // +0x40
    hkUint8 pad44[0x4c - 0x44];
    hkAgentNnTrack m_agentTrack;                                   // +0x4c
    hkAction** m_actions;                                          // +0x64
    int m_numActions;                                              // +0x68
};

struct hkWorld {
    hkUint8 pad00[0x38];
    hkSimulationIsland** m_activeSimulationIslands;                // +0x38
    hkUint8 pad3c[0xa8 - 0x3c];
    bool m_processActionsInSingleThread;                           // +0xa8
    hkUint8 pada9[0x170 - 0xa9];
    hkWorldDynamicsStepInfo m_dynamicsStepInfo;                    // +0x170
};

struct hkProcessCollisionInput { hkUint8 pad[0x10]; hkStepInfo m_stepInfo; hkUint8 pad20[0xc]; };   // size 0x2c
struct hkConstraintQueryIn { hkUint8 pad[0x20]; };

struct __declspec(align(16)) hkProcessCollisionOutput {
    hkUint8 pad0000[0x3034];
    hkReal m_toi;                                                  // +0x3034
    hkUint8 pad3038[0x3050 - 0x3038];
    __forceinline hkProcessCollisionOutput() { m_toi = HK_REAL_MAX; }
};

// Solver buffer header shared by the integrate jobs of one island (row 3, 32 bytes).
struct hkBuildJacobianTask;
struct hkBuildJacobianTaskHeader {
    void* m_buffer;                                                // +0x00
    int m_bufferSize;                                              // +0x04
    void* m_accumulators;                                          // +0x08
    void* m_jacobians;                                             // +0x0c
    void* m_schemas;                                               // +0x10
    void* m_solverTemps;                                           // +0x14
    int m_openJobs;                                                // +0x18
    hkBuildJacobianTask* m_tasks;                                  // +0x1c

    __forceinline hkBuildJacobianTaskHeader()
    {
        m_buffer = 0; m_bufferSize = 0; m_accumulators = 0; m_jacobians = 0;
        m_schemas = 0; m_solverTemps = 0; m_openJobs = 0; m_tasks = 0;
    }
    __forceinline void* operator new(size_t) { return hkThreadMemory::getInstance().allocateRow(3, HK_MEMORY_CLASS_CONSTRAINT_SOLVER); }
    __forceinline void operator delete(void* p) { hkThreadMemory::getInstance().deallocateRow(p, 3, HK_MEMORY_CLASS_CONSTRAINT_SOLVER); }
};

// One build-jacobian task (row 13).
struct hkBuildJacobianTask {
    hkBuildJacobianTask* m_next;                                   // +0x00
    hkBuildJacobianTaskHeader* m_taskHeader;                       // +0x04
    void* m_jacobians;                                             // +0x08
    void* m_schemas;                                               // +0x0c
    void* m_solverTemps;                                           // +0x10
    hkInplaceArray<hkConstraintInternal*, 0xf0> m_constraints;     // +0x14

    __forceinline ~hkBuildJacobianTask() {}

    __forceinline void* operator new(size_t) { return hkThreadMemory::getInstance().allocateRow(13, HK_MEMORY_CLASS_CONSTRAINT_SOLVER); }
    __forceinline void operator delete(void* p) { hkThreadMemory::getInstance().deallocateRow(p, 13, HK_MEMORY_CLASS_CONSTRAINT_SOLVER); }
};

struct hkConstraintSolverSetup {
    static int calcBufferSize(hkSimulationIsland* island, int minSize);                       // 0x010a4b30
    static void layoutBuffer(hkSimulationIsland* island, void* buffer, int bufferSize,
                             hkBuildJacobianTaskHeader* taskHeader);                         // 0x010a4a70
    static void buildAccumulatorBatch(const hkStepInfo& info, hkEntity** entities, int first, int end,
                                      void* accumulators);                                   // 0x010a4b50
    static void buildJacobianElementBatch(hkConstraintQueryIn& in, hkConstraintInternal** constraints,
                                          int numConstraints, void* accumulators, void* schemas,
                                          void* jacobians, void* nextSchemas);               // 0x010a4bb0
    static void solveSingleThreaded(const hkStepInfo& stepInfo, const hkSolverInfo& solverInfo,
                                    hkConstraintQueryIn& in, hkSimulationIsland* island,
                                    hkEntity** entities, int numEntities);                   // 0x010a5070
    static void integrateBatch(const hkWorldDynamicsStepInfo& info, hkEntity** entities, int numEntities,
                               void* accumulators);                                          // 0x010a4c60
};
void hkSolveConstraints(const hkSolverInfo& info, void* schemas, void* accumulators, void* jacobians,
                        void* solverTemps);                                                  // 0x010b8b30
void hkExportImpulsesAndRhs(const hkSolverInfo& info, void* schemas, void* accumulators, void* jacobians,
                            void* solverTemps);                                              // 0x010bd5e0

class hkMultiThreadedSimulation;
void processAgentEntry(hkAgentNnEntry* entry, const hkProcessCollisionInput& input,
                       hkProcessCollisionOutput& output, hkMultiThreadedSimulation* simulation);   // 0x0109c5e0

class hkContinuousSimulation {
public:
    void collideEntitiesBroadPhaseContinuous(hkEntity** entities, int numEntities, hkWorld* world,
                                             void* criticalSection);                         // 0x010f1df0
};

// ---- job queue -----------------------------------------------------------------------------------
struct hkJobQueueEntry {
    int m_jobType;                                                 // +0x00
    hkUint16 m_islandIndex;                                        // +0x04
    hkUint16 m_pad06;
    union {
        struct { hkBuildJacobianTaskHeader* m_taskHeader; hkUint16 m_firstEntity; hkUint16 m_numEntities; } m_accum;
        struct { hkBuildJacobianTask* m_task; } m_jac;
        struct {
            char* m_buffer;                                        // +0x08
            int m_pad0c;
            int m_accumulatorsOffset;                              // +0x10
            int m_jacobiansOffset;                                 // +0x14
            int m_schemasOffset;                                   // +0x18
            int m_solverTempsOffset;                               // +0x1c
            int m_numSolverResults;                                // +0x20
            hkBuildJacobianTaskHeader* m_taskHeader;               // +0x24
        } m_solve;
        struct { int m_sectorIndex; int m_numSectors; } m_narrowPhase;
    };
};

class hkJobQueue {
public:
    int getNextJob(int threadType, hkJobQueueEntry& job, int wait);                           // 0x010a6620
    int finishJobAndGetNextJob(int threadType, const hkJobQueueEntry& oldJob, hkJobQueueEntry& jobOut,
                               void* threadData, int wait);                                  // 0x010a5c20
    void finishAddAndGetNextJob(int a, int b, int threadType, hkJobQueueEntry& job, int wait);   // 0x010a6110
    void addJob(hkJobQueueEntry& job, int priority, int b);                                  // 0x010a5ba0
};

struct hkMtThreadStructure {
    hkWorld* m_world;                                              // +0x00
    hkMultiThreadedSimulation* m_simulation;                       // +0x04
    int m_threadType;                                              // +0x08
    hkProcessCollisionInput m_collisionInput;                      // +0x0c
    hkConstraintQueryIn m_constraintQueryIn;                       // +0x38
};

class hkMultiThreadedSimulation : public hkContinuousSimulation {
public:
    hkUint8 pad000[0xbc];
    bool m_multiCpuSolver;                                         // +0xbc
    hkUint8 pad0bd[0x100 - 0xbd];
    hkJobQueue m_jobQueue;                                         // +0x100
    hkUint8 pad101[0x1c0 - 0x101];
    hkUint8 m_broadPhaseCriticalSection[4];                        // +0x1c0

    void processJobs(hkMtThreadStructure& tl);
};

// @ 0x0109cba0
void hkMultiThreadedSimulation::processJobs(hkMtThreadStructure& tl)
{
    hkJobQueueEntry job;
    if (m_jobQueue.getNextJob(tl.m_threadType, job, 0) != 0)
        return;
    for (;;)
    {
        switch (job.m_jobType)
        {
        case 0:
        {
            HK_TIMER_BEGIN_LIST("Integrate", "Actions");
            hkWorld* world = tl.m_world;
            hkSimulationIsland* island = world->m_activeSimulationIslands[job.m_islandIndex];
            hkWorldDynamicsStepInfo& stepInfo = world->m_dynamicsStepInfo;
            if (!world->m_processActionsInSingleThread)
            {
                for (int i = 0; i < island->m_numActions; i++)
                {
                    hkAction* action = island->m_actions[i];
                    if (action)
                        action->applyAction(stepInfo.m_stepInfo);
                }
            }
            hkEntity** entities = island->m_entities;
            int numEntities = island->m_numEntities;
            if (island->m_sumSizeOfJacobians == 0)
            {
                HK_TIMER_SPLIT_LIST("SingleObj");
                for (int i = island->m_numEntities - 1; i >= 0; i--)
                    island->m_entities[i]->m_motion->integrate(stepInfo.m_stepInfo,
                                                               stepInfo.m_solverInfo.m_globalAccelerationPerStep);
            }
            else if (!tl.m_simulation->m_multiCpuSolver)
            {
                HK_TIMER_SPLIT_LIST("Solver 1Cpu");
                hkConstraintSolverSetup::solveSingleThreaded(stepInfo.m_stepInfo, stepInfo.m_solverInfo,
                                                             tl.m_constraintQueryIn, island, entities, numEntities);
            }
            else
            {
                HK_TIMER_SPLIT_LIST("Init nCpu");
                int bufferSize = hkConstraintSolverSetup::calcBufferSize(island, 0x200);
                HK_TIMER_SPLIT_LIST("Allocate");
                void* buffer = hkMemory::getInstance().allocate(bufferSize, HK_MEMORY_CLASS_CONSTRAINT_SOLVER);
                HK_TIMER_SPLIT_LIST("Build Jobs");
                hkBuildJacobianTaskHeader* taskHeader = new hkBuildJacobianTaskHeader;
                hkConstraintSolverSetup::layoutBuffer(island, buffer, bufferSize, taskHeader);

                // the build-accumulators job for all entities of the island
                job.m_jobType = 1;
                job.m_accum.m_taskHeader = taskHeader;
                taskHeader->m_openJobs = 2;
                job.m_accum.m_firstEntity = 0;
                job.m_accum.m_numEntities = (hkUint16)numEntities;
                m_jobQueue.addJob(job, 0, 1);

                // one build-jacobian task with every constraint, low priority constraints last
                hkEntity** e = island->m_entities;
                void* jacobians = taskHeader->m_jacobians;
                void* schemas = taskHeader->m_schemas;
                int n = island->m_numEntities;
                void* solverTemps = taskHeader->m_solverTemps;
                hkBuildJacobianTask* task = new hkBuildJacobianTask;
                task->m_jacobians = jacobians;
                task->m_schemas = schemas;
                task->m_solverTemps = solverTemps;
                task->m_next = 0;
                task->m_taskHeader = taskHeader;
                taskHeader->m_tasks = task;
                {
                    hkInplaceArray<hkConstraintInternal*, 256> lowPriority;
                    for (hkEntity** eEnd = e + n; e < eEnd; e++)
                    {
                        hkConstraintInternal* c = (*e)->m_constraintsMaster;
                        hkConstraintInternal* cEnd = c + (*e)->m_numConstraintsMaster;
                        for (; c < cEnd; c++)
                        {
                            if (c->m_priority < 3)
                                task->m_constraints.pushBack(c);
                            else
                                lowPriority.pushBack(c);
                        }
                    }
                    for (int i = 0; i < lowPriority.getSize(); i++)
                        task->m_constraints.pushBack(lowPriority[i]);
                }
                HK_TIMER_END_LIST();

                hkJobQueueEntry jacJob;
                jacJob.m_jobType = 2;
                jacJob.m_islandIndex = job.m_islandIndex;
                jacJob.m_accum.m_taskHeader = taskHeader;
                if (m_jobQueue.finishJobAndGetNextJob(tl.m_threadType, jacJob, job, &tl, 0) != 0)
                    return;
                break;
            }
            HK_TIMER_END_LIST();
            job.m_jobType = 6;
            m_jobQueue.finishAddAndGetNextJob(0, 1, tl.m_threadType, job, 0);
            break;
        }

        case 1:
        {
            HK_TIMER_BEGIN_LIST("Integrate", "BuildAccum");
            hkConstraintSolverSetup::buildAccumulatorBatch(
                tl.m_collisionInput.m_stepInfo,
                tl.m_world->m_activeSimulationIslands[job.m_islandIndex]->m_entities,
                job.m_accum.m_firstEntity, job.m_accum.m_firstEntity + job.m_accum.m_numEntities,
                job.m_accum.m_taskHeader->m_accumulators);
            HK_TIMER_END_LIST();
            if (m_jobQueue.finishJobAndGetNextJob(tl.m_threadType, job, job, &tl, 0) != 0)
                return;
            break;
        }

        case 3:
        {
            hkBuildJacobianTask* task = job.m_jac.m_task;
            HK_TIMER_BEGIN_LIST("Integrate", "BuildJac");
            void* nextSchemas = task->m_next ? task->m_next->m_schemas : 0;
            hkConstraintSolverSetup::buildJacobianElementBatch(
                tl.m_constraintQueryIn, task->m_constraints.m_data, task->m_constraints.m_size,
                task->m_taskHeader->m_accumulators, task->m_schemas, task->m_jacobians, nextSchemas);
            HK_TIMER_END_LIST();
            if (m_jobQueue.finishJobAndGetNextJob(tl.m_threadType, job, job, &tl, 0) != 0)
                return;
            break;
        }

        case 4:
        {
            char* buffer = job.m_solve.m_buffer;
            void* accumulators = buffer + job.m_solve.m_accumulatorsOffset;
            void* schemas = buffer + job.m_solve.m_schemasOffset;
            hkUint32* solverTemps = (hkUint32*)(buffer + job.m_solve.m_solverTempsOffset);
            void* jacobians = buffer + job.m_solve.m_jacobiansOffset;
            HK_TIMER_BEGIN_LIST("Integrate", "ZeroSolverRes");
            for (int i = 0; i < job.m_solve.m_numSolverResults; i++)
                solverTemps[i] = 0;
            HK_TIMER_SPLIT_LIST("Solve");
            hkSolveConstraints(tl.m_world->m_dynamicsStepInfo.m_solverInfo, schemas, accumulators, jacobians,
                               solverTemps);
            HK_TIMER_END_LIST();
            job.m_jobType = 5;
            job.m_accum.m_taskHeader = job.m_solve.m_taskHeader;
            m_jobQueue.finishAddAndGetNextJob(1, 0, tl.m_threadType, job, 0);
            break;
        }

        case 5:
        {
            HK_TIMER_BEGIN("writeBackConstraints");
            hkBuildJacobianTaskHeader* taskHeader = job.m_accum.m_taskHeader;
            hkExportImpulsesAndRhs(tl.m_world->m_dynamicsStepInfo.m_solverInfo, taskHeader->m_schemas,
                                   taskHeader->m_accumulators, taskHeader->m_jacobians, taskHeader->m_solverTemps);
            hkSimulationIsland* island = tl.m_world->m_activeSimulationIslands[job.m_islandIndex];
            hkConstraintSolverSetup::integrateBatch(tl.m_world->m_dynamicsStepInfo, island->m_entities,
                                                    island->m_numEntities, taskHeader->m_accumulators);
            while (taskHeader->m_tasks)
            {
                hkBuildJacobianTask* task = taskHeader->m_tasks;
                taskHeader->m_tasks = task->m_next;
                // delete task (cl 15 would call the scalar deleting destructor out of line)
                task->~hkBuildJacobianTask();
                hkBuildJacobianTask::operator delete(task);
            }
            hkMemory::getInstance().deallocate(taskHeader->m_buffer, taskHeader->m_bufferSize,
                                               HK_MEMORY_CLASS_CONSTRAINT_SOLVER);
            delete taskHeader;
            HK_TIMER_END();
            job.m_jobType = 6;
            m_jobQueue.finishAddAndGetNextJob(1, 0, tl.m_threadType, job, 0);
            break;
        }

        case 6:
        {
            hkSimulationIsland* island = tl.m_world->m_activeSimulationIslands[job.m_islandIndex];
            tl.m_simulation->collideEntitiesBroadPhaseContinuous(island->m_entities, island->m_numEntities,
                                                                 tl.m_world,
                                                                 tl.m_simulation->m_broadPhaseCriticalSection);
            int numSectors = island->m_agentTrack.m_numSectors;
            if (numSectors > 0)
            {
                job.m_jobType = 7;
                job.m_narrowPhase.m_sectorIndex = 0;
                job.m_narrowPhase.m_numSectors = numSectors;
                m_jobQueue.finishAddAndGetNextJob(1, 1, tl.m_threadType, job, 0);
                break;
            }
            if (m_jobQueue.finishJobAndGetNextJob(tl.m_threadType, job, job, &tl, 0) != 0)
                return;
            break;
        }

        case 7:
        {
            hkSimulationIsland* island = tl.m_world->m_activeSimulationIslands[job.m_islandIndex];
            HK_TIMER_BEGIN("NarrowPhase");
            hkProcessCollisionOutput output;
            while (--job.m_narrowPhase.m_numSectors >= 0)
            {
                hkAgentNnTrack& track = island->m_agentTrack;
                hkUint8* sector = track.m_sectors[job.m_narrowPhase.m_sectorIndex];
                hkUint32 bytesUsed = (job.m_narrowPhase.m_sectorIndex < track.m_numSectors - 1)
                                         ? track.m_sectorSize : track.m_bytesUsedInLastSector;
                hkUint8* end = sector + bytesUsed;
                for (hkUint8* entry = sector; entry < end; entry += ((hkAgentNnEntry*)entry)->m_size)
                    processAgentEntry((hkAgentNnEntry*)entry, tl.m_collisionInput, output, tl.m_simulation);
                job.m_narrowPhase.m_sectorIndex++;
            }
            HK_TIMER_END();
            if (m_jobQueue.finishJobAndGetNextJob(tl.m_threadType, job, job, &tl, 0) != 0)
                return;
            break;
        }
        }
    }
}
