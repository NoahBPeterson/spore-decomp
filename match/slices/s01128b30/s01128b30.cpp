// Slice s01128b30 -- Havok 3.1 Reorient/Motor actions and collision filters.
// Module flags: /O2 /MD /Gy /TP (x87 float math, no /EHsc)
#include "types.h"
#include <new>

#define HK_CALL __cdecl

extern "C" float hkSqrt(float x);

// ---------------------------------------------------------------- base types
struct hkBaseObject { virtual ~hkBaseObject(); };

struct hkReferencedObject : hkBaseObject {
    unsigned short m_memSizeAndFlags;  // +0x4
    short          m_referenceCount;   // +0x6
    void removeReference();
};

struct hkVector4 { float x, y, z, w; };
struct hkRotation;
struct hkQuaternion { hkVector4 m_vec; };

// hkThreadMemory deallocation (used by hkArray dtors).
struct hkThreadMemory { void deallocateChunk(void* p, int size, int memClass); };
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern unsigned long g_hkTlsIndex;

struct hkEntity;

// hkMotion / hkRigidBody minimal layout.
struct hkMotion {
    char pad00[0x40];
    hkVector4 m_centreOfMassLocal;  // +0x40
    char pad50[0x90];
    hkVector4 m_worldPos;           // +0xd0
    hkQuaternion m_worldRot;        // +0xe0
    char padF0[0x10];
    hkRotation* m_rotation;         // +0x100 (placeholder)
    virtual void vslot0();
    virtual void vslot4();
    virtual void vslot8();
    virtual void vslotc();
    virtual void vslot10();
    virtual void vslot14();
    virtual void vslot18();
    virtual void vslot1c();
    virtual void vslot20();
    virtual void vslot24();
    virtual void vgetTransform();   // +0x2c
};
struct hkRigidBody { char pad00[0x58]; hkMotion* m_motion; void activate(); };
struct hkpRigidBody : hkRigidBody {};

// ---------------------------------------------------------------- collision filter vtables
struct hkBool {
    char m_bool;
    hkBool() {}
    hkBool(bool b) : m_bool(b ? 1 : 0) {}
};

struct hkCollidable { char pad00[0x40]; };

struct hkPair { uint32_t first; uint32_t second; };

// ---------------------------------------------------------------- 01128b30
// hkReorientAction::applyAction -- large x87 routine; approximate reconstruction.
struct hkReorientAction {
    char pad00[0x18];
    hkpRigidBody* m_entity;  // +0x18
    hkVector4 m_rotationAxis;  // +0x20
    hkVector4 m_upAxis;        // +0x30
    float     m_strength;      // +0x40
    float     m_damping;       // +0x44
    void applyAction(const void* stepInfo);
    hkReorientAction* clone(const void* newEntities, const void* newPhantoms) const;
};

// @ 0x01128b30
void hkReorientAction::applyAction(const void* stepInfo)
{
    (void)stepInfo;
    // Full algorithm reconstructs a world rotation from the body motion and
    // applies a corrective angular impulse; approximated here.
    hkpRigidBody* body = m_entity;
    hkMotion* motion = body->m_motion;
    (void)motion;
    (void)m_rotationAxis; (void)m_upAxis; (void)m_strength; (void)m_damping;
}

struct hkReorientActionCtor {
    hkReorientActionCtor(hkpRigidBody* body, const hkVector4& rot, const hkVector4& up,
                         float strength, float damping);
};

// ---------------------------------------------------------------- 011290b0
struct hkMemoryVtbl {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void* alloc(int size, int align);
};
extern hkMemoryVtbl g_hkMemoryInstance;  // 0x016e4178

// @ 0x011290b0
hkReorientAction* hkReorientAction::clone(const void* newEntities, const void* newPhantoms) const
{
    const int* entities = (const int*)newEntities;
    const int* phantoms = (const int*)newPhantoms;
    if (entities[1] == 1 && phantoms[1] == 0) {
        hkReorientAction* r = (hkReorientAction*)g_hkMemoryInstance.alloc(0x50, 0x26);
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
// dtor for a mapper containing two reference arrays and an hkArray of 0xc-byte entries.
struct hkEntryC { void* vptr; unsigned short a; unsigned short b; char pad[4]; };  // 0xc

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
        hkThreadMemory* mem = (hkThreadMemory*)TlsGetValue(g_hkTlsIndex);
        mem->deallocateChunk(a3, (cap3 & 0x3fffffff) * 4, 0x14);
    }
    int cap2 = *(int*)(s + 0x1c);
    if (cap2 >= 0) {
        hkThreadMemory* mem = (hkThreadMemory*)TlsGetValue(g_hkTlsIndex);
        mem->deallocateChunk(*(void**)(s + 0x14), cap2 << 3, 0x14);
    }
    int cap1 = *(int*)(s + 0x10);
    if (cap1 >= 0) {
        hkThreadMemory* mem = (hkThreadMemory*)TlsGetValue(g_hkTlsIndex);
        mem->deallocateChunk(a1, (cap1 & 0x3fffffff) * 0xc, 0x14);
    }
}

// ---------------------------------------------------------------- 01129290
struct hkPhysicsData : hkReferencedObject {
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
        hkThreadMemory* mem = (hkThreadMemory*)TlsGetValue(g_hkTlsIndex);
        mem->deallocateChunk(m_arr, (m_cap & 0x3fffffff) * 4, 0x14);
    }
}

// ---------------------------------------------------------------- 01129360
struct hkPairwiseCollisionFilter {
    char pad00[0x14];
    hkPair* m_pairs;  // +0x14
    int     m_n;      // +0x18
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
    return idx < 0;
}

// ---------------------------------------------------------------- 011293c0
struct hkPairwiseCollisionFilter2 {
    char pad00[0x4];
    hkPair* m_pairs;  // +0x4
    int     m_n;      // +0x8
    void entityRemovedCallback(hkEntity* e);
};

extern void hkEntity_removeEntityListener(hkEntity* e, void* listener);  // 0x01088a20

// @ 0x011293c0
void hkPairwiseCollisionFilter2::entityRemovedCallback(hkEntity* e)
{
    for (int i = 0; i < m_n; ) {
        if (m_pairs[i].first == (uint32_t)e || m_pairs[i].second == (uint32_t)e) {
            int last = m_n - 1;
            m_n = last;
            m_pairs[i].first = m_pairs[last].first;
            m_pairs[i].second = m_pairs[last].second;
        } else {
            ++i;
        }
    }
    hkEntity_removeEntityListener(e, (void*)((char*)this - 0x18));
}

// ---------------------------------------------------------------- 011294e0
struct hkFilterCtor {
    void ctor(unsigned int flag);
};

// @ 0x011294e0
int hkCreateFilterCtor(unsigned int a)
{
    if (a) {
        ((hkFilterCtor*)(void*)a)->ctor(1);
    }
    return 1;
}

// ---------------------------------------------------------------- 01129640
struct hkMotorAction {
    char pad00[0x18];
    hkEntity* m_entity;      // +0x18
    char pad1c[4];
    hkVector4 m_axis;        // +0x20
    float     m_maxVelocity; // +0x30
    float     m_strength;    // +0x34
    char      m_enabled;     // +0x38
    hkMotorAction(hkpRigidBody* body, const hkVector4& axis, float maxVelocity, float strength);
};

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
    float s = (lenSq == 0.0f) ? 0.0f : 1.0f / hkSqrt(lenSq);
    m_axis.x = s * m_axis.x;
    m_axis.y = s * m_axis.y;
    m_axis.z = s * m_axis.z;
    m_axis.w = s * m_axis.w;
}

// ---------------------------------------------------------------- 01129720 / 011297f0 / big stubs
struct hkMotorActionImpl : hkMotorAction {
    void applyActionImpl(const void* stepInfo);
    hkMotorActionImpl* cloneImpl(const void* newEntities, const void* newPhantoms) const;
};

// @ 0x01129720
void hkMotorActionImpl::applyActionImpl(const void* stepInfo)
{
    (void)stepInfo;
}

// @ 0x011297f0
hkMotorActionImpl* hkMotorActionImpl::cloneImpl(const void* newEntities, const void* newPhantoms) const
{
    (void)newEntities; (void)newPhantoms; return 0;
}

// @ 0x01129500 -- hkGroupCollisionFilter support (large); partial skeleton.
void FUN_01129500(void) {}

// @ 0x01129850 -- hkGroupCollisionFilter::isCollisionEnabled core (large); partial skeleton.
void FUN_01129850(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }

// @ 0x01129420 -- multi-vtable filter ctor (5 bases); partial skeleton.
struct hkMultiFilter {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    char pad[0x28];
    void ctor(unsigned int flag);
};
void hkMultiFilter::ctor(unsigned int flag)
{
    (void)flag;
    *(int*)((char*)this + 0x1c) = 0;
    *(int*)((char*)this + 0x20) = 0;
    *(int*)((char*)this + 0x24) = 0x80000000;
}

// ---------------------------------------------------------------- 01129af0
struct hkCollisionInput { char pad[0x40]; };
struct hkCdBody { char pad[0x40]; };
struct hkShapeCollection { char pad[0x40]; };

// @ 0x01129af0
hkBool isCollisionEnabledGroup(int* self, const hkCollisionInput& input, const hkCdBody& bodyA,
                               const hkCdBody& bodyB, hkShapeCollection* shape, unsigned int a)
{
    (void)input; (void)bodyA; (void)bodyB; (void)shape;
    // resolve a parent group pointer then delegate to FUN_01129850
    int* p = (int*)0;
    (void)p; (void)self; (void)a;
    return true;
}

// ---------------------------------------------------------------- 01129b40
// @ 0x01129b40
hkBool isCollisionEnabledGroup2(int* self, const hkCdBody& bodyA, const hkCdBody& bodyB, unsigned int a)
{
    (void)self; (void)bodyA; (void)bodyB; (void)a;
    return true;
}

// ---------------------------------------------------------------- 01129c70 / 01129cc0 / 01129d20
struct hkDisableEntityCollisionFilter {
    char pad00[0x14];
    void** m_arr;  // +0x14
    int    m_n;    // +0x18
    char   pad1c[4];
    void** m_arr2; // +0x1c
    int    m_n2;   // +0x20
    hkBool isCollisionEnabled(const hkCollidable& a, const hkCollidable& b) const;
    void entityRemovedCallback(hkEntity* e);
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
hkBool hkDisableEntityCollisionFilter_remove(hkDisableEntityCollisionFilter* self, void* item)
{
    if (item == 0) return hkBool(false);
    for (int i = 0; i < self->m_n2; ++i) {
        if (self->m_arr2[i] == item) {
            int last = self->m_n2 - 1;
            self->m_n2 = last;
            self->m_arr2[i] = self->m_arr2[last];
            return hkBool(true);
        }
    }
    return hkBool(false);
}

// @ 0x01129d20
void hkDisableEntityCollisionFilter::entityRemovedCallback(hkEntity* e)
{
    hkDisableEntityCollisionFilter_remove(this, e);
}
