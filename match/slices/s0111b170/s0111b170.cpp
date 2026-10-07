// Havok 3.1.0: hkGeomConvexHullBuilder::mergeHulls (0x0111B170).
// Merges two convex hulls (divide-and-conquer hull builder): starting from the common tangent line of the two
// hulls, it repeatedly grows a front of "weighted lines" (one hkLocalArray-style stack-allocated
// hkInplaceArray<WeightedLine,16> per round), each round picking the best wrapping neighbours on both hulls,
// until findWrapping() closes the wrapping band; then stitchHulls() splices the band into the merged hull.
//
// Built /O2 /MD /Gy /TP /fp:fast (Havok module, no /EHsc). Self-contained; same conventions as
// match/slices/s01118f50 (the sibling buildPlaneEquations):
// hkVector4 is 16-byte aligned (the original frame does `and esp,-16`), 0.0f/1.0f come from the constant pool.
// Names: methods are from symbols/havok_names.txt. Struct member names marked "(name guessed)" are Claude-coined.
// The outer loop has no iteration bound in the original (maxIterations is computed and stored into the
// config, but the loop exits only through findWrapping finding a wrapping); this is kept as is.
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

enum hkResult { HK_SUCCESS = 0, HK_FAILURE = 1 };
enum { HK_MEMORY_CLASS_ARRAY = 0x14 };

inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

extern unsigned long g_hkThreadMemoryTlsIndex;   // 0x016E4174 (hkThreadMemory::s_threadMemoryInstance TLS slot)
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

	void deallocateChunk(void* p, int nbytes, int memClass);   // 0x0107DB10
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

struct hkArrayUtil
{
	static void _reserveMore(void* array, int sizeElem);   // 0x0107F530
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
	T* begin() { return m_data; }
	void pushBack(const T& e)
	{
		if (m_size == getCapacity())
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		m_data[m_size++] = e;
	}
	void clear() { m_size = 0; }
};

template <class T, unsigned N>
class hkInplaceArray : public hkArray<T>
{
public:
	hkInplaceArray(int size = 0) : hkArray<T>(m_storage, size, N) {}
	T m_storage[N];
};

// Havok 3.1 was built by an older cl that loads 0.0f/1.0f from the constant pool (0x01485378 / 0x01485720).
extern const float kZero;   // 0x01485378
extern const float kOne;    // 0x01485720
__forceinline float hkMath_sqrt(float r) { return (float)sqrt((double)r); }   // hkMath::sqrt (inline fsqrt)

struct __declspec(align(16)) hkVector4
{
	float x, y, z, w;

	__forceinline void setSub4(const hkVector4& a, const hkVector4& b) { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
	__forceinline void setAdd4(const hkVector4& a, const hkVector4& b) { x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; w = a.w + b.w; }
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
	static __forceinline float invSqrtOrZero(float len2) { return (len2 == kZero) ? kZero : kOne / hkMath_sqrt(len2); }
	__forceinline void mul4(float s) { x = x * s; y = y * s; z = z * s; w = w * s; }
	// The original sums z, y, x (Havok's hkVector4 FPU path); written in that order for /fp:precise.
	__forceinline float lengthSquared3() const { return z * z + y * y + x * x; }
	__forceinline void normalize3()
	{
		mul4(invSqrtOrZero(lengthSquared3()));
	}
};

struct hkGeomEdge
{
	uint16_t m_vertex;   // +0
	uint16_t m_twin;     // +2
	uint16_t m_next;     // +4
	uint16_t m_pad;      // +6
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
	float m_singleLineTolerance;   // +8 (name guessed): passed to isSingleLine
	uint32_t m_padC[5];
	float m_wrappingTolerance;     // +0x20 (name guessed): seeds hkGeomConvexHullConfig, grown by 10% per stuck round
};

struct hkGeomConvexHullConfig
{
	float m_tolerance;     // +0 (read by addWrappingLines)
	int m_pad4;
	int m_maxIterations;   // +8 (name guessed): stored, never read
};

class hkGeomConvexHullBuilder
{
public:
	struct WeightedLine
	{
		hkGeomEdge* m_edgeA;          // +0 (name guessed): edge in hull A
		hkGeomEdge* m_edgeB;          // +4 (name guessed): edge in hull B
		WeightedLine* m_lastLine;     // +8 (name guessed): the line this one was grown from (0 for the tangent)
		uint16_t m_lastVertex;        // +0xc (name guessed)
		float m_weight;               // +0x10 (sort key)
	};
	struct WeightedNeighbour
	{
		uint32_t m_data[2];
	};
	struct WrappingLine
	{
		uint32_t m_data[4];
	};

	static hkResult mergeHulls(const hkGeomConvexHullTolerances& tolerances, hkGeomHull& hullA, hkGeomHull& hullB,
		hkGeomHull& mergedHull);

	static hkBool isSingleLine(float tolerance, hkGeomHull& hullA, hkGeomHull& hullB, hkGeomHull& mergedHull);   // 0x011161B0
	static void getCommonTangent(hkGeomHull& hullA, hkGeomHull& hullB, WeightedLine& line, hkVector4& normal);   // 0x01116880
	static void findWeightedNeighbours(const hkGeomConvexHullTolerances& tolerances, hkGeomHull& hull,
		const hkVector4& normal, unsigned short lastVertex, const hkGeomEdge* edge, const hkVector4* a,
		const hkVector4* b, hkArray<WeightedNeighbour>& neighbours);   // 0x0111AEF0
	static void validateNeighbours(const hkGeomConvexHullTolerances& tolerances, const hkVector4* vertices,
		const hkVector4& normal, unsigned short lastVertex, WeightedLine* line, const hkVector4* a,
		const hkVector4* b, hkArray<WeightedNeighbour>& neighboursA, hkArray<WeightedNeighbour>& neighboursB);   // 0x0111A8A0
	static void addWrappingLines(const hkGeomConvexHullConfig& config, WeightedLine* line,
		hkArray<WeightedNeighbour>& neighboursA, hkArray<WeightedNeighbour>& neighboursB,
		hkArray<WeightedLine>& newLines);   // 0x01117580
	static void findWrapping(hkGeomHull& hullA, hkGeomHull& hullB, const hkArray<WeightedLine>& lines,
		hkArray<WrappingLine>& wrapping);   // 0x0111B010
	static void stitchHulls(hkGeomHull& hullA, hkGeomHull& hullB, hkArray<WrappingLine>& wrapping,
		hkGeomHull& mergedHull);   // 0x0111A290
};

// 0x01115A20 (name guessed): a.m_weight < b.m_weight
hkBool weightedLineLess(const hkGeomConvexHullBuilder::WeightedLine& a, const hkGeomConvexHullBuilder::WeightedLine& b);

struct hkAlgorithm
{
	template <class T, class L>
	static void quickSortRecursive(T* data, int lo, int hi, L less);   // 0x01115A50 (instance for WeightedLine)
};
template <> void hkAlgorithm::quickSortRecursive<hkGeomConvexHullBuilder::WeightedLine,
	hkBool (*)(const hkGeomConvexHullBuilder::WeightedLine&, const hkGeomConvexHullBuilder::WeightedLine&)>(
	hkGeomConvexHullBuilder::WeightedLine* data, int lo, int hi,
	hkBool (*less)(const hkGeomConvexHullBuilder::WeightedLine&, const hkGeomConvexHullBuilder::WeightedLine&));

typedef hkGeomConvexHullBuilder::WeightedLine WeightedLine;
typedef hkInplaceArray<WeightedLine, 16> LineArray;   // 0x14c bytes, 0x150 on the thread-memory stack

// @ 0x0111b170
hkResult hkGeomConvexHullBuilder::mergeHulls(const hkGeomConvexHullTolerances& tolerances, hkGeomHull& hullA,
	hkGeomHull& hullB, hkGeomHull& mergedHull)
{
	mergedHull.m_vertices = hullA.m_vertices;
	if (isSingleLine(tolerances.m_singleLineTolerance, hullA, hullB, mergedHull))
		return HK_SUCCESS;

	const hkVector4* vertices = hullA.m_vertices;
	hkInplaceArray<WeightedLine, 1> tangentLine(1);
	hkVector4 tangentNormal;
	getCommonTangent(hullA, hullB, tangentLine[0], tangentNormal);
	hkVector4 lastNormal = tangentNormal;

	int maxNumLines = hullA.m_edges.getSize() + hullB.m_edges.getSize() + 2;
	hkGeomConvexHullConfig config;
	config.m_tolerance = tolerances.m_wrappingTolerance;
	const int maxIterations = maxNumLines * 3;
	config.m_maxIterations = maxIterations;

	hkInplaceArray<hkArray<WeightedLine>*, 64> lineArrays;
	hkInplaceArray<WrappingLine, 128> wrapping;
	hkArray<WeightedLine>* currentLines = &tangentLine;

	if (maxIterations > 0)
	{
		for (int iteration = 0;; iteration++)
		{
			if (iteration > maxNumLines)
			{
				config.m_tolerance = config.m_tolerance * 1.1f;
				if (config.m_tolerance > 1.0f)
					maxNumLines++;
			}

			void* mem = hkThreadMemory::getInstance().allocateStack(sizeof(LineArray));
			LineArray* newLines = new (mem) LineArray;
			lineArrays.pushBack(newLines);

			for (int i = 0; i < currentLines->getSize(); i++)
			{
				WeightedLine& line = (*currentLines)[i];
				hkInplaceArray<WeightedNeighbour, 64> neighboursA;
				hkInplaceArray<WeightedNeighbour, 64> neighboursB;

				const hkVector4* a = &vertices[line.m_edgeA->m_vertex];
				const hkVector4* b = &vertices[line.m_edgeB->m_vertex];
				hkVector4 normal;

				const WeightedLine* last = line.m_lastLine;
				if (last == 0)
				{
					normal = tangentNormal;
				}
				else
				{
					const hkVector4* lastA = &vertices[last->m_edgeA->m_vertex];
					const hkVector4* lastB = &vertices[last->m_edgeB->m_vertex];
					const hkVector4* other = b;
					if (lastA != a)
						other = a;

					hkVector4 lastDir;
					lastDir.setSub4(*lastB, *lastA);
					lastDir.normalize3();
					hkVector4 dir;
					dir.setSub4(*other, *lastA);
					dir.normalize3();
					normal.setCross(lastDir, dir);
					if (normal.lengthSquared3() < 1e-6f)
					{
						dir.setSub4(*other, *lastB);
						dir.normalize3();
						normal.setCross(lastDir, dir);
						if (normal.lengthSquared3() < 1e-6f)
						{
							hkVector4 sum;
							sum.setAdd4(dir, lastDir);
							hkVector4 diff;
							diff.setSub4(lastDir, dir);
							const float diffLen2 = diff.lengthSquared3();
							float sumLen2;
							if (diffLen2 < 1e-6f || (sumLen2 = sum.lengthSquared3()) < 1e-6f)
							{
								normal = lastNormal;
							}
							else
							{
								sum.mul4(hkVector4::invSqrtOrZero(sumLen2));
								diff.mul4(hkVector4::invSqrtOrZero(diffLen2));
								normal.setCross(diff, sum);
							}
						}
					}
					normal.normalize3();
				}
				lastNormal = normal;

				findWeightedNeighbours(tolerances, hullA, normal, line.m_lastVertex, line.m_edgeA, a, b, neighboursA);
				findWeightedNeighbours(tolerances, hullB, normal, line.m_lastVertex, line.m_edgeB, a, b, neighboursB);
				validateNeighbours(tolerances, hullB.m_vertices, normal, line.m_lastVertex, &line, a, b, neighboursA, neighboursB);
				addWrappingLines(config, &line, neighboursA, neighboursB, *newLines);
			}

			currentLines = newLines;
			if (newLines->getSize() > 1)
				hkAlgorithm::quickSortRecursive<WeightedLine, hkBool (*)(const WeightedLine&, const WeightedLine&)>(
					newLines->begin(), 0, newLines->getSize() - 1, weightedLineLess);
			findWrapping(hullA, hullB, *newLines, wrapping);
			if (wrapping.getSize() != 0)
				break;
		}
	}

	for (int i = lineArrays.getSize() - 1; i >= 0; i--)
	{
		((LineArray*)lineArrays[i])->~LineArray();
		hkThreadMemory::getInstance().deallocateStack(lineArrays[i]);
	}
	lineArrays.clear();

	if (wrapping.getSize() == 0)
		return HK_FAILURE;

	stitchHulls(hullA, hullB, wrapping, mergedHull);
	return HK_SUCCESS;
}
