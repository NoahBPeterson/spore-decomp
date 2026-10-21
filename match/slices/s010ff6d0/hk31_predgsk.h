#pragma once
// Havok 3.1.0 predictive-GSK (predGsk) agent3 support structures, shared by gold4 slice s010ff6d0.
// Layouts come from the dev PDB (hkGskManifold, hkGskCache) and from the retail binary.
#include "../s010cbaa0/hk31_b005.h"

typedef unsigned short hkContactPointId;

struct hkAgentEntry
{
	unsigned char  m_streamCommand;    // +0x0
	unsigned char  m_agentType;        // +0x1
	unsigned char  m_numContactPoints; // +0x2
	unsigned char  m_size;             // +0x3
	unsigned int   m_userData;         // +0x4
};

struct hkAgent3Input
{
	const hkCdBody*         m_bodyA;  // +0x0
	const hkCdBody*         m_bodyB;  // +0x4
	const void*             m_input;  // +0x8
	hkTransform             m_aTb;    // +0xc
};

// hkShape with the virtual slots the predGsk agents call: slot 2 (+0x8) getType,
// slot 10 (+0x28) getSupportingVertices.  The leading 0xc bytes are the hkReferencedObject header
// (vftable, memSizeAndFlags+referenceCount, m_userData).
struct hkPredGskShapeView
{
	uint32_t m_vtblAndRefs[3];  // +0x0
	float    m_radius;          // +0xc
	virtual void s0(); virtual void s1();
	virtual int  getType() const;                                              // +0x8
	virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
	virtual void s7(); virtual void s8(); virtual void s9();
	virtual void getSupportingVertices(const unsigned short* ids, int numIds,
	                                   hkVector4* out) const;                  // +0x28
};

// The box/convex shape vtable layout used by the predGsk cache initialiser and sepNormal.
struct hkConvexShapeView : hkPredGskShapeView {};

// hkGskManifold: the predictive-GSK contact-point cache.  Byte +0x0 = numFaceVertex,
// +0x1 = numVertex, +0x2 = numPoints, +0x3 = isComplete; the sorted point array starts at +0xc and
// every entry is 8 bytes ({u16 featureA; u16 featureB; u16 contactPointId; u16 pad}).
struct hkGskManifold
{
	unsigned char  m_faceVertexFeatureCount;   // +0x0
	unsigned char  m_vertexFeatureCount;       // +0x1
	unsigned char  m_numPoints;                // +0x2
	unsigned char  m_isComplete;               // +0x3
	unsigned char  m_pad04[8];                 // +0x4
	unsigned char  m_pad0c[2];                 // +0xc
	unsigned char  m_numManifoldPoints;        // +0xe

	static void removePoint(hkGskManifold* m, int index);   // 0x0110fd70
	static void cleanup(hkGskManifold* m, void* mgr);        // 0x0110fdd0
};

// The point array the removePoint/commitPotential/updatePoint entries walk starts at +0x12 (updatePoint
// reads {u8 a; u8 b; u16 id} at +0x12, removePoint/commitPotential read just the u16 id there).
inline unsigned char* hkGskManifold_points(hkGskManifold* m) { return (unsigned char*)m + 0x12; }
// updatePoint walks an array of {u16 key; u16 id} records starting at +0x10 instead.
inline unsigned char* hkGskManifold_points2(hkGskManifold* m) { return (unsigned char*)m + 0x10; }

// hkGskCache: the shape-cache header the cache initialiser returns the "free" pointer for.  The
// supporting-vertex id arrays live in the 16-byte aligned region before/around it; the returned free
// pointer is ((faceVertex + vertexCount*4 + pointCount) * 2 + 0x1f) & ~0xf past the header base.
struct hkGskCache
{
	unsigned int   m_numIdsA;        // +0x00
	unsigned int   m_numIdsB;        // +0x04
	unsigned char  m_numFaceVertex;  // +0x08
	unsigned char  m_numVertex;      // +0x09
	unsigned char  m_numPoints;      // +0x0a
	unsigned char  m_pad0b;          // +0x0b
	unsigned char  m_faceVertexCnt;  // +0x0c
	unsigned char  m_vertexCnt;      // +0x0d
	unsigned char  m_pointCnt;       // +0x0e
	unsigned char  m_pad0f;          // +0x0f
	unsigned char  m_header[0x10];   // +0x10
};

// ---- external entry points ------------------------------------------------------------------------------
extern "C" void HK_CALL hkGsk_initVertexCache(void* shapeA, void* shapeB,
                                              const hkTransform* aTb);                 // 0x01113fd0
extern "C" void HK_CALL hkGsk_initFaceCache(void* shapeA, void* shapeB,
                                            const hkTransform* aTb);                   // 0x01113e90
extern "C" void HK_CALL hkGsk_updateVertexCache(float* featureInfo);                   // 0x0110cd00

extern "C" void HK_CALL hkGsk_getClosestFeature(void* shapeA, void* shapeB,
                                                const hkTransform* aTb, float* out);   // 0x0110e510

// ---- agent3 entry points (defined in s010ff6d0.cpp) ------------------------------------------------------
extern "C" void HK_CALL hkPredGskAgent3_removePoint(hkAgentEntry*, void*, hkContactPointId);
extern "C" void HK_CALL hkPredGskAgent3_commitPotential(hkAgentEntry*, void*, hkContactPointId);
extern "C" void HK_CALL hkPredGskAgent3_updatePoint(hkAgentEntry*, void*, hkContactPointId);
extern "C" void HK_CALL hkPredGskAgent3_sepNormal(const hkAgent3Input& input, void* agentData,
                                                  hkVector4& normal);
