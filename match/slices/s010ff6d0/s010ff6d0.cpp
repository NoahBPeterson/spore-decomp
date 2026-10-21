// gold4 slice s010ff6d0 -- Havok 3.1.0 predictive-GSK (predGsk) agent3: the dispatcher registration for the
// cylinder/box predictive agent, the four gsk manifold entry points, the cache initialiser and sepNormal.
//
//  0x010ff6d0  hkPredGskCylinderAgent3 registration (unnamed in the dev PDB)
//  0x010ff760  hkPredGskAgent3::removePoint
//  0x010ff7a0  hkPredGskAgent3::commitPotential
//  0x010ff7d0  hkPredGskAgent3::updatePoint (unnamed in the dev PDB)
//  0x010ff820  hkGsk_cacheInit (unnamed in the dev PDB)
//  0x010ff8c0  hkPredGskAgent3::sepNormal
//
// Havok 3.1.0 was built with VC .NET 2003, so this slice compiles with /vc71.
#include "hk31_predgsk.h"

// ---------------------------------------------------------------------------------------------------------
// dispatcher registration table.  The 3.1 predictive-agent table drops the createZombie entry, so the slot
// order is create, destroy, cleanup, removePoint, commitPotential, updatePoint, updateFilter, invalidateTim,
// warpTime, sepNormal, process (0x2c bytes).
// ---------------------------------------------------------------------------------------------------------
class hkCollisionDispatcher
{
public:
	struct Agent3Funcs
	{
		void* (*m_createFunc)();               // +0x00
		void  (*m_destroyFunc)();              // +0x04
		void  (*m_cleanupFunc)();              // +0x08
		void  (*m_removePointFunc)();          // +0x0c
		void  (*m_commitPotentialFunc)();      // +0x10
		void  (*m_updatePointFunc)();          // +0x14
		void  (*m_updateFilterFunc)();         // +0x18
		void  (*m_invalidateTimFunc)();        // +0x1c
		void  (*m_warpTimeFunc)();             // +0x20
		void  (*m_sepNormalFunc)();            // +0x24
		void* (*m_processFunc)();              // +0x28
		hkBool m_isPredictive;                 // +0x2c
		hkBool m_ignoreSymmetricVersion;       // +0x2d
		unsigned char m_pad2e[6];              // +0x2e
		Agent3Funcs() : m_createFunc(0), m_destroyFunc(0), m_cleanupFunc(0), m_removePointFunc(0),
		                m_commitPotentialFunc(0), m_updatePointFunc(0), m_updateFilterFunc(0),
		                m_invalidateTimFunc(0), m_warpTimeFunc(0), m_sepNormalFunc(0),
		                m_processFunc(0), m_isPredictive(hkBool(false)),
		                m_ignoreSymmetricVersion(hkBool(false)) {}
	};
	int registerAgent3(Agent3Funcs& funcs, int typeA, int typeB);   // 0x010cd4c0
};

// ---------------------------------------------------------------------------------------------------------
// entry points referenced by the registration table (defined in other slices / by this one)
// ---------------------------------------------------------------------------------------------------------
extern "C" void* HK_CALL hkPredGskCylinderAgent3_create();          // 0x010fdf30
extern "C" void  HK_CALL hkPredGskAgent3_process();                 // 0x010fdf80
extern "C" void  HK_CALL hkGskManifold_cleanupEntry();              // 0x010ff800
extern "C" void  HK_CALL hkGskManifold_cleanupPair();               // 0x010ff880

// =========================================================================================================
// @ 0x010ff6d0
void HK_CALL hkPredGskCylinderAgent3_register(hkCollisionDispatcher* dispatcher)
{
	hkCollisionDispatcher::Agent3Funcs funcs;
	funcs.m_createFunc          = &hkPredGskCylinderAgent3_create;
	funcs.m_processFunc         = (void* (*)())&hkPredGskAgent3_process;
	funcs.m_sepNormalFunc       = (void (*)())&hkPredGskAgent3_sepNormal;
	funcs.m_cleanupFunc         = (void (*)())&hkGskManifold_cleanupPair;
	funcs.m_removePointFunc     = (void (*)())&hkPredGskAgent3_removePoint;
	funcs.m_commitPotentialFunc = (void (*)())&hkPredGskAgent3_commitPotential;
	funcs.m_updatePointFunc     = (void (*)())&hkPredGskAgent3_updatePoint;
	funcs.m_updateFilterFunc    = 0;
	funcs.m_invalidateTimFunc   = 0;
	funcs.m_warpTimeFunc        = 0;
	funcs.m_destroyFunc         = (void (*)())&hkGskManifold_cleanupEntry;
	funcs.m_isPredictive            = hkBool(true);
	funcs.m_ignoreSymmetricVersion  = hkBool(true);
	dispatcher->registerAgent3(funcs, 5, 1);
	dispatcher->registerAgent3(funcs, 1, 5);
}

// =========================================================================================================
// @ 0x010ff760
void HK_CALL hkPredGskAgent3_removePoint(hkAgentEntry* entry, void* agentData, hkContactPointId id)
{
	(void)entry;
	hkGskManifold* manifold = (hkGskManifold*)agentData;
	unsigned short* pointId = (unsigned short*)((char*)manifold + 0x12);
	const int n = manifold->m_numManifoldPoints;
	int i = 0;
	if (n <= 0)
		return;
	for (;;)
	{
		if (*pointId == id)
			break;
		++i;
		pointId += 4;
		if (i >= n)
			return;
	}
	hkGskManifold::removePoint(manifold, i);
}

// =========================================================================================================
// @ 0x010ff7a0
void HK_CALL hkPredGskAgent3_commitPotential(hkAgentEntry* entry, void* agentData, hkContactPointId id)
{
	(void)entry;
	hkGskManifold* manifold = (hkGskManifold*)agentData;
	const int n = manifold->m_numManifoldPoints;
	for (int i = 0; i < n; ++i)
	{
		if (*(unsigned short*)(hkGskManifold_points(manifold) + i * 8) == 0xffff)
		{
			*(unsigned short*)(hkGskManifold_points(manifold) + i * 8) = id;
			break;
		}
	}
}

// =========================================================================================================
// @ 0x010ff7d0
void HK_CALL hkPredGskAgent3_updatePoint(hkAgentEntry* entry, void* agentData, hkContactPointId id)
{
	(void)entry;
	hkGskManifold* manifold = (hkGskManifold*)agentData;
	const int n = manifold->m_numManifoldPoints;
	for (int i = 0; i < n; ++i)
	{
		unsigned char* point = hkGskManifold_points2(manifold) + i * 8;
		if (*(unsigned short*)(point + 2) == id)
		{
			point[0] = 0;
			point[1] = 0;
			return;
		}
	}
}

// =========================================================================================================
// @ 0x010ff820
void* HK_CALL hkGsk_cacheInit(const hkAgent3Input& input, hkAgentEntry* entry, void* cache)
{
	void* shapeB = (void*)input.m_bodyB->m_shape;
	void* shapeA = (void*)input.m_bodyA->m_shape;

	if (((hkConvexShapeView*)shapeB)->getType() == 6)
		hkGsk_initVertexCache(shapeA, shapeB, &input.m_aTb);
	else
		hkGsk_initFaceCache(shapeA, shapeB, &input.m_aTb);

	hkGskCache* c = (hkGskCache*)cache;
	const int zero = 0;
	entry->m_numContactPoints = 0;
	*(int*)((char*)cache + 0xc) = zero;
	return (char*)cache + (((c->m_faceVertexCnt + c->m_pointCnt * 4 + c->m_vertexCnt) * 2 + 0x1f) &
	                       0xfffffff0);
}

// =========================================================================================================
// @ 0x010ff8c0
void HK_CALL hkPredGskAgent3_sepNormal(const hkAgent3Input& input, void* agentData, hkVector4& normal)
{
	hkConvexShapeView* shapeA = (hkConvexShapeView*)input.m_bodyA->m_shape;
	hkConvexShapeView* shapeB = (hkConvexShapeView*)input.m_bodyB->m_shape;

	const unsigned char* features = (const unsigned char*)agentData;
	const int numA   = (signed char)features[8];
	const int numB   = (signed char)features[10];
	const int idOfsA = (signed char)features[9];
	const int idOfsB = (signed char)features[11];
	(void)idOfsB;

	hkVector4 featureA[12];
	char      featureB_raw[164];
	hkVector4* featureB = (hkVector4*)featureB_raw;
	(void)featureB;
	float featureInfo[8];

	featureInfo[1] = 0.0f;
	featureInfo[0] = 0.0f;

	shapeA->getSupportingVertices((const unsigned short*)agentData, numA, featureA);
	shapeB->getSupportingVertices((const unsigned short*)((const char*)agentData + idOfsA * 2), numB,
	                              featureB);

	hkGsk_getClosestFeature(shapeA, shapeB, &input.m_aTb, featureInfo);

	if (featureInfo[1] != 0.0f)
		hkGsk_updateVertexCache(featureInfo);

	const hkTransform* transA = (const hkTransform*)input.m_bodyA->m_motion;
	const float f0 = featureInfo[0], f1 = featureInfo[1], f2 = featureInfo[2], f3 = featureInfo[3];
	normal.x = f0 * transA->m_rot[0].x + f2 * transA->m_rot[1].x + f3 * transA->m_rot[2].x;
	normal.y = f0 * transA->m_rot[0].y + f2 * transA->m_rot[1].y + f3 * transA->m_rot[2].y;
	normal.z = f0 * transA->m_rot[0].z + f2 * transA->m_rot[1].z + f3 * transA->m_rot[2].z;
	normal.w = 0.0f;
	normal.w = (featureInfo[4] - shapeA->m_radius) - shapeB->m_radius;
}
