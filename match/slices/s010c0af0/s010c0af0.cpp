// Havok 3.1.0 (VC .NET 2003, cl 13.10) — hkBoxShape ray cast, the hkConvexShape ray/projection wrappers,
// the hkConvexVerticesShape vertex queries, hkAabbUtil::calcAabb and hkConvexVerticesShape::getOriginalVertices.
//
// Module flags: /O2 /MD /Gy /TP /vc71
//
// 0x010C0AF0 hkBoxShape::castRay                 — slab ray/box intersection against ±(m_halfExtents + m_radius).
// 0x010C0F80 hkConvexShape::getMaximumProjection — vcall getSupportingVertex, then dot3 with `dir` plus m_radius.
// 0x010C0FC0 hkConvexShape::castRayWithCollector — castRay, rotate the normal into world space, addHit.
// 0x010C1080 hkConvexVerticesShape::getCollisionSpheresInfo — size + "use the shared buffer".
// 0x010C1090 hkConvexVerticesShape::getFirstVertex — first lane of the first FourVectors.
// 0x010C10C0 hkConvexVerticesShape::getCollisionSpheres — one sphere per vertex (centre + m_radius).
// 0x010C1250 hkConvexVerticesShape::getSupportingVertex (name guessed — no PDB name; vtable slot 9) —
//            vertex maximising dot3(dir); out.w carries the winning index in its raw bits.
// 0x010C1520 hkConvexVerticesShape::convertVertexIdsToVertices — gather vertices by id.
// 0x010C16B0 hkAabbUtil::calcAabb — world-space AABB of a half-extent box under a transform.
// 0x010C1910 hkConvexVerticesShape::getOriginalVertices — un-swizzle the vertices, w cleared.
//
// Self-contained: hkVector4 is 16-byte aligned (the original frames do `and esp,-16`).
#include "types.h"
#include <math.h>

#ifdef _WIN32
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
#endif
// cl 13.10 has no __rdtsc intrinsic, so the original inlines the instruction directly.
static __forceinline unsigned int hkRdtsc()
{
	unsigned int t;
	__asm { rdtsc }
	__asm { mov t, eax }
	return t;
}

typedef unsigned short hkUint16;

// Havok's hkBool: one byte, with a user copy constructor (so the original returns it via a hidden pointer).
class hkBool
{
public:
	char m_bool;
	hkBool() {}
	hkBool(bool b) : m_bool(b ? 1 : 0) {}
	hkBool(const hkBool& b) : m_bool(b.m_bool) {}
	operator bool() const { return m_bool != 0; }
};

// ---- main memory ----------------------------------------------------------------------------------------
enum { HK_MEMORY_CLASS_ARRAY = 0x14 };

extern unsigned long g_hkThreadMemoryTlsIndex;   // 0x016E4174 (hkThreadMemory TLS slot)
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
};

// ---- monitor stream (HK_TIMER_BEGIN / HK_TIMER_END) ------------------------------------------------------
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorTimerEndTag[];           // "Et" @ 0x0149cc34
extern const char hkMonitorTimerTtrcBox[];          // "TtrcBox" @ 0x014a27c4

struct hkMonitorCommand { const char* m_commandAndMonitor; unsigned int m_time0; unsigned int m_pad; };

#define HK_TIMER_COMMAND(name) do { \
	void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
	if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
		hkMonitorCommand* hkCmd_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
		hkCmd_->m_commandAndMonitor = name; \
		volatile unsigned int hkTicks_ = hkRdtsc(); \
		hkCmd_->m_time0 = hkTicks_; \
		TlsSetValue(g_hkMonitorStreamCurrentTls, hkCmd_ + 1); } } while (0)
#define HK_TIMER_BEGIN(name) HK_TIMER_COMMAND(name)
#define HK_TIMER_END()       HK_TIMER_COMMAND(hkMonitorTimerEndTag)

// ---- math ----------------------------------------------------------------------------------------------
#define HK_REAL_MAX 3.40282e+38f      // 0x7f7fffee in this build (not FLT_MAX)

class __declspec(align(16)) hkVector4
{
public:
	float x, y, z, w;

	float& operator[](int i) { return (&x)[i]; }
	const float& operator[](int i) const { return (&x)[i]; }

	void setZero() { x = 0.0f; y = 0.0f; z = 0.0f; w = 0.0f; }
};

// Store the raw 32-bit pattern `bits` into the float `f` (the binary writes index | 0x3f000000).
static __forceinline void hkSetRaw(float& f, unsigned int bits) { *(unsigned int*)&f = bits; }

// hkSphere: centre vector; the radius occupies the w lane (size 0x10).
class hkSphere
{
public:
	hkVector4 m_pos;   // +0x00 (m_pos.w = radius)
};

// ---- shape ray cast ------------------------------------------------------------------------------------
struct hkShapeRayCastInput
{
	hkVector4 m_from;       // +0x00
	hkVector4 m_to;         // +0x10
	uint32_t m_filterInfo;  // +0x20
	const void* m_filter;   // +0x24
};

struct hkShapeRayCastOutput
{
	hkVector4 m_normal;     // +0x00
	int m_shapeKey;         // +0x10
	float m_hitFraction;    // +0x14
};

struct hkAabb
{
	hkVector4 m_min;        // +0x00
	hkVector4 m_max;        // +0x10
};

class hkTransform
{
public:
	hkVector4 m_rotation[3];   // +0x00 .. +0x2c
	hkVector4 m_translation;   // +0x30 .. +0x3c
};

class hkCdBody
{
public:
	const void* m_shape;            // +0x00
	int m_shapeKey;                 // +0x04
	const hkTransform* m_transform; // +0x08
	const hkCdBody* m_parent;       // +0x0c
};

class hkCdVertex : public hkVector4
{
};

class hkRayHitCollector
{
public:
	virtual void addHit(const hkCdBody& body, const hkShapeRayCastOutput& hit) = 0;   // vtable slot 0
	float m_earlyOutHitFraction;   // +0x04
};

// hkFourVectors<hkVector4>: four vertices in SoA form (0x30 bytes).
struct FourVectors
{
	hkVector4 m_x;   // +0x00
	hkVector4 m_y;   // +0x10
	hkVector4 m_z;   // +0x20
};

// hkSphereRepShape only exists here to host the nested hkCollisionSpheresInfo (mangled as such).
class hkSphereRepShape
{
public:
	struct hkCollisionSpheresInfo
	{
		int m_numSpheres;   // +0x00
		bool m_useBuffer;   // +0x04
	};
};

// The whole 12-slot shape vtable lives on this single base, in the observed order, so that the emitted
// vcall displacements match: castRay is slot 5 (0x14) and getSupportingVertex is slot 9 (0x24).
class hkConvexShape
{
public:
	virtual ~hkConvexShape() {}
	virtual void calcStatistics(void*) const {}
	virtual int getType() const { return 0; }
	virtual void getAabb(const hkTransform&, float, hkAabb&) const {}
	virtual float getMaximumProjection(const hkVector4& dir) const;                       // 0x010C0F80
	virtual hkBool castRay(const hkShapeRayCastInput& in, hkShapeRayCastOutput& out) const = 0;
	virtual void castRayWithCollector(const hkShapeRayCastInput& in, const hkCdBody& body,
		hkRayHitCollector& collector) const;                                             // 0x010C0FC0
	virtual void getCollisionSpheresInfo(hkSphereRepShape::hkCollisionSpheresInfo& info) const = 0;
	virtual const hkSphere* getCollisionSpheres(hkSphere* buffer) const = 0;
	virtual void getSupportingVertex(const hkVector4& dir, hkCdVertex& out) const = 0;
	virtual void convertVertexIdsToVertices(const hkUint16* ids, int numIds, hkCdVertex* out) const = 0;
	virtual void getFirstVertex(hkVector4& out) const = 0;

	int m_memSizeAndFlags;   // +0x04
	int m_referenceCount;    // +0x08
	float m_radius;          // +0x0c
};

class hkConvexVerticesShape : public hkConvexShape
{
public:
	hkVector4 m_aabbHalfExtents;              // +0x10
	hkVector4 m_aabbCenter;                   // +0x20
	hkArray<FourVectors> m_rotatedVertices;   // +0x30 (m_data / m_size / m_capacityAndFlags)
	int m_numVertices;                        // +0x3c

	virtual void getCollisionSpheresInfo(hkSphereRepShape::hkCollisionSpheresInfo& info) const;        // 0x010C1080
	virtual void getFirstVertex(hkVector4& out) const;                                                 // 0x010C1090
	virtual const hkSphere* getCollisionSpheres(hkSphere* buffer) const;                               // 0x010C10C0
	virtual void getSupportingVertex(const hkVector4& dir, hkCdVertex& out) const;                     // 0x010C1250
	virtual void convertVertexIdsToVertices(const hkUint16* ids, int numIds, hkCdVertex* out) const;   // 0x010C1520
	void getOriginalVertices(hkArray<hkVector4>& out) const;                                           // 0x010C1910
};

class hkBoxShape : public hkConvexShape
{
public:
	hkVector4 m_halfExtents;   // +0x10
	virtual hkBool castRay(const hkShapeRayCastInput& in, hkShapeRayCastOutput& out) const;   // 0x010C0AF0
};

struct hkAabbUtil
{
	static void calcAabb(const hkTransform& transform, const hkVector4& halfExtents, const hkVector4& center,
		float extraRadius, hkAabb& out);                                                               // 0x010C16B0
};

// @ 0x010c0af0
hkBool hkBoxShape::castRay(const hkShapeRayCastInput& in, hkShapeRayCastOutput& out) const
{
	HK_TIMER_BEGIN(hkMonitorTimerTtrcBox);

	const float radius = m_radius;
	const float plusX = radius + m_halfExtents.x;
	const float plusY = radius + m_halfExtents.y;
	const float plusZ = radius + m_halfExtents.z;
	const float plusW = radius + m_halfExtents.w;
	const float minusX = -plusX;
	const float minusY = -plusY;
	const float minusZ = -plusZ;
	const float minusW = -plusW;

	unsigned int fromPlus = ((plusX <= in.m_from.x) ? 8u : 0u) | ((plusY <= in.m_from.y) ? 4u : 0u) |
		((plusZ <= in.m_from.z) ? 2u : 0u) | ((plusW <= in.m_from.w) ? 1u : 0u);
	unsigned int fromMinus = ((in.m_from.x <= minusX) ? 8u : 0u) | ((in.m_from.y <= minusY) ? 4u : 0u) |
		((in.m_from.z <= minusZ) ? 2u : 0u) | ((in.m_from.w <= minusW) ? 1u : 0u);
	unsigned int toPlus = ((plusX <= in.m_to.x) ? 8u : 0u) | ((plusY <= in.m_to.y) ? 4u : 0u) |
		((plusZ <= in.m_to.z) ? 2u : 0u) | ((plusW <= in.m_to.w) ? 1u : 0u);
	unsigned int toMinus = ((in.m_to.x <= minusX) ? 8u : 0u) | ((in.m_to.y <= minusY) ? 4u : 0u) |
		((in.m_to.z <= minusZ) ? 2u : 0u) | ((in.m_to.w <= minusW) ? 1u : 0u);
	fromPlus &= 0xe;
	fromMinus &= 0xe;
	toPlus &= 0xe;
	toMinus &= 0xe;

	if ((fromPlus & toPlus) != 0 || (fromMinus & toMinus) != 0 || (fromPlus | fromMinus) == 0)
	{
		HK_TIMER_END();
		return hkBool(false);
	}

	const float from[4] = { in.m_from.x, in.m_from.y, in.m_from.z, in.m_from.w };
	const float to[4] = { in.m_to.x, in.m_to.y, in.m_to.z, in.m_to.w };
	const float minus[4] = { minusX, minusY, minusZ, minusW };
	static const unsigned int axisBit[3] = { 8, 4, 2 };

	float best1 = 0.0f;
	float best2 = out.m_hitFraction;
	hkVector4 normal;
	normal.setZero();

	unsigned int mask = (toPlus | fromPlus) & 0xe;
	unsigned int fromBits = fromPlus;
	float C = 1.0f;
	int pass = 1;

	do
	{
		int axis = 2;
		do
		{
			const unsigned int bit = axisBit[axis];
			if ((mask & bit) != 0)
			{
				const float q = minus[axis];
				const float num = C * from[axis] + q;
				const float t = num / (num - (C * to[axis] + q));

				if ((fromBits & bit) != 0)
				{
					if (t >= best1)
					{
						best1 = t;
						normal.setZero();
						normal[axis] = C;
					}
				}
				else if (t <= best2)
				{
					best2 = t;
				}

				if (best2 < best1)
				{
					HK_TIMER_END();
					return hkBool(false);
				}
			}
			axis--;
		} while (axis >= 0);

		C = -1.0f;
		mask = (toMinus | fromMinus) & 0xe;
		fromBits = fromMinus;
		pass--;
	} while (pass >= 0);

	out.m_normal = normal;
	out.m_shapeKey = -1;
	out.m_hitFraction = best1;

	HK_TIMER_END();
	return hkBool(true);
}

// @ 0x010c0f80
float hkConvexShape::getMaximumProjection(const hkVector4& dir) const
{
	hkCdVertex v;
	getSupportingVertex(dir, v);
	return v.x * dir.x + v.y * dir.y + v.z * dir.z + m_radius;
}

// @ 0x010c0fc0
void hkConvexShape::castRayWithCollector(const hkShapeRayCastInput& in, const hkCdBody& body,
	hkRayHitCollector& collector) const
{
	hkShapeRayCastOutput out;
	out.m_hitFraction = collector.m_earlyOutHitFraction;

	if (!castRay(in, out))
		return;

	out.m_shapeKey = body.m_shapeKey;

	const float* m = (const float*)body.m_transform;
	const float nx = out.m_normal.x;
	const float ny = out.m_normal.y;
	const float nz = out.m_normal.z;

	out.m_normal.x = (nz * m[8] + ny * m[4]) + nx * m[0];
	out.m_normal.y = (nz * m[9] + nx * m[1]) + ny * m[5];
	out.m_normal.z = (nz * m[10] + ny * m[6]) + nx * m[2];
	out.m_normal.w = 0.0f;

	collector.addHit(body, out);
}

// @ 0x010c1080
void hkConvexVerticesShape::getCollisionSpheresInfo(hkSphereRepShape::hkCollisionSpheresInfo& info) const
{
	info.m_numSpheres = m_numVertices;
	info.m_useBuffer = true;
}

// @ 0x010c1090
void hkConvexVerticesShape::getFirstVertex(hkVector4& out) const
{
	out.x = m_rotatedVertices.m_data->m_x.x;
	out.y = m_rotatedVertices.m_data->m_y.x;
	out.z = m_rotatedVertices.m_data->m_z.x;
	out.w = 0.0f;
}

// @ 0x010c10c0
const hkSphere* hkConvexVerticesShape::getCollisionSpheres(hkSphere* buffer) const
{
	hkSphere* spheres = buffer;
	const FourVectors* src = m_rotatedVertices.m_data;
	const int last = m_numVertices - 1;
	int remainder = last;

	if (last >= 3)
	{
		int groups = (unsigned int)(last + 1) >> 2;
		remainder = last + groups * -4;

		do
		{
			for (int lane = 0; lane < 4; lane++)
			{
				spheres->m_pos.x = src->m_x[lane];
				spheres->m_pos.y = src->m_y[lane];
				spheres->m_pos.z = src->m_z[lane];
				spheres->m_pos.w = m_radius;
				spheres++;
			}
			src++;
			groups--;
		} while (groups != 0);
	}

	if (remainder >= 0)
	{
		spheres->m_pos.x = src->m_x.x;
		spheres->m_pos.y = src->m_y.x;
		spheres->m_pos.z = src->m_z.x;
		spheres->m_pos.w = m_radius;
		spheres++;
	}
	if (remainder >= 1)
	{
		spheres->m_pos.x = src->m_x.y;
		spheres->m_pos.y = src->m_y.y;
		spheres->m_pos.z = src->m_z.y;
		spheres->m_pos.w = m_radius;
		spheres++;
	}
	if (remainder >= 2)
	{
		spheres->m_pos.x = src->m_x.z;
		spheres->m_pos.y = src->m_y.z;
		spheres->m_pos.z = src->m_z.z;
		spheres->m_pos.w = m_radius;
	}

	return buffer;
}

// @ 0x010c1250  (name guessed: vtable slot 9, hkConvexShape::getSupportingVertex)
void hkConvexVerticesShape::getSupportingVertex(const hkVector4& dir, hkCdVertex& out) const
{
	const FourVectors* verts = m_rotatedVertices.m_data;
	const int numVertices = m_rotatedVertices.m_size * 4;

	unsigned int bestIndex = 0;

	if (numVertices > 0)
	{
		const float dx = dir.x;
		const float dy = dir.y;
		const float dz = dir.z;

		float max0 = -HK_REAL_MAX;
		float max1 = -HK_REAL_MAX;
		float max2 = -HK_REAL_MAX;
		float max3 = -HK_REAL_MAX;

		unsigned int idx = 3;
		const FourVectors* v = verts;
		do
		{
			const float d0 = dz * v->m_z.x + (dy * v->m_y.x + dx * v->m_x.x);
			const float d1 = dz * v->m_z.y + (dy * v->m_y.y + dx * v->m_x.y);
			const float d2 = dz * v->m_z.z + (dy * v->m_y.z + dx * v->m_x.z);
			const float d3 = dz * v->m_z.w + (dy * v->m_y.w + dx * v->m_x.w);

			const unsigned int mask = ((max3 < d3) ? 1u : 0u) | ((max2 < d2) ? 2u : 0u) |
				((max1 < d1) ? 4u : 0u) | ((max0 < d0) ? 8u : 0u);

			if (mask != 0)
			{
				float best;
				unsigned int bestIdx;

				switch (mask)
				{
				case 1:
					best = d3; bestIdx = idx; break;
				case 2:
					best = d2; bestIdx = idx - 1; break;
				case 4:
					best = d1; bestIdx = idx - 2; break;
				case 8:
					best = d0; bestIdx = idx - 3; break;
				case 7:
					if (d2 < d1)
					{
						if (d3 < d1) { best = d1; bestIdx = idx - 2; }
						else { best = d3; bestIdx = idx; }
					}
					else
					{
						if (d2 <= d3) { best = d3; bestIdx = idx; }
						else { best = d2; bestIdx = idx - 1; }
					}
					break;
				case 0xb:
					if (d2 < d0)
					{
						if (d0 <= d3) { best = d3; bestIdx = idx; }
						else { best = d0; bestIdx = idx - 3; }
					}
					else
					{
						if (d2 <= d3) { best = d3; bestIdx = idx; }
						else { best = d2; bestIdx = idx - 1; }
					}
					break;
				default:
					if (d0 <= d1)
					{
						if (d2 < d1)
						{
							if (d3 < d1) { best = d1; bestIdx = idx - 2; }
							else { best = d3; bestIdx = idx; }
						}
						else
						{
							if (d2 <= d3) { best = d3; bestIdx = idx; }
							else { best = d2; bestIdx = idx - 1; }
						}
					}
					else
					{
						if (d2 < d0)
						{
							if (d0 <= d3) { best = d3; bestIdx = idx; }
							else { best = d0; bestIdx = idx - 3; }
						}
						else
						{
							if (d2 <= d3) { best = d3; bestIdx = idx; }
							else { best = d2; bestIdx = idx - 1; }
						}
					}
					break;
				}

				bestIndex = bestIdx;
				max0 = best;
				max1 = best;
				max2 = best;
				max3 = best;
			}

			v++;
			idx += 4;
		} while ((int)(idx + 1) < numVertices);
	}

	const FourVectors* elem = verts + (bestIndex >> 2);
	const int lane = bestIndex & 3;
	out.x = elem->m_x[lane];
	out.y = elem->m_y[lane];
	out.z = elem->m_z[lane];
	hkSetRaw(out.w, bestIndex | 0x3f000000);
}

// @ 0x010c1520
void hkConvexVerticesShape::convertVertexIdsToVertices(const hkUint16* ids, int numIds, hkCdVertex* out) const
{
	const FourVectors* verts = m_rotatedVertices.m_data;
	int remainder = numIds - 1;

	if (numIds >= 4)
	{
		int groups = (unsigned int)numIds >> 2;
		remainder = (numIds - 1) + groups * -4;

		do
		{
			for (int lane = 0; lane < 4; lane++)
			{
				const int id = ids[lane];
				const float* f = (const float*)(verts + (id >> 2));
				out->x = f[id & 3];
				out->y = f[(id & 3) + 4];
				out->z = f[(id & 3) + 8];
				hkSetRaw(out->w, id | 0x3f000000);
				out++;
			}
			ids += 4;
			groups--;
		} while (groups != 0);
	}

	for (int i = 0; i <= remainder; i++)
	{
		const int id = ids[i];
		const float* f = (const float*)(verts + (id >> 2));
		out->x = f[id & 3];
		out->y = f[(id & 3) + 4];
		out->z = f[(id & 3) + 8];
		hkSetRaw(out->w, id | 0x3f000000);
		out++;
	}
}

// @ 0x010c16b0
void hkAabbUtil::calcAabb(const hkTransform& transform, const hkVector4& halfExtents, const hkVector4& center,
	float extraRadius, hkAabb& out)
{
	const float* m = (const float*)&transform;
	const float hx = halfExtents.x;
	const float hy = halfExtents.y;
	const float hz = halfExtents.z;

	const float cx = center.x;
	const float cy = center.y;
	const float cz = center.z;

	// ext[i] = (|hy*m[4+i]| + |hx*m[i]|) + (|hz*m[8+i]| + extraRadius)
	float e[4];
	e[0] = (fabs(hy * m[4]) + fabs(hx * m[0])) + (fabs(hz * m[8]) + extraRadius);
	e[1] = (fabs(hy * m[5]) + fabs(hx * m[1])) + (fabs(hz * m[9]) + extraRadius);
	e[2] = (fabs(hy * m[6]) + fabs(hx * m[2])) + (fabs(hz * m[10]) + extraRadius);
	e[3] = (fabs(hy * m[7]) + fabs(hx * m[3])) + (fabs(hz * m[11]) + extraRadius);

	float cw[3];
	cw[0] = ((m[8] * cz + m[4] * cy) + m[0] * cx) + m[12];
	cw[1] = ((m[9] * cz + m[5] * cy) + m[1] * cx) + m[13];
	cw[2] = ((m[10] * cz + m[6] * cy) + m[2] * cx) + m[14];

	out.m_min.x = cw[0] - e[0];
	out.m_min.y = cw[1] - e[1];
	out.m_min.z = cw[2] - e[2];
	out.m_min.w = -e[3];
	out.m_max.x = cw[0] + e[0];
	out.m_max.y = cw[1] + e[1];
	out.m_max.z = cw[2] + e[2];
	out.m_max.w = e[3];
}

// @ 0x010c1910
void hkConvexVerticesShape::getOriginalVertices(hkArray<hkVector4>& out) const
{
	out.reserveFor(m_numVertices);
	out.m_size = m_numVertices;

	for (int i = 0; i < m_numVertices; i++)
	{
		hkVector4& v = out.m_data[i];
		v.x = ((const float*)m_rotatedVertices.m_data)[(i / 4) * 12 + (i % 4)];
		v.y = ((const float*)m_rotatedVertices.m_data)[(i / 4) * 12 + (i % 4) + 4];
		v.z = ((const float*)m_rotatedVertices.m_data)[(i / 4) * 12 + (i % 4) + 8];
		v.w = 0.0f;
	}
}
