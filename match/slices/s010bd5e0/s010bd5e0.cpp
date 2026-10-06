// Slice s010bd5e0 — one function, @ 0x010bd5e0 (6,264 bytes).
//
// Havok 3.1.0 (prebuilt, statically linked) constraint solver: export of the solver results,
// inferred to be hkExportImpulsesAndRhs( info, schemas, accumulators, jacobians, temp )
// (the Havok 6 hkpSolve.h comment: "exports the result from the solver into the solver
// results"). It walks the same Jacobian schema stream as hkSolveConstraints (0x010b8b30,
// slice s010b8b30) and, for every solver element, copies the accumulated impulse from the
// solver temp buffer into the hkSolverResults and stores the remaining velocity error
// ("rhs") computed from the summed velocities of the two velocity accumulators.
// Jump table at 0x010bedf0 (26 schema types; type 2 and unknown types re-dispatch forever,
// exactly as in the original, which has no default handling).
// Layouts: hkSolverInfo and hkSolverResults are from the dev PDB (tools/pdb_type.py); the
// accumulator / Jacobian / schema layouts are read from the disassembly (see s010b8b30).
#include "types.h"

#define HK_CALL
#define HK_FORCE_INLINE __forceinline

typedef float    hkReal;
typedef int8_t   hkInt8;
typedef uint8_t  hkUint8;
typedef uint16_t hkUint16;
typedef uint32_t hkUint32;
typedef unsigned long hkUlong;

struct __declspec(align(16)) hkVector4
{
	hkReal x, y, z, w;

	HK_FORCE_INLINE void setMul4(const hkVector4& a, const hkVector4& b)
	{
		x = a.x * b.x; y = a.y * b.y; z = a.z * b.z;
	}
	HK_FORCE_INLINE void setSub4(const hkVector4& a, const hkVector4& b)
	{
		x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;
	}
	HK_FORCE_INLINE void setAdd4(const hkVector4& a, const hkVector4& b)
	{
		x = a.x + b.x; y = a.y + b.y; z = a.z + b.z;
	}
	HK_FORCE_INLINE void mul4(const hkVector4& a)
	{
		x *= a.x; y *= a.y; z *= a.z;
	}
	HK_FORCE_INLINE void add4(const hkVector4& a)
	{
		x += a.x; y += a.y; z += a.z;
	}
	HK_FORCE_INLINE hkReal horizontalAdd3() const { return (x + y) + z; }
};

// ---- hkSolverInfo (dev PDB, size 0x140) ----
struct hkSolverInfo
{
	struct DeactivationInfo                  // size 0x20
	{
		float m_linearVelocityThresholdInv;
		float m_angularVelocityThresholdInv;
		float m_slowObjectVelocityMultiplier;
		float m_relativeSleepVelocityThreshold;
		hkUint32 m_stepsToDeactivate;
		hkUint32 m_padding[3];
	};

	float m_one;                                 // +0x00
	float m_tau;                                 // +0x04
	float m_damping;                             // +0x08
	float m_frictionTau;                         // +0x0c
	hkVector4 m_globalAccelerationPerSubStep;    // +0x10
	hkVector4 m_globalAccelerationPerStep;       // +0x20
	hkVector4 m_integrateVelocityFactor;         // +0x30
	hkVector4 m_invIntegrateVelocityFactor;      // +0x40
	float m_dampDivTau;                          // +0x50
	float m_tauDivDamp;                          // +0x54
	float m_dampDivFrictionTau;                  // +0x58
	float m_frictionTauDivDamp;                  // +0x5c
	float m_contactRestingVelocity;              // +0x60
	DeactivationInfo m_deactivationInfo[6];      // +0x64
	float m_deltaTime;                           // +0x124
	float m_invDeltaTime;                        // +0x128
	int m_numSteps;                              // +0x12c
	float m_invNumSteps;                         // +0x130
};

// ---- hkSolverResults (dev PDB, size 8) ----
class hkSolverResults
{
public:
	float m_impulseApplied;      // +0
	float m_internalSolverData;  // +4 (the exported rhs)
};

struct hkSolverElemTemp { float m_impulseApplied; };

// ---- velocity accumulator (0x80-byte stride) ----
struct hkVelocityAccumulator
{
	hkUint8 m_type;                      // +0x00
	hkUint8 m_pad01[3];
	hkUint32 m_deactivationCounter;      // +0x04
	int m_deactivationClass;             // +0x08
	int m_pad0c;
	hkVector4 m_linearVel;               // +0x10
	hkVector4 m_angularVel;              // +0x20
	hkVector4 m_invMasses;               // +0x30
	hkVector4 m_sumLinearVel;            // +0x40
	hkVector4 m_sumAngularVel;           // +0x50
	hkVector4 m_pad60[2];
};

// ---- Jacobian elements ----
class hkJacobianElement {};

// 0x30 bytes: linear (w = rhs), angular A, angular B.
class hk1Lin2AngJacobian : public hkJacobianElement
{
public:
	hkVector4 m_linear0;
	hkVector4 m_angular[2];

	HK_FORCE_INLINE hkReal getRhs() const { return m_linear0.w; }

	// Relative summed velocity of the two bodies along this Jacobian.
	HK_FORCE_INLINE hkReal getSumVelocity(const hkVelocityAccumulator& a, const hkVelocityAccumulator& b) const
	{
		hkVector4 angA; angA.setMul4(m_angular[0], a.m_sumAngularVel);
		hkVector4 lin;  lin.setSub4(a.m_sumLinearVel, b.m_sumLinearVel);
		hkVector4 angB; angB.setMul4(m_angular[1], b.m_sumAngularVel);
		lin.mul4(m_linear0);
		hkVector4 ang;  ang.setAdd4(angB, angA);
		lin.add4(ang);
		return lin.horizontalAdd3();
	}
};

// 0x20 bytes: angular A (w = inverse effective mass), angular B (w = rhs).
class hk2AngJacobian : public hkJacobianElement
{
public:
	hkVector4 m_angular[2];

	HK_FORCE_INLINE hkReal getInvJacDiag() const { return m_angular[0].w; }
	HK_FORCE_INLINE hkReal getRhs() const { return m_angular[1].w; }

	HK_FORCE_INLINE hkReal getSumVelocity(const hkVelocityAccumulator& a, const hkVelocityAccumulator& b) const
	{
		hkVector4 angA; angA.setMul4(m_angular[0], a.m_sumAngularVel);
		hkVector4 angB; angB.setMul4(m_angular[1], b.m_sumAngularVel);
		hkVector4 ang;  ang.setAdd4(angB, angA);
		return ang.horizontalAdd3();
	}
};

// 0x40 bytes: linear A (w = rhs), linear B, angular A, angular B.
class hk2Lin2AngJacobian : public hkJacobianElement
{
public:
	hkVector4 m_linear[2];
	hkVector4 m_angular[2];

	HK_FORCE_INLINE hkReal getRhs() const { return m_linear[0].w; }

	HK_FORCE_INLINE hkReal getSumVelocity(const hkVelocityAccumulator& a, const hkVelocityAccumulator& b) const
	{
		hkVector4 angA; angA.setMul4(m_angular[0], a.m_sumAngularVel);
		hkVector4 angB; angB.setMul4(m_angular[1], b.m_sumAngularVel);
		hkVector4 linA; linA.setMul4(m_linear[0], a.m_sumLinearVel);
		hkVector4 linB; linB.setMul4(b.m_sumLinearVel, m_linear[1]);
		hkVector4 ang;  ang.setAdd4(angB, angA);
		hkVector4 lin;  lin.setSub4(linA, linB);
		lin.add4(ang);
		return lin.horizontalAdd3();
	}
};

// ---- Jacobian schemas (byte type first; most store their size at +2) ----
class hkJacobianSchema
{
public:
	enum SchemaType
	{
		SCHEMA_TYPE_END = 0,
		SCHEMA_TYPE_HEADER = 1,
		SCHEMA_TYPE_GOTO = 3,                 // no Jacobian data
		SCHEMA_TYPE_1D_BILATERAL = 4,
		SCHEMA_TYPE_PAIR_CONTACT = 5,
		SCHEMA_TYPE_1D_ANGULAR_MOTOR = 6,
		SCHEMA_TYPE_1D_LINEAR_MOTOR = 7,
		SCHEMA_TYPE_1D_FRICTION = 8,
		SCHEMA_TYPE_2D_FRICTION = 9,
		SCHEMA_TYPE_3D_FRICTION = 10,
		SCHEMA_TYPE_1D_ANGULAR_FRICTION = 11,
		SCHEMA_TYPE_1D_ANGULAR_LIMITS = 12,
		SCHEMA_TYPE_1D_LINEAR_LIMITS = 13,
		SCHEMA_TYPE_1D_ANGULAR = 14,
		SCHEMA_TYPE_1D_BILATERAL_USER_TAU = 15,
		SCHEMA_TYPE_1D_LINEAR_USER_TAU = 16,
		SCHEMA_TYPE_SKIP_2ANG = 17,           // 0x20 bytes of Jacobian data, no result
		SCHEMA_TYPE_ADD_VELOCITY = 18,
		SCHEMA_TYPE_SET_TAU = 19,             // no Jacobian data
		SCHEMA_TYPE_SET_MASS = 20,            // no Jacobian data
		SCHEMA_TYPE_2LIN2ANG = 21,
		SCHEMA_TYPE_1D_ANGULAR_USER_TAU = 22,
		SCHEMA_TYPE_STIFF_SPRING_CHAIN = 23,
		SCHEMA_TYPE_BALL_SOCKET_CHAIN = 24,
		SCHEMA_TYPE_POWERED_CHAIN = 25
	};

	hkInt8 m_type;                       // +0
	hkInt8 m_numSolverResultsClass;      // +1 read by the "no results" skip loop
	hkUint16 m_sizeOfSchema;             // +2

	HK_FORCE_INLINE const hkJacobianSchema* getNext() const
	{
		return (const hkJacobianSchema*)((const char*)this + m_sizeOfSchema);
	}
};

struct hkJacobianHeaderSchema : hkJacobianSchema          // type 0x01, 0x18 bytes
{
	int m_jacobianOffset;                // +0x04 byte offset into the Jacobian buffer
	int m_bodyAOffset;                   // +0x08 byte offset into the accumulators
	int m_bodyBOffset;                   // +0x0c
	int m_solverResultStriding;          // +0x10
	hkSolverResults* m_solverResultInMainThread; // +0x14 (null: results are not exported)
};

struct hkJacobianMotorSchema : hkJacobianSchema           // types 0x06/0x07, 0x1c bytes
{
	float m_maxImpulse;                  // +0x04
	float m_minImpulse;                  // +0x08
	float m_velocityDelta;               // +0x0c
	float m_tau;                         // +0x10
	float m_damping;                     // +0x14
	float m_usedImpulseFactor;           // +0x18
};

struct hkJacobianFrictionSchema : hkJacobianSchema        // types 0x08/0x0b, 0x0c bytes
{
	float m_maxFrictionForce;            // +0x04
	float m_usedImpulseFactor;           // +0x08
};

struct hkJacobian2dFrictionSchema : hkJacobianSchema      // type 0x09, 0x18 bytes
{
	hkSolverResults* m_frictionResults;  // +0x04 (exported here, not to the header's results)
	float m_coupling;                    // +0x08
	float m_maxFrictionForce;            // +0x0c
	float m_usedImpulseFactor;           // +0x10
	int m_frictionResultStriding;        // +0x14
};

struct hkJacobian3dFrictionSchema : hkJacobian2dFrictionSchema  // type 0x0a, 0x1c bytes
{
	float m_angularFrictionFactor;       // +0x18
};

struct hkJacobianStiffSpringChainSchema : hkJacobianSchema  // type 0x17
{
	int m_numConstraints;                // +0x04
	int m_pad08[2];
	int m_bodyOffsets[1];                // +0x10, [m_numConstraints + 1]

	HK_FORCE_INLINE const hkJacobianElement* getEnd(const hkJacobianElement* j) const
	{
		return (const hkJacobianElement*)(((hkUlong)j + m_numConstraints * 0x40 + 4 + 15) & ~hkUlong(15));
	}
};

struct hkJacobianBallSocketChainSchema : hkJacobianSchema   // type 0x18
{
	int m_numConstraints;                // +0x04
	int m_pad08[2];
	int m_bodyOffsets[1];                // +0x10

	HK_FORCE_INLINE const hkJacobianElement* getEnd(const hkJacobianElement* j) const
	{
		return (const hkJacobianElement*)((const char*)j + m_numConstraints * 0x130 + 0x10);
	}
};

// Per-constraint motor info of a powered chain, 0x4c bytes.
struct hkPoweredChainMotorInfo
{
	struct Axis                          // 0x18 bytes
	{
		float m_minForce;                // +0x00 (+0x04 in the info)
		float m_maxForce;                // +0x04
		float m_pad08;
		float m_invMass;                 // +0x0c divisor of the force limit
		float m_pad10[2];
	};
	hkUint8 m_limitFlags;                // +0x00, 2 bits per axis: 3 = max limited, 1 = min limited
	hkUint8 m_pad01[3];
	Axis m_axis[3];                      // +0x04
};

struct hkJacobianPoweredChainSchema : hkJacobianSchema      // type 0x19
{
	hkUint8* m_limitFlagsOut;            // +0x04 per-constraint copy of the limit flags
	int m_numConstraints;                // +0x08
	int m_pad0c[3];
	int m_bodyOffsets[1];                // +0x18, [m_numConstraints + 1], then the motor infos

	HK_FORCE_INLINE const hkPoweredChainMotorInfo& getMotorInfo(int i) const
	{
		return *(const hkPoweredChainMotorInfo*)((const char*)&m_bodyOffsets[m_numConstraints + 1]
		                                         + i * sizeof(hkPoweredChainMotorInfo));
	}
	HK_FORCE_INLINE const hkJacobianElement* getEnd(const hkJacobianElement* j) const
	{
		return (const hkJacobianElement*)((const char*)j + m_numConstraints * 0x4f0 + 0x20);
	}
};

namespace hkMath
{
	template <typename T> T max2(T a, T b);    // 0x01081500 (out of line)
	template <typename T> T min2(T a, T b);    // 0x010871f0 (out of line)
}

// Helpers to step the raw streams.
template <typename T>
static HK_FORCE_INLINE const T* hkAddByteOffsetConst(const void* p, int offset)
{
	return (const T*)((const char*)p + offset);
}

static HK_FORCE_INLINE hkSolverResults* nextResult(hkSolverResults* r, int striding)
{
	return (hkSolverResults*)((char*)r + striding);
}

// =====================================================================================

void HK_CALL hkExportImpulsesAndRhs(const hkSolverInfo& info, const hkJacobianSchema* schema,
                                    const hkVelocityAccumulator* accumulators,
                                    const hkJacobianElement* jacobians, const hkSolverElemTemp* temp)
{
	const hkReal dampDivTauDt = info.m_dampDivTau * info.m_deltaTime;
	const hkReal dampDivFrictionTauDt = info.m_dampDivFrictionTau * info.m_deltaTime;
	const hkReal velToRhs = hkReal(info.m_numSteps) * info.m_deltaTime;
	const hkReal deltaTime = info.m_deltaTime;

	const hkJacobianElement* jac;
	const hkVelocityAccumulator* bodyA;
	const hkVelocityAccumulator* bodyB;
	hkSolverResults* results;
	int resultStriding;

nextHeader:
	{
		const hkJacobianHeaderSchema* header = (const hkJacobianHeaderSchema*)schema;
		resultStriding = header->m_solverResultStriding;
		jac = hkAddByteOffsetConst<hkJacobianElement>(jacobians, header->m_jacobianOffset);
		bodyA = hkAddByteOffsetConst<hkVelocityAccumulator>(accumulators, header->m_bodyAOffset);
		bodyB = hkAddByteOffsetConst<hkVelocityAccumulator>(accumulators, header->m_bodyBOffset);
		results = header->m_solverResultInMainThread;
		schema = (const hkJacobianSchema*)(header + 1);

		if (!results)
		{
			// Nothing to export for this constraint: just step the temp buffer over its elements.
			while (schema->m_type > hkJacobianSchema::SCHEMA_TYPE_HEADER)
			{
				const hkInt8 numClass = schema->m_numSolverResultsClass;
				if (numClass >= 5)
				{
					temp++;
					if (numClass >= 8)
					{
						temp++;
						if (numClass == 9)
						{
							temp++;
						}
					}
				}
				schema = schema->getNext();
			}
		}
	}

	for (;;)
	{
		const int type = schema->m_type;
		switch (type)
		{
		case hkJacobianSchema::SCHEMA_TYPE_END:
			return;

		case hkJacobianSchema::SCHEMA_TYPE_HEADER:
			goto nextHeader;

		case hkJacobianSchema::SCHEMA_TYPE_PAIR_CONTACT:
		{
			const hk1Lin2AngJacobian* j = (const hk1Lin2AngJacobian*)jac;
			const hkReal v0 = j[0].getSumVelocity(*bodyA, *bodyB);
			const hkReal v1 = j[1].getSumVelocity(*bodyA, *bodyB);
			results->m_impulseApplied = temp[0].m_impulseApplied;
			results->m_internalSolverData = dampDivTauDt * j[0].getRhs() - v0 * velToRhs;
			results = nextResult(results, resultStriding);
			results->m_internalSolverData = dampDivTauDt * j[1].getRhs() - v1 * velToRhs;
			results->m_impulseApplied = temp[1].m_impulseApplied;
			results = nextResult(results, resultStriding);
			temp += 2;
			schema = hkAddByteOffsetConst<hkJacobianSchema>(schema, 8);
			jac = j + 2;
			break;
		}

		case hkJacobianSchema::SCHEMA_TYPE_1D_BILATERAL:
		case hkJacobianSchema::SCHEMA_TYPE_1D_LINEAR_LIMITS:
		case hkJacobianSchema::SCHEMA_TYPE_1D_BILATERAL_USER_TAU:
		case hkJacobianSchema::SCHEMA_TYPE_1D_LINEAR_USER_TAU:
		{
			do
			{
				const hk1Lin2AngJacobian* j = (const hk1Lin2AngJacobian*)jac;
				jac = j + 1;
				const hkReal v = j->getSumVelocity(*bodyA, *bodyB);
				results->m_impulseApplied = temp->m_impulseApplied;
				results->m_internalSolverData = dampDivTauDt * j->getRhs() - v * velToRhs;
				results = nextResult(results, resultStriding);
				temp++;
				schema = schema->getNext();
			} while (schema->m_type == type);
			break;
		}

		case hkJacobianSchema::SCHEMA_TYPE_ADD_VELOCITY:
		{
			const hkVector4& dv = *(const hkVector4*)jac;
			hkVelocityAccumulator* a = const_cast<hkVelocityAccumulator*>(bodyA);
			a->m_linearVel.x = dv.x + a->m_linearVel.x;
			a->m_linearVel.y = a->m_linearVel.y + dv.y;
			a->m_linearVel.z = a->m_linearVel.z + dv.z;
			a->m_linearVel.w = a->m_linearVel.w + dv.w;
			a->m_sumLinearVel.x = dv.x + a->m_sumLinearVel.x;
			a->m_sumLinearVel.y = a->m_sumLinearVel.y + dv.y;
			a->m_sumLinearVel.z = a->m_sumLinearVel.z + dv.z;
			a->m_sumLinearVel.w = a->m_sumLinearVel.w + dv.w;
			jac = hkAddByteOffsetConst<hkJacobianElement>(jac, sizeof(hkVector4));
			schema = schema->getNext();
			break;
		}

		case hkJacobianSchema::SCHEMA_TYPE_1D_FRICTION:
		{
			const hkJacobianFrictionSchema* s = (const hkJacobianFrictionSchema*)schema;
			const hk1Lin2AngJacobian* j = (const hk1Lin2AngJacobian*)jac;
			const hkReal v = j->getSumVelocity(*bodyA, *bodyB);
			results->m_impulseApplied = temp->m_impulseApplied;
			results->m_internalSolverData = (dampDivTauDt * j->getRhs() - v * velToRhs) * s->m_usedImpulseFactor;
			jac = j + 1;
			goto singleElementDone;
		}

		case hkJacobianSchema::SCHEMA_TYPE_1D_LINEAR_MOTOR:
		{
			do
			{
				const hkJacobianMotorSchema* s = (const hkJacobianMotorSchema*)schema;
				const hk1Lin2AngJacobian* j = (const hk1Lin2AngJacobian*)jac;
				jac = j + 1;
				const hkReal v = j->getSumVelocity(*bodyA, *bodyB);
				results->m_impulseApplied = temp->m_impulseApplied;
				results->m_internalSolverData = (deltaTime * j->getRhs() - v * velToRhs) * s->m_usedImpulseFactor;
				results = nextResult(results, resultStriding);
				temp++;
				schema = schema->getNext();
			} while (schema->m_type == hkJacobianSchema::SCHEMA_TYPE_1D_LINEAR_MOTOR);
			break;
		}

		case hkJacobianSchema::SCHEMA_TYPE_1D_ANGULAR_LIMITS:
		case hkJacobianSchema::SCHEMA_TYPE_1D_ANGULAR:
		case hkJacobianSchema::SCHEMA_TYPE_1D_ANGULAR_USER_TAU:
		{
			do
			{
				const hk2AngJacobian* j = (const hk2AngJacobian*)jac;
				jac = j + 1;
				const hkReal v = j->getSumVelocity(*bodyA, *bodyB);
				results->m_impulseApplied = temp->m_impulseApplied;
				results->m_internalSolverData = j->getRhs() * deltaTime - v * velToRhs;
				results = nextResult(results, resultStriding);
				temp++;
				schema = schema->getNext();
			} while (schema->m_type == type);
			break;
		}

		case hkJacobianSchema::SCHEMA_TYPE_1D_ANGULAR_FRICTION:
		{
			do
			{
				const hkJacobianFrictionSchema* s = (const hkJacobianFrictionSchema*)schema;
				const hk2AngJacobian* j = (const hk2AngJacobian*)jac;
				jac = j + 1;
				const hkReal v = j->getSumVelocity(*bodyA, *bodyB);
				results->m_impulseApplied = temp->m_impulseApplied;
				results->m_internalSolverData = (deltaTime * j->getRhs() - v * velToRhs) * s->m_usedImpulseFactor;
				results = nextResult(results, resultStriding);
				temp++;
				schema = schema->getNext();
			} while (schema->m_type == hkJacobianSchema::SCHEMA_TYPE_1D_ANGULAR_FRICTION);
			break;
		}

		case hkJacobianSchema::SCHEMA_TYPE_1D_ANGULAR_MOTOR:
		{
			do
			{
				const hkJacobianMotorSchema* s = (const hkJacobianMotorSchema*)schema;
				const hk2AngJacobian* j = (const hk2AngJacobian*)jac;
				jac = j + 1;
				const hkReal v = j->getSumVelocity(*bodyA, *bodyB);
				results->m_impulseApplied = temp->m_impulseApplied;
				results->m_internalSolverData = (deltaTime * j->getRhs() - v * velToRhs) * s->m_usedImpulseFactor;
				results = nextResult(results, resultStriding);
				temp++;
				schema = schema->getNext();
			} while (schema->m_type == hkJacobianSchema::SCHEMA_TYPE_1D_ANGULAR_MOTOR);
			break;
		}

		case hkJacobianSchema::SCHEMA_TYPE_2LIN2ANG:
		{
			const hk2Lin2AngJacobian* j = (const hk2Lin2AngJacobian*)jac;
			const hkReal v = j->getSumVelocity(*bodyA, *bodyB);
			results->m_impulseApplied = temp->m_impulseApplied;
			results->m_internalSolverData = j->getRhs() * dampDivTauDt - v * velToRhs;
			jac = j + 1;
			goto singleElementDone;
		}

		singleElementDone:
			results = nextResult(results, resultStriding);
			temp++;
			schema = schema->getNext();
			break;

		case hkJacobianSchema::SCHEMA_TYPE_2D_FRICTION:
		{
			const hkJacobian2dFrictionSchema* s = (const hkJacobian2dFrictionSchema*)schema;
			const hk1Lin2AngJacobian* j = (const hk1Lin2AngJacobian*)jac;
			hkSolverResults* fr = s->m_frictionResults;
			const hkReal v0 = j[0].getSumVelocity(*bodyA, *bodyB);
			const hkReal v1 = j[1].getSumVelocity(*bodyA, *bodyB);
			const hkReal factor = s->m_usedImpulseFactor;
			fr->m_impulseApplied = temp[0].m_impulseApplied;
			fr->m_internalSolverData = (dampDivFrictionTauDt * j[0].getRhs() - v0 * velToRhs) * factor;
			fr = nextResult(fr, s->m_frictionResultStriding);
			fr->m_internalSolverData = factor * (dampDivFrictionTauDt * j[1].getRhs() - v1 * velToRhs);
			fr->m_impulseApplied = temp[1].m_impulseApplied;
			temp += 2;
			schema = hkAddByteOffsetConst<hkJacobianSchema>(schema, sizeof(hkJacobian2dFrictionSchema));
			jac = j + 2;
			break;
		}

		case hkJacobianSchema::SCHEMA_TYPE_3D_FRICTION:
		{
			const hkJacobian3dFrictionSchema* s = (const hkJacobian3dFrictionSchema*)schema;
			const hk1Lin2AngJacobian* j = (const hk1Lin2AngJacobian*)jac;
			const hk2AngJacobian* ja = (const hk2AngJacobian*)(j + 2);
			hkSolverResults* fr = s->m_frictionResults;
			const hkReal v0 = j[0].getSumVelocity(*bodyA, *bodyB);
			const hkReal v1 = j[1].getSumVelocity(*bodyA, *bodyB);
			const hkReal v2 = ja->getSumVelocity(*bodyA, *bodyB);
			const hkReal factor = s->m_usedImpulseFactor;
			fr->m_impulseApplied = temp[0].m_impulseApplied;
			fr->m_internalSolverData = (dampDivFrictionTauDt * j[0].getRhs() - v0 * velToRhs) * factor;
			fr = nextResult(fr, s->m_frictionResultStriding);
			fr->m_internalSolverData = factor * (dampDivFrictionTauDt * j[1].getRhs() - v1 * velToRhs);
			fr->m_impulseApplied = temp[1].m_impulseApplied;
			fr = nextResult(fr, s->m_frictionResultStriding);
			fr->m_impulseApplied = temp[2].m_impulseApplied;
			fr->m_internalSolverData = (dampDivFrictionTauDt * ja->getRhs() - v2 * velToRhs) * s->m_usedImpulseFactor;
			temp += 3;
			schema = hkAddByteOffsetConst<hkJacobianSchema>(schema, sizeof(hkJacobian3dFrictionSchema));
			jac = ja + 1;
			break;
		}

		case hkJacobianSchema::SCHEMA_TYPE_STIFF_SPRING_CHAIN:
		{
			const hkJacobianStiffSpringChainSchema* s = (const hkJacobianStiffSpringChainSchema*)schema;
			if (!results)
			{
				temp += s->m_numConstraints;
			}
			else
			{
				const hk1Lin2AngJacobian* j = (const hk1Lin2AngJacobian*)jac;
				for (int i = 0; i < s->m_numConstraints; i++, j++)
				{
					const hkVelocityAccumulator* a = hkAddByteOffsetConst<hkVelocityAccumulator>(accumulators, s->m_bodyOffsets[i]);
					const hkVelocityAccumulator* b = hkAddByteOffsetConst<hkVelocityAccumulator>(accumulators, s->m_bodyOffsets[i + 1]);
					const hkReal v = j->getSumVelocity(*a, *b);
					results->m_impulseApplied = temp->m_impulseApplied;
					results->m_internalSolverData = deltaTime * j->getRhs() - v * velToRhs;
					results = nextResult(results, resultStriding);
					temp++;
				}
			}
			jac = s->getEnd(jac);
			schema = schema->getNext();
			break;
		}

		case hkJacobianSchema::SCHEMA_TYPE_BALL_SOCKET_CHAIN:
		{
			const hkJacobianBallSocketChainSchema* s = (const hkJacobianBallSocketChainSchema*)schema;
			if (!results)
			{
				temp += s->m_numConstraints * 3;
			}
			else
			{
				const hk1Lin2AngJacobian* j = (const hk1Lin2AngJacobian*)jac;
				for (int i = 0; i < s->m_numConstraints * 3; i++, j++)
				{
					const hkVelocityAccumulator* a = hkAddByteOffsetConst<hkVelocityAccumulator>(accumulators, s->m_bodyOffsets[i]);
					const hkVelocityAccumulator* b = hkAddByteOffsetConst<hkVelocityAccumulator>(accumulators, s->m_bodyOffsets[i + 1]);
					const hkReal v = j->getSumVelocity(*a, *b);
					results->m_impulseApplied = temp->m_impulseApplied;
					results->m_internalSolverData = deltaTime * j->getRhs() - v * velToRhs;
					results = nextResult(results, resultStriding);
					temp++;
				}
			}
			jac = s->getEnd(jac);
			schema = schema->getNext();
			break;
		}

		case hkJacobianSchema::SCHEMA_TYPE_POWERED_CHAIN:
		{
			const hkJacobianPoweredChainSchema* s = (const hkJacobianPoweredChainSchema*)schema;
			for (int i = 0; i < s->m_numConstraints; i++)
			{
				s->m_limitFlagsOut[i] = s->getMotorInfo(i).m_limitFlags;
			}

			const int numConstraints = s->m_numConstraints;
			const hk2AngJacobian* angJac = (const hk2AngJacobian*)((const hk1Lin2AngJacobian*)jac + 3 * numConstraints);
			if (!results)
			{
				temp += numConstraints * 6;
			}
			else
			{
				const hk1Lin2AngJacobian* linJac = (const hk1Lin2AngJacobian*)jac;
				for (int i = 0; i < s->m_numConstraints; i++)
				{
					const hkPoweredChainMotorInfo& motor = s->getMotorInfo(i);
					for (int axis = 0; axis < 3; axis++, linJac++, angJac++)
					{
						const hkVelocityAccumulator* a = hkAddByteOffsetConst<hkVelocityAccumulator>(accumulators, s->m_bodyOffsets[i]);
						const hkVelocityAccumulator* b = hkAddByteOffsetConst<hkVelocityAccumulator>(accumulators, s->m_bodyOffsets[i + 1]);

						// linear part
						{
							const hkReal v = linJac->getSumVelocity(*a, *b);
							results[axis].m_impulseApplied = temp[axis].m_impulseApplied;
							results[axis].m_internalSolverData = deltaTime * linJac->getRhs() - v * velToRhs;
						}
						// angular (motor) part, clamped against the motor force limits
						{
							const hkReal v = angJac->getSumVelocity(*a, *b);
							results[3 + axis].m_impulseApplied = temp[3 + axis].m_impulseApplied;
							hkReal rhs = deltaTime * angJac->getRhs() - v * velToRhs;
							results[3 + axis].m_internalSolverData = rhs;

							const int shift = axis * 2;
							if (((motor.m_limitFlags >> shift) & 3) == 3)
							{
								rhs = hkMath::max2<hkReal>(rhs, motor.m_axis[axis].m_maxForce / angJac->getInvJacDiag()
								                                / motor.m_axis[axis].m_invMass * info.m_deltaTime * 1.5f);
								results[3 + axis].m_internalSolverData = rhs;
							}
							if (((motor.m_limitFlags >> shift) & 3) == 1)
							{
								results[3 + axis].m_internalSolverData =
									hkMath::min2<hkReal>(rhs, motor.m_axis[axis].m_minForce / angJac->getInvJacDiag()
									                          / motor.m_axis[axis].m_invMass * info.m_deltaTime * 1.5f);
							}
						}
					}
					results = nextResult(results, resultStriding * 6);
					temp += 6;
				}
			}
			jac = s->getEnd(jac);
			schema = schema->getNext();
			break;
		}

		case hkJacobianSchema::SCHEMA_TYPE_SKIP_2ANG:
			schema = schema->getNext();
			jac = hkAddByteOffsetConst<hkJacobianElement>(jac, sizeof(hk2AngJacobian));
			break;

		case hkJacobianSchema::SCHEMA_TYPE_GOTO:
		case hkJacobianSchema::SCHEMA_TYPE_SET_TAU:
		case hkJacobianSchema::SCHEMA_TYPE_SET_MASS:
			schema = schema->getNext();
			break;

		default:
			// Unknown types (and type 2) re-dispatch the same schema, as in the original.
			break;
		}
	}
}
