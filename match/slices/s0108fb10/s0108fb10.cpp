// Slice s0108fb10: Havok 3.1.0 physics objects statically linked into SporeApp.exe.
// hkStiffSpringChainData (ctor/dtor/buildJacobian), hkStabilizedBoxMotion::clone, its applyAccumulator,
// hkStabilizedSphereMotion::clone, its applyAccumulator, hkSpringDamperConstraintMotor
// (calcMotorData/clone), and hkSphereMotion's inertia virtuals (setInertiaLocal/setInertiaInvLocal/getInertia*).
// Compiled with /vc71 /O2 /MD /Gy /TP (Havok is a /vc71 object). The x87 math functions are equivalence-only.
#include "s0108fb10.h"
#include <math.h>
#include <intrin.h>

// global constants referenced by the math (the ones used by the stabilised motions are declared in the header)
extern "C" const float g_hkZero_01485378;       // 0x01485378  = 0.0f
extern "C" const float g_hkQuatRef_015b9b20[4]; // 0x015b9b20  identity-ish reference quaternion (x,y,z,w)
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
		self->m_atoms.m_data = 0;
		self->m_atoms.m_size = 0;
		self->m_atoms.m_capacityAndFlags = (int)0x80000000;
	}
}

// @ 0x108fb40
// hkStiffSpringChainData::`scalar deleting destructor' (the compiler-generated ??_G name cannot be spelled).
void* hkStiffSpringChainData::scalarDeletingDtor(unsigned int flags)
{
	*(volatile const void* volatile*)this = (const volatile void*)0x014a195c;   // vtable first
	__asm { }
	if (m_atoms.m_capacityAndFlags >= 0)                             // chunk NOT owned by us
	{
		hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
		tm->deallocateChunk((void*)m_atoms.m_data,
		                    (m_atoms.m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) * 0x30, 0x14);
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
// hkStiffSpringChainData::buildJacobian: one bilateral distance row per link, solved against the solvers'
// velocity accumulators. The chain instance stores the linked entities; their motions carry the per-body
// solver indices the solver expects, so the offsets array collects those (rebased with the chunk base) and
// the finalize call hands the whole row table to the solver.
void hkStiffSpringChainData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	_hkBeginConstraints(in, out, in.m_constraintRuntime, 8);

	// Per-link sub-query: same step scaling as the caller, but without the chain instance/runtime.
	hkConstraintQueryIn query = in;
	query.m_constraintInstance = 0;
	query.m_constraintRuntime = 0;
	query.m_rhsFactor = query.m_substepInvDeltaTime;
	query.m_virtMassFactor = 1.0f;

	const hkConstraintChainInstance* instance = (const hkConstraintChainInstance*)in.m_constraintInstance;
	void* jacobianRows = out.m_jacobians;          // every link row rewinds to this cursor
	void* jacobianSchemas = out.m_jacobianSchemas;

	// The solver stores body indices relative to the accumulator block: subtract the first body's index to get
	// the chunk base and add it back when the finalize call needs the row base.
	const hkMotion* firstMotion = instance->m_entities[0]->m_motion;
	const char* chunkBase = (const char*)in.m_bodyA - firstMotion->m_solverData;

	// Body indices of the link ends: the first body, then one entry per link (32 slots live on the stack).
	int inlineIndices[32];
	hkArray<int> bodyIndices;
	bodyIndices.m_data = inlineIndices;
	bodyIndices.m_size = 1;
	bodyIndices.m_capacityAndFlags = (int)0x80000020;   // 32 elements, buffer not owned
	inlineIndices[0] = firstMotion->m_solverData;

	const int numLinks = instance->m_chainedEntities.m_size - 1;
	const hkStiffSpringChainAtom* atom = m_atoms.m_data;
	const hkMotionState* previousState = &((const hkRigidMotion*)firstMotion)->m_motionState;

	for (int i = 0; i < numLinks; ++i)
	{
		const hkMotion* nextMotion = instance->m_chainedEntities.m_data[i + 1]->m_motion;
		bodyIndices.pushBack(nextMotion->m_solverData);
		const hkMotionState* nextState = &((const hkRigidMotion*)nextMotion)->m_motionState;

		// link axis = world pivot on the previous body - world pivot on the next body
		hk1dLinearBilateralConstraintInfo linear;
		hkVector4_setTransformedPos(&linear.m_pivotA, 0, &previousState->m_transform, &atom[i].m_pivotA);
		hkVector4_setTransformedPos(&linear.m_pivotB, 0, &nextState->m_transform, &atom[i].m_pivotB);

		const float dx = linear.m_pivotA.x - linear.m_pivotB.x;
		const float dy = linear.m_pivotA.y - linear.m_pivotB.y;
		const float dz = linear.m_pivotA.z - linear.m_pivotB.z;
		const float dw = linear.m_pivotA.w - linear.m_pivotB.w;

		float length = sqrtf(dz * dz + dy * dy + dx * dx);
		const float invLength = 1.0f / length;
		hkVector4 direction;
		direction.x = dx * invLength;
		direction.y = dy * invLength;
		direction.z = dz * invLength;
		direction.w = dw * invLength;

		if (length > 0.0f)
		{
			linear.m_constrainedDofW = direction;
		}
		else
		{
			// coincident pivots: fall back to the identity axis
			linear.m_constrainedDofW = *(const hkVector4*)&g_hkQuatRef_015b9b20;
			length = 0.0f;
		}

		_hkConstraintQueryBegin(query);
		_hk1dLinearBilateralConstraintBuildJacobian(linear, query, out);
		out.m_jacobianSchemas = jacobianSchemas;          // one shared schema for all links
		_hkReplacePreviousRhs(atom[i].m_length - length, query, out, 1);

		previousState = nextState;
	}

	_hkFinalizeConstraints(numLinks, m_tau, m_damping, m_cfm, bodyIndices.m_data, chunkBase,
	                       jacobianRows, in, out);

	// release the index array if _reserveMore moved it off the stack
	if (bodyIndices.m_capacityAndFlags >= 0)
	{
		hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
		tm->deallocateChunk(bodyIndices.m_data,
		                    (bodyIndices.m_capacityAndFlags & HK_ARRAY_CAPACITY_MASK) * 4, 0x14);
	}
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

// ---------------------------------------------------------------------------------------------------------
// hkMotionState doubles as the hkSweptTransform *and* the hkTransform handed to hkVector4::hamilton/
// hkRotation::set (the transform is the first member of both), preceded so the store survives the
// inf/nan check the copy is used for below.
// ---------------------------------------------------------------------------------------------------------
__forceinline hkMotionState& asTransform(hkMotionState& s) { return s; }

// Rotates v into out with the transform's column-major rotation; the .w lane is cleared. The retail code
// walks the columns in reverse order (column 2 first), which the sum order below reproduces.
__forceinline void setRotatedDir(hkVector4& out, const hkVector4* rot, const hkVector4& v)
{
	out.x = (v.z * rot[2].x + v.y * rot[1].x) + v.x * rot[0].x;
	out.y = (v.z * rot[2].y + v.y * rot[1].y) + v.x * rot[0].y;
	out.z = (v.z * rot[2].z + v.y * rot[1].z) + v.x * rot[0].z;
	out.w = 0.0f;
}

// @ 0x108ffc0
const hkVelocityAccumulator* hkStabilizedSphereMotionEx::applyAccumulator(const hkStepInfo& stepInfo,
                                                                          const hkVelocityAccumulator* prevAcc)
{
	hkMotionState& motionState = m_motionState;

	m_linearVelocity = prevAcc->m_linearVelocity2;
	m_angularVelocity = prevAcc->m_angularVelocity2;
	motionState.m_deactivationCounter = (uint16_t)prevAcc->m_deactivationClass;

	// centre of mass 0 = centre of mass 1 (the copy is what the .w lane below overwrites), start time in .w
	hkVector4& centerOfMass0 = motionState.m_sweptTransform.m_centerOfMass0;
	hkVector4& centerOfMass1 = motionState.m_sweptTransform.m_centerOfMass1;
	centerOfMass0 = centerOfMass1;
	centerOfMass0.w = stepInfo.m_startTime;

	// clamp the linear velocity to the motion's limit (all four lanes are scaled)
	float speedSq = (m_linearVelocity.y * m_linearVelocity.y + m_linearVelocity.x * m_linearVelocity.x)
	              + m_linearVelocity.z * m_linearVelocity.z;
	const float maxLinearVelocity = motionState.m_maxLinearVelocity;
	if (speedSq > maxLinearVelocity * maxLinearVelocity)
	{
		const float scale = maxLinearVelocity / sqrtf(speedSq);
		m_linearVelocity.x = scale * m_linearVelocity.x;
		m_linearVelocity.y = scale * m_linearVelocity.y;
		m_linearVelocity.z = scale * m_linearVelocity.z;
		m_linearVelocity.w = scale * m_linearVelocity.w;
	}

	// centre of mass 1 += deltaTime * linear velocity, with the inverse delta time in the .w lane
	const float deltaTime = stepInfo.m_deltaTime;
	centerOfMass1.x = centerOfMass1.x + deltaTime * m_linearVelocity.x;
	centerOfMass1.y = centerOfMass1.y + deltaTime * m_linearVelocity.y;
	centerOfMass1.z = centerOfMass1.z + deltaTime * m_linearVelocity.z;
	centerOfMass1.w = centerOfMass1.w + deltaTime * m_linearVelocity.w;
	centerOfMass1.w = stepInfo.m_invDeltaTime;

	// The rotation copy also feeds hkVector4::hamilton, which checks the last lane and computes 1/x for it
	// into a stack slot (dead here) before the half-step delta is built.
	motionState.m_sweptTransform.m_rotation0 = motionState.m_sweptTransform.m_rotation1;
	hkQuaternion rotation = motionState.m_sweptTransform.m_rotation1;
	float invHalfDeltaTime = 1.0f / (deltaTime * g_hkHalf_0149e064);
	(void)invHalfDeltaTime;

	// half-step angular delta and the cosine series of its length stored in .w
	hkQuaternion delta;
	float maxAngle = motionState.m_maxAngularVelocity * stepInfo.m_deltaTime;
	if (maxAngle > g_hkMaxAngle_013ec4b4)
		maxAngle = g_hkMaxAngle_013ec4b4;
	const float maxAngleSq = maxAngle * maxAngle;
	const float halfDeltaTime = deltaTime * g_hkHalf_0149e064;
	delta.x = halfDeltaTime * m_angularVelocity.x;
	delta.y = halfDeltaTime * m_angularVelocity.y;
	delta.z = halfDeltaTime * m_angularVelocity.z;

	float angleSq = (delta.x * delta.x + (delta.y * delta.y + delta.z * delta.z)) * g_hkAngleScale_0149e068;
	if (angleSq > maxAngleSq)
	{
		// over the per-step turn limit: scale both the angular velocity and the half-step delta down
		const float scale = maxAngle / sqrtf(angleSq);
		m_angularVelocity.x = scale * m_angularVelocity.x;
		m_angularVelocity.y = scale * m_angularVelocity.y;
		m_angularVelocity.z = scale * m_angularVelocity.z;
		m_angularVelocity.w = scale * m_angularVelocity.w;
		delta.x = scale * delta.x;
		delta.y = scale * delta.y;
		delta.z = scale * delta.z;
		angleSq = maxAngleSq;
	}
	const float angleSq2 = angleSq * angleSq;
	delta.w = ((g_hkOne_01485720 - angleSq * g_hkHalf_0149e064) - angleSq2 * g_hkStepScale_0149e060)
	          - (angleSq2 * angleSq) * g_hkStepScale2_0149e05c;

	hkQuaternion_setMul(&rotation, 0, &delta, &rotation);
	hkQuaternion_normalize(&rotation, 0);

	motionState.m_deltaAngle.x = delta.x + delta.x;
	motionState.m_deltaAngle.y = delta.y + delta.y;
	motionState.m_deltaAngle.z = delta.z + delta.z;
	motionState.m_deltaAngle.w = sqrtf(angleSq * g_hkPi_014a1984);

	motionState.m_sweptTransform.m_rotation1 = rotation;
	hkRotation_set((hkRotation*)&asTransform(motionState), 0, &motionState.m_sweptTransform.m_rotation1);

	// translation = centre of mass - rotation * centre of mass in local space
	const hkVector4& centerOfMassLocal = motionState.m_sweptTransform.m_centerOfMassLocal;
	const hkVector4* rot = motionState.m_transform.m_rot;
	const float rx = (centerOfMassLocal.z * rot[2].x + centerOfMassLocal.y * rot[1].x) + centerOfMassLocal.x * rot[0].x;
	const float ry = (centerOfMassLocal.z * rot[2].y + centerOfMassLocal.y * rot[1].y) + centerOfMassLocal.x * rot[0].y;
	const float rz = (centerOfMassLocal.z * rot[2].z + centerOfMassLocal.y * rot[1].z) + centerOfMassLocal.x * rot[0].z;
	hkVector4& translation = motionState.m_transform.m_trans;
	translation.x = centerOfMass1.x - rx;
	translation.y = centerOfMass1.y - ry;
	translation.z = centerOfMass1.z - rz;
	translation.w = centerOfMass1.w;

	return (const hkVelocityAccumulator*)&prevAcc->m_centerOfMass;
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
// hkStabilizedBoxMotion::applyAccumulator: same integration as the stabilized sphere, except that the incoming
// angular velocity is rotated into world space first and the two rotation accesses use the hkMathQuaternion
// helpers (the sphere uses plain copies). Equivalence-only (x87), see nonmatching.txt.
const hkVelocityAccumulator* hkStabilizedBoxMotionEx::applyAccumulator(const hkStepInfo& stepInfo,
                                                                       const hkVelocityAccumulator* prevAcc)
{
	hkMotionState& motionState = m_motionState;

	m_linearVelocity = prevAcc->m_linearVelocity2;
	setRotatedDir(m_angularVelocity, motionState.m_transform.m_rot, prevAcc->m_angularVelocity2);
	motionState.m_deactivationCounter = (uint16_t)prevAcc->m_deactivationClass;

	// centre of mass 0 = centre of mass 1 (the copy is what the .w lane below overwrites), start time in .w
	hkVector4& centerOfMass0 = motionState.m_sweptTransform.m_centerOfMass0;
	hkVector4& centerOfMass1 = motionState.m_sweptTransform.m_centerOfMass1;
	centerOfMass0 = centerOfMass1;
	centerOfMass0.w = stepInfo.m_startTime;

	// clamp the linear velocity to the motion's limit (all four lanes are scaled)
	float speedSq = (m_linearVelocity.y * m_linearVelocity.y + m_linearVelocity.x * m_linearVelocity.x)
	              + m_linearVelocity.z * m_linearVelocity.z;
	const float maxLinearVelocity = motionState.m_maxLinearVelocity;
	if (speedSq > maxLinearVelocity * maxLinearVelocity)
	{
		const float scale = maxLinearVelocity / sqrtf(speedSq);
		m_linearVelocity.x = scale * m_linearVelocity.x;
		m_linearVelocity.y = scale * m_linearVelocity.y;
		m_linearVelocity.z = scale * m_linearVelocity.z;
		m_linearVelocity.w = scale * m_linearVelocity.w;
	}

	// centre of mass 1 += deltaTime * linear velocity, with the inverse delta time in the .w lane
	const float deltaTime = stepInfo.m_deltaTime;
	centerOfMass1.x = centerOfMass1.x + deltaTime * m_linearVelocity.x;
	centerOfMass1.y = centerOfMass1.y + deltaTime * m_linearVelocity.y;
	centerOfMass1.z = centerOfMass1.z + deltaTime * m_linearVelocity.z;
	centerOfMass1.w = centerOfMass1.w + deltaTime * m_linearVelocity.w;
	centerOfMass1.w = stepInfo.m_invDeltaTime;

	// The two rotation accesses go through the hkMathQuaternion helpers: the first copies the current
	// rotation into rotation0 (and computes 1/.5*dt for the dead 4th lane), the second copies the swept
	// transform's two centre-of-mass lanes into it, the third copies the accumulated rotation into
	// rotation0 of the local copy. m_rotation1 at the far end of the state is volatile so the second copy
	// is not forwarded.
	hkVector4& cometQuaternion = motionState.m_transform.m_rot[0];
	hkQuaternion rotation = motionState.m_sweptTransform.m_rotation1;
	(void)(1.0f / (deltaTime * g_hkHalf_0149e064));
	cometQuaternion = *(const hkVector4*)&motionState.m_sweptTransform.m_centerOfMass0;
	rotation = motionState.m_sweptTransform.m_rotation0;
	cometQuaternion = *(const hkVector4*)(const volatile void*)&motionState.m_sweptTransform.m_rotation1;

	// half-step angular delta and the cosine series of its length stored in .w
	hkQuaternion delta;
	float maxAngle = motionState.m_maxAngularVelocity * stepInfo.m_deltaTime;
	if (maxAngle > g_hkMaxAngle_013ec4b4)
		maxAngle = g_hkMaxAngle_013ec4b4;
	const float maxAngleSq = maxAngle * maxAngle;
	const float halfDeltaTime = deltaTime * g_hkHalf_0149e064;
	delta.x = halfDeltaTime * m_angularVelocity.x;
	delta.y = halfDeltaTime * m_angularVelocity.y;
	delta.z = halfDeltaTime * m_angularVelocity.z;

	float angleSq = (delta.x * delta.x + (delta.y * delta.y + delta.z * delta.z)) * g_hkAngleScale_0149e068;
	if (angleSq > maxAngleSq)
	{
		// over the per-step turn limit: scale both the angular velocity and the half-step delta down
		const float scale = maxAngle / sqrtf(angleSq);
		m_angularVelocity.x = scale * m_angularVelocity.x;
		m_angularVelocity.y = scale * m_angularVelocity.y;
		m_angularVelocity.z = scale * m_angularVelocity.z;
		m_angularVelocity.w = scale * m_angularVelocity.w;
		delta.x = scale * delta.x;
		delta.y = scale * delta.y;
		delta.z = scale * delta.z;
		angleSq = maxAngleSq;
	}
	const float angleSq2 = angleSq * angleSq;
	delta.w = ((g_hkOne_01485720 - angleSq * g_hkHalf_0149e064) - angleSq2 * g_hkStepScale_0149e060)
	          - (angleSq2 * angleSq) * g_hkStepScale2_0149e05c;

	hkQuaternion_setMul(&rotation, 0, &delta, &rotation);
	hkQuaternion_normalize(&rotation, 0);

	motionState.m_deltaAngle.x = delta.x + delta.x;
	motionState.m_deltaAngle.y = delta.y + delta.y;
	motionState.m_deltaAngle.z = delta.z + delta.z;
	motionState.m_deltaAngle.w = sqrtf(angleSq * g_hkPi_014a1988);
	motionState.m_sweptTransform.m_rotation1 = rotation;
	hkRotation_set((hkRotation*)&asTransform(motionState), 0, &motionState.m_sweptTransform.m_rotation1);

	// translation = centre of mass - rotation * centre of mass in local space
	const hkVector4& centerOfMassLocal = motionState.m_sweptTransform.m_centerOfMassLocal;
	const hkVector4* rot = motionState.m_transform.m_rot;
	const float rx = (centerOfMassLocal.z * rot[2].x + centerOfMassLocal.y * rot[1].x) + centerOfMassLocal.x * rot[0].x;
	const float ry = (centerOfMassLocal.z * rot[2].y + centerOfMassLocal.y * rot[1].y) + centerOfMassLocal.x * rot[0].y;
	const float rz = (centerOfMassLocal.z * rot[2].z + centerOfMassLocal.y * rot[1].z) + centerOfMassLocal.x * rot[0].z;
	hkVector4& translation = motionState.m_transform.m_trans;
	translation.x = centerOfMass1.x - rx;
	translation.y = centerOfMass1.y - ry;
	translation.z = centerOfMass1.z - rz;
	translation.w = centerOfMass1.w;

	return (const hkVelocityAccumulator*)&prevAcc->m_centerOfMass;
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
