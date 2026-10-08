// @ 0x010E2BE0  hkBvTreeAgent::prepareCollisionPartnersLinearCast(bodyA, bodyB, linearCastInput)   (Havok 3.1.0, thiscall, ret 0xC)
// Like prepareCollisionPartners, but the aabb comes from calcAabbLinearCast and is always cached (no early-out and no
// memory-limit check); the hits are sorted before the in-place/merge partner update.
#include "../s010e1340/hk31_agents.h"

typedef unsigned int hkShapeKey;

extern unsigned long g_hkThreadMemoryTls;           // 0x016e4174
hkCollisionAgent* hkNullAgent_getNullAgent();       // 0x010cd8d0

extern hkBool g_hkBvTreeAgentUpdateKeysInPlace;     // 0x016E58F9

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

// The global memory manager (0x016E4178); only the fields used for the "enough memory left" test are named.
struct hkMemoryView
{
	void* m_vtable;
	int m_memoryOverflow;     // +4
	int m_softLimit;          // +8
	int m_pad0c[2];
	int m_allocatedA;         // +0x14
	int m_pad18[4];
	int m_allocatedB;         // +0x28
};

extern hkMemoryView* g_hkMemoryInstance;           // 0x016E4178

class hkBvTreeShapeQuery : public hkShape
{
public:
	virtual void bvTreeSlot7();
	virtual void bvTreeSlot8();
	virtual void queryAabb(const hkAabb& aabb, hkArray<hkShapeKey>& hits) const = 0;     // 9 (+0x24)
	hkShapeCollection* m_shapeCollection;                                                  // +0xc
};

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


// prepareCollisionPartnersLinearCast is not declared in the shared header; a trivial derived class carries the member.
class hkBvTreeAgentPrepare : public hkBvTreeAgent
{
public:
	void prepareCollisionPartnersLinearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input);
};

// @ 0x010E2BE0
void hkBvTreeAgentPrepare::prepareCollisionPartnersLinearCast(const hkCdBody& bodyA, const hkCdBody& bodyB, const hkLinearCastCollisionInput& input)
{
	hkAabb aabb;
	calcAabbLinearCast(bodyA, bodyB, input, aabb);
	{
		hkAabb& c = m_cachedAabb;
		c.m_min.x = aabb.m_min.x; c.m_min.y = aabb.m_min.y; c.m_min.z = aabb.m_min.z;
		c.m_max.x = aabb.m_max.x; c.m_max.y = aabb.m_max.y; c.m_max.z = aabb.m_max.z;
		c.m_max.w = aabb.m_max.w; c.m_min.w = aabb.m_min.w;
	}

	hkInplaceArray<hkShapeKey, 128> hitList;
	hitList.m_data = hitList.m_storage;
	hitList.m_size = 0;
	hitList.m_capacityAndFlags = (int)0x80000080;
	((const hkBvTreeShapeQuery*)bodyB.m_shape)->queryAabb(aabb, hitList);

	if (hitList.m_size > 1)
		hkAlgorithm::quickSortRecursive(hitList.m_data, 0, hitList.m_size - 1, hkAlgorithm::less<hkShapeKey>());

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
	}
	else
	{
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

	if (hitList.m_capacityAndFlags >= 0)
		hkThreadMemoryInstance().deallocateChunk(hitList.m_data, (hitList.m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) * (int)sizeof(hkShapeKey), HK_MEMORY_CLASS_ARRAY);
}
