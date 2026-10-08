// _hkCvxCvxDistByHeuristicSampling @ 0x01123850 (2050 bytes, __cdecl, 6 args) -- Havok 3.1 (VC .NET 2003, /vc71).
//
// Estimates the closest points of two convex shapes without a GJK pass: sample the three axis directions (and
// their negatives) of the table at 0x015B9B20, keep the direction with the largest separating distance, then
// refine it: build a perpendicular frame (t, s) around the best normal n, and test n+t, n-t, n+s, n-s (all
// renormalised, offset scaled by `scale`). Any improvement replaces the best sample (the scale stays); when none
// improves, scale is halved. `scale` starts at 1.0, is multiplied by 0.99 every iteration, and the search stops
// once scale <= 0.001. The last 0x24 bytes of the output block are the contact: normal+distance, point A,
// distance again, and 0.5.
//
// The sample evaluator (0x01123710, 307 bytes; shape A in ecx, shape B / direction on the stack, transform in
// esi, output in edi) is a static helper of the same translation unit: cl gives it that register convention.
// It is included here (it belongs to the neighbouring slice) so that this function compiles and links against
// the same body.
#include "../s010eb310/hk31_math.h"

struct __declspec(align(16)) hkSample   // 0x30 bytes: support point on A, support point on B (B space), normal + distance
{
	hkVector4 m_pointA;      // +0x00
	hkVector4 m_pointB;      // +0x10
	hkVector4 m_normal;      // +0x20 (w = separating distance along the normal)
	hkSample() {}
	hkSample& operator=(const hkSample& o)
	{
		m_pointA.x = o.m_pointA.x; m_pointA.y = o.m_pointA.y; m_pointA.z = o.m_pointA.z; m_pointA.w = o.m_pointA.w;
		m_pointB.x = o.m_pointB.x; m_pointB.y = o.m_pointB.y; m_pointB.z = o.m_pointB.z; m_pointB.w = o.m_pointB.w;
		m_normal.x = o.m_normal.x; m_normal.y = o.m_normal.y; m_normal.z = o.m_normal.z; m_normal.w = o.m_normal.w;
		return *this;
	}
};

extern const hkVector4 g_sampleDirs[3];   // 0x015B9B20: (1,0,0,0) (0,1,0,0) (0,0,1,0)

// @ 0x01123710 (not in this slice's list)
static void evaluate(const hkConvexShape* shapeA, const hkConvexShape* shapeB, const hkTransform* BtoA,
                     const hkVector4& dir, hkSample& out)
{
	out.m_normal.x = dir.x;
	out.m_normal.y = dir.y;
	out.m_normal.z = dir.z;
	out.m_normal.w = dir.w;

	__declspec(align(16)) hkVector4 negDir;
	negDir.x = -dir.x;
	negDir.y = -dir.y;
	negDir.z = -dir.z;
	negDir.w = -dir.w;
	shapeA->getSupportingVertex(negDir, *(hkCdVertex*)&out.m_pointA);

	// direction in B space = rotation^T * dir
	__declspec(align(16)) hkVector4 dirB;
	dirB.x = dir.x * BtoA->m_rot[0].x + dir.z * BtoA->m_rot[0].z + dir.y * BtoA->m_rot[0].y;
	dirB.y = dir.x * BtoA->m_rot[1].x + dir.z * BtoA->m_rot[1].z + dir.y * BtoA->m_rot[1].y;
	dirB.z = dir.x * BtoA->m_rot[2].x + dir.z * BtoA->m_rot[2].z + dir.y * BtoA->m_rot[2].y;
	dirB.w = 0.0f;
	shapeB->getSupportingVertex(dirB, *(hkCdVertex*)&out.m_pointB);

	// point B in A space
	const float bx = out.m_pointB.x, by = out.m_pointB.y, bz = out.m_pointB.z;
	const float wx = by * BtoA->m_rot[1].x + bz * BtoA->m_rot[2].x + bx * BtoA->m_rot[0].x + BtoA->m_trans.x;
	const float wy = by * BtoA->m_rot[1].y + bz * BtoA->m_rot[2].y + bx * BtoA->m_rot[0].y + BtoA->m_trans.y;
	const float wz = by * BtoA->m_rot[1].z + bz * BtoA->m_rot[2].z + bx * BtoA->m_rot[0].z + BtoA->m_trans.z;

	out.m_normal.w = (out.m_pointA.z - wz) * out.m_normal.z + (out.m_pointA.y - wy) * out.m_normal.y +
	                 (out.m_pointA.x - wx) * out.m_normal.x;
}

struct hkSamplingResult   // the block passed as the last argument
{
	hkVector4 m_normal;      // +0x00 (w = distance)
	hkVector4 m_pointA;      // +0x10
	hkReal m_distance;       // +0x20
	hkReal m_half;           // +0x24 (always 0.5)
};

static inline void mul4(hkVector4& v, hkReal f)
{
	v.x = v.x * f;
	v.y = v.y * f;
	v.z = v.z * f;
	v.w = v.w * f;
}

// @ 0x01123850
void __cdecl _hkCvxCvxDistByHeuristicSampling(const hkConvexShape* shapeA, const hkConvexShape* shapeB,
                                              const hkTransform* BtoA, hkVector4* pointA, hkVector4* pointB,
                                              hkSamplingResult* result)
{
	hkSample best;
	hkSample cur;
	best.m_normal.w = -HK_REAL_MAX;

	for (const hkVector4* d = g_sampleDirs; d < g_sampleDirs + 3; ++d)
	{
		__declspec(align(16)) hkVector4 dir = *d;
		evaluate(shapeA, shapeB, BtoA, dir, cur);
		if (cur.m_normal.w > best.m_normal.w)
			best = cur;
		dir.x = -dir.x;
		dir.y = -dir.y;
		dir.z = -dir.z;
		dir.w = -dir.w;
		evaluate(shapeA, shapeB, BtoA, dir, cur);
		if (cur.m_normal.w > best.m_normal.w)
			best = cur;
	}

	hkReal scale = 1.0f;
	do
	{
		scale = scale * 0.99f;
		__declspec(align(16)) hkVector4 n = best.m_normal;

		// tangent t = n x e_min (perpendicular to n), built from the smallest |component| of n
		const hkReal ax = fabsf(n.x);
		const hkReal ay = fabsf(n.y);
		const hkReal az = fabsf(n.z);
		int i0 = 0, i1 = 1, i2 = 2;
		hkReal m = ax;
		if (ay < ax) { i0 = 1; i1 = 0; m = ay; }
		if (az < m) { i2 = i0; i0 = 2; }
		const float* np = &n.x;
		__declspec(align(16)) hkVector4 t;
		float* tp = &t.x;
		tp[i0] = 0.0f;
		tp[3] = 0.0f;
		tp[i1] = np[i2];
		tp[i2] = -np[i1];

		hkReal len2 = t.x * t.x + t.z * t.z + t.y * t.y;
		hkReal inv;
		if (len2 == 0.0f) inv = 0.0f; else inv = 1.0f / (hkReal)sqrt((double)len2);
		mul4(t, inv);

		// s = t x n
		__declspec(align(16)) hkVector4 s;
		s.x = t.z * n.y - t.y * n.z;
		s.y = n.z * t.x - t.z * n.x;
		s.z = t.y * n.x - n.y * t.x;
		s.w = 0.0f;
		mul4(t, scale);
		mul4(s, scale);

		__declspec(align(16)) hkVector4 c1, c2, c3, c4;
		c1.x = n.x + t.x; c1.y = t.y + n.y; c1.z = t.z + n.z; c1.w = t.w + n.w;
		c2.x = n.x - t.x; c2.y = n.y - t.y; c2.z = n.z - t.z; c2.w = n.w - t.w;
		c3.x = n.x + s.x; c3.y = s.y + n.y; c3.z = s.z + n.z; c3.w = s.w + n.w;
		c4.x = n.x - s.x; c4.y = n.y - s.y; c4.z = n.z - s.z; c4.w = n.w - s.w;

		hkReal l2 = c1.x * c1.x + c1.z * c1.z + c1.y * c1.y;
		hkReal inv2;
		if (l2 == 0.0f) inv2 = 0.0f; else inv2 = 1.0f / (hkReal)sqrt((double)l2);
		mul4(c1, inv2);
		mul4(c2, inv2);
		mul4(c3, inv2);
		mul4(c4, inv2);

		evaluate(shapeA, shapeB, BtoA, c1, cur);
		if (cur.m_normal.w > best.m_normal.w)
		{
			best = cur;
		}
		else
		{
			evaluate(shapeA, shapeB, BtoA, c2, cur);
			if (cur.m_normal.w > best.m_normal.w)
			{
				best = cur;
			}
			else
			{
				evaluate(shapeA, shapeB, BtoA, c3, cur);
				if (cur.m_normal.w > best.m_normal.w)
				{
					best = cur;
				}
				else
				{
					evaluate(shapeA, shapeB, BtoA, c4, cur);
					if (cur.m_normal.w > best.m_normal.w)
						best = cur;
					else
						scale = scale * 0.5f;
				}
			}
		}
	} while (scale > 0.001f);

	*pointA = best.m_pointA;
	*pointB = best.m_pointB;
	result->m_distance = best.m_normal.w;
	result->m_normal = best.m_normal;
	result->m_pointA = best.m_pointA;
	result->m_half = 0.5f;
}
