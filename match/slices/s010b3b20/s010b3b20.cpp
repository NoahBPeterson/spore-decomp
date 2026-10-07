// Slice s010b3b20 -- Havok 3.1 powered-chain solver driver (0x010b3b20).
//
// Solves one powered chain (a chain of constraints with angular motors) in the Havok solver:
//   1. adds each motor's target velocity to the rhs (w) of its angular Jacobian row;
//   2. computes the chain's rhs velocities (hkPoweredChain_CalculateVelocities) and overwrites the rows
//      of motors that are disabled (state 2: zero, states 1/3: explicit limit impulse);
//   3. solves the block-tridiagonal LU system (0x010aef10) and iterates motor enabling/disabling
//      (ScanAndEnableMotors / ScanAndDisableMotors) with an LU update after every change;
//   4. back-substitutes the final constraint velocities through the decomposition, from the last
//      constraint to the first, and applies the resulting impulses (3 linear + 3 angular rows) to the
//      two velocity accumulators of every constraint, accumulating them in the chain's impulse array.
//
// Module: Havok prebuilt library (x87, 16-byte aligned frame). The original's compiler reassociated the
// hkMatrix3 * hkVector4 row sums differently per row; the sums below are written with the original's
// grouping (read from the disassembly), so the result is bit-identical under any x87 precision.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

#define HK_FORCE_INLINE __forceinline

typedef float hkReal;
typedef unsigned char hkUint8;

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
};

class hkMatrix3 {
public:
    hkVector4 m_col0;
    hkVector4 m_col1;
    hkVector4 m_col2;
};

class hkMatrix6 {
public:
    hkMatrix3 m_m[2][2];   // [row][column]
};

class hkVector8 {
public:
    hkVector4 m_lin;
    hkVector4 m_ang;
};

// Velocity accumulator (only the fields used here).
struct hkVelocityAccumulator {
    hkVector4 m_header;     // +0x00
    hkVector4 m_linearVel;  // +0x10
    hkVector4 m_angularVel; // +0x20
    hkVector4 m_invMasses;  // +0x30 (xyz: angular inverse inertia, w: inverse mass)
};

// One linear row of a chain constraint: linear direction and the angular Jacobians of both bodies.
struct hkp1Lin2AngJacobian {
    hkVector4 m_linear0;
    hkVector4 m_angular[2];
};

// One angular motor row: the angular Jacobians of both bodies; the w of the second carries the rhs.
struct hkp2AngJacobian {
    hkVector4 m_angular[2];
};

// Five 6x6 blocks per constraint of the block-tridiagonal LU decomposition.
struct hkPoweredChainConstraintMatrices {
    hkMatrix6 m_m0;
    hkMatrix6 m_m1;
    hkMatrix6 m_m2;     // +0x180
    hkMatrix6 m_m3;
    hkMatrix6 m_m4;
};

struct hkPoweredChainMotorParams {
    hkReal m_pad0[2];
    hkReal m_targetVelocity;    // +0x08
    hkReal m_tau;               // +0x0c
    hkReal m_damping;           // +0x10
    hkReal m_pad14;
};

struct hkPoweredChainMotorInfo {    // 0x4c bytes
    hkUint8 m_motorStates;          // 2 bits per motor
    hkUint8 m_pad[3];
    hkPoweredChainMotorParams m_motors[3];
};

// Jacobian schema header of the chain (only the fields used here); the motor infos follow the
// numConstraints + 1 accumulator offsets.
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
    hkp1Lin2AngJacobian* m_linearJacobians;             // +0x10 (3 rows per constraint)
    hkp2AngJacobian* m_angularJacobians;                // +0x14 (3 rows per constraint)
    const int* m_accumulatorOffsets;                    // +0x18
    char* m_accumulatorsBase;                           // +0x1c
    hkPoweredChainConstraintMatrices* m_matrices;       // +0x20
    hkPoweredChainMotorInfo* m_motorInfo;               // +0x24
    hkVector8* m_velocities;                            // +0x28 (numConstraints + 1 entries)
    hkVector8* m_rhs;                                   // +0x2c
};

extern "C" void hkPoweredChain_CalculateVelocities(hkPoweredChainSolverInfo* info, hkVector8* rhs);
extern "C" void hkPoweredChain_OverwriteVelocityWithExplicitImpulse(int constraintIndex, int motorIndex,
                                                                    hkPoweredChainMotorInfo* motorInfo,
                                                                    hkVector8* rhs);
// 0x010aef10: solves the LU-decomposed system for the chain velocities.
extern "C" void FUN_010aef10(hkPoweredChainSolverInfo* info, hkVector8* velocities);
extern "C" void hkPoweredChain_ScanAndEnableMotors(hkPoweredChainSolverInfo* info, int* constraintIndexOut,
                                                   int* motorIndexOut, hkReal* maxError,
                                                   hkPoweredChainMotorInfo* motorInfo);
extern "C" void hkPoweredChain_ScanAndDisableMotors(hkPoweredChainSolverInfo* info, int* constraintIndexOut,
                                                    int* motorIndexOut, hkReal* maxError,
                                                    hkPoweredChainMotorInfo* motorInfo);
extern "C" void hkPoweredChain_UpdateLuDecomposition(int constraintIndex, int numConstraints,
                                                     hkPoweredChainMotorInfo* motorInfo,
                                                     hkPoweredChainConstraintMatrices* matrices);
extern "C" void hkPoweredChain_RestoreVelocityValue(int constraintIndex, int motorIndex,
                                                    hkPoweredChainSolverInfo* info, hkVector8* rhs);

// Row k of m * v, summed as (m(k,1)*v1 + m(k,2)*v2) + m(k,0)*v0 (the original's grouping for most rows).
static HK_FORCE_INLINE hkReal mulRowA(const hkMatrix3& m, int k, hkReal v0, hkReal v1, hkReal v2)
{
    return ((&m.m_col1.x)[k] * v1 + (&m.m_col2.x)[k] * v2) + (&m.m_col0.x)[k] * v0;
}

// Row k of m * v, summed as (m(k,1)*v1 + m(k,0)*v0) + m(k,2)*v2.
static HK_FORCE_INLINE hkReal mulRowB(const hkMatrix3& m, int k, hkReal v0, hkReal v1, hkReal v2)
{
    return ((&m.m_col1.x)[k] * v1 + (&m.m_col0.x)[k] * v0) + (&m.m_col2.x)[k] * v2;
}

// Applies an impulse along a linear row to both accumulators.
static HK_FORCE_INLINE void applyLinearImpulse(hkVelocityAccumulator* a, hkVelocityAccumulator* b,
                                               const hkp1Lin2AngJacobian& jac, hkReal imp)
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

// Applies an impulse along an angular row to both accumulators.
static HK_FORCE_INLINE void applyAngularImpulse(hkVelocityAccumulator* a, hkVelocityAccumulator* b,
                                                const hkp2AngJacobian& jac, hkReal imp)
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

// @ 0x010b3b20
void __cdecl hkPoweredChain_Solve(const hkPoweredChainSolverParams* params, char* accumulatorsBase,
                                     hkPoweredChainSchema* schema, char* buffer, hkReal* impulses)
{
    hkPoweredChainSolverInfo info;
    int n = schema->m_numConstraints;
    info.m_params = params;
    info.m_numConstraints = n;
    info.m_tau = schema->m_tau;
    info.m_damping = schema->m_damping;
    info.m_linearJacobians = (hkp1Lin2AngJacobian*)buffer;
    info.m_angularJacobians = (hkp2AngJacobian*)(buffer + n * sizeof(hkp1Lin2AngJacobian) * 3);
    info.m_accumulatorOffsets = schema->m_accumulatorOffsets;
    info.m_accumulatorsBase = accumulatorsBase;
    info.m_matrices = (hkPoweredChainConstraintMatrices*)(buffer + n * 0xf0);
    info.m_motorInfo = (hkPoweredChainMotorInfo*)&schema->m_accumulatorOffsets[n + 1];
    info.m_velocities = (hkVector8*)(buffer + n * 0x4b0);
    info.m_rhs = (hkVector8*)(buffer + n * 0x4d0 + 0x20);

    // Motor target velocities go into the rhs of the angular rows.
    int i;
    for (i = 0; i < info.m_numConstraints; i++) {
        hkp2AngJacobian* jac = &info.m_angularJacobians[i * 3];
        hkPoweredChainMotorInfo& motorInfo = info.m_motorInfo[i];
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
        const hkMatrix6& m = info.m_matrices[i].m_m2;
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

        hkVelocityAccumulator* accA =
            (hkVelocityAccumulator*)(accumulatorsBase + info.m_accumulatorOffsets[i]);
        hkVelocityAccumulator* accB =
            (hkVelocityAccumulator*)(accumulatorsBase + info.m_accumulatorOffsets[i + 1]);
        const hkp1Lin2AngJacobian* lin = &info.m_linearJacobians[i * 3];
        const hkp2AngJacobian* ang = &info.m_angularJacobians[i * 3];
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
