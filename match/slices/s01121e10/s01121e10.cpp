// Slice s01121e10 (Havok 3.1.0 collide / geometry).
//
//   0x01121e10  hkCalculatePenetrationDepth            (EPA entry point, "TtPenetration" timer)
//   0x01121f30  hkCalcMultiPenetrationDepth            (one contact per shape B)
//   0x011223b0  hkGeomConvexHullTester::findSameEdges
//   0x01122480  hkGeomConvexHullTester::checkPlaneEquations
//   0x01122580  hkGeomConvexHullTester::isValidPlanarHull        (unnamed in the DB)
//   0x01122680  hkGeomConvexHullTester::isValidNonPlanarHull
//   0x011228f0  hkGeomConvexHullTester::isValidHull
//   0x01122b20  hkWingedEdge::resetVertexEdgesAndStates          (unnamed in the DB)
//   0x01122b70  hkWingedEdge::Triangle::calcStateAndUpdateTolerance
//   0x01122c00  hkWingedEdge::findVisibleTriangles
//   0x01122cd0  hkWingedEdge::allocateTriangles
//
// Compile flags: /vc71 /O2 /MD /Gy /TP   (Havok 3.1.0 shipped with the VC7.1 toolchain,
// cl 13.10.3077; every other /vc71 manifest in this repo uses the same set).

typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;

typedef float    hkReal;
typedef uint32_t hkUint32;

// HK_REAL_MAX in this build is 3.40282e+38f == 0x7f7fffee (not FLT_MAX).
#define HK_REAL_MAX 3.40282e+38f

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long index, void* value);

// ---- Havok monitor stream timers (TLS slot 0x016e42a4 = write pointer, 0x016e42a8 = end) ---------
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char    hkMonitorEndTag[];             // 0x0149cc34 "Et"

struct hkMonitorCommand
{
	const char* m_commandAndMonitor;
	hkUint32    m_time0;
	hkUint32    m_time1;
};

#define HK_TIMER_COMMAND(name) do { \
	void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
	if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
		hkMonitorCommand* c_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
		c_->m_commandAndMonitor = name; \
		hkUint32 hkTicks_; __asm { rdtsc } __asm { mov hkTicks_, eax } \
		c_->m_time0 = hkTicks_; \
		TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); }\
	} while (0)
#define HK_TIMER_BEGIN(name) HK_TIMER_COMMAND("Tt" name)
#define HK_TIMER_END()       HK_TIMER_COMMAND(hkMonitorEndTag)

// ---- thread memory ------------------------------------------------------------------------------
extern unsigned long g_hkThreadMemoryTlsIndex;   // 0x016e4174

// hkThreadMemory: vtable slot +0x0c = allocate(int), +0x10 = releaseBlock(void*); the
// deallocateChunk below is a plain (non-virtual) member called directly at 0x0107db10.
class hkThreadMemory
{
public:
	virtual void  slot0();
	virtual void  slot1();
	virtual void  slot2();
	virtual void* allocate(int nbytes);              // vtable +0x0c
	virtual void  releaseBlock(void* p);             // vtable +0x10

	void deallocateChunk(void* p, int nbytes, int memClass);   // 0x0107db10

	int       m_i04;              // +0x04
	uint8_t   m_pad08[0x18];      // +0x08
	uint8_t*  m_current;          // +0x20 bump pointer
	int       m_i24;              // +0x24
	uint8_t*  m_preallocStart;    // +0x28
	uint8_t*  m_end;              // +0x2c
};

static inline hkThreadMemory* getThreadMemory()
{
	return (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex);
}

// ---- hkArray ------------------------------------------------------------------------------------
enum { HK_ARRAY_FLAG_MASK = 0x3fffffff, HK_ARRAY_DONT_DEALLOCATE = (int)0x80000000 };

struct hkArrayUtil { static void _reserveMore(void* arr, int elemSize); };   // 0x0107f530

template <typename T>
class hkArray
{
public:
	T*  m_data;              // +0x00
	int m_size;              // +0x04
	int m_capacityAndFlags;  // +0x08

	void pushBack(const T& t)
	{
		if (m_size == (m_capacityAndFlags & HK_ARRAY_FLAG_MASK))
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		m_data[m_size] = t;
		m_size = m_size + 1;
	}

	void quickFree()
	{
		if (m_capacityAndFlags >= 0)
			getThreadMemory()->deallocateChunk(m_data,
			                                   (m_capacityAndFlags & HK_ARRAY_FLAG_MASK) * (int)sizeof(T), 0x14);
	}
};

// ---- vectors / transforms -----------------------------------------------------------------------
class __declspec(align(16)) hkVector4
{
public:
	hkReal x, y, z, w;
};

typedef hkVector4 hkCdVertex;

class hkConvexShape;

class hkTransform
{
public:
	hkVector4 m_col0, m_col1, m_col2;   // rotation columns
	hkVector4 m_translation;
};

__forceinline hkReal dot3(const hkVector4& a, const hkVector4& b)
{
	return a.x * b.x + (a.y * b.y + a.z * b.z);
}

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
static __forceinline hkReal hkFabs(hkReal r) { return (hkReal)fabs((double)r); }

// hkBool is returned through a hidden pointer (its ctor makes it non-POD), which is what the
// original callers rely on (`mov [esp+4]` return buffer + `mov [eax],dl` in the callee).
class hkBool
{
public:
	hkBool() {}
	hkBool(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
	char m_bool;
};

// ---- gsk status / out ---------------------------------------------------------------------------
enum hkGskStatus
{
	HK_GSK_OK                = 0,
	HK_GSK_VALID             = 1,
	HK_GSK_FAILED            = 2,
	HK_GSK_PENETRATION_DEPTH = 3
};

struct hkGskOut
{
	hkVector4 m_normal;   // +0x00
	hkVector4 m_point;    // +0x10
	hkReal    m_dist;     // +0x20
	hkReal    m_half;     // +0x24
};

enum hkResult { HK_RESULT_OK = 0, HK_RESULT_FAIL = 1 };

class hkContactPoint
{
public:
	hkVector4 m_position;   // +0x00
	hkVector4 m_normal;     // +0x10
	hkReal    m_distance;   // +0x20
};

// ---- hkConvexPenetrationUtil (0x70 bytes, 16-aligned: it holds hkVector4 members) ---------------
class __declspec(align(16)) hkConvexPenetrationUtil
{
public:
	void init(const hkConvexShape* shapeA, const hkConvexShape* shapeB, const hkTransform& aTb,
	          hkReal tolerance, hkCdVertex* simplexA, hkCdVertex* simplexB, hkVector4* diffs,
	          int* dim);                                        // 0x01120f40
	hkGskStatus calculatePenetrationDepth(hkGskOut& out);        // 0x01121c60

private:
	uint8_t m_pad00[0x40];
	hkReal  m_bestDist;      // +0x40
	uint8_t m_pad44[0x2c];   // ... size 0x70
};

void _hkCvxCvxDistByHeuristicSampling(const hkConvexShape* shapeA, const hkConvexShape* shapeB,
                                      const hkTransform& aTb, hkCdVertex* simplexA,
                                      hkCdVertex* simplexB, hkGskOut* out);           // 0x01123850

// ---- hkWingedEdge -------------------------------------------------------------------------------
class hkWingedEdge
{
public:
	class Triangle;
	struct Vertex;
	struct Edge;

	struct Vertex                                // 0x40 bytes
	{
		hkReal    m_x, m_y, m_z, m_w;   // +0x00  position (also read as a float* by Triangle)
		hkVector4 m_a;                  // +0x10
		hkVector4 m_b;                  // +0x20
		Edge*     m_edge;               // +0x30
		uint8_t   m_pad34[0xc];         // +0x34
	};

	struct Edge                                  // 0x10 bytes
	{
		Vertex*   m_vertex;             // +0x00
		uint8_t   m_pad04[8];           // +0x04
		Triangle* m_triangle;           // +0x0c
	};

	struct TriVertex                             // 0x10 bytes
	{
		Vertex* m_vertex;               // +0x00
		uint8_t m_pad04[4];             // +0x04
		Edge*   m_edge;                 // +0x08
		uint8_t m_pad0c[4];             // +0x0c
	};

	enum TriangleState { TRI_NONE = 1, TRI_VISIBLE = 2, TRI_OUTSIDE = 4 };

	enum WingedEdgeStatus { WE_OK = 0, WE_VISIBLE = 1, WE_FINISHED = 2, WE_OUTSIDE = 4 };

	class Triangle                               // 0x50 bytes
	{
	public:
		hkVector4 m_normal;             // +0x00  plane normal
		hkReal    m_dist;               // +0x10  plane distance (also the "nearest" marker)
		TriVertex m_vertices[3];        // +0x14  stride 0x10
		int       m_state;              // +0x44
		uint8_t   m_pad48[8];           // +0x48

		TriangleState calcStateAndUpdateTolerance(const hkVector4& pos, hkReal& tolLo,
		                                          hkReal& tolHi) const;   // 0x01122b70
	};

	// +0x00
	hkReal m_tolLo;                  // +0x00
	hkReal m_tolHi;                  // +0x04
	int    m_numVertices;            // +0x08
	int    m_numTriangles;           // +0x0c  number of visible triangles in m_triangleList
	int    m_numAllocatedTriangles;  // +0x10
	uint8_t m_pad14[0xc];            // +0x14

	Vertex m_vertices[55];           // +0x20  (55 * 0x40 == 0xdc0 -> ends at 0xde0)
	Triangle* m_triangleList[100];   // +0xde0 (100 * 4 == 0x190 -> ends at 0xf70)
	Triangle  m_triangles[60];       // +0xf70 (60 * 0x50 == 0x12c0 -> ends at 0x2230)

	uint8_t m_pad2230[0x2eb0 - 0x2230];

	// +0x2eb0: scratch pointer.  hkCalcMultiPenetrationDepth reads it as a `const hkVector4&`
	// support point and also hands its address to find2ClosestMultiTriangles(..., Triangle*&).
	union Scratch { hkVector4* m_points; Triangle* m_triangle; };
	Scratch m_scratch;

	void initializeWithTetrahedron(hkVector4* a, hkVector4* b, hkVector4* w);   // 0x01120850
	void resetVertexEdgesAndStates();                                        // 0x01122b20
	WingedEdgeStatus findVisibleTriangles(Triangle* tri, const hkVector4& pos,
	                                      int& count, Edge*& edge);          // 0x01122c00
	void allocateTriangles(hkArray<Triangle*>& triangles, int num);          // 0x01122cd0
};

void find2ClosestMultiTriangles(hkWingedEdge& we1, hkWingedEdge& we2, hkVector4& out,
                                       hkWingedEdge::Triangle*& triA,
                                       hkWingedEdge::Triangle*& triB);       // 0x011231a0

// =================================================================================================
// @ 0x01121e10 hkCalculatePenetrationDepth
hkGskStatus hkCalculatePenetrationDepth(const hkConvexShape* shapeA, const hkConvexShape* shapeB,
                                        const hkTransform& aTb, hkReal tolerance,
                                        hkCdVertex* simplexA, hkCdVertex* simplexB,
                                        hkVector4* diffs, int* dim, hkGskOut& out)
{
	HK_TIMER_BEGIN("Penetration");

	hkConvexPenetrationUtil util;
	util.init(shapeA, shapeB, aTb, tolerance, simplexA, simplexB, diffs, dim);

	hkGskStatus status = util.calculatePenetrationDepth(out);
	if (status == HK_GSK_PENETRATION_DEPTH)
	{
		_hkCvxCvxDistByHeuristicSampling(shapeA, shapeB, aTb, simplexA, simplexB, &out);
		*dim = 1;
		status = HK_GSK_VALID;
	}

	HK_TIMER_END();
	return status;
}

// =================================================================================================
// 0x01121f30 works on a per-shape scratch block: a penetration-utility header (0x140 bytes,
// holding a copy of the second transform, the tolerance scratch buffer and the three
// hkVector4[4] support arrays that hkWingedEdge points at) immediately followed by a 0x2ec0-byte
// hkWingedEdge polytope.  One block per shape B; the stride is 0x3000.
struct hkPenetrationUtilHeader
{
	hkTransform m_simplex;          // +0x000  64-byte block copied from the 5th argument
	hkReal      m_tol[4];           // +0x040  four 1e-4 tolerances
	hkReal      m_epsilon;          // +0x050  1e-8
	const void* m_shapeA;           // +0x054
	const void* m_shapeB;           // +0x058
	int         m_i5c;              // +0x05c
	hkVector4*  m_a;                // +0x060
	hkVector4*  m_b;                // +0x064
	hkVector4*  m_w;                // +0x068
	int*        m_num;              // +0x06c
	hkVector4   m_aBuf[4];          // +0x070
	hkVector4   m_bBuf[4];          // +0x0b0
	hkVector4   m_wBuf[4];          // +0x0f0
	int         m_numBuf;           // +0x130
	const void* m_shapeB2;          // +0x134
	hkContactPoint* m_contactOut;   // +0x138
	int         m_pad13c;           // +0x13c
};                                    // size 0x140

struct hkPenetrationSlot
{
	hkPenetrationUtilHeader m_util;   // +0x000
	hkWingedEdge            m_we;     // +0x140  (0x2ec0 bytes)
};                                    // size 0x3000

// Utility helpers used by hkCalcMultiPenetrationDepth (declared with the argument counts and
// calling conventions the original call sites push).
extern "C" int hkConvexPenetrationUtil_evolve(hkPenetrationUtilHeader& util, const hkVector4& d,
                                              hkVector4& out);                           // 0x01121610
namespace hkInternal
{
	void getPointForSimplex(hkPenetrationUtilHeader& util, const hkVector4& v,
	                        hkWingedEdge::Vertex& out);                                  // 0x01120fb0
	int  tryToExpandPolytope(hkPenetrationUtilHeader& util, hkWingedEdge& we,
	                         hkWingedEdge::Triangle* tri, hkWingedEdge::Vertex* v,
	                         int& status);                                               // 0x01120a80
	void convertResultToFeature(hkPenetrationUtilHeader& util, hkWingedEdge& we,
	                            hkWingedEdge::Triangle* tri, hkGskOut& out);             // 0x01120c40
}

// @ 0x01121f30 hkCalcMultiPenetrationDepth
hkResult hkCalcMultiPenetrationDepth(const hkTransform& aTb, const hkConvexShape* shapeA,
                                     const hkConvexShape** shapesB, int numShapesB,
                                     const hkTransform& simplex, hkContactPoint** out)
{
	hkThreadMemory* tm = getThreadMemory();
	const int bytes = (numShapesB * 0x3000 + 0x10) & ~0xf;

	hkPenetrationSlot* slots;
	{
		uint8_t* cur = tm->m_current;
		if ((uint32_t)(cur + bytes) > (uint32_t)tm->m_end)
			slots = (hkPenetrationSlot*)tm->allocate(bytes);
		else
		{
			tm->m_current = cur + bytes;
			slots = (hkPenetrationSlot*)cur;
		}
	}

	// ---- phase 1: fill one slot per shape ---------------------------------------------------
	if (numShapesB > 0)
	{
		const hkConvexShape** pShape = shapesB;
		hkContactPoint**      pOut   = out;
		int                   i      = 0;
		do
		{
			hkPenetrationSlot& slot = slots[i];

			slot.m_util.m_simplex   = simplex;
			slot.m_util.m_tol[0]    = 1e-4f;
			slot.m_util.m_tol[1]    = 1e-4f;
			slot.m_util.m_tol[2]    = 1e-4f;
			slot.m_util.m_tol[3]    = 1e-4f;
			slot.m_util.m_epsilon   = 1e-8f;
			slot.m_util.m_shapeA    = shapeA;
			slot.m_util.m_shapeB    = *pShape;
			slot.m_util.m_i5c       = 0;
			slot.m_util.m_numBuf    = 0;
			slot.m_util.m_shapeB2   = *pShape;
			slot.m_util.m_contactOut = *pOut;
			slot.m_util.m_a = slot.m_util.m_aBuf;
			slot.m_util.m_b = slot.m_util.m_bBuf;
			slot.m_util.m_w = slot.m_util.m_wBuf;
			slot.m_util.m_num = &slot.m_util.m_numBuf;

			hkVector4 tmp;
			if (hkConvexPenetrationUtil_evolve(slot.m_util, tmp, tmp) == 1)
			{
				--numShapesB;
			}
			else
			{
				slot.m_we.initializeWithTetrahedron(slot.m_util.m_aBuf, slot.m_util.m_bBuf,
				                                    slot.m_util.m_wBuf);
			}

			++i;
			++pShape;
			++pOut;
		} while (i < numShapesB);
	}

	// ---- phase 2: expand at most two polytopes ----------------------------------------------
	int count = numShapesB;
	if (count >= 3)
	{
		numShapesB = 2;
		count = numShapesB;
	}

	hkVector4 closest;
	bool expanded;
	do
	{
		find2ClosestMultiTriangles(slots[0].m_we, slots[1].m_we, closest,
		                           slots[0].m_we.m_scratch.m_triangle,
		                           slots[1].m_we.m_scratch.m_triangle);
		expanded = false;
		{
			int i = 0;
			if (count > 0)
			{
				do
				{
					hkWingedEdge& we = slots[i].m_we;
					if (we.m_numVertices < 0x37)
					{
						hkWingedEdge::Vertex* v = &we.m_vertices[we.m_numVertices++];
						int st = 0;
						v->m_edge = 0;
						hkInternal::getPointForSimplex(slots[i].m_util, *we.m_scratch.m_points, *v);
						if (hkInternal::tryToExpandPolytope(slots[i].m_util, we, 0, v, st) == 1)
						{
							if (st == 3)
							{
								tm = getThreadMemory();
								tm->m_current = (uint8_t*)slots;
								if (slots == (hkPenetrationSlot*)tm->m_preallocStart)
									tm->releaseBlock(slots);
								return HK_RESULT_FAIL;
							}
						}
						else
						{
							expanded = true;
						}
					}
					++i;
				} while (i < count);
			}
		}
	} while (expanded);

	if (count < 2)
	{
		tm = getThreadMemory();
		tm->m_current = (uint8_t*)slots;
		if (slots == (hkPenetrationSlot*)tm->m_preallocStart)
			tm->releaseBlock(slots);
		return HK_RESULT_FAIL;
	}

	// ---- phase 3: convert the two closest features into contact points ----------------------
	{
		hkVector4 normal;
		normal.x = -closest.x;
		normal.y = -closest.y;
		normal.z = -closest.z;
		normal.w = -closest.w;
		hkReal dist = -closest.w - ((const hkReal*)&aTb)[3];

		hkGskOut gskOut;
		for (int i = 0; i < count; ++i)
		{
			hkPenetrationSlot& slot = slots[i];
			hkInternal::convertResultToFeature(slot.m_util, slot.m_we,
			                                   slot.m_we.m_scratch.m_triangle, gskOut);
			hkContactPoint* cp = slot.m_util.m_contactOut;

			cp->m_normal.x = normal.z * aTb.m_col0.x + (normal.y * aTb.m_col1.x + normal.x * aTb.m_col2.x);
			cp->m_normal.y = normal.z * aTb.m_col0.y + (normal.y * aTb.m_col1.y + normal.x * aTb.m_col2.y);
			cp->m_normal.z = normal.z * aTb.m_col0.z + (normal.y * aTb.m_col1.z + normal.x * aTb.m_col2.z);
			cp->m_normal.w = 0.0f;

			cp->m_position.x = gskOut.m_normal.z * aTb.m_col0.x +
			                   (gskOut.m_normal.y * aTb.m_col1.x + gskOut.m_normal.x * aTb.m_col2.x) +
			                   aTb.m_translation.x;
			cp->m_position.y = gskOut.m_normal.z * aTb.m_col0.y +
			                   (gskOut.m_normal.y * aTb.m_col1.y + gskOut.m_normal.x * aTb.m_col2.y) +
			                   aTb.m_translation.y;
			cp->m_position.z = gskOut.m_normal.z * aTb.m_col0.z +
			                   (gskOut.m_normal.y * aTb.m_col1.z + gskOut.m_normal.x * aTb.m_col2.z) +
			                   aTb.m_translation.z;
			cp->m_position.w = 0.0f;

			cp->m_distance = dist - *(const hkReal*)&slot.m_util.m_shapeB;
		}
	}

	tm = getThreadMemory();
	tm->m_current = (uint8_t*)slots;
	if (slots == (hkPenetrationSlot*)tm->m_preallocStart)
		tm->releaseBlock(slots);
	return HK_RESULT_OK;
}

// =================================================================================================
// ---- convex hull tester -------------------------------------------------------------------------
struct hkGeomConvexHullTolerances
{
	float  m_values[4];        // +0x00
	bool   m_useUnitCube;      // +0x01 ... tested directly by isValidHull
};

// A convex hull is an hkArray<hkVector4> of vertices; the tester passes it straight to
// checkPlaneEquations, whose parameters are hkArray<hkVector4>&.
struct hkGeomHull : public hkArray<hkVector4> {};

// PlaneAndPoints: the plane plus pointers to the three vertex indices it was built from.
struct PlaneAndPoints
{
	hkVector4       m_plane;   // +0x00
	unsigned short* m_v0;      // +0x10
	unsigned short* m_v1;      // +0x14
	unsigned short* m_v2;      // +0x18
	uint32_t        m_pad1c;   // +0x1c
};

struct hkGeomConvexHullBuilder
{
	// 0x01118f50
	static void buildPlaneEquations(hkBool& ok, const hkGeomConvexHullTolerances& tolerances,
	                                hkGeomHull& hull, hkArray<hkVector4>& vertices,
	                                hkVector4& a, hkVector4& b, hkVector4& c, hkVector4& d);
	// 0x01116050
	static void convertFromUnitCube(hkArray<hkVector4>& vertices, hkVector4& scale,
	                                hkVector4& offset);
};

// 0x01115e20: the inverse of convertFromUnitCube (computes the unit-cube -> hull bounds).
void FUN_01115e20(hkArray<hkVector4>& vertices, hkVector4& offset, hkVector4& scale);

struct hkGeomConvexHullTester
{
	static hkBool findSameEdges(const PlaneAndPoints& a, const PlaneAndPoints& b,
	                            hkBool& e0, hkBool& e1, hkBool& e2);                    // 0x011223b0
	static hkBool checkPlaneEquations(hkArray<hkVector4>& a, hkArray<hkVector4>& b,
	                                  hkArray<hkVector4>& planes, hkReal tolerance);    // 0x01122480
	static hkBool FUN_01122580(hkArray<hkVector4>& verts, hkGeomHull& hullA, hkGeomHull& hullB,
	                           hkGeomHull& hullC, hkArray<PlaneAndPoints>& planes,
	                           hkReal tolerance);                                        // 0x01122580
	static hkBool isValidNonPlanarHull(hkArray<hkVector4>& verts, hkGeomHull& hullA,
	                                   hkGeomHull& hullB, hkGeomHull& hullC,
	                                   hkArray<PlaneAndPoints>& planes, hkReal tolerance); // 0x01122680
	static hkBool isValidHull(const hkGeomConvexHullTolerances& tolerances,
	                          const hkVector4* points, int numPoints, hkGeomHull& hull,
	                          hkArray<hkVector4>& vertices);                            // 0x011228f0
};

// @ 0x011223b0 hkGeomConvexHullTester::findSameEdges
hkBool hkGeomConvexHullTester::findSameEdges(const PlaneAndPoints& pa, const PlaneAndPoints& pb,
                                             hkBool& e0, hkBool& e1, hkBool& e2)
{
	unsigned short a0 = *pa.m_v0;
	unsigned short a1 = *pa.m_v1;
	unsigned short a2 = *pa.m_v2;
	unsigned short b0 = *pb.m_v0;
	unsigned short b1 = *pb.m_v1;
	unsigned short b2 = *pb.m_v2;

	bool result = true;

	if (a0 == b0)
	{
		if (a1 == b1 || a1 == b2)
		{
			if (e0.m_bool) result = false;
			e0.m_bool = 1;
		}
		if (a2 == b1 || a2 == b2)
		{
			if (e1.m_bool) result = false;
			e1.m_bool = 1;
		}
	}
	if (a0 == b1)
	{
		if (a1 == b2)
		{
			if (e0.m_bool) result = false;
			e0.m_bool = 1;
		}
		if (a2 == b2)
		{
			if (e1.m_bool) result = false;
			e1.m_bool = 1;
		}
	}
	if ((a1 == b0 && (a2 == b1 || a2 == b2)) || (a1 == b1 && a2 == b2))
	{
		if (e2.m_bool) result = false;
		e2.m_bool = 1;
	}
	return result;
}

// @ 0x01122480 hkGeomConvexHullTester::checkPlaneEquations
hkBool hkGeomConvexHullTester::checkPlaneEquations(hkArray<hkVector4>& a, hkArray<hkVector4>& b,
                                                   hkArray<hkVector4>& planes, hkReal tolerance)
{
	bool result = true;
	int  i = 0;
	do
	{
		if (planes.m_size <= i)
			break;

		int j = 0;
		if (result)
		{
			int n = a.m_size;
			int k = 0;
			while (j < n)
			{
				result = result && (dot3(a.m_data[k], planes.m_data[i]) + planes.m_data[i].w < tolerance);
				++j;
				++k;
				if (!result)
					break;
			}
		}

		j = 0;
		if (result)
		{
			int n = b.m_size;
			int k = 0;
			while (j < n)
			{
				result = result && (dot3(b.m_data[k], planes.m_data[i]) + planes.m_data[i].w < tolerance);
				++j;
				++k;
				if (!result)
					break;
			}
		}

		++i;
	} while (result);

	return result;
}

// @ 0x01122580 hkGeomConvexHullTester::FUN_01122580
hkBool hkGeomConvexHullTester::FUN_01122580(hkArray<hkVector4>& verts, hkGeomHull& hullA,
                                            hkGeomHull& hullB, hkGeomHull& hullC,
                                            hkArray<PlaneAndPoints>& planes, hkReal tolerance)
{
	bool result = checkPlaneEquations(verts, hullB, hullC, tolerance);

	int i = 0;
	if (planes.m_size > 0)
	{
		do
		{
			hkBool e0(false), e1(false), e2(false);

			for (int j = 0; j < planes.m_size; ++j)
			{
				if (j != i)
					findSameEdges(planes.m_data[i], planes.m_data[j], e0, e1, e2);
			}

			result = result && e0.m_bool && e1.m_bool && e2.m_bool;
			++i;
		} while (i < planes.m_size);
	}

	return result;
}

// @ 0x01122680 hkGeomConvexHullTester::isValidNonPlanarHull
hkBool hkGeomConvexHullTester::isValidNonPlanarHull(hkArray<hkVector4>& verts, hkGeomHull& hullA,
                                                    hkGeomHull& hullB, hkGeomHull& hullC,
                                                    hkArray<PlaneAndPoints>& planes,
                                                    hkReal tolerance)
{
	bool result = checkPlaneEquations(verts, hullB, hullC, tolerance);

	int planeCount = planes.m_size;
	int i = 0;
	if (planeCount > 0)
	{
		do
		{
			bool distinct = false;
			if (result)
			{
				PlaneAndPoints& pi = planes.m_data[i];
				unsigned short v = *pi.m_v1;
				if (*pi.m_v0 == v || v == *pi.m_v2)
					distinct = false;
				else
					distinct = true;
			}

			hkBool e0(false), e1(false), e2(false);

			for (int j = 0; j < planeCount; ++j)
			{
				if (j == i)
					continue;

				PlaneAndPoints& pj = planes.m_data[j];

				if (distinct &&
				    *planes.m_data[i].m_v0 == *pj.m_v0 &&
				    *planes.m_data[i].m_v1 == *pj.m_v1 &&
				    *planes.m_data[i].m_v2 == *pj.m_v2)
				{
					hkReal dx = planes.m_data[i].m_plane.x - pj.m_plane.x;
					hkReal dy = planes.m_data[i].m_plane.y - pj.m_plane.y;
					hkReal dz = planes.m_data[i].m_plane.z - pj.m_plane.z;
					hkReal dw = planes.m_data[i].m_plane.w - pj.m_plane.w;
					if (hkFabs(dy) <= 1e-3f && hkFabs(dx) <= 1e-3f &&
					    hkFabs(dz) <= 1e-3f && hkFabs(dw) <= 1e-3f)
					{
						distinct = false;
						continue;
					}
				}

				if (distinct)
				{
					if (!findSameEdges(planes.m_data[i], pj, e0, e1, e2))
						distinct = false;
				}
			}

			result = distinct && e0.m_bool && e1.m_bool && e2.m_bool;
			++i;
		} while (i < planeCount);
	}

	if (hullB.m_size > 2)
	{
		if (result && (planeCount - hullA.m_capacityAndFlags / 2) + (hullB.m_size - 2) == 0)
			return hkBool(true);
		result = false;
	}

	return result;
}

// @ 0x011228f0 hkGeomConvexHullTester::isValidHull
hkBool hkGeomConvexHullTester::isValidHull(const hkGeomConvexHullTolerances& tolerances,
                                           const hkVector4* points, int numPoints,
                                           hkGeomHull& hull, hkArray<hkVector4>& vertices)
{
	hkArray<hkVector4> a;        // 0x80000000 = empty, allocation not owned
	hkArray<hkVector4> b;
	hkArray<PlaneAndPoints> planes;
	a.m_data = 0; a.m_size = 0; a.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
	b.m_data = 0; b.m_size = 0; b.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
	planes.m_data = 0; planes.m_size = 0; planes.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;

	for (int i = 0; i < numPoints; ++i)
		a.pushBack(points[i]);

	hkVector4 unitCubeA, unitCubeB;
	if (tolerances.m_useUnitCube)
	{
		FUN_01115e20(vertices, unitCubeA, unitCubeB);
		FUN_01115e20(a, unitCubeA, unitCubeB);
	}

	hkVector4 cubeMin, cubeMax, cubeMin2, cubeMax2;
	hkBool ok(false);

	hkGeomConvexHullBuilder::buildPlaneEquations(ok, tolerances, hull, vertices,
	                                             cubeMin, cubeMax, cubeMin2, cubeMax2);

	hkBool hullValid =
	    ok.m_bool ? FUN_01122580(vertices, hull, hull, hull, planes, (hkReal)tolerances.m_values[2])
	              : isValidNonPlanarHull(vertices, hull, hull, hull, planes,
	                                     (hkReal)tolerances.m_values[2]);

	bool valid = hullValid.m_bool;

	if (tolerances.m_useUnitCube)
	{
		hkGeomConvexHullBuilder::convertFromUnitCube(vertices, unitCubeA, unitCubeB);
		hkGeomConvexHullBuilder::convertFromUnitCube(a, unitCubeA, unitCubeB);
	}

	a.quickFree();
	b.quickFree();
	planes.quickFree();

	return valid;
}

// =================================================================================================
// @ 0x01122b20 hkWingedEdge::resetVertexEdgesAndStates
void hkWingedEdge::resetVertexEdgesAndStates()
{
	for (int i = 0; i < m_numAllocatedTriangles; ++i)
		m_triangles[i].m_state = 0;

	for (int j = 0; j < m_numVertices; ++j)
		m_vertices[j].m_edge = 0;
}

// @ 0x01122b70 hkWingedEdge::Triangle::calcStateAndUpdateTolerance
hkWingedEdge::TriangleState
hkWingedEdge::Triangle::calcStateAndUpdateTolerance(const hkVector4& pos, hkReal& tolLo,
                                                    hkReal& tolHi) const
{
	const float* vp = (const float*)m_vertices[0].m_vertex;
	hkVector4 d;
	d.x = pos.x - vp[0];
	d.y = pos.y - vp[1];
	d.z = pos.z - vp[2];

	hkReal dist = dot3(d, m_normal);

	TriangleState state = TRI_NONE;
	if (dist > tolLo)
	{
		if (dist < tolHi)
			tolHi = dist;
	}
	else
	{
		hkReal t = dist + 1e-07f;
		if (t > tolLo)
			tolLo = t;
		state = TRI_VISIBLE;
	}

	if (tolLo >= tolHi)
		return TRI_OUTSIDE;
	return state;
}

// @ 0x01122c00 hkWingedEdge::findVisibleTriangles
hkWingedEdge::WingedEdgeStatus
hkWingedEdge::findVisibleTriangles(Triangle* tri, const hkVector4& pos, int& count, Edge*& edge)
{
	WingedEdgeStatus result = WE_OK;
	TriVertex* tv = &tri->m_vertices[0];

	for (int i = 0; i < 3; ++i, ++tv)
	{
		Edge*     e     = (Edge*)tv->m_edge;
		Triangle* other = (Triangle*)e->m_triangle;

		int state = other->m_state;
		if (state == 0)
		{
			state = other->calcStateAndUpdateTolerance(pos, m_tolLo, m_tolHi);
			other->m_state = state;

			if (state == TRI_NONE)
			{
				result = findVisibleTriangles(other, pos, count, edge);
				if (result == WE_FINISHED)
					break;
			}
			else if (state == TRI_OUTSIDE)
			{
				result = WE_FINISHED;
				break;
			}
		}

		if (other->m_state == TRI_VISIBLE)
		{
			e->m_vertex->m_edge = e;
			++count;
			edge = e;
		}
	}

	*(int*)&tri->m_dist = 0x7f7fffee;
	m_triangleList[m_numTriangles] = tri;
	++m_numTriangles;

	return result;
}

// @ 0x01122cd0 hkWingedEdge::allocateTriangles
void hkWingedEdge::allocateTriangles(hkArray<Triangle*>& list, int num)
{
	// The original materialises the array pointer in eax before testing num (and leaves it
	// there across the early-out, which callers of this void function can observe).
	hkArray<Triangle*>* pl = &list;
	if (pl != 0 && num != 0)
	{
		int i = m_numTriangles - 1;

		do
		{
			if (i < 0)
				break;
			pl->m_data[pl->m_size] = m_triangleList[i];
			++pl->m_size;
			--m_numTriangles;
			--num;
			--i;
		} while (num != 0);

		while (num > 0)
		{
			Triangle* t = &m_triangles[m_numAllocatedTriangles];
			++m_numAllocatedTriangles;
			pl->m_data[pl->m_size] = t;
			++pl->m_size;
			--num;
		}
	}
}
