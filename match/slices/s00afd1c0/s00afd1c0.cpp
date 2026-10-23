// Slice s00afd1c0 -- SP::cActionCircle slot generators (spiral / ring / radial-fan packings of the
// 0x18-byte tSlot records kept in the vector at +0x50).
//
//  0x00afd1c0  cActionCircle::SetSpiralSlots(float radius, int count)
//  0x00afd6d0  cActionCircle::SetRingSlots(float radius, float density, int count)
//  0x00afdc00  cActionCircle::SetFanSlots(float radius, float spread, int count)
//
// All three clear the slot vector, mark the packing mode in mPacking (+0x24), store the caller's
// radius in mSlotRadius (+0x10) and then append one slot per generated point.  With mbRelative
// (+0x28) clear the points are wrapped onto the planet surface through
// SP::PlanetModel()->DirectionToSurfacePosition(); with it set the raw points are stored as-is.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <math.h>

namespace SP {

struct cSPVector3 { float x, y, z; };
struct cSPQuaternion { float x, y, z, w; };

class cGameData {
 public:
	virtual void dtor();      // +0
	virtual int AddRef();     // +4
	virtual int Release();    // +8
};

class cInteractionAgent {
 public:
	virtual void dtor();
	virtual int AddRef();
	virtual int Release();
};

// EA::IRefCounted / EA::AutoRefCount<cGameData>, flattened to the one pointer the slots hold.
class cGameDataRef {
 public:
	cGameData* mpObject;                    // +0
	void AddRef() { if (mpObject) mpObject->AddRef(); }
	void Release() { if (mpObject) mpObject->Release(); }
};

class cActionCircle {
 public:
	struct tSlot {                          // 0x18 bytes
		bool mOccupied;                     // +0x0
		char _pad0[3];
		cGameDataRef mReservingNoun;        // +0x4
		unsigned int mReservingId;          // +0x8
		cSPVector3 mPos;                    // +0xc
	};

	struct SlotVector {
		tSlot* mpBegin;                     // +0
		tSlot* mpEnd;                       // +4
		tSlot* mpCapacity;                  // +8

		void Erase(tSlot* first, tSlot* last);              // 0x00afc0d0
		void InsertAtEnd(tSlot* where, const tSlot* value); // 0x00afc150
		void Reserve(int count);                            // 0x00afbe80

		void push_back(const tSlot& value) {
			tSlot* end = mpEnd;
			if (end != mpCapacity) {
				mpEnd = end + 1;
				if (end) {
					end->mOccupied = false;
					end->mReservingNoun.mpObject = 0;
					end->mReservingId = 0;
					end->mPos = value.mPos;
				}
			}
			else {
				InsertAtEnd(end, &value);
			}
		}
	};

	cSPVector3 mFacing;                     // +0x00
	float mRadius;                          // +0x0c
	float mSlotRadius;                      // +0x10
	cSPVector3 mCenter;                     // +0x14
	float mAltitude;                        // +0x20
	int mPacking;                           // +0x24
	bool mbRelative;                        // +0x28
	char _pad29[0x50 - 0x29];
	SlotVector mSlots;                      // +0x50

	void SetSpiralSlots(float radius, int count);                    // 0x00afd1c0
	void SetRingSlots(float radius, float density, int count);       // 0x00afd6d0
	void SetFanSlots(float radius, float spread, int count);         // 0x00afdc00

	// Appends one slot holding pos (the vector's push_back plus the temporary's release).
	void AddSlot(const cSPVector3& pos) {
		tSlot slot;
		slot.mOccupied = false;
		slot.mReservingNoun.mpObject = 0;
		slot.mReservingId = 0;
		slot.mPos = pos;
		mSlots.push_back(slot);
		slot.mReservingNoun.Release();
	}
};

class cPlanetModel {
 public:
	cSPVector3 DirectionToSurfacePosition(const cSPVector3& dir);    // 0x00b815a0
};

cPlanetModel* PlanetModel();                                        // 0x00b3d350

}  // namespace SP

using SP::cSPVector3;
using SP::cSPQuaternion;
using SP::cActionCircle;

// Globals written at startup: the pi constant and the default axis / center vectors used when the
// circle is relative to its owner.
extern float g_PI;                  // 0x0167af14
extern cSPVector3 g_defaultCenter;  // 0x0167aec4
extern cSPVector3 g_defaultAxis;    // 0x0167af18
extern cSPVector3 g_defaultAxisAlt; // 0x0167af24

static const float kNormEps = 1.0e-08f;   // 0x013ec4b8
static const float kTwo = 2.0f;           // 0x01470f1c
static const float kHalf = 0.5f;          // 0x01471064
static const float kSpiralStep = 0.41666666f;  // 0x0145c464 = 5/12
static const float kDenseLimit = 0.95f;   // 0x013f7344

// Rotates v by the quaternion q (x, y, z, w) -- the source spells the matrix out per component.
static cSPVector3 RotateByQuat(const cSPQuaternion& q, const cSPVector3& v)
{
	const float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
	const float xy = q.x * q.y, xz = q.x * q.z, yz = q.y * q.z;
	const float wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;

	cSPVector3 r;
	r.x = ((1.0f - (yy + zz) * kTwo) * v.x + (xy - wz) * kTwo * v.y) + (xz + wy) * kTwo * v.z;
	r.y = ((xy + wz) * kTwo * v.x + (1.0f - (xx + zz) * kTwo) * v.y) + (yz - wx) * kTwo * v.z;
	r.z = ((xz - wy) * kTwo * v.x + (yz + wx) * kTwo * v.y) + (1.0f - (xx + yy) * kTwo) * v.z;
	return r;
}

// --------------------------------------------------------------------------------------- 0x00afd1c0
// Spiral packing (mPacking 7): one slot at the centre, then rows of 2, 3, 4, ... points walking out
// along the step direction, each row advanced sideways by the tangent.
// @ 0x00afd1c0
void cActionCircle::SetSpiralSlots(float radius, int count)
{
	mPacking = 7;
	mSlotRadius = radius;
	mSlots.Erase(mSlots.mpBegin, mSlots.mpEnd);

	const float twoRadius = radius * kTwo;

	// Axis the facing vector is turned about, and the cross product used for the row step.
	cSPVector3 axis;
	if (!mbRelative) {
		const float inv = 1.0f / sqrtf(((mFacing.x * mFacing.x + mFacing.y * mFacing.y) +
		                                mFacing.z * mFacing.z) + kNormEps);
		axis.x = mFacing.x * inv;
		axis.y = mFacing.y * inv;
		axis.z = mFacing.z * inv;
	}
	else {
		axis = g_defaultAxis;
	}

	const float crossX = axis.y * mFacing.z - axis.z * mFacing.y;
	const float crossY = axis.z * mFacing.x - axis.x * mFacing.z;
	const float crossZ = axis.x * mFacing.y - axis.y * mFacing.x;

	cSPVector3 first = mbRelative ? g_defaultCenter : mCenter;

	const float sinStep = sinf(g_PI * kSpiralStep);
	const float cosStep = cosf(g_PI * kSpiralStep);

	cSPVector3 step, tangent;
	step.x = (mFacing.x * cosStep + crossX * sinStep) * twoRadius;
	step.y = (mFacing.y * cosStep + crossY * sinStep) * twoRadius;
	step.z = (mFacing.z * cosStep + crossZ * sinStep) * twoRadius;
	tangent.x = -crossX * twoRadius;
	tangent.y = -crossY * twoRadius;
	tangent.z = -crossZ * twoRadius;

	AddSlot(first);

	int remaining = count - 1;
	int rowLength = 2;
	while (remaining > 0) {
		cSPVector3 rowStart;
		rowStart.x = first.x + step.x;
		rowStart.y = first.y + step.y;
		rowStart.z = first.z + step.z;
		first = rowStart;

		cSPVector3 p = rowStart;
		int left = rowLength;
		if (left > 0) {
			do {
				cSPVector3 pos;
				if (!mbRelative) {
					const float altitude = mAltitude;
					const float inv = 1.0f / sqrtf(((p.y * p.y + p.z * p.z) +
					                                p.x * p.x) + kNormEps);
					cSPVector3 dir;
					dir.x = p.x * inv * altitude;
					dir.y = p.y * inv * altitude;
					dir.z = p.z * inv * altitude;
					const cSPVector3 surf = SP::PlanetModel()->DirectionToSurfacePosition(p);
					pos.x = surf.x + dir.x;
					pos.y = surf.y + dir.y;
					pos.z = surf.z + dir.z;
				}
				else {
					pos = p;
				}
				AddSlot(pos);

				p.x = p.x + tangent.x;
				p.y = p.y + tangent.y;
				p.z = p.z + tangent.z;
				--left;
			} while (left != 0);
		}

		remaining -= rowLength;
		++rowLength;
	}

	const cSPVector3& last = (mSlots.mpEnd - 1)->mPos;
	const float dx = last.x - first.x;
	const float dy = last.y - first.y;
	const float dz = last.z - first.z;
	mRadius = sqrtf((dz * dz + dy * dy) + dx * dx) + radius;
}

// --------------------------------------------------------------------------------------- 0x00afd6d0
// Ring packing (mPacking 1): count slots evenly spread around the centre, the facing vector rotated
// about the normalised centre by (i * step + start) / 2.
// @ 0x00afd6d0
void cActionCircle::SetRingSlots(float radius, float density, int count)
{
	mPacking = 1;
	mSlotRadius = radius;
	mSlots.Erase(mSlots.mpBegin, mSlots.mpEnd);

	const float slots = (count > 0) ? (float)count : 1.0f;
	float start = 0.0f;
	float step = 0.0f;
	if (count > 1) {
		start = (g_PI * density) * -kHalf;
		if (density >= kDenseLimit) {
			step = (1.0f / slots) * g_PI;
		}
		else {
			step = (1.0f / (slots - 1.0f)) * (g_PI * density);
		}
	}

	const cSPVector3 center = mbRelative ? g_defaultCenter : mCenter;

	cSPVector3 axis;
	if (!mbRelative) {
		const float inv = 1.0f / sqrtf(((mCenter.z * mCenter.z + mCenter.y * mCenter.y) +
		                                mCenter.x * mCenter.x) + kNormEps);
		axis.x = mCenter.x * inv;
		axis.y = mCenter.y * inv;
		axis.z = mCenter.z * inv;
	}
	else {
		axis = g_defaultAxis;
	}

	float i = 0.0f;
	while (i < slots) {
		const float angle = (i * step + start) * kHalf;
		const float s = sinf(angle);
		const float c = cosf(angle);

		cSPVector3 negFacing;
		negFacing.x = -mFacing.x;
		negFacing.y = -mFacing.y;
		negFacing.z = -mFacing.z;

		cSPQuaternion q;
		q.x = axis.x * s;
		q.y = axis.y * s;
		q.z = axis.z * s;
		q.w = c;

		const cSPVector3 rotated = RotateByQuat(q, negFacing);
		cSPVector3 p;
		p.x = rotated.x * mRadius + center.x;
		p.y = rotated.y * mRadius + center.y;
		p.z = rotated.z * mRadius + center.z;

		cSPVector3 pos;
		if (!mbRelative) {
			const float altitude = mAltitude;
			const float inv = 1.0f / sqrtf(((p.y * p.y + p.z * p.z) + p.x * p.x) + kNormEps);
			cSPVector3 dir;
			dir.x = p.x * inv * altitude;
			dir.y = p.y * inv * altitude;
			dir.z = p.z * inv * altitude;
			const cSPVector3 surf = SP::PlanetModel()->DirectionToSurfacePosition(p);
			pos.x = surf.x + dir.x;
			pos.y = surf.y + dir.y;
			pos.z = surf.z + dir.z;
		}
		else {
			pos = p;
		}
		AddSlot(pos);

		i = i + 1.0f;
	}
}

// --------------------------------------------------------------------------------------- 0x00afdc00
// Radial fan (mPacking 2): the slot count is the circular packing that fits the radius, capped by
// count; the slots walk from the facing vector towards the axis by PI / slots each.
// @ 0x00afdc00
void cActionCircle::SetFanSlots(float radius, float spread, int count)
{
	const float total = radius + spread;
	mPacking = 2;
	mRadius = total;
	mSlotRadius = radius;

	const float halfAngle = asin(radius / total);
	const float sides = g_PI / (halfAngle + halfAngle);
	int numSides = (int)sides;
	if (sides < (float)numSides) {
		numSides = numSides - 1;
	}
	if (count > 0 && count < numSides) {
		numSides = count;
	}

	const float step = g_PI / (float)numSides;

	cSPVector3 axis;
	if (!mbRelative) {
		const float inv = 1.0f / sqrtf(((mCenter.z * mCenter.z + mCenter.y * mCenter.y) +
		                                mCenter.x * mCenter.x) + kNormEps);
		const float cx = mCenter.x * inv;
		const float cy = mCenter.y * inv;
		const float cz = mCenter.z * inv;
		axis.x = mFacing.z * cy - mFacing.y * cz;
		axis.y = mFacing.x * cz - mFacing.z * cx;
		axis.z = mFacing.y * cx - mFacing.x * cy;
	}
	else {
		axis = g_defaultAxisAlt;
	}

	mSlots.Erase(mSlots.mpBegin, mSlots.mpEnd);
	mSlots.Reserve(numSides);

	float angle = 0.0f;
	for (int n = numSides; n > 0; --n) {
		const float s = sinf(angle);
		const float c = cosf(angle);

		cSPVector3 p;
		p.x = (mFacing.x * c + axis.x * s) * total;
		p.y = (mFacing.y * c + axis.y * s) * total;
		p.z = (mFacing.z * c + axis.z * s) * total;

		cSPVector3 pos;
		if (!mbRelative) {
			cSPVector3 q;
			q.x = mCenter.x + p.x;
			q.y = mCenter.y + p.y;
			q.z = mCenter.z + p.z;
			const float altitude = mAltitude;
			const float inv = 1.0f / sqrtf(((q.y * q.y + q.z * q.z) + q.x * q.x) + kNormEps);
			cSPVector3 dir;
			dir.x = q.x * inv * altitude;
			dir.y = q.y * inv * altitude;
			dir.z = q.z * inv * altitude;
			const cSPVector3 surf = SP::PlanetModel()->DirectionToSurfacePosition(q);
			pos.x = surf.x + dir.x;
			pos.y = surf.y + dir.y;
			pos.z = surf.z + dir.z;
		}
		else {
			pos = p;
		}
		AddSlot(pos);

		angle = angle + step;
	}
}
