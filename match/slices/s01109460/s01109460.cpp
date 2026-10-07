// Slice s01109460 — Havok 3.1 hkBoxBoxCollisionDetection separating-axis test (3182 bytes).
// Tests the 3 face axes of A, the 3 face axes of B and the 9 edge-edge axes
// (A_i x B_j) for separation; stores the per-axis separating distances
// (+0xe0..+0x12c) and returns 1 as soon as an axis separates the boxes, else 0.
// Flags: /O2 /MD /Gy /TP (x87 FPU hkVector4, 16-byte aligned frame).
#include "types.h"
#include <math.h>

typedef float hkReal;

struct __declspec(align(16)) hkVector4 {
    hkReal x, y, z, w;
};

struct hkMatrix3 {
    hkVector4 c0, c1, c2;   // columns
    void setTranspose(const hkMatrix3& m);   // 01081550
};

// v = m * b
inline void setRotatedDir(hkVector4& v, const hkMatrix3& m, const hkVector4& b)
{
    const hkReal b0 = b.x;
    const hkReal b1 = b.y;
    const hkReal b2 = b.z;
    v.x = m.c0.x * b0 + m.c1.x * b1 + m.c2.x * b2;
    v.y = m.c0.y * b0 + m.c1.y * b1 + m.c2.y * b2;
    v.z = m.c0.z * b0 + m.c1.z * b1 + m.c2.z * b2;
}

// v = m^T * b
inline void setRotatedInverseDir(hkVector4& v, const hkMatrix3& m, const hkVector4& b)
{
    const hkReal b0 = b.x;
    const hkReal b1 = b.y;
    const hkReal b2 = b.z;
    v.x = m.c0.x * b0 + m.c0.y * b1 + m.c0.z * b2;
    v.y = m.c1.x * b0 + m.c1.y * b1 + m.c1.z * b2;
    v.z = m.c2.x * b0 + m.c2.y * b1 + m.c2.z * b2;
}

inline hkReal hkFabs(hkReal r) { return (hkReal)fabs(r); }

// hkVector4::compareGreaterThan4 style mask: x=8, y=4, z=2, w=1.
__forceinline int compareGreaterThan4(const hkVector4& v, const hkVector4& a)
{
    return ((v.x > a.x) ? 8 : 0) | ((v.y > a.y) ? 4 : 0) | ((v.z > a.z) ? 2 : 0) | ((v.w > a.w) ? 1 : 0);
}

struct hkBoxBoxUtils {
    static void cmpAllGT3(const hkVector4& v, const hkReal& r, int& mask);                                   // 01108660
    static void rsqrtAll3(hkVector4& v);                                                                     // 011086a0
    static void selectIfGT3(hkVector4& v, const hkReal& limit, const hkVector4& scale, const hkReal& bound);  // 011086f0
};

enum { HK_VECTOR3_COMPARE_MASK_XYZ = 0xe };

class hkBoxBoxCollisionDetection {
public:
    uint32_t m_pad00[8];
    hkMatrix3 m_aRb;                // +0x20 rotation of B in A
    hkVector4 m_pad50;
    hkVector4 m_radiusA;            // +0x60 box A half extents
    hkVector4 m_radiusB;            // +0x70 box B half extents
    hkVector4 m_pad80[3];
    hkReal m_tolerance;             // +0xb0
    uint32_t m_padb4[3];
    hkVector4 m_dinA;               // +0xc0 B's centre in A
    hkVector4 m_dinB;               // +0xd0 A's centre in B
    hkVector4 m_sepDist[5];         // +0xe0 faceA, faceB, edges A_x, A_y, A_z

    int checkIntersection(const hkVector4& tolerance4);
};

int hkBoxBoxCollisionDetection::checkIntersection(const hkVector4& tolerance4)
{
    const hkReal bound = 999.99994f;
    const hkReal limit = -1e17f;

    hkMatrix3 absR;
    absR.c0.x = hkFabs(m_aRb.c0.x);
    absR.c0.y = hkFabs(m_aRb.c0.y);
    absR.c0.z = hkFabs(m_aRb.c0.z);
    absR.c1.x = hkFabs(m_aRb.c1.x);
    absR.c1.y = hkFabs(m_aRb.c1.y);
    absR.c1.z = hkFabs(m_aRb.c1.z);
    absR.c2.x = hkFabs(m_aRb.c2.x);
    absR.c2.y = hkFabs(m_aRb.c2.y);
    absR.c2.z = hkFabs(m_aRb.c2.z);

    // ---- face axes of A
    {
        hkVector4 proj;
        setRotatedDir(proj, absR, m_radiusB);
        hkVector4 sum;
        sum.x = proj.x + m_radiusA.x;
        sum.y = proj.y + m_radiusA.y;
        sum.z = proj.z + m_radiusA.z;
        sum.w = m_radiusA.w;
        hkVector4 d;
        d.x = hkFabs(m_dinA.x) - sum.x;
        d.y = hkFabs(m_dinA.y) - sum.y;
        d.z = hkFabs(m_dinA.z) - sum.z;
        d.w = hkFabs(m_dinA.w) - sum.w;
        if (compareGreaterThan4(d, tolerance4) & HK_VECTOR3_COMPARE_MASK_XYZ)
            return 1;
        m_sepDist[0] = d;
    }

    // ---- face axes of B
    {
        hkVector4 proj;
        setRotatedInverseDir(proj, absR, m_radiusA);
        hkVector4 sum;
        sum.x = proj.x + m_radiusB.x;
        sum.y = proj.y + m_radiusB.y;
        sum.z = proj.z + m_radiusB.z;
        sum.w = m_radiusB.w;
        hkVector4 d;
        d.x = hkFabs(m_dinB.x) - sum.x;
        d.y = hkFabs(m_dinB.y) - sum.y;
        d.z = hkFabs(m_dinB.z) - sum.z;
        d.w = hkFabs(m_dinB.w) - sum.w;
        if (compareGreaterThan4(d, tolerance4) & HK_VECTOR3_COMPARE_MASK_XYZ)
            return 1;
        m_sepDist[1] = d;
    }

    // ---- edge axes A_i x B_j (vector components are j)
    hkMatrix3 rT;
    rT.setTranspose(m_aRb);
    hkVector4 sq0 = rT.c0;
    sq0.x *= sq0.x; sq0.y *= sq0.y; sq0.z *= sq0.z; sq0.w *= sq0.w;
    hkVector4 sq1 = rT.c1;
    sq1.x *= sq1.x; sq1.y *= sq1.y; sq1.z *= sq1.z; sq1.w *= sq1.w;
    hkVector4 sq2 = rT.c2;
    sq2.x *= sq2.x; sq2.y *= sq2.y; sq2.z *= sq2.z; sq2.w *= sq2.w;

    const hkVector4& rA = m_radiusA;
    const hkVector4& rB = m_radiusB;
    const hkVector4& t = m_dinA;

    // A_x x B_j
    {
        hkVector4 a;
        a.x = rT.c1.x * t.z; a.y = rT.c1.y * t.z; a.z = rT.c1.z * t.z; a.w = rT.c1.w * t.z;
        hkVector4 b;
        b.x = rT.c2.x * t.y; b.y = rT.c2.y * t.y; b.z = rT.c2.z * t.y; b.w = rT.c2.w * t.y;
        hkVector4 dist;
        dist.x = hkFabs(a.x - b.x); dist.y = hkFabs(a.y - b.y);
        dist.z = hkFabs(a.z - b.z); dist.w = hkFabs(a.w - b.w);
        hkReal r0 = absR.c0.z * rA.y + absR.c0.y * rA.z + absR.c2.x * rB.y + absR.c1.x * rB.z;
        hkReal r1 = absR.c1.z * rA.y + absR.c1.y * rA.z + absR.c0.x * rB.z + absR.c2.x * rB.x;
        hkReal r2 = absR.c2.z * rA.y + absR.c2.y * rA.z + absR.c0.x * rB.y + absR.c1.x * rB.x;
        hkVector4 len;
        len.x = sq2.x + sq1.x; len.y = sq2.y + sq1.y; len.z = sq2.z + sq1.z; len.w = sq2.w + sq1.w;
        dist.x -= r0; dist.y -= r1; dist.z -= r2;
        hkBoxBoxUtils::rsqrtAll3(len);
        dist.x = len.x * dist.x; dist.y = len.y * dist.y; dist.z = len.z * dist.z; dist.w = len.w * dist.w;
        if (dist.x > m_tolerance || dist.y > m_tolerance || dist.z > m_tolerance)
            return 1;
        hkBoxBoxUtils::selectIfGT3(dist, limit, len, bound);
        m_sepDist[2] = dist;
    }

    // A_y x B_j
    {
        hkVector4 a;
        a.x = rT.c2.x * t.x; a.y = rT.c2.y * t.x; a.z = rT.c2.z * t.x; a.w = rT.c2.w * t.x;
        hkVector4 b;
        b.x = rT.c0.x * t.z; b.y = rT.c0.y * t.z; b.z = rT.c0.z * t.z; b.w = rT.c0.w * t.z;
        hkVector4 dist;
        dist.x = hkFabs(a.x - b.x); dist.y = hkFabs(a.y - b.y);
        dist.z = hkFabs(a.z - b.z); dist.w = hkFabs(a.w - b.w);
        hkReal r0 = absR.c0.z * rA.x + absR.c2.y * rB.y + absR.c0.x * rA.z + absR.c1.y * rB.z;
        hkReal r1 = absR.c1.z * rA.x + absR.c1.x * rA.z + absR.c0.y * rB.z + absR.c2.y * rB.x;
        hkReal r2 = absR.c2.z * rA.x + absR.c0.y * rB.y + absR.c2.x * rA.z + absR.c1.y * rB.x;
        hkVector4 len;
        len.x = sq2.x + sq0.x; len.y = sq2.y + sq0.y; len.z = sq2.z + sq0.z; len.w = sq2.w + sq0.w;
        dist.x -= r0; dist.y -= r1; dist.z -= r2;
        hkBoxBoxUtils::rsqrtAll3(len);
        dist.x = len.x * dist.x; dist.y = len.y * dist.y; dist.z = len.z * dist.z; dist.w = len.w * dist.w;
        int mask = compareGreaterThan4(dist, tolerance4) & HK_VECTOR3_COMPARE_MASK_XYZ;
        hkBoxBoxUtils::cmpAllGT3(dist, m_tolerance, mask);
        if (mask)
            return 1;
        hkBoxBoxUtils::selectIfGT3(dist, limit, len, bound);
        m_sepDist[3] = dist;
    }

    // A_z x B_j
    {
        hkVector4 a;
        a.x = rT.c0.x * t.y; a.y = rT.c0.y * t.y; a.z = rT.c0.z * t.y; a.w = rT.c0.w * t.y;
        hkVector4 b;
        b.x = rT.c1.x * t.x; b.y = rT.c1.y * t.x; b.z = rT.c1.z * t.x; b.w = rT.c1.w * t.x;
        hkVector4 dist;
        dist.x = hkFabs(a.x - b.x); dist.y = hkFabs(a.y - b.y);
        dist.z = hkFabs(a.z - b.z); dist.w = hkFabs(a.w - b.w);
        hkReal r0 = absR.c2.z * rB.y + absR.c0.y * rA.x + absR.c0.x * rA.y + absR.c1.z * rB.z;
        hkReal r1 = absR.c1.y * rA.x + absR.c1.x * rA.y + absR.c0.z * rB.z + absR.c2.z * rB.x;
        hkReal r2 = absR.c0.z * rB.y + absR.c2.y * rA.x + absR.c2.x * rA.y + absR.c1.z * rB.x;
        hkVector4 len;
        len.x = sq1.x + sq0.x; len.y = sq1.y + sq0.y; len.z = sq1.z + sq0.z; len.w = sq1.w + sq0.w;
        dist.x -= r0; dist.y -= r1; dist.z -= r2;
        hkBoxBoxUtils::rsqrtAll3(len);
        dist.x = len.x * dist.x; dist.y = len.y * dist.y; dist.z = len.z * dist.z; dist.w = len.w * dist.w;
        int mask = compareGreaterThan4(dist, tolerance4) & HK_VECTOR3_COMPARE_MASK_XYZ;
        hkBoxBoxUtils::cmpAllGT3(dist, m_tolerance, mask);
        if (mask)
            return 1;
        hkBoxBoxUtils::selectIfGT3(dist, limit, len, bound);
        m_sepDist[4] = dist;
    }
    return 0;
}
