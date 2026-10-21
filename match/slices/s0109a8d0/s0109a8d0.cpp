// Slice s0109a8d0 -- Havok 3.1 hkDiscreteSimulation step machinery and the
// hkWorldOperationQueue append / dispatch / teardown code.
//
// 0109a8d0  hkDiscreteSimulation::stepDeltaTime           (ret 0xc, this = simulation)
// 0109aca0  hkDiscreteSimulation::recoverFromStepFailure  (ret 8,   this = simulation)
// 0109ae00  recursive add-reference walker over a small step-info pair
// 0109ae60  hkWorldObject::removeReference
// 0109ae80  broadphase-handle "less than" predicate (returns byte* out)
// 0109aed0  hkArray::insert (0x14-byte elements)
// 0109afe0  hkWorldOperationQueue::enqueue (ret 4)
// 0109b3e0  hkWorldOperationQueue::hkWorldOperationQueue (this = queue, arg = ctx)
// 0109b420  hkWorldOperationQueue::~hkWorldOperationQueue
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP
#include "types.h"

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long index, void* value);
extern "C" __declspec(dllimport) void  __stdcall InitializeCriticalSectionAndSpinCount(void* cs, unsigned long spin);
extern "C" __declspec(dllimport) void  __stdcall DeleteCriticalSection(void* cs);
extern "C" __declspec(dllimport) void  __stdcall LeaveCriticalSection(void* cs);
extern "C" __declspec(dllimport) void  __stdcall EnterCriticalSection(void* cs);

typedef float    hkReal;
typedef uint8_t  hkUint8;
typedef uint16_t hkUint16;
typedef uint32_t hkUint32;
typedef int32_t  hkInt32;

#define HK_REAL_MAX 3.402823466e+38f

// ---- monitor stream timers (TLS 0x016e42a4 = write pointer, 0x016e42a8 = end) ----------------------
extern volatile unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern volatile unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorEndTag[];                         // 0x0149cc34

#define HK_TIMER_SET_TIME(field) { hkUint32 ticks_; __asm { rdtsc } __asm { mov ticks_, eax } field = ticks_; }

struct hkMonitorCommand { const char* m_commandAndMonitor; hkUint32 m_time0; hkUint32 m_time1; };

#define HK_TIMER_COMMAND(name) do { \
    void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
        hkMonitorCommand* c_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_commandAndMonitor = name; \
        HK_TIMER_SET_TIME(c_->m_time0) \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_BEGIN(name) HK_TIMER_COMMAND("Tt" name)
#define HK_TIMER_END()       HK_TIMER_COMMAND(hkMonitorEndTag)

// ---- Havok TLS / memory ----------------------------------------------------------------------------
extern unsigned long g_hkThreadMemoryTls;                    // 0x016e4174

struct hkThreadMemory {                                      // TLS object
    hkUint8  pad00[0x20];
    char*    m_stack;                                        // +0x20
    hkUint8  pad24[0x2c - 0x24];
    char*    m_stackEnd;                                     // +0x2c
    int getStackAvailable() const { return (int)(m_stackEnd - m_stack) - 0x10; }
    void deallocateChunk(void* p, int size, int cls);        // 0x0107db10
};

struct hkMemory {                                            // 0x016e4178 (hkMemory::s_instance)
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void  v0c();
    virtual void* allocate(hkUint32 size, hkUint32 align);   // +0x10
    virtual void  deallocate(void* p, hkUint32 size, hkUint32 align);  // +0x14

    int     m_outOfMemoryFlag;                               // +0x04 (set to 1 when OOM)
    int     m_criticalMemorySize;                            // +0x08
    hkUint8 pad0c[0x08];
    int     m_memoryUsed;                                    // +0x14
    hkUint8 pad18[0x10];
    int     m_memoryAvailable;                               // +0x28
};
extern hkMemory* g_hkMemory;                                 // 0x016e4178

// ---- hkArray / hkArrayUtil -------------------------------------------------------------------------
template <class T>
struct hkArray {
    T*  m_data;                 // +0x0
    int m_size;                 // +0x4
    int m_capacityAndFlags;     // +0x8
    int getSize()     const { return m_size; }
    int getCapacity() const { return m_capacityAndFlags & 0x3fffffff; }
    T& operator[](int i) { return m_data[i]; }
};

extern "C" void hkArrayUtil_reserveMore(void* array, int sizeElem);               // 0x0107f530
extern "C" void hkArrayUtil_reserveExactly(void* array, int n, int sizeElem);     // 0x0107f4a0
extern "C" void* hkString_memCpy(void* dst, const void* src, unsigned int n);     // 0x0107f440
extern "C" void hkThreadMemory_deallocateChunk(void* mem, void* p, int n, int cls); // 0x0107db10
extern "C" void hkCriticalSection_enter(void* cs);                                // 0x0107f820

// ---- world / step ----------------------------------------------------------------------------------
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

struct hkWorldObject;

// A referenced object header as touched by the ref-count walkers in this slice.
struct hkRefBase {
    virtual void* dtor(hkUint32 flags);   // +0x0  (scalar deleting destructor)
    hkUint16 m_memSizeAndFlags;   // +0x4
    hkUint16 m_referenceCount;    // +0x6
    void addReference() { if (m_memSizeAndFlags != 0) ++m_referenceCount; }
    void removeReference();
};

// hkWorldObject is exactly hkRefBase for our purposes (25-byte removeReference).
struct hkWorldObject : public hkRefBase { };
static inline void hkWorldObject_addRef(hkWorldObject* o)
{
    if (o->m_memSizeAndFlags != 0) ++o->m_referenceCount;
}

// 0x14-byte operation record queued in hkWorldOperationQueue.
struct hkWorldOperation {
    hkUint8  m_type;     // +0x0
    hkUint8  pad01[3];
    void*    m_p1;       // +0x4
    void*    m_p2;       // +0x8
    void*    m_p3;       // +0xc
    void*    m_p4;       // +0x10
};

// The object referred to by the simulator's step (root of the reference walks).
struct hkSimulationStep {
    hkUint8 pad00[0x18];
    hkReal  m_frameDeltaTime;    // +0x18
};

// hkWorldOperationQueue -----------------------------------------------------------------------------
// layout: hkArray<op> @0 (+0x0/+0x4/+0x8), ctx @0xc, delayed hkArray<op> @0x10..0x18,
//         flag @0x1c, hkCriticalSection @0x20 (size 0x20).
struct hkCriticalSection {
    hkUint8 m_section[0x18];
    int     m_ownerLo;           // +0x18
    int     m_ownerHi;           // +0x1c
    void enter();                // 0x0107f820
    __forceinline void leave()
    {
        m_ownerLo = -1;
        m_ownerHi = -1;
        LeaveCriticalSection(this);
    }
};

struct hkWorldOperationQueue {
    hkWorldOperation* m_ops;             // +0x0
    int               m_numOps;          // +0x4
    int               m_opsCapacityFlags;// +0x8
    void*             m_ctx;             // +0xc
    hkWorldOperation* m_delayedOps;      // +0x10
    int               m_numDelayedOps;   // +0x14
    int               m_delayCapacityFlags; // +0x18
    hkUint8           m_deferring;       // +0x1c
    hkUint8           pad1d[3];
    hkCriticalSection m_criticalSection; // +0x20

    hkWorldOperationQueue(void* ctx);           // 0x0109b3e0
    ~hkWorldOperationQueue();                   // 0x0109b420
    void push(const hkWorldOperation& op);      // 0x0109afe0
};

// hkDiscreteSimulation ------------------------------------------------------------------------------
struct hkWorld;
struct hkDiscreteSimulation {
    virtual void vslot00();
    virtual hkUint32 recoverFromStepFailure(hkWorld* world, int failure);       // vtable +0x4
    virtual hkUint32 stepDeltaTime(hkWorld* world, hkReal frameDelta, hkReal physicsDelta); // vtable +0x8
    hkUint8  pad04[4];
    hkReal   m_frameDelta;               // +0x8
};

// hkWorld (subset touched here).  Offsets per the 3.1 layout.
struct hkCollisionDispatcher;
struct hkWorld {
    hkUint8  pad00[0x0c];
    hkReal   m_field0c;                  // +0x0c
    hkReal   m_field10;                  // +0x10
    hkReal   m_field14;                  // +0x14
    hkReal   m_field18;                  // +0x18
    hkUint8  pad1c[0x40];
    hkCollisionDispatcher* m_collisionDispatcher;   // +0x5c
    int  calcMaxIslandSizeEstimate();               // 0x01082ca0
    void updateCollisionFilterOnWorld(int a, int b); // 0x010869e0
};

// The vtable used by world->m_collisionDispatcher (slot +0xc = integrate).
struct hkCollisionDispatcher {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void integrateWorld(hkWorld* world, const hkStepInfo& info);   // +0xc
};

extern "C" void hkWorld_updateCollisionFilterOnWorld(hkWorld* world, int a, int b);   // 0x010869e0
extern "C" int  hkWorld_calcMaxIslandSizeEstimate(hkWorld* world);                    // 0x01082ca0
extern "C" void FUN_01099690(void* sim, hkWorld* world, const hkStepInfo& info);      // 0x01099690
extern "C" void FUN_0109a200(void* sim, hkWorld* world, const hkStepInfo& info);      // 0x0109a200
extern "C" void FUN_0109f5a0(hkWorld* world, const hkStepInfo& info);                 // 0x0109f5a0
extern "C" void FUN_0109ae60(hkWorldObject* obj);                                     // 0x0109ae60
extern "C" void hkWorldCallbackUtil_firePostSimulationCallback(hkWorld* world, const hkStepInfo& info); // 0x0109f5a0

// Stand-ins for the free functions invoked with the simulation in ecx.
struct SimOps {
    void stepIntegrate(hkWorld* world, const hkStepInfo& info);   // 0x01099690 (ecx = sim)
    void stepCollide(hkWorld* world, const hkStepInfo& info);     // 0x0109a200 (ecx = sim)
};

// ------------------------------------------------------------------ bodies

// @ 0x0109a8d0
hkUint32 hkDiscreteSimulation::stepDeltaTime(hkWorld* world, hkReal frameDeltaTime, hkReal physicsDeltaTime)
{
    (void)frameDeltaTime;

    HK_TIMER_BEGIN("Simulate");

    m_frameDelta = physicsDeltaTime;

    int maxIsland = world->calcMaxIslandSizeEstimate();

    hkThreadMemory* threadMem = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
    if (maxIsland > threadMem->getStackAvailable()) {
        int freeMem = g_hkMemory->m_memoryAvailable + g_hkMemory->m_memoryUsed;
        freeMem = (freeMem < g_hkMemory->m_criticalMemorySize)
                    ? (g_hkMemory->m_criticalMemorySize - freeMem) : 0;
        if (maxIsland > freeMem) {
            g_hkMemory->m_outOfMemoryFlag = 1;
            HK_TIMER_END();
            return 1;
        }
    }

    hkReal endTime = world->m_field18 + physicsDeltaTime;
    world->m_field14 = world->m_field18;
    world->m_field18 = endTime;
    world->m_field10 = endTime;

    hkStepInfo info(world->m_field14, endTime);
    (void)info;

    world->m_collisionDispatcher->integrateWorld(world, info);

    HK_TIMER_BEGIN("Integrate");
    ((SimOps*)this)->stepIntegrate(world, info);
    HK_TIMER_END();

    world->m_field0c = world->m_field10;

    HK_TIMER_BEGIN("Collide");
    ((SimOps*)this)->stepCollide(world, info);
    HK_TIMER_END();

    if (g_hkMemory->m_outOfMemoryFlag == 1) {
        HK_TIMER_END();
        return 2;
    }

    HK_TIMER_BEGIN("PostSimulateCb");
    hkWorldCallbackUtil_firePostSimulationCallback(world, info);
    HK_TIMER_END();

    HK_TIMER_END();
    return 0;
}

// @ 0x0109aca0
hkUint32 hkDiscreteSimulation::recoverFromStepFailure(hkWorld* world, int failure)
{
    if (failure == 1)
        return this->stepDeltaTime(world, 0, m_frameDelta);

    hkReal start = world->m_field14;
    hkReal end   = world->m_field18;
    hkStepInfo info(start, end);
    (void)info;

    world->updateCollisionFilterOnWorld(0, 1);

    if (g_hkMemory->m_outOfMemoryFlag == 1)
        return 2;

    ((SimOps*)this)->stepCollide(world, info);

    if (g_hkMemory->m_outOfMemoryFlag == 1)
        return 2;

    HK_TIMER_BEGIN("PostSimulateCb");
    hkWorldCallbackUtil_firePostSimulationCallback(world, info);
    HK_TIMER_END();

    return 0;
}

// @ 0x0109ae00
// Walks two small step records and add-refs the world object reachable from each.
// A record's +5 byte is a signed offset to a sub-object; its +0x10 is a second vtable.
struct StepRec { hkUint8 pad00[4]; hkUint8 m_kind; int8_t m_off5; hkUint8 pad06[2]; };
struct StepObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(void* other);                              // +0x20
};

void __stdcall FUN_0109ae00(StepRec** param_1)
{
    StepRec* a = param_1[0];
    if (a->m_kind == 3) {
        StepRec* b = param_1[1];
        if (b->m_kind != 3) {
            hkUint8* ap = (hkUint8*)a + a->m_off5;
            StepObj* ao = (StepObj*)(*(hkUint32*)(ap + 0x10) + (hkUint32)ap);
            ao->v20((hkUint8*)b + b->m_off5);
        }
    }
    StepRec* b2 = param_1[1];
    if (b2->m_kind == 3) {
        hkUint8* bp = (hkUint8*)b2 + b2->m_off5;
        StepObj* bo = (StepObj*)(*(hkUint32*)(bp + 0x10) + (hkUint32)bp);
        StepRec* a2 = param_1[0];
        return bo->v20((hkUint8*)a2 + a2->m_off5);
    }
}

// @ 0x0109ae60
void hkRefBase::removeReference()
{
    if (m_memSizeAndFlags != 0) {
        if (--m_referenceCount == 0)
            this->dtor(1);
    }
}

// @ 0x0109ae80
// Less-than predicate on the broadphase handles reached through two step records.
// Out byte is 1 when param_2 < param_3.
void FUN_0109ae80(hkUint8* out, hkUint8* param_2, hkUint8* param_3)
{
    hkUint32 a0 = *(hkUint16*)(*(hkUint32*)(*(hkUint32*)(param_2 + 4) + 0x5c) + 0x20);
    hkUint32 a1 = *(hkUint16*)(*(hkUint32*)(*(hkUint32*)(param_3 + 4) + 0x5c) + 0x20);

    if (a0 < a1) { *out = 1; return; }
    if (a0 == a1) {
        hkUint32 v2 = *(hkUint32*)(*(hkUint32*)(param_2 + 8) + 0x5c);
        hkUint32 v3 = *(hkUint32*)(*(hkUint32*)(param_3 + 8) + 0x5c);
        hkUint16 b0 = *(hkUint16*)(v2 + 0x20);
        hkUint16 b1 = *(hkUint16*)(v3 + 0x20);
        if (b0 < b1) { *out = 1; return; }
    }
    *out = 0;
}

// @ 0x0109aed0
// hkArray<op>::insert: insert `src->m_size` records from `src->m_data` at index `position`,
// shifting the existing [position .. size) tail up.  ecx = the array (0x14-byte elements).
struct WorldOpArray {
    hkWorldOperation* m_data;
    int m_size;
    int m_capacityAndFlags;
    void insert(int position, WorldOpArray* src);   // 0x0109aed0
};

void WorldOpArray::insert(int position, WorldOpArray* src)
{
    int count   = src->m_size;
    int newSize = m_size + count;
    int numTail = m_size - position;

    if ((m_capacityAndFlags & 0x3fffffff) < newSize) {
        int grow = (m_capacityAndFlags & 0x3fffffff) * 2;
        if (grow <= newSize) grow = newSize;
        hkArrayUtil_reserveExactly(this, grow, 0x14);
    }

    hkWorldOperation* base = m_data;

    // shift the tail up by `count` slots
    if (numTail - 1 >= 0) {
        hkWorldOperation* dst = base + (count + position) + (numTail - 1);
        int n = numTail;
        do {
            hkWorldOperation* s = dst - count;
            *dst = *s;
            --dst;
            --n;
        } while (n != 0);
    }

    // copy the inserted records into the gap
    if (count - 1 >= 0) {
        hkWorldOperation* dst = base + position + (count - 1);
        hkWorldOperation* s   = src->m_data + (count - 1);
        int n = count;
        do {
            *dst = *s;
            --dst; --s;
            --n;
        } while (n != 0);
    }

    m_size = newSize;
}

// @ 0x0109afe0
// hkWorldOperationQueue::push: append a copy of `op` to the pending-operation array and
// bump the per-type reference counts / deep-copy sub-arrays the operation owns.  this = queue.
void hkWorldOperationQueue::push(const hkWorldOperation& op)
{
    hkWorldOperationQueue* self = this;

    self->m_criticalSection.enter();

    if (self->m_numOps == (self->m_opsCapacityFlags & 0x3fffffff))
        hkArrayUtil_reserveMore(&self->m_ops, 0x14);

    int idx = self->m_numOps;
    hkWorldOperation* base = self->m_ops;
    self->m_numOps = idx + 1;
    ++*(int*)((char*)self->m_ctx + 0x88);

    hkWorldOperation* dst = base + idx;
    hkString_memCpy(dst, &op, 0x14);

    switch (dst->m_type) {
    case 1: case 2: case 3: case 4:
    case 8: case 9: case 0xa: case 0xb:
    case 0xd: case 0xe:
    case 0x12: case 0x13:
    case 0x15:
    case 0x17: case 0x18: case 0x19: case 0x1a: case 0x1b: case 0x1c:
    case 0x20: case 0x21: case 0x22:
        hkWorldObject_addRef((hkWorldObject*)dst->m_p1);
        break;

    case 5:
        hkWorldObject_addRef((hkWorldObject*)dst->m_p1);
        hkWorldObject_addRef((hkWorldObject*)dst->m_p2);
        break;

    case 6:
    case 7:
    case 0xf:
    case 0x10:
    case 0x16: {
        hkUint16 n = *(hkUint16*)((char*)dst + 8);
        void* buf = g_hkMemory->allocate((hkUint32)n << 2, 4);
        dst->m_p1 = buf;
        hkString_memCpy(buf, *(void**)((char*)&op + 4), (hkUint32)n << 2);
        void** it = (void**)dst->m_p1;
        void** end = it + n;
        for (; it < end; ++it)
            hkWorldObject_addRef((hkWorldObject*)*it);
        break;
    }

    case 0xc:
        hkWorldObject_addRef((hkWorldObject*)dst->m_p1);
        hkWorldObject_addRef((hkWorldObject*)dst->m_p2);
        if (self->m_deferring != 0) {
            if (self->m_numDelayedOps == (self->m_delayCapacityFlags & 0x3fffffff))
                hkArrayUtil_reserveMore(&self->m_delayedOps, 0x14);
            hkWorldOperation* d = self->m_delayedOps + self->m_numDelayedOps;
            *(hkUint32*)((char*)d + 0)  = *(hkUint32*)((char*)dst + 0);
            *(hkUint32*)((char*)d + 4)  = *(hkUint32*)((char*)dst + 4);
            *(hkUint32*)((char*)d + 8)  = *(hkUint32*)((char*)dst + 8);
            *(hkUint32*)((char*)d + 0xc) = *(hkUint32*)((char*)dst + 0xc);
            *(hkUint32*)((char*)d + 0x10) = *(hkUint32*)((char*)dst + 0x10);
            ++self->m_numDelayedOps;
            --self->m_numOps;
        }
        break;

    case 0x11:
        hkWorldObject_addRef((hkWorldObject*)dst->m_p1);
        {
            void* p = g_hkMemory->allocate(0x20, 0x24);
            if (p == 0) {
                dst->m_p2 = 0;
            } else {
                const hkUint32* s = *(const hkUint32**)((char*)&op + 8);
                hkUint32* d = (hkUint32*)p;
                d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3];
                d[4] = s[4]; d[5] = s[5]; d[6] = s[6]; d[7] = s[7];
                dst->m_p2 = p;
            }
        }
        break;

    case 0x1d:
        hkWorldObject_addRef((hkWorldObject*)dst->m_p1);
        goto dec_counters;

    case 0x1e:
        ((hkRefBase*)dst->m_p1)->removeReference();
dec_counters:
        --self->m_numOps;
        --*(int*)((char*)self->m_ctx + 0x88);
        break;

    default:
        break;
    }

    self->m_criticalSection.leave();
}

// @ 0x0109b3e0
hkWorldOperationQueue::hkWorldOperationQueue(void* ctx)
{
    m_opsCapacityFlags = (int)0x80000000;
    m_ops = 0;
    m_numOps = 0;
    m_delayCapacityFlags = (int)0x80000000;
    m_delayedOps = 0;
    m_numDelayedOps = 0;
    InitializeCriticalSectionAndSpinCount(&m_criticalSection, 4000);
    m_ctx = ctx;
    m_deferring = 0;
}
// @ 0x0109b420
hkWorldOperationQueue::~hkWorldOperationQueue()
{
    DeleteCriticalSection(&m_criticalSection);
    if (!((int)m_delayCapacityFlags < 0)) {
        hkThreadMemory* mem = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
        mem->deallocateChunk(m_delayedOps,
            ((m_delayCapacityFlags & 0x3fffffff) * 5) * 4, 0x14);
    }
    if (!((int)m_opsCapacityFlags < 0)) {
        hkThreadMemory* mem = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
        mem->deallocateChunk(m_ops,
            ((m_opsCapacityFlags & 0x3fffffff) * 5) * 4, 0x14);
    }
}
