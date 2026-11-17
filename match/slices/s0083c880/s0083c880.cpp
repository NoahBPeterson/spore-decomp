// Hashtable node allocation (0x0083c880): allocate a 0x18-byte node, copy-construct the 0x14-byte value into it
// (0x67e900) and clear the bucket link.
#include "game/types.h"

void* EaAlloc_83c880(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0

struct HashValue_83c880 {
    char mData[0x14];
    HashValue_83c880(const HashValue_83c880& o);   // 0x0067e900
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct HashNode_83c880 {
    HashValue_83c880 mValue;                     // +0x00
    HashNode_83c880* mpNext;                     // +0x14
};
struct Hashtable_83c880 {
    HashNode_83c880* DoAllocateNode(const HashValue_83c880& value);
};

// @ 0x0083c880
HashNode_83c880* Hashtable_83c880::DoAllocateNode(const HashValue_83c880& value)
{
    HashNode_83c880* n = (HashNode_83c880*)EaAlloc_83c880(sizeof(HashNode_83c880), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&n->mValue) HashValue_83c880(value);
    n->mpNext = 0;
    return n;
}
