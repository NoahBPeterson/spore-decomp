// gold4 slice s010d8520 -- Havok 3.1.0 sphere/capsule, sphere/sphere and box/box collision agents.
//
//  0x010d8520  hkSphereCapsuleAgent::staticGetPenetrations
//  0x010d8840  hkSymmetricAgent<hkSphereCapsuleAgent>::getClosestPoints
//  0x010d88c0  hkSymmetricAgent<hkSphereCapsuleAgent>::processCollision
//  0x010d89d0  hkSphereSphereAgent::cleanup
//  0x010d8a00  hkSphereSphereAgent::create
//  0x010d8a30  hkSphereSphereAgent::processCollision
//  0x010d8c80  hkSphereSphereAgent::getClosestPoints
//  0x010d8e90  hkSphereSphereAgent::staticGetClosestPoints
//  0x010d90a0  hkSphereSphereAgent::getPenetrations
//  0x010d91a0  hkSphereSphereAgent::staticGetPenetrations
//  0x010d92a0  hkSphereSphereAgent::registerAgent
//  0x010d92f0  hkBoxBoxAgent::cleanup
//  0x010d9330  hkBoxBoxAgent::createBoxBoxAgent
//  0x010d93e0  hkBoxBoxOriginCache_update (unnamed in the dev PDB)
//
// Havok 3.1.0 was built with VC .NET 2003, so this slice compiles with /vc71.
#include "hk31_sphere.h"
#include <math.h>

// ---- sphere/capsule agent ------------------------------------------------------------------------------------
// Only the two entry points of this slice are declared here; the rest of the class lives in another slice.
class hkSphereCapsuleAgent : public hkCollisionAgent
{
public:
	virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
	virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);      // 0x010d7be0
	virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);   // 0x010d7710
	virtual void cleanup();
	virtual void updateShapeCollectionFilter(const hkCdBody&, const hkCdBody&, const hkCollisionInput&);

	static void HK_CALL staticGetClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);    // 0x010d8080
	static void HK_CALL staticGetPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);   // 0x010d8520
};

// @ 0x010d8520
void hkSphereCapsuleAgent::staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                 const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
	HK_TIMER_BEGIN("TtSphereCapsule");

	const hkSphereShapeView* shapeA = (const hkSphereShapeView*)bodyA.m_shape;
	const hkCapsuleShapeView* shapeB = (const hkCapsuleShapeView*)bodyB.m_shape;
	const hkTransformCols* transA = (const hkTransformCols*)bodyA.m_motion;
	const hkTransformCols* transB = (const hkTransformCols*)bodyB.m_motion;

	// the two capsule endpoints, transformed into world space (transB's basis, used transposed: the three stored
	// vectors are the columns).
	hkVector4 p0, p1;
	p0.x = shapeB->m_vertexA.x * transB->m_col[0].x + shapeB->m_vertexA.y * transB->m_col[1].x + shapeB->m_vertexA.z * transB->m_col[2].x + transB->m_trans.x;
	p0.y = shapeB->m_vertexA.x * transB->m_col[0].y + shapeB->m_vertexA.y * transB->m_col[1].y + shapeB->m_vertexA.z * transB->m_col[2].y + transB->m_trans.y;
	p0.z = shapeB->m_vertexA.x * transB->m_col[0].z + shapeB->m_vertexA.y * transB->m_col[1].z + shapeB->m_vertexA.z * transB->m_col[2].z + transB->m_trans.z;
	p1.x = shapeB->m_vertexB.x * transB->m_col[0].x + shapeB->m_vertexB.y * transB->m_col[1].x + shapeB->m_vertexB.z * transB->m_col[2].x + transB->m_trans.x;
	p1.y = shapeB->m_vertexB.x * transB->m_col[0].y + shapeB->m_vertexB.y * transB->m_col[1].y + shapeB->m_vertexB.z * transB->m_col[2].y + transB->m_trans.y;
	p1.z = shapeB->m_vertexB.x * transB->m_col[0].z + shapeB->m_vertexB.y * transB->m_col[1].z + shapeB->m_vertexB.z * transB->m_col[2].z + transB->m_trans.z;

	ClosestPointLineSegResult closest;
	hkCollideTriangleUtil::closestPointLineSeg(transA->m_trans, p0, p1, closest);

	float dx = closest.m_point.x - transA->m_trans.x;
	float dy = closest.m_point.y - transA->m_trans.y;
	float dz = closest.m_point.z - transA->m_trans.z;

	float radius = shapeA->m_radius + shapeB->m_radius;
	if (dx * dx + dy * dy + dz * dz < radius * radius)
		collector.addCdBodyPair(bodyA, bodyB);

	HK_TIMER_END();
}

// ---- symmetric sphere/capsule agent -------------------------------------------------------------------------
// The shared hkSymmetricAgentFlipCollector's inlined constructor stores the vftable at +0 and hkRealMax() at +4 with
// no EH frame (the base carries a trivial destructor).  The binary's frame is a plain 0xc-byte aggregate, so build the
// collector as a POD local and hand its address to the (thiscall) sphere/capsule entry point.
struct hkFlipCollectorFixed                                 // vtable 0x014A43A4
{
	void* m_vftable;                     // +0
	float m_earlyOutDistance;            // +4
	hkCdPointCollector* m_original;      // +8
};

class hkSymmetricAgent_hkSphereCapsuleAgent : public hkSphereCapsuleAgent
{
public:
	virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
	virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);      // 0x010d8840
	virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);   // 0x010d88c0
};

// @ 0x010d8840
void hkSymmetricAgent_hkSphereCapsuleAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                             const hkCollisionInput& input, hkCdPointCollector& collector)
{
	hkFlipCollectorFixed flipCollector;
	flipCollector.m_original = &collector;
	flipCollector.m_earlyOutDistance = hkRealMax();
	flipCollector.m_vftable = (void*)0x014A43A4;
	hkSphereCapsuleAgent::getClosestPoints(bodyB, bodyA, input, *(hkCdPointCollector*)&flipCollector);
}

// @ 0x010d88c0
void hkSymmetricAgent_hkSphereCapsuleAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                             const hkProcessCollisionInput& input, hkProcessCollisionOutput& output)
{
	float toiTimeBefore = output.m_toiTime;
	hkProcessCdPoint* firstNewPoint = output.m_firstFreeContactPoint;
	hkSphereCapsuleAgent::processCollision(bodyB, bodyA, input, output);
	for (hkProcessCdPoint* p = firstNewPoint; p < output.m_firstFreeContactPoint; ++p)
		p->m_contact.setFlipped(p->m_contact);
	if (toiTimeBefore != output.m_toiTime)
	{
		output.m_toiContact.m_separatingNormal.x = -output.m_toiContact.m_separatingNormal.x;
		output.m_toiContact.m_separatingNormal.y = -output.m_toiContact.m_separatingNormal.y;
		output.m_toiContact.m_separatingNormal.z = -output.m_toiContact.m_separatingNormal.z;
	}
}

// ---- sphere/sphere agent ------------------------------------------------------------------------------------
// @ 0x010d89d0
void hkSphereSphereAgent::cleanup()
{
	if (m_contactPointId != 0xffff)
	{
		m_contactMgr->removePoint(m_contactPointId);
		m_contactPointId = 0xffff;
	}
	delete this;
}

// @ 0x010d8a00
hkSphereSphereAgent* HK_CALL hkSphereSphereAgent::create(hkContactMgr* mgr)
{
	return new hkSphereSphereAgent(mgr);
}

// @ 0x010d8a30
void hkSphereSphereAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                           const hkProcessCollisionInput& input, hkProcessCollisionOutput& output)
{
	HK_TIMER_BEGIN("TtSphereSphere");

	const hkSphereShapeView* shapeA = (const hkSphereShapeView*)bodyA.m_shape;
	const hkSphereShapeView* shapeB = (const hkSphereShapeView*)bodyB.m_shape;
	const hkTransformCols* transA = (const hkTransformCols*)bodyA.m_motion;
	const hkTransformCols* transB = (const hkTransformCols*)bodyB.m_motion;

	float dx = transA->m_trans.x - transB->m_trans.x;
	float dy = transA->m_trans.y - transB->m_trans.y;
	float dz = transA->m_trans.z - transB->m_trans.z;
	float dw = transA->m_trans.w - transB->m_trans.w;
	float distSq = dx * dx + dy * dy + dz * dz;
	float radius = input.m_tolerance + shapeB->m_radius + shapeA->m_radius;

	if (distSq < radius * radius)
	{
		hkProcessCdPoint* point = output.m_firstFreeContactPoint;
		float* pf = (float*)point;
		float distance;
		if (distSq <= 0.0f)
		{
			pf[4] = 1.0f; pf[5] = 0.0f; pf[6] = 0.0f; pf[7] = 0.0f;
			distance = -(shapeA->m_radius + shapeB->m_radius);
		}
		else
		{
			float invDist = 1.0f / sqrtf(distSq);
			pf[4] = dx * invDist;
			pf[5] = dy * invDist;
			pf[6] = dz * invDist;
			pf[7] = dw * invDist;
			distance = distSq * invDist - (shapeA->m_radius + shapeB->m_radius);
		}

		float rB = shapeB->m_radius;
		pf[0] = transB->m_trans.x;
		pf[1] = transB->m_trans.y;
		pf[2] = transB->m_trans.z;
		pf[3] = transB->m_trans.w;
		pf[0] = rB * pf[4] + pf[0];
		pf[1] = rB * pf[5] + pf[1];
		pf[2] = rB * pf[6] + pf[2];
		pf[3] = rB * pf[7] + pf[3];
		pf[7] = distance;

		if (m_contactPointId == 0xffff)
			m_contactPointId = m_contactMgr->addContactPoint(bodyA, bodyB, input, *point);

		if (m_contactPointId != 0xffff)
		{
			point->m_extra[0] = m_contactPointId;
			output.m_firstFreeContactPoint = point + 1;
		}
	}
	else if (m_contactPointId != 0xffff)
	{
		m_contactMgr->removePoint(m_contactPointId);
		m_contactPointId = 0xffff;
	}

	HK_TIMER_END();
}

// @ 0x010d8c80
void hkSphereSphereAgent::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                           const hkCollisionInput& input, hkCdPointCollector& collector)
{
	HK_TIMER_BEGIN("TtSphereSphere");

	const hkSphereShapeView* shapeA = (const hkSphereShapeView*)bodyA.m_shape;
	const hkSphereShapeView* shapeB = (const hkSphereShapeView*)bodyB.m_shape;
	const hkTransformCols* transA = (const hkTransformCols*)bodyA.m_motion;
	const hkTransformCols* transB = (const hkTransformCols*)bodyB.m_motion;

	float dx = transA->m_trans.x - transB->m_trans.x;
	float dy = transA->m_trans.y - transB->m_trans.y;
	float dz = transA->m_trans.z - transB->m_trans.z;
	float dw = transA->m_trans.w - transB->m_trans.w;
	float distSq = dx * dx + dy * dy + dz * dz;
	float radius = input.m_tolerance + shapeB->m_radius + shapeA->m_radius;

	if (distSq < radius * radius)
	{
		hkVector4 n;
		float distance;
		if (distSq <= 0.0f)
		{
			distance = 0.0f;
			n.x = 1.0f; n.y = 0.0f; n.z = 0.0f;
		}
		else
		{
			float invDist = 1.0f / sqrtf(distSq);
			n.x = dx * invDist;
			n.y = dy * invDist;
			n.z = dz * invDist;
			n.w = dw * invDist;
			distance = distSq * invDist;
		}

		float rB = shapeB->m_radius;
		hkCdPoint point;
		point.m_contact.m_position.x = n.x * rB + transB->m_trans.x;
		point.m_contact.m_position.y = n.y * rB + transB->m_trans.y;
		point.m_contact.m_position.z = n.z * rB + transB->m_trans.z;
		point.m_contact.m_position.w = n.w * rB + transB->m_trans.w;
		point.m_contact.m_separatingNormal.x = n.x;
		point.m_contact.m_separatingNormal.y = n.y;
		point.m_contact.m_separatingNormal.z = n.z;
		point.m_contact.m_separatingNormal.w = distance - (shapeB->m_radius + shapeA->m_radius);
		point.m_cdBodyA = &bodyA;
		point.m_cdBodyB = &bodyB;
		collector.addCdPoint(point);
	}

	HK_TIMER_END();
}

// @ 0x010d8e90
void HK_CALL hkSphereSphereAgent::staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                         const hkCollisionInput& input, hkCdPointCollector& collector)
{
	HK_TIMER_BEGIN("TtSphereSphere");

	const hkSphereShapeView* shapeA = (const hkSphereShapeView*)bodyA.m_shape;
	const hkSphereShapeView* shapeB = (const hkSphereShapeView*)bodyB.m_shape;
	const hkTransformCols* transA = (const hkTransformCols*)bodyA.m_motion;
	const hkTransformCols* transB = (const hkTransformCols*)bodyB.m_motion;

	float dx = transA->m_trans.x - transB->m_trans.x;
	float dy = transA->m_trans.y - transB->m_trans.y;
	float dz = transA->m_trans.z - transB->m_trans.z;
	float dw = transA->m_trans.w - transB->m_trans.w;
	float distSq = dx * dx + dy * dy + dz * dz;
	float radius = input.m_tolerance + shapeB->m_radius + shapeA->m_radius;

	if (distSq < radius * radius)
	{
		hkVector4 n;
		float distance;
		if (distSq <= 0.0f)
		{
			distance = 0.0f;
			n.x = 1.0f; n.y = 0.0f; n.z = 0.0f;
		}
		else
		{
			float invDist = 1.0f / sqrtf(distSq);
			n.x = dx * invDist;
			n.y = dy * invDist;
			n.z = dz * invDist;
			n.w = dw * invDist;
			distance = distSq * invDist;
		}

		float rB = shapeB->m_radius;
		hkCdPoint point;
		point.m_contact.m_position.x = n.x * rB + transB->m_trans.x;
		point.m_contact.m_position.y = n.y * rB + transB->m_trans.y;
		point.m_contact.m_position.z = n.z * rB + transB->m_trans.z;
		point.m_contact.m_position.w = n.w * rB + transB->m_trans.w;
		point.m_contact.m_separatingNormal.x = n.x;
		point.m_contact.m_separatingNormal.y = n.y;
		point.m_contact.m_separatingNormal.z = n.z;
		point.m_contact.m_separatingNormal.w = distance - (shapeB->m_radius + shapeA->m_radius);
		point.m_cdBodyA = &bodyA;
		point.m_cdBodyB = &bodyB;
		collector.addCdPoint(point);
	}

	HK_TIMER_END();
}

// @ 0x010d90a0
void hkSphereSphereAgent::getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                          const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
	HK_TIMER_BEGIN("TtSphereSphere");

	const hkSphereShapeView* shapeA = (const hkSphereShapeView*)bodyA.m_shape;
	const hkSphereShapeView* shapeB = (const hkSphereShapeView*)bodyB.m_shape;
	const hkTransformCols* transA = (const hkTransformCols*)bodyA.m_motion;
	const hkTransformCols* transB = (const hkTransformCols*)bodyB.m_motion;

	float dx = transB->m_trans.x - transA->m_trans.x;
	float dy = transB->m_trans.y - transA->m_trans.y;
	float dz = transB->m_trans.z - transA->m_trans.z;
	float radius = shapeA->m_radius + shapeB->m_radius;

	if (dx * dx + dy * dy + dz * dz < radius * radius)
		collector.addCdBodyPair(bodyA, bodyB);

	HK_TIMER_END();
}

// @ 0x010d91a0
void HK_CALL hkSphereSphereAgent::staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                        const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
	HK_TIMER_BEGIN("TtSphereSphere");

	const hkSphereShapeView* shapeA = (const hkSphereShapeView*)bodyA.m_shape;
	const hkSphereShapeView* shapeB = (const hkSphereShapeView*)bodyB.m_shape;
	const hkTransformCols* transA = (const hkTransformCols*)bodyA.m_motion;
	const hkTransformCols* transB = (const hkTransformCols*)bodyB.m_motion;

	float dx = transB->m_trans.x - transA->m_trans.x;
	float dy = transB->m_trans.y - transA->m_trans.y;
	float dz = transB->m_trans.z - transA->m_trans.z;
	float radius = shapeA->m_radius + shapeB->m_radius;

	if (dx * dx + dy * dy + dz * dz < radius * radius)
		collector.addCdBodyPair(bodyA, bodyB);

	HK_TIMER_END();
}

// @ 0x010d92a0
void HK_CALL hkSphereSphereAgent::registerAgent(hkCollisionDispatcher* dispatcher)
{
	hkAgentFuncs funcs;
	funcs.m_createFunc = (hkAgentCreateFunc)&hkSphereSphereAgent::create;
	funcs.m_getPenetrationsFunc = (hkAgentGetPenetrationsFunc)&hkSphereSphereAgent::staticGetPenetrations;
	funcs.m_getClosestPointFunc = (hkAgentGetClosestPointsFunc)&hkSphereSphereAgent::staticGetClosestPoints;
	funcs.m_linearCastFunc = (hkAgentLinearCastFunc)&hkIterativeLinearCastAgent_staticLinearCast;
	dispatcher->registerCollisionAgent(funcs, 4, 4);
}

// @ 0x010d92f0
void hkBoxBoxAgent::cleanup()
{
	for (int i = 0; i < (int)hkBoxBoxManifold_numEntries(m_manifold); ++i)
		m_contactMgr->removePoint(m_manifold.m_entries[i].m_key);
	delete this;
}

// @ 0x010d9330
hkCollisionAgent* HK_CALL hkBoxBoxAgent::createBoxBoxAgent(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                           const hkCollisionInput& input, hkContactMgr* mgr)
{
	const hkConvexShapeView* shapeA = (const hkConvexShapeView*)bodyA.m_shape;
	const hkConvexShapeView* shapeB = (const hkConvexShapeView*)bodyB.m_shape;
	float radiusA = shapeA->m_halfExtents.w * g_hkBoxBoxRadiusFactor;
	if ((radiusA > input.m_tolerance) &&
	    (shapeB->m_halfExtents.w * g_hkBoxBoxRadiusFactor > input.m_tolerance))
	{
		hkBoxBoxAgent* agent = new hkBoxBoxAgent(mgr);
		agent->m_manifold.init();
		return agent;
	}
	return hkGskfAgent_createGskfAgent(bodyA, bodyB, input, mgr);
}

// @ 0x010d93e0
void hkBoxBoxOriginCache::update()
{
	m_cachedOrigin.x = m_trans.x;
	m_cachedOrigin.y = m_trans.y;
	m_cachedOrigin.z = m_trans.z;
	m_cachedOrigin.w = m_trans.w;
	m_cachedAxis.x = m_cachedOrigin.x * m_rot[0].x + m_cachedOrigin.y * m_rot[0].y + m_cachedOrigin.z * m_rot[0].z;
	m_cachedAxis.y = m_cachedOrigin.x * m_rot[1].x + m_cachedOrigin.y * m_rot[1].y + m_cachedOrigin.z * m_rot[1].z;
	m_cachedAxis.z = m_cachedOrigin.x * m_rot[2].x + m_cachedOrigin.y * m_rot[2].y + m_cachedOrigin.z * m_rot[2].z;
	m_cachedAxis.w = 0.0f;
}
