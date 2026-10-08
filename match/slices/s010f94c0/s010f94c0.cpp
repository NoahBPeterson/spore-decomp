// Slice s010f94c0: hk3AxisSweep::hk3AxisSweep(worldMin, worldMax, numMarkers) (Havok 3.1.0 broadphase ctor).
//
// Sets up the empty sweep-and-prune structure: the node array gets node 0 (the sentinel that spans every endpoint),
// each axis array gets a 0 sentinel, `numMarkers` rounded to a power of two gives (N - 1) markers that are spread evenly
// over the integer range (each is a node with a min and a max endpoint on axis 0), and the three axes get a closing
// 0xfffd sentinel. Before that the float to int conversion is calibrated: a 23-step bisection between 10.0 and 11.0
// finds the smallest float whose (1.0f + x) converts to the integer 12, giving m_intToFloatFloorCorrection.
// Layouts are the 32-bit offsets seen in the binary. Flags: /O2 /MD /Gy /TP (x87 floats, no /EHsc).
#include "types.h"
#include <stddef.h>

typedef uint32_t hkUint32;
typedef uint16_t hkUint16;
typedef hkUint16 BpInt;
typedef float hkReal;

inline void* operator new(unsigned int, void* p) throw() { return p; }

namespace hkArrayUtil
{
	void __cdecl _reserveExactly(void* array, int n, int elemSize);   // 0x0107f4a0
	void __cdecl _reserveMore(void* array, int elemSize);             // 0x0107f530
}

template <typename T>
struct hkArray
{
	enum { CAPACITY_MASK = 0x3fffffff };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	hkArray() : m_data(0), m_size(0), m_capacityAndFlags((int)0x80000000) {}
	int getSize() const { return m_size; }
	int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
	__forceinline void reserve(int n)
	{
		int cap = getCapacity();
		if (cap < n)
		{
			int newCap = cap * 2;
			if (n >= newCap)
				newCap = n;
			hkArrayUtil::_reserveExactly(this, newCap, (int)sizeof(T));
		}
	}
	__forceinline T& expandOne()
	{
		if (m_size == getCapacity())
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		return m_data[m_size++];
	}
	__forceinline void pushBackUnchecked(const T& t) { m_data[m_size] = t; m_size++; }
};

class hkMemory
{
public:
	virtual void* allocate(int nbytes, int memClass);   // slot 0
};
extern hkMemory* hkMemory_s_instance;   // 0x016e4178

__declspec(align(16)) class hkVector4
{
public:
	hkReal x, y, z, w;
	__forceinline void setAll(hkReal r) { x = r; y = r; z = r; w = r; }
	__forceinline void setAdd4(const hkVector4& a, const hkVector4& b) { x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; w = a.w + b.w; }
	__forceinline void setSub4(const hkVector4& a, const hkVector4& b) { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
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
	__forceinline void setZero4() { x = y = z = w = 0.0f; }
};

// The broadphase resolution limit: 65532 in every component.
extern const hkVector4 hk3AxisSweep_maxIntValue;   // 0x015ba360

union hkFloatIntUnion4
{
	hkReal f[4];
	hkUint32 i[4];
};
static __forceinline void hkConvertToInt(const hkVector4& v, hkUint32* out)
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

class hkBroadPhaseHandle;

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
	hkBroadPhase() { m_referenceCount = 1; }
	hkUint32 m_type;              // +8
};

struct hkBpEndPoint
{
	BpInt m_value;       // +0 (bit 0 set = max endpoint)
	BpInt m_nodeIndex;   // +2
};
struct hkBpNode
{
	BpInt min_y, min_z, max_y, max_z, min_x, max_x;   // +0..+a
	hkBroadPhaseHandle* m_handle;                       // +c
};
struct hkBpMarker
{
	BpInt m_nodeIndex;                  // +0
	BpInt m_position;                   // +2
	hkArray<hkUint32> m_overlapping;    // +4
};
struct hkBpAxis
{
	hkArray<hkBpEndPoint> m_endPoints;
};

class hk3AxisSweep : public hkBroadPhase
{
public:
	hk3AxisSweep(const hkVector4& worldMin, const hkVector4& worldMax, int numMarkers);

	hkVector4 m_offsetLow;              // +0x10
	hkVector4 m_offsetHigh;             // +0x20
	hkVector4 m_scale;                  // +0x30
	hkArray<hkBpNode> m_nodes;          // +0x40
	hkBpAxis m_axis[3];                 // +0x4c
	int m_numMarkers;                   // +0x70
	int m_ld2NumMarkers;                // +0x74
	hkBpMarker* m_markers;              // +0x78
	hkReal m_intToFloatFloorCorrection; // +0x7c
};
typedef char hk3AxisSweep_layout_check[(offsetof(hk3AxisSweep, m_nodes) == 0x40 && offsetof(hk3AxisSweep, m_intToFloatFloorCorrection) == 0x7c) ? 1 : -1];

// @ 0x010f94c0
hk3AxisSweep::hk3AxisSweep(const hkVector4& worldMin, const hkVector4& worldMax, int numMarkers)
{
	if (numMarkers == 0)
		numMarkers = 1;
	int ld2 = -1;
	for (; 0 < numMarkers; numMarkers >>= 1)
		ld2++;

	m_nodes.reserve(255);

	m_offsetLow.setZero4();
	m_offsetHigh.setZero4();
	m_scale.setAll(1.0f);

	// calibrate the float to int conversion
	hkReal hi = 11.0f;
	hkReal lo = 10.0f;
	for (int it = 23; it != 0; it--)
	{
		hkReal mid = (hi + lo) * 0.5f;
		hkVector4 t;
		t.setAll(1.0f + mid);
		t.setAdd4(t, m_offsetHigh);
		t.mul4(m_scale);
		hkVector4 zero;
		zero.setZero4();
		t.setMin4(t, hk3AxisSweep_maxIntValue);
		t.setMax4(t, zero);
		hkUint32 ti[4];
		hkConvertToInt(t, ti);
		if ((hkUint16(ti[0]) | 1) < 12)
			lo = mid;
		else
			hi = mid;
	}
	m_intToFloatFloorCorrection = (hi + lo) * 0.5f - 11.0f;

	hkVector4 extent;
	extent.setSub4(worldMax, worldMin);
	m_scale.setAll(65532.0f);
	hkVector4 inv;
	inv.x = 1.0f / extent.x;
	inv.y = 1.0f / extent.y;
	inv.z = 1.0f / extent.z;
	inv.w = 0.0f;
	m_scale.mul4(inv);
	m_offsetLow.x = -worldMin.x;
	m_offsetLow.y = -worldMin.y;
	m_offsetLow.z = -worldMin.z;
	m_offsetLow.w = -worldMin.w;
	hkVector4 tol;
	tol.x = extent.x * 1.5258789e-05f;
	tol.y = extent.y * 1.5258789e-05f;
	tol.z = extent.z * 1.5258789e-05f;
	tol.w = extent.w * 1.5258789e-05f;
	m_offsetHigh.setAdd4(tol, m_offsetLow);
	m_scale.w = 0.0f;
	m_offsetLow.w = 0.0f;
	m_offsetHigh.w = 0.0f;

	// node 0: the sentinel node
	hkBpNode* node0 = &m_nodes.expandOne();
	node0->min_y = 0;
	node0->min_z = 0;
	node0->min_x = 0;

	const int markerCount = 1 << ld2;
	m_axis[0].m_endPoints.reserve(markerCount * 2 + 510);
	m_axis[1].m_endPoints.reserve(512);
	m_axis[2].m_endPoints.reserve(512);

	hkBpEndPoint first;
	first.m_value = 0;
	first.m_nodeIndex = 0;
	m_axis[0].m_endPoints.pushBackUnchecked(first);
	m_axis[1].m_endPoints.pushBackUnchecked(first);
	m_axis[2].m_endPoints.pushBackUnchecked(first);

	m_numMarkers = markerCount - 1;
	m_ld2NumMarkers = ld2;
	m_markers = 0;
	if (m_numMarkers != 0)
		m_markers = (hkBpMarker*)hkMemory_s_instance->allocate(m_numMarkers << 4, 0x1e);

	for (int i = 0; i < m_numMarkers; i++)
	{
		hkBpMarker* marker = new (&m_markers[i]) hkBpMarker;
		BpInt nodeIndex = (BpInt)m_nodes.getSize();
		BpInt position = (BpInt)((i + 1) << (16 - m_ld2NumMarkers));
		marker->m_nodeIndex = nodeIndex;
		marker->m_position = position;

		hkBpNode* node = &m_nodes.expandOne();
		node->min_x = (BpInt)m_axis[0].m_endPoints.getSize();
		hkBpEndPoint minEp;
		minEp.m_value = position;
		minEp.m_nodeIndex = nodeIndex;
		m_axis[0].m_endPoints.pushBackUnchecked(minEp);
		node->max_x = (BpInt)m_axis[0].m_endPoints.getSize();
		hkBpEndPoint maxEp = minEp;
		maxEp.m_value |= 1;
		m_axis[0].m_endPoints.pushBackUnchecked(maxEp);
		node->m_handle = (hkBroadPhaseHandle*)((i << 4) | 1);
		node->min_y = 0;
		node->min_z = 0;
		node->max_y = 1;
		node->max_z = 1;
	}

	node0->max_x = (BpInt)m_axis[0].m_endPoints.getSize();
	node0->max_y = (BpInt)m_axis[1].m_endPoints.getSize();
	node0->max_z = (BpInt)m_axis[2].m_endPoints.getSize();

	hkBpEndPoint last;
	last.m_value = 0xfffd;
	last.m_nodeIndex = 0;
	m_axis[0].m_endPoints.pushBackUnchecked(last);
	m_axis[1].m_endPoints.pushBackUnchecked(last);
	m_axis[2].m_endPoints.pushBackUnchecked(last);
}
