// Havok (Spore build) -- slice s01119e00: hkGeomConvexHullBuilder / hkArray helpers
//
//   0x01119E00  remap+collect worker used by stitchHulls
//   0x01119F00  hkArray<T>::operator=
//   0x01119FA0  emit-face-candidates helper
//   0x0111A060  hkGeomConvexHullBuilder::buildPlaneEquations (5-argument overload)
//   0x0111A0F0  hkGeomConvexHullBuilder::removeUnusedVertices
//   0x0111A290  hkGeomConvexHullBuilder::stitchHulls
//   0x0111A700  hkGeomConvexHullBuilder::removeCoPlanarNeighbours
//   0x0111A8A0  hkGeomConvexHullBuilder::validateNeighbours
//   0x0111A9E0  hkGeomConvexHullBuilder::isValidEdgeCheck
//
// Names come from symbols/havok_names.txt (the Havok identical-code symbol database).
// Self-contained single TU: hkGeomHull / hkGeomEdge / hkArray / hkVector4 are declared
// here so the whole slice scores from one compile.
#include "types.h"
#include <math.h>

#define NULL 0
#define DONT_DEALLOCATE_FLAG_CONST ((int)0x80000000)

#ifdef _WIN32
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
#endif

// ---------------------------------------------------------------------------
// Havok base types
// ---------------------------------------------------------------------------

class hkBool
{
public:
	hkBool() {}
	hkBool(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
	char m_bool;
};

enum { HK_MEMORY_CLASS_ARRAY = 0x14 };

extern unsigned long g_hkThreadMemoryTlsIndex;   // 0x016E4174 (hkThreadMemory TLS slot)

class hkThreadMemory
{
public:
	struct Stack
	{
		char* m_current;   // +0x20
		Stack* m_prev;     // +0x24
		char* m_base;      // +0x28
		char* m_end;       // +0x2c
	};
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void* onStackOverflow(int nbytes);   // slot 3 (+0xc)
	virtual void onStackUnderflow(void* p);      // slot 4 (+0x10)

	uint32_t m_pad4[7];
	Stack m_stack;   // +0x20

	void  deallocateChunk(void* p, int nbytes, int memClass);   // 0x0107DB10
	void* allocateChunk(int nbytes, int memClass);              // 0x0107DAA0
	static hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }

	inline void* allocateStack(int nbytesin)
	{
		int actualBytes = (nbytesin + 16) & ~15;
		char* p = m_stack.m_current;
		char* end = p + actualBytes;
		if (end <= m_stack.m_end)
		{
			m_stack.m_current = end;
			return p;
		}
		return onStackOverflow(actualBytes);
	}
	inline void deallocateStack(void* p)
	{
		m_stack.m_current = (char*)p;
		if (p == m_stack.m_base)
			onStackUnderflow(p);
	}
};

// ---------------------------------------------------------------------------
// hkArray
// ---------------------------------------------------------------------------

struct hkArrayUtil
{
	static void _reserveExactly(void* array, int numElem, int sizeElem);   // 0x0107F4A0
	static void _reserveMore(void* array, int sizeElem);                   // 0x0107F530
};

template <class T>
class hkArray
{
public:
	enum { CAPACITY_MASK = 0x3FFFFFFF, DONT_DEALLOCATE_FLAG = (int)0x80000000 };
	T*  m_data;
	int m_size;
	int m_capacityAndFlags;

	hkArray() : m_data(0), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}
	hkArray(T* buffer, int size, int capacity)
		: m_data(buffer), m_size(size), m_capacityAndFlags(capacity | DONT_DEALLOCATE_FLAG) {}
	~hkArray()
	{
		if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
			hkThreadMemory::getInstance().deallocateChunk(m_data, getCapacity() * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
	}
	int   getSize() const { return m_size; }
	int   getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
	T&    operator[](int i) { return m_data[i]; }
	const T& operator[](int i) const { return m_data[i]; }
	T*    begin() { return m_data; }
	void  clear() { m_size = 0; }

	void reserveFor(int n)
	{
		const int cap = getCapacity();
		if (cap < n)
		{
			int cap2 = cap + cap;
			int newSize = (n < cap2) ? cap2 : n;
			hkArrayUtil::_reserveExactly(this, newSize, (int)sizeof(T));
		}
	}
	void setSize(int n)
	{
		reserveFor(n);
		m_size = n;
	}
	T* expandBy(int n)
	{
		int oldSize = m_size;
		int newSize = oldSize + n;
		reserveFor(newSize);
		m_size = newSize;
		return m_data + oldSize;
	}
	T& expandOne() { return *expandBy(1); }
	T& pushBackUnchecked() { return m_data[m_size++]; }
	void pushBack(const T& e)
	{
		if (m_size == getCapacity())
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		m_data[m_size++] = e;
	}

	hkArray<T>& operator=(const hkArray<T>& other);   // 0x01119F00
};

// Set up a stack-buffer hkArray (no heap allocation, capacity = DONT_DEALLOCATE | count).
template <class T>
static void setupStackArray(hkArray<T>& a, char* buf, int count)
{
	a.m_data = (T*)buf;
	a.m_size = 0;
	a.m_capacityAndFlags = (int)0x80000000 | count;
}

// Force emission of hkArray<hkGeomEdge>::operator= (0x01119F00).
struct hkGeomEdge;
template hkArray<hkGeomEdge>& hkArray<hkGeomEdge>::operator=(const hkArray<hkGeomEdge>&);

// @ 0x01119f00
template <class T>
hkArray<T>& hkArray<T>::operator=(const hkArray<T>& other)
{
	hkThreadMemory& mem = hkThreadMemory::getInstance();
	if (getCapacity() < other.m_size)
	{
		if (m_capacityAndFlags >= 0)
			mem.deallocateChunk(m_data, getCapacity() * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
		m_data = (T*)mem.allocateChunk(other.m_size * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
		m_capacityAndFlags = (m_capacityAndFlags & 0x40000000) | other.m_size;
	}
	// local variables reproduce the original's register/schedule shape
	int size = other.m_size;
	T*  dst  = m_data;
	m_size   = size;
	const T* src = other.m_data;
	if (size > 0)
	{
		int delta = (int)src - (int)dst;
		do
		{
			*(uint32_t*)dst = *(uint32_t*)(delta + (int)dst);
			*((uint32_t*)dst + 1) = *(uint32_t*)(delta + (int)dst + 4);
			dst += 1;
			size--;
		} while (size != 0);
	}
	return *this;
}

// ---------------------------------------------------------------------------
// hull types
// ---------------------------------------------------------------------------

struct __declspec(align(16)) hkVector4
{
	float x, y, z, w;
};

struct hkGeomEdge
{
	uint16_t m_vertex;   // +0
	uint16_t m_twin;     // +2
	uint16_t m_next;     // +4
	uint16_t m_flag;     // +6
};

class hkGeomHull
{
public:
	const hkVector4*    m_vertices;   // +0
	hkArray<hkGeomEdge> m_edges;      // +4
};

struct hkGeomConvexHullTolerances
{
	char m_pad0[2];
	hkBool m_postFilter;              // +2
	char m_pad3;
	float m_pad4;
	float m_minNormalLengthSq;        // +8
	float m_weldTolerance;            // +0xc
	float m_pad10;
	float m_opposingPlaneTolerance;   // +0x14
};

class hkGeomConvexHullBuilder
{
public:
	struct PlaneAndPoints
	{
		hkVector4         m_plane;    // +0
		const hkGeomEdge* m_edge0;    // +0x10
		const hkGeomEdge* m_edge1;    // +0x14
		const hkGeomEdge* m_edge2;    // +0x18
		void sort();                  // 0x01116D00
	};
	struct WeightedNeighbour
	{
		uint32_t m_data[2];
	};
	struct WeightedLine
	{
		hkGeomEdge*   m_edgeA;       // +0
		hkGeomEdge*   m_edgeB;       // +4
		WeightedLine* m_lastLine;    // +8
		uint16_t      m_lastVertex;  // +0xc
		uint16_t      m_padE;
		float         m_weight;      // +0x10
	};
	struct WrappingLine
	{
		uint32_t m_data[4];
	};

	// 0x01119E00
	static void remapEdges(const hkGeomHull& hull, char flag, hkGeomHull& mergedHull, hkArray<uint16_t>& remap);
	// 0x01119FA0
	static void emitFaceCandidates(hkGeomHull& hull, hkArray<uint32_t>& faces);

	static hkBool buildPlaneEquations(const hkGeomConvexHullTolerances& tolerances, hkGeomHull& hull,
		const hkArray<hkVector4>& usedVertices, hkArray<hkVector4>& planeEquations);                          // 0x0111A060
	static void removeUnusedVertices(hkGeomHull& hull, hkArray<hkVector4>& usedVertices);                       // 0x0111A0F0
	static void stitchHulls(hkGeomHull& hullA, hkGeomHull& hullB, hkArray<WrappingLine>& wrapping,
		hkGeomHull& mergedHull);                                                                                // 0x0111A290
	static void removeCoPlanarNeighbours(const hkGeomConvexHullTolerances& tolerances, hkGeomHull& hull,
		const hkVector4& normal, const hkGeomEdge* edge, const hkVector4* a, const hkVector4* b,
		hkArray<WeightedNeighbour>& neighbours);                                                                // 0x0111A700
	static void validateNeighbours(const hkGeomConvexHullTolerances& tolerances, const hkVector4* vertices,
		const hkVector4& normal, unsigned short lastVertex, WeightedLine* line, const hkVector4* a,
		const hkVector4* b, hkArray<WeightedNeighbour>& neighboursA, hkArray<WeightedNeighbour>& neighboursB);  // 0x0111A8A0
	static hkBool isValidEdgeCheck(hkGeomHull& hull, hkGeomEdge* edge, int flag);                               // 0x0111A9E0

	static void calculateNewNeighbours(const hkVector4* vertices, const hkGeomConvexHullTolerances& tolerances,
		float tolerance, const hkVector4& normal, const hkGeomEdge* edge, const hkVector4* a, const hkVector4* b,
		hkArray<WeightedNeighbour>& neighbours);                                                                // 0x011172B0

	static hkBool buildPlaneEquationsFull(const hkGeomConvexHullTolerances& tolerances, hkGeomHull& hull,
		const hkArray<hkVector4>& usedVertices, hkVector4& planarNormal, hkBool& planarHullFound,
		hkArray<hkVector4>& planeEquations, hkArray<PlaneAndPoints>& planesAndPoints);                          // 0x01118F50
};

// out-of-slice callees
void FUN_0111cc90(void* p);                                                                  // 0x0111cc90

// ---------------------------------------------------------------------------
// 0x01119F00 -- hkArray<T>::operator=
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// 0x01119E00 -- merge worker
// ---------------------------------------------------------------------------
// @ 0x01119e00
void hkGeomConvexHullBuilder::remapEdges(const hkGeomHull& hull, char flag, hkGeomHull& mergedHull,
	hkArray<uint16_t>& remap)
{
	remap.setSize(hull.m_edges.m_size);

	const int startSize = mergedHull.m_edges.m_size;
	int i;
	for (i = 0; i < hull.m_edges.m_size; i++)
	{
		const hkGeomEdge* e = &hull.m_edges.m_data[i];
		if (e->m_flag == 1 || e->m_flag == 2)
		{
			remap.m_data[i] = (uint16_t)mergedHull.m_edges.m_size;
			mergedHull.m_edges.pushBack(*e);
		}
		else
		{
			remap.m_data[i] = 0xffff;
		}
	}

	for (i = startSize; i < mergedHull.m_edges.m_size; i++)
	{
		hkGeomEdge* e = &mergedHull.m_edges.m_data[i];
		e->m_twin = remap.m_data[e->m_twin];
		e->m_next = remap.m_data[e->m_next];
	}
	(void)flag;
}

// ---------------------------------------------------------------------------
// 0x01119FA0 -- emit face candidates
// ---------------------------------------------------------------------------
// @ 0x01119fa0
void hkGeomConvexHullBuilder::emitFaceCandidates(hkGeomHull& hull, hkArray<uint32_t>& faces)
{
	const hkGeomEdge* edges = hull.m_edges.m_data;
	int i;
	for (i = 0; i < hull.m_edges.getSize(); i++)
	{
		uint32_t n0 = *(const uint32_t*)((const char*)edges + i * 8);
		uint16_t n1 = *(const uint16_t*)((const char*)edges + i * 8 + 4);
		if (i < (int)n1)
		{
			uint16_t n2 = *(const uint16_t*)((const char*)edges + (int)n1 * 8 + 4);
			if (i < (int)n2)
			{
				uint16_t v0 = *(const uint16_t*)((const char*)edges + (int)n1 * 8);
				uint16_t v1 = *(const uint16_t*)((const char*)edges + (int)n2 * 8);
				uint32_t f0 = n0;
				uint32_t* out;
				int idx = faces.m_size;
				int need = faces.m_size + 1;
				if (faces.getCapacity() < need)
				{
					int newCap = faces.getCapacity() + faces.getCapacity();
					if (newCap <= need)
						newCap = need;
					hkArrayUtil::_reserveExactly(&faces, newCap, 12);
				}
				out = faces.m_data + idx * 3;
				faces.m_size = need;
				out[0] = f0 & 0xffff;
				out[1] = (unsigned)v1;
				out[2] = (unsigned)v0;
			}
		}
	}
}

// ---------------------------------------------------------------------------
// 0x0111A060 -- 5-argument buildPlaneEquations wrapper
// ---------------------------------------------------------------------------
// @ 0x0111a060
hkBool hkGeomConvexHullBuilder::buildPlaneEquations(const hkGeomConvexHullTolerances& tolerances, hkGeomHull& hull,
	const hkArray<hkVector4>& usedVertices, hkArray<hkVector4>& planeEquations)
{
	hkBool planarHullFound;
	hkVector4 planarNormal;
	struct RawPlanes
	{
		void*  m_data;
		int    m_size;
		int    m_capacityAndFlags;
	};
	RawPlanes planesAndPoints;
	planesAndPoints.m_data = 0;
	planesAndPoints.m_size = 0;
	planesAndPoints.m_capacityAndFlags = (int)0x80000000;

	hkBool result = buildPlaneEquationsFull(tolerances, hull, usedVertices, planarNormal, planarHullFound,
	                                        planeEquations, *(hkArray<PlaneAndPoints>*)&planesAndPoints);

	if (planesAndPoints.m_capacityAndFlags >= 0)
		hkThreadMemory::getInstance().deallocateChunk(planesAndPoints.m_data,
			planesAndPoints.m_capacityAndFlags << 5, HK_MEMORY_CLASS_ARRAY);
	return result;
}

// ---------------------------------------------------------------------------
// 0x0111A0F0 -- removeUnusedVertices
// ---------------------------------------------------------------------------
// @ 0x0111a0f0
void hkGeomConvexHullBuilder::removeUnusedVertices(hkGeomHull& hull, hkArray<hkVector4>& usedVertices)
{
	int i;
	for (i = 0; i < hull.m_edges.m_size; i++)
		usedVertices.m_data[hull.m_edges.m_data[i].m_vertex].w = 1073741824.0f;

	int* used = (int*)hkThreadMemory::getInstance().allocateStack(usedVertices.m_size * 4 + 16);

	int numUsed = 0;
	for (int j = 0; j < usedVertices.m_size; j++)
	{
		if (usedVertices.m_data[j].w == 1073741824.0f)
		{
			usedVertices.m_data[numUsed] = usedVertices.m_data[j];
			used[j] = numUsed;
			numUsed++;
		}
		else
		{
			used[j] = -1;
		}
	}

	usedVertices.reserveFor(numUsed);
	usedVertices.m_size = numUsed;

	for (int k = 0; k < hull.m_edges.m_size; k++)
		hull.m_edges.m_data[k].m_vertex = (uint16_t)used[hull.m_edges.m_data[k].m_vertex];

	hkThreadMemory::getInstance().deallocateStack(used);

	for (int m = 0; m < hull.m_edges.m_size; m++)
		usedVertices.m_data[hull.m_edges.m_data[m].m_vertex].w = 0.0f;
}

// ---------------------------------------------------------------------------
// 0x0111A290 -- stitchHulls
// ---------------------------------------------------------------------------
// @ 0x0111a290
void hkGeomConvexHullBuilder::stitchHulls(hkGeomHull& hullA, hkGeomHull& hullB, hkArray<WrappingLine>& wrapping,
	hkGeomHull& mergedHull)
{
	mergedHull.m_edges.m_size = 0;

	hkThreadMemory& mem = hkThreadMemory::getInstance();

	hkArray<uint16_t> remapA;
	setupStackArray(remapA, (char*)mem.allocateStack(hullA.m_edges.getSize() * 4 + 16),
	                hullA.m_edges.getSize());
	remapEdges(hullA, 1, mergedHull, remapA);

	hkArray<uint16_t> remapB;
	setupStackArray(remapB, (char*)mem.allocateStack(hullB.m_edges.getSize() * 4 + 16),
	                hullB.m_edges.getSize());
	remapEdges(hullB, 0, mergedHull, remapB);

	int total = wrapping.m_size * 3 + mergedHull.m_edges.m_size;
	if ((int)((unsigned)mergedHull.m_edges.m_capacityAndFlags & 0x3fffffff) < total)
		hkArrayUtil::_reserveExactly(&mergedHull.m_edges, total, 8);

	for (int i = 0; i < wrapping.m_size; i++)
	{
		WrappingLine* w = wrapping.m_data + i;
		hkGeomEdge* a = (hkGeomEdge*)w->m_data[0];
		hkGeomEdge* b = (hkGeomEdge*)w->m_data[1];

		*(uint16_t*)(w->m_data + 2) = a->m_vertex;
		*(uint16_t*)(w->m_data + 3) =
			*(uint16_t*)((char*)mergedHull.m_edges.m_data + (int)a->m_next * 8);
		*(uint16_t*)((char*)w->m_data + 0xe) = b->m_vertex;

		int aIdx = ((int)a - (int)hullA.m_edges.m_data) >> 3;
		int bTwin = (int16_t)b->m_twin >> 3;
		uint16_t ra = *(uint16_t*)((char*)remapA.m_data + aIdx * 2);
		w->m_data[0] = (ra == 0xffff) ? 0
			: (uint32_t)((char*)mergedHull.m_edges.m_data + ra * 8);
		uint16_t rb = *(uint16_t*)((char*)remapB.m_data + bTwin * 2);
		w->m_data[1] = (rb == 0xffff) ? 0
			: (uint32_t)((char*)mergedHull.m_edges.m_data + rb * 8);
	}

	int firstOut = mergedHull.m_edges.m_size;
	int idx      = wrapping.m_size - 1;
	uint32_t first = 0xffff;
	WrappingLine* lastOut = 0;
	if (idx >= 0)
	{
		WrappingLine* cur  = wrapping.m_data + idx;
		WrappingLine* next = cur;
		for (;;)
		{
			uint32_t out0 = mergedHull.m_edges.m_size;
			hkGeomEdge* p = &mergedHull.m_edges.expandOne();
			uint32_t out1 = mergedHull.m_edges.m_size;
			hkGeomEdge* q = &mergedHull.m_edges.expandOne();

			hkGeomEdge* a = (hkGeomEdge*)cur->m_data[0];
			hkGeomEdge* b = (hkGeomEdge*)next->m_data[0];
			uint32_t prevOut = out0;

			if (a == b)
			{
				hkGeomEdge* t;
				if (a->m_flag == 2)
					t = (hkGeomEdge*)((char*)mergedHull.m_edges.m_data + a->m_twin * 8);
				else
				{
					t = &mergedHull.m_edges.expandOne();
				}

				p->m_vertex = ((hkGeomEdge*)cur->m_data[1])->m_vertex;
				p->m_flag   = (uint16_t)out0;
				p->m_twin   = 0xffff;
				if (lastOut != 0)
					*(uint16_t*)((char*)lastOut + 2) = (uint16_t)out0;
				*(uint16_t*)((char*)cur->m_data + 0xe) = (uint16_t)first;
				*(uint16_t*)((char*)&p->m_twin) = (uint16_t)(((int)q - (int)mergedHull.m_edges.m_data) >> 3);
				t->m_twin = (uint16_t)first;

				q->m_vertex = cur->m_data[2];
				q->m_flag   = (uint16_t)out0;
				q->m_twin   = (uint16_t)first;
			}
			else
			{
				hkGeomEdge* t;
				if (a->m_flag == 2)
					t = (hkGeomEdge*)((char*)mergedHull.m_edges.m_data + a->m_twin * 8);
				else
				{
					t = &mergedHull.m_edges.expandOne();
					prevOut = mergedHull.m_edges.m_size - 1;
				}

				p->m_vertex = (uint16_t)(int)cur->m_data[3];
				p->m_flag   = (uint16_t)first;
				p->m_twin   = 0xffff;
				if (lastOut != 0)
					*(uint16_t*)((char*)lastOut + 2) = (uint16_t)prevOut;
				*(uint16_t*)((char*)q + 2) = (uint16_t)(((int)t - (int)mergedHull.m_edges.m_data) >> 3);
				*(uint16_t*)((char*)&q->m_twin) = (uint16_t)first;
				t->m_twin = (uint16_t)prevOut;

				q->m_vertex = (uint16_t)(int)a->m_vertex;
				q->m_flag   = (uint16_t)prevOut;
				q->m_twin   = (uint16_t)first;
			}

			first   = (uint32_t)out0;
			lastOut = next;
			if (--idx == 0)
				break;
			next = cur;
			lastOut = (WrappingLine*)((char*)cur + 0);
			q    = (hkGeomEdge*)cur;
			cur  = (WrappingLine*)((char*)cur - 16);
			lastOut = (WrappingLine*)q;
		}
	}
	(void)firstOut;
	(void)first;
}

// ---------------------------------------------------------------------------
// 0x0111A700 -- removeCoPlanarNeighbours
// ---------------------------------------------------------------------------
// @ 0x0111a700
void hkGeomConvexHullBuilder::removeCoPlanarNeighbours(const hkGeomConvexHullTolerances& tolerances, hkGeomHull& hull,
	const hkVector4& normal, const hkGeomEdge* edge, const hkVector4* a, const hkVector4* b,
	hkArray<WeightedNeighbour>& neighbours)
{
	const float tolerance = tolerances.m_weldTolerance;

	if (neighbours.m_size > 1 && ((*(const float*)&neighbours.m_data[0].m_data[1]) - normal.x) < tolerance)
	{
		const float baseY = *(const float*)&neighbours.m_data[0].m_data[1];

		hkArray<WeightedNeighbour> candidates;
		WeightedNeighbour stackBuf[128];
		candidates.m_data = stackBuf;
		candidates.m_size = 0;
		candidates.m_capacityAndFlags = (int)0x80000040;

		for (int i = 0; i < neighbours.m_size; i++)
		{
			const float y = *(const float*)&neighbours.m_data[i].m_data[1];
			if (tolerance < y - baseY)
				break;
			candidates.pushBack(neighbours.m_data[i]);
		}

		calculateNewNeighbours(hull.m_vertices, tolerances, baseY, normal, edge, a, b, candidates);

		neighbours.m_data[0].m_data[0] = candidates.m_data[0].m_data[0];
		neighbours.m_data[0].m_data[1] = candidates.m_data[0].m_data[1];
		*(float*)&neighbours.m_data[0].m_data[1] = baseY;

		if (neighbours.getCapacity() < 1)
			hkArrayUtil::_reserveExactly(&neighbours, 1, 8);
		neighbours.m_size = 1;

		if ((candidates.m_capacityAndFlags & 0x80000000) == 0)
			hkThreadMemory::getInstance().deallocateChunk(candidates.m_data,
				candidates.getCapacity() * 8, HK_MEMORY_CLASS_ARRAY);
	}
}

// ---------------------------------------------------------------------------
// 0x0111A8A0 -- validateNeighbours
// ---------------------------------------------------------------------------
// @ 0x0111a8a0
void hkGeomConvexHullBuilder::validateNeighbours(const hkGeomConvexHullTolerances& tolerances, const hkVector4* vertices,
	const hkVector4& normal, unsigned short lastVertex, WeightedLine* line, const hkVector4* a,
	const hkVector4* b, hkArray<WeightedNeighbour>& neighboursA, hkArray<WeightedNeighbour>& neighboursB)
{
	if (neighboursA.m_size != 1)
		return;
	if (neighboursB.m_size != 1)
		return;

	const hkGeomEdge* ref = line->m_edgeA;
	if (line->m_lastLine != NULL && lastVertex != 0xffff && line->m_lastLine->m_edgeA->m_vertex == lastVertex)
		ref = line->m_edgeB;

	float ya = *(const float*)&neighboursA.m_data[0].m_data[1];
	float yb = *(const float*)&neighboursB.m_data[0].m_data[1];

	if (fabsf(ya - yb) < tolerances.m_weldTolerance)
	{
		WeightedNeighbour tmpBuf[2];
		tmpBuf[0] = neighboursA.m_data[0];
		tmpBuf[1] = neighboursB.m_data[0];

		hkArray<WeightedNeighbour> tmp;
		tmp.m_data = tmpBuf;
		tmp.m_size = 2;
		tmp.m_capacityAndFlags = (int)0x80000002;

		calculateNewNeighbours(vertices, tolerances, yb, normal, ref, a, b, tmp);

		WeightedNeighbour* pick = &neighboursA.m_data[0];
		if (tmp.m_data[0].m_data[0] != neighboursA.m_data[0].m_data[0])
			pick = &neighboursB.m_data[0];

		*(float*)&pick->m_data[1] = *(float*)&pick->m_data[1] * 0.5f;

		if ((tmp.m_capacityAndFlags & 0x80000000) == 0)
			hkThreadMemory::getInstance().deallocateChunk(tmp.m_data, tmp.getCapacity() * 8, HK_MEMORY_CLASS_ARRAY);
	}
}

// ---------------------------------------------------------------------------
// 0x0111A9E0 -- isValidEdgeCheck
// ---------------------------------------------------------------------------
// @ 0x0111a9e0
hkBool hkGeomConvexHullBuilder::isValidEdgeCheck(hkGeomHull& hull, hkGeomEdge* edge, int flag)
{
	const hkGeomEdge* base = hull.m_edges.m_data;

	hkGeomEdge* stackBuf[128];
	hkArray<hkGeomEdge*> stack;
	stack.m_data = stackBuf;
	stack.m_size = 1;
	stack.m_capacityAndFlags = (int)0x80000080;
	stack.m_data[0] = edge;

	hkBool result;
	for (;;)
	{
		hkGeomEdge* e = stack.m_data[--stack.m_size];
		hkGeomEdge* cur = e;
		for (;;)
		{
			cur = (hkGeomEdge*)((const char*)base + (int)cur->m_next * 8);
			switch (cur->m_flag)
			{
			case 1:
			case 3:
				if ((int)cur->m_flag != flag)
				{
					result.m_bool = 0;
					goto done;
				}
				break;
			case 2:
				if (flag == 3)
				{
					if (cur->m_flag != 3)
					{
						result.m_bool = 0;
						goto done;
					}
					break;
				}
				break;
			default:
				break;
			}
			cur->m_flag = (uint16_t)flag;
			if (cur == e)
				break;
		}
		/* twin walk */
		hkGeomEdge* t = (hkGeomEdge*)((const char*)base + (int)e->m_next * 8);
		hkGeomEdge* tEnd = t;
		do
		{
			hkGeomEdge* twin = (hkGeomEdge*)((const char*)base + (int)t->m_twin * 8);
			t = (hkGeomEdge*)((const char*)base + (int)t->m_next * 8);
			if (twin->m_flag == 0)
			{
				if (stack.m_size == stack.getCapacity())
					hkArrayUtil::_reserveMore(&stack, 4);
				((hkGeomEdge**)stack.m_data)[stack.m_size] = twin;
				stack.m_size++;
			}
		} while (t != tEnd);

		if (stack.m_size == 0)
		{
			result.m_bool = 1;
			if ((stack.m_capacityAndFlags & 0x80000000) == 0)
				hkThreadMemory::getInstance().deallocateChunk(stack.m_data, stack.getCapacity() * 4, HK_MEMORY_CLASS_ARRAY);
			return result;
		}
	}

done:
	if ((stack.m_capacityAndFlags & 0x80000000) == 0)
		hkThreadMemory::getInstance().deallocateChunk(stack.m_data, stack.getCapacity() * 4, HK_MEMORY_CLASS_ARRAY);
	return result;
}
