// Slice s010eee10: hkRagdollConstraintData::buildJacobian (Havok 3.1.0, 0x010EEE10, 1657 bytes).
// Flags: /vc71 /O2 /MD /Gy /TP /fp:fast  (cl 13.10 ignores /fp:fast; the VS2008 equivalence tester needs it for inline fsqrt)
//
// Same algorithm as the powered ragdoll's non-motor path (slice s010ef580): keycode gate, A/B frames
// to world (pivot, plane axis, twist axis), angular friction rows or none, the twist-limit row (relative
// twist angle via atan2fApproximation, tau from the averaged twist axis), buildLimits (cone and plane
// limits) and the 3-row ball socket between the pivots. Layouts: match/include/havok31/hkReflectedClasses.h
// (hkRagdollConstraintData, 0x90 bytes); the keycode flag is a separate byte (0x016E5AAD) per constraint type.
// Float sums are grouped as the asm evaluates them; x87 values that never reach memory are hkX87Real.
#include "types.h"
#include <math.h>
#include <stddef.h>

typedef float hkReal;

extern const float kZero;   // 0x01485378
extern const float kOne;    // 0x01485720
typedef double hkX87Real;
// A float stack slot written and read back (rounds to float even under /fp:fast).
__forceinline float hkStoreF(hkX87Real v) { volatile float f = (float)v; return f; }

class __declspec(align(16)) hkVector4
{
public:
	float x, y, z, w;

	// add4 of a translation whose w the rotated vector had as 0: the original copies t.w.
	__forceinline void addTranslation(const hkVector4& t) { x = hkStoreF(x) + t.x; y = hkStoreF(y) + t.y; z = hkStoreF(z) + t.z; w = t.w; }

	// setCross(a, b) followed by normalize3() (lengthInverse3 + mul4), with the original's x87 data flow:
	// x stays on the x87 stack, y and z are stored (rounded) and z's square uses the stack value once.
	__forceinline void setCrossNormalized(const hkVector4& a, const hkVector4& b)
	{
		const hkX87Real nx = (hkX87Real)b.z * a.y - (hkX87Real)b.y * a.z;
		const float ny = hkStoreF((hkX87Real)b.x * a.z - (hkX87Real)b.z * a.x);
		const hkX87Real nzr = (hkX87Real)b.y * a.x - (hkX87Real)a.y * b.x;
		const float nz = hkStoreF(nzr);
		const hkX87Real len2 = (nzr * nz + (hkX87Real)ny * ny) + nx * nx;
		const hkX87Real inv = (len2 == kZero) ? (hkX87Real)kZero : kOne / sqrt(len2);
		x = (float)(inv * nx);
		y = (float)(ny * inv);
		z = (float)(nz * inv);
		w = (float)(inv * kZero);
	}
};

class hkMatrix3
{
public:
	hkVector4 m_col[3];
	void setMul(const hkMatrix3& a, const hkMatrix3& b);   // 0x01081DB0
};
class hkRotation : public hkMatrix3 {};

class hkTransform
{
public:
	hkRotation m_rotation;     // +0x00 (three columns)
	hkVector4 m_translation;   // +0x30
};

// hkVector4::setRotatedDir (out of line at 0x010814A0; inlined here): (vz*c2 + vy*c1) + vx*c0, w = 0.
__forceinline void setRotatedDir(hkVector4& d, const hkRotation& r, const hkVector4& v)
{
	const float vx = v.x, vy = v.y, vz = v.z;
	d.x = (vz * r.m_col[2].x + vy * r.m_col[1].x) + vx * r.m_col[0].x;
	d.y = (vz * r.m_col[2].y + vy * r.m_col[1].y) + vx * r.m_col[0].y;
	d.z = (vz * r.m_col[2].z + vy * r.m_col[1].z) + vx * r.m_col[0].z;
	d.w = 0.0f;
}

struct hkSolverResults
{
	hkReal m_impulseApplied;        // +0
	hkReal m_internalSolverData;    // +4
};

class hkConstraintQueryIn
{
public:
	float m_substepDeltaTime;            // +0x00
	float m_substepInvDeltaTime;         // +0x04
	float m_frameDeltaTime;              // +0x08
	float m_frameInvDeltaTime;           // +0x0c
	float m_virtualMassFactor;           // +0x10
	float m_rhsFactor;                   // +0x14
	float m_dampingFactor;               // +0x18
	float m_frictionRhsFactor;           // +0x1c
	void* m_accumulatorBufferRoot;       // +0x20
	void* m_jacobianBufferRoot;          // +0x24
	void* m_bodyA;                       // +0x28
	void* m_bodyB;                       // +0x2c
	hkTransform* m_transformA;           // +0x30
	hkTransform* m_transformB;           // +0x34
	float m_tau;                         // +0x38
	float m_damping;                     // +0x3c
	void* m_constraintInstance;          // +0x40
	void* m_constraintRuntime;           // +0x44
};

class hkConstraintQueryOut
{
public:
	void* m_jacobians;          // +0
	void* m_jacobianSchemas;    // +4
};

struct hk1dAngularFrictionInfo
{
	const hkVector4* m_constrainedDofW;     // +0x00 (the three world axes of body A)
	hkSolverResults* m_lastSolverResults;   // +0x04
	hkReal m_maxFrictionTorque;             // +0x08
	int m_numFriction;                      // +0x0c
};

struct hk1dAngularLimitInfo
{
	hkVector4 m_constrainedDofW;   // +0x00
	hkReal m_min;                  // +0x10
	hkReal m_max;                  // +0x14
	hkReal m_computedAngle;        // +0x18
	hkReal m_tau;                  // +0x1c
};

extern bool g_ragdollKeycodeOk;                      // 0x016E5AAD
bool hkSolverCheckKeycode(int component);           // 0x010BFBE0 (cdecl)

extern "C" void hkBeginConstraints(const hkConstraintQueryIn& in, hkConstraintQueryOut& out,
                                   hkSolverResults* sr, int solverResultStriding);                        // 0x010AA080
extern "C" void hk1dAngularFrictionBuildJacobian(const hk1dAngularFrictionInfo& info, const hkConstraintQueryIn& in,
                                                 hkConstraintQueryOut& out);                               // 0x010AA3C0
extern "C" void hk1dAngularLimitBuildJacobian(const hk1dAngularLimitInfo& info, const hkConstraintQueryIn& in,
                                              hkConstraintQueryOut& out);                                  // 0x010AB0E0
// 0x010AB2D0 (name guessed): the 3-row ball-socket jacobian between the two world pivots.
extern "C" void hkBallSocketBuildJacobian(const hkVector4& pivotA, const hkVector4& pivotB,
                                          const hkConstraintQueryIn& in, hkConstraintQueryOut& out);

namespace hkMath
{
	float atan2fApproximation(float x, float y);                                                         // 0x0120ADB0
}
class hkRagdollConstraintData
{
public:
	virtual void vslot0();
	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void vslot6();
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);   // 7 (+0x1c)

	void buildLimits(const hkVector4& twistAxisAinWorld, const hkVector4& twistAxisBinWorld,
	                 const hkVector4& planeAxisBinWorld, const hkConstraintQueryIn& in,
	                 hkConstraintQueryOut& out);                                              // 0x010EEA50

	// +0x04..0x0f hkConstraintData (refcount, userData): cl pads the vfptr to the 16-byte member alignment.
	hkVector4 m_basisA_pivot;         // +0x10
	hkVector4 m_basisA_planeAxis;     // +0x20
	hkVector4 m_basisA_twistAxis;     // +0x30
	hkVector4 m_basisB_pivot;         // +0x40
	hkVector4 m_basisB_planeAxis;     // +0x50
	hkVector4 m_basisB_twistAxis;     // +0x60
	hkReal m_coneMinAngle;            // +0x70
	hkReal m_planeMinAngle;           // +0x74
	hkReal m_planeMaxAngle;           // +0x78
	hkReal m_twistMinAngle;           // +0x7c
	hkReal m_twistMaxAngle;           // +0x80
	hkReal m_maxFrictionTorque;       // +0x84
	hkReal m_angularLimitsTauFactor;  // +0x88
};


// @ 0x010EEE10
void hkRagdollConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	if (!g_ragdollKeycodeOk)
	{
		g_ragdollKeycodeOk = hkSolverCheckKeycode(1);
		if (!g_ragdollKeycodeOk)
			return;
	}

	// constraint frames in world space
	const hkTransform& tA = *in.m_transformA;
	hkVector4 pivotAinWorld;
	setRotatedDir(pivotAinWorld, tA.m_rotation, m_basisA_pivot);
	hkVector4 planeAxisAinWorld;
	setRotatedDir(planeAxisAinWorld, tA.m_rotation, m_basisA_planeAxis);
	hkVector4 twistAxisAinWorld;
	setRotatedDir(twistAxisAinWorld, tA.m_rotation, m_basisA_twistAxis);
	pivotAinWorld.addTranslation(tA.m_translation);

	const hkTransform& tB = *in.m_transformB;
	hkVector4 pivotBinWorld;
	setRotatedDir(pivotBinWorld, tB.m_rotation, m_basisB_pivot);
	hkVector4 planeAxisBinWorld;
	setRotatedDir(planeAxisBinWorld, tB.m_rotation, m_basisB_planeAxis);
	hkVector4 twistAxisBinWorld;
	setRotatedDir(twistAxisBinWorld, tB.m_rotation, m_basisB_twistAxis);
	pivotBinWorld.addTranslation(tB.m_translation);

	hkSolverResults* runtime = (hkSolverResults*)in.m_constraintRuntime;

	if (m_maxFrictionTorque > kZero)
	{
		hkBeginConstraints(in, out, runtime, 8);

		hk1dAngularFrictionInfo friction;
		friction.m_constrainedDofW = &in.m_transformA->m_rotation.m_col[0];
		friction.m_lastSolverResults = runtime;
		friction.m_maxFrictionTorque = m_maxFrictionTorque;
		friction.m_numFriction = 3;
		hk1dAngularFrictionBuildJacobian(friction, in, out);
	}
	else
	{
		hkBeginConstraints(in, out, &runtime[3], 8);
	}

	// twist limit (hkInternalConstraintUtils_inlineCalcRelativeAngle inlined)
	{
		hk1dAngularLimitInfo info;
		info.m_constrainedDofW = twistAxisAinWorld;
		info.m_min = m_twistMinAngle;
		info.m_max = m_twistMaxAngle;

		// twist_axis_ws = twistB + twistA; x and w stay on the x87 stack, y and z are stored.
		const hkX87Real sumX = (hkX87Real)twistAxisBinWorld.x + twistAxisAinWorld.x;
		const float sumY = hkStoreF((hkX87Real)twistAxisBinWorld.y + twistAxisAinWorld.y);
		const float sumZ = hkStoreF((hkX87Real)twistAxisBinWorld.z + twistAxisAinWorld.z);
		const hkX87Real sumW = (hkX87Real)twistAxisBinWorld.w + twistAxisAinWorld.w;
		const hkX87Real twist_axis_ws_length3 = sqrt((sumX * sumX + (hkX87Real)sumZ * sumZ) + (hkX87Real)sumY * sumY);
		hkVector4 twist_axis_ws;
		hkReal tauMax;
		if (twist_axis_ws_length3 > 1e-16f)
		{
			tauMax = hkStoreF(0.5f * twist_axis_ws_length3);
			const hkX87Real inv = kOne / twist_axis_ws_length3;
			twist_axis_ws.x = hkStoreF(inv * sumX);
			twist_axis_ws.y = hkStoreF(sumY * inv);
			twist_axis_ws.z = hkStoreF(sumZ * inv);
			twist_axis_ws.w = hkStoreF(sumW * inv);
		}
		else
		{
			tauMax = 0.0f;
			twist_axis_ws = twistAxisBinWorld;
		}

		// m_ws_us: c0 = twist_axis_ws, c1 = c0 x planeB (on the x87 stack), c2 = c1 x c0 (stored)
		const hkX87Real c1x = (hkX87Real)planeAxisBinWorld.z * twist_axis_ws.y - (hkX87Real)planeAxisBinWorld.y * twist_axis_ws.z;
		const hkX87Real c1y = (hkX87Real)planeAxisBinWorld.x * twist_axis_ws.z - (hkX87Real)planeAxisBinWorld.z * twist_axis_ws.x;
		const hkX87Real c1z = (hkX87Real)planeAxisBinWorld.y * twist_axis_ws.x - (hkX87Real)planeAxisBinWorld.x * twist_axis_ws.y;
		hkVector4 c2;
		c2.y = hkStoreF(twist_axis_ws.x * c1z - c1x * twist_axis_ws.z);
		c2.z = hkStoreF(c1x * twist_axis_ws.y - c1y * twist_axis_ws.x);
		c2.x = hkStoreF(c1y * twist_axis_ws.z - c1z * twist_axis_ws.y);

		const float d1 = hkStoreF((c1z * planeAxisAinWorld.z + c1y * planeAxisAinWorld.y) + c1x * planeAxisAinWorld.x);
		const float d2 = hkStoreF((planeAxisAinWorld.x * c2.x + planeAxisAinWorld.z * c2.z) + planeAxisAinWorld.y * c2.y);
		info.m_computedAngle = hkMath::atan2fApproximation(d1, d2);
		info.m_constrainedDofW = twist_axis_ws;
		info.m_tau = (sqrt((hkX87Real)tauMax) * in.m_tau) * tauMax;
		hk1dAngularLimitBuildJacobian(info, in, out);
	}

	buildLimits(twistAxisAinWorld, twistAxisBinWorld, planeAxisBinWorld, in, out);
	hkBallSocketBuildJacobian(pivotAinWorld, pivotBinWorld, in, out);
}
