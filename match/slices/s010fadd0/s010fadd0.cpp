// flags: /O2 /MD /Gy /TP /vc71
// Slice s010fadd0: hk3AxisSweep::addObjectBatch (Havok 3.1.0 broadphase, 0x010fadd0, 1978 bytes).
//
// Grows the node array and the three endpoint arrays, converts every new aabb to broadphase integer space (the
// same inlined conversion as calcAabbCache), writes the unsorted min/max endpoints of each new node at the end of
// the axis arrays, quick-sorts the new endpoints per axis and merges them into the old ones (mergeBatch with a
// stack scratch buffer), shifts the marker nodes' y/z endpoint positions by the inserted endpoints, then builds a
// bitfield with one bit per new node and calls queryBatchAabbSub to report the new overlap pairs.
// Layouts are the 32-bit offsets seen in the binary (Havok 2013 hkp3AxisSweep.h used for names only).
#include "types.h"
#include <stddef.h>

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);

typedef uint32_t hkUint32;
typedef uint16_t hkUint16;
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
// hkArrayUtil::_reserveExactly (0x0107f4a0) is needed by hkArray<T>::insertAt, which is defined before hkArrayUtil.
void hkArrayReserveExactly(void* arrayBase, int numElem, int elemSize);

template <typename T>
class hkArray
{ public:
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
	T* begin() { return m_data; }
	const T* begin() const { return m_data; }
	T& operator[](int i) { return m_data[i]; }
	const T& operator[](int i) const { return m_data[i]; }
	__forceinline void pushBackUnchecked(const T& t) { m_data[m_size] = t; m_size++; }
	// Inserts every element of src before index (0x010fbb80 for hkArray<hkClass*>).
	void insertAt(int index, const hkArray<T>& src);
};

template <typename T>
struct hkLocalArray : hkArray<T>
{
	__forceinline explicit hkLocalArray(int n)
	{
		this->m_data = (T*)hkThreadMemory::getInstance().allocateStack(n * (int)sizeof(T));
		this->m_capacityAndFlags = n | (int)0x80000000;
		m_localMemory = this->m_data;
	}
	__forceinline ~hkLocalArray() { hkThreadMemory::getInstance().deallocateStack(m_localMemory); }
	T* m_localMemory;
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
typedef float hkReal;
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

// For x in [0, 65532], x + 65536 has exponent 16, so its float bits >> 7 keep 16 mantissa bits: the low 16 bits are
// 2 * x truncated (bit 0 is later used as the min/max endpoint parity). The vector is converted in place and then
// reinterpreted as four ints through a union copy.
union hkVectorIntUnion4
{
	hkVector4 v;
	hkUint32 i[4];
};
static __forceinline void hkConvertToUint16(hkVector4& v, hkUint16* out)
{
	v.x += 65536.0f;
	v.y += 65536.0f;
	v.z += 65536.0f;
	v.w += 65536.0f;
	hkVectorIntUnion4 u;
	u.v = v;
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
class hkBool
{
public:
	hkBool() {}
	hkBool(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
private:
	char m_bool;
};
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

// Growing an hkArray by n elements: reserve (doubling policy through _reserveExactly), then bump the size.
struct hkArrayUtil
{
	static void _reserveExactly(void* arrayBase, int numElem, int elemSize);   // 0x0107f4a0
	// Shrinks the array into its inplace storage (or a smaller block) once its size halves.
	static void _reduce(void* arrayBase, int elemSize, void* inplaceStorage, int inplaceCapacity);   // 0x0107f5d0
};

// Havok base library string helpers.
struct hkString { static void* memCpy(void* dst, const void* src, int n); };   // 0x0107f440

class hkClass;

class hk3AxisSweep : public hkBroadPhase
{
public:
	struct hkBpEndPoint
	{
		BpInt m_value;       // +0 (bit 0 set = max endpoint)
		BpInt m_nodeIndex;   // +2
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
		// Merges the sorted batch of numNew new endpoints (at the end of the array) into the sorted old ones.
		void mergeBatch(hkBpNode* nodes, int oldNumEndPoints, int numNew, int axis, hkBpEndPoint* tmpBuffer);   // 0x010f4f50
		// Drops every endpoint of a removed node, given the per-node relocation table of removeObjectBatch.
		void removeBatch(hkBpNode* nodes, int axis, const hkArray<int>& nodeRelocations);   // 0x010f5620
	};

	virtual void addObjectBatch(hkArray<hkBroadPhaseHandle*>& addObjectList, hkArray<hkAabb>& addAabbList,
	                            hkArray<hkBroadPhaseHandlePair>& newPairs);
	virtual void removeObjectBatch(hkArray<hkBroadPhaseHandle*>& removeObjectList,
	                               hkArray<hkBroadPhaseHandlePair>& newPairs);
	void queryBatchAabbSub(hkUint32* bitField, hkArray<hkBroadPhaseHandlePair>& pairsOut, hkBool addPairs) const;   // 0x010f9ac0

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

// hkAlgorithm::quickSortRecursive<hk3AxisSweep::hkBpEndPoint, hkAlgorithm::less<...> > (out-of-line template instance).
void quickSortRecursiveEndPoints(hk3AxisSweep::hkBpEndPoint* pArr, int d, int h,
                                 hkAlgorithm::less<hk3AxisSweep::hkBpEndPoint> cmpLess);   // 0x010f5480
namespace hkAlgorithm
{
	__forceinline void quickSort(hk3AxisSweep::hkBpEndPoint* pArr, int numElem, less<hk3AxisSweep::hkBpEndPoint> cmpLess)
	{
		if (numElem > 1)
			quickSortRecursiveEndPoints(pArr, 0, numElem - 1, cmpLess);
	}
}

static __forceinline void hkToggleBit(hkUint32* bitField, int index)
{
	int word = index >> 5;
	int bit = index & 0x1f;
	bitField[word] ^= (1 << bit);
}

template <typename T>
static __forceinline T* hkExpandBy(hkArray<T>& a, int n)
{
	int oldSize = a.m_size;
	int newSize = oldSize + n;
	int capacity = a.m_capacityAndFlags & hkArray<T>::CAPACITY_MASK;
	if (capacity < newSize)
	{
		int newCapacity = capacity * 2;
		if (newSize >= newCapacity)
			newCapacity = newSize;
		hkArrayUtil::_reserveExactly(&a, newCapacity, (int)sizeof(T));
	}
	a.m_size = newSize;
	return a.m_data + oldSize;
}

// @ 0x010fadd0
void hk3AxisSweep::addObjectBatch(hkArray<hkBroadPhaseHandle*>& addObjectList, hkArray<hkAabb>& addAabbList,
                                  hkArray<hkBroadPhaseHandlePair>& newPairs)
{
	if (addAabbList.getSize() < 1)
		return;

	// make room for the new nodes and for two new endpoints per object on every axis
	const int oldNumNodes = m_nodes.getSize();
	const int numObjects = addObjectList.getSize();
	hkExpandBy(m_nodes, numObjects);

	int oldNumEndPoints[3];
	oldNumEndPoints[0] = m_axis[0].m_endPoints.getSize();
	oldNumEndPoints[1] = m_axis[1].m_endPoints.getSize();
	oldNumEndPoints[2] = m_axis[2].m_endPoints.getSize();
	hkBpEndPoint* newEndPoints[3];
	newEndPoints[0] = hkExpandBy(m_axis[0].m_endPoints, numObjects * 2);
	newEndPoints[1] = hkExpandBy(m_axis[1].m_endPoints, numObjects * 2);
	newEndPoints[2] = hkExpandBy(m_axis[2].m_endPoints, numObjects * 2);

	// fill the unsorted endpoints of every new object
	for (int i = 0; i < numObjects; i++)
	{
		hkUint16 minI[8];
		{
			hkVector4 zero;
			zero.setZero4();
			hkVector4 mi;
			mi.setAdd4(addAabbList[i].m_min, m_offsetLow);
			mi.mul4(m_scale);
			mi.setMin4(mi, hk3AxisSweep_maxIntValue);
			mi.setMax4(mi, zero);
			hkConvertToUint16(mi, minI);
		}
		hkUint16 maxI[8];
		{
			hkVector4 zero;
			zero.setZero4();
			hkVector4 ma;
			ma.setAdd4(addAabbList[i].m_max, m_offsetHigh);
			ma.mul4(m_scale);
			ma.setMin4(ma, hk3AxisSweep_maxIntValue);
			ma.setMax4(ma, zero);
			hkConvertToUint16(ma, maxI);
		}
		hkUint32 lo[4];
		hkUint32 hi[4];
		lo[0] = minI[0] & 0xfffe;
		lo[1] = minI[1] & 0xfffe;
		lo[2] = minI[2] & 0xfffe;
		hi[0] = maxI[0] | 1;
		hi[1] = maxI[1] | 1;
		hi[2] = maxI[2] | 1;

		const int nodeIndex = oldNumNodes + i;
		hkBroadPhaseHandle* handle = addObjectList[i];
		m_nodes[nodeIndex].m_handle = handle;
		handle->m_id = nodeIndex;

		newEndPoints[0][i * 2].m_value = BpInt(lo[0]);
		newEndPoints[0][i * 2].m_nodeIndex = BpInt(nodeIndex);
		newEndPoints[0][i * 2 + 1].m_value = BpInt(hi[0]);
		newEndPoints[0][i * 2 + 1].m_nodeIndex = BpInt(nodeIndex);
		newEndPoints[1][i * 2].m_value = BpInt(lo[1]);
		newEndPoints[1][i * 2].m_nodeIndex = BpInt(nodeIndex);
		newEndPoints[1][i * 2 + 1].m_value = BpInt(hi[1]);
		newEndPoints[1][i * 2 + 1].m_nodeIndex = BpInt(nodeIndex);
		newEndPoints[2][i * 2].m_value = BpInt(lo[2]);
		newEndPoints[2][i * 2].m_nodeIndex = BpInt(nodeIndex);
		newEndPoints[2][i * 2 + 1].m_value = BpInt(hi[2]);
		newEndPoints[2][i * 2 + 1].m_nodeIndex = BpInt(nodeIndex);
	}

	const int numNewEndPoints = numObjects * 2;
	hkBpNode* nodes = m_nodes.begin();

	// sort the new endpoints of every axis
	for (int axis = 0; axis < 3; axis++)
		hkAlgorithm::quickSort(newEndPoints[axis], numNewEndPoints, hkAlgorithm::less<hkBpEndPoint>());

	// merge them into the old arrays
	{
		hkLocalBuffer<hkBpEndPoint> tmp(oldNumEndPoints[0]);
		for (int axis = 0; axis < 3; axis++)
			m_axis[axis].mergeBatch(nodes, oldNumEndPoints[axis], numNewEndPoints, axis, tmp.begin());
	}

	// the marker nodes store their y/z endpoint positions in max_y/max_z: shift them by the inserted endpoints
	if (m_numMarkers)
	{
		for (int i = 0; i < m_numMarkers; i++)
		{
			hkBpNode& markerNode = m_nodes[m_markers[i].m_nodeIndex];
			markerNode.max_y = BpInt(markerNode.max_y + numNewEndPoints);
			markerNode.max_z = BpInt(markerNode.max_z + numNewEndPoints);
		}
	}

	// find every overlap of the new objects (bitfield with one bit per new node)
	{
		int numNodes = m_nodes.getSize();
		int numBytes = numNodes >> 3;
		hkLocalBuffer<hkUint32> bitFieldBuffer((numNodes >> 5) + 8);
		hkUint32* bitField = bitFieldBuffer.begin();
		{
			hkUint32* p = bitField;
			for (int i = numBytes >> 4; i >= 0; i--)
			{
				hkUint32* q = p;
				p += 4;
				q[0] = 0;
				q[1] = 0;
				q[2] = 0;
				q[3] = 0;
			}
		}
		for (int i = 0; i < numObjects; i++)
			hkToggleBit(bitField, oldNumNodes + i);
		queryBatchAabbSub(bitField, newPairs, true);
	}
}

// ---- hkArray<T>::insertAt ---------------------------------------------------------------------------------------
// @ 0x010fbb80
template <>
void hkArray<hkClass*>::insertAt(int index, const hkArray<hkClass*>& src)
{
	const int numToInsert = src.m_size;
	const int newSize = m_size + numToInsert;
	int capacity = m_capacityAndFlags & CAPACITY_MASK;
	if (capacity < newSize)
	{
		int newCapacity = capacity * 2;
		if (newSize >= newCapacity)
			newCapacity = newSize;
		hkArrayReserveExactly(this, newCapacity, (int)sizeof(hkClass*));
	}
	const int numToMove = m_size - index;
	for (int i = numToMove - 1; i >= 0; i--)
		m_data[index + numToInsert + i] = m_data[index + i];
	for (int i = numToInsert - 1; i >= 0; i--)
		m_data[index + i] = src.m_data[i];
	m_size = newSize;
}

// ---- hk3AxisSweep::removeObjectBatch -----------------------------------------------------------------------------
// Mirror image of addObjectBatch: reports the overlaps the removed objects still have, marks the removed nodes with the
// address of a stack sentinel, compacts the node array (relocating the handles/markers that were moved, keeping a
// per-node relocation table) and then rebuilds the three endpoint arrays with hkBpAxis::removeBatch. The marker nodes'
// y/z endpoint positions shrink by the two removed endpoints each, and their overlap lists are remapped.
// @ 0x010fb590
void hk3AxisSweep::removeObjectBatch(hkArray<hkBroadPhaseHandle*>& removeObjectList,
                                     hkArray<hkBroadPhaseHandlePair>& newPairs)
{
	const int numNodes = m_nodes.getSize();
	const int numRemove = removeObjectList.getSize();

	// find every overlap the removed objects are still part of (bitfield with one bit per removed node)
	{
		hkLocalBuffer<hkUint32> bitFieldBuffer((numNodes >> 5) + 8);
		hkUint32* bitField = bitFieldBuffer.begin();
		{
			hkUint32* p = bitField;
			for (int i = (numNodes >> 3) >> 4; i >= 0; i--)
			{
				hkUint32* q = p;
				p += 4;
				q[0] = 0;
				q[1] = 0;
				q[2] = 0;
				q[3] = 0;
			}
		}
		for (int i = 0; i < numRemove; i++)
			hkToggleBit(bitField, removeObjectList[i]->m_id);
		queryBatchAabbSub(bitField, newPairs, false);
	}

	// mark the removed nodes with the address of a stack sentinel and clear their handle ids
	int removedSentinel = 0;
	for (int i = 0; i < numRemove; i++)
	{
		hkBroadPhaseHandle* handle = removeObjectList[i];
		m_nodes[handle->m_id].m_handle = (hkBroadPhaseHandle*)&removedSentinel;
		handle->m_id = 0;
	}
	hkBroadPhaseHandle* const sentinel = (hkBroadPhaseHandle*)&removedSentinel;

	// compact the node array from both ends, recording where every node went
	int* relocationRaw = (int*)hkThreadMemory::getInstance().allocateStack(numNodes * (int)sizeof(int));
	hkArray<int> relocations(relocationRaw, numNodes, numNodes);

	int numKept = 0;
	int lastNode = m_nodes.getSize() - 1;
	while (numKept <= lastNode)
	{
		if (m_nodes[lastNode].m_handle == sentinel)
		{
			relocations[lastNode] = -1;
			lastNode--;
			continue;
		}
		if (m_nodes[numKept].m_handle == sentinel)
		{
			m_nodes[numKept] = m_nodes[lastNode];
			relocations[lastNode] = numKept;
			relocations[numKept] = -1;
			hkBroadPhaseHandle* handle = m_nodes[numKept].m_handle;
			const hkUint32 handleBits = (hkUint32)handle;
			if ((handleBits & 1) == 0)
				handle->m_id = (hkUint32)numKept;
			else
				m_markers[handleBits >> 1].m_nodeIndex = BpInt(numKept);
		}
		else
		{
			relocations[numKept] = numKept;
		}
		numKept++;
	}

	const int newNumNodes = lastNode + 1;
	int capacity = m_nodes.m_capacityAndFlags & hkArray<hkBpNode>::CAPACITY_MASK;
	if (capacity < newNumNodes)
	{
		int newCapacity = capacity * 2;
		if (newNumNodes >= newCapacity)
			newCapacity = newNumNodes;
		hkArrayUtil::_reserveExactly(&m_nodes, newCapacity, (int)sizeof(hkBpNode));
	}
	m_nodes.m_size = newNumNodes;
	hkBpNode* nodes = m_nodes.begin();

	for (int axis = 0; axis < 3; axis++)
		m_axis[axis].removeBatch(nodes, axis, relocations);

	// the marker nodes store their y/z endpoint positions in max_y/max_z: shift them by the removed endpoints
	if (m_numMarkers)
	{
		const int numRemovedEndPoints = numRemove * 2;
		for (int i = 0; i < m_numMarkers; i++)
		{
			hkBpNode& markerNode = m_nodes[m_markers[i].m_nodeIndex];
			markerNode.max_y = BpInt(markerNode.max_y - numRemovedEndPoints);
			markerNode.max_z = BpInt(markerNode.max_z - numRemovedEndPoints);
			hkArray<BpInt>& overlaps = m_markers[i].m_overlappingObjects;
			for (int k = 0; k < overlaps.getSize(); k++)
				overlaps[k] = BpInt(relocations[overlaps[k]]);
		}
	}

	hkThreadMemory::getInstance().deallocateStack(relocationRaw);
}

// ---- Havok AI agent neighbourhood machine ------------------------------------------------------------------------
// Layouts are the 32-bit offsets seen in the binary: every agent starts with a kind byte (2/4/6 dispatch the shape
// filter and the time bookkeeping on different sub-objects), the world data block holds two 32x32 grids of agent type
// bytes and a table of 0x34-byte per-type callbacks (shape collection filter, tim invalidation, time warp).

// An agent as seen through its vtable: the third slot returns the row/column index it occupies in the machine grids.
struct hkAgentNnAgent
{
	virtual void nn0();
	virtual void nn1();
	virtual int getShapeType();          // +0x08
};

// One 0x34-byte entry of the per-agent-type callback table.
struct hkAgentNnAgentTypeEntry
{
	void* m_updateShapeCollectionFilter;  // +0x00
	void* m_invalidateTim;               // +0x04
	void* m_warpTime;                    // +0x08
	unsigned char m_pad0c[0x0c];         // +0x0c
	hkUint32 m_type;                     // +0x18 (2 == solid)
	unsigned char m_pad1c[0x18];         // +0x1c
};
typedef char hkAgentNnAgentTypeEntry_check[(sizeof(hkAgentNnAgentTypeEntry) == 0x34
	&& offsetof(hkAgentNnAgentTypeEntry, m_type) == 0x18) ? 1 : -1];

// The machine's data block.
struct hkAgentNnMachineWorld
{
	unsigned char m_pad000[0x190];              // +0x000
	unsigned char m_cellState[0x400];           // +0x190 per-cell state byte (index into m_filterFlags)
	unsigned char m_pad590[0x410];              // +0x590
	unsigned char m_filterFlags[0x4f4];         // +0x9a0 0x14-byte filter entries
	unsigned char m_cellsPlain[0x400];          // +0xe94 32x32 grid of agent type bytes
	unsigned char m_cellsFiltered[0x400];       // +0x1294 32x32 grid of filtered agent type bytes
	unsigned char m_pad1694[0x18];              // +0x1694
	hkAgentNnAgentTypeEntry m_agentTypes[1];    // +0x16ac per-agent-type callbacks
};
typedef char hkAgentNnMachineWorld_check[(offsetof(hkAgentNnMachineWorld, m_cellsPlain) == 0xe94
	&& offsetof(hkAgentNnMachineWorld, m_cellsFiltered) == 0x1294
	&& offsetof(hkAgentNnMachineWorld, m_agentTypes) == 0x16ac) ? 1 : -1];

// The machine context handed to the callbacks (only the first member and the grid selector are used here).
struct hkAgentNnMachineContext
{
	hkAgentNnMachineWorld* m_world;      // +0x00
	hkUint32 m_pad04[2];                 // +0x04
	unsigned char m_useFilteredGrid;     // +0x0c
};

// The agent entry the callbacks work on.
struct hkAgentNnAgentEntry
{
	unsigned char m_agentKind;           // +0x00 (2/4/6)
	unsigned char m_agentType;           // +0x01 (index into m_agentTypes)
	unsigned char m_pad02[0x12];         // +0x02
	hkUint32 m_userData0;                // +0x14
	hkUint32 m_userData1;                // +0x18
	float m_time;                        // +0x1c (-1.0f == invalid)
	hkVector4 m_position;                // +0x20
	hkVector4 m_positionFiltered;        // +0x30
};
typedef char hkAgentNnAgentEntry_check[(offsetof(hkAgentNnAgentEntry, m_time) == 0x1c
	&& offsetof(hkAgentNnAgentEntry, m_position) == 0x20
	&& offsetof(hkAgentNnAgentEntry, m_positionFiltered) == 0x30) ? 1 : -1];

typedef void (__cdecl* hkAgentNnShapeFilterFn)(hkAgentNnAgentEntry*, void*, hkUint32, hkUint32,
                                              hkAgentNnMachineContext*);
typedef void (__cdecl* hkAgentNnTimFn)(hkAgentNnAgentEntry*, void*, hkAgentNnMachineContext*);
typedef void (__cdecl* hkAgentNnWarpTimeFn)(hkAgentNnAgentEntry*, void*, float, float, hkAgentNnMachineContext*);

// Both agents must agree on the cell type; returns it and whether that cell counts as a solid contact.
// @ 0x010fb8f0
extern "C" void hkAgentNnMachine_GetAgentType(hkAgentNnAgent* const* agentA, hkAgentNnAgent* const* agentB,
                                              hkAgentNnMachineContext* context, hkUint32* typeOut,
                                              hkUint32* solidOut)
{
	hkAgentNnMachineWorld* world = context->m_world;
	const int rowA = (*agentA)->getShapeType();
	const int rowB = (*agentB)->getShapeType();
	const int cell = rowA * 0x20 + rowB;
	const int type = context->m_useFilteredGrid ? world->m_cellsFiltered[cell] : world->m_cellsPlain[cell];
	hkUint32 solid = hkUint32(world->m_agentTypes[type].m_type == 2);
	if (type == 1)
		solid = hkUint32(world->m_filterFlags[world->m_cellState[cell] * 0x14] != 0);
	*solidOut = solid;
	if (solid)
	{
		const int cellSwapped = rowB * 0x20 + rowA;
		*typeOut = hkUint32(context->m_useFilteredGrid ? world->m_cellsFiltered[cellSwapped]
		                                               : world->m_cellsPlain[cellSwapped]);
	}
	else
	{
		*typeOut = hkUint32(type);
	}
}

// Lets the agent's type refresh its shape collection filter for the sub-object matching its kind.
// @ 0x010fb9c0
extern "C" void hkAgentNnMachine_UpdateShapeCollectionFilter(hkAgentNnAgentEntry* agent,
                                                            hkAgentNnMachineContext* context)
{
	void* filterTarget;
	switch (agent->m_agentKind)
	{
	case 2:
	case 6:
		filterTarget = &agent->m_position;
		break;
	case 4:
		filterTarget = &agent->m_positionFiltered;
		break;
	default:
		return;
	}
	void* filter = context->m_world->m_agentTypes[agent->m_agentType].m_updateShapeCollectionFilter;
	if (filter)
		((hkAgentNnShapeFilterFn)filter)(agent, filterTarget, agent->m_userData0, agent->m_userData1, context);
}

// InvalidateTim on the agent's type: kind 4 also clears the time and the position.
// @ 0x010fba10
extern "C" void hkAgentNnMachine_InvalidateTimInAgent(hkAgentNnAgentEntry* agent, hkAgentNnMachineContext* context)
{
	switch (agent->m_agentKind)
	{
	case 2:
	case 6:
		{
			hkAgentNnTimFn invalidate =
				(hkAgentNnTimFn)context->m_world->m_agentTypes[agent->m_agentType].m_invalidateTim;
			if (invalidate)
				invalidate(agent, &agent->m_position, context);
		}
		break;
	case 4:
		{
			agent->m_time = -1.0f;
			agent->m_position.setZero4();
			hkAgentNnTimFn invalidate =
				(hkAgentNnTimFn)context->m_world->m_agentTypes[agent->m_agentType].m_invalidateTim;
			if (invalidate)
				invalidate(agent, &agent->m_positionFiltered, context);
		}
		break;
	}
}

// WarpTime on the agent's type; kind 4 moves its own time forward (or invalidates it when the time does not match).
// @ 0x010fba90
extern "C" void hkAgentNnMachine_WarpTimeInAgent(hkAgentNnAgentEntry* agent, float oldTime, float newTime,
                                                 hkAgentNnMachineContext* context)
{
	void* warpTarget;
	switch (agent->m_agentKind)
	{
	case 2:
	case 6:
		warpTarget = &agent->m_position;
		break;
	case 4:
		if (agent->m_time == oldTime)
			agent->m_time = newTime;
		else
			agent->m_time = -1.0f;
		warpTarget = &agent->m_positionFiltered;
		break;
	default:
		return;
	}
	hkAgentNnWarpTimeFn warp =
		(hkAgentNnWarpTimeFn)context->m_world->m_agentTypes[agent->m_agentType].m_warpTime;
	if (warp)
		warp(agent, warpTarget, oldTime, newTime, context);
}

// ---- pair tables -------------------------------------------------------------------------------------------------
// A pair table is a graph node: it owns a list of 8-byte references, each pointing back at the record that owns the
// reference (+0) and at the other side of the pair (+4).
struct hkPairRef
{
	void* m_record;      // +0x00
	void* m_peer;        // +0x04
};
struct hkPairTable
{
	unsigned char m_pad00[0x24];   // +0x00
	hkPairRef* m_refs;             // +0x24
	int m_numRefs;                 // +0x28
};

// Finds the record of the pair (a, b) by scanning the shorter reference list for the other side.
// @ 0x010fbb30
void* hkPairTableFindPeer(hkPairTable* tableA, hkPairTable* tableB)
{
	hkPairTable* peer;
	hkPairTable* searched;
	if (tableA->m_numRefs <= tableB->m_numRefs)
	{
		searched = tableA;
		peer = tableB;
	}
	else
	{
		searched = tableB;
		peer = tableA;
	}
	for (int i = 0; i < searched->m_numRefs; i++)
	{
		if (searched->m_refs[i].m_peer == peer)
			return searched->m_refs[i].m_record;
	}
	return 0;
}

// ---- variable-size record block array ----------------------------------------------------------------
// A block array: m_data holds one heap block per record, the records are packed back to back inside those blocks and
// m_usedBytes counts the free tail of the last block. Removing a record moves the last record over it and updates the
// two pair tables the moved record is referenced from.
struct hkPairRecord
{
	unsigned char m_pad00[0x0c];   // +0x00
	hkUint16 m_refIndexA;          // +0x0c
	hkUint16 m_refIndexB;          // +0x0e
	unsigned char m_pad10[0x04];   // +0x10
	hkPairTable* m_tableA;         // +0x14
	hkPairTable* m_tableB;         // +0x18
};
typedef char hkPairRecord_check[(offsetof(hkPairRecord, m_tableA) == 0x14
	&& offsetof(hkPairRecord, m_tableB) == 0x18) ? 1 : -1];

struct hkRecordBlockArray
{
	void** m_data;                 // +0x00
	int m_size;                    // +0x04
	int m_capacityAndFlags;        // +0x08
	int m_inplaceStorage;          // +0x0c
	int m_usedBytes;               // +0x10
	hkUint16 m_recordSize;         // +0x14
	hkUint16 m_chunkSize;          // +0x16
};
typedef char hkRecordBlockArray_check[(offsetof(hkRecordBlockArray, m_usedBytes) == 0x10
	&& offsetof(hkRecordBlockArray, m_chunkSize) == 0x16) ? 1 : -1];

// @ 0x010fbc50
void hkRecordBlockArrayRemove(hkRecordBlockArray* blocks, hkPairRecord* record)
{
	char* lastRecord = (char*)blocks->m_data[blocks->m_size - 1] - blocks->m_recordSize
	                 + blocks->m_usedBytes;
	if ((char*)record != lastRecord)
	{
		hkString::memCpy(record, lastRecord, blocks->m_recordSize);
		record->m_tableA->m_refs[record->m_refIndexA].m_record = record;
		record->m_tableB->m_refs[record->m_refIndexB].m_record = record;
	}
	blocks->m_usedBytes -= blocks->m_recordSize;
	if (blocks->m_usedBytes == 0)
	{
		const int oldSize = blocks->m_size;
		void* chunk = blocks->m_data[oldSize - 1];
		blocks->m_size = oldSize - 1;
		const int capacity = blocks->m_capacityAndFlags & hkArray<int>::CAPACITY_MASK;
		if (blocks->m_capacityAndFlags >= 0 && (oldSize < 1 || oldSize * 2 < capacity))
			hkArrayUtil::_reduce(blocks, (int)sizeof(void*), &blocks->m_inplaceStorage, 1);
		hkThreadMemory::getInstance().deallocateChunk(chunk, blocks->m_chunkSize, 0x24);
		blocks->m_usedBytes = blocks->m_chunkSize;
	}
}
