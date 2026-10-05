// Slice s00501f40: mostly skeletons (see partial.txt); two small helpers reconstructed.
#include "types.h"

void EASTL_allocator_deallocate(void* p);   // 0x00f47380
struct DequeBase2 { void Deallocate(void* p); };   // 0x00569260
struct DequeIter  { void SetSubarray(int p); };    // 0x00569340

struct Alloc2 {
    void deallocate(void* p, int n);        // 0x00502eb0
};
struct Deque {
    void F();                               // 0x00502e70
};

// @ 0x00502e70
void Deque::F()
{
    ((DequeBase2*)this)->Deallocate(*(void**)((char*)this + 0xc));
    ((DequeIter*)((char*)this + 8))->SetSubarray(*(int*)((char*)this + 0x14) + 4);
    *(void**)((char*)this + 8) = *(void**)((char*)this + 0xc);
}

// @ 0x00502eb0
void Alloc2::deallocate(void* p, int n)
{
    if (p) {
        void* q = p;
        EASTL_allocator_deallocate(q);
    }
}

// ---------------------------------------------------------------------------
// Large /Od bodies reconstructed only as skeletons (see partial.txt).
// ---------------------------------------------------------------------------
// @ 0x00501f40
void FUN_00501f40() {}
// @ 0x00502450
void FUN_00502450() {}
// @ 0x00502880
void FUN_00502880() {}
// @ 0x00502dd0
void FUN_00502dd0() {}
