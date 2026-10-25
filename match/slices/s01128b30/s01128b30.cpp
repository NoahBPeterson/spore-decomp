// Slice s01128b30 -- Havok 3.1 hkReorientAction, hkMotorAction and the hkGroupCollisionFilter
// family. Module flags: /O2 /MD /Gy /TP (x87 float math, no /EHsc).
#include "types.h"
#include "../s0107e670/hk31_base.h"
#include <new>
#include <math.h>

// ---- CRT entry points used by the original x87 code paths.
extern "C" float __cdecl sqrtf(float x);          // the binary inlines fsqrt; source uses the CRT helper

// cl15 has no fsqrt intrinsic (sqrtf emits a __CIsqrt call the original does not import), so the
// same x87 primitive is used here: a single fsqrt, exactly as the retail code does.
static inline float hkSqrtX87(float x)
{
    float r;
    __asm {
        fld  dword ptr [x]
        fsqrt
        fstp dword ptr [r]
    }
    return r;
}

// TlsGetValue / hkThreadMemory / hkMemory / hkBool / hkReferencedObject / hkVector4 / hkQuaternion /
// hkRotation / hkTransform all come from hk31_base.h; the object layouts below follow the 32-bit
// binary (pointer members make 64-bit offsets differ).

// hkThreadMemory::s_threadMemoryTls (0x016e4174): the TLS slot holding the current thread's block.

// hkQuaternion is only forward-declared by hk31_base.h; the motion state needs it complete.
class hkQuaternion { public: float x, y, z, w; };

class hkMotion;

// hkEntity: entity listeners live in an hkArray at +0xb4, body motion state pointer at +0x58.
class hkEntity {
public:
    void activate();                                 // 0x01088ae0
    void removeEntityListener(void* listener);       // 0x01088a20 (this = the entity)
    char pad00[0x58];
    hkMotion* m_motion;                              // +0x58
    char     pad5c[0x5c];
    void**   m_listenerData;                         // +0xb4
    int      m_listenerSize;                         // +0xb8
};

class hkMotion {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void vgetTransform(void* out);            // +0x2c: fills an hkTransform
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual void vapplyAngularImpulseScaled(float dt, const void* dir);   // +0x74
    char pad04[0x0c];
    hkTransform m_transform;                         // +0x10
    char pad50[0x30];
    hkQuaternion m_rotation;                         // +0x80
    char pad90[0x50];
    hkVector4 m_linearVelocity;                      // +0xd0
    hkVector4 m_angularVelocity;                     // +0xe0
};

// hkpRigidBody shares hkEntity's leading layout (motion pointer at +0x58) and its activate().
class hkpRigidBody { public: char pad00[0x58]; hkMotion* m_motion; };

// hkVector4 rotation helpers (0x01081440 / 0x010814a0).
inline void hkVector4SetRotatedInverseDir(hkVector4& out, const hkRotation& r, const hkVector4& dir)
{
    out.x = dir.x * r.m[0] + dir.y * r.m[4] + dir.z * r.m[8];
    out.y = dir.x * r.m[1] + dir.y * r.m[5] + dir.z * r.m[9];
    out.z = dir.x * r.m[2] + dir.y * r.m[6] + dir.z * r.m[10];
    out.w = dir.x * r.m[3] + dir.y * r.m[7] + dir.z * r.m[11];
}

inline void hkVector4SetRotatedDir(hkVector4& out, const hkRotation& r, const hkVector4& dir)
{
    out.x = dir.x * r.m[0] + dir.y * r.m[1] + dir.z * r.m[2] + dir.w * r.m[3];
    out.y = dir.x * r.m[4] + dir.y * r.m[5] + dir.z * r.m[6] + dir.w * r.m[7];
    out.z = dir.x * r.m[8] + dir.y * r.m[9] + dir.z * r.m[10] + dir.w * r.m[11];
    out.w = 0.0f;
}

// ---------------------------------------------------------------- collision filter family
class hkCollidable { public: char pad00[0x40]; };

struct hkPair { uint32_t first; uint32_t second; };

// The four filter interfaces; hkCollisionFilter derives from hkReferencedObject and all four
// (non-virtually), so their vtable pointers land at +0/+8/+0xc/+0x10/+0x14 (as in s01129d50).
class hkCollidableCollidableFilter { public:
    virtual void v00();
    virtual hkBool isCollisionEnabled(const hkCollidable& a, const hkCollidable& b) const;
};
class hkShapeCollectionFilter { public:
    virtual hkBool isCollisionEnabled(const void* input, const void* a, const void* b,
                                      const void* collection, uint32_t key) const;
    virtual void v01();
};
class hkRayShapeCollectionFilter { public:
    virtual hkBool isCollisionEnabled(const void* input, const void* collection, uint32_t key) const;
    virtual void v01();
};
class hkRayCollidableFilter { public:
    virtual void v00();
    virtual hkBool isCollisionEnabled(const void* input, const hkCollidable& c) const;
};

// hkCollisionFilter: hkReferencedObject + the four interfaces (vtables at +0/+8/+0xc/+0x10/+0x14).
class hkCollisionFilter : public hkReferencedObject, public hkCollidableCollidableFilter,
                          public hkShapeCollectionFilter, public hkRayShapeCollectionFilter,
                          public hkRayCollidableFilter
{
public:
    virtual ~hkCollisionFilter() {}     // 0x005efd40 restores the base vtables
protected:
    hkCollisionFilter() {}
};

// hkEntityListener: vptr only; the derived filter places it at +0x18.
class hkEntityListener {
public:
    virtual void el00();                                        // 0 (dtor slot)
    virtual void entityAddedCallback(hkEntity* e);              // 1
    virtual void entityRemovedCallback(hkEntity* e);            // 2
    virtual void entityShapeSetCallback(hkEntity* e);           // 3
};

// hkGroupCollisionFilter: hkCollisionFilter (vtables at +0/+8/+0xc/+0x10/+0x14) plus an
// hkEntityListener subobject whose vptr sits at +0x18; its low byte doubles as the ctor's default
// answer byte (m_default). The 256-bit group-mask table / entity-pair array follows at +0x1c.
class hkGroupCollisionFilter : public hkCollisionFilter, public hkEntityListener
{
public:
    virtual ~hkGroupCollisionFilter();                 // 0x01129500
    virtual hkBool isCollisionEnabled(const hkCollidable& a, const hkCollidable& b) const;
    virtual hkBool isCollisionEnabled(const void* input, const void* a, const void* b,
                                      const void* collection, uint32_t key) const;   // 0x01129af0
    virtual hkBool isCollisionEnabled(const void* input, const void* b,
                                      const void* collection, uint32_t key) const;   // 0x01129b40
    virtual hkBool isCollisionEnabled(const void* input, const hkCollidable& c) const;
    virtual void entityAddedCallback(hkEntity* e);
    virtual void entityRemovedCallback(hkEntity* e);   // 0x011293c0
    virtual void entityShapeSetCallback(hkEntity* e);

    // +0x1c: the group-mask table / entity-pair array (data, then size, then capacityAndFlags).
    hkPair*  m_pairs;                                  // +0x1c
    int      m_pairSize;                               // +0x20
    int      m_pairCapacityAndFlags;                   // +0x24

    // The default answer byte aliases the hkEntityListener vptr's first byte at +0x18.
    hkBool& m_default() const { return *(hkBool*)((char*)this + 0x18); }

    // The private 256-bit collision-mask core (sret hkBool* is the first stack argument).
    void isCollisionEnabled_core(hkBool* result, uint32_t groupA, uint32_t groupB) const;
};

// The 256-bit group-mask table is the group filter's +0x1c array; the default answer byte is the
// low byte at +0x18 (the hkEntityListener vptr).

// ---------------------------------------------------------------- 01128b30
// hkReorientAction::applyAction -- corrective angular impulse from the body's world rotation.
struct hkReorientAction {
    char pad00[0x18];
    hkpRigidBody* m_entity;    // +0x18
    hkVector4 m_rotationAxis;  // +0x20
    hkVector4 m_upAxis;        // +0x30
    float     m_strength;      // +0x40
    float     m_damping;       // +0x44
    void applyAction(const void* stepInfo);
    hkReorientAction* clone(const void* newEntities, const void* newPhantoms) const;
};

static inline float absf(float v) { return v < 0.0f ? -v : v; }

// @ 0x01128b30
void hkReorientAction::applyAction(const void* stepInfo)
{
    const float* step = (const float*)stepInfo;
    hkpRigidBody* body = m_entity;
    hkMotion* motion = body->m_motion;

    // The body's world rotation as a quaternion (m_transform rows folded into a quaternion).
    float qx = motion->m_rotation.x;
    float qy = motion->m_rotation.y;
    float qz = motion->m_rotation.z;
    float qw = motion->m_rotation.w;
    float qw2 = qw * qw;

    float ux = m_upAxis.x, uy = m_upAxis.y, uz = m_upAxis.z;

    // setRotatedInverseDir(upAxis) -- columns 0..2, doubled (the 0.5 quaternion scale is folded in).
    float c0, c1, c2;
    {
        float su = qz * uz + (qy * uy + qx * ux);
        float col0 = (qy * uz - qz * uy) * qw + (su * qx + (qw2 - 0.5f) * ux);
        float col1 = (qz * ux - qx * uz) * qw + (su * qy + (qw2 - 0.5f) * uy);
        float col2 = (qx * uy - qy * ux) * qw + (su * qz + (qw2 - 0.5f) * uz);
        c0 = col0 + col0;
        c1 = col1 + col1;
        c2 = col2 + col2;
    }

    // setRotatedDir(rotationAxis) -- full 4-lane transform of the axis by q.
    float ax = m_rotationAxis.x, ay = m_rotationAxis.y, az = m_rotationAxis.z, aw = m_rotationAxis.w;
    float a = qz * az + (qy * ay + qx * ax);
    float a0 = (qy * az - qz * ay) * qw + (a * qx + (qw2 - 0.5f) * ax);
    float a1 = (qz * ax - qx * az) * qw + (a * qy + (qw2 - 0.5f) * ay);
    float a2 = (qx * ay - qy * ax) * qw + (a * qz + (qw2 - 0.5f) * az);
    float a3 = qw * 0.0f + (a * qw + (qw2 - 0.5f) * aw);
    float d0 = a0 + a0, d1 = a1 + a1, d2 = a2 + a2, d3 = a3 + a3;

    // Rotate the up axis towards the desired axis and normalise.
    float sdot = -(c1 * d1 + (c2 * d2 + c0 * d0));
    float n0 = sdot * d0 + c0;
    float n1 = sdot * d1 + c1;
    float n2 = sdot * d2 + c2;
    float len2 = n1 * n1 + (n2 * n2 + n0 * n0);
    float inv = (len2 == 0.0f) ? 0.0f : 1.0f / hkSqrtX87(len2);
    n0 *= inv; n1 *= inv; n2 *= inv;

    // Signed angle between the rotated up axis and the rotation axis.
    float ca = n0 * d0 + (n2 * d2 + n1 * d1);
    float angle;
    if (absf(ca) < 1.0f)
        angle = (float)acos((double)ca);   // CRT __CIacos (argument/result on the x87 stack)
    else if (ca <= 0.0f)
        angle = 3.1415927f;
    else
        angle = 0.0f;

    // Cross products used to pick the dominant axis and its sign.
    float e0 = n2 * d1 - n1 * d2;
    float e1 = n0 * d2 - n2 * d0;
    float e2 = n1 * d0 - n0 * d1;

    float ae0 = absf(e0), ae1 = absf(e1), ae2 = absf(e2);
    int i0;
    if (ae1 <= ae0)      i0 = (ae2 <= ae0) ? 0 : 2;
    else                 i0 = (ae2 <= ae1) ? 1 : 2;

    float ad0 = absf(d0), ad1 = absf(d1), ad2 = absf(d2);
    int i1;
    if (ad1 <= ad0)      i1 = (ad2 <= ad0) ? 0 : 2;
    else                 i1 = (ad2 <= ad1) ? 1 : 2;

    float sk0 = (i0 == 0) ? e0 : (i0 == 1) ? e1 : e2;
    float sk1 = (i1 == 0) ? d0 : (i1 == 1) ? d1 : d2;
    if ((sk0 < 0.0f) != (sk1 < 0.0f))
        angle = -angle;

    // Angular impulse: strength * dt * angle along the axis, minus the current angular velocity * damping.
    float k = m_damping * step[3];
    hkVector4 impulse;
    float sc = m_strength * step[3] * angle;
    impulse.x = d0 * sc - k * motion->m_angularVelocity.x;
    impulse.y = d1 * sc - k * motion->m_angularVelocity.y;
    impulse.z = d2 * sc - k * motion->m_angularVelocity.z;
    impulse.w = d3 * sc - k * motion->m_angularVelocity.w;

    ((hkEntity*)(void*)body)->activate();
    // The original applies the angular impulse through the hkMotion angular-impulse slot (+0x68).
    ((void(__thiscall*)(hkMotion*, const hkVector4&))*(void**)((char*)*(void**)motion + 0x68))(motion, impulse);
}

struct hkReorientActionCtor {
    hkReorientActionCtor(hkpRigidBody* body, const hkVector4& rot, const hkVector4& up,
                         float strength, float damping);
};

// ---------------------------------------------------------------- 011290b0
// @ 0x011290b0
hkReorientAction* hkReorientAction::clone(const void* newEntities, const void* newPhantoms) const
{
    const int* entities = (const int*)newEntities;
    const int* phantoms = (const int*)newPhantoms;
    if (entities[1] == 1 && phantoms[1] == 0) {
        hkReorientAction* r = (hkReorientAction*)hkMemory::s_instance->allocateChunk(0x50, 0x26);
        *(unsigned short*)((char*)r + 4) = 0x50;
        hkpRigidBody* body = *(hkpRigidBody**)entities[0];
        new (r) hkReorientActionCtor(body, *(const hkVector4*)((const char*)this + 0x20),
                                     *(const hkVector4*)((const char*)this + 0x30),
                                     *(const float*)((const char*)this + 0x40),
                                     *(const float*)((const char*)this + 0x44));
        *(int*)((char*)r + 0x10) = *(const int*)((const char*)this + 0x10);
        return r;
    }
    return 0;
}

// ---------------------------------------------------------------- 01129130
struct hkPoweredChainMapper : hkReferencedObject {
    char pad08[0x28 - 0x8];
    virtual ~hkPoweredChainMapper();
};

// @ 0x01129130
hkPoweredChainMapper::~hkPoweredChainMapper()
{
    char* s = (char*)this;
    int   n1 = *(int*)(s + 0xc);
    void* a1 = *(void**)(s + 8);
    for (int i = 0; i < n1; ++i) {
        void* p = *(void**)((char*)a1 + i * 0xc + 8);
        if (p) {
            hkReferencedObject* o = (hkReferencedObject*)p;
            if (o->m_memSizeAndFlags != 0 && --o->m_referenceCount == 0) {
                (*(void(__thiscall**)(hkReferencedObject*, int))*(void**)o)(o, 1);
            }
        }
    }
    int   n3 = *(int*)(s + 0x24);
    void** a3 = *(void***)(s + 0x20);
    for (int i = 0; i < n3; ++i) {
        hkReferencedObject* o = (hkReferencedObject*)a3[i];
        if (o->m_memSizeAndFlags != 0 && --o->m_referenceCount == 0) {
            (*(void(__thiscall**)(hkReferencedObject*, int))*(void**)o)(o, 1);
        }
    }
    int cap3 = *(int*)(s + 0x28);
    if (cap3 >= 0) {
        hkThreadMemory::getInstance().deallocateChunk(a3, (cap3 & 0x3fffffff) * 4, 0x14);
    }
    int cap2 = *(int*)(s + 0x1c);
    if (cap2 >= 0) {
        hkThreadMemory::getInstance().deallocateChunk(*(void**)(s + 0x14), cap2 << 3, 0x14);
    }
    int cap1 = *(int*)(s + 0x10);
    if (cap1 >= 0) {
        hkThreadMemory::getInstance().deallocateChunk(a1, (cap1 & 0x3fffffff) * 0xc, 0x14);
    }
}

// ---------------------------------------------------------------- 01129290
class hkPhysicsData : public hkReferencedObject { public:
    hkReferencedObject* m_obj;  // +0x8
    hkReferencedObject** m_arr; // +0xc
    int m_n;                    // +0x10
    int m_cap;                  // +0x14
    virtual ~hkPhysicsData();
};

// @ 0x01129290
hkPhysicsData::~hkPhysicsData()
{
    if (m_obj && m_obj->m_memSizeAndFlags != 0 && --m_obj->m_referenceCount == 0) {
        (*(void(__thiscall**)(hkReferencedObject*, int))*(void**)m_obj)(m_obj, 1);
    }
    for (int i = 0; i < m_n; ++i) {
        hkReferencedObject* o = m_arr[i];
        if (o->m_memSizeAndFlags != 0 && --o->m_referenceCount == 0) {
            (*(void(__thiscall**)(hkReferencedObject*, int))*(void**)o)(o, 1);
        }
    }
    if (m_cap >= 0) {
        hkThreadMemory::getInstance().deallocateChunk(m_arr, (m_cap & 0x3fffffff) * 4, 0x14);
    }
}

// ---------------------------------------------------------------- 01129360
// hkPairwiseCollisionFilter: handle id at +0x10, pair array at +0x14/+0x18.
struct hkPairwiseCollisionFilter {
    char    pad00[0x10];
    int     m_handleId;  // +0x10
    hkPair* m_pairs;     // +0x14
    int     m_n;         // +0x18
    hkBool isCollisionEnabled(const hkCollidable& a, const hkCollidable& b) const;
};

// @ 0x01129360
hkBool hkPairwiseCollisionFilter::isCollisionEnabled(const hkCollidable& a, const hkCollidable& b) const
{
    uint32_t pa = (uint32_t)((const char*)&a + *(const int*)((const char*)&a + 0x10));
    uint32_t pb = (uint32_t)((const char*)&b + *(const int*)((const char*)&b + 0x10));
    uint32_t vmax, vmin;
    if (pb < pa) { vmax = pa; vmin = pb; } else { vmax = pb; vmin = pa; }
    int idx = -1;
    for (int i = 0; i < m_n; ++i) {
        if (m_pairs[i].first == vmax && m_pairs[i].second == vmin) { idx = i; break; }
    }
    return hkBool(idx < 0);
}

// ---------------------------------------------------------------- 011293c0
struct hkPairwiseCollisionFilterListener {
    char    pad00[0x4];
    hkPair* m_pairs;  // +0x4 (filter pairs, base - 0x18)
    int     m_n;      // +0x8
    void entityRemovedCallback(hkEntity* e);
};

extern void hkEntity_removeEntityListener(hkEntity* e, void* listener);  // 0x01088a20

// @ 0x011293c0
void hkPairwiseCollisionFilterListener::entityRemovedCallback(hkEntity* e)
{
    int n = m_n;
    for (int i = 0; i < n; ) {
        if (m_pairs[i].first == (uint32_t)e || m_pairs[i].second == (uint32_t)e) {
            --n;
            m_pairs[i].first = m_pairs[n].first;
            m_pairs[i].second = m_pairs[n].second;
        } else {
            ++i;
        }
    }
    m_n = n;
    hkEntity_removeEntityListener(e, (void*)((char*)this - 0x18));
}

// ---------------------------------------------------------------- 01129420 / 011294e0 / 01129500
// The six vtable pointers the ctor installs (base subobject vtables first, then the derived ones).
extern void* Vtbl_013ef82c[];   // 0x013ef82c  hkRayCollidableFilter
extern void* Vtbl_013ef824[];   // 0x013ef824  hkRayShapeCollectionFilter
extern void* Vtbl_0145c414[];   // 0x0145c414  hkEntityListener
extern void* Vtbl_013ef094[];   // 0x013ef094  hkReferencedObject
extern void* Vtbl_014a6f8c[];   // 0x014a6f8c  hkGroupCollisionFilter +0
extern void* Vtbl_014a6f84[];   // 0x014a6f84  hkGroupCollisionFilter +8
extern void* Vtbl_014a6f7c[];   // 0x014a6f7c  hkGroupCollisionFilter +0xc
extern void* Vtbl_014a6f74[];   // 0x014a6f74  hkGroupCollisionFilter +0x10
extern void* Vtbl_014a6f6c[];   // 0x014a6f6c  hkGroupCollisionFilter +0x14
extern void* Vtbl_014a6f58[];   // 0x014a6f58  hkGroupCollisionFilter +0x18

// The ctor takes its object pointer in ecx and the (unused) flag on the stack.
// @ 0x01129420
hkGroupCollisionFilter* __fastcall hkGroupCollisionFilter_ctor(hkGroupCollisionFilter* self, int, unsigned int /*flag*/)
{
    ((hkReferencedObject*)(void*)self)->m_referenceCount = 1;   // +6 (memSize filled by the allocator)
    // Base/interface vtables, then the derived ones overwrite them (the object is also its own
    // hkEntityListener, so +0x18 receives the listener vtable). The stores are volatile so the
    // later overwrite does not let the compiler drop the base ones (the original emits all 12).
    *(void* volatile*)((char*)self + 0x08) = Vtbl_013ef82c;
    *(void* volatile*)((char*)self + 0x0c) = Vtbl_013ef824;
    *(void* volatile*)((char*)self + 0x10) = Vtbl_013ef824;
    *(void* volatile*)((char*)self + 0x14) = Vtbl_013ef82c;
    *(void* volatile*)((char*)self + 0x18) = Vtbl_0145c414;
    *(void* volatile*)((char*)self + 0x00) = Vtbl_014a6f8c;
    *(void* volatile*)((char*)self + 0x08) = Vtbl_014a6f84;
    *(void* volatile*)((char*)self + 0x0c) = Vtbl_014a6f7c;
    *(void* volatile*)((char*)self + 0x10) = Vtbl_014a6f74;
    *(void* volatile*)((char*)self + 0x14) = Vtbl_014a6f6c;
    *(void* volatile*)((char*)self + 0x18) = Vtbl_014a6f58;
    self->m_pairs = 0;                                 // +0x1c
    self->m_pairSize = 0;                              // +0x20
    self->m_pairCapacityAndFlags = (int)0x80000000;    // +0x24 (empty array, locked)
    return self;
}

// @ 0x011294e0
hkGroupCollisionFilter* hkGroupCollisionFilter_create(unsigned int a)
{
    if (a != 0)
        return hkGroupCollisionFilter_ctor((hkGroupCollisionFilter*)a, 0, 1);
    return (hkGroupCollisionFilter*)1;
}

// @ 0x01129500
hkGroupCollisionFilter::~hkGroupCollisionFilter()
{
    // The most-derived vtable is (re)installed first by the compiler-generated prologue.
    *(void**)((char*)this + 0x00) = Vtbl_014a6f8c;
    *(void**)((char*)this + 0x08) = Vtbl_014a6f84;
    *(void**)((char*)this + 0x0c) = Vtbl_014a6f7c;
    *(void**)((char*)this + 0x10) = Vtbl_014a6f74;
    *(void**)((char*)this + 0x14) = Vtbl_014a6f6c;
    *(void**)((char*)this + 0x18) = Vtbl_014a6f58;

    // Deregister this object's listener subobject from every tracked entity (both pair sides).
    for (int i = 0; i < m_pairSize; ++i) {
        for (int side = 0; side < 2; ++side) {
            hkEntity* e = (hkEntity*)(side == 0 ? m_pairs[i].first : m_pairs[i].second);
            if (e == 0)
                continue;
            void* listener = (void*)((char*)this + 0x18);
            int n = e->m_listenerSize, j = 0;
            for (; j < n; ++j) {
                if (e->m_listenerData[j] == listener)
                    break;
            }
            if (j < n)
                e->removeEntityListener(listener);
        }
    }

    if (m_pairCapacityAndFlags >= 0) {
        hkThreadMemory::getInstance().deallocateChunk(m_pairs, (m_pairCapacityAndFlags & 0x3fffffff) << 3, 0x14);
    }

    // Base destructors restore the base subobject vtables.
    *(void**)((char*)this + 0x00) = Vtbl_013ef094;
    *(void**)((char*)this + 0x08) = Vtbl_013ef82c;
    *(void**)((char*)this + 0x0c) = Vtbl_013ef824;
    *(void**)((char*)this + 0x10) = Vtbl_013ef824;
    *(void**)((char*)this + 0x14) = Vtbl_013ef82c;
    *(void**)((char*)this + 0x18) = Vtbl_0145c414;
}

// ---------------------------------------------------------------- 01129640 / 01129720 / 011297f0
struct hkMotorAction {
    char pad00[0x10];
    uint32_t m_userData;         // +0x10
    uint32_t m_pad14;            // +0x14
    hkpRigidBody* m_entity;      // +0x18
    char pad1c[4];
    hkVector4 m_axis;            // +0x20
    float     m_maxVelocity;     // +0x30
    float     m_strength;        // +0x34
    char      m_enabled;         // +0x38
    hkMotorAction(hkpRigidBody* body, const hkVector4& axis, float maxVelocity, float strength);
    void applyAction(const void* stepInfo);
    hkMotorAction* clone(const void* newEntities, const void* newPhantoms) const;
};
hkMotorAction* hkMotorAction_ctor(hkMotorAction* self, hkpRigidBody* body, const hkVector4& axis,
                                  float maxVelocity, float strength);

extern void hkUnaryAction_ctor(void* self, hkEntity* body, unsigned int ud);  // 0x0120b890

// @ 0x01129640
hkMotorAction::hkMotorAction(hkpRigidBody* body, const hkVector4& axis,
                             float maxVelocity, float strength)
{
    hkUnaryAction_ctor(this, (hkEntity*)(void*)body, 0);
    m_axis = axis;
    m_maxVelocity = maxVelocity;
    m_strength = strength;
    m_enabled = 1;

    float lenSq = m_axis.x * m_axis.x + m_axis.y * m_axis.y + m_axis.z * m_axis.z + m_axis.w * m_axis.w;
    float s = (lenSq == 0.0f) ? 0.0f : 1.0f / hkSqrtX87(lenSq);
    m_axis.x = s * m_axis.x;
    m_axis.y = s * m_axis.y;
    m_axis.z = s * m_axis.z;
    m_axis.w = s * m_axis.w;
}

// @ 0x01129720
void hkMotorAction::applyAction(const void* stepInfo)
{
    if (m_enabled == 0)
        return;

    hkpRigidBody* body = (hkpRigidBody*)(void*)m_entity;
    hkMotion* motion = body->m_motion;
    const hkRotation& rot = *(const hkRotation*)&motion->m_transform;
    const float* step = (const float*)stepInfo;

    // Direction of the motor axis expressed in the body frame.
    hkVector4 localDir;
    hkVector4SetRotatedInverseDir(localDir, rot, m_axis);

    // impulse = (maxVelocity - <localDir, axis>) * strength * axis
    hkVector4 impulse;
    float mag = (m_maxVelocity - (localDir.x * m_axis.x + localDir.y * m_axis.y +
                                  localDir.z * m_axis.z + localDir.w * m_axis.w)) * m_strength;
    impulse.x = mag * m_axis.x;
    impulse.y = mag * m_axis.y;
    impulse.z = mag * m_axis.z;
    impulse.w = mag * m_axis.w;

    hkTransform transform;
    motion->vgetTransform(&transform);

    hkVector4 worldImpulse;
    hkVector4SetRotatedDir(worldImpulse, rot, impulse);

    // Rotate the world impulse back into the body frame and store it over the transform.
    hkVector4 bodyImpulse;
    hkVector4SetRotatedDir(bodyImpulse, rot, worldImpulse);

    float dt = step[2];

    ((hkEntity*)(void*)body)->activate();
    ((void(__thiscall*)(hkMotion*, float, const hkVector4&))*(void**)((char*)*(void**)motion + 0x74))
        (motion, dt, bodyImpulse);
}

// @ 0x011297f0
hkMotorAction* hkMotorAction::clone(const void* newEntities, const void* newPhantoms) const
{
    const int* entities = (const int*)newEntities;
    const int* phantoms = (const int*)newPhantoms;
    if (entities[1] != 1 || phantoms[1] != 0)
        return 0;

    hkMotorAction* r = (hkMotorAction*)hkMemory::s_instance->allocateChunk(0x40, 0x26);
    ((hkReferencedObject*)(void*)r)->m_memSizeAndFlags = 0x40;
    hkMotorAction_ctor(r, (hkpRigidBody*)(void*)*(const int*)entities[0],
                       m_axis, m_maxVelocity, m_strength);
    r->m_enabled = m_enabled;
    r->m_userData = m_userData;
    return r;
}

// ---------------------------------------------------------------- 01129850 / 01129af0 / 01129b40
// @ 0x01129850
void hkGroupCollisionFilter::isCollisionEnabled_core(hkBool* result, uint32_t groupA, uint32_t groupB) const
{
    if (groupA == 0 || groupB == 0) {
        *result = m_default();
        return;
    }

    // The 256-bit table is stored at +0x1c. `result` is the hidden hkBool sret pointer.
    const uint32_t* bits = (const uint32_t*)((const char*)this + 0x1c);
    uint32_t acc = 0;
    for (unsigned bit = 0; bit < 0x20; ++bit) {
        if (groupA & (1u << bit))
            acc |= bits[bit];
    }
    *result = hkBool((groupB & acc) != 0);
}

// hkShapeCollectionFilter::isCollisionEnabled: ask the collection for the key (vtable +0x2c), walk
// the collision body to its root, then use the root body's group.
// @ 0x01129af0
hkBool hkGroupCollisionFilter::isCollisionEnabled(const void* input, const void* /*a*/, const void* b,
                                                  const void* collection, uint32_t key) const
{
    uint32_t group = ((uint32_t(__thiscall*)(const void*, uint32_t))(
        *(void**)(*(const int*)collection + 0x2c)))(collection, key);
    const unsigned char* body = (const unsigned char*)b;
    while (*(const int*)(body + 0xc) != 0)
        body = *(const unsigned char* const*)(body + 0xc);
    hkBool result(false);
    ((const hkGroupCollisionFilter*)((const char*)this - 0xc))
        ->isCollisionEnabled_core(&result, *(const uint32_t*)(body + 0x1c), group);
    return result;
}

// hkRayShapeCollectionFilter::isCollisionEnabled: group comes from the collection key, this time
// adjusted from the +0x10 interface subobject.
// @ 0x01129b40
hkBool hkGroupCollisionFilter::isCollisionEnabled(const void* input, const void* b,
                                                  const void* /*collection*/, uint32_t key) const
{
    uint32_t group = ((uint32_t(__thiscall*)(const void*, uint32_t))(
        *(void**)(*(const int*)b + 0x2c)))(b, key);
    const unsigned char* root = (const unsigned char*)input;
    hkBool result(false);
    ((const hkGroupCollisionFilter*)((const char*)this - 0x10))
        ->isCollisionEnabled_core(&result, *(const uint32_t*)(root + 0x20), group);
    return result;
}

// ---------------------------------------------------------------- 01129c70 / 01129cc0 / 01129d20
struct hkDisableEntityCollisionFilter {
    char  pad00[0x14];
    void** m_arr;   // +0x14
    int    m_n;     // +0x18
    void** m_arr2;  // +0x1c
    int    m_n2;    // +0x20
    hkBool isCollisionEnabled(const hkCollidable& a, const hkCollidable& b) const;
    hkBool removeEntity(void* item);
};

// The entity-removed listener is a second base subobject placed at +0x18 of the filter object;
// ecx on entry is that subobject, and the filter base is ecx-0x18.
struct hkEntityListenerSlot {
    virtual void el0(); virtual void el1(); virtual void el2();
    virtual void entityRemovedCallback(hkEntity* e);
};

// @ 0x01129c70
hkBool hkDisableEntityCollisionFilter::isCollisionEnabled(const hkCollidable& a, const hkCollidable& b) const
{
    int n = m_n;
    for (int i = 0; i < n; ++i) {
        int v = (int)((char*)m_arr[i] + 0x1c);
        if (v == (int)(const void*)&a || v == (int)(const void*)&b) {
            return hkBool(false);
        }
    }
    return hkBool(true);
}

// @ 0x01129cc0
hkBool hkDisableEntityCollisionFilter::removeEntity(void* item)
{
    if (item == 0) return hkBool(false);
    for (int i = 0; i < m_n2; ++i) {
        if (m_arr2[i] == item) {
            int last = m_n2 - 1;
            m_n2 = last;
            m_arr2[i] = m_arr2[last];
            return hkBool(true);
        }
    }
    return hkBool(false);
}

// @ 0x01129d20
void hkEntityListenerSlot::entityRemovedCallback(hkEntity* e)
{
    hkDisableEntityCollisionFilter* self =
        (hkDisableEntityCollisionFilter*)(void*)((char*)this - 0x18);
    if (e != 0) {
        self->removeEntity(e);
        e->removeEntityListener((void*)this);
    }
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
