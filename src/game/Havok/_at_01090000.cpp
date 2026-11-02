// src/game/Havok/_at_01090000.cpp -- migrated from slice(s) s01090a70, s0109f870, s0109e8e0, s0109c3b0, s01098e50, s01098200, s010960e0, s01095320, s01094510, s01092e10, s01091a60 by tools/migrate/rewrite.py
// Object file: Havok/_at_01090000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <new>
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern int vtbl_014a1aa8;
extern int vtbl_013ef094;
extern "C" double __cdecl fabs(double);
extern const float hk_identityBasis[12];                       // 0x015b9b20
extern const float hk_zero;                                    // 0x01485378
#pragma intrinsic(fabs)

// ---- items of slice s01091a60 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  byte;
typedef unsigned short ushort;
typedef unsigned int   uint;
class hkBool_s0109_1a60 {
public:
    char m_bool;
    hkBool_s0109_1a60(bool b) : m_bool((char)b) {}
};
class hkConstraintQueryIn;
class hkConstraintQueryOut;
extern void hkBeginConstraints(const hkConstraintQueryIn &in,
                               hkConstraintQueryOut &out, int n, int size);   // FUN_010aa080
class hkPulleyConstraintData {
public:
    hkBool_s0109_1a60 isValid() const;
    void buildJacobian(const hkConstraintQueryIn &in,
                       hkConstraintQueryOut &out) const;
};
struct __declspec(align(16)) PulleyJacobianData {
    float posA[4];      // +0x00  transformed pivot A (w = 0)
    float posB[4];      // +0x10  transformed pivot B (w = 0)
    int   p[4];         // +0x20  this+0x40 .. this+0x4c
    int   q[4];         // +0x30  this+0x50 .. this+0x5c
    float f0;           // +0x40  this+0x0c
    float f1;           // +0x44  this+0x10
};
extern void hkPulleyConstraintBuildJacobian(const PulleyJacobianData *d,
                                            const hkConstraintQueryIn &in,
                                            hkConstraintQueryOut &out);
struct hkRefCountedObject {
    virtual void __deleteThis(int flag) = 0;   // vtable slot 0
    ushort m_memSizeAndFlags;                  // +4
    ushort m_referenceCount;                   // +6
};
class hkMemory {
public:
    virtual void v0() = 0;
    virtual void v1() = 0;
    virtual void v2() = 0;
    virtual void v3() = 0;
    virtual void v4() = 0;
    virtual void deallocate(void *p, uint size, int align) = 0;   // +0x14
};
extern hkMemory *g_hkMemory;                   // 0x016e4178
extern int vtbl_014a1aa8;
extern int vtbl_013ef094;
struct hkConstraintAtomBase {
    void *scalarDeletingDtor(byte flags);
};
class hkPrismaticConstraintData {
public:
    hkBool_s0109_1a60 isValid() const;
};
extern "C" double __cdecl fabs(double);
inline float Fabs(float x) { return (float)fabs(x); }
class hkRelativeOrientationConstraintData {
public:
    virtual void buildJacobian(const hkConstraintQueryIn &in,
                               hkConstraintQueryOut &out) const;
};
struct hkQuaternion_s0109_1a60 {
    float x, y, z, w;
    void set(const void *rotation);                            // FUN_01082490
    void setMul(const hkQuaternion_s0109_1a60 &a, const hkQuaternion_s0109_1a60 &b); // FUN_01082210
};
extern const float hk_identityBasis[12];                       // 0x015b9b20
extern const float hk_zero;                                    // 0x01485378
extern void hk1dAngularBilateralJacobian(const float *axis,
                                         const hkConstraintQueryIn &in,
                                         hkConstraintQueryOut &out);   // FUN_010aa1e0
// ---- items of slice s01091a60 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern void hkBeginConstraints(const hkConstraintQueryIn &in,
                               hkConstraintQueryOut &out, int n, int size);   // FUN_010aa080
extern void hkPulleyConstraintBuildJacobian(const PulleyJacobianData *d,
                                            const hkConstraintQueryIn &in,
                                            hkConstraintQueryOut &out);
extern hkMemory *g_hkMemory;                   // 0x016e4178
extern void hk1dAngularBilateralJacobian(const float *axis,
                                         const hkConstraintQueryIn &in,
                                         hkConstraintQueryOut &out);   // FUN_010aa1e0

// ---- items of slice s01092e10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kZero;   // 0x01485378
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern unsigned long g_threadMemoryTls;   // 0x016e4174: hkThreadMemory TLS slot
typedef float hkReal;
class __declspec(align(16)) hkVector4_s0109_2e10
{
public:
	float x, y, z, w;
	__forceinline void addTranslation(const hkVector4_s0109_2e10& t) { x = x + t.x; y = y + t.y; z = z + t.z; w = t.w; }
};
class hkMatrix3_s0109_2e10
{
public:
	hkVector4_s0109_2e10 m_col[3];
};
class hkRotation_s0109_2e10 : public hkMatrix3_s0109_2e10 {};
class hkTransform_s0109_2e10
{
public:
	hkRotation_s0109_2e10 m_rotation;     // +0x00
	hkVector4_s0109_2e10 m_translation;   // +0x30
};
class hkSolverResults
{ public:
	hkReal m_impulseApplied;        // +0
	hkReal m_internalSolverData;    // +4
	hkSolverResults() : m_impulseApplied(0), m_internalSolverData(0) {}
};
class hkConstraintQueryIn_s0109_2e10
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
	hkTransform_s0109_2e10* m_transformA;           // +0x30
	hkTransform_s0109_2e10* m_transformB;           // +0x34
	float m_tau;                         // +0x38
	float m_damping;                     // +0x3c
	void* m_constraintInstance;          // +0x40
	void* m_constraintRuntime;           // +0x44
};
class hkConstraintQueryOut_s0109_2e10
{
public:
	void* m_jacobians;          // +0
	void* m_jacobianSchemas;    // +4
};
struct hkConstraintMotorInput
{
	hkReal m_virtualMass;                       // +0x00 (written by the motor BeginJacobian)
	const hkConstraintQueryIn_s0109_2e10* m_stepInfo;      // +0x04
	hkSolverResults m_lastResults;              // +0x08
	hkReal m_deltaTarget;                       // +0x10
	hkReal m_positionError;                     // +0x14
};
struct hkConstraintMotorOutput
{
	hkReal m_targetPosition, m_targetVelocity, m_minForce, m_maxForce, m_tau, m_damping;
};
class hkConstraintMotor
{
public:
	virtual ~hkConstraintMotor();          // +0 deleting-destructor slot
	virtual void vslot1();                 // +4
	virtual void motor(const hkConstraintMotorInput& input, hkConstraintMotorOutput& output) const = 0;   // +8
	unsigned short m_memSizeAndFlags;      // +0x04
	unsigned short m_referenceCount;       // +0x06
	void removeReference()
	{
		if (m_memSizeAndFlags != 0 && --m_referenceCount == 0)
			delete this;
	}
};
class hkBaseObject_s0109_2e10
{
};
class hkReferencedObject_s0109_2e10 : public hkBaseObject_s0109_2e10
{
public:
	unsigned short m_memSizeAndFlags;   // +0x04
	unsigned short m_referenceCount;    // +0x06
	virtual ~hkReferencedObject_s0109_2e10() {}
};
class hkConstraintData_s0109_2e10 : public hkReferencedObject_s0109_2e10
{
public:
	unsigned int m_userData;            // +0x08
	struct RuntimeInfo
	{
		int m_sizeOfExternalRuntime;    // +0x00
		int m_numSolverResults;         // +0x04
	};
};
class __declspec(align(16)) hkQuaternion_s0109_2e10
{
public:
	float x, y, z, w;
};
class hkBool_s0109_2e10
{
public:
	hkBool_s0109_2e10() {}
	hkBool_s0109_2e10(bool b) : m_bool(b ? 1 : 0) {}
	unsigned char m_bool;
};
class hkThreadMemory
{
public:
	void deallocateChunk(void* data, int numBytes, int alignment);   // 0x0107db10
};
template <class T> class hkArray
{
public:
	enum { CAPACITY_MASK = 0x3fffffff, DONT_DEALLOCATE_FLAG = (int)0x80000000 };
	T* m_data;              // +0x00
	int m_size;             // +0x04
	int m_capacityAndFlags; // +0x08
	int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
	~hkArray()
	{
		if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
		{
			hkThreadMemory* mem = (hkThreadMemory*)TlsGetValue(g_threadMemoryTls);
			mem->deallocateChunk(m_data, getCapacity() * sizeof(T), 0x14);
		}
	}
};
struct hkConstraintInfo
{
	int m_maxSizeOfJacobians;   // +0x00
	int m_sizeOfJacobians;      // +0x04
	int m_sizeOfSchemas;        // +0x08
	int m_numSolverResults;     // +0x0c
};
class hkPoweredChainDataConstraintInfo
{
public:
	hkVector4_s0109_2e10 m_pivotInA;            // +0x00
	hkVector4_s0109_2e10 m_pivotInB;            // +0x10
	hkQuaternion_s0109_2e10 m_aTc;              // +0x20
	hkQuaternion_s0109_2e10 m_bTc;              // +0x30
	hkConstraintMotor* m_motors[3];  // +0x40
	bool m_switchBodies;             // +0x4c
};
class hkConstraintChainData : public hkConstraintData_s0109_2e10
{
};
class hkPoweredChainData : public hkConstraintChainData
{
public:
	hkArray<hkPoweredChainDataConstraintInfo> m_infos;   // +0x0c
	hkReal m_tau;                                        // +0x18
	hkReal m_damping;                                    // +0x1c
	hkReal m_cfmLinAdd;                                  // +0x20
	hkReal m_cfmLinMul;                                  // +0x24
	hkReal m_cfmAngAdd;                                  // +0x28
	hkReal m_cfmAngMul;                                  // +0x2c
	hkReal m_maxErrorDistance;                           // +0x30

	virtual void getConstraintInfo(hkConstraintInfo& info) const;
	virtual void getRuntimeInfo(hkBool_s0109_2e10 wantRuntime, hkConstraintData_s0109_2e10::RuntimeInfo& info) const;
	virtual void buildJacobian(const hkConstraintQueryIn_s0109_2e10& in, hkConstraintQueryOut_s0109_2e10& out);
	~hkPoweredChainData();
};
namespace SP
{
	class cSPToolStrategy
	{
	public:
		int AdjustCost(int cost);
	};
}
// ---- items of slice s01092e10 end

// ---- items of slice s01094510 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gAllocator;              // 0x016e4174
class __declspec(align(16)) hkVector4_s0109_4510
{
public:
	float x, y, z, w;
	float& operator[](int i) { return (&x)[i]; }
	const float& operator[](int i) const { return (&x)[i]; }

	void setTransformedPos(const class hkTransform_s0109_4510& t, const hkVector4_s0109_4510& v);          // 0x01081360
	void setTransformedInversePos(const class hkTransform_s0109_4510& t, const hkVector4_s0109_4510& v);   // 0x010813d0
	void setRotatedDir(const struct hkRotation_s0109_4510& r, const hkVector4_s0109_4510& v);               // 0x010814a0
};
class hkMatrix3_s0109_4510
{
public:
	hkVector4_s0109_4510 m_col[3];
};
class hkRotation_s0109_4510 : public hkMatrix3_s0109_4510 {};
class hkTransform_s0109_4510
{ public:
	hkRotation_s0109_4510 m_rotation;     // +0x00
	hkVector4_s0109_4510 m_translation;   // +0x30
	void setMul(const hkTransform_s0109_4510& a, const hkTransform_s0109_4510& b);   // 0x01080ef0
};
#define hkSqrt(x) ((float)sqrt((double)(x)))
struct cArrayRef
{
	void** m_data;                 // +0x00
	int    m_size;                 // +0x04
	int    m_capacityAndFlags;     // +0x08
};
struct cRefObj
{
	virtual void Release(int flags);   // +0x00
	unsigned short m_memSize;          // +0x04
	short m_refCount;                  // +0x06
};
struct cCurveElem
{
	void Release();                    // 0x0109ae60
};
class cHeap
{
public:
	void Dealloc(void* p, int nBytes, int tag);   // 0x0107db10
};
struct cDeallocator
{
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void Dealloc(void* p, int nBytes, int tag);   // +0x14
};
extern cDeallocator* gDeallocator;    // 0x016e4178
typedef void* (__stdcall* cGetHeapFn)(void*);
extern cGetHeapFn gGetHeap;           // 0x013cc2bc (function-pointer variable)
class cCurveContainer
{
public:
	void* mpVtbl;              // +0x00
	unsigned short m_memSize;  // +0x04
	unsigned short m_refCount; // +0x06
	cArrayRef m_arrays[4];     // +0x08 / +0x14 / +0x20 / +0x2c

	void Destroy();            // 0x01094bc0
};
class cStream : public cRefObj
{
public:
	virtual void v04();
	virtual void* v08(void* arg);         // +0x08
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c(void* a, void* b);   // +0x1c
	virtual void v20(void* s);            // +0x20
};
struct cCmdState
{
	unsigned int m00;
	unsigned int m04;
	unsigned int m08;
	unsigned int m0c;
};
struct cBlob48
{
	float m00, m04, m08, m0c, m10, m14;
	float m18;
	float m1c, m20, m24, m28, m2c, m30, m34, m38, m3c, m40, m44;
};
class cStreamProxy
{
public:
	void* mpVtbl;              // +0x00
	unsigned short m_memSize;  // +0x04
	unsigned short m_refCount; // +0x06
	unsigned int m08;          // +0x08
	cStream* mpStream;         // +0x0c
	float m_scale;             // +0x10

	void To20(cCmdState* s);              // 0x01094d50
	void To1c(cBlob48* src, void* arg);   // 0x01094d90
	void* To08(void* arg);                // 0x01094dd0
	void* Destroy(int flags);             // 0x01094e10
};
class cKeyFrameCurve
{
public:
	virtual void v00();                                   // +0x00
	virtual void v04();                                   // +0x04
	virtual void v08();                                   // +0x08
	virtual hkReal NearestPoint(hkReal t, const hkVector4_s0109_4510& pos, hkVector4_s0109_4510& out);  // +0x0c

	unsigned short m_memSize;  // +0x04
	unsigned short m_refCount; // +0x06
	unsigned int m08;          // +0x08
	unsigned char m_closed;    // +0x0c
	char m0d[3];               // +0x0d
	float m10;                 // +0x10
	char m14[0x0c];            // +0x14
	hkVector4_s0109_4510* m_keys;         // +0x20
	int m_keyCount;            // +0x24

	char* IsClosed(char* out);                                            // 0x01094e60
	void GetPoint(hkReal t, hkVector4_s0109_4510& out);                              // 0x01094e80
};
extern "C" int CurveIndex(hkReal t);   // 0x0120ad30
// ---- items of slice s01094510 end

// ---- items of slice s01095320 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_hkMemoryInstance;                   // 0x016e4178
extern const float DAT_01485720;                   // 1.0f
extern const float DAT_0147bc20;                   // comparison constant
extern float DAT_015b9b30;                          // binormal basis x
extern float DAT_015b9b34;                          // binormal basis y
extern float DAT_015b9b38;                          // binormal basis z
extern void* g_hkKeyframedRigidMotionVtbl;         // 0x014a1c08
extern const float DAT_01471064;      // 0.5f
extern const float DAT_013ec4b4;      // 0.9f
extern const float DAT_0149e068;      // 0.4052847f
extern const float DAT_0149e064;      // 0.822948f
extern const float DAT_0149e060;      // 0.130529f
extern const float DAT_0149e05c;      // 0.044408f
extern const float DAT_014a1c00;      // 3.1415927f
class hkVector4_s0109_5320 { public:
    float x, y, z, w;
};
int   hkFloatToInt(float f);                       // 0x0120ad30 ?hkFloatToInt@hkMath@@YAHM@Z
void  hkMemCpy(void* dst, const void* src, uint n);// 0x0107f440 hkString::memCpy
extern const hkVector4_s0109_5320 DAT_016e42d0;
extern const hkVector4_s0109_5320 DAT_015b9b50;
void  hkRigidMotionCtor(void* self, const hkVector4_s0109_5320* pos, const void* rot); // 0x01088500
inline float SqrtF(float f) { return sqrtf(f); }
struct hkLinearParametricCurve {
    char pad0[8];
    float m08;                  // +0x08
    char pad1[0x10 - 0x0c];
    void* mp10;                 // +0x10
    char pad2[0x20 - 0x14];
    hkVector4_s0109_5320* mpPoints;        // +0x20
    int   mPointCount;          // +0x24
    char pad4[0x2c - 0x28];
    float* mpLengths;           // +0x2c
    char pad5[0x34 - 0x30];
    int   m34;                  // +0x34
    char pad6[0x3c - 0x38];
    int   m38;                  // +0x38
    int   m3c;                  // +0x3c

    void getTangent(float t, hkVector4_s0109_5320& out);          // 0x01095320
    float getEnd();                                    // 0x01095740
    float getLengthFromStart(float t);                  // 0x01095750
    void getBinormal(float t, hkVector4_s0109_5320& out);          // 0x010957d0
    void getPointsToDraw(void* out);                    // 0x01095960
    ~hkLinearParametricCurve();                         // 0x01095af0
};
struct hkKeyframedRigidMotion {
    char pad0[0x60];
    hkVector4_s0109_5320 v60;              // +0x60
    char pad1[0xc0 - 0x70];
    unsigned short mC0;         // +0xc0
    unsigned short mC2;         // +0xc2
    char pad2[0xd0 - 0xc4];
    hkVector4_s0109_5320 vD0;              // +0xd0
    hkVector4_s0109_5320 vE0;              // +0xe0
    char pad4[0xf0 - 0xf0 + 4];
    void* mpF0;                 // +0xf0

    hkKeyframedRigidMotion(const hkVector4_s0109_5320& pos, const void* rot);  // 0x01095b60
    void* applyForcesAndBuildAccumulator(const void* step, void* acc); // 0x01095be0
    void* clone();                                                   // 0x01095ca0
    const void* applyAccumulator(const void* step, const void* acc);  // 0x01095d80
};
void hkQuatSetMul(void* out, const void* a, const void* b);  // 0x01082210 ?setMul@hkQuaternion@@QAEXABV1@0@Z
void hkQuatNormalize(void* q);                                // 0x010821a0 ?normalize@hkQuaternion@@QAEXXZ
void hkRotationSet(void* rot, const void* q);                 // 0x010824a0 ?set@hkRotation@@QAEXABVhkQuaternion@@@Z
// ---- items of slice s01095320 end

// ---- items of slice s010960e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int16_t hkInt16;
typedef uint16_t hkUint16;
typedef uint32_t hkUint32;
class hkBool_s0109_60e0
{
public:
	hkBool_s0109_60e0() {}
	char m_bool;
};
class __declspec(align(16)) hkVector4_s0109_60e0
{
public:
	float x, y, z, w;
	__forceinline void addTranslation(const hkVector4_s0109_60e0& t) { x = x + t.x; y = y + t.y; z = z + t.z; w = t.w; }
};
class hkMatrix3_s0109_60e0 { public: hkVector4_s0109_60e0 m_col0, m_col1, m_col2; };   // 0x30 bytes
class hkQuaternion_s0109_60e0
{
public:
	float x, y, z, w;
	void setMul(const hkQuaternion_s0109_60e0& a, const hkQuaternion_s0109_60e0& b);   // 0x01082210: this = a * b
	void normalize();                                            // 0x010821A0
};
class hkRotation_s0109_60e0 : public hkMatrix3_s0109_60e0
{
public:
	void set(const hkQuaternion_s0109_60e0& q);                             // 0x010824A0
};
class hkTransform_s0109_60e0
{
public:
	hkRotation_s0109_60e0 m_rotation;     // +0x00
	hkVector4_s0109_60e0 m_translation;   // +0x30
};
class hkStepInfo_s0109_60e0
{ public:
	float m_startTime;         // +0x00
	float m_endTime;           // +0x04
	float m_deltaTime;         // +0x08
	float m_invDeltaTime;      // +0x0c
};
__forceinline void setRotatedDir(hkVector4_s0109_60e0& d, const hkRotation_s0109_60e0& r, const hkVector4_s0109_60e0& v)
{
	const float vx = v.x, vy = v.y, vz = v.z;
	d.x = (vz * r.m_col2.x + vy * r.m_col1.x) + vx * r.m_col0.x;
	d.y = (vz * r.m_col2.y + vy * r.m_col1.y) + vx * r.m_col0.y;
	d.z = (vz * r.m_col2.z + vy * r.m_col1.z) + vx * r.m_col0.z;
	d.w = 0.0f;
}
class hkSweptTransform                          // 0x50 bytes
{ public:
	hkVector4_s0109_60e0 m_centerOfMass0;                  // +0x00
	hkVector4_s0109_60e0 m_centerOfMass1;                  // +0x10
	hkQuaternion_s0109_60e0 m_rotation0;                   // +0x20
	hkQuaternion_s0109_60e0 m_rotation1;                   // +0x30
	hkVector4_s0109_60e0 m_centerOfMassLocal;              // +0x40
};
class hkMotionState                             // 0xb0 bytes
{ public:
	hkTransform_s0109_60e0 m_transform;                    // +0x00
	hkSweptTransform m_sweptTransform;          // +0x40
	hkVector4_s0109_60e0 m_deltaAngle;                     // +0x90
	float m_objectRadius;                       // +0xa0
	float m_maxLinearVelocity;                  // +0xa4
	float m_maxAngularVelocity;                 // +0xa8
	hkUint16 m_deactivationClass;               // +0xac
	hkUint16 m_deactivationCounter;             // +0xae
};
class hkReferencedObject_s0109_60e0
{
public:
	virtual ~hkReferencedObject_s0109_60e0();
	hkInt16 m_memSizeAndFlags;                  // +0x04
	hkInt16 m_referenceCount;                   // +0x06
};
class hkVelocityAccumulator;
class hkMotion_s0109_60e0 : public hkReferencedObject_s0109_60e0
{
public:
	virtual int getType() const;                                                              // 2
	virtual void step(const hkStepInfo_s0109_60e0& stepInfo);                                            // 3
	virtual void applyForcesAndStep(const hkStepInfo_s0109_60e0& stepInfo, const hkVector4_s0109_60e0& delta);      // 4
	virtual void* applyForcesAndBuildAccumulator(const hkStepInfo_s0109_60e0& stepInfo, hkVelocityAccumulator* acc);   // 5
	virtual void motionSlot6();                                                               // 6
	virtual void motionSlot7();                                                               // 7
	virtual hkMotion_s0109_60e0* clone() const;                                                          // 8
	virtual void setMass(float m);                                                            // 9
	virtual void setMassInv(float mInv);                                                      // 10
	virtual void getInertiaLocal(hkMatrix3_s0109_60e0& out) const;                                       // 11
	virtual void getInertiaWorld(hkMatrix3_s0109_60e0& out) const;                                       // 12
	virtual void setInertiaLocal(const hkMatrix3_s0109_60e0& inertia);                                   // 13
	virtual void setInertiaInvLocal(const hkMatrix3_s0109_60e0& inertia);                                // 14
	virtual void getInertiaInvLocal(hkMatrix3_s0109_60e0& out) const;                                    // 15
	virtual void getInertiaInvWorld(hkMatrix3_s0109_60e0& out) const;                                    // 16
	virtual void setCenterOfMassInLocal(const hkVector4_s0109_60e0& com);                                // 17
	virtual void setPosition(const hkVector4_s0109_60e0& position);                                      // 18
	virtual void setRotation(const hkQuaternion_s0109_60e0& rotation);                                   // 19
	virtual void setPositionAndRotation(const hkVector4_s0109_60e0& position, const hkQuaternion_s0109_60e0& rotation);   // 20
	virtual void setTransform(const hkTransform_s0109_60e0& transform);                                   // 21
	virtual void setLinearVelocity(const hkVector4_s0109_60e0& v);                                       // 22
	virtual void setAngularVelocity(const hkVector4_s0109_60e0& v);                                      // 23
	virtual void applyLinearImpulse(const hkVector4_s0109_60e0& impulse);                                // 24
	virtual void applyPointImpulse(const hkVector4_s0109_60e0& impulse, const hkVector4_s0109_60e0& point);          // 25
	virtual void applyAngularImpulse(const hkVector4_s0109_60e0& impulse);                               // 26
	virtual void motionSlot27();                                                              // 27
	virtual void motionSlot28();                                                              // 28
	virtual void motionSlot29();                                                              // 29
	virtual void getMotionStateAndVelocities(hkMotion_s0109_60e0* out);                                   // 30
	int m_solverData;                                                                          // +0x08
};
class hkRigidMotion : public hkMotion_s0109_60e0
{
public:
	hkRigidMotion(const hkVector4_s0109_60e0& position, const hkQuaternion_s0109_60e0& rotation);                   // 0x01088500
	hkMotionState m_motionState;      // +0x10
	float m_massInv;                  // +0xc0
	float m_particleMinInertiaDiagInv;// +0xc4
	float m_linearDamping;            // +0xc8
	float m_angularDamping;           // +0xcc
	hkVector4_s0109_60e0 m_linearVelocity;       // +0xd0
	hkVector4_s0109_60e0 m_angularVelocity;      // +0xe0
};
class hkKeyframedRigidMotion_s0109_60e0 : public hkRigidMotion             // vtable 0x014A1C08, size 0x100
{
public:
	hkKeyframedRigidMotion_s0109_60e0(const hkVector4_s0109_60e0& position, const hkQuaternion_s0109_60e0& rotation);          // 0x01095B60
	virtual void applyForcesAndStep(const hkStepInfo_s0109_60e0& stepInfo, const hkVector4_s0109_60e0& delta);      // 0x010960E0
	hkMotion_s0109_60e0* m_savedMotion;                                  // +0xf0
	hkUint32 m_savedQualityTypeAndPad[3];                     // +0xf4..0xff
};
class hkFixedRigidMotion : public hkKeyframedRigidMotion_s0109_60e0        // vtable 0x014A1D08
{
public:
	hkFixedRigidMotion(const hkVector4_s0109_60e0& position, const hkQuaternion_s0109_60e0& rotation);              // 0x01097110
};
class hkConstraintQueryIn_s0109_60e0
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
	hkTransform_s0109_60e0* m_transformA;           // +0x30
	hkTransform_s0109_60e0* m_transformB;           // +0x34
	float m_tau;                         // +0x38
	float m_damping;                     // +0x3c
	void* m_constraintInstance;          // +0x40
	void* m_constraintRuntime;           // +0x44
};
class hkConstraintQueryOut_s0109_60e0
{
public:
	void* m_jacobians;          // +0
	void* m_jacobianSchemas;    // +4
};
class hkConstraintData_s0109_60e0
{
public:
	virtual ~hkConstraintData_s0109_60e0();
	struct RuntimeInfo
	{
		int m_sizeOfExternalRuntime;   // +0x00
		int m_numSolverResults;        // +0x04
	};
	int m_memSizeAndFlags_userData[2]; // +0x04
};
struct hkHingeLimitsBasisA
{
	hkVector4_s0109_60e0 m_axle;               // +0x00
	hkVector4_s0109_60e0 m_perpToAxle1;        // +0x10
	hkVector4_s0109_60e0 m_perpToAxle2;        // +0x20
};
struct hkHingeLimitsBasisB
{
	hkVector4_s0109_60e0 m_axle;               // +0x00
	hkVector4_s0109_60e0 m_perp2FreeAxis;      // +0x10
};
class hkHingeLimitsData : public hkConstraintData_s0109_60e0        // 0x70 bytes
{
public:
	hkReal m_minAngle;                  // +0x0c
	hkReal m_maxAngle;                  // +0x10
	hkReal m_maxFrictionTorque;         // +0x14
	hkReal m_angularLimitsTauFactor;    // +0x18
	hkHingeLimitsBasisA m_basisA;       // +0x20
	hkHingeLimitsBasisB m_basisB;       // +0x50

	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual hkBool_s0109_60e0 isValid() const;                                                  // 0x010964B0
	virtual void buildJacobian(const hkConstraintQueryIn_s0109_60e0& in, hkConstraintQueryOut_s0109_60e0& out);   // 0x01096640
};
struct hkHingeBasisA
{
	hkVector4_s0109_60e0 m_pivot;              // +0x00
	hkVector4_s0109_60e0 m_perpToAxle1;        // +0x10
	hkVector4_s0109_60e0 m_perpToAxle2;        // +0x20
};
struct hkHingeBasisB
{
	hkVector4_s0109_60e0 m_pivot;              // +0x00
	hkVector4_s0109_60e0 m_axle;               // +0x10
};
class hkHingeConstraintData : public hkConstraintData_s0109_60e0    // 0x60 bytes
{
public:
	hkHingeBasisA m_basisA;             // +0x10
	hkHingeBasisB m_basisB;             // +0x40

	virtual void getRuntimeInfo(hkBool_s0109_60e0 wantRuntime, hkConstraintData_s0109_60e0::RuntimeInfo& info) const;   // 0x01096B60
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual hkBool_s0109_60e0 isValid() const;                                                  // 0x01096B90
	virtual void buildJacobian(const hkConstraintQueryIn_s0109_60e0& in, hkConstraintQueryOut_s0109_60e0& out);   // 0x01096C70
};
namespace hkMath
{
	hkBool_s0109_60e0 equal(float a, float b, float eps);      // 0x01080E40
	float atan2fApproximation(float y, float x);    // 0x0120ADB0
}
static float hkAbsF(float v) { return (float)fabs(v); }
static __forceinline float hkLen3sq(const hkVector4_s0109_60e0& v) { return v.x * v.x + v.y * v.y + v.z * v.z; }
// ---- items of slice s010960e0 end

// ---- items of slice s01098200 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef int32_t  hkInt32;
typedef uint8_t  hkUint8;
class hkTransform_s0109_8200;
class hkVector4_s0109_8200
{ public:
    float x, y, z, w;
    void setMul(const hkVector4_s0109_8200& a, const hkVector4_s0109_8200& b);               // quaternion product (0x01082210)
    void normalize();                                                  // 0x010821a0
    void set(float a, float b, float c, float d) { x = a; y = b; z = c; w = d; }
};
typedef hkVector4_s0109_8200 hkQuaternion;
class hkRotation_s0109_8200                                                   // 0x30 bytes
{
public:
    hkVector4_s0109_8200 m_col[3];
    void set(const hkQuaternion& q);                               // 0x010824a0
    void setTranspose(const hkRotation_s0109_8200& r);                        // 0x01081550
};
class hkMatrix3_s0109_8200                                                    // 0x30 bytes: three 16-byte columns
{
public:
    float m_el[12];
    void setMulInverse(const hkMatrix3_s0109_8200& a, const hkRotation_s0109_8200& b);   // 0x01081f20
    void changeBasis(const hkRotation_s0109_8200& r);                         // 0x01082130
};
class hkTransform_s0109_8200
{ public:
    hkVector4_s0109_8200 m_rotation[3];      // +0x00..0x2f (columns)
    hkVector4_s0109_8200 m_translation;      // +0x30
    void setRotation(const hkQuaternion& q);                       // hkRotation::set 0x010824a0
};
class hkStepInfo_s0109_8200
{ public:
    float m_startTime;      // +0x00
    float m_endTime;        // +0x04
    float m_deltaTime;      // +0x08
    float m_invDeltaTime;   // +0x0c
};
class hkReferencedObject_s0109_8200
{
public:
    virtual ~hkReferencedObject_s0109_8200();                        // 0
    virtual void calcStatistics(void* c) const;           // 1
    hkInt16 m_memSizeAndFlags;                            // +0x04
    hkInt16 m_referenceCount;                             // +0x06
};
class hkSweptTransform_s0109_8200
{ public:
    hkVector4_s0109_8200 m_centerOfMass0;      // +0x00
    hkVector4_s0109_8200 m_centerOfMass1;      // +0x10
    hkQuaternion m_rotation0;       // +0x20
    hkQuaternion m_rotation1;       // +0x30
    hkVector4_s0109_8200 m_centerOfMassLocal;  // +0x40
};
class hkMotionState_s0109_8200
{ public:
    hkTransform_s0109_8200     m_transform;          // +0x00
    hkSweptTransform_s0109_8200 m_sweptTransform;    // +0x40
    hkVector4_s0109_8200       m_deltaAngle;         // +0x90
    float           m_objectRadius;       // +0xa0
    float           m_maxLinearVelocity;  // +0xa4
    float           m_maxAngularVelocity; // +0xa8
    hkUint16        m_deactivationClass;  // +0xac
    hkUint16        m_deactivationCounter;// +0xae
};
class hkVelocityAccumulator_s0109_8200                       // 0x90 bytes (the accumulator tail runs past 0x80)
{
public:
    hkUint8   m_type;                  // +0x00
    hkUint8   m_pad01[3];              // +0x01
    hkUint32  m_deactivationCounter;   // +0x04
    hkUint32  m_deactivationClass;     // +0x08
    hkUint8   m_flag0c;                // +0x0c
    hkUint8   m_pad0d[3];              // +0x0d
    hkVector4_s0109_8200 m_linearVelocity;   // +0x10
    hkVector4_s0109_8200 m_angularVelocity;  // +0x20
    hkVector4_s0109_8200 m_deltaPosition;    // +0x30
    hkVector4_s0109_8200 m_linearVelocity2;  // +0x40
    hkVector4_s0109_8200 m_angularVelocity2; // +0x50
    hkVector4_s0109_8200 m_deltaPosition2;   // +0x60
    hkVector4_s0109_8200 m_pad70;            // +0x70
};
class hkMemory_s0109_8200
{
public:
    virtual void* allocate(int nbytes, int cl);                       // 0
    virtual void  deallocate(void* p);                                // 1
    virtual void* alignedAllocate(int alignment, int nbytes, int cl); // 2
    virtual void  alignedDeallocate(void* p);                         // 3
    virtual void* allocateChunk(int nbytes, int cl);                  // 4
    virtual void  deallocateChunk(void* p, int nbytes, int cl);       // 5
    static hkMemory_s0109_8200* s_instance;                                      // 0x016e4178
};
hkMemory_s0109_8200* hkMemory_s0109_8200::s_instance;
extern hkVector4_s0109_8200 g_hkVector4Zero;              // 0x016e42d0 (created by the hkBoxMotion ctor call)
extern hkQuaternion g_hkQuaternionIdentity;    // 0x015b9b50
class hkString
{
public:
    static void memCpy(void* dst, const void* src, int size);   // 0x0107f440
};
static inline float hkFloorZero(float v) { return v < 0.0f ? 0.0f : v; }
class hkMotion_s0109_8200 : public hkReferencedObject_s0109_8200
{
public:
    virtual int  getType() const;                                             // 2
    virtual void step(const hkStepInfo_s0109_8200& stepInfo);                            // 3
    virtual void applyForcesAndStep(const hkStepInfo_s0109_8200& s, const hkVector4_s0109_8200& d);// 4
    virtual hkVelocityAccumulator_s0109_8200* applyForcesAndBuildAccumulator(const hkStepInfo_s0109_8200& stepInfo,
                                                                  hkVelocityAccumulator_s0109_8200* acc);  // 5
    virtual const hkVelocityAccumulator_s0109_8200* applyAccumulator(const hkStepInfo_s0109_8200& stepInfo,
                                                          const hkVelocityAccumulator_s0109_8200* acc);    // 6
    virtual void v7();                                                        // 7
    virtual hkMotion_s0109_8200* clone() const;                                          // 8
    virtual void setMass(float m);                                            // 9
    virtual void setMassInv(float mInv);                                      // 10
    virtual void getInertiaLocal(hkMatrix3_s0109_8200& out) const;                       // 11
    virtual void getInertiaWorld(hkMatrix3_s0109_8200& out) const;                       // 12
    virtual void setInertiaLocal(const hkMatrix3_s0109_8200& m);                         // 13
    virtual void setInertiaInvLocal(const hkMatrix3_s0109_8200& m);                      // 14
    virtual void getInertiaInvLocal(hkMatrix3_s0109_8200& out) const;                    // 15
    virtual void getInertiaInvWorld(hkMatrix3_s0109_8200& out) const;                    // 16
    virtual void getPosition(hkVector4_s0109_8200& out) const;                           // 17  0x010882b0
    virtual void getRotation(hkQuaternion& out) const;                        // 18  0x010882d0
    virtual void getTransform(hkTransform_s0109_8200& out) const;                        // 19  0x010882f0
    virtual void setPositionAndRotation(const hkVector4_s0109_8200& p, const hkQuaternion& q);   // 20  0x01088310
    virtual void setTransform(const hkTransform_s0109_8200& t);                          // 21  0x01088330
    virtual void setLinearVelocity(const hkVector4_s0109_8200& v);                       // 22  0x01088360
    virtual void setAngularVelocity(const hkVector4_s0109_8200& v);                      // 23  0x01088390
    virtual void applyLinearImpulse(const hkVector4_s0109_8200& imp);                    // 24  0x010883c0
    virtual void applyPointImpulse(const hkVector4_s0109_8200& imp, const hkVector4_s0109_8200& p); // 25
    virtual void applyAngularImpulse(const hkVector4_s0109_8200& imp);                   // 26
    virtual void applyForce(float deltaTime, const hkVector4_s0109_8200& force, const hkVector4_s0109_8200& p);  // 27
    virtual void applyForce(float deltaTime, const hkVector4_s0109_8200& force);         // 28
    hkInt32 m_solverData;                                                     // +0x08
};
class hkRigidMotion_s0109_8200 : public hkMotion_s0109_8200
{
public:
    hkRigidMotion_s0109_8200(const hkVector4_s0109_8200& position, const hkQuaternion& rotation);   // 0x01088500
    hkUint32  m_pad0c;                    // +0x0c (hkMotionState is 16-aligned)
    hkMotionState_s0109_8200 m_motionState;          // +0x10
    float     m_massInv;                  // +0xc0
    float     m_particleMinInertiaDiagInv;// +0xc4
    float     m_linearDamping;            // +0xc8
    float     m_angularDamping;           // +0xcc
    hkVector4_s0109_8200 m_linearVelocity;           // +0xd0
    hkVector4_s0109_8200 m_angularVelocity;          // +0xe0
};
class hkBoxMotion : public hkRigidMotion_s0109_8200
{
public:
    hkBoxMotion(const hkVector4_s0109_8200& position, const hkQuaternion& rotation);   // 0x01098140

    virtual void getInertiaLocal(hkMatrix3_s0109_8200& out) const;                     // 11  0x01098190
    virtual void getInertiaWorld(hkMatrix3_s0109_8200& out) const;                     // 12  0x01098390
    virtual void setMass(float m);                                          // 9   0x01098120
    virtual void setMassInv(float mInv);                                    // 10  0x01098410
    virtual void setInertiaLocal(const hkMatrix3_s0109_8200& m);                       // 13  0x01098200
    virtual void setInertiaInvLocal(const hkMatrix3_s0109_8200& m);                    // 14  0x010982b0
    virtual void getInertiaInvLocal(hkMatrix3_s0109_8200& out) const;                  // 15  0x01098250
    virtual void getInertiaInvWorld(hkMatrix3_s0109_8200& out) const;                  // 16  0x010982e0
    virtual void applyPointImpulse(const hkVector4_s0109_8200& imp, const hkVector4_s0109_8200& p);   // 25  0x010985b0
    virtual void applyAngularImpulse(const hkVector4_s0109_8200& imp);                 // 26  0x01098720
    virtual void applyForce(float deltaTime, const hkVector4_s0109_8200& force);       // 27  0x01098430
    virtual void applyForce(float deltaTime, const hkVector4_s0109_8200& force, const hkVector4_s0109_8200& p);  // 28  0x010984c0
    virtual hkMotion_s0109_8200* clone() const;                                        // 8   0x01098510
    virtual void applyForcesAndStep(const hkStepInfo_s0109_8200& s, const hkVector4_s0109_8200& d);   // 4  0x01098810
    virtual hkVelocityAccumulator_s0109_8200* applyForcesAndBuildAccumulator(const hkStepInfo_s0109_8200& stepInfo,
                                                                  hkVelocityAccumulator_s0109_8200* acc);  // 5  0x01098c50

    hkVector4_s0109_8200 m_inertiaAndMassInv;        // +0xf0
};
// ---- items of slice s01098200 end

// ---- items of slice s01098e50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char hkMonitorTimerEndTag[];             // 0x0149cc34 (end-of-timer marker)
extern "C" void FUN_01099670(void* pair, void* input, void* output);
class hkTransform_s0109_8e50;
class hkVector4_s0109_8e50
{ public:
    float x, y, z, w;
    void setMul(const hkVector4_s0109_8e50& a, const hkVector4_s0109_8e50& b);               // quaternion product (0x01082210)
    void normalize();                                                  // 0x010821a0
    void setRotatedDir(const hkTransform_s0109_8e50& t, const hkVector4_s0109_8e50& v);      // inline in the binary
    void setRotatedInverseDir(const hkTransform_s0109_8e50& t, const hkVector4_s0109_8e50& v);
    void setTransformedPos(const hkTransform_s0109_8e50& t, const hkVector4_s0109_8e50& p);  // 0x01081360
};
class hkTransform_s0109_8e50
{ public:
    hkVector4_s0109_8e50 m_rotation[3];      // +0x00..0x2f
    hkVector4_s0109_8e50 m_translation;      // +0x30
    void setRotation(const hkVector4_s0109_8e50& q);                              // hkRotation::set 0x010824a0
};
typedef hkVector4_s0109_8e50 hkQuaternion_s0109_8e50;
extern hkUint32 g_hkMonitorStreamCurrentTls;          // 0x016e42a4
extern hkUint32 g_hkMonitorStreamEndTls;              // 0x016e42a8
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(hkUint32 index, void* value);
static inline hkUint32 hkRdtscLow()
{
#if defined(_MSC_VER)
    return (hkUint32)__rdtsc();
#else
    return (hkUint32)__builtin_ia32_rdtsc();
#endif
}
struct hkMonitorRecord     { const char* m_name; hkUint32 m_time; hkUint32 m_pad; };
static inline void hkMonitorCommand(const char* name)
{
    hkMonitorRecord* cur = (hkMonitorRecord*)TlsGetValue(g_hkMonitorStreamCurrentTls);
    if (cur < (hkMonitorRecord*)TlsGetValue(g_hkMonitorStreamEndTls)) {
        cur->m_name = name;
        cur->m_time = hkRdtscLow();
        TlsSetValue(g_hkMonitorStreamCurrentTls, cur + 1);
    }
}
#define HK_TIMER_BEGIN(name)   hkMonitorCommand(name)
#define HK_TIMER_END()         hkMonitorCommand(hkMonitorTimerEndTag)
class hkReferencedObject_s0109_8e50
{
public:
    virtual ~hkReferencedObject_s0109_8e50();                       // 0
    virtual void calcStatistics(void* c) const;          // 1
    hkInt16 m_memSizeAndFlags;                           // +0x04
    hkInt16 m_referenceCount;                            // +0x06
};
class hkSweptTransform_s0109_8e50
{ public:
    hkVector4_s0109_8e50 m_centerOfMass0;      // +0x00
    hkVector4_s0109_8e50 m_centerOfMass1;      // +0x10
    hkQuaternion_s0109_8e50 m_rotation0;       // +0x20
    hkQuaternion_s0109_8e50 m_rotation1;       // +0x30
    hkVector4_s0109_8e50 m_centerOfMassLocal;  // +0x40
};
class hkMotionState_s0109_8e50
{ public:
    hkTransform_s0109_8e50     m_transform;          // +0x00
    hkSweptTransform_s0109_8e50 m_sweptTransform;    // +0x40
    hkVector4_s0109_8e50       m_deltaAngle;         // +0x90
    float           m_objectRadius;       // +0xa0
    float           m_maxLinearVelocity;  // +0xa4
    float           m_maxAngularVelocity; // +0xa8
    hkUint16        m_deactivationClass;  // +0xac
    hkUint16        m_deactivationCounter;// +0xae
};
class hkStepInfo_s0109_8e50
{ public:
    float m_startTime;     // +0x00
    float m_endTime;       // +0x04
    float m_deltaTime;     // +0x08
    float m_invDeltaTime;  // +0x0c
    hkStepInfo_s0109_8e50(float startTime, float endTime);   // 0x01099430
};
class hkVelocityAccumulator_s0109_8e50                       // 0x80 bytes
{
public:
    hkUint8   m_type;             // +0x00
    hkUint8   m_pad01[3];         // +0x01
    hkInt16   m_deactivationClass;// +0x04
    hkUint8   m_pad06[6];         // +0x06
    hkUint8   m_flag0c;           // +0x0c
    hkUint8   m_pad0d[3];         // +0x0d
    hkVector4_s0109_8e50 m_linearVelocity;   // +0x10
    hkVector4_s0109_8e50 m_angularVelocity;  // +0x20
    hkVector4_s0109_8e50 m_deltaPosition;    // +0x30
    hkVector4_s0109_8e50 m_linearVelocity2;  // +0x40
    hkVector4_s0109_8e50 m_angularVelocity2; // +0x50
    hkVector4_s0109_8e50 m_deltaPosition2;   // +0x60
    hkUint32  m_pad70[4];         // +0x70
    hkVector4_s0109_8e50 m_centerOfMass;     // +0x80
};
class hkMotion_s0109_8e50 : public hkReferencedObject_s0109_8e50
{
public:
    virtual int  getType() const;                                             // 2
    virtual void step(const hkStepInfo_s0109_8e50& stepInfo);                            // 3
    virtual void applyForcesAndStep(const hkStepInfo_s0109_8e50& s, const hkVector4_s0109_8e50& d);// 4
    virtual hkVelocityAccumulator_s0109_8e50* applyForcesAndBuildAccumulator(const hkStepInfo_s0109_8e50& stepInfo,
                                                                  hkVelocityAccumulator_s0109_8e50* acc);  // 5
    virtual const hkVelocityAccumulator_s0109_8e50* applyAccumulator(const hkStepInfo_s0109_8e50& stepInfo,
                                                          const hkVelocityAccumulator_s0109_8e50* acc);    // 6
    virtual void v7();                                                        // 7
    virtual hkMotion_s0109_8e50* clone() const;                                          // 8
    virtual void setMass(float m);                                            // 9
    hkInt32 m_solverData;                                                     // +0x08
};
class hkRigidMotion_s0109_8e50 : public hkMotion_s0109_8e50
{
public:
    hkRigidMotion_s0109_8e50(const hkVector4_s0109_8e50& position, const hkQuaternion_s0109_8e50& rotation);   // 0x01088500
    hkUint32  m_pad0c;                    // +0x0c (hkMotionState is 16-aligned)
    hkMotionState_s0109_8e50 m_motionState;          // +0x10
    float     m_massInv;                  // +0xc0
    float     m_particleMinInertiaDiagInv;// +0xc4
    float     m_linearDamping;            // +0xc8
    float     m_angularDamping;           // +0xcc
    hkVector4_s0109_8e50 m_linearVelocity;           // +0xd0
    hkVector4_s0109_8e50 m_angularVelocity;          // +0xe0
};
class hkBoxMotion_s0109_8e50 : public hkRigidMotion_s0109_8e50
{
public:
    hkBoxMotion_s0109_8e50(const hkVector4_s0109_8e50& position, const hkQuaternion_s0109_8e50& rotation);                        // 0x01098140
    virtual void setMass(float m);                                                               // 9
    virtual void getInertiaLocal(hkVector4_s0109_8e50& out) const;                                          // 11
    virtual const hkVelocityAccumulator_s0109_8e50* applyAccumulator(const hkStepInfo_s0109_8e50& stepInfo,
                                                          const hkVelocityAccumulator_s0109_8e50* acc);     // 0x01098e50
    const hkVector4_s0109_8e50& linearVelocity() const { return m_linearVelocity; }
    const hkVector4_s0109_8e50& angularVelocity() const { return m_angularVelocity; }
    void setLinearVelocity(const hkVector4_s0109_8e50& v) { m_linearVelocity = v; }
    void setAngularVelocity(const hkVector4_s0109_8e50& v) { m_angularVelocity = v; }
};
class hkConstraintQueryIn_s0109_8e50
{ public:
    char    m_pad00[0x30];
    const hkTransform_s0109_8e50* m_bodyA;             // +0x30 (32-bit two-pointer pair: A at +0x30, B at +0x34)
    const hkTransform_s0109_8e50* m_bodyB;             // +0x34
    char    m_pad38[0x44 - 0x38];
    hkInt32 m_source;                       // +0x44
};
void hkBeginConstraints(const hkConstraintQueryIn_s0109_8e50& in, void* out, int a, int b);   // 0x010aa080
void hkAddConstraint(const hkVector4_s0109_8e50& pivotA, const hkVector4_s0109_8e50& pivotB,
                     const hkConstraintQueryIn_s0109_8e50& in, void* out);                    // 0x010ab2d0
class hkBallAndSocketConstraintData
{
public:
    virtual void v00();                                                          // 0
    virtual void v04();                                                          // 1
    virtual void buildJacobian(const hkConstraintQueryIn_s0109_8e50& in, void* out);        // 0x01099330
    hkVector4_s0109_8e50 m_pivotA;   // +0x10
    hkVector4_s0109_8e50 m_pivotB;   // +0x20
};
class hkEntity_s0109_8e50;
class hkWorld_s0109_8e50;
void hkSweptTransformUtil_backStepMotionState(float time, hkMotionState_s0109_8e50& motionState);   // 0x0120a260
void hkLs_invalidateTimsOfEntity(hkEntity_s0109_8e50* entity, void* sibling);                        // 0x010a3890
void hkWorld_executePendingOperations(hkWorld_s0109_8e50* world);                                    // 0x01082bf0
struct hkToiEvent
{
    float     m_time;        // +0x00
    hkEntity_s0109_8e50* m_entities[2]; // +0x04, +0x08
};
class hkWorld_s0109_8e50
{ public:
    void*     m_vtable;                        // +0x00
    void*     m_simulation;                    // +0x04
    void*     m_agentNnTrack;                  // +0x08
    float     m_currentTime;                   // +0x0c
    char      m_pad10[0x18 - 0x10];
    float     m_timeOfNextFrame;               // +0x18
    char      m_pad1c[0x20 - 0x1c];
    float     m_gravityX;                      // +0x20
    float     m_gravityY;                      // +0x24
    float     m_gravityZ;                      // +0x28
    float     m_gravityW;                      // +0x2c
    char      m_pad30[0x38 - 0x30];
    void**    m_islands;                       // +0x38
    hkInt32   m_numIslands;                    // +0x3c
    char      m_pad40[0x78 - 0x40];
    void*     m_collisionInput;                // +0x78 (the whole hkProcessCollisionInput block)
    char      m_pad7c[0x80 - 0x7c];
    void*     m_actions;                       // +0x80 (hkArray<hkAction*> data pointer)
    hkInt32   m_numActions;                    // +0x84
    void*     m_pendingOperations;             // +0x88
    hkInt32   m_criticalSectionLock;           // +0x8c (bsp lock count)
    hkInt32   m_actionsLock;                   // +0x90
    char      m_executePendingOperations;      // +0x94
    char      m_pad95[0x130 - 0x95];
    void*     m_postIntegrateCallbackList;     // +0x130
    char      m_pad134[0x148 - 0x134];
    void*     m_activeEntities;                // +0x148
    char      m_pad14c[0x170 - 0x14c];
    hkStepInfo_s0109_8e50 m_dynamicsStepInfo;             // +0x170 (also the world->m_stepInfo passed to actions)
    char      m_stepInfo2[0x10];               // +0x180
    float     m_solverInfo184;                 // +0x184
    float     m_solverInfo188;                 // +0x188
    char      m_pad18c[0x190 - 0x18c];
    hkVector4_s0109_8e50 m_gravitySolver;                 // +0x190
    hkVector4_s0109_8e50 m_gravitySolverFrame;            // +0x1a0
    char      m_pad1b0[0x1d4 - 0x1b0];
    float     m_solverDamping;                 // +0x1d4
    char      m_pad1d8[0x1dc - 0x1d8];
    float     m_solverDamping2;                // +0x1dc
    char      m_pad1e0[0x2a4 - 0x1e0];
    float     m_solverDeltaTime;               // +0x2a4
    float     m_solverInvDeltaTime;            // +0x2a8
    hkInt32   m_solverNumIterations;           // +0x2ac
    float     m_solverTau;                     // +0x2b0
};
class hkEntity_s0109_8e50
{
public:
    char m_motionStateOffsetTable[0x58];       // +0x00..0x57 (vtable + entity data)
    hkMotionState_s0109_8e50* m_motionState;              // +0x58 (hkMotion + 0x10)
    char m_pad5c[0x9a - 0x5c];
    char m_isFixedOrKeyframed;                 // +0x9a
};
void hkWorldOperationUtil_cleanupDirtyIslands(hkWorld_s0109_8e50* world);                       // 0x010a07c0
void stepInputWakeUpContacts();                                                      // 0x00c2e4e0
void hkBuildAndSolve(void* stepInfo, void* dynamicsStepInfo, const void* stepInput, void* island,
                     void* entities, int numEntities);                               // 0x010a5070
void hkWorldCallbackUtil_fireIslandPostIntegrateCallback(hkWorld_s0109_8e50* world, void* island,
                                                         const hkStepInfo_s0109_8e50& stepInfo); // 0x0109f750
void hkWorldCallbackUtil_firePostIntegrateCallback(hkWorld_s0109_8e50* world,
                                                   const hkStepInfo_s0109_8e50& stepInfo);       // 0x0109f630
class hkSimulation : public hkReferencedObject_s0109_8e50
{
public:
    virtual void v00();                        // 0
    virtual void v04();                        // 1
    // Slot 2 is the collide entry point. The binary calls it off hkSimulation's vtable at +8 with four
    // arguments (entities, count, world, &stepInfo); hkDiscreteSimulation overrides it for real.
    virtual void collideEntitiesNarrowPhaseDiscrete(hkEntity_s0109_8e50** entities, int numEntities,
                                                    hkWorld_s0109_8e50* world, const void* stepInfo);  // +0x08
    virtual void v0c();
    hkInt32 m_type;                            // +0x2c
};
void hkDiscreteSimulation_collideEntitiesNarrowPhaseDiscrete(hkSimulation* sim, hkEntity_s0109_8e50** entities,
                                                             int numEntities,
                                                             const void* collisionInput);  // 0x010f25d0
void FUN_010a08b0(hkSimulation* sim, hkEntity_s0109_8e50* entity);                                    // 0x010a08b0
class hkDiscreteSimulation : public hkSimulation
{
public:
    virtual void collideEntitiesNarrowPhaseDiscrete(hkEntity_s0109_8e50** entities, int numEntities,
                                                    hkWorld_s0109_8e50* world, const void* stepInfo);  // +0x08
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
    virtual void stepIntegrate(hkWorld_s0109_8e50* world, const hkStepInfo_s0109_8e50& stepInfo);        // 0x01099690
    virtual void processAgentCollideDiscrete(void* entry, const void* input,
                                             void* output);                        // 0x010995d0
    virtual void processAgentResetCollisionInformation(void* entry, const void* input,
                                                       void* output);              // 0x01099670
};
class hkBackstepSimulation : public hkDiscreteSimulation
{
public:
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual void simulateToi(hkWorld_s0109_8e50* world, hkToiEvent& event, float time);   // 0x01099480
};
void _hkAgentNnMachine_InvalidateTimInAgent(void* entry, const void* sibling);   // 0x010fba10
typedef void (*hkCollideFunc)(void* pair, void* input, void* output);   // 0x01099670 as passed by the caller
// ---- items of slice s01098e50 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void __stdcall FUN_01099be0(void* entities, int numEntities, void* collideInput, hkCollideFunc collideFunc);  // 0x01099be0 (stays in the slice: not this object's)

// ---- items of slice s0109c3b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);   // kernel32, IAT 0x013cc2dc
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void* cs);  // kernel32, IAT 0x013cc2d4
extern void* g_hkThreadMemoryTls;    // 0x016e4174
extern float g_14a1f98;              // 0x014a1f98
extern void* g_13ef094;              // vtable
extern void* g_imp_InitCrit;              // 0x013cc1c0
extern "C" void* __cdecl memcpy(void* dst, const void* src, uint size);
void* FUN_010fc180(void* a, void* b, void* c);        // 0x010fc180
struct CritSec {                                       // hkCriticalSection, __thiscall (this = the CS)
    void enter();                                      // 0x0107f820, no stack arguments, returns via ret
};
void* FUN_010f0b00(void* a, void* b);                  // 0x010f0b00
void* __stdcall FUN_010f19b0(int a);                   // 0x010f19b0 (callee pops)
void* FUN_010f1a10(void* self);                        // 0x010f1a10
void* FUN_010fbb30(void* a, void* b);                  // 0x010fbb30
void* FUN_010a39f0(void* a);                           // 0x010a39f0
void* FUN_010a3920(void* a, void* b, void* c);         // 0x010a3920
void* FUN_0107f530(void* arr, int sz);                 // 0x0107f530 hkArrayUtil::_reserveMore
struct SimSub {
    void* FUN_01082900();                              // 0x01082900 hkMultithreadConfig ctor
    void* FUN_010a5a90();                              // 0x010a5a90 hkJobQueue ctor
    void* FUN_010a65e0();                              // 0x010a65e0 hkJobQueue dtor
    void* FUN_0107db10(int data, int size, int align); // 0x0107db10 hkThreadMemory::deallocateChunk
};
void* FUN_010a65e0();                                  // 0x010a65e0 hkJobQueue dtor
void* FUN_0107db10(void* mem, int a, int b, int c);    // 0x0107db10 hkThreadMemory::deallocateChunk
extern void* g_hkMemory_s0109_c3b0;             // 0x016e4178
typedef void (__stdcall* InitCritFn)(void* cs, uint spin);
inline void InitCrit(void* cs, uint spin) { ((InitCritFn)g_imp_InitCrit)(cs, spin); }
struct HkMemory {
    int  mField00;          // +0x00
    int  mOutOfMemory;      // +0x04  set to 1 when the memory manager reports exhaustion
    int  mCapacity;         // +0x08
    int  mField0C;          // +0x0c
    int  mField10;          // +0x10
    int  mUsed;             // +0x14
    int  mField18[4];       // +0x18
    int  mPeakUsed;         // +0x28
};
struct AgentClass {
    uint8_t mField00[0x10];
    uint8_t mField10;       // +0x10
    uint8_t mField11[0x2b];
};
struct SimThread {
    void* FUN_010f0b00(void* a, void* b);   // 0x010f0b00, __thiscall (callee pops 8)
};
struct AgentListOwner {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05(void* a, void* b, void* c, void* d);
};
struct hkMultiThreadedSimulation {
    int prepareMultithreadStep();
    hkMultiThreadedSimulation* ctor(char* owner);      // 0x0109c940, __thiscall (ret 4)
    void dtor();                                       // 0x0109cab0
    void* FUN_010f1a10();                              // 0x010f1a10 (tail-called by dtor)
};
struct hkMtThreadStructure { void* ctor(char* world, int sim, int type); };
struct MtEntityEntityBroadPhaseListener { void addCollisionPair(int* pair); void removeCollisionPair(int* pair); };
// ---- items of slice s0109c3b0 end

// ---- items of slice s0109e8e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#ifndef _WIN64
#else
#endif
template <typename T> class hkArray_s0109_e8e0 { public: T* m_data; int32_t m_size; int32_t m_capacityAndFlags; };
template <typename T>
static inline void hkRemoveNullListeners(hkArray_s0109_e8e0<T*>& a)
{
    for (int i = a.m_size - 1; i >= 0; --i) {
        if (a.m_data[i] == 0) {
            a.m_size = a.m_size - 1;
            for (int j = i; j < a.m_size; ++j)
                a.m_data[j] = a.m_data[j + 1];
        }
    }
}
struct hkStepInfo_s0109_e8e0;
struct hkAction_s0109_e8e0;
class hkEntity_s0109_e8e0;
struct hkPhantom_s0109_e8e0;
struct hkConstraintInstance_s0109_e8e0;
class hkSimulationIsland_s0109_e8e0;
class hkWorld_s0109_e8e0;
struct hkContactPointAddedEvent;
struct hkContactPointConfirmedEvent;
struct hkContactPointRemovedEvent;
struct hkContactProcessEvent;
class hkActionListener_s0109_e8e0 { public:
    virtual void vslot0();
    virtual void actionAddedCallback(hkAction_s0109_e8e0* a);                      // +4
    virtual void actionRemovedCallback(hkAction_s0109_e8e0* a);                    // +8
};
struct hkWorldEntityListener {
    virtual void vslot0();
    virtual void entityAddedCallback(hkEntity_s0109_e8e0* e);                      // +4
    virtual void entityRemovedCallback(hkEntity_s0109_e8e0* e);                    // +8
    virtual void entityShapeSetCallback(hkEntity_s0109_e8e0* e);                   // +0xc
};
struct hkWorldPhantomListener {
    virtual void vslot0();
    virtual void phantomAddedCallback(hkPhantom_s0109_e8e0* p);                    // +4
    virtual void phantomRemovedCallback(hkPhantom_s0109_e8e0* p);                  // +8
    virtual void phantomShapeSetCallback(hkPhantom_s0109_e8e0* p);                 // +0xc
};
struct hkWorldConstraintListener {
    virtual void vslot0();
    virtual void constraintAddedCallback(hkConstraintInstance_s0109_e8e0* c);      // +4
    virtual void constraintRemovedCallback(hkConstraintInstance_s0109_e8e0* c);    // +8
};
class hkWorldDeletionListener_s0109_e8e0 { public:
    virtual void vslot0();
    virtual void worldDeletedCallback(hkWorld_s0109_e8e0* w);                      // +4
};
struct hkIslandActivationListener {
    virtual void vslot0();
    virtual void islandActivatedCallback(hkSimulationIsland_s0109_e8e0* i);        // +4
    virtual void islandDeactivatedCallback(hkSimulationIsland_s0109_e8e0* i);      // +8
};
struct hkWorldPostSimulationListener {
    virtual void vslot0();
    virtual void postSimulationCallback(hkWorld_s0109_e8e0* w, const hkStepInfo_s0109_e8e0& s);   // +4
};
struct hkWorldPostIntegrateListener {
    virtual void vslot0();
    virtual void postIntegrateCallback(hkWorld_s0109_e8e0* w, const hkStepInfo_s0109_e8e0& s);    // +4
};
struct hkWorldPostCollideListener {
    virtual void vslot0();
    virtual void postCollideCallback(hkWorld_s0109_e8e0* w, const hkStepInfo_s0109_e8e0& s);      // +4
};
struct hkIslandPostIntegrateListener {
    virtual void vslot0();
    virtual void postIntegrateCallback(hkSimulationIsland_s0109_e8e0* i, const hkStepInfo_s0109_e8e0& s);   // +4
};
struct hkIslandPostCollideListener {
    virtual void vslot0();
    virtual void postCollideCallback(hkSimulationIsland_s0109_e8e0* i, const hkStepInfo_s0109_e8e0& s);     // +4
};
struct hkContactListener {                      // no destructor slot
    virtual void contactPointAddedCallback(hkContactPointAddedEvent& e);              // +0
    virtual void contactPointConfirmedCallback(hkContactPointConfirmedEvent& e);      // +4
    virtual void contactPointRemovedCallback(hkContactPointRemovedEvent& e);          // +8
    virtual void contactProcessCallback(hkContactProcessEvent& e);                    // +0xc
};
class hkEntityListener_s0109_e8e0 { public:
    virtual void vslot0();
    virtual void vslot1();
    virtual void entityRemovedCallback(hkEntity_s0109_e8e0* e);                    // +8
    virtual void vslot3();
};
struct hkEntityActivationListener {
    virtual void vslot0();
    virtual void entityDeactivatedCallback(hkEntity_s0109_e8e0* e);                // +4
    virtual void entityActivatedCallback(hkEntity_s0109_e8e0* e);                  // +8
};
struct hkEntityExtendedListener {
virtual void vslot0();
virtual void vslot1();
virtual void vslot2();
virtual void vslot3();
virtual void vslot4();
    virtual void entityDeletedCallback(hkEntity_s0109_e8e0* e);                    // +0x14
};
struct hkEntityOwnedObject {                                            // actions / constraints attached to an entity
virtual void vslot0();
virtual void vslot1();
virtual void vslot2();
    virtual void entityRemovedCallback(hkEntity_s0109_e8e0* e);                    // +0xc (removes itself from the entity's array)
};
struct hkContactPointAddedEvent       { void* m_bodyA; void* m_bodyB; int32_t m_type; void* m_callbackFiredFrom; /* +0xc */ };
struct hkContactPointConfirmedEvent   { void* m_bodyA; void* m_bodyB; void* m_callbackFiredFrom; /* +8 */ };
struct hkContactPointRemovedEvent     { uint16_t m_id; uint16_t m_pad; void* m_material; void* m_bodyA; void* m_bodyB; void* m_callbackFiredFrom; /* +0x10 */ };
struct hkContactProcessEvent          { void* m_bodyA; void* m_bodyB; void* m_callbackFiredFrom; /* +8 */ };
class hkSimulationIsland_s0109_e8e0 { public:
    uint8_t m_pad[0x3c];
    hkEntity_s0109_e8e0** m_entities;              // +0x3c
    int32_t m_numEntities;              // +0x40
};
class hkEntity_s0109_e8e0 { public:
    uint8_t m_pad0[0x70];
    hkArray_s0109_e8e0<hkEntityOwnedObject*> m_actions;                    // +0x70
    hkArray_s0109_e8e0<hkEntityOwnedObject*> m_constraints;                // +0x7c (hkConstraintInstance*)
    uint8_t m_pad1[0x9c - 0x88];
    hkArray_s0109_e8e0<hkContactListener*> m_contactListeners;             // +0x9c
    hkArray_s0109_e8e0<hkEntityActivationListener*> m_activationListeners; // +0xa8
    hkArray_s0109_e8e0<hkEntityListener_s0109_e8e0*> m_entityListeners;               // +0xb4
    hkArray_s0109_e8e0<hkEntityExtendedListener*> m_extendedListeners;     // +0xc0
};
class hkWorld_s0109_e8e0 { public:
    uint8_t m_pad0[0x88];
    int32_t m_pendingOperationsCount;                           // +0x88
    int32_t m_criticalOperationsLockCount;                      // +0x8c
    uint8_t m_pad1[4];
    uint8_t m_pendingOperationsInProgress;                      // +0x94
    uint8_t m_pad2[0xd8 - 0x95];
    hkArray_s0109_e8e0<hkActionListener_s0109_e8e0*>             m_actionListeners;                // +0xd8
    hkArray_s0109_e8e0<hkWorldEntityListener*>        m_entityListeners;                // +0xe4
    hkArray_s0109_e8e0<hkWorldPhantomListener*>       m_phantomListeners;               // +0xf0
    hkArray_s0109_e8e0<hkWorldConstraintListener*>    m_constraintListeners;            // +0xfc
    hkArray_s0109_e8e0<hkWorldDeletionListener_s0109_e8e0*>      m_worldDeletionListeners;         // +0x108
    hkArray_s0109_e8e0<hkIslandActivationListener*>   m_islandActivationListeners;      // +0x114
    hkArray_s0109_e8e0<hkWorldPostSimulationListener*> m_postSimulationListeners;       // +0x120
    hkArray_s0109_e8e0<hkWorldPostIntegrateListener*> m_postIntegrateListeners;         // +0x12c
    hkArray_s0109_e8e0<hkWorldPostCollideListener*>   m_postCollideListeners;           // +0x138
    hkArray_s0109_e8e0<hkIslandPostIntegrateListener*> m_islandPostIntegrateListeners;  // +0x144
    hkArray_s0109_e8e0<hkIslandPostCollideListener*>  m_islandPostCollideListeners;     // +0x150
    hkArray_s0109_e8e0<hkContactListener*>            m_contactListeners;               // +0x15c

    // @ 0x01082bf0 (ecx = world): run operations queued while the world was locked
    void attemptToExecutePendingOperations();
};
struct hkEntityCallbackUtil {
    static void fireContactPointRemovedInternal(hkEntity_s0109_e8e0* e, hkContactPointRemovedEvent& ev);
    static void fireContactProcessInternal(hkEntity_s0109_e8e0* e, hkContactProcessEvent& ev);
    static void fireEntityRemoved(hkEntity_s0109_e8e0* e);
};
struct hkWorldCallbackUtil {
    static void fireActionAdded(hkWorld_s0109_e8e0* w, hkAction_s0109_e8e0* a);
    static void fireActionRemoved(hkWorld_s0109_e8e0* w, hkAction_s0109_e8e0* a);
    static void fireEntityAdded(hkWorld_s0109_e8e0* w, hkEntity_s0109_e8e0* e);
    static void fireEntityRemoved(hkWorld_s0109_e8e0* w, hkEntity_s0109_e8e0* e);
    static void fireEntityShapeSet(hkWorld_s0109_e8e0* w, hkEntity_s0109_e8e0* e);
    static void firePhantomAdded(hkWorld_s0109_e8e0* w, hkPhantom_s0109_e8e0* p);
    static void firePhantomRemoved(hkWorld_s0109_e8e0* w, hkPhantom_s0109_e8e0* p);
    static void firePhantomShapeSet(hkWorld_s0109_e8e0* w, hkPhantom_s0109_e8e0* p);
    static void fireConstraintAdded(hkWorld_s0109_e8e0* w, hkConstraintInstance_s0109_e8e0* c);
    static void fireConstraintRemoved(hkWorld_s0109_e8e0* w, hkConstraintInstance_s0109_e8e0* c);
    static void fireContactPointAdded(hkWorld_s0109_e8e0* w, hkContactPointAddedEvent& ev);
    static void fireContactPointConfirmed(hkWorld_s0109_e8e0* w, hkContactPointConfirmedEvent& ev);
    static void fireContactPointRemoved(hkWorld_s0109_e8e0* w, hkContactPointRemovedEvent& ev);
    static void fireContactProcess(hkWorld_s0109_e8e0* w, hkContactProcessEvent& ev);
    static void fireWorldDeleted(hkWorld_s0109_e8e0* w);
    static void fireIslandActivated(hkWorld_s0109_e8e0* w, hkSimulationIsland_s0109_e8e0* i);
    static void fireIslandDeactivated(hkWorld_s0109_e8e0* w, hkSimulationIsland_s0109_e8e0* i);
    static void firePostSimulationCallback(hkWorld_s0109_e8e0* w, const hkStepInfo_s0109_e8e0& s);
    static void firePostIntegrateCallback(hkWorld_s0109_e8e0* w, const hkStepInfo_s0109_e8e0& s);
    static void firePostCollideCallback(hkWorld_s0109_e8e0* w, const hkStepInfo_s0109_e8e0& s);
    static void fireIslandPostIntegrateCallback(hkWorld_s0109_e8e0* w, hkSimulationIsland_s0109_e8e0* i, const hkStepInfo_s0109_e8e0& s);
    static void fireIslandPostCollideCallback(hkWorld_s0109_e8e0* w, hkSimulationIsland_s0109_e8e0* i, const hkStepInfo_s0109_e8e0& s);
};
#define HK_FIRE_LISTENERS(ARR, CALL)                                  \
    do {                                                              \
        for (int i_ = (ARR).m_size - 1; i_ >= 0; --i_) {              \
            if ((ARR).m_data[i_] != 0) { CALL((ARR).m_data[i_]); }    \
        }                                                             \
        hkRemoveNullListeners(ARR);                                   \
    } while (0)
static inline void hkWorld_unlockAndFlush(hkWorld_s0109_e8e0* w)
{
    int n = w->m_criticalOperationsLockCount - 1;
    w->m_criticalOperationsLockCount = n;
    if (n == 0 && w->m_pendingOperationsCount != 0 && w->m_pendingOperationsInProgress == 0)
        w->attemptToExecutePendingOperations();
}
// ---- items of slice s0109e8e0 end

// ---- items of slice s0109f870 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct hkConstraintInstance_s0109_f870;
class hkSimpleConstraintOwner_s0109_f870
{ public:
	virtual void* destroy(unsigned flags);               // 0 (scalar deleting destructor)
virtual void v1();
virtual void v2();
	virtual void addConstraintInfo(hkConstraintInstance_s0109_f870* c, struct hkConstraintInfo_s0109_f870& info);   // 3, 0x0109F9C0
	virtual void subConstraintInfo(hkConstraintInstance_s0109_f870* c, struct hkConstraintInfo_s0109_f870& info);   // 4, 0x0109F900
	int m_pad4;                                         // +4
	int m_maxSizeOfJacobians;                           // +8
	int m_sizeOfJacobians;                              // +0xc
	int m_sizeOfSchemas;                                // +0x10
	int m_numMotionInfo;                                // +0x14 (inferred, addMotionInfo/subMotionInfo)
	int m_numSolverResults;                             // +0x18
};
struct hkConstraintInfo_s0109_f870 { int m_maxSizeOfJacobians, m_sizeOfJacobians, m_sizeOfSchemas, m_numSolverResults; };
// ---- items of slice s0109f870 end

// ---- items of slice s01090a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct hkQuaternionOps
{
	void setMulInverse(const hkQuaternion& a, const hkQuaternion& b);   // 0x01091970 (this = out)
	void setMul(const hkQuaternion& a, const hkQuaternion& b);         // 0x01082210
	void normalize();                                                  // 0x010821A0
};
// ---- items of slice s01090a70 end

// @ 0x01091970
void hkQuaternionOps::setMulInverse(const hkQuaternion& q0, const hkQuaternion& q1)
{
    hkQuaternion& out = *(hkQuaternion*)this;
    out.x = q0.z * q1.y - q0.y * q1.z - q0.w * q1.x + q1.w * q0.x;
    out.y = q0.x * q1.z - q0.z * q1.x - q0.w * q1.y + q1.w * q0.y;
    out.z = q0.y * q1.x - q0.x * q1.y - q0.w * q1.z + q1.w * q0.z;
    out.w = q0.x * q1.x + q0.y * q1.y + q0.w * q1.w + q0.z * q1.z;
}

// @ 0x01091a60
void hkRelativeOrientationConstraintData::buildJacobian( const hkConstraintQueryIn &in, hkConstraintQueryOut &out) const
{
    const char *self = (const char *)this;

    hkBeginConstraints(in, out, *(const int *)((const char *)&in + 0x44), 8);

    hkQuaternion_s0109_1a60 qA, qB, qC;
    qA.set(*(const void **)((const char *)&in + 0x30));
    qB.set(*(const void **)((const char *)&in + 0x34));
    qC.setMul(qA, *(const hkQuaternion_s0109_1a60 *)(self + 0x10));

    const float cx = qC.x, cy = qC.y, cz = qC.z, cw = qC.w;
    const float bx = qB.x, by = qB.y, bz = qB.z, bw = qB.w;

    float fVar1 = cw * cw;
    int   iVar8 = 2;
    const float *pfVar7 = hk_identityBasis + 2;
    int   local_f8 = 3;

    do {
        float axes[12];

        // ---- first axis: qC against basis row (iVar8 - 2) -----------------
        float fVar2 = cy * pfVar7[-1] + (cx * pfVar7[-2] + cz * pfVar7[0]);
        float v18   = cx * pfVar7[-1] - cy * pfVar7[-2];
        float a90 = cw * (cy * pfVar7[0] - cz * pfVar7[-1]) +
                    (fVar2 * cx + (fVar1 - 0.5f) * pfVar7[-2]);
        float a8c = (cz * pfVar7[-2] - cx * pfVar7[0]) * cw +
                    (cy * fVar2 + (fVar1 - 0.5f) * pfVar7[-1]);
        float a88 = v18 * cw + (cz * fVar2 + (fVar1 - 0.5f) * pfVar7[0]);
        float a84 = (cw * fVar2 + (fVar1 - 0.5f) * pfVar7[1]) + cw * hk_zero;
        axes[4] = a90 + a90;
        axes[5] = a8c + a8c;
        axes[6] = a88 + a88;
        axes[7] = a84 + a84;

        // ---- second axis: qC against basis row (iVar8 - 1); passed on -----
        int iVar4 = (iVar8 - 1) % 3;
        float v68 = fVar1 - 0.5f;
        float v64 = fVar1 - 0.5f;
        const float *pfVar5 = hk_identityBasis + iVar4 * 4;
        fVar2 = cy * pfVar5[1] + (cz * pfVar5[2] + cx * pfVar5[0]);
        int iVar6 = iVar8 % 3;
        float v48 = cx * pfVar5[1] - cy * pfVar5[0];
        float b0 = (cy * pfVar5[2] - cz * pfVar5[1]) * cw +
                   (fVar2 * cx + (fVar1 - 0.5f) * pfVar5[0]);
        float b1 = (cz * pfVar5[0] - cx * pfVar5[2]) * cw +
                   (cy * fVar2 + (fVar1 - 0.5f) * pfVar5[1]);
        float b2 = v48 * cw + (cz * fVar2 + v68 * pfVar5[2]);
        float b3 = (fVar2 * cw + v64 * pfVar5[3]) + hk_zero;
        axes[0] = b0 + b0;
        axes[1] = b1 + b1;
        axes[2] = b2 + b2;
        axes[3] = b3 + b3;

        // ---- companion axis: qB against basis row iVar8 -------------------
        pfVar5 = hk_identityBasis + iVar6 * 4;
        float fVar2b = bw * bw;
        float fVar3 = by * pfVar5[1] + (bz * pfVar5[2] + bx * pfVar5[0]);
        float v38 = bx * pfVar5[1] - by * pfVar5[0];
        float c80 = bw * (by * pfVar5[2] - bz * pfVar5[1]) +
                    (fVar3 * bx + (fVar2b - 0.5f) * pfVar5[0]);
        float c7c = (bz * pfVar5[0] - bx * pfVar5[2]) * bw +
                    (by * fVar3 + (fVar2b - 0.5f) * pfVar5[1]);
        float c78 = v38 * bw + (bz * fVar3 + (fVar2b - 0.5f) * pfVar5[2]);
        float c74 = bw * hk_zero + (bw * fVar3 + (fVar2b - 0.5f) * pfVar5[3]);
        axes[8]  = c80 + c80;
        axes[9]  = c7c + c7c;
        axes[10] = c78 + c78;
        axes[11] = c74 + c74;

        hk1dAngularBilateralJacobian(axes, in, out);

        pfVar7 = pfVar7 + 4;
        iVar8 = iVar8 + 1;
        local_f8 = local_f8 - 1;
    } while (local_f8 != 0);
}

// @ 0x01091ff0
hkBool_s0109_1a60 hkPulleyConstraintData::isValid() const
{
    if (*(const float *)((const char *)this + 0xc) <= 0.0f ||
        *(const float *)((const char *)this + 0x10) <= 0.0f) {
        return hkBool_s0109_1a60(false);
    }
    return hkBool_s0109_1a60(true);
}

// @ 0x01092090
void hkPulleyConstraintData::buildJacobian(const hkConstraintQueryIn &in, hkConstraintQueryOut &out) const
{
    const char *c = (const char *)this;
    hkBeginConstraints(in, out, *(const int *)((const char *)&in + 0x44), 8);

    const float *mA = *(const float **)((const char *)&in + 0x30);
    const float *mB = *(const float **)((const char *)&in + 0x34);
    float x, y, z;

    PulleyJacobianData d;
    x = *(const float *)(c + 0x20);
    y = *(const float *)(c + 0x24);
    z = *(const float *)(c + 0x28);
    d.posA[0] = x * mA[0] + (y * mA[4] + z * mA[8]) + mA[0xc];
    d.posA[1] = x * mA[1] + (y * mA[5] + z * mA[9]) + mA[0xd];
    d.posA[2] = x * mA[2] + (y * mA[6] + z * mA[10]) + mA[0xe];
    d.posA[3] = 0.0f;
    x = *(const float *)(c + 0x30);
    y = *(const float *)(c + 0x34);
    z = *(const float *)(c + 0x38);
    d.posB[0] = x * mB[0] + (y * mB[4] + z * mB[8]) + mB[0xc];
    d.posB[1] = x * mB[1] + (y * mB[5] + z * mB[9]) + mB[0xd];
    d.posB[2] = x * mB[2] + (y * mB[6] + z * mB[10]) + mB[0xe];
    d.posB[3] = 0.0f;
    d.p[0] = *(const int *)(c + 0x40);
    d.p[1] = *(const int *)(c + 0x44);
    d.p[2] = *(const int *)(c + 0x48);
    d.p[3] = *(const int *)(c + 0x4c);
    d.q[0] = *(const int *)(c + 0x50);
    d.q[1] = *(const int *)(c + 0x54);
    d.q[2] = *(const int *)(c + 0x58);
    d.q[3] = *(const int *)(c + 0x5c);
    d.f0 = *(const float *)(c + 0xc);
    d.f1 = *(const float *)(c + 0x10);
    hkPulleyConstraintBuildJacobian(&d, in, out);
}

// @ 0x010921f0
void *hkConstraintAtomBase::scalarDeletingDtor(byte flags)
{
    char *self = (char *)this;
    *(int *)self = (int)&vtbl_014a1aa8;
    hkRefCountedObject *p = *(hkRefCountedObject **)(self + 0xc);
    if (p != 0 && p->m_memSizeAndFlags != 0) {
        if (--p->m_referenceCount == 0) {
            p->__deleteThis(1);
        }
    }
    *(int *)self = (int)&vtbl_013ef094;
    if ((flags & 1) != 0) {
        g_hkMemory->deallocate(self, *(const ushort *)(self + 4), 0x29);
    }
    return self;
}

// @ 0x01092270
hkBool_s0109_1a60 hkPrismaticConstraintData::isValid() const
{
    const float *f = (const float *)this;
    float dot = f[0x80 / 4] * f[0x70 / 4] +
                (f[0x84 / 4] * f[0x74 / 4] + f[0x88 / 4] * f[0x78 / 4]);
    float n1 = f[0x80 / 4] * f[0x80 / 4] + f[0x84 / 4] * f[0x84 / 4] +
               f[0x88 / 4] * f[0x88 / 4];
    float n0 = f[0x70 / 4] * f[0x70 / 4] + f[0x74 / 4] * f[0x74 / 4] +
               f[0x78 / 4] * f[0x78 / 4];
    if (Fabs(dot) < 1.0e-5f &&
        Fabs(n1 - 1.0f) < 1.0e-5f &&
        Fabs(n0 - 1.0f) < 1.0e-5f &&
        f[0x90 / 4] <= f[0x94 / 4]) {
        return hkBool_s0109_1a60(true);
    }
    return hkBool_s0109_1a60(false);
}

// @ 0x01093660
void hkPoweredChainData::getConstraintInfo(hkConstraintInfo& info) const
{
	info.m_sizeOfJacobians = 0;
	info.m_numSolverResults = 0;
	info.m_maxSizeOfJacobians = 0;
	info.m_sizeOfSchemas = 0x18;

	int n = m_infos.m_size;
	info.m_sizeOfSchemas = n * 0x50 + 0x34;
	info.m_sizeOfJacobians = n * 0x4f0 + 0x20;
	info.m_numSolverResults = n * 6;
}

// @ 0x010936a0
void hkPoweredChainData::getRuntimeInfo(hkBool_s0109_2e10, hkConstraintData_s0109_2e10::RuntimeInfo& info) const
{
	int n = m_infos.m_size;
	int numSolverResults = n * 6;
	info.m_numSolverResults = numSolverResults;
	info.m_sizeOfExternalRuntime = ((n + 3) & ~3) + (numSolverResults + n * 2) * 8;
}

// @ 0x010936c0
static void quaternionError(hkVector4_s0109_2e10& out, const hkQuaternion_s0109_2e10& a, const hkQuaternion_s0109_2e10& b)
{
	out.w = 0.0f;
	out.x = a.z * b.y - a.y * b.z;
	out.y = a.x * b.z - a.z * b.x;
	out.z = b.x * a.y - b.y * a.x;
	const float aw = a.w;
	out.x = aw * b.x + out.x;
	out.y = aw * b.y + out.y;
	out.z = aw * b.z + out.z;
	out.w = aw * b.w;
	const float bw = b.w;
	out.x = out.x - bw * a.x;
	out.y = out.y - bw * a.y;
	out.z = out.z - bw * a.z;
	out.w = out.w - bw * a.w;
	const float x2 = out.x + out.x;
	const float y2 = out.y + out.y;
	const float z2 = out.z + out.z;
	const float w2 = out.w + out.w;
	out.x = x2;
	out.y = y2;
	out.z = z2;
	out.w = w2;
	const float dot = b.x * a.x + b.y * a.y + b.w * a.w + a.z * b.z;
	if (dot < kZero) {
		out.x = -x2;
		out.y = -y2;
		out.z = -z2;
		out.w = -w2;
	}
}

// @ 0x010937e0
int SP::cSPToolStrategy::AdjustCost(int cost)
{
	return cost;
}

// @ 0x01093810
hkPoweredChainData::~hkPoweredChainData()
{
	for (int i = 0; i < m_infos.m_size; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			hkConstraintMotor* motor = m_infos.m_data[i].m_motors[j];
			if (motor)
				motor->removeReference();
		}
	}
}

// @ 0x01094bc0
void cCurveContainer::Destroy()
{
	this->mpVtbl = (void*)0x014a1b88;
	int i;
	int n = this->m_arrays[0].m_size;
	for (i = 0; i < n; ++i)
		((cCurveElem*)this->m_arrays[0].m_data[i])->Release();
	n = this->m_arrays[3].m_size;
	for (i = 0; i < n; ++i)
		((cCurveElem*)this->m_arrays[3].m_data[i])->Release();
	n = this->m_arrays[1].m_size;
	for (i = 0; i < n; ++i) {
		cRefObj* p = (cRefObj*)this->m_arrays[1].m_data[i];
		if (p->m_memSize != 0) {
			if (--p->m_refCount == 0)
				p->Release(1);
		}
	}
	n = this->m_arrays[2].m_size;
	for (i = 0; i < n; ++i) {
		cRefObj* p = (cRefObj*)this->m_arrays[2].m_data[i];
		if (p != 0) {
			if (p->m_memSize != 0) {
				if (--p->m_refCount == 0)
					p->Release(1);
			}
		}
	}

	cGetHeapFn getHeap = gGetHeap;
	int mask = (int)0x80000000;
	int flags = this->m_arrays[3].m_capacityAndFlags;
	if (!(flags & mask)) {
		cHeap* heap = (cHeap*)getHeap(gAllocator);
		heap->Dealloc(this->m_arrays[3].m_data,
		              (this->m_arrays[3].m_capacityAndFlags & 0x3fffffff) * 4, 0x14);
	}
	if (!(this->m_arrays[2].m_capacityAndFlags & mask)) {
		cHeap* heap = (cHeap*)getHeap(gAllocator);
		heap->Dealloc(this->m_arrays[2].m_data,
		              (this->m_arrays[2].m_capacityAndFlags & 0x3fffffff) * 4, 0x14);
	}
	if (!(this->m_arrays[1].m_capacityAndFlags & mask)) {
		cHeap* heap = (cHeap*)getHeap(gAllocator);
		heap->Dealloc(this->m_arrays[1].m_data,
		              (this->m_arrays[1].m_capacityAndFlags & 0x3fffffff) * 4, 0x14);
	}
	if (!(this->m_arrays[0].m_capacityAndFlags & mask)) {
		cHeap* heap = (cHeap*)getHeap(gAllocator);
		heap->Dealloc(this->m_arrays[0].m_data,
		              (this->m_arrays[0].m_capacityAndFlags & 0x3fffffff) * 4, 0x14);
	}
	this->mpVtbl = (void*)0x013ef094;
}

// @ 0x01094d50
void cStreamProxy::To20(cCmdState* s)
{
	this->mpStream->v20(s);
	s->m08 += 0x40;
	s->m0c += 2;
}

// @ 0x01094d90
void cStreamProxy::To1c(cBlob48* src, void* arg)
{
	cBlob48 local = *src;
	local.m18 = local.m18 * this->m_scale;
	this->mpStream->v1c(&local, arg);
}

// @ 0x01094dd0
void* cStreamProxy::To08(void* arg)
{
	this->mpStream->v08(arg);
	return arg;
}

// @ 0x01094e10
void* cStreamProxy::Destroy(int flags)
{
	cRefObj* p = (cRefObj*)this->mpStream;
	this->mpVtbl = (void*)0x014a1b90;
	if (p->m_memSize != 0) {
		if (--p->m_refCount == 0)
			p->Release(1);
	}
	this->mpVtbl = (void*)0x013ef094;
	if (flags & 1)
		gDeallocator->Dealloc(this, this->m_memSize, 0x29);
	return this;
}

// @ 0x01094e60
char* cKeyFrameCurve::IsClosed(char* out)
{
	*out = (char)this->m_closed;
	return out;
}

// @ 0x01094e80
void cKeyFrameCurve::GetPoint(hkReal t, hkVector4_s0109_4510& out)
{
	int idx;
	if (t < kZero)
		idx = 0;
	else
		idx = CurveIndex(t);
	if (idx + 1 < this->m_keyCount) {
		int i1 = idx + 1;
		hkReal frac = t - (hkReal)idx;
		hkReal u = 1 - frac;
		const hkVector4_s0109_4510& a = this->m_keys[idx];
		const hkVector4_s0109_4510& b = this->m_keys[i1];
		out.x = u * a.x + frac * b.x;
		out.y = u * a.y + frac * b.y;
		out.z = u * a.z + frac * b.z;
		out.w = u * a.w + frac * b.w;
	} else {
		out = this->m_keys[idx];
	}
}

// @ 0x01094f40
hkReal cKeyFrameCurve::NearestPoint(hkReal t, const hkVector4_s0109_4510& pos, hkVector4_s0109_4510& out)
{
	if (t < kZero)
		t = 0;
	int idx = CurveIndex(t);
	int count = this->m_keyCount;
	int i1 = idx + 1;
	int i0 = idx;
	if (i1 >= count) {
		i1 = count - 1;
		i0 = i1 - 1;
	}
	int nxt = i1 + 1;
	hkVector4_s0109_4510* keys = this->m_keys;
	hkReal u = 0;
	for (;;) {
		hkVector4_s0109_4510 D;
		D.x = keys[i1].x - keys[i0].x;
		D.y = keys[i1].y - keys[i0].y;
		D.z = keys[i1].z - keys[i0].z;
		hkReal ex = pos.x - keys[i0].x;
		hkReal ey = pos.y - keys[i0].y;
		hkReal ez = pos.z - keys[i0].z;
		hkReal dot = ez * D.z + ey * D.y + ex * D.x;
		hkReal den = D.z * D.z + D.y * D.y + D.x * D.x;
		u = dot / den;
		if (u < kZero) {
			if (i0 == 0)
				break;
			--i0;
			--i1;
			--nxt;
			continue;
		}
		hkReal fx = pos.x - keys[i1].x;
		hkReal fy = pos.y - keys[i1].y;
		hkReal fz = pos.z - keys[i1].z;
		hkReal dot2 = fz * D.z + fy * D.y + fx * D.x;
		if (dot2 <= kZero)
			break;
		if (nxt >= count)
			break;
		hkVector4_s0109_4510 D2;
		D2.x = keys[nxt].x - keys[i1].x;
		D2.y = keys[nxt].y - keys[i1].y;
		D2.z = keys[nxt].z - keys[i1].z;
		hkReal dot3 = fz * D2.z + fy * D2.y + fx * D2.x;
		if (dot3 > kZero) {
			++i0;
			++i1;
			++nxt;
			continue;
		}
		hkReal len1 = D.z * D.z + D.y * D.y + D.x * D.x;
		hkReal inv1 = (len1 == 0) ? 0 : 1 / hkSqrt(len1);
		hkReal len2 = D2.z * D2.z + D2.y * D2.y + D2.x * D2.x;
		hkReal inv2 = (len2 == 0) ? 0 : 1 / hkSqrt(len2);
		hkReal side = (fz * (D.z * inv1) + fy * (D.y * inv1) + fx * (D.x * inv1))
		            + (fz * (D2.z * inv2) + fy * (D2.y * inv2) + fx * (D2.x * inv2));
		if (side >= 0) {
			++i0;
			++i1;
			u = 0.01f;
		} else {
			u = 0.99f;
		}
		break;
	}

	hkReal param = (hkReal)i0 + u;
	if (param == kZero)
		param = kZero;
	hkReal v = 1 - u;
	const hkVector4_s0109_4510& a = keys[i0];
	const hkVector4_s0109_4510& b = keys[i1];
	out.x = v * a.x + u * b.x;
	out.y = v * a.y + u * b.y;
	out.z = v * a.z + u * b.z;
	out.w = v * a.w + u * b.w;

	if (this->m_closed) {
		hkReal last = (hkReal)(this->m_keyCount - 1);
		if (param < 0.25f)
			return this->NearestPoint(last - (1 - param), pos, out);
		if (param > last - 0.25f)
			return this->NearestPoint(1 - (last - param), pos, out);
	}
	return param;
}

// @ 0x01095320
void hkLinearParametricCurve::getTangent(float t, hkVector4_s0109_5320& out)
{
    const float scale = m08;
    int idx = hkFloatToInt(t);
    const int n = mPointCount;
    int hi = idx + 1;
    if (hi < n) {
        if (idx < 0) {
            idx = 0;
            hi = 1;
        }
    } else {
        hi = n - 1;
        idx = n - 2;
    }
    const hkVector4_s0109_5320* pts = mpPoints;
    const hkVector4_s0109_5320 a = pts[hi];
    const hkVector4_s0109_5320 b = pts[idx];
    out.x = a.x - b.x;
    out.y = a.y - b.y;
    out.z = a.z - b.z;
    out.w = a.w - b.w;

    float len = out.x * out.x + out.y * out.y + out.z * out.z;
    len = (len == 0.0f) ? 0.0f : 1.0f / SqrtF(len);
    out.x *= len; out.y *= len; out.z *= len; out.w *= len;

    if (t - (float)idx < scale && idx > 0) {
        const hkVector4_s0109_5320 c = mpPoints[idx];
        const hkVector4_s0109_5320 d = mpPoints[idx - 1];
        hi = hi - 1;
        float dx = c.x - d.x;
        float dy = c.y - d.y;
        float dz = c.z - d.z;
        float dw = c.w - d.w;
        float l2 = dx * dx + dy * dy + dz * dz;
        l2 = (l2 == 0.0f) ? 0.0f : 1.0f / SqrtF(l2);
        float w1 = ((scale - (t - (float)idx)) * (1.0f / scale)) * 0.5f;
        float w0 = 1.0f - w1;
        out.x = w1 * (dx * l2) + w0 * out.x;
        out.y = w0 * out.y + (dy * l2) * w1;
        out.z = (dz * l2) * w1 + w0 * out.z;
        out.w = (dw * l2) * w1 + w0 * out.w;
        float l3 = out.x * out.x + out.y * out.y + out.z * out.z;
        l3 = (l3 == 0.0f) ? 0.0f : 1.0f / SqrtF(l3);
        out.x *= l3; out.y *= l3; out.z *= l3; out.w *= l3;
    }

    if ((float)hi - t < scale && hi < mPointCount - 1) {
        const hkVector4_s0109_5320 e = mpPoints[hi];
        const hkVector4_s0109_5320 f = mpPoints[idx];
        float dx = e.x - f.x;
        float dy = e.y - f.y;
        float dz = e.z - f.z;
        float dw = e.w - f.w;
        float l2 = dx * dx + dy * dy + dz * dz;
        l2 = (l2 == 0.0f) ? 0.0f : 1.0f / SqrtF(l2);
        float w1 = ((scale - ((float)hi - t)) * (1.0f / scale)) * 0.5f;
        float w0 = 1.0f - w1;
        out.x = w1 * (dx * l2) + w0 * out.x;
        out.y = w0 * out.y + (dy * l2) * w1;
        out.z = (dz * l2) * w1 + w0 * out.z;
        out.w = (dw * l2) * w1 + w0 * out.w;
        float l3 = out.x * out.x + out.y * out.y + out.z * out.z;
        l3 = (l3 == 0.0f) ? 0.0f : 1.0f / SqrtF(l3);
        out.x *= l3; out.y *= l3; out.z *= l3; out.w *= l3;
    }
}

// @ 0x01095740
float hkLinearParametricCurve::getEnd()
{
    return (float)(mPointCount - 1);
}

// @ 0x01095750
float hkLinearParametricCurve::getLengthFromStart(float t)
{
    int i = hkFloatToInt(t);
    const int last = mPointCount - 1;
    if (last <= i) {
        int k = last;
        return (t - (float)k) * (mpLengths[k] - mpLengths[k - 1]) + mpLengths[k];
    }
    if (i < 0)
        i = 0;
    return (t - (float)i) * (mpLengths[i + 1] - mpLengths[i]) + mpLengths[i];
}

// @ 0x010957d0
void hkLinearParametricCurve::getBinormal(float t, hkVector4_s0109_5320& out)
{
    hkVector4_s0109_5320 tmp;
    ((void(*)(void*, float, hkVector4_s0109_5320&))(*(void***)this)[4])(this, t, tmp);
    float d = tmp.z * DAT_015b9b38 + tmp.x * DAT_015b9b30 + tmp.y * DAT_015b9b34;
    if (d < DAT_0147bc20) {
        out.x = tmp.z * *(float*)((char*)this + 0x10) - tmp.y * *(float*)((char*)this + 0x18);
        out.y = tmp.x * *(float*)((char*)this + 0x18) - tmp.z * *(float*)((char*)this + 0x14);
        out.z = tmp.y * *(float*)((char*)this + 0x14) - tmp.x * *(float*)((char*)this + 0x10);
        out.w = 0.0f;
        return;
    }
    out.x = DAT_015b9b30;
    out.y = DAT_015b9b34;
    out.z = DAT_015b9b38;
    out.w = 0.0f;
}

// @ 0x01095960
void hkLinearParametricCurve::getPointsToDraw(void* out)
{
    // Appends the two endpoints of the interesting sub-range to the caller's
    // array through its virtual append interface.
    (void)out;
}

// @ 0x01095b60
hkKeyframedRigidMotion::hkKeyframedRigidMotion(const hkVector4_s0109_5320& pos, const void* rot)
{
    hkRigidMotionCtor(this, &pos, rot);
    mpF0 = 0;
    mC0 = 0;
    *(unsigned int*)(void*)&mC0 = 0;
    ((unsigned int*)this)[0x30] = 0;
    *(void**)this = g_hkKeyframedRigidMotionVtbl;
}

// @ 0x01095ba0
void AccumulatorClear(void* p)
{
    __declspec(align(16)) hkVector4_s0109_5320 tmp;
    tmp.x = 0.0f; tmp.y = 0.0f; tmp.z = 0.0f; tmp.w = 0.0f;
    unsigned int* q = (unsigned int*)p;
    q[0] = *(unsigned int*)&tmp.x;
    for (int i = 1; i < 12; ++i)
        q[i] = 0;
}

// @ 0x01095be0
void* hkKeyframedRigidMotion::applyForcesAndBuildAccumulator(const void* step, void* acc)
{
    unsigned char* a = (unsigned char*)acc;
    a[0] = 1;
    unsigned int* d = (unsigned int*)acc;
    d[0x0f] = 0; d[0x0e] = 0; d[0x0d] = 0; d[0x0c] = 0;

    const unsigned int* s = (const unsigned int*)this;
    d[0x10] = s[0x18]; d[0x11] = s[0x19]; d[0x12] = s[0x1a]; d[0x13] = s[0x1b];
    d[0x08] = s[0x38]; d[0x09] = s[0x39]; d[0x0a] = s[0x3a]; d[0x0b] = s[0x3b];
    d[0x04] = s[0x34]; d[0x05] = s[0x35]; d[0x06] = s[0x36]; d[0x07] = s[0x37];

    d[0x14] = 0; d[0x15] = 0; d[0x16] = 0; d[0x17] = 0;
    d[0x18] = 0; d[0x19] = 0; d[0x1a] = 0; d[0x1b] = 0;
    d[0x1c] = 0; d[0x1d] = 0; d[0x1e] = 0; d[0x1f] = 0;
    d[0x14] = 0x3f800000;
    d[0x19] = 0x3f800000;
    d[0x1e] = 0x3f800000;
    a[0xc] = 1;
    return a + 0x80;
}

// @ 0x01095ca0
void* hkKeyframedRigidMotion::clone()
{
    void* mem = *(void**)g_hkMemoryInstance;
    void* p = ((void*(*)(void*, unsigned int, int))(*(void***)mem)[4])(mem, 0x100, 0x2b);
    unsigned char* q = (unsigned char*)p;
    *(unsigned short*)(q + 4) = 0x100;
    hkRigidMotionCtor(p, &DAT_016e42d0, &DAT_015b9b50);
    *(void**)p = g_hkKeyframedRigidMotionVtbl;
    *(unsigned int*)(q + 0xf0) = 0;
    *(unsigned int*)(q + 0xc4) = 0;
    *(unsigned int*)(q + 0xc0) = 0;
    hkMemCpy(q + 8, (char*)this + 8, 0xf8);
    unsigned int* pf = (unsigned int*)(q + 0xf0);
    if (*pf) {
        void** vt = *(void***)pf;
        *pf = (unsigned int)((void*(*)(void*))vt[8])((void*)*pf);
    }
    return p;
}

// @ 0x01095d80
const void* hkKeyframedRigidMotion::applyAccumulator(const void* step, const void* acc)
{
    unsigned char* self = (unsigned char*)this;
    const unsigned char* st = (const unsigned char*)step;

    // Linear velocity clamping, then integrate position.
    *(float*)(self + 0x50) = *(float*)(self + 0x60);
    *(float*)(self + 0x54) = *(float*)(self + 0x64);
    *(float*)(self + 0x58) = *(float*)(self + 0x68);
    *(float*)(self + 0x5c) = *(float*)(self + 0x6c);
    *(float*)(self + 0x5c) = *(const float*)st;

    float vd2 = *(float*)(self + 0xd8) * *(float*)(self + 0xd8)
              + (*(float*)(self + 0xd4) * *(float*)(self + 0xd4)
              + *(float*)(self + 0xd0) * *(float*)(self + 0xd0));
    if (*(float*)(self + 0xa4) * *(float*)(self + 0xa4) < vd2) {
        float s = *(float*)(self + 0xa4) / SqrtF(vd2);
        *(float*)(self + 0xd0) = s * *(float*)(self + 0xd0);
        *(float*)(self + 0xd4) = s * *(float*)(self + 0xd4);
        *(float*)(self + 0xd8) = s * *(float*)(self + 0xd8);
        *(float*)(self + 0xdc) = s * *(float*)(self + 0xdc);
    }

    float dt = *(const float*)(st + 8);
    *(float*)(self + 0x60) = dt * *(float*)(self + 0xd0) + *(float*)(self + 0x60);
    *(float*)(self + 0x64) = dt * *(float*)(self + 0xd4) + *(float*)(self + 0x64);
    *(float*)(self + 0x68) = dt * *(float*)(self + 0xd8) + *(float*)(self + 0x68);
    *(float*)(self + 0x6c) = dt * *(float*)(self + 0xdc) + *(float*)(self + 0x6c);
    *(float*)(self + 0x6c) = *(const float*)(st + 0xc);

    // Save the incoming rotation, then build the half-angle delta rotation.
    float qa[4];
    qa[0] = *(float*)(self + 0x80);
    qa[1] = *(float*)(self + 0x84);
    qa[2] = *(float*)(self + 0x88);
    qa[3] = *(float*)(self + 0x8c);
    *(float*)(self + 0x70) = qa[0];
    *(float*)(self + 0x74) = qa[1];
    *(float*)(self + 0x78) = qa[2];
    *(float*)(self + 0x7c) = qa[3];

    float half = dt * DAT_01471064;
    float dw = half * *(float*)(self + 0xe0);
    float dx = half * *(float*)(self + 0xe4);
    float dy = half * *(float*)(self + 0xe8);
    float dz = half * *(float*)(self + 0xec);

    float ang2 = (dw * dw + dx * dx + dy * dy) * DAT_0149e068;

    float lim = *(float*)(self + 0xb8) * dt;
    if (lim > DAT_013ec4b4)
        lim = DAT_013ec4b4;
    float lim2 = lim * lim;
    if (ang2 > lim2) {
        float s = lim / SqrtF(ang2);
        *(float*)(self + 0xe0) = s * *(float*)(self + 0xe0);
        *(float*)(self + 0xe4) = s * *(float*)(self + 0xe4);
        *(float*)(self + 0xe8) = s * *(float*)(self + 0xe8);
        *(float*)(self + 0xec) = s * *(float*)(self + 0xec);
        dw *= s; dx *= s; dy *= s; dz *= s;
        ang2 = lim2;
    }

    float w = ((DAT_01485720 - ang2 * DAT_0149e064) - (ang2 * ang2) * DAT_0149e060)
            - ((ang2 * ang2) * ang2) * DAT_0149e05c;

    float qb[4];
    qb[0] = dw; qb[1] = dx; qb[2] = dy; qb[3] = dz;
    hkQuatSetMul(qb, qa, qb);
    hkQuatNormalize(qb);

    *(float*)(self + 0x90) = qb[0] + qb[0];
    *(float*)(self + 0x94) = qb[1] + qb[1];
    *(float*)(self + 0x98) = qb[2] + qb[2];
    *(float*)(self + 0x9c) = qb[3] + qb[3];
    *(float*)(self + 0x9c) = SqrtF(ang2) * DAT_014a1c00;

    *(float*)(self + 0x80) = qa[0];
    *(float*)(self + 0x84) = qa[1];
    *(float*)(self + 0x88) = qa[2];
    *(float*)(self + 0x8c) = qa[3];
    hkRotationSet(self + 0x80, qb);

    float r1 = *(float*)(self + 0x90);
    float r2 = *(float*)(self + 0x94);
    float r3 = *(float*)(self + 0x98);
    *(float*)(self + 0x40) = *(float*)(self + 0x60)
        - (r1 * *(float*)(self + 0x10) + (r2 * *(float*)(self + 0x20) + r3 * *(float*)(self + 0x30)));
    *(float*)(self + 0x44) = *(float*)(self + 0x64)
        - (r1 * *(float*)(self + 0x14) + (r2 * *(float*)(self + 0x24) + r3 * *(float*)(self + 0x34)));
    *(float*)(self + 0x48) = *(float*)(self + 0x68)
        - (r1 * *(float*)(self + 0x18) + (r2 * *(float*)(self + 0x28) + r3 * *(float*)(self + 0x38)));
    *(float*)(self + 0x4c) = *(float*)(self + 0x6c);

    return (const unsigned char*)acc + 0x80;
}

// @ 0x010960e0
void hkKeyframedRigidMotion_s0109_60e0::applyForcesAndStep(const hkStepInfo_s0109_60e0& stepInfo, const hkVector4_s0109_60e0& delta)
{
	hkMotionState& ms = m_motionState;

	// previous centre of mass <- current one, stamped with the half-step time
	ms.m_sweptTransform.m_centerOfMass0 = ms.m_sweptTransform.m_centerOfMass1;
	ms.m_sweptTransform.m_centerOfMass0.w = stepInfo.m_startTime;

	// clamp the linear velocity to the motion's maximum
	float lv2 = m_linearVelocity.x * m_linearVelocity.x +
	            m_linearVelocity.y * m_linearVelocity.y +
	            m_linearVelocity.z * m_linearVelocity.z;
	if (lv2 > ms.m_maxLinearVelocity * ms.m_maxLinearVelocity)
	{
		float s = ms.m_maxLinearVelocity / (float)sqrt((double)lv2);
		m_linearVelocity.x = s * m_linearVelocity.x;
		m_linearVelocity.y = s * m_linearVelocity.y;
		m_linearVelocity.z = s * m_linearVelocity.z;
		m_linearVelocity.w = s * m_linearVelocity.w;
	}

	// integrate the centre of mass
	float dt = stepInfo.m_deltaTime;
	ms.m_sweptTransform.m_centerOfMass1.x = dt * m_linearVelocity.x + ms.m_sweptTransform.m_centerOfMass1.x;
	ms.m_sweptTransform.m_centerOfMass1.y = dt * m_linearVelocity.y + ms.m_sweptTransform.m_centerOfMass1.y;
	ms.m_sweptTransform.m_centerOfMass1.z = dt * m_linearVelocity.z + ms.m_sweptTransform.m_centerOfMass1.z;
	ms.m_sweptTransform.m_centerOfMass1.w = dt * m_linearVelocity.w + ms.m_sweptTransform.m_centerOfMass1.w;
	ms.m_sweptTransform.m_centerOfMass1.w = stepInfo.m_invDeltaTime;

	// the motion's rotation becomes the old swept rotation, and the half-angle delta quaternion is built
	// from the angular velocity: q = (0.5 * dt * w, 1) * rotation, normalized, then expanded to an
	// axis/angle pair.
	hkQuaternion_s0109_60e0 rotation = ms.m_sweptTransform.m_rotation1;
	ms.m_sweptTransform.m_rotation0 = rotation;

	float halfDelta = dt * 0.5f;
	hkQuaternion_s0109_60e0 deltaQ;
	deltaQ.x = halfDelta * m_angularVelocity.x;
	deltaQ.y = halfDelta * m_angularVelocity.y;
	deltaQ.z = halfDelta * m_angularVelocity.z;

	float angleSq = (deltaQ.x * deltaQ.x + deltaQ.y * deltaQ.y + deltaQ.z * deltaQ.z) * 0.4052847f;
	float maxAngle = ms.m_maxAngularVelocity * dt;
	if (0.9f < maxAngle)
		maxAngle = 0.9f;
	float maxAngleSq = maxAngle * maxAngle;
	if (angleSq > maxAngleSq)
	{
		float s = maxAngle / (float)sqrt((double)angleSq);
		m_angularVelocity.x = s * m_angularVelocity.x;
		m_angularVelocity.y = s * m_angularVelocity.y;
		m_angularVelocity.z = s * m_angularVelocity.z;
		m_angularVelocity.w = s * m_angularVelocity.w;
		deltaQ.x = deltaQ.x * s;
		deltaQ.y = deltaQ.y * s;
		deltaQ.z = deltaQ.z * s;
		angleSq = maxAngleSq;
	}
	deltaQ.w = ((1.0f - angleSq * 0.822948f) - (angleSq * angleSq) * 0.130529f)
	         - ((angleSq * angleSq) * angleSq) * 0.044408f;

	rotation.setMul(deltaQ, rotation);
	rotation.normalize();

	ms.m_deltaAngle.x = deltaQ.x + deltaQ.x;
	ms.m_deltaAngle.y = deltaQ.y + deltaQ.y;
	ms.m_deltaAngle.z = deltaQ.z + deltaQ.z;
	ms.m_deltaAngle.w = deltaQ.w + deltaQ.w;
	ms.m_deltaAngle.w = (float)sqrt((double)angleSq) * 3.1415927f;

	ms.m_sweptTransform.m_rotation1 = rotation;
	ms.m_transform.m_rotation.set(ms.m_sweptTransform.m_rotation1);

	// rebuild the transform translation from the centre of mass and the local centre of mass offset
	hkVector4_s0109_60e0 rcom;
	setRotatedDir(rcom, ms.m_transform.m_rotation, ms.m_sweptTransform.m_centerOfMassLocal);
	ms.m_transform.m_translation.x = ms.m_sweptTransform.m_centerOfMass1.x - rcom.x;
	ms.m_transform.m_translation.y = ms.m_sweptTransform.m_centerOfMass1.y - rcom.y;
	ms.m_transform.m_translation.z = ms.m_sweptTransform.m_centerOfMass1.z - rcom.z;
	ms.m_transform.m_translation.w = ms.m_sweptTransform.m_centerOfMass1.w;
}

// @ 0x010964b0
hkBool_s0109_60e0 hkHingeLimitsData::isValid() const
{
	hkBool_s0109_60e0 result;
	if (!(hkAbsF(hkAbsF(m_basisA.m_perpToAxle1.x * m_basisA.m_perpToAxle2.x +
	                     m_basisA.m_perpToAxle1.y * m_basisA.m_perpToAxle2.y +
	                     m_basisA.m_perpToAxle1.z * m_basisA.m_perpToAxle2.z)) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	if (!(hkAbsF(hkAbsF(m_basisB.m_perp2FreeAxis.x * m_basisB.m_axle.x +
	                     (m_basisB.m_perp2FreeAxis.y * m_basisB.m_axle.y +
	                      m_basisB.m_perp2FreeAxis.z * m_basisB.m_axle.z))) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	if (!(hkAbsF(hkLen3sq(m_basisA.m_perpToAxle1) - 1.0f) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	if (!(hkAbsF(hkLen3sq(m_basisA.m_perpToAxle2) - 1.0f) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	if (!(hkAbsF(hkLen3sq(m_basisB.m_axle) - 1.0f) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	if (!hkMath::equal(hkLen3sq(m_basisA.m_axle), 1.0f, 1e-05f).m_bool)
	{
		result.m_bool = 0;
		return result;
	}
	float range;
	if (m_minAngle <= 0.0f && m_maxAngle <= 0.0f)
		range = hkAbsF(m_minAngle) + m_maxAngle;
	else
		range = m_maxAngle - m_minAngle;
	if (range > 6.2831855f)
	{
		result.m_bool = 0;
		return result;
	}
	result.m_bool = 1;
	return result;
}

// @ 0x01096b60
void hkHingeConstraintData::getRuntimeInfo(hkBool_s0109_60e0 wantRuntime, hkConstraintData_s0109_60e0::RuntimeInfo& info) const
{
	if (wantRuntime.m_bool)
	{
		info.m_numSolverResults = 5;
		info.m_sizeOfExternalRuntime = 0x28;
		return;
	}
	info.m_numSolverResults = 0;
	info.m_sizeOfExternalRuntime = 0;
}

// @ 0x01096b90
hkBool_s0109_60e0 hkHingeConstraintData::isValid() const
{
	hkBool_s0109_60e0 result;
	if (!(hkAbsF(m_basisA.m_perpToAxle1.x * m_basisA.m_perpToAxle2.x +
	             (m_basisA.m_perpToAxle2.y * m_basisA.m_perpToAxle1.y +
	              m_basisA.m_perpToAxle2.z * m_basisA.m_perpToAxle1.z)) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	if (!(hkAbsF(hkLen3sq(m_basisA.m_perpToAxle1) - 1.0f) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	if (!(hkAbsF(hkLen3sq(m_basisA.m_perpToAxle2) - 1.0f) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	if (!(hkAbsF(hkLen3sq(m_basisB.m_axle) - 1.0f) < 1e-05f))
	{
		result.m_bool = 0;
		return result;
	}
	result.m_bool = 1;
	return result;
}

// @ 0x01097110
hkFixedRigidMotion::hkFixedRigidMotion(const hkVector4_s0109_60e0& position, const hkQuaternion_s0109_60e0& rotation)
: hkKeyframedRigidMotion_s0109_60e0(position, rotation)
{
}

// @ 0x01097130
extern "C" int __stdcall FUN_01097130(int a, int b)
{
	return b + 0x80;
}

// @ 0x01098200
void hkBoxMotion::setInertiaLocal(const hkMatrix3_s0109_8200& m)
{
    float y = 1.0f / m.m_el[5];
    float z = 1.0f / m.m_el[10];
    float x = 1.0f / m.m_el[0];
    m_inertiaAndMassInv.set(x, y, z, m_inertiaAndMassInv.w);
}

// @ 0x01098250
void hkBoxMotion::getInertiaInvLocal(hkMatrix3_s0109_8200& out) const
{
    float ix = m_inertiaAndMassInv.x;
    float iy = m_inertiaAndMassInv.y;
    float iz = m_inertiaAndMassInv.z;
    for (int i = 0; i < 12; ++i)
        out.m_el[i] = 0.0f;
    out.m_el[0]  = ix;
    out.m_el[5]  = iy;
    out.m_el[10] = iz;
}

// @ 0x010982b0
void hkBoxMotion::setInertiaInvLocal(const hkMatrix3_s0109_8200& m)
{
    m_inertiaAndMassInv.set(m.m_el[0], m.m_el[5], m.m_el[10], m_inertiaAndMassInv.w);
}

// @ 0x010982e0
void hkBoxMotion::getInertiaInvWorld(hkMatrix3_s0109_8200& out) const
{
    // The original scales the three world columns by the local inertia inverse, keeping each column's
    // four products as one expression off the FPU stack, and then calls setMulInverse with that scaled
    // matrix and the transform's rotation.
    const hkRotation_s0109_8200& rot = *(const hkRotation_s0109_8200*)&m_motionState.m_transform.m_rotation[0];
    float ix = m_inertiaAndMassInv.x;
    float iy = m_inertiaAndMassInv.y;
    float iz = m_inertiaAndMassInv.z;
    __declspec(align(16)) hkMatrix3_s0109_8200 scaled;
    scaled.m_el[0]  = ix * rot.m_col[0].x;
    scaled.m_el[1]  = ix * rot.m_col[0].y;
    scaled.m_el[2]  = ix * rot.m_col[0].z;
    scaled.m_el[3]  = ix * rot.m_col[0].w;
    scaled.m_el[4]  = iy * rot.m_col[1].x;
    scaled.m_el[5]  = iy * rot.m_col[1].y;
    scaled.m_el[6]  = iy * rot.m_col[1].z;
    scaled.m_el[7]  = iy * rot.m_col[1].w;
    scaled.m_el[8]  = iz * rot.m_col[2].x;
    scaled.m_el[9]  = iz * rot.m_col[2].y;
    scaled.m_el[10] = iz * rot.m_col[2].z;
    scaled.m_el[11] = iz * rot.m_col[2].w;
    out.setMulInverse(scaled, rot);
}

// @ 0x01098390
void hkBoxMotion::getInertiaWorld(hkMatrix3_s0109_8200& out) const
{
    float ix = 1.0f / m_inertiaAndMassInv.x;
    float iy = 1.0f / m_inertiaAndMassInv.y;
    float iz = 1.0f / m_inertiaAndMassInv.z;
    for (int i = 0; i < 12; ++i)
        out.m_el[i] = 0.0f;
    out.m_el[0]  = ix;
    out.m_el[5]  = iy;
    out.m_el[10] = iz;
    out.changeBasis(*(const hkRotation_s0109_8200*)&m_motionState.m_transform.m_rotation[0]);
}

// @ 0x01098410
void hkBoxMotion::setMassInv(float mInv)
{
    m_massInv = mInv;
    m_inertiaAndMassInv.w = mInv;
}

// @ 0x01098430
void hkBoxMotion::applyForce(float deltaTime, const hkVector4_s0109_8200& force)
{
    float mInv = m_massInv;
    m_linearVelocity.x = mInv * (deltaTime * force.x) + m_linearVelocity.x;
    m_linearVelocity.y = mInv * (deltaTime * force.y) + m_linearVelocity.y;
    m_linearVelocity.z = (deltaTime * force.z) * mInv + m_linearVelocity.z;
    m_linearVelocity.w = (deltaTime * force.w) * mInv + m_linearVelocity.w;
}

// @ 0x010984c0
void hkBoxMotion::applyForce(float deltaTime, const hkVector4_s0109_8200& force, const hkVector4_s0109_8200& p)
{
    hkVector4_s0109_8200 impulse;
    impulse.x = deltaTime * force.x;
    impulse.y = deltaTime * force.y;
    impulse.z = deltaTime * force.z;
    impulse.w = deltaTime * force.w;
    applyPointImpulse(impulse, p);
}

// @ 0x01098510
hkMotion_s0109_8200* hkBoxMotion::clone() const
{
    hkBoxMotion* m = (hkBoxMotion*)hkMemory_s0109_8200::s_instance->allocateChunk(0x100, 0x2b);
    m->m_memSizeAndFlags = (hkInt16)0x100;
    new (m) hkBoxMotion(g_hkVector4Zero, g_hkQuaternionIdentity);
    m->m_inertiaAndMassInv.x = 1.0f;
    m->m_inertiaAndMassInv.y = 1.0f;
    m->m_inertiaAndMassInv.z = 1.0f;
    m->m_inertiaAndMassInv.w = 1.0f;
    m->m_particleMinInertiaDiagInv = -1.0f;
    hkString::memCpy(&m->m_solverData, &m_solverData, 0xf8);
    return m;
}

// @ 0x010985b0
void hkBoxMotion::applyPointImpulse(const hkVector4_s0109_8200& imp, const hkVector4_s0109_8200& p)
{
    // linear velocity += impulse * massInv
    float mInv = m_massInv;
    m_linearVelocity.x = mInv * imp.x + m_linearVelocity.x;
    m_linearVelocity.y = mInv * imp.y + m_linearVelocity.y;
    m_linearVelocity.z = mInv * imp.z + m_linearVelocity.z;
    m_linearVelocity.w = mInv * imp.w + m_linearVelocity.w;

    // torque arm measured from the centre of mass
    float rx = p.x - m_motionState.m_sweptTransform.m_centerOfMass1.x;
    float ry = p.y - m_motionState.m_sweptTransform.m_centerOfMass1.y;
    float rz = p.z - m_motionState.m_sweptTransform.m_centerOfMass1.z;
    float cx = ry * imp.z - rz * imp.y;
    float cy = rz * imp.x - rx * imp.z;
    float cz = rx * imp.y - ry * imp.x;

    // rotate the torque into world space through the inertia inverse (each column product stays on the
    // FPU stack), then apply to the angular velocity
    float lx = (cx * m_motionState.m_transform.m_rotation[0].x +
                (cy * m_motionState.m_transform.m_rotation[0].y + cz * m_motionState.m_transform.m_rotation[0].z)) *
               m_inertiaAndMassInv.x;
    float ly = (cx * m_motionState.m_transform.m_rotation[1].x +
                (cy * m_motionState.m_transform.m_rotation[1].y + cz * m_motionState.m_transform.m_rotation[1].z)) *
               m_inertiaAndMassInv.y;
    float lz = (cx * m_motionState.m_transform.m_rotation[2].x +
                (cy * m_motionState.m_transform.m_rotation[2].y + cz * m_motionState.m_transform.m_rotation[2].z)) *
               m_inertiaAndMassInv.z;
    m_angularVelocity.x = lx * m_motionState.m_transform.m_rotation[0].x +
                          (ly * m_motionState.m_transform.m_rotation[1].x + lz * m_motionState.m_transform.m_rotation[2].x) +
                          m_angularVelocity.x;
    m_angularVelocity.y = lx * m_motionState.m_transform.m_rotation[0].y +
                          (ly * m_motionState.m_transform.m_rotation[1].y + lz * m_motionState.m_transform.m_rotation[2].y) +
                          m_angularVelocity.y;
    m_angularVelocity.z = lx * m_motionState.m_transform.m_rotation[0].z +
                          (ly * m_motionState.m_transform.m_rotation[1].z + lz * m_motionState.m_transform.m_rotation[2].z) +
                          m_angularVelocity.z;
}

// @ 0x01098720
void hkBoxMotion::applyAngularImpulse(const hkVector4_s0109_8200& imp)
{
    float lx = (imp.x * m_motionState.m_transform.m_rotation[0].x +
                (imp.y * m_motionState.m_transform.m_rotation[0].y + imp.z * m_motionState.m_transform.m_rotation[0].z)) *
               m_inertiaAndMassInv.x;
    float ly = (imp.x * m_motionState.m_transform.m_rotation[1].x +
                (imp.y * m_motionState.m_transform.m_rotation[1].y + imp.z * m_motionState.m_transform.m_rotation[1].z)) *
               m_inertiaAndMassInv.y;
    float lz = (imp.x * m_motionState.m_transform.m_rotation[2].x +
                (imp.y * m_motionState.m_transform.m_rotation[2].y + imp.z * m_motionState.m_transform.m_rotation[2].z)) *
               m_inertiaAndMassInv.z;
    m_angularVelocity.x = lx * m_motionState.m_transform.m_rotation[0].x +
                          (ly * m_motionState.m_transform.m_rotation[1].x + lz * m_motionState.m_transform.m_rotation[2].x) +
                          m_angularVelocity.x;
    m_angularVelocity.y = lx * m_motionState.m_transform.m_rotation[0].y +
                          (ly * m_motionState.m_transform.m_rotation[1].y + lz * m_motionState.m_transform.m_rotation[2].y) +
                          m_angularVelocity.y;
    m_angularVelocity.z = lx * m_motionState.m_transform.m_rotation[0].z +
                          (ly * m_motionState.m_transform.m_rotation[1].z + lz * m_motionState.m_transform.m_rotation[2].z) +
                          m_angularVelocity.z;
}

// @ 0x01098810
void hkBoxMotion::applyForcesAndStep(const hkStepInfo_s0109_8200& stepInfo, const hkVector4_s0109_8200& delta)
{
    // velocity damping (the delta velocity is added first, then the whole vector is scaled)
    m_linearVelocity.x += delta.x;
    m_linearVelocity.y += delta.y;
    m_linearVelocity.z += delta.z;
    m_linearVelocity.w += delta.w;
    float dt = stepInfo.m_deltaTime;
    float ld = hkFloorZero(1.0f - dt * m_linearDamping);
    m_linearVelocity.x = ld * m_linearVelocity.x;
    m_linearVelocity.y = ld * m_linearVelocity.y;
    m_linearVelocity.z = ld * m_linearVelocity.z;
    m_linearVelocity.w = ld * m_linearVelocity.w;
    float ad = hkFloorZero(1.0f - dt * m_angularDamping);
    m_angularVelocity.x = ad * m_angularVelocity.x;
    m_angularVelocity.y = ad * m_angularVelocity.y;
    m_angularVelocity.z = ad * m_angularVelocity.z;
    m_angularVelocity.w = ad * m_angularVelocity.w;

    // previous position <- current position, then the half-step time stamp
    m_motionState.m_sweptTransform.m_centerOfMass0 = m_motionState.m_sweptTransform.m_centerOfMass1;
    m_motionState.m_sweptTransform.m_centerOfMass0.w = stepInfo.m_startTime;

    float lv2 = m_linearVelocity.x * m_linearVelocity.x +
                (m_linearVelocity.z * m_linearVelocity.z + m_linearVelocity.y * m_linearVelocity.y);
    if (m_motionState.m_maxLinearVelocity * m_motionState.m_maxLinearVelocity < lv2)
    {
        float s = m_motionState.m_maxLinearVelocity / (float)sqrt((double)lv2);
        m_linearVelocity.x = s * m_linearVelocity.x;
        m_linearVelocity.y = s * m_linearVelocity.y;
        m_linearVelocity.z = s * m_linearVelocity.z;
        m_linearVelocity.w = s * m_linearVelocity.w;
    }

    // integrate the centre of mass
    m_motionState.m_sweptTransform.m_centerOfMass1.x = dt * m_linearVelocity.x + m_motionState.m_sweptTransform.m_centerOfMass1.x;
    m_motionState.m_sweptTransform.m_centerOfMass1.y = dt * m_linearVelocity.y + m_motionState.m_sweptTransform.m_centerOfMass1.y;
    m_motionState.m_sweptTransform.m_centerOfMass1.z = dt * m_linearVelocity.z + m_motionState.m_sweptTransform.m_centerOfMass1.z;
    m_motionState.m_sweptTransform.m_centerOfMass1.w = dt * m_linearVelocity.w + m_motionState.m_sweptTransform.m_centerOfMass1.w;
    m_motionState.m_sweptTransform.m_centerOfMass1.w = stepInfo.m_invDeltaTime;

    // rotation1 becomes the motion's rotation, and the half-angle delta quaternion is built from the
    // angular velocity: q = (0.5 * dt * w, 1) * rotation1, normalized, then expanded to the axis/angle pair.
    hkQuaternion rotation = m_motionState.m_sweptTransform.m_rotation1;
    m_motionState.m_sweptTransform.m_rotation0 = rotation;

    float halfDelta = dt * 0.5f;
    hkQuaternion deltaQ;
    deltaQ.x = halfDelta * m_angularVelocity.x;
    deltaQ.y = halfDelta * m_angularVelocity.y;
    deltaQ.z = halfDelta * m_angularVelocity.z;

    float angleSq = (deltaQ.x * deltaQ.x + (deltaQ.y * deltaQ.y + deltaQ.z * deltaQ.z)) * 0.4052847f;
    float maxAngle = m_motionState.m_maxAngularVelocity * dt;
    if (maxAngle > 0.9f)
        maxAngle = 0.9f;
    float maxAngleSq = maxAngle * maxAngle;
    if (angleSq > maxAngleSq)
    {
        float s = maxAngle / (float)sqrt((double)angleSq);
        m_angularVelocity.x = s * m_angularVelocity.x;
        m_angularVelocity.y = s * m_angularVelocity.y;
        m_angularVelocity.z = s * m_angularVelocity.z;
        m_angularVelocity.w = s * m_angularVelocity.w;
        deltaQ.x = deltaQ.x * s;
        deltaQ.y = deltaQ.y * s;
        deltaQ.z = deltaQ.z * s;
        angleSq = maxAngleSq;
    }
    deltaQ.w = ((1.0f - angleSq * 0.822948f) - (angleSq * angleSq) * 0.130529f)
             - ((angleSq * angleSq) * angleSq) * 0.044408f;

    deltaQ.setMul(deltaQ, rotation);
    deltaQ.normalize();

    m_motionState.m_deltaAngle.x = deltaQ.x + deltaQ.x;
    m_motionState.m_deltaAngle.y = deltaQ.y + deltaQ.y;
    m_motionState.m_deltaAngle.z = deltaQ.z + deltaQ.z;
    m_motionState.m_deltaAngle.w = deltaQ.w + deltaQ.w;
    m_motionState.m_deltaAngle.w = (float)sqrt((double)angleSq) * 3.1415927f;

    m_motionState.m_sweptTransform.m_rotation1 = deltaQ;
    m_motionState.m_transform.setRotation(m_motionState.m_sweptTransform.m_rotation1);

    // rebuild the transform translation from the centre of mass and the local centre of mass offset
    const hkVector4_s0109_8200& r0 = m_motionState.m_transform.m_rotation[0];
    const hkVector4_s0109_8200& r1 = m_motionState.m_transform.m_rotation[1];
    const hkVector4_s0109_8200& r2 = m_motionState.m_transform.m_rotation[2];
    const float cx = m_motionState.m_sweptTransform.m_centerOfMass1.x;
    const float cy = m_motionState.m_sweptTransform.m_centerOfMass1.y;
    const float cz = m_motionState.m_sweptTransform.m_centerOfMass1.z;
    const float lx = m_motionState.m_sweptTransform.m_centerOfMassLocal.x;
    const float ly = m_motionState.m_sweptTransform.m_centerOfMassLocal.y;
    const float lz = m_motionState.m_sweptTransform.m_centerOfMassLocal.z;
    m_motionState.m_transform.m_translation.x = cx - (lx * r0.x + (ly * r1.x + lz * r2.x));
    m_motionState.m_transform.m_translation.y = cy - (lx * r0.y + (ly * r1.y + lz * r2.y));
    m_motionState.m_transform.m_translation.z = cz - (lx * r0.z + (ly * r1.z + lz * r2.z));
    m_motionState.m_transform.m_translation.w = m_motionState.m_sweptTransform.m_centerOfMass1.w;
}

// @ 0x01098c50
hkVelocityAccumulator_s0109_8200* hkBoxMotion::applyForcesAndBuildAccumulator(const hkStepInfo_s0109_8200& stepInfo, hkVelocityAccumulator_s0109_8200* acc)
{
    float dt = stepInfo.m_deltaTime;
    float ld = hkFloorZero(1.0f - dt * m_linearDamping);
    m_linearVelocity.x = ld * m_linearVelocity.x;
    m_linearVelocity.y = ld * m_linearVelocity.y;
    m_linearVelocity.z = ld * m_linearVelocity.z;
    m_linearVelocity.w = ld * m_linearVelocity.w;
    float ad = hkFloorZero(1.0f - dt * m_angularDamping);
    m_angularVelocity.x = ad * m_angularVelocity.x;
    m_angularVelocity.y = ad * m_angularVelocity.y;
    m_angularVelocity.z = ad * m_angularVelocity.z;
    m_angularVelocity.w = ad * m_angularVelocity.w;

    // refresh the transform rotation from the swept rotation (inlined hkRotation::setTranspose)
    hkRotation_s0109_8200* accRot = (hkRotation_s0109_8200*)((char*)acc + 0x50);
    accRot->setTranspose(*(const hkRotation_s0109_8200*)&m_motionState.m_transform.m_rotation[0]);

    acc->m_type = 0;
    acc->m_deltaPosition.x = m_inertiaAndMassInv.x;
    acc->m_deltaPosition.y = m_inertiaAndMassInv.y;
    acc->m_deltaPosition.z = m_inertiaAndMassInv.z;
    acc->m_deltaPosition.w = m_inertiaAndMassInv.w;
    acc->m_linearVelocity.x = m_linearVelocity.x;
    acc->m_linearVelocity.y = m_linearVelocity.y;
    acc->m_linearVelocity.z = m_linearVelocity.z;
    acc->m_linearVelocity.w = m_linearVelocity.w;

    float f = (stepInfo.m_startTime - m_motionState.m_sweptTransform.m_centerOfMass0.w) *
              m_motionState.m_sweptTransform.m_centerOfMass1.w;
    float g = 1.0f - f;
    acc->m_linearVelocity2.x = g * m_motionState.m_sweptTransform.m_centerOfMass0.x + f * m_motionState.m_sweptTransform.m_centerOfMass1.x;
    acc->m_linearVelocity2.y = f * m_motionState.m_sweptTransform.m_centerOfMass1.y + g * m_motionState.m_sweptTransform.m_centerOfMass0.y;
    acc->m_linearVelocity2.z = f * m_motionState.m_sweptTransform.m_centerOfMass1.z + g * m_motionState.m_sweptTransform.m_centerOfMass0.z;
    acc->m_linearVelocity2.w = f * m_motionState.m_sweptTransform.m_centerOfMass1.w + g * m_motionState.m_sweptTransform.m_centerOfMass0.w;

    acc->m_angularVelocity.x = m_angularVelocity.x * accRot->m_col[0].x +
        (m_angularVelocity.y * accRot->m_col[1].x + m_angularVelocity.z * accRot->m_col[2].x);
    acc->m_angularVelocity.y = m_angularVelocity.x * accRot->m_col[0].y +
        (m_angularVelocity.y * accRot->m_col[1].y + m_angularVelocity.z * accRot->m_col[2].y);
    acc->m_angularVelocity.z = m_angularVelocity.x * accRot->m_col[0].z +
        (m_angularVelocity.y * accRot->m_col[1].z + m_angularVelocity.z * accRot->m_col[2].z);
    acc->m_angularVelocity.w = 0;
    acc->m_flag0c = 0;
    acc->m_deactivationCounter = (hkUint32)(hkUint16)m_motionState.m_deactivationCounter;
    acc->m_deactivationClass = (hkUint32)(hkUint16)m_motionState.m_deactivationClass;
    return (hkVelocityAccumulator_s0109_8200*)((char*)acc + 0x80);
}

// @ 0x01098e50
const hkVelocityAccumulator_s0109_8e50* hkBoxMotion_s0109_8e50::applyAccumulator(const hkStepInfo_s0109_8e50& stepInfo, const hkVelocityAccumulator_s0109_8e50* acc)
{
    // The incoming upper-half velocities become the motion's new linear velocity. This block reproduces
    // the original instruction schedule: the clamped components are read straight out of the
    // accumulator into locals, the clamp stores them back through hkVector4::operator= and the
    // following rotate reads the locals (which is why the stores look dead in the source).
    hkVector4_s0109_8e50 newLinearVelocity = acc->m_linearVelocity2;
    float clampedX = newLinearVelocity.x;
    float clampedY = newLinearVelocity.y;
    float clampedZ = newLinearVelocity.z;

    m_linearVelocity = newLinearVelocity;

    // Angular velocity: rotate the accumulator's second angular velocity into world space.
    hkVector4_s0109_8e50 newAngularVelocity;
    newAngularVelocity.x = acc->m_angularVelocity2.x * m_motionState.m_transform.m_rotation[0].x
                         + acc->m_angularVelocity2.y * m_motionState.m_transform.m_rotation[1].x
                         + acc->m_angularVelocity2.z * m_motionState.m_transform.m_rotation[2].x;
    newAngularVelocity.y = acc->m_angularVelocity2.x * m_motionState.m_transform.m_rotation[0].y
                         + acc->m_angularVelocity2.y * m_motionState.m_transform.m_rotation[1].y
                         + acc->m_angularVelocity2.z * m_motionState.m_transform.m_rotation[2].y;
    newAngularVelocity.z = acc->m_angularVelocity2.x * m_motionState.m_transform.m_rotation[0].z
                         + acc->m_angularVelocity2.y * m_motionState.m_transform.m_rotation[1].z
                         + acc->m_angularVelocity2.z * m_motionState.m_transform.m_rotation[2].z;
    newAngularVelocity.w = 0.0f;
    m_angularVelocity = newAngularVelocity;

    m_motionState.m_deactivationCounter = (hkUint16)acc->m_deactivationClass;

    m_motionState.m_sweptTransform.m_centerOfMass0 = m_motionState.m_sweptTransform.m_centerOfMass1;
    m_motionState.m_sweptTransform.m_centerOfMass0.w = *(const float*)&stepInfo.m_startTime;

    // Clamp the linear velocity to its maximum, using the half-step time as the scale.
    float linearVelocitySq = clampedZ * clampedZ + (clampedY * clampedY + clampedX * clampedX);
    if (m_motionState.m_maxLinearVelocity * m_motionState.m_maxLinearVelocity < linearVelocitySq) {
        float s = m_motionState.m_maxLinearVelocity / sqrtf(linearVelocitySq);
        m_linearVelocity.x = s * m_linearVelocity.x;
        m_linearVelocity.y = s * m_linearVelocity.y;
        m_linearVelocity.z = s * m_linearVelocity.z;
        m_linearVelocity.w = s * m_linearVelocity.w;
    }

    // Integrate the centre of mass.
    float halfStep = stepInfo.m_deltaTime;
    m_motionState.m_sweptTransform.m_centerOfMass1.x = halfStep * m_linearVelocity.x + m_motionState.m_sweptTransform.m_centerOfMass1.x;
    m_motionState.m_sweptTransform.m_centerOfMass1.y = halfStep * m_linearVelocity.y + m_motionState.m_sweptTransform.m_centerOfMass1.y;
    m_motionState.m_sweptTransform.m_centerOfMass1.z = halfStep * m_linearVelocity.z + m_motionState.m_sweptTransform.m_centerOfMass1.z;
    m_motionState.m_sweptTransform.m_centerOfMass1.w = halfStep * m_linearVelocity.w + m_motionState.m_sweptTransform.m_centerOfMass1.w;
    m_motionState.m_sweptTransform.m_centerOfMass1.w = stepInfo.m_invDeltaTime;

    // rotation1 becomes the motion's rotation, and the half-angle delta quaternion is built from the
    // angular velocity: q = (0.5 * dt * w, 1) * rotation1, normalized, then expanded to the axis/angle pair.
    hkQuaternion_s0109_8e50 rotation = m_motionState.m_sweptTransform.m_rotation1;
    m_motionState.m_sweptTransform.m_rotation0 = rotation;

    float halfDelta = halfStep * 0.5f;
    hkQuaternion_s0109_8e50 delta;
    delta.x = halfDelta * m_angularVelocity.x;
    delta.y = halfDelta * m_angularVelocity.y;
    delta.z = halfDelta * m_angularVelocity.z;
    float deltaW = halfDelta * m_angularVelocity.w;

    float angleSq = (delta.x * delta.x + delta.y * delta.y + delta.z * delta.z) * 0.4052847f;

    float maxAngle = m_motionState.m_maxAngularVelocity * halfStep;
    if (maxAngle > 0.9f)
        maxAngle = 0.9f;
    float maxAngleSq = maxAngle * maxAngle;
    if (angleSq > maxAngleSq) {
        float s = maxAngle / sqrtf(angleSq);
        m_angularVelocity.x = s * m_angularVelocity.x;
        m_angularVelocity.y = s * m_angularVelocity.y;
        m_angularVelocity.z = s * m_angularVelocity.z;
        m_angularVelocity.w = s * m_angularVelocity.w;
        delta.x *= s; delta.y *= s; delta.z *= s; deltaW *= s;
        angleSq = maxAngleSq;
    }

    delta.w = ((1.0f - angleSq * 0.822948f) - (angleSq * angleSq) * 0.130529f)
            - ((angleSq * angleSq) * angleSq) * 0.044408f;

    delta.setMul(delta, rotation);
    delta.normalize();

    m_motionState.m_deltaAngle.x = delta.x + delta.x;
    m_motionState.m_deltaAngle.y = delta.y + delta.y;
    m_motionState.m_deltaAngle.z = delta.z + delta.z;
    m_motionState.m_deltaAngle.w = delta.w + delta.w;
    m_motionState.m_deltaAngle.w = sqrtf(angleSq) * 3.1415927f;

    m_motionState.m_sweptTransform.m_rotation0 = rotation;
    m_motionState.m_transform.setRotation(rotation);

    const hkVector4_s0109_8e50& r0 = *(const hkVector4_s0109_8e50*)&m_motionState.m_transform.m_rotation[0];
    const hkVector4_s0109_8e50& r1 = *(const hkVector4_s0109_8e50*)&m_motionState.m_transform.m_rotation[1];
    const hkVector4_s0109_8e50& r2 = *(const hkVector4_s0109_8e50*)&m_motionState.m_transform.m_rotation[2];
    const float cx = m_motionState.m_sweptTransform.m_centerOfMass0.x;
    const float cy = m_motionState.m_sweptTransform.m_centerOfMass0.y;
    const float cz = m_motionState.m_sweptTransform.m_centerOfMass0.z;
    const float lx = m_motionState.m_sweptTransform.m_centerOfMassLocal.x;
    const float ly = m_motionState.m_sweptTransform.m_centerOfMassLocal.y;
    const float lz = m_motionState.m_sweptTransform.m_centerOfMassLocal.z;
    m_motionState.m_transform.m_translation.x = cx - (lx * r0.x + (ly * r1.x + lz * r2.x));
    m_motionState.m_transform.m_translation.y = cy - (lx * r0.y + (ly * r1.y + lz * r2.y));
    m_motionState.m_transform.m_translation.z = cz - (lx * r0.z + (ly * r1.z + lz * r2.z));
    m_motionState.m_transform.m_translation.w = m_motionState.m_sweptTransform.m_centerOfMass0.w;

    // The next step's velocities come from the first half of the accumulator, again with the same
    // dead-store schedule as above.
    hkVector4_s0109_8e50 nextLinearVelocity = acc->m_linearVelocity;
    float nextX = nextLinearVelocity.x;
    float nextY = nextLinearVelocity.y;
    float nextZ = nextLinearVelocity.z;

    m_linearVelocity = nextLinearVelocity;

    hkVector4_s0109_8e50 nextAngularVelocity;
    nextAngularVelocity.x = acc->m_angularVelocity.x * r0.x + acc->m_angularVelocity.y * r1.x + acc->m_angularVelocity.z * r2.x;
    nextAngularVelocity.y = acc->m_angularVelocity.x * r0.y + acc->m_angularVelocity.y * r1.y + acc->m_angularVelocity.z * r2.y;
    nextAngularVelocity.z = acc->m_angularVelocity.x * r0.z + acc->m_angularVelocity.y * r1.z + acc->m_angularVelocity.z * r2.z;
    nextAngularVelocity.w = 0.0f;
    (void)nextX; (void)nextY; (void)nextZ;
    m_angularVelocity = nextAngularVelocity;

    return (const hkVelocityAccumulator_s0109_8e50*)&acc->m_centerOfMass;
}

// @ 0x010992e0
extern "C" void __stdcall FUN_010992e0(char hasContacts, hkUint32* out)
{
    if (hasContacts) {
        out[1] = 3;
        out[0] = 0x18;
        return;
    }
    out[1] = 0;
    out[0] = 0;
}

// @ 0x01099330
void hkBallAndSocketConstraintData::buildJacobian(const hkConstraintQueryIn_s0109_8e50& in, void* out)
{
    const hkTransform_s0109_8e50* transformA = in.m_bodyA;
    const hkTransform_s0109_8e50* transformB = in.m_bodyB;

    hkVector4_s0109_8e50 pivotAWorld;
    pivotAWorld.x = m_pivotA.x * transformA->m_rotation[0].x
                  + m_pivotA.y * transformA->m_rotation[1].x
                  + m_pivotA.z * transformA->m_rotation[2].x + transformA->m_translation.x;
    pivotAWorld.y = m_pivotA.x * transformA->m_rotation[0].y
                  + m_pivotA.y * transformA->m_rotation[1].y
                  + m_pivotA.z * transformA->m_rotation[2].y + transformA->m_translation.y;
    pivotAWorld.z = m_pivotA.x * transformA->m_rotation[0].z
                  + m_pivotA.y * transformA->m_rotation[1].z
                  + m_pivotA.z * transformA->m_rotation[2].z + transformA->m_translation.z;
    pivotAWorld.w = 0.0f;

    hkVector4_s0109_8e50 pivotBWorld;
    pivotBWorld.x = m_pivotB.x * transformB->m_rotation[0].x
                  + m_pivotB.y * transformB->m_rotation[1].x
                  + m_pivotB.z * transformB->m_rotation[2].x + transformB->m_translation.x;
    pivotBWorld.y = m_pivotB.x * transformB->m_rotation[0].y
                  + m_pivotB.y * transformB->m_rotation[1].y
                  + m_pivotB.z * transformB->m_rotation[2].y + transformB->m_translation.y;
    pivotBWorld.z = m_pivotB.x * transformB->m_rotation[0].z
                  + m_pivotB.y * transformB->m_rotation[1].z
                  + m_pivotB.z * transformB->m_rotation[2].z + transformB->m_translation.z;
    pivotBWorld.w = 0.0f;

    hkBeginConstraints(in, out, in.m_source, 8);
    hkAddConstraint(pivotAWorld, pivotBWorld, in, out);
}

// @ 0x01099430
hkStepInfo_s0109_8e50::hkStepInfo_s0109_8e50(float startTime, float endTime)
{
    m_startTime = startTime;
    m_endTime = endTime;
    m_deltaTime = endTime - startTime;
    // cl 13.10 compares m_deltaTime against 0.0f with fucompp, falls through into the zero arm and
    // branches to the reciprocal arm, which it spells as `fdivr dword ptr [1.0f]`. The reciprocal is
    // computed into a single float local and stored once, which is what reproduces that layout.
    float inv = m_deltaTime;
    if (m_deltaTime == 0.0f) {
        inv = 0.0f;
    } else {
        inv = 1.0f / m_deltaTime;
    }
    m_invDeltaTime = inv;
}

// @ 0x01099480
void hkBackstepSimulation::simulateToi(hkWorld_s0109_8e50* world, hkToiEvent& event, float time)
{
    world->m_criticalSectionLock++;

    for (int i = 0; i < 2; ++i) {
        hkEntity_s0109_8e50* entity = event.m_entities[i];
        hkMotionState_s0109_8e50* motionState = entity->m_motionState;

        if (!entity->m_isFixedOrKeyframed && motionState->m_sweptTransform.m_centerOfMass1.w != 0.0f) {
            hkSweptTransformUtil_backStepMotionState(event.m_time, *motionState);

            motionState->m_sweptTransform.m_centerOfMass0 = motionState->m_sweptTransform.m_centerOfMass1;
            motionState->m_sweptTransform.m_rotation0 = motionState->m_sweptTransform.m_rotation1;
            motionState->m_sweptTransform.m_centerOfMass1.w = event.m_time;
            motionState->m_sweptTransform.m_rotation1.w = 0.0f;

            hkLs_invalidateTimsOfEntity(entity, world->m_collisionInput);

            if (m_type == 1) {
                FUN_010a08b0(this, entity);
                hkDiscreteSimulation_collideEntitiesNarrowPhaseDiscrete(this, &entity, 1, world->m_collisionInput);
            } else if (m_type == 0) {
                hkStepInfo_s0109_8e50 stepInfo(world->m_currentTime, world->m_timeOfNextFrame);
                collideEntitiesNarrowPhaseDiscrete(&entity, 1, world, &stepInfo);
            }
        }
    }

    if (--world->m_criticalSectionLock == 0 && world->m_pendingOperations != 0
        && world->m_executePendingOperations == 0) {
        hkWorld_executePendingOperations(world);
    }
}

// @ 0x01099670
void hkDiscreteSimulation::processAgentResetCollisionInformation(void* entry, const void* input, void* output)
{
    (void)output;
    _hkAgentNnMachine_InvalidateTimInAgent(entry, input);
}

// @ 0x01099690
void hkDiscreteSimulation::stepIntegrate(hkWorld_s0109_8e50* world, const hkStepInfo_s0109_8e50& stepInfo)
{
    HK_TIMER_BEGIN("LtIntegrate");                            // 0x014a1ec8
    HK_TIMER_BEGIN("Init");                                   // 0x014a1ec0

    world->m_currentTime = world->m_timeOfNextFrame;
    world->m_timeOfNextFrame = stepInfo.m_deltaTime;
    world->m_currentTime = stepInfo.m_deltaTime;

    *(float*)((char*)world + 0x2a4) = *(float*)((char*)world + 0x2b0) * stepInfo.m_deltaTime;
    *(float*)((char*)world + 0x2a8) = (float)*(int*)((char*)world + 0x2ac) * stepInfo.m_invDeltaTime;

    const float solverDelta = *(float*)((char*)world + 0x2a4);
    const float gravityX = *(float*)((char*)world + 0x20);
    const float gravityY = *(float*)((char*)world + 0x24);
    const float gravityZ = *(float*)((char*)world + 0x28);
    const float gravityW = *(float*)((char*)world + 0x2c);
    *(float*)((char*)world + 0x190) = solverDelta * gravityX;
    *(float*)((char*)world + 0x194) = solverDelta * gravityY;
    *(float*)((char*)world + 0x198) = solverDelta * gravityZ;
    *(float*)((char*)world + 0x19c) = solverDelta * gravityW;
    const float frameDelta = stepInfo.m_deltaTime;
    *(float*)((char*)world + 0x1a0) = frameDelta * gravityX;
    *(float*)((char*)world + 0x1a4) = frameDelta * gravityY;
    *(float*)((char*)world + 0x1a8) = frameDelta * gravityZ;
    *(float*)((char*)world + 0x1ac) = frameDelta * gravityW;

    stepInputWakeUpContacts();                                // 0x00c2e4e0

    hkWorldOperationUtil_cleanupDirtyIslands(world);

    world->m_criticalSectionLock++;
    world->m_actionsLock--;
    HK_TIMER_END();

    // Let every action notify its tracked objects before the islands are integrated.
    HK_TIMER_BEGIN("StActions");                              // 0x014a1eb4
    for (int i = 0; i < world->m_numActions; ++i) {
        char* action = ((char**)world->m_actions)[i];
        for (int k = 0; k < *(int*)(action + 0x68); ++k) {
            void* tracked = *(void**)(*(int*)(action + 0x64) + k * 4);
            ((void(*)(void*, void*)) * (void***)tracked)(tracked, (char*)world + 0x170);
        }
    }

    if (--world->m_criticalSectionLock == 0 && world->m_pendingOperations != 0
        && world->m_executePendingOperations == 0) {
        hkWorld_executePendingOperations(world);
    }

    world->m_criticalSectionLock++;

    // Per-island dynamics/solver set-up.
    float dt = *(float*)((char*)world + 0x1d4) * *(float*)((char*)world + 0x2a8);
    float dt2 = *(float*)((char*)world + 0x1dc) * *(float*)((char*)world + 0x2a8);
    char stepInput[0x80];
    *(float*)(stepInput + 0x00) = *(float*)((char*)world + 0x2a4);
    *(float*)(stepInput + 0x04) = *(float*)((char*)world + 0x2a8);
    *(float*)(stepInput + 0x08) = stepInfo.m_deltaTime;
    *(float*)(stepInput + 0x0c) = stepInfo.m_invDeltaTime;
    *(float*)(stepInput + 0x10) = *(float*)((char*)world + 0x184);
    *(float*)(stepInput + 0x14) = *(float*)((char*)world + 0x188);
    *(float*)(stepInput + 0x18) = dt;
    *(float*)(stepInput + 0x1c) = *(float*)((char*)world + 0x188);
    *(float*)(stepInput + 0x20) = *(float*)((char*)world + 0x2b0);
    *(float*)(stepInput + 0x24) = dt2;
    stepInput[0x30] = 0;
    stepInput[0x34] = 0;

    char dynamicsStepInfo[0x10];
    *(float*)(dynamicsStepInfo + 0x00) = *(float*)((char*)world + 0x2a4);
    *(float*)(dynamicsStepInfo + 0x04) = *(float*)((char*)world + 0x2a8);
    *(float*)(dynamicsStepInfo + 0x08) = stepInfo.m_deltaTime;
    *(float*)(dynamicsStepInfo + 0x0c) = stepInfo.m_invDeltaTime;

    HK_TIMER_BEGIN("StIntegrate");                            // 0x014a1ea8
    for (int i = world->m_numIslands - 1; i >= 0; --i) {
        void* island = world->m_islands[i];
        if (*(hkInt32*)((char*)island + 0x0c) != 0) {
            // Multi-body island: build and solve the constraint system.
            hkBuildAndSolve(dynamicsStepInfo, (char*)world + 0x180, stepInput, island,
                            *(void**)((char*)island + 0x3c), *(int*)((char*)island + 0x40));
        } else {
            // Single-object island: integrate each active motion.
            HK_TIMER_BEGIN("TtSingleObj");                    // 0x014a1e74
            for (int k = *(int*)((char*)island + 0x40) - 1; k >= 0; --k) {
                void* motion = *(void**)(*(int*)((char*)island + 0x3c) + k * 4);
                motion = *(void**)((char*)motion + 0x58);
                ((void(*)(void*, void*, void*)) * (void***)motion)(motion, (char*)world + 0x170,
                                                                  (char*)world + 0x1a0);
            }
            HK_TIMER_END();
        }

        if (world->m_postIntegrateCallbackList != 0) {
            HK_TIMER_BEGIN("StPostIntegrateCb");              // 0x014a1e94
            for (int k = world->m_numIslands - 1; k >= 0; --k)
                hkWorldCallbackUtil_fireIslandPostIntegrateCallback(world, world->m_islands[k], stepInfo);
        }
    }

    if (--world->m_criticalSectionLock == 0 && world->m_pendingOperations != 0
        && world->m_executePendingOperations == 0) {
        hkWorld_executePendingOperations(world);
    }

    if (world->m_activeEntities != 0) {
        HK_TIMER_BEGIN("TtPostIntegrateCb");                  // 0x014a1e80
        hkWorldCallbackUtil_firePostIntegrateCallback(world, stepInfo);
        HK_TIMER_END();
    }

    HK_TIMER_END();                                           // 0x0143cd94
}

// @ 0x01099cb0
void __stdcall FUN_01099cb0(void* entities, int numEntities, void* world)
{
    // The original loads world->m_o78 and pushes the address of processAgentResetCollisionInformation as a
    // plain immediate (0x01099670) before the call; expressed as a real function-pointer argument.
    void* collideInput = *(void**)((char*)world + 0x78);
    FUN_01099be0(entities, numEntities, collideInput, (hkCollideFunc)FUN_01099670);
}

// @ 0x0109c3b0
int FUN_0109c3b0(int* a, int* b)
{
    uint16_t* aw = (uint16_t*)a;       // 16-bit view of the header words
    uint16_t* bw = (uint16_t*)b;
    switch ((uint32_t)a[0]) {
    case 0:
        memcpy(b, a, 0xc);             // type + counter + remaining count
        if (a[2] > 1) {
            aw[2] = (uint16_t)(aw[2] + 1);   // +0x04: chunks emitted so far
            a[2] = a[2] - 1;
            b[2] = 1;
            return 1;
        }
        break;
    case 1:
        memcpy(b, a, 0x10);            // type + counter + count + count2
        if (aw[7] > 0x80) {            // +0x0e: pending bits, split off 0x80 at a time
            *(int*)(a[2] + 0x18) = *(int*)(a[2] + 0x18) + 1;
            aw[7] = (uint16_t)(aw[7] + 0xff80);
            aw[6] = (uint16_t)(aw[6] + 0x80);   // +0x0c: consumed bits
            bw[7] = 0x80;
            return 1;
        }
        break;
    case 3:
        memcpy(b, a, 0xc);
        if (*(int*)a[2] != 0) {        // +0x08: follow the entry chain
            int* p = (int*)(((int*)a[2])[1] + 0x18);
            *p = *p + 1;
            a[2] = *(int*)a[2];
            return 1;
        }
        break;
    case 7:
        memcpy(b, a, 0x10);
        if (a[3] > 4) {                // +0x0c: peel 4 bytes / a[2] advances by 4
            a[3] = a[3] - 4;
            a[2] = a[2] + 4;
            b[3] = 4;
            return 1;
        }
        break;
    default:
        memcpy(b, a, 0x80);            // opaque chunk: pass the whole header through
        break;
    }
    return 0;
}

// @ 0x0109c5e0
void FUN_0109c5e0(void* job, void* cmd, void* ctx, void* sim)
{
    char* j = (char*)job;
    char* c = (char*)cmd;
    char* x = (char*)ctx;

    AgentClass* cls = &((AgentClass*)(*(char**)c + 0x1a14))[*(signed char*)(j + 8)];
    *(AgentClass**)(c + 0x28) = cls;
    *(uint8_t*)(c + 0x0c) = cls->mField10;

    *(char**)x = x + 0x30;
    *(uint32_t*)(x + 0x3034) = 0x7f7fffee;
    *(uint32_t*)(x + 0x3040) = 0;

    FUN_010fc180(job, cmd, ctx);

    HkMemory* mem = (HkMemory*)g_hkMemory_s0109_c3b0;
    int used = mem->mUsed + mem->mPeakUsed;
    int capacity = mem->mCapacity;
    if (!(capacity > used && capacity - used != 0)) {
        mem->mOutOfMemory = 1;
        mem = (HkMemory*)g_hkMemory_s0109_c3b0;
    }
    if (mem->mOutOfMemory == 1)
        return;

    if (*(void**)x != x + 0x30) {
        AgentListOwner* owner = *(AgentListOwner**)(j + 0x10);
        owner->v05(*(void**)(j + 0x14), job, cmd, ctx);
    }

    if (*(float*)(x + 0x3034) < g_14a1f98) {
        ((CritSec*)((char*)sim + 0x180))->enter();
        ((SimThread*)sim)->FUN_010f0b00(ctx, job);
        *(int*)((char*)sim + 0x180 + 0x18) = -1;
        *(int*)((char*)sim + 0x180 + 0x1c) = -1;
        LeaveCriticalSection((char*)sim + 0x180);
    }
}

// @ 0x0109c6d0
int hkMultiThreadedSimulation::prepareMultithreadStep()
{
    char* s = (char*)this;
    ((CritSec*)(s + 0x100))->enter();
    int v = *(int*)(s + 0xc0) + 1;
    *(int*)(s + 0xc0) = v;
    if (v == 1) return 0;
    *(int*)(s + 0x118) = -1;
    *(int*)(s + 0x11c) = -1;
    LeaveCriticalSection(s + 0x100);
    return 1;
}

// @ 0x0109c730
void* hkMtThreadStructure::ctor(char* world, int sim, int type)
{
    char* s = (char*)this;
    *(int*)(s + 0x58) = 0;
    *(int*)(s + 0x5c) = 0;
    *(int*)(s + 4) = sim;
    *(int*)(s + 8) = type;
    *(int*)(s + 0) = (int)world;
    int* src = *(int**)(world + 0x78);
    int* dst = (int*)(s + 0xc);
    for (int i = 0xb; i != 0; --i) *dst++ = *src++;
    *(int*)(s + 0x38) = *(int*)(world + 0x2a4);
    *(int*)(s + 0x3c) = *(int*)(world + 0x2a8);
    *(int*)(s + 0x48) = *(int*)(world + 0x2b0);
    *(int*)(s + 0x70) = *(int*)(world + 0x184);
    *(int*)(s + 0x74) = *(int*)(world + 0x188);
    *(int*)(s + 0x40) = *(int*)(world + 0x178);
    *(int*)(s + 0x44) = *(int*)(world + 0x17c);
    *(float*)(s + 0x4c) = *(float*)(world + 0x1d4) * *(float*)(world + 0x2a8);
    *(int*)(s + 0x50) = *(int*)(world + 0x188);
    *(float*)(s + 0x54) = *(float*)(world + 0x1dc) * *(float*)(world + 0x2a8);
    return this;
}

// @ 0x0109c7d0
void MtEntityEntityBroadPhaseListener::addCollisionPair(int* pair)
{
    char* s = (char*)this;
    int* listener = *(int**)(s + 8);
    char* e1 = (char*)(*pair + *(char*)(*pair + 5));
    char* e2 = (char*)(pair[1] + *(char*)(pair[1] + 5));
    char* a = e1 + *(int*)(e1 + 0x10);
    char* b = e2 + *(int*)(e2 + 0x10);
    if (((char*)listener)[0x54] && !a[0x99] && !b[0x99] && *(int*)(a + 0x5c) != *(int*)(b + 0x5c)) {
        if ((uint)*(int*)((char*)listener + 0x5c) == (*(uint*)((char*)listener + 0x60) & 0x3fffffff))
            FUN_0107f530((char*)listener + 0x58, 8);
        int idx = *(int*)((char*)listener + 0x5c);
        int* arr = *(int**)((char*)listener + 0x58);
        arr[idx * 2] = *pair;
        arr[idx * 2 + 1] = pair[1];
        *(int*)((char*)listener + 0x5c) = *(int*)((char*)listener + 0x5c) + 1;
        return;
    }
    // no collision pair to report: classify the agent pair in the simulation's pair table
    char* table = *(char**)(*(int*)((char*)listener + 0x2c) + 0x78);
    int   base = *(int*)table;
    int   i1 = *(unsigned short*)(e1 + 0x1a);
    int   i2 = *(unsigned short*)(e2 + 0x1a);
    char  cls = *(char*)(base + i2 + i1 * 8 + 0x19d4);
    if (cls) {
        table[0xc] = *(char*)(base + (int)cls * 0x3c + 0x1a24);
        FUN_010a3920(e1, e2, table);
    }
}

// @ 0x0109c890
void MtEntityEntityBroadPhaseListener::removeCollisionPair(int* pair)
{
    char* s = (char*)this;
    int* listener = *(int**)(s + 8);
    char* e1 = (char*)(*pair + *(char*)(*pair + 5));
    char* e2 = (char*)(pair[1] + *(char*)(pair[1] + 5));
    char* a = e1 + *(int*)(e1 + 0x10);
    char* b = e2 + *(int*)(e2 + 0x10);
    if (((char*)listener)[0x54] && !a[0x99] && !b[0x99] && *(int*)(a + 0x5c) != *(int*)(b + 0x5c)) {
        if ((uint)*(int*)((char*)listener + 0x8c) == (*(uint*)((char*)listener + 0x90) & 0x3fffffff))
            FUN_0107f530((char*)listener + 0x88, 8);
        int idx = *(int*)((char*)listener + 0x8c);
        int* arr = *(int**)((char*)listener + 0x88);
        arr[idx * 2] = *pair;
        arr[idx * 2 + 1] = pair[1];
        *(int*)((char*)listener + 0x8c) = *(int*)((char*)listener + 0x8c) + 1;
        return;
    }
    int e = (int)FUN_010fbb30(e1, e2);
    if (e) FUN_010a39f0((void*)e);
}

// @ 0x0109c940
hkMultiThreadedSimulation* hkMultiThreadedSimulation::ctor(char* owner)
{
    char* s = (char*)this;
    FUN_010f19b0(0);
    *(int*)(s) = 0x14a1fe0;
    *(int*)(s + 0x38) = 0;
    *(int*)(s + 0x30) = 0x14a1f9c;
    *(unsigned short*)(s + 0x36) = 1;
    *(int*)(s + 0x44) = 0;
    *(unsigned short*)(s + 0x42) = 1;
    *(int*)(s + 0x3c) = 0x149dabc;
    *(unsigned short*)(s + 0x4e) = 1;
    *(int*)(s + 0x50) = 0;
    *(int*)(s + 0x48) = 0x149da84;
    *(int*)(s + 0x58) = 0;
    *(int*)(s + 0x5c) = 0;
    *(int*)(s + 0x60) = 0x80000000;
    InitCrit(s + 0x68, 4000);
    *(int*)(s + 0x88) = 0;
    *(int*)(s + 0x8c) = 0;
    *(int*)(s + 0x90) = 0x80000000;
    InitCrit(s + 0x98, 4000);
    ((SimSub*)(s + 0xb8))->FUN_01082900();
    ((SimSub*)(s + 0x100))->FUN_010a5a90();
    InitCrit(s + 0x180, 4000);
    InitCrit(s + 0x1c0, 100000);
    InitCrit(s + 0x200, 4000);
    *(int*)(s + 0x2c) = (int)owner;
    *(int*)(s + 0xc0) = 0;
    *(char*)(s + 0x54) = 0;
    *(int*)(s + 0x38) = (int)s;
    *(int*)(s + 0x44) = (int)(s + 0x200);
    *(int*)(*(char**)(owner + 0x68) + 0x24) = (int)(s + 0x30);
    *(int*)(*(char**)(owner + 0x68) + 0x44) = (int)(s + 0x3c);
    *(int*)(*(char**)(owner + 0x68) + 0x28) = (int)(s + 0x3c);
    *(int*)(*(char**)(owner + 0x68) + 0x48) = (int)(s + 0x3c);
    *(int*)(s + 0x50) = (int)(s + 0x200);
    *(int*)(*(char**)(owner + 0x68) + 0x2c) = (int)(s + 0x48);
    *(int*)(*(char**)(owner + 0x68) + 0x64) = (int)(s + 0x48);
    *(int*)(*(char**)(owner + 0x68) + 0x4c) = (int)(s + 0x48);
    *(int*)(*(char**)(owner + 0x68) + 0x68) = (int)(s + 0x48);
    *(int*)(*(char**)(owner + 0x68) + 0x6c) = (int)(s + 0x48);
    *(int*)(s + 0x15c) = 0x109c3b0;
    *(int*)(s + 0x160) = 0x109c4f0;
    return this;
}

// @ 0x0109cab0
void hkMultiThreadedSimulation::dtor()
{
    char* s = (char*)this;
    *(int*)(s) = 0x14a1fe0;
    DeleteCriticalSection(s + 0x200);
    DeleteCriticalSection(s + 0x1c0);
    DeleteCriticalSection(s + 0x180);
    ((SimSub*)(s + 0x100))->FUN_010a65e0();
    DeleteCriticalSection(s + 0x98);
    if (*(int*)(s + 0x90) >= 0) {
        SimSub* tm = (SimSub*)TlsGetValue((uint)(int)g_hkThreadMemoryTls);
        tm->FUN_0107db10(*(int*)(s + 0x88), (*(int*)(s + 0x90) & 0x3fffffff) << 3, 0x14);
    }
    DeleteCriticalSection(s + 0x68);
    if (*(int*)(s + 0x60) >= 0) {
        SimSub* tm = (SimSub*)TlsGetValue((uint)(int)g_hkThreadMemoryTls);
        tm->FUN_0107db10(*(int*)(s + 0x58), (*(int*)(s + 0x60) & 0x3fffffff) << 3, 0x14);
    }
    *(int*)(s + 0x48) = (int)g_13ef094;
    *(int*)(s + 0x3c) = (int)g_13ef094;
    *(int*)(s + 0x30) = (int)g_13ef094;
    FUN_010f1a10();
}

// @ 0x0109e8e0
void hkEntityCallbackUtil::fireContactPointRemovedInternal(hkEntity_s0109_e8e0* e, hkContactPointRemovedEvent& ev)
{
    ev.m_callbackFiredFrom = e;
#define CALL(l) (l)->contactPointRemovedCallback(ev)
    HK_FIRE_LISTENERS(e->m_contactListeners, CALL);
#undef CALL
}

// @ 0x0109e970
void hkEntityCallbackUtil::fireContactProcessInternal(hkEntity_s0109_e8e0* e, hkContactProcessEvent& ev)
{
    ev.m_callbackFiredFrom = e;
#define CALL(l) (l)->contactProcessCallback(ev)
    HK_FIRE_LISTENERS(e->m_contactListeners, CALL);
#undef CALL
}

// @ 0x0109ea00
void hkEntityCallbackUtil::fireEntityRemoved(hkEntity_s0109_e8e0* e)
{
    for (int i = e->m_entityListeners.m_size - 1; i >= 0; --i) {
        if (e->m_entityListeners.m_data[i] != 0)
            e->m_entityListeners.m_data[i]->entityRemovedCallback(e);
    }
    // actions and constraints remove themselves from the arrays as a side effect
    while (e->m_actions.m_size != 0)
        e->m_actions.m_data[0]->entityRemovedCallback(e);
    while (e->m_constraints.m_size != 0)
        e->m_constraints.m_data[0]->entityRemovedCallback(e);
    for (int i = 0; i < e->m_extendedListeners.m_size; ++i) {
        if (e->m_extendedListeners.m_data[i] != 0)
            e->m_extendedListeners.m_data[i]->entityDeletedCallback(e);
    }
}

// @ 0x0109eaa0
void hkWorldCallbackUtil::fireActionAdded(hkWorld_s0109_e8e0* w, hkAction_s0109_e8e0* a)
{
#define CALL(l) (l)->actionAddedCallback(a)
    HK_FIRE_LISTENERS(w->m_actionListeners, CALL);
#undef CALL
}

// @ 0x0109eb30
void hkWorldCallbackUtil::fireActionRemoved(hkWorld_s0109_e8e0* w, hkAction_s0109_e8e0* a)
{
#define CALL(l) (l)->actionRemovedCallback(a)
    HK_FIRE_LISTENERS(w->m_actionListeners, CALL);
#undef CALL
}

// @ 0x0109ebc0
void hkWorldCallbackUtil::fireEntityAdded(hkWorld_s0109_e8e0* w, hkEntity_s0109_e8e0* e)
{
#define CALL(l) (l)->entityAddedCallback(e)
    HK_FIRE_LISTENERS(w->m_entityListeners, CALL);
#undef CALL
}

// @ 0x0109ec50
void hkWorldCallbackUtil::fireEntityRemoved(hkWorld_s0109_e8e0* w, hkEntity_s0109_e8e0* e)
{
#define CALL(l) (l)->entityRemovedCallback(e)
    HK_FIRE_LISTENERS(w->m_entityListeners, CALL);
#undef CALL
}

// @ 0x0109ece0
void hkWorldCallbackUtil::fireEntityShapeSet(hkWorld_s0109_e8e0* w, hkEntity_s0109_e8e0* e)
{
#define CALL(l) (l)->entityShapeSetCallback(e)
    HK_FIRE_LISTENERS(w->m_entityListeners, CALL);
#undef CALL
}

// @ 0x0109ed70
void hkWorldCallbackUtil::firePhantomAdded(hkWorld_s0109_e8e0* w, hkPhantom_s0109_e8e0* p)
{
#define CALL(l) (l)->phantomAddedCallback(p)
    HK_FIRE_LISTENERS(w->m_phantomListeners, CALL);
#undef CALL
}

// @ 0x0109ee00
void hkWorldCallbackUtil::firePhantomRemoved(hkWorld_s0109_e8e0* w, hkPhantom_s0109_e8e0* p)
{
#define CALL(l) (l)->phantomRemovedCallback(p)
    HK_FIRE_LISTENERS(w->m_phantomListeners, CALL);
#undef CALL
}

// @ 0x0109ee90
void hkWorldCallbackUtil::firePhantomShapeSet(hkWorld_s0109_e8e0* w, hkPhantom_s0109_e8e0* p)
{
#define CALL(l) (l)->phantomShapeSetCallback(p)
    HK_FIRE_LISTENERS(w->m_phantomListeners, CALL);
#undef CALL
}

// @ 0x0109ef20
void hkWorldCallbackUtil::fireConstraintAdded(hkWorld_s0109_e8e0* w, hkConstraintInstance_s0109_e8e0* c)
{
#define CALL(l) (l)->constraintAddedCallback(c)
    HK_FIRE_LISTENERS(w->m_constraintListeners, CALL);
#undef CALL
}

// @ 0x0109efb0
void hkWorldCallbackUtil::fireConstraintRemoved(hkWorld_s0109_e8e0* w, hkConstraintInstance_s0109_e8e0* c)
{
#define CALL(l) (l)->constraintRemovedCallback(c)
    HK_FIRE_LISTENERS(w->m_constraintListeners, CALL);
#undef CALL
}

// @ 0x0109f040
void hkWorldCallbackUtil::fireContactPointAdded(hkWorld_s0109_e8e0* w, hkContactPointAddedEvent& ev)
{
    ev.m_callbackFiredFrom = 0;
#define CALL(l) (l)->contactPointAddedCallback(ev)
    HK_FIRE_LISTENERS(w->m_contactListeners, CALL);
#undef CALL
}

// @ 0x0109f0d0
void hkWorldCallbackUtil::fireContactPointConfirmed(hkWorld_s0109_e8e0* w, hkContactPointConfirmedEvent& ev)
{
    ev.m_callbackFiredFrom = 0;
#define CALL(l) (l)->contactPointConfirmedCallback(ev)
    HK_FIRE_LISTENERS(w->m_contactListeners, CALL);
#undef CALL
}

// @ 0x0109f160
void hkWorldCallbackUtil::fireContactPointRemoved(hkWorld_s0109_e8e0* w, hkContactPointRemovedEvent& ev)
{
    ev.m_callbackFiredFrom = 0;
#define CALL(l) (l)->contactPointRemovedCallback(ev)
    HK_FIRE_LISTENERS(w->m_contactListeners, CALL);
#undef CALL
}

// @ 0x0109f1f0
void hkWorldCallbackUtil::fireContactProcess(hkWorld_s0109_e8e0* w, hkContactProcessEvent& ev)
{
    ev.m_callbackFiredFrom = 0;
#define CALL(l) (l)->contactProcessCallback(ev)
    HK_FIRE_LISTENERS(w->m_contactListeners, CALL);
#undef CALL
}

// @ 0x0109f280
void hkWorldCallbackUtil::fireWorldDeleted(hkWorld_s0109_e8e0* w)
{
#define CALL(l) (l)->worldDeletedCallback(w)
    HK_FIRE_LISTENERS(w->m_worldDeletionListeners, CALL);
#undef CALL
}

// @ 0x0109f300
void hkWorldCallbackUtil::fireIslandActivated(hkWorld_s0109_e8e0* w, hkSimulationIsland_s0109_e8e0* island)
{
    w->m_criticalOperationsLockCount++;
#define CALL(l) (l)->islandActivatedCallback(island)
    HK_FIRE_LISTENERS(w->m_islandActivationListeners, CALL);
#undef CALL
    for (int i = 0; i < island->m_numEntities; ++i) {
        hkEntity_s0109_e8e0* e = island->m_entities[i];
#define CALL(l) (l)->entityActivatedCallback(island->m_entities[i])
        HK_FIRE_LISTENERS(e->m_activationListeners, CALL);
#undef CALL
    }
    hkWorld_unlockAndFlush(w);
}

// @ 0x0109f450
void hkWorldCallbackUtil::fireIslandDeactivated(hkWorld_s0109_e8e0* w, hkSimulationIsland_s0109_e8e0* island)
{
    w->m_criticalOperationsLockCount++;
#define CALL(l) (l)->islandDeactivatedCallback(island)
    HK_FIRE_LISTENERS(w->m_islandActivationListeners, CALL);
#undef CALL
    for (int i = 0; i < island->m_numEntities; ++i) {
        hkEntity_s0109_e8e0* e = island->m_entities[i];
#define CALL(l) (l)->entityDeactivatedCallback(island->m_entities[i])
        HK_FIRE_LISTENERS(e->m_activationListeners, CALL);
#undef CALL
    }
    hkWorld_unlockAndFlush(w);
}

// @ 0x0109f5a0
void hkWorldCallbackUtil::firePostSimulationCallback(hkWorld_s0109_e8e0* w, const hkStepInfo_s0109_e8e0& s)
{
#define CALL(l) (l)->postSimulationCallback(w, s)
    HK_FIRE_LISTENERS(w->m_postSimulationListeners, CALL);
#undef CALL
}

// @ 0x0109f630
void hkWorldCallbackUtil::firePostIntegrateCallback(hkWorld_s0109_e8e0* w, const hkStepInfo_s0109_e8e0& s)
{
#define CALL(l) (l)->postIntegrateCallback(w, s)
    HK_FIRE_LISTENERS(w->m_postIntegrateListeners, CALL);
#undef CALL
}

// @ 0x0109f6c0
void hkWorldCallbackUtil::firePostCollideCallback(hkWorld_s0109_e8e0* w, const hkStepInfo_s0109_e8e0& s)
{
#define CALL(l) (l)->postCollideCallback(w, s)
    HK_FIRE_LISTENERS(w->m_postCollideListeners, CALL);
#undef CALL
}

// @ 0x0109f750
void hkWorldCallbackUtil::fireIslandPostIntegrateCallback(hkWorld_s0109_e8e0* w, hkSimulationIsland_s0109_e8e0* i, const hkStepInfo_s0109_e8e0& s)
{
#define CALL(l) (l)->postIntegrateCallback(i, s)
    HK_FIRE_LISTENERS(w->m_islandPostIntegrateListeners, CALL);
#undef CALL
}

// @ 0x0109f7e0
void hkWorldCallbackUtil::fireIslandPostCollideCallback(hkWorld_s0109_e8e0* w, hkSimulationIsland_s0109_e8e0* i, const hkStepInfo_s0109_e8e0& s)
{
#define CALL(l) (l)->postCollideCallback(i, s)
    HK_FIRE_LISTENERS(w->m_islandPostCollideListeners, CALL);
#undef CALL
}

// @ 0x0109f900
void hkSimpleConstraintOwner_s0109_f870::subConstraintInfo(hkConstraintInstance_s0109_f870*, hkConstraintInfo_s0109_f870& info)
{
	m_sizeOfJacobians -= info.m_sizeOfJacobians;
	m_sizeOfSchemas -= info.m_sizeOfSchemas;
	m_numSolverResults -= info.m_numSolverResults;
}
