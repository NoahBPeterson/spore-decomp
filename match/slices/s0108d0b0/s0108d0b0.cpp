// Havok 3.1.0 (statically linked, ~2005 MSVC x87 build): hkSimpleConstraintContactMgr and
// its Factory, hkDynamicsCpIdMgr::getAllUsedIds, hkShapePhantom and hkAabbPhantom members.
//
// Functional-equivalence rewrite (not byte-exact). Member offsets follow the 32-bit retail
// layout; calls into Havok functions that live in other slices are declared extern with
// the class they belong to (so the calling convention is the original thiscall).
//
// Float notes (x87): friction/restitution are sqrt(a*b)*scale kept in extended precision up
// to a single store to a float local, then fistp (round-to-nearest-even, NOT truncation) and
// only the low 16 / 8 bits stored. See hkFistp() and hkSqrtScaled() below.
#include "types.h"
#include <math.h>
#include <new>
#if defined(_M_IX86) || defined(_M_X64) || defined(__SSE__)
#include <xmmintrin.h>
#endif

#ifndef _WIN64
#define HK_OFFSET_CHECK(name, cond) typedef char name[(cond) ? 1 : -1]
#else
#define HK_OFFSET_CHECK(name, cond)
#endif
#define HK_PAD(n) uint8_t

// ---------------------------------------------------------------------------------------
// Small helpers
// ---------------------------------------------------------------------------------------

// x87 fistp dword with the default rounding mode (round to nearest even). Out of range or
// NaN yields the "integer indefinite" value 0x80000000 as the hardware does.
static inline int32_t hkFistp(float f)
{
#if defined(_M_IX86) || defined(_M_X64) || defined(__SSE__)
    // cvtss2si rounds with the current mode (nearest even) and returns 0x80000000 for
    // NaN/out-of-range, exactly like fistp.
    return _mm_cvtss_si32(_mm_set_ss(f));
#else
    if (!(f >= -2147483648.0f && f < 2147483648.0f)) return (int32_t)0x80000000;
    return (int32_t)lrintf(f);
#endif
}

// float -> (fld a; fmul b; fsqrt; fmul scale; fstp float).
// X87-PRECISION: the product, the square root and the scale all stay in 80-bit registers in
// the original; only the final fstp rounds to float. a*b of two floats is exact in a double,
// so only the sqrt rounding (53 vs 64 bits) can differ from the binary.
static inline float hkSqrtScaled(float a, float b, float scale)
{
    return (float)(sqrt((double)a * (double)b) * (double)scale);
}

template <typename T> struct hkArray {
    T* m_data; int32_t m_size; int32_t m_capacityAndFlags;
};

struct hkVector4 { float m_x, m_y, m_z, m_w; };
struct hkAabb { hkVector4 m_min, m_max; };
struct hkTransform { hkVector4 m_rotation[3]; hkVector4 m_translation; };  // 0x40 in later SDKs; layout used only by address here

struct hkContactPoint {                       // 32 bytes
    hkVector4 m_position;
    hkVector4 m_separatingNormal;             // xyz = normal, w = distance
};

struct hkContactPointMaterial {               // 12 bytes (at +8 of hkContactPointProperties)
    uint32_t m_userData;
    uint16_t m_friction;                      // sqrt(muA*muB) * 256, rounded
    uint8_t  m_restitution;                   // sqrt(rA*rB) * 128, rounded
    uint8_t  m_maxImpulse;
    uint8_t  m_flags;
    uint8_t  m_pad[3];
};
struct hkContactPointProperties {             // 0x14 bytes
    uint32_t m_impulse[2];
    hkContactPointMaterial m_material;
};
HK_OFFSET_CHECK(chk_props_size, sizeof(hkContactPointProperties) == 0x14);

struct hkReferencedObject {
    virtual ~hkReferencedObject() {}
    uint16_t m_memSizeAndFlags;               // +4
    uint16_t m_referenceCount;                // +6
};

struct hkCdBody {
    void*            m_shape;                 // +0x00
    uint32_t         m_shapeKey;              // +0x04
    void*            m_motion;                // +0x08
    const hkCdBody*  m_parent;                // +0x0c
};
struct hkCollidable : hkCdBody {
    int32_t          m_ownerOffset;           // +0x10
};
static inline uint8_t* hkCollidable_getOwner(const hkCollidable* c) { return (uint8_t*)c + c->m_ownerOffset; }
// Follow m_parent to the root collidable, then to its owner.
static inline uint8_t* hkCdBody_getRootOwner(const hkCdBody* b)
{
    while (b->m_parent) b = b->m_parent;
    return (uint8_t*)b + ((const hkCollidable*)b)->m_ownerOffset;
}

struct hkRigidBodyListenerView;
// The few hkRigidBody (hkEntity) fields touched by this slice.
struct hkEntity {
    void*    m_vptr;
    uint8_t  m_pad0[0x36 - 4];
    int16_t  m_objectQualityType;             // +0x36 (collidable broadphase handle quality type)
    uint8_t  m_pad1[0x64 - 0x38];
    float    m_friction;                      // +0x64
    float    m_restitution;                   // +0x68
    uint8_t  m_pad2[0x96 - 0x6c];
    uint16_t m_processContactCallbackDelay;   // +0x96
    uint8_t  m_pad3[0x9c - 0x98];
    void*    m_contactListenersData;          // +0x9c (hkArray<hkContactListener*> data)
    int32_t  m_numContactListeners;           // +0xa0 (hkArray size; non-zero = listeners present)

    // @ 0x0108cf90
    void getPointVelocity(const hkVector4& p, hkVector4& velOut) const;
};
HK_OFFSET_CHECK(chk_ent_friction, 1);

struct hkCriticalSection {
    uint8_t  m_win32CriticalSection[0x18];    // CRITICAL_SECTION
    uint32_t m_owner;                         // +0x18
    int32_t  m_recursion;                     // +0x1c
    // @ 0x0107f820
    void enter();
    // inlined in the callers: reset bookkeeping, then LeaveCriticalSection
    inline void leave()
    {
        m_owner = 0xffffffffu;
        m_recursion = -1;
        hkLeaveCriticalSection(this);
    }
    static void hkLeaveCriticalSection(void* cs);   // kernel32 LeaveCriticalSection (IAT call)
};

struct hkMemory {
    virtual ~hkMemory() {}
    virtual void vslot1();
    virtual void vslot2();
    virtual void vslot3();
    virtual void* allocateChunk(int nbytes, int memoryClass);   // +0x10
};
extern hkMemory* g_hkMemory;      // 0x016e4178 (hkMemory::s_instance)

struct hkStatisticsCollector {
    virtual ~hkStatisticsCollector();
    virtual void beginObject(const char* name, int flags, const void* obj);                                   // +4
    virtual void addArray(const char* name, int memClass, const void* data, int used, int allocated);        // +8
    virtual void vslot3();
    virtual void vslot4();
    virtual void vslot5();
    virtual void endObject();                                                                                // +0x18
};

struct hkCollisionInput { uint8_t m_pad[8]; float m_tolerance; };           // m_tolerance at +8

struct hkCollisionDispatcher {
    uint8_t m_pad[0x19d4];
    int8_t  m_collisionQualityMatrix[8][8];             // +0x19d4
    uint8_t m_pad2[0x1a4c - 0x19d4 - 64];
    struct { uint16_t m_constraintPriority; uint8_t m_rest[0x3c - 2]; } m_collisionQualityInfo[1];   // +0x1a4c, stride 0x3c
};

struct hkWorldOperationQueued { uint8_t m_type; void* m_object; void* m_arg; };

struct hkWorld {
    uint8_t m_pad0[0x78];
    hkCollisionInput* m_collisionInput;             // +0x78
    uint8_t m_pad1[4];
    hkCollisionDispatcher* m_collisionDispatcher;   // +0x80
    uint8_t m_pad2[4];
    int32_t m_pendingOperationsCount;               // +0x88
    int32_t m_criticalOperationsLockCount;          // +0x8c
    uint8_t m_pad3[4];
    uint8_t m_pendingOperationsInProgress;          // +0x94
    uint8_t m_pad4[0xac - 0x95];
    hkCriticalSection* m_criticalSection;           // +0xac

    // @ 0x010829d0 (ecx = world)
    void queueOperation(const hkWorldOperationQueued& op);
    // @ 0x01082bf0 (ecx = world)
    void attemptToExecutePendingOperations();
};
HK_OFFSET_CHECK(chk_world_cs, 1);

// ---------------------------------------------------------------------------------------
// Callback / event plumbing living in other slices
// ---------------------------------------------------------------------------------------
struct hkContactPointAddedEvent {                   // 0x28 bytes. Also used for TOI-added events (type 0).
    const hkCollidable* m_bodyA;                    // +0x00
    const hkCollidable* m_bodyB;                    // +0x04
    int32_t  m_type;                                // +0x08 (0 = TOI, 1 = normal)
    void*    m_callbackFiredFrom;                   // +0x0c (set by the callback utils; never written here)
    hkContactPoint* m_contactPoint;                 // +0x10
    hkContactPointMaterial* m_material;             // +0x14
    float    m_projectedVelocity;                   // +0x18
    int32_t  m_rejected;                            // +0x1c (result; 1 = reject/remove the point)
    void*    m_mgr;                                 // +0x20
    uint16_t m_contactPointId;                      // +0x24
    uint16_t m_nextSkipDelay;                       // +0x26
};
struct hkContactPointRemovedEvent {                 // 0x18 bytes
    uint16_t m_contactPointId;                      // +0x00
    uint16_t m_pad02;
    hkContactPointMaterial* m_material;             // +0x04
    hkEntity* m_bodyA;                              // +0x08
    hkEntity* m_bodyB;                              // +0x0c
    void*    m_callbackFiredFrom;                   // +0x10 (set by the callback utils)
    void*    m_mgr;                                 // +0x14
};
struct hkContactProcessEvent {                      // 0x410 bytes
    const hkCollidable* m_bodyA;
    const hkCollidable* m_bodyB;
    void* m_callbackFiredFrom;              // +0x08 (set by the callback utils)
    void* m_collisionData;                  // +0x0c
    hkContactPointProperties* m_props[256]; // +0x10
    void* m_mgr;
};

// @ 0x0109f040 / 0x0109e7c0 hkWorldCallbackUtil::fireContactPointAdded / hkEntityCallbackUtil::fireContactPointAddedInternal
extern void __cdecl hkWorldCallbackUtil_fireContactPointAdded(hkWorld*, hkContactPointAddedEvent&);
extern void __cdecl hkEntityCallbackUtil_fireContactPointAddedInternal(hkEntity*, hkContactPointAddedEvent&);
// @ 0x0109f160 / 0x0109e8e0
extern void __cdecl hkWorldCallbackUtil_fireContactPointRemoved(hkWorld*, hkContactPointRemovedEvent&);
extern void __cdecl hkEntityCallbackUtil_fireContactPointRemovedInternal(hkEntity*, hkContactPointRemovedEvent&);
// @ 0x0109f1f0 / 0x0109e970
extern void __cdecl hkWorldCallbackUtil_fireContactProcess(hkWorld*, hkContactProcessEvent&);
extern void __cdecl hkEntityCallbackUtil_fireContactProcessInternal(hkEntity*, hkContactProcessEvent&);
// @ 0x0109f930 / 0x0109fa10: add / remove the constraint instance to / from the world's
// critical-locked island bookkeeping (role inferred from the call sites).
extern void __cdecl hkWorld_addConstraintCritical(hkWorld*, void* constraintInstance, int);
extern void __cdecl hkWorld_removeConstraintCritical(hkWorld*, void* constraintInstance, int);

struct hkConstraintInstance {
    virtual ~hkConstraintInstance();
    uint16_t m_memSizeAndFlags;     // +4
    uint16_t m_referenceCount;      // +6
    uint32_t m_pad08[1];            // +8
    void*    m_data;                // +0x0c (relative to instance: +0x80 in the manager)
    hkEntity* m_entityA;            // +0x10
    hkEntity* m_entityB;            // +0x14
    uint32_t m_pad18[4];
    // @ 0x0108bf80
    hkConstraintInstance(int priority);
    // @ 0x0108bfb0
    void setPriority(int priority);
};

// virtual slots 9 and 10 are what the two forwarding thunks call
struct hkSimpleContactConstraintData {
    virtual void vslot0(); virtual void vslot1(); virtual void vslot2(); virtual void vslot3();
    virtual void vslot4(); virtual void vslot5(); virtual void vslot6(); virtual void vslot7();
    virtual void vslot8();
    virtual void vslot9();          // +0x24
    virtual void vslot10();         // +0x28
    uint16_t m_pad04;               // +4 (zeroed by the owner)
    uint32_t m_pad08[1];
    hkArray<uint8_t> m_idToIndex;                   // +0x0c: contact point id -> slot
    uint32_t m_pad18[2];
    hkArray<hkContactPoint> m_contactPoints;        // +0x20
    uint32_t m_pad2c[3];
    hkArray<hkContactPointProperties> m_properties; // +0x38
    uint32_t m_pad44[8];
    // @ 0x010a45b0
    hkSimpleContactConstraintData(hkConstraintInstance* instance);
    // @ 0x0108cb20
    ~hkSimpleContactConstraintData();
    // @ 0x010a42f0
    uint16_t allocateContactPoint(hkContactPoint** cpOut, hkContactPointProperties** propsOut);
    // @ 0x010a4420
    void freeContactPoint(uint16_t id);
};
HK_OFFSET_CHECK(chk_scd_size, sizeof(hkSimpleContactConstraintData) == 0x64 || sizeof(void*) != 4);

// ---------------------------------------------------------------------------------------
// hkSimpleConstraintContactMgr
// ---------------------------------------------------------------------------------------
struct hkProcessCollisionPoint {                    // 0x30 bytes
    hkContactPoint m_cp;
    uint16_t m_id;                                  // +0x20
    uint16_t m_pad22;
    uint32_t m_pad24[3];
};
struct hkProcessCollisionData {
    hkProcessCollisionPoint* m_firstFree;           // +0x00 (end of the contact point list)
    uint8_t m_pad[0x2c];
    hkProcessCollisionPoint m_points[1];            // +0x30
};
struct hkProcessCollisionInput;

struct hkSimpleConstraintContactMgr : hkReferencedObject {
    hkWorld*   m_world;                             // +0x08
    uint16_t   m_reservedContactPoints;             // +0x0c
    uint16_t   m_skipNextNprocessCallbacks;         // +0x0e
    hkSimpleContactConstraintData m_contactConstraintData;  // +0x10
    hkConstraintInstance m_constraint;              // +0x74 (m_data at +0x80, entities at +0x84/+0x88)

    // The virtual slots beyond the destructor that this slice calls.
    virtual void vslot1();
    virtual void vslot2();
    virtual void vslot3();
    virtual void removeContactPoint(uint16_t id);                                       // +0x10 (slot 4)
    virtual void vslot5();
    virtual void vslot6();
    virtual void vslot7();
    virtual hkContactPointProperties* getContactPointProperties(uint16_t id);           // +0x20 (slot 8)

    hkSimpleConstraintContactMgr(hkWorld* world, hkEntity* bodyA, hkEntity* bodyB);
    ~hkSimpleConstraintContactMgr();
    int addToi(const hkCollidable& a, const hkCollidable& b, const hkProcessCollisionInput& input,
               hkContactPoint& cp, float toi, float projectedVelocity, hkContactPointMaterial& material);
    uint16_t addContactPoint(const hkCollidable& a, const hkCollidable& b, const hkProcessCollisionInput& input,
                             hkContactPoint& cp);
    hkContactPoint* getContactPoint(uint16_t id);
    void processContact(const hkCollidable& a, const hkCollidable& b, const hkProcessCollisionInput& input,
                        hkProcessCollisionData& data);
    void calcStatistics(hkStatisticsCollector* collector) const;
    void thunkData9();
    void thunkData10();

    struct Factory : hkReferencedObject {
        hkWorld* m_world;                           // +8
        Factory(hkWorld* world);
        hkSimpleConstraintContactMgr* createContactMgr(const hkCollidable& a, const hkCollidable& b,
                                                       const void* input);
    };
};

struct hkContactPtIdArray;  // forward

// @ 0x0108d0b0
// hkSimpleConstraintContactMgr::addToi: only fills in the material and fires the TOI-added event.
int hkSimpleConstraintContactMgr::addToi(const hkCollidable& a, const hkCollidable& b,
        const hkProcessCollisionInput& input, hkContactPoint& cp, float toi, float projectedVelocity,
        hkContactPointMaterial& material)
{
    hkEntity* bodyA = (hkEntity*)hkCdBody_getRootOwner(&a);
    hkEntity* bodyB = (hkEntity*)hkCdBody_getRootOwner(&b);

    // X87-PRECISION: fld bodyB.friction; fmul bodyA.friction; fsqrt; fmul 256.0; fstp float; fistp.
    float friction = hkSqrtScaled(bodyB->m_friction, bodyA->m_friction, 256.0f);       // const @ 0x013f1160
    material.m_friction = (uint16_t)hkFistp(friction);
    float restitution = hkSqrtScaled(bodyB->m_restitution, bodyA->m_restitution, 128.0f); // const @ 0x01400a58
    material.m_restitution = (uint8_t)hkFistp(restitution);

    hkContactPointAddedEvent ev;
    ev.m_bodyA = &a;
    ev.m_bodyB = &b;
    ev.m_type = 0;
    ev.m_contactPoint = &cp;
    ev.m_material = &material;
    ev.m_projectedVelocity = projectedVelocity;
    ev.m_rejected = 0;
    ev.m_mgr = this;
        *(float*)&ev.m_contactPointId = toi;   // +0x24: raw copy of the first float argument

    hkWorldCallbackUtil_fireContactPointAdded(m_world, ev);
    if (bodyA->m_numContactListeners != 0) hkEntityCallbackUtil_fireContactPointAddedInternal(bodyA, ev);
    if (bodyB->m_numContactListeners != 0) hkEntityCallbackUtil_fireContactPointAddedInternal(bodyB, ev);
    return ev.m_rejected;
}

// @ 0x0108d1c0
uint16_t hkSimpleConstraintContactMgr::addContactPoint(const hkCollidable& a, const hkCollidable& b,
        const hkProcessCollisionInput& input, hkContactPoint& cp)
{
    // too many points for the 8 bit slot ids
    if ((int)((uint32_t)m_reservedContactPoints + m_contactConstraintData.m_properties.m_size) >= 0xff)
        return 0xffff;

    hkEntity* bodyA = (hkEntity*)hkCdBody_getRootOwner(&a);
    hkEntity* bodyB = (hkEntity*)hkCdBody_getRootOwner(&b);

    if (m_contactConstraintData.m_properties.m_size == 0) {
        // first contact: register the constraint with the world, under the critical section
        hkCriticalSection* cs = m_world->m_criticalSection;
        if (!cs) {
            hkWorld_addConstraintCritical(m_world, &m_constraint, 1);
        } else {
            cs->enter();
            hkWorld_addConstraintCritical(m_world, &m_constraint, 1);
            m_world->m_criticalSection->leave();
        }
    }

    hkContactPoint* newCp;
    hkContactPointProperties* newProps;
    uint16_t id = m_contactConstraintData.allocateContactPoint(&newCp, &newProps);
    *newCp = cp;                      // eight dword copies

    hkVector4 velA, velB;
    bodyA->getPointVelocity(cp.m_position, velA);
    bodyB->getPointVelocity(cp.m_position, velB);

    // X87-PRECISION: whole expression stays on the FPU stack; order is (dz*nz + dy*ny) + dx*nx.
    double dx = (double)velA.m_x - (double)velB.m_x;
    double dy = (double)velA.m_y - (double)velB.m_y;
    double dz = (double)velA.m_z - (double)velB.m_z;
    float projectedVelocity = (float)((dz * (double)cp.m_separatingNormal.m_z + dy * (double)cp.m_separatingNormal.m_y)
                                      + dx * (double)cp.m_separatingNormal.m_x);

    // X87-PRECISION: note operand order bodyB * bodyA (commutative, product is exact in double)
    float friction = hkSqrtScaled(bodyB->m_friction, bodyA->m_friction, 256.0f);
    newProps->m_material.m_friction = (uint16_t)hkFistp(friction);
    float restitution = hkSqrtScaled(bodyB->m_restitution, bodyA->m_restitution, 128.0f);
    newProps->m_material.m_restitution = (uint8_t)hkFistp(restitution);
    newProps->m_impulse[0] = 0;       // *(uint32*)newProps = 0

    hkContactPointAddedEvent ev;
    ev.m_bodyA = &a;
    ev.m_bodyB = &b;
    ev.m_type = 1;
    ev.m_contactPoint = &cp;
    ev.m_material = &newProps->m_material;
    ev.m_projectedVelocity = projectedVelocity;
    ev.m_rejected = 0;
    ev.m_mgr = this;
    ev.m_contactPointId = id;
    ev.m_nextSkipDelay = 0;

    hkWorldCallbackUtil_fireContactPointAdded(m_world, ev);
    if (bodyA->m_numContactListeners != 0) hkEntityCallbackUtil_fireContactPointAddedInternal(bodyA, ev);
    if (bodyB->m_numContactListeners != 0) hkEntityCallbackUtil_fireContactPointAddedInternal(bodyB, ev);

    if (ev.m_rejected == 1) {
        removeContactPoint(id);       // virtual slot 4
        return 0xffff;
    }
    m_skipNextNprocessCallbacks = ev.m_nextSkipDelay;
    return id;
}

// @ 0x0108d420
void hkSimpleConstraintContactMgr::removeContactPoint(uint16_t id)
{
    hkEntity* bodyB = (hkEntity*)m_constraint.m_entityB;
    hkEntity* bodyA = (hkEntity*)m_constraint.m_entityA;

    hkContactPointRemovedEvent ev;
    // inlined getContactPointProperties(id): index through the id table (done even for 0xffff)
    hkContactPointProperties* props = m_contactConstraintData.m_properties.m_data
        + m_contactConstraintData.m_idToIndex.m_data[id];
    ev.m_material = props ? &props->m_material : 0;
    ev.m_contactPointId = id;
    ev.m_bodyA = bodyA;
    ev.m_bodyB = bodyB;
    ev.m_mgr = this;
    if (ev.m_contactPointId != 0xffff) {
        hkContactPointProperties* p = getContactPointProperties(id);    // virtual slot 8
        ev.m_material = p ? &p->m_material : 0;
    }

    hkWorldCallbackUtil_fireContactPointRemoved(m_world, ev);
    if (bodyA->m_numContactListeners != 0) hkEntityCallbackUtil_fireContactPointRemovedInternal(bodyA, ev);
    if (bodyB->m_numContactListeners != 0) hkEntityCallbackUtil_fireContactPointRemovedInternal(bodyB, ev);

    m_contactConstraintData.freeContactPoint(id);

    if (m_contactConstraintData.m_properties.m_size == 0) {
        hkCriticalSection* cs = m_world->m_criticalSection;
        if (!cs) {
            hkWorld_removeConstraintCritical(m_world, &m_constraint, 1);
        } else {
            cs->enter();
            hkWorld_removeConstraintCritical(m_world, &m_constraint, 1);
            m_world->m_criticalSection->leave();
        }
    }
}

// @ 0x0108d550
hkContactPoint* hkSimpleConstraintContactMgr::getContactPoint(uint16_t id)
{
    return m_contactConstraintData.m_contactPoints.m_data + m_contactConstraintData.m_idToIndex.m_data[id];
}

// @ 0x0108d570
hkContactPointProperties* hkSimpleConstraintContactMgr::getContactPointProperties(uint16_t id)
{
    return m_contactConstraintData.m_properties.m_data + m_contactConstraintData.m_idToIndex.m_data[id];
}

// @ 0x0108d590
void hkSimpleConstraintContactMgr::processContact(const hkCollidable& a, const hkCollidable& b,
        const hkProcessCollisionInput& input, hkProcessCollisionData& data)
{
    uint16_t skip = m_skipNextNprocessCallbacks;
    m_skipNextNprocessCallbacks = (uint16_t)(skip - 1);
    if (skip == 0) {
        hkEntity* ownerB = (hkEntity*)hkCollidable_getOwner(&b);
        hkEntity* ownerA = (hkEntity*)hkCollidable_getOwner(&a);
        uint16_t delay = ownerB->m_processContactCallbackDelay;
        if (ownerA->m_processContactCallbackDelay < ownerB->m_processContactCallbackDelay)
            delay = ownerA->m_processContactCallbackDelay;
        m_skipNextNprocessCallbacks = delay;

        hkContactProcessEvent ev;
        ev.m_bodyA = &a;
        ev.m_bodyB = &b;
        ev.m_collisionData = &data;
        ev.m_mgr = this;
        hkContactPointProperties** out = ev.m_props;
        const uint8_t* ids = m_contactConstraintData.m_idToIndex.m_data;
        hkContactPointProperties* props = m_contactConstraintData.m_properties.m_data;
        for (hkProcessCollisionPoint* p = data.m_points; p < data.m_firstFree; ++p)
            *out++ = props + ids[p->m_id];

        hkWorldCallbackUtil_fireContactProcess(m_world, ev);
        if (ownerA->m_numContactListeners != 0) hkEntityCallbackUtil_fireContactProcessInternal(ownerA, ev);
        if (ownerB->m_numContactListeners != 0) hkEntityCallbackUtil_fireContactProcessInternal(ownerB, ev);
    }

    // copy the freshly computed contact points into the constraint's storage
    for (hkProcessCollisionPoint* p = data.m_points; p < data.m_firstFree; ++p) {
        hkContactPoint* dst = m_contactConstraintData.m_contactPoints.m_data
            + m_contactConstraintData.m_idToIndex.m_data[p->m_id];
        *dst = p->m_cp;
    }
}

// @ 0x0108d850
hkSimpleConstraintContactMgr::Factory::Factory(hkWorld* world)
{
    m_referenceCount = 1;
    m_world = world;
}

// hkDynamicsCpIdMgr (byte array of slots, 0xff = free)
struct hkDynamicsCpIdMgr { hkArray<uint8_t> m_ids;  void getAllUsedIds(hkArray<uint16_t>& out) const; };
extern "C++" void hkArrayUtil_reserveMore(void* array, int elemSize);   // @ 0x0107f530 hkArrayUtil::_reserveMore

// @ 0x0108d8a0
void hkDynamicsCpIdMgr::getAllUsedIds(hkArray<uint16_t>& out) const
{
    for (int i = 0; i < m_ids.m_size; ++i) {
        if (m_ids.m_data[i] != 0xff) {
            if (out.m_size == (out.m_capacityAndFlags & 0x3fffffff))
                hkArrayUtil_reserveMore(&out, 2);
            out.m_data[out.m_size] = (uint16_t)i;
            out.m_size++;
        }
    }
}

// @ 0x0108d900
void hkSimpleConstraintContactMgr::calcStatistics(hkStatisticsCollector* c) const
{
    c->beginObject(0, 8, this);
    if (m_contactConstraintData.m_properties.m_capacityAndFlags >= 0)
        c->addArray("Props", 8, m_contactConstraintData.m_properties.m_data,
                    m_contactConstraintData.m_properties.m_size * 0x14,
                    (m_contactConstraintData.m_properties.m_capacityAndFlags & 0x3fffffff) * 0x14);
    if (m_contactConstraintData.m_contactPoints.m_capacityAndFlags >= 0)
        c->addArray("ContactPts", 8, m_contactConstraintData.m_contactPoints.m_data,
                    m_contactConstraintData.m_contactPoints.m_size << 5,
                    (m_contactConstraintData.m_contactPoints.m_capacityAndFlags & 0x3fffffff) << 5);
    if (m_contactConstraintData.m_idToIndex.m_capacityAndFlags >= 0)
        c->addArray("ContactIds", 8, m_contactConstraintData.m_idToIndex.m_data,
                    m_contactConstraintData.m_idToIndex.m_size,
                    m_contactConstraintData.m_idToIndex.m_capacityAndFlags & 0x3fffffff);
    c->endObject();
}

// @ 0x0108d9a0
hkSimpleConstraintContactMgr::hkSimpleConstraintContactMgr(hkWorld* world, hkEntity* bodyA, hkEntity* bodyB)
    : m_contactConstraintData(&m_constraint), m_constraint(1)
{
    m_referenceCount = 1;
    // the vptr store is emitted by the compiler
    m_constraint.m_data = &m_contactConstraintData;
    m_constraint.m_entityA = bodyA;
    m_constraint.m_entityB = bodyB;
    m_world = world;
    m_skipNextNprocessCallbacks = 0;
    m_reservedContactPoints = 0;
    m_contactConstraintData.m_pad04 = 0;
    m_constraint.m_memSizeAndFlags = 0;
    // collision priority = dispatcher->qualityInfo[ matrix[typeA][typeB] ].priority
    hkCollisionDispatcher* d = world->m_collisionDispatcher;
    int quality = d->m_collisionQualityMatrix[(uint16_t)bodyA->m_objectQualityType][(uint16_t)bodyB->m_objectQualityType];
    m_constraint.setPriority(d->m_collisionQualityInfo[quality].m_constraintPriority);
}

// @ 0x0108da30
void hkSimpleConstraintContactMgr::thunkData9()  { m_contactConstraintData.vslot9(); }

// @ 0x0108da40
void hkSimpleConstraintContactMgr::thunkData10() { m_contactConstraintData.vslot10(); }

// @ 0x0108da50
hkSimpleConstraintContactMgr::~hkSimpleConstraintContactMgr()
{
    if (m_contactConstraintData.m_properties.m_size != 0)
        hkWorld_removeConstraintCritical(m_world, &m_constraint, 1);
    m_constraint.m_entityA = 0;
    m_constraint.m_entityB = 0;
    m_constraint.m_data = 0;
    // member destructors (~hkConstraintInstance, ~hkSimpleContactConstraintData) follow
}

// @ 0x0108dab0
hkSimpleConstraintContactMgr*
hkSimpleConstraintContactMgr::Factory::createContactMgr(const hkCollidable& a, const hkCollidable& b, const void* input)
{
    hkEntity* ownerA = (hkEntity*)hkCollidable_getOwner(&a);
    hkEntity* ownerB = (hkEntity*)hkCollidable_getOwner(&b);
    void* mem = g_hkMemory->allocateChunk(0x9c, 0x1f);
    ((hkReferencedObject*)mem)->m_memSizeAndFlags = 0x9c;
    return new (mem) hkSimpleConstraintContactMgr(m_world, ownerA, ownerB);
}

// ---------------------------------------------------------------------------------------
// hkShapePhantom / hkAabbPhantom
// ---------------------------------------------------------------------------------------
struct hkShape : hkReferencedObject {
    virtual void vslot1();
    virtual void vslot2();
    // slot 3 (+0x0c)
    virtual void getAabb(const hkTransform& t, float tolerance, hkAabb& out) const;
};

struct hkMotionState {
    uint8_t m_pad[0x40];
    // @ 0x01088410
    void setTransform(const hkTransform& t);
};

struct hkPhantom;
extern void __cdecl hkWorldOperationUtil_removePhantomBP(hkWorld*, hkPhantom*);   // @ 0x010a0f20
extern void __cdecl hkWorldOperationUtil_addPhantomBP(hkWorld*, hkPhantom*);      // @ 0x010a0d10
extern void __cdecl hkWorldCallbackUtil_firePhantomShapeSet(hkWorld*, hkPhantom*);// @ 0x0109ee90

struct hkPhantom : hkReferencedObject {
    hkWorld* m_world;                       // +0x08
    uint32_t m_pad0c[4];                    // +0x0c
    hkShape* m_shape;                       // +0x1c (collidable.m_shape)
    uint32_t m_pad20;                       // +0x20
    hkMotionState* m_motionState;           // +0x24 (collidable.m_motion)
    uint32_t m_pad28[1];
    int32_t  m_ownerOffset;                 // +0x2c
    uint8_t  m_pad30[0x58 - 0x30];
    hkArray<void*> m_overlapListeners;      // +0x58
    hkArray<void*> m_phantomListeners;      // +0x64

    // @ 0x01082800  (hkWorldObject ctor, kind = 2 for phantoms)
    hkPhantom(hkShape* shape, int kind);
    // @ 0x010826e0  (finish-loaded ctor)
    hkPhantom(int finishLoaded);
    // @ 0x0108e680
    void updateBroadPhase(const hkAabb& aabb);
    // @ 0x0108e3e0
    void firePhantomShapeSet();
    // @ 0x0108c0b0 / 0x0108c100
    int fireCollidableAdded(const void* collidable);
    void fireCollidableRemoved(const void* collidable, bool);
    // @ 0x0108e4e0
    void calcContentStatistics(hkStatisticsCollector* c) const;
};

struct hkShapePhantom : hkPhantom {
    hkTransform m_transform;                // +0x70 (rotation 0x30 + translation at +0xa0)

    hkShapePhantom(hkShape* shape, const hkTransform& t);
    void setTransform(const hkTransform& t);
    void setPosition(const hkVector4& p, float extraTolerance);
    virtual void calcAabb(hkAabb& out);
    virtual int setShape(hkShape* shape);
};

// @ 0x0108dd40
hkShapePhantom::hkShapePhantom(hkShape* shape, const hkTransform& t)
    : hkPhantom(shape, 2)
{
    m_overlapListeners.m_data = 0; m_overlapListeners.m_size = 0; m_overlapListeners.m_capacityAndFlags = (int32_t)0x80000000;
    m_phantomListeners.m_data = 0; m_phantomListeners.m_size = 0; m_phantomListeners.m_capacityAndFlags = (int32_t)0x80000000;
    m_ownerOffset = -28;                    // collidable.m_ownerOffset = (this - &collidable)
    m_motionState = (hkMotionState*)&m_transform;
    ((hkMotionState*)&m_transform)->setTransform(t);
}

// @ 0x0108db50
void hkShapePhantom::setTransform(const hkTransform& t)
{
    ((hkMotionState*)&m_transform)->setTransform(t);
    if (m_world) {
        hkAabb aabb;
        // X87-PRECISION: fld tolerance (float); fmul 0.5f; fstp float arg
        float halfTol = m_world->m_collisionInput->m_tolerance * 0.5f;   // 0.5f @ 0x01471064
        m_shape->getAabb(t, halfTol, aabb);
        updateBroadPhase(aabb);
    }
}

// @ 0x0108dbb0
void hkShapePhantom::setPosition(const hkVector4& p, float extraTolerance)
{
    m_transform.m_translation = p;          // 4 dword copies to +0xa0
    if (m_world) {
        hkAabb aabb;
        // X87-PRECISION: (tolerance*0.5f) + extra stays in extended precision until fstp to the float arg.
        float tol = (float)((double)m_world->m_collisionInput->m_tolerance * 0.5 + (double)extraTolerance);
        m_shape->getAabb(m_transform, tol, aabb);
        updateBroadPhase(aabb);
    }
}

// @ 0x0108dc20
void hkShapePhantom::calcAabb(hkAabb& out)
{
    float halfTol = m_world->m_collisionInput->m_tolerance * 0.5f;       // 0.5f @ 0x01471064
    m_shape->getAabb(m_transform, halfTol, out);
}

// @ 0x0108dc50
int hkShapePhantom::setShape(hkShape* shape)
{
    hkWorld* world = m_world;
    if (world) {
        if (world->m_criticalOperationsLockCount != 0) {
            hkWorldOperationQueued op;
            op.m_type = 5;                  // SET_PHANTOM_SHAPE
            op.m_object = this;
            op.m_arg = shape;
            world->queueOperation(op);
            return 0;                       // result: postponed
        }
        world->m_criticalOperationsLockCount++;
        hkWorldOperationUtil_removePhantomBP(m_world, this);
    }

    hkShape* old = m_shape;
    if (old && old->m_memSizeAndFlags != 0) {
        if (--old->m_referenceCount == 0)
            delete old;                     // virtual deleting dtor (slot 0, flag 1)
    }
    m_shape = shape;
    if (shape->m_memSizeAndFlags != 0) shape->m_referenceCount++;

    if (m_world) hkWorldCallbackUtil_firePhantomShapeSet(m_world, this);
    firePhantomShapeSet();

    if (m_world) {
        hkWorldOperationUtil_addPhantomBP(m_world, this);
        hkWorld* w = m_world;
        if (--w->m_criticalOperationsLockCount == 0 && w->m_pendingOperationsCount != 0
            && w->m_pendingOperationsInProgress == 0)
            w->attemptToExecutePendingOperations();
    }
    return 1;                               // result: done
}

struct hkAabbPhantom : hkPhantom {
    hkAabb m_aabb;                          // +0x70
    hkArray<void*> m_overlappingCollidables;   // +0x90

    hkAabbPhantom(const hkAabb& aabb, uint32_t collisionFilterInfo);
    hkAabbPhantom(int finishLoaded);
    virtual void calcAabb(hkAabb& out);
    void setAabb(const hkAabb& aabb);
    virtual bool isOverlappingCollidableAdded(const void* c);
    virtual void removeOverlappingCollidable(void* c);
    virtual void addOverlappingCollidable(void* c);
    virtual void calcStatistics(hkStatisticsCollector* c) const;
};

// @ 0x0108dd90
void hkAabbPhantom::calcAabb(hkAabb& out) { out = m_aabb; }

// @ 0x0108dde0
void hkAabbPhantom::setAabb(const hkAabb& aabb)
{
    m_aabb = aabb;
    updateBroadPhase(m_aabb);   // tail call with the phantom's own copy
}

// @ 0x0108de30
bool hkAabbPhantom::isOverlappingCollidableAdded(const void* c)
{
    for (int i = 0; i < m_overlappingCollidables.m_size; ++i)
        if (m_overlappingCollidables.m_data[i] == c) return true;
    return false;
}

// @ 0x0108de70
void hkAabbPhantom::removeOverlappingCollidable(void* c)
{
    int idx = -1;
    int n = m_overlappingCollidables.m_size;
    for (int i = 0; i < n; ++i) {
        if (m_overlappingCollidables.m_data[i] == c) { idx = i; break; }
    }
    fireCollidableRemoved(c, idx >= 0);
    if (idx >= 0) {
        // remove-swap-last
        int last = --m_overlappingCollidables.m_size;
        m_overlappingCollidables.m_data[idx] = m_overlappingCollidables.m_data[last];
    }
}

// @ 0x0108dee0
void hkAabbPhantom::addOverlappingCollidable(void* c)
{
    if (fireCollidableAdded(c) == 0) {      // hkCollidableAccept: 0 = accept
        if (m_overlappingCollidables.m_size == (m_overlappingCollidables.m_capacityAndFlags & 0x3fffffff))
            hkArrayUtil_reserveMore(&m_overlappingCollidables, 4);
        m_overlappingCollidables.m_data[m_overlappingCollidables.m_size] = c;
        m_overlappingCollidables.m_size++;
    }
}

// @ 0x0108df30
void hkAabbPhantom::calcStatistics(hkStatisticsCollector* c) const
{
    c->beginObject("AabbPhantom", 2, this);
    calcContentStatistics(c);
    if (m_overlappingCollidables.m_capacityAndFlags >= 0)
        c->addArray("OvrlpCollPtr", 8, m_overlappingCollidables.m_data,
                    m_overlappingCollidables.m_size << 2,
                    (m_overlappingCollidables.m_capacityAndFlags & 0x3fffffff) << 2);
    c->endObject();
}

// @ 0x0108df90
// finish-loaded style constructor taking the object as an argument (null tolerant)
void hkAabbPhantom_constructFinishLoaded(hkAabbPhantom* self)
{
    if (self) new (self) hkAabbPhantom(1);
}
hkAabbPhantom::hkAabbPhantom(int finishLoaded) : hkPhantom(1)
{
    m_overlapListeners.m_data = 0; m_overlapListeners.m_size = 0; m_overlapListeners.m_capacityAndFlags = (int32_t)0x80000000;
    m_phantomListeners.m_data = 0; m_phantomListeners.m_size = 0; m_phantomListeners.m_capacityAndFlags = (int32_t)0x80000000;
    m_overlappingCollidables.m_data = 0; m_overlappingCollidables.m_size = 0;
    m_overlappingCollidables.m_capacityAndFlags = (int32_t)0x80000000;
}

// @ 0x0108dfe0
hkAabbPhantom::hkAabbPhantom(const hkAabb& aabb, uint32_t collisionFilterInfo) : hkPhantom((hkShape*)0, 2)
{
    m_overlapListeners.m_data = 0; m_overlapListeners.m_size = 0; m_overlapListeners.m_capacityAndFlags = (int32_t)0x80000000;
    m_phantomListeners.m_data = 0; m_phantomListeners.m_size = 0; m_phantomListeners.m_capacityAndFlags = (int32_t)0x80000000;
    m_ownerOffset = -28;
    m_overlappingCollidables.m_data = 0; m_overlappingCollidables.m_size = 0;
    m_overlappingCollidables.m_capacityAndFlags = (int32_t)0x80000000;
    m_aabb = aabb;
    ((uint32_t*)this)[0x0e] = collisionFilterInfo;      // +0x38 collidable collision filter info
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
