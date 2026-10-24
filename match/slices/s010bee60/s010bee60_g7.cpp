// flags: /O2 /MD /Gy /TP /vc71
// gold7 batch, worker 5 / slice s010bee60: the three hkSimpleConstraintUtil helpers that drive one
// simple-constraint iteration (Havok 3.1.0, built with VC .NET 2003). They operate on the
// hkSimpleConstraintInfo block laid out by the committed hkSimpleConstraintUtil_InitInfo
// (s010bee60.cpp), so the hkMatrix3 / hkVector4 model is reused from there.
//
//   0x010bf620  hkSimpleConstraintUtil_applyImpulse  - project the relative velocity through the two
//                                bodies' invInertia * (r x R) blocks into the constraint-space impulse
//                                and subtract the reaction (m_mCinv columns) back into the velocity.
//   0x010bf800  hkSimpleConstraintUtil_getPointVelocity - relative point velocity of the two bodies:
//                                (wA x rA + vA) - (wB x rB + vB), projected through the direction matrix.
//   0x010bf980  hkSimpleConstraintUtil_Collide    - BIAS/soft-constraint clamp on the normal impulse,
//                                then applyImpulse and return the clamped value.
//
// The x87 arithmetic is written to follow the binary's spill/reuse pattern (the first results of each
// 3x3 transform go to stack temporaries while the last stays in an x87 register).
#include "types.h"
#include <stddef.h>
#include <math.h>

typedef float hkReal;

__declspec(align(16)) struct hkVector4
{
	hkReal x, y, z, w;
};

__declspec(align(16)) struct hkMatrix3Mem
{
	float x0, y0, z0, x1, y1, z1, x2, y2, z2;
};

class hkMatrix3
{ public:
	hkVector4 c[3];

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
		c[0] = m.c[0];
		c[1] = m.c[1];
		c[2] = m.c[2];
	}
};

// ---- blocks laid out by hkSimpleConstraintUtil_InitInfo -------------------------------------------------
struct hkSimpleConstraintBodyInfo       // 0x70 bytes
{
	hkMatrix3 m_rxR;            // +0x00
	hkMatrix3 m_IinvRxR;        // +0x30
	hkReal m_invMass;           // +0x60
	hkReal m_invMassReg;        // +0x64 1 / (invMass + epsilon)
	hkReal m_pad[2];            // +0x68
};

struct hkSimpleConstraintInfo
{
	hkSimpleConstraintBodyInfo m_body[2];   // +0x00
	hkMatrix3 m_directions;                 // +0x0e0 (copy of R)
	hkMatrix3 m_mC;                         // +0x110
	hkMatrix3 m_mCinv;                      // +0x140
};
typedef char hkSimpleConstraintInfo_layout_check[(offsetof(hkSimpleConstraintInfo, m_mCinv) == 0x140) ? 1 : -1];

// Constraint working block (the object param_2 the Collide/applyImpulse pair share):
//   +0x00..+0x08  unused (the +0x0c field is cleared)
//   +0x10         the normal velocity D squared / restitution term
//   +0x14         the bounce factor (BIAS)
//   +0x18         the contact-separation distance
//   +0x1c         the accumulated normal impulse
//   +0x20         the friction factor
//   +0x1c/+0x0c   cleared on exit
struct hkSimpleConstraintWork
{
	hkReal m_unk00[4];      // +0x00
	hkReal m_d;             // +0x10
	hkReal m_bias;          // +0x14
	hkReal m_separation;    // +0x18
	hkReal m_impulse;       // +0x1c
	hkReal m_friction;      // +0x20
};

// @ 0x010bf620  hkSimpleConstraintUtil_applyImpulse
// The relative velocity stored in relVel is first rotated by the direction frame (body[0] m_IinvRxR
// rows, offsets 0x30/0x40/0x50 etc.), scaled by each body's invMass, and folded into the linear
// impulse/velocity; then each body's m_IinvRxR is applied to the impulse and the reaction is folded
// into the angular part (indices 4..6 = the +0x10/+0x14/+0x18 slots).
void hkSimpleConstraintUtil_applyImpulse(const void* infoRaw,
                                         const float* relVel,
                                         float* impulse,
                                         float* velocity)
{
	const hkSimpleConstraintInfo& info = *(const hkSimpleConstraintInfo*)infoRaw;	// ---- block at 0xe0 (m_directions) applied to relVel -> d (row-major transform) ----
	const float vx = relVel[0], vy = relVel[1], vz = relVel[2];
	const hkMatrix3& dir = info.m_directions;
	float d0 = vx * dir.c[0].x + vy * dir.c[1].x + vz * dir.c[2].x;
	float d1 = vx * dir.c[0].y + vy * dir.c[1].y + vz * dir.c[2].y;
	float d2 = vx * dir.c[0].z + vy * dir.c[1].z + vz * dir.c[2].z;

	const float a = info.m_body[0].m_invMass;
	impulse[0] = d0 * a + impulse[0];
	impulse[1] = d1 * a + impulse[1];
	impulse[2] = d2 * a + impulse[2];
	impulse[3] = a * 0.0f + impulse[3];

	const float b = info.m_body[1].m_invMass;
	velocity[0] = velocity[0] - d0 * b;
	velocity[1] = velocity[1] - d1 * b;
	velocity[2] = velocity[2] - d2 * b;
	velocity[3] = velocity[3] - b * 0.0f;

	// ---- body[0] m_IinvRxR (0x30..0x58) applied to relVel, accumulated into impulse[4..6] ----
	const hkMatrix3& r0 = info.m_body[0].m_IinvRxR;
	float e0 = vx * r0.c[0].x + vy * r0.c[1].x + vz * r0.c[2].x;
	float e1 = vx * r0.c[0].y + vy * r0.c[1].y + vz * r0.c[2].y;
	float e2 = vx * r0.c[0].z + vy * r0.c[1].z + vz * r0.c[2].z;
	impulse[4] = e0 + impulse[4];
	impulse[5] = e1 + impulse[5];
	impulse[6] = e2 + impulse[6];

	// ---- body[1] m_IinvRxR (0xa0..0xc8) applied to relVel, subtracted from velocity[4..6] ----
	const hkMatrix3& r1 = info.m_body[1].m_IinvRxR;
	float f0 = vx * r1.c[0].x + vy * r1.c[1].x + vz * r1.c[2].x;
	float f1 = vx * r1.c[0].y + vy * r1.c[1].y + vz * r1.c[2].y;
	float f2 = vx * r1.c[0].z + vy * r1.c[1].z + vz * r1.c[2].z;
	velocity[4] = velocity[4] - f0;
	velocity[5] = velocity[5] - f1;
	velocity[6] = velocity[6] - f2;

	impulse[7] = 0.0f;
	velocity[7] = 0.0f;
	impulse[3] = 0.0f;
	velocity[3] = 0.0f;
}
// @ 0x010bf800  hkSimpleConstraintUtil_getPointVelocity
// out = R * (vA - vB) + ((wA * m_rxR[0]) - (wB * m_rxR[1])) where R is the column block at
// +0xe0/+0xf0/+0x100, m_rxR[0] is the 3x3 at +0x00 (rows +0x00/+0x10/+0x20) and m_rxR[1] the 3x3 at
// +0x70 (rows +0x70/+0x80/+0x90); the w vector of each body is at +0x10/+0x14/+0x18.
float* hkSimpleConstraintUtil_getPointVelocity(const float* m,
                                               const float* bodyA,
                                               const float* bodyB,
                                               float* out)
{
	const float wax = bodyA[4], way = bodyA[5], waz = bodyA[6];
	const float wbx = bodyB[4], wby = bodyB[5], wbz = bodyB[6];

	// column-major: component j of m_rxR[i] * w
	const float p0 = waz * m[0x20 / 4] + way * m[0x10 / 4] + wax * m[0x00 / 4];
	const float p1 = waz * m[0x24 / 4] + way * m[0x14 / 4] + wax * m[0x04 / 4];
	const float p2 = waz * m[0x28 / 4] + way * m[0x18 / 4] + wax * m[0x08 / 4];

	const float q0 = wbz * m[0x90 / 4] + wby * m[0x80 / 4] + wbx * m[0x70 / 4];
	const float q1 = wbz * m[0x94 / 4] + wby * m[0x84 / 4] + wbx * m[0x74 / 4];
	const float q2 = wbz * m[0x98 / 4] + wby * m[0x88 / 4] + wbx * m[0x78 / 4];

	const float dx = p0 - q0;
	const float dy = p1 - q1;
	const float dz = p2 - q2;

	const float c0 = bodyA[0] - bodyB[0];
	const float c1 = bodyA[1] - bodyB[1];
	const float c2 = bodyA[2] - bodyB[2];

	out[0] = (c0 * m[0xe0 / 4] + c1 * m[0xe4 / 4] + c2 * m[0xe8 / 4]) + dx;
	out[1] = (c0 * m[0xf0 / 4] + c1 * m[0xf4 / 4] + c2 * m[0xf8 / 4]) + dy;
	out[2] = (c0 * m[0x100 / 4] + c1 * m[0x104 / 4] + c2 * m[0x108 / 4]) + dz;
	out[3] = 0.0f;
	return out;
}

// @ 0x010bf980  hkSimpleConstraintUtil_Collide
float hkSimpleConstraintUtil_Collide(const float* m,
                                     hkSimpleConstraintWork& work,
                                     float* sa,
                                     float* sb)
{
	__declspec(align(16)) hkVector4 rel4;
	hkSimpleConstraintUtil_getPointVelocity(m, sa, sb, &rel4.x);
	float* rel = &rel4.x;

	if (rel[0] > work.m_separation)
	{
		rel[0] = work.m_separation;
		if (!(work.m_separation < work.m_impulse))
			return 0.0f;
	}

	rel[1] = -rel[1];
	rel[2] = -rel[2];
	rel[0] = (work.m_bias + 1.0f) * -rel[0] + work.m_impulse;
	// m_mCinv (0x140..0x168) applied to rel
	float t0 = rel[2] * m[0x160 / 4] + rel[1] * m[0x150 / 4] + rel[0] * m[0x140 / 4];
	float t1 = rel[2] * m[0x164 / 4] + rel[1] * m[0x154 / 4] + rel[0] * m[0x144 / 4];
	float t2 = rel[2] * m[0x168 / 4] + rel[1] * m[0x158 / 4] + rel[0] * m[0x148 / 4];

	if ((work.m_d * work.m_d) * (t0 * t0) < t2 * t2 + t1 * t1)
	{
		float a1 = t2 < 0.0f ? -t2 : t2;    // fabs(t2)
		float a4 = t1 < 0.0f ? -t1 : t1;    // fabs(t1)
		float fv5 = rel[0] * m[0x11c / 4];
		rel[0] = rel[0] - fv5 * m[0x110 / 4];
		rel[1] = rel[1] - fv5 * m[0x114 / 4];
		float f2 = rel[2] - fv5 * m[0x118 / 4];
		float f3 = f2 * m[0x134 / 4];
		float l1c = (rel[1] * m[0x124 / 4] - f3) * m[0x12c / 4];
		float l18 = (f2 * m[0x138 / 4] - f3) * m[0x12c / 4];
		float v2 = l1c * l1c + l18 * l18;
		float v3 = fv5 * work.m_d;
		v3 = v3 * v3;
		if (v3 < v2)
		{
			v2 = (float)sqrt((double)(v3 / v2));
			l1c = v2 * l1c;
			l18 = v2 * l18;
		}
		float f2b = ((rel[0] - l1c * m[0x120 / 4]) - l18 * m[0x130 / 4]) * m[0x11c / 4];
		if (f2b < 0.0f)
			f2b = 0.0f;
		t0 = (a4 + a1) * work.m_friction + (f2b + fv5);
	}

	float outv[4];
	outv[0] = t0; outv[1] = t1; outv[2] = t2; outv[3] = 0.0f;
	hkSimpleConstraintUtil_applyImpulse(m, outv, sa, sb);	return outv[0];
}
