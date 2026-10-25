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
extern "C" void* __cdecl Pool_26930();               // 0x00926930
extern "C" void* __cdecl Pool_28de0();               // 0x00928de0
// 0x00927140 ?CreateSegment@FreePool@Allocator@EA@@QAE_NPAIIDDII@Z  (thiscall, ecx=this)
typedef void (__thiscall* PoolCreateSegmentFn)(void*, unsigned*, unsigned, int, int, unsigned, unsigned);

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
    bool  LazyInit(int, int, int, int, int, int);   // 0x009274d0
    static MemPool* Create(int, int, int, int, int, int);
};

#define F32(o) (*(uint32_t*)((char*)this + (o)))

// Shared tail of Alloc (original LAB_00927445): split the chunk and link the remainder.
static __forceinline void* Pool_FinishChunk(MemPool* self, uint32_t* chunk, unsigned n, bool fresh)
{
    uint32_t size = chunk[1] & 0x7ffffff8;
    if (n < size) {
        chunk[1] = n | 1;
        uint32_t* rem = (uint32_t*)((char*)chunk + n);
        size -= n;
        rem[0] = n;
        rem[1] = size;
        *(uint32_t*)((char*)rem + size) = size;
        uint32_t* top = *(uint32_t**)((char*)self + 0x440);
        if (fresh) {
            *(uint32_t**)((char*)self + 0x440) = rem;
            rem[3] = (uint32_t)rem;
            *(uint32_t*)(top + 8) = *(uint32_t*)(top + 0xc);
            if (*(uint8_t*)((char*)self + 0x46c) == 0)
                *(uint32_t*)((char*)self + 0x468) =
                    ((*(uint32_t*)((char*)top + 4) >> 1) & 0x3ffffffc) + (uint32_t)top;
        } else {
            uint32_t tail = *(uint32_t*)((char*)self + 0x3c);
            rem[2] = (uint32_t)((char*)self + 0x30);
            rem[3] = tail;
            *(uint32_t*)((char*)self + 0x3c) = (uint32_t)rem;
            *(uint32_t*)(tail + 8) = (uint32_t)rem;
        }
    }
    return chunk;
}

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
    F32(0x4ac) = 0; F32(0x4b0) = 0;
    F32(0x4b4) = 0x100;
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
    F32(0x4b8) = (uint32_t)&Pool_26930;   // 0x00926930
    F32(0x4bc) = (uint32_t)this;
    F32(0x4c0) = (uint32_t)&Pool_28de0;   // 0x00928de0
    F32(0x4c4) = (uint32_t)this;
    LazyInit(a, b, c, d, e, f);
}

// @ 0x009274d0
bool MemPool::LazyInit(int a, int b, int c, int d, int e, int f)
{
    int* bin;
    if (*(uint8_t*)this == 0) {
        *(uint8_t*)this = 1;
        if (F32(0x4e4) == 0)
            F32(0x4e4) = (uint32_t)Pool_26100((char*)this + 0x4e8);
        CriSec* cs = (CriSec*)F32(0x4e4);
        if (cs != 0) {
            EnterCriticalSection(cs);
            cs->ref++;
        }
        F32(0x004) = 0x40;
        F32(0x008) = 0; F32(0x00c) = 0; F32(0x010) = 0; F32(0x014) = 0;
        F32(0x018) = 0; F32(0x01c) = 0; F32(0x020) = 0; F32(0x024) = 0;
        F32(0x028) = 0; F32(0x02c) = 0;
        operator_new__((char*)this + 0x30, 0, 0x400);
        /* 0x7f bin headers, each self-linked at +8/+0xc, step 8 */
        bin = (int*)((char*)this + 0x30);
        for (int i = 0x7f; i != 0; --i) {
            bin[2] = (int)bin;
            bin[3] = (int)bin;
            bin += 2;
        }
        F32(0x430) = 0; F32(0x434) = 0; F32(0x438) = 0; F32(0x43c) = 0;
        F32(0x440) = (uint32_t)((char*)this + 0x30);
        F32(0x444) = 0;
        F32(0x448) = 0; F32(0x44c) = 0; F32(0x450) = 0; F32(0x454) = 0;
        F32(0x458) = 0; F32(0x45c) = 0; F32(0x460) = 0; F32(0x464) = 0;
        F32(0x460) = (uint32_t)((char*)this + 0x448);
        F32(0x464) = (uint32_t)((char*)this + 0x448);
        F32(0x004) = (F32(0x004) & 1) | 0x48;
        bin = (int*)((char*)this + 0x49c);
        F32(0x468) = 0;
        *(uint8_t*)((char*)this + 0x46c) = 0;
        F32(0x488) = 0; F32(0x48c) = 0;
        F32(0x490) = 0x10000;
        F32(0x494) = 0x20000;
        *(uint8_t*)((char*)this + 0x498) = 0;
        bin[0] = 0; bin[1] = 0; bin[2] = 0; bin[3] = 0;
        F32(0x4a4) = (uint32_t)((char*)this + 0x49c);
        F32(0x4a8) = (uint32_t)((char*)this + 0x49c);
        F32(0x4c8) = 0x40000;
        F32(0x4cc) = 0x10000;
        F32(0x4d0) = F32(0x440);
        F32(0x4d4) = (uint32_t)Pool_28df0();
        if (cs != 0) {
            cs->ref--;
            LeaveCriticalSection(cs);
        }
    }
    if (a != 0 || b != 0)
        ((PoolCreateSegmentFn)0x00927140)(this, (unsigned*)a, (unsigned)b, c, d, e, f);
    if (*(uint8_t*)((char*)this + 0x50c) == 0) {
        *(uint8_t*)((char*)this + 0x50c) = 1;
        for (void** p = (void**)g_poolHookList; p != 0; p = (void**)p[2])
            ((void(__cdecl*)(void*, int, void*))p[0])(this, 1, p[1]);
    }
    return true;
}

// @ 0x009272c0
void* MemPool::Alloc(unsigned n)
{
    uint32_t* seg    = *(uint32_t**)((char*)this + 0x460);
    uint32_t* sentin = (uint32_t*)((char*)this + 0x448);
    uint32_t got = 0;
    bool fresh = false;
    uint32_t* chunk = 0;

    if (seg != sentin) {
        do {
            if (n <= (uint32_t)(seg[2] - seg[1])) {
                got = n;
                if (n < F32(0x4dc)) got = F32(0x4dc);
                uint32_t avail = seg[2] - seg[1];
                if (avail < got) got = avail;
                if (VirtualAlloc((void*)(seg[1] + (int)seg), got, 0x1000, 4) == 0)
                    seg[2] = seg[1];
                break;
            }
            seg = (uint32_t*)seg[6];
        } while (seg != sentin);

        if (seg != sentin) {
            uint32_t used = seg[1];
            uint32_t size = got;
            if (used != 0) {
                uint32_t* prev = (uint32_t*)((uint32_t)seg + used - 0x10);
                if ((*(uint32_t*)((uint32_t)seg + used - 0xc) & 1) == 0) {
                    chunk = (uint32_t*)((uint32_t)prev - *prev);   // merge with prev
                    *(uint32_t*)(chunk[2] + 0xc) = chunk[3];
                    *(uint32_t*)(chunk[3] + 8)   = chunk[2];
                    size = *prev + got;
                    chunk[1] = size | 1;
                    fresh = (chunk == *(uint32_t**)((char*)this + 0x440));
                } else {
                    prev[1] = got | 1;
                    chunk = prev;
                }
                uint32_t* bound = (uint32_t*)((char*)chunk + size);
                bound[0] = size;
                bound[1] = 8;
                bound[2] = 8;
                bound[3] = 9;
            } else {
                chunk = (uint32_t*)(((uint32_t)seg + 0x27) & ~7u);   // (seg+39)&~7
                uint32_t tail = (uint32_t)seg + (got - (uint32_t)chunk);
                uint32_t tsz  = tail & ~7u;
                uint32_t tprev = tsz - 0x10;
                seg[0] = (uint32_t)chunk;                    // seg size
                chunk[1] = (tail & 0x80000007u) | 1 | tprev;
                chunk[0] = 0;
                *(uint32_t*)(tprev + (uint32_t)chunk) = tprev;
                *(uint32_t*)((uint32_t)chunk + tsz - 0xc) = 8;
                *(uint32_t*)((uint32_t)chunk + tsz - 8) = 8;
                *(uint32_t*)((uint32_t)chunk + tsz - 4) = 9;
                Pool_26840(chunk, 1);
                fresh = true;
            }
            seg[1] = seg[1] + got;
        }
    }

    if (chunk == 0) {
        chunk = (uint32_t*)Pool_26c20((char*)this, n, 0);
        if (chunk == 0) return 0;
        Pool_26840(chunk, 1);
        fresh = true;
    }
    return Pool_FinishChunk(this, chunk, n, fresh);
}

// @ 0x00927700
void MemPool::ShrinkHeap()
{
    uint32_t hdr = F32(0x004);
    if (hdr == 0) {
        LazyInit(0, 0, 1, 0, 0, 0);
        return;
    }
    uint32_t** slot = (uint32_t**)((char*)this + 8);
    uint32_t** last = (uint32_t**)((char*)this + (hdr >> 3) * 4);
    do {
        uint32_t* chunk = (uint32_t*)*slot;
        if (chunk != 0) {
            *slot = 0;
            uint32_t* next;
            do {
                chunk[1] &= 0x7ffffffb;                       // clear prev-inuse hints
                next = (uint32_t*)chunk[3];
                uint32_t sz  = chunk[1] & 0x7ffffff8;         // this chunk's size
                uint32_t* fwd = (uint32_t*)((char*)chunk + sz);
                uint32_t fsz = *(uint32_t*)((char*)fwd + 4) & 0x7ffffff8;
                if ((chunk[1] & 1) == 0) {                    // previous chunk free
                    uint32_t psz = *chunk;
                    sz += psz;
                    chunk = (uint32_t*)((char*)chunk - psz);
                    chunk[1] = sz | 1;
                    *fwd = sz;
                    *(uint32_t*)(chunk[2] + 0xc) = chunk[3];
                    *(uint32_t*)(chunk[3] + 8)   = chunk[2];
                }
                if ((*(uint8_t*)((char*)fwd + 4 + fsz) & 1) == 0) {   // chunk after fwd free
                    *(uint32_t*)(fwd[2] + 0xc) = fwd[3];
                    *(uint32_t*)(fwd[3] + 8)   = fwd[2];
                    sz += fsz;
                    chunk[1] = sz | 1;
                    *(uint32_t*)((char*)chunk + sz) = sz;
                } else {
                    fwd[1] &= 0xfffffffe;
                    *fwd = sz;
                }
                if (chunk == *(uint32_t**)((char*)this + 0x440) ||
                    fwd   == *(uint32_t**)((char*)this + 0x440)) {
                    *(uint32_t**)((char*)this + 0x440) = chunk;
                    chunk[3] = (uint32_t)chunk;
                    chunk[2] = (uint32_t)chunk;
                    chunk[1] = sz | 1;
                    *(uint32_t*)((char*)chunk + sz) = sz;
                    if (*(uint8_t*)((char*)this + 0x46c) == 0) {
                        uint32_t* t = *(uint32_t**)((char*)this + 0x440);
                        *(uint32_t*)((char*)this + 0x468) =
                            ((*(uint32_t*)((char*)t + 4) >> 1) & 0x3ffffffc) + (uint32_t)t;
                    }
                } else {
                    uint32_t tail = F32(0x3c);
                    chunk[2] = (uint32_t)((char*)this + 0x30);
                    chunk[3] = tail;
                    F32(0x3c) = (uint32_t)chunk;
                    *(uint32_t*)(tail + 8) = (uint32_t)chunk;
                }
                chunk = next;
            } while (next != 0);
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