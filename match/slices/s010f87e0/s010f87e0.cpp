// Slice s010f87e0: hk3AxisSweep::castAabb (Havok 3.1.0 broadphase).
//
// Sweeps an aabb (input.m_from +- m_halfExtents) along input.m_from -> input.m_to through the 3-axis sweep-and-prune
// broadphase (or through an aabb cache from calcAabbCache) and reports every node it touches to the collector,
// earliest first, honouring the collector's early-out fraction. See the comment at the function.
// Layouts are the 32-bit offsets seen in the binary; helper code shared with s010f9f30 (calcAabbCache).
// Flags: /O2 /MD /Gy /TP (x87 floats, no /EHsc).
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
typedef unsigned char hkUint8;
__declspec(align(16)) struct hkVector4
{
	hkReal x, y, z, w;
	__forceinline hkReal& operator()(int i) { return (&x)[i]; }
	__forceinline const hkReal& operator()(int i) const { return (&x)[i]; }
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
	__forceinline void setZero4() { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; }
	// index of the smallest of x, y, z (ties go to the later component)
	__forceinline int getIndexOfMinComponent3() const
	{
		if (x < y)
			return (x < z) ? 0 : 2;
		return (y < z) ? 1 : 2;
	}
};

namespace hkMath
{
	template <typename T> __forceinline T min2(T a, T b) { return (a < b) ? a : b; }
	template <typename T> __forceinline T fabs(T a) { return (a < T(0)) ? -a : a; }
}
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

static const hkReal HK_REAL_EPSILON = 1.1920929e-07f;   // 0x014a5ad0

// The broadphase resolution limit: 65532 in every component.
extern const hkVector4 hk3AxisSweep_maxIntValue;   // 0x015ba360

// For x in [0, 65532], x + 65536 has exponent 16, so its float bits >> 7 keep 16 mantissa bits.
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

template <typename T> static __forceinline const T* hkAddByteOffsetConst(const T* p, int offset)
{
	return (const T*)((const char*)p + offset);
}

// ---- hk3AxisSweep -----------------------------------------------------------------------------------------------
class hkBroadPhaseHandle;
class hkBroadPhaseCastCollector
{
public:
	virtual ~hkBroadPhaseCastCollector();
	virtual hkReal addBroadPhaseHandle(const hkBroadPhaseHandle* broadphaseHandle, int castIndex) = 0;   // +4
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
	struct hkCastAabbInput
	{
		hkVector4 m_from;              // +0x00
		hkVector4 m_to;                // +0x10
		hkVector4 m_halfExtents;       // +0x20
		const char* m_aabbCacheBuf;    // +0x30 (optional: three cached axes, see calcAabbCache)
	};
	hkUint32 m_type;                   // +8
};
class hk3AxisSweep : public hkBroadPhase
{
public:
	struct hkBpEndPoint
	{
		BpInt m_value;       // +0 (bit 0 set = max endpoint)
		BpInt m_nodeIndex;   // +2
	};
	struct hkBpNode
	{
		BpInt min_y, min_z, max_y, max_z, min_x, max_x;   // +0..+a
		hkBroadPhaseHandle* m_handle;                       // +c (bit 0 set = marker)
		__forceinline int isMarker() const { return int(*(const hkUint32*)&m_handle) & 1; }
	};
	struct hkBpMarker;
	struct hkBpAxis
	{
		hkArray<hkBpEndPoint> m_endPoints;
	};

	virtual void castAabb(const hkCastAabbInput& input, hkBroadPhaseCastCollector& collector) const;

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

static __forceinline void hkReportHandle(hkBroadPhaseCastCollector& collector, const hk3AxisSweep::hkBpNode& node, hkReal& earlyOut)
{
	if (!node.isMarker())
	{
		hkReal f = collector.addBroadPhaseHandle(node.m_handle, 0);
		earlyOut = hkMath::min2(earlyOut, f);
	}
}

// @ 0x010f87e0
// One byte per node collects an overlap bit per axis (1/2/4; 7 = overlapping). The start aabb's overlaps are
// built by scanning each axis from its nearer end, reported, and then the aabb is swept along the cast path by
// walking the endpoints of every axis in time order: a "max" event (the aabb's leading face passes an endpoint)
// toggles the axis bit and reports nodes reaching 7, a "min" event (the trailing face) toggles it back. Node 0's
// byte starts at 8 so reaching the sentinel endpoints ends that axis (time 2.0). Stops once the earliest pending
// event is later than the collector's early-out fraction.
void hk3AxisSweep::castAabb(const hkCastAabbInput& input, hkBroadPhaseCastCollector& collector) const
{
	hkVector4 aabbMin; aabbMin.setSub4(input.m_from, input.m_halfExtents);
	hkVector4 aabbMax; aabbMax.setAdd4(input.m_halfExtents, input.m_from);

	// the start aabb in broadphase integer space
	__declspec(align(16)) hkUint32 minI[4];
	__declspec(align(16)) hkUint32 maxI[4];
	{
		hkVector4 zero;
		zero.setZero4();
		hkVector4 mi;
		mi.setAdd4(aabbMin, m_offsetLow);
		mi.mul4(m_scale);
		mi.setMin4(mi, hk3AxisSweep_maxIntValue);
		mi.setMax4(mi, zero);
		hkConvertToInt(mi, minI);
		hkVector4 ma;
		ma.setAdd4(aabbMax, m_offsetLow);
		ma.mul4(m_scale);
		ma.setMin4(ma, hk3AxisSweep_maxIntValue);
		ma.setMax4(ma, zero);
		hkConvertToInt(ma, maxI);
	}

	hkTimerBeginList("Lthk3AxisSweep", "bitfield");

	hkLocalBuffer<hkUint8> bitFieldBuffer(m_nodes.getSize() + 16);
	hkUint8* bitField = bitFieldBuffer.begin();
	{
		hkUint32* p = (hkUint32*)bitField;
		for (int i = m_nodes.getSize() >> 4; i >= 0; i--)
		{
			p[0] = 0;
			p[1] = 0;
			p[2] = 0;
			p[3] = 0;
			p += 4;
		}
	}

	// per axis: mark the nodes overlapping the start aabb and remember where its min and max faces are
	const hkBpEndPoint* minPtr[3];
	const hkBpEndPoint* maxPtr[3];
	{
		const hkBpAxis* axis = input.m_aabbCacheBuf ? (const hkBpAxis*)input.m_aabbCacheBuf : &m_axis[0];
		hkUint8 mask = 1;
		for (int a = 0; a < 3; a++, axis++, mask <<= 1)
		{
			const hkBpEndPoint* ep = axis->m_endPoints.begin();
			int numEp = axis->m_endPoints.getSize();
			hkUint32 lo = minI[a];
			if (lo < ep[numEp >> 1].m_value)
			{
				// scan up from the start
				const hkBpEndPoint* e = ep + 1;
				const hkBpEndPoint* end4 = ep + numEp - 4;
				for (; e < end4; e += 4)
				{
					if (e[3].m_value > lo)
						break;
					bitField[e[0].m_nodeIndex] ^= mask;
					bitField[e[1].m_nodeIndex] ^= mask;
					bitField[e[2].m_nodeIndex] ^= mask;
					bitField[e[3].m_nodeIndex] ^= mask;
				}
				while (e->m_value <= lo)
				{
					bitField[e->m_nodeIndex] ^= mask;
					e++;
				}
				hkUint32 hi = maxI[a];
				minPtr[a] = e;
				while (e->m_value <= hi)
				{
					bitField[e->m_nodeIndex] ^= hkUint8((e->m_value & 1) - 1) & mask;
					e++;
				}
				maxPtr[a] = e;
			}
			else
			{
				// scan down from the end
				const hkBpEndPoint* start4 = ep + 4;
				const hkBpEndPoint* e = ep + numEp - 2;
				hkUint32 hi = maxI[a];
				for (; e >= start4; e -= 4)
				{
					if (e[-3].m_value <= hi)
						break;
					bitField[e[0].m_nodeIndex] ^= mask;
					bitField[e[-1].m_nodeIndex] ^= mask;
					bitField[e[-2].m_nodeIndex] ^= mask;
					bitField[e[-3].m_nodeIndex] ^= mask;
				}
				while (e->m_value > hi)
				{
					bitField[e->m_nodeIndex] ^= mask;
					e--;
				}
				maxPtr[a] = e + 1;
				while (e->m_value > lo)
				{
					bitField[e->m_nodeIndex] ^= hkUint8(-(e->m_value & 1)) & mask;
					e--;
				}
				minPtr[a] = e + 1;
			}
		}
	}

	hkTimerSplitList("StStartOverlaps");

	// report every node overlapping the start aabb on all three axes
	hkReal earlyOut = 1.0f;
	{
		const hkUint32* p = (const hkUint32*)bitField;
		const hkUint32* end = p + (m_nodes.getSize() >> 2) + 1;
		const hkBpNode* nodes = m_nodes.begin();
		for (; p < end; p++, nodes += 4)
		{
			// any byte == 7
			if (((*p + 0x01010101) & 0x08080808) == 0)
				continue;
			const hkUint8* b = (const hkUint8*)p;
			if (b[0] == 7)
				hkReportHandle(collector, nodes[0], earlyOut);
			if (b[1] == 7)
				hkReportHandle(collector, nodes[1], earlyOut);
			if (b[2] == 7)
				hkReportHandle(collector, nodes[2], earlyOut);
			if (b[3] == 7)
				hkReportHandle(collector, nodes[3], earlyOut);
		}
	}

	hkTimerSplitList("StWalk");

	// per axis: walking direction and the time (path fraction) at which each face reaches an endpoint value
	hkVector4 path; path.setSub4(input.m_to, input.m_from);
	int increment[3];         // endpoint step in bytes
	int minFlip[3];           // xor'ed into the endpoint's max bit on min-face events
	int maxFlip[3];           // ... on max-face events
	hkVector4 invDist;        // 1 / (path length in integer space), 0 if degenerate
	hkVector4 minOffset;      // time offset of the min face
	hkVector4 maxOffset;      // time offset of the max face
	for (int a = 0; a < 3; a++)
	{
		hkReal dist = path(a) * m_scale(a);
		hkReal absDist = (hkReal)fabs(dist);
		if (dist > 0.0f)
		{
			increment[a] = sizeof(hkBpEndPoint);
			minFlip[a] = 0;
			maxFlip[a] = 1;
		}
		else
		{
			increment[a] = -(int)sizeof(hkBpEndPoint);
			// walking backwards: the faces swap roles
			{ hkReal t = aabbMin(a); aabbMin(a) = aabbMax(a); aabbMax(a) = t; }
			{ const hkBpEndPoint* t = maxPtr[a]; maxPtr[a] = minPtr[a]; minPtr[a] = t; }
			{ hkUint32 t = maxI[a]; maxI[a] = minI[a]; minI[a] = t; }
			minPtr[a] = hkAddByteOffsetConst(minPtr[a], increment[a]);
			maxPtr[a] = hkAddByteOffsetConst(maxPtr[a], increment[a]);
			minFlip[a] = 1;
			maxFlip[a] = 0;
		}
		if (absDist < (m_offsetLow(a) + aabbMin(a)) * m_scale(a) * HK_REAL_EPSILON ||
		    absDist < (input.m_to(a) + m_offsetLow(a)) * m_scale(a) * HK_REAL_EPSILON)
		{
			invDist(a) = 0.0f;
			minOffset(a) = -2.0f;
			maxOffset(a) = -2.0f;
		}
		else
		{
			hkReal inv = 1.0f / dist;
			invDist(a) = inv;
			minOffset(a) = ((m_offsetLow(a) + aabbMin(a)) * m_scale(a) - m_intToFloatFloorCorrection) * inv;
			maxOffset(a) = ((aabbMax(a) + m_offsetLow(a)) * m_scale(a) - m_intToFloatFloorCorrection) * inv;
		}
	}

	hkVector4 minTime;
	hkVector4 maxTime;
	minTime.x = hkReal(int(minPtr[0]->m_value)) * invDist.x - minOffset.x;
	minTime.y = hkReal(int(minPtr[1]->m_value)) * invDist.y - minOffset.y;
	minTime.z = hkReal(int(minPtr[2]->m_value)) * invDist.z - minOffset.z;
	maxTime.x = hkReal(int(maxPtr[0]->m_value)) * invDist.x - maxOffset.x;
	maxTime.y = hkReal(int(maxPtr[1]->m_value)) * invDist.y - maxOffset.y;
	maxTime.z = hkReal(int(maxPtr[2]->m_value)) * invDist.z - maxOffset.z;
	bitField[0] = 8;

	int minAxis = minTime.getIndexOfMinComponent3();
	int maxAxis = maxTime.getIndexOfMinComponent3();
	while (1)
	{
		hkReal& tMax = maxTime(maxAxis);
		hkReal& tMin = minTime(minAxis);
		if (tMax < tMin)
		{
			// the leading face enters a node's interval (or leaves it, walking backwards)
			if (tMax > earlyOut)
				break;
			const hkBpEndPoint* ep;
			BpInt value;
			do
			{
				ep = maxPtr[maxAxis];
				int nodeIndex = ep->m_nodeIndex;
				hkUint8 bits = bitField[nodeIndex] ^ hkUint8(((ep->m_value & 1) ^ hkUint8(maxFlip[maxAxis])) << maxAxis);
				bitField[nodeIndex] = bits;
				if (bits >= 7)
				{
					if (nodeIndex == 0)
					{
						tMax = 2.0f;
						goto nextMax;
					}
					hkReportHandle(collector, m_nodes[nodeIndex], earlyOut);
				}
				value = ep->m_value;
				ep = hkAddByteOffsetConst(ep, increment[maxAxis]);
				maxPtr[maxAxis] = ep;
			} while (value == ep->m_value);
			tMax = hkReal(int(ep->m_value)) * invDist(maxAxis) - maxOffset(maxAxis);
nextMax:
			maxAxis = maxTime.getIndexOfMinComponent3();
		}
		else
		{
			// the trailing face leaves a node's interval
			if (tMin > earlyOut)
				break;
			hkUint8 flip = hkUint8(minFlip[minAxis]);
			const hkBpEndPoint* ep;
			BpInt value;
			do
			{
				ep = minPtr[minAxis];
				int nodeIndex = ep->m_nodeIndex;
				hkUint8 bits = bitField[nodeIndex] ^ hkUint8(((ep->m_value & 1) ^ flip) << minAxis);
				bitField[nodeIndex] = bits;
				if (bits > 8)
				{
					tMin = 2.0f;
					goto nextMin;
				}
				value = ep->m_value;
				ep = hkAddByteOffsetConst(ep, increment[minAxis]);
				minPtr[minAxis] = ep;
			} while (value == ep->m_value);
			tMin = hkReal(int(ep->m_value)) * invDist(minAxis) - minOffset(minAxis);
nextMin:
			minAxis = minTime.getIndexOfMinComponent3();
		}
	}

	hkTimerSplitList(hkMonitorListEndTag);
}
