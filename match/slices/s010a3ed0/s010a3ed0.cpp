// Havok 3.1.0 slice s010a3ed0: hkSimpleContactConstraintData / hkSoftContactConstraintData and the
// hkConstraintSolverSetup helpers (SporeApp.exe 0x010a3ed0..0x010a4e3e).
//
// Layout notes: struct stubs carry members at the offsets seen in the 32-bit binary (comments give the byte
// offset). Pointer-valued members make the 64-bit layout differ; the offsets in the comments are the x86
// ones. Member names that come from the Havok 3.1 reflection data or from the dev PDB are real; names tagged
// "(inferred)" are Claude-coined from how the code uses the field (6.x headers were used only as a naming hint).
#include "types.h"
#include <stddef.h>
#include <string.h>

#if defined(_WIN32)
#include <windows.h>
#endif

// X87-PRECISION: values the binary keeps unrounded on the x87 stack use this type. Spore runs the x87 at 24-bit
// precision on the main thread, so `float` is the closest portable choice; `double` keeps the extended-range
// behaviour of an unrestricted x87. Change here to experiment.
typedef double hkX87Real;

typedef uint8_t hkUint8;
typedef uint16_t hkUint16;

// User-declared ctor => non-POD => returned through a hidden pointer, as in the binary.
class hkBool
{
public:
	hkBool(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
private:
	char m_bool;
};

struct hkArrayUtil
{
	static void _reserveMore(void* array, int elemSize);                                       // 0x0107F530
	static void _reduce(void* array, int elemSize, void* inplaceStorage, int inplaceCapacity); // 0x0107F5D0
};

// Layout shared by every hkArray<T>: data, size, capacity | flags.
template <typename T>
struct hkArray
{
	enum { CAPACITY_MASK = 0x3FFFFFFF };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	// Inlined hkArray::expandOne(): reserve (growth) when full, then bump the size.
	T* expandOne()
	{
		if (m_size == (m_capacityAndFlags & CAPACITY_MASK))
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		T* p = m_data + m_size;
		++m_size;
		return p;
	}
};

struct hkVector4 { float x, y, z, w; };

// hkContactPoint, 32 bytes: position, then separating normal with the distance in w.
struct hkContactPoint
{
	hkVector4 m_position;           // +0
	hkVector4 m_separatingNormal;   // +0x10 (w = separating distance)
};

// 0x14 bytes per contact point; the user-visible hkContactPointProperties part starts at +8.
struct hkContactPointProperties
{
	float m_solverData0;            // +0   (inferred) scratch written by buildJacobian
	float m_solverData1;            // +4   (inferred)
	int m_userData;                 // +8   start of the part handed to callbacks
	hkUint16 m_friction;            // +0xc (inferred) fixed point, scaled by 1/256
	hkUint8 m_restitution;          // +0xe (inferred) fixed point, scaled by 1/128
	hkUint8 m_flags;                // +0xf bit0 = needs update, bit1 = in solver
	float m_solverData4;            // +0x10 (inferred)
};

struct hkContactPointPropertiesPublic { int m_userData; hkUint16 m_friction; hkUint8 m_restitution; hkUint8 m_flags; };

// hkConstraintInfo (16 bytes): sizes the owner must reserve for this constraint.
struct hkConstraintInfo
{
	int m_maxSizeOfJacobians;   // +0
	int m_sizeOfJacobians;      // +4
	int m_sizeOfSchemas;        // +8
	int m_numSolverResults;     // +0xc
};

struct hkConstraintInstance;
struct hkCollidable { char m_pad[1]; };

struct hkCriticalSection
{
	void enter();                    // 0x0107F820
	char m_cs[24];
	uint64_t m_owner;                // +0x18, thread id while locked, -1 otherwise
	void leave()
	{
#if defined(_WIN32)
		m_owner = (uint64_t)-1;      // two dword stores of -1 in the binary
		LeaveCriticalSection((LPCRITICAL_SECTION)m_cs);
#endif
	}
};

// ---- minimal world / island / entity stubs (x86 offsets) ----------------------------------------------------------
struct hkSolverInfoWorld { char m_pad[0x70]; float m_contactRestingVelocity; };   // (inferred) float at +0x70
struct hkCollisionInputStub { char m_pad[0x24]; hkSolverInfoWorld* m_dynamicsInfo; }; // +0x24
struct hkWorld
{
	char m_pad0[0x78];
	hkCollisionInputStub* m_collisionInput;  // +0x78
};

struct hkWorldStub2
{
	char m_pad[0xac];
	hkCriticalSection* m_modifyConstraintCriticalSection;   // +0xac
};

// Owner reached through hkConstraintInstance+8; its +0x1c field points to something with a critical section at +0xac.
struct hkOwnerStub
{
	virtual void v0(); virtual void v1(); virtual void v2();
	virtual void addConstraintInfo(hkConstraintInstance* c, hkConstraintInfo& info);   // slot 3
	virtual void subConstraintInfo(hkConstraintInstance* c, hkConstraintInfo& info);   // slot 4
	uint32_t m_pad[6];                 // +4..+0x1b (x86)
	hkWorldStub2* m_world;             // +0x1c
};

struct hkMotion;
struct hkEntityStub;

// hkContactPointConfirmedEvent, 0x28 bytes inside the stack frame (esp+0x68..0x8c).
struct hkContactPointConfirmedEvent
{
	hkCollidable* m_collidableA;                      // +0 (entityA + 0x1c)
	hkCollidable* m_collidableB;                      // +4 (entityB + 0x1c)
	void* m_unused;                                   // +8 (never written here)
	hkContactPoint* m_contactPoint;                   // +0xc
	hkContactPointPropertiesPublic* m_properties;     // +0x10 (props + 8)
	int m_firstCallbackForFullManifold;               // +0x14 (0 here)
	float m_projectedVelocity;                        // +0x18
	int m_isConstraintCallback;                       // +0x1c (1 here)
	void* m_constraintData;                           // +0x20 (the hkSimpleContactConstraintData)
};

// hkSimpleConstraintUtilCollideParams, 0x24 bytes at esp+0x90 (inferred field names).
struct hkSimpleConstraintUtilCollideParams
{
	hkVector4 m_normalAndDistance;     // +0
	float m_friction;                  // +0x10
	float m_restitution;               // +0x14
	float m_velocityAlongNormal;       // +0x18
	float m_externalSeparatingVelocity;// +0x1c (0 here)
	float m_extraSeparatingVelocity;   // +0x20 (0 here)
};

// hkMotion: only the fields used here (x86 offsets).
struct hkVelocityAccumulator;
struct hkStepInfo;
struct hkMotion
{
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual hkVelocityAccumulator* buildAccumulator(const hkStepInfo& stepInfo, hkVelocityAccumulator* acc);   // slot 5 (inferred)
	virtual void integrateFromAccumulator(const hkStepInfo& stepInfo, hkVelocityAccumulator* acc);              // slot 6 (inferred)
	virtual int getSizeOfAccumulators();                                                                         // slot 7 (inferred)
	int m_accumulatorOffset;           // +8
	char m_pad[0xc0 - 0xc];
	float m_inverseMass;               // +0xc0
	char m_pad2[0xd0 - 0xc4];
	hkVector4 m_linearVelocity;        // +0xd0
	hkVector4 m_angularVelocity;       // +0xe0
};

struct hkEntityStub
{
	char m_pad0[8];
	hkWorld* m_world;                  // +8
	char m_pad1[0x1c - 0xc];
	hkCollidable m_collidable;         // +0x1c (address of this member is passed)
	char m_pad2[0x58 - 0x1d];
	hkMotion* m_motion;                // +0x58
	char m_pad3[0xa0 - 0x5c];
	void* m_contactListeners;          // +0xa0 first dword of the listener array (tested for non-zero)
};

struct hkConstraintInstance
{
	char m_pad0[8];
	hkOwnerStub* m_owner;              // +8 (hkSimpleConstraintOwner / simulation island)
	char m_pad1[4];
	hkEntityStub* m_entities[2];       // +0x10, +0x14
};

// hkVelocityAccumulator: 0x80 bytes. Only the fields touched here are named.
struct hkVelocityAccumulator
{
	hkUint8 m_type;                    // +0
	char m_pad1[0xf];
	float m_linearVelocity[4];         // +0x10
	float m_angularVelocity[4];        // +0x20
	char m_pad2[0x10];
	float m_stored[8];                 // +0x40: oneStepIntegrate stores the 8 floats of +0x10..+0x2f here; the
	                                   //        contact code reads the centre of mass at +0x40..+0x48 (inferred)
	char m_pad3[0x80 - 0x60];
};

// hkConstraintQueryIn (0x48 bytes copied by hkSoftContactConstraintData::buildJacobian).
struct hkConstraintQueryIn
{
	float m_deltaTime;                              // +0 (inferred: multiplies the -1.3 factor)
	char m_pad4[0x18 - 4];
	float m_softScaledA;                            // +0x18 scaled by hkSoftContactConstraintData (inferred)
	char m_pad1c[0x20 - 0x1c];
	hkVelocityAccumulator* m_bodyBuffer;            // +0x20 (inferred: accumulator buffer base)
	void* m_jacobianBuffer;                         // +0x24 (inferred: jacobian element buffer)
	hkVelocityAccumulator* m_accumulatorA;          // +0x28
	hkVelocityAccumulator* m_accumulatorB;          // +0x2c
	void* m_motionStateA;                           // +0x30
	void* m_motionStateB;                           // +0x34
	float m_softScaledB;                            // +0x38 (inferred)
	float m_softScaledC;                            // +0x3c (inferred)
	hkConstraintInstance* m_constraintInstance;     // +0x40
	int m_constraintFlags;                          // +0x44
};

struct hkJacobianSchema;
struct hkJacobianElement;
struct hkConstraintQueryOut
{
	hkJacobianElement* m_jacobians;    // +0
	hkJacobianSchema* m_schemas;       // +4
};

// ---- hkIdMgrA: id -> index table (hkArray<hkUint8>, 0xff = free slot) ---------------------------------------------
struct hkIdMgrA : hkArray<hkUint8>
{
	int newUid(hkUint8 value);          // 0x010A4290 (name inferred)
};

// ---- the constraint data classes -----------------------------------------------------------------------------------
class hkConstraintData
{
public:
	virtual ~hkConstraintData() {}          // slot 0
	virtual void slot1() {}                 // slot 1 (empty, hkReferencedObject)
	virtual void slot2();
	virtual void slot3();
	virtual void getRuntimeInfo();          // slot 4 (signature elided)
	virtual void slot5();
	virtual void addInstance(void*);        // slot 6 (signature elided)
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);   // slot 7
	short m_memSizeAndFlags;                // +4
	short m_referenceCount;                 // +6
};

class hkSimpleContactConstraintData : public hkConstraintData
{
public:
	hkSimpleContactConstraintData();                                    // 0x010A4620
	hkSimpleContactConstraintData(hkConstraintInstance* constraint);    // 0x010A45B0
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);   // 0x010A3ED0
	hkUint16 allocateContactPoint(hkContactPoint** cpOut, hkContactPointProperties** propsOut);   // 0x010A42F0
	void freeContactPoint(hkUint16 id);                                  // 0x010A4420

	int m_userData;                                 // +8
	hkIdMgrA m_idMgrA;                              // +0xc (data), +0x10 size, +0x14 capacity|flags
	hkUint8 m_idMgrAStorage[8];                     // +0x18 inplace storage of m_idMgrA
	hkArray<hkContactPoint> m_contactPoints;        // +0x20
	float m_softScale;                              // +0x2c padding in the base class; used by hkSoftContactConstraintData
	int m_pad30;                                    // +0x30 never written by the constructors
	hkConstraintInstance* m_constraint;             // +0x34
	hkArray<hkContactPointProperties> m_contactPointProperties;   // +0x38
	hkUint8 m_flags;                                // +0x44 bit1 = new contact points pending, bit2/bit0 dirty flags
	hkUint8 m_flags2;                               // +0x45
	hkUint16 m_atomSizeFlags;                       // +0x46 (3)
	int m_pad48[7];                                 // +0x48..+0x63
};

// hkBodyVelocity: linear then angular velocity (8 floats).
struct hkBodyVelocity { float m_linear[4]; float m_angular[4]; };
struct hkSimpleConstraintInfoInitInput;

class hkSoftContactConstraintData : public hkSimpleContactConstraintData
{
public:
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);   // 0x010A4680
	virtual void toiCollisionResponseEndCallback(const hkContactPoint& cp, float m, hkSimpleConstraintInfoInitInput& inA,
	                                             hkBodyVelocity& velA, hkSimpleConstraintInfoInitInput& inB, hkBodyVelocity& velB);   // 0x010A46F0
	virtual void toiCollisionResponseBeginCallback(const hkContactPoint& cp, hkSimpleConstraintInfoInitInput& inA,
	                                               hkBodyVelocity& velA, hkSimpleConstraintInfoInitInput& inB, hkBodyVelocity& velB);   // 0x010A4850

	// File-scope statics at 0x016E5090 (A), 0x016E50B0 (B), 0x016E50D0 (flag); names inferred.
	static hkBodyVelocity s_toiVelocityA;
	static hkBodyVelocity s_toiVelocityB;
	static hkUint8 s_toiActive;
};

hkBodyVelocity hkSoftContactConstraintData::s_toiVelocityA;
hkBodyVelocity hkSoftContactConstraintData::s_toiVelocityB;
hkUint8 hkSoftContactConstraintData::s_toiActive;

// ---- external callees ------------------------------------------------------------------------------------------------
struct hkRigidAccumulator;
struct hkSolveSingleOutput { int m_pad; };
struct hkWorldCallbackUtil { static void fireContactPointConfirmed(hkWorld* world, hkContactPointConfirmedEvent& e); };   // 0x0109F0D0
struct hkEntityCallbackUtil { static void fireContactPointConfirmedInternal(hkEntityStub* e, hkContactPointConfirmedEvent& ev); };   // 0x0109E850
struct hkSimpleCollisionResponse
{
	// 0x010A6B50
	static void solveSingleContact2(const hkContactPoint& cp, const hkSimpleConstraintUtilCollideParams& params,
	                                hkEntityStub* bodyA, hkEntityStub* bodyB, hkVelocityAccumulator* accA,
	                                hkVelocityAccumulator* accB, hkSimpleContactConstraintData& data, hkSolveSingleOutput& out);
};
// 0x010A7720: post-pass after the contact points are processed (name unknown); cdecl.
void hkSimpleContactConstraintData_buildJacobianPass(hkContactPoint* points, int numPoints, hkContactPointProperties* props,
                                                     hkUint8* flags, const hkConstraintQueryIn* in, hkConstraintQueryOut* out);
// 0x010B48B0 (name unknown): cdecl, five args.
void hkConstraintSolverSetup_zeroFromSchemas(void* solverInfo, char* a, void* b, void* c, void* d);

// ===========================================================================================================================

// @ 0x010a3ed0
void hkSimpleContactConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	int numPoints = m_contactPoints.m_size;
	if (m_flags & 2)
	{
		hkContactPoint* cp = m_contactPoints.m_data;
		hkContactPointProperties* props = m_contactPointProperties.m_data;
		for (int remaining = numPoints; remaining > 0; --remaining, ++cp, ++props)
		{
			if (!(props->m_flags & 1))
				continue;

			hkEntityStub* entityA = in.m_constraintInstance->m_entities[0];
			hkEntityStub* entityB = in.m_constraintInstance->m_entities[1];
			hkMotion* motionA = entityA->m_motion;
			hkMotion* motionB = entityB->m_motion;
			const float* comA = (const float*)((const char*)in.m_accumulatorA + 0x40);
			const float* comB = (const float*)((const char*)in.m_accumulatorB + 0x40);

			// X87-PRECISION: the relative positions stay unrounded on the FPU stack; each cross product is rounded
			// when it is stored to a float slot, then the velocity of the point is added.
			hkX87Real rAx = (hkX87Real)cp->m_position.x - comA[0];
			hkX87Real rAy = (hkX87Real)cp->m_position.y - comA[1];
			hkX87Real rAz = (hkX87Real)cp->m_position.z - comA[2];
			float crossAx = (float)(rAz * motionA->m_angularVelocity.y - rAy * motionA->m_angularVelocity.z);
			float crossAy = (float)(rAx * motionA->m_angularVelocity.z - rAz * motionA->m_angularVelocity.x);
			hkX87Real crossAz = rAy * motionA->m_angularVelocity.x - rAx * motionA->m_angularVelocity.y;
			// X87-PRECISION: only the x component of body A's point velocity stays unrounded (y and z are stored).
			hkX87Real velAx = (hkX87Real)crossAx + motionA->m_linearVelocity.x;
			float velAy = (float)((hkX87Real)crossAy + motionA->m_linearVelocity.y);
			float velAz = (float)(crossAz + motionA->m_linearVelocity.z);

			hkX87Real rBx = (hkX87Real)cp->m_position.x - comB[0];
			hkX87Real rBy = (hkX87Real)cp->m_position.y - comB[1];
			hkX87Real rBz = (hkX87Real)cp->m_position.z - comB[2];
			float crossBx = (float)(rBz * motionB->m_angularVelocity.y - rBy * motionB->m_angularVelocity.z);
			float crossBy = (float)(rBx * motionB->m_angularVelocity.z - rBz * motionB->m_angularVelocity.x);
			hkX87Real crossBz = rBy * motionB->m_angularVelocity.x - rBx * motionB->m_angularVelocity.y;
			float velBx = (float)((hkX87Real)crossBx + motionB->m_linearVelocity.x);
			float velBy = (float)((hkX87Real)crossBy + motionB->m_linearVelocity.y);
			float velBz = (float)(crossBz + motionB->m_linearVelocity.z);   // z cross is NOT stored before the add

			// X87-PRECISION: relative velocity and its dot with the normal are formed on the FPU stack.
			hkX87Real relX = velAx - velBx;
			hkX87Real relY = (hkX87Real)velAy - velBy;
			hkX87Real relZ = (hkX87Real)velAz - velBz;
			float projVel = (float)((relY * cp->m_separatingNormal.y + relX * cp->m_separatingNormal.x) +
			                        relZ * cp->m_separatingNormal.z);

			hkContactPointConfirmedEvent ev;
			ev.m_collidableA = &entityA->m_collidable;
			ev.m_collidableB = &entityB->m_collidable;
			ev.m_contactPoint = cp;
			ev.m_properties = (hkContactPointPropertiesPublic*)((char*)props + 8);
			ev.m_firstCallbackForFullManifold = 0;
			ev.m_projectedVelocity = projVel;
			ev.m_isConstraintCallback = 1;
			ev.m_constraintData = this;

			hkWorld* world = entityA->m_world;
			hkWorldCallbackUtil::fireContactPointConfirmed(world, ev);
			if (entityA->m_contactListeners != 0)
				hkEntityCallbackUtil::fireContactPointConfirmedInternal(entityA, ev);
			if (entityB->m_contactListeners != 0)
				hkEntityCallbackUtil::fireContactPointConfirmedInternal(entityB, ev);

			// restitution: byte * 1/128 (exact in float, power of two)
			float restitution = (float)props->m_restitution * 0.0078125f;
			// binary: fcomp / test ah,0x41 -> taken when (-threshold <= v) or unordered, or restitution <= 0.3 or unordered
			float negThreshold = -world->m_collisionInput->m_dynamicsInfo->m_contactRestingVelocity;
			if (negThreshold > ev.m_projectedVelocity && restitution > 0.3f) // NaN falls to the else branch, as the fcomp/test ah,0x41 pairs do
			{
				hkSimpleConstraintUtilCollideParams params;
				params.m_normalAndDistance.x = cp->m_separatingNormal.x;
				params.m_normalAndDistance.y = cp->m_separatingNormal.y;
				params.m_normalAndDistance.z = cp->m_separatingNormal.z;
				params.m_normalAndDistance.w = cp->m_separatingNormal.w;
				params.m_friction = (float)props->m_friction * 0.00390625f;
				params.m_restitution = restitution;
				params.m_velocityAlongNormal = ev.m_projectedVelocity;
				params.m_externalSeparatingVelocity = 0.0f;
				params.m_extraSeparatingVelocity = 0.0f;
				hkSolveSingleOutput solveOut;
				hkSimpleCollisionResponse::solveSingleContact2(*cp, params, entityA, entityB, in.m_accumulatorA,
				                                               in.m_accumulatorB, *this, solveOut);
				props->m_solverData0 = 0.0f;
				props->m_solverData4 = cp->m_separatingNormal.w;
			}
			else
			{
				// X87-PRECISION: mass term and the following products stay on the FPU stack (rounded only when stored).
				hkX87Real sumInvMass = (hkX87Real)motionB->m_inverseMass + motionA->m_inverseMass;
				hkX87Real recip = 1.0f / (sumInvMass + 1.00000001335143196e-10f);  // 0x2edbe6ff
				hkX87Real r = (recip * (restitution + 1.0f));
				props->m_solverData0 = (float)(((r * ev.m_projectedVelocity)) * -0.2f);
				hkX87Real t = (((hkX87Real)props->m_restitution * in.m_deltaTime) * ev.m_projectedVelocity) * 0.0078125f;
				hkX87Real v1 = t * -1.3f;   // fst stores a rounded copy; the unrounded value feeds the next fadd
				props->m_solverData1 = (float)v1;
				props->m_solverData4 = (float)(v1 + cp->m_separatingNormal.w);
			}
			props->m_flags &= 0xfe;
		}
		m_flags &= 0xfd;
	}
	hkSimpleContactConstraintData_buildJacobianPass(m_contactPoints.m_data, numPoints, m_contactPointProperties.m_data,
	                                                &m_flags, &in, &out);
}

// @ 0x010a4290
int hkIdMgrA::newUid(hkUint8 value)
{
	// Reuse the highest free slot (0xff) if there is one, otherwise append.
	for (int i = m_size - 1; i >= 0; --i)
	{
		if (m_data[i] == 0xff)
		{
			m_data[i] = value;
			return i;
		}
	}
	if (m_size == (m_capacityAndFlags & CAPACITY_MASK))
		hkArrayUtil::_reserveMore(this, 1);
	m_data[m_size] = value;
	int idx = m_size;
	m_size = idx + 1;
	return idx;
}

// @ 0x010a42f0
hkUint16 hkSimpleContactConstraintData::allocateContactPoint(hkContactPoint** cpOut, hkContactPointProperties** propsOut)
{
	int numProps = m_contactPointProperties.m_size;
	hkConstraintInfo info;
	info.m_maxSizeOfJacobians = numProps * 0x30 + 0xb0;
	info.m_sizeOfJacobians = 0;
	info.m_sizeOfSchemas = 0;
	if (numProps == 1)
	{
		info.m_sizeOfSchemas = 4;
		info.m_sizeOfJacobians = 0x20;
	}
	info.m_sizeOfSchemas += 4;
	info.m_sizeOfJacobians += 0x30;
	info.m_numSolverResults = (numProps == 1) + 1;

	hkOwnerStub* owner = m_constraint->m_owner;
	hkCriticalSection* cs = owner->m_world->m_modifyConstraintCriticalSection;
	if (cs != 0)
	{
		cs->enter();
		m_constraint->m_owner->addConstraintInfo(m_constraint, info);
		cs->leave();
	}
	else
	{
		owner->addConstraintInfo(m_constraint, info);
	}

	m_flags |= 6;
	int oldCount = m_contactPoints.m_size;
	hkContactPoint* newPoint = m_contactPoints.expandOne();
	hkContactPointProperties* newProps = m_contactPointProperties.expandOne();
	newProps->m_solverData0 = 0.0f;
	newProps->m_solverData1 = 0.0f;
	newProps->m_flags = 1;
	if (oldCount > 0 && !(newProps[-1].m_flags & 2))
		newProps->m_flags = 3;
	*cpOut = newPoint;
	*propsOut = newProps;
	return (hkUint16)m_idMgrA.newUid((hkUint8)oldCount);
}

// @ 0x010a4420
void hkSimpleContactConstraintData::freeContactPoint(hkUint16 id)
{
	int idx = m_idMgrA.m_data[id];
	m_idMgrA.m_data[id] = 0xff;

	hkConstraintInfo info;
	info.m_maxSizeOfJacobians = 0;
	info.m_sizeOfJacobians = 0;
	info.m_sizeOfSchemas = 0;
	info.m_numSolverResults = 0;
	int oldProps = m_contactPointProperties.m_size;
	if (oldProps == 2)
	{
		info.m_sizeOfSchemas = 4;
		info.m_sizeOfJacobians = 0x20;
		info.m_numSolverResults = 1;
	}

	// remove the properties entry (the contact point array is only shortened, exactly as in the binary)
	m_contactPointProperties.m_size = oldProps - 1;
	for (int i = idx; i < m_contactPointProperties.m_size; ++i)
		m_contactPointProperties.m_data[i] = m_contactPointProperties.m_data[i + 1];
	m_contactPointProperties.m_data[idx].m_flags &= 0xfd;
	m_contactPoints.m_size = m_contactPoints.m_size - 1;

	// hkArray::optimizeCapacity-style shrink checks
	if (m_contactPointProperties.m_size * 2 + 2 <= (m_contactPointProperties.m_capacityAndFlags & hkArray<int>::CAPACITY_MASK))
		hkArrayUtil::_reduce(&m_contactPointProperties, (int)sizeof(hkContactPointProperties), 0, 0);
	if (m_contactPoints.m_size * 2 + 2 <= (m_contactPoints.m_capacityAndFlags & hkArray<int>::CAPACITY_MASK))
		hkArrayUtil::_reduce(&m_contactPoints, (int)sizeof(hkContactPoint), 0, 0);

	// ids that pointed behind the removed entry move down by one
	for (int j = m_idMgrA.m_size - 1; j >= 0; --j)
	{
		hkUint8* p = &m_idMgrA.m_data[j];
		if (*p != 0xff && (int)*p > idx)
			--*p;
	}

	info.m_sizeOfSchemas += 4;
	info.m_sizeOfJacobians += 0x30;
	info.m_numSolverResults += 1;

	hkOwnerStub* owner = m_constraint->m_owner;
	hkCriticalSection* cs = owner->m_world->m_modifyConstraintCriticalSection;
	if (cs != 0)
	{
		cs->enter();
		m_constraint->m_owner->subConstraintInfo(m_constraint, info);
		cs->leave();
		m_flags |= 5;
		return;
	}
	owner->subConstraintInfo(m_constraint, info);
	m_flags |= 5;
}

// @ 0x010a45b0
hkSimpleContactConstraintData::hkSimpleContactConstraintData(hkConstraintInstance* constraint)
{
	m_referenceCount = 1;
	m_userData = 0;
	m_idMgrA.m_size = 0;
	m_idMgrA.m_capacityAndFlags = (int)0x80000008;
	m_idMgrA.m_data = m_idMgrAStorage;
	m_contactPoints.m_data = 0;
	m_contactPoints.m_size = 0;
	m_contactPoints.m_capacityAndFlags = (int)0x80000000;
	m_contactPointProperties.m_data = 0;
	m_contactPointProperties.m_size = 0;
	m_contactPointProperties.m_capacityAndFlags = (int)0x80000000;
	*(hkUint16*)&m_flags = 0;           // m_flags and m_flags2
	m_atomSizeFlags = 3;
	for (int i = 0; i < 7; ++i)
		m_pad48[i] = 0;
	m_constraint = constraint;
}

// @ 0x010a4620
hkSimpleContactConstraintData::hkSimpleContactConstraintData()
{
	m_referenceCount = 1;
	m_userData = 0;
	m_idMgrA.m_size = 0;
	m_idMgrA.m_capacityAndFlags = (int)0x80000008;
	m_idMgrA.m_data = m_idMgrAStorage;
	m_contactPoints.m_data = 0;
	m_contactPoints.m_size = 0;
	m_contactPoints.m_capacityAndFlags = (int)0x80000000;
	m_contactPointProperties.m_data = 0;
	m_contactPointProperties.m_size = 0;
	m_contactPointProperties.m_capacityAndFlags = (int)0x80000000;
	*(hkUint16*)&m_flags = 0;
	m_atomSizeFlags = 3;
	for (int i = 0; i < 7; ++i)
		m_pad48[i] = 0;
	m_constraint = 0;
}

// @ 0x010a4680
void hkSoftContactConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	float scale = m_softScale;
	hkConstraintQueryIn local = in;          // 0x12 dwords (rep movsd)
	local.m_softScaledA = local.m_softScaledA * scale;
	local.m_softScaledB = local.m_softScaledB * scale;
	local.m_softScaledC = local.m_softScaledC * scale;
	hkSimpleContactConstraintData::buildJacobian(local, out);   // non-virtual call to 0x010a3ed0
}

// @ 0x010a46f0
void hkSoftContactConstraintData::toiCollisionResponseEndCallback(const hkContactPoint&, float, hkSimpleConstraintInfoInitInput&,
                                                                  hkBodyVelocity& velA, hkSimpleConstraintInfoInitInput&,
                                                                  hkBodyVelocity& velB)
{
	float s = m_softScale;
	// X87-PRECISION: 1.0 - s stays unrounded on the FPU stack, and so do the two products of each blend.
	hkX87Real u = 1.0f - s;
	for (int i = 0; i < 4; ++i)
		velA.m_linear[i] = (float)(s * velA.m_linear[i] + s_toiVelocityA.m_linear[i] * u);
	for (int i = 0; i < 4; ++i)
		velA.m_angular[i] = (float)(s * velA.m_angular[i] + s_toiVelocityA.m_angular[i] * u);
	for (int i = 0; i < 4; ++i)
		velB.m_linear[i] = (float)(s * velB.m_linear[i] + s_toiVelocityB.m_linear[i] * u);
	for (int i = 0; i < 4; ++i)
		velB.m_angular[i] = (float)(s * velB.m_angular[i] + s_toiVelocityB.m_angular[i] * u);
	s_toiActive = 0;
}

// @ 0x010a4850
void hkSoftContactConstraintData::toiCollisionResponseBeginCallback(const hkContactPoint&, hkSimpleConstraintInfoInitInput&,
                                                                    hkBodyVelocity& velA, hkSimpleConstraintInfoInitInput&,
                                                                    hkBodyVelocity& velB)
{
	s_toiActive = 1;
	s_toiVelocityA = velA;   // 8 dwords
	s_toiVelocityB = velB;
}

// ---- hkConstraintSolverSetup -----------------------------------------------------------------------------------------
// hkConstraintSolverResources: 0x50 bytes of buffer bookkeeping. Dwords 3.. hold buffer ADDRESSES (char*), so the
// 64-bit layout differs; index = (x86 offset)/4.
struct hkConstraintSolverResources
{
	const hkStepInfo* m_stepInfo;       // 0
	void* m_solverInfo;                 // 1
	hkConstraintQueryIn* m_queryIn;     // 2
	char* m_p[17];                      // dwords 3..19 (m_p[k-3])
};
#define HK_RES(r, k) ((r).m_p[(k) - 3])

struct hkSolverInfo
{
	// Only the sizes that the buffer layout function reads (x86 offsets; names inferred).
	char m_pad0[0xc];
	int m_sizeC;                        // +0xc
	int m_size10;                       // +0x10
	int m_size14;                       // +0x14
	int m_numSolverResults;             // +0x18
	char m_pad1c[0x40 - 0x1c];
	int m_numAccumulators;              // +0x40
};

// Result of hkConstraintSolverSetup_layoutBuffer: sizes (when buffer == 0) or addresses (inside a buffer).
struct hkSolverBufferLayout
{
	uintptr_t m_buffer;       // 0
	uintptr_t m_end;          // 1 (total size when m_buffer == 0)
	uintptr_t m_accumulators; // 2
	uintptr_t m_elements;     // 3
	uintptr_t m_schemas;      // 4
	uintptr_t m_results;      // 5
	uintptr_t m_pad6, m_pad7;
};

static inline void hkVelocityAccumulator_setFixed(hkUint8* p)
{
	// 0x80-byte accumulator for fixed bodies: byte 0 = 1 (type), byte 0xc = 1, all dwords from +0x10 cleared.
	p[0] = 1;
	p[0xc] = 1;
	uint32_t* d = (uint32_t*)p;
	for (int i = 4; i < 32; ++i)
		d[i] = 0;
}

static inline uintptr_t hkAlign16(uintptr_t v) { return v & ~(uintptr_t)15; }

// @ 0x010a48f0
void hkConstraintSolverSetup_initializeSolverState(hkStepInfo& stepInfo, hkSolverInfo& solverInfo, hkConstraintQueryIn& in,
                                                   char* buffer, int bufferSize, hkConstraintSolverResources& res)
{
	res.m_stepInfo = &stepInfo;
	res.m_solverInfo = &solverInfo;
	res.m_queryIn = &in;

	int n = bufferSize - bufferSize % 16;      // sign-corrected remainder idiom in the binary
	int q1 = (n * 10) / 0x3c;
	int q2 = (n * 0x1e) / 0x3c;

	uintptr_t b0 = ((uintptr_t)buffer + 0xf) & ~(uintptr_t)0xf;
	HK_RES(res, 3) = (char*)b0;
	uintptr_t t4 = hkAlign16(q1 + b0 + 0xf);
	uintptr_t t6 = hkAlign16(q2 + t4 + 0xf);
	HK_RES(res, 4) = (char*)t4;
	HK_RES(res, 5) = (char*)t4;
	uintptr_t t8 = hkAlign16(q1 + t6 + 0xf);
	HK_RES(res, 6) = (char*)t6;
	HK_RES(res, 7) = (char*)t6;
	HK_RES(res, 8) = (char*)t8;
	HK_RES(res, 9) = (char*)t8;
	// X87-PRECISION: fild of n*10 times -0.01f, kept unrounded, then _ftol2 (truncation).
	int c = (int)((hkX87Real)(n * 10) * -0.0100000007078051567f);   // constant 0xbc23d70b @ 0x014a22c4
	uintptr_t t10 = hkAlign16((uintptr_t)((intptr_t)t8 - c) + 0xf);
	HK_RES(res, 0xe) = buffer + n;
	HK_RES(res, 0xa) = (char*)t10;
	HK_RES(res, 0xd) = (char*)t10;
	HK_RES(res, 0xf) = (char*)t10;
	HK_RES(res, 0x10) = (char*)t10;
	HK_RES(res, 0x11) = HK_RES(res, 3);
	HK_RES(res, 0x12) = HK_RES(res, 5);
	HK_RES(res, 0x13) = HK_RES(res, 7);
	HK_RES(res, 0xb) = HK_RES(res, 9);
	HK_RES(res, 0xc) = HK_RES(res, 9);
}

// @ 0x010a49e0   (name inferred)
void hkConstraintSolverSetup_resetSolverBuffers(hkConstraintSolverResources& res, int keepExisting)
{
	for (uint32_t* p = (uint32_t*)HK_RES(res, 7); p < (uint32_t*)HK_RES(res, 0x13); ++p)
		*p = 0;
	if (keepExisting == 0)
	{
		HK_RES(res, 0xc) = HK_RES(res, 9);
		HK_RES(res, 0x10) = HK_RES(res, 0xd);
	}
	if (HK_RES(res, 0xc) != HK_RES(res, 0xb))
		hkConstraintSolverSetup_zeroFromSchemas(res.m_solverInfo, HK_RES(res, 0xc), HK_RES(res, 3), HK_RES(res, 5), HK_RES(res, 7));
	if (HK_RES(res, 0x10) != HK_RES(res, 0xf))
		hkConstraintSolverSetup_zeroFromSchemas(res.m_solverInfo, HK_RES(res, 0x10), HK_RES(res, 3), HK_RES(res, 5), HK_RES(res, 7));
	HK_RES(res, 0xc) = HK_RES(res, 0xb);
	HK_RES(res, 0x10) = HK_RES(res, 0xf);
}

// @ 0x010a4a70   (name inferred; cdecl; the third argument is unused)
void hkConstraintSolverSetup_layoutBuffer(const hkSolverInfo* info, uintptr_t base, void* /*unused*/, hkSolverBufferLayout* out)
{
	out->m_buffer = base;
	out->m_accumulators = base;
	out->m_elements = base + 0x90 + info->m_size14;
	out->m_results = out->m_elements + info->m_sizeC;
	out->m_schemas = out->m_results + info->m_numSolverResults * 4 + 8;
	out->m_end = (info->m_size10 - out->m_buffer) + 4 + out->m_schemas;
	if (out->m_buffer != 0)
	{
		hkUint8* acc = (hkUint8*)out->m_accumulators;
		hkVelocityAccumulator_setFixed(acc);
		acc[(info->m_numAccumulators + 1) * 0x80] = 2;
	}
}

// @ 0x010a4b30   (name inferred) size query: layout with a null buffer
void hkConstraintSolverSetup_calcBufferSize(const hkSolverInfo* info)
{
	hkSolverBufferLayout tmp;
	hkConstraintSolverSetup_layoutBuffer(info, 0, 0, &tmp);
}

struct hkConstraintSolverSetup
{
	static void buildAccumulatorBatch(const hkStepInfo& stepInfo, hkEntityStub* const* entities, int from, int to, hkVelocityAccumulator* base);
	static void buildJacobianElementBatch(hkConstraintQueryIn& in, struct hkConstraintInternal** internals, int n,
	                                      hkVelocityAccumulator* base, hkJacobianSchema* schemas, hkJacobianElement* elements,
	                                      hkJacobianSchema* last);
	static void oneStepIntegrate(const hkStepInfo& stepInfo, hkEntityStub** entities, int n, hkVelocityAccumulator* base);
	static void internalAddAccumulators(hkConstraintSolverResources& res, hkEntityStub** entities, int n);
	static hkBool internalIsMemoryOkForNewAccumulators(hkConstraintSolverResources& res, hkEntityStub** entities, int n);
};

// @ 0x010a4b50
void hkConstraintSolverSetup::buildAccumulatorBatch(const hkStepInfo& stepInfo, hkEntityStub* const* entities, int from, int to,
                                                    hkVelocityAccumulator* base)
{
	char* acc = (char*)base + (from + 1) * 0x80;
	for (hkEntityStub* const* p = entities + from; p < entities + to; ++p)
	{
		hkMotion* motion = (*p)->m_motion;
		int offset = (int)(acc - (char*)base);
		if (motion->m_accumulatorOffset != offset)
			motion->m_accumulatorOffset = offset;
		acc = (char*)motion->buildAccumulator(stepInfo, (hkVelocityAccumulator*)acc);
	}
}

// hkConstraintInternal: fields used by buildJacobianElementBatch (x86 offsets, 0x1c+ bytes).
struct hkConstraintInternal
{
	hkConstraintInstance* m_constraint;   // +0
	hkEntityStub* m_entities[2];          // +4, +8
	hkConstraintData* m_data;             // +0xc
	int m_pad10, m_pad14;
	int m_atomFlags;                      // +0x18 (copied to hkConstraintQueryIn::+0x44)
};

// @ 0x010a4bb0
void hkConstraintSolverSetup::buildJacobianElementBatch(hkConstraintQueryIn& in, hkConstraintInternal** internals, int n,
                                                        hkVelocityAccumulator* base, hkJacobianSchema* schemas,
                                                        hkJacobianElement* elements, hkJacobianSchema* last)
{
	in.m_jacobianBuffer = elements;
	hkConstraintInternal** end = internals + n;
	in.m_bodyBuffer = base;
	hkConstraintQueryOut out;
	out.m_jacobians = elements;
	out.m_schemas = schemas;
	for (; internals < end; ++internals)
	{
		hkConstraintInternal* ci = *internals;
		hkMotion* motionA = ci->m_entities[0]->m_motion;
		hkMotion* motionB = ci->m_entities[1]->m_motion;
		in.m_accumulatorA = (hkVelocityAccumulator*)((char*)base + motionA->m_accumulatorOffset);
		in.m_motionStateA = (char*)motionA + 0x10;
		in.m_motionStateB = (char*)motionB + 0x10;
		in.m_accumulatorB = (hkVelocityAccumulator*)((char*)base + motionB->m_accumulatorOffset);
		in.m_constraintInstance = ci->m_constraint;
		in.m_constraintFlags = ci->m_atomFlags;
		ci->m_data->buildJacobian(in, out);
	}
	if (last == 0)
		*(int*)out.m_schemas = 0;   // schema-stream terminator, written at the cursor the callees advanced
}

// @ 0x010a4c60   (name inferred)
void hkConstraintSolverSetup_integrateBatch(const hkStepInfo& stepInfo, hkEntityStub** entities, int n, hkVelocityAccumulator* base)
{
	for (hkEntityStub** p = entities; p < entities + n; ++p)
	{
		hkMotion* motion = (*p)->m_motion;
		motion->integrateFromAccumulator(stepInfo, (hkVelocityAccumulator*)((char*)base + motion->m_accumulatorOffset));
	}
}

// @ 0x010a4ca0
void hkConstraintSolverSetup::oneStepIntegrate(const hkStepInfo& stepInfo, hkEntityStub** entities, int n, hkVelocityAccumulator* base)
{
	for (hkEntityStub** p = entities; p < entities + n; ++p)
	{
		hkMotion* motion = (*p)->m_motion;
		hkVelocityAccumulator* acc = (hkVelocityAccumulator*)((char*)base + motion->m_accumulatorOffset);
		// copy the 8 floats at +0x10..+0x2f to +0x40..+0x5f
		for (int i = 0; i < 4; ++i)
			acc->m_stored[i] = acc->m_linearVelocity[i];
		for (int i = 0; i < 4; ++i)
			acc->m_stored[4 + i] = acc->m_angularVelocity[i];
		motion->integrateFromAccumulator(stepInfo, acc);
	}
}

// @ 0x010a4d10
void hkConstraintSolverSetup::internalAddAccumulators(hkConstraintSolverResources& res, hkEntityStub** entities, int n)
{
	hkEntityStub** end = entities + n;
	char* acc = HK_RES(res, 0x11);
	if (acc == HK_RES(res, 3))
	{
		hkVelocityAccumulator_setFixed((hkUint8*)acc);
		acc += 0x80;
		HK_RES(res, 0x11) = acc;
	}
	for (; entities < end; ++entities)
	{
		hkMotion* motion = (*entities)->m_motion;
		const hkStepInfo* step = res.m_stepInfo;
		int offset = (int)(acc - HK_RES(res, 3));
		if (motion->m_accumulatorOffset != offset)
			motion->m_accumulatorOffset = offset;
		acc = (char*)motion->buildAccumulator(*step, (hkVelocityAccumulator*)acc);
		HK_RES(res, 0x11) = acc;
	}
	*(hkUint8*)acc = 2;
}

// @ 0x010a4de0
hkBool hkConstraintSolverSetup::internalIsMemoryOkForNewAccumulators(hkConstraintSolverResources& res, hkEntityStub** entities, int n)
{
	uintptr_t cur = (uintptr_t)HK_RES(res, 0x11);
	hkEntityStub** end = entities + n;
	if (cur == (uintptr_t)HK_RES(res, 3))
		cur += 0x80;
	uintptr_t limit = (uintptr_t)HK_RES(res, 4) - 0x10;
	for (; entities < end; ++entities)
	{
		cur += (uintptr_t)(*entities)->m_motion->getSizeOfAccumulators();
		if (cur > limit)
			return hkBool(false);
	}
	return hkBool(true);
}
