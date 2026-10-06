// Slice s0110e510 (frozen batch op1_big #76).  Havok 3.1.0 collide: hkGsk.
//
// 0x0110e510 is the GSK closest-feature iteration of hkGsk (Havok's Gilbert-Johnson-Keerthi
// variant): it keeps a simplex of m_dimA vertices of shape A and m_dimB vertices of shape B
// (B's vertices are kept both in B space and transformed into A space), reduces the simplex
// to the feature closest to the origin of the Minkowski difference, then asks both shapes for
// new support vertices along the current separating direction until nothing improves.
// Neighbours by name (symbols/havok_names.txt): 0x0110c330 hkGsk::checkTriangleBoundaries,
// 0x0110cde0 hkGsk::convertFeatureToClosestDistance, 0x0110cec0 hkGsk::reduceDimensionExtended,
// 0x0110dd70 hkGsk::handlePenetration; callee 0x01105940 hkCollideTriangleUtil::closestLineSegLineSeg.
//
// Flags: /O2 /MD /Gy /EHsc /TP (x87 floats, 16-byte aligned frame for the hkVector4 locals).
#include <math.h>

typedef float hkReal;

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;

    inline void setSub4(const hkVector4& a, const hkVector4& b) {
        x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w;
    }
    inline void setNeg4(const hkVector4& a) { x = -a.x; y = -a.y; z = -a.z; w = -a.w; }
    inline hkReal dot3(const hkVector4& a) const { return z * a.z + y * a.y + x * a.x; }
    inline hkReal lengthSquared3() const { return x * x + y * y + z * z; }
    inline void mul4(hkReal r) { x *= r; y *= r; z *= r; w *= r; }
};

class hkTransform {
public:
    hkVector4 m_col0, m_col1, m_col2;   // rotation columns
    hkVector4 m_translation;
};

// this = t * v (rotation then translation), w cleared
static __forceinline void setTransformedPos(hkVector4& out, const hkTransform& t, const hkVector4& v) {
    const hkReal vx = v.x, vy = v.y, vz = v.z;
    out.x = t.m_col2.x * vz + t.m_col1.x * vy + t.m_col0.x * vx + t.m_translation.x;
    out.y = t.m_col2.y * vz + t.m_col1.y * vy + t.m_col0.y * vx + t.m_translation.y;
    out.z = t.m_col2.z * vz + t.m_col1.z * vy + t.m_col0.z * vx + t.m_translation.z;
    out.w = 0.0f;
}

// signed square: d * |d|
static inline hkReal signedSquare(hkReal d) { return (hkReal)fabs(d) * d; }

class hkConvexShape {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual void getSupportingVertex(const hkVector4& direction, hkVector4& supportingVertexOut) const;  // 0x24
};

class hkCollideTriangleUtil {
public:
    struct ClosestLineSegLineSegResult {
        hkVector4 m_closestPointA;
        hkVector4 m_closestPointB;
        hkVector4 m_closestAB;
        hkReal m_distanceSquared;
        hkReal m_t;
        hkReal m_u;
        hkReal m_pad;
    };
    // returns a bit mask: 1/2 = A collapses to its end/start point, 4/8 = B likewise; 0 = interior
    static int closestLineSegLineSeg(const hkVector4& A, const hkVector4& dA, const hkVector4& B,
                                     const hkVector4& dB, ClosestLineSegLineSegResult& result);  // 0x01105940
};

// Static helper of this TU (called with a register convention): tests the origin against
// the faces of the tetrahedron (one vertex of `point`, four of `tetra`); returns the index of
// the vertex to drop, or < 0 if the origin is inside.
int hkGsk_checkTetrahedron(const hkVector4* point, const hkVector4* tetra, hkReal sign);  // 0x0110d990

// checkTriangleBoundaries result -> vertex index (>= 0: an edge's opposite vertex region,
// < 0: index - 8 of the vertex to remove, -1 = vertex 1 region)
static const signed char s_triangleFeatureToIndex[16] = {
    -1, -1, 2, -1, 1, -1, -8, -1, 0, -1, -7, -1, -6, -1, -1, -1 };
// next / next-next vertex of a triangle: s_triNext[i], s_triNext[i + 2]
static const signed char s_triNext[5] = { 2, 0, 1, 2, 0 };

class hkGsk {
public:
    enum SupportTypes {
        SUPPORT_A = -8,     // the last reduction came from a triangle of A
        SUPPORT_NONE = 0,
        SUPPORT_B = 8       // the last reduction came from a triangle of B
    };
    enum { TRIANGLE_INSIDE = 14 };

    int getClosestFeature(const hkConvexShape* shapeA, const hkConvexShape* shapeB,
                          const hkTransform& aTb, hkVector4& separatingNormalOut);

protected:
    int checkTriangleBoundaries(const hkVector4& point, hkVector4* triangle, SupportTypes type);  // 0x0110c330
    int checkTriangleEdge(hkVector4* triangleVerts, hkVector4* edgeVerts, int* triangleDim,
                          int* edgeDim, bool wasEdge, int type);                                // 0x0110c720
    void handlePenetration(const hkConvexShape* shapeA, const hkConvexShape* shapeB,
                           const hkTransform& aTb);                                            // 0x0110dd70
    bool addSupportVertexA(const hkConvexShape* shapeA, hkReal threshold);
    bool addSupportVertexB(const hkConvexShape* shapeB, const hkTransform& aTb, hkReal threshold);

public:
    int m_dimA;                                     // +0x000
    int m_dimB;                                     // +0x004
    int m_maxDimA;                                  // +0x008
    int m_maxDimB;                                  // +0x00c
    bool m_doNotHandlePenetration;                  // +0x010
    int m_featureChange;                            // +0x014
    int m_pad18[2];
    hkVector4 m_verticesA[4];                       // +0x020
    hkVector4 m_verticesAinA[4];                    // +0x060
    hkVector4 m_verticesBinA[4];                    // +0x0a0
    hkVector4 m_verticesB[4];                       // +0x0e0
    hkVector4 m_closestPointDir;                    // +0x120 (separating direction, A - B)
    hkCollideTriangleUtil::ClosestLineSegLineSegResult m_lineResult;   // +0x130
    int m_lastSupportType;                          // +0x170
    int m_lastDimB;                                 // +0x174
};

// Ask A for its support vertex along -dir; keep it if it improves on every simplex vertex.
__forceinline bool hkGsk::addSupportVertexA(const hkConvexShape* shapeA, hkReal threshold) {
    if (m_dimA == m_maxDimA || m_lastSupportType == SUPPORT_B) return false;
    hkVector4 dirA;
    dirA.setNeg4(m_closestPointDir);
    shapeA->getSupportingVertex(dirA, m_verticesA[m_dimA]);
    const int n = m_dimA;
    const hkVector4& v = m_verticesA[n];
    hkReal s = (v.x - m_verticesA[0].x) * dirA.x + (v.z - m_verticesA[0].z) * dirA.z +
               (v.y - m_verticesA[0].y) * dirA.y;
    if (signedSquare(s) <= threshold) return false;
    switch (n) {
    case 3:
        s = (v.x - m_verticesA[2].x) * dirA.x + (v.z - m_verticesA[2].z) * dirA.z +
            (v.y - m_verticesA[2].y) * dirA.y;
        if (signedSquare(s) < threshold) return false;
        // fall through
    case 2:
        s = (v.x - m_verticesA[1].x) * dirA.x + (v.z - m_verticesA[1].z) * dirA.z +
            (v.y - m_verticesA[1].y) * dirA.y;
        if (signedSquare(s) < threshold) return false;
        break;
    }
    m_dimA = n + 1;
    m_featureChange = 1;
    return true;
}

// Ask B for its support vertex along dir (rotated into B space); on success also store it
// transformed into A space.
__forceinline bool hkGsk::addSupportVertexB(const hkConvexShape* shapeB, const hkTransform& aTb,
                                            hkReal threshold) {
    if (m_dimB == m_maxDimB || m_lastSupportType == SUPPORT_A) return false;
    hkVector4 dirB;
    const hkReal nx = m_closestPointDir.x, ny = m_closestPointDir.y, nz = m_closestPointDir.z;
    dirB.x = nz * aTb.m_col0.z + ny * aTb.m_col0.y + nx * aTb.m_col0.x;
    dirB.y = nz * aTb.m_col1.z + ny * aTb.m_col1.y + nx * aTb.m_col1.x;
    dirB.z = nx * aTb.m_col2.x + nz * aTb.m_col2.z + ny * aTb.m_col2.y;
    dirB.w = 0.0f;
    shapeB->getSupportingVertex(dirB, m_verticesB[m_dimB]);
    const int n = m_dimB;
    const hkVector4& v = m_verticesB[n];
    hkReal s = (v.x - m_verticesB[0].x) * dirB.x + (v.z - m_verticesB[0].z) * dirB.z +
               (v.y - m_verticesB[0].y) * dirB.y;
    if (signedSquare(s) <= threshold) return false;
    switch (n) {
    case 3:
        s = (v.x - m_verticesB[2].x) * dirB.x + (v.z - m_verticesB[2].z) * dirB.z +
            (v.y - m_verticesB[2].y) * dirB.y;
        if (signedSquare(s) < threshold) return false;
        // fall through
    case 2:
        s = (v.x - m_verticesB[1].x) * dirB.x + (v.z - m_verticesB[1].z) * dirB.z +
            (v.y - m_verticesB[1].y) * dirB.y;
        if (signedSquare(s) < threshold) return false;
        break;
    }
    const hkReal bx = v.x, by = v.y, bz = v.z;
    hkVector4& out = m_verticesBinA[n];
    out.x = by * aTb.m_col1.x + bz * aTb.m_col2.x + bx * aTb.m_col0.x + aTb.m_translation.x;
    out.y = by * aTb.m_col1.y + bz * aTb.m_col2.y + bx * aTb.m_col0.y + aTb.m_translation.y;
    out.z = by * aTb.m_col1.z + bz * aTb.m_col2.z + bx * aTb.m_col0.z + aTb.m_translation.z;
    out.w = 0.0f;
    m_dimB++;
    m_featureChange = 1;
    return true;
}

// @ 0x0110e510
int hkGsk::getClosestFeature(const hkConvexShape* shapeA, const hkConvexShape* shapeB,
                             const hkTransform& aTb, hkVector4& separatingNormalOut) {
    // bring B's simplex vertices into A space
    {
        const hkTransform t = aTb;
        for (int i = 0; i < m_dimB; i++) {
            setTransformedPos(m_verticesBinA[i], t, m_verticesB[i]);
        }
    }

    int iteration = 0;
    hkReal eps = 1e-10f;
    hkVector4* const vA = m_verticesA;
    hkVector4* const vB = m_verticesBinA;
    int oldDimSum;
    bool penetrating;
    hkReal threshold;
    int r, idx, next, next2;
    hkVector4 lenA, lenB;

next_iteration:
    eps += eps;
    iteration++;
    oldDimSum = m_dimA + m_dimB;
    m_lastSupportType = SUPPORT_NONE;

dispatch:
    switch ((m_dimA << 3) | m_dimB) {
    case 0x0c:  // point A - tetrahedron B
        r = hkGsk_checkTetrahedron(vA, vB, 1.0f);
        if (r < 0) goto penetration;
        m_dimB--;
        vB[r] = vB[3];
        m_verticesB[r] = m_verticesB[3];
        // fall through
    case 0x0b:  // point A - triangle B
        r = checkTriangleBoundaries(vA[0], vB, SUPPORT_B);
        if (r == TRIANGLE_INSIDE) goto feature_found;
        idx = s_triangleFeatureToIndex[r];
        if (idx >= 0) {
            next = s_triNext[idx];
            next2 = s_triNext[idx + 2];
            const hkVector4& vI = vB[idx];
            const hkReal dx = vA[0].x - vI.x, dy = vA[0].y - vI.y, dz = vA[0].z - vI.z;
            const hkReal e1x = vB[next].x - vI.x, e1y = vB[next].y - vI.y, e1z = vB[next].z - vI.z;
            const hkReal e2x = vB[next2].x - vI.x, e2y = vB[next2].y - vI.y, e2z = vB[next2].z - vI.z;
            m_dimB = 2;
            if (e1z * dz + e1y * dy + e1x * dx < 0.0f) {
                vB[next] = vB[2];
                m_verticesB[next] = m_verticesB[2];
                if (e2z * dz + e2y * dy + e2x * dx < 0.0f) {
                    if (next2 == m_dimB) next2 = next;
                    m_dimB--;
                    vB[next2] = vB[m_dimB];
                    m_verticesB[next2] = m_verticesB[m_dimB];
                }
            } else {
                vB[next2] = vB[2];
                m_verticesB[next2] = m_verticesB[2];
            }
            goto dispatch;
        }
        idx += 8;
        if (idx > 3) idx = 1;
        m_dimB--;
        vB[idx] = vB[2];
        m_verticesB[idx] = m_verticesB[2];
        // fall through
    case 0x0a: {  // point A - edge B
        const hkReal ex = vB[1].x - vB[0].x, ey = vB[1].y - vB[0].y, ez = vB[1].z - vB[0].z;
        hkVector4 v1, v0;
        v1.x = vB[1].x - vA[0].x; v1.y = vB[1].y - vA[0].y; v1.z = vB[1].z - vA[0].z;
        v0.x = vB[0].x - vA[0].x; v0.y = vB[0].y - vA[0].y; v0.z = vB[0].z - vA[0].z;
        const int side0 = (v0.z * ez + v0.y * ey + v0.x * ex < 0.0f) ? 8 : 0;
        const int side1 = (v1.z * ez + v1.y * ey + v1.x * ex < 0.0f) ? 8 : 0;
        if (side1 != side0) {
            // the origin projects onto the edge interior
            m_closestPointDir.w = 0.0f;
            const hkReal cx = v0.z * v1.y - v0.y * v1.z;
            const hkReal cy = v0.x * v1.z - v1.x * v0.z;
            const hkReal cz = v1.x * v0.y - v0.x * v1.y;
            m_closestPointDir.x = cz * ey - cy * ez;
            m_closestPointDir.y = cx * ez - ex * cz;
            m_closestPointDir.z = ex * cy - cx * ey;
            goto feature_found;
        }
        if (side1) {
            vB[0] = vB[1];
            m_verticesB[0] = m_verticesB[1];
        }
        m_dimB--;
    }
        // fall through
    case 0x09:  // point - point
    point_point:
        m_closestPointDir.setSub4(vA[0], vB[0]);
        goto feature_found;

    case 0x21:  // tetrahedron A - point B
        r = hkGsk_checkTetrahedron(vB, vA, -1.0f);
        if (r < 0) goto penetration;
        m_dimA--;
        vA[r] = vA[3];
        // fall through
    case 0x19:  // triangle A - point B
        r = checkTriangleBoundaries(vB[0], vA, SUPPORT_A);
        if (r == TRIANGLE_INSIDE) goto feature_found;
        idx = s_triangleFeatureToIndex[r];
        if (idx >= 0) {
            next = s_triNext[idx];
            next2 = s_triNext[idx + 2];
            const hkVector4& vI = vA[idx];
            const hkReal dx = vB[0].x - vI.x, dy = vB[0].y - vI.y, dz = vB[0].z - vI.z;
            const hkReal e1x = vA[next].x - vI.x, e1y = vA[next].y - vI.y, e1z = vA[next].z - vI.z;
            const hkReal e2x = vA[next2].x - vI.x, e2y = vA[next2].y - vI.y, e2z = vA[next2].z - vI.z;
            m_dimA = 2;
            if (e1z * dz + e1y * dy + e1x * dx < 0.0f) {
                vA[next] = vA[2];
                if (e2z * dz + e2y * dy + e2x * dx < 0.0f) {
                    if (next2 == m_dimA) next2 = next;
                    m_dimA--;
                    vA[next2] = vA[m_dimA];
                }
            } else {
                vA[next2] = vA[2];
            }
            goto dispatch;
        }
        idx += 8;
        if (idx > 3) idx = 1;
        m_dimA--;
        vA[idx] = vA[2];
        // fall through
    case 0x11: {  // edge A - point B
        const hkReal ex = vA[1].x - vA[0].x, ey = vA[1].y - vA[0].y, ez = vA[1].z - vA[0].z;
        hkVector4 v1, v0;
        v1.x = vA[1].x - vB[0].x; v1.y = vA[1].y - vB[0].y; v1.z = vA[1].z - vB[0].z;
        v0.x = vA[0].x - vB[0].x; v0.y = vA[0].y - vB[0].y; v0.z = vA[0].z - vB[0].z;
        const int side0 = (v0.z * ez + v0.y * ey + v0.x * ex < 0.0f) ? 8 : 0;
        const int side1 = (v1.z * ez + v1.y * ey + v1.x * ex < 0.0f) ? 8 : 0;
        if (side1 != side0) {
            m_closestPointDir.w = 0.0f;
            const hkReal cx = v0.z * v1.y - v0.y * v1.z;
            const hkReal cy = v0.x * v1.z - v1.x * v0.z;
            const hkReal cz = v1.x * v0.y - v0.x * v1.y;
            m_closestPointDir.x = cy * ez - cz * ey;
            m_closestPointDir.y = ex * cz - cx * ez;
            m_closestPointDir.z = cx * ey - ex * cy;
            goto feature_found;
        }
        if (side1) {
            vA[0] = vA[1];
            m_verticesAinA[0] = m_verticesAinA[1];
        }
        m_dimA--;
        goto point_point;
    }

    case 0x12:  // edge A - edge B
    edge_edge: {
        lenA.setSub4(vA[1], vA[0]);
        lenB.setSub4(vB[1], vB[0]);
        const int res = hkCollideTriangleUtil::closestLineSegLineSeg(vA[0], lenA, vB[0], lenB, m_lineResult);
        if (res) {
            if (res & 1) {
                vA[0] = vA[1];
                m_dimA = 1;
            } else if (res & 2) {
                m_dimA = 1;
            }
            if (res & 4) {
                vB[0] = vB[1];
                m_verticesB[0] = m_verticesB[1];
                m_dimB = 1;
            } else if (res & 8) {
                m_dimB = 1;
            }
            goto dispatch;
        }
        m_closestPointDir.w = 0.0f;
        m_closestPointDir.x = lenB.z * lenA.y - lenB.y * lenA.z;
        m_closestPointDir.y = lenB.x * lenA.z - lenA.x * lenB.z;
        m_closestPointDir.z = lenA.x * lenB.y - lenB.x * lenA.y;
        const hkReal dist = (vA[0].z - vB[0].z) * m_closestPointDir.z +
                            (vA[0].y - vB[0].y) * m_closestPointDir.y +
                            (vA[0].x - vB[0].x) * m_closestPointDir.x;
        if (dist < 0.0f) {
            m_closestPointDir.setNeg4(m_closestPointDir);
        }
        goto feature_found;
    }

    case 0x13:  // edge A - triangle B
        r = checkTriangleEdge(vA, vB, &m_dimA, &m_dimB, m_lastDimB == 2, SUPPORT_B);
        goto triangle_edge_result;
    case 0x1a:  // triangle A - edge B
        r = checkTriangleEdge(vB, vA, &m_dimB, &m_dimA, m_lastDimB == 2, SUPPORT_A);
    triangle_edge_result:
        if (r == 1) goto penetration;
        if (r == 2) goto edge_edge;
        goto feature_found;

    default:
        goto penetration;
    }

feature_found:
    m_lastDimB = m_dimB;
    penetrating = false;
    goto check;

penetration:
    penetrating = true;

check: {
    const hkReal len2 = m_closestPointDir.x * m_closestPointDir.x +
                        m_closestPointDir.y * m_closestPointDir.y +
                        m_closestPointDir.z * m_closestPointDir.z;
    m_featureChange |= m_dimA - oldDimSum + m_dimB;
    const hkReal dist = (vA[0].z - vB[0].z) * m_closestPointDir.z +
                        (vA[0].y - vB[0].y) * m_closestPointDir.y +
                        (vA[0].x - vB[0].x) * m_closestPointDir.x;
    if (penetrating || signedSquare(dist) <= len2 * eps || len2 < eps) {
        if (m_doNotHandlePenetration) {
            if (m_dimA + m_dimB > 4) {
                if (m_dimA > m_dimB) {
                    m_dimA = 3;
                    m_dimB = 1;
                    return 4;
                }
                m_dimA = 1;
                m_dimB = 3;
            }
            return 4;
        }
        handlePenetration(shapeA, shapeB, aTb);
        goto finish;
    }
    threshold = len2 * eps;
}
    {
        // odd iterations try A's support first, even ones B's
        const int oddIteration = iteration & 1;
        if (oddIteration && addSupportVertexA(shapeA, threshold)) goto next_iteration;
        if (addSupportVertexB(shapeB, aTb, threshold)) goto next_iteration;
        if (!oddIteration && addSupportVertexA(shapeA, threshold)) goto next_iteration;
    }

finish: {
    const hkReal dx = vA[0].x - vB[0].x;
    const hkReal dy = vA[0].y - vB[0].y;
    const hkReal dz = vA[0].z - vB[0].z;
    const hkReal len2 = m_closestPointDir.lengthSquared3();
    const hkReal inv = (len2 == 0.0f) ? 0.0f : 1.0f / (hkReal)sqrt((double)len2);
    m_closestPointDir.mul4(inv);
    separatingNormalOut = m_closestPointDir;
    const hkReal dist = dz * m_closestPointDir.z + dy * m_closestPointDir.y + dx * m_closestPointDir.x;
    separatingNormalOut.w = dist;
    m_closestPointDir.w = dist;
    return 0;
}
}
