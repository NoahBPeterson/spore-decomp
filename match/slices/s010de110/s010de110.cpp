// Slice s010de110: hkConvexListAgent::processCollision (Havok 3.1.0, hkConvexListAgent.cpp).
// Built /vc71 /O2 /MD /Gy /TP (x87).  A convex-list agent runs in one of two modes:
//   stream mode (m_inGskMode == 0): the list's children are processed one by one by an agent track
//       (hkAgent1nMachine); every 25 steps a GSK query against the list's convex hull checks whether
//       the hull is far enough away to switch to
//   gsk mode (m_inGskMode == 1): the list is treated as ONE convex hull (hkConvexListConvexShape) and
//       processed by the predictive GSK agent; when the hull is penetrated it switches back.
#include "types.h"
#include <math.h>
#pragma intrinsic(sqrt)

typedef float hkReal;
typedef float hkTime;
typedef uint16_t hkUint16;
typedef uint32_t hkShapeKey;
inline void* operator new(unsigned, void* p) { return p; }
inline void operator delete(void*, void*) {}

class __declspec(align(16)) hkVector4 { public: float x, y, z, w; };
struct __declspec(align(16)) hkTransform
{
    hkVector4 m_col0, m_col1, m_col2, m_translation;
    void setMulInverseMul(const hkTransform& a, const hkTransform& b);   // 0x010810f0 (thiscall)
};

// ---- Havok monitor-stream timer commands (TLS) ----------------------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern unsigned long g_hkThreadMemoryTls;           // 0x016e4174
extern const char hkTimerEndListTag[];              // 0x0143cd94 ("lt")

struct hkMonitorCommand  { const char* m_commandAndMonitor; uint32_t m_time0; uint32_t m_pad; };   // 12 bytes
struct hkMonitorCommand2 { hkMonitorCommand m_first; const char* m_secondCommand; };               // 16 bytes

#define HK_READ_TICKS(dst) { uint32_t ticks_; __asm { rdtsc } __asm { mov ticks_, eax } (dst) = ticks_; }
#define HK_TIMER_CMD(name) do { \
    void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
        hkMonitorCommand* c_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_commandAndMonitor = name; \
        HK_READ_TICKS(c_->m_time0); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_BEGIN_LIST(a, b) do { \
    void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
        hkMonitorCommand2* c_ = (hkMonitorCommand2*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_->m_first.m_commandAndMonitor = "Lt" a; c_->m_secondCommand = b; \
        HK_READ_TICKS(c_->m_first.m_time0); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_SPLIT_LIST(name)  HK_TIMER_CMD("St" name)
#define HK_TIMER_END_LIST()        HK_TIMER_CMD(hkTimerEndListTag)

// ---- Havok thread memory stack (hkAllocateStack / hkDeallocateStack) ---------------------------------------
struct hkThreadMemoryRaw
{
    virtual void vslot0(); virtual void vslot1(); virtual void vslot2();
    virtual void* onStackOverflow(int nbytes);          // +0x0c
    virtual void onStackUnderflow(void* p);              // +0x10
    uint32_t pad04[7];
    char* m_stackCurrent;                                // +0x20
    char* m_stackPrev;                                   // +0x24
    char* m_stackBase;                                   // +0x28
    char* m_stackEnd;                                    // +0x2c
    static __forceinline hkThreadMemoryRaw& getInstance() { return *(hkThreadMemoryRaw*)TlsGetValue(g_hkThreadMemoryTls); }
};
template <typename T> __forceinline T* hkAllocateStack(int n)
{
    hkThreadMemoryRaw& tm = hkThreadMemoryRaw::getInstance();
    int size = (n * (int)sizeof(T) + 0x10) & ~0xf;
    char* cur = tm.m_stackCurrent;
    char* next = cur + size;
    if ((uint32_t)next <= (uint32_t)tm.m_stackEnd)
    {
        tm.m_stackCurrent = next;
        return (T*)cur;
    }
    return (T*)tm.onStackOverflow(size);
}
template <typename T> __forceinline void hkDeallocateStack(T* p)
{
    hkThreadMemoryRaw& tm = hkThreadMemoryRaw::getInstance();
    tm.m_stackCurrent = (char*)p;
    if ((char*)p == tm.m_stackBase)
        tm.onStackUnderflow(p);
}

// ---- shapes / bodies --------------------------------------------------------------------------------------
struct hkReferencedObject
{
    virtual ~hkReferencedObject() {}
    uint16_t m_memSizeAndFlags;
    int16_t  m_referenceCount;
};
struct hkShape : hkReferencedObject { uint32_t m_userData; };   // +8
struct hkConvexShape : hkShape
{
    float m_radius;                                              // +0xc
    virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
};
struct hkConvexShapeRef { hkConvexShape* m_shape; uint32_t m_unknown; };
struct hkConvexListShape;
// temporary "list as one convex hull" view
struct hkConvexListConvexShape : hkConvexShape
{
    hkConvexShapeRef* m_subShapesData;                           // +0x10
    int m_subShapesSize;                                         // +0x14
    inline hkConvexListConvexShape(const hkConvexListShape& list, int);   // radius 0 form
    inline hkConvexListConvexShape(const hkConvexListShape& list);        // radius of the first child
};
struct hkConvexListShape : hkConvexListConvexShape
{
    int m_subShapesCapacity;                                     // +0x18
    float m_minDistanceToUseConvexHullForGsk;                    // +0x1c
};
inline hkConvexListConvexShape::hkConvexListConvexShape(const hkConvexListShape& list, int)
{
    m_userData = 0;
    m_referenceCount = 1;
    m_radius = 0.0f;
    m_subShapesData = list.m_subShapesData;
    m_subShapesSize = list.m_subShapesSize;
}
inline hkConvexListConvexShape::hkConvexListConvexShape(const hkConvexListShape& list)
{
    m_userData = 0;
    m_referenceCount = 1;
    m_radius = list.m_subShapesData[0].m_shape->m_radius;
    m_subShapesData = list.m_subShapesData;
    m_subShapesSize = list.m_subShapesSize;
}

struct hkSweptTransform { hkVector4 m_centerOfMass0, m_centerOfMass1, m_rotation0, m_rotation1, m_centerOfMassLocal; };
struct hkMotionState
{
    hkTransform      m_transform;                       // +0x00
    hkSweptTransform m_sweptTransform;                  // +0x40 (m_centerOfMass1.w = inverse delta time)
    hkVector4        m_deltaAngle;                      // +0x90
    hkReal           m_objectRadius;                    // +0xa0
};
struct hkCdBody
{
    const hkShape*       m_shape;                       // +0
    uint32_t             m_shapeKey;                    // +4
    const hkMotionState* m_motion;                      // +8 (hkMotionState* on a root body)
    const hkCdBody*      m_parent;                      // +0xc
};
struct hkStepInfo { hkReal m_startTime, m_endTime, m_deltaTime, m_invDeltaTime; };
struct hkProcessCollisionInput
{
    void*      m_dispatcher;                            // +0x0
    void*      m_filter;                                // +0x4
    hkReal     m_tolerance;                             // +0x8
    bool       m_createPredictiveAgents;                // +0xc
    hkStepInfo m_stepInfo;                              // +0x10
};
struct hkContactPoint { hkVector4 m_position; hkVector4 m_separatingNormal; };
struct hkProcessCdPoint { hkContactPoint m_contact; uint32_t m_extra[4]; };   // 0x30 bytes
struct hkProcessCollisionOutput
{
    hkProcessCdPoint* m_firstFreeContactPoint;          // +0
    uint32_t m_pad0[3];
    hkContactPoint m_toiContact;                        // +0x10
    hkProcessCdPoint m_contactPoints[256];              // +0x30
    uint32_t m_toiProperties;                           // +0x3030
    hkTime   m_toiTime;                                 // +0x3034
    uint32_t m_pad1[2];
    uint32_t* m_potentialContacts;                      // +0x3040 (0x1008 bytes copied by the backup)
};
struct hkProcessCollisionOutputBackup
{
    hkProcessCdPoint* m_firstFreeContactPoint;
    uint32_t m_potentialContacts[0x402];       // +4 .. +0x100c
    uint32_t m_pad;
    uint32_t m_toiContact[8];
    hkTime   m_toiTime;                                 // +0x1030
    uint32_t m_toiProperties;
    hkProcessCollisionOutputBackup(const hkProcessCollisionOutput& out);   // 0x010dd1d0
    void restore(hkProcessCollisionOutput& out);                            // 0x010dd260
};
struct hkContactMgr;
struct hkCollisionDispatcher;

// ---- GSK / agent callees -------------------------------------------------------------------------------------
struct hkGskCache { uint32_t m_pad[3]; };
struct hkGskInfo
{
    const hkTransform*   m_aTb;
    const hkMotionState* m_transformA;
    const hkShape*       m_shapeA;
    const hkShape*       m_shapeB;
    float                m_tolerance;
};
extern int  __cdecl hkGsk_closestPoints(hkGskInfo* info, hkGskCache* cache, hkVector4* sepNormal, hkVector4* out);   // 0x0110fa20
struct hkGskManifold
{
    uint8_t m_numVertsA, m_numVertsB, m_numContactPoints, m_pad;
    struct ContactPoint { uint8_t m_dimA, m_dimB; hkUint16 m_id; uint32_t m_allVerts; } m_contactPoints[4];
    uint8_t m_padding[32];
};
extern void __cdecl hkGskManifold_cleanup(hkGskManifold* manifold, hkContactMgr* mgr);                       // 0x0110fdd0
extern void __cdecl hkAgent1nMachine_Destroy(void* track, hkCollisionDispatcher* dispatcher, hkContactMgr* mgr);  // 0x01104760
extern void __cdecl hkAgent1nMachine_Create(void* track);                                                    // 0x01103bc0
struct hkAgent3ProcessInput                    // 0x70 bytes
{
    const hkCdBody* m_bodyA;                   // +0
    const hkCdBody* m_bodyB;                   // +4
    const hkProcessCollisionInput* m_input;    // +8
    hkContactMgr* m_contactMgr;                // +0xc
    hkTransform m_aTb;                         // +0x10
    float m_distAtT1;                          // +0x50
    hkVector4 m_linearTimInfo;                 // +0x60
};
extern "C" void __cdecl hkAgent1nMachine_Process(void* track, hkAgent3ProcessInput& input, const hkShape* collection,
                                                 const hkShapeKey* hitList, int numHits, hkProcessCollisionOutput& output);   // 0x011048d0
// an hkArray<void*> with in-place storage for one sector pointer: the agent track
struct hkAgent1nTrackInit
{
    void* m_data; int m_size; int m_capacityAndFlags; void* m_storage;
    hkAgent1nTrackInit() { m_data = &m_storage; m_size = 0; m_capacityAndFlags = (int)0x80000001; }
};

// ---- the agent ----------------------------------------------------------------------------------------------
struct hkCollisionAgent
{
    virtual ~hkCollisionAgent() {}
    virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                  const hkProcessCollisionInput& input, hkProcessCollisionOutput& result);
    uint16_t      m_memSizeAndFlags;                    // +4
    int16_t       m_referenceCount;                     // +6
    hkContactMgr* m_contactMgr;                         // +8
};
struct hkGskBaseAgent : hkCollisionAgent
{
    hkGskCache m_cache;                                 // +0xc
    hkTime     m_timeOfSeparatingNormal;                // +0x18
    hkReal     m_allowedPenetration;                    // +0x1c
    hkVector4  m_separatingNormal;                      // +0x20 (w = distance)
};
struct hkGskfAgent : hkGskBaseAgent
{
    hkGskManifold m_manifold;                           // +0x30
};
struct hkPredGskfAgent : hkGskfAgent
{
    virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                  const hkProcessCollisionInput& input, hkProcessCollisionOutput& result);   // 0x010d9f60
};
struct hkConvexListAgent : hkPredGskfAgent
{
    hkCollisionDispatcher* m_dispatcher;                // +0x80
    uint8_t  m_inGskMode;                               // +0x84
    uint8_t  m_pad85;
    int16_t  m_hullCheckCountdown;                      // +0x86
    uint32_t m_pad4[2];
    virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                  const hkProcessCollisionInput& input, hkProcessCollisionOutput& result);   // 0x010de110
};

// the agent track (stream mode) and the manifold (gsk mode) share storage at +0x30; in stream mode the
// float at +0x40 caches the distance of the list's hull
#define HK_HULL_DISTANCE(agent) (*(float*)((char*)(agent) + 0x40))
#define HK_AGENT_TRACK(agent)   ((char*)(agent) + 0x30)

// temporary "body B as one convex hull"
struct hkConvexListHullBody : hkCdBody
{
    hkConvexListConvexShape m_hull;
    hkConvexListHullBody(const hkCdBody& B) : m_hull(*(const hkConvexListShape*)B.m_shape)
    {
        m_shape = &m_hull;
        m_shapeKey = B.m_shapeKey;
        m_motion = B.m_motion;
        m_parent = &B;
    }
};

// @ 0x010de110
void hkConvexListAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                         const hkProcessCollisionInput& input, hkProcessCollisionOutput& result)
{
    HK_TIMER_BEGIN_LIST("CvxLst", "Tim");

    const hkConvexListShape* shapeB = (const hkConvexListShape*)bodyB.m_shape;
    const hkMotionState* msA = bodyA.m_motion;
    const hkMotionState* msB = bodyB.m_motion;

    // hkSweptTransformUtil::calcTimInfo: linear movement (xyz) and worst-case angular movement (w)
    hkVector4 timInfo;
    {
        const hkReal deltaTime = input.m_stepInfo.m_deltaTime;
        hkVector4 diffB;
        timInfo.x = msA->m_sweptTransform.m_centerOfMass0.x - msA->m_sweptTransform.m_centerOfMass1.x;
        timInfo.y = msA->m_sweptTransform.m_centerOfMass0.y - msA->m_sweptTransform.m_centerOfMass1.y;
        timInfo.z = msA->m_sweptTransform.m_centerOfMass0.z - msA->m_sweptTransform.m_centerOfMass1.z;
        diffB.x = msB->m_sweptTransform.m_centerOfMass1.x - msB->m_sweptTransform.m_centerOfMass0.x;
        diffB.y = msB->m_sweptTransform.m_centerOfMass1.y - msB->m_sweptTransform.m_centerOfMass0.y;
        diffB.z = msB->m_sweptTransform.m_centerOfMass1.z - msB->m_sweptTransform.m_centerOfMass0.z;
        const hkReal scaleA = deltaTime * msA->m_sweptTransform.m_centerOfMass1.w;
        const hkReal scaleB = deltaTime * msB->m_sweptTransform.m_centerOfMass1.w;
        timInfo.x = timInfo.x * scaleA;
        timInfo.y = timInfo.y * scaleA;
        timInfo.z = timInfo.z * scaleA;
        timInfo.x = diffB.x * scaleB + timInfo.x;
        timInfo.y = diffB.y * scaleB + timInfo.y;
        timInfo.z = diffB.z * scaleB + timInfo.z;
        timInfo.w = msB->m_objectRadius * msB->m_deltaAngle.w * scaleB + msA->m_objectRadius * msA->m_deltaAngle.w * scaleA;
    }

    hkProcessCollisionOutputBackup backup(result);

    if (m_inGskMode)
        goto GSK_MODE;

STREAM_MODE:
    HK_TIMER_SPLIT_LIST("Stream");
    if (m_hullCheckCountdown-- >= 0)
        goto STREAM_PROCESS;
    {
        // every 25 steps: is the hull of the list separated from body A?
        m_hullCheckCountdown = 25;
        hkConvexListConvexShape hull(*shapeB, 0);
        hkTransform aTb;
        aTb.setMulInverseMul(msA->m_transform, msB->m_transform);
        hkGskInfo info;
        info.m_aTb = &aTb;
        info.m_transformA = msA;
        info.m_shapeA = bodyA.m_shape;
        info.m_shapeB = &hull;
        info.m_tolerance = input.m_tolerance;
        hkVector4 closest;
        if (!hkGsk_closestPoints(&info, &m_cache, &m_separatingNormal, &closest))
            goto HULL_NOT_SEPARATED;
        // hull is separated: switch to gsk mode
        hkAgent1nMachine_Destroy(HK_AGENT_TRACK(this), m_dispatcher, m_contactMgr);
        *(void**)HK_AGENT_TRACK(this) = 0;
        m_inGskMode = 1;
        backup.restore(result);
    }

GSK_MODE:
    if (m_separatingNormal.w > input.m_tolerance)
    {
        m_separatingNormal.w = m_separatingNormal.w
            - (((timInfo.z * m_separatingNormal.z + timInfo.y * m_separatingNormal.y) + timInfo.x * m_separatingNormal.x) + timInfo.w);
        if (*(volatile hkReal*)&m_separatingNormal.w > input.m_tolerance)
            goto TIM_KEEPS_APART;
    }

    HK_TIMER_SPLIT_LIST("Gsk");
    {
        hkConvexListHullBody hullB(bodyB);
        hkPredGskfAgent::processCollision(bodyA, hullB, input, result);
    }
    if (backup.m_toiTime == result.m_toiTime)
    {
        // stay in gsk mode unless the contact manifold touches more than one child of the list
        if (!m_manifold.m_numContactPoints)
            goto END;
        const hkGskManifold::ContactPoint& cp = m_manifold.m_contactPoints[0];
        // per-vertex byte (index * 16) into the vertex id array that follows the contact points
        const uint8_t* allVerts = (const uint8_t*)&cp.m_allVerts;
        const char* ids = (const char*)&m_manifold.m_contactPoints[m_manifold.m_numContactPoints];
        unsigned firstChild = *(const hkUint16*)(ids + (allVerts[cp.m_dimA] >> 3)) & 0xff00;
        for (int i = cp.m_dimA + 1; i < cp.m_dimA + cp.m_dimB; i++)
        {
            unsigned child = *(const hkUint16*)(ids + (allVerts[i] >> 3)) & 0xff00;
            if (firstChild != child)
                goto SWITCH_TO_STREAM;
        }
        goto END;
    }

SWITCH_TO_STREAM:
    {
        hkGskManifold_cleanup(&m_manifold, m_contactMgr);
        m_inGskMode = 0;
        new (HK_AGENT_TRACK(this)) hkAgent1nTrackInit();
        hkAgent1nMachine_Create(HK_AGENT_TRACK(this));
        m_hullCheckCountdown = 25;
        HK_HULL_DISTANCE(this) = 0.0f;
        backup.restore(result);
    }
    goto STREAM_MODE;

TIM_KEEPS_APART:
    // time of impact estimate keeps the hull apart
    if (m_manifold.m_numContactPoints)
        hkGskManifold_cleanup(&m_manifold, m_contactMgr);
    goto END;

HULL_NOT_SEPARATED:
    HK_HULL_DISTANCE(this) = -m_separatingNormal.w;

STREAM_PROCESS:
    {
        // the hull distance shrinks by the movement of the bodies
        HK_HULL_DISTANCE(this) = HK_HULL_DISTANCE(this) - (hkReal)sqrt((double)((timInfo.x * timInfo.x + timInfo.z * timInfo.z) + timInfo.y * timInfo.y));

        hkAgent3ProcessInput in;
        in.m_bodyA = &bodyA;
        in.m_bodyB = &bodyB;
        in.m_input = &input;
        in.m_contactMgr = m_contactMgr;
        in.m_aTb.setMulInverseMul(msA->m_transform, msB->m_transform);
        in.m_linearTimInfo = timInfo;

        const int n = shapeB->m_subShapesSize;
        int* keys = hkAllocateStack<int>(n + 1);
        for (int i = 0; i < n; i++)
            keys[i] = i;
        keys[n] = -1;
        hkAgent1nMachine_Process(HK_AGENT_TRACK(this), in, shapeB, (const hkShapeKey*)keys, n, result);
        hkDeallocateStack(keys);
    }

END:
    HK_TIMER_END_LIST();
}
