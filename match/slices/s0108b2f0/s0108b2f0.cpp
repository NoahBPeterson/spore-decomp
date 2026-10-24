// Slice s0108b2f0: hkLimitedHingeConstraintData::buildJacobian (Havok 3.1.0, 0x0108b2f0, 1763 bytes).
// Flags: /O2 /MD /Gy /TP /fp:fast.
//
// Layouts: match/include/havok31/hkReflectedClasses.h (hkLimitedHingeConstraintData 0x90 bytes: min/max angle
// +0xc/+0x10, max friction torque +0x14, angular limits tau factor +0x18, basisA {pivot, axle, perpToAxle1,
// perpToAxle2} +0x20, basisB {pivot, axle, perp2FreeAxis} +0x60). The runtime block and the info structs for
// the hk1d* builders were read off the stores in the asm; names follow Havok 6.x where they exist.
//
// Steps: frame A and B to world; two angular bilateral rows (A's perpendicular axes against B's axle); the
// hinge angle (atan2 of B's free perpendicular against A's perp1 and axle x ...) unwrapped against the angle
// kept in the runtime (+0x38); the angular limit row; the ball-socket rows; optional angular friction row.
//
// Havok 3.1 was built by an older cl: x87 scheduling differs, behaviourally equivalent, not byte-exact.
#include "types.h"

typedef float hkReal;

extern const float kZero;   // 0x01485378

class __declspec(align(16)) hkVector4
{
public:
	float x, y, z, w;
	__forceinline hkVector4& operator=(const hkVector4& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
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

class hkSolverResults
{ public:
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
	void* m_jacobians;              // +0x00
	int32_t m_numSolverResults;     // +0x04
	int32_t m_numSolverElemTemps;   // +0x08
};

// in.m_constraintRuntime (0x3c bytes): solver results of the rows, friction row at +0x30, previous hinge angle.
struct hkLimitedHingeRuntime
{
	hkSolverResults m_solverResults[7];     // +0x00
	hkReal m_previousAngle;                 // +0x38
};

struct hk1dAngularFrictionInfo
{
	const hkVector4* m_constrainedDofW;     // +0x00
	hkSolverResults* m_lastSolverResults;   // +0x04
	hkReal m_maxFrictionTorque;             // +0x08
	int m_numFriction;                      // +0x0c
};

struct hk1dAngularLimitInfo
{
	hkVector4 m_constrainedDofW;   // +0x00
	hkReal m_min;                  // +0x10
	hkReal m_max;                  // +0x14
	hkReal m_computedAngle;        // +0x18
	hkReal m_tau;                  // +0x1c
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
extern "C" void hk1dAngularFrictionBuildJacobian(const hk1dAngularFrictionInfo& info, const hkConstraintQueryIn& in,
                                                 hkConstraintQueryOut& out);                               // 0x010AA3C0
extern "C" void hk1dAngularLimitBuildJacobian(const hk1dAngularLimitInfo& info, const hkConstraintQueryIn& in,
                                              hkConstraintQueryOut& out);                                  // 0x010AB0E0
// 0x010AB2D0 (name guessed): the 3-row ball-socket jacobian between the two world pivots.
extern "C" void hkBallSocketBuildJacobian(const hkVector4& pivotA, const hkVector4& pivotB,
                                          const hkConstraintQueryIn& in, hkConstraintQueryOut& out);
namespace hkMath { float atan2fApproximation(float y, float x); }     // 0x0120adb0 (cdecl)

extern const float kPi;      // 0x0149e210
extern const float kTwoPi;   // 0x01446dec

struct hkLimitedHingeBasisA
{
	hkVector4 m_pivot;          // +0x00
	hkVector4 m_axle;           // +0x10
	hkVector4 m_perpToAxle1;    // +0x20
	hkVector4 m_perpToAxle2;    // +0x30
};

struct hkLimitedHingeBasisB
{
	hkVector4 m_pivot;          // +0x00
	hkVector4 m_axle;           // +0x10
	hkVector4 m_perp2FreeAxis;  // +0x20
};

class hkBaseRef
{
public:
	uint16_t m_memSizeAndFlags;         // +0x04
	uint16_t m_referenceCount;          // +0x06

	// The size-and-flags word is written by the allocator before construction.
	hkBaseRef() : m_referenceCount(1) {}
	virtual ~hkBaseRef() {}
	void addReference();                                                    // 0x01082590
	// Inlined by retail inside ~hkConstraintInstance.
	void removeReference()
	{
		if (m_memSizeAndFlags) {
			if (--m_referenceCount == 0)
				delete this;
		}
	}
};

class hkConstraintData : public hkBaseRef
{
public:
	uint32_t m_userData;                // +0x08

	hkConstraintData() : m_userData(0) {}
	virtual ~hkConstraintData() {}
};

class hkLimitedHingeConstraintData : public hkConstraintData
{
public:
	hkReal m_minAngle;                  // +0x0c
	hkReal m_maxAngle;                  // +0x10
	hkReal m_maxFrictionTorque;         // +0x14
	hkReal m_angularLimitsTauFactor;    // +0x18
	hkLimitedHingeBasisA m_basisA;      // +0x20
	hkLimitedHingeBasisB m_basisB;      // +0x60

	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void vslot6();
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);
};

// @ 0x0108b2f0
void hkLimitedHingeConstraintData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	hkLimitedHingeRuntime* runtime = (hkLimitedHingeRuntime*)in.m_constraintRuntime;
	hkBeginConstraints(in, out, runtime->m_solverResults, 8);

	// frame A in world: axle, perp1, perp2 (rotA.m_col[0..2]) and the pivot
	const hkTransform& tA = *in.m_transformA;
	hkRotation rotA;
	setRotatedDir(rotA.m_col[0], tA.m_rotation, m_basisA.m_axle);
	hkVector4 perp1AW;
	setRotatedDir(perp1AW, tA.m_rotation, m_basisA.m_perpToAxle1);
	hkVector4 perp2AW;
	setRotatedDir(perp2AW, tA.m_rotation, m_basisA.m_perpToAxle2);
	hkVector4 pivotAW;
	setRotatedDir(pivotAW, tA.m_rotation, m_basisA.m_pivot);
	pivotAW.addTranslation(tA.m_translation);
	rotA.m_col[1] = perp1AW;
	rotA.m_col[2] = perp2AW;

	// frame B in world
	const hkTransform& tB = *in.m_transformB;
	hkVector4 axleBW;
	setRotatedDir(axleBW, tB.m_rotation, m_basisB.m_axle);
	hkVector4 perp2FreeBW;
	setRotatedDir(perp2FreeBW, tB.m_rotation, m_basisB.m_perp2FreeAxis);
	hkVector4 pivotBW;
	setRotatedDir(pivotBW, tB.m_rotation, m_basisB.m_pivot);
	pivotBW.addTranslation(tB.m_translation);

	// two angular rows keeping B's axle perpendicular to A's perp1 / perp2
	{
		hk1dAngularBilateralConstraintInfo ang;
		ang.m_zeroErrorAxisAinW = perp2AW;
		ang.m_constrainedDofW = perp1AW;
		ang.m_perpZeroErrorAxisBinW = axleBW;
		hk1dAngularBilateralConstraintBuildJacobian(ang, in, out);
	}
	{
		hk1dAngularBilateralConstraintInfo ang;
		ang.m_zeroErrorAxisAinW = perp1AW;
		ang.m_constrainedDofW = perp2AW;
		ang.m_perpZeroErrorAxisBinW.x = -axleBW.x;
		ang.m_perpZeroErrorAxisBinW.y = -axleBW.y;
		ang.m_perpZeroErrorAxisBinW.z = -axleBW.z;
		ang.m_perpZeroErrorAxisBinW.w = -axleBW.w;
		hk1dAngularBilateralConstraintBuildJacobian(ang, in, out);
	}

	// hinge angle, unwrapped against the previous one
	hk1dAngularLimitInfo limit;
	limit.m_constrainedDofW = rotA.m_col[0];
	limit.m_min = m_minAngle;
	limit.m_max = m_maxAngle;
	limit.m_tau = in.m_tau * m_angularLimitsTauFactor;

	const hkVector4& p = perp2FreeBW;
	const hkVector4& a = axleBW;
	// evaluated on the x87 stack at extended precision, stored once
	typedef double X87;
	const float cosPart = (float)((X87)p.y * perp1AW.y + ((X87)p.z * perp1AW.z + (X87)p.x * perp1AW.x));
	const float sinPart = (float)(((X87)p.z * a.x - (X87)p.x * a.z) * perp1AW.y +
		(((X87)p.x * a.y - (X87)p.y * a.x) * perp1AW.z + ((X87)p.y * a.z - (X87)p.z * a.y) * perp1AW.x));
	float angle = hkMath::atan2fApproximation(cosPart, sinPart);
	if (runtime->m_previousAngle - angle > kPi)
		angle = angle + kTwoPi;
	else if (angle - runtime->m_previousAngle > kPi)
		angle = angle - kTwoPi;
	limit.m_computedAngle = angle;
	runtime->m_previousAngle = angle;
	hk1dAngularLimitBuildJacobian(limit, in, out);

	hkBallSocketBuildJacobian(pivotAW, pivotBW, in, out);

	if (m_maxFrictionTorque != kZero)
	{
		hk1dAngularFrictionInfo friction;
		friction.m_constrainedDofW = &rotA.m_col[0];
		friction.m_lastSolverResults = &runtime->m_solverResults[6];
		friction.m_maxFrictionTorque = m_maxFrictionTorque;
		friction.m_numFriction = 1;
		hk1dAngularFrictionBuildJacobian(friction, in, out);
	}
}

// ---------------------------------------------------------------------------
// hkBallSocketChain / hkConstraintInstance support code.
// ---------------------------------------------------------------------------
typedef int hkBool32;

struct hkConstraintInfo {                                            // 0x10 bytes
	int32_t m_maxSizeOfSchema;          // +0x00
	int32_t m_sizeOfSchemas;            // +0x04
	int32_t m_numSolverResults;         // +0x08
	int32_t m_numSolverElemTemps;       // +0x0c
};

struct hkConstraintRuntimeInfo {                                     // 0x08 bytes
	int32_t m_numSolverResults;         // +0x00
	int32_t m_numSolverElemTemps;       // +0x04
};

struct hkBallSocketConstraintInfo {                                  // 0x20 bytes
	hkVector4 m_pivotA;                 // +0x00
	hkVector4 m_pivotB;                 // +0x10
};

// hkArray<hkBallSocketConstraintInfo> block shared by the chain data.
class hkThreadMemory
{
public:
	void deallocateChunk(void* data, int numBytes, int alignment);      // 0x0107db10
};

extern unsigned long  g_hkThreadMemoryTls;          // 0x016e4174

__declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);

struct hkBallSocketChainArray {
	hkBallSocketConstraintInfo* m_data;          // +0x00
	int32_t m_size;                              // +0x04
	int32_t m_capacityAndFlags;                  // +0x08
};

class hkMemory
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10();
	virtual void deallocate(void* block, int size, int memoryClass);   // slot 5 (+0x14)
};

extern hkMemory*      g_hkMemoryInstance;           // 0x016e4178

class hkBallSocketChainData : public hkConstraintData
{
public:
	hkBallSocketChainArray m_chain;              // +0x0c
	hkReal m_tau;                                // +0x18
	hkReal m_damping;                            // +0x1c
	hkReal m_maxImpulse;                         // +0x20
	hkReal m_maxFriction;                        // +0x24

	hkBallSocketChainData();
// @ 0x0108bb40
	virtual ~hkBallSocketChainData();
	void operator delete(void* block)
	{
		hkBallSocketChainData* pData = (hkBallSocketChainData*)block;
		g_hkMemoryInstance->deallocate(block, pData->m_memSizeAndFlags, 0x29);
	}
	virtual void getConstraintInfo(hkConstraintInfo& info) const;
	virtual void getRuntimeInfo(bool allow, hkConstraintRuntimeInfo& info) const;
	void addConstraint(const hkVector4& pivotA, const hkVector4& pivotB);
	virtual void buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out);
};

extern "C" void hkArrayUtil_reserveMore(void* array, int numElemBytes);   // 0x0107f530

hkBallSocketChainData::~hkBallSocketChainData()
{
	// hkArray<hkBallSocketConstraintInfo>::deallocate()
	if (m_chain.m_capacityAndFlags < 0)
		return;
	// hkThreadMemory::getInstance()
	hkThreadMemory* pThreadMemory = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
	pThreadMemory->deallocateChunk(m_chain.m_data,
	                               (uint32_t)(m_chain.m_capacityAndFlags & 0x3fffffff) * 0x20u, 0x14);
}

// ---------------------------------------------------------------------------
// hkBallSocketChainData::buildJacobian (definition at the end of this file)
// ---------------------------------------------------------------------------

// @ 0x0108bb00
hkBallSocketChainData::hkBallSocketChainData()
{
	m_chain.m_data = 0;
	m_chain.m_size = 0;
	m_chain.m_capacityAndFlags = 0x80000000;
	m_tau = 0.6f;
	m_damping = 1.0f;
	m_maxImpulse = 1.1920929e-8f;
	m_maxFriction = 0.1f;
}

// @ 0x0108b9f0
void hkBallSocketChainData::getConstraintInfo(hkConstraintInfo& info) const
{
	info.m_maxSizeOfSchema = 0;
	info.m_sizeOfSchemas = 0;
	info.m_numSolverResults = 0x18;
	info.m_numSolverElemTemps = 0;

	const int32_t n = m_chain.m_size;
	info.m_numSolverResults = n * 4 + 0x2c;
	info.m_sizeOfSchemas = n * 0x130 + 0x10;
	info.m_numSolverElemTemps = n * 3;
}

// @ 0x0108ba30
void hkBallSocketChainData::getRuntimeInfo(bool allow, hkConstraintRuntimeInfo& info) const
{
	if (allow) {
		info.m_numSolverElemTemps = m_chain.m_size * 3;
		info.m_numSolverResults = info.m_numSolverElemTemps * 8;
	} else {
		info.m_numSolverElemTemps = 0;
		info.m_numSolverResults = 0;
	}
}

// @ 0x0108ba70
void hkBallSocketChainData::addConstraint(const hkVector4& pivotA, const hkVector4& pivotB)
{
	hkBallSocketChainArray* pChain = &m_chain;
	if (pChain->m_size == (pChain->m_capacityAndFlags & 0x3fffffff))
		hkArrayUtil_reserveMore(pChain, 0x20);

	hkBallSocketConstraintInfo* pSlot = &pChain->m_data[pChain->m_size];
	++pChain->m_size;
	pSlot->m_pivotA = pivotA;
	pSlot->m_pivotB = pivotB;
}

// ---------------------------------------------------------------------------
// hkConstraintInstance / hkPhantom listener notification.
// ---------------------------------------------------------------------------
class hkWorld;
struct hkCollidable;

// hkRigidBody motion: the world transform lives at +0x10, the solver-body index at +0x08.
struct hkMotion
{
	uint8_t     pad00[0x08];
	int32_t     m_solverBodyIndex;      // +0x08
	uint8_t     pad0c[0x04];
	hkTransform m_transform;            // +0x10
};

class hkEntity : public hkBaseRef                  // hkWorldObject
{
public:
	hkWorld* m_world;                   // +0x08
	uint8_t  pad0c[0x4c];
	hkMotion* m_motion;                 // +0x58
	void removeReference();                                         // 0x0109ae60
};

struct hkWorld
{
	uint8_t   pad00[0x34];
	hkEntity* m_fixedBody;              // +0x34
};

struct hkConstraintRuntime
{
	uint8_t pad00[0x10];
	uint8_t m_priority;                 // +0x10
};

extern void __cdecl hkWorldOperationUtil_removeConstraintImmediately(
	hkWorld* world, class hkConstraintInstance* instance, bool removeFromWorld);   // 0x0109fa10

class hkConstraintInstance : public hkBaseRef
{
public:
	enum ConstraintPriority
	{
		CONSTRAINT_PRIORITY_INVALID = 0,
		CONSTRAINT_PRIORITY_PSI,
		CONSTRAINT_PRIORITY_ENTITY
	};

	hkWorld*             m_world;       // +0x08
	hkConstraintData*    m_constraintData;  // +0x0c
	hkEntity*            m_entityA;     // +0x10
	hkEntity*            m_entityB;     // +0x14
	uint8_t              m_priority;    // +0x18
	uint8_t              m_wantRuntime; // +0x19
	uint8_t              pad1a[2];      // +0x1a
	uint32_t             m_dynamics;    // +0x1c
	uint32_t             m_field20;     // +0x20
	hkConstraintRuntime* m_runtime;     // +0x24
	hkEntity**           m_chainEntities;   // +0x28 (ball-socket chains only)
	int32_t              m_numChainEntities; // +0x2c

	hkConstraintInstance(hkEntity* entityA, hkEntity* entityB,
	                     hkConstraintData* data, ConstraintPriority priority);
	hkConstraintInstance(ConstraintPriority priority);
	virtual ~hkConstraintInstance();
	void setPriority(ConstraintPriority priority);
	virtual void entityRemovedCallback(hkEntity* entity);
	void fixNullEntities();
};

// @ 0x0108bf80
hkConstraintInstance::hkConstraintInstance(ConstraintPriority priority)
{
	m_world = 0;
	m_priority = (uint8_t)priority;
	m_wantRuntime = 0;
	m_dynamics = 0;
	m_field20 = 0;
	m_runtime = 0;
}

// @ 0x0108bf10
hkConstraintInstance::hkConstraintInstance(hkEntity* entityA, hkEntity* entityB,
                                           hkConstraintData* data, ConstraintPriority priority)
{
	m_world = 0;
	m_constraintData = data;
	m_priority = (uint8_t)priority;
	m_wantRuntime = 0;
	m_dynamics = 0;
	m_field20 = 0;
	m_runtime = 0;
	m_entityA = entityA;
	m_entityB = entityB;
	m_entityA->addReference();
	if (m_entityB)
		m_entityB->addReference();
	if (m_constraintData->m_memSizeAndFlags)
		++m_constraintData->m_referenceCount;
}

// @ 0x0108bec0
hkConstraintInstance::~hkConstraintInstance()
{
	if (m_entityA)
		m_entityA->removeReference();
	if (m_entityB)
		m_entityB->removeReference();
	if (m_constraintData)
		m_constraintData->removeReference();
}

// @ 0x0108bfb0
void hkConstraintInstance::setPriority(ConstraintPriority priority)
{
	m_priority = (uint8_t)priority;
	if (m_runtime)
		m_runtime->m_priority = (uint8_t)priority;
}

// @ 0x0108bfd0
void hkConstraintInstance::entityRemovedCallback(hkEntity* entity)
{
	if (!m_world)
		return;
	hkWorldOperationUtil_removeConstraintImmediately(entity->m_world, this, true);
}

// @ 0x0108bff0
void hkConstraintInstance::fixNullEntities()
{
	hkEntity** pEntity = &m_entityA;
	for (int i = 2; i != 0; --i) {
		hkEntity* cur = *pEntity;
		if (!cur) {
			hkEntity* other = (hkEntity*)((uint32_t)m_entityA ^ (uint32_t)m_entityB
			                              ^ (uint32_t)cur);
			if (other) {
				hkWorld* world = other->m_world;
				if (world) {
					*pEntity = world->m_fixedBody;
					(*pEntity)->addReference();
				}
			}
		}
		++pEntity;
	}
}

// ---------------------------------------------------------------------------
// Phantom listener dispatch.
// ---------------------------------------------------------------------------
class hkPhantom;

struct hkCollidableAddedEvent
{
	hkPhantom*          m_phantom;      // +0x00
	const hkCollidable* m_collidable;   // +0x04
	int32_t             m_accept;       // +0x08
};

struct hkCollidableRemovedEvent
{
	hkPhantom*          m_phantom;      // +0x00
	const hkCollidable* m_collidable;   // +0x04
	bool                m_removed;      // +0x08
};

class hkPhantomListener
{
public:
	virtual void collidableAdded(const hkCollidableAddedEvent& event);
	virtual void collidableRemoved(const hkCollidableRemovedEvent& event);
};

class hkPhantom
{
public:
	uint8_t             pad00[0x58];
	hkPhantomListener** m_listeners;    // +0x58
	int32_t             m_numListeners; // +0x5c

	int32_t fireCollidableAdded(const hkCollidable* collidable);
	void    fireCollidableRemoved(const hkCollidable* collidable, bool removed);
};

// @ 0x0108c0b0
int32_t hkPhantom::fireCollidableAdded(const hkCollidable* collidable)
{
	hkCollidableAddedEvent event;
	event.m_phantom = this;
	event.m_collidable = collidable;
	event.m_accept = 0;

	for (int i = m_numListeners - 1; i >= 0; --i) {
		hkPhantomListener* pListener = m_listeners[i];
		if (pListener)
			pListener->collidableAdded(event);
	}
	return event.m_accept;
}

// @ 0x0108c100
void hkPhantom::fireCollidableRemoved(const hkCollidable* collidable, bool removed)
{
	hkCollidableRemovedEvent event;
	event.m_collidable = collidable;
	event.m_phantom = this;
	event.m_removed = removed;

	for (int i = m_numListeners - 1; i >= 0; --i) {
		hkPhantomListener* pListener = m_listeners[i];
		if (pListener)
			pListener->collidableRemoved(event);
	}
}

// ---------------------------------------------------------------------------
// hkBallSocketChainData::buildJacobian
// ---------------------------------------------------------------------------
struct hkBallSocketChainRuntime
{
	hkSolverResults m_solverResults[/* numLinks * 4 */ 4];
};

// hkArray<int> storage with an empty (allocatable) block, handed to the row builder below.
struct hkIntArray
{
	int32_t* m_data;                 // +0x00
	int32_t  m_size;                 // +0x04
	int32_t  m_capacityAndFlags;     // +0x08

	void pushBack(int32_t value)
	{
		if (m_size == (m_capacityAndFlags & 0x3fffffff))
			hkArrayUtil_reserveMore(this, 4);
		m_data[m_size++] = value;
	}
	void deallocate()
	{
		if (m_capacityAndFlags < 0)
			return;
		hkThreadMemory* pThreadMemory = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
		pThreadMemory->deallocateChunk(m_data, (uint32_t)(m_capacityAndFlags & 0x3fffffff) * 4u, 0x14);
	}
};

struct hkStabilizedBallSocketInfo
{
	hkVector4 m_pivotAinW;              // +0x00
	hkVector4 m_pivotBinW;              // +0x10
	hkVector4 m_axisAinW;               // +0x20
	hkSolverResults* m_solverResults;   // +0x30
};

// 0x010ACBF0 (name guessed): the three ball-socket rows of one chain link.
extern "C" void _hkStabilizedBallSocketConstraintBuildJacobian(const hkStabilizedBallSocketInfo& info,
                                                              const hkConstraintQueryIn& in,
                                                              hkConstraintQueryOut& out);
// 0x00C2E4E0 (name unknown): in-place normalization of one vector.
extern "C" void hkVector4Util_normalize(hkVector4& v);
// 0x010AD020 (name guessed): closes the constraint and hands the per-body row layout to the solver.
extern "C" int hkConstraintBuildJacobianAndSetData(hkConstraintQueryOut& out, const hkConstraintQueryIn& in,
                                                   int32_t numRowsAdded, int32_t firstSolverResult,
                                                   int32_t* bodyIndices, int32_t bodyIndexBase,
                                                   int32_t rowTriple0, int32_t rowTriple1, int32_t rowTriple2);

// @ 0x0108bba0
void hkBallSocketChainData::buildJacobian(const hkConstraintQueryIn& in, hkConstraintQueryOut& out)
{
	hkBallSocketChainRuntime* runtime = (hkBallSocketChainRuntime*)in.m_constraintRuntime;
	hkBeginConstraints(in, out, runtime->m_solverResults, 8);

	hkConstraintInstance* instance = (hkConstraintInstance*)in.m_constraintInstance;
	const int32_t numLinks = instance->m_numChainEntities - 1;
	const int32_t firstSolverResult = out.m_numSolverResults;

	// Solver-body index of every body of the chain: the anchor body first, then one
	// entry per link. The row builder maps the rows onto those bodies.
	hkIntArray bodyIndices;
	bodyIndices.m_data = 0;
	bodyIndices.m_size = 0;
	bodyIndices.m_capacityAndFlags = 0;
	bodyIndices.pushBack(instance->m_chainEntities[0]->m_motion->m_solverBodyIndex);

	// in.m_bodyA is offset by the anchor body's solver index
	const int32_t anchorBase = (int32_t)((size_t)in.m_bodyA
	                                     - (size_t)instance->m_chainEntities[0]->m_motion->m_solverBodyIndex);

	hkBallSocketConstraintInfo* pLink = m_chain.m_data;
	for (int32_t link = 0; link < numLinks; ++link, ++pLink)
	{
		hkEntity* entityB = instance->m_chainEntities[link + 1];
		const hkTransform& transformA = instance->m_chainEntities[link]->m_motion->m_transform;
		const hkTransform& transformB = entityB->m_motion->m_transform;
		bodyIndices.pushBack(entityB->m_motion->m_solverBodyIndex);

		// the link's two pivots in world space
		hkVector4 pivotAinW, pivotBinW;
		setRotatedDir(pivotAinW, transformA.m_rotation, pLink->m_pivotA);
		pivotAinW.addTranslation(transformA.m_translation);
		setRotatedDir(pivotBinW, transformB.m_rotation, pLink->m_pivotB);
		pivotBinW.addTranslation(transformB.m_translation);

		hkStabilizedBallSocketInfo socket;
		socket.m_pivotAinW = pivotAinW;
		socket.m_pivotBinW = pivotBinW;
		socket.m_axisAinW = transformA.m_rotation.m_col[1];
		hkVector4Util_normalize(socket.m_axisAinW);
		socket.m_solverResults = runtime->m_solverResults + link * 4;
		_hkStabilizedBallSocketConstraintBuildJacobian(socket, in, out);

		out.m_numSolverResults += 4;
	}

	hkConstraintBuildJacobianAndSetData(out, in, out.m_numSolverResults - firstSolverResult, firstSolverResult,
	                                    bodyIndices.m_data, anchorBase,
	                                    (int32_t)instance->m_dynamics, (int32_t)instance->m_field20,
	                                    (int32_t)(size_t)instance->m_runtime);

	bodyIndices.deallocate();
}
