// hkCollideCapsuleUtilManifoldCapsVsCaps, 0x01106490   (Havok 3.1.0, x87, /O2 /fp:fast)
//
//   extern "C" void hkCollideCapsuleUtilManifoldCapsVsCaps(const hkVector4* capsA, hkReal capsARadius,
//                                                          const hkVector4* capsB, hkReal capsBRadius,
//                                                          hkContactPoint* pointsOut);
//
// Contact manifold between two capsules (segments capsA[0..1] / capsB[0..1]). It runs an inlined
// closest-point-between-segments (hkLineSegmentUtil::closestLineSegLineSeg shape, returning the
// "endpoint was clamped" bits 1/2/4/8), writes pointsOut[0] (always its separating normal and distance;
// the position only when the capsules are within tolerance) and, unless the segments are close to
// parallel, tries the two end-point pairs as extra contacts pointsOut[1] / pointsOut[2].
// Each pointsOut[i].m_separatingNormal.w is read as that point's collision tolerance on entry.
//
// Float semantics: the original is x87 code from an older cl that keeps intermediates at 80 bits
// on the FPU stack and rounds a value to 32 bits only where it spills it to memory. /fp:fast gives
// the inline fsqrt (no __CIsqrt) and the 80-bit intermediates; `Rounded()` marks every place where
// the original stores a value as a float and reloads it (a hkVector4 member, a spilled local), so
// the results stay bit-identical. Values not wrapped in Rounded() are used unrounded there too.
// The sums are written in the original's association (dot3 (x*x' + z*z') + y*y', normalize3
// length (x*x + y*y) + z*z, manifold-point distance (z*z + y*y) + x*x); /fp:fast may regroup
// them, which only moves 64-bit rounding. tools/difftest/equiv.py: PASS, bit-identical on
// 3 x 400 random inputs plus 400 with NaN/Inf, 99.9% coverage (tested through a C++-linkage copy
// so the harness knows the return type is void).

#include <math.h>

struct __declspec(align(16)) hkVector4 {
    float x, y, z, w;
};

struct hkContactPoint {
    hkVector4 m_position;
    hkVector4 m_separatingNormal;   // w = distance
};

static const float HK_REAL_EPSILON = 1.1920929e-07f;   // 0x014a5e90

// A float stored to memory and read back (32-bit rounding of an x87 value).
static __forceinline float Rounded(double x)
{
    volatile float m = (float)x;
    return m;
}

// Unrounded intermediates are typed `double`: at the FPU's 64-bit precision they stay on the x87
// stack exactly as in the original, and if cl has to spill one it keeps 53 bits instead of 24.
typedef double hkExtReal;

static __forceinline hkExtReal dot3(const hkVector4& a, const hkVector4& b)
{
    return (hkExtReal)a.x * b.x + (hkExtReal)a.z * b.z + (hkExtReal)a.y * b.y;
}

// hkVector4::normalize3 on a vector held in memory: scales all four components by 1/|xyz|
// (0 when the length is 0). The inverse stays unrounded; the squared length is spilled (rounded)
// in the manifold loop's copy (spillLength) and kept on the FPU stack in the point-0 copy.
template <bool spillLength>
static __forceinline void normalize3(hkVector4& v)
{
    hkExtReal len2 = (hkExtReal)v.x * v.x + (hkExtReal)v.y * v.y + (hkExtReal)v.z * v.z;
    if (spillLength)
        len2 = Rounded(len2);
    hkExtReal inv;
    if (len2 == 0.0f)
        inv = 0.0f;
    else
        inv = 1.0f / sqrt(len2);
    v.x = Rounded(inv * v.x);
    v.y = Rounded(inv * v.y);
    v.z = Rounded(inv * v.z);
    v.w = Rounded(inv * v.w);
}

// @ 0x01106490
extern "C" void hkCollideCapsuleUtilManifoldCapsVsCaps(const hkVector4* capsA, float capsARadius,
                                                       const hkVector4* capsB, float capsBRadius,
                                                       hkContactPoint* pointsOut)
{
    hkVector4 dA;
    dA.x = Rounded((hkExtReal)capsA[1].x - capsA[0].x);
    dA.y = Rounded((hkExtReal)capsA[1].y - capsA[0].y);
    dA.z = Rounded((hkExtReal)capsA[1].z - capsA[0].z);
    dA.w = Rounded((hkExtReal)capsA[1].w - capsA[0].w);
    hkVector4 dB;
    dB.x = Rounded((hkExtReal)capsB[1].x - capsB[0].x);
    dB.y = Rounded((hkExtReal)capsB[1].y - capsB[0].y);
    dB.z = Rounded((hkExtReal)capsB[1].z - capsB[0].z);
    dB.w = Rounded((hkExtReal)capsB[1].w - capsB[0].w);

    // orient segment A along B
    hkExtReal dAdBExact = dot3(dB, dA);
    float dAdB = Rounded(dAdBExact);
    hkVector4 segA[2];
    if (dAdBExact < 0.0f) {
        dAdB = -dAdB;
        segA[0] = capsA[1];
        dA.x = -dA.x;
        dA.y = -dA.y;
        dA.z = -dA.z;
        dA.w = -dA.w;
        segA[1] = capsA[0];
    } else {
        segA[0] = capsA[0];
        segA[1] = capsA[1];
    }

    // --- closest points between the segments (hkLineSegmentUtil::closestLineSegLineSeg) ---------
    hkExtReal dx, dy, dz;   // unrounded
    dx = (hkExtReal)capsB[0].x - segA[0].x;
    dy = (hkExtReal)capsB[0].y - segA[0].y;
    dz = (hkExtReal)capsB[0].z - segA[0].z;
    float projA = Rounded(dx * dA.x + dz * dA.z + dy * dA.y);
    float projB = Rounded(dx * dB.x + dz * dB.z + dy * dB.y);
    float dA2 = Rounded(dot3(dA, dA));
    hkExtReal dB2Exact = dot3(dB, dB);
    float dB2 = Rounded(dB2Exact);
    float dA2dB2 = Rounded(dB2Exact * dA2);
    float dAdB2 = Rounded((hkExtReal)dAdB * dAdB);
    float det = Rounded(fabs((hkExtReal)dA2dB2 - dAdB2));
    hkExtReal numExact = (hkExtReal)dB2 * projA - (hkExtReal)projB * dAdB;
    float num = Rounded(numExact);

    int flags;
    hkExtReal t;   // unrounded
    if (det * det <= numExact * det) {
        t = 1.0f;
        flags = 1;
    } else if (num <= 0.0f) {
        t = 0.0f;
        flags = 2;
    } else if ((fabs((hkExtReal)dA2dB2) + dAdB2) * 9.5367432e-07f < det) {
        t = (hkExtReal)num / det;
        flags = 0;
    } else {
        t = 1.0f;
        flags = 1;
    }

    hkExtReal uExact = dAdB * t - projB;
    float u = Rounded(uExact);
    if (uExact >= dB2) {
        u = 1.0f;
        flags = 4;
    } else if (u <= 0.0f) {
        u = 0.0f;
        flags = 8;
    } else {
        u = Rounded((hkExtReal)u / dB2);
        goto done;
    }
    {
        hkExtReal tExact = (hkExtReal)u * dAdB + projA;
        float tr = Rounded(tExact);
        if (tExact <= 0.0f) {
            t = 0.0f;
            flags |= 2;
        } else if (tr >= dA2) {
            t = 1.0f;
            flags |= 1;
        } else {
            t = (hkExtReal)tr / dA2;
        }
    }
done:

    hkVector4 closestA;
    closestA.x = Rounded(dA.x * t + segA[0].x);
    closestA.y = Rounded(dA.y * t + segA[0].y);
    closestA.z = Rounded(dA.z * t + segA[0].z);
    closestA.w = Rounded(dA.w * t + segA[0].w);
    hkVector4 closestB;
    closestB.x = Rounded((hkExtReal)dB.x * u + capsB[0].x);
    closestB.y = Rounded((hkExtReal)dB.y * u + capsB[0].y);
    closestB.z = Rounded((hkExtReal)dB.z * u + capsB[0].z);
    closestB.w = Rounded((hkExtReal)dB.w * u + capsB[0].w);
    hkExtReal diffX = closestA.x - closestB.x;   // unrounded
    hkVector4 diff;
    diff.y = Rounded((hkExtReal)closestA.y - closestB.y);
    diff.z = Rounded((hkExtReal)closestA.z - closestB.z);
    diff.w = Rounded((hkExtReal)closestA.w - closestB.w);

    // --- point 0 ---------------------------------------------------------------------------------
    float radiusSum = Rounded((hkExtReal)capsARadius + capsBRadius);
    hkExtReal maxDist = radiusSum + pointsOut[0].m_separatingNormal.w;
    if (maxDist < HK_REAL_EPSILON)
        maxDist = HK_REAL_EPSILON;
    hkVector4& n0 = pointsOut[0].m_separatingNormal;
    n0.y = diff.y;
    n0.w = diff.w;
    hkExtReal dist2Exact = diffX * diffX + (hkExtReal)diff.z * diff.z + (hkExtReal)diff.y * diff.y;
    float dist2 = Rounded(dist2Exact);
    n0.z = diff.z;
    if (!(dist2Exact < maxDist * maxDist)) {
        // separated: only the plane
        float inv = Rounded(1.0f / sqrt((hkExtReal)dist2));
        n0.x = Rounded(diffX);
        n0.x = Rounded((hkExtReal)inv * n0.x);
        n0.y = Rounded((hkExtReal)inv * n0.y);
        n0.z = Rounded((hkExtReal)inv * n0.z);
        n0.w = Rounded((hkExtReal)inv * n0.w);
        n0.w = Rounded((hkExtReal)inv * dist2 - radiusSum);
        return;
    }
    n0.x = Rounded(diffX);
    hkExtReal dist;   // unrounded
    if (dist2 < HK_REAL_EPSILON) {
        // the segments intersect: any normal perpendicular to A
        dist = 0.0f;
        int i0 = 0, i1 = 1, i2 = 2;
        float ax = fabsf(dA.x);
        float ay = fabsf(dA.y);
        float az = fabsf(dA.z);
        float m = ax;
        if (ay < ax) {
            i1 = 0;
            m = ay;
            i0 = 1;
        }
        if (az < m) {
            i2 = i0;
            i0 = 2;
        }
        float* dAv = &dA.x;
        float* nv = &n0.x;
        float v = -dAv[i1];
        nv[i0] = 0.0f;
        n0.w = 0.0f;
        nv[i1] = dAv[i2];
        nv[i2] = v;
        normalize3<false>(n0);
    } else {
        hkExtReal invExact = 1.0f / sqrt((hkExtReal)dist2);
        float inv = Rounded(invExact);
        dist = invExact * dist2;
        n0.x = Rounded((hkExtReal)inv * n0.x);
        n0.y = Rounded((hkExtReal)inv * n0.y);
        n0.z = Rounded((hkExtReal)inv * n0.z);
        n0.w = Rounded((hkExtReal)inv * n0.w);
    }
    {
        hkVector4& p0 = pointsOut[0].m_position;
        hkExtReal s = capsBRadius - dist;
        p0 = closestA;
        p0.x = Rounded(s * n0.x + closestA.x);
        p0.y = Rounded(s * n0.y + closestA.y);
        p0.z = Rounded(s * n0.z + closestA.z);
        p0.w = Rounded(s * n0.w + closestA.w);
        n0.w = Rounded(dist - radiusSum);
    }

    // --- end-point contacts (skipped when the segments are close to parallel) -------------------
    if (dA2dB2 * 0.2f < det)
        return;

    hkExtReal invDet = 1.0f / dA2dB2;   // unrounded
    hkVector4 p = segA[0];
    hkVector4 q = capsB[0];
    hkExtReal qx = q.x;                 // q.x lives on the FPU stack (unrounded once moved)
    float kA = Rounded(dB2 * invDet);
    float kB = Rounded(invDet * dA2);
    int mask = 10;
    hkContactPoint* out = pointsOut + 1;
    for (int i = 0;; ++i, ++out) {
        if ((mask & flags) == 0) {
            // a, b: projections of the end-point pair (unrounded); the second pair's are
            // (dA2 - a) - dAdB and (dB2 - b) - dAdB
            hkExtReal a = i ? ((hkExtReal)dA2 - projA) - dAdB : projA;
            hkExtReal b = i ? ((hkExtReal)dB2 + projB) - dAdB : -(hkExtReal)projB;
            if (b > 0.0f) {
                if (b > dB2)
                    goto next;
                if (a > 0.0f) {
                    if (a > dA2)
                        goto next;
                    if (a * a * kA < b * b * kB)
                        goto moveP;
                }
                {
                    hkExtReal s = b * kB;
                    qx = dB.x * s + qx;
                    q.y = Rounded(dB.y * s + q.y);
                    q.z = Rounded(dB.z * s + q.z);
                    q.w = Rounded(dB.w * s + q.w);
                }
            } else if (a > 0.0f) {
                if (a > dA2)
                    goto next;
            moveP:
                hkExtReal s = a * kA;
                p.x = Rounded(dA.x * s + p.x);
                p.y = Rounded(dA.y * s + p.y);
                p.z = Rounded(dA.z * s + p.z);
                p.w = Rounded(dA.w * s + p.w);
            }
            {
                float rs = radiusSum;
                hkVector4 pq;
                pq.x = Rounded(p.x - qx);
                pq.y = Rounded((hkExtReal)p.y - q.y);
                pq.z = Rounded((hkExtReal)p.z - q.z);
                pq.w = Rounded((hkExtReal)p.w - q.w);
                hkExtReal maxD = (hkExtReal)rs + out->m_separatingNormal.w;
                hkExtReal d2Exact = (hkExtReal)pq.z * pq.z + (hkExtReal)pq.y * pq.y + (hkExtReal)pq.x * pq.x;
                float d2 = Rounded(d2Exact);
                if (d2Exact < maxD * maxD) {
                    hkExtReal len = sqrt((hkExtReal)d2);   // unrounded
                    hkVector4& n = out->m_separatingNormal;
                    n = pq;
                    if (d2 > HK_REAL_EPSILON)
                        normalize3<true>(n);
                    else
                        n = pointsOut[0].m_separatingNormal;
                    hkExtReal s = capsBRadius - len;
                    out->m_position = p;
                    out->m_position.x = Rounded(s * n.x + p.x);
                    out->m_position.y = Rounded(s * n.y + p.y);
                    out->m_position.z = Rounded(s * n.z + p.z);
                    out->m_position.w = Rounded(s * n.w + p.w);
                    n.w = Rounded(len - rs);
                }
            }
        }
    next:
        if (i == 1)
            return;
        p = segA[1];
        q = capsB[1];
        qx = q.x;
        dA.x = -dA.x;
        dA.y = -dA.y;
        dA.z = -dA.z;
        dA.w = -dA.w;
        mask = 5;
        dB.x = -dB.x;
        dB.y = -dB.y;
        dB.z = -dB.z;
        dB.w = -dB.w;
    }
}
