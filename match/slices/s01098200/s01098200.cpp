// Havok 3.1.0 slice s01098200 (0x01098200..0x01098C4C): hkBoxMotion's inertia getters/setters, the mass
// and inertia setters, clone, the impulse/force appliers, applyForcesAndStep and
// applyForcesAndBuildAccumulator.
//
// Toolchain: the shipped module was built by cl 13.10 (VC .NET 2003); the whole slice therefore compiles
// with /vc71 /O2 /MD /Gy /EHsc /TP. All floating point is scalar x87; several intermediate products stay
// on the FPU stack across statements (X87-PRECISION comments mark those expressions).
//
// Class layout (32-bit, from the disassembly): hkReferencedObject 0x08, hkMotion 0x0c, hkRigidMotion
// 0x0f0, hkBoxMotion 0x100. The retail vtable at 0x014A18B8 orders the motion virtuals
// setMass(9), setMassInv(10), getInertiaLocal(11), getInertiaWorld(12), setInertiaLocal(13),
// setInertiaInvLocal(14), getInertiaInvLocal(15), getInertiaInvWorld(16), ... applyPointImpulse(25),
// applyAngularImpulse(26), applyForce(27), applyForce(dt,force,p)(28).
#include "types.h"
#include <math.h>
#include <new>

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
    void set(float a, float b, float c, float d) { x = a; y = b; z = c; w = d; }
};
typedef hkVector4 hkQuaternion;

class hkRotation                                                   // 0x30 bytes
{
public:
    hkVector4 m_col[3];
    void set(const hkQuaternion& q);                               // 0x010824a0
    void setTranspose(const hkRotation& r);                        // 0x01081550
};

class hkMatrix3                                                    // 0x30 bytes: three 16-byte columns
{
public:
    float m_el[12];
    void setMulInverse(const hkMatrix3& a, const hkRotation& b);   // 0x01081f20
    void changeBasis(const hkRotation& r);                         // 0x01082130
};

class hkTransform
{ public:
    hkVector4 m_rotation[3];      // +0x00..0x2f (columns)
    hkVector4 m_translation;      // +0x30
    void setRotation(const hkQuaternion& q);                       // hkRotation::set 0x010824a0
};

class hkStepInfo
{ public:
    float m_startTime;      // +0x00
    float m_endTime;        // +0x04
    float m_deltaTime;      // +0x08
    float m_invDeltaTime;   // +0x0c
};

class hkReferencedObject
{
public:
    virtual ~hkReferencedObject();                        // 0
    virtual void calcStatistics(void* c) const;           // 1
    hkInt16 m_memSizeAndFlags;                            // +0x04
    hkInt16 m_referenceCount;                             // +0x06
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

class hkVelocityAccumulator                       // 0x90 bytes (the accumulator tail runs past 0x80)
{
public:
    hkUint8   m_type;                  // +0x00
    hkUint8   m_pad01[3];              // +0x01
    hkUint32  m_deactivationCounter;   // +0x04
    hkUint32  m_deactivationClass;     // +0x08
    hkUint8   m_flag0c;                // +0x0c
    hkUint8   m_pad0d[3];              // +0x0d
    hkVector4 m_linearVelocity;   // +0x10
    hkVector4 m_angularVelocity;  // +0x20
    hkVector4 m_deltaPosition;    // +0x30
    hkVector4 m_linearVelocity2;  // +0x40
    hkVector4 m_angularVelocity2; // +0x50
    hkVector4 m_deltaPosition2;   // +0x60
    hkVector4 m_pad70;            // +0x70
};

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
};
hkMemory* hkMemory::s_instance;

// ---- referenced globals (relocation-masked; the difftest resolver matches the retail addresses) ----
extern hkVector4 g_hkVector4Zero;              // 0x016e42d0 (created by the hkBoxMotion ctor call)
extern hkQuaternion g_hkQuaternionIdentity;    // 0x015b9b50

// hkString::memCpy (0x0107f440): the binary moves 0xf8 bytes through this helper.
class hkString
{
public:
    static void memCpy(void* dst, const void* src, int size);   // 0x0107f440
};

// Inline helper the original keeps on the FPU stack (fsubr 1.0 / fcomp 0.0 / keep >= 0.0).
static inline float hkFloorZero(float v) { return v < 0.0f ? 0.0f : v; }

// ===================================================================================================
// motions
// ===================================================================================================
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
    virtual void setMassInv(float mInv);                                      // 10
    virtual void getInertiaLocal(hkMatrix3& out) const;                       // 11
    virtual void getInertiaWorld(hkMatrix3& out) const;                       // 12
    virtual void setInertiaLocal(const hkMatrix3& m);                         // 13
    virtual void setInertiaInvLocal(const hkMatrix3& m);                      // 14
    virtual void getInertiaInvLocal(hkMatrix3& out) const;                    // 15
    virtual void getInertiaInvWorld(hkMatrix3& out) const;                    // 16
    virtual void getPosition(hkVector4& out) const;                           // 17  0x010882b0
    virtual void getRotation(hkQuaternion& out) const;                        // 18  0x010882d0
    virtual void getTransform(hkTransform& out) const;                        // 19  0x010882f0
    virtual void setPositionAndRotation(const hkVector4& p, const hkQuaternion& q);   // 20  0x01088310
    virtual void setTransform(const hkTransform& t);                          // 21  0x01088330
    virtual void setLinearVelocity(const hkVector4& v);                       // 22  0x01088360
    virtual void setAngularVelocity(const hkVector4& v);                      // 23  0x01088390
    virtual void applyLinearImpulse(const hkVector4& imp);                    // 24  0x010883c0
    virtual void applyPointImpulse(const hkVector4& imp, const hkVector4& p); // 25
    virtual void applyAngularImpulse(const hkVector4& imp);                   // 26
    virtual void applyForce(float deltaTime, const hkVector4& force, const hkVector4& p);  // 27
    virtual void applyForce(float deltaTime, const hkVector4& force);         // 28
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
    hkBoxMotion(const hkVector4& position, const hkQuaternion& rotation);   // 0x01098140

    virtual void getInertiaLocal(hkMatrix3& out) const;                     // 11  0x01098190
    virtual void getInertiaWorld(hkMatrix3& out) const;                     // 12  0x01098390
    virtual void setMass(float m);                                          // 9   0x01098120
    virtual void setMassInv(float mInv);                                    // 10  0x01098410
    virtual void setInertiaLocal(const hkMatrix3& m);                       // 13  0x01098200
    virtual void setInertiaInvLocal(const hkMatrix3& m);                    // 14  0x010982b0
    virtual void getInertiaInvLocal(hkMatrix3& out) const;                  // 15  0x01098250
    virtual void getInertiaInvWorld(hkMatrix3& out) const;                  // 16  0x010982e0
    virtual void applyPointImpulse(const hkVector4& imp, const hkVector4& p);   // 25  0x010985b0
    virtual void applyAngularImpulse(const hkVector4& imp);                 // 26  0x01098720
    virtual void applyForce(float deltaTime, const hkVector4& force);       // 27  0x01098430
    virtual void applyForce(float deltaTime, const hkVector4& force, const hkVector4& p);  // 28  0x010984c0
    virtual hkMotion* clone() const;                                        // 8   0x01098510
    virtual void applyForcesAndStep(const hkStepInfo& s, const hkVector4& d);   // 4  0x01098810
    virtual hkVelocityAccumulator* applyForcesAndBuildAccumulator(const hkStepInfo& stepInfo,
                                                                  hkVelocityAccumulator* acc);  // 5  0x01098c50

    hkVector4 m_inertiaAndMassInv;        // +0xf0
};

// ===================================================================================================
// hkBoxMotion
// ===================================================================================================

// @ 0x01098200
void hkBoxMotion::setInertiaLocal(const hkMatrix3& m)
{
    float y = 1.0f / m.m_el[5];
    float z = 1.0f / m.m_el[10];
    float x = 1.0f / m.m_el[0];
    m_inertiaAndMassInv.set(x, y, z, m_inertiaAndMassInv.w);
}

// @ 0x01098250
void hkBoxMotion::getInertiaInvLocal(hkMatrix3& out) const
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
void hkBoxMotion::setInertiaInvLocal(const hkMatrix3& m)
{
    m_inertiaAndMassInv.set(m.m_el[0], m.m_el[5], m.m_el[10], m_inertiaAndMassInv.w);
}

// @ 0x010982e0
void hkBoxMotion::getInertiaInvWorld(hkMatrix3& out) const
{
    // The original scales the three world columns by the local inertia inverse, keeping each column's
    // four products as one expression off the FPU stack, and then calls setMulInverse with that scaled
    // matrix and the transform's rotation.
    const hkRotation& rot = *(const hkRotation*)&m_motionState.m_transform.m_rotation[0];
    float ix = m_inertiaAndMassInv.x;
    float iy = m_inertiaAndMassInv.y;
    float iz = m_inertiaAndMassInv.z;
    __declspec(align(16)) hkMatrix3 scaled;
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
void hkBoxMotion::getInertiaWorld(hkMatrix3& out) const
{
    float ix = 1.0f / m_inertiaAndMassInv.x;
    float iy = 1.0f / m_inertiaAndMassInv.y;
    float iz = 1.0f / m_inertiaAndMassInv.z;
    for (int i = 0; i < 12; ++i)
        out.m_el[i] = 0.0f;
    out.m_el[0]  = ix;
    out.m_el[5]  = iy;
    out.m_el[10] = iz;
    out.changeBasis(*(const hkRotation*)&m_motionState.m_transform.m_rotation[0]);
}
// @ 0x01098410
void hkBoxMotion::setMassInv(float mInv)
{
    m_massInv = mInv;
    m_inertiaAndMassInv.w = mInv;
}

// @ 0x01098430
void hkBoxMotion::applyForce(float deltaTime, const hkVector4& force)
{
    float mInv = m_massInv;
    m_linearVelocity.x = mInv * (deltaTime * force.x) + m_linearVelocity.x;
    m_linearVelocity.y = mInv * (deltaTime * force.y) + m_linearVelocity.y;
    m_linearVelocity.z = (deltaTime * force.z) * mInv + m_linearVelocity.z;
    m_linearVelocity.w = (deltaTime * force.w) * mInv + m_linearVelocity.w;
}

// @ 0x010984c0
void hkBoxMotion::applyForce(float deltaTime, const hkVector4& force, const hkVector4& p)
{
    hkVector4 impulse;
    impulse.x = deltaTime * force.x;
    impulse.y = deltaTime * force.y;
    impulse.z = deltaTime * force.z;
    impulse.w = deltaTime * force.w;
    applyPointImpulse(impulse, p);
}

// @ 0x01098510
hkMotion* hkBoxMotion::clone() const
{
    hkBoxMotion* m = (hkBoxMotion*)hkMemory::s_instance->allocateChunk(0x100, 0x2b);
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
void hkBoxMotion::applyPointImpulse(const hkVector4& imp, const hkVector4& p)
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
void hkBoxMotion::applyAngularImpulse(const hkVector4& imp)
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
void hkBoxMotion::applyForcesAndStep(const hkStepInfo& stepInfo, const hkVector4& delta)
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
    const hkVector4& r0 = m_motionState.m_transform.m_rotation[0];
    const hkVector4& r1 = m_motionState.m_transform.m_rotation[1];
    const hkVector4& r2 = m_motionState.m_transform.m_rotation[2];
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
hkVelocityAccumulator* hkBoxMotion::applyForcesAndBuildAccumulator(const hkStepInfo& stepInfo,
                                                                   hkVelocityAccumulator* acc)
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
    hkRotation* accRot = (hkRotation*)((char*)acc + 0x50);
    accRot->setTranspose(*(const hkRotation*)&m_motionState.m_transform.m_rotation[0]);

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
    return (hkVelocityAccumulator*)((char*)acc + 0x80);
}
