// Slice s01101c00 -- Havok 3.1 hkMoppObbVirtualMachine public query entry points.
//
//   0x01101c00  hkMoppObbVirtualMachine::queryObb(const hkMoppCode*, const hkTransform&,
//                                                 const hkVector4& extent, float radius,
//                                                 hkArray<hkMoppPrimitiveInfo>*)    (648 B)
//   0x01101e90  hkMoppObbVirtualMachine::queryAabb(const hkMoppCode*, const hkAabb&,
//                                                  hkArray<hkMoppPrimitiveInfo>*)     (310 B)
//
// Both convert a world-space query shape into the integer cell bounds the MOPP virtual
// machine works in, publish them on the VM (m_hi = the rounding-up bounds at 0x10/0x14/0x18,
// m_lo = the rounding-down bounds at 0x20/0x24/0x28) and then hand a small hkMoppObbState
// (the six bounds' high halves plus a zeroed origin/scratch tail) to the recursive bytecode
// walker at 0x011014d0 (hkMoppObbVirtualMachine::queryObb in the s01100cf0 reconstruction;
// called queryObbRecurse here to keep the name unambiguous inside this one translation unit).
//
//   cell = (world - code->m_offset) * code->m_scale, low bound = cell - 1, high bound = cell + 1
//   queryAabb: world = aabb.m_min / aabb.m_max
//   queryObb : world = transform.m_translation -+ extent_i, where the extent of the OBB along
//              axis a is sum_c |extent_c * transform column c row a| + radius
//   hkMoppObbState.m_hi[a] = (m_hi[a] >> 16) + 1,  m_lo[a] = m_lo[a] >> 16
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /vc71 (Havok was built with VC7.1; the original is
// x87 throughout and has no EH frame). The original converts float->int with a bare round-to-
// nearest `fistp dword`, which no VS2008/VC7.1 source form reproduces (a plain `(int)` calls
// `_ftol2`, which truncates); ToInt() below uses the cvtsd2si intrinsic, whose MXCSR rounding
// matches the original's nearest-rounding behaviour, at the cost of different bytes.
#include "types.h"
#include <math.h>
#include <emmintrin.h>

typedef unsigned int hkUint32;

struct hkVector4 { float x, y, z, w; };

struct hkMoppPrimitiveInfo {
    hkUint32 m_id;
    hkUint32 m_data[3];
};

template <class T>
struct hkArray {
    T*   m_data;
    int  m_size;
    int  m_capacityAndFlags;
};

// The compiled MOPP code: object header, the quantization origin (12 bytes), the world->cell
// scale and the byte stream.
struct hkMoppCode {
    char                 m_pad000[0x10];
    float                m_offsetX;    // 0x10  quantization origin
    float                m_offsetY;    // 0x14
    float                m_offsetZ;    // 0x18
    float                m_scale;      // 0x1c  world -> cell scale
    const unsigned char* m_data;       // 0x20  MOPP byte stream
};

struct hkAabb { hkVector4 m_min; hkVector4 m_max; };

// Column-major basis (column c = the c-th world axis in local space, row 3 unpacked) plus the
// translation. Element (row a, column c) lives at m_col[c][a] == m_cols[4c + a].
struct hkTransform {
    float     m_col0[4];      // 0x00
    float     m_col1[4];      // 0x10
    float     m_col2[4];      // 0x20
    hkVector4 m_translation;  // 0x30
};

// The query state handed to the recursive walker: the packed cell range, the origin the
// walker accumulates and its scratch tail.
struct hkMoppObbState {
    int m_hi[3];       // 0x00  (m_hi >> 16) + 1 per axis
    int m_pad0c;       // 0x0c  unused
    int m_lo[3];       // 0x10  m_lo >> 16 per axis
    int m_pad1c;       // 0x1c  unused
    int m_org[3];      // 0x20  quantized origin, starts at 0
    int m_primOffset;  // 0x2c  starts at 0
    int m_shift;       // 0x30  starts at 0
    int m_reg[4];      // 0x34  scratch (only m_reg[0] is initialized)
};

// Round-to-nearest float -> int with the original's x87 `fistp dword` semantics: both the x87
// fistp and cvtsd2si round per the round-to-nearest control word, where a plain `(int)` would
// truncate. The intrinsic also gives the function its 16-byte aligned frame.
static __forceinline int ToInt(float f)
{
    return _mm_cvtsd_si32(_mm_set_sd(f));
}

struct hkMoppObbVirtualMachine {
    hkArray<hkMoppPrimitiveInfo>* m_primitives;  // 0x00  output array
    int                           m_pad04[3];
    int                           m_hi[3];       // 0x10  rounding-up cell bounds
    int                           m_pad1c;
    int                           m_lo[3];       // 0x20  rounding-down cell bounds
    char                          m_pad2c[4];
    const hkMoppCode*             m_code;        // 0x30  code being queried

    // The recursive MOPP bytecode walker (thiscall, callee pops its 2 arguments).
    void queryObbRecurse(const hkMoppObbState* state, const unsigned char* p);  // 0x011014d0

    // 0x01101c00
    void queryObb(const hkMoppCode* code, const hkTransform& transform, const hkVector4& extent,
                  float radius, hkArray<hkMoppPrimitiveInfo>* primitives);

    // 0x01101e90
    void queryAabb(const hkMoppCode* code, const hkAabb& aabb,
                   hkArray<hkMoppPrimitiveInfo>* primitives);
};

// @ 0x01101c00
// A transformed box (transform, half extents, sphere radius) quantized to cell bounds: the
// world extent of the box along axis a / axis b / axis c is the absolute column sum
// sum_c |extent_c * m_col_c| plus the radius, and the world centre is the translation.
void hkMoppObbVirtualMachine::queryObb(const hkMoppCode* code, const hkTransform& transform,
                                       const hkVector4& extent, float radius,
                                       hkArray<hkMoppPrimitiveInfo>* primitives)
{
    m_primitives = primitives;
    m_code = code;

    float hx = extent.x;
    float hy = extent.y;
    float hz = extent.z;
    float ex = ((fabsf(hy * transform.m_col1[0]) + fabsf(hx * transform.m_col0[0]))
                + fabsf(hz * transform.m_col2[0])) + radius;
    float ey = ((fabsf(hy * transform.m_col1[1]) + fabsf(hx * transform.m_col0[1]))
                + fabsf(hz * transform.m_col2[1])) + radius;
    float ez = ((fabsf(hy * transform.m_col1[2]) + fabsf(hx * transform.m_col0[2]))
                + fabsf(hz * transform.m_col2[2])) + radius;

    float tx = transform.m_translation.x;
    float ty = transform.m_translation.y;
    float tz = transform.m_translation.z;

    m_lo[0] = ToInt(((tx - ex) - code->m_offsetX) * code->m_scale) - 1;
    m_hi[0] = ToInt(((tx + ex) - code->m_offsetX) * code->m_scale) + 1;
    m_lo[1] = ToInt(((ty - ey) - code->m_offsetY) * code->m_scale) - 1;
    m_hi[1] = ToInt(((ty + ey) - code->m_offsetY) * code->m_scale) + 1;
    m_lo[2] = ToInt(((tz - ez) - code->m_offsetZ) * code->m_scale) - 1;
    m_hi[2] = ToInt(((tz + ez) - code->m_offsetZ) * code->m_scale) + 1;

    hkMoppObbState state;
    state.m_hi[0] = (m_hi[0] >> 16) + 1;
    state.m_hi[1] = (m_hi[1] >> 16) + 1;
    state.m_hi[2] = (m_hi[2] >> 16) + 1;
    state.m_lo[0] = m_lo[0] >> 16;
    state.m_lo[1] = m_lo[1] >> 16;
    state.m_lo[2] = m_lo[2] >> 16;
    state.m_org[0] = 0;
    state.m_org[1] = 0;
    state.m_org[2] = 0;
    state.m_primOffset = 0;
    state.m_shift = 0;
    state.m_reg[0] = 0;

    queryObbRecurse(&state, code->m_data);
}

// @ 0x01101e90
// An axis-aligned box quantized to cell bounds (min corner rounding down, max corner rounding
// up, so the query always covers the input box).
void hkMoppObbVirtualMachine::queryAabb(const hkMoppCode* code, const hkAabb& aabb,
                                        hkArray<hkMoppPrimitiveInfo>* primitives)
{
    m_primitives = primitives;
    m_code = code;

    m_lo[0] = ToInt((aabb.m_min.x - code->m_offsetX) * code->m_scale) - 1;
    m_hi[0] = ToInt((aabb.m_max.x - code->m_offsetX) * code->m_scale) + 1;
    m_lo[1] = ToInt((aabb.m_min.y - code->m_offsetY) * code->m_scale) - 1;
    m_hi[1] = ToInt((aabb.m_max.y - code->m_offsetY) * code->m_scale) + 1;
    m_lo[2] = ToInt((aabb.m_min.z - code->m_offsetZ) * code->m_scale) - 1;
    m_hi[2] = ToInt((aabb.m_max.z - code->m_offsetZ) * code->m_scale) + 1;

    hkMoppObbState state;
    state.m_hi[0] = (m_hi[0] >> 16) + 1;
    state.m_hi[1] = (m_hi[1] >> 16) + 1;
    state.m_hi[2] = (m_hi[2] >> 16) + 1;
    state.m_lo[0] = m_lo[0] >> 16;
    state.m_lo[1] = m_lo[1] >> 16;
    state.m_lo[2] = m_lo[2] >> 16;
    state.m_org[0] = 0;
    state.m_org[1] = 0;
    state.m_org[2] = 0;
    state.m_primOffset = 0;
    state.m_shift = 0;
    state.m_reg[0] = 0;

    queryObbRecurse(&state, code->m_data);
}