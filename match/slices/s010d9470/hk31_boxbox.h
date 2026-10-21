#pragma once
// Havok 3.1.0 box/box collision agents (gold4 slice s010d9470), sharing the sphere/capsule layouts of slice
// s010d8520.  Member names follow the Havok 6.x headers; layouts come from the retail binary.
#include "../s010d8520/hk31_sphere.h"

// hkBoxBoxCollisionDetection: the box/box manifold builder.  The agents fill m_bodyA/m_bodyB/m_env/m_wTa/m_wTb, the
// two box radii (already offset by m_motion->m_translation) at +0x60/+0x70, the tolerance at +0xb0 and the aTb
// transform at +0x50, then call calcManifold / calculateClosestPoint / checkIntersection.
class hkBoxBoxCollisionDetection
{
public:
	const hkCdBody*           m_bodyA;                  // +0x00
	const hkCdBody*           m_bodyB;                  // +0x04
	const hkCollisionInput*   m_env;                    // +0x08
	hkContactMgr*             m_contactMgr;             // +0x0c
	hkProcessCollisionOutput* m_result;                 // +0x10
	const hkTransform*        m_wTa;                    // +0x14
	const hkTransform*        m_wTb;                    // +0x18
	uint32_t                  m_pad1c;                  // +0x1c
	hkRotation                m_aRb;                    // +0x20
	hkVector4                 m_aTb;                    // +0x50
	hkVector4                 m_radiusA;                // +0x60
	hkVector4                 m_radiusB;                // +0x70
	hkVector4                 m_tolerance4;             // +0x80
	hkVector4                 m_boundaryToleranceA;     // +0x90
	hkVector4                 m_boundaryToleranceB;     // +0xa0
	float                     m_tolerance;              // +0xb0
	uint32_t                  m_padb4[3];
	hkVector4                 m_dinA;                   // +0xc0
	hkVector4                 m_dinB;                   // +0xd0

	void calcManifold(hkBoxBoxManifold& manifold) const;                    // 0x0110b3a0
	hkBool calculateClosestPoint(hkContactPoint& point) const;              // 0x0110b260
	int checkIntersection(const hkVector4& tolerance4);                     // 0x01109460
};

// The rotation member needs a field copy (arrays are not assignable).
inline void hkRotation_set(hkRotation& r, const hkVector4* cols)
{
	r.m_col[0] = cols[0]; r.m_col[1] = cols[1]; r.m_col[2] = cols[2];
}

// hkBoxBoxAgent (the familiar agent) plus its manifold helper, reused from slice s010d8520.
inline void hkBoxBoxAgent_run(hkBoxBoxCollisionDetection& cd, hkBoxBoxManifold& manifold,
                              const hkCdBody& bodyA, const hkCdBody& bodyB, const hkTransform* wTa,
                              const hkTransform* wTb, float tolerance)
{
	cd.m_bodyA = &bodyA;
	cd.m_bodyB = &bodyB;
	cd.m_wTa = wTa;
	cd.m_wTb = wTb;
	cd.m_tolerance = tolerance;
	cd.m_tolerance4.x = tolerance; cd.m_tolerance4.y = tolerance;
	cd.m_tolerance4.z = tolerance; cd.m_tolerance4.w = tolerance;
	(void)manifold;
}

// hkPredGskfAgent factory and the gsk base-agent entries (declared for the registerAgent tables).
class hkPredGskfAgent : public hkCollisionAgent      // vtable 0x014a48f8
{
public:
	static hkCollisionAgent* HK_CALL createPredGskfAgent(const hkCdBody&, const hkCdBody&, const hkCollisionInput&,
	                                                     hkContactMgr* mgr);                                  // 0x010d9ea0
	static void HK_CALL registerAgent(hkCollisionDispatcher* dispatcher);                                     // 0x010d9f10
};
void HK_CALL hkGskBaseAgent_staticGetPenetrations(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input,
                                                  hkCdBodyPairCollector& collector);                              // 0x010edaa0
void HK_CALL hkGskBaseAgent_staticGetClosestPoints(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input,
                                                   hkCdPointCollector& collector);                                // 0x010ed430


