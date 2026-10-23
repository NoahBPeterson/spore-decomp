// Slice s010edf70: Havok 3.1.0 (0x010EDF70..0x010EE9ED).
//
//   0x010EDF70  hkGeometryUtility::createConvexGeometry          (cdecl, 4 args)
//   0x010EE1B0  hkRagdollLimitsData::buildLimits                 (thiscall, ret 0x14)
//   0x010EE410  hkRagdollLimitsData::isValid                     (virtual, hkBool sret, ret 4)
//   0x010EE550  hkRagdollLimitsData::buildJacobian               (virtual, ret 8)
//   0x010EEA50  hkRagdollConstraintData::buildLimits             (thiscall, ret 0x14)
//   0x010EECB0  hkRagdollConstraintData::isValid                 (virtual, hkBool sret, ret 4)
//   0x010EEDD0  hkRagdollConstraintData::hkRagdollConstraintData(int)  (thiscall, ret 4)
//
// Layouts: match/include/havok31/hkReflectedClasses.h (hkRagdollConstraintData 0x90 @773,
// hkRagdollLimitsData 0x70 @844).  The keycode flag bytes are 0x016E5AAC (limits) and
// 0x016E5AAD (constraint).  Float 1.1920929e-07 lives at 0x014A5950 (limits) / 0x014A5990
// (constraint); 1.0f at 0x01485720, 0.0f at 0x01485378, 1e-05f at 0x013F89BC.
//
// Flags: /vc71 /O2 /MD /Gy /TP   (Havok 3.1.0 shipped with cl 13.10.3077).
#include "types.h"
#include <math.h>
#include <stddef.h>

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long index, void* value);

typedef float hkReal;
typedef unsigned int hkUint32;
typedef unsigned short hkUint16;
typedef unsigned char hkUint8;

// ---------------------------------------------------------------------------
// float / x87 helpers
// ---------------------------------------------------------------------------
extern const float kZero;   // 0x01485378
extern const float kOne;    // 0x01485720

class __declspec(align(16)) hkVector4
{
public:
	hkReal x, y, z, w;
};

static __forceinline float hkLen3sq(const hkVector4& v) { return v.x * v.x + v.y * v.y + v.z * v.z; }
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
static float hkAbsF(float v) { return (float)fabs(v); }

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

// hkVector4::setRotatedDir (out of line at 0x010814A0, inlined here).
static __forceinline void setRotatedDir(hkVector4& d, const hkRotation& r, const hkVector4& v)
{
	const float vx = v.x, vy = v.y, vz = v.z;
	d.x = vx * r.m_col[0].x + (r.m_col[1].x * vy + r.m_col[2].x * vz);
	d.y = r.m_col[0].y * vx + (r.m_col[1].y * vy + r.m_col[2].y * vz);
	d.z = vx * r.m_col[0].z + (r.m_col[1].z * vy + r.m_col[2].z * vz);
	d.w = 0.0f;
}

static __forceinline float hkDot3(const hkVector4& a, const hkVector4& b)
{
	return a.x * b.x + (a.y * b.y + a.z * b.z);
}

// ---------------------------------------------------------------------------
// hkBool (returned by value through a hidden sret pointer)
// ---------------------------------------------------------------------------
class hkBool
{
public:
	hkBool() {}
	hkBool(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
	char m_bool;
};

// ---------------------------------------------------------------------------
// monitor stream timers (TLS 0x016E42A4 = write pointer, 0x016E42A8 = end)
// ---------------------------------------------------------------------------
extern volatile unsigned long g_hkMonitorStreamCurrentTls;   // 0x016E42A4
extern volatile unsigned long g_hkMonitorStreamEndTls;       // 0x016E42A8
extern const char hkMonitorEndListTag[];                     // 0x0143CD94

struct hkMonitorCommand { const char* m_commandAndMonitor; hkUint32 m_time0; hkUint32 m_time1; };
struct hkMonitorListCommand { const char* m_commandAndMonitor; hkUint32 m_time0; hkUint32 m_time1; const char* m_nameOfFirstSplit; };

#define HK_TIMER_SET_TIME(field) { hkUint32 ticks_; __asm { rdtsc } __asm { mov ticks_, eax } field = ticks_; }

#define HK_TIMER_COMMAND(name) do { \
	void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
	if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
		hkMonitorCommand* c_ = (hkMonitorCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
		c_->m_commandAndMonitor = name; \
		HK_TIMER_SET_TIME(c_->m_time0) \
		TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_BEGIN_LIST(name, first) do { \
	void* hkEnd_ = TlsGetValue(g_hkMonitorStreamEndTls); \
	if (TlsGetValue(g_hkMonitorStreamCurrentTls) < hkEnd_) { \
		hkMonitorListCommand* c_ = (hkMonitorListCommand*)TlsGetValue(g_hkMonitorStreamCurrentTls); \
		c_->m_commandAndMonitor = "Lt" name; \
		c_->m_nameOfFirstSplit = first; \
		HK_TIMER_SET_TIME(c_->m_time0) \
		TlsSetValue(g_hkMonitorStreamCurrentTls, c_ + 1); } } while (0)
#define HK_TIMER_SPLIT_LIST(name) HK_TIMER_COMMAND("St" name)
#define HK_TIMER_END_LIST() HK_TIMER_COMMAND(hkMonitorEndListTag)

// ---------------------------------------------------------------------------
// thread memory / hkArray / geometry
// ---------------------------------------------------------------------------
extern unsigned long g_hkThreadMemoryTlsIndex;   // 0x016E4174

class hkThreadMemory
{
public:
	void deallocateChunk(void* p, int nbytes, int memClass);   // 0x0107DB10
	static hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }
};

template <class T>
class hkArray
{
public:
	T* m_data;
	int m_size;
	int m_capacityAndFlags;
	int getSize() const { return m_size; }
	int getCapacity() const { return m_capacityAndFlags & 0x3FFFFFFF; }
};

struct hkStridedVertices
{
	const hkReal* m_vertices;   // +0
	int m_numVertices;          // +4
	int m_striding;             // +8
};

struct hkGeometry
{
	hkArray<hkVector4> m_vertices;    // +0x0
	hkArray<hkVector4> m_triangles;   // +0xc
};

struct hkGeomEdge
{
	hkUint16 m_vertex;   // +0
	hkUint16 m_twin;     // +2
	hkUint16 m_next;     // +4
	hkUint16 m_pad;      // +6
};

template <class T, int N>
class hkInplaceArray : public hkArray<T>
{
public:
	T m_storage[N];
};

class hkGeomHull
{
public:
	hkGeomHull();     // 0x0111CC90
	~hkGeomHull()
	{
		if ((m_edges.m_capacityAndFlags & 0x80000000) == 0)
			hkThreadMemory::getInstance().deallocateChunk(m_edges.m_data,
				m_edges.getCapacity() * (int)sizeof(hkGeomEdge), 0x14);
	}
	const hkVector4* m_vertices;                     // +0x00
	hkInplaceArray<hkGeomEdge, 128> m_edges;         // +0x04 (inplace storage at +0x10)
};

struct hkGeomConvexHullTolerances
{
	unsigned char m_b0;          // +0x00
	unsigned char m_b1;          // +0x01
	unsigned char m_postFilter;  // +0x02
	unsigned char m_b3;          // +0x03
	float m_values[12];          // +0x04 .. +0x30
};

class hkGeomConvexHullBuilder
{
public:
	static hkBool buildPlaneEquations(const hkGeomConvexHullTolerances& tolerances, hkGeomHull& hull,
		const hkArray<hkVector4>& usedVertices, hkArray<hkVector4>& planeEquations);   // 0x0111A060
};

extern "C" void FUN_010ede30(const hkStridedVertices& verts, hkGeomHull& hull, hkGeometry& geometryOut, int flags);  // 0x010EDE30
extern "C" void FUN_01119fa0(hkGeomHull& hull, hkGeometry& geometryOut);                                            // 0x01119FA0

class hkGeometryUtility
{
public:
	static void createConvexGeometry(const hkStridedVertices& verts, hkGeometry& geometryOut,
		hkArray<hkVector4>& planeEquationsOut, int flags);   // 0x010EDF70
};

// ---------------------------------------------------------------------------
// constraint query / solver plumbing
// ---------------------------------------------------------------------------
class hkSolverResults
{
public:
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

struct hk1dAngularLimitInfo
{
	hkVector4 m_constrainedDofW;   // +0x00
	hkReal m_min;                  // +0x10
	hkReal m_max;                  // +0x14
	hkReal m_computedAngle;        // +0x18
	hkReal m_tau;                  // +0x1c
};

extern bool g_ragdollLimitsKeycodeOk;        // 0x016E5AAC
bool hkSolverCheckKeycode(int component);    // 0x010BFBE0 (cdecl)

extern "C" void hkBeginConstraints(const hkConstraintQueryIn& in, hkConstraintQueryOut& out,
	hkSolverResults* sr, int solverResultStriding);   // 0x010AA080
extern "C" void hk1dAngularLimitBuildJacobian(const hk1dAngularLimitInfo& info, const hkConstraintQueryIn& in,
	hkConstraintQueryOut& out);                       // 0x010AB0E0

namespace hkMath
{
	float atan2fApproximation(float x, float y);      // 0x0120ADB0
}

// ---------------------------------------------------------------------------
// constraint data hierarchy
// ---------------------------------------------------------------------------
class hkBaseObject
{
public:
	virtual ~hkBaseObject();
};

class hkReferencedObject : public hkBaseObject
{
public:
	unsigned short m_memSizeAndFlags;   // +0x4
	short m_referenceCount;             // +0x6
	hkReferencedObject();
	virtual ~hkReferencedObject();
};
hkReferencedObject::hkReferencedObject() { m_referenceCount = 1; }

class hkConstraintData : public hkReferencedObject
{
public:
	unsigned int m_userData;            // +0x8
	hkConstraintData(int = 0);
	virtual void getConstraintInfo(void* info) const;
	virtual void getRuntimeInfo(hkBool, void* info) const;
	virtual hkBool isValid() const;
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);
};
hkConstraintData::hkConstraintData(int) {}

class hkRagdollLimitsData : public hkConstraintData
{
public:
	struct BasisA { hkVector4 m_planeAxis; hkVector4 m_twistAxis; };   // 0x20
	struct BasisB { hkVector4 m_planeAxis; hkVector4 m_twistAxis; };   // 0x20
	BasisA m_basisA;                 // +0x10
	BasisB m_basisB;                 // +0x30
	hkReal m_coneMinAngle;           // +0x50
	hkReal m_planeMinAngle;          // +0x54
	hkReal m_planeMaxAngle;          // +0x58
	hkReal m_twistMinAngle;          // +0x5c
	hkReal m_twistMaxAngle;          // +0x60
	hkReal m_maxFrictionTorque;      // +0x64
	hkReal m_angularLimitsTauFactor; // +0x68

	virtual hkBool isValid() const;                                                  // 0x010EE410
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);  // 0x010EE550
	void buildLimits(const hkVector4& twistAxisAinWorld, const hkVector4& twistAxisBinWorld,
		const hkVector4& planeAxisBinWorld, const hkConstraintQueryIn& in,
		hkConstraintQueryOut& out);                                              // 0x010EE1B0
};

class hkRagdollConstraintData : public hkConstraintData
{
public:
	struct BasisA { hkVector4 m_pivot; hkVector4 m_planeAxis; hkVector4 m_twistAxis; };   // 0x30
	struct BasisB { hkVector4 m_pivot; hkVector4 m_planeAxis; hkVector4 m_twistAxis; };   // 0x30
	BasisA m_basisA;                 // +0x10
	BasisB m_basisB;                 // +0x40
	hkReal m_coneMinAngle;           // +0x70
	hkReal m_planeMinAngle;          // +0x74
	hkReal m_planeMaxAngle;          // +0x78
	hkReal m_twistMinAngle;          // +0x7c
	hkReal m_twistMaxAngle;          // +0x80
	hkReal m_maxFrictionTorque;      // +0x84
	hkReal m_angularLimitsTauFactor; // +0x88

	hkRagdollConstraintData(int);                                                    // 0x010EEDD0
	virtual hkBool isValid() const;                                                  // 0x010EECB0
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);  // 0x010EEE10 (other slice)
	void buildLimits(const hkVector4& twistAxisAinWorld, const hkVector4& twistAxisBinWorld,
		const hkVector4& planeAxisBinWorld, const hkConstraintQueryIn& in,
		hkConstraintQueryOut& out);                                              // 0x010EEA50
};

// ===========================================================================
// 0x010EDF70  hkGeometryUtility::createConvexGeometry
// ===========================================================================
// @ 0x010EDF70
void hkGeometryUtility::createConvexGeometry(const hkStridedVertices& verts, hkGeometry& geometryOut,
	hkArray<hkVector4>& planeEquationsOut, int flags)
{
	HK_TIMER_BEGIN_LIST("CreateConvex", "Hull");

	hkGeomHull hull;
	FUN_010ede30(verts, hull, geometryOut, flags);
	FUN_01119fa0(hull, geometryOut);

	HK_TIMER_SPLIT_LIST("planes");

	hkGeomConvexHullTolerances tolerances;
	tolerances.m_postFilter = (flags == 2);
	tolerances.m_b0 = 1;
	tolerances.m_values[0] = 2e-5f;
	tolerances.m_values[1] = 4e-6f;
	tolerances.m_values[2] = 1e-6f;
	tolerances.m_values[3] = 1e-5f;
	tolerances.m_values[4] = 0.05f;
	tolerances.m_values[5] = 1e-6f;
	tolerances.m_values[6] = 1e-6f;
	tolerances.m_values[7] = 1e-8f;
	tolerances.m_values[8] = 1e-6f;
	tolerances.m_values[9] = 1e-4f;
	tolerances.m_values[10] = 1e-5f;
	tolerances.m_values[11] = 2e-5f;

	hkGeomConvexHullBuilder::buildPlaneEquations(tolerances, hull, geometryOut.m_vertices,
		planeEquationsOut);

	HK_TIMER_END_LIST();
}

// ===========================================================================
// 0x010EE1B0  hkRagdollLimitsData::buildLimits
// ===========================================================================
// @ 0x010EE1B0
void hkRagdollLimitsData::buildLimits(const hkVector4& twistA, const hkVector4& twistB,
	const hkVector4& planeB, const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	// ---- twist limit: axis = normalize(twistA x twistB), min = -coneMinAngle ----
	{
		const float cx = twistA.y * twistB.z - twistA.z * twistB.y;
		const float cy = twistB.x * twistA.z - twistA.x * twistB.z;
		const float cz = twistA.x * twistB.y - twistA.y * twistB.x;
		const float len2 = (cx * cx + cy * cy) + cz * cz;
		if (!(len2 < 1.1920929e-07f))
		{
			const float len = (float)sqrt((double)len2);
			const float angle = hkMath::atan2fApproximation(len, hkDot3(twistA, twistB));

			hk1dAngularLimitInfo info;
			const float inv = kOne / len;
			info.m_constrainedDofW.x = cx * inv;
			info.m_constrainedDofW.y = inv * cy;
			info.m_constrainedDofW.z = inv * cz;
			info.m_constrainedDofW.w = inv * kZero;
			info.m_min = -m_coneMinAngle;
			info.m_max = 100.0f;
			info.m_computedAngle = -angle;
			info.m_tau = m_angularLimitsTauFactor * in.m_tau;
			hk1dAngularLimitBuildJacobian(info, in, out);
		}
	}

	// ---- plane limit: axis = normalize(twistA x planeB) ----
	{
		const float cx = twistA.y * planeB.z - twistA.z * planeB.y;
		const float cy = twistA.z * planeB.x - planeB.z * twistA.x;
		const float cz = twistA.x * planeB.y - twistA.y * planeB.x;
		const float len2 = (cz * cz + cy * cy) + cx * cx;
		if (len2 < 1.1920929e-07f)
			return;

		const float len = (float)sqrt((double)len2);
		const float angle = hkMath::atan2fApproximation(twistA.y * planeB.y + (twistA.x * planeB.x + twistA.z * planeB.z), len);

		hk1dAngularLimitInfo info;
		const float inv = kOne / len;
		info.m_constrainedDofW.x = cx * inv;
		info.m_constrainedDofW.y = cy * inv;
		info.m_constrainedDofW.z = cz * inv;
		info.m_constrainedDofW.w = inv * kZero;
		info.m_min = m_planeMinAngle;
		info.m_max = m_planeMaxAngle;
		info.m_computedAngle = angle;
		info.m_tau = m_angularLimitsTauFactor * in.m_tau;
		hk1dAngularLimitBuildJacobian(info, in, out);
	}
}

// ===========================================================================
// 0x010EE410  hkRagdollLimitsData::isValid
// ===========================================================================
// @ 0x010EE410
hkBool hkRagdollLimitsData::isValid() const
{
	hkBool result;
	if (!(hkAbsF(hkLen3sq(m_basisA.m_planeAxis) - 1.0f) < 1e-05f)) { result.m_bool = 0; return result; }
	if (!(hkAbsF(hkLen3sq(m_basisB.m_planeAxis) - 1.0f) < 1e-05f)) { result.m_bool = 0; return result; }
	if (!(hkAbsF(hkLen3sq(m_basisA.m_twistAxis) - 1.0f) < 1e-05f)) { result.m_bool = 0; return result; }
	if (!(hkAbsF(hkLen3sq(m_basisB.m_twistAxis) - 1.0f) < 1e-05f)) { result.m_bool = 0; return result; }
	if (hkAbsF(m_coneMinAngle) > 1.0f) { result.m_bool = 0; return result; }
	if (m_planeMinAngle > m_planeMaxAngle) { result.m_bool = 0; return result; }
	if (m_twistMinAngle > m_twistMaxAngle) { result.m_bool = 0; return result; }
	result.m_bool = 1;
	return result;
}

// ===========================================================================
// 0x010EE550  hkRagdollLimitsData::buildJacobian
// ===========================================================================
// @ 0x010EE550
void hkRagdollLimitsData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	if (!g_ragdollLimitsKeycodeOk)
	{
		g_ragdollLimitsKeycodeOk = hkSolverCheckKeycode(1);
		if (!g_ragdollLimitsKeycodeOk)
			return;
	}

	const hkTransform& tA = *in.m_transformA;
	hkVector4 planeAxisAinWorld;
	setRotatedDir(planeAxisAinWorld, tA.m_rotation, m_basisA.m_planeAxis);
	hkVector4 twistAxisAinWorld;
	setRotatedDir(twistAxisAinWorld, tA.m_rotation, m_basisA.m_twistAxis);

	const hkTransform& tB = *in.m_transformB;
	hkVector4 planeAxisBinWorld;
	setRotatedDir(planeAxisBinWorld, tB.m_rotation, m_basisB.m_planeAxis);
	hkVector4 twistAxisBinWorld;
	setRotatedDir(twistAxisBinWorld, tB.m_rotation, m_basisB.m_twistAxis);

	hkBeginConstraints(in, out, (hkSolverResults*)in.m_constraintRuntime, 8);

	// twist_axis_ws = normalize(twistB + twistA); tauMax = 0.5*|sum|
	hkVector4 twist_axis_ws;
	hkReal tauMax;
	{
		const float sx = twistAxisBinWorld.x + twistAxisAinWorld.x;
		const float sy = twistAxisBinWorld.y + twistAxisAinWorld.y;
		const float sz = twistAxisBinWorld.z + twistAxisAinWorld.z;
		const float len = (float)sqrt((double)((sx * sx + sz * sz) + sy * sy));
		if (!(len > 1e-16f))
		{
			tauMax = 0.0f;
			twist_axis_ws = twistAxisBinWorld;
		}
		else
		{
			tauMax = len * 0.5f;
			const float inv = kOne / len;
			twist_axis_ws.x = inv * sx;
			twist_axis_ws.y = sy * inv;
			twist_axis_ws.z = sz * inv;
			twist_axis_ws.w = inv * kZero;
		}
	}

	// c1 = planeB x twist_axis_ws, c2 = c1 x twist_axis_ws
	hkVector4 c2;
	const float c1x = planeAxisBinWorld.z * twist_axis_ws.y - planeAxisBinWorld.y * twist_axis_ws.z;
	const float c1y = planeAxisBinWorld.x * twist_axis_ws.z - planeAxisBinWorld.z * twist_axis_ws.x;
	const float c1z = planeAxisBinWorld.y * twist_axis_ws.x - planeAxisBinWorld.x * twist_axis_ws.y;
	c2.x = c1y * twist_axis_ws.z - c1z * twist_axis_ws.y;
	c2.y = c1z * twist_axis_ws.x - c1x * twist_axis_ws.z;
	c2.z = c1x * twist_axis_ws.y - c1y * twist_axis_ws.x;

	hk1dAngularLimitInfo info;
	const float d1 = c1x * planeAxisAinWorld.x + (c1y * planeAxisAinWorld.y + c1z * planeAxisAinWorld.z);
	const float d2 = c2.x * planeAxisAinWorld.x + (c2.y * planeAxisAinWorld.y + c2.z * planeAxisAinWorld.z);
	info.m_computedAngle = hkMath::atan2fApproximation(d1, d2);
	info.m_constrainedDofW = twist_axis_ws;
	info.m_min = m_twistMinAngle;
	info.m_max = m_twistMaxAngle;
	info.m_tau = (sqrt(tauMax) * in.m_tau) * tauMax;
	hk1dAngularLimitBuildJacobian(info, in, out);

	buildLimits(twistAxisAinWorld, twistAxisBinWorld, planeAxisBinWorld, in, out);
}

// ===========================================================================
// 0x010EEA50  hkRagdollConstraintData::buildLimits
// ===========================================================================
// @ 0x010EEA50
void hkRagdollConstraintData::buildLimits(const hkVector4& twistA, const hkVector4& twistB,
	const hkVector4& planeB, const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	// ---- twist limit: axis = normalize(twistA x twistB), min = -coneMinAngle ----
	{
		const float cx = twistA.y * twistB.z - twistA.z * twistB.y;
		const float cy = twistB.x * twistA.z - twistA.x * twistB.z;
		const float cz = twistA.x * twistB.y - twistA.y * twistB.x;
		const float len2 = (cx * cx + cy * cy) + cz * cz;
		if (!(len2 < 1.1920929e-07f))
		{
			const float len = (float)sqrt((double)len2);
			const float angle = hkMath::atan2fApproximation(len, hkDot3(twistA, twistB));

			hk1dAngularLimitInfo info;
			const float inv = kOne / len;
			info.m_constrainedDofW.x = cx * inv;
			info.m_constrainedDofW.y = inv * cy;
			info.m_constrainedDofW.z = inv * cz;
			info.m_constrainedDofW.w = inv * kZero;
			info.m_min = -m_coneMinAngle;
			info.m_max = 100.0f;
			info.m_computedAngle = -angle;
			info.m_tau = m_angularLimitsTauFactor * in.m_tau;
			hk1dAngularLimitBuildJacobian(info, in, out);
		}
	}

	// ---- plane limit: axis = normalize(twistA x planeB) ----
	{
		const float cx = twistA.y * planeB.z - twistA.z * planeB.y;
		const float cy = twistA.z * planeB.x - planeB.z * twistA.x;
		const float cz = twistA.x * planeB.y - twistA.y * planeB.x;
		const float len2 = (cz * cz + cy * cy) + cx * cx;
		if (len2 < 1.1920929e-07f)
			return;

		const float len = (float)sqrt((double)len2);
		const float angle = hkMath::atan2fApproximation(twistA.y * planeB.y + (twistA.x * planeB.x + twistA.z * planeB.z), len);

		hk1dAngularLimitInfo info;
		const float inv = kOne / len;
		info.m_constrainedDofW.x = cx * inv;
		info.m_constrainedDofW.y = cy * inv;
		info.m_constrainedDofW.z = cz * inv;
		info.m_constrainedDofW.w = inv * kZero;
		info.m_min = m_planeMinAngle;
		info.m_max = m_planeMaxAngle;
		info.m_computedAngle = angle;
		info.m_tau = m_angularLimitsTauFactor * in.m_tau;
		hk1dAngularLimitBuildJacobian(info, in, out);
	}
}

// ===========================================================================
// 0x010EECB0  hkRagdollConstraintData::isValid
// ===========================================================================
// @ 0x010EECB0
hkBool hkRagdollConstraintData::isValid() const
{
	hkBool result;
	if (!(hkAbsF(hkLen3sq(m_basisA.m_planeAxis) - 1.0f) < 1e-05f)) { result.m_bool = 0; return result; }
	if (!(hkAbsF(hkLen3sq(m_basisB.m_planeAxis) - 1.0f) < 1e-05f)) { result.m_bool = 0; return result; }
	if (!(hkAbsF(hkLen3sq(m_basisA.m_twistAxis) - 1.0f) < 1e-05f)) { result.m_bool = 0; return result; }
	if (!(hkAbsF(hkLen3sq(m_basisB.m_twistAxis) - 1.0f) < 1e-05f)) { result.m_bool = 0; return result; }
	if (hkAbsF(m_coneMinAngle) > 1.0f) { result.m_bool = 0; return result; }
	if (m_planeMinAngle > m_planeMaxAngle) { result.m_bool = 0; return result; }
	if (m_twistMinAngle > m_twistMaxAngle) { result.m_bool = 0; return result; }
	result.m_bool = 1;
	return result;
}

// ===========================================================================
// 0x010EEDD0  hkRagdollConstraintData::hkRagdollConstraintData(int)
// ===========================================================================
// @ 0x010EEDD0
hkRagdollConstraintData::hkRagdollConstraintData(int) {}
