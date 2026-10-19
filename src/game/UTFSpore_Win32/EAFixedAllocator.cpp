// src/game/UTFSpore_Win32/EAFixedAllocator.cpp -- migrated from slice(s) s00926410 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAFixedAllocator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Allocator/FixedAllocatorBase.h"
#include <windows.h>

// ---- items of slice s00926410 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
namespace EA {
namespace Allocator {
struct CoreBlock_s0092_6410;
}
}
namespace EA {
namespace Allocator {
struct Chunk_s0092_6410;
}
}
namespace EA {
namespace Allocator {
typedef void* (__cdecl *CoreAllocFn)(uint32 size, void* context);
}
}
namespace EA {
namespace Allocator {
typedef void  (__cdecl *CoreFreeFn)(void* p, void* context);
}
}
extern "C" void* FUN_006abeb0(uint32 size, void* context);  // 0x006abeb0
extern "C" void  FUN_00f47410(void* p, void* context);       // 0x00f47410
namespace EA {
namespace Allocator {
class FixedAllocatorBase_s0092_6410 {
public:
    uint32 mnObjectSize;                  // +0x00
    uint32 mnObjectAlignment;             // +0x04
    uint32 mnCountPerCoreBlock;           // +0x08
    CoreBlock_s0092_6410* mpHeadCoreBlock;           // +0x0c
    Chunk_s0092_6410* mpHeadChunk;                   // +0x10
    CoreAllocFn mpCoreAllocationFunction; // +0x14
    CoreFreeFn  mpCoreFreeFunction;       // +0x18
    void* mpCoreFunctionContext;          // +0x1c

    bool SplitCore(CoreBlock_s0092_6410* pCoreBlock);   // @ 0x009265f0
    bool AddCore(CoreBlock_s0092_6410* pCoreBlock, uint32 nSize);  // @ 0x00926650
    bool Init(uint32 objectSize, uint32 objectAlignment, uint32 countPerCoreBlock,
              CoreBlock_s0092_6410* pCoreBlock, uint32 nSize, CoreAllocFn allocFn, CoreFreeFn freeFn,
              void* context);                  // @ 0x009266b0
    FixedAllocatorBase_s0092_6410(uint32 objectSize, uint32 objectAlignment, uint32 countPerCoreBlock,
                       CoreBlock_s0092_6410* pCoreBlock, uint32 nSize, CoreAllocFn allocFn, CoreFreeFn freeFn,
                       void* context);         // @ 0x00926720
};
}
}
namespace EA {
namespace Allocator {
struct CoreBlock_s0092_6410 {
    CoreBlock_s0092_6410* mpNext;   // +0x00
    uint32 mnSize;       // +0x04
    char mData[4];       // +0x08
};
}
}
namespace EA {
namespace Allocator {
struct Chunk_s0092_6410 {
    Chunk_s0092_6410* mpNext;       // +0x00
};
}
}
// ---- items of slice s00926410 end

// @ 0x009265f0
namespace EA { namespace Allocator {
bool FixedAllocatorBase_s0092_6410::SplitCore(CoreBlock_s0092_6410* pCoreBlock)
{
    Chunk_s0092_6410* pChunk = (Chunk_s0092_6410*)((mnObjectAlignment + (uint32)pCoreBlock + 7) & ~(mnObjectAlignment - 1));
    char* pEnd = (char*)pCoreBlock + pCoreBlock->mnSize - 2 * mnObjectSize;
    if (pChunk <= (Chunk_s0092_6410*)pEnd) {
        mpHeadChunk = pChunk;
        do {
            Chunk_s0092_6410* pNext = (Chunk_s0092_6410*)((char*)pChunk + mnObjectSize);
            pChunk->mpNext = pNext;
            pChunk = pNext;
        } while (pChunk <= (Chunk_s0092_6410*)pEnd);
        pChunk->mpNext = 0;
        return true;
    }
    return false;
}
}}  // namespace EA::Allocator

// @ 0x00926650
namespace EA { namespace Allocator {
bool FixedAllocatorBase_s0092_6410::AddCore(CoreBlock_s0092_6410* pCoreBlock, uint32 nSize)
{
    if (pCoreBlock == 0) {
        while (nSize == 0)
            nSize = (mnCountPerCoreBlock + 2) * mnObjectSize + 0xc;
        if (nSize == 0xffffffff)
            goto fail;
        pCoreBlock = (CoreBlock_s0092_6410*)(*mpCoreAllocationFunction)(nSize, mpCoreFunctionContext);
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
}}  // namespace EA::Allocator

// @ 0x009266b0
namespace EA { namespace Allocator {
bool FixedAllocatorBase_s0092_6410::Init(uint32 objectSize, uint32 objectAlignment, uint32 countPerCoreBlock, CoreBlock_s0092_6410* pCoreBlock, uint32 nSize, CoreAllocFn allocFn, CoreFreeFn freeFn, void* context)
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
}}  // namespace EA::Allocator

// @ 0x00926720
namespace EA { namespace Allocator {
FixedAllocatorBase_s0092_6410::FixedAllocatorBase_s0092_6410(uint32 objectSize, uint32 objectAlignment, uint32 countPerCoreBlock, CoreBlock_s0092_6410* pCoreBlock, uint32 nSize, CoreAllocFn allocFn, CoreFreeFn freeFn, void* context)
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
}}  // namespace EA::Allocator
