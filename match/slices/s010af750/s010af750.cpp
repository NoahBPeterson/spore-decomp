// Slice s010af750 -- hkPoweredChain_ScanAndEnableMotors (Havok 3.1 powered-chain solver, 0x010af750).
//
// The powered-chain solver keeps, per chain constraint, five hkMatrix6 blocks of its block-tridiagonal
// LU decomposition and a motor record with a 2-bit state per angular motor (0 = enabled; 1/3 = disabled
// at one of the two force limits). This pass walks the chain backwards, back-substituting the stored
// velocities through the decomposition to get each constraint's resulting angular velocity, and compares
// it with the motor's target velocity. Among the disabled motors whose limit is violated it picks the one
// with the largest error, re-enables it (state 0) and returns its constraint and motor index.
//
// Module: Havok prebuilt library (x87, 16-byte aligned frame, compiler-reassociated float sums, i.e.
// /fp:fast). The math is written with the Havok FPU hkVector4/hkMatrix3/hkMatrix6/hkVector8 inline
// helpers (Havok 6 headers: hkFpuVector4.inl, hkMatrix6.h); the transpose stays an out-of-line call
// (_hkMatrix6SetTranspose) as in the original.
#include "types.h"

#define HK_FORCE_INLINE __forceinline

typedef float hkReal;
typedef unsigned char hkUint8;

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
    HK_FORCE_INLINE hkReal& operator()(int i) { return (&x)[i]; }
    HK_FORCE_INLINE const hkReal& operator()(int i) const { return (&x)[i]; }
    HK_FORCE_INLINE void setZero4() { x = y = z = w = 0; }
    HK_FORCE_INLINE void add4(const hkVector4& v) { x += v.x; y += v.y; z += v.z; w += v.w; }
    HK_FORCE_INLINE void setSub4(const hkVector4& v0, const hkVector4& v1) {
        x = v0.x - v1.x; y = v0.y - v1.y; z = v0.z - v1.z; w = v0.w - v1.w;
    }
    HK_FORCE_INLINE void setMul4(const hkVector4& a, const hkVector4& b) {
        x = a.x * b.x; y = a.y * b.y; z = a.z * b.z; w = a.w * b.w;
    }
    HK_FORCE_INLINE void addMul4(const hkVector4& a, const hkVector4& b) {
        x += a.x * b.x; y += a.y * b.y; z += a.z * b.z; w += a.w * b.w;
    }
    HK_FORCE_INLINE void setMul4(hkReal r, const hkVector4& a) {
        x = r * a.x; y = r * a.y; z = r * a.z; w = r * a.w;
    }
    HK_FORCE_INLINE void addMul4(hkReal r, const hkVector4& a) {
        x += r * a.x; y += r * a.y; z += r * a.z; w += r * a.w;
    }
    HK_FORCE_INLINE hkReal horizontalAdd3() const { return x + y + z; }
    HK_FORCE_INLINE void _setMul3(const class hkMatrix3& r, const hkVector4& v);
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
    HK_FORCE_INLINE void setIdentity() {
        setZero();
        hkReal one = 1.0f;
        (*this)(0, 0) = one;
        (*this)(1, 1) = one;
        (*this)(2, 2) = one;
    }
};

HK_FORCE_INLINE void hkVector4::_setMul3(const hkMatrix3& r, const hkVector4& v) {
    hkReal v0 = v(0);
    hkReal v1 = v(1);
    hkReal v2 = v(2);
    hkVector4& t = *this;
    t(0) = r(0, 0) * v0 + r(0, 1) * v1 + r(0, 2) * v2;
    t(1) = r(1, 0) * v0 + r(1, 1) * v1 + r(1, 2) * v2;
    t(2) = r(2, 0) * v0 + r(2, 1) * v1 + r(2, 2) * v2;
    t(3) = 0;
}

class hkMatrix6 {
public:
    hkMatrix3 m_m[2][2];   // [row][column]
    HK_FORCE_INLINE void setIdentity() {
        m_m[0][0].setIdentity();
        m_m[0][1].setZero();
        m_m[1][0].setZero();
        m_m[1][1].setIdentity();
    }
};

class hkVector8 {
public:
    hkVector4 m_lin;
    hkVector4 m_ang;
    HK_FORCE_INLINE void setZero8() { m_lin.setZero4(); m_ang.setZero4(); }
    HK_FORCE_INLINE void add8(const hkVector8& a) { m_lin.add4(a.m_lin); m_ang.add4(a.m_ang); }
    HK_FORCE_INLINE void setSub8(const hkVector8& a, const hkVector8& b) {
        m_lin.setSub4(a.m_lin, b.m_lin);
        m_ang.setSub4(a.m_ang, b.m_ang);
    }
    HK_FORCE_INLINE void _setMul6(const hkMatrix6& a, const hkVector8& b) {
        hkVector4 tmp[2];
        tmp[0]._setMul3(a.m_m[0][0], b.m_lin);
        m_lin._setMul3(a.m_m[0][1], b.m_ang);
        tmp[1]._setMul3(a.m_m[1][0], b.m_lin);
        m_ang._setMul3(a.m_m[1][1], b.m_ang);
        m_lin.add4(tmp[0]);
        m_ang.add4(tmp[1]);
    }
};

extern "C" void hkMatrix6SetTranspose(hkMatrix6& out, const hkMatrix6& in);

// Velocity accumulator of a body in the chain (only the fields used here).
struct hkPoweredChainAccumulator {
    hkVector4 m_linearVel;          // +0x00 (type/padding in the real accumulator header)
    hkVector4 m_pad10;
    hkVector4 m_angularVel;         // +0x20
    hkVector4 m_pad30;
    hkVector4 m_pad40;
    hkVector4 m_originalAngularVel; // +0x50 (scratch: angular velocity before the solver pass)
};

// One angular motor row of a chain constraint: the angular Jacobians of both bodies; the w of the
// second carries the motor's target velocity term.
struct hkPoweredChainJacobianRow {
    hkVector4 m_angularA;
    hkVector4 m_angularB;
};

// Five 6x6 blocks per constraint of the block-tridiagonal LU decomposition.
struct hkPoweredChainConstraintMatrices {
    hkMatrix6 m_m0;
    hkMatrix6 m_m1;
    hkMatrix6 m_m2;
    hkMatrix6 m_m3;
    hkMatrix6 m_m4;
};

struct hkPoweredChainMotorParams {
    hkReal m_pad0[3];
    hkReal m_tau;       // +0x0c
    hkReal m_damping;   // +0x10
    hkReal m_pad14;
};

struct hkPoweredChainMotorInfo {
    hkUint8 m_motorStates;      // 2 bits per motor
    hkUint8 m_pad[3];
    hkPoweredChainMotorParams m_motors[3];
};

struct hkPoweredChainSolverParams {
    hkReal m_pad[16];
    hkReal m_tauScale;          // +0x40
};

struct hkPoweredChainSolverInfo {
    const hkPoweredChainSolverParams* m_params;        // +0x00
    int m_numConstraints;                              // +0x04
    hkReal m_tau;                                      // +0x08
    hkReal m_damping;                                  // +0x0c
    void* m_10;                                        // +0x10
    const hkPoweredChainJacobianRow* m_jacobians;      // +0x14 (3 rows per constraint)
    const int* m_accumulatorOffsets;                   // +0x18 (numConstraints + 1 bodies)
    const char* m_accumulatorsBase;                    // +0x1c
    const hkPoweredChainConstraintMatrices* m_matrices; // +0x20
    hkPoweredChainMotorInfo* m_motorInfo;              // +0x24
    const hkVector8* m_velocities;                     // +0x28 (numConstraints + 1 entries)
};

enum { MOTOR_ENABLED = 0, MOTOR_AT_UPPER_LIMIT = 1, MOTOR_AT_LOWER_LIMIT = 3 };

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
static HK_FORCE_INLINE hkReal hkMath_fabs(hkReal r) { return (hkReal)fabs(r); }

// @ 0x010af750
extern "C" void hkPoweredChain_ScanAndEnableMotors(const hkPoweredChainSolverInfo* info,
                                                   int* constraintIndexOut, int* motorIndexOut)
{
    int bestConstraint = -1;
    int bestMotor = -1;
    hkReal maxError = 0.0f;

    // Back substitution: vel[i] = velocities[i+1] - m2[i] * vel[i+1], starting from a zero vector.
    hkVector8 velNext2;
    hkVector8 velNext;
    velNext.setZero8();
    hkVector8 vel;
    int i = info->m_numConstraints - 1;
    {
        hkVector8 tmp;
        tmp._setMul6(info->m_matrices[i].m_m2, velNext);
        vel.setSub8(info->m_velocities[i + 1], tmp);
    }

    for (; i >= 0; i--) {
        velNext2 = velNext;
        velNext = vel;

        if (i >= 1) {
            hkVector8 tmp;
            tmp._setMul6(info->m_matrices[i - 1].m_m2, velNext);
            vel.setSub8(info->m_velocities[i], tmp);
        } else {
            vel.setZero8();
        }

        hkMatrix6 lower;
        if (i >= 1)
            hkMatrix6SetTranspose(lower, info->m_matrices[i - 1].m_m4);
        else
            lower.setIdentity();

        // Resulting velocity of constraint i.
        hkVector8 result;
        result._setMul6(lower, vel);
        {
            hkVector8 tmp;
            tmp._setMul6(info->m_matrices[i].m_m3, velNext);
            result.add8(tmp);
            tmp._setMul6(info->m_matrices[i].m_m4, velNext2);
            result.add8(tmp);
        }

        hkPoweredChainMotorInfo* motorInfo = &info->m_motorInfo[i];
        int motorStates = motorInfo->m_motorStates;
        for (int j = 0; j < 3; j++) {
            int state = (motorStates >> (j * 2)) & 3;
            if (state == MOTOR_AT_LOWER_LIMIT || state == MOTOR_AT_UPPER_LIMIT) {
                const int* offsets = &info->m_accumulatorOffsets[i];
                const hkPoweredChainAccumulator* accA =
                    (const hkPoweredChainAccumulator*)(info->m_accumulatorsBase + offsets[0]);
                const hkPoweredChainAccumulator* accB =
                    (const hkPoweredChainAccumulator*)(info->m_accumulatorsBase + offsets[1]);
                const hkPoweredChainJacobianRow& jac = info->m_jacobians[i * 3 + j];
                const hkPoweredChainMotorParams& motor = motorInfo->m_motors[j];
                hkReal tau = motor.m_tau;

                hkVector4 deltaA; deltaA.setSub4(accA->m_angularVel, accA->m_originalAngularVel);
                hkVector4 deltaB; deltaB.setSub4(accB->m_angularVel, accB->m_originalAngularVel);
                hkVector4 origA = accA->m_originalAngularVel;
                hkVector4 origB = accB->m_originalAngularVel;

                hkVector4 deltaVel; deltaVel.setMul4(deltaA, jac.m_angularA);
                deltaVel.addMul4(deltaB, jac.m_angularB);
                hkVector4 origVel; origVel.setMul4(origA, jac.m_angularA);
                origVel.addMul4(origB, jac.m_angularB);

                hkVector4 sum;
                sum.setMul4(tau * info->m_params->m_tauScale, origVel);
                sum.addMul4(motor.m_damping, deltaVel);
                hkReal target = tau * jac.m_angularB.w - sum.horizontalAdd3();
                hkReal current = result.m_ang(j);

                bool violated;
                if (state == MOTOR_AT_LOWER_LIMIT)
                    violated = current <= target;
                else
                    violated = current >= target;
                if (violated) {
                    hkReal error = hkMath_fabs(current - target);
                    if (error > maxError) {
                        maxError = error;
                        bestConstraint = i;
                        bestMotor = j;
                    }
                }
            }
        }
    }

    if (bestConstraint >= 0) {
        hkUint8& states = info->m_motorInfo[bestConstraint].m_motorStates;
        int shift = bestMotor * 2;
        states = (hkUint8)((states & ~(3 << shift)) | (MOTOR_ENABLED << shift));
        *constraintIndexOut = bestConstraint;
        *motorIndexOut = bestMotor;
    }
}
