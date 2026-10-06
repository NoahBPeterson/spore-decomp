// SP::cGameCameraController::UpdateInterpolation(float) @ 0x00F502B0
// (cTerrainCameraController has the same layout and method; its code lives near 0x00B0F000-0x00B16000, so this
// copy at 0x00F502B0 is taken to be the cGameCameraController one.)
// Names: dev-PDB (work/devbuild): class SP::cGameCameraController, its cInterpolationData<T> members, the
// cHermiteSplineInterpolation<T> splines, SP::SplineInterpolation<T> and CalculateAnchorInterpolationTime.
// Retail layout: the splines are 0x3c bytes each (0x30 in the dev PDB), so every member from +0x16c on is shifted.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
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
	float Length() const { return sqrtf(x * x + y * y + z * z + w * w); }
	static cSPQuaternion ZERO;   // 0x016C9064 (name guessed: all four components zero)
};
static inline cSPQuaternion operator-(const cSPQuaternion& a) { cSPQuaternion r; r.x = -a.x; r.y = -a.y; r.z = -a.z; r.w = -a.w; return r; }
static inline cSPQuaternion operator-(const cSPQuaternion& a, const cSPQuaternion& b) { cSPQuaternion r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; r.w = a.w - b.w; return r; }
static inline cSPQuaternion operator*(const cSPQuaternion& a, float s) { cSPQuaternion r; r.x = a.x * s; r.y = a.y * s; r.z = a.z * s; r.w = a.w * s; return r; }
static inline cSPQuaternion operator/(const cSPQuaternion& a, float s) { cSPQuaternion r; r.x = a.x / s; r.y = a.y / s; r.z = a.z / s; r.w = a.w / s; return r; }

static inline cSPVector3 Normalize(const cSPVector3& v)
{
	float inv = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return cSPVector3(inv * v.x, v.y * inv, v.z * inv);
}
static inline cSPQuaternion Normalize(const cSPQuaternion& q)
{
	float inv = 1.0f / sqrtf(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	return cSPQuaternion(inv * q.x, inv * q.y, inv * q.z, inv * q.w);
}

namespace eastl {
template <class T> inline const T& max(const T& a, const T& b) { return (a < b) ? b : a; }
}

namespace SP {
template <class T> T SplineInterpolation(const T& current, const T& velocity, const T& end, const T& endVelocity, float time, float dt);
// 0x00B0FC40 (float), 0x00B10E50 (cSPVector3), 0x00B11160 (cSPQuaternion)
template <> float SplineInterpolation<float>(const float&, const float&, const float&, const float&, float, float);
template <> cSPVector3 SplineInterpolation<cSPVector3>(const cSPVector3&, const cSPVector3&, const cSPVector3&, const cSPVector3&, float, float);
template <> cSPQuaternion SplineInterpolation<cSPQuaternion>(const cSPQuaternion&, const cSPQuaternion&, const cSPQuaternion&, const cSPQuaternion&, float, float);

template <class T> struct cHermiteSplineInterpolation
{
	uint32_t mData[15];   // times / points / slopes vectors (retail size 0x3c)
	T Interpolate(float t);   // 0x0069A5F0 (float), 0x0069A9A0 (cSPVector3), 0x0069AEE0 (cSPQuaternion)
};

struct cTerrainMapSet { float GetHeightAt(const cSPVector3& pos); };   // 0x00F927C0
struct cPlanetModel { virtual void v0(); virtual void v1(); virtual void v2(); virtual cTerrainMapSet* GetTerrain(); };   // +0xc
cPlanetModel* GetActivePlanetModel();   // 0x00F48AA0 (returns the global at 0x016C8EBC; name guessed)

float CameraApproach(float current, float target, float factor);   // 0x00F4EF40 (name guessed)

extern float kYawInterpolationTime;   // 0x015B0A80 (= 0.2f; name guessed)
extern float kRestingDamping;         // 0x015B0A7C (= 0.95f; name guessed)

class cGameCameraController
{
public:
	template <class T> struct cInterpolationData
	{
		bool targetChanged;    // +0
		bool targetMoving;     // +1
		float currentTime;     // +4
		float targetTime;      // +8
		T start;
		T current;
		T end;
		T target;
		T velocity;
		T targetVelocity;

		void UpdateTarget(float time)
		{
			targetTime = time;
			targetVelocity *= 0.0f;
			end = target;
			currentTime = 0.0f;
			targetChanged = false;
		}
	};

protected:
	void UpdateInterpolation(float deltaTime);     // 0x00F502B0
	float CalculateAnchorInterpolationTime();      // 0x00F4F480
public:

	uint32_t mBase[4];                                          // cICameraController + RefCountTemplate
	bool mDoEdgeScroll, mMouseScrollIsActive, mCivScroll, mStopCameraTarget, mUIZoomIn, mUIZoomOut, mUIRotateR, mUIRotateL;   // +0x10
	cInterpolationData<float> mCameraAnchorRadius;              // +0x18
	cInterpolationData<cSPVector3> mCameraAnchorDirection;      // +0x3c
	cInterpolationData<cSPQuaternion> mCameraAnchorOrientation; // +0x90
	cInterpolationData<float> mCameraDistance;                  // +0xfc
	cInterpolationData<float> mCameraPitch;                     // +0x120
	cInterpolationData<float> mCameraYaw;                       // +0x144
	bool mBallisticMotion;                                      // +0x168
	bool mAltZoomMode;                                          // +0x169
	cHermiteSplineInterpolation<float> mDistanceSpline;         // +0x16c
	cHermiteSplineInterpolation<float> mPitchSpline;            // +0x1a8
	cHermiteSplineInterpolation<cSPVector3> mDirectionSpline;   // +0x1e4
	cHermiteSplineInterpolation<cSPQuaternion> mOrientationSpline;   // +0x220
	float mLastDeltaTime;                                       // +0x25c
	float mLastZoomEffort;                                      // +0x260
	float mTargetCameraPreRotateX;                              // +0x264
	float mTargetCameraPreRotateZ;                              // +0x268
	float mCurrentCameraPreRotateX;                             // +0x26c
	float mCurrentCameraPreRotateZ;                             // +0x270
	float mCurrentCameraHeightAboveWater;                       // +0x274
	float mAnchorInterpolationTime;                             // +0x278
	float mOrientationInterpolationTime;                        // +0x27c
	float mThetaInterpolationTime;                              // +0x280
	float mPhiInterpolationTime;                                // +0x284
	float mDistanceInterpolationTime;                           // +0x288
};

// @ 0x00f502b0
void cGameCameraController::UpdateInterpolation(float deltaTime)
{
	// 1 - 2^(-dt / halfLife)
	float rotateFactor = 1.0f - expf(deltaTime / mOrientationInterpolationTime * -0.30103f);
	float distanceFactor = 1.0f - expf(deltaTime / mDistanceInterpolationTime * -0.30103f);
	mCurrentCameraPreRotateX = CameraApproach(mCurrentCameraPreRotateX, mTargetCameraPreRotateX, rotateFactor);
	mCurrentCameraPreRotateZ = CameraApproach(mCurrentCameraPreRotateZ, mTargetCameraPreRotateZ, rotateFactor);

	float time = -1.0f;
	if (!mBallisticMotion)
	{
		if (mCameraAnchorDirection.targetChanged)
		{
			time = CalculateAnchorInterpolationTime();
			mCameraAnchorDirection.UpdateTarget(time);
			if (mCameraAnchorDirection.targetVelocity == cSPVector3::ZERO)
				mCameraAnchorDirection.targetTime = time;
			mCameraAnchorDirection.targetMoving = false;
			mCameraAnchorRadius.targetMoving = false;
			mCameraAnchorOrientation.targetMoving = false;
		}
		if (mCameraDistance.targetChanged)
		{
			if (time < 0.0f)
				time = CalculateAnchorInterpolationTime();
			mCameraDistance.UpdateTarget(time);
			mCameraDistance.targetVelocity = 0.0f;
		}
		if (mCameraPitch.targetChanged)
		{
			if (time < 0.0f)
				time = CalculateAnchorInterpolationTime();
			mCameraPitch.UpdateTarget(time);
			mCameraPitch.targetVelocity = 0.0f;
		}
		if (mCameraYaw.targetChanged)
			mCameraYaw.UpdateTarget(kYawInterpolationTime);
		if (mCameraAnchorRadius.targetChanged)
		{
			if (time < 0.0f)
				time = CalculateAnchorInterpolationTime();
			mCameraAnchorRadius.UpdateTarget(time);
		}
		if (mCameraAnchorOrientation.targetChanged)
		{
			if (time < 0.0f)
				time = CalculateAnchorInterpolationTime();
			mCameraAnchorOrientation.UpdateTarget(time);
		}
	}

	bool ballisticDone = true;

	// Anchor direction: a unit vector; its velocity keeps only the tangential part.
	if (mCameraAnchorDirection.targetTime > mCameraAnchorDirection.currentTime)
	{
		mCameraAnchorDirection.currentTime += deltaTime;
		cSPVector3 prev = mCameraAnchorDirection.current;
		if (mBallisticMotion)
		{
			mCameraAnchorDirection.current = mDirectionSpline.Interpolate(mCameraAnchorDirection.currentTime);
			ballisticDone = false;
		}
		else
		{
			float damping = (mCameraAnchorDirection.targetMoving || mCameraAnchorDirection.targetVelocity.Dot(mCameraAnchorDirection.targetVelocity) > 1.5258789e-05f) ? 1.0f : kRestingDamping;
			float remaining = (mCameraAnchorDirection.targetTime - mCameraAnchorDirection.currentTime) * damping;
			mCameraAnchorDirection.current = SplineInterpolation(mCameraAnchorDirection.current, mCameraAnchorDirection.velocity,
				mCameraAnchorDirection.end, mCameraAnchorDirection.targetVelocity, eastl::max(deltaTime, remaining), deltaTime);
		}
		mCameraAnchorDirection.current = mCameraAnchorDirection.current / mCameraAnchorDirection.current.Length();
		mCameraAnchorDirection.velocity = (mCameraAnchorDirection.current - prev) / deltaTime;
		mCameraAnchorDirection.velocity = mCameraAnchorDirection.velocity - mCameraAnchorDirection.current * mCameraAnchorDirection.current.Dot(mCameraAnchorDirection.velocity);
	}
	else
	{
		mCameraAnchorDirection.velocity = cSPVector3::ZERO;
		mCameraAnchorDirection.targetVelocity = cSPVector3::ZERO;
	}

	// Anchor orientation: shortest arc, renormalized, tangential velocity.
	if (mCameraAnchorOrientation.targetTime > mCameraAnchorOrientation.currentTime)
	{
		mCameraAnchorOrientation.currentTime += deltaTime;
		cSPQuaternion prev = mCameraAnchorOrientation.current;
		if (mBallisticMotion)
		{
			mCameraAnchorOrientation.current = mOrientationSpline.Interpolate(mCameraAnchorOrientation.currentTime);
			ballisticDone = false;
		}
		else
		{
			if (mCameraAnchorOrientation.end.w * mCameraAnchorOrientation.current.w + mCameraAnchorOrientation.end.z * mCameraAnchorOrientation.current.z
				+ mCameraAnchorOrientation.end.y * mCameraAnchorOrientation.current.y + mCameraAnchorOrientation.end.x * mCameraAnchorOrientation.current.x < 0.0f)
				mCameraAnchorOrientation.end = -mCameraAnchorOrientation.end;
			float damping = (mCameraAnchorOrientation.targetMoving || mCameraAnchorOrientation.targetVelocity.Dot(mCameraAnchorOrientation.targetVelocity) > 1.5258789e-05f) ? 1.0f : kRestingDamping;
			float remaining = (mCameraAnchorOrientation.targetTime - mCameraAnchorOrientation.currentTime) * damping;
			mCameraAnchorOrientation.current = SplineInterpolation(mCameraAnchorOrientation.current, mCameraAnchorOrientation.velocity,
				mCameraAnchorOrientation.end, mCameraAnchorOrientation.targetVelocity, eastl::max(deltaTime, remaining), deltaTime);
		}
		mCameraAnchorOrientation.current = mCameraAnchorOrientation.current / mCameraAnchorOrientation.current.Length();
		mCameraAnchorOrientation.velocity = (mCameraAnchorOrientation.current - prev) / deltaTime;
		mCameraAnchorOrientation.velocity = mCameraAnchorOrientation.velocity - mCameraAnchorOrientation.current * mCameraAnchorOrientation.current.Dot(mCameraAnchorOrientation.velocity);
	}
	else
	{
		mCameraAnchorOrientation.velocity = cSPQuaternion::ZERO;
		mCameraAnchorOrientation.targetVelocity = cSPQuaternion::ZERO;
	}

	// Camera distance: eases toward the target when idle.
	if (mCameraDistance.targetTime > mCameraDistance.currentTime)
	{
		mCameraDistance.currentTime += deltaTime;
		float prev = mCameraDistance.current;
		if (mBallisticMotion)
		{
			mCameraDistance.current = mDistanceSpline.Interpolate(mCameraDistance.currentTime);
			ballisticDone = false;
		}
		else
		{
			float damping = (mCameraDistance.targetMoving || fabsf(mCameraDistance.targetVelocity) > 1.5258789e-05f) ? 1.0f : kRestingDamping;
			float remaining = (mCameraDistance.targetTime - mCameraDistance.currentTime) * damping;
			mCameraDistance.current = SplineInterpolation(mCameraDistance.current, mCameraDistance.velocity,
				mCameraDistance.end, mCameraDistance.targetVelocity, eastl::max(deltaTime, remaining), deltaTime);
		}
		mCameraDistance.velocity = (mCameraDistance.current - prev) / deltaTime;
	}
	else
	{
		float end = mCameraDistance.end;
		mCameraDistance.velocity = 0.0f;
		mCameraDistance.targetVelocity = 0.0f;
		float current = mCameraDistance.current;
		if (fabsf(end - current) > 1.5258789e-05f)
			mCameraDistance.current = (end - current) * distanceFactor + current;
		else
			mCameraDistance.current = end;
	}

	// Camera pitch.
	if (mCameraPitch.targetTime > mCameraPitch.currentTime)
	{
		mCameraPitch.currentTime += deltaTime;
		float prev = mCameraPitch.current;
		if (mBallisticMotion)
		{
			mCameraPitch.current = mPitchSpline.Interpolate(mCameraPitch.currentTime);
			ballisticDone = false;
		}
		else
		{
			float damping = (mCameraPitch.targetMoving || fabsf(mCameraPitch.targetVelocity) > 1.5258789e-05f) ? 1.0f : kRestingDamping;
			float remaining = (mCameraPitch.targetTime - mCameraPitch.currentTime) * damping;
			mCameraPitch.current = SplineInterpolation(mCameraPitch.current, mCameraPitch.velocity,
				mCameraPitch.end, mCameraPitch.targetVelocity, eastl::max(deltaTime, remaining), deltaTime);
		}
		mCameraPitch.velocity = (mCameraPitch.current - prev) / deltaTime;
	}
	else
	{
		mCameraPitch.velocity = 0.0f;
		mCameraPitch.targetVelocity = 0.0f;
	}

	// Camera yaw (never ballistic).
	if (mCameraYaw.targetTime > mCameraYaw.currentTime)
	{
		mCameraYaw.currentTime += deltaTime;
		float prev = mCameraYaw.current;
		float damping = (mCameraYaw.targetMoving || fabsf(mCameraYaw.targetVelocity) > 1.5258789e-05f) ? 1.0f : kRestingDamping;
		float remaining = (mCameraYaw.targetTime - mCameraYaw.currentTime) * damping;
		mCameraYaw.current = SplineInterpolation(mCameraYaw.current, mCameraYaw.velocity,
			mCameraYaw.end, mCameraYaw.targetVelocity, eastl::max(deltaTime, remaining), deltaTime);
		mCameraYaw.velocity = (mCameraYaw.current - prev) / deltaTime;
	}
	else
	{
		mCameraYaw.velocity = 0.0f;
		mCameraYaw.targetVelocity = 0.0f;
	}

	// Anchor radius: the end radius is kept above the terrain under the anchor.
	if (mCameraAnchorRadius.targetTime > mCameraAnchorRadius.currentTime)
	{
		float end = mCameraAnchorRadius.end;
		if (!mBallisticMotion)
		{
			float ground = GetActivePlanetModel()->GetTerrain()->GetHeightAt(mCameraAnchorDirection.current);
			end = eastl::max(ground, end);
		}
		float prev = mCameraAnchorRadius.current;
		mCameraAnchorRadius.currentTime = deltaTime + mCameraAnchorRadius.currentTime;
		float remaining = mCameraAnchorRadius.targetTime - mCameraAnchorRadius.currentTime;
		mCameraAnchorRadius.current = SplineInterpolation(mCameraAnchorRadius.current, mCameraAnchorRadius.velocity,
			end, mCameraAnchorRadius.targetVelocity, eastl::max(deltaTime, remaining), deltaTime);
		mCameraAnchorRadius.velocity = (mCameraAnchorRadius.current - prev) / deltaTime;
	}
	else
	{
		mCameraAnchorRadius.velocity = 0.0f;
		mCameraAnchorRadius.targetVelocity = 0.0f;
	}

	mLastDeltaTime = deltaTime;
	if (ballisticDone)
		mBallisticMotion = false;
}

}   // namespace SP
