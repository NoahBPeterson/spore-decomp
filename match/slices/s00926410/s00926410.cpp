// Slice s00926410 (bfs2 #23), 32-bit MSVC 2008.
// EA::Allocator (FixedAllocatorBase / StackAllocator) and fixed-hashtable helpers.
// Class layouts from the 2008 dev PDB.
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
typedef unsigned int uint32;

extern "C" void FUN_00928de0(void* a, void* b);   // 0x00928de0
extern "C" void FUN_00928dd0(void);               // 0x00928dd0

namespace EA { namespace Allocator {

// ===========================================================================
// FixedAllocatorBase
// ===========================================================================
struct CoreBlock;
struct Chunk;

typedef void* (__cdecl *CoreAllocFn)(uint32 size, void* context);
typedef void  (__cdecl *CoreFreeFn)(void* p, void* context);

extern "C" void* FUN_006abeb0(uint32 size, void* context);  // 0x006abeb0
extern "C" void  FUN_00f47410(void* p, void* context);       // 0x00f47410

class FixedAllocatorBase {
public:
    uint32 mnObjectSize;                  // +0x00
    uint32 mnObjectAlignment;             // +0x04
    uint32 mnCountPerCoreBlock;           // +0x08
    CoreBlock* mpHeadCoreBlock;           // +0x0c
    Chunk* mpHeadChunk;                   // +0x10
    CoreAllocFn mpCoreAllocationFunction; // +0x14
    CoreFreeFn  mpCoreFreeFunction;       // +0x18
    void* mpCoreFunctionContext;          // +0x1c

    bool SplitCore(CoreBlock* pCoreBlock);   // @ 0x009265f0
    bool AddCore(CoreBlock* pCoreBlock, uint32 nSize);  // @ 0x00926650
    bool Init(uint32 objectSize, uint32 objectAlignment, uint32 countPerCoreBlock,
              CoreBlock* pCoreBlock, uint32 nSize, CoreAllocFn allocFn, CoreFreeFn freeFn,
              void* context);                  // @ 0x009266b0
    FixedAllocatorBase(uint32 objectSize, uint32 objectAlignment, uint32 countPerCoreBlock,
                       CoreBlock* pCoreBlock, uint32 nSize, CoreAllocFn allocFn, CoreFreeFn freeFn,
                       void* context);         // @ 0x00926720
};

struct CoreBlock {
    CoreBlock* mpNext;   // +0x00
    uint32 mnSize;       // +0x04
    char mData[4];       // +0x08
};

struct Chunk {
    Chunk* mpNext;       // +0x00
};

// @ 0x009265f0
bool FixedAllocatorBase::SplitCore(CoreBlock* pCoreBlock)
{
    Chunk* pChunk = (Chunk*)((mnObjectAlignment + (uint32)pCoreBlock + 7) & ~(mnObjectAlignment - 1));
    char* pEnd = (char*)pCoreBlock + pCoreBlock->mnSize - 2 * mnObjectSize;
    if (pChunk <= (Chunk*)pEnd) {
        mpHeadChunk = pChunk;
        do {
            Chunk* pNext = (Chunk*)((char*)pChunk + mnObjectSize);
            pChunk->mpNext = pNext;
            pChunk = pNext;
        } while (pChunk <= (Chunk*)pEnd);
        pChunk->mpNext = 0;
        return true;
    }
    return false;
}

// @ 0x00926650
bool FixedAllocatorBase::AddCore(CoreBlock* pCoreBlock, uint32 nSize)
{
    if (pCoreBlock == 0) {
        while (nSize == 0)
            nSize = (mnCountPerCoreBlock + 2) * mnObjectSize + 0xc;
        if (nSize == 0xffffffff)
            goto fail;
        pCoreBlock = (CoreBlock*)(*mpCoreAllocationFunction)(nSize, mpCoreFunctionContext);
        if (pCoreBlock == 0)
            goto fail;
    }
    pCoreBlock->mpNext = mpHeadCoreBlock;
    pCoreBlock->mnSize = nSize;
    mpHeadCoreBlock = pCoreBlock;
    return SplitCore(pCoreBlock);
fail:
    return false;
}

// @ 0x009266b0
bool FixedAllocatorBase::Init(uint32 objectSize, uint32 objectAlignment, uint32 countPerCoreBlock,
                              CoreBlock* pCoreBlock, uint32 nSize, CoreAllocFn allocFn,
                              CoreFreeFn freeFn, void* context)
{
    if (objectAlignment <= 0)
        objectAlignment = mnObjectAlignment;
    mnObjectAlignment = objectAlignment;
    if (objectSize != 0) {
        if (objectSize < 4)
            objectSize = 4;
        mnObjectSize = (objectSize - 1 + objectAlignment) & ~(objectAlignment - 1);
    }
    if (countPerCoreBlock != 0)
        mnCountPerCoreBlock = countPerCoreBlock;
    if (allocFn != 0)
        mpCoreAllocationFunction = allocFn;
    if (freeFn != 0)
        mpCoreFreeFunction = freeFn;
    mpCoreFunctionContext = context;
    if (mpHeadCoreBlock == 0)
        return AddCore(pCoreBlock, nSize);
    return false;
}

// @ 0x00926720
FixedAllocatorBase::FixedAllocatorBase(uint32 objectSize, uint32 objectAlignment,
                                       uint32 countPerCoreBlock, CoreBlock* pCoreBlock,
                                       uint32 nSize, CoreAllocFn allocFn, CoreFreeFn freeFn,
                                       void* context)
{
    mnObjectSize = objectSize;
    mpHeadCoreBlock = 0;
    mpHeadChunk = 0;
    mpCoreFunctionContext = 0;
    mnObjectAlignment = 8;
    mnCountPerCoreBlock = 0x80;
    mpCoreAllocationFunction = &FUN_006abeb0;
    mpCoreFreeFunction = &FUN_00f47410;
    Init(objectSize, objectAlignment, countPerCoreBlock, pCoreBlock, nSize, allocFn, freeFn, context);
}

// ===========================================================================
// small helpers
// ===========================================================================

// @ 0x00926790
int FUN_00926790(int p)
{
    return p + 8;
}

// @ 0x009267a0
uint32 FUN_009267a0(int p)
{
    uint32 a = (uint32)(p + 0xb);
    if (a > 0x10)
        return a & 0xfffffff8;
    return 0x10;
}

// @ 0x009267c0
int FUN_009267c0(int* p)
{
    return (int)p - *p;
}

// @ 0x009267e0
uint32 __fastcall FUN_009267e0(int p)
{
    return *(uint32*)(p + 4) & 1;
}

// @ 0x009267f0
int FUN_009267f0(uint32 v)
{
    if (v >> 6 <= 0x20)
        return (v >> 6) + 0x38;
    if (v >> 9 <= 0x14)
        return (v >> 9) + 0x5b;
    if (v >> 0xc <= 0xa)
        return (v >> 0xc) + 0x6e;
    if (v >> 0xf <= 4)
        return (v >> 0xf) + 0x77;
    if (v >> 0x12 <= 2)
        return (v >> 0x12) + 0x7c;
    return 0x7e;
}

// @ 0x00926a10
void __stdcall FUN_00926a10(int p)
{
    *(int*)(*(int*)(p + 0x18) + 0x1c) = *(int*)(p + 0x1c);
    *(int*)(*(int*)(p + 0x1c) + 0x18) = *(int*)(p + 0x18);
}

// ===========================================================================
// fixed string pool (hashtable for interned strings)
// ===========================================================================
struct Pool {
    char pad0[0x448];
    void* end;      // +0x448
    char pad1[0x14];
    void* cur;      // +0x460

    void* Find(unsigned p);                       // @ 0x00926a30
    bool  Contains(unsigned p);                   // @ 0x00926ab0
    bool  FreeBlock(void* block, char flag);      // @ 0x00926a60
};

// @ 0x00926a30
void* Pool::Find(unsigned p)
{
    void* e = end;
    void* c = cur;
    while (c != e) {
        if (p >= (unsigned)c && p < (unsigned)c + *(int*)((char*)c + 4))
            return c;
        c = *(void**)((char*)c + 0x18);
    }
    return 0;
}

// @ 0x00926ab0
bool Pool::Contains(unsigned p)
{
    if ((*(uint32*)(p + 4) & 0x7ffffff8) < 0x10) {
        void* b = Find(p);
        if (b != 0 && (unsigned)(*(int*)((char*)b + 4) + (int)b - 0x10) <= p)
            return true;
    }
    return false;
}

// @ 0x00926a60
bool Pool::FreeBlock(void* block, char flag)
{
    if (*(char*)((char*)block + 0xd) != 0 ||
        (flag != 0 && *(char*)((char*)block + 0xe) != 0)) {
        if (*(void**)((char*)block + 0x10) != 0) {
            (*(void(__cdecl**)(void*, void*, void*, void*))(*(void**)((char*)block + 0x10)))
                (this, block, *(void**)((char*)block + 8), *(void**)((char*)block + 0x14));
            return true;
        }
        VirtualFree(block, 0, 0x8000);
        return true;
    }
    return false;
}

// ===========================================================================
// StackAllocator / stack helpers
// ===========================================================================

// @ 0x009268f0
void FUN_009268f0(int p, uint32 v)
{
    uint32 h = *(uint32*)(p + 4) & 0x7ffffff8;
    uint32 n = (h - 9) & 0xfffffff8;
    *(uint32*)(p + 4) = (*(uint32*)(p + 4) & 0x80000007) | n;
    *(uint32*)(n + p) = n;
    *(uint32*)(n + p + 4) = v | 8;
    *(uint32*)(n + p + 8) = 8;
    *(uint32*)(n + p + 0xc) = 9;
}

// @ 0x00926930
void FUN_00926930(int a1, void* a2)
{
    FUN_00928de0(*(void**)(a1 + 0xc), a2);
    FUN_00928de0((void*)0x1401b70, a2);
    FUN_00928dd0();
}

// ===========================================================================
// hashtable/list helpers
// ===========================================================================

// @ 0x00926410
void __fastcall FUN_00926410(void* self)
{
    void* p = *(void**)((char*)self + 0x30);
    while (p != 0) {
        *(void**)((char*)self + 0x30) = *(void**)p;
        (*(void(__cdecl**)(void*))(*(void**)((char*)self + 0x2c)))(p);
        p = *(void**)((char*)self + 0x30);
    }
    *(int*)((char*)self + 0x34) = 0;
    *(int*)((char*)self + 0x30) = 0;
    void* cs = *(void**)self;
    if (cs != 0) {
        DeleteCriticalSection((LPCRITICAL_SECTION)cs);
        *(void**)self = 0;
    }
}

// @ 0x009265b0
bool __fastcall FUN_009265b0(void* self)
{
    void* p = *(void**)((char*)self + 0x0c);
    while (p != 0) {
        void* q = *(void**)((char*)self + 0x0c);
        *(void**)((char*)self + 0x0c) = *(void**)q;
        (*(void(__cdecl**)(void*, void*))(*(void**)((char*)self + 0x18)))
            (q, *(void**)((char*)self + 0x1c));
        p = *(void**)((char*)self + 0x0c);
    }
    *(int*)((char*)self + 0x10) = 0;
    return true;
}

// ===========================================================================
// large functions: behaviourally-shaped skeletons (partial)
// ===========================================================================
void FUN_00926460(void* self, void* name) { (void)self; (void)name; }
void FUN_00926840(void* self, void* node, char flag) { (void)self; (void)node; (void)flag; }
void FUN_009268b0(void* self, void* node, uint32 v) { (void)self; (void)node; (void)v; }
void FUN_00926960(void* self, void* a, uint32 b, char c) { (void)self; (void)a; (void)b; (void)c; }
void FUN_00926af0(void* self, void* a, int b, uint32 c, int d, int e, char f)
{
    (void)self; (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
}
void FUN_00926c20(void* self) { (void)self; }
void FUN_00926db0(void* self) { (void)self; }
void FUN_00926f10(void* self) { (void)self; }
void FUN_00927140(void* self) { (void)self; }

// ===========================================================================
// 0x00926fd0: the heap's free(): fast-bin push, boundary-tag coalescing, top handling,
// mmap'd (VirtualAlloc) chunk release and trim (dlmalloc layout; sizes in the low bits of head).
// ===========================================================================
struct FreeChunk {
    uint32 prev_size;   // +0x00
    uint32 head;        // +0x04 (size | flags: 1 = prev in use, 2 = mapped)
    FreeChunk* fd;      // +0x08
    FreeChunk* bk;      // +0x0c
};

static inline void UnlinkChunk(FreeChunk* c)
{
    FreeChunk* fd = c->fd;
    FreeChunk* bk = c->bk;
    fd->bk = bk;
    c->bk->fd = c->fd;
}

struct FreePool {
    uint32 bins0;                 // +0x00 (fast bins are indexed by chunk size >> 3)
    uint32 mMaxFast;              // +0x04
    char pad8[0x30 - 8];
    FreeChunk mUnsorted;          // +0x30 (list sentinel: fd +0x38, bk +0x3c)
    char pad40[0x440 - 0x40];
    FreeChunk* mTop;              // +0x440
    char pad444[0x468 - 0x444];
    FreeChunk* mLimit;            // +0x468
    char pad46c[0x488 - 0x46c];
    int mMapCount;                // +0x488
    int mMapBytes;                // +0x48c
    char pad490[0x4c8 - 0x490];
    uint32 mTrimThreshold;        // +0x4c8
    uint32 mTrimArg;              // +0x4cc

    void Free(void* mem);                       // 0x00926fd0 (ret 4)
    void SetTop(FreeChunk* p, uint32 size);     // 0x009268b0 (ret 8)
    bool Contains(unsigned p);                  // 0x00926ab0
    void Trim(uint32 arg);                      // 0x00926db0 (ret 4)
};

// @ 0x00926fd0
void FreePool::Free(void* mem)
{
    if (mem == 0)
        return;
    char* m = (char*)mem;
    uint32 head = *(uint32*)(m - 4);
    uint32 maxFast = mMaxFast;
    m -= 8;
    FreeChunk* p = (FreeChunk*)m;
    uint32 size = head & 0x7ffffff8;
    if (size <= maxFast) {
        bool inRange = true;
        if (mLimit != 0)
            inRange = p < mLimit;
        if (inRange) {
            mMaxFast |= 1;
            FreeChunk** bin = (FreeChunk**)this + (size >> 3);
            FreeChunk* old = *bin;
            p->head |= 0x80000004;
            p->bk = old;
            *bin = p;
            return;
        }
    }
    if ((head & 2) == 0) {
        FreeChunk* next = (FreeChunk*)((char*)p + size);
        uint32 nextSize = next->head & 0x7ffffff8;
        if ((head & 1) == 0) {
            uint32 prevSize = p->prev_size;
            size += prevSize;
            p = (FreeChunk*)((char*)p - prevSize);
            p->head = size | 1;
            next->prev_size = size;
            UnlinkChunk(p);
        }
        if (((char*)next)[nextSize + 4] & 1) {
            next->head &= ~1u;
            next->prev_size = size;
        } else {
            UnlinkChunk(next);
            size += nextSize;
            p->head = size | 1;
            *(uint32*)((char*)p + size) = size;
        }
        if (p == mTop || next == mTop) {
            mTop = p;
            SetTop(p, size);
        } else {
            FreeChunk* last = mUnsorted.bk;
            p->fd = &mUnsorted;
            p->bk = last;
            mUnsorted.bk = p;
            last->fd = p;
        }
        if (size >= 0x10000 && Contains((unsigned)((char*)p + size)) && size >= mTrimThreshold)
            Trim(mTrimArg);
    } else {
        uint32 offset = p->prev_size;
        FreeChunk* link = (FreeChunk*)((char*)p + size + 8);
        FreeChunk* nx = ((FreeChunk**)link)[0];
        FreeChunk* pv = ((FreeChunk**)link)[1];
        nx->bk = pv;
        pv->fd = nx;
        mMapBytes -= offset + 0x10 + size;
        mMapCount -= 1;
        VirtualFree((char*)p - offset, 0, 0x8000);
    }
}

}}
