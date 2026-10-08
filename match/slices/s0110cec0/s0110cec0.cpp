// Slice s0110cec0 (Havok 3.1.0 collide): hkGsk closest point / separating normal of a simplex pair,
// 0x0110d1d0 (1981 bytes, next to hkGsk::reduceDimensionExtended 0x0110cec0).
//
// hkGsk_getClosestPointFromSimplex(verticesA, verticesBinA, dimA, dimB, direction, pointOut, normalOut)
// (declared with this name in s01112950, Claude-coined; Havok's real name is not known).  A cdecl
// helper that, for the simplex pair (dimA vertices of shape A, dimB vertices of B in A space; dim 1 = vertex,
// 2 = edge, 3 = triangle), returns the closest point of the feature pair on A's side (pointOut) and the unit
// separating normal; normalOut.w carries the signed distance.  Only the pairs
//   (1,1) vertex/vertex   (1,2) vertex/edge   (1,3) vertex/triangle
//   (2,1) edge/vertex     (2,2) edge/edge     (3,1) triangle/vertex
// are handled; every other pair leaves the outputs untouched.
// Vertex/edge cases use the previous direction as the normal, the others build it from the feature geometry
// and flip it to face `direction`.
//
// Flags: /vc71 /O2 /MD /Gy /TP  (Havok was built with VC .NET 2003).
#include <math.h>
#pragma intrinsic(sqrt)

typedef float hkReal;

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
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
    static int closestLineSegLineSeg(const hkVector4& A, const hkVector4& dA, const hkVector4& B,
                                     const hkVector4& dB, ClosestLineSegLineSegResult& result);  // 0x01105940
};

static __forceinline void hkCopy4(hkVector4& d, const hkVector4& s) { d.x = s.x; d.y = s.y; d.z = s.z; d.w = s.w; }

// @ 0x0110d1d0
void __cdecl hkGsk_getClosestPointFromSimplex(const hkVector4* verticesA, const hkVector4* verticesBinA,
                                              int dimA, int dimB, const hkVector4& direction,
                                              hkVector4& pointOut, hkVector4& normalOut)
{
    const hkVector4* A = verticesA;
    const hkVector4* B = verticesBinA;
    const hkVector4& dir = direction;
    hkVector4& n = normalOut;

    switch (dimA << 3 | dimB) {
    case 9: {   // vertex / vertex
        n.x = A[0].x - B[0].x;
        n.y = A[0].y - B[0].y;
        n.z = A[0].z - B[0].z;
        n.w = A[0].w - B[0].w;
        const hkReal dx = dir.x * n.x;
        const hkReal lenSq = n.x * n.x + n.y * n.y + n.z * n.z;
        if (lenSq <= (dx + (dir.y * n.y + dir.z * n.z)) * 1000.0f) {
            const hkReal len = (hkReal)sqrt(lenSq);
            const hkReal inv = 1.0f / len;
            n.x *= inv; n.y *= inv; n.z *= inv; n.w *= inv;
            n.w = len;
        } else {
            const hkReal d = dx + (dir.y * n.y + dir.z * n.z);
            hkCopy4(n, dir);
            n.w = d;
        }
        hkCopy4(pointOut, A[0]);
        break;
    }
    case 10: {  // vertex / edge
        const hkReal dx = A[0].x - B[0].x, dy = A[0].y - B[0].y, dz = A[0].z - B[0].z;
        hkCopy4(n, dir);
        n.w = dy * n.y + dz * n.z + dx * n.x;
        hkCopy4(pointOut, A[0]);
        break;
    }
    case 17: {  // edge / vertex
        const hkReal dx = B[0].x - A[0].x, dy = B[0].y - A[0].y, dz = B[0].z - A[0].z;
        hkCopy4(n, dir);
        hkCopy4(pointOut, B[0]);
        const hkReal d = dy * n.y + dz * n.z + dx * n.x;
        pointOut.x = pointOut.x - d * n.x;
        pointOut.y = pointOut.y - d * n.y;
        pointOut.z = pointOut.z - d * n.z;
        pointOut.w = pointOut.w - d * n.w;
        n.w = -d;
        break;
    }
    case 11: {  // vertex / triangle
        n.w = 0.0f;
        const hkReal e1x = B[2].x - B[1].x, e1y = B[2].y - B[1].y, e1z = B[2].z - B[1].z;
        const hkReal e0x = B[0].x - B[2].x, e0y = B[0].y - B[2].y, e0z = B[0].z - B[2].z;
        const hkReal nx = e0z * e1y - e0y * e1z;
        const hkReal ny = e1z * e0x - e0z * e1x;
        const hkReal nz = e0y * e1x - e1y * e0x;
        n.x = nx; n.y = ny; n.z = nz;
        const hkReal lenSq = nz * nz + ny * ny + nx * nx;
        hkReal inv;
        if (lenSq == 0.0f) inv = 0.0f; else inv = 1.0f / (hkReal)sqrt(lenSq);
        if (nz * dir.z + ny * dir.y + nx * dir.x < 0.0f) {
            n.w = 0.0f;
            n.x = -nx; n.y = -ny; n.z = -nz;
        }
        n.x = inv * n.x; n.y = inv * n.y; n.z = inv * n.z;
        n.w = inv * 0.0f;
        hkCopy4(pointOut, A[0]);
        n.w = n.z * (A[0].z - B[0].z) + n.y * (A[0].y - B[0].y) + n.x * (A[0].x - B[0].x);
        break;
    }
    case 25: {  // triangle / vertex
        n.w = 0.0f;
        const hkReal e1x = A[2].x - A[1].x, e1y = A[2].y - A[1].y, e1z = A[2].z - A[1].z;
        const hkReal e0x = A[0].x - A[2].x, e0y = A[0].y - A[2].y, e0z = A[0].z - A[2].z;
        const hkReal nx = e0z * e1y - e0y * e1z;
        const hkReal ny = e1z * e0x - e0z * e1x;
        const hkReal nz = e0y * e1x - e1y * e0x;
        n.x = nx; n.y = ny; n.z = nz;
        const hkReal lenSq = nz * nz + ny * ny + nx * nx;
        hkReal inv;
        if (lenSq == 0.0f) inv = 0.0f; else inv = 1.0f / (hkReal)sqrt(lenSq);
        if (nz * dir.z + ny * dir.y + nx * dir.x < 0.0f) {
            n.w = 0.0f;
            n.x = -nx; n.y = -ny; n.z = -nz;
        }
        const hkReal x2 = inv * n.x, y2 = inv * n.y, z2 = inv * n.z;
        n.x = x2; n.y = y2; n.z = z2;
        n.w = inv * 0.0f;
        hkCopy4(pointOut, B[0]);
        const hkReal d = z2 * (B[0].z - A[0].z) + y2 * (B[0].y - A[0].y) + x2 * (B[0].x - A[0].x);
        pointOut.x = pointOut.x - d * n.x;
        pointOut.y = pointOut.y - d * n.y;
        pointOut.z = pointOut.z - d * n.z;
        pointOut.w = pointOut.w - d * n.w;
        n.w = -d;
        break;
    }
    case 18: {  // edge / edge
        hkVector4 dA, dB;
        dA.x = A[1].x - A[0].x; dA.y = A[1].y - A[0].y; dA.z = A[1].z - A[0].z; dA.w = A[1].w - A[0].w;
        dB.x = B[1].x - B[0].x; dB.y = B[1].y - B[0].y; dB.z = B[1].z - B[0].z; dB.w = B[1].w - B[0].w;
        hkCollideTriangleUtil::ClosestLineSegLineSegResult res;
        hkCollideTriangleUtil::closestLineSegLineSeg(A[0], dA, B[0], dB, res);
        n.w = 0.0f;
        const hkReal nx = dB.z * dA.y - dB.y * dA.z;
        const hkReal ny = dA.z * dB.x - dB.z * dA.x;
        const hkReal nz = dB.y * dA.x - dA.y * dB.x;
        n.x = nx; n.y = ny; n.z = nz;
        const hkReal edgeSq = (dB.z * dB.z + dA.z * dA.z) + (dB.y * dB.y + dA.y * dA.y) + (dB.x * dB.x + dA.x * dA.x);
        if ((nz * nz + ny * ny + nx * nx) * 0.001f <= edgeSq * edgeSq) {
            hkCopy4(n, dir);
        } else {
            if (nz * dir.z + ny * dir.y + nx * dir.x < 0.0f) {
                n.w = 0.0f;
                n.x = -nx; n.y = -ny; n.z = -nz;
            }
            const hkReal lenSq = n.x * n.x + n.y * n.y + n.z * n.z;
            hkReal inv;
            if (lenSq == 0.0f) inv = 0.0f; else inv = 1.0f / (hkReal)sqrt(lenSq);
            n.x = inv * n.x; n.y = inv * n.y; n.z = inv * n.z;
            n.w = inv * 0.0f;
        }
        hkCopy4(pointOut, res.m_closestPointA);
        n.w = (A[0].x - B[0].x) * n.x + (A[0].z - B[0].z) * n.z + (A[0].y - B[0].y) * n.y;
        break;
    }
    default:
        break;
    }
}
