// Slice s010b0b50 -- hkPoweredChain_BuildConstraintMatrixAndLuDecomposition (Havok 3.1 powered-chain
// solver, 0x010b0b50).
//
// The powered-chain solver treats the chain as a block-tridiagonal system: for each chain constraint i
// it builds the 6x6 block J_i M^-1 J_i^T (diagonal block, matrix m_m3) and the coupling block
// J_i M^-1 J_(i+1)^T with the next constraint through their shared body (m_m4, zero for the last
// constraint), with each constraint's three linear rows (hkp1Lin2AngJacobian) and three angular motor
// rows (hkp2AngJacobian). The diagonal gets the chain's CFM (m_cfmLinMul/Add, m_cfmAngMul/Add). Then
// the per-row LU decomposition helper factors the system row by row.
//
// Flags: /O2 /MD /Gy /TP (no /fp:fast: the sums below are written in the original's evaluation order).
// Module: Havok prebuilt library (x87, 16-byte aligned frame). Same hkVector4/hkMatrix3/hkMatrix6
// inline helpers as slice s010af750.
#include "types.h"

#define HK_FORCE_INLINE __forceinline

typedef float hkReal;
typedef unsigned char hkUint8;

struct hkBool {
    char m_bool;
};

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
    HK_FORCE_INLINE hkReal& operator()(int i) { return (&x)[i]; }
    HK_FORCE_INLINE const hkReal& operator()(int i) const { return (&x)[i]; }
    HK_FORCE_INLINE void setZero4() { x = y = z = w = 0; }
    HK_FORCE_INLINE void add4(const hkVector4& v) { x += v.x; y += v.y; z += v.z; w += v.w; }
    HK_FORCE_INLINE void setAdd4(const hkVector4& a, const hkVector4& b) {
        x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; w = a.w + b.w;
    }
    HK_FORCE_INLINE void setSub4(const hkVector4& a, const hkVector4& b) {
        x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w;
    }
    HK_FORCE_INLINE void mul4(const hkVector4& a) { x *= a.x; y *= a.y; z *= a.z; w *= a.w; }
    HK_FORCE_INLINE void setMul4(const hkVector4& a, const hkVector4& b) {
        x = a.x * b.x; y = a.y * b.y; z = a.z * b.z; w = a.w * b.w;
    }
    HK_FORCE_INLINE void setMul4(hkReal r, const hkVector4& a) {
        x = r * a.x; y = r * a.y; z = r * a.z; w = r * a.w;
    }
    HK_FORCE_INLINE hkReal horizontalAdd3() const { return (z + y) + x; }
};

class hkMatrix3 {
public:
    hkVector4 m_col0;
    hkVector4 m_col1;
    hkVector4 m_col2;
    HK_FORCE_INLINE hkReal& operator()(int row, int col) { return (&m_col0)[col](row); }
    HK_FORCE_INLINE const hkReal& operator()(int row, int col) const { return (&m_col0)[col](row); }
    HK_FORCE_INLINE void setZero() {
        hkVector4 zero; zero.setZero4();
        m_col0 = zero;
        m_col1 = zero;
        m_col2 = zero;
    }
    // Transpose of the 3x3 part; the w components of the columns become zero.
    HK_FORCE_INLINE void setTranspose(const hkMatrix3& s) {
        (*this)(0, 0) = s(0, 0);
        (*this)(1, 1) = s(1, 1);
        (*this)(2, 2) = s(2, 2);
        m_col0.w = 0;
        m_col1.w = 0;
        m_col2.w = 0;
        (*this)(1, 0) = s(0, 1);
        (*this)(0, 1) = s(1, 0);
        (*this)(2, 0) = s(0, 2);
        (*this)(0, 2) = s(2, 0);
        (*this)(2, 1) = s(1, 2);
        (*this)(1, 2) = s(2, 1);
    }
};

class hkMatrix6 {
public:
    hkMatrix3 m_m[2][2];   // [row][column]
    HK_FORCE_INLINE void setZero() {
        m_m[0][0].setZero();
        m_m[0][1].setZero();
        m_m[1][0].setZero();
        m_m[1][1].setZero();
    }
};

// Velocity accumulator of a body (only the field used here).
struct hkVelocityAccumulator {
    hkVector4 m_pad00[3];
    hkVector4 m_invMasses;          // +0x30: inverse inertia (xyz), inverse mass (w)
};

// Linear constraint row: linear Jacobian (body B uses its negation) plus the angular Jacobians.
struct hkp1Lin2AngJacobian {
    hkVector4 m_linear0;            // +0x00
    hkVector4 m_angular[2];         // +0x10, +0x20
};

// Angular (motor) constraint row.
struct hkp2AngJacobian {
    hkVector4 m_angular[2];         // +0x00, +0x10
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

// hkpPoweredChainData's constraint force mixing parameters.
struct hkPoweredChainCfm {
    hkReal m_cfmLinAdd;
    hkReal m_cfmLinMul;
    hkReal m_cfmAngAdd;
    hkReal m_cfmAngMul;
};

extern "C" void hkPoweredChain_ComputeConstraintMatrixLuDecomposition_ForOneRow(
    hkBool notLastRow, hkPoweredChainConstraintMatrices* matrices, hkPoweredChainMotorInfo* motorInfo,
    hkMatrix6* prevOffDiagonal, hkMatrix6** prevOffDiagonalPtr);

// The element helpers below spell out where the original rounds to float. The Havok library keeps some
// partial products/sums in x87 registers (extended precision) and spills others to float temporaries;
// a named hkReal local is a rounded float here (/fp:precise), a sub-expression stays unrounded.

// One element of J_a M^-1 J_b^T for two angular Jacobians through a single body.
static HK_FORCE_INLINE hkReal angularDot(const hkVector4& a, const hkVector4& b, const hkVector4& invMasses)
{
    hkReal pz = a.z * b.z;
    hkReal px = (a.x * b.x) * invMasses.x;
    return ((pz * invMasses.z) + (a.y * b.y) * invMasses.y) + px;
}

// One element of J_a M^-1 J_b^T for two angular rows acting on bodies A and B.
static HK_FORCE_INLINE hkReal angularDot2(const hkVector4& aA, const hkVector4& bA, const hkVector4& aB,
                                          const hkVector4& bB, const hkVector4& invA, const hkVector4& invB)
{
    hkReal pAz = aA.z * bA.z;
    hkReal pBx = aB.x * bB.x;
    hkReal pBy = aB.y * bB.y;
    hkReal pBz = aB.z * bB.z;
    hkReal qAx = (aA.x * bA.x) * invA.x;
    hkReal qBz = pBz * invB.z;
    hkReal sx = pBx * invB.x + qAx;
    hkReal sy = pBy * invB.y + (aA.y * bA.y) * invA.y;
    return ((qBz + pAz * invA.z) + sy) + sx;
}

// One element of J_a M^-1 J_b^T for two linear rows (linear part through both bodies' inverse masses).
static HK_FORCE_INLINE hkReal linearDot2(const hkp1Lin2AngJacobian& a, const hkp1Lin2AngJacobian& b,
                                         const hkVector4& invA, const hkVector4& invB)
{
    hkReal lz = a.m_linear0.z * b.m_linear0.z;
    hkReal pAx = a.m_angular[0].x * b.m_angular[0].x;
    hkReal pAy = a.m_angular[0].y * b.m_angular[0].y;
    hkReal pAz = a.m_angular[0].z * b.m_angular[0].z;
    hkReal pBx = a.m_angular[1].x * b.m_angular[1].x;
    hkReal pBy = a.m_angular[1].y * b.m_angular[1].y;
    hkReal pBz = a.m_angular[1].z * b.m_angular[1].z;
    hkReal wA = invA.w;
    hkReal wB = invB.w;
    hkReal lAx = wA * (a.m_linear0.x * b.m_linear0.x);
    hkReal lAy = wA * (a.m_linear0.y * b.m_linear0.y);
    hkReal lAz = wA * lz;
    hkReal lBx = wB * (a.m_linear0.x * b.m_linear0.x);
    pAx = pAx * invA.x; pAy = pAy * invA.y; pAz = pAz * invA.z;
    pBx = pBx * invB.x; pBy = pBy * invB.y; pBz = pBz * invB.z;
    hkReal sx = lBx + lAx;
    hkReal sy = (a.m_linear0.y * b.m_linear0.y) * wB + lAy;
    hkReal az = pBz + pAz;
    sx = sx + (pBx + pAx);
    sy = sy + (pBy + pAy);
    return (((lz * wB + lAz) + az) + sy) + sx;
}

// One element of the coupling block for two linear rows through the shared body (whose linear
// Jacobian enters with opposite signs).
static HK_FORCE_INLINE hkReal linearCoupling(const hkp1Lin2AngJacobian& a, const hkp1Lin2AngJacobian& b,
                                             const hkVector4& inv)
{
    hkReal lz = a.m_linear0.z * b.m_linear0.z;
    hkReal px = a.m_angular[1].x * b.m_angular[0].x;
    hkReal py = a.m_angular[1].y * b.m_angular[0].y;
    hkReal pz = a.m_angular[1].z * b.m_angular[0].z;
    hkReal w = inv.w;
    hkReal tx = w * (a.m_linear0.x * b.m_linear0.x);
    pz = pz * inv.z;
    hkReal sx = px * inv.x - tx;
    hkReal sy = py * inv.y - (a.m_linear0.y * b.m_linear0.y) * w;
    return ((pz - lz * w) + sy) + sx;
}

// @ 0x010b0b50
extern "C" void hkPoweredChain_BuildConstraintMatrixAndLuDecomposition(
    int numConstraints, const hkPoweredChainCfm* cfm, hkPoweredChainMotorInfo* motorInfos,
    const hkp1Lin2AngJacobian* linJacs, const hkp2AngJacobian* angJacs, const int* accumulatorOffsets,
    const char* accumulatorsBase, hkPoweredChainConstraintMatrices* matrices)
{
    hkMatrix6 prevOffDiagonal;
    prevOffDiagonal.setZero();
    hkMatrix6* prevOffDiagonalPtr = &prevOffDiagonal;

    for (int i = 0; i < numConstraints; i++) {
        const hkp1Lin2AngJacobian* lin = linJacs + i * 3;
        const hkp2AngJacobian* ang = angJacs + i * 3;
        hkMatrix6& diag = matrices[i].m_m3;

        // Diagonal block, symmetric 3x3 parts.
        for (int j = 0; j < 3; j++) {
            for (int k = j; k < 3; k++) {
                const hkVelocityAccumulator* accA =
                    (const hkVelocityAccumulator*)(accumulatorsBase + accumulatorOffsets[i]);
                const hkVelocityAccumulator* accB =
                    (const hkVelocityAccumulator*)(accumulatorsBase + accumulatorOffsets[i + 1]);
                hkReal v = linearDot2(lin[k], lin[j], accA->m_invMasses, accB->m_invMasses);
                diag.m_m[0][0](j, k) = v;
                diag.m_m[0][0](k, j) = v;
                hkReal va = angularDot2(ang[k].m_angular[0], ang[j].m_angular[0], ang[k].m_angular[1],
                                        ang[j].m_angular[1], accA->m_invMasses, accB->m_invMasses);
                diag.m_m[1][1](j, k) = va;
                diag.m_m[1][1](k, j) = va;
            }
            diag.m_m[0][0](j, j) = cfm->m_cfmLinMul * diag.m_m[0][0](j, j);
            diag.m_m[1][1](j, j) = cfm->m_cfmAngMul * diag.m_m[1][1](j, j);
            diag.m_m[0][0](j, j) = diag.m_m[0][0](j, j) + cfm->m_cfmLinAdd;
            diag.m_m[1][1](j, j) = cfm->m_cfmAngAdd + diag.m_m[1][1](j, j);
        }

        // Angular rows x linear rows; the upper right block is its transpose.
        for (int k = 0; k < 3; k++) {
            for (int r = 0; r < 3; r++) {
                const hkVelocityAccumulator* accA =
                    (const hkVelocityAccumulator*)(accumulatorsBase + accumulatorOffsets[i]);
                const hkVelocityAccumulator* accB =
                    (const hkVelocityAccumulator*)(accumulatorsBase + accumulatorOffsets[i + 1]);
                diag.m_m[1][0](k, r) = angularDot2(ang[k].m_angular[0], lin[r].m_angular[0], ang[k].m_angular[1],
                                                   lin[r].m_angular[1], accA->m_invMasses, accB->m_invMasses);
            }
        }
        diag.m_m[0][1].setTranspose(diag.m_m[1][0]);

        // Coupling with the next constraint through the shared body.
        hkMatrix6& offDiag = matrices[i].m_m4;
        if (i < numConstraints - 1) {
            const hkp1Lin2AngJacobian* linNext = lin + 3;
            const hkp2AngJacobian* angNext = ang + 3;
            for (int r = 0; r < 3; r++) {
                for (int k = 0; k < 3; k++) {
                    const hkVelocityAccumulator* acc =
                        (const hkVelocityAccumulator*)(accumulatorsBase + accumulatorOffsets[i + 1]);
                    offDiag.m_m[0][0](r, k) = linearCoupling(lin[r], linNext[k], acc->m_invMasses);
                    offDiag.m_m[1][1](r, k) =
                        angularDot(ang[r].m_angular[1], angNext[k].m_angular[0], acc->m_invMasses);
                    offDiag.m_m[0][1](r, k) =
                        angularDot(lin[r].m_angular[1], angNext[k].m_angular[0], acc->m_invMasses);
                    offDiag.m_m[1][0](r, k) =
                        angularDot(ang[r].m_angular[1], linNext[k].m_angular[0], acc->m_invMasses);
                }
            }
        } else {
            offDiag.setZero();
        }
    }

    for (int i = 0; i < numConstraints; i++) {
        hkBool notLast;
        notLast.m_bool = (char)(i != numConstraints - 1);
        hkPoweredChain_ComputeConstraintMatrixLuDecomposition_ForOneRow(
            notLast, &matrices[i], &motorInfos[i], &prevOffDiagonal, &prevOffDiagonalPtr);
    }
}
