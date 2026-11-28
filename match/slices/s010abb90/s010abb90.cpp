// Flags: /vc71 /O2 /MD /Gy /TP
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

	__forceinline void operator=(const hkVector4& v)
	{
		x = v.x; y = v.y; z = v.z; w = v.w;
	}
	__forceinline float& operator()(int i) { return (&x)[i]; }
	__forceinline const float& operator()(int i) const { return (&x)[i]; }
};

class hkMatrix3
{
public:
	hkVector4 m_col[3];

	__forceinline float& operator()(int row, int col) { return (&m_col[0])[col](row); }
	__forceinline const float& operator()(int row, int col) const { return (&m_col[0])[col](row); }
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

// ===================================================================================================
// 0x010abb90 -- chain constraint solver setup (Havok 3.1.0 FPU path)
//
// A chain of numLinks three-row constraints (ball-socket links between consecutive bodies) gives a
// block-tridiagonal system.  For link k this builds the 3x3 diagonal block D = J M^-1 J^T + tau I and
// the coupling C = J_k M^-1 J_k+1^T through the body the two links share, then runs one step of the
// block forward elimination (Thomas algorithm):
//     lower    = C_k-1^T
//     invDiag  = (D - lower * upper_k-1)^-1   (diagonal clamped to at least HK_REAL_EPSILON first)
//     upper    = invDiag * C_k
// Under /LTCG the original receives accumOffsets in ecx and blocks in edx (custom register ABI).
// ===================================================================================================

// solver-side per-body velocity accumulator: inverse inertia (xyz) and inverse mass (w) at +0x30
class hkVelocityAccumulator
{
public:
	unsigned char m_pad00[0x30];
	hkVector4 m_invMasses;                 // +0x30
};

// one jacobian row: linear part, angular part for body A and for body B
class hk1Lin2AngJacobian
{
public:
	hkVector4 m_linear0;                   // +0x00
	hkVector4 m_angular[2];                // +0x10, +0x20
};

// per-link result of the forward elimination (0x90 bytes)
class hkChainBlock
{
public:
	hkMatrix3 m_lower;                     // +0x00
	hkMatrix3 m_invDiag;                   // +0x30
	hkMatrix3 m_upper;                     // +0x60
};

extern "C" void hkMatrix3_setMulMat3Mat3(hkMatrix3* out, const hkMatrix3* a, const hkMatrix3* b);   // 0x01081c30
extern "C" void FUN_01081da0(hkMatrix3* m);   // 0x01081da0: m->invertSymmetric()

static __forceinline float& el(hkMatrix3& m, int row, int col) { return (&m.m_col[col].x)[row]; }
static __forceinline const float& el(const hkMatrix3& m, int row, int col) { return (&m.m_col[col].x)[row]; }

// FPU hkVector4 operations (Havok's non-SIMD path, all inline)
static __forceinline void setMul4(hkVector4& d, const hkVector4& a, const hkVector4& b)
{
	d.x = a.x * b.x; d.y = a.y * b.y; d.z = a.z * b.z; d.w = a.w * b.w;
}
static __forceinline void setMul4(hkVector4& d, float s, const hkVector4& a)
{
	d.x = s * a.x; d.y = s * a.y; d.z = s * a.z; d.w = s * a.w;
}
static __forceinline void mul4(hkVector4& d, const hkVector4& a)
{
	d.x *= a.x; d.y *= a.y; d.z *= a.z; d.w *= a.w;
}
static __forceinline void setAdd4(hkVector4& d, const hkVector4& a, const hkVector4& b)
{
	d.x = a.x + b.x; d.y = a.y + b.y; d.z = a.z + b.z; d.w = a.w + b.w;
}
static __forceinline void sub4v(hkVector4& d, const hkVector4& a)
{
	d.x -= a.x; d.y -= a.y; d.z -= a.z; d.w -= a.w;
}
static __forceinline float horizontalAdd3(const hkVector4& v)
{
	return v.z + v.y + v.x;
}

// J_a M^-1 J_b^T for two rows acting on the same pair of bodies
static __forceinline float getNonDiag(const hk1Lin2AngJacobian& a, const hk1Lin2AngJacobian& b,
                                      const hkVelocityAccumulator& accA, const hkVelocityAccumulator& accB)
{
	hkVector4 lin;  setMul4(lin, a.m_linear0, b.m_linear0);
	hkVector4 ang0; setMul4(ang0, a.m_angular[0], b.m_angular[0]);
	hkVector4 ang1; setMul4(ang1, a.m_angular[1], b.m_angular[1]);
	hkVector4 linA; setMul4(linA, accA.m_invMasses.w, lin);
	hkVector4 linB; setMul4(linB, accB.m_invMasses.w, lin);
	mul4(ang0, accA.m_invMasses);
	mul4(ang1, accB.m_invMasses);
	setAdd4(linA, linB, linA);
	setAdd4(ang0, ang1, ang0);
	setAdd4(ang0, linA, ang0);
	return horizontalAdd3(ang0);
}

// J_a M^-1 J_b^T where only the second body of a is the first body of b
static __forceinline void getNonDiagShared(float& out, const hk1Lin2AngJacobian& a, const hk1Lin2AngJacobian& b,
                                           const hkVelocityAccumulator& shared)
{
	const hkVector4& invM = shared.m_invMasses;
	hkVector4 lin; setMul4(lin, a.m_linear0, b.m_linear0);
	hkVector4 ang; setMul4(ang, a.m_angular[1], b.m_angular[0]);
	hkVector4 linM; setMul4(linM, invM.w, lin);
	mul4(ang, invM);
	sub4v(ang, linM);
	out = horizontalAdd3(ang);
}

// out(j, r) = jac[link j] M^-1 jac[next link r]^T through the body the two links share
static __forceinline void setCoupling(hkMatrix3* out, const hk1Lin2AngJacobian* a, const hk1Lin2AngJacobian* b, const hkVelocityAccumulator& shared)
{
	hkVector4* cols = out->m_col;
	for (int j = 0; j < 3; ++j)
		for (int r = 0; r < 3; ++r)
			getNonDiagShared(cols[r](j), a[j], b[r], shared);
}

static __forceinline void set(hkVector4& v, float x, float y, float z, float w)
{
	v.x = x; v.y = y; v.z = z; v.w = w;
}

static __forceinline void setZero4(hkVector4& v)
{
	v.x = v.y = v.z = v.w = 0.0f;
}

// hkMatrix3 built from three zero columns
static __forceinline void setAllZero(hkMatrix3& m)
{
	set(m.m_col[0], 0.0f, 0.0f, 0.0f, 0.0f);
	set(m.m_col[1], 0.0f, 0.0f, 0.0f, 0.0f);
	set(m.m_col[2], 0.0f, 0.0f, 0.0f, 0.0f);
}

static __forceinline void setZero(hkMatrix3& m)
{
	setZero4(m.m_col[0]);
	setZero4(m.m_col[1]);
	setZero4(m.m_col[2]);
}

static __forceinline void sub4(hkVector4& v, const hkVector4& o)
{
	v.x -= o.x; v.y -= o.y; v.z -= o.z; v.w -= o.w;
}

static __forceinline void sub(hkMatrix3& m, const hkMatrix3& o)
{
	sub4(m.m_col[0], o.m_col[0]);
	sub4(m.m_col[1], o.m_col[1]);
	sub4(m.m_col[2], o.m_col[2]);
}

static __forceinline void setTranspose(hkMatrix3& m, const hkMatrix3& o)
{
	m(0, 0) = o(0, 0);
	m(1, 1) = o(1, 1);
	m(2, 2) = o(2, 2);
	m(3, 0) = 0.0f;
	m(3, 1) = 0.0f;
	m(3, 2) = 0.0f;
	m.m_col[0].y = o.m_col[1].x;
	m.m_col[1].x = o.m_col[0].y;
	m.m_col[0].z = o.m_col[2].x;
	m.m_col[2].x = o.m_col[0].z;
	m.m_col[1].z = o.m_col[2].y;
	m.m_col[2].y = o.m_col[1].z;
}

static __forceinline float max2(float a, float b)
{
	return (a > b) ? a : b;
}

extern "C" void hkEscape(const void*);
// @ 0x010abb90
static void hkChainBuildBlocks(const int* accumOffsets, hkChainBlock* blocks, int numLinks, float tau,
                                   const hk1Lin2AngJacobian* jac, const char* accumBase)
{
	hkMatrix3 prevCoupling;
	hkMatrix3 prevUpper;
	setAllZero(prevCoupling);
	setAllZero(prevUpper);
	const hk1Lin2AngJacobian* rowJ = jac;
	// RULE-EXCEPTION: R17. Retail treats jac as address-taken (reloaded from its stack home, base-free
	// k*0x90 offset). cl 13.10 does that only when &jac reaches a call or store, even in dead code, so the
	// original most likely had a debug check here that release builds compile out. Its form is unknown.
	if (0) hkEscape(&jac);
	const int* offs = accumOffsets;
	hkChainBlock* blockPtr = blocks;
	for (int k = 0; k < numLinks; ++k, ++offs, ++blockPtr)
	{
		hkMatrix3 diag;
		const hk1Lin2AngJacobian* linkRows = rowJ;
		const int* next = offs + 1;
		for (int j = 0; j < 3; ++j)
		{
			for (int m = j; m < 3; ++m)
			{
				const hkVelocityAccumulator& accB = *(const hkVelocityAccumulator*)(accumBase + next[0]);
				const hkVelocityAccumulator& accA = *(const hkVelocityAccumulator*)(accumBase + next[-1]);
				float v = getNonDiag(linkRows[m], linkRows[j], accA, accB);
				el(diag, j, m) = v;
				diag(m, j) = v;
			}
			diag(j, j) = tau + diag(j, j);
		}
		hkMatrix3 coupling;
		setAllZero(coupling);
		if (k < numLinks - 1)
		{
			const hkVelocityAccumulator& shared = *(const hkVelocityAccumulator*)(accumBase + next[0]);
			const hk1Lin2AngJacobian* nextRows = jac + 3 * (k + 1);
			setCoupling(&coupling, &jac[3 * k], nextRows, shared);
		}
		else
		{
			setZero(coupling);
		}
		hkChainBlock& block = *blockPtr;
		setTranspose(block.m_lower, prevCoupling);
		hkMatrix3 lu;
		hkMatrix3_setMulMat3Mat3(&lu, &block.m_lower, &prevUpper);
		block.m_invDiag = diag;
		sub(block.m_invDiag, lu);
		block.m_invDiag(0, 0) = max2(block.m_invDiag(0, 0), _HK_REAL_EPSILON);
		block.m_invDiag(1, 1) = max2(block.m_invDiag(1, 1), _HK_REAL_EPSILON);
		block.m_invDiag(2, 2) = max2(block.m_invDiag(2, 2), _HK_REAL_EPSILON);
		FUN_01081da0(&block.m_invDiag);
		hkMatrix3_setMulMat3Mat3(&block.m_upper, &block.m_invDiag, &coupling);

		rowJ = linkRows + 3;
		prevCoupling = coupling;
		prevUpper = block.m_upper;
	}
}

// Same-object stand-in for the builder's only caller (0x010ad020, the ball-socket chain jacobian setup); it is
// here so cl gives the static builder its private register convention (accumOffsets ecx, blocks edx).
extern "C" void hkBallSocketChainBuildBlocks_caller(const int* accumOffsets, hkChainBlock* blocks, int numLinks, float tau,
                                                    const hk1Lin2AngJacobian* jac, const char* accumBase)
{
	hkChainBuildBlocks(accumOffsets, blocks, numLinks, tau, jac, accumBase);
}
