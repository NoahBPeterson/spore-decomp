// Havok 3.1.0 (VC .NET 2003, cl 13.10) — hkGeomConvexHullBuilder hull-welding helpers.
//
// 0x011161B0 isSingleLine            — true when the two hulls collapse to one line; builds the 2-edge merged hull.
// 0x01116620 getPlaneEquationZaxis   — plane through p0,p1 whose normal is perpendicular to the Z axis.
// 0x01116880 getCommonTangent        — the common tangent line of two hulls (grows it to a wrapping tangent).
// 0x01116A20 getAngleBetweenVertexAndPlane — wrapped angle (0..8) of a vertex off a plane, with tolerances.
// 0x01116D00 PlaneAndPoints::sort    — 3-element compare/swap on the face's half-edge pointers.
// 0x01116D50 weldXsortedVertices     — welds near-duplicate vertices in an x-sorted array.
// 0x01116F90 addPlanesForOpposingFace— (name guessed) adds the extra planes for an opposing face pair.
//
// Self-contained; same Havok conventions as match/slices/s01118f50 (kZero/kOne come from the constant pool).
// hkVector4 is 16-byte aligned (the original frames do `and esp,-16`).
// Unnamed callees carry Claude-coined names marked "(name guessed)".
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
	T* begin() { return m_data; }
	void clear() { m_size = 0; }
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

// Havok 3.1 was built by an older cl that loads 0.0f/1.0f from the constant pool (0x01485378 / 0x01485720).
extern const float kZero;   // 0x01485378
extern const float kOne;    // 0x01485720
__forceinline float hkMath_sqrt(double r) { return (float)sqrt(r); }   // hkMath::sqrt (inline fsqrt)

// Havok's generic swap (hkAlgorithm); the allocator relies on it being a plain
// three-assignment template so that the temporaries coalesce with the operands.
template <class T>
inline void hkSwap(T& a, T& b) { T t = a; a = b; b = t; }

class __declspec(align(16)) hkVector4
{
public:
	float x, y, z, w;

	__forceinline void setSub4(const hkVector4& a, const hkVector4& b) { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
	__forceinline void setAdd4(const hkVector4& a, const hkVector4& b) { x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; w = a.w + b.w; }
	__forceinline void setNeg3(const hkVector4& a) { x = -a.x; y = -a.y; z = -a.z; }
	__forceinline void setCross3(const hkVector4& a, const hkVector4& b)
	{
		x = a.y * b.z - a.z * b.y;
		y = a.z * b.x - a.x * b.z;
		z = a.x * b.y - a.y * b.x;
	}
	__forceinline void mul4(float s) { x = x * s; y = y * s; z = z * s; w = w * s; }
	// Havok's x87 lengthSquared3 sums z, y, x in that order.
	__forceinline float lengthSquared3() const { return z * z + y * y + x * x; }
	__forceinline float dot3(const hkVector4& a) const { return z * a.z + y * a.y + x * a.x; }
	static __forceinline float invSqrtOrZero(float len2) { return (len2 == kZero) ? kZero : kOne / hkMath_sqrt(len2); }
	// Same, but the reciprocal stays in x87 extended precision (no float32 rounding of the
	// sqrt or the division): the original computes `1/sqrt(len2)` with `fsqrt`/`fdivr` and
	// hands the register value on unrounded.
	static __forceinline double invSqrtOrZeroExt(double len2) { return (len2 == 0.0) ? 0.0 : (double)kOne / sqrt(len2); }
	// The 80-bit x87 value is passed on as a double so it is not flushed to float32 (which would
	// overflow for a length near FLT_MAX; the original keeps it in a register).
	static __forceinline float invSqrtOrZeroD(double len2) { return (len2 == 0.0) ? kZero : (float)(kOne / hkMath_sqrt(len2)); }
	__forceinline void normalize3() { mul4(invSqrtOrZero(lengthSquared3())); }
};

struct hkGeomEdge
{
	uint16_t m_vertex;   // +0
	uint16_t m_twin;     // +2 (index of the opposite half-edge)
	uint16_t m_next;     // +4 (next half-edge of the face)
	uint16_t m_pad;      // +6
};

class hkGeomHull
{
public:
	const hkVector4* m_vertices;      // +0
	hkArray<hkGeomEdge> m_edges;      // +4

	// 0x0111C740 (name guessed): rebuild this hull as a single line between the two vertices.
	void initializeWithLine(unsigned short a, unsigned short b);   // 0x0111C740
};

struct hkGeomConvexHullTolerances
{
	uint32_t m_pad0[2];
	float m_distanceTolerance;   // +8 (name guessed): below it the vertex/plane angle is 0
	uint32_t m_padC[9];
	float m_angleTolerance;      // +0x30 (name guessed): wrap tolerance for the returned angle
};

class hkGeomConvexHullBuilder
{
public:
	struct WeightedLine
	{
		hkGeomEdge* m_edgeA;          // +0 (name guessed): edge in hull A
		hkGeomEdge* m_edgeB;          // +4 (name guessed): edge in hull B
		WeightedLine* m_lastLine;     // +8 (name guessed)
		int m_lastVertex;             // +0xc (name guessed)
		float m_weight;               // +0x10
	};

	struct PlaneAndPoints
	{
		hkVector4 m_plane;               // +0
		const hkGeomEdge* m_edge0;       // +0x10
		const hkGeomEdge* m_edge1;       // +0x14
		const hkGeomEdge* m_edge2;       // +0x18
		void sort();                     // 0x01116D00
	};

	static hkBool isSingleLine(float tolerance, hkGeomHull& hullA, hkGeomHull& hullB, hkGeomHull& mergedHull);   // 0x011161B0
	static void getPlaneEquationZaxis(const hkVector4& p0, const hkVector4& p1, hkVector4& plane);               // 0x01116620
	static void getCommonTangent(hkGeomHull& hullA, hkGeomHull& hullB, WeightedLine& line, hkVector4& normal);   // 0x01116880
	static float getAngleBetweenVertexAndPlane(const hkGeomConvexHullTolerances& tol, const hkVector4& A,
		const hkVector4& plane, const hkVector4& C, const hkVector4& D);                                        // 0x01116A20
	static void weldXsortedVertices(float tolerance, hkArray<hkVector4>& verts, int& numWelded);                 // 0x01116D50
	static void addPlanesForOpposingFace(const hkVector4& plane, const hkVector4& v0, const hkVector4& v1,
		const hkVector4& v2, hkArray<hkVector4>& planeEquations);                                               // 0x01116F90
};

// @ 0x01116d00
void hkGeomConvexHullBuilder::PlaneAndPoints::sort()
{
	if (m_edge0->m_vertex > m_edge1->m_vertex)
		hkSwap(m_edge0, m_edge1);
	if (m_edge1->m_vertex > m_edge2->m_vertex)
		hkSwap(m_edge1, m_edge2);
	if (m_edge0->m_vertex > m_edge1->m_vertex)
		hkSwap(m_edge0, m_edge1);
}

// @ 0x01116620
void hkGeomConvexHullBuilder::getPlaneEquationZaxis(const hkVector4& p0, const hkVector4& p1, hkVector4& plane)
{
	// The differences are kept in extended precision for the tolerance test (the original
	// compares the x87 values) but rounded to float32 for every product below.
	const double dxe = (double)p0.x - p1.x;
	const double dye = (double)p0.y - p1.y;
	const double dze = (double)p0.z - p1.z;
	const float dx = (float)dxe;
	const float dy = (float)dye;
	const float dz = (float)dze;

	if (fabs(dxe) < 1e-6 && fabs(dye) < 1e-6)
	{
		plane.w = kZero;
		const float px = dy * kZero - dz * kZero;
		plane.x = px;
		const float py = dz - dx * kZero;
		plane.y = py;
		const float pz = dx * kZero - dy;
		plane.z = pz;
		const float inv = hkVector4::invSqrtOrZero(px * px + py * py + pz * pz);
		plane.x = px * inv;
		plane.y = py * inv;
		plane.z = pz * inv;
		plane.w = inv * kZero;
		return;
	}

	const double dz2 = (double)dz * dz;
	const double dy2 = (double)dy * dy;
	const double dx2 = (double)dx * dx;
	const double len2 = (dz2 + dy2) + dx2;
	const double inv = hkVector4::invSqrtOrZeroExt(len2);
	// The original never rounds ndx/ndz out of the x87 register, but does round ndy to a
	// float32 slot and reload it (0x01116667 `fstp [esp+0x24]`).  Keeping ndx extended is
	// what makes the sub-branch's `ndz*0 - ndx` collapse to the reference's signed zero when
	// ndx is below the float32 denormal range (dx tiny * inv tiny).
	const double ndx = (double)dx * inv;
	const float ndy = (float)((double)dy * inv);
	const double ndz = (double)dz * inv;

	plane.w = kZero;
	plane.x = (float)((double)ndy * kZero - ndz);       // cross(n, (0,1,0))
	plane.y = (float)(ndz * kZero - ndx * kZero);
	const double pz = ndx - (double)ndy * kZero;        // held unrounded for the length test
	plane.z = (float)pz;

	if ((double)plane.x * plane.x + (double)plane.y * plane.y + pz * pz < 1.1920929e-7f)
	{
		// plane.w is already kZero from the store above; the original reloads a zero into
		// edx here (not eax), so re-storing it would clobber eax that the caller sees.
		plane.x = (float)((double)ndy - ndz * kZero);   // cross(n, (0,0,1))
		plane.y = (float)(ndz * kZero - ndx);
		plane.z = (float)(ndx * kZero - (double)ndy * kZero);
	}

	const double plen = ((double)plane.x * plane.x + (double)plane.y * plane.y) + (double)plane.z * plane.z;
	const double inv2 = (plen == 0.0) ? 0.0 : (double)kOne / sqrt(plen);
	plane.x = (float)((double)plane.x * inv2);
	plane.y = (float)((double)plane.y * inv2);
	plane.z = (float)((double)plane.z * inv2);
	plane.w = (float)(inv2 * kZero);
}

// @ 0x01116880
void hkGeomConvexHullBuilder::getCommonTangent(hkGeomHull& hullA, hkGeomHull& hullB, WeightedLine& line, hkVector4& normal)
{
	line.m_edgeA = hullA.m_edges.m_data;
	line.m_edgeB = hullB.m_edges.m_data;
	line.m_lastLine = 0;
	line.m_weight = kZero;
	line.m_lastVertex = -1;

	const hkVector4* vertices = hullA.m_vertices;
	const hkVector4* a = &vertices[line.m_edgeA->m_vertex];
	const hkVector4* b = &vertices[line.m_edgeB->m_vertex];
	getPlaneEquationZaxis(*a, *b, normal);

	const int maxIter = (hullA.m_edges.getSize() + hullB.m_edges.getSize()) * 2;
	for (int iter = 0; iter < maxIter; iter++)
	{
		bool changed = false;

		for (int i = hullA.m_edges.getSize() - 1; i >= 0; i--)
		{
			const hkVector4* p = &vertices[hullA.m_edges[i].m_vertex];
			if (1e-7f < normal.z * (p->z - a->z) + normal.x * (p->x - a->x) + normal.y * (p->y - a->y))
			{
				line.m_edgeA = &hullA.m_edges[i];
				getPlaneEquationZaxis(*p, *b, normal);
				changed = true;
				a = p;
			}
		}

		for (int i = hullB.m_edges.getSize() - 1; i >= 0; i--)
		{
			const hkVector4* p = &vertices[hullB.m_edges[i].m_vertex];
			if (1e-7f < normal.z * (p->z - b->z) + normal.x * (p->x - b->x) + normal.y * (p->y - b->y))
			{
				line.m_edgeB = &hullB.m_edges[i];
				getPlaneEquationZaxis(*a, *p, normal);
				changed = true;
				b = p;
			}
		}

		if (!changed)
			return;
		getPlaneEquationZaxis(*a, *b, normal);
	}
}

// @ 0x01116a20
float hkGeomConvexHullBuilder::getAngleBetweenVertexAndPlane(const hkGeomConvexHullTolerances& tol, const hkVector4& A,
	const hkVector4& plane, const hkVector4& C, const hkVector4& D)
{
	const float dx = A.x - C.x;
	const float dy = A.y - C.y;
	const float dz = A.z - C.z;
	const double len2 = (double)(dz * dz + dy * dy + dx * dx);
	if (len2 < tol.m_distanceTolerance)
		return 0.0f;

	const float inv = hkVector4::invSqrtOrZeroD(len2);
	const float ndx = dx * inv;
	const float ndy = dy * inv;
	const float ndz = dz * inv;
	const float negd = -(ndz * plane.z + (ndy * plane.y + ndx * plane.x));

	hkVector4 e;
	e.setSub4(C, D);
	// The original spills the cross components to float32 stack slots; with values near
	// FLT_MAX that turns the z component into +inf and the 0*inf in the dot product into
	// NaN (the x87 register alone would stay finite). Keep the components in memory.
	volatile hkVector4 cross;
	cross.x = e.y * plane.z - e.z * plane.y;
	cross.y = e.z * plane.x - e.x * plane.z;
	cross.z = e.x * plane.y - e.y * plane.x;
	cross.w = 0.0f;
	const float inv2 = hkVector4::invSqrtOrZero(cross.z * cross.z + cross.y * cross.y + cross.x * cross.x);
	const float dot = (cross.x * inv2) * ndx + ((cross.y * inv2) * ndy + (cross.z * inv2) * ndz);

	if (negd * negd + dot * dot < tol.m_distanceTolerance)
		return 1.70141e+38f;

	const float andd = fabsf(negd);
	const float adot = fabsf(dot);
	const float angleTol = tol.m_angleTolerance;

	float v;
	if (andd < 1e-6f && adot < 1e-7f)
	{
		v = (dot < 0.0f) ? 4.0f : kZero;
	}
	else if (adot < andd)
	{
		v = 2.0f - dot / negd;
		if (negd < -1e-6f)
			v += 4.0f;
	}
	else
	{
		v = negd / dot;
		if (dot < -0.999999f && andd < 1e-6f)
			v = 4.0f;
		else if (dot < -1e-6f)
			v += 4.0f;
		if (fabsf(v) < angleTol)
			v = kZero;
		else if (dot > 1e-6f && andd < 1e-7f)
			v += 8.0f;
	}

	if (v < -angleTol)
		v += 8.0f;
	if (v > 8.0f)
		v = kZero;
	return v;
}

// @ 0x01116d50
void hkGeomConvexHullBuilder::weldXsortedVertices(float tolerance, hkArray<hkVector4>& verts, int& numWelded)
{
	hkVector4* base = verts.m_data;
	hkVector4* out = base;
	hkVector4* last = base - 1;
	const int size = verts.m_size;

	for (int i = 0; i < size; i++)
	{
		hkVector4* v = base + i;
		bool merged = false;
		for (hkVector4* p = last; p >= base; p--)
		{
			if (p->x < v->x - 0.01f)
				break;
			const float ddx = p->x - v->x;
			const float ddy = p->y - v->y;
			const float ddz = p->z - v->z;
			if (ddz * ddz + ddy * ddy + ddx * ddx < tolerance)
			{
				int j = i + 1;
				while (j < size)
				{
					const float ex = p->x - base[j].x;
					const float ey = p->y - base[j].y;
					const float ez = p->z - base[j].z;
					if (!(ez * ez + ey * ey + ex * ex < tolerance))
						break;
					j++;
				}
				i = j - 1;
				merged = true;
				break;
			}
		}
		if (!merged)
		{
			*out = *v;
			out++;
			last = out - 1;
		}
	}

	const int count = (int)(out - base);
	numWelded = count;
	verts.reserveFor(count);
	verts.m_size = count;
}

// @ 0x01116f90  (name guessed)
void hkGeomConvexHullBuilder::addPlanesForOpposingFace(const hkVector4& plane, const hkVector4& v0, const hkVector4& v1,
	const hkVector4& v2, hkArray<hkVector4>& planeEquations)
{
	hkVector4& e = *planeEquations.expandBy(1);

	// hkVector4::setCross3(plane, v0 - v1)
	const float ex = v0.x - v1.x;
	const float ey = v0.y - v1.y;
	const float ez = v0.z - v1.z;

	e.x = plane.y * ez - plane.z * ey;
	e.y = plane.z * ex - plane.x * ez;
	e.z = plane.x * ey - plane.y * ex;
	e.w = kZero;

	if (1e-6f < (v2.x - v1.x) * e.x + (v2.z - v1.z) * e.z + (v2.y - v1.y) * e.y)
	{
		e.w = kZero;
		e.x = -e.x;
		e.y = -e.y;
		e.z = -e.z;
	}

	const double len2 = (double)(e.z * e.z + e.y * e.y + e.x * e.x);
	if (len2 > 1e-4f)
	{
		const float inv = hkVector4::invSqrtOrZeroD(len2);
		e.x = e.x * inv;
		e.y = e.y * inv;
		e.z = e.z * inv;
		e.w = -(e.z * v0.z + (e.x * v0.x + e.y * v0.y));
		return;
	}
	planeEquations.setSize(planeEquations.getSize() - 1);
}

// @ 0x011161b0
hkBool hkGeomConvexHullBuilder::isSingleLine(float tolerance, hkGeomHull& hullA, hkGeomHull& hullB, hkGeomHull& mergedHull)
{
	const hkVector4* vertices = hullA.m_vertices;
	if (hullA.m_edges.getSize() >= 3 || hullB.m_edges.getSize() >= 3)
		return hkBool(false);

	int idxA, idxB;
	int idxC = 0, idxD = 0;
	int mode = 3;

	if (hullA.m_edges.getSize() == 2)
	{
		int v0 = hullA.m_edges[0].m_vertex;
		int v1 = hullA.m_edges[hullA.m_edges[0].m_twin].m_vertex;
		idxA = v0;
		idxB = v1;
		if (v1 < v0)
		{
			idxA = v1;
			idxB = v0;
		}
		idxC = hullB.m_edges[0].m_vertex;
		if (hullB.m_edges.getSize() == 2)
		{
			idxD = hullB.m_edges[hullB.m_edges[0].m_twin].m_vertex;
			if (idxD < idxC)
			{
				int t = idxC;
				idxC = idxD;
				idxD = t;
			}
			mode = 4;
		}
	}
	else
	{
		if (hullB.m_edges.getSize() != 2)
		{
			mergedHull.initializeWithLine(hullA.m_edges[0].m_vertex, hullB.m_edges[0].m_vertex);
			return hkBool(true);
		}
		idxA = hullA.m_edges[0].m_vertex;
		int v1 = hullB.m_edges[hullB.m_edges[0].m_twin].m_vertex;
		idxC = hullB.m_edges[0].m_vertex;
		idxB = v1;
		if (v1 < idxA)
		{
			idxB = idxA;
			idxA = v1;
		}
	}

	const hkVector4& A = vertices[idxA];
	const hkVector4& B = vertices[idxB];
	const hkVector4& C = vertices[idxC];

	const float bx = B.x - A.x;
	const float by = B.y - A.y;
	const float bz = B.z - A.z;
	const float fVar7 = bz * bz + by * by + bx * bx;

	const float cx = C.x - B.x;
	const float cy = C.y - B.y;
	const float cz = C.z - B.z;
	const float fVar13 = cz * cz + cy * cy + cx * cx;

	const float ax = A.x - C.x;
	const float ay = A.y - C.y;
	const float az = A.z - C.z;
	float local_54 = az * az + ay * ay + ax * ax;

	const float invBA = hkVector4::invSqrtOrZero(fVar7);
	const float invCB = hkVector4::invSqrtOrZero(fVar13);
	const float invAC = hkVector4::invSqrtOrZero(local_54);

	float nx = cx * invCB - bx * invBA;
	float ny = cy * invCB - by * invBA;
	float nz = cz * invCB - bz * invBA;

	if (nz * nz + ny * ny + nx * nx < tolerance)
	{
		if (mode == 4)
		{
			const hkVector4& D = vertices[idxD];
			const float ddx = D.x - B.x;
			const float ddy = D.y - B.y;
			const float ddz = D.z - B.z;
			const float lenDB = ddz * ddz + ddy * ddy + ddx * ddx;
			const float invDB = hkVector4::invSqrtOrZero(lenDB);
			const float mx = cx * invCB - ddx * invDB;
			const float my = cy * invCB - ddy * invDB;
			const float mz = cz * invCB - ddz * invDB;
			if (!(mx * mx + my * my + mz * mz < tolerance))
				return hkBool(false);

			if (fVar13 < lenDB)
			{
				idxC = idxD;
				const float ex = A.x - D.x;
				const float ey = A.y - D.y;
				const float ez = A.z - D.z;
				local_54 = ey * ey + (ez * ez + ex * ex);
			}
		}

		float best = local_54;
		if (best < fVar13)
			best = fVar13;
		if (best < fVar7)
			best = fVar7;

		if (fVar7 == best)
		{
			mergedHull.initializeWithLine(idxA, idxB);
			return hkBool(true);
		}
		if (fVar13 == best)
		{
			mergedHull.initializeWithLine(idxB, idxC);
			return hkBool(true);
		}
		if (local_54 == best)
		{
			mergedHull.initializeWithLine(idxC, idxA);
			return hkBool(true);
		}
		return hkBool(true);
	}

	return hkBool(false);
}

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct hkGeomHull {
	void initializeWithLine(int&, int&); // 0x0111c740
};
}
