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
template <typename T>
struct hkArray
{
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
struct hkArrayUtil { static void _reserveExactly(void* arrayBase, int numElem, int elemSize); };   // 0x0107f4a0

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
	};

	virtual void addObjectBatch(hkArray<hkBroadPhaseHandle*>& addObjectList, hkArray<hkAabb>& addAabbList,
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
