// Slice s010938e0: hkPoweredChainData::buildJacobian (Havok 3.1.0, 0x010938e0, 2316 bytes).
// Flags: /O2 /MD /Gy /TP /fp:fast /GS- (x87 code, no EH frame, no security cookie).
//
// Layouts: match/include/havok31/hkReflectedClasses.h (hkPoweredChainData 0x34 bytes: m_infos +0xc,
// m_tau +0x18 .. m_maxErrorDistance +0x30; ConstraintInfo 0x50: pivotInA/B +0, aTc +0x20, bTc +0x30,
// motors[3] +0x40, switchBodies +0x4c). The chain instance, runtime and info structs were read off the
// asm (offsets in the comments); member names follow the Havok 6.x headers where they exist.
//
// What it does: for each of the n = chainedEntities-1 links it advances a copy of the query-in one body
// along the chain, builds the stabilized ball-socket jacobian (pivots to world, the schemas are thrown
// away again), computes the angular error of the link's quaternion (target aTc and the previous target
// kept in the runtime) and for the three motor axes builds a velocity-motor jacobian row through
// motor->motor(). Finally it fills a parameter block and calls _hkPoweredChainBuildJacobian.
// Havok 3.1 was built by an older cl, so this is behaviourally equivalent rather than byte-exact.
#include "types.h"

typedef float hkReal;

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern unsigned long g_threadMemoryTls;                         // 0x016e4174: hkThreadMemory TLS slot
extern const float kZero;                                       // 0x01485378
extern const float kOne;                                        // 0x01485720

struct hkThreadMemory {
	void deallocateChunk(void* p, int nbytes, int cls);         // 0x0107db10
};

struct hkArrayUtil {
	static void _reserveExactly(void* array, int n, int elemSize);   // 0x0107f4a0
	static void _reserveMore(void* array, int elemSize);             // 0x0107f530
};

template <class T> struct hkArray {
	enum { CAPACITY_MASK = 0x3fffffff, DONT_DEALLOCATE_FLAG = (int)0x80000000 };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;
	int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
	void pushBackUnchecked(const T& t) { m_data[m_size++] = t; }
	void pushBack(const T& t)
	{
		if (m_size == getCapacity())
			hkArrayUtil::_reserveMore(this, sizeof(T));
		m_data[m_size++] = t;
	}
	~hkArray()
	{
		if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0) {
			hkThreadMemory* mem = (hkThreadMemory*)TlsGetValue(g_threadMemoryTls);
			mem->deallocateChunk(m_data, getCapacity() * sizeof(T), 0x14);
		}
	}
};

template <class T, int N> struct hkInplaceArray : hkArray<T> {
	T m_storage[N];
	hkInplaceArray()
	{
		this->m_size = 0;
		this->m_data = m_storage;
		this->m_capacityAndFlags = N | hkArray<T>::DONT_DEALLOCATE_FLAG;
	}
	void setSizeAndReserve(int n)
	{
		if (n > N)
			hkArrayUtil::_reserveExactly(this, n < 2 * N ? 2 * N : n, sizeof(T));
		this->m_size = n;
	}
};

class __declspec(align(16)) hkVector4
{
public:
	float x, y, z, w;
};

class hkRotation;

class __declspec(align(16)) hkQuaternion
{
public:
	float x, y, z, w;
	void set(const hkRotation& r);                                   // 0x01082490
	void setMul(const hkQuaternion& a, const hkQuaternion& b);       // 0x01082210
	float lengthSquared() const { return x * x + w * w + z * z + y * y; }
};

class hkRotation
{
public:
	hkVector4 m_col[3];
	void set(const hkQuaternion& q);                                 // 0x010824a0
};

class hkTransform
{
public:
	hkRotation m_rotation;     // +0x00
	hkVector4 m_translation;   // +0x30
};

// hkVector4::setTransformedPos (inlined): ((vz*c2 + vy*c1) + vx*c0) + t, w = 0.
__forceinline void setTransformedPos(hkVector4& d, const hkTransform& t, const float* p)
{
	const float vx = p[0], vy = p[1], vz = p[2];
	d.x = ((vz * t.m_rotation.m_col[2].x + vy * t.m_rotation.m_col[1].x) + vx * t.m_rotation.m_col[0].x) + t.m_translation.x;
	d.y = ((vz * t.m_rotation.m_col[2].y + vy * t.m_rotation.m_col[1].y) + vx * t.m_rotation.m_col[0].y) + t.m_translation.y;
	d.z = ((vz * t.m_rotation.m_col[2].z + vy * t.m_rotation.m_col[1].z) + vx * t.m_rotation.m_col[0].z) + t.m_translation.z;
	d.w = 0.0f;
}

struct hkSolverResults
{
	hkReal m_impulseApplied;        // +0
	hkReal m_internalSolverData;    // +4
	hkSolverResults() : m_impulseApplied(0), m_internalSolverData(0) {}
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
	int m_bodyA;                         // +0x28 (solver accumulator pointer, handled as an integer)
	int m_bodyB;                         // +0x2c
	const hkTransform* m_transformA;     // +0x30
	const hkTransform* m_transformB;     // +0x34
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

// hkConstraintMotorInput: status written by the motor BeginJacobian, then the inputs.
struct hkConstraintMotorInput
{
	hkReal m_virtualMass;                       // +0x00
	const hkConstraintQueryIn* m_stepInfo;      // +0x04
	hkSolverResults m_lastResults;              // +0x08
	hkReal m_deltaTarget;                       // +0x10
	hkReal m_positionError;                     // +0x14
};

struct hkConstraintMotorOutput
{
	hkReal m_targetPosition;
	hkReal m_targetVelocity;
	hkReal m_minForce;
	hkReal m_maxForce;
	hkReal m_tau;
	hkReal m_damping;
};

class hkConstraintMotor
{
public:
	virtual void vslot0();
	virtual void vslot1();
	virtual void motor(const hkConstraintMotorInput& input, hkConstraintMotorOutput& output) const = 0;   // +8
};

// hkp3dAngularMotorSolverInfo-style per-motor block (0x18 bytes, written by the commit)
struct hkMotorInfo { int m_data[6]; };

// Element of the local per-link array (0x4c bytes): motor status flag, then one block per axis.
struct hkChainLinkMotorInfo
{
	unsigned char m_flags;       // +0x00 (copied from the runtime flags)
	hkMotorInfo m_motors[3];     // +0x04, +0x1c, +0x34
};

// ---- Havok 3.1 entity / motion / chain instance views (offsets from the asm)
struct hkMotionView
{
	char pad00[8];
	int m_solverOffset;          // +0x08
	char pad0c[4];
	hkTransform m_transform;     // +0x10
};
struct hkEntityView
{
	char pad00[0x58];
	hkMotionView* m_motion;      // +0x58
};
struct hkConstraintInternalView
{
	char pad00[0x18];
	void* m_runtime;             // +0x18
};
struct hkConstraintChainInstanceView
{
	char pad00[0x10];
	hkEntityView* m_entities[2];             // +0x10
	char pad18[0x0c];
	hkConstraintInternalView* m_internal;    // +0x24
	hkArray<hkEntityView*> m_chainedEntities; // +0x28
};

// Parameter block of _hkPoweredChainBuildJacobian (0x34 bytes, stores read off the asm).
struct hkPoweredChainBuildParams
{
	int m_numConstraints;                    // +0x00
	hkReal m_tau;                            // +0x04
	hkReal m_damping;                        // +0x08
	hkReal m_cfmLinAdd;                      // +0x0c
	hkReal m_cfmLinMul;                      // +0x10
	hkReal m_cfmAngAdd;                      // +0x14
	hkReal m_cfmAngMul;                      // +0x18
	int* m_bodyOffsets;                      // +0x1c
	int m_baseOffset;                        // +0x20
	hkChainLinkMotorInfo* m_links;           // +0x24
	int m_unused28;                          // +0x28
	unsigned char* m_flags;                  // +0x2c
	void* m_jacobiansStart;                  // +0x30
};

extern "C" void hkBeginConstraints(const hkConstraintQueryIn& in, hkConstraintQueryOut& out,
                                   hkSolverResults* sr, int solverResultStriding);              // 0x010AA080
extern "C" void hkQueryInCheck(const hkConstraintQueryIn* in);                                   // 0x00C2E4E0 (empty)
extern "C" void hkStabilizedBallSocketConstraintBuildJacobian(const hkVector4& pivotAW, const hkVector4& pivotBW,
                                                              hkReal maxErrorDistance, const hkConstraintQueryIn& in,
                                                              hkConstraintQueryOut& out);       // 0x010ACBF0
extern "C" void hk1dAngularVelocityMotorBeginJacobian(const hkVector4& axis, const hkConstraintQueryIn& in,
                                                      void* jacobians, hkConstraintMotorInput* statusOut);   // 0x010AC750
extern "C" void hk1dAngularVelocityMotorCommitJacobianInMotorInfo(const hkConstraintMotorOutput& info,
                                                                  const hkConstraintQueryIn& in,
                                                                  hkConstraintQueryOut& out,
                                                                  hkMotorInfo* motorInfoOut);   // 0x010AA130
extern "C" void hkPoweredChainBuildJacobian(const hkPoweredChainBuildParams* params, const hkConstraintQueryIn& in,
                                            hkConstraintQueryOut& out);                         // 0x010B1BF0

// 0x010936c0 (same TU, register convention): doubled vector part of conj(a) * b with its
// sign flipped when a . b < 0, i.e. the angular error between the two orientations.
static void quaternionError(hkVector4& out, const hkQuaternion& a, const hkQuaternion& b)       // 0x010936c0
{
	const float r1 = a.x * b.z - a.z * b.x;
	const float r2 = b.x * a.y - b.y * a.x;
	const float r3 = a.z * b.y - a.y * b.z;
	out.w = 0.0f;
	out.x = r3;
	out.y = r1;
	out.z = r2;
	const float aw = a.w;
	out.x = aw * b.x + out.x;
	out.y = aw * b.y + r1;
	out.z = aw * b.z + r2;
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

class hkConstraintData
{
public:
	virtual ~hkConstraintData();
	int m_memSizeAndFlags_userData[2];  // +0x04
};

class hkPoweredChainData : public hkConstraintData
{
public:
	struct ConstraintInfo
	{
		hkVector4 m_pivotInA;            // +0x00
		hkVector4 m_pivotInB;            // +0x10
		hkQuaternion m_aTc;              // +0x20
		hkQuaternion m_bTc;              // +0x30
		hkConstraintMotor* m_motors[3];  // +0x40
		bool m_switchBodies;             // +0x4c
	};

	hkArray<ConstraintInfo> m_infos;     // +0x0c
	hkReal m_tau;                        // +0x18
	hkReal m_damping;                    // +0x1c
	hkReal m_cfmLinAdd;                  // +0x20
	hkReal m_cfmLinMul;                  // +0x24
	hkReal m_cfmAngAdd;                  // +0x28
	hkReal m_cfmAngMul;                  // +0x2c
	hkReal m_maxErrorDistance;           // +0x30

	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual hkSolverResults* getSolverResults(void* runtime);   // +0x14 (returns its argument)
	virtual void vslot6();
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);
};

// @ 0x010938e0
void hkPoweredChainData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	hkBeginConstraints(in, out, (hkSolverResults*)in.m_constraintRuntime, 8);
	void* const savedSchemas = out.m_jacobianSchemas;

	// per-link copy of the query-in that is stepped along the chain
	hkConstraintQueryIn inCopy = in;
	inCopy.m_constraintInstance = 0;
	inCopy.m_constraintRuntime = 0;
	hkInplaceArray<int, 32> bodyOffsets;
	void* const jacobiansStart = out.m_jacobians;

	hkConstraintChainInstanceView* instance = (hkConstraintChainInstanceView*)in.m_constraintInstance;
	const int base = in.m_bodyA - instance->m_entities[0]->m_motion->m_solverOffset;
	const int n = instance->m_chainedEntities.m_size - 1;
	hkInplaceArray<hkChainLinkMotorInfo, 32> links;
	links.setSizeAndReserve(n);

	hkMotionView* motion = instance->m_chainedEntities.m_data[0]->m_motion;
	inCopy.m_bodyB = motion->m_solverOffset + base;
	bodyOffsets.pushBackUnchecked(inCopy.m_bodyB - base);
	inCopy.m_transformB = &motion->m_transform;
	inCopy.m_rhsFactor = inCopy.m_substepInvDeltaTime;
	inCopy.m_dampingFactor = 1.0f;

	hkConstraintQueryOut localOut;
	localOut.m_jacobians = (char*)out.m_jacobians + n * 0x90;
	localOut.m_jacobianSchemas = out.m_jacobianSchemas;

	for (int i = 0; i < n; i++) {
		inCopy.m_bodyA = inCopy.m_bodyB;
		inCopy.m_transformA = inCopy.m_transformB;
		hkMotionView* nextMotion = instance->m_chainedEntities.m_data[i + 1]->m_motion;
		inCopy.m_bodyB = nextMotion->m_solverOffset + base;
		bodyOffsets.pushBack(inCopy.m_bodyB - base);
		inCopy.m_transformB = &nextMotion->m_transform;

		// pivots in world space
		const ConstraintInfo* info = &m_infos.m_data[i];
		hkVector4 pivotAW;
		setTransformedPos(pivotAW, *inCopy.m_transformA, &info->m_pivotInA.x);
		hkVector4 pivotBW;
		setTransformedPos(pivotBW, *inCopy.m_transformB, &info->m_pivotInB.x);

		hkQueryInCheck(&inCopy);
		hkStabilizedBallSocketConstraintBuildJacobian(pivotAW, pivotBW, m_maxErrorDistance, inCopy, out);
		out.m_jacobianSchemas = savedSchemas;

		// orientation of the two bodies, in the constraint space
		hkQuaternion qA;
		qA.set(inCopy.m_transformA->m_rotation);
		hkQuaternion qB;
		qB.set(inCopy.m_transformB->m_rotation);
		if (m_infos.m_data[i].m_switchBodies) {
			hkQuaternion t = qA;
			qA = qB;
			qB = t;
		}
		hkQuaternion bTcInWorld;
		bTcInWorld.setMul(qB, info->m_bTc);
		qB = bTcInWorld;

		// target orientation and the previous one kept in the runtime
		const int size = m_infos.m_size;
		hkQuaternion* runtimeQ = (hkQuaternion*)((char*)in.m_constraintRuntime + (size * 3 + i) * 16 + ((size + 3) & ~3));
		hkQuaternion prevTarget = *runtimeQ;
		if (prevTarget.lengthSquared() == kZero)
			prevTarget = info->m_aTc;
		hkQuaternion qTarget;
		qTarget.setMul(qA, info->m_aTc);
		hkQuaternion qPrevTarget;
		qPrevTarget.setMul(qA, prevTarget);
		*runtimeQ = info->m_aTc;

		hkVector4 err;
		quaternionError(err, qTarget, qB);
		hkVector4 errPrev;
		quaternionError(errPrev, qPrevTarget, qB);
		err.x -= errPrev.x;
		err.y -= errPrev.y;
		err.z -= errPrev.z;
		err.w -= errPrev.w;
		if (m_infos.m_data[i].m_switchBodies) {
			err.x = -err.x;
			err.y = -err.y;
			err.z = -err.z;
			errPrev.x = -errPrev.x;
			errPrev.y = -errPrev.y;
			errPrev.z = -errPrev.z;
		}

		hkRotation motorAxes;
		motorAxes.set(qB);
		const float* errs = &err.x;
		const float* errsPrev = &errPrev.x;
		for (int j = 0; j < 3; j++) {
			hkVector4 axis = motorAxes.m_col[j];
			hkSolverResults* results = getSolverResults(((hkConstraintChainInstanceView*)in.m_constraintInstance)->m_internal->m_runtime);
			hkConstraintMotorInput input;
			hk1dAngularVelocityMotorBeginJacobian(axis, inCopy, localOut.m_jacobians, &input);
			input.m_deltaTarget = errs[j];
			input.m_lastResults = results[i * 6 + 3 + j];
			input.m_positionError = errsPrev[j];
			input.m_stepInfo = &inCopy;
			hkConstraintMotorOutput output;
			m_infos.m_data[i].m_motors[j]->motor(input, output);
			hk1dAngularVelocityMotorCommitJacobianInMotorInfo(output, inCopy, localOut, &links.m_data[i].m_motors[j]);
			localOut.m_jacobianSchemas = savedSchemas;
		}
	}
	out.m_jacobians = localOut.m_jacobians;

	const unsigned char* flags = (const unsigned char*)((hkConstraintChainInstanceView*)in.m_constraintInstance)->m_internal->m_runtime + m_infos.m_size * 0x30;
	for (int k = 0; k < n; k++)
		links.m_data[k].m_flags = flags[k];

	hkPoweredChainBuildParams params;
	params.m_tau = m_tau;
	params.m_damping = m_damping;
	params.m_cfmLinAdd = m_cfmLinAdd;
	params.m_cfmLinMul = m_cfmLinMul;
	params.m_cfmAngAdd = m_cfmAngAdd;
	params.m_cfmAngMul = m_cfmAngMul;
	params.m_bodyOffsets = bodyOffsets.m_data;
	params.m_baseOffset = base;
	params.m_links = links.m_data;
	params.m_unused28 = 0;
	params.m_flags = (unsigned char*)flags;
	params.m_jacobiansStart = jacobiansStart;
	params.m_numConstraints = n;
	hkPoweredChainBuildJacobian(&params, in, out);
}
