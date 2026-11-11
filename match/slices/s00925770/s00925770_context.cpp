// ContextCoreAllocator callback: the StackAllocator allocation hook returns its block.
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/Allocator/ContextCoreAllocator.h"

// @ 0x00925bf0
void* EA::Allocator::ContextCoreAllocator::allocate2(unsigned size, unsigned* allocatedSize, void* context)
{
    ICoreAllocator* allocator = static_cast<ContextCoreAllocator*>(context)->mpAllocator;
    typedef void* (__thiscall* AllocationFunction)(ICoreAllocator*, unsigned, const char*, unsigned);
    AllocationFunction allocate = (AllocationFunction)(*(void***)allocator)[2];
    void* result = allocate(allocator, size, 0, 0);
    if (allocatedSize)
        *allocatedSize = result ? size : 0;
    return result;
}
