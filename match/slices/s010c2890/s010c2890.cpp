// Slice s010c2890 -- Havok collision shapes (hkCapsuleShape / hkSphereShape / hkShape).
// Built as part of the whole-program LTCG link of SporeApp.exe.
#include <math.h>
#include <string.h>
#include <intrin.h>

// -----------------------------------------------------------------------------------
// Havok types used by this slice (member names/offsets from the type registry).
// -----------------------------------------------------------------------------------
typedef float hkReal;

struct __declspec(align(16)) hkVector4          // 16 bytes, HK_ALIGN16
{
	union
	{
		hkReal m_quad[4];     // +0x00
		struct { hkReal x, y, z, w; };
	};
};

class hkBool
{
public:
	hkBool() {}
	hkBool(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
	char m_bool;
};

struct hkShapeRayCastInput
{
	hkVector4 m_from;                    // +0x00
	hkVector4 m_to;                      // +0x10
	unsigned int m_filterInfo;           // +0x20
	void* m_rayShapeCollectionFilter;    // +0x24
};

struct hkShapeRayCastOutput
{
	float m_normal[4];                   // +0x00
	unsigned int m_shapeKey;             // +0x10
	float m_hitFraction;                 // +0x14
};

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorTimerEndTag[];           // 0x0149cc34
extern const char hkTtrcCapsule[];                  // 0x014a28bc ("TtrcCapsule")
struct hkMonitorCommand { const char* m_command; unsigned int m_time0; unsigned int m_pad; };
static __forceinline void hkTimerCommand(const char* name)
{
	void* end = TlsGetValue(g_hkMonitorStreamEndTls);
	if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end)
	{
		hkMonitorCommand* c = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls);
		c->m_command = name;
		volatile unsigned int t = (unsigned int)__rdtsc();
		c->m_time0 = t;
		TlsSetValue(g_hkMonitorStreamCurrentTls, c + 1);
	}
}

struct hkAabb             // two vectors
{
	hkVector4 m_min;      // +0x00
	hkVector4 m_max;      // +0x10
};

struct hkTransform
{
	hkReal    m_rotation[12];   // +0x00
	hkVector4 m_translation;    // +0x30
};

struct hkCdBody
{
	const void*  m_shape;       // +0x00
	unsigned int m_shapeKey;    // +0x04
	void*        m_motion;      // +0x08
	hkCdBody*    m_parent;      // +0x0c
};

struct hkArray
{
	void*        m_data;             // +0x00
	int          m_size;             // +0x04
	unsigned int m_capacityAndFlags; // +0x08
};

// One entry of hkAllCdBodyPairCollector's array.
struct hkCdBodyPair
{
	const hkCdBody* m_bodyA;     // +0x00
	unsigned int    m_shapeKeyA; // +0x04
	const hkCdBody* m_bodyB;     // +0x08
	unsigned int    m_shapeKeyB; // +0x0c
};

namespace hkArrayUtil
{
	void _reserveMore(hkArray* array, int elementSize);   // 0x0107f530
}

struct hkAllCdBodyPairCollector
{
	unsigned int m_pad04;    // +0x04
	hkArray      m_pairs;    // +0x08

	virtual void addCdBodyPair(const hkCdBody& bodyA, const hkCdBody& bodyB);   // 0x010c3690
};

struct hkShape
{
	unsigned short m_memSizeAndFlags;  // +0x04
	unsigned short m_referenceCount;   // +0x06
	void*          m_userData;         // +0x08
	hkReal         m_radius;           // +0x0c

	hkShape(hkReal radius) : m_referenceCount(1), m_userData(0), m_radius(radius) {}

	virtual hkReal getMaximumProjection(const hkVector4& dir) const;   // 0x010c3510

	void setTypeInfo(void* target);                                    // 0x010c3730
};

struct hkSphereShape : public hkShape
{
	hkSphereShape(hkReal radius);                                      // 0x010c3770

	virtual void getSupportingVertex(const hkVector4& dir, hkVector4& vertex) const;   // 0x010c3790
	virtual void convertVertexIdsToVertices(const unsigned short* ids, int numIds,
	                                        hkVector4* vertices) const;                // 0x010c37b0
	virtual void getFirstVertex(hkVector4& v) const;                                   // 0x010c37e0
	virtual void getAabb(const hkTransform& t, hkReal tol, hkAabb& aabb) const;        // 0x010c3800
	virtual hkBool castRay(const hkShapeRayCastInput& input,
	                       hkShapeRayCastOutput& output) const;                        // 0x010c3880
};

struct hkCapsuleShape : public hkSphereShape
{
	hkVector4 m_vertexA;   // +0x10
	hkVector4 m_vertexB;   // +0x20

	virtual void getAabb(const hkTransform& t, hkReal tol, hkAabb& aabb) const;        // 0x010c2c10
	virtual hkBool castRay(const hkShapeRayCastInput& input,
	                       hkShapeRayCastOutput& output) const;                        // 0x010c2e30

	// Static __cdecl helpers (HK_CALL): the addresses carry the identical-code-folded
	// static copies, so the emitted epilogue is a plain `ret`, not thiscall's `ret N`.
	static void closestInfLineSegInfLineSeg(const hkVector4& p0, const hkVector4& d0,
	                                        const hkVector4& p1, const hkVector4& d1,
	                                        hkReal* outDistance, hkReal* outS, hkReal* outT,
	                                        hkVector4* outP0, hkVector4* outP1);        // 0x010c2890
	static void closestPointLineSeg(const hkVector4& p, const hkVector4& a, const hkVector4& b,
	                                hkVector4& out);                                   // 0x010c2ad0
};

// Constant the two closest-point routines scale the degeneracy test by (2^-20).
static const hkReal HK_EPSILON = 9.5367431640625e-07f;


// @ 0x010c2890
// Closest points between two infinite line segments.  Every result is returned through a pointer.
void hkCapsuleShape::closestInfLineSegInfLineSeg(const hkVector4& p0, const hkVector4& d0,
                                                 const hkVector4& p1, const hkVector4& d1,
                                                 hkReal* outDistance, hkReal* outS, hkReal* outT,
                                                 hkVector4* outP0, hkVector4* outP1)
{
	hkVector4 e;
	e.m_quad[0] = p1.m_quad[0] - p0.m_quad[0];
	e.m_quad[1] = p1.m_quad[1] - p0.m_quad[1];
	e.m_quad[2] = p1.m_quad[2] - p0.m_quad[2];
	e.m_quad[3] = p1.m_quad[3] - p0.m_quad[3];

	hkReal b = d0.m_quad[2] * d1.m_quad[2] + d0.m_quad[1] * d1.m_quad[1] +
	           d0.m_quad[0] * d1.m_quad[0];
	hkReal eDotD1 = e.m_quad[0] * d1.m_quad[0] + e.m_quad[2] * d1.m_quad[2] +
	                e.m_quad[1] * d1.m_quad[1];
	hkReal c = d1.m_quad[2] * d1.m_quad[2] + (d1.m_quad[0] * d1.m_quad[0] +
	                                          d1.m_quad[1] * d1.m_quad[1]);
	hkReal a = (d0.m_quad[2] * d0.m_quad[2] + (d0.m_quad[0] * d0.m_quad[0] +
	                                           d0.m_quad[1] * d0.m_quad[1])) * c;
	hkReal denom = a - b * b;

	hkReal s;
	if (fabsf(denom) <= (fabsf(a) + b * b) * HK_EPSILON)
	{
		s = 0.0f;
	}
	else
	{
		s = ((e.m_quad[0] * d0.m_quad[0] + e.m_quad[2] * d0.m_quad[2] +
		      e.m_quad[1] * d0.m_quad[1]) * c - eDotD1 * b) / denom;
	}
	*outS = s;
	hkReal t = (b * s - eDotD1) / c;
	*outT = t;

	hkReal q0x = p0.m_quad[0] + s * d0.m_quad[0];
	hkReal q0y = p0.m_quad[1] + s * d0.m_quad[1];
	hkReal q0z = p0.m_quad[2] + s * d0.m_quad[2];
	hkReal q0w = p0.m_quad[3] + s * d0.m_quad[3];
	hkReal q1x = p1.m_quad[0] + t * d1.m_quad[0];
	hkReal q1y = p1.m_quad[1] + t * d1.m_quad[1];
	hkReal q1z = p1.m_quad[2] + t * d1.m_quad[2];
	hkReal q1w = p1.m_quad[3] + t * d1.m_quad[3];

	hkReal dx = q0x - q1x;
	hkReal dy = q0y - q1y;
	hkReal dz = q0z - q1z;

	outP0->m_quad[0] = q0x;
	outP0->m_quad[1] = q0y;
	outP0->m_quad[2] = q0z;
	outP0->m_quad[3] = q0w;
	outP1->m_quad[0] = q1x;
	outP1->m_quad[1] = q1y;
	outP1->m_quad[2] = q1z;
	outP1->m_quad[3] = q1w;
	*outDistance = dx * dx + (dy * dy + dz * dz);
}


// @ 0x010c2ad0
// Closest point on the segment a-b to the point p, clamped to the segment ends.
void hkCapsuleShape::closestPointLineSeg(const hkVector4& p, const hkVector4& a, const hkVector4& b,
                                        hkVector4& out)
{
	hkVector4 d;
	d.m_quad[0] = b.m_quad[0] - a.m_quad[0];
	d.m_quad[1] = b.m_quad[1] - a.m_quad[1];
	d.m_quad[2] = b.m_quad[2] - a.m_quad[2];
	d.m_quad[3] = b.m_quad[3] - a.m_quad[3];

	hkReal magSqr = d.m_quad[2] * d.m_quad[2] + d.m_quad[1] * d.m_quad[1] +
	                d.m_quad[0] * d.m_quad[0];
	hkReal t = -(d.m_quad[1] * (a.m_quad[1] - p.m_quad[1]) +
	             d.m_quad[2] * (a.m_quad[2] - p.m_quad[2]) +
	             d.m_quad[0] * (a.m_quad[0] - p.m_quad[0]));

	// Nested tests as in the original: only a strictly smaller t lands on the
	// segment interior; an unordered compare picks the far endpoint.
	if (t <= 0.0f)
	{
		out = a;
	}
	else
	{
		if (t < magSqr)
		{
			t = t / magSqr;
			out = a;
			out.m_quad[0] = d.m_quad[0] * t + out.m_quad[0];
			out.m_quad[1] = d.m_quad[1] * t + out.m_quad[1];
			out.m_quad[2] = d.m_quad[2] * t + out.m_quad[2];
			out.m_quad[3] = d.m_quad[3] * t + out.m_quad[3];
		}
		else
		{
			out = b;
		}
	}
}


// @ 0x010c2c10
// AABB of the capsule: the segment endpoints transformed, expanded by radius + tolerance.
void hkCapsuleShape::getAabb(const hkTransform& t, hkReal tol, hkAabb& aabb) const
{
	hkReal r = m_radius + tol;

	hkReal ax = m_vertexA.m_quad[0], ay = m_vertexA.m_quad[1], az = m_vertexA.m_quad[2];
	hkReal bx = m_vertexB.m_quad[0], by = m_vertexB.m_quad[1], bz = m_vertexB.m_quad[2];

	hkReal pax = (t.m_rotation[0] * ax + (t.m_rotation[4] * ay + t.m_rotation[8] * az)) +
	             t.m_translation.m_quad[0];
	hkReal pay = (t.m_rotation[1] * ax + (t.m_rotation[5] * ay + t.m_rotation[9] * az)) +
	             t.m_translation.m_quad[1];
	hkReal paz = (t.m_rotation[2] * ax + (t.m_rotation[6] * ay + t.m_rotation[10] * az)) +
	             t.m_translation.m_quad[2];

	hkReal pbx = (t.m_rotation[0] * bx + (t.m_rotation[4] * by + t.m_rotation[8] * bz)) +
	             t.m_translation.m_quad[0];
	hkReal pby = (t.m_rotation[1] * bx + (t.m_rotation[5] * by + t.m_rotation[9] * bz)) +
	             t.m_translation.m_quad[1];
	hkReal pbz = (t.m_rotation[2] * bx + (t.m_rotation[6] * by + t.m_rotation[10] * bz)) +
	             t.m_translation.m_quad[2];

	hkReal mnx = (pax < pbx) ? pax : pbx;
	hkReal mny = (pay < pby) ? pay : pby;
	hkReal mnz = (paz < pbz) ? paz : pbz;
	hkReal mxx = (pax < pbx) ? pbx : pax;
	hkReal mxy = (pay < pby) ? pby : pay;
	hkReal mxz = (paz < pbz) ? pbz : paz;

	aabb.m_min.m_quad[0] = mnx - r;
	aabb.m_min.m_quad[1] = mny - r;
	aabb.m_min.m_quad[2] = mnz - r;
	aabb.m_min.m_quad[3] = -r;
	aabb.m_max.m_quad[0] = mxx;
	aabb.m_max.m_quad[1] = mxy;
	aabb.m_max.m_quad[2] = mxz;
	aabb.m_max.m_quad[3] = 0.0f;
	aabb.m_max.m_quad[0] = r + aabb.m_max.m_quad[0];
	aabb.m_max.m_quad[1] = r + aabb.m_max.m_quad[1];
	aabb.m_max.m_quad[2] = r + aabb.m_max.m_quad[2];
	aabb.m_max.m_quad[3] = r + aabb.m_max.m_quad[3];
}


// Ray/capsule epsilon (FLT_EPSILON); distinct from the 2^-20 degeneracy scale above.
static const hkReal HK_RAY_EPS = 1.1920929e-07f;

// @ 0x010c2e30
// Ray against a capsule (segment A..B plus radius r), x87 build.  If the ray start is inside the capsule the
// cast fails.  Otherwise the ray is intersected with the infinite cylinder around the segment (closest
// approach of the two infinite lines gives the entry fraction); the hit is accepted when it falls between the
// two end points of the segment and in front of the best fraction so far.  A miss of the cylinder body falls
// back to a ray cast against a temporary hkSphereShape placed at the nearer end point (A when the along-axis
// position is <= 0, else B).
hkBool hkCapsuleShape::castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const
{
	hkTimerCommand(hkTtrcCapsule);

	const hkVector4& A = m_vertexA;
	const hkVector4& B = m_vertexB;
	const hkVector4& from = input.m_from;
	const hkVector4& to = input.m_to;

	{
		hkVector4 pt;
		hkCapsuleShape::closestPointLineSeg(from, A, B, pt);
		const float dx = from.x - pt.x, dy = from.y - pt.y, dz = from.z - pt.z;
		const float dist = (float)sqrt(dx * dx + dz * dz + dy * dy);
		if (dist < m_radius)
			goto fail;
	}

	{
		hkVector4 d;
		d.x = to.x - from.x; d.y = to.y - from.y; d.z = to.z - from.z; d.w = to.w - from.w;
		hkVector4 e;
		e.x = B.x - A.x; e.y = B.y - A.y; e.z = B.z - A.z; e.w = B.w - A.w;

		float distSq = 3.40282e+38f;
		float tRay, tSeg;
		hkVector4 pA, pB;
		hkCapsuleShape::closestInfLineSegInfLineSeg(from, d, A, e, &distSq, &tRay, &tSeg, &pA, &pB);

		const float r2 = m_radius * m_radius;
		if (distSq > r2)
			goto fail;

		// unit axis a and its length
		float ax, ay, az, len;
		const float len2 = e.x * e.x + e.z * e.z + e.y * e.y;
		if (len2 > HK_RAY_EPS)
		{
			len = (float)sqrt(len2);
			const float inv = 1.0f / len;
			ax = e.x * inv; ay = e.y * inv; az = e.z * inv;
		}
		else
		{
			ax = 0.0f; ay = 0.0f; az = 0.0f;
			len = 0.0f;
		}

		// component of the ray direction perpendicular to the axis
		const float s = -(d.x * ax + d.z * az + d.y * ay);
		const float px = ax * s + d.x;
		const float py = ay * s + d.y;
		const float pz = az * s + d.z;
		const float h = (float)sqrt(m_radius * m_radius - distSq);
		const float q = px * px + pz * pz + py * py;
		float invq;
		if (q == 0.0f) invq = 0.0f; else invq = 1.0f / (float)sqrt(q);
		volatile float f = tRay - invq * h;       // entry fraction on the cylinder

		volatile float along;
		if (!(f >= output.m_hitFraction))
		{
			const float ap = az * A.z + ay * A.y + ax * A.x;
			const float omf = 1.0f - f;
			volatile hkVector4 hit;
			hit.x = omf * from.x + f * to.x;
			hit.y = f * to.y + omf * from.y;
			hit.z = f * to.z + omf * from.z;
			hit.w = f * to.w + omf * from.w;
			along = (hit.x * ax + hit.z * az + hit.y * ay) - ap;

			if (f >= 0.0f && along > 0.0f && along < len)
			{
				const float u = along / len;
				const float omu = 1.0f - u;
				volatile float spx = u * B.x + omu * A.x;
				volatile float spy = omu * A.y + u * B.y;
				volatile float spz = omu * A.z + u * B.z;
				float spw = omu * A.w + u * B.w;
				volatile hkVector4 nrm;
				nrm.x = hit.x - spx;
				nrm.y = hit.y - spy;
				nrm.z = hit.z - spz;
				nrm.w = hit.w - spw;
				double nq = (double)nrm.x * nrm.x + (double)nrm.z * nrm.z + (double)nrm.y * nrm.y;
				double invn;
				if (nq == 0.0) invn = 0.0; else invn = 1.0 / sqrt(nq);
				output.m_shapeKey = 0xffffffff;
				nrm.y = nrm.y * invn; output.m_normal[1] = nrm.y;
				nrm.z = nrm.z * invn; output.m_normal[2] = nrm.z;
				output.m_hitFraction = f;
				nrm.w = nrm.w * invn; output.m_normal[3] = nrm.w;
				output.m_normal[0] = nrm.x * invn;
				hkTimerCommand(hkMonitorTimerEndTag);
				return true;
			}

			// missed the cylinder body: test the nearer end cap sphere
			const float v = ((ax * from.x + az * from.z + ay * from.y) - ap) / len;
			const float omv = 1.0f - v;
			hkVector4 cp;
			cp.x = omv * A.x + v * B.x;
			cp.y = omv * A.y + v * B.y;
			cp.z = omv * A.z + v * B.z;
			const float ex = from.x - cp.x, ey = from.y - cp.y, ez = from.z - cp.z;
			const float cd = (float)sqrt(ez * ez + ey * ey + ex * ex);
			if (cd > m_radius && f < 0.0f)
				goto fail;

			hkShapeRayCastInput sin;
			sin.m_filterInfo = 0;
			sin.m_rayShapeCollectionFilter = 0;
			const hkVector4& c = (along <= 0.0f) ? A : B;
			sin.m_from.x = from.x - c.x; sin.m_from.y = from.y - c.y; sin.m_from.z = from.z - c.z; sin.m_from.w = from.w - c.w;
			sin.m_to.x = to.x - c.x; sin.m_to.y = to.y - c.y; sin.m_to.z = to.z - c.z; sin.m_to.w = to.w - c.w;
			hkSphereShape sphere(m_radius);
			hkTimerCommand(hkMonitorTimerEndTag);
			return sphere.castRay(sin, output);
		}
	}

fail:
	hkTimerCommand(hkMonitorTimerEndTag);
	return false;
}


// Stand-in for the hkShape vtable: slot 3 (byte offset +0xc) is getAabb.
struct hkShapeVtbl
{
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void getAabb(const hkTransform& t, hkReal tol, hkAabb& aabb) const;
};


// @ 0x010c3510
// Maximum projection of the shape on dir: getAabb against the identity transform, then the
// support point of that box.
hkReal hkShape::getMaximumProjection(const hkVector4& dir) const
{
	hkTransform t;
	for (int i = 0; i < 12; ++i)
		t.m_rotation[i] = 0.0f;
	t.m_rotation[0] = 1.0f;
	t.m_rotation[5] = 1.0f;
	t.m_rotation[10] = 1.0f;
	for (int i = 0; i < 4; ++i)
		t.m_translation.m_quad[i] = 0.0f;

	hkAabb aabb;

	// hkShape's vtable slot 3 (byte +0xc) is getAabb; the VC7.1 header cannot spell
	// __thiscall in a function-pointer typedef, so dispatch through the named slot.
	(*(const hkShapeVtbl*)this).getAabb(t, 0.0f, aabb);

	hkReal ex = (aabb.m_max.m_quad[0] - aabb.m_min.m_quad[0]) * 0.5f;
	hkReal ey = (aabb.m_max.m_quad[1] - aabb.m_min.m_quad[1]) * 0.5f;
	hkReal ez = (aabb.m_max.m_quad[2] - aabb.m_min.m_quad[2]) * 0.5f;
	hkReal cx = (aabb.m_min.m_quad[0] + aabb.m_max.m_quad[0]) * 0.5f;
	hkReal cy = (aabb.m_min.m_quad[1] + aabb.m_max.m_quad[1]) * 0.5f;
	hkReal cz = (aabb.m_min.m_quad[2] + aabb.m_max.m_quad[2]) * 0.5f;
	union FloatBits { hkReal f; unsigned int u; };
	FloatBits bx, by, bz, bd;
	bx.f = ex; bd.f = dir.m_quad[0]; bx.u ^= bd.u & 0x80000000u;
	by.f = ey; bd.f = dir.m_quad[1]; by.u ^= bd.u & 0x80000000u;
	bz.f = ez; bd.f = dir.m_quad[2]; bz.u ^= bd.u & 0x80000000u;
	hkReal sx = bx.f;
	hkReal sy = by.f;
	hkReal sz = bz.f;

	return (cz + sz) * dir.m_quad[2] + ((cx + sx) * dir.m_quad[0] + (cy + sy) * dir.m_quad[1]);
}


// @ 0x010c3690
// Appends the shape keys and the root bodies of a colliding pair to the collector's array.
void hkAllCdBodyPairCollector::addCdBodyPair(const hkCdBody& bodyA, const hkCdBody& bodyB)
{
	hkArray& pairs = m_pairs;
	if (pairs.m_size == (int)(pairs.m_capacityAndFlags & 0x3fffffff))
		hkArrayUtil::_reserveMore(&pairs, 0x10);

	hkCdBodyPair* pair = (hkCdBodyPair*)pairs.m_data + pairs.m_size;
	++pairs.m_size;

	const hkCdBody* a = &bodyA;
	while (a->m_parent)
		a = a->m_parent;
	pair->m_bodyA = a;
	pair->m_shapeKeyA = bodyA.m_shapeKey;

	const hkCdBody* b = &bodyB;
	while (b->m_parent)
		b = b->m_parent;
	pair->m_bodyB = b;
	pair->m_shapeKeyB = bodyB.m_shapeKey;
}


struct hkTypeInfoRegistry
{
	virtual void slot0();
	virtual void setClass(const char* name, int numClasses, void* object);   // 1
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void finish();                                                   // 6
};

// @ 0x010c3730
// Tags `this` with the "SphereShape" class on the registry object passed in.
void hkShape::setTypeInfo(void* target)
{
	hkTypeInfoRegistry* reg = (hkTypeInfoRegistry*)target;
	reg->setClass("SphereShape", 1, this);
	reg->finish();
}


// @ 0x010c3770
// hkSphereShape constructor: one reference, no user data, the given radius.
hkSphereShape::hkSphereShape(hkReal radius) : hkShape(radius)
{
}


// @ 0x010c3790
// A sphere's support point is the origin, whatever the direction.
void hkSphereShape::getSupportingVertex(const hkVector4& dir, hkVector4& vertex) const
{
	(void)dir;
	vertex.m_quad[3] = 0;
	vertex.m_quad[2] = 0;
	vertex.m_quad[1] = 0;
	vertex.m_quad[0] = 0;
}


// @ 0x010c37b0
// A sphere has no vertices: everything collapses to the origin.
void hkSphereShape::convertVertexIdsToVertices(const unsigned short* ids, int numIds,
                                               hkVector4* vertices) const
{
	(void)ids;
	for (int i = numIds - 1; i >= 0; --i)
	{
		vertices->m_quad[3] = 0;
		vertices->m_quad[2] = 0;
		vertices->m_quad[1] = 0;
		vertices->m_quad[0] = 0;
		++vertices;
	}
}


// @ 0x010c37e0
void hkSphereShape::getFirstVertex(hkVector4& v) const
{
	v.m_quad[3] = 0;
	v.m_quad[2] = 0;
	v.m_quad[1] = 0;
	v.m_quad[0] = 0;
}


// @ 0x010c3800
// AABB of the sphere: the transformed origin expanded by radius + tolerance.
void hkSphereShape::getAabb(const hkTransform& t, hkReal tol, hkAabb& aabb) const
{
	hkVector4 tol4;
	tol4.m_quad[0] = tol4.m_quad[1] = tol4.m_quad[2] = tol4.m_quad[3] = m_radius + tol;

	aabb.m_min.m_quad[0] = t.m_translation.m_quad[0] - tol4.m_quad[0];
	aabb.m_min.m_quad[1] = t.m_translation.m_quad[1] - tol4.m_quad[1];
	aabb.m_min.m_quad[2] = t.m_translation.m_quad[2] - tol4.m_quad[2];
	aabb.m_min.m_quad[3] = t.m_translation.m_quad[3] - tol4.m_quad[3];
	aabb.m_max.m_quad[0] = t.m_translation.m_quad[0] + tol4.m_quad[0];
	aabb.m_max.m_quad[1] = t.m_translation.m_quad[1] + tol4.m_quad[1];
	aabb.m_max.m_quad[2] = t.m_translation.m_quad[2] + tol4.m_quad[2];
	aabb.m_max.m_quad[3] = t.m_translation.m_quad[3] + tol4.m_quad[3];
}