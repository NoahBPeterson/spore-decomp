// Slice s010b48b0 — one function, @ 0x010b48b0 (17,020 bytes).
//
// Havok 3.1.0 (prebuilt library) constraint-solver inner loop: one Gauss-Seidel
// pass over a stream of jacobian schemas.  The schema stream is a sequence of
// variable-size records whose first byte is the schema type (dispatched through a
// 26-entry jump table, 0x00..0x19).  A header schema (type 1) selects the two
// velocity accumulators (bodies A and B) and the jacobian-element cursor; each
// following schema consumes one or more jacobian elements, computes the impulse
// that removes the velocity error, applies it to both accumulators and adds it
// to the solver temp (accumulated impulse) slot of the constraint row.
// Callers: hkConstraintSolverSetup code at 0x010a4a2d/0x010a4a4e and 0x010f2d73/
// 0x010f2d94/0x010f2e60.
//
// The schema-type numbers map onto the Havok 3.1 jacobian builders that emit
// them (symbols/havok_names.txt): 6 hk1dAngularVelocityMotor, 7 hk1dLinearVelocity-
// Motor, 8 hk1dLinearFriction, 0xb hk1dAngularFriction, 0xc hk1dAngularLimit,
// 0xd hk1dLinearLimit, 0xe hk1dAngularBilateral, 0xf hk1dLinearBilateral,
// 0x10 hk1dLinearBilateralUserTau, 0x11 hkSetInvMass, 0x12 hkAddVelocity,
// 0x13/0x14 set/restore tau & damping, 0x15 hkPulley, 0x17/0x18/0x19 stiff-spring /
// ball-socket / powered chains (solved out of line).  4/5 are single/paired contact
// points, 9/10 are 2D/3D friction.
//
// Every path, call, store and side effect of the original is reproduced; float
// sums are grouped per component (x87 /O2 /fp:fast reassociates them anyway), and
// x87 compares keep the original's NaN side (see the comments at each compare).
// Not byte-exact (huge x87 function with a 0xcd4-byte aligned frame).
#include "types.h"
#include <math.h>

struct hkVector4 { float x, y, z, w; };

// hkSolverInfo (dev PDB, size 0x140).
struct hkSolverInfo
{
    float m_one;                                  // +0x00
    float m_tau;                                  // +0x04
    float m_damping;                              // +0x08
    float m_frictionTau;                          // +0x0c
    hkVector4 m_globalAccelerationPerSubStep;     // +0x10
    hkVector4 m_globalAccelerationPerStep;        // +0x20
    hkVector4 m_integrateVelocityFactor;          // +0x30
    hkVector4 m_invIntegrateVelocityFactor;       // +0x40
    char m_rest[0x140 - 0x50];
};

// hkVelocityAccumulator (0x80 bytes; Havok 6 header names, Havok 3.1 offsets).
struct hkVelocityAccumulator
{
    uint8_t m_type;                               // +0x00
    char m_pad01[0xf];
    hkVector4 m_linearVel;                        // +0x10
    hkVector4 m_angularVel;                       // +0x20
    hkVector4 m_invMasses;                        // +0x30  xyz: inverse inertia (core space), w: inverse mass
    hkVector4 m_sumLinearVel;                     // +0x40  scratch0
    hkVector4 m_sumAngularVel;                    // +0x50  scratch1
    char m_scratch23[0x20];                       // +0x60
};

struct hkJacobianElement;

// 0x30 bytes.  m_linear0.w = rhs, m_angular[0].w = inverse effective mass
// (invJacDiag), m_angular[1].w = diagonal of a paired row's 2x2 inverse mass matrix.
struct hk1Lin2AngJacobian
{
    hkVector4 m_linear0;
    hkVector4 m_angular[2];
    hkJacobianElement* next(int n);               // 0x010aa040 (out of line)
};

// 0x20 bytes.  m_angular[0].w = invJacDiag, m_angular[1].w = rhs.
struct hk2AngJacobian
{
    hkVector4 m_angular[2];
};

// 0x40 bytes.  m_linear[0].w = rhs, m_angular[0].w = invJacDiag.
struct hk2Lin2AngJacobian
{
    hkVector4 m_linear[2];
    hkVector4 m_angular[2];
    hkJacobianElement* next(int n);               // 0x010b1d00 (out of line)
};

// ---- schemas ---------------------------------------------------------------------------
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

struct hkJacobianStiffSpringChainSchema : hkJacobianSchema
{
    int m_numConstraints;                         // +0x04 (one temp each)
    hkJacobianElement* getEnd(hkJacobianElement* j);     // 0x010b1d10
};

struct hkJacobianBallSocketChainSchema : hkJacobianSchema
{
    int m_numConstraints;                         // +0x04 (three temps each)
    hkJacobianElement* getEnd(hkJacobianElement* j);     // 0x010b1d30
};

struct hkJacobianPoweredChainSchema : hkJacobianSchema
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

// Out-of-line chain solvers (cdecl): (info, accumulator buffer, schema, first jacobian, temps).
extern "C" void hkSolveStiffSpringChain(hkSolverInfo& info, char* accumulators, hkJacobianStiffSpringChainSchema* schema,
                                        hkJacobianElement* jac, float* temp);   // 0x010b22a0
extern "C" void hkSolveBallSocketChain(hkSolverInfo& info, char* accumulators, hkJacobianBallSocketChainSchema* schema,
                                       hkJacobianElement* jac, float* temp);    // 0x010b2890
extern "C" void hkSolvePoweredChain(hkSolverInfo& info, char* accumulators, hkJacobianPoweredChainSchema* schema,
                                    hkJacobianElement* jac, float* temp);       // 0x010b3b20

// ---- jacobian helpers (Havok inline math) ---------------------------------------------

// J * (vA - vB) for a 1Lin2Ang row.
static inline float getVelocity(const hk1Lin2AngJacobian& j, const hkVelocityAccumulator& a, const hkVelocityAccumulator& b)
{
    return ((a.m_linearVel.x - b.m_linearVel.x) * j.m_linear0.x + a.m_angularVel.x * j.m_angular[0].x + b.m_angularVel.x * j.m_angular[1].x)
         + ((a.m_linearVel.y - b.m_linearVel.y) * j.m_linear0.y + a.m_angularVel.y * j.m_angular[0].y + b.m_angularVel.y * j.m_angular[1].y)
         + ((a.m_linearVel.z - b.m_linearVel.z) * j.m_linear0.z + a.m_angularVel.z * j.m_angular[0].z + b.m_angularVel.z * j.m_angular[1].z);
}

// J * (wA, wB) for a 2Ang row.
static inline float getAngularVelocity(const hk2AngJacobian& j, const hkVelocityAccumulator& a, const hkVelocityAccumulator& b)
{
    return (a.m_angularVel.x * j.m_angular[0].x + b.m_angularVel.x * j.m_angular[1].x)
         + (a.m_angularVel.y * j.m_angular[0].y + b.m_angularVel.y * j.m_angular[1].y)
         + (a.m_angularVel.z * j.m_angular[0].z + b.m_angularVel.z * j.m_angular[1].z);
}

// J * (vA - vB) for a 2Lin2Ang (pulley) row: each body has its own linear part.
static inline float getVelocity(const hk2Lin2AngJacobian& j, const hkVelocityAccumulator& a, const hkVelocityAccumulator& b)
{
    return ((a.m_linearVel.x * j.m_linear[0].x - b.m_linearVel.x * j.m_linear[1].x) + (a.m_angularVel.x * j.m_angular[0].x + b.m_angularVel.x * j.m_angular[1].x))
         + ((a.m_linearVel.y * j.m_linear[0].y - b.m_linearVel.y * j.m_linear[1].y) + (a.m_angularVel.y * j.m_angular[0].y + b.m_angularVel.y * j.m_angular[1].y))
         + ((a.m_linearVel.z * j.m_linear[0].z - b.m_linearVel.z * j.m_linear[1].z) + (a.m_angularVel.z * j.m_angular[0].z + b.m_angularVel.z * j.m_angular[1].z));
}

// Velocity seen by a user-tau row: the step-summed velocity weighted by tauFactor plus
// the velocity change since the sum weighted by dampFactor (1Lin2Ang).
static inline float getUserTauVelocity(const hk1Lin2AngJacobian& j, const hkVelocityAccumulator& a, const hkVelocityAccumulator& b,
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

// Same for a 2Ang row (angular velocities only).
static inline float getUserTauAngularVelocity(const hk2AngJacobian& j, const hkVelocityAccumulator& a, const hkVelocityAccumulator& b,
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

static inline void applyImpulse(const hk1Lin2AngJacobian& j, hkVelocityAccumulator& a, hkVelocityAccumulator& b, float impulse)
{
    const float ia = impulse * a.m_invMasses.w;
    const float ib = impulse * b.m_invMasses.w;
    a.m_linearVel.x += ia * j.m_linear0.x;
    a.m_linearVel.y += ia * j.m_linear0.y;
    a.m_linearVel.z += ia * j.m_linear0.z;
    b.m_linearVel.x -= ib * j.m_linear0.x;
    b.m_linearVel.y -= ib * j.m_linear0.y;
    b.m_linearVel.z -= ib * j.m_linear0.z;
    a.m_angularVel.x += (impulse * a.m_invMasses.x) * j.m_angular[0].x;
    a.m_angularVel.y += (impulse * a.m_invMasses.y) * j.m_angular[0].y;
    a.m_angularVel.z += (impulse * a.m_invMasses.z) * j.m_angular[0].z;
    b.m_angularVel.x += (impulse * b.m_invMasses.x) * j.m_angular[1].x;
    b.m_angularVel.y += (impulse * b.m_invMasses.y) * j.m_angular[1].y;
    b.m_angularVel.z += (impulse * b.m_invMasses.z) * j.m_angular[1].z;
}

static inline void applyAngularImpulse(const hk2AngJacobian& j, hkVelocityAccumulator& a, hkVelocityAccumulator& b, float impulse)
{
    a.m_angularVel.x += (impulse * a.m_invMasses.x) * j.m_angular[0].x;
    a.m_angularVel.y += (impulse * a.m_invMasses.y) * j.m_angular[0].y;
    a.m_angularVel.z += (impulse * a.m_invMasses.z) * j.m_angular[0].z;
    b.m_angularVel.x += (impulse * b.m_invMasses.x) * j.m_angular[1].x;
    b.m_angularVel.y += (impulse * b.m_invMasses.y) * j.m_angular[1].y;
    b.m_angularVel.z += (impulse * b.m_invMasses.z) * j.m_angular[1].z;
}

static inline void applyImpulse(const hk2Lin2AngJacobian& j, hkVelocityAccumulator& a, hkVelocityAccumulator& b, float impulse)
{
    const float ia = impulse * a.m_invMasses.w;
    const float ib = impulse * b.m_invMasses.w;
    a.m_linearVel.x += ia * j.m_linear[0].x;
    a.m_linearVel.y += ia * j.m_linear[0].y;
    a.m_linearVel.z += ia * j.m_linear[0].z;
    b.m_linearVel.x -= ib * j.m_linear[1].x;
    b.m_linearVel.y -= ib * j.m_linear[1].y;
    b.m_linearVel.z -= ib * j.m_linear[1].z;
    a.m_angularVel.x += (impulse * a.m_invMasses.x) * j.m_angular[0].x;
    a.m_angularVel.y += (impulse * a.m_invMasses.y) * j.m_angular[0].y;
    a.m_angularVel.z += (impulse * a.m_invMasses.z) * j.m_angular[0].z;
    b.m_angularVel.x += (impulse * b.m_invMasses.x) * j.m_angular[1].x;
    b.m_angularVel.y += (impulse * b.m_invMasses.y) * j.m_angular[1].y;
    b.m_angularVel.z += (impulse * b.m_invMasses.z) * j.m_angular[1].z;
}

// Two contact points sharing one body pair (type 5): solve the 2x2 LCP.  Both
// impulses must come out positive, otherwise each row is retried on its own.
static inline void solvePairContact(const hkJacobianPairContactSchema& s, const hk1Lin2AngJacobian* j,
                                    hkVelocityAccumulator& a, hkVelocityAccumulator& b, float* temp)
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

// Clamp |impulse| to maxImpulse, recording the ratio when clamped (friction rows).
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

// Clamp a motor impulse to [minImpulse, maxImpulse], recording bound/impulse when clamped.
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

// @ 0x010b48b0
void hkSolver_solveJacobianSchemas(hkSolverInfo& info, hkJacobianSchema* schemas, char* accumulators,
                                   hkJacobianElement* jacobians, float* temp)
{
    float savedDamping = info.m_damping;
    float savedTau = info.m_tau;

    char* s = (char*)schemas;
    char* jac;
    hkVelocityAccumulator* a;
    hkVelocityAccumulator* b;

header:
    {
        const hkJacobianHeaderSchema* h = (const hkJacobianHeaderSchema*)s;
        a = (hkVelocityAccumulator*)(accumulators + h->m_bodyAOffset);
        b = (hkVelocityAccumulator*)(accumulators + h->m_bodyBOffset);
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
            applyAngularImpulse(ja, *a, *b, va);
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
                applyAngularImpulse(j, *a, *b, impulse);
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
                applyAngularImpulse(j, *a, *b, impulse);
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
                    applyAngularImpulse(j, *a, *b, impulse);
                    *temp += impulse;
                }
                else
                {
                    const float dMin = v - ls.m_minRhs;
                    if (dMin < 0.0f)
                    {
                        const float impulse = dMin * j.m_angular[0].w;
                        applyAngularImpulse(j, *a, *b, impulse);
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
                    const float impulse = dMax * j.m_angular[0].w;
                    applyImpulse(j, *a, *b, impulse);
                    *temp += impulse;
                }
                const float dMin = v - ls.m_minRhs;
                if (dMin < 0.0f)
                {
                    const float impulse = dMin * j.m_angular[0].w;
                    applyImpulse(j, *a, *b, impulse);
                    *temp += impulse;
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
                applyAngularImpulse(j, *a, *b, impulse);
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
            const hkVector4* m = (const hkVector4*)jac;
            a->m_invMasses = m[0];
            b->m_invMasses = m[1];
            jac += 2 * sizeof(hkVector4);
            s += ((hkJacobianSchema*)s)->m_size;
            break;
        }

        case SCHEMA_ADD_VELOCITY:
        {
            const hkVector4& dv = *(const hkVector4*)jac;
            jac += sizeof(hkVector4);
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
            hkJacobianStiffSpringChainSchema* cs = (hkJacobianStiffSpringChainSchema*)s;
            hkSolveStiffSpringChain(info, accumulators, cs, (hkJacobianElement*)jac, temp);
            temp += cs->m_numConstraints;
            jac = (char*)cs->getEnd((hkJacobianElement*)jac);
            s += cs->m_size;
            break;
        }

        case SCHEMA_BALL_SOCKET_CHAIN:
        {
            hkJacobianBallSocketChainSchema* cs = (hkJacobianBallSocketChainSchema*)s;
            hkSolveBallSocketChain(info, accumulators, cs, (hkJacobianElement*)jac, temp);
            temp += cs->m_numConstraints * 3;
            jac = (char*)cs->getEnd((hkJacobianElement*)jac);
            s += cs->m_size;
            break;
        }

        case SCHEMA_POWERED_CHAIN:
        {
            hkJacobianPoweredChainSchema* cs = (hkJacobianPoweredChainSchema*)s;
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
