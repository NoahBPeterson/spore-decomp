// Slice s0109c3b0: Havok hkMultiThreadedSimulation / hkMtThreadStructure internals.
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

typedef unsigned int uint;

void* FUN_010fc180(void* a, void* b, void* c);        // 0x010fc180
void* FUN_0107f820(void* cs);                          // 0x0107f820 hkCriticalSection::enter
void* FUN_010f0b00(void* a, void* b);                  // 0x010f0b00
void* FUN_010f19b0(int a);                             // 0x010f19b0
void* FUN_010f1a10(void* self);                        // 0x010f1a10
void* FUN_010fbb30(void* a, void* b);                  // 0x010fbb30
void* FUN_010a39f0(void* a);                           // 0x010a39f0
void* FUN_010a3920(void* a, void* b, void* c);         // 0x010a3920
void* FUN_0107f530(void* arr, int sz);                 // 0x0107f530 hkArrayUtil::_reserveMore
void* FUN_01082900();                                  // 0x01082900 hkMultithreadConfig ctor
void* FUN_010a5a90();                                  // 0x010a5a90 hkJobQueue ctor
void* FUN_010a65e0();                                  // 0x010a65e0 hkJobQueue dtor
void* FUN_0107db10(void* mem, int a, int b, int c);    // 0x0107db10 hkThreadMemory::deallocateChunk
void* FUN_0109c4f0();                                  // 0x0109c4f0
void* TlsGetValue(void* idx);                          // kernel32
void  LeaveCriticalSection(void* cs);                  // kernel32
void  DeleteCriticalSection(void* cs);                 // kernel32
void  InitializeCriticalSectionAndSpinCount(void* cs, uint spin);  // kernel32
extern void* g_hkMemory;             // 0x016e4178
extern void* g_hkThreadMemoryTls;    // 0x016e4174
extern float g_14a1f98;              // 0x014a1f98
extern void* g_13ef094;              // vtable
extern void* g_imp_LeaveCriticalSection;  // 0x013cc2dc
extern void* g_imp_DeleteCriticalSection; // 0x013cc2d4
extern void* g_imp_TlsGetValue;           // 0x013cc2bc
extern void* g_imp_InitCrit;              // 0x013cc1c0

// @ 0x0109c3b0
int FUN_0109c3b0(int* a, int* b) {
    switch (a[0]) {
    case 0:
        b[0] = a[0]; b[1] = a[1]; b[2] = a[2];
        if (a[2] > 1) {
            *(short*)(a + 1) = (short)(*(short*)(a + 1) + 1);
            a[2] = a[2] - 1;
            b[2] = 1;
            return 1;
        }
        break;
    case 1:
        b[0] = a[0]; b[1] = a[1]; b[2] = a[2]; b[3] = a[3];
        if ((unsigned short)(*(short*)((char*)a + 0xe)) > 0x80) {
            *(int*)(a[2] + 0x18) = *(int*)(a[2] + 0x18) + 1;
            *(short*)((char*)a + 0xe) = (short)(*(short*)((char*)a + 0xe) + 0xff80);
            *(short*)(a + 3) = (short)(*(short*)(a + 3) + 0x80);
            *(short*)((char*)b + 0xe) = 0x80;
            return 1;
        }
        break;
    case 2:
        break;
    case 3:
        b[0] = a[0]; b[1] = a[1]; b[2] = a[2];
        if (*(int*)a[2] != 0) {
            int* p = (int*)(((int*)a[2])[1] + 0x18);
            *p = *p + 1;
            a[2] = *(int*)a[2];
            return 1;
        }
        break;
    case 7:
        b[0] = a[0]; b[1] = a[1]; b[2] = a[2]; b[3] = a[3];
        if (a[3] > 4) {
            a[3] = a[3] - 4;
            a[2] = a[2] + 4;
            b[3] = 4;
            return 1;
        }
        break;
    default:
        for (int i = 0x20; i != 0; --i) { *b++ = *a++; }
        break;
    }
    return 0;
}

// @ 0x0109c5e0
void FUN_0109c5e0(void* a, int* b, int* c, int d) {
    (void)a; (void)b; (void)c; (void)d;
}

// @ 0x0109c6d0  hkMultiThreadedSimulation::prepareMultithreadStep
int FUN_0109c6d0(void* self) {
    char* s = (char*)self;
    FUN_0107f820(s + 0x100);
    int v = *(int*)(s + 0xc0) + 1;
    *(int*)(s + 0xc0) = v;
    if (v == 1) return 0;
    *(int*)(s + 0x118) = -1;
    *(int*)(s + 0x11c) = -1;
    LeaveCriticalSection(s + 0x100);
    return 1;
}

// @ 0x0109c730  hkMtThreadStructure ctor
void* FUN_0109c730(void* self, char* world, int sim, int type) {
    char* s = (char*)self;
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
    return self;
}

// @ 0x0109c7d0
void FUN_0109c7d0(void* self, int* pair) {
    char* s = (char*)self;
    int* listener = *(int**)(s + 8);
    char* e1 = (char*)(*pair + *(char*)(*pair + 5));
    char* e2 = (char*)(pair[1] + *(char*)(pair[1] + 5));
    char* a = e1 + *(int*)(e1 + 0x10);
    char* b = e2 + *(int*)(e2 + 0x10);
    if (listener[0x54/4] && !a[0x99] && !b[0x99] && *(int*)(a + 0x5c) != *(int*)(b + 0x5c)) {
        if ((uint)*(int*)((char*)listener + 0x5c) == (*(uint*)((char*)listener + 0x60) & 0x3fffffff))
            FUN_0107f530((char*)listener + 0x58, 8);
        int idx = *(int*)((char*)listener + 0x5c);
        int* arr = *(int**)((char*)listener + 0x58);
        arr[idx * 2] = *pair;
        arr[idx * 2 + 1] = pair[1];
        *(int*)((char*)listener + 0x5c) = *(int*)((char*)listener + 0x5c) + 1;
        return;
    }
    int* t = *(int**)(*(int*)((char*)listener + 0x2c) + 0x78);
    (void)t;
}

// @ 0x0109c890
void FUN_0109c890(void* self, int* pair) {
    char* s = (char*)self;
    int* listener = *(int**)(s + 8);
    char* e1 = (char*)(*pair + *(char*)(*pair + 5));
    char* e2 = (char*)(pair[1] + *(char*)(pair[1] + 5));
    char* a = e1 + *(int*)(e1 + 0x10);
    char* b = e2 + *(int*)(e2 + 0x10);
    if (listener[0x54/4] && !a[0x99] && !b[0x99] && *(int*)(a + 0x5c) != *(int*)(b + 0x5c)) {
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
void* FUN_0109c940(void* self, char* owner) {
    char* s = (char*)self;
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
    InitializeCriticalSectionAndSpinCount(s + 0x68, 4000);
    *(int*)(s + 0x88) = 0;
    *(int*)(s + 0x8c) = 0;
    *(int*)(s + 0x90) = 0x80000000;
    InitializeCriticalSectionAndSpinCount(s + 0x98, 4000);
    FUN_01082900();
    FUN_010a5a90();
    InitializeCriticalSectionAndSpinCount(s + 0x180, 4000);
    InitializeCriticalSectionAndSpinCount(s + 0x1c0, 100000);
    InitializeCriticalSectionAndSpinCount(s + 0x200, 4000);
    *(int*)(s + 0x2c) = (int)owner;
    *(int*)(s + 0xc0) = 0;
    *(char*)(s + 0x54) = 0;
    *(int*)(s + 0x38) = (int)s;
    *(int*)(s + 0x44) = (int)(s + 0x200);
    char* q = *(char**)(owner + 0x68);
    *(int*)(q + 0x24) = (int)(s + 0x30);
    *(int*)(q + 0x44) = (int)(s + 0x3c);
    *(int*)(q + 0x28) = (int)(s + 0x3c);
    *(int*)(q + 0x48) = (int)(s + 0x3c);
    *(int*)(s + 0x50) = (int)(s + 0x200);
    *(int*)(q + 0x2c) = (int)(s + 0x48);
    *(int*)(q + 0x64) = (int)(s + 0x48);
    *(int*)(q + 0x4c) = (int)(s + 0x48);
    *(int*)(q + 0x68) = (int)(s + 0x48);
    *(int*)(q + 0x6c) = (int)(s + 0x48);
    *(int*)(s + 0x15c) = 0x109c3b0;
    *(int*)(s + 0x160) = 0x109c4f0;
    return self;
}

// @ 0x0109cab0  hkMultiThreadedSimulation dtor
void FUN_0109cab0(void* self) {
    char* s = (char*)self;
    *(int*)(s) = 0x14a1fe0;
    DeleteCriticalSection(s + 0x200);
    DeleteCriticalSection(s + 0x1c0);
    DeleteCriticalSection(s + 0x180);
    FUN_010a65e0();
    DeleteCriticalSection(s + 0x98);
    if (*(int*)(s + 0x90) >= 0) {
        void* tm = TlsGetValue(g_hkThreadMemoryTls);
        FUN_0107db10(tm, *(int*)(s + 0x88), (*(int*)(s + 0x90) & 0x3fffffff) << 3, 0x14);
    }
    DeleteCriticalSection(s + 0x68);
    if (*(int*)(s + 0x60) >= 0) {
        void* tm = TlsGetValue(g_hkThreadMemoryTls);
        FUN_0107db10(tm, *(int*)(s + 0x58), (*(int*)(s + 0x60) & 0x3fffffff) << 3, 0x14);
    }
    *(int*)(s + 0x48) = (int)g_13ef094;
    *(int*)(s + 0x3c) = (int)g_13ef094;
    *(int*)(s + 0x30) = (int)g_13ef094;
    FUN_010f1a10(self);
}
