// Slice s0108eb30: hkWheelConstraintData::buildJacobian (Havok 3.1.0, 0x0108eb30, 2029 bytes).
// Flags: /vc71 /O2 /MD /Gy /TP /fp:fast.
// Layout from the asm: basisA {pivot +0x10, axle +0x20}, basisB {pivot +0x30, steering +0x40, perpSteering +0x50,
// suspension +0x60, perpSuspension +0x70, referenceAxle +0x80 (unused here)}, suspension min/max/strength/damping
// +0x90..+0x9c. Rows: 2 angular bilateral, 2 linear bilateral (pivotB projected on the suspension axis), the
// suspension limit and the user-tau spring row.
#include "types.h"

typedef float hkReal;

extern const float kZero;   // 0x01485378

class __declspec(align(16)) hkVector4
{
public:
	float x, y, z, w;
	__forceinline void addTranslation(const hkVector4& t) { x = x + t.x; y = y + t.y; z = z + t.z; w = t.w; }
};

class hkMatrix3
{
public:
	hkVector4 m_col[3];
};
class hkRotation : public hkMatrix3 {};

class hkTransform
{
public:
	hkRotation m_rotation;     // +0x00
	hkVector4 m_translation;   // +0x30
};

__forceinline void setRotatedDir(hkVector4& d, const hkRotation& r, const hkVector4& v)
{
	const float vx = v.x, vy = v.y, vz = v.z;
	d.x = (vz * r.m_col[2].x + vy * r.m_col[1].x) + vx * r.m_col[0].x;
	d.y = (vz * r.m_col[2].y + vy * r.m_col[1].y) + vx * r.m_col[0].y;
	d.z = (vz * r.m_col[2].z + vy * r.m_col[1].z) + vx * r.m_col[0].z;
	d.w = 0.0f;
}

struct hkSolverResults
{
	hkReal m_impulseApplied;        // +0
	hkReal m_internalSolverData;    // +4
};

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


struct hkWheelInfo4
{
	hkVector4 a, b, c;
};
struct hk1dLinearBilateralConstraintInfo
{
	hkVector4 m_pivotA;                      // +0x00
	hkVector4 m_pivotB;                      // +0x10
	hkVector4 m_constrainedDofW;             // +0x20
};
struct hk1dLinearLimitInfo
{
	hkVector4 m_pivotA;                      // +0x00
	hkVector4 m_pivotB;                      // +0x10
	hkVector4 m_constrainedDofW;             // +0x20
	hkReal m_min;                            // +0x30 (min / tau)
	hkReal m_max;                            // +0x34 (max / damping)
};
struct hk1dAngularBilateralConstraintInfo
{
	hkVector4 m_zeroErrorAxisAinW;           // +0x00
	hkVector4 m_constrainedDofW;             // +0x10
	hkVector4 m_perpZeroErrorAxisBinW;       // +0x20
};

extern "C" void hkBeginConstraints(const hkConstraintQueryIn& in, hkConstraintQueryOut& out,
                                   hkSolverResults* sr, int solverResultStriding);                        // 0x010AA080
extern "C" void hk1dAngularBilateralConstraintBuildJacobian(const hk1dAngularBilateralConstraintInfo& info,
                                                            const hkConstraintQueryIn& in,
                                                            hkConstraintQueryOut& out);                   // 0x010AA1E0
extern "C" void hk1dLinearBilateralConstraintBuildJacobian(const hk1dLinearBilateralConstraintInfo& info,
                                                           const hkConstraintQueryIn& in,
                                                           hkConstraintQueryOut& out);                    // 0x010AA890
extern "C" void hk1dLinearLimitBuildJacobian(const hk1dLinearLimitInfo& info, const hkConstraintQueryIn& in,
                                             hkConstraintQueryOut& out);                                  // 0x010AAE10
extern "C" void hk1dLinearBilateralConstraintUserTauBuildJacobian(const hk1dLinearLimitInfo& info,
                                                                  const hkConstraintQueryIn& in,
                                                                  hkConstraintQueryOut& out);             // 0x010AAB50

struct hkWheelBasisA
{
	hkVector4 m_pivot;   // +0x00
	hkVector4 m_axle;    // +0x10
};
struct hkWheelBasisB
{
	hkVector4 m_pivot;                 // +0x00
	hkVector4 m_steeringAxis;          // +0x10
	hkVector4 m_perpToSteeringAxis;    // +0x20
	hkVector4 m_suspensionAxis;        // +0x30
	hkVector4 m_perpToSuspensionAxis;  // +0x40
	hkVector4 m_referenceAxle;         // +0x50
};

class hkConstraintData
{
public:
	virtual ~hkConstraintData();
	int m_memSizeAndFlags_userData[2];  // +0x04
};

class hkWheelConstraintData : public hkConstraintData
{
public:
	hkWheelBasisA m_basisA;          // +0x10
	hkWheelBasisB m_basisB;          // +0x30
	hkReal m_suspensionMinLimit;     // +0x90
	hkReal m_suspensionMaxLimit;     // +0x94
	hkReal m_suspensionStrength;     // +0x98
	hkReal m_suspensionDamping;      // +0x9c

	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void vslot6();
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);
};

// @ 0x0108eb30
void hkWheelConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	hkBeginConstraints(in, out, (hkSolverResults*)in.m_constraintRuntime, 8);

	const hkTransform& tA = *in.m_transformA;
	hkVector4 pivotAW;
	setRotatedDir(pivotAW, tA.m_rotation, m_basisA.m_pivot);
	pivotAW.addTranslation(tA.m_translation);
	hkVector4 axleAW;
	setRotatedDir(axleAW, tA.m_rotation, m_basisA.m_axle);

	const hkTransform& tB = *in.m_transformB;
	hkVector4 pivotBW;
	setRotatedDir(pivotBW, tB.m_rotation, m_basisB.m_pivot);
	pivotBW.addTranslation(tB.m_translation);
	hkVector4 steerBW;
	setRotatedDir(steerBW, tB.m_rotation, m_basisB.m_steeringAxis);
	hkVector4 perpSteerBW;
	setRotatedDir(perpSteerBW, tB.m_rotation, m_basisB.m_perpToSteeringAxis);
	hkVector4 suspBW;
	setRotatedDir(suspBW, tB.m_rotation, m_basisB.m_suspensionAxis);
	hkVector4 perpSuspBW;
	setRotatedDir(perpSuspBW, tB.m_rotation, m_basisB.m_perpToSuspensionAxis);

	// angular: A's axle against B's steering axis, then its perpendicular
	{
		hk1dAngularBilateralConstraintInfo ang;
		ang.m_zeroErrorAxisAinW = axleAW;
		ang.m_constrainedDofW.x = axleAW.y * steerBW.z - axleAW.z * steerBW.y;
		ang.m_constrainedDofW.y = axleAW.z * steerBW.x - axleAW.x * steerBW.z;
		ang.m_constrainedDofW.z = axleAW.x * steerBW.y - axleAW.y * steerBW.x;
		ang.m_constrainedDofW.w = 0.0f;
		ang.m_perpZeroErrorAxisBinW = steerBW;
		hk1dAngularBilateralConstraintBuildJacobian(ang, in, out);
		ang.m_constrainedDofW.x = -steerBW.x;
		ang.m_constrainedDofW.y = -steerBW.y;
		ang.m_constrainedDofW.z = -steerBW.z;
		ang.m_constrainedDofW.w = 0.0f;
		ang.m_perpZeroErrorAxisBinW = perpSteerBW;
		hk1dAngularBilateralConstraintBuildJacobian(ang, in, out);
	}

	// linear: pivot A against B's pivot projected onto the suspension axis, two perpendicular rows
	{
		hk1dLinearBilateralConstraintInfo lin;
		lin.m_pivotA = pivotAW;
		const double t = ((pivotAW.x - pivotBW.x) * suspBW.x + (pivotAW.z - pivotBW.z) * suspBW.z) +
			(pivotAW.y - pivotBW.y) * suspBW.y;
		lin.m_pivotB.x = (float)(suspBW.x * t + pivotBW.x);
		lin.m_pivotB.y = (float)(suspBW.y * t + pivotBW.y);
		lin.m_pivotB.z = (float)(suspBW.z * t + pivotBW.z);
		lin.m_pivotB.w = (float)(t * 0.0f + pivotBW.w);
		lin.m_constrainedDofW = perpSuspBW;
		hk1dLinearBilateralConstraintBuildJacobian(lin, in, out);
		const hkVector4 d = lin.m_constrainedDofW;
		lin.m_constrainedDofW.x = d.z * suspBW.y - d.y * suspBW.z;
		lin.m_constrainedDofW.y = suspBW.z * d.x - d.z * suspBW.x;
		lin.m_constrainedDofW.z = d.y * suspBW.x - suspBW.y * d.x;
		lin.m_constrainedDofW.w = 0.0f;
		hk1dLinearBilateralConstraintBuildJacobian(lin, in, out);
	}

	// suspension limit, then the spring row
	{
		hk1dLinearLimitInfo lim;
		lim.m_pivotA = pivotAW;
		lim.m_pivotB = pivotBW;
		lim.m_constrainedDofW = suspBW;
		lim.m_min = m_suspensionMinLimit;
		lim.m_max = m_suspensionMaxLimit;
		hk1dLinearLimitBuildJacobian(lim, in, out);
	}
	{
		hk1dLinearLimitInfo spr;
		spr.m_pivotA = pivotAW;
		spr.m_pivotB = pivotBW;
		spr.m_constrainedDofW = suspBW;
		spr.m_min = m_suspensionStrength;
		spr.m_max = m_suspensionDamping;
		hk1dLinearBilateralConstraintUserTauBuildJacobian(spr, in, out);
	}
}
