// Slice s01108460 -- Havok 3.1 hkBoxBoxUtils / hkBoxBoxCollisionDetection helpers,
// linked into SporeApp.exe from a Havok 3.1.0 dev build (VC .NET 2003, cl 13.10.3077).
//
//   0x01108460  hkBoxBoxUtils  (static, register-ABI inline helper: build section bit)
//   0x011084f0  hkBoxBoxUtils  (static, register-ABI inline helper: build selected bit)
//   0x01108550  hkBoxBoxUtils  (register-ABI inline helper: fill both bitsets + classify)
//   0x01108660  hkBoxBoxUtils::cmpAllGT3(const hkVector4&, const hkReal&, int&)
//   0x011086a0  hkBoxBoxUtils::rsqrtAll3(hkVector4&)
//   0x011086f0  hkBoxBoxUtils::selectIfGT3(hkVector4&, const hkReal&, const hkVector4&, const hkReal&)
//   0x01108750  hkBoxBoxUtils  (register-ABI inline helper: pack two vectors' signs)
//   0x011088b0  hkBoxBoxUtils  (register-ABI inline helper: pack one vector's signs)
//   0x01108940  hkBoxBoxCollisionDetection::faceAVertexBValidationDataFromFeatureId
//   0x01108a10  hkBoxBoxCollisionDetection::faceAVertexBContactPointFromFeaturePointCache
//   0x01108b80  hkBoxBoxCollisionDetection::faceBVertexAContactPointFromFeaturePointCache
//   0x01108c30  hkBoxBoxCollisionDetection::edgeEdgeContactPointFromFeaturePointCache
//   0x01108d00  hkBoxBoxCollisionDetection::tryToAddPointFaceA
//
// Built /vc71 /O2 /MD /Gy /EHsc /TP.  The three *Utils helpers and the two sign
// packers use the whole-program (LTCG) register convention picked by the dev build
// (arguments in eax/ebx/esi/edi, no standard x86 convention), so their retail bytes
// are not reachable from ordinary C; the hkBoxBoxUtils leaf maths and the transform
// methods are ordinary cdecl/thiscall and are reconstructed verbatim.
#define _USE_MATH_DEFINES
#include <math.h>
#include "types.h"

typedef float hkReal;

struct __declspec(align(16)) hkVector4 {
    hkReal x, y, z, w;
};

struct hkMatrix3 {
    hkVector4 c0, c1, c2;
};

struct hkTransform {
    hkVector4 c0, c1, c2;   // basis columns
    hkVector4 t;            // translation
};

// ---- hkBoxBoxUtils: the leaf maths and the register-ABI inline helpers --------------

// 8-entry axis mask table at 0x014a5ef0 (components are 0.0f/1.0f).
static const hkVector4 g_axisMask[8] = {
    { 1.0f, 1.0f, 1.0f, 0.0f },
    { 1.0f, 1.0f, 0.0f, 1.0f },
    { 1.0f, 0.0f, 1.0f, 1.0f },
    { 0.0f, 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f, 1.0f },
};

// Set bit k of *bits when bit k+1 is clear (test-and-set of the next free slot).
static void hkSetBitIfClear(unsigned int* bits, unsigned int bit)
{
    if ((*bits & (bit << 1)) == 0)
        *bits |= bit;
}

// 0x01108460 -- for n=0,1,2 skip that section; set the section's free bit in *bits.
// @ 0x1108460
void buildSectionBits(unsigned int value, unsigned int* bits, int n)
{
    const unsigned int t = value >> 4;
    const unsigned int b1 = (~(t >> 1)) & 1u;
    const unsigned int b2 = (~(t >> 2)) & 1u;
    const unsigned int b3 = (~(t >> 3)) & 1u;
    if (n != 0)
        hkSetBitIfClear(bits, 1u << (2 * b2 + 4 * b1));
    if (n != 1)
        hkSetBitIfClear(bits, 1u << (2 * b3 + 4 * b1 + 8));
    if (n != 2)
        hkSetBitIfClear(bits, 1u << (2 * b3 + 4 * b2 + 16));
}

// 0x011084f0 -- set the one free bit selected by the low nibble of value.
// @ 0x11084f0
void buildSelectedBit(unsigned int value, unsigned int* bits)
{
    const unsigned int t = value >> 4;
    const unsigned int b1 = (~(t >> 1)) & 1u;
    const unsigned int b2 = (~(t >> 2)) & 1u;
    const unsigned int b3 = (~(t >> 3)) & 1u;
    const unsigned int sel = value & 0xf;
    unsigned int k;
    if (sel == 0)
        k = 2 * b2 + 4 * b1;
    else if (sel == 1)
        k = 2 * b3 + 4 * b1 + 8;
    else
        k = 2 * b3 + 4 * b2 + 16;
    hkSetBitIfClear(bits, 1u << k);
}

// 0x01108550 -- walk a 4-byte-record table (class@+0, feature@+1), fill two bitsets
// (classes <=2 via buildSectionBits, classes 3..6 via buildSelectedBit, higher via
// buildSelectedBit twice) and set the "valid" byte at +0x22.
struct hkFeaturePointList {
    uint8_t  m_rec[1];    // variable: record[i].class@+4*i, .feature@+4*i+1
    uint8_t  pad20;
    uint8_t  m_count;     // +0x21  number of records
    uint8_t  m_valid;     // +0x22
};
// @ 0x1108550
void hkFeatureBits(unsigned int* bitsLo, unsigned int* bitsHi,
                          unsigned int count, hkFeaturePointList* list)
{
    (void)count;
    unsigned int a = 0, b = 0;
    for (unsigned int i = 0; i < list->m_count; ++i) {
        const unsigned int cls = list->m_rec[i * 4];
        const unsigned int val = list->m_rec[i * 4 + 1];
        if (cls <= 2)
            buildSectionBits(val, bitsHi, (int)cls);
        else if (cls <= 6)
            buildSectionBits(val, bitsLo, (int)cls - 3);
        else {
            buildSelectedBit(cls, bitsLo);
            buildSelectedBit(val, bitsHi);
        }
    }
    a = *bitsLo;
    b = *bitsHi;
    list->m_valid = (uint8_t)(!((a & 0x555555u) || (b & 0x555555u)) ? 0 : 1);
    (void)a; (void)b;
}

// 0x01108660 -- mask = OR over the three components of (v > r).
// @ 0x1108660
void cmpAllGT3(const hkVector4& v, const hkReal& r, int& mask)
{
    mask = ((v.x > r) || (v.y > r) || (v.z > r)) ? 1 : 0;
}

// 0x011086a0 -- v.xyz = 1/sqrt(v.xyz + FLT_EPSILON); v.w = 0.
// @ 0x11086a0
void rsqrtAll3(hkVector4& v)
{
    v.x = 1.0f / sqrtf(v.x + 1.192092896e-07f);
    v.y = 1.0f / sqrtf(v.y + 1.192092896e-07f);
    v.z = 1.0f / sqrtf(v.z + 1.192092896e-07f);
    v.w = 0.0f;
}

// 0x011086f0 -- v.i = (scale.i > bound) ? limit : v.i.
// @ 0x11086f0
void selectIfGT3(hkVector4& v, const hkReal& limit, const hkVector4& scale, const hkReal& bound)
{
    v.x = (scale.x > bound) ? limit : v.x;
    v.y = (scale.y > bound) ? limit : v.y;
    v.z = (scale.z > bound) ? limit : v.z;
}

// 0x01108750 -- pack the sign (>=0) of eight components (a then b) plus two nibbles
// into two bytes at *out.
struct hkSignBytes {
    uint8_t m_lo;
    uint8_t m_hi;
};
// @ 0x1108750
void hkPackSigns2(hkSignBytes* out, const hkVector4& a, const hkVector4& b,
                         int loSel, int hiSel)
{
    hkVector4 av = a;
    hkVector4 bv = b;
    (&av.x)[loSel] = 1.0f;
    (&bv.x)[hiSel] = 1.0f;
    const unsigned int sa = ((av.x >= 0.0f) ? 8u : 0u) | ((av.y >= 0.0f) ? 4u : 0u)
                          | ((av.z >= 0.0f) ? 2u : 0u) | ((av.w >= 0.0f) ? 1u : 0u);
    const unsigned int sb = ((bv.x >= 0.0f) ? 8u : 0u) | ((bv.y >= 0.0f) ? 4u : 0u)
                          | ((bv.z >= 0.0f) ? 2u : 0u) | ((bv.w >= 0.0f) ? 1u : 0u);
    out->m_lo = (uint8_t)(((sa & 0xe) << 4) | (uint8_t)loSel);
    out->m_hi = (uint8_t)((((~sb) & 0xe) << 4) + (uint8_t)hiSel);
}

// 0x011088b0 -- pack the sign (>=0) of the four components of v plus (arg >> 28) & 8.
// @ 0x11088b0
int hkPackSigns1(const hkVector4& v, unsigned int hiBits)
{
    const unsigned int s = ((v.x >= 0.0f) ? 8u : 0u) | ((v.y >= 0.0f) ? 4u : 0u)
                         | ((v.z >= 0.0f) ? 2u : 0u) | ((v.w >= 0.0f) ? 1u : 0u);
    return (int)((s & 0xe0) | ((hiBits >> 28) & 8u));
}

// ---- hkBoxBoxCollisionDetection: the manifold helpers -------------------------------

struct hkFeatureContactPoint {
    uint8_t  m_id;        // +0x00
    uint8_t  m_feature;   // +0x01
    uint16_t m_axis;      // +0x02
};

struct hkFeaturePointCache {
    hkVector4 m_v0;       // +0x00
    hkVector4 m_v1;       // +0x10
    hkVector4 m_v2;       // +0x20
    hkReal   m_w30;       // +0x30  stored as +/-1.0f
    uint32_t m_d34;       // +0x34
    uint32_t m_d38;       // +0x38  feature id
    uint32_t m_d3c;
};

struct hkProcessCdPoint {
    hkVector4 m_position;   // +0x00
    hkVector4 m_normal;     // +0x10  (w @ +0x1c)
    uint16_t  m_d20;        // +0x20
    uint16_t  m_pad22;
};

struct hkBoxBoxManifold {
    uint8_t  m_rec[1];
    uint8_t  pad20;
    uint8_t  m_count;     // +0x21
    uint8_t  m_d22;
};

class hkBoxBoxCollisionDetection {
public:
    uint8_t            pad00[0x14];
    const hkTransform* m_wTa;          // +0x14  A's world transform
    const hkTransform* m_wTb;          // +0x18  B's world transform
    uint8_t            pad1c[4];
    hkMatrix3      m_aRb;             // +0x20  B's rotation expressed in A
    hkVector4      m_aTb;             // +0x50  B's origin expressed in A
    hkVector4      m_radiusA;         // +0x60
    hkVector4      m_radiusB;         // +0x70
    hkVector4      pad80;
    hkVector4      m_boundaryTol;     // +0x90

    void faceAVertexBValidationDataFromFeatureId(hkFeaturePointCache& out,
                                                 const hkFeatureContactPoint& cp);        // 0x01108940
    void faceBVertexAValidationDataFromFeatureId(hkFeaturePointCache& out,
                                                 const hkFeatureContactPoint& cp);        // 0x01108ac0
    void faceAVertexBContactPointFromFeaturePointCache(hkProcessCdPoint& out,
                                                       const hkFeatureContactPoint& cp,
                                                       const hkFeaturePointCache& cache);  // 0x01108a10
    void faceBVertexAContactPointFromFeaturePointCache(hkProcessCdPoint& out,
                                                       const hkFeatureContactPoint& cp,
                                                       const hkFeaturePointCache& cache);  // 0x01108b80
    void edgeEdgeContactPointFromFeaturePointCache(hkProcessCdPoint& out,
                                                   const hkFeatureContactPoint& cp,
                                                   const hkFeaturePointCache& cache);      // 0x01108c30
    void tryToAddPointFaceA(hkBoxBoxManifold& manifold, hkFeatureContactPoint cp,
                            unsigned short a, hkReal tol);                                    // 0x01108d00
};

// 0x01108ac0 -- B-vertex-in-A validation data: local point = radiusA * axis mask,
// world point = aRb^T * (local - aTb), with w sign/feature bytes packed.
// @ 0x1108ac0
void hkBoxBoxCollisionDetection::faceBVertexAValidationDataFromFeatureId(
        hkFeaturePointCache& out, const hkFeatureContactPoint& cp)
{
    out.m_d38 = cp.m_id;
    unsigned int wbits = 0x3f800000u | ((unsigned int)(cp.m_feature & 0xf8) << 28);
    out.m_w30 = *(hkReal*)&wbits;

    const hkVector4& mask = g_axisMask[(cp.m_feature >> 1) & 7];
    hkVector4 a;
    a.x = m_radiusA.x * mask.x;
    a.y = m_radiusA.y * mask.y;
    a.z = m_radiusA.z * mask.z;
    a.w = m_radiusA.w * mask.w;
    out.m_v0 = a;

    hkVector4 d;
    d.x = a.x - m_aTb.x;
    d.y = a.y - m_aTb.y;
    d.z = a.z - m_aTb.z;

    hkVector4 p;
    p.x = m_aRb.c0.x * d.x + m_aRb.c0.y * d.y + m_aRb.c0.z * d.z;
    p.y = m_aRb.c1.x * d.x + m_aRb.c1.y * d.y + m_aRb.c1.z * d.z;
    p.z = m_aRb.c2.x * d.x + m_aRb.c2.y * d.y + m_aRb.c2.z * d.z;
    p.w = 0.0f;
    out.m_v1 = p;
}

// 0x01108940
// @ 0x1108940
void hkBoxBoxCollisionDetection::faceAVertexBValidationDataFromFeatureId(
        hkFeaturePointCache& out, const hkFeatureContactPoint& cp)
{
    out.m_d38 = cp.m_id;
    unsigned int wbits = 0x3f800000u | ((unsigned int)(cp.m_feature & 0xf8) << 28);
    out.m_w30 = *(hkReal*)&wbits;

    const hkVector4& mask = g_axisMask[(cp.m_feature >> 1) & 7];
    hkVector4 a;
    a.x = m_radiusB.x * mask.x;
    a.y = m_radiusB.y * mask.y;
    a.z = m_radiusB.z * mask.z;
    a.w = m_radiusB.w * mask.w;
    out.m_v1 = a;

    hkVector4 p;
    p.x = m_aRb.c0.x * a.x + m_aRb.c1.x * a.y + m_aRb.c2.x * a.z + m_aTb.x;
    p.y = m_aRb.c0.y * a.x + m_aRb.c1.y * a.y + m_aRb.c2.y * a.z + m_aTb.y;
    p.z = m_aRb.c0.z * a.x + m_aRb.c1.z * a.y + m_aRb.c2.z * a.z + m_aTb.z;
    p.w = 0.0f;
    out.m_v0 = p;
}

// 0x01108a10
// @ 0x1108a10
void hkBoxBoxCollisionDetection::faceAVertexBContactPointFromFeaturePointCache(
        hkProcessCdPoint& out, const hkFeatureContactPoint& cp, const hkFeaturePointCache& cache)
{
    out.m_d20 = cp.m_axis;
    const hkVector4& a = cache.m_v1;
    const unsigned int rows = *(const unsigned int*)&cache.m_w30;
    const unsigned int off = (unsigned int)((float)rows * 0.0f);
    (void)off;

    const hkVector4* t = (const hkVector4*)&cache.m_w30;
    out.m_position.x = m_aRb.c0.x * t[0].x + m_aRb.c1.x * t[0].y + m_aRb.c2.x * t[0].z + m_aTb.x;
    out.m_position.y = m_aRb.c0.y * t[0].x + m_aRb.c1.y * t[0].y + m_aRb.c2.y * t[0].z + m_aTb.y;
    out.m_position.z = m_aRb.c0.z * t[0].x + m_aRb.c1.z * t[0].y + m_aRb.c2.z * t[0].z + m_aTb.z;
    out.m_position.w = 0.0f;

    out.m_normal.x = m_aRb.c0.x * a.x + m_aRb.c1.x * a.y + m_aRb.c2.x * a.z + m_aTb.x;
    out.m_normal.y = m_aRb.c0.y * a.x + m_aRb.c1.y * a.y + m_aRb.c2.y * a.z + m_aTb.y;
    out.m_normal.z = m_aRb.c0.z * a.x + m_aRb.c1.z * a.y + m_aRb.c2.z * a.z + m_aTb.z;
    out.m_normal.w = 0.0f;
}

// 0x01108b80
// @ 0x1108b80
void hkBoxBoxCollisionDetection::faceBVertexAContactPointFromFeaturePointCache(
        hkProcessCdPoint& out, const hkFeatureContactPoint& cp, const hkFeaturePointCache& cache)
{
    out.m_d20 = cp.m_axis;
    const hkVector4& a = cache.m_v1;
    const int bucket = (int)cache.m_d38 - 4;

    out.m_position.x = m_aRb.c0.x * a.x + m_aRb.c1.x * a.y + m_aRb.c2.x * a.z + m_aTb.x;
    out.m_position.y = m_aRb.c0.y * a.x + m_aRb.c1.y * a.y + m_aRb.c2.y * a.z + m_aTb.y;
    out.m_position.z = m_aRb.c0.z * a.x + m_aRb.c1.z * a.y + m_aRb.c2.z * a.z + m_aTb.z;
    out.m_position.w = 0.0f;

    const hkVector4* t = (const hkVector4*)&cache.m_w30;
    out.m_normal.x = m_aRb.c0.x * t[bucket].x + m_aRb.c1.x * t[bucket].y + m_aRb.c2.x * t[bucket].z + m_aTb.x;
    out.m_normal.y = m_aRb.c0.y * t[bucket].x + m_aRb.c1.y * t[bucket].y + m_aRb.c2.y * t[bucket].z + m_aTb.y;
    out.m_normal.z = m_aRb.c0.z * t[bucket].x + m_aRb.c1.z * t[bucket].y + m_aRb.c2.z * t[bucket].z + m_aTb.z;
    out.m_normal.w = 0.0f;
}

// 0x01108c30
// @ 0x1108c30
void hkBoxBoxCollisionDetection::edgeEdgeContactPointFromFeaturePointCache(
        hkProcessCdPoint& out, const hkFeatureContactPoint& cp, const hkFeaturePointCache& cache)
{
    out.m_d20 = cp.m_axis;
    const hkTransform& ta = *m_wTa;
    const hkVector4& v0 = cache.m_v0;

    out.m_position.x = ta.c0.x * v0.x + ta.c1.x * v0.y + ta.c2.x * v0.z + ta.t.x;
    out.m_position.y = ta.c0.y * v0.x + ta.c1.y * v0.y + ta.c2.y * v0.z + ta.t.y;
    out.m_position.z = ta.c0.z * v0.x + ta.c1.z * v0.y + ta.c2.z * v0.z + ta.t.z;
    out.m_position.w = 0.0f;

    const hkVector4& v2 = cache.m_v2;
    out.m_normal.x = ta.c0.x * v2.x + ta.c1.x * v2.y + ta.c2.x * v2.z;
    out.m_normal.y = ta.c0.y * v2.x + ta.c1.y * v2.y + ta.c2.y * v2.z;
    out.m_normal.z = ta.c0.z * v2.x + ta.c1.z * v2.y + ta.c2.z * v2.z;
    out.m_normal.w = 0.0f;
    *(uint32_t*)&out.m_normal.w = cache.m_d34;
}

// 0x01108d00
// @ 0x1108d00
void hkBoxBoxCollisionDetection::tryToAddPointFaceA(hkBoxBoxManifold& manifold,
                                                    hkFeatureContactPoint cp,
                                                    unsigned short a, hkReal tol)
{
    hkFeaturePointCache cache;
    faceAVertexBValidationDataFromFeatureId(cache, cp);
    const hkReal ax = fabsf(cache.m_v0.x);
    const hkReal ay = fabsf(cache.m_v0.y);
    const hkReal az = fabsf(cache.m_v0.z);
    const hkReal aw = fabsf(cache.m_v0.w);
    if (ax > m_boundaryTol.x || ay > m_boundaryTol.y
        || az > m_boundaryTol.z || aw > m_boundaryTol.w)
        return;
    const unsigned int count = manifold.m_count;
    manifold.m_rec[count * 4 + 0] = cp.m_id;
    manifold.m_rec[count * 4 + 1] = cp.m_feature;
    manifold.m_rec[count * 4 + 2] = (uint8_t)(a & 0xff);
    manifold.m_rec[count * 4 + 3] = (uint8_t)(tol != 0.0f);
    manifold.m_count = (uint8_t)(count + 1);
}
