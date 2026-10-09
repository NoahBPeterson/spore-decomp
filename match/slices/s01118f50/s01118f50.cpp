// Havok 3.1.0: hkGeomConvexHullBuilder::buildPlaneEquations (0x01118F50), the 8-argument overload.
// Builds one plane per hull face (the face of every half-edge triple i -> next -> next2 whose smallest index is i),
// merges/repairs exactly opposing faces, and falls back to 6 bounding planes around a segment/point hull.
//
// Self-contained: hkVector4 is 16-byte aligned here (the original frame does `and esp,-16`).
// Names: hkGeomConvexHullBuilder methods are from symbols/havok_names.txt; the two unnamed callees
// (0x01115730, 0x01116F90) carry Claude-coined names marked "(name guessed)".
// Float accumulation order: written in Havok's natural x,y,z order. The original's sums come out reversed in
// places (e.g. z*z + y*y + x*x), which /fp:fast reproduces.
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
	T* begin() { return m_data; }
	void clear() { m_size = 0; }
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
};

#define HK_REAL_MAX 3.40282e+38f
// Havok 3.1 was built by an older cl that loads 0.0f/1.0f from the constant pool (0x01485378 / 0x01485720).
extern const float kZero;   // 0x01485378
extern const float kOne;    // 0x01485720
__forceinline float hkMath_sqrt(float r) { return (float)sqrt((double)r); }   // hkMath::sqrt (inline fsqrt)

struct __declspec(align(16)) hkVector4
{
	float x, y, z, w;

	__forceinline void setSub4(const hkVector4& a, const hkVector4& b) { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
	__forceinline void setAdd4(const hkVector4& a, const hkVector4& b) { x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; w = a.w + b.w; }
	__forceinline void setNeg4(const hkVector4& a) { x = -a.x; y = -a.y; z = -a.z; w = -a.w; }
	__forceinline void setNeg3(const hkVector4& a) { x = -a.x; y = -a.y; z = -a.z; }
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
	__forceinline float lengthSquared4() const { return x * x + y * y + z * z + w * w; }
	__forceinline void normalize3()
	{
		const float len2 = lengthSquared3();
		const float inv = (len2 == kZero) ? kZero : kOne / hkMath_sqrt(len2);
		mul4(inv);
	}
	// normalize3 of a cross product the original had just stored: it re-reads the stored (float-rounded)
	// components, while cl here would keep the unrounded x87 values (a 1-ulp difference in the plane).
	__forceinline void normalize3Stored()
	{
		const float x0 = *(volatile float*)&x;
		const float y0 = *(volatile float*)&y;
		const float z0 = *(volatile float*)&z;
		const float len2 = z0 * z0 + y0 * y0 + x0 * x0;
		const float inv = (len2 == kZero) ? kZero : kOne / hkMath_sqrt(len2);
		x = x0 * inv; y = y0 * inv; z = z0 * inv; w = w * inv;
	}
	// Plane through p with this (unit) normal: w = -n.p
	__forceinline void setPlaneDistance(const hkVector4& p) { w = -dot3(p); }
};

struct hkGeomEdge
{
	uint16_t m_vertex;   // +0
	uint16_t m_twin;     // +2 (index of the opposite half-edge)
	uint16_t m_next;     // +4 (next half-edge of the face)
	uint16_t m_pad;      // +6
};

struct hkGeomHull
{
	const hkVector4* m_vertices;      // +0
	hkArray<hkGeomEdge> m_edges;      // +4
};

struct hkGeomConvexHullTolerances
{
	char m_pad0[2];
	hkBool m_postFilter;              // +2 (name guessed): when set, opposing faces trigger a planar rebuild
	char m_pad3;
	float m_pad4;
	float m_minNormalLengthSq;        // +8 (name guessed): faces with |n|^2 below it are dropped
	float m_pad0c;
	float m_weldTolerance;            // +0x10 (name guessed): passed to weldXsortedVertices
	float m_pad14;
	float m_opposingPlaneTolerance;   // +0x18 (name guessed): |a + b|^2 below it = opposing planes
};

class hkGeomConvexHullBuilder
{
public:
	struct PlaneAndPoints
	{
		hkVector4 m_plane;               // +0
		const hkGeomEdge* m_edge0;       // +0x10
		const hkGeomEdge* m_edge1;       // +0x14
		const hkGeomEdge* m_edge2;       // +0x18
		void sort();                     // 0x01116D00
	};

	static hkBool buildPlaneEquations(const hkGeomConvexHullTolerances& tolerances, hkGeomHull& hull,
		const hkArray<hkVector4>& usedVertices, hkVector4& planarNormal, hkBool& planarHullFound,
		hkArray<hkVector4>& planeEquations, hkArray<PlaneAndPoints>& planesAndPoints);

	// 0x01115730 (name guessed): true when face a's edge pair (a0,a1) and face b's edge pair (b0,b1) are shared
	static hkBool sharesEdgePair(const hkGeomEdge* edges, const hkGeomEdge* a0, const hkGeomEdge* b0,
		const hkGeomEdge* a1, const hkGeomEdge* b1, const PlaneAndPoints& a, const PlaneAndPoints& b);   // 0x01115730
	// 0x01116F90 (name guessed): adds the extra planes for an opposing face pair
	static void addPlanesForOpposingFace(const hkVector4& plane, const hkVector4& v0, const hkVector4& v1,
		const hkVector4& v2, hkArray<hkVector4>& planeEquations);   // 0x01116f90

	static hkBool vectorLessAndMergeCoordinates(hkVector4& a, hkVector4& b);                   // 0x01115950
	static void weldXsortedVertices(float tolerance, hkArray<hkVector4>& verts, int& numWelded);   // 0x01116D50
	static void generateHullFromPlanarPoints(const hkVector4& normal, const hkVector4* points, int numPoints,
		hkArray<hkVector4>& usedPoints, hkArray<hkVector4>& planeEquations);                      // 0x01117840
};

struct hkAlgorithm
{
	template <class T, class L>
	static void quickSortRecursive(T* data, int lo, int hi, L less);   // 0x011155B0 (instance for hkVector4)
};
template <> void hkAlgorithm::quickSortRecursive<hkVector4, hkBool (*)(hkVector4&, hkVector4&)>(
	hkVector4* data, int lo, int hi, hkBool (*less)(hkVector4&, hkVector4&));

static inline void sortAndWeld(const hkGeomConvexHullTolerances& tolerances, hkArray<hkVector4>& planeEquations, int& numWelded)
{
	if (planeEquations.getSize() > 1)
		hkAlgorithm::quickSortRecursive<hkVector4, hkBool (*)(hkVector4&, hkVector4&)>(planeEquations.begin(), 0,
			planeEquations.getSize() - 1, hkGeomConvexHullBuilder::vectorLessAndMergeCoordinates);
	hkGeomConvexHullBuilder::weldXsortedVertices(tolerances.m_weldTolerance, planeEquations, numWelded);
}

// @ 0x01118f50
hkBool hkGeomConvexHullBuilder::buildPlaneEquations(const hkGeomConvexHullTolerances& tolerances, hkGeomHull& hull,
	const hkArray<hkVector4>& usedVertices, hkVector4& planarNormal, hkBool& planarHullFound,
	hkArray<hkVector4>& planeEquations, hkArray<PlaneAndPoints>& planesAndPoints)
{
	const hkVector4* vertices = hull.m_vertices;
	const hkGeomEdge* edges = hull.m_edges.m_data;

	// 1. One plane per face: visit each face once, from its smallest half-edge index.
	for (int i = 0; i < hull.m_edges.getSize(); i++)
	{
		const hkGeomEdge edge = hull.m_edges[i];
		const int next = edge.m_next;
		const int next2 = edges[next].m_next;
		if (i < next && i < next2)
		{
			hkVector4& plane = *planeEquations.expandBy(1);
			const hkVector4 p0 = hull.m_vertices[edge.m_vertex];
			const hkGeomEdge* e1 = &edges[next];
			const hkVector4 p1 = hull.m_vertices[e1->m_vertex];
			const hkGeomEdge* e2 = &edges[next2];
			const hkVector4 p2 = hull.m_vertices[e2->m_vertex];

			hkVector4 d1; d1.setSub4(p0, p1); d1.normalize3();
			hkVector4 d2; d2.setSub4(p2, p1); d2.normalize3();
			plane.setCross(d1, d2);
			if (plane.lengthSquared3() < tolerances.m_minNormalLengthSq)
			{
				planeEquations.setSize(planeEquations.getSize() - 1);
			}
			else
			{
				plane.normalize3();
				plane.setPlaneDistance(p0);
				PlaneAndPoints& pp = planesAndPoints.expandOne();
				pp.m_plane = plane;
				pp.m_edge0 = &hull.m_edges[i];
				pp.m_edge1 = e1;
				pp.m_edge2 = e2;
				pp.sort();
			}
		}
	}

	// 2. Opposing faces (a + b ~ 0) mean a flat hull: snap a to -b and add the planes for the shared edges.
	planarHullFound = false;
	for (int i = 0; i < planesAndPoints.getSize(); i++)
	{
		for (int j = i + 1; j < planesAndPoints.getSize(); j++)
		{
			PlaneAndPoints a = planesAndPoints[i];
			PlaneAndPoints b = planesAndPoints[j];
			hkVector4 sum; sum.setAdd4(b.m_plane, a.m_plane);
			if (sum.lengthSquared4() < tolerances.m_opposingPlaneTolerance)
			{
				a.m_plane.setNeg3(b.m_plane);
				planarHullFound = true;
				const hkGeomEdge* a0 = a.m_edge0;
				const hkGeomEdge* a1 = a.m_edge1;
				const hkGeomEdge* a2 = a.m_edge2;
				if (sharesEdgePair(edges, a0, b.m_edge0, a1, b.m_edge1, a, b) ||
					sharesEdgePair(edges, a0, b.m_edge0, a1, b.m_edge2, a, b))
				{
					planarHullFound = true;
					addPlanesForOpposingFace(a.m_plane, vertices[a0->m_vertex], vertices[a1->m_vertex], vertices[a2->m_vertex], planeEquations);
				}
				if (sharesEdgePair(edges, a0, b.m_edge0, a2, b.m_edge1, a, b) ||
					sharesEdgePair(edges, a0, b.m_edge0, a2, b.m_edge2, a, b))
				{
					planarHullFound = true;
					addPlanesForOpposingFace(a.m_plane, vertices[a0->m_vertex], vertices[a2->m_vertex], vertices[a1->m_vertex], planeEquations);
				}
				if (sharesEdgePair(edges, a1, b.m_edge0, a2, b.m_edge1, a, b) ||
					sharesEdgePair(edges, a1, b.m_edge0, a2, b.m_edge2, a, b) ||
					sharesEdgePair(edges, a1, b.m_edge1, a2, b.m_edge2, a, b))
				{
					planarHullFound = true;
					addPlanesForOpposingFace(a.m_plane, vertices[a1->m_vertex], vertices[a2->m_vertex], vertices[a0->m_vertex], planeEquations);
				}
			}
		}
	}
	if (planarHullFound)
	{
		// Normal of the plane through the first three used vertices.
		const hkVector4* v = usedVertices.m_data;
		hkVector4 a; a.setSub4(v[0], v[1]);
		hkVector4 b; b.setSub4(v[0], v[2]);
		planarNormal.setCross(a, b);
		planarNormal.normalize3();
		planarNormal.setPlaneDistance(usedVertices.m_data[0]);
	}

	int numWelded;
	sortAndWeld(tolerances, planeEquations, numWelded);

	// 3. Fewer than two planes: the hull is a point or a segment. Bound it with 6 planes.
	const int numPlanes = planeEquations.getSize();
	if (numPlanes < 2)
	{
		hkVector4 p0, p1;
		if (hull.m_edges.getSize() == 1)
		{
			p0 = hull.m_vertices[hull.m_edges[0].m_vertex];
			p1 = p0;
			p1.x = p0.x + 1.0f;
		}
		else
		{
			p0 = hull.m_vertices[hull.m_edges[0].m_vertex];
			p1 = hull.m_vertices[hull.m_edges[hull.m_edges[0].m_twin].m_vertex];
		}
		hkVector4 dir; dir.setSub4(p0, p1);

		// The coordinate axis most perpendicular to the segment.
		float bestDot = HK_REAL_MAX;
		hkVector4 bestAxis;
		for (int k = 0; k < 3; k++)
		{
			hkVector4 axis;
			axis.x = 0.0f; axis.y = 0.0f; axis.z = 0.0f;
			(&axis.x)[k] = 1.0f;
			const float d = fabsf(axis.dot3(dir));
			if (d < bestDot)
			{
				bestDot = d;
				bestAxis.x = axis.x; bestAxis.y = axis.y; bestAxis.z = axis.z;
			}
		}

		planeEquations.setSize(numPlanes + 6);
		hkVector4& e0 = planeEquations[numPlanes];
		e0.setCross(dir, bestAxis);
		e0.normalize3Stored();
		e0.setPlaneDistance(p0);

		hkVector4& e1 = planeEquations[numPlanes + 1];
		e1.setCross(dir, e0);
		e1.normalize3Stored();
		e1.setPlaneDistance(p0);

		hkVector4& e2 = planeEquations[numPlanes + 2];
		e2.setNeg4(e0);
		e2.setPlaneDistance(p0);

		hkVector4& e3 = planeEquations[numPlanes + 3];
		e3.setNeg4(e1);
		e3.setPlaneDistance(p0);

		hkVector4& e4 = planeEquations[numPlanes + 4];
		e4 = dir;
		e4.normalize3();
		e4.setPlaneDistance(p0);

		hkVector4& e5 = planeEquations[numPlanes + 5];
		e5.setNeg4(e4);
		e5.normalize3();
		if (hull.m_edges.getSize() == 1)
			e5.setPlaneDistance(p0);
		else
			e5.setPlaneDistance(p1);
	}

	// 4. Flat hull: rebuild the planes from the planar points.
	if (planarHullFound && tolerances.m_postFilter)
	{
		planeEquations.clear();
		hkArray<hkVector4> usedPoints;
		generateHullFromPlanarPoints(planarNormal, usedVertices.m_data, usedVertices.getSize(), usedPoints, planeEquations);
	}

	sortAndWeld(tolerances, planeEquations, numWelded);
	return true;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct hkGeomConvexHullBuilder {
    void sharesEdgePair(void*, void*, void*, void*, void*, int&, int&); // 0x01115730
    void addPlanesForOpposingFace(int&, int&, int&, int&, int&); // 0x01116f90
};
}
