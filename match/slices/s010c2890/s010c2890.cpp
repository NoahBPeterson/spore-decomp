// Slice s010c2890 -- Havok collision shapes (hkCapsuleShape / hkSphereShape / hkShape).
// Built as part of the whole-program LTCG link of SporeApp.exe.
#include <math.h>
#include <string.h>

// -----------------------------------------------------------------------------------
// Havok types used by this slice (member names/offsets from the type registry).
// -----------------------------------------------------------------------------------
typedef float hkReal;

struct __declspec(align(16)) hkVector4          // 16 bytes, HK_ALIGN16
{
	hkReal m_quad[4];     // +0x00
};

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
};

struct hkCapsuleShape : public hkSphereShape
{
	hkVector4 m_vertexA;   // +0x10
	hkVector4 m_vertexB;   // +0x20

	virtual void getAabb(const hkTransform& t, hkReal tol, hkAabb& aabb) const;        // 0x010c2c10

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