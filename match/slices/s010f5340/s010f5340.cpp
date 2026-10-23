// flags: /O2 /MD /Gy /TP /vc71
// Slice s010f5340: hk3AxisSweep endpoint management (Havok 3.1.0 broadphase).
//
// getAabbFromNode converts a node's integer endpoints back to world space, getAllAabbs/getAabb are thin
// wrappers around it, insert/removeBatch maintain the per-axis sorted endpoint arrays, and
// addObject/removeObject/reQuerySingleObject insert/erase a node and report the overlaps found by walking
// the x endpoints through a bitfield (marker nodes give a head start; markers collect the overlapping
// node indices instead of pairs). begin/endOverlapCheckMarker are the two __fastcall helpers doing the
// marker bookkeeping.
//
// Layouts are the 32-bit offsets seen in the binary (the Havok 2013 hkp3AxisSweep.h is used for names only).
#include "types.h"
#include <stddef.h>

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);

typedef uint32_t hkUint32;
typedef uint16_t hkUint16;
typedef unsigned long hkUlong;
typedef float hkReal;
typedef hkUint16 BpInt;

inline void* operator new(unsigned int, void* p) throw() { return p; }

// ---- TLS globals ------------------------------------------------------------------------------------------------
extern unsigned long g_hkThreadMemoryTls;           // 0x016e4174

// ---- thread memory --------------------------------------------------------------------------------------------------
enum { HK_MEMORY_CLASS_ARRAY = 0x14 };
class hkThreadMemory
{
public:
	virtual void tm0();
	virtual void tm1();
	virtual void tm2();
	virtual void* onStackOverflow(int nbytes);   // 3 (+0xc)
	virtual void onStackUnderflow(void* p);      // 4 (+0x10)

	void deallocateChunk(void* p, int nbytes, int cl);   // 0x0107db10

	static __forceinline hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls); }

	__forceinline void* allocateStack(int nbytes)
	{
		int size = (nbytes + 0x10) & ~0xf;
		char* current = m_stackCurrent;
		char* next = current + size;
		if (next <= m_stackEnd)
		{
			m_stackCurrent = next;
			return current;
		}
		return onStackOverflow(size);
	}
	__forceinline void deallocateStack(void* p)
	{
		m_stackCurrent = (char*)p;
		if ((char*)p == m_stackBase)
			onStackUnderflow(p);
	}

	hkUint32 m_pad04[7];
	char* m_stackCurrent;   // +0x20
	char* m_stackPrev;      // +0x24
	char* m_stackBase;      // +0x28
	char* m_stackEnd;       // +0x2c
};

// ---- arrays -------------------------------------------------------------------------------------------------------
template <typename T>
class hkArray
{
public:
	enum { CAPACITY_MASK = 0x3fffffff };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	hkArray() : m_data(0), m_size(0), m_capacityAndFlags((int)0x80000000) {}
	hkArray(T* buffer, int size, int capacity) : m_data(buffer), m_size(size), m_capacityAndFlags(capacity | (int)0x80000000) {}
	__forceinline ~hkArray()
	{
		if (m_capacityAndFlags >= 0)
			hkThreadMemory::getInstance().deallocateChunk(m_data, (m_capacityAndFlags & CAPACITY_MASK) * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
	}
	int getSize() const { return m_size; }
	int indexOf(const T& t) const
	{
		for (int i = 0; i < m_size; i++)
			if (m_data[i] == t)
				return i;
		return -1;
	}
	T* begin() { return m_data; }
	const T* begin() const { return m_data; }
	T& operator[](int i) { return m_data[i]; }
	const T& operator[](int i) const { return m_data[i]; }
	__forceinline void pushBack(const T& t)
	{
		if (m_size == (m_capacityAndFlags & CAPACITY_MASK))
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		m_data[m_size] = t;
		m_size++;
	}
	__forceinline T& expandOne()
	{
		if (m_size == (m_capacityAndFlags & CAPACITY_MASK))
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		return m_data[m_size++];
	}
};

struct hkArrayUtil
{
	static void _reserveExactly(void* arrayBase, int numElem, int elemSize);   // 0x0107f4a0
	static void _reserveMore(void* arrayBase, int elemSize);                   // 0x0107f530
};

template <typename T>
struct hkLocalBuffer
{
	__forceinline explicit hkLocalBuffer(int n) { m_p = (T*)hkThreadMemory::getInstance().allocateStack(n * (int)sizeof(T)); }
	__forceinline ~hkLocalBuffer() { hkThreadMemory::getInstance().deallocateStack(m_p); }
	T* begin() { return m_p; }
	T* m_p;
};

// ---- math -----------------------------------------------------------------------------------------------------------
__declspec(align(16)) struct hkVector4
{
	hkReal x, y, z, w;
	__forceinline void setAdd4(const hkVector4& a, const hkVector4& b) { x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; w = a.w + b.w; }
	__forceinline void mul4(const hkVector4& a) { x *= a.x; y *= a.y; z *= a.z; w *= a.w; }
	__forceinline void setMin4(const hkVector4& a, const hkVector4& b)
	{
		x = (a.x < b.x) ? a.x : b.x;
		y = (a.y < b.y) ? a.y : b.y;
		z = (a.z < b.z) ? a.z : b.z;
		w = (a.w < b.w) ? a.w : b.w;
	}
	__forceinline void setMax4(const hkVector4& a, const hkVector4& b)
	{
		x = (a.x > b.x) ? a.x : b.x;
		y = (a.y > b.y) ? a.y : b.y;
		z = (a.z > b.z) ? a.z : b.z;
		w = (a.w > b.w) ? a.w : b.w;
	}
	__forceinline void setZero4() { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; }
};
class hkAabb
{
public:
	hkVector4 m_min;
	hkVector4 m_max;
};

// The broadphase resolution limit: 65532 in every component.
extern const hkVector4 hk3AxisSweep_maxIntValue;   // 0x015ba360

union hkFloatIntUnion4
{
	hkReal f[4];
	hkUint32 i[4];
};
static __forceinline void hkConvertToUint16(const hkVector4& v, hkUint16* out)
{
	hkFloatIntUnion4 u;
	u.f[0] = v.x + 65536.0f;
	u.f[1] = v.y + 65536.0f;
	u.f[2] = v.z + 65536.0f;
	u.f[3] = v.w + 65536.0f;
	out[0] = hkUint16(u.i[0] >> 7);
	out[1] = hkUint16(u.i[1] >> 7);
	out[2] = hkUint16(u.i[2] >> 7);
	out[3] = hkUint16(u.i[3] >> 7);
}

namespace hkAlgorithm
{
	template <typename T> struct less
	{
		bool operator()(const T& a, const T& b) const { return a < b; }
	};
}

// ---- hk3AxisSweep -----------------------------------------------------------------------------------------------
class hkBroadPhaseHandle
{
public:
	hkUint32 m_id;   // +0 (index of the node)
};
class hkBroadPhaseHandlePair
{
public:
	hkBroadPhaseHandle* m_a;
	hkBroadPhaseHandle* m_b;

	hkBroadPhaseHandlePair() {}
	hkBroadPhaseHandlePair(hkBroadPhaseHandle* a, hkBroadPhaseHandle* b) : m_a(a), m_b(b) {}
};
class hkReferencedObject
{
public:
	virtual ~hkReferencedObject();
	hkUint16 m_memSizeAndFlags;   // +4
	hkUint16 m_referenceCount;    // +6
};
class hkBroadPhase : public hkReferencedObject
{
public:
	hkUint32 m_type;              // +8 (padding up to the aligned members at +0x10)
};

// Offsets of the six per-node endpoint indices inside hkBpNode, indexed by axis * 2 + minmax.
static const int s_memberOffsets[6] = { 8, 0xa, 0, 4, 2, 6 };   // 0x015ba374

class hk3AxisSweep : public hkBroadPhase
{
public:
	struct hkBpNode;
	struct hkBpMarker;

	struct hkBpEndPoint
	{
		BpInt m_value;       // +0 (bit 0 set = max endpoint)
		BpInt m_nodeIndex;   // +2
		int isMaxPoint() const { return m_value & 1; }
		bool operator<(const hkBpEndPoint& o) const { return m_value < o.m_value; }
	};
	struct hkBpNode
	{
		BpInt min_y;                       // +0
		BpInt min_z;                       // +2
		BpInt max_y;                       // +4
		BpInt max_z;                       // +6
		BpInt min_x;                       // +8
		BpInt max_x;                       // +a
		hkBroadPhaseHandle* m_handle;      // +c (bit 0 set = marker)

		int isMarker() const { return int((hkUlong)m_handle) & 1; }
		hkBpMarker& getMarker(hkBpMarker* markers) const
		{
			return *(hkBpMarker*)((char*)markers + (int((hkUlong)m_handle) & ~1));
		}
		__forceinline hkUint32 yzDisjoint(const hkBpNode& other) const
		{
			hkUint32 maxA = *(const hkUint32*)&max_y;
			hkUint32 minB = *(const hkUint32*)&other.min_y;
			hkUint32 maxB = *(const hkUint32*)&other.max_y;
			hkUint32 minA = *(const hkUint32*)&min_y;
			return ((maxB - minA) | (maxA - minB)) & 0x80008000;
		}
		void setElem(int axis, int minmax, int value)
		{
			BpInt* p = (BpInt*)((char*)&min_y + s_memberOffsets[axis * 2 + minmax]);
			p[0] = BpInt(value);
		}
	};
	struct hkBpMarker
	{
		BpInt m_nodeIndex;                         // +0
		BpInt m_value;                             // +2
		hkArray<BpInt> m_overlappingObjects;       // +4
	};
	struct hkBpAxis
	{
		hkArray<hkBpEndPoint> m_endPoints;

		void insert(hkBpNode* nodes, int nodeIndex, BpInt minPosition, BpInt maxPosition,
		            BpInt& minInsertPositionOut, BpInt& maxInsertPositionOut);
		void removeBatch(hkBpNode* nodes, int axis, const hkArray<int>& nodeRelocations);
		void remove(int minPosition, int maxPosition);   // 0x010f50f0
	};

	virtual void addObject(hkBroadPhaseHandle* object, const hkAabb& aabb, hkArray<hkBroadPhaseHandlePair>& pairsOut);
	virtual void removeObject(hkBroadPhaseHandle* object, hkArray<hkBroadPhaseHandlePair>& pairsOut);
	virtual void reQuerySingleObject(hkBroadPhaseHandle* object, hkArray<hkBroadPhaseHandlePair>& pairsOut) const;
	virtual void getAabb(hkBroadPhaseHandle* object, hkAabb& aabb) const;
	virtual void getAllAabbs(hkArray<hkAabb>& aabbsOut);

	void setBitsBasedOnXInterval(int numNodes, int x_value, const hkBpNode& queryNode, BpInt queryNodeIndex, hkUint32* bitField) const;   // 0x010f5150
	void updateNodesAfterInsert(hkBpNode* nodes, int numNodes, hkBpNode& newNode);   // 0x010f4ab0
	void updateNodesAfterDelete(hkBpNode* nodes, int numNodes, hkBpNode& oldNode);   // 0x010f4c60

protected:
	void getAabbFromNode(const hkBpNode& node, hkAabb& aabb) const;

public:
	hkVector4 m_offsetLow;              // +0x10
	hkVector4 m_offsetHigh;             // +0x20
	hkVector4 m_scale;                  // +0x30
	hkArray<hkBpNode> m_nodes;          // +0x40
	hkBpAxis m_axis[3];                 // +0x4c
	int m_numMarkers;                   // +0x70
	int m_ld2NumMarkers;                // +0x74
	hkBpMarker* m_markers;              // +0x78
};
typedef char hk3AxisSweep_layout_check[(offsetof(hk3AxisSweep, m_nodes) == 0x40 && offsetof(hk3AxisSweep, m_markers) == 0x78) ? 1 : -1];

// hkAlgorithm::quickSortRecursive<hkBpEndPoint, less<hkBpEndPoint> > (instantiated out of line).
// Verbatim from hkSort.inl: the HK_ALIGN16 locals are what force the 16-byte aligned frame.
template <typename T, typename Less>
void quickSortRecursive(T* pArr, int d, int h, Less cmpLess)
{
	int i, j;
	__declspec(align(16)) T str;
begin:
	i = h;
	j = d;

	str = pArr[(d + h) >> 1];

	do
	{
		while (cmpLess(pArr[j], str)) { j++; }
		while (cmpLess(str, pArr[i])) { i--; }

		if (i >= j)
		{
			if (i != j)
			{
				__declspec(align(16)) T zal;
				T& pi = pArr[i];
				T& pj = pArr[j];
				zal = pi; pi = pj, pj = zal;
			}

			i--;
			j++;
		}
	} while (j <= i);

	if (d < i)
	{
		quickSortRecursive(pArr, d, i, cmpLess);
	}

	if (j < h)
	{
		d = j;
		goto begin;
	}
}
template void quickSortRecursive<hk3AxisSweep::hkBpEndPoint, hkAlgorithm::less<hk3AxisSweep::hkBpEndPoint> >(
	hk3AxisSweep::hkBpEndPoint*, int, int, hkAlgorithm::less<hk3AxisSweep::hkBpEndPoint>);

// @ 0x010f5340
void hk3AxisSweep::getAabbFromNode(const hkBpNode& node, hkAabb& aabb) const
{
	hkVector4 invScale;
	invScale.x = 1.0f / m_scale.x;
	invScale.y = 1.0f / m_scale.y;
	invScale.z = 1.0f / m_scale.z;

	hkVector4 min;
	min.x = hkReal(m_axis[0].m_endPoints[node.min_x].m_value) * invScale.x - m_offsetLow.x;
	min.y = hkReal(m_axis[1].m_endPoints[node.min_y].m_value) * invScale.y - m_offsetLow.y;
	min.z = hkReal(m_axis[2].m_endPoints[node.min_z].m_value) * invScale.z - m_offsetLow.z;
	min.w = -m_offsetLow.w;

	hkVector4 max;
	max.x = hkReal(m_axis[0].m_endPoints[node.max_x].m_value) * invScale.x - m_offsetLow.x;
	max.y = hkReal(m_axis[1].m_endPoints[node.max_y].m_value) * invScale.y - m_offsetLow.y;
	max.z = hkReal(m_axis[2].m_endPoints[node.max_z].m_value) * invScale.z - m_offsetLow.z;
	max.w = -m_offsetLow.w;

	aabb.m_min = min;
	aabb.m_max = max;
}

// @ 0x010f5500
void __fastcall beginOverlapCheckMarker(hk3AxisSweep::hkBpMarker* markers, hk3AxisSweep::hkBpNode& a,
                                               int nodeIndexA, hk3AxisSweep::hkBpNode& b,
                                               hkArray<hkBroadPhaseHandlePair>& newPairsOut)
{
	if (!b.isMarker())
	{
		hkBroadPhaseHandlePair& pair = newPairsOut.expandOne();
		pair.m_a = a.m_handle;
		pair.m_b = b.m_handle;
	}
	else
	{
		hk3AxisSweep::hkBpMarker& marker = *(hk3AxisSweep::hkBpMarker*)((char*)markers + (int((hkUlong)b.m_handle) & ~1));
		marker.m_overlappingObjects.pushBack(BpInt(nodeIndexA));
	}
}

// @ 0x010f5590
void __fastcall endOverlapCheckMarker(hk3AxisSweep::hkBpMarker* markers, hk3AxisSweep::hkBpNode& a,
                                             int nodeIndexA, hk3AxisSweep::hkBpNode& b,
                                             hkArray<hkBroadPhaseHandlePair>& deletedPairsOut)
{
	if (!b.isMarker())
	{
		hkBroadPhaseHandlePair& pair = deletedPairsOut.expandOne();
		pair.m_a = a.m_handle;
		pair.m_b = b.m_handle;
	}
	else
	{
		hk3AxisSweep::hkBpMarker& marker = *(hk3AxisSweep::hkBpMarker*)((char*)markers + (int((hkUlong)b.m_handle) & ~1));
		const int index = marker.m_overlappingObjects.indexOf(BpInt(nodeIndexA));
		marker.m_overlappingObjects.m_size--;
		marker.m_overlappingObjects[index] = marker.m_overlappingObjects[marker.m_overlappingObjects.m_size];
	}
}

// @ 0x010f5620
void hk3AxisSweep::hkBpAxis::removeBatch(hkBpNode* nodes, int axis, const hkArray<int>& relocations)
{
	hkBpEndPoint* out = m_endPoints.begin();
	const hkBpEndPoint* end = m_endPoints.begin() + m_endPoints.getSize();
	int count = 0;
	for (const hkBpEndPoint* ep = m_endPoints.begin(); ep < end; ep++)
	{
		const int relocation = relocations[ep->m_nodeIndex];
		if (relocation < 0)
			continue;
		*out = *ep;
		out->m_nodeIndex = BpInt(relocation);
		nodes[relocation].setElem(axis, out->m_value & 1, count);
		out++;
		count++;
	}
	if ((m_endPoints.m_capacityAndFlags & hkArray<hkBpEndPoint>::CAPACITY_MASK) < count)
	{
		int newCapacity = (m_endPoints.m_capacityAndFlags & hkArray<hkBpEndPoint>::CAPACITY_MASK) * 2;
		if (count >= newCapacity)
			newCapacity = count;
		hkArrayUtil::_reserveExactly(&m_endPoints, newCapacity, (int)sizeof(hkBpEndPoint));
	}
	m_endPoints.m_size = count;
}

// @ 0x010f56c0
void hk3AxisSweep::hkBpAxis::insert(hkBpNode* nodes, int nodeIndex, BpInt minPosition, BpInt maxPosition,
                                    BpInt& minInsertPositionOut, BpInt& maxInsertPositionOut)
{
	const int newSize = m_endPoints.getSize() + 2;
	if ((m_endPoints.m_capacityAndFlags & hkArray<hkBpEndPoint>::CAPACITY_MASK) < newSize)
	{
		int newCapacity = (m_endPoints.m_capacityAndFlags & hkArray<hkBpEndPoint>::CAPACITY_MASK) * 2;
		if (newSize >= newCapacity)
			newCapacity = newSize;
		hkArrayUtil::_reserveExactly(&m_endPoints, newCapacity, (int)sizeof(hkBpEndPoint));
	}
	hkBpEndPoint* p = m_endPoints.begin() + newSize - 3;
	m_endPoints.m_size = newSize;
	while (maxPosition <= p->m_value)
	{
		p[2] = p[0];
		p--;
	}
	p[2].m_value = maxPosition;
	p[2].m_nodeIndex = BpInt(nodeIndex);
	maxInsertPositionOut = BpInt(p - m_endPoints.begin() + 2);
	while (minPosition < p->m_value)
	{
		p[1] = p[0];
		p--;
	}
	p[1].m_nodeIndex = BpInt(nodeIndex);
	p[1].m_value = minPosition;
	minInsertPositionOut = BpInt(p - m_endPoints.begin() + 1);
}

// @ 0x010f5760
void hk3AxisSweep::reQuerySingleObject(hkBroadPhaseHandle* object, hkArray<hkBroadPhaseHandlePair>& pairsOut) const
{
	const int numNodes = m_nodes.getSize();
	hkLocalBuffer<hkUint32> bitFieldBuffer((numNodes >> 5) + 8);
	hkUint32* bitField = bitFieldBuffer.begin();
	const hkBpNode& node = m_nodes[object->m_id];
	setBitsBasedOnXInterval(numNodes, m_axis[0].m_endPoints[node.min_x].m_value, node, BpInt(object->m_id), bitField);
	{
		const hkUint32* bitEnd = bitField + (m_nodes.getSize() >> 5) + 1;
		const hkBpNode* nodes = m_nodes.begin();
		for (const hkUint32* p = bitField; p < bitEnd; p++, nodes += 32)
		{
			const hkBpNode* n = nodes;
			for (hkUint32 bits = *p; bits != 0; )
			{
				if ((bits & 0xff) == 0)
				{
					n += 8;
					bits >>= 8;
				}
				else
				{
					if (bits & 1)
					{
						if (!node.yzDisjoint(*n) && !n->isMarker())
							pairsOut.pushBack(hkBroadPhaseHandlePair(object, n->m_handle));
					}
					n++;
					bits >>= 1;
				}
			}
		}
	}
}

// @ 0x010f58e0
void hk3AxisSweep::addObject(hkBroadPhaseHandle* object, const hkAabb& aabb, hkArray<hkBroadPhaseHandlePair>& pairsOut)
{
	hkUint16 minI[4];
	{
		hkVector4 zero;
		zero.setZero4();
		hkVector4 mi;
		mi.setAdd4(aabb.m_min, m_offsetLow);
		mi.mul4(m_scale);
		mi.setMin4(mi, hk3AxisSweep_maxIntValue);
		mi.setMax4(mi, zero);
		hkConvertToUint16(mi, minI);
	}
	hkUint16 maxI[4];
	{
		hkVector4 zero;
		zero.setZero4();
		hkVector4 ma;
		ma.setAdd4(aabb.m_max, m_offsetHigh);
		ma.mul4(m_scale);
		ma.setMin4(ma, hk3AxisSweep_maxIntValue);
		ma.setMax4(ma, zero);
		hkConvertToUint16(ma, maxI);
	}
	BpInt lo[4];
	BpInt hi[4];
	lo[0] = BpInt(minI[0] & 0xfffe);
	lo[1] = BpInt(minI[1] & 0xfffe);
	lo[2] = BpInt(minI[2] & 0xfffe);
	hi[0] = BpInt(maxI[0] | 1);
	hi[1] = BpInt(maxI[1] | 1);
	hi[2] = BpInt(maxI[2] | 1);

	const int nodeIndex = m_nodes.getSize();
	if (m_nodes.m_size == (m_nodes.m_capacityAndFlags & hkArray<hkBpNode>::CAPACITY_MASK))
		hkArrayUtil::_reserveMore(&m_nodes, (int)sizeof(hkBpNode));
	hkBpNode* node = m_nodes.begin() + m_nodes.m_size;
	m_nodes.m_size++;

	m_axis[0].insert(m_nodes.begin(), nodeIndex, lo[0], hi[0], node->min_x, node->max_x);
	m_axis[1].insert(m_nodes.begin(), nodeIndex, lo[1], hi[1], node->min_y, node->max_y);
	m_axis[2].insert(m_nodes.begin(), nodeIndex, lo[2], hi[2], node->min_z, node->max_z);
	updateNodesAfterInsert(m_nodes.begin(), nodeIndex, *node);
	node->m_handle = object;
	object->m_id = nodeIndex;

	const int numNodes = m_nodes.getSize();
	hkLocalBuffer<hkUint32> bitFieldBuffer((numNodes >> 5) + 8);
	hkUint32* bitField = bitFieldBuffer.begin();
	setBitsBasedOnXInterval(numNodes, lo[0], *node, BpInt(nodeIndex), bitField);
	{
		const hkUint32* bitEnd = bitField + (m_nodes.getSize() >> 5) + 1;
		const hkBpNode* nodes = m_nodes.begin();
		for (const hkUint32* p = bitField; p < bitEnd; p++, nodes += 32)
		{
			const hkBpNode* n = nodes;
			for (hkUint32 bits = *p; bits != 0; )
			{
				if ((bits & 0xff) == 0)
				{
					n += 8;
					bits >>= 8;
				}
				else
				{
					if (bits & 1)
					{
						if (!node->yzDisjoint(*n))
						{
							if (!n->isMarker())
								pairsOut.pushBack(hkBroadPhaseHandlePair(object, n->m_handle));
							else
								n->getMarker(m_markers).m_overlappingObjects.pushBack(BpInt(nodeIndex));
						}
					}
					n++;
					bits >>= 1;
				}
			}
		}
	}
}

// @ 0x010f5e80
void hk3AxisSweep::removeObject(hkBroadPhaseHandle* object, hkArray<hkBroadPhaseHandlePair>& pairsOut)
{
	const int nodeIndex = object->m_id;
	const int numNodes = m_nodes.getSize();
	hkBpNode* node = m_nodes.begin() + nodeIndex;
	hkLocalBuffer<hkUint32> bitFieldBuffer((numNodes >> 5) + 8);
	hkUint32* bitField = bitFieldBuffer.begin();
	setBitsBasedOnXInterval(numNodes, m_axis[0].m_endPoints[node->min_x].m_value, *node, BpInt(nodeIndex), bitField);
	{
		const hkUint32* bitEnd = bitField + (m_nodes.getSize() >> 5) + 1;
		const hkBpNode* nodes = m_nodes.begin();
		for (const hkUint32* p = bitField; p < bitEnd; p++, nodes += 32)
		{
			const hkBpNode* n = nodes;
			for (hkUint32 bits = *p; bits != 0; )
			{
				if ((bits & 0xff) == 0)
				{
					n += 8;
					bits >>= 8;
				}
				else
				{
					if (bits & 1)
					{
						if (!node->yzDisjoint(*n))
						{
							if (!n->isMarker())
							{
								pairsOut.pushBack(hkBroadPhaseHandlePair(object, n->m_handle));
							}
							else
							{
								hkBpMarker& marker = n->getMarker(m_markers);
								const int index = marker.m_overlappingObjects.indexOf(BpInt(nodeIndex));
								marker.m_overlappingObjects.m_size--;
								marker.m_overlappingObjects[index] = marker.m_overlappingObjects[marker.m_overlappingObjects.m_size];
							}
						}
					}
					n++;
					bits >>= 1;
				}
			}
		}
	}

	m_axis[0].remove(node->min_x, node->max_x);
	m_axis[1].remove(node->min_y, node->max_y);
	m_axis[2].remove(node->min_z, node->max_z);
	updateNodesAfterDelete((hkBpNode*)object, numNodes, *node);

	if (nodeIndex < numNodes - 1)
	{
		const hkBpNode& lastNode = m_nodes[numNodes - 1];
		*node = lastNode;
		m_axis[0].m_endPoints[node->min_x].m_nodeIndex = BpInt(nodeIndex);
		m_axis[0].m_endPoints[node->max_x].m_nodeIndex = BpInt(nodeIndex);
		if (!node->isMarker())
		{
			m_axis[1].m_endPoints[node->min_y].m_nodeIndex = BpInt(nodeIndex);
			m_axis[1].m_endPoints[node->max_y].m_nodeIndex = BpInt(nodeIndex);
			m_axis[2].m_endPoints[node->min_z].m_nodeIndex = BpInt(nodeIndex);
			m_axis[2].m_endPoints[node->max_z].m_nodeIndex = BpInt(nodeIndex);
			node->m_handle->m_id = hkUint32(nodeIndex);
		}
		else
		{
			node->getMarker(m_markers).m_nodeIndex = BpInt(nodeIndex);
		}

		if (m_numMarkers != 0 && !node->isMarker())
		{
			const int shift = 16 - m_ld2NumMarkers;
			int startMarker = int(m_axis[0].m_endPoints[node->min_x].m_value) >> shift;
			if (startMarker > 0)
			{
				if (m_nodes[m_markers[startMarker - 1].m_nodeIndex].max_x > node->min_x)
					startMarker--;
			}
			const int endMarker = (int(m_axis[0].m_endPoints[node->max_x].m_value) >> shift) - 1;
			for (int i = startMarker; i <= endMarker; i++)
			{
				hkBpMarker& marker = m_markers[i];
				const int index = marker.m_overlappingObjects.indexOf(BpInt(numNodes - 1));
				marker.m_overlappingObjects[index] = BpInt(nodeIndex);
			}
		}
	}

	if ((m_nodes.m_capacityAndFlags & hkArray<hkBpNode>::CAPACITY_MASK) < numNodes - 1)
	{
		int newCapacity = (m_nodes.m_capacityAndFlags & hkArray<hkBpNode>::CAPACITY_MASK) * 2;
		if (numNodes - 1 >= newCapacity)
			newCapacity = numNodes - 1;
		hkArrayUtil::_reserveExactly(&m_nodes, newCapacity, (int)sizeof(hkBpNode));
	}
	m_nodes.m_size = numNodes - 1;
}

// @ 0x010f6250
void hk3AxisSweep::getAllAabbs(hkArray<hkAabb>& aabbsOut)
{
	if ((aabbsOut.m_capacityAndFlags & hkArray<hkAabb>::CAPACITY_MASK) < m_nodes.getSize())
		hkArrayUtil::_reserveExactly(&aabbsOut, m_nodes.getSize(), (int)sizeof(hkAabb));
	aabbsOut.m_size = m_nodes.getSize();
	for (int i = 0; i < m_nodes.getSize(); i++)
		getAabbFromNode(m_nodes[i], aabbsOut[i]);
}

// @ 0x010f62c0
void hk3AxisSweep::getAabb(hkBroadPhaseHandle* object, hkAabb& aabb) const
{
	getAabbFromNode(m_nodes[object->m_id], aabb);
}
