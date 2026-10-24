// Havok 3.1.0 slice s01123850: hkInertiaTensorComputer mass-property builders.
//
// Struct stubs carry members at the x86 offsets of the 32-bit binary (comments).
// Flags: /vc71 /O2 /MD /Gy /TP
#pragma once
#include "types.h"

// hkResult: HK_SUCCESS = 0, HK_FAILURE = 1 (returned as a 4-byte enum).
enum hkResult { HK_SUCCESS = 0, HK_FAILURE = 1 };

// hkVector4: 4 floats (x/y/z/w), 0x10 bytes.
struct hkVector4
{
	float x;                                      // +0x00
	float y;                                      // +0x04
	float z;                                      // +0x08
	float w;                                      // +0x0c
};

// hkMatrix3: three 4-wide rows (0x30 bytes).
struct hkMatrix3
{
	float m[12];
};

// hkMassProperties: volume at +0, centre of mass at +4..+0x13 (4 floats),
// then the 3x3 inertia tensor laid out as three 4-wide rows at +0x20/+0x30/+0x40.
struct hkMassProperties
{
	float m_volume;                               // +0x00
	float m_cx;                                   // +0x04
	float m_cy;                                   // +0x08
	float m_cz;                                   // +0x0c
	float m_cw;                                   // +0x10
	float m_pad14;                                // +0x14
	float m_pad18;                                // +0x18
	float m_pad1c;                                // +0x1c
	float m_i00;                                  // +0x20
	float m_i01;                                  // +0x24
	float m_i02;                                  // +0x28
	float m_i03;                                  // +0x2c
	float m_i10;                                  // +0x30
	float m_i11;                                  // +0x34
	float m_i12;                                  // +0x38
	float m_i13;                                  // +0x3c
	float m_i20;                                  // +0x40
	float m_i21;                                  // +0x44
	float m_i22;                                  // +0x48
	float m_i23;                                  // +0x4c
};

struct hkInertiaTensorComputer
{
	static hkResult computeSphereVolumeMassProperties(float radius, float volume, hkMassProperties& out);   // 0x01124060
	static hkResult computeBoxVolumeMassProperties(const hkVector4& halfExtents, float volume, hkMassProperties& out);  // 0x01124110
	static void shiftInertiaToCom(hkVector4& com, float mass, hkMatrix3& inertia);        // 0x011241e0
	static void shiftInertiaFromCom(hkVector4& com, float mass, hkMatrix3& inertia);      // 0x01124280
};

// @ 0x01124060
hkResult hkInertiaTensorComputer::computeSphereVolumeMassProperties(float radius, float volume,
                                                                    hkMassProperties& out)
{
	if (radius < 0.0f || volume < 0.0f)
		return HK_FAILURE;

	float f = (volume * (radius * radius)) * 0.4f;

	out.m_i00 = 0.0f;
	out.m_i01 = 0.0f;
	out.m_i02 = 0.0f;
	out.m_i03 = 0.0f;
	out.m_i10 = 0.0f;
	out.m_i11 = 0.0f;
	out.m_i12 = 0.0f;
	out.m_i13 = 0.0f;
	out.m_i20 = 0.0f;
	out.m_i21 = 0.0f;
	out.m_i22 = 0.0f;
	out.m_i23 = 0.0f;

	out.m_i00 = 1.0f;
	out.m_i11 = 1.0f;
	out.m_i22 = 1.0f;

	out.m_i00 = f;
	out.m_i11 = f;
	out.m_i22 = f;

	out.m_pad1c = 0.0f;
	out.m_pad18 = 0.0f;
	out.m_pad14 = 0.0f;
	out.m_cw = 0.0f;
	out.m_cx = volume;
	out.m_volume = ((radius * radius) * radius) * 4.1887903f;
	return HK_SUCCESS;
}

// @ 0x01124110
hkResult hkInertiaTensorComputer::computeBoxVolumeMassProperties(const hkVector4& halfExtents,
                                                                 float volume,
                                                                 hkMassProperties& out)
{
	if (halfExtents.y < 0.0f)
		return HK_FAILURE;

	float hx = halfExtents.x;
	float hy = halfExtents.y;
	float hz = halfExtents.z;
	float f = volume * 0.33333334f;

	out.m_i00 = (hy * hy + hz * hz) * f;
	out.m_i01 = 0.0f;
	out.m_i02 = 0.0f;
	out.m_i03 = 0.0f;
	out.m_i10 = 0.0f;
	out.m_i11 = (hx * hx + hz * hz) * f;
	out.m_i12 = 0.0f;
	out.m_i13 = 0.0f;
	out.m_i20 = 0.0f;
	out.m_i21 = 0.0f;
	out.m_i22 = (hx * hx + hy * hy) * f;
	out.m_i23 = 0.0f;

	out.m_pad1c = 0.0f;
	out.m_pad18 = 0.0f;
	out.m_pad14 = 0.0f;
	out.m_cw = 0.0f;
	out.m_cy = hy;
	out.m_volume = (hx * hy * hz) * 8.0f;
	return HK_SUCCESS;
}

// @ 0x011241e0
void hkInertiaTensorComputer::shiftInertiaToCom(hkVector4& com, float mass, hkMatrix3& inertia)
{
	float* m = inertia.m;

	m[0]  = m[0]  - (com.z * com.z + com.y * com.y) * mass;
	m[5]  = m[5]  - (com.z * com.z + com.x * com.x) * mass;
	m[10] = m[10] - (com.y * com.y + com.x * com.x) * mass;

	float v = (mass * com.x) * com.y + m[1];
	m[1] = v;
	m[4] = v;

	v = (mass * com.z) * com.y + m[6];
	m[6] = v;
	m[9] = v;

	v = (mass * com.x) * com.z + m[8];
	m[8] = v;
	m[2] = v;
}

// @ 0x01124280
void hkInertiaTensorComputer::shiftInertiaFromCom(hkVector4& com, float mass, hkMatrix3& inertia)
{
	float* m = inertia.m;

	m[0]  = (com.z * com.z + com.y * com.y) * mass + m[0];
	m[5]  = (com.z * com.z + com.x * com.x) * mass + m[5];
	m[10] = (com.y * com.y + com.x * com.x) * mass + m[10];

	float v = m[1] - (mass * com.x) * com.y;
	m[1] = v;
	m[4] = v;

	v = m[6] - (mass * com.z) * com.y;
	m[6] = v;
	m[9] = v;

	v = m[8] - (mass * com.x) * com.z;
	m[8] = v;
	m[2] = v;
}

// ---------------------------------------------------------------------------
// InternalInertiaTensorComputer: accumulates Mirtich projection integrals.
// this+0x00..+0x08: the three vertex axes (A/B/C), this+0x0c..+0x30: the ten
// running integrals P1, Pa, Pb, Paa, Pab, Pbb, Paaa, Paab, Pabb, Pbbb.
struct InternalInertiaTensorComputer
{
	int   m_axes[3];                              // +0x00 A, +0x04 B, +0x08 C
	float m_p1;                                   // +0x0c
	float m_pa;                                   // +0x10
	float m_pb;                                   // +0x14
	float m_paa;                                  // +0x18
	float m_pab;                                  // +0x1c
	float m_pbb;                                  // +0x20
	float m_paaa;                                 // +0x24
	float m_paab;                                 // +0x28
	float m_pabb;                                 // +0x2c
	float m_pbbb;                                 // +0x30

	void compProjectionIntegrals(const hkVector4* vertices);   // 0x01124320
};

// @ 0x01124320
void InternalInertiaTensorComputer::compProjectionIntegrals(const hkVector4* vertices)
{
	const float* v = (const float*)vertices;

	int ax = m_axes[0];
	int bx = m_axes[1];

	m_pbbb = 0.0f;
	m_pabb = 0.0f;
	m_paab = 0.0f;
	m_paaa = 0.0f;
	m_pbb = 0.0f;
	m_pab = 0.0f;
	m_paa = 0.0f;
	m_pb = 0.0f;
	m_pa = 0.0f;
	m_p1 = 0.0f;

	int i = 1;
	const float* p2 = (const float*)((const char*)v + bx * 4);
	int n = 3;
	const float* p1 = (const float*)((const char*)v + ax * 4);
	float fVar16 = 0.0f, fVar15 = 0.0f, fVar14 = 0.0f, fVar13 = 0.0f;
	float fVar17 = 0.0f, fVar21 = 0.0f, fVar10 = 0.0f, fVar9 = 0.0f, fVar6 = 0.0f, fVar1 = 0.0f;

	do {
		float a0 = p1[0];                          // fVar1  = *pfVar24
		float b0 = p2[0];                          // fVar2  = *pfVar23
		int j = (i % 3);
		float a1 = v[ax + j];                      // fVar3
		float b1 = v[bx + j];                      // fVar4
		float da = a1 - a0;                        // fVar5
		float db = b1 - b0;                        // fVar12
		float a02 = a0 * a0;                       // fVar6
		float a03 = a02 * a0;                      // fVar7
		float b02 = b0 * b0;                       // fVar8
		float b03 = b02 * b0;                      // fVar19
		float a12 = a1 * a1;                       // fVar20
		float b13 = (b1 * b1) * b1;                // fVar11
		float bb02 = (b1 * b1) * b0;
		float bb03 = b02 * b1;
		float sA = a1 * (a1 + a0) + a02;           // fVar13
		float sA3 = sA * a1 + a03;                 // fVar17
		float sB = (b1 + b0) * b1 + b02;           // fVar9
		float sB3 = sB * b1 + b03;                 // fVar10
		float cross = a1 * a0 + a1 * a0;           // fVar14
		float t1 = (a12 * 3.0f + cross) + a02;     // fVar18
		float t2 = (a02 * 3.0f + cross) + a12;     // fVar6 (reused)

		fVar10 = (sB3 * b1 + b03 * b0) * da + m_p1;
		m_p1 = fVar10;
		fVar17 = sB * da + m_pa;
		m_pa = fVar17;
		fVar15 = sA * db + m_paa;
		m_paa = fVar15;
		fVar14 = sA3 * db + m_paaa;
		m_paaa = fVar14;
		fVar16 = (a1 + a0) * db + m_pb;
		m_pb = fVar16;
		fVar9 = (t2 * b0 + t1 * b1) * db + m_pbb;
		m_pbb = fVar9;
		fVar1 = (((b13 * 4.0f + (bb02 * 3.0f + (bb03 + bb03))) + b03) * a1 +
		         ((b03 * 4.0f + ((bb02 + bb02) + bb03 * 3.0f)) + b13) * a0) * da + m_pbbb;
		m_pbbb = fVar1;
		fVar21 = sB3 * da + m_pab;
		m_pab = fVar21;
		fVar6 = ((a03 * 4.0f + t2 * a1) * b0 + (t1 * a0 + (a12 * a1) * 4.0f) * b1) * db + m_paab;
		m_paab = fVar6;
		fVar13 = (sA3 * a1 + a03 * a0) * db + m_pabb;
		m_pabb = fVar13;

		p1 += 4;
		p2 += 4;
		++i;
		--n;
	} while (n != 0);

	m_pb      = fVar16 * 0.5f;
	m_paa     = fVar15 * 0.16666667f;
	m_paaa    = fVar14 * 0.083333336f;
	m_pbb     = fVar9 * 0.041666668f;
	m_pa      = fVar17 * -0.16666667f;
	m_pabb    = fVar13 * -0.016666668f;
	m_p1      = fVar10 * -0.05f;
	m_pbbb    = fVar1 * -0.016666668f;
	m_pab     = fVar21 * -0.083333336f;
	m_paab    = fVar6 * 0.016666668f;
}
