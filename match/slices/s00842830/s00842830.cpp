// Hashtable node allocation (0x00842830): allocate a 0x24-byte node, copy-construct the 0x20-byte value into it
// (0x841f00) and clear the bucket link.
#include "game/types.h"

void* EaAlloc_842830(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0

struct HashValue_842830 {
    char mData[0x20];
    HashValue_842830(const HashValue_842830& o);   // 0x00841f00
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct HashNode_842830 {
    HashValue_842830 mValue;                     // +0x00
    HashNode_842830* mpNext;                     // +0x20
};
struct Hashtable_842830 {
    HashNode_842830* DoAllocateNode(const HashValue_842830& value);
};

// @ 0x00842830
HashNode_842830* Hashtable_842830::DoAllocateNode(const HashValue_842830& value)
{
    HashNode_842830* n = (HashNode_842830*)EaAlloc_842830(sizeof(HashNode_842830), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&n->mValue) HashValue_842830(value);
    n->mpNext = 0;
    return n;
}
