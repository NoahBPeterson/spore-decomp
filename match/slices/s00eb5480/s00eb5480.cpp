// Slice s00eb5480: SP::cGameCinematicsCameraController::UpdateInterpolation(float) @ 0x00EB5480 and the
// file-local sCalculateOrientation(from, to, current, pole) @ 0x00EB5C00 (dev-PDB name `anonymous namespace'::sCalculateOrientation).
// Names/layouts: dev PDB (cGameCinematicsCameraController, tELerpScalar/tELerpAngle/tSLerpVector3/tELerpQuaternion);
// retail shifts the splines (0x3c bytes each instead of 0x30), so mDistanceSpline is at +0x1b0 here.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same module family as s00f502b0).
#include "types.h"
#include <math.h>

struct cSPVector3
{
	float x, y, z;
	cSPVector3() {}
	cSPVector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

	float SquaredLength() const { return x * x + y * y + z * z; }
	cSPVector3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
	bool operator==(const cSPVector3& b) const { return x == b.x && y == b.y && z == b.z; }
	float Dot(const cSPVector3& b) const { return x * b.x + y * b.y + z * b.z; }
	// same sum as Dot, accumulated statement by statement so cl /fp:fast keeps the x-first order of the original
	float DotXYZ(const cSPVector3& b) const { float d = x * b.x; d += y * b.y; d += z * b.z; return d; }
	float Length() const { return sqrtf(x * x + y * y + z * z); }
	static cSPVector3 ZERO;   // 0x016C9058
};
static inline cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b) { cSPVector3 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r; }
static inline cSPVector3 operator*(const cSPVector3& a, float s) { cSPVector3 r; r.x = a.x * s; r.y = a.y * s; r.z = a.z * s; return r; }
static inline cSPVector3 operator/(const cSPVector3& a, float s) { cSPVector3 r; r.x = a.x / s; r.y = a.y / s; r.z = a.z / s; return r; }

struct cSPQuaternion
{
	float x, y, z, w;
	cSPQuaternion() {}
	cSPQuaternion(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

	float SquaredLength() const { return x * x + y * y + z * z + w * w; }
	cSPQuaternion& operator*=(float s) { x *= s; y *= s; z *= s; w *= s; return *this; }
	float Dot(const cSPQuaternion& b) const { return x * b.x + y * b.y + z * b.z + w * b.w; }
	// same sum as Dot, accumulated statement by statement so cl /fp:fast keeps the x-first order of the original
	float DotXYZW(const cSPQuaternion& b) const { float d = x * b.x; d += y * b.y; d += z * b.z; d += w * b.w; return d; }
	float Length() const { return sqrtf(x * x + y * y + z * z + w * w); }
	static cSPQuaternion ZERO;   // 0x016C9064 (name guessed: all four components zero)
};
static inline cSPQuaternion operator-(const cSPQuaternion& a) { cSPQuaternion r; r.x = -a.x; r.y = -a.y; r.z = -a.z; r.w = -a.w; return r; }
static inline cSPQuaternion operator-(const cSPQuaternion& a, const cSPQuaternion& b) { cSPQuaternion r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; r.w = a.w - b.w; return r; }
static inline cSPQuaternion operator*(const cSPQuaternion& a, float s) { cSPQuaternion r; r.x = a.x * s; r.y = a.y * s; r.z = a.z * s; r.w = a.w * s; return r; }
static inline cSPQuaternion operator/(const cSPQuaternion& a, float s) { cSPQuaternion r; r.x = a.x / s; r.y = a.y / s; r.z = a.z / s; r.w = a.w / s; return r; }

static inline cSPVector3 Normalize(const cSPVector3& v)
{
	// The original computes 1/sqrt on the x87 and rounds it to float once (it moves to SSE through memory);
	// volatile keeps cl from multiplying with the unrounded x87 value under /fp:fast.
	volatile float invv = (float)(1.0 / sqrt((double)v.x * v.x + (double)v.y * v.y + (double)v.z * v.z));
	float inv = invv;
	return cSPVector3(inv * v.x, v.y * inv, v.z * inv);
}
static inline cSPQuaternion Normalize(const cSPQuaternion& q)
{
	volatile float inv = (float)(1.0 / sqrt((double)q.x * q.x + (double)q.y * q.y + (double)q.z * q.z + (double)q.w * q.w));
	return cSPQuaternion(inv * q.x, inv * q.y, inv * q.z, inv * q.w);
}

namespace eastl {
template <class T> inline const T& max(const T& a, const T& b) { return (a < b) ? b : a; }
}


namespace SP {
// SplineInterpolation<float> (plain overload so the call has an address): 0x00B0FC40
float SplineInterpolation(const float&, const float&, const float&, const float&, float, float);

template <class T> struct cHermiteSplineInterpolation
{
	uint32_t mData[15];   // retail size 0x3c
	T Evaluate(float t);   // 0x0069A5F0 (float), 0x0069A9A0 (cSPVector3), 0x0069AEE0 (cSPQuaternion)
};

struct tELerpScalar { float mOrig, mCurrent, mTarget, mCurrentTime, mVelocity; };          // 0x14
typedef tELerpScalar tELerpAngle;                                                         // same layout
struct tSLerpVector3
{
	cSPVector3 mCurrent, mTarget, mOrig;
	bool mOnSphere;
	float mCurrentTime;
	cSPVector3 mVelocity;                                                                 // 0x38
};
struct tELerpQuaternion
{
	cSPQuaternion mOrig, mCurrent, mTarget;
	float mCurrentTime;
	cSPQuaternion mVelocity;                                                              // 0x44
};

extern const float kLerpEaseScale;   // 0x015A93F0 (0.95f; name guessed)

class cGameCinematicsCameraController
{
public:
	void UpdateInterpolation(float deltaTime);      // 0x00EB5480

	uint32_t mBase[6];                              // +0x00 vptrs / refcount / config / mode
	tELerpAngle mCameraTheta;                       // +0x18
	tELerpAngle mCameraPhi;                         // +0x2c
	tELerpAngle mCameraRoll;                        // +0x40
	tSLerpVector3 mSubjectPosition;                 // +0x54
	tSLerpVector3 mSubjectDirection;                // +0x8c
	tELerpScalar mSubjectRadius;                    // +0xc4
	tELerpScalar mFieldOfView;                      // +0xd8
	tELerpScalar mCamOffset;                        // +0xec
	uint8_t mPad100[0x130 - 0x100];                 // +0x100 clips, flags, durations, mCurrentAt, mSubjectUp
	tELerpQuaternion mOrientation;                  // +0x130
	uint8_t mCurrentTransform[0x1b0 - 0x174];       // +0x174 cSPTransform (padded in retail)
	cHermiteSplineInterpolation<float> mDistanceSpline;          // +0x1b0
	cHermiteSplineInterpolation<float> mPitchSpline;             // +0x1ec
	cHermiteSplineInterpolation<cSPVector3> mDirectionSpline;    // +0x228
	cHermiteSplineInterpolation<cSPQuaternion> mOrientationSpline;   // +0x264
};

// @ 0x00eb5480
void cGameCinematicsCameraController::UpdateInterpolation(float deltaTime)
{
	// Subject direction: Hermite spline, renormalized; velocity keeps only the tangential part.
	if (mSubjectDirection.mCurrentTime < 1.0f)
	{
		mSubjectDirection.mCurrentTime += deltaTime;
		cSPVector3 prev = mSubjectDirection.mCurrent;
		mSubjectDirection.mCurrent = mDirectionSpline.Evaluate(mSubjectDirection.mCurrentTime);
		mSubjectDirection.mCurrent = Normalize(mSubjectDirection.mCurrent);
		mSubjectDirection.mVelocity = (mSubjectDirection.mCurrent - prev) / deltaTime;
		mSubjectDirection.mVelocity = mSubjectDirection.mVelocity - mSubjectDirection.mCurrent * mSubjectDirection.mCurrent.DotXYZ(mSubjectDirection.mVelocity);
	}
	// Orientation: Hermite spline on the quaternion, renormalized.
	if (mOrientation.mCurrentTime < 1.0f)
	{
		mOrientation.mCurrentTime += deltaTime;
		cSPQuaternion prev = mOrientation.mCurrent;
		mOrientation.mCurrent = mOrientationSpline.Evaluate(mOrientation.mCurrentTime);
		mOrientation.mCurrent = Normalize(mOrientation.mCurrent);
		mOrientation.mVelocity = (mOrientation.mCurrent - prev) / deltaTime;
		mOrientation.mVelocity = mOrientation.mVelocity - mOrientation.mCurrent * mOrientation.mCurrent.DotXYZW(mOrientation.mVelocity);
	}
	// Camera offset: Hermite spline on a scalar.
	if (mCamOffset.mCurrentTime < 1.0f)
	{
		mCamOffset.mCurrentTime += deltaTime;
		float prev = mCamOffset.mCurrent;
		mCamOffset.mCurrent = mDistanceSpline.Evaluate(mCamOffset.mCurrentTime);
		mCamOffset.mVelocity = (mCamOffset.mCurrent - prev) / deltaTime;
	}
	// Phi: Hermite spline on a scalar.
	if (mCameraPhi.mCurrentTime < 1.0f)
	{
		mCameraPhi.mCurrentTime += deltaTime;
		float prev = mCameraPhi.mCurrent;
		mCameraPhi.mCurrent = mPitchSpline.Evaluate(mCameraPhi.mCurrentTime);
		mCameraPhi.mVelocity = (mCameraPhi.mCurrent - prev) / deltaTime;
	}
	// Theta: eased spline interpolation toward the target.
	if (mCameraTheta.mCurrentTime < 1.0f)
	{
		float prev = mCameraTheta.mCurrent;
		mCameraTheta.mCurrentTime += deltaTime;
		float remaining = (1.0f - mCameraTheta.mCurrentTime) * kLerpEaseScale;
		mCameraTheta.mCurrent = SplineInterpolation(mCameraTheta.mCurrent, mCameraTheta.mVelocity, mCameraTheta.mTarget,
			0.0f, eastl::max(deltaTime, remaining), deltaTime);
		mCameraTheta.mVelocity = (mCameraTheta.mCurrent - prev) / deltaTime;
	}
	// Subject radius.
	if (mSubjectRadius.mCurrentTime < 1.0f)
	{
		float prev = mSubjectRadius.mCurrent;
		mSubjectRadius.mCurrentTime += deltaTime;
		float remaining = 1.0f - mSubjectRadius.mCurrentTime;
		mSubjectRadius.mCurrent = SplineInterpolation(mSubjectRadius.mCurrent, mSubjectRadius.mVelocity, mSubjectRadius.mTarget,
			0.0f, eastl::max(deltaTime, remaining), deltaTime);
		mSubjectRadius.mVelocity = (mSubjectRadius.mCurrent - prev) / deltaTime;
	}
	mSubjectPosition.mCurrent = mSubjectDirection.mCurrent * mSubjectRadius.mCurrent;
}

// ---- sCalculateOrientation ----
struct cTerrainSphere { cSPQuaternion BuildSurfaceOrientation(const cSPVector3& position, const cSPQuaternion& current); };   // 0x00F9C960
cTerrainSphere* GetActiveTerrainSphere();   // 0x00F48AA0 (planet-model getter; name guessed)
extern bool gSnapToSurface;                 // 0x015A93F4 (name guessed)

static inline cSPVector3 Cross(const cSPVector3& a, const cSPVector3& b)
{
	return cSPVector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

// Hamilton product r * q, evaluated in the original's order.
static inline cSPQuaternion Mul(const cSPQuaternion& r, const cSPQuaternion& q)
{
	return cSPQuaternion((r.w * q.x + r.x * q.w) + (q.z * r.y - q.y * r.z),
	                     (q.y * r.w + r.y * q.w) + (r.z * q.x - q.z * r.x),
	                     (q.z * r.w + r.z * q.w) + (q.y * r.x - r.y * q.x),
	                     r.w * q.w - ((q.z * r.z + q.y * r.y) + q.x * r.x));
}

// Rotation that takes `from` onto `to` (shortest arc), composed with `current`; when the two directions are
// opposite the axis is derived from `pole` (or any perpendicular).
// @ 0x00eb5c00
cSPQuaternion sCalculateOrientation(const cSPVector3& from, const cSPVector3& to, const cSPQuaternion& current,
                                    const cSPVector3& pole)
{
	cSPVector3 n1 = Normalize(from);
	cSPVector3 n2 = Normalize(to);
	cSPVector3 sum(n2.x + n1.x, n2.y + n1.y, n2.z + n1.z);
	float len = (float)sqrt((double)sum.z * sum.z + (double)sum.y * sum.y + (double)sum.x * sum.x);
	if (len < 1.5258789e-05f)
	{
		// opposite directions: pick a perpendicular axis
		cSPVector3 d(from.x - pole.x, from.y - pole.y, from.z - pole.z);
		cSPVector3 dn = Normalize(d);
		cSPVector3 t = Cross(dn, n1);
		cSPVector3 v = Cross(n1, t);
		if ((float)sqrt((double)v.z * v.z + (double)v.y * v.y + (double)v.x * v.x) < 1.5258789e-05f)
		{
			v = Cross(n1, cSPVector3(1.0f, 0.0f, 0.0f));
			if ((float)sqrt((double)v.z * v.z + (double)v.y * v.y + (double)v.x * v.x) < 1.5258789e-05f)
				v = Cross(n1, cSPVector3(0.0f, 0.0f, 1.0f));
		}
		cSPVector3 axis = Normalize(v);
		return Mul(cSPQuaternion(axis.x, axis.y, axis.z, 0.0f), current);
	}
	float invLen = 1.0f / len;
	cSPVector3 h(sum.x * invLen, sum.y * invLen, sum.z * invLen);
	cSPVector3 axis = Cross(n1, h);
	cSPQuaternion r(axis.x, axis.y, axis.z, (h.x * n1.x + h.z * n1.z) + h.y * n1.y);
	cSPQuaternion result = Mul(r, current);
	if (gSnapToSurface)
	{
		cTerrainSphere* sphere = GetActiveTerrainSphere();
		if (sphere)
			result = sphere->BuildSurfaceOrientation(to, result);
	}
	return result;
}

}   // namespace SP
