// Slice s0111bc80 (Havok 3.1.0 convex-hull builder core).
//
//   0x0111bc80  hkGeomConvexHullBuilder::buildHullRecursive   (unnamed in the DB; recursive divide-and-conquer
//                                                              hull builder: degenerate 1/2/3-vertex hulls,
//                                                              split, recurse, markRedundantVertices, merge)
//   0x0111c160  hkGeomConvexHullBuilder::buildConvexHull      (DB name)
//   0x0111c2e0  hkGeomConvexHullBuilder::createConvexHull     (unnamed; copy input, sort, build, retry with
//                                                              loosened tolerances)
//   0x0111c6e0  hkGeomHull::initializeWithVertex              (unnamed; 1-vertex degenerate hull)
//   0x0111c740  hkGeomHull::initializeWithLine                (unnamed; 2-vertex degenerate hull)
//
// Compile flags: /vc71 /O2 /MD /Gy /TP   (Havok 3.1.0 shipped with the VC7.1 toolchain, no /EHsc).
// Layouts follow the sibling slices (s0111c7f0, s0111b170, s01118f50).
#include "types.h"
#include <math.h>

#ifdef _WIN32
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
#endif

typedef uint32_t hkUint32;
typedef uint16_t hkUint16;
typedef uint8_t hkUint8;

class hkBool
{
public:
	hkBool() {}
	hkBool(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
	char m_bool;
};

enum hkResult { HK_SUCCESS = 0, HK_FAILURE = 1 };
enum { HK_MEMORY_CLASS_ARRAY = 0x14 };

extern unsigned long g_hkThreadMemoryTlsIndex;   // 0x016E4174

class hkThreadMemory
{
public:
	virtual void tm0(); virtual void tm1(); virtual void tm2();
	virtual void* allocateStackChunk(int nbytes);       // slot 3 (+0xc)
	virtual void releaseStackChunk(void* p);            // slot 4 (+0x10)
	void deallocateChunk(void* p, int nbytes, int memClass);   // 0x0107DB10
	static hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }
};

struct hkArrayUtil { static void _reserveMore(void* array, int elemSize); };   // 0x0107F530

template <class T>
class hkArray
{
public:
	enum { CAPACITY_MASK = 0x3FFFFFFF, DONT_DEALLOCATE_FLAG = (int)0x80000000 };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;
	hkArray() : m_data(0), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}
	hkArray(T* buffer, int size, int capacity) : m_data(buffer), m_size(size), m_capacityAndFlags(capacity | DONT_DEALLOCATE_FLAG) {}
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
	void clear() { m_size = 0; }
};

struct __declspec(align(16)) hkVector4
{
	float x, y, z, w;
};

// Half-edge hull edge: origin vertex, twin edge, next edge in the face (+ a padding word).
struct hkGeomEdge
{
	hkUint16 m_vertex;   // +0
	hkUint16 m_twin;     // +2
	hkUint16 m_next;     // +4
	hkUint16 m_pad;      // +6 (never written by this slice; stack garbage in the binary)
};

// hkArray with an inline element buffer; the capacity field keeps the DONT_DEALLOCATE flag.
template <class T, int N>
class hkInplaceArray : public hkArray<T>
{
public:
	T m_inline[N];
	hkInplaceArray() : hkArray<T>(m_inline, 0, N) {}
};

class hkGeomHull
{
public:
	const hkVector4* m_vertices;                 // +0
	hkInplaceArray<hkGeomEdge, 128> m_edges;     // +4 (data), +8 (size), +0xc (capacity), buffer +0x10

	hkGeomHull() : m_vertices(0) {}              // 0x0111cc90
	void initializeWithVertex(hkUint16 v);           // 0x0111c6e0 (name guessed)
	void initializeWithLine(hkUint16 a, hkUint16 b); // 0x0111c740 (name guessed)
	void initializeWithTriangle(int a, int b, int c);// 0x0111c7f0
};

// @ 0x0111c6e0
void hkGeomHull::initializeWithVertex(hkUint16 v)
{
	m_edges.m_size = 0;
	hkGeomEdge e;
	e.m_vertex = v;
	e.m_twin = 0;
	e.m_next = 0;
	m_edges.pushBack(e);
}

// @ 0x0111c740
void hkGeomHull::initializeWithLine(hkUint16 a, hkUint16 b)
{
	m_edges.m_size = 0;
	hkGeomEdge e0;
	e0.m_vertex = a;
	e0.m_twin = 1;
	e0.m_next = 1;
	hkGeomEdge e1;
	e1.m_vertex = b;
	e1.m_twin = 0;
	e1.m_next = 0;
	m_edges.pushBack(e0);
	m_edges.pushBack(e1);
}

// ---- convex-hull builder tolerances --------------------------------------------------------------
// 0x34 bytes: {char,char,char,char, float[12]} (offsets taken from the builder's use sites).
struct hkGeomConvexHullTolerances
{
	hkBool m_flag0;          // +0
	char m_recentre;         // +1 (name guessed)
	char m_removeCollinear;  // +2 (name guessed)
	char m_pad3;             // +3
	float m_weldTolerance;   // +4 (name guessed)
	float m_more[11];        // +8 .. +0x30
};

// ---- callees (defined in sibling slices) ---------------------------------------------------------
void recentreVertices(hkArray<hkVector4>* verts, hkVector4* extents, hkVector4* center);   // 0x01115e20
void removeUnusedVertices(hkGeomHull& hull, hkArray<hkVector4>& verts);                    // 0x0111a0f0
void removeFlaggedVertices(hkArray<hkVector4>& verts);                                     // 0x01117140
void removeCollinearVertices(hkArray<hkVector4>& verts, float tolerance);                  // 0x01118340
void weldXsortedVertices(float tolerance, hkArray<hkVector4>& verts, int& outCount);       // 0x01116d50
void markRedundantVertices(hkGeomHull& hull, int first, int last,
	const hkGeomConvexHullTolerances& tolerances, hkBool& changed);                        // 0x011187d0
void buildHullRecursive(const hkGeomConvexHullTolerances& tolerances, hkArray<hkVector4>* verts,
	int first, int last, hkGeomHull& hull);                                                // 0x0111bc80
void quickSortVertices(hkVector4* data, int lo, int hi, hkBool (*less)(hkVector4&, hkVector4&)); // 0x011155b0

class hkGeomConvexHullBuilder
{
public:
	static hkBool vectorLessAndMergeCoordinates(hkVector4& a, hkVector4& b);                     // 0x01115950
	static void convertFromUnitCube(hkArray<hkVector4>& verts, hkVector4& scale, hkVector4& translation); // 0x01116050
	static void buildConvexHull(const hkGeomConvexHullTolerances& tolerances, const hkVector4* vertices,
		int numVertices, hkGeomHull& hull, hkArray<hkVector4>& outVertices);                    // 0x0111c160
	static void createConvexHull(const hkVector4* vertices, int numVertices, hkGeomHull& hull,
		hkArray<hkVector4>& outVertices, int mode);                                             // 0x0111c2e0 (name guessed)
};

// @ 0x0111c160
void hkGeomConvexHullBuilder::buildConvexHull(const hkGeomConvexHullTolerances& tolerances,
	const hkVector4* vertices, int numVertices, hkGeomHull& hull, hkArray<hkVector4>& outVertices)
{
	outVertices.m_size = 0;
	for (int i = 0; i < numVertices; ++i)
		outVertices.pushBack(vertices[i]);

	hkVector4 scale;
	hkVector4 center;
	if (tolerances.m_recentre)
		recentreVertices(&outVertices, &scale, &center);

	if (outVertices.m_size > 1)
		quickSortVertices(outVertices.m_data, 0, outVertices.m_size - 1, vectorLessAndMergeCoordinates);

	int welded;
	weldXsortedVertices(tolerances.m_weldTolerance, outVertices, welded);
	if (tolerances.m_removeCollinear && welded < 300)
		removeCollinearVertices(outVertices, 0.001f);

	hkBool changed(1);
	char stuck = 0;
	char cur = 1;
	char prev = 0;
	while (prev == 0 || cur != 0)
	{
		stuck = (cur == 0);
		for (int i = 0; i < outVertices.m_size; ++i)
			outVertices.m_data[i].w = 0.0f;
		hull.m_edges.m_size = 0;
		buildHullRecursive(tolerances, &outVertices, 0, outVertices.m_size - 1, hull);
		removeUnusedVertices(hull, outVertices);
		removeFlaggedVertices(outVertices);
		markRedundantVertices(hull, 0, outVertices.m_size - 1, tolerances, changed);
		removeFlaggedVertices(outVertices);
		cur = stuck;
		prev = changed.m_bool;
	}

	if (tolerances.m_recentre)
		convertFromUnitCube(outVertices, scale, center);
}

// ---- more callees (defined in sibling slices) ----------------------------------------------------
hkResult mergeHulls(const hkGeomConvexHullTolerances& tolerances, hkGeomHull& a, hkGeomHull& b,
	hkGeomHull& out);                                                                      // 0x0111b170
hkBool isValidHull(const hkGeomConvexHullTolerances& tolerances, const hkVector4* vertices,
	int numVertices, hkGeomHull& hull, hkArray<hkVector4>& verts);                         // 0x011228f0
hkBool buildPlaneEquations(const hkGeomConvexHullTolerances& tolerances, hkGeomHull& hull,
	const hkArray<hkVector4>& verts, hkVector4& outPlane, hkVector4& outPoint,
	hkArray<hkVector4>& outVerts, hkArray<struct PlaneAndPoints>& outPlanes);              // 0x01118f50
void generateHullFromPlanarPoints(const hkVector4& plane, const hkVector4* points, int numPoints,
	hkArray<hkVector4>& verts, hkArray<hkVector4>& out);                                   // 0x01117840

struct PlaneAndPoints { hkVector4 m_plane; hkVector4 m_points; };   // 32 bytes (0x01118f50 element)

// Floating-point bit pattern helper (the binary stores the tolerance constants as raw dwords).
static inline float hkFloatBits(unsigned int bits) { union { unsigned int u; float f; } v; v.u = bits; return v.f; }

// @ 0x0111bc80
void buildHullRecursive(const hkGeomConvexHullTolerances& tolerances, hkArray<hkVector4>* verts,
	int first, int last, hkGeomHull& hull)
{
	int count = 0;
	const int end = last + 1;
	int i = first;
	if (end - first > 3)
	{
		for (; i + 4 <= end; i += 4)
		{
			count += (verts->m_data[i].w == 0.0f);
			count += (verts->m_data[i + 1].w == 0.0f);
			count += (verts->m_data[i + 2].w == 0.0f);
			count += (verts->m_data[i + 3].w == 0.0f);
		}
	}
	for (; i < end; ++i)
		count += (verts->m_data[i].w == 0.0f);

	if (count < 4)
	{
		hull.m_vertices = verts->m_data;
		hkInplaceArray<int, 3> zeroVertices;
		for (int j = first; j < end; ++j)
			if (verts->m_data[j].w == 0.0f)
				zeroVertices.pushBack(j);
		if (count != 0)
		{
			if (count == 1)
				hull.initializeWithVertex((hkUint16)zeroVertices[0]);
			else if (count == 2)
				hull.initializeWithLine((hkUint16)zeroVertices[0], (hkUint16)zeroVertices[1]);
			else
				hull.initializeWithTriangle(zeroVertices[0], zeroVertices[1], zeroVertices[2]);
		}
		return;
	}

	const int mid = (first + last) / 2;
	hkGeomHull hull1;
	hull1.m_vertices = verts->m_data;
	hkGeomHull hull2;
	hull2.m_vertices = verts->m_data;

	hkBool flag(1);
	do
	{
		do
		{
			hull1.m_edges.m_size = 0;
			buildHullRecursive(tolerances, verts, first, mid, hull1);
			markRedundantVertices(hull1, first, mid, tolerances, flag);
		} while (flag.m_bool != 0);
		flag.m_bool = 1;
		do
		{
			hull2.m_edges.m_size = 0;
			buildHullRecursive(tolerances, verts, mid + 1, last, hull2);
			markRedundantVertices(hull2, mid + 1, last, tolerances, flag);
		} while (flag.m_bool != 0);
		hkBool f1(1);
		hkBool f2(1);
		markRedundantVertices(hull1, first, last, tolerances, f1);
		markRedundantVertices(hull2, first, last, tolerances, f2);
		flag.m_bool = (f1.m_bool == 0 && f2.m_bool == 0) ? 0 : 1;
	} while (flag.m_bool != 0);

	if (hull1.m_edges.m_size == 0)
	{
		for (int j = 0; j < hull2.m_edges.m_size; ++j)
			hull.m_edges.pushBack(hull2.m_edges[j]);
	}
	else if (hull2.m_edges.m_size == 0)
	{
		for (int j = 0; j < hull1.m_edges.m_size; ++j)
			hull.m_edges.pushBack(hull1.m_edges[j]);
	}
	else
	{
		mergeHulls(tolerances, hull1, hull2, hull);
	}
	if (hull.m_edges.m_size == 0)
		hull1.m_edges = hull.m_edges;
}

// @ 0x0111c2e0
void hkGeomConvexHullBuilder::createConvexHull(const hkVector4* vertices, int numVertices,
	hkGeomHull& hull, hkArray<hkVector4>& outVertices, int mode)
{
	hkGeomConvexHullTolerances tolerances;
	tolerances.m_flag0 = 0;
	tolerances.m_recentre = 0;
	tolerances.m_removeCollinear = (mode == 2);
	tolerances.m_weldTolerance = hkFloatBits(0x37a7c5ac);   // +4
	tolerances.m_more[0]  = hkFloatBits(0x368637bd);        // +8
	tolerances.m_more[1]  = hkFloatBits(0x358637bd);        // +0xc
	tolerances.m_more[2]  = hkFloatBits(0x3727c5ac);        // +0x10
	tolerances.m_more[3]  = hkFloatBits(0x3d4ccccd);        // +0x14
	tolerances.m_more[4]  = hkFloatBits(0x358637bd);        // +0x18
	tolerances.m_more[5]  = hkFloatBits(0x358637bd);        // +0x1c
	tolerances.m_more[6]  = hkFloatBits(0x322bcc77);        // +0x20
	tolerances.m_more[7]  = hkFloatBits(0x358637bd);        // +0x24
	tolerances.m_more[8]  = hkFloatBits(0x38d1b717);        // +0x28
	tolerances.m_more[9]  = hkFloatBits(0x3727c5ac);        // +0x2c
	tolerances.m_more[10] = hkFloatBits(0x37a7c5ac);        // +0x30

	hkArray<hkVector4> work;
	if (numVertices > 0)
	{
		for (int i = 0; i < numVertices; ++i)
			work.pushBack(vertices[i]);
		if (work.m_size > 1)
			quickSortVertices(work.m_data, 0, work.m_size - 1, vectorLessAndMergeCoordinates);
	}

	int welded;
	weldXsortedVertices(tolerances.m_weldTolerance, work, welded);

	hkArray<hkVector4> weldOut;
	outVertices.m_size = 0;
	buildConvexHull(tolerances, work.m_data, work.m_size, hull, outVertices);
	hkBool valid = isValidHull(tolerances, work.m_data, work.m_size, hull, outVertices);

	if (!valid)
	{
		if (mode == 2)
		{
			weldOut.m_size = 0;
			hkVector4 plane;
			hkVector4 plane2;
			hkArray<PlaneAndPoints> planes;
			hkBool planar = buildPlaneEquations(tolerances, hull, work, plane, plane2, weldOut, planes);
			if (planar)
			{
				outVertices.m_size = 0;
				removeCollinearVertices(work, hkFloatBits(0x3a83126f));
				hkArray<hkVector4> planarVerts;
				generateHullFromPlanarPoints(plane, work.m_data, work.m_size, outVertices, planarVerts);
				valid = isValidHull(tolerances, vertices, numVertices, hull, outVertices);
				if (planarVerts.m_capacityAndFlags >= 0)
					hkThreadMemory::getInstance().deallocateChunk(planarVerts.m_data, planarVerts.getCapacity() * (int)sizeof(hkVector4), HK_MEMORY_CLASS_ARRAY);
			}
			if (planes.m_capacityAndFlags >= 0)
				hkThreadMemory::getInstance().deallocateChunk(planes.m_data, planes.getCapacity() * (int)sizeof(PlaneAndPoints), HK_MEMORY_CLASS_ARRAY);
			goto cleanup;
		}
	}
	else if (mode == 2)
	{
		goto cleanup;
	}

	tolerances.m_recentre = 1;
	if (!valid)
	{
		tolerances.m_flag0 = 1;
		buildConvexHull(tolerances, vertices, numVertices, hull, outVertices);
		valid = isValidHull(tolerances, vertices, numVertices, hull, outVertices);
		if (!valid)
		{
			tolerances.m_more[0] = hkFloatBits(0x3456bf95);   // +8
			buildConvexHull(tolerances, vertices, numVertices, hull, outVertices);
			valid = isValidHull(tolerances, vertices, numVertices, hull, outVertices);
			if (!valid)
			{
				tolerances.m_more[10] = hkFloatBits(0x358637bd);   // +0x30
				buildConvexHull(tolerances, vertices, numVertices, hull, outVertices);
				isValidHull(tolerances, vertices, numVertices, hull, outVertices);
			}
		}
	}
cleanup:
	if (weldOut.m_capacityAndFlags >= 0)
		hkThreadMemory::getInstance().deallocateChunk(weldOut.m_data, weldOut.getCapacity() * (int)sizeof(hkVector4), HK_MEMORY_CLASS_ARRAY);
	if (work.m_capacityAndFlags >= 0)
		hkThreadMemory::getInstance().deallocateChunk(work.m_data, work.getCapacity() * (int)sizeof(hkVector4), HK_MEMORY_CLASS_ARRAY);
}
