// hkConvexPenetrationUtil simplex evolution step @ 0x01121610 (1616 bytes, __thiscall, ret 8) -- Havok 3.1.0 (VC .NET 2003, /vc71).
//
// The expanding-simplex / GJK "evolve" loop used by calculatePenetrationDepth (0x01121c60). The simplex lives in three
// parallel arrays: m_w (difference vertices), m_a (support points on A), m_b (support points on B), with the live vertex
// count behind a pointer (m_num). Depending on the count the step runs one of case0To1 / case1To2 / case2To3, checks
// whether the current sub-simplex (point, segment, triangle) is degenerate against the tolerance m_eps, and for a
// triangle projects the normal through findBestProjection to add a 4th vertex. A tetrahedron whose volume is
// negligible means the origin is outside: the function returns 0. A hit within m_bestDist fills hkGskOut with the normal, the
// barycentric-interpolated closest point on A, and status 0. Status 3 is returned when the simplex cannot progress.
typedef unsigned char uint8_t;
#include <math.h>

struct __declspec(align(16)) hkVector4
{
	float x, y, z, w;
};

class hkBool
{
public:
	hkBool() {}
	hkBool(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
private:
	char m_bool;
};

struct hkGskOut
{
	hkVector4 m_normal;   // +0
	hkVector4 m_point;    // +0x10
	float m_dist;         // +0x20
	float m_half;         // +0x24 (0.5 on success)
};

struct hkWingedEdgeVertex
{
	hkVector4 m_w;
	hkVector4 m_a;
	hkVector4 m_b;
};

struct hkCollideTriangleUtil
{
	static void calcBarycentricCoordinates(const hkVector4& p, const hkVector4& a, const hkVector4& b, const hkVector4& c, float* out);   // 0x01105630
};

extern const hkVector4 g_hkZeroVector;   // 0x016E42D0

struct hkConvexPenetrationUtil
{
	char m_pad0[0x40];
	float m_bestDist;       // +0x40
	char m_pad44[0x0c];
	float m_eps;            // +0x50
	char m_pad54[0x0c];
	hkVector4* m_a;         // +0x60
	hkVector4* m_b;         // +0x64
	hkVector4* m_w;         // +0x68
	int* m_num;             // +0x6c

	void findBestProjection(const hkVector4& dir, const hkVector4& w, hkWingedEdgeVertex& out, float& dist);   // 0x011210c0
	hkBool case0To1(hkGskOut& out);   // 0x011211a0
	void case1To2();                  // 0x011212f0
	void case2To3();                  // 0x011213e0
	int evolve(hkGskOut& out, int& status);   // 0x01121610
};

static inline float sqrtInverse(float v)
{
	return v == 0.0f ? 0.0f : 1.0f / sqrtf(v);
}

int hkConvexPenetrationUtil::evolve(hkGskOut& out, int& status)
{
	int prev = -1;
	hkVector4 n;
	hkWingedEdgeVertex vtx;
	float dist;
	float bary[4];
	const hkVector4* W;

	switch (*m_num)
	{
	case 0: goto c0;
	case 1: goto c1;
	case 2: goto c2;
	case 3: goto c3;
	case 4: goto c4;
	default: status = 3; return 1;
	}

c4:
	{
		const hkVector4* Wt = m_w;
		float tax = Wt[1].x - Wt[2].x, tay = Wt[1].y - Wt[2].y;
		float cx = (Wt[1].z - Wt[2].z) * (Wt[0].y - Wt[1].y) - tay * (Wt[0].z - Wt[1].z);
		float cy = (Wt[0].z - Wt[1].z) * tax - (Wt[1].z - Wt[2].z) * (Wt[0].x - Wt[1].x);
		float cz = tay * (Wt[0].x - Wt[1].x) - (Wt[0].y - Wt[1].y) * tax;
		float vol = (Wt[3].x - Wt[0].x) * cx + (Wt[3].y - Wt[0].y) * cy + (Wt[3].z - Wt[0].z) * cz;
		if ((cx * cx + cy * cy + cz * cz) * m_eps < vol * vol) { status = 0; return 0; }
	}
	if (prev > 2) { status = 3; return 1; }
	--*m_num;
c3:
	{
		W = m_w;
		float ax = W[0].x - W[1].x, ay = W[0].y - W[1].y, az = W[0].z - W[1].z;
		float bx = W[1].x - W[2].x, by = W[1].y - W[2].y, bz = W[1].z - W[2].z;
		n.w = 0.0f;
		n.x = bz * ay - by * az;
		n.y = az * bx - bz * ax;
		n.z = by * ax - ay * bx;
	}
	{
		float nl2 = n.x * n.x + n.y * n.y + n.z * n.z;
		if (nl2 == 0.0f)
		{
			if (prev >= 2) goto degenerate;
			--*m_num;
			goto c2;
		}
		prev = 3;
		float il = sqrtInverse(nl2);
		n.x *= il; n.y *= il; n.z *= il; n.w *= il;
		goto expand;
	}
c2:
	{
		W = m_w;
		float dx = W[0].x - W[1].x;
		float dy = W[0].y - W[1].y;
		float dz = W[0].z - W[1].z;
		float l2 = dx * dx + dy * dy + dz * dz;
		if (l2 > m_eps)
		{
			prev = 2;
			case2To3();
			goto c3;
		}
	}
	if (prev > 0) { status = 3; return 1; }
	--*m_num;
c1:
	{
		W = m_w;
		float len2 = W[0].x * W[0].x + W[0].y * W[0].y + W[0].z * W[0].z;
		if (len2 > m_eps)
		{
			prev = 1;
			case1To2();
			goto c2;
		}
	}
	if (prev >= 0) { status = 3; return 1; }
	--*m_num;
c0:
	if (case0To1(out)) { status = 0; return 1; }
	prev = 0;
	goto c1;

expand:
	findBestProjection(n, *m_w, vtx, dist);
	if (dist < m_bestDist)
	{
		out.m_normal = n;
		out.m_dist = 0.0f;
		const hkVector4* Wv = m_w;
		hkCollideTriangleUtil::calcBarycentricCoordinates(g_hkZeroVector, Wv[0], Wv[1], Wv[2], bary);
		const hkVector4* A = m_a;
		out.m_point.x = bary[0] * A[0].x + bary[1] * A[1].x + bary[2] * A[2].x;
		out.m_point.y = bary[0] * A[0].y + bary[1] * A[1].y + bary[2] * A[2].y;
		out.m_point.z = bary[0] * A[0].z + bary[1] * A[1].z + bary[2] * A[2].z;
		out.m_point.w = bary[0] * A[0].w + bary[1] * A[1].w + bary[2] * A[2].w;
		goto done;
	}
	m_w[*m_num] = vtx.m_w;
	m_a[*m_num] = vtx.m_a;
	m_b[*m_num] = vtx.m_b;
	++*m_num;
	goto c4;

degenerate:
	{
		// degenerate triangle: build any direction perpendicular to the segment W0-W1
		float d[4];
		out.m_dist = 0.0f;
		W = m_w;
		d[0] = W[0].x - W[1].x;
		d[1] = W[0].y - W[1].y;
		d[2] = W[0].z - W[1].z;
		d[3] = W[0].w - W[1].w;
		float a0 = fabsf(d[0]);
		float a1 = fabsf(d[1]);
		int i = 0, j = 1, k = 2;
		float mn = a0;
		if (a1 < a0) { i = 1; j = 0; mn = a1; }
		if (fabsf(d[2]) < mn) { k = i; i = 2; }
		float* o = &out.m_normal.x;
		o[i] = 0.0f;
		o[3] = 0.0f;
		o[j] = d[k];
		o[k] = -d[j];
		float il = sqrtInverse(o[0] * o[0] + o[1] * o[1] + o[2] * o[2]);
		o[0] *= il; o[1] *= il; o[2] *= il; o[3] *= il;
		W = m_w;
		const hkVector4* A = m_a;
		float s = (fabsf(W[0].z) + fabsf(W[0].y)) + fabsf(W[0].x);
		float t = s / ((s + s) + 1.1920929e-07f);
		float u = 1.0f - t;
		out.m_point.x = u * A[0].x + t * A[1].x;
		out.m_point.y = u * A[0].y + t * A[1].y;
		out.m_point.z = u * A[0].z + t * A[1].z;
		out.m_point.w = u * A[0].w + t * A[1].w;
	}
done:
	out.m_half = 0.5f;
	status = 0;
	return 1;
}
