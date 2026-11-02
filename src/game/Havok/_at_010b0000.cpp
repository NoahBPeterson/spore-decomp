// src/game/Havok/_at_010b0000.cpp -- migrated from slice(s) s010b48b0, s010b3b20, s010b2890, s010b22a0, s010b17a0, s010b0b50 by tools/migrate/rewrite.py
// Object file: Havok/_at_010b0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>

// ---- items of slice s010b0b50 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define HK_FORCE_INLINE __forceinline
typedef float hkReal;
typedef unsigned char hkUint8;
class hkBool_s010b_0b50 { public:
    char m_bool;
};
class __declspec(align(16)) hkVector4_s010b_0b50 {
public:
    hkReal x, y, z, w;
    HK_FORCE_INLINE hkReal& operator()(int i) { return (&x)[i]; }
    HK_FORCE_INLINE const hkReal& operator()(int i) const { return (&x)[i]; }
    HK_FORCE_INLINE void setZero4() { x = y = z = w = 0; }
    HK_FORCE_INLINE void add4(const hkVector4_s010b_0b50& v) { x += v.x; y += v.y; z += v.z; w += v.w; }
    HK_FORCE_INLINE void setAdd4(const hkVector4_s010b_0b50& a, const hkVector4_s010b_0b50& b) {
        x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; w = a.w + b.w;
    }
    HK_FORCE_INLINE void setSub4(const hkVector4_s010b_0b50& a, const hkVector4_s010b_0b50& b) {
        x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w;
    }
    HK_FORCE_INLINE void mul4(const hkVector4_s010b_0b50& a) { x *= a.x; y *= a.y; z *= a.z; w *= a.w; }
    HK_FORCE_INLINE void setMul4(const hkVector4_s010b_0b50& a, const hkVector4_s010b_0b50& b) {
        x = a.x * b.x; y = a.y * b.y; z = a.z * b.z; w = a.w * b.w;
    }
    HK_FORCE_INLINE void setMul4(hkReal r, const hkVector4_s010b_0b50& a) {
        x = r * a.x; y = r * a.y; z = r * a.z; w = r * a.w;
    }
    HK_FORCE_INLINE hkReal horizontalAdd3() const { return (z + y) + x; }
};
class hkMatrix3_s010b_0b50 {
public:
    hkVector4_s010b_0b50 m_col0;
    hkVector4_s010b_0b50 m_col1;
    hkVector4_s010b_0b50 m_col2;
    HK_FORCE_INLINE hkReal& operator()(int row, int col) { return (&m_col0)[col](row); }
    HK_FORCE_INLINE const hkReal& operator()(int row, int col) const { return (&m_col0)[col](row); }
    HK_FORCE_INLINE void setZero() {
        hkVector4_s010b_0b50 zero; zero.setZero4();
        m_col0 = zero;
        m_col1 = zero;
        m_col2 = zero;
    }
    // Transpose of the 3x3 part; the w components of the columns become zero.
    HK_FORCE_INLINE void setTranspose(const hkMatrix3_s010b_0b50& s) {
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
    hkMatrix3_s010b_0b50 m_m[2][2];   // [row][column]
    HK_FORCE_INLINE void setZero() {
        m_m[0][0].setZero();
        m_m[0][1].setZero();
        m_m[1][0].setZero();
        m_m[1][1].setZero();
    }
};
class hkVelocityAccumulator { public:
    hkVector4_s010b_0b50 m_pad00[3];
    hkVector4_s010b_0b50 m_invMasses;          // +0x30: inverse inertia (xyz), inverse mass (w)
};
struct hkp1Lin2AngJacobian {
    hkVector4_s010b_0b50 m_linear0;            // +0x00
    hkVector4_s010b_0b50 m_angular[2];         // +0x10, +0x20
};
struct hkp2AngJacobian {
    hkVector4_s010b_0b50 m_angular[2];         // +0x00, +0x10
};
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
struct hkPoweredChainCfm {
    hkReal m_cfmLinAdd;
    hkReal m_cfmLinMul;
    hkReal m_cfmAngAdd;
    hkReal m_cfmAngMul;
};
extern "C" void hkPoweredChain_ComputeConstraintMatrixLuDecomposition_ForOneRow(
    hkBool_s010b_0b50 notLastRow, hkPoweredChainConstraintMatrices* matrices, hkPoweredChainMotorInfo* motorInfo,
    hkMatrix6* prevOffDiagonal, hkMatrix6** prevOffDiagonalPtr);
static HK_FORCE_INLINE hkReal angularDot(const hkVector4_s010b_0b50& a, const hkVector4_s010b_0b50& b, const hkVector4_s010b_0b50& invMasses)
{
    hkReal pz = a.z * b.z;
    hkReal px = (a.x * b.x) * invMasses.x;
    return ((pz * invMasses.z) + (a.y * b.y) * invMasses.y) + px;
}
static HK_FORCE_INLINE hkReal angularDot2(const hkVector4_s010b_0b50& aA, const hkVector4_s010b_0b50& bA, const hkVector4_s010b_0b50& aB,
                                          const hkVector4_s010b_0b50& bB, const hkVector4_s010b_0b50& invA, const hkVector4_s010b_0b50& invB)
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
static HK_FORCE_INLINE hkReal linearDot2(const hkp1Lin2AngJacobian& a, const hkp1Lin2AngJacobian& b,
                                         const hkVector4_s010b_0b50& invA, const hkVector4_s010b_0b50& invB)
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
static HK_FORCE_INLINE hkReal linearCoupling(const hkp1Lin2AngJacobian& a, const hkp1Lin2AngJacobian& b,
                                             const hkVector4_s010b_0b50& inv)
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
// ---- items of slice s010b0b50 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void hkPoweredChain_ComputeConstraintMatrixLuDecomposition_ForOneRow(
    hkBool_s010b_0b50 notLastRow, hkPoweredChainConstraintMatrices* matrices, hkPoweredChainMotorInfo* motorInfo,
    hkMatrix6* prevOffDiagonal, hkMatrix6** prevOffDiagonalPtr);

// ---- items of slice s010b17a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short hkUint16;
typedef unsigned int hkUint32;
class __declspec(align(16)) hkVector4_s010b_17a0 {
public:
    hkReal x, y, z, w;
    __forceinline hkReal& operator()(int i) { return (&x)[i]; }
    __forceinline const hkReal& operator()(int i) const { return (&x)[i]; }
    __forceinline hkVector4_s010b_17a0& operator=(const hkVector4_s010b_17a0& o) {
        x = o.x; y = o.y; z = o.z; w = o.w; return *this;
    }
};
struct hkJacobianElement {
    hkUint32 m_raw[0x40 / 4];
};
struct hkp2Lin2AngJacobian {
    hkVector4_s010b_17a0 m_linear[2];          // +0x00, +0x10
    hkVector4_s010b_17a0 m_angular[2];         // +0x20, +0x30
    hkJacobianElement* next(int i); // 0x010b1d00
};
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
struct hkPoweredChainMotorInfo_s010b_17a0 {    // 0x4c bytes
    hkUint32 m_raw[0x4c / 4];
};
struct hkPoweredChainBuildJacobianSpec {
    int m_numConstraints;            // +0x00
    float m_field04;                 // +0x04
    float m_field08;                 // +0x08
    hkUint32 m_field0c;              // +0x0c  (linJacs base = &m_field0c)
    hkUint32 m_pad10[3];             // +0x10..0x1b
    hkUint32* m_elementSource;       // +0x1c
    void* m_cfm;                     // +0x20
    hkPoweredChainMotorInfo_s010b_17a0* m_motorInfos;  // +0x24
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
extern "C" void hkPoweredChain_BuildConstraintMatrixAndLuDecomposition_s010b_17a0(int numConstraints, const void* linJacs, void* motorInfos, const void* accumulatorOffsets, const void* angJacs, void* matrices, const void* cfm, const void* accumulatorsBase, int stride);  // 0x010b0b50
struct hkJacobianStream {
    int m_field0;    // +0x00
    int m_dataM;     // +0x04
    int m_dataA;     // +0x08
    int m_dataB;     // +0x0c
    int m_field10;   // +0x10
    int m_field14;   // +0x14
    // the compressed element stream begins at +0x18
};
static __forceinline float jacLinearRow(const float* A, const float* B, const float* M)
{
    return (((A[6] - B[6]) * M[2] + (B[10] * M[10] + A[10] * M[6])) +
            ((A[4] - B[4]) * M[0] + (B[8] * M[8] + A[8] * M[4]))) +
           ((A[5] - B[5]) * M[1] + (B[9] * M[9] + A[9] * M[5]));
}
static __forceinline float jacLinearRow2(const float* A, const float* B, const float* M)
{
    return (((A[6] - B[6]) * M[0xe] + (B[10] * M[0x16] + A[10] * M[0x12])) +
            ((A[5] - B[5]) * M[0xd] + (B[9] * M[0x15] + A[9] * M[0x11]))) +
           ((A[4] - B[4]) * M[0xc] + (B[8] * M[0x14] + A[8] * M[0x10]));
}
// ---- items of slice s010b17a0 end

// ---- items of slice s010b22a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct GskVertex
{
    char   pad00[0x10];
    hkReal m_linear[3];      // +0x10 body 0 linear velocity
    hkReal m_pad1c;
    hkReal m_angular[3];     // +0x20 body 0 angular velocity
    hkReal m_pad2c;
    hkReal m_direction[3];   // +0x30 contact direction
    hkReal m_invMass;        // +0x3c
};
struct GskContactList
{
    char   pad00[0x04];
    int    m_count;          // +0x04 number of contacts
    hkReal m_weight0;        // +0x08
    hkReal m_weight1;        // +0x0c
    int    m_vertexIndex[1]; // +0x10 two vertex indices per contact
};
struct GskRow
{
    hkReal m_pad00[3];       // +0x00
    hkReal m_mass;           // +0x0c
    hkReal m_vel0[3];        // +0x10 cached velocity of the first vertex
    hkReal m_pad1c;
    hkReal m_vel1[3];        // +0x20 cached velocity of the second vertex
    hkReal m_pad2c;
    hkReal m_normal[3];      // +0x30
    hkReal m_impulse;        // +0x3c
};
struct GskSolverConfig
{
    char   pad00[0x40];
    hkReal m_invMassScale;   // +0x40
};
// ---- items of slice s010b22a0 end

// ---- items of slice s010b2890 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Solver { char pad[0x40]; float dt; };
struct Chain {
    int pad0;
    int n;
    float stiff;     // 0x08
    float damp;      // 0x0c
    int off[1];      // 0x10: body offsets, n+1 entries
};
template<int K> __forceinline void Comp(const float* pa, const float* pb, const float* a, const float* b, const float* c, float& S, float& T)
{
    S = pb[0x50 / 4 + K] * c[K] + pa[0x50 / 4 + K] * b[K] + (pa[0x40 / 4 + K] - pb[0x40 / 4 + K]) * a[K];
    T = (pb[0x20 / 4 + K] - pb[0x50 / 4 + K]) * c[K] + (pa[0x20 / 4 + K] - pa[0x50 / 4 + K]) * b[K]
      + ((pa[0x10 / 4 + K] - pa[0x40 / 4 + K]) - (pb[0x10 / 4 + K] - pb[0x40 / 4 + K])) * a[K];
}
__forceinline float FwdRow(int row, const float* A, const float* B, const float* m, const float* l, const float* v,
                           float stiff, float fV, float fU)
{
    const float* a = m + row * 12;
    const float* b = a + 4;
    const float* c = a + 8;
    float S0, T0, S1, T1, S2, T2;
    Comp<0>(A, B, a, b, c, S0, T0);
    Comp<1>(A, B, a, b, c, S1, T1);
    Comp<2>(A, B, a, b, c, S2, T2);
    return stiff * a[3]
         - (((S0 * fV + fU * T0) + (fV * S2 + fU * T2)) + (S1 * fV + fU * T1))
         - (v[0] * l[row] + (v[2] * l[8 + row] + v[1] * l[4 + row]));
}
__forceinline void BackRow(int row, float v, float* A, float* B, const float* m, float* o)
{
    const float* a = m + row * 12;
    const float* b = a + 4;
    const float* c = a + 8;
    float fa = v * A[0x3c / 4];
    float fb = v * B[0x3c / 4];
    A[0x10 / 4] = fa * a[0] + A[0x10 / 4];
    A[0x14 / 4] = fa * a[1] + A[0x14 / 4];
    A[0x18 / 4] = fa * a[2] + A[0x18 / 4];
    B[0x10 / 4] = B[0x10 / 4] - fb * a[0];
    B[0x14 / 4] = B[0x14 / 4] - fb * a[1];
    B[0x18 / 4] = B[0x18 / 4] - fb * a[2];
    A[0x20 / 4] = (v * A[0x30 / 4]) * b[0] + A[0x20 / 4];
    A[0x24 / 4] = (v * A[0x34 / 4]) * b[1] + A[0x24 / 4];
    A[0x28 / 4] = (v * A[0x38 / 4]) * b[2] + A[0x28 / 4];
    B[0x20 / 4] = (v * B[0x30 / 4]) * c[0] + B[0x20 / 4];
    B[0x24 / 4] = (v * B[0x34 / 4]) * c[1] + B[0x24 / 4];
    B[0x28 / 4] = (v * B[0x38 / 4]) * c[2] + B[0x28 / 4];
    o[row] = v + o[row];
}
// ---- items of slice s010b2890 end

// ---- items of slice s010b3b20 begin (TODO(rewrite): local stubs, replace by canonical classes)
class __declspec(align(16)) hkVector4_s010b_3b20 {
public:
    hkReal x, y, z, w;
};
class hkMatrix3_s010b_3b20 {
public:
    hkVector4_s010b_3b20 m_col0;
    hkVector4_s010b_3b20 m_col1;
    hkVector4_s010b_3b20 m_col2;
};
class hkMatrix6_s010b_3b20 {
public:
    hkMatrix3_s010b_3b20 m_m[2][2];   // [row][column]
};
class hkVector8 {
public:
    hkVector4_s010b_3b20 m_lin;
    hkVector4_s010b_3b20 m_ang;
};
class hkVelocityAccumulator_s010b_3b20 { public:
    hkVector4_s010b_3b20 m_header;     // +0x00
    hkVector4_s010b_3b20 m_linearVel;  // +0x10
    hkVector4_s010b_3b20 m_angularVel; // +0x20
    hkVector4_s010b_3b20 m_invMasses;  // +0x30 (xyz: angular inverse inertia, w: inverse mass)
};
struct hkp1Lin2AngJacobian_s010b_3b20 {
    hkVector4_s010b_3b20 m_linear0;
    hkVector4_s010b_3b20 m_angular[2];
};
struct hkp2AngJacobian_s010b_3b20 {
    hkVector4_s010b_3b20 m_angular[2];
};
struct hkPoweredChainConstraintMatrices_s010b_3b20 {
    hkMatrix6_s010b_3b20 m_m0;
    hkMatrix6_s010b_3b20 m_m1;
    hkMatrix6_s010b_3b20 m_m2;     // +0x180
    hkMatrix6_s010b_3b20 m_m3;
    hkMatrix6_s010b_3b20 m_m4;
};
struct hkPoweredChainMotorParams {
    hkReal m_pad0[2];
    hkReal m_targetVelocity;    // +0x08
    hkReal m_tau;               // +0x0c
    hkReal m_damping;           // +0x10
    hkReal m_pad14;
};
struct hkPoweredChainMotorInfo_s010b_3b20 {    // 0x4c bytes
    hkUint8 m_motorStates;          // 2 bits per motor
    hkUint8 m_pad[3];
    hkPoweredChainMotorParams m_motors[3];
};
struct hkPoweredChainSchema {
    int m_pad0[2];
    int m_numConstraints;           // +0x08
    int m_pad0c;
    hkReal m_tau;                   // +0x10
    hkReal m_damping;               // +0x14
    int m_accumulatorOffsets[1];    // +0x18 (numConstraints + 1 entries)
};
struct hkPoweredChainSolverParams;
struct hkPoweredChainSolverInfo {
    const hkPoweredChainSolverParams* m_params;         // +0x00
    int m_numConstraints;                               // +0x04
    hkReal m_tau;                                       // +0x08
    hkReal m_damping;                                   // +0x0c
    hkp1Lin2AngJacobian_s010b_3b20* m_linearJacobians;             // +0x10 (3 rows per constraint)
    hkp2AngJacobian_s010b_3b20* m_angularJacobians;                // +0x14 (3 rows per constraint)
    const int* m_accumulatorOffsets;                    // +0x18
    char* m_accumulatorsBase;                           // +0x1c
    hkPoweredChainConstraintMatrices_s010b_3b20* m_matrices;       // +0x20
    hkPoweredChainMotorInfo_s010b_3b20* m_motorInfo;               // +0x24
    hkVector8* m_velocities;                            // +0x28 (numConstraints + 1 entries)
    hkVector8* m_rhs;                                   // +0x2c
};
extern "C" void hkPoweredChain_CalculateVelocities(hkPoweredChainSolverInfo* info, hkVector8* rhs);
extern "C" void hkPoweredChain_OverwriteVelocityWithExplicitImpulse(int constraintIndex, int motorIndex,
                                                                    hkPoweredChainMotorInfo_s010b_3b20* motorInfo,
                                                                    hkVector8* rhs);
extern "C" void FUN_010aef10(hkPoweredChainSolverInfo* info, hkVector8* velocities);
extern "C" void hkPoweredChain_ScanAndEnableMotors(hkPoweredChainSolverInfo* info, int* constraintIndexOut,
                                                   int* motorIndexOut, hkReal* maxError,
                                                   hkPoweredChainMotorInfo_s010b_3b20* motorInfo);
extern "C" void hkPoweredChain_ScanAndDisableMotors(hkPoweredChainSolverInfo* info, int* constraintIndexOut,
                                                    int* motorIndexOut, hkReal* maxError,
                                                    hkPoweredChainMotorInfo_s010b_3b20* motorInfo);
extern "C" void hkPoweredChain_UpdateLuDecomposition(int constraintIndex, int numConstraints,
                                                     hkPoweredChainMotorInfo_s010b_3b20* motorInfo,
                                                     hkPoweredChainConstraintMatrices_s010b_3b20* matrices);
extern "C" void hkPoweredChain_RestoreVelocityValue(int constraintIndex, int motorIndex,
                                                    hkPoweredChainSolverInfo* info, hkVector8* rhs);
static HK_FORCE_INLINE hkReal mulRowA(const hkMatrix3_s010b_3b20& m, int k, hkReal v0, hkReal v1, hkReal v2)
{
    return ((&m.m_col1.x)[k] * v1 + (&m.m_col2.x)[k] * v2) + (&m.m_col0.x)[k] * v0;
}
static HK_FORCE_INLINE hkReal mulRowB(const hkMatrix3_s010b_3b20& m, int k, hkReal v0, hkReal v1, hkReal v2)
{
    return ((&m.m_col1.x)[k] * v1 + (&m.m_col0.x)[k] * v0) + (&m.m_col2.x)[k] * v2;
}
static HK_FORCE_INLINE void applyLinearImpulse(hkVelocityAccumulator_s010b_3b20* a, hkVelocityAccumulator_s010b_3b20* b,
                                               const hkp1Lin2AngJacobian_s010b_3b20& jac, hkReal imp)
{
    hkReal iAx = imp * a->m_invMasses.x;
    hkReal iAy = imp * a->m_invMasses.y;
    hkReal iAz = imp * a->m_invMasses.z;
    hkReal iAw = imp * a->m_invMasses.w;
    hkReal iBx = imp * b->m_invMasses.x;
    hkReal iBy = imp * b->m_invMasses.y;
    hkReal iBz = imp * b->m_invMasses.z;
    hkReal iBw = imp * b->m_invMasses.w;

    hkReal lAx = iAw * jac.m_linear0.x;
    hkReal lAy = iAw * jac.m_linear0.y;
    hkReal lAz = iAw * jac.m_linear0.z;
    hkReal lBx = iBw * jac.m_linear0.x;
    hkReal lBy = iBw * jac.m_linear0.y;
    hkReal lBz = iBw * jac.m_linear0.z;
    a->m_linearVel.x = lAx + a->m_linearVel.x;
    a->m_linearVel.y = lAy + a->m_linearVel.y;
    a->m_linearVel.z = lAz + a->m_linearVel.z;
    b->m_linearVel.x = b->m_linearVel.x - lBx;
    b->m_linearVel.y = b->m_linearVel.y - lBy;
    b->m_linearVel.z = b->m_linearVel.z - lBz;

    hkReal aAx = iAx * jac.m_angular[0].x;
    hkReal aAy = iAy * jac.m_angular[0].y;
    hkReal aAz = iAz * jac.m_angular[0].z;
    hkReal aBx = iBx * jac.m_angular[1].x;
    hkReal aBy = iBy * jac.m_angular[1].y;
    hkReal aBz = iBz * jac.m_angular[1].z;
    a->m_angularVel.x = aAx + a->m_angularVel.x;
    a->m_angularVel.y = aAy + a->m_angularVel.y;
    a->m_angularVel.z = aAz + a->m_angularVel.z;
    b->m_angularVel.x = aBx + b->m_angularVel.x;
    b->m_angularVel.y = aBy + b->m_angularVel.y;
    b->m_angularVel.z = aBz + b->m_angularVel.z;
}
static HK_FORCE_INLINE void applyAngularImpulse(hkVelocityAccumulator_s010b_3b20* a, hkVelocityAccumulator_s010b_3b20* b,
                                                const hkp2AngJacobian_s010b_3b20& jac, hkReal imp)
{
    hkReal iAx = imp * a->m_invMasses.x;
    hkReal iAy = imp * a->m_invMasses.y;
    hkReal iAz = imp * a->m_invMasses.z;
    hkReal iBx = imp * b->m_invMasses.x;
    hkReal iBy = imp * b->m_invMasses.y;
    hkReal iBz = imp * b->m_invMasses.z;

    hkReal aAx = iAx * jac.m_angular[0].x;
    hkReal aAy = iAy * jac.m_angular[0].y;
    hkReal aAz = iAz * jac.m_angular[0].z;
    hkReal aBx = iBx * jac.m_angular[1].x;
    hkReal aBy = iBy * jac.m_angular[1].y;
    hkReal aBz = iBz * jac.m_angular[1].z;
    a->m_angularVel.x = aAx + a->m_angularVel.x;
    a->m_angularVel.y = aAy + a->m_angularVel.y;
    a->m_angularVel.z = aAz + a->m_angularVel.z;
    b->m_angularVel.x = aBx + b->m_angularVel.x;
    b->m_angularVel.y = aBy + b->m_angularVel.y;
    b->m_angularVel.z = aBz + b->m_angularVel.z;
}
// ---- items of slice s010b3b20 end

// ---- items of slice s010b48b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class hkVector4_s010b_48b0 { public: float x, y, z, w; };
struct hkSolverInfo_s010b_48b0
{
    float m_one;                                  // +0x00
    float m_tau;                                  // +0x04
    float m_damping;                              // +0x08
    float m_frictionTau;                          // +0x0c
    hkVector4_s010b_48b0 m_globalAccelerationPerSubStep;     // +0x10
    hkVector4_s010b_48b0 m_globalAccelerationPerStep;        // +0x20
    hkVector4_s010b_48b0 m_integrateVelocityFactor;          // +0x30
    hkVector4_s010b_48b0 m_invIntegrateVelocityFactor;       // +0x40
    char m_rest[0x140 - 0x50];
};
class hkVelocityAccumulator_s010b_48b0
{ public:
    uint8_t m_type;                               // +0x00
    char m_pad01[0xf];
    hkVector4_s010b_48b0 m_linearVel;                        // +0x10
    hkVector4_s010b_48b0 m_angularVel;                       // +0x20
    hkVector4_s010b_48b0 m_invMasses;                        // +0x30  xyz: inverse inertia (core space), w: inverse mass
    hkVector4_s010b_48b0 m_sumLinearVel;                     // +0x40  scratch0
    hkVector4_s010b_48b0 m_sumAngularVel;                    // +0x50  scratch1
    char m_scratch23[0x20];                       // +0x60
};
struct hkJacobianElement;
struct hk1Lin2AngJacobian
{
    hkVector4_s010b_48b0 m_linear0;
    hkVector4_s010b_48b0 m_angular[2];
    hkJacobianElement* next(int n);               // 0x010aa040 (out of line)
};
struct hk2AngJacobian
{
    hkVector4_s010b_48b0 m_angular[2];
};
struct hk2Lin2AngJacobian
{
    hkVector4_s010b_48b0 m_linear[2];
    hkVector4_s010b_48b0 m_angular[2];
    hkJacobianElement* next(int n);               // 0x010b1d00 (out of line)
};
struct hkJacobianSchema                           // common 4-byte head of every schema
{
    int8_t m_type;                                // +0 (read with movsx)
    uint8_t m_pad1;
    uint16_t m_size;                              // +2 byte size, for the variable-size schemas
};
struct hkJacobianHeaderSchema : hkJacobianSchema  // type 1, 0x18 bytes
{
    int m_jacobianOffset;                         // +0x04 into the jacobian-element buffer
    int m_bodyAOffset;                            // +0x08 into the accumulator buffer
    int m_bodyBOffset;                            // +0x0c
    char m_pad10[8];
};
struct hkJacobianPairContactSchema : hkJacobianSchema    // type 5, 8 bytes
{
    float m_coupling;                             // +0x04 off-diagonal of the 2x2 inverse mass matrix
};
struct hkJacobianMotorSchema : hkJacobianSchema   // types 6/7, 0x1c bytes
{
    float m_maxImpulse;                           // +0x04
    float m_minImpulse;                           // +0x08
    float m_velocity;                             // +0x0c added to the jacobian rhs every pass
    float m_tau;                                  // +0x10
    float m_damping;                              // +0x14
    float m_impulseRatio;                         // +0x18 written when the impulse is clamped
};
struct hkJacobianFrictionSchema : hkJacobianSchema       // types 8/0xb, 0xc bytes
{
    float m_maxFrictionImpulse;                   // +0x04
    float m_frictionRatio;                        // +0x08 written when the impulse is clamped
};
struct hkJacobian2dFrictionSchema : hkJacobianSchema     // type 9 (0x18 bytes) / 10 (0x1c bytes)
{
    float m_unused04;                             // +0x04
    float m_coupling;                             // +0x08 off-diagonal of the 2x2 inverse mass matrix
    float m_maxFrictionImpulse;                   // +0x0c
    float m_frictionRatio;                        // +0x10 written when the impulse is clamped
    float m_unused14;                             // +0x14
    float m_angularFrictionFactor;                // +0x18 (type 10 only)
};
struct hkJacobianAngularLimitSchema : hkJacobianSchema   // type 0xc, 0x10 bytes
{
    float m_maxRhs;                               // +0x04
    float m_minRhs;                               // +0x08
    float m_tau;                                  // +0x0c
};
struct hkJacobianLinearLimitSchema : hkJacobianSchema    // type 0xd, 0xc bytes
{
    float m_maxRhs;                               // +0x04
    float m_minRhs;                               // +0x08
};
struct hkJacobianUserTauSchema : hkJacobianSchema // types 0x10 / 0x13, 0xc bytes
{
    float m_tau;                                  // +0x04
    float m_damping;                              // +0x08
};
struct hkJacobianStiffSpringChainSchema_s010b_48b0 : hkJacobianSchema
{
    int m_numConstraints;                         // +0x04 (one temp each)
    hkJacobianElement* getEnd(hkJacobianElement* j);     // 0x010b1d10
};
struct hkJacobianBallSocketChainSchema_s010b_48b0 : hkJacobianSchema
{
    int m_numConstraints;                         // +0x04 (three temps each)
    hkJacobianElement* getEnd(hkJacobianElement* j);     // 0x010b1d30
};
struct hkJacobianPoweredChainSchema_s010b_48b0 : hkJacobianSchema
{
    int m_pad04;
    int m_numConstraints;                         // +0x08 (six temps each)
    hkJacobianElement* getEnd(hkJacobianElement* j);     // 0x010b1d50
};
enum
{
    SCHEMA_END = 0, SCHEMA_HEADER = 1, SCHEMA_GOTO = 3,
    SCHEMA_SINGLE_CONTACT = 4, SCHEMA_PAIR_CONTACT = 5,
    SCHEMA_ANGULAR_MOTOR = 6, SCHEMA_LINEAR_MOTOR = 7, SCHEMA_LINEAR_FRICTION = 8,
    SCHEMA_2D_FRICTION = 9, SCHEMA_3D_FRICTION = 10,
    SCHEMA_ANGULAR_FRICTION = 0xb, SCHEMA_ANGULAR_LIMIT = 0xc, SCHEMA_LINEAR_LIMIT = 0xd,
    SCHEMA_ANGULAR_BILATERAL = 0xe, SCHEMA_LINEAR_BILATERAL = 0xf,
    SCHEMA_LINEAR_BILATERAL_USER_TAU = 0x10, SCHEMA_SET_MASS = 0x11, SCHEMA_ADD_VELOCITY = 0x12,
    SCHEMA_SET_TAU_AND_DAMPING = 0x13, SCHEMA_RESTORE_TAU_AND_DAMPING = 0x14, SCHEMA_PULLEY = 0x15,
    SCHEMA_STIFF_SPRING_CHAIN = 0x17, SCHEMA_BALL_SOCKET_CHAIN = 0x18, SCHEMA_POWERED_CHAIN = 0x19
};
extern "C" void hkSolveStiffSpringChain(hkSolverInfo_s010b_48b0& info, char* accumulators, hkJacobianStiffSpringChainSchema_s010b_48b0* schema,
                                        hkJacobianElement* jac, float* temp);   // 0x010b22a0
extern "C" void hkSolveBallSocketChain(hkSolverInfo_s010b_48b0& info, char* accumulators, hkJacobianBallSocketChainSchema_s010b_48b0* schema,
                                       hkJacobianElement* jac, float* temp);    // 0x010b2890
extern "C" void hkSolvePoweredChain(hkSolverInfo_s010b_48b0& info, char* accumulators, hkJacobianPoweredChainSchema_s010b_48b0* schema,
                                    hkJacobianElement* jac, float* temp);       // 0x010b3b20
static inline float getVelocity(const hk1Lin2AngJacobian& j, const hkVelocityAccumulator_s010b_48b0& a, const hkVelocityAccumulator_s010b_48b0& b)
{
    return ((a.m_linearVel.x - b.m_linearVel.x) * j.m_linear0.x + a.m_angularVel.x * j.m_angular[0].x + b.m_angularVel.x * j.m_angular[1].x)
         + ((a.m_linearVel.y - b.m_linearVel.y) * j.m_linear0.y + a.m_angularVel.y * j.m_angular[0].y + b.m_angularVel.y * j.m_angular[1].y)
         + ((a.m_linearVel.z - b.m_linearVel.z) * j.m_linear0.z + a.m_angularVel.z * j.m_angular[0].z + b.m_angularVel.z * j.m_angular[1].z);
}
static inline float getAngularVelocity(const hk2AngJacobian& j, const hkVelocityAccumulator_s010b_48b0& a, const hkVelocityAccumulator_s010b_48b0& b)
{
    return (a.m_angularVel.x * j.m_angular[0].x + b.m_angularVel.x * j.m_angular[1].x)
         + (a.m_angularVel.y * j.m_angular[0].y + b.m_angularVel.y * j.m_angular[1].y)
         + (a.m_angularVel.z * j.m_angular[0].z + b.m_angularVel.z * j.m_angular[1].z);
}
static inline float getVelocity(const hk2Lin2AngJacobian& j, const hkVelocityAccumulator_s010b_48b0& a, const hkVelocityAccumulator_s010b_48b0& b)
{
    return ((a.m_linearVel.x * j.m_linear[0].x - b.m_linearVel.x * j.m_linear[1].x) + (a.m_angularVel.x * j.m_angular[0].x + b.m_angularVel.x * j.m_angular[1].x))
         + ((a.m_linearVel.y * j.m_linear[0].y - b.m_linearVel.y * j.m_linear[1].y) + (a.m_angularVel.y * j.m_angular[0].y + b.m_angularVel.y * j.m_angular[1].y))
         + ((a.m_linearVel.z * j.m_linear[0].z - b.m_linearVel.z * j.m_linear[1].z) + (a.m_angularVel.z * j.m_angular[0].z + b.m_angularVel.z * j.m_angular[1].z));
}
static inline float getUserTauVelocity(const hk1Lin2AngJacobian& j, const hkVelocityAccumulator_s010b_48b0& a, const hkVelocityAccumulator_s010b_48b0& b,
                                       float tauFactor, float dampFactor)
{
    const float sx = (a.m_sumLinearVel.x - b.m_sumLinearVel.x) * j.m_linear0.x + a.m_sumAngularVel.x * j.m_angular[0].x + b.m_sumAngularVel.x * j.m_angular[1].x;
    const float sy = (a.m_sumLinearVel.y - b.m_sumLinearVel.y) * j.m_linear0.y + a.m_sumAngularVel.y * j.m_angular[0].y + b.m_sumAngularVel.y * j.m_angular[1].y;
    const float sz = (a.m_sumLinearVel.z - b.m_sumLinearVel.z) * j.m_linear0.z + a.m_sumAngularVel.z * j.m_angular[0].z + b.m_sumAngularVel.z * j.m_angular[1].z;
    const float dx = ((a.m_linearVel.x - a.m_sumLinearVel.x) - (b.m_linearVel.x - b.m_sumLinearVel.x)) * j.m_linear0.x
                   + (a.m_angularVel.x - a.m_sumAngularVel.x) * j.m_angular[0].x + (b.m_angularVel.x - b.m_sumAngularVel.x) * j.m_angular[1].x;
    const float dy = ((a.m_linearVel.y - a.m_sumLinearVel.y) - (b.m_linearVel.y - b.m_sumLinearVel.y)) * j.m_linear0.y
                   + (a.m_angularVel.y - a.m_sumAngularVel.y) * j.m_angular[0].y + (b.m_angularVel.y - b.m_sumAngularVel.y) * j.m_angular[1].y;
    const float dz = ((a.m_linearVel.z - a.m_sumLinearVel.z) - (b.m_linearVel.z - b.m_sumLinearVel.z)) * j.m_linear0.z
                   + (a.m_angularVel.z - a.m_sumAngularVel.z) * j.m_angular[0].z + (b.m_angularVel.z - b.m_sumAngularVel.z) * j.m_angular[1].z;
    return (sx * tauFactor + dx * dampFactor) + (sy * tauFactor + dy * dampFactor) + (sz * tauFactor + dz * dampFactor);
}
static inline float getUserTauAngularVelocity(const hk2AngJacobian& j, const hkVelocityAccumulator_s010b_48b0& a, const hkVelocityAccumulator_s010b_48b0& b,
                                              float tauFactor, float dampFactor)
{
    const float sx = a.m_sumAngularVel.x * j.m_angular[0].x + b.m_sumAngularVel.x * j.m_angular[1].x;
    const float sy = a.m_sumAngularVel.y * j.m_angular[0].y + b.m_sumAngularVel.y * j.m_angular[1].y;
    const float sz = a.m_sumAngularVel.z * j.m_angular[0].z + b.m_sumAngularVel.z * j.m_angular[1].z;
    const float dx = (a.m_angularVel.x - a.m_sumAngularVel.x) * j.m_angular[0].x + (b.m_angularVel.x - b.m_sumAngularVel.x) * j.m_angular[1].x;
    const float dy = (a.m_angularVel.y - a.m_sumAngularVel.y) * j.m_angular[0].y + (b.m_angularVel.y - b.m_sumAngularVel.y) * j.m_angular[1].y;
    const float dz = (a.m_angularVel.z - a.m_sumAngularVel.z) * j.m_angular[0].z + (b.m_angularVel.z - b.m_sumAngularVel.z) * j.m_angular[1].z;
    return (sx * tauFactor + dx * dampFactor) + (sy * tauFactor + dy * dampFactor) + (sz * tauFactor + dz * dampFactor);
}
static inline void applyImpulse(const hk1Lin2AngJacobian& j, hkVelocityAccumulator_s010b_48b0& a, hkVelocityAccumulator_s010b_48b0& b, float impulse)
{
    const float dax = impulse * a.m_invMasses.w * j.m_linear0.x;
    const float day = impulse * a.m_invMasses.w * j.m_linear0.y;
    const float daz = impulse * a.m_invMasses.w * j.m_linear0.z;
    const float dbx = impulse * b.m_invMasses.w * j.m_linear0.x;
    const float dby = impulse * b.m_invMasses.w * j.m_linear0.y;
    const float dbz = impulse * b.m_invMasses.w * j.m_linear0.z;
    const float wax = impulse * a.m_invMasses.x * j.m_angular[0].x;
    const float way = impulse * a.m_invMasses.y * j.m_angular[0].y;
    const float waz = impulse * a.m_invMasses.z * j.m_angular[0].z;
    const float wbx = impulse * b.m_invMasses.x * j.m_angular[1].x;
    const float wby = impulse * b.m_invMasses.y * j.m_angular[1].y;
    const float wbz = impulse * b.m_invMasses.z * j.m_angular[1].z;
    a.m_linearVel.x += dax;
    a.m_linearVel.y += day;
    a.m_linearVel.z += daz;
    b.m_linearVel.x -= dbx;
    b.m_linearVel.y -= dby;
    b.m_linearVel.z -= dbz;
    a.m_angularVel.x += wax;
    a.m_angularVel.y += way;
    a.m_angularVel.z += waz;
    b.m_angularVel.x += wbx;
    b.m_angularVel.y += wby;
    b.m_angularVel.z += wbz;
}
static inline void applyImpulseL(const hk1Lin2AngJacobian& j, hkVelocityAccumulator_s010b_48b0& a, hkVelocityAccumulator_s010b_48b0& b,
                                 float d, float invJacDiag)
{
    const float dax = d * invJacDiag * a.m_invMasses.w * j.m_linear0.x;
    const float day = d * invJacDiag * a.m_invMasses.w * j.m_linear0.y;
    const float daz = d * invJacDiag * a.m_invMasses.w * j.m_linear0.z;
    const float dbx = d * invJacDiag * b.m_invMasses.w * j.m_linear0.x;
    const float dby = d * invJacDiag * b.m_invMasses.w * j.m_linear0.y;
    const float dbz = d * invJacDiag * b.m_invMasses.w * j.m_linear0.z;
    const float wax = d * invJacDiag * a.m_invMasses.x * j.m_angular[0].x;
    const float way = d * invJacDiag * a.m_invMasses.y * j.m_angular[0].y;
    const float waz = d * invJacDiag * a.m_invMasses.z * j.m_angular[0].z;
    const float wbx = d * invJacDiag * b.m_invMasses.x * j.m_angular[1].x;
    const float wby = d * invJacDiag * b.m_invMasses.y * j.m_angular[1].y;
    const float wbz = d * invJacDiag * b.m_invMasses.z * j.m_angular[1].z;
    a.m_linearVel.x += dax;
    a.m_linearVel.y += day;
    a.m_linearVel.z += daz;
    b.m_linearVel.x -= dbx;
    b.m_linearVel.y -= dby;
    b.m_linearVel.z -= dbz;
    a.m_angularVel.x += wax;
    a.m_angularVel.y += way;
    a.m_angularVel.z += waz;
    b.m_angularVel.x += wbx;
    b.m_angularVel.y += wby;
    b.m_angularVel.z += wbz;
}
static inline void applyAngularImpulse_s010b_48b0(const hk2AngJacobian& j, hkVelocityAccumulator_s010b_48b0& a, hkVelocityAccumulator_s010b_48b0& b, float impulse)
{
    const float wax = impulse * a.m_invMasses.x * j.m_angular[0].x;
    const float way = impulse * a.m_invMasses.y * j.m_angular[0].y;
    const float waz = impulse * a.m_invMasses.z * j.m_angular[0].z;
    const float wbx = impulse * b.m_invMasses.x * j.m_angular[1].x;
    const float wby = impulse * b.m_invMasses.y * j.m_angular[1].y;
    const float wbz = impulse * b.m_invMasses.z * j.m_angular[1].z;
    a.m_angularVel.x += wax;
    a.m_angularVel.y += way;
    a.m_angularVel.z += waz;
    b.m_angularVel.x += wbx;
    b.m_angularVel.y += wby;
    b.m_angularVel.z += wbz;
}
static inline void applyImpulse(const hk2Lin2AngJacobian& j, hkVelocityAccumulator_s010b_48b0& a, hkVelocityAccumulator_s010b_48b0& b, float impulse)
{
    const float dax = impulse * a.m_invMasses.w * j.m_linear[0].x;
    const float day = impulse * a.m_invMasses.w * j.m_linear[0].y;
    const float daz = impulse * a.m_invMasses.w * j.m_linear[0].z;
    const float dbx = impulse * b.m_invMasses.w * j.m_linear[1].x;
    const float dby = impulse * b.m_invMasses.w * j.m_linear[1].y;
    const float dbz = impulse * b.m_invMasses.w * j.m_linear[1].z;
    const float wax = impulse * a.m_invMasses.x * j.m_angular[0].x;
    const float way = impulse * a.m_invMasses.y * j.m_angular[0].y;
    const float waz = impulse * a.m_invMasses.z * j.m_angular[0].z;
    const float wbx = impulse * b.m_invMasses.x * j.m_angular[1].x;
    const float wby = impulse * b.m_invMasses.y * j.m_angular[1].y;
    const float wbz = impulse * b.m_invMasses.z * j.m_angular[1].z;
    a.m_linearVel.x += dax;
    a.m_linearVel.y += day;
    a.m_linearVel.z += daz;
    b.m_linearVel.x -= dbx;
    b.m_linearVel.y -= dby;
    b.m_linearVel.z -= dbz;
    a.m_angularVel.x += wax;
    a.m_angularVel.y += way;
    a.m_angularVel.z += waz;
    b.m_angularVel.x += wbx;
    b.m_angularVel.y += wby;
    b.m_angularVel.z += wbz;
}
static inline void solvePairContact(const hkJacobianPairContactSchema& s, const hk1Lin2AngJacobian* j,
                                    hkVelocityAccumulator_s010b_48b0& a, hkVelocityAccumulator_s010b_48b0& b, float* temp)
{
    const float v0 = j[0].m_linear0.w - getVelocity(j[0], a, b);
    const float v1 = j[1].m_linear0.w - getVelocity(j[1], a, b);
    const float i0 = v1 * s.m_coupling + v0 * j[0].m_angular[1].w;
    const float i1 = v0 * s.m_coupling + v1 * j[1].m_angular[1].w;
    if (i0 > 0.0f)                                // NaN takes the else side
    {
        if (i1 > 0.0f)
        {
            applyImpulse(j[0], a, b, i0);
            temp[0] += i0;
            applyImpulse(j[1], a, b, i1);
            temp[1] += i1;
            return;
        }
    }
    else
    {
        const float s1 = v1 * j[1].m_angular[0].w;
        if (!(s1 <= 0.0f))                        // NaN applies (jp)
        {
            applyImpulse(j[1], a, b, s1);
            temp[1] += s1;
            return;
        }
    }
    const float s0 = v0 * j[0].m_angular[0].w;
    if (s0 > 0.0f)
    {
        applyImpulse(j[0], a, b, s0);
        temp[0] += s0;
    }
}
static inline float clampFriction(float impulse, float maxImpulse, float& ratioOut)
{
    const float absImpulse = (float)fabs(impulse);
    if (absImpulse > maxImpulse)
    {
        const float ratio = maxImpulse / absImpulse;
        impulse = impulse * ratio;
        ratioOut = ratio;
    }
    return impulse;
}
static inline float clampMotor(float impulse, hkJacobianMotorSchema& s)
{
    if (impulse > s.m_maxImpulse)
    {
        s.m_impulseRatio = s.m_maxImpulse / impulse;
        impulse = s.m_maxImpulse;
    }
    else if (impulse < s.m_minImpulse)
    {
        s.m_impulseRatio = s.m_minImpulse / impulse;
        impulse = s.m_minImpulse;
    }
    return impulse;
}
// ---- items of slice s010b48b0 end

// @ 0x010b0b50
extern "C" void hkPoweredChain_BuildConstraintMatrixAndLuDecomposition( int numConstraints, const hkPoweredChainCfm* cfm, hkPoweredChainMotorInfo* motorInfos, const hkp1Lin2AngJacobian* linJacs, const hkp2AngJacobian* angJacs, const int* accumulatorOffsets, const char* accumulatorsBase, hkPoweredChainConstraintMatrices* matrices)
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
        hkBool_s010b_0b50 notLast;
        notLast.m_bool = (char)(i != numConstraints - 1);
        hkPoweredChain_ComputeConstraintMatrixLuDecomposition_ForOneRow(
            notLast, &matrices[i], &motorInfos[i], &prevOffDiagonal, &prevOffDiagonalPtr);
    }
}

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
            *(hkPoweredChainMotorInfo_s010b_17a0*)dst2 = *(const hkPoweredChainMotorInfo_s010b_17a0*)src2;
            dst2 += 0x4c;
            src2 += 0x4c;
        } while (--n != 0);
    }

    hdr->m_field0c = spec->m_field28;
    hdr->m_field04 = spec->m_field2c;
    hkPoweredChain_BuildConstraintMatrixAndLuDecomposition_s010b_17a0(
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

// @ 0x010b1d70
extern "C" int hkPoweredChain_JacobiBuild(int dummy, const hkJacobianStream* jac, int offsetA, int offsetM, int limit, float* out)
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

// @ 0x010b22a0
void __cdecl GskSolver_Iterate(const GskSolverConfig* pConfig, GskVertex* pVertices, const GskContactList* pContacts, GskRow* pRows, hkReal* pAccumulators)
{
    const int count = pContacts->m_count;
    hkReal* pImpulses = (hkReal*)((char*)pRows + count * 0x3c);
    const hkReal massScale = pContacts->m_weight0 * pConfig->m_invMassScale;
    const hkReal dt = pContacts->m_weight1;

    // ---- forward pass: solve for every contact's impulse -------------------------------
    for (int i = 0; i < count; ++i)
    {
        const GskRow* pRow = &pRows[i];
        const GskVertex* pA = &pVertices[pContacts->m_vertexIndex[2 * i]];
        const GskVertex* pB = &pVertices[pContacts->m_vertexIndex[2 * i + 1]];

        // relative velocity of the pair along the contact direction
        hkReal relVel = 0.0f;
        hkReal response = 0.0f;
        for (int c = 0; c < 3; ++c)
        {
            hkReal dv = (pA->m_linear[c] - pRow->m_vel0[c]) -
                        (pB->m_linear[c] - pRow->m_vel1[c]);
            relVel += dv * pRow->m_normal[c];
            response += (pA->m_direction[c] * massScale + pB->m_direction[c]) *
                        (pA->m_linear[c] + pB->m_linear[c]) * dt;
        }

        // the accumulated impulse of the previous contact feeds back into this one
        hkReal impulse = ((relVel * massScale + response) -
                          (i > 0 ? pImpulses[i - 1] * pRow[0].m_impulse : 0.0f)) /
                         pRow->m_impulse;
        pImpulses[i] = impulse;
    }

    // ---- backward pass: integrate the impulses back into the vertices -------------------
    for (int i = count - 1; i >= 0; --i)
    {
        GskRow* pRow = &pRows[i];
        GskVertex* pA = &pVertices[pContacts->m_vertexIndex[2 * i]];
        GskVertex* pB = &pVertices[pContacts->m_vertexIndex[2 * i + 1]];
        hkReal impulse = pImpulses[i];

        for (int c = 0; c < 3; ++c)
        {
            pA->m_linear[c] += impulse * pA->m_invMass * pRow->m_normal[c];
            pB->m_linear[c] -= impulse * pB->m_invMass * pRow->m_normal[c];
            pA->m_angular[c] += impulse * pA->m_direction[c] * pRow->m_vel0[c];
            pB->m_angular[c] += impulse * pB->m_direction[c] * pRow->m_vel1[c];
        }
        pAccumulators[i] += impulse;
    }
}

// @ 0x010b2890
void* ChainSolve(Solver* solver, char* bodies, Chain* chain, float* mat, float* out)
{
    int n = chain->n;
    char* lastA = 0;
    float* L = (float*)((char*)mat + n * 0x90);      // per-link 3x4 factor blocks
    float* V = (float*)((char*)mat + n * 0x120 + 0x10) - 4; // n+1 vectors, 4 floats each
    V[0] = 0; V[1] = 0; V[2] = 0; V[3] = 0;
    lastA = (char*)V + 0x10;
    for (int i = 0; i < n; i++) {
        char* A = bodies + chain->off[i];
        char* B = bodies + chain->off[i + 1];
        float* m = mat + i * 36;
        float* l = L + i * 36;
        float* v = V + i * 4;
        float fV = chain->stiff * solver->dt;
        float fU = chain->damp;
        float r[3];
        r[0] = FwdRow(0, (float*)A, (float*)B, m, l, v, chain->stiff, fV, fU);
        r[1] = FwdRow(1, (float*)A, (float*)B, m, l, v, chain->stiff, fV, fU);
        r[2] = FwdRow(2, (float*)A, (float*)B, m, l, v, chain->stiff, fV, fU);
        float* nv = v + 4;
        nv[0] = r[1] * l[16] + (r[0] * l[12] + r[2] * l[20]);
        nv[1] = r[0] * l[13] + (r[1] * l[17] + r[2] * l[21]);
        nv[2] = r[0] * l[14] + (r[1] * l[18] + r[2] * l[22]);
        nv[3] = 0.0f;
    }

    float x0 = 0.0f, x1 = 0.0f, x2 = 0.0f;
    for (int i = n - 1; i >= 0; i--) {
        char* bodyA = bodies + chain->off[i];
        lastA = bodyA;
        float* A = (float*)bodyA;
        float* B = (float*)(bodies + chain->off[i + 1]);
        float* m = mat + i * 36;
        float* l = L + i * 36;
        float* nv = V + (i + 1) * 4;
        float* o = (float*)((char*)out + i * 0xc);
        float t0 = nv[0] - (x1 * l[28] + (x0 * l[24] + x2 * l[32]));
        float t1 = nv[1] - (x0 * l[25] + (x2 * l[33] + x1 * l[29]));
        float t2 = nv[2] - (x0 * l[26] + (x2 * l[34] + x1 * l[30]));
        x0 = t0; x1 = t1; x2 = t2;
        BackRow(0, x0, A, B, m, o);
        BackRow(1, x1, A, B, m, o);
        BackRow(2, x2, A, B, m, o);
    }
    return lastA;
}

// @ 0x010b3b20
void __cdecl hkPoweredChain_Solve(const hkPoweredChainSolverParams* params, char* accumulatorsBase, hkPoweredChainSchema* schema, char* buffer, hkReal* impulses)
{
    hkPoweredChainSolverInfo info;
    int n = schema->m_numConstraints;
    info.m_params = params;
    info.m_numConstraints = n;
    info.m_tau = schema->m_tau;
    info.m_damping = schema->m_damping;
    info.m_linearJacobians = (hkp1Lin2AngJacobian_s010b_3b20*)buffer;
    info.m_angularJacobians = (hkp2AngJacobian_s010b_3b20*)(buffer + n * sizeof(hkp1Lin2AngJacobian_s010b_3b20) * 3);
    info.m_accumulatorOffsets = schema->m_accumulatorOffsets;
    info.m_accumulatorsBase = accumulatorsBase;
    info.m_matrices = (hkPoweredChainConstraintMatrices_s010b_3b20*)(buffer + n * 0xf0);
    info.m_motorInfo = (hkPoweredChainMotorInfo_s010b_3b20*)&schema->m_accumulatorOffsets[n + 1];
    info.m_velocities = (hkVector8*)(buffer + n * 0x4b0);
    info.m_rhs = (hkVector8*)(buffer + n * 0x4d0 + 0x20);

    // Motor target velocities go into the rhs of the angular rows.
    int i;
    for (i = 0; i < info.m_numConstraints; i++) {
        hkp2AngJacobian_s010b_3b20* jac = &info.m_angularJacobians[i * 3];
        hkPoweredChainMotorInfo_s010b_3b20& motorInfo = info.m_motorInfo[i];
        jac[0].m_angular[1].w = motorInfo.m_motors[0].m_targetVelocity + jac[0].m_angular[1].w;
        jac[1].m_angular[1].w = motorInfo.m_motors[1].m_targetVelocity + jac[1].m_angular[1].w;
        jac[2].m_angular[1].w = motorInfo.m_motors[2].m_targetVelocity + jac[2].m_angular[1].w;
    }

    hkPoweredChain_CalculateVelocities(&info, info.m_rhs);

    for (i = 0; i < info.m_numConstraints; i++) {
        for (int j = 0; j < 3; j++) {
            int state = (hkUint8)(info.m_motorInfo[i].m_motorStates >> (j * 2)) & 3;
            if (state == 2)
                (&info.m_rhs[i].m_ang.x)[j] = 0.0f;
            else if (state != 0)
                hkPoweredChain_OverwriteVelocityWithExplicitImpulse(i, j, info.m_motorInfo, info.m_rhs);
        }
    }

    int constraintIndex;
    int motorIndex;
    hkReal maxError;

    FUN_010aef10(&info, info.m_velocities);
    constraintIndex = -1;
    motorIndex = -1;
    maxError = 0.0f;
    hkPoweredChain_ScanAndEnableMotors(&info, &constraintIndex, &motorIndex, &maxError, info.m_motorInfo);
    while (constraintIndex >= 0) {
        hkPoweredChain_UpdateLuDecomposition(constraintIndex, info.m_numConstraints, info.m_motorInfo,
                                             info.m_matrices);
        hkPoweredChain_RestoreVelocityValue(constraintIndex, motorIndex, &info, info.m_rhs);
        FUN_010aef10(&info, info.m_velocities);
        constraintIndex = -1;
        motorIndex = -1;
        maxError = 0.0f;
        hkPoweredChain_ScanAndEnableMotors(&info, &constraintIndex, &motorIndex, &maxError, info.m_motorInfo);
    }

    FUN_010aef10(&info, info.m_velocities);
    constraintIndex = -1;
    motorIndex = -1;
    maxError = 0.0f;
    hkPoweredChain_ScanAndDisableMotors(&info, &constraintIndex, &motorIndex, &maxError, info.m_motorInfo);
    while (constraintIndex >= 0) {
        hkPoweredChain_UpdateLuDecomposition(constraintIndex, info.m_numConstraints, info.m_motorInfo,
                                             info.m_matrices);
        hkPoweredChain_OverwriteVelocityWithExplicitImpulse(constraintIndex, motorIndex, info.m_motorInfo,
                                                            info.m_rhs);
        FUN_010aef10(&info, info.m_velocities);
        constraintIndex = -1;
        motorIndex = -1;
        maxError = 0.0f;
        hkPoweredChain_ScanAndDisableMotors(&info, &constraintIndex, &motorIndex, &maxError, info.m_motorInfo);
    }

    // Back substitution: vel[i] = velocities[i+1] - m2[i] * vel[i+1], then apply vel[i] as impulses.
    hkVector8 vel;
    vel.m_lin.x = 0.0f;
    vel.m_lin.y = 0.0f;
    vel.m_lin.z = 0.0f;
    vel.m_ang.x = 0.0f;
    vel.m_ang.y = 0.0f;
    vel.m_ang.z = 0.0f;
    for (i = info.m_numConstraints - 1; i >= 0; i--) {
        const hkMatrix6_s010b_3b20& m = info.m_matrices[i].m_m2;
        hkReal lx = vel.m_lin.x, ly = vel.m_lin.y, lz = vel.m_lin.z;
        hkReal ax = vel.m_ang.x, ay = vel.m_ang.y, az = vel.m_ang.z;

        hkReal t00 = mulRowA(m.m_m[0][0], 0, lx, ly, lz);
        hkReal t01 = mulRowA(m.m_m[0][0], 1, lx, ly, lz);
        hkReal t02 = mulRowA(m.m_m[0][0], 2, lx, ly, lz);
        hkReal u00 = mulRowA(m.m_m[0][1], 0, ax, ay, az);
        hkReal u01 = mulRowA(m.m_m[0][1], 1, ax, ay, az);
        hkReal u02 = mulRowA(m.m_m[0][1], 2, ax, ay, az);
        hkReal t10 = mulRowA(m.m_m[1][0], 0, lx, ly, lz);
        hkReal t11 = mulRowA(m.m_m[1][0], 1, lx, ly, lz);
        hkReal t12 = mulRowA(m.m_m[1][0], 2, lx, ly, lz);
        hkReal u10 = mulRowA(m.m_m[1][1], 0, ax, ay, az);
        hkReal u11 = mulRowB(m.m_m[1][1], 1, ax, ay, az);
        hkReal u12 = mulRowB(m.m_m[1][1], 2, ax, ay, az);

        const hkVector8& v = info.m_velocities[i + 1];
        vel.m_lin.x = v.m_lin.x - (u00 + t00);
        vel.m_lin.y = v.m_lin.y - (u01 + t01);
        vel.m_lin.z = v.m_lin.z - (u02 + t02);
        vel.m_ang.x = v.m_ang.x - (u10 + t10);
        vel.m_ang.y = v.m_ang.y - (u11 + t11);
        vel.m_ang.z = v.m_ang.z - (u12 + t12);

        hkVelocityAccumulator_s010b_3b20* accA =
            (hkVelocityAccumulator_s010b_3b20*)(accumulatorsBase + info.m_accumulatorOffsets[i]);
        hkVelocityAccumulator_s010b_3b20* accB =
            (hkVelocityAccumulator_s010b_3b20*)(accumulatorsBase + info.m_accumulatorOffsets[i + 1]);
        const hkp1Lin2AngJacobian_s010b_3b20* lin = &info.m_linearJacobians[i * 3];
        const hkp2AngJacobian_s010b_3b20* ang = &info.m_angularJacobians[i * 3];
        hkReal* imp = &impulses[i * 6];

        applyLinearImpulse(accA, accB, lin[0], vel.m_lin.x);
        imp[0] = vel.m_lin.x + imp[0];
        applyLinearImpulse(accA, accB, lin[1], vel.m_lin.y);
        imp[1] = vel.m_lin.y + imp[1];
        applyLinearImpulse(accA, accB, lin[2], vel.m_lin.z);
        imp[2] = vel.m_lin.z + imp[2];
        applyAngularImpulse(accA, accB, ang[0], vel.m_ang.x);
        imp[3] = vel.m_ang.x + imp[3];
        applyAngularImpulse(accA, accB, ang[1], vel.m_ang.y);
        imp[4] = vel.m_ang.y + imp[4];
        applyAngularImpulse(accA, accB, ang[2], vel.m_ang.z);
        imp[5] = vel.m_ang.z + imp[5];
    }
}

// @ 0x010b48b0
void hkSolver_solveJacobianSchemas(hkSolverInfo_s010b_48b0& info, hkJacobianSchema* schemas, char* accumulators, hkJacobianElement* jacobians, float* temp)
{
    float savedDamping = info.m_damping;
    float savedTau = info.m_tau;

    char* s = (char*)schemas;
    char* jac;
    hkVelocityAccumulator_s010b_48b0* a;
    hkVelocityAccumulator_s010b_48b0* b;

header:
    {
        const hkJacobianHeaderSchema* h = (const hkJacobianHeaderSchema*)s;
        a = (hkVelocityAccumulator_s010b_48b0*)(accumulators + h->m_bodyAOffset);
        b = (hkVelocityAccumulator_s010b_48b0*)(accumulators + h->m_bodyBOffset);
        jac = (char*)jacobians + h->m_jacobianOffset;
        s += sizeof(hkJacobianHeaderSchema);
    }

    for (;;)
    {
        switch (((hkJacobianSchema*)s)->m_type)
        {
        case SCHEMA_END:
            return;

        case SCHEMA_HEADER:
            goto header;

        case SCHEMA_SINGLE_CONTACT:
            do
            {
                hk1Lin2AngJacobian& j = *(hk1Lin2AngJacobian*)jac;
                const float v = j.m_linear0.w - getVelocity(j, *a, *b);
                if (!(v < 0.0f))                  // NaN applies (test ah,5 / jnp)
                {
                    const float impulse = v * j.m_angular[0].w;
                    applyImpulse(j, *a, *b, impulse);
                    *temp += impulse;
                }
                s += 4;
                jac += sizeof(hk1Lin2AngJacobian);
                temp += 1;
            } while (((hkJacobianSchema*)s)->m_type == SCHEMA_SINGLE_CONTACT);
            break;

        case SCHEMA_PAIR_CONTACT:
            // The original solves up to two pair schemas in a row, then goes straight
            // into 3D friction when that follows.
            solvePairContact(*(hkJacobianPairContactSchema*)s, (hk1Lin2AngJacobian*)jac, *a, *b, temp);
            s += sizeof(hkJacobianPairContactSchema);
            temp += 2;
            jac += 2 * sizeof(hk1Lin2AngJacobian);
            if (((hkJacobianSchema*)s)->m_type != SCHEMA_PAIR_CONTACT)
                break;
            solvePairContact(*(hkJacobianPairContactSchema*)s, (hk1Lin2AngJacobian*)jac, *a, *b, temp);
            s += sizeof(hkJacobianPairContactSchema);
            temp += 2;
            jac += 2 * sizeof(hk1Lin2AngJacobian);
            if (((hkJacobianSchema*)s)->m_type != SCHEMA_3D_FRICTION)
                break;
            // fall through
        case SCHEMA_3D_FRICTION:
        {
            hkJacobian2dFrictionSchema& fs = *(hkJacobian2dFrictionSchema*)s;
            hk1Lin2AngJacobian* j = (hk1Lin2AngJacobian*)jac;
            hk2AngJacobian& ja = *(hk2AngJacobian*)(jac + 2 * sizeof(hk1Lin2AngJacobian));
            const float v0 = j[0].m_linear0.w - getVelocity(j[0], *a, *b);
            const float v1 = j[1].m_linear0.w - getVelocity(j[1], *a, *b);
            float va = (ja.m_angular[1].w - getAngularVelocity(ja, *a, *b)) * ja.m_angular[0].w;
            float i0 = v1 * fs.m_coupling + v0 * j[0].m_angular[1].w;
            float i1 = v0 * fs.m_coupling + v1 * j[1].m_angular[1].w;
            const float lenSq = i0 * i0 + (i1 * i1 + va * va);
            if (lenSq > fs.m_maxFrictionImpulse * fs.m_maxFrictionImpulse)
            {
                const float ratio = fs.m_maxFrictionImpulse / (float)sqrt(lenSq);
                i0 = ratio * i0;
                i1 = ratio * i1;
                va = va * ratio;
                fs.m_frictionRatio = ratio;
            }
            va = va * fs.m_angularFrictionFactor;
            applyImpulse(j[0], *a, *b, i0);
            temp[0] += i0;
            applyImpulse(j[1], *a, *b, i1);
            temp[1] += i1;
            applyAngularImpulse_s010b_48b0(ja, *a, *b, va);
            temp[2] += va;
            s += 0x1c;
            jac += 2 * sizeof(hk1Lin2AngJacobian) + sizeof(hk2AngJacobian);
            temp += 3;
            break;
        }

        case SCHEMA_2D_FRICTION:
        {
            hkJacobian2dFrictionSchema& fs = *(hkJacobian2dFrictionSchema*)s;
            hk1Lin2AngJacobian* j = (hk1Lin2AngJacobian*)jac;
            const float v0 = j[0].m_linear0.w - getVelocity(j[0], *a, *b);
            const float v1 = j[1].m_linear0.w - getVelocity(j[1], *a, *b);
            const float maxSq = fs.m_maxFrictionImpulse * fs.m_maxFrictionImpulse;
            float i0 = v1 * fs.m_coupling + v0 * j[0].m_angular[1].w;
            float i1 = v0 * fs.m_coupling + v1 * j[1].m_angular[1].w;
            const float lenSq = i0 * i0 + i1 * i1;
            if (lenSq > maxSq)
            {
                const float ratio = (float)sqrt(maxSq / lenSq);
                i0 = ratio * i0;
                i1 = ratio * i1;
                fs.m_frictionRatio = ratio;
            }
            applyImpulse(j[0], *a, *b, i0);
            temp[0] += i0;
            applyImpulse(j[1], *a, *b, i1);
            temp[1] += i1;
            s += 0x18;
            jac += 2 * sizeof(hk1Lin2AngJacobian);
            temp += 2;
            break;
        }

        case SCHEMA_ANGULAR_MOTOR:
            do
            {
                hkJacobianMotorSchema& ms = *(hkJacobianMotorSchema*)s;
                hk2AngJacobian& j = *(hk2AngJacobian*)jac;
                j.m_angular[1].w = ms.m_velocity + j.m_angular[1].w;
                const float tauFactor = ms.m_tau * info.m_invIntegrateVelocityFactor.x;
                float impulse = (j.m_angular[1].w * ms.m_tau
                                 - getUserTauAngularVelocity(j, *a, *b, tauFactor, ms.m_damping)) * j.m_angular[0].w;
                impulse = clampMotor(impulse, ms);
                s += sizeof(hkJacobianMotorSchema);
                applyAngularImpulse_s010b_48b0(j, *a, *b, impulse);
                *temp += impulse;
                temp += 1;
                jac += sizeof(hk2AngJacobian);
            } while (((hkJacobianSchema*)s)->m_type == SCHEMA_ANGULAR_MOTOR);
            break;

        case SCHEMA_LINEAR_MOTOR:
            do
            {
                hkJacobianMotorSchema& ms = *(hkJacobianMotorSchema*)s;
                hk1Lin2AngJacobian& j = *(hk1Lin2AngJacobian*)jac;
                j.m_linear0.w = ms.m_velocity + j.m_linear0.w;
                const float tauFactor = ms.m_tau * info.m_invIntegrateVelocityFactor.x;
                float impulse = (j.m_linear0.w * ms.m_tau
                                 - getUserTauVelocity(j, *a, *b, tauFactor, ms.m_damping)) * j.m_angular[0].w;
                impulse = clampMotor(impulse, ms);
                applyImpulse(j, *a, *b, impulse);
                *temp += impulse;
                jac = (char*)j.next(1);
                temp += 1;
                s += sizeof(hkJacobianMotorSchema);
            } while (((hkJacobianSchema*)s)->m_type == SCHEMA_LINEAR_MOTOR);
            break;

        case SCHEMA_LINEAR_FRICTION:
            do
            {
                hkJacobianFrictionSchema& fs = *(hkJacobianFrictionSchema*)s;
                hk1Lin2AngJacobian& j = *(hk1Lin2AngJacobian*)jac;
                float impulse = (j.m_linear0.w - getVelocity(j, *a, *b)) * j.m_angular[0].w;
                impulse = clampFriction(impulse, fs.m_maxFrictionImpulse, fs.m_frictionRatio);
                applyImpulse(j, *a, *b, impulse);
                *temp += impulse;
                jac = (char*)j.next(1);
                temp += 1;
                s += sizeof(hkJacobianFrictionSchema);
            } while (((hkJacobianSchema*)s)->m_type == SCHEMA_LINEAR_FRICTION);
            break;

        case SCHEMA_ANGULAR_FRICTION:
            do
            {
                hkJacobianFrictionSchema& fs = *(hkJacobianFrictionSchema*)s;
                hk2AngJacobian& j = *(hk2AngJacobian*)jac;
                float impulse = (j.m_angular[1].w - getAngularVelocity(j, *a, *b)) * j.m_angular[0].w;
                impulse = clampFriction(impulse, fs.m_maxFrictionImpulse, fs.m_frictionRatio);
                s += sizeof(hkJacobianFrictionSchema);
                applyAngularImpulse_s010b_48b0(j, *a, *b, impulse);
                *temp += impulse;
                temp += 1;
                jac += sizeof(hk2AngJacobian);
            } while (((hkJacobianSchema*)s)->m_type == SCHEMA_ANGULAR_FRICTION);
            break;

        case SCHEMA_ANGULAR_LIMIT:
            do
            {
                const hkJacobianAngularLimitSchema& ls = *(hkJacobianAngularLimitSchema*)s;
                hk2AngJacobian& j = *(hk2AngJacobian*)jac;
                const float tauFactor = ls.m_tau * info.m_invIntegrateVelocityFactor.x;
                const float damping = info.m_damping;
                const float v = ls.m_tau * j.m_angular[1].w - getUserTauAngularVelocity(j, *a, *b, tauFactor, damping);
                const float dMax = v - ls.m_maxRhs;
                if (dMax > 0.0f)                  // NaN goes to the lower-limit side
                {
                    const float impulse = dMax * j.m_angular[0].w;
                    applyAngularImpulse_s010b_48b0(j, *a, *b, impulse);
                    *temp += impulse;
                }
                else
                {
                    const float dMin = v - ls.m_minRhs;
                    if (dMin < 0.0f)
                    {
                        const float impulse = dMin * j.m_angular[0].w;
                        applyAngularImpulse_s010b_48b0(j, *a, *b, impulse);
                        *temp += impulse;
                    }
                }
                jac += sizeof(hk2AngJacobian);
                s += sizeof(hkJacobianAngularLimitSchema);
                temp += 1;
            } while (((hkJacobianSchema*)s)->m_type == SCHEMA_ANGULAR_LIMIT);
            break;

        case SCHEMA_LINEAR_LIMIT:
            do
            {
                const hkJacobianLinearLimitSchema& ls = *(hkJacobianLinearLimitSchema*)s;
                hk1Lin2AngJacobian& j = *(hk1Lin2AngJacobian*)jac;
                const float v = j.m_linear0.w - getVelocity(j, *a, *b);
                const float dMax = v - ls.m_maxRhs;
                if (dMax > 0.0f)
                {
                    applyImpulseL(j, *a, *b, dMax, j.m_angular[0].w);
                    *temp += dMax * j.m_angular[0].w;
                }
                const float dMin = v - ls.m_minRhs;
                if (dMin < 0.0f)
                {
                    applyImpulseL(j, *a, *b, dMin, j.m_angular[0].w);
                    *temp += dMin * j.m_angular[0].w;
                }
                jac = (char*)j.next(1);
                temp += 1;
                s += sizeof(hkJacobianLinearLimitSchema);
            } while (((hkJacobianSchema*)s)->m_type == SCHEMA_LINEAR_LIMIT);
            break;

        case SCHEMA_ANGULAR_BILATERAL:
            do
            {
                hk2AngJacobian& j = *(hk2AngJacobian*)jac;
                const float impulse = (j.m_angular[1].w - getAngularVelocity(j, *a, *b)) * j.m_angular[0].w;
                applyAngularImpulse_s010b_48b0(j, *a, *b, impulse);
                *temp += impulse;
                s += 4;
                jac += sizeof(hk2AngJacobian);
                temp += 1;
            } while (((hkJacobianSchema*)s)->m_type == SCHEMA_ANGULAR_BILATERAL);
            break;

        case SCHEMA_LINEAR_BILATERAL:
            do
            {
                hk1Lin2AngJacobian& j = *(hk1Lin2AngJacobian*)jac;
                const float impulse = (j.m_linear0.w - getVelocity(j, *a, *b)) * j.m_angular[0].w;
                applyImpulse(j, *a, *b, impulse);
                *temp += impulse;
                jac = (char*)j.next(1);
                temp += 1;
                s += 4;
            } while (((hkJacobianSchema*)s)->m_type == SCHEMA_LINEAR_BILATERAL);
            break;

        case SCHEMA_LINEAR_BILATERAL_USER_TAU:
            do
            {
                const hkJacobianUserTauSchema& ts = *(hkJacobianUserTauSchema*)s;
                hk1Lin2AngJacobian& j = *(hk1Lin2AngJacobian*)jac;
                const float tauFactor = ts.m_tau * info.m_invIntegrateVelocityFactor.x;
                const float impulse = (ts.m_tau * j.m_linear0.w
                                       - getUserTauVelocity(j, *a, *b, tauFactor, ts.m_damping)) * j.m_angular[0].w;
                applyImpulse(j, *a, *b, impulse);
                *temp += impulse;
                jac = (char*)j.next(1);
                temp += 1;
                s += sizeof(hkJacobianUserTauSchema);
            } while (((hkJacobianSchema*)s)->m_type == SCHEMA_LINEAR_BILATERAL_USER_TAU);
            break;

        case SCHEMA_SET_MASS:
        {
            const hkVector4_s010b_48b0* m = (const hkVector4_s010b_48b0*)jac;
            a->m_invMasses = m[0];
            b->m_invMasses = m[1];
            jac += 2 * sizeof(hkVector4_s010b_48b0);
            s += ((hkJacobianSchema*)s)->m_size;
            break;
        }

        case SCHEMA_ADD_VELOCITY:
        {
            const hkVector4_s010b_48b0& dv = *(const hkVector4_s010b_48b0*)jac;
            jac += sizeof(hkVector4_s010b_48b0);
            const float f = info.m_integrateVelocityFactor.x * 0.0f;
            const float fx = f * dv.x, fy = f * dv.y, fz = f * dv.z, fw = f * dv.w;
            a->m_linearVel.x += dv.x;
            a->m_linearVel.y += dv.y;
            a->m_linearVel.z += dv.z;
            a->m_linearVel.w += dv.w;
            a->m_linearVel.x += fx;
            a->m_linearVel.y += fy;
            a->m_linearVel.z += fz;
            a->m_linearVel.w += fw;
            a->m_sumLinearVel.x += fx;
            a->m_sumLinearVel.y += fy;
            a->m_sumLinearVel.z += fz;
            a->m_sumLinearVel.w += fw;
        }
            // fall through
        case SCHEMA_GOTO:
            s += ((hkJacobianSchema*)s)->m_size;
            break;

        case SCHEMA_SET_TAU_AND_DAMPING:
        {
            const hkJacobianUserTauSchema& ts = *(hkJacobianUserTauSchema*)s;
            savedDamping = info.m_damping;
            savedTau = info.m_tau;
            info.m_damping = ts.m_damping;
            info.m_tau = ts.m_tau;
            s += sizeof(hkJacobianUserTauSchema);
            break;
        }

        case SCHEMA_RESTORE_TAU_AND_DAMPING:
            info.m_tau = savedTau;
            info.m_damping = savedDamping;
            s += 4;
            break;

        case SCHEMA_PULLEY:
        {
            hk2Lin2AngJacobian& j = *(hk2Lin2AngJacobian*)jac;
            const float impulse = (j.m_linear[0].w - getVelocity(j, *a, *b)) * j.m_angular[0].w;
            applyImpulse(j, *a, *b, impulse);
            *temp += impulse;
            jac = (char*)j.next(1);
            temp += 1;
            s += 0xc;
            break;
        }

        case SCHEMA_STIFF_SPRING_CHAIN:
        {
            hkJacobianStiffSpringChainSchema_s010b_48b0* cs = (hkJacobianStiffSpringChainSchema_s010b_48b0*)s;
            hkSolveStiffSpringChain(info, accumulators, cs, (hkJacobianElement*)jac, temp);
            temp += cs->m_numConstraints;
            jac = (char*)cs->getEnd((hkJacobianElement*)jac);
            s += cs->m_size;
            break;
        }

        case SCHEMA_BALL_SOCKET_CHAIN:
        {
            hkJacobianBallSocketChainSchema_s010b_48b0* cs = (hkJacobianBallSocketChainSchema_s010b_48b0*)s;
            hkSolveBallSocketChain(info, accumulators, cs, (hkJacobianElement*)jac, temp);
            temp += cs->m_numConstraints * 3;
            jac = (char*)cs->getEnd((hkJacobianElement*)jac);
            s += cs->m_size;
            break;
        }

        case SCHEMA_POWERED_CHAIN:
        {
            hkJacobianPoweredChainSchema_s010b_48b0* cs = (hkJacobianPoweredChainSchema_s010b_48b0*)s;
            hkSolvePoweredChain(info, accumulators, cs, (hkJacobianElement*)jac, temp);
            temp += cs->m_numConstraints * 6;
            jac = (char*)cs->getEnd((hkJacobianElement*)jac);
            s += cs->m_size;
            break;
        }

        default:                                  // types 2, 0x16 and > 0x19
            __debugbreak();
            return;
        }
    }
}
