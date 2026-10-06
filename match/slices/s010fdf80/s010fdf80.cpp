// Havok 3.1.0: hkPredGskCylinderAgent3::process @ 0x010fdf80  (/O2 /MD /Gy /EHsc /TP, x87 float, SSE-aligned frame)
//
// Predictive GSK agent3 for pairs where one or both bodies are hkCylinderShapes. It is hkPredGskAgent3::process
// (see slice s010ff9e0) plus a cylinder->capsule switch:
//  * hkAgentEntry::m_userData bits 0/1 say body A/B is a cylinder, bits 2/3 say that cylinder is currently
//    approximated by a capsule. A cylinder whose axis is nearly perpendicular to the separating normal
//    (|axis . n| < 0.085) switches to the capsule, and back once |axis . n| > 0.17 (hysteresis). Each switch
//    flushes the contact manifold.
//  * While in capsule mode the body is temporarily replaced (in the const input!) by a stack hkCdBody whose
//    shape is a freshly allocated hkCapsuleShape(vertexA, vertexB, cylRadius + radius + 0.002), and the GSK
//    cache handed to the GSK routines is a local copy whose cylinder vertex ids are remapped to capsule ids.
//    After the step the capsule is released and the original bodies are restored.
// Signature (exact mangled name):
//   ?process@hkPredGskCylinderAgent3@@YAPAXABUhkAgent3ProcessInput@@PAUhkAgentEntry@@PAXPAVhkVector4@@AAUhkProcessCollisionOutput@@@Z
#include <math.h>
#include <new>

typedef unsigned char  hkUchar;
typedef unsigned short hkUint16;
typedef unsigned int   hkUint32;
typedef signed char    hkInt8;

struct hkRotation { float col0[4]; float col1[4]; float col2[4]; };

class __declspec(align(16)) hkVector4
{
public:
    float x, y, z, w;
    void setRotatedDir(const hkRotation& r, const hkVector4& v);   // 0x010814a0 (out of line)
};
struct hkTransform { float col0[4]; float col1[4]; float col2[4]; float trans[4]; };   // 0x40 bytes

// hkMemory::getInstance() singleton; vtable slot 4 (+0x10) = allocateChunk(nbytes, memoryClass)
class hkMemory
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void* allocateChunk(int nbytes, int cls);
};
extern hkMemory* g_hkMemoryInstance;   // 0x016e4178
enum { HK_MEMORY_CLASS_SHAPE = 0x24 };

class hkReferencedObject
{
public:
    virtual ~hkReferencedObject();                 // slot 0: deleting dtor
    hkUint16 m_memSizeAndFlags;                    // +0x4
    short    m_referenceCount;                     // +0x6

    // HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE)
    void* operator new(size_t nbytes)
    {
        hkReferencedObject* b = static_cast<hkReferencedObject*>(g_hkMemoryInstance->allocateChunk((int)nbytes, HK_MEMORY_CLASS_SHAPE));
        b->m_memSizeAndFlags = (hkUint16)nbytes;
        return b;
    }
    void removeReference()
    {
        if (m_memSizeAndFlags != 0)
        {
            --m_referenceCount;
            if (m_referenceCount == 0)
                delete this;
        }
    }
};

struct hkShape : public hkReferencedObject
{
    // vtable slot 10 (+0x28): hkConvexShape::getSupportingVertices
    virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void getSupportingVertices(const hkUint16* ids, int numIds, hkVector4* out) const;
    hkUint32 m_userData;    // +0x8
    float    m_radius;      // +0xc (hkConvexShape::m_radius)
};

struct hkCylinderShape : public hkShape
{
    float     m_cylRadius;          // +0x10
    hkVector4 m_vertexA;            // +0x20
    hkVector4 m_vertexB;            // +0x30
    hkVector4 m_perpendicular1;     // +0x40
    hkVector4 m_perpendicular2;     // +0x50
    float getCylinderRadius() const;   // 0x00a0ab60 (out of line)
};

struct hkCapsuleShape : public hkShape
{
    hkVector4 m_vertexA;            // +0x10
    hkVector4 m_vertexB;            // +0x20
    // Havok is built without C++ exceptions: no cleanup of the new-expression is emitted
    hkCapsuleShape(const hkVector4& vertexA, const hkVector4& vertexB, float radius) throw();   // 0x010c2730
};

struct hkCdBody
{
    const hkShape*      m_shape;     // +0x0
    hkUint32            m_shapeKey;  // +0x4
    const hkTransform*  m_motion;    // +0x8
    const hkCdBody*     m_parent;    // +0xc

    hkCdBody() {}
    // hkCdBody(const hkCdBody* parent): child body sharing the parent's motion
    hkCdBody(const hkCdBody* parent) { m_parent = parent; m_motion = parent->m_motion; }
    void setShape(const hkShape* shape, hkUint32 key) { m_shapeKey = key; m_shape = shape; }
};
// The root body of a collision is an hkCollidable; allowed penetration depth lives at +0x20.
struct hkCollidableRoot : public hkCdBody { hkUint32 m_pad[4]; float m_allowedPenetrationDepth; };

struct hkCollisionQualityInfo
{
    float m_keepContact;         // +0x0
    float m_create4dContact;     // +0x4
    float m_createContact;       // +0x8
    float m_manifoldTimDistance; // +0xc
    char  m_useContinuousPhysics;// +0x10
    char  m_pad[3];
    float m_minSeparation;       // +0x14
    float m_minExtraSeparation;  // +0x18
    float m_minSafeDeltaTime;    // +0x1c
    float m_minAbsoluteSafeDeltaTime; // +0x20
    float m_toiSeparation;       // +0x24
    float m_toiExtraSeparation;  // +0x28
};

struct hkProcessCollisionInput
{
    void*  m_dispatcher;         // +0x0
    void*  m_filter;             // +0x4
    float  m_tolerance;          // +0x8
    char   m_createPredictiveAgents;
    char   m_pad[3];
    float  m_stepInfo[4];        // +0x10
    void*  m_config;             // +0x20
    void*  m_dynamicsInfo;       // +0x24
    const hkCollisionQualityInfo* m_collisionQualityInfo;   // +0x28
};

struct hkProcessCdPoint;
struct hkAgentEntry { hkUchar m_streamCommand, m_agentType, m_numContactPoints, m_size; hkUint32 m_userData; };

// hkAgentEntry::m_userData flags of this agent
enum
{
    CYLINDER_A        = 1,
    CYLINDER_B        = 2,
    CAPSULE_MODE_A    = 4,   // CAPSULE_MODE_A << i for body i
    CAPSULE_MODE_B    = 8
};

struct hkContactMgr
{
    virtual void v0();
    virtual void v1();
    virtual hkUint16 addContactPoint(const hkCdBody* a, const hkCdBody* b, const hkProcessCollisionInput* in, hkProcessCdPoint* cp);   // +0x8
    virtual int      reserveContactPoints(int n);   // +0xc (returns 0 on success)
};

struct hkAgent3ProcessInput
{
    const hkCdBody* m_bodyA;                // +0x0
    const hkCdBody* m_bodyB;                // +0x4
    const hkProcessCollisionInput* m_input; // +0x8
    hkContactMgr*   m_contactMgr;           // +0xc
    hkTransform     m_aTb;                  // +0x10
    float           m_distAtT1;             // +0x50
};
struct hkAgent3Input;

struct hkProcessCdPoint { hkUint32 m_data[12]; };   // 0x30 bytes; short id at +0x20

struct ContactRef { hkProcessCdPoint* m_contact; hkAgentEntry* m_entry; void* m_agentData; };
struct PotentialInfo
{
    ContactRef*        m_firstFreePotentialContact;     // +0x0
    hkProcessCdPoint** m_firstFreeRepresentativeContact;// +0x4
};
struct hkProcessCollisionOutput
{
    hkProcessCdPoint* m_firstFreeContactPoint;  // +0x0
    hkUint32 m_pad[0xc0f];
    PotentialInfo*    m_potentialContacts;      // +0x3040
};

// The agent data starts with the GSK cache (12 bytes), followed by the contact manifold at +0xc.
struct hkGskCache
{
    hkUint32 m_vertexPairs[2];  // hkUint16 m_vertices[4]: A's ids first (m_dimA of them), then B's
    hkInt8   m_dimA;          // +0x8
    hkInt8   m_dimB;          // +0x9
    hkUchar  m_maxDimA;       // +0xa
    hkUchar  m_gskFlags;      // +0xb
    // (stored as dwords so the stack copy below does not draw a /GS cookie, which the original lacks)
    hkUint16* vertices() { return (hkUint16*)m_vertexPairs; }
};

// Shape info block handed to the GSK closest-points routine.
struct hkGskInfo
{
    const hkTransform* m_aTb;
    const hkTransform* m_transformA;
    const hkShape*     m_shapeA;
    const hkShape*     m_shapeB;
    float              m_tolerance;
};

// ---- Havok monitor-stream timer commands (TLS) ------------------------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
extern "C" unsigned __int64 __rdtsc();
#pragma intrinsic(__rdtsc)
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char g_hkTimerEndTag0[];               // 0x0143cd94
extern const char g_hkTimerEndTag1[];               // 0x0149cc34 ("Et")

#define HK_TIMER_CMD(name) do { \
    void* end_ = TlsGetValue(g_hkMonitorStreamEndTls); \
    if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end_) { \
        hkUint32* c_ = (hkUint32*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
        c_[0] = (hkUint32)(name); \
        c_[1] = (hkUint32)__rdtsc(); \
        TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 3); } } while (0)

// ---- callees (cdecl, relocation-masked) --------------------------------------------------------------------
namespace hkPredGskAgent3
{
    void __cdecl sepNormal(const hkAgent3Input& input, void* agentData, hkVector4& sepNormalOut);           // 0x010ff8c0
}
extern int      __cdecl hkGsk_closestPoints(hkGskInfo* info, void* cache, hkVector4* sepNormal, hkVector4* out);  // 0x0110fa20
extern void     __cdecl hkGskManifold_cleanup(hkUchar* manifold, hkContactMgr* mgr);                                    // 0x0110fdd0
extern void     __cdecl hkGskManifold_removePoint(hkUchar* manifold, int idx);                                          // 0x0110fd70
extern void     __cdecl hkGskManifold_update(hkUchar* manifold, hkVector4* verts, int numRemoved,
                                             hkProcessCollisionOutput* out, hkContactMgr* mgr);                         // 0x0110fe20
extern unsigned __cdecl hkGskManifold_numRemoved(hkUchar* manifold, void* cache);                                       // 0x01111330
extern int      __cdecl hkGsk_addPoint(hkUchar* manifold, const hkCdBody* a, const hkCdBody* b,
                                       const hkProcessCollisionInput* in, void* cache, hkProcessCdPoint* cp,
                                       hkProcessCdPoint* start, hkContactMgr* mgr, int flag);                           // 0x01111d90
extern void     __cdecl hkGsk_toi(const hkAgent3ProcessInput* input, float minRadius, float t0, float t1,
                                  void* agentData, hkVector4* sepNormal, hkProcessCollisionOutput* out);                // 0x01112950

// out[i] = R * in[i] + t  (hkVector4Util::transformPoints, w cleared; unrolled by 4 as in the binary)
#define HK_XFORM_ONE(P) { \
        const float x = (P).x, y = (P).y, z = (P).z; \
        (P).x = (m10 * y + (m20 * z + m00 * x)) + tx; \
        (P).y = (m01 * x + (m11 * y + m21 * z)) + ty; \
        (P).z = (m02 * x + (m12 * y + m22 * z)) + tz; \
        (P).w = 0.0f; }
static __forceinline void transformPoints(const hkTransform* t, hkVector4* v, int n)
{
    const float m00 = t->col0[0], m01 = t->col0[1], m02 = t->col0[2];
    const float m10 = t->col1[0], m11 = t->col1[1], m12 = t->col1[2];
    const float m20 = t->col2[0], m21 = t->col2[1], m22 = t->col2[2];
    const float tx = t->trans[0], ty = t->trans[1], tz = t->trans[2];
    int i = 0;
    if (n >= 4)
    {
        int blocks = ((n - 4) >> 2) + 1;
        i = blocks * 4;
        hkVector4* p = v;
        do {
            HK_XFORM_ONE(p[0]) HK_XFORM_ONE(p[1]) HK_XFORM_ONE(p[2]) HK_XFORM_ONE(p[3])
            p += 4;
        } while (--blocks);
    }
    for (; i < n; ++i)
        HK_XFORM_ONE(v[i])
}

// Gather both bodies' supporting vertices for the manifold and move them into world space.
static __forceinline void getPoints(const hkAgent3ProcessInput* in, hkUchar* manifold, hkVector4* verts, const hkVector4* sepNormal)
{
    const hkCdBody* bodyA = in->m_bodyA;
    const hkCdBody* bodyB = in->m_bodyB;
    const hkShape* shapeA = bodyA->m_shape;
    const hkShape* shapeB = bodyB->m_shape;
    float info[8];
    info[0] = sepNormal->x; info[1] = sepNormal->y; info[2] = sepNormal->z; info[3] = sepNormal->w;
    info[4] = shapeA->m_radius;
    info[5] = shapeB->m_radius;
    info[6] = in->m_input->m_tolerance;
    float s = (info[5] + info[4]) + info[6];
    info[7] = s * s;
    (void)info;
    const int numPoints = manifold[2];
    if (numPoints)
    {
        const hkUint16* idsA = (const hkUint16*)(manifold + 4 + numPoints * 8);
        const int numA = manifold[0];
        shapeA->getSupportingVertices(idsA, numA, verts);
        transformPoints(bodyA->m_motion, verts, numA);
        const int numB = manifold[1];
        shapeB->getSupportingVertices(idsA + numA, numB, verts + numA);
        transformPoints(bodyB->m_motion, verts + numA, numB);
    }
}

// Replace every cylinder body that is in capsule mode by a temporary child body holding an equivalent
// capsule (cylinder end points, cylinder radius + convex radius + 0.002). The original body pointers go to
// savedBodies[i] (0 when not replaced).
static __forceinline void replaceCylindersByCapsules(const hkCdBody** bodyPtr[2], const int capsuleMode[2],
                                                     const hkCdBody* savedBodies[2], hkCdBody tmpBodies[2])
{
    for (int i = 0; i < 2; i++)
    {
        if (capsuleMode[i])
        {
            const hkCylinderShape* cyl = static_cast<const hkCylinderShape*>((*bodyPtr[i])->m_shape);
            const float convexRadius = cyl->m_radius;
            hkCapsuleShape* capsule = new hkCapsuleShape(cyl->m_vertexA, cyl->m_vertexB,
                                                         cyl->getCylinderRadius() + convexRadius + 0.002f);
            hkCdBody* body = new (&tmpBodies[i]) hkCdBody(*bodyPtr[i]);
            body->setShape(capsule, body->m_parent->m_shapeKey);
            savedBodies[i] = *bodyPtr[i];
            *bodyPtr[i] = body;
        }
        else
            savedBodies[i] = 0;
    }
}

// Cylinder vertex ids carry the cap in bit 7; the capsule's two vertices have ids 16 (vertexB) and 0 (vertexA).
static __forceinline hkUint16 cylinderToCapsuleVertexId(hkUint16 id)
{
    return (hkUint16)((1 - (((hkUchar)id >> 7) & 1)) << 4);
}

namespace hkPredGskCylinderAgent3
{

// @ 0x010fdf80
void* __cdecl process(const hkAgent3ProcessInput& input, hkAgentEntry* entry, void* agentData,
                      hkVector4* separatingNormal, hkProcessCollisionOutput& result)
{
    HK_TIMER_CMD("TtPredGskf3");
    {
        void* end_ = TlsGetValue(g_hkMonitorStreamEndTls);
        if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end_) {
            hkUint32* c_ = (hkUint32*)TlsGetValue(g_hkMonitorStreamCurrentTls);
            c_[0] = (hkUint32)"Ltintern";
            c_[3] = (hkUint32)"init";
            c_[1] = (hkUint32)__rdtsc();
            TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 4);
        }
    }

    float dist = input.m_distAtT1;
    const hkCdBody** bodyPtr[2];
    bodyPtr[1] = const_cast<const hkCdBody**>(&input.m_bodyB);
    const hkUint32 flags = entry->m_userData;
    int isCylinder[2];
    isCylinder[0] = flags & CYLINDER_A;
    isCylinder[1] = flags & CYLINDER_B;
    int capsuleMode[2];
    capsuleMode[1] = flags & CAPSULE_MODE_B;
    const hkCdBody* savedBodies[2];
    savedBodies[0] = 0;
    savedBodies[1] = 0;
    capsuleMode[0] = flags & CAPSULE_MODE_A;
    hkUchar* const manifold = (hkUchar*)agentData + 0xc;
    bodyPtr[0] = const_cast<const hkCdBody**>(&input.m_bodyA);

    hkVector4 sepNormal;
    hkPredGskAgent3::sepNormal(reinterpret_cast<const hkAgent3Input&>(input), agentData, sepNormal);

    hkGskCache cacheCopy;   // shares its stack slot with the axis vector below in the binary
    hkCdBody tmpBodies[2];
    hkVector4 sepOut;
    hkVector4 verts[16];

    // ---- cylinder <-> capsule switching (hysteresis on |axis . separatingNormal|) ----
    for (int i = 0; i < 2; i++)
    {
        if (!isCylinder[i])
            continue;
        const hkCdBody* body = *bodyPtr[i];
        const hkCylinderShape* cyl = static_cast<const hkCylinderShape*>(body->m_shape);
        hkVector4 axis;
        axis.x = cyl->m_vertexB.x - cyl->m_vertexA.x;
        axis.y = cyl->m_vertexB.y - cyl->m_vertexA.y;
        axis.z = cyl->m_vertexB.z - cyl->m_vertexA.z;
        const float aw = cyl->m_vertexB.w - cyl->m_vertexA.w;
        const float len2 = axis.x * axis.x + axis.y * axis.y + axis.z * axis.z;
        const float invLen = (len2 == 0.0f) ? 0.0f : 1.0f / sqrtf(len2);
        axis.x *= invLen;
        axis.y *= invLen;
        axis.z *= invLen;
        axis.w = aw * invLen;
        axis.setRotatedDir(*reinterpret_cast<const hkRotation*>(body->m_motion), axis);
        const float cosAngle = fabsf(sepNormal.x * axis.x + sepNormal.z * axis.z + sepNormal.y * axis.y);

        if (capsuleMode[i])
        {
            if (cosAngle > 0.17f)
            {
                capsuleMode[i] = 0;
                entry->m_userData &= ~(CAPSULE_MODE_A << i);
                hkGskManifold_cleanup(manifold, input.m_contactMgr);
                entry->m_numContactPoints = manifold[2];
                *(hkUint32*)manifold = 0;
            }
        }
        else if (cosAngle < 0.085f)
        {
            capsuleMode[i] = 1;
            entry->m_userData |= (CAPSULE_MODE_A << i);
            hkGskManifold_cleanup(manifold, input.m_contactMgr);
            entry->m_numContactPoints = manifold[2];
            *(hkUint32*)manifold = 0;
        }
    }

    const hkCollisionQualityInfo* quality = input.m_input->m_collisionQualityInfo;

    if (quality->m_useContinuousPhysics)
    {
        const hkCdBody* a = input.m_bodyA;
        while (a->m_parent) a = a->m_parent;
        const hkCdBody* b = input.m_bodyB;
        while (b->m_parent) b = b->m_parent;
        float minRadius = static_cast<const hkCollidableRoot*>(b)->m_allowedPenetrationDepth;
        if (static_cast<const hkCollidableRoot*>(a)->m_allowedPenetrationDepth < minRadius)
            minRadius = static_cast<const hkCollidableRoot*>(a)->m_allowedPenetrationDepth;

        float t0 = minRadius * quality->m_minExtraSeparation + separatingNormal->w;
        float t0b = minRadius * quality->m_minSeparation;
        if (t0b < t0) t0 = t0b;
        if (dist < t0)
        {
            float t1 = minRadius * quality->m_toiExtraSeparation + separatingNormal->w;
            float t1b = minRadius * quality->m_toiSeparation;
            if (t1b < t1) t1 = t1b;
            HK_TIMER_CMD("Sttoi");
            hkGsk_toi(&input, minRadius, t0, t1, agentData, separatingNormal, &result);
            goto process_gsk;
        }
    }

    if (quality->m_manifoldTimDistance < dist)
    {
        // far enough apart: only refresh the existing manifold points
        separatingNormal->w = dist;
        if (manifold[2])
        {
            HK_TIMER_CMD("StgetPoints");
            replaceCylindersByCapsules(bodyPtr, capsuleMode, savedBodies, tmpBodies);
            getPoints(&input, manifold, verts, separatingNormal);
            hkGskManifold_update(manifold, verts, 0, &result, input.m_contactMgr);
            if (manifold[2] && result.m_potentialContacts)
            {
                *(hkUint32*)result.m_potentialContacts->m_firstFreeRepresentativeContact =
                    (hkUint32)((char*)result.m_firstFreeContactPoint - manifold[2] * 0x30);
                result.m_potentialContacts->m_firstFreeRepresentativeContact =
                    (hkProcessCdPoint**)((char*)result.m_potentialContacts->m_firstFreeRepresentativeContact + 4);
            }
        }
        goto restore_bodies;
    }

process_gsk:
    HK_TIMER_CMD("Stprocess");
    replaceCylindersByCapsules(bodyPtr, capsuleMode, savedBodies, tmpBodies);
    {
        // The GSK routines see a cache whose cylinder vertex ids are converted to capsule ids.
        hkGskCache* cache = (hkGskCache*)agentData;
        if (capsuleMode[0] || capsuleMode[1])
        {
            cache = &cacheCopy;
            cacheCopy = *(const hkGskCache*)agentData;
            if (capsuleMode[0])
            {
                cacheCopy.vertices()[0] = cylinderToCapsuleVertexId(cacheCopy.vertices()[0]);
                if (cacheCopy.m_dimA > 1)
                {
                    // cylinder edge/face -> the capsule's segment; B's vertex moves down one slot
                    cacheCopy.vertices()[0] = 16;
                    cacheCopy.vertices()[1] = 0;
                    if (cacheCopy.m_dimA == 3)
                    {
                        cacheCopy.m_dimA = 2;
                        cacheCopy.vertices()[2] = cacheCopy.vertices()[3];
                    }
                }
            }
            if (capsuleMode[1])
            {
                hkUint16& v = cacheCopy.vertices()[cacheCopy.m_dimA];
                v = cylinderToCapsuleVertexId(v);
                if (cacheCopy.m_dimB > 1)
                {
                    cacheCopy.vertices()[cacheCopy.m_dimA] = 16;
                    cacheCopy.vertices()[cacheCopy.m_dimA + 1] = 0;
                    if (cacheCopy.m_dimB == 3)
                        cacheCopy.m_dimB = 2;
                }
            }
        }

        {
            hkGskInfo info;
            info.m_aTb        = &input.m_aTb;
            info.m_transformA = input.m_bodyA->m_motion;
            info.m_shapeA     = input.m_bodyA->m_shape;
            info.m_shapeB     = input.m_bodyB->m_shape;
            info.m_tolerance  = input.m_input->m_tolerance;
            int gsk = hkGsk_closestPoints(&info, cache, separatingNormal, &sepOut);
            if (gsk == 1)
            {
                if (manifold[2])
                    hkGskManifold_cleanup(manifold, input.m_contactMgr);
                goto restore_normal;
            }
        }

        const int numRemoved = (int)(hkGskManifold_numRemoved(manifold, cache) & 0xff);
        hkProcessCdPoint* const start = result.m_firstFreeContactPoint;
        if (numRemoved < (int)manifold[2])
        {
            getPoints(&input, manifold, verts, separatingNormal);
            hkGskManifold_update(manifold, verts, numRemoved, &result, input.m_contactMgr);
        }

        hkProcessCdPoint* cp = result.m_firstFreeContactPoint;
        {
            hkVector4* d = (hkVector4*)cp;
            d[0] = sepOut;
            d[1] = *separatingNormal;
        }

        if (numRemoved == 0)
        {
            const hkCollisionQualityInfo* q = input.m_input->m_collisionQualityInfo;
            float thresh = ((int)cache->m_dimB + (int)cache->m_dimA == 4) ? q->m_create4dContact : q->m_createContact;
            if (separatingNormal->w < thresh)
            {
                int r = hkGsk_addPoint(manifold, input.m_bodyA, input.m_bodyB, input.m_input, cache, cp, start,
                                       input.m_contactMgr, 1);
                if (r == 4)
                {
                    short* cpId = (short*)((char*)cp + 0x20);
                    if (*cpId == -1)
                    {
                        bool remove = false;
                        if (result.m_potentialContacts)
                        {
                            if (input.m_contactMgr->reserveContactPoints(1) == 0)
                            {
                                ContactRef* ref = result.m_potentialContacts->m_firstFreePotentialContact;
                                result.m_potentialContacts->m_firstFreePotentialContact = ref + 1;
                                ref->m_entry = entry;
                                ref->m_contact = cp;
                                ref->m_agentData = agentData;
                                result.m_firstFreeContactPoint = (hkProcessCdPoint*)((char*)result.m_firstFreeContactPoint + 0x30);
                            }
                            else
                                remove = true;
                        }
                        else
                        {
                            hkUint16 id = input.m_contactMgr->addContactPoint(input.m_bodyA, input.m_bodyB, input.m_input, cp);
                            *cpId = (short)id;
                            if (id == 0xffff)
                                remove = true;
                            else
                            {
                                *(hkUint16*)(manifold + 6) = id;
                                result.m_firstFreeContactPoint = (hkProcessCdPoint*)((char*)result.m_firstFreeContactPoint + 0x30);
                            }
                        }
                        if (remove)
                        {
                            hkGskManifold_removePoint(manifold, 0);
                            cp = start;
                        }
                    }
                    else
                        result.m_firstFreeContactPoint = (hkProcessCdPoint*)((char*)result.m_firstFreeContactPoint + 0x30);
                }
                else if (r == 5)
                    cp = start;
                else if (r == 6)
                {
                    result.m_firstFreeContactPoint = (hkProcessCdPoint*)((char*)result.m_firstFreeContactPoint - 0x30);
                    cp = start;
                }
                else
                    cp = start + r;
            }
        }
        else
        {
            *(hkUint16*)((char*)cp + 0x20) = *(hkUint16*)(manifold + 6);
            result.m_firstFreeContactPoint = (hkProcessCdPoint*)((char*)result.m_firstFreeContactPoint + 0x30);
        }

        if (result.m_potentialContacts && cp < result.m_firstFreeContactPoint)
        {
            *result.m_potentialContacts->m_firstFreeRepresentativeContact = cp;
            result.m_potentialContacts->m_firstFreeRepresentativeContact =
                (hkProcessCdPoint**)((char*)result.m_potentialContacts->m_firstFreeRepresentativeContact + 4);
        }
    }

restore_normal:
    *separatingNormal = sepNormal;

restore_bodies:
    for (int i = 0; i < 2; i++)
    {
        if (savedBodies[i])
        {
            const hkCdBody** slot = bodyPtr[i];
            const_cast<hkShape*>((*slot)->m_shape)->removeReference();
            *slot = savedBodies[i];
        }
    }

    entry->m_numContactPoints = manifold[2];
    HK_TIMER_CMD(g_hkTimerEndTag0);
    HK_TIMER_CMD(g_hkTimerEndTag1);
    return (char*)agentData + ((((manifold[0] + manifold[2] * 4 + manifold[1]) * 2) + 0x1f) & 0xfffffff0);
}

}
