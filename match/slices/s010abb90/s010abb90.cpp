// Slice s010abb90: Havok motor-constraint jacobian builders.
//   0x010ac750  hk1dAngularVelocityMotorBeginJacobian  (extern "C", cdecl)
// The body block reached through hkpConstraintQueryIn (+0x28 bodyA, +0x2c bodyB) is the solver-side
// per-body cache: a "has infinite mass" flag at +0x0c, the inverse inertia (xyz) / inverse mass (w)
// vector at +0x30 and the body rotation at +0x50.  All vector math is the FPU (non-SIMD) Havok path,
// which evaluates the rotated-inverse-dir dot products in z,y,x order.
#include "types.h"

extern const float _HK_REAL_EPSILON;   // 0x014a23a4
extern const float _HK_REAL_ONE;       // 0x01485720

class __declspec(align(16)) hkVector4
{
public:
	float x, y, z, w;
};

class hkMatrix3
{
public:
	hkVector4 m_col[3];
};

class hkRotation : public hkMatrix3 {};

// solver-side body cache referenced by hkpConstraintQueryIn
class hkSolverBody
{
public:
	unsigned int m_vtable;                 // +0x00
	unsigned int m_pad04;                  // +0x04
	unsigned int m_pad08;                  // +0x08
	unsigned char m_hasInfiniteMass;       // +0x0c
	unsigned char m_pad0d[0x23];           // +0x0d
	hkVector4 m_inertiaAndMassInv;         // +0x30
	unsigned char m_pad40[0x10];           // +0x40
	hkRotation m_rotation;                 // +0x50
};

class hkpConstraintQueryIn
{
public:
	unsigned char m_pad00[0x28];           // +0x00
	const hkSolverBody* m_bodyA;           // +0x28
	const hkSolverBody* m_bodyB;           // +0x2c
};

// two angular jacobian columns
class hkp2AngJacobian
{
public:
	hkVector4 m_angular[2];                // +0x00, +0x10
};

class hkp1dBilateralConstraintStatus
{
public:
	float m_virtualMass;                   // +0x00
};

__forceinline void setMul3(hkVector4& d, const hkVector4& a, const hkVector4& b)
{
	d.x = a.x * b.x;
	d.y = a.y * b.y;
	d.z = a.z * b.z;
}

__forceinline void setRotatedInverseDir(hkVector4& d, const hkRotation& r, const hkVector4& v)
{
	const float v0 = v.x, v1 = v.y, v2 = v.z;
	d.x = (v2 * r.m_col[2].x + v1 * r.m_col[1].x) + v0 * r.m_col[0].x;
	d.y = (v2 * r.m_col[2].y + v1 * r.m_col[1].y) + v0 * r.m_col[0].y;
	d.z = (v2 * r.m_col[2].z + v1 * r.m_col[1].z) + v0 * r.m_col[0].z;
	d.w = 0;
}

__forceinline void setRotatedInverseDirNeg(hkVector4& d, const hkRotation& r, const hkVector4& v)
{
	const float v0 = -v.x, v1 = -v.y, v2 = -v.z;
	d.x = (v2 * r.m_col[2].x + v1 * r.m_col[1].x) + v0 * r.m_col[0].x;
	d.y = (v2 * r.m_col[2].y + v1 * r.m_col[1].y) + v0 * r.m_col[0].y;
	d.z = (v2 * r.m_col[2].z + v1 * r.m_col[1].z) + v0 * r.m_col[0].z;
	d.w = 0;
}

// @ 0x010ac750
extern "C" void hk1dAngularVelocityMotorBeginJacobian(const hkVector4& directionOfConstraint,
                                                      const hkpConstraintQueryIn& in,
                                                      hkp2AngJacobian& jac,
                                                      hkp1dBilateralConstraintStatus& statusOut)
{
	const hkSolverBody* bodyA = in.m_bodyA;
	const hkSolverBody* bodyB = in.m_bodyB;
	hkVector4& jacA = jac.m_angular[0];
	hkVector4& jacB = jac.m_angular[1];

	if (bodyA->m_hasInfiniteMass)
	{
		jacA = directionOfConstraint;
	}
	else
	{
		setRotatedInverseDir(jacA, bodyA->m_rotation, directionOfConstraint);
	}

	if (bodyB->m_hasInfiniteMass)
	{
		jacB.x = -directionOfConstraint.x;
		jacB.y = -directionOfConstraint.y;
		jacB.z = -directionOfConstraint.z;
		jacB.w = -directionOfConstraint.w;
	}
	else
	{
		setRotatedInverseDirNeg(jacB, bodyB->m_rotation, directionOfConstraint);
	}

	hkVector4 sqA;
	hkVector4 sqB;
	sqA.x = jacA.x * jacA.x;
	sqA.y = jacA.y * jacA.y;
	sqA.z = jacA.z * jacA.z;
	sqB.x = jacB.x * jacB.x;
	sqB.y = jacB.y * jacB.y;
	sqB.z = jacB.z * jacB.z;

	float invMass = (((sqB.z * bodyB->m_inertiaAndMassInv.z +
	                  sqA.z * bodyA->m_inertiaAndMassInv.z) +
	                 (sqB.y * bodyB->m_inertiaAndMassInv.y +
	                  sqA.y * bodyA->m_inertiaAndMassInv.y)) +
	                (sqB.x * bodyB->m_inertiaAndMassInv.x +
	                 sqA.x * bodyA->m_inertiaAndMassInv.x)) +
	                _HK_REAL_EPSILON;
	invMass = _HK_REAL_ONE / invMass;

	jacA.w = invMass;
	statusOut.m_virtualMass = invMass;
}
