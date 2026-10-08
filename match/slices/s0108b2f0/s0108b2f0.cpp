// Slice s0108b2f0: hkLimitedHingeConstraintData::buildJacobian (Havok 3.1.0, 0x0108b2f0, 1763 bytes).
// Flags: /O2 /MD /Gy /TP /fp:fast.
//
// Layouts: match/include/havok31/hkReflectedClasses.h (hkLimitedHingeConstraintData 0x90 bytes: min/max angle
// +0xc/+0x10, max friction torque +0x14, angular limits tau factor +0x18, basisA {pivot, axle, perpToAxle1,
// perpToAxle2} +0x20, basisB {pivot, axle, perp2FreeAxis} +0x60). The runtime block and the info structs for
// the hk1d* builders were read off the stores in the asm; names follow Havok 6.x where they exist.
//
// Steps: frame A and B to world; two angular bilateral rows (A's perpendicular axes against B's axle); the
// hinge angle (atan2 of B's free perpendicular against A's perp1 and axle x ...) unwrapped against the angle
// kept in the runtime (+0x38); the angular limit row; the ball-socket rows; optional angular friction row.
//
// Havok 3.1 was built by an older cl: x87 scheduling differs, behaviourally equivalent, not byte-exact.
#include "types.h"

typedef float hkReal;

extern const float kZero;   // 0x01485378

class __declspec(align(16)) hkVector4
{
public:
	float x, y, z, w;
	__forceinline void addTranslation(const hkVector4& t) { x = x + t.x; y = y + t.y; z = z + t.z; w = t.w; }
};

class hkMatrix3
{
public:
	hkVector4 m_col[3];
};
class hkRotation : public hkMatrix3 {};

class hkTransform
{
public:
	hkRotation m_rotation;     // +0x00
	hkVector4 m_translation;   // +0x30
};

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

// in.m_constraintRuntime (0x3c bytes): solver results of the rows, friction row at +0x30, previous hinge angle.
struct hkLimitedHingeRuntime
{
	hkSolverResults m_solverResults[7];     // +0x00
	hkReal m_previousAngle;                 // +0x38
};

struct hk1dAngularFrictionInfo
{
	const hkVector4* m_constrainedDofW;     // +0x00
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

struct hk1dAngularBilateralConstraintInfo
{
	hkVector4 m_zeroErrorAxisAinW;           // +0x00
	hkVector4 m_constrainedDofW;             // +0x10
	hkVector4 m_perpZeroErrorAxisBinW;       // +0x20
};

extern "C" void hkBeginConstraints(const hkConstraintQueryIn& in, hkConstraintQueryOut& out,
                                   hkSolverResults* sr, int solverResultStriding);                        // 0x010AA080
extern "C" void hk1dAngularBilateralConstraintBuildJacobian(const hk1dAngularBilateralConstraintInfo& info,
                                                            const hkConstraintQueryIn& in,
                                                            hkConstraintQueryOut& out);                   // 0x010AA1E0
extern "C" void hk1dAngularFrictionBuildJacobian(const hk1dAngularFrictionInfo& info, const hkConstraintQueryIn& in,
                                                 hkConstraintQueryOut& out);                               // 0x010AA3C0
extern "C" void hk1dAngularLimitBuildJacobian(const hk1dAngularLimitInfo& info, const hkConstraintQueryIn& in,
                                              hkConstraintQueryOut& out);                                  // 0x010AB0E0
// 0x010AB2D0 (name guessed): the 3-row ball-socket jacobian between the two world pivots.
extern "C" void hkBallSocketBuildJacobian(const hkVector4& pivotA, const hkVector4& pivotB,
                                          const hkConstraintQueryIn& in, hkConstraintQueryOut& out);
namespace hkMath { float atan2fApproximation(float y, float x); }     // 0x0120adb0 (cdecl)

extern const float kPi;      // 0x0149e210
extern const float kTwoPi;   // 0x01446dec

struct hkLimitedHingeBasisA
{
	hkVector4 m_pivot;          // +0x00
	hkVector4 m_axle;           // +0x10
	hkVector4 m_perpToAxle1;    // +0x20
	hkVector4 m_perpToAxle2;    // +0x30
};

struct hkLimitedHingeBasisB
{
	hkVector4 m_pivot;          // +0x00
	hkVector4 m_axle;           // +0x10
	hkVector4 m_perp2FreeAxis;  // +0x20
};

class hkConstraintData
{
public:
	virtual ~hkConstraintData();
	int m_memSizeAndFlags_userData[2];  // +0x04
};

class hkLimitedHingeConstraintData : public hkConstraintData
{
public:
	hkReal m_minAngle;                  // +0x0c
	hkReal m_maxAngle;                  // +0x10
	hkReal m_maxFrictionTorque;         // +0x14
	hkReal m_angularLimitsTauFactor;    // +0x18
	hkLimitedHingeBasisA m_basisA;      // +0x20
	hkLimitedHingeBasisB m_basisB;      // +0x60

	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void vslot6();
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);
};

// @ 0x0108b2f0
void hkLimitedHingeConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	hkLimitedHingeRuntime* runtime = (hkLimitedHingeRuntime*)in.m_constraintRuntime;
	hkBeginConstraints(in, out, runtime->m_solverResults, 8);

	// frame A in world: axle, perp1, perp2 (rotA.m_col[0..2]) and the pivot
	const hkTransform& tA = *in.m_transformA;
	hkRotation rotA;
	setRotatedDir(rotA.m_col[0], tA.m_rotation, m_basisA.m_axle);
	hkVector4 perp1AW;
	setRotatedDir(perp1AW, tA.m_rotation, m_basisA.m_perpToAxle1);
	hkVector4 perp2AW;
	setRotatedDir(perp2AW, tA.m_rotation, m_basisA.m_perpToAxle2);
	hkVector4 pivotAW;
	setRotatedDir(pivotAW, tA.m_rotation, m_basisA.m_pivot);
	pivotAW.addTranslation(tA.m_translation);
	rotA.m_col[1] = perp1AW;
	rotA.m_col[2] = perp2AW;

	// frame B in world
	const hkTransform& tB = *in.m_transformB;
	hkVector4 axleBW;
	setRotatedDir(axleBW, tB.m_rotation, m_basisB.m_axle);
	hkVector4 perp2FreeBW;
	setRotatedDir(perp2FreeBW, tB.m_rotation, m_basisB.m_perp2FreeAxis);
	hkVector4 pivotBW;
	setRotatedDir(pivotBW, tB.m_rotation, m_basisB.m_pivot);
	pivotBW.addTranslation(tB.m_translation);

	// two angular rows keeping B's axle perpendicular to A's perp1 / perp2
	{
		hk1dAngularBilateralConstraintInfo ang;
		ang.m_zeroErrorAxisAinW = perp2AW;
		ang.m_constrainedDofW = perp1AW;
		ang.m_perpZeroErrorAxisBinW = axleBW;
		hk1dAngularBilateralConstraintBuildJacobian(ang, in, out);
	}
	{
		hk1dAngularBilateralConstraintInfo ang;
		ang.m_zeroErrorAxisAinW = perp1AW;
		ang.m_constrainedDofW = perp2AW;
		ang.m_perpZeroErrorAxisBinW.x = -axleBW.x;
		ang.m_perpZeroErrorAxisBinW.y = -axleBW.y;
		ang.m_perpZeroErrorAxisBinW.z = -axleBW.z;
		ang.m_perpZeroErrorAxisBinW.w = -axleBW.w;
		hk1dAngularBilateralConstraintBuildJacobian(ang, in, out);
	}

	// hinge angle, unwrapped against the previous one
	hk1dAngularLimitInfo limit;
	limit.m_constrainedDofW = rotA.m_col[0];
	limit.m_min = m_minAngle;
	limit.m_max = m_maxAngle;
	limit.m_tau = in.m_tau * m_angularLimitsTauFactor;

	const hkVector4& p = perp2FreeBW;
	const hkVector4& a = axleBW;
	// evaluated on the x87 stack at extended precision, stored once
	typedef double X87;
	const float cosPart = (float)((X87)p.y * perp1AW.y + ((X87)p.z * perp1AW.z + (X87)p.x * perp1AW.x));
	const float sinPart = (float)(((X87)p.z * a.x - (X87)p.x * a.z) * perp1AW.y +
		(((X87)p.x * a.y - (X87)p.y * a.x) * perp1AW.z + ((X87)p.y * a.z - (X87)p.z * a.y) * perp1AW.x));
	float angle = hkMath::atan2fApproximation(cosPart, sinPart);
	if (runtime->m_previousAngle - angle > kPi)
		angle = angle + kTwoPi;
	else if (angle - runtime->m_previousAngle > kPi)
		angle = angle - kTwoPi;
	limit.m_computedAngle = angle;
	runtime->m_previousAngle = angle;
	hk1dAngularLimitBuildJacobian(limit, in, out);

	hkBallSocketBuildJacobian(pivotAW, pivotBW, in, out);

	if (m_maxFrictionTorque != kZero)
	{
		hk1dAngularFrictionInfo friction;
		friction.m_constrainedDofW = &rotA.m_col[0];
		friction.m_lastSolverResults = &runtime->m_solverResults[6];
		friction.m_maxFrictionTorque = m_maxFrictionTorque;
		friction.m_numFriction = 1;
		hk1dAngularFrictionBuildJacobian(friction, in, out);
	}
}
