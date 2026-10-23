// Havok 3.1.0 hkAgentNnMachine: agent-track storage + per-entry collision dispatch.
// 0x010FBD10 .. 0x010FC180.  Flags: /O2 /MD /Gy /TP /vc71  (Havok was built with VC .NET 2003 / cl 13.10)
//
//   010fbd10  hkAgentNnTrack_appendCopy       copy one entry into a track's last sector (allocate one if full)
//   010fbdb0  _hkAgentNnMachine_CreateAgent   fill in a fresh entry, link both collidables, run the create callback
//   010fbf80  _hkAgentNnMachine_DestroyAgent  run the destroy callback, unlink the entry from both collidables
//   010fc090  _hkAgentNnMachine_AppendTrack   drain one track into another, freeing the emptied sectors
//   010fc180  hkAgentNnMachine_processAgent   dispatch one entry by stream command (2 = agent2, 4 = agent3, 6 = object)
//
// Struct stubs carry members at the x86 offsets of the 32-bit binary (comments); the Havok headers are
// not available, so every object is modelled as raw fields.
#include "types.h"
#include <intrin.h>

typedef unsigned char  hkUchar;
typedef unsigned short hkUint16;
typedef unsigned int   hkUint32;

#define HK_REAL_MAX 3.40282e+38f      // 0x7f7fffee in this build (not FLT_MAX)

// ---- OS / TLS --------------------------------------------------------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);   // kernel32!TlsGetValue
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
#pragma intrinsic(__rdtsc)

extern unsigned long g_hkThreadMemoryTls;           // 0x016E4174
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016E42A4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016E42A8
extern const char    hkMonitorTimerEndTag[];        // 0x0149CC34 (end-of-timer monitor command)

// HK_TIMER_COMMAND(name): 12-byte monitor record (name, rdtsc, pad) while the stream still has room.
#define HK_TIMER_COMMAND(name) do { \
    void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
        hkUint32* c_ = (hkUint32*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_[0] = (hkUint32)(name); c_[1] = (hkUint32)__rdtsc(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 3); } } while (0)

// ---- memory ----------------------------------------------------------------------------------------------
class hkThreadMemory
{
public:
    void* allocateChunk(int nbytes, int cl);                 // 0x0107DAA0 (thiscall)
    void  deallocateChunk(void* p, int nbytes, int cl);      // 0x0107DB10 (thiscall)
};
static __forceinline hkThreadMemory* hkThreadMemoryInstance()
{
    return (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
}

extern "C" void hkArrayUtil_reserveMore(void* arrayBase, int elemSize);                    // 0x0107F530
extern "C" void hkArrayUtil_reduce(void* arrayBase, int elemSize, void* inplace, int cap); // 0x0107F5D0
extern "C" void hkString_memCpy(void* dst, const void* src, int nbytes);                   // 0x0107F440

template <typename T>
class hkArray
{
public:
    T*  m_data;              // +0x00
    int m_size;              // +0x04
    int m_capacityAndFlags;  // +0x08 (bit 31: memory not owned)
    int getCapacity() const { return m_capacityAndFlags & 0x3fffffff; }
    void insertAt(int index, const hkArray<T>& other);       // 0x010FBB80 (thiscall, ret 8)
};

// ---- math ------------------------------------------------------------------------------------------------
class __declspec(align(16)) hkVector4 { public: float x, y, z, w; };

class __declspec(align(16)) hkTransform
{
public:
    float col0[4]; float col1[4]; float col2[4]; float trans[4];
    void setMulInverseMul(const hkTransform& a, const hkTransform& b);   // 0x010810F0 (thiscall)
};

class hkSweptTransform
{
public:
    hkVector4 m_centerOfMass0;     // +0x00 (w = start time)
    hkVector4 m_centerOfMass1;     // +0x10 (w = inverse delta time)
    hkVector4 m_rotation0;         // +0x20
    hkVector4 m_rotation1;         // +0x30
    hkVector4 m_centerOfMassLocal; // +0x40
};

class hkMotionState
{
public:
    hkTransform      m_transform;       // +0x00
    hkSweptTransform m_sweptTransform;  // +0x40
    hkVector4        m_deltaAngle;      // +0x90 (w = max angular movement)
    float            m_objectRadius;    // +0xa0
};

namespace hkSweptTransformUtil
{
    void __cdecl lerp2(const hkSweptTransform& st, float t, hkTransform& out);   // 0x01209C50
}

// ---- collision types -------------------------------------------------------------------------------------
class hkCollidable;
class hkContactMgr;
class hkCollisionAgent;
struct hkAgentNnEntry;
struct hkProcessCollisionOutput;
struct hkAgent3ProcessInput;

struct hkAgentEntryPair                  // one live agent of a collidable
{
    hkAgentNnEntry* m_entry;             // +0x00
    hkCollidable*   m_other;             // +0x04 (the collidable on the far side of the pair)
};

class hkCdBody
{
public:
    const void*     m_shape;             // +0x00
    hkUint32        m_shapeKey;          // +0x04
    const void*     m_motion;            // +0x08 (hkMotionState*, whose first member is the transform)
    const hkCdBody* m_parent;            // +0x0c
};

class hkCollidable : public hkCdBody
{
public:
    char                    m_pad10[0x1a - 0x10];   // +0x10
    hkUint16                m_collidableType;       // +0x1a (index into the dispatcher's pair-type table)
    char                    m_pad1c[0x24 - 0x1c];   // +0x1c
    hkArray<hkAgentEntryPair> m_agents;             // +0x24 (one {entry, other} pair per live agent)
};

struct hkAgentNnEntry
{
    hkUchar       m_streamCommand;                 // +0x00
    hkUchar       m_agentType;                     // +0x01 (index into the dispatcher's agent-type table)
    hkUchar       m_numContactPoints;              // +0x02
    hkUchar       m_size;                          // +0x03 (track->m_agentSize, the sector stride)
    hkCollisionAgent* m_agent;                     // +0x04 (stream command 6)
    hkUchar       m_collisionQualityIndex;         // +0x08 (index into dispatcher->m_qualityInfo)
    hkUchar       m_pad09[3];                      // +0x09
    hkUint16      m_agentIndexOnCollidable[2];     // +0x0c (slot of this entry in each collidable's m_agents)
    hkContactMgr* m_contactMgr;                    // +0x10
    hkCollidable* m_collidable[2];                 // +0x14
    float         m_sepNormalTime;                 // +0x1c (time the cached separating normal is valid for)
    hkVector4     m_sepNormal;                     // +0x20 (w = distance)
    // +0x30: agent data
};

struct hkAgentNnTrack
{
    hkArray<hkAgentNnEntry*> m_sectors;            // +0x00 (inplace storage of 1 at +0x0c)
    hkAgentNnEntry*          m_inplaceSector;      // +0x0c (hkInplaceArrayZ<char*,1> storage)
    hkUint32                 m_bytesUsedInLastSector;  // +0x10
    hkUint16                 m_agentSize;          // +0x14 (bytes per entry)
    hkUint16                 m_sectorSize;         // +0x16 (sector capacity; also the "sector full" threshold)
};

extern "C" void hkAgentNnTrack_remove(hkAgentNnTrack* track, hkAgentNnEntry* entry);   // 0x010FBC50

// ---- collision input -------------------------------------------------------------------------------------
class hkContactMgr
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void processContact(const hkCdBody* a, const hkCdBody* b, const struct hkProcessCollisionInput* input,
                                hkProcessCollisionOutput* output);       // +0x14
};

class hkCollisionAgent
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void processCollision(const hkCdBody* a, const hkCdBody* b, const struct hkProcessCollisionInput* input,
                                  hkProcessCollisionOutput* output);     // +0x14
};

class hkStepInfo { public: float m_startTime, m_endTime, m_deltaTime, m_invDeltaTime; };

struct hkCollisionQualityInfo
{
    char pad[0x10];
    char m_useContinuousPhysics;                 // +0x10
    char pad2[0x3c - 0x11];                      // size 0x3c
};

struct hkProcessCollisionInput
{
    class hkCollisionDispatcher* m_dispatcher;   // +0x00
    void*                        m_filter;       // +0x04
    float                        m_tolerance;    // +0x08
    char                         m_createPredictiveAgents;   // +0x0c
    char                         pad0d[3];
    hkStepInfo                   m_stepInfo;     // +0x10
    void*                        m_config;       // +0x20
    void*                        m_dynamicsInfo; // +0x24
    hkCollisionQualityInfo*      m_collisionQualityInfo;     // +0x28 (set by CreateAgent)
};

struct hkAgent3ProcessInput                   // size 0x50
{
    const hkCdBody*                m_bodyA;          // +0x00
    const hkCdBody*                m_bodyB;          // +0x04
    const hkProcessCollisionInput* m_input;          // +0x08
    void*                          m_contactMgr;     // +0x0c (hkContactMgr*)
    hkTransform                    m_aTb;            // +0x10
};

typedef void (__cdecl* CreateAgentFn)(hkAgent3ProcessInput* in, hkAgentNnEntry* entry, void* agentData);
typedef void (__cdecl* DestroyAgentFn)(hkAgentNnEntry* entry, void* agentData, void* contactMgr);
typedef void (__cdecl* Func08Fn)(hkAgentNnEntry* entry, void* agentData, hkContactMgr* mgr);
typedef void (__cdecl* SepNormalFn)(const hkAgent3ProcessInput* in, void* agentData, hkVector4* out);
typedef void (__cdecl* ProcessFn)(const hkAgent3ProcessInput* in, hkAgentNnEntry* entry, void* agentData,
                                  hkVector4* sepNormal, hkProcessCollisionOutput* out);

struct hkAgent3Func                   // 0x34 bytes per agent type; the table starts at dispatcher + 0x1694
{
    CreateAgentFn  m_create;          // +0x00 (dispatcher + 0x1694)
    DestroyAgentFn m_destroy;         // +0x04 (dispatcher + 0x1698)
    Func08Fn       m_func08;          // +0x08 (dispatcher + 0x169c)
    char           pad0c[0x24 - 0x0c];
    SepNormalFn    m_sepNormal;       // +0x24 (dispatcher + 0x16b8)
    ProcessFn      m_process;         // +0x28 (dispatcher + 0x16bc)
    char           pad2c[0x34 - 0x2c];
};

class hkCollisionDispatcher
{
public:
    char         m_pad00[0x1694];                    // +0x0000
    hkAgent3Func m_agent3Func[1];                    // +0x1694 (stride 0x34; indexed by hkAgentNnEntry::m_agentType)
    // +0x19d4: 8x8 pair-type table -> agent-type id;  +0x1a14: hkCollisionQualityInfo[1] (stride 0x3c)
};

// Linear movement bound of the pair over the step (hkSweptTransformUtil::calcTimInfo).
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

// ==========================================================================================================
// hkAgentNnTrack_appendCopy (0x010FBD10)
// ==========================================================================================================
// @ 0x010fbd10 hkAgentNnTrack_appendCopy
extern "C" hkAgentNnEntry* hkAgentNnTrack_appendCopy(hkAgentNnTrack* track, const hkAgentNnEntry* entry)
{
    if (track->m_bytesUsedInLastSector == track->m_sectorSize)
    {
        hkThreadMemory* tm = hkThreadMemoryInstance();
        hkAgentNnEntry* sector = (hkAgentNnEntry*)tm->allocateChunk(track->m_sectorSize, 0x24);
        if (track->m_sectors.m_size == track->m_sectors.getCapacity())
            hkArrayUtil_reserveMore(&track->m_sectors, 4);
        track->m_sectors.m_data[track->m_sectors.m_size] = sector;
        ++track->m_sectors.m_size;
        track->m_bytesUsedInLastSector = 0;
    }

    hkAgentNnEntry* e = (hkAgentNnEntry*)((char*)track->m_sectors.m_data[track->m_sectors.m_size - 1]
                                          + track->m_bytesUsedInLastSector);
    track->m_bytesUsedInLastSector += track->m_agentSize;
    hkString_memCpy(e, entry, track->m_agentSize);

    const hkUint16 index0 = e->m_agentIndexOnCollidable[0];
    const hkUint16 index1 = e->m_agentIndexOnCollidable[1];
    e->m_collidable[0]->m_agents.m_data[index0].m_entry = e;
    e->m_collidable[1]->m_agents.m_data[index1].m_entry = e;
    return e;
}

// ==========================================================================================================
// _hkAgentNnMachine_CreateAgent (0x010FBDB0)
// ==========================================================================================================
// @ 0x010fbdb0 _hkAgentNnMachine_CreateAgent
extern "C" hkAgentNnEntry* _hkAgentNnMachine_CreateAgent(hkAgentNnTrack* track, hkCollidable* collA,
                                                         hkCollidable* collB, int agentType,
                                                         hkProcessCollisionInput* input, hkContactMgr* mgr)
{
    hkCollisionDispatcher* dispatcher = input->m_dispatcher;

    // hkAgentNnTrack::allocateEntry() inlined (same body as hkAgentNnTrack_appendCopy, without the copy)
    if (track->m_bytesUsedInLastSector == track->m_sectorSize)
    {
        hkThreadMemory* tm = hkThreadMemoryInstance();
        hkAgentNnEntry* sector = (hkAgentNnEntry*)tm->allocateChunk(track->m_sectorSize, 0x24);
        if (track->m_sectors.m_size == track->m_sectors.getCapacity())
            hkArrayUtil_reserveMore(&track->m_sectors, 4);
        track->m_sectors.m_data[track->m_sectors.m_size] = sector;
        ++track->m_sectors.m_size;
        track->m_bytesUsedInLastSector = 0;
    }
    hkAgentNnEntry* entry = (hkAgentNnEntry*)((char*)track->m_sectors.m_data[track->m_sectors.m_size - 1]
                                              + track->m_bytesUsedInLastSector);
    track->m_bytesUsedInLastSector += track->m_agentSize;

    entry->m_contactMgr = mgr;
    entry->m_collidable[0] = collA;
    entry->m_collidable[1] = collB;

    entry->m_agentIndexOnCollidable[0] = (hkUint16)collA->m_agents.m_size;
    entry->m_agentIndexOnCollidable[1] = (hkUint16)collB->m_agents.m_size;

    if (collA->m_agents.m_size == collA->m_agents.getCapacity())
        hkArrayUtil_reserveMore(&collA->m_agents, 8);
    hkAgentEntryPair* pa = &collA->m_agents.m_data[collA->m_agents.m_size++];
    if (collB->m_agents.m_size == collB->m_agents.getCapacity())
        hkArrayUtil_reserveMore(&collB->m_agents, 8);
    hkAgentEntryPair* pb = &collB->m_agents.m_data[collB->m_agents.m_size++];
    pa->m_entry = entry;
    pb->m_entry = entry;
    pa->m_other = collB;
    pb->m_other = collA;

    hkAgent3ProcessInput in;
    in.m_bodyA = collA;
    in.m_bodyB = collB;
    in.m_input = input;
    in.m_contactMgr = entry->m_contactMgr;
    in.m_aTb.setMulInverseMul(((const hkMotionState*)collA->m_motion)->m_transform,
                              ((const hkMotionState*)collB->m_motion)->m_transform);

    // The agent type of this pair comes from the dispatcher's collidable-type table; its
    // hkCollisionQualityInfo is published back on the input for the process step.
    const char qualityIndex =
        *(char*)((char*)dispatcher + 0x19d4 + collA->m_collidableType * 8 + collB->m_collidableType);
    entry->m_collisionQualityIndex = qualityIndex;
    input->m_collisionQualityInfo = (hkCollisionQualityInfo*)((char*)dispatcher + 0x1a14 + qualityIndex * 0x3c);

    entry->m_agentType = (hkUchar)agentType;
    void* agentData;
    if (dispatcher->m_agent3Func[agentType].m_sepNormal != 0)
    {
        entry->m_streamCommand = 4;                              // agent3: TIM-cached separating normal
        entry->m_sepNormalTime = -1.0f;
        ((hkUint32*)&entry->m_sepNormal)[0] = 0;
        ((hkUint32*)&entry->m_sepNormal)[1] = 0;
        ((hkUint32*)&entry->m_sepNormal)[2] = 0;
        ((hkUint32*)&entry->m_sepNormal)[3] = 0;
        agentData = (char*)entry + 0x30;
    }
    else
    {
        entry->m_streamCommand = 2;                              // agent2: no persistent separating normal
        agentData = (char*)entry + 0x20;
    }
    dispatcher->m_agent3Func[agentType].m_create(&in, entry, agentData);

    entry->m_size = (hkUchar)track->m_agentSize;
    return entry;
}

// ==========================================================================================================
// _hkAgentNnMachine_DestroyAgent (0x010FBF80)
// ==========================================================================================================
// @ 0x010fbf80 _hkAgentNnMachine_DestroyAgent
extern "C" void _hkAgentNnMachine_DestroyAgent(hkAgentNnTrack* track, hkAgentNnEntry* entry,
                                               hkCollisionDispatcher* dispatcher)
{
    const hkUchar cmd = entry->m_streamCommand;
    switch (cmd)
    {
    case 2:
    case 6:
        dispatcher->m_agent3Func[entry->m_agentType].m_destroy(entry, (char*)entry + 0x20, entry->m_contactMgr);
        break;
    case 4:
        dispatcher->m_agent3Func[entry->m_agentType].m_destroy(entry, (char*)entry + 0x30, entry->m_contactMgr);
        break;
    }

    // unlink the entry from both collidables (compacting each m_agents array)
    hkUint16*      index      = entry->m_agentIndexOnCollidable;
    hkCollidable** collidable = entry->m_collidable;
    int            n          = 2;
    do
    {
        hkCollidable* c = *collidable;
        const int slot = *index;
        hkAgentEntryPair* pairs = c->m_agents.m_data;
        const int last = c->m_agents.m_size - 1;
        c->m_agents.m_size = last;
        pairs[slot] = pairs[last];
        if (slot < c->m_agents.m_size)
        {
            hkAgentNnEntry* moved = pairs[slot].m_entry;
            moved->m_agentIndexOnCollidable[moved->m_collidable[0] != c ? 1 : 0] = (hkUint16)slot;
        }
        if (c->m_agents.m_size * 2 + 8 <= c->m_agents.getCapacity())
            hkArrayUtil_reduce(&c->m_agents, 8, 0, 0);
        ++index;
        ++collidable;
    } while (--n);

    hkAgentNnTrack_remove(track, entry);
}

// ==========================================================================================================
// _hkAgentNnMachine_AppendTrack (0x010FC090)
// ==========================================================================================================
// @ 0x010fc090 _hkAgentNnMachine_AppendTrack
extern "C" void _hkAgentNnMachine_AppendTrack(hkAgentNnTrack* dst, hkAgentNnTrack* src)
{
    if (dst->m_bytesUsedInLastSector != dst->m_sectorSize)
    {
        do
        {
            if (src->m_sectors.m_size == 0)
                break;

            // copy the source track's last live entry over, then drop it
            hkAgentNnEntry* last = (hkAgentNnEntry*)((char*)src->m_sectors.m_data[src->m_sectors.m_size - 1]
                                                     + src->m_bytesUsedInLastSector - src->m_agentSize);
            hkAgentNnTrack_appendCopy(dst, last);

            const int size = src->m_sectors.m_size;
            src->m_bytesUsedInLastSector -= src->m_agentSize;
            if (src->m_bytesUsedInLastSector == 0)
            {
                // the source sector is empty now: pop and free it
                hkAgentNnEntry* sector = src->m_sectors.m_data[size - 1];
                src->m_sectors.m_size = size - 1;
                if (src->m_sectors.m_capacityAndFlags >= 0
                    && (size < 1 || size * 2 < src->m_sectors.getCapacity()))
                    hkArrayUtil_reduce(&src->m_sectors, 4, &src->m_inplaceSector, 1);
                hkThreadMemoryInstance()->deallocateChunk(sector, src->m_sectorSize, 0x24);
                src->m_bytesUsedInLastSector = src->m_sectorSize;
            }
        } while (dst->m_bytesUsedInLastSector != dst->m_sectorSize);
    }

    if (src->m_sectors.m_size != 0)
    {
        // whatever is left (whole, non-empty sectors) moves over wholesale
        dst->m_sectors.insertAt(dst->m_sectors.m_size, src->m_sectors);
        dst->m_bytesUsedInLastSector = src->m_bytesUsedInLastSector;
        src->m_sectors.m_size = 0;
        src->m_bytesUsedInLastSector = dst->m_sectorSize;
    }
}

// ==========================================================================================================
// hkAgentNnMachine_processAgent (0x010FC180)
// ==========================================================================================================
// @ 0x010fc180 hkAgentNnMachine_processAgent
extern "C" void hkAgentNnMachine_processAgent(hkAgentNnEntry* entry, hkProcessCollisionInput* input,
                                              hkProcessCollisionOutput* output)
{
    hkCollisionDispatcher* dispatcher = input->m_dispatcher;
    hkAgent3ProcessInput in;
    float                distAtT1;                   // in + 0x50
    hkVector4            linearTimInfo;              // in + 0x60

    if (entry->m_streamCommand == 2)
    {
        hkCollidable* a = entry->m_collidable[0];
        hkCollidable* b = entry->m_collidable[1];
        const hkMotionState* ma = (const hkMotionState*)a->m_motion;
        const hkMotionState* mb = (const hkMotionState*)b->m_motion;
        in.m_bodyA = a;
        in.m_bodyB = b;
        in.m_input = input;
        in.m_contactMgr = entry->m_contactMgr;
        calcTimInfo(ma, mb, input->m_stepInfo, linearTimInfo);
        in.m_aTb.setMulInverseMul(ma->m_transform, mb->m_transform);
        dispatcher->m_agent3Func[entry->m_agentType].m_process(&in, entry, (char*)entry + 0x20, 0, output);
        return;
    }

    if (entry->m_streamCommand == 6)
    {
        entry->m_agent->processCollision(entry->m_collidable[0], entry->m_collidable[1], input, output);
        return;
    }

    if (entry->m_streamCommand != 4)
        return;

    hkCollidable* a = entry->m_collidable[0];
    hkCollidable* b = entry->m_collidable[1];
    const hkMotionState* ma = (const hkMotionState*)a->m_motion;
    const hkMotionState* mb = (const hkMotionState*)b->m_motion;
    in.m_bodyA = a;
    in.m_bodyB = b;
    in.m_input = input;
    in.m_contactMgr = entry->m_contactMgr;
    calcTimInfo(ma, mb, input->m_stepInfo, linearTimInfo);

    float dist;
    if (entry->m_sepNormalTime != input->m_stepInfo.m_startTime)
    {
        if (!input->m_collisionQualityInfo->m_useContinuousPhysics)
        {
            // no continuous physics: invalidate the cached separating plane
            entry->m_sepNormalTime = input->m_stepInfo.m_endTime;
            ((hkUint32*)&entry->m_sepNormal)[0] = 0;
            ((hkUint32*)&entry->m_sepNormal)[1] = 0;
            ((hkUint32*)&entry->m_sepNormal)[2] = 0;
            ((hkUint32*)&entry->m_sepNormal)[3] = 0xff7fffee;   // -HK_REAL_MAX
            dist = -HK_REAL_MAX;
            goto processAgent3;
        }

        // recompute the separating normal at the start of the step
        HK_TIMER_COMMAND("TtrecalcT0");
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
        dispatcher->m_agent3Func[entry->m_agentType].m_sepNormal(&in2, (char*)entry + 0x30, &entry->m_sepNormal);
        HK_TIMER_COMMAND(hkMonitorTimerEndTag);
    }

    entry->m_sepNormalTime = input->m_stepInfo.m_endTime;
    dist = entry->m_sepNormal.w
           - (((linearTimInfo.z * entry->m_sepNormal.z + linearTimInfo.y * entry->m_sepNormal.y)
               + linearTimInfo.x * entry->m_sepNormal.x) + linearTimInfo.w);
    if (input->m_tolerance <= dist)
    {
        // still separated by more than the tolerance: just remember the new distance
        entry->m_sepNormal.w = dist;
        if (entry->m_numContactPoints)
            dispatcher->m_agent3Func[entry->m_agentType].m_func08(entry, (char*)entry + 0x30, entry->m_contactMgr);
        return;
    }

processAgent3:
    distAtT1 = dist;
    in.m_aTb.setMulInverseMul(ma->m_transform, mb->m_transform);
    dispatcher->m_agent3Func[entry->m_agentType].m_process(&in, entry, (char*)entry + 0x30,
                                                            &entry->m_sepNormal, output);
}
