// Slice s010938e0 (part 2): Havok 3.1.0 constraint motors and the point-to-plane / point-to-path
// constraint datasets (0x01094210..0x010944E1).  The code is x87 (the Havok libraries were built with
// VC7.1), hence the /vc71 flag.
//
//  01094210  hkPositionConstraintMotor::calcMotorData   (motor force limits, position recovery, clamping)
//  010942E0  hkPositionConstraintMotor::clone
//  01094360  hkPointToPlaneConstraintData::isValid      (plane equation must be normalised)
//  010943B0  hkPointToPlaneConstraintData::buildJacobian
//  01094470  compiler-generated scalar deleting destructor of hkPointToPathConstraintData
//  010944C0  hkPointToPathConstraintData::isValid
//
// Layouts below are read off the asm; the constraint motor hierarchy is the same one that
// slices/s0108eb30 reconstructs (its hkVelocityConstraintMotor::clone is byte-exact).
#include "types.h"
#include <stddef.h>
#include <math.h>

typedef float hkReal;

#define CHK(cls, name, off) typedef char chk_##cls##_##name[(offsetof(cls, name) == (off)) ? 1 : -1]

// ---------------------------------------------------------------------------------------------------
// basic Havok types
// ---------------------------------------------------------------------------------------------------
// A user-declared constructor keeps this non-POD so that it is returned through a hidden pointer.
class hkBool
{
public:
	hkBool() {}
	hkBool(bool b) : m_bool(b) {}
	operator bool() const { return m_bool != 0; }
	bool m_bool;
};

class hkRotation;
class hkTransform;

__declspec(align(16)) class hkVector4
{
public:
	float x, y, z, w;
	void setTransformedPos(const hkTransform& t, const hkVector4& p);    // 0x01081360
	void setRotatedDir(const hkRotation& r, const hkVector4& v);         // 0x010814a0
	hkBool isNormalized3(hkReal tolerance) const;                        // 0x010812f0
};

class hkMatrix3
{
public:
	hkVector4 m_col[3];
};
class hkRotation : public hkMatrix3
{
};
class hkTransform
{
public:
	hkRotation m_rotation;      // +0x00
	hkVector4 m_translation;    // +0x30
};

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
hkMemory* hkMemory::s_instance;                                       // 0x016e4178

class hkReferencedObject
{
public:
	virtual ~hkReferencedObject() {}
	void removeReference()
	{
		if (m_memSizeAndFlags != 0)
		{
			if (--m_referenceCount == 0)
				delete this;
		}
	}
	unsigned short m_memSizeAndFlags;   // +0x04
	short m_referenceCount;             // +0x06
};

class hkSolverResults
{
public:
	hkReal m_impulseApplied;      // +0x00
	hkReal m_internalSolverData;  // +0x04
};

class hkConstraintQueryIn
{
public:
	float m_substepDeltaTime;         // +0x00
	float m_substepInvDeltaTime;      // +0x04
	float m_frameDeltaTime;           // +0x08
	float m_frameInvDeltaTime;        // +0x0c
	float m_virtualMassFactor;        // +0x10
	float m_rhsFactor;                // +0x14
	float m_dampingFactor;            // +0x18
	float m_frictionRhsFactor;        // +0x1c
	void* m_accumulatorBufferRoot;    // +0x20
	void* m_jacobianBufferRoot;       // +0x24
	void* m_bodyA;                    // +0x28
	void* m_bodyB;                    // +0x2c
	hkTransform* m_transformA;        // +0x30
	hkTransform* m_transformB;        // +0x34
	float m_tau;                      // +0x38
	float m_damping;                  // +0x3c
	void* m_constraintInstance;       // +0x40
	void* m_constraintRuntime;        // +0x44
};

class hkConstraintQueryOut
{
public:
	void* m_jacobians;          // +0x00
	void* m_jacobianSchemas;    // +0x04
};

struct hk1dLinearBilateralConstraintInfo
{
	hkVector4 m_pivotA;              // +0x00
	hkVector4 m_pivotB;              // +0x10
	hkVector4 m_constrainedDofW;     // +0x20
};

extern "C" void hkBeginConstraints(const hkConstraintQueryIn& in, hkConstraintQueryOut& out,
                                   hkSolverResults* sr, int solverResultStriding);              // 0x010AA080
extern "C" void hk1dLinearBilateralConstraintBuildJacobian(const hk1dLinearBilateralConstraintInfo& info,
                                                           const hkConstraintQueryIn& in,
                                                           hkConstraintQueryOut& out);          // 0x010AA890

// ---------------------------------------------------------------------------------------------------
// constraint motors
// ---------------------------------------------------------------------------------------------------
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

class hkPositionConstraintMotor : public hkLimitedForceConstraintMotor
{
public:
	float m_tau;                              // +0x10
	float m_damping;                          // +0x14
	float m_proportionalRecoveryVelocity;     // +0x18
	float m_constantRecoveryVelocity;         // +0x1c
	virtual void calcMotorData(const hkConstraintMotorInput& in, hkConstraintMotorOutput& out);
	virtual hkConstraintMotor* clone() const;
};
CHK(hkLimitedForceConstraintMotor, m_minForce, 0x08);
CHK(hkLimitedForceConstraintMotor, m_maxForce, 0x0c);
CHK(hkPositionConstraintMotor, m_tau, 0x10);
CHK(hkPositionConstraintMotor, m_damping, 0x14);
CHK(hkPositionConstraintMotor, m_proportionalRecoveryVelocity, 0x18);
CHK(hkPositionConstraintMotor, m_constantRecoveryVelocity, 0x1c);
CHK(hkConstraintMotorInput, m_stepInfo, 0x04);
CHK(hkConstraintMotorInput, m_lastResults, 0x08);
CHK(hkConstraintMotorInput, m_deltaTarget, 0x10);
CHK(hkConstraintMotorInput, m_positionError, 0x14);
CHK(hkConstraintMotorOutput, m_targetVelocity, 0x04);
CHK(hkConstraintMotorOutput, m_minForce, 0x08);
CHK(hkConstraintMotorOutput, m_maxForce, 0x0c);
CHK(hkConstraintMotorOutput, m_tau, 0x10);
CHK(hkConstraintMotorOutput, m_damping, 0x14);

// @ 0x01094210
void hkPositionConstraintMotor::calcMotorData(const hkConstraintMotorInput& in, hkConstraintMotorOutput& out)
{
	// The motor drives with a symmetric force window around m_maxForce (the sign convention of the
	// impulse makes the lower limit the positive one).
	const hkReal maxForce = m_maxForce;
	out.m_minForce = maxForce;
	out.m_maxForce = -maxForce;
	out.m_tau = m_tau;
	out.m_damping = m_damping;

	const hkReal error = in.m_positionError;
	// Proportional recovery: move at most m_proportionalRecoveryVelocity * error per frame.
	const hkReal correction = error * m_proportionalRecoveryVelocity * in.m_stepInfo->m_frameDeltaTime;
	const hkReal delta = error - correction;
	const hkReal maxCorrection = m_constantRecoveryVelocity * in.m_stepInfo->m_frameDeltaTime;

	// If the proportional correction still leaves more than one constant step of error, step from the
	// correction by the constant recovery amount in the direction of the error; otherwise the target
	// stays at the raw position error.
	hkReal target = error;
	if (fabsf(delta) > maxCorrection)
		target = correction + (delta <= 0.0f ? -maxCorrection : maxCorrection);

	// Clamp against the solver's own idea of where the body may go this step.
	const hkReal upper = fabsf(error) - in.m_lastResults.m_internalSolverData;
	const hkReal lower = -fabsf(error) - in.m_lastResults.m_internalSolverData;
	if (target < lower)
		target = lower;
	else if (target > upper)
		target = upper;

	out.m_targetVelocity = (target + in.m_deltaTarget) * in.m_stepInfo->m_frameInvDeltaTime;
	out.m_targetPosition = in.m_lastResults.m_internalSolverData;
}

// @ 0x010942e0
hkConstraintMotor* hkPositionConstraintMotor::clone() const
{
	hkPositionConstraintMotor* p = (hkPositionConstraintMotor*)hkMemory::s_instance->allocateChunk(0x20, 0x29);
	*(const void**)p = (const void*)0x014a1808;      // hkConstraintMotor vtable
	p->m_memSizeAndFlags = 0x20;
	p->m_referenceCount = 1;
	p->m_minForce = m_minForce;
	p->m_maxForce = m_maxForce;
	*(const void**)p = (const void*)0x014a1b14;      // hkPositionConstraintMotor vtable
	p->m_tau = m_tau;
	p->m_damping = m_damping;
	p->m_proportionalRecoveryVelocity = m_proportionalRecoveryVelocity;
	p->m_constantRecoveryVelocity = m_constantRecoveryVelocity;
	return p;
}

// ---------------------------------------------------------------------------------------------------
// point-to-plane constraint data
// ---------------------------------------------------------------------------------------------------
class hkPointToPlaneConstraintData : public hkReferencedObject
{
public:
	virtual hkBool isValid() const;
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);
	void* mpUnk08;              // +0x08
	void* mpUnk0c;              // +0x0c
	hkVector4 m_pointA;         // +0x10  (in A's space)
	hkVector4 m_pointB;         // +0x20  (in B's space)
	hkVector4 m_planeNormal;    // +0x30  (in A's space)
};
CHK(hkPointToPlaneConstraintData, m_pointA, 0x10);
CHK(hkPointToPlaneConstraintData, m_pointB, 0x20);
CHK(hkPointToPlaneConstraintData, m_planeNormal, 0x30);

// @ 0x01094360
hkBool hkPointToPlaneConstraintData::isValid() const
{
	return m_planeNormal.isNormalized3(0.0001f);
}

// @ 0x010943b0
void hkPointToPlaneConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	hkBeginConstraints(in, out, (hkSolverResults*)in.m_constraintRuntime, 8);

	hk1dLinearBilateralConstraintInfo info;
	info.m_pivotA.setTransformedPos(*in.m_transformA, m_pointA);
	info.m_pivotB.setTransformedPos(*in.m_transformB, m_pointB);
	info.m_constrainedDofW.setRotatedDir(in.m_transformA->m_rotation, m_planeNormal);

	hk1dLinearBilateralConstraintBuildJacobian(info, in, out);
}

// ---------------------------------------------------------------------------------------------------
// point-to-path constraint data
// ---------------------------------------------------------------------------------------------------
class hkPointToPathConstraintData : public hkReferencedObject
{
public:
	virtual hkBool isValid() const;
	void* mpUnk08;                  // +0x08
	hkReferencedObject* m_path;     // +0x0c  (the path curve, reference counted)
	int m_unk10;                    // +0x10
	unsigned char m_validFlag;      // +0x14
};
CHK(hkPointToPathConstraintData, m_path, 0x0c);
CHK(hkPointToPathConstraintData, m_validFlag, 0x14);

// @ 0x010944c0
hkBool hkPointToPathConstraintData::isValid() const
{
	return hkBool(m_path != 0 && m_validFlag != 0);
}

// The compiler-generated scalar deleting destructor of hkPointToPathConstraintData.  MSVC only emits it
// as a side effect of the virtual destructor, so it is reconstructed here as a plain member of the same
// object layout: publish the class vtable, drop the path reference, publish the base vtable and finally
// hand the block back to the chunk allocator when the deleting flag is set.
struct hkPointToPathLayout
{
	void* mpVtbl;                       // +0x00
	unsigned short m_memSizeAndFlags;   // +0x04
	short m_referenceCount;             // +0x06
	void* mpUnk08;                      // +0x08
	hkReferencedObject* m_path;         // +0x0c
	int m_unk10;                        // +0x10
	unsigned char m_validFlag;          // +0x14
	void* scalarDeletingDestructor(unsigned int flags);
};
CHK(hkPointToPathLayout, m_memSizeAndFlags, 0x04);
CHK(hkPointToPathLayout, m_referenceCount, 0x06);
CHK(hkPointToPathLayout, m_path, 0x0c);

// @ 0x01094470
void* hkPointToPathLayout::scalarDeletingDestructor(unsigned int flags)
{
	mpVtbl = (void*)0x014a1b64;         // hkPointToPathConstraintData vtable
	if (m_path != 0)
		m_path->removeReference();
	mpVtbl = (void*)0x013ef094;         // hkReferencedObject vtable
	if ((flags & 1) != 0)
		hkMemory::s_instance->deallocateChunk(this, m_memSizeAndFlags, 0x29);
	return this;
}
