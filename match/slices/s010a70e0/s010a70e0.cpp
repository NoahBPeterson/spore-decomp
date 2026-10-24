// Havok 3.1.0 contact response helpers.
//
// 0x010a70e0  hkpSimpleCollisionResponse::solveSingleContact
// 0x010a76d0  _hkInitHeader
//
// The layouts below are the 32-bit offsets observed in the binary and match the
// dev-PDB hkMotionState / hkRigidMotion records.  Only the fields this slice
// reads or writes are named; the unknown virtual slots are placeholders that
// preserve the retail vtable byte offsets (getInertiaInvWorld at +0x40,
// setLinearVelocity at +0x58, setAngularVelocity at +0x5c, and the two
// hkDynamicsContactMgr TOI callbacks at +0x30 / +0x34).
#include "types.h"
#include <math.h>
#include <stddef.h>
#include <intrin.h>

#pragma intrinsic(fabs)

typedef float hkReal;
typedef unsigned short hkUint16;

// The retail Havok build evaluates hkMath::sqrt with the FPU's x87 fsqrt
// instruction.  MSVC's <math.h> sqrt always calls the CRT's _CIsqrt instead,
// so use the instruction directly; this keeps the result in the x87 register
// and does not disturb the SSE state.
static hkReal hkSqrt(hkReal value)
{
	__asm
	{
		fld value
		fsqrt
		fstp value
	}
	return value;
}

__declspec(align(16)) struct hkVector4
{
	hkReal x, y, z, w;
};

__declspec(align(16)) struct hkQuaternion
{
	hkReal x, y, z, w;
};

__declspec(align(16)) struct hkMatrix3
{
	hkVector4 m_col0;   // +0x00
	hkVector4 m_col1;   // +0x10
	hkVector4 m_col2;   // +0x20
};

// hkTransform: three rotation columns followed by the translation column.
__declspec(align(16)) struct hkTransform
{
	hkVector4 m_rotation[3];   // +0x00
	hkVector4 m_translation;   // +0x30
};

// hkSweptTransform: the two centre-of-mass keys with the two motion times in
// their w components, then the two rotations and the local centre of mass.
__declspec(align(16)) struct hkSweptTransform
{
	hkVector4 m_centerOfMass0;      // +0x00 (w = time0)
	hkVector4 m_centerOfMass1;      // +0x10 (w = 1 / (time1 - time0))
	hkQuaternion m_rotation0;       // +0x20
	hkQuaternion m_rotation1;       // +0x30
	hkVector4 m_centerOfMassLocal;  // +0x40
};

__declspec(align(16)) struct hkMotionState
{
	hkTransform m_transform;              // +0x00
	hkSweptTransform m_sweptTransform;    // +0x40
	hkVector4 m_deltaAngle;               // +0x90 (per-step angular delta)
	float m_objectRadius;                 // +0xa0
	float m_maxLinearVelocity;            // +0xa4
	float m_maxAngularVelocity;           // +0xa8
	hkUint16 m_deactivationClass;         // +0xac
	hkUint16 m_deactivationCounter;       // +0xae
};

class hkContactPoint
{
public:
	hkVector4 m_position;           // +0x00
	hkVector4 m_separatingNormal;   // +0x10 (w = separating distance)
};

// hkpBodyVelocity: the linear and angular velocity, both in world space.
__declspec(align(16)) struct hkpBodyVelocity
{
	hkVector4 m_linear;    // +0x00
	hkVector4 m_angular;   // +0x10
};

// hkpSimpleConstraintInfoInitInput: one body's mass-relative contact position,
// inverse world inertia, and inverse mass.
__declspec(align(16)) struct hkpSimpleConstraintInfoInitInput
{
	hkVector4 m_massRelPos;    // +0x00
	hkMatrix3 m_invInertia;    // +0x10
	hkReal m_invMass;          // +0x40
};

// hkpSimpleConstraintBodyInfo and hkpSimpleConstraintInfo as laid out by
// hkSimpleConstraintUtil_InitInfo (0x010bee60).
__declspec(align(16)) struct hkpSimpleConstraintBodyInfo
{
	hkMatrix3 m_rxR;        // +0x00
	hkMatrix3 m_IinvRxR;    // +0x30
	hkReal m_invMass;       // +0x60
	hkReal m_invMassReg;    // +0x64
	hkReal m_pad[2];        // +0x68
};

__declspec(align(16)) struct hkpSimpleConstraintInfo
{
	hkpSimpleConstraintBodyInfo m_body[2];   // +0x000
	hkMatrix3 m_directions;                  // +0x0e0
	hkMatrix3 m_mC;                          // +0x110
	hkMatrix3 m_mCinv;                       // +0x140
};

struct hkSimpleConstraintUtilCollideParams
{
	float m_friction;                    // +0x00
	float m_restitution;                 // +0x04
	float m_maxImpulse;                  // +0x08
	float m_externalSeperatingVelocity;  // +0x0c
	float m_extraSeparatingVelocity;     // +0x10
	float m_extraSlope;                  // +0x14
	unsigned char m_contactImpulseLimitBreached;   // +0x18
};

class hkConstraintQueryIn;

// hkpMotion / hkRigidMotion.  The virtual slots that are actually called sit at
// the retail byte offsets; the other slots preserve the vtable's shape.  The
// first 16-byte member (m_motionState) starts at +0x10 after the vftable.
class hkRigidMotion
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0a(); virtual void slot0b();
	virtual void slot0c(); virtual void slot0d(); virtual void slot0e(); virtual void slot0f();
	virtual void getInertiaInvWorld(hkMatrix3& inertiaInvOut);   // +0x40
	virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15();
	virtual void setLinearVelocity(const hkVector4& velocity);    // +0x58
	virtual void setAngularVelocity(const hkVector4& velocity);   // +0x5c

	hkMotionState m_motionState;           // +0x10
	float m_massInv;                       // +0xc0
	float m_particleMinInertiaDiagInv;     // +0xc4
	float m_linearDamping;                 // +0xc8
	float m_angularDamping;                // +0xcc
	hkVector4 m_linearVelocity;            // +0xd0
	hkVector4 m_angularVelocity;           // +0xe0
};

typedef char hkRigidMotion_layout_motionState[(offsetof(hkRigidMotion, m_motionState) == 0x10) ? 1 : -1];
typedef char hkRigidMotion_layout_massInv[(offsetof(hkRigidMotion, m_massInv) == 0xc0) ? 1 : -1];
typedef char hkRigidMotion_layout_linearVelocity[(offsetof(hkRigidMotion, m_linearVelocity) == 0xd0) ? 1 : -1];

// hkDynamicsContactMgr: the two TOI callbacks used by solveSingleContact.
class hkDynamicsContactMgr
{
public:
	virtual void cslot00(); virtual void cslot01(); virtual void cslot02(); virtual void cslot03();
	virtual void cslot04(); virtual void cslot05(); virtual void cslot06(); virtual void cslot07();
	virtual void cslot08(); virtual void cslot09(); virtual void cslot0a(); virtual void cslot0b();

	// +0x30
	virtual void toiCollisionResponseBeginCallback(const hkContactPoint& cp,
	                                               const hkpSimpleConstraintInfoInitInput& inA,
	                                               hkpBodyVelocity& velA,
	                                               const hkpSimpleConstraintInfoInitInput& inB,
	                                               hkpBodyVelocity& velB);
	// +0x34
	virtual void toiCollisionResponseEndCallback(const hkContactPoint& cp, hkReal impulseApplied,
	                                             const hkpSimpleConstraintInfoInitInput& inA,
	                                             hkpBodyVelocity& velA,
	                                             const hkpSimpleConstraintInfoInitInput& inB,
	                                             hkpBodyVelocity& velB);
};

// hkConstraintQueryIn: only the buffer roots and body accumulators used by the
// schema header writer are named.
class hkConstraintQueryIn
{
public:
	char m_pad00[0x20];
	int* m_accumulatorBufferRoot;   // +0x20
	int* m_jacobianBufferRoot;      // +0x24
	int* m_bodyA;                   // +0x28
	int* m_bodyB;                   // +0x2c
};

// hkConstraintQueryOut: the jacobian cursor and the schema cursor.
struct hkConstraintQueryOut
{
	int* m_jacobians;   // +0x00
	int* m_schemas;     // +0x04
};

// One jacobian schema header (0x18 bytes).
struct hkJacobianSchemaHeader
{
	int m_type;              // +0x00
	int m_jacobianOffset;    // +0x04
	int m_bodyAOffset;       // +0x08
	int m_bodyBOffset;       // +0x0c
	int m_size;              // +0x10
	int m_extra;             // +0x14
};

// ---- external Havok helpers (identical-code names from symbols/havok_names.txt) ----
extern "C" void hkSimpleConstraintUtil_InitInfo(const hkpSimpleConstraintInfoInitInput& bodyA,
                                                const hkpSimpleConstraintInfoInitInput& bodyB,
                                                const hkMatrix3& directions,
                                                hkpSimpleConstraintInfo& info);            // 0x010bee60
extern "C" hkReal hkSimpleConstraintUtil_Collide(const hkpSimpleConstraintInfo& info,
                                                 hkSimpleConstraintUtilCollideParams& params,
                                                 hkpBodyVelocity& velA,
                                                 hkpBodyVelocity& velB);                   // 0x010bf980
extern "C" void hkSimpleConstraintUtil_getPointVelocity(const hkpSimpleConstraintInfo& info,
                                                       const hkpBodyVelocity& velA,
                                                       const hkpBodyVelocity& velB,
                                                       hkVector4& out);                    // 0x010bf800

class hkpSimpleCollisionResponse
{
public:
	struct SolveSingleOutput
	{
		hkReal m_impulse;              // +0x00
		hkReal m_velocityKeyframedA;   // +0x04
		hkReal m_velocityKeyframedB;   // +0x08
	};

	static void solveSingleContact(const hkContactPoint& cp, float time,
	                               const hkSimpleConstraintUtilCollideParams& params,
	                               hkRigidMotion* bodyA, hkRigidMotion* bodyB,
	                               hkDynamicsContactMgr* contactMgr,
	                               SolveSingleOutput& output);
};

// hkpSimpleCollisionResponse::solveSingleContact.
// @ 0x010a70e0
void hkpSimpleCollisionResponse::solveSingleContact(const hkContactPoint& cp, float time,
                                                    const hkSimpleConstraintUtilCollideParams& params,
                                                    hkRigidMotion* bodyA, hkRigidMotion* bodyB,
                                                    hkDynamicsContactMgr* contactMgr,
                                                    SolveSingleOutput& output)
{
	hkpSimpleConstraintInfoInitInput inA;
	hkpSimpleConstraintInfoInitInput inB;
	hkMatrix3 directions;
	hkpSimpleConstraintInfo info;
	hkpBodyVelocity velA;
	hkpBodyVelocity velB;
	hkpBodyVelocity keyframedVelA;
	hkpBodyVelocity keyframedVelB;
	hkVector4 pointVelocityA;
	hkVector4 pointVelocityB;

	// ---- body A: contact point in the centre-of-mass frame and inverse inertia ----
	{
		const hkSweptTransform& s = bodyA->m_motionState.m_sweptTransform;
		const hkReal t = (time - s.m_centerOfMass0.w) * s.m_centerOfMass1.w;
		const hkReal u = 1.0f - t;
		inA.m_massRelPos.x = cp.m_position.x - (u * s.m_centerOfMass0.x + t * s.m_centerOfMass1.x);
		inA.m_massRelPos.y = cp.m_position.y - (u * s.m_centerOfMass0.y + t * s.m_centerOfMass1.y);
		inA.m_massRelPos.z = cp.m_position.z - (u * s.m_centerOfMass0.z + t * s.m_centerOfMass1.z);
		inA.m_massRelPos.w = cp.m_position.w - (u * s.m_centerOfMass0.w + t * s.m_centerOfMass1.w);
	}
	inA.m_invMass = bodyA->m_massInv;
	_ReadWriteBarrier();
	bodyA->getInertiaInvWorld(inA.m_invInertia);

	// ---- body B ----
	{
		const hkSweptTransform& s = bodyB->m_motionState.m_sweptTransform;
		const hkReal t = (time - s.m_centerOfMass0.w) * s.m_centerOfMass1.w;
		const hkReal u = 1.0f - t;
		inB.m_massRelPos.x = cp.m_position.x - (u * s.m_centerOfMass0.x + t * s.m_centerOfMass1.x);
		inB.m_massRelPos.y = cp.m_position.y - (u * s.m_centerOfMass0.y + t * s.m_centerOfMass1.y);
		inB.m_massRelPos.z = cp.m_position.z - (u * s.m_centerOfMass0.z + t * s.m_centerOfMass1.z);
		inB.m_massRelPos.w = cp.m_position.w - (u * s.m_centerOfMass0.w + t * s.m_centerOfMass1.w);
	}
	inB.m_invMass = bodyB->m_massInv;
	_ReadWriteBarrier();
	bodyB->getInertiaInvWorld(inB.m_invInertia);

	// ---- reference frame: the contact normal plus two tangents ----
	directions.m_col0 = cp.m_separatingNormal;

	{
		const float ax = (float)fabs(cp.m_separatingNormal.x);
		const float ay = (float)fabs(cp.m_separatingNormal.y);
		const float az = (float)fabs(cp.m_separatingNormal.z);

		// Pick the smallest axis pair first, then the largest component; the
		// resulting tangent is the cross product of the normal with that axis.
		const bool xSmaller = ax <= ay;
		float smallest = xSmaller ? ax : ay;
		unsigned int other = xSmaller ? 0u : 1u;
		unsigned int largest;
		if (smallest <= az)
		{
			largest = 2u;
		}
		else
		{
			largest = other;
			other = 2u;
		}

		const unsigned int first = xSmaller ? 1u : 0u;
		hkReal* tangent = &directions.m_col1.x;
		tangent[other] = 0.0f;
		tangent[first] = (&cp.m_separatingNormal.x)[largest];
		tangent[largest] = -(&cp.m_separatingNormal.x)[first];

		const hkReal len2 = tangent[2] * tangent[2] +
		                    (tangent[1] * tangent[1] + tangent[0] * tangent[0]);
		hkReal invLen = 0.0f;
		if (len2 != 0.0f)
			invLen = 1.0f / hkSqrt(len2);
		tangent[0] *= invLen;
		tangent[1] *= invLen;
		tangent[2] *= invLen;
		tangent[3] = invLen * 0.0f;

		directions.m_col2.x = tangent[0] * cp.m_separatingNormal.z - tangent[2] * cp.m_separatingNormal.x;
		directions.m_col2.y = tangent[1] * cp.m_separatingNormal.x - tangent[0] * cp.m_separatingNormal.y;
		directions.m_col2.z = tangent[2] * cp.m_separatingNormal.y - tangent[1] * cp.m_separatingNormal.z;
		directions.m_col2.w = 0.0f;
	}

	// ---- current velocities (the solver updates these in place) ----
	velA.m_linear = bodyA->m_linearVelocity;
	velA.m_angular = bodyA->m_angularVelocity;
	velB.m_linear = bodyB->m_linearVelocity;
	velB.m_angular = bodyB->m_angularVelocity;

	// ---- keyframed velocities reconstructed from the swept transforms ----
	{
		const hkSweptTransform& s = bodyA->m_motionState.m_sweptTransform;
		const hkReal invDt = s.m_centerOfMass1.w;
		keyframedVelA.m_linear.x = (s.m_centerOfMass1.x - s.m_centerOfMass0.x) * invDt;
		keyframedVelA.m_linear.y = (s.m_centerOfMass1.y - s.m_centerOfMass0.y) * invDt;
		keyframedVelA.m_linear.z = (s.m_centerOfMass1.z - s.m_centerOfMass0.z) * invDt;
		keyframedVelA.m_linear.w = (s.m_centerOfMass1.w - s.m_centerOfMass0.w) * invDt;
		keyframedVelA.m_angular.x = bodyA->m_motionState.m_deltaAngle.x * invDt;
		keyframedVelA.m_angular.y = bodyA->m_motionState.m_deltaAngle.y * invDt;
		keyframedVelA.m_angular.z = bodyA->m_motionState.m_deltaAngle.z * invDt;
		keyframedVelA.m_angular.w = bodyA->m_motionState.m_deltaAngle.w * invDt;
	}
	{
		const hkSweptTransform& s = bodyB->m_motionState.m_sweptTransform;
		const hkReal invDt = s.m_centerOfMass1.w;
		keyframedVelB.m_linear.x = (s.m_centerOfMass1.x - s.m_centerOfMass0.x) * invDt;
		keyframedVelB.m_linear.y = (s.m_centerOfMass1.y - s.m_centerOfMass0.y) * invDt;
		keyframedVelB.m_linear.z = (s.m_centerOfMass1.z - s.m_centerOfMass0.z) * invDt;
		keyframedVelB.m_linear.w = (s.m_centerOfMass1.w - s.m_centerOfMass0.w) * invDt;
		keyframedVelB.m_angular.x = bodyB->m_motionState.m_deltaAngle.x * invDt;
		keyframedVelB.m_angular.y = bodyB->m_motionState.m_deltaAngle.y * invDt;
		keyframedVelB.m_angular.z = bodyB->m_motionState.m_deltaAngle.z * invDt;
		keyframedVelB.m_angular.w = bodyB->m_motionState.m_deltaAngle.w * invDt;
	}

	_ReadWriteBarrier();
	contactMgr->toiCollisionResponseBeginCallback(cp, inA, velA, inB, velB);

	hkSimpleConstraintUtil_InitInfo(inA, inB, directions, info);
	output.m_impulse = hkSimpleConstraintUtil_Collide(info,
	                                                  const_cast<hkSimpleConstraintUtilCollideParams&>(params),
	                                                  velA, velB);

	contactMgr->toiCollisionResponseEndCallback(cp, output.m_impulse, inA, velA, inB, velB);

	// The first sample keeps body A keyframed and body B dynamic; the second
	// swaps them, giving the relative point velocity for each body.
	hkSimpleConstraintUtil_getPointVelocity(info, velB, keyframedVelA, pointVelocityA);
	hkSimpleConstraintUtil_getPointVelocity(info, velA, keyframedVelB, pointVelocityB);

	output.m_velocityKeyframedB = pointVelocityB.x;
	output.m_velocityKeyframedA = pointVelocityA.x;

	bodyA->setLinearVelocity(velA.m_linear);
	bodyA->setAngularVelocity(velA.m_angular);
	bodyB->setLinearVelocity(velB.m_linear);
	bodyB->setAngularVelocity(velB.m_angular);
}

// ---------------------------------------------------------------------------------------------
// _hkInitHeader: write one 0x18-byte jacobian schema header.  The header holds
// the schema id, the byte offsets of the body accumulators from the accumulator
// buffer root, the current schema offset from the jacobian buffer root, and two
// caller-supplied dwords, then advances the schema cursor.
// @ 0x010a76d0
void _hkInitHeader(hkConstraintQueryIn* in, unsigned int arg2, unsigned int arg3,
                   hkConstraintQueryOut* out)
{
	const int bodyA = (int)(size_t)in->m_bodyA;
	int* dest = out->m_schemas;
	const int jacobianBase = (int)(size_t)in->m_jacobianBufferRoot;
	const int bodyB = (int)(size_t)in->m_bodyB;
	const int accumulatorBase = (int)(size_t)in->m_accumulatorBufferRoot;
	const int jacobians = (int)(size_t)out->m_jacobians;

	dest[1] = jacobians - jacobianBase;
	dest[2] = bodyA - accumulatorBase;
	dest[3] = bodyB - accumulatorBase;
	dest[0] = 0x180101;
	dest[5] = (int)arg2;
	dest[4] = (int)arg3;
	out->m_schemas = dest + 6;
}
