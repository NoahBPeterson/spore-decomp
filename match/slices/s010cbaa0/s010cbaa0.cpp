// Havok 3.1.0 slice s010cbaa0: hkBvShape, MOPP tolerance requirements + buildCode, ray-hit collectors,
// hkWorldRayCaster, hkTypedBroadPhaseDispatcher, hkWorldLinearCaster, hkNullAgent3::create.
// Equivalent portable source (not byte-exact). Operation order of the x87 math is taken from the disassembly.
#include "../s010cbaa0/hk31_b005.h"
#include <math.h>
#include <string.h>

// ---------------------------------------------------------------------------------------------------------
// hkBvShape
// ---------------------------------------------------------------------------------------------------------
class hkBvShape : public hkShape
{
public:
	virtual ~hkBvShape();                                                                    // 0 (deleting dtor 0x010CBB00)
	virtual void calcStatistics(hkStatisticsCollector* c) const;                              // 1 (0x010CBAA0)
	virtual int getType() const;                                                              // 2 (0x010CBA90)
	virtual void getAabb(const hkTransform& localToWorld, float tolerance, hkAabb& out) const;// 3 (0x010CBA80)
	virtual float getMaximumProjection(const hkVector4& direction) const;                     // 4 (0x010C3510, hkShape's)
	virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const;                 // 5
	virtual void castRayWithCollector(const hkShapeRayCastInput& input, const hkCdBody& cdBody,
	                                  hkRayHitCollector& collector) const;                                       // 6

	hkShape* m_boundingVolumeShape;   // +0x0c
	hkShape* m_childShape;            // +0x10
};

// @ 0x010cbaa0
void hkBvShape::calcStatistics(hkStatisticsCollector* c) const
{
	c->beginObject("BvShape", 1, this);
	c->addReferencedObject("Child", 1, m_childShape);
	c->endObject();
}

// @ 0x010cbb30
hkBvShape::~hkBvShape()
{
	// member release order as in the binary: child (+0x10) first, then the bounding volume (+0x0c)
	m_childShape->removeReference();
	m_boundingVolumeShape->removeReference();
}

// @ 0x010cbb80
hkBool hkBvShape::castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const
{
	HK_TIMER_BEGIN("TtrcBvShape");
	hkBool result = m_childShape->castRay(input, output);
	HK_TIMER_END();
	return result;
}

// @ 0x010cbc60
void hkBvShape::castRayWithCollector(const hkShapeRayCastInput& input, const hkCdBody& cdBody, hkRayHitCollector& collector) const
{
	HK_TIMER_BEGIN("TtrcBvShape");
	hkCdBody childBody;
	childBody.m_shape = m_childShape;
	childBody.m_shapeKey = cdBody.m_shapeKey;
	childBody.m_motion = cdBody.m_motion;
	childBody.m_parent = &cdBody;
	m_childShape->castRayWithCollector(input, childBody, collector);
	HK_TIMER_END();
}

// ---------------------------------------------------------------------------------------------------------
// MOPP: hkMoppFitToleranceRequirements and hkMoppUtility::buildCode
// ---------------------------------------------------------------------------------------------------------
class hkShapeCollection;
class hkMoppCode;

class hkMoppFitToleranceRequirements : public hkReferencedObject    // vtable 0x014A4248 (slot 0 = 0x010DD550, slot 1 empty)
{
public:
	hkMoppFitToleranceRequirements();
	void getAbsoluteFitToleranceOfAxisAlignedTriangles(hkVector4& out) const;
	float getRelativeFitToleranceOfInternalNodes() const { return m_relativeFitToleranceOfInternalNodes; }   // 0x00C06330
	float getAbsoluteFitToleranceOfInternalNodes() const { return m_absoluteFitToleranceOfInternalNodes; }   // 0x00FD9440
	float getAbsoluteFitToleranceOfTriangles() const { return m_absoluteFitToleranceOfTriangles; }           // 0x00E28A00

	hkVector4 m_absoluteFitToleranceOfAxisAlignedTriangles;   // +0x10
	float m_relativeFitToleranceOfInternalNodes;              // +0x20
	float m_absoluteFitToleranceOfInternalNodes;              // +0x24
	float m_absoluteFitToleranceOfTriangles;                  // +0x28
	hkBool m_useShapeKeys;                                    // +0x2c
	hkBool m_enablePrimitiveSplitting;                        // +0x2d
};

// @ 0x010cbf00
hkMoppFitToleranceRequirements::hkMoppFitToleranceRequirements()
	: m_useShapeKeys(true), m_enablePrimitiveSplitting(true)
{
	m_absoluteFitToleranceOfTriangles = 0.3f;                 // 0x3e99999a
	m_relativeFitToleranceOfInternalNodes = 0.4f;             // 0x3ecccccd
	m_absoluteFitToleranceOfInternalNodes = 0.1f;             // 0x3dcccccd
	m_absoluteFitToleranceOfAxisAlignedTriangles.x = 0.05f;   // 0x3d4ccccd
	m_absoluteFitToleranceOfAxisAlignedTriangles.y = 0.05f;
	m_absoluteFitToleranceOfAxisAlignedTriangles.z = 0.05f;
	m_absoluteFitToleranceOfAxisAlignedTriangles.w = 0.0f;
}

// @ 0x010cbed0
void hkMoppFitToleranceRequirements::getAbsoluteFitToleranceOfAxisAlignedTriangles(hkVector4& out) const
{
	// raw dword copies in the binary (no x87 load/store), so use a bit copy
	memcpy(&out, &m_absoluteFitToleranceOfAxisAlignedTriangles, sizeof(hkVector4));
}

// The MOPP compiler objects used by buildCode live in code outside this slice (0x01103xxx). Their roles are
// inferred from the member offsets and the call order; the names are descriptive, not recovered symbols.
struct hkMoppSplitParams { uint32_t m_v[5]; };                      // 0x14 bytes, set by 0x011037E0 / copied by 0x01103590
struct hkMoppCostParams { float m_v[6]; };                          // 0x18 bytes, initialised by 0x01103830 (five 1.0f and 0.5f)
struct hkMoppAssemblerParams
{
	float m_relativeFitToleranceOfInternalNodes;     // +0
	float m_absoluteFitToleranceOfInternalNodes;     // +4
	float m_absoluteFitToleranceOfTriangles;         // +8
	uint32_t m_unused0c;                             // +0xc (never copied by 0x011037A0)
	hkVector4 m_absoluteFitToleranceOfAxisAlignedTriangles;   // +0x10
	int m_mode;                                      // +0x20
};
// Stack object with vtable 0x014A5DEC: wraps the shape collection.
class hkMoppShapeCollectionInterface : public hkReferencedObject
{
public:
	explicit hkMoppShapeCollectionInterface(const hkShapeCollection* c);   // 0x01103330
	~hkMoppShapeCollectionInterface() { m_shapeCollection = 0; }            // 0x01103360 (vptr reset + clear)
	virtual int getNumPrimitives() const;                                    // slot 2 (0x00FC7E50)
	virtual void slot3();                                                    // 0x011032C0
	const hkShapeCollection* m_shapeCollection;   // +8
	int m_numChildShapes;                         // +0xc
};
struct hkMoppCompilerState                         // 0x54 bytes in the 32-bit binary
{
	uint32_t m_unk00;
	hkMoppSplitParams m_split;                    // +0x04
	hkMoppCostParams m_cost;                      // +0x18
	hkMoppAssemblerParams m_assembler;            // +0x30 (0x24 bytes)
	explicit hkMoppCompilerState(int mode);                                          // 0x01103610
	~hkMoppCompilerState();                                                          // 0x00C2E4E0 (empty, shared with other no-op dtors)
	void setSplitParams(const hkMoppSplitParams& p);                                 // 0x01103590
	void setCostParams(const hkMoppCostParams& p);                                   // 0x011035C0
	void setAssemblerParams(const hkMoppAssemblerParams& p);                         // 0x011037A0
	int calcBufferSize(const hkMoppShapeCollectionInterface& i) const;               // 0x011035F0
	hkMoppCode* build(const hkMoppShapeCollectionInterface& i, void* buffer, int bufferSize);   // 0x01103670
};
void hkMoppCostParams_init(hkMoppCostParams* p, int);                // 0x01103830 (this in ECX, one ignored stack arg)
void hkMoppSplitParams_init(hkMoppSplitParams* p, int mode);         // 0x011037E0

class hkMoppUtility
{
public:
	static hkMoppCode* buildCode(const hkShapeCollection* shapeCollection, const hkMoppFitToleranceRequirements& mfr);
};

// @ 0x010cbd40
hkMoppCode* hkMoppUtility::buildCode(const hkShapeCollection* shapeCollection, const hkMoppFitToleranceRequirements& mfr)
{
	hkMoppShapeCollectionInterface collectionInterface(shapeCollection);
	hkMoppCompilerState compiler(0);

	hkMoppCostParams cost;
	hkMoppCostParams_init(&cost, 0);
	cost.m_v[0] = 1.0f;
	if (!mfr.m_useShapeKeys)
		cost.m_v[4] = 0.0f;
	compiler.setCostParams(cost);

	hkMoppAssemblerParams params;
	params.m_relativeFitToleranceOfInternalNodes = 0.5f;
	params.m_absoluteFitToleranceOfInternalNodes = 0.2f;
	params.m_absoluteFitToleranceOfTriangles = 1.0f;
	params.m_mode = 4;
	params.m_absoluteFitToleranceOfAxisAlignedTriangles.x = 0.2f;
	params.m_absoluteFitToleranceOfAxisAlignedTriangles.y = 0.2f;
	params.m_absoluteFitToleranceOfAxisAlignedTriangles.z = 0.05f;
	params.m_absoluteFitToleranceOfAxisAlignedTriangles.w = 0.0f;
	params.m_relativeFitToleranceOfInternalNodes = mfr.getRelativeFitToleranceOfInternalNodes();
	params.m_absoluteFitToleranceOfInternalNodes = mfr.getAbsoluteFitToleranceOfInternalNodes();
	params.m_absoluteFitToleranceOfTriangles = mfr.getAbsoluteFitToleranceOfTriangles();
	hkVector4 axisAligned;
	mfr.getAbsoluteFitToleranceOfAxisAlignedTriangles(axisAligned);
	params.m_absoluteFitToleranceOfAxisAlignedTriangles = axisAligned;
	compiler.setAssemblerParams(params);

	hkMoppSplitParams split;
	hkMoppSplitParams_init(&split, 0);
	if (mfr.m_enablePrimitiveSplitting)
	{
		split.m_v[2] = 0x32;
	}
	else
	{
		split.m_v[1] = 0;
		split.m_v[2] = 0;
	}
	split.m_v[4] = 5;
	compiler.setSplitParams(split);

	int bufferSize = compiler.calcBufferSize(collectionInterface);
	void* buffer = hkMemory::s_instance->allocate(bufferSize, 0x25);
	hkMoppCode* code = compiler.build(collectionInterface, buffer, bufferSize);
	hkMemory::s_instance->deallocate(buffer);
	return code;
}

// ---------------------------------------------------------------------------------------------------------
// Ray-hit collectors
// ---------------------------------------------------------------------------------------------------------
struct hkClosestRayHitCollector : hkRayHitCollector      // vtable 0x01464944
{
	virtual void addRayHit(const hkCdBody& cdBody, const hkShapeRayCastOutput& hitInfo);
	hkWorldRayCastOutput m_rayHit;                          // +0x10 (hkVector4 is 16-byte aligned)
};

// @ 0x010cbf50
void hkClosestRayHitCollector::addRayHit(const hkCdBody& cdBody, const hkShapeRayCastOutput& hitInfo)
{
	// fcomp + test ah,5 / jp: plain "<" (false when unordered)
	if (hitInfo.m_hitFraction < m_rayHit.m_hitFraction)
	{
		memcpy(&m_rayHit, &hitInfo, 0x18);                      // six raw dwords: normal, shapeKey, hitFraction
		const hkCdBody* root = &cdBody;
		while (root->m_parent)
			root = root->m_parent;
		m_rayHit.m_rootCollidable = (const hkCollidable*)root;
		m_earlyOutHitFraction = hitInfo.m_hitFraction;
	}
}

struct hkAllRayHitCollector : hkRayHitCollector          // vtable 0x0146494C
{
	virtual void addRayHit(const hkCdBody& cdBody, const hkShapeRayCastOutput& hitInfo);
	void sortHits();
	uint32_t m_pad[2];                                      // (32-bit layout) the array starts at +0x10
	hkArray<hkWorldRayCastOutput> m_hits;                   // +0x10
};

// @ 0x010cbfb0
void hkAllRayHitCollector::addRayHit(const hkCdBody& cdBody, const hkShapeRayCastOutput& hitInfo)
{
	if (m_hits.m_size == m_hits.getCapacity())
		hkArrayUtil::_reserveMore(&m_hits, 0x30);
	hkWorldRayCastOutput* e = &m_hits.m_data[m_hits.m_size];
	m_hits.m_size = m_hits.m_size + 1;
	memcpy(e, &hitInfo, 0x18);                              // six raw dwords (padding is not copied)
	const hkCdBody* root = &cdBody;
	while (root->m_parent)
		root = root->m_parent;
	e->m_rootCollidable = (const hkCollidable*)root;
}

// Element copy used by the swap in the quick sort: the first six dwords plus m_rootCollidable.
static inline void hkWorldRayCastOutput_copy(hkWorldRayCastOutput* dst, const hkWorldRayCastOutput* src)
{
	memcpy(dst, src, 0x18);
	dst->m_rootCollidable = src->m_rootCollidable;
}

struct hkWorldRayCastOutputLess { };    // empty comparator object passed by value (compares m_hitFraction)

// @ 0x010cc020  (hkAlgorithm::quickSortRecursive specialised on m_hitFraction)
static void quickSortRecursive(hkWorldRayCastOutput* pArr, int d, int h, hkWorldRayCastOutputLess less)
{
	do
	{
		float pivot = pArr[(d + h) >> 1].m_hitFraction;
		int i = d;
		int j = h;
		do
		{
			while (pArr[i].m_hitFraction < pivot) ++i;
			while (pivot < pArr[j].m_hitFraction) --j;
			if (j < i) break;
			if (i != j)
			{
				hkWorldRayCastOutput tmp;
				hkWorldRayCastOutput_copy(&tmp, &pArr[j]);
				hkWorldRayCastOutput_copy(&pArr[j], &pArr[i]);
				hkWorldRayCastOutput_copy(&pArr[i], &tmp);
			}
			--j;
			++i;
		} while (i <= j);
		if (d < j)
			quickSortRecursive(pArr, d, j, less);
		d = i;
	} while (d < h);
}

// @ 0x010cc160
void hkAllRayHitCollector::sortHits()
{
	if (m_hits.m_size > 1)
	{
		hkWorldRayCastOutputLess less;
		quickSortRecursive(m_hits.m_data, 0, m_hits.m_size - 1, less);
	}
}

// ---------------------------------------------------------------------------------------------------------
// Broad phase types
// ---------------------------------------------------------------------------------------------------------
struct hkBroadPhaseHandle { uint32_t m_id; };
struct hkTypedBroadPhaseHandle : hkBroadPhaseHandle
{
	signed char m_type;               // +4
	signed char m_ownerOffset;        // +5 (byte offset from the handle to its hkCollidable)
	uint16_t m_objectQualityType;     // +6
	uint32_t m_collisionFilterInfo;   // +8
};
struct hkCollidable : hkCdBody
{
	int m_ownerOffset;                              // +0x10
	hkTypedBroadPhaseHandle m_broadPhaseHandle;     // +0x14
	float m_allowedPenetrationDepth;                // +0x20
};
struct hkBroadPhaseHandlePair { hkBroadPhaseHandle* m_a; hkBroadPhaseHandle* m_b; };               // 8 bytes (32-bit)
struct hkTypedBroadPhaseHandlePair { hkTypedBroadPhaseHandle* m_a; hkTypedBroadPhaseHandle* m_b; };// 8 bytes (32-bit)

class hkShapeCollectionFilter { public: virtual ~hkShapeCollectionFilter() {} };
class hkRayShapeCollectionFilter { public: virtual ~hkRayShapeCollectionFilter() {} };
class hkCollidableCollidableFilter
{
public:
	virtual ~hkCollidableCollidableFilter() {}                                                              // 0
	virtual hkBool isCollisionEnabled(const hkCollidable& a, const hkCollidable& b) const = 0;              // 1
};
class hkRayCollidableFilter
{
public:
	virtual ~hkRayCollidableFilter() {}                                                                      // 0
	virtual hkBool isCollisionEnabled(const hkWorldRayCastInput& a, const hkCollidable& b) const = 0;       // 1
};
// Base order gives the binary's offsets: +8 collidable pair, +0xc shape collection, +0x10 ray shape collection,
// +0x14 ray/collidable (32-bit layout).
class hkCollisionFilter : public hkReferencedObject, public hkCollidableCollidableFilter, public hkShapeCollectionFilter,
	public hkRayShapeCollectionFilter, public hkRayCollidableFilter { };

class hkBroadPhaseCastCollector
{
public:
	virtual ~hkBroadPhaseCastCollector() {}                                                   // 0
	virtual hkReal addBroadPhaseHandle(const hkBroadPhaseHandle* h, int castIndex) = 0;       // 1
};

struct hkBroadPhaseCastRayInput                  // built on the stack by hkWorldRayCaster::castRay (0x20 bytes)
{
	hkVector4 m_from;                             // +0
	int m_numRays;                                // +0x10
	const hkVector4* m_toBase;                    // +0x14
	int m_toStriding;                             // +0x18
	const void* m_aabbCacheInfo;                  // +0x1c
};
struct hkAabbCastInput { hkVector4 m_from; hkVector4 m_to; hkVector4 m_halfExtents; };   // three vectors built by linearCast

#define HK_BP_PAD(n) virtual void bpSlot##n();
class hkBroadPhase
{
public:
	HK_BP_PAD(0) HK_BP_PAD(1) HK_BP_PAD(2) HK_BP_PAD(3) HK_BP_PAD(4) HK_BP_PAD(5) HK_BP_PAD(6) HK_BP_PAD(7)
	HK_BP_PAD(8) HK_BP_PAD(9) HK_BP_PAD(10) HK_BP_PAD(11) HK_BP_PAD(12) HK_BP_PAD(13) HK_BP_PAD(14)
	virtual void castRay(const hkBroadPhaseCastRayInput& input, hkBroadPhaseCastCollector* collector, int collectorStriding) const;   // 15 (+0x3c)
	HK_BP_PAD(16) HK_BP_PAD(17)
	virtual void castAabb(const hkAabbCastInput& input, hkBroadPhaseCastCollector& collector) const;                                    // 18 (+0x48)
};

// ---------------------------------------------------------------------------------------------------------
// hkWorldRayCaster
// ---------------------------------------------------------------------------------------------------------
class hkWorldRayCaster : public hkBroadPhaseCastCollector
{
public:
	void castRay(hkBroadPhase& broadphase, const hkWorldRayCastInput& input, const hkCollisionFilter* filter,
	             const char* aabbCache, hkRayHitCollector& collector);
	virtual hkReal addBroadPhaseHandle(const hkBroadPhaseHandle* broadPhaseHandle, int castIndex);

	const hkWorldRayCastInput* m_input;              // +4
	const hkRayCollidableFilter* m_filter;           // +8
	hkRayHitCollector* m_collectorBase;              // +0xc
	int m_collectorStriding;                         // +0x10
	hkShapeRayCastInput m_shapeInput;                // +0x20 (16-byte aligned through hkVector4)
};

// @ 0x010cc190
hkReal hkWorldRayCaster::addBroadPhaseHandle(const hkBroadPhaseHandle* broadPhaseHandle, int castIndex)
{
	const hkTypedBroadPhaseHandle* handle = (const hkTypedBroadPhaseHandle*)broadPhaseHandle;
	const hkCollidable* collidable = (const hkCollidable*)((const char*)handle + handle->m_ownerOffset);
	hkRayHitCollector* collector = (hkRayHitCollector*)((char*)m_collectorBase + (size_t)(m_collectorStriding * castIndex));
	const hkShape* shape = collidable->m_shape;
	if (shape != 0)
	{
		const hkWorldRayCastInput* in = &m_input[castIndex];
		if (m_filter->isCollisionEnabled(*in, *collidable))
		{
			const hkTransform* t = (const hkTransform*)collidable->m_motion;
			const hkWorldRayCastInput* in0 = m_input;    // the ray origin always comes from element 0 (single point)
			// X87-PRECISION: dx/dy/dz and every product/partial sum stay on the x87 stack; only the final sum is stored.
			{
				hkX87Real dx = (hkX87Real)in0->m_from.x - t->m_trans.x;
				hkX87Real dy = (hkX87Real)in0->m_from.y - t->m_trans.y;
				hkX87Real dz = (hkX87Real)in0->m_from.z - t->m_trans.z;
				m_shapeInput.m_from.x = (float)((dx * t->m_rot[0].x + dz * t->m_rot[0].z) + dy * t->m_rot[0].y);
				m_shapeInput.m_from.y = (float)((dx * t->m_rot[1].x + dz * t->m_rot[1].z) + dy * t->m_rot[1].y);
				m_shapeInput.m_from.z = (float)((dx * t->m_rot[2].x + dz * t->m_rot[2].z) + dy * t->m_rot[2].y);
				m_shapeInput.m_from.w = 0.0f;
			}
			{
				hkX87Real dx = (hkX87Real)in->m_to.x - t->m_trans.x;
				hkX87Real dy = (hkX87Real)in->m_to.y - t->m_trans.y;
				hkX87Real dz = (hkX87Real)in->m_to.z - t->m_trans.z;
				m_shapeInput.m_to.x = (float)((dx * t->m_rot[0].x + dz * t->m_rot[0].z) + dy * t->m_rot[0].y);
				m_shapeInput.m_to.y = (float)((dx * t->m_rot[1].x + dz * t->m_rot[1].z) + dy * t->m_rot[1].y);
				m_shapeInput.m_to.z = (float)((dx * t->m_rot[2].x + dz * t->m_rot[2].z) + dy * t->m_rot[2].y);
				m_shapeInput.m_to.w = 0.0f;
			}
			m_shapeInput.m_filterInfo = in->m_filterInfo;
			shape->castRayWithCollector(m_shapeInput, *collidable, *collector);
		}
	}
	return collector->m_earlyOutHitFraction;
}

// @ 0x010cc2c0
void hkWorldRayCaster::castRay(hkBroadPhase& broadphase, const hkWorldRayCastInput& input, const hkCollisionFilter* filter,
                               const char* aabbCache, hkRayHitCollector& collector)
{
	HK_TIMER_BEGIN("TtRayCstCached");
	m_collectorBase = &collector;
	m_input = &input;
	m_collectorStriding = 0;
	m_filter = filter ? static_cast<const hkRayCollidableFilter*>(filter) : 0;
	if (input.m_enableShapeCollectionFilter)
		m_shapeInput.m_rayShapeCollectionFilter = filter ? static_cast<const hkRayShapeCollectionFilter*>(filter) : 0;
	else
		m_shapeInput.m_rayShapeCollectionFilter = 0;

	hkBroadPhaseCastRayInput rayInput;
	rayInput.m_from.x = input.m_from.x;
	rayInput.m_from.y = input.m_from.y;
	rayInput.m_from.z = input.m_from.z;
	rayInput.m_from.w = input.m_from.w;
	rayInput.m_toBase = &input.m_to;
	rayInput.m_aabbCacheInfo = aabbCache;
	rayInput.m_numRays = 1;
	rayInput.m_toStriding = 0x10;
	broadphase.castRay(rayInput, this, 0);
	HK_TIMER_END();
}

// ---------------------------------------------------------------------------------------------------------
// hkTypedBroadPhaseDispatcher
// ---------------------------------------------------------------------------------------------------------
class hkBroadPhaseListener : public hkReferencedObject
{
public:
	virtual void addCollisionPair(hkTypedBroadPhaseHandlePair& pair) = 0;      // 2
	virtual void removeCollisionPair(hkTypedBroadPhaseHandlePair& pair) = 0;   // 3
};
class hkNullBroadPhaseListener : public hkBroadPhaseListener                    // vtable 0x014A4260, 8 bytes
{
public:
	static void* operator new(size_t n)
	{
		void* p = hkMemory::s_instance->allocateChunk((int)n, HK_MEMORY_CLASS_CDINFO);
		((hkReferencedObject*)p)->m_memSizeAndFlags = (hkInt16)n;
		return p;
	}
	static void operator delete(void* p)
	{
		hkMemory::s_instance->deallocateChunk(p, ((hkReferencedObject*)p)->m_memSizeAndFlags, HK_MEMORY_CLASS_CDINFO);
	}
	virtual void addCollisionPair(hkTypedBroadPhaseHandlePair&) {}
	virtual void removeCollisionPair(hkTypedBroadPhaseHandlePair&) {}
};

// hkPointerMapBase<hkUint64> (code at 0x0107E0F0..0x0107E5D0): m_elem holds the keys [0..m_hashMod] followed by the
// values; findKey returns an index that is <= m_hashMod when the key exists.
struct hkPointerMapBaseU64
{
	hkUint64* m_elem;
	int m_numElems;
	int m_hashMod;
	hkPointerMapBaseU64();                                      // 0x0107E0F0
	~hkPointerMapBaseU64();                                     // 0x0107E140
	void reserve(int numElements);                              // 0x0107E5D0
	int findKey(hkUint64 key) const;                            // 0x0107E240
	void insert(hkUint64 key, hkUint64 value);                  // 0x0107E160
	void remove(int iterator);                                  // 0x0107E2D0
	hkUint64* valueAt(int iterator) const { return &m_elem[m_hashMod + 1 + iterator]; }
};

class hkTypedBroadPhaseDispatcher
{
public:
	hkTypedBroadPhaseDispatcher();
	~hkTypedBroadPhaseDispatcher();
	void addPairs(hkTypedBroadPhaseHandlePair* newPairs, int numNewPairs, const hkCollidableCollidableFilter* filter) const;
	void removePairs(hkTypedBroadPhaseHandlePair* deletedPairs, int numDeletedPairs) const;
	static void removeDuplicates(hkArray<hkBroadPhaseHandlePair>& newPairs, hkArray<hkBroadPhaseHandlePair>& delPairs);

	hkBroadPhaseListener* m_broadPhaseListeners[8][8];     // +0
	hkNullBroadPhaseListener* m_nullBroadPhaseListener;    // +0x100
};

// @ 0x010cc3f0
hkTypedBroadPhaseDispatcher::~hkTypedBroadPhaseDispatcher()
{
	delete m_nullBroadPhaseListener;
}

// @ 0x010cc410
void hkTypedBroadPhaseDispatcher::addPairs(hkTypedBroadPhaseHandlePair* newPairs, int numNewPairs, const hkCollidableCollidableFilter* filter) const
{
	for (int i = numNewPairs - 1; i >= 0; --i)
	{
		const hkTypedBroadPhaseHandle* a = newPairs->m_a;
		const hkTypedBroadPhaseHandle* b = newPairs->m_b;
		const hkCollidable* collA = (const hkCollidable*)((const char*)a + a->m_ownerOffset);
		const hkCollidable* collB = (const hkCollidable*)((const char*)b + b->m_ownerOffset);
		if (filter->isCollisionEnabled(*collA, *collB))
		{
			m_broadPhaseListeners[newPairs->m_a->m_type][newPairs->m_b->m_type]->addCollisionPair(*newPairs);
		}
		++newPairs;
	}
}

// @ 0x010cc480
void hkTypedBroadPhaseDispatcher::removePairs(hkTypedBroadPhaseHandlePair* deletedPairs, int numDeletedPairs) const
{
	for (int i = numDeletedPairs - 1; i >= 0; --i)
	{
		m_broadPhaseListeners[deletedPairs->m_a->m_type][deletedPairs->m_b->m_type]->removeCollisionPair(*deletedPairs);
		++deletedPairs;
	}
}

// @ 0x010cc4c0
hkTypedBroadPhaseDispatcher::hkTypedBroadPhaseDispatcher()
{
	m_nullBroadPhaseListener = new hkNullBroadPhaseListener();
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			m_broadPhaseListeners[i][j] = m_nullBroadPhaseListener;
}

// The 64-bit key of a handle pair is (smaller pointer) | (larger pointer << 32): only valid for 32-bit pointers.
// 32-BIT ASSUMPTION: a 64-bit port needs a wider key (e.g. a pair, or hashing both pointers).
static inline hkUint64 hkMakePairKey(const void* lo, const void* hi)
{
	return (hkUint64)(uint32_t)(uintptr_t)lo | ((hkUint64)(uint32_t)(uintptr_t)hi << 32);
}

// @ 0x010cc560  (cdecl; removes pairs that appear in both arrays, in either order)
void hkTypedBroadPhaseDispatcher::removeDuplicates(hkArray<hkBroadPhaseHandlePair>& newPairs, hkArray<hkBroadPhaseHandlePair>& delPairs)
{
	int minSize = delPairs.m_size;
	if (newPairs.m_size < delPairs.m_size)
		minSize = newPairs.m_size;

	if (minSize < 32)
	{
		// small case: quadratic search
		for (int j = 0; j < delPairs.m_size; ++j)
		{
			const void* delA = delPairs.m_data[j].m_a;
			const hkBroadPhaseHandlePair* del = &delPairs.m_data[j];
			for (int i = 0; i < newPairs.m_size; ++i)
			{
				const hkBroadPhaseHandlePair& np = newPairs.m_data[i];
				if ((np.m_a == delA && np.m_b == del->m_b) || (np.m_b == delA && np.m_a == del->m_b))
				{
					int last = newPairs.m_size - 1;
					newPairs.m_size = last;
					newPairs.m_data[i] = newPairs.m_data[last];
					int dlast = delPairs.m_size - 1;
					delPairs.m_size = dlast;
					delPairs.m_data[j] = delPairs.m_data[dlast];
					--j;
					break;
				}
			}
		}
		return;
	}

	// large case: hash the new pairs by their (ordered) pointer pair; value = (index << 8) | count
	hkPointerMapBaseU64 map;
	map.reserve(newPairs.m_size);
	for (int i = 0; i < newPairs.m_size; ++i)
	{
		uintptr_t lo = (uintptr_t)newPairs.m_data[i].m_a;
		uintptr_t hi = (uintptr_t)newPairs.m_data[i].m_b;
		if (lo > hi) { uintptr_t t = lo; lo = hi; hi = t; }
		hkUint64 key = hkMakePairKey((const void*)lo, (const void*)hi);
		int it = map.findKey(key);
		if (it <= map.m_hashMod)
		{
			*map.valueAt(it) += 1;
			newPairs.m_data[i].m_a = 0;
		}
		else
		{
			map.insert(key, (hkUint64)(int64_t)(int)((i << 8) | 1));
		}
	}
	for (int j = 0; j < delPairs.m_size; ++j)
	{
		uintptr_t lo = (uintptr_t)delPairs.m_data[j].m_a;
		uintptr_t hi = (uintptr_t)delPairs.m_data[j].m_b;
		if (lo > hi) { uintptr_t t = lo; lo = hi; hi = t; }
		int it = map.findKey(hkMakePairKey((const void*)lo, (const void*)hi));
		if (it <= map.m_hashMod)
		{
			hkUint64* valuePtr = map.valueAt(it);
			hkUint64 value = *valuePtr;
			if ((uint32_t)(value & 0xff) > 1)
			{
				*valuePtr = value - 1;
			}
			else
			{
				map.remove(it);
				newPairs.m_data[(uint32_t)value >> 8].m_a = 0;
			}
			int last = delPairs.m_size - 1;
			delPairs.m_size = last;
			delPairs.m_data[j] = delPairs.m_data[last];
			--j;
		}
	}
	// compact the surviving new pairs
	int n = 0;
	for (int i = 0; i < newPairs.m_size; ++i)
	{
		if (newPairs.m_data[i].m_a != 0)
		{
			newPairs.m_data[n].m_a = newPairs.m_data[i].m_a;
			newPairs.m_data[n].m_b = newPairs.m_data[i].m_b;
			++n;
		}
	}
	newPairs.setSize(n);
}

// ---------------------------------------------------------------------------------------------------------
// hkWorldLinearCaster
// ---------------------------------------------------------------------------------------------------------
struct hkCollisionAgentConfig;
class hkCollisionDispatcher;
class hkCdPointCollector
{
public:
	virtual void v0();
	virtual void addCdPoint();
	float m_earlyOutDistance;     // +4
};
struct hkCollisionInput
{
	hkCollisionDispatcher* m_dispatcher;      // +0
	const void* m_filter;                     // +4 (hkShapeCollectionFilter*)
	float m_tolerance;                        // +8
	hkBool m_createPredictiveAgents;          // +0xc
	hkCollisionInput() : m_createPredictiveAgents(false) {}
};
struct hkLinearCastCollisionInput : hkCollisionInput
{
	hkVector4 m_path;                         // +0x10
	float m_maxExtraPenetration;              // +0x20
	float m_cachedPathLength;                 // +0x24
	hkCollisionAgentConfig* m_config;         // +0x28
};
struct hkLinearCastInput
{
	hkVector4 m_to;                           // +0
	float m_maxExtraPenetration;              // +0x10
	float m_startPointTolerance;              // +0x14
};
typedef void (__cdecl *hkAgentLinearCastFunc)(const hkCdBody&, const hkCdBody&, const hkLinearCastCollisionInput&,
                                              hkCdPointCollector&, hkCdPointCollector*);
struct hkAgentFuncs                            // 0x14 bytes in the 32-bit binary
{
	void* m_createFunc;                       // +0
	void* m_getPenetrationsFunc;              // +4
	void* m_getClosestPointFunc;              // +8
	hkAgentLinearCastFunc m_linearCastFunc;   // +0xc
	uint8_t m_isFlipped, m_isPredictive;      // +0x10
};
class hkCollisionDispatcher
{
public:
	uint8_t m_pad0[0x190];                    // (32-bit layout)
	uint8_t m_agent2Types[32][32];            // +0x190
	uint8_t m_agent2TypesPredictive[32][32];  // +0x590
	hkAgentFuncs m_agent2Func[1];             // +0x990 (stride 0x14 in the binary)
};

class hkWorldLinearCaster : public hkBroadPhaseCastCollector
{
public:
	void linearCast(const hkBroadPhase& broadphase, const hkCollidable* collA, const hkLinearCastInput& input,
	                const hkCollidableCollidableFilter* filter, const hkCollisionInput& collInput,
	                hkCollisionAgentConfig* config, hkCdPointCollector& castCollector, hkCdPointCollector* startPointCollector);
	virtual hkReal addBroadPhaseHandle(const hkBroadPhaseHandle* broadPhaseHandle, int castIndex);

	const hkLinearCastInput* m_input;                    // +4
	const hkCollidableCollidableFilter* m_filter;        // +8
	hkCdPointCollector* m_castCollector;                 // +0xc
	hkCdPointCollector* m_startPointCollector;           // +0x10
	const hkCollidable* m_collidableA;                   // +0x14
	int m_typeA;                                         // +0x18
	hkLinearCastCollisionInput m_shapeInput;             // +0x20
};

// @ 0x010cc7d0
hkReal hkWorldLinearCaster::addBroadPhaseHandle(const hkBroadPhaseHandle* broadPhaseHandle, int castIndex)
{
	const hkTypedBroadPhaseHandle* handle = (const hkTypedBroadPhaseHandle*)broadPhaseHandle;
	const hkCollidable* collB = (const hkCollidable*)((const char*)handle + handle->m_ownerOffset);
	const hkShape* shapeB = collB->m_shape;
	if (shapeB != 0 && m_collidableA != collB)
	{
		if (m_filter->isCollisionEnabled(*m_collidableA, *collB))
		{
			int typeB = shapeB->getType();
			hkCollisionDispatcher* d = m_shapeInput.m_dispatcher;
			int agentIndex = d->m_agent2Types[m_typeA][typeB];
			d->m_agent2Func[agentIndex].m_linearCastFunc(*m_collidableA, *collB, m_shapeInput, *m_castCollector, m_startPointCollector);
		}
	}
	return m_castCollector->m_earlyOutDistance;
}

// @ 0x010cc860
void hkWorldLinearCaster::linearCast(const hkBroadPhase& broadphase, const hkCollidable* collA, const hkLinearCastInput& input,
                                     const hkCollidableCollidableFilter* filter, const hkCollisionInput& collInput,
                                     hkCollisionAgentConfig* config, hkCdPointCollector& castCollector,
                                     hkCdPointCollector* startPointCollector)
{
	m_castCollector = &castCollector;
	m_startPointCollector = startPointCollector;
	m_input = &input;
	m_collidableA = collA;
	m_filter = filter;
	m_typeA = collA->m_shape->getType();
	static_cast<hkCollisionInput&>(m_shapeInput) = collInput;
	m_shapeInput.m_config = config;

	const hkTransform* motion = (const hkTransform*)collA->m_motion;
	hkVector4 path;
	path.x = input.m_to.x - motion->m_trans.x;
	path.y = input.m_to.y - motion->m_trans.y;
	path.z = input.m_to.z - motion->m_trans.z;
	path.w = input.m_to.w - motion->m_trans.w;
	m_shapeInput.m_path = path;
	// X87-PRECISION: the sum of squares stays on the x87 stack until fsqrt (inline fsqrt, correctly rounded in 24-bit mode)
	hkX87Real lengthSq = ((hkX87Real)path.z * path.z + (hkX87Real)path.y * path.y) + (hkX87Real)path.x * path.x;
	m_shapeInput.m_cachedPathLength = (float)sqrt(lengthSq);
	m_shapeInput.m_tolerance = input.m_startPointTolerance;

	hkAabb aabb;
	collA->m_shape->getAabb(*motion, input.m_startPointTolerance, aabb);
	m_shapeInput.m_maxExtraPenetration = input.m_maxExtraPenetration;

	hkAabbCastInput cast;
	// X87-PRECISION: each (a + b) feeds fmul 0.5 on the stack before the store
	cast.m_from.x = (float)(((hkX87Real)aabb.m_min.x + aabb.m_max.x) * 0.5f);
	cast.m_from.y = (float)(((hkX87Real)aabb.m_max.y + aabb.m_min.y) * 0.5f);
	cast.m_from.z = (float)(((hkX87Real)aabb.m_max.z + aabb.m_min.z) * 0.5f);
	cast.m_from.w = (float)(((hkX87Real)aabb.m_max.w + aabb.m_min.w) * 0.5f);
	cast.m_to.x = cast.m_from.x + path.x;
	cast.m_to.y = cast.m_from.y + path.y;
	cast.m_to.z = cast.m_from.z + path.z;
	cast.m_to.w = cast.m_from.w + path.w;
	float extentX = 0.0f, extentY = 0.0f;
	// X87-PRECISION: x and y differences are kept on the stack, z and w are stored and reloaded
	cast.m_halfExtents.x = (float)(((hkX87Real)aabb.m_max.x - aabb.m_min.x) * 0.5f);
	cast.m_halfExtents.y = (float)(((hkX87Real)aabb.m_max.y - aabb.m_min.y) * 0.5f);
	extentX = cast.m_halfExtents.x; extentY = cast.m_halfExtents.y;   // (silence unused warnings)
	(void)extentX; (void)extentY;
	{
		float dz = aabb.m_max.z - aabb.m_min.z;
		float dw = aabb.m_max.w - aabb.m_min.w;
		cast.m_halfExtents.z = dz * 0.5f;
		cast.m_halfExtents.w = dw * 0.5f;
	}
	broadphase.castAabb(cast, *this);
}

// ---------------------------------------------------------------------------------------------------------
// hkNullAgent3
// ---------------------------------------------------------------------------------------------------------
struct hkAgent3Input;
struct hkAgentEntry
{
	uint8_t m_streamCommand;
	uint8_t m_agentType;
	uint8_t m_numContactPoints;
	uint8_t m_size;
	uintptr_t m_userData;
};
struct hkNullAgent3
{
	static void* create(const hkAgent3Input& input, hkAgentEntry* entry, void* agentData);
};

// @ 0x010cca40
void* hkNullAgent3::create(const hkAgent3Input& input, hkAgentEntry* entry, void* agentData)
{
	entry->m_streamCommand = 0;
	return agentData;
}

// ---------------------------------------------------------------------------------------------------------
// 32-bit layout checks against the binary (offsets verified from the disassembly / PDB)
// ---------------------------------------------------------------------------------------------------------
#if defined(_M_IX86)
#define HK_LAYOUT_CHECK(name, cond) typedef char hkLayoutCheck_##name[(cond) ? 1 : -1]
HK_LAYOUT_CHECK(closestRayHit, sizeof(hkClosestRayHitCollector) == 0x40 && offsetof(hkClosestRayHitCollector, m_rayHit) == 0x10);
HK_LAYOUT_CHECK(allRayHit, offsetof(hkAllRayHitCollector, m_hits) == 0x10 && sizeof(hkWorldRayCastOutput) == 0x30);
HK_LAYOUT_CHECK(worldRayCaster, offsetof(hkWorldRayCaster, m_shapeInput) == 0x20 && offsetof(hkWorldRayCaster, m_collectorStriding) == 0x10);
HK_LAYOUT_CHECK(linearCaster, offsetof(hkWorldLinearCaster, m_shapeInput) == 0x20 && sizeof(hkWorldLinearCaster) == 0x50 && offsetof(hkWorldLinearCaster, m_typeA) == 0x18);
HK_LAYOUT_CHECK(dispatcher, offsetof(hkTypedBroadPhaseDispatcher, m_nullBroadPhaseListener) == 0x100);
HK_LAYOUT_CHECK(moppReq, sizeof(hkMoppFitToleranceRequirements) == 0x30 && offsetof(hkMoppFitToleranceRequirements, m_useShapeKeys) == 0x2c);
HK_LAYOUT_CHECK(handle, sizeof(hkTypedBroadPhaseHandle) == 0xc && sizeof(hkCollidable) == 0x24);
HK_LAYOUT_CHECK(bvShape, offsetof(hkBvShape, m_childShape) == 0x10);
HK_LAYOUT_CHECK(collisionInput, sizeof(hkLinearCastCollisionInput) == 0x30 && offsetof(hkLinearCastCollisionInput, m_config) == 0x28);
#endif
