// Slice s010e86c0 -- Havok height-field AABB build + forwarding ray collector.
//
//  010e86c0  hkSampledHeightFieldShape::getAabb(const hkTransform&, float, hkAabb&) const
//  010e8830  hkForwardingRayCollector::addRayHit(const hkCdBody&, const hkShapeRayCastOutput&)
//
// Frozen batch gold5.  32-bit x86, MSVC 2008 SP1, flags
// /O2 /MD /Gy /TP /arch:SSE /fp:fast (default /GS on).

#include "types.h"

class hkTransform;
class hkAabb;
class hkCdBody;
struct hkShapeRayCastOutput;

// 16-byte aligned 4-float vector; the alignment is what forces getAabb's
// "and esp, 0xfffffff0" frame.
struct __declspec(align(16)) hkVector4 {
    float x, y, z, w;
};

// ---------------------------------------------------------------------------
// The sampled height-field shape.  Slot 9 (+0x24) of the vtable is the height
// sampler; slot 10 (+0x28) is this getAabb override.
// ---------------------------------------------------------------------------
struct hkSampledHeightFieldShape {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual float getHeight(int x, int z) const;                             // vtbl +0x24
    virtual void getAabb(const hkTransform& localToWorld, float tolerance,
                         hkAabb& out) const;                                 // vtbl +0x28

    uint8_t pad04[0x0c - 0x04];
    int     m_xRes;             // +0x0c  (row count)
    int     m_zRes;             // +0x10  (column count)
    mutable float m_heightCenter;     // +0x14  (cached by the const getAabb)
    uint8_t pad18[0x24 - 0x18];
    float   m_scale;            // +0x24
    uint8_t pad28[0x50 - 0x28];
    float   m_ext0;             // +0x50
    mutable float m_ext1;             // +0x54  (cached by the const getAabb)
    float   m_ext2;             // +0x58
    float   m_ext3;             // +0x5c
};

// hkAabbUtil::calcAabb -- packs (transform, centre, extents, tolerance) into out.
extern "C" void FUN_010c16b0(const hkTransform& localToWorld, const hkVector4& center,
                             const hkVector4& extents, float tolerance, hkAabb& out);

// ---------------------------------------------------------------------------
// @ 0x010e86c0
// ---------------------------------------------------------------------------
void hkSampledHeightFieldShape::getAabb(const hkTransform& localToWorld, float tolerance,
                                        hkAabb& out) const
{
    float lo;
    float hi;
    hkVector4 center;
    hkVector4 extents;

    lo = getHeight(0, 0);
    hi = lo;

    if (0.0f > m_ext1) {
        int i = 0;
        if (0 < m_xRes) {
            do {
                int j = 0;
                if (0 < m_zRes) {
                    do {
                        float h = getHeight(i, j);
                        if (h < lo) lo = h;
                        if (h > hi) hi = h;
                        j++;
                    } while (j < m_zRes);
                }
                i++;
            } while (i < m_xRes);
        }

        float a = lo * m_scale;
        hi = hi * m_scale;
        lo = a;
        if (a >= hi) lo = hi;
        if (a > hi) hi = a;
        m_heightCenter = (lo + hi) * 0.5f;
        m_ext1 = hi - lo;
    }

    center.x = m_ext0 * 0.5f;
    center.y = m_ext1 * 0.5f;
    center.z = m_ext2 * 0.5f;
    center.w = m_ext3 * 0.5f;
    extents = center;
    center.y = m_heightCenter;

    FUN_010c16b0(localToWorld, center, extents, tolerance, out);
}

// ---------------------------------------------------------------------------
// The forwarding collector that receives the ray hit.
// ---------------------------------------------------------------------------
struct Collector {
    void FUN_00b501a0(const hkShapeRayCastOutput& out);
};

struct hkShapeRayCastOutput {
    uint8_t pad00[0x14];
    float   m_hitFraction;      // +0x14
};

struct hkForwardingRayCollector {
    virtual void addRayHit(const hkCdBody& body, const hkShapeRayCastOutput& out);

    float       m_bestFraction;     // +0x04
    uint8_t     m_hasHit;           // +0x08
    uint8_t     pad09[0x03];
    Collector*  m_collector;        // +0x0c
};

// ---------------------------------------------------------------------------
// @ 0x010e8830
// ---------------------------------------------------------------------------
void hkForwardingRayCollector::addRayHit(const hkCdBody& body, const hkShapeRayCastOutput& out)
{
    if (m_bestFraction > out.m_hitFraction) {
        // Raw 4-byte copy of the float (MSVC folds float->float assignments into an
        // integer move when the value is not otherwise needed on the x87 stack).
        *(int*)&m_bestFraction = *(const int*)&out.m_hitFraction;
        m_collector->FUN_00b501a0(out);
        m_hasHit = 1;
    }
}
