// gold4 slice s010d7570 -- Havok 3.1.0 sphere/capsule and sphere/triangle collision agents.
//
//  0x010d7570  hkSymmetricAgent<hkSphereTriangleAgent>::processCollision
//  0x010d7680  cleanup (shared by hkSphereTriangleAgent and hkSphereCapsuleAgent; one COMDAT body)
//  0x010d76b0  hkSphereCapsuleAgent::create
//  0x010d76e0  hkSymmetricAgent<hkSphereCapsuleAgent>::create
//  0x010d7710  hkSphereCapsuleAgent::processCollision (bodyA = sphere, bodyB = capsule)
//  0x010d7be0  hkSphereCapsuleAgent::getClosestPoints
//  0x010d8080  hkSphereCapsuleAgent::staticGetClosestPoints
//
// All three geometry entry points share the same shape: transform the capsule's two endpoints to world
// space, find the closest point on that segment to the sphere centre, and (when the distance is inside
// radiusSum + tolerance) build a contact whose position is the sphere centre offset to the capsule
// surface and whose separating normal is the unit direction from the segment to the sphere centre.
// processCollision registers/refreshes an hkContactMgr contact point; the two getClosestPoints variants
// report an hkCdPoint to the collector.
//
// Havok 3.1.0 was built by VC .NET 2003 (x87 floats, 16-byte aligned frames): /vc71 /O2 /MD /Gy /TP.
#include "../s010d8520/hk31_sphere.h"
#include <math.h>

// ---------------------------------------------------------------------------------------------------------
// hkSphereTriangleAgent: only the slots this slice references.  Its vtable (0x014a4740) is
//   dtor(0x10d93b0), calcStatistics, getPenetrations(0x10d7190), getClosestPoints(0x10d6a80), linearCast,
//   processCollision(0x10d66e0), cleanup(0x10d7680), removePoint, commitPotential, createZombie.
// ---------------------------------------------------------------------------------------------------------
class hkSphereTriangleAgent : public hkCollisionAgent
{
public:
	virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
	virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
	virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);   // 0x010d66e0
	virtual void cleanup();                                                                                                       // 0x010d7680
	virtual void updateShapeCollectionFilter(const hkCdBody&, const hkCdBody&, const hkCollisionInput&);

protected:
	unsigned short m_contactPointId;      // +0xc
};

// ---------------------------------------------------------------------------------------------------------
// hkSphereCapsuleAgent: hkCollisionAgent (0xc) + the contact-point id at +0xc (0x10-byte object).
// vtable 0x014a47d8: getPenetrations(0x10d87a0), getClosestPoints(0x10d7be0), linearCast(0x10ec0a0),
// processCollision(0x10d7710), cleanup(0x10d7680).
// ---------------------------------------------------------------------------------------------------------
class hkSphereCapsuleAgent : public hkCollisionAgent
{
public:
	virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
	virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);   // 0x010d7be0
	virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);   // 0x010d7710
	virtual void cleanup();                                                                                                       // 0x010d7680
	virtual void updateShapeCollectionFilter(const hkCdBody&, const hkCdBody&, const hkCollisionInput&);

	static hkCollisionAgent* HK_CALL create(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010d76b0
	static void HK_CALL staticGetClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);   // 0x010d8080
	static void HK_CALL staticGetPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&); // 0x010d8520

protected:
	hkSphereCapsuleAgent(hkContactMgr* mgr) : hkCollisionAgent(mgr), m_contactPointId(0xffff) {}
	unsigned short m_contactPointId;      // +0xc (0x10-byte object)
};

class hkSymmetricAgent_hkSphereCapsuleAgent : public hkSphereCapsuleAgent
{
public:
	explicit hkSymmetricAgent_hkSphereCapsuleAgent(hkContactMgr* mgr) : hkSphereCapsuleAgent(mgr) {}
	static hkCollisionAgent* HK_CALL create(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010d76e0
	virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
	virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
	virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);
};

// The symmetric wrapper of hkSphereTriangleAgent (vtable base 0x014a477c).
class hkSymmetricAgent_hkSphereTriangleAgent : public hkSphereTriangleAgent
{
public:
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);   // 0x010d7570
};

// ---------------------------------------------------------------------------------------------------------
// capsule/sphere shape views.  The capsule carries the two segment endpoints at +0x10 and +0x20; the
// shared motion is a column-major hkTransform (basis columns at +0/+0x10/+0x20, translation at +0x30).
// ---------------------------------------------------------------------------------------------------------
struct hkCapsuleShapeViewA
{
	uint32_t m_header[3];    // +0
	float m_radius;          // +0xc
	hkVector4 m_vertexA;     // +0x10
	hkVector4 m_vertexB;     // +0x20
};
struct hkSphereShapeViewA
{
	uint32_t m_header[3];    // +0
	float m_radius;          // +0xc
};

static __forceinline float hkAbsf(float x) { return x < 0.0f ? -x : x; }

// out = R * in + t (column-major transform: basis columns at +0x10*c, translation at +0x30).
#define HK_XFORM_COL(O, I, T) { \
	const float inx = (I).x, iny = (I).y, inz = (I).z; \
	(O).x = (T)[0] * inx + ((T)[4] * iny + (T)[8]  * inz) + (T)[0xc]; \
	(O).y = (T)[1] * inx + ((T)[5] * iny + (T)[9]  * inz) + (T)[0xd]; \
	(O).z = (T)[2] * inx + ((T)[6] * iny + (T)[10] * inz) + (T)[0xe]; \
	(O).w = 0.0f; }

// ---------------------------------------------------------------------------------------------------------
// @ 0x010d7570
// hkSymmetricAgent<hkSphereTriangleAgent>::processCollision: snapshot the TOI time and the next free
// contact point, run the triangle agent with the bodies swapped, flip every newly added contact point,
// and negate the TOI separating normal when the TOI time changed.
// ---------------------------------------------------------------------------------------------------------
void hkSymmetricAgent_hkSphereTriangleAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                              const hkProcessCollisionInput& input,
                                                              hkProcessCollisionOutput& output)
{
	const float toiTimeBefore = output.m_toiTime;
	hkProcessCdPoint* p = output.m_firstFreeContactPoint;
	hkSphereTriangleAgent::processCollision(bodyB, bodyA, input, output);
	while (p < output.m_firstFreeContactPoint)
	{
		p->m_contact.setFlipped(p->m_contact);
		++p;
	}
	if (toiTimeBefore != output.m_toiTime)      // fucompp: unordered counts as different
	{
		output.m_toiContact.m_separatingNormal.x = -output.m_toiContact.m_separatingNormal.x;
		output.m_toiContact.m_separatingNormal.y = -output.m_toiContact.m_separatingNormal.y;
		output.m_toiContact.m_separatingNormal.z = -output.m_toiContact.m_separatingNormal.z;
	}
}

// ---------------------------------------------------------------------------------------------------------
// @ 0x010d7680  cleanup (identical body emitted for hkSphereTriangleAgent and hkSphereCapsuleAgent)
// ---------------------------------------------------------------------------------------------------------
void hkSphereTriangleAgent::cleanup()
{
	if (m_contactPointId != 0xffff)
		m_contactMgr->removePoint(m_contactPointId);
	delete this;
}

// ---------------------------------------------------------------------------------------------------------
// @ 0x010d76b0  hkSphereCapsuleAgent::create
// ---------------------------------------------------------------------------------------------------------
hkCollisionAgent* HK_CALL hkSphereCapsuleAgent::create(const hkCdBody& a, const hkCdBody& b,
                                                      const hkCollisionInput& input, hkContactMgr* mgr)
{
	return new hkSphereCapsuleAgent(mgr);
}

// ---------------------------------------------------------------------------------------------------------
// @ 0x010d76e0  hkSymmetricAgent<hkSphereCapsuleAgent>::create
// ---------------------------------------------------------------------------------------------------------
hkCollisionAgent* HK_CALL hkSymmetricAgent_hkSphereCapsuleAgent::create(const hkCdBody& a, const hkCdBody& b,
                                                                       const hkCollisionInput& input, hkContactMgr* mgr)
{
	return new hkSymmetricAgent_hkSphereCapsuleAgent(mgr);
}

// ---------------------------------------------------------------------------------------------------------
// @ 0x010d7710  hkSphereCapsuleAgent::processCollision
// ---------------------------------------------------------------------------------------------------------
void hkSphereCapsuleAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                            const hkProcessCollisionInput& input, hkProcessCollisionOutput& output)
{
	HK_TIMER_BEGIN("TtSphereCapsule");

	const float* sphereTrans = (const float*)bodyA.m_motion;                 // centre at +0x30
	const hkSphereShapeViewA* sphereShape = (const hkSphereShapeViewA*)bodyA.m_shape;
	const float* capsuleTrans = (const float*)bodyB.m_motion;
	const hkCapsuleShapeViewA* capsuleShape = (const hkCapsuleShapeViewA*)bodyB.m_shape;

	hkProcessCdPoint* contact = output.m_firstFreeContactPoint;

	hkVector4 pA, pB;
	HK_XFORM_COL(pA, capsuleShape->m_vertexA, capsuleTrans)
	HK_XFORM_COL(pB, capsuleShape->m_vertexB, capsuleTrans)

	ClosestPointLineSegResult closest;
	hkCollideTriangleUtil::closestPointLineSeg(*(const hkVector4*)(sphereTrans + 0xc), pA, pB, closest);

	const float dx = (sphereTrans + 0xc)[0] - closest.m_point.x;
	const float dy = (sphereTrans + 0xc)[1] - closest.m_point.y;
	const float dz = (sphereTrans + 0xc)[2] - closest.m_point.z;
	const float dw = (sphereTrans + 0xc)[3] - closest.m_point.w;

	const float radiusSum = sphereShape->m_radius + capsuleShape->m_radius;
	const float radius = radiusSum + input.m_tolerance;
	const float distSq = dx * dx + dy * dy + dz * dz;

	if (radius * radius <= distSq)
	{
		if (m_contactPointId != 0xffff)
		{
			m_contactMgr->removePoint(m_contactPointId);
			m_contactPointId = 0xffff;
		}
	}
	else
	{
		float n[4];
		float distance;
		if (!(distSq > 0.0f))
		{
			// sphere centre coincides with the segment: build an axis-aligned direction from the
			// segment direction by zeroing its smallest component and swapping the other two.
			n[0] = pB.x - pA.x;
			n[1] = pB.y - pA.y;
			n[2] = pB.z - pA.z;
			n[3] = pB.w - pA.w;
			const float ax = hkAbsf(n[0]);
			const float ay = hkAbsf(n[1]);
			const bool bx = ax <= ay;                          // "smallest of x/y"
			const float small = bx ? ax : ay;
			unsigned zero = bx ? 0u : 1u;
			unsigned other = 2u;
			if (small <= hkAbsf(n[2])) { other = bx ? 0u : 1u; zero = 2u; }
			const float from = bx ? (pB.x - pA.x) : (pB.y - pA.y);
			const float oth  = (other == 2u) ? (pB.z - pA.z) : (other == 0u ? (pB.x - pA.x) : (pB.y - pA.y));
			((float*)&n)[zero] = 0.0f;
			n[3] = 0.0f;
			((float*)&n)[bx] = oth;
			((float*)&n)[other] = -from;
			distance = 0.0f;
		}
		else
		{
			distance = sqrtf(distSq);
			n[0] = dx; n[1] = dy; n[2] = dz; n[3] = dw;
		}

		const float lenSq = n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
		const float invLen = (lenSq == 0.0f) ? 0.0f : 1.0f / sqrtf(lenSq);
		n[0] *= invLen; n[1] *= invLen; n[2] *= invLen; n[3] *= invLen;

		const float k = capsuleShape->m_radius - distance;
		contact->m_contact.m_position.x = n[0] * k + (sphereTrans + 0xc)[0];
		contact->m_contact.m_position.y = n[1] * k + (sphereTrans + 0xc)[1];
		contact->m_contact.m_position.z = n[2] * k + (sphereTrans + 0xc)[2];
		contact->m_contact.m_position.w = n[3] * k + (sphereTrans + 0xc)[3];
		contact->m_contact.m_separatingNormal.x = n[0];
		contact->m_contact.m_separatingNormal.y = n[1];
		contact->m_contact.m_separatingNormal.z = n[2];
		contact->m_contact.m_separatingNormal.w = distance - radiusSum;

		if (m_contactPointId == 0xffff)
			m_contactPointId = m_contactMgr->addContactPoint(bodyA, bodyB, input, *contact);
		if (m_contactPointId != 0xffff)
		{
			contact->m_extra[0] = m_contactPointId;
			output.m_firstFreeContactPoint = contact + 1;
		}
	}

	HK_TIMER_END();
}

// ---------------------------------------------------------------------------------------------------------
// @ 0x010d7be0  hkSphereCapsuleAgent::getClosestPoints
// ---------------------------------------------------------------------------------------------------------
void hkSphereCapsuleAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                            const hkCollisionInput& input, hkCdPointCollector& collector)
{
	HK_TIMER_BEGIN("TtSphereCapsule");

	const float* sphereTrans = (const float*)bodyA.m_motion;
	const hkSphereShapeViewA* sphereShape = (const hkSphereShapeViewA*)bodyA.m_shape;
	const float* capsuleTrans = (const float*)bodyB.m_motion;
	const hkCapsuleShapeViewA* capsuleShape = (const hkCapsuleShapeViewA*)bodyB.m_shape;

	hkVector4 pA, pB;
	HK_XFORM_COL(pA, capsuleShape->m_vertexA, capsuleTrans)
	HK_XFORM_COL(pB, capsuleShape->m_vertexB, capsuleTrans)

	ClosestPointLineSegResult closest;
	hkCollideTriangleUtil::closestPointLineSeg(*(const hkVector4*)(sphereTrans + 0xc), pA, pB, closest);

	const float dx = (sphereTrans + 0xc)[0] - closest.m_point.x;
	const float dy = (sphereTrans + 0xc)[1] - closest.m_point.y;
	const float dz = (sphereTrans + 0xc)[2] - closest.m_point.z;
	const float dw = (sphereTrans + 0xc)[3] - closest.m_point.w;

	const float radiusSum = sphereShape->m_radius + capsuleShape->m_radius;
	const float radius = radiusSum + input.m_tolerance;
	const float distSq = dx * dx + dy * dy + dz * dz;

	if (distSq < radius * radius)
	{
		hkVector4 n;
		float distance;
		if (distSq <= 0.0f)
		{
			n.x = pB.x - pA.x;
			n.y = pB.y - pA.y;
			n.z = pB.z - pA.z;
			n.w = pB.w - pA.w;
			const float ax = hkAbsf(n.x);
			const float ay = hkAbsf(n.y);
			const bool bx = ax <= ay;
			const float small = bx ? ax : ay;
			unsigned keep = 2u;
			unsigned other = bx ? 0u : 1u;
			if (hkAbsf(n.z) < small) { keep = bx ? 0u : 1u; other = 2u; }
			const float from = bx ? (pB.x - pA.x) : (pB.y - pA.y);
			const float oth  = (keep == 2u) ? (pB.z - pA.z) : (keep == 0u ? (pB.x - pA.x) : (pB.y - pA.y));
			((float*)&n)[other] = 0.0f;
			n.w = 0.0f;
			((float*)&n)[bx] = oth;
			((float*)&n)[keep] = -from;
			distance = 0.0f;
		}
		else
		{
			distance = sqrtf(distSq);
			n.x = dx; n.y = dy; n.z = dz; n.w = dw;
		}

		const float lenSq = n.x * n.x + n.y * n.y + n.z * n.z;
		const float invLen = (lenSq == 0.0f) ? 0.0f : 1.0f / sqrtf(lenSq);
		n.x *= invLen; n.y *= invLen; n.z *= invLen;

		const float k = capsuleShape->m_radius - distance;
		hkCdPoint point;
		point.m_contact.m_position.x = n.x * k + (sphereTrans + 0xc)[0];
		point.m_contact.m_position.y = n.y * k + (sphereTrans + 0xc)[1];
		point.m_contact.m_position.z = n.z * k + (sphereTrans + 0xc)[2];
		point.m_contact.m_position.w = (n.w * invLen) * k + (sphereTrans + 0xc)[3];
		point.m_contact.m_separatingNormal.x = n.x;
		point.m_contact.m_separatingNormal.y = n.y;
		point.m_contact.m_separatingNormal.z = n.z;
		point.m_contact.m_separatingNormal.w = distance - radiusSum;
		point.m_cdBodyA = &bodyA;
		point.m_cdBodyB = &bodyB;
		collector.addCdPoint(point);
	}

	HK_TIMER_END();
}

// ---------------------------------------------------------------------------------------------------------
// @ 0x010d8080  hkSphereCapsuleAgent::staticGetClosestPoints (same body as getClosestPoints)
// ---------------------------------------------------------------------------------------------------------
void hkSphereCapsuleAgent::staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                  const hkCollisionInput& input, hkCdPointCollector& collector)
{
	HK_TIMER_BEGIN("TtSphereCapsule");

	const float* sphereTrans = (const float*)bodyA.m_motion;
	const hkSphereShapeViewA* sphereShape = (const hkSphereShapeViewA*)bodyA.m_shape;
	const float* capsuleTrans = (const float*)bodyB.m_motion;
	const hkCapsuleShapeViewA* capsuleShape = (const hkCapsuleShapeViewA*)bodyB.m_shape;

	hkVector4 pA, pB;
	HK_XFORM_COL(pA, capsuleShape->m_vertexA, capsuleTrans)
	HK_XFORM_COL(pB, capsuleShape->m_vertexB, capsuleTrans)

	ClosestPointLineSegResult closest;
	hkCollideTriangleUtil::closestPointLineSeg(*(const hkVector4*)(sphereTrans + 0xc), pA, pB, closest);

	const float dx = (sphereTrans + 0xc)[0] - closest.m_point.x;
	const float dy = (sphereTrans + 0xc)[1] - closest.m_point.y;
	const float dz = (sphereTrans + 0xc)[2] - closest.m_point.z;
	const float dw = (sphereTrans + 0xc)[3] - closest.m_point.w;

	const float radiusSum = sphereShape->m_radius + capsuleShape->m_radius;
	const float radius = radiusSum + input.m_tolerance;
	const float distSq = dx * dx + dy * dy + dz * dz;

	if (distSq < radius * radius)
	{
		hkVector4 n;
		float distance;
		if (distSq <= 0.0f)
		{
			n.x = pB.x - pA.x;
			n.y = pB.y - pA.y;
			n.z = pB.z - pA.z;
			n.w = pB.w - pA.w;
			const float ax = hkAbsf(n.x);
			const float ay = hkAbsf(n.y);
			const bool bx = ax <= ay;
			const float small = bx ? ax : ay;
			unsigned keep = 2u;
			unsigned other = bx ? 0u : 1u;
			if (hkAbsf(n.z) < small) { keep = bx ? 0u : 1u; other = 2u; }
			const float from = bx ? (pB.x - pA.x) : (pB.y - pA.y);
			const float oth  = (keep == 2u) ? (pB.z - pA.z) : (keep == 0u ? (pB.x - pA.x) : (pB.y - pA.y));
			((float*)&n)[other] = 0.0f;
			n.w = 0.0f;
			((float*)&n)[bx] = oth;
			((float*)&n)[keep] = -from;
			distance = 0.0f;
		}
		else
		{
			distance = sqrtf(distSq);
			n.x = dx; n.y = dy; n.z = dz; n.w = dw;
		}

		const float lenSq = n.x * n.x + n.y * n.y + n.z * n.z;
		const float invLen = (lenSq == 0.0f) ? 0.0f : 1.0f / sqrtf(lenSq);
		n.x *= invLen; n.y *= invLen; n.z *= invLen;

		const float k = capsuleShape->m_radius - distance;
		hkCdPoint point;
		point.m_contact.m_position.x = n.x * k + (sphereTrans + 0xc)[0];
		point.m_contact.m_position.y = n.y * k + (sphereTrans + 0xc)[1];
		point.m_contact.m_position.z = n.z * k + (sphereTrans + 0xc)[2];
		point.m_contact.m_position.w = (n.w * invLen) * k + (sphereTrans + 0xc)[3];
		point.m_contact.m_separatingNormal.x = n.x;
		point.m_contact.m_separatingNormal.y = n.y;
		point.m_contact.m_separatingNormal.z = n.z;
		point.m_contact.m_separatingNormal.w = distance - radiusSum;
		point.m_cdBodyA = &bodyA;
		point.m_cdBodyB = &bodyB;
		collector.addCdPoint(point);
	}

	HK_TIMER_END();
}
