// Slice s010ad3b0 -- hkPoweredChain_ComputeConstraintMatrixLuDecomposition_ForOneRow (Havok 3.1 powered-chain
// solver, 0x010ad3b0, cdecl).
//
// One step of the block-tridiagonal LU decomposition of the chain's 6x6 constraint matrices. Per row i
// (constraint matrices m_m0..m_m4, see hkPoweredChain_BuildConstraintMatrixAndLuDecomposition 0x010b0b50):
//   a = copy of m_m3 (diagonal block), b = copy of m_m4 (coupling to the next constraint);
//   rows of disabled motors are replaced in a/b (0x010ad1c0) and removed from the previous coupling
//   block (0x010ad2d0);
//   m_m0 = transpose(prevOffDiagonal); m_m1 = a - m_m0 * (*prevOffDiagonalPtr);
//   the six diagonal entries of m_m1 are clamped to at least FLT_EPSILON;
//   m_m1 = inverse(m_m1); m_m2 = m_m1 * b;
//   the next row's "previous off-diagonal" is m_m4 and its pointer is m_m2.
//
// Flags: /O2 /MD /Gy /TP (Havok prebuilt library: x87, 16-byte aligned frame because of hkVector4).
#include "types.h"

typedef float hkReal;
typedef unsigned char hkUint8;

struct hkBool {
    char m_bool;
};

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
    hkReal& operator()(int i) { return (&x)[i]; }
    const hkReal& operator()(int i) const { return (&x)[i]; }
};

class hkMatrix3 {
public:
    hkVector4 m_col0;
    hkVector4 m_col1;
    hkVector4 m_col2;
    hkReal& operator()(int row, int col) { return (&m_col0)[col](row); }
    const hkReal& operator()(int row, int col) const { return (&m_col0)[col](row); }
    __forceinline void operator=(const hkMatrix3& a) {
        m_col0 = a.m_col0;
        m_col1 = a.m_col1;
        m_col2 = a.m_col2;
    }
};

class hkMatrix6 {
public:
    hkMatrix3 m_m[2][2];   // [row][column]
    hkMatrix6() {}
    hkMatrix6(const hkMatrix6& o);                 // 0x010ad140, out-of-line copy (thiscall ret 4)
    __forceinline void operator=(const hkMatrix6& a) {
        m_m[0][0] = a.m_m[0][0];
        m_m[0][1] = a.m_m[0][1];
        m_m[1][0] = a.m_m[1][0];
        m_m[1][1] = a.m_m[1][1];
    }
};

// Five 6x6 blocks per constraint of the block-tridiagonal LU decomposition.
struct hkPoweredChainConstraintMatrices {
    hkMatrix6 m_m0;
    hkMatrix6 m_m1;
    hkMatrix6 m_m2;
    hkMatrix6 m_m3;     // +0x240: J_i M^-1 J_i^T (+ CFM)
    hkMatrix6 m_m4;     // +0x300: J_i M^-1 J_(i+1)^T
};

struct hkPoweredChainMotorInfo {    // 0x4c bytes
    hkUint8 m_motorStates;
    hkUint8 m_pad[0x4b];
};

extern "C" {
void hkMatrix6SetTranspose(hkMatrix6* out, const hkMatrix6* in);             // 0x0120b1b0
void hkMatrix6SetMul(hkMatrix6* out, const hkMatrix6* a, const hkMatrix6* b);  // 0x0120b0a0
void hkMatrix6Sub(hkMatrix6* a, const hkMatrix6* b);                         // 0x0120ae50
void hkMatrix6SetInvert(hkMatrix6* out, const hkMatrix6* in);                // 0x0120b880
void hkPoweredChain_DisableMotorInMatrixRow_NextConstraint(hkPoweredChainMotorInfo* motorInfo,
                                                           hkMatrix6* prevOffDiagonal);   // 0x010ad2d0
// 0x010ad1c0: motor-state dependent rewrite of the two copies (identity row for a disabled motor).
void hkPoweredChain_ApplyMotorStatesToRows(hkPoweredChainMotorInfo* motorInfo, hkBool notLastRow,
                                           hkMatrix6* a, hkMatrix6* b);

void hkPoweredChain_ComputeConstraintMatrixLuDecomposition_ForOneRow(
    hkBool notLastRow, hkPoweredChainConstraintMatrices* matrices, hkPoweredChainMotorInfo* motorInfo,
    hkMatrix6* prevOffDiagonal, hkMatrix6** prevOffDiagonalPtr);
}

extern hkReal HK_REAL_EPSILON;      // 0x014a23c4 (FLT_EPSILON)

extern "C" void hkPoweredChain_ComputeConstraintMatrixLuDecomposition_ForOneRow(
    hkBool notLastRow, hkPoweredChainConstraintMatrices* matrices, hkPoweredChainMotorInfo* motorInfo,
    hkMatrix6* prevOffDiagonal, hkMatrix6** prevOffDiagonalPtr)
{
    hkMatrix6 a(matrices->m_m3);
    hkMatrix6 b(matrices->m_m4);
    hkPoweredChain_ApplyMotorStatesToRows(motorInfo, notLastRow, &a, &b);
    hkPoweredChain_DisableMotorInMatrixRow_NextConstraint(motorInfo, prevOffDiagonal);

    hkMatrix6SetTranspose(&matrices->m_m0, prevOffDiagonal);

    hkMatrix6 product;
    hkMatrix6SetMul(&product, &matrices->m_m0, *prevOffDiagonalPtr);

    matrices->m_m1 = a;
    hkMatrix6Sub(&matrices->m_m1, &product);

    hkMatrix6& m1 = matrices->m_m1;
    if (!(m1.m_m[0][0](0, 0) > HK_REAL_EPSILON)) m1.m_m[0][0](0, 0) = HK_REAL_EPSILON;
    if (!(m1.m_m[1][1](0, 0) > HK_REAL_EPSILON)) m1.m_m[1][1](0, 0) = HK_REAL_EPSILON;
    if (!(m1.m_m[0][0](1, 1) > HK_REAL_EPSILON)) m1.m_m[0][0](1, 1) = HK_REAL_EPSILON;
    if (!(m1.m_m[1][1](1, 1) > HK_REAL_EPSILON)) m1.m_m[1][1](1, 1) = HK_REAL_EPSILON;
    if (!(m1.m_m[0][0](2, 2) > HK_REAL_EPSILON)) m1.m_m[0][0](2, 2) = HK_REAL_EPSILON;
    if (!(m1.m_m[1][1](2, 2) > HK_REAL_EPSILON)) m1.m_m[1][1](2, 2) = HK_REAL_EPSILON;

    hkMatrix6 copy;
    copy = matrices->m_m1;
    hkMatrix6SetInvert(&matrices->m_m1, &copy);
    hkMatrix6SetMul(&matrices->m_m2, &matrices->m_m1, &b);

    *prevOffDiagonal = matrices->m_m4;
    *prevOffDiagonalPtr = &matrices->m_m2;
}
