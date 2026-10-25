// Slice s0109c3b0: Havok hkMultiThreadedSimulation / hkMtThreadStructure internals.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

typedef unsigned int uint;

extern "C" void* __cdecl memcpy(void* dst, const void* src, uint size);

void* FUN_010fc180(void* a, void* b, void* c);        // 0x010fc180
struct CritSec {                                       // hkCriticalSection, __thiscall (this = the CS)
    void enter();                                      // 0x0107f820, no stack arguments, returns via ret
};
void* FUN_010f0b00(void* a, void* b);                  // 0x010f0b00
void* __stdcall FUN_010f19b0(int a);                   // 0x010f19b0 (callee pops)
void* FUN_010f1a10(void* self);                        // 0x010f1a10
void* FUN_010fbb30(void* a, void* b);                  // 0x010fbb30
void* FUN_010a39f0(void* a);                           // 0x010a39f0
void* FUN_010a3920(void* a, void* b, void* c);         // 0x010a3920
void* FUN_0107f530(void* arr, int sz);                 // 0x0107f530 hkArrayUtil::_reserveMore
// sub-objects of the simulation constructed in place (__thiscall on the sub-object)
struct SimSub {
    void* FUN_01082900();                              // 0x01082900 hkMultithreadConfig ctor
    void* FUN_010a5a90();                              // 0x010a5a90 hkJobQueue ctor
    void* FUN_010a65e0();                              // 0x010a65e0 hkJobQueue dtor
    void* FUN_0107db10(int data, int size, int align); // 0x0107db10 hkThreadMemory::deallocateChunk
};
void* FUN_010a65e0();                                  // 0x010a65e0 hkJobQueue dtor
void* FUN_0107db10(void* mem, int a, int b, int c);    // 0x0107db10 hkThreadMemory::deallocateChunk
int FUN_0109c4f0(struct StepIn* a, struct StepHeader* b, struct StepPool** pool);  // 0x0109c4f0
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(uint idx);          // kernel32, IAT 0x013cc2bc
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);   // kernel32, IAT 0x013cc2dc
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void* cs);  // kernel32, IAT 0x013cc2d4
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSectionAndSpinCount(void* cs, uint spin);  // kernel32, IAT 0x013cc1c0
extern void* g_hkMemory;             // 0x016e4178
extern void* g_hkThreadMemoryTls;    // 0x016e4174
extern float g_14a1f98;              // 0x014a1f98
extern void* g_13ef094;              // vtable
extern void* g_imp_LeaveCriticalSection;  // 0x013cc2dc
extern void* g_imp_DeleteCriticalSection; // 0x013cc2d4
extern void* g_imp_TlsGetValue;           // 0x013cc2bc
extern void* g_imp_InitCrit;              // 0x013cc1c0
typedef void (__stdcall* InitCritFn)(void* cs, uint spin);
// called through the imported pointer slot: the original issues `call dword ptr [IAT]`
inline void InitCrit(void* cs, uint spin) { ((InitCritFn)g_imp_InitCrit)(cs, spin); }

// @ 0x0109c3b0  agent-nn stream stepper: splits the next 0x80-byte chunk header off `a`
// into `b`, returning 1 when a sub-chunk was emitted and 0 when the type is not splittable.
// `a` is both the header and the cursor (a[1] is a word counter, a[2]/a[3] the remaining
// byte counts); >7 copies the whole 0x80-byte header through untouched.
int FUN_0109c3b0(int* a, int* b) {
    uint16_t* aw = (uint16_t*)a;       // 16-bit view of the header words
    uint16_t* bw = (uint16_t*)b;
    switch ((uint32_t)a[0]) {
    case 0:
        memcpy(b, a, 0xc);             // type + counter + remaining count
        if (a[2] > 1) {
            aw[2] = (uint16_t)(aw[2] + 1);   // +0x04: chunks emitted so far
            a[2] = a[2] - 1;
            b[2] = 1;
            return 1;
        }
        break;
    case 1:
        memcpy(b, a, 0x10);            // type + counter + count + count2
        if (aw[7] > 0x80) {            // +0x0e: pending bits, split off 0x80 at a time
            *(int*)(a[2] + 0x18) = *(int*)(a[2] + 0x18) + 1;
            aw[7] = (uint16_t)(aw[7] + 0xff80);
            aw[6] = (uint16_t)(aw[6] + 0x80);   // +0x0c: consumed bits
            bw[7] = 0x80;
            return 1;
        }
        break;
    case 3:
        memcpy(b, a, 0xc);
        if (*(int*)a[2] != 0) {        // +0x08: follow the entry chain
            int* p = (int*)(((int*)a[2])[1] + 0x18);
            *p = *p + 1;
            a[2] = *(int*)a[2];
            return 1;
        }
        break;
    case 7:
        memcpy(b, a, 0x10);
        if (a[3] > 4) {                // +0x0c: peel 4 bytes / a[2] advances by 4
            a[3] = a[3] - 4;
            a[2] = a[2] + 4;
            b[3] = 4;
            return 1;
        }
        break;
    default:
        memcpy(b, a, 0x80);            // opaque chunk: pass the whole header through
        break;
    }
    return 0;
}

// cursors / nodes used by the second half of the stepper (FUN_0109c4f0)
struct StepIn {                 // the header FUN_0109c3b0 advances
    int      mType;             // +0x00
    uint16_t mIndex;            // +0x04
    uint16_t mPad06;            // +0x06
    int*     mpEntry;           // +0x08
};

struct StepEntry {              // per-index entry in the pool table
    int mField00;               // +0x00
    int mField04;               // +0x04
    int mField08;               // +0x08
    int mField0C;               // +0x0c
    int mField10;               // +0x10
    int mField14;               // +0x14
    int mField18;               // +0x18  outstanding-node count
    int mField1C;               // +0x1c
};

struct StepPool {               // object behind *(int*)arg3
    uint8_t    mPad00[0x38];
    StepEntry** mpTable;        // +0x38  indexed by StepIn::mIndex
};

struct StepNode {               // 0x28-byte scheduling node
    int      mType;             // +0x00
    uint16_t mIndex;            // +0x04
    uint16_t mPad06;            // +0x06
    int      mField08;          // +0x08
    int      mField0C;          // +0x0c
    int      mField10;          // +0x10
    int      mField14;          // +0x14
    int      mField18;          // +0x18
    int      mField1C;          // +0x1c
    int      mField20;          // +0x20
    int      mField24;          // +0x24
};

struct StepHeader {             // head written into the caller's buffer
    int      mType;             // +0x00
    int      mField04;          // +0x04
    StepNode mNode;             // +0x08
};

// @ 0x0109c4f0  expands the record popped by FUN_0109c3b0 into up to two scheduling
// nodes; returns 1 while the entry is still busy and 0 once nodes were produced.
int FUN_0109c4f0(StepIn* a, StepHeader* b, StepPool** pool) {
    if (a->mType <= 0)
        return 1;
    if (a->mType <= 2) {
        StepEntry* p = (StepEntry*)((int*)a->mpEntry)[1];
        if (--p->mField18 != 0)
            return 1;
        b->mField04 = 0;
        b->mType = 1;
        b->mNode.mType = 3;
        b->mNode.mIndex = a->mIndex;
        b->mNode.mField08 = p->mField1C;
        p->mField18 = 1;
        return 0;
    }
    if (a->mType != 3)
        return 1;
    StepEntry* p = (StepEntry*)((int*)a->mpEntry)[1];
    if (--p->mField18 != 0)
        return 1;
    b->mField04 = 0;
    b->mType = 2;
    b->mNode.mType = 4;
    b->mNode.mIndex = a->mIndex;
    b->mNode.mField08 = p->mField00;
    b->mNode.mField10 = p->mField08 - b->mNode.mField08;
    b->mNode.mField14 = p->mField0C - b->mNode.mField08;
    b->mNode.mField18 = p->mField10 - b->mNode.mField08;
    b->mNode.mField1C = p->mField14 - b->mNode.mField08;
    b->mNode.mField0C = p->mField04;
    b->mNode.mField24 = (int)p;
    b->mNode.mField20 = (*pool)->mpTable[a->mIndex]->mField18;
    return 0;
}

// hkMemory singleton (g_hkMemory): capacity/usage counters and the out-of-memory flag
struct HkMemory {
    int  mField00;          // +0x00
    int  mOutOfMemory;      // +0x04  set to 1 when the memory manager reports exhaustion
    int  mCapacity;         // +0x08
    int  mField0C;          // +0x0c
    int  mField10;          // +0x10
    int  mUsed;             // +0x14
    int  mField18[4];       // +0x18
    int  mPeakUsed;         // +0x28
};

// 0x3c-byte agent-class descriptor indexed by the job's class byte
struct AgentClass {
    uint8_t mField00[0x10];
    uint8_t mField10;       // +0x10
    uint8_t mField11[0x2b];
};

// the simulation object handed to the step wrapper as its 4th argument
struct SimThread {
    void* FUN_010f0b00(void* a, void* b);   // 0x010f0b00, __thiscall (callee pops 8)
};

// vtable front-end for the agent-list callback invoked through [entry+0x10]
struct AgentListOwner {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05(void* a, void* b, void* c, void* d);
};

// @ 0x0109c5e0
void FUN_0109c5e0(void* job, void* cmd, void* ctx, void* sim)
{
    char* j = (char*)job;
    char* c = (char*)cmd;
    char* x = (char*)ctx;

    AgentClass* cls = &((AgentClass*)(*(char**)c + 0x1a14))[*(signed char*)(j + 8)];
    *(AgentClass**)(c + 0x28) = cls;
    *(uint8_t*)(c + 0x0c) = cls->mField10;

    *(char**)x = x + 0x30;
    *(uint32_t*)(x + 0x3034) = 0x7f7fffee;
    *(uint32_t*)(x + 0x3040) = 0;

    FUN_010fc180(job, cmd, ctx);

    HkMemory* mem = (HkMemory*)g_hkMemory;
    int used = mem->mUsed + mem->mPeakUsed;
    int capacity = mem->mCapacity;
    if (!(capacity > used && capacity - used != 0)) {
        mem->mOutOfMemory = 1;
        mem = (HkMemory*)g_hkMemory;
    }
    if (mem->mOutOfMemory == 1)
        return;

    if (*(void**)x != x + 0x30) {
        AgentListOwner* owner = *(AgentListOwner**)(j + 0x10);
        owner->v05(*(void**)(j + 0x14), job, cmd, ctx);
    }

    if (*(float*)(x + 0x3034) < g_14a1f98) {
        ((CritSec*)((char*)sim + 0x180))->enter();
        ((SimThread*)sim)->FUN_010f0b00(ctx, job);
        *(int*)((char*)sim + 0x180 + 0x18) = -1;
        *(int*)((char*)sim + 0x180 + 0x1c) = -1;
        LeaveCriticalSection((char*)sim + 0x180);
    }
}

struct hkMultiThreadedSimulation {
    int prepareMultithreadStep();
    hkMultiThreadedSimulation* ctor(char* owner);      // 0x0109c940, __thiscall (ret 4)
    void dtor();                                       // 0x0109cab0
    void* FUN_010f1a10();                              // 0x010f1a10 (tail-called by dtor)
};
struct hkMtThreadStructure { void* ctor(char* world, int sim, int type); };
struct MtEntityEntityBroadPhaseListener { void addCollisionPair(int* pair); void removeCollisionPair(int* pair); };

// @ 0x0109c6d0  hkMultiThreadedSimulation::prepareMultithreadStep
int hkMultiThreadedSimulation::prepareMultithreadStep() {
    char* s = (char*)this;
    ((CritSec*)(s + 0x100))->enter();
    int v = *(int*)(s + 0xc0) + 1;
    *(int*)(s + 0xc0) = v;
    if (v == 1) return 0;
    *(int*)(s + 0x118) = -1;
    *(int*)(s + 0x11c) = -1;
    LeaveCriticalSection(s + 0x100);
    return 1;
}

// @ 0x0109c730  hkMtThreadStructure ctor
void* hkMtThreadStructure::ctor(char* world, int sim, int type) {
    char* s = (char*)this;
    *(int*)(s + 0x58) = 0;
    *(int*)(s + 0x5c) = 0;
    *(int*)(s + 4) = sim;
    *(int*)(s + 8) = type;
    *(int*)(s + 0) = (int)world;
    int* src = *(int**)(world + 0x78);
    int* dst = (int*)(s + 0xc);
    for (int i = 0xb; i != 0; --i) *dst++ = *src++;
    *(int*)(s + 0x38) = *(int*)(world + 0x2a4);
    *(int*)(s + 0x3c) = *(int*)(world + 0x2a8);
    *(int*)(s + 0x48) = *(int*)(world + 0x2b0);
    *(int*)(s + 0x70) = *(int*)(world + 0x184);
    *(int*)(s + 0x74) = *(int*)(world + 0x188);
    *(int*)(s + 0x40) = *(int*)(world + 0x178);
    *(int*)(s + 0x44) = *(int*)(world + 0x17c);
    *(float*)(s + 0x4c) = *(float*)(world + 0x1d4) * *(float*)(world + 0x2a8);
    *(int*)(s + 0x50) = *(int*)(world + 0x188);
    *(float*)(s + 0x54) = *(float*)(world + 0x1dc) * *(float*)(world + 0x2a8);
    return this;
}

// @ 0x0109c7d0
void MtEntityEntityBroadPhaseListener::addCollisionPair(int* pair) {
    char* s = (char*)this;
    int* listener = *(int**)(s + 8);
    char* e1 = (char*)(*pair + *(char*)(*pair + 5));
    char* e2 = (char*)(pair[1] + *(char*)(pair[1] + 5));
    char* a = e1 + *(int*)(e1 + 0x10);
    char* b = e2 + *(int*)(e2 + 0x10);
    if (((char*)listener)[0x54] && !a[0x99] && !b[0x99] && *(int*)(a + 0x5c) != *(int*)(b + 0x5c)) {
        if ((uint)*(int*)((char*)listener + 0x5c) == (*(uint*)((char*)listener + 0x60) & 0x3fffffff))
            FUN_0107f530((char*)listener + 0x58, 8);
        int idx = *(int*)((char*)listener + 0x5c);
        int* arr = *(int**)((char*)listener + 0x58);
        arr[idx * 2] = *pair;
        arr[idx * 2 + 1] = pair[1];
        *(int*)((char*)listener + 0x5c) = *(int*)((char*)listener + 0x5c) + 1;
        return;
    }
    // no collision pair to report: classify the agent pair in the simulation's pair table
    char* table = *(char**)(*(int*)((char*)listener + 0x2c) + 0x78);
    int   base = *(int*)table;
    int   i1 = *(unsigned short*)(e1 + 0x1a);
    int   i2 = *(unsigned short*)(e2 + 0x1a);
    char  cls = *(char*)(base + i2 + i1 * 8 + 0x19d4);
    if (cls) {
        table[0xc] = *(char*)(base + (int)cls * 0x3c + 0x1a24);
        FUN_010a3920(e1, e2, table);
    }
}

// @ 0x0109c890
void MtEntityEntityBroadPhaseListener::removeCollisionPair(int* pair) {
    char* s = (char*)this;
    int* listener = *(int**)(s + 8);
    char* e1 = (char*)(*pair + *(char*)(*pair + 5));
    char* e2 = (char*)(pair[1] + *(char*)(pair[1] + 5));
    char* a = e1 + *(int*)(e1 + 0x10);
    char* b = e2 + *(int*)(e2 + 0x10);
    if (((char*)listener)[0x54] && !a[0x99] && !b[0x99] && *(int*)(a + 0x5c) != *(int*)(b + 0x5c)) {
        if ((uint)*(int*)((char*)listener + 0x8c) == (*(uint*)((char*)listener + 0x90) & 0x3fffffff))
            FUN_0107f530((char*)listener + 0x88, 8);
        int idx = *(int*)((char*)listener + 0x8c);
        int* arr = *(int**)((char*)listener + 0x88);
        arr[idx * 2] = *pair;
        arr[idx * 2 + 1] = pair[1];
        *(int*)((char*)listener + 0x8c) = *(int*)((char*)listener + 0x8c) + 1;
        return;
    }
    int e = (int)FUN_010fbb30(e1, e2);
    if (e) FUN_010a39f0((void*)e);
}

// @ 0x0109c940  hkMultiThreadedSimulation ctor
hkMultiThreadedSimulation* hkMultiThreadedSimulation::ctor(char* owner) {
    char* s = (char*)this;
    FUN_010f19b0(0);
    *(int*)(s) = 0x14a1fe0;
    *(int*)(s + 0x38) = 0;
    *(int*)(s + 0x30) = 0x14a1f9c;
    *(unsigned short*)(s + 0x36) = 1;
    *(int*)(s + 0x44) = 0;
    *(unsigned short*)(s + 0x42) = 1;
    *(int*)(s + 0x3c) = 0x149dabc;
    *(unsigned short*)(s + 0x4e) = 1;
    *(int*)(s + 0x50) = 0;
    *(int*)(s + 0x48) = 0x149da84;
    *(int*)(s + 0x58) = 0;
    *(int*)(s + 0x5c) = 0;
    *(int*)(s + 0x60) = 0x80000000;
    InitCrit(s + 0x68, 4000);
    *(int*)(s + 0x88) = 0;
    *(int*)(s + 0x8c) = 0;
    *(int*)(s + 0x90) = 0x80000000;
    InitCrit(s + 0x98, 4000);
    ((SimSub*)(s + 0xb8))->FUN_01082900();
    ((SimSub*)(s + 0x100))->FUN_010a5a90();
    InitCrit(s + 0x180, 4000);
    InitCrit(s + 0x1c0, 100000);
    InitCrit(s + 0x200, 4000);
    *(int*)(s + 0x2c) = (int)owner;
    *(int*)(s + 0xc0) = 0;
    *(char*)(s + 0x54) = 0;
    *(int*)(s + 0x38) = (int)s;
    *(int*)(s + 0x44) = (int)(s + 0x200);
    *(int*)(*(char**)(owner + 0x68) + 0x24) = (int)(s + 0x30);
    *(int*)(*(char**)(owner + 0x68) + 0x44) = (int)(s + 0x3c);
    *(int*)(*(char**)(owner + 0x68) + 0x28) = (int)(s + 0x3c);
    *(int*)(*(char**)(owner + 0x68) + 0x48) = (int)(s + 0x3c);
    *(int*)(s + 0x50) = (int)(s + 0x200);
    *(int*)(*(char**)(owner + 0x68) + 0x2c) = (int)(s + 0x48);
    *(int*)(*(char**)(owner + 0x68) + 0x64) = (int)(s + 0x48);
    *(int*)(*(char**)(owner + 0x68) + 0x4c) = (int)(s + 0x48);
    *(int*)(*(char**)(owner + 0x68) + 0x68) = (int)(s + 0x48);
    *(int*)(*(char**)(owner + 0x68) + 0x6c) = (int)(s + 0x48);
    *(int*)(s + 0x15c) = 0x109c3b0;
    *(int*)(s + 0x160) = 0x109c4f0;
    return this;
}

// @ 0x0109cab0  hkMultiThreadedSimulation dtor
void hkMultiThreadedSimulation::dtor() {
    char* s = (char*)this;
    *(int*)(s) = 0x14a1fe0;
    DeleteCriticalSection(s + 0x200);
    DeleteCriticalSection(s + 0x1c0);
    DeleteCriticalSection(s + 0x180);
    ((SimSub*)(s + 0x100))->FUN_010a65e0();
    DeleteCriticalSection(s + 0x98);
    if (*(int*)(s + 0x90) >= 0) {
        SimSub* tm = (SimSub*)TlsGetValue((uint)(int)g_hkThreadMemoryTls);
        tm->FUN_0107db10(*(int*)(s + 0x88), (*(int*)(s + 0x90) & 0x3fffffff) << 3, 0x14);
    }
    DeleteCriticalSection(s + 0x68);
    if (*(int*)(s + 0x60) >= 0) {
        SimSub* tm = (SimSub*)TlsGetValue((uint)(int)g_hkThreadMemoryTls);
        tm->FUN_0107db10(*(int*)(s + 0x58), (*(int*)(s + 0x60) & 0x3fffffff) << 3, 0x14);
    }
    *(int*)(s + 0x48) = (int)g_13ef094;
    *(int*)(s + 0x3c) = (int)g_13ef094;
    *(int*)(s + 0x30) = (int)g_13ef094;
    FUN_010f1a10();
}
