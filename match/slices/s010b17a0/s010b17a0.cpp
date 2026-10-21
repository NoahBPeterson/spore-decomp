// Slice s010b17a0 -- Havok 3.1.0 powered-chain solver (0x010b17a0..0x010b1d70).
//   _hkPoweredChain_UpdateLuDecomposition                   0x010b17a0
//   _hkPoweredChainBuildJacobian                            0x010b1bf0
//   hk2Lin2AngJacobian::next / hkJacobian*ChainSchema::getEnd  0x010b1d00..0x010b1d50
//   powered-chain jacobian evaluator                       0x010b1d70
// Flags: /vc71 /O2 /MD /Gy /TP (Havok 3.1.0 is cl 13.10; x87 codegen).
#include "types.h"

typedef float hkReal;
typedef unsigned char hkUint8;
typedef unsigned short hkUint16;
typedef unsigned int hkUint32;

struct hkBool {
    char m_bool;
};

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
    __forceinline hkReal& operator()(int i) { return (&x)[i]; }
    __forceinline const hkReal& operator()(int i) const { return (&x)[i]; }
    __forceinline hkVector4& operator=(const hkVector4& o) {
        x = o.x; y = o.y; z = o.z; w = o.w; return *this;
    }
};

// ---- jacobian elements --------------------------------------------------------------------------------------------
// The "JacobianElement" a schema hands out is an opaque 0x40-byte struct; the schema stores a compressed
// element description (type byte + size word) followed by the linear data it references.
struct hkJacobianElement {
    hkUint32 m_raw[0x40 / 4];
};

// 3 linear + 2 angular ranks (hkp1Lin2AngJacobian): one linear Jacobian (0x10) and two angular (0x10 each).
struct hkp1Lin2AngJacobian {
    hkVector4 m_linear0;            // +0x00
    hkVector4 m_angular[2];         // +0x10, +0x20
};

// 2 angular ranks (hkp2AngJacobian).
struct hkp2AngJacobian {
    hkVector4 m_angular[2];         // +0x00, +0x10
};

// 2 linear + 2 angular ranks (hkp2Lin2AngJacobian): 0x40 bytes.
struct hkp2Lin2AngJacobian {
    hkVector4 m_linear[2];          // +0x00, +0x10
    hkVector4 m_angular[2];         // +0x20, +0x30
    hkJacobianElement* next(int i); // 0x010b1d00
};

// ---- chain schemas ------------------------------------------------------------------------------------------------
// Each schema keeps the element count at a fixed offset and the compressed element stream right after its
// own header. getEnd returns the first 16-byte-aligned address past the last element.
struct hkJacobianStiffSpringChainSchema {
    hkUint32 m_pad0;                // +0x00
    int m_numElements;              // +0x04
    hkUint8 m_elements_0x08[0x13 - 0x08];
    hkJacobianElement* getEnd(hkJacobianElement* start);   // 0x010b1d10
};

struct hkJacobianBallSocketChainSchema {
    hkUint32 m_pad0;                // +0x00
    int m_numElements;              // +0x04
    hkUint8 m_elements_0x08[0x10 - 0x08];
    hkJacobianElement* getEnd(hkJacobianElement* start);   // 0x010b1d30
};

struct hkJacobianPoweredChainSchema {
    hkUint32 m_pad0;                // +0x00
    hkUint32 m_pad4;                // +0x04
    int m_numElements;              // +0x08
    hkUint8 m_elements_0x0c[0x20 - 0x0c];
    hkJacobianElement* getEnd(hkJacobianElement* start);   // 0x010b1d50
};

// ---- 6x6 block matrices of the powered-chain solver ------------------------------------------------------------------
class hkMatrix3 {
public:
    hkVector4 m_col0;
    hkVector4 m_col1;
    hkVector4 m_col2;      // 0x30 bytes
    __forceinline hkMatrix3& operator=(const hkMatrix3& o) {
        m_col0 = o.m_col0; m_col1 = o.m_col1; m_col2 = o.m_col2; return *this;
    }
};
class hkMatrix6 {
public:
    hkMatrix3 m_m[2][2];   // [row][column], 0xc0 bytes
    __forceinline void setZero() {
        hkVector4 z;
        z.x = 0; z.y = 0; z.z = 0; z.w = 0;
        m_m[0][0].m_col0 = z; m_m[0][0].m_col1 = z; m_m[0][0].m_col2 = z;
        m_m[0][1].m_col0 = z; m_m[0][1].m_col1 = z; m_m[0][1].m_col2 = z;
        m_m[1][0].m_col0 = z; m_m[1][0].m_col1 = z; m_m[1][0].m_col2 = z;
        m_m[1][1].m_col0 = z; m_m[1][1].m_col1 = z; m_m[1][1].m_col2 = z;
    }
};

// Five 6x6 blocks per constraint of the block-tridiagonal LU decomposition (0x3c0 bytes).
struct hkPoweredChainConstraintMatrices {
    hkMatrix6 m_m0;     // +0x000
    hkMatrix6 m_m1;     // +0x0c0
    hkMatrix6 m_m2;     // +0x180
    hkMatrix6 m_m3;     // +0x240
    hkMatrix6 m_m4;     // +0x300
};

struct hkPoweredChainMotorInfo {    // 0x4c bytes
    hkUint32 m_raw[0x4c / 4];
};

extern "C" void hkPoweredChain_ComputeConstraintMatrixLuDecomposition_ForOneRow(
    hkBool notLastRow, hkPoweredChainConstraintMatrices* matrices, hkPoweredChainMotorInfo* motorInfo,
    hkMatrix6* prevOffDiagonal, hkMatrix6** prevOffDiagonalPtr);   // 0x010ad3b0

// @ 0x010b17a0
extern "C" void hkPoweredChain_UpdateLuDecomposition(
    int numConstraints, int numToProcess, hkPoweredChainMotorInfo* motorInfos,
    hkPoweredChainConstraintMatrices* matrices)
{
    int start = numConstraints - 1;
    if (start < 0)
        start = 0;

    hkMatrix6 prevOffDiagonal;
    hkMatrix6* prevOffDiagonalPtr;
    if (start == 0) {
        prevOffDiagonal.setZero();
        prevOffDiagonalPtr = &prevOffDiagonal;
    } else {
        const hkMatrix6& src = matrices[start - 1].m_m4;
        prevOffDiagonal.m_m[0][0] = src.m_m[0][0];
        prevOffDiagonal.m_m[0][1] = src.m_m[0][1];
        prevOffDiagonal.m_m[1][0] = src.m_m[1][0];
        prevOffDiagonal.m_m[1][1] = src.m_m[1][1];
        prevOffDiagonalPtr = &matrices[start - 1].m_m2;
    }

    for (int i = start; i < numToProcess; i++) {
        hkBool notLast;
        notLast.m_bool = (i != numToProcess - 1) ? 1 : 0;
        hkPoweredChain_ComputeConstraintMatrixLuDecomposition_ForOneRow(
            notLast, &matrices[i], &motorInfos[i], &prevOffDiagonal, &prevOffDiagonalPtr);
    }
}

// ---- build-jacobian spec + output cache header -----------------------------------------------------------------------
struct hkPoweredChainBuildJacobianSpec {
    int m_numConstraints;            // +0x00
    float m_field04;                 // +0x04
    float m_field08;                 // +0x08
    hkUint32 m_field0c;              // +0x0c  (linJacs base = &m_field0c)
    hkUint32 m_pad10[3];             // +0x10..0x1b
    hkUint32* m_elementSource;       // +0x1c
    void* m_cfm;                     // +0x20
    hkPoweredChainMotorInfo* m_motorInfos;  // +0x24
    hkUint32 m_field28;              // +0x28
    hkUint32 m_field2c;              // +0x2c
    const char* m_accumulatorBase;   // +0x30
};

struct hkPoweredChainCacheHeader {
    hkUint32 m_sizeAndType;          // +0x00
    hkUint32 m_field04;              // +0x04
    hkUint32 m_numConstraints;       // +0x08
    hkUint32 m_field0c;              // +0x0c
    float    m_f10;                  // +0x10
    float    m_f14;                  // +0x14
    // element data follows at +0x18
};

extern "C" void hkPoweredChain_BuildConstraintMatrixAndLuDecomposition(int numConstraints, const void* linJacs, void* motorInfos, const void* accumulatorOffsets, const void* angJacs, void* matrices, const void* cfm, const void* accumulatorsBase, int stride);  // 0x010b0b50

// @ 0x010b1bf0
extern "C" void hkPoweredChainBuildJacobian(const hkPoweredChainBuildJacobianSpec* spec, int* out)
{
    int numConstraints = spec->m_numConstraints;
    hkPoweredChainCacheHeader* hdr = (hkPoweredChainCacheHeader*)out[1];
    hkUint32* src1 = spec->m_elementSource;
    hkUint32* dst;

    hdr->m_f10 = spec->m_field04;
    hdr->m_field04 = spec->m_field2c;
    hdr->m_f14 = spec->m_field08;
    hdr->m_sizeAndType = ((hkUint32)(numConstraints * 0x13 + 6 + (numConstraints + 1)) << 0x12) | 0xc19;
    hdr->m_numConstraints = numConstraints;

    dst = (hkUint32*)(hdr + 1);
    int c = numConstraints + 1;
    if (c > 0) {
        do { *dst++ = *src1++; } while (--c != 0);
    }

    char* dst2 = (char*)hdr + 0x1c + numConstraints * 4;
    const char* src2 = (const char*)spec->m_motorInfos;
    int n = numConstraints;
    if (n > 0) {
        do {
            *(hkPoweredChainMotorInfo*)dst2 = *(const hkPoweredChainMotorInfo*)src2;
            dst2 += 0x4c;
            src2 += 0x4c;
        } while (--n != 0);
    }

    hdr->m_field0c = spec->m_field28;
    hdr->m_field04 = spec->m_field2c;
    hkPoweredChain_BuildConstraintMatrixAndLuDecomposition(
        numConstraints, &spec->m_field0c, spec->m_motorInfos, spec->m_accumulatorBase,
        spec->m_accumulatorBase + numConstraints * 0x90, (char*)hdr + 0x18, spec->m_cfm,
        (const void*)out[0], numConstraints * 0x3c0);

    out[0] = out[0] + numConstraints * 0x400 + 0x20;
    out[1] = out[1] + *(hkUint16*)((char*)hdr + 2);
}

// @ 0x010b1d00
hkJacobianElement* hkp2Lin2AngJacobian::next(int i)
{
    return (hkJacobianElement*)((char*)this + i * 0x40);
}

// @ 0x010b1d10
hkJacobianElement* hkJacobianStiffSpringChainSchema::getEnd(hkJacobianElement* start)
{
    return (hkJacobianElement*)(((int)start + m_numElements * 0x40 + 0x13) & ~0xf);
}

// @ 0x010b1d30
hkJacobianElement* hkJacobianBallSocketChainSchema::getEnd(hkJacobianElement* start)
{
    return (hkJacobianElement*)((char*)start + m_numElements * 0x130 + 0x10);
}

// @ 0x010b1d50
hkJacobianElement* hkJacobianPoweredChainSchema::getEnd(hkJacobianElement* start)
{
    return (hkJacobianElement*)((char*)start + m_numElements * 0x4f0 + 0x20);
}

// ---- powered-chain jacobian evaluator -------------------------------------------------------------------------------
// Walks the compressed element stream of a chain constraint and writes the relative-velocity rows of the
// constraint's Jacobian into `out` (at most `limit` rows). Each type byte selects how much linear data the
// element consumes from the M block and how many output rows it produces.
struct hkJacobianStream {
    int m_field0;    // +0x00
    int m_dataM;     // +0x04
    int m_dataA;     // +0x08
    int m_dataB;     // +0x0c
    int m_field10;   // +0x10
    int m_field14;   // +0x14
    // the compressed element stream begins at +0x18
};

// Relative-velocity row for one linear Jacobian: (A-B) applied to the body's linear/angular Jacobians in M.
static __forceinline float jacLinearRow(const float* A, const float* B, const float* M)
{
    return (((A[6] - B[6]) * M[2] + (B[10] * M[10] + A[10] * M[6])) +
            ((A[4] - B[4]) * M[0] + (B[8] * M[8] + A[8] * M[4]))) +
           ((A[5] - B[5]) * M[1] + (B[9] * M[9] + A[9] * M[5]));
}

// Second row of a two-row element, using the following M block.
static __forceinline float jacLinearRow2(const float* A, const float* B, const float* M)
{
    return (((A[6] - B[6]) * M[0xe] + (B[10] * M[0x16] + A[10] * M[0x12])) +
            ((A[5] - B[5]) * M[0xd] + (B[9] * M[0x15] + A[9] * M[0x11]))) +
           ((A[4] - B[4]) * M[0xc] + (B[8] * M[0x14] + A[8] * M[0x10]));
}

// @ 0x010b1d70
extern "C" int hkPoweredChain_JacobiBuild(int dummy, const hkJacobianStream* jac, int offsetA,
                                          int offsetM, int limit, float* out)
{
    const float* A = (const float*)(jac->m_dataA + offsetA);
    const float* B = (const float*)(jac->m_dataB + offsetA);
    const char* M = (const char*)(jac->m_dataM + offsetM);
    const char* pos = (const char*)jac + 0x18;
    int dc = 0;
    int d8 = 1;
    int d4 = 2;

    for (;;) {
        int type;
        while ((type = *(const signed char*)pos) > 0x14)
            pos++;

        switch (type) {
        case 0:
        case 1:
        case 9:
        case 10:
            return dc;
        case 2:
            break;
        case 3:
        case 19:
        case 20:
            pos += *(const hkUint16*)(pos + 2);
            break;
        case 4: {
            if (d8 > limit)
                return dc;
            dc++; d4++; d8++;
            float v = jacLinearRow(A, B, (const float*)M);
            if (0.0f < v) v = 0.0f;
            *out = v;
            out++;
            M += 0x30;
            pos += *(const hkUint16*)(pos + 2);
            break;
        }
        case 5: {
            if (d4 > limit)
                return dc;
            dc += 2; d4 += 2; d8 += 2;
            float v0 = jacLinearRow(A, B, (const float*)M);
            if (0.0f < v0) v0 = 0.0f;
            *out = v0;
            float v1 = jacLinearRow2(A, B, (const float*)M);
            if (0.0f < v1) v1 = 0.0f;
            out[1] = v1;
            out += 2;
            M += 0x60;
            pos += *(const hkUint16*)(pos + 2);
            break;
        }
        case 6:
        case 11:
        case 12:
            do {
                pos += *(const hkUint16*)(pos + 2);
                M += 0x20;
            } while (*(const signed char*)pos == type);
            break;
        case 7:
        case 8:
        case 13:
            do {
                pos += *(const hkUint16*)(pos + 2);
                M += 0x30;
            } while (*(const signed char*)pos == type);
            break;
        case 14:
            pos += *(const hkUint16*)(pos + 2);
            M += 0x20;
            break;
        case 15:
        case 16: {
            if (d8 > limit)
                return dc;
            dc++; d4++; d8++;
            *out = jacLinearRow(A, B, (const float*)M);
            out++;
            M += 0x30;
            pos += *(const hkUint16*)(pos + 2);
            break;
        }
        case 17:
            pos += *(const hkUint16*)(pos + 2);
            M += 0x20;
            break;
        case 18:
            pos += *(const hkUint16*)(pos + 2);
            M += 0x10;
            break;
        }
    }
}
