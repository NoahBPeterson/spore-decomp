// gold4 slice s010d7570 -- Havok 3.1.0 sphere/capsule and sphere/triangle collision agents.
//
//  0x010d7570  hkSymmetricAgent<hkSphereTriangleAgent>::processCollision
//  0x010d7680  cleanup (shared by hkSphereTriangleAgent and hkSphereCapsuleAgent; one COMDAT body)
//  0x010d76b0  hkSphereCapsuleAgent::create
//  0x010d76e0  hkSymmetricAgent<hkSphereCapsuleAgent>::create
//  0x010d7710  hkSphereCapsuleAgent::processCollision
//  0x010d7be0  hkSphereCapsuleAgent::getClosestPoints
//  0x010d8080  hkSphereCapsuleAgent::staticGetClosestPoints
//
// Havok 3.1.0 was built by VC .NET 2003 (x87 floats, 16-byte aligned frames): /vc71 /O2 /MD /Gy /TP.
// Layouts/member names come from the shared Havok headers (hkVector4, hkTransform, hkContactPoint,
// hkProcessCollisionOutput ...); the geometry follows the binary exactly.
#include "../s010d8520/hk31_sphere.h"
#include <math.h>

// ---------------------------------------------------------------------------------------------------------
// hkSphereTriangleAgent: only the slots this slice references.  Its vtable (0x014a4740) is
//   dtor, calcStatistics, getPenetrations(0x10d7190), getClosestPoints(0x10d6a80), linearCast,
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
// vtable 0x014a47d8.
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

// "|v| < c" test the x87 compiler emits for ABS(x) comparisons
static __forceinline float hkAbsf(float x) { return x < 0.0f ? -x : x; }

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
// @ 0x010d7710  hkSphereCapsuleAgent::processCollision (bodyA = sphere, bodyB = capsule)
//
// Transform the capsule's two endpoints to world space, find the closest point on that segment to the
// sphere centre, and (when the distance is inside radiusSum + tolerance) emit a contact point whose
// position is the sphere centre offset to the capsule surface and whose separating normal is the
// unit direction from the segment to the sphere centre.  A previously registered contact point is
// removed when the shapes separate.
// ---------------------------------------------------------------------------------------------------------
void hkSphereCapsuleAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                            const hkProcessCollisionInput& input, hkProcessCollisionOutput& output)
{
	HK_TIMER_BEGIN("TtSphereCapsule");

	const float* sphereTrans = (const float*)bodyA.m_motion;                 // centre at +0x30
	const hkSphereShapeViewA* sphereShape = (const hkSphereShapeViewA*)bodyA.m_shape;
	const float* capsuleTrans = (const float*)bodyB.m_motion;
	const hkCapsuleShapeViewA* capsuleShape = (const hkCapsuleShapeViewA*)bodyB.m_shape;

	float* point = (float*)output.m_firstFreeContactPoint;

	// world-space capsule endpoints
	float pAx = capsuleTrans[0] * capsuleShape->m_vertexA.x + (capsuleTrans[4] * capsuleShape->m_vertexA.y + capsuleTrans[8]  * capsuleShape->m_vertexA.z) + capsuleTrans[0xc];
	float pAy = capsuleTrans[1] * capsuleShape->m_vertexA.x + (capsuleTrans[5] * capsuleShape->m_vertexA.y + capsuleTrans[9]  * capsuleShape->m_vertexA.z) + capsuleTrans[0xd];
	float pAz = capsuleTrans[2] * capsuleShape->m_vertexA.x + (capsuleTrans[6] * capsuleShape->m_vertexA.y + capsuleTrans[10] * capsuleShape->m_vertexA.z) + capsuleTrans[0xe];
	float pBx = capsuleTrans[0] * capsuleShape->m_vertexB.x + (capsuleTrans[4] * capsuleShape->m_vertexB.y + capsuleTrans[8]  * capsuleShape->m_vertexB.z) + capsuleTrans[0xc];
	float pBy = capsuleTrans[1] * capsuleShape->m_vertexB.x + (capsuleTrans[5] * capsuleShape->m_vertexB.y + capsuleTrans[9]  * capsuleShape->m_vertexB.z) + capsuleTrans[0xd];
	float pBz = capsuleTrans[2] * capsuleShape->m_vertexB.x + (capsuleTrans[6] * capsuleShape->m_vertexB.y + capsuleTrans[10] * capsuleShape->m_vertexB.z) + capsuleTrans[0xe];

	ClosestPointLineSegResult closest;
	hkCollideTriangleUtil::closestPointLineSeg(*(const hkVector4*)(sphereTrans + 0xc),
	                                           *(const hkVector4*)&pAx, *(const hkVector4*)&pBx, closest);

	float dx = (sphereTrans + 0xc)[0] - closest.m_point.x;
	float dy = (sphereTrans + 0xc)[1] - closest.m_point.y;
	float dz = (sphereTrans + 0xc)[2] - closest.m_point.z;
	float dw = (sphereTrans + 0xc)[3] - closest.m_point.w;

	const float radiusSum = sphereShape->m_radius + capsuleShape->m_radius;
	const float radius = radiusSum + input.m_tolerance;
	float distSq = dx * dx + dy * dy + dz * dz;

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
		float distance;
		if (distSq <= 0.0f)
		{
			// sphere centre coincides with the segment: build an axis-aligned direction from the
			// segment direction by zeroing its smallest component and swapping the other two.
			float segx = pBx - pAx, segy = pBy - pAy, segz = pBz - pAz;
			float ax = hkAbsf(segx), ay = hkAbsf(segy);
			bool bx = ax <= ay;
			float small = bx ? ax : ay;
			unsigned zero = bx ? 0u : 1u;
			unsigned other = 2u;
			unsigned keep = bx ? 0u : 1u;
			if (small <= hkAbsf(segz)) { other = 2u; keep = zero; zero = 2u; }
			float segFrom = bx ? segx : segy;
			float segOther = (other == 2u) ? segz : (other == 0u ? segx : segy);
			point[zero + 4] = 0.0f;
			point[7] = 0.0f;
			point[bx + 4] = segOther;
			point[other + 4] = -segFrom;
			distance = 0.0f;
		}
		else
		{
			distance = sqrtf(distSq);
			point[4] = dx; point[5] = dy; point[6] = dz; point[7] = dw;
		}

		float lenSq = point[4] * point[4] + point[5] * point[5] + point[6] * point[6];
		float invLen = (lenSq == 0.0f) ? 0.0f : 1.0f / sqrtf(lenSq);
		point[4] *= invLen; point[5] *= invLen; point[6] *= invLen; point[7] *= invLen;

		const float k = capsuleShape->m_radius - distance;
		point[0] = (sphereTrans + 0xc)[0];
		point[1] = (sphereTrans + 0xc)[1];
		point[2] = (sphereTrans + 0xc)[2];
		point[3] = (sphereTrans + 0xc)[3];
		point[0] = k * point[4] + point[0];
		point[1] = k * point[5] + point[1];
		point[2] = k * point[6] + point[2];
		point[3] = k * point[7] + point[3];
		point[7] = distance - radiusSum;

		if (m_contactPointId == 0xffff)
			m_contactPointId = m_contactMgr->addContactPoint(bodyA, bodyB, input,
			                                                 *(hkProcessCdPoint*)point);
		if (m_contactPointId != 0xffff)
		{
			*(unsigned short*)(point + 8) = m_contactPointId;
			output.m_firstFreeContactPoint = (hkProcessCdPoint*)(point + 0xc);
		}
	}

	HK_TIMER_END();
}

// ---------------------------------------------------------------------------------------------------------
// @ 0x010d7be0  hkSphereCapsuleAgent::getClosestPoints (bodyA = sphere, bodyB = capsule)
// ---------------------------------------------------------------------------------------------------------
void hkSphereCapsuleAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                            const hkCollisionInput& input, hkCdPointCollector& collector)
{
	HK_TIMER_BEGIN("TtSphereCapsule");

	const float* sphereTrans = (const float*)bodyA.m_motion;
	const hkSphereShapeViewA* sphereShape = (const hkSphereShapeViewA*)bodyA.m_shape;
	const float* capsuleTrans = (const float*)bodyB.m_motion;
	const hkCapsuleShapeViewA* capsuleShape = (const hkCapsuleShapeViewA*)bodyB.m_shape;

	float pAx = capsuleTrans[0] * capsuleShape->m_vertexA.x + (capsuleTrans[4] * capsuleShape->m_vertexA.y + capsuleTrans[8]  * capsuleShape->m_vertexA.z) + capsuleTrans[0xc];
	float pAy = capsuleTrans[1] * capsuleShape->m_vertexA.x + (capsuleTrans[5] * capsuleShape->m_vertexA.y + capsuleTrans[9]  * capsuleShape->m_vertexA.z) + capsuleTrans[0xd];
	float pAz = capsuleTrans[2] * capsuleShape->m_vertexA.x + (capsuleTrans[6] * capsuleShape->m_vertexA.y + capsuleTrans[10] * capsuleShape->m_vertexA.z) + capsuleTrans[0xe];
	float pBx = capsuleTrans[0] * capsuleShape->m_vertexB.x + (capsuleTrans[4] * capsuleShape->m_vertexB.y + capsuleTrans[8]  * capsuleShape->m_vertexB.z) + capsuleTrans[0xc];
	float pBy = capsuleTrans[1] * capsuleShape->m_vertexB.x + (capsuleTrans[5] * capsuleShape->m_vertexB.y + capsuleTrans[9]  * capsuleShape->m_vertexB.z) + capsuleTrans[0xd];
	float pBz = capsuleTrans[2] * capsuleShape->m_vertexB.x + (capsuleTrans[6] * capsuleShape->m_vertexB.y + capsuleTrans[10] * capsuleShape->m_vertexB.z) + capsuleTrans[0xe];

	ClosestPointLineSegResult closest;
	hkCollideTriangleUtil::closestPointLineSeg(*(const hkVector4*)(sphereTrans + 0xc),
	                                           *(const hkVector4*)&pAx, *(const hkVector4*)&pBx, closest);

	float dx = (sphereTrans + 0xc)[0] - closest.m_point.x;
	float dy = (sphereTrans + 0xc)[1] - closest.m_point.y;
	float dz = (sphereTrans + 0xc)[2] - closest.m_point.z;
	float dw = (sphereTrans + 0xc)[3] - closest.m_point.w;

	const float radiusSum = sphereShape->m_radius + capsuleShape->m_radius;
	const float radius = radiusSum + input.m_tolerance;
	float distSq = dx * dx + dy * dy + dz * dz;

	if (distSq < radius * radius)
	{
		float n[4];
		float distance;
		if (distSq <= 0.0f)
		{
			float segx = pBx - pAx, segy = pBy - pAy, segz = pBz - pAz;
			float ax = hkAbsf(segx), ay = hkAbsf(segy);
			bool bx = ax <= ay;
			float small = bx ? ax : ay;
			unsigned keep = 2u;
			unsigned other = bx ? 0u : 1u;
			if (hkAbsf(segz) < small) { keep = bx ? 0u : 1u; other = 2u; }
			float segFrom = bx ? segx : segy;
			float segOther = (keep == 2u) ? segz : (keep == 0u ? segx : segy);
			n[other] = 0.0f;
			n[3] = 0.0f;
			n[bx] = segOther;
			n[keep] = -segFrom;
			distance = 0.0f;
		}
		else
		{
			distance = sqrtf(distSq);
			n[0] = dx; n[1] = dy; n[2] = dz; n[3] = dw;
		}

		float lenSq = n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
		float invLen = (lenSq == 0.0f) ? 0.0f : 1.0f / sqrtf(lenSq);
		n[0] *= invLen; n[1] *= invLen; n[2] *= invLen;

		const float k = capsuleShape->m_radius - distance;
		hkCdPoint point;
		point.m_contact.m_position.x = n[0] * k + (sphereTrans + 0xc)[0];
		point.m_contact.m_position.y = n[1] * k + (sphereTrans + 0xc)[1];
		point.m_contact.m_position.z = n[2] * k + (sphereTrans + 0xc)[2];
		point.m_contact.m_position.w = (n[3] * invLen) * k + (sphereTrans + 0xc)[3];
		point.m_contact.m_separatingNormal.x = n[0];
		point.m_contact.m_separatingNormal.y = n[1];
		point.m_contact.m_separatingNormal.z = n[2];
		point.m_contact.m_separatingNormal.w = distance - radiusSum;
		point.m_cdBodyA = &bodyA;
		point.m_cdBodyB = &bodyB;
		collector.addCdPoint(point);
	}

	HK_TIMER_END();
}

// ---------------------------------------------------------------------------------------------------------
// @ 0x010d8080  hkSphereCapsuleAgent::staticGetClosestPoints (same body as getClosestPoints, no timers)
// ---------------------------------------------------------------------------------------------------------
void hkSphereCapsuleAgent::staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                  const hkCollisionInput& input, hkCdPointCollector& collector)
{
	const float* sphereTrans = (const float*)bodyA.m_motion;
	const hkSphereShapeViewA* sphereShape = (const hkSphereShapeViewA*)bodyA.m_shape;
	const float* capsuleTrans = (const float*)bodyB.m_motion;
	const hkCapsuleShapeViewA* capsuleShape = (const hkCapsuleShapeViewA*)bodyB.m_shape;

	float pAx = capsuleTrans[0] * capsuleShape->m_vertexA.x + (capsuleTrans[4] * capsuleShape->m_vertexA.y + capsuleTrans[8]  * capsuleShape->m_vertexA.z) + capsuleTrans[0xc];
	float pAy = capsuleTrans[1] * capsuleShape->m_vertexA.x + (capsuleTrans[5] * capsuleShape->m_vertexA.y + capsuleTrans[9]  * capsuleShape->m_vertexA.z) + capsuleTrans[0xd];
	float pAz = capsuleTrans[2] * capsuleShape->m_vertexA.x + (capsuleTrans[6] * capsuleShape->m_vertexA.y + capsuleTrans[10] * capsuleShape->m_vertexA.z) + capsuleTrans[0xe];
	float pBx = capsuleTrans[0] * capsuleShape->m_vertexB.x + (capsuleTrans[4] * capsuleShape->m_vertexB.y + capsuleTrans[8]  * capsuleShape->m_vertexB.z) + capsuleTrans[0xc];
	float pBy = capsuleTrans[1] * capsuleShape->m_vertexB.x + (capsuleTrans[5] * capsuleShape->m_vertexB.y + capsuleTrans[9]  * capsuleShape->m_vertexB.z) + capsuleTrans[0xd];
	float pBz = capsuleTrans[2] * capsuleShape->m_vertexB.x + (capsuleTrans[6] * capsuleShape->m_vertexB.y + capsuleTrans[10] * capsuleShape->m_vertexB.z) + capsuleTrans[0xe];

	ClosestPointLineSegResult closest;
	hkCollideTriangleUtil::closestPointLineSeg(*(const hkVector4*)(sphereTrans + 0xc),
	                                           *(const hkVector4*)&pAx, *(const hkVector4*)&pBx, closest);

	float dx = (sphereTrans + 0xc)[0] - closest.m_point.x;
	float dy = (sphereTrans + 0xc)[1] - closest.m_point.y;
	float dz = (sphereTrans + 0xc)[2] - closest.m_point.z;
	float dw = (sphereTrans + 0xc)[3] - closest.m_point.w;

	const float radiusSum = sphereShape->m_radius + capsuleShape->m_radius;
	const float radius = radiusSum + input.m_tolerance;
	float distSq = dx * dx + dy * dy + dz * dz;

	if (distSq < radius * radius)
	{
		float n[4];
		float distance;
		if (distSq <= 0.0f)
		{
			float segx = pBx - pAx, segy = pBy - pAy, segz = pBz - pAz;
			float ax = hkAbsf(segx), ay = hkAbsf(segy);
			bool bx = ax <= ay;
			float small = bx ? ax : ay;
			unsigned keep = 2u;
			unsigned other = bx ? 0u : 1u;
			if (hkAbsf(segz) < small) { keep = bx ? 0u : 1u; other = 2u; }
			float segFrom = bx ? segx : segy;
			float segOther = (keep == 2u) ? segz : (keep == 0u ? segx : segy);
			n[other] = 0.0f;
			n[3] = 0.0f;
			n[bx] = segOther;
			n[keep] = -segFrom;
			distance = 0.0f;
		}
		else
		{
			distance = sqrtf(distSq);
			n[0] = dx; n[1] = dy; n[2] = dz; n[3] = dw;
		}

		float lenSq = n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
		float invLen = (lenSq == 0.0f) ? 0.0f : 1.0f / sqrtf(lenSq);
		n[0] *= invLen; n[1] *= invLen; n[2] *= invLen;

		const float k = capsuleShape->m_radius - distance;
		hkCdPoint point;
		point.m_contact.m_position.x = n[0] * k + (sphereTrans + 0xc)[0];
		point.m_contact.m_position.y = n[1] * k + (sphereTrans + 0xc)[1];
		point.m_contact.m_position.z = n[2] * k + (sphereTrans + 0xc)[2];
		point.m_contact.m_position.w = (n[3] * invLen) * k + (sphereTrans + 0xc)[3];
		point.m_contact.m_separatingNormal.x = n[0];
		point.m_contact.m_separatingNormal.y = n[1];
		point.m_contact.m_separatingNormal.z = n[2];
		point.m_contact.m_separatingNormal.w = distance - radiusSum;
		point.m_cdBodyA = &bodyA;
		point.m_cdBodyB = &bodyB;
		collector.addCdPoint(point);
	}
}
