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
// hkQuaternion / hkRotation / hkVector4 helpers. They are __thiscall members in Havok (receiver in ecx, the
// arguments on the stack and popped by the callee), declared __fastcall with a dummy edx slot so the call
// sites keep the callee-pops shape the retail code uses.
// ---------------------------------------------------------------------------------------------------------
void __fastcall hkQuaternion_setMul(hkQuaternion* out, int, const hkQuaternion* a, const hkQuaternion* b);   // 0x01082210
void __fastcall hkQuaternion_normalize(hkQuaternion* q, int);                                               // 0x010821A0
void __fastcall hkRotation_set(hkRotation* out, int, const hkQuaternion* q);                                // 0x010824A0
void __fastcall hkVector4_setTransformedPos(hkVector4* out, int, const hkTransform* t, const hkVector4* p); // 0x01081360

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
// x87 math constants read by the stabilised motions (absolute addresses of the retail image). The two
// 1/12 < x < 1 values at 0x0149E060 / 0x0149E05C are *derived* constants: the compiler folded
// 2*pi/24 and (2*pi/24)^2, so their initialiser has to come from sqrtf() to land on the same bits.
// ---------------------------------------------------------------------------------------------------------
extern "C" const float g_hkOne_01485720;        // 0x01485720 = 1.0f
extern "C" const float g_hkHalf_0149e064;       // 0x0149E064 = 0.5f
extern "C" const float g_hkStepScale_0149e060;  // 0x0149E060 = (2*pi/24)^2
extern "C" const float g_hkStepScale2_0149e05c; // 0x0149E05C = 2*pi/24
extern "C" const float g_hkAngleScale_0149e068; // 0x0149E068 = 1/((2*pi/24)^2)
extern "C" const float g_hkMaxAngle_013ec4b4;   // 0x013EC4B4 = 0.9f
extern "C" const float g_hkPi_014a1984;         // 0x014A1984 = pi (stabilised sphere)
extern "C" const float g_hkPi_014a1988;         // 0x014A1988 = pi (stabilised box)

// ---------------------------------------------------------------------------------------------------------
// step info / velocity accumulator (layouts from the dev PDB; the accumulator is read by applyAccumulator)
// ---------------------------------------------------------------------------------------------------------
struct hkStepInfo
{
	float m_startTime;      // +0x00
	float m_endTime;        // +0x04
	float m_deltaTime;      // +0x08
	float m_invDeltaTime;   // +0x0c
};

class hkVelocityAccumulator
{
public:
	unsigned char m_type;              // +0x00
	unsigned char m_pad01[3];
	int16_t m_deactivationClass;       // +0x04
	unsigned char m_pad06[6];
	unsigned char m_flag0c;            // +0x0c
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

// ---------------------------------------------------------------------------------------------------------
// constraint solver queries: hkConstraintQueryStepInfo (0x20) + hkConstraintQueryIn (0x48, dev PDB layout)
// ---------------------------------------------------------------------------------------------------------
struct hkConstraintQueryStepInfo
{
	float m_substepDeltaTime;       // +0x00
	float m_substepInvDeltaTime;    // +0x04
	float m_frameDeltaTime;         // +0x08
	float m_frameInvDeltaTime;      // +0x0c
	float m_invNumSteps;            // +0x10
	float m_rhsFactor;              // +0x14
	float m_virtMassFactor;         // +0x18
	float m_frictionRhsFactor;      // +0x1c
};

class hkConstraintQueryIn : public hkConstraintQueryStepInfo
{
public:
	hkVelocityAccumulator* m_accumulatorBufferRoot;   // +0x20
	void* m_jacobianBufferRoot;                       // +0x24
	hkVelocityAccumulator* m_bodyA;                   // +0x28
	hkVelocityAccumulator* m_bodyB;                   // +0x2c
	hkTransform* m_transformA;                        // +0x30
	hkTransform* m_transformB;                        // +0x34
	float m_tau;                                      // +0x38
	float m_damping;                                  // +0x3c
	void* m_constraintInstance;                       // +0x40
	void* m_constraintRuntime;                        // +0x44
};

// Both members are cursors into the solver's output buffers, advanced by the row builders.
class hkConstraintQueryOut
{
public:
	void* m_jacobians;          // +0x00
	void* m_jacobianSchemas;    // +0x04
};

class hk1dLinearBilateralConstraintInfo
{
public:
	hkVector4 m_pivotA;            // +0x00
	hkVector4 m_pivotB;            // +0x10
	hkVector4 m_constrainedDofW;   // +0x20
};

// hkConstraintInstance / hkConstraintChainInstance (dev PDB layouts, 32-bit pointers). Only the entity array
// of the chain instance is read by buildJacobian.
class hkConstraintInstance : public hkReferencedObject
{
public:
	void* m_owner;                     // +0x08
	void* m_data;                      // +0x0c
	hkEntity* m_entities[2];           // +0x10
	unsigned char m_priority;          // +0x18
	unsigned char m_wantRuntime;       // +0x19
	unsigned char m_pad1a[2];
	char* m_name;                      // +0x1c
	unsigned int m_userData;           // +0x20
	void* m_internal;                  // +0x24
};

class hkConstraintChainInstance : public hkConstraintInstance
{
public:
	hkArray<hkEntity*> m_chainedEntities;   // +0x28
	void* m_action;                         // +0x34
};

// Solver helpers called by the chain buildJacobian (cdecl, caller cleans the stack).
extern "C" void _hkBeginConstraints(const hkConstraintQueryIn& in, hkConstraintQueryOut& out,
                                    const void* solverResults, int solverResultStriding);       // 0x010AA080
extern "C" void _hk1dLinearBilateralConstraintBuildJacobian(const hk1dLinearBilateralConstraintInfo& info,
                                                            const hkConstraintQueryIn& in,
                                                            hkConstraintQueryOut& out);         // 0x010AA890
extern "C" void _hkReplacePreviousRhs(float rhs, const hkConstraintQueryIn& in,
                                      hkConstraintQueryOut& out, int index);                    // 0x010AA050
extern "C" void _hkFinalizeConstraints(int numRows, float tau, float damping, float cfm,
                                       const int* bodyIndices, const void* rowBase, void* jacobianRows,
                                       const hkConstraintQueryIn& in, hkConstraintQueryOut& out); // 0x010AD0B0
// Bare `ret` in this build: an empty hook the solver still calls with the query.
extern "C" void _hkConstraintQueryBegin(hkConstraintQueryIn& in);                               // 0x00C2E4E0

// hkStiffSpringChainData: the per-link atoms (pivot pair + rest length) and the stiffness parameters.
class hkStiffSpringChainAtom
{
public:
	hkVector4 m_pivotA;        // +0x00 (in the previous body's local frame)
	hkVector4 m_pivotB;        // +0x10 (in the next body's local frame)
	float m_length;            // +0x20 rest length of the link
	float m_pad24[3];
};

class hkStiffSpringChainData : public hkReferencedObject
{
public:
	// vtable 0x014A195C (destructor stored there); operator new sits in the base class.
	virtual ~hkStiffSpringChainData();                                                        // 0
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);     // 1 (+4)
	void* scalarDeletingDtor(unsigned int flags);                                             // ??_G body

	int16_t m_pad08[2];                                        // +8
	hkArray<hkStiffSpringChainAtom> m_atoms;                   // +0xc (data / size / capacityAndFlags)
	float m_tau;                                               // +0x18
	float m_damping;                                           // +0x1c
	float m_cfm;                                               // +0x20
};

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
