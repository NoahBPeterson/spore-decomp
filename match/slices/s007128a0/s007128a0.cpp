// Hashtable node allocation (0x007128a0): allocate a 0x50-byte node, copy-construct the 0x4c-byte value into it
// (0x7127d0) and clear the bucket link.
#include "game/types.h"

void* EaAlloc_7128a0(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0

struct HashValue_7128a0 {
    char mData[0x4c];
    HashValue_7128a0(const HashValue_7128a0& o);   // 0x007127d0
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct HashNode_7128a0 {
    HashValue_7128a0 mValue;                     // +0x00
    HashNode_7128a0* mpNext;                     // +0x4c
};
struct Hashtable_7128a0 {
    HashNode_7128a0* DoAllocateNode(const HashValue_7128a0& value);
};

// @ 0x007128a0
HashNode_7128a0* Hashtable_7128a0::DoAllocateNode(const HashValue_7128a0& value)
{
    HashNode_7128a0* n = (HashNode_7128a0*)EaAlloc_7128a0(sizeof(HashNode_7128a0), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&n->mValue) HashValue_7128a0(value);
    n->mpNext = 0;
    return n;
}
