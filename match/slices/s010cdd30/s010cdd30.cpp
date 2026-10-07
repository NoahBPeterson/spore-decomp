// @ 0x010CDD30  hkBvTreeStreamAgent::processCollision (Havok 3.1.0, profiler list "LtBvTree3" / "QueryTree" / "StNarrow")
//
// 1. Builds the agent3 process input: the two bodies, the input, the contact manager, aTb = inverse(A) * B and the
//    TIM info (hkSweptTransformUtil::calcTimInfo: relative linear motion of both bodies scaled to this step, w = the
//    angular sweep radius of both).
// 2. (inlined prepareCollisionPartnersProcess) bTa = inverse(aTb); the linear TIM is rotated into B's space; the aabb
//    of A in B's space is computed (with continuous physics: grown by the angular sweep, clipped to the sphere around
//    A's end position, and swept by the relative motion incl. B's rotation).  If the cached aabb (m_cachedAabb) still
//    contains it, the tree query is skipped; otherwise the aabb is grown by the tolerance and the motion (clamped to
//    0.4 of its extent), cached and the BV tree is queried.  The hit list starts with HK_INVALID_SHAPE_KEY, which
//    sorts to the end and terminates the key list.
// 3. Narrow phase through the agent1n machine: with the cached result (no key list), or after a memory check
//    (hkMemory critical limit vs. one 512-byte sector per 4 keys; on failure the memory state is set to
//    out-of-memory and the function returns without the timer end tag) with the sorted key list.
//
// Complete source; the aabb computation follows hkBvTreeAgent::processCollision (s010e3430).  Not byte-exact.
#include "../s010e1340/hk31_agents.h"

typedef unsigned int hkShapeKey;
#define HK_INVALID_SHAPE_KEY 0xffffffffu

extern const char hkMonitorTimerListEndTag[];       // "lt" at 0x0143CD94

// ---- profiler list begin (0x10-byte command) -------------------------------------------------------------------
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

// ---- thread memory (only deallocateChunk is used here) ---------------------------------------------------------
class hkThreadMemoryView
{
public:
	void deallocateChunk(void* p, int nbytes, int cl);                  // 0x0107DB10
};
static inline hkThreadMemoryView& hkThreadMemoryInstance() { return *(hkThreadMemoryView*)hkTlsGet(g_hkThreadMemoryTls); }

// ---- hkMemory statistics (dev PDB: m_memoryState +4, m_criticalMemoryLimit +8, m_memoryStatistics +0x10) --------
struct hkMemoryStatisticsView
{
	int m_numSysAllocs, m_sysAllocsSize, m_sysAllocsHighMark, m_numPages, m_sizeOfPage, m_pageOverhead, m_pageMemoryUsed;
};
struct hkMemoryView
{
	enum MemoryState { MEMORY_STATE_OK = 0, MEMORY_STATE_OUT_OF_MEMORY = 1 };
	void* m_vtable;
	int m_memoryState;                         // +4
	int m_criticalMemoryLimit;                 // +8
	int m_referenceCount;                      // +0xc
	hkMemoryStatisticsView m_memoryStatistics; // +0x10

	int getAvailableMemory() const
	{
		int used = m_memoryStatistics.m_pageMemoryUsed + m_memoryStatistics.m_sysAllocsSize;
		return (m_criticalMemoryLimit > used) ? m_criticalMemoryLimit - used : 0;
	}
};
static inline hkMemoryView& hkMemoryInstance() { return *(hkMemoryView*)hkMemory::s_instance; }

// ---- transforms ------------------------------------------------------------------------------------------------
struct hkTransformInv : hkTransform
{
	void setInverse(const hkTransform& t);     // 0x01080E70
};

// ---- agent3 / agent1n ------------------------------------------------------------------------------------------
struct hkAgent3ProcessInput                    // 0x70 bytes (dev PDB)
{
	const hkCdBody* m_bodyA;                   // +0
	const hkCdBody* m_bodyB;                   // +4
	const hkProcessCollisionInput* m_input;    // +8
	hkContactMgr* m_contactMgr;                // +0xc
	hkTransform m_aTb;                         // +0x10
	float m_distAtT1;                          // +0x50
	hkVector4 m_linearTimInfo;                 // +0x60
};
struct hkAgent1nTrack
{
	hkArray<void*> m_sectors;                  // +0 (size at +4)
};
extern "C" void hkAgent1nMachine_Process(hkAgent1nTrack& track, hkAgent3ProcessInput& input, const hkShapeCollection* container,
                                         const hkShapeKey* hitList, int numHits, hkProcessCollisionOutput& output);   // 0x011048D0
#define HK_AGENT3_SECTOR_SIZE 512

// ---- shapes / quality info -------------------------------------------------------------------------------------
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

// ---- the agent ---------------------------------------------------------------------------------------------------
class hkBvTreeStreamAgent : public hkCollisionAgent
{
public:
	virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkProcessCollisionInput& input, hkProcessCollisionOutput& output);

	hkCollisionDispatcher* m_dispatcher;      // +0xc
	hkAabb m_cachedAabb;                      // +0x10
	hkAgent1nTrack m_agentTrack;              // +0x30
};

// (z * r.z + y * r.y) + x * r.x per column: the operation order of the inlined hkVector4::setRotatedInverseDir.
static inline void rotateInverse(hkVector4& out, const hkTransform& t, hkX87Real x, hkX87Real y, hkX87Real z)
{
	out.x = (z * t.m_rot[0].z + y * t.m_rot[0].y) + x * t.m_rot[0].x;
	out.y = (z * t.m_rot[1].z + y * t.m_rot[1].y) + x * t.m_rot[1].x;
	out.z = (z * t.m_rot[2].z + y * t.m_rot[2].y) + x * t.m_rot[2].x;
}

// hkSweptTransformUtil::calcTimInfo
static __forceinline void calcTimInfo(const hkMotionState& ms0, const hkMotionState& ms1, float deltaTime, hkVector4& timOut)
{
	const hkMotionState::hkSweptTransform& st0 = ms0.m_sweptTransform;
	const hkMotionState::hkSweptTransform& st1 = ms1.m_sweptTransform;
	hkVector4 diff0;
	diff0.x = st0.m_centerOfMass0.x - st0.m_centerOfMass1.x;
	diff0.y = st0.m_centerOfMass0.y - st0.m_centerOfMass1.y;
	diff0.z = st0.m_centerOfMass0.z - st0.m_centerOfMass1.z;
	diff0.w = st0.m_centerOfMass0.w - st0.m_centerOfMass1.w;
	hkVector4 diff1;
	diff1.x = st1.m_centerOfMass1.x - st1.m_centerOfMass0.x;
	diff1.y = st1.m_centerOfMass1.y - st1.m_centerOfMass0.y;
	diff1.z = st1.m_centerOfMass1.z - st1.m_centerOfMass0.z;
	diff1.w = st1.m_centerOfMass1.w - st1.m_centerOfMass0.w;
	float f0 = deltaTime * st0.m_centerOfMass1.w;          // m_centerOfMass1.w = inverse delta time
	float f1 = deltaTime * st1.m_centerOfMass1.w;
	timOut.x = diff0.x * f0;
	timOut.y = diff0.y * f0;
	timOut.z = diff0.z * f0;
	timOut.w = diff0.w * f0;
	timOut.x = diff1.x * f1 + timOut.x;
	timOut.y = diff1.y * f1 + timOut.y;
	timOut.z = diff1.z * f1 + timOut.z;
	timOut.w = diff1.w * f1 + timOut.w;
	timOut.w = ms1.m_objectRadius * ms1.m_deltaAngle.w * f1 + ms0.m_objectRadius * ms0.m_deltaAngle.w * f0;
}

// ---------------------------------------------------------------------------------------------------------------
void hkBvTreeStreamAgent::processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                           const hkProcessCollisionInput& input, hkProcessCollisionOutput& output)
{
	hkTimerBeginList("LtBvTree3", "QueryTree");

	hkAgent3ProcessInput in3;
	{
		in3.m_bodyA = &bodyA;
		in3.m_bodyB = &bodyB;
		in3.m_input = &input;
		in3.m_contactMgr = m_contactMgr;
		const hkMotionState* msA = (const hkMotionState*)bodyA.m_motion;
		const hkMotionState* msB = (const hkMotionState*)bodyB.m_motion;
		calcTimInfo(*msA, *msB, ((const hkStepInfoView*)input.m_stepInfo)->m_deltaTime, in3.m_linearTimInfo);
		in3.m_aTb.setMulInverseMul(msA->m_transform, msB->m_transform);
	}

	hkInplaceArray<hkShapeKey, 128> hitList;
	hitList.m_data = hitList.m_storage;
	hitList.m_size = 0;
	hitList.m_capacityAndFlags = (int)0x80000080;
	hitList.m_data[hitList.m_size++] = HK_INVALID_SHAPE_KEY;      // terminator (sorts to the end)

	hkBool queryDone = false;
	// ---- prepareCollisionPartnersProcess ----
	{
		hkTransformInv bTa;
		bTa.setInverse(in3.m_aTb);

		const hkMotionState* msA = (const hkMotionState*)bodyA.m_motion;
		const hkMotionState* msB = (const hkMotionState*)bodyB.m_motion;

		// linear TIM in B's space (w = 0)
		hkVector4 linearMotion;
		linearMotion.w = 0.0f;
		rotateInverse(linearMotion, msB->m_transform, in3.m_linearTimInfo.x, in3.m_linearTimInfo.y, in3.m_linearTimInfo.z);

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
			// X87-PRECISION: the radius and the differences fed to the rotation stay on the FPU stack.
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

		hkAabb* cachedAabb = &m_cachedAabb;
		if (cachedAabb)
		{
			// hkAabb::contains: (cached.min <= aabb.min) & (aabb.max <= cached.max), xyz all set (masks X=8 Y=4 Z=2 W=1)
			int minMask = ((cachedAabb->m_min.x <= aabb.m_min.x) << 3) | ((cachedAabb->m_min.y <= aabb.m_min.y) << 2) |
			              ((cachedAabb->m_min.z <= aabb.m_min.z) << 1) | (cachedAabb->m_min.w <= aabb.m_min.w);
			int maxMask = ((aabb.m_max.x <= cachedAabb->m_max.x) << 3) | ((aabb.m_max.y <= cachedAabb->m_max.y) << 2) |
			              ((aabb.m_max.z <= cachedAabb->m_max.z) << 1) | (aabb.m_max.w <= cachedAabb->m_max.w);
			if ((minMask & maxMask & 0xe) == 0xe)
			{
				queryDone = true;
				goto narrowPhase;
			}

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
			aabb.m_max.w = aabb.m_max.w + halfTolerance;

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

		((const hkBvTreeShapeQuery*)bodyB.m_shape)->queryAabb(aabb, hitList);
	}

narrowPhase:
	HK_TIMER_COMMAND("StNarrow");
	{
		const hkShapeKey* keys;
		int numKeys;
		if (queryDone)
		{
			keys = 0;
			numKeys = 0;
		}
		else
		{
			// one new 512-byte sector per 4 keys must fit under the critical memory limit
			hkMemoryView& memory = hkMemoryInstance();
			int needed = ((hitList.m_size / 4 - m_agentTrack.m_sectors.m_size) + 1) * HK_AGENT3_SECTOR_SIZE;
			if (needed > memory.getAvailableMemory())
			{
				memory.m_memoryState = hkMemoryView::MEMORY_STATE_OUT_OF_MEMORY;
				goto done;
			}
			if (hitList.m_size > 1)
				hkAlgorithm::quickSortRecursive(hitList.m_data, 0, hitList.m_size - 1, hkAlgorithm::less<hkShapeKey>());
			keys = hitList.m_data;
			numKeys = hitList.m_size;
		}
		hkAgent1nMachine_Process(m_agentTrack, in3, ((const hkBvTreeShapeQuery*)bodyB.m_shape)->m_shapeCollection, keys, numKeys, output);
	}
	HK_TIMER_COMMAND(hkMonitorTimerListEndTag);

done:
	if (hitList.m_capacityAndFlags >= 0)
		hkThreadMemoryInstance().deallocateChunk(hitList.m_data, (hitList.m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) * (int)sizeof(hkShapeKey), HK_MEMORY_CLASS_ARRAY);
}
