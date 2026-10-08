// flags: /O2 /MD /Gy /TP /vc71
// Slice s010f62e0: hk3AxisSweep::querySingleAabb (Havok 3.1.0 broadphase).
//
// The aabb is converted to broadphase integer space and every node overlapping it is reported as a
// hkBroadPhaseHandlePair (0, handle) appended to the output array: x axis via a bitfield toggled while
// walking the x endpoints (starting from the nearest marker), y/z via binary search of the endpoint arrays
// and a packed yzDisjoint test; marker nodes (handle bit 0) are skipped.
// Layouts are the 32-bit offsets seen in the binary (Havok 2013 hkp3AxisSweep.h used for names only).
#include "types.h"
#include <intrin.h>
#include <stddef.h>
#pragma intrinsic(__rdtsc)

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long, void*);

typedef uint32_t hkUint32;
typedef uint16_t hkUint16;
typedef hkUint16 BpInt;

inline void* operator new(unsigned int, void* p) throw() { return p; }

// ---- TLS globals ------------------------------------------------------------------------------------------------
extern unsigned long g_hkThreadMemoryTls;           // 0x016e4174
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorListEndTag[];            // 0x0143cd94 ("lt")

// ---- monitor stream timers ----------------------------------------------------------------------------------------
struct hkMonitorCommand { const char* m_command; hkUint32 m_time0; hkUint32 m_pad; };
struct hkMonitorListCommand { const char* m_command; hkUint32 m_time0; hkUint32 m_pad; const char* m_firstTimer; };

static __forceinline hkUint32 hkGetTicks32()
{
	volatile hkUint32 t = (hkUint32)__rdtsc();
	return t;
}
static __forceinline void hkTimerBeginList(const char* name, const char* first)
{
	void* end = TlsGetValue(g_hkMonitorStreamEndTls);
	if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end)
	{
		hkMonitorListCommand* c = (hkMonitorListCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls);
		c->m_command = name;
		c->m_firstTimer = first;
		c->m_time0 = hkGetTicks32();
		TlsSetValue(g_hkMonitorStreamCurrentTls, c + 1);
	}
}
static __forceinline void hkTimerSplitList(const char* name)
{
	void* end = TlsGetValue(g_hkMonitorStreamEndTls);
	if (TlsGetValue(g_hkMonitorStreamCurrentTls) < end)
	{
		hkMonitorCommand* c = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls);
		c->m_command = name;
		c->m_time0 = hkGetTicks32();
		TlsSetValue(g_hkMonitorStreamCurrentTls, c + 1);
	}
}

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
		if (next > m_stackEnd)
			return onStackOverflow(size);
		m_stackCurrent = next;
		return current;
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
struct hkArrayUtil { static void _reserveMore(void* arrayBase, int elemSize); };   // 0x0107f530
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
// 2 * x truncated (bit 0 is later used as the min/max endpoint parity).
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
class hkBroadPhaseHandle;
class hkBroadPhaseHandlePair
{
public:
	hkBroadPhaseHandle* m_a;   // +0 (always null here)
	hkBroadPhaseHandle* m_b;   // +4 (the node's handle)
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

		__forceinline int isMarker() const { return int(*(const hkUint32*)&m_handle) & 1; }
		__forceinline hkUint32 yzDisjoint(const hkBpNode& other) const
		{
			hkUint32 maxA = *(const hkUint32*)&max_y;
			hkUint32 minB = *(const hkUint32*)&other.min_y;
			hkUint32 maxB = *(const hkUint32*)&other.max_y;
			hkUint32 minA = *(const hkUint32*)&min_y;
			return ((maxB - minA) | (maxA - minB)) & 0x80008000;
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
		// Binary search: first endpoint in [start, end] whose value is >= value.
		const hkBpEndPoint* find(const hkBpEndPoint* start, const hkBpEndPoint* end, BpInt value) const;   // 0x010f4e10
	};

	virtual void querySingleAabb(const hkAabb& aabb, hkArray<hkBroadPhaseHandlePair>& pairsOut) const;

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

static __forceinline void hkToggleBit(hkUint32* bitField, int index)
{
	bitField[index >> 5] ^= 1 << (index & 0x1f);
}
static __forceinline void hkClearBit(hkUint32* bitField, int index)
{
	bitField[index >> 5] &= ~(1 << (index & 0x1f));
}

static __forceinline hkBroadPhaseHandlePair handlePair(const hk3AxisSweep::hkBpNode& n)
{
	hkBroadPhaseHandlePair p;
	p.m_a = 0;
	p.m_b = n.m_handle;
	return p;
}

// @ 0x010f62e0
void hk3AxisSweep::querySingleAabb(const hkAabb& aabb, hkArray<hkBroadPhaseHandlePair>& pairsOut) const
{
	hkTimerBeginList("LtquerySingleAabb", "marker");

	{
	int numNodes = m_nodes.getSize();
	hkLocalBuffer<hkUint32> bitFieldBuffer((numNodes >> 5) + 8);
	hkUint32* bitField = bitFieldBuffer.begin();
	{
		hkUint32* p = bitField;
		for (int i = numNodes >> 7; i >= 0; i--)
		{
			p[0] = 0;
			p[1] = 0;
			p[2] = 0;
			p[3] = 0;
			p += 4;
		}
	}

	// convert the aabb to broadphase integer space
	hkUint16 minI[4];
	hkUint16 maxI[4];
	{
		hkVector4 zero;
		zero.setZero4();
		hkVector4 mi;
		mi.setAdd4(aabb.m_min, m_offsetLow);
		mi.mul4(m_scale);
		mi.setMin4(mi, hk3AxisSweep_maxIntValue);
		mi.setMax4(mi, zero);
		hkConvertToUint16(mi, minI);
		hkVector4 ma;
		ma.setAdd4(aabb.m_max, m_offsetHigh);
		ma.mul4(m_scale);
		ma.setMin4(ma, hk3AxisSweep_maxIntValue);
		ma.setMax4(ma, zero);
		hkConvertToUint16(ma, maxI);
	}
	hkUint32 minX = minI[0] & 0xfffe;
	hkUint32 minY = minI[1] & 0xfffe;
	hkUint32 minZ = minI[2] & 0xfffe;
	hkUint32 maxX = maxI[0] | 1;
	hkUint32 maxY = maxI[1] | 1;
	hkUint32 maxZ = maxI[2] | 1;

	// x axis: toggle a bit for every node whose interval starts before minX (markers give a head start)
	{
		const hkBpEndPoint* ep = &m_axis[0].m_endPoints[1];
		if (m_numMarkers)
		{
			int markerIndex = int(minX) >> (16 - m_ld2NumMarkers);
			if (markerIndex > 0)
			{
				const hkBpMarker& marker = m_markers[markerIndex - 1];
				hkToggleBit(bitField, marker.m_nodeIndex);
				const BpInt* o = marker.m_overlappingObjects.begin();
				for (int i = marker.m_overlappingObjects.getSize() - 1; i >= 0; i--)
				{
					hkToggleBit(bitField, *o);
					o++;
				}
				const hkBpNode& markerNode = m_nodes[marker.m_nodeIndex];
				const hkBpEndPoint* end = &m_axis[0].m_endPoints[markerNode.max_x];
				for (const hkBpEndPoint* e = &m_axis[0].m_endPoints[markerNode.min_x + 1]; e < end; e++)
				{
					if (!(e->m_value & 1))
						hkClearBit(bitField, e->m_nodeIndex);
				}
				ep = &m_axis[0].m_endPoints[markerNode.min_x + 1];
			}
		}
		while (ep->m_value < minX)
		{
			hkToggleBit(bitField, ep->m_nodeIndex);
			ep++;
		}
		while (ep->m_value < maxX)
		{
			if (!(ep->m_value & 1))
				hkToggleBit(bitField, ep->m_nodeIndex);
			ep++;
		}
	}

	hkTimerSplitList("Styz-Axis");

	// y/z axes: endpoint index range of the query aabb
	hkBpNode refNode;
	{
		const hkBpAxis& axis = m_axis[1];
		const hkBpEndPoint* start = &axis.m_endPoints[1];
		const hkBpEndPoint* end = &axis.m_endPoints[axis.m_endPoints.getSize() - 2];
		refNode.min_y = BpInt(axis.find(start, end, BpInt(minY)) - axis.m_endPoints.begin());
		refNode.max_y = BpInt(axis.find(start, end, BpInt(maxY)) - 1 - axis.m_endPoints.begin());
	}
	{
		const hkBpAxis& axis = m_axis[2];
		const hkBpEndPoint* start = &axis.m_endPoints[1];
		const hkBpEndPoint* end = &axis.m_endPoints[axis.m_endPoints.getSize() - 2];
		refNode.min_z = BpInt(axis.find(start, end, BpInt(minZ)) - axis.m_endPoints.begin());
		refNode.max_z = BpInt(axis.find(start, end, BpInt(maxZ)) - 1 - axis.m_endPoints.begin());
	}

	hkTimerSplitList("StScanBitfield");

	{
		const hkUint32* bitEnd = bitField + (m_nodes.getSize() >> 5) + 1;
		const hkBpNode* nodes = m_nodes.begin();
		for (const hkUint32* p = bitField; p < bitEnd; p++, nodes += 32)
		{
			const hkBpNode* n = nodes;
			for (hkUint32 bits = *p; bits; bits >>= 4, n += 4)
			{
				if (!(bits & 0xf))
					continue;
				if ((bits & 1) && !refNode.yzDisjoint(n[0]) && !n[0].isMarker())
					pairsOut.pushBack(handlePair(n[0]));
				if ((bits & 2) && !refNode.yzDisjoint(n[1]) && !n[1].isMarker())
					pairsOut.pushBack(handlePair(n[1]));
				if ((bits & 4) && !refNode.yzDisjoint(n[2]) && !n[2].isMarker())
					pairsOut.pushBack(handlePair(n[2]));
				if ((bits & 8) && !refNode.yzDisjoint(n[3]) && !n[3].isMarker())
					pairsOut.pushBack(handlePair(n[3]));
			}
		}
	}
	}
	hkTimerSplitList(hkMonitorListEndTag);
}
