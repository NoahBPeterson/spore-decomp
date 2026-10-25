// Slice s01122d50 (Havok 3.1.0 collide / EPA polytope expansion).
//
//   0x01122d50  hkWingedEdge::initializePolytopeExpansion
//   0x01122f70  hkWingedEdge::Triangle::calculateTriangleData
//   0x01123070  hkWingedEdge::findTriangleNearestOrigin
//   0x011231a0  find2ClosestMultiTriangles
//   0x01123510  hkWingedEdge::addVertex
//   0x01123580  hkWingedEdge::addTetrahedron
//   0x01123680  hkWingedEdge::DoAssignValues
//   0x01123710  HkDepthHelper::computeDepth
//
// Compile flags: /vc71 /O2 /MD /Gy /TP   (Havok 3.1.0 shipped with the VC7.1 toolchain,
// cl 13.10.3077; every other /vc71 manifest in this repo uses the same set).

typedef unsigned int   uint32_t;
typedef unsigned char  uint8_t;

typedef float    hkReal;

// HK_REAL_MAX in this build is 3.40282e+38f == 0x7f7fffee (not FLT_MAX).
#define HK_REAL_MAX     3.40282e+38f
#define HK_REAL_EPSILON 1.0e-7f

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern unsigned long g_hkThreadMemoryTlsIndex;   // 0x016e4174

class hkThreadMemory
{
public:
	void deallocateChunk(void* p, int nbytes, int memClass);   // 0x0107db10
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

class hkTransform
{
public:
	hkVector4 m_col0, m_col1, m_col2;   // rotation columns (raw layout +0x00/+0x10/+0x20)
	hkVector4 m_translation;            // +0x30
};

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt)
#pragma intrinsic(fabs)

static inline hkReal hkSqrt(hkReal r) { return (hkReal)sqrt((double)r); }
static inline hkReal hkFabs(hkReal r) { return (hkReal)fabs((double)r); }

// ---- hkWingedEdge -------------------------------------------------------------------------------
class hkWingedEdge
{
public:
	class Triangle;
	struct Vertex;
	struct TriVertex;

	struct Vertex                                // 0x40 bytes
	{
		hkVector4 m_pos;                // +0x00
		hkVector4 m_a;                  // +0x10
		hkVector4 m_b;                  // +0x20
		TriVertex* m_edge;              // +0x30
		uint8_t   m_pad34[0xc];         // +0x34
	};

	struct TriVertex                             // 0x10 bytes, also used as an Edge record
	{
		Vertex*    m_vertex;            // +0x00
		TriVertex* m_next;              // +0x04
		TriVertex* m_edge;              // +0x08
		Triangle*  m_triangle;          // +0x0c
	};

	typedef TriVertex Edge;

	enum TriangleState { TRI_NONE = 1, TRI_VISIBLE = 2, TRI_OUTSIDE = 4,
	                     TRI_VISITED = TRI_NONE | TRI_VISIBLE };   // == 3, walk marker

	enum WingedEdgeStatus { WE_OK = 0, WE_VISIBLE = 1, WE_FINISHED = 2, WE_OUTSIDE = 4 };

	class Triangle                               // 0x50 bytes
	{
	public:
		hkVector4 m_normal;             // +0x00  plane normal
		hkReal    m_dist;               // +0x10  plane distance
		TriVertex m_vertices[3];        // +0x14  stride 0x10
		int       m_state;              // +0x44
		uint8_t   m_pad48[8];           // +0x48

		TriangleState calcStateAndUpdateTolerance(const hkVector4& pos, hkReal& tolLo,
		                                          hkReal& tolHi) const;   // 0x01122b70
		void calculateTriangleData();                                     // 0x01122f70
	};

	// +0x00
	hkReal m_tolLo;                  // +0x00
	hkReal m_tolHi;                  // +0x04
	int    m_numVertices;            // +0x08
	int    m_numTriangles;           // +0x0c
	int    m_numAllocatedTriangles;  // +0x10
	uint8_t m_pad14[0xc];            // +0x14

	Vertex m_vertices[55];           // +0x20
	Triangle* m_triangleList[100];   // +0xde0
	Triangle  m_triangles[60];       // +0xf70

	void resetVertexEdgesAndStates();                                        // 0x01122b20
	WingedEdgeStatus findVisibleTriangles(Triangle* tri, const hkVector4& pos,
	                                      int& count, Edge*& edge);          // 0x01122c00
	void allocateTriangles(hkArray<Triangle*>& triangles, int num);          // 0x01122cd0

	WingedEdgeStatus initializePolytopeExpansion(hkArray<Triangle*>& list, int num,
	                                             Edge* edge, Vertex*& vertex); // 0x01122d50
	void addTetrahedron();                                                   // 0x01123580
	WingedEdgeStatus addVertex(Triangle* tri, const hkVector4& pos,
	                           int& count, Edge*& edge);                     // 0x01123510
	WingedEdgeStatus DoAssignValues(int count, Edge* edge, Vertex* vertex); // 0x01123680
	Triangle* findTriangleNearestOrigin(Triangle* tri);                      // 0x01123070
};

void find2ClosestMultiTriangles(hkWingedEdge& we1, hkWingedEdge& we2, hkVector4& out,
                                hkWingedEdge::Triangle*& triA,
                                hkWingedEdge::Triangle*& triB);               // 0x011231a0

// =================================================================================================
// @ 0x01122d50 hkWingedEdge::initializePolytopeExpansion
hkWingedEdge::WingedEdgeStatus
hkWingedEdge::initializePolytopeExpansion(hkArray<Triangle*>& list, int, Edge* edge,
                                          Vertex*& vertex)
{
	Edge* startEdge = edge;

	const int n = list.m_size;
	for (int i = 0; i < n; ++i)
	{
		Edge* e = edge;
		if (e == 0)
			return WE_FINISHED;

		Triangle* tri  = list.m_data[i];
		Triangle* next = list.m_data[(i + 1 < n) ? i + 1 : 0];

		tri->m_vertices[0].m_triangle = tri;
		tri->m_vertices[1].m_triangle = tri;
		tri->m_vertices[2].m_triangle = tri;

		tri->m_vertices[1].m_next = &tri->m_vertices[2];
		tri->m_vertices[2].m_next = &tri->m_vertices[0];
		tri->m_vertices[0].m_next = &tri->m_vertices[1];

		tri->m_vertices[0].m_vertex = e->m_next->m_vertex;
		tri->m_vertices[1].m_vertex = e->m_vertex;
		tri->m_vertices[2].m_vertex = vertex;

		e->m_edge = &tri->m_vertices[0];

		tri->m_vertices[0].m_edge = e;
		next->m_vertices[1].m_edge = &tri->m_vertices[2];
		tri->m_vertices[2].m_edge = &next->m_vertices[1];

		Vertex* a = tri->m_vertices[0].m_vertex;
		Vertex* b = tri->m_vertices[1].m_vertex;
		Vertex* c = tri->m_vertices[2].m_vertex;

		hkReal ux = a->m_pos.x - b->m_pos.x;
		hkReal uy = a->m_pos.y - b->m_pos.y;
		hkReal uz = a->m_pos.z - b->m_pos.z;
		hkReal vx = b->m_pos.x - c->m_pos.x;
		hkReal vy = b->m_pos.y - c->m_pos.y;
		hkReal vz = b->m_pos.z - c->m_pos.z;

		hkReal nx = vz * uy - vy * uz;
		hkReal ny = uz * vx - vz * ux;
		hkReal nz = vy * ux - uy * vx;

		tri->m_normal.w = 0.0f;
		tri->m_normal.x = nx;
		tri->m_normal.y = ny;
		tri->m_normal.z = nz;

		hkReal len2 = nx * nx + (ny * ny + nz * nz);
		if (len2 == 0.0f)
			return WE_FINISHED;

		hkReal inv;
		if (len2 == 0.0f)
			inv = 0.0f;
		else
			inv = 1.0f / hkSqrt(len2);

		tri->m_normal.x = nx * inv;
		tri->m_normal.y = ny * inv;
		tri->m_normal.z = nz * inv;
		tri->m_normal.w = inv * 0.0f;

		tri->m_dist = tri->m_normal.x * a->m_pos.x
		            + (tri->m_normal.y * a->m_pos.y + tri->m_normal.z * a->m_pos.z);

		Vertex* farVertex = e->m_next->m_vertex;
		edge = farVertex->m_edge;
		farVertex->m_edge = 0;
	}

	for (int t = 0; t < m_numAllocatedTriangles; ++t)
		m_triangles[t].m_state = 0;

	for (int v = 0; v < m_numVertices; ++v)
		m_vertices[v].m_edge = 0;

	return (startEdge == edge) ? WE_OK : WE_FINISHED;
}

// =================================================================================================
// @ 0x01122f70 hkWingedEdge::Triangle::calculateTriangleData
void hkWingedEdge::Triangle::calculateTriangleData()
{
	Vertex* a = m_vertices[0].m_vertex;
	Vertex* b = m_vertices[1].m_vertex;
	Vertex* c = m_vertices[2].m_vertex;

	hkReal ux = a->m_pos.x - b->m_pos.x;
	hkReal uy = a->m_pos.y - b->m_pos.y;
	hkReal uz = a->m_pos.z - b->m_pos.z;

	hkVector4 v;
	v.x = b->m_pos.x - c->m_pos.x;
	v.y = b->m_pos.y - c->m_pos.y;
	v.z = b->m_pos.z - c->m_pos.z;

	hkReal nx = v.z * uy - v.y * uz;
	hkReal ny = uz * v.x - v.z * ux;
	hkReal nz = v.y * ux - v.x * uy;

	m_normal.x = nx;
	m_normal.y = ny;
	m_normal.z = nz;
	m_normal.w = 0.0f;

	hkReal len2 = nx * nx + (ny * ny + nz * nz);
	hkReal inv;
	if (len2 == 0.0f)
		inv = 0.0f;
	else
		inv = 1.0f / hkSqrt(len2);

	m_normal.x = nx * inv;
	m_normal.y = ny * inv;
	m_normal.z = nz * inv;
	m_normal.w = inv * 0.0f;
	m_dist = m_normal.x * a->m_pos.x
	       + (m_normal.y * a->m_pos.y + m_normal.z * a->m_pos.z);
}

// =================================================================================================
// @ 0x01123070 hkWingedEdge::findTriangleNearestOrigin
hkWingedEdge::Triangle* hkWingedEdge::findTriangleNearestOrigin(Triangle* startTri)
{
	resetVertexEdgesAndStates();

	Triangle* cur        = startTri;
	Edge*     skipEdge   = 0;
	bool      done       = false;

	for (;;)
	{
		if (done)
			return cur;

		cur->m_state = TRI_VISITED;

		int i = 0;
		TriVertex* tv = &cur->m_vertices[0];
		do
		{
			if (tv != skipEdge)
			{
				Vertex* v0 = tv->m_vertex;
				Vertex* v1 = tv->m_next->m_vertex;

				hkVector4 diff;
				diff.x = v1->m_pos.x - v0->m_pos.x;
				diff.y = v1->m_pos.y - v0->m_pos.y;
				diff.z = v1->m_pos.z - v0->m_pos.z;

				hkReal dx = diff.x;
				hkReal dy = diff.y;
				hkReal dz = diff.z;

				hkReal cx = dy * cur->m_normal.z - dz * cur->m_normal.y;
				hkReal cy = dz * cur->m_normal.x - dx * cur->m_normal.z;
				hkReal cz = dx * cur->m_normal.y - dy * cur->m_normal.x;

				hkReal cross = cx * v0->m_pos.x + (cz * v0->m_pos.z + cy * v0->m_pos.y);

				hkReal len2 = dy * dy + (dx * dx + dz * dz);
				if (hkFabs(cross) * cross < len2 * -9.9999994e-11f)
				{
					Triangle* other = tv->m_edge->m_triangle;
					if (startTri->m_dist <= 0.0f || startTri->m_dist * 0.9f <= other->m_dist)
					{
						skipEdge = cur->m_vertices[i].m_edge;
						done     = (other->m_state == TRI_VISITED);
						cur      = other;
						break;
					}
				}
			}
			++i;
			++tv;
		} while (i < 3);

		if (i == 3)
			return cur;
	}
}

// =================================================================================================
// @ 0x011231a0 find2ClosestMultiTriangles
void find2ClosestMultiTriangles(hkWingedEdge& we1, hkWingedEdge& we2, hkVector4& out,
                                hkWingedEdge::Triangle*& triA,
                                hkWingedEdge::Triangle*& triB)
{
	hkReal best   = HK_REAL_MAX;
	hkReal outA   = 0.0f;
	hkReal outB   = 0.0f;

	int count1 = we1.m_numAllocatedTriangles;
	if (count1 - 1 >= 0)
	{
		hkWingedEdge::Triangle* t1 = &we1.m_triangles[count1 - 1];

		do
		{
			if (t1->m_dist * t1->m_dist <= best)
			{
				int count2 = we2.m_numAllocatedTriangles - 1;
				if (count2 > 0)
				{
					hkWingedEdge::Triangle* t2 = &we2.m_triangles[count2];

					do
					{
						if (t2->m_dist * t2->m_dist <= best)
						{
							hkReal dot = t2->m_normal.x * t1->m_normal.x
							           + (t1->m_normal.y * t2->m_normal.y
							           +  t2->m_normal.z * t1->m_normal.z);

							if (-0.5f <= dot)
							{
								hkReal d1 = t1->m_dist;
								hkReal d2 = t2->m_dist;
								hkReal a  = d1 - d2 * dot;
								hkReal b  = d2 - d1 * dot;

								hkReal wa;        // weight applied to t1 normal
								hkReal wb;        // weight applied to t2 normal
								hkReal metric;    // squared distance, kept in `best`

								if (a <= 1.1920929e-07f)
								{
									if (d1 <= 1.1920929e-07f)
									{
										wa     = 0.5f;
										wb     = 0.5f;
										metric = -(dot * dot);
									}
									else
									{
										wa     = 0.0f;
										wb     = 1.0f;
										metric = d2 * d2;
									}
								}
								else if (b <= 1.1920929e-07f)
								{
									if (d2 <= 0.0f)
									{
										wa     = 0.5f;
										wb     = 0.5f;
										metric = -(dot * dot);
									}
									else
									{
										wa     = 1.0f;
										wb     = 0.0f;
										metric = d1 * d1;
									}
								}
								else if (a > b)
								{
									hkReal t  = b / a;
									hkReal s  = 1.0f / (t * dot + 1.0f);
									wb        = t * s;
									wa        = s;
									hkReal ct = s * d1;
									hkReal bt = t * ct;
									hkReal dd = ct + bt * dot;
									metric    = dd * dd + ((1.0f - dot * dot) * bt) * bt;
								}
								else
								{
									hkReal t  = a / b;
									hkReal s  = 1.0f / (t * dot + 1.0f);
									wb        = s;
									wa        = t * s;
									hkReal ct = s * d2;
									hkReal bt = t * ct;
									hkReal dd = bt + ct * dot;
									metric    = dd * dd + ((1.0f - dot * dot) * ct) * ct;
								}

								if (metric < best)
								{
									outA = wa;
									outB = wb;
									triA = t1;
									triB = t2;
									best = metric;
								}
							}
						}

						--t2;
					} while (--count2 != 0);
				}
			}

			--t1;
		} while (--count1 != 0);
	}

	out.x = outA * triA->m_normal.x;
	out.y = outA * triA->m_normal.y;
	out.z = outA * triA->m_normal.z;
	out.w = outA * triA->m_normal.w;

	out.x = out.x + outB * triB->m_normal.x;
	out.y = out.y + outB * triB->m_normal.y;
	out.z = out.z + outB * triB->m_normal.z;
	out.w = out.w + outB * triB->m_normal.w;

	hkReal len2 = out.x * out.x + (out.y * out.y + out.z * out.z);
	hkReal inv;
	if (len2 == 0.0f)
		inv = 0.0f;
	else
		inv = 1.0f / hkSqrt(len2);

	out.x = out.x * inv;
	out.y = out.y * inv;
	out.z = out.z * inv;
	out.w = out.w * inv;

	if (best >= 0.0f)
		out.w = hkSqrt(best);
	else
		out.w = 0.0f;
}

// =================================================================================================
// @ 0x01123510 hkWingedEdge::addVertex
hkWingedEdge::WingedEdgeStatus
hkWingedEdge::addVertex(Triangle* tri, const hkVector4& pos, int& count, Edge*& edge)
{
	edge  = 0;
	count = 0;

	m_tolHi = HK_REAL_MAX;
	m_tolLo = HK_REAL_EPSILON;

	TriangleState state = tri->calcStateAndUpdateTolerance(pos, m_tolLo, m_tolHi);
	tri->m_state = state;

	if (state == TRI_NONE)
		return findVisibleTriangles(tri, pos, count, edge);

	return WE_FINISHED;
}

// =================================================================================================
// @ 0x01123580 hkWingedEdge::addTetrahedron
void hkWingedEdge::addTetrahedron()
{
	// Vertex byte offset, and the two byte offsets summed into the edge slot (relative to
	// +0xf84, i.e. the first TriVertex of m_triangles[0]).  Three triples per triangle.
	static const int kTetra[36] =
	{
		0x00, 0xa0, 0x20,   0x80, 0xf0, 0x00,   0x40, 0x50, 0x00,
		0x00, 0x00, 0x20,   0x40, 0xf0, 0x20,   0xc0, 0xa0, 0x00,
		0x00, 0x50, 0x20,   0xc0, 0xf0, 0x10,   0x80, 0x00, 0x00,
		0x40, 0x00, 0x10,   0x80, 0xa0, 0x10,   0xc0, 0x50, 0x10,
	};

	m_numAllocatedTriangles = 4;

	const int* p = kTetra;
	for (int t = 0; t < 4; ++t)
	{
		Triangle* tri = &m_triangles[t];

		tri->m_vertices[0].m_next = &tri->m_vertices[1];
		tri->m_vertices[1].m_next = &tri->m_vertices[2];
		tri->m_vertices[2].m_next = &tri->m_vertices[0];
		tri->m_state = 0;

		for (int k = 0; k < 3; ++k)
		{
			tri->m_vertices[k].m_triangle = tri;
			tri->m_vertices[k].m_vertex   = &m_vertices[p[0] >> 6];

			int edgeOffset = 0x14 + p[1] + p[2];       // relative to &m_triangles[0]
			int edgeTri    = edgeOffset / 0x50;
			int edgeVert   = (edgeOffset % 0x50 - 0x14) / 0x10;
			tri->m_vertices[k].m_edge = &m_triangles[edgeTri].m_vertices[edgeVert];

			p += 3;
		}
	}

	m_triangles[3].calculateTriangleData();

	if (m_triangles[3].m_normal.x * (m_vertices[0].m_pos.x - m_vertices[1].m_pos.x)
	  + (m_triangles[3].m_normal.y * (m_vertices[0].m_pos.y - m_vertices[1].m_pos.y)
	  +  m_triangles[3].m_normal.z * (m_vertices[0].m_pos.z - m_vertices[1].m_pos.z)) > 0.0f)
	{
		m_triangles[2].m_vertices[0].m_vertex = &m_vertices[1];
		m_triangles[1].m_vertices[0].m_vertex = &m_vertices[1];
		m_triangles[0].m_vertices[0].m_vertex = &m_vertices[1];

		m_triangles[3].m_vertices[0].m_vertex = &m_vertices[0];
		m_triangles[1].m_vertices[1].m_vertex = &m_vertices[0];
		m_triangles[0].m_vertices[2].m_vertex = &m_vertices[0];
	}

	for (int i = 0; i < 4; ++i)
		m_triangles[i].calculateTriangleData();
}

// =================================================================================================
// @ 0x01123680 hkWingedEdge::DoAssignValues
hkWingedEdge::WingedEdgeStatus
hkWingedEdge::DoAssignValues(int count, Edge* edge, Vertex* vertex)
{
	Triangle* buffer[100];
	hkArray<Triangle*> list;

	list.m_data            = buffer;
	list.m_size            = 0;
	list.m_capacityAndFlags = (int)0x80000000 | 100;

	allocateTriangles(list, count);

	WingedEdgeStatus result = initializePolytopeExpansion(list, count, edge, vertex);

	list.quickFree();

	return result;
}

// =================================================================================================
// @ 0x01123710 HkDepthHelper::computeDepth
//
// The original passes `xform` in ESI and `out` in EDI (a custom internal convention used by
// _hkCvxCvxDistByHeuristicSampling).  This decompilation makes both explicit arguments; the
// calling convention therefore differs from the original, but the data flow is identical.
struct HkDepthOut
{
	hkVector4 m_point0;   // +0x00
	hkVector4 m_point1;   // +0x10
	hkVector4 m_normal;   // +0x20
	hkReal    m_depth;    // +0x2c
};

class HkDepthHelper
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void transform(const hkVector4& in, hkVector4* out);   // vtable +0x24

	void computeDepth(HkDepthHelper* obj, const hkVector4& plane,
	                  const hkTransform& xform, HkDepthOut& out);
};

void HkDepthHelper::computeDepth(HkDepthHelper* obj, const hkVector4& plane,
                                 const hkTransform& xform, HkDepthOut& out)
{
	out.m_normal = plane;

	hkVector4 neg;
	neg.x = -plane.x;
	neg.y = -plane.y;
	neg.z = -plane.z;
	neg.w = -plane.w;
	transform(neg, &out.m_point0);

	hkVector4 h;
	h.x = plane.x * xform.m_col0.x + plane.y * xform.m_col0.y + plane.z * xform.m_col0.z;
	h.y = plane.x * xform.m_col1.x + plane.y * xform.m_col1.y + plane.z * xform.m_col1.z;
	h.z = plane.x * xform.m_col2.x + plane.y * xform.m_col2.y + plane.z * xform.m_col2.z;
	h.w = 0.0f;
	obj->transform(h, &out.m_point1);

	hkVector4 t;
	t.x = out.m_point1.x * xform.m_col0.x + out.m_point1.y * xform.m_col1.x
	    + out.m_point1.z * xform.m_col2.x + xform.m_translation.x;
	t.y = out.m_point1.x * xform.m_col0.y + out.m_point1.y * xform.m_col1.y
	    + out.m_point1.z * xform.m_col2.y + xform.m_translation.y;
	t.z = out.m_point1.x * xform.m_col0.z + out.m_point1.y * xform.m_col1.z
	    + out.m_point1.z * xform.m_col2.z + xform.m_translation.z;

	out.m_depth = (out.m_point0.x - t.x) * out.m_normal.x
	            + ((out.m_point0.y - t.y) * out.m_normal.y
	            +  (out.m_point0.z - t.z) * out.m_normal.z);
}
