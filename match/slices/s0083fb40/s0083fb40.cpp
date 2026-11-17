// Hashtable node allocation (0x0083fb40): allocate a 0x18-byte node, copy-construct the 0x14-byte value into it
// (0x83f990) and clear the bucket link.
#include "game/types.h"

void* EaAlloc_83fb40(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0

struct HashValue_83fb40 {
    char mData[0x14];
    HashValue_83fb40(const HashValue_83fb40& o);   // 0x0083f990
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct HashNode_83fb40 {
    HashValue_83fb40 mValue;                     // +0x00
    HashNode_83fb40* mpNext;                     // +0x14
};
struct Hashtable_83fb40 {
    HashNode_83fb40* DoAllocateNode(const HashValue_83fb40& value);
};

// @ 0x0083fb40
HashNode_83fb40* Hashtable_83fb40::DoAllocateNode(const HashValue_83fb40& value)
{
    HashNode_83fb40* n = (HashNode_83fb40*)EaAlloc_83fb40(sizeof(HashNode_83fb40), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&n->mValue) HashValue_83fb40(value);
    n->mpNext = 0;
    return n;
}
