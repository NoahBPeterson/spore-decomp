// Havok 3.1.0: hkGeomConvexHullBuilder::generateHullFromPlanarPoints (0x01117840).
// 2D gift wrapping of a set of coplanar points: outputs the hull vertices (in wrapping order) and the plane
// equations of the resulting flat hull: +normal, -normal, then one side plane per hull edge.
//
// Flags: /O2 /MD /Gy /TP /fp:fast (no /EHsc: the local hkArray has no EH frame).
// Self-contained: hkVector4 is 16-byte aligned (the original frame does `and esp,-16`).
// Names: method name/signature from symbols/havok_names.txt; local names are Claude-coined.
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
	void* allocateChunk(int nbytes, int memClass);               // 0x0107DAA0
	void deallocateChunk(void* p, int nbytes, int memClass);     // 0x0107DB10
	static hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }
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

	__forceinline hkArray(int size, const T& fill)
		: m_data((T*)hkThreadMemory::getInstance().allocateChunk(size * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY)),
		  m_size(size), m_capacityAndFlags(size)
	{
		for (int i = 0; i < size; i++)
			m_data[i] = fill;
	}
	~hkArray()
	{
		if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
			hkThreadMemory::getInstance().deallocateChunk(m_data, getCapacity() * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
	}
	int getSize() const { return m_size; }
	int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
	T& operator[](int i) { return m_data[i]; }
	const T& operator[](int i) const { return m_data[i]; }
	void clear() { m_size = 0; }
	void pushBack(const T& e)
	{
		if (m_size == getCapacity())
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		m_data[m_size++] = e;
	}
	T& expandOne()
	{
		if (m_size == getCapacity())
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		return m_data[m_size++];
	}
};

#define HK_REAL_MAX 3.40282e+38f
// Havok 3.1 was built by an older cl that loads 0.0f/1.0f from the constant pool (0x01485378 / 0x01485720).
extern const float kZero;   // 0x01485378
extern const float kOne;    // 0x01485720
__forceinline float hkMath_sqrt(float r) { return (float)sqrt((double)r); }       // hkMath::sqrt (inline fsqrt)
__forceinline float hkMath_sqrtInverse(float r) { return kOne / hkMath_sqrt(r); }  // hkMath::sqrtInverse
__forceinline float hkMath_fabs(float r) { return (float)fabs((double)r); }        // hkMath::fabs

struct __declspec(align(16)) hkVector4
{
	float x, y, z, w;

	__forceinline void set(float a, float b, float c, float d) { x = a; y = b; z = c; w = d; }
	__forceinline void setSub4(const hkVector4& a, const hkVector4& b) { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; w = a.w - b.w; }
	__forceinline void setNeg4(const hkVector4& a) { x = -a.x; y = -a.y; z = -a.z; w = -a.w; }
	__forceinline void add4(const hkVector4& a) { x += a.x; y += a.y; z += a.z; w += a.w; }
	__forceinline void add3clobberW(const hkVector4& a) { x += a.x; y += a.y; z += a.z; }
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
	__forceinline float length3() const { return hkMath_sqrt(lengthSquared3()); }
	__forceinline void normalize3()
	{
		const float len2 = lengthSquared3();
		const float inv = (len2 == kZero) ? kZero : kOne / hkMath_sqrt(len2);
		mul4(inv);
	}
	// Plane through p with this (unit) normal: w = -n.p
	__forceinline void setPlaneDistance(const hkVector4& p) { w = -dot3(p); }
};

class hkGeomConvexHullBuilder
{
public:
	static void generateHullFromPlanarPoints(const hkVector4& normal, const hkVector4* points, int numPoints,
		hkArray<hkVector4>& usedPoints, hkArray<hkVector4>& planeEquations);
};

// Turns the edge (inside a plane with the given in-plane normal) into an outward unit side plane through p.
static __forceinline void makeSidePlane(hkVector4& plane, const hkVector4& outside, const hkVector4& p)
{
	const float sign = (plane.dot3(outside) < 1e-6f) ? -1.0f : kOne;
	plane.mul4(sign);
	plane.normalize3();
	plane.setPlaneDistance(p);
}

// @ 0x01117840
void hkGeomConvexHullBuilder::generateHullFromPlanarPoints(const hkVector4& normal, const hkVector4* points,
	int numPoints, hkArray<hkVector4>& usedPoints, hkArray<hkVector4>& planeEquations)
{
	planeEquations.clear();
	hkVector4 negNormal;
	negNormal.setNeg4(normal);
	planeEquations.pushBack(normal);
	planeEquations.pushBack(negNormal);

	hkArray<hkBool> used(numPoints, false);

	// A direction inside the plane.
	hkVector4 perp;
	if (hkMath_fabs(kOne - hkMath_fabs(normal.z)) < 1e-6f)
	{
		hkVector4 xAxis;
		xAxis.set(1.0f, kZero, kZero, kZero);
		perp.setCross(xAxis, normal);
	}
	else
	{
		hkVector4 zAxis;
		zAxis.set(kZero, kZero, 1.0f, kZero);
		perp.setCross(normal, zAxis);
	}

	// Start with the point furthest along it: it is on the hull.
	int startIndex = -1;
	{
		float maxDist = -HK_REAL_MAX;
		for (int i = 0; i < numPoints; i++)
		{
			const float dist = points[i].dot3(perp);
			if (dist > maxDist)
			{
				maxDist = dist;
				startIndex = i;
			}
		}
	}
	used[startIndex] = true;
	usedPoints.pushBack(points[startIndex]);

	int prevIndex = startIndex;
	int currentIndex = startIndex;
	int nextIndex = -1;
	int secondIndex = -1;

	hkVector4 direction;
	direction.setCross(perp, normal);
	direction.add3clobberW(perp);

	for (;;)
	{
		float bestSin = -2.0f;
		direction.normalize3();
		float bestAngle = HK_REAL_MAX;

		// Wrap: the next point is the one with the smallest turning angle from the current direction.
		for (int i = 0; i < numPoints; i++)
		{
			if (i == currentIndex)
				continue;
			hkVector4 edge;
			edge.setSub4(points[i], points[currentIndex]);
			hkVector4 cross;
			cross.setCross(direction, edge);
			const float invLen = hkMath_sqrtInverse(edge.lengthSquared3());
			float sinAngle = cross.length3() * invLen;
			const float cosAngle = edge.dot3(direction) * invLen;
			if (cross.dot3(normal) > kZero)
				sinAngle *= -1.0f;
			float angle;
			if (cosAngle < kZero)
				angle = 2.0f - sinAngle;
			else if (sinAngle > kZero)
				angle = sinAngle;
			else
				angle = 4.0f - sinAngle;
			if (angle < bestAngle)
			{
				bestAngle = angle;
				nextIndex = i;
				bestSin = sinAngle;
			}
		}

		if (currentIndex != startIndex)
		{
			// Side plane through the edge (prev -> current).
			const hkVector4& current = points[currentIndex];
			hkVector4 edgeIn;
			edgeIn.setSub4(current, points[prevIndex]);
			hkVector4 edgeOut;
			edgeOut.setSub4(current, points[nextIndex]);
			hkVector4& plane = planeEquations.expandOne();
			hkVector4 inPlaneNormal;
			if (prevIndex == nextIndex)
				inPlaneNormal = normal;
			else
				inPlaneNormal.setCross(edgeIn, edgeOut);
			plane.setCross(edgeIn, inPlaneNormal);
			makeSidePlane(plane, edgeOut, current);
		}
		else
		{
			secondIndex = nextIndex;
		}

		if (used[nextIndex])
			break;
		used[nextIndex] = true;
		usedPoints.pushBack(points[nextIndex]);

		hkVector4 newDirection;
		newDirection.setSub4(points[nextIndex], points[currentIndex]);
		newDirection.normalize3();
		if (bestSin < 1e-4f)
			direction = newDirection;
		else
			direction.add4(newDirection);
		prevIndex = currentIndex;
		currentIndex = nextIndex;
	}

	// Closing side plane through the edge (current -> next == an already used point).
	{
		const hkVector4& next = points[nextIndex];
		hkVector4 edgeIn;
		edgeIn.setSub4(next, points[currentIndex]);
		hkVector4 edgeOut;
		edgeOut.setSub4(next, points[secondIndex]);
		hkVector4& plane = planeEquations.expandOne();
		plane.setCross(edgeIn, planeEquations[0]);
		makeSidePlane(plane, edgeOut, next);
	}
}
