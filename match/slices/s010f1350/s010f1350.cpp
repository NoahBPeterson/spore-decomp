// Slice s010f1350: Havok hkContinuousSimulation continuous-collision routines.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

typedef unsigned int uint;

void* FUN_01099cb0(int a, int b, int c);      // 0x01099cb0
void* FUN_010f0bb0(void* self, int a, int b); // 0x010f0bb0
void* FUN_0111ccf0();                         // 0x0111ccf0 hkDefaultToiResourceMgr ctor
void* FUN_0107db10(void* mem, int a, int b, int c);  // 0x0107db10 deallocateChunk
void* TlsGetValue(void* idx);
void* hkMemoryAlloc(int size, int align);     // hkMemory::s_instance vtable+0x10
extern void* g_hkMemory;                      // 0x016e4178
extern void* g_hkThreadMemoryTls;             // 0x016e4174
extern void* g_13ef094;                       // vtable

// @ 0x010f19b0  hkContinuousSimulation ctor helper
void* FUN_010f19b0(void* self, int owner) {
    char* s = (char*)self;
    *(unsigned short*)(s + 6) = 1;
    *(char*)(s + 0xc) = 1;
    *(int*)(s) = 0x14a59d0;
    *(int*)(s + 0x18) = 0;
    *(int*)(s + 0x1c) = 0;
    *(int*)(s + 0x20) = 0x80000000;
    *(int*)(s + 0x14) = 0;
    *(int*)(s + 0x10) = owner;
    void* tm = g_hkMemory;
    void* alloc = hkMemoryAlloc(0xc, 0x12);
    *(unsigned short*)((char*)alloc + 4) = 0xc;
    void* mgr = FUN_0111ccf0();
    *(int*)(s + 0x28) = 0;
    *(int*)(s + 0x24) = (int)mgr;
    return self;
}

// @ 0x010f1a10  hkContinuousSimulation dtor
void FUN_010f1a10(void* self) {
    char* s = (char*)self;
    *(int*)(s) = 0x14a59d0;
    int r = *(int*)(s + 0x24);
    if (r) {
        void** vt = *(void***)r;
        ((void(__thiscall*)(void*,int))vt[0])((void*)r, 1);
    }
    if (*(int*)(s + 0x20) >= 0) {
        void* tm = TlsGetValue(g_hkThreadMemoryTls);
        FUN_0107db10(tm, *(int*)(s + 0x18),
                     (*(int*)(s + 0x20) & 0x3fffffff) << 6, 0x14);
    }
    *(int*)(s) = (int)g_13ef094;
}

// @ 0x010f1a60  hkContinuousSimulation::resetCollisionInformationForEntities
struct ContinuousSim {
    void resetEntities(int a, int b, int c);
    void collideIsland(int* island, void* input);
    void processAgentCollide(void* entry, void* input, void* output);
    void* scalarDelete(unsigned int flags);
    void f0bb0(int a, int b);   // 0x010f0bb0
};
void ContinuousSim::resetEntities(int a, int b, int c) {
    FUN_01099cb0(a, b, c);
    f0bb0(a, b);
}

// @ 0x010f1350
void FUN_010f1350(void* input, int prio, float dt, void* entities, void* flags, void* a, void* b) {
    (void)input; (void)prio; (void)dt; (void)entities; (void)flags; (void)a; (void)b;
}

// @ 0x010f1690
char FUN_010f1690(void* a, void* b) {
    (void)a; (void)b;
    return 0;
}

// @ 0x010f17f0
void FUN_010f17f0(float dt, void* island, void* flags, void* entities) {
    (void)dt; (void)island; (void)flags; (void)entities;
}

// @ 0x010f18d0
void FUN_010f18d0(void* island, void* flags) {
    (void)island; (void)flags;
}

// @ 0x010f1a90
void ContinuousSim::collideIsland(int* island, void* input) {
    (void)island; (void)input;
}

// @ 0x010f1cc0
void ContinuousSim::processAgentCollide(void* entry, void* input, void* output) {
    (void)entry; (void)input; (void)output;
}

// @ 0x010f1d80  hkContinuousSimulation scalar deleting dtor
void* ContinuousSim::scalarDelete(unsigned int flags) {
    FUN_010f1a10(this);
    if (flags & 1) {
        // operator delete(this)
    }
    return this;
}
