// Slice s01103c40: hkAgent1nMachine_Weld (Havok 3.1 hkAgent1nMachine.cpp).
// Flags: /vc71 /O2 /MD /Gy /TP (VC .NET 2003, x87, no EH).  Stub layouts follow match/slices/s011048d0 (same TU).
#include "types.h"

typedef float hkReal;
typedef uint32_t hkShapeKey;
typedef uint16_t hkContactPointId;

class hkVector4 { public: float x, y, z, w; };
class hkTransform { public:
    hkVector4 m_rot[3];
    hkVector4 m_trans;
};
class hkMotionState { public: hkTransform m_transform; };

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

class hkCdBody { public:
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
class hkCollisionDispatcher;
struct hkCollisionInput {
    hkCollisionDispatcher* m_dispatcher;      // +0
    uint32_t m_pad[9];
    hkCollisionAgentConfig* m_config;         // +0x28
};

class hkContactPoint { public:
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
class hkCollisionDispatcher { public:
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

// ---------------------------------------------------------------------------------------------------
// hkAgent1nMachine sector rebuild / destroy helpers (hkArray<hkAgent1nSector*>)
// ---------------------------------------------------------------------------------------------------
class hkString { public: static void __cdecl memCpy(void* dst, const void* src, int n); };   // 0x0107f440

struct hkAgent1nSector {
    uint32_t m_bytesAllocated;                // +0
    uint32_t m_pad[3];
    uint8_t m_data[512 - 16];                 // +0x10
};
struct hkAgent1nTrack {
    hkAgent1nSector** m_sectorsData;          // +0   hkArray<hkAgent1nSector*>
    int m_sectorsSize;                        // +4
    int m_sectorsCapacityAndFlags;            // +8
};
struct hkArrayUtil { static void __cdecl _reserveExactly(void* array, int numElem, int elemSize); };   // 0x0107f4a0

class hkMemory { public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void* allocateChunkFromSizeClass(int sizeIndex, int memClass);           // +0x18
    virtual void deallocateChunkToSizeClass(void* p, int sizeIndex, int memClass);  // +0x1c
    static hkMemory* s_instance;                                                      // 0x016e4178
};
class hkThreadMemory { public:
    uint8_t m_pad0[0x34];
    int m_maxNumElemsOnFreeList;              // +0x34
    uint8_t m_pad1[0x68 - 0x38];
    void** m_freeListHead;                    // +0x68 (size class 12)
    uint8_t m_pad2[0xac - 0x6c];
    int m_numFreeElements;                    // +0xac
    void deallocateChunk(void* p, int size, int memClass);   // 0x0107db10
};
extern unsigned long g_hkThreadMemoryTls;     // 0x016e4174

inline hkAgent1nSector* allocateSectorSafe()
{
    hkThreadMemory* mem = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
    void** p = mem->m_freeListHead;
    if (p == 0) {
        p = (void**)hkMemory::s_instance->allocateChunkFromSizeClass(0xc, 0x1c);
    } else {
        mem->m_numFreeElements--;
        mem->m_freeListHead = (void**)*p;
    }
    if (p != 0)
        *(uint32_t*)p = 0;
    return (hkAgent1nSector*)p;
}

inline void deallocateSector(hkAgent1nSector* sector)
{
    hkThreadMemory* mem = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
    if (mem->m_numFreeElements < mem->m_maxNumElemsOnFreeList) {
        mem->m_numFreeElements++;
        *(void***)sector = mem->m_freeListHead;
        mem->m_freeListHead = (void**)sector;
    } else {
        hkMemory::s_instance->deallocateChunkToSizeClass(sector, 0xc, 0x1c);
    }
}

struct hkAgent1nMachine_VisitorInput {
    const void* m_bodyA;                      // +0x00
    const void* m_collectionBodyB;            // +0x04
    const void* m_containerShapeB;            // +0x08
    const void* m_input;                      // +0x0c
    void* m_constraintOwner;                  // +0x10
    void* m_unused;                           // +0x14
};
typedef void* (__cdecl *hkAgent1nVisitorFunc)(hkAgent1nMachine_VisitorInput& vin,
                                              hkAgent1nMachineEntry* entry, void* agentData);

typedef void (__cdecl *hkAgent3DestroyFunc)(hkAgent1nMachineEntry* entry, void* agentData,
                                            void* constraintOwner);
struct hkAgent3FuncsExact {                    // 0x34 bytes (table base 0x1698)
    hkAgent3DestroyFunc m_destroyFunc;        // +0x00
    void* m_other0[5];                        // +0x04
    void* m_invalidateTimFunc;                // +0x18
    void* m_warpTimeFunc;                     // +0x1c
    void* m_other1[5];                        // +0x20
};
class hkCollisionDispatcherExact {
public:
    uint8_t m_pad[0x1698];
    hkAgent3FuncsExact m_agent3Func[1];       // +0x1698, indexed by agent type
};

// @ 0x01104420  hkAgent1nMachine_UpdateShapeCollectionFilter walker
extern "C" void __cdecl hkAgent1nMachine_UpdateShapeCollectionFilterWalker(
    hkAgent1nTrack* track, const hkAgent1nMachine_VisitorInput* visitorInput, hkAgent1nVisitorFunc visitor)
{
    hkAgent1nSector* sector = track->m_sectorsData[0];
    uint8_t* end = (uint8_t*)sector + sector->m_bytesAllocated + 0x10;
    uint8_t* p = (uint8_t*)sector + 0x10;
    int sectorIndex = 1;
    int outCount = 0;
    hkAgent1nSector* prevSector = 0;

    hkAgent1nSector* newSector = allocateSectorSafe();
    uint8_t* q = (uint8_t*)newSector + 0x10;

    for (;;) {
        unsigned int size = p[3];
        hkString::memCpy(q, p, (int)size);
        p += size;

        hkAgent1nMachine_VisitorInput vin = *visitorInput;
        int dataOffset = 0x10;
        switch (q[0]) {
        case 1:
            q += 0x10;
            break;
        case 4:
        case 5:
            dataOffset = 0x20;
            // fall through
        case 2:
        case 3:
        case 6:
            q = (uint8_t*)visitor(vin, (hkAgent1nMachineEntry*)q, q + dataOffset);
            break;
        }

        if (p == end) {
            if (prevSector != 0)
                deallocateSector(prevSector);
            prevSector = sector;
            if (track->m_sectorsSize <= sectorIndex) {
                // last source sector: publish the current write sector
                newSector->m_bytesAllocated = (uint32_t)(q - 0x10 - (uint8_t*)newSector);
                int newSize = outCount + 1;
                int cap = track->m_sectorsCapacityAndFlags & 0x3fffffff;
                if (cap < newSize) {
                    int c2 = cap + cap;
                    hkArrayUtil::_reserveExactly(track, (newSize < c2) ? c2 : newSize, 4);
                }
                track->m_sectorsSize = newSize;
                track->m_sectorsData[outCount] = newSector;
                if (sector != 0)
                    deallocateSector(sector);
                return;
            }
            sector = track->m_sectorsData[sectorIndex];
            p = (uint8_t*)sector + 0x10;
            end = (uint8_t*)sector + sector->m_bytesAllocated + 0x10;
            sectorIndex++;
        }

        hkAgent1nSector* savedPrev = prevSector;
        int used = (int)(q - 0x10 - (uint8_t*)newSector);
        if (0x1a0 < (int)(p[3] + used)) {
            // the write sector cannot take the next entry: seal it
            newSector->m_bytesAllocated = (uint32_t)used;
            if (sectorIndex <= outCount) {
                // the writer caught up with the reader: make room in the track array
                int newSize = track->m_sectorsSize + 1;
                int numToMove = track->m_sectorsSize - sectorIndex;
                int cap = track->m_sectorsCapacityAndFlags & 0x3fffffff;
                if (cap < newSize) {
                    int c2 = cap + cap;
                    hkArrayUtil::_reserveExactly(track, (newSize < c2) ? c2 : newSize, 4);
                }
                hkAgent1nSector** src = &track->m_sectorsData[sectorIndex];
                hkAgent1nSector** dst = src + 1;
                for (int i = numToMove - 1; i >= 0; i--)
                    dst[i] = src[i];
                sectorIndex++;
                track->m_sectorsSize = newSize;
            }
            track->m_sectorsData[outCount] = newSector;
            outCount++;

            newSector = savedPrev;
            if (savedPrev == 0) {
                newSector = allocateSectorSafe();
                q = (uint8_t*)newSector + 0x10;
            } else {
                prevSector = 0;
                q = (uint8_t*)savedPrev + 0x10;
            }
        }
    }
}

// @ 0x01104760  hkAgent1nMachine_Destroy walker
extern "C" void __cdecl hkAgent1nMachine_DestroyWalker(
    hkAgent1nTrack* track, const hkCollisionDispatcherExact* disp, void* constraintOwner)
{
    hkAgent1nSector* sector = track->m_sectorsData[0];
    uint8_t* end = (uint8_t*)sector + sector->m_bytesAllocated + 0x10;
    uint8_t* p = (uint8_t*)sector + 0x10;
    int sectorIndex = 1;

    for (;;) {
        hkAgent1nMachineEntry* entry = (hkAgent1nMachineEntry*)p;
        switch (entry->m_streamCommand) {
        case 2:
        case 3:
        case 6: {
            void* agentData = p + 0x10;
            p += entry->m_size;
            disp->m_agent3Func[entry->m_agentType].m_destroyFunc(entry, agentData, constraintOwner);
            break;
        }

        case 4:
        case 5: {
            void* agentData = p + 0x20;
            p += entry->m_size;
            disp->m_agent3Func[entry->m_agentType].m_destroyFunc(entry, agentData, constraintOwner);
            break;
        }

        case 0:
            p += entry->m_size;
            break;

        case 1:
            deallocateSector(sector);
            if (track->m_sectorsCapacityAndFlags >= 0) {
                hkThreadMemory* mem = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
                mem->deallocateChunk(track->m_sectorsData,
                                     (track->m_sectorsCapacityAndFlags & 0x3fffffff) << 2, 0x14);
            }
            track->m_sectorsData = 0;
            track->m_sectorsSize = 0;
            track->m_sectorsCapacityAndFlags =
                (track->m_sectorsCapacityAndFlags & 0xc0000000) | 0x80000000;
            return;
        }

        if (p < end)
            continue;
        deallocateSector(sector);
        sector = track->m_sectorsData[sectorIndex];
        sectorIndex++;
        end = (uint8_t*)sector + sector->m_bytesAllocated + 0x10;
        p = (uint8_t*)sector + 0x10;
    }
}
