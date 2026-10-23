// Slice s01099cd0 -- Havok 3.1 hkDiscreteSimulation collide machinery.
//
// 01099cd0  hkDiscreteSimulation::collideEntitiesBroadPhaseDiscrete (static: entities, n, world)
// 0109a200  hkDiscreteSimulation::stepCollide (unnamed in pdb; ecx = simulation, (world, stepInfo))
// 0109a6a0  hkDiscreteSimulation::reintegrateAndRecollideEntities (virtual)
// 0109a800  hkDiscreteSimulation::collideEntitiesDiscrete (virtual)
//
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP
#include "types.h"

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long index, void* value);

typedef float    hkReal;
typedef uint8_t  hkUint8;
typedef uint16_t hkUint16;
typedef uint32_t hkUint32;
typedef int32_t  hkInt32;

// ---- monitor-stream TLS (same globals the neighbouring slice uses) ------------------------------
extern volatile unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern volatile unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern unsigned long g_hkThreadMemoryTls;                    // 0x016e4174
extern hkUint8* g_hkMemory;                                  // 0x016e4178 (hkMemory::s_instance)

#define HK_RDTSC() hk_rdtsc()
__forceinline hkUint32 hk_rdtsc() { hkUint32 t_; __asm { rdtsc } __asm { mov t_, eax } return t_; }

// "Lt<name>" begin command: {cmd, time0, time1, subMonitor}
struct hkMonitorCommand { const char* m_command; hkUint32 m_time0; hkUint32 m_time1; const char* m_sub; };
// plain begin/end command: {cmd, time0, time1}
struct hkMonitorEnd { const char* m_command; hkUint32 m_time0; hkUint32 m_time1; };

#define HK_TIMER_BEGIN2(cmd, sub) do { \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < TlsGetValue(g_hkMonitorStreamEndTls)) { \
        hkMonitorCommand* c_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_command = cmd; c_->m_sub = sub; c_->m_time0 = HK_RDTSC(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)

#define HK_TIMER_BEGIN1(cmd) do { \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < TlsGetValue(g_hkMonitorStreamEndTls)) { \
        hkMonitorEnd* c_ = (hkMonitorEnd*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_command = cmd; c_->m_time0 = HK_RDTSC(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)

#define HK_TIMER_END1() do { \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < TlsGetValue(g_hkMonitorStreamEndTls)) { \
        hkMonitorEnd* c_ = (hkMonitorEnd*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_command = (const char*)&DAT_0143cd94; c_->m_time0 = HK_RDTSC(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)

extern const char DAT_0143cd94[];
extern const char DAT_0149cc34[];

// ---- thread memory ------------------------------------------------------------------------------
class hkThreadMemory {
public:
    hkUint8 pad00[0x20];
    char*   m_stack;        // +0x20
    hkUint8 pad24[0x2c - 0x24];
    char*   m_stackEnd;     // +0x2c
    hkUint8 pad30[0x40 - 0x30];
    char*   m_highWater;    // +0x40
    char* getStackAvailable() const { return m_stackEnd; }
    void* allocTop(int nbytes);   // vtable +0x0c
    void  freeTop(void* p);       // vtable +0x10
};
extern "C" void hkThreadMemory_deallocateChunk(void* mem, void* p, int n, int cls); // 0x0107db10

// ---- world / entity -----------------------------------------------------------------------------
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

class hkMotion {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void setStepInfo(float* p);       // +0x0c
};

class hkShape {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void computeAabb(void* a, float half, void* out);   // +0x0c
};

class hkEntity {
public:
    hkUint8  pad00[0x1c];
    hkShape* m_shape;        // +0x1c
    hkUint8  pad20[0x24 - 0x20];
    hkUint8* m_shapeData;    // +0x24
    hkUint8  pad28[0x30 - 0x28];
    hkUint8  m_aabb[0x10];   // +0x30
    hkUint8  pad40[0x58 - 0x40];
    hkMotion* m_motion;      // +0x58
};

class hkBroadPhase {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void sweep(void* a, void* b, int n, void* outA, void* outB);   // +0x1c
};

class hkWorld {
public:
    hkUint8 pad00[0x0c];
    hkReal  m_field0c;      // +0x0c
    hkReal  m_field10;      // +0x10
    hkReal  m_field14;      // +0x14
    hkReal  m_field18;      // +0x18
    hkUint8 pad1c[0x38 - 0x1c];
    void*   m_islands;      // +0x38
    int     m_numIslands;   // +0x3c
    hkUint8 pad40[0x78 - 0x40];
    void*   m_simPtr;       // +0x78
    hkUint8 pad7c[0x88 - 0x7c];
    int     m_field88;      // +0x88
    int     m_field8c;      // +0x8c
    hkUint8 pad90[0x94 - 0x90];
    char    m_field94;      // +0x94
    hkUint8 pad95[0x2e8 - 0x95];
    int     m_numBroadPhase; // +0x2e8

    void executePendingOperations();   // 0x01082bf0
    void reportError(void* msg);       // 0x010829d0
};

struct hkDiscreteSimulation {
    virtual void vslot00();                                                              // +0x0
    virtual void vslot04();                                                              // +0x4
    virtual void vslot08();                                                              // +0x8
    virtual void reintegrateAndRecollideEntities(hkEntity** entities, int n, hkWorld* world); // +0xc
    virtual void collideEntitiesDiscrete(hkEntity** entities, int n, hkWorld* world, const hkStepInfo& info); // +0x10
    static void collideEntitiesBroadPhaseDiscrete(hkEntity** entities, int n, hkWorld* world); // 0x01099cd0
    void stepCollide(hkWorld* world, const hkStepInfo& info);                            // 0x0109a200
    void FUN_01099be0(hkEntity** entities, int n, void* sim, void* fn);                  // 0x01099be0
};

// ---- out-of-slice helpers ------------------------------------------------------------------------
extern "C" void FUN_010995d0();
extern "C" void backStepMotionState(int startTime, void* motionPlus10);   // 0x0120a260
extern "C" void hkLs_invalidateTimsOfEntity(hkEntity* e, void* sim);      // 0x010a3890
extern "C" void FUN_010cc560(void* a, void* b);                           // 0x010cc560
extern "C" void FUN_010cc480(float a, void* b);                           // 0x010cc480
extern "C" void FUN_010cc410(void* a, int b, void* c);                    // 0x010cc410
extern "C" void FUN_010fc700(void* a, void* b);                           // 0x010fc700
extern "C" void FUN_0109f7e0(void* a, void* b, const void* c);            // 0x0109f7e0
extern "C" void FUN_0109f6c0(void* a, const void* b);                     // 0x0109f6c0

// =================================================================================================
// @ 0x01099cd0
void __cdecl hkDiscreteSimulation::collideEntitiesBroadPhaseDiscrete(hkEntity** entities, int numEntities, hkWorld* world)
{
    HK_TIMER_BEGIN2("LtBroadPhase", "InitMem");

    int n = world->m_numBroadPhase;
    hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);

    // two hkArray<void*> (8-byte elements) and one hkArray<0x20-byte> + one hkArray<void*> scratch
    void** a1 = (void**)tm->m_stack;
    int sz1 = (n * 8 + 0x10) & ~0xf;
    if ((hkUint32)tm->m_stackEnd < (hkUint32)((char*)a1 + sz1)) a1 = (void**)tm->allocTop(sz1);
    else tm->m_stack = (char*)a1 + sz1;

    void** a2 = (void**)tm->m_stack;
    int sz2 = (n * 8 + 0x10) & ~0xf;
    if ((hkUint32)tm->m_stackEnd < (hkUint32)((char*)a2 + sz2)) a2 = (void**)tm->allocTop(sz2);
    else tm->m_stack = (char*)a2 + sz2;

    char* a3 = tm->m_stack;
    int sz3 = numEntities * 0x20 + 0x10;
    if ((hkUint32)tm->m_stackEnd < (hkUint32)(a3 + sz3)) a3 = (char*)tm->allocTop(sz3);
    else tm->m_stack = a3 + sz3;

    char* a4 = tm->m_stack;
    int sz4 = (numEntities * 4 + 0x10) & ~0xf;
    if ((hkUint32)tm->m_stackEnd < (hkUint32)(a4 + sz4)) a4 = (char*)tm->allocTop(sz4);
    else tm->m_stack = a4 + sz4;

    float half = *(float*)((char*)world->m_simPtr + 8) * 0.5f;

    HK_TIMER_BEGIN1("StCalcAabbs");
    for (int i = 0; i < numEntities; ++i) {
        hkEntity* e = entities[i];
        *(void**)(a4 + i * 4) = e->m_aabb;
        e->m_shape->computeAabb(e->m_shapeData, half, a3 + i * 0x20);
    }
    HK_TIMER_END1();

    HK_TIMER_BEGIN1("St3AxisSweep");
    ((hkBroadPhase*)world->m_simPtr)->sweep(a4, a1, numEntities, a2, a1);
    HK_TIMER_END1();

    tm->m_stack = a4;
    if (a4 == tm->m_highWater) tm->freeTop(a4);
    tm->m_stack = (char*)a1;
    if (a1 == (void**)tm->m_highWater) tm->freeTop(a1);

    if (numEntities > 0) {
        HK_TIMER_BEGIN1("StRemoveDup");
        FUN_010cc560(0, &half);
        HK_TIMER_BEGIN1("StRemoveAgt");
        FUN_010cc480(half, a1);
        int freeMem = *(int*)(g_hkMemory + 0x28) + *(int*)(g_hkMemory + 0x14);
        freeMem = (freeMem < *(int*)(g_hkMemory + 8)) ? (*(int*)(g_hkMemory + 8) - freeMem) : 0;
        if (numEntities * 0x280 <= freeMem) {
            HK_TIMER_BEGIN1("StAddAgt");
            void* p = (world->m_numBroadPhase != 0) ? (void*)(world->m_numBroadPhase + 8) : 0;
            FUN_010cc410(0, numEntities, p);
            goto done;
        }
        *(int*)(g_hkMemory + 4) = 1;
    }
    HK_TIMER_END1();
done:
    HK_TIMER_END1();

    tm->m_stack = (char*)a1;
    if ((hkUint32)a1 == (hkUint32)tm->m_highWater) tm->freeTop(a1);
    if (((hkUint32)a2 & 0x80000000) == 0) hkThreadMemory_deallocateChunk(tm, a2, (hkUint32)a2 << 3, 0x14);
    tm->m_stack = (char*)a3;
    if ((hkUint32)a3 == (hkUint32)tm->m_highWater) tm->freeTop(a3);
    if (((hkUint32)a4 & 0x80000000) == 0) hkThreadMemory_deallocateChunk(tm, a4, (hkUint32)a4 << 3, 0x14);
}

// =================================================================================================
// @ 0x0109a200
void hkDiscreteSimulation::stepCollide(hkWorld* world, const hkStepInfo& stepInfo)
{
    HK_TIMER_BEGIN2("LtSimulate", "Collide");

    *(hkStepInfo*)((char*)this + 0x170) = stepInfo;
    void* p = world->m_simPtr;
    *(hkStepInfo*)((char*)p + 0x10) = stepInfo;
    *(float*)((char*)this + 0x2a4) = *(float*)((char*)this + 0x2b0) * (float)stepInfo.m_deltaTime;
    *(float*)((char*)this + 0x2a8) = (float)*(int*)((char*)this + 0x2ac) * (float)stepInfo.m_invDeltaTime;
    ++world->m_field8c;

    for (int i = 0; i < world->m_numIslands; ++i) {
        void* island = *(void**)((char*)world->m_islands + i * 4);
        hkDiscreteSimulation::collideEntitiesBroadPhaseDiscrete(
            *(hkEntity***)((char*)island + 0x3c), *(int*)((char*)island + 0x40), world);
        if (*(int*)(g_hkMemory + 4) == 1) {
            if (--world->m_field8c == 0 && world->m_field88 != 0 && world->m_field94 == 0)
                world->executePendingOperations();
            HK_TIMER_END1();
            return;
        }
    }

    if (--world->m_field8c == 0 && world->m_field88 != 0 && world->m_field94 == 0)
        world->executePendingOperations();

    ++world->m_field8c;
    for (int i = 0; i < world->m_numIslands; ++i) {
        void* island = *(void**)((char*)world->m_islands + i * 4);
        void* sim = world->m_simPtr;
        HK_TIMER_BEGIN1("TtNarrowPhase");
        *(int*)((char*)sim + 0x28) = *(int*)sim + 0x1a50;
        *((hkUint8*)sim + 0xc) = 0;
        FUN_010fc700((char*)island + 0x4c, sim);
        HK_TIMER_END1();
        if (*(int*)(g_hkMemory + 4) == 1) {
            if (--world->m_field8c == 0 && world->m_field88 != 0 && world->m_field94 == 0)
                world->executePendingOperations();
            HK_TIMER_END1();
            return;
        }
        if (*(int*)((char*)this + 0x154) != 0) {
            HK_TIMER_BEGIN1("TtIslandPostCollideCb");
            FUN_0109f7e0(this, island, &stepInfo);
            HK_TIMER_END1();
        }
    }

    if (--world->m_field8c == 0 && world->m_field88 != 0 && world->m_field94 == 0)
        world->executePendingOperations();

    if (*(int*)((char*)this + 0x13c) != 0) {
        HK_TIMER_BEGIN1("StPostCollideCB");
        FUN_0109f6c0(this, &stepInfo);
        HK_TIMER_END1();
    }
    HK_TIMER_END1();
}

// =================================================================================================
// @ 0x0109a6a0
void hkDiscreteSimulation::reintegrateAndRecollideEntities(hkEntity** entities, int numEntities, hkWorld* world)
{
    if (world->m_field8c != 0) {
        struct Report { hkUint8 tag; hkUint8 pad[3]; void* entities; hkUint16 numEntities; };
        Report r;
        r.tag = 0x16;
        r.entities = entities;
        r.numEntities = (hkUint16)numEntities;
        world->reportError(&r);
        return;
    }

    hkReal endTime = world->m_field18;
    world->m_field8c = 1;
    hkStepInfo info(world->m_field0c, endTime);
    *(hkStepInfo*)((char*)world->m_simPtr + 0x10) = info;

    for (int i = 0; i < numEntities; ++i) {
        hkEntity* e = entities[i];
        backStepMotionState(*(int*)&world->m_field0c, (char*)e->m_motion + 0x10);
        e->m_motion->setStepInfo(&info.m_startTime);
    }

    hkDiscreteSimulation::collideEntitiesBroadPhaseDiscrete(entities, numEntities, world);

    for (int i = 0; i < numEntities; ++i)
        hkLs_invalidateTimsOfEntity(entities[i], world->m_simPtr);

    FUN_01099be0(entities, numEntities, world->m_simPtr, (void*)&FUN_010995d0);

    if (--world->m_field8c == 0 && world->m_field88 != 0 && world->m_field94 == 0)
        world->executePendingOperations();
}

// =================================================================================================
// @ 0x0109a800
void hkDiscreteSimulation::collideEntitiesDiscrete(hkEntity** entities, int numEntities, hkWorld* world, const hkStepInfo& stepInfo)
{
    hkStepInfo saved = stepInfo;
    void* sim = world->m_simPtr;
    hkStepInfo* p = (hkStepInfo*)((char*)sim + 0x10);
    *p = stepInfo;
    ++world->m_field8c;

    hkDiscreteSimulation::collideEntitiesBroadPhaseDiscrete(entities, numEntities, world);
    FUN_01099be0(entities, numEntities, sim, (void*)&FUN_010995d0);

    if (--world->m_field8c == 0 && world->m_field88 != 0 && world->m_field94 == 0)
        world->executePendingOperations();

    *p = saved;
}
