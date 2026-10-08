// Slice s01092e10: hkPoweredHingeConstraintData::buildJacobian (Havok 3.1.0, 0x01092e10, 2110 bytes).
// Flags: /vc71 /O2 /MD /Gy /TP /fp:fast. Layout (hkReflectedClasses.h): hkLimitedHingeConstraintData fields up to
// +0x90, then m_motorActive +0x90, m_ignoreLimits +0x91, m_targetAngle +0x94, m_motor +0x98.
// Runtime (0x48 bytes): initialized flag +0, initial position +4, solver results +8.., previous angle +0x40,
// revolution count +0x44. The hinge angle is unwrapped with the revolution counter; the motor row uses
// the first result slot (motor or friction), otherwise rows start at +0x10.
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
	hkSolverResults() : m_impulseApplied(0), m_internalSolverData(0) {}
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
struct hkPoweredHingeRuntime
{
	char m_initialized;                     // +0x00
	hkReal m_initialPosition;               // +0x04
	hkSolverResults m_solverResults[7];     // +0x08 (motor/friction row at +0x08, then +0x10..)
	hkReal m_previousAngle;                 // +0x40
	hkReal m_revolutions;                   // +0x44
};

struct hkConstraintMotorInput
{
	hkReal m_virtualMass;                       // +0x00 (written by the motor BeginJacobian)
	const hkConstraintQueryIn* m_stepInfo;      // +0x04
	hkSolverResults m_lastResults;              // +0x08
	hkReal m_deltaTarget;                       // +0x10
	hkReal m_positionError;                     // +0x14
};

struct hkConstraintMotorOutput
{
	hkReal m_targetPosition, m_targetVelocity, m_minForce, m_maxForce, m_tau, m_damping;
};

class hkConstraintMotor
{
public:
	virtual void vslot0();
	virtual void vslot1();
	virtual void motor(const hkConstraintMotorInput& input, hkConstraintMotorOutput& output) const = 0;   // +8
};

extern "C" void hk1dAngularVelocityMotorBeginJacobian(const hkVector4& axis, const hkConstraintQueryIn& in,
                                                      void* jacobians, hkConstraintMotorInput* statusOut);   // 0x010AC750
extern "C" void hk1dAngularVelocityMotorCommitJacobian(const hkConstraintMotorOutput& info,
                                                       const hkConstraintQueryIn& in, hkConstraintQueryOut& out);   // 0x010AA0D0

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

extern const float kPi;      // 0x014a1ae0
extern const float kNegPi;   // 0x0149e14c
extern const float kOne;     // 0x01485720
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

class hkPoweredHingeConstraintData : public hkConstraintData
{
public:
	hkReal m_minAngle;                  // +0x0c
	hkReal m_maxAngle;                  // +0x10
	hkReal m_maxFrictionTorque;         // +0x14
	hkReal m_angularLimitsTauFactor;    // +0x18
	hkLimitedHingeBasisA m_basisA;      // +0x20
	hkLimitedHingeBasisB m_basisB;      // +0x60
	bool m_motorActive;                 // +0x90
	bool m_ignoreLimits;                // +0x91
	hkReal m_targetAngle;               // +0x94
	hkConstraintMotor* m_motor;         // +0x98

	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void vslot6();
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);
};

// @ 0x01092e10
void hkPoweredHingeConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	// frame A in world: axle, perp1, perp2 and the pivot
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

	hkPoweredHingeRuntime* runtime = (hkPoweredHingeRuntime*)in.m_constraintRuntime;

	hk1dAngularLimitInfo limit;
	limit.m_constrainedDofW = rotA.m_col[0];
	limit.m_min = m_minAngle;
	limit.m_max = m_maxAngle;
	limit.m_tau = in.m_tau * m_angularLimitsTauFactor;

	// the three world vectors were stored as floats (rounded) before this point; read them back from memory
	const volatile hkVector4& p = perp2FreeBW;
	const volatile hkVector4& a = axleBW;
	const volatile hkVector4& b = perp1AW;
	typedef double X87;
	const float cosPart = (float)((X87)p.x * b.x + ((X87)p.y * b.y + (X87)p.z * b.z));
	const X87 ta = (X87)p.y * a.z - (X87)p.z * a.y;
	const X87 tb = (X87)p.z * a.x - (X87)p.x * a.z;
	const X87 tc = (X87)p.x * a.y - (X87)p.y * a.x;
	const float sinPart = (float)((ta * b.x + tc * b.z) + tb * b.y);
	float angle = hkMath::atan2fApproximation(-cosPart, -sinPart) + kPi;
	const float diff = angle - runtime->m_previousAngle;
	if (diff < kNegPi)
		runtime->m_revolutions = runtime->m_revolutions + kOne;
	else if (diff > kPi)
		runtime->m_revolutions = runtime->m_revolutions - kOne;
	runtime->m_previousAngle = angle;
	// the stored (rounded) float is what the unwrapped angle is built from
	angle = runtime->m_revolutions * kTwoPi + *(volatile float*)&runtime->m_previousAngle;
	limit.m_computedAngle = angle;

	if (m_motor != 0 && m_motorActive)
	{
		if (runtime->m_initialized == 0)
		{
			runtime->m_initialPosition = angle;
			runtime->m_initialized = 1;
		}
		hkBeginConstraints(in, out, &runtime->m_solverResults[0], 8);
		hkConstraintMotorInput input;
		hk1dAngularVelocityMotorBeginJacobian(rotA.m_col[0], in, out.m_jacobians, &input);
		input.m_deltaTarget = m_targetAngle - runtime->m_initialPosition;
		input.m_lastResults = runtime->m_solverResults[0];
		input.m_positionError = runtime->m_initialPosition - angle;
		input.m_stepInfo = &in;
		hkConstraintMotorOutput output;
		m_motor->motor(input, output);
		hk1dAngularVelocityMotorCommitJacobian(output, in, out);
	}
	else if (m_maxFrictionTorque != kZero)
	{
		hkBeginConstraints(in, out, &runtime->m_solverResults[0], 8);
		hk1dAngularFrictionInfo friction;
		friction.m_constrainedDofW = &rotA.m_col[0];
		friction.m_lastSolverResults = &runtime->m_solverResults[0];
		friction.m_maxFrictionTorque = m_maxFrictionTorque;
		friction.m_numFriction = 1;
		hk1dAngularFrictionBuildJacobian(friction, in, out);
	}
	else
	{
		hkBeginConstraints(in, out, &runtime->m_solverResults[1], 8);
	}

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

	hkBallSocketBuildJacobian(pivotAW, pivotBW, in, out);

	if (!m_ignoreLimits)
	{
		limit.m_tau = in.m_tau * m_angularLimitsTauFactor;
		hk1dAngularLimitBuildJacobian(limit, in, out);
	}
	runtime->m_initialPosition = m_targetAngle;
}
