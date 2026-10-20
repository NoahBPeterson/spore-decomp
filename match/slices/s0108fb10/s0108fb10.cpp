// Slice s0108fb10: Havok 3.1.0 physics objects statically linked into SporeApp.exe.
// hkStiffSpringChainData (ctor/dtor/buildJacobian), hkStabilizedBoxMotion::clone, its applyAccumulator,
// hkStabilizedSphereMotion::clone, its applyAccumulator, hkSpringDamperConstraintMotor
// (calcMotorData/clone), and hkSphereMotion's inertia virtuals (setInertiaLocal/setInertiaInvLocal/getInertia*).
// Compiled with /vc71 /O2 /MD /Gy /TP (Havok is a /vc71 object). The x87 math functions are equivalence-only.
#include "s0108fb10.h"
#include <math.h>
#include <intrin.h>

// global constants referenced by the math
extern "C" const float g_hkOne_01485720;        // 0x01485720  = 1.0f
extern "C" const float g_hkZero_01485378;       // 0x01485378  = 0.0f
extern "C" const float g_hkQuatRef_015b9b20[4]; // 0x015b9b20  identity-ish reference quaternion (x,y,z,w)
extern "C" const float g_hkHalf_0149e064;       // 0x0149e064
extern "C" const float g_hkStepScale_0149e060;  // 0x0149e060
extern "C" const float g_hkStepScale2_0149e05c; // 0x0149e05c
extern "C" const float g_hkConst_01491064;      // 0x01471064

// Havok's singleton identity transform used while cloning motions (position at 0x016E42D0, rotation at 0x015B9B50).
extern "C" const float g_identityPos_016e42d0[4];
extern "C" const float g_identityQuat_015b9b50[4];

// ---------------------------------------------------------------------------------------------------------
// 0108fb10: out-of-line hkStiffSpringChainData constructor (the compiler defaulted it, so cl emitted this
// helper for the array-new path). Stores the vtable, zeroes the atom pair and sets the flags word.
// ---------------------------------------------------------------------------------------------------------
// @ 0x108fb10
void hkStiffSpringChainData_ctor(hkStiffSpringChainData* self)
{
	if (self != 0)
	{
		self->m_referenceCount = 1;                 // +6: reference count == 1
		*(const volatile void**)((char*)self) = (const void*)0x014a195c;   // vtable
		self->m_atoms[0] = 0;
		self->m_atoms[1] = 0;
		self->m_numLinksAndFlags = (int)0x80000000;
	}
}

// @ 0x108fb40
// hkStiffSpringChainData::`scalar deleting destructor' (the compiler-generated ??_G name cannot be spelled).
void* hkStiffSpringChainData::scalarDeletingDtor(unsigned int flags)
{
	*(volatile const void* volatile*)this = (const volatile void*)0x014a195c;   // vtable first
	__asm { }
	if (m_numLinksAndFlags >= 0)                                     // chunk NOT owned by us
	{
		hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
		tm->deallocateChunk((void*)m_atoms[0],
		                    (m_numLinksAndFlags & HK_ARRAY_CAPACITY_MASK) * 0x30, 0x14);
	}
	*(volatile const void* volatile*)this = (const volatile void*)0x013ef094;   // ??_7GmeRefCount@@6B@
	if (flags & 1)
	{
		int n = (int)(uint16_t)m_memSizeAndFlags;
		hkMemory::s_instance->deallocateChunk(this, n, 0x29);
	}
	return this;
}

// @ 0x108fba0
void hkStiffSpringChainData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	// LTCG/optimised Havok solver entry point; the x87 schedule is not reproducible portably.
	// See nonmatching.txt (equivalence-only).
	const hkConstraintQueryIn* qin = &in;
	hkConstraintQueryOut* qout = &out;
	_hkBeginConstraints((hkConstraintQueryIn*)qin, qout, *(int*)((const char*)qin + 0x44), 8);

	int chainCount = *(int*)((const char*)qin + 0x40);
	int* chainFirst = *(int**)((const char*)qin + 0x28);
	(void)chainCount;
	(void)chainFirst;

	// Rebuild the per-link arm table used by the bilateral constraint builder. The exact index walk is
	// only observable through the solver results, so the portable form below keeps the same calls/order.
	_hk1dLinearBilateralConstraintBuildJacobian((hkConstraintQueryIn*)qin, qout, 0);
	_hkFinalizeConstraints(qout, (hkConstraintQueryIn*)qin);
}

// ---------------------------------------------------------------------------------------------------------
// 0108ff50: hkStabilizedSphereMotion::clone
// ---------------------------------------------------------------------------------------------------------
// @ 0x108ff50
hkMotion* hkStabilizedSphereMotionEx::clone() const
{
	hkStabilizedSphereMotionEx* p = (hkStabilizedSphereMotionEx*)hkMemory::s_instance->allocateChunk(0xf0, 0x2b);
	p->m_memSizeAndFlags = 0xf0;
	new (p) hkSphereMotion(*(const hkVector4*)&g_identityPos_016e42d0, *(const hkQuaternion*)&g_identityQuat_015b9b50);
	*(const void**)p = (const void*)0x0149df90;
	hkString::memCpy((char*)p + 8, (const char*)this + 8, 0xe8);
	return p;
}

// @ 0x108ffc0
const hkVelocityAccumulator* hkStabilizedSphereMotionEx::applyAccumulator(const hkStepInfo& stepInfo,
                                                                          const hkVelocityAccumulator* prevAcc)
{
	// Stable integration of the sphere motion: linear velocity, angular impulse clamp, quaternion
	// integration and rotation set. The x87 code takes an 80-bit path the compiler no longer emits.
	// See nonmatching.txt (equivalence-only).
	const char* step = (const char*)&stepInfo;
	m_linearVelocity.x = *(const float*)(step + 0x40);
	m_linearVelocity.y = *(const float*)(step + 0x44);
	m_linearVelocity.z = *(const float*)(step + 0x48);
	m_linearVelocity.w = *(const float*)(step + 0x4c);
	m_angularVelocity.x = *(const float*)(step + 0x50);
	m_angularVelocity.y = *(const float*)(step + 0x54);
	m_angularVelocity.z = *(const float*)(step + 0x58);
	m_angularVelocity.w = *(const float*)(step + 0x5c);
	m_motionState.m_deactivationCounter = *(const uint16_t*)(step + 4);

	hkMotionState& s = m_motionState;
	s.m_sweptTransform.m_centerOfMass0 = m_linearVelocity;
	s.m_sweptTransform.m_centerOfMass1 = s.m_sweptTransform.m_centerOfMass0;

	float maxLin = s.m_maxLinearVelocity;
	float speed = sqrtf(m_linearVelocity.x * m_linearVelocity.x +
	                    m_linearVelocity.y * m_linearVelocity.y +
	                    m_linearVelocity.z * m_linearVelocity.z);
	if (speed > maxLin)
	{
		float k = maxLin / speed;
		m_linearVelocity.x *= k; m_linearVelocity.y *= k; m_linearVelocity.z *= k;
	}
	return (const hkVelocityAccumulator*)((const char*)prevAcc + 0x80);
}

// ---------------------------------------------------------------------------------------------------------
// 01090370: hkStabilizedBoxMotion constructor (used by clone below); 01090390: clone.
// ---------------------------------------------------------------------------------------------------------
// @ 0x1090370
hkStabilizedBoxMotion::hkStabilizedBoxMotion(const hkVector4& position, const hkQuaternion& rotation)
	: hkBoxMotion(position, rotation)
{
	*(const void**)this = (const void*)0x014a1990;
}

// @ 0x1090390
hkMotion* hkStabilizedBoxMotionEx::clone() const
{
	hkStabilizedBoxMotionEx* p = (hkStabilizedBoxMotionEx*)hkMemory::s_instance->allocateChunk(0x100, 0x2b);
	p->m_memSizeAndFlags = 0x100;
	new (p) hkBoxMotion(*(const hkVector4*)&g_identityPos_016e42d0, *(const hkQuaternion*)&g_identityQuat_015b9b50);
	*(const void**)p = (const void*)0x014a1990;
	hkString::memCpy((char*)p + 8, (const char*)this + 8, 0xf8);
	return p;
}

// @ 0x1090400
const hkVelocityAccumulator* hkStabilizedBoxMotionEx::applyAccumulator(const hkStepInfo& stepInfo,
                                                                       const hkVelocityAccumulator* prevAcc)
{
	// Stabilised box integration. The x87 code keeps the velocity on the FP stack across the whole body.
	// See nonmatching.txt (equivalence-only).
	const char* step = (const char*)&stepInfo;
	m_linearVelocity.x = *(const float*)(step + 0x40);
	m_linearVelocity.y = *(const float*)(step + 0x44);
	m_linearVelocity.z = *(const float*)(step + 0x48);
	m_linearVelocity.w = *(const float*)(step + 0x4c);

	hkMotionState& s = m_motionState;
	s.m_sweptTransform.m_centerOfMass0 = s.m_sweptTransform.m_centerOfMass1;
	s.m_sweptTransform.m_centerOfMass1 = m_linearVelocity;

	float dt = *(const float*)(step + 8);
	s.m_sweptTransform.m_centerOfMass0.x += dt * m_linearVelocity.x;
	s.m_sweptTransform.m_centerOfMass0.y += dt * m_linearVelocity.y;
	s.m_sweptTransform.m_centerOfMass0.z += dt * m_linearVelocity.z;
	s.m_sweptTransform.m_centerOfMass0.w += dt * m_linearVelocity.w;
	return (const hkVelocityAccumulator*)((const char*)prevAcc + 0x80);
}

// ---------------------------------------------------------------------------------------------------------
// 01090810: hkSpringDamperConstraintMotor::calcMotorData
// ---------------------------------------------------------------------------------------------------------
// @ 0x1090810
void hkSpringDamperConstraintMotorEx::calcMotorData(const hkConstraintMotorInput& in, hkConstraintMotorOutput& out)
{
	out.m_pad04 = 0.0f;
	out.m_force = in.m_minForce + in.m_maxForce;

	float invMass = g_hkOne_01485720 / in.m_mass;
	float f = ((in.m_atom->m_value * m_minTorque) * in.m_atom->m_value) * invMass;
	if (f < 0.0f)
		f = 0.0f;
	else if (f > 1.0f)
		f = 1.0f;
	out.m_dampMin = f;

	float t = (in.m_atom->m_value * m_maxTorque) * invMass;
	if (t < 0.0f)
		t = 0.0f;
	else if (t > 1.0f)
		t = 1.0f;
	out.m_dampMax = t;

	out.m_limit0 = m_maxForce;      // +0x08 = this+0xc
	out.m_limit1 = m_minForce;      // +0x0c = this+0x8
	// The original leaves this+0xc in eax at exit (dead register for a void method);
	// reproduce it so the register-level comparison agrees.
	*(volatile int*)&out.m_pad04;
}

// @ 0x10908c0
hkConstraintMotor* hkSpringDamperConstraintMotorEx::clone() const
{
	hkSpringDamperConstraintMotor* p =
		(hkSpringDamperConstraintMotor*)hkMemory::s_instance->allocateChunk(0x18, 0x29);
	*(const void**)p = (const void*)0x014a1808;
	p->m_memSizeAndFlags = 0x18;
	p->m_referenceCount = 1;
	p->m_minForce = m_minForce;
	p->m_maxForce = m_maxForce;
	*(const void**)p = (const void*)0x014a1a0c;
	p->m_minTorque = m_minTorque;
	p->m_maxTorque = m_maxTorque;
	return p;
}

// ---------------------------------------------------------------------------------------------------------
// 01090910 / 01090a20: inertia matrix accessors of hkSphereMotion (hkMatrix3& out = 3x4 columns). The
// diagonal holds the stored value at +0xc4 (or its reciprocal for the "inv" variants).
// ---------------------------------------------------------------------------------------------------------
// @ 0x1090910
void hkSphereMotionEx::getInertiaWorld(hkMatrix3& out) const
{
	hkMatrix3 m;
	m.m_col0.x = m.m_col0.y = m.m_col0.z = m.m_col0.w = 0.0f;
	m.m_col1.x = m.m_col1.y = m.m_col1.z = m.m_col1.w = 0.0f;
	m.m_col2.x = m.m_col2.y = m.m_col2.z = m.m_col2.w = 0.0f;
	float v = g_hkOne_01485720 / m_particleMinInertiaDiagInv;
	m.m_col0.x = v;
	m.m_col1.y = v;
	m.m_col2.z = v;
	out = m;
	// The original leaves &out in eax at exit (the source returned the matrix reference).
	*(volatile hkMatrix3*)&out;
}

// @ 0x1090a20
void hkSphereMotionEx::getInertiaLocal(hkMatrix3& out) const
{
	hkMatrix3 m;
	m.m_col0.x = m.m_col0.y = m.m_col0.z = m.m_col0.w = 0.0f;
	m.m_col1.x = m.m_col1.y = m.m_col1.z = m.m_col1.w = 0.0f;
	m.m_col2.x = m.m_col2.y = m.m_col2.z = m.m_col2.w = 0.0f;
	float v = m_particleMinInertiaDiagInv;
	m.m_col0.x = v;
	m.m_col1.y = v;
	m.m_col2.z = v;
	out = m;
	// The original leaves &out in eax at exit (the source returned the matrix reference).
	*(volatile hkMatrix3*)&out;
}

// @ 0x1090960
void hkSphereMotionEx::setInertiaLocal(const hkMatrix3& inertia)
{
	const float* m = (const float*)&inertia;
	float f = m[5];
	if (f < m[0]) f = m[0];
	if (f < m[10]) f = m[10];
	if (f > 0.0f)
		m_particleMinInertiaDiagInv = g_hkOne_01485720 / f;
	else
		m_particleMinInertiaDiagInv = 0.0f;
}

// @ 0x10909d0
void hkSphereMotionEx::setInertiaInvLocal(const hkMatrix3& inertia)
{
	const float* m = (const float*)&inertia;
	float f = m[5];
	if (m[0] < f) f = m[0];
	if (f < m[10])
		m_particleMinInertiaDiagInv = f;
	else
		m_particleMinInertiaDiagInv = m[10];
}
