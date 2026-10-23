// Slice s01105630 -- Havok 3.1.0 hkCollideTriangleUtil: triangle point/segment queries used by the
// shape-shape collision agents.
//
//  0x01105630  hkCollideTriangleUtil::calcBarycentricCoordinates
//  0x01105940  hkCollideTriangleUtil::closestLineSegLineSeg
//  0x01105c30  hkCollideTriangleUtil::closestPointLineSeg
//  0x01105d80  hkCollideTriangleUtil::setupClosestPointTriangleCache
//  0x01105e90  hkCollideTriangleUtil::setupPointTriangleDistanceCache
//  0x01106010  hkCollideTriangleUtil::closestPointTriangle
//
// Havok 3.1.0 was built with VC .NET 2003 and the scalar (x87) math path, so this slice compiles with
// /vc71 and no /arch:SSE. Layouts come from the disassembly; the member names follow the Havok 6.x
// headers and are used for naming only.
#include "types.h"
#include <math.h>

#define HK_ALIGN16 __declspec(align(16))
#define HK_CALL __cdecl
typedef float hkReal;

struct HK_ALIGN16 hkVector4
{
	float x, y, z, w;
	void setSub4(const hkVector4& a, const hkVector4& b)
	{ x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
	void setAdd4(const hkVector4& a, const hkVector4& b)
	{ x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; w = a.w + b.w; }
	void setCross(const hkVector4& a, const hkVector4& b)
	{ x = a.y*b.z - a.z*b.y; y = a.z*b.x - a.x*b.z; z = a.x*b.y - a.y*b.x; }
	hkReal dot3(const hkVector4& v) const { return x*v.x + (y*v.y + z*v.z); }
	hkReal lengthSquared3() const { return x*x + (y*y + z*z); }
	hkReal length3() const { return sqrtf(lengthSquared3()); }
	void addMul4(hkReal r, const hkVector4& v)
	{ x += v.x*r; y += v.y*r; z += v.z*r; w += v.w*r; }
};
inline hkVector4 operator-(const hkVector4& a, const hkVector4& b)
{ hkVector4 r; r.setSub4(a, b); return r; }

class hkCollideTriangleUtil
{
public:
	// ClosestPointLineSegResult: the closest point on the segment (+ reserved fields).
	struct ClosestPointLineSegResult
	{
		hkVector4 m_point;      // +0
		uint32_t m_reserved[4]; // +0x10
	};
	// ClosestLineSegLineSegResult: closest point on the first segment, the vector between the two
	// closest points (first - second) and its squared length.
	struct ClosestLineSegLineSegResult
	{
		hkVector4 m_closestPoint;    // +0
		hkVector4 m_direction;       // +0x10
		hkReal    m_distanceSquared; // +0x20
	};
	struct ClosestPointTriangleCache
	{
		hkReal m_QQ;             // +0
		hkReal m_RR;             // +4
		hkReal m_QR;             // +8
		hkReal m_invTriNormal;   // +0xc
	};
	struct PointTriangleDistanceCache
	{
		hkReal m_invLen0;        // +0
		hkReal m_invLen1;        // +4
		hkReal m_invLen2;        // +8
		hkReal m_invTriNormal;   // +0xc
		hkReal m_triNormalLen;   // +0x10
	};
	struct ClosestPointTriangleResult
	{
		hkVector4 m_hitDirection;   // +0 (w = 0)
		hkReal    m_distance;       // +0x10
	};
	enum ClosestPointTriangleStatus
	{
		CLOSEST_POINT_TRIANGLE_FACE = 0,
		CLOSEST_POINT_TRIANGLE_EDGE = 1
	};

	static void HK_CALL calcBarycentricCoordinates(const hkVector4& A, const hkVector4& B, const hkVector4& C,
	                                              const hkVector4& P, hkReal* barycentric);              // 0x01105630
	static int HK_CALL closestLineSegLineSeg(const hkVector4& p1, const hkVector4& q1, const hkVector4& p2,
	                                         const hkVector4& q2, ClosestLineSegLineSegResult& result);      // 0x01105940
	static int HK_CALL closestPointLineSeg(const hkVector4& point, const hkVector4& lineStart, const hkVector4& lineEnd,
	                                       ClosestPointLineSegResult& result);                               // 0x01105c30
	static void HK_CALL setupClosestPointTriangleCache(const hkVector4* triangle, ClosestPointTriangleCache& cache); // 0x01105d80
	static void HK_CALL setupPointTriangleDistanceCache(const hkVector4* triangle, PointTriangleDistanceCache& cache); // 0x01105e90
	static ClosestPointTriangleStatus HK_CALL closestPointTriangle(const hkVector4& position, const hkVector4* tri,
	                                                              const ClosestPointTriangleCache& cache,
	                                                              ClosestPointTriangleResult& result);           // 0x01106010
};

// Barycentric tolerances and the edge/vertex tables of closestPointTriangle (written at startup).
extern hkReal g_triBaryLimit0;             // 0x016e42d0
extern hkReal g_triBaryLimit1;             // 0x016e42d4
extern hkReal g_triBaryLimit2;             // 0x016e42d8
extern hkReal g_triBaryLimit3;             // 0x016e42dc
extern const signed char g_triRegionVertex[];    // 0x014a5e60 (index 0..13 -> vertex id, -1 = edge case)
extern const signed char g_triEdgeStart[];       // 0x014a5e70
extern const signed char g_triEdgeOther[];       // 0x014a5e72
extern const signed char g_triVertexEdgeStart[]; // 0x014a5e78
extern const signed char g_triVertexEdgeEnd[];   // 0x014a5e7a

// --------------------------------------------------------------------------------------- 0x01105630
// @ 0x01105630
void hkCollideTriangleUtil::calcBarycentricCoordinates(const hkVector4& A, const hkVector4& B, const hkVector4& C,
                                                       const hkVector4& P, hkReal* barycentric)
{
	const hkReal ux = B.x - C.x, uy = B.y - C.y, uz = B.z - C.z;
	const hkReal vx = P.x - C.x, vy = P.y - C.y, vz = P.z - C.z;
	const hkReal d00 = uz*uz + (ux*ux + uy*uy);
	const hkReal d11 = vz*vz + (vx*vx + vy*vy);
	const hkReal d01 = vz*uz + (vy*uy + vx*ux);
	const hkReal denom = d11*d00 - d01*d01;

	if (denom > 0.0f) {
		const hkReal inv = 1.0f / denom;
		const hkReal wx = C.x - A.x, wy = C.y - A.y, wz = C.z - A.z;
		const hkReal d20 = wz*uz + (wy*uy + wx*ux);
		const hkReal d21 = wz*vz + (wy*vy + wx*vx);
		hkReal v = d01*d21 - d11*d20;
		hkReal w = d20*d01 - d21*d00;
		barycentric[0] = v*inv;
		barycentric[1] = ((denom - v) - w)*inv;
		barycentric[2] = w*inv;
		return;
	}

	// Degenerate triangle: the point projects outside, so clamp to the closest edge or vertex.
	const hkReal abx = B.x - P.x, aby = B.y - P.y, abz = B.z - P.z;
	const hkReal sqAB = abz*abz + (aby*aby + abx*abx);
	if (d00 < d11) {
		if (d11 <= sqAB) {
			const hkReal apx = A.x - P.x, apy = A.y - P.y, apz = A.z - P.z;
			barycentric[1] = 0.0f;
			const hkReal t = (apz*abz + (apy*aby + apx*abx)) / sqAB;
			barycentric[0] = t;
			barycentric[2] = 1.0f - t;
			return;
		}
		barycentric[0] = 0.0f;
		{
			const hkReal A0 = A.x - C.x, A1 = A.y - C.y, A2 = A.z - C.z;
			const hkReal t = (A2*vz + (A1*vy + A0*vx)) / d11;
			barycentric[2] = t;
			barycentric[1] = 1.0f - t;
		}
		return;
	}
	if (sqAB < d00) {
		barycentric[2] = 0.0f;
		{
			const hkReal A0 = A.x - B.x, A1 = A.y - B.y, A2 = A.z - B.z;
			const hkReal t = (A2*uz + (A1*uy + A0*ux)) / d00;
			barycentric[0] = t;
			barycentric[1] = 1.0f - t;
		}
		return;
	}
	barycentric[1] = 0.0f;
	if (sqAB > 0.0f) {
		const hkReal t = (abz*(A.z - P.z) + (aby*(A.y - P.y) + abx*(A.x - P.x))) / sqAB;
		barycentric[0] = t;
		barycentric[2] = 1.0f - t;
		return;
	}
	barycentric[0] = 0.0f;
	barycentric[2] = 0.0f;
}

// --------------------------------------------------------------------------------------- 0x01105940
// @ 0x01105940
int hkCollideTriangleUtil::closestLineSegLineSeg(const hkVector4& p1, const hkVector4& d1, const hkVector4& p2,
                                                 const hkVector4& d2, ClosestLineSegLineSegResult& result)
{
	const hkReal d1DotD2 = d1.x*d2.x + (d1.y*d2.y + d1.z*d2.z);
	const hkReal vx = p2.x - p1.x, vy = p2.y - p1.y, vz = p2.z - p1.z;
	const hkReal vDotD1 = vx*d1.x + (vy*d1.y + vz*d1.z);
	const hkReal vDotD2 = vx*d2.x + (vy*d2.y + vz*d2.z);
	const hkReal d1Sq = d1.x*d1.x + (d1.y*d1.y + d1.z*d1.z);
	const hkReal d2Sq = d2.x*d2.x + (d2.y*d2.y + d2.z*d2.z);

	const hkReal absDet = fabsf(d2Sq*d1Sq - d1DotD2*d1DotD2);
	const hkReal num = d2Sq*vDotD1 - vDotD2*d1DotD2;

	hkReal s;
	int status;
	if (absDet*absDet == num*absDet) {
		if (num == 0.0f) {
			s = 0.0f;
			status = 2;
		}
		else if ((d1Sq + d2Sq)*1.0e-06f >= absDet) {
			s = 1.0f;
			status = 1;
		}
		else {
			s = num / absDet;
			status = 0;
		}
	}
	else {
		s = 1.0f;
		status = 1;
	}

	hkReal t = d1DotD2*s - vDotD2;
	if (t < d2Sq) {
		if (t > 0.0f) {
			t = t / d2Sq;
		}
		else {
			t = 0.0f;
			status = 8;
		}
		// t was clamped: re-solve for the closest point on the first segment.
		const hkReal u = t*d1DotD2 + vDotD1;
		if (u <= 0.0f) {
			s = 0.0f;
			status |= 2;
		}
		else if (u < d1Sq) {
			s = u / d1Sq;
		}
		else {
			s = 1.0f;
			status |= 1;
		}
	}
	else {
		t = 1.0f;
		status = 4;
	}

	result.m_closestPoint = p1;
	result.m_closestPoint.addMul4(s, d1);
	result.m_direction = p2;
	result.m_direction.addMul4(t, d2);
	result.m_direction.setSub4(result.m_closestPoint, result.m_direction);
	result.m_distanceSquared = result.m_direction.lengthSquared3();
	return status;
}

// --------------------------------------------------------------------------------------- 0x01105c30
// @ 0x01105c30
int hkCollideTriangleUtil::closestPointLineSeg(const hkVector4& point, const hkVector4& lineStart,
                                               const hkVector4& lineEnd, ClosestPointLineSegResult& result)
{
	hkVector4 diff, dir;
	diff.setSub4(point, lineStart);
	dir.setSub4(lineEnd, lineStart);
	hkReal u = dir.dot3(diff);
	hkReal v = dir.lengthSquared3();
	if (u <= 0.0f) {
		result.m_point = lineStart;
		return 8;
	}
	if (u >= v) {
		result.m_point.setAdd4(dir, lineStart);
		return 4;
	}
	u = u / v;
	result.m_point = lineStart;
	result.m_point.addMul4(u, dir);
	return 0;
}

// --------------------------------------------------------------------------------------- 0x01105d80
// @ 0x01105d80
void hkCollideTriangleUtil::setupClosestPointTriangleCache(const hkVector4* triangle, ClosestPointTriangleCache& cache)
{
	hkVector4 e, f;
	e.setSub4(triangle[0], triangle[1]);
	f.setSub4(triangle[2], triangle[1]);
	hkReal EE = e.lengthSquared3();
	hkReal FF = f.lengthSquared3();
	hkReal FE = f.dot3(e);
	hkReal inv = 1.0f / (FF*EE - FE*FE);
	cache.m_QQ = inv * EE;
	cache.m_RR = inv * FF;
	cache.m_QR = inv * FE;
	hkVector4 cross;
	cross.setCross(e, f);
	cache.m_invTriNormal = 1.0f / cross.length3();
}

// --------------------------------------------------------------------------------------- 0x01105e90
// @ 0x01105e90
void hkCollideTriangleUtil::setupPointTriangleDistanceCache(const hkVector4* triangle, PointTriangleDistanceCache& cache)
{
	hkVector4 f, g, h;
	f.setSub4(triangle[2], triangle[1]);
	g.setSub4(triangle[0], triangle[2]);
	h.setSub4(triangle[1], triangle[0]);

	hkReal ff = f.lengthSquared3();
	if (ff == 0.0f) cache.m_invLen0 = 0.0f; else cache.m_invLen0 = 1.0f / sqrtf(ff);
	hkReal gg = g.lengthSquared3();
	if (gg == 0.0f) cache.m_invLen1 = 0.0f; else cache.m_invLen1 = 1.0f / sqrtf(gg);
	hkReal hh = h.lengthSquared3();
	if (hh == 0.0f) cache.m_invLen2 = 0.0f; else cache.m_invLen2 = 1.0f / sqrtf(hh);

	hkVector4 cross;
	cross.setCross(f, g);
	hkReal len = cross.length3();
	cache.m_invTriNormal = 1.0f / len;
	cache.m_triNormalLen = len;
}

// --------------------------------------------------------------------------------------- 0x01106010
// @ 0x01106010
hkCollideTriangleUtil::ClosestPointTriangleStatus HK_CALL
hkCollideTriangleUtil::closestPointTriangle(const hkVector4& position, const hkVector4* tri,
                                            const ClosestPointTriangleCache& cache,
                                            ClosestPointTriangleResult& result)
{
	// Edge 1 (v1->v2), edge 2 (v2->v0) and the point relative to v1.
	hkVector4 toV1;
	toV1.setSub4(tri[1], position);
	hkVector4 u, v;
	u.setSub4(tri[0], tri[1]);
	v.setSub4(tri[2], tri[1]);

	const hkReal u2 = u.x*toV1.x + (u.y*toV1.y + u.z*toV1.z);
	const hkReal v2 = v.x*toV1.x + (v.y*toV1.y + v.z*toV1.z);

	hkReal b0 = v2*cache.m_QR - u2*cache.m_RR;
	hkReal b2 = u2*cache.m_QR - v2*cache.m_QQ;
	hkReal b1 = (1.001f - b0) - b2;
	b0 = b0 + 0.001f;

	unsigned int region = ((g_triBaryLimit2 < b0) << 1) |
	                      ((g_triBaryLimit1 < b1) << 2) |
	                      (((g_triBaryLimit0 < b2 + 0.001f) ? 8u : 0u) & 0xe) |
	                      (g_triBaryLimit3 < 0.001f ? 1u : 0u);
	region &= 0xe;

	if (region == 0xe) {
		// Point is closest to the face plane: return the plane normal scaled by the distance.
		const hkReal nx = v.y*u.z - v.z*u.y;
		const hkReal ny = v.z*u.x - v.x*u.z;
		const hkReal nz = v.x*u.y - v.y*u.x;
		hkVector4 n;
		n.x = nx * cache.m_invTriNormal;
		n.y = ny * cache.m_invTriNormal;
		n.z = nz * cache.m_invTriNormal;
		n.w = 0.0f;
		result.m_hitDirection = n;
		const hkReal dist = n.x*(tri[1].x - position.x) + (n.y*(tri[1].y - position.y) +
		                                                   n.z*(tri[1].z - position.z));
		result.m_distance = dist;
		if (dist > 0.0f) {
			result.m_hitDirection.x = -n.x;
			result.m_hitDirection.y = -n.y;
			result.m_hitDirection.z = -n.z;
			result.m_hitDirection.w = -n.w;
			return CLOSEST_POINT_TRIANGLE_FACE;
		}
		result.m_distance = -dist;
		return CLOSEST_POINT_TRIANGLE_FACE;
	}

	const int idx = (int)g_triRegionVertex[region];
	if (idx >= 0) {
		// The point is closest to one of the three vertices: the result is one of the two edges at it.
		ClosestPointLineSegResult r0, r1;
		const hkVector4& va = tri[idx];
		const hkVector4& vb = tri[(int)g_triEdgeOther[idx]];
		const hkVector4& vc = tri[(int)g_triEdgeStart[idx]];
		closestPointLineSeg(position, va, vb, r0);
		closestPointLineSeg(position, vc, va, r1);

		hkVector4 d0, d1;
		d0.setSub4(position, r0.m_point);
		d1.setSub4(position, r1.m_point);
		const hkReal l0 = d0.lengthSquared3();
		const hkReal l1 = d1.lengthSquared3();
		if (l0 < l1) {
			const hkReal inv = 1.0f / sqrtf(l0);
			result.m_hitDirection.x = d0.x * inv;
			result.m_hitDirection.y = d0.y * inv;
			result.m_hitDirection.z = d0.z * inv;
			result.m_hitDirection.w = (position.w - r0.m_point.w) * inv;
			result.m_distance = l0 * inv;
		}
		else {
			const hkReal inv = 1.0f / sqrtf(l1);
			result.m_hitDirection.x = d1.x * inv;
			result.m_hitDirection.y = d1.y * inv;
			result.m_hitDirection.z = d1.z * inv;
			result.m_hitDirection.w = (position.w - r1.m_point.w) * inv;
			result.m_distance = l1 * inv;
		}
		return CLOSEST_POINT_TRIANGLE_EDGE;
	}

	// Closest to one of the three edges.
	ClosestPointLineSegResult r;
	closestPointLineSeg(position, tri[(int)g_triVertexEdgeStart[idx]], tri[(int)g_triVertexEdgeEnd[idx]], r);
	result.m_hitDirection.setSub4(position, r.m_point);
	result.m_distance = result.m_hitDirection.length3();
	const hkReal inv = 1.0f / result.m_distance;
	result.m_hitDirection.x = result.m_hitDirection.x * inv;
	result.m_hitDirection.y = result.m_hitDirection.y * inv;
	result.m_hitDirection.z = result.m_hitDirection.z * inv;
	result.m_hitDirection.w = result.m_hitDirection.w * inv;
	return CLOSEST_POINT_TRIANGLE_EDGE;
}

