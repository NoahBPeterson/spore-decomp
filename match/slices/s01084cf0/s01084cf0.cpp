// Slice s01084cf0 -- Havok 3.1 hkWorld collision-filter maintenance + batch entity add.
// Module flags: /vc71 (Havok dependency, cl 13.10).
//
// Three out-of-line hkWorld entry points lifted from Physics/Dynamics/World/hkWorld.cpp:
//   0x01084cf0  hkWorld::updateCollisionFilterOnPhantom(hkPhantom*, hkUpdateCollectionFilterMode)
//   0x01084fa0  (static) updateCollisionFilterOnEntity(hkWorld*, hkEntity*, ...)
//   0x01085490  hkWorld::addEntityBatch(hkEntity const* const*, int, hkEntityActivation)
//
// All three are macro-heavy Havok internals: the hkMonitorStream HK_TIMER_BEGIN/END
// telemetry (a TLS buffer written with rdtsc timestamps), hkThreadMemory stack
// allocations for the scratch hkArray's, hkArrayUtil::_reserve growth, the
// +0x7c collision-filter / +0x64 broadphase calls and the world's +0x8c operation
// lock with the +0x88 pending-count / +0x94 unwind guard.
//
// The source below reproduces the control flow, the array/telemetry traffic and the
// error-report structure faithfully.  The timer and thread-memory macros are modelled
// as inline helpers, so the result is behaviourally equivalent rather than byte-exact.
// Layouts: work/claude/wt/src/game/include/hkWorld.h, hkEntity.h, hkPhantom.h,
// hkWorldObject.h and match/include/havok31/hkReflectedClasses.h.
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef signed char    s8;
typedef unsigned long  u32d;    // DWORD (TLS index)

// ---- imports / globals -----------------------------------------------------
extern "C" void* __stdcall TlsGetValue(u32d index);
extern "C" int   __stdcall TlsSetValue(u32d index, void* value);
extern unsigned int g_hkMonitorStreamEndTls;      // 0x016e42a8
extern unsigned int g_hkMonitorStreamCurrentTls;  // 0x016e42a4
extern unsigned int g_hkThreadMemoryTls;          // 0x016e4174
unsigned long long __cdecl rdtsc(void);

// ---- hkMonitorStream HK_TIMER_BEGIN / HK_TIMER_END --------------------------
// "Lt..." records are 4 dwords {name, timestamp, unused, section} advancing by 0x10;
// "St..." (and the frame-boundary) records are 3 dwords {name, timestamp, unused}
// advancing by 0xc.
static inline void hkTimerBegin(const char* name, const char* section) {
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    void* cur = TlsGetValue(g_hkMonitorStreamCurrentTls);
    if (cur < end) {
        u32* p = (u32*)TlsGetValue(g_hkMonitorStreamCurrentTls);
        p[0] = (u32)name;
        p[3] = (u32)section;
        p[1] = (u32)rdtsc();
        TlsSetValue(g_hkMonitorStreamCurrentTls, p + 4);
    }
}
static inline void hkTimerEnd(const char* name) {
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    void* cur = TlsGetValue(g_hkMonitorStreamCurrentTls);
    if (cur < end) {
        u32* p = (u32*)TlsGetValue(g_hkMonitorStreamCurrentTls);
        p[0] = (u32)name;
        p[1] = (u32)rdtsc();
        TlsSetValue(g_hkMonitorStreamCurrentTls, p + 3);
    }
}

// ---- hkThreadMemory (thread-local stack allocator) --------------------------
// The per-thread instance lives in a TLS slot; [tid+0x20] is the stack cursor,
// [tid+0x24] the mark, [tid+0x28] the base and [tid+0x2c] the stack limit.  Scratch
// arrays that fit are carved off the stack; otherwise allocateChunk (vtable +0xc)
// is used, and freeStackAlloc (vtable +0x10) releases an entire stack frame.
class hkThreadMemory {
public:
    virtual ~hkThreadMemory();              // +0x00
    virtual void _v1();                     // +0x04
    virtual void _v2();                     // +0x08
    virtual void* allocateChunk(u32 size);  // +0x0c
    virtual void  freeStackAlloc(void* p);  // +0x10

    void deallocateChunk(void* p, u32 size, int align);   // 0x0107db10

    u8*   m_stackCurrent;   // 0x20
    u8*   m_stackMark;      // 0x24
    u8*   m_stackBase;      // 0x28
    u8*   m_stackLimit;     // 0x2c
};
static hkThreadMemory* hkThreadMemoryInstance() {
    return (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
}
static void* hkStackAlloc(u32 bytes) {
    hkThreadMemory* mem = hkThreadMemoryInstance();
    u32 need = (bytes + 0x10) & 0xfffffff0u;
    u8* cur = mem->m_stackCurrent;
    u8* end = cur + need;
    if ((u32)mem->m_stackLimit < (u32)end)
        return mem->allocateChunk(need);
    mem->m_stackCurrent = end;
    return cur;
}
static void hkStackRelease(void* p) {
    hkThreadMemory* mem = hkThreadMemoryInstance();
    mem->m_stackCurrent = (u8*)p;
    if (p == mem->m_stackMark)
        mem->freeStackAlloc(p);
}
// hkArray<T> heap block release: a set high capacity bit means "stack owned".
static void hkArrayFree(void* data, int caps, int elemSize) {
    if ((caps & 0x80000000) == 0)
        hkThreadMemoryInstance()->deallocateChunk(
            data, (u32)(caps & 0x3fffffff) * (u32)elemSize, 0x14);
}

// ---- forward declarations --------------------------------------------------
class hkWorld; class hkEntity; class hkPhantom; class hkSimulationIsland;
class hkProcessCollisionInput; class hkBroadPhase; class hkCollisionFilter;

// ---- callees ---------------------------------------------------------------
class hkWorldOperationQueue {
public:
    void queueOperation(void* op);                   // 0x0109afe0
};
void hkArrayUtil_reserveExact(void* arr, int newCap, int elemSize);   // 0x0107f4a0
void hkArrayUtil_reserveGrow(void* arr, int elemSize);                // 0x0107f530
void worldUpdatePhantomOverlap(hkCollisionFilter* filter, void* agent);  // 0x01082910
void FUN_010cc410(int a, int b, int c);              // 0x010cc410
void FUN_010cc560(void* a, void* b);                 // 0x010cc560
void FUN_01082590(void);                             // 0x01082590
void FUN_01209b70(int a, int b, void* c);            // 0x01209b70
void FUN_010a2250(void* entity);                     // 0x010a2250
void FUN_010a39f0(void* entity);                     // 0x010a39f0
void FUN_010fb9c0(void* entity, void* input);        // 0x010fb9c0
void FUN_0109ebc0(void* world, void* entity);        // 0x0109ebc0
void FUN_0109e730(void* entity);                     // 0x0109e730
void* hkMemoryAllocate(u32 size, int align);         // hkMemory::allocate

// ---- hkBroadPhaseHandle / collidable / world object hierarchy --------------
class hkBroadPhaseHandle {
public:
    u32 m_id;              // 0x00
    u16 m_handleType;      // 0x04
    s8  m_ownerOffset;     // 0x05
    u8  m_pad06[2];        // 0x06
    u32 m_pad08;           // 0x08
    u32 m_pad0c;           // 0x0c
    void* owner() const { return (char*)this + m_ownerOffset; }
};
struct hkBroadPhaseHandlePair { hkBroadPhaseHandle* m_a; hkBroadPhaseHandle* m_b; };

// The collidable embedded in every hkWorldObject; its broadphase handle sits at +0x30.
struct hkCollidable {
    void*              m_shape;        // 0x00
    u32                m_shapeKey;     // 0x04
    void*              m_motion;       // 0x08
    void*              m_parent;       // 0x0c
    void*              m_owner;        // 0x10
    hkBroadPhaseHandle m_handle;       // 0x14
};

// hkReferencedObject: 2 vtable slots, then the size/flags + refcount words.
class hkReferencedObject {
public:
    virtual ~hkReferencedObject();          // slot 0
    virtual void calcStatistics(void*);     // slot 1
    u16 m_memSizeAndFlags;                  // 0x04
    u16 m_referenceCount;                   // 0x06
};
// hkWorldObject adds setShape (slot 2) and getMotionState (slot 3).
class hkWorldObject : public hkReferencedObject {
public:
    virtual ~hkWorldObject();                        // slot 0 (override)
    virtual void* setShape(void*);                   // slot 2
    virtual void* getMotionState();                  // slot 3
    void*        m_world;                            // 0x08
    void*        m_userData;                         // 0x0c
    char*        m_name;                             // 0x10
    u32          m_lockThreadId;                     // 0x14
    int          m_lockCount;                        // 0x18
    hkCollidable m_collidable;                       // 0x1c
};

// Frozen collision entry: an 8-byte element of the hkEntity's +0x40 array.  Both
// dwords are object pointers; the first carries handle base offsets at +0x14/+0x18.
struct hkCollisionEntry {
    void* m_objectA;       // 0x00
    void* m_objectB;       // 0x04
};
struct hkCollisionEntryTarget {
    u8  m_pad00[0x14];
    int m_handleA;         // 0x14
    int m_handleB;         // 0x18
};

// hkEntity adds deallocateInternalArrays (slot 4).
class hkEntity : public hkWorldObject {
public:
    virtual ~hkEntity();                             // slot 0 (override)
    virtual void deallocateInternalArrays();         // slot 4
    void** m_collisionEntriesData;                   // 0x40
    int    m_collisionEntriesSize;                   // 0x44
    int    m_collisionEntriesCaps;                   // 0x48
    u8     m_pad4c[0x58 - 0x4c];
    void*  m_motion;                                 // 0x58
    void*  m_simulationIsland;                       // 0x5c
    u8     m_pad60[0x99 - 0x60];
    u8     m_fixed;                                  // 0x99
    u8     m_pad9a[0xcc - 0x9a];
    u32    m_uid;                                    // 0xcc
};
// hkPhantom adds slots 4..11; updateShapeCollectionFilter is slot 10 (+0x28).
class hkPhantom : public hkWorldObject {
public:
    virtual ~hkPhantom();                            // slot 0 (override)
    virtual int  getType();                          // slot 4
    virtual void calcAabb(void*);                    // slot 5
    virtual void addOverlappingCollidable(void*);    // slot 6
    virtual int  isOverlappingCollidableAdded(void*);// slot 7
    virtual void removeOverlappingCollidable(void*); // slot 8
    virtual void* clone();                           // slot 9
    virtual void updateShapeCollectionFilter();      // slot 10
    virtual void deallocateInternalArrays();         // slot 11
};

// hkSimulationIsland carries an hkArray<hkEntity*> at +0x3c.
class hkSimulationIsland {
public:
    u8                 m_pad00[0x3c];
    hkEntity**         m_entities;                   // 0x3c
    int                m_entitiesSize;               // 0x40
    int                m_entitiesCaps;               // 0x44
};

// hkBroadPhase: slot 3 (+0x0c) batches new handles, slot 12 (+0x30) runs an AABB query.
class hkBroadPhase {
public:
    virtual ~hkBroadPhase();                                     // 0
    virtual void _v1();                                          // 1 (+0x04)
    virtual void _v2();                                          // 2 (+0x08)
    virtual void addEntityBatch(void*, void*, void*);            // 3 (+0x0c)
    virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7();
    virtual void _v8(); virtual void _v9(); virtual void _v10(); virtual void _v11();
    virtual void queryAabb(void*, void*);                        // 12 (+0x30)
};

// The collidable-collidable filter reached through m_collisionFilter+8.
class hkCollidableCollidableFilter {
public:
    virtual ~hkCollidableCollidableFilter();
    virtual char* isCollisionEnabled(void*, void*, void*);       // slot 1 (+0x04)
};
class hkCollisionFilter {
public:
    u32                        _pad00;
    u32                        _pad04;
    hkCollidableCollidableFilter* m_collidableCollidableFilter;  // 0x08
};
struct hkProcessCollisionInput {
    u32   _pad00;
    u32   _pad04;
    float m_tolerance;                     // 0x08
};

// ---- enums referenced by the mangled names ---------------------------------
enum hkUpdateCollectionFilterMode {
    HK_UPDATE_FILTER_ON_PHANTOM_UPDATE_OVERLAPS         = 0,
    HK_UPDATE_FILTER_ON_PHANTOM_UPDATE_SHAPE_COLLECTION = 1,
};
enum hkEntityActivation {
    HK_ENTITY_ACTIVATION_DO_ACTIVATE            = 0,
    HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE        = 1,
    HK_ENTITY_ACTIVATION_DO_NOT_ACTIVATE_OR_ADD = 2,
};

// ---- hkWorld ---------------------------------------------------------------
template <class T> struct hkArray {
    T*  m_data;              // +0x00
    int m_size;              // +0x04
    int m_capacityAndFlags;  // +0x08
};

class hkWorld {
public:
    void updateCollisionFilterOnPhantom(hkPhantom* phantom, hkUpdateCollectionFilterMode mode);
    void addEntityBatch(hkEntity const* const* entities, int count, hkEntityActivation activation);
    void executePendingOperations();                 // 0x01082bf0
    hkSimulationIsland* getSimulationIsland();       // 0x010a2810

    void* m_vtable;                                  // 0x00
    u32   m_memSizeAndFlags;                         // 0x04
    u16   m_referenceCount;                          // 0x08
    u16   m_pad0a;                                   // 0x0a
    u8    m_pad0c[0x38 - 0x0c];                      // 0x0c
    hkArray<hkSimulationIsland*> m_activeSimulationIslands;    // 0x38
    hkArray<hkSimulationIsland*> m_inactiveSimulationIslands;  // 0x44
    u8    m_pad50[0x64 - 0x50];                      // 0x50
    hkBroadPhase* m_broadPhase;                      // 0x64
    u8    m_pad68[0x78 - 0x68];                      // 0x68
    hkProcessCollisionInput* m_collisionInput;       // 0x78
    hkCollisionFilter* m_collisionFilter;            // 0x7c
    void* m_collisionDispatcher;                     // 0x80
    hkWorldOperationQueue* m_pendingOperations;      // 0x84
    int   m_pendingOperationsCount;                  // 0x88
    int   m_lockCount;                               // 0x8c
    int   m_lockCountForPhantoms;                    // 0x90
    u8    m_blockExecutingPendingOperations;         // 0x94
    u8    m_pad95[0xb4 - 0x95];                      // 0x95
    u8    m_wantSimulationIslands;                   // 0xb4
    u8    m_pad_b5[0xc8 - 0xb5];                     // 0xb5
    u32   m_lastEntityUid;                           // 0xc8
    u8    m_pad_cc[0x2e4 - 0xcc];                    // 0xcc
    int   m_broadPhaseQuerySize;                     // 0x2e4
};

// ===========================================================================
// @ 0x01084cf0  hkWorld::updateCollisionFilterOnPhantom
// ===========================================================================
void hkWorld::updateCollisionFilterOnPhantom(hkPhantom* phantom, hkUpdateCollectionFilterMode mode)
{
    if (m_lockCount != 0) {
        // Defer: queue a filter-update operation onto the pending-operation list.
        struct Op { u8 m_type; u8 m_pad[3]; hkPhantom* m_phantom; u8 m_mode; };
        Op op;
        op.m_type = 0x13;
        op.m_phantom = phantom;
        op.m_mode = (u8)mode;
        m_pendingOperations->queueOperation(&op);
        return;
    }
    m_lockCount = 1;
    hkTimerBegin("LtUpdateFilterOnPhantom", "broadphase");

    u32 n = (u32)m_broadPhaseQuerySize;
    hkArray<hkBroadPhaseHandlePair> overlaps;
    overlaps.m_size = 0;
    overlaps.m_capacityAndFlags = 0x80000000;
    overlaps.m_data = (hkBroadPhaseHandlePair*)hkStackAlloc(n * 8);
    overlaps.m_capacityAndFlags = (int)(n | 0x80000000u);

    hkBroadPhaseHandle* handle = &phantom->m_collidable.m_handle;
    m_broadPhase->queryAabb(handle, &overlaps);

    hkTimerEnd("StUpdateOverlaps");
    for (int i = 0; i < overlaps.m_size; i++) {
        if (overlaps.m_data[i].m_b != handle)
            worldUpdatePhantomOverlap(m_collisionFilter, overlaps.m_data[i].m_b->owner());
    }

    if (mode != 0) {
        hkTimerEnd("StcollectionFilter");
        phantom->updateShapeCollectionFilter();
    }

    if (--m_lockCount == 0 && m_pendingOperationsCount != 0 &&
        m_blockExecutingPendingOperations == 0)
        executePendingOperations();

    hkTimerEnd("\x01");                       // frame boundary (0x143cd94)
    hkStackRelease(overlaps.m_data);
    hkArrayFree(overlaps.m_data, overlaps.m_capacityAndFlags, 8);
}

// ===========================================================================
// @ 0x01084fa0  (static) updateCollisionFilterOnEntity
// ===========================================================================
void updateCollisionFilterOnEntity(
        hkWorld* world, hkEntity* entity, hkEntityActivation activation, u8 collectionMode)
{
    if (world->m_lockCount != 0) {
        struct Op { u8 m_type; u8 m_pad[3]; hkEntity* m_entity; u8 m_activation; u8 m_collection; };
        Op op;
        op.m_type = 0x12;
        op.m_entity = entity;
        op.m_activation = (u8)activation;
        op.m_collection = collectionMode;
        world->m_pendingOperations->queueOperation(&op);
        return;
    }
    hkTimerBegin("LtUpdateFilterOnEntity", "init");
    world->m_lockCount += 1;

    hkBroadPhaseHandlePair overlapBuf[128];           // in-frame 1 KB scratch array
    hkArray<hkBroadPhaseHandlePair> overlaps;
    overlaps.m_data = overlapBuf;
    overlaps.m_size = 0;
    overlaps.m_capacityAndFlags = 0x80000080;

    if (activation == 0) {
        hkTimerEnd("Stbroadphase");
        world->m_broadPhase->queryAabb(&entity->m_collidable.m_handle, &overlaps);
        hkTimerEnd("Stphantom");

        // Drop pairs whose owner is a phantom (broadphase type 2); the rest have their
        // frozen collision filter refreshed, splicing removed entries out of the array.
        for (int i = 0; i < overlaps.m_size; i++) {
            char* owner = (char*)overlaps.m_data[i].m_b->owner();
            if (owner[0x18] == 2) {
                int* collidable = (int*)(owner + *(int*)(owner + 0x10));
                worldUpdatePhantomOverlap(world->m_collisionFilter, owner);
                if (collectionMode != 0)
                    (*(void(**)(void))(*collidable + 0x28))();
                overlaps.m_size -= 1;
                overlaps.m_data[i] = overlaps.m_data[overlaps.m_size];
                i -= 1;
            }
        }

        // Collect this entity's own frozen-collision handles into a pair array and
        // pass it through the phantom-overlap resolver.
        hkBroadPhaseHandlePair pairBuf[128];          // in-frame 1 KB scratch array
        hkArray<hkBroadPhaseHandlePair> pairs;
        pairs.m_data = pairBuf;
        pairs.m_size = 0;
        pairs.m_capacityAndFlags = 0x80000080;
        hkCollisionEntry* entries = (hkCollisionEntry*)entity->m_collisionEntriesData;
        for (int i = 0; i < entity->m_collisionEntriesSize; i++) {
            if ((u32)pairs.m_size == ((u32)pairs.m_capacityAndFlags & 0x3fffffffu))
                hkArrayUtil_reserveGrow(&pairs.m_data, 8);
            int slot = pairs.m_size;
            pairs.m_size += 1;
            hkCollisionEntryTarget* t = (hkCollisionEntryTarget*)entries[i].m_objectA;
            pairs.m_data[slot].m_a = (hkBroadPhaseHandle*)(t->m_handleA + 0x14);
            pairs.m_data[slot].m_b = (hkBroadPhaseHandle*)(t->m_handleB + 0x14);
        }
        FUN_010cc560(&pairs, &overlaps);
        hkArrayFree(pairs.m_data, pairs.m_capacityAndFlags, 8);
    }

    hkTimerEnd("StcheckAgts");
    u32 handleType16 = (u32)*(u16*)((char*)entity + 0x36);
    hkCollisionEntry* entries = (hkCollisionEntry*)entity->m_collisionEntriesData;
    for (int i = 0; i < entity->m_collisionEntriesSize; i++) {
        char* ok = world->m_collisionFilter->m_collidableCollidableFilter->isCollisionEnabled(
                        (char*)&overlaps + 3, (char*)entity + 0x1c, entries[i].m_objectB);
        if (*ok == 0 ||
            *(char*)((u32)*(u16*)((char*)entries[i].m_objectB + 0x1a) + handleType16 * 8 + 0x19d4 +
                     *(int*)((char*)world + 0x80)) == 0) {
            FUN_010a39f0(entries[i].m_objectA);
            i -= 1;
            *(u8*)(*(int*)((char*)entity + 0x5c) + 0x26) = 1;
        } else if (collectionMode == 1) {
            FUN_010fb9c0(entries[i].m_objectA, world->m_collisionInput);
        }
    }

    if (0 < overlaps.m_size) {
        hkTimerEnd("StaddAgts");
        int filter = (world->m_collisionFilter == 0) ? 0 : (int)world->m_collisionFilter + 8;
        FUN_010cc410((int)overlaps.m_data, overlaps.m_size, filter);
    }

    if (--world->m_lockCount == 0 && world->m_pendingOperationsCount != 0 &&
        world->m_blockExecutingPendingOperations == 0)
        world->executePendingOperations();
    hkArrayFree(overlaps.m_data, overlaps.m_capacityAndFlags, 8);
    hkTimerEnd("\x01");                       // frame boundary (0x143cd94)
}

// ===========================================================================
// @ 0x01085490  hkWorld::addEntityBatch
// ===========================================================================
void hkWorld::addEntityBatch(hkEntity const* const* entities, int count, hkEntityActivation activation)
{
    if (count == 0)
        return;
    if (m_lockCount != 0) {
        // Defer: queue an AddEntityBatch operation onto the pending-operation list.
        struct Op { u8 m_type; u8 m_pad[3]; const hkEntity* const* m_entities;
                    u16 m_count; u8 m_activation; };
        Op op;
        op.m_type = 6;
        op.m_entities = entities;
        op.m_count = (u16)count;
        op.m_activation = (u8)activation;
        m_pendingOperations->queueOperation(&op);
        return;
    }
    hkTimerBegin("LtAddEntities", "init");
    m_lockCount += 1;

    // Scratch A: the broadphase handles handed to the broadphase (4 bytes each).
    hkArray<hkBroadPhaseHandle*> handles;
    handles.m_size = 0;
    handles.m_capacityAndFlags = 0x80000000;
    void* handlesMem = hkStackAlloc((u32)count * 4);
    handles.m_data = (hkBroadPhaseHandle**)handlesMem;
    handles.m_capacityAndFlags = count | 0x80000000;

    // Scratch B: the per-entity AABBs (0x20 bytes each).
    hkArray<u8> aabbs;
    aabbs.m_size = 0;
    aabbs.m_capacityAndFlags = 0x80000000;
    void* aabbsMem = hkStackAlloc((u32)count * 0x20);
    aabbs.m_data = (u8*)aabbsMem;
    aabbs.m_capacityAndFlags = count | 0x80000000;

    hkSimulationIsland* island = 0;
    int anyActive = 0;
    if (m_wantSimulationIslands == 0) {
        // Pre-size the fixed island's entity array so the new entities fit.
        hkSimulationIsland* fixed = *m_activeSimulationIslands.m_data;
        int need = fixed->m_entitiesSize + count;
        if ((fixed->m_entitiesCaps & 0x3fffffff) < need) {
            int cap = (fixed->m_entitiesCaps & 0x3fffffff) * 2;
            if (need < cap) need = cap;
            hkArrayUtil_reserveExact(&fixed->m_entities, need, 4);
        }
    } else {
        island = (hkSimulationIsland*)hkMemoryAllocate(0x74, 0x2f);
        *(u16*)((char*)island + 4) = 0x74;
        island = getSimulationIsland();
        if (activation == 1) {
            *(u16*)((char*)island + 0x20) = (u16)m_activeSimulationIslands.m_size;
            *(u8*)((char*)island + 0x26) = 1;
            *(u8*)((char*)island + 0x29) = 1;
            *(u8*)((char*)island + 0x28) = 1;
        } else {
            *(u16*)((char*)island + 0x20) = (u16)m_inactiveSimulationIslands.m_size;
            *(u8*)((char*)island + 0x26) = 1;
            *(u8*)((char*)island + 0x29) = 0;
            *(u8*)((char*)island + 0x28) = 0;
        }
    }

    float tolerance = m_collisionInput->m_tolerance;
    for (int i = 0; i < count; i++) {
        hkEntity* e = (hkEntity*)entities[i];
        u32 uid = ++m_lastEntityUid;
        e->m_uid = uid;
        FUN_01082590();
        if (e->m_collidable.m_motion == 0)
            e->m_collidable.m_motion = e->getMotionState();
        FUN_01209b70(0, 0, (char*)e->m_motion + 0x10);
        e->m_world = this;
        if (e->m_fixed == 0)
            anyActive = 1;
        FUN_010a2250(e);
        if (e->m_collidable.m_owner != 0) {
            int aabbSlot = aabbs.m_size * 0x20;
            aabbs.m_size += 1;
            (*(void(**)(void*, float, u8*))(*(int*)e->m_collidable.m_owner + 0xc))
                (e->m_collidable.m_motion, tolerance * 0.5f, aabbs.m_data + aabbSlot);
            handles.m_data[handles.m_size] = &e->m_collidable.m_handle;
            handles.m_size += 1;
        }
    }

    if (m_wantSimulationIslands != 0) {
        if (anyActive) {
            hkArray<hkSimulationIsland*>* arr =
                (activation != 1) ? &m_inactiveSimulationIslands : &m_activeSimulationIslands;
            if (arr->m_size == (arr->m_capacityAndFlags & 0x3fffffff))
                hkArrayUtil_reserveGrow(arr, 4);
            arr->m_data[arr->m_size] = island;
            arr->m_size += 1;
        } else {
            (*(void(**)(int))*(int*)island)(1);
        }
    }

    // Scratch C: the broadphase handle list the broadphase fills in.
    u32 qn = (u32)m_broadPhaseQuerySize;
    hkArray<hkBroadPhaseHandle*> outHandles;
    outHandles.m_size = 0;
    outHandles.m_capacityAndFlags = 0x80000000;
    outHandles.m_data = (hkBroadPhaseHandle**)hkStackAlloc(qn * 8);
    outHandles.m_capacityAndFlags = (int)(qn | 0x80000000u);

    hkTimerEnd("StBroadphase");
    m_broadPhase->addEntityBatch(&handles, &aabbs, &outHandles);

    hkTimerEnd("StCreateAgents");
    int filter = (m_collisionFilter == 0) ? 0 : (int)m_collisionFilter + 8;
    FUN_010cc410(handles.m_size, handles.m_capacityAndFlags, filter);

    hkTimerEnd("StAddedCb");
    for (int i = 0; i < outHandles.m_size; i++) {
        void* h = outHandles.m_data[i];
        FUN_0109ebc0(this, h);
        FUN_0109e730(h);
    }

    if (--m_lockCount == 0 && m_pendingOperationsCount != 0 &&
        m_blockExecutingPendingOperations == 0)
        executePendingOperations();

    hkTimerEnd("\x01");                       // frame boundary (0x143cd94)
    hkStackRelease(outHandles.m_data);
    hkArrayFree(outHandles.m_data, outHandles.m_capacityAndFlags, 8);
    hkStackRelease(aabbsMem);
    hkArrayFree(aabbsMem, aabbs.m_capacityAndFlags, 0x20);
    hkStackRelease(handlesMem);
    hkArrayFree(handlesMem, handles.m_capacityAndFlags, 4);
}