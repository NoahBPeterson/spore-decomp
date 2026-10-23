// Havok 3.1.0 slice s010c90a0 (0x010c90a0..0x010c9c70): the hkCylinderShape virtuals
// (vtable 0x014a40c4) -- support-vertex queries, the vertex-id decoder, the collision-sphere
// set and the AABB fit. Linked into SporeApp.exe out of a Havok 3.1.0 static library built
// with VC .NET 2003, hence /vc71.
//
// LAYOUT (hkCylinderShape, 0x60 bytes; hkConvexShape <- hkSphereRepShape <- hkShape <-
// hkReferencedObject). Offsets are the 32-bit ones of the shipped binary and match
// match/include/havok31/hkReflectedClasses.h:
//   +0x00 vtable 0x014a40c4      +0x04 m_memSizeAndFlags   +0x06 m_referenceCount
//   +0x08 m_userData (hkShape)   +0x0c m_radius (hkConvexShape)
//   +0x10 m_cylRadius            +0x20 m_vertexA           +0x30 m_vertexB
//   +0x40 m_perpendicular1       +0x50 m_perpendicular2
//
// VTABLE 0x014a40c4: 010dd550, 010c9030, 010c9020, 010c9920 (getAabb), 010c0f80, 010c9c70,
//   010c0fc0, 010c9000, 010c9520 (getCollisionSpheres), 010c90a0 (getSupportingVertex),
//   010c9360 (convertVertexIdsToVertices), 010c9500 (getFirstVertex).
//
// The vertex id packed by getSupportingVertex / consumed by convertVertexIdsToVertices is a
// byte: bits 0-3 pick the 16-fold angle step, bit 4 swaps the sin/cos roles, bit 5 negates the
// sin term, bit 6 negates the cos term and bit 7 picks the base vertex (0 = m_vertexB,
// 1 = m_vertexA). The id is stored in the vertex's w component with the 0x3f000000 exponent
// forced on (so w reads back as a small float carrying the id).
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------------------------------
// Minimal Havok value types (only the members these functions touch).
// ---------------------------------------------------------------------------------------------------
struct hkVector4
{
    float x, y, z, w;
};

// A collision-dispatch vertex: a plain 16-byte vector whose w carries the encoded vertex id.
struct hkCdVertex
{
    float x, y, z, w;
};

struct hkAabb
{
    hkVector4 m_min;   // +0x00
    hkVector4 m_max;   // +0x10
};

// A collision sphere: position in x/y/z, radius in w.
struct hkSphere
{
    hkVector4 m_pos;
};

struct hkTransform
{
    float m[16];   // 3x3 rotation in the leading 12 floats, translation in the last vector
};

// ---------------------------------------------------------------------------------------------------
// The cylinder shape.
// ---------------------------------------------------------------------------------------------------
struct hkCylinderShape
{
    virtual void v00();                                                             // slot 0  0x010dd550
    virtual void v01();                                                             // slot 1  0x010c9030
    virtual void v02();                                                             // slot 2  0x010c9020
    virtual void getAabb(const hkTransform& transform, float tolerance, hkAabb& aabb) const;  // slot 3
    virtual void v04();                                                             // slot 4  0x010c0f80
    virtual void v05();                                                             // slot 5  0x010c9c70
    virtual void v06();                                                             // slot 6  0x010c0fc0
    virtual void v07();                                                             // slot 7  0x010c9000
    virtual const hkSphere* getCollisionSpheres(hkSphere* spheres) const;           // slot 8
    virtual void getSupportingVertex(const hkVector4& direction, hkCdVertex& vertex) const;  // slot 9
    virtual void convertVertexIdsToVertices(const unsigned short* ids, int numIds,
                                            hkCdVertex* vertices) const;            // slot 10
    virtual void getFirstVertex(hkVector4& vertex) const;                           // slot 11

    uint16_t m_memSizeAndFlags;   // +0x04
    uint16_t m_referenceCount;    // +0x06
    int32_t  m_userData;          // +0x08
    float    m_radius;            // +0x0c
    float    m_cylRadius;         // +0x10
    uint32_t m_pad14[3];          // +0x14
    hkVector4 m_vertexA;          // +0x20
    hkVector4 m_vertexB;          // +0x30
    hkVector4 m_perpendicular1;   // +0x40
    hkVector4 m_perpendicular2;   // +0x50
};

// ---------------------------------------------------------------------------------------------------
// Globals and helpers outside this slice.
// ---------------------------------------------------------------------------------------------------
extern float g_hkSupportScale;       // 0x015ba2d0  scale applied to the supporting-vertex angle
extern float g_hkAngleStep;          // 0x015ba2d4  (2*pi / 16, the 16-fold angle step)
extern float g_hkFpuRoundingValue;   // 0x015ba2d8  initialised by the ctor below

// 0x010c9050: probes the current FPU rounding mode and returns a float in [0,1].
float hkFpuRoundingProbe();

// 0x010c98e0
// @ 0x010c98e0
void hkCylinderShape_init(hkCylinderShape* self)
{
    if (self)
    {
        self->m_referenceCount = 1;
        *(uint32_t*)self = 0x14a40c4;
        if (g_hkFpuRoundingValue < 0.0f)
            g_hkFpuRoundingValue = 1.0f - hkFpuRoundingProbe();
    }
}

// 0x010c90a0
// @ 0x010c90a0
void hkCylinderShape::getSupportingVertex(const hkVector4& direction, hkCdVertex& vertex) const
{
    float d1 = m_perpendicular1.x * direction.x
             + (m_perpendicular1.y * direction.y + m_perpendicular1.z * direction.z);
    float d2 = m_perpendicular2.x * direction.x
             + (m_perpendicular2.y * direction.y + m_perpendicular2.z * direction.z);
    float len2 = d1 * d1 + d2 * d2;

    int   d2Sign;
    float n1, n2;                       // normalised projections onto m_perpendicular1 / 2
    if (len2 < 1.4210855e-14f)
    {
        d2Sign = 1;
        n2 = 0.0f;
        n1 = 1.0f;
    }
    else
    {
        float inv = 1.0f / sqrtf(len2);
        n2 = inv * d2;
        n1 = inv * d1;
        d2Sign = (n2 < 0.0f) ? 0 : 1;
    }

    float a1 = fabsf(n1);
    float a2 = fabsf(n2);
    int   n2Smaller = (a2 < a1);
    float minAbs = n2Smaller ? a2 : a1;

    float height = (m_vertexB.x - m_vertexA.x) * direction.x
                 + ((m_vertexB.y - m_vertexA.y) * direction.y
                  + (m_vertexB.z - m_vertexA.z) * direction.z);

    int n1Sign = (n1 >= 0.0f) ? 1 : 0;
    int heightNeg = (height < 0.0f) ? 1 : 0;
    unsigned int id = (unsigned int)(n2Smaller
                      + (n1Sign + (d2Sign + heightNeg * 2) * 2) * 2) * 0x10
                      + (int)(g_hkSupportScale * minAbs - g_hkFpuRoundingValue + 0.05f);

    // Decode the id into the base vertex plus a scaled perpendicular offset.
    unsigned char b = (unsigned char)id;
    float angle = ((float)(id & 0xf) + 0.5f) * g_hkAngleStep;
    float c, s;
    if ((b >> 4 & 1) == 0)
    {
        c = sqrtf(1.0f - angle * angle);
        s = angle;
    }
    else
    {
        c = angle;
        s = sqrtf(1.0f - angle * angle);
    }
    if ((b >> 6 & 1) == 0) c = -c;
    if ((b >> 5 & 1) == 0) s = -s;

    const hkVector4& base = (b & 0x80) ? m_vertexA : m_vertexB;
    float r = m_cylRadius;
    vertex.x = (c * m_perpendicular2.x + s * m_perpendicular1.x) * r + base.x;
    vertex.y = (c * m_perpendicular2.y + s * m_perpendicular1.y) * r + base.y;
    vertex.z = (c * m_perpendicular2.z + s * m_perpendicular1.z) * r + base.z;
    vertex.w = (c * m_perpendicular2.w + s * m_perpendicular1.w) * r + base.w;
    *(uint32_t*)&vertex.w = id | 0x3f000000u;
}

// 0x010c9360
// @ 0x010c9360
void hkCylinderShape::convertVertexIdsToVertices(const unsigned short* ids, int numIds,
                                                 hkCdVertex* vertices) const
{
    for (int i = numIds - 1; i >= 0; --i)
    {
        unsigned int id = (unsigned int)*ids;
        unsigned char b = (unsigned char)id;
        float angle = ((float)(id & 0xf) + 0.5f) * g_hkAngleStep;
        float c, s;
        if ((b >> 4 & 1) == 0)
        {
            c = sqrtf(1.0f - angle * angle);
            s = angle;
        }
        else
        {
            c = angle;
            s = sqrtf(1.0f - angle * angle);
        }
        if ((b >> 6 & 1) == 0) c = -c;
        if ((b >> 5 & 1) == 0) s = -s;

        const hkVector4& base = (b & 0x80) ? m_vertexA : m_vertexB;
        float r = m_cylRadius;
        vertices->x = (c * m_perpendicular2.x + s * m_perpendicular1.x) * r + base.x;
        vertices->y = (c * m_perpendicular2.y + s * m_perpendicular1.y) * r + base.y;
        vertices->z = (c * m_perpendicular2.z + s * m_perpendicular1.z) * r + base.z;
        vertices->w = (c * m_perpendicular2.w + s * m_perpendicular1.w) * r + base.w;
        *(uint32_t*)&vertices->w = id | 0x3f000000u;

        ++ids;
        ++vertices;
    }
}

// 0x010c9500
// @ 0x010c9500
void hkCylinderShape::getFirstVertex(hkVector4& vertex) const
{
    vertex.x = m_vertexB.x;
    vertex.y = m_vertexB.y;
    vertex.z = m_vertexB.z;
    vertex.w = m_vertexB.w;
}

// 0x010c9520
// @ 0x010c9520
const hkSphere* hkCylinderShape::getCollisionSpheres(hkSphere* spheres) const
{
    float r = m_cylRadius;
    float r707 = r * 0.70710677f;

    // (perp1 +/- perp2) * r * sin(45deg)
    float sx = (m_perpendicular1.x + m_perpendicular2.x) * r707;
    float sy = (m_perpendicular1.y + m_perpendicular2.y) * r707;
    float sz = (m_perpendicular1.z + m_perpendicular2.z) * r707;
    float dx = (m_perpendicular1.x - m_perpendicular2.x) * r707;
    float dy = (m_perpendicular1.y - m_perpendicular2.y) * r707;
    float dz = (m_perpendicular1.z - m_perpendicular2.z) * r707;

    // perp1 * r and perp2 * r
    float ax = r * m_perpendicular1.x;
    float ay = r * m_perpendicular1.y;
    float az = r * m_perpendicular1.z;
    float bx = r * m_perpendicular2.x;
    float by = r * m_perpendicular2.y;
    float bz = r * m_perpendicular2.z;

    float rad = m_radius;

    for (int k = 0; k < 2; ++k)
    {
        const hkVector4& base = k ? m_vertexB : m_vertexA;
        hkSphere* o = spheres + k * 8;

        o[0].m_pos.x = base.x + ax; o[0].m_pos.y = base.y + ay; o[0].m_pos.z = base.z + az;
        o[1].m_pos.x = base.x + sx; o[1].m_pos.y = base.y + sy; o[1].m_pos.z = base.z + sz;
        o[2].m_pos.x = base.x + bx; o[2].m_pos.y = base.y + by; o[2].m_pos.z = base.z + bz;
        o[3].m_pos.x = base.x - dx; o[3].m_pos.y = base.y - dy; o[3].m_pos.z = base.z - dz;
        o[4].m_pos.x = base.x - ax; o[4].m_pos.y = base.y - ay; o[4].m_pos.z = base.z - az;
        o[5].m_pos.x = base.x - sx; o[5].m_pos.y = base.y - sy; o[5].m_pos.z = base.z - sz;
        o[6].m_pos.x = base.x - bx; o[6].m_pos.y = base.y - by; o[6].m_pos.z = base.z - bz;
        o[7].m_pos.x = base.x + dx; o[7].m_pos.y = base.y + dy; o[7].m_pos.z = base.z + dz;

        o[0].m_pos.w = rad; o[1].m_pos.w = rad; o[2].m_pos.w = rad; o[3].m_pos.w = rad;
        o[4].m_pos.w = rad; o[5].m_pos.w = rad; o[6].m_pos.w = rad; o[7].m_pos.w = rad;
    }
    return spheres;
}

// 0x010c9920
// @ 0x010c9920
void hkCylinderShape::getAabb(const hkTransform& transform, float tolerance, hkAabb& aabb) const
{
    const float* t = transform.m;

    float ax = m_vertexA.x, ay = m_vertexA.y, az = m_vertexA.z;
    float bx = m_vertexB.x, by = m_vertexB.y, bz = m_vertexB.z;

    float awx = t[0] * ax + (t[4] * ay + t[8] * az) + t[0xc];
    float awy = t[1] * ax + (t[5] * ay + t[9] * az) + t[0xd];
    float awz = t[2] * ax + (t[10] * az + t[6] * ay) + t[0xe];
    float bwx = t[0] * bx + (t[4] * by + t[8] * bz) + t[0xc];
    float bwy = t[1] * bx + (t[5] * by + t[9] * bz) + t[0xd];
    float bwz = t[2] * bx + (t[10] * bz + t[6] * by) + t[0xe];

    float dx = bwx - awx;
    float dy = bwy - awy;
    float dz = bwz - awz;
    float len2 = dx * dx + (dy * dy + dz * dz);

    float inv;
    if (len2 == 0.0f)
        inv = 0.0f;
    else
        inv = 1.0f / sqrtf(len2);

    float r = m_cylRadius;
    float tol = tolerance + m_radius;

    // Per-axis extension of the capsule: the disc radius plus the 1.01-fattened slant term.
    float ex = tol + r * sqrtf(1.01f - (dx * inv) * (dx * inv));
    float ey = sqrtf(1.01f - (dy * inv) * (dy * inv)) * r + tol;
    float ez = sqrtf(1.01f - (dz * inv) * (dz * inv)) * r + tol;

    float minx = (awx < bwx) ? awx : bwx;
    float miny = (awy < bwy) ? awy : bwy;
    float minz = (awz < bwz) ? awz : bwz;
    aabb.m_min.x = minx - ex;
    aabb.m_min.y = miny - ey;
    aabb.m_min.z = minz - ez;
    aabb.m_min.w = -tol;

    float maxx = (bwx < awx) ? awx : bwx;
    float maxy = (bwy < awy) ? awy : bwy;
    float maxz = (bwz < awz) ? awz : bwz;
    aabb.m_max.x = maxx + ex;
    aabb.m_max.y = maxy + ey;
    aabb.m_max.z = maxz + ez;
    aabb.m_max.w = tol;
}
