// @ 0x010E3430  hkBvTreeAgent::processCollision (Havok 3.1.0, profiler list "LtBvTree" / "QueryTree" / "StNarrowPhase")
//
// 1. Computes the aabb of body A in body B's space (bTa = inverse(B) * A, A's shape getAabb).  With continuous
//    physics the aabb is grown by the angular sweep of both bodies, clipped against the sphere that bounds A's end
//    position, and the relative linear motion of A in B's space is extended by B's angular velocity.
// 2. If aabb caching is on (global 0x015BA318) and the cached aabb (m_cachedAabb) still contains the new aabb, the
//    tree query and the partner update are skipped.  Otherwise the aabb is grown by the tolerance and by the motion
//    (clamped to 0.4 of its extent), stored as the new cached aabb, and the BV tree is queried with it.
// 3. The collision partners are updated against the query result: either in place (global 0x016E58F9 set: unknown
//    keys are removed with removeAtAndCopy, new keys inserted at the hit index) or by sorting the hit list and
//    merging it with the (sorted) partner list into a stack-allocated array that is then copied back.  New partners
//    get an agent from the dispatcher when the shape-collection filter enables the pair, else the null agent.
// 4. Every partner agent's processCollision is called with the child body of B.
//
// Complete source.  The x87 operation order follows the disassembly; not byte-exact.
#include "../s010e1340/hk31_agents.h"

typedef unsigned int hkShapeKey;

// ---- externals (redeclared here with their addresses) ----------------------------------------------------------
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern unsigned long g_hkThreadMemoryTls;           // 0x016e4174
hkCollisionAgent* hkNullAgent_getNullAgent();       // 0x010cd8d0

// ---- globals -------------------------------------------------------------------------------------------------
extern hkBool g_hkBvTreeAgentUseAabbCaching;        // 0x015BA318
extern hkBool g_hkBvTreeAgentUpdateKeysInPlace;     // 0x016E58F9
extern const char hkMonitorTimerListEndTag[];       // "lt" at 0x0143CD94

// ---- profiler list commands (begin list: 0x10-byte command, split: 0xc bytes, end: 0xc bytes) ---------------
struct hkMonitorListCommand { const char* m_command; uint32_t m_time0; uint32_t m_pad; const char* m_firstTimer; };

static inline void hkTimerBeginList(const char* name, const char* firstTimer)
{
	void* end = hkTlsGet(g_hkMonitorStreamEndTls);
	if (hkTlsGet(g_hkMonitorStreamCurrentTls) < end)
	{
		hkMonitorListCommand* c = (hkMonitorListCommand*)hkTlsGet(g_hkMonitorStreamCurrentTls);
		c->m_command = name;
		c->m_firstTimer = firstTimer;
		c->m_time0 = HK_RDTSC32();
		hkTlsSet(g_hkMonitorStreamCurrentTls, c + 1);
	}
}

// ---- thread memory (stack area + chunk allocator) ------------------------------------------------------------
class hkThreadMemoryView
{
public:
	virtual ~hkThreadMemoryView();
	virtual void setStackArea(void* buf, int nbytes);                   // 1
	virtual void releaseCachedMemory();                                 // 2
	virtual void* onStackOverflow(int nbytes);                          // 3 (+0xc)
	virtual void onStackUnderflow(void* p);                             // 4 (+0x10)

	void* allocateChunk(int nbytes, int cl);                            // 0x0107DAA0
	void deallocateChunk(void* p, int nbytes, int cl);                  // 0x0107DB10

	void* allocateStack(int nbytes)
	{
		nbytes = (nbytes + 15) & ~15;
		char* current = m_stackCurrent;
		if (current + nbytes > m_stackEnd)
			return onStackOverflow(nbytes);
		m_stackCurrent = current + nbytes;
		return current;
	}
	void deallocateStack(void* p)
	{
		m_stackCurrent = (char*)p;
		if (p == m_stackBase)
			onStackUnderflow(p);
	}

	uint32_t m_pad04[7];
	char* m_stackCurrent;      // +0x20
	void* m_stackPrev;         // +0x24
	char* m_stackBase;         // +0x28
	char* m_stackEnd;          // +0x2c
};
static inline hkThreadMemoryView& hkThreadMemoryInstance() { return *(hkThreadMemoryView*)hkTlsGet(g_hkThreadMemoryTls); }

// hkLocalArray<T>: hkArray whose storage comes from the thread-memory stack.
template <typename T>
struct hkLocalArray : hkArray<T>
{
	explicit __forceinline hkLocalArray(int n)
	{
		this->m_data = 0;
		this->m_size = 0;
		this->m_capacityAndFlags = (int)0x80000000;
		this->m_data = (T*)hkThreadMemoryInstance().allocateStack(n * (int)sizeof(T));
		this->m_capacityAndFlags = n | (int)0x80000000;
		m_localMemory = this->m_data;
	}
	__forceinline ~hkLocalArray()
	{
		hkThreadMemoryInstance().deallocateStack(m_localMemory);
		if (this->m_capacityAndFlags >= 0)
			hkThreadMemoryInstance().deallocateChunk(this->m_data, (this->m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
	}
	T* m_localMemory;
};

// ---- shapes / quality info -----------------------------------------------------------------------------------
class hkBvTreeShapeQuery : public hkShape
{
public:
	virtual void bvTreeSlot7();
	virtual void bvTreeSlot8();
	virtual void queryAabb(const hkAabb& aabb, hkArray<hkShapeKey>& hits) const = 0;     // 9 (+0x24)
	hkShapeCollection* m_shapeCollection;                                                  // +0xc
};
struct hkCollisionQualityInfoView
{
	float m_keepContact, m_create4dContact, m_createContact, m_manifoldTimDistance;
	hkBool m_useContinuousPhysics;                       // +0x10
};
struct hkStepInfoView { float m_startTime, m_endTime, m_deltaTime, m_invDeltaTime; };   // hkProcessCollisionInput +0x10

namespace hkAlgorithm
{
	template <typename T> struct less { bool operator()(const T& a, const T& b) const { return a < b; } };
	template <typename T, typename L> void quickSortRecursive(T* pArr, int d, int h, L cmpLess);   // 0x010CDC20 (T = unsigned int)
}

// The (input, bodyA, bodyB, container, key) overload is slot 0 of hkShapeCollectionFilter's vtable in the binary.
class hkShapeCollectionFilterView
{
public:
	virtual hkBool isCollisionEnabled(const hkCollisionInput& input, const hkCdBody& collA, const hkCdBody& collB,
	                                  const hkShapeCollection& bContainer, unsigned int bKey) const = 0;           // 0
};
// Child-shape scratch buffer (0x200 bytes; dword elements so no /GS cookie is generated).
struct hkShapeBufferStorage { uint32_t m_data[0x80]; };

// ---- helpers -------------------------------------------------------------------------------------------------
// (z * r.z + y * r.y) + x * r.x per column: the operation order of the inlined hkVector4::setRotatedInverseDir.
// X87-PRECISION: the inputs and the sums stay on the FPU stack; only the results are stored (rounded to float).
static inline void rotateInverse(hkVector4& out, const hkTransform& t, hkX87Real x, hkX87Real y, hkX87Real z)
{
	out.x = (z * t.m_rot[0].z + y * t.m_rot[0].y) + x * t.m_rot[0].x;
	out.y = (z * t.m_rot[1].z + y * t.m_rot[1].y) + x * t.m_rot[1].x;
	out.z = (z * t.m_rot[2].z + y * t.m_rot[2].y) + x * t.m_rot[2].x;
}

// hkCollisionDispatcher::getNewCollisionAgent
static __forceinline hkCollisionAgent* getNewCollisionAgent(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input, hkContactMgr* mgr)
{
	hkCollisionDispatcher* dispatcher = (hkCollisionDispatcher*)input.m_dispatcher;
	int typeA = bodyA.m_shape->getType();
	int typeB = bodyB.m_shape->getType();
	const uint8_t (*table)[32] = input.m_createPredictiveAgents ? dispatcher->m_agent2TypesPred : dispatcher->m_agent2Types;
	return dispatcher->m_agent2Func[table[typeA][typeB]].m_createFunc(bodyA, bodyB, input, mgr);
}

// Agent for a new partner: the dispatcher's agent if the filter enables the pair, else the null agent.
static __forceinline hkCollisionAgent* createPartnerAgent(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkCollisionInput& input,
                                                   const hkShapeCollection* collection, hkShapeKey key, hkCdBody& childBody,
                                                   hkShapeBufferStorage& shapeBuffer, hkContactMgr* mgr)
{
	childBody.m_shape = collection->getChildShape(key, (hkShapeBuffer*)&shapeBuffer);
	childBody.m_shapeKey = key;
	if (((const hkShapeCollectionFilterView*)input.m_filter)->isCollisionEnabled(input, bodyA, bodyB, *collection, key))
		return getNewCollisionAgent(bodyA, childBody, input, mgr);
	return hkNullAgent_getNullAgent();
}

// ---------------------------------------------------------------------------------------------------------------
void hkBvTreeAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                     const hkProcessCollisionInput& input, hkProcessCollisionOutput& output)
{
	hkTimerBeginList("LtBvTree", "QueryTree");

	hkInplaceArray<hkShapeKey, 128> hitList;
	hitList.m_data = hitList.m_storage;
	hitList.m_size = 0;
	hitList.m_capacityAndFlags = (int)0x80000080;

	const hkMotionState* msA = (const hkMotionState*)bodyA.m_motion;
	const hkMotionState* msB = (const hkMotionState*)bodyB.m_motion;
	hkTransform bTa;
	bTa.setMulInverseMul(msB->m_transform, msA->m_transform);

	// relative linear motion of A during this step, in B's space (w = 0)
	hkVector4 linearMotion;
	{
		const float deltaTime = ((const hkStepInfoView*)input.m_stepInfo)->m_deltaTime;
		const hkMotionState::hkSweptTransform& stA = msA->m_sweptTransform;
		const hkMotionState::hkSweptTransform& stB = msB->m_sweptTransform;
		// X87-PRECISION: dAx, dAy, fA/fB as first used, mAy, vy and vz stay on the FPU stack; the other
		// intermediates are stored to float stack slots by the original.
		hkX87Real dAx = (hkX87Real)stA.m_centerOfMass0.x - stA.m_centerOfMass1.x;
		hkX87Real dAy = (hkX87Real)stA.m_centerOfMass0.y - stA.m_centerOfMass1.y;
		float dAz = stA.m_centerOfMass0.z - stA.m_centerOfMass1.z;
		float dBx = stB.m_centerOfMass1.x - stB.m_centerOfMass0.x;
		float dBy = stB.m_centerOfMass1.y - stB.m_centerOfMass0.y;
		float dBz = stB.m_centerOfMass1.z - stB.m_centerOfMass0.z;
		hkX87Real fAx87 = (hkX87Real)deltaTime * stA.m_centerOfMass1.w;    // m_centerOfMass1.w = inverse delta time
		float fA = (float)fAx87;
		float mAx = (float)(fAx87 * dAx);
		hkX87Real mAy = dAy * fA;
		float mAz = dAz * fA;
		hkX87Real fBx87 = (hkX87Real)deltaTime * stB.m_centerOfMass1.w;
		float fB = (float)fBx87;
		float vx = (float)(fBx87 * dBx + mAx);
		hkX87Real vy = (hkX87Real)dBy * fB + mAy;
		hkX87Real vz = (hkX87Real)dBz * fB + mAz;
		rotateInverse(linearMotion, msB->m_transform, vx, vy, vz);
		linearMotion.w = 0.0f;
	}

	hkAabb* cachedAabb = g_hkBvTreeAgentUseAabbCaching ? &m_cachedAabb : 0;

	hkAabb aabb;
	hkVector4 diag;
	const hkCollisionQualityInfoView* quality = (const hkCollisionQualityInfoView*)input.m_collisionQualityInfo;
	if (!quality->m_useContinuousPhysics)
	{
		bodyA.m_shape->getAabb(bTa, input.m_tolerance * 0.5f, aabb);
		diag.x = aabb.m_max.x - aabb.m_min.x;
		diag.y = aabb.m_max.y - aabb.m_min.y;
		diag.z = aabb.m_max.z - aabb.m_min.z;
		diag.w = aabb.m_max.w - aabb.m_min.w;
	}
	else
	{
		// angular sweep of both bodies
		float angularExtraB = msB->m_objectRadius * msB->m_deltaAngle.w * msB->m_deltaAngle.w;
		bodyA.m_shape->getAabb(bTa,
			(float)((((hkX87Real)msA->m_deltaAngle.w + msB->m_deltaAngle.w) * msA->m_objectRadius + angularExtraB) + (hkX87Real)input.m_tolerance * 0.5f), aabb);

		// clip against the sphere around A's end position (in B's space)
		const hkMotionState* msB2 = (const hkMotionState*)bodyB.m_motion;
		// X87-PRECISION: the radius, the differences fed to the rotation and -radius stay on the FPU stack.
		hkX87Real radius = ((hkX87Real)input.m_tolerance * 0.5f + msA->m_objectRadius) + angularExtraB;
		hkVector4 center;
		rotateInverse(center, msB2->m_transform,
		              (hkX87Real)msA->m_sweptTransform.m_centerOfMass1.x - msB2->m_transform.m_trans.x,
		              (hkX87Real)msA->m_sweptTransform.m_centerOfMass1.y - msB2->m_transform.m_trans.y,
		              (hkX87Real)msA->m_sweptTransform.m_centerOfMass1.z - msB2->m_transform.m_trans.z);
		hkVector4 sphereMax, sphereMin;
		sphereMax.x = (float)(center.x + radius);
		sphereMax.y = (float)(center.y + radius);
		sphereMax.z = (float)(center.z + radius);
		sphereMax.w = (float)radius;
		sphereMin.x = (float)(center.x - radius);
		sphereMin.y = (float)(center.y - radius);
		sphereMin.z = (float)(center.z - radius);
		hkX87Real sphereMinW = -radius;
		if (!(aabb.m_min.x > sphereMin.x)) aabb.m_min.x = sphereMin.x;
		if (!(aabb.m_min.y > sphereMin.y)) aabb.m_min.y = sphereMin.y;
		if (!(aabb.m_min.z > sphereMin.z)) aabb.m_min.z = sphereMin.z;
		if (!(aabb.m_min.w > sphereMinW)) aabb.m_min.w = (float)sphereMinW;
		if (!(aabb.m_max.x < sphereMax.x)) aabb.m_max.x = sphereMax.x;
		if (!(aabb.m_max.y < sphereMax.y)) aabb.m_max.y = sphereMax.y;
		if (!(aabb.m_max.z < sphereMax.z)) aabb.m_max.z = sphereMax.z;
		if (!(aabb.m_max.w < sphereMax.w)) aabb.m_max.w = sphereMax.w;

		diag.x = aabb.m_max.x - aabb.m_min.x;
		diag.y = aabb.m_max.y - aabb.m_min.y;
		diag.z = aabb.m_max.z - aabb.m_min.z;
		diag.w = aabb.m_max.w - aabb.m_min.w;

		// linear motion of A's center caused by B's rotation
		if (msB->m_deltaAngle.w > 0.0f)
		{
			// X87-PRECISION: d, cz and f stay on the FPU stack; cx and cy are stored to float slots.
			hkX87Real dx = (hkX87Real)center.x - msB->m_sweptTransform.m_centerOfMassLocal.x;
			hkX87Real dy = (hkX87Real)center.y - msB->m_sweptTransform.m_centerOfMassLocal.y;
			hkX87Real dz = (hkX87Real)center.z - msB->m_sweptTransform.m_centerOfMassLocal.z;
			const hkVector4& w = msB->m_deltaAngle;
			float cx = (float)(dy * w.z - dz * w.y);
			float cy = (float)(dz * w.x - dx * w.z);
			hkX87Real cz = dx * w.y - dy * w.x;
			hkX87Real f = (hkX87Real)msB->m_sweptTransform.m_centerOfMass1.w * ((const hkStepInfoView*)input.m_stepInfo)->m_deltaTime;
			linearMotion.x = (float)(cx * f + linearMotion.x);
			linearMotion.y = (float)(cy * f + linearMotion.y);
			linearMotion.z = (float)(f * cz + linearMotion.z);
			linearMotion.w = (float)(f * 0.0f);
		}

		// sweep the aabb along the linear motion
		float minX = (0.0f < linearMotion.x) ? 0.0f : linearMotion.x;
		float minY = (0.0f < linearMotion.y) ? 0.0f : linearMotion.y;
		float minZ = (0.0f < linearMotion.z) ? 0.0f : linearMotion.z;
		float minW = (0.0f < linearMotion.w) ? 0.0f : linearMotion.w;
		float maxX = (0.0f > linearMotion.x) ? 0.0f : linearMotion.x;
		float maxY = (0.0f > linearMotion.y) ? 0.0f : linearMotion.y;
		float maxZ = (0.0f > linearMotion.z) ? 0.0f : linearMotion.z;
		float maxW = (0.0f > linearMotion.w) ? 0.0f : linearMotion.w;
		aabb.m_min.x = minX + aabb.m_min.x;
		aabb.m_min.y = minY + aabb.m_min.y;
		aabb.m_min.z = minZ + aabb.m_min.z;
		aabb.m_min.w = minW + aabb.m_min.w;
		aabb.m_max.x = maxX + aabb.m_max.x;
		aabb.m_max.y = maxY + aabb.m_max.y;
		aabb.m_max.z = maxZ + aabb.m_max.z;
		aabb.m_max.w = maxW + aabb.m_max.w;
	}

	if (cachedAabb)
	{
		// hkAabb::contains: (cached.min <= aabb.min) & (aabb.max <= cached.max), xyz all set (masks X=8 Y=4 Z=2 W=1)
		int minMask = ((cachedAabb->m_min.x <= aabb.m_min.x) << 3) | ((cachedAabb->m_min.y <= aabb.m_min.y) << 2) |
		              ((cachedAabb->m_min.z <= aabb.m_min.z) << 1) | (cachedAabb->m_min.w <= aabb.m_min.w);
		int maxMask = ((aabb.m_max.x <= cachedAabb->m_max.x) << 3) | ((aabb.m_max.y <= cachedAabb->m_max.y) << 2) |
		              ((aabb.m_max.z <= cachedAabb->m_max.z) << 1) | (aabb.m_max.w <= cachedAabb->m_max.w);
		if ((minMask & maxMask & 0xe) == 0xe)
			goto queryDone;

		// grow the aabb by the tolerance and against the motion (at most 0.4 of its extent) and cache it
		float minMx = (0.0f < linearMotion.x) ? 0.0f : linearMotion.x;
		float minMy = (0.0f < linearMotion.y) ? 0.0f : linearMotion.y;
		float minMz = (0.0f < linearMotion.z) ? 0.0f : linearMotion.z;
		float minMw = (0.0f < linearMotion.w) ? 0.0f : linearMotion.w;
		float maxMx = (0.0f > linearMotion.x) ? 0.0f : linearMotion.x;
		float maxMy = (0.0f > linearMotion.y) ? 0.0f : linearMotion.y;
		float maxMz = (0.0f > linearMotion.z) ? 0.0f : linearMotion.z;
		float maxMw = (0.0f > linearMotion.w) ? 0.0f : linearMotion.w;

		float halfTolerance = input.m_tolerance * 0.5f;
		aabb.m_min.x = aabb.m_min.x - halfTolerance;
		aabb.m_min.y = aabb.m_min.y - halfTolerance;
		aabb.m_min.z = aabb.m_min.z - halfTolerance;
		aabb.m_min.w = aabb.m_min.w - halfTolerance;
		aabb.m_max.x = aabb.m_max.x + halfTolerance;
		aabb.m_max.y = aabb.m_max.y + halfTolerance;
		aabb.m_max.z = aabb.m_max.z + halfTolerance;
		aabb.m_max.w = halfTolerance + aabb.m_max.w;

		hkVector4 growMin, growMax, limit;
		growMin.x = maxMx * -2.0f;
		growMin.y = maxMy * -2.0f;
		growMin.z = maxMz * -2.0f;
		growMin.w = maxMw * -2.0f;
		growMax.x = minMx * -2.0f;
		growMax.y = minMy * -2.0f;
		growMax.z = minMz * -2.0f;
		growMax.w = minMw * -2.0f;
		limit.x = diag.x * 0.4f;
		limit.y = diag.y * 0.4f;
		limit.z = diag.z * 0.4f;
		limit.w = diag.w * 0.4f;
		if (!(growMax.x < limit.x)) growMax.x = limit.x;
		if (!(growMax.y < limit.y)) growMax.y = limit.y;
		if (!(growMax.z < limit.z)) growMax.z = limit.z;
		if (!(growMax.w < limit.w)) growMax.w = limit.w;
		float negLimitX = -limit.x;
		float negLimitY = -limit.y;
		float negLimitZ = -limit.z;
		float negLimitW = -limit.w;
		if (!(growMin.x > negLimitX)) growMin.x = negLimitX;
		if (!(growMin.y > negLimitY)) growMin.y = negLimitY;
		if (!(growMin.z > negLimitZ)) growMin.z = negLimitZ;
		if (!(growMin.w > negLimitW)) growMin.w = negLimitW;

		aabb.m_min.x = growMin.x + aabb.m_min.x;  cachedAabb->m_min.x = aabb.m_min.x;
		aabb.m_min.y = growMin.y + aabb.m_min.y;  cachedAabb->m_min.y = aabb.m_min.y;
		aabb.m_min.z = growMin.z + aabb.m_min.z;  cachedAabb->m_min.z = aabb.m_min.z;
		aabb.m_min.w = growMin.w + aabb.m_min.w;  cachedAabb->m_min.w = aabb.m_min.w;
		aabb.m_max.x = growMax.x + aabb.m_max.x;  cachedAabb->m_max.x = aabb.m_max.x;
		aabb.m_max.y = growMax.y + aabb.m_max.y;  cachedAabb->m_max.y = aabb.m_max.y;
		aabb.m_max.z = growMax.z + aabb.m_max.z;  cachedAabb->m_max.z = aabb.m_max.z;
		aabb.m_max.w = growMax.w + aabb.m_max.w;  cachedAabb->m_max.w = aabb.m_max.w;
	}

	{
		((const hkBvTreeShapeQuery*)bodyB.m_shape)->queryAabb(aabb, hitList);

		const hkShapeCollection* collection = ((const hkBvTreeShapeQuery*)bodyB.m_shape)->m_shapeCollection;
		hkCdBody childBody;
		childBody.m_parent = &bodyB;
		childBody.m_motion = bodyB.m_motion;
		hkShapeBufferStorage shapeBuffer;

		if (g_hkBvTreeAgentUpdateKeysInPlace)
		{
			hkContactMgr* mgr = m_contactMgr;
			hkArray<hkBvAgentEntryInfo>& partners = m_collisionPartners;
			hkShapeKey* hitBegin = hitList.m_data;
			hkShapeKey* hitEnd = hitList.m_data + hitList.m_size;

			// remove the partners whose key is no longer hit
			{
				hkBvAgentEntryInfo* partnerEnd = partners.m_data + partners.m_size;
				hkShapeKey* hit = hitBegin;
				for (hkBvAgentEntryInfo* partner = partners.m_data; partner != partnerEnd; partner++)
				{
					if (hit != hitEnd && partner->m_key == *hit)
					{
						hit++;
						continue;
					}
					for (hit = hitBegin; hit != hitEnd; hit++)
					{
						if (partner->m_key == *hit)
							break;
					}
					if (hit != hitEnd)
					{
						hit++;
						continue;
					}
					partner->m_collisionAgent->cleanup();
					// removeAtAndCopy
					partners.m_size--;
					for (int i = int(partner - partners.m_data); i < partners.m_size; i++)
						partners.m_data[i] = partners.m_data[i + 1];
					partner--;
					partnerEnd--;
				}
			}

			// insert the new keys
			if (hitList.m_size != partners.m_size)
			{
				hkBvAgentEntryInfo* partner = partners.m_data;
				hkBvAgentEntryInfo* partnerEnd = partners.m_data + partners.m_size;
				for (hkShapeKey* hit = hitBegin; hit != hitEnd; hit++, partner++)
				{
					if (partner != partnerEnd && partner->m_key == *hit)
						continue;

					// insertAt(hit index)
					int index = int(hit - hitBegin);
					int size = partners.m_size;
					int newSize = size + 1;
					int numToMove = size - index;
					if ((partners.m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) < newSize)
					{
						int cap = (partners.m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) * 2;
						hkArrayUtil::_reserveExactly(&partners, (newSize < cap) ? cap : newSize, (int)sizeof(hkBvAgentEntryInfo));
					}
					partner = partners.m_data + index;
					for (int i = numToMove - 1; i >= 0; i--)
						partner[i + 1] = partner[i];
					partners.m_size = newSize;

					partner->m_collisionAgent = createPartnerAgent(bodyA, bodyB, input, collection, *hit, childBody, shapeBuffer, mgr);
					partner->m_key = *hit;
					partnerEnd = partners.m_data + partners.m_size;
				}
			}
		}		else
		{
			// sort the hits and merge them with the (sorted) partner list
			if (hitList.m_size > 1)
				hkAlgorithm::quickSortRecursive(hitList.m_data, 0, hitList.m_size - 1, hkAlgorithm::less<hkShapeKey>());

			hkContactMgr* mgr = m_contactMgr;
			hkBvAgentEntryInfo* partner = m_collisionPartners.m_data;
			hkBvAgentEntryInfo* partnerEnd = partner + m_collisionPartners.m_size;
			hkShapeKey* hit = hitList.m_data;
			hkShapeKey* hitEnd = hitList.m_data + hitList.m_size;

			hkLocalArray<hkBvAgentEntryInfo> newPartners(hitList.m_size);
			newPartners.setSize(hitList.m_size);
			hkBvAgentEntryInfo* out = newPartners.m_data;

			while (partner != partnerEnd)
			{
				if (hit == hitEnd)
				{
					for (; partner != partnerEnd; partner++)
					{
						if (partner->m_collisionAgent)
							partner->m_collisionAgent->cleanup();
					}
					break;
				}
				if (*hit == partner->m_key)
				{
					*out = *partner;
					out++;
					partner++;
					hit++;
				}
				else if (*hit < partner->m_key)
				{
					out->m_collisionAgent = createPartnerAgent(bodyA, bodyB, input, collection, *hit, childBody, shapeBuffer, mgr);
					out->m_key = *hit;
					out++;
					hit++;
				}
				else
				{
					if (partner->m_collisionAgent)
						partner->m_collisionAgent->cleanup();
					partner++;
				}
			}
			for (; hit != hitEnd; hit++)
			{
				out->m_collisionAgent = createPartnerAgent(bodyA, bodyB, input, collection, *hit, childBody, shapeBuffer, mgr);
				out->m_key = *hit;
				out++;
			}

			// m_collisionPartners = newPartners
			int n = newPartners.m_size;
			if ((m_collisionPartners.m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) < n)
			{
				if (m_collisionPartners.m_capacityAndFlags >= 0)
					hkThreadMemoryInstance().deallocateChunk(m_collisionPartners.m_data,
						(m_collisionPartners.m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) * (int)sizeof(hkBvAgentEntryInfo), HK_MEMORY_CLASS_ARRAY);
				m_collisionPartners.m_data = (hkBvAgentEntryInfo*)hkThreadMemoryInstance().allocateChunk(n * (int)sizeof(hkBvAgentEntryInfo), HK_MEMORY_CLASS_ARRAY);
				m_collisionPartners.m_capacityAndFlags = (m_collisionPartners.m_capacityAndFlags & 0x40000000) | n;
			}
			m_collisionPartners.m_size = n;
			hkBvAgentEntryInfo* dst = m_collisionPartners.m_data;
			const hkBvAgentEntryInfo* src = newPartners.m_data;
			for (int i = n; i > 0; i--)
				*dst++ = *src++;
		}

	}

queryDone:
	if (hitList.m_capacityAndFlags >= 0)
		hkThreadMemoryInstance().deallocateChunk(hitList.m_data, (hitList.m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) * (int)sizeof(hkShapeKey), HK_MEMORY_CLASS_ARRAY);

	// narrow phase on every partner
	{
		hkBvAgentEntryInfo* partner = m_collisionPartners.m_data;
		hkBvAgentEntryInfo* partnerEnd = partner + m_collisionPartners.m_size;
		hkCdBody childBody;
		childBody.m_parent = &bodyB;
		childBody.m_motion = bodyB.m_motion;
		HK_TIMER_COMMAND("StNarrowPhase");
		const hkShapeCollection* collection = ((const hkBvTreeShapeQuery*)bodyB.m_shape)->m_shapeCollection;
		for (; partner != partnerEnd; partner++)
		{
			hkShapeBufferStorage shapeBuffer;
			childBody.m_shape = collection->getChildShape(partner->m_key, (hkShapeBuffer*)&shapeBuffer);
			childBody.m_shapeKey = partner->m_key;
			partner->m_collisionAgent->processCollision(bodyA, childBody, input, output);
		}
	}
	HK_TIMER_COMMAND(hkMonitorTimerListEndTag);
}
