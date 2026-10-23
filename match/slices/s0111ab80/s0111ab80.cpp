// Havok 3.1.0 hkGeomConvexHullBuilder: the wrapping-band routines.
//   0x0111AEF0  findWeightedNeighbours -- walks the edge ring of one hull from a given edge,
//               weighting every visited edge by the angle between its vertex and a plane.
//   0x0111B010  findWrapping -- grows a wrapping band from a list of weighted lines and tests
//               each candidate band with FUN_0111AB80.
//   0x0111AB80  the band validity check (flood-mark edges of both hulls along the band).
// Built /vc71 /O2 /MD /Gy /TP (Havok module: VC .NET 2003, x87, no /arch:SSE, no /EHsc).
// Self-contained; same conventions as match/slices/s0111b170 (the sibling mergeHulls).
#include "types.h"

// ---- hkArrayUtil ------------------------------------------------------------
struct hkArrayUtil
{
	static void _reserveExactly(void* array, int newCapacity, int elemSize);   // 0x0107F4A0
};

// ---- hkArray ----------------------------------------------------------------
template <class T>
class hkArray
{
public:
	enum { CAPACITY_MASK = 0x3FFFFFFF, DONT_DEALLOCATE_FLAG = (int)0x80000000 };
	T*  m_data;              // +0
	int m_size;              // +4
	int m_capacityAndFlags;  // +8

	int getSize() const { return m_size; }
	int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
	T*  begin() { return m_data; }
	T&  operator[](int i) { return m_data[i]; }

	// The original inlines this growth (capacity doubles, clamped up to size+1) and
	// returns a reference to the new element.
	T& pushBack()
	{
		const int oldSize = m_size;
		const int newSize = oldSize + 1;
		if (getCapacity() < newSize)
		{
			int newCapacity = getCapacity() * 2;
			if (newCapacity <= newSize)
				newCapacity = newSize;
			hkArrayUtil::_reserveExactly(this, newCapacity, (int)sizeof(T));
		}
		m_size = newSize;
		return m_data[oldSize];
	}
};

// ---- hkVector4 / hkGeomEdge / hkGeomHull ------------------------------------
struct __declspec(align(16)) hkVector4 { float x, y, z, w; };

struct hkGeomEdge
{
	uint16_t m_vertex;   // +0
	uint16_t m_twin;     // +2
	uint16_t m_next;     // +4
	uint16_t m_marked;   // +6 (walk state; 0/1/2/3)
};

class hkGeomHull
{
public:
	const hkVector4* m_vertices;      // +0
	hkArray<hkGeomEdge> m_edges;      // +4
};

struct hkGeomConvexHullTolerances
{
	uint32_t m_pad0[2];
	float m_singleLineTolerance;   // +8
	uint32_t m_padC[5];
	float m_wrappingTolerance;     // +0x20
};

// 0x0111A9E0: writes its result through the out pointer and returns it.
char* FUN_0111a9e0(char* out, void* hull, int edge, int flag);

class hkGeomConvexHullBuilder
{
public:
	struct WeightedLine                       // 0x14
	{
		hkGeomEdge*       m_edgeA;            // +0
		hkGeomEdge*       m_edgeB;            // +4
		WeightedLine*     m_lastLine;         // +8 (linked list back to the tangent)
		uint32_t          m_lastVertex;       // +0xc (low 16 bits used)
		float             m_weight;           // +0x10
	};
	struct WeightedNeighbour                  // 0x8
	{
		const hkGeomEdge* m_edge;             // +0
		float             m_weight;           // +4
	};
	struct WrappingLine                       // 0x10
	{
		hkGeomEdge*       m_edgeA;            // +0
		hkGeomEdge*       m_edgeB;            // +4
		uint32_t          m_pad8[2];          // +8
	};

	static float getAngleBetweenVertexAndPlane(const hkGeomConvexHullTolerances& tolerances,
		const hkVector4& vertex, const hkVector4& normal, const hkVector4& a, const hkVector4& b);   // 0x01116A20
	static void removeCoPlanarNeighbours(const hkGeomConvexHullTolerances& tolerances, hkGeomHull& hull,
		const hkVector4& normal, const hkGeomEdge* edge, const hkVector4* a, const hkVector4* b,
		hkArray<WeightedNeighbour>& neighbours);   // 0x0111A700
	static void findWeightedNeighbours(const hkGeomConvexHullTolerances& tolerances, hkGeomHull& hull,
		const hkVector4& normal, unsigned short lastVertex, const hkGeomEdge* edge, const hkVector4* a,
		const hkVector4* b, hkArray<WeightedNeighbour>& neighbours);   // 0x0111AEF0
	static void findWrapping(hkGeomHull& hullA, hkGeomHull& hullB, const hkArray<WeightedLine>& lines,
		hkArray<WrappingLine>& wrapping);   // 0x0111B010
};

typedef hkGeomConvexHullBuilder::WeightedNeighbour WeightedNeighbour;
typedef hkGeomConvexHullBuilder::WeightedLine WeightedLine;
typedef hkGeomConvexHullBuilder::WrappingLine WrappingLine;

// 0x011159F0 (the WeightedNeighbour comparator) and 0x01115BF0 (the instantiation of
// hkAlgorithm::quickSortRecursive<WeightedNeighbour>).
typedef char (*NeighbourLess)(const WeightedNeighbour&, const WeightedNeighbour&);
char sortByY(const WeightedNeighbour& a, const WeightedNeighbour& b);
void quickSortRecursive_WeightedNeighbour(WeightedNeighbour* data, int lo, int hi, NeighbourLess less);

// 0x0111AB80: the wrapping-band validity check.
void FUN_0111ab80(char* pOut, hkGeomHull* hull, const void* unused, char flag,
	hkArray<WrappingLine>* wrapping);

// @ 0x0111aef0
void hkGeomConvexHullBuilder::findWeightedNeighbours(const hkGeomConvexHullTolerances& tolerances,
	hkGeomHull& hull, const hkVector4& normal, unsigned short lastVertex, const hkGeomEdge* edge,
	const hkVector4* a, const hkVector4* b, hkArray<WeightedNeighbour>& neighbours)
{
	if (hull.m_edges.m_size == 1)
		return;

	hkGeomEdge* edges = hull.m_edges.m_data;
	const hkVector4* vertices = hull.m_vertices;
	const hkGeomEdge* e = &edges[edge->m_twin];
	const hkGeomEdge* start = e;
	do
	{
		float w;
		if (e->m_vertex == lastVertex)
		{
			w = 4.0f;
		}
		else
		{
			w = getAngleBetweenVertexAndPlane(tolerances, vertices[e->m_vertex], normal, *a, *b);
		}

		WeightedNeighbour& nb = neighbours.pushBack();
		nb.m_edge = e;
		nb.m_weight = w;

		e = &edges[edges[e->m_next].m_twin];
	} while (e != start);

	if (neighbours.m_size > 1)
		quickSortRecursive_WeightedNeighbour(neighbours.m_data, 0, neighbours.m_size - 1, sortByY);

	removeCoPlanarNeighbours(tolerances, hull, normal, edge, a, b, neighbours);
}

// @ 0x0111b010
void hkGeomConvexHullBuilder::findWrapping(hkGeomHull& hullA, hkGeomHull& hullB,
	const hkArray<WeightedLine>& lines, hkArray<WrappingLine>& wrapping)
{
	int i = 0;
	if (0 < lines.m_size)
	{
		do
		{
			const WeightedLine* line = &lines.m_data[i];

			wrapping.m_size = 0;
			WrappingLine& first = wrapping.pushBack();
			first.m_edgeA = line->m_edgeA;
			first.m_edgeB = line->m_edgeB;

			for (const WeightedLine* p = line->m_lastLine; p != 0; p = p->m_lastLine)
			{
				if (p->m_edgeA == line->m_edgeA && p->m_edgeB == line->m_edgeB &&
					p->m_lastVertex == line->m_lastVertex)
				{
					char okA, okB;
					FUN_0111ab80(&okA, &hullA, hullB.m_edges.m_data, 1, &wrapping);
					FUN_0111ab80(&okB, &hullB, hullA.m_edges.m_data, 0, &wrapping);
					if (okA != 0 && okB != 0)
						return;
				}

				WrappingLine& wl = wrapping.pushBack();
				wl.m_edgeA = p->m_edgeA;
				wl.m_edgeB = p->m_edgeB;
			}

			i++;
		} while (i < lines.m_size);
	}

	wrapping.m_size = 0;
}

// @ 0x0111ab80
void FUN_0111ab80(char* pOut, hkGeomHull* hull, const void* /*unused*/, char flag,
	hkArray<WrappingLine>* wrapping)
{
	hkGeomEdge* edges = hull->m_edges.m_data;
	int changed = 0;

	for (int i = 0; i < hull->m_edges.m_size; i++)
		edges[i].m_marked = 0;

	const hkGeomEdge* cur;
	if (flag == 0)
		cur = wrapping->m_data[0].m_edgeB;
	else
		cur = wrapping->m_data[0].m_edgeA;

	int n = wrapping->m_size - 1;
	if (-1 < n)
	{
		for (int i = n; i >= 0; i--)
		{
			const hkGeomEdge* v = (flag == 0) ? wrapping->m_data[i].m_edgeB
			                                  : wrapping->m_data[i].m_edgeA;
			if (v != cur)
			{
				changed++;
				cur = v;
				if (flag != 0)
					cur = &edges[v->m_twin];
				if (cur->m_marked == 3)
				{
					*pOut = 0;
					return;
				}
				((hkGeomEdge*)cur)->m_marked = 3;
				cur = v;
			}
		}

		if (changed != 0)
		{
			const hkGeomEdge* cur2 = (flag == 0) ? wrapping->m_data[0].m_edgeB
			                                     : wrapping->m_data[0].m_edgeA;
			int m = wrapping->m_size - 1;
			if (-1 < m)
			{
				for (int i = m; i >= 0; i--)
				{
					const hkGeomEdge* v = (flag == 0) ? wrapping->m_data[i].m_edgeB
					                                  : wrapping->m_data[i].m_edgeA;
					if (v != cur2)
					{
						const hkGeomEdge* t = v;
						if (flag == 0)
							t = &edges[v->m_twin];
						unsigned short s = t->m_marked;
						cur2 = v;
						if (s == 0)
						{
							((hkGeomEdge*)t)->m_marked = 1;
						}
						else if (s == 1)
						{
							*pOut = 0;
							return;
						}
						else if (s == 3)
						{
							((hkGeomEdge*)t)->m_marked = 2;
						}
					}
				}
			}

			char local_1a, local_19;
			char cVar4 = 1;
			char local_14 = 1;
			const hkGeomEdge* cur3 = (flag == 0) ? wrapping->m_data[0].m_edgeB
			                                     : wrapping->m_data[0].m_edgeA;
			int local_c = wrapping->m_size;
			char cVar3 = local_14;
			if (-1 < local_c - 1)
			{
				do
				{
					const hkGeomEdge* v = (flag == 0) ? wrapping->m_data[local_c - 1].m_edgeB
					                                  : wrapping->m_data[local_c - 1].m_edgeA;
					if (v != cur3)
					{
						const hkGeomEdge* t = v;
						if (flag == 0)
							t = &edges[v->m_twin];
						if (t->m_marked == 1)
						{
							if (cVar4 == 0 ||
								*FUN_0111a9e0(&local_1a, hull, (int)t, 1) == 0)
								cVar4 = 0;
							else
								cVar4 = 1;
						}
						cur3 = v;
						if (edges[v->m_twin].m_marked == 3)
						{
							if (cVar4 == 0 ||
								*FUN_0111a9e0(&local_19, hull, (int)&edges[v->m_twin], 3) == 0)
								cVar4 = 0;
							else
								cVar4 = 1;
						}
					}
					local_c--;
					cVar3 = cVar4;
				} while (local_c != 0);
			}
			local_14 = cVar3;

			const hkGeomEdge* cur4 = (flag == 0) ? wrapping->m_data[0].m_edgeB
			                                     : wrapping->m_data[0].m_edgeA;
			int local_4 = wrapping->m_size;
			if (-1 < local_4 - 1)
			{
				int local_c2 = local_4 - 1;
				do
				{
					const hkGeomEdge* v = (flag == 0) ? wrapping->m_data[local_c2].m_edgeB
					                                  : wrapping->m_data[local_c2].m_edgeA;
					if (v != cur4)
					{
						const hkGeomEdge* t = v;
						if (flag == 0)
							t = &edges[v->m_twin];
						cur4 = v;
						if (t->m_marked == 2)
						{
							char local_8 = 1;
							const hkGeomEdge* w = (flag == 0) ? wrapping->m_data[0].m_edgeB
							                                  : wrapping->m_data[0].m_edgeA;
							int k = wrapping->m_size - 1;
							if (-1 < k)
							{
								do
								{
									const hkGeomEdge* u = (flag == 0) ? wrapping->m_data[k].m_edgeB
									                                  : wrapping->m_data[k].m_edgeA;
									if (u != w)
									{
										w = u;
										if (u->m_marked != 2)
										{
											local_8 = 0;
											break;
										}
									}
									k--;
								} while (-1 < k);
							}

							bool bVar2 = false;
							for (int j = 0; j < hull->m_edges.m_size; j++)
							{
								if (edges[j].m_marked == 0)
								{
									bVar2 = true;
									break;
								}
							}

							if (local_8 != 0 && bVar2)
							{
								if (local_14 == 0 ||
									*FUN_0111a9e0(&local_19, hull, (int)t, 3) == 0)
									local_14 = 0;
								else
									local_14 = 1;
							}
						}
					}
					local_c2--;
					local_4--;
				} while (local_4 != 0);
			}

			for (int j = 0; j < hull->m_edges.m_size; j++)
			{
				if (local_14 == 0 || edges[j].m_marked == 0)
					local_14 = 0;
				else
					local_14 = 1;
			}
			*pOut = local_14;
			return;
		}
	}

	*pOut = 1;
}
