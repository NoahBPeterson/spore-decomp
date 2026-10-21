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
    hkUint8 m_motorStates;
    hkUint8 m_pad[0x4b];
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
