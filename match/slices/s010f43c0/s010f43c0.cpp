// flags: /O2 /MD /Gy /TP /vc71
// Slice s010f43c0: Havok 3.1.0 hkContinuousSimulation step recovery + hk3AxisSweep maintenance.
//
//   0x010f43c0  hkContinuousSimulation::stepDeltaTime
//   0x010f4850  hkContinuousSimulation::recoverFromStepFailure
//   0x010f4ab0  hk3AxisSweep::updateNodesAfterInsert
//   0x010f4c60  hk3AxisSweep::updateNodesAfterDelete
//   0x010f4e10  binary search over the x endpoint array (cdecl helper)
//   0x010f4e70  hk3AxisSweep::shiftBroadPhase
//   0x010f4f50  hk3AxisSweep::hkBpAxis::mergeBatch
//   0x010f50f0  hk3AxisSweep::hkBpAxis::remove
//   0x010f5150  hk3AxisSweep::setBitsBasedOnXInterval
//   0x010f5310  hk3AxisSweep::FUN_010f5310 (numNodes-1)
//   0x010f5320  hk3AxisSweep::getAabbCacheSize
//
// Household names/types (hkBpNode, hkBpAxis, offsets) are those recovered in slice s010f5340.
#include "types.h"
#include <stddef.h>
#include <math.h>
#include <intrin.h>

typedef uint32_t hkUint32;
typedef uint16_t hkUint16;
typedef unsigned long hkUlong;
typedef float hkReal;
typedef hkUint16 BpInt;

// ---------------------------------------------------------------------------------------------
// monitor stream timers (inlined TLS appends; record = { name, rdtsc, pad })
// ---------------------------------------------------------------------------------------------
extern unsigned long g_hkMonitorStreamEndTls;      // 0x016e42a8
extern unsigned long g_hkMonitorStreamCurTls;      // 0x016e42a4
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);

struct hkMonitorStreamRecord { const char* m_name; unsigned int m_time; unsigned int m_pad; };

static __forceinline void hkMonitorStamp(const char* name)
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    void* cur = TlsGetValue(g_hkMonitorStreamCurTls);
    if (cur < end)
    {
        hkMonitorStreamRecord* r = (hkMonitorStreamRecord*)TlsGetValue(g_hkMonitorStreamCurTls);
        r->m_name = name;
        r->m_time = (unsigned int)__rdtsc();
        TlsSetValue(g_hkMonitorStreamCurTls, r + 1);
    }
}
static __forceinline void hkMonitorEnd() { hkMonitorStamp((const char*)0x0149cc34); }

// ---------------------------------------------------------------------------------------------
// memory
// ---------------------------------------------------------------------------------------------
extern unsigned long g_hkThreadMemoryTls;          // 0x016e4174

struct hkThreadMemoryRaw
{
    void** vftable;           // +0x00
    char pad04[0x1c];         // +0x04
    char* m_stackCurrent;     // +0x20
    char* m_stackPrev;        // +0x24
    char* m_stackBase;        // +0x28
    char* m_stackEnd;         // +0x2c
};
static __forceinline hkThreadMemoryRaw* hkThreadMemoryGet() { return (hkThreadMemoryRaw*)TlsGetValue(g_hkThreadMemoryTls); }

class hkMemory
{
public:
    void** vftable;             // +0x00
    int m_memoryState;          // +0x04 (1 = out of memory)
    int m_criticalMemoryLimit;  // +0x08
    int m_referenceCount;       // +0x0c
    int m_sysAllocs0;           // +0x10
    int m_sysAllocsSize;        // +0x14
    int m_stats18;              // +0x18
    int m_stats1c;              // +0x1c
    int m_stats20;              // +0x20
    int m_stats24;              // +0x24
    int m_pageMemoryUsed;       // +0x28
};
extern hkMemory* g_hkMemoryInstance;               // 0x016e4178

// ---------------------------------------------------------------------------------------------
// math
// ---------------------------------------------------------------------------------------------
__declspec(align(16)) struct hkVector4 { hkReal x, y, z, w; };

class hkStepInfo
{
public:
    hkReal m_startTime;      // +0x00
    hkReal m_endTime;        // +0x04
    hkReal m_deltaTime;      // +0x08
    hkReal m_invDeltaTime;   // +0x0c
    hkStepInfo() {}
    hkStepInfo(hkReal startTime, hkReal endTime);    // 0x01099430
};

static __forceinline hkReal hkInvDelta(hkReal delta)
{
    return (delta == 0.0f) ? 0.0f : 1.0f / delta;
}

// ---------------------------------------------------------------------------------------------
// containers / broadphase types
// ---------------------------------------------------------------------------------------------
template <typename T>
class hkArray
{
public:
    T* m_data;
    int m_size;
    int m_capacityAndFlags;
};

class hkBroadPhaseHandle
{
public:
    hkUint32 m_id;   // +0
};

// hk3AxisSweep node / axis layouts (see slice s010f5340)
// 0x015ba374. mergeBatch indexes this with (value & 1) + axis * 2; the retail caller only
// passes axis 0..2, but the original reads the surrounding image words for other axis values.
static const int* const s_memberOffsets = (const int*)0x015ba374;

struct hkBpEndPoint
{
    BpInt m_value;       // +0
    BpInt m_nodeIndex;   // +2
};

struct hkBpNode
{
    BpInt min_y;                       // +0
    BpInt min_z;                       // +2
    BpInt max_y;                       // +4
    BpInt max_z;                       // +6
    BpInt min_x;                       // +8
    BpInt max_x;                       // +a
    hkBroadPhaseHandle* m_handle;      // +c
};

class hkReferencedObject
{
public:
    virtual ~hkReferencedObject();
    hkUint16 m_memSizeAndFlags;   // +4
    hkUint16 m_referenceCount;    // +6
};

// hkBroadPhase: the only entry used here is the virtual at vtable+0x34 (slot 13), which the
// retail hk3AxisSweep::shiftBroadPhase reaches through a base-qualified virtual dispatch.
class hkBroadPhase : public hkReferencedObject
{
public:
    virtual void bv01();
    virtual void bv02();
    virtual void bv03();
    virtual void bv04();
    virtual void bv05();
    virtual void bv06();
    virtual void bv07();
    virtual void bv08();
    virtual void bv09();
    virtual void bv10();
    virtual void bv11();
    virtual void bv12();
    virtual void shiftBroadPhaseBase(const hkVector4& delta, hkVector4& effectiveDelta,
                                     hkArray<hkBroadPhaseHandle*>& movedObjects);
    hkUint32 m_type;              // +8
};

class hk3AxisSweep : public hkBroadPhase
{
public:
    struct hkBpAxis
    {
        hkArray<hkBpEndPoint> m_endPoints;   // +0 (m_data,+4 size,+8 cap)

        void mergeBatch(hkBpNode* nodes, int split, int numNew, int axis, hkBpEndPoint* out);
        void remove(int minPosition, int maxPosition);
    };

    virtual void shiftBroadPhase(const hkVector4& delta, hkVector4& effectiveDelta,
                                 hkArray<hkBroadPhaseHandle*>& movedObjects);

    void FUN_010f5150(int numNodes, int xValue, const hkBpNode& queryNode, int queryNodeIndex,
                      hkUint32* bitField) const;
    int FUN_010f5310() const;
    int getAabbCacheSize() const;

protected:
    void updateNodesAfterInsert(hkBpNode* nodes, int numNodes, hkBpNode& newNode);
    void updateNodesAfterDelete(hkBpNode* nodes, int numNodes, hkBpNode& oldNode);

public:
    hkVector4 m_offsetLow;              // +0x10
    hkVector4 m_offsetHigh;             // +0x20
    hkVector4 m_scale;                  // +0x30
    hkArray<hkBpNode> m_nodes;          // +0x40
    hkBpAxis m_axis[3];                 // +0x4c
    int m_numMarkers;                   // +0x70
    int m_ld2NumMarkers;                // +0x74
    void* m_markers;                    // +0x78
};
typedef char hk3AxisSweep_layout_check[(offsetof(hk3AxisSweep, m_nodes) == 0x40
                                        && offsetof(hk3AxisSweep, m_axis) == 0x4c
                                        && offsetof(hk3AxisSweep, m_numMarkers) == 0x70
                                        && offsetof(hk3AxisSweep, m_markers) == 0x78) ? 1 : -1];

// ---------------------------------------------------------------------------------------------
// world / collision types
// ---------------------------------------------------------------------------------------------
class hkEntity;
struct hkContactPointMaterial { void* m_userData; hkUint16 m_friction; uint8_t m_restitution; uint8_t m_flags; };

struct hkContactPointRemovedEvent
{
    hkUint16 m_contactPointId;                       // +0x00
    hkContactPointMaterial* m_contactPointMaterial;  // +0x04
    hkEntity* m_entityA;                             // +0x08
    hkEntity* m_entityB;                             // +0x0c
    hkEntity* m_callbackFiredFrom;                   // +0x10
    void* m_internalContactMgr;                      // +0x14
};

struct hkToiEvent                                  // 0x40
{
    hkReal m_time;                                   // +0x00
    hkEntity* m_entities[2];                         // +0x04
    hkReal m_seperatingVelocity;                     // +0x0c
    hkContactPointMaterial m_material;               // +0x10
    void* m_contactMgr;                              // +0x18
    char pad1c[4];
    hkVector4 m_contactPosition;                     // +0x20
};

class hkEntity
{
public:
    char pad00[8];
    class hkWorld* m_world;                          // +0x08
    char pad0c[0xa0 - 0x0c];
    int m_hasContactPointRemovedCallback;            // +0xa0
};

class hkWorld;

class hkWorldMaintenanceMgr
{
public:
    virtual void mv0();
    virtual void mv1();
    virtual void mv2();
    virtual void performMaintenance(hkWorld* world, const hkStepInfo& stepInfo);   // vtable +0x0c
};

class hkWorld
{
public:
    char pad00[0x0c];
    hkReal m_currentTime;                            // +0x0c
    hkReal m_timeOfNextFrame;                        // +0x10
    hkReal m_timeOfLastPsi;                          // +0x14
    hkReal m_timeOfNextPsi;                          // +0x18
    char pad1c[0x5c - 0x1c];
    hkWorldMaintenanceMgr* m_maintenanceMgr;         // +0x5c
    char pad60[0x120 - 0x60];
    hkArray<void*> m_worldPostSimulationListeners;   // +0x120

    int calcMaxIslandSizeEstimate() const;           // 0x01082ca0
    void updateCollisionFilterOnWorld(int mode, int fullCheck);   // 0x010869e0
};

struct hkWorldCallbackUtil
{
    static void fireContactPointRemoved(hkWorld* world, hkContactPointRemovedEvent& event);   // 0x0109f160
    static void firePostSimulationCallback(hkWorld* world, const hkStepInfo& stepInfo);       // 0x0109f5a0
};
struct hkEntityCallbackUtil
{
    static void fireContactPointRemovedInternal(hkEntity* entity, hkContactPointRemovedEvent& event);  // 0x0109e8e0
};

// ---------------------------------------------------------------------------------------------
// simulation
// ---------------------------------------------------------------------------------------------
enum hkStepResult { HK_STEP_RESULT_SUCCESS = 0, HK_STEP_RESULT_MEMORY_FAILURE = 1, HK_STEP_RESULT_BUSY = 2 };

class hkToiResourceMgr
{
public:
    virtual void tv0();
    virtual void tv1();
    virtual void resetForStep();     // vtable +0x08
};

class hkDiscreteSimulation
{
public:
    void stepIntegrate(hkWorld* world, const hkStepInfo& stepInfo);   // 0x01099690
};

class hkContinuousSimulation
{
public:
    virtual void vslot0();
    virtual void vslot1();
    virtual hkStepResult vslot2(hkWorld* world, int a, int b);
    virtual void vslot3();
    virtual void vslot4();
    virtual void vslot5();
    virtual void vslot6();
    virtual void vslot7();
    virtual void vslot8();
    virtual void vslot9();
    virtual void vslot10();
    virtual void vslot11();
    virtual void resetCollisionInformationForEntities(hkEntity** entities, int numEntities, hkWorld* world);   // +0x30
    virtual void reintegrateAndRecollideEntities(hkEntity** entities, int numEntities, hkWorld* world);         // +0x34

    hkUint32 m_refCount;                             // +0x04
    hkReal m_frameDeltaTime;                         // +0x08
    char m_synchronizeFrameAndPhysicsTime;           // +0x0c
    char pad0d[3];
    int m_stepFlag;                                  // +0x10 (0/1/2)
    int m_simulationStep;                            // +0x14
    hkArray<hkToiEvent> m_toiEvents;                 // +0x18
    hkToiResourceMgr* m_toiResourceMgr;              // +0x24
    int m_pad28;                                     // +0x28

    hkStepResult handleAllToisTill(hkWorld* world, hkReal time);   // 0x010f0830
    void collide(hkWorld* world, const hkStepInfo& stepInfo);      // 0x010f3600

    virtual hkStepResult stepDeltaTime(hkWorld* world, hkReal physicsDeltaTime, hkReal frameDeltaTime);
    virtual hkStepResult recoverFromStepFailure(hkWorld* world, hkStepResult stepResult);
};
typedef char hkContinuousSimulation_layout_check[(offsetof(hkContinuousSimulation, m_toiEvents) == 0x18
                                                  && offsetof(hkContinuousSimulation, m_toiResourceMgr) == 0x24) ? 1 : -1];

// ---------------------------------------------------------------------------------------------
// hkContinuousSimulation::stepDeltaTime (0x010f43c0)
// ---------------------------------------------------------------------------------------------
// @ 0x010f43c0
hkStepResult hkContinuousSimulation::stepDeltaTime(hkWorld* world, hkReal physicsDeltaTime, hkReal frameDeltaTime)
{
    hkMonitorStamp("TtSimulate");

    m_frameDeltaTime = frameDeltaTime;
    world->m_timeOfNextFrame += physicsDeltaTime;

    if (m_simulationStep == 1)
        goto endFrame;

    do
    {
        if (m_synchronizeFrameAndPhysicsTime != 0
            && fabs(world->m_timeOfNextFrame - world->m_timeOfNextPsi) < frameDeltaTime * 0.01f
            && physicsDeltaTime / frameDeltaTime > 0.1f)
        {
            world->m_timeOfNextFrame = world->m_timeOfNextPsi;
        }

        if (m_toiEvents.m_size != 0)
        {
            hkReal minTime = (world->m_timeOfNextFrame < world->m_timeOfNextPsi)
                           ? world->m_timeOfNextFrame : world->m_timeOfNextPsi;
            if (handleAllToisTill(world, minTime) != 0)
            {
                hkMonitorEnd();
                return (hkStepResult)2;
            }
        }

        if (world->m_timeOfNextFrame <= world->m_timeOfNextPsi)
        {
            world->m_currentTime = world->m_timeOfNextFrame;
            goto finish;
        }

        m_toiResourceMgr->resetForStep();
        m_pad28 = 0;

        const int sizeEstimate = world->calcMaxIslandSizeEstimate();
        hkThreadMemoryRaw* tm = hkThreadMemoryGet();
        const int freeChunk = (int)(tm->m_stackEnd - tm->m_stackCurrent) - 0x10;
        if (sizeEstimate > freeChunk)
        {
            hkMemory* mem = g_hkMemoryInstance;
            const int used = mem->m_sysAllocsSize + mem->m_pageMemoryUsed;
            int available = (mem->m_criticalMemoryLimit > used)
                          ? mem->m_criticalMemoryLimit - used : 0;
            if (sizeEstimate > available)
            {
                mem->m_memoryState = 1;
                hkMonitorEnd();
                return (hkStepResult)1;
            }
        }

        hkStepInfo psiStep;
        const hkReal newPsi = frameDeltaTime + world->m_timeOfNextPsi;
        world->m_timeOfLastPsi = world->m_timeOfNextPsi;
        world->m_timeOfNextPsi = newPsi;
        psiStep.m_startTime = world->m_timeOfLastPsi;
        psiStep.m_endTime = newPsi;
        psiStep.m_deltaTime = newPsi - world->m_timeOfLastPsi;
        psiStep.m_invDeltaTime = hkInvDelta(psiStep.m_deltaTime);

        world->m_maintenanceMgr->performMaintenance(world, psiStep);
        world->m_currentTime = world->m_timeOfLastPsi;
        ((hkDiscreteSimulation*)this)->stepIntegrate(world, psiStep);

        if (m_stepFlag != 0)
        {
            m_simulationStep = 1;
            goto finish;
        }

    endFrame:
        {
            hkStepInfo frameStep;
            frameStep.m_startTime = world->m_timeOfLastPsi;
            frameStep.m_endTime = world->m_timeOfNextPsi;
            frameStep.m_deltaTime = world->m_timeOfNextPsi - world->m_timeOfLastPsi;
            frameStep.m_invDeltaTime = hkInvDelta(frameStep.m_deltaTime);
            collide(world, frameStep);
        }

        if (g_hkMemoryInstance->m_memoryState == 1)
        {
            hkMonitorEnd();
            return (hkStepResult)2;
        }

        m_simulationStep = 0;
    } while (m_stepFlag != 2);

finish:
    hkMonitorEnd();

    if (world->m_worldPostSimulationListeners.m_size != 0)
    {
        hkMonitorStamp("TtPostSimulateCb");

        hkStepInfo postStep;
        postStep.m_startTime = world->m_timeOfNextFrame - physicsDeltaTime;
        postStep.m_endTime = world->m_timeOfNextFrame;
        postStep.m_deltaTime = postStep.m_endTime - postStep.m_startTime;
        postStep.m_invDeltaTime = hkInvDelta(postStep.m_deltaTime);

        hkWorldCallbackUtil::firePostSimulationCallback(world, postStep);
        hkMonitorEnd();
    }
    return (hkStepResult)0;
}

// ---------------------------------------------------------------------------------------------
// hkContinuousSimulation::recoverFromStepFailure (0x010f4850)
// ---------------------------------------------------------------------------------------------
// @ 0x010f4850
hkStepResult hkContinuousSimulation::recoverFromStepFailure(hkWorld* world, hkStepResult stepResult)
{
    if (stepResult == (hkStepResult)1)
    {
        return vslot2(world, 0, *(int*)((char*)this + 8));
    }

    hkStepInfo stepInfo;
    stepInfo.m_startTime = world->m_currentTime;
    stepInfo.m_endTime = world->m_timeOfNextPsi;
    stepInfo.m_deltaTime = stepInfo.m_endTime - stepInfo.m_startTime;
    stepInfo.m_invDeltaTime = hkInvDelta(stepInfo.m_deltaTime);

    for (int i = m_toiEvents.m_size - 1; i >= 0; i--)
    {
        hkToiEvent& e = m_toiEvents.m_data[i];
        hkContactPointRemovedEvent removed;
        removed.m_contactPointId = 0xffff;
        removed.m_contactPointMaterial = (hkContactPointMaterial*)((char*)&e + 0x10);
        removed.m_entityA = e.m_entities[0];
        removed.m_entityB = e.m_entities[1];
        removed.m_internalContactMgr = e.m_contactMgr;

        hkWorldCallbackUtil::fireContactPointRemoved(e.m_entities[0]->m_world, removed);
        if (e.m_entities[0]->m_hasContactPointRemovedCallback != 0)
            hkEntityCallbackUtil::fireContactPointRemovedInternal(e.m_entities[0], removed);
        if (e.m_entities[1]->m_hasContactPointRemovedCallback != 0)
            hkEntityCallbackUtil::fireContactPointRemovedInternal(e.m_entities[1], removed);
    }

    m_toiEvents.m_size = 0;
    world->updateCollisionFilterOnWorld(0, 1);

    if (g_hkMemoryInstance->m_memoryState == 1)
        return (hkStepResult)2;

    collide(world, stepInfo);

    if (g_hkMemoryInstance->m_memoryState == 1)
        return (hkStepResult)2;

    const int oldSimulationStep = m_simulationStep;
    m_simulationStep = 0;

    if (m_stepFlag == 2 && oldSimulationStep == 1)
    {
        if (world->m_worldPostSimulationListeners.m_size != 0)
        {
            hkMonitorStamp("TtPostSimulateCb");

            hkStepInfo postStep(world->m_timeOfNextFrame, world->m_timeOfNextFrame);
            hkWorldCallbackUtil::firePostSimulationCallback(world, postStep);
            hkMonitorEnd();
        }
        return (hkStepResult)0;
    }

    return vslot2(world, 0, *(int*)((char*)this + 8));
}

// ---------------------------------------------------------------------------------------------
// hk3AxisSweep::updateNodesAfterInsert (0x010f4ab0)
// ---------------------------------------------------------------------------------------------
static __forceinline BpInt hkShiftInsert(BpInt value, hkUint32 mn, hkUint32 mx)
{
    const hkUint32 v = value;
    return (BpInt)(v + ((mn - v) >> 31) + ((mx - v) >> 31));
}

// @ 0x010f4ab0
void hk3AxisSweep::updateNodesAfterInsert(hkBpNode* nodes, int numNodes, hkBpNode& newNode)
{
    const hkUint32 mnx = (hkUint16)(newNode.min_x - 1);
    const hkUint32 mxx = (hkUint16)(newNode.max_x - 2);
    const hkUint32 mny = (hkUint16)(newNode.min_y - 1);
    const hkUint32 mxy = (hkUint16)(newNode.max_y - 2);
    const hkUint32 mnz = (hkUint16)(newNode.min_z - 1);
    const hkUint32 mxz = (hkUint16)(newNode.max_z - 2);

    hkBpNode* end = nodes + numNodes;
    for (hkBpNode* n = nodes; n < end; n++)
    {
        n->min_x = hkShiftInsert(n->min_x, mnx, mxx);
        n->min_y = hkShiftInsert(n->min_y, mny, mxy);
        n->max_x = hkShiftInsert(n->max_x, mnx, mxx);
        n->max_y = hkShiftInsert(n->max_y, mny, mxy);
        n->min_z = hkShiftInsert(n->min_z, mnz, mxz);
        n->max_z = hkShiftInsert(n->max_z, mnz, mxz);
    }
}

// ---------------------------------------------------------------------------------------------
// hk3AxisSweep::updateNodesAfterDelete (0x010f4c60)
// ---------------------------------------------------------------------------------------------
static __forceinline BpInt hkShiftDelete(BpInt value, hkUint32 mn, hkUint32 mx)
{
    const hkUint32 v = value;
    return (BpInt)(v - ((mn - v) >> 31) - ((mx - v) >> 31));
}

// @ 0x010f4c60
void hk3AxisSweep::updateNodesAfterDelete(hkBpNode* nodes, int numNodes, hkBpNode& oldNode)
{
    const hkUint32 mnx = oldNode.min_x;
    const hkUint32 mxx = oldNode.max_x;
    const hkUint32 mny = oldNode.min_y;
    const hkUint32 mxy = oldNode.max_y;
    const hkUint32 mnz = oldNode.min_z;
    const hkUint32 mxz = oldNode.max_z;

    hkBpNode* end = nodes + numNodes;
    for (hkBpNode* n = nodes; n < end; n++)
    {
        n->min_x = hkShiftDelete(n->min_x, mnx, mxx);
        n->max_x = hkShiftDelete(n->max_x, mnx, mxx);
        n->min_y = hkShiftDelete(n->min_y, mny, mxy);
        n->max_y = hkShiftDelete(n->max_y, mny, mxy);
        n->min_z = hkShiftDelete(n->min_z, mnz, mxz);
        n->max_z = hkShiftDelete(n->max_z, mnz, mxz);
    }
}

// ---------------------------------------------------------------------------------------------
// monotone binary search over the x endpoints (0x010f4e10)
// ---------------------------------------------------------------------------------------------
// @ 0x010f4e10
void __cdecl FUN_010f4e10(unsigned short* begin, unsigned short* end, unsigned short value)
{
    unsigned short* p = begin;
    unsigned int diff = (unsigned int)((char*)end - (char*)p);
    while ((int)(diff & 0xfffffffc) > 0x40)
    {
        unsigned short* mid = p + ((int)diff >> 3) * 2;
        if (*mid < value)
        {
            p = mid;
        }
        else
        {
            end = mid;
        }
        diff = (unsigned int)((char*)end - (char*)p);
    }
    while (*p < value)
        p += 2;
}

// ---------------------------------------------------------------------------------------------
// hk3AxisSweep::shiftBroadPhase (0x010f4e70)
// ---------------------------------------------------------------------------------------------
// @ 0x010f4e70
void hk3AxisSweep::shiftBroadPhase(const hkVector4& delta, hkVector4& effectiveDelta,
                                   hkArray<hkBroadPhaseHandle*>& movedObjects)
{
    hkVector4 negDelta;
    negDelta.x = -delta.x;
    negDelta.y = -delta.y;
    negDelta.z = -delta.z;
    negDelta.w = -delta.w;

    hkVector4 shift;
    shiftBroadPhaseBase(negDelta, shift, movedObjects);

    m_offsetLow.x += shift.x;
    m_offsetLow.y += shift.y;
    m_offsetLow.z += shift.z;
    m_offsetLow.w += shift.w;

    m_offsetHigh.x = 1.0f / m_scale.x + m_offsetLow.x;
    m_offsetHigh.y = 1.0f / m_scale.y + m_offsetLow.y;
    m_offsetHigh.z = 1.0f / m_scale.z + m_offsetLow.z;
    m_offsetHigh.w = m_offsetLow.w;

    effectiveDelta.x = -shift.x;
    effectiveDelta.y = -shift.y;
    effectiveDelta.z = -shift.z;
    effectiveDelta.w = -shift.w;
}

// ---------------------------------------------------------------------------------------------
// hk3AxisSweep::hkBpAxis::mergeBatch (0x010f4f50)
// ---------------------------------------------------------------------------------------------
// @ 0x010f4f50
void hk3AxisSweep::hkBpAxis::mergeBatch(hkBpNode* nodes, int split, int numNew, int axis, hkBpEndPoint* out)
{
    for (int i = 0; i < split; i++)
        out[i] = m_endPoints.m_data[i];

    hkBpEndPoint* base = m_endPoints.m_data;
    hkBpEndPoint* b = out + 1;
    hkBpEndPoint* bEnd = out + split - 1;
    hkBpEndPoint* a = base + split;
    hkBpEndPoint* aEnd = base + split + numNew;
    hkBpEndPoint* o = base + 1;
    const int axis2 = axis * 2;

    while (b->m_value < a->m_value)
    {
        b++;
        o++;
    }

    if (b < bEnd)
    {
        for (; a < aEnd; a++)
        {
            while (b->m_value < a->m_value)
            {
                *o = *b;
                const int index = (int)(o - base);
                *(BpInt*)((char*)&nodes[o->m_nodeIndex] + s_memberOffsets[(o->m_value & 1) + axis2]) = BpInt(index);
                b++;
                o++;
                if (b >= bEnd)
                    goto copyA;
            }
            *o = *a;
            const int index = (int)(o - base);
            *(BpInt*)((char*)&nodes[o->m_nodeIndex] + s_memberOffsets[(o->m_value & 1) + axis2]) = BpInt(index);
            o++;
        }
    }
    else
    {
copyA:
        for (; a < aEnd; a++, o++)
        {
            *o = *a;
            const int index = (int)(o - base);
            *(BpInt*)((char*)&nodes[o->m_nodeIndex] + s_memberOffsets[(o->m_value & 1) + axis2]) = BpInt(index);
        }
    }

    if (b <= bEnd)
    {
        do
        {
            *o = *b;
            const int index = (int)(o - base);
            *(BpInt*)((char*)&nodes[o->m_nodeIndex] + s_memberOffsets[(o->m_value & 1) + axis2]) = BpInt(index);
            b++;
            o++;
        } while (b <= bEnd);
    }
}

// ---------------------------------------------------------------------------------------------
// hk3AxisSweep::hkBpAxis::remove (0x010f50f0)
// ---------------------------------------------------------------------------------------------
// @ 0x010f50f0
void hk3AxisSweep::hkBpAxis::remove(int minPosition, int maxPosition)
{
    hkBpEndPoint* p = m_endPoints.m_data + minPosition;
    hkBpEndPoint* end1 = m_endPoints.m_data + maxPosition - 1;
    while (p < end1)
    {
        *p = p[1];
        p++;
    }

    const int newSize = m_endPoints.m_size - 2;
    hkBpEndPoint* end2 = m_endPoints.m_data + newSize;
    m_endPoints.m_size = newSize;
    while (p < end2)
    {
        *p = p[2];
        p++;
    }
}

// ---------------------------------------------------------------------------------------------
// hk3AxisSweep::setBitsBasedOnXInterval (0x010f5150)
// ---------------------------------------------------------------------------------------------
static __forceinline void hkToggleBit(hkUint32* bitField, hkUint32 index)
{
    bitField[index >> 5] ^= 1u << (index & 0x1f);
}

// @ 0x010f5150
void hk3AxisSweep::FUN_010f5150(int numNodes, int xValue, const hkBpNode& queryNode,
                                int queryNodeIndex, hkUint32* bitField) const
{
    hkUint32* clear = bitField;
    for (int i = 0; i <= (numNodes >> 7); i++)
    {
        clear[0] = 0;
        clear[1] = 0;
        clear[2] = 0;
        clear[3] = 0;
        clear += 4;
    }

    hkBpEndPoint* p = m_axis[0].m_endPoints.m_data + 1;

    if (m_numMarkers != 0)
    {
        const int shift = 16 - m_ld2NumMarkers;
        const int markerIndex = xValue >> shift;
        if (markerIndex > 0)
        {
            char* marker = (char*)m_markers + (markerIndex - 1) * 0x10;
            BpInt markerNodeIndex = *(BpInt*)marker;
            hkToggleBit(bitField, markerNodeIndex);

            BpInt* overlaps = *(BpInt**)(marker + 4);
            int numOverlaps = *(int*)(marker + 8);
            for (int i = numOverlaps - 1; i >= 0; i--)
            {
                BpInt index = overlaps[i];
                if (index != queryNodeIndex)
                    hkToggleBit(bitField, index);
            }

            const hkBpNode& markerNode = m_nodes.m_data[markerNodeIndex];
            p = m_axis[0].m_endPoints.m_data + 1 + markerNode.min_x;
            hkBpEndPoint* markerEnd = m_axis[0].m_endPoints.m_data + markerNode.max_x;
            for (; p < markerEnd; p++)
            {
                if ((p->m_value & 1) == 0)
                {
                    const hkUint32 index = p->m_nodeIndex;
                    bitField[index >> 5] &= ~(1u << (index & 0x1f));
                }
            }
            p = m_axis[0].m_endPoints.m_data + 1 + markerNode.min_x;
        }
    }

    hkBpEndPoint* end1 = m_axis[0].m_endPoints.m_data + queryNode.min_x;
    for (; p < end1; p++)
        hkToggleBit(bitField, p->m_nodeIndex);

    p++;
    hkBpEndPoint* end2 = m_axis[0].m_endPoints.m_data + queryNode.max_x;
    for (; p < end2; p++)
    {
        if ((p->m_value & 1) == 0)
            hkToggleBit(bitField, p->m_nodeIndex);
    }
}

// ---------------------------------------------------------------------------------------------
// hk3AxisSweep::FUN_010f5310 / getAabbCacheSize
// ---------------------------------------------------------------------------------------------
// @ 0x010f5310
int hk3AxisSweep::FUN_010f5310() const
{
    return m_nodes.m_size + -1;
}

// @ 0x010f5320
int hk3AxisSweep::getAabbCacheSize() const
{
    return (m_nodes.m_size - m_numMarkers) * 0x18 + 0x24;
}
