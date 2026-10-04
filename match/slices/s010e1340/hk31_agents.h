#pragma once
// Havok 3.1.0 collision agents (hkCollisionAgent, hkShapeCollectionAgent, hkBvTreeAgent, hkMoppAgent and the symmetric
// wrappers) shared by batch b005 slices s010e1340 and s010e6530. Layouts from the 32-bit retail binary; member names from
// the Havok 6.x headers (hkpBvTreeAgent etc.), used for naming only.
#include "../s010869e0/hk31_world.h"

extern const char hkMonitorTimerEndTag[];
#define HK_REAL_MAX_BITS 0x7f7fffeeu
static inline float hkRealMax()      // 3.40282e+38f in this build: bit pattern 0x7f7fffee
{
	uint32_t u = HK_REAL_MAX_BITS;
	float f;
	memcpy(&f, &u, sizeof(f));
	return f;
}

class hkContactMgr;
class hkMoppCode;

// ---- collectors ----------------------------------------------------------------------------------------------
struct hkContactPoint
{
	hkVector4 m_position;                                  // +0
	hkVector4 m_separatingNormal;                          // +0x10 (w = distance)
	void setFlipped(const hkContactPoint& other);          // 0x010CECF0
};
struct hkCdPoint { hkContactPoint m_contact; const hkCdBody* m_cdBodyA; const hkCdBody* m_cdBodyB; };
class hkCdPointCollector
{
public:
	virtual ~hkCdPointCollector() {}                       // 0
	virtual void addCdPoint(const hkCdPoint& point) = 0;   // 1
	float m_earlyOutDistance;                              // +4
};
class hkCdBodyPairCollector
{
public:
	virtual ~hkCdBodyPairCollector() {}                     // 0
	virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b) = 0;   // 1
	hkBool m_earlyOut;                                     // +4
	hkCdBodyPairCollector() : m_earlyOut(false) {}
};
struct hkProcessCdPoint { hkContactPoint m_contact; uint32_t m_extra[4]; };     // 0x30 bytes
struct hkProcessCollisionOutput
{
	hkProcessCdPoint* m_firstFreeContactPoint;             // +0
	uint32_t m_pad0[3];
	hkContactPoint m_toiContact;                           // +0x10 (normal at +0x20)
	hkProcessCdPoint m_contactPoints[256];                 // +0x30
	uint32_t m_toiProperties;                              // +0x3030
	float m_toiTime;                                       // +0x3034
};
struct hkLinearCastCollisionInput : hkCollisionInput
{
	hkVector4 m_path;                         // +0x10
	float m_maxExtraPenetration;              // +0x20
	float m_cachedPathLength;                 // +0x24
	void* m_config;                           // +0x28
};

// Symmetric-agent collector wrappers (vtables 0x014A43AC, 0x014A43B4): flip the reported points / body pairs.
class hkSymmetricAgentFlipCollector : public hkCdPointCollector        // vtable 0x014A43A4
{
public:
	explicit hkSymmetricAgentFlipCollector(hkCdPointCollector& original) : m_original(original) { m_earlyOutDistance = hkRealMax(); }
	virtual void addCdPoint(const hkCdPoint& point);           // 0x010EBBB0
	hkCdPointCollector& m_original;                            // +8
};
class hkSymmetricAgentFlipCastCollector : public hkCdPointCollector    // size 0x30 in the binary
{
public:
	hkSymmetricAgentFlipCastCollector(const hkVector4& path, hkCdPointCollector* original)
		: m_path(path), m_original(original) { m_earlyOutDistance = hkRealMax(); }
	virtual void addCdPoint(const hkCdPoint& point);           // 0x010EBC00
	hkVector4 m_path;                                          // +0x10
	hkCdPointCollector* m_original;                            // +0x20
};
class hkSymmetricAgentFlipBodyCollector : public hkCdBodyPairCollector    // 0x014A43B4
{
public:
	explicit hkSymmetricAgentFlipBodyCollector(hkCdBodyPairCollector& original) : m_original(original) { m_earlyOut = hkBool(false); }
	virtual void addCdBodyPair(const hkCdBody& a, const hkCdBody& b);   // 0x010EBC50
	hkCdBodyPairCollector& m_original;                         // +8
};

// ---- agents --------------------------------------------------------------------------------------------------
class hkCollisionAgent : public hkReferencedObject             // vtable slots 2..9 as used by the compound agents
{
public:
	virtual void getPenetrations(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkCdBodyPairCollector& collector) = 0;       // 2
	virtual void getClosestPoints(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkCdPointCollector& collector) = 0;          // 3
	virtual void linearCast(const hkCdBody& a, const hkCdBody& b, const hkLinearCastCollisionInput& input,
	                        hkCdPointCollector& castCollector, hkCdPointCollector* startCollector) = 0;                                                 // 4
	virtual void processCollision(const hkCdBody& a, const hkCdBody& b, const hkProcessCollisionInput& input, hkProcessCollisionOutput& output) = 0;   // 5
	virtual void cleanup() = 0;                                                                                                                     // 6
	virtual void updateShapeCollectionFilter(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input) = 0;                               // 7
	virtual void invalidateTim(hkCollisionInput& input);                                                                                             // 8
	virtual void warpTime(float oldTime, float newTime, hkCollisionInput& input);                                                                    // 9
	virtual void removePoint(unsigned short contactPointId);                                                                                         // 10 (0x010829F0)
	virtual void commitPotential(unsigned short contactPointId);                                                                                     // 11
	virtual void createZombie(unsigned short contactPointId);                                                                                        // 12

	hkContactMgr* m_contactMgr;     // +8
protected:
	explicit hkCollisionAgent(hkContactMgr* mgr) : m_contactMgr(mgr) {}
};

struct hkShapeCollectionKeyAgentPair { unsigned int m_key; hkCollisionAgent* m_agent; };   // 8 bytes

class hkShapeCollectionAgent : public hkCollisionAgent           // vtable 0x014A4D24, size 0x38
{
public:
	hkShapeCollectionAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010E1090
	virtual ~hkShapeCollectionAgent();                           // 0 (scalar deleting destructor 0x010E1380, shared with hkMultiSphereAgent)
	virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);           // 0x010E0C30
	virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);              // 0x010E0730
	virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);   // 0x010E09B0
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);   // 0x010E0610
	virtual void cleanup();
	virtual void updateShapeCollectionFilter(const hkCdBody&, const hkCdBody&, const hkCollisionInput&);                       // 0x010E0EC0
	virtual void invalidateTim(hkCollisionInput& input);                                                                        // 0x010E0590
	virtual void warpTime(float oldTime, float newTime, hkCollisionInput& input);                                               // 0x010E05C0

	static hkCollisionAgent* createListAAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010E1340
	static hkCollisionAgent* createListBAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010E14D0

	hkInplaceArray<hkShapeCollectionKeyAgentPair, 4> m_agents;    // +0xc (data, size, capacity, 4 inline pairs)
};

// ---- MOPP / BV tree -----------------------------------------------------------------------------------------
class hkShapeCollection : public hkShape
{
public:
	virtual int getNumChildShapes() const = 0;                                                // 7 (+0x1c, 0x010E7F80)
	virtual void shapeCollectionSlot8();                                                      // 8
	virtual void shapeCollectionSlot9();                                                      // 9
	virtual const hkShape* getChildShape(unsigned int key, void* shapeBuffer) const = 0;      // 10 (+0x28)
};
struct hkShapeBuffer { uint8_t m_data[0x200]; };      // child-shape scratch buffer (524 bytes of stack in the binary)
class hkBvTreeShape : public hkShape
{
public:
	hkShapeCollection* m_shapeCollection;             // +0xc
};
struct hkMoppCodeView                                 // hkMoppCode: m_info at +0x10, m_data array at +0x20
{
	uint32_t m_header[4];
	uint32_t m_info[4];
	hkArray<unsigned char> m_data;                    // +0x20 (size at +0x24)
};
class hkMoppBvTreeShape : public hkBvTreeShape
{
public:
	const hkMoppCodeView* m_code;                     // +0x10
};

struct hkBvAgentEntryInfo                             // 12 bytes
{
	unsigned int m_key;                               // +0
	int m_userInfo;                                   // +4
	hkCollisionAgent* m_collisionAgent;               // +8
};
class hkBvTreeAgent : public hkCollisionAgent         // vtable 0x014A4D9C, size 0x40
{
public:
	explicit hkBvTreeAgent(hkContactMgr* mgr);                                              // 0x010E21A0
	virtual ~hkBvTreeAgent();                                                               // 0: 0x010E19F0 (deleting), body 0x010E1A50
	virtual void calcStatistics(hkStatisticsCollector* c) const;                            // 1 (0x010E2110)
	virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);   // 0x010E4FB0
	virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);      // 0x010E4BE0
	virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);   // 0x010E4840
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);   // 0x010E3430
	virtual void cleanup();                                                                 // 0x010E1D30
	virtual void updateShapeCollectionFilter(const hkCdBody&, const hkCdBody&, const hkCollisionInput&);   // 0x010E1E00
	virtual void invalidateTim(hkCollisionInput& input);                                    // 0x010E1D70
	virtual void warpTime(float oldTime, float newTime, hkCollisionInput& input);           // 0x010E1DB0

	static void calcAabbLinearCast(const hkCdBody& a, const hkCdBody& b, const hkLinearCastCollisionInput& input, hkAabb& aabbOut);   // 0x010E1F90
	static hkCollisionAgent* createShapeBvAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010E21F0
	static hkCollisionAgent* createBvTreeShapeAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010E5450
	static void registerAgent(hkCollisionDispatcher* dispatcher);                           // 0x010E1C70
	static void registerPredictiveAgent(hkCollisionDispatcher* dispatcher);                 // 0x010E1720

	hkArray<hkBvAgentEntryInfo> m_collisionPartners;        // +0xc
	hkAabb m_cachedAabb;                                    // +0x20 (16-byte aligned through hkVector4)
};

class hkMoppAgent : public hkBvTreeAgent
{
public:
	explicit hkMoppAgent(hkContactMgr* mgr) : hkBvTreeAgent(mgr) {}
	static void staticLinearCast(const hkCdBody& a, const hkCdBody& b, const hkLinearCastCollisionInput& input,
	                             hkCdPointCollector& castCollector, hkCdPointCollector* startCollector);      // 0x010E17E0
	static hkCollisionAgent* createBvBvAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010E1C00
};

// hkSymmetricAgent<AGENT>: runs AGENT with the two bodies swapped and flips the results (vtable of the binary's
// hkSymmetricAgent<hkShapeCollectionAgent> is 0x014A4D58, of hkSymmetricAgent<hkMoppAgent> 0x014A4E0C).
template <typename AGENT>
class hkSymmetricAgent : public AGENT
{
public:
	hkSymmetricAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr) : AGENT(a, b, input, mgr) {}
	explicit hkSymmetricAgent(hkContactMgr* mgr) : AGENT(mgr) {}
	virtual void getPenetrations(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkCdBodyPairCollector& collector);
	virtual void getClosestPoints(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkCdPointCollector& collector);
	virtual void linearCast(const hkCdBody& a, const hkCdBody& b, const hkLinearCastCollisionInput& input,
	                        hkCdPointCollector& castCollector, hkCdPointCollector* startCollector);
	virtual void processCollision(const hkCdBody& a, const hkCdBody& b, const hkProcessCollisionInput& input, hkProcessCollisionOutput& output);
};

// Template member definitions (explicitly instantiated in the slices that own the binary's instances).
template <typename AGENT>
void hkSymmetricAgent<AGENT>::getPenetrations(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdBodyPairCollector& collector)
{
	hkSymmetricAgentFlipBodyCollector flipCollector(collector);
	AGENT::getPenetrations(bodyB, bodyA, input, flipCollector);
}

template <typename AGENT>
void hkSymmetricAgent<AGENT>::getClosestPoints(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkCdPointCollector& collector)
{
	hkSymmetricAgentFlipCollector flipCollector(collector);
	AGENT::getClosestPoints(bodyB, bodyA, input, flipCollector);
}

template <typename AGENT>
void hkSymmetricAgent<AGENT>::linearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input,
                                         hkCdPointCollector& collector, hkCdPointCollector* startCollector)
{
	// copy of the input with the path negated (all four components, as the binary does)
	hkLinearCastCollisionInput input2 = input;
	input2.m_path.x = -input.m_path.x;
	input2.m_path.y = -input.m_path.y;
	input2.m_path.z = -input.m_path.z;
	input2.m_path.w = -input.m_path.w;

	hkSymmetricAgentFlipCastCollector flipCollector(input.m_path, &collector);
	if (startCollector)
	{
		hkSymmetricAgentFlipCastCollector flipStartCollector(input.m_path, startCollector);
		AGENT::linearCast(bodyB, bodyA, input2, flipCollector, &flipStartCollector);
	}
	else
	{
		AGENT::linearCast(bodyB, bodyA, input2, flipCollector, 0);
	}
}

template <typename AGENT>
void hkSymmetricAgent<AGENT>::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkProcessCollisionInput& input, hkProcessCollisionOutput& output)
{
	float toiTimeBefore = output.m_toiTime;
	hkProcessCdPoint* firstNewPoint = output.m_firstFreeContactPoint;
	AGENT::processCollision(bodyB, bodyA, input, output);
	for (hkProcessCdPoint* p = firstNewPoint; p < output.m_firstFreeContactPoint; ++p)
		p->m_contact.setFlipped(p->m_contact);
	if (toiTimeBefore != output.m_toiTime)       // fucompp: unordered counts as different
	{
		output.m_toiContact.m_separatingNormal.x = -output.m_toiContact.m_separatingNormal.x;
		output.m_toiContact.m_separatingNormal.y = -output.m_toiContact.m_separatingNormal.y;
		output.m_toiContact.m_separatingNormal.z = -output.m_toiContact.m_separatingNormal.z;
	}
}

// ---- multi sphere / bounding volume ------------------------------------------------------------------------
class hkSphereShape : public hkShape                          // 0x10 bytes
{
public:
	explicit hkSphereShape(float radius);                                                     // 0x010C3770
	virtual int getType() const;
	virtual void getAabb(const hkTransform& localToWorld, float tolerance, hkAabb& out) const;
	virtual float getMaximumProjection(const hkVector4& direction) const;
	virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const;
	virtual void castRayWithCollector(const hkShapeRayCastInput& input, const hkCdBody& cdBody, hkRayHitCollector& collector) const;
	float m_radius;                                           // +0xc
};
struct hkMultiSphereShapeView                                 // hkMultiSphereShape layout: hkShape (0xc), count, 8 spheres (x,y,z,radius)
{
	uint32_t m_header[3];
	int m_numSpheres;                                         // +0xc
	hkVector4 m_spheres[8];                                   // +0x10 (w = radius)
};
struct hkBvShapeView                                          // hkBvShape layout: m_boundingVolumeShape +0xc, m_childShape +0x10
{
	uint32_t m_header[3];
	const hkShape* m_boundingVolumeShape;
	const hkShape* m_childShape;
};
class hkMultiSphereAgent : public hkCollisionAgent            // vtable 0x014A4E54, size 0x38
{
public:
	hkMultiSphereAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010E6530
	virtual ~hkMultiSphereAgent();                            // 0 (shares 0x010E1380 with hkShapeCollectionAgent)
	virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);   // 0x010E5FD0
	virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);      // 0x010E5850
	virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);   // 0x010E5BF0
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);   // 0x010E5630
	virtual void cleanup();
	virtual void updateShapeCollectionFilter(const hkCdBody&, const hkCdBody&, const hkCollisionInput&);
	static hkCollisionAgent* createListAAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010E68D0
	static hkCollisionAgent* createListBAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010E6A30
	hkInplaceArray<hkShapeCollectionKeyAgentPair, 4> m_agents;    // +0xc
};
class hkBvAgent : public hkCollisionAgent                     // vtable 0x014A4EC0, size 0x14
{
public:
	hkBvAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010E6C00
	virtual void getPenetrations(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdBodyPairCollector&);   // 0x010E7750
	virtual void getClosestPoints(const hkCdBody&, const hkCdBody&, const hkCollisionInput&, hkCdPointCollector&);      // 0x010E7390
	virtual void linearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);   // 0x010E6F90
	virtual void processCollision(const hkCdBody&, const hkCdBody&, const hkProcessCollisionInput&, hkProcessCollisionOutput&);   // 0x010E6D90
	virtual void cleanup();                                                       // 0x010E6B00
	virtual void updateShapeCollectionFilter(const hkCdBody&, const hkCdBody&, const hkCollisionInput&);   // 0x010E6CF0
	virtual void invalidateTim(hkCollisionInput& input);                          // 0x010E6B30
	virtual void warpTime(float oldTime, float newTime, hkCollisionInput& input); // 0x010E6B60
	virtual void removePoint(unsigned short contactPointId);                      // 0x010E6BA0
	virtual void commitPotential(unsigned short contactPointId);                  // 0x010E6BC0
	virtual void createZombie(unsigned short contactPointId);                     // 0x010E6BE0
	static void staticLinearCast(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&, hkCdPointCollector&, hkCdPointCollector*);   // 0x010E71B0
	static hkCollisionAgent* createBvShapeAgent(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input, hkContactMgr* mgr);   // 0x010E6CB0
	hkCollisionAgent* m_boundingVolumeAgent;                  // +0xc
	hkCollisionAgent* m_childAgent;                           // +0x10
};

// ---- MOPP aabb cast ------------------------------------------------------------------------------------------
struct hkMoppAabbCastInput                    // built on the stack by hkMoppAgent::staticLinearCast
{
	hkVector4 m_from;                         // +0
	hkVector4 m_to;                           // +0x10
	hkVector4 m_extents;                      // +0x20 (half extents)
	const hkLinearCastCollisionInput* m_input;   // +0x30
	const hkCdBody* m_bodyA;                  // +0x34
	const hkCdBody* m_bodyB;                  // +0x38
};
struct hkMoppAabbCastVirtualMachine           // 0x30 bytes on the stack, never constructed explicitly
{
	uint32_t m_state[12];
	void aabbCast(const hkMoppAabbCastInput& input, hkCdPointCollector& castCollector, hkCdPointCollector* startCollector);   // 0x01115400
};

// the null agent singleton (0x010CD8D0)
hkCollisionAgent* hkNullAgent_getNullAgent();
