// @ 0x01112950  hkGsk_calcToi   (Havok 3.1.0; real name unknown, Claude-coined)
// Flags: /O2 /MD /Gy /EHsc /TP /fp:fast (x87, 16-byte aligned frame; /fp:fast for the inline fsqrt).
//
// Continuous (time-of-impact) step of the predictive GSK convex agent, called from
// hkPredGskAgent3::process (s010ff9e0, there declared as hkGsk_toi) when the predicted
// distance drops below the minimum separation.
//   1. "setup":   tolerances from hkCollisionQualityInfo, per-body angular deltas over the step,
//                 the cached GSK simplex vertices of both shapes.
//   2. loop:      conservative advancement. From the current separating normal, bound the
//                 approaching velocity (linear TIM + angular * object radius), advance t by the
//                 safe step (optionally refined against the plane through the closest point,
//                 "Stplane"), re-run GSK at the new time ("StsepNormal").
//   3. "Stfinal": up to 10 regula-falsi steps on the distance function to hit toiSeparation.
//   4. builds the TOI contact point, estimates the separating velocity and reports it through
//                 hkContactMgr::addToi; on success stores it in the collision output.
// The monitor-stream timer commands (TLS) are written out as macros like in s010ff9e0.

#include <math.h>

typedef unsigned char  hkUchar;
typedef signed char    hkInt8;
typedef unsigned short hkUint16;
typedef unsigned int   hkUint32;
typedef float          hkReal;
typedef float          hkTime;

class __declspec(align(16)) hkVector4 { public: float x, y, z, w; };

class hkRotation { public: hkVector4 m_col0, m_col1, m_col2; };

class hkTransform
{
public:
    hkRotation m_rotation;       // +0x00
    hkVector4  m_translation;    // +0x30
    void setMulInverseMul(const hkTransform& bTa, const hkTransform& bTc);   // 0x010810f0
};

// hkVector4 out-of-line helpers (0x01081360, 0x010814a0)
class __declspec(align(16)) hkVector4M : public hkVector4
{
public:
    void setTransformedPos(const hkTransform& t, const hkVector4& p);   // 0x01081360
    void setRotatedDir(const hkRotation& r, const hkVector4& d);        // 0x010814a0
};

class hkSweptTransform
{
public:
    hkVector4 m_centerOfMass0;      // +0x00 (w: start time)
    hkVector4 m_centerOfMass1;      // +0x10 (w: inverse delta time)
    hkVector4 m_rotation0;          // +0x20
    hkVector4 m_rotation1;          // +0x30
    hkVector4 m_centerOfMassLocal;  // +0x40
};

class hkMotionState
{
public:
    hkTransform      m_transform;         // +0x00
    hkSweptTransform m_sweptTransform;    // +0x40
    hkVector4        m_deltaAngle;        // +0x90
    float            m_objectRadius;      // +0xa0
};

namespace hkSweptTransformUtil {
void lerp2Ha(const hkSweptTransform& sweptTrans, hkReal t, hkReal deltaTime, hkTransform& out);   // 0x01209f50
}

struct hkSphere { hkVector4 m_pos; };

class hkConvexShape
{
public:
    struct CollisionSpheresInfo { int m_numSpheres; int m_pad[3]; };
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void getCollisionSpheresInfo(CollisionSpheresInfo& info) const;                       // +0x1c
    virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;                     // +0x20
    virtual void v9();
    virtual void getSupportingVertices(const hkUint16* ids, int numIds, hkVector4* verticesOut) const;   // +0x28
    float m_pad[2];
    float m_radius;      // +0xc
};

struct hkCdBody
{
    const hkConvexShape* m_shape;   // +0x0
    hkUint32             m_shapeKey;
    const hkMotionState* m_motion;  // +0x8
    const hkCdBody*      m_parent;  // +0xc
};

struct hkStepInfo
{
    hkTime m_startTime;      // +0x0
    hkTime m_endTime;        // +0x4
    hkReal m_deltaTime;      // +0x8
    hkReal m_invDeltaTime;   // +0xc
};

struct hkCollisionQualityInfo
{
    float m_keepContact;              // +0x00
    float m_create4dContact;          // +0x04
    float m_createContact;            // +0x08
    float m_manifoldTimDistance;      // +0x0c
    char  m_useContinuousPhysics;     // +0x10
    float m_minSeparation;            // +0x14
    float m_minExtraSeparation;       // +0x18
    float m_minSafeDeltaTime;         // +0x1c
    float m_minAbsoluteSafeDeltaTime; // +0x20
    float m_toiSeparation;            // +0x24
    float m_toiExtraSeparation;       // +0x28
    float m_toiAccuracy;              // +0x2c
    float m_maxContraintViolation;    // +0x30
    float m_minToiDeltaTime;          // +0x34
};

struct hkProcessCollisionInput
{
    void*  m_dispatcher;                                  // +0x00
    void*  m_filter;                                      // +0x04
    float  m_tolerance;                                   // +0x08
    char   m_createPredictiveAgents;                      // +0x0c
    hkStepInfo m_stepInfo;                                // +0x10
    void*  m_config;                                      // +0x20
    void*  m_dynamicsInfo;                                // +0x24
    const hkCollisionQualityInfo* m_collisionQualityInfo; // +0x28
};

class hkContactPoint
{
public:
    hkVector4 m_position;           // +0x00
    hkVector4 m_separatingNormal;   // +0x10 (w: distance)
};

struct hkContactPointMaterial { void* m_userData; hkUint16 m_friction; hkUchar m_restitution; hkUchar m_flags; };

class hkContactMgr
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual int addToi(const hkCdBody& a, const hkCdBody& b, const hkProcessCollisionInput& input,
                       hkContactPoint& cp, hkTime toi, hkReal separatingVelocity,
                       hkContactPointMaterial& materialOut);                                       // +0x1c
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

struct hkProcessCdPoint { hkUint32 m_data[12]; };

struct hkProcessCollisionOutput
{
    hkProcessCdPoint*      m_firstFreeContactPoint;     // +0x0000
    hkContactPoint         m_toiContactPoint;           // +0x0010
    hkProcessCdPoint       m_contactPoints[256];        // +0x0030
    float                  m_toiSeperatingVelocity;     // +0x3030
    hkTime                 m_toi;                       // +0x3034
    hkContactPointMaterial m_toiMaterial;               // +0x3038
};

// Agent data: the cached GSK simplex (vertex ids + dimensions).
struct hkGskCache
{
    hkUint16 m_vertices[4];   // +0x0
    hkInt8   m_dimA;          // +0x8
    hkInt8   m_dimB;          // +0x9
    hkInt8   m_maxDimA;       // +0xa
    hkInt8   m_maxDimB;       // +0xb
};

// GSK solver state (0x170 bytes on the stack).
class __declspec(align(16)) hkGsk
{
public:
    int       m_dimA;               // +0x000
    int       m_dimB;               // +0x004
    int       m_maxDimA;            // +0x008
    int       m_maxDimB;            // +0x00c
    bool      m_doNotHandlePenetration;   // +0x010
    int       m_featureChange;      // +0x014
    hkVector4 m_verticesA[4];       // +0x020
    hkVector4 m_verticesTmp[4];     // +0x060
    hkVector4 m_verticesBinA[4];    // +0x0a0
    hkVector4 m_verticesB[4];       // +0x0e0
    hkVector4 m_tmp;                // +0x120
    hkVector4 m_closestPointA;      // +0x130
    hkVector4 m_pad[4];

    // returns the separating normal in A space (w = distance)
    void getClosestPoint(const hkConvexShape* shapeA, const hkConvexShape* shapeB,
                         const hkTransform& aTb, hkVector4& normalOut);          // 0x0110e510
    void checkForChangesAndUpdateCache(hkGskCache& cache);                       // 0x0110cd00
};

// Inputs of the plane-based TOI estimate (hk4dGskCollidePointsWithPlane).
struct __declspec(align(16)) hk4dGskVertexCollidePointsInput
{
    const hkMotionState* m_motionA;      // +0x00
    const hkMotionState* m_motionB;      // +0x04
    hkSphere*            m_vertices;     // +0x08 (shape A collision spheres, stack allocated)
    int                  m_numVertices;  // +0x0c
    int                  m_allocated;    // +0x10
    float                m_radiusSum;    // +0x14
    float                m_maxAngularDist;      // +0x18
    float                m_invMaxAngularDist;   // +0x1c
    hkVector4            m_planeNormalInB;      // +0x20
    hkVector4            m_pointInB;            // +0x30
    const hkStepInfo*    m_stepInfo;            // +0x40
    float                m_approachVelocity;    // +0x44
    float                m_pad48[2];
    hkVector4            m_linearTimInfo;       // +0x50
    hkVector4            m_deltaAngle[2];       // +0x60 (A), +0x70 (B), scaled to one step
    float                m_startT;              // +0x80
};

struct hk4dGskTolerances
{
    float m_toiSeparation;       // +0x00
    float m_minSeparation;       // +0x04
    float m_minSafeDeltaTime;    // +0x08 (normalized to the step)
    float m_minToiDeltaTime;     // +0x0c
    float m_toiAccuracy;         // +0x10
};

extern void __cdecl hk4dGskCollidePointsWithPlane(const hk4dGskVertexCollidePointsInput& input,
                                                  const hk4dGskTolerances& tol, float& toiInOut);   // 0x01112600
extern void __cdecl hkGsk_getClosestPointFromSimplex(const hkVector4* verticesA, const hkVector4* verticesBinA,
                                                     int dimA, int dimB, const hkVector4& direction,
                                                     hkVector4& pointOut, hkVector4& normalOut);     // 0x0110d1d0
// 0x011120a0: static helper in this TU (register args ecx/edx/edi in the binary).
extern float __cdecl hkGsk_calcSeparatingVelocity(const hkVector4* deltaAngles, const hkVector4& normal,
                                                  const hkVector4& position, const hkMotionState* motionA,
                                                  const hkMotionState* motionB, hkTime toi);

// ---- Havok monitor-stream timer commands (TLS) ------------------------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
extern "C" unsigned __int64 __rdtsc();
#pragma intrinsic(__rdtsc)
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern unsigned long g_hkThreadMemoryTls;           // 0x016e4174
extern const char g_hkTimerEndTag0[];               // 0x0143cd94

#define HK_TIMER_BEGIN_LIST(name, sub) do { \
    void* end_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end_) { \
        hkUint32* c_ = (hkUint32*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_[0] = (hkUint32)(name); \
        c_[3] = (hkUint32)(sub); \
        c_[1] = (hkUint32)__rdtsc(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 4); } } while (0)

#define HK_TIMER_CMD(name) do { \
    void* end_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end_) { \
        hkUint32* c_ = (hkUint32*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_[0] = (hkUint32)(name); \
        c_[1] = (hkUint32)__rdtsc(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 3); } } while (0)

#define HK_MONITOR_ADD_VALUE(name, value) do { \
    void* end_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end_) { \
        hkUint32* c_ = (hkUint32*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_[0] = (hkUint32)(name); \
        *(float*)&c_[1] = (value); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 2); } } while (0)

// ---- hkThreadMemory stack allocator -----------------------------------------------------------------------
class hkThreadMemory
{
public:
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void* onStackOverflow(int numBytes);   // +0xc
    virtual void  onStackUnderflow(void* p);       // +0x10
    char  m_pad[0x1c];
    char* m_stackCurrent;   // +0x20
    char* m_stackPrev;      // +0x24
    char* m_stackBase;      // +0x28
    char* m_stackEnd;       // +0x2c
};

template <class T> static __forceinline T* hkAllocateStack(int n)
{
    hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
    int numBytes = (n * (int)sizeof(T) + 16) & ~15;
    char* cur = tm->m_stackCurrent;
    char* next = cur + numBytes;
    if (next > tm->m_stackEnd)
        return (T*)tm->onStackOverflow(numBytes);
    tm->m_stackCurrent = next;
    return (T*)cur;
}

static __forceinline void hkDeallocateStack(void* p)
{
    hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
    tm->m_stackCurrent = (char*)p;
    if ((char*)p == tm->m_stackBase)
        tm->onStackUnderflow(p);
}

static __forceinline float hkAbs(float x) { return x < 0.0f ? -x : x; }

// out[i] = R * in[i] + t, w cleared (hkVector4Util::transformPoints, unrolled by 4)
#define HK_XFORM_ONE(D, S) { \
        const float x = (S).x, y = (S).y, z = (S).z; \
        (D).x = (m20 * z + m10 * y + m00 * x) + tx; \
        (D).y = (m21 * z + m11 * y + m01 * x) + ty; \
        (D).z = (m22 * z + m12 * y + m02 * x) + tz; \
        (D).w = 0.0f; }
static __forceinline void transformPoints(const hkTransform& t, const hkVector4* in, int n, hkVector4* out)
{
    const float m00 = t.m_rotation.m_col0.x, m01 = t.m_rotation.m_col0.y, m02 = t.m_rotation.m_col0.z;
    const float m10 = t.m_rotation.m_col1.x, m11 = t.m_rotation.m_col1.y, m12 = t.m_rotation.m_col1.z;
    const float m20 = t.m_rotation.m_col2.x, m21 = t.m_rotation.m_col2.y, m22 = t.m_rotation.m_col2.z;
    const float tx = t.m_translation.x, ty = t.m_translation.y, tz = t.m_translation.z;
    int i = 0;
    if (n >= 4)
    {
        unsigned blocks = ((unsigned)(n - 4) >> 2) + 1;
        i = blocks * 4;
        const hkVector4* s = in;
        hkVector4* d = out;
        do {
            HK_XFORM_ONE(d[0], s[0]) HK_XFORM_ONE(d[1], s[1]) HK_XFORM_ONE(d[2], s[2]) HK_XFORM_ONE(d[3], s[3])
            s += 4; d += 4;
        } while (--blocks);
    }
    for (; i < n; ++i)
        HK_XFORM_ONE(out[i], in[i])
}

// @ 0x01112950
void __cdecl hkGsk_calcToi(const hkAgent3ProcessInput& input, hkReal allowedPenetrationDepth,
                           hkReal minSeparation, hkReal toiSeparation, hkGskCache& cache,
                           hkVector4& separatingNormal, hkProcessCollisionOutput& output)
{
    HK_TIMER_BEGIN_LIST("LtToi", "setup");

    // ---- setup ----
    const hkProcessCollisionInput* pi = input.m_input;
    const hkCollisionQualityInfo* quality = pi->m_collisionQualityInfo;

    hk4dGskTolerances tol;
    tol.m_toiAccuracy = allowedPenetrationDepth * quality->m_toiAccuracy;
    tol.m_toiSeparation = toiSeparation;
    tol.m_minSeparation = minSeparation;
    {
        float minSafe = quality->m_minAbsoluteSafeDeltaTime;
        float relSafe = allowedPenetrationDepth * quality->m_minSafeDeltaTime;
        if (relSafe > minSafe)
            minSafe = relSafe;
        tol.m_minSafeDeltaTime = minSafe * pi->m_stepInfo.m_invDeltaTime;
    }
    tol.m_minToiDeltaTime = quality->m_minToiDeltaTime;

    const hkConvexShape* shapeB = input.m_bodyB->m_shape;
    const hkConvexShape* shapeA = input.m_bodyA->m_shape;
    const hkMotionState* motionA = input.m_bodyA->m_motion;
    const hkMotionState* motionB = input.m_bodyB->m_motion;

    hk4dGskVertexCollidePointsInput vin;
    vin.m_vertices = 0;
    {
        const float dt = pi->m_stepInfo.m_deltaTime;
        const float sA = dt * motionA->m_sweptTransform.m_centerOfMass1.w;
        vin.m_deltaAngle[0].x = sA * motionA->m_deltaAngle.x;
        vin.m_deltaAngle[0].y = sA * motionA->m_deltaAngle.y;
        vin.m_deltaAngle[0].z = sA * motionA->m_deltaAngle.z;
        vin.m_deltaAngle[0].w = sA * motionA->m_deltaAngle.w;
        const float sB = dt * motionB->m_sweptTransform.m_centerOfMass1.w;
        vin.m_deltaAngle[1].x = sB * motionB->m_deltaAngle.x;
        vin.m_deltaAngle[1].y = sB * motionB->m_deltaAngle.y;
        vin.m_deltaAngle[1].z = sB * motionB->m_deltaAngle.z;
        vin.m_deltaAngle[1].w = sB * motionB->m_deltaAngle.w;
    }

    bool haveNormal = false;
    bool planeFailed = false;
    int numIter = 0;

    hkGsk gsk;
    gsk.m_doNotHandlePenetration = false;
    gsk.m_featureChange = 0;
    gsk.m_dimA = cache.m_dimA;
    gsk.m_dimB = cache.m_dimB;
    gsk.m_maxDimA = cache.m_maxDimA;
    gsk.m_maxDimB = cache.m_maxDimB;
    shapeA->getSupportingVertices(cache.m_vertices, gsk.m_dimA, gsk.m_verticesA);
    shapeB->getSupportingVertices(cache.m_vertices + gsk.m_dimA, gsk.m_dimB, gsk.m_verticesB);

    float oldDist = separatingNormal.w;
    int featureChange = 1;
    float t = 0.0f;
    float tPrev = 0.0f;
    float curDist = separatingNormal.w;
    const float distLimit = tol.m_toiAccuracy + toiSeparation;

    hkVector4 savedNormal;
    hkTransform transA, transB, aTb;
    hkVector4 localNormal;

    // ---- conservative advancement ----
    while (curDist > distLimit)
    {
        float dt = 1.0f - t;
        if (dt <= 0.0f)
            goto END;

        const hkVector4& n = separatingNormal;
        float angular;
        {
            const hkVector4& a = vin.m_deltaAngle[0];
            const hkVector4& b = vin.m_deltaAngle[1];
            const float ax = a.y * n.z - a.z * n.y;
            const float ay = a.z * n.x - a.x * n.z;
            const float az = a.x * n.y - a.y * n.x;
            const float bx = b.y * n.z - b.z * n.y;
            const float by = b.z * n.x - b.x * n.z;
            const float bz = b.x * n.y - b.y * n.x;
            const float lenB = sqrtf(bz * bz + by * by + bx * bx);
            const float lenA = sqrtf(az * az + ay * ay + ax * ax);
            angular = lenB * motionB->m_objectRadius + lenA * motionA->m_objectRadius;
        }
        const float linear = (input.m_linearTimInfo.z * n.z + input.m_linearTimInfo.y * n.y)
                             + n.x * input.m_linearTimInfo.x;
        const float velocity = linear + angular;
        if (velocity <= 0.0f)
            goto END;
        if (separatingNormal.w - velocity * dt > minSeparation)
            goto END;

        dt = (separatingNormal.w - minSeparation) / velocity;

        if (dt < 0.2f && !planeFailed && haveNormal && linear * 10.0f < angular)
        {
            if (!vin.m_vertices)
            {
                vin.m_motionA = motionA;
                vin.m_motionB = motionB;
                vin.m_radiusSum = shapeB->m_radius + shapeA->m_radius;
                vin.m_linearTimInfo = input.m_linearTimInfo;
                vin.m_stepInfo = &pi->m_stepInfo;
                hkConvexShape::CollisionSpheresInfo info;
                shapeA->getCollisionSpheresInfo(info);
                vin.m_allocated = info.m_numSpheres;
                vin.m_numVertices = info.m_numSpheres;
                vin.m_vertices = hkAllocateStack<hkSphere>(info.m_numSpheres);
                shapeA->getCollisionSpheres(vin.m_vertices);
                vin.m_maxAngularDist =
                    vin.m_deltaAngle[1].w * motionB->m_objectRadius * vin.m_deltaAngle[1].w
                    + vin.m_deltaAngle[0].w * motionA->m_objectRadius * vin.m_deltaAngle[0].w;
                vin.m_invMaxAngularDist = 1.0f / (vin.m_maxAngularDist + 1.1920929e-07f);
            }
            vin.m_startT = t;
            vin.m_approachVelocity = velocity;
            HK_TIMER_CMD("Stplane");
            float toi = 1.0f;
            hk4dGskCollidePointsWithPlane(vin, tol, toi);
            const float planeDt = toi - t;
            if (planeDt < dt + dt)
                planeFailed = true;
            else
                dt = planeDt;
        }

        if (dt + t >= 1.0f)
            goto END;
        tPrev = t;
        if (tol.m_minSafeDeltaTime > dt)
            dt = tol.m_minSafeDeltaTime;
        t = dt + t;
        if (!(t < 1.0f))
            t = 1.0f;

        savedNormal = separatingNormal;
        oldDist = separatingNormal.w;

        HK_TIMER_CMD("StsepNormal");
        {
            const hkStepInfo& si = pi->m_stepInfo;
            const float time = t * si.m_deltaTime;
            hkSweptTransformUtil::lerp2Ha(motionA->m_sweptTransform, si.m_startTime, time, transA);
            hkSweptTransformUtil::lerp2Ha(motionB->m_sweptTransform, si.m_startTime, time, transB);
        }
        numIter++;
        aTb.setMulInverseMul(transA, transB);
        gsk.getClosestPoint(shapeA, shapeB, aTb, localNormal);

        const hkRotation& rA = transA.m_rotation;
        separatingNormal.x = (rA.m_col2.x * localNormal.z + rA.m_col1.x * localNormal.y) + localNormal.x * rA.m_col0.x;
        separatingNormal.y = (rA.m_col2.y * localNormal.z + rA.m_col1.y * localNormal.y) + localNormal.x * rA.m_col0.y;
        separatingNormal.z = (rA.m_col2.z * localNormal.z + rA.m_col1.z * localNormal.y) + localNormal.x * rA.m_col0.z;
        separatingNormal.w = 0.0f;

        float px, py, pz;
        const float dist = localNormal.w;
        if (gsk.m_dimA == 1)
        {
            px = gsk.m_verticesA[0].x;
            py = gsk.m_verticesA[0].y;
            pz = gsk.m_verticesA[0].z;
        }
        else if (gsk.m_dimB == 1)
        {
            px = localNormal.x * dist + gsk.m_verticesBinA[0].x;
            py = dist * localNormal.y + gsk.m_verticesBinA[0].y;
            pz = dist * localNormal.z + gsk.m_verticesBinA[0].z;
        }
        else
        {
            px = gsk.m_closestPointA.x;
            py = gsk.m_closestPointA.y;
            pz = gsk.m_closestPointA.z;
        }
        vin.m_pointInB.w = 0.0f;
        featureChange = gsk.m_featureChange;
        haveNormal = true;
        {
            // closest point on B, moved from A space into B space
            const float dx = (px - localNormal.x * dist) - aTb.m_translation.x;
            const float dy = (py - dist * localNormal.y) - aTb.m_translation.y;
            const float dz = (pz - dist * localNormal.z) - aTb.m_translation.z;
            const hkRotation& r = aTb.m_rotation;
            vin.m_pointInB.x = dx * r.m_col0.x + dy * r.m_col0.y + dz * r.m_col0.z;
            vin.m_pointInB.y = dx * r.m_col1.x + dy * r.m_col1.y + dz * r.m_col1.z;
            vin.m_pointInB.z = dx * r.m_col2.x + dy * r.m_col2.y + dz * r.m_col2.z;
        }
        separatingNormal.w = (dist - shapeA->m_radius) - shapeB->m_radius;
        {
            const hkRotation& rB = transB.m_rotation;
            const float nx = separatingNormal.x, ny = separatingNormal.y, nz = separatingNormal.z;
            vin.m_planeNormalInB.x = (rB.m_col0.z * nz + rB.m_col0.y * ny) + rB.m_col0.x * nx;
            vin.m_planeNormalInB.y = (rB.m_col1.z * nz + rB.m_col1.y * ny) + rB.m_col1.x * nx;
            vin.m_planeNormalInB.z = (rB.m_col2.z * nz + rB.m_col2.y * ny) + rB.m_col2.x * nx;
        }
        curDist = separatingNormal.w;
        vin.m_planeNormalInB.w = 0.0f;
    }

    // ---- regula falsi towards toiSeparation ----
    HK_TIMER_CMD("Stfinal");
    {
        float distHi = curDist;     // distance at tHi (below the limit)
        float distLo = oldDist;     // distance at tLo
        float tHi = t;
        float tLo = tPrev;
        int needGsk = featureChange;
        const float radiusSum = shapeA->m_radius + shapeB->m_radius;
        const float slope = (curDist - oldDist) / (t - tPrev);
        const float negAccuracy = -tol.m_toiAccuracy;
        float newT;
        float dist;
        hkVector4 normalOut;
        hkVector4 point;

        for (int i = 0; i < 10; i++)
        {
            float diff = distHi - distLo;
            if (diff > negAccuracy)
            {
                diff = 0.5f;
                tHi = tLo;
            }
            if (hkAbs(distHi - toiSeparation) < tol.m_toiAccuracy)
            {
                haveNormal = true;
                needGsk = 0;
                newT = tHi;
            }
            else
            {
                haveNormal = false;
                float f = (toiSeparation - distLo) / diff;
                if (f <= 0.1f)
                    f = 0.1f;
                else if (!(f < 0.9f))
                    f = 0.9f;
                newT = (1.0f - f) * tLo + f * tHi;
            }

            {
                const hkStepInfo& si = pi->m_stepInfo;
                const float time = newT * si.m_deltaTime;
                hkSweptTransformUtil::lerp2Ha(input.m_bodyA->m_motion->m_sweptTransform, si.m_startTime, time, transA);
                hkSweptTransformUtil::lerp2Ha(input.m_bodyB->m_motion->m_sweptTransform, si.m_startTime, time, transB);
            }
            aTb.setMulInverseMul(transA, transB);

            if (needGsk)
            {
                gsk.getClosestPoint(input.m_bodyA->m_shape, input.m_bodyB->m_shape, aTb, normalOut);
                if (gsk.m_dimA == 1)
                    point = gsk.m_verticesA[0];
                else if (gsk.m_dimB == 1)
                {
                    point.x = normalOut.x * normalOut.w + gsk.m_verticesBinA[0].x;
                    point.y = normalOut.y * normalOut.w + gsk.m_verticesBinA[0].y;
                    point.z = normalOut.z * normalOut.w + gsk.m_verticesBinA[0].z;
                    point.w = normalOut.w * normalOut.w + gsk.m_verticesBinA[0].w;
                }
                else
                    point = gsk.m_closestPointA;
            }
            else
            {
                transformPoints(aTb, gsk.m_verticesB, gsk.m_dimB, gsk.m_verticesBinA);
                hkVector4 dirA;
                const hkRotation& rA = transA.m_rotation;
                dirA.x = rA.m_col0.z * savedNormal.z + rA.m_col0.y * savedNormal.y + savedNormal.x * rA.m_col0.x;
                dirA.y = rA.m_col1.z * savedNormal.z + rA.m_col1.y * savedNormal.y + savedNormal.x * rA.m_col1.x;
                dirA.z = rA.m_col2.z * savedNormal.z + rA.m_col2.y * savedNormal.y + savedNormal.x * rA.m_col2.x;
                dirA.w = 0.0f;
                hkGsk_getClosestPointFromSimplex(gsk.m_verticesA, gsk.m_verticesBinA, gsk.m_dimA, gsk.m_dimB,
                                                 dirA, point, normalOut);
            }

            dist = normalOut.w - radiusSum;
            if (hkAbs(dist - toiSeparation) < tol.m_toiAccuracy || haveNormal || tHi == tLo)
                break;
            if (dist < toiSeparation)
            {
                distHi = dist;
                tHi = newT;
            }
            else
            {
                distLo = dist;
                tLo = newT;
            }
        }

        // ---- report the time of impact ----
        const hkStepInfo& si = pi->m_stepInfo;
        float toiDelta = newT * si.m_deltaTime;
        if (!(toiDelta > tol.m_minToiDeltaTime))
            toiDelta = tol.m_minToiDeltaTime;
        const hkTime toi = toiDelta + si.m_startTime;
        if (!(toi < output.m_toi))
            goto END;
        if (si.m_endTime - tol.m_minToiDeltaTime <= toi)
            goto END;

        const hkConvexShape* sA = input.m_bodyA->m_shape;
        hkVector4M cpPos;
        cpPos.setTransformedPos(transA, point);
        hkContactPoint cp;
        ((hkVector4M&)cp.m_separatingNormal).setRotatedDir(transA.m_rotation, normalOut);
        {
            const float s = -sA->m_radius - dist;
            cp.m_position.x = cp.m_separatingNormal.x * s + cpPos.x;
            cp.m_position.y = cp.m_separatingNormal.y * s + cpPos.y;
            cp.m_position.z = cp.m_separatingNormal.z * s + cpPos.z;
            cp.m_position.w = cp.m_separatingNormal.w * s + cpPos.w;
            cp.m_separatingNormal.w = dist;
        }

        // relative velocity of the contact point along the normal
        const hkMotionState* mA = input.m_bodyA->m_motion;
        const hkMotionState* mB = input.m_bodyB->m_motion;
        const float nlx = -input.m_linearTimInfo.x;
        const float nly = -input.m_linearTimInfo.y;
        const float nlz = -input.m_linearTimInfo.z;
        float vx, vy, vz;
        {
            const hkSweptTransform& st = mA->m_sweptTransform;
            const float u = (toi - st.m_centerOfMass0.w) * st.m_centerOfMass1.w;
            const float v = 1.0f - u;
            const float rx = cp.m_position.x - (v * st.m_centerOfMass0.x + u * st.m_centerOfMass1.x);
            const float ry = cp.m_position.y - (v * st.m_centerOfMass0.y + u * st.m_centerOfMass1.y);
            const float rz = cp.m_position.z - (v * st.m_centerOfMass0.z + u * st.m_centerOfMass1.z);
            const hkVector4& a = vin.m_deltaAngle[0];
            vx = (a.y * rz - a.z * ry) + nlx;
            vy = (a.z * rx - a.x * rz) + nly;
            vz = (a.x * ry - a.y * rx) + nlz;
        }
        {
            const hkSweptTransform& st = mB->m_sweptTransform;
            const float u = (toi - st.m_centerOfMass0.w) * st.m_centerOfMass1.w;
            const float v = 1.0f - u;
            const float rx = cp.m_position.x - (u * st.m_centerOfMass1.x + v * st.m_centerOfMass0.x);
            const float ry = cp.m_position.y - (v * st.m_centerOfMass0.y + u * st.m_centerOfMass1.y);
            const float rz = cp.m_position.z - (v * st.m_centerOfMass0.z + u * st.m_centerOfMass1.z);
            const hkVector4& b = vin.m_deltaAngle[1];
            vx = vx - (b.y * rz - b.z * ry);
            vy = vy - (b.z * rx - b.x * rz);
            vz = vz - (b.x * ry - b.y * rx);
        }
        float projVel = (vz * cp.m_separatingNormal.z + vy * cp.m_separatingNormal.y) + vx * cp.m_separatingNormal.x;
        if (slope < projVel)
        {
            if (slope > 1.2f * projVel)
                projVel = slope;
            else
            {
                projVel = hkGsk_calcSeparatingVelocity(vin.m_deltaAngle, cp.m_separatingNormal, cp.m_position,
                                                       mA, mB, toi);
                if (0.0f < projVel)
                    projVel = 0.0f;
            }
        }
        const hkReal sepVel = projVel * si.m_invDeltaTime;

        hkContactPointMaterial material;
        if (input.m_contactMgr->addToi(*input.m_bodyA, *input.m_bodyB, *input.m_input, cp, toi, sepVel, material) == 0)
        {
            output.m_toiSeperatingVelocity = sepVel;
            output.m_toiContactPoint = cp;
            output.m_toi = toi;
            output.m_toiMaterial = material;
        }
    }

END:
    if (vin.m_vertices)
        hkDeallocateStack(vin.m_vertices);
    HK_MONITOR_ADD_VALUE("MinumIter", (float)numIter);
    if (gsk.m_featureChange)
        gsk.checkForChangesAndUpdateCache(cache);
    HK_TIMER_CMD(g_hkTimerEndTag0);
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
