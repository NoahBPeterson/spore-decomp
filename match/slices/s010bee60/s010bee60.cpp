// flags: /O2 /MD /Gy /TP /vc71
// Slice s010bee60: hkSimpleConstraintUtil_InitInfo (Havok 3.1.0, 0x010bee60, 1974 bytes).
//
// Builds the effective-mass data of a simple 3-axis constraint between two bodies:
//   mC     = (invMassA + invMassB) * I + sum over both bodies of (r x R)^T * (invInertia * (r x R))
//   mCinv  = mC^-1 (the cofactor/determinant formula with a tiny epsilon added to the determinant)
// plus, per body, the matrices (r x R) and invInertia * (r x R), the inverse mass and the regularized
// reciprocal 1 / (invMass + epsilon). The reference-frame rotation R is copied to the info block.
// Layouts are the 32-bit offsets seen in the binary; the 4th component of every column is written as 0.
#include "types.h"
#include <stddef.h>

typedef float hkReal;

__declspec(align(16)) struct hkVector4
{
	hkReal x, y, z, w;
};

// Product scratch: the compiler spills the first seven results as floats and keeps the last two in x87 registers.
__declspec(align(16)) struct hkMatrix3Mem
{
	volatile float x0, y0, z0, x1, y1, z1, x2;
	float y2, z2;
};

struct hkMatrix3
{
	hkVector4 c[3];     // three columns of four floats

	__forceinline void setZero()
	{
		c[0].x = 0.0f; c[0].y = 0.0f; c[0].z = 0.0f; c[0].w = 0.0f;
		c[1].x = 0.0f; c[1].y = 0.0f; c[1].z = 0.0f; c[1].w = 0.0f;
		c[2].x = 0.0f; c[2].y = 0.0f; c[2].z = 0.0f; c[2].w = 0.0f;
	}
	__forceinline void setDiagonal(hkReal x, hkReal y, hkReal z)
	{
		setZero();
		c[0].x = x;
		c[1].y = y;
		c[2].z = z;
	}
	__forceinline void copy(const hkMatrix3& m)
	{
		c[0].x = m.c[0].x; c[0].y = m.c[0].y; c[0].z = m.c[0].z; c[0].w = m.c[0].w;
		c[1].x = m.c[1].x; c[1].y = m.c[1].y; c[1].z = m.c[1].z; c[1].w = m.c[1].w;
		c[2].x = m.c[2].x; c[2].y = m.c[2].y; c[2].z = m.c[2].z; c[2].w = m.c[2].w;
	}
	// this = a * b with a's columns as the transform (each result column is a rotated b column)
	__forceinline void setMul(const hkMatrix3& a, const hkMatrix3& b);
	__forceinline void transpose()
	{
		hkReal t;
		t = c[0].y; c[0].y = c[1].x; c[1].x = t;
		t = c[0].z; c[0].z = c[2].x; c[2].x = t;
		t = c[1].z; c[1].z = c[2].y; c[2].y = t;
	}
	__forceinline void add(const hkMatrix3Mem& m);
	__forceinline void addUnused(const hkMatrix3& m)
	{
		c[0].x += m.c[0].x; c[0].y += m.c[0].y; c[0].z += m.c[0].z;
		c[1].x += m.c[1].x; c[1].y += m.c[1].y; c[1].z += m.c[1].z;
		c[2].x += m.c[2].x; c[2].y += m.c[2].y; c[2].z += m.c[2].z;
	}
};

__forceinline void setRotatedDir(hkVector4& d, const hkMatrix3& r, const hkVector4& v)
{
	const hkReal vx = v.x, vy = v.y, vz = v.z;
	d.x = (vz * r.c[2].x + vy * r.c[1].x) + vx * r.c[0].x;
	d.y = (vz * r.c[2].y + vy * r.c[1].y) + vx * r.c[0].y;
	d.z = (vz * r.c[2].z + vy * r.c[1].z) + vx * r.c[0].z;
	d.w = 0.0f;
}

// d = a * b, summed in the order the binary uses: the x row as (bx*a0 + a2*bz) + a1*by, the y/z rows as
// (a2*bz + a1*by) + a0*bx.
__forceinline void setMulSplitX(hkMatrix3Mem& d, const hkMatrix3& a, const hkMatrix3& b)
{
	const hkVector4& u = b.c[0];
	d.x0 = (u.x * a.c[0].x + a.c[2].x * u.z) + a.c[1].x * u.y;
	d.y0 = (a.c[2].y * u.z + a.c[1].y * u.y) + a.c[0].y * u.x;
	d.z0 = (a.c[2].z * u.z + a.c[1].z * u.y) + a.c[0].z * u.x;
	const hkVector4& v = b.c[1];
	d.x1 = (v.x * a.c[0].x + a.c[2].x * v.z) + a.c[1].x * v.y;
	d.y1 = (a.c[2].y * v.z + a.c[1].y * v.y) + a.c[0].y * v.x;
	d.z1 = (a.c[2].z * v.z + a.c[1].z * v.y) + a.c[0].z * v.x;
	const hkVector4& w = b.c[2];
	d.x2 = (w.x * a.c[0].x + a.c[2].x * w.z) + a.c[1].x * w.y;
	d.y2 = (a.c[2].y * w.z + a.c[1].y * w.y) + a.c[0].y * w.x;
	d.z2 = (a.c[2].z * w.z + a.c[1].z * w.y) + a.c[0].z * w.x;
}

__forceinline void hkMatrix3::add(const hkMatrix3Mem& m)
{
	c[0].x += m.x0; c[0].y += m.y0; c[0].z += m.z0;
	c[1].x += m.x1; c[1].y += m.y1; c[1].z += m.z1;
	c[2].x += m.x2; c[2].y += m.y2; c[2].z += m.z2;
}

__forceinline void hkMatrix3::setMul(const hkMatrix3& a, const hkMatrix3& b)
{
	const hkReal a00 = a.c[0].x, a01 = a.c[0].y, a02 = a.c[0].z;
	const hkReal a10 = a.c[1].x, a11 = a.c[1].y, a12 = a.c[1].z;
	const hkReal a20 = a.c[2].x, a21 = a.c[2].y, a22 = a.c[2].z;
	{
		const hkReal vx = b.c[0].x, vy = b.c[0].y, vz = b.c[0].z;
		c[0].x = (vz * a20 + vy * a10) + vx * a00;
		c[0].y = (vz * a21 + vy * a11) + vx * a01;
		c[0].z = (vz * a22 + vy * a12) + vx * a02;
		c[0].w = 0.0f;
	}
	{
		const hkReal vx = b.c[1].x, vy = b.c[1].y, vz = b.c[1].z;
		c[1].x = (vz * a20 + vy * a10) + vx * a00;
		c[1].y = (vz * a21 + vy * a11) + vx * a01;
		c[1].z = (vz * a22 + vy * a12) + vx * a02;
		c[1].w = 0.0f;
	}
	{
		const hkReal vx = b.c[2].x, vy = b.c[2].y, vz = b.c[2].z;
		c[2].x = (vz * a20 + vy * a10) + vx * a00;
		c[2].y = (vz * a21 + vy * a11) + vx * a01;
		c[2].z = (vz * a22 + vy * a12) + vx * a02;
		c[2].w = 0.0f;
	}
}

__forceinline void setCross(hkVector4& d, const hkVector4& a, const hkVector4& b)
{
	const hkReal ty = a.z * b.x - a.x * b.z;
	const hkReal tz = a.x * b.y - a.y * b.x;
	const hkReal tx = a.y * b.z - a.z * b.y;
	d.x = tx;
	d.y = ty;
	d.z = tz;
	d.w = 0.0f;
}

// Same cross product, with the operand order the binary has for the first column.
__forceinline void setCrossFirst(hkVector4& d, const hkVector4& a, const hkVector4& b)
{
	const hkReal ty = a.z * b.x - b.z * a.x;
	const hkReal tz = a.x * b.y - a.y * b.x;
	const hkReal tx = b.z * a.y - a.z * b.y;
	d.x = tx;
	d.y = ty;
	d.z = tz;
	d.w = 0.0f;
}

// ---- input / output blocks ------------------------------------------------------------------------------
struct hkSimpleConstraintInfoInitInput
{
	hkVector4 m_massRelPos;     // +0x00 (center of mass to the contact point)
	hkMatrix3 m_invInertia;     // +0x10
	hkReal m_invMass;           // +0x40
};

struct hkSimpleConstraintBodyInfo       // 0x70 bytes
{
	hkMatrix3 m_rxR;            // +0x00 columns: r x R.col(i)
	hkMatrix3 m_IinvRxR;        // +0x30 invInertia * m_rxR
	hkReal m_invMass;           // +0x60
	hkReal m_invMassReg;        // +0x64 1 / (invMass + epsilon)
	hkReal m_pad[2];            // +0x68
};

struct hkSimpleConstraintInfo
{
	hkSimpleConstraintBodyInfo m_body[2];   // +0x00
	hkMatrix3 m_directions;                 // +0xe0 (copy of R)
	hkMatrix3 m_mC;                         // +0x110
	hkMatrix3 m_mCinv;                      // +0x140
};
typedef char hkSimpleConstraintInfo_layout_check[(offsetof(hkSimpleConstraintInfo, m_mCinv) == 0x140) ? 1 : -1];

static const hkReal HK_REAL_EPSILON = 1.1920929e-07f;
static const hkReal HK_REAL_DET_EPSILON = 1.6940659e-21f;

void hkSimpleConstraintUtil_InitInfo(const hkSimpleConstraintInfoInitInput& bodyA,
                                     const hkSimpleConstraintInfoInitInput& bodyB,
                                     const hkMatrix3& directions,
                                     hkSimpleConstraintInfo& info)
{
	const hkReal invMassSum = bodyA.m_invMass + bodyB.m_invMass;
	info.m_mC.setDiagonal(invMassSum, invMassSum, invMassSum);
	info.m_directions.copy(directions);

	const hkSimpleConstraintInfoInitInput* in = &bodyA;
	for (int i = 0; i < 2; i++)
	{
		hkSimpleConstraintBodyInfo& bi = info.m_body[i];

		setCrossFirst(bi.m_rxR.c[0], in->m_massRelPos, directions.c[0]);
		setCross(bi.m_rxR.c[1], in->m_massRelPos, directions.c[1]);
		setCross(bi.m_rxR.c[2], in->m_massRelPos, directions.c[2]);

		bi.m_IinvRxR.setMul(in->m_invInertia, bi.m_rxR);

		bi.m_rxR.transpose();
		hkMatrix3Mem prod;
		setMulSplitX(prod, bi.m_rxR, bi.m_IinvRxR);
		info.m_mC.add(prod);

		bi.m_invMass = in->m_invMass;
		bi.m_invMassReg = 1.0f / (in->m_invMass + HK_REAL_EPSILON);
		in = &bodyB;
	}

	// invert mC (cofactors over the determinant)
	const hkMatrix3& m = info.m_mC;
	const hkReal cof00 = m.c[1].y * m.c[2].z - m.c[2].y * m.c[1].z;
	const hkReal cof01 = m.c[2].x * m.c[1].z - m.c[2].z * m.c[1].x;
	const hkReal cof02 = m.c[2].y * m.c[1].x - m.c[2].x * m.c[1].y;
	const hkReal cof10 = m.c[2].y * m.c[0].z - m.c[2].z * m.c[0].y;
	const hkReal cof11 = m.c[0].x * m.c[2].z - m.c[0].z * m.c[2].x;
	const hkReal cof12 = m.c[0].y * m.c[2].x - m.c[0].x * m.c[2].y;
	const hkReal cof20 = m.c[1].z * m.c[0].y - m.c[1].y * m.c[0].z;
	const hkReal cof21 = m.c[1].x * m.c[0].z - m.c[0].x * m.c[1].z;
	const hkReal cof22 = m.c[0].x * m.c[1].y - m.c[0].y * m.c[1].x;
	volatile hkReal invDet = 1.0f / (((cof00 * m.c[0].x + cof02 * m.c[0].z) + cof01 * m.c[0].y) + HK_REAL_DET_EPSILON);

	hkMatrix3& inv = info.m_mCinv;
	inv.c[0].x = cof00 * invDet;
	inv.c[0].y = cof01 * invDet;
	inv.c[0].z = cof02 * invDet;
	inv.c[0].w = invDet * 0.0f;
	inv.c[1].x = cof10 * invDet;
	inv.c[1].y = cof11 * invDet;
	inv.c[1].z = cof12 * invDet;
	inv.c[1].w = invDet * 0.0f;
	inv.c[2].x = cof20 * invDet;
	inv.c[2].y = cof21 * invDet;
	inv.c[2].z = cof22 * invDet;
	inv.c[2].w = invDet * 0.0f;

	info.m_mC.c[0].w = 1.0f / (info.m_mC.c[0].x + HK_REAL_EPSILON);
	info.m_mC.c[1].w = 1.0f / ((info.m_mC.c[2].z * info.m_mC.c[1].y - info.m_mC.c[2].y * info.m_mC.c[1].z) + HK_REAL_EPSILON);
}
