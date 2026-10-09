// Slice s010b8b30 — one function, @ 0x010b8b30 (19,112 bytes).
//
// Havok 3.1.0 (prebuilt, statically linked) constraint solver main loop, inferred to be
// hkSolveConstraints( info, schemas, accumulators, jacobians, temp ):
//   * one-time keycode check (hkSolverCheckKeycode, 0x010bfbe0);
//   * reset every velocity accumulator's sum-velocities and add the per-substep gravity;
//   * for each of info.m_numSteps substeps: walk the Jacobian schema stream and apply one
//     Gauss-Seidel impulse per Jacobian (26 schema types, jump table at 0x010bd570), then
//     integrate the accumulators (with the deactivation velocity check for dynamic bodies).
// Layouts: hkSolverInfo and DeactivationInfo are from the dev PDB (tools/pdb_type.py); the
// accumulator, Jacobian and schema layouts are read from the disassembly (names inferred, after
// the Havok 6 hkpSolve naming). The compiled original was built with float reassociation, so the
// order of the 3-term dot products below is canonical (x, y, z), not the original's schedule.
#include "types.h"
#include <intrin.h>
#include <math.h>

#define HK_BREAKPOINT() __debugbreak()
#define HK_FORCE_INLINE __forceinline

typedef uint8_t  hkUint8;
typedef uint16_t hkUint16;
typedef uint32_t hkUint32;
typedef int      hkBool32;

struct __declspec(align(16)) hkVector4
{
	float x, y, z, w;
};

// ---- hkSolverInfo (dev PDB, size 0x140) ----
struct hkSolverInfo
{
	struct DeactivationInfo                  // size 0x20
	{
		float m_linearVelocityThresholdInv;      // +0x00
		float m_angularVelocityThresholdInv;     // +0x04
		float m_slowObjectVelocityMultiplier;    // +0x08
		float m_relativeSleepVelocityThreshold;  // +0x0c
		hkUint32 m_stepsToDeactivate;            // +0x10
		hkUint32 m_padding[3];                   // +0x14
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

// ---- velocity accumulator (0x80-byte stride) ----
struct hkVelocityAccumulator
{
	enum { HK_RIGID_BODY = 0, HK_KEYFRAMED_RIGID_BODY = 1, HK_END = 2 };

	hkUint8 m_type;                      // +0x00
	hkUint8 m_pad01[3];
	hkUint32 m_deactivationCounter;      // +0x04 (unsigned: decremented only when != 0)
	int m_deactivationClass;             // +0x08 index into hkSolverInfo::m_deactivationInfo
	int m_pad0c;
	hkVector4 m_linearVel;               // +0x10
	hkVector4 m_angularVel;              // +0x20
	hkVector4 m_invMasses;               // +0x30 (xyz: inverse inertia diagonal, w: inverse mass)
	hkVector4 m_sumLinearVel;            // +0x40
	hkVector4 m_sumAngularVel;           // +0x50
	hkVector4 m_pad60[2];
};

// ---- Jacobian elements ----
class hkJacobianElement {};

// 0x30 bytes: linear (w = rhs), angular A (w = inverse effective mass), angular B
// (w = off-diagonal / second inverse-mass entry used by the 2D/3D cases).
class hk1Lin2AngJacobian : public hkJacobianElement
{
public:
	hkVector4 m_linear0;
	hkVector4 m_angular[2];

	float getRhs() const { return m_linear0.w; }
	float getInvJacDiag() const { return m_angular[0].w; }
	hkJacobianElement* next(int n);      // 0x010aa040 (out of line)
};

// 0x20 bytes: angular A (w = inverse effective mass), angular B (w = rhs).
class hk2AngJacobian : public hkJacobianElement
{
public:
	hkVector4 m_angular[2];

	float getInvJacDiag() const { return m_angular[0].w; }
	float& getRhs() { return m_angular[1].w; }
	float getRhs() const { return m_angular[1].w; }
};

// 0x40 bytes: linear A (w = rhs), linear B, angular A (w = inverse effective mass), angular B.
class hk2Lin2AngJacobian : public hkJacobianElement
{
public:
	hkVector4 m_linear[2];
	hkVector4 m_angular[2];

	float getRhs() const { return m_linear[0].w; }
	float getInvJacDiag() const { return m_angular[0].w; }
	hkJacobianElement* next(int n);      // 0x010b1d00 (out of line)
};

// ---- Jacobian schemas (byte type first; variable-size ones store their size at +2) ----
class hkJacobianSchema
{
public:
	hkUint8 m_type;                      // +0
	hkUint8 m_pad1;
	hkUint16 m_sizeOfSchema;             // +2 (types 0x03, 0x11, 0x12, 0x17..0x19)
};

struct hkJacobianHeaderSchema : hkJacobianSchema          // type 0x01, 0x18 bytes
{
	int m_jacobianOffset;                // +0x04 byte offset into the Jacobian buffer
	int m_bodyAOffset;                   // +0x08 byte offset into the accumulators
	int m_bodyBOffset;                   // +0x0c
	int m_pad10[2];
};

struct hkJacobianPairContactSchema : hkJacobianSchema     // type 0x05, 8 bytes
{
	float m_coupling;                    // +0x04 off-diagonal of the 2x2 inverse mass matrix
};

struct hkJacobianMotorSchema : hkJacobianSchema           // types 0x06/0x07, 0x1c bytes
{
	float m_maxImpulse;                  // +0x04
	float m_minImpulse;                  // +0x08
	float m_velocityDelta;               // +0x0c added to the Jacobian rhs every iteration
	float m_tau;                         // +0x10
	float m_damping;                     // +0x14
	float m_usedImpulseFactor;           // +0x18 (output)
};

struct hkJacobianFrictionSchema : hkJacobianSchema        // types 0x08/0x0b, 0x0c bytes
{
	float m_maxFrictionForce;            // +0x04
	float m_usedImpulseFactor;           // +0x08 (output)
};

struct hkJacobian2dFrictionSchema : hkJacobianSchema      // type 0x09, 0x18 bytes
{
	float m_pad04;
	float m_coupling;                    // +0x08
	float m_maxFrictionForce;            // +0x0c
	float m_usedImpulseFactor;           // +0x10 (output)
	float m_pad14;
};

struct hkJacobian3dFrictionSchema : hkJacobianSchema      // type 0x0a, 0x1c bytes
{
	float m_pad04;
	float m_coupling;                    // +0x08
	float m_maxFrictionForce;            // +0x0c
	float m_usedImpulseFactor;           // +0x10 (output)
	float m_pad14;
	float m_angularFrictionFactor;       // +0x18
};

struct hkJacobianAngularLimitsSchema : hkJacobianSchema   // type 0x0c, 0x10 bytes
{
	float m_maxLimit;                    // +0x04
	float m_minLimit;                    // +0x08
	float m_tau;                         // +0x0c
};

struct hkJacobianLinearLimitsSchema : hkJacobianSchema    // type 0x0d, 0x0c bytes
{
	float m_maxLimit;                    // +0x04
	float m_minLimit;                    // +0x08
};

struct hkJacobianUserTauSchema : hkJacobianSchema         // type 0x10, 0x0c bytes
{
	float m_tau;                         // +0x04
	float m_damping;                     // +0x08
};

struct hkJacobianSetTauSchema : hkJacobianSchema          // type 0x13, 0x0c bytes
{
	float m_tau;                         // +0x04
	float m_damping;                     // +0x08
};

struct hkJacobianStiffSpringChainSchema : hkJacobianSchema  // type 0x17
{
	int m_numConstraints;                // +0x04
	hkJacobianElement* getEnd(hkJacobianElement* j);   // 0x010b1d10
};

struct hkJacobianBallSocketChainSchema : hkJacobianSchema   // type 0x18
{
	int m_numConstraints;                // +0x04
	hkJacobianElement* getEnd(hkJacobianElement* j);   // 0x010b1d30
};

struct hkJacobianPoweredChainSchema : hkJacobianSchema      // type 0x19
{
	int m_pad04;
	int m_numConstraints;                // +0x08
	hkJacobianElement* getEnd(hkJacobianElement* j);   // 0x010b1d50
};

struct hkSolverElemTemp { float m_impulseApplied; };

// ---- out-of-line callees / globals (relocations, masked) ----
extern hkUint8 g_hkSolverKeycodeChecked;                 // 0x016e5180
extern hkVector4 g_hkKeyframedGravity;                   // 0x016e42d0 (hkVector4 constant)
char hkSolverCheckKeycode(int unused);                   // 0x010bfbe0
// Chain solvers (cdecl, 5 args): 0x010b22a0 / 0x010b2890 / 0x010b3b20.
void hkSolveStiffSpringChain(const hkSolverInfo& info, hkVelocityAccumulator* accums,
                             const hkJacobianSchema* schema, hkJacobianElement* jac, hkSolverElemTemp* temp); // 0x010b22a0
void hkSolveBallSocketChain(const hkSolverInfo& info, hkVelocityAccumulator* accums,
                            const hkJacobianSchema* schema, hkJacobianElement* jac, hkSolverElemTemp* temp); // 0x010b2890
void hkSolvePoweredChain(const hkSolverInfo& info, hkVelocityAccumulator* accums,
                         const hkJacobianSchema* schema, hkJacobianElement* jac, hkSolverElemTemp* temp); // 0x010b3b20

// =====================================================================================
// Inline solver helpers
// =====================================================================================

// Relative velocity along a 1Lin2Ang Jacobian.
static HK_FORCE_INLINE float getRelVel(const hk1Lin2AngJacobian& j, const hkVelocityAccumulator& a,
                              const hkVelocityAccumulator& b)
{
	const hkVector4& l = j.m_linear0;
	const hkVector4& p = j.m_angular[0];
	const hkVector4& q = j.m_angular[1];
	float tx = (b.m_angularVel.x * q.x + a.m_angularVel.x * p.x) + (a.m_linearVel.x - b.m_linearVel.x) * l.x;
	float ty = (b.m_angularVel.y * q.y + a.m_angularVel.y * p.y) + (a.m_linearVel.y - b.m_linearVel.y) * l.y;
	float tz = (b.m_angularVel.z * q.z + a.m_angularVel.z * p.z) + (a.m_linearVel.z - b.m_linearVel.z) * l.z;
	return (tx + ty) + tz;
}

// Relative velocity along a 2Lin2Ang Jacobian (separate linear parts for A and B).
static HK_FORCE_INLINE float getRelVel(const hk2Lin2AngJacobian& j, const hkVelocityAccumulator& a,
                              const hkVelocityAccumulator& b)
{
	float tx = (a.m_linearVel.x * j.m_linear[0].x - b.m_linearVel.x * j.m_linear[1].x)
	         + (b.m_angularVel.x * j.m_angular[1].x + a.m_angularVel.x * j.m_angular[0].x);
	float ty = (a.m_linearVel.y * j.m_linear[0].y - b.m_linearVel.y * j.m_linear[1].y)
	         + (b.m_angularVel.y * j.m_angular[1].y + a.m_angularVel.y * j.m_angular[0].y);
	float tz = (a.m_linearVel.z * j.m_linear[0].z - b.m_linearVel.z * j.m_linear[1].z)
	         + (b.m_angularVel.z * j.m_angular[1].z + a.m_angularVel.z * j.m_angular[0].z);
	return (tx + ty) + tz;
}

// Relative angular velocity along a 2Ang Jacobian.
static HK_FORCE_INLINE float getRelVel(const hk2AngJacobian& j, const hkVelocityAccumulator& a,
                              const hkVelocityAccumulator& b)
{
	float tx = b.m_angularVel.x * j.m_angular[1].x + a.m_angularVel.x * j.m_angular[0].x;
	float ty = b.m_angularVel.y * j.m_angular[1].y + a.m_angularVel.y * j.m_angular[0].y;
	float tz = b.m_angularVel.z * j.m_angular[1].z + a.m_angularVel.z * j.m_angular[0].z;
	return (tx + ty) + tz;
}

// Velocity seen by a stabilised (user-tau) 1Lin2Ang Jacobian: the summed velocities weighted by
// kSum plus the current-substep velocities (vel - sumVel) weighted by kVel.
static HK_FORCE_INLINE float getStabilizedRelVel(const hk1Lin2AngJacobian& j, const hkVelocityAccumulator& a,
                                        const hkVelocityAccumulator& b, float kSum, float kVel)
{
	const hkVector4& l = j.m_linear0;
	const hkVector4& p = j.m_angular[0];
	const hkVector4& q = j.m_angular[1];
	float sx = (b.m_sumAngularVel.x * q.x + a.m_sumAngularVel.x * p.x) + (a.m_sumLinearVel.x - b.m_sumLinearVel.x) * l.x;
	float sy = (b.m_sumAngularVel.y * q.y + a.m_sumAngularVel.y * p.y) + (a.m_sumLinearVel.y - b.m_sumLinearVel.y) * l.y;
	float sz = (b.m_sumAngularVel.z * q.z + a.m_sumAngularVel.z * p.z) + (a.m_sumLinearVel.z - b.m_sumLinearVel.z) * l.z;
	float vx = ((b.m_angularVel.x - b.m_sumAngularVel.x) * q.x + (a.m_angularVel.x - a.m_sumAngularVel.x) * p.x)
	         + ((a.m_linearVel.x - a.m_sumLinearVel.x) - (b.m_linearVel.x - b.m_sumLinearVel.x)) * l.x;
	float vy = ((b.m_angularVel.y - b.m_sumAngularVel.y) * q.y + (a.m_angularVel.y - a.m_sumAngularVel.y) * p.y)
	         + ((a.m_linearVel.y - a.m_sumLinearVel.y) - (b.m_linearVel.y - b.m_sumLinearVel.y)) * l.y;
	float vz = ((b.m_angularVel.z - b.m_sumAngularVel.z) * q.z + (a.m_angularVel.z - a.m_sumAngularVel.z) * p.z)
	         + ((a.m_linearVel.z - a.m_sumLinearVel.z) - (b.m_linearVel.z - b.m_sumLinearVel.z)) * l.z;
	return ((sx * kSum + vx * kVel) + (sy * kSum + vy * kVel)) + (sz * kSum + vz * kVel);
}

// Same for a 2Ang Jacobian.
static HK_FORCE_INLINE float getStabilizedRelVel(const hk2AngJacobian& j, const hkVelocityAccumulator& a,
                                        const hkVelocityAccumulator& b, float kSum, float kVel)
{
	const hkVector4& p = j.m_angular[0];
	const hkVector4& q = j.m_angular[1];
	float sx = b.m_sumAngularVel.x * q.x + a.m_sumAngularVel.x * p.x;
	float sy = b.m_sumAngularVel.y * q.y + a.m_sumAngularVel.y * p.y;
	float sz = b.m_sumAngularVel.z * q.z + a.m_sumAngularVel.z * p.z;
	float vx = (b.m_angularVel.x - b.m_sumAngularVel.x) * q.x + (a.m_angularVel.x - a.m_sumAngularVel.x) * p.x;
	float vy = (b.m_angularVel.y - b.m_sumAngularVel.y) * q.y + (a.m_angularVel.y - a.m_sumAngularVel.y) * p.y;
	float vz = (b.m_angularVel.z - b.m_sumAngularVel.z) * q.z + (a.m_angularVel.z - a.m_sumAngularVel.z) * p.z;
	return ((sx * kSum + vx * kVel) + (sy * kSum + vy * kVel)) + (sz * kSum + vz * kVel);
}

static HK_FORCE_INLINE void applyAngular(hkVelocityAccumulator& a, hkVelocityAccumulator& b,
                                const hkVector4& angA, const hkVector4& angB, float impulse)
{
	a.m_angularVel.x = (impulse * a.m_invMasses.x) * angA.x + a.m_angularVel.x;
	a.m_angularVel.y = (impulse * a.m_invMasses.y) * angA.y + a.m_angularVel.y;
	a.m_angularVel.z = (impulse * a.m_invMasses.z) * angA.z + a.m_angularVel.z;
	b.m_angularVel.x = (impulse * b.m_invMasses.x) * angB.x + b.m_angularVel.x;
	b.m_angularVel.y = (impulse * b.m_invMasses.y) * angB.y + b.m_angularVel.y;
	b.m_angularVel.z = (impulse * b.m_invMasses.z) * angB.z + b.m_angularVel.z;
}

// Apply an impulse along a 1Lin2Ang Jacobian (body B gets the negated linear part).
static HK_FORCE_INLINE void applyImpulse(const hk1Lin2AngJacobian& j, hkVelocityAccumulator& a,
                                hkVelocityAccumulator& b, float impulse)
{
	float la = impulse * a.m_invMasses.w;
	float lb = impulse * b.m_invMasses.w;
	a.m_linearVel.x = la * j.m_linear0.x + a.m_linearVel.x;
	a.m_linearVel.y = la * j.m_linear0.y + a.m_linearVel.y;
	a.m_linearVel.z = la * j.m_linear0.z + a.m_linearVel.z;
	b.m_linearVel.x = b.m_linearVel.x - lb * j.m_linear0.x;
	b.m_linearVel.y = b.m_linearVel.y - lb * j.m_linear0.y;
	b.m_linearVel.z = b.m_linearVel.z - lb * j.m_linear0.z;
	applyAngular(a, b, j.m_angular[0], j.m_angular[1], impulse);
}

static HK_FORCE_INLINE void applyImpulse(const hk2Lin2AngJacobian& j, hkVelocityAccumulator& a,
                                hkVelocityAccumulator& b, float impulse)
{
	float la = impulse * a.m_invMasses.w;
	float lb = impulse * b.m_invMasses.w;
	a.m_linearVel.x = la * j.m_linear[0].x + a.m_linearVel.x;
	a.m_linearVel.y = la * j.m_linear[0].y + a.m_linearVel.y;
	a.m_linearVel.z = la * j.m_linear[0].z + a.m_linearVel.z;
	b.m_linearVel.x = b.m_linearVel.x - lb * j.m_linear[1].x;
	b.m_linearVel.y = b.m_linearVel.y - lb * j.m_linear[1].y;
	b.m_linearVel.z = b.m_linearVel.z - lb * j.m_linear[1].z;
	applyAngular(a, b, j.m_angular[0], j.m_angular[1], impulse);
}

static HK_FORCE_INLINE void applyImpulse(const hk2AngJacobian& j, hkVelocityAccumulator& a,
                                hkVelocityAccumulator& b, float impulse)
{
	applyAngular(a, b, j.m_angular[0], j.m_angular[1], impulse);
}

// Motor-style clamp: clips the impulse into [min, max] and records the used fraction.
static HK_FORCE_INLINE float clampMotorImpulse(hkJacobianMotorSchema& s, float impulse)
{
	if (impulse > s.m_maxImpulse)
	{
		s.m_usedImpulseFactor = s.m_maxImpulse / impulse;
		impulse = s.m_maxImpulse;
	}
	else if (impulse < s.m_minImpulse)
	{
		s.m_usedImpulseFactor = s.m_minImpulse / impulse;
		impulse = s.m_minImpulse;
	}
	return impulse;
}

// 1D friction clamp: |impulse| <= maxFrictionForce.
static HK_FORCE_INLINE float clampFrictionImpulse(hkJacobianFrictionSchema& s, float impulse)
{
	float absImpulse = fabsf(impulse);
	if (s.m_maxFrictionForce < absImpulse)
	{
		float f = s.m_maxFrictionForce / absImpulse;
		impulse = impulse * f;
		s.m_usedImpulseFactor = f;
	}
	return impulse;
}

// Per-substep integration of the accumulated velocities (shared by both accumulator types).
static HK_FORCE_INLINE void integrateAccumulator(hkVelocityAccumulator& acc, float integrateFactor,
                                        const hkVector4& gravity, bool lastStep, float finalScale)
{
	hkVector4 dLin, dAng;
	dLin.x = acc.m_linearVel.x - acc.m_sumLinearVel.x;
	dLin.y = acc.m_linearVel.y - acc.m_sumLinearVel.y;
	dLin.z = acc.m_linearVel.z - acc.m_sumLinearVel.z;
	dLin.w = acc.m_linearVel.w - acc.m_sumLinearVel.w;
	dAng.x = acc.m_angularVel.x - acc.m_sumAngularVel.x;
	dAng.y = acc.m_angularVel.y - acc.m_sumAngularVel.y;
	dAng.z = acc.m_angularVel.z - acc.m_sumAngularVel.z;
	dAng.w = acc.m_angularVel.w - acc.m_sumAngularVel.w;

	acc.m_sumLinearVel.x = dLin.x * integrateFactor + acc.m_sumLinearVel.x;
	acc.m_sumLinearVel.y = dLin.y * integrateFactor + acc.m_sumLinearVel.y;
	acc.m_sumLinearVel.z = dLin.z * integrateFactor + acc.m_sumLinearVel.z;
	acc.m_sumLinearVel.w = dLin.w * integrateFactor + acc.m_sumLinearVel.w;
	acc.m_sumAngularVel.x = dAng.x * integrateFactor + acc.m_sumAngularVel.x;
	acc.m_sumAngularVel.y = dAng.y * integrateFactor + acc.m_sumAngularVel.y;
	acc.m_sumAngularVel.z = dAng.z * integrateFactor + acc.m_sumAngularVel.z;
	acc.m_sumAngularVel.w = dAng.w * integrateFactor + acc.m_sumAngularVel.w;

	if (lastStep)
	{
		// Final substep: scale the summed velocities; the velocities keep only the last delta.
		acc.m_sumLinearVel.x *= finalScale;
		acc.m_sumLinearVel.y *= finalScale;
		acc.m_sumLinearVel.z *= finalScale;
		acc.m_sumLinearVel.w *= finalScale;
		acc.m_sumAngularVel.x *= finalScale;
		acc.m_sumAngularVel.y *= finalScale;
		acc.m_sumAngularVel.z *= finalScale;
		acc.m_sumAngularVel.w *= finalScale;
	}
	else
	{
		dAng.x = dAng.x + acc.m_sumAngularVel.x;
		dAng.y = dAng.y + acc.m_sumAngularVel.y;
		dAng.z = dAng.z + acc.m_sumAngularVel.z;
		dAng.w = dAng.w + acc.m_sumAngularVel.w;
		dLin.x = (dLin.x + acc.m_sumLinearVel.x) + gravity.x;
		dLin.y = (dLin.y + acc.m_sumLinearVel.y) + gravity.y;
		dLin.z = (dLin.z + acc.m_sumLinearVel.z) + gravity.z;
		dLin.w = (dLin.w + acc.m_sumLinearVel.w) + gravity.w;
	}
	acc.m_linearVel = dLin;
	acc.m_angularVel = dAng;
}

static HK_FORCE_INLINE void scaleVector(hkVector4& v, float s)
{
	v.x = s * v.x; v.y = s * v.y; v.z = s * v.z; v.w = s * v.w;
}

static HK_FORCE_INLINE void setZero(hkVector4& v)
{
	v.x = 0.0f; v.y = 0.0f; v.z = 0.0f; v.w = 0.0f;
}

// Deactivation check of a dynamic body before integration.
static HK_FORCE_INLINE void checkDeactivation(const hkSolverInfo& info, hkVelocityAccumulator& acc)
{
	const hkSolverInfo::DeactivationInfo& d = info.m_deactivationInfo[acc.m_deactivationClass];
	float vx = d.m_angularVelocityThresholdInv * fabsf(acc.m_angularVel.x) + d.m_linearVelocityThresholdInv * fabsf(acc.m_linearVel.x);
	float vy = d.m_angularVelocityThresholdInv * fabsf(acc.m_angularVel.y) + d.m_linearVelocityThresholdInv * fabsf(acc.m_linearVel.y);
	float vz = d.m_angularVelocityThresholdInv * fabsf(acc.m_angularVel.z) + d.m_linearVelocityThresholdInv * fabsf(acc.m_linearVel.z);

	float one = info.m_one;
	if (one < vz || one < vy || one < vx)
	{
		acc.m_deactivationCounter = d.m_stepsToDeactivate;     // clearly moving
		return;
	}
	float t = d.m_relativeSleepVelocityThreshold;
	if (t < vz || t < vy || t < vx)
	{
		// slow: damp the velocities
		scaleVector(acc.m_angularVel, d.m_slowObjectVelocityMultiplier);
		scaleVector(acc.m_linearVel, d.m_slowObjectVelocityMultiplier);
		acc.m_deactivationCounter = d.m_stepsToDeactivate;
		return;
	}
	// resting: count down and freeze
	if (acc.m_deactivationCounter != 0)
		acc.m_deactivationCounter--;
	setZero(acc.m_angularVel);
	setZero(acc.m_linearVel);
}

// =====================================================================================
// @ 0x010b8b30
// =====================================================================================
hkBool32 hkSolveConstraints(hkSolverInfo& info, const hkJacobianSchema* schemas,
                            hkVelocityAccumulator* accumulators, char* jacobians,
                            hkSolverElemTemp* temp)
{
	if (!g_hkSolverKeycodeChecked)
	{
		g_hkSolverKeycodeChecked = hkSolverCheckKeycode(0);
		if (!g_hkSolverKeycodeChecked)
			return 0;
	}

	const hkVector4 gravity = info.m_globalAccelerationPerSubStep;

	// Reset the summed velocities and add one substep of gravity to the dynamic bodies.
	{
		hkVelocityAccumulator* acc = accumulators;
		for (;;)
		{
			switch (acc->m_type)
			{
			case hkVelocityAccumulator::HK_RIGID_BODY:
				setZero(acc->m_sumLinearVel);
				setZero(acc->m_sumAngularVel);
				acc->m_linearVel.x = gravity.x + acc->m_linearVel.x;
				acc->m_linearVel.y = gravity.y + acc->m_linearVel.y;
				acc->m_linearVel.z = gravity.z + acc->m_linearVel.z;
				acc->m_linearVel.w = gravity.w + acc->m_linearVel.w;
				acc++;
				continue;
			case hkVelocityAccumulator::HK_KEYFRAMED_RIGID_BODY:
				setZero(acc->m_sumLinearVel);
				setZero(acc->m_sumAngularVel);
				acc++;
				continue;
			case hkVelocityAccumulator::HK_END:
				break;
			default:
				HK_BREAKPOINT();
				continue;
			}
			break;
		}
	}

	const float finalScale = info.m_invNumSteps * info.m_invIntegrateVelocityFactor.x;
	if (info.m_numSteps <= 0)
		return 1;

	int step = 0;
	do
	{
		float savedTau = info.m_tau;
		float savedDamping = info.m_damping;

		const hkJacobianSchema* schema = schemas;
		hkSolverElemTemp* tmp = temp;
		hkJacobianElement* jac;
		hkVelocityAccumulator* bodyA;
		hkVelocityAccumulator* bodyB;

	nextHeader:
		{
			const hkJacobianHeaderSchema* h = static_cast<const hkJacobianHeaderSchema*>(schema);
			bodyA = (hkVelocityAccumulator*)((char*)accumulators + h->m_bodyAOffset);
			bodyB = (hkVelocityAccumulator*)((char*)accumulators + h->m_bodyBOffset);
			jac = (hkJacobianElement*)(jacobians + h->m_jacobianOffset);
			schema = (const hkJacobianSchema*)((const char*)schema + sizeof(hkJacobianHeaderSchema));
		}

		for (;;)
		{
			hkVelocityAccumulator& a = *bodyA;
			hkVelocityAccumulator& b = *bodyB;

			switch ((signed char)schema->m_type)
			{
			default:            // 0x02, 0x16 and anything out of range
				HK_BREAKPOINT();
				// fall through
			case 0x00:          // end of schemas
				goto integrate;

			case 0x01:          // header: new body pair / Jacobian block
				goto nextHeader;

			case 0x03:          // goto / skip
				schema = (const hkJacobianSchema*)((const char*)schema + schema->m_sizeOfSchema);
				break;

			case 0x04:          // single contact (non-penetration)
			{
				hk1Lin2AngJacobian* j = static_cast<hk1Lin2AngJacobian*>(jac);
				do
				{
					float rhs = j->getRhs() - getRelVel(*j, a, b);
					if (!(rhs < 0.0f))
					{
						float impulse = rhs * j->getInvJacDiag();
						applyImpulse(*j, a, b, impulse);
						tmp->m_impulseApplied = impulse + tmp->m_impulseApplied;
					}
					schema = (const hkJacobianSchema*)((const char*)schema + 4);
					j++;
					tmp++;
				} while (schema->m_type == 0x04);
				jac = j;
				break;
			}

			case 0x05:          // contact pair: 2x2 LCP
			{
				hk1Lin2AngJacobian* j = static_cast<hk1Lin2AngJacobian*>(jac);
				do
				{
					const hkJacobianPairContactSchema* s = static_cast<const hkJacobianPairContactSchema*>(schema);
					float r0 = j[0].getRhs() - getRelVel(j[0], a, b);
					float r1 = j[1].getRhs() - getRelVel(j[1], a, b);
					float i0 = r1 * s->m_coupling + r0 * j[0].m_angular[1].w;
					float i1 = r0 * s->m_coupling + r1 * j[1].m_angular[1].w;
					if (i0 <= 0.0f)
					{
						float x1 = r1 * j[1].getInvJacDiag();
						if (x1 <= 0.0f)
							goto pairSingle0;
						applyImpulse(j[1], a, b, x1);
						tmp[1].m_impulseApplied = x1 + tmp[1].m_impulseApplied;
					}
					else if (i1 <= 0.0f)
					{
					pairSingle0:
						float x0 = r0 * j[0].getInvJacDiag();
						if (0.0f < x0)
						{
							applyImpulse(j[0], a, b, x0);
							tmp[0].m_impulseApplied = x0 + tmp[0].m_impulseApplied;
						}
					}
					else
					{
						applyImpulse(j[0], a, b, i0);
						tmp[0].m_impulseApplied = i0 + tmp[0].m_impulseApplied;
						applyImpulse(j[1], a, b, i1);
						tmp[1].m_impulseApplied = i1 + tmp[1].m_impulseApplied;
					}
					schema = (const hkJacobianSchema*)((const char*)schema + sizeof(hkJacobianPairContactSchema));
					j += 2;
					tmp += 2;
				} while (schema->m_type == 0x05);
				jac = j;
				break;
			}

			case 0x06:          // angular motor
			{
				hk2AngJacobian* j = static_cast<hk2AngJacobian*>(jac);
				do
				{
					hkJacobianMotorSchema* s = (hkJacobianMotorSchema*)schema;
					float rhs = s->m_velocityDelta + j->getRhs();
					j->getRhs() = rhs;
					float vel = getStabilizedRelVel(*j, a, b, s->m_tau * info.m_invIntegrateVelocityFactor.x, s->m_damping);
					float impulse = clampMotorImpulse(*s, (rhs * s->m_tau - vel) * j->getInvJacDiag());
					schema = (const hkJacobianSchema*)((const char*)schema + sizeof(hkJacobianMotorSchema));
					applyImpulse(*j, a, b, impulse);
					tmp->m_impulseApplied = impulse + tmp->m_impulseApplied;
					tmp++;
					j++;
				} while (schema->m_type == 0x06);
				jac = j;
				break;
			}

			case 0x07:          // linear motor
			{
				do
				{
					hk1Lin2AngJacobian* j = static_cast<hk1Lin2AngJacobian*>(jac);
					hkJacobianMotorSchema* s = (hkJacobianMotorSchema*)schema;
					float rhs = s->m_velocityDelta + j->m_linear0.w;
					j->m_linear0.w = rhs;
					float vel = getStabilizedRelVel(*j, a, b, s->m_tau * info.m_invIntegrateVelocityFactor.x, s->m_damping);
					float impulse = clampMotorImpulse(*s, (rhs * s->m_tau - vel) * j->getInvJacDiag());
					applyImpulse(*j, a, b, impulse);
					tmp->m_impulseApplied = impulse + tmp->m_impulseApplied;
					jac = j->next(1);
					tmp++;
					schema = (const hkJacobianSchema*)((const char*)schema + sizeof(hkJacobianMotorSchema));
				} while (schema->m_type == 0x07);
				break;
			}

			case 0x08:          // linear friction
			{
				do
				{
					hk1Lin2AngJacobian* j = static_cast<hk1Lin2AngJacobian*>(jac);
					hkJacobianFrictionSchema* s = (hkJacobianFrictionSchema*)schema;
					float impulse = (j->getRhs() - getRelVel(*j, a, b)) * j->getInvJacDiag();
					impulse = clampFrictionImpulse(*s, impulse);
					applyImpulse(*j, a, b, impulse);
					tmp->m_impulseApplied = impulse + tmp->m_impulseApplied;
					jac = j->next(1);
					tmp++;
					schema = (const hkJacobianSchema*)((const char*)schema + sizeof(hkJacobianFrictionSchema));
				} while (schema->m_type == 0x08);
				break;
			}

			case 0x09:          // 2D friction
			{
				hk1Lin2AngJacobian* j = static_cast<hk1Lin2AngJacobian*>(jac);
				hkJacobian2dFrictionSchema* s = (hkJacobian2dFrictionSchema*)schema;
				float r0 = j[0].getRhs() - getRelVel(j[0], a, b);
				float r1 = j[1].getRhs() - getRelVel(j[1], a, b);
				float maxSq = s->m_maxFrictionForce * s->m_maxFrictionForce;
				float i0 = r1 * s->m_coupling + r0 * j[0].m_angular[1].w;
				float i1 = r0 * s->m_coupling + r1 * j[1].m_angular[1].w;
				float lenSq = i0 * i0 + i1 * i1;
				if (maxSq < lenSq)
				{
					float f = sqrtf(maxSq / lenSq);
					i0 = f * i0;
					i1 = f * i1;
					s->m_usedImpulseFactor = f;
				}
				applyImpulse(j[0], a, b, i0);
				tmp[0].m_impulseApplied = i0 + tmp[0].m_impulseApplied;
				applyImpulse(j[1], a, b, i1);
				tmp[1].m_impulseApplied = i1 + tmp[1].m_impulseApplied;
				schema = (const hkJacobianSchema*)((const char*)schema + sizeof(hkJacobian2dFrictionSchema));
				jac = j + 2;
				tmp += 2;
				break;
			}

			case 0x0a:          // 3D friction (2 linear + 1 angular)
			{
				hk1Lin2AngJacobian* j = static_cast<hk1Lin2AngJacobian*>(jac);
				hk2AngJacobian* ja = (hk2AngJacobian*)(j + 2);
				hkJacobian3dFrictionSchema* s = (hkJacobian3dFrictionSchema*)schema;
				float r0 = j[0].getRhs() - getRelVel(j[0], a, b);
				float r1 = j[1].getRhs() - getRelVel(j[1], a, b);
				float r2 = (ja->getRhs() - getRelVel(*ja, a, b)) * ja->getInvJacDiag();
				float i0 = r1 * s->m_coupling + r0 * j[0].m_angular[1].w;
				float i1 = r0 * s->m_coupling + r1 * j[1].m_angular[1].w;
				float lenSq = r2 * r2 + (i0 * i0 + i1 * i1);
				if (s->m_maxFrictionForce * s->m_maxFrictionForce < lenSq)
				{
					float f = s->m_maxFrictionForce / sqrtf(lenSq);
					i0 = f * i0;
					i1 = f * i1;
					r2 = f * r2;
					s->m_usedImpulseFactor = f;
				}
				r2 = r2 * s->m_angularFrictionFactor;
				applyImpulse(j[0], a, b, i0);
				tmp[0].m_impulseApplied = i0 + tmp[0].m_impulseApplied;
				applyImpulse(j[1], a, b, i1);
				tmp[1].m_impulseApplied = i1 + tmp[1].m_impulseApplied;
				applyImpulse(*ja, a, b, r2);
				tmp[2].m_impulseApplied = r2 + tmp[2].m_impulseApplied;
				schema = (const hkJacobianSchema*)((const char*)schema + sizeof(hkJacobian3dFrictionSchema));
				jac = ja + 1;
				tmp += 3;
				break;
			}

			case 0x0b:          // angular friction
			{
				hk2AngJacobian* j = static_cast<hk2AngJacobian*>(jac);
				do
				{
					hkJacobianFrictionSchema* s = (hkJacobianFrictionSchema*)schema;
					float impulse = (j->getRhs() - getRelVel(*j, a, b)) * j->getInvJacDiag();
					impulse = clampFrictionImpulse(*s, impulse);
					schema = (const hkJacobianSchema*)((const char*)schema + sizeof(hkJacobianFrictionSchema));
					applyImpulse(*j, a, b, impulse);
					tmp->m_impulseApplied = impulse + tmp->m_impulseApplied;
					tmp++;
					j++;
				} while (schema->m_type == 0x0b);
				jac = j;
				break;
			}

			case 0x0c:          // angular limits (stabilised)
			{
				hk2AngJacobian* j = static_cast<hk2AngJacobian*>(jac);
				do
				{
					const hkJacobianAngularLimitsSchema* s = static_cast<const hkJacobianAngularLimitsSchema*>(schema);
					float kSum = s->m_tau * info.m_invIntegrateVelocityFactor.x;
					float rhs = s->m_tau * j->getRhs() - getStabilizedRelVel(*j, a, b, kSum, info.m_damping);
					float over = rhs - s->m_maxLimit;
					if (over <= 0.0f)
					{
						float under = rhs - s->m_minLimit;
						if (under < 0.0f)
						{
							float impulse = under * j->getInvJacDiag();
							applyImpulse(*j, a, b, impulse);
							tmp->m_impulseApplied = impulse + tmp->m_impulseApplied;
						}
					}
					else
					{
						float impulse = over * j->getInvJacDiag();
						applyImpulse(*j, a, b, impulse);
						tmp->m_impulseApplied = impulse + tmp->m_impulseApplied;
					}
					j++;
					schema = (const hkJacobianSchema*)((const char*)schema + sizeof(hkJacobianAngularLimitsSchema));
					tmp++;
				} while (schema->m_type == 0x0c);
				jac = j;
				break;
			}

			case 0x0d:          // linear limits
			{
				do
				{
					hk1Lin2AngJacobian* j = static_cast<hk1Lin2AngJacobian*>(jac);
					const hkJacobianLinearLimitsSchema* s = static_cast<const hkJacobianLinearLimitsSchema*>(schema);
					float rhs = j->getRhs() - getRelVel(*j, a, b);
					float over = rhs - s->m_maxLimit;
					if (0.0f < over)
					{
						float impulse = over * j->getInvJacDiag();
						applyImpulse(*j, a, b, impulse);
						tmp->m_impulseApplied = impulse + tmp->m_impulseApplied;
					}
					float under = rhs - s->m_minLimit;
					if (under < 0.0f)
					{
						float impulse = under * j->getInvJacDiag();
						applyImpulse(*j, a, b, impulse);
						tmp->m_impulseApplied = impulse + tmp->m_impulseApplied;
					}
					jac = j->next(1);
					tmp++;
					schema = (const hkJacobianSchema*)((const char*)schema + sizeof(hkJacobianLinearLimitsSchema));
				} while (schema->m_type == 0x0d);
				break;
			}

			case 0x0e:          // 1D angular bilateral
			{
				hk2AngJacobian* j = static_cast<hk2AngJacobian*>(jac);
				do
				{
					float impulse = (j->getRhs() - getRelVel(*j, a, b)) * j->getInvJacDiag();
					applyImpulse(*j, a, b, impulse);
					tmp->m_impulseApplied = impulse + tmp->m_impulseApplied;
					schema = (const hkJacobianSchema*)((const char*)schema + 4);
					j++;
					tmp++;
				} while (schema->m_type == 0x0e);
				jac = j;
				break;
			}

			case 0x0f:          // 1D linear bilateral
			{
				do
				{
					hk1Lin2AngJacobian* j = static_cast<hk1Lin2AngJacobian*>(jac);
					float impulse = (j->getRhs() - getRelVel(*j, a, b)) * j->getInvJacDiag();
					applyImpulse(*j, a, b, impulse);
					tmp->m_impulseApplied = impulse + tmp->m_impulseApplied;
					jac = j->next(1);
					tmp++;
					schema = (const hkJacobianSchema*)((const char*)schema + 4);
				} while (schema->m_type == 0x0f);
				break;
			}

			case 0x10:          // 1D linear bilateral with user tau/damping
			{
				do
				{
					hk1Lin2AngJacobian* j = static_cast<hk1Lin2AngJacobian*>(jac);
					const hkJacobianUserTauSchema* s = static_cast<const hkJacobianUserTauSchema*>(schema);
					float vel = getStabilizedRelVel(*j, a, b, s->m_tau * info.m_invIntegrateVelocityFactor.x, s->m_damping);
					float impulse = (s->m_tau * j->getRhs() - vel) * j->getInvJacDiag();
					applyImpulse(*j, a, b, impulse);
					tmp->m_impulseApplied = impulse + tmp->m_impulseApplied;
					jac = j->next(1);
					tmp++;
					schema = (const hkJacobianSchema*)((const char*)schema + sizeof(hkJacobianUserTauSchema));
				} while (schema->m_type == 0x10);
				break;
			}

			case 0x11:          // set the masses of the body pair
			{
				const hkVector4* m = (const hkVector4*)jac;
				a.m_invMasses = m[0];
				b.m_invMasses = m[1];
				jac = (hkJacobianElement*)(m + 2);
				schema = (const hkJacobianSchema*)((const char*)schema + schema->m_sizeOfSchema);
				break;
			}

			case 0x12:          // add a velocity to body A (and its substep-integrated share)
			{
				const hkVector4& v = *(const hkVector4*)jac;
				float f = (float)step * info.m_integrateVelocityFactor.x;
				a.m_linearVel.x = a.m_linearVel.x + v.x;
				a.m_linearVel.y = a.m_linearVel.y + v.y;
				a.m_linearVel.z = a.m_linearVel.z + v.z;
				a.m_linearVel.w = a.m_linearVel.w + v.w;
				a.m_linearVel.x = f * v.x + a.m_linearVel.x;
				a.m_linearVel.y = f * v.y + a.m_linearVel.y;
				a.m_linearVel.z = f * v.z + a.m_linearVel.z;
				a.m_linearVel.w = f * v.w + a.m_linearVel.w;
				a.m_sumLinearVel.x = f * v.x + a.m_sumLinearVel.x;
				a.m_sumLinearVel.y = f * v.y + a.m_sumLinearVel.y;
				a.m_sumLinearVel.z = f * v.z + a.m_sumLinearVel.z;
				a.m_sumLinearVel.w = f * v.w + a.m_sumLinearVel.w;
				jac = (hkJacobianElement*)(&v + 1);
				schema = (const hkJacobianSchema*)((const char*)schema + schema->m_sizeOfSchema);
				break;
			}

			case 0x13:          // override tau / damping
			{
				const hkJacobianSetTauSchema* s = static_cast<const hkJacobianSetTauSchema*>(schema);
				savedDamping = info.m_damping;
				savedTau = info.m_tau;
				info.m_damping = s->m_damping;
				info.m_tau = s->m_tau;
				schema = (const hkJacobianSchema*)((const char*)schema + sizeof(hkJacobianSetTauSchema));
				break;
			}

			case 0x14:          // restore tau / damping
				info.m_tau = savedTau;
				info.m_damping = savedDamping;
				schema = (const hkJacobianSchema*)((const char*)schema + 4);
				break;

			case 0x15:          // 1D bilateral, separate linear parts (2Lin2Ang)
			{
				hk2Lin2AngJacobian* j = static_cast<hk2Lin2AngJacobian*>(jac);
				float impulse = (j->getRhs() - getRelVel(*j, a, b)) * j->getInvJacDiag();
				applyImpulse(*j, a, b, impulse);
				tmp->m_impulseApplied = impulse + tmp->m_impulseApplied;
				jac = j->next(1);
				tmp++;
				schema = (const hkJacobianSchema*)((const char*)schema + 0xc);
				break;
			}

			case 0x17:          // stiff-spring chain
			{
				hkSolveStiffSpringChain(info, accumulators, schema, jac, tmp); // 0x010b22a0
				hkJacobianStiffSpringChainSchema* s = (hkJacobianStiffSpringChainSchema*)schema;
				tmp += s->m_numConstraints;
				jac = s->getEnd(jac);
				schema = (const hkJacobianSchema*)((const char*)schema + schema->m_sizeOfSchema);
				break;
			}

			case 0x18:          // ball-socket chain
			{
				hkSolveBallSocketChain(info, accumulators, schema, jac, tmp); // 0x010b2890
				hkJacobianBallSocketChainSchema* s = (hkJacobianBallSocketChainSchema*)schema;
				tmp += s->m_numConstraints * 3;
				jac = s->getEnd(jac);
				schema = (const hkJacobianSchema*)((const char*)schema + schema->m_sizeOfSchema);
				break;
			}

			case 0x19:          // powered chain
			{
				hkSolvePoweredChain(info, accumulators, schema, jac, tmp); // 0x010b3b20
				hkJacobianPoweredChainSchema* s = (hkJacobianPoweredChainSchema*)schema;
				tmp += s->m_numConstraints * 6;
				jac = s->getEnd(jac);
				schema = (const hkJacobianSchema*)((const char*)schema + schema->m_sizeOfSchema);
				break;
			}
			}
		}

	integrate:
		{
			const bool lastStep = (step == info.m_numSteps - 1);
			hkVelocityAccumulator* acc = accumulators;
			for (;;)
			{
				hkUint8 type = acc->m_type;
				if (type == hkVelocityAccumulator::HK_RIGID_BODY)
				{
					checkDeactivation(info, *acc);
					integrateAccumulator(*acc, info.m_integrateVelocityFactor.x, gravity, lastStep, finalScale);
					acc++;
				}
				else if (type == hkVelocityAccumulator::HK_KEYFRAMED_RIGID_BODY)
				{
					integrateAccumulator(*acc, info.m_integrateVelocityFactor.x, g_hkKeyframedGravity, lastStep, finalScale);
					acc++;
				}
				else if (type == hkVelocityAccumulator::HK_END)
				{
					break;
				}
				// any other type: the original spins re-reading the same entry
			}
		}
		step++;
	} while (step < info.m_numSteps);

	return 1;
}
// --- equivalence checker address annotations
    void hkSolveBallSocketChain(...); // 0x010b2890
    void hkSolvePoweredChain(...); // 0x010b3b20
    void hkSolveStiffSpringChain(...); // 0x010b22a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
