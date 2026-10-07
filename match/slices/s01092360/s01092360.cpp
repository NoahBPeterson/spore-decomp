// Slice s01092360: hkPrismaticConstraintData::buildJacobian (Havok 3.1.0, 0x01092360, 2556 bytes).
// Flags: /O2 /MD /Gy /TP /fp:fast.
//
// Layouts: match/include/havok31/hkReflectedClasses.h (hkPrismaticConstraintData 0xa0 bytes: m_motor +0xc,
// m_basisA {pivot, shaft, BtoAoffsetRotation} +0x10, m_basisB {pivot, shaft, perpToShaft} +0x60, limits
// +0x90/+0x94, max friction +0x98, motor target +0x9c). The runtime block (in.m_constraintRuntime) and the
// info structs passed to the hk1d* jacobian builders were read off the stores in the asm (offsets in the
// comments); member names follow the Havok 6.x headers where they still exist.
//
// Steps: frame A (pivot, shaft, BtoA-offset rotation) and frame B (pivot, shaft, perpendicular) to world;
// first-call init of the runtime's previous motor target; then either the motor row (linear velocity
// motor begin, motor->motor(), commit), the friction row or no row (the solver results then start at
// row 1); three angular bilateral rows, two linear bilateral rows (along perpB and shaftB x perpB, with
// pivot B moved along the shaft to pivot A's projection) and the linear limit along the shaft.
//
// Havok 3.1 was built by an older cl than ours: x87 scheduling differs, so this is behaviourally
// equivalent, not byte-exact. Float sums are grouped as the asm evaluates them.
#include "types.h"

typedef float hkReal;

extern const float kZero;   // 0x01485378

class __declspec(align(16)) hkVector4
{
public:
	float x, y, z, w;

	// add4 of a translation whose w the rotated vector had as 0: the original copies t.w.
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
	hkRotation m_rotation;     // +0x00 (three columns)
	hkVector4 m_translation;   // +0x30
};

// hkVector4::setRotatedDir (inlined): (vz*c2 + vy*c1) + vx*c0, w = 0.
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

// in.m_constraintRuntime of a prismatic constraint (0x40 bytes): solver results of the 7 rows
// (motor or friction, 3 angular, 2 linear, limit), the previous motor target and its init flag.
struct hkPrismaticRuntime
{
	hkSolverResults m_solverResults[7];     // +0x00
	hkReal m_previousTargetPosition;        // +0x38
	bool m_initialized;                     // +0x3c
};

// hkConstraintMotorInput (0x18): status written by hk1dLinearVelocityMotorBeginJacobian, then the inputs.
struct hkConstraintMotorInput
{
	hkReal m_virtualMass;                       // +0x00 (hk1dBilateralConstraintStatus)
	const hkConstraintQueryIn* m_stepInfo;      // +0x04
	hkSolverResults m_lastResults;              // +0x08
	hkReal m_deltaTarget;                       // +0x10
	hkReal m_positionError;                     // +0x14
};

// hkConstraintMotorOutput: filled by hkConstraintMotor::motor.
struct hkConstraintMotorOutput
{
	hkReal m_targetPosition;
	hkReal m_targetVelocity;
	hkReal m_minForce;
	hkReal m_maxForce;
	hkReal m_tau;
	hkReal m_damping;
};

class hkConstraintMotor
{
public:
	virtual void vslot0();
	virtual void vslot1();
	virtual void motor(const hkConstraintMotorInput& input, hkConstraintMotorOutput& output) const = 0;   // +8
};

struct hk1dLinearFrictionInfo
{
	hkVector4 m_pivot;                       // +0x00
	hkVector4 m_constrainedDofW;             // +0x10
	hkReal m_maxFrictionForce;               // +0x20
	hkSolverResults* m_lastSolverResults;    // +0x24
};

struct hk1dAngularBilateralConstraintInfo
{
	hkVector4 m_zeroErrorAxisAinW;           // +0x00
	hkVector4 m_constrainedDofW;             // +0x10
	hkVector4 m_perpZeroErrorAxisBinW;       // +0x20
};

struct hk1dLinearBilateralConstraintInfo
{
	hkVector4 m_pivotA;                      // +0x00
	hkVector4 m_pivotB;                      // +0x10
	hkVector4 m_constrainedDofW;             // +0x20
};

struct hk1dLinearLimitInfo
{
	hkVector4 m_pivotA;                      // +0x00
	hkVector4 m_pivotB;                      // +0x10
	hkVector4 m_constrainedDofW;             // +0x20
	hkReal m_min;                            // +0x30
	hkReal m_max;                            // +0x34
};

extern "C" void hkBeginConstraints(const hkConstraintQueryIn& in, hkConstraintQueryOut& out,
                                   hkSolverResults* sr, int solverResultStriding);                        // 0x010AA080
extern "C" void hk1dLinearVelocityMotorBeginJacobian(const hkVector4& dir, const hkVector4& pivot,
                                                     const hkConstraintQueryIn& in, void* jac,
                                                     hkConstraintMotorInput& statusOut);                 // 0x010AC8F0
extern "C" void hk1dLinearVelocityMotorCommitJacobian(hkConstraintMotorOutput& info, const hkConstraintQueryIn& in,
                                                      hkConstraintQueryOut& out);                         // 0x010AA180
extern "C" void hk1dLinearFrictionBuildJacobian(const hk1dLinearFrictionInfo& info, const hkConstraintQueryIn& in,
                                                hkConstraintQueryOut& out);                               // 0x010AA5F0
extern "C" void hk1dAngularBilateralConstraintBuildJacobian(const hk1dAngularBilateralConstraintInfo& info,
                                                            const hkConstraintQueryIn& in,
                                                            hkConstraintQueryOut& out);                   // 0x010AA1E0
extern "C" void hk1dLinearBilateralConstraintBuildJacobian(const hk1dLinearBilateralConstraintInfo& info,
                                                           const hkConstraintQueryIn& in,
                                                           hkConstraintQueryOut& out);                    // 0x010AA890
extern "C" void hk1dLinearLimitBuildJacobian(const hk1dLinearLimitInfo& info, const hkConstraintQueryIn& in,
                                             hkConstraintQueryOut& out);                                  // 0x010AAE10

struct hkPrismaticConstraintDataConstraintBasisA
{
	hkVector4 m_pivot;                  // +0x00
	hkVector4 m_shaft;                  // +0x10
	hkRotation m_BtoAoffsetRotation;    // +0x20
};

struct hkPrismaticConstraintDataConstraintBasisB
{
	hkVector4 m_pivot;                  // +0x00
	hkVector4 m_shaft;                  // +0x10
	hkVector4 m_perpToShaft;            // +0x20
};

class hkConstraintData
{
public:
	virtual ~hkConstraintData();
	int m_memSizeAndFlags_userData[2];  // +0x04
};

class hkPrismaticConstraintData : public hkConstraintData
{
public:
	hkConstraintMotor* m_motor;                             // +0x0c
	hkPrismaticConstraintDataConstraintBasisA m_basisA;     // +0x10
	hkPrismaticConstraintDataConstraintBasisB m_basisB;     // +0x60
	hkReal m_minLimit;                                      // +0x90
	hkReal m_maxLimit;                                      // +0x94
	hkReal m_maxFrictionForce;                              // +0x98
	hkReal m_motorTargetPosition;                           // +0x9c

	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);
};

// @ 0x01092360
void hkPrismaticConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	// frame A in world
	const hkTransform& tA = *in.m_transformA;
	hkVector4 pivotAW;
	setRotatedDir(pivotAW, tA.m_rotation, m_basisA.m_pivot);
	hkVector4 shaftAW;   // computed but unused (the stores survive in the original)
	setRotatedDir(shaftAW, tA.m_rotation, m_basisA.m_shaft);
	hkRotation rotA;
	setRotatedDir(rotA.m_col[0], tA.m_rotation, m_basisA.m_BtoAoffsetRotation.m_col[0]);
	setRotatedDir(rotA.m_col[1], tA.m_rotation, m_basisA.m_BtoAoffsetRotation.m_col[1]);
	setRotatedDir(rotA.m_col[2], tA.m_rotation, m_basisA.m_BtoAoffsetRotation.m_col[2]);
	pivotAW.addTranslation(tA.m_translation);

	// frame B in world
	const hkTransform& tB = *in.m_transformB;
	hkVector4 pivotBW;
	setRotatedDir(pivotBW, tB.m_rotation, m_basisB.m_pivot);
	hkVector4 shaftBW;
	setRotatedDir(shaftBW, tB.m_rotation, m_basisB.m_shaft);
	hkVector4 perpBW;
	setRotatedDir(perpBW, tB.m_rotation, m_basisB.m_perpToShaft);
	pivotBW.addTranslation(tB.m_translation);

	hkPrismaticRuntime* runtime = (hkPrismaticRuntime*)in.m_constraintRuntime;
	if (!runtime->m_initialized) {
		runtime->m_previousTargetPosition = m_motorTargetPosition;
		runtime->m_initialized = true;
	}

	// motor / friction row
	if (m_motor) {
		hkBeginConstraints(in, out, runtime->m_solverResults, 8);
		hkConstraintMotorInput motorIn;
		hk1dLinearVelocityMotorBeginJacobian(shaftBW, pivotAW, in, out.m_jacobians, motorIn);
		const float dx = pivotAW.x - pivotBW.x;
		const float dy = pivotAW.y - pivotBW.y;
		const float dz = pivotAW.z - pivotBW.z;
		motorIn.m_stepInfo = &in;
		motorIn.m_lastResults = runtime->m_solverResults[0];
		motorIn.m_deltaTarget = m_motorTargetPosition - runtime->m_previousTargetPosition;
		motorIn.m_positionError = runtime->m_previousTargetPosition - ((dx * shaftBW.x + shaftBW.z * dz) + shaftBW.y * dy);
		hkConstraintMotorOutput motorOut;
		m_motor->motor(motorIn, motorOut);
		hk1dLinearVelocityMotorCommitJacobian(motorOut, in, out);
		runtime->m_previousTargetPosition = m_motorTargetPosition;
	} else if (m_maxFrictionForce > kZero) {
		hkBeginConstraints(in, out, runtime->m_solverResults, 8);
		hk1dLinearFrictionInfo friction;
		friction.m_pivot = pivotAW;
		friction.m_constrainedDofW = shaftBW;
		friction.m_maxFrictionForce = m_maxFrictionForce;
		friction.m_lastSolverResults = runtime->m_solverResults;
		hk1dLinearFrictionBuildJacobian(friction, in, out);
	} else {
		hkBeginConstraints(in, out, &runtime->m_solverResults[1], 8);
	}

	// angular rows: B's rotation must follow A's offset rotation
	const hkRotation& rotB = in.m_transformB->m_rotation;
	{
		hk1dAngularBilateralConstraintInfo ang;
		ang.m_zeroErrorAxisAinW = rotA.m_col[0];
		ang.m_constrainedDofW = rotA.m_col[2];
		ang.m_perpZeroErrorAxisBinW = rotB.m_col[1];
		hk1dAngularBilateralConstraintBuildJacobian(ang, in, out);
	}
	{
		hk1dAngularBilateralConstraintInfo ang;
		ang.m_zeroErrorAxisAinW = rotA.m_col[1];
		ang.m_constrainedDofW = rotA.m_col[0];
		ang.m_perpZeroErrorAxisBinW = rotB.m_col[2];
		hk1dAngularBilateralConstraintBuildJacobian(ang, in, out);
		ang.m_zeroErrorAxisAinW = rotA.m_col[2];
		ang.m_constrainedDofW = rotA.m_col[1];
		ang.m_perpZeroErrorAxisBinW = rotB.m_col[0];
		hk1dAngularBilateralConstraintBuildJacobian(ang, in, out);
	}

	// linear rows perpendicular to the shaft, at pivot A's projection onto B's shaft
	{
		const float dx = pivotAW.x - pivotBW.x;
		const float dy = pivotAW.y - pivotBW.y;
		const float dz = pivotAW.z - pivotBW.z;
		const float proj = (dx * shaftBW.x + dz * shaftBW.z) + dy * shaftBW.y;

		hk1dLinearBilateralConstraintInfo lin;
		lin.m_pivotA = pivotAW;
		lin.m_pivotB.x = shaftBW.x * proj + pivotBW.x;
		lin.m_pivotB.y = shaftBW.y * proj + pivotBW.y;
		lin.m_pivotB.z = shaftBW.z * proj + pivotBW.z;
		lin.m_pivotB.w = shaftBW.w * proj + pivotBW.w;
		lin.m_constrainedDofW = perpBW;
		hk1dLinearBilateralConstraintBuildJacobian(lin, in, out);

		// m_constrainedDofW = shaftBW x perpBW
		const hkVector4& p = lin.m_constrainedDofW;
		const float ny = shaftBW.z * p.x - p.z * shaftBW.x;
		const float nz = p.y * shaftBW.x - shaftBW.y * p.x;
		const float nx = p.z * shaftBW.y - p.y * shaftBW.z;
		lin.m_constrainedDofW.x = nx;
		lin.m_constrainedDofW.y = ny;
		lin.m_constrainedDofW.z = nz;
		lin.m_constrainedDofW.w = 0.0f;
		hk1dLinearBilateralConstraintBuildJacobian(lin, in, out);
	}

	// linear limit along the shaft
	{
		hk1dLinearLimitInfo limit;
		limit.m_pivotA = pivotAW;
		limit.m_pivotB = pivotBW;
		limit.m_constrainedDofW = shaftBW;
		limit.m_min = m_minLimit;
		limit.m_max = m_maxLimit;
		hk1dLinearLimitBuildJacobian(limit, in, out);
	}
}
