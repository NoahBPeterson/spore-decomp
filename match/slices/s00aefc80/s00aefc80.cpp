// Slice s00aefc80 (batch op3_big) — 0x00aefc80, 3163 bytes.
//
// SP::SPCreatureProxy::StepDeltaTime(float dt)   (retail layout; __thiscall, ret 4)
//
// The 0x150-byte proxy (constructed by 0x00aefb80) owns an SPDynamicsParticle at +0x80
// and a keyframed hkRigidBody at +0x54.  Each step:
//   1. If the body has contacts (+0x5c > 0) and is not hard-keyframed, the particle is
//      pulled back to within 0.1 of the body when it drifted too far (or the body's
//      forward axis points into the particle's support normal), then de-penetrated.
//   2. The particle is stepped (SPDynamicsParticle::StepDeltaTime), with surface
//      constraints built in two hkLocalArrays from the proxy's contact planes (plus the
//      particle's own support plane when it is supported) if +0x00 is set.
//   3. FUN_00aef410, then the body is keyframed (soft for mode 0, hard for mode 1) to the
//      particle position with an orientation that is either the stored quaternion or
//      a frame aligned to the (blended) surface up vector.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same module as s00af8b50).

#include "types.h"
#include <math.h>

#pragma pack(push, 8)

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);

typedef float hkReal;

class hkRotation;
class hkQuaternion;

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
    void operator=(const hkVector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    hkReal& operator()(int i) { return (&x)[i]; }
    void setZero4() { x = y = z = w = 0.0f; }
    void set(hkReal a, hkReal b, hkReal c, hkReal d = 0.0f) { x = a; y = b; z = c; w = d; }
    void setAll(hkReal a) { x = a; y = a; z = a; w = a; }
    void mul4(hkReal s) { x *= s; y *= s; z *= s; w *= s; }
    hkReal lengthSquared3() const { return x * x + y * y + z * z; }
    hkReal dot3(const hkVector4& a) const { return x * a.x + y * a.y + z * a.z; }
    void setInterpolate4(const hkVector4& a, const hkVector4& b, hkReal t)
    {
        const hkReal s = 1.0f - t;
        x = s * a.x + t * b.x;
        y = s * a.y + t * b.y;
        z = s * a.z + t * b.z;
        w = s * a.w + t * b.w;
    }
    void setCross(const hkVector4& v1, const hkVector4& v2)
    {
        const hkReal nx = v1.y * v2.z - v1.z * v2.y;
        const hkReal ny = v1.z * v2.x - v1.x * v2.z;
        const hkReal nz = v1.x * v2.y - v1.y * v2.x;
        set(nx, ny, nz, 0.0f);
    }
    inline void normalize3();
    __forceinline void setRotatedDir(const hkQuaternion& quat, const hkVector4& direction);
    void setRotatedDir(const hkRotation& r, const hkVector4& v);     // 0x010814A0
};

static __forceinline hkReal hkSqrtInverse(hkReal r) { return (hkReal)(1.0f / sqrt(r)); }

void hkVector4::normalize3()
{
    const hkReal lenSq = lengthSquared3();
    const hkReal inv = (lenSq == 0.0f) ? 0.0f : hkSqrtInverse(lenSq);
    mul4(inv);
}

class hkQuaternion {
public:
    hkVector4 m_vec;
    void set(const hkRotation& r);                                   // 0x01082490
};

class hkRotation {
public:
    hkVector4 m_col0, m_col1, m_col2;
    void set(const hkQuaternion& q);                                 // 0x010824A0
    void setCols(const hkVector4& c0, const hkVector4& c1, const hkVector4& c2)
    {
        m_col0 = c0;
        m_col1 = c1;
        m_col2 = c2;
    }
};

extern const hkVector4 g_hkQuadRealMinusHalf;                              // 0x0149D620 (-0.5 x4)

// FPU hkVector4::setRotatedDir(const hkQuaternion&, const hkVector4&) of Havok 3.
void hkVector4::setRotatedDir(const hkQuaternion& quat, const hkVector4& direction)
{
    const hkReal qreal = quat.m_vec.w;
    const hkReal q2 = qreal * qreal;
    hkVector4 ret = g_hkQuadRealMinusHalf;
    ret.x = (ret.x + q2) * direction.x;
    ret.y = (ret.y + q2) * direction.y;
    ret.z = (ret.z + q2) * direction.z;
    const hkReal imagDotDir = quat.m_vec.dot3(direction);
    ret.x += quat.m_vec.x * imagDotDir;
    ret.y += quat.m_vec.y * imagDotDir;
    ret.z += quat.m_vec.z * imagDotDir;
    hkVector4 imagCrossDir;
    imagCrossDir.setCross(quat.m_vec, direction);
    ret.x += imagCrossDir.x * qreal;
    ret.y += imagCrossDir.y * qreal;
    ret.z += imagCrossDir.z * qreal;
    x = ret.x * 2.0f;
    y = ret.y * 2.0f;
    z = ret.z * 2.0f;
    w = ret.w;
}

class hkTransform {
public:
    hkRotation m_rotation;
    hkVector4 m_translation;
};

struct hkMotion {
    uint32_t pad00[4];
    hkTransform m_transform;                    // +0x10
    hkVector4 m_centerOfMass0;                  // +0x50
    hkVector4 m_centerOfMass1;                  // +0x60
};

class hkWorld;

class hkRigidBody {
public:
    uint32_t pad00[2];
    hkWorld* m_world;                           // +0x08
    uint32_t pad0c[(0x58 - 0x0c) / 4];
    hkMotion* m_motion;                         // +0x58
};

// ---- hkThreadMemory stack allocator / hkArray / hkLocalArray (Havok 3.1) ------------------
extern unsigned long g_hkThreadMemoryTls;       // 0x016E4174

struct hkThreadMemory {
    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    virtual void* onStackOverflow(int numBytes);         // +0x0c
    virtual void onStackUnderflow(void* p);               // +0x10
    uint32_t pad04[7];
    char* m_stackCurrent;     // +0x20
    char* m_stackPrev;        // +0x24
    char* m_stackBase;        // +0x28
    char* m_stackEnd;         // +0x2c
    void deallocateChunk(void* p, int numBytes, int memoryClass);          // 0x0107DB10

    static __forceinline hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls); }
};
enum { HK_MEMORY_CLASS_ARRAY = 0x14 };

template <typename T> __forceinline T* hkAllocateStack(int n)
{
    hkThreadMemory& tm = hkThreadMemory::getInstance();
    int size = (n * (int)sizeof(T) + 0x10) & ~0xf;
    char* cur = tm.m_stackCurrent;
    char* next = cur + size;
    if ((uint32_t)next > (uint32_t)tm.m_stackEnd)
        return (T*)tm.onStackOverflow(size);
    tm.m_stackCurrent = next;
    return (T*)cur;
}
template <typename T> __forceinline void hkDeallocateStack(T* p)
{
    hkThreadMemory& tm = hkThreadMemory::getInstance();
    tm.m_stackCurrent = (char*)p;
    if ((char*)p == tm.m_stackBase)
        tm.onStackUnderflow(p);
}

template <typename T> struct hkArray {
    enum { CAPACITY_MASK = 0x3fffffff, DONT_DEALLOCATE_FLAG = 0x80000000 };
    T* m_data;
    int m_size;
    int m_capacityAndFlags;

    hkArray() : m_data(0), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}
    __forceinline ~hkArray() { releaseMemory(); }
    __forceinline void releaseMemory()
    {
        if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
            hkThreadMemory::getInstance().deallocateChunk(m_data, getCapacity() * sizeof(T), HK_MEMORY_CLASS_ARRAY);
    }
    int getSize() const { return m_size; }
    int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
    T& operator[](int i) { return m_data[i]; }
    void setSizeUnchecked(int n) { m_size = n; }
};

template <typename T> struct hkLocalArray : hkArray<T> {
    T* m_localMemory;
    __forceinline hkLocalArray(int capacity)
    {
        this->m_data = hkAllocateStack<T>(capacity);
        this->m_capacityAndFlags = capacity | hkArray<T>::DONT_DEALLOCATE_FLAG;
        m_localMemory = this->m_data;
    }
    __forceinline ~hkLocalArray() { hkDeallocateStack(m_localMemory); }
};

struct hkSurfaceConstraintInfo {
    hkVector4 m_plane;                          // +0x00
    hkVector4 m_velocity;                       // +0x10
    hkReal m_staticFriction;                    // +0x20
    hkReal m_extraUpStaticFriction;             // +0x24
    hkReal m_extraDownStaticFriction;           // +0x28
    hkReal m_dynamicFriction;                   // +0x2c
    int m_priority;                             // +0x30
};

struct hkSurfaceConstraintInteraction {
    uint32_t m_data[4];
};

class hkKeyFrameUtility {
public:
    struct AccelerationInfo {
        hkVector4 m_linearPositionFactor;       // +0x00
        hkVector4 m_angularPositionFactor;      // +0x10
        hkVector4 m_linearVelocityFactor;       // +0x20
        hkVector4 m_angularVelocityFactor;      // +0x30
        hkReal m_maxLinearAcceleration;         // +0x40
        hkReal m_maxAngularAcceleration;        // +0x44
        hkReal m_maxAllowedDistance;            // +0x48
        AccelerationInfo();                     // 0x01127E90
    };
    struct KeyFrameInfo {
        hkVector4 m_position;                   // +0x00
        hkQuaternion m_orientation;             // +0x10
        hkVector4 m_linearVelocity;             // +0x20
        hkVector4 m_angularVelocity;            // +0x30
    };
    static void applySoftKeyFrame(const KeyFrameInfo& keyFrameInfo, AccelerationInfo& accelInfo,
                                  hkReal deltaTime, hkReal invDeltaTime, hkRigidBody* body);   // 0x01127EE0
    static void applyHardKeyFrame(const hkVector4& nextPosition, const hkQuaternion& nextOrientation,
                                  hkReal invDeltaTime, hkRigidBody* body);                    // 0x011282F0
};

extern hkVector4 g_hkZeroVector;                                     // 0x016E42D0

namespace SP {

struct Vector3 { float x, y, z; };

extern Vector3 g_kProxyForwardAxis;                                  // 0x0167AD68
extern const float g_kProxyMaxDriftSq;                                     // 0x01567270
extern const float g_kContactStaticFriction;                               // 0x01567274
extern const float g_kContactDynamicFriction;                              // 0x01567278
extern const float g_kSoftKeyFramePositionFactor;                          // 0x01567250
extern const float g_kSoftKeyFrameRotationFactor;                          // 0x01567254

hkVector4 GetUpVector(const hkVector4& position);                                      // 0x00B65710
void ResolvePenetration(const hkVector4* probe, const hkVector4* position, hkWorld* world,
                        hkVector4* out);                                                // 0x00AF86C0

struct SPSurfaceConstraints {
    hkArray<hkSurfaceConstraintInfo>* m_constraints;
    hkArray<hkSurfaceConstraintInteraction>* m_interactions;
};

class SPDynamicsParticle {
public:
    bool m_enabled;                             // +0x00
    uint32_t pad04[3];
    hkVector4 m_pos;                            // +0x10
    hkVector4 m_vel;                            // +0x20
    uint32_t pad30[(0x4c - 0x30) / 4];
    int m_supportState;                         // +0x4c
    hkVector4 m_supportNormal;                  // +0x50
    uint32_t pad60[2];
    void* m_supportBody;                        // +0x68
    uint32_t pad6c[(0xc0 - 0x6c) / 4];

    hkVector4 GetSupportNormal() const;                                              // 0x00AF8520
    void SnapToGround();                                                             // 0x00AF8540
    void StepDeltaTime(float dt, SPSurfaceConstraints* pConstraints);                // 0x00AF8B50
};

struct SPContactPlane {
    hkVector4 m_position;                       // +0x00
    hkVector4 m_10;                             // +0x10
    hkVector4 m_normal;                         // +0x20
};

class SPCreatureProxy {
public:
    bool m_useContactConstraints;               // +0x00
    bool m_hasContacts;                         // +0x01
    uint32_t pad04[(0x24 - 0x04) / 4];
    float m_positionBlendAlpha;                 // +0x24
    bool m_alignToSurface;                      // +0x28
    int m_keyFrameMode;                         // +0x2c  0 = soft, 1 = hard
    uint32_t pad30[4];
    hkQuaternion m_rot;                         // +0x40
    hkWorld* m_world;                           // +0x50
    hkRigidBody* m_body;                        // +0x54
    uint32_t pad58;
    int m_numContacts;                          // +0x5c
    uint32_t pad60;
    hkArray<SPContactPlane> m_contactPlanes;    // +0x64
    uint32_t pad70[4];
    SPDynamicsParticle m_particle;              // +0x80
    float m_lastDeltaTime;                      // +0x140

    void FUN_00aef410();                                                             // 0x00AEF410
    void StepDeltaTime(float dt);
};

}  // namespace SP

#pragma pack(pop)

using namespace SP;

void SPCreatureProxy::StepDeltaTime(float dt)
{
    if (!m_particle.m_enabled || m_body->m_world == 0)
        return;

    m_hasContacts = m_numContacts > 0;
    if (m_hasContacts && m_keyFrameMode != 1) {
        const hkTransform& t = m_body->m_motion->m_transform;
        hkVector4 diff;
        diff.x = m_particle.m_pos.x - t.m_translation.x;
        diff.y = m_particle.m_pos.y - t.m_translation.y;
        diff.z = m_particle.m_pos.z - t.m_translation.z;
        diff.w = m_particle.m_pos.w - t.m_translation.w;

        hkVector4 localForward;
        localForward.set(g_kProxyForwardAxis.x, g_kProxyForwardAxis.y, g_kProxyForwardAxis.z, 0.0f);
        hkVector4 forward;
        forward.setRotatedDir(m_body->m_motion->m_transform.m_rotation, localForward);

        const hkReal distSq = diff.z * diff.z + diff.y * diff.y + diff.x * diff.x;
        if (distSq > g_kProxyMaxDriftSq || forward.dot3(m_particle.GetSupportNormal()) < 0.0f) {
            const hkTransform& bt = m_body->m_motion->m_transform;
            diff.mul4(hkSqrtInverse(distSq));
            m_particle.m_pos.x = diff.x * 0.1f + bt.m_translation.x;
            m_particle.m_pos.y = diff.y * 0.1f + bt.m_translation.y;
            m_particle.m_pos.z = diff.z * 0.1f + bt.m_translation.z;
            m_particle.m_pos.w = diff.w * 0.1f + bt.m_translation.w;
            ResolvePenetration(&m_body->m_motion->m_centerOfMass1, &m_particle.m_pos, m_world, &m_particle.m_pos);
            m_particle.SnapToGround();
        }
    }

    if (m_useContactConstraints) {
        int numConstraints = m_contactPlanes.getSize();
        bool addSupportPlane;
        if (m_particle.m_supportState != 0 && m_particle.m_supportBody == 0) {
            addSupportPlane = true;
            numConstraints++;
        } else {
            addSupportPlane = false;
        }

        hkLocalArray<hkSurfaceConstraintInfo> constraints(numConstraints);
        constraints.setSizeUnchecked(numConstraints);

        const hkReal dynamicFriction = g_kContactDynamicFriction;
        const hkReal staticFriction = g_kContactStaticFriction;
        const int numPlanes = m_contactPlanes.getSize();
        int i;
        for (i = 0; i < numPlanes; i++) {
            hkSurfaceConstraintInfo& info = constraints[i];
            info.m_dynamicFriction = dynamicFriction;
            info.m_extraDownStaticFriction = 0.0f;
            info.m_extraUpStaticFriction = 0.0f;
            info.m_plane = m_contactPlanes[i].m_normal;
            info.m_plane(3) = 0.0f;
            info.m_priority = 0;
            info.m_staticFriction = staticFriction;
            info.m_velocity.setZero4();
        }
        if (addSupportPlane) {
            hkSurfaceConstraintInfo& info = constraints[i];
            info.m_dynamicFriction = 0.0f;
            info.m_extraDownStaticFriction = 0.0f;
            info.m_extraUpStaticFriction = 0.0f;
            info.m_plane = m_particle.m_supportNormal;
            info.m_plane(3) = 0.0f;
            info.m_priority = 1;
            info.m_staticFriction = staticFriction;
            info.m_velocity.setZero4();
        }

        hkLocalArray<hkSurfaceConstraintInteraction> interactions(constraints.getSize());
        interactions.setSizeUnchecked(constraints.getSize());

        SPSurfaceConstraints sc;
        sc.m_constraints = &constraints;
        sc.m_interactions = &interactions;
        m_particle.StepDeltaTime(dt, &sc);
    } else {
        m_particle.StepDeltaTime(dt, 0);
    }

    FUN_00aef410();

    hkRotation rot;
    if (m_alignToSurface) {
        hkVector4 up;
        up.setInterpolate4(m_particle.GetSupportNormal(), GetUpVector(m_particle.m_pos), m_positionBlendAlpha);
        up.normalize3();

        hkVector4 yAxis;
        yAxis.set(0.0f, 1.0f, 0.0f, 0.0f);
        hkVector4 forward;
        forward.setRotatedDir(m_rot, yAxis);

        hkVector4 side;
        side.setCross(forward, up);
        side.normalize3();
        hkVector4 front;
        front.setCross(up, side);
        rot.setCols(side, front, up);
    } else {
        rot.set(m_rot);
    }

    switch (m_keyFrameMode) {
    case 0: {
        hkKeyFrameUtility::KeyFrameInfo kfi;
        kfi.m_position = m_particle.m_pos;
        kfi.m_orientation.set(rot);
        kfi.m_linearVelocity = m_particle.m_vel;
        kfi.m_angularVelocity = g_hkZeroVector;

        hkKeyFrameUtility::AccelerationInfo ai;
        ai.m_linearPositionFactor.setAll(g_kSoftKeyFramePositionFactor);
        ai.m_linearVelocityFactor.setAll(g_kSoftKeyFramePositionFactor);
        ai.m_angularPositionFactor.setAll(g_kSoftKeyFrameRotationFactor);
        ai.m_angularVelocityFactor.setAll(g_kSoftKeyFrameRotationFactor);
        hkKeyFrameUtility::applySoftKeyFrame(kfi, ai, dt, 1.0f / dt, m_body);
        break;
    }
    case 1: {
        hkQuaternion q;
        q.set(rot);
        hkKeyFrameUtility::applyHardKeyFrame(m_particle.m_pos, q, 1.0f / dt, m_body);
        break;
    }
    }
    m_lastDeltaTime = dt;
}
