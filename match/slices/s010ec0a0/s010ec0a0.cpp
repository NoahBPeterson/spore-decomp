// Havok 3.1.0: hkGskfAgent::processCollisionNoTim @ 0x010ec700
// Flags: /O2 /MD /Gy /TP (x87 float, 16-byte aligned frame)
//
// The non-predictive GSK convex-convex agent's step (no time-of-impact handling):
//   1. aTb = inverse(A) * B, run the GSK closest-points query on the agent's cache.
//   2. If the bodies are farther apart than the tolerance (status 1), just clean up the manifold.
//   3. Otherwise drop the manifold points the cache says changed, re-fetch the vertices of the surviving ones
//      in world space (4x-unrolled hkVector4Util::transformPoints, inlined twice) and re-validate them with
//      hkGskManifold_verifyAndGetPoints, write the new closest point (separating normal) as contact point and
//      add / reuse a contact id through the contact manager.
// Agent layout (binary offsets): +8 contactMgr, +0xc hkGskCache, +0x20 separating normal (w = distance),
// +0x30 hkGskManifold (+0x32 numContactPoints, +0x36 first contact point id).
// Same shape as the agent3 version in slice s010ff9e0, with this-relative state instead of agent3 data.
#include "types.h"
#include <new>

typedef unsigned char  hkUchar;
typedef unsigned short hkUint16;
typedef unsigned int   hkUint32;

class __declspec(align(16)) hkVector4 { public: float x, y, z, w; };
class hkTransform
{ public:
    hkVector4 m_col0, m_col1, m_col2, m_translation;   // 0x40 bytes
    void setMulInverseMul(const hkTransform& a, const hkTransform& b);   // 0x010810f0: this = inverse(a) * b
};

class hkConvexShape
{ public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void convertVertexIdsToVertices(const hkUint16* ids, int numIds, hkVector4* verticesOut) const;   // slot 10
    hkUint32 m_pad[2];
    float    m_radius;                                  // +0xc
};

class hkCdBody
{ public:
    const hkConvexShape* m_shape;                       // +0x0
    hkUint32             m_shapeKey;                    // +0x4
    const hkTransform*   m_motion;                      // +0x8
    const hkCdBody*      m_parent;                      // +0xc
};

struct hkCollisionQualityInfo
{
    float m_keepContact;                                // +0x0
    float m_create4dContact;                            // +0x4
    float m_createContact;                              // +0x8
};
struct hkProcessCollisionInput
{
    void*  m_dispatcher;                                // +0x0
    void*  m_filter;                                    // +0x4
    float  m_tolerance;                                 // +0x8
    hkUint32 m_pad[0x0d - 3];
    const hkCollisionQualityInfo* m_collisionQualityInfo;   // +0x28 (pad up to it)
};

struct hkProcessCdPoint { hkVector4 m_position; hkVector4 m_separatingNormal; hkUint16 m_id; hkUint16 m_pad[7]; };   // 0x30

class hkContactMgr
{ public:
    virtual void v0();
    virtual void v1();
    virtual hkUint16 addContactPoint(const hkCdBody* a, const hkCdBody* b, const hkProcessCollisionInput* in,
                                     hkProcessCdPoint* cp);   // +0x8
};

struct PotentialInfo
{
    void*              m_firstFreePotentialContact;     // +0x0
    hkProcessCdPoint** m_firstFreeRepresentativeContact;// +0x4
};
struct hkProcessCollisionOutput
{
    hkProcessCdPoint* m_firstFreeContactPoint;          // +0x0
    hkUint32          m_pad[0xc0f];
    PotentialInfo*    m_potentialContacts;              // +0x3040
};

struct hkGskCache
{
    hkUint16    m_vertices[4];                          // +0x0
    signed char m_dimA, m_dimB, m_maxDimA, m_maxDimB;   // +0x8
};

struct hkGskManifoldWork
{
    hkVector4 m_vertices[16];                           // +0x000 vertices of A then B (world space)
    hkVector4 m_masterNormal;                           // +0x100
    float     m_radiusA;                                // +0x110
    float     m_radiusB;                                // +0x114
    float     m_keepContact;                            // +0x118
    float     m_radiusSumSqrd;                          // +0x11c
};

struct hkGskManifold
{
    hkUchar  m_numVertsA;                               // +0
    hkUchar  m_numVertsB;                               // +1
    hkUchar  m_numContactPoints;                        // +2
    hkUchar  m_pad;
    struct ContactPoint { hkUchar m_dimA, m_dimB; hkUint16 m_id; hkUint32 m_allVerts; } m_contactPoints[4];
};

// Shape info block handed to the GSK closest-points routine.
struct hkGskInfo
{
    const hkTransform*   m_aTb;
    const hkTransform*   m_transformA;
    const hkConvexShape* m_shapeA;
    const hkConvexShape* m_shapeB;
    float                m_tolerance;
};

// ---- callees (cdecl) ----------------------------------------------------------------------------------------
extern int      __cdecl hkGsk_closestPoints(hkGskInfo* info, hkGskCache* cache, hkVector4* sepNormal, hkVector4* out);   // 0x0110fa20
extern void     __cdecl hkGskManifold_cleanup(hkGskManifold* manifold, hkContactMgr* mgr);                              // 0x0110fdd0
extern void     __cdecl hkGskManifold_removePoint(hkGskManifold* manifold, int idx);                                    // 0x0110fd70
extern void     __cdecl hkGskManifold_verifyAndGetPoints(hkGskManifold* manifold, const hkVector4* work, int firstPointIndex,
                                                         hkProcessCollisionOutput* out, hkContactMgr* mgr);             // 0x0110fe20
extern unsigned __cdecl hkGskManifold_numRemoved(hkGskManifold* manifold, hkGskCache* cache);                           // 0x01111330
extern int      __cdecl hkGsk_addPoint(hkGskManifold* manifold, const hkCdBody* a, const hkCdBody* b,
                                       const hkProcessCollisionInput* in, hkGskCache* cache, hkProcessCdPoint* cp,
                                       hkProcessCdPoint* start, hkContactMgr* mgr, int flag);                           // 0x01111d90

// hkVector4::_setTransformedPos: out = t * in (w cleared)
static __forceinline void setTransformedPos(hkVector4& out, const hkTransform& t, const hkVector4& b)
{
    const float x = b.x, y = b.y, z = b.z;
    out.x = t.m_col0.x * x + (t.m_col1.x * y + t.m_col2.x * z) + t.m_translation.x;
    out.y = t.m_col0.y * x + (t.m_col1.y * y + t.m_col2.y * z) + t.m_translation.y;
    out.z = t.m_col0.z * x + (t.m_col1.z * y + t.m_col2.z * z) + t.m_translation.z;
    out.w = 0.0f;
}

// hkVector4Util::transformPoints: Havok copies the transform first so the loop cannot alias it.
static __forceinline void transformPoints(const hkTransform& t, hkVector4* v, int n)
{
    const hkTransform unaliased = t;
    for (int i = 0; i < n; i++)
        setTransformedPos(v[i], unaliased, v[i]);
}

struct hkCollisionInput;

// Packed vector used inside the agent: VC7.1 aligns the first data member of a class that contains an
// over-aligned member to 16 bytes, which would move every retail field by 0x0c.  The agent's normal does not
// need vector alignment, so keep it packed and cast only at the calls that require hkVector4*.
class hkVector4NoAlign { public: float x, y, z, w; };

struct hkGskfAgentBase
{
    virtual ~hkGskfAgentBase();
    virtual void slot1();
    virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                  const hkProcessCollisionInput& input, hkProcessCollisionOutput& result);

    hkGskfAgentBase(const hkCdBody& bodyA, const hkCdBody& bodyB, hkContactMgr* mgr);   // 0x010ed2a0

    hkUint16        m_memSizeAndFlags;                  // +4
    short           m_referenceCount;                   // +6
    hkContactMgr*   m_contactMgr;                       // +8
    hkGskCache      m_cache;                            // +0xc
    float           m_timeOfSeparatingNormal;           // +0x18
    float           m_allowedPenetration;               // +0x1c
    hkVector4NoAlign m_separatingNormal;                // +0x20 (w = distance)
    union
    {
        hkGskManifold m_manifold;                       // +0x30
        hkUint32      m_manifoldDword;                  // +0x30, zeroed by the constructor
    };
};

struct hkGskfAgent : public hkGskfAgentBase
{
    hkGskfAgent(const hkCdBody& bodyA, const hkCdBody& bodyB, hkContactMgr* mgr);      // 0x010ec660
    virtual void cleanup();                                                             // 0x010ec590
    virtual void removePoint(hkUint16 id);                                              // 0x010ec5b0
    virtual void commitPotential(hkUint16 id);                                          // 0x010ec5f0
    virtual void createZombie(hkUint16 id);                                             // 0x010ec630

    static hkGskfAgent* createGskfAgent(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                        const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010ec690

    void processCollisionNoTim(const hkCdBody& bodyA, const hkCdBody& bodyB,
                               const hkProcessCollisionInput& input, hkProcessCollisionOutput& result);   // 0x010ec700
};

// @ 0x010ec700
void hkGskfAgent::processCollisionNoTim(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                        const hkProcessCollisionInput& input, hkProcessCollisionOutput& result)
{
    hkTransform aTb;
    aTb.setMulInverseMul(*bodyA.m_motion, *bodyB.m_motion);

    hkGskInfo info;
    info.m_aTb        = &aTb;
    info.m_transformA = bodyA.m_motion;
    info.m_shapeA     = bodyA.m_shape;
    info.m_shapeB     = bodyB.m_shape;
    info.m_tolerance  = input.m_tolerance;

    hkVector4 closest;
    hkContactMgr* const mgr = m_contactMgr;
    hkGskManifold* const manifold = &m_manifold;
    hkGskCache* const cache = &m_cache;
    hkVector4* const sepNormal = (hkVector4*)&m_separatingNormal;

    if (hkGsk_closestPoints(&info, cache, sepNormal, &closest) == 1)
    {
        if (manifold->m_numContactPoints)
            hkGskManifold_cleanup(manifold, mgr);
        return;
    }

    const int numRemoved = (int)(hkGskManifold_numRemoved(manifold, cache) & 0xff);
    hkProcessCdPoint* const start = result.m_firstFreeContactPoint;
    if (numRemoved < (int)manifold->m_numContactPoints)
    {
        // hkGskManifold_init
        hkGskManifoldWork work;
        const hkConvexShape* shapeA = bodyA.m_shape;
        const hkConvexShape* shapeB = bodyB.m_shape;
        work.m_keepContact = input.m_tolerance;
        work.m_radiusA = shapeA->m_radius;
        work.m_radiusB = shapeB->m_radius;
        const float radiusSum = work.m_radiusB + work.m_radiusA + work.m_keepContact;
        work.m_radiusSumSqrd = radiusSum * radiusSum;
        work.m_masterNormal = *sepNormal;
        if (manifold->m_numContactPoints)
        {
            const hkUint16* idsA = (const hkUint16*)((const char*)manifold + 4 + manifold->m_numContactPoints * 8);
            const int numA = manifold->m_numVertsA;
            shapeA->convertVertexIdsToVertices(idsA, numA, work.m_vertices);
            transformPoints(*bodyA.m_motion, work.m_vertices, numA);
            shapeB->convertVertexIdsToVertices(idsA + numA, manifold->m_numVertsB, work.m_vertices + numA);
            transformPoints(*bodyB.m_motion, work.m_vertices + numA, manifold->m_numVertsB);
        }
        hkGskManifold_verifyAndGetPoints(manifold, work.m_vertices, numRemoved, &result, mgr);
    }

    hkProcessCdPoint* cp = result.m_firstFreeContactPoint;
    cp->m_position = closest;
    cp->m_separatingNormal = *sepNormal;

    if (numRemoved == 0)
    {
        const hkCollisionQualityInfo* q = input.m_collisionQualityInfo;
        const float thresh = ((int)m_cache.m_dimA + (int)m_cache.m_dimB == 4) ? q->m_create4dContact : q->m_createContact;
        if (sepNormal->w < thresh)
        {
            const int r = hkGsk_addPoint(manifold, &bodyA, &bodyB, &input, cache, cp, start, mgr, 1);
            if (r == 4)
            {
                if (cp->m_id == 0xffff)
                {
                    cp->m_id = mgr->addContactPoint(&bodyA, &bodyB, &input, cp);
                    if (cp->m_id == 0xffff)
                    {
                        hkGskManifold_removePoint(manifold, 0);
                        cp = start;
                    }
                    else
                    {
                        manifold->m_contactPoints[0].m_id = cp->m_id;
                        result.m_firstFreeContactPoint = result.m_firstFreeContactPoint + 1;
                    }
                }
                else
                    result.m_firstFreeContactPoint = result.m_firstFreeContactPoint + 1;
            }
            else if (r == 5)
                cp = start;
            else if (r == 6)
            {
                result.m_firstFreeContactPoint = result.m_firstFreeContactPoint - 1;
                cp = start;
            }
            else
                cp = start + r;
        }
    }
    else
    {
        cp->m_id = manifold->m_contactPoints[0].m_id;
        result.m_firstFreeContactPoint = result.m_firstFreeContactPoint + 1;
    }

    if (result.m_potentialContacts && cp < result.m_firstFreeContactPoint)
    {
        *result.m_potentialContacts->m_firstFreeRepresentativeContact = cp;
        result.m_potentialContacts->m_firstFreeRepresentativeContact =
            result.m_potentialContacts->m_firstFreeRepresentativeContact + 1;
    }
}

// ---- shared Havok collision types for this slice ---------------------------------------------------------------
#define HK_REAL_MAX 3.40282e+38f
typedef double hkX87Real;

class hkBool
{
public:
    hkBool() {}
    hkBool(bool b) : m_bool(b ? 1 : 0) {}
    operator bool() const { return m_bool != 0; }
private:
    char m_bool;
};

struct hkCollisionInput
{
    void*   m_dispatcher;                 // +0x00
    void*   m_filter;                     // +0x04
    float   m_tolerance;                  // +0x08
    hkBool  m_createPredictiveAgents;     // +0x0c
};

struct hkCollisionAgentConfig
{
    float m_iterativeLinearCastEarlyOutDistance;   // +0x0
    int   m_iterativeLinearCastMaxIterations;      // +0x4
};

struct hkLinearCastCollisionInput : public hkCollisionInput
{
    hkVector4 m_path;                     // +0x10
    float     m_maxExtraPenetration;      // +0x20
    float     m_cachedPathLength;         // +0x24
    hkCollisionAgentConfig* m_config;     // +0x28
};

class __declspec(align(16)) hkContactPoint
{
public:
    hkVector4 m_position;                 // +0x00
    hkVector4 m_separatingNormal;         // +0x10 (w = distance)
    void setSeparatingNormal(const hkVector4& normal, float dist);   // 0x010d0040
};

struct hkCdPoint
{
    hkContactPoint m_contact;             // +0x00
    const hkCdBody* m_cdBodyA;            // +0x20
    const hkCdBody* m_cdBodyB;            // +0x24
};

class hkCdPointCollector
{
public:
    virtual void slot0();
    virtual void addCdPoint(const hkCdPoint& point);   // +0x04
    float m_earlyOutDistance;                          // +0x04
    hkCdPointCollector() : m_earlyOutDistance(HK_REAL_MAX) {}
};

class hkSimpleClosestContactCollector : public hkCdPointCollector
{
public:
    hkBool         m_hasHit;              // +0x08
    hkContactPoint m_hitContact;          // +0x10
    hkSimpleClosestContactCollector() : hkCdPointCollector() { reset(); }
    void reset() { m_hasHit = hkBool(false); m_hitContact.m_separatingNormal.w = HK_REAL_MAX; }
    virtual void addCdPoint(const hkCdPoint& point);
};

class hkMotionState : public hkTransform
{
public:
    hkUint32 m_pad[0x1c];                 // +0x40 .. +0xaf (size 0xb0)
    hkMotionState& operator=(const hkMotionState& other);   // 0x010df5d0
};

class hkMemory
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void* allocateChunk(int nbytes, int cl);   // +0x10
    static hkMemory* s_instance;                       // 0x016e4178
};

class hkFeatureContactPoint
{
public:
    hkUchar  m_featureIdA;                // +0x0
    hkUchar  m_featureIdB;                // +0x1
    hkUint16 m_contactPointId;            // +0x2
};

class hkBoxBoxManifold
{
public:
    hkBool findInManifold(const hkFeatureContactPoint& cp);                     // 0x010ec4c0
    hkBool findInManifoldExtern(const hkFeatureContactPoint& cp);               // same ABI, opaque to the optimizer
    int    addPoint(const hkCdBody& bodyA, const hkCdBody& bodyB,
                    hkFeatureContactPoint& fcp);                                // 0x010ec540
    void   removePoint(int index);                                              // 0x010ec4a0
    hkBoxBoxManifold* init();                                                   // 0x010ec500 (retail leaves this in eax)

    hkFeatureContactPoint m_contactPoints[8];   // +0x00 (8 * 4 bytes)
    hkUchar m_faceVertexFeatureCount;           // +0x20
    hkUchar m_numPoints;                        // +0x21
    hkBool  m_isComplete;                       // +0x22
    hkBool  m_manifoldNormalInitialized;        // +0x23
};

class hkCollisionAgent
{
public:
    virtual ~hkCollisionAgent();                                                    // +0x00
    virtual void slot1();                                                           // +0x04
    virtual void getPenetrations(const hkCdBody& a, const hkCdBody& b,
                                 const hkCollisionInput& input, void* collector);    // +0x08
    virtual void getClosestPoints(const hkCdBody& a, const hkCdBody& b,
                                  const hkCollisionInput& input,
                                  hkCdPointCollector& collector);                   // +0x0c
    virtual void linearCast(const hkCdBody& a, const hkCdBody& b,
                            const hkLinearCastCollisionInput& input,
                            hkCdPointCollector& castCollector,
                            hkCdPointCollector* startCollector);                    // +0x10
};

class hkIterativeLinearCastAgent : public hkCollisionAgent
{
public:
    virtual void linearCast(const hkCdBody& a, const hkCdBody& b,
                            const hkLinearCastCollisionInput& input,
                            hkCdPointCollector& castCollector,
                            hkCdPointCollector* startCollector);
};

struct hkGskfAgentVtblView { void** m_vptr; };

// @ 0x010ec0a0
void hkIterativeLinearCastAgent::linearCast(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                            const hkLinearCastCollisionInput& input,
                                            hkCdPointCollector& castCollector,
                                            hkCdPointCollector* startCollector)
{
    hkCollisionInput closestInput;
    closestInput.m_dispatcher = input.m_dispatcher;
    closestInput.m_filter = input.m_filter;
    closestInput.m_tolerance = input.m_tolerance + input.m_cachedPathLength;
    closestInput.m_createPredictiveAgents = input.m_createPredictiveAgents;

    hkSimpleClosestContactCollector collector;
    getClosestPoints(bodyA, bodyB, closestInput, collector);
    if (!collector.m_hasHit)
        return;

    hkCdPoint point;
    point.m_contact = collector.m_hitContact;
    point.m_cdBodyA = &bodyA;
    point.m_cdBodyB = &bodyB;
    float dist = collector.m_hitContact.m_separatingNormal.w;
    if (dist < input.m_tolerance && startCollector != 0)
        startCollector->addCdPoint(point);

    const hkVector4& n = collector.m_hitContact.m_separatingNormal;
    hkX87Real d = ((hkX87Real)n.x * input.m_path.x + (hkX87Real)n.z * input.m_path.z) +
                  (hkX87Real)n.y * input.m_path.y;
    float distAfter = (float)(dist + d);
    if (distAfter > 0.0f)
        return;
    if (d + input.m_maxExtraPenetration >= 0.0)
        return;

    if (!(dist <= input.m_config->m_iterativeLinearCastEarlyOutDistance))
    {
        hkSimpleClosestContactCollector collector2;
        point.m_contact.m_separatingNormal.w =
            (float)((hkX87Real)dist / ((hkX87Real)dist - distAfter));

        hkMotionState movedMotion;
        movedMotion = *(const hkMotionState*)bodyA.m_motion;
        hkCdBody movedBody;
        movedBody.m_shape = bodyA.m_shape;
        movedBody.m_shapeKey = bodyA.m_shapeKey;
        movedBody.m_motion = &movedMotion;
        movedBody.m_parent = &bodyA;

        hkVector4* movedTrans = &movedMotion.m_translation;
        const hkVector4* origTrans = &((const hkMotionState*)bodyA.m_motion)->m_translation;
        for (int i = input.m_config->m_iterativeLinearCastMaxIterations - 1; i >= 0; --i)
        {
            collector2.reset();
            float f = point.m_contact.m_separatingNormal.w;
            movedTrans->x = f * input.m_path.x + origTrans->x;
            movedTrans->y = f * input.m_path.y + origTrans->y;
            movedTrans->z = f * input.m_path.z + origTrans->z;
            movedTrans->w = f * input.m_path.w + origTrans->w;
            getClosestPoints(movedBody, bodyB, closestInput, collector2);
            if (!collector2.m_hasHit)
                return;
            const hkVector4& n2 = collector2.m_hitContact.m_separatingNormal;
            hkX87Real dot = ((hkX87Real)n2.y * input.m_path.y + (hkX87Real)n2.z * input.m_path.z) +
                            (hkX87Real)n2.x * input.m_path.x;
            if (dot >= 0.0)
                return;
            float curDist = n2.w;
            hkX87Real negDot = -dot;
            if (negDot < (hkX87Real)f * negDot + curDist)
                return;
            hkX87Real newFrac = curDist / negDot + f;
            if (newFrac > castCollector.m_earlyOutDistance)
                return;
            point.m_contact.m_position = collector2.m_hitContact.m_position;
            point.m_contact.setSeparatingNormal(n2, (float)newFrac);
            if (curDist <= input.m_config->m_iterativeLinearCastEarlyOutDistance)
                break;
        }
        castCollector.addCdPoint(point);
        return;
    }

    if (dist <= 0.0f)
    {
        point.m_contact.m_separatingNormal.w = 0.0f;
        castCollector.addCdPoint(point);
        return;
    }
    hkX87Real frac = (hkX87Real)dist / ((hkX87Real)dist - distAfter);
    if (!(frac > castCollector.m_earlyOutDistance))
    {
        point.m_contact.m_separatingNormal.w = (float)frac;
        castCollector.addCdPoint(point);
    }
}

// @ 0x010ec4a0
void hkBoxBoxManifold::removePoint(int index)
{
    m_isComplete = false;
    m_contactPoints[index] = m_contactPoints[m_numPoints - 1];
    --m_numPoints;
}

// @ 0x010ec4c0
hkBool hkBoxBoxManifold::findInManifold(const hkFeatureContactPoint& cp)
{
    for (int i = m_numPoints - 1; i >= 0; --i)
    {
        if (m_contactPoints[i].m_featureIdA == cp.m_featureIdA &&
            m_contactPoints[i].m_featureIdB == cp.m_featureIdB)
            return hkBool(true);
    }
    return hkBool(false);
}

// @ 0x010ec500
hkBoxBoxManifold* hkBoxBoxManifold::init()
{
    hkBoxBoxManifold* const self = this;
    const int zero = 0;
    self->m_contactPoints[0].m_contactPointId = zero;
    self->m_contactPoints[1].m_contactPointId = zero;
    self->m_contactPoints[2].m_contactPointId = zero;
    self->m_contactPoints[3].m_contactPointId = zero;
    self->m_contactPoints[4].m_contactPointId = zero;
    self->m_contactPoints[5].m_contactPointId = zero;
    self->m_contactPoints[6].m_contactPointId = zero;
    self->m_contactPoints[7].m_contactPointId = zero;
    self->m_numPoints = 0;
    self->m_faceVertexFeatureCount = 0;
    self->m_isComplete = false;
    return self;
}

// @ 0x010ec540
int hkBoxBoxManifold::addPoint(const hkCdBody& bodyA, const hkCdBody& bodyB,
                               hkFeatureContactPoint& fcp)
{
    (void)bodyA;
    (void)bodyB;
    hkBoxBoxManifold* const self = this;
    hkFeatureContactPoint* const point = &fcp;
    const hkUchar count = self->m_numPoints;
    if (count > 8)
        return -1;
    if (self->findInManifoldExtern(*point))
        goto fail;
    const int index = count;
    if (index >= 8)
        goto fail;
    self->m_contactPoints[index] = *point;
    ++self->m_numPoints;
    return index;
fail:
    return -1;
}

// @ 0x010ec590
void hkGskfAgent::cleanup()
{
    hkGskManifold_cleanup(&m_manifold, m_contactMgr);
    delete this;
}

// @ 0x010ec5b0
void hkGskfAgent::removePoint(hkUint16 id)
{
    for (int i = 0; i < m_manifold.m_numContactPoints; ++i)
    {
        if (m_manifold.m_contactPoints[i].m_id == id)
        {
            hkGskManifold_removePoint(&m_manifold, i);
            return;
        }
    }
}

// @ 0x010ec5f0
void hkGskfAgent::commitPotential(hkUint16 id)
{
    for (int i = 0; i < m_manifold.m_numContactPoints; ++i)
    {
        if (m_manifold.m_contactPoints[i].m_id == 0xffff)
        {
            m_manifold.m_contactPoints[i].m_id = id;
            return;
        }
    }
}

// @ 0x010ec630
void hkGskfAgent::createZombie(hkUint16 id)
{
    hkGskManifold::ContactPoint* point = m_manifold.m_contactPoints;
    for (int i = 0; i < m_manifold.m_numContactPoints; ++i, ++point)
    {
        if (point->m_id == id)
        {
            point->m_dimA = 0;
            point->m_dimB = 0;
            return;
        }
    }
}

// @ 0x010ec660
hkGskfAgent::hkGskfAgent(const hkCdBody& bodyA, const hkCdBody& bodyB, hkContactMgr* mgr)
    : hkGskfAgentBase(bodyA, bodyB, mgr)
{
    m_manifoldDword = 0;
}

// @ 0x010ec690
hkGskfAgent* hkGskfAgent::createGskfAgent(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                          const hkCollisionInput& input, hkContactMgr* mgr)
{
    (void)input;
    hkMemory* const mem = hkMemory::s_instance;
    if (mgr != 0)
    {
        hkGskfAgent* const agent = (hkGskfAgent*)mem->allocateChunk(0x80, 0x1c);
        agent->m_memSizeAndFlags = 0x80;
        new (agent) hkGskfAgentBase(bodyA, bodyB, mgr);
        ((hkGskfAgentVtblView*)agent)->m_vptr = (void**)0x14a52d8;
        agent->m_manifoldDword = 0;
        return agent;
    }
    hkGskfAgent* const agent = (hkGskfAgent*)mem->allocateChunk(0x30, 0x1c);
    agent->m_memSizeAndFlags = 0x30;
    new (agent) hkGskfAgentBase(bodyA, bodyB, 0);
    return agent;
}
