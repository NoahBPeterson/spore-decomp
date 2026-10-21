// Slice s010ac8f0 -- Havok 3.1.0 constraint "build jacobian" helpers in the powered-chain / ball-socket
// solver family (SporeApp.exe 0x010ac8f0..0x010ad3ad).
//
//  010ac8f0  hk1dLinearVelocityMotor::buildJacobian   (one row, caller-supplied axis)
//  010acb50  hkSetInvMassBuildJacobian                 (hkJacobian helper: "constant" build jacobian)
//  010acbb0  hkAddVelocityBuildJacobian                (hkJacobian helper)
//  010acbf0  hkStabilizedBallSocketConstraint::buildJacobian (3 rows, identity basis)
//  010ad020  hkConstraintBuildJacobian::buildJacobianAndSetData<T, N>  (N=4 layout, sizeof(hkMatrix6)=0xa0)
//  010ad0b0  hkConstraintBuildJacobian::buildJacobianAndSetData<T, N>  (N=3 layout, sizeof=0x10*n)
//  010ad140  hkMatrix6::hkMatrix6(const hkMatrix6&)
//  010ad1c0  hkPoweredChain_ApplyMotorStatesToRows
//  010ad2d0  hkPoweredChain_DisableMotorInMatrixRow_NextConstraint
//  010ad360  hkPoweredChain_OverwriteVelocityWithExplicitImpulse
//
// Flags: /vc71 /O2 /MD /Gy /TP  (Havok 3.1.0 prebuilt library, cl 13.10, x87)
#include "types.h"
#include <math.h>

typedef float hkReal;
typedef unsigned char hkUint8;

// ---- math ---------------------------------------------------------------------------------------------
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
};
class hkMatrix6 {
public:
    hkMatrix3 m_m[2][2];   // [row][column]
    hkMatrix6() {}
    hkMatrix6(const hkMatrix6& o);      // 0x010ad140 (thiscall, ret 4)
};

// The identity basis table at 0x015b9b20: three unit hkVector4 rows (x), (y), (z).
// buildJacobian's loop walks it as a pointer whose "row base" is at +8 (so [row-2..row+1] == x,y,z,w).
extern hkVector4 hk_identityBasis[4];   // 0x015b9b20: (1,0,0,0),(0,1,0,0),(0,0,1,0),(0,0,0,1)

// ---- constraint-side objects -------------------------------------------------------------------------
// A hkRigidBody-like motion holder: the two bodies hang off the constraint at +0x28/+0x2c, each carrying a
// hkMotionState at +0x30 whose transform / inertia / cfm rows start at the offsets used below.
struct hkMassAndVelocity {
    hkUint8  m_pad0[0xc];
    hkUint8  m_useInvInertia;      // +0x0c  (0 = use the full inertia rows, nonzero = identity)
    hkUint8  m_pad1[0x03];
    hkReal   m_invMassScalar;      // +0x10
    hkReal   m_linearVelocity[3];  // +0x14  (unused here)
    hkReal   m_gravity[3];         // +0x20  (unused here)
    hkUint8  m_pad2[0x08];
    hkReal   m_diag;               // +0x30 .. 0x38 inertia diagonal (x,y,z)
    hkReal   m_diagY;
    hkReal   m_diagZ;
    hkReal   m_cfmScalar;          // +0x3c
    hkReal   m_centerOfMass[3];    // +0x40
    hkUint8  m_pad3[0x04];
    hkReal   m_invInertia[9];      // +0x50 world inverse inertia (3x3, column stride 0x10)
};

// The constraint that owns the two bodies: this+0x28 / this+0x2c point at the hkMassAndVelocity states.
struct hkConstraintCore {
    hkUint8 m_pad0[0x14];
    hkReal  m_tau;                 // +0x14
    hkUint8 m_pad1[0x0c];
    hkReal  m_stabilizationFactor; // +0x18 (?)  -- read as [param_4+0x18]
    hkUint8 m_pad2[0x0c];
    hkMassAndVelocity* m_bodyA;    // +0x28
    hkMassAndVelocity* m_bodyB;    // +0x2c
};

// hkPoweredChainMotorInfo (0x4c bytes): the low bits of m_motorStates select which motors are disabled.
struct hkPoweredChainMotorInfo {
    hkUint8 m_motorStates;
    hkUint8 m_pad[0x4b];
};

// The 5 block matrices of one powered-chain row (see s010ad3b0).
struct hkPoweredChainConstraintMatrices {
    hkMatrix6 m_m0;
    hkMatrix6 m_m1;
    hkMatrix6 m_m2;
    hkMatrix6 m_m3;
    hkMatrix6 m_m4;
};

// ---- external helpers ---------------------------------------------------------------------------------
extern "C" {
// 0x010ab2d0: shared "fill motor rows from the constraint + compute the 1d stabilization axis".
void hkPoweredChain_BuildMotorJacobianRows(const hkReal* dirA, const hkReal* dirB,
                                           hkConstraintCore* constraint, void* outState);   // 0x010ab2d0

// 0x010ac550 / 0x010abb90: build the actual constraint jacobian rows (elementSize 0x30 / bigger).
void hkConstraintBuildJacobian_N3(int n, void* a, void* b, void* out);   // 0x010ac550
void hkConstraintBuildJacobian_N6(int n, void* a, void* b, void* out);   // 0x010abb90
}

extern hkReal HK_REAL_EPSILON;   // 0x014a23a4 (FLT_EPSILON)
extern hkReal HK_REAL_ONE;       // 0x01485720 (1.0f)
extern hkReal HK_REAL_ZERO;      // 0x01485378 (0.0f)

// =========================================================================================================
// 010ac8f0 -- hk1dLinearVelocityMotor::buildJacobian
// =========================================================================================================
// @ 0x010ac8f0
extern "C" void hk1dLinearVelocityMotorBuildJacobian(const hkReal* dir, const hkReal* pivot,
                                                     hkConstraintCore* constraint,
                                                     hkReal* jacobianRow, hkReal* outInvMass)
{
    hkMassAndVelocity* bodyA = constraint->m_bodyA;
    hkMassAndVelocity* bodyB = constraint->m_bodyB;

    jacobianRow[0] = dir[0];
    jacobianRow[1] = dir[1];
    jacobianRow[2] = dir[2];
    jacobianRow[3] = dir[3];

    hkReal rA0 = pivot[0] - bodyA->m_centerOfMass[0];
    hkReal rA1 = pivot[1] - bodyA->m_centerOfMass[1];
    hkReal rA2 = pivot[2] - bodyA->m_centerOfMass[2];
    hkReal rB0 = pivot[0] - bodyB->m_centerOfMass[0];
    hkReal rB1 = pivot[1] - bodyB->m_centerOfMass[1];
    hkReal rB2 = pivot[2] - bodyB->m_centerOfMass[2];

    hkReal cA0 = rA1 * dir[2] - rA2 * dir[1];
    hkReal cA1 = rA2 * dir[0] - rA0 * dir[2];
    hkReal cA2 = rA0 * dir[1] - rA1 * dir[0];

    if (bodyA->m_useInvInertia == 0) {
        jacobianRow[4] = cA0 * bodyA->m_invInertia[0] +
                         (cA1 * bodyA->m_invInertia[4] + cA2 * bodyA->m_invInertia[8]);
        jacobianRow[5] = cA0 * bodyA->m_invInertia[1] +
                         (cA1 * bodyA->m_invInertia[5] + cA2 * bodyA->m_invInertia[9]);
        jacobianRow[6] = cA0 * bodyA->m_invInertia[2] +
                         (cA1 * bodyA->m_invInertia[6] + cA2 * bodyA->m_invInertia[10]);
    } else {
        jacobianRow[4] = cA0;
        jacobianRow[5] = cA1;
        jacobianRow[6] = cA2;
    }
    jacobianRow[7] = 0.0f;

    hkReal cB0 = rB1 * dir[2] - rB2 * dir[1];
    hkReal cB1 = rB2 * dir[0] - rB0 * dir[2];
    hkReal cB2 = rB0 * dir[1] - rB1 * dir[0];

    if (bodyB->m_useInvInertia == 0) {
        jacobianRow[8]  = cB0 * bodyB->m_invInertia[0] +
                          (cB1 * bodyB->m_invInertia[4] + cB2 * bodyB->m_invInertia[8]);
        jacobianRow[9]  = cB0 * bodyB->m_invInertia[1] +
                          (cB1 * bodyB->m_invInertia[5] + cB2 * bodyB->m_invInertia[9]);
        jacobianRow[10] = cB0 * bodyB->m_invInertia[2] +
                          (cB1 * bodyB->m_invInertia[6] + cB2 * bodyB->m_invInertia[10]);
    } else {
        jacobianRow[8]  = cB0;
        jacobianRow[9]  = cB1;
        jacobianRow[10] = cB2;
    }
    jacobianRow[11] = 0.0f;

    hkReal invMass =
        ((((jacobianRow[10] * jacobianRow[10]) * bodyB->m_invInertia[2] +
           (jacobianRow[6]  * jacobianRow[6])  * bodyA->m_invInertia[2]) +
          ((jacobianRow[9]  * jacobianRow[9])  * bodyB->m_invInertia[1] +
           (jacobianRow[5]  * jacobianRow[5])  * bodyA->m_invInertia[1])) +
         ((jacobianRow[8]  * jacobianRow[8])  * bodyB->m_invInertia[0] +
          (jacobianRow[4]  * jacobianRow[4])  * bodyA->m_invInertia[0])) +
        ((bodyB->m_cfmScalar + bodyA->m_cfmScalar) + HK_REAL_EPSILON);

    jacobianRow[11] = invMass;
    hkReal inv = HK_REAL_ONE / invMass;
    jacobianRow[7] = inv;
    *outInvMass = inv;
}

// =========================================================================================================
// 010acb50 -- hkSetInvMassBuildJacobian
// =========================================================================================================
// The hkJacobian accumulator: [0] = byte cursor (out pointer), [1] = type-tag cursor. Each build jacobian
// writes a tag word and one jacobian row (16 bytes here) and bumps both cursors.
struct hkJacobian {
    hkReal* m_cursor;      // +0
    int*    m_typeCursor;  // +4
};

// @ 0x010acb50
extern "C" void hkSetInvMassBuildJacobian(const hkReal* a, const hkReal* b, int /*unused*/, hkJacobian* jac)
{
    hkReal* cur = jac->m_cursor;
    int* typ = jac->m_typeCursor;
    *typ = 0x40411;
    cur[0] = a[0];
    cur[1] = a[1];
    cur[2] = a[2];
    cur[3] = a[3];
    cur[4] = b[0];
    cur[5] = b[1];
    cur[6] = b[2];
    cur[7] = b[3];
    jac->m_typeCursor = typ + 1;
    jac->m_cursor = jac->m_cursor + 8;
}

// =========================================================================================================
// 010acbb0 -- hkAddVelocityBuildJacobian
// =========================================================================================================
// @ 0x010acbb0
extern "C" void hkAddVelocityBuildJacobian(const hkReal* a, int /*unused*/, hkJacobian* jac)
{
    hkReal* cur = jac->m_cursor;
    int* typ = jac->m_typeCursor;
    *typ = 0x40312;
    cur[0] = a[0];
    cur[1] = a[1];
    cur[2] = a[2];
    cur[3] = a[3];
    jac->m_typeCursor = typ + 1;
    jac->m_cursor = jac->m_cursor + 4;
}

// =========================================================================================================
// 010acbf0 -- hkStabilizedBallSocketConstraint::buildJacobian
// =========================================================================================================
// @ 0x010acbf0
extern "C" void hkStabilizedBallSocketConstraintBuildJacobian(const hkReal* dirA, const hkReal* dirB,
                                                              hkReal tauScalar, hkConstraintCore* constraint,
                                                              void* outState)
{
    hkReal* rowBase = *(hkReal**)outState;
    hkMassAndVelocity* bodyA = constraint->m_bodyA;
    hkMassAndVelocity* bodyB = constraint->m_bodyB;

    hkPoweredChain_BuildMotorJacobianRows(dirA, dirB, constraint, outState);

    hkReal nx = rowBase[0x1b];
    hkReal ny = rowBase[0x0f];
    hkReal nz = rowBase[0x03];
    hkReal axisLen = sqrtf(nz * nz + (ny * ny + nx * nx));
    tauScalar = tauScalar * constraint->m_tau;
    if (axisLen <= tauScalar)
        return;

    int count = 3;
    hkReal scale = sqrtf(sqrtf(tauScalar / axisLen));
    hkReal om = 1.0f - scale;

    hkReal pA0 = om * bodyA->m_centerOfMass[0] + scale * dirA[0];
    hkReal pA1 = scale * dirA[1] + om * bodyA->m_centerOfMass[1];
    hkReal pA2 = scale * dirA[2] + om * bodyA->m_centerOfMass[2];
    hkReal pB0 = om * bodyB->m_centerOfMass[0] + scale * dirB[0];
    hkReal pB1 = scale * dirB[1] + om * bodyB->m_centerOfMass[1];
    hkReal pB2 = scale * dirB[2] + om * bodyB->m_centerOfMass[2];

    const hkReal* basis = &hk_identityBasis[0].x + 2;   // 0x015b9b28
    hkReal* row = rowBase + 5;
    int remaining = 3;
    do {
        hkReal* thisRow = rowBase;
        hkReal f1 = constraint->m_stabilizationFactor;
        hkReal f2 = constraint->m_tau;

        thisRow[0] = basis[-2];
        row[-4] = basis[-1];
        row[-3] = basis[0];
        row[-2] = basis[1];

        hkReal rA0 = pA0 - bodyA->m_centerOfMass[0];
        hkReal rA1 = pA1 - bodyA->m_centerOfMass[1];
        hkReal rA2 = pA2 - bodyA->m_centerOfMass[2];
        hkReal rB0 = pB0 - bodyB->m_centerOfMass[0];
        hkReal rB1 = pB1 - bodyB->m_centerOfMass[1];
        hkReal rB2 = pB2 - bodyB->m_centerOfMass[2];

        hkReal cA0 = rA1 * basis[0] - rA2 * basis[-1];
        hkReal cA1 = rA2 * basis[-2] - rA0 * basis[0];
        hkReal cA2 = rA0 * basis[-1] - rA1 * basis[-2];

        if (bodyA->m_useInvInertia == 0) {
            row[-1] = cA0 * bodyA->m_invInertia[0] +
                      (cA1 * bodyA->m_invInertia[4] + cA2 * bodyA->m_invInertia[8]);
            row[0]  = cA1 * bodyA->m_invInertia[1] +
                      (cA2 * bodyA->m_invInertia[5] + cA0 * bodyA->m_invInertia[9]);
            row[1]  = cA1 * bodyA->m_invInertia[2] +
                      (cA2 * bodyA->m_invInertia[6] + cA0 * bodyA->m_invInertia[10]);
        } else {
            row[-1] = cA0;
            row[0]  = cA1;
            row[1]  = cA2;
        }
        row[2] = 0.0f;

        hkReal cB0 = rB1 * basis[0] - rB2 * basis[-1];
        hkReal cB1 = rB2 * basis[-2] - rB0 * basis[0];
        hkReal cB2 = rB0 * basis[-1] - rB1 * basis[-2];

        if (bodyB->m_useInvInertia == 0) {
            row[3] = cB0 * bodyB->m_invInertia[0] +
                     (cB1 * bodyB->m_invInertia[4] + cB2 * bodyB->m_invInertia[8]);
            row[4] = cB0 * bodyB->m_invInertia[1] +
                     (cB1 * bodyB->m_invInertia[5] + cB2 * bodyB->m_invInertia[9]);
            row[5] = cB0 * bodyB->m_invInertia[2] +
                     (cB1 * bodyB->m_invInertia[6] + cB2 * bodyB->m_invInertia[10]);
            row[6] = 0.0f;
        } else {
            row[3] = cB0;
            row[4] = cB1;
            row[5] = cB2;
            row[6] = 0.0f;
        }

        count--;
        hkReal invMass = ((bodyB->m_cfmScalar + bodyA->m_cfmScalar) + HK_REAL_EPSILON) +
            ((((row[5] * row[5]) * bodyB->m_invInertia[2] +
               (row[1] * row[1]) * bodyA->m_invInertia[2]) +
              ((row[4] * row[4]) * bodyB->m_invInertia[1] +
               (row[0] * row[0]) * bodyA->m_invInertia[1])) +
             ((row[3] * row[3]) * bodyB->m_invInertia[0] +
              (row[-1] * row[-1]) * bodyA->m_invInertia[0]));
        row[6] = invMass;
        row[2] = f1 / invMass;

        row[-2] = ((pB2 - pA2) * basis[0] +
                   ((pB1 - pA1) * basis[-1] + (pB0 - pA0) * basis[-2])) * f2;

        row += 0xc;
        basis += 4;
        rowBase = thisRow + 0xc;
    } while (--remaining != 0);

    // (the do/while above runs exactly 3 times; see the count handling)
}

// =========================================================================================================
// 010ad140 -- hkMatrix6::hkMatrix6(const hkMatrix6&)
// =========================================================================================================
// @ 0x010ad140
hkMatrix6::hkMatrix6(const hkMatrix6& o)
{
    hkReal* dst = &m_m[0][0].m_col0.x;
    const hkReal* src = &o.m_m[0][0].m_col0.x;
    int n = 4;
    do {
        dst[0]  = src[0];
        dst[1]  = src[1];
        dst[2]  = src[2];
        dst[3]  = src[3];
        dst[4]  = src[4];
        dst[5]  = src[5];
        dst[6]  = src[6];
        dst[7]  = src[7];
        dst[8]  = src[8];
        dst[9]  = src[9];
        dst[10] = src[10];
        dst[11] = src[11];
        dst += 0xc;
        src += 0xc;
    } while (--n);
}

// =========================================================================================================
// 010ad1c0 -- hkPoweredChain_ApplyMotorStatesToRows
// =========================================================================================================
// @ 0x010ad1c0
extern "C" void hkPoweredChain_ApplyMotorStatesToRows(hkPoweredChainMotorInfo* motorInfo, char notLastRow,
                                                      hkMatrix6* a, hkMatrix6* b)
{
    if (motorInfo->m_motorStates == 0)
        return;

    if ((motorInfo->m_motorStates & 3) != 0) {
        hkReal* p = &a->m_m[0][0].m_col0.x;
        p[0x60/4] = 0.0f; p[0x70/4] = 0.0f; p[0x80/4] = 0.0f;
        p[0x90/4] = 0.0f; p[0xa0/4] = 0.0f; p[0xb0/4] = 0.0f;
        p[0x90/4] = 1.0f;
        if (notLastRow != 0) {
            hkReal* q = &b->m_m[0][0].m_col0.x;
            q[0x60/4] = 0.0f; q[0x70/4] = 0.0f; q[0x80/4] = 0.0f;
            q[0x90/4] = 0.0f; q[0xa0/4] = 0.0f; q[0xb0/4] = 0.0f;
        }
    }
    if ((motorInfo->m_motorStates & 0xc) != 0) {
        hkReal* p = &a->m_m[0][0].m_col0.x;
        p[0x64/4] = 0.0f; p[0x74/4] = 0.0f; p[0x84/4] = 0.0f;
        p[0x94/4] = 0.0f; p[0xa4/4] = 0.0f; p[0xb4/4] = 0.0f;
        p[0xa4/4] = 1.0f;
        if (notLastRow != 0) {
            hkReal* q = &b->m_m[0][0].m_col0.x;
            q[0x64/4] = 0.0f; q[0x74/4] = 0.0f; q[0x84/4] = 0.0f;
            q[0x94/4] = 0.0f; q[0xa4/4] = 0.0f; q[0xb4/4] = 0.0f;
        }
    }
    if ((motorInfo->m_motorStates & 0x30) != 0) {
        hkReal* p = &a->m_m[0][0].m_col0.x;
        p[0x68/4] = 0.0f; p[0x78/4] = 0.0f; p[0x88/4] = 0.0f;
        p[0x98/4] = 0.0f; p[0xa8/4] = 0.0f; p[0xb8/4] = 0.0f;
        p[0xb8/4] = 1.0f;
        if (notLastRow != 0) {
            hkReal* q = &b->m_m[0][0].m_col0.x;
            q[0x68/4] = 0.0f; q[0x78/4] = 0.0f; q[0x88/4] = 0.0f;
            q[0x98/4] = 0.0f; q[0xa8/4] = 0.0f; q[0xb8/4] = 0.0f;
        }
    }
}

// =========================================================================================================
// 010ad2d0 -- hkPoweredChain_DisableMotorInMatrixRow_NextConstraint
// =========================================================================================================
// @ 0x010ad2d0
extern "C" void hkPoweredChain_DisableMotorInMatrixRow_NextConstraint(hkPoweredChainMotorInfo* motorInfo,
                                                                      hkMatrix6* prevOffDiagonal)
{
    if (motorInfo->m_motorStates == 0)
        return;
    hkReal* p = &prevOffDiagonal->m_m[0][0].m_col0.x;
    if ((motorInfo->m_motorStates & 3) != 0) {
        p[0x3c/4] = 0.0f; p[0x38/4] = 0.0f; p[0x34/4] = 0.0f; p[0x30/4] = 0.0f;
        p[0x9c/4] = 0.0f; p[0x98/4] = 0.0f; p[0x94/4] = 0.0f; p[0x90/4] = 0.0f;
    }
    if ((motorInfo->m_motorStates & 0xc) != 0) {
        p[0x4c/4] = 0.0f; p[0x48/4] = 0.0f; p[0x44/4] = 0.0f; p[0x40/4] = 0.0f;
        p[0xac/4] = 0.0f; p[0xa8/4] = 0.0f; p[0xa4/4] = 0.0f; p[0xa0/4] = 0.0f;
    }
    if ((motorInfo->m_motorStates & 0x30) != 0) {
        p[0x5c/4] = 0.0f; p[0x58/4] = 0.0f; p[0x54/4] = 0.0f; p[0x50/4] = 0.0f;
        p[0xbc/4] = 0.0f; p[0xb8/4] = 0.0f; p[0xb4/4] = 0.0f; p[0xb0/4] = 0.0f;
    }
}

// =========================================================================================================
// 010ad360 -- hkPoweredChain_OverwriteVelocityWithExplicitImpulse
// =========================================================================================================
// @ 0x010ad360
extern "C" hkUint8* hkPoweredChain_OverwriteVelocityWithExplicitImpulse(int constraintIndex, int motorIndex,
                                                                    const hkUint8* motorInfos, hkVector4* velocities)
{
    const hkUint8* info = (const hkUint8*)(constraintIndex * 0x4c + (int)motorInfos);
    hkReal* out = (hkReal*)(constraintIndex * 0x20 + (int)velocities);
    unsigned char state = (unsigned char)((info[0] >> ((unsigned char)motorIndex << 1)) & 3);
    if (state == 1) {
        const hkReal& v = *(const hkReal*)(info + motorIndex * 0x18 + 4);
        out[4 + motorIndex] = v;
    } else {
        const hkReal& v = *(const hkReal*)(info + motorIndex * 0x18 + 8);
        out[4 + motorIndex] = v;
    }
    return (hkUint8*)info;
}

// =========================================================================================================
// 010ad0b0 / 010ad020 -- hkConstraintBuildJacobian::buildJacobianAndSetData
// =========================================================================================================
// Both are the same template pattern: reserve `n` jacobian rows from a builder state {cursor, end}, emit a
// per-row header, run the row builder, then advance the cursor.
//   state (int*): [0] = current out pointer, [1] = header/record cursor.
// @ 0x010ad0b0
extern "C" void hkConstraintBuildJacobianAndSetData_16(int n, int d0, int d1, void* a, int* src, void* out1,
                                                       void* out2, void* rec, int* state)
{
    int* hdr = (int*)state[1];
    hdr[2] = d0;
    hdr[3] = d1;
    hdr[1] = n;
    hdr[0] = (n + 5) * 0x40000 | 0xa17;
    {
        int* dst = (int*)((char*)hdr + 0x10);
        for (int i = n + 1; i > 0; i--) {
            *dst = *src;
            dst++;
            src++;
        }
    }
    hkConstraintBuildJacobian_N3(n, a, (char*)hdr + 0x10, out1);
    state[0] = (state[0] + n * 0x10 + 0x13) & ~0xf;
    state[1] = state[1] + *(unsigned short*)((char*)hdr + 2);
}

// @ 0x010ad020
extern "C" void hkConstraintBuildJacobianAndSetData_160(int n, int d0, int d1, void* a, int* src, void* out1,
                                                        void* out2, void* rec, int* state)
{
    int* hdr = (int*)state[1];
    hdr[2] = d0;
    hdr[3] = d1;
    hdr[1] = n;
    hdr[0] = (n + 5) * 0x40000 | 0xb18;
    {
        int* dst = (int*)((char*)hdr + 0x10);
        for (int i = n + 1; i > 0; i--) {
            *dst = *src;
            dst++;
            src++;
        }
    }
    hkConstraintBuildJacobian_N6(n, a, out2, out1);
    state[0] = state[0] + n * 0xa0 + 0x10;
    state[1] = state[1] + *(unsigned short*)((char*)hdr + 2);
}
