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

// A non-16-aligned vec used only by hkTransform, so hkConvexPenetrationUtil keeps
// the alignment it had when its head was a plain char[0x40] (adding an align(16)
// member changed the committed evolve() codegen by one byte).
struct hkVec4f
{
	float x, y, z, w;
};

struct hkTransform
{
	hkVec4f m_col0;   // +0x00
	hkVec4f m_col1;   // +0x10
	hkVec4f m_col2;   // +0x20
	hkVec4f m_col3;   // +0x30 (translation)
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

struct hkWingedEdge;   // defined below (the polytope accelerator)

// hkConvexShape: only the support-mapping slot is used here (vtable slot 0x24).
struct hkConvexShape
{
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void getSupportingVertex(const hkVector4& dir, hkVector4* out);   // slot 0x24
};

struct hkConvexPenetrationUtil
{
	hkTransform m_xf;       // +0x00 (basis cols +0x00/+0x10/+0x20, translation +0x30)
	float m_bestDist;       // +0x40
	float m_sphereR;        // +0x44
	float m_scale1;         // +0x48
	float m_scale2;         // +0x4c
	float m_eps;            // +0x50
	hkConvexShape* m_shape0; // +0x54
	hkConvexShape* m_shape1; // +0x58
	int   m_simplexCount;   // +0x5c
	hkVector4* m_a;         // +0x60
	hkVector4* m_b;         // +0x64
	hkVector4* m_w;         // +0x68
	int* m_num;             // +0x6c

	void findBestProjection(const hkVector4& dir, const hkVector4& w, hkWingedEdgeVertex& out, float& dist);   // 0x011210c0
	hkBool case0To1(hkGskOut& out);   // 0x011211a0
	void case1To2();                  // 0x011212f0
	void case2To3();                  // 0x011213e0
	int evolve(hkGskOut& out, int& status);   // 0x01121610

	void init(hkConvexShape* shapeA, hkConvexShape* shapeB, const hkTransform& xf, float k,
	          void* a, void* b, hkVector4* w, int* num);   // 0x01120f40
	void getPointForSimplex(const hkVector4& dir, hkWingedEdgeVertex& out);   // 0x01120fb0
	int calculatePenetrationDepth(hkGskOut& out);   // 0x01121c60

	void addPointToSimplex(const hkWingedEdgeVertex& vtx);   // 0x01120a00
	hkBool tryToExpandPolytope(hkWingedEdge* edge, void* tri, const hkWingedEdgeVertex& vtx, int* status);  // 0x01120a80
	void randomVector(int seed, float lo, float hi, hkVector4* out);   // 0x01120eb0
	void convertResultToFeature(hkWingedEdge* edge, void* tri, hkGskOut* out);   // 0x01120c40
};


static inline float sqrtInverse(float v)
{
	return v == 0.0f ? 0.0f : 1.0f / sqrtf(v);
}

// ---- shared helpers reached from the simplex steps (Havok, VC .NET 2003) ----
// hkTransform_::assign is a __thiscall member (this in ecx, src on the stack);
// MSVC rejects __thiscall on free functions, so model it on a dummy class.
struct hkTransformAssign
{
	void assign(const void* src);   // 0x01088410 (this = hkTransform*)
};
#define hkTransform_assign(self, dummy, src) (((hkTransformAssign*)(self))->assign(src))
// hkWingedEdge: the polytope accelerator the depth routine builds (0x01120850 / 0x01120770).
struct hkWingedEdge
{
	void  initializeWithTetrahedron(hkVector4* a, hkVector4* b, hkVector4* w);   // 0x01120850
	void* findTriangleOnNearestPlane();   // 0x01120770
};
extern void FUN_01114310(hkVector4* v);                              // 0x01114310
extern const hkVector4 g_hkZero15;                                   // 0x015b9b30 (four zero floats)

// the accumulate/quantised vertex type used by the winged-edge polytope
struct hkWingedEdgeVertexAcc
{
	hkVector4 m_pos;    // +0x00
	hkVector4 m_pad10;  // +0x10
	hkVector4 m_pad20;  // +0x20
	int       m_flag30; // +0x30
};


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

// ===========================================================================
// 0x01120f40  hkConvexPenetrationUtil::init -- 97 bytes, __thiscall, ret 0x20.
// Copy the transform in, seed m_eps with k^2 and clear the simplex counters.
// Args (after ecx): shapeA(+0x54), shapeB(+0x58), transform(+0x44..+0x4c),
// float k, a(+0x60), b(+0x64), w(+0x68), num(+0x6c).
// ===========================================================================
// @ 0x01120f40
void hkConvexPenetrationUtil::init(hkConvexShape* shapeA, hkConvexShape* shapeB,
                                   const hkTransform& xf, float k,
                                   void* a, void* b, hkVector4* w, int* num)
{
	hkTransform_assign(&m_xf, 0, &xf);   // +0x00
	m_shape0 = shapeA;                // +0x54
	m_shape1 = shapeB;                // +0x58
	m_bestDist = k;                   // +0x40
	m_scale2   = k;                   // +0x4c
	m_sphereR  = k;                   // +0x44
	m_scale1   = k;                   // +0x48
	m_a  = (hkVector4*)a;             // +0x60
	m_b  = (hkVector4*)b;             // +0x64
	m_simplexCount = 0;               // +0x5c
	m_w  = w;                         // +0x68
	m_num = num;                      // +0x6c
	m_eps      = k * k;               // +0x50
}

// ===========================================================================
// 0x01120fb0  hkConvexPenetrationUtil::getPointForSimplex -- 266 bytes,
// __thiscall ret 8.  dir -> support point on A (out.m_a) and on B via the
// negated, inverse-rotated direction (out.m_b); out.m_w = m_a - xf(m_b).
// ===========================================================================
// @ 0x01120fb0
void hkConvexPenetrationUtil::getPointForSimplex(const hkVector4& dir, hkWingedEdgeVertex& out)
{
	m_shape0->getSupportingVertex(dir, &out.m_a);         // shape0->slot 0x24

	hkVector4 nd;
	nd.x = -(dir.x * m_xf.m_col0.x + dir.z * m_xf.m_col2.x + dir.y * m_xf.m_col1.x);
	nd.y = -(dir.x * m_xf.m_col0.y + dir.z * m_xf.m_col2.y + dir.y * m_xf.m_col1.y);
	nd.z = -(dir.x * m_xf.m_col0.z + dir.z * m_xf.m_col2.z + dir.y * m_xf.m_col1.z);
	nd.w = 0.0f;
	m_shape1->getSupportingVertex(nd, &out.m_b);          // shape1->slot 0x24

	out.m_w.x = out.m_a.x - (out.m_b.x * m_xf.m_col0.x + (out.m_b.y * m_xf.m_col1.x + out.m_b.z * m_xf.m_col2.x) + m_xf.m_col3.x);
	out.m_w.y = out.m_a.y - (out.m_b.x * m_xf.m_col0.y + (out.m_b.y * m_xf.m_col1.y + out.m_b.z * m_xf.m_col2.y) + m_xf.m_col3.y);
	out.m_w.z = out.m_a.z - (out.m_b.x * m_xf.m_col0.z + (out.m_b.y * m_xf.m_col1.z + out.m_b.z * m_xf.m_col2.z) + m_xf.m_col3.z);
	out.m_w.w = out.m_b.w;
}

// ===========================================================================
// 0x011210c0  hkConvexPenetrationUtil::findBestProjection -- 221 bytes,
// __thiscall ret 0x10.  Compare the support point along `dir` with the one
// along -dir and keep the one that is furthest from `vtx`; report its distance.
// ===========================================================================
// @ 0x011210c0
void hkConvexPenetrationUtil::findBestProjection(const hkVector4& dir, const hkVector4& vtx,
                                                 hkWingedEdgeVertex& out, float& dist)
{
	hkVector4 neg;
	neg.x = -dir.x;
	neg.y = -dir.y;
	neg.z = -dir.z;
	neg.w = -dir.w;

	hkWingedEdgeVertex va;
	getPointForSimplex(dir, va);
	getPointForSimplex(neg, out);

	float f1 = (va.m_w.x - vtx.x) * dir.x + ((va.m_w.y - vtx.y) * dir.y + (va.m_w.z - vtx.z) * dir.z);
	float f2 = (out.m_w.x - vtx.x) * neg.x + ((out.m_w.y - vtx.y) * neg.y + (out.m_w.z - vtx.z) * neg.z);
	if (f2 <= f1)
	{
		FUN_01114310(&va.m_w);
		dist = f1;
		return;
	}
	dist = f2;
}

// ===========================================================================
// 0x011211a0  hkConvexPenetrationUtil::case0To1 -- 325 bytes, __thiscall
// ret 8 (returns hkBool by value).  Grow a 0-simplex to a 1-simplex.
// ===========================================================================
// @ 0x011211a0
hkBool hkConvexPenetrationUtil::case0To1(hkGskOut& out)
{
	hkVector4 d;
	d.x = -m_xf.m_col3.x;
	d.y = -m_xf.m_col3.y;
	d.z = -m_xf.m_col3.z;
	d.w = -m_xf.m_col3.w;

	float t2 = m_xf.m_col3.z * m_xf.m_col3.z
	         + (m_xf.m_col3.y * m_xf.m_col3.y + m_xf.m_col3.x * m_xf.m_col3.x);
	if (t2 >= m_eps)
		d = g_hkZero15;

	hkWingedEdgeVertex vtx;
	getPointForSimplex(d, vtx);
	addPointToSimplex(vtx);

	hkVector4* w = m_w;
	float w2 = w[0].z * w[0].z + (w[0].y * w[0].y + w[0].x * w[0].x);
	if (w2 >= m_eps)
	{
		out.m_normal = d;
		out.m_point  = vtx.m_a;
		out.m_dist   = sqrtf(w2);
		out.m_half   = 0.5f;
		return hkBool(true);
	}
	return hkBool(false);
}

// ===========================================================================
// 0x011212f0  hkConvexPenetrationUtil::case1To2 -- 235 bytes, __thiscall ret 0.
// Grow a 1-simplex to a 2-simplex: probe both directions along m_w[0].
// ===========================================================================
// @ 0x011212f0
void hkConvexPenetrationUtil::case1To2()
{
	hkVector4* w = m_w;
	hkWingedEdgeVertex v90;
	getPointForSimplex(*w, v90);

	hkVector4* w2 = m_w;
	hkVector4 neg;
	neg.x = -w2[0].x;
	neg.y = -w2[0].y;
	neg.z = -w2[0].z;
	neg.w = -w2[0].w;
	hkWingedEdgeVertex v50;
	getPointForSimplex(neg, v50);

	hkVector4* w3 = m_w;
	float d90 = (v90.m_w.x - w3[0].x) * (v90.m_w.x - w3[0].x)
	          + ((v90.m_w.y - w3[0].y) * (v90.m_w.y - w3[0].y)
	          + (v90.m_w.z - w3[0].z) * (v90.m_w.z - w3[0].z));
	float d50 = (v50.m_w.x - w3[0].x) * (v50.m_w.x - w3[0].x)
	          + ((v50.m_w.y - w3[0].y) * (v50.m_w.y - w3[0].y)
	          + (v50.m_w.z - w3[0].z) * (v50.m_w.z - w3[0].z));
	if (d90 >= d50)
		addPointToSimplex(v90);
	else
		addPointToSimplex(v50);
}

// ===========================================================================
// 0x011213e0  hkConvexPenetrationUtil::case2To3 -- 549 bytes, __thiscall ret 0.
// Grow a 2-simplex to a 3-simplex: build two perpendicular directions from the
// segment m_w[0]-m_w[1], project each, and keep the closer support point.
// ===========================================================================
// @ 0x011213e0
void hkConvexPenetrationUtil::case2To3()
{
	hkVector4* W = m_w;
	float b0[4];
	b0[0] = W[0].x - W[1].x;
	b0[1] = W[0].y - W[1].y;
	b0[2] = W[0].z - W[1].z;
	b0[3] = W[0].w - W[1].w;

	float a0 = fabsf(b0[0]);
	float a1 = fabsf(b0[1]);
	float a2 = fabsf(b0[2]);
	bool  bVar4 = a0 <= a1;
	float fmin  = bVar4 ? a0 : a1;
	int   iMin  = bVar4 ? 0 : 1;
	int   iMax  = 2;
	if (a2 < fmin)
	{
		iMin = 2;
		iMax = bVar4 ? 0 : 1;
	}

	float d0[4];
	d0[iMin] = 0.0f;
	d0[bVar4 ? 1 : 0] = b0[iMax];
	d0[iMax] = -b0[bVar4 ? 1 : 0];

	float c0 = d0[2] * b0[1] - d0[1] * b0[2];
	float c1 = b0[2] * d0[0] - d0[2] * b0[0];
	float c2 = d0[1] * b0[0] - d0[0] * b0[1];

	float il = sqrtInverse(d0[0] * d0[0] + (d0[2] * d0[2] + d0[1] * d0[1]));
	d0[0] *= il; d0[1] *= il; d0[2] *= il; d0[3] = il * 0.0f;

	float il2 = sqrtInverse(c0 * c0 + (c1 * c1 + c2 * c2));
	hkVector4 ev;
	ev.x = c0 * il2;
	ev.y = c1 * il2;
	ev.z = c2 * il2;
	ev.w = il2 * 0.0f;

	hkWingedEdgeVertex vA, vB;
	float distA, distB;
	findBestProjection(*(hkVector4*)d0, W[0], vA, distA);
	findBestProjection(ev, W[0], vB, distB);
	if (distB < distA)
		addPointToSimplex(vA);
	else
		addPointToSimplex(vB);
}

// ===========================================================================
// 0x01121c60  hkConvexPenetrationUtil::calculatePenetrationDepth -- 426 bytes,
// __thiscall ret 4.  Drive evolve / polytope expansion until a result is found,
// perturbing the search direction on failure (up to 20 restarts).
// ===========================================================================
// @ 0x01121c60
int hkConvexPenetrationUtil::calculatePenetrationDepth(hkGskOut& out)
{
	int status;
	hkWingedEdge edge;
	hkWingedEdgeVertexAcc verts[64];
	int count;
	hkVector4 jitter;
	void* tri = 0;

	for (;;)
	{
		status = 0;
		int e = evolve(out, status);
		if (e == 1)
		{
			if (status != 3)
				return status;
		}
		else
		{
			edge.initializeWithTetrahedron(m_a, m_b, m_w);
			tri = edge.findTriangleOnNearestPlane();
			count = 0;
			verts[count].m_flag30 = 0;
			count = count + 1;
			getPointForSimplex(*(hkVector4*)tri, *(hkWingedEdgeVertex*)&verts[count - 1]);
			int r = tryToExpandPolytope(&edge, tri, *(hkWingedEdgeVertex*)&verts[count - 1], &status);
			for (;;)
			{
				if (r == 1)
					break;
				if (0x36 < count)
				{
					count = 2;
					break;
				}
				tri = edge.findTriangleOnNearestPlane();
				verts[count].m_flag30 = 0;
				count = count + 1;
				getPointForSimplex(*(hkVector4*)tri, *(hkWingedEdgeVertex*)&verts[count - 1]);
				r = tryToExpandPolytope(&edge, tri, *(hkWingedEdgeVertex*)&verts[count - 1], &status);
			}
			if (status != 3)
			{
				convertResultToFeature(&edge, tri, &out);
				return status;
			}
		}

		int c = m_simplexCount + 1;
		m_simplexCount = c;
		if (c == 1)
		{
			*m_num = 1;
		}
		else
		{
			if (c > 0x13)
				return status;
			*m_num = 0;
			randomVector(c, -1.0e-4f, 1.0e-4f, &jitter);
			jitter.x += m_xf.m_col3.x;
			jitter.y += m_xf.m_col3.y;
			jitter.z += m_xf.m_col3.z;
			jitter.w += m_xf.m_col3.w;
			m_xf.m_col3.x = jitter.x;
			m_xf.m_col3.y = jitter.y;
			m_xf.m_col3.z = jitter.z;
			m_xf.m_col3.w = jitter.w;
		}
	}
}

