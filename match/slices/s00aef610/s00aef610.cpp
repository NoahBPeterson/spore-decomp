// Slice s00aef610 (batch gold4) — SP::cHavokLocomotiveController + its
// collision-listener sub-object (0x150-byte "Simulator" Havok controller;
// ctor 0x00aefb80).
//
// Layout (from the ctor 0x00aefb80 and neighbouring slices):
//   +0x00  bool m_enabled
//   +0x04  float
//   +0x10..+0x1c floats, +0x18 hkRigidBody* m_body0
//   +0x20  float (read as a byte in 0x00aef750)
//   +0x24  float
//   +0x28  bool
//   +0x2c  int
//   +0x30  float
//   +0x34  bool
//   +0x40..+0x4c floats (rot / misc)
//   +0x50  hkWorld* m_world
//   +0x54  hkRigidBody* m_body
//   +0x58  cHavokLocomotiveCollisionListener (0x28 bytes, own vtable)
//   +0x80  SP::cEntityListener (embedded base, 0xb8 bytes)
//   +0x138 pad
//   +0x140 float m_lastDeltaTime
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

#include "types.h"
#include <math.h>

#pragma pack(push, 8)

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);

typedef float hkReal;

class hkWorld;
class hkRigidBody;

class __declspec(align(16)) hkVector4 {
public:
    hkReal x, y, z, w;
    void operator=(const hkVector4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    hkReal& operator()(int i) { return (&x)[i]; }
    void setZero4() { x = y = z = w = 0.0f; }
    void set(hkReal a, hkReal b, hkReal c, hkReal d = 0.0f) { x = a; y = b; z = c; w = d; }
    void setAll(hkReal a) { x = y = z = w = a; }
    void mul4(hkReal s) { x *= s; y *= s; z *= s; w *= s; }
    hkReal lengthSquared3() const { return x * x + y * y + z * z; }
};

static __forceinline hkReal hkSqrtInverse(hkReal r) { return (hkReal)(1.0f / sqrt(r)); }

// ---- hkThreadMemory --------------------------------------------------------
extern unsigned long g_hkThreadMemoryTls;       // 0x016E4174

struct hkThreadMemory {
    void deallocateChunk(void* p, int numBytes, int memoryClass);          // 0x0107DB10
};

namespace hkArrayUtil {
void _reserveMore(void* array, int elemSize);                  // 0x0107F530
void _reserveExactly(void* array, int count, int elemSize);    // 0x0107F4A0
}

// ---- Havok classes used here ----------------------------------------------
class hkRigidMotion {
public:
    float getMass() const;                                        // 0x01088270
};

class hkRigidBody {
public:
    uint32_t pad00[2];
    int m_field08;                                  // +0x08  ("is in world" guard)
    uint32_t pad0c[(0x50 - 0x0c) / 4];
    hkWorld* m_world;                               // +0x50
    uint32_t pad54;
    hkRigidMotion* m_motion;                        // +0x58
    void setPosition(const hkVector4& pos);                       // 0x01087820
    void addCollisionListener(void* listener);                    // 0x01088C90
    void removeCollisionListener(void* listener);                 // 0x01088A70
    void addReference();                                          // 0x01082590
};

class hkWorld {
public:
    hkRigidBody* addEntity(hkRigidBody* entity, int activation);  // 0x01082EE0
    void removeEntity(bool* pb, hkRigidBody* entity);             // 0x01083110
};

// A node of the collidable chain walked in 0x00aef610.
struct hkCollidableNode {
    uint32_t pad00[3];
    hkCollidableNode* m_next;           // +0x0c
    int m_shapeKey;                     // +0x10
    uint32_t pad14;
    char m_hasKey;                      // +0x18
};

// Contact-confirmed event (0x00aef610 / 0x00aef930 argument).
struct hkCollidableConfirmedEvent {
    hkCollidableNode* m_collidableA;        // +0x00
    hkCollidableNode* m_collidableB;        // +0x04
    uint32_t pad08;
    void* m_contactPoint;                   // +0x0c
    uint32_t pad10[4];
    hkRigidBody* m_body;                    // +0x20
    unsigned short getContactPointId() const;                     // 0x0108D040
};

class hkResponseModifier {
public:
    static void setInvMassScalingForContact(
        hkRigidBody* contactMgr, hkRigidBody* bodyA, hkRigidBody* bodyB,
        float invMassScaling, float timeFactor);                  // 0x0108CA40
};

namespace SP {

class cHavokLocomotiveController;
class cHavokLocomotiveCollisionListener;

// ---- SP::cEntityListener (embedded base at +0x80) --------------------------
struct hkArrayUint {
    unsigned int* m_data;
    int m_size;
    int m_capacityAndFlags;
};

class cEntityListener {
public:
    bool m0;                    // +0x0
    char _pad0[3];
    void* m4;                   // +0x4
    char _pad8[8];              // +0x8
    float m10, m14, m18, m1c;   // +0x10
    float m20, m24, m28, m2c;   // +0x20
    float m30, m34, m38;        // +0x30
    bool m3c;                   // +0x3c
    char _pad3d[3];
    float m40, m44;             // +0x40
    char m48, m49, m4a;         // +0x48
    char _pad4b;
    int m4c;                    // +0x4c
    float m50, m54, m58, m5c;   // +0x50
    void* m_vtbl;               // +0x60
    cEntityListener* m64;       // +0x64
    void* m68;                  // +0x68
    char _pad6c[4];             // +0x6c
    float m70, m74, m78, m7c;   // +0x70
    float m80, m84, m88, m8c;   // +0x80
    float m90, m94, m98;        // +0x90
    hkArrayUint m9c;            // +0x9c
    uint32_t ma8;               // +0xa8
    uint32_t mac;               // +0xac
    uint32_t mb0, mb4;          // +0xb0

    void Construct();                                             // 0x00AF9B50
    void Destroy();                                               // 0x00AF9CA0
    void FUN_00af8a10(int a, float f);                            // 0x00AF8A10
};

// Contact point record appended by 0x00aef930 (stride 0x30).
struct __declspec(align(16)) hkContactPointEvent {
    int m_contactPointId;               // +0x00
    uint32_t pad04[3];
    float m_data[8];                    // +0x10
};

// ---------------------------------------------------------------------------
// The hkCollisionListener sub-object at +0x58 of the controller.
// ---------------------------------------------------------------------------
class cHavokLocomotiveCollisionListener {
public:
    struct Array {
        hkContactPointEvent* m_data;                        // +0x0c
        int m_size;                                         // +0x10
        int m_capacityAndFlags;                             // +0x14
    };
    void* m_vtbl;                                       // +0x00
    int m_field04;                                      // +0x04
    int m_field08;                                      // +0x08
    Array m_arr;                                        // +0x0c
    cHavokLocomotiveController* m_owner;                // +0x18
    bool m_field1c;                                     // +0x1c
    char pad1d[3];
    float m_field20;                                    // +0x20
    uint32_t pad24;

    void AddConfirmedContact(hkCollidableConfirmedEvent* ev);     // 0x00AEF930
    void RemoveContact(unsigned short* id);                       // 0x00AEFA40
    void* FUN_00aefb30(unsigned int flags);                       // 0x00AEFB30
};

// ---------------------------------------------------------------------------
// SP::cHavokLocomotiveController — 0x150-byte Havok controller.
// ---------------------------------------------------------------------------
class cHavokLocomotiveController {
public:
    char m_enabled;                                     // +0x00
    char m_hasContacts;                                 // +0x01
    char pad02[2];
    float m_field04;                                    // +0x04
    char pad08[8];
    float m_field10;                                    // +0x10
    float m_field14;                                    // +0x14
    hkRigidBody* m_body0;                               // +0x18
    bool m_field1c;                                     // +0x1c
    char pad1d[3];
    float m_field20;                                    // +0x20
    float m_field24;                                    // +0x24
    char m_field28;                                     // +0x28
    char pad29[3];
    int m_field2c;                                      // +0x2c
    float m_field30;                                    // +0x30
    char m_field34;                                     // +0x34
    char pad35[11];
    float m_field40;                                    // +0x40
    float m_field44;                                    // +0x44
    float m_field48;                                    // +0x48
    float m_field4c;                                    // +0x4c
    hkWorld* m_world;                                   // +0x50
    hkRigidBody* m_body;                                // +0x54
    cHavokLocomotiveCollisionListener m_listener;       // +0x58
    cEntityListener m_entityListener;                   // +0x80
    char pad138[8];
    float m_lastDeltaTime;                              // +0x140
    char pad144[12];

    cHavokLocomotiveController(hkRigidBody* body);                // 0x00AEFB80
    void SetPosition(const hkVector4& pos);                       // 0x00AEF7E0
    void SetEnabled(bool enabled);                                // 0x00AEF750
    void FUN_00aef6b0(int a, float f);                            // 0x00AEF6B0
    void AddToWorld();                                            // 0x00AEF6E0
    void FUN_00aef690(char b);                                    // 0x00AEF690
    void HandleConfirmedContact(hkCollidableConfirmedEvent* ev);  // 0x00AEF610
    void FUN_00aef8c0(hkWorld* world, hkWorld* planet);           // 0x00AEF8C0
    void FUN_00aefae0();                                          // 0x00AEFAE0
    void FUN_00aef410();                                          // 0x00AEF410
    void FUN_00aef330();                                          // 0x00AEF330
};

void FUN_00b4d8e0(void* a, hkRigidBody* body);                     // 0x00B4D8E0

// Object 0x00aef6e0 queries for a "creature" component.
class D961 {
public:
    int* Find(int* out, int tag);                                 // 0x00496140
};

// Component returned by D961::Find (vtable slot 3 takes a message id).
class cCreatureComponent {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual int HandleMessage(unsigned int msg);
};

}  // namespace SP

#pragma pack(pop)

using namespace SP;

extern void* g_locoListenerVtbl;              // 0x0145C160
extern void* g_locoListenerVtblDestroyed;     // 0x013F8990
extern const float g_kLocoSoftFactor;         // 0x014853BC
extern const float g_kLocoPointOne;           // 0x01488874 = 0.1f
extern const float g_kLocoOne;                // 0x01485720 = 1.0f
extern const float g_kLocoNegOne;             // 0x013EB1BC = -1.0f
extern const float g_kLocoTwoHundred;         // 0x01567258 = 200.0f

// ===========================================================================
// @ 0x00aef610
// ===========================================================================
void SP::cHavokLocomotiveController::HandleConfirmedContact(hkCollidableConfirmedEvent* ev) {
    if (!(char)m_field1c)
        return;

    hkCollidableNode* nB = ev->m_collidableB;
    while (nB->m_next)
        nB = nB->m_next;
    char* idB = 0;
    if (nB->m_hasKey == 1)
        idB = (char*)nB + nB->m_shapeKey;

    hkCollidableNode* nA = ev->m_collidableA;
    while (nA->m_next)
        nA = nA->m_next;
    char* idA = 0;
    if (nA->m_hasKey == 1)
        idA = (char*)nA + nA->m_shapeKey;

    char* p0 = idB;
    char* p1 = idA;
    if (p0 == *(char**)((char*)m_body0 + 0x54)) {
        char* t = p0;
        p0 = p1;
        p1 = t;
    }
    hkResponseModifier::setInvMassScalingForContact(
        ev->m_body, (hkRigidBody*)p1, (hkRigidBody*)p0, m_field20, 1.0f);
}

// ===========================================================================
// @ 0x00aef690
// ===========================================================================
void SP::cHavokLocomotiveController::FUN_00aef690(char b) {
    char* self = (char*)this;
    if (b) {
        if (*self == 0) {
            *self = b;
            *(int*)(self + 0x68) = 0;
            return;
        }
        *self = b;
    } else {
        *self = b;
    }
}

// ===========================================================================
// @ 0x00aef6b0
// ===========================================================================
void SP::cHavokLocomotiveController::FUN_00aef6b0(int a, float f) {
    m_entityListener.FUN_00af8a10(a, f);
    FUN_00aef410();
    FUN_00aef330();
}

// ===========================================================================
// @ 0x00aef6e0
// ===========================================================================
void SP::cHavokLocomotiveController::AddToWorld() {
    m_world->addEntity(m_body, 1);
    m_body->addCollisionListener(&m_listener);
    FUN_00aef330();

    int local[2];
    int* found = ((D961*)m_body)->Find(local, 1);
    cCreatureComponent* obj = (cCreatureComponent*)*found;
    if (!obj)
        return;
    if (!obj->HandleMessage(0xce9f6639))
        return;
    void* r = (void*)obj->HandleMessage(0x01186577);
    FUN_00b4d8e0(r, m_body);
}

// ===========================================================================
// @ 0x00aef750
// ===========================================================================
void SP::cHavokLocomotiveController::SetEnabled(bool enabled) {
    char old = m_entityListener.m0;
    if (!m_world) {
        m_entityListener.m0 = enabled;
        return;
    }
    if (old) {
        if (!enabled) {
            m_body->removeCollisionListener(&m_listener);
            m_world->removeEntity(&enabled, m_body);
            m_entityListener.m0 = enabled;
            return;
        }
        if (old)
            goto store;
    }
    if (enabled) {
        AddToWorld();
        if (m_entityListener.m4c > 0 && *(char*)&m_field20) {
            FUN_00aef6b0(0, g_kLocoSoftFactor);
            m_entityListener.m0 = enabled;
            return;
        }
    }
store:
    m_entityListener.m0 = enabled;
}

// ===========================================================================
// @ 0x00aef7e0
// ===========================================================================
void SP::cHavokLocomotiveController::SetPosition(const hkVector4& pos) {
    hkVector4* rot = (hkVector4*)&m_entityListener.m10;
    rot->x = pos.x;
    rot->y = pos.y;
    rot->z = pos.z;
    rot->w = pos.w;

    float* dst = &m_entityListener.m50;
    float lenSq = (pos.z * pos.z + pos.y * pos.y) + pos.x * pos.x;
    float inv;
    if (lenSq != 0.0f)
        inv = hkSqrtInverse(lenSq);
    else
        inv = 0.0f;
    dst[0] = pos.x * inv;
    dst[1] = inv * pos.y;
    dst[2] = pos.z * inv;
    dst[3] = pos.w * inv;

    if (m_body->m_field08 != 0)
        m_body->setPosition(pos);
    FUN_00aef410();
}

// ===========================================================================
// @ 0x00aef8c0
// ===========================================================================
void SP::cHavokLocomotiveController::FUN_00aef8c0(hkWorld* world, hkWorld* planet) {
    char* s = (char*)this;
    *(int*)(s + 0x134) = (int)planet;
    m_entityListener.m30 = m_body->m_motion->getMass();
    *(int*)(s + 0x130) = (int)world;
    m_entityListener.m2c = 0.0f;
    m_entityListener.m28 = 0.0f;
    m_entityListener.m24 = 0.0f;
    m_entityListener.m20 = 0.0f;
    bool enabled = m_entityListener.m0;
    m_world = world;
    if (enabled)
        AddToWorld();
}

// ===========================================================================
// @ 0x00aef930
// ===========================================================================
void SP::cHavokLocomotiveCollisionListener::AddConfirmedContact(hkCollidableConfirmedEvent* ev) {
    m_field04 = m_field04 + 1;
    if (!*(char*)m_owner)
        return;

    const float* src = (const float*)ev->m_contactPoint;
    unsigned int id = ev->getContactPointId();
    hkContactPointEvent pt;
    pt.m_data[0] = src[0];
    pt.m_data[1] = src[1];
    pt.m_data[2] = src[2];
    pt.m_data[3] = src[3];
    pt.m_data[4] = src[4];
    pt.m_data[5] = src[5];
    pt.m_data[6] = src[6];
    pt.m_data[7] = src[7];
    pt.m_contactPointId = (int)id;

    if (m_arr.m_size == (m_arr.m_capacityAndFlags & 0x3fffffff))
        hkArrayUtil::_reserveMore(&m_arr, 0x30);
    hkContactPointEvent& dst = m_arr.m_data[m_arr.m_size];
    dst.m_contactPointId = pt.m_contactPointId;
    dst.m_data[0] = pt.m_data[0];
    dst.m_data[1] = pt.m_data[1];
    dst.m_data[2] = pt.m_data[2];
    dst.m_data[3] = pt.m_data[3];
    dst.m_data[4] = pt.m_data[4];
    dst.m_data[5] = pt.m_data[5];
    dst.m_data[6] = pt.m_data[6];
    dst.m_data[7] = pt.m_data[7];
    m_arr.m_size++;
}

// ===========================================================================
// @ 0x00aefa40
// ===========================================================================
void SP::cHavokLocomotiveCollisionListener::RemoveContact(unsigned short* id) {
    --m_field04;
    int n = m_field04;
    m_field04 = (n < 0) ? 0 : n;
    if (!*(char*)m_owner)
        return;

    int count = m_arr.m_size;
    if (count <= 0)
        return;
    int i = 0;
    hkContactPointEvent* p = m_arr.m_data;
    int sid = (int)*id;
    for (;;) {
        if (p->m_contactPointId == sid)
            break;
        i++;
        p++;
        if (i >= count)
            return;
    }
    m_arr.m_size = count - 1;
    hkContactPointEvent* back = m_arr.m_data + (count - 1);
    hkContactPointEvent* at = m_arr.m_data + i;
    at->m_contactPointId = back->m_contactPointId;
    at->m_data[0] = back->m_data[0];
    at->m_data[1] = back->m_data[1];
    at->m_data[2] = back->m_data[2];
    at->m_data[3] = back->m_data[3];
    at->m_data[4] = back->m_data[4];
    at->m_data[5] = back->m_data[5];
    at->m_data[6] = back->m_data[6];
    at->m_data[7] = back->m_data[7];
}

// ===========================================================================
// @ 0x00aefae0
// ===========================================================================
void SP::cHavokLocomotiveController::FUN_00aefae0() {
    m_entityListener.Destroy();
    if ((m_listener.m_arr.m_capacityAndFlags & 0x80000000) == 0) {
        int cap = m_listener.m_arr.m_capacityAndFlags & 0x3fffffff;
        hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
        tm->deallocateChunk(m_listener.m_arr.m_data, cap * 0x30, 0x14);
    }
    m_listener.m_vtbl = &g_locoListenerVtblDestroyed;
}

// ===========================================================================
// @ 0x00aefb30
// ===========================================================================
void* SP::cHavokLocomotiveCollisionListener::FUN_00aefb30(unsigned int flags) {
    if ((m_arr.m_capacityAndFlags & 0x80000000) == 0) {
        int cap = m_arr.m_capacityAndFlags & 0x3fffffff;
        hkThreadMemory* tm = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
        tm->deallocateChunk(m_arr.m_data, cap * 0x30, 0x14);
    }
    m_vtbl = &g_locoListenerVtblDestroyed;
    if (flags & 1)
        operator delete(this);
    return this;
}

// ===========================================================================
// @ 0x00aefb80
// ===========================================================================
SP::cHavokLocomotiveController::cHavokLocomotiveController(hkRigidBody* body) {
    float soft = g_kLocoPointOne;
    m_listener.m_vtbl = &g_locoListenerVtbl;
    m_listener.m_field04 = 0;
    m_listener.m_field08 = 0;
    m_listener.m_arr.m_data = 0;
    m_listener.m_arr.m_size = 0;
    m_listener.m_arr.m_capacityAndFlags = (int)0x80000000;
    m_listener.m_owner = 0;
    m_listener.m_field1c = false;
    m_listener.m_field20 = soft;
    if ((m_listener.m_arr.m_capacityAndFlags & 0x3fffffff) < 8)
        hkArrayUtil::_reserveExactly(&m_listener.m_arr, 8, 0x30);
    m_entityListener.Construct();

    m_field04 = 0.0f;
    m_enabled = 0;
    m_hasContacts = 0;
    m_field1c = false;
    m_body0 = 0;
    m_field14 = 0.0f;
    m_field10 = 0.0f;
    m_field34 = 0;
    m_field30 = soft;
    *(char*)&m_field20 = 0;
    m_field24 = g_kLocoTwoHundred;
    m_field28 = 1;
    m_field2c = 0;
    m_field04 = 0.0f;
    m_field40 = 0.0f;
    m_field44 = 0.0f;
    m_field48 = 0.0f;
    m_field4c = g_kLocoOne;
    m_entityListener.ma8 = *(uint32_t*)&g_kLocoOne;
    m_entityListener.mac = *(uint32_t*)&g_kLocoNegOne;
    m_world = 0;
    m_listener.m_owner = this;
    m_body = body;
    body->addReference();
    m_lastDeltaTime = 0.0f;
}
