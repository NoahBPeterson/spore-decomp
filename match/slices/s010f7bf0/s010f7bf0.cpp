// Slice s010f7bf0: hk3AxisSweep::castRay (Havok 3.1.0 broadphase).
//
// Casts several rays from one start point through the 3-axis sweep-and-prune broadphase (or an aabb cache) and
// reports every node each ray touches to that ray's collector, honouring each collector's early-out fraction.
// Layouts are the 32-bit offsets seen in the binary; helpers shared with s010f87e0 (castAabb).
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
	__forceinline void setMin4(const hkVector4& b)
	{
		if (!(x < b.x)) x = b.x;
		if (!(y < b.y)) y = b.y;
		if (!(z < b.z)) z = b.z;
		if (!(w < b.w)) w = b.w;
	}
	__forceinline void setMax4(hkReal b)
	{
		if (!(x > b)) x = b;
		if (!(y > b)) y = b;
		if (!(z > b)) z = b;
		if (!(w > b)) w = b;
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

template <typename T> static __forceinline T* hkAddByteOffset(T* p, int offset)
{
	return (T*)((char*)p + offset);
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
	struct hkCastRayInput
	{
		hkVector4 m_from;              // +0x00
		int m_numCasts;                // +0x10
		const hkVector4* m_toBase;     // +0x14
		int m_toStriding;              // +0x18
		const char* m_aabbCacheBuf;    // +0x1c (optional: three cached axes, see calcAabbCache)
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

	virtual void castRay(const hkCastRayInput& input, hkBroadPhaseCastCollector* collectorBase, int collectorStriding) const;

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


// index of the smallest of t[0..2] (ties go to the later one)
static __forceinline int hkIndexOfMin3(const hkReal* t)
{
	if (t[0] < t[1])
		return (t[0] < t[2]) ? 0 : 2;
	return (t[1] < t[2]) ? 1 : 2;
}

static __forceinline void hkReportHandle(hkBroadPhaseCastCollector* collector, const hk3AxisSweep::hkBpNode& node, int castIndex, hkReal& earlyOut)
{
	earlyOut = hkMath::min2(earlyOut, collector->addBroadPhaseHandle(node.m_handle, castIndex));
}

static __forceinline void hkReportToAll(const hkBroadPhase::hkCastRayInput& input, hkBroadPhaseCastCollector* collectorBase, int collectorStriding,
	const hk3AxisSweep::hkBpNode& node, hkReal* earlyOuts)
{
	hkBroadPhaseCastCollector* collector = collectorBase;
	for (int i = 0; i < input.m_numCasts; i++)
	{
		hkReportHandle(collector, node, i, earlyOuts[i]);
		collector = hkAddByteOffset(collector, collectorStriding);
	}
}

// @ 0x010f7bf0
// One byte per node: the low nibble holds the overlap bits (1/2/4 per axis) of the common start point, the high
// nibble (0x10/0x20/0x40) a working copy for the current ray. The start point's overlaps are built by scanning
// each axis from its nearer end (both nibbles at once), nodes containing it (0x77) are reported to every ray,
// and then each ray walks the endpoints of all three axes in time order, toggling the axis bit; a node reaching
// 0x7x is reported. Node 0's byte starts at 0x88 so reaching the sentinel endpoints ends that axis (time 2.0).
// After each ray but the last, the high nibbles are restored from the low ones.
void hk3AxisSweep::castRay(const hkCastRayInput& input, hkBroadPhaseCastCollector* collectorBase, int collectorStriding) const
{
	// the start point in broadphase integer space
	__declspec(align(16)) hkUint32 fromI[4];
	{
		hkVector4 fi;
		fi.setAdd4(input.m_from, m_offsetLow);
		fi.mul4(m_scale);
		fi.setMin4(hk3AxisSweep_maxIntValue);
		fi.setMax4(0.0f);
		hkConvertToInt(fi, fromI);
	}

	hkTimerBeginList("Lthk3AxisSweep", "memory");

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

	hkTimerSplitList("Stbitfield");

	// per axis: mark the nodes containing the start point and remember the first endpoint above it
	const hkBpEndPoint* startPtr[3];
	{
		const hkBpAxis* axis = input.m_aabbCacheBuf ? (const hkBpAxis*)input.m_aabbCacheBuf : &m_axis[0];
		hkUint8 mask = 0x11;
		for (int a = 0; a < 3; a++, axis++, mask <<= 1)
		{
			const hkBpEndPoint* ep = axis->m_endPoints.begin();
			int numEp = axis->m_endPoints.getSize();
			hkUint32 v = fromI[a];
			const hkBpEndPoint* e;
			if (v < ep[numEp >> 1].m_value)
			{
				// scan up from the start
				e = ep + 1;
				const hkBpEndPoint* end4 = ep + numEp - 4;
				for (; e < end4; e += 4)
				{
					if (e[3].m_value > v)
						break;
					bitField[e[0].m_nodeIndex] ^= mask;
					bitField[e[1].m_nodeIndex] ^= mask;
					bitField[e[2].m_nodeIndex] ^= mask;
					bitField[e[3].m_nodeIndex] ^= mask;
				}
				while (e->m_value <= v)
				{
					bitField[e->m_nodeIndex] ^= mask;
					e++;
				}
			}
			else
			{
				// scan down from the end
				const hkBpEndPoint* start4 = ep + 4;
				e = ep + numEp - 2;
				for (; e >= start4; e -= 4)
				{
					if (e[-3].m_value <= v)
						break;
					bitField[e[0].m_nodeIndex] ^= mask;
					bitField[e[-1].m_nodeIndex] ^= mask;
					bitField[e[-2].m_nodeIndex] ^= mask;
					bitField[e[-3].m_nodeIndex] ^= mask;
				}
				while (e->m_value > v)
				{
					bitField[e->m_nodeIndex] ^= mask;
					e--;
				}
				e++;
			}
			startPtr[a] = e;
		}
	}

	hkTimerSplitList("StStartOverlaps");

	// report every node containing the start point to every ray
	hkLocalBuffer<hkReal> earlyOutBuffer(input.m_numCasts);
	hkReal* earlyOuts = earlyOutBuffer.begin();
	for (int i = 0; i < input.m_numCasts; i++)
	{
		earlyOuts[i] = 1.0f;
	}
	{
		const hkUint32* p = (const hkUint32*)bitField;
		const hkUint32* end = p + (m_nodes.getSize() >> 2) + 1;
		const hkBpNode* nodes = m_nodes.begin();
		while (p < end)
		{
			// any byte == 0x77 (the buffer is padded, so reading up to two words past the end is fine)
			if (((p[0] + 0x01010101) & 0x08080808) == 0)
			{
				if (((p[1] + 0x01010101) & 0x08080808) == 0)
				{
					if (((p[2] + 0x01010101) & 0x08080808) == 0)
					{
						nodes += 12;
						p += 3;
					}
					else
					{
						nodes += 8;
						p += 2;
					}
				}
				else
				{
					nodes += 4;
					p += 1;
				}
				continue;
			}
			const hkUint8* b = (const hkUint8*)p;
			if (b[0] == 0x77 && !nodes[0].isMarker())
				hkReportToAll(input, collectorBase, collectorStriding, nodes[0], earlyOuts);
			if (b[1] == 0x77 && !nodes[1].isMarker())
				hkReportToAll(input, collectorBase, collectorStriding, nodes[1], earlyOuts);
			if (b[2] == 0x77 && !nodes[2].isMarker())
				hkReportToAll(input, collectorBase, collectorStriding, nodes[2], earlyOuts);
			if (b[3] == 0x77 && !nodes[3].isMarker())
				hkReportToAll(input, collectorBase, collectorStriding, nodes[3], earlyOuts);
			nodes += 4;
			p++;
		}
	}
	bitField[0] = 0x88;

	hkTimerSplitList("StWalk");

	const int numNodes = m_nodes.getSize();
	hkBroadPhaseCastCollector* collector = collectorBase;
	for (int i = 0; i < input.m_numCasts; i++)
	{
		hkReal earlyOut = earlyOuts[i];
		const hkBpEndPoint* curPtr[3];
		curPtr[0] = startPtr[0];
		curPtr[1] = startPtr[1];
		curPtr[2] = startPtr[2];

		hkVector4 to = *hkAddByteOffsetConst(input.m_toBase, i * input.m_toStriding);
		hkVector4 path; path.setSub4(to, input.m_from);

		// per axis: walking direction and the time (path fraction) at which the ray reaches an endpoint value
		int increment[3];      // endpoint step in bytes
		hkVector4 invDist;     // 1 / (path length in integer space), 0 if degenerate
		hkVector4 offset;      // time offset of the start point
		for (int a = 0; a < 3; a++)
		{
			hkReal dist = path(a) * m_scale(a);
			hkReal absDist = (hkReal)fabs(dist);
			hkReal fromF = (m_offsetLow(a) + input.m_from(a)) * m_scale(a);
			if (absDist < fromF * HK_REAL_EPSILON ||
			    absDist < (to(a) + m_offsetLow(a)) * m_scale(a) * HK_REAL_EPSILON)
			{
				invDist(a) = 0.0f;
				offset(a) = -2.0f;
			}
			else
			{
				increment[a] = sizeof(hkBpEndPoint);
				hkReal inv = 1.0f / dist;
				if (dist < 0.0f)
				{
					increment[a] = -(int)sizeof(hkBpEndPoint);
					curPtr[a]--;
				}
				invDist(a) = inv;
				offset(a) = (fromF - m_intToFloatFloorCorrection) * inv;
			}
		}

		hkReal time[3];
		time[0] = hkReal(int(curPtr[0]->m_value)) * invDist.x - offset.x;
		time[1] = hkReal(int(curPtr[1]->m_value)) * invDist.y - offset.y;
		time[2] = hkReal(int(curPtr[2]->m_value)) * invDist.z - offset.z;

		while (1)
		{
			int axis = hkIndexOfMin3(time);
			hkReal& t = time[axis];
			if (t > earlyOut)
				break;
			hkUint8 mask = hkUint8(0x10 << axis);
			const hkBpEndPoint* ep;
			const hkBpEndPoint* next;
			do
			{
				ep = curPtr[axis];
				int nodeIndex = ep->m_nodeIndex;
				hkUint8 bits = bitField[nodeIndex] ^ mask;
				bitField[nodeIndex] = bits;
				if (bits >= 0x70)
				{
					if (nodeIndex == 0)
					{
						t = 2.0f;
						goto nextAxis;
					}
					const hkBpNode& node = m_nodes[nodeIndex];
					if (!node.isMarker())
						hkReportHandle(collector, node, i, earlyOut);
				}
				next = hkAddByteOffsetConst(ep, increment[axis]);
				curPtr[axis] = next;
			} while (ep->m_value == next->m_value);
			t = hkReal(int(next->m_value)) * invDist(axis) - offset(axis);
nextAxis:;
		}

		// restore the working nibbles for the next ray
		if (i < input.m_numCasts - 1)
		{
			hkUint32* p = (hkUint32*)bitField;
			for (; p < (hkUint32*)bitField + (numNodes >> 2) + 1; p += 2)
			{
				hkUint32 a0 = p[0] & 0x0f0f0f0f;
				hkUint32 a1 = p[1] & 0x0f0f0f0f;
				p[0] = (a0 << 4) | a0;
				p[1] = (a1 << 4) | a1;
			}
		}
		collector = hkAddByteOffset(collector, collectorStriding);
	}

	hkTimerSplitList(hkMonitorListEndTag);
}
