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
    void* e = (char*)this + 0x448;   // end is an embedded sentinel node, not a stored pointer
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
            ((void(__cdecl*)(void*, void*, void*, void*))(*(void**)((char*)block + 0x10)))
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
    while (*(void**)((char*)self + 0x0c) != 0) {
        void* q = *(void**)((char*)self + 0x0c);
        *(void**)((char*)self + 0x0c) = *(void**)q;
        ((void(__cdecl*)(void*, void*))(*(void**)((char*)self + 0x18)))
            (q, *(void**)((char*)self + 0x1c));
    }
    *(int*)((char*)self + 0x10) = 0;
    return true;
}

// ===========================================================================
// 0x00926460: interned-string pool. Hash-chained lookup; on a miss a node
// (chain link + hash + inline copy of the string) is carved out of the pool's
// current block, growing the block list through the core allocator first.
// ===========================================================================
extern "C" uint32 __stdcall FUN_00926190(const char* s);    // 0x00926190 (string hash)
extern "C" void   FUN_011e0744(void* dst, const char* s,
                               uint32 count);               // 0x011e0744 (eastl char-buffer range insert)
extern "C" char   DAT_013ec47c;                             // 0x013ec47c (shared empty string)

struct StrNode {
    StrNode* mpNext;   // +0x00
    uint32   mHash;    // +0x04
    void*    mpStr;    // +0x08 (points at +0x0c)
};

struct StringPool {
    void*     mpLock;        // +0x00 (LPCRITICAL_SECTION)
    char      pad04[0x34 - 0x04];
    void*     mpBlocks;      // +0x34 (current block; blocks chain through their first dword)
    StrNode** mpBuckets;     // +0x38
    uint32    mCapacity;     // +0x3c
    uint32    mUsed;         // +0x40
    uint32    mBucketCount;  // +0x44
    uint32    mCount;        // +0x48
    char      pad4c[0x4d - 0x4c];
    char      mCanGrow;      // +0x4d

    bool  Equals(const char* a, const char* b, uint32 n);   // 0x009261f0
    void* Intern(const char* s);                            // 0x00926460
};

// @ 0x00926460
void* StringPool::Intern(const char* s)
{
    if (s == 0)
        return 0;
    if (s[0] == '\0')
        return &DAT_013ec47c;
    uint32 hash = FUN_00926190(s);
    uint32 len = 0;
    do {
        ++len;
    } while (s[len - 1] != '\0');
    void* lock = mpLock;
    if (lock != 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)lock);
        ((uint32*)lock)[6] += 1;
    }
    StrNode** slot = &mpBuckets[hash % mBucketCount];
    StrNode* node = *slot;
    StrNode* found = 0;
    while (node != 0) {
        if (node->mHash == hash && Equals(s, (const char*)node->mpStr, len)) {
            found = node;
            break;
        }
        node = node->mpNext;
    }
    if (found == 0) {
        uint32 need = (len + 0x10) & 0xfffffffc;
        if (mUsed + need > mCapacity) {
            if (mCanGrow == 0) {
                if (lock != 0) {
                    ((uint32*)lock)[6] -= 1;
                    LeaveCriticalSection((LPCRITICAL_SECTION)lock);
                }
                return &DAT_013ec47c;
            }
            void* block = FUN_006abeb0(mCapacity, 0);
            *(uint32*)block = 0;
            *(uint32*)mpBlocks = (uint32)block;
            mpBlocks = block;
            mUsed = 4;
        }
        mCount += 1;
        StrNode* p = (StrNode*)((char*)mpBlocks + mUsed);
        mUsed += need;
        p->mHash = hash;
        char* str = (char*)p + 0xc;
        p->mpStr = str;
        FUN_011e0744(str, s, len);
        p->mpNext = *slot;
        *slot = p;
        found = (StrNode*)str;
    }
    void* result = (void*)found;
    if (lock != 0) {
        ((uint32*)lock)[6] -= 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)lock);
    }
    return result;
}

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

// dlmalloc-style segment-list node (VirtualAlloc'd arena descriptor).
struct SegNode {
    uint32   mAlignedBase;  // +0x00 (aligned chunk base inside the arena)
    uint32   mSizeA;        // +0x04 (arena size, shrinks during trim)
    uint32   mSizeB;        // +0x08 (requested size)
    unsigned char mFlagC;   // +0x0c
    unsigned char mFlagD;   // +0x0d
    unsigned char mFlagE;   // +0x0e
    unsigned char mFlagF;   // +0x0f
    uint32   mUnk10;        // +0x10
    uint32   mUnk14;        // +0x14
    SegNode* mpNext;        // +0x18
    SegNode* mpPrev;        // +0x1c
};

struct FreePool {
    uint32 bins0;                 // +0x00 (fast bins are indexed by chunk size >> 3)
    uint32 mMaxFast;              // +0x04
    char pad8[0x30 - 8];
    FreeChunk mUnsorted;          // +0x30 (bin sentinel #1: fd +0x38, bk +0x3c)
    char pad40[0x430 - 0x40];
    uint32 mSmallMap;             // +0x430 (smallbin bit map)
    char pad434[0x440 - 0x434];
    FreeChunk* mTop;              // +0x440
    FreeChunk* mDv;               // +0x444 (designated victim)
    char pad448[0x460 - 0x448];   // +0x448 segment-list sentinel
    SegNode* mSegHead;            // +0x460 (= sentinel.mpNext)
    SegNode* mSegTail;            // +0x464 (= sentinel.mpPrev)
    FreeChunk* mLimit;            // +0x468
    char mTrimCheck;              // +0x46c
    char pad46d[0x488 - 0x46d];
    int mMapCount;                // +0x488
    int mMapBytes;                // +0x48c
    char pad490[0x498 - 0x490];
    char mNoCommit;               // +0x498 (use MEM_NOCOMMIT instead of reserve+commit)
    char pad499[0x49c - 0x499];
    FreeChunk mMmapList;          // +0x49c (mmap'd arena list sentinel: fd +0x4a4, bk +0x4a8)
    char pad4ac[0x4c8 - 0x4ac];
    uint32 mTrimThreshold;        // +0x4c8
    uint32 mTrimArg;              // +0x4cc
    char pad4d0[0x4d4 - 0x4d0];
    uint32 mPageSize;             // +0x4d4
    uint32 mGrainSize;            // +0x4d8
    uint32 mMinSegmentSize;       // +0x4dc
    char pad4e0[0x4e4 - 0x4e0];
    void* mpLock;                 // +0x4e4 (LPCRITICAL_SECTION)

    void Free(void* mem);                       // 0x00926fd0 (ret 4)
    void SetTop(FreeChunk* p, uint32 size);     // 0x009268b0 (ret 8)
    bool Contains(unsigned p);                  // 0x00926ab0
    int  Trim(uint32 arg);                      // 0x00926db0 (ret 4)
    void SetTopAndLink(FreeChunk* p, char flag);             // 0x00926840 (ret 8)
    void BinInsert(FreeChunk* p, uint32 size, char unlink);  // 0x00926960 (ret 0xc)
    void SplitChunk(FreeChunk* p, int size, uint32 align,
                    uint32 a5, uint32 a6, char flag);        // 0x00926af0 (ret 0x18)
    SegNode* NewSegment(uint32 size, char flag);             // 0x00926c20 (ret 8)
    void* AllocSegment(uint32 nBytes);                       // 0x00926f10 (ret 4)
    bool CreateSegment(uint32* base, uint32 size, char a4,
                       char a5, uint32 a6, uint32 a7);       // 0x00927140 (ret 0x18)
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

// ===========================================================================
// 0x00926840: install p as the top chunk. When there was a different previous
// top and `flag` is set, the previous top is appended to the unsorted bin.
// ===========================================================================
// @ 0x00926840
void FreePool::SetTopAndLink(FreeChunk* p, char flag)
{
    FreeChunk* old = mTop;
    mTop = p;
    mTop->bk = mTop;
    mTop->fd = mTop->bk;
    FreeChunk* unsorted = &mUnsorted;
    if (old != unsorted && flag != 0) {
        FreeChunk* bk = unsorted->bk;
        old->fd = unsorted;
        old->bk = bk;
        unsorted->bk = old;
        bk->fd = old;
    }
    if (mTrimCheck == 0)
        mLimit = (FreeChunk*)((mTop->head >> 1 & 0x3ffffffc) + (uint32)mTop);
}

// ===========================================================================
// 0x009268b0: initialise a fresh top chunk of `size` bytes (boundary tags:
// head = size|1, self-linked fd/bk and a trailing size field).
// ===========================================================================
// @ 0x009268b0
void FreePool::SetTop(FreeChunk* p, uint32 size)
{
    p->head = size | 1;
    p->bk = p;
    p->fd = p;
    *(uint32*)((char*)p + size) = size;
    if (mTrimCheck == 0)
        mLimit = (FreeChunk*)((mTop->head >> 1 & 0x3ffffffc) + (uint32)mTop);
}

// ===========================================================================
// 0x00926960: insert `p` into the small/large bin for `size`. `unlink` first
// removes p from the head of the unsorted bin (its bk is the sentinel).
// ===========================================================================
// @ 0x00926960
void FreePool::BinInsert(FreeChunk* p, uint32 size, char unlink)
{
    if (unlink != 0) {
        FreeChunk* f = *(FreeChunk**)((char*)p + 8);
        *(FreeChunk**)((char*)this + 0x38) = f;
        *(FreeChunk**)((char*)f + 0xc) = (FreeChunk*)((char*)this + 0x30);
    }
    uint32 index;
    FreeChunk* sentinel;
    FreeChunk* bk;
    FreeChunk* fd;
    if (size < 0x200) {
        index = size >> 3;
        sentinel = (FreeChunk*)((char*)this + index * 8 + 0x28);
        bk = sentinel->bk;
        fd = sentinel;
    } else {
        index = (uint32)FUN_009267f0(size);
        sentinel = (FreeChunk*)((char*)this + index * 8 + 0x28);
        bk = sentinel->bk;
        fd = sentinel;
        if (fd != bk) {
            FreeChunk* first = fd->fd;
            if (first->head <= size) {
                while (size < (bk->head & 0x7ffffff8))
                    bk = bk->bk;
                fd = bk->fd;
            } else {
                bk = fd;
                fd = first;
            }
        }
    }
    *(uint32*)((char*)this + ((int)index >> 5) * 4 + 0x430) |= 1u << (index & 0x1f);
    p->fd = fd;
    p->bk = bk;
    bk->fd = p;
    fd->bk = p;
}

// ===========================================================================
// 0x00926af0: split `p` at an aligned boundary, unlink it, then re-insert the
// pieces into the unsorted bin / top. 6 stack arguments; the first decides
// whether the split point is measured from the chunk head or its header.
// ===========================================================================
// @ 0x00926af0
void FreePool::SplitChunk(FreeChunk* p, int size, uint32 align,
                          uint32 a5, uint32 a6, char flag)
{
    uint32 off;
    if (flag != 0)
        off = (((p->head & 0x7ffffff8) - align + (uint32)p + 8 + a6) & -(int)a5) - a6;
    else
        off = ((uint32)p + a5 + 7 + a6 & -(int)a5) - a6;
    p->fd->bk = p->bk;
    p->bk->fd = p->fd;
    off -= 8;
    uint32 span = off - (uint32)p + align;
    int rem = size - (int)span;
    if (rem < 0x10) {
        *(uint32*)((char*)p + size + 4) |= 1;
    } else {
        FreeChunk* p2 = (FreeChunk*)((char*)p + span);
        FreeChunk* bk = mUnsorted.bk;
        p2->fd = &mUnsorted;
        p2->bk = bk;
        mUnsorted.bk = p2;
        bk->fd = p2;
        if (span < 0x200)
            mDv = p2;
        p->head = span | 1;
        p2->head = rem | 1;
        *(uint32*)((char*)p2 + rem) = rem;
    }
    uint32 csize = p->head & 0x7ffffff8;
    uint32 left = csize - align;
    if (left < 0x10) {
        *(uint32*)((char*)p + csize + 4) |= 1;
        return;
    }
    FreeChunk* bk2 = mUnsorted.bk;
    p->fd = &mUnsorted;
    p->bk = bk2;
    mUnsorted.bk = p;
    FreeChunk* q = (FreeChunk*)((char*)p + left);
    bk2->fd = p;
    if (align < 0x200)
        mDv = p;
    q->head = align;
    *(uint32*)((char*)q + align + 4) |= 1;
    p->head = left | 1;
    q->prev_size = left;
}

// ===========================================================================
// 0x00926c20: reserve a new arena with VirtualAlloc and turn it into a
// segment node holding the initial free chunk. `flag` forces the commit to
// cover the whole reservation.
// ===========================================================================
// @ 0x00926c20
SegNode* FreePool::NewSegment(uint32 size, char flag)
{
    uint32 align = mPageSize;
    uint32 commitSize = (align - 1 + size) & ~(align - 1);
    uint32 kind = 1;
    uint32 minReserve = commitSize;
    if (commitSize < mGrainSize)
        minReserve = (mGrainSize - 1 + align) & ~(align - 1);
    uint32 reserveSize = (minReserve + 0xffff) & 0xffff0000;
    void* lpAddress = VirtualAlloc(0, reserveSize, 0x2000, 4);
    SegNode* node;
    if (lpAddress != 0) {
        if (commitSize < mMinSegmentSize)
            commitSize = (mMinSegmentSize - 1 + mPageSize) & ~(mPageSize - 1);
        if (reserveSize < commitSize || flag != 0)
            commitSize = reserveSize;
        node = (SegNode*)VirtualAlloc(lpAddress, commitSize, 0x1000, 4);
        if (node != 0)
            goto build;
    }
    {
        DWORD flAllocationType = 0x3000;
        if (mNoCommit != 0)
            flAllocationType = 0x103000;
        node = (SegNode*)VirtualAlloc(0, minReserve, flAllocationType, 4);
        if (node == 0)
            return 0;
        kind = 3;
        reserveSize = minReserve;
        commitSize = minReserve;
    }
build:
    node->mAlignedBase = ((uint32)node + 0x27) & 0xfffffff8;
    *((unsigned char*)node + 0xd) = (unsigned char)(kind >> 1);
    node->mSizeB = commitSize;
    node->mSizeA = commitSize;
    bool atTop = (uint32)mSegTail != (uint32)this + 0x448;
    node->mpPrev = (SegNode*)((char*)this + 0x448);
    *((unsigned char*)node + 0xd) = (unsigned char)atTop;
    *((unsigned char*)node + 0xf) = (unsigned char)atTop;
    *((unsigned char*)node + 0xe) = 1;
    node->mUnk10 = 0;
    node->mUnk14 = 0;
    node->mpNext = mSegHead;
    mSegHead = node;
    node->mpNext->mpPrev = node;
    node->mSizeB = reserveSize;
    if (mTrimCheck == 0 && (uint32)mSegTail != (uint32)mSegHead) {
        mTrimCheck = 1;
        mLimit = 0;
    }
    {
        FreeChunk* chunk = (FreeChunk*)node->mAlignedBase;
        uint32 top = (uint32)node + (commitSize - node->mAlignedBase);
        uint32 size8 = top & 0x7ffffff8;
        uint32 prevSize = size8 - 0x10;
        chunk->head = (top & 0x80000007) | kind | prevSize;
        chunk->prev_size = 0;
        *(uint32*)((char*)chunk + prevSize) = prevSize;
        *(uint32*)((char*)chunk + size8 - 0xc) = 8;
        *(uint32*)((char*)chunk + size8 - 8) = 8;
        *(uint32*)((char*)chunk + size8 - 4) = 9;
        return (SegNode*)chunk;
    }
}

// ===========================================================================
// 0x00926f10: carve a new mmap'd chunk out of an OS allocation and link its
// trailing header into the mmap list. Returns the payload (header + 8).
// ===========================================================================
// @ 0x00926f10
void* FreePool::AllocSegment(uint32 nBytes)
{
    uint32 align = mPageSize - 1;
    uint32 size = (align + nBytes + 0x1f) & ~align;
    if (size >= nBytes) {
        DWORD flAllocationType = 0x3000;
        if (mNoCommit != 0)
            flAllocationType = 0x103000;
        int* p = (int*)VirtualAlloc(0, size, flAllocationType, 4);
        if (p != 0) {
            mMapBytes += size;
            mMapCount += 1;
            size -= 0x10;
            int* q;
            if (((uint32)p & 7) != 0) {
                uint32 pad = 8 - ((uint32)p & 7);
                q = (int*)((char*)p + pad);
                size -= pad;
                q[0] = pad;
                q[1] = size - pad | 2;
            } else {
                q = p;
                q[0] = 0;
                q[1] = size | 2;
            }
            FreeChunk* list = &mMmapList;
            uint32 next = (uint32)list->bk;
            FreeChunk* trailer = (FreeChunk*)((char*)q + size);
            trailer->prev_size = size;
            trailer->head = 0x13;
            trailer->fd = list;
            trailer->bk = (FreeChunk*)next;
            list->bk = trailer;
            *(FreeChunk**)(next + 8) = trailer;
            return (char*)q + 8;
        }
    }
    return 0;
}

// ===========================================================================
// 0x00926db0: walk the segment list and hand the tail pages of each wholly
// committed segment back to the OS, then relink the shrunken chunk. Returns
// the number of bytes released.
// ===========================================================================
// @ 0x00926db0
int FreePool::Trim(uint32 pad)
{
    void* lock = mpLock;
    if (lock != 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)lock);
        ((uint32*)lock)[6] += 1;
    }
    uint32 total = 0;
    SegNode* sentinel = (SegNode*)((char*)this + 0x448);
    for (SegNode* seg = mSegHead; seg != sentinel; seg = seg->mpNext) {
        FreeChunk* c = 0;
        if (seg->mFlagD != 0) {
            FreeChunk* cand = (FreeChunk*)((char*)seg + seg->mSizeA - 0x10);
            if ((*(unsigned char*)((char*)seg + seg->mSizeA - 0xc) & 1) == 0) {
                c = (FreeChunk*)((char*)cand - cand->prev_size);
                if (seg->mFlagF != 0) {
                    uint32 csize = c->head & 0x7ffffff8;
                    if (pad + 0x40 < csize) {
                        uint32 unit = ((mMinSegmentSize >> 1) + 0xffff) & 0xffff0000;
                        uint32 avail = csize - (pad + 0x40);
                        uint32 dwSize = unit;
                        if (unit * 2 < avail) {
                            dwSize += unit;
                            while (unit * 3 < avail)
                                dwSize += unit;
                        }
                        if (dwSize < avail &&
                            VirtualFree((char*)seg + seg->mSizeA - dwSize, dwSize, 0x4000) != 0) {
                            total += dwSize;
                            seg->mSizeA -= dwSize;
                            if (c != mTop) {
                                c->fd->bk = c->bk;
                                c->bk->fd = c->fd;
                            }
                            c->head = ((csize - dwSize) + 0x10) | (c->head & 0x80000007);
                            FUN_009268f0((int)c, 0);
                            if (c != mTop) {
                                FreeChunk* bk = mUnsorted.bk;
                                c->fd = &mUnsorted;
                                c->bk = bk;
                                mUnsorted.bk = c;
                                bk->fd = c;
                            }
                        }
                    }
                }
            }
        }
    }
    if (lock != 0) {
        ((uint32*)lock)[6] -= 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)lock);
    }
    return total;
}

// ===========================================================================
// 0x00927140: adopt an externally supplied arena (or ask for a fresh one) as
// a segment, then install its first chunk as the top. The two byte arguments
// are segment flags, the two word arguments are segment bookkeeping.
// ===========================================================================
// @ 0x00927140
bool FreePool::CreateSegment(uint32* base, uint32 size, char a4,
                            char a5, uint32 a6, uint32 a7)
{
    void* lock = mpLock;
    if (lock != 0) {
        EnterCriticalSection((LPCRITICAL_SECTION)lock);
        ((uint32*)lock)[6] += 1;
    }
    uint32* p;
    if (base == 0) {
        if (size != 0) {
            p = (uint32*)NewSegment((mPageSize - 1 + size) & ~(mPageSize - 1), 1);
            if (p != 0) {
                SetTopAndLink((FreeChunk*)p, 1);
                if (lock != 0) {
                    ((uint32*)lock)[6] -= 1;
                    LeaveCriticalSection((LPCRITICAL_SECTION)lock);
                }
                return true;
            }
        }
    } else if (size > 0x3f) {
        if (size % mPageSize != 0)
            size &= ~(mPageSize - 1);
        if ((size & 0xf) != 0)
            size &= 0xfffffff0;
        base[0] = ((uint32)base + 0x27) & 0xfffffff8;
        *((unsigned char*)base + 0xd) = (unsigned char)a4;
        *((unsigned char*)base + 0xe) = (unsigned char)a4;
        *((unsigned char*)base + 0xf) = (unsigned char)a5;
        *((SegNode**)((char*)base + 0x1c)) = (SegNode*)((char*)this + 0x448);
        base[1] = size;
        base[2] = size;
        *(unsigned char*)(base + 3) = 0;
        base[4] = a6;
        base[5] = a7;
        base[6] = (uint32)mSegHead;
        mSegHead = (SegNode*)base;
        *(SegNode**)(base[6] + 0x1c) = (SegNode*)base;
        if (a6 == 0) {
            MEMORY_BASIC_INFORMATION info;
            info.BaseAddress = base;
            VirtualQuery(base, &info, 0x1c);
            if (info.State == 0x2000)
                base[1] = 0;
        }
        p = (uint32*)base[0];
        uint32 top = (uint32)base + (size - (uint32)p);
        uint32 size8 = top & 0x7ffffff8;
        uint32 prevSize = size8 - 0x10;
        p[1] = (top & 0x80000007) | 1 | prevSize;
        p[0] = 0;
        *(uint32*)((char*)p + size8 - 0xc) = 8;
        *(uint32*)((char*)p + prevSize) = prevSize;
        *(uint32*)((char*)p + size8 - 8) = 8;
        *(uint32*)((char*)p + size8 - 4) = 9;
        SetTopAndLink((FreeChunk*)p, (char)(mTop != &mUnsorted));
        if (lock != 0) {
            ((uint32*)lock)[6] -= 1;
            LeaveCriticalSection((LPCRITICAL_SECTION)lock);
        }
        return true;
    }
    if (lock != 0) {
        ((uint32*)lock)[6] -= 1;
        LeaveCriticalSection((LPCRITICAL_SECTION)lock);
    }
    return false;
}

}}
