// Havok 3.1.0: hkGskManifold_verifyAndGetPoints @ 0x0110fe20  (/O2 /MD /Gy /EHsc /TP, x87 float, 16-byte aligned frame)
// Re-validates every cached GSK manifold contact point from index firstPointIndex on against the freshly
// fetched (world-space) vertices, writes the surviving points to the collision output and drops the rest
// (the contact manager is told to remove their ids). The manifold layout follows the Havok 6.x header
// hkpGskManifold.h; the work block (vertices + master normal + radii) is laid out as the callers in
// slices s010ff9e0 / s010fdf80 build it (info[8] right after verts[16]).
#include <math.h>

typedef unsigned char  hkUchar;
typedef unsigned short hkUint16;
typedef unsigned int   hkUint32;
typedef float          hkReal;
typedef hkUint16       hkContactPointId;

class __declspec(align(16)) hkVector4
{
public:
    float x, y, z, w;

    inline void setSub4(const hkVector4& a, const hkVector4& b)
    { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
    inline void setCross(const hkVector4& a, const hkVector4& b)
    {
        x = a.y * b.z - a.z * b.y;
        y = a.z * b.x - a.x * b.z;
        z = a.x * b.y - a.y * b.x;
        w = 0.0f;
    }
    inline hkReal dot3(const hkVector4& a) const { return x * a.x + y * a.y + z * a.z; }
    inline hkReal lengthSquared3() const { return x * x + y * y + z * z; }
    // (1-t)*a + t*b
    inline void setInterpolate4(const hkVector4& a, const hkVector4& b, hkReal t)
    {
        const hkReal s = 1.0f - t;
        x = s * a.x + t * b.x; y = s * a.y + t * b.y; z = s * a.z + t * b.z; w = s * a.w + t * b.w;
    }
    // this = a + b * r
    inline void setAddMul4(const hkVector4& a, const hkVector4& b, hkReal r)
    { x = b.x * r + a.x; y = b.y * r + a.y; z = b.z * r + a.z; w = b.w * r + a.w; }
    inline void setNeg4(const hkVector4& a) { x = -a.x; y = -a.y; z = -a.z; w = -a.w; }
    inline void mul4(hkReal r) { x *= r; y *= r; z *= r; w *= r; }
    // normalize the xyz part; a zero vector stays zero
    inline void normalize3IfNotZero()
    {
        const hkReal len2 = lengthSquared3();
        const hkReal inv = (len2 == 0.0f) ? 0.0f : 1.0f / (hkReal)sqrt(len2);
        mul4(inv);
    }
};

// 4-bit sign mask: x -> bit 3, y -> bit 2, z -> bit 1, w -> bit 0
static inline int signMask4(hkReal x, hkReal y, hkReal z, hkReal w)
{
    return ((x < 0.0f) << 3) | ((y < 0.0f) << 2) | ((z < 0.0f) << 1) | (int)(w < 0.0f);
}

struct hkGskManifold
{
    struct ContactPoint
    {
        hkUchar          m_dimA;
        hkUchar          m_dimB;
        hkContactPointId m_id;
        hkUchar          m_vert[4];   // byte offsets (index * sizeof(hkVector4)) into the work vertices
    };
    hkUchar      m_numVertsA;
    hkUchar      m_numVertsB;
    hkUchar      m_numContactPoints;
    ContactPoint m_contactPoints[4];
    hkUchar      m_padding[32];       // followed by the vertex id array
};

struct hkGskManifoldWork
{
    hkVector4 m_vertices[16];   // +0x000 vertices of A then B (world space)
    hkVector4 m_masterNormal;   // +0x100
    hkReal    m_radiusA;        // +0x110
    hkReal    m_radiusB;        // +0x114
    hkReal    m_keepContact;    // +0x118
    hkReal    m_radiusSumSqrd;  // +0x11c
};

struct hkProcessCdPoint
{
    hkVector4        m_position;           // +0x00
    hkVector4        m_separatingNormal;   // +0x10 (w = distance)
    hkContactPointId m_contactPointId;     // +0x20
    hkUint16         m_pad[7];
};

struct hkProcessCollisionOutput
{
    hkProcessCdPoint* m_firstFreeContactPoint;   // +0x0
};

struct hkContactMgr
{
    virtual void v0();
    virtual void v1();
    virtual void addContactPoint();
    virtual void reserveContactPoints();
    virtual void removeContactPoint(hkContactPointId id);   // +0x10
};

// Compacts the vertex id array after points were removed (0x0110fc50; takes the manifold in ecx).
void __fastcall hkGskManifold_removeUnusedVertices(hkGskManifold* manifold);

static inline const hkVector4& vertexAt(const hkGskManifoldWork& work, int byteOffset)
{
    return *(const hkVector4*)((const char*)&work + byteOffset);
}

// Havok's hkString::memCpy4
static inline void memCpy4(void* dst, const void* src, int numWords)
{
    hkUint32* d = (hkUint32*)dst;
    const hkUint32* s = (const hkUint32*)src;
    for (int i = numWords - 1; i >= 0; i--)
        *d++ = *s++;
}

// @ 0x0110fe20
void __cdecl hkGskManifold_verifyAndGetPoints(hkGskManifold& manifold, const hkGskManifoldWork& work, int firstPointIndex,
                                              hkProcessCollisionOutput& out, hkContactMgr* contactMgr)
{
    const int originalNumPoints = manifold.m_numContactPoints;

    hkGskManifold::ContactPoint* cpoint = &manifold.m_contactPoints[firstPointIndex];
    for (int i = firstPointIndex; i < manifold.m_numContactPoints; i++, cpoint++)
    {
        hkProcessCdPoint* cp = out.m_firstFreeContactPoint;

        hkVector4 pointA;   // contact point on A
        hkVector4 diff;     // pointA - pointB (xyz)
        hkVector4 normal;
        int failed;

        switch (cpoint->m_dimA * 4 + cpoint->m_dimB)
        {
        case 1 * 4 + 1:   // point - point
        {
            const hkVector4& a = vertexAt(work, cpoint->m_vert[0]);
            const hkVector4& b = vertexAt(work, cpoint->m_vert[1]);
            hkVector4 d; d.setSub4(a, b);
            if (d.lengthSquared3() > work.m_radiusSumSqrd)
            {
                failed = 1;
                break;
            }
            diff = d;
            normal = work.m_masterNormal;
            pointA = a;
            failed = 0;
            break;
        }

        case 1 * 4 + 2:   // point A - edge B
        {
            const hkVector4& a  = vertexAt(work, cpoint->m_vert[0]);
            const hkVector4& b0 = vertexAt(work, cpoint->m_vert[1]);
            const hkVector4& b1 = vertexAt(work, cpoint->m_vert[2]);
            hkVector4 edge; edge.setSub4(b1, b0);
            pointA = a;
            normal = work.m_masterNormal;
            hkVector4 d1; d1.setSub4(b1, a);
            hkVector4 d0; d0.setSub4(a, b0);
            hkVector4 cross; cross.setCross(edge, d1);
            const hkReal dot1 = d1.dot3(edge);
            const hkReal dot0 = d0.dot3(edge);
            const hkReal edgeLen2 = edge.lengthSquared3();
            const int mask = signMask4(dot1, dot0, cross.lengthSquared3(), edgeLen2 * work.m_radiusSumSqrd);
            if (mask & 0xd)
            {
                failed = 1;
                break;
            }
            const hkReal t = dot1 / (dot0 + dot1);
            hkVector4 pointB; pointB.setInterpolate4(b0, b1, t);
            diff.setSub4(pointA, pointB);
            failed = 0;
            break;
        }

        case 1 * 4 + 3:   // point A - triangle B
        {
            const hkVector4& a  = vertexAt(work, cpoint->m_vert[0]);
            const hkVector4& b0 = vertexAt(work, cpoint->m_vert[1]);
            const hkVector4& b1 = vertexAt(work, cpoint->m_vert[2]);
            const hkVector4& b2 = vertexAt(work, cpoint->m_vert[3]);
            diff.setSub4(a, b0);
            pointA = a;
            hkVector4 e0; e0.setSub4(b2, b1);
            hkVector4 e1; e1.setSub4(b0, b2);
            hkVector4 e2; e2.setSub4(b1, b0);
            hkVector4 n; n.setCross(e0, e1);
            n.normalize3IfNotZero();
            hkVector4 p0; p0.setSub4(a, b1);
            hkVector4 p1; p1.setSub4(a, b2);
            hkVector4 p2; p2.setSub4(a, b0);
            hkVector4 c0; c0.setCross(p0, e0);
            hkVector4 c1; c1.setCross(p1, e1);
            hkVector4 c2; c2.setCross(p2, e2);
            normal = n;
            const int mask = signMask4(c0.dot3(n), c1.dot3(n), c2.dot3(n), n.dot3(work.m_masterNormal));
            if (mask & 1)
                normal.setNeg4(n);
            failed = ~mask & 0xe;
            break;
        }

        case 2 * 4 + 1:   // edge A - point B
        {
            const hkVector4& a0 = vertexAt(work, cpoint->m_vert[0]);
            const hkVector4& a1 = vertexAt(work, cpoint->m_vert[1]);
            const hkVector4& b  = vertexAt(work, cpoint->m_vert[2]);
            hkVector4 edge; edge.setSub4(a1, a0);
            normal = work.m_masterNormal;
            hkVector4 d1; d1.setSub4(a1, b);
            hkVector4 d0; d0.setSub4(b, a0);
            hkVector4 cross; cross.setCross(edge, d1);
            const hkReal dot1 = d1.dot3(edge);
            const hkReal dot0 = d0.dot3(edge);
            const hkReal edgeLen2 = edge.lengthSquared3();
            const int mask = signMask4(dot1, dot0, cross.lengthSquared3(), edgeLen2 * work.m_radiusSumSqrd);
            if (mask & 0xd)
            {
                failed = 1;
                break;
            }
            const hkReal t = dot1 / (dot1 + dot0);
            pointA.setInterpolate4(a1, a0, t);
            diff.setSub4(pointA, b);
            failed = 0;
            break;
        }

        case 2 * 4 + 2:   // edge A - edge B
        {
            const hkVector4& a0 = vertexAt(work, cpoint->m_vert[0]);
            const hkVector4& a1 = vertexAt(work, cpoint->m_vert[1]);
            const hkVector4& b0 = vertexAt(work, cpoint->m_vert[2]);
            const hkVector4& b1 = vertexAt(work, cpoint->m_vert[3]);
            hkVector4 edgeA; edgeA.setSub4(a1, a0);
            hkVector4 edgeB; edgeB.setSub4(b1, b0);
            hkVector4 d0; d0.setSub4(a0, b0);
            hkVector4 d1; d1.setSub4(a1, b1);
            hkVector4 n; n.setCross(edgeA, edgeB);
            hkVector4 planeA; planeA.setCross(edgeA, n);
            hkVector4 planeB; planeB.setCross(edgeB, n);
            normal = work.m_masterNormal;
            const hkReal distA0 = d0.dot3(planeB);
            const hkReal distB0 = d0.dot3(planeA);
            const hkReal distA1 = d1.dot3(planeB);
            const hkReal distB1 = d1.dot3(planeA);
            const int mask = signMask4(distA0, distB0, distA1, distB1);
            if (mask != 0xc && mask != 3)
            {
                failed = 1;
                break;
            }
            const hkReal tA = distA0 / (distA0 - distA1);
            pointA.setInterpolate4(a0, a1, tA);
            const hkReal tB = distB0 / (distB0 - distB1);
            hkVector4 pointB; pointB.setInterpolate4(b0, b1, tB);
            diff.setSub4(pointA, pointB);
            failed = 0;
            break;
        }

        case 3 * 4 + 1:   // triangle A - point B
        {
            const hkVector4& a0 = vertexAt(work, cpoint->m_vert[0]);
            const hkVector4& a1 = vertexAt(work, cpoint->m_vert[1]);
            const hkVector4& a2 = vertexAt(work, cpoint->m_vert[2]);
            const hkVector4& b  = vertexAt(work, cpoint->m_vert[3]);
            diff.setSub4(a0, b);
            hkVector4 e0; e0.setSub4(a2, a1);
            hkVector4 e1; e1.setSub4(a0, a2);
            hkVector4 e2; e2.setSub4(a1, a0);
            hkVector4 n; n.setCross(e0, e1);
            n.normalize3IfNotZero();
            hkVector4 p0; p0.setSub4(b, a1);
            hkVector4 p1; p1.setSub4(b, a2);
            hkVector4 p2; p2.setSub4(b, a0);
            hkVector4 c0; c0.setCross(p0, e0);
            hkVector4 c1; c1.setCross(p1, e1);
            hkVector4 c2; c2.setCross(p2, e2);
            const hkReal d0 = c0.dot3(n);
            const hkReal d1 = c1.dot3(n);
            const hkReal d2 = c2.dot3(n);
            const hkReal dn = n.dot3(work.m_masterNormal);
            // project B onto the triangle plane
            pointA.setAddMul4(b, n, diff.dot3(n));
            normal = n;
            const int mask = signMask4(d0, d1, d2, dn);
            if (mask & 1)
                normal.setNeg4(n);
            failed = ~mask & 0xe;
            break;
        }

        case 0:
        default:
            failed = 1;
            break;
        }

        if (!failed)
        {
            const hkReal dist = normal.dot3(diff) - work.m_radiusB;
            const hkReal negDist = -dist;
            const hkReal finalDist = dist - work.m_radiusA;
            if (finalDist < work.m_keepContact)
            {
                cp->m_position.setAddMul4(pointA, normal, negDist);
                cp->m_separatingNormal = normal;
                cp->m_separatingNormal.w = finalDist;
                cp->m_contactPointId = cpoint->m_id;
                out.m_firstFreeContactPoint++;
                continue;
            }
        }

        // the point is no longer valid: release it and move the last point into its slot
        if (cpoint->m_id != 0xffff)
            contactMgr->removeContactPoint(cpoint->m_id);
        manifold.m_numContactPoints--;
        *cpoint = manifold.m_contactPoints[manifold.m_numContactPoints];
        i--;
        cpoint--;
    }

    if (manifold.m_numContactPoints < originalNumPoints)
    {
        // the vertex ids follow the contact points: move them down over the freed slots
        const int numVerts = manifold.m_numVertsA + manifold.m_numVertsB;
        memCpy4(&manifold.m_contactPoints[manifold.m_numContactPoints], &manifold.m_contactPoints[originalNumPoints],
                (numVerts + 1) >> 1);
        hkGskManifold_removeUnusedVertices(&manifold);
    }
}
