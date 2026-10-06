// Slice s01127ee0 -- Havok 3.1 keyframe utilities + Spring/Reorient actions.
// Module flags: /O2 /MD /Gy /EHsc /TP (x87 float math; no /arch:SSE)
#include "types.h"
#include <new>

#define HK_CALL __cdecl

// ---------------------------------------------------------------- base types
struct hkBaseObject {
    virtual ~hkBaseObject();
};

struct hkReferencedObject : hkBaseObject {
    unsigned short m_memSizeAndFlags;  // +0x4
    short          m_referenceCount;   // +0x6

    void removeReference();
    void addReference();
};

struct hkVector4 { float x, y, z, w; };

struct hkQuaternion {
    hkVector4 m_vec;  // +0x0
    void setMulInverse(const hkQuaternion& q0, const hkQuaternion& q1);  // 0x01091970
    void normalize();                                                     // 0x010821a0
    void getAxis(hkVector4& axis) const;                                  // 0x01127dc0
};

struct hkMotion {
    char           pad00[0x40];
    hkVector4      m_centreOfMassLocal;   // +0x40
    char           pad50[0x30];
    char           pad80[0x50];
    hkVector4      m_sweptWorldPos;       // +0xd0
    hkQuaternion   m_sweptWorldRot;       // +0xe0

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
    virtual void setPosition(const void* p);   // +0x58
    virtual void setRotation(const void* p);   // +0x5c
};

struct hkEntity;

struct hkRigidBody {
    char      pad00[0x58];
    hkMotion* m_motion;  // +0x58

    void setPositionAndRotation(const hkVector4& position, const hkQuaternion& rotation);  // 0x01087860
    void activate();                                                                        // 0x01088ae0
    void getPointVelocity(const hkVector4& point, hkVector4& velocity) const;              // 0x0108cf90
};

struct hkpRigidBody : hkRigidBody {};

// Thread memory helpers (used by hkArray destructors).
struct hkThreadMemory {
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
    positionDelta.x = keyFrameInfo.m_position.x - motion->m_centreOfMassLocal.x;
    positionDelta.y = keyFrameInfo.m_position.y - motion->m_centreOfMassLocal.y;
    positionDelta.z = keyFrameInfo.m_position.z - motion->m_centreOfMassLocal.z;
    positionDelta.w = keyFrameInfo.m_position.w - motion->m_centreOfMassLocal.w;

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
        motion->setRotation(&keyFrameInfo.m_angularVelocity);
        body->activate();
        motion->setPosition(&keyFrameInfo.m_linearVelocity);
    }

    motion = body->m_motion;

    hkQuaternion inv;
    inv.setMulInverse(keyFrameInfo.m_orientation, motion->m_sweptWorldRot);
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

    outPos.x += motion->m_sweptWorldPos.x;
    outPos.y += motion->m_sweptWorldPos.y;
    outPos.z += motion->m_sweptWorldPos.z;
    outPos.w += motion->m_sweptWorldPos.w;

    outAng.x += motion->m_sweptWorldRot.m_vec.x;
    outAng.y += motion->m_sweptWorldRot.m_vec.y;
    outAng.z += motion->m_sweptWorldRot.m_vec.z;
    outAng.w += motion->m_sweptWorldRot.m_vec.w;

    body->activate();
    motion->setRotation(&outAng);
    body->activate();
    motion->setPosition(&outPos);
}

// @ 0x011282f0 -- behaviourally-faithful reconstruction (not byte-exact).
void HK_CALL hkKeyFrameUtility::applyHardKeyFrame(const hkVector4& nextPosition, const hkQuaternion& nextOrientation,
                                                  float invDeltaTime, hkpRigidBody* body)
{
    hkMotion* motion = body->m_motion;

    hkQuaternion q = nextOrientation;
    float twoQw = q.m_vec.w + q.m_vec.w;
    hkVector4 up;
    up.x = q.m_vec.x * twoQw;
    up.y = q.m_vec.y * twoQw;
    up.z = q.m_vec.z * twoQw;
    up.w = q.m_vec.w * twoQw;

    hkVector4 newPos;
    newPos.x = up.x * 0.0f + nextPosition.x;
    newPos.y = up.y * 0.0f + nextPosition.y;
    newPos.z = up.z * 0.0f + nextPosition.z;
    newPos.w = up.w * 0.0f + nextPosition.w;

    hkVector4 delta;
    delta.x = (newPos.x - motion->m_centreOfMassLocal.x) * invDeltaTime;
    delta.y = (newPos.y - motion->m_centreOfMassLocal.y) * invDeltaTime;
    delta.z = (newPos.z - motion->m_centreOfMassLocal.z) * invDeltaTime;
    delta.w = (newPos.w - motion->m_centreOfMassLocal.w) * invDeltaTime;

    body->activate();
    motion->setPosition(&delta);

    hkQuaternion inv;
    inv.setMulInverse(nextOrientation, motion->m_sweptWorldRot);
    inv.normalize();

    float absW = inv.m_vec.w < 0.0f ? -inv.m_vec.w : inv.m_vec.w;
    float angle;
    if (absW < 1.0f) {
        angle = hkAcos(absW);
    } else if (absW <= 0.0f) {
        angle = 3.1415927f;
    } else {
        angle = 0.0f;
    }
    angle = angle + angle;

    hkVector4 axis; axis.x = 0.0f; axis.y = 0.0f; axis.z = 0.0f; axis.w = 0.0f;
    hkVector4 angular; angular.x = 0.0f; angular.y = 0.0f; angular.z = 0.0f; angular.w = 0.0f;
    if (0.001f <= angle) {
        inv.getAxis(axis);
        float s = angle * invDeltaTime;
        angular.x = axis.x * s;
        angular.y = axis.y * s;
        angular.z = axis.z * s;
        angular.w = axis.w * s;
    }

    body->activate();
    motion->setRotation(&angular);
}

// ---------------------------------------------------------------- Spring action
struct hkBinaryActionBase {
    virtual void vf();
    char pad[0x1c];
    hkBinaryActionBase(hkEntity* a, hkEntity* b, unsigned int ud);
};

struct hkSpringAction : hkBinaryActionBase {
    hkVector4 m_lastForce;       // +0x20
    hkVector4 m_positionAinA;    // +0x30
    hkVector4 m_positionBinB;    // +0x40
    float     m_restLength;      // +0x50
    float     m_strength;        // +0x54
    float     m_damping;         // +0x58
    char      onCompression;     // +0x5c
    char      onExtension;       // +0x5d

    hkSpringAction(hkEntity* a, hkEntity* b, unsigned int userData);
    void applyAction(const void* stepInfo);
    hkSpringAction* clone(const void* newEntities, const void* newPhantoms) const;
};

struct hkStepInfo { float m_startTime, m_endTime, m_deltaTime, m_invDeltaTime; };

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
void hkSpringAction::applyAction(const void* stepInfoRaw)
{
    const hkStepInfo& stepInfo = *(const hkStepInfo*)stepInfoRaw;
    hkRigidBody* ea = *(hkRigidBody**)((char*)this + 0x18);
    hkRigidBody* eb = *(hkRigidBody**)((char*)this + 0x1c);

    hkVector4 worldA, worldB;
    ea->m_motion->setPosition(&m_positionAinA);
    eb->m_motion->setPosition(&m_positionBinB);
    (void)worldA; (void)worldB;
    (void)stepInfo;
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
