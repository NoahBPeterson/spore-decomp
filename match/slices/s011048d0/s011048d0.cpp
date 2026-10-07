// Havok 3.1.0 slice s011048d0: hkAgent1nMachine_Process (hkAgent1nMachine.cpp).
// Flags: /O2 /MD /Gy /TP (x87, no EH).  Struct stubs carry members at the offsets seen in the 32-bit binary;
// the layouts follow match/slices/s01102fc0 (same Havok TU: Create/Weld/InvalidateTim/WarpTime live there).
#include "types.h"
#include <new>

typedef float hkReal;
typedef float hkTime;
typedef uint32_t hkShapeKey;

struct __declspec(align(16)) hkVector4 { float x, y, z, w; };
struct __declspec(align(16)) hkTransform {
    hkVector4 m_rot[3];
    hkVector4 m_trans;
    void setInverse(const hkTransform& t);                                   // 0x01080e70
};

// Havok's bool wrapper: returned through a hidden pointer by virtual functions.
class hkBool {
public:
    hkBool() {}
    hkBool(bool b) { m_bool = (char)b; }
    operator bool() const { return m_bool != 0; }
    char m_bool;
};

struct hkString { static void __cdecl memCpy(void* dst, const void* src, int n); };   // 0x0107f440

struct hkMotionState;
class hkShape {
public:
    virtual void hkShape_v0();
    virtual void hkShape_v1();
    virtual int getType() const;                                             // +0x08
};

struct hkCdBody {
    const hkShape* m_shape;                   // +0
    hkShapeKey m_shapeKey;                    // +4
    const hkMotionState* m_motion;            // +8
    const hkCdBody* m_parent;                 // +0xc
    hkCdBody(const hkCdBody* parent) { m_parent = parent; m_motion = parent->m_motion; }
    hkCdBody() {}
};

struct hkShapeBuffer { uint32_t m_data[0x80]; };                            // 512 bytes

class hkShapeCollection : public hkShape {
public:
    virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8(); virtual void v9();
    virtual const hkShape* getChildShape(hkShapeKey key, hkShapeBuffer& buffer) const;   // +0x28
    uint32_t m_userDataAndRefs[2];            // +4
    hkBool m_disableWelding;                  // +0xc
};

struct hkCollisionInput;
class hkCollisionFilter {
public:
    virtual hkBool isCollisionEnabled(const hkCollisionInput& input, const hkCdBody& a, const hkCdBody& b,
                                      const hkShapeCollection* bContainer, hkShapeKey bKey) const;    // +0x00
};

struct hkCollisionAgentConfig {
    uint8_t m_pad[0x10];
    hkBool m_recalcTimAtT0;                   // +0x10: recompute the separating normal at t0
    uint8_t m_pad1[3];
    hkReal m_defaultTimDistance;              // +0x14
};

struct hkCollisionDispatcher;
struct hkCollisionInput {
    hkCollisionDispatcher* m_dispatcher;      // +0
    hkCollisionFilter* m_filter;              // +4
    hkReal m_tolerance;                       // +8
    hkBool m_createPredictiveAgents;          // +0xc
    uint8_t m_pad0[3];
    hkTime m_startTime;                       // +0x10 (step info)
    hkTime m_endTime;                         // +0x14
    uint32_t m_pad1[4];
    hkCollisionAgentConfig* m_config;         // +0x28
};

struct hkContactMgr;
struct hkAgent3Input {
    const hkCdBody* m_bodyA;                  // +0
    const hkCdBody* m_bodyB;                  // +4
    const hkCollisionInput* m_input;          // +8
    hkContactMgr* m_contactMgr;               // +0xc
    hkTransform m_aTb;                        // +0x10
};
struct hkAgent3ProcessInput : hkAgent3Input { // 0x70 bytes
    hkReal m_distAtT1;                        // +0x50
    uint32_t m_pad[3];
    hkVector4 m_linearTimInfo;                // +0x60
};

// Body/transform scratch filled by the input-at-t0 helper below.
struct hkAgent3InputAtT0Scratch {
    hkCdBody m_bodyA;                         // +0
    hkCdBody m_bodyB;                         // +0x10
    hkTransform m_transformA;                 // +0x20
    hkTransform m_transformB;                 // +0x60
};

struct hkContactPoint {
    hkVector4 m_position;
    hkVector4 m_separatingNormal;             // w = distance
    void setFlipped(const hkContactPoint& cp);                                // 0x010cecf0
};
struct hkProcessCdPoint {                     // 0x30 bytes
    hkContactPoint m_contact;
    uint32_t m_contactPointId;
    uint32_t m_pad[3];
};

struct hkContactRef { hkProcessCdPoint* m_contactPoint; void* m_agentEntry; void* m_agentData; };
struct hkPotentialInfo {
    hkContactRef* m_firstFreePotentialContact;            // +0
    hkProcessCdPoint** m_firstFreeRepresentativeContact;  // +4
    hkProcessCdPoint* m_representativeContacts[256];      // +8
    hkContactRef m_potentialContacts[256];                // +0x408
};

struct hkProcessCollisionOutput {
    hkProcessCdPoint* m_firstFreeContactPoint;            // +0
    uint32_t m_pad0[3];
    hkVector4 m_toiPosition;                              // +0x10
    hkVector4 m_toiSeparatingNormal;                      // +0x20
    uint8_t m_pad1[0x3034 - 0x30];
    hkTime m_toiTime;                                     // +0x3034
    uint32_t m_pad2[2];
    hkPotentialInfo* m_potentialContacts;                 // +0x3040
};

class hkCollisionAgent {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void processCollision(const hkCdBody& bodyA, const hkCdBody& bodyB,
                                  const hkCollisionInput& input, hkProcessCollisionOutput& output);   // +0x14
};

// Agent entries in a sector
struct hkAgent1nMachineEntry {
    uint8_t m_streamCommand;                  // 0 padding, 1 end, 2/3 agent (3 = flipped), 4/5 agent with TIM, 6 collision agent
    uint8_t m_agentType;
    uint8_t m_numContactPoints;
    uint8_t m_size;
    hkCollisionAgent* m_agent;                // +4 (stream command 6)
    hkShapeKey m_shapeKey;                    // +8
};
struct hkAgent1nMachineTimEntry : hkAgent1nMachineEntry {
    hkTime m_timeOfSeparatingNormal;          // +0xc
    hkVector4 m_separatingNormal;             // +0x10
};

typedef uint8_t* (__cdecl *hkAgent3CreateFunc)(const hkAgent3Input& input, hkAgent1nMachineEntry* entry, void* agentData);
typedef void (__cdecl *hkAgent3DestroyFunc)(hkAgent1nMachineEntry* entry, void* agentData, hkContactMgr* mgr);
typedef uint8_t* (__cdecl *hkAgent3CleanupFunc)(hkAgent1nMachineEntry* entry, void* agentData, hkContactMgr* mgr);
typedef void (__cdecl *hkAgent3SepNormalFunc)(const hkAgent3Input& input, void* agentData, hkVector4& sepNormalOut);
typedef uint8_t* (__cdecl *hkAgent3ProcessFunc)(const hkAgent3ProcessInput& input, hkAgent1nMachineEntry* entry,
                                                void* agentData, hkVector4* separatingNormal, hkProcessCollisionOutput& output);
struct hkAgent3Funcs {                        // 0x34 bytes
    hkAgent3CreateFunc m_createFunc;          // +0x00
    hkAgent3DestroyFunc m_destroyFunc;        // +0x04
    hkAgent3CleanupFunc m_cleanupFunc;        // +0x08
    void* m_other0[6];                        // +0x0c
    hkAgent3SepNormalFunc m_sepNormalFunc;    // +0x24
    hkAgent3ProcessFunc m_processFunc;        // +0x28
    void* m_other1;                           // +0x2c
    int m_symmetric;                          // +0x30 (2 = agent is written for (B,A): flip the input)
};
struct hkCollisionDispatcher {
    uint8_t m_pad[0xe94];
    uint8_t m_agent3Types[32][32];            // +0xe94
    uint8_t m_agent3TypesPred[32][32];        // +0x1294
    hkAgent3Funcs m_agent3Func[1];            // +0x1694
};

// Track / sectors
struct hkAgent1nSector {
    uint32_t m_bytesAllocated;                // +0
    uint32_t m_pad[3];
    uint8_t m_data[512 - 16];                 // +0x10
    hkAgent1nSector() { m_bytesAllocated = 0; }
    uint8_t* getBegin() { return m_data; }
    uint8_t* getEnd() { return m_data + m_bytesAllocated; }
};
struct hkAgent1nTrack {
    hkAgent1nSector** m_sectorsData;          // hkArray<hkAgent1nSector*>
    int m_sectorsSize;
    int m_sectorsCapacityAndFlags;
};
struct hkArrayUtil { static void __cdecl _reserveExactly(void* array, int numElem, int elemSize); };   // 0x0107f4a0

// Memory
struct hkMemory {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void* allocateChunkFromSizeClass(int sizeIndex, int memClass);           // +0x18
    virtual void deallocateChunkToSizeClass(void* p, int sizeIndex, int memClass);  // +0x1c
    static hkMemory* s_instance;                                                      // 0x016e4178
};
struct hkThreadMemory {
    uint8_t m_pad0[0x34];
    int m_maxNumElemsOnFreeList;              // +0x34
    uint8_t m_pad1[0x68 - 0x38];
    void** m_freeListHead;                    // +0x68 (size class 12)
    uint8_t m_pad2[0xac - 0x6c];
    int m_numFreeElements;                    // +0xac
};
extern unsigned long g_hkThreadMemoryTls;     // 0x016e4174
extern unsigned long g_hkMonitorStreamEndTls; // 0x016e42a8
extern unsigned long g_hkMonitorStreamTls;    // 0x016e42a4
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern "C" __declspec(dllimport) int __stdcall TlsSetValue(unsigned long index, void* value);

inline hkAgent1nSector* allocateSector()
{
    hkThreadMemory* mem = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
    void** p = mem->m_freeListHead;
    if (p) {
        mem->m_numFreeElements--;
        mem->m_freeListHead = (void**)*p;
    } else {
        p = (void**)hkMemory::s_instance->allocateChunkFromSizeClass(0xc, 0x1c);
    }
    return new (p) hkAgent1nSector();
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

// Monitor stream (HK_TIMER_BEGIN / HK_TIMER_END / HK_MONITOR_ADD_VALUE)
struct hkMonitorTimerCommand { const char* m_commandAndMonitor; uint32_t m_time0; uint32_t m_time1; };
struct hkMonitorValueCommand { const char* m_commandAndMonitor; float m_value; };

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

inline void hkMonitorAddValue(const char* command, float value)
{
    char* end = (char*)TlsGetValue(g_hkMonitorStreamEndTls);
    if ((char*)TlsGetValue(g_hkMonitorStreamTls) < end) {
        hkMonitorValueCommand* h = (hkMonitorValueCommand*)TlsGetValue(g_hkMonitorStreamTls);
        h->m_commandAndMonitor = command;
        h->m_value = value;
        TlsSetValue(g_hkMonitorStreamTls, h + 1);
    }
}

// Same-TU helpers that the binary calls out of line (with register arguments).
void hkAgent3ProcessInput_setFlipped(hkAgent3ProcessInput* dst, const hkAgent3ProcessInput* src);    // 0x01103aa0 (ECX=src, EAX=dst)
void hkAgent3Input_setAtT0(hkAgent3Input* out, const hkAgent3Input* src, hkAgent3InputAtT0Scratch* scratch); // 0x01103a10 (ESI=src, EDI=scratch)
extern "C" void __cdecl hkAgent1nMachine_Weld(hkAgent3Input& input, const hkShapeCollection* collection,
                                              hkProcessCollisionOutput& output);                      // 0x01103c40

// The flipped copy of a process input (same body as 0x01103aa0, inlined at two sites).
inline void setFlippedInline(hkAgent3ProcessInput& dst, const hkAgent3ProcessInput& src)
{
    dst.m_bodyA = src.m_bodyB;
    dst.m_bodyB = src.m_bodyA;
    dst.m_input = src.m_input;
    dst.m_contactMgr = src.m_contactMgr;
    dst.m_linearTimInfo.x = -src.m_linearTimInfo.x;
    dst.m_linearTimInfo.y = -src.m_linearTimInfo.y;
    dst.m_linearTimInfo.z = -src.m_linearTimInfo.z;
    dst.m_linearTimInfo.w = src.m_linearTimInfo.w;
    dst.m_aTb.setInverse(src.m_aTb);
}

// hkContactPoint::setFlipped(*this) inlined: position += normal * distance (all four lanes), normal = -normal.
inline void flipContactPointInPlace(hkContactPoint& cp)
{
    hkReal d = cp.m_separatingNormal.w;
    cp.m_position.x = d * cp.m_separatingNormal.x + cp.m_position.x;
    cp.m_position.y = d * cp.m_separatingNormal.y + cp.m_position.y;
    cp.m_position.z = d * cp.m_separatingNormal.z + cp.m_position.z;
    cp.m_position.w = d * cp.m_separatingNormal.w + cp.m_position.w;
    cp.m_separatingNormal.x = -cp.m_separatingNormal.x;
    cp.m_separatingNormal.y = -cp.m_separatingNormal.y;
    cp.m_separatingNormal.z = -cp.m_separatingNormal.z;
    cp.m_separatingNormal.w = cp.m_separatingNormal.w;
}

inline hkReal timDistance(const hkAgent1nMachineTimEntry* e, const hkVector4& lin)
{
    const hkVector4& n = e->m_separatingNormal;
    return n.w - (((n.z * lin.z + n.y * lin.y) + n.x * lin.x) + lin.w);
}

// Monitor-stream strings (literals; .rdata 0x014a4954 "TtrecalcT0", 0x0149cc34 "Et",
// 0x014a5bec "MinumTim", 0x014a5e38 "TtWelding").

// @ 0x011048d0
extern "C" void __cdecl hkAgent1nMachine_Process(hkAgent1nTrack& agentTrack, hkAgent3ProcessInput& input,
                                                 const hkShapeCollection* collection, const hkShapeKey* hitList,
                                                 int numHits, hkProcessCollisionOutput& output)
{
    // welding: collect potential contacts unless an outer machine already does
    hkPotentialInfo potentialInfo;
    hkPotentialInfo* savedPotential = output.m_potentialContacts;
    if (savedPotential == 0 && !collection->m_disableWelding) {
        potentialInfo.m_firstFreePotentialContact = &potentialInfo.m_potentialContacts[0];
        potentialInfo.m_firstFreeRepresentativeContact = &potentialInfo.m_representativeContacts[0];
        output.m_potentialContacts = &potentialInfo;
    } else {
        output.m_potentialContacts = 0;
    }

    hkCollisionDispatcher* dispatcher = input.m_input->m_dispatcher;

    hkCdBody newBodyB(input.m_bodyB);
    input.m_bodyB = &newBodyB;

    hkAgent1nSector* readSector = agentTrack.m_sectorsData[0];
    uint8_t* readPos = readSector->getBegin();
    uint8_t* readEnd = readSector->getEnd();
    int nextReadSector = 1;
    int numTim = 0;
    int writeSectorIndex = 0;

    hkShapeBuffer shapeBuffer;
    hkAgent3ProcessInput flippedCreateInput;
    hkAgent3ProcessInput flippedInput;
    hkAgent3ProcessInput flippedTimInput;
    hkAgent3Input inputAtT0;
    hkAgent3InputAtT0Scratch scratchAtT0;
    hkAgent3Input flippedInputAtT0;
    hkAgent3InputAtT0Scratch flippedScratchAtT0;
    hkBool inputAtT0Ready = false;
    hkBool flippedInputAtT0Ready = false;

    for (;;) {
        hkAgent1nSector* writeSector = allocateSector();
        uint8_t* out = writeSector->getBegin();

        do {
            hkShapeKey key;
            hkAgent1nMachineEntry* entry = (hkAgent1nMachineEntry*)out;

            if (hitList == 0) {
                // no hit list: keep every agent
                hkAgent1nMachineEntry* in = (hkAgent1nMachineEntry*)readPos;
                hkString::memCpy(out, in, in->m_size);
                readPos += in->m_size;
                key = in->m_shapeKey;
            } else {
                key = *hitList;
                hkAgent1nMachineEntry* in = (hkAgent1nMachineEntry*)readPos;
                if (in->m_shapeKey == key) {
                    hkString::memCpy(out, in, in->m_size);
                    readPos += in->m_size;
                } else if (in->m_shapeKey < key) {
                    // the agent's key left the hit list: destroy it
                    void* agentData = ((in->m_streamCommand & 0xe) == 4) ? (void*)(readPos + 0x20) : (void*)(readPos + 0x10);
                    readPos += in->m_size;
                    dispatcher->m_agent3Func[in->m_agentType].m_destroyFunc(in, agentData, input.m_contactMgr);
                    goto nextEntry;
                } else {
                    // new key: create an agent in place
                    const hkCdBody* parentB = input.m_bodyB->m_parent;
                    const hkCollisionInput* cinput = input.m_input;
                    if (!cinput->m_filter->isCollisionEnabled(*cinput, *input.m_bodyA, *parentB, collection, key)) {
                        entry->m_shapeKey = key;
                        entry->m_agentType = 0;
                        entry->m_numContactPoints = 0;
                        entry->m_streamCommand = 0;
                        entry->m_size = 0x10;
                    } else {
                        const hkShape* child = collection->getChildShape(key, shapeBuffer);
                        newBodyB.m_shape = child;
                        newBodyB.m_shapeKey = key;
                        entry->m_shapeKey = key;
                        const hkShape* shapeA = input.m_bodyA->m_shape;
                        hkBool predictive = input.m_input->m_createPredictiveAgents;
                        int typeB = child->getType();
                        int typeA = shapeA->getType();
                        uint8_t agentType;
                        if (predictive) agentType = dispatcher->m_agent3TypesPred[typeA][typeB];
                        else            agentType = dispatcher->m_agent3Types[typeA][typeB];
                        entry->m_agentType = agentType;
                        entry->m_numContactPoints = 0;

                        const hkAgent3ProcessInput* createInput = &input;
                        int flip = 0;
                        if (dispatcher->m_agent3Func[agentType].m_symmetric == 2) {
                            flip = 1;
                            createInput = &flippedCreateInput;
                            hkAgent3ProcessInput_setFlipped(&flippedCreateInput, &input);
                        }
                        uint8_t* end;
                        if (dispatcher->m_agent3Func[entry->m_agentType].m_sepNormalFunc) {
                            hkAgent1nMachineTimEntry* te = (hkAgent1nMachineTimEntry*)entry;
                            te->m_streamCommand = (uint8_t)(flip + 4);
                            te->m_timeOfSeparatingNormal = -1.0f;
                            te->m_separatingNormal.w = 0.0f;
                            te->m_separatingNormal.z = 0.0f;
                            te->m_separatingNormal.y = 0.0f;
                            te->m_separatingNormal.x = 0.0f;
                            end = dispatcher->m_agent3Func[entry->m_agentType].m_createFunc(*createInput, entry, out + 0x20);
                        } else {
                            entry->m_streamCommand = (uint8_t)(flip + 2);
                            end = dispatcher->m_agent3Func[entry->m_agentType].m_createFunc(*createInput, entry, out + 0x10);
                        }
                        entry->m_size = (uint8_t)((uint8_t)(uint32_t)end - (uint8_t)(uint32_t)entry);
                    }
                }
                hitList++;
            }

            // process the (copied or new) entry at 'out'
            switch (entry->m_streamCommand) {
            case 0:
            case 1:
                out += 0x10;
                break;

            case 2: {
                newBodyB.m_shape = collection->getChildShape(key, shapeBuffer);
                newBodyB.m_shapeKey = key;
                uint8_t* end = dispatcher->m_agent3Func[entry->m_agentType].m_processFunc(input, entry, out + 0x10, 0, output);
                entry->m_size = (uint8_t)((uint8_t)(uint32_t)end - (uint8_t)(uint32_t)entry);
                out = end;
                break;
            }

            case 3: {
                setFlippedInline(flippedInput, input);
                newBodyB.m_shape = collection->getChildShape(key, shapeBuffer);
                newBodyB.m_shapeKey = key;
                hkTime oldToi = output.m_toiTime;
                hkProcessCdPoint* firstPoint = output.m_firstFreeContactPoint;
                uint8_t* end = dispatcher->m_agent3Func[entry->m_agentType].m_processFunc(flippedInput, entry, out + 0x10, 0, output);
                entry->m_size = (uint8_t)((uint8_t)(uint32_t)end - (uint8_t)(uint32_t)entry);
                out = end;
                for (hkProcessCdPoint* p = firstPoint; p < output.m_firstFreeContactPoint; p++) {
                    flipContactPointInPlace(p->m_contact);
                }
                if (output.m_toiTime != oldToi) {
                    output.m_toiSeparatingNormal.x = -output.m_toiSeparatingNormal.x;
                    output.m_toiSeparatingNormal.y = -output.m_toiSeparatingNormal.y;
                    output.m_toiSeparatingNormal.z = -output.m_toiSeparatingNormal.z;
                }
                break;
            }

            case 4: {
                hkAgent1nMachineTimEntry* te = (hkAgent1nMachineTimEntry*)entry;
                const hkCollisionInput* cinput = input.m_input;
                hkReal dist;
                if (te->m_timeOfSeparatingNormal == cinput->m_startTime) {
                    goto timCheck4;
                }
                {
                    hkCollisionAgentConfig* config = cinput->m_config;
                    if (config->m_recalcTimAtT0) {
                        hkMonitorTimer("TtrecalcT0");
                        if (!inputAtT0Ready) {
                            inputAtT0Ready = true;
                            hkAgent3Input_setAtT0(&inputAtT0, &input, &scratchAtT0);
                        }
                        scratchAtT0.m_bodyB.m_shape = collection->getChildShape(key, shapeBuffer);
                        scratchAtT0.m_bodyB.m_shapeKey = key;
                        dispatcher->m_agent3Func[entry->m_agentType].m_sepNormalFunc(inputAtT0, out + 0x20, te->m_separatingNormal);
                        hkMonitorTimer("Et");
                        goto timCheck4;
                    }
                    te->m_timeOfSeparatingNormal = cinput->m_endTime;
                    dist = config->m_defaultTimDistance * 0.1f;
                    te->m_separatingNormal.w = 0.0f;
                    te->m_separatingNormal.z = 0.0f;
                    te->m_separatingNormal.y = 0.0f;
                    te->m_separatingNormal.x = 0.0f;
                    te->m_separatingNormal.w = dist;
                    goto process4;
                }
            timCheck4:
                te->m_timeOfSeparatingNormal = input.m_input->m_endTime;
                dist = timDistance(te, input.m_linearTimInfo);
                if (dist >= input.m_input->m_tolerance) {
                    // still separated: skip the agent
                    te->m_separatingNormal.w = dist;
                    if (te->m_numContactPoints == 0) {
                        out += te->m_size;
                    } else {
                        uint8_t* end = dispatcher->m_agent3Func[entry->m_agentType].m_cleanupFunc(entry, out + 0x20, input.m_contactMgr);
                        entry->m_size = (uint8_t)((uint8_t)(uint32_t)end - (uint8_t)(uint32_t)entry);
                        out = end;
                    }
                    numTim++;
                    break;
                }
            process4:
                {
                    input.m_distAtT1 = dist;
                    newBodyB.m_shape = collection->getChildShape(key, shapeBuffer);
                    newBodyB.m_shapeKey = key;
                    uint8_t* end = dispatcher->m_agent3Func[entry->m_agentType].m_processFunc(input, entry, out + 0x20,
                                                                                            &te->m_separatingNormal, output);
                    entry->m_size = (uint8_t)((uint8_t)(uint32_t)end - (uint8_t)(uint32_t)entry);
                    out = end;
                }
                break;
            }

            case 5: {
                hkAgent1nMachineTimEntry* te = (hkAgent1nMachineTimEntry*)entry;
                setFlippedInline(flippedTimInput, input);
                hkReal dist;
                if (te->m_timeOfSeparatingNormal == flippedTimInput.m_input->m_startTime) {
                    goto timCheck5;
                }
                {
                    hkCollisionAgentConfig* config = flippedTimInput.m_input->m_config;
                    if (config->m_recalcTimAtT0) {
                        hkMonitorTimer("TtrecalcT0");
                        if (!flippedInputAtT0Ready) {
                            flippedInputAtT0Ready = true;
                            hkAgent3Input_setAtT0(&flippedInputAtT0, &flippedTimInput, &flippedScratchAtT0);
                        }
                        flippedScratchAtT0.m_bodyA.m_shape = collection->getChildShape(key, shapeBuffer);
                        flippedScratchAtT0.m_bodyA.m_shapeKey = key;
                        dispatcher->m_agent3Func[entry->m_agentType].m_sepNormalFunc(flippedInputAtT0, out + 0x20, te->m_separatingNormal);
                        hkMonitorTimer("Et");
                        goto timCheck5;
                    }
                    te->m_timeOfSeparatingNormal = flippedTimInput.m_input->m_endTime;
                    dist = config->m_defaultTimDistance * 0.5f;
                    te->m_separatingNormal.w = 0.0f;
                    te->m_separatingNormal.z = 0.0f;
                    te->m_separatingNormal.y = 0.0f;
                    te->m_separatingNormal.x = 0.0f;
                    te->m_separatingNormal.w = dist;
                    goto process5;
                }
            timCheck5:
                te->m_timeOfSeparatingNormal = flippedTimInput.m_input->m_endTime;
                dist = timDistance(te, flippedTimInput.m_linearTimInfo);
                if (dist >= flippedTimInput.m_input->m_tolerance) {
                    te->m_separatingNormal.w = dist;
                    if (te->m_numContactPoints == 0) {
                        out += te->m_size;
                    } else {
                        uint8_t* end = dispatcher->m_agent3Func[entry->m_agentType].m_cleanupFunc(entry, out + 0x20,
                                                                                                flippedTimInput.m_contactMgr);
                        entry->m_size = (uint8_t)((uint8_t)(uint32_t)end - (uint8_t)(uint32_t)entry);
                        out = end;
                    }
                    numTim++;
                    break;
                }
            process5:
                {
                    flippedTimInput.m_distAtT1 = dist;
                    newBodyB.m_shape = collection->getChildShape(key, shapeBuffer);
                    newBodyB.m_shapeKey = key;
                    hkTime oldToi = output.m_toiTime;
                    hkProcessCdPoint* firstPoint = output.m_firstFreeContactPoint;
                    uint8_t* end = dispatcher->m_agent3Func[entry->m_agentType].m_processFunc(flippedTimInput, entry, out + 0x20,
                                                                                            &te->m_separatingNormal, output);
                    entry->m_size = (uint8_t)((uint8_t)(uint32_t)end - (uint8_t)(uint32_t)entry);
                    out = end;
                    for (hkProcessCdPoint* p = firstPoint; p < output.m_firstFreeContactPoint; p++) {
                        p->m_contact.setFlipped(p->m_contact);
                    }
                    if (output.m_toiTime != oldToi) {
                        output.m_toiSeparatingNormal.x = -output.m_toiSeparatingNormal.x;
                        output.m_toiSeparatingNormal.y = -output.m_toiSeparatingNormal.y;
                        output.m_toiSeparatingNormal.z = -output.m_toiSeparatingNormal.z;
                    }
                }
                break;
            }

            case 6: {
                newBodyB.m_shape = collection->getChildShape(key, shapeBuffer);
                newBodyB.m_shapeKey = key;
                entry->m_agent->processCollision(*input.m_bodyA, newBodyB, *input.m_input, output);
                out += 0x10;
                break;
            }
            }

        nextEntry:
            if (readPos == readEnd) {
                deallocateSector(readSector);
                if (nextReadSector >= agentTrack.m_sectorsSize) {
                    // done: store the last sector
                    writeSector->m_bytesAllocated = (uint32_t)(out - writeSector->m_data);
                    int newSize = writeSectorIndex + 1;
                    int cap = agentTrack.m_sectorsCapacityAndFlags & 0x3fffffff;
                    if (cap < newSize) {
                        int c2 = cap + cap;
                        hkArrayUtil::_reserveExactly(&agentTrack, (newSize < c2) ? c2 : newSize, 4);
                    }
                    agentTrack.m_sectorsSize = newSize;
                    agentTrack.m_sectorsData[writeSectorIndex] = writeSector;

                    hkMonitorAddValue("MinumTim", (float)numTim);
                    input.m_bodyB = newBodyB.m_parent;

                    hkPotentialInfo* potential = output.m_potentialContacts;
                    if (potential && potential->m_firstFreePotentialContact > &potential->m_potentialContacts[0]) {
                        hkMonitorTimer("TtWelding");
                        hkAgent1nMachine_Weld(input, collection, output);
                        hkMonitorTimer("Et");
                    }
                    output.m_potentialContacts = savedPotential;
                    return;
                }
                readSector = agentTrack.m_sectorsData[nextReadSector];
                readPos = readSector->getBegin();
                readEnd = readSector->getEnd();
                nextReadSector++;
            }
        } while ((int)(out - writeSector->m_data) + ((hkAgent1nMachineEntry*)readPos)->m_size <= 0x1a0);

        // the write sector is full: store it
        int used = (int)(out - writeSector->m_data);
        writeSector->m_bytesAllocated = used;
        if (writeSectorIndex >= nextReadSector) {
            // the writer caught up with the reader: make room
            int numToMove = agentTrack.m_sectorsSize - nextReadSector;
            int newSize = agentTrack.m_sectorsSize + 1;
            int cap = agentTrack.m_sectorsCapacityAndFlags & 0x3fffffff;
            if (cap < newSize) {
                int c2 = cap + cap;
                hkArrayUtil::_reserveExactly(&agentTrack, (newSize < c2) ? c2 : newSize, 4);
            }
            hkAgent1nSector** src = &agentTrack.m_sectorsData[nextReadSector];
            hkAgent1nSector** dst = src + 1;
            for (int i = numToMove - 1; i >= 0; i--) {
                dst[i] = src[i];
            }
            nextReadSector++;
            agentTrack.m_sectorsSize = newSize;
        }
        agentTrack.m_sectorsData[writeSectorIndex] = writeSector;
        writeSectorIndex++;
    }
}
