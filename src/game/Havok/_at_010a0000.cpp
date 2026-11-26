// src/game/Havok/_at_010a0000.cpp -- migrated from slice(s) s0109f870, s010aed40, s010adab0, s010abb90, s010ab2d0, s010aa5f0, s010a98c0, s010a8b90, s010a7720, s010a6860, s010a3ed0, s010a32c0, s010a22b0 by tools/migrate/rewrite.py
// Object file: Havok/_at_010a0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkThreadMemoryTlsIndex;    // 0x016E4174
extern unsigned long g_hkMonitorStreamCurrentTls; // 0x016E42A4
extern unsigned long g_hkMonitorStreamEndTls;     // 0x016E42A8
extern const char* const hkNullName;    // 0
extern const char* const g_monitorStreamEndMarker;      // 0x0143CD94
#include <stddef.h>
#include <intrin.h>
#include <math.h>
#include <string.h>
#include <windows.h>

// ---- items of slice s010a22b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
typedef float hkReal;
typedef uint16_t hkUint16;
void* operator new(size_t, void* p) { return p; }
class hkBool_s010a_22b0
{
public:
    hkBool_s010a_22b0() : m_bool(0) {}
    hkBool_s010a_22b0(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
    int8_t m_bool;
};
class hkVector4_s010a_22b0 { public: float x, y, z, w; };
class hkAabb_s010a_22b0 { public: hkVector4_s010a_22b0 m_min; hkVector4_s010a_22b0 m_max; };      // 0x20
inline void hkAabb_set(hkAabb_s010a_22b0& aabb, hkReal x0, hkReal y0, hkReal z0, hkReal x1, hkReal y1, hkReal z1)
{
    aabb.m_min.x = x0; aabb.m_min.y = y0; aabb.m_min.z = z0; aabb.m_min.w = 0;
    aabb.m_max.x = x1; aabb.m_max.y = y1; aabb.m_max.z = z1; aabb.m_max.w = 0;
}
class hkStepInfo_s010a_22b0 { public: hkReal m_startTime, m_endTime, m_deltaTime, m_invDeltaTime; };   // 0x10
class hkStatisticsCollector;
class hkReferencedObject_s010a_22b0
{
public:
    hkReferencedObject_s010a_22b0() { m_referenceCount = 1; }
    virtual ~hkReferencedObject_s010a_22b0() {}
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
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual void* allocateChunk(int nbytes, int cls);
    virtual void v5();
    virtual void* onRowEmpty(int row, int cls);
    virtual void deallocateChunk(void* p, int nbytes, int cls);
    virtual void v8();

    int m_numUsedChunks;                          // +0x04 (the sticky "out of memory" flag)
    static hkMemory* s_instance;                  // 0x016E4178
};
extern unsigned long g_hkThreadMemoryTlsIndex;    // 0x016E4174
class hkThreadMemory
{ public:
    struct Elem { Elem* m_next; };
    uint32_t m_pad0[0xe];
    Elem*    m_freeListHead[17];                  // +0x38
    int      m_freeListCount[17];                 // +0x7c

    static hkThreadMemory* getInstance() { return (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }
    void deallocateChunk(void* p, int nbytes, int cls);    // 0x0107DB10
};
extern unsigned long g_hkMonitorStreamCurrentTls; // 0x016E42A4
extern unsigned long g_hkMonitorStreamEndTls;     // 0x016E42A8
static __forceinline void hkMonitorStream_startTimer(const char* name)
{
    unsigned char* end = (unsigned char*)TlsGetValue(g_hkMonitorStreamEndTls);
    unsigned char* current = (unsigned char*)TlsGetValue(g_hkMonitorStreamCurrentTls);
    if (current < end)
    {
        current = (unsigned char*)TlsGetValue(g_hkMonitorStreamCurrentTls);   // the original re-reads it for the store
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
        current = (unsigned char*)TlsGetValue(g_hkMonitorStreamCurrentTls);   // the original re-reads it for the store
        *(const char**)(current) = marker;
        volatile uint32_t t = (uint32_t)__rdtsc();
        *(uint32_t*)(current + 4) = t;
        TlsSetValue(g_hkMonitorStreamCurrentTls, current + 0xc);
    }
}
static __forceinline void hkMonitorStream_startTimerList(const char* name, const char* firstSplit)
{
    unsigned char* end = (unsigned char*)TlsGetValue(g_hkMonitorStreamEndTls);
    unsigned char* current = (unsigned char*)TlsGetValue(g_hkMonitorStreamCurrentTls);
    if (current < end)
    {
        current = (unsigned char*)TlsGetValue(g_hkMonitorStreamCurrentTls);   // the original re-reads it for the store
        *(const char**)(current) = name;
        *(const char**)(current + 0xc) = firstSplit;
        volatile uint32_t t = (uint32_t)__rdtsc();
        *(uint32_t*)(current + 4) = t;
        TlsSetValue(g_hkMonitorStreamCurrentTls, current + 0x10);
    }
}
void hkArrayUtil__reserveMore(void* array, int sizeofElem);      // 0x0107F530 (hkArrayUtil::_reserveMore)
template <typename T>
class hkArray
{ public:
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
class hkInplaceArray : public hkArray<T> { public:
    T m_storage[N];                             // +0xc
};
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
class hkUnionFind
{
public:
    void addEdge(int a, int b);                 // 0x01209540
    hkBool_s010a_22b0 isFullyConnected() const { return hkBool_s010a_22b0(m_array->m_data[0] == -m_array->m_size); }
    hkArray<int>* m_array;                      // +0
};
class hkWorld_s010a_22b0;
class hkEntity_s010a_22b0;
class hkRigidBody_s010a_22b0;
class hkPhantom_s010a_22b0;
class hkAabbPhantom;
class hkSimulationIsland_s010a_22b0;
class hkCollisionDispatcher_s010a_22b0;
class hkCollisionFilter_s010a_22b0;
struct hkProcessCollisionInput_s010a_22b0;
class hkAction_s010a_22b0;
class hkWorldDeletionListener_s010a_22b0;
struct hkCollidableAddedEvent;
class hkMultiThreadLock_s010a_22b0 { public: unsigned int m_threadId; int m_lockCount; };
struct hkAgentNnTrack_s010a_22b0                                     // 0x18 bytes
{
    hkInplaceArray<char*, 1> m_sectors;      // +0 (data, size, capacity, one inline sector ptr)
    unsigned int   m_bytesUsedInLastSector;  // +0x10
    unsigned short m_agentSize;              // +0x14
    unsigned short m_sectorSize;             // +0x16
};
class hkSimpleConstraintOwner_s010a_22b0 : public hkReferencedObject_s010a_22b0
{
public:
    int m_maxSizeOfJacobians;        // +0x08
    int m_sumSizeOfJacobians;        // +0x0c
    int m_sumSizeOfSchemas;          // +0x10
    int m_sumSizeOfMotions;          // +0x14
    int m_sumNumSolverResults;       // +0x18
};
class hkSimulationIsland_s010a_22b0 : public hkSimpleConstraintOwner_s010a_22b0      // size 0x74
{
protected:
    hkSimulationIsland_s010a_22b0(hkWorld_s010a_22b0* world);         // 0x010A2810
public:
    virtual ~hkSimulationIsland_s010a_22b0();              // 0x010A24F0
    virtual void calcStatistics(hkStatisticsCollector* collector) const;   // 0x010A22B0
    void addAction(hkAction_s010a_22b0* action);           // 0x010A24B0
    hkBool_s010a_22b0 isFullyConnected(hkUnionFind& islandLinks);   // 0x010A2590
    hkBool_s010a_22b0 shouldDeactivate(const hkStepInfo_s010a_22b0& stepInfo); // 0x010A20F0

    hkWorld_s010a_22b0* m_world;                           // +0x1c
    uint16_t m_storageIndex;                    // +0x20
    uint16_t m_dirtyListIndex;                  // +0x22
    uint8_t m_highFrequencyDeactivationCounter; // +0x24
    uint8_t m_lowFrequencyDeactivationCounter;  // +0x25
    uint8_t m_splitCheckRequested;              // +0x26
    uint8_t m_actionListCleanupNeeded;          // +0x27
    uint8_t m_active;                           // +0x28
    uint8_t m_isInActiveIslandsArray;           // +0x29
    uint16_t m_pad2a;                           // +0x2a
    hkMultiThreadLock_s010a_22b0 m_multiThreadLock;        // +0x2c
    float m_timeSinceLastHighFrequencyCheck;    // +0x34
    float m_timeSinceLastLowFrequencyCheck;     // +0x38
    hkInplaceArray<hkEntity_s010a_22b0*, 1> m_entities;    // +0x3c
    hkAgentNnTrack_s010a_22b0 m_agentTrack;                // +0x4c
    hkArray<void*> m_actions;                   // +0x64
    float m_timeOfDeactivation;                 // +0x70 (-10.0f)
};
class hkCollidable_s010a_22b0
{ public:
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

    hkEntity_s010a_22b0* getEntity() const { return (hkEntity_s010a_22b0*)((char*)this + m_entityOffset); }
};
class hkMotion_s010a_22b0
{
public:
    uint32_t m_pad00[0x5c / 4];
    hkReal   m_time;                 // +0x5c (advanced by resetWorldTime)
};
class hkMaterial_s010a_22b0 { public: uint32_t m_data[3]; };
class hkEntity_s010a_22b0
{
public:
    virtual void deallocateInternalArrays();
    virtual hkEntity_s010a_22b0* entityClone() const;
virtual void _v2();
virtual void _v3();
virtual void _v4();
virtual void _v5();
virtual void _v6();

    uint32_t m_memSizeAndFlags;                 // +4
    void* m_broadPhaseHandle;                   // +8
    uint8_t m_pad0c[0x10 - 0xc];
    uint32_t m_0x10;                            // +0x10
    uint8_t m_pad14[0x58 - 0x14];
    hkMotion_s010a_22b0*          m_motion;                // +0x58
    hkSimulationIsland_s010a_22b0* m_simulationIsland;     // +0x5c
    hkMaterial_s010a_22b0         m_material;              // +0x60
    void*              m_deactivator;           // +0x6c
    uint32_t           m_constraintsMaster[3];  // +0x70 (data, size, capacity)
    uint32_t           m_constraintsSlave[3];   // +0x7c
    uint32_t           m_constraintRuntime[3];  // +0x88
    uint16_t           m_storageIndex;          // +0x94
    uint16_t           m_processContactCallbackDelay;   // +0x96
    char               m_autoRemoveLevel;       // +0x98
    hkBool_s010a_22b0             m_fixed;                 // +0x99
    hkBool_s010a_22b0             m_isFixedOrKeyframed;    // +0x9a
    hkBool_s010a_22b0             m_internalCollideFlag;   // +0x9b
};
struct hkConstraintInstanceInternal
{
    void*      m_constraintInstance;    // +0
    hkEntity_s010a_22b0*  m_entityA;               // +4
    hkEntity_s010a_22b0*  m_entityB;               // +8
    void*      m_constraintData;        // +0xc
    uint32_t   m_pad10[3];              // +0x10
};
class hkAction_s010a_22b0
{
public:
    virtual void actionSlot0();
    virtual void actionSlot1();
    virtual void actionSlot2();
    virtual void getEntities(hkArray<hkEntity_s010a_22b0*>& entities);    // +0xc
};
class hkWorldObject_s010a_22b0 : public hkReferencedObject_s010a_22b0
{
public:
    void removeReference();             // 0x0109AE60 (?removeReference@hkWorldObject@@QAEXXZ)
    hkWorld_s010a_22b0* m_world;                   // +8
};
class hkPhantom_s010a_22b0 : public hkWorldObject_s010a_22b0
{
public:
    void addOverlapListener(void* listener);        // 0x0108E4A0
    void removeOverlapListener(void* listener);     // 0x0108E450
    uint32_t m_pad0c[0x34 / 4 - 3];
    uint8_t  m_phantomType;                         // +0x34
};
class hkAabbPhantom : public hkPhantom_s010a_22b0
{
public:
    hkAabbPhantom(const hkAabb_s010a_22b0& aabb, uint32_t collisionFilterInfo);    // 0x0108DFE0
};
struct hkProcessCollisionInput_s010a_22b0
{ private:
public:
    void* m_dispatcher;                 // +0
    void* m_filter;                     // +4
    float m_tolerance;                  // +8
    hkBool_s010a_22b0 m_createPredictiveAgents;    // +0xc
    uint8_t m_pad0d[3];
    hkStepInfo_s010a_22b0 m_stepInfo;              // +0x10
};
struct hkWorldDynamicsStepInfo_s010a_22b0
{
    hkStepInfo_s010a_22b0 m_stepInfo;              // +0
    uint32_t   m_solverInfo[0x140 / 4];
};
class hkSimulation : public hkReferencedObject_s010a_22b0
{
public:
    virtual int  stepDeltaTime(hkWorld_s010a_22b0* world, hkReal physicsDeltaTime, hkReal frameDeltaTime);   // slot 2
virtual int  simSlot3();
virtual void simSlot4();
virtual void simSlot5();
virtual void simSlot6();
virtual void simSlot7();
virtual void simSlot8();
virtual void simSlot9();
virtual void simSlot10();
virtual void simSlot11();
virtual void simSlot12();
    virtual void simSlot13(hkWorld_s010a_22b0* world, hkReal advance);            // +0x34
};
class hkWorld_s010a_22b0 : public hkReferencedObject_s010a_22b0
{
public:
    hkSimulation*        m_simulation;                  // +0x08
    hkReal               m_currentTime;                 // +0x0c
    hkReal               m_timeOfNextFrame;             // +0x10
    hkReal               m_timeOfLastPsi;               // +0x14
    hkReal               m_timeOfNextPsi;               // +0x18
    uint32_t             m_pad1c;
    hkVector4_s010a_22b0            m_gravity;                     // +0x20
    hkSimulationIsland_s010a_22b0*  m_fixedIsland;                 // +0x30
    hkRigidBody_s010a_22b0*         m_fixedRigidBody;              // +0x34
    hkArray<hkSimulationIsland_s010a_22b0*> m_activeSimulationIslands;     // +0x38
    hkArray<hkSimulationIsland_s010a_22b0*> m_inactiveSimulationIslands;   // +0x44
    hkArray<hkSimulationIsland_s010a_22b0*> m_dirtySimulationIslands;      // +0x50
    void*                m_maintenanceMgr;              // +0x5c
    void*                m_memoryWatchDog;              // +0x60
    void*                m_broadPhase;                  // +0x64
    void*                m_broadPhaseDispatcher;        // +0x68
    void*                m_phantomBroadPhaseListener;   // +0x6c
    void*                m_entityEntityBroadPhaseListener;  // +0x70
    void*                m_broadPhaseBorderListener;    // +0x74
    hkProcessCollisionInput_s010a_22b0* m_collisionInput;          // +0x78
    hkCollisionFilter_s010a_22b0*   m_collisionFilter;             // +0x7c
    hkCollisionDispatcher_s010a_22b0* m_collisionDispatcher;       // +0x80
    void*                m_pendingOperations;           // +0x84
    int                  m_pendingOperationsCount;      // +0x88
    int                  m_lockCount;                   // +0x8c
    int                  m_lockCountForPhantoms;        // +0x90
    hkBool_s010a_22b0               m_blockExecutingPendingOperations;     // +0x94
    hkBool_s010a_22b0               m_criticalOperationsAllowed;   // +0x95
    uint16_t             m_pad96;
    void*                m_pendingOperationQueues;      // +0x98
    int                  m_pendingOperationQueueCount;  // +0x9c
    hkMultiThreadLock_s010a_22b0    m_multiThreadLock;             // +0xa0
    hkBool_s010a_22b0               m_processActionsInSingleThread;    // +0xa8
    uint8_t              m_pada9[3];
    void*                m_modifyConstraintCriticalSection; // +0xac
    void*                m_worldLock;                   // +0xb0
    hkBool_s010a_22b0               m_wantSimulationIslands;       // +0xb4
    hkBool_s010a_22b0               m_wantDeactivation;            // +0xb5
    hkBool_s010a_22b0               m_shouldActivateOnRigidBodyTransformChange;    // +0xb6
    uint8_t              m_padb7;
    hkReal               m_highFrequencyDeactivationPeriod;     // +0xb8
    hkReal               m_lowFrequencyDeactivationPeriod;      // +0xbc
    hkReal               m_toiCollisionResponseRotateNormal;    // +0xc0
    int                  m_simulationType;              // +0xc4
    unsigned int         m_lastEntityUid;               // +0xc8
    hkArray<hkPhantom_s010a_22b0*>  m_phantoms;                    // +0xcc
    uint32_t             m_pad0d8[0x170 / 4 - 0xd8 / 4];   // +0xd8..+0x170
    hkWorldDynamicsStepInfo_s010a_22b0 m_dynamicsStepInfo;         // +0x170
    hkAabb_s010a_22b0               m_broadPhaseBorder;            // +0x2c0
    int                  m_broadPhaseNumMarkers;        // +0x2e0

    void addWorldDeletionListener(hkWorldDeletionListener_s010a_22b0* listener);   // 0x01083530
    void removeWorldDeletionListener(hkWorldDeletionListener_s010a_22b0* listener);   // 0x01082A40
    hkPhantom_s010a_22b0* addPhantom(hkPhantom_s010a_22b0* phantom);          // 0x01083320
    void removePhantomBatch(hkPhantom_s010a_22b0** phantoms, int numPhantoms);     // 0x01086500
    void removeEntity(void* tmp, hkEntity_s010a_22b0* entity);     // 0x01083110
    void updateCollisionFilterOnWorld(int updateMode, int updateShapeCollections);   // 0x010869E0
};
class hkRigidBody_s010a_22b0 : public hkEntity_s010a_22b0
{
public:
    void setMotionType(int newState, int preferredActivationState, int collisionFilterUpdateMode);   // 0x01087520
};
class hkWorldDeletionListener_s010a_22b0
{
public:
    virtual ~hkWorldDeletionListener_s010a_22b0() {}
    virtual void worldDeletedCallback(hkWorld_s010a_22b0* world);
};
struct hkCollidableAddedEvent
{
    void* m_0;                      // +0
    hkCollidable_s010a_22b0* m_collidable;     // +4
};
class hkCollidableListener
{
public:
    ~hkCollidableListener() {}
    virtual void collidableAddedCallback(const hkCollidableAddedEvent& event);
    virtual void collidableRemovedCallback(const void* event);
};
class hkDefaultWorldMaintenanceMgr : public hkReferencedObject_s010a_22b0
{
public:
    hkDefaultWorldMaintenanceMgr();                                     // 0x010A2910
    virtual void init(hkWorld_s010a_22b0* world);                                  // 0x010A28F0
    virtual void performMaintenance(hkWorld_s010a_22b0* world, hkStepInfo_s010a_22b0& stepInfo);   // 0x010A2AC0

    void resetWorldTime(hkWorld_s010a_22b0* world, hkStepInfo_s010a_22b0& stepInfo);          // 0x010A2960
    void checkDeactivation(hkWorld_s010a_22b0* world, const hkStepInfo_s010a_22b0& stepInfo);// 0x010A2A70

    hkReal m_worldTimeOffset;           // +0x08 (33.0f)
    hkReal m_worldTimeResetDelay;       // +0x0c (63.0f)
};
enum BroadPhaseBorderBehaviour
{
    BROAD_PHASE_BORDER_RAISE_ERROR = 0,
    BROAD_PHASE_BORDER_CLAMP = 1,
    BROAD_PHASE_BORDER_REMOVE_ENTITY = 2
};
class hkBroadPhaseBorder : public hkReferencedObject_s010a_22b0, public hkWorldDeletionListener_s010a_22b0, public hkCollidableListener
{
public:
    hkBroadPhaseBorder(hkWorld_s010a_22b0* world, BroadPhaseBorderBehaviour behaviour);   // 0x010A2DB0
    virtual ~hkBroadPhaseBorder();                                              // 0x010A2C60
    virtual void maxPositionExceededCallback(hkEntity_s010a_22b0* entity);                 // 0x010A2CB0 (slot 2)
    virtual void deactivate();                                                  // 0x010A2D30 (slot 3)
    virtual void worldDeletedCallback(hkWorld_s010a_22b0* world);                          // 0x010A2CF0
    virtual void collidableAddedCallback(const hkCollidableAddedEvent& event);  // 0x010A3190

    hkWorld_s010a_22b0*   m_world;                 // +0x10
    hkPhantom_s010a_22b0* m_phantoms[6];           // +0x14
    int        m_behaviour;             // +0x2c
};
void hkWorldOperationUtil_splitSimulationIslands(hkWorld_s010a_22b0* world);                   // 0x010A1320
void hkAgentMachineUtil_calcNnStatisticsContactMgrsOnly(const hkAgentNnTrack_s010a_22b0& track, hkStatisticsCollector* collector);   // 0x010FCF90
void hkAgentMachineUtil_calcNnStatistics(const hkAgentNnTrack_s010a_22b0& track, hkStatisticsCollector* collector);   // 0x010FCEB0
extern const char* const hkNullName;    // 0
extern const char* const g_monitorStreamEndMarker;      // 0x0143CD94
// ---- items of slice s010a22b0 end

// ---- items of slice s010a32c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void _hkAgentNnMachine_GetAgentType(const void* a, const void* b, void* world, void* agentTypeOut, void* flippedOut);   // 0x010fb8f0
typedef int8_t hkInt8;
class hkBool_s010a_32c0
{
public:
    hkBool_s010a_32c0() : m_bool(0) {}
    hkBool_s010a_32c0(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
    int8_t m_bool;
};
class hkReferencedObject_s010a_32c0
{
public:
    hkReferencedObject_s010a_32c0() { m_referenceCount = 1; }
    virtual ~hkReferencedObject_s010a_32c0() {}
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
struct __declspec(align(16)) hkVector4_s010a_32c0 { float x, y, z, w; };
class hkMatrix3_s010a_32c0 {  // mul at 0x01081bb0
    public: hkVector4_s010a_32c0 m_col0, m_col1, m_col2;
    void mul(hkReal v);
};
class hkStepInfo_s010a_32c0 { public: hkReal m_startTime, m_endTime, m_deltaTime, m_invDeltaTime; };
namespace hkMath {
 float atan2fApproximation(float y, float x);   // 0x0120adb0
}
class hkMemory_s010a_32c0
{
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
    virtual void* allocateChunk(int nbytes, int cls);
    virtual void v5();
    virtual void* onRowEmpty(int row, int cls);
    virtual void deallocateChunk(void* p, int nbytes, int cls);
    virtual void v8();

    int m_numUsedChunks;                            // +0x04 (the sticky "out of memory" flag)
    int m_rowSize;                                  // +0x08
    int m_numBytesAllocated;                        // +0x14
    int m_numBytesAllocated2;                       // +0x28
    static hkMemory_s010a_32c0* s_instance;                    // 0x016e4178
};
class hkThreadMemory_s010a_32c0
{ public:
    struct Elem { Elem* m_next; };
    uint32_t m_pad0[0xe];
    Elem*    m_freeListHead[17];    // +0x38
    int      m_freeListCount[17];   // +0x7c

    static hkThreadMemory_s010a_32c0* getInstance() { return (hkThreadMemory_s010a_32c0*)TlsGetValue(g_hkThreadMemoryTlsIndex); }
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
        return hkMemory_s010a_32c0::s_instance->onRowEmpty(row, cls);
    }
};
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
class hkWorld_s010a_32c0;
class hkSimulation_s010a_32c0 : public hkReferencedObject_s010a_32c0          // 0xc
{
public:
    hkSimulation_s010a_32c0() {}
    virtual void simSlot0();
    virtual void simSlot1();
    virtual void step(hkWorld_s010a_32c0* world, const hkStepInfo_s010a_32c0& stepInfo, hkReal invDeltaTime);
    hkWorld_s010a_32c0* m_world;                       // +0x08
};
class hkAsynchronousSimulation : public hkSimulation_s010a_32c0    // 0x10
{
public:
    hkAsynchronousSimulation() { m_synchronizeFrameAndPhysicsTime.m_bool = 1; }
    hkBool_s010a_32c0 m_synchronizeFrameAndPhysicsTime;    // +0x0c
};
enum hkStepResult { HK_STEP_RESULT_SUCCESS = 0, HK_STEP_RESULT_MEMORY_FAILURE = 1, HK_STEP_RESULT_BUSY = 2 };
struct hkWorldDynamicsStepInfo_s010a_32c0
{
    hkStepInfo_s010a_32c0 m_stepInfo;                  // +0x00
    uint32_t   m_solverInfo[0x140 / 4];     // +0x10
};
class hkHalfstepSimulation : public hkAsynchronousSimulation   // 0x14
{
public:
    hkHalfstepSimulation();                 // 0x010a32a0
    virtual hkStepResult stepDeltaTime(hkWorld_s010a_32c0* world, hkReal physicsDeltaTime, hkReal frameDeltaTime);
    hkReal m_frameDeltaTime;                // +0x10
    int    m_simulationStep;                // +0x10 (slot reused: frame delta, then the half-step flag)
};
class hkSimulationIsland_s010a_32c0;
class hkRigidBody_s010a_32c0;
class hkBroadPhase;
class hkProcessCollisionInput_s010a_32c0;
class hkCollisionFilter_s010a_32c0;
class hkCollisionDispatcher_s010a_32c0;
class hkContactMgrFactory;
class hkWorldOperationQueue;
class hkEntity_s010a_32c0;
class hkMultiThreadLock_s010a_32c0 { public: unsigned int m_threadId; int m_lockCount; };
class hkWorld_s010a_32c0 : public hkReferencedObject_s010a_32c0             // 0x2f0
{
public:
    hkSimulation_s010a_32c0*                     m_simulation;                 // +0x08
    hkReal                            m_currentTime;                // +0x0c
    hkReal                            m_timeOfNextFrame;            // +0x10
    hkReal                            m_timeOfLastPsi;              // +0x14
    hkReal                            m_timeOfNextPsi;              // +0x18
    uint32_t                          m_pad1c;
    hkVector4_s010a_32c0                         m_gravity;                    // +0x20
    hkSimulationIsland_s010a_32c0*               m_fixedIsland;                // +0x30
    hkRigidBody_s010a_32c0*                      m_fixedRigidBody;             // +0x34
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
    hkProcessCollisionInput_s010a_32c0*          m_collisionInput;             // +0x78
    hkCollisionFilter_s010a_32c0*                m_collisionFilter;            // +0x7c
    hkCollisionDispatcher_s010a_32c0*            m_collisionDispatcher;        // +0x80
    hkWorldOperationQueue*            m_pendingOperations;          // +0x84
    int                               m_pendingOperationsCount;     // +0x88
    int                               m_lockCount;                  // +0x8c
    int                               m_lockCountForPhantoms;       // +0x90
    hkBool_s010a_32c0                            m_blockExecutingPendingOperations;  // +0x94
    hkBool_s010a_32c0                            m_criticalOperationsAllowed;  // +0x95
    uint16_t                          m_pad96;
    void*                             m_pendingOperationQueues;     // +0x98
    int                               m_pendingOperationQueueCount; // +0x9c
    hkMultiThreadLock_s010a_32c0                 m_multiThreadLock;            // +0xa0
    hkBool_s010a_32c0                            m_processActionsInSingleThread;     // +0xa8
    uint8_t                           m_pada9[3];
    void*                             m_modifyConstraintCriticalSection;  // +0xac
    void*                             m_worldLock;                  // +0xb0
    hkBool_s010a_32c0                            m_wantSimulationIslands;      // +0xb4
    hkBool_s010a_32c0                            m_wantDeactivation;           // +0xb5
    hkBool_s010a_32c0                            m_shouldActivateOnRigidBodyTransformChange;   // +0xb6
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
    hkWorldDynamicsStepInfo_s010a_32c0           m_dynamicsStepInfo;           // +0x170
    uint32_t                          m_broadPhaseExtents[8];       // +0x2c0
    int                               m_broadPhaseNumMarkers;       // +0x2e0
    int                               m_broadPhaseQuerySize;        // +0x2e4
    int                               m_broadPhaseUpdateSize;       // +0x2e8
    hkInt8                            m_contactPointGeneration;     // +0x2ec
};
class hkCollidable_s010a_32c0
{ public:
    virtual ~hkCollidable_s010a_32c0();
    void* m_broadPhaseHandle;                  // +0x04
    void* m_shape;                             // +0x08
    void* m_motion;                            // +0x0c
    void* m_entity;                            // +0x10
};
class hkLinkedCollidable_s010a_32c0 : public hkCollidable_s010a_32c0 { public:
    void* m_pairInfo[2];                       // +0x14
};
struct hkAgentNnEntry_s010a_32c0                                          // 0x1c bytes (retail)
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
    hkLinkedCollidable_s010a_32c0* m_collidable[2];    // +0x14
};
class hkBroadPhaseHandle_s010a_32c0
{ public:
    virtual ~hkBroadPhaseHandle_s010a_32c0();
};
class hkTypedBroadPhaseHandle_s010a_32c0 : public hkBroadPhaseHandle_s010a_32c0 { public:
    int8_t m_type;                             // +0x04
    int8_t m_ownerOffset;                      // +0x05 (the original walks it as a signed byte)
    uint16_t m_objectQualityType;              // +0x06
    uint32_t m_collisionFilterInfo;            // +0x08
};
struct hkBroadPhasePair
{
    hkBroadPhaseHandle_s010a_32c0* m_a;                   // +0
    hkBroadPhaseHandle_s010a_32c0* m_b;                   // +4
    uint32_t m_0x8;
    uint32_t m_0xc;
};
struct hkAgentNnTrack_s010a_32c0                                          // 0x18 bytes
{
    char** m_sectorData;           // +0
    int m_numSectors;              // +4
    int m_sectorCapacity;          // +8
    char* m_inlineSector;          // +0xc
    unsigned int m_bytesUsedInLastSector;   // +0x10
    unsigned short m_agentSize;    // +0x14
    unsigned short m_sectorSize;   // +0x16
};
class hkMaterial_s010a_32c0 { public: uint32_t m_data[3]; };
class hkEntity_s010a_32c0
{
public:
    virtual void deallocateInternalArrays();
    virtual hkEntity_s010a_32c0* entityClone() const;
virtual void _v2();
virtual void _v3();
virtual void _v4();
virtual void _v5();
virtual void _v6();

    // the virtuals above put the compiler's vfptr at +0; only the reference-count word that follows it belongs here
    uint32_t m_memSizeAndFlags;                 // +4
    void* m_broadPhaseHandle;                   // +8
    uint8_t m_pad0c[0x10 - 0xc];
    uintptr_t m_0x10;                           // +0x10
    uint8_t m_pad14[0x58 - 0x14];
    void*              m_motion;                // +0x58
    hkSimulationIsland_s010a_32c0* m_simulationIsland;     // +0x5c
    hkMaterial_s010a_32c0         m_material;              // +0x60
    void*              m_deactivator;           // +0x6c
    uint32_t           m_constraintsMaster[3];  // +0x70
    uint32_t           m_constraintsSlave[3];   // +0x7c
    uint32_t           m_constraintRuntime[3];  // +0x88
    uint16_t           m_storageIndex;          // +0x94
    uint16_t           m_processContactCallbackDelay;   // +0x96
    char               m_autoRemoveLevel;       // +0x98
    hkBool_s010a_32c0             m_fixed;                 // +0x99
    hkBool_s010a_32c0             m_isFixedOrKeyframed;    // +0x9a
    hkBool_s010a_32c0             m_internalCollideFlag;   // +0x9b
};
class hkSimulationIsland_s010a_32c0 : public hkReferencedObject_s010a_32c0          // 0x74 bytes (retail)
{
public:
    int m_maxSizeOfJacobians;           // +0x08
    int m_sumSizeOfJacobians;           // +0x0c
    int m_sumSizeOfSchemas;             // +0x10
    int m_sumSizeOfMotions;             // +0x14
    int m_sumNumSolverResults;          // +0x18
    hkWorld_s010a_32c0* m_world;                   // +0x1c
    uint16_t m_storageIndex;            // +0x20
    uint16_t m_dirtyListIndex;          // +0x22
    uint8_t m_highFrequencyDeactivationCounter;   // +0x24
    uint8_t m_lowFrequencyDeactivationCounter;    // +0x25
    hkBool_s010a_32c0 m_splitCheckRequested;       // +0x26
    hkBool_s010a_32c0 m_actionListCleanupNeeded;   // +0x27
    hkBool_s010a_32c0 m_active;                    // +0x28
    hkBool_s010a_32c0 m_isInActiveIslandsArray;    // +0x29
    uint16_t m_pad2a;
    hkMultiThreadLock_s010a_32c0 m_multiThreadLock;    // +0x2c
    hkReal m_timeSinceLastHighFrequencyCheck;   // +0x34
    hkReal m_timeSinceLastLowFrequencyCheck;    // +0x38
    hkEntity_s010a_32c0** m_entityData;            // +0x3c
    int m_numEntities;                  // +0x40
    int m_entityCapacity;               // +0x44
    hkEntity_s010a_32c0* m_inlineEntity;           // +0x48
    hkAgentNnTrack_s010a_32c0 m_agentTrack;        // +0x4c
};
class hkCollisionDispatcher_s010a_32c0                    // hkReferencedObject; only the tail tables matter here
{ public:
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
class hkEntityEntityBroadPhaseListener
{
public:
    hkEntityEntityBroadPhaseListener(hkWorld_s010a_32c0* world);
    virtual void addCollisionPair(const hkBroadPhasePair& pair);
    virtual void removeCollisionPair(const hkBroadPhasePair& pair);

    uint16_t m_pad04;                   // +4
    uint16_t m_objectQualityType;       // +6
    hkWorld_s010a_32c0* m_world;                   // +8
};
extern "C" void _hkAgentNnMachine_CreateAgent(hkAgentNnTrack_s010a_32c0* track, const void* a, const void* b, void* agentType, void* world, void* createArg);   // 0x010fbdb0
extern "C" void _hkAgentNnMachine_DestroyAgent(hkAgentNnTrack_s010a_32c0* track, hkAgentNnEntry_s010a_32c0* entry, hkCollisionDispatcher_s010a_32c0* dispatcher);   // 0x010fbf80
void hkWorld_integrateIslandsEntityMotion(hkWorld_s010a_32c0* world, hkReal startTime, hkReal endTime, hkReal invDeltaTime);     // 0x01099690
void hkWorld_performBroadphaseAndCollisionDetection(hkWorld_s010a_32c0* world, hkReal startTime, hkReal endTime, hkReal invDeltaTime);   // 0x0109a200
void hkWorldCallbackUtil_firePostSimulationCallback(hkWorld_s010a_32c0* world, hkReal startTime, hkReal endTime, hkReal invDeltaTime);   // 0x0109f5a0
void hkWorld_markIslandDirtyThreadSafe(hkWorld_s010a_32c0* world, hkSimulationIsland_s010a_32c0* islandA, hkSimulationIsland_s010a_32c0* islandB);   // 0x010a1170
int  hkWorld_calcMaxIslandSizeEstimate(const hkWorld_s010a_32c0* world);   // 0x01082ca0
int  hkMemoryWatchdog_getUsedMemory();                          // 0x01083060
int  hkMemoryWatchdog_getMaxAllowedMemory();                    // 0x01083080
void hkWorld_integrateIslandsAtPsi(hkWorld_s010a_32c0* world, const hkStepInfo_s010a_32c0& stepInfo, hkReal invDeltaTime);   // hkWorld.inl (through m_dynamicsStepInfo)
void hkWorldAgentUtil_addAgent(hkAgentNnEntry_s010a_32c0* entryA, hkAgentNnEntry_s010a_32c0* entryB, hkCollisionDispatcher_s010a_32c0* dispatcher);   // 0x010a3920
void hkWorldAgentUtil_removeAgent(hkAgentNnEntry_s010a_32c0* entry);   // 0x010a39f0
struct hkConstraintInfo
{
    int m_maxSizeOfJacobians;      // +0x00
    int m_sizeOfJacobians;         // +0x04
    int m_sizeOfSchemas;           // +0x08
    int m_numSolverResults;        // +0x0c
};
struct hkConstraintData_s010a_32c0;      // +0x2c/+0x30/+0x3c used by the mass changer and the base info size calc
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
struct hkConstraintQueryOut
{
    void* m_accumulatorBufferRoot;     // +0x00
    void* m_jacobianBufferRoot;        // +0x04
};
struct hkSimpleConstraintInfoInitInput
{
    uint8_t  m_pad00[0x10];
    hkMatrix3_s010a_32c0 m_transform;             // +0x10 (scaled by the mass)
    hkReal    m_scale;                 // +0x40 (scaled by the mass)
};
struct hkBodyVelocity
{
    hkVector4_s010a_32c0 m_linearVelocity;        // +0x00
    hkVector4_s010a_32c0 m_angularVelocity;       // +0x10
    uint8_t   m_pad20[0x20];
};
struct hkConstraintInstance_s010a_32c0;
class hkConstraintData_s010a_32c0
{
public:
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
virtual void c4();
    virtual void getConstraintInfo(hkConstraintInfo& info) const;      // 0x010a3e70 (base impl)
virtual void c6();
virtual void c7();
virtual void c8();
virtual void c9();
virtual void c10();
virtual void c11();
virtual void c12();
    uint32_t m_pad04;
    uint32_t m_userData;               // +0x08
    uint8_t  m_pad0c[0x2c - 0x0c];
    hkReal   m_minLinearMass;          // +0x2c (hkMassChangerConstraintData)
    hkReal   m_maxLinearMass;          // +0x30
    uint8_t  m_pad34[0x3c - 0x34];
    int      m_numSolverElemTemps;     // +0x3c

    void addInstance(hkConstraintInstance_s010a_32c0* instance, void* runtime, int sizeOfRuntime) const;   // 0x010a3a70
};
class hkMassChangerConstraintData : public hkConstraintData_s010a_32c0
{
public:
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
virtual void c4();
    virtual void getConstraintInfo(hkConstraintInfo& info) const;      // 0x010a3c10
virtual void c6();
virtual void c7();
virtual void c8();
virtual void c9();
virtual void c10();
virtual void c11();
virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);
    virtual void toiCollisionResponseBeginCallback(const void* cp, hkSimpleConstraintInfoInitInput& bodyA,
            hkSimpleConstraintInfoInitInput& bodyB, hkBodyVelocity& velA, hkBodyVelocity& velB);   // 0x010a3c40
};
void hkInitQueryOut(hkConstraintQueryIn& in, int sizeOfExternalRuntime, int numSolverResults,
        hkConstraintQueryOut& out);                                              // 0x010a76d0
void hkSetInvMassBuildJacobian(const hkVector4_s010a_32c0& invMassA, const hkVector4_s010a_32c0& invMassB,
        hkConstraintQueryIn& in, hkConstraintQueryOut& out);                     // 0x010acb50
void hkSimpleContactConstraintData_buildJacobian(void* self, const hkConstraintQueryIn& in,
        hkConstraintQueryOut& out);                                              // 0x010a3ed0
// ---- items of slice s010a32c0 end

// ---- items of slice s010a3ed0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#if defined(_WIN32)
#endif
typedef double hkX87Real;
typedef uint8_t hkUint8;
class hkBool_s010a_3ed0
{
public:
	hkBool_s010a_3ed0(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
private:
	char m_bool;
};
struct hkArrayUtil
{
	static void _reserveMore(void* array, int elemSize);                                       // 0x0107F530
	static void _reduce(void* array, int elemSize, void* inplaceStorage, int inplaceCapacity); // 0x0107F5D0
};
template <typename T>
class hkArray_s010a_3ed0
{ public:
	enum { CAPACITY_MASK = 0x3FFFFFFF };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	// Inlined hkArray::expandOne(): reserve (growth) when full, then bump the size.
	T* expandOne()
	{
		if (m_size == (m_capacityAndFlags & CAPACITY_MASK))
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		T* p = m_data + m_size;
		++m_size;
		return p;
	}
};
class hkVector4_s010a_3ed0 { public: float x, y, z, w; };
class hkContactPoint_s010a_3ed0
{ public:
	hkVector4_s010a_3ed0 m_position;           // +0
	hkVector4_s010a_3ed0 m_separatingNormal;   // +0x10 (w = separating distance)
};
class hkContactPointProperties
{ public:
	float m_solverData0;            // +0   (inferred) scratch written by buildJacobian
	float m_solverData1;            // +4   (inferred)
	int m_userData;                 // +8   start of the part handed to callbacks
	hkUint16 m_friction;            // +0xc (inferred) fixed point, scaled by 1/256
	hkUint8 m_restitution;          // +0xe (inferred) fixed point, scaled by 1/128
	hkUint8 m_flags;                // +0xf bit0 = needs update, bit1 = in solver
	float m_solverData4;            // +0x10 (inferred)
};
struct hkContactPointPropertiesPublic { int m_userData; hkUint16 m_friction; hkUint8 m_restitution; hkUint8 m_flags; };
class hkConstraintInstance_s010a_3ed0;
class hkCollidable_s010a_3ed0 { public: char m_pad[1]; };
class hkCriticalSection_s010a_3ed0
{ public:
	void enter();                    // 0x0107F820
	char m_cs[24];
	uint64_t m_owner;                // +0x18, thread id while locked, -1 otherwise
	void leave()
	{
#if defined(_WIN32)
		m_owner = (uint64_t)-1;      // two dword stores of -1 in the binary
		LeaveCriticalSection((LPCRITICAL_SECTION)m_cs);
#endif
	}
};
struct hkSolverInfoWorld { char m_pad[0x70]; float m_contactRestingVelocity; };   // (inferred) float at +0x70
struct hkCollisionInputStub { char m_pad[0x24]; hkSolverInfoWorld* m_dynamicsInfo; }; // +0x24
class hkWorld_s010a_3ed0
{ public:
	char m_pad0[0x78];
	hkCollisionInputStub* m_collisionInput;  // +0x78
};
struct hkWorldStub2
{
	char m_pad[0xac];
	hkCriticalSection_s010a_3ed0* m_modifyConstraintCriticalSection;   // +0xac
};
struct hkOwnerStub
{
virtual void v0();
virtual void v1();
virtual void v2();
	virtual void addConstraintInfo(hkConstraintInstance_s010a_3ed0* c, hkConstraintInfo& info);   // slot 3
	virtual void subConstraintInfo(hkConstraintInstance_s010a_3ed0* c, hkConstraintInfo& info);   // slot 4
	uint32_t m_pad[6];                 // +4..+0x1b (x86)
	hkWorldStub2* m_world;             // +0x1c
};
class hkMotion_s010a_3ed0;
struct hkEntityStub;
struct hkContactPointConfirmedEvent
{
	hkCollidable_s010a_3ed0* m_collidableA;                      // +0 (entityA + 0x1c)
	hkCollidable_s010a_3ed0* m_collidableB;                      // +4 (entityB + 0x1c)
	void* m_unused;                                   // +8 (never written here)
	hkContactPoint_s010a_3ed0* m_contactPoint;                   // +0xc
	hkContactPointPropertiesPublic* m_properties;     // +0x10 (props + 8)
	int m_firstCallbackForFullManifold;               // +0x14 (0 here)
	float m_projectedVelocity;                        // +0x18
	int m_isConstraintCallback;                       // +0x1c (1 here)
	void* m_constraintData;                           // +0x20 (the hkSimpleContactConstraintData)
};
struct hkSimpleConstraintUtilCollideParams
{
	hkVector4_s010a_3ed0 m_normalAndDistance;     // +0
	float m_friction;                  // +0x10
	float m_restitution;               // +0x14
	float m_velocityAlongNormal;       // +0x18
	float m_externalSeparatingVelocity;// +0x1c (0 here)
	float m_extraSeparatingVelocity;   // +0x20 (0 here)
};
class hkVelocityAccumulator;
struct hkStepInfo_s010a_3ed0;
class hkMotion_s010a_3ed0
{ public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
	virtual hkVelocityAccumulator* buildAccumulator(const hkStepInfo_s010a_3ed0& stepInfo, hkVelocityAccumulator* acc);   // slot 5 (inferred)
	virtual void integrateFromAccumulator(const hkStepInfo_s010a_3ed0& stepInfo, hkVelocityAccumulator* acc);              // slot 6 (inferred)
	virtual int getSizeOfAccumulators();                                                                         // slot 7 (inferred)
	int m_pad4;                        // +4 (non-virtual field slot before the accumulator offset)
	int m_accumulatorOffset;           // +8
	char m_pad[0xc0 - 0xc];
	float m_inverseMass;               // +0xc0
	char m_pad2[0xd0 - 0xc4];
	hkVector4_s010a_3ed0 m_linearVelocity;        // +0xd0
	hkVector4_s010a_3ed0 m_angularVelocity;       // +0xe0
};
struct hkEntityStub
{
	char m_pad0[8];
	hkWorld_s010a_3ed0* m_world;                  // +8
	char m_pad1[0x1c - 0xc];
	hkCollidable_s010a_3ed0 m_collidable;         // +0x1c (address of this member is passed)
	char m_pad2[0x58 - 0x1d];
	hkMotion_s010a_3ed0* m_motion;                // +0x58
	char m_pad3[0xa0 - 0x5c];
	void* m_contactListeners;          // +0xa0 first dword of the listener array (tested for non-zero)
};
class hkConstraintInstance_s010a_3ed0
{ public:
	char m_pad0[8];
	hkOwnerStub* m_owner;              // +8 (hkSimpleConstraintOwner / simulation island)
	char m_pad1[4];
	hkEntityStub* m_entities[2];       // +0x10, +0x14
};
class hkVelocityAccumulator
{ public:
	hkUint8 m_type;                    // +0
	char m_pad1[0xf];
	float m_linearVelocity[4];         // +0x10
	float m_angularVelocity[4];        // +0x20
	char m_pad2[0x10];
	float m_stored[8];                 // +0x40: oneStepIntegrate stores the 8 floats of +0x10..+0x2f here; the
	                                   //        contact code reads the centre of mass at +0x40..+0x48 (inferred)
	char m_pad3[0x80 - 0x60];
};
class hkConstraintQueryIn_s010a_3ed0
{ public:
	float m_deltaTime;                              // +0 (inferred: multiplies the -1.3 factor)
	char m_pad4[0x18 - 4];
	float m_softScaledA;                            // +0x18 scaled by hkSoftContactConstraintData (inferred)
	char m_pad1c[0x20 - 0x1c];
	hkVelocityAccumulator* m_bodyBuffer;            // +0x20 (inferred: accumulator buffer base)
	void* m_jacobianBuffer;                         // +0x24 (inferred: jacobian element buffer)
	hkVelocityAccumulator* m_accumulatorA;          // +0x28
	hkVelocityAccumulator* m_accumulatorB;          // +0x2c
	void* m_motionStateA;                           // +0x30
	void* m_motionStateB;                           // +0x34
	float m_softScaledB;                            // +0x38 (inferred)
	float m_softScaledC;                            // +0x3c (inferred)
	hkConstraintInstance_s010a_3ed0* m_constraintInstance;     // +0x40
	int m_constraintFlags;                          // +0x44
};
struct hkJacobianSchema;
struct hkJacobianElement;
struct hkConstraintQueryOut_s010a_3ed0
{
	hkJacobianElement* m_jacobians;    // +0
	hkJacobianSchema* m_schemas;       // +4
};
struct hkIdMgrA : hkArray_s010a_3ed0<hkUint8>
{
	int newUid(hkUint8 value);          // 0x010A4290 (name inferred)
};
class hkConstraintData_s010a_3ed0
{
public:
	virtual ~hkConstraintData_s010a_3ed0() {}          // slot 0
	virtual void slot1() {}                 // slot 1 (empty, hkReferencedObject)
	virtual void slot2();
	virtual void slot3();
	virtual void getRuntimeInfo();          // slot 4 (signature elided)
	virtual void slot5();
	virtual void addInstance(void*);        // slot 6 (signature elided)
	virtual void buildJacobian(const hkConstraintQueryIn_s010a_3ed0& in, hkConstraintQueryOut_s010a_3ed0& out);   // slot 7
	short m_memSizeAndFlags;                // +4
	short m_referenceCount;                 // +6
};
class hkSimpleContactConstraintData : public hkConstraintData_s010a_3ed0
{
public:
	hkSimpleContactConstraintData();                                    // 0x010A4620
	hkSimpleContactConstraintData(hkConstraintInstance_s010a_3ed0* constraint);    // 0x010A45B0
	virtual void buildJacobian(const hkConstraintQueryIn_s010a_3ed0& in, hkConstraintQueryOut_s010a_3ed0& out);   // 0x010A3ED0
	hkUint16 allocateContactPoint(hkContactPoint_s010a_3ed0** cpOut, hkContactPointProperties** propsOut);   // 0x010A42F0
	void freeContactPoint(hkUint16 id);                                  // 0x010A4420

	int m_userData;                                 // +8
	hkIdMgrA m_idMgrA;                              // +0xc (data), +0x10 size, +0x14 capacity|flags
	hkUint8 m_idMgrAStorage[8];                     // +0x18 inplace storage of m_idMgrA
	hkArray_s010a_3ed0<hkContactPoint_s010a_3ed0> m_contactPoints;        // +0x20
	float m_softScale;                              // +0x2c padding in the base class; used by hkSoftContactConstraintData
	int m_pad30;                                    // +0x30 never written by the constructors
	hkConstraintInstance_s010a_3ed0* m_constraint;             // +0x34
	hkArray_s010a_3ed0<hkContactPointProperties> m_contactPointProperties;   // +0x38
	hkUint8 m_flags;                                // +0x44 bit1 = new contact points pending, bit2/bit0 dirty flags
	hkUint8 m_flags2;                               // +0x45
	hkUint16 m_atomSizeFlags;                       // +0x46 (3)
	int m_pad48[7];                                 // +0x48..+0x63
};
struct hkBodyVelocity_s010a_3ed0 { float m_linear[4]; float m_angular[4]; };
struct hkSimpleConstraintInfoInitInput;
class hkSoftContactConstraintData : public hkSimpleContactConstraintData
{
public:
	virtual void buildJacobian(const hkConstraintQueryIn_s010a_3ed0& in, hkConstraintQueryOut_s010a_3ed0& out);   // 0x010A4680
	virtual void toiCollisionResponseEndCallback(const hkContactPoint_s010a_3ed0& cp, float m, hkSimpleConstraintInfoInitInput& inA,
	                                             hkBodyVelocity_s010a_3ed0& velA, hkSimpleConstraintInfoInitInput& inB, hkBodyVelocity_s010a_3ed0& velB);   // 0x010A46F0
	virtual hkBodyVelocity_s010a_3ed0* toiCollisionResponseBeginCallback(const hkContactPoint_s010a_3ed0& cp, hkSimpleConstraintInfoInitInput& inA,
	                                               hkBodyVelocity_s010a_3ed0& velA, hkSimpleConstraintInfoInitInput& inB, hkBodyVelocity_s010a_3ed0& velB);   // 0x010A4850

	// File-scope statics at 0x016E5090 (A), 0x016E50B0 (B), 0x016E50D0 (flag); names inferred.
	static hkBodyVelocity_s010a_3ed0 s_toiVelocityA;   // 0x016e5090
	static hkBodyVelocity_s010a_3ed0 s_toiVelocityB;   // 0x016e50b0
	static hkUint8 s_toiActive;             // 0x016e50d0
};
hkBodyVelocity_s010a_3ed0 hkSoftContactConstraintData::s_toiVelocityA;
hkBodyVelocity_s010a_3ed0 hkSoftContactConstraintData::s_toiVelocityB;
hkUint8 hkSoftContactConstraintData::s_toiActive;
struct hkSolveSingleOutput { int m_pad; };
struct hkWorldCallbackUtil { static void fireContactPointConfirmed(hkWorld_s010a_3ed0* world, hkContactPointConfirmedEvent& e); };   // 0x0109F0D0
struct hkEntityCallbackUtil { static void fireContactPointConfirmedInternal(hkEntityStub* e, hkContactPointConfirmedEvent& ev); };   // 0x0109E850
struct hkSimpleCollisionResponse
{
	// 0x010A6B50
	static void solveSingleContact2(const hkContactPoint_s010a_3ed0& cp, const hkSimpleConstraintUtilCollideParams& params,
	                                hkEntityStub* bodyA, hkEntityStub* bodyB, hkVelocityAccumulator* accA,
	                                hkVelocityAccumulator* accB, hkSimpleContactConstraintData& data, hkSolveSingleOutput& out);
};
void hkSimpleContactConstraintData_buildJacobianPass(hkContactPoint_s010a_3ed0* points, int numPoints, hkContactPointProperties* props,
                                                     hkUint8* flags, const hkConstraintQueryIn_s010a_3ed0* in, hkConstraintQueryOut_s010a_3ed0* out);
void hkConstraintSolverSetup_zeroFromSchemas(void* solverInfo, char* a, void* b, void* c, void* d);   // 0x010b48b0 (equiv t3)
struct hkConstraintSolverResources
{
	const hkStepInfo_s010a_3ed0* m_stepInfo;       // 0
	void* m_solverInfo;                 // 1
	hkConstraintQueryIn_s010a_3ed0* m_queryIn;     // 2
	char* m_p[17];                      // dwords 3..19 (m_p[k-3])
};
#define HK_RES(r, k) ((r).m_p[(k) - 3])
struct hkSolverInfo_s010a_3ed0
{
	// Only the sizes that the buffer layout function reads (x86 offsets; names inferred).
	char m_pad0[0xc];
	int m_sizeC;                        // +0xc
	int m_size10;                       // +0x10
	int m_size14;                       // +0x14
	int m_numSolverResults;             // +0x18
	char m_pad1c[0x40 - 0x1c];
	int m_numAccumulators;              // +0x40
};
struct hkSolverBufferLayout
{
	uintptr_t m_buffer;       // 0
	uintptr_t m_end;          // 1 (total size when m_buffer == 0)
	uintptr_t m_accumulators; // 2
	uintptr_t m_elements;     // 3
	uintptr_t m_schemas;      // 4
	uintptr_t m_results;      // 5
	uintptr_t m_pad6, m_pad7;
};
static inline void hkVelocityAccumulator_setFixed(hkUint8* p)
{
	// 0x80-byte accumulator for fixed bodies: byte 0 = 1 (type), byte 0xc = 1, all dwords from +0x10 cleared.
	p[0] = 1;
	p[0xc] = 1;
	uint32_t* d = (uint32_t*)p;
	for (int i = 4; i < 32; ++i)
		d[i] = 0;
}
static inline uintptr_t hkAlign16(uintptr_t v) { return v & ~(uintptr_t)15; }
struct hkConstraintSolverSetup
{
	static void buildAccumulatorBatch(const hkStepInfo_s010a_3ed0& stepInfo, hkEntityStub* const* entities, int from, int to, hkVelocityAccumulator* base);
	static void buildJacobianElementBatch(hkConstraintQueryIn_s010a_3ed0& in, struct hkConstraintInternal_s010a_3ed0** internals, int n,
	                                      hkVelocityAccumulator* base, hkJacobianSchema* schemas, hkJacobianElement* elements,
	                                      hkJacobianSchema* last);
	static void oneStepIntegrate(const hkStepInfo_s010a_3ed0& stepInfo, hkEntityStub** entities, int n, hkVelocityAccumulator* base);
	static void internalAddAccumulators(hkConstraintSolverResources& res, hkEntityStub** entities, int n);
	static hkBool_s010a_3ed0 internalIsMemoryOkForNewAccumulators(hkConstraintSolverResources& res, hkEntityStub** entities, int n);
};
struct hkConstraintInternal_s010a_3ed0
{
	hkConstraintInstance_s010a_3ed0* m_constraint;   // +0
	hkEntityStub* m_entities[2];          // +4, +8
	hkConstraintData_s010a_3ed0* m_data;             // +0xc
	int m_pad10, m_pad14;
	int m_atomFlags;                      // +0x18 (copied to hkConstraintQueryIn::+0x44)
};
// ---- items of slice s010a3ed0 end

// ---- items of slice s010a6860 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memmove(void* dst, const void* src, size_t n);
struct Edge;
struct Node;
struct Entry;
struct Handler {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
  virtual void GetSize(int kind, int* outSize);              // +0x10
  virtual void v5();
  virtual void Write(Edge* e, char* data, int size);         // +0x18
  virtual void v7();
  virtual void Prepare(int* out);                            // +0x20
};
struct Owner {
virtual void v0();
virtual void v1();
virtual void v2();
  virtual void OnAdd(Edge* e, int* info);                    // +0x0c
};
struct Edge {
  char pad0[4];
  unsigned short f4;
  unsigned short f6;
  Owner* owner;          // 0x08
  Handler* handler;      // 0x0c
  Node* nodes[2];        // 0x10
  unsigned char order;   // 0x18
  unsigned char kind;    // 0x19
  char pad1a[0x0a];
  Entry* entry;          // 0x24
};
struct Entry {
  Edge* edge;            // 0x00
  Node* nodes[2];        // 0x04
  Handler* handler;      // 0x0c
  unsigned char order;   // 0x10
  unsigned char side;    // 0x11
  unsigned short index;  // 0x12
  unsigned short size;   // 0x14
  char* data;            // 0x18
};
struct InsertRange {
  const Entry* p;
  int count;
  unsigned int flags;
};
struct EntryArray {
  Entry* data;
  int size;
  unsigned int cap;
  void Insert(int pos, InsertRange* r);
};
struct ByteArray {
  char* data;
  int size;
  unsigned int cap;
};
struct PtrArray {
  Edge** data;
  int size;
  unsigned int cap;
};
struct Node {
  char pad0[8];
  int f8;
  char padc[0x50];
  Owner* owner;          // 0x5c
  char pad60[0x10];
  EntryArray entries;    // 0x70
  PtrArray edges;        // 0x7c
  ByteArray buffer;      // 0x88
  char pad94[5];
  char f99;              // 0x99
  char pad9a[0x32];
  unsigned int rank;     // 0xcc
};
void FUN_010a1170(int a, Node* n0, Node* n1);
void FUN_0107f4a0(ByteArray* a, int n, int f);
void FUN_0107f530(PtrArray* a, int elemSize);
// ---- items of slice s010a6860 end

// ---- items of slice s010a8b90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kP1;       // 0x01485378   0.0f
extern float kP2;       // 0x014a2394   1.1920929e-07f  (FLT_EPSILON)
extern float kP3;       // 0x01485720   1.0f
extern float kP4;       // 0x013f9428   0.001f
extern float kP5;       // 0x01471064   0.5f
extern float kNegTiny;  // 0x013ef56c  -0.001f
struct Vec4
{
    float x, y, z, w;
};
struct Feature
{
    float m_v0[4];      // +0x00  plane normal / point coordinates
    float m_v1[4];      // +0x10  plane origin / surface normal
    float m_radius;     // +0x20
    float m_marginA;    // +0x24
    float m_marginB;    // +0x28
    float m_scale;      // +0x2c
    int   m_id;         // +0x30
};
struct Rec
{
    Feature* m_p[3];    // +0x00  (stride 0x0c)
};
struct Shape
{
    char  m_pad0[0x20];
    float m_tol[4];     // +0x20  per-axis tolerance (xyz used)
    float m_dir[4];     // +0x30  reference direction (xyz used)
    char  m_pad1[0x8];
    char* m_base;       // +0x48  support-array base for the flag-index computation
};
struct IdTable
{
    char  m_pad0[0x24];
    char* m_slots;      // +0x24
};
struct Ctx
{
    Rec      m_recs[4]; // +0x00
    int      m_count;   // +0x30
    char     m_pad0[4]; // +0x34
    Shape*   m_shape;   // +0x38
    IdTable* m_table;   // +0x3c
};
inline void MarkFeature(Shape* pShape, IdTable* pTable, const void* pFeature, int value)
{
    char* pSlot = pTable->m_slots +
                  ((((char*)pFeature - pShape->m_base) >> 6) << 4) + 0xc;
    *(int*)pSlot = value;
}
inline long double LenSq(const Feature* pKey)
{
    return (long double)pKey->m_v1[0] * pKey->m_v1[0] +
           (long double)pKey->m_v1[1] * pKey->m_v1[1] +
           (long double)pKey->m_v1[2] * pKey->m_v1[2];
}
inline float Abs(float x)
{
    return x < 0.0f ? -x : x;
}
// ---- items of slice s010a8b90 end

// ---- items of slice s010a98c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void f010a8cf0(void*);                            // 0x010a8cf0
extern "C" void f010a8cb0(void*);                            // 0x010a8cb0
extern "C" void f010a90b0(void*, void*, void*, void*);       // 0x010a90b0
extern "C" void f010a9580(void*, void*, int, void*, void*);  // 0x010a9580
extern "C" void f010a8b90(void*);                            // 0x010a8b90
extern float g_14a23a4;                                      // 1.1920929e-07f
static inline float M(int p, int off) { return *(float*)(p + off); }
struct hk1Lin2AngJacobian {
    char pad[0x30];
    hkJacobianElement* next(int i);      // 0x010aa040
};
// ---- items of slice s010a98c0 end

// ---- items of slice s010aa5f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char hkUint8_s010a_a5f0;
typedef unsigned int u32;
class __declspec(align(16)) hkVector4_s010a_a5f0 {
public:
    hkReal x, y, z, w;
    hkReal& operator()(int i) { return (&x)[i]; }
};
struct hkMassAndVelocity {
    hkUint8_s010a_a5f0  m_pad0[0xc];
    hkUint8_s010a_a5f0  m_useInvInertia;      // +0x0c  (0 = use the full inertia rows, nonzero = identity)
    hkUint8_s010a_a5f0  m_pad1[0x03];
    hkReal   m_invMassScalar;      // +0x10
    hkReal   m_f14;                // +0x14
    hkReal   m_f18;                // +0x18
    hkReal   m_f1c;                // +0x1c
    hkUint8_s010a_a5f0  m_pad2[0x10];         // +0x20 .. 0x2f
    hkReal   m_diagX;              // +0x30
    hkReal   m_diagY;              // +0x34
    hkReal   m_diagZ;              // +0x38
    hkReal   m_cfmScalar;          // +0x3c
    hkReal   m_centerOfMass[3];    // +0x40
    hkUint8_s010a_a5f0  m_pad3[0x04];         // +0x4c
    hkReal   m_invInertia[9];      // +0x50 world inverse inertia (3x3, column stride 0x10)
};
struct hkConstraintCore {
    hkUint8_s010a_a5f0 m_pad0[0x14];
    hkReal  m_f14;                 // +0x14
    hkReal  m_f18;                 // +0x18
    hkUint8_s010a_a5f0 m_pad1[0x0c];          // +0x1c .. 0x27
    hkMassAndVelocity* m_bodyA;    // +0x28
    hkMassAndVelocity* m_bodyB;    // +0x2c
};
struct hkJacobian {
    void* m_cursor;                // +0
    void* m_typeCursor;            // +4
};
extern hkReal HK_REAL_EPSILON;     // 0x014a23a4 (FLT_EPSILON)
extern hkReal HK_REAL_ONE;         // 0x01485720 (1.0f)
// ---- items of slice s010aa5f0 end

// ---- items of slice s010ab2d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct hkVector4_s010a_b2d0 { hkReal x, y, z, w; };
static inline hkVector4_s010a_b2d0 hkCross(const hkVector4_s010a_b2d0& a, const hkVector4_s010a_b2d0& b)
{
    hkVector4_s010a_b2d0 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    r.w = 0.0f;
    return r;
}
static inline hkReal hkLen3(const hkVector4_s010a_b2d0& v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}
// ---- items of slice s010ab2d0 end

// ---- items of slice s010abb90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float _HK_REAL_EPSILON;   // 0x014a23a4
extern const float _HK_REAL_ONE;       // 0x01485720
class __declspec(align(16)) hkVector4_s010a_bb90
{
public:
	float x, y, z, w;
};
class hkMatrix3_s010a_bb90
{
public:
	hkVector4_s010a_bb90 m_col[3];
};
class hkRotation_s010a_bb90 : public hkMatrix3_s010a_bb90 {};
class hkSolverBody
{
public:
	unsigned int m_vtable;                 // +0x00
	unsigned int m_pad04;                  // +0x04
	unsigned int m_pad08;                  // +0x08
	unsigned char m_hasInfiniteMass;       // +0x0c
	unsigned char m_pad0d[0x23];           // +0x0d
	hkVector4_s010a_bb90 m_inertiaAndMassInv;         // +0x30
	unsigned char m_pad40[0x10];           // +0x40
	hkRotation_s010a_bb90 m_rotation;                 // +0x50
};
class hkpConstraintQueryIn
{
public:
	unsigned char m_pad00[0x28];           // +0x00
	const hkSolverBody* m_bodyA;           // +0x28
	const hkSolverBody* m_bodyB;           // +0x2c
};
class hkp2AngJacobian
{
public:
	hkVector4_s010a_bb90 m_angular[2];                // +0x00, +0x10
};
class hkp1dBilateralConstraintStatus
{
public:
	float m_virtualMass;                   // +0x00
};
__forceinline void setRotatedInverseDir(hkVector4_s010a_bb90& d, const hkRotation_s010a_bb90& r, const hkVector4_s010a_bb90& v)
{
	const float v0 = v.x, v1 = v.y, v2 = v.z;
	d.x = (v2 * r.m_col[2].x + v1 * r.m_col[1].x) + v0 * r.m_col[0].x;
	d.y = (v2 * r.m_col[2].y + v1 * r.m_col[1].y) + v0 * r.m_col[0].y;
	d.z = (v2 * r.m_col[2].z + v1 * r.m_col[1].z) + v0 * r.m_col[0].z;
	d.w = 0;
}
__forceinline void setRotatedInverseDirNeg(hkVector4_s010a_bb90& d, const hkRotation_s010a_bb90& r, const hkVector4_s010a_bb90& v)
{
	const float v0 = -v.x, v1 = -v.y, v2 = -v.z;
	d.x = (v2 * r.m_col[2].x + v1 * r.m_col[1].x) + v0 * r.m_col[0].x;
	d.y = (v2 * r.m_col[2].y + v1 * r.m_col[1].y) + v0 * r.m_col[0].y;
	d.z = (v2 * r.m_col[2].z + v1 * r.m_col[1].z) + v0 * r.m_col[0].z;
	d.w = 0;
}
// ---- items of slice s010abb90 end

// ---- items of slice s010aed40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct hkVector4_s010a_ed40 { hkReal x, y, z, w; };
// ---- items of slice s010aed40 end

// ---- items of slice s0109f870 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_ReadWriteBarrier)
typedef short hkInt16;
class hkBool_s0109_f870
{
public:
	hkBool_s0109_f870(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
private:
	char m_bool;
};
enum
{
	HK_MEMORY_CLASS_ARRAY = 0x14,
	HK_MEMORY_CLASS_COLLIDE = 0x1c,
	HK_MEMORY_CLASS_CDINFO = 0x1e
};
class hkMemory_s0109_f870
{
public:
	virtual void* allocate(int nbytes, int cl);                          // 0
	virtual void deallocate(void* p);                                    // 1
	virtual void* alignedAllocate(int alignment, int nbytes, int cl);    // 2
	virtual void alignedDeallocate(void* p);                             // 3
	virtual void* allocateChunk(int nbytes, int cl);                     // 4 (+0x10)
	virtual void deallocateChunk(void* p, int nbytes, int cl);           // 5 (+0x14)
	static hkMemory_s0109_f870* s_instance;
};
struct hkArrayUtil_s0109_f870
{
	static void _reserveMore(void* arrayBase, int elemSize);             // 0x0107F530
	static void _reserveExactly(void* arrayBase, int numElem, int elemSize); // 0x0107F4A0
};
enum { HK_ARRAY_CAPACITY_MASK = 0x3fffffff };
template <typename T>
class hkArray_s0109_f870
{ public:
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	int getCapacity() const { return m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK; }
	void pushBack(const T& t)
	{
		if (m_size == getCapacity())
			hkArrayUtil_s0109_f870::_reserveMore(this, (int)sizeof(T));
		m_data[m_size] = t;
		m_size = m_size + 1;
	}
	void setSize(int n)
	{
		int cap = getCapacity();
		if (cap < n)
		{
			int newCap = cap * 2;
			if (newCap <= n) newCap = n;
			hkArrayUtil_s0109_f870::_reserveExactly(this, newCap, (int)sizeof(T));
		}
		m_size = n;
	}
};
#define HK_ALIGN16 __declspec(align(16))
class hkRotation_s0109_f870;
struct HK_ALIGN16 hkVector4_s0109_f870
{
	float x, y, z, w;
	void setRotatedInverseDir(const hkRotation_s0109_f870& a, const hkVector4_s0109_f870& b);     // 0x01081440 (this = transpose(a) * b)
};
class hkRotation_s0109_f870 { public: hkVector4_s0109_f870 m_col[3]; };
class hkTransform_s0109_f870
{ public:
	hkVector4_s0109_f870 m_rot[3];
	hkVector4_s0109_f870 m_trans;
	void setMulInverseMul(const hkTransform_s0109_f870& a, const hkTransform_s0109_f870& b);      // 0x010810F0 (this = inverse(a) * b)
};
class hkBaseObject_s0109_f870 { public: virtual ~hkBaseObject_s0109_f870() {} };
class hkReferencedObject_s0109_f870 : public hkBaseObject_s0109_f870
{
public:
	virtual ~hkReferencedObject_s0109_f870() {}                                     // 0
	virtual void calcStatistics(class hkStatisticsCollector_s0109_f870* c) const {} // 1 (0x0052E650 is the empty default)

	// HK_DECLARE_CLASS_ALLOCATOR: chunk allocation, size stored in m_memSizeAndFlags.
	static void* operator new(size_t nbytes)
	{
		void* p = hkMemory_s0109_f870::s_instance->allocateChunk((int)nbytes, HK_MEMORY_CLASS_COLLIDE);
		((hkReferencedObject_s0109_f870*)p)->m_memSizeAndFlags = (unsigned short)nbytes;
		return p;
	}
	static void operator delete(void* p)
	{
		hkMemory_s0109_f870::s_instance->deallocateChunk(p, ((hkReferencedObject_s0109_f870*)p)->m_memSizeAndFlags, HK_MEMORY_CLASS_COLLIDE);
	}
	static void* operator new(size_t, void* p) { return p; }
	static void operator delete(void*, void*) {}

	// memSize == 0 means "not heap owned": never reference counted.
	void addReference() { if (m_memSizeAndFlags != 0) ++m_referenceCount; }
	void removeReference()
	{
		if (m_memSizeAndFlags != 0)
		{
			m_referenceCount = (hkInt16)(m_referenceCount - 1);
			if (m_referenceCount == 0)
				delete this;
		}
	}

	unsigned short m_memSizeAndFlags;  // 0x04
	hkInt16 m_referenceCount;   // 0x06

protected:
	hkReferencedObject_s0109_f870() : m_referenceCount(1) {}
};
class hkStatisticsCollector_s0109_f870
{ public:
	virtual void s0();
	virtual void beginObject(const char* name, int mode, const void* obj);                                     // +4
	virtual void addArray(const char* name, int elemSize, const void* ptr, int usedBytes, int allocBytes);    // +8
	virtual void addReferencedObject(const char* name, int mode, const void* obj);                             // +0xc
	virtual void s4();
	virtual void s5();
	virtual void endObject();                                                                                  // +0x18
};
class hkQuaternion_s0109_f870 { public: float x, y, z, w; };
class hkMatrix3_s0109_f870 { public: hkVector4_s0109_f870 m_col0, m_col1, m_col2; };   // 0x30 bytes
class hkSweptTransform                                   // 0x50 bytes
{ public:
	hkVector4_s0109_f870 m_centerOfMass0;      // +0   (w = time0)
	hkVector4_s0109_f870 m_centerOfMass1;      // +0x10 (w = invDeltaTime)
	hkQuaternion_s0109_f870 m_rotation0;       // +0x20
	hkQuaternion_s0109_f870 m_rotation1;       // +0x30
	hkVector4_s0109_f870 m_centerOfMassLocal;  // +0x40
};
class hkMotionState                                      // 0xb0 bytes
{ public:
	hkTransform_s0109_f870 m_transform;        // +0
	hkSweptTransform m_sweptTransform;   // +0x40
	hkVector4_s0109_f870 m_deltaAngle;         // +0x90
	float m_objectRadius;           // +0xa0
	float m_linearDamping;          // +0xa4
	float m_angularDamping;         // +0xa8
	float m_pad;                    // +0xac
	hkMotionState& operator=(const hkMotionState&);       // 0x010888C0 (0xb0-byte copy)
};
struct hkSweptTransformUtil
{
	static void setTimeInformation(float time0, float time1, hkMotionState& ms);   // 0x01209B70
	static void freezeMotionState(float time, hkMotionState& ms);                  // 0x0120A570
};
class hkMotion_s0109_f870
{ public:
	virtual void* destroy(unsigned flags);                                   // 0
	virtual void s1();
	virtual int getType() const;                                             // 2 (+8)
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
	virtual void getInertiaLocal(hkMatrix3_s0109_f870& out) const;                      // 11 (+0x2c)
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
	virtual void setLinearVelocity(const hkVector4_s0109_f870& v);                      // 22 (+0x58)
	virtual void setAngularVelocity(const hkVector4_s0109_f870& v);                     // 23 (+0x5c)
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
	virtual void getMotionStateAndVelocities(hkMotion_s0109_f870* motionOut) const;     // 30 (+0x78)

	char m_pad8[0x10 - 8];
	hkMotionState m_motionState;     // +0x10
	float getMass() const;           // 0x01088270 (hkRigidMotion::getMass: 0 if inverse mass is 0, else 1/inverseMass)
	// members behind the motion state (inverse mass at +0xc0, saved motion at +0xf0, ...) are read through the
	// HK_MOTION_* accessors below
};
#define HK_MOTION_U32(m, off)  (*(uint32_t*)((char*)(m) + (off)))
#define HK_MOTION_PTR(m, off)  (*(hkMotion_s0109_f870**)((char*)(m) + (off)))
struct hkFixedRigidMotion { static hkMotion_s0109_f870* construct(void* mem, const hkVector4_s0109_f870& position, const hkQuaternion_s0109_f870& rotation); };       // ctor @ 0x01097110
struct hkKeyframedRigidMotion { static hkMotion_s0109_f870* construct(void* mem, const hkVector4_s0109_f870& position, const hkQuaternion_s0109_f870& rotation); };    // ctor @ 0x01095B60
hkMotion_s0109_f870* hkRigidBody_createMotion(int motionType, const hkVector4_s0109_f870& position, const hkQuaternion_s0109_f870& rotation, float mass, const hkMatrix3_s0109_f870& inertiaLocal,
                          const hkVector4_s0109_f870& centerOfMassLocal, float linearDamping, float angularDamping); // 0x01087290
class hkWorld_s0109_f870;
class hkSimulationIsland_s0109_f870;
struct hkAgentNnEntry_s0109_f870;
struct hkConstraintInstance_s0109_f870;
class hkAction_s0109_f870;
class hkEntity_s0109_f870;
struct hkAgentNnTrack_s0109_f870 { char m_pad[0x24]; };
struct hkCollisionInputStub_s0109_f870 { char m_pad[1]; };
class hkCollidable_s0109_f870 { public: char m_pad0[0x10]; int m_ownerOffset; };   // +0x10: offset from the collidable to its owner entity
struct hkCollisionEntry { hkAgentNnEntry_s0109_f870* m_agentEntry; hkCollidable_s0109_f870* m_partner; };   // 8 bytes (32-bit)
struct hkConstraintInternalStub { hkConstraintInstance_s0109_f870* m_constraint; char m_pad[0x1c - 4]; };   // 0x1c bytes per entry
class hkEntity_s0109_f870
{ public:
	char m_pad0[8];
	hkWorld_s0109_f870* m_world;                                   // +8
	char m_pad1[0x24 - 0xc];
	hkMotionState* m_motionStatePtr;                    // +0x24
	char m_pad2[0x36 - 0x28];
	hkUint16 m_broadPhaseHandleType;                    // +0x36 (inferred; 1 = fixed, 2 = moving)
	char m_pad3[0x40 - 0x38];
	hkCollisionEntry* m_collisionEntriesData;           // +0x40
	int m_collisionEntriesSize;                         // +0x44
	char m_pad4[0x58 - 0x48];
	hkMotion_s0109_f870* m_motion;                                 // +0x58
	hkSimulationIsland_s0109_f870* m_island;                       // +0x5c
	char m_pad5[0x70 - 0x60];
	hkConstraintInternalStub* m_constraintsMasterData;  // +0x70
	int m_constraintsMasterSize;                        // +0x74
	int m_constraintsMasterCap;                         // +0x78
	hkConstraintInstance_s0109_f870** m_constraintsSlaveData;      // +0x7c
	int m_constraintsSlaveSize;                         // +0x80
	char m_pad6[0x94 - 0x84];
	hkUint16 m_storageIndex;                            // +0x94 (index inside the island's entity array)
	char m_pad7[0x99 - 0x96];
	hkUint8 m_isFixed;                                  // +0x99
	hkUint8 m_isFixedOrKeyframed;                       // +0x9a
	char m_pad8[0xc0 - 0x9b];
	hkAction_s0109_f870** m_actionsData;                           // +0xc0
	int m_actionsSize;                                  // +0xc4
};
class hkSimpleConstraintOwner_s0109_f870
{ public:
	virtual void* destroy(unsigned flags);               // 0 (scalar deleting destructor)
virtual void v1();
virtual void v2();
	virtual void addConstraintInfo(hkConstraintInstance_s0109_f870* c, struct hkConstraintInfo_s0109_f870& info);   // 3, 0x0109F9C0
	virtual void subConstraintInfo(hkConstraintInstance_s0109_f870* c, struct hkConstraintInfo_s0109_f870& info);   // 4, 0x0109F900
	int m_pad4;                                         // +4
	int m_maxSizeOfJacobians;                           // +8
	int m_sizeOfJacobians;                              // +0xc
	int m_sizeOfSchemas;                                // +0x10
	int m_numMotionInfo;                                // +0x14 (inferred, addMotionInfo/subMotionInfo)
	int m_numSolverResults;                             // +0x18
};
struct hkConstraintInfo_s0109_f870 { int m_maxSizeOfJacobians, m_sizeOfJacobians, m_sizeOfSchemas, m_numSolverResults; };
class hkAction_s0109_f870
{ public:
	char m_pad0[4];
	hkUint16 m_memSizeAndFlags;                         // +4
	hkUint16 m_referenceCount;                          // +6
	char m_pad1[4];
	hkSimulationIsland_s0109_f870* m_island;                       // +0xc
};
class hkSimulationIsland_s0109_f870 : public hkSimpleConstraintOwner_s0109_f870 { public:
	void internalAddEntity(hkEntity_s0109_f870* e);                 // 0x010A2250
	void construct(hkWorld_s0109_f870* world);                      // 0x010A2810 (placement ctor)
	hkWorld_s0109_f870* m_world;                                   // +0x1c
	hkUint16 m_storageIndex;                            // +0x20
	hkUint16 m_dirtyListIndex;                          // +0x22 (0xffff = not on the dirty list)
	hkUint8 m_activeCounter0;                           // +0x24 (inferred, merged with min())
	hkUint8 m_activeCounter1;                           // +0x25 (inferred, merged with min())
	hkUint8 m_actionListCleanupNeeded;                  // +0x26
	hkUint8 m_splitCheckRequested;                      // +0x27
	hkUint8 m_activeMark;                               // +0x28 (inferred)
	hkUint8 m_active;                                   // +0x29 (1 = in the world's active islands array)
	char m_pad2a[0x34 - 0x2a];
	int m_pad34;                                        // +0x34 cleared on activation (inferred timers)
	int m_pad38;                                        // +0x38
	hkEntity_s0109_f870** m_entitiesData;                          // +0x3c
	int m_entitiesSize;                                 // +0x40
	int m_entitiesCap;                                  // +0x44
	char m_pad48[0x4c - 0x48];
	hkAgentNnTrack_s0109_f870 m_agentTrack;                        // +0x4c (data, size, cap, inplace, bytes used, stride...)
	// the remaining fields (+0x64 actions array, +0x70 time) are addressed through the accessor macros below
};
#define HK_ISLAND_TIME(i)          (*(float*)((char*)(i) + 0x70))
struct hkEntityListenerStub { virtual void v0(); virtual void v1(); virtual void inactiveEntityMovedCallback(hkEntity_s0109_f870* entity); };   // slot 2
class hkWorld_s0109_f870
{ public:
	char m_pad0[0xc];
	float m_currentTime;                                // +0xc (inferred)
	char m_pad1[0x30 - 0x10];
	hkSimulationIsland_s0109_f870* m_fixedIsland;                  // +0x30
	hkEntity_s0109_f870* m_fixedRigidBody;                         // +0x34
	hkArray_s0109_f870<hkSimulationIsland_s0109_f870*> m_activeSimulationIslands;     // +0x38
	hkArray_s0109_f870<hkSimulationIsland_s0109_f870*> m_inactiveSimulationIslands;   // +0x44
	hkArray_s0109_f870<hkSimulationIsland_s0109_f870*> m_dirtySimulationIslands;      // +0x50
	char m_pad2[0x78 - 0x5c];
	hkCollisionInputStub_s0109_f870* m_collisionInput;             // +0x78
	char m_pad3[0x88 - 0x7c];
	int m_pendingOperationQueueCount;                   // +0x88 (inferred)
	int m_criticalOperationsLockCount;                  // +0x8c
	char m_pad4[0x94 - 0x90];
	hkUint8 m_blockExecutingPendingOperations;          // +0x94
	char m_pad5[0xb4 - 0x95];
	hkUint8 m_wantSimulationIslands;                    // +0xb4
	char m_pad6[0x100 - 0xb5];
	void* m_constraintListenersData;                    // +0x100 first dword of the listener array (tested for non-zero)
	char m_pad7[0x120 - 0x104];
	hkEntityListenerStub** m_entityListenersData;       // +0x120 (inferred)
	int m_entityListenersSize;                          // +0x124
	char m_pad8[0x170 - 0x128];
	float m_simulationTime;                             // +0x170 (hkTime, inferred)
	void executePendingOperations();                    // 0x01082BF0
};
struct hkWorldCallbackUtil_s0109_f870
{
	static void fireInactiveEntityMoved(hkWorld_s0109_f870* world, hkEntity_s0109_f870* entity);     // 0x0109F870
	static void fireConstraintAdded(hkWorld_s0109_f870* world, hkConstraintInstance_s0109_f870* c);  // 0x0109EF20
	static void fireConstraintRemoved(hkWorld_s0109_f870* world, hkConstraintInstance_s0109_f870* c);// 0x0109EFB0
	static void fireIslandActivated(hkWorld_s0109_f870* world, hkSimulationIsland_s0109_f870* i);    // 0x0109F300
	static void fireIslandDeactivated(hkWorld_s0109_f870* world, hkSimulationIsland_s0109_f870* i);  // 0x0109F450
};
extern hkVector4_s0109_f870 g_hkVector4Zero;                                              // 0x016E42D0 (static zero vector, set up elsewhere)
void hkSimulationIsland_internalRemoveEntity(hkSimulationIsland_s0109_f870* island, hkEntity_s0109_f870* e);// 0x010A2040 (thiscall)
struct hkWorldOperationUtil
{
	static hkConstraintInstance_s0109_f870* addConstraintImmediately(hkWorld_s0109_f870* world, hkConstraintInstance_s0109_f870* constraint, int fireCallbacks);   // 0x0109F930
	static void removeConstraintImmediately(hkWorld_s0109_f870* world, hkConstraintInstance_s0109_f870* constraint, int fireCallbacks);                  // 0x0109FA10
	static void removeAttachedAgentsConnectingTheEntityAndAFixedPartnerEntityPlus(hkAgentNnTrack_s0109_f870& trackToScan, hkEntity_s0109_f870* entity,
	                                                                              hkAgentNnTrack_s0109_f870& agentsRemoved, int newMotionType);   // 0x0109FAB0
	static void removeIslandFromDirtyList(hkWorld_s0109_f870* world, hkSimulationIsland_s0109_f870* island);   // 0x0109FB40
	static void addEntitySI(hkWorld_s0109_f870* world, hkEntity_s0109_f870* entity, int initialActivationState);   // 0x0109FB70
	static void removeAttachedActionsFromFixedIsland(hkWorld_s0109_f870* world, hkEntity_s0109_f870* entity, hkArray_s0109_f870<hkAction_s0109_f870*>& actionsToBeMoved);   // 0x0109FC70
	static void removeIsland(hkWorld_s0109_f870* world, hkSimulationIsland_s0109_f870* island);                // 0x0109FD50
	static void removeAttachedConstraints(hkEntity_s0109_f870* entity, hkArray_s0109_f870<hkConstraintInstance_s0109_f870*>& constraintsToBeMoved);   // 0x0109FDD0
	static void internalActivateIsland(hkWorld_s0109_f870* world, hkSimulationIsland_s0109_f870* island);      // 0x0109FF50
	static void internalDeactivateIsland(hkWorld_s0109_f870* world, hkSimulationIsland_s0109_f870* island);    // 0x010A0020
	static void markIslandInactive(hkWorld_s0109_f870* world, hkSimulationIsland_s0109_f870* island);          // 0x010A00E0
	static void markIslandActive(hkWorld_s0109_f870* world, hkSimulationIsland_s0109_f870* island);            // 0x010A0130
	static void replaceMotionObject(class hkRigidBody_s0109_f870* body, int newMotionType, hkBool_s0109_f870 newStateNeedsInertia, hkBool_s0109_f870 oldStateNeedsInertia, hkWorld_s0109_f870* world);   // 0x010A0190
	static void removeEntitySI(hkWorld_s0109_f870* world, hkEntity_s0109_f870* entity);                        // 0x010A03C0
	static hkSimulationIsland_s0109_f870* internalMergeTwoIslands(hkWorld_s0109_f870* world, hkSimulationIsland_s0109_f870* islandA, hkSimulationIsland_s0109_f870* islandB);   // 0x010A0410
	static inline void putIslandOnDirtyList(hkWorld_s0109_f870* world, hkSimulationIsland_s0109_f870* island);
};
class hkRigidBody_s0109_f870 : public hkEntity_s0109_f870 { public:};
static inline void hkWorldOperationUtil_pushIsland(hkArray_s0109_f870<hkSimulationIsland_s0109_f870*>& a, hkSimulationIsland_s0109_f870* island)
{
	if (a.m_size == (a.m_capacityAndFlags & 0x3fffffff))
		hkArrayUtil_s0109_f870::_reserveMore(&a, 4);
	a.m_data[a.m_size] = island;
	a.m_size = a.m_size + 1;
}
inline void hkWorldOperationUtil::putIslandOnDirtyList(hkWorld_s0109_f870* world, hkSimulationIsland_s0109_f870* island)
{
	island->m_dirtyListIndex = (hkUint16)world->m_dirtySimulationIslands.m_size;
	hkWorldOperationUtil_pushIsland(world->m_dirtySimulationIslands, island);
}
namespace __equiv_ann1 {
struct hkFixedRigidMotion {
    void construct();   // 0x01088270 (equiv t3)
};
}
// ---- items of slice s0109f870 end

// @ 0x010a0020
void hkWorldOperationUtil::internalDeactivateIsland(hkWorld_s0109_f870* world, hkSimulationIsland_s0109_f870* island)
{
	hkWorldOperationUtil_pushIsland(world->m_inactiveSimulationIslands, island);
	hkArray_s0109_f870<hkSimulationIsland_s0109_f870*>& active = world->m_activeSimulationIslands;
	active.m_data[island->m_storageIndex] = active.m_data[active.m_size - 1];
	active.m_data[island->m_storageIndex]->m_storageIndex = island->m_storageIndex;
	active.m_size = active.m_size - 1;
	island->m_storageIndex = (hkUint16)(world->m_inactiveSimulationIslands.m_size - 1);
	island->m_active = 0;
	HK_ISLAND_TIME(island) = world->m_simulationTime;
	for (int i = 0; i < island->m_entitiesSize; i++)
	{
		hkEntity_s0109_f870* e = island->m_entitiesData[i];
		hkSweptTransformUtil::freezeMotionState(HK_ISLAND_TIME(island), e->m_motion->m_motionState);
		e->m_motion->setLinearVelocity(g_hkVector4Zero);
		e->m_motion->setAngularVelocity(g_hkVector4Zero);
	}
	hkWorldCallbackUtil_s0109_f870::fireIslandDeactivated(world, island);
}

// @ 0x010a00e0
void hkWorldOperationUtil::markIslandInactive(hkWorld_s0109_f870* world, hkSimulationIsland_s0109_f870* island)
{
	island->m_activeMark = 0;
	_ReadWriteBarrier();
	if (island->m_dirtyListIndex == 0xffff)
		putIslandOnDirtyList(world, island);
}

// @ 0x010a0130
void hkWorldOperationUtil::markIslandActive(hkWorld_s0109_f870* world, hkSimulationIsland_s0109_f870* island)
{
	island->m_activeMark = 1;
	island->m_activeCounter1 = 0;
	island->m_activeCounter0 = 0;
	if (island->m_dirtyListIndex == 0xffff)
		putIslandOnDirtyList(world, island);
}

// @ 0x010a0190
void hkWorldOperationUtil::replaceMotionObject(hkRigidBody_s0109_f870* body, int newMotionType, hkBool_s0109_f870 newStateNeedsInertia, hkBool_s0109_f870 oldStateNeedsInertia, hkWorld_s0109_f870* world)
{
	if (!newStateNeedsInertia)
	{
		hkMotion_s0109_f870* oldMotion = body->m_motion;
		hkMotion_s0109_f870* newMotion;
		void* mem = hkMemory_s0109_f870::s_instance->allocateChunk(0x100, 0x2b);
		if (newMotionType == 7)
		{
			((hkReferencedObject_s0109_f870*)mem)->m_memSizeAndFlags = 0x100;
			newMotion = hkFixedRigidMotion::construct(mem, body->m_motion->m_motionState.m_transform.m_trans,
			                                         *(const hkQuaternion_s0109_f870*)&body->m_motion->m_motionState.m_sweptTransform.m_rotation1);
			newMotion->m_motionState = oldMotion->m_motionState;
			// fucompp with 0.0 + test ah,0x44 / jnp: skip only when invDeltaTime == 0 (a NaN does the freeze)
			if (!(oldMotion->m_motionState.m_sweptTransform.m_centerOfMass1.w == 0.0f))
			{
				float time;
				if (world == 0)
				{
					// X87-PRECISION: 1.0f / invDeltaTime is added to time0 unrounded, rounded at the float store.
					time = (float)((hkX87Real)1.0f / oldMotion->m_motionState.m_sweptTransform.m_centerOfMass1.w +
					               oldMotion->m_motionState.m_sweptTransform.m_centerOfMass0.w);
				}
				else
				{
					time = world->m_currentTime;
				}
				hkSweptTransformUtil::freezeMotionState(time, newMotion->m_motionState);
			}
		}
		else
		{
			((hkReferencedObject_s0109_f870*)mem)->m_memSizeAndFlags = 0x100;
			newMotion = hkKeyframedRigidMotion::construct(mem, body->m_motion->m_motionState.m_transform.m_trans,
			                                             *(const hkQuaternion_s0109_f870*)&body->m_motion->m_motionState.m_sweptTransform.m_rotation1);
			oldMotion->getMotionStateAndVelocities(newMotion);
		}

		if (oldStateNeedsInertia)
		{
			HK_MOTION_PTR(newMotion, 0xf0) = oldMotion;
			HK_MOTION_U32(newMotion, 0xf4) = (uint32_t)body->m_broadPhaseHandleType;
			body->m_motion = newMotion;
		}
		else
		{
			HK_MOTION_PTR(newMotion, 0xf0) = HK_MOTION_PTR(oldMotion, 0xf0);
			HK_MOTION_U32(newMotion, 0xf4) = HK_MOTION_U32(oldMotion, 0xf4);
			body->m_motion = newMotion;
			oldMotion->destroy(1);
		}
		body->m_broadPhaseHandleType = (hkUint16)((newMotionType != 7) + 1);
	}
	else
	{
		if (!oldStateNeedsInertia)
		{
			hkMotion_s0109_f870* oldMotion = body->m_motion;
			hkMotion_s0109_f870* saved = HK_MOTION_PTR(oldMotion, 0xf0);
			body->m_motion = saved;
			body->m_broadPhaseHandleType = (hkUint16)HK_MOTION_U32(oldMotion, 0xf4);
			oldMotion->getMotionStateAndVelocities(saved);
			HK_MOTION_PTR(oldMotion, 0xf0) = 0;
			oldMotion->destroy(1);
		}
		if (body->m_motion->getType() != newMotionType && newMotionType != 1)
		{
			hkMotion_s0109_f870* oldMotion = body->m_motion;
			hkMatrix3_s0109_f870 inertiaLocal;
			oldMotion->getInertiaLocal(inertiaLocal);
			float mass = oldMotion->getMass();
			hkMotion_s0109_f870* newMotion = hkRigidBody_createMotion(newMotionType, oldMotion->m_motionState.m_transform.m_trans,
			                                      *(const hkQuaternion_s0109_f870*)&oldMotion->m_motionState.m_sweptTransform.m_rotation1, mass,
			                                      inertiaLocal, oldMotion->m_motionState.m_sweptTransform.m_centerOfMassLocal,
			                                      oldMotion->m_motionState.m_linearDamping, oldMotion->m_motionState.m_angularDamping);
			oldMotion->getMotionStateAndVelocities(newMotion);
			HK_MOTION_U32(newMotion, 0xc8) = HK_MOTION_U32(oldMotion, 0xc8);
			HK_MOTION_U32(newMotion, 0xcc) = HK_MOTION_U32(oldMotion, 0xcc);
			body->m_motion = newMotion;
			oldMotion->destroy(1);
		}
	}
	body->m_motionStatePtr = &body->m_motion->m_motionState;
	body->m_isFixed = (newMotionType == 7);
	body->m_isFixedOrKeyframed = (newMotionType == 7 || newMotionType == 6) ? 1 : 0;
}

// @ 0x010a03c0
void hkWorldOperationUtil::removeEntitySI(hkWorld_s0109_f870* world, hkEntity_s0109_f870* entity)
{
	hkSimulationIsland_s0109_f870* island = entity->m_island;
	entity->m_world = 0;
	hkSimulationIsland_internalRemoveEntity(island, entity);
	if (island->m_storageIndex != 0xffff && island->m_entitiesSize == 0 && world->m_wantSimulationIslands)
	{
		removeIsland(world, island);
		island->destroy(1);     // scalar deleting destructor, vtable slot 0
	}
}

// @ 0x010a22b0
void hkSimulationIsland_s010a_22b0::calcStatistics(hkStatisticsCollector* collector) const
{
    collector->beginAddObject(hkNullName, 8, this);
    if (m_entities.m_capacity >= 0)
        collector->addArray("EntityPtrs", 8, m_entities.m_data, m_entities.m_size * 4,
                            (m_entities.m_capacity & 0x3fffffff) * 4);

    for (int i = 0; i < m_entities.m_size; i++)
    {
        hkEntity_s010a_22b0* entity = m_entities.m_data[i];
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

// @ 0x010a2ac0
void hkDefaultWorldMaintenanceMgr::performMaintenance(hkWorld_s010a_22b0* world, hkStepInfo_s010a_22b0& stepInfo)
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

// @ 0x010a2db0
hkBroadPhaseBorder::hkBroadPhaseBorder(hkWorld_s010a_22b0* world, BroadPhaseBorderBehaviour behaviour)
: hkReferencedObject_s010a_22b0(), hkWorldDeletionListener_s010a_22b0(), hkCollidableListener()
{
    m_world = world;
    m_behaviour = behaviour;
    addReference();
    world->addWorldDeletionListener(this);

    const hkAabb_s010a_22b0& bounds = world->m_broadPhaseBorder;
    const hkReal minX = bounds.m_min.x, minY = bounds.m_min.y, minZ = bounds.m_min.z;
    const hkReal maxX = bounds.m_max.x, maxY = bounds.m_max.y, maxZ = bounds.m_max.z;

    struct PhantomFactory
    {
        static hkAabbPhantom* create(const hkAabb_s010a_22b0& aabb, void* owner)
        {
            hkAabbPhantom* phantom = (hkAabbPhantom*)hkMemory::s_instance->allocateChunk(0xa0, 0x2e);
            phantom->m_memSizeAndFlags = 0xa0;
            new ((void*)phantom) hkAabbPhantom(aabb, 0);
            phantom->m_phantomType = 3;
            phantom->addOverlapListener(owner);
            return phantom;
        }
    };

    hkAabb_s010a_22b0 aabb;
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

// @ 0x010a32c0
hkStepResult hkHalfstepSimulation::stepDeltaTime(hkWorld_s010a_32c0* world, hkReal physicsDeltaTime, hkReal frameDeltaTime)
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
            const hkThreadMemory_s010a_32c0* threadMemory = hkThreadMemory_s010a_32c0::getInstance();
            const int largestFreeChunk = threadMemory->m_freeListCount[0] - (int)threadMemory->m_freeListHead[0];
            if (largestFreeChunk - 0x10 < islandSizeEstimate)
            {
                if (islandSizeEstimate > hkMemoryWatchdog_getMaxAllowedMemory() - hkMemoryWatchdog_getUsedMemory())
                {
                    hkMemory_s010a_32c0::s_instance->m_numUsedChunks = 1;
                    stream.endTimer((const char*)0x0149cc34);
                    return HK_STEP_RESULT_MEMORY_FAILURE;
                }
            }

            const hkReal newPsi = world->m_timeOfNextPsi + halfDelta;
            world->m_timeOfLastPsi = world->m_timeOfNextPsi;
            world->m_timeOfNextPsi = newPsi;

            hkStepInfo_s010a_32c0 psiStep;
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

        hkStepInfo_s010a_32c0 frameStep;
        frameStep.m_startTime    = world->m_timeOfLastPsi;
        frameStep.m_endTime      = world->m_timeOfNextPsi;
        frameStep.m_deltaTime    = world->m_timeOfNextPsi - world->m_timeOfLastPsi;
        frameStep.m_invDeltaTime = 1.0f / frameStep.m_deltaTime;

        hkWorld_performBroadphaseAndCollisionDetection(world, frameStep.m_startTime, frameStep.m_endTime, frameStep.m_invDeltaTime);
        if (hkMemory_s010a_32c0::s_instance->m_numUsedChunks == 1)
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

    hkStepInfo_s010a_32c0 postStep;
    postStep.m_startTime    = world->m_timeOfNextFrame - physicsDeltaTime;
    postStep.m_endTime      = world->m_timeOfNextFrame;
    postStep.m_deltaTime    = postStep.m_endTime - postStep.m_startTime;
    postStep.m_invDeltaTime = 1.0f / postStep.m_deltaTime;

    hkWorldCallbackUtil_firePostSimulationCallback(world, postStep.m_startTime, postStep.m_endTime, postStep.m_invDeltaTime);
    stream.endTimer((const char*)0x0149cc34);
    stream.endTimer((const char*)0x0149cc34);
    return HK_STEP_RESULT_SUCCESS;
}

// @ 0x010a3780
void hkEntityEntityBroadPhaseListener::addCollisionPair(const hkBroadPhasePair& pair)
{
    // Each handle's ownerOffset (a signed byte at +5) shifts it to an hkLinkedCollidable; +0 is its entity.
    hkLinkedCollidable_s010a_32c0* collA = (hkLinkedCollidable_s010a_32c0*)((const char*)pair.m_a + ((hkTypedBroadPhaseHandle_s010a_32c0*)pair.m_a)->m_ownerOffset);
    hkLinkedCollidable_s010a_32c0* collB = (hkLinkedCollidable_s010a_32c0*)((const char*)pair.m_b + ((hkTypedBroadPhaseHandle_s010a_32c0*)pair.m_b)->m_ownerOffset);

    // The original walks world->m_collisionInput (+0x78); its first member is the dispatcher whose tail holds
    // the quality table. The material index is the 16-bit layer at collidable+0x1a, and the selected agent type
    // is written back into the collision input at +0xc (which is also what addAgent receives).
    hkCollisionInputStub* input = (hkCollisionInputStub*)m_world->m_collisionInput;
    hkCollisionDispatcher_s010a_32c0* dispatcher = *(hkCollisionDispatcher_s010a_32c0**)input;
    const char quality = dispatcher->m_collisionQualityTable[*(const uint16_t*)((const char*)collA + 0x1a)]
                            [*(const uint16_t*)((const char*)collB + 0x1a)];
    if (quality != 0)
    {
        const char* agentTypes = dispatcher->m_agentTypeForCombination;
        ((char*)input)[0xc] = agentTypes[quality * 0x3c];
        hkWorldAgentUtil_addAgent((hkAgentNnEntry_s010a_32c0*)collA, (hkAgentNnEntry_s010a_32c0*)collB,
                                  (hkCollisionDispatcher_s010a_32c0*)input);
    }
}

// @ 0x010a3810
hkSimulationIsland_s010a_32c0* hkWorldAgentUtil_getIslandFromAgentEntry(void* entry, hkSimulationIsland_s010a_32c0* islandA, hkSimulationIsland_s010a_32c0* islandB)
{
    // The original walks the island's agent track: its sector count is the size measure and the entry is
    // looked for inside each sector (sector start <= entry < sector start + m_sectorSize).
    const hkBool_s010a_32c0 aIsSmaller(islandA->m_agentTrack.m_numSectors <= islandB->m_agentTrack.m_numSectors);
    hkSimulationIsland_s010a_32c0* island = aIsSmaller ? islandA : islandB;
    hkBool_s010a_32c0 containsEntry(false);

    const int numSectors = island->m_agentTrack.m_numSectors;
    if (numSectors > 0)
    {
        char** sectors = island->m_agentTrack.m_sectorData;
        for (int i = 0; i < numSectors; i++)
        {
            if ((uintptr_t)entry >= (uintptr_t)sectors[i]
                && (uintptr_t)entry < (uintptr_t)sectors[i] + island->m_agentTrack.m_sectorSize)
            {
                containsEntry = hkBool_s010a_32c0(true);
                break;
            }
        }
    }
    // the original returns islandB when (containsEntry != aIsSmaller), islandA otherwise
    return (containsEntry != aIsSmaller) ? islandB : islandA;
}

// @ 0x010a3920
void hkWorldAgentUtil_addAgent(hkAgentNnEntry_s010a_32c0* entryA, hkAgentNnEntry_s010a_32c0* entryB, hkCollisionDispatcher_s010a_32c0* dispatcher)
{
    hkEntity_s010a_32c0* entityA = (hkEntity_s010a_32c0*)entryA;
    hkEntity_s010a_32c0* entityB = (hkEntity_s010a_32c0*)entryB;

    if (!entityA->m_fixed && !entityB->m_fixed && entityA->m_simulationIsland != entityB->m_simulationIsland)
        hkWorld_markIslandDirtyThreadSafe((hkWorld_s010a_32c0*)dispatcher, entityA->m_simulationIsland, entityB->m_simulationIsland);

    hkSimulationIsland_s010a_32c0* islandA = entityA->m_simulationIsland;
    hkSimulationIsland_s010a_32c0* islandB = entityB->m_simulationIsland;
    hkSimulationIsland_s010a_32c0* island = islandB;
    if ((uint16_t)0xffff == islandA->m_storageIndex)   // errors on the uninitialized (0xffff) island
        island = islandA;

    void* agentType = 0;
    uint32_t flipped = 0;
    _hkAgentNnMachine_GetAgentType(entryA, entryB, dispatcher, &agentType, &flipped);

    hkAgentNnEntry_s010a_32c0* first = entryA;
    hkAgentNnEntry_s010a_32c0* second = entryB;
    if (flipped != 0)
    {
        first = entryB;
        second = entryA;
    }

    void* agent = (*(void* (**)(void*, hkAgentNnEntry_s010a_32c0*, hkAgentNnEntry_s010a_32c0*))((char*)agentType + 8))(dispatcher, first, second);
    _hkAgentNnMachine_CreateAgent(&island->m_agentTrack, first, second, agentType, dispatcher, agent);
}

// hkContactMgr: only its vtable is needed; the original tail-calls slot 6 (vtable+0x18).
class hkContactMgr_s010a_32c0
{
public:
    virtual void c0();
    virtual void c1();
    virtual void c2();
    virtual void c3();
    virtual void c4();
    virtual void c5();
    virtual void destroy();          // +0x18
};

// @ 0x010a39f0
void hkWorldAgentUtil_removeAgent(hkAgentNnEntry_s010a_32c0* entry)
{
    hkLinkedCollidable_s010a_32c0* collA = entry->m_collidable[0];
    hkLinkedCollidable_s010a_32c0* collB = entry->m_collidable[1];
    // m_entity is a byte offset from the collidable in this build: the original adds it to the collidable pointer.
    hkEntity_s010a_32c0* entityA = (hkEntity_s010a_32c0*)((char*)collA + (intptr_t)collA->m_entity);
    hkEntity_s010a_32c0* entityB = (hkEntity_s010a_32c0*)((char*)collB + (intptr_t)collB->m_entity);

    // X87? no: the compiled class places m_simulationIsland at +0x5c; the original reads +0x5c too.
    hkSimulationIsland_s010a_32c0* islandA = entityA->m_simulationIsland;
    hkSimulationIsland_s010a_32c0* islandB = entityB->m_simulationIsland;
    hkSimulationIsland_s010a_32c0* island;
    if (islandA == islandB)
    {
        island = islandA;
        island->m_splitCheckRequested.m_bool = 1;
    }
    else if (entityA->m_fixed)
    {
        island = islandB;
    }
    else if (entityB->m_fixed)
    {
        island = islandA;
    }
    else
    {
        island = hkWorldAgentUtil_getIslandFromAgentEntry(entry, islandA, islandB);
        islandA->m_splitCheckRequested.m_bool = 1;
        islandB->m_splitCheckRequested.m_bool = 1;
    }

    _hkAgentNnMachine_DestroyAgent(&island->m_agentTrack, entry, island->m_world->m_collisionDispatcher);
    // tail call: entry->m_contactMgr->vtable[6](), with m_contactMgr as `this`
    ((hkContactMgr_s010a_32c0*)(uintptr_t)entry->m_contactMgr)->destroy();
}

// @ 0x010a3a90
void hkInternalConstraintUtils_calcRelativeAngle(const hkVector4_s010a_32c0& axisA, const hkVector4_s010a_32c0& axisB, const hkVector4_s010a_32c0& ref0, const hkVector4_s010a_32c0& ref1, hkVector4_s010a_32c0& axisOut, hkReal& angleOut)
{
    hkVector4_s010a_32c0 axis;
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

// @ 0x010a3c40
void hkMassChangerConstraintData::toiCollisionResponseBeginCallback(const void* /*cp*/, hkSimpleConstraintInfoInitInput& bodyA, hkSimpleConstraintInfoInitInput& bodyB, hkBodyVelocity& /*velA*/, hkBodyVelocity& /*velB*/)
{
    const hkReal minMass = m_minLinearMass;
    const hkReal maxMass = m_maxLinearMass;
    bodyA.m_scale = minMass * bodyA.m_scale;
    bodyA.m_transform.mul(minMass);
    bodyB.m_scale = maxMass * bodyB.m_scale;
    bodyB.m_transform.mul(maxMass);
}

// @ 0x010a3c90
void hkMassChangerConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
    hkInitQueryOut(const_cast<hkConstraintQueryIn&>(in), 0, 0, out);

    // +0x30 of each velocity accumulator is the 4-float linear-velocity block scaled here.
    hkVector4_s010a_32c0* velA = (hkVector4_s010a_32c0*)((char*)in.m_bodyA + 0x30);
    hkVector4_s010a_32c0* velB = (hkVector4_s010a_32c0*)((char*)in.m_bodyB + 0x30);

    const hkVector4_s010a_32c0 savedA = *velA;
    const hkVector4_s010a_32c0 savedB = *velB;

    hkVector4_s010a_32c0 scaledA;
    scaledA.x = savedA.x * m_minLinearMass;
    scaledA.y = savedA.y * m_minLinearMass;
    scaledA.z = savedA.z * m_minLinearMass;
    scaledA.w = savedA.w * m_minLinearMass;
    hkVector4_s010a_32c0 scaledB;
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

// @ 0x010a3ed0
void hkSimpleContactConstraintData::buildJacobian(const hkConstraintQueryIn_s010a_3ed0& in, hkConstraintQueryOut_s010a_3ed0& out)
{
	int numPoints = m_contactPoints.m_size;
	if (m_flags & 2)
	{
		hkContactPoint_s010a_3ed0* cp = m_contactPoints.m_data;
		hkContactPointProperties* props = m_contactPointProperties.m_data;
		for (int remaining = numPoints; remaining > 0; --remaining, ++cp, ++props)
		{
			if (!(props->m_flags & 1))
				continue;

			hkEntityStub* entityA = in.m_constraintInstance->m_entities[0];
			hkEntityStub* entityB = in.m_constraintInstance->m_entities[1];
			hkMotion_s010a_3ed0* motionA = entityA->m_motion;
			hkMotion_s010a_3ed0* motionB = entityB->m_motion;
			const float* comA = (const float*)((const char*)in.m_accumulatorA + 0x40);
			const float* comB = (const float*)((const char*)in.m_accumulatorB + 0x40);

			// X87-PRECISION: the relative positions stay unrounded on the FPU stack; each cross product is rounded
			// when it is stored to a float slot, then the velocity of the point is added.
			hkX87Real rAx = (hkX87Real)cp->m_position.x - comA[0];
			hkX87Real rAy = (hkX87Real)cp->m_position.y - comA[1];
			hkX87Real rAz = (hkX87Real)cp->m_position.z - comA[2];
			float crossAx = (float)(rAz * motionA->m_angularVelocity.y - rAy * motionA->m_angularVelocity.z);
			float crossAy = (float)(rAx * motionA->m_angularVelocity.z - rAz * motionA->m_angularVelocity.x);
			hkX87Real crossAz = rAy * motionA->m_angularVelocity.x - rAx * motionA->m_angularVelocity.y;
			// X87-PRECISION: only the x component of body A's point velocity stays unrounded (y and z are stored).
			hkX87Real velAx = (hkX87Real)crossAx + motionA->m_linearVelocity.x;
			float velAy = (float)((hkX87Real)crossAy + motionA->m_linearVelocity.y);
			float velAz = (float)(crossAz + motionA->m_linearVelocity.z);

			hkX87Real rBx = (hkX87Real)cp->m_position.x - comB[0];
			hkX87Real rBy = (hkX87Real)cp->m_position.y - comB[1];
			hkX87Real rBz = (hkX87Real)cp->m_position.z - comB[2];
			float crossBx = (float)(rBz * motionB->m_angularVelocity.y - rBy * motionB->m_angularVelocity.z);
			float crossBy = (float)(rBx * motionB->m_angularVelocity.z - rBz * motionB->m_angularVelocity.x);
			hkX87Real crossBz = rBy * motionB->m_angularVelocity.x - rBx * motionB->m_angularVelocity.y;
			float velBx = (float)((hkX87Real)crossBx + motionB->m_linearVelocity.x);
			float velBy = (float)((hkX87Real)crossBy + motionB->m_linearVelocity.y);
			float velBz = (float)(crossBz + motionB->m_linearVelocity.z);   // z cross is NOT stored before the add

			// X87-PRECISION: relative velocity and its dot with the normal are formed on the FPU stack.
			hkX87Real relX = velAx - velBx;
			hkX87Real relY = (hkX87Real)velAy - velBy;
			hkX87Real relZ = (hkX87Real)velAz - velBz;
			float projVel = (float)((relY * cp->m_separatingNormal.y + relX * cp->m_separatingNormal.x) +
			                        relZ * cp->m_separatingNormal.z);

			hkContactPointConfirmedEvent ev;
			ev.m_collidableA = &entityA->m_collidable;
			ev.m_collidableB = &entityB->m_collidable;
			ev.m_contactPoint = cp;
			ev.m_properties = (hkContactPointPropertiesPublic*)((char*)props + 8);
			ev.m_firstCallbackForFullManifold = 0;
			ev.m_projectedVelocity = projVel;
			ev.m_isConstraintCallback = 1;
			ev.m_constraintData = this;

			hkWorld_s010a_3ed0* world = entityA->m_world;
			hkWorldCallbackUtil::fireContactPointConfirmed(world, ev);
			if (entityA->m_contactListeners != 0)
				hkEntityCallbackUtil::fireContactPointConfirmedInternal(entityA, ev);
			if (entityB->m_contactListeners != 0)
				hkEntityCallbackUtil::fireContactPointConfirmedInternal(entityB, ev);

			// restitution: byte * 1/128 (exact in float, power of two)
			float restitution = (float)props->m_restitution * 0.0078125f;
			// binary: fcomp / test ah,0x41 -> taken when (-threshold <= v) or unordered, or restitution <= 0.3 or unordered
			float negThreshold = -world->m_collisionInput->m_dynamicsInfo->m_contactRestingVelocity;
			if (negThreshold > ev.m_projectedVelocity && restitution > 0.3f) // NaN falls to the else branch, as the fcomp/test ah,0x41 pairs do
			{
				hkSimpleConstraintUtilCollideParams params;
				params.m_normalAndDistance.x = cp->m_separatingNormal.x;
				params.m_normalAndDistance.y = cp->m_separatingNormal.y;
				params.m_normalAndDistance.z = cp->m_separatingNormal.z;
				params.m_normalAndDistance.w = cp->m_separatingNormal.w;
				params.m_friction = (float)props->m_friction * 0.00390625f;
				params.m_restitution = restitution;
				params.m_velocityAlongNormal = ev.m_projectedVelocity;
				params.m_externalSeparatingVelocity = 0.0f;
				params.m_extraSeparatingVelocity = 0.0f;
				hkSolveSingleOutput solveOut;
				hkSimpleCollisionResponse::solveSingleContact2(*cp, params, entityA, entityB, in.m_accumulatorA,
				                                               in.m_accumulatorB, *this, solveOut);
				props->m_solverData0 = 0.0f;
				props->m_solverData4 = cp->m_separatingNormal.w;
			}
			else
			{
				// X87-PRECISION: mass term and the following products stay on the FPU stack (rounded only when stored).
				hkX87Real sumInvMass = (hkX87Real)motionB->m_inverseMass + motionA->m_inverseMass;
				hkX87Real recip = 1.0f / (sumInvMass + 1.00000001335143196e-10f);  // 0x2edbe6ff
				hkX87Real r = (recip * (restitution + 1.0f));
				props->m_solverData0 = (float)(((r * ev.m_projectedVelocity)) * -0.2f);
				hkX87Real t = (((hkX87Real)props->m_restitution * in.m_deltaTime) * ev.m_projectedVelocity) * 0.0078125f;
				hkX87Real v1 = t * -1.3f;   // fst stores a rounded copy; the unrounded value feeds the next fadd
				props->m_solverData1 = (float)v1;
				props->m_solverData4 = (float)(v1 + cp->m_separatingNormal.w);
			}
			props->m_flags &= 0xfe;
		}
		m_flags &= 0xfd;
	}
	hkSimpleContactConstraintData_buildJacobianPass(m_contactPoints.m_data, numPoints, m_contactPointProperties.m_data,
	                                                &m_flags, &in, &out);
}

// @ 0x010a4290
int hkIdMgrA::newUid(hkUint8 value)
{
	// Reuse the highest free slot (0xff) if there is one, otherwise append.
	for (int i = m_size - 1; i >= 0; --i)
	{
		if (m_data[i] == 0xff)
		{
			m_data[i] = value;
			return i;
		}
	}
	if (m_size == (m_capacityAndFlags & CAPACITY_MASK))
		hkArrayUtil::_reserveMore(this, 1);
	m_data[m_size] = value;
	int idx = m_size;
	m_size = idx + 1;
	return idx;
}

// @ 0x010a42f0
hkUint16 hkSimpleContactConstraintData::allocateContactPoint(hkContactPoint_s010a_3ed0** cpOut, hkContactPointProperties** propsOut)
{
	int numProps = m_contactPointProperties.m_size;
	hkConstraintInfo info;
	info.m_maxSizeOfJacobians = numProps * 0x30 + 0xb0;
	info.m_sizeOfJacobians = 0;
	info.m_sizeOfSchemas = 0;
	if (numProps == 1)
	{
		info.m_sizeOfSchemas = 4;
		info.m_sizeOfJacobians = 0x20;
	}
	info.m_sizeOfSchemas += 4;
	info.m_sizeOfJacobians += 0x30;
	info.m_numSolverResults = (numProps == 1) + 1;

	hkOwnerStub* owner = m_constraint->m_owner;
	hkCriticalSection_s010a_3ed0* cs = owner->m_world->m_modifyConstraintCriticalSection;
	if (cs != 0)
	{
		cs->enter();
		m_constraint->m_owner->addConstraintInfo(m_constraint, info);
		cs->leave();
	}
	else
	{
		owner->addConstraintInfo(m_constraint, info);
	}

	m_flags |= 6;
	int oldCount = m_contactPoints.m_size;
	hkContactPoint_s010a_3ed0* newPoint = m_contactPoints.expandOne();
	hkContactPointProperties* newProps = m_contactPointProperties.expandOne();
	newProps->m_solverData0 = 0.0f;
	newProps->m_solverData1 = 0.0f;
	newProps->m_flags = 1;
	if (oldCount > 0 && !(newProps[-1].m_flags & 2))
		newProps->m_flags = 3;
	*cpOut = newPoint;
	*propsOut = newProps;
	return (hkUint16)m_idMgrA.newUid((hkUint8)oldCount);
}

// @ 0x010a4420
void hkSimpleContactConstraintData::freeContactPoint(hkUint16 id)
{
	int idx = m_idMgrA.m_data[id];
	m_idMgrA.m_data[id] = 0xff;

	hkConstraintInfo info;
	info.m_maxSizeOfJacobians = 0;
	info.m_sizeOfJacobians = 0;
	info.m_sizeOfSchemas = 0;
	info.m_numSolverResults = 0;
	int oldProps = m_contactPointProperties.m_size;
	if (oldProps == 2)
	{
		info.m_sizeOfSchemas = 4;
		info.m_sizeOfJacobians = 0x20;
		info.m_numSolverResults = 1;
	}

	// remove the properties entry (the contact point array is only shortened, exactly as in the binary)
	m_contactPointProperties.m_size = oldProps - 1;
	for (int i = idx; i < m_contactPointProperties.m_size; ++i)
		m_contactPointProperties.m_data[i] = m_contactPointProperties.m_data[i + 1];
	m_contactPointProperties.m_data[idx].m_flags &= 0xfd;
	m_contactPoints.m_size = m_contactPoints.m_size - 1;

	// hkArray::optimizeCapacity-style shrink checks
	if (m_contactPointProperties.m_size * 2 + 2 <= (m_contactPointProperties.m_capacityAndFlags & hkArray_s010a_3ed0<int>::CAPACITY_MASK))
		hkArrayUtil::_reduce(&m_contactPointProperties, (int)sizeof(hkContactPointProperties), 0, 0);
	if (m_contactPoints.m_size * 2 + 2 <= (m_contactPoints.m_capacityAndFlags & hkArray_s010a_3ed0<int>::CAPACITY_MASK))
		hkArrayUtil::_reduce(&m_contactPoints, (int)sizeof(hkContactPoint_s010a_3ed0), 0, 0);

	// ids that pointed behind the removed entry move down by one
	for (int j = m_idMgrA.m_size - 1; j >= 0; --j)
	{
		hkUint8* p = &m_idMgrA.m_data[j];
		if (*p != 0xff && (int)*p > idx)
			--*p;
	}

	info.m_sizeOfSchemas += 4;
	info.m_sizeOfJacobians += 0x30;
	info.m_numSolverResults += 1;

	hkOwnerStub* owner = m_constraint->m_owner;
	hkCriticalSection_s010a_3ed0* cs = owner->m_world->m_modifyConstraintCriticalSection;
	if (cs != 0)
	{
		cs->enter();
		m_constraint->m_owner->subConstraintInfo(m_constraint, info);
		cs->leave();
		m_flags |= 5;
		return;
	}
	owner->subConstraintInfo(m_constraint, info);
	m_flags |= 5;
}

// @ 0x010a45b0
hkSimpleContactConstraintData::hkSimpleContactConstraintData(hkConstraintInstance_s010a_3ed0* constraint)
{
	m_referenceCount = 1;
	m_userData = 0;
	m_idMgrA.m_size = 0;
	m_idMgrA.m_capacityAndFlags = (int)0x80000008;
	m_idMgrA.m_data = m_idMgrAStorage;
	m_contactPoints.m_data = 0;
	m_contactPoints.m_size = 0;
	m_contactPoints.m_capacityAndFlags = (int)0x80000000;
	m_contactPointProperties.m_data = 0;
	m_contactPointProperties.m_size = 0;
	m_contactPointProperties.m_capacityAndFlags = (int)0x80000000;
	*(hkUint16*)&m_flags = 0;           // m_flags and m_flags2
	m_atomSizeFlags = 3;
	for (int i = 0; i < 7; ++i)
		m_pad48[i] = 0;
	m_constraint = constraint;
}

// @ 0x010a4620
hkSimpleContactConstraintData::hkSimpleContactConstraintData()
{
	m_referenceCount = 1;
	m_userData = 0;
	m_idMgrA.m_size = 0;
	m_idMgrA.m_capacityAndFlags = (int)0x80000008;
	m_idMgrA.m_data = m_idMgrAStorage;
	m_contactPoints.m_data = 0;
	m_contactPoints.m_size = 0;
	m_contactPoints.m_capacityAndFlags = (int)0x80000000;
	m_contactPointProperties.m_data = 0;
	m_contactPointProperties.m_size = 0;
	m_contactPointProperties.m_capacityAndFlags = (int)0x80000000;
	*(hkUint16*)&m_flags = 0;
	m_atomSizeFlags = 3;
	for (int i = 0; i < 7; ++i)
		m_pad48[i] = 0;
	m_constraint = 0;
}

// @ 0x010a4680
void hkSoftContactConstraintData::buildJacobian(const hkConstraintQueryIn_s010a_3ed0& in, hkConstraintQueryOut_s010a_3ed0& out)
{
	float scale = m_softScale;
	hkConstraintQueryIn_s010a_3ed0 local = in;          // 0x12 dwords (rep movsd)
	local.m_softScaledA = local.m_softScaledA * scale;
	local.m_softScaledB = local.m_softScaledB * scale;
	local.m_softScaledC = local.m_softScaledC * scale;
	hkSimpleContactConstraintData::buildJacobian(local, out);   // non-virtual call to 0x010a3ed0
}

// @ 0x010a46f0
void hkSoftContactConstraintData::toiCollisionResponseEndCallback(const hkContactPoint_s010a_3ed0&, float, hkSimpleConstraintInfoInitInput&, hkBodyVelocity_s010a_3ed0& velA, hkSimpleConstraintInfoInitInput&, hkBodyVelocity_s010a_3ed0& velB)
{
	float s = m_softScale;
	// X87-PRECISION: 1.0 - s stays unrounded on the FPU stack, and so do the two products of each blend.
	hkX87Real u = 1.0f - s;
	for (int i = 0; i < 4; ++i)
		velA.m_linear[i] = (float)(s * velA.m_linear[i] + s_toiVelocityA.m_linear[i] * u);
	for (int i = 0; i < 4; ++i)
		velA.m_angular[i] = (float)(s * velA.m_angular[i] + s_toiVelocityA.m_angular[i] * u);
	for (int i = 0; i < 4; ++i)
		velB.m_linear[i] = (float)(s * velB.m_linear[i] + s_toiVelocityB.m_linear[i] * u);
	for (int i = 0; i < 4; ++i)
		velB.m_angular[i] = (float)(s * velB.m_angular[i] + s_toiVelocityB.m_angular[i] * u);
	s_toiActive = 0;
}

// 0x010a4850 (byte-exact lifted version: match/slices/s010a4850/s010a4850.cpp)
hkBodyVelocity_s010a_3ed0* hkSoftContactConstraintData::toiCollisionResponseBeginCallback(const hkContactPoint_s010a_3ed0&, hkSimpleConstraintInfoInitInput&, hkBodyVelocity_s010a_3ed0& velA, hkSimpleConstraintInfoInitInput&, hkBodyVelocity_s010a_3ed0& velB)
{
	s_toiActive = 1;
	s_toiVelocityA = velA;   // 8 dwords
	s_toiVelocityB = velB;
	return &velB;            // the original leaves velB's address in EAX (void_hides_eax)
}

// @ 0x010a48f0
void hkConstraintSolverSetup_initializeSolverState(hkStepInfo_s010a_3ed0& stepInfo, hkSolverInfo_s010a_3ed0& solverInfo, hkConstraintQueryIn_s010a_3ed0& in, char* buffer, int bufferSize, hkConstraintSolverResources& res)
{
	res.m_stepInfo = &stepInfo;
	res.m_solverInfo = &solverInfo;
	res.m_queryIn = &in;

	int n = bufferSize - bufferSize % 16;      // sign-corrected remainder idiom in the binary
	int q1 = (n * 10) / 0x3c;
	int q2 = (n * 0x1e) / 0x3c;

	uintptr_t b0 = ((uintptr_t)buffer + 0xf) & ~(uintptr_t)0xf;
	HK_RES(res, 3) = (char*)b0;
	uintptr_t t4 = hkAlign16(q1 + b0 + 0xf);
	uintptr_t t6 = hkAlign16(q2 + t4 + 0xf);
	HK_RES(res, 4) = (char*)t4;
	HK_RES(res, 5) = (char*)t4;
	uintptr_t t8 = hkAlign16(q1 + t6 + 0xf);
	HK_RES(res, 6) = (char*)t6;
	HK_RES(res, 7) = (char*)t6;
	HK_RES(res, 8) = (char*)t8;
	HK_RES(res, 9) = (char*)t8;
	// X87-PRECISION: fild of n*10 times -0.01f, kept unrounded, then _ftol2 (truncation).
	int c = (int)((hkX87Real)(n * 10) * -0.0100000007078051567f);   // constant 0xbc23d70b @ 0x014a22c4
	uintptr_t t10 = hkAlign16((uintptr_t)((intptr_t)t8 - c) + 0xf);
	HK_RES(res, 0xe) = buffer + n;
	HK_RES(res, 0xa) = (char*)t10;
	HK_RES(res, 0xd) = (char*)t10;
	HK_RES(res, 0xf) = (char*)t10;
	HK_RES(res, 0x10) = (char*)t10;
	HK_RES(res, 0x11) = HK_RES(res, 3);
	HK_RES(res, 0x12) = HK_RES(res, 5);
	HK_RES(res, 0x13) = HK_RES(res, 7);
	HK_RES(res, 0xb) = HK_RES(res, 9);
	HK_RES(res, 0xc) = HK_RES(res, 9);
}

// @ 0x010a49e0
void hkConstraintSolverSetup_resetSolverBuffers(hkConstraintSolverResources& res, int keepExisting)
{
	for (uint32_t* p = (uint32_t*)HK_RES(res, 7); p < (uint32_t*)HK_RES(res, 0x13); ++p)
		*p = 0;
	if (keepExisting == 0)
	{
		HK_RES(res, 0xc) = HK_RES(res, 9);
		HK_RES(res, 0x10) = HK_RES(res, 0xd);
	}
	if (HK_RES(res, 0xc) != HK_RES(res, 0xb))
		hkConstraintSolverSetup_zeroFromSchemas(res.m_solverInfo, HK_RES(res, 0xc), HK_RES(res, 3), HK_RES(res, 5), HK_RES(res, 7));
	if (HK_RES(res, 0x10) != HK_RES(res, 0xf))
		hkConstraintSolverSetup_zeroFromSchemas(res.m_solverInfo, HK_RES(res, 0x10), HK_RES(res, 3), HK_RES(res, 5), HK_RES(res, 7));
	HK_RES(res, 0xc) = HK_RES(res, 0xb);
	HK_RES(res, 0x10) = HK_RES(res, 0xf);
}

// @ 0x010a4a70
__declspec(noinline) uint64_t hkConstraintSolverSetup_layoutBuffer(const hkSolverInfo_s010a_3ed0* info, uintptr_t base, void* /*unused*/, hkSolverBufferLayout* out)
{
	out->m_buffer = base;
	out->m_accumulators = base;
	out->m_elements = base + 0x90 + info->m_size14;
	out->m_results = out->m_elements + info->m_sizeC;
	out->m_schemas = out->m_results + info->m_numSolverResults * 4 + 8;
	out->m_end = (info->m_size10 - out->m_buffer) + 4 + out->m_schemas;
	if (out->m_buffer != 0)
	{
		hkUint8* acc = (hkUint8*)out->m_accumulators;
		acc[0] = 1;
		acc[0xc] = 1;
		uint32_t* d = (uint32_t*)acc;
		for (int i = 4; i < 32; ++i)
			d[i] = 0;
		acc[(info->m_numAccumulators + 1) * 0x80] = 2;
	}
	return out->m_end;
}

// @ 0x010a4b30
void hkConstraintSolverSetup_calcBufferSize(const hkSolverInfo_s010a_3ed0* info)
{
	hkSolverBufferLayout tmp;
	hkConstraintSolverSetup_layoutBuffer(info, 0, 0, &tmp);
}

// @ 0x010a4b50
void hkConstraintSolverSetup::buildAccumulatorBatch(const hkStepInfo_s010a_3ed0& stepInfo, hkEntityStub* const* entities, int from, int to, hkVelocityAccumulator* base)
{
	char* acc = (char*)base + (from + 1) * 0x80;
	for (hkEntityStub* const* p = entities + from; p < entities + to; ++p)
	{
		hkMotion_s010a_3ed0* motion = (*p)->m_motion;
		int offset = (int)(acc - (char*)base);
		if (motion->m_accumulatorOffset != offset)
			motion->m_accumulatorOffset = offset;
		acc = (char*)motion->buildAccumulator(stepInfo, (hkVelocityAccumulator*)acc);
	}
}

// @ 0x010a4bb0
void hkConstraintSolverSetup::buildJacobianElementBatch(hkConstraintQueryIn_s010a_3ed0& in, hkConstraintInternal_s010a_3ed0** internals, int n, hkVelocityAccumulator* base, hkJacobianSchema* schemas, hkJacobianElement* elements, hkJacobianSchema* last)
{
	in.m_jacobianBuffer = elements;
	hkConstraintInternal_s010a_3ed0** end = internals + n;
	in.m_bodyBuffer = base;
	hkConstraintQueryOut_s010a_3ed0 out;
	out.m_jacobians = elements;
	out.m_schemas = schemas;
	for (; internals < end; ++internals)
	{
		hkConstraintInternal_s010a_3ed0* ci = *internals;
		hkMotion_s010a_3ed0* motionA = ci->m_entities[0]->m_motion;
		hkMotion_s010a_3ed0* motionB = ci->m_entities[1]->m_motion;
		in.m_accumulatorA = (hkVelocityAccumulator*)((char*)base + motionA->m_accumulatorOffset);
		in.m_motionStateA = (char*)motionA + 0x10;
		in.m_motionStateB = (char*)motionB + 0x10;
		in.m_accumulatorB = (hkVelocityAccumulator*)((char*)base + motionB->m_accumulatorOffset);
		in.m_constraintInstance = ci->m_constraint;
		in.m_constraintFlags = ci->m_atomFlags;
		ci->m_data->buildJacobian(in, out);
	}
	if (last == 0)
		*(int*)out.m_schemas = 0;   // schema-stream terminator, written at the cursor the callees advanced
}

// @ 0x010a4c60
void hkConstraintSolverSetup_integrateBatch(const hkStepInfo_s010a_3ed0& stepInfo, hkEntityStub** entities, int n, hkVelocityAccumulator* base)
{
	for (hkEntityStub** p = entities; p < entities + n; ++p)
	{
		hkMotion_s010a_3ed0* motion = (*p)->m_motion;
		motion->integrateFromAccumulator(stepInfo, (hkVelocityAccumulator*)((char*)base + motion->m_accumulatorOffset));
	}
}

// @ 0x010a4ca0
void hkConstraintSolverSetup::oneStepIntegrate(const hkStepInfo_s010a_3ed0& stepInfo, hkEntityStub** entities, int n, hkVelocityAccumulator* base)
{
	for (hkEntityStub** p = entities; p < entities + n; ++p)
	{
		hkMotion_s010a_3ed0* motion = (*p)->m_motion;
		hkVelocityAccumulator* acc = (hkVelocityAccumulator*)((char*)base + motion->m_accumulatorOffset);
		// copy the 8 floats at +0x10..+0x2f to +0x40..+0x5f (the original moves them as 8 dwords)
		uint32_t* stored = (uint32_t*)acc->m_stored;
		const uint32_t* vel = (const uint32_t*)acc->m_linearVelocity;
		for (int i = 0; i < 8; ++i)
			stored[i] = vel[i];
		motion->integrateFromAccumulator(stepInfo, acc);
	}
}

// @ 0x010a4d10
void hkConstraintSolverSetup::internalAddAccumulators(hkConstraintSolverResources& res, hkEntityStub** entities, int n)
{
	hkEntityStub** end = entities + n;
	char* acc = HK_RES(res, 0x11);
	if (acc == HK_RES(res, 3))
	{
		hkVelocityAccumulator_setFixed((hkUint8*)acc);
		acc += 0x80;
		HK_RES(res, 0x11) = acc;
	}
	for (; entities < end; ++entities)
	{
		hkMotion_s010a_3ed0* motion = (*entities)->m_motion;
		const hkStepInfo_s010a_3ed0* step = res.m_stepInfo;
		int offset = (int)(acc - HK_RES(res, 3));
		if (motion->m_accumulatorOffset != offset)
			motion->m_accumulatorOffset = offset;
		acc = (char*)motion->buildAccumulator(*step, (hkVelocityAccumulator*)acc);
		HK_RES(res, 0x11) = acc;
	}
	*(hkUint8*)acc = 2;
}

// @ 0x010a4de0
hkBool_s010a_3ed0 hkConstraintSolverSetup::internalIsMemoryOkForNewAccumulators(hkConstraintSolverResources& res, hkEntityStub** entities, int n)
{
	uintptr_t cur = (uintptr_t)HK_RES(res, 0x11);
	hkEntityStub** end = entities + n;
	if (cur == (uintptr_t)HK_RES(res, 3))
		cur += 0x80;
	uintptr_t limit = (uintptr_t)HK_RES(res, 4) - 0x10;
	for (; entities < end; ++entities)
	{
		cur += (uintptr_t)(*entities)->m_motion->getSizeOfAccumulators();
		if (cur > limit)
			return hkBool_s010a_3ed0(false);
	}
	return hkBool_s010a_3ed0(true);
}

// @ 0x010a6860
void FUN_010a6860(void* unused, Edge* e)
{
  if (e->f4 != 0)
    e->f6++;
  Entry tmp;
  tmp.edge = e;
  tmp.nodes[0] = e->nodes[0];
  tmp.nodes[1] = e->nodes[1];
  tmp.handler = e->handler;
  tmp.order = e->order;
  if (tmp.nodes[0]->f99 == 0 && tmp.nodes[1]->f99 == 0 && tmp.nodes[0]->owner != tmp.nodes[1]->owner)
    FUN_010a1170(tmp.nodes[0]->f8, tmp.nodes[0], tmp.nodes[1]);
  tmp.side = tmp.nodes[0]->f99 != 0;
  Node* node = tmp.nodes[tmp.side];
  e->owner = node->owner;
  int info;
  tmp.handler->Prepare(&info);
  e->owner->OnAdd(e, &info);

  EntryArray* arr = &node->entries;
  int n = arr->size;
  int i = 0;
  for (; i < n; i++) {
    Entry* p = &arr->data[i];
    if (p->order > tmp.order) break;
    if (p->order == tmp.order) {
      if (p->nodes[0]->rank > tmp.nodes[0]->rank) break;
      if (p->nodes[0]->rank == tmp.nodes[0]->rank && p->nodes[1]->rank > tmp.nodes[1]->rank) break;
    }
  }
  int start = n < (int)(arr->cap & 0x3fffffff) ? i : 0;
  InsertRange r;
  r.p = &tmp;
  r.count = 1;
  r.flags = 0x80000001;
  arr->Insert(i, &r);
  for (int j = start; j < arr->size; j++)
    arr->data[j].edge->entry = &arr->data[j];

  Entry* ent = e->entry;
  ent->handler->GetSize(e->kind, &info);
  ent->size = (unsigned short)info;
  if (info == 0) {
    ent->data = 0;
  } else {
    ByteArray* buf = &node->buffer;
    char* old = buf->data;
    int newSize = buf->size + info;
    if ((int)(buf->cap & 0x3fffffff) < newSize)
      FUN_0107f4a0(buf, newSize, 1);
    buf->size += info;
    char* pos = buf->data;
    int delta = pos - old;
    int k = 0;
    for (; k < i; k++) {
      Entry* p = &arr->data[k];
      if (p->data) {
        p->data += delta;
        pos = p->data + p->size;
      }
    }
    memmove(pos + ent->size, pos, buf->data - ent->size - pos + buf->size);
    ent->data = pos;
    delta += ent->size;
    for (k++; k < arr->size; k++) {
      Entry* p = &arr->data[k];
      p->data = p->data ? p->data + delta : 0;
    }
  }
  ent->handler->Write(e, ent->data, ent->size);
  Node* other = ent->nodes[1 - ent->side];
  ent->index = (unsigned short)other->edges.size;
  PtrArray* v = &other->edges;
  if (v->size == (int)(v->cap & 0x3fffffff))
    FUN_0107f530(v, 4);
  v->data[v->size] = e;
  v->size++;
}

// @ 0x010a7720
static __forceinline void SchemaFloat(uint32_t* s, float f)
{ *(float*)s = f; }

// @ 0x010a8b90
int FUN_010a8b90(Ctx* pCtx)
{
    Rec* p;
    Rec* q;
    int  i;
    int  j;

    if (pCtx->m_count <= 1)
        return pCtx->m_count;

    i = 1;
    p = pCtx->m_recs;
    while (i < pCtx->m_count)
    {
        j = i;
        q = p + 1;
        do
        {
            Feature* kb = q->m_p[1];
            Feature* ka = p->m_p[1];
            if (ka->m_id < kb->m_id)
                goto next;
            if (ka->m_id == kb->m_id)
            {
                if (LenSq(ka) < LenSq(kb))
                    goto next;
            }
            {
                Rec tmp = *p;
                *p = *q;
                *q = tmp;
            }
        next:
            ++j;
            ++q;
        } while (j < pCtx->m_count);
        ++i;
        ++p;
    }
    return pCtx->m_count;
}

// @ 0x010a8cb0
bool* FUN_010a8cb0(const Feature* pPoint, const Feature* pPlane, bool* pOut)
{
    float dx = pPoint->m_v0[0] - pPlane->m_v1[0];
    float dy = pPoint->m_v0[1] - pPlane->m_v1[1];
    float dz = pPoint->m_v0[2] - pPlane->m_v1[2];

    *pOut = (dz * pPlane->m_v0[2] + dy * pPlane->m_v0[1] + dx * pPlane->m_v0[0]) < kNegTiny;
    return pOut;
}

// @ 0x010a8cf0
void FUN_010a8cf0(Feature* pCollider, Ctx* pCtx, Feature* pPoint, Vec4* pOut)
{
    float rad;      // collider radius
    float scale;    // collider normalised direction scale
    float margin;   // active margin (+0x24 or +0x28)
    float dx, dy, dz, dw;   // tangential part of (point - origin)
    float len2;     // |point - origin|^2
    float distSq;   // squared distance along the plane normal
    float proj;     // signed projection of (dy,dz,dw) onto the disc normal
    float invLen;   // 1/|disc normal|
    float nx, ny, nz;
    float tmp;
    int   outOrigin = 0;
    Shape* pShape;

    rad    = pCollider->m_radius;
    scale  = pCollider->m_scale;
    pShape = pCtx->m_shape;

    dx = pPoint->m_v0[0] - pCollider->m_v1[0];
    dy = pPoint->m_v0[1] - pCollider->m_v1[1];
    dz = pPoint->m_v0[2] - pCollider->m_v1[2];

    distSq = dx * pCollider->m_v0[0] +
             (dz * pCollider->m_v0[2] + dy * pCollider->m_v0[1]);
    len2 = dx * dx + (dy * dy + dz * dz);

    dx = dx - distSq * pCollider->m_v0[0];
    dy = dy - distSq * pCollider->m_v0[1];
    dz = dz - distSq * pCollider->m_v0[2];
    dw = (pPoint->m_v0[3] - pCollider->m_v1[3]) - distSq * pCollider->m_v0[3];
    distSq = distSq * distSq;

    if (dx * pShape->m_dir[0] +
        (dy * pShape->m_dir[1] + dz * pShape->m_dir[2]) <= kP1)
        margin = pCollider->m_marginB;
    else
        margin = pCollider->m_marginA;

    nx = 0.0f;
    ny = 0.0f;
    nz = 0.0f;
    invLen = 0.0f;
    proj = 0.0f;

    if (margin <= kP1)
    {
        if (len2 <= (rad * rad + kP3) * distSq)
            outOrigin = 1;
    }
    else
    {
        nx = pShape->m_dir[1] * pCollider->m_v0[2] - pShape->m_dir[2] * pCollider->m_v0[1];
        ny = pShape->m_dir[2] * pCollider->m_v0[0] - pShape->m_dir[0] * pCollider->m_v0[2];
        nz = pShape->m_dir[0] * pCollider->m_v0[1] - pCollider->m_v0[0] * pShape->m_dir[1];
        tmp = nx * nx + (ny * ny + nz * nz);
        if (kP2 < tmp)
        {
            invLen = kP3 / sqrtf(tmp);
            nx = nx * invLen;
            ny = ny * invLen;
            nz = nz * invLen;
            invLen = invLen * kP1;
            proj = nx * dx + (ny * dy + nz * dz);
            tmp = (rad * rad) * distSq;
            if ((proj * proj < tmp) != (proj * proj == tmp))
            {
                dx = dx - nx * proj;
                dy = dy - ny * proj;
                dz = dz - nz * proj;
                tmp = invLen * proj;
                proj = kP1;
                dw = dw - tmp;
            }
        }
        rad = ((margin + rad) * (margin + rad)) * distSq;
        distSq = (len2 - proj * proj) - distSq;
        if ((distSq < rad) != (distSq == rad))
        {
            if (proj == kP1)
            {
                outOrigin = 1;
            }
            else
            {
                dx = nx * proj;
                dy = ny * proj;
                dz = nz * proj;
                dw = invLen * proj;
            }
        }
    }

    if (outOrigin)
    {
        pOut->x = pCollider->m_v1[0];
        pOut->y = pCollider->m_v1[1];
        pOut->z = pCollider->m_v1[2];
        pOut->w = pCollider->m_v1[3];
        return;
    }

    if (scale < kP3)
    {
        rad = dx * dx + (dy * dy + dz * dz);
        if (kP2 <= rad && len2 * kP4 < rad)
        {
            scale = (kP3 - scale) * sqrtf(len2 / rad) + scale;
            tmp = (scale * dx) * pCollider->m_v0[0] +
                  ((dz * scale) * pCollider->m_v0[2] + (dy * scale) * pCollider->m_v0[1]);
            dx = scale * dx - tmp * pCollider->m_v0[0];
            dy = dy * scale - tmp * pCollider->m_v0[1];
            dz = dz * scale - tmp * pCollider->m_v0[2];
            dw = dw * scale - tmp * pCollider->m_v0[3];
        }
    }

    pOut->x = dx + pCollider->m_v1[0];
    pOut->y = dy + pCollider->m_v1[1];
    pOut->z = dz + pCollider->m_v1[2];
    pOut->w = dw + pCollider->m_v1[3];
}

// @ 0x010a90b0
void FUN_010a90b0(Ctx* pCtx, Feature* pB, Feature* pC, Vec4* pOut, Feature* pA)
{
    float f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13;
    int   bX, bY, bZ;
    Shape* pShape;

    f2 = pA->m_v0[2] * pB->m_v0[1] - pB->m_v0[2] * pA->m_v0[1];
    f4 = pB->m_v0[2] * pA->m_v0[0] - pA->m_v0[2] * pB->m_v0[0];
    f5 = pA->m_v0[1] * pB->m_v0[0] - pA->m_v0[0] * pB->m_v0[1];
    f3 = f2 * f2 + (f5 * f5 + f4 * f4);

    if (f3 > kP2)
    {
        f3 = kP3 / sqrtf(f3);
        f2 = f2 * f3;
        f4 = f4 * f3;
        f5 = f5 * f3;
        f6 = f3 * kP1;
        pShape = pCtx->m_shape;

        f7 = ((pB->m_v0[0] + pA->m_v0[0]) * f2 +
              ((pA->m_v0[2] + pB->m_v0[2]) * f5 +
               (pA->m_v0[1] + pB->m_v0[1]) * f4)) * kP5;
        f10 = pB->m_v1[0] * pB->m_v0[0] +
              (pB->m_v1[1] * pB->m_v0[1] + pB->m_v1[2] * pB->m_v0[2]);
        f8 = pA->m_v0[0] * pA->m_v1[0] +
             (pA->m_v1[1] * pA->m_v0[1] + pA->m_v1[2] * pA->m_v0[2]);

        f12 = ((pA->m_v0[2] * pB->m_v0[1] - pB->m_v0[2] * pA->m_v0[1]) * f7 +
               ((f5 * pA->m_v0[1] - f4 * pA->m_v0[2]) * f10 +
                (f4 * pB->m_v0[2] - f5 * pB->m_v0[1]) * f8)) * f3;
        f11 = ((pB->m_v0[2] * pA->m_v0[0] - pA->m_v0[2] * pB->m_v0[0]) * f7 +
               ((f2 * pA->m_v0[2] - f5 * pA->m_v0[0]) * f10 +
                (f5 * pB->m_v0[0] - f2 * pB->m_v0[2]) * f8)) * f3;
        f3  = ((f2 * pB->m_v0[1] - f4 * pB->m_v0[0]) * f8 +
               ((pA->m_v0[1] * pB->m_v0[0] - pA->m_v0[0] * pB->m_v0[1]) * f7 +
                (f4 * pA->m_v0[0] - f2 * pA->m_v0[1]) * f10)) * f3;

        bZ = Abs(f3)  < pShape->m_tol[2];
        bY = Abs(f11) < pShape->m_tol[1];
        bX = Abs(f12) < pShape->m_tol[0];
        if (bX && bY && bZ)
        {
            f7  = pC->m_v0[0] - f12;
            f9  = pC->m_v0[1] - f11;
            f8  = pC->m_v0[2] - f3;
            f10 = f9 * f9 + (f8 * f8 + f7 * f7);
            f13 = f2 * pShape->m_dir[0] +
                  (f5 * pShape->m_dir[2] + f4 * pShape->m_dir[1]);
            f7  = f7 * f2 + (f8 * f5 + f9 * f4);

            if (f7 * f13 <= kP1)
                f8 = pB->m_marginB + pA->m_marginB;
            else
                f8 = pB->m_marginA + pA->m_marginA;

            f9  = (f8 * f13 + (pB->m_radius + pA->m_radius)) * kP5;
            f13 = (pB->m_scale + pA->m_scale) * kP5;
            f8  = f7 * f7;

            if (f8 <= (f9 * f9) * (f10 - f8))
            {
                pOut->w = f6;
                pOut->x = f12;
                pOut->y = f11;
                pOut->z = f3;
                return;
            }

            if (f13 < kP3 && f10 * kP4 < f8)
                f7 = ((kP3 - f13) * (sqrtf(f10) * Abs(kP3 / f7)) + f13) * f7;

            pOut->x = f2 * f7 + f12;
            pOut->y = f4 * f7 + f11;
            pOut->z = f5 * f7 + f3;
            pOut->w = f6 * f7 + f6;
            return;
        }
    }

    MarkFeature(pCtx->m_shape, pCtx->m_table, pB, 2);
    MarkFeature(pCtx->m_shape, pCtx->m_table, pA, 2);

    if (pA->m_id < pB->m_id)
    {
        FUN_010a8cf0(pA, pCtx, pC, pOut);
        FUN_010a8cf0(pB, pCtx, (Feature*)pOut, pOut);
    }
    else
    {
        FUN_010a8cf0(pB, pCtx, pC, pOut);
        FUN_010a8cf0(pA, pCtx, (Feature*)pOut, pOut);
    }
}

// @ 0x010a9580
void FUN_010a9580(Feature* pCollider, Ctx* pCtx, Feature* pB, int p4, Feature* p5, Vec4* pOut, Feature* pA)
{
    float f2, f3, f4, f5, f6, f7, f8, f9;
    int   bX, bY, bZ;
    int   snapshot;
    Shape* pShape;

    f2 = pB->m_v0[2] * pA->m_v0[1] - pA->m_v0[2] * pB->m_v0[1];
    f3 = pA->m_v0[2] * pB->m_v0[0] - pB->m_v0[2] * pA->m_v0[0];
    f7 = pA->m_v0[0] * pB->m_v0[1] - pB->m_v0[0] * pA->m_v0[1];
    f5 = f3 * pCollider->m_v0[1] +
         (f7 * pCollider->m_v0[2] + f2 * pCollider->m_v0[0]);

    if (kP2 <= Abs(f5))
    {
        f9 = pCollider->m_v0[0] * pCollider->m_v1[0] +
             (pCollider->m_v1[1] * pCollider->m_v0[1] +
              pCollider->m_v1[2] * pCollider->m_v0[2]);
        f6 = pA->m_v1[0] * pA->m_v0[0] +
             (pA->m_v1[1] * pA->m_v0[1] + pA->m_v1[2] * pA->m_v0[2]);
        f8 = pB->m_v0[0] * pB->m_v1[0] +
             (pB->m_v1[1] * pB->m_v0[1] + pB->m_v1[2] * pB->m_v0[2]);
        f5 = kP3 / f5;

        f4 = (f2 * f9 +
              ((pB->m_v0[1] * pCollider->m_v0[2] - pB->m_v0[2] * pCollider->m_v0[1]) * f6 +
               (pA->m_v0[2] * pCollider->m_v0[1] - pCollider->m_v0[2] * pA->m_v0[1]) * f8)) * f5;
        f3 = (f3 * f9 +
              ((pB->m_v0[2] * pCollider->m_v0[0] - pB->m_v0[0] * pCollider->m_v0[2]) * f6 +
               (pA->m_v0[0] * pCollider->m_v0[2] - pA->m_v0[2] * pCollider->m_v0[0]) * f8)) * f5;
        f2 = (f7 * f9 +
              ((pCollider->m_v0[1] * pB->m_v0[0] - pCollider->m_v0[0] * pB->m_v0[1]) * f6 +
               (pCollider->m_v0[0] * pA->m_v0[1] - pA->m_v0[0] * pCollider->m_v0[1]) * f8)) * f5;

        pShape = pCtx->m_shape;
        bX = Abs(f4) < pShape->m_tol[0];
        bY = Abs(f3) < pShape->m_tol[1];
        bZ = Abs(f2) < pShape->m_tol[2];
        if (bX && bY && bZ)
        {
            pOut->w = f5 * kP1;
            pOut->x = f4;
            pOut->y = f3;
            pOut->z = f2;
            return;
        }
    }

    if (p4 != 0)
    {
        FUN_010a8b90(pCtx);
        pCollider = pCtx->m_recs[0].m_p[1];
        pA = pCtx->m_recs[1].m_p[1];
        pB = pCtx->m_recs[2].m_p[1];
    }

    MarkFeature(pCtx->m_shape, pCtx->m_table, pCollider, 1);
    MarkFeature(pCtx->m_shape, pCtx->m_table, pA, 1);
    MarkFeature(pCtx->m_shape, pCtx->m_table, pB, 1);

    snapshot = pCtx->m_count;
    FUN_010a90b0(pCtx, pCollider, p5, pOut, pA);
    if (snapshot == pCtx->m_count)
        FUN_010a90b0(pCtx, pCollider, (Feature*)pOut, pOut, pB);
    if (snapshot != pCtx->m_count)
        return;
    FUN_010a90b0(pCtx, pA, (Feature*)pOut, pOut, pB);
}

// @ 0x010a98c0
void f010a98c0(int* p)
{
    for (;;) {
        switch (p[0xc]) {
        case 1:
            f010a8cf0(p);
            return;
        case 2: {
            int scratch[4];
            f010a8cf0(p);
            f010a8cb0(scratch);
            if (*(uint8_t*)scratch) {
                f010a90b0(p, (void*)p[1], (void*)(p[0xe] + 0x10), (void*)(p[0xf] + 0x10));
                return;
            }
            int* dst = (int*)p[0xf];
            dst[4] = scratch[2];
            dst[5] = scratch[3];
            dst[6] = 0;
            dst[7] = 0;
            p[0] = p[3];
            p[1] = p[4];
            p[2] = p[5];
            p[0xc] = 1;
            continue;
        }
        case 3: {
            int scratch[8];
            int* pcur = p + 1;
            f010a8cf0(p);
            f010a8cb0(scratch);
            if (*(uint8_t*)scratch == 0) {
                f010a8cb0(scratch + 2);
                if (*(uint8_t*)((char*)scratch + 8) == 0) {
                    int* dst = (int*)p[0xf];
                    dst[4] = scratch[2];
                    dst[5] = scratch[3];
                    dst[6] = 0;
                    dst[7] = 0;
                    p[0] = p[6];
                    p[1] = p[7];
                    p[2] = p[8];
                    p[0xc] = 1;
                    continue;
                }
            }
            {
                int i = 0;
                do {
                    if (p[0xc] < 3) break;
                    f010a90b0(p, (void*)*pcur, (void*)(p[0xe] + 0x10), scratch);
                    f010a8cb0((char*)scratch + 12);
                    if (*(uint8_t*)((char*)scratch + 12) == 0) {
                        int* e = p + i * -3 + 3;
                        e[0] = p[3];
                        e[1] = p[4];
                        e[2] = p[5];
                        p[3] = p[6];
                        p[4] = p[7];
                        p[5] = p[8];
                        p[0xc] = 2;
                        break;
                    }
                    i++;
                    pcur += 3;
                } while (i < 2);
                if (i >= 2) {
                    if (p[0xc] > 2) {
                        f010a9580(p, (void*)p[7], 1, (void*)(p[0xe] + 0x10), (void*)(p[0xf] + 0x10));
                        return;
                    }
                }
            }
            continue;
        }
        case 4: {
            int loc[8];
            int i = 0;
            f010a8b90(p);
            do {
                f010a9580(p, (void*)p[10], 0, (void*)(p[0xe] + 0x10), loc);
                int* e = p + i * 3;
                f010a8cb0(loc);
                if (*(uint8_t*)loc == 0) {
                    e[0] = p[6];
                    e[1] = p[7];
                    e[2] = p[8];
                    p[6] = p[9];
                    p[7] = p[10];
                    p[8] = p[0xb];
                    p[0xc] = 3;
                    i = 10;
                }
                i++;
            } while (i < 3);
            if (i >= 10) continue;
            {
                float loc40[4];
                int* src = (int*)p[0xe];
                loc40[0] = *(float*)((char*)src + 0x10);
                loc40[1] = *(float*)((char*)src + 0x14);
                loc40[2] = *(float*)((char*)src + 0x18);
                loc40[3] = *(float*)((char*)src + 0x1c);
                int u = p[10];
                int saved = p[0xc];
                f010a9580(p, (void*)p[7], 0, loc40, loc40);
                if (saved == p[0xc]) f010a9580(p, (void*)u, 0, loc40, loc40);
                if (saved == p[0xc]) f010a9580(p, (void*)u, 0, loc40, loc40);
                if (saved == p[0xc]) f010a9580(p, (void*)u, 0, loc40, loc40);
                int* dst = (int*)p[0xf];
                dst[4] = *(int*)&loc40[0];
                dst[5] = *(int*)&loc40[1];
                dst[6] = *(int*)&loc40[2];
                dst[7] = *(int*)&loc40[3];
                int mx = 0;
                if (-1 < *(int*)(p[2] + 0xc)) mx = *(int*)(p[2] + 0xc);
                if (mx <= *(int*)(p[5] + 0xc)) mx = *(int*)(p[5] + 0xc);
                if (mx <= *(int*)(p[8] + 0xc)) mx = *(int*)(p[8] + 0xc);
                if (mx <= *(int*)(p[0xb] + 0xc)) mx = *(int*)(p[0xb] + 0xc);
                int k = 0;
                int* pi = p + 2;
                do {
                    if (mx == *(int*)(*pi + 0xc)) {
                        int* e = p + k * 3;
                        e[0] = p[9];
                        e[1] = p[10];
                        e[2] = p[0xb];
                        break;
                    }
                    k++;
                    pi += 3;
                } while (k < 4);
                p[0xc] = p[0xc] - 1;
                *(int*)(p[2] + 0xc) = 0;
                *(int*)(p[5] + 0xc) = 0;
                *(int*)(p[8] + 0xc) = 0;
            }
            return;
        }
        default:
            return;
        }
    }
}

// @ 0x010a9d30
void f010a9d30(float* a, float* b)
{
    float l74 = a[0x10];
    b[4] = a[4];
    b[5] = a[5];
    b[6] = a[6];
    b[7] = a[7];
    b[0] = a[0];
    b[1] = a[1];
    b[2] = a[2];
    b[3] = a[3];
    int i = 0;
    // solver state handed to f010a98c0: 4 basis slots (3 words each), then
    // count, lambda, context a, context b
    int st[16];
    st[12] = 0;
    st[13] = 0;
    st[14] = (int)a;
    st[15] = (int)b;
    float l1c = 0.0f;
    if (0 < (int)a[0x13]) {
        int off = 0;
        do {
            char* e = (char*)(int)b[9] + off;
            e[0] = 0;
            e[1] = 0;
            *(int*)(e + 4) = 0;
            *(int*)(e + 8) = 0;
            *(int*)(e + 0xc) = 0;
            i++;
            off += 0x10;
        } while (i < (int)a[0x13]);
    }
    if (0.0f <= l74) {
        for (;;) {
            float l78 = l74;
            int l70 = -1;
            if (0 < (int)a[0x13]) {
                int idx = 0, c64 = 0, i8 = 0;
                do {
                    if ((((st[12] < 1) || (st[0] != idx)) &&
                         ((st[12] < 2 || (st[3] != idx)))) &&
                        (((st[12] < 3 || (st[6] != idx)) &&
                         (*(int*)((char*)(int)b[9] + 0xc + i8) == 0)))) {
                        float* e = (float*)((char*)(int)a[0x12] + c64);
                        float f1 = -((b[5] - e[5]) * e[1] +
                                     ((b[4] - *(float*)((char*)(int)a[0x12] + 0x10 + c64)) * e[0] +
                                      (b[6] - e[6]) * e[2]));
                        if (f1 < 0.0f == (f1 == 0.0f)) {
                            float f2 = -l1c;
                            f2 = ((f2 * e[5] + b[1]) * e[1] +
                                  ((f2 * e[4] + b[0]) * e[0] +
                                   (f2 * e[6] + b[2]) * e[2])) + e[3];
                            if (f2 < 1.1920929e-07f != (f2 == 1.1920929e-07f)) f2 = 0.0f;
                            f2 = f2 + *(float*)((char*)(int)b[9] + 8 + i8);
                            if (f2 < f1 * l78) {
                                l78 = f2 / f1;
                                l70 = idx;
                            }
                        }
                    }
                    c64 += 0x40;
                    idx++;
                    i8 += 0x10;
                } while (idx < (int)a[0x13]);
            }
            if (0.0001f < l78) {
                l1c = l78 + l1c;
                l74 = l74 - l78;
                b[0] = l78 * b[4] + b[0];
                b[1] = l78 * b[5] + b[1];
                b[2] = l78 * b[6] + b[2];
                b[3] = l78 * b[7] + b[3];
                if (0 < st[12]) {
                    int* pi = st + 2;
                    int k = st[12];
                    do {
                        char* e = (char*)*pi;
                        pi += 3;
                        k--;
                        *(float*)(e + 4) = l78 + *(float*)(e + 4);
                        e[0] = 1;
                    } while (k != 0);
                }
                b[8] = l1c;
                if (a[0x11] < l1c) return;
            }
            if (l70 < 0) break;
            int i7 = st[12] * 3;
            st[12] = st[12] + 1;
            st[i7 + 1] = l70 * 0x40 + (int)a[0x12];
            int i8 = l70 * 0x10 + (int)b[9];
            float f1 = *(float*)(l70 * 0x10 + 8 + (int)b[9]) + 1.1920929e-07f;
            st[i7 + 2] = i8;
            *(float*)(i8 + 8) = f1 + f1;
            st[i7] = l70;
            f010a98c0(st);
            if (!(l74 >= 0.0f)) return;
        }
        b[8] = a[0x10];
    }
}

// @ 0x010aa040
hkJacobianElement* hk1Lin2AngJacobian::next(int i)
{
    return (hkJacobianElement*)((char*)this + i * 0x30);
}

// @ 0x010aa050
void f010aa050(float s, int body, int* stack, int index)
{
    float v = *(float*)(body + 4);
    *(float*)(index * -0x30 + *stack + 0xc) = s * v;
}

// @ 0x010aa080
void f010aa080(int ctx, int* stack, int a3, int a4)
{
    int b20 = *(int*)(ctx + 0x20);
    int b24 = *(int*)(ctx + 0x24);
    int b2c = *(int*)(ctx + 0x2c);
    int b28 = *(int*)(ctx + 0x28);
    int* out = (int*)stack[1];
    out[1] = *stack - b24;
    out[2] = b28 - b20;
    out[3] = b2c - b20;
    out[0] = 0x180101;
    out[5] = a3;
    out[4] = a4;
    stack[1] = (int)(out + 6);
}

// @ 0x010aa0d0
void f010aa0d0(float* a, float* b, int* stack)
{
    int* o = (int*)stack[1];
    int base = stack[0];
    int* ia = (int*)a;
    ((float*)o)[1] = a[2] * b[0];
    ((float*)o)[2] = a[3] * b[0];
    o[3] = ia[1];
    o[4] = ia[4];
    o[5] = ia[5];
    o[6] = 0x3f800000;
    o[0] = 0x1c0606;
    *(float*)(base + 0x1c) = b[1] * a[0];
    stack[0] = base + 0x20;
    stack[1] = (int)(o + 7);
}

// @ 0x010aa130
void f010aa130(float* a, float* b, int* stack, float* out)
{
    int base = stack[0];
    int* o = (int*)out;
    int* ia = (int*)a;
    out[0] = a[2] * b[0];
    out[1] = a[3] * b[0];
    o[2] = ia[1];
    o[3] = ia[4];
    o[4] = ia[5];
    o[5] = 0x3f800000;
    *(float*)(base + 0x1c) = b[1] * a[0];
    stack[0] = base + 0x20;
}

// @ 0x010aa180
void f010aa180(float* a, float* b, int* stack)
{
    int* o = (int*)stack[1];
    int base = stack[0];
    int* ia = (int*)a;
    ((float*)o)[1] = a[2] * b[0];
    ((float*)o)[2] = a[3] * b[0];
    o[3] = ia[1];
    o[6] = 0x3f800000;
    o[4] = ia[4];
    o[5] = ia[5];
    o[0] = 0x1c0507;
    *(float*)(base + 0xc) = b[1] * a[0];
    stack[0] = base + 0x30;
    stack[1] = (int)(o + 7);
}

// @ 0x010aa1e0
void f010aa1e0(float* a, int b, int* stack)
{
    int bodyA = *(int*)(b + 0x28);
    float lever = *(float*)(b + 0x18);
    int bodyB = *(int*)(b + 0x2c);
    float* e = (float*)*stack;
    if (*(char*)(bodyA + 0xc) == 0) {
        float x = a[4], y = a[5], z = a[6];
        e[0] = x * M(bodyA, 0x50) + (y * M(bodyA, 0x60) + z * M(bodyA, 0x70));
        e[1] = x * M(bodyA, 0x54) + (y * M(bodyA, 0x64) + z * M(bodyA, 0x74));
        e[2] = x * M(bodyA, 0x58) + (y * M(bodyA, 0x68) + z * M(bodyA, 0x78));
        e[3] = 0.0f;
    } else {
        e[0] = a[4];
        e[1] = a[5];
        e[2] = a[6];
        e[3] = a[7];
    }
    float nx = -a[4];
    if (*(char*)(bodyB + 0xc) == 0) {
        float ny = -a[5];
        float nz = -a[6];
        e[4] = nx * M(bodyB, 0x50) + (nz * M(bodyB, 0x70) + ny * M(bodyB, 0x60));
        e[5] = nz * M(bodyB, 0x74) + (nx * M(bodyB, 0x54) + ny * M(bodyB, 0x64));
        e[6] = nz * M(bodyB, 0x78) + (nx * M(bodyB, 0x58) + ny * M(bodyB, 0x68));
        e[7] = 0.0f;
    } else {
        e[4] = nx;
        e[5] = -a[5];
        e[6] = -a[6];
        e[7] = -a[7];
    }
    // Original x87 rounding structure (0x010aa322..0x010aa373):
    //   q2/q4/q5/q6 are stored to 32-bit float slots and reloaded; q0/q1 are
    //   never stored and stay in extended-precision x87 registers (so a huge e[1]
    //   does not overflow to inf before the multiply -- `inf * 0` would be NaN).
    //   Each product is extended (float operand, extended result) and the three
    // Original x87 rounding structure (0x010aa2ea..0x010aa36f). Trace of the x87
    // stack, top first:
    //   q0 = e0^2 , q1 = e1^2   -> stay in x87 registers (never fstp'd)
    //   q2/q4/q5/q6             -> fstp'd to 32-bit float slots and reloaded
    //   0x010aa327 fstp [esp+0x20]  -> `q0*A30` is rounded to FLOAT on its own
    //   0x010aa32b fmul [edx+0x34]  -> `q1*A34` stays extended
    //   0x010aa332 fmul [edx+0x38]  -> `q2*A38` stays extended
    //   `mem20 = q4*B30 + q0*A30` (fstp -> float), `mem24 = q5*B34 + q1*A34`
    //   (fstp -> float), `mem18 = q6*B38` (fstp -> float). Combine order is
    //   `((q2*A38 + mem18) + mem24) + mem20 + eps`, extended, one rounding at the
    //   e[3] store.
    // Separately rounding q0*A30 to float is what makes a huge e[0] turn the pair
    // into NaN (inf*finite + -inf) instead of a finite value.
    float q2 = e[2] * e[2], q4 = e[4] * e[4], q5 = e[5] * e[5], q6 = e[6] * e[6];
    long double q0 = (long double)e[0] * e[0];
    long double q1 = (long double)e[1] * e[1];
    float m18 = (float)((long double)q6 * M(bodyB, 0x38));
    float m24 = (float)((long double)q5 * M(bodyB, 0x34) + q1 * M(bodyA, 0x34));
    float t20 = (float)(q0 * M(bodyA, 0x30));
    float m20 = (float)((long double)q4 * M(bodyB, 0x30) + t20);
    long double den = ((((long double)q2 * M(bodyA, 0x38) + m18) + m24) + m20) +
                      g_14a23a4;
    e[3] = (float)((long double)lever / den);
    int* cmd = (int*)stack[1];
    cmd[0] = 0x4060e;
    stack[0] = (int)(e + 8);
    stack[1] = (int)(cmd + 1);
    e[7] = -(a[0] * a[8] + (a[1] * a[9] + a[2] * a[10])) * *(float*)(b + 0x14);
}

// @ 0x010aa3c0
int f010aa3c0(int* p, float* b, int* stack_)
{
    float* e = (float*)*stack_;
    int* cmd = (int*)stack_[1];
    float* v = (float*)*p;
    int n = p[3];
    if (n - 1 >= 0) {
        float* src = (float*)(p[1] + 4);
        do {
            // b[] holds two body pointers in float slots; the original loads them
            // as raw dwords (`mov edx,[ecx+0x2c]`), so reinterpret, don't convert.
            int bodyB = *(int*)(b + 0xb);
            int bodyA = *(int*)(b + 10);
            float bx = v[0], by = v[1], bz = v[2];
            if (*(char*)(bodyA + 0xc) == 0) {
                e[0] = bx * M(bodyA, 0x50) + (by * M(bodyA, 0x60) + bz * M(bodyA, 0x70));
                e[1] = bx * M(bodyA, 0x54) + (by * M(bodyA, 0x64) + bz * M(bodyA, 0x74));
                e[2] = bx * M(bodyA, 0x58) + (by * M(bodyA, 0x68) + bz * M(bodyA, 0x78));
                e[3] = 0.0f;
            } else {
                e[0] = v[0];
                e[1] = v[1];
                e[2] = v[2];
                e[3] = v[3];
            }
            float nx = -v[0];
            if (*(char*)(bodyB + 0xc) == 0) {
                float ny = -v[1];
                float nz = -v[2];
                e[4] = nx * M(bodyB, 0x50) + (ny * M(bodyB, 0x60) + nz * M(bodyB, 0x70));
                e[5] = ny * M(bodyB, 0x64) + (nz * M(bodyB, 0x74) + nx * M(bodyB, 0x54));
                e[6] = ny * M(bodyB, 0x68) + (nz * M(bodyB, 0x78) + nx * M(bodyB, 0x58));
                e[7] = 0.0f;
            } else {
                e[4] = nx;
                e[5] = -v[1];
                e[6] = -v[2];
                e[7] = -v[3];
            }
            // Original x87 rounding structure (0x010aa4f0..0x010aa59a), same shape as
            // 010aa1e0 above (trace there is annotated in full): q2/q4/q5/q6 pass
            // through 32-bit float slots, q0/q1 stay in x87 registers,
            // `mem30 = q0*A30` is rounded to float on its own (0x010aa53d) before
            // `mem20 = q4*B30 + mem30`, `mem24 = q5*B34 + q1*A34` (q1 extended) and
            // `mem18 = q6*B38` are each fstp'd to float, and the combine is
            // `((q6*B38 + q2*A38) + mem24) + mem20 + eps` in extended precision
            // (0x010aa582..0x010aa594) with one rounding at the e[3] store.
            float q2 = e[2] * e[2], q4 = e[4] * e[4], q5 = e[5] * e[5], q6 = e[6] * e[6];
            long double q0 = (long double)e[0] * e[0];
            long double q1 = (long double)e[1] * e[1];
            float m18 = (float)((long double)q6 * M(bodyB, 0x38));
            float m24 = (float)((long double)q5 * M(bodyB, 0x34) + q1 * M(bodyA, 0x34));
            float m30 = (float)(q0 * M(bodyA, 0x30));
            float m20 = (float)((long double)q4 * M(bodyB, 0x30) + m30);
            long double den = ((((long double)m18 + (long double)q2 * M(bodyA, 0x38)) +
                                m24) +
                               m20) +
                              g_14a23a4;
            e[3] = (float)(1.0L / den);
            cmd[0] = 0xc060b;
            cmd[2] = 0x3f800000;
            // `fld [ecx+8]` (ecx = param_1) / `fmul [b]` / `fstp [edi-8]`: the middle
            // command word is p[2] read as a float and scaled by the time step b[0];
            // it is stored as a *float* (a raw fstp), so no int conversion.
            *(float*)(cmd + 1) = *(float*)(p + 2) * b[0];
            e[7] = *src * b[1];
            src += 2;
            v += 4;
            e += 8;
            cmd += 3;
        } while (--n != 0);
    }
    stack_[1] = (int)cmd;
    int* end = stack_;
    end[0] = (int)e;
    return (int)end;
}

// @ 0x010aa5f0
extern "C" void FUN_010aa5f0(hkReal* a, hkConstraintCore* c, hkJacobian* out)
{
    hkReal* dst = (hkReal*)out->m_cursor;
    hkMassAndVelocity* bodyA = c->m_bodyA;
    hkReal tau = c->m_f18;
    hkMassAndVelocity* bodyB = c->m_bodyB;

    dst[0] = a[4];
    dst[1] = a[5];
    dst[2] = a[6];
    dst[3] = a[7];

    hkVector4_s010a_a5f0 rA, rB;
    rA.x = a[0] - bodyA->m_centerOfMass[0];
    rA.y = a[1] - bodyA->m_centerOfMass[1];
    rA.z = a[2] - bodyA->m_centerOfMass[2];
    rB.x = a[0] - bodyB->m_centerOfMass[0];
    rB.y = a[1] - bodyB->m_centerOfMass[1];
    rB.z = a[2] - bodyB->m_centerOfMass[2];

    hkReal cA0 = rA.y * a[6] - rA.z * a[5];
    hkReal cA1 = rA.z * a[4] - rA.x * a[6];
    hkReal cA2 = rA.x * a[5] - rA.y * a[4];

    if (bodyA->m_useInvInertia == 0) {
        dst[4] = cA0 * bodyA->m_invInertia[0] +
                 (cA1 * bodyA->m_invInertia[4] + cA2 * bodyA->m_invInertia[8]);
        dst[5] = cA0 * bodyA->m_invInertia[1] +
                 (cA1 * bodyA->m_invInertia[5] + cA2 * bodyA->m_invInertia[9]);
        dst[6] = cA0 * bodyA->m_invInertia[2] +
                 (cA1 * bodyA->m_invInertia[6] + cA2 * bodyA->m_invInertia[10]);
    } else {
        dst[4] = cA0;
        dst[5] = cA1;
        dst[6] = cA2;
    }
    dst[7] = 0.0f;

    hkReal cB0 = rB.z * a[5] - rB.y * a[6];
    hkReal cB1 = rB.x * a[6] - rB.z * a[4];
    hkReal cB2 = rB.y * a[4] - rB.x * a[5];

    if (bodyB->m_useInvInertia == 0) {
        dst[8]  = cB0 * bodyB->m_invInertia[0] +
                  (cB1 * bodyB->m_invInertia[4] + cB2 * bodyB->m_invInertia[8]);
        dst[9]  = cB0 * bodyB->m_invInertia[1] +
                  (cB1 * bodyB->m_invInertia[5] + cB2 * bodyB->m_invInertia[9]);
        dst[10] = cB0 * bodyB->m_invInertia[2] +
                  (cB1 * bodyB->m_invInertia[6] + cB2 * bodyB->m_invInertia[10]);
        dst[11] = 0.0f;
    } else {
        dst[8]  = cB0;
        dst[9]  = cB1;
        dst[10] = cB2;
        dst[11] = 0.0f;
    }

    hkReal invMass =
        ((((dst[10] * dst[10]) * bodyB->m_invInertia[2] +
           (dst[6]  * dst[6])  * bodyA->m_invInertia[2]) +
          ((dst[9]  * dst[9])  * bodyB->m_invInertia[1] +
           (dst[5]  * dst[5])  * bodyA->m_invInertia[1])) +
         ((dst[8]  * dst[8])  * bodyB->m_invInertia[0] +
          (dst[4]  * dst[4])  * bodyA->m_invInertia[0])) +
        ((bodyB->m_cfmScalar + bodyA->m_cfmScalar) + HK_REAL_EPSILON);

    dst[11] = invMass;
    dst[7]  = tau / invMass;

    hkReal g1 = *(hkReal*)((char*)(*(int*)(a + 9)) + 4);
    hkReal* p = (hkReal*)out->m_typeCursor;
    hkReal g3 = a[8];
    hkReal g4 = *(hkReal*)c;
    ((u32*)p)[0] = 0xc0508;
    ((u32*)p)[2] = 0x3f800000;
    p[1] = g3 * g4;
    out->m_cursor = dst + 0xc;
    out->m_typeCursor = p + 3;
    dst[3] = g1 * c->m_f14;
}

// @ 0x010aa890
extern "C" void FUN_010aa890(hkReal* a, hkConstraintCore* c, hkJacobian* out)
{
    hkMassAndVelocity* bodyA = c->m_bodyA;
    hkReal tau = c->m_f18;
    hkMassAndVelocity* bodyB = c->m_bodyB;
    hkReal f4 = c->m_f14;
    hkReal* dst = (hkReal*)out->m_cursor;
    hkReal* p = (hkReal*)out->m_typeCursor;

    dst[0] = a[8];
    dst[1] = a[9];
    dst[2] = a[10];
    dst[3] = a[0xb];

    hkVector4_s010a_a5f0 rA, rB;
    rA.x = a[0] - bodyA->m_centerOfMass[0];
    rA.y = a[1] - bodyA->m_centerOfMass[1];
    rA.z = a[2] - bodyA->m_centerOfMass[2];
    rB.x = a[4] - bodyB->m_centerOfMass[0];
    rB.y = a[5] - bodyB->m_centerOfMass[1];
    rB.z = a[6] - bodyB->m_centerOfMass[2];

    hkReal cA0 = rA.y * a[10] - rA.z * a[9];
    hkReal cA1 = rA.z * a[8] - rA.x * a[10];
    hkReal cA2 = rA.x * a[9] - rA.y * a[8];

    if (bodyA->m_useInvInertia == 0) {
        dst[4] = cA0 * bodyA->m_invInertia[0] +
                 (cA1 * bodyA->m_invInertia[4] + cA2 * bodyA->m_invInertia[8]);
        dst[5] = cA0 * bodyA->m_invInertia[1] +
                 (cA1 * bodyA->m_invInertia[5] + cA2 * bodyA->m_invInertia[9]);
        dst[6] = cA0 * bodyA->m_invInertia[2] +
                 (cA1 * bodyA->m_invInertia[6] + cA2 * bodyA->m_invInertia[10]);
    } else {
        dst[4] = cA0;
        dst[5] = cA1;
        dst[6] = cA2;
    }
    dst[7] = 0.0f;

    hkReal cB0 = rB.z * a[9] - rB.y * a[10];
    hkReal cB1 = rB.x * a[10] - rB.z * a[8];
    hkReal cB2 = rB.y * a[8] - rB.x * a[9];

    if (bodyB->m_useInvInertia == 0) {
        dst[8]  = cB0 * bodyB->m_invInertia[0] +
                  (cB1 * bodyB->m_invInertia[4] + cB2 * bodyB->m_invInertia[8]);
        dst[9]  = cB0 * bodyB->m_invInertia[1] +
                  (cB1 * bodyB->m_invInertia[5] + cB2 * bodyB->m_invInertia[9]);
        dst[10] = cB0 * bodyB->m_invInertia[2] +
                  (cB1 * bodyB->m_invInertia[6] + cB2 * bodyB->m_invInertia[10]);
        dst[11] = 0.0f;
    } else {
        dst[8]  = cB0;
        dst[9]  = cB1;
        dst[10] = cB2;
        dst[11] = 0.0f;
    }

    hkReal invMass =
        ((((dst[10] * dst[10]) * bodyB->m_invInertia[2] +
           (dst[6]  * dst[6])  * bodyA->m_invInertia[2]) +
          ((dst[9]  * dst[9])  * bodyB->m_invInertia[1] +
           (dst[5]  * dst[5])  * bodyA->m_invInertia[1])) +
         ((dst[8]  * dst[8])  * bodyB->m_invInertia[0] +
          (dst[4]  * dst[4])  * bodyA->m_invInertia[0])) +
        ((bodyB->m_cfmScalar + bodyA->m_cfmScalar) + HK_REAL_EPSILON);

    dst[11] = invMass;
    dst[7]  = tau / invMass;

    dst[3] = ((a[5] - a[1]) * a[9] +
              ((a[6] - a[2]) * a[10] + (a[4] - a[0]) * a[8])) * f4;

    ((u32*)p)[0] = 0x4050f;
    out->m_cursor = dst + 0xc;
    out->m_typeCursor = p + 1;
}

// @ 0x010aab50
extern "C" void FUN_010aab50(hkReal* a, hkConstraintCore* c, hkJacobian* out)
{
    hkMassAndVelocity* bodyA = c->m_bodyA;
    hkReal tau = c->m_f14;
    hkMassAndVelocity* bodyB = c->m_bodyB;
    hkReal* dst = (hkReal*)out->m_cursor;
    hkReal* p = (hkReal*)out->m_typeCursor;

    dst[0] = a[8];
    dst[1] = a[9];
    dst[2] = a[10];
    dst[3] = a[0xb];

    hkVector4_s010a_a5f0 rA, rB;
    rA.x = a[0] - bodyA->m_centerOfMass[0];
    rA.y = a[1] - bodyA->m_centerOfMass[1];
    rA.z = a[2] - bodyA->m_centerOfMass[2];
    rB.x = a[4] - bodyB->m_centerOfMass[0];
    rB.y = a[5] - bodyB->m_centerOfMass[1];
    rB.z = a[6] - bodyB->m_centerOfMass[2];

    hkReal cA0 = rA.y * a[10] - rA.z * a[9];
    hkReal cA1 = rA.z * a[8] - rA.x * a[10];
    hkReal cA2 = rA.x * a[9] - rA.y * a[8];

    if (bodyA->m_useInvInertia == 0) {
        dst[4] = cA0 * bodyA->m_invInertia[0] +
                 (cA1 * bodyA->m_invInertia[4] + cA2 * bodyA->m_invInertia[8]);
        dst[5] = cA0 * bodyA->m_invInertia[1] +
                 (cA1 * bodyA->m_invInertia[5] + cA2 * bodyA->m_invInertia[9]);
        dst[6] = cA0 * bodyA->m_invInertia[2] +
                 (cA1 * bodyA->m_invInertia[6] + cA2 * bodyA->m_invInertia[10]);
    } else {
        dst[4] = cA0;
        dst[5] = cA1;
        dst[6] = cA2;
    }
    dst[7] = 0.0f;

    hkReal cB0 = rB.z * a[9] - rB.y * a[10];
    hkReal cB1 = rB.x * a[10] - rB.z * a[8];
    hkReal cB2 = rB.y * a[8] - rB.x * a[9];

    if (bodyB->m_useInvInertia == 0) {
        dst[8]  = cB0 * bodyB->m_invInertia[0] +
                  (cB1 * bodyB->m_invInertia[4] + cB2 * bodyB->m_invInertia[8]);
        dst[9]  = cB0 * bodyB->m_invInertia[1] +
                  (cB1 * bodyB->m_invInertia[5] + cB2 * bodyB->m_invInertia[9]);
        dst[10] = cB0 * bodyB->m_invInertia[2] +
                  (cB1 * bodyB->m_invInertia[6] + cB2 * bodyB->m_invInertia[10]);
        dst[11] = 0.0f;
    } else {
        dst[8]  = cB0;
        dst[9]  = cB1;
        dst[10] = cB2;
        dst[11] = 0.0f;
    }

    hkReal invMass =
        ((((dst[10] * dst[10]) * bodyB->m_invInertia[2] +
           (dst[6]  * dst[6])  * bodyA->m_invInertia[2]) +
          ((dst[9]  * dst[9])  * bodyB->m_invInertia[1] +
           (dst[5]  * dst[5])  * bodyA->m_invInertia[1])) +
         ((dst[8]  * dst[8])  * bodyB->m_invInertia[0] +
          (dst[4]  * dst[4])  * bodyA->m_invInertia[0])) +
        ((bodyB->m_cfmScalar + bodyA->m_cfmScalar) + HK_REAL_EPSILON);

    dst[11] = invMass;
    dst[7]  = HK_REAL_ONE / invMass;

    dst[3] = ((a[6] - a[2]) * a[10] +
              ((a[5] - a[1]) * a[9] + (a[4] - a[0]) * a[8])) * tau;

    p[1] = a[0xc];
    ((u32*)p)[0] = 0xc0510;
    p[2] = a[0xd];
    out->m_cursor = dst + 0xc;
    out->m_typeCursor = p + 3;
}

// @ 0x010aae10
extern "C" void FUN_010aae10(hkReal* a, hkConstraintCore* c, hkJacobian* out)
{
    hkReal* dst = (hkReal*)out->m_cursor;
    hkReal f4 = c->m_f14;
    hkReal tau = c->m_f18;
    hkMassAndVelocity* bodyA = c->m_bodyA;
    hkMassAndVelocity* bodyB = c->m_bodyB;

    dst[0] = a[8];
    dst[1] = a[9];
    dst[2] = a[10];
    dst[3] = a[0xb];

    hkVector4_s010a_a5f0 rA, rB;
    rA.x = a[0] - bodyA->m_centerOfMass[0];
    rA.y = a[1] - bodyA->m_centerOfMass[1];
    rA.z = a[2] - bodyA->m_centerOfMass[2];
    rB.x = a[4] - bodyB->m_centerOfMass[0];
    rB.y = a[5] - bodyB->m_centerOfMass[1];
    rB.z = a[6] - bodyB->m_centerOfMass[2];

    hkReal cA0 = rA.y * a[10] - rA.z * a[9];
    hkReal cA1 = rA.z * a[8] - rA.x * a[10];
    hkReal cA2 = rA.x * a[9] - rA.y * a[8];

    if (bodyA->m_useInvInertia == 0) {
        dst[4] = cA0 * bodyA->m_invInertia[0] +
                 (cA1 * bodyA->m_invInertia[4] + cA2 * bodyA->m_invInertia[8]);
        dst[5] = cA0 * bodyA->m_invInertia[1] +
                 (cA1 * bodyA->m_invInertia[5] + cA2 * bodyA->m_invInertia[9]);
        dst[6] = cA0 * bodyA->m_invInertia[2] +
                 (cA1 * bodyA->m_invInertia[6] + cA2 * bodyA->m_invInertia[10]);
    } else {
        dst[4] = cA0;
        dst[5] = cA1;
        dst[6] = cA2;
    }
    dst[7] = 0.0f;

    hkReal cB0 = rB.z * a[9] - rB.y * a[10];
    hkReal cB1 = rB.x * a[10] - rB.z * a[8];
    hkReal cB2 = rB.y * a[8] - rB.x * a[9];

    if (bodyB->m_useInvInertia == 0) {
        dst[8]  = cB0 * bodyB->m_invInertia[0] +
                  (cB1 * bodyB->m_invInertia[4] + cB2 * bodyB->m_invInertia[8]);
        dst[9]  = cB0 * bodyB->m_invInertia[1] +
                  (cB1 * bodyB->m_invInertia[5] + cB2 * bodyB->m_invInertia[9]);
        dst[10] = cB0 * bodyB->m_invInertia[2] +
                  (cB1 * bodyB->m_invInertia[6] + cB2 * bodyB->m_invInertia[10]);
        dst[11] = 0.0f;
    } else {
        dst[8]  = cB0;
        dst[9]  = cB1;
        dst[10] = cB2;
        dst[11] = 0.0f;
    }

    hkReal invMass =
        ((((dst[10] * dst[10]) * bodyB->m_invInertia[2] +
           (dst[6]  * dst[6])  * bodyA->m_invInertia[2]) +
          ((dst[9]  * dst[9])  * bodyB->m_invInertia[1] +
           (dst[5]  * dst[5])  * bodyA->m_invInertia[1])) +
         ((dst[8]  * dst[8])  * bodyB->m_invInertia[0] +
          (dst[4]  * dst[4])  * bodyA->m_invInertia[0])) +
        ((bodyB->m_cfmScalar + bodyA->m_cfmScalar) + HK_REAL_EPSILON);

    dst[11] = invMass;
    dst[7]  = tau / invMass;

    dst[3] = ((a[6] - a[2]) * a[10] +
              ((a[4] - a[0]) * a[8] + (a[5] - a[1]) * a[9])) * f4;

    hkReal f1b = c->m_f14;
    hkReal f4b = a[0xc];
    hkReal f2b = a[0xd];
    hkReal* p = (hkReal*)out->m_typeCursor;
    ((u32*)p)[0] = 0xc050d;
    p[1] = -f1b * f4b;
    p[2] = -f1b * f2b;
    out->m_cursor = dst + 0xc;
    out->m_typeCursor = p + 3;
}

// @ 0x010ab0e0
extern "C" void FUN_010ab0e0(hkReal* a, hkConstraintCore* c, hkJacobian* out)
{
    hkReal f1 = a[7];
    hkReal* dst = (hkReal*)out->m_cursor;
    hkMassAndVelocity* bodyB = c->m_bodyB;
    hkMassAndVelocity* bodyA = c->m_bodyA;
    hkReal* p = (hkReal*)out->m_typeCursor;

    if (bodyA->m_useInvInertia == 0) {
        hkReal x = a[0];
        hkReal y = a[1];
        hkReal z = a[2];
        dst[0] = x * bodyA->m_invInertia[0] +
                 (y * bodyA->m_invInertia[4] + z * bodyA->m_invInertia[8]);
        dst[1] = x * bodyA->m_invInertia[1] +
                 (y * bodyA->m_invInertia[5] + z * bodyA->m_invInertia[9]);
        dst[2] = x * bodyA->m_invInertia[2] +
                 (y * bodyA->m_invInertia[6] + z * bodyA->m_invInertia[10]);
        dst[3] = 0.0f;
    } else {
        dst[0] = a[0];
        dst[1] = a[1];
        dst[2] = a[2];
        dst[3] = a[3];
    }

    hkReal nx = -a[0];
    if (bodyB->m_useInvInertia == 0) {
        hkReal ny = -a[1];
        hkReal nz = -a[2];
        dst[4] = nx * bodyB->m_invInertia[0] +
                 (nz * bodyB->m_invInertia[8] + ny * bodyB->m_invInertia[4]);
        dst[5] = nz * bodyB->m_invInertia[9] +
                 (ny * bodyB->m_invInertia[5] + nx * bodyB->m_invInertia[1]);
        dst[6] = nz * bodyB->m_invInertia[10] +
                 (ny * bodyB->m_invInertia[6] + nx * bodyB->m_invInertia[2]);
        dst[7] = 0.0f;
    } else {
        dst[4] = nx;
        dst[5] = -a[1];
        dst[6] = -a[2];
        dst[7] = -a[3];
    }

    dst[3] = HK_REAL_ONE /
        (((((dst[6] * dst[6]) * bodyB->m_invInertia[2] +
            (dst[2] * dst[2]) * bodyA->m_invInertia[2]) +
           ((dst[4] * dst[4]) * bodyB->m_invInertia[0] +
            (dst[0] * dst[0]) * bodyA->m_invInertia[0])) +
          ((dst[5] * dst[5]) * bodyB->m_invInertia[1] +
           (dst[1] * dst[1]) * bodyA->m_invInertia[1])) +
         HK_REAL_EPSILON);

    hkReal f2 = -*(hkReal*)((char*)c + 4);
    hkReal f3 = a[4];
    hkReal f4 = a[5];
    ((u32*)p)[0] = 0x10060c;
    p[1] = (f2 * f3) * f1;
    p[2] = (f2 * f4) * f1;
    p[3] = f1;
    out->m_typeCursor = p + 4;
    out->m_cursor = dst + 8;
    dst[7] = f2 * a[6];
}

// @ 0x010ab2d0
void _hk3AxisConstraintBuildJacobian(const unsigned char* bodyA, const unsigned char* bodyB, const unsigned char* data, const unsigned char* out)
{
    static const hkReal kBasis[12] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f
    };

    const unsigned char* pa = *(const unsigned char* const*)(data + 0x28);
    const unsigned char* pb = *(const unsigned char* const*)(data + 0x2c);

    hkVector4_s010a_b2d0* o = (hkVector4_s010a_b2d0*)out;

    for (int i = 0; i < 3; ++i)
    {
        hkVector4_s010a_b2d0 axis;
        axis.x = kBasis[i * 4 + 0];
        axis.y = kBasis[i * 4 + 1];
        axis.z = kBasis[i * 4 + 2];
        axis.w = kBasis[i * 4 + 3];

        hkVector4_s010a_b2d0 pA;
        pA.x = *(const hkReal*)(bodyA + 0) - *(const hkReal*)(pa + 0x40);
        pA.y = *(const hkReal*)(bodyA + 4) - *(const hkReal*)(pa + 0x44);
        pA.z = *(const hkReal*)(bodyA + 8) - *(const hkReal*)(pa + 0x48);
        pA.w = 0.0f;

        hkVector4_s010a_b2d0 pB;
        pB.x = *(const hkReal*)(bodyB + 0) - *(const hkReal*)(pb + 0x40);
        pB.y = *(const hkReal*)(bodyB + 4) - *(const hkReal*)(pb + 0x44);
        pB.z = *(const hkReal*)(bodyB + 8) - *(const hkReal*)(pb + 0x48);
        pB.w = 0.0f;

        hkReal sign = (*(const unsigned char*)(data + 0x0c) != 0) ? -1.0f : 1.0f;

        o[i * 3 + 0] = axis;
        o[i * 3 + 1] = hkCross(pA, axis);
        o[i * 3 + 2] = hkCross(pB, axis);
        o[i * 3 + 2].x *= sign;
        o[i * 3 + 2].y *= sign;
        o[i * 3 + 2].z *= sign;
    }
}

// @ 0x010ab5d0
void _hkPulleyConstraintBuildJacobian(const unsigned char* atoms, const unsigned char* bodyA, const unsigned char* bodyB, const unsigned char* out)
{
    hkVector4_s010a_b2d0 sepA;
    sepA.x = *(const hkReal*)(atoms + 0x20) - *(const hkReal*)(atoms + 0x00);
    sepA.y = *(const hkReal*)(atoms + 0x24) - *(const hkReal*)(atoms + 0x04);
    sepA.z = *(const hkReal*)(atoms + 0x28) - *(const hkReal*)(atoms + 0x08);
    sepA.w = *(const hkReal*)(atoms + 0x2c) - *(const hkReal*)(atoms + 0x0c);

    hkVector4_s010a_b2d0 sepB;
    sepB.x = *(const hkReal*)(atoms + 0x10) - *(const hkReal*)(atoms + 0x30);
    sepB.y = *(const hkReal*)(atoms + 0x14) - *(const hkReal*)(atoms + 0x34);
    sepB.z = *(const hkReal*)(atoms + 0x18) - *(const hkReal*)(atoms + 0x38);
    sepB.w = *(const hkReal*)(atoms + 0x1c) - *(const hkReal*)(atoms + 0x3c);

    const hkReal lenA = hkLen3(sepA);
    const hkReal lenB = hkLen3(sepB);
    const hkReal leverage = *(const hkReal*)(atoms + 0x40);

    hkVector4_s010a_b2d0 nA, nB;
    const hkReal invA = (lenA != 0.0f) ? 1.0f / lenA : 0.0f;
    const hkReal invB = (lenB != 0.0f) ? 1.0f / lenB : 0.0f;
    nA.x = sepA.x * invA; nA.y = sepA.y * invA; nA.z = sepA.z * invA; nA.w = 0.0f;
    nB.x = sepB.x * invB * leverage;
    nB.y = sepB.y * invB * leverage;
    nB.z = sepB.z * invB * leverage;
    nB.w = 0.0f;

    const unsigned char* ra = *(const unsigned char* const*)(bodyA + 0x28);
    const unsigned char* rb = *(const unsigned char* const*)(bodyB + 0x28);

    hkVector4_s010a_b2d0 rA;
    rA.x = *(const hkReal*)(ra + 0x20);
    rA.y = *(const hkReal*)(ra + 0x24);
    rA.z = *(const hkReal*)(ra + 0x28);
    rA.w = 0.0f;

    hkVector4_s010a_b2d0 rB;
    rB.x = *(const hkReal*)(rb + 0x20);
    rB.y = *(const hkReal*)(rb + 0x24);
    rB.z = *(const hkReal*)(rb + 0x28);
    rB.w = 0.0f;

    hkVector4_s010a_b2d0* o = (hkVector4_s010a_b2d0*)out;
    o[0] = nA;
    o[1] = hkCross(rA, nA);
    o[2] = nB;
    o[3] = hkCross(rB, nB);
    o[4].x = lenA + lenB * leverage;   // rope length
    o[4].y = o[4].z = o[4].w = 0.0f;
    (void)bodyA;
    (void)bodyB;
}

// @ 0x010ac750
extern "C" void hk1dAngularVelocityMotorBeginJacobian(const hkVector4_s010a_bb90& directionOfConstraint, const hkpConstraintQueryIn& in, hkp2AngJacobian& jac, hkp1dBilateralConstraintStatus& statusOut)
{
	const hkSolverBody* bodyA = in.m_bodyA;
	const hkSolverBody* bodyB = in.m_bodyB;
	hkVector4_s010a_bb90& jacA = jac.m_angular[0];
	hkVector4_s010a_bb90& jacB = jac.m_angular[1];

	if (bodyA->m_hasInfiniteMass)
	{
		jacA = directionOfConstraint;
	}
	else
	{
		setRotatedInverseDir(jacA, bodyA->m_rotation, directionOfConstraint);
	}

	if (bodyB->m_hasInfiniteMass)
	{
		jacB.x = -directionOfConstraint.x;
		jacB.y = -directionOfConstraint.y;
		jacB.z = -directionOfConstraint.z;
		jacB.w = -directionOfConstraint.w;
	}
	else
	{
		setRotatedInverseDirNeg(jacB, bodyB->m_rotation, directionOfConstraint);
	}

	hkVector4_s010a_bb90 sqA;
	hkVector4_s010a_bb90 sqB;
	sqA.x = jacA.x * jacA.x;
	sqA.y = jacA.y * jacA.y;
	sqA.z = jacA.z * jacA.z;
	sqB.x = jacB.x * jacB.x;
	sqB.y = jacB.y * jacB.y;
	sqB.z = jacB.z * jacB.z;

	float invMass = (((sqB.z * bodyB->m_inertiaAndMassInv.z +
	                  sqA.z * bodyA->m_inertiaAndMassInv.z) +
	                 (sqB.y * bodyB->m_inertiaAndMassInv.y +
	                  sqA.y * bodyA->m_inertiaAndMassInv.y)) +
	                (sqB.x * bodyB->m_inertiaAndMassInv.x +
	                 sqA.x * bodyA->m_inertiaAndMassInv.x)) +
	                _HK_REAL_EPSILON;
	invMass = _HK_REAL_ONE / invMass;

	jacA.w = invMass;
	statusOut.m_virtualMass = invMass;
}

// @ 0x010adab0
void __cdecl hkPoweredChain_CalculateVelocities(int *param_1,int param_2)
{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  int *piVar5;
  float fVar6;
  int iVar7;
  float fVar8;
  float fVar9;
  float *pfVar10;
  float *pfVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  float *local_574;
  float *local_570;
  float *local_56c;
  int local_55c;
  int local_554;
  
  local_570 = (float *)param_1[4];
  local_56c = (float *)param_1[5];
  local_554 = 0;
  if (0 < param_1[1]) {
    local_55c = 0;
    pfVar10 = local_570 + 0x12;
    pfVar11 = local_56c + 0xe;
    local_574 = (float *)(param_2 + 8);
    do {
      iVar14 = param_1[7];
      piVar5 = (int *)(param_1[6] + local_554 * 4);
      iVar7 = *piVar5;
      iVar12 = iVar7 + iVar14;
      iVar13 = piVar5[1] + iVar14;
      pfVar1 = (float *)(iVar12 + 0x40);
      pfVar2 = (float *)(iVar12 + 0x50);
      pfVar3 = (float *)(iVar13 + 0x40);
      pfVar4 = (float *)(iVar13 + 0x50);
      fVar6 = *(float*)&param_1[2] * *(float *)(*param_1 + 0x40);
      fVar8 = *(float*)&param_1[3];
      local_574[-2] =
           *(float*)&param_1[2] * pfVar10[-0xf] -
           (((((*(float *)(iVar13 + 0x58) * pfVar10[-8] + *(float *)(iVar12 + 0x58) * pfVar10[-0xc])
              + (*(float *)(iVar12 + 0x48) - *(float *)(iVar13 + 0x48)) * pfVar10[-0x10]) * fVar6 +
             (((*(float *)(iVar13 + 0x28) - *(float *)(iVar13 + 0x58)) * pfVar10[-8] +
              (*(float *)(iVar12 + 0x28) - *(float *)(iVar12 + 0x58)) * pfVar10[-0xc]) +
             ((*(float *)(iVar12 + 0x18) - *(float *)(iVar12 + 0x48)) -
             (*(float *)(iVar13 + 0x18) - *(float *)(iVar13 + 0x48))) * pfVar10[-0x10]) * fVar8) +
            (((*(float *)(iVar13 + 0x54) * pfVar10[-9] + *(float *)(iVar12 + 0x54) * pfVar10[-0xd])
             + (*(float *)(iVar12 + 0x44) - *(float *)(iVar13 + 0x44)) * pfVar10[-0x11]) * fVar6 +
            (((*(float *)(iVar13 + 0x24) - *(float *)(iVar13 + 0x54)) * pfVar10[-9] +
             (*(float *)(iVar12 + 0x24) - *(float *)(iVar12 + 0x54)) * pfVar10[-0xd]) +
            ((*(float *)(iVar12 + 0x14) - *(float *)(iVar12 + 0x44)) -
            (*(float *)(iVar13 + 0x14) - *(float *)(iVar13 + 0x44))) * pfVar10[-0x11]) * fVar8)) +
           (((*pfVar4 * pfVar10[-10] + *pfVar2 * pfVar10[-0xe]) + (*pfVar1 - *pfVar3) * *local_570)
            * fVar6 +
           fVar8 * (((*(float *)(iVar13 + 0x20) - *pfVar4) * pfVar10[-10] +
                    (*(float *)(iVar12 + 0x20) - *pfVar2) * pfVar10[-0xe]) +
                   ((*(float *)(iVar7 + 0x10 + iVar14) - *(float *)(iVar12 + 0x40)) -
                   (*(float *)(iVar13 + 0x10) - *pfVar3)) * *local_570)));
      fVar6 = *(float*)&param_1[2] * *(float *)(*param_1 + 0x40);
      fVar8 = *(float*)&param_1[3];
      local_574[-1] =
           *(float*)&param_1[2] * pfVar10[-3] -
           (((((*pfVar4 * pfVar10[2] + *pfVar2 * pfVar10[-2]) + (*pfVar1 - *pfVar3) * pfVar10[-6]) *
              fVar6 + fVar8 * (((*(float *)(iVar13 + 0x20) - *pfVar4) * pfVar10[2] +
                               (*(float *)(iVar12 + 0x20) - *pfVar2) * pfVar10[-2]) +
                              ((*(float *)(iVar12 + 0x10) - *pfVar1) -
                              (*(float *)(iVar13 + 0x10) - *pfVar3)) * pfVar10[-6])) +
            ((((*(float *)(iVar13 + 0x28) - *(float *)(iVar13 + 0x58)) * pfVar10[4] +
              (*(float *)(iVar12 + 0x28) - *(float *)(iVar12 + 0x58)) * *pfVar10) +
             ((*(float *)(iVar12 + 0x18) - *(float *)(iVar12 + 0x48)) -
             (*(float *)(iVar13 + 0x18) - *(float *)(iVar13 + 0x48))) * pfVar10[-4]) * fVar8 +
            fVar6 * ((*(float *)(iVar12 + 0x48) - *(float *)(iVar13 + 0x48)) * pfVar10[-4] +
                    (*(float *)(iVar13 + 0x58) * pfVar10[4] + *(float *)(iVar12 + 0x58) * *pfVar10))
            )) + ((((*(float *)(iVar13 + 0x24) - *(float *)(iVar13 + 0x54)) * pfVar10[3] +
                   (*(float *)(iVar12 + 0x24) - *(float *)(iVar12 + 0x54)) * pfVar10[-1]) +
                  ((*(float *)(iVar12 + 0x14) - *(float *)(iVar12 + 0x44)) -
                  (*(float *)(iVar13 + 0x14) - *(float *)(iVar13 + 0x44))) * pfVar10[-5]) * fVar8 +
                 ((*(float *)(iVar12 + 0x44) - *(float *)(iVar13 + 0x44)) * pfVar10[-5] +
                 (*(float *)(iVar13 + 0x54) * pfVar10[3] + *(float *)(iVar12 + 0x54) * pfVar10[-1]))
                 * fVar6));
      fVar6 = *(float*)&param_1[2] * *(float *)(*param_1 + 0x40);
      fVar8 = *(float*)&param_1[3];
      *local_574 = *(float*)&param_1[2] * pfVar10[9] -
                   (((((*pfVar4 * pfVar10[0xe] + *pfVar2 * pfVar10[10]) +
                      (*pfVar1 - *pfVar3) * pfVar10[6]) * fVar6 +
                     fVar8 * (((*(float *)(iVar13 + 0x20) - *pfVar4) * pfVar10[0xe] +
                              (*(float *)(iVar12 + 0x20) - *pfVar2) * pfVar10[10]) +
                             ((*(float *)(iVar12 + 0x10) - *pfVar1) -
                             (*(float *)(iVar13 + 0x10) - *pfVar3)) * pfVar10[6])) +
                    (fVar6 * ((*(float *)(iVar13 + 0x58) * pfVar10[0x10] +
                              *(float *)(iVar12 + 0x58) * pfVar10[0xc]) +
                             (*(float *)(iVar12 + 0x48) - *(float *)(iVar13 + 0x48)) * pfVar10[8]) +
                    fVar8 * (((*(float *)(iVar13 + 0x28) - *(float *)(iVar13 + 0x58)) *
                              pfVar10[0x10] +
                             (*(float *)(iVar12 + 0x28) - *(float *)(iVar12 + 0x58)) * pfVar10[0xc])
                            + ((*(float *)(iVar12 + 0x18) - *(float *)(iVar12 + 0x48)) -
                              (*(float *)(iVar13 + 0x18) - *(float *)(iVar13 + 0x48))) * pfVar10[8])
                    )) + (((*(float *)(iVar13 + 0x54) * pfVar10[0xf] +
                           *(float *)(iVar12 + 0x54) * pfVar10[0xb]) +
                          (*(float *)(iVar12 + 0x44) - *(float *)(iVar13 + 0x44)) * pfVar10[7]) *
                          fVar6 + fVar8 * (((*(float *)(iVar13 + 0x24) - *(float *)(iVar13 + 0x54))
                                            * pfVar10[0xf] +
                                           (*(float *)(iVar12 + 0x24) - *(float *)(iVar12 + 0x54)) *
                                           pfVar10[0xb]) +
                                          ((*(float *)(iVar12 + 0x14) - *(float *)(iVar12 + 0x44)) -
                                          (*(float *)(iVar13 + 0x14) - *(float *)(iVar13 + 0x44))) *
                                          pfVar10[7])));
      local_574[1] = 0.0;
      fVar8 = *(float *)(param_1[9] + 0x10 + local_55c);
      iVar14 = param_1[9] + local_55c;
      fVar9 = fVar8 * *(float *)(*param_1 + 0x40);
      fVar6 = *(float *)(iVar14 + 0x14);
      local_574[2] = fVar8 * pfVar11[-7] -
                     ((((*pfVar4 * pfVar11[-10] + *pfVar2 * *local_56c) * fVar9 +
                       ((*(float *)(iVar13 + 0x20) - *pfVar4) * pfVar11[-10] +
                       (*(float *)(iVar12 + 0x20) - *pfVar2) * *local_56c) * fVar6) +
                      (fVar9 * (*(float *)(iVar13 + 0x58) * pfVar11[-8] +
                               *(float *)(iVar12 + 0x58) * pfVar11[-0xc]) +
                      fVar6 * ((*(float *)(iVar13 + 0x28) - *(float *)(iVar13 + 0x58)) * pfVar11[-8]
                              + (*(float *)(iVar12 + 0x28) - *(float *)(iVar12 + 0x58)) *
                                pfVar11[-0xc]))) +
                     (fVar9 * (*(float *)(iVar13 + 0x54) * pfVar11[-9] +
                              *(float *)(iVar12 + 0x54) * pfVar11[-0xd]) +
                     fVar6 * ((*(float *)(iVar13 + 0x24) - *(float *)(iVar13 + 0x54)) * pfVar11[-9]
                             + (*(float *)(iVar12 + 0x24) - *(float *)(iVar12 + 0x54)) *
                               pfVar11[-0xd])));
      fVar6 = *(float *)(iVar14 + 0x28) * *(float *)(*param_1 + 0x40);
      fVar8 = *(float *)(iVar14 + 0x2c);
      local_574[3] = *(float *)(iVar14 + 0x28) * pfVar11[1] -
                     ((((*pfVar4 * pfVar11[-2] + *pfVar2 * pfVar11[-6]) * fVar6 +
                       ((*(float *)(iVar13 + 0x20) - *pfVar4) * pfVar11[-2] +
                       (*(float *)(iVar12 + 0x20) - *pfVar2) * pfVar11[-6]) * fVar8) +
                      (fVar6 * (*(float *)(iVar13 + 0x58) * *pfVar11 +
                               *(float *)(iVar12 + 0x58) * pfVar11[-4]) +
                      fVar8 * ((*(float *)(iVar13 + 0x28) - *(float *)(iVar13 + 0x58)) * *pfVar11 +
                              (*(float *)(iVar12 + 0x28) - *(float *)(iVar12 + 0x58)) * pfVar11[-4])
                      )) + (fVar6 * (*(float *)(iVar13 + 0x54) * pfVar11[-1] +
                                    *(float *)(iVar12 + 0x54) * pfVar11[-5]) +
                           fVar8 * ((*(float *)(iVar13 + 0x24) - *(float *)(iVar13 + 0x54)) *
                                    pfVar11[-1] +
                                   (*(float *)(iVar12 + 0x24) - *(float *)(iVar12 + 0x54)) *
                                   pfVar11[-5])));
      fVar6 = *(float *)(iVar14 + 0x40) * *(float *)(*param_1 + 0x40);
      local_570 = local_570 + 0x24;
      local_56c = local_56c + 0x18;
      pfVar10 = pfVar10 + 0x24;
      local_55c = local_55c + 0x4c;
      fVar8 = *(float *)(iVar14 + 0x44);
      local_554 = local_554 + 1;
      local_574[4] = *(float *)(iVar14 + 0x40) * pfVar11[9] -
                     ((((*pfVar4 * pfVar11[6] + *pfVar2 * pfVar11[2]) * fVar6 +
                       ((*(float *)(iVar13 + 0x20) - *pfVar4) * pfVar11[6] +
                       (*(float *)(iVar12 + 0x20) - *pfVar2) * pfVar11[2]) * fVar8) +
                      (fVar6 * (*(float *)(iVar13 + 0x58) * pfVar11[8] +
                               *(float *)(iVar12 + 0x58) * pfVar11[4]) +
                      fVar8 * ((*(float *)(iVar13 + 0x28) - *(float *)(iVar13 + 0x58)) * pfVar11[8]
                              + (*(float *)(iVar12 + 0x28) - *(float *)(iVar12 + 0x58)) * pfVar11[4]
                              ))) +
                     (fVar6 * (*(float *)(iVar13 + 0x54) * pfVar11[7] +
                              *(float *)(iVar12 + 0x54) * pfVar11[3]) +
                     fVar8 * ((*(float *)(iVar13 + 0x24) - *(float *)(iVar13 + 0x54)) * pfVar11[7] +
                             (*(float *)(iVar12 + 0x24) - *(float *)(iVar12 + 0x54)) * pfVar11[3])))
      ;
      local_574[5] = 0.0;
      pfVar11 = pfVar11 + 0x18;
      local_574 = local_574 + 8;
    } while (local_554 < param_1[1]);
  }
  return;
}

// @ 0x010aed40
void _hkPoweredChain_RestoreVelocityValue(int i, int k, const unsigned char* d, hkReal* out)
{
    const int*           idx = *(const int* const*)(d + 0x18);
    const unsigned char* ref = *(const unsigned char* const*)(d + 0x1c);
    const unsigned char* P   = ref + idx[i];
    const unsigned char* Q   = ref + idx[i + 1];

    const unsigned char* row = *(const unsigned char* const*)(d + 0x24) + i * 0x4c;
    const hkReal*        T   = (const hkReal*)(row + k * 24);
    const hkReal*        m   = (const hkReal*)(*(const unsigned char* const*)(d + 0x14) + (k + 3 * i) * 32);

    hkVector4_s010a_ed40 a;                                    // body-A pivot displacement
    a.x = *(const hkReal*)(P + 0x20) - *(const hkReal*)(P + 0x50);
    a.y = *(const hkReal*)(P + 0x24) - *(const hkReal*)(P + 0x54);
    a.z = *(const hkReal*)(P + 0x28) - *(const hkReal*)(P + 0x58);

    hkVector4_s010a_ed40 b;                                    // body-B pivot displacement
    b.x = *(const hkReal*)(Q + 0x20) - *(const hkReal*)(Q + 0x50);
    b.y = *(const hkReal*)(Q + 0x24) - *(const hkReal*)(Q + 0x54);
    b.z = *(const hkReal*)(Q + 0x28) - *(const hkReal*)(Q + 0x58);

    hkVector4_s010a_ed40 p;                                    // A reference (P + 0x50)
    p.x = *(const hkReal*)(P + 0x50);
    p.y = *(const hkReal*)(P + 0x54);
    p.z = *(const hkReal*)(P + 0x58);
    p.w = *(const hkReal*)(P + 0x5c);

    hkVector4_s010a_ed40 q;                                    // B reference (Q + 0x50)
    q.x = *(const hkReal*)(Q + 0x50);
    q.y = *(const hkReal*)(Q + 0x54);
    q.z = *(const hkReal*)(Q + 0x58);
    q.w = *(const hkReal*)(Q + 0x5c);

    // (a, b) projected through the row rotation, plus the (p, q) terms and the
    // stored row offset T[4] / T[5].
    hkReal v = (a.x * m[0] + b.x * m[4])
             + (a.y * m[1] + b.y * m[5])
             + (a.z * m[2] + b.z * m[6])
             + (p.z * m[4] + q.x * m[6])
             + (p.z * m[2])
             + (p.w * m[5] + p.y * m[1])
             + T[4] - T[5];

    out[i * 8 + k + 4] = v;
}

// @ 0x010aef10
void _hkPoweredChain_AccumulateConstraintVelocities(const unsigned char* chain, hkVector4_s010a_ed40* out)
{
    const int    n     = *(const int*)(chain + 4);
    const hkReal* basis = (const hkReal*)*(const unsigned char* const*)(chain + 0x20);
    const hkReal* pos   = (const hkReal*)(*(const unsigned char* const*)(chain + 0x28) + 0x20);

    out[0].x = out[0].y = out[0].z = out[0].w = 0.0f;
    out[1].x = out[1].y = out[1].z = out[1].w = 0.0f;

    for (int i = n - 1; i >= 0; --i)
    {
        const hkReal* m  = basis + i * 8;           // 0x20 bytes per row
        const hkReal* v  = pos + i * 8;             // constraint pivot/velocity

        // Rotate the constraint's pivot velocity into chain space.
        hkVector4_s010a_ed40 r;
        r.x = v[0] * m[0x10] + v[1] * m[4] + v[2] * m[0];
        r.y = v[0] * m[0x14] + v[1] * m[5] + v[2] * m[1];
        r.z = v[0] * m[0x18] + v[1] * m[6] + v[2] * m[2];
        r.w = 0.0f;

        hkVector4_s010a_ed40 s;
        s.x = v[0] * m[0x40] + v[1] * m[0x50] + v[2] * m[0x30];
        s.y = v[0] * m[0x44] + v[1] * m[0x54] + v[2] * m[0x34];
        s.z = v[0] * m[0x48] + v[1] * m[0x58] + v[2] * m[0x38];
        s.w = 0.0f;

        out[0].x += r.x; out[0].y += r.y; out[0].z += r.z;
        out[1].x += s.x; out[1].y += s.y; out[1].z += s.z;
        out[1].w += m[0x154] * m[0x178] + m[0x168] * m[0x158];
    }
}

// @ 0x010af330
void _hkPoweredChain_ScanAndDisableMotors(const unsigned char* chain, int* outConstraint, int* outMotor, hkReal* outValue)
{
    const int            n      = *(const int*)(chain + 4);
    const unsigned char* flags  = *(const unsigned char* const*)(chain + 0x24);
    const unsigned char* basis  = *(const unsigned char* const*)(chain + 0x20);
    const unsigned char* pivots = *(const unsigned char* const*)(chain + 0x28) + 0x20;

    hkReal best      = -1.0f;                        // [esp + 0x0c]
    int    bestCon   = -1;                           // [esp + 0x14]
    int    bestMotor = -1;                           // [esp + 0x18]

    hkVector4_s010a_ed40 ang = { 0.0f, 0.0f, 0.0f, 0.0f };      // [esp + 0x20]
    hkVector4_s010a_ed40 lin = { 0.0f, 0.0f, 0.0f, 0.0f };      // [esp + 0x30]

    for (int i = n - 1; i >= 0; --i)
    {
        const unsigned char* b = basis + i * 0x3c0;
        const hkReal*        v = (const hkReal*)(pivots + i * 0x20);

        // Row's angular velocity error (columns at +0x180 .. +0x1b8).
        ang.x = v[0] * (*(const hkReal*)(b + 0x1b0)) + v[1] * (*(const hkReal*)(b + 0x1a0)) + v[2] * (*(const hkReal*)(b + 0x180));
        ang.y = v[0] * (*(const hkReal*)(b + 0x1b4)) + v[1] * (*(const hkReal*)(b + 0x1a4)) + v[2] * (*(const hkReal*)(b + 0x184));
        ang.z = v[0] * (*(const hkReal*)(b + 0x1b8)) + v[1] * (*(const hkReal*)(b + 0x1a8)) + v[2] * (*(const hkReal*)(b + 0x188));

        lin.x = v[0] * (*(const hkReal*)(b + 0x190)) + v[1] * (*(const hkReal*)(b + 0x1a0)) + v[2] * (*(const hkReal*)(b + 0x1b0));
        lin.y = v[0] * (*(const hkReal*)(b + 0x194)) + v[1] * (*(const hkReal*)(b + 0x1a4)) + v[2] * (*(const hkReal*)(b + 0x1b4));
        lin.z = v[0] * (*(const hkReal*)(b + 0x198)) + v[1] * (*(const hkReal*)(b + 0x1a8)) + v[2] * (*(const hkReal*)(b + 0x1b8));

        // The stored velocity is subtracted (vectors at v - 0x18 / v - 8).
        const hkReal* prev = v - 8;
        hkReal ex = ang.x - prev[0], ey = ang.y - prev[1], ez = ang.z - prev[2];
        hkReal fx = lin.x - prev[3], fy = lin.y - prev[4], fz = lin.z - prev[5];

        const unsigned char status = flags[i * 0x4c];

        if ((status & 0x03) == 0)
        {
            hkReal d = (*(const hkReal*)(b + 0x188) * 2.0f - ex) - (*(const hkReal*)(b + 0x184) * 2.0f - fy);
            if (!(d < best)) { }
            if (d >= best) { best = d; bestCon = i; bestMotor = 0; }
        }
        if ((status & 0x0c) == 0)
        {
            hkReal d = (*(const hkReal*)(b + 0x1a0) * 2.0f - ey) - (*(const hkReal*)(b + 0x19c) * 2.0f - fx);
            if (d >= best) { best = d; bestCon = i; bestMotor = 1; }
        }
        if ((status & 0x30) == 0)
        {
            hkReal d = (*(const hkReal*)(b + 0x1b8) * 2.0f - ez) - (*(const hkReal*)(b + 0x1b4) * 2.0f - fz);
            if (d >= best) { best = d; bestCon = i; bestMotor = 2; }
        }
    }

    if (bestCon < 0)
        return;

    unsigned char*       row = (unsigned char*)flags + bestCon * 0x4c;
    const hkReal*        lim = (const hkReal*)(row + bestMotor * 0x18);
    unsigned int         bits = (best > lim[1]) ? 3u : 1u;
    unsigned int         shift = (unsigned int)bestMotor * 2u;
    unsigned char        mask = (unsigned char)(3u << shift);

    *row = (unsigned char)((*row & ~mask) | ((unsigned char)bits << shift));
    *outConstraint = bestCon;
    *outMotor = bestMotor;
    (void)outValue;
}
