// hkSampledHeightFieldShape::castSphere  @ 0x010e9ce0  (Havok 3.1.0, 5677 bytes)
//
//   void hkSampledHeightFieldShape::castSphere(const hkHeightFieldShape::hkSphereCastInput& input,
//                                              const hkCdBody& cdBody,
//                                              hkRayHitCollector& collector) const
//
// Identification: __thiscall with `ret 0xc` (3 args); input+0x30 (m_radius) and +0x34
// (m_maxExtraPenetration) are read past the 0x30-byte hkShapeRayCastInput, the shape's vtable
// slots 9 (+0x24 getHeightAt(int,int)) and 10 (+0x28 getTriangleFlip, hkBool via hidden pointer)
// are used, and the collector's slot 0 is addRayHit(cdBody, output).  The Havok 6 header lists the
// same members (castSphere -> private castRayInternal(input, cdBody, reportPenetratingStartPosition,
// maxExtraPenetration, collector)); castRayInternal is inlined here with report = true.
//
// The algorithm: shift the ray down by the sphere radius, scale it into grid space, then walk the
// grid cells with a 3-axis DDA (x, the triangle diagonal x+z or x-z, and z), testing the ray
// height against the height-field surface sampled on each crossed edge, and report the first
// crossing (or a penetrating start) with the triangle normal and a (z<<16 | x<<1 | tri) shape key.
// A near-vertical ray is handled separately by sampling the single cell under the ray.
//
// Ghidra could not recover this function (all scalar state is on the x87 stack); the source was
// written from the disassembly, so x87 compares use the original's NaN behaviour where it matters.

#include "types.h"
extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(__rdtsc)

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long index, void* value);

typedef float hkReal;
typedef uint32_t hkUint32;

// HK_REAL_MAX in this build is 3.40282e+38f == 0x7f7fffee (not FLT_MAX).
#define HK_REAL_MAX 3.40282e+38f

// ---- Havok monitor stream timers (TLS slot 0x016e42a4 = write pointer, 0x016e42a8 = end) ---------
extern unsigned long g_hkMonitorStreamCurrentTls;   // 0x016e42a4
extern unsigned long g_hkMonitorStreamEndTls;       // 0x016e42a8
extern const char hkMonitorEndTag[];                // 0x0149cc34 "Et"

struct hkMonitorCommand
{
	const char* m_commandAndMonitor;
	hkUint32 m_time0;
	hkUint32 m_time1;
};

#define HK_TIMER_COMMAND(name) do { \
	void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
	if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
		hkMonitorCommand* c_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
		c_->m_commandAndMonitor = name; \
		c_->m_time0 = (hkUint32)__rdtsc(); \
		TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_BEGIN(name) HK_TIMER_COMMAND("Tt" name)
#define HK_TIMER_END() HK_TIMER_COMMAND(hkMonitorEndTag)
#define HK_TIMER_END_AND_RETURN() do { HK_TIMER_END(); return; } while (0)

#include <math.h>

// ---- math ----------------------------------------------------------------------------------------
namespace hkMath
{
	template <typename T> T max2(T a, T b);       // 0x01081500 ??$max2@M@hkMath@@YAMMM@Z (out of line)

	inline hkReal fabs(hkReal r) { return (hkReal)::fabs((double)r); }
	inline hkReal sqrtInverse(hkReal r) { return (hkReal)(1.0 / ::sqrt((double)r)); }

	// round-to-nearest float -> int (x87 fistp)
	inline int hkToIntFast(hkReal r)
	{
		int i;
		__asm { fld r }
		__asm { fistp i }
		return i;
	}
}

__declspec(align(16)) class hkVector4
{
public:
	hkReal x, y, z, w;

	__forceinline void set(hkReal a, hkReal b, hkReal c, hkReal d) { x = a; y = b; z = c; w = d; }
	__forceinline void mul4(const hkVector4& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; }
	__forceinline hkReal lengthSquared3() const { return x * x + y * y + z * z; }
	__forceinline void normalize3()
	{
		// the squared length and its reciprocal square root stay on the x87 stack
		double lenSq = (double)x * x + (double)y * y + (double)z * z;
		double invLen = (lenSq == 0.0) ? 0.0 : 1.0 / ::sqrt(lenSq);
		x = (hkReal)(x * invLen); y = (hkReal)(y * invLen); z = (hkReal)(z * invLen); w = (hkReal)(w * invLen);
	}
};

// Float -> int through the 3*2^16 magic constant: the integer part sits in the mantissa bits 6..21.
union hkFloatBits { hkReal f; hkUint32 i; };
static inline int hkFloatToInt16(hkReal magicAdded)
{
	hkFloatBits u;
	u.f = magicAdded;
	return (int16_t)(u.i >> 6);
}

class hkBool
{
public:
	hkBool() {}
	hkBool(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
	char m_bool;
};

// ---- collision structures ------------------------------------------------------------------------
class hkShape;
class hkCdBody
{
public:
	const hkShape* m_shape;      // +0
	hkUint32 m_shapeKey;         // +4
	const void* m_motion;        // +8
	const hkCdBody* m_parent;    // +0xc
};

struct hkShapeRayCastInput
{
	hkVector4 m_from;                           // +0
	hkVector4 m_to;                             // +0x10
	hkUint32 m_filterInfo;                      // +0x20
	const void* m_rayShapeCollectionFilter;     // +0x24
};                                              // size 0x30 (16-aligned)

struct hkShapeRayCastOutput
{
	hkVector4 m_normal;      // +0
	hkUint32 m_extraInfo;    // +0x10 (shape key)
	hkReal m_hitFraction;    // +0x14
	hkShapeRayCastOutput() : m_hitFraction(1.0f) {}
};

class hkRayHitCollector
{
public:
	virtual void addRayHit(const hkCdBody& cdBody, const hkShapeRayCastOutput& hitInfo) = 0;   // 0
	hkReal m_earlyOutHitFraction;                                                             // +4
};

class hkHeightFieldShape
{
public:
	struct hkSphereCastInput : public hkShapeRayCastInput
	{
		hkReal m_radius;                  // +0x30
		hkReal m_maxExtraPenetration;     // +0x34
	};
};

class hkReferencedObject
{
public:
	virtual ~hkReferencedObject();                                                               // 0
	virtual void slot1();                                                                        // 1
	int16_t m_memSizeAndFlags;                      // +4
	int16_t m_referenceCount;                       // +6
};

class hkShape : public hkReferencedObject
{
public:
	hkUint32 m_userData;                            // +8
};

class hkSampledHeightFieldShape : public hkShape
{
public:
	virtual int getType() const;                                                                 // 2
	virtual void getAabb(const void* localToWorld, hkReal tolerance, void* out) const;           // 3
	virtual hkReal getMaximumProjection(const hkVector4& direction) const;                       // 4
	virtual hkBool castRay(const hkShapeRayCastInput& input, hkShapeRayCastOutput& output) const; // 5
	virtual void castRayWithCollector(const hkShapeRayCastInput& input, const hkCdBody& cdBody,
	                                  hkRayHitCollector& collector) const;                       // 6
	virtual void collideSpheres(const void* input, void* outputArray) const;                     // 7
	virtual void castSphere(const hkHeightFieldShape::hkSphereCastInput& input, const hkCdBody& cdBody,
	                        hkRayHitCollector& collector) const;                                 // 8
	virtual hkReal getHeightAt(int x, int z) const;                                              // 9  (+0x24)
	virtual hkBool getTriangleFlip() const;                                                      // 10 (+0x28)

	int m_xRes;                                     // +0xc
	int m_zRes;                                     // +0x10
	hkReal m_heightCenter;                          // +0x14
	hkVector4 m_intToFloatScale;                    // +0x20
	hkVector4 m_floatToIntScale;                    // +0x30
	hkVector4 m_floatToIntOffsetFloorCorrected;     // +0x40
	hkVector4 m_extents;                            // +0x50

private:
	__forceinline void castRayInternal(const hkShapeRayCastInput& input, const hkCdBody& cdBody,
	                                   bool reportPenetratingStartPosition, hkReal maxExtraPenetration,
	                                   hkRayHitCollector& collector) const;
};

// Interpolated height of the surface along the edge the ray just crossed.
#define LERP_HEIGHT(h1, h0, w) (((h1) - (h0)) * (w) + (h0))

__forceinline void hkSampledHeightFieldShape::castRayInternal(const hkShapeRayCastInput& input,
	const hkCdBody& cdBody, bool reportPenetratingStartPosition, hkReal maxExtraPenetration,
	hkRayHitCollector& collector) const
{
	bool reportPenetrating = reportPenetratingStartPosition;

	HK_TIMER_BEGIN("rcHeightFild");

	// Start cell: (from + offset) * floatToIntScale, converted with the magic-number trick.
	hkVector4 ssFrom;
	ssFrom.x = (input.m_from.x + m_floatToIntOffsetFloorCorrected.x) * m_floatToIntScale.x;
	ssFrom.y = (input.m_from.y + m_floatToIntOffsetFloorCorrected.y) * m_floatToIntScale.y;
	ssFrom.z = (input.m_from.z + m_floatToIntOffsetFloorCorrected.z) * m_floatToIntScale.z;
	ssFrom.w = (input.m_from.w + m_floatToIntOffsetFloorCorrected.w) * m_floatToIntScale.w;
	hkVector4 ssFromMagic;
	ssFromMagic.x = ssFrom.x + 196608.0f;
	ssFromMagic.y = ssFrom.y + 196608.0f;
	ssFromMagic.z = ssFrom.z + 196608.0f;
	ssFromMagic.w = ssFrom.w + 196608.0f;

	// cell[0] = x, cell[1] = triangle diagonal (x+z or x-z), cell[2] = z.
	// cell[1] is only assigned after clipping; the axis-1 setup below reads it like the original.
	int cell[3];
	cell[0] = hkFloatToInt16(ssFromMagic.x);
	cell[2] = hkFloatToInt16(ssFromMagic.z);

	// Ray end points in grid space, laid out (x, diagonal, z, height).
	hkVector4 from;
	hkVector4 to;
	from.x = input.m_from.x * m_floatToIntScale.x;
	from.y = input.m_from.y * m_floatToIntScale.y;
	from.z = input.m_from.z * m_floatToIntScale.z;
	to.x = input.m_to.x * m_floatToIntScale.x;
	to.y = input.m_to.y * m_floatToIntScale.y;
	to.z = input.m_to.z * m_floatToIntScale.z;

	hkBool flip = getTriangleFlip();
	from.w = from.y;
	to.w = to.y;
	if (!flip)
	{
		from.y = from.x + from.z;
		to.y = to.x + to.z;
	}
	else
	{
		from.y = from.x - from.z;
		to.y = to.x - to.z;
	}

	// ---- DDA setup per axis: dt = |1/delta|, step = +-1, tNext = parameter of the next crossing ----
	hkReal dt[3];
	hkReal tNext[3];
	int step[3];
	hkReal invDeltaX;
	hkReal invDeltaZ;
	hkReal absDeltaX;
	hkReal absDeltaZ;

	{
		hkReal delta = to.x - from.x;
		absDeltaX = hkMath::fabs(delta);
		if (absDeltaX < 3.0517578e-05f)
		{
			dt[0] = 0.0f;
			step[0] = -1;
			tNext[0] = HK_REAL_MAX;
		}
		else
		{
			invDeltaX = 1.0f / delta;
			if (delta < 0.0f)
			{
				step[0] = -1;
				dt[0] = -invDeltaX;
			}
			else
			{
				cell[0]++;
				dt[0] = invDeltaX;
				step[0] = 1;
			}
			tNext[0] = ((hkReal)cell[0] - from.x) * invDeltaX;
		}
	}
	{
		hkReal delta = to.y - from.y;
		if (hkMath::fabs(delta) < 3.0517578e-05f)
		{
			dt[1] = 0.0f;
			step[1] = -1;
			tNext[1] = HK_REAL_MAX;
		}
		else
		{
			hkReal invDelta = 1.0f / delta;
			if (delta < 0.0f)
			{
				step[1] = -1;
				dt[1] = -invDelta;
			}
			else
			{
				cell[1]++;
				dt[1] = invDelta;
				step[1] = 1;
			}
			tNext[1] = ((hkReal)cell[1] - from.y) * invDelta;
		}
	}
	{
		hkReal delta = to.z - from.z;
		absDeltaZ = hkMath::fabs(delta);
		if (absDeltaZ < 3.0517578e-05f)
		{
			dt[2] = 0.0f;
			step[2] = -1;
			tNext[2] = HK_REAL_MAX;
		}
		else
		{
			invDeltaZ = 1.0f / delta;
			if (delta < 0.0f)
			{
				step[2] = -1;
				dt[2] = -invDeltaZ;
			}
			else
			{
				cell[2]++;
				dt[2] = invDeltaZ;
				step[2] = 1;
			}
			tNext[2] = ((hkReal)cell[2] - from.z) * invDeltaZ;
		}
	}

	if (dt[2] + dt[0] == 0.0f || dt[1] + dt[0] == 0.0f || dt[1] + dt[2] == 0.0f)
	{
		// ---- (near) vertical ray: test the single cell below the start point ----
		if ((unsigned)cell[0] >= (unsigned)(m_xRes - 1) || (unsigned)cell[2] >= (unsigned)(m_zRes - 1))
			HK_TIMER_END_AND_RETURN();

		hkReal subZ = from.z - (hkReal)cell[2];
		hkShapeRayCastOutput output;
		output.m_normal.set(1.0f, 1.0f, 1.0f, 1.0f);
		hkReal subX = from.x - (hkReal)cell[0];

		const int x = cell[0];
		const int z = cell[2];
		hkReal height;
		hkReal dhdx;
		hkReal dhdz;
		int triangle;
		if (getTriangleFlip())
		{
			hkReal h00 = getHeightAt(x, z);
			hkReal h11 = getHeightAt(x + 1, z + 1);
			if (subX > subZ)
			{
				hkReal h10 = getHeightAt(x + 1, z);
				dhdx = h10 - h00;
				dhdz = h11 - h10;
				height = dhdx * subX + dhdz * subZ + h00;
				triangle = 1;
			}
			else
			{
				hkReal h01 = getHeightAt(x, z + 1);
				dhdx = h11 - h01;
				dhdz = h01 - h00;
				height = dhdx * subX + dhdz * subZ + h00;
				triangle = 0;
			}
		}
		else
		{
			hkReal h10 = getHeightAt(x + 1, z);
			hkReal h01 = getHeightAt(x, z + 1);
			if (subX + subZ > 1.0f)
			{
				hkReal h11 = getHeightAt(x + 1, z + 1);
				dhdx = h11 - h01;
				dhdz = h11 - h10;
				height = (subX - 1.0f) * dhdx + dhdz * subZ + h10;
				triangle = 1;
			}
			else
			{
				hkReal h00 = getHeightAt(x, z);
				dhdx = h10 - h00;
				dhdz = h01 - h00;
				height = dhdx * subX + dhdz * subZ + h00;
				triangle = 0;
			}
		}
		output.m_normal.x = -dhdx;
		output.m_normal.z = -dhdz;

		hkReal startDist = from.w - height;
		hkReal endDist = to.w - height;
		if (endDist > startDist)
			HK_TIMER_END_AND_RETURN();

		hkReal hitFraction;
		if (startDist < 0.0f)
		{
			if (startDist - maxExtraPenetration < endDist)
				HK_TIMER_END_AND_RETURN();
			hitFraction = 0.0f;
		}
		else
		{
			if (endDist >= 0.0f)
				HK_TIMER_END_AND_RETURN();
			hitFraction = startDist / (startDist - endDist);
		}

		if (hitFraction < collector.m_earlyOutHitFraction)
		{
			output.m_normal.mul4(m_floatToIntScale);
			output.m_normal.normalize3();
			output.m_extraInfo = ((z << 15) + x) * 2 + triangle;
			output.m_hitFraction = hitFraction;
			collector.addRayHit(cdBody, output);
		}
		HK_TIMER_END_AND_RETURN();
	}

	{
		// ---- clip the ray against the x range, then the z range ----
		hkVector4 cur = from;
		const int startX = cell[0];

		bool clip = false;
		hkReal t;
		if (step[0] > 0)
		{
			if (cell[0] <= 0)
			{
				if (to.x < 0.0f)
					HK_TIMER_END_AND_RETURN();
				t = -(from.x * dt[0]);
				cell[0] = 1;
				clip = true;
			}
		}
		else if (cell[0] > m_xRes - 2)
		{
			hkReal limit = (hkReal)(m_xRes - 1);
			if (to.x > limit)
				HK_TIMER_END_AND_RETURN();
			t = (from.x - limit) * dt[0];
			cell[0] = m_xRes - 2;
			clip = true;
		}
		if (clip)
		{
			tNext[0] = dt[0] + t;
			hkReal s = 1.0f - t;
			cur.y = s * from.y + t * to.y;
			cur.z = t * to.z + s * from.z;
			cell[2] = cell[2] + hkMath::hkToIntFast(t * absDeltaZ) * step[2] - 2;
			while ((hkReal)cell[2] <= cur.z)
				cell[2]++;
			cell[2] += step[2] >> 1;
			tNext[2] = ((hkReal)cell[2] - from.z) * invDeltaZ;
		}

		clip = false;
		if (step[2] > 0)
		{
			if (cell[2] <= 0)
			{
				if (to.z < 0.0f)
					HK_TIMER_END_AND_RETURN();
				t = -(dt[2] * from.z);
				cell[2] = 1;
				clip = true;
			}
		}
		else if (cell[2] > m_zRes - 2)
		{
			hkReal limit = (hkReal)(m_zRes - 1);
			if (to.z > limit)
				HK_TIMER_END_AND_RETURN();
			t = (from.z - limit) * dt[2];
			cell[2] = m_zRes - 2;
			clip = true;
		}
		if (clip)
		{
			tNext[2] = dt[2] + t;
			hkReal s = 1.0f - t;
			cur.x = from.x * s + to.x * t;
			cur.y = t * to.y + s * from.y;
			cell[0] = hkMath::hkToIntFast(t * absDeltaX) * step[0] + startX - 2;
			while ((hkReal)cell[0] <= cur.x)
				cell[0]++;
			cell[0] += step[0] >> 1;
			tNext[0] = ((hkReal)cell[0] - from.x) * invDeltaX;
		}

		if ((unsigned)cell[0] >= (unsigned)m_xRes)
			HK_TIMER_END_AND_RETURN();
		if ((unsigned)(cell[0] - step[0]) >= (unsigned)m_xRes)
			HK_TIMER_END_AND_RETURN();

		// ---- diagonal axis: does the ray cross the cell diagonals (diag) or walk along them? ----
		bool diag = (((step[2] ^ step[0]) >= 0) != (flip != 0));
		if (dt[1] == 0.0f)
			diag = false;

		int half = 2;
		if (!flip)
			cell[1] = cell[0] + cell[2];
		else
			cell[1] = cell[0] - cell[2];

		hkReal diagOffset = cur.y - (hkReal)cell[1];
		if (diag)
		{
			if (hkMath::fabs(diagOffset) > 1.0f)
				cell[1] -= step[1];
			else
				half = 0;
		}
		else if ((hkReal)step[1] * diagOffset > 0.0f)
		{
			half = 0;
			cell[1] += step[1];
		}

		if (dt[1] == 0.0f)
			tNext[1] = HK_REAL_MAX;
		else
			tNext[1] = ((hkReal)cell[1] - from.y) * (hkReal)step[1] * dt[1];

		// ---- pick the axis crossed last before the (clipped) start ----
		hkReal prev0 = (dt[0] == 0.0f) ? -HK_REAL_MAX : tNext[0] - dt[0];
		hkReal prev1 = (dt[1] == 0.0f) ? -HK_REAL_MAX : tNext[1] - dt[1];
		hkReal prev2 = (dt[2] == 0.0f) ? -HK_REAL_MAX : tNext[2] - dt[2];
		int axis;
		if (diag)
		{
			if (half == 0)
				axis = 1;
			else if (!(prev0 > prev2))
				axis = 2;
			else
				axis = 0;
		}
		else if (absDeltaX < absDeltaZ)
		{
			if (half != 0)
				axis = 2;
			else if (!(prev0 > prev1))
				axis = 1;
			else
				axis = 0;
		}
		else
		{
			if (half != 0)
				axis = 0;
			else if (prev1 > prev2)
				axis = 1;
			else
				axis = 2;
		}
		tNext[axis] -= dt[axis];
		cell[axis] -= step[axis];

		// ---- walk ----
		hkReal lastSurfaceHeight = HK_REAL_MAX;
		hkReal lastRayHeight = 0.0f;
		hkReal lastT = -1.0f;

		while ((unsigned)cell[0] < (unsigned)m_xRes)
		{
			if ((unsigned)cell[2] >= (unsigned)m_zRes)
				break;
			if (lastT > collector.m_earlyOutHitFraction)
				HK_TIMER_END_AND_RETURN();

			hkReal* tNextAxis = &tNext[axis];
			const hkReal t = *tNextAxis;
			const int x = cell[0];
			const int z = cell[2];
			const int xPrev = x - step[0];

			hkReal s = 1.0f - t;
			cur.x = to.x * t + s * from.x;
			cur.z = t * to.z + s * from.z;
			cur.w = t * to.w + s * from.w;

			hkReal surfaceHeight;
			if (axis == 0)
			{
				hkReal h1 = getHeightAt(x, z - step[2]);
				hkReal h0 = getHeightAt(x, z);
				surfaceHeight = LERP_HEIGHT(h1, h0, hkMath::fabs(cur.z - (hkReal)z));
			}
			else if (axis == 2)
			{
				hkReal h1 = getHeightAt(xPrev, z);
				hkReal h0 = getHeightAt(x, z);
				surfaceHeight = LERP_HEIGHT(h1, h0, hkMath::fabs(cur.x - (hkReal)x));
			}
			else
			{
				int zA = z;
				int zB;
				hkReal w = hkMath::fabs(cur.x - (hkReal)x);
				if (diag)
				{
					zA = z - step[2];
					zB = z;
				}
				else
				{
					zB = z - step[2];
				}
				hkReal h1 = getHeightAt(xPrev, zB);
				hkReal h0 = getHeightAt(x, zA);
				surfaceHeight = LERP_HEIGHT(h1, h0, w);
			}

			if (!(cur.w >= surfaceHeight))
			{
				hkReal hitFraction;
				hkReal endDist = cur.w - surfaceHeight;
				if (reportPenetrating)
				{
					hkReal startDist = lastRayHeight - lastSurfaceHeight;
					if (startDist - (t - lastT) * maxExtraPenetration <= endDist)
						goto noHit;
					if (startDist <= 0.0f)
					{
						hitFraction = hkMath::max2<hkReal>(0.0f, lastT);
						goto haveHit;
					}
				}
				else if (lastRayHeight < lastSurfaceHeight)
				{
					goto noHit;
				}

				if (!(lastT >= 0.0f))
				{
					hkReal f = t / (t - lastT);
					hkReal startDist = from.w - ((1.0f - f) * surfaceHeight + f * lastSurfaceHeight);
					if (startDist < 0.0f)
					{
						if (!reportPenetrating)
							goto noHit;
						startDist = 0.0f;
					}
					hitFraction = startDist / (startDist - endDist) * t;
				}
				else
				{
					hkReal startDist = lastRayHeight - lastSurfaceHeight;
					hitFraction = (t - lastT) * (startDist / (startDist - endDist)) + lastT;
				}

			haveHit:
				lastSurfaceHeight = surfaceHeight;
				lastRayHeight = cur.w;
				lastT = t;
				if (hitFraction > collector.m_earlyOutHitFraction)
					HK_TIMER_END_AND_RETURN();

				{
					// triangle normal from the three corner heights of the crossed triangle
					const int zPrev = z - step[2];
					hkShapeRayCastOutput output;
					output.m_normal.w = 0.0f;
					output.m_normal.y = 1.0f;
					hkReal gx;
					hkReal gz;
					bool upper;
					if (diag)
					{
						hkReal hA = getHeightAt(x, zPrev);
						hkReal hB = getHeightAt(xPrev, z);
						if (axis == 1)
						{
							hkReal hC = getHeightAt(xPrev, zPrev);
							gx = hC - hA;
							gz = hC - hB;
							upper = zPrev > z;
						}
						else
						{
							hkReal hC = getHeightAt(x, z);
							gx = hB - hC;
							gz = hA - hC;
							upper = z > zPrev;
						}
					}
					else
					{
						hkReal hB = getHeightAt(xPrev, zPrev);
						hkReal hA = getHeightAt(x, z);
						if (axis == 0 || (axis == 1 && absDeltaX < absDeltaZ))
						{
							hkReal hC = getHeightAt(x, zPrev);
							gx = hB - hC;
							gz = hC - hA;
							upper = zPrev > z;
						}
						else
						{
							hkReal hC = getHeightAt(xPrev, z);
							gx = hC - hA;
							gz = hB - hC;
							upper = z > zPrev;
						}
					}
					int triangle = (upper ? 1 : 0) ^ ((flip != 0) ? 1 : 0);
					output.m_normal.x = (hkReal)step[0] * gx;
					output.m_normal.z = (hkReal)step[2] * gz;
					output.m_normal.mul4(m_floatToIntScale);
					output.m_normal.normalize3();
					output.m_extraInfo =
						(((z - (step[2] >> 1) - 1) << 15) - (step[0] >> 1) + x) * 2 + triangle - 2;
					output.m_hitFraction = hitFraction;
					collector.addRayHit(cdBody, output);
				}
				if (reportPenetrating)
					reportPenetrating = false;
				goto advance;
			}
		noHit:
			lastSurfaceHeight = surfaceHeight;
			lastRayHeight = cur.w;
			lastT = t;

		advance:
			cell[axis] += step[axis];
			*tNextAxis += dt[axis];
			half ^= 2;

			// ---- next axis: the nearest crossing, alternating with the diagonal ----
			if (diag)
			{
				if (half == 0)
					axis = 1;
				else if (!(tNext[0] < tNext[2]))
					axis = 2;
				else
					axis = 0;
			}
			else if (absDeltaX < absDeltaZ)
			{
				if (half != 0)
					axis = 2;
				else if (!(tNext[0] < tNext[1]))
					axis = 1;
				else
					axis = 0;
			}
			else
			{
				if (half != 0)
					axis = 0;
				else
				{
					axis = 1;
					if (!(tNext[1] < tNext[2]))
						axis = 2;
				}
			}
		}
		HK_TIMER_END_AND_RETURN();
	}
}

// @ 0x010e9ce0
void hkSampledHeightFieldShape::castSphere(const hkHeightFieldShape::hkSphereCastInput& input,
	const hkCdBody& cdBody, hkRayHitCollector& collector) const
{
	hkReal radius = input.m_radius;
	if (m_intToFloatScale.y > 0.0f)
		radius = -radius;

	hkShapeRayCastInput rayInput = input;
	rayInput.m_from.y += radius;
	rayInput.m_to.y += radius;

	castRayInternal(rayInput, cdBody, true, input.m_maxExtraPenetration, collector);
}
