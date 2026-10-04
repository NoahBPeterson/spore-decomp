// Havok 3.1.0 math, part: hkVector4 rotate helpers, hkMatrix3 (transpose, invert, mul, add/sub, approx-equal),
// hkRotation::setTranspose, hkMath::acos/max, hkQuaternion (normalize, setMul, setAxisAngle)
// (0x010813D0..0x01082345). Equivalent portable source. Float grouping follows the disassembly; values the x87
// keeps on its stack without storing are typed hkX87Real and marked "X87-PRECISION".
#include "../s010eb310/hk31_math.h"

// @ 0x010813d0
void hkVector4::setTransformedInversePos(const hkTransform& t, const hkVector4& v)
{
	const float* m = &t.m_rot[0].x;   // 16 floats: three rotation columns then the translation at 12..14
	// X87-PRECISION: the three differences stay on the x87 stack.
	hkX87Real dx = (hkX87Real)v.x - m[12];
	hkX87Real dy = (hkX87Real)v.y - m[13];
	hkX87Real dz = (hkX87Real)v.z - m[14];
	x = (float)((dz * m[2] + dy * m[1]) + dx * m[0]);
	y = (float)((dz * m[6] + dy * m[5]) + dx * m[4]);
	z = (float)((dz * m[10] + dy * m[9]) + dx * m[8]);
	w = 0.0f;
}

// @ 0x01081440
void hkVector4::setRotatedInverseDir(const hkRotation& r, const hkVector4& v)
{
	const float* m = r.m_el;
	float vx = v.x, vy = v.y, vz = v.z;
	x = (vz * m[2] + vy * m[1]) + vx * m[0];
	y = (vz * m[6] + vy * m[5]) + vx * m[4];
	z = (vz * m[10] + vy * m[9]) + vx * m[8];
	w = 0.0f;
}

// @ 0x010814a0
void hkVector4::setRotatedDir(const hkRotation& r, const hkVector4& v)
{
	const float* m = r.m_el;
	float vx = v.x, vy = v.y, vz = v.z;
	x = (vz * m[8] + vy * m[4]) + vx * m[0];
	y = (vz * m[9] + vy * m[5]) + vx * m[1];
	z = (vz * m[10] + vy * m[6]) + vx * m[2];
	w = 0.0f;
}

// ---- hkMath ------------------------------------------------------------------------------------------------
namespace hkMath
{
	template <typename T> T max2(T a, T b);
	template <> float max2<float>(float a, float b);
	float acos(float x);   // 0x01082160 (name guessed: clamped arc cosine)
}

// @ 0x01081500
template <>
float hkMath::max2<float>(float a, float b)
{
	return (a > b) ? a : b;    // fcomp / test ah,0x41 / jne: unordered and equal return b
}

// @ 0x01082160
float hkMath::acos(float x)
{
	// |x| < 1 (or NaN: fcomp / test ah,1) -> CRT acos (x87 _CIacos); otherwise 0 for x > 0, pi for x <= 0.
	if (!(fabsf(x) >= 1.0f))
		return (float)::acos((double)x);
	if (x > 0.0f)
		return 0.0f;
	return 3.14159274101257324f;    // 0x40490fdb
}

// ---- hkMatrix3 --------------------------------------------------------------------------------------------------
// @ 0x01081520
void hkMatrix3::transpose()
{
	float t;
	t = m_el[4]; m_el[4] = m_el[1]; m_el[1] = t;
	t = m_el[8]; m_el[8] = m_el[2]; m_el[2] = t;
	t = m_el[9]; m_el[9] = m_el[6]; m_el[6] = t;
}

// @ 0x01081550
void hkRotation::setTranspose(const hkRotation& r)
{
	// raw dword copies (the binary moves the floats through integer registers)
	uint32_t* d = (uint32_t*)m_el;
	const uint32_t* s = (const uint32_t*)r.m_el;
	d[0] = s[0];
	d[5] = s[5];
	d[10] = s[10];
	d[3] = 0;
	d[7] = 0;
	d[11] = 0;
	d[1] = s[4];
	d[4] = s[1];
	d[2] = s[8];
	d[8] = s[2];
	d[6] = s[9];
	d[9] = s[6];
}

// @ 0x010815a0
hkBool hkMatrix3::isApproximatelyEqual(const hkMatrix3& m, hkReal eps) const
{
	// Per column only x, y and z are tested (the w difference is computed by the binary but masked out). A component
	// fails when eps < |difference| (fcomp / test ah,5 / jp): NaN differences pass.
	for (int c = 0; c < 3; ++c)
	{
		int b = c * 4;
		hkX87Real d0 = (hkX87Real)m_el[b + 0] - m.m_el[b + 0];
		hkX87Real d1 = (hkX87Real)m_el[b + 1] - m.m_el[b + 1];
		hkX87Real d2 = (hkX87Real)m_el[b + 2] - m.m_el[b + 2];
		float a0 = (float)fabs(d0);          // stored to [esp+0x10]
		hkX87Real a1 = fabs(d1);             // X87-PRECISION: |d1| stays on the x87 stack
		float a2 = (float)fabs(d2);          // stored to [esp+0x18]
		bool fail = (eps < a2) || (eps < a1) || (eps < a0);
		if (fail)
			return hkBool(false);
	}
	return hkBool(true);
}

// @ 0x010817c0
void hkMatrix3::setCrossSkewSymmetric(const hkVector4& v)
{
	float vy = v.y;
	float vz = v.z;
	m_el[0] = 0.0f;
	m_el[1] = vz;
	m_el[3] = 0.0f;
	m_el[2] = -vy;
	float vx = v.x;
	vz = v.z;
	m_el[5] = 0.0f;
	m_el[7] = 0.0f;
	m_el[4] = -vz;
	m_el[6] = vx;
	vx = v.x;
	m_el[8] = v.y;
	m_el[9] = -vx;
	m_el[10] = 0.0f;
	m_el[11] = 0.0f;
}

// Shared by invert / invertSymmetric: cofactors of the 3x3 part and the determinant.
// The first element of the second cofactor row stays on the x87 stack unstored.
#define HK_MATRIX3_COFACTORS \
	float c0 = m_el[5] * m_el[10] - m_el[6] * m_el[9];     /* [esp] */ \
	float c1 = m_el[8] * m_el[6] - m_el[4] * m_el[10];     /* [esp+4] */ \
	float c2 = m_el[4] * m_el[9] - m_el[5] * m_el[8];      /* [esp+8] */ \
	hkX87Real r10 = (hkX87Real)m_el[9] * m_el[2] - (hkX87Real)m_el[10] * m_el[1];   /* X87-PRECISION: not stored */ \
	float r11 = m_el[10] * m_el[0] - m_el[8] * m_el[2];    /* [esp+0x24] */ \
	float r12 = m_el[8] * m_el[1] - m_el[9] * m_el[0];     /* [esp+0x28] */ \
	float r20 = m_el[6] * m_el[1] - m_el[5] * m_el[2];     /* [esp+0x10] */ \
	float r21 = m_el[4] * m_el[2] - m_el[6] * m_el[0];     /* [esp+0x14] */ \
	float r22 = m_el[5] * m_el[0] - m_el[4] * m_el[1];     /* [esp+0x18] */ \
	hkX87Real det = ((hkX87Real)c1 * m_el[1] + (hkX87Real)c2 * m_el[2]) + (hkX87Real)c0 * m_el[0];   /* X87-PRECISION */

#define HK_MATRIX3_WRITE_INVERSE \
	hkX87Real inv = 1.0 / det;                                                  /* X87-PRECISION */ \
	m_el[0] = (float)(c0 * inv); \
	m_el[1] = (float)(c1 * inv); \
	m_el[2] = (float)(c2 * inv); \
	float zero = (float)(0.0 * inv);       /* 0 * inv keeps NaN/Inf propagation */ \
	m_el[3] = zero; \
	m_el[4] = (float)(r10 * inv); \
	m_el[5] = (float)(r11 * inv); \
	m_el[6] = (float)(r12 * inv); \
	m_el[7] = zero; \
	m_el[8] = (float)(r20 * inv); \
	m_el[9] = (float)(r21 * inv); \
	m_el[10] = (float)(r22 * inv); \
	m_el[11] = zero;

// @ 0x01081810
hkResult hkMatrix3::invert(hkReal epsilon)
{
	HK_MATRIX3_COFACTORS
	// (eps*eps)*eps < |det|, an ordered "less": otherwise the matrix is rejected (also for NaN)
	hkX87Real eps3 = ((hkX87Real)epsilon * epsilon) * epsilon;
	if (!(eps3 < fabs(det)))
		return HK_FAILURE;
	HK_MATRIX3_WRITE_INVERSE
	// the cofactor matrix is the transpose of the inverse: swap (1,4), (2,8), (6,9)
	float t;
	t = m_el[4]; m_el[4] = m_el[1]; m_el[1] = t;
	t = m_el[8]; m_el[8] = m_el[2]; m_el[2] = t;
	t = m_el[9]; m_el[9] = m_el[6]; m_el[6] = t;
	return HK_SUCCESS;
}

// @ 0x01081990
void hkMatrix3::invertSymmetric()
{
	HK_MATRIX3_COFACTORS
	// determinant clamped to at least 2^-69 (0x1d000000); NaN keeps the determinant
	if (1.69406589e-21f > det)
		det = 1.69406589e-21f;
	HK_MATRIX3_WRITE_INVERSE
}

// @ 0x01081ad0
void hkMatrix3::add(const hkMatrix3& m)
{
	for (int i = 0; i < 12; ++i)
		m_el[i] = m.m_el[i] + m_el[i];
}

// @ 0x01081b40
void hkMatrix3::sub(const hkMatrix3& m)
{
	for (int i = 0; i < 12; ++i)
		m_el[i] = m_el[i] - m.m_el[i];
}

// @ 0x01081bb0
void hkMatrix3::mul(hkReal scale)
{
	for (int i = 0; i < 12; ++i)
		m_el[i] = scale * m_el[i];
}

// @ 0x01081c30
// C-style helper (cdecl, symbol _hkMatrix3_setMulMat3Mat3): out = a * b. All of a is loaded first, then each column
// of b is read just before its column of out is written (so out may alias a but not b).
extern "C" void hkMatrix3_setMulMat3Mat3(hkMatrix3* out, const hkMatrix3* a, const hkMatrix3* b)
{
	float a0 = a->m_el[0], a1 = a->m_el[1], a2 = a->m_el[2];
	float a4 = a->m_el[4], a5 = a->m_el[5], a6 = a->m_el[6];
	float a8 = a->m_el[8], a9 = a->m_el[9], a10 = a->m_el[10];
	float b0 = b->m_el[0], b2 = b->m_el[2], b1 = b->m_el[1];
	out->m_el[0] = b0 * a0 + (a4 * b1 + a8 * b2);
	out->m_el[1] = b0 * a1 + (a5 * b1 + a9 * b2);
	out->m_el[2] = b0 * a2 + (a6 * b1 + a10 * b2);
	out->m_el[3] = 0.0f;
	b2 = b->m_el[6]; b0 = b->m_el[4]; b1 = b->m_el[5];
	out->m_el[4] = b0 * a0 + (a4 * b1 + a8 * b2);
	out->m_el[5] = b0 * a1 + (a5 * b1 + a9 * b2);
	out->m_el[6] = b0 * a2 + (a6 * b1 + a10 * b2);
	out->m_el[7] = 0.0f;
	b0 = b->m_el[8]; b1 = b->m_el[9]; b2 = b->m_el[10];
	out->m_el[8] = b0 * a0 + (a4 * b1 + a8 * b2);
	out->m_el[9] = b0 * a1 + (a5 * b1 + a9 * b2);
	out->m_el[10] = b0 * a2 + (a6 * b1 + a10 * b2);
	out->m_el[11] = 0.0f;
}

// @ 0x01081db0
void hkMatrix3::setMul(const hkMatrix3& a, const hkMatrix3& b)
{
	float a2 = a.m_el[2];
	float a0 = a.m_el[0];
	float a1 = a.m_el[1];
	float a5 = a.m_el[5];
	float a4 = a.m_el[4];
	float a8 = a.m_el[8];
	float a6 = a.m_el[6];
	float a9 = a.m_el[9];
	float a10 = a.m_el[10];
	float b0 = b.m_el[0];
	float b2 = b.m_el[2];
	float b1 = b.m_el[1];
	m_el[0] = b0 * a0 + (a4 * b1 + a8 * b2);
	m_el[1] = b0 * a1 + (a5 * b1 + a9 * b2);
	m_el[2] = b0 * a2 + (a6 * b1 + a10 * b2);
	m_el[3] = 0.0f;
	b2 = b.m_el[6];
	b0 = b.m_el[4];
	b1 = b.m_el[5];
	m_el[4] = b0 * a0 + (a4 * b1 + a8 * b2);
	m_el[5] = b0 * a1 + (a5 * b1 + a9 * b2);
	m_el[6] = b0 * a2 + (a6 * b1 + a10 * b2);
	m_el[7] = 0.0f;
	b0 = b.m_el[8];
	b1 = b.m_el[9];
	b2 = b.m_el[10];
	m_el[8] = b0 * a0 + (a4 * b1 + a8 * b2);
	m_el[9] = b0 * a1 + (a5 * b1 + a9 * b2);
	m_el[10] = b0 * a2 + (a6 * b1 + a10 * b2);
	m_el[11] = 0.0f;
}

// @ 0x01081f20
void hkRotation::setMulInverse(const hkMatrix3& a, const hkRotation& b)
{
	// this = a * inverse(b), the inverse of a rotation being its transpose
	float b0 = b.m_el[0], b5 = b.m_el[5], b1 = b.m_el[1], b4 = b.m_el[4], b8 = b.m_el[8];
	float b10 = b.m_el[10], b2 = b.m_el[2], b9 = b.m_el[9], b6 = b.m_el[6];
	float a0 = a.m_el[0], a1 = a.m_el[1], a2 = a.m_el[2];
	float a4 = a.m_el[4], a5 = a.m_el[5], a6 = a.m_el[6];
	float a8 = a.m_el[8], a9 = a.m_el[9], a10 = a.m_el[10];
	m_el[0] = b0 * a0 + (b4 * a4 + a8 * b8);
	m_el[1] = b0 * a1 + (b4 * a5 + a9 * b8);
	m_el[2] = b0 * a2 + (b4 * a6 + b8 * a10);
	m_el[3] = 0.0f;
	m_el[4] = b1 * a0 + (b5 * a4 + b9 * a8);
	m_el[5] = b1 * a1 + (b5 * a5 + b9 * a9);
	m_el[6] = b1 * a2 + (b5 * a6 + b9 * a10);
	m_el[7] = 0.0f;
	m_el[8] = b2 * a0 + (b10 * a8 + b6 * a4);
	m_el[9] = b2 * a1 + (b10 * a9 + b6 * a5);
	m_el[10] = b2 * a2 + (b10 * a10 + b6 * a6);
	m_el[11] = 0.0f;
}

// @ 0x010820b0
void hkMatrix3::mul(const hkMatrix3& m)
{
	hkMatrix3 tmp;
	tmp.setMul(*this, m);
	for (int i = 0; i < 12; ++i)
		m_el[i] = tmp.m_el[i];
}

// @ 0x01082130
void hkMatrix3::changeBasis(const hkRotation& r)
{
	// this = r * this * inverse(r): tmp = this * inverse(r); this = r * tmp
	hkRotation tmp;
	tmp.setMulInverse(*this, r);
	setMul(r, tmp);
}

// ---- hkQuaternion ----------------------------------------------------------------------------------------------------
// @ 0x010821a0
void hkQuaternion::normalize()
{
	// X87-PRECISION: the squared length and the reciprocal square root stay on the x87 stack (inline fsqrt).
	hkX87Real len2 = (((hkX87Real)m_vec[0] * m_vec[0] + (hkX87Real)m_vec[1] * m_vec[1]) + (hkX87Real)m_vec[2] * m_vec[2])
	                 + (hkX87Real)m_vec[3] * m_vec[3];
	hkX87Real inv = (len2 == 0.0) ? 0.0 : 1.0 / sqrt(len2);
	m_vec[0] = (float)(inv * m_vec[0]);
	m_vec[1] = (float)(inv * m_vec[1]);
	m_vec[2] = (float)(inv * m_vec[2]);
	m_vec[3] = (float)(inv * m_vec[3]);
}

// @ 0x01082210
void hkQuaternion::setMul(const hkQuaternion& a, const hkQuaternion& b)
{
	// All inputs are read before any output is written, so this may alias a or b.
	// X87-PRECISION: the x/y cross terms (X1, Y1) and the z sum stay on the x87 stack.
	hkX87Real X1 = (hkX87Real)b.m_vec[2] * a.m_vec[1] - (hkX87Real)a.m_vec[2] * b.m_vec[1];
	hkX87Real Y1 = (hkX87Real)a.m_vec[2] * b.m_vec[0] - (hkX87Real)b.m_vec[2] * a.m_vec[0];
	float Z1 = (float)((hkX87Real)b.m_vec[1] * a.m_vec[0] - (hkX87Real)b.m_vec[0] * a.m_vec[1]);   // [esp+0x18]
	float aw = a.m_vec[3];
	float tx = (float)((hkX87Real)aw * b.m_vec[0] + X1);       // [esp+0x10]
	float ty = (float)((hkX87Real)aw * b.m_vec[1] + Y1);       // [esp+0x14]
	hkX87Real tz = (hkX87Real)aw * b.m_vec[2] + Z1;            // kept on the x87 stack
	float bw = b.m_vec[3];
	float rx = (float)((hkX87Real)bw * a.m_vec[0] + tx);
	float ry = (float)((hkX87Real)bw * a.m_vec[1] + ty);
	float rz = (float)((hkX87Real)bw * a.m_vec[2] + tz);
	float rw = (float)((hkX87Real)a.m_vec[3] * b.m_vec[3]
	                   - (((hkX87Real)a.m_vec[0] * b.m_vec[0] + (hkX87Real)b.m_vec[1] * a.m_vec[1]) + (hkX87Real)a.m_vec[2] * b.m_vec[2]));
	m_vec[2] = rz;
	m_vec[0] = rx;
	m_vec[1] = ry;
	m_vec[3] = rw;
}

// @ 0x01082310
void hkQuaternion::setAxisAngle(const hkVector4& axis, hkReal angle)
{
	// X87-PRECISION: half-angle and sin stay on the x87 stack. Inline fsin / fcos (x87 transcendental accuracy).
	hkX87Real half = (hkX87Real)angle * 0.5f;
	hkX87Real s = sin(half);
	m_vec[0] = (float)(s * axis.x);
	m_vec[1] = (float)(s * axis.y);
	m_vec[2] = (float)(s * axis.z);
	m_vec[3] = (float)(s * axis.w);    // overwritten below; the binary still performs this multiply and store
	m_vec[3] = (float)cos(half);
}
