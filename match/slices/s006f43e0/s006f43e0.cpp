// Slice s006f43e0: Graphics/image-resource dispatch helpers, intrusive-pointer copy loops,
// camera/lighting distance queries and a Graphics-hashtable destructor.
// Region 0x6f43e0-0x6f54a0. Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
#include "types.h"
#include <intrin.h>

// ---- external callees -------------------------------------------------------------------
void* __cdecl FUN_0067dd60();          // +0x20 dispatcher (graphics manager)
void* __cdecl FUN_0067dd40();          // +0x74/0x78/0x7c dispatcher
void  __cdecl FUN_0070f520(void* b, void* e);
void  __cdecl Hashtable_DoFreeNodes1(void* b, void* e);
void  __cdecl Hashtable_DoFreeNodes2(void* b, void* e);
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
void  __cdecl operator_delete_(void* p);
void  __cdecl FUN_007c40f0(void* p);
void  __cdecl FUN_006ddcc0();
void  __cdecl FUN_006ddd10(int a, void* b);
void  __cdecl FUN_00921440(void* out, unsigned a, void* b, int c);
void  __cdecl FUN_011f1120();

extern float g_16194f8;   // 0x16194f8  camera basis
extern float g_16194fc;   // 0x16194fc
extern float g_1619500;   // 0x1619500
extern float g_1619638;   // 0x1619638  matrix data
extern char  g_1619530;   // 0x1619530

static inline void** Vt(void* p) { return *(void***)p; }
static inline void* CallSlot0(void* p, int slot) {
    return ((void* (__thiscall*)(void*))Vt(p)[slot])(p);
}

struct cImageHost {
    void GetImageResource(void* r);      // 0x576650
};

// @ 0x006f44c0
bool __stdcall FUN_006f44c0(void* a, void* b, cImageHost* host) {
    void* mgr = FUN_0067dd60();
    int r = (*(int (__thiscall**)(void*, void*, void*, int))(Vt(mgr) + 8))(mgr, a, b, 0);
    if (r != 0) {
        host->GetImageResource((void*)r);
        return true;
    }
    return false;
}

// @ 0x006f4500
bool __stdcall FUN_006f4500(unsigned int id, void* unused, cImageHost* host) {
    (void)unused;
    if (id == 0x0F19D8D5) {
        void* mgr = FUN_0067dd40();
        void* r = CallSlot0(mgr, 30);
        host->GetImageResource(r);
        return true;
    }
    if (id == 0xFD9802C7) {
        void* mgr = FUN_0067dd40();
        void* r = CallSlot0(mgr, 31);
        host->GetImageResource(r);
        return true;
    }
    if (id == 0x9B304161) {
        void* mgr = FUN_0067dd40();
        void* r = CallSlot0(mgr, 29);
        host->GetImageResource(r);
        return true;
    }
    return false;
}

// @ 0x006f43e0  (intrusive_ptr copy + release)
static void AddRef(void* p) { _InterlockedExchangeAdd((volatile long*)((char*)p + 8), 1); }
static void Release(void* p) {
    volatile long* rc = (volatile long*)((char*)p + 8);
    _InterlockedExchangeAdd(rc, -1);
    long c = _InterlockedExchangeAdd(rc, 0);
    if (c < 1) _InterlockedExchangeAdd(rc, 1);
}
void FUN_006f43e0(void** first, void** last, void** dest) {
    for (; first != last; ++first, ++dest) {
        void* s = *first;
        void* d = *dest;
        if (s != d) {
            if (s) AddRef(s);
            *dest = s;
            if (d) Release(d);
        }
    }
}

// @ 0x006f4450  (intrusive_ptr copy_backward + release)
void FUN_006f4450(void** first, void** last, void** destEnd) {
    while (last != first) {
        void* s = *--last;
        void* d = *--destEnd;
        if (s != d) {
            if (s) AddRef(s);
            *destEnd = s;
            if (d) Release(d);
        }
    }
}

// @ 0x006f51b0
void __fastcall FUN_006f51b0(char* self) {
    FUN_0070f520(*(void**)(self + 0x78), *(void**)(self + 0x7c));
    void* p = *(void**)(self + 0x78);
    if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = *(void**)(self + 0x60);
    if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    p = *(void**)(self + 0x4c);
    if (p && ((int*)p)[-1]) EASTL_allocator_deallocate(p);
    Hashtable_DoFreeNodes1(*(void**)(self + 0x30), *(void**)(self + 0x34));
    *(void**)(self + 0x38) = 0;
    if (*(unsigned int*)(self + 0x34) > 1) EASTL_allocator_deallocate(*(void**)(self + 0x30));
    Hashtable_DoFreeNodes2(*(void**)(self + 0x10), *(void**)(self + 0x14));
    *(void**)(self + 0x18) = 0;
    if (*(unsigned int*)(self + 0x14) > 1) EASTL_allocator_deallocate(*(void**)(self + 0x10));
}

// ---- complex camera/lighting + hashtable routines: skeletons (see partial.txt) ----------
// @ 0x006f4580
float FUN_006f4580() { return 0.0f; }
// @ 0x006f46f0
float __fastcall FUN_006f46f0(int self) { (void)self; return 0.0f; }
// @ 0x006f4930
float FUN_006f4930() { return 0.0f; }
// @ 0x006f4a10
void FUN_006f4a10(int self, float* v, unsigned a, char flag) { (void)self; (void)v; (void)a; (void)flag; }
// @ 0x006f4b90
void FUN_006f4b90(void* self, void* state, unsigned a, float b, float c, float d, float e) {
    (void)self; (void)state; (void)a; (void)b; (void)c; (void)d; (void)e;
}
// @ 0x006f4ff0
void FUN_006f4ff0(void* self, void* out, void* key) { (void)self; (void)out; (void)key; }
// @ 0x006f5260
void FUN_006f5260(void* self, unsigned a, int b, unsigned c, void* d) {
    (void)self; (void)a; (void)b; (void)c; (void)d;
}
