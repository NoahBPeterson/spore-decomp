// Slice s0088ae10: constructor taking an owner object (a manager is created when the argument is
// null), setting two float fields from globals and initialising a small table and a critter section.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
//
// Field offsets below are the retail ones as seen by this function; only the assignments that matter
// for codegen are kept.
#include "types.h"
#include <intrin.h>

extern float g_f_01485720;      // 0x01485720
extern float g_f_01470f1c;      // 0x01470f1c
extern void* vtbl_01427eb0[];   // 0x01427eb0
extern void* vtbl_0154df28[];   // 0x0154df28

void* FUN_008859d0();           // 0x008859d0: creates the manager

// DLL import used for the critter section; `call dword ptr [0x13cc2d0]` has no `add esp`.
typedef void (__stdcall* CsFn)(void*);
extern CsFn g_InitSection_013cc2d0;   // 0x013cc2d0, ret 4

struct S88AE10 {
    void* vt0;                  // +0x000
    char  pad_04[0x08 - 0x04];
    void* m08;                  // +0x008
    char  pad_0c[0x30 - 0x0c];
    void* m30;                  // +0x030
    void* m34;                  // +0x034
    void* m38;                  // +0x038
    void* m40;                  // +0x040
    char  pad_44[0x50 - 0x44];
    int   m50;                  // +0x050
    int   m54;                  // +0x054
    int   m58;                  // +0x058
    int   m5C;                  // +0x05c
    int   m60;                  // +0x060
    int   m64;                  // +0x064
    int   m68;                  // +0x068
    int   m6C;                  // +0x06c
    int   m70;                  // +0x070
    int   m74;                  // +0x074
    int   m78;                  // +0x078
    int   m7C;                  // +0x07c
    char  pad_80[0x160 - 0x80];
    uint8_t m160;               // +0x160
    uint8_t m161;               // +0x161
    uint8_t m162;               // +0x162
    char  pad_163[0x168 - 0x163];
    char  cs168[0x20];          // +0x168 critical section
    int   m188;                 // +0x188

    S88AE10* ctor(void* owner);
};

// @ 0x0088ae10
S88AE10* S88AE10::ctor(void* owner)
{
    *(void**)this = vtbl_01427eb0;                  // [0x00]
    if (owner == 0)
        owner = FUN_008859d0();
    *(void**)((char*)this + 0x08) = owner;
    *(float*)((char*)this + 0x1c) = g_f_01485720;
    *(float*)((char*)this + 0x20) = g_f_01470f1c;
    *(void**)((char*)this + 0x28) = owner;
    *(int*)((char*)this + 0x2c) = 0;
    *(int*)((char*)this + 0x14) = 1;
    *(void**)((char*)this + 0x10) = vtbl_0154df28;
    *(int*)((char*)this + 0x18) = 0;
    *(int*)((char*)this + 0x24) = 0;
    char* e = (char*)this + 0x48;
    *(void**)((char*)this + 0x40) = e;
    *(void**)((char*)this + 0x34) = e;
    *(void**)((char*)this + 0x30) = e;
    *(void**)((char*)this + 0x38) = e + 8;
    g_InitSection_013cc2d0(cs168);
    m50 = 2;
    m54 = 0x200;
    m58 = 3;
    m5C = 0;
    m160 = 0;
    m161 = 0;
    m162 = 0;
    _InterlockedExchange((long*)&m188, 0);
    m68 = 0xc;
    m6C = 0xc;
    m70 = 0x10;
    m74 = 0x10;
    m78 = 0x14;
    m7C = 0x14;
    *(int*)((char*)this + 0x60) = 4;
    *(int*)((char*)this + 0x64) = 8;
    *(int*)((char*)this + 0x5c) = 8;
    return this;
}
