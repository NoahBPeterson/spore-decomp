// Hashtable node allocation (0x00a3b320): allocate a 0x18-byte node, copy-construct the 0x14-byte value into it
// (0xb20b90) and clear the bucket link.
#include "game/types.h"

void* EaAlloc_a3b320(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0

struct HashValue_a3b320 {
    char mData[0x14];
    HashValue_a3b320(const HashValue_a3b320& o);   // 0x00b20b90
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct HashNode_a3b320 {
    HashValue_a3b320 mValue;                     // +0x00
    HashNode_a3b320* mpNext;                     // +0x14
};
struct Hashtable_a3b320 {
    HashNode_a3b320* DoAllocateNode(const HashValue_a3b320& value);
};

// @ 0x00a3b320
HashNode_a3b320* Hashtable_a3b320::DoAllocateNode(const HashValue_a3b320& value)
{
    HashNode_a3b320* n = (HashNode_a3b320*)EaAlloc_a3b320(sizeof(HashNode_a3b320), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&n->mValue) HashValue_a3b320(value);
    n->mpNext = 0;
    return n;
}
