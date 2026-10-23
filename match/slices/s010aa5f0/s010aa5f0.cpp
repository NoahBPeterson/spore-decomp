// match/slices/s010aa5f0/s010aa5f0.cpp
// Slice s010aa5f0 -- Havok 3.1.0 1-D constraint Jacobian builders (SporeApp.exe 0x010aa5f0..0x010ab2c2).
//
//  010aa5f0  _hk1dLinearFrictionBuildJacobian
//  010aa890  _hk1dLinearBilateralConstraintBuildJacobian
//  010aab50  _hk1dLinearBilateralConstraintUserTauBuildJacobian
//  010aae10  _hk1dLinearLimitBuildJacobian
//  010ab0e0  _hk1dAngularLimitBuildJacobian
//
// Flags: /vc71 /O2 /MD /Gy /TP  (Havok 3.1.0 prebuilt library, cl 13.10, x87)
#include "types.h"

typedef float hkReal;
typedef unsigned char hkUint8;
typedef unsigned int u32;

// ---- math ---------------------------------------------------------------------------------------------
class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
    hkReal& operator()(int i) { return (&x)[i]; }
};

// ---- the two rigid bodies the constraint owns ---------------------------------------------------------
// A hkRigidBody-like motion holder: the two bodies hang off the constraint at +0x28/+0x2c, each carrying a
// hkMotionState at +0x30 whose inertia diagonal / cfm row / centre of mass / world inverse inertia start
// at the offsets used below.
struct hkMassAndVelocity {
    hkUint8  m_pad0[0xc];
    hkUint8  m_useInvInertia;      // +0x0c  (0 = use the full inertia rows, nonzero = identity)
    hkUint8  m_pad1[0x03];
    hkReal   m_invMassScalar;      // +0x10
    hkReal   m_f14;                // +0x14
    hkReal   m_f18;                // +0x18
    hkReal   m_f1c;                // +0x1c
    hkUint8  m_pad2[0x10];         // +0x20 .. 0x2f
    hkReal   m_diagX;              // +0x30
    hkReal   m_diagY;              // +0x34
    hkReal   m_diagZ;              // +0x38
    hkReal   m_cfmScalar;          // +0x3c
    hkReal   m_centerOfMass[3];    // +0x40
    hkUint8  m_pad3[0x04];         // +0x4c
    hkReal   m_invInertia[9];      // +0x50 world inverse inertia (3x3, column stride 0x10)
};

// The constraint that owns the two bodies: +0x28 / +0x2c point at the hkMassAndVelocity states.
struct hkConstraintCore {
    hkUint8 m_pad0[0x14];
    hkReal  m_f14;                 // +0x14
    hkReal  m_f18;                 // +0x18
    hkUint8 m_pad1[0x0c];          // +0x1c .. 0x27
    hkMassAndVelocity* m_bodyA;    // +0x28
    hkMassAndVelocity* m_bodyB;    // +0x2c
};

// The hkJacobian accumulator: [0] = byte cursor (out pointer), [1] = type-tag cursor.
struct hkJacobian {
    void* m_cursor;                // +0
    void* m_typeCursor;            // +4
};

extern hkReal HK_REAL_EPSILON;     // 0x014a23a4 (FLT_EPSILON)
extern hkReal HK_REAL_ONE;         // 0x01485720 (1.0f)

// =========================================================================================================
// 010aa5f0 -- _hk1dLinearFrictionBuildJacobian
// =========================================================================================================
// @ 0x010aa5f0
extern "C" void FUN_010aa5f0(hkReal* a, hkConstraintCore* c, hkJacobian* out)
{
    hkReal* dst = (hkReal*)out->m_cursor;
    hkMassAndVelocity* bodyA = c->m_bodyA;
    hkReal tau = c->m_f18;
    hkMassAndVelocity* bodyB = c->m_bodyB;

    dst[0] = a[4];
    dst[1] = a[5];
    dst[2] = a[6];
    dst[3] = a[7];

    hkVector4 rA, rB;
    rA.x = a[0] - bodyA->m_centerOfMass[0];
    rA.y = a[1] - bodyA->m_centerOfMass[1];
    rA.z = a[2] - bodyA->m_centerOfMass[2];
    rB.x = a[0] - bodyB->m_centerOfMass[0];
    rB.y = a[1] - bodyB->m_centerOfMass[1];
    rB.z = a[2] - bodyB->m_centerOfMass[2];

    hkReal cA0 = rA.y * a[6] - rA.z * a[5];
    hkReal cA1 = rA.z * a[4] - rA.x * a[6];
    hkReal cA2 = rA.x * a[5] - rA.y * a[4];

    if (bodyA->m_useInvInertia == 0) {
        dst[4] = cA0 * bodyA->m_invInertia[0] +
                 (cA1 * bodyA->m_invInertia[4] + cA2 * bodyA->m_invInertia[8]);
        dst[5] = cA0 * bodyA->m_invInertia[1] +
                 (cA1 * bodyA->m_invInertia[5] + cA2 * bodyA->m_invInertia[9]);
        dst[6] = cA0 * bodyA->m_invInertia[2] +
                 (cA1 * bodyA->m_invInertia[6] + cA2 * bodyA->m_invInertia[10]);
    } else {
        dst[4] = cA0;
        dst[5] = cA1;
        dst[6] = cA2;
    }
    dst[7] = 0.0f;

    hkReal cB0 = rB.z * a[5] - rB.y * a[6];
    hkReal cB1 = rB.x * a[6] - rB.z * a[4];
    hkReal cB2 = rB.y * a[4] - rB.x * a[5];

    if (bodyB->m_useInvInertia == 0) {
        dst[8]  = cB0 * bodyB->m_invInertia[0] +
                  (cB1 * bodyB->m_invInertia[4] + cB2 * bodyB->m_invInertia[8]);
        dst[9]  = cB0 * bodyB->m_invInertia[1] +
                  (cB1 * bodyB->m_invInertia[5] + cB2 * bodyB->m_invInertia[9]);
        dst[10] = cB0 * bodyB->m_invInertia[2] +
                  (cB1 * bodyB->m_invInertia[6] + cB2 * bodyB->m_invInertia[10]);
        dst[11] = 0.0f;
    } else {
        dst[8]  = cB0;
        dst[9]  = cB1;
        dst[10] = cB2;
        dst[11] = 0.0f;
    }

    hkReal invMass =
        ((((dst[10] * dst[10]) * bodyB->m_invInertia[2] +
           (dst[6]  * dst[6])  * bodyA->m_invInertia[2]) +
          ((dst[9]  * dst[9])  * bodyB->m_invInertia[1] +
           (dst[5]  * dst[5])  * bodyA->m_invInertia[1])) +
         ((dst[8]  * dst[8])  * bodyB->m_invInertia[0] +
          (dst[4]  * dst[4])  * bodyA->m_invInertia[0])) +
        ((bodyB->m_cfmScalar + bodyA->m_cfmScalar) + HK_REAL_EPSILON);

    dst[11] = invMass;
    dst[7]  = tau / invMass;

    hkReal g1 = *(hkReal*)((char*)(*(int*)(a + 9)) + 4);
    hkReal* p = (hkReal*)out->m_typeCursor;
    hkReal g3 = a[8];
    hkReal g4 = *(hkReal*)c;
    ((u32*)p)[0] = 0xc0508;
    ((u32*)p)[2] = 0x3f800000;
    p[1] = g3 * g4;
    out->m_cursor = dst + 0xc;
    out->m_typeCursor = p + 3;
    dst[3] = g1 * c->m_f14;
}

// =========================================================================================================
// 010aa890 -- _hk1dLinearBilateralConstraintBuildJacobian
// =========================================================================================================
// @ 0x010aa890
extern "C" void FUN_010aa890(hkReal* a, hkConstraintCore* c, hkJacobian* out)
{
    hkMassAndVelocity* bodyA = c->m_bodyA;
    hkReal tau = c->m_f18;
    hkMassAndVelocity* bodyB = c->m_bodyB;
    hkReal f4 = c->m_f14;
    hkReal* dst = (hkReal*)out->m_cursor;
    hkReal* p = (hkReal*)out->m_typeCursor;

    dst[0] = a[8];
    dst[1] = a[9];
    dst[2] = a[10];
    dst[3] = a[0xb];

    hkVector4 rA, rB;
    rA.x = a[0] - bodyA->m_centerOfMass[0];
    rA.y = a[1] - bodyA->m_centerOfMass[1];
    rA.z = a[2] - bodyA->m_centerOfMass[2];
    rB.x = a[4] - bodyB->m_centerOfMass[0];
    rB.y = a[5] - bodyB->m_centerOfMass[1];
    rB.z = a[6] - bodyB->m_centerOfMass[2];

    hkReal cA0 = rA.y * a[10] - rA.z * a[9];
    hkReal cA1 = rA.z * a[8] - rA.x * a[10];
    hkReal cA2 = rA.x * a[9] - rA.y * a[8];

    if (bodyA->m_useInvInertia == 0) {
        dst[4] = cA0 * bodyA->m_invInertia[0] +
                 (cA1 * bodyA->m_invInertia[4] + cA2 * bodyA->m_invInertia[8]);
        dst[5] = cA0 * bodyA->m_invInertia[1] +
                 (cA1 * bodyA->m_invInertia[5] + cA2 * bodyA->m_invInertia[9]);
        dst[6] = cA0 * bodyA->m_invInertia[2] +
                 (cA1 * bodyA->m_invInertia[6] + cA2 * bodyA->m_invInertia[10]);
    } else {
        dst[4] = cA0;
        dst[5] = cA1;
        dst[6] = cA2;
    }
    dst[7] = 0.0f;

    hkReal cB0 = rB.z * a[9] - rB.y * a[10];
    hkReal cB1 = rB.x * a[10] - rB.z * a[8];
    hkReal cB2 = rB.y * a[8] - rB.x * a[9];

    if (bodyB->m_useInvInertia == 0) {
        dst[8]  = cB0 * bodyB->m_invInertia[0] +
                  (cB1 * bodyB->m_invInertia[4] + cB2 * bodyB->m_invInertia[8]);
        dst[9]  = cB0 * bodyB->m_invInertia[1] +
                  (cB1 * bodyB->m_invInertia[5] + cB2 * bodyB->m_invInertia[9]);
        dst[10] = cB0 * bodyB->m_invInertia[2] +
                  (cB1 * bodyB->m_invInertia[6] + cB2 * bodyB->m_invInertia[10]);
        dst[11] = 0.0f;
    } else {
        dst[8]  = cB0;
        dst[9]  = cB1;
        dst[10] = cB2;
        dst[11] = 0.0f;
    }

    hkReal invMass =
        ((((dst[10] * dst[10]) * bodyB->m_invInertia[2] +
           (dst[6]  * dst[6])  * bodyA->m_invInertia[2]) +
          ((dst[9]  * dst[9])  * bodyB->m_invInertia[1] +
           (dst[5]  * dst[5])  * bodyA->m_invInertia[1])) +
         ((dst[8]  * dst[8])  * bodyB->m_invInertia[0] +
          (dst[4]  * dst[4])  * bodyA->m_invInertia[0])) +
        ((bodyB->m_cfmScalar + bodyA->m_cfmScalar) + HK_REAL_EPSILON);

    dst[11] = invMass;
    dst[7]  = tau / invMass;

    dst[3] = ((a[5] - a[1]) * a[9] +
              ((a[6] - a[2]) * a[10] + (a[4] - a[0]) * a[8])) * f4;

    ((u32*)p)[0] = 0x4050f;
    out->m_cursor = dst + 0xc;
    out->m_typeCursor = p + 1;
}

// =========================================================================================================
// 010aab50 -- _hk1dLinearBilateralConstraintUserTauBuildJacobian
// =========================================================================================================
// @ 0x010aab50
extern "C" void FUN_010aab50(hkReal* a, hkConstraintCore* c, hkJacobian* out)
{
    hkMassAndVelocity* bodyA = c->m_bodyA;
    hkReal tau = c->m_f14;
    hkMassAndVelocity* bodyB = c->m_bodyB;
    hkReal* dst = (hkReal*)out->m_cursor;
    hkReal* p = (hkReal*)out->m_typeCursor;

    dst[0] = a[8];
    dst[1] = a[9];
    dst[2] = a[10];
    dst[3] = a[0xb];

    hkVector4 rA, rB;
    rA.x = a[0] - bodyA->m_centerOfMass[0];
    rA.y = a[1] - bodyA->m_centerOfMass[1];
    rA.z = a[2] - bodyA->m_centerOfMass[2];
    rB.x = a[4] - bodyB->m_centerOfMass[0];
    rB.y = a[5] - bodyB->m_centerOfMass[1];
    rB.z = a[6] - bodyB->m_centerOfMass[2];

    hkReal cA0 = rA.y * a[10] - rA.z * a[9];
    hkReal cA1 = rA.z * a[8] - rA.x * a[10];
    hkReal cA2 = rA.x * a[9] - rA.y * a[8];

    if (bodyA->m_useInvInertia == 0) {
        dst[4] = cA0 * bodyA->m_invInertia[0] +
                 (cA1 * bodyA->m_invInertia[4] + cA2 * bodyA->m_invInertia[8]);
        dst[5] = cA0 * bodyA->m_invInertia[1] +
                 (cA1 * bodyA->m_invInertia[5] + cA2 * bodyA->m_invInertia[9]);
        dst[6] = cA0 * bodyA->m_invInertia[2] +
                 (cA1 * bodyA->m_invInertia[6] + cA2 * bodyA->m_invInertia[10]);
    } else {
        dst[4] = cA0;
        dst[5] = cA1;
        dst[6] = cA2;
    }
    dst[7] = 0.0f;

    hkReal cB0 = rB.z * a[9] - rB.y * a[10];
    hkReal cB1 = rB.x * a[10] - rB.z * a[8];
    hkReal cB2 = rB.y * a[8] - rB.x * a[9];

    if (bodyB->m_useInvInertia == 0) {
        dst[8]  = cB0 * bodyB->m_invInertia[0] +
                  (cB1 * bodyB->m_invInertia[4] + cB2 * bodyB->m_invInertia[8]);
        dst[9]  = cB0 * bodyB->m_invInertia[1] +
                  (cB1 * bodyB->m_invInertia[5] + cB2 * bodyB->m_invInertia[9]);
        dst[10] = cB0 * bodyB->m_invInertia[2] +
                  (cB1 * bodyB->m_invInertia[6] + cB2 * bodyB->m_invInertia[10]);
        dst[11] = 0.0f;
    } else {
        dst[8]  = cB0;
        dst[9]  = cB1;
        dst[10] = cB2;
        dst[11] = 0.0f;
    }

    hkReal invMass =
        ((((dst[10] * dst[10]) * bodyB->m_invInertia[2] +
           (dst[6]  * dst[6])  * bodyA->m_invInertia[2]) +
          ((dst[9]  * dst[9])  * bodyB->m_invInertia[1] +
           (dst[5]  * dst[5])  * bodyA->m_invInertia[1])) +
         ((dst[8]  * dst[8])  * bodyB->m_invInertia[0] +
          (dst[4]  * dst[4])  * bodyA->m_invInertia[0])) +
        ((bodyB->m_cfmScalar + bodyA->m_cfmScalar) + HK_REAL_EPSILON);

    dst[11] = invMass;
    dst[7]  = HK_REAL_ONE / invMass;

    dst[3] = ((a[6] - a[2]) * a[10] +
              ((a[5] - a[1]) * a[9] + (a[4] - a[0]) * a[8])) * tau;

    p[1] = a[0xc];
    ((u32*)p)[0] = 0xc0510;
    p[2] = a[0xd];
    out->m_cursor = dst + 0xc;
    out->m_typeCursor = p + 3;
}

// =========================================================================================================
// 010aae10 -- _hk1dLinearLimitBuildJacobian
// =========================================================================================================
// @ 0x010aae10
extern "C" void FUN_010aae10(hkReal* a, hkConstraintCore* c, hkJacobian* out)
{
    hkReal* dst = (hkReal*)out->m_cursor;
    hkReal f4 = c->m_f14;
    hkReal tau = c->m_f18;
    hkMassAndVelocity* bodyA = c->m_bodyA;
    hkMassAndVelocity* bodyB = c->m_bodyB;

    dst[0] = a[8];
    dst[1] = a[9];
    dst[2] = a[10];
    dst[3] = a[0xb];

    hkVector4 rA, rB;
    rA.x = a[0] - bodyA->m_centerOfMass[0];
    rA.y = a[1] - bodyA->m_centerOfMass[1];
    rA.z = a[2] - bodyA->m_centerOfMass[2];
    rB.x = a[4] - bodyB->m_centerOfMass[0];
    rB.y = a[5] - bodyB->m_centerOfMass[1];
    rB.z = a[6] - bodyB->m_centerOfMass[2];

    hkReal cA0 = rA.y * a[10] - rA.z * a[9];
    hkReal cA1 = rA.z * a[8] - rA.x * a[10];
    hkReal cA2 = rA.x * a[9] - rA.y * a[8];

    if (bodyA->m_useInvInertia == 0) {
        dst[4] = cA0 * bodyA->m_invInertia[0] +
                 (cA1 * bodyA->m_invInertia[4] + cA2 * bodyA->m_invInertia[8]);
        dst[5] = cA0 * bodyA->m_invInertia[1] +
                 (cA1 * bodyA->m_invInertia[5] + cA2 * bodyA->m_invInertia[9]);
        dst[6] = cA0 * bodyA->m_invInertia[2] +
                 (cA1 * bodyA->m_invInertia[6] + cA2 * bodyA->m_invInertia[10]);
    } else {
        dst[4] = cA0;
        dst[5] = cA1;
        dst[6] = cA2;
    }
    dst[7] = 0.0f;

    hkReal cB0 = rB.z * a[9] - rB.y * a[10];
    hkReal cB1 = rB.x * a[10] - rB.z * a[8];
    hkReal cB2 = rB.y * a[8] - rB.x * a[9];

    if (bodyB->m_useInvInertia == 0) {
        dst[8]  = cB0 * bodyB->m_invInertia[0] +
                  (cB1 * bodyB->m_invInertia[4] + cB2 * bodyB->m_invInertia[8]);
        dst[9]  = cB0 * bodyB->m_invInertia[1] +
                  (cB1 * bodyB->m_invInertia[5] + cB2 * bodyB->m_invInertia[9]);
        dst[10] = cB0 * bodyB->m_invInertia[2] +
                  (cB1 * bodyB->m_invInertia[6] + cB2 * bodyB->m_invInertia[10]);
        dst[11] = 0.0f;
    } else {
        dst[8]  = cB0;
        dst[9]  = cB1;
        dst[10] = cB2;
        dst[11] = 0.0f;
    }

    hkReal invMass =
        ((((dst[10] * dst[10]) * bodyB->m_invInertia[2] +
           (dst[6]  * dst[6])  * bodyA->m_invInertia[2]) +
          ((dst[9]  * dst[9])  * bodyB->m_invInertia[1] +
           (dst[5]  * dst[5])  * bodyA->m_invInertia[1])) +
         ((dst[8]  * dst[8])  * bodyB->m_invInertia[0] +
          (dst[4]  * dst[4])  * bodyA->m_invInertia[0])) +
        ((bodyB->m_cfmScalar + bodyA->m_cfmScalar) + HK_REAL_EPSILON);

    dst[11] = invMass;
    dst[7]  = tau / invMass;

    dst[3] = ((a[6] - a[2]) * a[10] +
              ((a[4] - a[0]) * a[8] + (a[5] - a[1]) * a[9])) * f4;

    hkReal f1b = c->m_f14;
    hkReal f4b = a[0xc];
    hkReal f2b = a[0xd];
    hkReal* p = (hkReal*)out->m_typeCursor;
    ((u32*)p)[0] = 0xc050d;
    p[1] = -f1b * f4b;
    p[2] = -f1b * f2b;
    out->m_cursor = dst + 0xc;
    out->m_typeCursor = p + 3;
}

// =========================================================================================================
// 010ab0e0 -- _hk1dAngularLimitBuildJacobian
// =========================================================================================================
// @ 0x010ab0e0
extern "C" void FUN_010ab0e0(hkReal* a, hkConstraintCore* c, hkJacobian* out)
{
    hkReal f1 = a[7];
    hkReal* dst = (hkReal*)out->m_cursor;
    hkMassAndVelocity* bodyB = c->m_bodyB;
    hkMassAndVelocity* bodyA = c->m_bodyA;
    hkReal* p = (hkReal*)out->m_typeCursor;

    if (bodyA->m_useInvInertia == 0) {
        hkReal x = a[0];
        hkReal y = a[1];
        hkReal z = a[2];
        dst[0] = x * bodyA->m_invInertia[0] +
                 (y * bodyA->m_invInertia[4] + z * bodyA->m_invInertia[8]);
        dst[1] = x * bodyA->m_invInertia[1] +
                 (y * bodyA->m_invInertia[5] + z * bodyA->m_invInertia[9]);
        dst[2] = x * bodyA->m_invInertia[2] +
                 (y * bodyA->m_invInertia[6] + z * bodyA->m_invInertia[10]);
        dst[3] = 0.0f;
    } else {
        dst[0] = a[0];
        dst[1] = a[1];
        dst[2] = a[2];
        dst[3] = a[3];
    }

    hkReal nx = -a[0];
    if (bodyB->m_useInvInertia == 0) {
        hkReal ny = -a[1];
        hkReal nz = -a[2];
        dst[4] = nx * bodyB->m_invInertia[0] +
                 (nz * bodyB->m_invInertia[8] + ny * bodyB->m_invInertia[4]);
        dst[5] = nz * bodyB->m_invInertia[9] +
                 (ny * bodyB->m_invInertia[5] + nx * bodyB->m_invInertia[1]);
        dst[6] = nz * bodyB->m_invInertia[10] +
                 (ny * bodyB->m_invInertia[6] + nx * bodyB->m_invInertia[2]);
        dst[7] = 0.0f;
    } else {
        dst[4] = nx;
        dst[5] = -a[1];
        dst[6] = -a[2];
        dst[7] = -a[3];
    }

    dst[3] = HK_REAL_ONE /
        (((((dst[6] * dst[6]) * bodyB->m_invInertia[2] +
            (dst[2] * dst[2]) * bodyA->m_invInertia[2]) +
           ((dst[4] * dst[4]) * bodyB->m_invInertia[0] +
            (dst[0] * dst[0]) * bodyA->m_invInertia[0])) +
          ((dst[5] * dst[5]) * bodyB->m_invInertia[1] +
           (dst[1] * dst[1]) * bodyA->m_invInertia[1])) +
         HK_REAL_EPSILON);

    hkReal f2 = -*(hkReal*)((char*)c + 4);
    hkReal f3 = a[4];
    hkReal f4 = a[5];
    ((u32*)p)[0] = 0x10060c;
    p[1] = (f2 * f3) * f1;
    p[2] = (f2 * f4) * f1;
    p[3] = f1;
    out->m_typeCursor = p + 4;
    out->m_cursor = dst + 8;
    dst[7] = f2 * a[6];
}
