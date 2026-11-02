// src/game/Havok/_at_01110000.cpp -- migrated from slice(s) s0111ffc0, s0111d560, s0111b170, s01118f50, s011187d0, s01117840, s01115400, s01114370, s01112950, s01112230, s01111330 by tools/migrate/rewrite.py
// Object file: Havok/_at_01110000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <string.h>
#include <stddef.h>

// ---- items of slice s01111330 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef float hkReal;
class __declspec(align(16)) hkVector4_s0111_1330
{
public:
    hkReal x, y, z, w;
    inline hkReal lengthSquared3() const { return x * x + y * y + z * z; }
    inline void setSub4(const hkVector4_s0111_1330& a, const hkVector4_s0111_1330& b)
    { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
    inline void setCross(const hkVector4_s0111_1330& a, const hkVector4_s0111_1330& b)
    {
        x = a.y * b.z - a.z * b.y;
        y = a.z * b.x - a.x * b.z;
        z = a.x * b.y - a.y * b.x;
        w = 0.0f;
    }
};
struct SimplexVertex
{
    hkVector4_s0111_1330 m_position;          // +0x00
    hkReal pad10[3];               // +0x10
    hkReal m_extra;                // +0x1c
    hkReal pad20[4];               // +0x20

    void setFrom(const hkVector4_s0111_1330* pSource);              // 0x01103af0
};
struct Simplex5
{
    SimplexVertex m_v[5];          // 0x30 apart; v[4] is the newest point

    // @ 0x011114b0
    int SelectVertexToDrop();
};
struct hkSimplexKey
{
    uint16_t m_values[4];   // +0x00 packed values, one per vertex
    signed char m_ids[2];   // +0x08 vertex-count halves (their sum is the vertex count)
};
#define HK_REAL_ZERO 0.0f
#define HK_REAL_ONE  1.0f
struct hkPackedRow
{
    union                                           // +0x00 the two ids the row was built from
    {
        struct { uint8_t m_id0, m_id1; uint16_t m_value; };
        uint32_t m_head;                            // +0x00 both ids and the value as one word
    };
    union                                           // +0x04 packed per-vertex byte offsets
    {
        uint8_t  m_payload[4];
        uint32_t m_tail;                            // +0x04 the same four bytes as one word
    };
};
struct hkPackedSimplex
{
    uint8_t     m_numVerticesA;   // +0x00
    uint8_t     m_numVerticesB;   // +0x01
    uint8_t     m_numRows;        // +0x02, at most 4
    uint8_t     m_pad03;          // +0x03
    hkPackedRow m_rows[4];        // +0x04

    uint16_t* wordValues() { return (uint16_t*)((uint8_t*)this + 4 + m_numRows * 8u); }
    uint8_t*  valueBytes() { return (uint8_t*)this + 8; }
    void      removeUnusedVertices();                           // 0x0110fc50
};
struct hkGskInsertPoint
{
    hkVector4_s0111_1330 m_position;         // +0x00
    unsigned  m_pad10[4];         // +0x10
    uint16_t  m_index;            // +0x20
};
struct hkGskInterface
{
    virtual void     v00();
    virtual void     v04();
    virtual uint16_t v08(void* a, void* b, void* c, const void* d);   // +0x08 index lookup / append
    virtual void     v0c();
    virtual void     v10(uint16_t index);                        // +0x10 note a dropped vertex
};
struct hkGskSolveBody
{
    hkReal  m_pad00[0x40];
    hkReal  m_p0[3];        // +0x40 segment start
    hkReal  m_start;        // +0x4c
    hkReal  m_p1[3];        // +0x50 segment end
    hkReal  m_invRange;     // +0x5c
};
extern const hkReal gGskPositiveScale;
extern const hkReal gGskNegativeScale;
// ---- items of slice s01111330 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern const hkReal gGskPositiveScale;
extern const hkReal gGskNegativeScale;

// ---- items of slice s01112230 begin (TODO(rewrite): local stubs, replace by canonical classes)
class hkRotation_s0111_2230;
class __declspec(align(16)) hkVector4_s0111_2230
{
public:
    hkReal x, y, z, w;

    void setRotatedDir(const hkRotation_s0111_2230& r, const hkVector4_s0111_2230& v);             // 0x010814a0
    void setTransformedPos(const hkRotation_s0111_2230& r, const hkVector4_s0111_2230& v);         // 0x01081360
    void setRotatedInverseDir(const hkRotation_s0111_2230& r, const hkVector4_s0111_2230& v);      // 0x01081440
};
class __declspec(align(16)) hkMatrix3_s0111_2230
{
public:
    hkVector4_s0111_2230 m_col0, m_col1, m_col2;
};
class hkRotation_s0111_2230 : public hkMatrix3_s0111_2230
{
};
class hkTransform_s0111_2230
{
public:
    hkRotation_s0111_2230 m_rotation;      // 0x00
    hkVector4_s0111_2230   m_translation;  // 0x30

    void setMulInverseMul(const hkTransform_s0111_2230& a, const hkTransform_s0111_2230& b);       // 0x010810f0
};
class hkSweptTransform
{
public:
    hkReal m_0x00;              // 0x00  start time
    hkReal m_0x04;              // 0x04
    hkReal m_0x08;              // 0x08  inverse delta time
    hkReal m_0x0c;              // 0x0c
};
struct hk4dGskVertexCollidePointsInput
{
    const void*  m_p0;          // 0x00  first swept shape (its transform is at +0x40)
    const void*  m_p1;          // 0x04  second swept shape (its hkVector4 is at +0x80)
    hkReal*      m_points;      // 0x08  4 floats per collide point
    int          m_numPoints;   // 0x0c
    hkReal       m_0x10;        // 0x10
    hkReal       m_0x14;        // 0x14  negated into hk4dGskCollideMatrices::m_0xc0.w
    hkReal       m_0x18;        // 0x18
    hkReal       m_0x1c;        // 0x1c
    hkVector4_s0111_2230    m_0x20;        // 0x20  direction handed to setRotatedDir
    hkVector4_s0111_2230    m_0x30;        // 0x30  position handed to setTransformedPos
    const hkSweptTransform* m_swept;  // 0x40
    hkReal       m_0x44;        // 0x44
    hkReal       m_0x48;        // 0x48
    hkReal       m_0x4c;        // 0x4c
    hkTransform_s0111_2230  m_0x50;        // 0x50  rows at +0x60/+0x70, translation at +0x80
};
struct hk4dGskTolerances
{
    hkReal m_0x00;              // 0x00
    hkReal m_0x04;              // 0x04
    hkReal m_0x08;              // 0x08
    hkReal m_0x0c;              // 0x0c
    hkReal m_0x10;              // 0x10  radial tolerance
};
struct hk4dGskVertexCollidePointsOutput
{
    hkReal m_0x00;              // 0x00  smallest hit distance seen
};
struct hk4dGskCollideMatrices
{
    hkTransform_s0111_2230 m_0x00;         // 0x00  interpolated first vertex frame
    hkTransform_s0111_2230 m_0x40;         // 0x40  interpolated second vertex frame
    hkTransform_s0111_2230 m_0x80;         // 0x80  first^-1 * second
    hkVector4_s0111_2230   m_0xc0;         // 0xc0  collide direction, .w = -in.m_0x14
    hkVector4_s0111_2230   m_0xd0;         // 0xd0  collide origin
    hkVector4_s0111_2230   m_0xe0;         // 0xe0  second vertex, relative to the collide frame
    hkVector4_s0111_2230   m_0xf0;         // 0xf0  first vertex rows difference
    hkVector4_s0111_2230   m_0x100;        // 0x100 first vertex translation in the collide frame
};
float __cdecl hk4dGskCollidePointWithPlaneFinal(const hk4dGskVertexCollidePointsInput& in,
                                                const hk4dGskTolerances& tol,
                                                const hkVector4_s0111_2230& point,
                                                hkReal tA, hkReal tB,
                                                hkReal time, hkReal dist, hkReal slope,
                                                hk4dGskVertexCollidePointsOutput& out);
// ---- items of slice s01112230 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __cdecl hk4dGskCollideInitMatrices(const hk4dGskVertexCollidePointsInput& in, hkReal t, hk4dGskCollideMatrices& out);  // 0x01112230 (stays in the slice: not this object's)

// ---- items of slice s01112950 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
extern "C" unsigned __int64 __rdtsc();
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern unsigned long g_hkThreadMemoryTls;           // 0x016e4174
extern const char g_hkTimerEndTag0[];               // 0x0143cd94
#pragma intrinsic(__rdtsc)
typedef unsigned char  hkUchar;
typedef signed char    hkInt8;
typedef unsigned short hkUint16;
typedef unsigned int   hkUint32;
typedef float          hkTime;
class __declspec(align(16)) hkVector4_s0111_2950 { public: float x, y, z, w; };
class hkRotation_s0111_2950 { public: hkVector4_s0111_2950 m_col0, m_col1, m_col2; };
class hkTransform_s0111_2950
{
public:
    hkRotation_s0111_2950 m_rotation;       // +0x00
    hkVector4_s0111_2950  m_translation;    // +0x30
    void setMulInverseMul(const hkTransform_s0111_2950& bTa, const hkTransform_s0111_2950& bTc);   // 0x010810f0
};
class __declspec(align(16)) hkVector4M : public hkVector4_s0111_2950
{
public:
    void setTransformedPos(const hkTransform_s0111_2950& t, const hkVector4_s0111_2950& p);   // 0x01081360
    void setRotatedDir(const hkRotation_s0111_2950& r, const hkVector4_s0111_2950& d);        // 0x010814a0
};
class hkSweptTransform_s0111_2950
{
public:
    hkVector4_s0111_2950 m_centerOfMass0;      // +0x00 (w: start time)
    hkVector4_s0111_2950 m_centerOfMass1;      // +0x10 (w: inverse delta time)
    hkVector4_s0111_2950 m_rotation0;          // +0x20
    hkVector4_s0111_2950 m_rotation1;          // +0x30
    hkVector4_s0111_2950 m_centerOfMassLocal;  // +0x40
};
class hkMotionState
{
public:
    hkTransform_s0111_2950      m_transform;         // +0x00
    hkSweptTransform_s0111_2950 m_sweptTransform;    // +0x40
    hkVector4_s0111_2950        m_deltaAngle;        // +0x90
    float            m_objectRadius;      // +0xa0
};
namespace hkSweptTransformUtil {
void lerp2Ha(const hkSweptTransform_s0111_2950& sweptTrans, hkReal t, hkReal deltaTime, hkTransform_s0111_2950& out);   // 0x01209f50
}
class hkSphere { public: hkVector4_s0111_2950 m_pos; };
class hkConvexShape
{
public:
    struct CollisionSpheresInfo { int m_numSpheres; int m_pad[3]; };
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual void getCollisionSpheresInfo(CollisionSpheresInfo& info) const;                       // +0x1c
    virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;                     // +0x20
    virtual void v9();
    virtual void getSupportingVertices(const hkUint16* ids, int numIds, hkVector4_s0111_2950* verticesOut) const;   // +0x28
    float m_pad[2];
    float m_radius;      // +0xc
};
class hkCdBody_s0111_2950
{ public:
    const hkConvexShape* m_shape;   // +0x0
    hkUint32             m_shapeKey;
    const hkMotionState* m_motion;  // +0x8
    const hkCdBody_s0111_2950*      m_parent;  // +0xc
};
class hkStepInfo_s0111_2950
{ public:
    hkTime m_startTime;      // +0x0
    hkTime m_endTime;        // +0x4
    hkReal m_deltaTime;      // +0x8
    hkReal m_invDeltaTime;   // +0xc
};
struct hkCollisionQualityInfo_s0111_2950
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
struct hkProcessCollisionInput_s0111_2950
{
    void*  m_dispatcher;                                  // +0x00
    void*  m_filter;                                      // +0x04
    float  m_tolerance;                                   // +0x08
    char   m_createPredictiveAgents;                      // +0x0c
    hkStepInfo_s0111_2950 m_stepInfo;                                // +0x10
    void*  m_config;                                      // +0x20
    void*  m_dynamicsInfo;                                // +0x24
    const hkCollisionQualityInfo_s0111_2950* m_collisionQualityInfo; // +0x28
};
class hkContactPoint_s0111_2950
{
public:
    hkVector4_s0111_2950 m_position;           // +0x00
    hkVector4_s0111_2950 m_separatingNormal;   // +0x10 (w: distance)
};
class hkContactPointMaterial { public: void* m_userData; hkUint16 m_friction; hkUchar m_restitution; hkUchar m_flags; };
class hkContactMgr
{
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual int addToi(const hkCdBody_s0111_2950& a, const hkCdBody_s0111_2950& b, const hkProcessCollisionInput_s0111_2950& input,
                       hkContactPoint_s0111_2950& cp, hkTime toi, hkReal separatingVelocity,
                       hkContactPointMaterial& materialOut);                                       // +0x1c
};
struct hkAgent3ProcessInput
{
    const hkCdBody_s0111_2950*                m_bodyA;          // +0x00
    const hkCdBody_s0111_2950*                m_bodyB;          // +0x04
    const hkProcessCollisionInput_s0111_2950* m_input;          // +0x08
    hkContactMgr*                  m_contactMgr;     // +0x0c
    hkTransform_s0111_2950                    m_aTb;            // +0x10
    float                          m_distAtT1;       // +0x50
    hkVector4_s0111_2950                      m_linearTimInfo;  // +0x60
};
struct hkProcessCdPoint { hkUint32 m_data[12]; };
struct hkProcessCollisionOutput
{
    hkProcessCdPoint*      m_firstFreeContactPoint;     // +0x0000
    hkContactPoint_s0111_2950         m_toiContactPoint;           // +0x0010
    hkProcessCdPoint       m_contactPoints[256];        // +0x0030
    float                  m_toiSeperatingVelocity;     // +0x3030
    hkTime                 m_toi;                       // +0x3034
    hkContactPointMaterial m_toiMaterial;               // +0x3038
};
struct hkGskCache
{
    hkUint16 m_vertices[4];   // +0x0
    hkInt8   m_dimA;          // +0x8
    hkInt8   m_dimB;          // +0x9
    hkInt8   m_maxDimA;       // +0xa
    hkInt8   m_maxDimB;       // +0xb
};
class __declspec(align(16)) hkGsk
{
public:
    int       m_dimA;               // +0x000
    int       m_dimB;               // +0x004
    int       m_maxDimA;            // +0x008
    int       m_maxDimB;            // +0x00c
    bool      m_doNotHandlePenetration;   // +0x010
    int       m_featureChange;      // +0x014
    hkVector4_s0111_2950 m_verticesA[4];       // +0x020
    hkVector4_s0111_2950 m_verticesTmp[4];     // +0x060
    hkVector4_s0111_2950 m_verticesBinA[4];    // +0x0a0
    hkVector4_s0111_2950 m_verticesB[4];       // +0x0e0
    hkVector4_s0111_2950 m_tmp;                // +0x120
    hkVector4_s0111_2950 m_closestPointA;      // +0x130
    hkVector4_s0111_2950 m_pad[4];

    // returns the separating normal in A space (w = distance)
    void getClosestPoint(const hkConvexShape* shapeA, const hkConvexShape* shapeB,
                         const hkTransform_s0111_2950& aTb, hkVector4_s0111_2950& normalOut);          // 0x0110e510
    void checkForChangesAndUpdateCache(hkGskCache& cache);                       // 0x0110cd00
};
struct __declspec(align(16)) hk4dGskVertexCollidePointsInput_s0111_2950
{
    const hkMotionState* m_motionA;      // +0x00
    const hkMotionState* m_motionB;      // +0x04
    hkSphere*            m_vertices;     // +0x08 (shape A collision spheres, stack allocated)
    int                  m_numVertices;  // +0x0c
    int                  m_allocated;    // +0x10
    float                m_radiusSum;    // +0x14
    float                m_maxAngularDist;      // +0x18
    float                m_invMaxAngularDist;   // +0x1c
    hkVector4_s0111_2950            m_planeNormalInB;      // +0x20
    hkVector4_s0111_2950            m_pointInB;            // +0x30
    const hkStepInfo_s0111_2950*    m_stepInfo;            // +0x40
    float                m_approachVelocity;    // +0x44
    float                m_pad48[2];
    hkVector4_s0111_2950            m_linearTimInfo;       // +0x50
    hkVector4_s0111_2950            m_deltaAngle[2];       // +0x60 (A), +0x70 (B), scaled to one step
    float                m_startT;              // +0x80
};
struct hk4dGskTolerances_s0111_2950
{
    float m_toiSeparation;       // +0x00
    float m_minSeparation;       // +0x04
    float m_minSafeDeltaTime;    // +0x08 (normalized to the step)
    float m_minToiDeltaTime;     // +0x0c
    float m_toiAccuracy;         // +0x10
};
extern void __cdecl hk4dGskCollidePointsWithPlane(const hk4dGskVertexCollidePointsInput_s0111_2950& input,
                                                  const hk4dGskTolerances_s0111_2950& tol, float& toiInOut);   // 0x01112600
extern void __cdecl hkGsk_getClosestPointFromSimplex(const hkVector4_s0111_2950* verticesA, const hkVector4_s0111_2950* verticesBinA,
                                                     int dimA, int dimB, const hkVector4_s0111_2950& direction,
                                                     hkVector4_s0111_2950& pointOut, hkVector4_s0111_2950& normalOut);     // 0x0110d1d0
extern float __cdecl hkGsk_calcSeparatingVelocity(const hkVector4_s0111_2950* deltaAngles, const hkVector4_s0111_2950& normal,
                                                  const hkVector4_s0111_2950& position, const hkMotionState* motionA,
                                                  const hkMotionState* motionB, hkTime toi);
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
class hkThreadMemory
{
public:
virtual void v0();
virtual void v1();
virtual void v2();
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
#define HK_XFORM_ONE(D, S) { \
        const float x = (S).x, y = (S).y, z = (S).z; \
        (D).x = (m20 * z + m10 * y + m00 * x) + tx; \
        (D).y = (m21 * z + m11 * y + m01 * x) + ty; \
        (D).z = (m22 * z + m12 * y + m02 * x) + tz; \
        (D).w = 0.0f; }
static __forceinline void transformPoints(const hkTransform_s0111_2950& t, const hkVector4_s0111_2950* in, int n, hkVector4_s0111_2950* out)
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
        const hkVector4_s0111_2950* s = in;
        hkVector4_s0111_2950* d = out;
        do {
            HK_XFORM_ONE(d[0], s[0]) HK_XFORM_ONE(d[1], s[1]) HK_XFORM_ONE(d[2], s[2]) HK_XFORM_ONE(d[3], s[3])
            s += 4; d += 4;
        } while (--blocks);
    }
    for (; i < n; ++i)
        HK_XFORM_ONE(out[i], in[i])
}
namespace __equiv_ann1 {
struct hkVector4M {
    void setRotatedDir();   // 0x010814a0 (equiv t2)
    void setTransformedPos();   // 0x01081360 (equiv t2)
};
}
// ---- items of slice s01112950 end

// ---- items of slice s01114370 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kZero;   // 0x01485378
extern const float kOne;    // 0x01485720
class hkBool_s0111_4370 { public:
    char m_bool;
    hkBool_s0111_4370() {}
    hkBool_s0111_4370(bool b) : m_bool((char)b) {}
    operator bool() const { return m_bool != 0; }
};
class hkOstream_s0111_4370 { public:
    hkOstream_s0111_4370(void* mem, int memSize, hkBool_s0111_4370 isString);   // 0x0107EF80
    ~hkOstream_s0111_4370();                                         // 0x0107EFD0
    hkOstream_s0111_4370& operator<<(const char* s);                 // 0x0107EE30
    uint32_t m_impl[3];
};
struct hkErrorIface {
    virtual void v0();
    virtual void v1();
    virtual void message(int msg, int id, const char* desc, const char* file, int line) = 0;
};
extern hkErrorIface* g_hkError;   // 0x016E4184
struct hkMoppShape {
    virtual void v0();
    virtual void v1();
    virtual int getType() = 0;
};
struct hkMoppContainer {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual hkMoppShape* getChildShape(int key, void* buffer) = 0;   // slot 10 (+0x28)
};
struct hkMoppChildRef {
    hkMoppShape* m_shape;
    int m_key;
    uint32_t m_a;
    uint32_t m_b;
};
struct hkMoppFilter {
    virtual hkBool_s0111_4370 check(void* a, void* b, void* c, hkMoppContainer* container, int key) = 0;
};
struct hkMoppDispatch {
    char pad[4];
    hkMoppFilter* m_filter;   // +4
};
typedef void (__cdecl *hkMoppHitFn)(void*, hkMoppChildRef*, void*, void*, void*);
struct hkMoppXform {
    __declspec(align(16)) float o[4];   // +0x00 offset (aligns the struct to 16)
    float f[5];            // +0x10 scale factors / extents (+0x20 used as the diagonal term)
    int   m_idx;           // +0x24
    float m_scale;         // +0x28
    int   m_primOffset;    // +0x2c
    uint32_t m_prop[4];    // +0x30 properties
    void assign(const hkMoppXform& o);   // 0x01114310
};
struct hkMoppQueryInput {
    float p[8];            // +0x00 start, +0x10 end
    char pad[0x10];
    hkMoppDispatch* m_a;   // +0x30
    void* m_b;             // +0x34
    char** m_c;            // +0x38
};
struct hkMoppRayInfo {
    char pad[0x10];
    float v[4];            // +0x10
};
struct hkMoppAabbCastVirtualMachine {
    char pad0[0x10];
    hkMoppRayInfo* m_info;      // +0x10
    float m_errScale;           // +0x14
    int   m_axisIdx;            // +0x18
    float m_frac;               // +0x1c
    float m_best;               // +0x20
    struct Hit { uint32_t a; float frac; }* m_hit;   // +0x24
    void* m_out;                // +0x28
    hkMoppQueryInput* m_in;     // +0x2c

    void cast(const hkMoppXform* xf, const uint8_t* pc, float* seg);   // 0x01114370
};
// ---- items of slice s01114370 end

// ---- items of slice s01115400 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_vecZero[3];
typedef unsigned char uchar;
typedef unsigned short ushort;
struct hkBool_s0111_5400
{
    uchar m_bool;
    hkBool_s0111_5400(uchar b) : m_bool(b) {}
    hkBool_s0111_5400(const hkBool_s0111_5400& o) : m_bool(o.m_bool) {}
    operator uchar() const { return m_bool; }
};
struct hkVector4_s0111_5400
{
    float x, y, z, w;

    hkVector4_s0111_5400 Sub(const hkVector4_s0111_5400& other) const;      // 011159c0
};
struct hkGeomConvexHullBuilder
{
    static hkBool_s0111_5400 vectorLessAndMergeCoordinates(hkVector4_s0111_5400& a, hkVector4_s0111_5400& b);   // 01115950
    static void getAabb(const struct hkArrayVector4& verts, struct hkAabb_s0111_5400& aabb); // 01115d00
    static void convertFromUnitCube(struct hkArrayVector4& verts, hkVector4_s0111_5400& scale,
                                    hkVector4_s0111_5400& translation);                   // 01116050
};
typedef hkBool_s0111_5400 (*hkVector4Less)(hkVector4_s0111_5400&, hkVector4_s0111_5400&);
struct WeightedNeighbour
{
    float m_weight;
    float m_key;
};
typedef hkBool_s0111_5400 (*WeightedNeighbourLess)(const WeightedNeighbour&, const WeightedNeighbour&);
struct HullPlane
{
    hkVector4_s0111_5400 m_plane;
    float m_dist;
};
typedef hkBool_s0111_5400 (*HullPlaneLess)(const HullPlane&, const HullPlane&);
struct hkArrayVector4
{
    hkVector4_s0111_5400* m_data;
    int m_size;
    int m_capacity;
};
struct hkAabb_s0111_5400
{
    hkVector4_s0111_5400 m_min;
    hkVector4_s0111_5400 m_max;
};
struct hkMatrix3_s0111_5400
{
    hkVector4_s0111_5400 m_row[3];

    void mul(const hkMatrix3_s0111_5400& other);
};
struct hkCdPointCollector_s0111_5400;
struct hkAabbCastInput
{
    hkVector4_s0111_5400 m_aabb[2];      // 0x00 .. 0x1f
    float     m_pad[6];       // 0x20 .. 0x37
    void*     m_objA;         // 0x38
    void*     m_shape;        // 0x3c
};
struct hkMoppAabbCastVirtualMachine_s0111_5400
{
    char      m_pad0[0x10];
    void*     m_mopp;         // 0x10
    float     m_invScale;     // 0x14
    void*     m_param18;      // 0x18
    float     m_f1c;          // 0x1c
    float     m_f20;          // 0x20
    void*     m_collector;    // 0x24
    void*     m_collector2;   // 0x28
    const hkAabbCastInput* m_input;   // 0x2c
    void*     m_mopp_at_0x20; // mopp bytecode pointer

    void aabbCast(const hkAabbCastInput& input, hkCdPointCollector_s0111_5400& collector,
                  hkCdPointCollector_s0111_5400* collector2);

    void m_step(const hkVector4_s0111_5400* offset, const uchar* code, hkVector4_s0111_5400* points); // 01114370
};
typedef void* (__thiscall* HkVtFunc)(void*);
__forceinline HkVtFunc Vt(void* obj, int index)
{
    return ((HkVtFunc*)(*(void***)obj))[index];
}
static uchar s_moppMemReady;                 // 0x016e5ac1
extern uchar hkThreadMemoryInit(int requirement);
struct hkGeomEdge
{
    ushort m_vertex;   // +0
    ushort m_twin;     // +2 (index of the opposite half-edge)
    ushort m_next;     // +4
    ushort m_pad;      // +6
};
#define TWIN(e) (edges[(e)->m_twin].m_vertex)
// ---- items of slice s01115400 end

// ---- items of slice s01117840 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned long g_hkThreadMemoryTlsIndex;   // 0x016E4174 (hkThreadMemory::s_threadMemoryInstance TLS slot)
#ifdef _WIN32
#endif
class hkBool_s0111_7840
{
public:
	hkBool_s0111_7840() {}
	hkBool_s0111_7840(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
	char m_bool;
};
enum { HK_MEMORY_CLASS_ARRAY = 0x14 };
class hkThreadMemory_s0111_7840
{
public:
	void* allocateChunk(int nbytes, int memClass);               // 0x0107DAA0
	void deallocateChunk(void* p, int nbytes, int memClass);     // 0x0107DB10
	static hkThreadMemory_s0111_7840& getInstance() { return *(hkThreadMemory_s0111_7840*)TlsGetValue(g_hkThreadMemoryTlsIndex); }
};
struct hkArrayUtil
{
	static void _reserveMore(void* array, int sizeElem);   // 0x0107F530
};
template <class T>
class hkArray
{
public:
	enum { CAPACITY_MASK = 0x3FFFFFFF, DONT_DEALLOCATE_FLAG = (int)0x80000000 };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	__forceinline hkArray(int size, const T& fill)
		: m_data((T*)hkThreadMemory_s0111_7840::getInstance().allocateChunk(size * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY)),
		  m_size(size), m_capacityAndFlags(size)
	{
		for (int i = 0; i < size; i++)
			m_data[i] = fill;
	}
	~hkArray()
	{
		if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
			hkThreadMemory_s0111_7840::getInstance().deallocateChunk(m_data, getCapacity() * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
	}
	int getSize() const { return m_size; }
	int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
	T& operator[](int i) { return m_data[i]; }
	const T& operator[](int i) const { return m_data[i]; }
	void clear() { m_size = 0; }
	void pushBack(const T& e)
	{
		if (m_size == getCapacity())
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		m_data[m_size++] = e;
	}
	T& expandOne()
	{
		if (m_size == getCapacity())
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		return m_data[m_size++];
	}
};
#define HK_REAL_MAX 3.40282e+38f
__forceinline float hkMath_sqrt(float r) { return (float)sqrt((double)r); }       // hkMath::sqrt (inline fsqrt)
__forceinline float hkMath_sqrtInverse(float r) { return kOne / hkMath_sqrt(r); }  // hkMath::sqrtInverse
__forceinline float hkMath_fabs(float r) { return (float)fabs((double)r); }        // hkMath::fabs
struct __declspec(align(16)) hkVector4_s0111_7840
{
	float x, y, z, w;

	__forceinline void set(float a, float b, float c, float d) { x = a; y = b; z = c; w = d; }
	__forceinline void setSub4(const hkVector4_s0111_7840& a, const hkVector4_s0111_7840& b) { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
	__forceinline void setNeg4(const hkVector4_s0111_7840& a) { x = -a.x; y = -a.y; z = -a.z; w = -a.w; }
	__forceinline void add4(const hkVector4_s0111_7840& a) { x += a.x; y += a.y; z += a.z; w += a.w; }
	__forceinline void add3clobberW(const hkVector4_s0111_7840& a) { x += a.x; y += a.y; z += a.z; }
	__forceinline void setCross(const hkVector4_s0111_7840& a, const hkVector4_s0111_7840& b)
	{
		const float nx = a.y * b.z - a.z * b.y;
		const float ny = a.z * b.x - a.x * b.z;
		const float nz = a.x * b.y - a.y * b.x;
		w = 0.0f;
		x = nx;
		y = ny;
		z = nz;
	}
	__forceinline void mul4(float s) { x = x * s; y = y * s; z = z * s; w = w * s; }
	__forceinline float dot3(const hkVector4_s0111_7840& a) const { return x * a.x + y * a.y + z * a.z; }
	__forceinline float lengthSquared3() const { return x * x + y * y + z * z; }
	__forceinline float length3() const { return hkMath_sqrt(lengthSquared3()); }
	__forceinline void normalize3()
	{
		const float len2 = lengthSquared3();
		const float inv = (len2 != kZero) ? kOne / hkMath_sqrt(len2) : kZero;
		mul4(inv);
	}
	// Plane through p with this (unit) normal: w = -n.p
	__forceinline void setPlaneDistance(const hkVector4_s0111_7840& p) { w = -dot3(p); }
};
class hkGeomConvexHullBuilder_s0111_7840
{
public:
	static void generateHullFromPlanarPoints(const hkVector4_s0111_7840& normal, const hkVector4_s0111_7840* points, int numPoints,
		hkArray<hkVector4_s0111_7840>& usedPoints, hkArray<hkVector4_s0111_7840>& planeEquations);
	static void removeCollinearVertices(hkArray<hkVector4_s0111_7840>& verts, float tolerance);   // 0x01118340
	static void removeFlaggedVertices(hkArray<hkVector4_s0111_7840>& verts);                      // 0x01117140
};
static __forceinline void makeSidePlane(hkVector4_s0111_7840& plane, const hkVector4_s0111_7840& outside, const hkVector4_s0111_7840& p)
{
	const float sign = (plane.dot3(outside) < 1e-6f) ? -1.0f : kOne;
	plane.mul4(sign);
	plane.normalize3();
	plane.setPlaneDistance(p);
}
// ---- items of slice s01117840 end

// ---- items of slice s011187d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class hkBool_s0111_87d0
{
public:
	hkBool_s0111_87d0() {}
	hkBool_s0111_87d0(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
	char m_bool;
};
class hkThreadMemory_s0111_87d0
{
public:
	void deallocateChunk(void* p, int nbytes, int memClass);   // 0x0107DB10
	static hkThreadMemory_s0111_87d0& getInstance() { return *(hkThreadMemory_s0111_87d0*)TlsGetValue(g_hkThreadMemoryTlsIndex); }
};
struct hkArrayUtil_s0111_87d0
{
	static void _reserveMore(void* array, int sizeElem);                   // 0x0107F530
	static void _reserveExactly(void* array, int numElem, int sizeElem);   // 0x0107F4A0
};
template <class T>
class hkArray_s0111_87d0
{
public:
	enum { CAPACITY_MASK = 0x3FFFFFFF, DONT_DEALLOCATE_FLAG = (int)0x80000000 };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	hkArray_s0111_87d0() : m_data(0), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}
	~hkArray_s0111_87d0()
	{
		if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
			hkThreadMemory_s0111_87d0::getInstance().deallocateChunk(m_data, getCapacity() * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
	}
	int getSize() const { return m_size; }
	int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
	T& operator[](int i) { return m_data[i]; }
	const T& operator[](int i) const { return m_data[i]; }
	void pushBack(const T& e)
	{
		if (m_size == getCapacity())
			hkArrayUtil_s0111_87d0::_reserveMore(this, (int)sizeof(T));
		m_data[m_size++] = e;
	}
	void reserveFor(int n)
	{
		const int cap = getCapacity();
		if (cap < n)
		{
			int cap2 = cap + cap;
			int newSize = (n < cap2) ? cap2 : n;
			hkArrayUtil_s0111_87d0::_reserveExactly(this, newSize, (int)sizeof(T));
		}
	}
	T* expandBy(int n)
	{
		int oldSize = m_size;
		int newSize = oldSize + n;
		reserveFor(newSize);
		m_size = newSize;
		return m_data + oldSize;
	}
	T& expandOne() { return *expandBy(1); }
};
struct __declspec(align(16)) hkVector4_s0111_87d0
{
	float x, y, z, w;

	__forceinline void setSub4(const hkVector4_s0111_87d0& a, const hkVector4_s0111_87d0& b) { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
	__forceinline void setCross(const hkVector4_s0111_87d0& a, const hkVector4_s0111_87d0& b)
	{
		const float nx = a.y * b.z - a.z * b.y;
		const float ny = a.z * b.x - a.x * b.z;
		const float nz = a.x * b.y - a.y * b.x;
		w = 0.0f;
		x = nx;
		y = ny;
		z = nz;
	}
	__forceinline void mul4(float s) { x = x * s; y = y * s; z = z * s; w = w * s; }
	__forceinline float dot3(const hkVector4_s0111_87d0& a) const { return x * a.x + y * a.y + z * a.z; }
	__forceinline float lengthSquared3() const { return x * x + y * y + z * z; }
	__forceinline void normalize3()
	{
		const float len2 = lengthSquared3();
		const float inv = (len2 == kZero) ? kZero : kOne / hkMath_sqrt(len2);
		mul4(inv);
	}
};
struct hkGeomEdge_s0111_87d0
{
	uint16_t m_vertex;    // +0
	uint16_t m_twin;      // +2 (index of the opposite half-edge)
	uint16_t m_next;      // +4 (next half-edge of the face)
	uint16_t m_visited;   // +6 (scratch flag, name guessed)
};
struct hkGeomHull
{
	hkVector4_s0111_87d0* m_vertices;            // +0
	hkArray_s0111_87d0<hkGeomEdge_s0111_87d0> m_edges;      // +4
};
struct hkGeomConvexHullTolerances
{
	hkBool_s0111_87d0 m_removeRedundant;         // +0 (name guessed): the whole pass is skipped when clear
	char m_pad1[7];
	float m_collinearTolSq;           // +8 (name guessed): |cross|^2 below it = on the line
	float m_coplanarTol;              // +0xc (name guessed): normals within 1 - tol of their average = flat
};
// ---- items of slice s011187d0 end

// ---- items of slice s01118f50 begin (TODO(rewrite): local stubs, replace by canonical classes)
class hkBool_s0111_8f50
{
public:
	hkBool_s0111_8f50() {}
	hkBool_s0111_8f50(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
	char m_bool;
};
class hkThreadMemory_s0111_8f50
{
public:
	void deallocateChunk(void* p, int nbytes, int memClass);   // 0x0107DB10
	static hkThreadMemory_s0111_8f50& getInstance() { return *(hkThreadMemory_s0111_8f50*)TlsGetValue(g_hkThreadMemoryTlsIndex); }
};
struct hkArrayUtil_s0111_8f50
{
	static void _reserveExactly(void* array, int numElem, int sizeElem);   // 0x0107F4A0
};
template <class T>
class hkArray_s0111_8f50
{
public:
	enum { CAPACITY_MASK = 0x3FFFFFFF, DONT_DEALLOCATE_FLAG = (int)0x80000000 };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	hkArray_s0111_8f50() : m_data(0), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}
	~hkArray_s0111_8f50()
	{
		if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
			hkThreadMemory_s0111_8f50::getInstance().deallocateChunk(m_data, getCapacity() * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
	}
	int getSize() const { return m_size; }
	int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
	T& operator[](int i) { return m_data[i]; }
	const T& operator[](int i) const { return m_data[i]; }
	T* begin() { return m_data; }
	void clear() { m_size = 0; }
	void reserveFor(int n)
	{
		const int cap = getCapacity();
		if (cap < n)
		{
			int cap2 = cap + cap;
			int newSize = (n < cap2) ? cap2 : n;
			hkArrayUtil_s0111_8f50::_reserveExactly(this, newSize, (int)sizeof(T));
		}
	}
	void setSize(int n)
	{
		reserveFor(n);
		m_size = n;
	}
	T* expandBy(int n)
	{
		int oldSize = m_size;
		int newSize = oldSize + n;
		reserveFor(newSize);
		m_size = newSize;
		return m_data + oldSize;
	}
	T& expandOne() { return *expandBy(1); }
};
struct __declspec(align(16)) hkVector4_s0111_8f50
{
	float x, y, z, w;

	__forceinline void setSub4(const hkVector4_s0111_8f50& a, const hkVector4_s0111_8f50& b) { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
	__forceinline void setAdd4(const hkVector4_s0111_8f50& a, const hkVector4_s0111_8f50& b) { x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; w = a.w + b.w; }
	__forceinline void setNeg4(const hkVector4_s0111_8f50& a) { x = -a.x; y = -a.y; z = -a.z; w = -a.w; }
	__forceinline void setNeg3(const hkVector4_s0111_8f50& a) { x = -a.x; y = -a.y; z = -a.z; }
	__forceinline void setCross(const hkVector4_s0111_8f50& a, const hkVector4_s0111_8f50& b)
	{
		const float nx = a.y * b.z - a.z * b.y;
		const float ny = a.z * b.x - a.x * b.z;
		const float nz = a.x * b.y - a.y * b.x;
		w = 0.0f;
		x = nx;
		y = ny;
		z = nz;
	}
	__forceinline void mul4(float s) { x = x * s; y = y * s; z = z * s; w = w * s; }
	__forceinline float dot3(const hkVector4_s0111_8f50& a) const { return x * a.x + y * a.y + z * a.z; }
	__forceinline float lengthSquared3() const { return x * x + y * y + z * z; }
	__forceinline float lengthSquared4() const { return x * x + y * y + z * z + w * w; }
	__forceinline void normalize3()
	{
		const float len2 = lengthSquared3();
		const float inv = (len2 == kZero) ? kZero : kOne / hkMath_sqrt(len2);
		mul4(inv);
	}
	// normalize3 of a cross product the original had just stored: it re-reads the stored (float-rounded)
	// components, while cl here would keep the unrounded x87 values (a 1-ulp difference in the plane).
	__forceinline void normalize3Stored()
	{
		const float x0 = *(volatile float*)&x;
		const float y0 = *(volatile float*)&y;
		const float z0 = *(volatile float*)&z;
		const float len2 = z0 * z0 + y0 * y0 + x0 * x0;
		const float inv = (len2 == kZero) ? kZero : kOne / hkMath_sqrt(len2);
		x = x0 * inv; y = y0 * inv; z = z0 * inv; w = w * inv;
	}
	// Plane through p with this (unit) normal: w = -n.p
	__forceinline void setPlaneDistance(const hkVector4_s0111_8f50& p) { w = -dot3(p); }
};
struct hkGeomEdge_s0111_8f50
{
	uint16_t m_vertex;   // +0
	uint16_t m_twin;     // +2 (index of the opposite half-edge)
	uint16_t m_next;     // +4 (next half-edge of the face)
	uint16_t m_pad;      // +6
};
struct hkGeomHull_s0111_8f50
{
	const hkVector4_s0111_8f50* m_vertices;      // +0
	hkArray_s0111_8f50<hkGeomEdge_s0111_8f50> m_edges;      // +4
};
struct hkGeomConvexHullTolerances_s0111_8f50
{
	char m_pad0[2];
	hkBool_s0111_8f50 m_postFilter;              // +2 (name guessed): when set, opposing faces trigger a planar rebuild
	char m_pad3;
	float m_pad4;
	float m_minNormalLengthSq;        // +8 (name guessed): faces with |n|^2 below it are dropped
	float m_pad0c;
	float m_weldTolerance;            // +0x10 (name guessed): passed to weldXsortedVertices
	float m_pad14;
	float m_opposingPlaneTolerance;   // +0x18 (name guessed): |a + b|^2 below it = opposing planes
};
class hkGeomConvexHullBuilder_s0111_8f50
{
public:
	struct PlaneAndPoints
	{
		hkVector4_s0111_8f50 m_plane;               // +0
		const hkGeomEdge_s0111_8f50* m_edge0;       // +0x10
		const hkGeomEdge_s0111_8f50* m_edge1;       // +0x14
		const hkGeomEdge_s0111_8f50* m_edge2;       // +0x18
		void sort();                     // 0x01116D00
	};

	static hkBool_s0111_8f50 buildPlaneEquations(const hkGeomConvexHullTolerances_s0111_8f50& tolerances, hkGeomHull_s0111_8f50& hull,
		const hkArray_s0111_8f50<hkVector4_s0111_8f50>& usedVertices, hkVector4_s0111_8f50& planarNormal, hkBool_s0111_8f50& planarHullFound,
		hkArray_s0111_8f50<hkVector4_s0111_8f50>& planeEquations, hkArray_s0111_8f50<PlaneAndPoints>& planesAndPoints);

	// 0x01115730 (name guessed): true when face a's edge pair (a0,a1) and face b's edge pair (b0,b1) are shared
	static hkBool_s0111_8f50 sharesEdgePair(const hkGeomEdge_s0111_8f50* edges, const hkGeomEdge_s0111_8f50* a0, const hkGeomEdge_s0111_8f50* b0,
		const hkGeomEdge_s0111_8f50* a1, const hkGeomEdge_s0111_8f50* b1, const PlaneAndPoints& a, const PlaneAndPoints& b);   // 0x01115730
	// 0x01116F90 (name guessed): adds the extra planes for an opposing face pair
	static void addPlanesForOpposingFace(const hkVector4_s0111_8f50& plane, const hkVector4_s0111_8f50& v0, const hkVector4_s0111_8f50& v1,
		const hkVector4_s0111_8f50& v2, hkArray_s0111_8f50<hkVector4_s0111_8f50>& planeEquations);   // 0x01116f90

	static hkBool_s0111_8f50 vectorLessAndMergeCoordinates(hkVector4_s0111_8f50& a, hkVector4_s0111_8f50& b);                   // 0x01115950
	static void weldXsortedVertices(float tolerance, hkArray_s0111_8f50<hkVector4_s0111_8f50>& verts, int& numWelded);   // 0x01116D50
	static void generateHullFromPlanarPoints(const hkVector4_s0111_8f50& normal, const hkVector4_s0111_8f50* points, int numPoints,
		hkArray_s0111_8f50<hkVector4_s0111_8f50>& usedPoints, hkArray_s0111_8f50<hkVector4_s0111_8f50>& planeEquations);                      // 0x01117840
};
struct hkAlgorithm
{
	template <class T, class L>
	static void quickSortRecursive(T* data, int lo, int hi, L less);   // 0x011155B0 (instance for hkVector4)
};
template <> void hkAlgorithm::quickSortRecursive<hkVector4_s0111_8f50, hkBool_s0111_8f50 (*)(hkVector4_s0111_8f50&, hkVector4_s0111_8f50&)>(
	hkVector4_s0111_8f50* data, int lo, int hi, hkBool_s0111_8f50 (*less)(hkVector4_s0111_8f50&, hkVector4_s0111_8f50&));
static inline void sortAndWeld(const hkGeomConvexHullTolerances_s0111_8f50& tolerances, hkArray_s0111_8f50<hkVector4_s0111_8f50>& planeEquations, int& numWelded)
{
	if (planeEquations.getSize() > 1)
		hkAlgorithm::quickSortRecursive<hkVector4_s0111_8f50, hkBool_s0111_8f50 (*)(hkVector4_s0111_8f50&, hkVector4_s0111_8f50&)>(planeEquations.begin(), 0,
			planeEquations.getSize() - 1, hkGeomConvexHullBuilder_s0111_8f50::vectorLessAndMergeCoordinates);
	hkGeomConvexHullBuilder_s0111_8f50::weldXsortedVertices(tolerances.m_weldTolerance, planeEquations, numWelded);
}
// ---- items of slice s01118f50 end

// ---- items of slice s0111b170 begin (TODO(rewrite): local stubs, replace by canonical classes)
class hkBool_s0111_b170
{
public:
	hkBool_s0111_b170() {}
	hkBool_s0111_b170(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
	char m_bool;
};
enum hkResult { HK_SUCCESS = 0, HK_FAILURE = 1 };
inline void* operator new(unsigned int, void* p) { return p; }
class hkThreadMemory_s0111_b170
{
public:
	struct Stack
	{
		char* m_current;   // +0x20
		Stack* m_prev;     // +0x24
		char* m_base;      // +0x28
		char* m_end;       // +0x2c
	};
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void* onStackOverflow(int nbytes);   // slot 3 (+0xc) 0x0107dc10
	virtual void onStackUnderflow(void* p);      // slot 4 (+0x10) 0x0107db90

	uint32_t m_pad4[7];
	Stack m_stack;   // +0x20

	void deallocateChunk(void* p, int nbytes, int memClass);   // 0x0107DB10
	static hkThreadMemory_s0111_b170& getInstance() { return *(hkThreadMemory_s0111_b170*)TlsGetValue(g_hkThreadMemoryTlsIndex); }

	inline void* allocateStack(int nbytesin)
	{
		int actualBytes = (nbytesin + 16) & ~15;
		char* p = m_stack.m_current;
		char* end = p + actualBytes;
		if (end <= m_stack.m_end)
		{
			m_stack.m_current = end;
			return p;
		}
		return onStackOverflow(actualBytes);  // 0x0107dc10 (hkThreadMemory::onStackOverflow)
	}
	inline void deallocateStack(void* p)
	{
		m_stack.m_current = (char*)p;
		if (p == m_stack.m_base)
			onStackUnderflow(p);  // 0x0107db90 (hkThreadMemory::onStackUnderflow)
	}
};
template <class T>
class hkArray_s0111_b170
{
public:
	enum { CAPACITY_MASK = 0x3FFFFFFF, DONT_DEALLOCATE_FLAG = (int)0x80000000 };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	hkArray_s0111_b170() : m_data(0), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}
	hkArray_s0111_b170(T* buffer, int size, int capacity) : m_data(buffer), m_size(size), m_capacityAndFlags(capacity | DONT_DEALLOCATE_FLAG) {}
	~hkArray_s0111_b170()
	{
		if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
			hkThreadMemory_s0111_b170::getInstance().deallocateChunk(m_data, getCapacity() * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
	}
	int getSize() const { return m_size; }
	int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
	T& operator[](int i) { return m_data[i]; }
	const T& operator[](int i) const { return m_data[i]; }
	T* begin() { return m_data; }
	void pushBack(const T& e)
	{
		if (m_size == getCapacity())
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		m_data[m_size++] = e;
	}
	void clear() { m_size = 0; }
};
template <class T, unsigned N>
class hkInplaceArray : public hkArray_s0111_b170<T>
{
public:
	hkInplaceArray(int size = 0) : hkArray_s0111_b170<T>(m_storage, size, N) {}
	T m_storage[N];
};
struct __declspec(align(16)) hkVector4_s0111_b170
{
	float x, y, z, w;

	__forceinline void setSub4(const hkVector4_s0111_b170& a, const hkVector4_s0111_b170& b) { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
	__forceinline void setAdd4(const hkVector4_s0111_b170& a, const hkVector4_s0111_b170& b) { x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; w = a.w + b.w; }
	__forceinline void setCross(const hkVector4_s0111_b170& a, const hkVector4_s0111_b170& b)
	{
		const float nx = a.y * b.z - a.z * b.y;
		const float ny = a.z * b.x - a.x * b.z;
		const float nz = a.x * b.y - a.y * b.x;
		w = 0.0f;
		x = nx;
		y = ny;
		z = nz;
	}
	static __forceinline float invSqrtOrZero(float len2) { return (len2 == kZero) ? kZero : kOne / hkMath_sqrt(len2); }
	__forceinline void mul4(float s) { x = x * s; y = y * s; z = z * s; w = w * s; }
	// The original sums z, y, x (Havok's hkVector4 FPU path); written in that order for /fp:precise.
	__forceinline float lengthSquared3() const { return z * z + y * y + x * x; }
	__forceinline void normalize3()
	{
		mul4(invSqrtOrZero(lengthSquared3()));
	}
};
struct hkGeomEdge_s0111_b170
{
	uint16_t m_vertex;   // +0
	uint16_t m_twin;     // +2
	uint16_t m_next;     // +4
	uint16_t m_pad;      // +6
};
class hkGeomHull_s0111_b170
{
public:
	const hkVector4_s0111_b170* m_vertices;      // +0
	hkArray_s0111_b170<hkGeomEdge_s0111_b170> m_edges;      // +4
};
struct hkGeomConvexHullTolerances_s0111_b170
{
	uint32_t m_pad0[2];
	float m_singleLineTolerance;   // +8 (name guessed): passed to isSingleLine
	uint32_t m_padC[5];
	float m_wrappingTolerance;     // +0x20 (name guessed): seeds hkGeomConvexHullConfig, grown by 10% per stuck round
};
struct hkGeomConvexHullConfig
{
	float m_tolerance;     // +0 (read by addWrappingLines)
	int m_pad4;
	int m_maxIterations;   // +8 (name guessed): stored, never read
};
class hkGeomConvexHullBuilder_s0111_b170
{
public:
	struct WeightedLine
	{
		hkGeomEdge_s0111_b170* m_edgeA;          // +0 (name guessed): edge in hull A
		hkGeomEdge_s0111_b170* m_edgeB;          // +4 (name guessed): edge in hull B
		WeightedLine* m_lastLine;     // +8 (name guessed): the line this one was grown from (0 for the tangent)
		uint16_t m_lastVertex;        // +0xc (name guessed)
		float m_weight;               // +0x10 (sort key)
	};
	struct WeightedNeighbour
	{
		uint32_t m_data[2];
	};
	struct WrappingLine
	{
		uint32_t m_data[4];
	};

	static hkResult mergeHulls(const hkGeomConvexHullTolerances_s0111_b170& tolerances, hkGeomHull_s0111_b170& hullA, hkGeomHull_s0111_b170& hullB,
		hkGeomHull_s0111_b170& mergedHull);

	static hkBool_s0111_b170 isSingleLine(float tolerance, hkGeomHull_s0111_b170& hullA, hkGeomHull_s0111_b170& hullB, hkGeomHull_s0111_b170& mergedHull);   // 0x011161B0
	static void getCommonTangent(hkGeomHull_s0111_b170& hullA, hkGeomHull_s0111_b170& hullB, WeightedLine& line, hkVector4_s0111_b170& normal);   // 0x01116880
	static void findWeightedNeighbours(const hkGeomConvexHullTolerances_s0111_b170& tolerances, hkGeomHull_s0111_b170& hull,
		const hkVector4_s0111_b170& normal, unsigned short lastVertex, const hkGeomEdge_s0111_b170* edge, const hkVector4_s0111_b170* a,
		const hkVector4_s0111_b170* b, hkArray_s0111_b170<WeightedNeighbour>& neighbours);   // 0x0111AEF0
	static void validateNeighbours(const hkGeomConvexHullTolerances_s0111_b170& tolerances, const hkVector4_s0111_b170* vertices,
		const hkVector4_s0111_b170& normal, unsigned short lastVertex, WeightedLine* line, const hkVector4_s0111_b170* a,
		const hkVector4_s0111_b170* b, hkArray_s0111_b170<WeightedNeighbour>& neighboursA, hkArray_s0111_b170<WeightedNeighbour>& neighboursB);   // 0x0111A8A0
	static void addWrappingLines(const hkGeomConvexHullConfig& config, WeightedLine* line,
		hkArray_s0111_b170<WeightedNeighbour>& neighboursA, hkArray_s0111_b170<WeightedNeighbour>& neighboursB,
		hkArray_s0111_b170<WeightedLine>& newLines);   // 0x01117580
	static void findWrapping(hkGeomHull_s0111_b170& hullA, hkGeomHull_s0111_b170& hullB, const hkArray_s0111_b170<WeightedLine>& lines,
		hkArray_s0111_b170<WrappingLine>& wrapping);   // 0x0111B010
	static void stitchHulls(hkGeomHull_s0111_b170& hullA, hkGeomHull_s0111_b170& hullB, hkArray_s0111_b170<WrappingLine>& wrapping,
		hkGeomHull_s0111_b170& mergedHull);   // 0x0111A290
};
hkBool_s0111_b170 weightedLineLess(const hkGeomConvexHullBuilder_s0111_b170::WeightedLine& a, const hkGeomConvexHullBuilder_s0111_b170::WeightedLine& b);
template <> void hkAlgorithm::quickSortRecursive<hkGeomConvexHullBuilder_s0111_b170::WeightedLine,
	hkBool_s0111_b170 (*)(const hkGeomConvexHullBuilder_s0111_b170::WeightedLine&, const hkGeomConvexHullBuilder_s0111_b170::WeightedLine&)>(
	hkGeomConvexHullBuilder_s0111_b170::WeightedLine* data, int lo, int hi,
	hkBool_s0111_b170 (*less)(const hkGeomConvexHullBuilder_s0111_b170::WeightedLine&, const hkGeomConvexHullBuilder_s0111_b170::WeightedLine&));
typedef hkGeomConvexHullBuilder_s0111_b170::WeightedLine WeightedLine;
typedef hkInplaceArray<WeightedLine, 16> LineArray;   // 0x14c bytes, 0x150 on the thread-memory stack
// ---- items of slice s0111b170 end

// ---- items of slice s0111d560 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float __cdecl FUN_0120ac90(float x);                                  // 0x0120ac90  hkFloor
extern int   __cdecl FUN_0120ad30(float x);                                  // 0x0120ad30  hkFloatToInt
extern float g_01488874;   // 0x1488874   0.1f
extern float g_013eb964;   // 0x13eb964  -0.1f
struct MoppCodeWriter
{
    char pad00[0x0c];
    int  cursor;                                  // +0x0c
    void putByte(int b);                          // 0x0111eb70
};
struct MoppNode;
struct MoppCell
{
    int           depth;       // +0x00
    unsigned char flag;        // +0x04
    char          pad05[3];
    int           level;       // +0x08
    struct Span { int lo, hi; };
    Span          span[3];     // +0x0c   per-axis [lo,hi]
    int           cellShift;   // +0x24
    int           cellBase[3]; // +0x28
    int           field34;     // +0x34
    int           field38;     // +0x38
    int           field3c;     // +0x3c
    int           field40;     // +0x40
    int           lo[3];       // +0x44
    int           out[3];      // +0x50

    void FUN_0111cdb0(MoppNode* child);                     // 0x0111cdb0
    void FUN_0111d2b0(MoppNode* child, float* origin);      // 0x0111d2b0
    void FUN_0111d340();                                    // 0x0111d340
};
struct MoppNode
{
    char  pad00[4];
    char  flag04;         // +0x04   leaf flag
    char  pad05[0x0c - 0x05];
    float span[3][2];     // +0x0c..+0x20   per-axis [lo,hi]
    char  pad24[0x39 - 0x24];
    char  flag39;         // +0x39
    char  pad3a[2];
    char  flag3c;         // +0x3c   fully subdivided flag
    char  pad3d[3];
    char  cells[3];       // +0x40..+0x42
    char  pad43[0xb8 - 0x43];
    float* normal;        // +0xb8
    float  planeMin;      // +0xbc
    float  planeMax;      // +0xc0
    char  padc4[0xec - 0xc4];
    MoppNode* childEC;    // +0xec
    MoppNode* childF0;    // +0xf0
};
struct MoppCompiler
{
    char  pad00[0x10];
    void* writer;                                 // +0x10
    char  pad14[4];
    int   maxDepth;                               // +0x18
    char  pad1c[0x30 - 0x1c];
    float origin[3];                              // +0x30
    float sat;                                    // +0x3c
    char  pad40[8];
    float minCell;                                // +0x48
    float scan[3];                                // +0x50

    void putByte(int b);                          // 0x0111eb70
    void FUN_0111d260(int a);                     // 0x0111d260
    char FUN_0111d410(char* out, MoppNode* node, MoppCell* build, MoppCell* in);  // 0x0111d410
    void FUN_0111d450(MoppCell* build, MoppCell* in, char* out);                  // 0x0111d450
    void FUN_0111d7f0(MoppCell* src, MoppCell* above);                            // 0x0111d7f0
    void FUN_0111d8e0(int p2, int p3, int p4, int p5, int p6);                    // 0x0111d8e0
    void FUN_0111db80(MoppNode* node, MoppCell* build, int* outHi, int* outLo);   // 0x0111db80
    int  FUN_0111d560(MoppNode* node, MoppCell* build, MoppCell* in);             // 0x0111d560
};
struct MoppBasis
{
    float v[3];      // +0x00
    float w;         // +0x0c
    float u;         // +0x10
    int   index;     // +0x14
    int   pad18[2];
};
extern MoppBasis g_moppBasis[13];   // 0x016e5ad0
struct MoppBuilder
{
    void*          vtable;      // +0x00
    char           pad04[2];
    unsigned short flags;       // +0x06
    int            field08;     // +0x08
    int            field0c;     // +0x0c
    int            field10;     // +0x10
    char           pad14[0x40 - 0x14];
    float          f40;         // +0x40
    float          f44;         // +0x44
    float          f48;         // +0x48
    char           pad4c[4];
    float          f50;         // +0x50
    float          f54;         // +0x54
    float          f58;         // +0x58
    float          f5c;         // +0x5c
    int            i60;         // +0x60

    void* FUN_0111df20(float* params, int a, int b);   // 0x0111df20
};
// ---- items of slice s0111d560 end

// ---- items of slice s0111ffc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct MoppInterface {
    virtual int  getNumSomething();                      // slot 2 (+8)
    virtual void* getData();                             // slot 3 (+0xc)
    virtual void addShape(const void* shape, int first, int last, int* outA, int* outB);   // slot 4 (+0x10)
    virtual void addShapeRange(const void* shape, int first, int last, int* outA, int* outB); // slot 5 (+0x14)
};
struct MoppChainNode {
    MoppChainNode* m_parent;      // +0
    // +4 (byte) flag written as 0
    uint8_t  m_pad4[8];           // +4 .. +0xc
    uint32_t m_copies[6];         // +0xc .. +0x24   (six dwords copied from the parent)
    uint32_t m_pad24[0x94];       // +0x24 .. +0xb8
    uint32_t m_iB8;               // +0xb8 (compared against a result field)
    float    m_fbc;               // +0xbc (1.0e10)
    float    m_fc4;               // +0xc4 (1.0e6)
    uint8_t  m_padc8[0x24];       // +0xc8 .. +0xec
    MoppChainNode* m_first;       // +0xec
    MoppChainNode* m_last;        // +0xf0
    int32_t  m_primCount;         // +0xf4 (primitives in the list this node covers)
};
struct MoppCompiler_s0111_ffc0 {
    uint8_t           m_pad0[8];      // +0
    void*             m_source;       // +8
    void*             m_scratch;      // +0xc
    MoppChainNode*    m_freeA;        // +0x10
    int32_t           m_freeACount;   // +0x14
    MoppChainNode*    m_freeB;        // +0x18  (a smaller 0xbc-byte node)
    int32_t           m_freeBCount;   // +0x1c
    int32_t           m_i20;          // +0x20
    MoppInterface*    m_ifaceA;       // +0x24
    MoppInterface*    m_ifaceB;       // +0x28
    MoppChainNode*    m_root;         // +0x2c
    int32_t           m_numEntries;   // +0x30
    uint8_t*          m_entries;      // +0x34  (stride 0x20)
    int32_t           m_log2Children; // +0x38

    // 0x0111ffc0: build a node. `side` selects first/last child, `depth` is the recursion level.
    MoppChainNode* buildNode(MoppChainNode* parent, const int* primList, int side, int depth);
    // 0x011202d0: compile entry point.
    MoppChainNode* compile(void* arg0, MoppInterface* ifaceB, int arg2, MoppInterface* ifaceA, void* source, uint32_t* arena);
};
MoppChainNode* hkFun_0111f9e0(MoppChainNode* parent, const int* primList);      // 0x0111f9e0
void  hkFun_0111efb0(MoppChainNode* node);                                       // 0x0111efb0
void  hkFun_0111f4c0(MoppChainNode* node, int* outIdx, float* outDist);          // 0x0111f4c0
void  hkFun_0111faa0(int first, int a, int b, int c);                            // 0x0111faa0
void  hkFun_0111f670(MoppChainNode* node, void* entry, const int* primList, int* a, int b);   // 0x0111f670
void  hkFun_0111f400(const int* primList, MoppChainNode* node);                  // 0x0111f400
void  hkFun_0111fe30(const int* primList, MoppChainNode* node, int depth, int* outA, int* outB);  // 0x0111fe30
// ---- items of slice s0111ffc0 end

// @ 0x01111d90
int __cdecl hkPackedSimplex_InsertVertex(hkPackedSimplex* pSimplex, void* a2, void* a3, void* a4, const hkSimplexKey* pKey, hkGskInsertPoint* pPoint, Simplex5* pSimplex5, hkGskInterface* pInterface, int bReplace)
{
    int result = 4;
    uint16_t packed;
    if (pSimplex->m_numRows == 4)
    {
        int dropped = pSimplex5->SelectVertexToDrop();
        if (dropped == 4)
            return 5;

        pInterface->v10(pSimplex->m_rows[dropped].m_value);

        // the dropped slot takes over the newest row; slot 0 takes row 1
        hkPackedRow* pDropped = &pSimplex->m_rows[dropped];
        if (dropped != 0)
            *pDropped = pSimplex->m_rows[0];
        else
            *pDropped = pSimplex->m_rows[1];

        pSimplex->removeUnusedVertices();

        uint16_t index = pInterface->v08(a2, a3, a4, pPoint);
        packed = index;
        if (index == 0xffff)
        {
            // the manifold replaced the vertex instead: drop the last simplex row and shift
            pSimplex->m_rows[0].m_tail = pSimplex->m_rows[3].m_tail;
            uint8_t  count = (uint8_t)(pSimplex->m_numRows - 1);
            pSimplex->m_numRows = count;
            pSimplex->m_rows[0].m_head = pSimplex->m_rows[3].m_head;
            uint8_t*  pBase = (uint8_t*)pSimplex + count * 8;
            uint32_t* pDst = (uint32_t*)(pBase + 4);
            uint32_t* pSrc = (uint32_t*)(pBase + 0xc);
            int n = ((int)pSimplex->m_numVerticesB + (int)pSimplex->m_numVerticesA - 1) >> 1;
            for (int i = 0; i <= n; ++i)
            {
                *pDst = *pSrc;
                ++pDst;
                ++pSrc;
            }
            pSimplex5->m_v[dropped].setFrom(&pSimplex5->m_v[3].m_position);
            return 6;
        }

        pPoint->m_index = index;
        pSimplex5->m_v[dropped].setFrom(&pPoint->m_position);
        result = dropped;
    }
    else
    {
        if (bReplace != 0 && pKey->m_ids[1] != 3)
        {
            packed = 0xffff;
        }
        else
        {
            packed = pInterface->v08(a2, a3, a4, pPoint);
            if (packed == 0xffff)
                return 5;
        }
        pPoint->m_index = packed;

        // make room in the middle of the packed-value words and append the old row 0
        int n = ((int)pSimplex->m_numVerticesB + (int)pSimplex->m_numVerticesA - 1) >> 1;
        int slot = n + (int)pSimplex->m_numRows * 2;
        uint32_t* pDst = (uint32_t*)((uint8_t*)pSimplex + slot * 4 + 4);
        uint32_t* pSrc = (uint32_t*)((uint8_t*)pSimplex + slot * 4 + 0xc);
        for (int i = n; i >= 0; --i)
        {
            *pDst = *pSrc;
            --pDst;
            --pSrc;
        }
        pSimplex->m_rows[pSimplex->m_numRows] = pSimplex->m_rows[0];
        ++pSimplex->m_numRows;
    }

    // fill row 0 from the key
    pSimplex->m_rows[0].m_id0 = (uint8_t)pKey->m_ids[0];
    pSimplex->m_rows[0].m_id1 = (uint8_t)pKey->m_ids[1];
    pSimplex->m_rows[0].m_value = packed;
    pSimplex->m_rows[0].m_tail = 0;

    // record one packed byte per simplex vertex; the 16-bit values live right after the rows
    uint16_t* pWordValues = pSimplex->wordValues();
    uint8_t* pValues = pSimplex->valueBytes();
    int offset = 0;
    for (int a = 0; a < pKey->m_ids[0]; ++a)
    {
        uint16_t v = pKey->m_values[a];
        int i = 0;
        for (; i < (int)pSimplex->m_numVerticesA; ++i)
            if (pWordValues[i] == v)
                goto foundA;

        {
            int n = (int)pSimplex->m_numVerticesA + (int)pSimplex->m_numVerticesB;
            for (int j = n; j > i; --j)
                pWordValues[j] = pWordValues[j - 1];
            pWordValues[i] = v;
            ++pSimplex->m_numVerticesA;
            offset += 0x10;
        }
    foundA:
        pValues[a] = (uint8_t)(i << 4);
    }
    if (offset)
    {
        for (int r = 1; r < (int)pSimplex->m_numRows; ++r)
        {
            hkPackedRow* pRow = &pSimplex->m_rows[r];
            for (int i = (int)pRow->m_id0; i < (int)pRow->m_id0 + (int)pRow->m_id1; ++i)
            {
                uint8_t value = pRow->m_payload[i];
                value = (uint8_t)(value + (uint8_t)offset);
                pRow->m_payload[i] = value;
            }
        }
    }
    for (int b = 0; b < pKey->m_ids[1]; ++b)
    {
        uint16_t v = pKey->m_values[pKey->m_ids[0] + b];
        int i = (int)pSimplex->m_numVerticesA;
        int n = (int)pSimplex->m_numVerticesA + (int)pSimplex->m_numVerticesB;
        for (; i < n; ++i)
            if (pWordValues[i] == v)
                goto foundB;

        pWordValues[i] = v;
        ++pSimplex->m_numVerticesB;
    foundB:
        pValues[pKey->m_ids[0] + b] = (uint8_t)(i << 4);
    }
    return result;
}

// @ 0x011120a0
static hkReal __forceinline GskContactOffset(const hkGskSolveBody* pBody, hkReal t, const hkVector4_s0111_1330& point, const hkReal* pBasis, const hkVector4_s0111_1330& axis)
{
    hkReal s = (t - pBody->m_start) * pBody->m_invRange;
    hkReal inv = HK_REAL_ONE - s;

    hkVector4_s0111_1330 centre;
    centre.x = inv * pBody->m_p0[0] + s * pBody->m_p1[0];
    centre.y = inv * pBody->m_p0[1] + s * pBody->m_p1[1];
    centre.z = inv * pBody->m_p0[2] + s * pBody->m_p1[2];

    hkVector4_s0111_1330 d;
    d.x = point.x - centre.x;
    d.y = point.y - centre.y;
    d.z = point.z - centre.z;

    hkVector4_s0111_1330 cross;
    cross.x = d.y * pBasis[2] - d.z * pBasis[1];
    cross.y = d.z * pBasis[0] - d.x * pBasis[2];
    cross.z = d.x * pBasis[1] - d.y * pBasis[0];

    hkReal v = cross.x * axis.x + cross.y * axis.y + cross.z * axis.z;
    if (!(v < HK_REAL_ZERO))
        v *= gGskPositiveScale;
    else
        v *= gGskNegativeScale;
    return v;
}

// @ 0x01112600
extern "C" void __cdecl hk4dGskCollidePointsWithPlane(const hk4dGskVertexCollidePointsInput& in, const hkReal* plane, hk4dGskVertexCollidePointsOutput& out)
{
    hk4dGskCollideMatrices m;

    hkReal t    = in.m_0x50.m_translation.x;
    hkReal tEnd = 1.0f;
    hkReal tPrev = t;

    for (;;)
    {
        hk4dGskCollideInitMatrices(in, t, m);

        const hkReal dt = tEnd - t;
        int remaining = in.m_numPoints;
        hkReal* point = in.m_points;
        const hkReal thickness = in.m_0x44;
        hkReal tNext = tEnd;

        if (remaining > 0)
        {
            hkReal* hit = point + 2;
            do
            {
                const hkReal fDist = ((point[0] - m.m_0xd0.x) * m.m_0xc0.x +
                                      (m.m_0xc0.y * (point[1] - m.m_0xd0.y) +
                                       m.m_0xc0.z * (point[2] - m.m_0xd0.z)))
                                     + m.m_0xc0.w;

                // The three guards are written as negated strict comparisons: MSVC's
                // "test ah,5; jnp" idiom tests for an *ordered* less-than, so the body is
                // still entered when an operand is NaN.  Written as `<=`/`>=` the compiler
                // folds "unordered" into the taken branch and the behaviour diverges.
                if (!(dt * thickness + plane[0] < fDist))
                {
                    const hkReal fSlope =
                        ((m.m_0xf0.z * (point[1] - m.m_0x100.y) - m.m_0xf0.y * (point[2] - m.m_0x100.z)) - m.m_0xe0.x) * m.m_0xc0.x +
                        (((m.m_0xf0.x * (point[2] - m.m_0x100.z) - m.m_0xf0.z * (point[0] - m.m_0x100.x)) - m.m_0xe0.y) * m.m_0xc0.y +
                         ((m.m_0xf0.y * (point[0] - m.m_0x100.x) - m.m_0xf0.x * (point[1] - m.m_0x100.y)) - m.m_0xe0.z) * m.m_0xc0.z);

                    if (!(fSlope * dt + (fDist - plane[0]) > ((dt * in.m_0x18) * dt) * 0.5f))
                    {
                        if (fDist < plane[0])
                        {
                            tEnd = hk4dGskCollidePointWithPlaneFinal(in, *(const hk4dGskTolerances*)plane,
                                                                     *(const hkVector4_s0111_2230*)point,
                                                                     tPrev, t, point[3],
                                                                     fDist, fSlope, out);
                        }
                        else
                        {
                            const hkReal s0 = point[0];
                            const hkReal s1 = point[1];
                            const hkReal s2 = point[2];
                            const hkReal s3 = point[3];
                            point[0] = hit[-2];
                            point[1] = hit[-1];
                            point[2] = hit[0];
                            point[3] = hit[1];
                            hit[-2] = s0;
                            hit[-1] = s1;
                            hit[0]  = s2;
                            hit[1]  = s3;
                            hit[1]  = fDist;
                            hit += 4;

                            hkReal d2 = (fDist - plane[1]) * in.m_0x1c;
                            d2 = d2 + d2;
                            if (!(d2 > dt * dt))
                            {
                                const hkReal halfWidth = (plane[0] - plane[1]) * in.m_0x1c;
                                d2 = sqrtf(d2);
                                const hkReal radius = fSlope * in.m_0x1c;
                                if (fSlope < 0.0f)
                                {
                                    if (d2 < -radius)
                                        d2 = -radius;
                                }
                                else
                                {
                                    d2 = (radius + radius) + d2;
                                }

                                if (!(d2 > dt))
                                {
                                    d2 = sqrtf(halfWidth + halfWidth) + d2;
                                    if (!(d2 > plane[2]))
                                        d2 = plane[2];
                                    d2 = d2 + t;
                                    if (!(tNext < d2))
                                        tNext = d2;
                                }
                            }
                        }
                    }
                }

                point += 4;
                remaining--;
            } while (remaining != 0);
        }

        if (tEnd < t || (t == tNext && tEnd <= t))
            break;

        tPrev = t;
        t = tNext;
    }
}

// @ 0x01112950
void __cdecl hkGsk_calcToi(const hkAgent3ProcessInput& input, hkReal allowedPenetrationDepth, hkReal minSeparation, hkReal toiSeparation, hkGskCache& cache, hkVector4_s0111_2950& separatingNormal, hkProcessCollisionOutput& output)
{
    HK_TIMER_BEGIN_LIST("LtToi", "setup");

    // ---- setup ----
    const hkProcessCollisionInput_s0111_2950* pi = input.m_input;
    const hkCollisionQualityInfo_s0111_2950* quality = pi->m_collisionQualityInfo;

    hk4dGskTolerances_s0111_2950 tol;
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

    hk4dGskVertexCollidePointsInput_s0111_2950 vin;
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

    hkVector4_s0111_2950 savedNormal;
    hkTransform_s0111_2950 transA, transB, aTb;
    hkVector4_s0111_2950 localNormal;

    // ---- conservative advancement ----
    while (curDist > distLimit)
    {
        float dt = 1.0f - t;
        if (dt <= 0.0f)
            goto END;

        const hkVector4_s0111_2950& n = separatingNormal;
        float angular;
        {
            const hkVector4_s0111_2950& a = vin.m_deltaAngle[0];
            const hkVector4_s0111_2950& b = vin.m_deltaAngle[1];
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
            const hkStepInfo_s0111_2950& si = pi->m_stepInfo;
            const float time = t * si.m_deltaTime;
            hkSweptTransformUtil::lerp2Ha(motionA->m_sweptTransform, si.m_startTime, time, transA);
            hkSweptTransformUtil::lerp2Ha(motionB->m_sweptTransform, si.m_startTime, time, transB);
        }
        numIter++;
        aTb.setMulInverseMul(transA, transB);
        gsk.getClosestPoint(shapeA, shapeB, aTb, localNormal);

        const hkRotation_s0111_2950& rA = transA.m_rotation;
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
            const hkRotation_s0111_2950& r = aTb.m_rotation;
            vin.m_pointInB.x = dx * r.m_col0.x + dy * r.m_col0.y + dz * r.m_col0.z;
            vin.m_pointInB.y = dx * r.m_col1.x + dy * r.m_col1.y + dz * r.m_col1.z;
            vin.m_pointInB.z = dx * r.m_col2.x + dy * r.m_col2.y + dz * r.m_col2.z;
        }
        separatingNormal.w = (dist - shapeA->m_radius) - shapeB->m_radius;
        {
            const hkRotation_s0111_2950& rB = transB.m_rotation;
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
        hkVector4_s0111_2950 normalOut;
        hkVector4_s0111_2950 point;

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
                const hkStepInfo_s0111_2950& si = pi->m_stepInfo;
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
                hkVector4_s0111_2950 dirA;
                const hkRotation_s0111_2950& rA = transA.m_rotation;
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
        const hkStepInfo_s0111_2950& si = pi->m_stepInfo;
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
        hkContactPoint_s0111_2950 cp;
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
            const hkSweptTransform_s0111_2950& st = mA->m_sweptTransform;
            const float u = (toi - st.m_centerOfMass0.w) * st.m_centerOfMass1.w;
            const float v = 1.0f - u;
            const float rx = cp.m_position.x - (v * st.m_centerOfMass0.x + u * st.m_centerOfMass1.x);
            const float ry = cp.m_position.y - (v * st.m_centerOfMass0.y + u * st.m_centerOfMass1.y);
            const float rz = cp.m_position.z - (v * st.m_centerOfMass0.z + u * st.m_centerOfMass1.z);
            const hkVector4_s0111_2950& a = vin.m_deltaAngle[0];
            vx = (a.y * rz - a.z * ry) + nlx;
            vy = (a.z * rx - a.x * rz) + nly;
            vz = (a.x * ry - a.y * rx) + nlz;
        }
        {
            const hkSweptTransform_s0111_2950& st = mB->m_sweptTransform;
            const float u = (toi - st.m_centerOfMass0.w) * st.m_centerOfMass1.w;
            const float v = 1.0f - u;
            const float rx = cp.m_position.x - (u * st.m_centerOfMass1.x + v * st.m_centerOfMass0.x);
            const float ry = cp.m_position.y - (v * st.m_centerOfMass0.y + u * st.m_centerOfMass1.y);
            const float rz = cp.m_position.z - (v * st.m_centerOfMass0.z + u * st.m_centerOfMass1.z);
            const hkVector4_s0111_2950& b = vin.m_deltaAngle[1];
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

// @ 0x01114370
void hkMoppAabbCastVirtualMachine::cast(const hkMoppXform* xf, const uint8_t* pc, float* seg)
{
    hkMoppXform local;
    for (;;) {
        unsigned op = *pc;
        int axis = 999;
        float lo, hi, p1;
        double p0;   // the original keeps p0 in an x87 register (never rounded to float)
        unsigned skipA, skipB;
        switch (op) {
        case 0:
            return;
        case 1: case 2: case 3: case 4: {
            float x = (float)pc[1];
            float y = (float)pc[2];
            float z = (float)pc[3];
            float s = (float)(1 << op);
            seg[3] = seg[3];
            seg[0] = seg[0] - x;
            seg[1] = seg[1] - y;
            seg[2] = seg[2] - z;
            seg[7] = seg[7];
            seg[4] = seg[4] - x;
            seg[5] = seg[5] - y;
            seg[6] = seg[6] - z;
            seg[0] = s * seg[0];
            seg[1] = s * seg[1];
            seg[2] = s * seg[2];
            seg[3] = s * seg[3];
            seg[4] = s * seg[4];
            seg[5] = s * seg[5];
            seg[6] = s * seg[6];
            seg[7] = s * seg[7];
            local.o[0] = x + xf->o[0];
            local.o[1] = y + xf->o[1];
            local.o[2] = z + xf->o[2];
            local.o[0] = local.o[0] * s;
            local.o[1] = local.o[1] * s;
            local.o[2] = local.o[2] * s;
            local.o[3] = xf->o[3] * s;
            local.m_idx = xf->m_idx + (int)op;
            pc += 4;
            local.m_scale = s * xf->m_scale;
            local.f[0] = s * xf->f[0];
            local.f[1] = s * xf->f[1];
            local.f[2] = s * xf->f[2];
            local.f[3] = s * xf->f[3];
            local.f[4] = s * xf->f[4];
            local.m_prop[0] = xf->m_prop[0];
            local.m_primOffset = xf->m_primOffset;
            xf = &local;
            continue;
        }
        case 5:
            pc += pc[1] + 2;
            continue;
        case 6:
            pc += (unsigned)pc[1] * 0x100 + pc[2] + 3;
            continue;
        case 7:
            pc += ((unsigned)pc[1] * 0x100 + pc[2]) * 0x100 + pc[3] + 4;
            continue;
        case 9: {
            unsigned v = pc[1];
            if (xf != &local) { local.assign(*xf); xf = &local; }
            local.m_primOffset += v;
            pc += 2;
            continue;
        }
        case 10: {
            unsigned v = pc[1] * 0x100 + pc[2];
            if (xf != &local) { local.assign(*xf); xf = &local; }
            local.m_primOffset += v;
            pc += 3;
            continue;
        }
        case 11: {
            unsigned v = ((pc[1] * 0x100 + pc[2]) * 0x100 + pc[3]) * 0x100 + pc[4];
            if (xf != &local) { local.assign(*xf); xf = &local; }
            local.m_primOffset = v;
            pc += 5;
            continue;
        }
        case 0x10: case 0x11: case 0x12:
            axis = op - 0x10;
            lo = (float)pc[2] - xf->f[axis];
            hi = (float)pc[1] + xf->f[axis];
            p0 = seg[axis];
            p1 = seg[axis + 4];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        case 0x13: {
            lo = (float)(pc[2] << 1) - ((xf->f[2] + xf->f[1]) + (xf->f[2] + xf->f[1]));
            hi = (float)(pc[1] << 1) + ((xf->f[2] + xf->f[1]) + (xf->f[2] + xf->f[1]));
            p0 = seg[2] + seg[1];
            p1 = seg[6] + seg[5];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        }
        case 0x14: {
            lo = (float)(int)(pc[2] * 2 - 0xff) - ((xf->f[2] + xf->f[1]) + (xf->f[2] + xf->f[1]));
            hi = (float)(int)(pc[1] * 2 - 0xff) + ((xf->f[2] + xf->f[1]) + (xf->f[2] + xf->f[1]));
            p0 = seg[1] - seg[2];
            p1 = seg[5] - seg[6];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        }
        case 0x15: {
            lo = (float)(pc[2] << 1) - ((xf->f[2] + xf->f[0]) + (xf->f[2] + xf->f[0]));
            hi = (float)(pc[1] << 1) + ((xf->f[2] + xf->f[0]) + (xf->f[2] + xf->f[0]));
            p0 = seg[2] + seg[0];
            p1 = seg[6] + seg[4];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        }
        case 0x16: {
            lo = (float)(int)(pc[2] * 2 - 0xff) - ((xf->f[2] + xf->f[0]) + (xf->f[2] + xf->f[0]));
            hi = (float)(int)(pc[1] * 2 - 0xff) + ((xf->f[2] + xf->f[0]) + (xf->f[2] + xf->f[0]));
            p0 = seg[0] - seg[2];
            p1 = seg[4] - seg[6];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        }
        case 0x17: {
            lo = (float)(pc[2] << 1) - ((xf->f[1] + xf->f[0]) + (xf->f[1] + xf->f[0]));
            hi = (float)(pc[1] << 1) + ((xf->f[1] + xf->f[0]) + (xf->f[1] + xf->f[0]));
            p0 = seg[1] + seg[0];
            p1 = seg[5] + seg[4];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        }
        case 0x18: {
            lo = (float)(int)(pc[2] * 2 - 0xff) - ((xf->f[1] + xf->f[0]) + (xf->f[1] + xf->f[0]));
            hi = (float)(int)(pc[1] * 2 - 0xff) + ((xf->f[1] + xf->f[0]) + (xf->f[1] + xf->f[0]));
            p0 = seg[0] - seg[1];
            p1 = seg[4] - seg[5];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        }
        case 0x19:
            lo = (float)(pc[2] * 3) - xf->f[4];
            hi = (float)(pc[1] * 3) + xf->f[4];
            p0 = seg[2] + seg[1] + seg[0];
            p1 = seg[6] + seg[5] + seg[4];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        case 0x1a:
            lo = (float)(((int)pc[2] - 0x55) * 3) - xf->f[4];
            hi = (float)(((int)pc[1] - 0x55) * 3) + xf->f[4];
            p0 = seg[1] + seg[0] - seg[2];
            p1 = seg[5] + seg[4] - seg[6];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        case 0x1b:
            lo = (float)(((int)pc[2] - 0x55) * 3) - xf->f[4];
            hi = (float)(((int)pc[1] - 0x55) * 3) + xf->f[4];
            p0 = seg[0] - seg[1] + seg[2];
            p1 = seg[4] - seg[5] + seg[6];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        case 0x1c:
            lo = (float)(((int)pc[2] - 0xaa) * 3) - xf->f[4];
            hi = (float)(((int)pc[1] - 0xaa) * 3) + xf->f[4];
            p0 = seg[0] - seg[1] - seg[2];
            p1 = seg[4] - seg[5] - seg[6];
            skipA = pc[3];
            pc += 4;
            skipB = 0;
            break;
        case 0x20: case 0x21: case 0x22:
            axis = op - 0x20;
            lo = (float)pc[1] - xf->f[axis];
            hi = ((float)pc[1] + kOne) + xf->f[axis];
            p0 = seg[axis];
            p1 = seg[axis + 4];
            skipA = pc[2];
            pc += 3;
            skipB = 0;
            break;
        case 0x23: case 0x24: case 0x25:
            axis = op - 0x23;
            lo = (float)pc[2] - xf->f[axis];
            hi = (float)pc[1] + xf->f[axis];
            p0 = seg[axis];
            p1 = seg[axis + 4];
            skipB = (pc[3] << 8) + pc[4];
            skipA = (pc[5] << 8) + pc[6];
            pc += 7;
            break;
        case 0x26: case 0x27: case 0x28:
        case 0x29: case 0x2a: case 0x2b: {
            int a;
            float lo2, hi2, q0, q1;
            if (op < 0x29) {
                a = op - 0x26;
                lo2 = (float)pc[1] - xf->f[a];
                hi2 = (float)pc[2];
                pc += 3;
            } else {
                a = op - 0x29;
                unsigned v1 = ((pc[1] << 8) + pc[2]) * 0x100 + pc[3];
                unsigned v2 = ((pc[4] << 8) + pc[5]) * 0x100 + pc[6];
                lo2 = (((float)(int)v1 * m_errScale) * xf->m_scale - xf->o[a]) - xf->f[a];
                hi2 = ((float)(int)v2 * m_errScale) * xf->m_scale - xf->o[a];
                pc += 7;
            }
            hi2 = hi2 + xf->f[a];
            q0 = seg[a];
            q1 = seg[a + 4];
            int side;
            if (q1 <= q0) {
                if (q0 < lo2) return;
                if (hi2 < q1) return;
                side = 1;
            } else {
                if (q1 < lo2) return;
                if (hi2 < q0) return;
                side = 0;
            }
            __declspec(align(16)) float t0[8];
            t0[0] = seg[0]; t0[1] = seg[1]; t0[2] = seg[2]; t0[3] = seg[3];
            float d = q0 - hi2;
            t0[4] = seg[4]; t0[5] = seg[5]; t0[6] = seg[6]; t0[7] = seg[7];
            if (d * (q1 - hi2) < kZero) {
                float* dst = seg + (4 - side * 4);
                dst[0] = t0[0] * (kOne - (d / (d - (q1 - hi2)))) + t0[4] * (d / (d - (q1 - hi2)));
                dst[1] = t0[1] * (kOne - (d / (d - (q1 - hi2)))) + t0[5] * (d / (d - (q1 - hi2)));
                dst[2] = t0[2] * (kOne - (d / (d - (q1 - hi2)))) + t0[6] * (d / (d - (q1 - hi2)));
                dst[3] = t0[3] * (kOne - (d / (d - (q1 - hi2)))) + t0[7] * (d / (d - (q1 - hi2)));
            }
            d = q0 - lo2;
            if (d * (q1 - lo2) < kZero) {
                float* dst = seg + side * 4;
                dst[0] = t0[0] * (kOne - (d / (d - (q1 - lo2)))) + t0[4] * (d / (d - (q1 - lo2)));
                dst[1] = t0[1] * (kOne - (d / (d - (q1 - lo2)))) + t0[5] * (d / (d - (q1 - lo2)));
                dst[2] = t0[2] * (kOne - (d / (d - (q1 - lo2)))) + t0[6] * (d / (d - (q1 - lo2)));
                dst[3] = t0[3] * (kOne - (d / (d - (q1 - lo2)))) + t0[7] * (d / (d - (q1 - lo2)));
            }
            continue;
        }
        case 0x30: case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x36: case 0x37:
        case 0x38: case 0x39: case 0x3a: case 0x3b: case 0x3c: case 0x3d: case 0x3e: case 0x3f:
        case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45: case 0x46: case 0x47:
        case 0x48: case 0x49: case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4e: case 0x4f:
        case 0x50: case 0x51: case 0x52: case 0x53: {
            unsigned v;
            if (op < 0x50)
                v = op - 0x30;
            else if (op == 0x50)
                v = pc[1];
            else if (op == 0x51)
                v = (pc[1] << 8) + pc[2];
            else if (op == 0x52)
                v = ((pc[1] << 8) + pc[2]) * 0x100 + pc[3];
            else
                v = (((pc[1] << 8) + pc[2]) << 16) + pc[4] + (pc[3] << 8);
            int key = v + xf->m_primOffset;
            hkMoppQueryInput* in = m_in;
            hkMoppContainer* container = (hkMoppContainer*)(*(char***)in->m_c)[3];
            hkMoppDispatch* disp = in->m_a;
            if (!disp->m_filter->check(disp, in->m_b, in->m_c, container, key))
                return;
            char buf[0x100];
            hkMoppChildRef ref;
            ref.m_shape = container->getChildShape(key, buf);
            ref.m_key = key;
            ref.m_a = ((uint32_t*)in->m_c)[2];
            ref.m_b = (uint32_t)in->m_c;
            int type = ref.m_shape->getType();
            char* tbl = *(char**)in->m_a;
            hkMoppHitFn fn = ((hkMoppHitFn*)tbl)[(*(uint8_t*)(tbl + m_axisIdx * 0x20 + 0x190 + type) + 0x7b) * 5];
            fn(in->m_b, &ref, in->m_a, m_hit, m_out);
            m_frac = m_hit->frac;
            return;
        }
        case 0x60: case 0x61: case 0x62: case 0x63: {
            local.m_prop[op - 0x60] = pc[1];
            pc += 2;
            goto setProp;
        }
        case 0x64: case 0x65: case 0x66: case 0x67:
            local.m_prop[op - 0x64] = (pc[1] << 8) + pc[2];
            pc += 3;
            goto setProp;
        case 0x68: case 0x69: case 0x6a: case 0x6b:
            local.m_prop[op - 0x68] = (((pc[1] << 8) + pc[2]) * 0x100 + pc[3]) * 0x100 + pc[4];
            pc += 5;
        setProp: {
            uint32_t p0v = local.m_prop[0];
            if (xf != &local) { local.assign(*xf); xf = &local; }
            local.m_prop[0] = p0v;
            continue;
        }
        default: {
            char buf[0x200];
            hkOstream_s0111_4370 os(buf, 0x200, true);
            os << "Unknown command - This mopp data has been corrupted (check for memory trashing), or an hkMoppBvTreeShape has been pointed at invalid mopp data.\n";
            g_hkError->message(3, 0x1298fedd, buf, ".\\collide\\mopp\\machine\\hkMoppAabbCastVirtualMachine.cpp", 0x1c7);
            continue;
        }
        }

        // interval test on the selected axis / combination
        if (lo <= p1 || lo <= p0) {
            pc += skipA;
            if (p0 <= hi || p1 <= hi) {
                __declspec(align(16)) float t0[8];
                t0[0] = seg[0]; t0[1] = seg[1]; t0[2] = seg[2]; t0[3] = seg[3];
                float d0 = p0 - hi;
                t0[4] = seg[4]; t0[5] = seg[5]; t0[6] = seg[6]; t0[7] = seg[7];
                float d1 = p0 - lo;
                float d2 = p1 - hi;
                float d3 = p1 - lo;
                if (d2 <= d0) {
                    if (d3 * d1 < kZero) {
                        t0[4] = (kOne - (d1 / (d1 - d3))) * seg[0] + (d1 / (d1 - d3)) * seg[4];
                        t0[5] = (d1 / (d1 - d3)) * seg[5] + (kOne - (d1 / (d1 - d3))) * seg[1];
                        t0[6] = (d1 / (d1 - d3)) * seg[6] + (kOne - (d1 / (d1 - d3))) * seg[2];
                        t0[7] = (d1 / (d1 - d3)) * seg[7] + (kOne - (d1 / (d1 - d3))) * seg[3];
                    }
                    cast(xf, pc, t0);
                    if (d2 * d0 < kZero) {
                        seg[0] = (d0 / (d0 - d2)) * seg[4] + (kOne - (d0 / (d0 - d2))) * seg[0];
                        seg[1] = (d0 / (d0 - d2)) * seg[5] + (kOne - (d0 / (d0 - d2))) * seg[1];
                        seg[2] = (d0 / (d0 - d2)) * seg[6] + (kOne - (d0 / (d0 - d2))) * seg[2];
                        seg[3] = (d0 / (d0 - d2)) * seg[7] + (kOne - (d0 / (d0 - d2))) * seg[3];
                    }
                    if (m_frac < m_best) {
                        float* in = m_in->p;
                        m_best = m_frac;
                        __declspec(align(16)) float p[4];
                        p[0] = (kOne - m_frac) * in[0] + m_frac * in[4];
                        p[1] = (kOne - m_frac) * in[1] + m_frac * in[5];
                        p[2] = (kOne - m_frac) * in[2] + m_frac * in[6];
                        const float* base = m_info->v;
                        seg[4] = p[0] - base[0];
                        seg[5] = p[1] - base[1];
                        seg[6] = p[2] - base[2];
                        seg[7] = ((kOne - m_frac) * in[3] + m_frac * in[7]) - base[3];
                        float s = xf->m_scale;
                        seg[4] = s * seg[4];
                        seg[5] = s * seg[5];
                        seg[6] = s * seg[6];
                        seg[7] = s * seg[7];
                        seg[4] = seg[4] - xf->o[0];
                        seg[5] = seg[5] - xf->o[1];
                        seg[6] = seg[6] - xf->o[2];
                        seg[7] = seg[7] - xf->o[3];
                        if (axis < 3 && hi < seg[axis + 4])
                            return;
                    }
                    pc += skipB - skipA;
                } else {
                    if (d2 * d0 < kZero) {
                        t0[4] = (d0 / (d0 - d2)) * seg[4] + (kOne - (d0 / (d0 - d2))) * seg[0];
                        t0[5] = (kOne - (d0 / (d0 - d2))) * seg[1] + (d0 / (d0 - d2)) * seg[5];
                        t0[6] = (kOne - (d0 / (d0 - d2))) * seg[2] + (d0 / (d0 - d2)) * seg[6];
                        t0[7] = (kOne - (d0 / (d0 - d2))) * seg[3] + (d0 / (d0 - d2)) * seg[7];
                    }
                    cast(xf, pc + (skipB - skipA), t0);
                    if (d3 * d1 < kZero) {
                        seg[0] = (kOne - (d1 / (d1 - d3))) * seg[0] + (d1 / (d1 - d3)) * seg[4];
                        seg[1] = (kOne - (d1 / (d1 - d3))) * seg[1] + (d1 / (d1 - d3)) * seg[5];
                        seg[2] = (kOne - (d1 / (d1 - d3))) * seg[2] + (d1 / (d1 - d3)) * seg[6];
                        seg[3] = (kOne - (d1 / (d1 - d3))) * seg[3] + (d1 / (d1 - d3)) * seg[7];
                    }
                    if (m_frac < m_best) {
                        float* in = m_in->p;
                        m_best = m_frac;
                        __declspec(align(16)) float p[4];
                        p[0] = (kOne - m_frac) * in[0] + m_frac * in[4];
                        p[1] = (kOne - m_frac) * in[1] + m_frac * in[5];
                        p[2] = (kOne - m_frac) * in[2] + m_frac * in[6];
                        const float* base = m_info->v;
                        seg[4] = p[0] - base[0];
                        seg[5] = p[1] - base[1];
                        seg[6] = p[2] - base[2];
                        seg[7] = ((kOne - m_frac) * in[3] + m_frac * in[7]) - base[3];
                        float s = xf->m_scale;
                        seg[4] = s * seg[4];
                        seg[5] = s * seg[5];
                        seg[6] = s * seg[6];
                        seg[7] = s * seg[7];
                        seg[4] = seg[4] - xf->o[0];
                        seg[5] = seg[5] - xf->o[1];
                        seg[6] = seg[6] - xf->o[2];
                        seg[7] = seg[7] - xf->o[3];
                        if (axis < 3 && !(seg[axis + 4] >= lo))
                            return;
                    }
                }
            }
        } else {
            pc += skipB;
        }
    }
}

// @ 0x01115400
void hkMoppAabbCastVirtualMachine_s0111_5400::aabbCast(const hkAabbCastInput& input, hkCdPointCollector_s0111_5400& collector, hkCdPointCollector_s0111_5400* collector2)
{
    if (s_moppMemReady == 0 &&
        (s_moppMemReady = hkThreadMemoryInit(4), s_moppMemReady == 0))
        return;

    m_input = &input;

    void* shape = (void*)input.m_shape;
    void* moppVt = *(void**)*(void**)((const char*)&input + 0x38);
    m_mopp = *(void**)((const char*)moppVt + 0x10);

    m_collector = &collector;
    m_collector2 = collector2;

    void* p1 = *(void**)((const char*)&input + 0x34);
    void* shapeObj = *(void**)p1;
    m_param18 = Vt(shapeObj, 2)(shapeObj);

    m_f1c = 1.0f;
    m_f20 = 1.0f;

    const char* m = (const char*)m_mopp;
    m_mopp_at_0x20 = *(void**)(m + 0x20);
    hkVector4_s0111_5400 offset;
    offset.x = 0.0f;
    offset.y = 0.0f;
    offset.z = 0.0f;
    offset.w = 0.0f;

    float w = *(float*)(m + 0x1c);
    m_invScale = 1.0f / w;

    float t = w * 1.5258789e-05f;
    hkVector4_s0111_5400 tmp;
    tmp.x = t * input.m_aabb[1].x;
    tmp.y = t * input.m_aabb[1].y;
    tmp.z = t * input.m_aabb[1].z;
    tmp.w = t * input.m_aabb[1].w;

    float sum = (input.m_aabb[1].z + input.m_aabb[1].y + input.m_aabb[1].x) * 3.0f;

    hkVector4_s0111_5400 pts[2];
    pts[0].x = (input.m_aabb[0].x - *(float*)(m + 0x10)) * t;
    pts[0].y = (input.m_aabb[0].y - *(float*)(m + 0x14)) * t;
    pts[0].z = (input.m_aabb[0].z - *(float*)(m + 0x18)) * t;
    pts[0].w = (input.m_aabb[0].w - *(float*)(m + 0x1c)) * t;
    pts[1].x = (input.m_aabb[1].x - *(float*)(m + 0x10)) * t;
    pts[1].y = (input.m_aabb[1].y - *(float*)(m + 0x14)) * t;
    pts[1].z = (input.m_aabb[1].z - *(float*)(m + 0x18)) * t;
    pts[1].w = (input.m_aabb[1].w - *(float*)(m + 0x1c)) * t;

    (void)shape;
    (void)sum;
    m_step(&offset, (const uchar*)(const char*)m_mopp_at_0x20, pts);
}

// @ 0x011155b0
void quickSortVector4(hkVector4_s0111_5400* base, int lo, int hi, hkVector4Less less)
{
    int i;
    int j;
    do
    {
        hkVector4_s0111_5400 pivot = base[(lo + hi) >> 1];
        i = lo;
        j = hi;
        do
        {
            while (less(base[i], pivot))
                ++i;
            while (less(pivot, base[j]))
                --j;
            if (j < i)
                break;
            if (j != i)
            {
                hkVector4_s0111_5400 t = base[j];
                base[j] = base[i];
                base[i] = t;
            }
            --j;
            ++i;
        } while (i <= j);

        if (lo < j)
            quickSortVector4(base, lo, j, less);
        lo = i;
    } while (hi > i);
}

// @ 0x01115730
hkBool_s0111_5400 sharesEdgePair(const hkGeomEdge* edges, const hkGeomEdge* a0, const hkGeomEdge* b0, const hkGeomEdge* a1, const hkGeomEdge* b1)
{
    bool e0 = a0 != b0 && a0->m_vertex == b0->m_vertex && TWIN(a0) != TWIN(b0);
    bool e1 = a1 != b1 && a1->m_vertex == b1->m_vertex && TWIN(a1) != TWIN(b1);
    if (!(e0 && e1))
        return hkBool_s0111_5400(0);

    // Block D: pairing (a0, b1) decides whether the two faces keep the edge.
    bool aPairOk = a0 == b1 || a0->m_vertex != b1->m_vertex || TWIN(a0) == TWIN(b1);
    // Block E: pairing (a1, b1).
    bool ePairAlign = a1 != b1 && a1->m_vertex == b1->m_vertex && TWIN(a1) == TWIN(b1);

    // Block F/G: fold the (a0, b1) and (a1, b1) twin pairings.
    bool t0Matches = TWIN(a0) == b1->m_vertex && TWIN(b1) == a0->m_vertex;
    bool p0AgainstB1 = &edges[a0->m_twin] == b1;
    bool t1Matches = TWIN(a1) == b1->m_vertex && TWIN(b1) == a1->m_vertex;
    bool p1AgainstB1 = &edges[a1->m_twin] == b1;
    bool t1PairOk = t1Matches && p1AgainstB1;

    bool reachedF = !aPairOk || ePairAlign == false;
    bool z;
    if (reachedF && t0Matches && !p0AgainstB1)
        z = true;
    else
        z = !t1PairOk;

    // Blocks I/J/K/M: fold the (a0, b0) and (a1, b0) pairings.
    bool m0 = a0 != b0 && a0->m_vertex == b0->m_vertex && TWIN(a0) == TWIN(b0);
    bool m1 = a1 != b0 && a1->m_vertex == b0->m_vertex && TWIN(a1) == TWIN(b0);
    bool c0a = &edges[a0->m_twin] == b0 && edges[a0->m_twin].m_vertex == b0->m_vertex
        && TWIN(b0) == a0->m_vertex;
    bool t1AgainstB0 = &edges[a1->m_twin] == b0 && TWIN(a1) == b0->m_vertex
        && TWIN(b0) == a1->m_vertex;
    bool h = z ? (m0 || !m1 ? !c0a : false) : false;

    return hkBool_s0111_5400(h ? 1 : 0);
}

// @ 0x01115950
hkBool_s0111_5400 hkGeomConvexHullBuilder::vectorLessAndMergeCoordinates(hkVector4_s0111_5400& a, hkVector4_s0111_5400& b)
{
    if (b.x <= a.x &&
        (a.x != b.x || b.y <= a.y) &&
        (a.x != b.x || a.y != b.y || b.z <= a.z))
        return hkBool_s0111_5400(0);
    return hkBool_s0111_5400(1);
}

// @ 0x011159c0
hkVector4_s0111_5400 hkVector4_s0111_5400::Sub(const hkVector4_s0111_5400& other) const
{
    hkVector4_s0111_5400 r;
    r.x = other.x - x;
    r.y = other.y - y;
    r.z = other.z - z;
    r.w = other.w - w;
    return r;
}

// @ 0x011159f0
hkBool_s0111_5400 sortByY(const hkVector4_s0111_5400& a, const hkVector4_s0111_5400& b)
{
    return hkBool_s0111_5400(!(a.y >= b.y));
}

// @ 0x01115a20
hkBool_s0111_5400 sortByW(const hkVector4_s0111_5400& a, const hkVector4_s0111_5400& b)
{
    return hkBool_s0111_5400(!(a.w >= b.w));
}

// @ 0x01115a50
void quickSortHullPlane(HullPlane* base, int lo, int hi, HullPlaneLess less)
{
    int i;
    int j;
    do
    {
        HullPlane pivot = base[(lo + hi) >> 1];
        i = lo;
        j = hi;
        do
        {
            while (less(base[i], pivot))
                ++i;
            while (less(pivot, base[j]))
                --j;
            if (j < i)
                break;
            if (j != i)
            {
                HullPlane t = base[j];
                base[j] = base[i];
                base[i] = t;
            }
            --j;
            ++i;
        } while (i <= j);

        if (lo < j)
            quickSortHullPlane(base, lo, j, less);
        lo = i;
    } while (hi > i);
}

// @ 0x01115bf0
void quickSortWeightedNeighbour(WeightedNeighbour* base, int lo, int hi, WeightedNeighbourLess less)
{
    int i;
    int j;
    do
    {
        WeightedNeighbour pivot = base[(lo + hi) >> 1];
        i = lo;
        j = hi;
        do
        {
            while (less(base[i], pivot))
                ++i;
            while (less(pivot, base[j]))
                --j;
            if (j < i)
                break;
            if (j != i)
            {
                WeightedNeighbour t = base[j];
                base[j] = base[i];
                base[i] = t;
            }
            --j;
            ++i;
        } while (i <= j);

        if (lo < j)
            quickSortWeightedNeighbour(base, lo, j, less);
        lo = i;
    } while (hi > i);
}

// @ 0x01115d00
void hkGeomConvexHullBuilder::getAabb(const hkArrayVector4& verts, hkAabb_s0111_5400& aabb)
{
    if (verts.m_size < 1)
        return;

    const hkVector4_s0111_5400& first = verts.m_data[0];
    aabb.m_min = first;
    aabb.m_max = first;

    for (int i = 0; i < verts.m_size; ++i)
    {
        const hkVector4_s0111_5400& v = verts.m_data[i];
        if (v.x < aabb.m_min.x) aabb.m_min.x = v.x;
        if (v.x > aabb.m_max.x) aabb.m_max.x = v.x;
        if (v.y < aabb.m_min.y) aabb.m_min.y = v.y;
        if (v.y > aabb.m_max.y) aabb.m_max.y = v.y;
        if (v.z < aabb.m_min.z) aabb.m_min.z = v.z;
        if (v.z > aabb.m_max.z) aabb.m_max.z = v.z;
    }
}

// @ 0x01115e20
void recentreVertices(hkArrayVector4* verts, hkVector4_s0111_5400* extents, hkVector4_s0111_5400* center)
{
    hkAabb_s0111_5400 aabb;
    hkGeomConvexHullBuilder::getAabb(*verts, aabb);

    center->x = aabb.m_min.x + aabb.m_max.x;
    center->y = aabb.m_min.y + aabb.m_max.y;
    center->z = aabb.m_min.z + aabb.m_max.z;
    center->w = aabb.m_min.w + aabb.m_max.w;
    center->x = center->x * 0.5f;
    center->y = center->y * 0.5f;
    center->z = center->z * 0.5f;
    center->w = center->w * 0.5f;

    extents->x = aabb.m_max.x - aabb.m_min.x;
    extents->y = aabb.m_max.y - aabb.m_min.y;
    extents->z = aabb.m_max.z - aabb.m_min.z;
    extents->w = aabb.m_max.w - aabb.m_min.w;

    hkMatrix3_s0111_5400 inv;
    inv.m_row[0].x = 1.0f;
    if (1.1920929e-07f < extents->z)
        inv.m_row[2].z = 1.0f / extents->z;
    else
        inv.m_row[2].z = 1.0f;
    if (1.1920929e-07f < extents->y)
        inv.m_row[1].y = 1.0f / extents->y;
    else
        inv.m_row[1].y = 1.0f;
    if (1.1920929e-07f < extents->x)
        inv.m_row[0].x = 1.0f / extents->x;
    else
        inv.m_row[0].x = 1.0f;
    inv.m_row[0].y = 0.0f;
    inv.m_row[0].z = 0.0f;
    inv.m_row[0].w = 0.0f;
    inv.m_row[1].x = 0.0f;
    inv.m_row[1].z = 0.0f;
    inv.m_row[1].w = 0.0f;
    inv.m_row[2].x = 0.0f;
    inv.m_row[2].y = 0.0f;
    inv.m_row[2].w = 0.0f;

    for (int i = 0; i < verts->m_size; ++i)
    {
        hkVector4_s0111_5400& v = verts->m_data[i];
        float ox = v.x - center->x;
        float oy = v.y - center->y;
        float oz = v.z - center->z;

        hkMatrix3_s0111_5400 m;
        m.m_row[0].x = ox;
        m.m_row[0].y = g_vecZero[0];
        m.m_row[0].z = g_vecZero[0];
        m.m_row[0].w = 0.0f;
        m.m_row[1].x = oy;
        m.m_row[1].y = g_vecZero[1];
        m.m_row[1].z = g_vecZero[1];
        m.m_row[1].w = 0.0f;
        m.m_row[2].x = oz;
        m.m_row[2].y = g_vecZero[2];
        m.m_row[2].z = g_vecZero[2];
        m.m_row[2].w = 0.0f;

        m.mul(inv);

        v.x = m.m_row[0].x;
        v.y = m.m_row[1].x;
        v.z = m.m_row[2].x;
        v.w = 0.0f;
    }
}

// @ 0x01116050
void hkGeomConvexHullBuilder::convertFromUnitCube(hkArrayVector4& verts, hkVector4_s0111_5400& scale, hkVector4_s0111_5400& translation)
{
    hkMatrix3_s0111_5400 scaleM;
    scaleM.m_row[0].x = scale.x;
    scaleM.m_row[0].y = 0.0f;
    scaleM.m_row[0].z = 0.0f;
    scaleM.m_row[0].w = 0.0f;
    scaleM.m_row[1].x = 0.0f;
    scaleM.m_row[1].y = scale.y;
    scaleM.m_row[1].z = 0.0f;
    scaleM.m_row[1].w = 0.0f;
    scaleM.m_row[2].x = 0.0f;
    scaleM.m_row[2].y = 0.0f;
    scaleM.m_row[2].z = scale.z;
    scaleM.m_row[2].w = 0.0f;

    for (int i = 0; i < verts.m_size; ++i)
    {
        hkVector4_s0111_5400& v = verts.m_data[i];

        hkMatrix3_s0111_5400 m;
        m.m_row[0].x = v.x;
        m.m_row[0].y = g_vecZero[0];
        m.m_row[0].z = g_vecZero[0];
        m.m_row[0].w = 0.0f;
        m.m_row[1].x = v.y;
        m.m_row[1].y = g_vecZero[1];
        m.m_row[1].z = g_vecZero[1];
        m.m_row[1].w = 0.0f;
        m.m_row[2].x = v.z;
        m.m_row[2].y = g_vecZero[2];
        m.m_row[2].z = g_vecZero[2];
        m.m_row[2].w = 0.0f;

        m.mul(scaleM);

        v.x = m.m_row[0].x;
        v.y = m.m_row[1].x;
        v.z = m.m_row[2].x;
        v.w = 0.0f;

        v.x = v.x + translation.x;
        v.y = translation.y + v.y;
        v.z = translation.z + v.z;
        v.w = translation.w + v.w;
    }
}

// @ 0x01117840
void hkGeomConvexHullBuilder_s0111_7840::generateHullFromPlanarPoints(const hkVector4_s0111_7840& normal, const hkVector4_s0111_7840* points, int numPoints, hkArray<hkVector4_s0111_7840>& usedPoints, hkArray<hkVector4_s0111_7840>& planeEquations)
{
	planeEquations.clear();
	hkVector4_s0111_7840 negNormal;
	negNormal.setNeg4(normal);
	planeEquations.pushBack(normal);
	planeEquations.pushBack(negNormal);

	hkArray<hkBool_s0111_7840> used(numPoints, false);

	// A direction inside the plane.
	hkVector4_s0111_7840 perp;
	if (hkMath_fabs(kOne - hkMath_fabs(normal.z)) < 1e-6f)
	{
		hkVector4_s0111_7840 xAxis;
		xAxis.set(1.0f, kZero, kZero, kZero);
		perp.setCross(xAxis, normal);
	}
	else
	{
		hkVector4_s0111_7840 zAxis;
		zAxis.set(kZero, kZero, 1.0f, kZero);
		perp.setCross(normal, zAxis);
	}

	// Start with the point furthest along it: it is on the hull.
	int startIndex = -1;
	{
		float maxDist = -HK_REAL_MAX;
		for (int i = 0; i < numPoints; i++)
		{
			const float dist = points[i].dot3(perp);
			if (dist > maxDist)
			{
				maxDist = dist;
				startIndex = i;
			}
		}
	}
	used[startIndex] = true;
	usedPoints.pushBack(points[startIndex]);

	int prevIndex = startIndex;
	int currentIndex = startIndex;
	int nextIndex = -1;
	int secondIndex = -1;

	hkVector4_s0111_7840 direction;
	direction.setCross(perp, normal);
	direction.add3clobberW(perp);

	for (;;)
	{
		float bestSin = -2.0f;
		direction.normalize3();
		float bestAngle = HK_REAL_MAX;

		// Wrap: the next point is the one with the smallest turning angle from the current direction.
		for (int i = 0; i < numPoints; i++)
		{
			if (i == currentIndex)
				continue;
			hkVector4_s0111_7840 edge;
			edge.setSub4(points[i], points[currentIndex]);
			hkVector4_s0111_7840 cross;
			cross.setCross(direction, edge);
			const float invLen = hkMath_sqrtInverse(edge.lengthSquared3());
			float sinAngle = cross.length3() * invLen;
			const float cosAngle = edge.dot3(direction) * invLen;
			if (cross.dot3(normal) > kZero)
				sinAngle *= -1.0f;
			float angle;
			if (cosAngle < kZero)
				angle = 2.0f - sinAngle;
			else if (sinAngle > kZero)
				angle = sinAngle;
			else
				angle = 4.0f - sinAngle;
			if (angle < bestAngle)
			{
				bestAngle = angle;
				nextIndex = i;
				bestSin = sinAngle;
			}
		}

		if (currentIndex != startIndex)
		{
			// Side plane through the edge (prev -> current).
			const hkVector4_s0111_7840& current = points[currentIndex];
			hkVector4_s0111_7840 edgeIn;
			edgeIn.setSub4(current, points[prevIndex]);
			hkVector4_s0111_7840 edgeOut;
			edgeOut.setSub4(current, points[nextIndex]);
			hkVector4_s0111_7840& plane = planeEquations.expandOne();
			hkVector4_s0111_7840 inPlaneNormal;
			if (prevIndex == nextIndex)
				inPlaneNormal = normal;
			else
				inPlaneNormal.setCross(edgeIn, edgeOut);
			plane.setCross(edgeIn, inPlaneNormal);
			makeSidePlane(plane, edgeOut, current);
		}
		else
		{
			secondIndex = nextIndex;
		}

		if (used[nextIndex])
			break;
		used[nextIndex] = true;
		usedPoints.pushBack(points[nextIndex]);

		hkVector4_s0111_7840 newDirection;
		newDirection.setSub4(points[nextIndex], points[currentIndex]);
		newDirection.normalize3();
		if (bestSin < 1e-4f)
			direction = newDirection;
		else
			direction.add4(newDirection);
		prevIndex = currentIndex;
		currentIndex = nextIndex;
	}

	// Closing side plane through the edge (current -> next == an already used point).
	{
		const hkVector4_s0111_7840& next = points[nextIndex];
		hkVector4_s0111_7840 edgeIn;
		edgeIn.setSub4(next, points[currentIndex]);
		hkVector4_s0111_7840 edgeOut;
		edgeOut.setSub4(next, points[secondIndex]);
		hkVector4_s0111_7840& plane = planeEquations.expandOne();
		plane.setCross(edgeIn, planeEquations[0]);
		makeSidePlane(plane, edgeOut, next);
	}
}

// @ 0x01118340
void hkGeomConvexHullBuilder_s0111_7840::removeCollinearVertices(hkArray<hkVector4_s0111_7840>& verts, float tolerance)
{
	for (int i = 0; i < verts.getSize(); i++)
		verts[i].w = 0.0f;

	for (int i = 0; i < verts.getSize(); i++)
	{
		for (int j = i + 1; j < verts.getSize(); j++)
		{
			for (int k = j + 1; k < verts.getSize(); k++)
			{
				if (verts[i].w == 1.0f || verts[j].w == 1.0f || verts[k].w == 1.0f)
					continue;

				hkVector4_s0111_7840 a;  a.setSub4(verts[i], verts[j]);  a.normalize3();
				hkVector4_s0111_7840 na; na.setNeg4(a);
				hkVector4_s0111_7840 b;  b.setSub4(verts[i], verts[k]);  b.normalize3();
				hkVector4_s0111_7840 nb; nb.setNeg4(b);
				hkVector4_s0111_7840 c;  c.setSub4(verts[k], verts[j]);  c.normalize3();
				hkVector4_s0111_7840 nc; nc.setNeg4(c);

				hkVector4_s0111_7840 cross1; cross1.setCross(a, b);
				const float len1 = cross1.lengthSquared3();
				const float dot1 = a.dot3(b);
				if (len1 >= tolerance || dot1 >= 0.0f)
				{
					hkVector4_s0111_7840 cross2; cross2.setCross(c, nb);
					const float len2 = cross2.lengthSquared3();
					const float dot2 = c.dot3(nb);
					if (len2 >= tolerance || dot2 >= 0.0f)
					{
						hkVector4_s0111_7840 cross3; cross3.setCross(na, nc);
						const float len3 = cross3.lengthSquared3();
						const float dot3 = nc.dot3(na);
						if (len3 < tolerance && dot3 < 0.0f)
							verts[j].w = 1.0f;
					}
					else
					{
						verts[k].w = 1.0f;
					}
				}
				else
				{
					verts[i].w = 1.0f;
				}
			}
		}
	}

	removeFlaggedVertices(verts);
}

// @ 0x011187d0
void markRedundantVertices(hkGeomHull& hull, int first, int last, const hkGeomConvexHullTolerances& tol, hkBool_s0111_87d0& changed)
{
	changed = false;
	if (!tol.m_removeRedundant)
		return;

	hkGeomEdge_s0111_87d0* edges = hull.m_edges.m_data;
	hkVector4_s0111_87d0* verts = hull.m_vertices;

	for (int i = 0; i < hull.m_edges.m_size; i++)
		edges[i].m_visited = 0;

	// --- 1. collinear vertices ---
	for (int ei = 0; ei < hull.m_edges.m_size; ei++)
	{
		hkGeomEdge_s0111_87d0& edge = hull.m_edges.m_data[ei];
		if (edge.m_visited == 1)
			continue;
		const int twin = edge.m_twin;
		edge.m_visited = 1;
		edges[twin].m_visited = 1;
		const int a = edge.m_vertex;
		const int b = edges[twin].m_vertex;
		const hkVector4_s0111_87d0& va = verts[a];
		const hkVector4_s0111_87d0& vb = verts[b];

		hkVector4_s0111_87d0 dir;
		dir.x = vb.x - va.x;
		dir.y = vb.y - va.y;
		dir.z = vb.z - va.z;
		float loDot = 1e-6f;
		float hiDot = dir.z * dir.z + dir.y * dir.y + dir.x * dir.x;
		int loVert = a;
		int hiVert = b;
		hkArray_s0111_87d0<int> onLine;

		if (b != a && va.w == kZero && vb.w == kZero)
		{
			for (int k = first; k < last + 1; k++)
			{
				if (k == a || k == b || !(verts[k].w == kZero))
					continue;
				const hkVector4_s0111_87d0& p = verts[k];
				const float tx = p.x - va.x;
				const float ty = p.y - va.y;
				const float tz = p.z - va.z;
				const float dot = tx * dir.x + tz * dir.z + ty * dir.y;
				const float cx = dir.y * tz - ty * dir.z;
				const float cy = dir.z * tx - tz * dir.x;
				const float cz = ty * dir.x - dir.y * tx;
				if (cy * cy + (cz * cz + cx * cx) < tol.m_collinearTolSq)
				{
					if (dot < loDot)
					{
						onLine.pushBack(loVert);
						loVert = k;
						loDot = dot;
					}
					else if (dot > hiDot)
					{
						onLine.pushBack(hiVert);
						hiVert = k;
						hiDot = dot;
					}
					else
					{
						onLine.pushBack(k);
					}
				}
			}
		}

		for (int j = 0; j < onLine.getSize(); j++)
		{
			const int v = onLine[j];
			if (v != loVert && v != hiVert)
			{
				verts[v].w = kOne;
				changed = true;
			}
		}
	}

	for (int i = 0; i < hull.m_edges.m_size; i++)
		hull.m_edges.m_data[i].m_visited = 0;

	// --- 2. coplanar vertices ---
	if (last - first > 2 && hull.m_edges.m_size > 2)
	{
		for (int vi = first; vi < last + 1; vi++)
		{
			hkVector4_s0111_87d0& vert = verts[vi];
			if (!(vert.w == kZero))
				continue;

			hkArray_s0111_87d0<hkVector4_s0111_87d0> normals;
			for (int ei = 0; ei < hull.m_edges.m_size; ei++)
			{
				hkGeomEdge_s0111_87d0& edge = hull.m_edges.m_data[ei];
				if (edge.m_visited == 1 || edge.m_vertex != vi)
					continue;
				edge.m_visited = 1;
				const hkGeomEdge_s0111_87d0* start = &edges[hull.m_edges.m_data[ei].m_twin];
				const hkGeomEdge_s0111_87d0* p = start;
				do
				{
					const hkGeomEdge_s0111_87d0& q = edges[p->m_next];
					edges[p->m_next].m_visited = 1;
					const hkVector4_s0111_87d0& vp = verts[p->m_vertex];
					const hkVector4_s0111_87d0& vq = verts[q.m_vertex];
					const hkVector4_s0111_87d0& vr = verts[edges[q.m_next].m_vertex];
					hkVector4_s0111_87d0 d1, d2;
					d1.x = vp.x - vq.x; d1.y = vp.y - vq.y; d1.z = vp.z - vq.z;
					d2.x = vr.x - vq.x; d2.y = vr.y - vq.y; d2.z = vr.z - vq.z;
					hkVector4_s0111_87d0& n = normals.expandOne();
					n.setCross(d1, d2);
					n.normalize3();
					p = &edges[q.m_twin];
				} while (p != start);
			}

			if (normals.getSize() > 0)
			{
				hkVector4_s0111_87d0 sum;
				sum.x = kZero; sum.y = kZero; sum.z = kZero; sum.w = kZero;
				for (int i = 0; i < normals.getSize(); i++)
				{
					sum.x += normals[i].x;
					sum.y += normals[i].y;
					sum.z += normals[i].z;
					sum.w += normals[i].w;
				}
				const float len2 = sum.z * sum.z + (sum.y * sum.y + sum.x * sum.x);
				if (tol.m_coplanarTol < len2)
				{
					const float inv = (len2 == kZero) ? kZero : kOne / hkMath_sqrt(len2);
					hkVector4_s0111_87d0 avg;
					avg.x = inv * sum.x;
					avg.y = sum.y * inv;
					avg.z = sum.z * inv;
					const float threshold = kOne - tol.m_coplanarTol;
					bool flat = true;
					for (int i = 0; i < normals.getSize(); i++)
					{
						const float d = avg.y * normals[i].y + avg.x * normals[i].x + avg.z * normals[i].z;
						if (d < threshold)
						{
							flat = false;
							break;
						}
					}
					if (flat)
					{
						vert.w = kOne;
						changed = true;
					}
				}
			}
		}
	}
}

// @ 0x01118f50
hkBool_s0111_8f50 hkGeomConvexHullBuilder_s0111_8f50::buildPlaneEquations(const hkGeomConvexHullTolerances_s0111_8f50& tolerances, hkGeomHull_s0111_8f50& hull, const hkArray_s0111_8f50<hkVector4_s0111_8f50>& usedVertices, hkVector4_s0111_8f50& planarNormal, hkBool_s0111_8f50& planarHullFound, hkArray_s0111_8f50<hkVector4_s0111_8f50>& planeEquations, hkArray_s0111_8f50<PlaneAndPoints>& planesAndPoints)
{
	const hkVector4_s0111_8f50* vertices = hull.m_vertices;
	const hkGeomEdge_s0111_8f50* edges = hull.m_edges.m_data;

	// 1. One plane per face: visit each face once, from its smallest half-edge index.
	for (int i = 0; i < hull.m_edges.getSize(); i++)
	{
		const hkGeomEdge_s0111_8f50 edge = hull.m_edges[i];
		const int next = edge.m_next;
		const int next2 = edges[next].m_next;
		if (i < next && i < next2)
		{
			hkVector4_s0111_8f50& plane = *planeEquations.expandBy(1);
			const hkVector4_s0111_8f50 p0 = hull.m_vertices[edge.m_vertex];
			const hkGeomEdge_s0111_8f50* e1 = &edges[next];
			const hkVector4_s0111_8f50 p1 = hull.m_vertices[e1->m_vertex];
			const hkGeomEdge_s0111_8f50* e2 = &edges[next2];
			const hkVector4_s0111_8f50 p2 = hull.m_vertices[e2->m_vertex];

			hkVector4_s0111_8f50 d1; d1.setSub4(p0, p1); d1.normalize3();
			hkVector4_s0111_8f50 d2; d2.setSub4(p2, p1); d2.normalize3();
			plane.setCross(d1, d2);
			if (plane.lengthSquared3() < tolerances.m_minNormalLengthSq)
			{
				planeEquations.setSize(planeEquations.getSize() - 1);
			}
			else
			{
				plane.normalize3();
				plane.setPlaneDistance(p0);
				PlaneAndPoints& pp = planesAndPoints.expandOne();
				pp.m_plane = plane;
				pp.m_edge0 = &hull.m_edges[i];
				pp.m_edge1 = e1;
				pp.m_edge2 = e2;
				pp.sort();
			}
		}
	}

	// 2. Opposing faces (a + b ~ 0) mean a flat hull: snap a to -b and add the planes for the shared edges.
	planarHullFound = false;
	for (int i = 0; i < planesAndPoints.getSize(); i++)
	{
		for (int j = i + 1; j < planesAndPoints.getSize(); j++)
		{
			PlaneAndPoints a = planesAndPoints[i];
			PlaneAndPoints b = planesAndPoints[j];
			hkVector4_s0111_8f50 sum; sum.setAdd4(b.m_plane, a.m_plane);
			if (sum.lengthSquared4() < tolerances.m_opposingPlaneTolerance)
			{
				a.m_plane.setNeg3(b.m_plane);
				planarHullFound = true;
				const hkGeomEdge_s0111_8f50* a0 = a.m_edge0;
				const hkGeomEdge_s0111_8f50* a1 = a.m_edge1;
				const hkGeomEdge_s0111_8f50* a2 = a.m_edge2;
				if (sharesEdgePair(edges, a0, b.m_edge0, a1, b.m_edge1, a, b) ||
					sharesEdgePair(edges, a0, b.m_edge0, a1, b.m_edge2, a, b))
				{
					planarHullFound = true;
					addPlanesForOpposingFace(a.m_plane, vertices[a0->m_vertex], vertices[a1->m_vertex], vertices[a2->m_vertex], planeEquations);
				}
				if (sharesEdgePair(edges, a0, b.m_edge0, a2, b.m_edge1, a, b) ||
					sharesEdgePair(edges, a0, b.m_edge0, a2, b.m_edge2, a, b))
				{
					planarHullFound = true;
					addPlanesForOpposingFace(a.m_plane, vertices[a0->m_vertex], vertices[a2->m_vertex], vertices[a1->m_vertex], planeEquations);
				}
				if (sharesEdgePair(edges, a1, b.m_edge0, a2, b.m_edge1, a, b) ||
					sharesEdgePair(edges, a1, b.m_edge0, a2, b.m_edge2, a, b) ||
					sharesEdgePair(edges, a1, b.m_edge1, a2, b.m_edge2, a, b))
				{
					planarHullFound = true;
					addPlanesForOpposingFace(a.m_plane, vertices[a1->m_vertex], vertices[a2->m_vertex], vertices[a0->m_vertex], planeEquations);
				}
			}
		}
	}
	if (planarHullFound)
	{
		// Normal of the plane through the first three used vertices.
		const hkVector4_s0111_8f50* v = usedVertices.m_data;
		hkVector4_s0111_8f50 a; a.setSub4(v[0], v[1]);
		hkVector4_s0111_8f50 b; b.setSub4(v[0], v[2]);
		planarNormal.setCross(a, b);
		planarNormal.normalize3();
		planarNormal.setPlaneDistance(usedVertices.m_data[0]);
	}

	int numWelded;
	sortAndWeld(tolerances, planeEquations, numWelded);

	// 3. Fewer than two planes: the hull is a point or a segment. Bound it with 6 planes.
	const int numPlanes = planeEquations.getSize();
	if (numPlanes < 2)
	{
		hkVector4_s0111_8f50 p0, p1;
		if (hull.m_edges.getSize() == 1)
		{
			p0 = hull.m_vertices[hull.m_edges[0].m_vertex];
			p1 = p0;
			p1.x = p0.x + 1.0f;
		}
		else
		{
			p0 = hull.m_vertices[hull.m_edges[0].m_vertex];
			p1 = hull.m_vertices[hull.m_edges[hull.m_edges[0].m_twin].m_vertex];
		}
		hkVector4_s0111_8f50 dir; dir.setSub4(p0, p1);

		// The coordinate axis most perpendicular to the segment.
		float bestDot = HK_REAL_MAX;
		hkVector4_s0111_8f50 bestAxis;
		for (int k = 0; k < 3; k++)
		{
			hkVector4_s0111_8f50 axis;
			axis.x = 0.0f; axis.y = 0.0f; axis.z = 0.0f;
			(&axis.x)[k] = 1.0f;
			const float d = fabsf(axis.dot3(dir));
			if (d < bestDot)
			{
				bestDot = d;
				bestAxis.x = axis.x; bestAxis.y = axis.y; bestAxis.z = axis.z;
			}
		}

		planeEquations.setSize(numPlanes + 6);
		hkVector4_s0111_8f50& e0 = planeEquations[numPlanes];
		e0.setCross(dir, bestAxis);
		e0.normalize3Stored();
		e0.setPlaneDistance(p0);

		hkVector4_s0111_8f50& e1 = planeEquations[numPlanes + 1];
		e1.setCross(dir, e0);
		e1.normalize3Stored();
		e1.setPlaneDistance(p0);

		hkVector4_s0111_8f50& e2 = planeEquations[numPlanes + 2];
		e2.setNeg4(e0);
		e2.setPlaneDistance(p0);

		hkVector4_s0111_8f50& e3 = planeEquations[numPlanes + 3];
		e3.setNeg4(e1);
		e3.setPlaneDistance(p0);

		hkVector4_s0111_8f50& e4 = planeEquations[numPlanes + 4];
		e4 = dir;
		e4.normalize3();
		e4.setPlaneDistance(p0);

		hkVector4_s0111_8f50& e5 = planeEquations[numPlanes + 5];
		e5.setNeg4(e4);
		e5.normalize3();
		if (hull.m_edges.getSize() == 1)
			e5.setPlaneDistance(p0);
		else
			e5.setPlaneDistance(p1);
	}

	// 4. Flat hull: rebuild the planes from the planar points.
	if (planarHullFound && tolerances.m_postFilter)
	{
		planeEquations.clear();
		hkArray_s0111_8f50<hkVector4_s0111_8f50> usedPoints;
		generateHullFromPlanarPoints(planarNormal, usedVertices.m_data, usedVertices.getSize(), usedPoints, planeEquations);
	}

	sortAndWeld(tolerances, planeEquations, numWelded);
	return true;
}

// @ 0x0111b170
hkResult hkGeomConvexHullBuilder_s0111_b170::mergeHulls(const hkGeomConvexHullTolerances_s0111_b170& tolerances, hkGeomHull_s0111_b170& hullA, hkGeomHull_s0111_b170& hullB, hkGeomHull_s0111_b170& mergedHull)
{
	mergedHull.m_vertices = hullA.m_vertices;
	if (isSingleLine(tolerances.m_singleLineTolerance, hullA, hullB, mergedHull))
		return HK_SUCCESS;

	const hkVector4_s0111_b170* vertices = hullA.m_vertices;
	hkInplaceArray<WeightedLine, 1> tangentLine(1);
	hkVector4_s0111_b170 tangentNormal;
	getCommonTangent(hullA, hullB, tangentLine[0], tangentNormal);
	hkVector4_s0111_b170 lastNormal = tangentNormal;

	int maxNumLines = hullA.m_edges.getSize() + hullB.m_edges.getSize() + 2;
	hkGeomConvexHullConfig config;
	config.m_tolerance = tolerances.m_wrappingTolerance;
	const int maxIterations = maxNumLines * 3;
	config.m_maxIterations = maxIterations;

	hkInplaceArray<hkArray_s0111_b170<WeightedLine>*, 64> lineArrays;
	hkInplaceArray<WrappingLine, 128> wrapping;
	hkArray_s0111_b170<WeightedLine>* currentLines = &tangentLine;

	if (maxIterations > 0)
	{
		for (int iteration = 0;; iteration++)
		{
			if (iteration > maxNumLines)
			{
				config.m_tolerance = config.m_tolerance * 1.1f;
				if (config.m_tolerance > 1.0f)
					maxNumLines++;
			}

			void* mem = hkThreadMemory_s0111_b170::getInstance().allocateStack(sizeof(LineArray));
			LineArray* newLines = new (mem) LineArray;
			lineArrays.pushBack(newLines);

			for (int i = 0; i < currentLines->getSize(); i++)
			{
				WeightedLine& line = (*currentLines)[i];
				hkInplaceArray<WeightedNeighbour, 64> neighboursA;
				hkInplaceArray<WeightedNeighbour, 64> neighboursB;

				const hkVector4_s0111_b170* a = &vertices[line.m_edgeA->m_vertex];
				const hkVector4_s0111_b170* b = &vertices[line.m_edgeB->m_vertex];
				hkVector4_s0111_b170 normal;

				const WeightedLine* last = line.m_lastLine;
				if (last == 0)
				{
					normal = tangentNormal;
				}
				else
				{
					const hkVector4_s0111_b170* lastA = &vertices[last->m_edgeA->m_vertex];
					const hkVector4_s0111_b170* lastB = &vertices[last->m_edgeB->m_vertex];
					const hkVector4_s0111_b170* other = b;
					if (lastA != a)
						other = a;

					hkVector4_s0111_b170 lastDir;
					lastDir.setSub4(*lastB, *lastA);
					lastDir.normalize3();
					hkVector4_s0111_b170 dir;
					dir.setSub4(*other, *lastA);
					dir.normalize3();
					normal.setCross(lastDir, dir);
					if (normal.lengthSquared3() < 1e-6f)
					{
						dir.setSub4(*other, *lastB);
						dir.normalize3();
						normal.setCross(lastDir, dir);
						if (normal.lengthSquared3() < 1e-6f)
						{
							hkVector4_s0111_b170 sum;
							sum.setAdd4(dir, lastDir);
							hkVector4_s0111_b170 diff;
							diff.setSub4(lastDir, dir);
							const float diffLen2 = diff.lengthSquared3();
							float sumLen2;
							if (diffLen2 < 1e-6f || (sumLen2 = sum.lengthSquared3()) < 1e-6f)
							{
								normal = lastNormal;
							}
							else
							{
								sum.mul4(hkVector4_s0111_b170::invSqrtOrZero(sumLen2));
								diff.mul4(hkVector4_s0111_b170::invSqrtOrZero(diffLen2));
								normal.setCross(diff, sum);
							}
						}
					}
					normal.normalize3();
				}
				lastNormal = normal;

				findWeightedNeighbours(tolerances, hullA, normal, line.m_lastVertex, line.m_edgeA, a, b, neighboursA);
				findWeightedNeighbours(tolerances, hullB, normal, line.m_lastVertex, line.m_edgeB, a, b, neighboursB);
				validateNeighbours(tolerances, hullB.m_vertices, normal, line.m_lastVertex, &line, a, b, neighboursA, neighboursB);
				addWrappingLines(config, &line, neighboursA, neighboursB, *newLines);
			}

			currentLines = newLines;
			if (newLines->getSize() > 1)
				hkAlgorithm::quickSortRecursive<WeightedLine, hkBool_s0111_b170 (*)(const WeightedLine&, const WeightedLine&)>(
					newLines->begin(), 0, newLines->getSize() - 1, weightedLineLess);
			findWrapping(hullA, hullB, *newLines, wrapping);
			if (wrapping.getSize() != 0)
				break;
		}
	}

	for (int i = lineArrays.getSize() - 1; i >= 0; i--)
	{
		((LineArray*)lineArrays[i])->~LineArray();
		hkThreadMemory_s0111_b170::getInstance().deallocateStack(lineArrays[i]);
	}
	lineArrays.clear();

	if (wrapping.getSize() == 0)
		return HK_FAILURE;

	stitchHulls(hullA, hullB, wrapping, mergedHull);
	return HK_SUCCESS;
}

// @ 0x0111d560
int MoppCompiler::FUN_0111d560(MoppNode* node, MoppCell* build, MoppCell* in)
{
    int limit0 = in->level;                 // frame value at +0x08

    if (node->flag04 == 0)
    {
        // ----- interior node -----
        if (node->flag39 == 0 && in->depth < this->maxDepth)
        {
            char probe = 0;
            this->FUN_0111d410(&probe, node, build, in);
            if (probe != 0)
                node->flag3c = 1;
        }

        char childInfo[20];
        if (node->flag3c == 1)
            this->FUN_0111d450(build, in, childInfo);

        int bestEC = -1;
        int bestF0 = -1;
        int limit  = 0x7fffffff;

        // Iteration order matches the original: childF0 first, then childEC.
        MoppNode* order[2];
        order[0] = node->childF0;
        order[1] = node->childEC;

        for (int i = 0; i < 2; i++)
        {
            MoppNode* c = order[i];
            if (c == 0)
                continue;

            MoppCell sub;
            memcpy(&sub, in, 0x48);
            sub.FUN_0111cdb0(c);
            sub.FUN_0111d2b0(c, this->origin);
            sub.depth = in->depth + 1;
            sub.flag  = 0;
            sub.FUN_0111d340();

            int r = this->FUN_0111d560(c, build, &sub);
            if (i == 0) bestF0 = r; else bestEC = r;
            if (sub.level <= limit)
                limit = sub.level;
        }

        int value = (int)((unsigned)limit + 2u);
        int alt   = limit0 + 2;
        if (alt < value)
            value = alt;

        if (node->childEC != 0)
        {
            MoppNode* c = node->childEC;
            int threshold = (node->flag39 == 0) ? limit0 : value;
            if ((node->flag39 == 0 || c->flag39 == 0) && bestEC < threshold)
                c->flag3c = 1;
            if (c->flag3c == 0 && bestEC <= value)
                value = bestEC;
        }
        if (node->childF0 != 0)
        {
            MoppNode* c = node->childF0;
            int threshold = (node->flag39 == 0) ? limit0 : value;
            if ((node->flag39 == 0 || c->flag39 == 0) && bestF0 < threshold)
                c->flag3c = 1;
            if (c->flag3c == 0 && bestF0 <= value)
                value = bestF0;
        }
        return value;
    }

    // ----- leaf node -----
    float  limit = this->minCell;
    float* span  = &node->span[0][0];

    for (int i = 0; i < 3; i++)
    {
        if (node->flag39 == 0)
            node->cells[i] = 1;

        float v = this->scan[i];
        if (span[1] - span[0] < v && v < limit)
        {
            int q = FUN_0120ad30(this->sat * v);
            if (q * 0x80 < (1 << (limit0 & 0x1f)))
            {
                if (node->flag39 == 0)
                    node->cells[i] = 2;
            }
            else
            {
                limit = v;
            }
        }
        span += 2;
    }

    unsigned u = (unsigned)FUN_0120ad30((this->sat * 0.9f) * limit);
    int bits = 0;
    if (u != 0)
    {
        do { u >>= 1; bits++; } while (u != 0);
    }
    if (bits + 6 <= limit0)
        return limit0;
    return bits + 6;
}

// @ 0x0111d7f0
void MoppCompiler::FUN_0111d7f0(MoppCell* src, MoppCell* above)
{
    float* scan = this->scan;
    int*   out  = src->out;
    int    i;

    for (i = 0; i < 3; i++)
    {
        float limit = (float)(1 << (above->cellShift & 0x1f)) / this->sat;
        if (limit <= this->minCell)
            limit = this->minCell;

        float v = scan[i];
        if (src->span[i].hi - src->span[i].lo < v && v <= limit)
            limit = v;

        int n = FUN_0120ad30(this->sat * limit);
        out[i]     = above->span[i].hi + 1 + n;
        out[i - 3] = above->span[i].lo - n;
    }
}

// @ 0x0111d8e0
void MoppCompiler::FUN_0111d8e0(int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int   iVar1 = *(int*)((char*)this->writer + 0xc);
    char* iVar3 = (char*)(iVar1 - param_6);

    if (param_4 < 3)
    {
        int iVar2 = iVar1 - param_5;
        if ((iVar2 > 0 || (int)iVar3 > 0xf8) && iVar2 < 0x10000 && (int)iVar3 < 0x10000)
        {
            ((MoppCodeWriter*)this->writer)->putByte((int)iVar3 & 0xff);
            ((MoppCodeWriter*)this->writer)->putByte((int)iVar3 >> 8 & 0xff);
            ((MoppCodeWriter*)this->writer)->putByte(iVar2 & 0xff);
            ((MoppCodeWriter*)this->writer)->putByte(iVar2 >> 8 & 0xff);
            ((MoppCodeWriter*)this->writer)->putByte(param_2);
            ((MoppCodeWriter*)this->writer)->putByte(param_3);
            ((MoppCodeWriter*)this->writer)->putByte(param_4 + 0x23);
            return;
        }
        if (param_3 - param_2 == 1)
        {
            if ((int)iVar3 > 0xfb)
            {
                FUN_0111d260(param_6);
                param_6 = *(int*)((char*)this->writer + 0xc);
            }
            FUN_0111d260(param_5);
            ((MoppCodeWriter*)this->writer)->putByte(*(int*)((char*)this->writer + 0xc) - param_6);
            ((MoppCodeWriter*)this->writer)->putByte(param_2);
            ((MoppCodeWriter*)this->writer)->putByte(param_4 + 0x20);
            return;
        }
    }

    if ((int)iVar3 > 0xfb)
    {
        FUN_0111d260(param_6);
        param_6 = *(int*)((char*)this->writer + 0xc);
    }
    FUN_0111d260(param_5);
    ((MoppCodeWriter*)this->writer)->putByte(*(int*)((char*)this->writer + 0xc) - param_6);
    ((MoppCodeWriter*)this->writer)->putByte(param_2);
    ((MoppCodeWriter*)this->writer)->putByte(param_3);
    ((MoppCodeWriter*)this->writer)->putByte(param_4 + 0x10);
}

// @ 0x0111da50
int __stdcall FUN_0111da50(float* n)
{
    float f0 = n[0];
    if (f0 > g_01488874)
    {
        float f2 = n[2];
        int r = 0;
        if (f2 <= g_01488874)
        {
            if (g_013eb964 <= f2)
            {
                if (g_01488874 < n[1]) return 7;
                if (n[1] < g_013eb964) return 8;
            }
            else
            {
                r = 6;
                if (g_01488874 < n[1]) return 10;
                if (n[1] < g_013eb964) return 0xc;
            }
        }
        else
        {
            r = 5;
            if (g_01488874 < n[1]) return 9;
            if (n[1] < g_013eb964) return 0xb;
        }
        return r;
    }
    if (n[1] <= g_01488874) return 2;
    if (g_01488874 < n[2]) return 3;
    if (n[2] < g_013eb964) return 4;
    return 1;
}

// @ 0x0111db80
void MoppCompiler::FUN_0111db80(MoppNode* node, MoppCell* build, int* outHi, int* outLo)
{
    float* normal = node->normal;

    int axis = 0;                 // last non-zero axis (ebx)
    int count = 0;                // iVar7
    int neg = 0;                  // local_40

    if (normal[0] != 0.0f) { count = 1; axis = 0; if (normal[0] < 0.0f) neg = 1; }
    if (normal[1] != 0.0f) { count++;  axis = 1; if (normal[1] < 0.0f) neg++; }
    if (normal[2] != 0.0f) { count++;  axis = 2; if (normal[2] < 0.0f) neg++; }

    float hi = node->planeMax;    // +0xc0
    float lo = node->planeMin;    // +0xbc

    if (count == 1)
    {
        int a = FUN_0120ad30(FUN_0120ac90((lo - this->origin[axis]) * this->sat));
        int b = FUN_0120ad30(FUN_0120ac90((hi - this->origin[axis]) * this->sat));
        int base = build->cellBase[axis];
        int sh   = build->cellShift;

        int m = (a - base) >> sh;         // edi  (from planeMin)
        int n = ((b - base) >> sh) + 1;   // eax  (from planeMax)

        if (m < 1) m = 0; else if (m > 0xfe) m = 0xff;
        if (n < 1) n = 0; else if (n > 0xfe) n = 0xff;

        *outLo = m;
        *outHi = n;
        if (*outLo < 0) *outLo = 0;
        return;
    }

    float invSat = 1.0f / this->sat;
    float plane =
          (build->cellBase[0] * invSat + this->origin[0]) * normal[0]
        + (build->cellBase[1] * invSat + this->origin[1]) * normal[1]
        + (build->cellBase[2] * invSat + this->origin[2]) * normal[2];

    float invCells = 1.0f / (float)(1 << (build->cellShift & 0x1f));

    float mul = 1.0f;         // diagonal scale (sqrt(count))
    float recip = 1.0f;       // 1.0, 1/sqrt(2), 1/sqrt(3)
    if (count == 2)      { mul = 1.4142135f; recip = 0.5f; }
    else if (count == 3) { mul = 1.7320508f; recip = 0.33333334f; }

    float a = ((lo - plane) * this->sat) * invCells * mul;
    float b = ((hi - plane) * this->sat) * invCells * mul;

    if (neg != 0)
    {
        float off = (float)(neg * 0xff);
        a += off;
        b += off;
    }

    int low  = FUN_0120ad30(FUN_0120ac90(recip * a));
    int high = FUN_0120ad30(FUN_0120ac90(recip * b)) + 1;

    if (low < 1) low = 0; else if (low > 0xfe) low = 0xff;

    if (high < 1)
    {
        *outLo = low;
        *outHi = 0;
        return;
    }
    if (high > 0xfe) high = 0xff;

    *outLo = low;
    *outHi = high;
}

// @ 0x0111de80
void __stdcall FUN_0111de80(int param_1, int* param_2)
{
    float fVar3;
    float fVar4;
    int uVar1 = *(int*)(param_1 + 0x1c);
    int uVar2 = *(int*)(param_1 + 0x0c);
    param_2[1] = *(int*)(param_1 + 0x14);
    param_2[0] = uVar2;
    param_2[3] = 0;
    param_2[2] = uVar1;
    fVar3 = 0.0f;
    fVar4 = *(float*)(param_1 + 0x10) - *(float*)(param_1 + 0x0c);
    if (0.0f <= fVar4) {
        fVar3 = fVar4;
    }
    fVar4 = *(float*)(param_1 + 0x18) - *(float*)(param_1 + 0x14);
    if (fVar3 <= fVar4) {
        fVar3 = fVar4;
    }
    fVar4 = *(float*)(param_1 + 0x20) - *(float*)(param_1 + 0x1c);
    if (fVar3 <= fVar4) {
        fVar3 = fVar4;
    }
    *(float*)(param_2 + 3) = (254.0f / fVar3) * 65536.0f;
}

// @ 0x0111df20
void* MoppBuilder::FUN_0111df20(float* params, int param_3, int param_4)
{
    this->flags  = 1;
    this->vtable = (void*)0x014a60e8u;
    this->f40 = 0.5f;
    this->f48 = 1.0f;
    this->i60 = 4;
    this->f44 = 0.2f;
    this->f50 = 0.2f;
    this->f54 = 0.2f;
    this->f58 = 0.05f;
    this->f5c = 0.0f;

    g_moppBasis[0].v[0] = 1.0f;
    g_moppBasis[0].v[1] = 0.0f;
    g_moppBasis[0].v[2] = 0.0f;
    g_moppBasis[0].w    = 0.0f;
    g_moppBasis[1].v[0] = 0.0f;
    g_moppBasis[1].v[1] = 1.0f;
    g_moppBasis[1].v[2] = 0.0f;
    g_moppBasis[1].w    = 0.0f;
    g_moppBasis[2].v[0] = 0.0f;
    g_moppBasis[2].v[1] = 0.0f;
    g_moppBasis[2].v[2] = 1.0f;
    g_moppBasis[2].w    = 0.0f;
    g_moppBasis[0].u    = 0.0f;
    g_moppBasis[1].u    = 0.0f;
    g_moppBasis[2].u    = 0.0f;
    g_moppBasis[3].v[0] = 0.0f;
    g_moppBasis[3].v[1] = 1.0f;
    g_moppBasis[3].v[2] = 1.0f;
    g_moppBasis[3].w    = 0.0f;
    g_moppBasis[4].v[0] = 1.0f;
    g_moppBasis[4].v[1] = 0.0f;
    g_moppBasis[4].v[2] = 1.0f;
    g_moppBasis[4].w    = 0.0f;
    g_moppBasis[5].v[0] = 1.0f;
    g_moppBasis[5].v[1] = 1.0f;
    g_moppBasis[5].v[2] = 0.0f;
    g_moppBasis[5].w    = 0.0f;
    g_moppBasis[3].u    = 0.2f;
    g_moppBasis[4].u    = 0.2f;
    g_moppBasis[5].u    = 0.2f;
    g_moppBasis[6].v[0] = 0.0f;
    g_moppBasis[6].v[1] = 1.0f;
    g_moppBasis[6].v[2] = -1.0f;
    g_moppBasis[6].w    = 0.0f;
    g_moppBasis[7].v[0] = 1.0f;
    g_moppBasis[7].v[1] = 0.0f;
    g_moppBasis[7].v[2] = -1.0f;
    g_moppBasis[7].w    = 0.0f;
    g_moppBasis[8].v[0] = 1.0f;
    g_moppBasis[8].v[1] = -1.0f;
    g_moppBasis[8].v[2] = 0.0f;
    g_moppBasis[8].w    = 0.0f;
    g_moppBasis[6].u    = 0.25f;
    g_moppBasis[7].u    = 0.25f;
    g_moppBasis[8].u    = 0.25f;
    g_moppBasis[9].v[0] = 1.0f;
    g_moppBasis[9].v[1] = 1.0f;
    g_moppBasis[9].v[2] = 1.0f;
    g_moppBasis[9].w    = 0.0f;
    g_moppBasis[10].v[0] = 1.0f;
    g_moppBasis[10].v[1] = 1.0f;
    g_moppBasis[10].v[2] = -1.0f;
    g_moppBasis[10].w    = 0.0f;
    g_moppBasis[11].v[0] = 1.0f;
    g_moppBasis[11].v[1] = -1.0f;
    g_moppBasis[11].v[2] = -1.0f;
    g_moppBasis[11].w    = 0.0f;
    g_moppBasis[12].v[0] = 1.0f;
    g_moppBasis[12].v[1] = -1.0f;
    g_moppBasis[12].v[2] = -1.0f;
    g_moppBasis[12].w    = 0.0f;
    g_moppBasis[9].u     = 0.3f;
    g_moppBasis[10].u    = 0.32f;
    g_moppBasis[11].u    = 0.32f;
    g_moppBasis[12].u    = 0.34f;

    for (int i = 0; i < 13; i++)
    {
        MoppBasis* e = &g_moppBasis[i];
        float dot = e->v[1] * e->v[1] + (e->v[0] * e->v[0] + e->v[2] * e->v[2]);
        float scale;
        if (dot == 0.0f)
            scale = 0.0f;
        else
            scale = 1.0f / sqrtf(dot);

        e->v[0] *= scale;
        e->v[1] *= scale;
        e->v[2] *= scale;
        e->w    *= scale;
        e->index = i;
    }

    this->f40 = params[0];
    this->f44 = params[1];
    this->f48 = params[2];
    this->f50 = params[4];
    this->f54 = params[5];
    this->f58 = params[6];
    this->f5c = params[7];
    this->i60 = *(int*)&params[8];
    this->field08 = param_4;
    this->field10 = param_3;
    this->field0c = 0;
    return this;
}

// @ 0x0111ffc0
MoppChainNode* MoppCompiler_s0111_ffc0::buildNode(MoppChainNode* parent, const int* primList, int side, int depth)
{
    if (primList[1] == 1)
    {
        if (this->m_freeBCount == 0)
            this->m_ifaceA->addShape((void*)this->m_root, (int)this, 0x800, 0, 0);
        // X87/ABI: the call target takes (parent, primList).
        return hkFun_0111f9e0(parent, primList);
    }

    if (this->m_freeACount == 0)
        this->m_ifaceA->addShape((void*)this->m_root, (int)this, 0x800, 0, 0);

    MoppChainNode* node = this->m_freeA;
    this->m_freeA = node->m_parent;
    this->m_freeACount -= 1;
    hkFun_0111efb0(node);

    node->m_pad4[0] = 0;
    node->m_fc4 = 1.0e6f;                       // 0x49742400
    node->m_fbc = 1.0e10f;                      // 0x501502f9
    node->m_first = 0;
    node->m_last = 0;
    node->m_primCount = primList[1];
    node->m_parent = parent;

    if (parent == 0)
    {
        this->m_root = node;
    }
    else
    {
        if (side == 0)
            parent->m_first = node;
        else
            parent->m_last = node;
        node->m_copies[0] = ((uint32_t*)parent)[3];
        node->m_copies[1] = ((uint32_t*)parent)[4];
        node->m_copies[2] = ((uint32_t*)parent)[5];
        node->m_copies[3] = ((uint32_t*)parent)[6];
        node->m_copies[4] = ((uint32_t*)parent)[7];
        node->m_copies[5] = ((uint32_t*)parent)[8];
    }

    int childIdx[3];
    float faceDist[3];
    // X87-PRECISION: 0x0111f4c0 returns three ints and three floats (two by pointer).
    hkFun_0111f4c0(parent, childIdx, faceDist);

    for (int i = 0; i < 3; ++i)
    {
        int entry = childIdx[i] * 0x20;
        float* e = (float*)(this->m_entries + entry);
        if (node->m_fc4 > faceDist[i] + e[4])
        {
            for (int j = i; j < 3; ++j)
            {
                int e2 = childIdx[j] * 0x20;
                this->m_ifaceB->addShapeRange((void*)(this->m_entries + e2), primList[0], primList[1],
                                              (int*)((char*)node + 0xc + childIdx[j] * 8),
                                              (int*)((char*)node + 0x10 + childIdx[j] * 8));
            }
            break;
        }

        int* slot = (int*)((char*)node + 0xc + childIdx[i] * 8);
        this->m_ifaceB->addShape((void*)(this->m_entries + entry), primList[0], primList[1],
                                 slot, slot + 1);

        if (primList[1] > 1)
            hkFun_0111faa0(primList[0], 0, primList[1] - 1, 0);

        hkFun_0111f670(node, (void*)(this->m_entries + entry), primList, slot, depth);
    }

    if (this->m_numEntries > 3)
    {
        int k = 3;
        int off = 0x60;
        do
        {
            if (node->m_fc4 <= *(float*)(this->m_entries + off + 0x10))
                break;
            this->m_ifaceB->addShape((void*)(this->m_entries + off), primList[0], primList[1],
                                     childIdx, &childIdx[1]);
            if (primList[1] > 1)
                hkFun_0111faa0(primList[0], 0, primList[1] - 1, 0);
            hkFun_0111f670(node, (void*)(this->m_entries + off), primList, childIdx, depth);
            ++k;
            off += 0x20;
        } while (k < this->m_numEntries);
    }

    hkFun_0111f400(primList, node);

    if ((void*)node->m_iB8 != (void*)this->m_scratch)
        this->m_ifaceB->addShape((void*)node->m_iB8, primList[0], primList[1], (int*)node, 0);

    // X87/ABI: 0x0111fe30 splits the primitive list for this node into two child lists.
    hkFun_0111fe30(primList, node, depth, &childIdx[0], &childIdx[1]);

    node->m_last = this->buildNode(node, &childIdx[1], 1, depth + 1);
    node->m_first = this->buildNode(node, &childIdx[0], 0, depth + 1);
    return node;
}
