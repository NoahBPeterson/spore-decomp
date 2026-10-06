// Slice s00927be0 - pool allocator cores + critical-section locked wrappers.
// Optimized (/O2, no /GS cookies). The three large allocator cores are approximated.
#include "types.h"

extern "C" {
__declspec(dllimport) void __stdcall EnterCriticalSection(void*);
__declspec(dllimport) void __stdcall LeaveCriticalSection(void*);
}

struct CriSec {
    uint8_t pad[0x18];
    int     ref;      // +0x18
};

struct cLocalLightInfo {
    uint8_t pad[0x4e4];
    CriSec* mCS;      // +0x4e4

    __declspec(noinline) void* AllocCore(int a, int b);                 // 0x00927be0
    __declspec(noinline) void* AllocAligned(void* p, int sz, int a3, int a4); // 0x009282e0
    __declspec(noinline) void* ReallocCore(void* p, int sz, int a3);    // 0x00928730

    __declspec(noinline) void* LockedAlloc(int a1, int a2, int a3, int a4, int a5, int a6);               // 0x009289f0
    __declspec(noinline) void* LockedAligned(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8); // 0x00928a30
    __declspec(noinline) void* LockedRealloc(int a1, int a2, int a3);                                     // 0x00928a80
};

extern cLocalLightInfo* g_pool;   // 0x016c8b44

// @ 0x009289f0
void* cLocalLightInfo::LockedAlloc(int a1, int a2, int a3, int a4, int a5, int a6)
{
    CriSec* cs = mCS;
    if (cs != 0) {
        EnterCriticalSection(cs);
        cs->ref++;
    }
    void* r = AllocCore(a1, a2);
    if (cs != 0) {
        cs->ref--;
        LeaveCriticalSection(cs);
    }
    return r;
}

// @ 0x00928a30
void* cLocalLightInfo::LockedAligned(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
    CriSec* cs = mCS;
    if (cs != 0) {
        EnterCriticalSection(cs);
        cs->ref++;
    }
    void* r = AllocAligned((void*)a1, a2, a3, a4);
    if (cs != 0) {
        cs->ref--;
        LeaveCriticalSection(cs);
    }
    return r;
}

// @ 0x00928a80
void* cLocalLightInfo::LockedRealloc(int a1, int a2, int a3)
{
    CriSec* cs = mCS;
    if (cs != 0) {
        EnterCriticalSection(cs);
        cs->ref++;
    }
    void* r = ReallocCore((void*)a1, a2, a3);
    if (cs != 0) {
        cs->ref--;
        LeaveCriticalSection(cs);
    }
    return r;
}

// @ 0x00928ad0
void __cdecl Pool_AllocGlobal(unsigned size, unsigned* out)
{
    unsigned r = (unsigned)g_pool->LockedAlloc((int)size, 0, 0, 0, 0, 0);
    if (out != 0)
        *out = r ? size : 0;
}

// ---------------------------------------------------------------- approximate cores
// @ 0x00927be0  (pool malloc core - approximated)
void* cLocalLightInfo::AllocCore(int a, int b)
{
    (void)a; (void)b;
    return 0;
}

// @ 0x009282e0  (pool aligned-alloc core - approximated)
void* cLocalLightInfo::AllocAligned(void* p, int sz, int a3, int a4)
{
    (void)p; (void)sz; (void)a3; (void)a4;
    return 0;
}

// @ 0x00928730  (pool realloc core - approximated)
void* cLocalLightInfo::ReallocCore(void* p, int sz, int a3)
{
    (void)p; (void)sz; (void)a3;
    return 0;
}