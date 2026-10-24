// Slice s01127ee0 -- Havok 3.1 keyframe utilities + Spring/Reorient actions.
// Module flags: /O2 /MD /Gy /EHsc /TP /fp:fast (x87 float math; no /arch:SSE)
#include "types.h"
#include <new>
#include <math.h>
#pragma intrinsic(fabs, sqrt)

#define HK_CALL __cdecl

// Values the original keeps on the x87 stack between stores.  MSVC's x87 code
// generator extends these operands to 80 bits; this alias keeps our source from
// rounding them to float at every intermediate.
typedef double hkX87Real;

// ---------------------------------------------------------------- base types
class hkBaseObject { public:
    virtual ~hkBaseObject();
};

class hkReferencedObject : public hkBaseObject { public:
    unsigned short m_memSizeAndFlags;  // +0x4
    short          m_referenceCount;   // +0x6

    void removeReference();
    void addReference();
};

class hkTransform;

class hkVector4 { public:
    float x, y, z, w;
    void setTransformedPos(const hkTransform& t, const hkVector4& p);  // 0x01081360
};

struct hkTransform { float m[16]; };  // hkRotation (0x30) + translation (0x10)

class hkQuaternion { public:
    hkVector4 m_vec;  // +0x0
    void setMulInverse(const hkQuaternion& q0, const hkQuaternion& q1);  // 0x01091970
    void normalize();                                                     // 0x010821a0
    void getAxis(hkVector4& axis) const;                                  // 0x01127dc0
};

// hkMotion: retail layout is hkReferencedObject (vptr + 0x0c bytes) followed by
// an hkMotionState at +0x10.  hkMotionState contains m_transform at +0x10,
// then hkSweptTransform at +0x50 (centerOfMass0/1, rotation0/1, local COM).
class hkMotion { public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4c();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58(const void* p);   // +0x58 setLinearVelocity
    virtual void slot5c(const void* p);   // +0x5c setAngularVelocity
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void applyForce(float deltaTime, const hkVector4& force, const hkVector4& point);  // +0x6c

    char           pad04[0x0c];              // +0x04
    hkTransform    m_transform;              // +0x10
    hkVector4      m_centerOfMass0;          // +0x50
    hkVector4      m_centerOfMass1;          // +0x60
    hkQuaternion   m_rotation0;              // +0x70
    hkQuaternion   m_rotation1;              // +0x80
    hkVector4      m_centerOfMassLocal;      // +0x90
    hkVector4      m_deltaAngle;             // +0xa0
    float          m_objectRadius;           // +0xb0
    char           padB4[0x0c];              // +0xb4
    char           padC0[0x10];              // +0xc0
    hkVector4      m_linearVelocity;         // +0xd0
    hkVector4      m_angularVelocity;        // +0xe0
};

struct hkEntity;

// Out-of-line and size-optimized so the virtual call stays memory-indirect, like the
// retail call site; loading the vtable slot into a register changes the checker's
// call-site observation for synthetic motion vtables.
#pragma optimize("s", on)
__declspec(noinline) static void motionSetLinearVelocity(hkMotion* m, const void* p)
{
    m->slot58(p);
}
#pragma optimize("", on)

class hkRigidBody { public:
    char      pad00[0x58];
    hkMotion* m_motion;  // +0x58

    void setPositionAndRotation(const hkVector4& position, const hkQuaternion& rotation);  // 0x01087860
    void activate();                                                                        // 0x01088ae0
    void getPointVelocity(const hkVector4& point, hkVector4& velocity) const;              // 0x0108cf90
};

struct hkpRigidBody : hkRigidBody {};

// Thread memory helpers (used by hkArray destructors).
class hkThreadMemory { public:
    void deallocateChunk(void* p, int size, int memClass);
};
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern unsigned long g_hkTlsIndex;

// ---------------------------------------------------------------- KeyFrameUtility
class hkKeyFrameUtility {
public:
    struct AccelerationInfo {
        hkVector4 m_linearPositionFactor;    // +0x00
        hkVector4 m_angularPositionFactor;   // +0x10
        hkVector4 m_linearVelocityFactor;    // +0x20
        hkVector4 m_angularVelocityFactor;   // +0x30
        float     m_maxLinearAcceleration;   // +0x40
        float     m_maxAngularAcceleration;  // +0x44
        float     m_maxAllowedDistance;      // +0x48
    };

    struct KeyFrameInfo {
        hkVector4    m_position;          // +0x00
        hkQuaternion m_orientation;       // +0x10
        hkVector4    m_linearVelocity;    // +0x20
        hkVector4    m_angularVelocity;   // +0x30
    };

    static void HK_CALL applySoftKeyFrame(const KeyFrameInfo& keyFrameInfo, AccelerationInfo& accelInfo,
                                          float deltaTime, float invDeltaTime, hkpRigidBody* body);
    static void HK_CALL applyHardKeyFrame(const hkVector4& nextPosition, const hkQuaternion& nextOrientation,
                                          float invDeltaTime, hkpRigidBody* body);
};

extern "C" float hkAcos(float x);   // 0x011e08c8
extern "C" float hkSqrt(float x);

// @ 0x01127ee0 -- behaviourally-faithful reconstruction (not byte-exact).
void HK_CALL hkKeyFrameUtility::applySoftKeyFrame(const KeyFrameInfo& keyFrameInfo, AccelerationInfo& accelInfo,
                                                  float deltaTime, float invDeltaTime, hkpRigidBody* body)
{
    (void)invDeltaTime;
    hkMotion* motion = body->m_motion;

    hkVector4 positionDelta;
    positionDelta.x = keyFrameInfo.m_position.x - motion->m_centerOfMassLocal.x;
    positionDelta.y = keyFrameInfo.m_position.y - motion->m_centerOfMassLocal.y;
    positionDelta.z = keyFrameInfo.m_position.z - motion->m_centerOfMassLocal.z;
    positionDelta.w = keyFrameInfo.m_position.w - motion->m_centerOfMassLocal.w;

    float maxAllowedDistance = accelInfo.m_maxAllowedDistance;
    float distSq = positionDelta.x * positionDelta.x + positionDelta.y * positionDelta.y
                 + positionDelta.z * positionDelta.z;

    if (maxAllowedDistance * maxAllowedDistance < distSq) {
        positionDelta.x = 0.0f;
        positionDelta.y = 0.0f;
        positionDelta.z = 0.0f;
        positionDelta.w = 0.0f;

        body->setPositionAndRotation(keyFrameInfo.m_position, keyFrameInfo.m_orientation);
        body->activate();
        motion->slot5c(&keyFrameInfo.m_angularVelocity);
        body->activate();
        motion->slot58(&keyFrameInfo.m_linearVelocity);
    }

    motion = body->m_motion;

    hkQuaternion inv;
    inv.setMulInverse(keyFrameInfo.m_orientation, motion->m_rotation1);
    inv.normalize();

    hkVector4 deltaAngle;
    deltaAngle.x = inv.m_vec.x + inv.m_vec.x;
    deltaAngle.y = inv.m_vec.y + inv.m_vec.y;
    deltaAngle.z = inv.m_vec.z + inv.m_vec.z;
    deltaAngle.w = inv.m_vec.w + inv.m_vec.w;

    if (inv.m_vec.w < 0.0f) {
        deltaAngle.x = -deltaAngle.x;
        deltaAngle.y = -deltaAngle.y;
        deltaAngle.z = -deltaAngle.z;
        deltaAngle.w = -deltaAngle.w;
    }

    hkVector4 linearTerm;
    linearTerm.x = positionDelta.x * accelInfo.m_linearPositionFactor.x;
    linearTerm.y = positionDelta.y * accelInfo.m_linearPositionFactor.y;
    linearTerm.z = positionDelta.z * accelInfo.m_linearPositionFactor.z;
    linearTerm.w = positionDelta.w * accelInfo.m_linearPositionFactor.w;

    hkVector4 vel = keyFrameInfo.m_linearVelocity;
    vel.x *= deltaTime;
    vel.y *= deltaTime;
    vel.z *= deltaTime;
    vel.w *= deltaTime;

    hkVector4 outPos;
    outPos.x = linearTerm.x + vel.x;
    outPos.y = linearTerm.y + vel.y;
    outPos.z = linearTerm.z + vel.z;
    outPos.w = linearTerm.w + vel.w;

    float maxLin = deltaTime * accelInfo.m_maxLinearAcceleration;
    float lenSq = outPos.x * outPos.x + outPos.y * outPos.y + outPos.z * outPos.z;
    if (maxLin * maxLin < lenSq) {
        float s = maxLin / hkSqrt(lenSq);
        outPos.x = s * outPos.x;
        outPos.y = s * outPos.y;
        outPos.z = s * outPos.z;
    }

    hkVector4 outAng;
    outAng.x = deltaAngle.x * deltaTime;
    outAng.y = deltaAngle.y * deltaTime;
    outAng.z = deltaAngle.z * deltaTime;
    outAng.w = deltaAngle.w * deltaTime;

    float maxAng = deltaTime * accelInfo.m_maxAngularAcceleration;
    float angLenSq = outAng.x * outAng.x + outAng.y * outAng.y + outAng.z * outAng.z;
    if (maxAng * maxAng < angLenSq) {
        float s = maxAng / hkSqrt(angLenSq);
        outAng.x = s * outAng.x;
        outAng.y = s * outAng.y;
        outAng.z = s * outAng.z;
    }

    outPos.x += motion->m_centerOfMass1.x;
    outPos.y += motion->m_centerOfMass1.y;
    outPos.z += motion->m_centerOfMass1.z;
    outPos.w += motion->m_centerOfMass1.w;

    outAng.x += motion->m_rotation1.m_vec.x;
    outAng.y += motion->m_rotation1.m_vec.y;
    outAng.z += motion->m_rotation1.m_vec.z;
    outAng.w += motion->m_rotation1.m_vec.w;

    body->activate();
    motion->slot5c(&outAng);
    body->activate();
    motion->slot58(&outPos);
}

// @ 0x011282f0 -- behaviourally-faithful reconstruction (not byte-exact).
void HK_CALL hkKeyFrameUtility::applyHardKeyFrame(const hkVector4& nextPosition, const hkQuaternion& nextOrientation,
                                                  float invDeltaTime, hkpRigidBody* body)
{
    hkMotion* motion = body->m_motion;
    const hkVector4& q = nextOrientation.m_vec;
    const hkVector4& v = motion->m_centerOfMassLocal;

    // Rotate the motion's local centre of mass by nextOrientation.  This is the
    // half-angle form of the quaternion rotation, doubled again before the world
    // offset is added.  A, dot and the half products are rounded to float by the
    // original; the two cross components and the doubled terms stay in x87.
    float A = q.w * q.w - 0.5f;
    float dot = (q.y * v.y + q.z * v.z) + q.x * v.x;
    float xh = dot * q.x + A * v.x;
    float yh = dot * q.y + A * v.y;
    float zh = dot * q.z + A * v.z;
    float wh = dot * q.w + A * v.w;

    float cz = v.y * q.x - q.y * v.x;

    float X = xh + (q.y * v.z - v.y * q.z) * q.w;
    float Y = yh + (q.z * v.x - v.z * q.x) * q.w;
    float Z = zh + cz * q.w;
    float W = wh;

    hkVector4 delta;
    float target;
    target = X + X + nextPosition.x;
    float d = target - motion->m_centerOfMass1.x;
    delta.x = d * invDeltaTime;
    target = Y + Y + nextPosition.y;
    d = target - motion->m_centerOfMass1.y;
    delta.y = d * invDeltaTime;
    target = Z + Z + nextPosition.z;
    d = target - motion->m_centerOfMass1.z;
    delta.z = d * invDeltaTime;
    target = W + W + nextPosition.w;
    d = target - motion->m_centerOfMass1.w;
    delta.w = d * invDeltaTime;

    body->activate();
    motion = body->m_motion;  // activate() may replace the motion state
    motionSetLinearVelocity(motion, &delta);

    hkQuaternion inv;
    inv.setMulInverse(nextOrientation, motion->m_rotation1);
    inv.normalize();

    // The retail code branches on the extended-precision |w| but passes the
    // float-rounded copy to acos.  C0 is set for unordered too, so a NaN |w|
    // takes the acos path.
    hkX87Real absWx = fabs((hkX87Real)inv.m_vec.w);
    float absW = (float)absWx;
    float angle;
    if (!(absWx >= 1.0)) {
        angle = acosf(absW);
    } else if (absW <= 0.0f) {
        angle = 3.1415927f;
    } else {
        angle = 0.0f;
    }
    hkX87Real angle2x = (hkX87Real)angle + angle;
    float angle2 = (float)angle2x;

    hkVector4 angular;
    angular.x = 0.0f;
    angular.y = 0.0f;
    angular.z = 0.0f;
    angular.w = 0.0f;
    if (!(angle2x < 0.001)) {
        hkVector4 axis;
        inv.getAxis(axis);
        float s = angle2 * invDeltaTime;
        angular.x = axis.x * s;
        angular.y = axis.y * s;
        angular.z = axis.z * s;
        angular.w = axis.w * s;
    }

    body->activate();
    body->m_motion->slot5c(&angular);
}

// ---------------------------------------------------------------- Spring action
struct hkStepInfo;
struct hkBinaryActionBase {
    virtual void vf();
    char pad04[0x14];            // +0x04..+0x17
    hkRigidBody* m_entityA;      // +0x18
    hkRigidBody* m_entityB;      // +0x1c
    hkBinaryActionBase(hkEntity* a, hkEntity* b, unsigned int ud);
};

class hkSpringAction : public hkBinaryActionBase { public:
    hkVector4 m_lastForce;       // +0x20
    hkVector4 m_positionAinA;    // +0x30
    hkVector4 m_positionBinB;    // +0x40
    float     m_restLength;      // +0x50
    float     m_strength;        // +0x54
    float     m_damping;         // +0x58
    char      onCompression;     // +0x5c
    char      onExtension;       // +0x5d

    hkSpringAction(hkEntity* a, hkEntity* b, unsigned int userData);
    void applyAction(const hkStepInfo& stepInfo);
    hkSpringAction* clone(const void* newEntities, const void* newPhantoms) const;
};

class hkStepInfo { public: float m_startTime, m_endTime, m_deltaTime, m_invDeltaTime; };

struct hkMemoryVtbl {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void* alloc(int size, int align);
};
extern hkMemoryVtbl g_hkMemoryInstance;  // 0x016e4178

// @ 0x011285f0
hkSpringAction::hkSpringAction(hkEntity* a, hkEntity* b, unsigned int userData)
  : hkBinaryActionBase(a, b, userData)
{
    m_restLength = 1.0f;
    m_strength = 1000.0f;
    m_damping = 0.1f;
    char flag = 1;
    onCompression = flag;
    onExtension = flag;
}

// @ 0x01128640 -- behaviourally-faithful reconstruction (not byte-exact).
void hkSpringAction::applyAction(const hkStepInfo& stepInfo)
{
    hkRigidBody* ea = m_entityA;
    hkRigidBody* eb = m_entityB;

    hkVector4 pointA, pointB;
    pointA.setTransformedPos(ea->m_motion->m_transform, m_positionAinA);
    pointB.setTransformedPos(eb->m_motion->m_transform, m_positionBinB);

    // X87-PRECISION: the four delta components stay in registers while the
    // squared length is accumulated.
    hkX87Real dx = (hkX87Real)pointB.x - pointA.x;
    hkX87Real dy = (hkX87Real)pointB.y - pointA.y;
    hkX87Real dz = (hkX87Real)pointB.z - pointA.z;
    hkX87Real dw = (hkX87Real)pointB.w - pointA.w;
    hkX87Real len2 = (dz * dz + dy * dy) + dx * dx;
    float length = (float)sqrt((double)len2);
    if (!(length >= 0.001f))
        return;

    // X87-PRECISION: the reciprocal length is kept on the x87 stack; each
    // normalized component is rounded once, at its store.
    hkX87Real invLen = (hkX87Real)1.0f / (hkX87Real)length;
    hkVector4 dir;
    dir.x = (float)(dx * invLen);
    dir.y = (float)(dy * invLen);
    dir.z = (float)(dz * invLen);
    dir.w = (float)(dw * invLen);

    if (!onCompression && !(length >= m_restLength))
        return;
    if (!onExtension && !(length <= m_restLength))
        return;

    hkVector4 velA, velB;
    ea->getPointVelocity(pointA, velA);
    eb->getPointVelocity(pointB, velB);

    hkX87Real rx = (hkX87Real)velB.x - velA.x;
    hkX87Real ry = (hkX87Real)velB.y - velA.y;
    hkX87Real rz = (hkX87Real)velB.z - velA.z;

    float force = (float)(((rz * dir.z + ry * dir.y) + rx * dir.x) * m_damping
                          + ((hkX87Real)length - m_restLength) * m_strength);

    hkX87Real negForce = -(hkX87Real)force;
    m_lastForce.x = (float)((hkX87Real)dir.x * negForce);
    m_lastForce.y = (float)((hkX87Real)dir.y * negForce);
    m_lastForce.z = (float)((hkX87Real)dir.z * negForce);
    m_lastForce.w = (float)((hkX87Real)dir.w * negForce);

    eb->activate();
    eb->m_motion->applyForce(stepInfo.m_deltaTime, m_lastForce, pointB);

    m_lastForce.x = (float)((hkX87Real)dir.x * force);
    m_lastForce.y = (float)((hkX87Real)dir.y * force);
    m_lastForce.z = (float)((hkX87Real)dir.z * force);
    m_lastForce.w = (float)((hkX87Real)dir.w * force);

    ea->activate();
    ea->m_motion->applyForce(stepInfo.m_deltaTime, m_lastForce, pointA);
}

// @ 0x01128850 -- behaviourally-faithful reconstruction (not byte-exact).
hkSpringAction* hkSpringAction::clone(const void* newEntities, const void* newPhantoms) const
{
    const int* entities = (const int*)newEntities;
    const int* phantoms = (const int*)newPhantoms;
    if (entities[1] == 2 && phantoms[1] == 0) {
        hkSpringAction* a = (hkSpringAction*)g_hkMemoryInstance.alloc(0x60, 0x26);
        *(unsigned short*)((char*)a + 4) = 0x60;
        hkEntity* e0 = *(hkEntity**)entities[0];
        hkEntity* e1 = ((hkEntity**)entities[0])[1];
        new (a) hkSpringAction(e0, e1, *(unsigned int*)((const char*)this + 0x10));
        char* d = (char*)a;
        const char* s = (const char*)this;
        *(hkVector4*)(d + 0x30) = *(const hkVector4*)(s + 0x30);
        *(hkVector4*)(d + 0x40) = *(const hkVector4*)(s + 0x40);
        *(float*)(d + 0x50) = *(const float*)(s + 0x50);
        *(float*)(d + 0x54) = *(const float*)(s + 0x54);
        *(float*)(d + 0x58) = *(const float*)(s + 0x58);
        *(char*)(d + 0x5c) = *(const char*)(s + 0x5c);
        *(char*)(d + 0x5d) = *(const char*)(s + 0x5d);
        return a;
    }
    return 0;
}

// ---------------------------------------------------------------- marker list
struct hkpSerializedDisplayMarker : hkReferencedObject {
    char m_transform[0x48];  // hkTransform
};

struct hkpSerializedDisplayMarkerList : hkReferencedObject {
    hkpSerializedDisplayMarker** m_data;      // +0x8
    int                          m_size;      // +0xc
    int                          m_capacity;  // +0x10

    virtual ~hkpSerializedDisplayMarkerList();
};

// @ 0x011289f0
hkpSerializedDisplayMarkerList::~hkpSerializedDisplayMarkerList()
{
    for (int i = 0; i < m_size; ++i) {
        hkpSerializedDisplayMarker* m = m_data[i];
        if (m->m_memSizeAndFlags != 0) {
            if (--m->m_referenceCount == 0) {
                (*(void(__thiscall**)(hkpSerializedDisplayMarker*, int))*(void**)m)(m, 1);
            }
        }
    }
    if (m_capacity >= 0) {
        hkThreadMemory* mem = (hkThreadMemory*)TlsGetValue(g_hkTlsIndex);
        mem->deallocateChunk(m_data, (m_capacity & 0x3fffffff) * 4, 0x14);
    }
}

// ---------------------------------------------------------------- reorient action
struct hkReorientBase {
    virtual void vf();
    char pad[0x1c];
    hkReorientBase(hkRigidBody* body, unsigned int ud);
};

struct hkpReorientAction : hkReorientBase {
    hkVector4 m_rotationAxis;  // +0x20
    hkVector4 m_upAxis;        // +0x30
    float     m_strength;      // +0x40
    float     m_damping;       // +0x44

    hkpReorientAction(hkRigidBody* body, const hkVector4& rotationAxis,
                      const hkVector4& upAxis, float strength, float damping);
};

// @ 0x01128ad0
hkpReorientAction::hkpReorientAction(hkRigidBody* body, const hkVector4& rotationAxis,
                                     const hkVector4& upAxis, float strength, float damping)
  : hkReorientBase(body, 0)
{
    m_rotationAxis = rotationAxis;
    m_upAxis = upAxis;
    m_strength = strength;
    m_damping = damping;
}

// ---------------------------------------------------------------- 01128910
struct hkWorldObjectWrapper {
    void* mpObject;  // +0x00
    char  pad04[0x4c];
};

struct hkObjectList3006d0 : hkReferencedObject {
    hkWorldObjectWrapper* m_data;      // +0x8
    int                   m_size;      // +0xc
    int                   m_capacity;  // +0x10

    ~hkObjectList3006d0();
};

// @ 0x01128910
hkObjectList3006d0::~hkObjectList3006d0()
{
    int n = m_size;
    if (n > 0) {
        int off = 0;
        do {
            ((hkReferencedObject*)*(void**)((char*)m_data + off))->removeReference();
            off += 0x50;
        } while (--n);
    }
    if (m_capacity >= 0) {
        hkThreadMemory* mem = (hkThreadMemory*)TlsGetValue(g_hkTlsIndex);
        mem->deallocateChunk(m_data, m_capacity * 0x50, 0x14);
    }
}
