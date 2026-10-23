// Havok 3.1.0 hkGeomConvexHullBuilder convex-hull construction helpers:
//   0x01117140  removeFlaggedVertices(hkArray<hkVector4>&)
//   0x011172b0  calculateNewNeighbours(const hkVector4*, const hkGeomConvexHullTolerances&, float,
//                                         const hkVector4&, const hkGeomEdge*, const hkVector4&,
//                                         const hkVector4&, hkArray<WeightedNeighbour>&)
//   0x01117580  addWrappingLines(const hkGeomConvexHullConfig&, WeightedLine*,
//                                   hkArray<WeightedNeighbour>&, hkArray<WeightedNeighbour>&,
//                                   hkArray<WeightedLine>&)
//
// Names come from symbols/havok_names.txt (all tagged `# havok identical-code`).
// The Havok 3.1 sources are not on disk; reconstructed from the retail disassembly.
//
// Flags: /vc71 /O2 /MD /Gy /TP
#include "../s0107e670/hk31_base.h"
#include <math.h>

// Havok 3.1 floats are pushed from the constant pool rather than fldz/fld1:
//   0x01485378 = 0.0f (kZero), 0x01485720 = 1.0f (kOne)
extern const float kZero;   // 0x01485378
extern const float kOne;    // 0x01485720

__forceinline float hkMath_sqrt(float r) { return (float)sqrt((double)r); }
__forceinline float hkMath_fabs(float r) { return (float)fabs((double)r); }

// hkGeomEdge: the retail code only ever reads the leading 16-bit vertex index.
class hkGeomEdge
{
public:
	hkUint16 m_vertex;
	hkUint16 m_pad;
};

// hkGeomConvexHullConfig: only the leading float (the wrapping-line distance threshold) is used.
struct hkGeomConvexHullConfig
{
	float m_distance;
};

// hkGeomConvexHullTolerances: only the float at +0xc is read here (0x011172b0) but the
// struct is passed by reference to getAngleBetweenVertexAndPlane (0x01116a20) as well.
struct hkGeomConvexHullTolerances
{
	float m_00, m_04, m_08, m_0c, m_10, m_14, m_18, m_1c;
};

class hkGeomConvexHullBuilder
{
public:
	// WeightedNeighbour: a vertex (whose leading 16-bit word is the vertex index) + its weight.
	struct WeightedNeighbour
	{
		const short* m_vertex;   // +0
		float        m_weight;   // +4
	};

	// WeightedLine: two vertex pointers, the owning line, a 32-bit tag and the accumulated weight.
	struct WeightedLine
	{
		const short* m_a;    // +0
		const short* m_b;    // +4
		const void*  m_c;    // +8
		unsigned int m_tag;  // +0xc
		float        m_w;    // +0x10
	};

	static void removeFlaggedVertices(hkArray<hkVector4>& vertices);
	static void calculateNewNeighbours(const hkVector4* vertices,
	                                   const hkGeomConvexHullTolerances& tolerances,
	                                   float f,
	                                   const hkVector4& v,
	                                   const hkGeomEdge* edge,
	                                   const hkVector4& a,
	                                   const hkVector4& b,
	                                   hkArray<WeightedNeighbour>& neighbours);
	static void addWrappingLines(const hkGeomConvexHullConfig& config,
	                             WeightedLine* line,
	                             hkArray<WeightedNeighbour>& linesA,
	                             hkArray<WeightedNeighbour>& linesB,
	                             hkArray<WeightedLine>& out);
	static float getAngleBetweenVertexAndPlane(const hkGeomConvexHullTolerances& tolerances,
	                                           const hkVector4& vertex,
	                                           const hkVector4& a,
	                                           const hkVector4& b,
	                                           const hkVector4& c);   // 0x01116A20
};

typedef bool (*WeightedNeighbourLess)(const hkGeomConvexHullBuilder::WeightedNeighbour&,
                                      const hkGeomConvexHullBuilder::WeightedNeighbour&);

// hkAlgorithm::quickSortRecursive<WeightedNeighbour,...>  (0x01115BF0)
extern void FUN_01115bf0(hkGeomConvexHullBuilder::WeightedNeighbour* data, int lo, int hi,
                         WeightedNeighbourLess less);
extern bool FUN_011159f0(const hkGeomConvexHullBuilder::WeightedNeighbour& a,
                         const hkGeomConvexHullBuilder::WeightedNeighbour& b);

// @ 0x01117140
void hkGeomConvexHullBuilder::removeFlaggedVertices(hkArray<hkVector4>& vertices)
{
	int num = vertices.m_size;
	hkVector4* src = vertices.m_data;
	int remainder = num - 1;
	hkVector4* dst = src;

	if (remainder + 1 >= 4)
	{
		int n = (int)((unsigned int)num >> 2);
		remainder -= n * 4;
		do
		{
			if (src->w == kZero) { hkVector4* p = dst++; p->x = src->x; p->y = src->y; p->z = src->z; p->w = src->w; }
			src++;
			if (src->w == kZero) { hkVector4* p = dst++; p->x = src->x; p->y = src->y; p->z = src->z; p->w = src->w; }
			src++;
			if (src->w == kZero) { hkVector4* p = dst++; p->x = src->x; p->y = src->y; p->z = src->z; p->w = src->w; }
			src++;
			if (src->w == kZero) { hkVector4* p = dst++; p->x = src->x; p->y = src->y; p->z = src->z; p->w = src->w; }
			src++;
		} while (--n);
	}

	if (remainder >= 0)
	{
		remainder++;
		do
		{
			if (src->w == kZero) { hkVector4* p = dst++; p->x = src->x; p->y = src->y; p->z = src->z; p->w = src->w; }
			src++;
		} while (--remainder);
	}

	int count = (int)(dst - vertices.m_data);
	if ((int)(vertices.m_capacityAndFlags & 0x3FFFFFFF) < count)
	{
		int cap = (vertices.m_capacityAndFlags & 0x3FFFFFFF) * 2;
		if (cap <= count) cap = count;
		hkArrayUtil::_reserveExactly(&vertices, cap, (int)sizeof(hkVector4));
	}
	vertices.m_size = count;
}

// @ 0x011172b0
void hkGeomConvexHullBuilder::calculateNewNeighbours(const hkVector4* vertices,
                                                     const hkGeomConvexHullTolerances& tolerances,
                                                     float f,
                                                     const hkVector4& v,
                                                     const hkGeomEdge* edge,
                                                     const hkVector4& a,
                                                     const hkVector4& b,
                                                     hkArray<WeightedNeighbour>& neighbours)
{
	float fVar2 = tolerances.m_0c;
	const hkVector4* pfVar7 = &vertices[edge->m_vertex];

	float local_50 = v.x;
	float local_4c = v.y;
	float local_48 = v.z;
	float local_44 = v.w;
	float fVar3 = a.x - b.x;
	float fVar4 = a.y - b.y;
	float local_38 = a.z - b.z;

	float local_54;
	float fVar5;
	float fVar6;

	if ((f < fVar2) || (8.0f - fVar2 < f))
	{
		fVar2 = local_48 * fVar3 - local_38 * local_50;
		local_54 = fVar4 * local_50 - local_4c * fVar3;
		local_50 = local_4c * local_38 - local_48 * fVar4;
		fVar5 = local_54 * local_54 + local_50 * local_50;
		fVar6 = fVar2 * fVar2;
	}
	else
	{
		if (fVar2 <= hkMath_fabs(f - 4.0f))
			goto LAB_01117446;
		fVar2 = local_38 * local_50 - local_48 * fVar3;
		local_54 = local_4c * fVar3 - fVar4 * local_50;
		local_50 = local_48 * fVar4 - local_4c * local_38;
		fVar5 = fVar2 * fVar2 + local_50 * local_50;
		fVar6 = local_54 * local_54;
	}

	if (fVar6 + fVar5 == kZero)
		local_44 = kZero;
	else
		local_44 = kOne / hkMath_sqrt(fVar6 + fVar5);

	local_50 = local_50 * local_44;
	local_4c = local_44 * fVar2;
	local_48 = local_54 * local_44;
	local_44 = local_44 * kZero;

LAB_01117446:
	float local_34 = pfVar7->w;
	float local_40 = (local_4c * local_38 - local_48 * fVar4) + pfVar7->x;
	float local_3c = (local_48 * fVar3 - local_38 * local_50) + pfVar7->y;
	fVar2 = (fVar4 * local_50 - local_4c * fVar3) + pfVar7->z;

	hkVector4 vecA;
	hkVector4 vecB;
	if (pfVar7 == &a)
	{
		vecA.x = pfVar7->x;
		vecA.y = pfVar7->y;
		vecA.z = pfVar7->z;
		vecA.w = pfVar7->w;
		vecB.x = local_40;
		vecB.y = local_3c;
		vecB.z = fVar2;
		vecB.w = local_34;
	}
	else
	{
		vecB.x = pfVar7->x;
		vecB.y = pfVar7->y;
		vecB.z = pfVar7->z;
		vecB.w = pfVar7->w;
		vecA.x = local_40;
		vecA.y = local_3c;
		vecA.z = fVar2;
		vecA.w = local_34;
	}

	hkVector4 plane;
	plane.x = local_50;
	plane.y = local_4c;
	plane.z = local_48;
	plane.w = local_44;

	int iVar8 = 0;
	if (0 < neighbours.m_size)
	{
		do
		{
			WeightedNeighbour* puVar1 = &neighbours.m_data[iVar8];
			puVar1->m_weight = getAngleBetweenVertexAndPlane(tolerances,
			                                                 vertices[*(const unsigned short*)puVar1->m_vertex],
			                                                 plane, vecB, vecA);
			iVar8++;
		} while (iVar8 < neighbours.m_size);
	}

	if (1 < neighbours.m_size)
		FUN_01115bf0(neighbours.m_data, 0, neighbours.m_size - 1, FUN_011159f0);
}

// @ 0x01117580
void hkGeomConvexHullBuilder::addWrappingLines(const hkGeomConvexHullConfig& config,
                                               WeightedLine* line,
                                               hkArray<WeightedNeighbour>& linesA,
                                               hkArray<WeightedNeighbour>& linesB,
                                               hkArray<WeightedLine>& out)
{
	float minW;
	if (linesA.m_size == 0)
	{
		minW = linesB.m_data[0].m_weight;
	}
	else if (linesB.m_size == 0)
	{
		minW = linesA.m_data[0].m_weight;
	}
	else
	{
		minW = linesB.m_data[0].m_weight;
		if (linesA.m_data[0].m_weight < minW)
			minW = linesA.m_data[0].m_weight;
	}

	const short* psVar1 = line->m_b;
	for (int i = 0; i < linesA.m_size; i++)
	{
		float fVar3 = linesA.m_data[i].m_weight - minW;
		if (config.m_distance < fVar3) break;
		const short* psVar2 = linesA.m_data[i].m_vertex;
		fVar3 = fVar3 + line->m_w;
		unsigned int uVar7 = *(const unsigned short*)line->m_a;

		int k = 0;
		for (; k < out.m_size; k++)
		{
			WeightedLine& e = out.m_data[k];
			if (*(const short*)e.m_a == *psVar2 &&
			    *(const short*)e.m_b == *psVar1 &&
			    e.m_tag == uVar7)
			{
				if (e.m_w < fVar3)
				{
					e.m_a = psVar2;
					e.m_b = psVar1;
					e.m_c = line;
					e.m_tag = uVar7;
					e.m_w = fVar3;
				}
				goto next1;
			}
		}
		if (out.m_size == (out.m_capacityAndFlags & 0x3FFFFFFF))
			hkArrayUtil::_reserveMore(&out, 0x14);
		{
			WeightedLine& e = out.m_data[out.m_size];
			e.m_a = psVar2;
			e.m_b = psVar1;
			e.m_c = line;
			e.m_tag = uVar7;
			e.m_w = fVar3;
			out.m_size++;
		}
	next1: ;
	}

	psVar1 = line->m_a;
	for (int i = 0; i < linesB.m_size; i++)
	{
		float fVar3 = linesB.m_data[i].m_weight - minW;
		if (config.m_distance < fVar3) break;
		const short* psVar2 = linesB.m_data[i].m_vertex;
		fVar3 = fVar3 + line->m_w;
		unsigned int uVar7 = *(const unsigned short*)line->m_b;

		int k = 0;
		for (; k < out.m_size; k++)
		{
			WeightedLine& e = out.m_data[k];
			if (*(const short*)e.m_a == *psVar1 &&
			    *(const short*)e.m_b == *psVar2 &&
			    e.m_tag == uVar7)
			{
				if (e.m_w < fVar3)
				{
					e.m_a = psVar1;
					e.m_b = psVar2;
					e.m_c = line;
					e.m_tag = uVar7;
					e.m_w = fVar3;
				}
				goto next2;
			}
		}
		if (out.m_size == (out.m_capacityAndFlags & 0x3FFFFFFF))
			hkArrayUtil::_reserveMore(&out, 0x14);
		{
			WeightedLine& e = out.m_data[out.m_size];
			e.m_a = psVar1;
			e.m_b = psVar2;
			e.m_c = line;
			e.m_tag = uVar7;
			e.m_w = fVar3;
			out.m_size++;
		}
	next2: ;
	}
}
