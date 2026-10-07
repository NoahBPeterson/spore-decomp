// Slice s0110b3a0 -- Havok 3.1.0 hkBoxBoxCollisionDetection::calcManifold (0x0110b3a0, 3519 bytes).
// Flags: /O2 /MD /Gy /TP /fp:fast (x87 hkVector4 code, 16-byte aligned frame).
//
// Box-box contact manifold update:
//  1. re-validate every cached manifold point (face A / vertex B, face B / vertex A, edge-edge)
//     and re-emit it into the process output, dropping the ones whose feature is no longer
//     valid;
//  2. check whether the manifold normal still matches (dot >= 0.95) and stop early when the
//     manifold is complete and unchanged;
//  3. run the separating-axis test with a tolerance below the closest current point;
//  4. find the closest feature pair, refresh the manifold normal and drop points whose normal
//     disagrees with it, then add the new point (unless it duplicates a vertex point or its
//     normal opposes the previous one);
//  5. when both boxes have a face nearly aligned with the normal (>= 0.98), try to add the
//     face-A / face-B vertex points and (optionally) the additional edge points.
#include "types.h"

#include <math.h>

typedef float hkReal;
typedef uint16_t hkContactPointId;

class hkBool {
public:
    char m_bool;
    hkBool() {}
    operator bool() const { return m_bool != 0; }
};

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;

    hkReal& operator()(int i) { return (&x)[i]; }
    const hkReal& operator()(int i) const { return (&x)[i]; }
    void setRotatedDir(const class hkRotation& r, const hkVector4& v);   // 0x010814a0
};

class hkRotation {
public:
    hkVector4 c0, c1, c2;   // columns
    const hkVector4& getColumn(int i) const { return (&c0)[i]; }
};

class hkTransform {
public:
    hkRotation m_rotation;
    hkVector4  m_translation;
};

class hkCdBody;
struct hkCollisionInput;

class hkContactPoint {
public:
    hkVector4 m_position;
    hkVector4 m_separatingNormal;   // w = distance
};

struct hkProcessCdPoint {
    hkContactPoint   m_contact;
    hkContactPointId m_contactPointId;   // +0x20
    uint16_t         m_pad22;
    uint32_t         m_pad24[3];

    hkProcessCdPoint& operator=(const hkProcessCdPoint& o);   // 0x01103af0
};

struct hkProcessCollisionOutput {
    hkProcessCdPoint* m_firstFreeContactPoint;   // +0x00
    uint32_t          m_pad04[(0x30 - 0x04) / 4];
    hkProcessCdPoint  m_contactPoints[8];        // +0x30

    int getNumContactPoints() const { return (int)(m_firstFreeContactPoint - &m_contactPoints[0]); }
};

class hkContactMgr {
public:
    virtual void v00();
    virtual void v04();
    virtual hkContactPointId addContactPoint(const hkCdBody& a, const hkCdBody& b,
                                             const hkCollisionInput& input, hkProcessCdPoint& cp);   // +0x08
    virtual void v0c();
    virtual void removeContactPoint(hkContactPointId id);   // +0x10
};

class hkFeatureContactPoint {
public:
    hkFeatureContactPoint() { m_contactPointId = 0; }

    uint8_t          m_featureIdA;
    uint8_t          m_featureIdB;
    hkContactPointId m_contactPointId;
};

class hkBoxBoxManifold {
public:
    int  addPoint(const hkCdBody& bodyA, const hkCdBody& bodyB, hkFeatureContactPoint& fcp);   // 0x010ec540
    void removePoint(int index);                                                                // 0x010ec4a0

    hkFeatureContactPoint m_contactPoints[8];
    uint8_t   m_faceVertexFeatureCount;      // +0x20
    uint8_t   m_numPoints;                   // +0x21
    hkBool    m_isComplete;                  // +0x22
    hkBool    m_manifoldNormalInitialized;   // +0x23
    uint32_t  m_pad24[3];
    hkVector4 m_manifoldNormalA;             // +0x30
    hkVector4 m_manifoldNormalB;             // +0x40
};

extern bool g_hkBoxBoxAddAdditionalEdges;   // 0x016e58f8
extern const int g_hkBoxBoxNextAxis[4];     // 0x014a5ec4 {1, 2, 0, 1}

inline hkReal hkFabs(hkReal r) { return (hkReal)fabs(r); }

inline hkReal hkMin2(hkReal a, hkReal b) { return (a < b) ? a : b; }

// x=8, y=4, z=2, w=1
__forceinline int compareLessThan4(const hkVector4& v, const hkVector4& a)
{
    return ((v.x < a.x) ? 8 : 0) | ((v.y < a.y) ? 4 : 0) | ((v.z < a.z) ? 2 : 0) | ((v.w < a.w) ? 1 : 0);
}

__forceinline int compareLessThanZero4(const hkVector4& v)
{
    return ((v.x < 0.0f) ? 8 : 0) | ((v.y < 0.0f) ? 4 : 0) | ((v.z < 0.0f) ? 2 : 0) | ((v.w < 0.0f) ? 1 : 0);
}

__forceinline void setAbs4(hkVector4& r, const hkVector4& v)
{
    r.x = hkFabs(v.x);
    r.y = hkFabs(v.y);
    r.z = hkFabs(v.z);
    r.w = hkFabs(v.w);
}

// r = m * v
__forceinline void setRotatedDirInl(hkVector4& r, const hkRotation& m, const hkVector4& v)
{
    const hkReal v0 = v.x;
    const hkReal v1 = v.y;
    const hkReal v2 = v.z;
    r.x = m.c0.x * v0 + m.c1.x * v1 + m.c2.x * v2;
    r.y = m.c0.y * v0 + m.c1.y * v1 + m.c2.y * v2;
    r.z = m.c0.z * v0 + m.c1.z * v1 + m.c2.z * v2;
}

// r = m^T * v
__forceinline void setRotatedInverseDir(hkVector4& r, const hkRotation& m, const hkVector4& v)
{
    const hkReal v0 = v.x;
    const hkReal v1 = v.y;
    const hkReal v2 = v.z;
    r.x = m.c0.x * v0 + m.c0.y * v1 + m.c0.z * v2;
    r.y = m.c1.x * v0 + m.c1.y * v1 + m.c1.z * v2;
    r.z = m.c2.x * v0 + m.c2.y * v1 + m.c2.z * v2;
}

__forceinline void setTransformedPos(hkVector4& r, const hkTransform& t, const hkVector4& v)
{
    const hkReal v0 = v.x;
    const hkReal v1 = v.y;
    const hkReal v2 = v.z;
    r.x = t.m_rotation.c0.x * v0 + t.m_rotation.c1.x * v1 + t.m_rotation.c2.x * v2 + t.m_translation.x;
    r.y = t.m_rotation.c0.y * v0 + t.m_rotation.c1.y * v1 + t.m_rotation.c2.y * v2 + t.m_translation.y;
    r.z = t.m_rotation.c0.z * v0 + t.m_rotation.c1.z * v1 + t.m_rotation.c2.z * v2 + t.m_translation.z;
}

__forceinline hkReal dot3(const hkVector4& a, const hkVector4& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Vertex feature id of a box from the signs of a normal (bits 7..5) and of the centre
// offset along the face axis (bit 3). Same-TU static helper (register argument), loaded from this object.
static uint8_t vertexIdFromNormal(const hkVector4& n, hkReal din)
{
    int mask = compareLessThanZero4(n);
    uint32_t bits = *reinterpret_cast<const uint32_t*>(&din);
    return (uint8_t)(((mask << 4) & 0xe0) | ((bits >> 28) & 8));
}

class hkBoxBoxCollisionDetection {
public:
    class hkFeaturePointCache {
    public:
        hkVector4 m_vA;           // +0x00
        hkVector4 m_vB;           // +0x10
        hkVector4 m_normal;       // +0x20
        hkReal    m_nscale;       // +0x30
        hkReal    m_distance;     // +0x34
        int       m_featureIndexA;  // +0x38
        int       m_featureIndexB;  // +0x3c
    };

    void calcManifold(hkBoxBoxManifold& manifold) const;

    void initVars() const;   // 0x010d93e0
    void faceAVertexBValidationDataFromFeatureId(hkFeaturePointCache& fpp, const hkFeatureContactPoint& fcp) const;   // 0x01108940
    void faceBVertexAValidationDataFromFeatureId(hkFeaturePointCache& fpp, const hkFeatureContactPoint& fcp) const;   // 0x01108ac0
    hkBool edgeEdgeValidationDataFromFeatureId(hkFeaturePointCache& fpp) const;                                     // 0x0110a600
    void faceAVertexBContactPointFromFeaturePointCache(hkProcessCdPoint& cp, const hkFeatureContactPoint& fcp, const hkFeaturePointCache& fpp) const;   // 0x01108a10
    void faceBVertexAContactPointFromFeaturePointCache(hkProcessCdPoint& cp, const hkFeatureContactPoint& fcp, const hkFeaturePointCache& fpp) const;   // 0x01108b80
    void edgeEdgeContactPointFromFeaturePointCache(hkProcessCdPoint& cp, const hkFeatureContactPoint& fcp, const hkFeaturePointCache& fpp) const;      // 0x01108c30
    int  checkIntersection(const hkVector4& tolerance4) const;                                                     // 0x01109460
    int  findClosestPoint(hkBoxBoxManifold& manifold, hkFeatureContactPoint& fcp, hkFeaturePointCache& fpp) const;   // 0x0110ad70
    void tryToAddPointFaceA(hkBoxBoxManifold& manifold, hkFeatureContactPoint fcp, uint16_t edgeMask, hkReal minDist) const;   // 0x01108d00
    void tryToAddPointFaceB(hkBoxBoxManifold& manifold, hkFeatureContactPoint fcp, uint16_t edgeMask, hkReal minDist) const;   // 0x011090b0
    void addAdditionalEdges(hkBoxBoxManifold& manifold, int edgeA, int edgeB, int otherA, int otherB,
                            const hkVector4& normalInA, const hkVector4& normalInB, hkReal minDist) const;      // 0x0110ac90
    void checkCompleteness(hkBoxBoxManifold& manifold, int maskA, int maskB) const;                              // 0x01108550

    const hkCdBody*           m_bodyA;        // +0x00
    const hkCdBody*           m_bodyB;        // +0x04
    const hkCollisionInput*   m_env;          // +0x08
    hkContactMgr*             m_contactMgr;   // +0x0c
    hkProcessCollisionOutput* m_result;       // +0x10
    const hkTransform*        m_wTa;          // +0x14
    const hkTransform*        m_wTb;          // +0x18
    uint32_t                  m_pad1c;
    hkRotation                m_aRb;          // +0x20
    hkVector4                 m_aTb;          // +0x50
    hkVector4                 m_radiusA;      // +0x60
    hkVector4                 m_radiusB;      // +0x70
    hkVector4                 m_tolerance4;   // +0x80
    hkVector4                 m_boundaryToleranceA;   // +0x90
    hkVector4                 m_boundaryToleranceB;   // +0xa0
    hkReal                    m_tolerance;    // +0xb0
    uint32_t                  m_padb4[3];
    hkVector4                 m_dinA;         // +0xc0
    hkVector4                 m_dinB;         // +0xd0
};

static __forceinline void calcManifoldNormalB(hkBoxBoxManifold& manifold, const hkRotation& aRb)
{
    setRotatedInverseDir(manifold.m_manifoldNormalB, aRb, manifold.m_manifoldNormalA);
    *reinterpret_cast<uint32_t*>(&manifold.m_manifoldNormalB.w) = 0;
    manifold.m_manifoldNormalInitialized.m_bool = true;
}

// @ 0x0110b3a0
void hkBoxBoxCollisionDetection::calcManifold(hkBoxBoxManifold& manifold) const
{
    initVars();

    hkProcessCdPoint* firstPoint = m_result->m_firstFreeContactPoint;

    // 1. Revalidate the existing points.
    {
        int i = 0;
        if (manifold.m_numPoints > 0) {
            hkFeatureContactPoint* fcp = &manifold.m_contactPoints[0];
            do {
                int featureA = fcp->m_featureIdA;
                if (featureA <= 2) {
                    hkFeaturePointCache fpp;
                    faceAVertexBValidationDataFromFeatureId(fpp, *fcp);
                    hkVector4 absV;
                    setAbs4(absV, fpp.m_vA);
                    if ((compareLessThan4(absV, m_boundaryToleranceA) & 0xe) != 0xe)
                        goto removePoint;
                    fpp.m_distance = fpp.m_nscale * fpp.m_vA(fpp.m_featureIndexA) - m_radiusA(fpp.m_featureIndexA);
                    hkProcessCdPoint* cp = m_result->m_firstFreeContactPoint;
                    m_result->m_firstFreeContactPoint = cp + 1;
                    faceAVertexBContactPointFromFeaturePointCache(*cp, *fcp, fpp);
                    i++;
                    fcp++;
                } else if (featureA <= 6) {
                    hkFeaturePointCache fpp;
                    faceBVertexAValidationDataFromFeatureId(fpp, *fcp);
                    hkVector4 absV;
                    setAbs4(absV, fpp.m_vB);
                    if ((compareLessThan4(absV, m_boundaryToleranceB) & 0xe) != 0xe)
                        goto removePoint;
                    fpp.m_distance = -(fpp.m_nscale * fpp.m_vB(fpp.m_featureIndexA - 4)) - m_radiusB(fpp.m_featureIndexA - 4);
                    hkProcessCdPoint* cp = m_result->m_firstFreeContactPoint;
                    m_result->m_firstFreeContactPoint = cp + 1;
                    faceBVertexAContactPointFromFeaturePointCache(*cp, *fcp, fpp);
                    i++;
                    fcp++;
                } else {
                    hkFeaturePointCache fpp;
                    fpp.m_featureIndexA = featureA;
                    fpp.m_featureIndexB = fcp->m_featureIdB;
                    if (!edgeEdgeValidationDataFromFeatureId(fpp))
                        goto removePoint;
                    hkProcessCdPoint* cp = m_result->m_firstFreeContactPoint;
                    m_result->m_firstFreeContactPoint = cp + 1;
                    edgeEdgeContactPointFromFeaturePointCache(*cp, *fcp, fpp);
                    i++;
                    fcp++;
                }
                continue;
            removePoint:
                if (fcp->m_featureIdA <= 6)
                    manifold.m_faceVertexFeatureCount--;
                m_contactMgr->removeContactPoint(fcp->m_contactPointId);
                manifold.removePoint(i);
            } while (i < manifold.m_numPoints);
        }
    }

    // 2. Does the manifold normal still match?
    hkBool normalChanged;
    if (manifold.m_numPoints < 2) {
        manifold.m_manifoldNormalInitialized.m_bool = false;
        normalChanged.m_bool = true;
    } else {
        if (!manifold.m_manifoldNormalInitialized)
            calcManifoldNormalB(manifold, m_aRb);
        hkVector4 nA;
        setRotatedDirInl(nA, m_aRb, manifold.m_manifoldNormalB);
        normalChanged.m_bool = dot3(nA, manifold.m_manifoldNormalA) < 0.95f;
        if (!normalChanged && manifold.m_isComplete)
            return;
    }

    // 3. Separating-axis test, with a tolerance just below the closest current point.
    int separated;
    if (manifold.m_numPoints == 0) {
        separated = checkIntersection(m_tolerance4);
    } else {
        hkReal minDist = firstPoint[0].m_contact.m_separatingNormal.w;
        for (int k = manifold.m_numPoints - 1; k > 0; k--)
            minDist = hkMin2(minDist, firstPoint[k].m_contact.m_separatingNormal.w);
        hkVector4 tol4;
        minDist = minDist - m_tolerance4.x * 0.05f;
        tol4.x = minDist;
        tol4.y = minDist;
        tol4.z = minDist;
        tol4.w = minDist;
        separated = checkIntersection(tol4);
    }
    if (separated)
        return;

    // 4. Closest feature pair.
    hkFeatureContactPoint fcp;
    hkFeaturePointCache fpp;
    int closest = findClosestPoint(manifold, fcp, fpp);

    if (normalChanged && closest) {
        hkVector4& normal = manifold.m_manifoldNormalA;
        if (fpp.m_featureIndexA <= 2) {
            hkReal s = -fpp.m_nscale;
            normal.x = 0.0f;
            normal.y = 0.0f;
            normal.z = 0.0f;
            normal.w = 0.0f;
            normal(fcp.m_featureIdA) = s;
        } else if (fpp.m_featureIndexA <= 6) {
            hkReal s = -fpp.m_nscale;
            const hkVector4& col = m_aRb.getColumn(fcp.m_featureIdA - 4);
            normal.x = s * col.x;
            normal.y = s * col.y;
            normal.z = s * col.z;
            normal.w = s * col.w;
        } else {
            normal = fpp.m_normal;
        }

        if (manifold.m_manifoldNormalInitialized) {
            hkVector4 worldNormal;
            worldNormal.setRotatedDir(m_wTa->m_rotation, manifold.m_manifoldNormalA);

            int base = m_result->getNumContactPoints() - manifold.m_numPoints;
            int k = 0;
            if (manifold.m_numPoints > 0) {
                do {
                    hkProcessCdPoint& cp = m_result->m_contactPoints[base + k];
                    if (dot3(worldNormal, cp.m_contact.m_separatingNormal) < 0.95f) {
                        cp = *(m_result->m_firstFreeContactPoint - 1);
                        if (manifold.m_contactPoints[k].m_featureIdA <= 6)
                            manifold.m_faceVertexFeatureCount--;
                        m_contactMgr->removeContactPoint(manifold.m_contactPoints[k].m_contactPointId);
                        manifold.removePoint(k);
                        m_result->m_firstFreeContactPoint--;
                    } else {
                        k++;
                    }
                } while (k < manifold.m_numPoints);
            }

            if (manifold.m_numPoints < 2)
                manifold.m_manifoldNormalInitialized.m_bool = false;
            else
                calcManifoldNormalB(manifold, m_aRb);
        }
    }

    if (closest != 2)
        return;

    // 4b. A new vertex point must not duplicate an existing vertex point.
    if (fcp.m_featureIdA <= 6) {
        hkVector4 pos;
        if (fcp.m_featureIdA <= 2)
            setTransformedPos(pos, *m_wTb, fpp.m_vB);
        else
            setTransformedPos(pos, *m_wTa, fpp.m_vA);
        for (int k = 0; k < manifold.m_numPoints; k++) {
            if (manifold.m_contactPoints[k].m_featureIdA <= 6) {
                const hkVector4& p = m_result->m_contactPoints[k].m_contact.m_position;
                hkReal dx = pos.x - p.x;
                hkReal dy = pos.y - p.y;
                hkReal dz = pos.z - p.z;
                hkReal t = m_tolerance;
                if (dx * dx + dz * dz + dy * dy <= t * t + 1.1920929e-07f)
                    return;
            }
        }
    }

    if (manifold.m_numPoints >= 8)
        return;

    int index = manifold.addPoint(*m_bodyA, *m_bodyB, fcp);
    if (index >= 0) {
        hkProcessCdPoint* cp = m_result->m_firstFreeContactPoint;
        if (fpp.m_featureIndexA <= 2)
            faceAVertexBContactPointFromFeaturePointCache(*cp, fcp, fpp);
        else if (fpp.m_featureIndexA <= 6)
            faceBVertexAContactPointFromFeaturePointCache(*cp, fcp, fpp);
        else
            edgeEdgeContactPointFromFeaturePointCache(*cp, fcp, fpp);

        if (manifold.m_numPoints > 1) {
            const hkVector4& prev = (m_result->m_firstFreeContactPoint - 1)->m_contact.m_separatingNormal;
            if (dot3(prev, cp->m_contact.m_separatingNormal) <= 0.0f) {
                manifold.removePoint(index);
                return;
            }
        }

        hkContactPointId id = m_contactMgr->addContactPoint(*m_bodyA, *m_bodyB, *m_env, *cp);
        manifold.m_contactPoints[index].m_contactPointId = id;
        if (id == 0xffff) {
            manifold.removePoint(index);
        } else {
            m_result->m_firstFreeContactPoint++;
            fcp.m_contactPointId = manifold.m_contactPoints[index].m_contactPointId;
            cp->m_contactPointId = manifold.m_contactPoints[index].m_contactPointId;
            if (fcp.m_featureIdA <= 6)
                manifold.m_faceVertexFeatureCount++;
        }
    }

    // 5. Faces nearly aligned with the normal: add the face points.
    hkFeatureContactPoint fcpA = fcp;
    if (manifold.m_numPoints < 1)
        return;

    int numPoints = manifold.m_numPoints;
    int base = m_result->getNumContactPoints() - numPoints;
    const hkVector4& normal = m_result->m_contactPoints[base].m_contact.m_separatingNormal;

    hkVector4 normalInA;
    setRotatedInverseDir(normalInA, m_wTa->m_rotation, normal);
    hkVector4 normalInB;
    setRotatedInverseDir(normalInB, m_wTb->m_rotation, normal);
    normalInB.w = 0.0f;
    normalInA.x = -normalInA.x;
    normalInA.y = -normalInA.y;
    normalInA.z = -normalInA.z;
    normalInA.w = 0.0f;

    hkVector4 absA;
    setAbs4(absA, normalInA);
    hkVector4 absB;
    setAbs4(absB, normalInB);

    int axisA;
    int maskA;
    if (absA.x > absA.y) {
        axisA = 0;
        maskA = 0x80;
    } else {
        axisA = 1;
        maskA = 0x40;
    }
    if (absA.z > absA(axisA)) {
        axisA = 2;
        maskA = 0x20;
    }
    int axisB;
    int maskB;
    if (absB.x > absB.y) {
        axisB = 0;
        maskB = 0x80;
    } else {
        axisB = 1;
        maskB = 0x40;
    }
    if (absB.z > absB(axisB)) {
        axisB = 2;
        maskB = 0x20;
    }

    if (absA(axisA) < 0.98f)
        return;
    if (absB(axisB) < 0.98f)
        return;

    hkFeatureContactPoint fcpB;
    fcpA.m_featureIdB = vertexIdFromNormal(normalInB, m_dinA(axisA));
    fcpB.m_featureIdB = vertexIdFromNormal(normalInA, m_dinB(axisB));
    fcpA.m_featureIdA = (uint8_t)axisA;
    fcpB.m_featureIdA = (uint8_t)(axisB + 4);

    hkReal minDist = 1.0f;
    if (numPoints > 0) {
        const hkProcessCdPoint* p = &m_result->m_contactPoints[base];
        for (int k = manifold.m_numPoints; k != 0; k--, p++) {
            if (p->m_contact.m_separatingNormal.w < minDist)
                minDist = p->m_contact.m_separatingNormal.w;
        }
    }

    tryToAddPointFaceA(manifold, fcpA, (uint16_t)maskB, minDist);
    tryToAddPointFaceB(manifold, fcpB, (uint16_t)maskA, minDist);

    if (manifold.m_faceVertexFeatureCount >= 4) {
        manifold.m_isComplete.m_bool = true;
        return;
    }

    if (g_hkBoxBoxAddAdditionalEdges) {
        int b0 = g_hkBoxBoxNextAxis[axisB];
        int a0 = g_hkBoxBoxNextAxis[axisA];
        int a1 = g_hkBoxBoxNextAxis[axisA + 1];
        normalInB.x = -normalInB.x;
        normalInB.y = -normalInB.y;
        normalInB.z = -normalInB.z;
        int b1 = g_hkBoxBoxNextAxis[axisB + 1];
        normalInB.w = 0.0f;
        addAdditionalEdges(manifold, a0, b0, a1, b1, normalInA, normalInB, minDist);
        addAdditionalEdges(manifold, a0, b1, a1, b0, normalInA, normalInB, minDist);
        addAdditionalEdges(manifold, a1, b0, a0, b1, normalInA, normalInB, minDist);
        addAdditionalEdges(manifold, a1, b1, a0, b0, normalInA, normalInB, minDist);
    }

    checkCompleteness(manifold, maskA, maskB);
}
