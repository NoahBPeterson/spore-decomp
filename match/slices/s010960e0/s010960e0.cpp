// Havok 3.1.0 slice s010960e0 (0x010960e0..0x0109713C):
//   010960e0  hkKeyframedRigidMotion::applyForcesAndStep
//   010964b0  hkHingeLimitsData::isValid
//   01096640  hkHingeLimitsData::buildJacobian
//   01096b60  hkHingeConstraintData::getRuntimeInfo
//   01096b90  hkHingeConstraintData::isValid
//   01096c70  hkHingeConstraintData::buildJacobian
//   01097110  hkFixedRigidMotion::hkFixedRigidMotion
//   01097130  FUN_01097130
//
// Toolchain: the dev PDB of this build (S_COMPILE) says cl 13.10.3077, i.e. VC .NET 2003, so the slice
// compiles with /vc71 /O2 /MD /Gy /EHsc /TP. Floating point is scalar x87; several intermediate products
// stay on the FPU stack across statements.
//
// Layouts (32-bit, from the disassembly and the PDB):
//   hkReferencedObject 0x08, hkMotion 0x0c, hkRigidMotion 0x10+0xb0 = 0x0f0, hkKeyframedRigidMotion 0x100,
//   hkFixedRigidMotion 0x100 (vtable 0x014A1D08);
//   hkConstraintData 0x0c (vtable +0x0), hkHingeLimitsData 0x70, hkHingeConstraintData 0x60.
#include "types.h"
#include <math.h>

typedef float hkReal;
typedef int16_t hkInt16;
typedef uint16_t hkUint16;
typedef uint32_t hkUint32;

// ---------------------------------------------------------------------------------------------------
// base types
// ---------------------------------------------------------------------------------------------------
// A user-declared constructor makes hkBool non-POD, so MSVC returns it through a hidden pointer
// (the binary's isValid bodies end in `mov byte ptr [eax],1; ret 4`, and hkMath::equal returns it in eax).
class hkBool
{
public:
	hkBool() {}
	char m_bool;
};

class __declspec(align(16)) hkVector4
{
public:
	float x, y, z, w;
	__forceinline void addTranslation(const hkVector4& t) { x = x + t.x; y = y + t.y; z = z + t.z; w = t.w; }
};

class hkMatrix3 { public: hkVector4 m_col0, m_col1, m_col2; };   // 0x30 bytes

class hkQuaternion
{
public:
	float x, y, z, w;
	void setMul(const hkQuaternion& a, const hkQuaternion& b);   // 0x01082210: this = a * b
	void normalize();                                            // 0x010821A0
};

class hkRotation : public hkMatrix3
{
public:
	void set(const hkQuaternion& q);                             // 0x010824A0
};

class hkTransform
{
public:
	hkRotation m_rotation;     // +0x00
	hkVector4 m_translation;   // +0x30
};

class hkStepInfo
{ public:
	float m_startTime;         // +0x00
	float m_endTime;           // +0x04
	float m_deltaTime;         // +0x08
	float m_invDeltaTime;      // +0x0c
};

// d = r * v, with the vector's three components loaded once (the binary's inline rotation idiom)
__forceinline void setRotatedDir(hkVector4& d, const hkRotation& r, const hkVector4& v)
{
	const float vx = v.x, vy = v.y, vz = v.z;
	d.x = (vz * r.m_col2.x + vy * r.m_col1.x) + vx * r.m_col0.x;
	d.y = (vz * r.m_col2.y + vy * r.m_col1.y) + vx * r.m_col0.y;
	d.z = (vz * r.m_col2.z + vy * r.m_col1.z) + vx * r.m_col0.z;
	d.w = 0.0f;
}

// ---------------------------------------------------------------------------------------------------
// motion state
// ---------------------------------------------------------------------------------------------------
class hkSweptTransform                          // 0x50 bytes
{ public:
	hkVector4 m_centerOfMass0;                  // +0x00
	hkVector4 m_centerOfMass1;                  // +0x10
	hkQuaternion m_rotation0;                   // +0x20
	hkQuaternion m_rotation1;                   // +0x30
	hkVector4 m_centerOfMassLocal;              // +0x40
};

class hkMotionState                             // 0xb0 bytes
{ public:
	hkTransform m_transform;                    // +0x00
	hkSweptTransform m_sweptTransform;          // +0x40
	hkVector4 m_deltaAngle;                     // +0x90
	float m_objectRadius;                       // +0xa0
	float m_maxLinearVelocity;                  // +0xa4
	float m_maxAngularVelocity;                 // +0xa8
	hkUint16 m_deactivationClass;               // +0xac
	hkUint16 m_deactivationCounter;             // +0xae
};

// ---------------------------------------------------------------------------------------------------
// motions (vtable slots from the retail vtables: 2 = getType, 4 = applyForcesAndStep, ...)
// ---------------------------------------------------------------------------------------------------
class hkReferencedObject
{
public:
	virtual ~hkReferencedObject();
	hkInt16 m_memSizeAndFlags;                  // +0x04
	hkInt16 m_referenceCount;                   // +0x06
};

class hkVelocityAccumulator;

class hkMotion : public hkReferencedObject
{
public:
	virtual int getType() const;                                                              // 2
	virtual void step(const hkStepInfo& stepInfo);                                            // 3
	virtual void applyForcesAndStep(const hkStepInfo& stepInfo, const hkVector4& delta);      // 4
	virtual void* applyForcesAndBuildAccumulator(const hkStepInfo& stepInfo, hkVelocityAccumulator* acc);   // 5
	virtual void motionSlot6();                                                               // 6
	virtual void motionSlot7();                                                               // 7
	virtual hkMotion* clone() const;                                                          // 8
	virtual void setMass(float m);                                                            // 9
	virtual void setMassInv(float mInv);                                                      // 10
	virtual void getInertiaLocal(hkMatrix3& out) const;                                       // 11
	virtual void getInertiaWorld(hkMatrix3& out) const;                                       // 12
	virtual void setInertiaLocal(const hkMatrix3& inertia);                                   // 13
	virtual void setInertiaInvLocal(const hkMatrix3& inertia);                                // 14
	virtual void getInertiaInvLocal(hkMatrix3& out) const;                                    // 15
	virtual void getInertiaInvWorld(hkMatrix3& out) const;                                    // 16
	virtual void setCenterOfMassInLocal(const hkVector4& com);                                // 17
	virtual void setPosition(const hkVector4& position);                                      // 18
	virtual void setRotation(const hkQuaternion& rotation);                                   // 19
	virtual void setPositionAndRotation(const hkVector4& position, const hkQuaternion& rotation);   // 20
	virtual void setTransform(const hkTransform& transform);                                   // 21
	virtual void setLinearVelocity(const hkVector4& v);                                       // 22
	virtual void setAngularVelocity(const hkVector4& v);                                      // 23
	virtual void applyLinearImpulse(const hkVector4& impulse);                                // 24
	virtual void applyPointImpulse(const hkVector4& impulse, const hkVector4& point);          // 25
	virtual void applyAngularImpulse(const hkVector4& impulse);                               // 26
	virtual void motionSlot27();                                                              // 27
	virtual void motionSlot28();                                                              // 28
	virtual void motionSlot29();                                                              // 29
	virtual void getMotionStateAndVelocities(hkMotion* out);                                   // 30
	int m_solverData;                                                                          // +0x08
};

class hkRigidMotion : public hkMotion
{
public:
	hkRigidMotion(const hkVector4& position, const hkQuaternion& rotation);                   // 0x01088500
	hkMotionState m_motionState;      // +0x10
	float m_massInv;                  // +0xc0
	float m_particleMinInertiaDiagInv;// +0xc4
	float m_linearDamping;            // +0xc8
	float m_angularDamping;           // +0xcc
	hkVector4 m_linearVelocity;       // +0xd0
	hkVector4 m_angularVelocity;      // +0xe0
};

class hkKeyframedRigidMotion : public hkRigidMotion             // vtable 0x014A1C08, size 0x100
{
public:
	hkKeyframedRigidMotion(const hkVector4& position, const hkQuaternion& rotation);          // 0x01095B60
	virtual void applyForcesAndStep(const hkStepInfo& stepInfo, const hkVector4& delta);      // 0x010960E0
	hkMotion* m_savedMotion;                                  // +0xf0
	hkUint32 m_savedQualityTypeAndPad[3];                     // +0xf4..0xff
};

class hkFixedRigidMotion : public hkKeyframedRigidMotion        // vtable 0x014A1D08
{
public:
	hkFixedRigidMotion(const hkVector4& position, const hkQuaternion& rotation);              // 0x01097110
};

// ---------------------------------------------------------------------------------------------------
// constraints
// ---------------------------------------------------------------------------------------------------
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

class hkSolverResults
{ public:
	hkReal m_impulseApplied;        // +0
	hkReal m_internalSolverData;    // +4
};

class hkConstraintData
{
public:
	virtual ~hkConstraintData();
	struct RuntimeInfo
	{
		int m_sizeOfExternalRuntime;   // +0x00
		int m_numSolverResults;        // +0x04
	};
	int m_memSizeAndFlags_userData[2]; // +0x04
};

struct hkHingeLimitsBasisA
{
	hkVector4 m_axle;               // +0x00
	hkVector4 m_perpToAxle1;        // +0x10
	hkVector4 m_perpToAxle2;        // +0x20
};

struct hkHingeLimitsBasisB
{
	hkVector4 m_axle;               // +0x00
	hkVector4 m_perp2FreeAxis;      // +0x10
};

struct hkHingeRuntime                         // in.m_constraintRuntime for hkHingeLimitsData (0x24 bytes)
{
	hkSolverResults m_solverResults[4];   // +0x00
	hkReal m_previousAngle;               // +0x20
};

class hkHingeLimitsData : public hkConstraintData        // 0x70 bytes
{
public:
	hkReal m_minAngle;                  // +0x0c
	hkReal m_maxAngle;                  // +0x10
	hkReal m_maxFrictionTorque;         // +0x14
	hkReal m_angularLimitsTauFactor;    // +0x18
	hkHingeLimitsBasisA m_basisA;       // +0x20
	hkHingeLimitsBasisB m_basisB;       // +0x50

	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual hkBool isValid() const;                                                  // 0x010964B0
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);   // 0x01096640
};

struct hkHingeBasisA
{
	hkVector4 m_pivot;              // +0x00
	hkVector4 m_perpToAxle1;        // +0x10
	hkVector4 m_perpToAxle2;        // +0x20
};

struct hkHingeBasisB
{
	hkVector4 m_pivot;              // +0x00
	hkVector4 m_axle;               // +0x10
};

class hkHingeConstraintData : public hkConstraintData    // 0x60 bytes
{
public:
	hkHingeBasisA m_basisA;             // +0x10
	hkHingeBasisB m_basisB;             // +0x40

	virtual void getRuntimeInfo(hkBool wantRuntime, hkConstraintData::RuntimeInfo& info) const;   // 0x01096B60
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual hkBool isValid() const;                                                  // 0x01096B90
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);   // 0x01096C70
};

// ---------------------------------------------------------------------------------------------------
// solver helpers (outside this slice: declared, resolved by tools/difftest/symbols)
// ---------------------------------------------------------------------------------------------------
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
	hkVector4 m_zeroErrorAxisAinW;      // +0x00
	hkVector4 m_constrainedDofW;        // +0x10
	hkVector4 m_perpZeroErrorAxisBinW;  // +0x20
};

extern "C" void hkBeginConstraints(const hkConstraintQueryIn& in, hkConstraintQueryOut& out,
                                   hkSolverResults* sr, int solverResultStriding);                        // 0x010AA080
extern "C" void hk1dAngularBilateralConstraintBuildJacobian(const hk1dAngularBilateralConstraintInfo& info,
                                                            const hkConstraintQueryIn& in,
                                                            hkConstraintQueryOut& out);                   // 0x010AA1E0
extern "C" void hk1dAngularLimitBuildJacobian(const hk1dAngularLimitInfo& info, const hkConstraintQueryIn& in,
                                              hkConstraintQueryOut& out);                                 // 0x010AB0E0
extern "C" void hkBallSocketBuildJacobian(const hkVector4& pivotA, const hkVector4& pivotB,
                                          const hkConstraintQueryIn& in, hkConstraintQueryOut& out);      // 0x010AB2D0

namespace hkMath
{
	hkBool equal(float a, float b, float eps);      // 0x01080E40
	float atan2fApproximation(float y, float x);    // 0x0120ADB0
}

extern const float kPi;      // 0x014A1CA0
extern const float kTwoPi;   // 0x01446DEC

extern "C" double __cdecl fabs(double);   // 0x00F0DDB6
#pragma intrinsic(fabs)
static float hkAbsF(float v) { return (float)fabs(v); }
static __forceinline float hkLen3sq(const hkVector4& v) { return v.x * v.x + v.y * v.y + v.z * v.z; }

// ===================================================================================================
// hkKeyframedRigidMotion::applyForcesAndStep  (the incoming impulse is unused by this motion)
// ===================================================================================================
// @ 0x010960e0
void hkKeyframedRigidMotion::applyForcesAndStep(const hkStepInfo& stepInfo, const hkVector4& delta)
{
	hkMotionState& ms = m_motionState;

	// previous centre of mass <- current one, stamped with the half-step time
	ms.m_sweptTransform.m_centerOfMass0 = ms.m_sweptTransform.m_centerOfMass1;
	ms.m_sweptTransform.m_centerOfMass0.w = stepInfo.m_startTime;

	// clamp the linear velocity to the motion's maximum
	float lv2 = m_linearVelocity.x * m_linearVelocity.x +
	            m_linearVelocity.y * m_linearVelocity.y +
	            m_linearVelocity.z * m_linearVelocity.z;
	if (lv2 > ms.m_maxLinearVelocity * ms.m_maxLinearVelocity)
	{
		float s = ms.m_maxLinearVelocity / (float)sqrt((double)lv2);
		m_linearVelocity.x = s * m_linearVelocity.x;
		m_linearVelocity.y = s * m_linearVelocity.y;
		m_linearVelocity.z = s * m_linearVelocity.z;
		m_linearVelocity.w = s * m_linearVelocity.w;
	}

	// integrate the centre of mass
	float dt = stepInfo.m_deltaTime;
	ms.m_sweptTransform.m_centerOfMass1.x = dt * m_linearVelocity.x + ms.m_sweptTransform.m_centerOfMass1.x;
	ms.m_sweptTransform.m_centerOfMass1.y = dt * m_linearVelocity.y + ms.m_sweptTransform.m_centerOfMass1.y;
	ms.m_sweptTransform.m_centerOfMass1.z = dt * m_linearVelocity.z + ms.m_sweptTransform.m_centerOfMass1.z;
	ms.m_sweptTransform.m_centerOfMass1.w = dt * m_linearVelocity.w + ms.m_sweptTransform.m_centerOfMass1.w;
	ms.m_sweptTransform.m_centerOfMass1.w = stepInfo.m_invDeltaTime;

	// the motion's rotation becomes the old swept rotation, and the half-angle delta quaternion is built
	// from the angular velocity: q = (0.5 * dt * w, 1) * rotation, normalized, then expanded to an
	// axis/angle pair.
	hkQuaternion rotation = ms.m_sweptTransform.m_rotation1;
	ms.m_sweptTransform.m_rotation0 = rotation;

	float halfDelta = dt * 0.5f;
	hkQuaternion deltaQ;
	deltaQ.x = halfDelta * m_angularVelocity.x;
	deltaQ.y = halfDelta * m_angularVelocity.y;
	deltaQ.z = halfDelta * m_angularVelocity.z;

	float angleSq = (deltaQ.x * deltaQ.x + deltaQ.y * deltaQ.y + deltaQ.z * deltaQ.z) * 0.4052847f;
	float maxAngle = ms.m_maxAngularVelocity * dt;
	if (0.9f < maxAngle)
		maxAngle = 0.9f;
	float maxAngleSq = maxAngle * maxAngle;
	if (angleSq > maxAngleSq)
	{
		float s = maxAngle / (float)sqrt((double)angleSq);
		m_angularVelocity.x = s * m_angularVelocity.x;
		m_angularVelocity.y = s * m_angularVelocity.y;
		m_angularVelocity.z = s * m_angularVelocity.z;
		m_angularVelocity.w = s * m_angularVelocity.w;
		deltaQ.x = deltaQ.x * s;
		deltaQ.y = deltaQ.y * s;
		deltaQ.z = deltaQ.z * s;
		angleSq = maxAngleSq;
	}
	deltaQ.w = ((1.0f - angleSq * 0.822948f) - (angleSq * angleSq) * 0.130529f)
	         - ((angleSq * angleSq) * angleSq) * 0.044408f;

	rotation.setMul(deltaQ, rotation);
	rotation.normalize();

	ms.m_deltaAngle.x = deltaQ.x + deltaQ.x;
	ms.m_deltaAngle.y = deltaQ.y + deltaQ.y;
	ms.m_deltaAngle.z = deltaQ.z + deltaQ.z;
	ms.m_deltaAngle.w = deltaQ.w + deltaQ.w;
	ms.m_deltaAngle.w = (float)sqrt((double)angleSq) * 3.1415927f;

	ms.m_sweptTransform.m_rotation1 = rotation;
	ms.m_transform.m_rotation.set(ms.m_sweptTransform.m_rotation1);

	// rebuild the transform translation from the centre of mass and the local centre of mass offset
	hkVector4 rcom;
	setRotatedDir(rcom, ms.m_transform.m_rotation, ms.m_sweptTransform.m_centerOfMassLocal);
	ms.m_transform.m_translation.x = ms.m_sweptTransform.m_centerOfMass1.x - rcom.x;
	ms.m_transform.m_translation.y = ms.m_sweptTransform.m_centerOfMass1.y - rcom.y;
	ms.m_transform.m_translation.z = ms.m_sweptTransform.m_centerOfMass1.z - rcom.z;
	ms.m_transform.m_translation.w = ms.m_sweptTransform.m_centerOfMass1.w;
}

// ===================================================================================================
// hkHingeLimitsData
// ===================================================================================================
// @ 0x010964b0
hkBool hkHingeLimitsData::isValid() const
{
	hkBool result;
	if (!(hkAbsF(hkAbsF(m_basisA.m_perpToAxle1.x * m_basisA.m_perpToAxle2.x +
	                     m_basisA.m_perpToAxle1.y * m_basisA.m_perpToAxle2.y +
	                     m_basisA.m_perpToAxle1.z * m_basisA.m_perpToAxle2.z)) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	if (!(hkAbsF(hkAbsF(m_basisB.m_perp2FreeAxis.x * m_basisB.m_axle.x +
	                     (m_basisB.m_perp2FreeAxis.y * m_basisB.m_axle.y +
	                      m_basisB.m_perp2FreeAxis.z * m_basisB.m_axle.z))) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	if (!(hkAbsF(hkLen3sq(m_basisA.m_perpToAxle1) - 1.0f) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	if (!(hkAbsF(hkLen3sq(m_basisA.m_perpToAxle2) - 1.0f) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	if (!(hkAbsF(hkLen3sq(m_basisB.m_axle) - 1.0f) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	if (!hkMath::equal(hkLen3sq(m_basisA.m_axle), 1.0f, 1e-05f).m_bool)
	{
		result.m_bool = 0;
		return result;
	}
	float range;
	if (m_minAngle <= 0.0f && m_maxAngle <= 0.0f)
		range = hkAbsF(m_minAngle) + m_maxAngle;
	else
		range = m_maxAngle - m_minAngle;
	if (range > 6.2831855f)
	{
		result.m_bool = 0;
		return result;
	}
	result.m_bool = 1;
	return result;
}

// @ 0x01096640
void hkHingeLimitsData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	hkHingeRuntime* runtime = (hkHingeRuntime*)in.m_constraintRuntime;
	hkBeginConstraints(in, out, runtime->m_solverResults, 8);

	// frame A and frame B in world space
	const hkTransform& tA = *in.m_transformA;
	hkVector4 axleAW;
	setRotatedDir(axleAW, tA.m_rotation, m_basisA.m_axle);
	hkVector4 perp1AW;
	setRotatedDir(perp1AW, tA.m_rotation, m_basisA.m_perpToAxle1);
	hkVector4 perp2AW;
	setRotatedDir(perp2AW, tA.m_rotation, m_basisA.m_perpToAxle2);

	const hkTransform& tB = *in.m_transformB;
	hkVector4 axleBW;
	setRotatedDir(axleBW, tB.m_rotation, m_basisB.m_axle);
	hkVector4 perp2FreeBW;
	setRotatedDir(perp2FreeBW, tB.m_rotation, m_basisB.m_perp2FreeAxis);

	// two angular rows keeping B's axle perpendicular to A's perpendicular axes
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

	// the hinge angle (unwrapped against the previous one) and the angular limit row
	hk1dAngularLimitInfo limit;
	limit.m_constrainedDofW = axleAW;
	limit.m_min = m_minAngle;
	limit.m_max = m_maxAngle;
	limit.m_tau = in.m_tau * m_angularLimitsTauFactor;

	const float cosPart = perp2FreeBW.x * perp1AW.x +
	                      (perp2FreeBW.y * perp1AW.y + perp2FreeBW.z * perp1AW.z);
	const float sinPart = (perp2FreeBW.y * axleBW.z - perp2FreeBW.z * axleBW.y) * perp1AW.x +
	                      ((perp2FreeBW.z * axleBW.x - perp2FreeBW.x * axleBW.z) * perp1AW.y +
	                       (perp2FreeBW.x * axleBW.y - perp2FreeBW.y * axleBW.x) * perp1AW.z);
	float angle = hkMath::atan2fApproximation(cosPart, sinPart);
	if (runtime->m_previousAngle - angle > kPi)
		angle = angle + kTwoPi;
	else if (angle - runtime->m_previousAngle > kPi)
		angle = angle - kTwoPi;
	limit.m_computedAngle = angle;
	runtime->m_previousAngle = angle;
	hk1dAngularLimitBuildJacobian(limit, in, out);
}

// ===================================================================================================
// hkHingeConstraintData
// ===================================================================================================
// @ 0x01096b60
void hkHingeConstraintData::getRuntimeInfo(hkBool wantRuntime, hkConstraintData::RuntimeInfo& info) const
{
	if (wantRuntime.m_bool)
	{
		info.m_numSolverResults = 5;
		info.m_sizeOfExternalRuntime = 0x28;
		return;
	}
	info.m_numSolverResults = 0;
	info.m_sizeOfExternalRuntime = 0;
}

// @ 0x01096b90
hkBool hkHingeConstraintData::isValid() const
{
	hkBool result;
	if (!(hkAbsF(m_basisA.m_perpToAxle1.x * m_basisA.m_perpToAxle2.x +
	             (m_basisA.m_perpToAxle2.y * m_basisA.m_perpToAxle1.y +
	              m_basisA.m_perpToAxle2.z * m_basisA.m_perpToAxle1.z)) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	if (!(hkAbsF(hkLen3sq(m_basisA.m_perpToAxle1) - 1.0f) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	if (!(hkAbsF(hkLen3sq(m_basisA.m_perpToAxle2) - 1.0f) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	if (!(hkAbsF(hkLen3sq(m_basisB.m_axle) - 1.0f) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	result.m_bool = 1;
	return result;
}

// @ 0x01096c70
void hkHingeConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	hkBeginConstraints(in, out, (hkSolverResults*)in.m_constraintRuntime, 8);

	// frame A: pivot and perpendicular axes in world space, pivot translated to A's origin
	const hkTransform& tA = *in.m_transformA;
	hkVector4 perp1AW;
	setRotatedDir(perp1AW, tA.m_rotation, m_basisA.m_perpToAxle1);
	hkVector4 perp2AW;
	setRotatedDir(perp2AW, tA.m_rotation, m_basisA.m_perpToAxle2);
	hkVector4 pivotAW;
	setRotatedDir(pivotAW, tA.m_rotation, m_basisA.m_pivot);
	pivotAW.addTranslation(tA.m_translation);

	// frame B: axle and pivot in world space
	const hkTransform& tB = *in.m_transformB;
	hkVector4 axleBW;
	setRotatedDir(axleBW, tB.m_rotation, m_basisB.m_axle);
	hkVector4 pivotBW;
	setRotatedDir(pivotBW, tB.m_rotation, m_basisB.m_pivot);
	pivotBW.addTranslation(tB.m_translation);

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
}

// ===================================================================================================
// hkFixedRigidMotion
// ===================================================================================================
// @ 0x01097110
hkFixedRigidMotion::hkFixedRigidMotion(const hkVector4& position, const hkQuaternion& rotation)
	: hkKeyframedRigidMotion(position, rotation)
{
}

// ===================================================================================================
// standalone helper: returns its second argument plus 0x80 (an object offset adjustor)
// ===================================================================================================
// @ 0x01097130  FUN_01097130
extern "C" int __stdcall FUN_01097130(int a, int b)
{
	return b + 0x80;
}
