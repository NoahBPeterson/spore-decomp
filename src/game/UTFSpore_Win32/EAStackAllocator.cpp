// src/game/UTFSpore_Win32/EAStackAllocator.cpp -- migrated from slice(s) s00928b00 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAStackAllocator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Allocator/StackAllocator.h"
#include <windows.h>
#include <string.h>
#include <wchar.h>

// ---- items of slice s00928b00 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
namespace EA {
namespace Allocator {
struct Bookmark_s0092_8b00;
}
}
namespace EA {
namespace Allocator {
struct Block_s0092_8b00 {
    Block_s0092_8b00* mpPrevBlock;  // +0x00
    char*  mpEnd;        // +0x04
    char   mData[4];     // +0x08
};
}
}
namespace EA {
namespace Allocator {
typedef void* (__cdecl *CoreAllocFn)(uint32 size, uint32* pActualSize, void* context);
}
}
namespace EA {
namespace Allocator {
typedef void  (__cdecl *CoreFreeFn)(void* p, void* context);
}
}
namespace EA {
namespace Allocator {
class StackAllocator_s0092_8b00 {
public:
    uint32 mnDefaultBlockSize;       // +0x00
    Block_s0092_8b00* mpCurrentBlock;           // +0x04
    char*  mpCurrentBlockEnd;        // +0x08
    char*  mpCurrentObjectBegin;     // +0x0c
    char*  mpCurrentObjectEnd;       // +0x10
    CoreAllocFn mpCoreAllocationFunction; // +0x14
    CoreFreeFn  mpCoreFreeFunction;       // +0x18
    void*  mpCoreFunctionContext;    // +0x1c
    Bookmark_s0092_8b00* mpTopBookmark;         // +0x20

    void Init(Block_s0092_8b00* pBlock, uint32 blockSize, CoreAllocFn alloc, CoreFreeFn free, void* ctx);  // 0x00928b00 (EA::Allocator::StackAllocator::Init)
    bool AllocateNewBlock(uint32 size);  // 0x0082b0d0 (EA::Allocator::StackAllocator::AllocateNewBlock)
    int  MallocAligned(int size, int align, int offset, char flag);  // 0x00928d40 (EA::Allocator::StackAllocator::MallocAligned)
    StackAllocator_s0092_8b00(void* pBlock = 0, uint32 blockSize = 0xffffffff, CoreAllocFn alloc = 0,
                   CoreFreeFn free = 0, void* ctx = 0);
    void Reset(void* p);
    ~StackAllocator_s0092_8b00();
};
}
}
extern "C" void* SP_Pool_AllocGlobal(uint32 size, uint32* pActual, void* ctx); // 0x00928ad0
extern "C" void  operator_delete__f47410(void* p, void* ctx);                  // 0x00f47410
// ---- items of slice s00928b00 end

// @ 0x00928b00
namespace EA { namespace Allocator {
void StackAllocator_s0092_8b00::Init(Block_s0092_8b00* pBlock, uint32 blockSize, CoreAllocFn alloc, CoreFreeFn free, void* ctx)
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
            (pBlock = (Block_s0092_8b00*)mpCoreAllocationFunction(blockSize, &blockSize, ctx)) != 0) {
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
}}  // namespace EA::Allocator

// @ 0x00928c40
namespace EA { namespace Allocator {
void StackAllocator_s0092_8b00::Reset(void* p)
{
    Block_s0092_8b00* b = mpCurrentBlock;
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
            mpTopBookmark = (Bookmark_s0092_8b00*)bm;
        }
        Block_s0092_8b00* nxt = b->mpPrevBlock;
        if (mpCoreFreeFunction != 0)
            mpCoreFreeFunction(b, mpCoreFunctionContext);
        b = nxt;
    }
}
}}  // namespace EA::Allocator

// @ 0x00928cd0
namespace EA { namespace Allocator {
StackAllocator_s0092_8b00::StackAllocator_s0092_8b00(void* pBlock, uint32 blockSize, CoreAllocFn alloc, CoreFreeFn free, void* ctx)
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
        Init((Block_s0092_8b00*)pBlock, blockSize, alloc, free, ctx);
}
}}  // namespace EA::Allocator
