// Havok 3.1.0 slice s010878b0 (0x010878B0..0x010888C0): hkRigidBody ctor/getCinfo/clone,
// hkWorldObject::copyProperties, hkRigidBodyCinfo defaults, hkWorldCinfo, hkRigidMotion basics and step.
// Layout comments give the 32-bit offsets of the shipped binary (pointer members make 64-bit sizes differ);
// they match hkReflectedClasses.h / the dev PDB.
#pragma once
#include "../s0107e670/hk31_base.h"
#include <new>
#include <string.h>
#include <cmath>

// Value the binary keeps on the x87 stack without storing. X87-PRECISION: switch to float / long double to experiment.
typedef double hkX87Real;
static inline hkX87Real hkX87Sqrt(hkX87Real v) { return std::sqrt(v); }   // inline fsqrt in the binary

#define HK_DECLARE_CLASS_ALLOCATOR_B(cls) \
    static void* operator new(size_t n) { void* p = hkMemory::s_instance->allocateChunk((int)n, cls); \
        ((hkReferencedObject*)p)->m_memSizeAndFlags = (hkInt16)n; return p; } \
    static void operator delete(void* p) { hkMemory::s_instance->deallocateChunk(p, ((hkReferencedObject*)p)->m_memSizeAndFlags, cls); } \
    static void* operator new(size_t, void* p) { return p; } \
    static void operator delete(void*, void*) {}

struct hkFinishLoadedObjectFlag { int m_finishing; };

struct hkQuaternion
{
    float x, y, z, w;
    void setMul(const hkQuaternion& a, const hkQuaternion& b);   // 0x01082210: this = a * b
    void normalize();                                              // 0x010821A0 (x*invLen, 0 for zero length)
};
struct hkMatrix3 { hkVector4 m_col[3]; };      // 0x30 bytes
struct hkStepInfo { float m_startTime; float m_endTime; float m_deltaTime; float m_invDeltaTime; };   // deltaTime @+8

// hkSweptTransform (0x50 bytes) and hkMotionState (0xb0 bytes)
struct hkSweptTransform
{
    hkVector4 m_centerOfMass0;      // +0x00
    hkVector4 m_centerOfMass1;      // +0x10
    hkQuaternion m_rotation0;       // +0x20
    hkQuaternion m_rotation1;       // +0x30
    hkVector4 m_centerOfMassLocal;  // +0x40
    hkSweptTransform& operator=(const hkSweptTransform& o);   // 0x01088480 (20 dword copies)
};
struct hkMotionState
{
    hkTransform m_transform;        // +0x00
    hkSweptTransform m_sweptTransform;   // +0x40
    hkVector4 m_deltaAngle;         // +0x90
    float m_objectRadius;           // +0xa0
    float m_maxLinearVelocity;      // +0xa4
    float m_maxAngularVelocity;     // +0xa8
    hkUint16 m_deactivationClass;   // +0xac
    hkUint16 m_deactivationCounter; // +0xae
    hkMotionState& operator=(const hkMotionState& o);          // 0x010888C0
};
void hkRotation_set(hkTransform* t, const hkQuaternion& q);    // hkRotation::set (0x010824A0) on the leading 3x4 of a transform
struct hkSweptTransformUtil { static void warpTo(const hkVector4& pos, const hkQuaternion& rot, hkMotionState& ms); };   // 0x0120A880
void hkMotionState_initMotionState(hkMotionState* ms, const hkVector4& pos, const hkQuaternion& rot);                      // 0x0120AC30

// ---- motions (vtable slots from the retail vtables) -------------------------------------------------------
class hkMotion : public hkReferencedObject
{
public:
    enum MotionType { MOTION_INVALID = 0, MOTION_DYNAMIC = 1, MOTION_SPHERE_INERTIA = 2, MOTION_STABILIZED_SPHERE_INERTIA = 3,
        MOTION_BOX_INERTIA = 4, MOTION_STABILIZED_BOX_INERTIA = 5, MOTION_KEYFRAMED = 6, MOTION_FIXED = 7, MOTION_THIN_BOX_INERTIA = 8 };
    virtual int getType() const;                                         // 2
    virtual void step(const hkStepInfo& stepInfo);                       // 3
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual hkMotion* clone() const;                                     // 8
    virtual void setMass(float m);                                       // 9
    virtual void setMassInv(float mInv);                                 // 10
    virtual void getInertiaLocal(hkMatrix3& out) const;                  // 11
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19();
    virtual void setPositionAndRotation(const hkVector4& pos, const hkQuaternion& rot);   // 20
    virtual void v21();
    virtual void setLinearVelocity(const hkVector4& v);                  // 22
    virtual void setAngularVelocity(const hkVector4& v);                 // 23
    virtual void applyLinearImpulse(const hkVector4& imp);               // 24
    virtual void applyPointImpulse(const hkVector4& imp, const hkVector4& p);   // 25
    virtual void applyAngularImpulse(const hkVector4& imp);              // 26
    virtual void v27(); virtual void v28(); virtual void v29();
    virtual void getMotionStateAndVelocities(hkMotion* out);             // 30

    int32_t m_solverData;                                                    // +0x08
};

class hkRigidMotion : public hkMotion
{
public:
    hkRigidMotion(const hkVector4& position, const hkQuaternion& rotation);   // 0x01088500
    // overrides implemented in this slice
    virtual void step(const hkStepInfo& stepInfo);                           // 0x01088570
    virtual void setMass(float m);                                           // 0x01088230
    virtual void setPositionAndRotation(const hkVector4& pos, const hkQuaternion& rot);   // 0x01088310
    virtual void applyLinearImpulse(const hkVector4& imp);                   // 0x010883C0
    // implemented elsewhere
    virtual void setMassInv(float mInv);                                     // 0x010882A0
    virtual void v17(); virtual void v18(); virtual void v19();              // 0x010882B0 / 0x010882D0 / 0x010882F0
    virtual void v21();                                                      // 0x01088330
    virtual void setLinearVelocity(const hkVector4& v);                      // 0x01088360
    virtual void setAngularVelocity(const hkVector4& v);                     // 0x01088390
    virtual void getMotionStateAndVelocities(hkMotion* out);                 // 0x01088960

    float getMass() const;                                                   // 0x01088270
    void setDeactivationClass(hkUint16 c);                                   // 0x01088350 (writes motionState + 0xac)

    uint32_t m_pad0c;                                                        // +0x0c (hkMotionState is 16-aligned)
    hkMotionState m_motionState;                                             // +0x10
    float m_massInv;                                                         // +0xc0
    float m_particleMinInertiaDiagInv;                                       // +0xc4
    float m_linearDamping;                                                   // +0xc8
    float m_angularDamping;                                                  // +0xcc
    hkVector4 m_linearVelocity;                                              // +0xd0
    hkVector4 m_angularVelocity;                                             // +0xe0
};

class hkFixedRigidMotion : public hkRigidMotion
{
public:
    hkFixedRigidMotion(const hkVector4& position, const hkQuaternion& rotation);   // 0x01097110
    uint32_t m_pad[4];                                                       // +0xf0 (size 0x100)
};
