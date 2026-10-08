// Havok 3.1.0: hkGeomConvexHullBuilder helper at 0x011187D0 (name guessed: markRedundantVertices).
// Runs on a half-edge hull (vertices + edges) after the hull is built and flags vertices that do not
// change its shape by setting their w to 1.0 (w == 0 means "kept"):
//  1. Collinear vertices: for every undirected edge (u,w) it collects the vertices in [first,last] that lie on the
//     line u-w (|cross|^2 < tol+8) and flags every one that is not the extreme point at either end.
//  2. Coplanar vertices: for every still-kept vertex it walks the half-edge fan around it, accumulates the face
//     normals, and if all of them agree with their average (dot >= 1 - tol+0xc) flags the vertex.
// Sets `changed` when it flagged something. Half-edge field `m_visited` is scratch (cleared in between).
//
// Self-contained; same Havok conventions as match/slices/s01118f50 (kZero/kOne from the constant pool).
// Names marked "(name guessed)" are Claude-coined. Flags: /O2 /MD /Gy /TP /fp:fast (Havok: no /EHsc).
#include "types.h"
#include <math.h>

#ifdef _WIN32
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
#endif

class hkBool
{
public:
	hkBool() {}
	hkBool(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
	char m_bool;
};

enum { HK_MEMORY_CLASS_ARRAY = 0x14 };

extern unsigned long g_hkThreadMemoryTlsIndex;   // 0x016E4174 (hkThreadMemory::s_threadMemoryInstance TLS slot)
class hkThreadMemory
{
public:
	void deallocateChunk(void* p, int nbytes, int memClass);   // 0x0107DB10
	static hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }
};

struct hkArrayUtil
{
	static void _reserveMore(void* array, int sizeElem);                   // 0x0107F530
	static void _reserveExactly(void* array, int numElem, int sizeElem);   // 0x0107F4A0
};

template <class T>
class hkArray
{
public:
	enum { CAPACITY_MASK = 0x3FFFFFFF, DONT_DEALLOCATE_FLAG = (int)0x80000000 };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	hkArray() : m_data(0), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}
	~hkArray()
	{
		if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
			hkThreadMemory::getInstance().deallocateChunk(m_data, getCapacity() * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
	}
	int getSize() const { return m_size; }
	int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
	T& operator[](int i) { return m_data[i]; }
	const T& operator[](int i) const { return m_data[i]; }
	void pushBack(const T& e)
	{
		if (m_size == getCapacity())
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		m_data[m_size++] = e;
	}
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
	T* expandBy(int n)
	{
		int oldSize = m_size;
		int newSize = oldSize + n;
		reserveFor(newSize);
		m_size = newSize;
		return m_data + oldSize;
	}
	T& expandOne() { return *expandBy(1); }
};

// Havok 3.1 was built by an older cl that loads 0.0f/1.0f from the constant pool (0x01485378 / 0x01485720).
extern const float kZero;   // 0x01485378
extern const float kOne;    // 0x01485720
__forceinline float hkMath_sqrt(float r) { return (float)sqrt((double)r); }   // hkMath::sqrt (inline fsqrt)

struct __declspec(align(16)) hkVector4
{
	float x, y, z, w;

	__forceinline void setSub4(const hkVector4& a, const hkVector4& b) { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
	__forceinline void setCross(const hkVector4& a, const hkVector4& b)
	{
		const float nx = a.y * b.z - a.z * b.y;
		const float ny = a.z * b.x - a.x * b.z;
		const float nz = a.x * b.y - a.y * b.x;
		w = 0.0f;
		x = nx;
		y = ny;
		z = nz;
	}
	__forceinline void mul4(float s) { x = x * s; y = y * s; z = z * s; w = w * s; }
	__forceinline float dot3(const hkVector4& a) const { return x * a.x + y * a.y + z * a.z; }
	__forceinline float lengthSquared3() const { return x * x + y * y + z * z; }
	__forceinline void normalize3()
	{
		const float len2 = lengthSquared3();
		const float inv = (len2 == kZero) ? kZero : kOne / hkMath_sqrt(len2);
		mul4(inv);
	}
};

struct hkGeomEdge
{
	uint16_t m_vertex;    // +0
	uint16_t m_twin;      // +2 (index of the opposite half-edge)
	uint16_t m_next;      // +4 (next half-edge of the face)
	uint16_t m_visited;   // +6 (scratch flag, name guessed)
};

struct hkGeomHull
{
	hkVector4* m_vertices;            // +0
	hkArray<hkGeomEdge> m_edges;      // +4
};

struct hkGeomConvexHullTolerances
{
	hkBool m_removeRedundant;         // +0 (name guessed): the whole pass is skipped when clear
	char m_pad1[7];
	float m_collinearTolSq;           // +8 (name guessed): |cross|^2 below it = on the line
	float m_coplanarTol;              // +0xc (name guessed): normals within 1 - tol of their average = flat
};

// @ 0x011187d0  (hkGeomConvexHullBuilder::markRedundantVertices, name guessed)
void markRedundantVertices(hkGeomHull& hull, int first, int last, const hkGeomConvexHullTolerances& tol, hkBool& changed)
{
	changed = false;
	if (!tol.m_removeRedundant)
		return;

	hkGeomEdge* edges = hull.m_edges.m_data;
	hkVector4* verts = hull.m_vertices;

	for (int i = 0; i < hull.m_edges.m_size; i++)
		edges[i].m_visited = 0;

	// --- 1. collinear vertices ---
	for (int ei = 0; ei < hull.m_edges.m_size; ei++)
	{
		hkGeomEdge& edge = hull.m_edges.m_data[ei];
		if (edge.m_visited == 1)
			continue;
		const int twin = edge.m_twin;
		edge.m_visited = 1;
		edges[twin].m_visited = 1;
		const int a = edge.m_vertex;
		const int b = edges[twin].m_vertex;
		const hkVector4& va = verts[a];
		const hkVector4& vb = verts[b];

		hkVector4 dir;
		dir.x = vb.x - va.x;
		dir.y = vb.y - va.y;
		dir.z = vb.z - va.z;
		float loDot = 1e-6f;
		float hiDot = dir.z * dir.z + dir.y * dir.y + dir.x * dir.x;
		int loVert = a;
		int hiVert = b;
		hkArray<int> onLine;

		if (b != a && va.w == kZero && vb.w == kZero)
		{
			for (int k = first; k < last + 1; k++)
			{
				if (k == a || k == b || !(verts[k].w == kZero))
					continue;
				const hkVector4& p = verts[k];
				const float tx = p.x - va.x;
				const float ty = p.y - va.y;
				const float tz = p.z - va.z;
				const float dot = tx * dir.x + tz * dir.z + ty * dir.y;
				const float cx = dir.y * tz - ty * dir.z;
				const float cy = dir.z * tx - tz * dir.x;
				const float cz = ty * dir.x - dir.y * tx;
				if (cy * cy + (cz * cz + cx * cx) < tol.m_collinearTolSq)
				{
					if (dot < loDot)
					{
						onLine.pushBack(loVert);
						loVert = k;
						loDot = dot;
					}
					else if (dot > hiDot)
					{
						onLine.pushBack(hiVert);
						hiVert = k;
						hiDot = dot;
					}
					else
					{
						onLine.pushBack(k);
					}
				}
			}
		}

		for (int j = 0; j < onLine.getSize(); j++)
		{
			const int v = onLine[j];
			if (v != loVert && v != hiVert)
			{
				verts[v].w = kOne;
				changed = true;
			}
		}
	}

	for (int i = 0; i < hull.m_edges.m_size; i++)
		hull.m_edges.m_data[i].m_visited = 0;

	// --- 2. coplanar vertices ---
	if (last - first > 2 && hull.m_edges.m_size > 2)
	{
		for (int vi = first; vi < last + 1; vi++)
		{
			hkVector4& vert = verts[vi];
			if (!(vert.w == kZero))
				continue;

			hkArray<hkVector4> normals;
			for (int ei = 0; ei < hull.m_edges.m_size; ei++)
			{
				hkGeomEdge& edge = hull.m_edges.m_data[ei];
				if (edge.m_visited == 1 || edge.m_vertex != vi)
					continue;
				edge.m_visited = 1;
				const hkGeomEdge* start = &edges[hull.m_edges.m_data[ei].m_twin];
				const hkGeomEdge* p = start;
				do
				{
					const hkGeomEdge& q = edges[p->m_next];
					edges[p->m_next].m_visited = 1;
					const hkVector4& vp = verts[p->m_vertex];
					const hkVector4& vq = verts[q.m_vertex];
					const hkVector4& vr = verts[edges[q.m_next].m_vertex];
					hkVector4 d1, d2;
					d1.x = vp.x - vq.x; d1.y = vp.y - vq.y; d1.z = vp.z - vq.z;
					d2.x = vr.x - vq.x; d2.y = vr.y - vq.y; d2.z = vr.z - vq.z;
					hkVector4& n = normals.expandOne();
					n.setCross(d1, d2);
					n.normalize3();
					p = &edges[q.m_twin];
				} while (p != start);
			}

			if (normals.getSize() > 0)
			{
				hkVector4 sum;
				sum.x = kZero; sum.y = kZero; sum.z = kZero; sum.w = kZero;
				for (int i = 0; i < normals.getSize(); i++)
				{
					sum.x += normals[i].x;
					sum.y += normals[i].y;
					sum.z += normals[i].z;
					sum.w += normals[i].w;
				}
				const float len2 = sum.z * sum.z + (sum.y * sum.y + sum.x * sum.x);
				if (tol.m_coplanarTol < len2)
				{
					const float inv = (len2 == kZero) ? kZero : kOne / hkMath_sqrt(len2);
					hkVector4 avg;
					avg.x = inv * sum.x;
					avg.y = sum.y * inv;
					avg.z = sum.z * inv;
					const float threshold = kOne - tol.m_coplanarTol;
					bool flat = true;
					for (int i = 0; i < normals.getSize(); i++)
					{
						const float d = avg.y * normals[i].y + avg.x * normals[i].x + avg.z * normals[i].z;
						if (d < threshold)
						{
							flat = false;
							break;
						}
					}
					if (flat)
					{
						vert.w = kOne;
						changed = true;
					}
				}
			}
		}
	}
}
