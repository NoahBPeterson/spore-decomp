// Havok 3.1.0 slice s01098e50 (0x01098E50..0x01099CE0): hkBoxMotion::applyAccumulator,
// hkBallAndSocketConstraintData::buildJacobian, hkStepInfo's time ctor, hkBackstepSimulation::simulateToi,
// hkDiscreteSimulation's integrate/collide entry points and the pointer-map driven collide helper.
//
// Toolchain: the shipped module was built by cl 13.10 (VC .NET 2003, x87 scalar float math); the whole
// slice therefore compiles with /vc71 /O2 /MD /Gy /EHsc /TP. Multiplications inside the inlined
// hkVector4::setRotatedDir stay on the FPU stack across statements (X87-PRECISION: those expressions are
// kept as single full expressions, exactly as hkVelocityAccumulator::applyAccumulator in s01095320 does).
#include "types.h"
#include <math.h>
#include <intrin.h>

// ===================================================================================================
// shared Havok 3.1 declarations used by this slice (32-bit member offsets in the comments)
// ===================================================================================================
typedef int32_t  hkInt32;
typedef uint32_t hkUint32;
typedef uint16_t hkUint16;
typedef int16_t  hkInt16;
typedef uint8_t  hkUint8;

class hkTransform;
class hkVector4
{ public:
    float x, y, z, w;
    void setMul(const hkVector4& a, const hkVector4& b);               // quaternion product (0x01082210)
    void normalize();                                                  // 0x010821a0
    void setRotatedDir(const hkTransform& t, const hkVector4& v);      // inline in the binary
    void setRotatedInverseDir(const hkTransform& t, const hkVector4& v);
    void setTransformedPos(const hkTransform& t, const hkVector4& p);  // 0x01081360
};
class hkTransform
{ public:
    hkVector4 m_rotation[3];      // +0x00..0x2f
    hkVector4 m_translation;      // +0x30
    void setRotation(const hkVector4& q);                              // hkRotation::set 0x010824a0
};
typedef hkVector4 hkQuaternion;

// ---- memory --------------------------------------------------------------------------------------
class hkMemory
{
public:
    virtual void* allocate(int nbytes, int cl);                       // 0
    virtual void  deallocate(void* p);                                // 1
    virtual void* alignedAllocate(int alignment, int nbytes, int cl); // 2
    virtual void  alignedDeallocate(void* p);                         // 3
    virtual void* allocateChunk(int nbytes, int cl);                  // 4
    virtual void  deallocateChunk(void* p, int nbytes, int cl);       // 5
    static hkMemory* s_instance;                                      // 0x016e4178
    hkInt32 m_o04;                                                    // +0x04 (out-of-memory flag)
    hkInt32 m_o08;                                                    // +0x08
    hkInt32 m_o0c;                                                    // +0x0c
    hkInt32 m_o10;                                                    // +0x10
    hkInt32 m_o14;                                                    // +0x14
    hkInt32 m_o18;                                                    // +0x18
    hkInt32 m_o1c;                                                    // +0x1c
    hkInt32 m_o20;                                                    // +0x20
    hkInt32 m_o24;                                                    // +0x24
    hkInt32 m_o28;                                                    // +0x28
};
hkMemory* hkMemory::s_instance;

// ---- monitor stream + TLS ------------------------------------------------------------------------
extern hkUint32 g_hkMonitorStreamCurrentTls;          // 0x016e42a4
extern hkUint32 g_hkMonitorStreamEndTls;              // 0x016e42a8
extern const char hkMonitorTimerEndTag[];             // 0x0149cc34 (end-of-timer marker)
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(hkUint32 index);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(hkUint32 index, void* value);

static inline hkUint32 hkRdtscLow()
{
#if defined(_MSC_VER)
    return (hkUint32)__rdtsc();
#else
    return (hkUint32)__builtin_ia32_rdtsc();
#endif
}

// One 12-byte monitor record: the command/monitor name, the rdtsc stamp and the alignment pad that the
// stream writer fills in later. A 16-byte "list" record additionally carries a first-split name.
struct hkMonitorRecord     { const char* m_name; hkUint32 m_time; hkUint32 m_pad; };
struct hkMonitorListRecord { const char* m_name; hkUint32 m_time; hkUint32 m_pad; const char* m_firstSplit; };

// HK_TIMER_COMMAND / HK_TIMER_BEGIN / HK_TIMER_END as inlined by the original (fast path only: no
// record is written when the stream is full). 12 bytes for the plain form, 16 for HK_TIMER_BEGIN_LIST.
static inline void hkMonitorCommand(const char* name)
{
    hkMonitorRecord* cur = (hkMonitorRecord*)TlsGetValue(g_hkMonitorStreamCurrentTls);
    if (cur < (hkMonitorRecord*)TlsGetValue(g_hkMonitorStreamEndTls)) {
        cur->m_name = name;
        cur->m_time = hkRdtscLow();
        TlsSetValue(g_hkMonitorStreamCurrentTls, cur + 1);
    }
}
static inline void hkMonitorCommandList(const char* name, const char* firstSplit)
{
    hkMonitorListRecord* cur = (hkMonitorListRecord*)TlsGetValue(g_hkMonitorStreamCurrentTls);
    if (cur < (hkMonitorListRecord*)TlsGetValue(g_hkMonitorStreamEndTls)) {
        cur->m_name = name;
        cur->m_firstSplit = firstSplit;
        cur->m_time = hkRdtscLow();
        TlsSetValue(g_hkMonitorStreamCurrentTls, cur + 1);
    }
}
#define HK_TIMER_BEGIN(name)   hkMonitorCommand(name)
#define HK_TIMER_END()         hkMonitorCommand(hkMonitorTimerEndTag)

// ===================================================================================================
// motions
// ===================================================================================================
class hkReferencedObject
{
public:
    virtual ~hkReferencedObject();                       // 0
    virtual void calcStatistics(void* c) const;          // 1
    hkInt16 m_memSizeAndFlags;                           // +0x04
    hkInt16 m_referenceCount;                            // +0x06
};

class hkSweptTransform
{ public:
    hkVector4 m_centerOfMass0;      // +0x00
    hkVector4 m_centerOfMass1;      // +0x10
    hkQuaternion m_rotation0;       // +0x20
    hkQuaternion m_rotation1;       // +0x30
    hkVector4 m_centerOfMassLocal;  // +0x40
};

class hkMotionState
{ public:
    hkTransform     m_transform;          // +0x00
    hkSweptTransform m_sweptTransform;    // +0x40
    hkVector4       m_deltaAngle;         // +0x90
    float           m_objectRadius;       // +0xa0
    float           m_maxLinearVelocity;  // +0xa4
    float           m_maxAngularVelocity; // +0xa8
    hkUint16        m_deactivationClass;  // +0xac
    hkUint16        m_deactivationCounter;// +0xae
};

class hkStepInfo
{ public:
    float m_startTime;     // +0x00
    float m_endTime;       // +0x04
    float m_deltaTime;     // +0x08
    float m_invDeltaTime;  // +0x0c
    hkStepInfo(float startTime, float endTime);   // 0x01099430
};

class hkVelocityAccumulator                       // 0x80 bytes
{
public:
    hkUint8   m_type;             // +0x00
    hkUint8   m_pad01[3];         // +0x01
    hkInt16   m_deactivationClass;// +0x04
    hkUint8   m_pad06[6];         // +0x06
    hkUint8   m_flag0c;           // +0x0c
    hkUint8   m_pad0d[3];         // +0x0d
    hkVector4 m_linearVelocity;   // +0x10
    hkVector4 m_angularVelocity;  // +0x20
    hkVector4 m_deltaPosition;    // +0x30
    hkVector4 m_linearVelocity2;  // +0x40
    hkVector4 m_angularVelocity2; // +0x50
    hkVector4 m_deltaPosition2;   // +0x60
    hkUint32  m_pad70[4];         // +0x70
    hkVector4 m_centerOfMass;     // +0x80
};

class hkMotion : public hkReferencedObject
{
public:
    virtual int  getType() const;                                             // 2
    virtual void step(const hkStepInfo& stepInfo);                            // 3
    virtual void applyForcesAndStep(const hkStepInfo& s, const hkVector4& d);// 4
    virtual hkVelocityAccumulator* applyForcesAndBuildAccumulator(const hkStepInfo& stepInfo,
                                                                  hkVelocityAccumulator* acc);  // 5
    virtual const hkVelocityAccumulator* applyAccumulator(const hkStepInfo& stepInfo,
                                                          const hkVelocityAccumulator* acc);    // 6
    virtual void v7();                                                        // 7
    virtual hkMotion* clone() const;                                          // 8
    virtual void setMass(float m);                                            // 9
    hkInt32 m_solverData;                                                     // +0x08
};

class hkRigidMotion : public hkMotion
{
public:
    hkRigidMotion(const hkVector4& position, const hkQuaternion& rotation);   // 0x01088500
    hkUint32  m_pad0c;                    // +0x0c (hkMotionState is 16-aligned)
    hkMotionState m_motionState;          // +0x10
    float     m_massInv;                  // +0xc0
    float     m_particleMinInertiaDiagInv;// +0xc4
    float     m_linearDamping;            // +0xc8
    float     m_angularDamping;           // +0xcc
    hkVector4 m_linearVelocity;           // +0xd0
    hkVector4 m_angularVelocity;          // +0xe0
};

class hkBoxMotion : public hkRigidMotion
{
public:
    hkBoxMotion(const hkVector4& position, const hkQuaternion& rotation);                        // 0x01098140
    virtual void setMass(float m);                                                               // 9
    virtual void getInertiaLocal(hkVector4& out) const;                                          // 11
    virtual const hkVelocityAccumulator* applyAccumulator(const hkStepInfo& stepInfo,
                                                          const hkVelocityAccumulator* acc);     // 0x01098e50
    const hkVector4& linearVelocity() const { return m_linearVelocity; }
    const hkVector4& angularVelocity() const { return m_angularVelocity; }
    void setLinearVelocity(const hkVector4& v) { m_linearVelocity = v; }
    void setAngularVelocity(const hkVector4& v) { m_angularVelocity = v; }
};

// Inlined by the original: the identity ratio, the two compare/clamp steps and the two rotated
// velocity transforms all run in one basic block (see the disassembly of 0x01098e50).
// -----------------------------------------------------------------------------------------------
// @ 0x01098e50
const hkVelocityAccumulator* hkBoxMotion::applyAccumulator(const hkStepInfo& stepInfo,
                                                           const hkVelocityAccumulator* acc)
{
    // The incoming upper-half velocities become the motion's new linear velocity. This block reproduces
    // the original instruction schedule: the clamped components are read straight out of the
    // accumulator into locals, the clamp stores them back through hkVector4::operator= and the
    // following rotate reads the locals (which is why the stores look dead in the source).
    hkVector4 newLinearVelocity = acc->m_linearVelocity2;
    float clampedX = newLinearVelocity.x;
    float clampedY = newLinearVelocity.y;
    float clampedZ = newLinearVelocity.z;

    m_linearVelocity = newLinearVelocity;

    // Angular velocity: rotate the accumulator's second angular velocity into world space.
    hkVector4 newAngularVelocity;
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
    hkQuaternion rotation = m_motionState.m_sweptTransform.m_rotation1;
    m_motionState.m_sweptTransform.m_rotation0 = rotation;

    float halfDelta = halfStep * 0.5f;
    hkQuaternion delta;
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

    const hkVector4& r0 = *(const hkVector4*)&m_motionState.m_transform.m_rotation[0];
    const hkVector4& r1 = *(const hkVector4*)&m_motionState.m_transform.m_rotation[1];
    const hkVector4& r2 = *(const hkVector4*)&m_motionState.m_transform.m_rotation[2];
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
    hkVector4 nextLinearVelocity = acc->m_linearVelocity;
    float nextX = nextLinearVelocity.x;
    float nextY = nextLinearVelocity.y;
    float nextZ = nextLinearVelocity.z;

    m_linearVelocity = nextLinearVelocity;

    hkVector4 nextAngularVelocity;
    nextAngularVelocity.x = acc->m_angularVelocity.x * r0.x + acc->m_angularVelocity.y * r1.x + acc->m_angularVelocity.z * r2.x;
    nextAngularVelocity.y = acc->m_angularVelocity.x * r0.y + acc->m_angularVelocity.y * r1.y + acc->m_angularVelocity.z * r2.y;
    nextAngularVelocity.z = acc->m_angularVelocity.x * r0.z + acc->m_angularVelocity.y * r1.z + acc->m_angularVelocity.z * r2.z;
    nextAngularVelocity.w = 0.0f;
    (void)nextX; (void)nextY; (void)nextZ;
    m_angularVelocity = nextAngularVelocity;

    return (const hkVelocityAccumulator*)&acc->m_centerOfMass;
}

// ===================================================================================================
// constraints
// ===================================================================================================
class hkConstraintQueryIn
{ public:
    char    m_pad00[0x30];
    const hkTransform* m_bodyA;             // +0x30 (32-bit two-pointer pair: A at +0x30, B at +0x34)
    const hkTransform* m_bodyB;             // +0x34
    char    m_pad38[0x44 - 0x38];
    hkInt32 m_source;                       // +0x44
};

void hkBeginConstraints(const hkConstraintQueryIn& in, void* out, int a, int b);   // 0x010aa080
void hkAddConstraint(const hkVector4& pivotA, const hkVector4& pivotB,
                     const hkConstraintQueryIn& in, void* out);                    // 0x010ab2d0

class hkBallAndSocketConstraintData
{
public:
    virtual void v00();                                                          // 0
    virtual void v04();                                                          // 1
    virtual void buildJacobian(const hkConstraintQueryIn& in, void* out);        // 0x01099330
    hkVector4 m_pivotA;   // +0x10
    hkVector4 m_pivotB;   // +0x20
};

// @ 0x01099330
void hkBallAndSocketConstraintData::buildJacobian(const hkConstraintQueryIn& in, void* out)
{
    const hkTransform* transformA = in.m_bodyA;
    const hkTransform* transformB = in.m_bodyB;

    hkVector4 pivotAWorld;
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

    hkVector4 pivotBWorld;
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

// ===================================================================================================
// hkStepInfo
// ===================================================================================================
// @ 0x01099430
hkStepInfo::hkStepInfo(float startTime, float endTime)
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

// ===================================================================================================
// world / collision structures
// ===================================================================================================
class hkEntity;
class hkWorld;

void hkSweptTransformUtil_backStepMotionState(float time, hkMotionState& motionState);   // 0x0120a260
void hkLs_invalidateTimsOfEntity(hkEntity* entity, void* sibling);                        // 0x010a3890
void hkWorld_executePendingOperations(hkWorld* world);                                    // 0x01082bf0

struct hkArrayEntity
{
    hkEntity* m_data;        // +0x00
    hkInt32   m_size;        // +0x04
    hkInt32   m_capacityAndFlags;  // +0x08
};

struct hkToiEvent
{
    float     m_time;        // +0x00
    hkEntity* m_entities[2]; // +0x04, +0x08
};

// hkWorld's leading layout up to the members this slice touches. The original never dereferences the
// vtable of the world itself, so it is modelled as a plain struct with the vtable pointer at +0.
class hkWorld
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
    hkStepInfo m_dynamicsStepInfo;             // +0x170 (also the world->m_stepInfo passed to actions)
    char      m_stepInfo2[0x10];               // +0x180
    float     m_solverInfo184;                 // +0x184
    float     m_solverInfo188;                 // +0x188
    char      m_pad18c[0x190 - 0x18c];
    hkVector4 m_gravitySolver;                 // +0x190
    hkVector4 m_gravitySolverFrame;            // +0x1a0
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

class hkEntity
{
public:
    char m_motionStateOffsetTable[0x58];       // +0x00..0x57 (vtable + entity data)
    hkMotionState* m_motionState;              // +0x58 (hkMotion + 0x10)
    char m_pad5c[0x9a - 0x5c];
    char m_isFixedOrKeyframed;                 // +0x9a
};

// ===================================================================================================
// simulations
// ===================================================================================================
// hkWorldOperationUtil::cleanupDirtyIslands / the entity step that shadows the collide vtable slot.
void hkWorldOperationUtil_cleanupDirtyIslands(hkWorld* world);                       // 0x010a07c0
void stepInputWakeUpContacts();                                                      // 0x00c2e4e0
void hkBuildAndSolve(void* stepInfo, void* dynamicsStepInfo, const void* stepInput, void* island,
                     void* entities, int numEntities);                               // 0x010a5070
void hkWorldCallbackUtil_fireIslandPostIntegrateCallback(hkWorld* world, void* island,
                                                         const hkStepInfo& stepInfo); // 0x0109f750
void hkWorldCallbackUtil_firePostIntegrateCallback(hkWorld* world,
                                                   const hkStepInfo& stepInfo);       // 0x0109f630

class hkSimulation : public hkReferencedObject
{
public:
    virtual void v00();                        // 0
    virtual void v04();                        // 1
    // Slot 2 is the collide entry point. The binary calls it off hkSimulation's vtable at +8 with four
    // arguments (entities, count, world, &stepInfo); hkDiscreteSimulation overrides it for real.
    virtual void collideEntitiesNarrowPhaseDiscrete(hkEntity** entities, int numEntities,
                                                    hkWorld* world, const void* stepInfo);  // +0x08
    virtual void v0c();
    hkInt32 m_type;                            // +0x2c
};

void hkDiscreteSimulation_collideEntitiesNarrowPhaseDiscrete(hkSimulation* sim, hkEntity** entities,
                                                             int numEntities,
                                                             const void* collisionInput);  // 0x010f25d0
void FUN_010a08b0(hkSimulation* sim, hkEntity* entity);                                    // 0x010a08b0

class hkDiscreteSimulation : public hkSimulation
{
public:
    virtual void collideEntitiesNarrowPhaseDiscrete(hkEntity** entities, int numEntities,
                                                    hkWorld* world, const void* stepInfo);  // +0x08
    virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void stepIntegrate(hkWorld* world, const hkStepInfo& stepInfo);        // 0x01099690
    virtual void processAgentCollideDiscrete(void* entry, const void* input,
                                             void* output);                        // 0x010995d0
    virtual void processAgentResetCollisionInformation(void* entry, const void* input,
                                                       void* output);              // 0x01099670
};

// ---------------------------------------------------------------------------------------------------
// The backstep simulation's collision work is the *static* entry point
// ?_hkAgentNnMachine_processAgent@@... (0x010fc180), not the virtual processAgentCollideDiscrete above,
// so declare it free-standing and give it the same signature.
// ---------------------------------------------------------------------------------------------------
void _hkAgentNnMachine_processAgent(void* entry, const void* input, void* output);  // 0x010fc180

// ===================================================================================================
// hkBackstepSimulation::simulateToi
// ===================================================================================================
class hkBackstepSimulation : public hkDiscreteSimulation
{
public:
    virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void simulateToi(hkWorld* world, hkToiEvent& event, float time);   // 0x01099480
};

// @ 0x01099480
void hkBackstepSimulation::simulateToi(hkWorld* world, hkToiEvent& event, float time)
{
    world->m_criticalSectionLock++;

    for (int i = 0; i < 2; ++i) {
        hkEntity* entity = event.m_entities[i];
        hkMotionState* motionState = entity->m_motionState;

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
                hkStepInfo stepInfo(world->m_currentTime, world->m_timeOfNextFrame);
                collideEntitiesNarrowPhaseDiscrete(&entity, 1, world, &stepInfo);
            }
        }
    }

    if (--world->m_criticalSectionLock == 0 && world->m_pendingOperations != 0
        && world->m_executePendingOperations == 0) {
        hkWorld_executePendingOperations(world);
    }
}

// ===================================================================================================
// hkProcessCollisionInput / hkProcessCollisionOutput
// ===================================================================================================
#define HK_REAL_MAX 3.40282e+38f          // stored as 0x7f7fffee by the original

struct hkProcessCollisionOutput
{
    void*   m_contactMgr;                  // +0x0000
    char    m_pad04[0x30 - 0x04];
    char    m_scratch[0x3034 - 0x30];      // +0x0030 inline area the output points at
    hkUint32 m_earlyOutDistanceOrMax;      // +0x3034 (written as 0x7f7fffee)
    char    m_pad3038[0x3040 - 0x3038];
    hkInt32 m_contactPointCount;           // +0x3040
};

struct hkProcessCollisionInput
{
    void*   m_dispatcher;                  // +0x00
    char    m_pad04[0x0c - 0x04];
    hkUint8 m_qualityType;                 // +0x0c (dispatcher table index)
    char    m_pad0d[0x28 - 0x0d];
    void*   m_dispatcherData;              // +0x28 (dispatcher + 0x1a50)
};

struct hkAgentNnEntry
{
    char       m_pad00[0x08];
    signed char m_agentType;                // +0x08 (signed byte: 0..N dispatcher row)
    char       m_pad09[0x10 - 0x09];
    void**     m_agentVtable;               // +0x10 (the agent's vtable)
    void*      m_agentA;                    // +0x14
    void*      m_agentB;                    // +0x18
};

// ===================================================================================================
// hkDiscreteSimulation::processAgentCollideDiscrete
// ===================================================================================================
// @ 0x010995d0
void hkDiscreteSimulation::processAgentCollideDiscrete(void* entry, const void* input, void* output)
{
    hkAgentNnEntry* agentEntry = (hkAgentNnEntry*)entry;
    hkProcessCollisionInput* collisionInput = (hkProcessCollisionInput*)input;
    hkProcessCollisionOutput* collisionOutput = (hkProcessCollisionOutput*)output;

    collisionOutput->m_earlyOutDistanceOrMax = 0x7f7fffee;
    collisionOutput->m_contactPointCount = 0;
    collisionOutput->m_contactMgr = collisionOutput->m_scratch;

    hkUint8* dispatcher = (hkUint8*)collisionInput->m_dispatcher;
    collisionInput->m_dispatcherData = dispatcher + 0x1a50;
    collisionInput->m_qualityType = dispatcher[agentEntry->m_agentType * 0x3c + 0x1a24];

    _hkAgentNnMachine_processAgent(entry, input, output);

    hkMemory* memory = hkMemory::s_instance;
    if (memory->m_o08 <= memory->m_o28 + memory->m_o14)
        memory->m_o04 = 1;

    if (hkMemory::s_instance->m_o04 != 1 && collisionOutput->m_contactMgr != collisionOutput->m_scratch) {
        void* agentB = agentEntry->m_agentB;
        void** vtable = (void**)agentEntry->m_agentVtable;
        void* vt0 = vtable[0];
        void* agentA = agentEntry->m_agentA;
        typedef void (__stdcall *CollideFn)(void*, void*, const void*, void*);
        CollideFn fn = (CollideFn)(((void**)vt0)[5]);
        fn(agentA, agentB, input, output);
    }
}

// ===================================================================================================
// hkDiscreteSimulation::processAgentResetCollisionInformation
// ===================================================================================================
void _hkAgentNnMachine_InvalidateTimInAgent(void* entry, const void* sibling);   // 0x010fba10

// @ 0x01099670
void hkDiscreteSimulation::processAgentResetCollisionInformation(void* entry, const void* input, void* output)
{
    (void)output;
    _hkAgentNnMachine_InvalidateTimInAgent(entry, input);
}

// ===================================================================================================
// hkDiscreteSimulation::stepIntegrate  (0x01099690)
// ===================================================================================================
// @ 0x01099690
void hkDiscreteSimulation::stepIntegrate(hkWorld* world, const hkStepInfo& stepInfo)
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

// ===================================================================================================
// hkPointerMap-driven collide helper
// ===================================================================================================
void hkPointerMapBase_ctor(void* map);                                  // 0x0107de00
void hkPointerMapBase_dtor(void* map);                                  // 0x0107de50
void hkPointerMapBase_reserve(void* map, int size);                     // 0x0107e5b0
void hkPointerMapBase_insert(void* map, void* key, void* value);        // 0x0107de70
int  hkPointerMapBase_find(void* map, void* key);                       // 0x0107def0

typedef void (*hkCollideFunc)(void* pair, void* input, void* output);   // 0x01099670 as passed by the caller

// Address 0x01099670 (hkDiscreteSimulation::processAgentResetCollisionInformation) taken as a raw
// free-function pointer, as FUN_01099cb0 does when it pushes the constant before the call.
extern "C" void FUN_01099670(void* pair, void* input, void* output);

// Byte address of hkDiscreteSimulation::processAgentResetCollisionInformation (0x01099670), as the
// original loads it straight into a push immediate.
extern char hkDiscreteSimulation_processAgentResetCollisionInformation_Address;

// @ 0x01099be0
void __stdcall FUN_01099be0(void* entities, int numEntities, void* collideInput, hkCollideFunc collideFunc)
{
    char map[0x3060];
    hkProcessCollisionOutput output;

    hkPointerMapBase_ctor(map);
    hkPointerMapBase_reserve(map, numEntities);

    output.m_earlyOutDistanceOrMax = 0x7f7fffee;

    for (int i = 0; i < numEntities; ++i) {
        char* entity = *(char**)((char*)entities + i * 4);
        entity += 0x1c;

        hkPointerMapBase_insert(map, entity, 0);

        for (int k = 0; k < *(int*)(entity + 0x28); ++k) {
            char* pair = entity + k * 8;
            if (hkPointerMapBase_find(map, *(void**)(pair + 4)) > 0) {
                collideFunc(*(void**)pair, collideInput, output.m_scratch);
                if (hkMemory::s_instance->m_o04 == 1)
                    goto done;
            }
        }
    }
done:
    hkPointerMapBase_dtor(map);
}

// @ 0x01099cb0
void __stdcall FUN_01099cb0(void* entities, int numEntities, void* world)
{
    // The original loads world->m_o78 and pushes the address of processAgentResetCollisionInformation as a
    // plain immediate (0x01099670) before the call; expressed as a real function-pointer argument.
    void* collideInput = *(void**)((char*)world + 0x78);
    FUN_01099be0(entities, numEntities, collideInput, (hkCollideFunc)FUN_01099670);
}

// ===================================================================================================
// small non-data-jump helper (0x010992e0): fills an (int, int) result pair
// ===================================================================================================
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

// ---------------------------------------------------------------------------------------------------
// referenced-but-external helpers (declared so the slice compiles standalone; not defined here)
// ---------------------------------------------------------------------------------------------------
