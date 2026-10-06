// Slice s009272c0 - custom pool allocator around 0x0092xxxx (dlmalloc-like) and
// SP::cLocalLightInfo lock helper. Optimized (/O2, no /GS cookies).
#include "types.h"

// ---------------------------------------------------------------- Win32 / CRT
extern "C" {
__declspec(dllimport) void* __stdcall VirtualAlloc(void*, unsigned, unsigned, unsigned);
__declspec(dllimport) void  __stdcall EnterCriticalSection(void*);
__declspec(dllimport) void  __stdcall LeaveCriticalSection(void*);
void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int); // 0x00f473a0
void* __cdecl operator_new__(void*, int, unsigned);                            // 0x011e073e
void* __cdecl op_delete(void*);                                                // 0x00f47380
}

// pool helpers (out of slice)
extern "C" void* __cdecl Pool_26100(void*);          // 0x00926100
extern "C" void  __cdecl Pool_26120(void*);          // 0x00926120
extern "C" void  __cdecl Pool_26140(void*);          // 0x00926140
extern "C" void  __cdecl Pool_26340(void*);          // 0x00926340
extern "C" void* __cdecl Pool_26790(void*);          // 0x00926790
extern "C" void* __cdecl Pool_267c0(void*);          // 0x009267c0
extern "C" void* __cdecl Pool_267d0();               // 0x009267d0
extern "C" int   __cdecl Pool_267e0();               // 0x009267e0
extern "C" void  __cdecl Pool_26840(void*, int);     // 0x00926840
extern "C" void* __cdecl Pool_26c20(void*, unsigned, int); // 0x00926c20
extern "C" void  __cdecl Pool_26a10(void*);          // 0x00926a10
extern "C" void  __cdecl Pool_26a60(void*, int);     // 0x00926a60
extern "C" void  __cdecl Pool_26fd0(void*, int);     // 0x00926fd0
extern "C" void* __cdecl Pool_28df0();               // 0x00928df0
extern "C" void  __cdecl Pool_27140(int, int, int, int, int, int); // 0x00927140

extern void* g_poolHookList;   // 0x01668ec0

// ---------------------------------------------------------------- lock helper
struct CriSec {
    uint8_t pad[0x18];
    int     ref;      // +0x18
};

struct cLocalLightInfo {
    uint8_t pad[0x4e4];
    CriSec* mCS;      // +0x4e4
    void Sub(int);    // 0x00926fd0
    void Release(int param);  // @ 0x009276c0
};

// @ 0x009276c0
void cLocalLightInfo::Release(int param)
{
    if (param != 0) {
        CriSec* cs = mCS;
        if (cs != 0) {
            EnterCriticalSection(cs);
            cs->ref++;
        }
        Sub(param);
        if (cs != 0) {
            cs->ref--;
            LeaveCriticalSection(cs);
        }
    }
}

// ---------------------------------------------------------------- pool object
// Allocator state embedded at +0 of the object (offsets 0x430..0x50c).
struct MemPool {
    uint8_t  m[0x510];
    void  Init(int, int, int, int, int, int);       // 0x00927860
    void* Alloc(unsigned);                          // 0x009272c0
    void  ShrinkHeap();                             // 0x00927700
    bool  Dispose();                                // 0x00927a50
    void  LazyInit(int, int, int, int, int, int);   // 0x009274d0
    static MemPool* Create(int, int, int, int, int, int);
};

#define F32(o) (*(uint32_t*)((char*)this + (o)))

// @ 0x00927860
void MemPool::Init(int a, int b, int c, int d, int e, int f)
{
    *(uint8_t*)((char*)this + 0x000) = 0;
    F32(0x004) = 0;
    F32(0x008) = 0; F32(0x00c) = 0; F32(0x010) = 0; F32(0x014) = 0;
    F32(0x018) = 0; F32(0x01c) = 0; F32(0x020) = 0; F32(0x024) = 0;
    F32(0x028) = 0; F32(0x02c) = 0;
    operator_new__((char*)this + 0x30, 0, 0x400);
    F32(0x430) = 0; F32(0x434) = 0; F32(0x438) = 0; F32(0x43c) = 0;
    F32(0x440) = 0; F32(0x444) = 0;
    F32(0x448) = 0; F32(0x44c) = 0; F32(0x450) = 0; F32(0x454) = 0;
    F32(0x458) = 0; F32(0x45c) = 0; F32(0x460) = 0; F32(0x464) = 0;
    F32(0x468) = 0;
    *(uint8_t*)((char*)this + 0x46c) = 0;
    *(uint8_t*)((char*)this + 0x46d) = 1;
    F32(0x470) = 0;
    *(uint8_t*)((char*)this + 0x474) = 9;
    *(uint8_t*)((char*)this + 0x475) = 10;
    F32(0x478) = 0; F32(0x47c) = 0; F32(0x480) = 0;
    *(uint8_t*)((char*)this + 0x484) = 0;
    F32(0x488) = 0; F32(0x48c) = 0; F32(0x490) = 0; F32(0x494) = 0;
    *(uint8_t*)((char*)this + 0x498) = 0;
    F32(0x49c) = 0; F32(0x4a0) = 0; F32(0x4a4) = 0; F32(0x4a8) = 0;
    F32(0x4ac) = 0; F32(0x4b0) = 0; F32(0x4b4) = 0x100;
    F32(0x4c8) = 0; F32(0x4cc) = 0; F32(0x4d0) = 0;
    F32(0x4d4) = 0x1000;
    F32(0x4d8) = 0x1000000;
    F32(0x4dc) = 0x400000;
    *(uint8_t*)((char*)this + 0x4e0) = 0;
    F32(0x4e4) = 0;
    F32(0x4e8) = 0; F32(0x4ec) = 0; F32(0x4f0) = 0; F32(0x4f4) = 0;
    F32(0x4f8) = 0; F32(0x4fc) = 0; F32(0x500) = 0; F32(0x504) = 0;
    F32(0x508) = 0;
    *(uint8_t*)((char*)this + 0x50c) = 0;
    F32(0x4b8) = (uint32_t)&Pool_26c20;  // placeholder hook
    F32(0x4bc) = (uint32_t)this;
    F32(0x4c0) = (uint32_t)&Pool_28df0;
    F32(0x4c4) = (uint32_t)this;
    LazyInit(a, b, c, d, e, f);
}

// @ 0x009274d0
void MemPool::LazyInit(int a, int b, int c, int d, int e, int f)
{
    if (*(uint8_t*)this == 0) {
        *(uint8_t*)this = 1;
        if (F32(0x4e4) == 0)
            F32(0x4e4) = (uint32_t)Pool_26100((char*)this + 0x4e8);
        void* cs = (void*)F32(0x4e4);
        if (cs) {
            EnterCriticalSection(cs);
            ((CriSec*)cs)->ref++;
        }
        F32(0x004) = 0x40;
        F32(0x008) = 0; F32(0x00c) = 0; F32(0x010) = 0; F32(0x014) = 0;
        F32(0x018) = 0; F32(0x01c) = 0; F32(0x020) = 0; F32(0x024) = 0;
        F32(0x028) = 0; F32(0x02c) = 0;
        operator_new__((char*)this + 0x30, 0, 0x400);
        F32(0x430) = 0; F32(0x434) = 0; F32(0x438) = 0; F32(0x43c) = 0;
        F32(0x440) = (uint32_t)((char*)this + 0x30);
        F32(0x444) = 0;
        F32(0x460) = (uint32_t)((char*)this + 0x448);
        F32(0x464) = (uint32_t)((char*)this + 0x448);
        F32(0x004) = (F32(0x004) & 1) | 0x48;
        F32(0x468) = 0;
        *(uint8_t*)((char*)this + 0x46c) = 0;
        F32(0x488) = 0; F32(0x48c) = 0;
        F32(0x490) = 0x10000;
        F32(0x494) = 0x20000;
        *(uint8_t*)((char*)this + 0x498) = 0;
        F32(0x49c) = 0; F32(0x4a0) = 0; F32(0x4a4) = 0; F32(0x4a8) = 0;
        F32(0x4a4) = (uint32_t)((char*)this + 0x49c);
        F32(0x4a8) = (uint32_t)((char*)this + 0x49c);
        F32(0x4c8) = 0x40000;
        F32(0x4cc) = 0x10000;
        F32(0x4d0) = F32(0x440);
        F32(0x4d4) = (uint32_t)Pool_28df0();
        if (cs) {
            ((CriSec*)cs)->ref--;
            LeaveCriticalSection(cs);
        }
    }
    if (a != 0 || b != 0)
        Pool_27140(a, b, c, d, e, f);
    if (*(uint8_t*)((char*)this + 0x50c) == 0) {
        *(uint8_t*)((char*)this + 0x50c) = 1;
        for (void** p = (void**)g_poolHookList; p != 0; p = (void**)p[2])
            ((void(__cdecl*)(void*, int, void*))p[0])(this, 1, p[1]);
    }
}

// @ 0x009272c0  (approximate reconstruction of the pool small-bucket allocator)
void* MemPool::Alloc(unsigned n)
{
    uint32_t* walk = (uint32_t*)F32(0x460);
    uint32_t* end  = (uint32_t*)((char*)this + 0x448);
    unsigned got = 0;
    bool fresh = false;
    if (walk != end) {
        for (;;) {
            unsigned avail = walk[2] - walk[1];
            if (n <= avail) {
                got = n;
                if (n < F32(0x4dc)) got = F32(0x4dc);
                if (avail < got) got = avail;
                if (VirtualAlloc((void*)(walk[1] + (int)walk), got, 0x1000, 4) == 0)
                    walk[2] = walk[1];
                break;
            }
            walk = (uint32_t*)walk[6];
            if (walk == end) break;
        }
    }
    uint32_t* node = (uint32_t*)Pool_26c20((char*)this, n, 0);
    if (node == 0) return 0;
    Pool_26840(node, 1);
    fresh = true;
    unsigned size = node[1] & 0x7ffffff8;
    if (n < size) {
        node[1] = n | 1;
        uint32_t* rem = (uint32_t*)((char*)node + n);
        size -= n;
        rem[0] = n;
        rem[1] = size;
        *(uint32_t*)((char*)rem + size) = size;
        if (fresh) {
            F32(0x440) = (uint32_t)rem;
            rem[3] = (uint32_t)rem;
            *(uint32_t*)(F32(0x440) + 8) = *(uint32_t*)(F32(0x440) + 0xc);
            if (*(uint8_t*)((char*)this + 0x46c) == 0)
                F32(0x468) = ((*(uint32_t*)(F32(0x440) + 4) >> 1) & 0x3ffffffc) + F32(0x440);
        } else {
            uint32_t tail = F32(0x3c);
            rem[2] = (uint32_t)((char*)this + 0x30);
            rem[3] = tail;
            F32(0x3c) = (uint32_t)rem;
            *(uint32_t*)(tail + 8) = (uint32_t)rem;
        }
    }
    return node;
}

// @ 0x00927700  (approximate: consolidate free chunks)
void MemPool::ShrinkHeap()
{
    uint32_t top = F32(0x004);
    if (top == 0) {
        LazyInit(0, 0, 1, 0, 0, 0);
        return;
    }
    uint32_t** slot = (uint32_t**)((char*)this + 8);
    uint32_t** last = (uint32_t**)((char*)this + (top >> 3) * 4);
    do {
        uint32_t* p = *slot;
        if (p) {
            *slot = 0;
            while (p) {
                uint32_t* next = (uint32_t*)p[3];
                Pool_26840(p, 0);
                p = next;
            }
        }
        ++slot;
    } while (slot != last);
    F32(0x004) &= 0xfffffffe;
}

// @ 0x00927a50  (approximate: teardown)
bool MemPool::Dispose()
{
    if (*(uint8_t*)((char*)this + 0x50c) == 1) {
        *(uint8_t*)((char*)this + 0x50c) = 0;
        for (void** p = (void**)g_poolHookList; p != 0; p = (void**)p[2])
            ((void(__cdecl*)(void*, int, void*))p[0])(this, 0, p[1]);
    }
    if (F32(0x4e4) != 0)
        Pool_26120((void*)F32(0x4e4));
    if (*(uint8_t*)this != 0) {
        *(uint8_t*)this = 0;
        if (Pool_267e0() != 0)
            ShrinkHeap();
        while (F32(0x4a8) != (uint32_t)((char*)this + 0x49c)) {
            void* v = Pool_26790(Pool_267c0((void*)F32(0x4a8)));
            Pool_26fd0(v, 0);
        }
        while (F32(0x464) != (uint32_t)((char*)this + 0x448)) {
            void* v = (void*)F32(0x464);
            Pool_26a10(v);
            Pool_26a60(v, 1);
        }
        F32(0x440) = (uint32_t)Pool_267d0();
        F32(0x468) = 0;
        *(uint8_t*)((char*)this + 0x46c) = 0;
    }
    if (F32(0x4e4) != 0) {
        void* v = (void*)F32(0x4e4);
        F32(0x4e4) = 0;
        Pool_26140(v);
        Pool_26340(v);
    }
    return true;
}

MemPool* MemPool::Create(int a, int b, int c, int d, int e, int f)
{
    MemPool* p = (MemPool*)operator_new(sizeof(MemPool), "EASTL", 0, 0, "allocator.h", 0xd1);
    p->Init(a, b, c, d, e, f);
    return p;
}