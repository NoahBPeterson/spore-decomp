// Havok 3.1.0: hkAgentNnMachine_ProcessTrack @ 0x010FC700  (/O2 /MD /Gy /TP /GS-, x87)
//
// Walks every sector of an hkAgentNnTrack and dispatches each agent entry by stream command:
//   2 = agent2 (no persistent separating normal)           -> agent3 table process(in, entry, entry+0x20, 0, out)
//   4 = agent3 (TIM-cached separating normal @ entry+0x20) -> recompute the TIM / separating plane when the
//        cached time differs from the step start, skip the full process() while the plane is still
//        farther away than the tolerance, otherwise process(in, entry, entry+0x30, entry+0x20, out)
//   6 = hkCollisionAgent object (virtual process, slot 5)
// After each entry the OOM watchdog runs; contacts produced are passed to the contact manager.
#include "types.h"
#include <intrin.h>

typedef unsigned char  hkUchar;
typedef unsigned short hkUint16;
typedef unsigned int   hkUint32;

#define HK_REAL_MAX 3.40282e+38f      // 0x7f7fffee in this build (not FLT_MAX)

template <typename T> struct hkArray { T* m_data; int m_size; int m_capacityAndFlags; };

class __declspec(align(16)) hkVector4 { public: float x, y, z, w; };
struct hkTransform
{
    float col0[4]; float col1[4]; float col2[4]; float trans[4];
    void setMulInverseMul(const hkTransform& a, const hkTransform& b);     // 0x010810f0 (thiscall)
};

struct hkSweptTransform
{
    hkVector4 m_centerOfMass0;     // +0x00 (w = start time)
    hkVector4 m_centerOfMass1;     // +0x10 (w = inverse delta time)
    hkVector4 m_rotation0;         // +0x20
    hkVector4 m_rotation1;         // +0x30
    hkVector4 m_centerOfMassLocal; // +0x40
};
struct hkMotionState
{
    hkTransform      m_transform;       // +0x00
    hkSweptTransform m_sweptTransform;  // +0x40
    hkVector4        m_deltaAngle;      // +0x90 (w = max angular movement)
    float            m_objectRadius;    // +0xa0
};
namespace hkSweptTransformUtil
{
    void __cdecl lerp2(const hkSweptTransform& st, float t, hkTransform& out);   // 0x01209c50
}

// ---- monitor stream (TLS) ---------------------------------------------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
extern "C" unsigned __int64 __rdtsc();
#pragma intrinsic(__rdtsc)
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8

#define HK_TIMER_CMD(name) do { \
    void* end_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end_) { \
        hkUint32* c_ = (hkUint32*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_[0] = (hkUint32)(name); \
        c_[1] = (hkUint32)__rdtsc(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 3); } } while (0)

// HK_MONITOR_ADD_VALUE(name, float): 8-byte record
static __forceinline void hkMonitorAddValue(const char* name, float value)
{
    void* end = TlsGetValue(g_hkMonitorStreamEndTls);
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end)
    {
        hkUint32* c = (hkUint32*)TlsGetValue(g_hkMonitorStreamCurrentTls);
        c[0] = (hkUint32)name;
        *(float*)&c[1] = value;
        TlsSetValue(g_hkMonitorStreamCurrentTls, c + 2);
    }
}

// ---- memory watchdog --------------------------------------------------------------------------------------
struct hkMemory
{
    void** vftable;                    // +0x00
    int m_memoryState;                 // +0x04 (1 = out of memory)
    int m_criticalMemoryLimit;         // +0x08
    int pad0c[2];                      // +0x0c
    int m_sysAllocsSize;               // +0x14
    int pad18[4];                      // +0x18
    int m_pageMemoryUsed;              // +0x28
};
extern hkMemory* g_hkMemoryInstance;   // 0x016e4178

// ---- collision types --------------------------------------------------------------------------------------
struct hkStepInfo { float m_startTime, m_endTime, m_deltaTime, m_invDeltaTime; };
struct hkCollisionQualityInfo { char pad[0x10]; char m_useContinuousPhysics; char pad2[0x3c - 0x11]; };

typedef void (__cdecl* Func08Fn)(struct hkAgentNnEntry* entry, void* agentData, struct hkContactMgr* mgr);
typedef void (__cdecl* SepNormalFn)(const struct hkAgent3ProcessInput* in, void* agentData, hkVector4* out);
typedef void (__cdecl* ProcessFn)(const struct hkAgent3ProcessInput* in, struct hkAgentNnEntry* entry,
                                  void* agentData, hkVector4* sepNormal, struct hkProcessCollisionOutput* out);
struct hkAgent3Func                    // 0x34 bytes per agent type, table at dispatcher + 0x1694
{
    char pad00[8];
    void (__cdecl* m_func08)(struct hkAgentNnEntry* entry, void* agentData, struct hkContactMgr* mgr);   // +0x08
    char pad0c[0x24 - 0x0c];
    void (__cdecl* m_sepNormal)(const struct hkAgent3ProcessInput* in, void* agentData, hkVector4* out);  // +0x24
    void (__cdecl* m_process)(const struct hkAgent3ProcessInput* in, struct hkAgentNnEntry* entry,
                              void* agentData, hkVector4* sepNormal, struct hkProcessCollisionOutput* out); // +0x28
};
struct hkCollisionDispatcher { char pad[0x1694]; hkAgent3Func m_agent3Func[1]; };

struct hkProcessCollisionInput
{
    hkCollisionDispatcher*   m_dispatcher;            // +0x00
    void*                    m_filter;                // +0x04
    float                    m_tolerance;             // +0x08
    char                     m_createPredictiveAgents;// +0x0c
    char                     pad0d[3];
    hkStepInfo               m_stepInfo;              // +0x10
    void*                    m_config;                // +0x20
    void*                    m_dynamicsInfo;          // +0x24
    hkCollisionQualityInfo*  m_collisionQualityInfo;  // +0x28
};

struct hkCdBody
{
    const void*        m_shape;     // +0x0
    hkUint32           m_shapeKey;  // +0x4
    const hkTransform* m_motion;    // +0x8 (hkMotionState*, whose first member is the transform)
    const hkCdBody*    m_parent;    // +0xc
};
struct hkCollidable : public hkCdBody { };

struct hkProcessCdPoint { hkUint32 m_data[12]; };
struct hkProcessCollisionOutput
{
    hkProcessCdPoint* m_firstFreeContactPoint;     // +0x0000
    hkUint32          m_pad[3];
    hkVector4         m_toiContactPoint[2];        // +0x0010
    hkProcessCdPoint  m_contactPoints[256];        // +0x0030
    float             m_toiSeperatingVelocity;     // +0x3030
    float             m_toi;                       // +0x3034
    hkUint32          m_toiMaterial[2];            // +0x3038
    void*             m_potentialContacts;         // +0x3040
    hkProcessCollisionOutput() { *(hkUint32*)&m_toi = 0x7f7fffee; }
};

struct hkContactMgr
{
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void processContact(const hkCdBody* a, const hkCdBody* b, const hkProcessCollisionInput* input,
                                hkProcessCollisionOutput* output);       // +0x14
};

struct hkCollisionAgent
{
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void processCollision(const hkCdBody* a, const hkCdBody* b, const hkProcessCollisionInput* input,
                                  hkProcessCollisionOutput* output);     // +0x14
};

struct hkAgentNnEntry
{
    hkUchar m_streamCommand, m_agentType, m_numContactPoints, m_size;   // +0x00
    hkCollisionAgent* m_agent;       // +0x04 (stream command 6)
    hkUint32 pad08[2];
    hkContactMgr* m_contactMgr;      // +0x10
    hkCollidable* m_collidable[2];   // +0x14
    float m_sepNormalTime;           // +0x1c (time the cached separating normal is valid for)
    hkVector4 m_sepNormal;           // +0x20 (w = distance)
    // +0x30: agent data
};

struct hkAgent3ProcessInput
{
    const hkCdBody*                m_bodyA;          // +0x00
    const hkCdBody*                m_bodyB;          // +0x04
    const hkProcessCollisionInput* m_input;          // +0x08
    hkContactMgr*                  m_contactMgr;     // +0x0c
    hkTransform                    m_aTb;            // +0x10
    float                          m_distAtT1;       // +0x50
    hkVector4                      m_linearTimInfo;  // +0x60
};

struct hkAgentNnTrack
{
    hkArray<hkAgentNnEntry*> m_sectors;     // +0x00
    hkUint32 m_pad0c;                       // +0x0c
    hkUint32 m_bytesUsedInLastSector;       // +0x10
    hkUint16 m_pad14;                       // +0x14
    hkUint16 m_bytesUsedInFullSector;       // +0x16
};
typedef char hkTrackOff_[(sizeof(hkAgentNnTrack) == 0x18) ? 1 : -1];

// Linear and angular movement bound of the pair over the step (hkSweptTransformUtil::calcTimInfo)
static __forceinline void calcTimInfo(const hkMotionState* ma, const hkMotionState* mb, const hkStepInfo& step,
                                      hkVector4& out)
{
    const float dt = step.m_deltaTime;
    hkVector4 dA, dB;
    dA.x = ma->m_sweptTransform.m_centerOfMass0.x - ma->m_sweptTransform.m_centerOfMass1.x;
    dA.y = ma->m_sweptTransform.m_centerOfMass0.y - ma->m_sweptTransform.m_centerOfMass1.y;
    dA.z = ma->m_sweptTransform.m_centerOfMass0.z - ma->m_sweptTransform.m_centerOfMass1.z;
    dA.w = ma->m_sweptTransform.m_centerOfMass0.w - ma->m_sweptTransform.m_centerOfMass1.w;
    dB.x = mb->m_sweptTransform.m_centerOfMass1.x - mb->m_sweptTransform.m_centerOfMass0.x;
    dB.y = mb->m_sweptTransform.m_centerOfMass1.y - mb->m_sweptTransform.m_centerOfMass0.y;
    dB.z = mb->m_sweptTransform.m_centerOfMass1.z - mb->m_sweptTransform.m_centerOfMass0.z;
    dB.w = mb->m_sweptTransform.m_centerOfMass1.w - mb->m_sweptTransform.m_centerOfMass0.w;
    const float fA = dt * ma->m_sweptTransform.m_centerOfMass1.w;
    const float fB = dt * mb->m_sweptTransform.m_centerOfMass1.w;
    out.x = dB.x * fB + dA.x * fA;
    out.y = dB.y * fB + dA.y * fA;
    out.z = dB.z * fB + dA.z * fA;
    out.w = (mb->m_objectRadius * mb->m_deltaAngle.w) * fB + (ma->m_objectRadius * ma->m_deltaAngle.w) * fA;
}

// @ 0x010FC700
void __cdecl hkAgentNnMachine_ProcessTrack(hkAgentNnTrack* track, hkProcessCollisionInput* input)
{
    hkProcessCollisionOutput output;
    int numUpdated = 0;

    for (int s = 0; s < track->m_sectors.m_size; )
    {
        hkAgentNnEntry* entry = track->m_sectors.m_data[s];
        ++s;
        const int bytes = (s == track->m_sectors.m_size) ? (int)track->m_bytesUsedInLastSector
                                                         : (int)track->m_bytesUsedInFullSector;
        hkAgentNnEntry* const sectorEnd = (hkAgentNnEntry*)((char*)entry + bytes);

        for (; entry < sectorEnd; entry = (hkAgentNnEntry*)((char*)entry + entry->m_size))
        {
            hkCollidable* a = entry->m_collidable[0];
            hkCollidable* b = entry->m_collidable[1];
            output.m_firstFreeContactPoint = output.m_contactPoints;
            *(hkUint32*)&output.m_toi = 0x7f7fffee;     // HK_REAL_MAX stored as an immediate
            output.m_potentialContacts = 0;

            const hkUchar cmd = entry->m_streamCommand;
            if (cmd == 2)
            {
                hkAgent3ProcessInput in;
                in.m_bodyA = entry->m_collidable[0];
                in.m_bodyB = entry->m_collidable[1];
                in.m_contactMgr = entry->m_contactMgr;
                in.m_input = input;
                const hkMotionState* ma = (const hkMotionState*)entry->m_collidable[0]->m_motion;
                const hkMotionState* mb = (const hkMotionState*)entry->m_collidable[1]->m_motion;
                calcTimInfo(ma, mb, input->m_stepInfo, in.m_linearTimInfo);
                in.m_aTb.setMulInverseMul(ma->m_transform, mb->m_transform);
                (*(ProcessFn*)((char*)input->m_dispatcher + entry->m_agentType * 0x34 + 0x16bc))(&in, entry, (char*)entry + 0x20, 0, &output);
            }
            else if (cmd == 4)
            {
                hkAgent3ProcessInput in;
                const hkMotionState* ma = (const hkMotionState*)a->m_motion;
                const hkMotionState* mb = (const hkMotionState*)b->m_motion;
                in.m_bodyA = a;
                in.m_bodyB = b;
                in.m_contactMgr = entry->m_contactMgr;
                in.m_input = input;
                calcTimInfo(ma, mb, input->m_stepInfo, in.m_linearTimInfo);

                float dist;
                if (entry->m_sepNormalTime != input->m_stepInfo.m_startTime)
                {
                    if (!input->m_collisionQualityInfo->m_useContinuousPhysics)
                    {
                        // no continuous physics: invalidate the cached separating plane
                        entry->m_sepNormalTime = input->m_stepInfo.m_endTime;
                        ((hkUint32*)&entry->m_sepNormal)[3] = 0;
                        ((hkUint32*)&entry->m_sepNormal)[2] = 0;
                        ((hkUint32*)&entry->m_sepNormal)[1] = 0;
                        ((hkUint32*)&entry->m_sepNormal)[0] = 0;
                        *(hkUint32*)&entry->m_sepNormal.w = 0xff7fffee;
                        dist = -HK_REAL_MAX;
                        goto processAgent3;
                    }
                    // recompute the separating normal at the start of the step
                    HK_TIMER_CMD("TtrecalcT0");
                    hkTransform xformA, xformB;
                    hkSweptTransformUtil::lerp2(ma->m_sweptTransform, input->m_stepInfo.m_startTime, xformA);
                    hkSweptTransformUtil::lerp2(mb->m_sweptTransform, input->m_stepInfo.m_startTime, xformB);
                    hkCdBody cdA, cdB;
                    cdA.m_shape = a->m_shape; cdA.m_shapeKey = a->m_shapeKey; cdA.m_motion = &xformA; cdA.m_parent = a;
                    cdB.m_shape = b->m_shape; cdB.m_shapeKey = b->m_shapeKey; cdB.m_motion = &xformB; cdB.m_parent = b;
                    hkAgent3ProcessInput in2;
                    in2.m_bodyA = &cdA;
                    in2.m_bodyB = &cdB;
                    in2.m_input = input;
                    in2.m_contactMgr = entry->m_contactMgr;
                    in2.m_aTb.setMulInverseMul(xformA, xformB);
                    (*(SepNormalFn*)((char*)input->m_dispatcher + entry->m_agentType * 0x34 + 0x16b8))(&in2, (char*)entry + 0x30, &entry->m_sepNormal);
                    HK_TIMER_CMD("Et");
                }
                entry->m_sepNormalTime = input->m_stepInfo.m_endTime;
                dist = entry->m_sepNormal.w
                       - (((in.m_linearTimInfo.z * entry->m_sepNormal.z + in.m_linearTimInfo.y * entry->m_sepNormal.y)
                           + in.m_linearTimInfo.x * entry->m_sepNormal.x) + in.m_linearTimInfo.w);
                if (input->m_tolerance <= dist)
                {
                    // still separated by more than the tolerance: just remember the new distance
                    entry->m_sepNormal.w = dist;
                    if (entry->m_numContactPoints)
                        (*(Func08Fn*)((char*)input->m_dispatcher + entry->m_agentType * 0x34 + 0x169c))(entry, (char*)entry + 0x30, entry->m_contactMgr);
                    ++numUpdated;
                    goto nextEntry;
                }
            processAgent3:
                in.m_distAtT1 = dist;
                in.m_aTb.setMulInverseMul(ma->m_transform, mb->m_transform);
                (*(ProcessFn*)((char*)input->m_dispatcher + entry->m_agentType * 0x34 + 0x16bc))(&in, entry, (char*)entry + 0x30, &entry->m_sepNormal, &output);
            }
            else if (cmd == 6)
            {
                entry->m_agent->processCollision(entry->m_collidable[0], entry->m_collidable[1], input, &output);
            }

        nextEntry:
            {
                hkMemory* mem = g_hkMemoryInstance;
                int used = mem->m_pageMemoryUsed + mem->m_sysAllocsSize;
                if (mem->m_criticalMemoryLimit <= used || (mem->m_criticalMemoryLimit - used) == 0)
                    mem->m_memoryState = 1;
            }
            if (g_hkMemoryInstance->m_memoryState == 1)
                return;
            if (output.m_firstFreeContactPoint != output.m_contactPoints)
                entry->m_contactMgr->processContact(a, b, input, &output);
        }
    }
    hkMonitorAddValue("MinumTim", (float)numUpdated);
}
