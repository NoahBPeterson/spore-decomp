// Slice s00928b00 (bfs2 #24), 32-bit MSVC 2008.
// EA::Allocator::StackAllocator + EA file-stream/big-file helpers.
// Layouts from the 2008 dev PDB.
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <string.h>
#include <wchar.h>

typedef unsigned int uint32;

namespace EA { namespace Allocator {

struct Bookmark;
struct Block {
    Block* mpPrevBlock;  // +0x00
    char*  mpEnd;        // +0x04
    char   mData[4];     // +0x08
};

typedef void* (__cdecl *CoreAllocFn)(uint32 size, uint32* pActualSize, void* context);
typedef void  (__cdecl *CoreFreeFn)(void* p, void* context);

class StackAllocator {
public:
    uint32 mnDefaultBlockSize;       // +0x00
    Block* mpCurrentBlock;           // +0x04
    char*  mpCurrentBlockEnd;        // +0x08
    char*  mpCurrentObjectBegin;     // +0x0c
    char*  mpCurrentObjectEnd;       // +0x10
    CoreAllocFn mpCoreAllocationFunction; // +0x14
    CoreFreeFn  mpCoreFreeFunction;       // +0x18
    void*  mpCoreFunctionContext;    // +0x1c
    Bookmark* mpTopBookmark;         // +0x20

    void Init(Block* pBlock, uint32 blockSize, CoreAllocFn alloc, CoreFreeFn free, void* ctx);
    bool AllocateNewBlock(uint32 size);
    int  MallocAligned(int size, int align, int offset, char flag);
    StackAllocator(void* pBlock = 0, uint32 blockSize = 0xffffffff, CoreAllocFn alloc = 0,
                   CoreFreeFn free = 0, void* ctx = 0);
    void Reset(void* p);
    ~StackAllocator();
};

extern "C" void* SP_Pool_AllocGlobal(uint32 size, uint32* pActual, void* ctx); // 0x00928ad0
extern "C" void  operator_delete__f47410(void* p, void* ctx);                  // 0x00f47410
void FUN_00928e20(void* self);                                                 // 0x00928e20
void EA_Text_ConvertEncoding(const wchar_t* src, int enc, int dstEnc, void* dst, uint32* pLen,
                             int a6);                                          // 0x0093c950

// @ 0x00928b00
void StackAllocator::Init(Block* pBlock, uint32 blockSize, CoreAllocFn alloc, CoreFreeFn free,
                          void* ctx)
{
    if (mpCurrentBlock == 0) {
        if (alloc != 0)
            mpCoreAllocationFunction = alloc;
        if (free != 0)
            mpCoreFreeFunction = free;
        mpCoreFunctionContext = ctx;
        if (blockSize == 0)
            blockSize = mnDefaultBlockSize;
        else if (blockSize < 0xc)
            blockSize = 0xc;
        if (pBlock != 0 ||
            (pBlock = (Block*)mpCoreAllocationFunction(blockSize, &blockSize, ctx)) != 0) {
            mpCurrentBlock = pBlock;
            mpCurrentBlockEnd = pBlock->mData + (blockSize - 8);
            pBlock->mpEnd = pBlock->mData + (blockSize - 8);
            mpCurrentBlock->mpPrevBlock = 0;
            char* p = (char*)mpCurrentBlock + 8;
            mpCurrentObjectBegin = p;
            mpCurrentObjectEnd = p;
            if (((uint32)p & 7) != 0) {
                p = (char*)(((uint32)p + 7) & 0xfffffff8);
                mpCurrentObjectBegin = p;
                mpCurrentObjectEnd = p;
            }
        }
    }
}

// @ 0x00928ba0
bool StackAllocator::AllocateNewBlock(uint32 size)
{
    uint32 avail = (uint32)(mpCurrentObjectEnd - mpCurrentObjectBegin);
    uint32 need = (avail >> 2) + avail + 0x1008 + size;
    if (need < 0x2000)
        need = 0x2000;
    void* p = mpCoreAllocationFunction(need, &need, mpCoreFunctionContext);
    if (p != 0) {
        *(void**)p = mpCurrentBlock;
        char* dst = (char*)p + 8;
        mpCurrentBlock = (Block*)p;
        *((char**)p + 1) = (char*)p + need;
        mpCurrentBlockEnd = (char*)p + need;
        if (((uint32)dst & 7) != 0)
            dst = (char*)(((uint32)p + 0xf) & 0xfffffff8);
        if (avail != 0 && dst != 0 && mpCurrentObjectBegin != 0)
            memcpy(dst, mpCurrentObjectBegin, avail);
        mpCurrentObjectBegin = dst;
        mpCurrentObjectEnd = dst + avail;
        return true;
    }
    return false;
}

// @ 0x00928d40
int StackAllocator::MallocAligned(int size, int align, int offset, char flag)
{
    uint32 mask = (uint32)(align - 1) | 7;
    uint32 sz = (uint32)(size + 7) & 0xfffffff8;
    int p = (int)(((uint32)mpCurrentObjectBegin + offset + mask) & ~mask) - offset;
    if (flag != 0 && (char*)(p + sz) > mpCurrentBlockEnd) {
        if (!AllocateNewBlock(sz + mask + 1 + offset))
            return 0;
        p = (int)(((uint32)mpCurrentObjectBegin + offset + mask) & ~mask) - offset;
    }
    mpCurrentObjectBegin = (char*)(p + sz);
    mpCurrentObjectEnd = (char*)(p + sz);
    return p;
}

// @ 0x00928cd0
StackAllocator::StackAllocator(void* pBlock, uint32 blockSize, CoreAllocFn alloc, CoreFreeFn free,
                               void* ctx)
{
    mnDefaultBlockSize = 0x2000;
    mpCurrentBlock = 0;
    mpCurrentBlockEnd = 0;
    mpCurrentObjectBegin = 0;
    mpCurrentObjectEnd = 0;
    if (alloc == 0)
        alloc = &SP_Pool_AllocGlobal;
    mpCoreAllocationFunction = alloc;
    if (free == 0)
        free = &operator_delete__f47410;
    mpCoreFreeFunction = free;
    mpCoreFunctionContext = 0;
    mpTopBookmark = 0;
    if (blockSize != 0xffffffff)
        Init((Block*)pBlock, blockSize, alloc, free, ctx);
}

// @ 0x00928c40
void StackAllocator::Reset(void* p)
{
    Block* b = mpCurrentBlock;
    for (;;) {
        if (b == 0) {
            mpCurrentBlock = 0;
            mpCurrentBlockEnd = 0;
            mpCurrentObjectBegin = 0;
            mpCurrentObjectEnd = 0;
            return;
        }
        char* start = (char*)b + 8;
        if ((char*)p >= start && (char*)p <= b->mpEnd) {
            mpCurrentBlock = b;
            mpCurrentBlockEnd = b->mpEnd;
            mpCurrentObjectBegin = (char*)p;
            mpCurrentObjectEnd = (char*)p;
            return;
        }
        if (mpTopBookmark != 0) {
            void* bm = mpTopBookmark;
            while (bm != 0 && *(char**)((char*)bm + 4) >= start && b->mpEnd > *(char**)((char*)bm + 4)
                   && bm >= (void*)start) {
                bm = *(void**)bm;
            }
            mpTopBookmark = (Bookmark*)bm;
        }
        Block* nxt = b->mpPrevBlock;
        if (mpCoreFreeFunction != 0)
            mpCoreFreeFunction(b, mpCoreFunctionContext);
        b = nxt;
    }
}

// @ 0x00929220
int FUN_00929220(void* self, const wchar_t* name)
{
    char* p = (char*)self;
    *(int*)(p + 0) = 0;
    *(int*)(p + 4) = 0;
    *(int*)(p + 8) = 0;
    *(int*)(p + 0x430) = 0;
    *(int*)(p + 0x434) = 0;
    *(int*)(p + 0x438) = 0;
    *(int*)(p + 0x43c) = 0;
    *(int*)(p + 0x440) = 0;
    *(int*)(p + 0x444) = 0;
    if (name != 0) {
        uint32 n = 0x104;
        EA_Text_ConvertEncoding(name, -1, 8, (char*)self + 0x1c, &n, 0x10);
        *(unsigned short*)(p + 0x222) = 0;
        FUN_00928e20(self);
    }
    return (int)self;
}

// @ 0x00929290
char FUN_00929290(void* self)
{
    char* p = (char*)self;
    char** begin = (char**)p;
    char** end = (char**)(p + 4);
    if (*p == *(int*)(p + 4))
        return 1;
    for (char** it = begin; it != end; it++) {
        int* obj = (int*)*it;
        (*(void(__thiscall**)(int*))((char*)*obj + 0x18))(obj);
        if (*it != 0) {
            void** vt = *(void***)*it;
            (*(void(__thiscall**)(void*, int))vt[0])(*it, 1);
        }
    }
    memmove(*begin, *end, 0);
    *(int*)(p + 4) = *(int*)(p + 4) + ((int)end - (int)begin >> 2) * -4;
    *(int*)(p + 0x434) = 0;
    *(int*)(p + 0x438) = 0;
    *(int*)(p + 0x43c) = 0;
    *(int*)(p + 0x440) = 0;
    return 1;
}

// @ 0x00929450
void FUN_00929450(void* self)
{
    FUN_00929290(self);
    char* p = *(char**)self;
    if (p != 0 && *(int*)(p - 4) != 0)
        operator_delete__f47410(p, 0);
}

// ===========================================================================
// remaining small helpers
// ===========================================================================

// @ 0x00928dc0
void __fastcall FUN_00928dc0(StackAllocator* self)
{
    self->Reset(0);
}

// @ 0x00928de0
void FUN_00928de0(const char* s)
{
    if (s != 0)
        OutputDebugStringA(s);
}

// @ 0x00928df0
uint32 FUN_00928df0()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    return si.dwPageSize;
}

// @ 0x00928f80
void FUN_00928f80(void* self, const wchar_t* name)
{
    char* p = (char*)self;
    if (*(int*)p == *(int*)(p + 4) && name != 0) {
        wcsncpy((wchar_t*)(p + 0x1c), name, 0x104);
        *(unsigned short*)(p + 0x222) = 0;
        FUN_00928e20(self);
    }
}

// @ 0x009290c0
char FUN_009290c0(void* self)
{
    int** begin = (int**)self;
    int** end = (int**)((char*)self + 4);
    char r = 0;
    if (begin != end) {
        r = 1;
        for (int** it = begin; it != end; it++) {
            if (r != 0) {
                int* obj = *it;
                r = (*(char(__thiscall**)(int*))((char*)*obj + 0x34))(obj);
                if (r != 0)
                    r = 1;
                else
                    r = 0;
            } else {
                r = 0;
            }
        }
    }
    return r;
}

// ===========================================================================
// big functions: behaviourally-shaped skeletons (partial)
// ===========================================================================
void FUN_00928e20(void* self) { (void)self; }
void FUN_00928f00(wchar_t* dst, unsigned n, int idx) { (void)dst; (void)n; (void)idx; }
int  FUN_00928fc0(void* self) { (void)self; return -1; }
int  FUN_00929000(void* self) { (void)self; return 0; }
int  FUN_009290a0(void* self) { (void)self; return 0; }
int  FUN_00929100(void* self, int a, unsigned b) { (void)self; (void)a; (void)b; return -1; }
int  FUN_00929310(void* self) { (void)self; return 0; }
int  FUN_00929470(void* self) { (void)self; return 0; }
int  FUN_009297a0(void* self) { (void)self; return 0; }
int  FUN_00929900(void* self) { (void)self; return 0; }

}}
