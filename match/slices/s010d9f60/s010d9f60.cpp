// Havok 3.1.0: hkPredGskfAgent::processCollision @ 0x010d9f60  (x87 float, 16-byte aligned frame)
// Predictive GSK convex-convex agent. Flow (labels as in the Havok sources):
//   init:      if the separating normal is not from this step's start time, either just stamp it
//              (no continuous physics -> full process) or recompute it at t0 ("recalcT0").
//   tim:       if the TIM (time of impact) estimate keeps the bodies apart, keep the manifold empty and quit.
//   toi:       continuous physics: if the bodies could come closer than minSeparation, compute a TOI.
//   getPoints: if still farther than the manifold TIM distance, only refresh the existing manifold points.
//   process:   full hkGskfAgent::processCollisionNoTim.
// Layouts: binary offsets; quality info / process input field names follow the dev PDB (see s010ff9e0).
#include "types.h"

typedef float hkReal;
typedef float hkTime;
typedef uint16_t hkUint16;

// hkBool: a char with a bool conversion.
class hkBool
{
public:
    operator bool() const { return m_bool != 0; }
private:
    char m_bool;
};
// hkPadSpu<T>: value wrapper (padded on the SPU); copies as a struct.
template <class T> struct hkPadSpu
{
    T m_storage;
    operator T() const { return m_storage; }
};

class __declspec(align(16)) hkVector4 { public: float x, y, z, w; };
struct hkTransform { hkVector4 m_col0, m_col1, m_col2, m_translation; };   // 0x40 bytes

// ---- Havok monitor-stream timer commands (TLS) ----------------------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkTimerEndListTag[];              // 0x0143cd94 ("lt")
extern const char hkTimerEndTag[];                  // 0x0149cc34 ("Et")

struct hkMonitorCommand  { const char* m_commandAndMonitor; uint32_t m_time0; uint32_t m_pad; };   // 12 bytes
struct hkMonitorCommand2 { hkMonitorCommand m_first; const char* m_secondCommand; };               // 16 bytes

// hkStopwatch tick read: Havok's x86 build reads the cycle counter with an inline-asm rdtsc into a local.
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
#define HK_TIMER_BEGIN(name)       HK_TIMER_CMD("Tt" name)
#define HK_TIMER_END()             HK_TIMER_CMD(hkTimerEndTag)
#define HK_TIMER_SPLIT_LIST(name)  HK_TIMER_CMD("St" name)
#define HK_TIMER_END_LIST()        HK_TIMER_CMD(hkTimerEndListTag)

// ---- shapes / bodies / inputs ------------------------------------------------------------------------------
struct hkConvexShape
{
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void convertVertexIdsToVertices(const hkUint16* ids, int numIds, hkVector4* verticesOut) const;   // slot 10
    uint32_t m_pad[2];
    hkReal   m_radius;                                  // +0xc
};

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
    const hkConvexShape* m_shape;                       // +0x0
    uint32_t             m_shapeKey;                    // +0x4
    const void*          m_motion;                      // +0x8 (hkMotionState* on a root body, hkTransform* otherwise)
    const hkCdBody*      m_parent;                      // +0xc
    hkCdBody(const hkCdBody* parent, const void* motion)
        : m_shape(parent->m_shape), m_shapeKey(parent->m_shapeKey), m_motion(motion), m_parent(parent) {}
    const hkMotionState* getMotionState() const { return (const hkMotionState*)m_motion; }
    const hkTransform&   getTransform() const { return *(const hkTransform*)m_motion; }
};

struct hkCollisionQualityInfo
{
    hkReal m_keepContact;                               // +0x0
    hkReal m_create4dContact;                           // +0x4
    hkReal m_createContact;                             // +0x8
    hkReal m_manifoldTimDistance;                       // +0xc
    hkBool m_useContinuousPhysics;                      // +0x10
    hkReal m_minSeparation;                             // +0x14
    hkReal m_minExtraSeparation;                        // +0x18
    hkReal m_minSafeDeltaTime;                          // +0x1c
    hkReal m_minAbsoluteSafeDeltaTime;                  // +0x20
    hkReal m_toiSeparation;                             // +0x24
    hkReal m_toiExtraSeparation;                        // +0x28
};
struct hkStepInfo { hkPadSpu<hkTime> m_startTime, m_endTime, m_deltaTime, m_invDeltaTime; };
struct hkProcessCollisionInput
{
    void*      m_dispatcher;                            // +0x0
    void*      m_filter;                                // +0x4
    hkReal     m_tolerance;                             // +0x8
    bool       m_createPredictiveAgents;                // +0xc
    hkStepInfo m_stepInfo;                              // +0x10
    void*      m_config;                                // +0x20
    void*      m_dynamicsInfo;                          // +0x24
    const hkCollisionQualityInfo* m_collisionQualityInfo;   // +0x28
};
struct hkProcessCollisionOutput;
struct hkContactMgr;

// Input for the 4d (linear + angular) GSK TOI query.
struct hk4dGskCollideInput
{
    const hkCdBody*                m_bodyA;             // +0x00
    const hkCdBody*                m_bodyB;             // +0x04
    const hkProcessCollisionInput* m_input;             // +0x08
    hkContactMgr*                  m_contactMgr;        // +0x0c
    hkTransform                    m_aTb;               // +0x10
    hkReal                         m_distAtT1;          // +0x50
    hkVector4                      m_linearTimInfo;     // +0x60
};

struct hkGskCache
{
    hkUint16    m_vertices[4];                          // +0x0
    signed char m_dimA, m_dimB, m_maxDimA, m_maxDimB;   // +0x8
};

// GSK closest-feature state.
struct hkGsk
{
    int       m_dimA, m_dimB, m_maxDimA, m_maxDimB;
    bool      m_doNotHandlePenetration;
    int       m_featureChange;
    hkVector4 m_verticesA[4];
    hkVector4 m_pad[8];
    hkVector4 m_verticesB[4];

    __forceinline void init(const hkConvexShape* shapeA, const hkConvexShape* shapeB, const hkGskCache& cache)
    {
        m_dimA = cache.m_dimA;
        m_dimB = cache.m_dimB;
        m_maxDimA = cache.m_maxDimA;
        m_maxDimB = cache.m_maxDimB;
        m_doNotHandlePenetration = false;
        m_featureChange = 0;
        shapeA->convertVertexIdsToVertices(cache.m_vertices, m_dimA, m_verticesA);
        shapeB->convertVertexIdsToVertices(cache.m_vertices + m_dimA, m_dimB, m_verticesB);
    }
    void checkForChangesAndUpdateCache(hkGskCache& cache);   // 0x110cd00
};

struct hkGskManifold
{
    uint8_t m_numVertsA;                                // +0
    uint8_t m_numVertsB;                                // +1
    uint8_t m_numContactPoints;                         // +2
    uint8_t m_pad;
    struct ContactPoint { uint8_t m_dimA, m_dimB; hkUint16 m_id; uint32_t m_allVerts; } m_contactPoints[4];
    const hkUint16* getVertexIds() const { return (const hkUint16*)&m_contactPoints[m_numContactPoints]; }
};

struct hkGskManifoldWork
{
    hkVector4 m_vertices[16];                           // +0x00
    hkVector4 m_masterNormal;                           // +0x100
    hkReal    m_radiusA;                                // +0x110
    hkReal    m_radiusB;                                // +0x114
    hkReal    m_keepContact;                            // +0x118
    hkReal    m_radiusSumSqrd;                          // +0x11c
};

// ---- callees ------------------------------------------------------------------------------------------------
namespace hkSweptTransformUtil {
void lerp2(const hkSweptTransform& st, hkTime t, hkTransform& transformOut);           // 0x1209c50
}
void hkGskBaseAgent_calcSeparatingNormal(const hkCdBody& bodyA, const hkCdBody& bodyB, hkReal earlyOutTolerance,
                                         hkGsk& gsk, hkVector4& separatingNormalOut);  // 0x10ed380
void hk4dGskCollideCalcToi(const hk4dGskCollideInput& in, hkReal allowedPenetration, hkReal minSeparation,
                           hkReal toiSeparation, hkGskCache& cache, hkVector4& separatingNormal,
                           hkProcessCollisionOutput& output);                          // 0x1112950
void hkGskManifold_cleanup(hkGskManifold& manifold, hkContactMgr* mgr);                // 0x110fdd0
void hkGskManifold_verifyAndGetPoints(hkGskManifold& manifold, const hkGskManifoldWork& work, int firstPointIndex,
                                      hkProcessCollisionOutput& output, hkContactMgr* mgr);   // 0x110fe20

// hkVector4::_setTransformedPos: this = t * b (w cleared)
static __forceinline void setTransformedPos(hkVector4& out, const hkTransform& t, const hkVector4& b)
{
    const hkReal x = b.x, y = b.y, z = b.z;
    out.x = t.m_col0.x * x + (t.m_col1.x * y + t.m_col2.x * z) + t.m_translation.x;
    out.y = t.m_col0.y * x + (t.m_col1.y * y + t.m_col2.y * z) + t.m_translation.y;
    out.z = t.m_col0.z * x + (t.m_col1.z * y + t.m_col2.z * z) + t.m_translation.z;
    out.w = 0.0f;
}

// hkVector4Util::transformPoints: Havok copies the transform first so the loop cannot alias it.
static __forceinline void transformPoints(const hkTransform& t, const hkVector4* vectorsIn, int numVectors,
                                          hkVector4* vectorsOut)
{
    const hkTransform unaliased = t;
    for (int i = 0; i < numVectors; i++)
        setTransformedPos(vectorsOut[i], unaliased, vectorsIn[i]);
}

static inline hkReal min2(hkReal a, hkReal b) { return a < b ? a : b; }

// ---- agents --------------------------------------------------------------------------------------------------
struct hkCollisionAgent
{
    virtual void dtor();
    virtual void slot1();
    virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                  const hkProcessCollisionInput& input, hkProcessCollisionOutput& result);
    uint16_t      m_memSizeAndFlags;                    // +4
    int16_t       m_referenceCount;                     // +6
    hkContactMgr* m_contactMgr;                         // +8
};
struct hkGskBaseAgent : hkCollisionAgent
{
    hkGskCache m_cache;                                 // +0xc
    hkPadSpu<hkTime> m_timeOfSeparatingNormal;          // +0x18
    hkReal     m_allowedPenetration;                    // +0x1c
    hkVector4  m_separatingNormal;                      // +0x20 (w = distance)
};
struct hkGskfAgent : hkGskBaseAgent
{
    hkGskManifold m_manifold;                           // +0x30
    void processCollisionNoTim(const hkCdBody& bodyA, const hkCdBody& bodyB,
                               const hkProcessCollisionInput& input, hkProcessCollisionOutput& result);   // 0x10ec700
};
struct hkPredGskfAgent : hkGskfAgent
{
    virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                  const hkProcessCollisionInput& input, hkProcessCollisionOutput& result);
};

// @ 0x010d9f60
void hkPredGskfAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                       const hkProcessCollisionInput& input, hkProcessCollisionOutput& result)
{
    HK_TIMER_BEGIN_LIST("PredGskf", "init");

    if (hkTime(input.m_stepInfo.m_startTime) != hkTime(m_timeOfSeparatingNormal))
    {
        if (!input.m_collisionQualityInfo->m_useContinuousPhysics)
        {
            m_timeOfSeparatingNormal = input.m_stepInfo.m_endTime;
            goto PROCESS_AT_T1;
        }
        HK_TIMER_BEGIN("recalcT0");
        {
            hkTransform transA;
            hkTransform transB;
            hkCdBody tempBodyA(&bodyA, &transA);
            hkCdBody tempBodyB(&bodyB, &transB);
            hkSweptTransformUtil::lerp2(bodyA.getMotionState()->m_sweptTransform, input.m_stepInfo.m_startTime, transA);
            hkSweptTransformUtil::lerp2(bodyB.getMotionState()->m_sweptTransform, input.m_stepInfo.m_startTime, transB);

            hkGsk gsk;
            gsk.init(bodyA.m_shape, bodyB.m_shape, m_cache);
            hkGskBaseAgent_calcSeparatingNormal(tempBodyA, tempBodyB, input.m_collisionQualityInfo->m_keepContact,
                                                gsk, m_separatingNormal);
            if (gsk.m_featureChange)
                gsk.checkForChangesAndUpdateCache(m_cache);
        }
        HK_TIMER_END();
    }

    m_timeOfSeparatingNormal = input.m_stepInfo.m_endTime;

    {
        // hkSweptTransformUtil::calcTimInfo: linear movement (xyz) and worst-case angular movement (w)
        const hkMotionState* msA = bodyA.getMotionState();
        const hkMotionState* msB = bodyB.getMotionState();
        const hkReal deltaTime = input.m_stepInfo.m_deltaTime;
        hkVector4 diffA, diffB;
        diffA.x = msA->m_sweptTransform.m_centerOfMass0.x - msA->m_sweptTransform.m_centerOfMass1.x;
        diffA.y = msA->m_sweptTransform.m_centerOfMass0.y - msA->m_sweptTransform.m_centerOfMass1.y;
        diffA.z = msA->m_sweptTransform.m_centerOfMass0.z - msA->m_sweptTransform.m_centerOfMass1.z;
        diffB.x = msB->m_sweptTransform.m_centerOfMass1.x - msB->m_sweptTransform.m_centerOfMass0.x;
        diffB.y = msB->m_sweptTransform.m_centerOfMass1.y - msB->m_sweptTransform.m_centerOfMass0.y;
        diffB.z = msB->m_sweptTransform.m_centerOfMass1.z - msB->m_sweptTransform.m_centerOfMass0.z;
        const hkReal scaleA = deltaTime * msA->m_sweptTransform.m_centerOfMass1.w;
        const hkReal scaleB = deltaTime * msB->m_sweptTransform.m_centerOfMass1.w;
        hkVector4 timInfo;
        timInfo.x = diffB.x * scaleB + diffA.x * scaleA;
        timInfo.y = diffB.y * scaleB + diffA.y * scaleA;
        timInfo.z = diffB.z * scaleB + diffA.z * scaleA;
        timInfo.w = msB->m_objectRadius * msB->m_deltaAngle.w * scaleB + msA->m_objectRadius * msA->m_deltaAngle.w * scaleA;

        const hkReal dist = m_separatingNormal.w
                          - (timInfo.x * m_separatingNormal.x + (timInfo.y * m_separatingNormal.y + timInfo.z * m_separatingNormal.z))
                          - timInfo.w;

        const hkCollisionQualityInfo& qi = *input.m_collisionQualityInfo;
        if (dist > qi.m_keepContact && m_allowedPenetration * 0.5f < dist)
        {
            HK_TIMER_SPLIT_LIST("tim");
            m_separatingNormal.w = dist;
            if (m_manifold.m_numContactPoints)
                hkGskManifold_cleanup(m_manifold, m_contactMgr);
            goto END;
        }

        if (qi.m_useContinuousPhysics)
        {
            HK_TIMER_SPLIT_LIST("toi");
            hk4dGskCollideInput in4d;
            in4d.m_bodyA = &bodyA;
            in4d.m_bodyB = &bodyB;
            in4d.m_input = &input;
            in4d.m_contactMgr = m_contactMgr;
            in4d.m_distAtT1 = dist;
            in4d.m_linearTimInfo = timInfo;

            const hkReal distAtT0 = m_separatingNormal.w;
            const hkReal minSeparation = min2(qi.m_minSeparation * m_allowedPenetration,
                                              qi.m_minExtraSeparation * m_allowedPenetration + distAtT0);
            if (dist < minSeparation)
            {
                const hkReal toiSeparation = min2(qi.m_toiSeparation * m_allowedPenetration,
                                                  qi.m_toiExtraSeparation * m_allowedPenetration + distAtT0);
                hk4dGskCollideCalcToi(in4d, m_allowedPenetration, minSeparation, toiSeparation, m_cache,
                                      m_separatingNormal, result);
                goto PROCESS_AT_T1;
            }
        }

        if (dist > qi.m_manifoldTimDistance)
        {
            HK_TIMER_SPLIT_LIST("getPoints");
            m_separatingNormal.w = dist;

            // hkGskManifold_init
            hkGskManifoldWork work;
            const hkConvexShape* shapeA = bodyA.m_shape;
            const hkConvexShape* shapeB = bodyB.m_shape;
            work.m_keepContact = input.m_tolerance;
            work.m_radiusA = shapeA->m_radius;
            work.m_radiusB = shapeB->m_radius;
            const hkReal radiusSum = work.m_radiusB + work.m_radiusA + work.m_keepContact;
            work.m_radiusSumSqrd = radiusSum * radiusSum;
            work.m_masterNormal = m_separatingNormal;
            if (m_manifold.m_numContactPoints)
            {
                const hkUint16* vertexIds = m_manifold.getVertexIds();
                shapeA->convertVertexIdsToVertices(vertexIds, m_manifold.m_numVertsA, &work.m_vertices[0]);
                transformPoints(bodyA.getTransform(), &work.m_vertices[0], m_manifold.m_numVertsA, &work.m_vertices[0]);
                shapeB->convertVertexIdsToVertices(vertexIds + m_manifold.m_numVertsA, m_manifold.m_numVertsB,
                                                   &work.m_vertices[m_manifold.m_numVertsA]);
                transformPoints(bodyB.getTransform(), &work.m_vertices[m_manifold.m_numVertsA], m_manifold.m_numVertsB,
                                &work.m_vertices[m_manifold.m_numVertsA]);
            }
            hkGskManifold_verifyAndGetPoints(m_manifold, work, 0, result, m_contactMgr);
            goto END;
        }
    }

PROCESS_AT_T1:
    HK_TIMER_SPLIT_LIST("process");
    processCollisionNoTim(bodyA, bodyB, input, result);

END:
    HK_TIMER_END_LIST();
}
