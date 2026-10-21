// gold4 slice s010d9470 -- Havok 3.1.0 box/box collision agent (hkBoxBoxAgent).
//
//  0x010d9470  hkBoxBoxAgent::processCollision
//  0x010d97a0  hkBoxBoxAgent::staticGetClosestPoints
//  0x010d9b10  hkBoxBoxAgent::staticGetPenetrations
//  0x010d9e50  hkBoxBoxAgent::registerAgent
//  0x010d9ea0  hkPredGskfAgent::createPredGskfAgent
//  0x010d9f10  hkPredGskfAgent::registerAgent
//
// Havok 3.1.0 was built with VC .NET 2003, so this slice compiles with /vc71.
#include "hk31_boxbox.h"

// ---- helpers referenced by name only -------------------------------------------------------------------------
// Two unnamed constructors used by the predictive-gskf factory (0x010d9ea0): a thiscall with three stack arguments
// and `ret 0xc`.  They are the hkPredGskfAgent (0x80-byte) and hkGskBaseAgent (0x30-byte) initialisers.
struct hkPredGskfAgentCtor {
	hkPredGskfAgentCtor() {}
	void init(const hkCdBody& a, const hkCdBody& b, hkContactMgr* mgr);          // 0x010ec660
};
struct hkGskBaseAgentCtor {
	hkGskBaseAgentCtor() {}
	void init(const hkCdBody& a, const hkCdBody& b, hkContactMgr* mgr);          // 0x010ed2a0
};
// The 3.1 AgentFuncs local is 0x18 bytes (four function pointers, the two flags and 2 bytes of padding).
struct hkAgentFuncs18 : hkAgentFuncs { uint16_t m_pad12; };

// hkMemory::s_instance allocation entry used by the agent factories.
struct hkMemoryAllocator {
	virtual void* slot0();
	virtual void* slot1();
	virtual void* slot2();
	virtual void* slot3();
	virtual void* allocate(int nbytes, int align);                              // vtable slot 4 (+0x10)
};

extern hkMemoryAllocator* hkMemory_s_instance;                                  // 0x016e4178

// @ 0x010d9ea0
hkCollisionAgent* HK_CALL hkPredGskfAgent::createPredGskfAgent(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                               const hkCollisionInput& input, hkContactMgr* mgr)
{
	if (mgr != 0)
	{
		hkPredGskfAgentCtor* agent = (hkPredGskfAgentCtor*)hkMemory_s_instance->allocate(0x80, 0x1c);
		((hkInt16*)agent)[2] = 0x80;
		agent->init(bodyA, bodyB, mgr);
		*(void**)agent = (void*)0x014a48f8;
		return (hkCollisionAgent*)agent;
	}
	hkGskBaseAgentCtor* agent = (hkGskBaseAgentCtor*)hkMemory_s_instance->allocate(0x30, 0x1c);
	((hkInt16*)agent)[2] = 0x30;
	agent->init(bodyA, bodyB, 0);
	return (hkCollisionAgent*)agent;
}

// @ 0x010d9e50
void HK_CALL hkBoxBoxAgent::registerAgent(hkCollisionDispatcher* dispatcher)
{
	hkAgentFuncs18 funcs;
	funcs.m_createFunc = (hkAgentCreateFunc)&hkBoxBoxAgent::createBoxBoxAgent;
	funcs.m_getPenetrationsFunc = (hkAgentGetPenetrationsFunc)&hkBoxBoxAgent::staticGetPenetrations;
	funcs.m_getClosestPointFunc = (hkAgentGetClosestPointsFunc)&hkBoxBoxAgent::staticGetClosestPoints;
	funcs.m_linearCastFunc = (hkAgentLinearCastFunc)&hkIterativeLinearCastAgent_staticLinearCast;
	funcs.m_isFlipped = false;
	funcs.m_isPredictive = false;
	dispatcher->registerCollisionAgent(funcs, 7, 7);
}

// @ 0x010d9f10
void HK_CALL hkPredGskfAgent::registerAgent(hkCollisionDispatcher* dispatcher)
{
	hkAgentFuncs18 funcs;
	funcs.m_createFunc = (hkAgentCreateFunc)&hkPredGskfAgent::createPredGskfAgent;
	funcs.m_getPenetrationsFunc = (hkAgentGetPenetrationsFunc)&hkGskBaseAgent_staticGetPenetrations;
	funcs.m_getClosestPointFunc = (hkAgentGetClosestPointsFunc)&hkGskBaseAgent_staticGetClosestPoints;
	funcs.m_linearCastFunc = (hkAgentLinearCastFunc)&hkIterativeLinearCastAgent_staticLinearCast;
	funcs.m_isFlipped = false;
	funcs.m_isPredictive = true;
	dispatcher->registerCollisionAgent(funcs, 1, 1);
}

// ---- box/box collision detection setup shared by the three entry points --------------------------------------

// @ 0x010d9470
void hkBoxBoxAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                     const hkProcessCollisionInput& input, hkProcessCollisionOutput& output)
{
	HK_TIMER_BEGIN("TtBoxBox");

	const hkConvexShapeView* shapeA = (const hkConvexShapeView*)bodyA.m_shape;
	const hkConvexShapeView* shapeB = (const hkConvexShapeView*)bodyB.m_shape;
	const hkTransform* wTa = (const hkTransform*)bodyA.m_motion;
	const hkTransform* wTb = (const hkTransform*)bodyB.m_motion;
	const float tolerance = input.m_tolerance;

	hkTransform aTb;
	aTb.setMulInverseMul(*wTa, *wTb);

	hkBoxBoxCollisionDetection cd;
	cd.m_pad1c = 0;
	hkRotation_set(cd.m_aRb, aTb.m_rot);
	cd.m_aTb = aTb.m_trans;
	cd.m_radiusA.x = shapeA->m_radius + shapeA->m_halfExtents.x;
	cd.m_radiusA.y = shapeA->m_radius + shapeA->m_halfExtents.y;
	cd.m_radiusA.z = shapeA->m_radius + shapeA->m_halfExtents.z;
	cd.m_radiusA.w = shapeA->m_radius + shapeA->m_halfExtents.w;
	cd.m_radiusB.x = shapeB->m_radius + shapeB->m_halfExtents.x;
	cd.m_radiusB.y = shapeB->m_radius + shapeB->m_halfExtents.y;
	cd.m_radiusB.z = shapeB->m_radius + shapeB->m_halfExtents.z;
	cd.m_radiusB.w = shapeB->m_radius + shapeB->m_halfExtents.w;
	cd.m_bodyA = &bodyA;
	cd.m_bodyB = &bodyB;
	cd.m_wTa = wTa;
	cd.m_wTb = wTb;
	cd.m_tolerance = tolerance;
	cd.m_tolerance4.x = tolerance; cd.m_tolerance4.y = tolerance;
	cd.m_tolerance4.z = tolerance; cd.m_tolerance4.w = tolerance;
	cd.m_boundaryToleranceA.x = tolerance + cd.m_radiusA.x;
	cd.m_boundaryToleranceA.y = tolerance + cd.m_radiusA.y;
	cd.m_boundaryToleranceA.z = tolerance + cd.m_radiusA.z;
	cd.m_boundaryToleranceA.w = tolerance + cd.m_radiusA.w;
	cd.m_boundaryToleranceB.x = tolerance + cd.m_radiusB.x;
	cd.m_boundaryToleranceB.y = tolerance + cd.m_radiusB.y;
	cd.m_boundaryToleranceB.z = tolerance + cd.m_radiusB.z;
	cd.m_boundaryToleranceB.w = tolerance + cd.m_radiusB.w;

	cd.calcManifold(m_manifold);

	HK_TIMER_END();
}

// @ 0x010d97a0
void HK_CALL hkBoxBoxAgent::staticGetClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                   const hkCollisionInput& input, hkCdPointCollector& collector)
{
	HK_TIMER_BEGIN("TtBoxBox");

	const hkConvexShapeView* shapeA = (const hkConvexShapeView*)bodyA.m_shape;
	const hkConvexShapeView* shapeB = (const hkConvexShapeView*)bodyB.m_shape;
	const hkTransform* wTa = (const hkTransform*)bodyA.m_motion;
	const hkTransform* wTb = (const hkTransform*)bodyB.m_motion;
	const float tolerance = input.m_tolerance;

	hkTransform aTb;
	aTb.setMulInverseMul(*wTa, *wTb);

	hkBoxBoxCollisionDetection cd;
	cd.m_pad1c = 0;
	hkRotation_set(cd.m_aRb, aTb.m_rot);
	cd.m_aTb = aTb.m_trans;
	cd.m_radiusA.x = shapeA->m_radius + shapeA->m_halfExtents.x;
	cd.m_radiusA.y = shapeA->m_radius + shapeA->m_halfExtents.y;
	cd.m_radiusA.z = shapeA->m_radius + shapeA->m_halfExtents.z;
	cd.m_radiusA.w = shapeA->m_radius + shapeA->m_halfExtents.w;
	cd.m_radiusB.x = shapeB->m_radius + shapeB->m_halfExtents.x;
	cd.m_radiusB.y = shapeB->m_radius + shapeB->m_halfExtents.y;
	cd.m_radiusB.z = shapeB->m_radius + shapeB->m_halfExtents.z;
	cd.m_radiusB.w = shapeB->m_radius + shapeB->m_halfExtents.w;
	cd.m_bodyA = &bodyA;
	cd.m_bodyB = &bodyB;
	cd.m_wTa = wTa;
	cd.m_wTb = wTb;
	cd.m_tolerance = tolerance;
	cd.m_tolerance4.x = tolerance; cd.m_tolerance4.y = tolerance;
	cd.m_tolerance4.z = tolerance; cd.m_tolerance4.w = tolerance;
	cd.m_boundaryToleranceA.x = tolerance + cd.m_radiusA.x;
	cd.m_boundaryToleranceA.y = tolerance + cd.m_radiusA.y;
	cd.m_boundaryToleranceA.z = tolerance + cd.m_radiusA.z;
	cd.m_boundaryToleranceA.w = tolerance + cd.m_radiusA.w;
	cd.m_boundaryToleranceB.x = tolerance + cd.m_radiusB.x;
	cd.m_boundaryToleranceB.y = tolerance + cd.m_radiusB.y;
	cd.m_boundaryToleranceB.z = tolerance + cd.m_radiusB.z;
	cd.m_boundaryToleranceB.w = tolerance + cd.m_radiusB.w;

	hkContactPoint point;
	if (cd.calculateClosestPoint(point))
		collector.addCdPoint(*(const hkCdPoint*)&point);

	HK_TIMER_END();
}

// @ 0x010d9b10
void HK_CALL hkBoxBoxAgent::staticGetPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                                  const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
	HK_TIMER_BEGIN("TtBoxBox");

	const hkConvexShapeView* shapeA = (const hkConvexShapeView*)bodyA.m_shape;
	const hkConvexShapeView* shapeB = (const hkConvexShapeView*)bodyB.m_shape;
	const hkTransform* wTa = (const hkTransform*)bodyA.m_motion;
	const hkTransform* wTb = (const hkTransform*)bodyB.m_motion;
	const float tolerance = input.m_tolerance;

	hkTransform aTb;
	aTb.setMulInverseMul(*wTa, *wTb);

	hkBoxBoxCollisionDetection cd;
	cd.m_pad1c = 0;
	hkRotation_set(cd.m_aRb, aTb.m_rot);
	cd.m_aTb = aTb.m_trans;
	cd.m_radiusA.x = shapeA->m_radius + shapeA->m_halfExtents.x;
	cd.m_radiusA.y = shapeA->m_radius + shapeA->m_halfExtents.y;
	cd.m_radiusA.z = shapeA->m_radius + shapeA->m_halfExtents.z;
	cd.m_radiusA.w = shapeA->m_radius + shapeA->m_halfExtents.w;
	cd.m_radiusB.x = shapeB->m_radius + shapeB->m_halfExtents.x;
	cd.m_radiusB.y = shapeB->m_radius + shapeB->m_halfExtents.y;
	cd.m_radiusB.z = shapeB->m_radius + shapeB->m_halfExtents.z;
	cd.m_radiusB.w = shapeB->m_radius + shapeB->m_halfExtents.w;
	cd.m_bodyA = &bodyA;
	cd.m_bodyB = &bodyB;
	cd.m_wTa = wTa;
	cd.m_wTb = wTb;
	cd.m_tolerance = tolerance;
	cd.m_tolerance4.x = tolerance; cd.m_tolerance4.y = tolerance;
	cd.m_tolerance4.z = tolerance; cd.m_tolerance4.w = tolerance;
	cd.m_boundaryToleranceA.x = tolerance + cd.m_radiusA.x;
	cd.m_boundaryToleranceA.y = tolerance + cd.m_radiusA.y;
	cd.m_boundaryToleranceA.z = tolerance + cd.m_radiusA.z;
	cd.m_boundaryToleranceA.w = tolerance + cd.m_radiusA.w;
	cd.m_boundaryToleranceB.x = tolerance + cd.m_radiusB.x;
	cd.m_boundaryToleranceB.y = tolerance + cd.m_radiusB.y;
	cd.m_boundaryToleranceB.z = tolerance + cd.m_radiusB.z;
	cd.m_boundaryToleranceB.w = tolerance + cd.m_radiusB.w;

	if (cd.checkIntersection(cd.m_tolerance4) == 0)
		collector.addCdBodyPair(bodyA, bodyB);

	HK_TIMER_END();
}
