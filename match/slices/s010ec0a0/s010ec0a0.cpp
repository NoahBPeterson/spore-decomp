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

typedef unsigned char  hkUchar;
typedef unsigned short hkUint16;
typedef unsigned int   hkUint32;

class __declspec(align(16)) hkVector4 { public: float x, y, z, w; };
struct hkTransform
{
    hkVector4 m_col0, m_col1, m_col2, m_translation;   // 0x40 bytes
    void setMulInverseMul(const hkTransform& a, const hkTransform& b);   // 0x010810f0: this = inverse(a) * b
};

struct hkConvexShape
{
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void convertVertexIdsToVertices(const hkUint16* ids, int numIds, hkVector4* verticesOut) const;   // slot 10
    hkUint32 m_pad[2];
    float    m_radius;                                  // +0xc
};

struct hkCdBody
{
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

struct hkContactMgr
{
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

struct hkGskfAgent
{
    virtual void dtor();
    virtual void slot1();
    virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                  const hkProcessCollisionInput& input, hkProcessCollisionOutput& result);
    hkUint16        m_memSizeAndFlags;                  // +4
    short           m_referenceCount;                   // +6
    hkContactMgr*   m_contactMgr;                       // +8
    hkGskCache      m_cache;                            // +0xc
    float           m_timeOfSeparatingNormal;           // +0x18
    float           m_allowedPenetration;               // +0x1c
    hkVector4       m_separatingNormal;                 // +0x20 (w = distance)
    hkGskManifold   m_manifold;                         // +0x30

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
    hkVector4* const sepNormal = &m_separatingNormal;

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
