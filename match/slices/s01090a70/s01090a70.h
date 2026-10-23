#pragma once
// Havok 3.1.0 physics classes for slice s01090a70: the hkSphereMotion motion virtuals
// (applyPointImpulse, applyAngularImpulse, a scaled angular-impulse helper, applyForcesAndStep,
// applyForcesAndBuildAccumulator, applyAccumulator, clone), the hkSpatialRigidBodyDeactivator
// constructor and its two deactivation predicates, and hkQuaternion::setMulInverse.
// Compiled with /vc71 /O2 /MD /Gy /TP (Havok is a /vc71 object).
// Reuses the batch b005 Havok declarations (hkMemory, hkReferencedObject, hkMotion, hkRigidMotion,
// hkSphereMotion, hkMotionState, hkSpatialRigidBodyDeactivator, ...), whose member offsets already
// match this slice (verified against the disassembly).
#include "../s010869e0/hk31_world.h"

// ---------------------------------------------------------------------------------------------------------
// hkString: static memory helpers used by clone (FUN_0107F440 = hkString::memCpy).
// ---------------------------------------------------------------------------------------------------------
class hkString
{ public:
	static void* memCpy(void* dst, const void* src, int nbytes);       // 0x0107F440
};

// ---------------------------------------------------------------------------------------------------------
// Quaternion / rotation helpers. 0x01082210 = hkQuaternion::setMul, 0x010821A0 = normalize,
// 0x010824A0 = hkRotation::set. They are ordinary __thiscall members (this = the destination / receiver);
// the wrappers keep that convention so the call sites match the binary.
// ---------------------------------------------------------------------------------------------------------
struct hkQuaternionOps
{
	void setMulInverse(const hkQuaternion& a, const hkQuaternion& b);   // 0x01091970 (this = out)
	void setMul(const hkQuaternion& a, const hkQuaternion& b);         // 0x01082210
	void normalize();                                                  // 0x010821A0
};
struct hkRotationOps
{
	void set(const hkQuaternion& q);                                   // 0x010824A0
};

// ---------------------------------------------------------------------------------------------------------
// hkStepInfo: the integrator reads deltaTime at +8, the swept times at +0/+0xc, and the incoming
// velocities at +0x40/+0x50. Size 0x60.
// ---------------------------------------------------------------------------------------------------------
struct hkStepInfo
{
	float m_startTime;             // +0x00
	float m_endTime;               // +0x04
	float m_deltaTime;             // +0x08
	float m_invDeltaTime;          // +0x0c
	uint32_t m_pad10[0xc];         // +0x10 .. +0x3f
	hkVector4 m_linearVelocity;    // +0x40
	hkVector4 m_angularVelocity;   // +0x50
};

// ---------------------------------------------------------------------------------------------------------
// hkVelocityAccumulator: 0x80 bytes. applyForcesAndBuildAccumulator fills it; applyAccumulator consumes
// the velocity slots and re-projects the motion at the swept time. Field offsets are the binary's.
// ---------------------------------------------------------------------------------------------------------
class hkVelocityAccumulator
{
public:
	uint8_t  m_islandIndex;          // +0x00 (written as 0)
	uint8_t  m_pad01[3];             // +0x01
	uint32_t m_deactivationCounter;  // +0x04 (stored as a 32-bit value)
	uint32_t m_deactivationClass;    // +0x08 (stored as a 32-bit value)
	uint8_t  m_isValid;              // +0x0c (written as 1)
	uint8_t  m_pad0d[3];             // +0x0d
	hkVector4 m_linearVelocity;      // +0x10
	hkVector4 m_angularVelocity;     // +0x20
	hkVector4 m_invMass;             // +0x30 (x,y,z = particleMinInertiaDiagInv, w = massInv)
	hkVector4 m_sweptCenterOfMass;   // +0x40 (center of mass at the swept time)
	hkMatrix3 m_rotation;            // +0x50
};

// ---------------------------------------------------------------------------------------------------------
// hkSphereMotionEx: the shared b005 header declares hkSphereMotion with only its constructor, so the
// virtuals owned by this slice are added through a thin subclass that keeps the layout and the inherited
// vtable slot order (the symbols carry the local spelling; symbols/slices maps them to the shipped VAs).
// ---------------------------------------------------------------------------------------------------------
class hkSphereMotionEx : public hkSphereMotion
{
public:
	virtual void applyPointImpulse(const hkVector4& impulse, const hkVector4& pos);                  // 25 (+0x64)
	virtual void applyAngularImpulse(const hkVector4& impulse);                                     // 26 (+0x68)
	virtual void applyAngularImpulseScaled(float scale, const hkVector4& impulse);                  // 29 (+0x74)
	virtual void applyForcesAndStep(const hkStepInfo& stepInfo, const hkVector4& force);            // 4  (+0x10)
	virtual void* applyForcesAndBuildAccumulator(const hkStepInfo& stepInfo, hkVelocityAccumulator* acc);   // 5
	virtual const hkVelocityAccumulator* applyAccumulator(const hkStepInfo& stepInfo, const hkVelocityAccumulator* acc);   // 6
	virtual hkMotion* clone() const;                                                                // 8  (+0x20)
};

// ---------------------------------------------------------------------------------------------------------
// Raw view of the deactivator layout (the shared header declares the class without members).
// ---------------------------------------------------------------------------------------------------------
struct hkSpatialRigidBodyDeactivatorData
{
	uint32_t m_pad00;              // +0x00 (vptr)
	uint16_t m_memSize;            // +0x04
	uint16_t m_referenceCount;     // +0x06
	uint32_t m_pad08[2];           // +0x08
	hkVector4 m_highFreqPosition;  // +0x10
	hkVector4 m_highFreqRotation;  // +0x20
	hkVector4 m_lowFreqPosition;   // +0x30
	hkVector4 m_lowFreqRotation;   // +0x40
	float m_highFreqTime;          // +0x50  (initialised to -1.0f)
	float m_highFreqLinearThreshold;   // +0x54
	float m_highFreqAngularThreshold;  // +0x58
	float m_lowFreqLinearThreshold;    // +0x5c
	float m_lowFreqAngularThreshold;   // +0x60
};
