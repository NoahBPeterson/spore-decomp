// s010ab2d0.cpp -- Havok 3.1.0 constraint buildJacobian routines.
//
//   0x010ab2d0  unnamed 3-axis constraint buildJacobian (sits between
//               _hk1dAngularLimitBuildJacobian and _hkPulleyConstraintBuildJacobian)
//   0x010ab5d0  _hkPulleyConstraintBuildJacobian
//
// Both are "identical-code" Havok routines built by the dev toolset (cl 13.10.x,
// /O2, whole-program optimisation): every helper is inlined, there are no calls,
// and the math is x87.  The reconstructions below follow the disassembly's data
// flow (same input loads, loop bounds and stores) but the compiler's x87 schedule
// and exact expression nesting could not be recovered, so neither is byte-exact.
//
#include "types.h"
#include <math.h>

typedef float hkReal;

struct hkVector4 { hkReal x, y, z, w; };

static inline hkVector4 hkCross(const hkVector4& a, const hkVector4& b)
{
    hkVector4 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    r.w = 0.0f;
    return r;
}

static inline hkReal hkLen3(const hkVector4& v)
{
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

// ---------------------------------------------------------------------------
// 0x010ab2d0 -- unnamed 3-axis constraint buildJacobian
//
// Builds three constraint rows against the identity basis stored at 0x015b9b20,
// each row being (axis, bodyA-point x axis, bodyB-point x axis).  A byte flag at
// data+0x0c selects the sign convention per row.
// @ 0x10ab2d0
void _hk3AxisConstraintBuildJacobian(const unsigned char* bodyA,
                                     const unsigned char* bodyB,
                                     const unsigned char* data,
                                     const unsigned char* out)
{
    static const hkReal kBasis[12] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f
    };

    const unsigned char* pa = *(const unsigned char* const*)(data + 0x28);
    const unsigned char* pb = *(const unsigned char* const*)(data + 0x2c);

    hkVector4* o = (hkVector4*)out;

    for (int i = 0; i < 3; ++i)
    {
        hkVector4 axis;
        axis.x = kBasis[i * 4 + 0];
        axis.y = kBasis[i * 4 + 1];
        axis.z = kBasis[i * 4 + 2];
        axis.w = kBasis[i * 4 + 3];

        hkVector4 pA;
        pA.x = *(const hkReal*)(bodyA + 0) - *(const hkReal*)(pa + 0x40);
        pA.y = *(const hkReal*)(bodyA + 4) - *(const hkReal*)(pa + 0x44);
        pA.z = *(const hkReal*)(bodyA + 8) - *(const hkReal*)(pa + 0x48);
        pA.w = 0.0f;

        hkVector4 pB;
        pB.x = *(const hkReal*)(bodyB + 0) - *(const hkReal*)(pb + 0x40);
        pB.y = *(const hkReal*)(bodyB + 4) - *(const hkReal*)(pb + 0x44);
        pB.z = *(const hkReal*)(bodyB + 8) - *(const hkReal*)(pb + 0x48);
        pB.w = 0.0f;

        hkReal sign = (*(const unsigned char*)(data + 0x0c) != 0) ? -1.0f : 1.0f;

        o[i * 3 + 0] = axis;
        o[i * 3 + 1] = hkCross(pA, axis);
        o[i * 3 + 2] = hkCross(pB, axis);
        o[i * 3 + 2].x *= sign;
        o[i * 3 + 2].y *= sign;
        o[i * 3 + 2].z *= sign;
    }
}

// ---------------------------------------------------------------------------
// 0x010ab5d0 -- _hkPulleyConstraintBuildJacobian
//
// Pulley constraint: two rope segments (pivotA - fixedPivotA) and
// (pivotB - fixedPivotB), with the B segment scaled by the leverage factor.  The
// row's linear directions are the normalized segment directions; the angular
// parts are r x n for each body.
// @ 0x10ab5d0
void _hkPulleyConstraintBuildJacobian(const unsigned char* atoms,
                                      const unsigned char* bodyA,
                                      const unsigned char* bodyB,
                                      const unsigned char* out)
{
    hkVector4 sepA;
    sepA.x = *(const hkReal*)(atoms + 0x20) - *(const hkReal*)(atoms + 0x00);
    sepA.y = *(const hkReal*)(atoms + 0x24) - *(const hkReal*)(atoms + 0x04);
    sepA.z = *(const hkReal*)(atoms + 0x28) - *(const hkReal*)(atoms + 0x08);
    sepA.w = *(const hkReal*)(atoms + 0x2c) - *(const hkReal*)(atoms + 0x0c);

    hkVector4 sepB;
    sepB.x = *(const hkReal*)(atoms + 0x10) - *(const hkReal*)(atoms + 0x30);
    sepB.y = *(const hkReal*)(atoms + 0x14) - *(const hkReal*)(atoms + 0x34);
    sepB.z = *(const hkReal*)(atoms + 0x18) - *(const hkReal*)(atoms + 0x38);
    sepB.w = *(const hkReal*)(atoms + 0x1c) - *(const hkReal*)(atoms + 0x3c);

    const hkReal lenA = hkLen3(sepA);
    const hkReal lenB = hkLen3(sepB);
    const hkReal leverage = *(const hkReal*)(atoms + 0x40);

    hkVector4 nA, nB;
    const hkReal invA = (lenA != 0.0f) ? 1.0f / lenA : 0.0f;
    const hkReal invB = (lenB != 0.0f) ? 1.0f / lenB : 0.0f;
    nA.x = sepA.x * invA; nA.y = sepA.y * invA; nA.z = sepA.z * invA; nA.w = 0.0f;
    nB.x = sepB.x * invB * leverage;
    nB.y = sepB.y * invB * leverage;
    nB.z = sepB.z * invB * leverage;
    nB.w = 0.0f;

    const unsigned char* ra = *(const unsigned char* const*)(bodyA + 0x28);
    const unsigned char* rb = *(const unsigned char* const*)(bodyB + 0x28);

    hkVector4 rA;
    rA.x = *(const hkReal*)(ra + 0x20);
    rA.y = *(const hkReal*)(ra + 0x24);
    rA.z = *(const hkReal*)(ra + 0x28);
    rA.w = 0.0f;

    hkVector4 rB;
    rB.x = *(const hkReal*)(rb + 0x20);
    rB.y = *(const hkReal*)(rb + 0x24);
    rB.z = *(const hkReal*)(rb + 0x28);
    rB.w = 0.0f;

    hkVector4* o = (hkVector4*)out;
    o[0] = nA;
    o[1] = hkCross(rA, nA);
    o[2] = nB;
    o[3] = hkCross(rB, nB);
    o[4].x = lenA + lenB * leverage;   // rope length
    o[4].y = o[4].z = o[4].w = 0.0f;
    (void)bodyA;
    (void)bodyB;
}
