// Slice s0110dd70 (Havok 3.1.0 collide): hkGsk::handlePenetration, 0x0110dd70.
//
// Called by hkGsk::getClosestFeature when the two shapes overlap.  It completes the simplex to
// four vertices on each shape (duplicating existing vertices as needed), forms the Minkowski
// difference vertices A[i] - B[i] and hands them to hkCalculatePenetrationDepth (an EPA-style
// expansion that returns the penetration normal in an hkGskOut).  Afterwards the simplex is
// de-duplicated by vertex id (hkVector4::w of a simplex vertex carries the 24+ bit id of the
// support vertex, mask 0xc0ffffff), B's vertices are re-transformed into A space, the simplex is
// reduced again and, for an edge/edge simplex, the closest points between the two edges are
// computed.  Layout is that of s0110e510 (hkGsk::getClosestFeature).
//
// Flags: /O2 /MD /Gy /EHsc /TP /vc71  (Havok was built with VC .NET 2003).
#include <math.h>

typedef float hkReal;

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
};

static __forceinline void hkCopy(hkVector4& d, const hkVector4& s) { d.x = s.x; d.y = s.y; d.z = s.z; d.w = s.w; }

class hkTransform {
public:
    hkVector4 m_col0, m_col1, m_col2;   // rotation columns
    hkVector4 m_translation;
};

class hkConvexShape;

struct hkGskOut {
    hkVector4 m_normal;   // +0
    hkVector4 m_point;    // +0x10
    hkReal m_dist;        // +0x20
    hkReal m_half;        // +0x24
};

enum hkGskStatus { HK_GSK_OK = 0 };

hkGskStatus hkCalculatePenetrationDepth(const hkConvexShape* shapeA, const hkConvexShape* shapeB,
                                        const hkTransform& aTb, hkReal tolerance,
                                        hkVector4* simplexA, hkVector4* simplexB,
                                        hkVector4* diffs, int* dim, hkGskOut& out);   // 0x01121e10

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
    static int closestLineSegLineSeg(const hkVector4& A, const hkVector4& dA, const hkVector4& B,
                                     const hkVector4& dB, ClosestLineSegLineSegResult& result);  // 0x01105940
};

// id of a simplex vertex (stored in w)
static inline unsigned int hkVertexId(const hkVector4& v) { return *(const unsigned int*)&v.w & 0xc0ffffffu; }

// this = t * v (rotation then translation), w cleared
static __forceinline void setTransformedPos(hkVector4& out, const hkTransform& t, const hkVector4& v) {
    const hkReal vx = v.x, vy = v.y, vz = v.z;
    hkReal rx = t.m_col0.x * vx; rx += t.m_col1.x * vy; rx += t.m_col2.x * vz; rx += t.m_translation.x;
    hkReal ry = t.m_col0.y * vx; ry += t.m_col1.y * vy; ry += t.m_col2.y * vz; ry += t.m_translation.y;
    hkReal rz = t.m_col0.z * vx; rz += t.m_col1.z * vy; rz += t.m_col2.z * vz; rz += t.m_translation.z;
    out.x = rx; out.y = ry; out.z = rz;
    out.w = 0.0f;
}

class hkGsk {
public:
    void handlePenetration(const hkConvexShape* shapeA, const hkConvexShape* shapeB,
                           const hkTransform& aTb);                                            // 0x0110dd70
protected:
    void reduceDimensionExtended();                                                            // 0x0110cec0

public:
    int m_dimA;                                     // +0x000
    int m_dimB;                                     // +0x004
    int m_maxDimA;                                  // +0x008
    int m_maxDimB;                                  // +0x00c
    bool m_doNotHandlePenetration;                  // +0x010
    int m_featureChange;                            // +0x014
    int m_pad18[2];
    hkVector4 m_verticesA[4];                       // +0x020
    hkVector4 m_verticesAinA[4];                    // +0x060 (unused here)
    hkVector4 m_verticesBinA[4];                    // +0x0a0
    hkVector4 m_verticesB[4];                       // +0x0e0
    hkVector4 m_closestPointDir;                    // +0x120
    hkCollideTriangleUtil::ClosestLineSegLineSegResult m_lineResult;   // +0x130
};

// @ 0x0110dd70
void hkGsk::handlePenetration(const hkConvexShape* shapeA, const hkConvexShape* shapeB,
                              const hkTransform& aTb) {
    int n = 4;
    if (m_dimB >= 3) {
        if (m_dimB > 3) {
            hkCopy(m_verticesA[3], m_verticesA[0]);
        } else if (m_dimA > 1) {
            hkCopy(m_verticesA[3], m_verticesA[1]);
            hkCopy(m_verticesB[3], m_verticesB[0]);
            hkCopy(m_verticesBinA[3], m_verticesBinA[0]);
        } else {
            n = 3;
        }
        hkCopy(m_verticesA[1], m_verticesA[0]);
        hkCopy(m_verticesA[2], m_verticesA[0]);
    } else {
        if (m_dimA >= 3) {
            if (m_dimA > 3) {
                hkCopy(m_verticesB[3], m_verticesB[0]);
                hkCopy(m_verticesBinA[3], m_verticesBinA[0]);
            } else if (m_dimB > 1) {
                hkCopy(m_verticesA[3], m_verticesA[0]);
                hkCopy(m_verticesB[3], m_verticesB[1]);
                hkCopy(m_verticesBinA[3], m_verticesBinA[1]);
            } else {
                n = 3;
            }
            hkCopy(m_verticesB[1], m_verticesB[0]);
            hkCopy(m_verticesBinA[1], m_verticesBinA[0]);
            hkCopy(m_verticesB[2], m_verticesB[0]);
            hkCopy(m_verticesBinA[2], m_verticesBinA[0]);
        } else {
            n = 1;
        }
    }

    hkVector4 diffs[4];
    for (int i = 0; i < n; i++) {
        const hkVector4& a = m_verticesA[i];
        const hkVector4& b = m_verticesBinA[i];
        diffs[i].x = a.x - b.x; diffs[i].y = a.y - b.y; diffs[i].z = a.z - b.z; diffs[i].w = a.w - b.w;
    }

    hkGskOut out;
    hkCalculatePenetrationDepth(shapeA, shapeB, aTb, 1e-4f, m_verticesA, m_verticesB, diffs, &n, out);

    if (n == 1) {
        m_dimB = 1;
        m_dimA = 1;
    } else {
        m_dimB = 3;
        m_dimA = 3;
        if (hkVertexId(m_verticesA[1]) == hkVertexId(m_verticesA[2]) ||
            hkVertexId(m_verticesA[0]) == hkVertexId(m_verticesA[2])) {
            m_dimA = 2;
        }
        if (hkVertexId(m_verticesA[0]) == hkVertexId(m_verticesA[1])) {
            m_dimA--;
            hkCopy(m_verticesA[0], m_verticesA[m_dimA]);
        }
        if (hkVertexId(m_verticesB[1]) == hkVertexId(m_verticesB[2]) ||
            hkVertexId(m_verticesB[0]) == hkVertexId(m_verticesB[2])) {
            m_dimB--;
        }
        if (m_dimB >= 2 && hkVertexId(m_verticesB[0]) == hkVertexId(m_verticesB[1])) {
            m_dimB--;
            hkCopy(m_verticesB[0], m_verticesB[m_dimB]);
        }

        hkTransform t;
        t.m_col0.x = aTb.m_col0.x; t.m_col0.y = aTb.m_col0.y; t.m_col0.z = aTb.m_col0.z;
        t.m_col1.x = aTb.m_col1.x; t.m_col1.y = aTb.m_col1.y; t.m_col1.z = aTb.m_col1.z;
        t.m_col2.x = aTb.m_col2.x; t.m_col2.y = aTb.m_col2.y; t.m_col2.z = aTb.m_col2.z;
        t.m_translation.x = aTb.m_translation.x; t.m_translation.y = aTb.m_translation.y; t.m_translation.z = aTb.m_translation.z;
        const int nB = m_dimB;
        for (int i = 0; i < nB; i++) {
            setTransformedPos(m_verticesBinA[i], t, m_verticesB[i]);
        }

        if (m_dimA + m_dimB > 4) {
            reduceDimensionExtended();
        }
        if (m_dimA == 2 && m_dimB == 2) {
            hkVector4 dA, dB;
            dA.x = m_verticesA[1].x - m_verticesA[0].x;
            dA.y = m_verticesA[1].y - m_verticesA[0].y;
            dA.z = m_verticesA[1].z - m_verticesA[0].z;
            dA.w = m_verticesA[1].w - m_verticesA[0].w;
            dB.x = m_verticesBinA[1].x - m_verticesBinA[0].x;
            dB.y = m_verticesBinA[1].y - m_verticesBinA[0].y;
            dB.z = m_verticesBinA[1].z - m_verticesBinA[0].z;
            dB.w = m_verticesBinA[1].w - m_verticesBinA[0].w;
            hkCollideTriangleUtil::closestLineSegLineSeg(m_verticesA[0], dA, m_verticesBinA[0], dB, m_lineResult);
        }
    }
    hkCopy(m_closestPointDir, out.m_normal);
    m_featureChange = 1;
}
