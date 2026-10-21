#pragma once
// Havok 3.1.0 classes for batch gold3 slice s0108fb10: hkStiffSpringChainData, hkStabilizedBoxMotion /
// hkStabilizedSphereMotion clones, hkSpringDamperConstraintMotor and hkSphereMotion inertia virtuals.
// Reuses the batch b005 Havok declarations (hkMemory, hkReferencedObject, hkMotion, hkRigidMotion,
// hkSphereMotion, hkBoxMotion, hkStabilizedSphereMotion, hkStabilizedBoxMotion, hkMotionState, ...), whic
// already match this slice's layouts (the PDB confirms the same member offsets).
#include "../s010869e0/hk31_world.h"

// ---------------------------------------------------------------------------------------------------------
// hkString: static memory helpers used by the clone methods (FUN_0107f440 = hkString::memCpy).
// ---------------------------------------------------------------------------------------------------------
class hkString
{ public:
	static void* memCpy(void* dst, const void* src, int nbytes);       // 0x0107F440
};

// ---------------------------------------------------------------------------------------------------------
// hkQuaternion helpers (FUN_01082210 = hkQuaternion::setMul, FUN_010821a0 = normalize).
// ---------------------------------------------------------------------------------------------------------
struct hkQuaternionOps
{
	static void setMul(hkQuaternion& out, const hkQuaternion& a, const hkQuaternion& b);   // 0x01082210
	static void normalize(hkQuaternion& q);                                               // 0x010821A0
};
struct hkRotationOps
{
	static void set(hkRotation& out, const hkQuaternion& q);                              // 0x010824A0
};

// ---------------------------------------------------------------------------------------------------------
// thread memory (hkThreadMemory) - deallocateChunk is a non-virtual member called through TLS.
// ---------------------------------------------------------------------------------------------------------
class hkThreadMemory
{
public:
	void deallocateChunk(void* p, int nbytes, int cl);       // 0x0107DB10
};

#if !defined(_WIN32)
extern "C" void* __stdcall TlsGetValue(unsigned long i);
#endif

// ---------------------------------------------------------------------------------------------------------
// constraints
// ---------------------------------------------------------------------------------------------------------
struct hkConstraintQueryIn;         // opaque here (hkConstraintQueryIn fields only used by buildJacobian)
struct hkConstraintQueryOut;

// hkBeginConstraints(in, out, numSolverResults, maxExtra) / hkReplacePreviousRhs / chain build-jacobian
extern "C" void _hkBeginConstraints(hkConstraintQueryIn* in, hkConstraintQueryOut* out, int num, int max);   // 0x010AA080
extern "C" void _hkReplacePreviousRhs(hkConstraintQueryIn* in, hkConstraintQueryOut* out, float rhs, int);    // 0x010AA050
extern "C" void _hkFinalizeConstraints(hkConstraintQueryOut* out, hkConstraintQueryIn* in);                   // 0x010AD0B0
extern "C" void _hk1dLinearBilateralConstraintBuildJacobian(hkConstraintQueryIn* in, hkConstraintQueryOut* out,
                                                            int* numSolverResults);                           // 0x010AA890

// hkStiffSpringChainData: the per-link parameters copied out of the query input.
class hkStiffSpringChainData : public hkReferencedObject
{
public:
	// vtable 0x014A195C (destructor stored there); operator new sits in the base class.
	virtual ~hkStiffSpringChainData();                                                        // 0
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);     // 1 (+4)
	void* scalarDeletingDtor(unsigned int flags);                                             // ??_G body

	int16_t m_pad08[2];                                        // +8
	uint32_t m_atoms[2];                                       // +0xc / +0x10 (chunk pointer + cookie)
	int32_t m_numLinksAndFlags;                                // +0x14 (bits 30..31 are flag bits)
};

// motion step input / accumulator returned by applyAccumulator (opaque: only read by the base class).
class hkStepInfo { public: uint32_t m_pad[0x14]; };            // fields used: +8 deltaTime, +0x40..+0x5f velocities
struct hkVelocityAccumulator;

// This slice owns hkStabilizedSphereMotion::clone/applyAccumulator and hkStabilizedBoxMotion::clone/
// applyAccumulator. The shared b005 header (s010869e0/hk31_world.h) declares those classes with only their
// constructors, so re-declare the methods here through local subclasses that keep the same layout. The
// mangled names therefore carry the local spelling; the shipped symbols are mapped in symbols/slices.
class hkStabilizedSphereMotionEx : public hkStabilizedSphereMotion
{
public:
	virtual hkMotion* clone() const;                                                        // 8 (+0x20)
	virtual const hkVelocityAccumulator* applyAccumulator(const hkStepInfo&, const hkVelocityAccumulator*);  // 6
};
class hkStabilizedBoxMotionEx : public hkStabilizedBoxMotion
{
public:
	virtual hkMotion* clone() const;                                                        // 8 (+0x20)
	virtual const hkVelocityAccumulator* applyAccumulator(const hkStepInfo&, const hkVelocityAccumulator*);  // 6
};

// hkConstraintMotorInput / Output keep the hkSpringDamperConstraintMotor shape.
// hkConstraintMotorInput: {float mass; hkAtom* atom; ...; float minForce@+0x10; float maxForce@+0x14}
struct hkAtom { float m_value; };
struct hkConstraintMotorInput
{
	float m_mass;                      // +0x00
	struct hkAtom* m_atom;             // +0x04 (its first float is the current value)
	uint32_t m_pad08[2];               // +0x08
	float m_minForce;                  // +0x10
	float m_maxForce;                  // +0x14
};
struct hkConstraintMotorOutput
{
	float m_force;                     // +0x00
	float m_pad04;                     // +0x04
	float m_limit0;                    // +0x08 (copied from this+0xc)
	float m_limit1;                    // +0x0c (copied from this+0x8)
	float m_dampMin;                   // +0x10
	float m_dampMax;                   // +0x14
};

class hkConstraintMotor : public hkReferencedObject
{
public:
	virtual ~hkConstraintMotor();                                              // 0
	virtual hkConstraintMotor* clone() const = 0;                              // 1 (+4)
	virtual void calcMotorData(const hkConstraintMotorInput& in, hkConstraintMotorOutput& out) = 0;   // 2 (+8)
};

class hkSpringDamperConstraintMotor : public hkConstraintMotor
{
public:
	float m_minForce;                                          // +0x08
	float m_maxForce;                                          // +0x0c
	float m_minTorque;                                         // +0x10
	float m_maxTorque;                                         // +0x14
};

// The shared header declares these virtuals only in the base classes; the overrides owned by this slice are
// added through thin subclasses that preserve the layout (see the Ex note above).
class hkSpringDamperConstraintMotorEx : public hkSpringDamperConstraintMotor
{
public:
	virtual hkConstraintMotor* clone() const;
	virtual void calcMotorData(const hkConstraintMotorInput& in, hkConstraintMotorOutput& out);
};
class hkSphereMotionEx : public hkSphereMotion
{
public:
	virtual void getInertiaLocal(hkMatrix3& out) const;
	virtual void getInertiaWorld(hkMatrix3& out) const;
	virtual void setInertiaLocal(const hkMatrix3& inertia);
	virtual void setInertiaInvLocal(const hkMatrix3& inertia);
};
