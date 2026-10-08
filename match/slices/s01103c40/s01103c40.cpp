// Slice s01103c40: hkAgent1nMachine_Weld (Havok 3.1 hkAgent1nMachine.cpp).
// Flags: /vc71 /O2 /MD /Gy /TP (VC .NET 2003, x87, no EH).  Stub layouts follow match/slices/s011048d0 (same TU).
#include "types.h"

typedef float hkReal;
typedef uint32_t hkShapeKey;
typedef uint16_t hkContactPointId;

struct hkVector4 { float x, y, z, w; };
struct hkTransform {
    hkVector4 m_rot[3];
    hkVector4 m_trans;
};
struct hkMotionState { hkTransform m_transform; };

class hkShape {
public:
    virtual void hkShape_v0();
    virtual void hkShape_v1();
    virtual int getType() const;                                             // +0x08
};
class hkConvexShape : public hkShape {
public:
    uint32_t m_memSizeAndRefs;                // +4
    uint32_t m_userData;                      // +8
    hkReal m_radius;                          // +0xc
};

struct hkCdBody {
    const hkShape* m_shape;                   // +0
    hkShapeKey m_shapeKey;                    // +4
    const hkMotionState* m_motion;            // +8
    const hkCdBody* m_parent;                 // +0xc
    hkCdBody(const hkCdBody* parent) { m_parent = parent; m_motion = parent->m_motion; }
    hkCdBody() {}
};

struct __declspec(align(16)) hkShapeBuffer { char m_buf[512]; };

class hkShapeCollection : public hkShape {
public:
    virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8(); virtual void v9();
    virtual const hkShape* getChildShape(hkShapeKey key, hkShapeBuffer& buffer) const;   // +0x28
};

struct hkCollisionAgentConfig {
    hkReal m_weldFactor;                      // +0 (scaled by 0.05 for point-vs-edge welding)
};
struct hkCollisionDispatcher;
struct hkCollisionInput {
    hkCollisionDispatcher* m_dispatcher;      // +0
    uint32_t m_pad[9];
    hkCollisionAgentConfig* m_config;         // +0x28
};

struct hkContactPoint {
    hkVector4 m_position;
    hkVector4 m_separatingNormal;             // w = distance
};
struct hkProcessCdPoint {                     // 0x30 bytes
    hkContactPoint m_contact;
    hkContactPointId m_contactPointId;        // +0x20
    uint8_t m_pad[14];
};

struct hkAgent1nMachineEntry {
    uint8_t m_streamCommand;
    uint8_t m_agentType;
    uint8_t m_numContactPoints;
    uint8_t m_size;
    uint32_t m_pad4;
    hkShapeKey m_shapeKey;                    // +8
};

typedef void (__cdecl *hkAgent3EntryFunc)(hkAgent1nMachineEntry* entry, void* agentData, hkContactPointId id);
struct hkAgent3Funcs {                        // 0x34 bytes
    void* m_createFunc;                       // +0x00
    void* m_destroyFunc;                      // +0x04
    void* m_cleanupFunc;                      // +0x08
    hkAgent3EntryFunc m_removePointFunc;      // +0x0c
    hkAgent3EntryFunc m_commitPotentialFunc;  // +0x10
    hkAgent3EntryFunc m_createZombieFunc;     // +0x14
    void* m_other[6];
};
struct hkCollisionDispatcher {
    uint8_t m_pad0[0x10c];
    uint32_t m_shapeTypeFlags[(0x1694 - 0x10c) / 4];   // +0x10c, indexed by shape type; bit 1 = convex
    hkAgent3Funcs m_agent3Func[1];            // +0x1694
};

class hkContactMgr {
public:
    virtual void v0();
    virtual void v1();
    virtual hkContactPointId addContactPoint(const hkCdBody& a, const hkCdBody& b, const hkCollisionInput& input,
                                             hkProcessCdPoint* cp);              // +8
    virtual void reserveContactPoints(int n);                                    // +0xc
    virtual void removeContactPoint(hkContactPointId id);                        // +0x10
};

struct hkAgent3Input {
    const hkCdBody* m_bodyA;                  // +0
    const hkCdBody* m_bodyB;                  // +4
    const hkCollisionInput* m_input;          // +8
    hkContactMgr* m_contactMgr;               // +0xc
    hkTransform m_aTb;                        // +0x10
};

struct hkContactRef { hkProcessCdPoint* m_contactPoint; hkAgent1nMachineEntry* m_agentEntry; void* m_agentData; };
struct hkPotentialInfo {
    hkContactRef* m_firstFreePotentialContact;            // +0
    hkProcessCdPoint** m_firstFreeRepresentativeContact;  // +4
    hkProcessCdPoint* m_representativeContacts[256];      // +8
    hkContactRef m_potentialContacts[256];                // +0x408
};
struct hkProcessCollisionOutput {
    hkProcessCdPoint* m_firstFreeContactPoint;            // +0
    uint8_t m_pad1[0x3040 - 4];
    hkPotentialInfo* m_potentialContacts;                 // +0x3040
};

enum hkResult { HK_SUCCESS, HK_FAILURE };
hkResult __cdecl hkCalcMultiPenetrationDepth(const hkTransform& transA, const hkConvexShape* shapeA,
                                             const hkConvexShape** shapesB, int numShapesB,
                                             const hkTransform& aTb, hkContactPoint** contactsOut);   // 0x01121f30

extern unsigned long g_hkMonitorStreamEndTls; // 0x016e42a8
extern unsigned long g_hkMonitorStreamTls;    // 0x016e42a4
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long index, void* value);

struct hkMonitorTimerCommand { const char* m_commandAndMonitor; uint32_t m_time0; uint32_t m_time1; };

inline void hkMonitorTimer(const char* command)
{
    char* end = (char*)TlsGetValue(g_hkMonitorStreamEndTls);
    if ((char*)TlsGetValue(g_hkMonitorStreamTls) < end) {
        hkMonitorTimerCommand* h = (hkMonitorTimerCommand*)TlsGetValue(g_hkMonitorStreamTls);
        h->m_commandAndMonitor = command;
        uint32_t ticks;
        __asm {
            rdtsc
            mov ticks, eax
        }
        h->m_time0 = ticks;
        TlsSetValue(g_hkMonitorStreamTls, h + 1);
    }
}

// @ 0x01103c40
extern "C" void __cdecl hkAgent1nMachine_Weld(hkAgent3Input& input, const hkShapeCollection* collection,
                                              hkProcessCollisionOutput& output)
{
    hkPotentialInfo* pi = output.m_potentialContacts;
    const hkConvexShape* shapeA = (const hkConvexShape*)input.m_bodyA->m_shape;

    hkShapeBuffer bufB;
    hkContactPointId contactIds[256];       // per potential contact: id returned by the contact manager
    hkShapeBuffer bufA;
    uint16_t conflicts[256];                // indices of potentials that conflict with a representative
    int numConflicts = 0;

    // Phase 1: add every potential contact to the manager unless it is covered by a representative.
    int i = 0;
    hkContactRef* p = pi->m_potentialContacts;
    if (p < pi->m_firstFreePotentialContact) {
        do {
            hkProcessCdPoint* cp = p->m_contactPoint;
            contactIds[i] = 0xffff;
            bool conflict = false;
            for (hkProcessCdPoint** rep = pi->m_representativeContacts; rep < pi->m_firstFreeRepresentativeContact; ++rep) {
                hkProcessCdPoint* other = *rep;
                if (cp == other) continue;
                hkReal radius = shapeA->m_radius;
                hkCollisionAgentConfig* config = input.m_input->m_config;
                hkReal dx = other->m_contact.m_position.x - cp->m_contact.m_position.x;
                hkReal dy = other->m_contact.m_position.y - cp->m_contact.m_position.y;
                hkReal dz = other->m_contact.m_position.z - cp->m_contact.m_position.z;
                const hkVector4& cn = cp->m_contact.m_separatingNormal;
                const hkVector4& on = other->m_contact.m_separatingNormal;
                hkReal dotDCn = dz * cn.z + dy * cn.y + dx * cn.x;
                hkReal dotDOn = dz * on.z + dy * on.y + dx * on.x;
                hkReal dotNN = on.z * cn.z + on.y * cn.y + on.x * cn.x;
                hkReal e = (dotNN - 1.0f) * radius;
                hkReal f = -dotDOn + e;
                hkReal g = dotDCn + e;
                if (f > radius) continue;
                if (dotNN > 0.9999f && other->m_contactPointId == 0xffff) continue;
                if (other->m_contactPointId == 0xffff
                    && dotNN < 0.8f
                    && g + f < 0.1f
                    && cn.w + on.w < radius * -2.0f) {
                    conflict = true;
                    continue;
                }
                hkReal tol = 0.0f;
                if (other->m_contactPointId != 0xffff) tol = config->m_weldFactor * 0.05f;
                if (cn.w <= on.w - tol) continue;
                goto skipPotential;
            }
            if (conflict) {
                conflicts[numConflicts] = (uint16_t)i;
                numConflicts++;
            }
            {
                hkShapeKey key = p->m_agentEntry->m_shapeKey;
                const hkShape* child = collection->getChildShape(key, bufA);
                hkCdBody childBody(input.m_bodyB);
                childBody.m_shape = child;
                childBody.m_shapeKey = key;
                hkContactPointId id = input.m_contactMgr->addContactPoint(*input.m_bodyA, childBody, *input.m_input, p->m_contactPoint);
                contactIds[i] = id;
                if (id != 0xffff) input.m_contactMgr->reserveContactPoints(-1);
            }
        skipPotential:
            i++;
            p++;
        } while (p < pi->m_firstFreePotentialContact);
    }

    // Phase 2: every conflicting potential becomes a zombie.
    hkCollisionDispatcher* dispatcher = input.m_input->m_dispatcher;
    for (int k = 0; k < numConflicts; k++) {
        hkContactRef& r = pi->m_potentialContacts[conflicts[k]];
        dispatcher->m_agent3Func[r.m_agentEntry->m_agentType].m_createZombieFunc(r.m_agentEntry, r.m_agentData, 0xffff);
    }

    // Phase 3: merge the two most opposed conflicting contacts until at most one is left.
    while (numConflicts >= 2) {
        hkMonitorTimer("TtConflicts");
        hkReal best = 2.0f;
        int bestI = 0;
        int bestJ = 1;
        for (int i = 0; i < numConflicts; i++) {
            const hkReal* n1 = &pi->m_potentialContacts[conflicts[i]].m_contactPoint->m_contact.m_separatingNormal.x;
            for (int j = i + 1; j < numConflicts; j++) {
                const hkReal* n2 = &pi->m_potentialContacts[conflicts[j]].m_contactPoint->m_contact.m_separatingNormal.x;
                hkReal d = n2[2] * n1[2] + n2[1] * n1[1] + n2[0] * n1[0];
                if (d < best) { bestI = i; best = d; bestJ = j; }
            }
        }
        uint16_t* pa = &conflicts[bestI];
        uint16_t* pb = &conflicts[bestJ];
        hkContactRef& ra = pi->m_potentialContacts[*pa];
        hkContactRef& rb = pi->m_potentialContacts[*pb];
        hkAgent1nMachineEntry* entryA = ra.m_agentEntry;
        hkAgent1nMachineEntry* entryB = rb.m_agentEntry;

        const hkConvexShape* bodyShape = (const hkConvexShape*)input.m_bodyA->m_shape;
        const hkCollisionDispatcher* disp = input.m_input->m_dispatcher;
        if (!((disp->m_shapeTypeFlags[bodyShape->getType()] >> 1) & 1)) break;
        const hkShape* sA = collection->getChildShape(entryA->m_shapeKey, bufA);
        if (!((disp->m_shapeTypeFlags[sA->getType()] >> 1) & 1)) break;
        const hkShape* sB = collection->getChildShape(entryB->m_shapeKey, bufB);
        if (!((disp->m_shapeTypeFlags[sB->getType()] >> 1) & 1)) break;

        const hkConvexShape* shapes[2];
        shapes[0] = (const hkConvexShape*)sA;
        shapes[1] = (const hkConvexShape*)sB;
        hkContactPoint* contacts[2];
        contacts[0] = &ra.m_contactPoint->m_contact;
        contacts[1] = &rb.m_contactPoint->m_contact;
        hkCalcMultiPenetrationDepth(input.m_bodyA->m_motion->m_transform, bodyShape, shapes, 2, input.m_aTb, contacts);

        *pb = conflicts[numConflicts - 1];
        *pa = conflicts[numConflicts - 2];
        numConflicts -= 2;
        hkMonitorTimer("Et");
    }

    // Phase 4: a lone remaining conflict keeps nothing in the manager.
    if (numConflicts != 0) {
        hkContactPointId* pid = &contactIds[conflicts[0]];
        hkContactPointId id = *pid;
        if (id != 0xffff) {
            input.m_contactMgr->removeContactPoint(id);
            *pid = 0xffff;
            input.m_contactMgr->reserveContactPoints(1);
        }
    }

    // Phase 5: commit the accepted potentials, drop and swap-remove the rejected ones (back to front).
    const hkCollisionDispatcher* disp2 = input.m_input->m_dispatcher;
    for (int k = (int)(pi->m_firstFreePotentialContact - pi->m_potentialContacts) - 1; k >= 0; k--) {
        hkContactRef* r = &pi->m_potentialContacts[k];
        hkContactPointId id = contactIds[k];
        if (id == 0xffff) {
            input.m_contactMgr->reserveContactPoints(-1);
            disp2->m_agent3Func[r->m_agentEntry->m_agentType].m_removePointFunc(r->m_agentEntry, r->m_agentData, 0xffff);
            output.m_firstFreeContactPoint--;
            *r->m_contactPoint = *output.m_firstFreeContactPoint;
        } else {
            disp2->m_agent3Func[r->m_agentEntry->m_agentType].m_commitPotentialFunc(r->m_agentEntry, r->m_agentData, id);
            r->m_contactPoint->m_contactPointId = id;
        }
    }
}
