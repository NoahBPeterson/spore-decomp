#pragma once
// Havok 3.1.0 sphere/capsule, sphere/sphere and box/box collision agents, shared by gold4 slices s010d8520 and
// s010d9470. Layouts come from the retail binary; the member names follow the Havok 6.x headers (hkpSphereCapsuleAgent
// etc.) and are used for naming only.
#include "../s010e1340/hk31_agents.h"

// hkTransform stored in the "transposed" convention the sphere agents use: the three vectors at +0 are the *columns*
// of the basis, the translation is at +0x30.  Indexed as trans->m_col[c] . row.
struct HK_ALIGN16 hkTransformCols
{
	hkVector4 m_col[3];      // +0  (basis columns)
	hkVector4 m_trans;       // +0x30
};

// hkSphereShape (0x10 bytes) and hkCapsuleShape: hkShape (0xc) with m_radius at +0xc; a capsule carries the two
// segment endpoints at +0x10 and +0x20 (read by the sphere/capsule agent as *shape+{0x10,0x20}).
struct hkSphereShapeView
{
	uint32_t m_header[3];    // +0  (vftable, memSizeAndFlags+referenceCount, m_userData)
	float m_radius;          // +0xc
};
struct hkCapsuleShapeView
{
	uint32_t m_header[3];    // +0
	float m_radius;          // +0xc
	hkVector4 m_vertexA;     // +0x10
	hkVector4 m_vertexB;     // +0x20
};
// hkConvexShape (box): the last component of m_halfExtents is the "radius" the box-box factory compares.
struct hkConvexShapeView
{
	uint32_t m_header[3];    // +0
	float m_radius;          // +0xc
	hkVector4 m_halfExtents; // +0x10 (w at +0x1c)
};

// hkCollideTriangleUtil::ClosestPointLineSegResult (the point, then padding).
struct ClosestPointLineSegResult
{
	hkVector4 m_point;       // +0
	uint32_t m_pad[4];
};
class hkCollideTriangleUtil
{
public:
	static int HK_CALL closestPointLineSeg(const hkVector4& a, const hkVector4& b, const hkVector4& c,
	                                       ClosestPointLineSegResult& outResult);   // 0x01105c30
};

// hkContactMgr: only the slots these agents use (2 = addContactPoint at +8, 4 = removePoint at +0x10).
class hkContactMgr : public hkReferencedObject
{
public:
	virtual unsigned short addContactPoint(const hkCdBody& bodyA, const hkCdBody& bodyB,
	                                       const hkProcessCollisionInput& input, hkProcessCdPoint& point);   // slot 2 (+8)
	virtual void contactMgrSlot3();                                                                    // slot 3 (+0xc)
	virtual void removePoint(unsigned short contactPointId);                                           // slot 4 (+0x10)
};

// The shared linear-cast stub used by both agents' registerAgent (the PDB names it hkIterativeLinearCastAgent).
void HK_CALL hkIterativeLinearCastAgent_staticLinearCast(const hkCdBody& a, const hkCdBody& b,
                                                         const hkLinearCastCollisionInput& input,
                                                         hkCdPointCollector& castCollector,
                                                         hkCdPointCollector* startCollector);   // 0x010ebc80

// ---- sphere/sphere agent -------------------------------------------------------------------------------------
class hkSphereSphereAgent : public hkCollisionAgent          // vtable 0x014a4850, size 0x10
{
public:
	static hkSphereSphereAgent* HK_CALL create(hkContactMgr* mgr);                                 // 0x010d8a00
	virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);   // 0x010d90a0
	virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);      // 0x010d8c80
	virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);   // 0x010d8a30
	virtual void cleanup();                                                                                              // 0x010d89d0
	virtual void updateShapeCollectionFilter(const hkCdBody&, const hkCdBody&, const hkCollisionInput&);

	static void HK_CALL staticGetClosestPoints(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input,
	                                           hkCdPointCollector& collector);                                          // 0x010d8e90
	static void HK_CALL staticGetPenetrations(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input,
	                                          hkCdBodyPairCollector& collector);                                        // 0x010d91a0
	static void HK_CALL registerAgent(hkCollisionDispatcher* dispatcher);                                               // 0x010d92a0

protected:
	hkSphereSphereAgent(hkContactMgr* mgr) : hkCollisionAgent(mgr), m_contactPointId(0xffff) {}
	unsigned short m_contactPointId;      // +0xc
};

// ---- box/box agent --------------------------------------------------------------------------------------------
// hkBoxBoxAgent (Havok 3.1): hkCollisionAgent (0xc) with the box-box manifold starting at +0x10 (the shared
// hkBoxBoxManifold_init at 0x010ec500 is called with ecx = agent + 0x10).  cleanup walks a child array at +0x12
// (stride 4, {u16 key; u16 pad}) with a byte count at +0x31, so the manifold's contact records start 2 bytes in.
struct hkBoxBoxManifold
{
	uint8_t m_pad0[2];                                                // +0x10
	struct Entry { uint16_t m_key; uint16_t m_pad; } m_entries[8];    // +0x12 (stride 4)
	uint8_t m_pad32[0x2e];                                            // +0x32
	void init();                                                      // 0x010ec500
};
// The byte count used by cleanup lives at agent + 0x31 == manifold + 0x21.
inline unsigned char& hkBoxBoxManifold_numEntries(hkBoxBoxManifold& m) { return ((unsigned char*)&m)[0x21]; }
inline const unsigned char& hkBoxBoxManifold_numEntries(const hkBoxBoxManifold& m) { return ((const unsigned char*)&m)[0x21]; }

// The unnamed helper (0x010d93e0) refreshes a cached origin/axis pair.  It is called on a box-box helper object whose
// transform rows are at +0x20/+0x30/+0x40, translation at +0x50, cached origin at +0xc0 and cached axis at +0xd0.
// The binary passes the object in ECX, so it is a __fastcall member-style helper.
struct hkBoxBoxOriginCache
{
	uint8_t m_pad00[0x20];
	hkVector4 m_rot[3];        // +0x20
	hkVector4 m_trans;         // +0x50
	uint8_t m_pad60[0x60];
	hkVector4 m_cachedOrigin;  // +0xc0
	hkVector4 m_cachedAxis;    // +0xd0
	void update();             // 0x010d93e0
};

extern const float g_hkBoxBoxRadiusFactor;                       // 0x014a48c8 (1.999f)

class hkBoxBoxAgent : public hkCollisionAgent               // vtable 0x014a4894, size 0x60
{
public:
	virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);
	virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);
	virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);   // 0x010d9470
	virtual void cleanup();                                                                                            // 0x010d92f0
	virtual void updateShapeCollectionFilter(const hkCdBody&, const hkCdBody&, const hkCollisionInput&);

	static hkCollisionAgent* HK_CALL createBoxBoxAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010d9330
	static void HK_CALL staticGetClosestPoints(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input,
	                                           hkCdPointCollector& collector);                                          // 0x010d97a0
	static void HK_CALL staticGetPenetrations(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input,
	                                          hkCdBodyPairCollector& collector);                                        // 0x010d9b10
	static void HK_CALL registerAgent(hkCollisionDispatcher* dispatcher);                                               // 0x010d9e50

protected:
	hkBoxBoxAgent(hkContactMgr* mgr) : hkCollisionAgent(mgr) {}
	uint32_t m_pad0c;                 // +0xc
	hkBoxBoxManifold m_manifold;      // +0x10
};

// hkGskfAgent factory (the box-box fallback) and the shared manifold initialiser.
hkCollisionAgent* HK_CALL hkGskfAgent_createGskfAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010ec690
void hkBoxBoxManifold_init(hkBoxBoxManifold* manifold);      // 0x010ec500 (ecx = agent + 0x10)
