// slice s01085a80 -- Havok 3.1 hkWorld batch add/remove of entities, actions and phantoms, plus
// the broadphase/narrowphase getPenetrations query.
//
// Equivalent portable source, not byte-exact.  The HK_TIMER_* telemetry, the hkThreadMemory stack
// arrays and the pending-operation queue guard are modelled as named helpers, so the frame layout
// and register schedule differ from the retail build (each function compiles far smaller than the
// 389-987 byte originals).  Field accesses use named class members at the real offsets.
// Module flags: /vc71 (Havok dependency), /O2 /MD /Gy /EHsc /TP.
#include <stddef.h>
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed char    i8;

class hkVector4 { public: float x, y, z, w; };          // 16-byte SIMD vector

// ------------------------------------------------------------------ TLS / telemetry
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long index, void* value);

extern unsigned long g_hkThreadMemoryTlsIndex;      // 0x016e4174  per-thread hkThreadMemory slot
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4  monitor-stream write pointer
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8  monitor-stream end

enum { HK_ARRAY_FLAG_MASK = 0x3fffffff, HK_ARRAY_DONT_DEALLOCATE = (int)0x80000000 };

// ------------------------------------------------------------------ forward decls
class hkWorld; class hkEntity; class hkPhantom; class hkAction; class hkMotion; class hkShape;
class hkWorldObject; class hkSimulationIsland; class hkBroadPhase; class hkThreadMemory;
class hkWorldOperationQueue; class hkSimulation; class hkCollisionFilter; class hkCollidable;
class hkTypedBroadPhaseHandlePair; class hkCollidableCollidableFilter; class hkCdBodyPairCollector;
struct hkCollisionInput; struct hkProcessCollisionInput; struct hkWorldOperationBase;

// ------------------------------------------------------------------ memory
struct hkArrayUtil { static void _reserveMore(void* arr, int elemSize); };   // 0x0107f530

class hkThreadMemory { public:
    virtual void* v0(); virtual void* v1(); virtual void* v2();
    virtual void* allocate(unsigned nbytes);      // slot 3 (+0x0c)
    virtual void  releaseBlock(void* p);          // slot 4 (+0x10)
    char  pad04[0x1c];                            // +0x04
    void* m_current;                              // +0x20
    void* m_preallocStart;                        // +0x28
    void* m_end;                                  // +0x2c
    void deallocateChunk(void* p, int nbytes, int memClass);   // 0x0107db10
};
static inline hkThreadMemory* hkThreadMemoryInstance()
{
    return (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex);
}

// A 4-byte header matching hkArray's {data,size,caps} prefix, allocated on the hkThreadMemory TLS
// stack (this is the hkThreadMemory::allocateStack / hkArray stack-array macro pair).
struct hkStackArray {
    void* m_data;   // +0x00
    int   m_size;   // +0x04
    int   m_caps;   // +0x08
    void reserve(int nbytes)
    {
        hkThreadMemory* tm = hkThreadMemoryInstance();
        u32 need = ((u32)nbytes + 0x10) & 0xfffffff0u;
        char* p = (char*)tm->m_current;
        u32 end = (u32)p + need;
        if ((u32)tm->m_end < end) {
            m_data = tm->allocate(need);
        } else {
            tm->m_current = (void*)end;
            m_data = p;
        }
    }
};

// Free an hkThreadMemory stack array: rewind the stack and (only when the array owns its storage,
// i.e. caps has the sign bit clear) hand the block back to the thread allocator's chunk free list.
static inline void hkStackFree(void* data, int caps, int elemSize)
{
    hkThreadMemory* tm = hkThreadMemoryInstance();
    tm->m_current = data;
    if (data == tm->m_preallocStart)
        tm->releaseBlock(data);
    if (caps >= 0)
        tm->deallocateChunk(data, (caps & HK_ARRAY_FLAG_MASK) * elemSize, 0x14);
}

// Inline (stack-resident) arrays keep caps with the sign bit set, so their free is a no-op.
static inline void hkStackInlineFree(void* data, int caps, int elemSize)
{
    if (caps >= 0) {
        hkThreadMemory* tm = hkThreadMemoryInstance();
        tm->deallocateChunk(data, (caps & HK_ARRAY_FLAG_MASK) * elemSize, 0x14);
    }
}

// ------------------------------------------------------------------ telemetry (hkMonitorStream)
struct hkTimerEntry3 { const char* name; u32 time; u32 pad; };                       // 12 bytes
struct hkTimerEntry4 { const char* name; u32 time; u32 pad; const char* name2; };    // 16 bytes
static inline u32 hkRdtsc() { u32 t; __asm { rdtsc } __asm { mov t, eax } return t; }
static inline bool hkTimerHasRoom()
{
    return (u32)TlsGetValue(g_hkMonitorStreamCurrentTls) < (u32)TlsGetValue(g_hkMonitorStreamEndTls);
}
static inline void hkTimerSplit(const char* name)
{
    if (hkTimerHasRoom()) {
        hkTimerEntry3* p = (hkTimerEntry3*)TlsGetValue(g_hkMonitorStreamCurrentTls);
        p->name = name;
        p->time = hkRdtsc();
        TlsSetValue(g_hkMonitorStreamCurrentTls, p + 1);
    }
}
static inline void hkTimerBeginList(const char* name, const char* name2)
{
    if (hkTimerHasRoom()) {
        hkTimerEntry4* p = (hkTimerEntry4*)TlsGetValue(g_hkMonitorStreamCurrentTls);
        p->name = name;
        p->name2 = name2;
        p->time = hkRdtsc();
        TlsSetValue(g_hkMonitorStreamCurrentTls, p + 1);
    }
}

// ------------------------------------------------------------------ hkArray
template<class T> class hkArray {
public:
    T*  m_data;                 // +0x00
    int m_size;                 // +0x04
    int m_capacityAndFlags;     // +0x08
    T& operator[](int i) { return m_data[i]; }
    void pushBack(const T& t)
    {
        if (m_size == (m_capacityAndFlags & HK_ARRAY_FLAG_MASK))
            hkArrayUtil::_reserveMore(this, sizeof(T));
        m_data[m_size++] = t;
    }
    int indexOf(const T& t) const
    {
        int i = 0;
        while (i < m_size) {
            if (m_data[i] == t)
                return i;
            ++i;
        }
        return -1;
    }
};

// ------------------------------------------------------------------ objects
// The first vtable slot is the scalar deleting destructor, so `obj->slot0(1)` reproduces the
// original's `(**(code**)*obj)(1)` call.
class hkReferencedObject {
public:
    virtual void slot0(int flags);          // +0x00  scalar deleting destructor
    virtual void slot1();                   // +0x04  calcStatistics
    u16 m_memSizeAndFlags;                  // +0x04 (after the vptr)
    u16 m_referenceCount;                   // +0x06
    void addReference();                    // 0x01082590
    void removeReference();                 // 0x0109ae60
};

class hkShape : public hkReferencedObject {
public:
    virtual unsigned slot2();                                        // +0x08  shape type (getType)
    virtual void     slot3(void* motion, float tolerance, void* aabbOut);   // +0x0c  getAabb
};

class hkBroadPhase {
public:
    virtual void  s0(); virtual void s1(); virtual void s2();
    virtual void  addBatch(void* handles, void* swept, void* pairs);   // +0x0c (slot 3)
    virtual void  s4();
    virtual void  removeBatch(void* handles, void* pairs);             // +0x14 (slot 5)
    virtual void  s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10();
    virtual void  query(void* aabb, void* outArray);                   // +0x2c (slot 11)
};

class hkTypedBroadPhaseHandle { public:
    u32 m_id;                    // +0x00
    u8  m_type;                  // +0x04
    i8  m_ownerOffset;           // +0x05
    u16 m_objectQualityType;     // +0x06
    u32 m_collisionFilterInfo;   // +0x08
};                               // 0xc

class hkTypedBroadPhaseHandlePair { public:
    hkTypedBroadPhaseHandle* m_a;    // +0x00
    hkTypedBroadPhaseHandle* m_b;    // +0x04
};                                   // 0x8

class hkCollidable { public:              // no vtable
    hkShape* m_shape;                     // +0x00
    u32      m_shapeKey;                  // +0x04
    void*    m_motion;                    // +0x08
};

class hkLinkedCollidable : public hkCollidable {
public:
    void* m_parent;                                  // +0x0c
    int   m_ownerOffset;                             // +0x10
    hkTypedBroadPhaseHandle m_broadPhaseHandle;      // +0x14
    float m_allowedPenetrationDepth;                 // +0x20
    hkArray<void*> m_collisionEntries;               // +0x24
};                                                   // 0x30

class hkWorldObject : public hkReferencedObject {
public:
    virtual void  slot1();                             // +0x04 (calcStatistics override)
    virtual void  slot2() {}                           // +0x08
    virtual void* getMotionState() = 0;                // +0x0c (slot 3)
    virtual void  slot4() {}                           // +0x10 (slot 4)
    void*  m_world;                                    // +0x08
    void*  m_userData;                                 // +0x0c
    const char* m_name;                                // +0x10
    u32    m_multithreadLock[2];                       // +0x14
    hkLinkedCollidable m_collidable;                   // +0x1c
    hkArray<char> m_properties;                        // +0x4c
};                                                     // 0x58

class hkMotion { public: char pad[0x10]; };            // only ever used by pointer

class hkSimulationIsland {
public:
    char  pad00[0x1c];              // +0x00
    hkWorld* m_world;               // +0x1c
    u16   m_storageIndex;           // +0x20
    u16   m_dirtyListIndex;         // +0x22
    void addAction(hkAction* a);    // 0x010a24b0
    void removeAction(hkAction* a); // 0x010a20b0
};

class hkEntity : public hkWorldObject {
public:
    hkMotion* m_motion;                            // +0x58
    hkSimulationIsland* m_simulationIsland;        // +0x5c
    char pad60[0x60];                              // +0x60..0xbf
    hkArray<hkAction*> m_actions;                  // +0xc0
    u32 m_uid;                                     // +0xcc
};

class hkPhantom : public hkWorldObject {
public:
    void firePhantomAdded();                       // 0x0108e370
    void firePhantomRemoved();                     // 0x0108e300
    virtual void slot5(void* sweptTransform) = 0;  // +0x14
    virtual void slot6() = 0;                      // +0x18
    virtual void slot7() = 0;                      // +0x1c
    virtual void slot8() = 0;                      // +0x20
    virtual void slot9() = 0;                      // +0x24
    virtual void slot10() = 0;                     // +0x28
    virtual void slot11() = 0;                     // +0x2c
};

class hkAction : public hkReferencedObject {
public:
    virtual void slot2();                            // +0x08
    virtual void getReferencedEntities(void* out);   // +0x0c (slot 3)
    virtual void slot4();                            // +0x10
    hkWorld* m_world;                                // +0x08
    hkSimulationIsland* m_island;                    // +0x0c
    void* m_userData;                                // +0x10
    const char* m_name;                              // +0x14
};

struct hkCollisionInput { char pad0[8]; float m_tolerance; };            // tolerance at +0x08
struct hkProcessCollisionInput { char pad0[8]; float m_tolerance; };     // +0x08

class hkCollidableCollidableFilter { };     // opaque, reached at hkCollisionFilter+8

class hkCdBodyPairFilterIface {
public:
    virtual char* slot0();                                                  // +0x00
    virtual char* isCollisionEnabled(char* out, const void* a, const void* b);   // +0x04
};

class hkCollisionFilter {
public:
    char pad0[8];                          // +0x00
    hkCdBodyPairFilterIface m_iface;       // +0x08
};

// Shape-pair dispatch table of an hkCdBodyPairCollector; the byte table and the handler pointers
// live in the collector's class data block, which is reached through its vtable pointer.
class hkCdBodyPairCollector {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    u8 m_hasHit;                           // +0x04  (the collector raises this to stop the query)
};

class hkSimulation {
public:
    virtual void s0(); virtual void s1();
    void removeEntitiesImmediately(hkEntity* const* entities, int numEntities);   // 0x010f0bb0
};

// A pending world operation.  The queue stores 20-byte elements (hkWorldOperationQueue::
// queueOperation memcpy's 0x14 bytes from the record), and only the first 12 are set by these
// entry points; the tail is left as whatever the frame held.  The original also stores `m_arg`
// with a 16-bit store, leaving the field's upper half untouched - hkOpSetArg reproduces that
// observable byte-level behaviour.
struct hkWorldOperationBase { u8 m_type; void* m_object; int m_arg; char m_reserved[8]; };

static inline void hkOpSetArg(hkWorldOperationBase& op, int value)
{
    // volatile keeps the store at 16 bits: cl would otherwise widen it and clobber the frame's
    // leftover bytes in the field's upper half.
    *(volatile u16*)&op.m_arg = (u16)value;
}

struct hkWorldOperationQueue {
    void queueOperation(const hkWorldOperationBase& op);   // 0x0109afe0
};

struct hkTypedBroadPhaseDispatcher {
    void addPairs(hkTypedBroadPhaseHandlePair* pairs, int numPairs,
                  const hkCollidableCollidableFilter* filter) const;      // 0x010cc410
    void removePairs(hkTypedBroadPhaseHandlePair* pairs, int numPairs) const;   // 0x010cc480
};

// ------------------------------------------------------------------ external callees
struct hkWorldCallbackUtil {
    static void fireEntityRemoved(hkWorld*, hkEntity*);    // 0x0109ec50
    static void fireActionAdded(hkWorld*, hkAction*);      // 0x0109eaa0
    static void fireActionRemoved(hkWorld*, hkAction*);    // 0x0109eb30
    static void firePhantomAdded(hkWorld*, hkPhantom*);    // 0x0109ed70
    static void firePhantomRemoved(hkWorld*, hkPhantom*);  // 0x0109ee00
};
struct hkEntityCallbackUtil {
    static void fireEntityRemoved(hkEntity*);              // 0x0109ea00
};
struct hkWorldOperationUtil {
    static void removeEntitySI(hkWorld*, hkEntity*);       // 0x010a03c0
};
// Moves the actions shared between two entities on different islands (declared here, resolved by
// the address embedded in the name).
void FUN_010a1170(hkWorld*, hkEntity*, hkEntity*);         // 0x010a1170

// ------------------------------------------------------------------ hkWorld
class hkWorld : public hkReferencedObject {
public:
    hkSimulation* m_simulation;                     // +0x08
    u32 pad0c[9];                                    // +0x0c..0x2f
    void* m_fixedIsland;                             // +0x30
    void* m_fixedRigidBody;                          // +0x34
    hkArray<hkSimulationIsland*> m_activeSimulationIslands;   // +0x38
    u32 pad44[3];                                    // +0x44..0x4f
    hkArray<hkSimulationIsland*> m_dirtySimIslands;  // +0x50
    void* m_maintenanceMgr;                          // +0x5c
    void* m_memoryWatchDog;                          // +0x60
    hkBroadPhase* m_broadPhase;                      // +0x64
    hkTypedBroadPhaseDispatcher* m_broadPhaseDispatcher;   // +0x68
    u32 pad6c[3];                                    // +0x6c..0x77
    hkProcessCollisionInput* m_collisionInput;       // +0x78
    hkCollisionFilter* m_collisionFilter;            // +0x7c
    void* m_collisionDispatcher;                     // +0x80
    hkWorldOperationQueue* m_pendingOperations;      // +0x84
    int m_pendingOperationsCount;                    // +0x88
    int m_lockCount;                                 // +0x8c
    int m_lockCountForPhantoms;                      // +0x90
    u8  m_blockExecutingPendingOperations;           // +0x94
    u8  m_criticalOperationsAllowed;                 // +0x95
    u16 pad96[23];                                   // +0x96..0xc3
    int m_simulationType;                            // +0xc4
    u32 m_lastEntityUid;                             // +0xc8
    hkArray<hkPhantom*> m_phantoms;                  // +0xcc
    u32 padd8[132];                                  // +0xd8..0x2e3
    int m_broadPhaseQuerySize;                       // +0x2e4

    void removeEntityBatch(hkEntity* const* entities, int numEntities);   // 0x01085a80
    hkAction* addActionImmediately(hkAction* action);                     // 0x01085e60 (FUN_)
    void removeActionImmediately(hkAction* action);                       // 0x01086030
    void addPhantomBatch(hkPhantom* const* phantoms, int numPhantoms);    // 0x010861c0
    void removePhantomBatch(hkPhantom* const* phantoms, int numPhantoms); // 0x01086500 (FUN_)
    void getPenetrations(const hkCollidable* collidable, const hkCollisionInput& input,
                         hkCdBodyPairCollector& collector);               // 0x010867a0
    void executePendingOperations();                                      // 0x01082bf0
};

// ===========================================================================
// @ 0x01085a80  hkWorld::removeEntityBatch
// ===========================================================================
void hkWorld::removeEntityBatch(hkEntity* const* entities, int numEntities)
{
    if (numEntities < 1)
        return;

    if (m_lockCount != 0) {
        hkWorldOperationBase op;
        op.m_type = 7;
        op.m_object = (void*)entities;
        hkOpSetArg(op, numEntities);   // the original stores only the low 16 bits of the count
        m_pendingOperations->queueOperation(op);
        return;
    }

    m_lockCount = 1;
    hkTimerBeginList("LtRemEntities", "Init+CallBck");

    // Collect the broadphase handle of every entity that has a shape.
    hkStackArray a1;
    a1.m_data = 0;
    a1.m_size = 0;
    a1.m_caps = HK_ARRAY_DONT_DEALLOCATE;
    a1.reserve(numEntities * 4);
    a1.m_caps = numEntities | HK_ARRAY_DONT_DEALLOCATE;

    hkEntity* const* end = entities + numEntities;
    for (hkEntity* const* it = entities; it != end; ++it) {
        hkEntity* e = *it;
        if (e->m_collidable.m_shape != 0) {
            ((void**)a1.m_data)[a1.m_size] = &e->m_collidable.m_broadPhaseHandle;
            a1.m_size = a1.m_size + 1;
        }
    }

    hkTimerSplit("StBroadPhase");

    hkStackArray a2;
    int querySize = m_broadPhaseQuerySize;
    a2.m_data = 0;
    a2.m_size = 0;
    a2.m_caps = HK_ARRAY_DONT_DEALLOCATE;
    a2.reserve(querySize * 8);
    a2.m_caps = querySize | HK_ARRAY_DONT_DEALLOCATE;

    m_broadPhase->removeBatch(&a1, &a2);

    hkTimerSplit("StDelAgents");
    m_broadPhaseDispatcher->removePairs((hkTypedBroadPhaseHandlePair*)a2.m_data, a2.m_size);
    hkStackFree(a2.m_data, a2.m_caps, 8);

    if (m_simulationType > 3)
        m_simulation->removeEntitiesImmediately(entities, numEntities);

    hkTimerSplit("StRemoveCb");
    for (hkEntity* const* it = entities; it != end; ++it) {
        hkEntity* e = *it;
        hkWorldCallbackUtil::fireEntityRemoved(this, e);
        hkEntityCallbackUtil::fireEntityRemoved(e);
        hkWorldOperationUtil::removeEntitySI(this, e);
        if (e->m_memSizeAndFlags == 0)
            e->slot4();
        e->removeReference();
    }
    hkTimerSplit("lt");

    m_lockCount = m_lockCount - 1;
    if (m_lockCount == 0 && m_pendingOperationsCount != 0 && m_blockExecutingPendingOperations == 0)
        executePendingOperations();
    hkStackFree(a1.m_data, a1.m_caps, 4);
}

// ===========================================================================
// @ 0x01085e60  hkWorld::addActionImmediately (unnamed in the symbol DB)
// ===========================================================================
hkAction* hkWorld::addActionImmediately(hkAction* action)
{
    if (m_lockCount != 0) {
        hkWorldOperationBase op;
        // The frame slot that holds the record is the one the original saved `this` in, so the
        // three padding bytes of the record are the low bytes of the world pointer.
        *(u32*)&op.m_type = (u32)this;
        op.m_type = 0xa;
        op.m_object = action;
        m_pendingOperations->queueOperation(op);
        return 0;
    }

    if (action->m_memSizeAndFlags != 0)
        action->m_referenceCount = (u16)(action->m_referenceCount + 1);
    m_lockCount = m_lockCount + 1;

    // The action's referenced entities arrive in a 4-element inline array on the stack.
    void* buffer[4];
    hkStackArray arr;
    arr.m_data = (void*)buffer;
    arr.m_size = 0;
    arr.m_caps = HK_ARRAY_DONT_DEALLOCATE | 4;
    action->getReferencedEntities(&arr);
    action->m_world = this;

    hkEntity* sharedIslandEntity = 0;   // first entity moved onto an island
    for (int i = 0; i < arr.m_size; ++i) {
        hkEntity* entity = (hkEntity*)((void**)arr.m_data)[i];
        hkSimulationIsland* island = entity->m_simulationIsland;

        int slot = -1;
        for (int j = 0; j < entity->m_actions.m_size; ++j) {
            if (entity->m_actions.m_data[j] == 0) {
                slot = j;
                break;
            }
        }
        if (slot >= 0) {
            entity->m_actions.m_data[slot] = action;
        } else {
            if (entity->m_actions.m_size == (entity->m_actions.m_capacityAndFlags & HK_ARRAY_FLAG_MASK))
                hkArrayUtil::_reserveMore(&entity->m_actions, 4);
            entity->m_actions.m_data[entity->m_actions.m_size] = action;
            entity->m_actions.m_size = entity->m_actions.m_size + 1;
        }

        if (island->m_storageIndex != 0xffff) {
            if (sharedIslandEntity == 0) {
                sharedIslandEntity = entity;
                island->addAction(action);
            } else if (sharedIslandEntity->m_simulationIsland != entity->m_simulationIsland) {
                FUN_010a1170(this, sharedIslandEntity, entity);
            }
        }
    }
    if (sharedIslandEntity == 0) {
        // No entity took the island path: fall back to the first referenced entity's island.
        hkEntity* first = (hkEntity*)((void**)arr.m_data)[0];
        first->m_simulationIsland->addAction(action);
    }

    m_lockCount = m_lockCount - 1;
    if (m_lockCount == 0 && m_pendingOperationsCount != 0 && m_blockExecutingPendingOperations == 0)
        executePendingOperations();
    hkWorldCallbackUtil::fireActionAdded(this, action);
    hkStackInlineFree(arr.m_data, arr.m_caps, 4);
    return action;
}

// ===========================================================================
// @ 0x01086030  hkWorld::removeActionImmediately
// ===========================================================================
void hkWorld::removeActionImmediately(hkAction* action)
{
    if (action->m_memSizeAndFlags != 0)
        action->m_referenceCount = (u16)(action->m_referenceCount + 1);
    m_lockCount = m_lockCount + 1;
    hkWorldCallbackUtil::fireActionRemoved(this, action);

    void* buffer[4];
    hkStackArray arr;
    arr.m_data = (void*)buffer;
    arr.m_size = 0;
    arr.m_caps = HK_ARRAY_DONT_DEALLOCATE | 4;
    action->getReferencedEntities(&arr);

    for (int i = 0; i < arr.m_size; ++i) {
        hkEntity* entity = (hkEntity*)((void**)arr.m_data)[i];
        int slot = 0;
        while (slot < entity->m_actions.m_size) {
            if (entity->m_actions.m_data[slot] == action)
                goto found;
            ++slot;
        }
        slot = -1;
    found:
        entity->m_actions.m_data[slot] = 0;   // -1 when absent: the original writes data[-1]
    }

    hkSimulationIsland* island = action->m_island;
    island->removeAction(action);
    action->m_world = 0;

    if (action->m_memSizeAndFlags != 0) {
        action->m_referenceCount = (u16)(action->m_referenceCount - 1);
        if (action->m_referenceCount == 0)
            action->slot0(1);
    }

    // Queue the island for the next cleanup pass if it is not already on the dirty list.
    hkWorld* w = island->m_world;
    if (island->m_dirtyListIndex == 0xffff) {
        island->m_dirtyListIndex = (u16)w->m_dirtySimIslands.m_size;
        hkArray<hkSimulationIsland*>* list = &w->m_dirtySimIslands;
        if (list->m_size == (list->m_capacityAndFlags & HK_ARRAY_FLAG_MASK))
            hkArrayUtil::_reserveMore(list, 4);
        list->m_data[list->m_size] = island;
        list->m_size = list->m_size + 1;
    }

    // Stack-resident array: caps carries HK_ARRAY_DONT_DEALLOCATE, so this is a no-op in practice.
    if ((arr.m_caps & HK_ARRAY_DONT_DEALLOCATE) == 0)
        hkThreadMemoryInstance()->deallocateChunk(arr.m_data, (arr.m_caps & HK_ARRAY_FLAG_MASK) * 4, 0x14);

    m_lockCount = m_lockCount - 1;
    if (m_lockCount == 0 && m_pendingOperationsCount != 0 && m_blockExecutingPendingOperations == 0)
        executePendingOperations();

    if (action->m_memSizeAndFlags != 0) {
        action->m_referenceCount = (u16)(action->m_referenceCount - 1);
        if (action->m_referenceCount == 0)
            action->slot0(1);
    }
}

// ===========================================================================
// @ 0x010861c0  hkWorld::addPhantomBatch
// ===========================================================================
void hkWorld::addPhantomBatch(hkPhantom* const* phantoms, int numPhantoms)
{
    if (m_lockCountForPhantoms + m_lockCount != 0) {
        hkWorldOperationBase op;
        op.m_type = 0xf;
        op.m_object = (void*)phantoms;
        hkOpSetArg(op, numPhantoms);
        m_pendingOperations->queueOperation(op);
        return;
    }

    m_lockCount = m_lockCount + 1;

    // a1: broadphase handles, a2: swept transforms (0x20 bytes each).
    hkStackArray a1;
    a1.m_data = 0;
    a1.m_size = 0;
    a1.m_caps = HK_ARRAY_DONT_DEALLOCATE;
    a1.reserve(numPhantoms * 4);
    a1.m_caps = numPhantoms | HK_ARRAY_DONT_DEALLOCATE;

    hkStackArray a2;
    a2.m_data = 0;
    a2.m_size = 0;
    a2.m_caps = HK_ARRAY_DONT_DEALLOCATE;
    a2.reserve(numPhantoms * 0x20);
    a2.m_caps = numPhantoms | HK_ARRAY_DONT_DEALLOCATE;

    for (int i = 0; i < numPhantoms; ++i) {
        hkPhantom* p = phantoms[i];
        if (p->m_collidable.m_motion == 0)
            p->m_collidable.m_motion = p->getMotionState();
        p->m_world = this;
        ((void**)a1.m_data)[i] = &p->m_collidable.m_broadPhaseHandle;
        p->slot5((char*)a2.m_data + i * 0x20);
        p->addReference();
        m_phantoms.pushBack(p);
        hkWorldCallbackUtil::firePhantomAdded(this, p);
        p->firePhantomAdded();
    }
    a2.m_size = numPhantoms;
    a1.m_size = numPhantoms;

    hkStackArray a3;
    int querySize = m_broadPhaseQuerySize;
    a3.m_data = 0;
    a3.m_size = 0;
    a3.m_caps = HK_ARRAY_DONT_DEALLOCATE;
    a3.reserve(querySize * 8);
    a3.m_caps = querySize | HK_ARRAY_DONT_DEALLOCATE;

    m_broadPhase->addBatch(&a1, &a2, &a3);

    const hkCollidableCollidableFilter* filter =
        m_collisionFilter ? (const hkCollidableCollidableFilter*)((char*)m_collisionFilter + 8) : 0;
    m_broadPhaseDispatcher->addPairs((hkTypedBroadPhaseHandlePair*)a3.m_data, a3.m_size, filter);

    m_lockCount = m_lockCount - 1;
    if (m_lockCount == 0 && m_pendingOperationsCount != 0 && m_blockExecutingPendingOperations == 0)
        executePendingOperations();

    hkStackFree(a3.m_data, a3.m_caps, 8);
    hkStackFree(a2.m_data, a2.m_caps, 0x20);
    hkStackFree(a1.m_data, a1.m_caps, 4);
}

// ===========================================================================
// @ 0x01086500  hkWorld::removePhantomBatch (unnamed in the symbol DB)
// ===========================================================================
void hkWorld::removePhantomBatch(hkPhantom* const* phantoms, int numPhantoms)
{
    if (m_lockCountForPhantoms + m_lockCount != 0) {
        hkWorldOperationBase op;
        op.m_type = 0x10;
        op.m_object = (void*)phantoms;
        hkOpSetArg(op, numPhantoms);
        m_pendingOperations->queueOperation(op);
        return;
    }

    m_lockCount = m_lockCount + 1;

    hkStackArray a1;
    a1.m_data = 0;
    a1.m_size = 0;
    a1.m_caps = HK_ARRAY_DONT_DEALLOCATE;
    a1.reserve(numPhantoms * 4);
    a1.m_caps = numPhantoms | HK_ARRAY_DONT_DEALLOCATE;

    for (int i = 0; i < numPhantoms; ++i) {
        hkPhantom* p = phantoms[i];
        ((void**)a1.m_data)[i] = &p->m_collidable.m_broadPhaseHandle;
        hkWorldCallbackUtil::firePhantomRemoved(this, p);
        p->firePhantomRemoved();
    }
    a1.m_size = numPhantoms;

    hkStackArray a2;
    int querySize = m_broadPhaseQuerySize;
    a2.m_data = 0;
    a2.m_size = 0;
    a2.m_caps = HK_ARRAY_DONT_DEALLOCATE;
    a2.reserve(querySize * 8);
    a2.m_caps = querySize | HK_ARRAY_DONT_DEALLOCATE;

    m_broadPhase->removeBatch(&a1, &a2);
    m_broadPhaseDispatcher->removePairs((hkTypedBroadPhaseHandlePair*)a2.m_data, a2.m_size);
    hkStackFree(a2.m_data, a2.m_caps, 8);

    // Unlink every phantom from the world and from m_phantoms (swap-remove).
    for (int i = 0; i < numPhantoms; ++i) {
        hkPhantom* p = phantoms[i];
        p->m_world = 0;
        int idx = m_phantoms.indexOf(p);
        int last = m_phantoms.m_size - 1;
        m_phantoms.m_size = last;
        m_phantoms.m_data[idx] = m_phantoms.m_data[last];
        if (p->m_memSizeAndFlags == 0)
            p->slot11();
        p->removeReference();
    }

    m_lockCount = m_lockCount - 1;
    if (m_lockCount == 0 && m_pendingOperationsCount != 0 && m_blockExecutingPendingOperations == 0)
        executePendingOperations();
    hkStackFree(a1.m_data, a1.m_caps, 4);
}

// ===========================================================================
// @ 0x010867a0  hkWorld::getPenetrations
// ===========================================================================
void hkWorld::getPenetrations(const hkCollidable* collidable, const hkCollisionInput& input,
                              hkCdBodyPairCollector& collector)
{
    hkTimerBeginList("LthkWorld::getPenetrations", "broadphase");

    // Query the broadphase for the collidable's fattened AABB, then narrowphase each candidate.
    float tolerance = input.m_tolerance - m_collisionInput->m_tolerance * 0.5f;
    hkVector4 aabb[2];
    collidable->m_shape->slot3(collidable->m_motion, tolerance, &aabb);

    void* pairBuffer[0x80];
    hkStackArray pairs;
    pairs.m_data = (void*)pairBuffer;
    pairs.m_size = 0;
    pairs.m_caps = HK_ARRAY_DONT_DEALLOCATE | 0x80;
    m_broadPhase->query(&aabb, &pairs);

    unsigned cShapeType = collidable->m_shape->slot2();
    hkTimerSplit("Stnarrowphase");

    for (int i = pairs.m_size - 1; i >= 0; --i) {
        hkTypedBroadPhaseHandle* handle = ((hkTypedBroadPhaseHandle**)pairs.m_data)[i * 2 + 1];
        hkCollidable* other = (hkCollidable*)((char*)handle + handle->m_ownerOffset);
        if (other == (hkCollidable*)collidable)
            continue;

        char hit = 0;
        char* hitFlag = m_collisionFilter->m_iface.isCollisionEnabled(&hit, (const void*)collidable,
                                                                       (const void*)other);
        if (*hitFlag == 0)
            continue;
        if (other->m_shape == 0)
            continue;

        unsigned otherShapeType = other->m_shape->slot2();
        // The collector's class data block holds, at +0x190, a [cShapeType][otherShapeType] table of
        // dispatch codes; code N selects the handler at vtable+0x994 + N*0x14.
        void** collectorVtbl = *(void***)&collector;
        u8 code = ((u8*)collectorVtbl)[0x190 + cShapeType * 0x20 + otherShapeType];
        typedef void (*HkPairDispatch)(const hkCollidable*, hkCollidable*, const hkCollisionInput&,
                                       hkCdBodyPairCollector&);
        HkPairDispatch dispatch =
            (HkPairDispatch)(*(void**)((char*)collectorVtbl + 0x994 + code * 0x14));
        dispatch(collidable, other, input, collector);
        if (collector.m_hasHit != 0)
            break;
    }
    hkTimerSplit("lt");

    hkStackInlineFree(pairs.m_data, pairs.m_caps, 8);
}