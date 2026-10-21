// Slice s010a22b0: 0x010A22B0..0x010A32A0 -- Havok 3.1.0 (prebuilt lib, VS2008 cl 15.00).
//   0x010A22B0 hkSimulationIsland::calcStatistics, 0x010A24B0 addAction, 0x010A24F0 ~hkSimulationIsland,
//   0x010A2590 isFullyConnected, 0x010A2810 hkSimulationIsland ctor,
//   0x010A28F0..0x010A2AC0 hkDefaultWorldMaintenanceMgr (init/ctor/resetWorldTime/checkDeactivation/
//   performMaintenance), 0x010A2C60..0x010A3190 hkBroadPhaseBorder (dtor/callbacks/deactivate/ctor),
//   0x010A31C0/0x010A32A0 hkHalfstepSimulation (recoverFromStepFailure/ctor).
// Flags: /O2 /MD /Gy /TP /GS- /fp:fast (Havok: x87 floats, no EH frame, /GS-).
// Layouts: match/slices/s010a32c0 (adjacent Havok slice), match/slices/s010869e0/hk31_world.h,
// match/slices/s010cbaa0/hk31_b005.h (hkArray/hkMemory).
#include <stddef.h>
#include <intrin.h>
#include "types.h"

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);

typedef float hkReal;
typedef uint16_t hkUint16;
typedef uint8_t hkUint8;
typedef int8_t hkInt8;

void* operator new(size_t, void* p) { return p; }

// ---------------------------------------------------------------------------------------------- core types
// hkBool: one byte; the user-provided constructors make it a non-trivial class, so it is returned
// through a hidden pointer (see checkDeactivation / isFullyConnected).
class hkBool
{
public:
    hkBool() : m_bool(0) {}
    hkBool(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
    int8_t m_bool;
};

struct hkVector4 { float x, y, z, w; };
struct hkAabb { hkVector4 m_min; hkVector4 m_max; };      // 0x20

inline void hkAabb_set(hkAabb& aabb, hkReal x0, hkReal y0, hkReal z0, hkReal x1, hkReal y1, hkReal z1)
{
    aabb.m_min.x = x0; aabb.m_min.y = y0; aabb.m_min.z = z0; aabb.m_min.w = 0;
    aabb.m_max.x = x1; aabb.m_max.y = y1; aabb.m_max.z = z1; aabb.m_max.w = 0;
}
struct hkStepInfo { hkReal m_startTime, m_endTime, m_deltaTime, m_invDeltaTime; };   // 0x10

class hkStatisticsCollector;

class hkReferencedObject
{
public:
    hkReferencedObject() { m_referenceCount = 1; }
    virtual ~hkReferencedObject() {}
    virtual void calcStatistics(hkStatisticsCollector* collector) const {}   // slot 1 (0x0052E650: empty)
    void addReference() { if (m_memSizeAndFlags != 0) m_referenceCount++; }
    void removeReference()
    {
        if (m_memSizeAndFlags != 0)
        {
            if (--m_referenceCount == 0)
                delete this;
        }
    }
    void operator delete(void*) {}

    hkUint16 m_memSizeAndFlags;                   // +0x4
    short    m_referenceCount;                    // +0x6
};

class hkMemory
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void* allocateChunk(int nbytes, int cls);
    virtual void v5();
    virtual void* onRowEmpty(int row, int cls);
    virtual void deallocateChunk(void* p, int nbytes, int cls);
    virtual void v8();

    int m_numUsedChunks;                          // +0x04 (the sticky "out of memory" flag)
    static hkMemory* s_instance;                  // 0x016E4178
};

extern unsigned long g_hkThreadMemoryTlsIndex;    // 0x016E4174

struct hkThreadMemory
{
    struct Elem { Elem* m_next; };
    uint32_t m_pad0[0xe];
    Elem*    m_freeListHead[17];                  // +0x38
    int      m_freeListCount[17];                 // +0x7c

    static hkThreadMemory* getInstance() { return (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }
    void deallocateChunk(void* p, int nbytes, int cls);    // 0x0107DB10
};

// HK_TIMER_BEGIN / HK_TIMER_END of hkMonitorStream.h; the fast path is inlined. A timer command is
// 0xc bytes (name ptr + rdtsc + the begin/end marker the writer puts after them).
extern unsigned long g_hkMonitorStreamCurrentTls; // 0x016E42A4
extern unsigned long g_hkMonitorStreamEndTls;     // 0x016E42A8

// 0xc-byte record: name, time, pad (this build does not write the 'B'/'E' tag byte).
static __forceinline void hkMonitorStream_startTimer(const char* name)
{
    unsigned char* end = (unsigned char*)TlsGetValue(g_hkMonitorStreamEndTls);
    unsigned char* current = (unsigned char*)TlsGetValue(g_hkMonitorStreamCurrentTls);
    if (current < end)
    {
        *(const char**)(current) = name;
        volatile uint32_t t = (uint32_t)__rdtsc();
        *(uint32_t*)(current + 4) = t;
        TlsSetValue(g_hkMonitorStreamCurrentTls, current + 0xc);
    }
}

static __forceinline void hkMonitorStream_endTimer(const char* marker)
{
    unsigned char* end = (unsigned char*)TlsGetValue(g_hkMonitorStreamEndTls);
    unsigned char* current = (unsigned char*)TlsGetValue(g_hkMonitorStreamCurrentTls);
    if (current < end)
    {
        *(const char**)(current) = marker;
        volatile uint32_t t = (uint32_t)__rdtsc();
        *(uint32_t*)(current + 4) = t;
        TlsSetValue(g_hkMonitorStreamCurrentTls, current + 0xc);
    }
}

// HK_TIMER_BEGIN_LIST: 0x10-byte record (name, time, pad, first split name).
static __forceinline void hkMonitorStream_startTimerList(const char* name, const char* firstSplit)
{
    unsigned char* end = (unsigned char*)TlsGetValue(g_hkMonitorStreamEndTls);
    unsigned char* current = (unsigned char*)TlsGetValue(g_hkMonitorStreamCurrentTls);
    if (current < end)
    {
        *(const char**)(current) = name;
        *(const char**)(current + 0xc) = firstSplit;
        volatile uint32_t t = (uint32_t)__rdtsc();
        *(uint32_t*)(current + 4) = t;
        TlsSetValue(g_hkMonitorStreamCurrentTls, current + 0x10);
    }
}

// ---------------------------------------------------------------------------------------------- containers
void hkArrayUtil__reserveMore(void* array, int sizeofElem);      // 0x0107F530 (hkArrayUtil::_reserveMore)

template <typename T>
struct hkArray
{
    T*  m_data;                                 // +0
    int m_size;                                 // +4
    int m_capacity;                             // +8 (bit 31: the data is inline storage)

    ~hkArray()
    {
        if (m_capacity >= 0)
            hkThreadMemory::getInstance()->deallocateChunk(m_data, ((unsigned)m_capacity & 0x3fffffffu) * sizeof(T), 0x14);
    }
    T& operator[](int i) { return m_data[i]; }
    const T& operator[](int i) const { return m_data[i]; }
    void pushBack(const T& e)
    {
        if (m_size == (m_capacity & 0x3fffffff))
            hkArrayUtil__reserveMore(this, sizeof(T));
        m_data[m_size++] = e;
    }
};

template <typename T, int N>
struct hkInplaceArray : hkArray<T>
{
    T m_storage[N];                             // +0xc
};

// ---------------------------------------------------------------------------------------------- statistics
class hkStatisticsCollector
{
public:
    virtual void v0();
    virtual void beginAddObject(const char* name, int id, const void* object);          // +0x04
    virtual void addArray(const char* name, int id, const void* array, int size, int capacity);   // +0x08
    virtual void addObject(const char* name, int id, const void* object);               // +0x0c
    virtual void beginGroup(const char* name);                                          // +0x10
    virtual void endGroup();                                                            // +0x14
    virtual void endAddObject();                                                        // +0x18
};

// ---------------------------------------------------------------------------------------------- union find
// match/slices/s01209060: hkUnionFind holds one hkArray<int>; isFullyConnected is
// m_array->m_data[0] == -m_array->m_size (set == every element in one class).
class hkUnionFind
{
public:
    void addEdge(int a, int b);                 // 0x01209540
    hkBool isFullyConnected() const { return hkBool(m_array->m_data[0] == -m_array->m_size); }
    hkArray<int>* m_array;                      // +0
};

// ---------------------------------------------------------------------------------------------- forward decls
class hkWorld;
class hkEntity;
class hkRigidBody;
class hkPhantom;
class hkAabbPhantom;
class hkSimulationIsland;
class hkCollisionDispatcher;
class hkCollisionFilter;
class hkProcessCollisionInput;
class hkAction;
class hkWorldDeletionListener;
struct hkCollidableAddedEvent;

class hkMultiThreadLock { public: unsigned int m_threadId; int m_lockCount; };

struct hkAgentNnEntry                                     // 0x1c bytes (retail)
{
    uint8_t  m_streamCommand;        // +0
    uint8_t  m_agentType;            // +1
    uint8_t  m_numContactPoints;     // +2
    uint8_t  m_size;                 // +3
    uint32_t m_userData;             // +4
    uint8_t  m_collisionQualityIndex;// +8
    uint8_t  m_padding[3];           // +9
    uint16_t m_agentIndexOnCollidable[2];   // +0xc
    void*    m_contactMgr;           // +0x10
    void*    m_collidable[2];        // +0x14
};

struct hkAgentNnTrack                                     // 0x18 bytes
{
    hkInplaceArray<char*, 1> m_sectors;      // +0 (data, size, capacity, one inline sector ptr)
    unsigned int   m_bytesUsedInLastSector;  // +0x10
    unsigned short m_agentSize;              // +0x14
    unsigned short m_sectorSize;             // +0x16
};

class hkSimpleConstraintOwner : public hkReferencedObject
{
public:
    int m_maxSizeOfJacobians;        // +0x08
    int m_sumSizeOfJacobians;        // +0x0c
    int m_sumSizeOfSchemas;          // +0x10
    int m_sumSizeOfMotions;          // +0x14
    int m_sumNumSolverResults;       // +0x18
};

class hkSimulationIsland : public hkSimpleConstraintOwner      // size 0x74
{
protected:
    hkSimulationIsland(hkWorld* world);         // 0x010A2810
public:
    virtual ~hkSimulationIsland();              // 0x010A24F0
    virtual void calcStatistics(hkStatisticsCollector* collector) const;   // 0x010A22B0
    void addAction(hkAction* action);           // 0x010A24B0
    hkBool isFullyConnected(hkUnionFind& islandLinks);   // 0x010A2590
    hkBool shouldDeactivate(const hkStepInfo& stepInfo); // 0x010A20F0

    hkWorld* m_world;                           // +0x1c
    uint16_t m_storageIndex;                    // +0x20
    uint16_t m_dirtyListIndex;                  // +0x22
    uint8_t m_highFrequencyDeactivationCounter; // +0x24
    uint8_t m_lowFrequencyDeactivationCounter;  // +0x25
    uint8_t m_splitCheckRequested;              // +0x26
    uint8_t m_actionListCleanupNeeded;          // +0x27
    uint8_t m_active;                           // +0x28
    uint8_t m_isInActiveIslandsArray;           // +0x29
    uint16_t m_pad2a;                           // +0x2a
    hkMultiThreadLock m_multiThreadLock;        // +0x2c
    float m_timeSinceLastHighFrequencyCheck;    // +0x34
    float m_timeSinceLastLowFrequencyCheck;     // +0x38
    hkInplaceArray<hkEntity*, 1> m_entities;    // +0x3c
    hkAgentNnTrack m_agentTrack;                // +0x4c
    hkArray<void*> m_actions;                   // +0x64
    float m_timeOfDeactivation;                 // +0x70 (-10.0f)
};

// One hkCollidable (embedded in an hkEntity at +0x1c). +0x10 holds the offset from the collidable back to
// its owning entity; +0x18 is the collidable's type; +0x24/+0x28 are its broad-phase pair list.
struct hkCollidable
{
    void*    m_vptr;                 // +0
    void*    m_broadPhaseHandle;     // +4
    void*    m_shape;                // +8
    void*    m_motion;               // +0xc
    int      m_entityOffset;         // +0x10
    uint32_t m_pad14;                // +0x14
    int8_t   m_type;                 // +0x18
    uint8_t  m_pad19[0xb];
    void*    m_pairsData;            // +0x24 (8-byte entries: agent entry, partner collidable)
    int      m_numPairs;             // +0x28

    hkEntity* getEntity() const { return (hkEntity*)((char*)this + m_entityOffset); }
};

struct hkCollisionEntry { void* m_agentEntry; hkCollidable* m_partner; };    // 8 bytes

class hkMotion
{
public:
    uint32_t m_pad00[0x5c / 4];
    hkReal   m_time;                 // +0x5c (advanced by resetWorldTime)
};

struct hkMaterial { uint32_t m_data[3]; };

class hkEntity
{
public:
    virtual void deallocateInternalArrays();
    virtual hkEntity* entityClone() const;
    virtual void _v2(); virtual void _v3(); virtual void _v4(); virtual void _v5(); virtual void _v6();

    uint32_t m_memSizeAndFlags;                 // +4
    void* m_broadPhaseHandle;                   // +8
    uint8_t m_pad0c[0x10 - 0xc];
    uint32_t m_0x10;                            // +0x10
    uint8_t m_pad14[0x58 - 0x14];
    hkMotion*          m_motion;                // +0x58
    hkSimulationIsland* m_simulationIsland;     // +0x5c
    hkMaterial         m_material;              // +0x60
    void*              m_deactivator;           // +0x6c
    uint32_t           m_constraintsMaster[3];  // +0x70 (data, size, capacity)
    uint32_t           m_constraintsSlave[3];   // +0x7c
    uint32_t           m_constraintRuntime[3];  // +0x88
    uint16_t           m_storageIndex;          // +0x94
    uint16_t           m_processContactCallbackDelay;   // +0x96
    char               m_autoRemoveLevel;       // +0x98
    hkBool             m_fixed;                 // +0x99
    hkBool             m_isFixedOrKeyframed;    // +0x9a
    hkBool             m_internalCollideFlag;   // +0x9b
};

// The 0x1c master-constraint entries of hkEntity (+0x70, stride 0x1c).
struct hkConstraintInstanceInternal
{
    void*      m_constraintInstance;    // +0
    hkEntity*  m_entityA;               // +4
    hkEntity*  m_entityB;               // +8
    void*      m_constraintData;        // +0xc
    uint32_t   m_pad10[3];              // +0x10
};

class hkAction
{
public:
    virtual void actionSlot0();
    virtual void actionSlot1();
    virtual void actionSlot2();
    virtual void getEntities(hkArray<hkEntity*>& entities);    // +0xc
};

// ---------------------------------------------------------------------------------------------- world objects
class hkWorldObject : public hkReferencedObject
{
public:
    void removeReference();             // 0x0109AE60 (?removeReference@hkWorldObject@@QAEXXZ)
    hkWorld* m_world;                   // +8
};

class hkPhantom : public hkWorldObject
{
public:
    void addOverlapListener(void* listener);        // 0x0108E4A0
    void removeOverlapListener(void* listener);     // 0x0108E450
    uint32_t m_pad0c[0x34 / 4 - 3];
    uint8_t  m_phantomType;                         // +0x34
};

class hkAabbPhantom : public hkPhantom
{
public:
    hkAabbPhantom(const hkAabb& aabb, uint32_t collisionFilterInfo);    // 0x0108DFE0
};

class hkProcessCollisionInput
{
public:
    void* m_dispatcher;                 // +0
    void* m_filter;                     // +4
    float m_tolerance;                  // +8
    hkBool m_createPredictiveAgents;    // +0xc
    uint8_t m_pad0d[3];
    hkStepInfo m_stepInfo;              // +0x10
};

struct hkWorldDynamicsStepInfo
{
    hkStepInfo m_stepInfo;              // +0
    uint32_t   m_solverInfo[0x140 / 4];
};

struct hkCollisionDispatcherTail
{
    uint8_t m_pad0000[0x1bf8];
    int     m_numBytesPerSector;        // +0x1bf8
    int     m_agentSize;                // +0x1bfc
};

// ---------------------------------------------------------------------------------------------- hkWorld
class hkSimulation : public hkReferencedObject
{
public:
    virtual int  stepDeltaTime(hkWorld* world, hkReal physicsDeltaTime, hkReal frameDeltaTime);   // slot 2
    virtual int  simSlot3(); virtual void simSlot4(); virtual void simSlot5(); virtual void simSlot6();
    virtual void simSlot7(); virtual void simSlot8(); virtual void simSlot9(); virtual void simSlot10();
    virtual void simSlot11(); virtual void simSlot12();
    virtual void simSlot13(hkWorld* world, hkReal advance);            // +0x34
};

class hkAsynchronousSimulation : public hkSimulation
{
public:
    hkAsynchronousSimulation() : m_synchronizeFrameAndPhysicsTime(true) {}
    virtual int recoverFromStepFailure(hkWorld* world, int result);    // slot 3
    hkReal m_frameDeltaTime;                 // +0x8
    hkBool m_synchronizeFrameAndPhysicsTime; // +0xc
};

enum hkStepResult { HK_STEP_RESULT_SUCCESS = 0, HK_STEP_RESULT_MEMORY_FAILURE = 1, HK_STEP_RESULT_BUSY = 2 };

class hkHalfstepSimulation : public hkAsynchronousSimulation       // size 0x14
{
public:
    hkHalfstepSimulation();                                             // 0x010A32A0
    virtual int recoverFromStepFailure(hkWorld* world, int result);     // 0x010A31C0
    void restartFromStepFailure(hkWorld* world, hkStepInfo& stepInfo);  // 0x0109A200
    int m_simulationStep;                    // +0x10
};

class hkWorld : public hkReferencedObject
{
public:
    hkSimulation*        m_simulation;                  // +0x08
    hkReal               m_currentTime;                 // +0x0c
    hkReal               m_timeOfNextFrame;             // +0x10
    hkReal               m_timeOfLastPsi;               // +0x14
    hkReal               m_timeOfNextPsi;               // +0x18
    uint32_t             m_pad1c;
    hkVector4            m_gravity;                     // +0x20
    hkSimulationIsland*  m_fixedIsland;                 // +0x30
    hkRigidBody*         m_fixedRigidBody;              // +0x34
    hkArray<hkSimulationIsland*> m_activeSimulationIslands;     // +0x38
    hkArray<hkSimulationIsland*> m_inactiveSimulationIslands;   // +0x44
    hkArray<hkSimulationIsland*> m_dirtySimulationIslands;      // +0x50
    void*                m_maintenanceMgr;              // +0x5c
    void*                m_memoryWatchDog;              // +0x60
    void*                m_broadPhase;                  // +0x64
    void*                m_broadPhaseDispatcher;        // +0x68
    void*                m_phantomBroadPhaseListener;   // +0x6c
    void*                m_entityEntityBroadPhaseListener;  // +0x70
    void*                m_broadPhaseBorderListener;    // +0x74
    hkProcessCollisionInput* m_collisionInput;          // +0x78
    hkCollisionFilter*   m_collisionFilter;             // +0x7c
    hkCollisionDispatcher* m_collisionDispatcher;       // +0x80
    void*                m_pendingOperations;           // +0x84
    int                  m_pendingOperationsCount;      // +0x88
    int                  m_lockCount;                   // +0x8c
    int                  m_lockCountForPhantoms;        // +0x90
    hkBool               m_blockExecutingPendingOperations;     // +0x94
    hkBool               m_criticalOperationsAllowed;   // +0x95
    uint16_t             m_pad96;
    void*                m_pendingOperationQueues;      // +0x98
    int                  m_pendingOperationQueueCount;  // +0x9c
    hkMultiThreadLock    m_multiThreadLock;             // +0xa0
    hkBool               m_processActionsInSingleThread;    // +0xa8
    uint8_t              m_pada9[3];
    void*                m_modifyConstraintCriticalSection; // +0xac
    void*                m_worldLock;                   // +0xb0
    hkBool               m_wantSimulationIslands;       // +0xb4
    hkBool               m_wantDeactivation;            // +0xb5
    hkBool               m_shouldActivateOnRigidBodyTransformChange;    // +0xb6
    uint8_t              m_padb7;
    hkReal               m_highFrequencyDeactivationPeriod;     // +0xb8
    hkReal               m_lowFrequencyDeactivationPeriod;      // +0xbc
    hkReal               m_toiCollisionResponseRotateNormal;    // +0xc0
    int                  m_simulationType;              // +0xc4
    unsigned int         m_lastEntityUid;               // +0xc8
    hkArray<hkPhantom*>  m_phantoms;                    // +0xcc
    uint32_t             m_pad0d8[0x170 / 4 - 0xd8 / 4];   // +0xd8..+0x170
    hkWorldDynamicsStepInfo m_dynamicsStepInfo;         // +0x170
    hkAabb               m_broadPhaseBorder;            // +0x2c0
    int                  m_broadPhaseNumMarkers;        // +0x2e0

    void addWorldDeletionListener(hkWorldDeletionListener* listener);   // 0x01083530
    void removeWorldDeletionListener(hkWorldDeletionListener* listener);   // 0x01082A40
    hkPhantom* addPhantom(hkPhantom* phantom);          // 0x01083320
    void removePhantomBatch(hkPhantom** phantoms, int numPhantoms);     // 0x01086500
    void removeEntity(void* tmp, hkEntity* entity);     // 0x01083110
    void updateCollisionFilterOnWorld(int updateMode, int updateShapeCollections);   // 0x010869E0
};

class hkRigidBody : public hkEntity
{
public:
    void setMotionType(int newState, int preferredActivationState, int collisionFilterUpdateMode);   // 0x01087520
};

// ---------------------------------------------------------------------------------------------- listeners
class hkWorldDeletionListener
{
public:
    virtual ~hkWorldDeletionListener() {}
    virtual void worldDeletedCallback(hkWorld* world);
};

struct hkCollidableAddedEvent
{
    void* m_0;                      // +0
    hkCollidable* m_collidable;     // +4
};

class hkCollidableListener
{
public:
    ~hkCollidableListener() {}
    virtual void collidableAddedCallback(const hkCollidableAddedEvent& event);
    virtual void collidableRemovedCallback(const void* event);
};

// ---------------------------------------------------------------------------------------------- maintenance
class hkDefaultWorldMaintenanceMgr : public hkReferencedObject
{
public:
    hkDefaultWorldMaintenanceMgr();                                     // 0x010A2910
    virtual void init(hkWorld* world);                                  // 0x010A28F0
    virtual void performMaintenance(hkWorld* world, hkStepInfo& stepInfo);   // 0x010A2AC0

    void resetWorldTime(hkWorld* world, hkStepInfo& stepInfo);          // 0x010A2960
    void checkDeactivation(hkWorld* world, const hkStepInfo& stepInfo);// 0x010A2A70

    hkReal m_worldTimeOffset;           // +0x08 (33.0f)
    hkReal m_worldTimeResetDelay;       // +0x0c (63.0f)
};

// ---------------------------------------------------------------------------------------------- broad-phase border
enum BroadPhaseBorderBehaviour
{
    BROAD_PHASE_BORDER_RAISE_ERROR = 0,
    BROAD_PHASE_BORDER_CLAMP = 1,
    BROAD_PHASE_BORDER_REMOVE_ENTITY = 2
};

class hkBroadPhaseBorder : public hkReferencedObject, public hkWorldDeletionListener, public hkCollidableListener
{
public:
    hkBroadPhaseBorder(hkWorld* world, BroadPhaseBorderBehaviour behaviour);   // 0x010A2DB0
    virtual ~hkBroadPhaseBorder();                                              // 0x010A2C60
    virtual void maxPositionExceededCallback(hkEntity* entity);                 // 0x010A2CB0 (slot 2)
    virtual void deactivate();                                                  // 0x010A2D30 (slot 3)
    virtual void worldDeletedCallback(hkWorld* world);                          // 0x010A2CF0
    virtual void collidableAddedCallback(const hkCollidableAddedEvent& event);  // 0x010A3190

    hkWorld*   m_world;                 // +0x10
    hkPhantom* m_phantoms[6];           // +0x14
    int        m_behaviour;             // +0x2c
};

// ---------------------------------------------------------------------------------------------- callees
void hkWorldOperationUtil_splitSimulationIslands(hkWorld* world);                   // 0x010A1320
void hkWorldOperationUtil_markIslandInactive(hkWorld* world, hkSimulationIsland* island);   // 0x010A00E0
void hkWorldAgentUtil_warpTime(hkSimulationIsland* island, hkReal startTime, hkReal endTime,
                               hkProcessCollisionInput* collisionInput);            // 0x010A38C0
void hkWorld_restartFromStepFailure(hkWorld* world, const hkStepInfo& stepInfo);    // 0x0109A200
void hkAgentMachineUtil_calcNnStatisticsContactMgrsOnly(const hkAgentNnTrack& track, hkStatisticsCollector* collector);   // 0x010FCF90
void hkAgentMachineUtil_calcNnStatistics(const hkAgentNnTrack& track, hkStatisticsCollector* collector);   // 0x010FCEB0

extern const char* const hkNullName;    // 0
extern const char* const g_monitorStreamEndMarker;      // 0x0143CD94

// =============================================================================================================
// hkSimulationIsland
// =============================================================================================================
// @ 0x010a22b0
void hkSimulationIsland::calcStatistics(hkStatisticsCollector* collector) const
{
    collector->beginAddObject(hkNullName, 8, this);
    if (m_entities.m_capacity >= 0)
        collector->addArray("EntityPtrs", 8, m_entities.m_data, m_entities.m_size * 4,
                            (m_entities.m_capacity & 0x3fffffff) * 4);

    for (int i = 0; i < m_entities.m_size; i++)
    {
        hkEntity* entity = m_entities.m_data[i];
        collector->addObject("Entity", 2, entity);
        collector->beginGroup("Constraints");
        if ((int)entity->m_constraintsMaster[2] >= 0)
            collector->addArray("ConMstPtr", 8, (void*)entity->m_constraintsMaster[0],
                                (int)entity->m_constraintsMaster[1] * 0x1c,
                                ((int)entity->m_constraintsMaster[2] & 0x3fffffff) * 0x1c);
        if ((int)entity->m_constraintsSlave[2] >= 0)
            collector->addArray("ConSlvPtr", 8, (void*)entity->m_constraintsSlave[0],
                                (int)entity->m_constraintsSlave[1] * 4,
                                ((int)entity->m_constraintsSlave[2] & 0x3fffffff) * 4);

        hkConstraintInstanceInternal* master = (hkConstraintInstanceInternal*)entity->m_constraintsMaster[0];
        const int numMaster = (int)entity->m_constraintsMaster[1];
        for (int j = 0; j < numMaster; j++)
        {
            collector->addObject("ConInstance", 2, master[j].m_constraintInstance);
            collector->addObject("ConData", 1, master[j].m_constraintData);
        }

        if ((int)entity->m_constraintRuntime[2] >= 0)
            collector->addArray("Runtime", 4, (void*)entity->m_constraintRuntime[0],
                                (int)entity->m_constraintRuntime[1],
                                (int)entity->m_constraintRuntime[2] & 0x3fffffff);
        collector->endGroup();
    }

    if (m_actions.m_capacity >= 0)
        collector->addArray("ActionPtrs", 8, m_actions.m_data, m_actions.m_size * 4,
                            (m_actions.m_capacity & 0x3fffffff) * 4);
    for (int i = 0; i < m_actions.m_size; i++)
        collector->addObject("Actions", 2, m_actions.m_data[i]);

    hkAgentMachineUtil_calcNnStatisticsContactMgrsOnly(m_agentTrack, collector);
    collector->beginGroup("CollAgents");
    hkAgentMachineUtil_calcNnStatistics(m_agentTrack, collector);
    collector->endGroup();
    collector->endAddObject();
}

// @ 0x010a24b0
void hkSimulationIsland::addAction(hkAction* action)
{
    m_actions.pushBack((void*)action);
    *(hkSimulationIsland**)((char*)action + 0xc) = this;
}

// @ 0x010a24f0
hkSimulationIsland::~hkSimulationIsland()
{
}

// @ 0x010a2590
hkBool hkSimulationIsland::isFullyConnected(hkUnionFind& islandLinks)
{
    // entity-entity links
    for (int i = 0; i < m_entities.m_size; i++)
    {
        hkCollidable* collidable = (hkCollidable*)((char*)m_entities.m_data[i] + 0x1c);
        for (int j = 0; j < collidable->m_numPairs; j++)
        {
            hkEntity* other = ((hkCollisionEntry*)collidable->m_pairsData)[j].m_partner->getEntity();
            if (!other->m_fixed)
            {
                islandLinks.addEdge(i, other->m_storageIndex);
                if (islandLinks.isFullyConnected())
                    return hkBool(true);
            }
        }
    }

    // constraint links
    for (int i = 0; i < m_entities.m_size; i++)
    {
        hkEntity* entity = m_entities.m_data[i];
        for (int j = 0; j < (int)entity->m_constraintsMaster[1]; j++)
        {
            hkConstraintInstanceInternal* master = (hkConstraintInstanceInternal*)entity->m_constraintsMaster[0];
            hkConstraintInstanceInternal& instance = master[j];
            hkEntity* entityA = instance.m_entityA;
            if (!entityA->m_fixed)
            {
                hkEntity* entityB = instance.m_entityB;
                if (!entityB->m_fixed)
                {
                    islandLinks.addEdge(entityA->m_storageIndex, entityB->m_storageIndex);
                    if (islandLinks.isFullyConnected())
                        return hkBool(true);
                }
            }
        }
    }

    // action links
    {
        hkInplaceArray<hkEntity*, 10> linkedEntities;
        linkedEntities.m_data = linkedEntities.m_storage;
        linkedEntities.m_size = 0;
        linkedEntities.m_capacity = 10 | (int)0x80000000;
        for (int i = 0; i < m_actions.m_size; i++)
        {
            if (!m_actions.m_data[i])
                continue;
            hkAction* action = (hkAction*)m_actions.m_data[i];

            linkedEntities.m_size = 0;
            action->getEntities(linkedEntities);

            int first = -1;
            int j = 0;
            while (j < linkedEntities.m_size && first == -1)
            {
                if (!linkedEntities[j]->m_fixed)
                    first = j;
                j++;
            }
            if (first != -1)
            {
                for (; j < linkedEntities.m_size; j++)
                {
                    if (!linkedEntities[j]->m_fixed)
                    {
                        islandLinks.addEdge(linkedEntities[first]->m_storageIndex, linkedEntities[j]->m_storageIndex);
                        if (islandLinks.isFullyConnected())
                            return hkBool(true);
                    }
                }
            }
        }
    }

    return islandLinks.isFullyConnected();
}

// @ 0x010a2810
hkSimulationIsland::hkSimulationIsland(hkWorld* world)
{
    m_world = world;
    m_dirtyListIndex = 0xffff;
    m_maxSizeOfJacobians = 0;
    m_sumSizeOfJacobians = 0;
    m_sumSizeOfSchemas = 0;
    m_sumSizeOfMotions = 0;
    m_sumNumSolverResults = 0;
    m_highFrequencyDeactivationCounter = 0;
    m_lowFrequencyDeactivationCounter = 0;
    m_splitCheckRequested = false;
    m_actionListCleanupNeeded = false;
    m_active = true;
    m_isInActiveIslandsArray = true;
    m_multiThreadLock.m_threadId = 0xffffffd1;
    m_multiThreadLock.m_lockCount = 0;
    m_timeSinceLastHighFrequencyCheck = 0;
    m_timeSinceLastLowFrequencyCheck = 0;

    m_entities.m_size = 0;
    m_entities.m_capacity = 0x80000001;
    m_entities.m_data = m_entities.m_storage;

    hkCollisionDispatcherTail* dispatcher = (hkCollisionDispatcherTail*)world->m_collisionDispatcher;
    const int sectorSize = dispatcher->m_numBytesPerSector;
    const int agentSize = dispatcher->m_agentSize;
    m_agentTrack.m_agentSize = (unsigned short)agentSize;
    m_agentTrack.m_sectorSize = (unsigned short)sectorSize;

    m_agentTrack.m_sectors.m_data = m_agentTrack.m_sectors.m_storage;
    m_agentTrack.m_sectors.m_size = 0;
    m_agentTrack.m_sectors.m_capacity = 0x80000001;
    m_agentTrack.m_bytesUsedInLastSector = (unsigned int)(sectorSize & 0xffff);

    m_actions.m_data = 0;
    m_actions.m_size = 0;
    m_actions.m_capacity = (int)0x80000000;
    m_timeOfDeactivation = -10.0f;
}

// =============================================================================================================
// hkDefaultWorldMaintenanceMgr
// =============================================================================================================
// @ 0x010a28f0
void hkDefaultWorldMaintenanceMgr::init(hkWorld* world)
{
    world->m_currentTime = m_worldTimeOffset;
    world->m_timeOfNextFrame = m_worldTimeOffset;
    world->m_timeOfLastPsi = m_worldTimeOffset;
    world->m_timeOfNextPsi = m_worldTimeOffset;
}

// @ 0x010a2910
hkDefaultWorldMaintenanceMgr::hkDefaultWorldMaintenanceMgr()
{
    m_worldTimeOffset = 33.0f;
    m_worldTimeResetDelay = 63.0f;
}

// @ 0x010a2960
void hkDefaultWorldMaintenanceMgr::resetWorldTime(hkWorld* world, hkStepInfo& stepInfo)
{
    hkStepInfo& worldStep = world->m_dynamicsStepInfo.m_stepInfo;

    const hkReal deltaTime = stepInfo.m_endTime - stepInfo.m_startTime;
    worldStep.m_startTime = m_worldTimeOffset;
    worldStep.m_endTime = deltaTime + m_worldTimeOffset;
    worldStep.m_deltaTime = deltaTime;
    worldStep.m_invDeltaTime = 1.0f / deltaTime;

    const hkReal advance = worldStep.m_startTime - stepInfo.m_startTime;
    world->m_currentTime += advance;
    world->m_timeOfNextFrame += advance;
    world->m_timeOfLastPsi = worldStep.m_startTime;
    world->m_timeOfNextPsi = worldStep.m_endTime;

    for (int i = 0; i < world->m_activeSimulationIslands.m_size; i++)
    {
        hkSimulationIsland* island = world->m_activeSimulationIslands.m_data[i];
        for (int j = 0; j < island->m_entities.m_size; j++)
            island->m_entities.m_data[j]->m_motion->m_time += advance;
    }

    for (int i = 0; i < world->m_activeSimulationIslands.m_size; i++)
        hkWorldAgentUtil_warpTime(world->m_activeSimulationIslands.m_data[i], stepInfo.m_endTime,
                                  worldStep.m_endTime, world->m_collisionInput);

    world->m_simulation->simSlot13(world, advance);

    stepInfo = worldStep;
    world->m_collisionInput->m_stepInfo = worldStep;
}

// @ 0x010a2a70
void hkDefaultWorldMaintenanceMgr::checkDeactivation(hkWorld* world, const hkStepInfo& stepInfo)
{
    if (!world->m_wantDeactivation)
        return;

    for (int i = world->m_activeSimulationIslands.m_size - 1; i >= 0; i--)
    {
        hkSimulationIsland* island = world->m_activeSimulationIslands.m_data[i];
        if (island->shouldDeactivate(stepInfo))
            hkWorldOperationUtil_markIslandInactive(world, island);
    }
}

// @ 0x010a2ac0
void hkDefaultWorldMaintenanceMgr::performMaintenance(hkWorld* world, hkStepInfo& stepInfo)
{
    hkMonitorStream_startTimerList("LtMaint", "Split");

    hkWorldOperationUtil_splitSimulationIslands(world);

    if (stepInfo.m_startTime >= m_worldTimeResetDelay)
    {
        hkMonitorStream_startTimer("StResetTime");
        resetWorldTime(world, stepInfo);
    }

    hkMonitorStream_startTimer("StCheckDeact");
    checkDeactivation(world, stepInfo);
    hkMonitorStream_endTimer(g_monitorStreamEndMarker);
}

// =============================================================================================================
// hkBroadPhaseBorder
// =============================================================================================================
// @ 0x010a2c60
hkBroadPhaseBorder::~hkBroadPhaseBorder()
{
    for (int i = 0; i < 6; i++)
    {
        if (m_phantoms[i])
        {
            m_phantoms[i]->removeReference();
            m_phantoms[i] = 0;
        }
    }
}

// @ 0x010a2cb0
void hkBroadPhaseBorder::maxPositionExceededCallback(hkEntity* entity)
{
    switch (m_behaviour)
    {
    case BROAD_PHASE_BORDER_RAISE_ERROR:
        ((hkRigidBody*)entity)->setMotionType(7 /*HK_MOTION_FIXED*/, 1 /*HK_ENTITY_DO_ACTIVATE*/,
                                              0 /*HK_UPDATE_FILTER_ON_ENTITY_DISABLE_ENTITY_ENTITY_COLLISIONS_ONLY*/);
        break;
    case BROAD_PHASE_BORDER_CLAMP:
        ((hkRigidBody*)entity)->setMotionType(7 /*HK_MOTION_FIXED*/, 1 /*HK_ENTITY_DO_ACTIVATE*/,
                                              0 /*HK_UPDATE_FILTER_ON_ENTITY_DISABLE_ENTITY_ENTITY_COLLISIONS_ONLY*/);
        break;
    case BROAD_PHASE_BORDER_REMOVE_ENTITY:
        m_world->removeEntity(&entity, entity);
        break;
    }
}

// @ 0x010a2cf0
void hkBroadPhaseBorder::worldDeletedCallback(hkWorld* world)
{
    m_world->removeWorldDeletionListener(this);
    removeReference();
}

// @ 0x010a2d30
void hkBroadPhaseBorder::deactivate()
{
    if (!m_world)
        return;

    m_world->removePhantomBatch(m_phantoms, 6);

    for (int i = 0; i < 6; i++)
    {
        m_phantoms[i]->removeOverlapListener((hkCollidableListener*)this);
        m_phantoms[i]->removeReference();
        m_phantoms[i] = 0;
    }

    ((hkWorldDeletionListener*)this)->worldDeletedCallback(m_world);
    m_world = 0;
}

// @ 0x010a2db0
hkBroadPhaseBorder::hkBroadPhaseBorder(hkWorld* world, BroadPhaseBorderBehaviour behaviour)
    : hkReferencedObject(), hkWorldDeletionListener(), hkCollidableListener()
{
    m_world = world;
    m_behaviour = behaviour;
    addReference();
    world->addWorldDeletionListener(this);

    const hkAabb& bounds = world->m_broadPhaseBorder;
    const hkReal minX = bounds.m_min.x, minY = bounds.m_min.y, minZ = bounds.m_min.z;
    const hkReal maxX = bounds.m_max.x, maxY = bounds.m_max.y, maxZ = bounds.m_max.z;

    struct PhantomFactory
    {
        static hkAabbPhantom* create(const hkAabb& aabb, void* owner)
        {
            hkAabbPhantom* phantom = (hkAabbPhantom*)hkMemory::s_instance->allocateChunk(0xa0, 0x2e);
            phantom->m_memSizeAndFlags = 0xa0;
            new ((void*)phantom) hkAabbPhantom(aabb, 0);
            phantom->m_phantomType = 3;
            phantom->addOverlapListener(owner);
            return phantom;
        }
    };

    hkAabb aabb;
    hkAabb_set(aabb, maxX, minY, minZ, maxX, maxY, maxZ);
    m_phantoms[0] = PhantomFactory::create(aabb, this);
    world->addPhantom(m_phantoms[0]);

    hkAabb_set(aabb, minX, minY, minZ, minX, maxY, maxZ);
    m_phantoms[1] = PhantomFactory::create(aabb, this);
    world->addPhantom(m_phantoms[1]);

    hkAabb_set(aabb, minX, maxY, minZ, maxX, maxY, maxZ);
    m_phantoms[2] = PhantomFactory::create(aabb, this);
    world->addPhantom(m_phantoms[2]);

    hkAabb_set(aabb, minX, minY, minZ, maxX, minY, maxZ);
    m_phantoms[3] = PhantomFactory::create(aabb, this);
    world->addPhantom(m_phantoms[3]);

    hkAabb_set(aabb, minX, minY, maxZ, maxX, maxY, maxZ);
    m_phantoms[4] = PhantomFactory::create(aabb, this);
    world->addPhantom(m_phantoms[4]);

    hkAabb_set(aabb, minX, minY, minZ, maxX, maxY, minZ);
    m_phantoms[5] = PhantomFactory::create(aabb, this);
    world->addPhantom(m_phantoms[5]);
}

// @ 0x010a3190
void hkBroadPhaseBorder::collidableAddedCallback(const hkCollidableAddedEvent& event)
{
    hkCollidable* collidable = event.m_collidable;
    if (collidable->m_type == 1)
    {
        hkEntity* entity = collidable->getEntity();
        if (entity)
            maxPositionExceededCallback(entity);
    }
}

// =============================================================================================================
// hkHalfstepSimulation
// =============================================================================================================
// @ 0x010a31c0
int hkHalfstepSimulation::recoverFromStepFailure(hkWorld* world, int result)
{
    if (result == HK_STEP_RESULT_MEMORY_FAILURE)
        return stepDeltaTime(world, 0, m_frameDeltaTime);

    const hkReal endTime = world->m_timeOfNextPsi;
    const hkReal startTime = world->m_timeOfLastPsi;
    hkStepInfo stepInfo;
    stepInfo.m_startTime = startTime;
    stepInfo.m_endTime = endTime;
    stepInfo.m_deltaTime = endTime - startTime;
    if (stepInfo.m_deltaTime == 0.0f)
        stepInfo.m_invDeltaTime = 0;
    else
        stepInfo.m_invDeltaTime = 1.0f / stepInfo.m_deltaTime;

    world->updateCollisionFilterOnWorld(0 /*HK_UPDATE_FILTER_ON_WORLD_FULL_CHECK*/,
                                        1 /*HK_UPDATE_COLLECTION_FILTER_PROCESS_SHAPE_COLLECTIONS*/);
    if (hkMemory::s_instance->m_numUsedChunks == 1)
        return HK_STEP_RESULT_BUSY;

    restartFromStepFailure(world, stepInfo);
    if (hkMemory::s_instance->m_numUsedChunks == 1)
        return HK_STEP_RESULT_BUSY;

    m_simulationStep = 0;
    world->m_currentTime = (world->m_timeOfNextPsi + world->m_timeOfLastPsi) * 0.5f;
    return stepDeltaTime(world, 0, m_frameDeltaTime);
}

// @ 0x010a32a0
hkHalfstepSimulation::hkHalfstepSimulation()
{
    m_simulationStep = 0;
}
