// Hashtable node allocation (0x0068cd80): allocate a 0x18-byte node, copy-construct the 0x14-byte value into it
// (0x688700) and clear the bucket link.
#include "game/types.h"

void* EaAlloc_68cd80(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0

struct HashValue_68cd80 {
    char mData[0x14];
    HashValue_68cd80(const HashValue_68cd80& o);   // 0x00688700
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct HashNode_68cd80 {
    HashValue_68cd80 mValue;                     // +0x00
    HashNode_68cd80* mpNext;                     // +0x14
};
struct Hashtable_68cd80 {
    HashNode_68cd80* DoAllocateNode(const HashValue_68cd80& value);
};

// @ 0x0068cd80
HashNode_68cd80* Hashtable_68cd80::DoAllocateNode(const HashValue_68cd80& value)
{
    HashNode_68cd80* n = (HashNode_68cd80*)EaAlloc_68cd80(sizeof(HashNode_68cd80), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&n->mValue) HashValue_68cd80(value);
    n->mpNext = 0;
    return n;
}
