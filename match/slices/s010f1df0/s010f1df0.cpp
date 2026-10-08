// s010f1df0: hkContinuousSimulation::collideEntitiesBroadPhaseContinuous (0x010f1df0), Havok 3.1.0.
//
// __thiscall (ECX = this, never used), ret 0x10: (hkEntity** entities, int numEntities, hkWorld* world,
// hkCriticalSection* criticalSection).  For every entity it
//   - computes the shape AABB (inflated by half the collision tolerance plus the angular delta * radius),
//     intersects it with the bounding box of the sphere around the end-of-step centre of mass,
//     and extends it by the swept motion (centerOfMass0 - centerOfMass1),
//   - sends the AABBs to the broad phase (update), collects the new / deleted pairs,
//   - removes duplicate pairs, removes the agents of deleted pairs, and (memory permitting) adds the agents
//     of new pairs (HK_TIMER_* split names: StCalcAabbs, St3AxisSweep, StRemoveDup, StRemoveAgt, StAddAgt).
// Flags: /O2 /MD /Gy /TP /GS- /vc71 (Havok was built with VC .NET 2003).
#include "types.h"

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long index, void* value);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);

typedef float hkReal;
typedef uint32_t hkUint32;

// ---- monitor stream timers ---------------------------------------------------------------------------
extern volatile unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern volatile unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorEndListTag[];                     // 0x0143cd94

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
#define HK_TIMER_SPLIT_LIST(name) HK_TIMER_COMMAND("St" name)
#define HK_TIMER_END_LIST() HK_TIMER_COMMAND(hkMonitorEndListTag)

// ---- memory ------------------------------------------------------------------------------------------
struct hkMemory {
    void** vftable;                    // +0x00
    int m_memoryState;                 // +0x04 (1 = out of memory)
    int m_criticalMemoryLimit;         // +0x08
    int m_referenceCount;              // +0x0c
    int m_sysAllocs0;                  // +0x10
    int m_sysAllocsSize;               // +0x14
    int m_stats[4];                    // +0x18
    int m_pageMemoryUsed;              // +0x28
};
extern hkMemory* g_hkMemoryInstance;           // 0x016e4178
extern unsigned long g_hkThreadMemoryTls;      // 0x016e4174

struct hkThreadMemoryRaw {
    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    virtual void* stackAllocateSlow(int numBytes);     // +0x0c (onStackOverflow)
    virtual void stackFreeSlow(char* p);               // +0x10
    char pad[0x1c];
    char* m_stackCurrent;     // +0x20
    char* m_stackPrev;        // +0x24
    char* m_stackBase;        // +0x28
    char* m_stackEnd;         // +0x2c
    void deallocateChunk(void* p, int numBytes, int memoryClass);      // 0x0107db10
};
static __forceinline hkThreadMemoryRaw* hkThreadMemoryGet() { return (hkThreadMemoryRaw*)TlsGetValue(g_hkThreadMemoryTls); }

static __forceinline char* hkAllocateStackChars(int n)
{
    hkThreadMemoryRaw* tm = hkThreadMemoryGet();
    int size = (n + 0x10) & ~0xf;
    char* cur = tm->m_stackCurrent;
    char* next = cur + size;
    if ((uint32_t)next <= (uint32_t)tm->m_stackEnd) {
        tm->m_stackCurrent = next;
        return cur;
    }
    return (char*)tm->stackAllocateSlow(size);
}
static __forceinline void hkDeallocateStackChars(char* p)
{
    hkThreadMemoryRaw* tm = hkThreadMemoryGet();
    tm->m_stackCurrent = p;
    if (p == tm->m_stackBase)
        tm->stackFreeSlow(p);
}

// ---- math / containers --------------------------------------------------------------------------------
extern const float hkRealZero;      // 0x01485378

struct __declspec(align(16)) hkVector4 {
    hkReal x, y, z, w;
    void setMin4(const hkVector4& a, const hkVector4& b)
    {
        x = a.x < b.x ? a.x : b.x;
        y = a.y < b.y ? a.y : b.y;
        z = a.z < b.z ? a.z : b.z;
        w = a.w < b.w ? a.w : b.w;
    }
    void setMax4(const hkVector4& a, const hkVector4& b)
    {
        x = a.x > b.x ? a.x : b.x;
        y = a.y > b.y ? a.y : b.y;
        z = a.z > b.z ? a.z : b.z;
        w = a.w > b.w ? a.w : b.w;
    }
};

struct hkAabb { hkVector4 m_min; hkVector4 m_max; };            // 0x20

struct hkBroadPhaseHandle { hkUint32 m_id; };
struct hkTypedBroadPhaseHandle { hkUint32 m_id; char m_type; char m_ownerOffset; unsigned short m_objectQualityType; hkUint32 m_collisionFilterInfo; };
struct hkBroadPhaseHandlePair { hkBroadPhaseHandle* m_a; hkBroadPhaseHandle* m_b; };

// hkLocalArray<T>: hkArray + memory taken from the thread-memory stack
template <class T>
struct hkLocalArray {
    T* m_data;
    int m_size;
    int m_capacityAndFlags;
    T* m_localMemory;
    __forceinline hkLocalArray(int n)
    {
        m_data = 0;
        m_size = 0;
        m_capacityAndFlags = 0x80000000;
        m_data = (T*)hkAllocateStackChars(n * (int)sizeof(T));
        m_localMemory = m_data;
        m_capacityAndFlags = n | 0x80000000;
    }
    __forceinline ~hkLocalArray()
    {
        hkDeallocateStackChars((char*)m_localMemory);
        if ((m_capacityAndFlags & 0x80000000) == 0)
            hkThreadMemoryGet()->deallocateChunk(m_data, (m_capacityAndFlags & 0x3fffffff) * (int)sizeof(T), 0x14);
    }
};

// ---- Havok objects ----------------------------------------------------------------------------------------
struct hkSweptTransform { hkVector4 m_centerOfMass0; hkVector4 m_centerOfMass1; hkVector4 pad[3]; };   // 0x50

struct hkMotionState {                  // 0xb0
    hkReal m_transform[16];             // +0x00
    hkSweptTransform m_sweptTransform;  // +0x40
    hkVector4 m_deltaAngle;             // +0x90
    hkReal m_objectRadius;              // +0xa0
};

struct hkShape {
    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    virtual void getAabb(const hkReal* localToWorld, hkReal tolerance, hkAabb& out);   // +0x0c
};

struct hkCollidable {                    // 0x24
    hkShape* m_shape;                    // +0x00
    hkUint32 m_shapeKey;                 // +0x04
    void* m_motion;                      // +0x08 (hkMotionState*)
    void* m_parent;                      // +0x0c
    int m_ownerOffset;                   // +0x10
    hkTypedBroadPhaseHandle m_broadPhaseHandle;   // +0x14
    hkReal m_allowedPenetrationDepth;    // +0x20
};

struct hkEntity {
    char pad00[0x1c];
    hkCollidable m_collidable;           // +0x1c (hkLinkedCollidable continues past 0x40)
};

struct hkBroadPhase {
    virtual void vslot0(); virtual void vslot1(); virtual void vslot2(); virtual void vslot3();
    virtual void vslot4(); virtual void vslot5(); virtual void vslot6();
    virtual void updateAabbs(hkBroadPhaseHandle** handles, hkAabb* aabbs, int numObjects,
                             hkLocalArray<hkBroadPhaseHandlePair>& newPairs,
                             hkLocalArray<hkBroadPhaseHandlePair>& delPairs);          // +0x1c
};

struct hkCollidableCollidableFilter { char pad[1]; };
struct hkCollisionFilter { char pad[8]; hkCollidableCollidableFilter m_ccFilter; };     // MI base at +8

struct hkProcessCollisionInput {
    void* m_dispatcher;
    void* m_filter;
    hkReal m_tolerance;                  // +0x08
};

struct hkTypedBroadPhaseDispatcher {
    static void removeDuplicates(hkLocalArray<hkBroadPhaseHandlePair>& newPairs, hkLocalArray<hkBroadPhaseHandlePair>& delPairs);   // 0x010cc560 (cdecl)
    void removePairs(hkBroadPhaseHandlePair* pairs, int n) const;                                            // 0x010cc480
    void addPairs(hkBroadPhaseHandlePair* pairs, int n, const hkCollidableCollidableFilter* filter) const;   // 0x010cc410
};

struct hkCriticalSection {                // 0x20
    unsigned char m_section[0x18];
    int m_ownerLo;                        // +0x18
    int m_ownerHi;                        // +0x1c
    void enter();                         // 0x0107f820
    __forceinline void leave()
    {
        m_ownerLo = -1;
        m_ownerHi = -1;
        LeaveCriticalSection(this);
    }
};

struct hkWorld {
    char pad00[0x64];
    hkBroadPhase* m_broadPhase;                           // +0x64
    hkTypedBroadPhaseDispatcher* m_broadPhaseDispatcher;  // +0x68
    char pad6c[0x78 - 0x6c];
    hkProcessCollisionInput* m_collisionInput;            // +0x78
    hkCollisionFilter* m_collisionFilter;                 // +0x7c
    char pad80[0x2e8 - 0x80];
    int m_broadPhaseUpdateSize;                           // +0x2e8
};

class hkContinuousSimulation {
public:
    void collideEntitiesBroadPhaseContinuous(hkEntity** entities, int numEntities, hkWorld* world, hkCriticalSection* criticalSection);
};

// @ 0x010f1df0
void hkContinuousSimulation::collideEntitiesBroadPhaseContinuous(hkEntity** entities, int numEntities, hkWorld* world, hkCriticalSection* criticalSection)
{
    hkAabb* aabbs;
    hkBroadPhaseHandle** handles;
    hkReal halfTolerance;
    HK_TIMER_BEGIN_LIST("BroadPhase", "InitMem");

    hkLocalArray<hkBroadPhaseHandlePair> newPairs(world->m_broadPhaseUpdateSize);
    hkLocalArray<hkBroadPhaseHandlePair> delPairs(world->m_broadPhaseUpdateSize);
    aabbs = (hkAabb*)hkAllocateStackChars(numEntities * (int)sizeof(hkAabb));
    handles = (hkBroadPhaseHandle**)hkAllocateStackChars(numEntities * (int)sizeof(void*));

    halfTolerance = world->m_collisionInput->m_tolerance * 0.5f;

    HK_TIMER_SPLIT_LIST("CalcAabbs");
    for (int i = 0; i <= numEntities - 1; i++) {
        hkEntity* entity = entities[i];
        hkMotionState* ms = (hkMotionState*)entity->m_collidable.m_motion;
        handles[i] = (hkBroadPhaseHandle*)&entity->m_collidable.m_broadPhaseHandle;
        hkAabb& aabb = aabbs[i];
        hkReal tolerance = ms->m_deltaAngle.w * ms->m_objectRadius + halfTolerance;
        entity->m_collidable.m_shape->getAabb((const hkReal*)entity->m_collidable.m_motion, tolerance, aabb);

        const hkReal r = halfTolerance + ms->m_objectRadius;
        hkVector4 sphereMax;
        sphereMax.x = r + ms->m_sweptTransform.m_centerOfMass1.x;
        sphereMax.y = r + ms->m_sweptTransform.m_centerOfMass1.y;
        sphereMax.z = r + ms->m_sweptTransform.m_centerOfMass1.z;
        sphereMax.w = r + ms->m_sweptTransform.m_centerOfMass1.w;
        hkVector4 sphereMin;
        sphereMin.x = ms->m_sweptTransform.m_centerOfMass1.x - r;
        sphereMin.y = ms->m_sweptTransform.m_centerOfMass1.y - r;
        sphereMin.z = ms->m_sweptTransform.m_centerOfMass1.z - r;
        sphereMin.w = ms->m_sweptTransform.m_centerOfMass1.w - r;
        aabb.m_min.setMax4(aabb.m_min, sphereMin);
        aabb.m_max.setMin4(aabb.m_max, sphereMax);

        hkVector4 delta;
        delta.x = ms->m_sweptTransform.m_centerOfMass0.x - ms->m_sweptTransform.m_centerOfMass1.x;
        delta.y = ms->m_sweptTransform.m_centerOfMass0.y - ms->m_sweptTransform.m_centerOfMass1.y;
        delta.z = ms->m_sweptTransform.m_centerOfMass0.z - ms->m_sweptTransform.m_centerOfMass1.z;
        delta.w = ms->m_sweptTransform.m_centerOfMass0.w - ms->m_sweptTransform.m_centerOfMass1.w;
        hkVector4 dMin;
        dMin.x = hkRealZero < delta.x ? hkRealZero : delta.x;
        dMin.y = hkRealZero < delta.y ? hkRealZero : delta.y;
        dMin.z = hkRealZero < delta.z ? hkRealZero : delta.z;
        dMin.w = hkRealZero < delta.w ? hkRealZero : delta.w;
        hkVector4 dMax;
        dMax.x = hkRealZero > delta.x ? hkRealZero : delta.x;
        dMax.y = hkRealZero > delta.y ? hkRealZero : delta.y;
        dMax.z = hkRealZero > delta.z ? hkRealZero : delta.z;
        dMax.w = hkRealZero > delta.w ? hkRealZero : delta.w;
        aabb.m_min.x = dMin.x + aabb.m_min.x;
        aabb.m_min.y = dMin.y + aabb.m_min.y;
        aabb.m_min.z = dMin.z + aabb.m_min.z;
        aabb.m_min.w = dMin.w + aabb.m_min.w;
        aabb.m_max.x = dMax.x + aabb.m_max.x;
        aabb.m_max.y = dMax.y + aabb.m_max.y;
        aabb.m_max.z = dMax.z + aabb.m_max.z;
        aabb.m_max.w = dMax.w + aabb.m_max.w;
    }

    HK_TIMER_SPLIT_LIST("3AxisSweep");
    if (criticalSection)
        criticalSection->enter();
    world->m_broadPhase->updateAabbs(handles, aabbs, numEntities, newPairs, delPairs);
    hkDeallocateStackChars((char*)handles);
    hkDeallocateStackChars((char*)aabbs);

    if (newPairs.m_size + delPairs.m_size > 0) {
        HK_TIMER_SPLIT_LIST("RemoveDup");
        hkTypedBroadPhaseDispatcher::removeDuplicates(newPairs, delPairs);

        HK_TIMER_SPLIT_LIST("RemoveAgt");
        world->m_broadPhaseDispatcher->removePairs(delPairs.m_data, delPairs.m_size);

        hkMemory* mem = g_hkMemoryInstance;
        int used = mem->m_pageMemoryUsed + mem->m_sysAllocsSize;
        unsigned int available = (mem->m_criticalMemoryLimit <= used) ? 0u : (unsigned int)(mem->m_criticalMemoryLimit - used);
        if ((unsigned int)(newPairs.m_size * 1000) > available) {
            mem->m_memoryState = 1;
        } else {
            HK_TIMER_SPLIT_LIST("AddAgt");
            world->m_broadPhaseDispatcher->addPairs(newPairs.m_data, newPairs.m_size,
                                                    world->m_collisionFilter ? &world->m_collisionFilter->m_ccFilter : 0);
        }
    }

    if (criticalSection)
        criticalSection->leave();
    HK_TIMER_END_LIST();
    // delPairs, then newPairs are destroyed here (stack pop + optional heap free)
}
