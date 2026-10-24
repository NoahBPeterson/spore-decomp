// Slice s0108eb30: hkWheelConstraintData::buildJacobian (Havok 3.1.0, 0x0108eb30, 2029 bytes).
// Flags: /vc71 /O2 /MD /Gy /TP /fp:fast.
// Layout from the asm: basisA {pivot +0x10, axle +0x20}, basisB {pivot +0x30, steering +0x40, perpSteering +0x50,
// suspension +0x60, perpSuspension +0x70, referenceAxle +0x80 (unused here)}, suspension min/max/strength/damping
// +0x90..+0x9c. Rows: 2 angular bilateral, 2 linear bilateral (pivotB projected on the suspension axis), the
// suspension limit and the user-tau spring row.
#include "types.h"
#include <math.h>

typedef float hkReal;

extern const float kZero;   // 0x01485378

class hkRotation;
class hkTransform;

__declspec(align(16)) class hkVector4
{
public:
	float x, y, z, w;
	__forceinline void addTranslation(const hkVector4& t) { x = x + t.x; y = y + t.y; z = z + t.z; w = t.w; }
	void setRotatedDir(const hkRotation& r, const hkVector4& v);         // 0x010814a0
	void setRotatedInverseDir(const hkRotation& r, const hkVector4& v);  // 0x01081440
	void setTransformedPos(const hkTransform& t, const hkVector4& p);    // 0x01081360
	void setMul(const hkVector4& a, const hkVector4& b);                 // 0x01082210
	void normalize();                                                    // 0x010821a0
};

class hkMatrix3
{
public:
	hkVector4 m_col[3];
};
class hkRotation : public hkMatrix3
{
public:
	void set(const hkVector4& q);                                        // 0x010824a0
};

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

class hkSolverResults
{ public:
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


struct hkWheelInfo4
{
	hkVector4 a, b, c;
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
	hkReal m_min;                            // +0x30 (min / tau)
	hkReal m_max;                            // +0x34 (max / damping)
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
extern "C" void hk1dLinearBilateralConstraintBuildJacobian(const hk1dLinearBilateralConstraintInfo& info,
                                                           const hkConstraintQueryIn& in,
                                                           hkConstraintQueryOut& out);                    // 0x010AA890
extern "C" void hk1dLinearLimitBuildJacobian(const hk1dLinearLimitInfo& info, const hkConstraintQueryIn& in,
                                             hkConstraintQueryOut& out);                                  // 0x010AAE10
extern "C" void hk1dLinearBilateralConstraintUserTauBuildJacobian(const hk1dLinearLimitInfo& info,
                                                                  const hkConstraintQueryIn& in,
                                                                  hkConstraintQueryOut& out);             // 0x010AAB50

struct hkWheelBasisA
{
	hkVector4 m_pivot;   // +0x00
	hkVector4 m_axle;    // +0x10
};
struct hkWheelBasisB
{
	hkVector4 m_pivot;                 // +0x00
	hkVector4 m_steeringAxis;          // +0x10
	hkVector4 m_perpToSteeringAxis;    // +0x20
	hkVector4 m_suspensionAxis;        // +0x30
	hkVector4 m_perpToSuspensionAxis;  // +0x40
	hkVector4 m_referenceAxle;         // +0x50
};

class hkConstraintData
{
public:
	virtual ~hkConstraintData();
	int m_memSizeAndFlags_userData[2];  // +0x04
};

class hkWheelConstraintData : public hkConstraintData
{
public:
	hkWheelBasisA m_basisA;          // +0x10
	hkWheelBasisB m_basisB;          // +0x30
	hkReal m_suspensionMinLimit;     // +0x90
	hkReal m_suspensionMaxLimit;     // +0x94
	hkReal m_suspensionStrength;     // +0x98
	hkReal m_suspensionDamping;      // +0x9c

	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void vslot6();
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);
};

// @ 0x0108eb30
void hkWheelConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	hkBeginConstraints(in, out, (hkSolverResults*)in.m_constraintRuntime, 8);

	const hkTransform& tA = *in.m_transformA;
	hkVector4 pivotAW;
	setRotatedDir(pivotAW, tA.m_rotation, m_basisA.m_pivot);
	pivotAW.addTranslation(tA.m_translation);
	hkVector4 axleAW;
	setRotatedDir(axleAW, tA.m_rotation, m_basisA.m_axle);

	const hkTransform& tB = *in.m_transformB;
	hkVector4 pivotBW;
	setRotatedDir(pivotBW, tB.m_rotation, m_basisB.m_pivot);
	pivotBW.addTranslation(tB.m_translation);
	hkVector4 steerBW;
	setRotatedDir(steerBW, tB.m_rotation, m_basisB.m_steeringAxis);
	hkVector4 perpSteerBW;
	setRotatedDir(perpSteerBW, tB.m_rotation, m_basisB.m_perpToSteeringAxis);
	hkVector4 suspBW;
	setRotatedDir(suspBW, tB.m_rotation, m_basisB.m_suspensionAxis);
	hkVector4 perpSuspBW;
	setRotatedDir(perpSuspBW, tB.m_rotation, m_basisB.m_perpToSuspensionAxis);

	// angular: A's axle against B's steering axis, then its perpendicular
	{
		hk1dAngularBilateralConstraintInfo ang;
		ang.m_zeroErrorAxisAinW = axleAW;
		ang.m_constrainedDofW.x = axleAW.y * steerBW.z - axleAW.z * steerBW.y;
		ang.m_constrainedDofW.y = axleAW.z * steerBW.x - axleAW.x * steerBW.z;
		ang.m_constrainedDofW.z = axleAW.x * steerBW.y - axleAW.y * steerBW.x;
		ang.m_constrainedDofW.w = 0.0f;
		ang.m_perpZeroErrorAxisBinW = steerBW;
		hk1dAngularBilateralConstraintBuildJacobian(ang, in, out);
		ang.m_constrainedDofW.x = -steerBW.x;
		ang.m_constrainedDofW.y = -steerBW.y;
		ang.m_constrainedDofW.z = -steerBW.z;
		ang.m_constrainedDofW.w = 0.0f;
		ang.m_perpZeroErrorAxisBinW = perpSteerBW;
		hk1dAngularBilateralConstraintBuildJacobian(ang, in, out);
	}

	// linear: pivot A against B's pivot projected onto the suspension axis, two perpendicular rows
	{
		hk1dLinearBilateralConstraintInfo lin;
		lin.m_pivotA = pivotAW;
		const double t = ((pivotAW.x - pivotBW.x) * suspBW.x + (pivotAW.z - pivotBW.z) * suspBW.z) +
			(pivotAW.y - pivotBW.y) * suspBW.y;
		lin.m_pivotB.x = (float)(suspBW.x * t + pivotBW.x);
		lin.m_pivotB.y = (float)(suspBW.y * t + pivotBW.y);
		lin.m_pivotB.z = (float)(suspBW.z * t + pivotBW.z);
		lin.m_pivotB.w = (float)(t * 0.0f + pivotBW.w);
		lin.m_constrainedDofW = perpSuspBW;
		hk1dLinearBilateralConstraintBuildJacobian(lin, in, out);
		const hkVector4 d = lin.m_constrainedDofW;
		lin.m_constrainedDofW.x = d.z * suspBW.y - d.y * suspBW.z;
		lin.m_constrainedDofW.y = suspBW.z * d.x - d.z * suspBW.x;
		lin.m_constrainedDofW.z = d.y * suspBW.x - suspBW.y * d.x;
		lin.m_constrainedDofW.w = 0.0f;
		hk1dLinearBilateralConstraintBuildJacobian(lin, in, out);
	}

	// suspension limit, then the spring row
	{
		hk1dLinearLimitInfo lim;
		lim.m_pivotA = pivotAW;
		lim.m_pivotB = pivotBW;
		lim.m_constrainedDofW = suspBW;
		lim.m_min = m_suspensionMinLimit;
		lim.m_max = m_suspensionMaxLimit;
		hk1dLinearLimitBuildJacobian(lim, in, out);
	}
	{
		hk1dLinearLimitInfo spr;
		spr.m_pivotA = pivotAW;
		spr.m_pivotB = pivotBW;
		spr.m_constrainedDofW = suspBW;
		spr.m_min = m_suspensionStrength;
		spr.m_max = m_suspensionDamping;
		hk1dLinearBilateralConstraintUserTauBuildJacobian(spr, in, out);
	}
}

// ===================================================================================================
// shared Havok 3.1 declarations used by the functions below
// ===================================================================================================
typedef hkVector4 hkQuaternion;

class hkMemory
{
public:
	virtual void* allocate(int nbytes, int cl);                       // 0
	virtual void  deallocate(void* p);                                // 1
	virtual void* alignedAllocate(int alignment, int nbytes, int cl); // 2
	virtual void  alignedDeallocate(void* p);                         // 3
	virtual void* allocateChunk(int nbytes, int cl);                  // 4
	virtual void  deallocateChunk(void* p, int nbytes, int cl);       // 5
	static hkMemory* s_instance;                                      // 0x016e4178
};
hkMemory* hkMemory::s_instance;

class hkBool
{
public:
	hkBool() {}
	hkBool(bool b) : m_bool(b ? 1 : 0) {}
	unsigned char m_bool;
};

// ---------------------------------------------------------------------------------------------------------
// constraint motors
// ---------------------------------------------------------------------------------------------------------
class hkConstraintMotorInput
{
public:
	float m_virtualMass;             // +0x00
	hkConstraintQueryIn* m_stepInfo; // +0x04
	hkSolverResults m_lastResults;   // +0x08
	float m_deltaTarget;             // +0x10
	float m_positionError;           // +0x14
};

class hkConstraintMotorOutput
{
public:
	float m_targetPosition;          // +0x00
	float m_targetVelocity;          // +0x04
	float m_minForce;                // +0x08
	float m_maxForce;                // +0x0c
	float m_tau;                     // +0x10
	float m_damping;                 // +0x14
};

class hkConstraintMotor
{
public:
	virtual ~hkConstraintMotor();
	virtual hkConstraintMotor* clone() const;
	virtual void calcMotorData(const hkConstraintMotorInput& in, hkConstraintMotorOutput& out);
	short m_memSizeAndFlags;         // +0x04
	short m_referenceCount;          // +0x06
};

class hkLimitedForceConstraintMotor : public hkConstraintMotor
{
public:
	float m_minForce;                // +0x08
	float m_maxForce;                // +0x0c
};

class hkVelocityConstraintMotor : public hkLimitedForceConstraintMotor
{
public:
	float m_tau;                     // +0x10
	float m_velocityTarget;          // +0x14
	bool m_useVelocityTargetFromConstraintTargets;  // +0x18
	virtual void calcMotorData(const hkConstraintMotorInput& in, hkConstraintMotorOutput& out);
	virtual hkConstraintMotor* clone() const;
};

// @ 0x0108f320
void hkVelocityConstraintMotor::calcMotorData(const hkConstraintMotorInput& in, hkConstraintMotorOutput& out)
{
	if (m_useVelocityTargetFromConstraintTargets)
		out.m_targetVelocity = (in.m_positionError + in.m_deltaTarget) * in.m_stepInfo->m_frameInvDeltaTime;
	else
		out.m_targetVelocity = m_velocityTarget;

	out.m_targetPosition = in.m_lastResults.m_internalSolverData;
	out.m_tau = m_tau;
	out.m_damping = m_tau;
	out.m_minForce = m_maxForce;
	out.m_maxForce = m_minForce;
}

// @ 0x0108f390
hkConstraintMotor* hkVelocityConstraintMotor::clone() const
{
	hkVelocityConstraintMotor* p = (hkVelocityConstraintMotor*)hkMemory::s_instance->allocateChunk(0x1c, 0x29);
	*(const void**)p = (const void*)0x014a1808;
	p->m_memSizeAndFlags = 0x1c;
	p->m_referenceCount = 1;
	p->m_minForce = m_minForce;
	p->m_maxForce = m_maxForce;
	*(const void**)p = (const void*)0x014a181c;
	p->m_tau = m_tau;
	p->m_velocityTarget = m_velocityTarget;
	p->m_useVelocityTargetFromConstraintTargets = m_useVelocityTargetFromConstraintTargets;
	return p;
}

// ---------------------------------------------------------------------------------------------------------
// motions
// ---------------------------------------------------------------------------------------------------------
class hkSweptTransform
{
public:
	hkVector4 m_centerOfMass0;       // +0x00
	hkVector4 m_centerOfMass1;       // +0x10
	hkQuaternion m_rotation0;        // +0x20
	hkQuaternion m_rotation1;        // +0x30
	hkVector4 m_centerOfMassLocal;   // +0x40
};

class hkMotionState
{
public:
	hkTransform m_transform;             // +0x00
	hkSweptTransform m_sweptTransform;   // +0x40
	hkVector4 m_deltaAngle;              // +0x90
	float m_objectRadius;                // +0xa0
	float m_maxLinearVelocity;           // +0xa4
	float m_maxAngularVelocity;          // +0xa8
	unsigned short m_deactivationClass;  // +0xac
	unsigned short m_deactivationCounter;// +0xae
};

class hkStepInfo
{
public:
	float m_startTime;     // +0x00
	float m_endTime;       // +0x04
	float m_deltaTime;     // +0x08
	float m_invDeltaTime;  // +0x0c
};

class hkVelocityAccumulator
{
public:
	unsigned char m_type;              // +0x00
	unsigned char m_pad01[3];
	short m_deactivationClass;         // +0x04
	unsigned char m_pad06[6];
	unsigned char m_flag0c;
	unsigned char m_pad0d[3];
	hkVector4 m_linearVelocity;        // +0x10
	hkVector4 m_angularVelocity;       // +0x20
	hkVector4 m_deltaPosition;         // +0x30
	hkVector4 m_linearVelocity2;       // +0x40
	hkVector4 m_angularVelocity2;      // +0x50
	hkVector4 m_deltaPosition2;        // +0x60
	unsigned int m_pad70[4];           // +0x70
	hkVector4 m_centerOfMass;          // +0x80
};

class hkReferencedMotion
{
public:
	virtual ~hkReferencedMotion();
	short m_memSizeAndFlags;    // +0x04
	short m_referenceCount;     // +0x06
};

class hkMotion : public hkReferencedMotion
{
public:
	virtual int getType() const;
	virtual void step(const hkStepInfo& stepInfo);
	virtual void applyForcesAndStep(const hkStepInfo& s, const hkVector4& d);
	virtual hkVelocityAccumulator* applyForcesAndBuildAccumulator(const hkStepInfo& stepInfo, hkVelocityAccumulator* acc);
	virtual const hkVelocityAccumulator* applyAccumulator(const hkStepInfo& stepInfo, const hkVelocityAccumulator* acc);
	int m_solverData;           // +0x08
};

class hkRigidMotion : public hkMotion
{
public:
	hkMotionState m_motionState;         // +0x10 (16-aligned)
	float m_massInv;                     // +0xc0
	float m_particleMinInertiaDiagInv;   // +0xc4
	float m_linearDamping;               // +0xc8
	float m_angularDamping;              // +0xcc
	hkVector4 m_linearVelocity;          // +0xd0
	hkVector4 m_angularVelocity;         // +0xe0
};

class hkBoxMotion : public hkRigidMotion
{
public:
	hkBoxMotion(const hkVector4& position, const hkVector4& rotation);  // 0x01098140
	hkVector4 m_inertiaAndMassInv;       // +0xf0
};

class hkThinBoxMotion : public hkBoxMotion
{
public:
	hkThinBoxMotion(const hkVector4& position, const hkVector4& rotation);
	virtual const hkVelocityAccumulator* applyAccumulator(const hkStepInfo& stepInfo,
	                                                      const hkVelocityAccumulator* acc);
};

// @ 0x0108f3e0
hkThinBoxMotion::hkThinBoxMotion(const hkVector4& position, const hkVector4& rotation)
	: hkBoxMotion(position, rotation)
{
	*(const void**)this = (const void*)0x014a1838;
}

// @ 0x0108f420
const hkVelocityAccumulator* hkThinBoxMotion::applyAccumulator(const hkStepInfo& stepInfo,
                                                               const hkVelocityAccumulator* acc)
{
	m_linearVelocity = acc->m_linearVelocity2;
	setRotatedDir(m_angularVelocity, m_motionState.m_transform.m_rotation, acc->m_angularVelocity2);

	m_motionState.m_deactivationCounter = (unsigned short)acc->m_deactivationClass;

	// Angular velocity -> body-frame angular momentum -> world space.  The rotation update below
	// re-derives the velocity from this momentum, so it survives the renormalisation unchanged
	// (the "thin" box integration; heavier boxes use the plain hkBoxMotion path).
	hkVector4 bodyAngular;
	bodyAngular.setRotatedInverseDir(m_motionState.m_transform.m_rotation, m_angularVelocity);

	float invIx = 1.0f / m_inertiaAndMassInv.x;
	float invIy = 1.0f / m_inertiaAndMassInv.y;
	float invIz = 1.0f / m_inertiaAndMassInv.z;
	bodyAngular.x = bodyAngular.x * invIx;
	bodyAngular.y = bodyAngular.y * invIy;
	bodyAngular.z = bodyAngular.z * invIz;
	bodyAngular.w = bodyAngular.w * 0.0f;

	hkVector4 worldMomentum;
	worldMomentum.setRotatedDir(m_motionState.m_transform.m_rotation, bodyAngular);

	m_motionState.m_sweptTransform.m_centerOfMass0 = m_motionState.m_sweptTransform.m_centerOfMass1;
	m_motionState.m_sweptTransform.m_centerOfMass0.w = stepInfo.m_startTime;

	float lx = m_linearVelocity.x;
	float ly = m_linearVelocity.y;
	float lz = m_linearVelocity.z;
	float linearVelocitySq = (lx * lx + ly * ly) + lz * lz;
	if (m_motionState.m_maxLinearVelocity * m_motionState.m_maxLinearVelocity < linearVelocitySq) {
		float s = m_motionState.m_maxLinearVelocity / sqrtf(linearVelocitySq);
		m_linearVelocity.x = s * m_linearVelocity.x;
		m_linearVelocity.y = s * m_linearVelocity.y;
		m_linearVelocity.z = s * m_linearVelocity.z;
		m_linearVelocity.w = s * m_linearVelocity.w;
	}

	float dt = stepInfo.m_deltaTime;
	m_motionState.m_sweptTransform.m_centerOfMass1.x = dt * m_linearVelocity.x + m_motionState.m_sweptTransform.m_centerOfMass1.x;
	m_motionState.m_sweptTransform.m_centerOfMass1.y = dt * m_linearVelocity.y + m_motionState.m_sweptTransform.m_centerOfMass1.y;
	m_motionState.m_sweptTransform.m_centerOfMass1.z = dt * m_linearVelocity.z + m_motionState.m_sweptTransform.m_centerOfMass1.z;
	m_motionState.m_sweptTransform.m_centerOfMass1.w = dt * m_linearVelocity.w + m_motionState.m_sweptTransform.m_centerOfMass1.w;
	m_motionState.m_sweptTransform.m_centerOfMass1.w = stepInfo.m_invDeltaTime;

	hkQuaternion rotation = m_motionState.m_sweptTransform.m_rotation1;
	m_motionState.m_sweptTransform.m_rotation0 = rotation;

	float halfDt = dt * 0.5f;
	hkQuaternion delta;
	delta.x = halfDt * m_angularVelocity.x;
	delta.y = halfDt * m_angularVelocity.y;
	delta.z = halfDt * m_angularVelocity.z;

	float angleSq = (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z) * 0.4052847f;

	float maxAngle = m_motionState.m_maxAngularVelocity * dt;
	if (maxAngle > 0.9f)
		maxAngle = 0.9f;
	float maxAngleSq = maxAngle * maxAngle;
	if (angleSq > maxAngleSq) {
		float s = maxAngle / sqrtf(angleSq);
		m_angularVelocity.x = s * m_angularVelocity.x;
		m_angularVelocity.y = s * m_angularVelocity.y;
		m_angularVelocity.z = s * m_angularVelocity.z;
		m_angularVelocity.w = s * m_angularVelocity.w;
		delta.x = s * delta.x;
		delta.y = s * delta.y;
		delta.z = s * delta.z;
		angleSq = maxAngleSq;
	}

	delta.w = ((1.0f - angleSq * 0.822948f) - (angleSq * angleSq) * 0.130529f)
	        - ((angleSq * angleSq) * angleSq) * 0.044408f;

	rotation.setMul(delta, rotation);
	rotation.normalize();

	m_motionState.m_deltaAngle.x = delta.x + delta.x;
	m_motionState.m_deltaAngle.y = delta.y + delta.y;
	m_motionState.m_deltaAngle.z = delta.z + delta.z;
	m_motionState.m_deltaAngle.w = delta.w + delta.w;
	m_motionState.m_deltaAngle.w = sqrtf(angleSq) * 3.1415927f;

	m_motionState.m_sweptTransform.m_rotation1 = rotation;
	m_motionState.m_transform.m_rotation.set(m_motionState.m_sweptTransform.m_rotation1);

	hkVector4 rotatedLocal;
	setRotatedDir(rotatedLocal, m_motionState.m_transform.m_rotation, m_motionState.m_sweptTransform.m_centerOfMassLocal);
	m_motionState.m_transform.m_translation.x = m_motionState.m_sweptTransform.m_centerOfMass1.x - rotatedLocal.x;
	m_motionState.m_transform.m_translation.y = m_motionState.m_sweptTransform.m_centerOfMass1.y - rotatedLocal.y;
	m_motionState.m_transform.m_translation.z = m_motionState.m_sweptTransform.m_centerOfMass1.z - rotatedLocal.z;
	m_motionState.m_transform.m_translation.w = m_motionState.m_sweptTransform.m_centerOfMass1.w;

	m_linearVelocity = acc->m_linearVelocity;

	hkVector4 tmp;
	tmp.setRotatedInverseDir(m_motionState.m_transform.m_rotation, worldMomentum);
	tmp.x = tmp.x * m_inertiaAndMassInv.x;
	tmp.y = tmp.y * m_inertiaAndMassInv.y;
	tmp.z = tmp.z * m_inertiaAndMassInv.z;
	tmp.w = tmp.w * m_inertiaAndMassInv.w;
	m_angularVelocity.setRotatedDir(m_motionState.m_transform.m_rotation, tmp);

	return (const hkVelocityAccumulator*)&acc->m_centerOfMass;
}

// ---------------------------------------------------------------------------------------------------------
// stiff-spring constraints
// ---------------------------------------------------------------------------------------------------------
struct hkConstraintInfo
{
	int m_numSolverResults;    // +0x00
	int m_sizeOfSchema;        // +0x04
	int m_sizeOfRuntime;       // +0x08
	int m_numSolverResults2;   // +0x0c
};

struct RuntimeInfo
{
	int m_size;                // +0x00
	int m_numSolverResults;    // +0x04
};

extern const hkVector4 g_identityBasis_015b9b20;   // 0x015b9b20 (_hk_identityBasis)
extern "C" void _hkReplacePreviousRhs(float rhs, const hkConstraintQueryIn& in,
                                      hkConstraintQueryOut& out, int index);   // 0x010aa050

class hkStiffSpringConstraintData : public hkConstraintData
{
public:
	hkReal m_springLength;   // +0x0c
	hkVector4 m_pivotInA;    // +0x10
	hkVector4 m_pivotInB;    // +0x20
	virtual hkBool isValid() const;
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);
	virtual void getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& info) const;
};

class hkStiffSpringChainData : public hkConstraintData
{
public:
	void* m_infosData;       // +0x0c
	int m_infosSize;         // +0x10
	int m_infosCapacity;     // +0x14
	hkReal m_tau;            // +0x18
	hkReal m_damping;        // +0x1c
	hkReal m_cfm;            // +0x20
	virtual void getConstraintInfo(hkConstraintInfo& info) const;
	virtual void getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& info) const;
};

// @ 0x0108f8d0
void hkStiffSpringConstraintData::getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& info) const
{
	if (wantRuntime.m_bool) {
		info.m_numSolverResults = 1;
		info.m_size = 8;
	} else {
		info.m_numSolverResults = 0;
		info.m_size = 0;
	}
}

// @ 0x0108f900
hkBool hkStiffSpringConstraintData::isValid() const
{
	hkBool result;
	if (m_springLength <= 0.0f) {
		result.m_bool = 0;
		return result;
	}
	result.m_bool = 1;
	return result;
}

// @ 0x0108f950
void hkStiffSpringConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	hkBeginConstraints(in, out, (hkSolverResults*)in.m_constraintRuntime, 8);

	hkVector4 direction;
	hk1dLinearBilateralConstraintInfo lin;
	lin.m_pivotA.setTransformedPos(*in.m_transformA, m_pivotInA);
	lin.m_pivotB.setTransformedPos(*in.m_transformB, m_pivotInB);

	float dx = lin.m_pivotA.x - lin.m_pivotB.x;
	float dy = lin.m_pivotA.y - lin.m_pivotB.y;
	float dz = lin.m_pivotA.z - lin.m_pivotB.z;
	float dw = lin.m_pivotA.w - lin.m_pivotB.w;
	float length = sqrtf(dz * dz + dy * dy + dx * dx);
	float invLength = 1.0f / length;

	direction.x = dx * invLength;
	direction.y = dy * invLength;
	direction.z = dz * invLength;
	direction.w = dw * invLength;

	if (length > 0.0f) {
		lin.m_constrainedDofW = direction;
	} else {
		lin.m_constrainedDofW = g_identityBasis_015b9b20;
		length = 0.0f;
	}

	hk1dLinearBilateralConstraintBuildJacobian(lin, in, out);

	_hkReplacePreviousRhs(m_springLength - length, in, out, 1);
}

// @ 0x0108faa0
void hkStiffSpringChainData::getConstraintInfo(hkConstraintInfo& info) const
{
	info.m_sizeOfSchema = 0;
	info.m_numSolverResults2 = 0;
	info.m_numSolverResults = 0;
	info.m_sizeOfRuntime = 0x18;

	int n = m_infosSize;
	info.m_sizeOfRuntime = n * 4 + 0x2c;
	info.m_sizeOfSchema = (n * 0x40 + 0x13) & ~0xf;
	info.m_numSolverResults2 = n;
}

// @ 0x0108fae0
void hkStiffSpringChainData::getRuntimeInfo(hkBool wantRuntime, RuntimeInfo& info) const
{
	if (wantRuntime.m_bool) {
		int n = m_infosSize;
		info.m_numSolverResults = n;
		info.m_size = n * 8;
	} else {
		info.m_numSolverResults = 0;
		info.m_size = 0;
	}
}
