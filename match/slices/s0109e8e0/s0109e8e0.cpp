// Havok 3.1.0 (statically linked, ~2005 MSVC build): hkWorldCallbackUtil / hkEntityCallbackUtil.
// Every function iterates a listener array BACKWARDS, calls one virtual slot, and then removes
// the entries that listeners nulled out while being called (ordered removal). No float math.
//
// Layouts are the retail 32-bit ones: listener arrays are hkArray<T*> {data, size, capacityAndFlags}
// at the offsets noted in hkWorld / hkEntity below.
#include "types.h"

#ifndef _WIN64
#define HK_OFFSET_CHECK(name, cond) typedef char name[(cond) ? 1 : -1]
#else
#define HK_OFFSET_CHECK(name, cond)
#endif

template <typename T> struct hkArray { T* m_data; int32_t m_size; int32_t m_capacityAndFlags; };

// Remove every null entry from a listener array, keeping order; iterates from the back, exactly
// as the inlined hkArray::removeAtAndCopy sequence does (size is reloaded in the copy loop).
template <typename T>
static inline void hkRemoveNullListeners(hkArray<T*>& a)
{
    for (int i = a.m_size - 1; i >= 0; --i) {
        if (a.m_data[i] == 0) {
            a.m_size = a.m_size - 1;
            for (int j = i; j < a.m_size; ++j)
                a.m_data[j] = a.m_data[j + 1];
        }
    }
}

struct hkStepInfo;
struct hkAction;
struct hkEntity;
struct hkPhantom;
struct hkConstraintInstance;
struct hkSimulationIsland;
struct hkWorld;
struct hkContactPointAddedEvent;
struct hkContactPointConfirmedEvent;
struct hkContactPointRemovedEvent;
struct hkContactProcessEvent;

// ---- listener interfaces (virtual slot order = vtable order in the binary) --------------
struct hkActionListener {
    virtual void vslot0();
    virtual void actionAddedCallback(hkAction* a);                      // +4
    virtual void actionRemovedCallback(hkAction* a);                    // +8
};
struct hkWorldEntityListener {
    virtual void vslot0();
    virtual void entityAddedCallback(hkEntity* e);                      // +4
    virtual void entityRemovedCallback(hkEntity* e);                    // +8
    virtual void entityShapeSetCallback(hkEntity* e);                   // +0xc
};
struct hkWorldPhantomListener {
    virtual void vslot0();
    virtual void phantomAddedCallback(hkPhantom* p);                    // +4
    virtual void phantomRemovedCallback(hkPhantom* p);                  // +8
    virtual void phantomShapeSetCallback(hkPhantom* p);                 // +0xc
};
struct hkWorldConstraintListener {
    virtual void vslot0();
    virtual void constraintAddedCallback(hkConstraintInstance* c);      // +4
    virtual void constraintRemovedCallback(hkConstraintInstance* c);    // +8
};
struct hkWorldDeletionListener {
    virtual void vslot0();
    virtual void worldDeletedCallback(hkWorld* w);                      // +4
};
struct hkIslandActivationListener {
    virtual void vslot0();
    virtual void islandActivatedCallback(hkSimulationIsland* i);        // +4
    virtual void islandDeactivatedCallback(hkSimulationIsland* i);      // +8
};
struct hkWorldPostSimulationListener {
    virtual void vslot0();
    virtual void postSimulationCallback(hkWorld* w, const hkStepInfo& s);   // +4
};
struct hkWorldPostIntegrateListener {
    virtual void vslot0();
    virtual void postIntegrateCallback(hkWorld* w, const hkStepInfo& s);    // +4
};
struct hkWorldPostCollideListener {
    virtual void vslot0();
    virtual void postCollideCallback(hkWorld* w, const hkStepInfo& s);      // +4
};
struct hkIslandPostIntegrateListener {
    virtual void vslot0();
    virtual void postIntegrateCallback(hkSimulationIsland* i, const hkStepInfo& s);   // +4
};
struct hkIslandPostCollideListener {
    virtual void vslot0();
    virtual void postCollideCallback(hkSimulationIsland* i, const hkStepInfo& s);     // +4
};
struct hkContactListener {                      // no destructor slot
    virtual void contactPointAddedCallback(hkContactPointAddedEvent& e);              // +0
    virtual void contactPointConfirmedCallback(hkContactPointConfirmedEvent& e);      // +4
    virtual void contactPointRemovedCallback(hkContactPointRemovedEvent& e);          // +8
    virtual void contactProcessCallback(hkContactProcessEvent& e);                    // +0xc
};
struct hkEntityListener {
    virtual void vslot0();
    virtual void vslot1();
    virtual void entityRemovedCallback(hkEntity* e);                    // +8
    virtual void vslot3();
};
struct hkEntityActivationListener {
    virtual void vslot0();
    virtual void entityDeactivatedCallback(hkEntity* e);                // +4
    virtual void entityActivatedCallback(hkEntity* e);                  // +8
};
struct hkEntityExtendedListener {
    virtual void vslot0(); virtual void vslot1(); virtual void vslot2(); virtual void vslot3(); virtual void vslot4();
    virtual void entityDeletedCallback(hkEntity* e);                    // +0x14
};
struct hkEntityOwnedObject {                                            // actions / constraints attached to an entity
    virtual void vslot0(); virtual void vslot1(); virtual void vslot2();
    virtual void entityRemovedCallback(hkEntity* e);                    // +0xc (removes itself from the entity's array)
};

// ---- events: only the fields these functions write --------------------------------------
struct hkContactPointAddedEvent       { void* m_bodyA; void* m_bodyB; int32_t m_type; void* m_callbackFiredFrom; /* +0xc */ };
struct hkContactPointConfirmedEvent   { void* m_bodyA; void* m_bodyB; void* m_callbackFiredFrom; /* +8 */ };
struct hkContactPointRemovedEvent     { uint16_t m_id; uint16_t m_pad; void* m_material; void* m_bodyA; void* m_bodyB; void* m_callbackFiredFrom; /* +0x10 */ };
struct hkContactProcessEvent          { void* m_bodyA; void* m_bodyB; void* m_callbackFiredFrom; /* +8 */ };

struct hkSimulationIsland {
    uint8_t m_pad[0x3c];
    hkEntity** m_entities;              // +0x3c
    int32_t m_numEntities;              // +0x40
};

struct hkEntity {
    uint8_t m_pad0[0x70];
    hkArray<hkEntityOwnedObject*> m_actions;                    // +0x70
    hkArray<hkEntityOwnedObject*> m_constraints;                // +0x7c (hkConstraintInstance*)
    uint8_t m_pad1[0x9c - 0x88];
    hkArray<hkContactListener*> m_contactListeners;             // +0x9c
    hkArray<hkEntityActivationListener*> m_activationListeners; // +0xa8
    hkArray<hkEntityListener*> m_entityListeners;               // +0xb4
    hkArray<hkEntityExtendedListener*> m_extendedListeners;     // +0xc0
};
HK_OFFSET_CHECK(chk_entity_end, sizeof(hkEntity) == 0xcc || sizeof(void*) != 4);

struct hkWorld {
    uint8_t m_pad0[0x88];
    int32_t m_pendingOperationsCount;                           // +0x88
    int32_t m_criticalOperationsLockCount;                      // +0x8c
    uint8_t m_pad1[4];
    uint8_t m_pendingOperationsInProgress;                      // +0x94
    uint8_t m_pad2[0xd8 - 0x95];
    hkArray<hkActionListener*>             m_actionListeners;                // +0xd8
    hkArray<hkWorldEntityListener*>        m_entityListeners;                // +0xe4
    hkArray<hkWorldPhantomListener*>       m_phantomListeners;               // +0xf0
    hkArray<hkWorldConstraintListener*>    m_constraintListeners;            // +0xfc
    hkArray<hkWorldDeletionListener*>      m_worldDeletionListeners;         // +0x108
    hkArray<hkIslandActivationListener*>   m_islandActivationListeners;      // +0x114
    hkArray<hkWorldPostSimulationListener*> m_postSimulationListeners;       // +0x120
    hkArray<hkWorldPostIntegrateListener*> m_postIntegrateListeners;         // +0x12c
    hkArray<hkWorldPostCollideListener*>   m_postCollideListeners;           // +0x138
    hkArray<hkIslandPostIntegrateListener*> m_islandPostIntegrateListeners;  // +0x144
    hkArray<hkIslandPostCollideListener*>  m_islandPostCollideListeners;     // +0x150
    hkArray<hkContactListener*>            m_contactListeners;               // +0x15c

    // @ 0x01082bf0 (ecx = world): run operations queued while the world was locked
    void attemptToExecutePendingOperations();
};
HK_OFFSET_CHECK(chk_world_contact, sizeof(hkWorld) == 0x168 || sizeof(void*) != 4);

struct hkEntityCallbackUtil {
    static void fireContactPointRemovedInternal(hkEntity* e, hkContactPointRemovedEvent& ev);
    static void fireContactProcessInternal(hkEntity* e, hkContactProcessEvent& ev);
    static void fireEntityRemoved(hkEntity* e);
};
struct hkWorldCallbackUtil {
    static void fireActionAdded(hkWorld* w, hkAction* a);
    static void fireActionRemoved(hkWorld* w, hkAction* a);
    static void fireEntityAdded(hkWorld* w, hkEntity* e);
    static void fireEntityRemoved(hkWorld* w, hkEntity* e);
    static void fireEntityShapeSet(hkWorld* w, hkEntity* e);
    static void firePhantomAdded(hkWorld* w, hkPhantom* p);
    static void firePhantomRemoved(hkWorld* w, hkPhantom* p);
    static void firePhantomShapeSet(hkWorld* w, hkPhantom* p);
    static void fireConstraintAdded(hkWorld* w, hkConstraintInstance* c);
    static void fireConstraintRemoved(hkWorld* w, hkConstraintInstance* c);
    static void fireContactPointAdded(hkWorld* w, hkContactPointAddedEvent& ev);
    static void fireContactPointConfirmed(hkWorld* w, hkContactPointConfirmedEvent& ev);
    static void fireContactPointRemoved(hkWorld* w, hkContactPointRemovedEvent& ev);
    static void fireContactProcess(hkWorld* w, hkContactProcessEvent& ev);
    static void fireWorldDeleted(hkWorld* w);
    static void fireIslandActivated(hkWorld* w, hkSimulationIsland* i);
    static void fireIslandDeactivated(hkWorld* w, hkSimulationIsland* i);
    static void firePostSimulationCallback(hkWorld* w, const hkStepInfo& s);
    static void firePostIntegrateCallback(hkWorld* w, const hkStepInfo& s);
    static void firePostCollideCallback(hkWorld* w, const hkStepInfo& s);
    static void fireIslandPostIntegrateCallback(hkWorld* w, hkSimulationIsland* i, const hkStepInfo& s);
    static void fireIslandPostCollideCallback(hkWorld* w, hkSimulationIsland* i, const hkStepInfo& s);
};

// Fire one callback on every listener in `arr` (back to front, skipping nulls), then drop
// the nulled entries. `Call` is a functor invoked as call(listener).
#define HK_FIRE_LISTENERS(ARR, CALL)                                  \
    do {                                                              \
        for (int i_ = (ARR).m_size - 1; i_ >= 0; --i_) {              \
            if ((ARR).m_data[i_] != 0) { CALL((ARR).m_data[i_]); }    \
        }                                                             \
        hkRemoveNullListeners(ARR);                                   \
    } while (0)

// @ 0x0109e8e0
void hkEntityCallbackUtil::fireContactPointRemovedInternal(hkEntity* e, hkContactPointRemovedEvent& ev)
{
    ev.m_callbackFiredFrom = e;
#define CALL(l) (l)->contactPointRemovedCallback(ev)
    HK_FIRE_LISTENERS(e->m_contactListeners, CALL);
#undef CALL
}

// @ 0x0109e970
void hkEntityCallbackUtil::fireContactProcessInternal(hkEntity* e, hkContactProcessEvent& ev)
{
    ev.m_callbackFiredFrom = e;
#define CALL(l) (l)->contactProcessCallback(ev)
    HK_FIRE_LISTENERS(e->m_contactListeners, CALL);
#undef CALL
}

// @ 0x0109ea00
void hkEntityCallbackUtil::fireEntityRemoved(hkEntity* e)
{
    for (int i = e->m_entityListeners.m_size - 1; i >= 0; --i) {
        if (e->m_entityListeners.m_data[i] != 0)
            e->m_entityListeners.m_data[i]->entityRemovedCallback(e);
    }
    // actions and constraints remove themselves from the arrays as a side effect
    while (e->m_actions.m_size != 0)
        e->m_actions.m_data[0]->entityRemovedCallback(e);
    while (e->m_constraints.m_size != 0)
        e->m_constraints.m_data[0]->entityRemovedCallback(e);
    for (int i = 0; i < e->m_extendedListeners.m_size; ++i) {
        if (e->m_extendedListeners.m_data[i] != 0)
            e->m_extendedListeners.m_data[i]->entityDeletedCallback(e);
    }
}

// @ 0x0109eaa0
void hkWorldCallbackUtil::fireActionAdded(hkWorld* w, hkAction* a)
{
#define CALL(l) (l)->actionAddedCallback(a)
    HK_FIRE_LISTENERS(w->m_actionListeners, CALL);
#undef CALL
}

// @ 0x0109eb30
void hkWorldCallbackUtil::fireActionRemoved(hkWorld* w, hkAction* a)
{
#define CALL(l) (l)->actionRemovedCallback(a)
    HK_FIRE_LISTENERS(w->m_actionListeners, CALL);
#undef CALL
}

// @ 0x0109ebc0
void hkWorldCallbackUtil::fireEntityAdded(hkWorld* w, hkEntity* e)
{
#define CALL(l) (l)->entityAddedCallback(e)
    HK_FIRE_LISTENERS(w->m_entityListeners, CALL);
#undef CALL
}

// @ 0x0109ec50
void hkWorldCallbackUtil::fireEntityRemoved(hkWorld* w, hkEntity* e)
{
#define CALL(l) (l)->entityRemovedCallback(e)
    HK_FIRE_LISTENERS(w->m_entityListeners, CALL);
#undef CALL
}

// @ 0x0109ece0
void hkWorldCallbackUtil::fireEntityShapeSet(hkWorld* w, hkEntity* e)
{
#define CALL(l) (l)->entityShapeSetCallback(e)
    HK_FIRE_LISTENERS(w->m_entityListeners, CALL);
#undef CALL
}

// @ 0x0109ed70
void hkWorldCallbackUtil::firePhantomAdded(hkWorld* w, hkPhantom* p)
{
#define CALL(l) (l)->phantomAddedCallback(p)
    HK_FIRE_LISTENERS(w->m_phantomListeners, CALL);
#undef CALL
}

// @ 0x0109ee00
void hkWorldCallbackUtil::firePhantomRemoved(hkWorld* w, hkPhantom* p)
{
#define CALL(l) (l)->phantomRemovedCallback(p)
    HK_FIRE_LISTENERS(w->m_phantomListeners, CALL);
#undef CALL
}

// @ 0x0109ee90
void hkWorldCallbackUtil::firePhantomShapeSet(hkWorld* w, hkPhantom* p)
{
#define CALL(l) (l)->phantomShapeSetCallback(p)
    HK_FIRE_LISTENERS(w->m_phantomListeners, CALL);
#undef CALL
}

// @ 0x0109ef20
void hkWorldCallbackUtil::fireConstraintAdded(hkWorld* w, hkConstraintInstance* c)
{
#define CALL(l) (l)->constraintAddedCallback(c)
    HK_FIRE_LISTENERS(w->m_constraintListeners, CALL);
#undef CALL
}

// @ 0x0109efb0
void hkWorldCallbackUtil::fireConstraintRemoved(hkWorld* w, hkConstraintInstance* c)
{
#define CALL(l) (l)->constraintRemovedCallback(c)
    HK_FIRE_LISTENERS(w->m_constraintListeners, CALL);
#undef CALL
}

// @ 0x0109f040 (name inferred from the sibling Confirmed/Removed/Process functions)
void hkWorldCallbackUtil::fireContactPointAdded(hkWorld* w, hkContactPointAddedEvent& ev)
{
    ev.m_callbackFiredFrom = 0;
#define CALL(l) (l)->contactPointAddedCallback(ev)
    HK_FIRE_LISTENERS(w->m_contactListeners, CALL);
#undef CALL
}

// @ 0x0109f0d0
void hkWorldCallbackUtil::fireContactPointConfirmed(hkWorld* w, hkContactPointConfirmedEvent& ev)
{
    ev.m_callbackFiredFrom = 0;
#define CALL(l) (l)->contactPointConfirmedCallback(ev)
    HK_FIRE_LISTENERS(w->m_contactListeners, CALL);
#undef CALL
}

// @ 0x0109f160
void hkWorldCallbackUtil::fireContactPointRemoved(hkWorld* w, hkContactPointRemovedEvent& ev)
{
    ev.m_callbackFiredFrom = 0;
#define CALL(l) (l)->contactPointRemovedCallback(ev)
    HK_FIRE_LISTENERS(w->m_contactListeners, CALL);
#undef CALL
}

// @ 0x0109f1f0
void hkWorldCallbackUtil::fireContactProcess(hkWorld* w, hkContactProcessEvent& ev)
{
    ev.m_callbackFiredFrom = 0;
#define CALL(l) (l)->contactProcessCallback(ev)
    HK_FIRE_LISTENERS(w->m_contactListeners, CALL);
#undef CALL
}

// @ 0x0109f280
void hkWorldCallbackUtil::fireWorldDeleted(hkWorld* w)
{
#define CALL(l) (l)->worldDeletedCallback(w)
    HK_FIRE_LISTENERS(w->m_worldDeletionListeners, CALL);
#undef CALL
}

// Run the queued world operations once the lock count drops back to zero.
static inline void hkWorld_unlockAndFlush(hkWorld* w)
{
    int n = w->m_criticalOperationsLockCount - 1;
    w->m_criticalOperationsLockCount = n;
    if (n == 0 && w->m_pendingOperationsCount != 0 && w->m_pendingOperationsInProgress == 0)
        w->attemptToExecutePendingOperations();
}

// @ 0x0109f300
void hkWorldCallbackUtil::fireIslandActivated(hkWorld* w, hkSimulationIsland* island)
{
    w->m_criticalOperationsLockCount++;
#define CALL(l) (l)->islandActivatedCallback(island)
    HK_FIRE_LISTENERS(w->m_islandActivationListeners, CALL);
#undef CALL
    for (int i = 0; i < island->m_numEntities; ++i) {
        hkEntity* e = island->m_entities[i];
#define CALL(l) (l)->entityActivatedCallback(island->m_entities[i])
        HK_FIRE_LISTENERS(e->m_activationListeners, CALL);
#undef CALL
    }
    hkWorld_unlockAndFlush(w);
}

// @ 0x0109f450
void hkWorldCallbackUtil::fireIslandDeactivated(hkWorld* w, hkSimulationIsland* island)
{
    w->m_criticalOperationsLockCount++;
#define CALL(l) (l)->islandDeactivatedCallback(island)
    HK_FIRE_LISTENERS(w->m_islandActivationListeners, CALL);
#undef CALL
    for (int i = 0; i < island->m_numEntities; ++i) {
        hkEntity* e = island->m_entities[i];
#define CALL(l) (l)->entityDeactivatedCallback(island->m_entities[i])
        HK_FIRE_LISTENERS(e->m_activationListeners, CALL);
#undef CALL
    }
    hkWorld_unlockAndFlush(w);
}

// @ 0x0109f5a0 (listener array at +0x120, between island activation and post-integrate)
void hkWorldCallbackUtil::firePostSimulationCallback(hkWorld* w, const hkStepInfo& s)
{
#define CALL(l) (l)->postSimulationCallback(w, s)
    HK_FIRE_LISTENERS(w->m_postSimulationListeners, CALL);
#undef CALL
}

// @ 0x0109f630
void hkWorldCallbackUtil::firePostIntegrateCallback(hkWorld* w, const hkStepInfo& s)
{
#define CALL(l) (l)->postIntegrateCallback(w, s)
    HK_FIRE_LISTENERS(w->m_postIntegrateListeners, CALL);
#undef CALL
}

// @ 0x0109f6c0
void hkWorldCallbackUtil::firePostCollideCallback(hkWorld* w, const hkStepInfo& s)
{
#define CALL(l) (l)->postCollideCallback(w, s)
    HK_FIRE_LISTENERS(w->m_postCollideListeners, CALL);
#undef CALL
}

// @ 0x0109f750
void hkWorldCallbackUtil::fireIslandPostIntegrateCallback(hkWorld* w, hkSimulationIsland* i, const hkStepInfo& s)
{
#define CALL(l) (l)->postIntegrateCallback(i, s)
    HK_FIRE_LISTENERS(w->m_islandPostIntegrateListeners, CALL);
#undef CALL
}

// @ 0x0109f7e0
void hkWorldCallbackUtil::fireIslandPostCollideCallback(hkWorld* w, hkSimulationIsland* i, const hkStepInfo& s)
{
#define CALL(l) (l)->postCollideCallback(i, s)
    HK_FIRE_LISTENERS(w->m_islandPostCollideListeners, CALL);
#undef CALL
}
