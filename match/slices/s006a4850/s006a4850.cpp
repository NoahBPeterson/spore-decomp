// Hashtable node allocation (0x006a4850): allocate a 0x18-byte node, copy-construct the 0x14-byte value into it
// (0x9fc440) and clear the bucket link.
#include "game/types.h"

void* EaAlloc_6a4850(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0

struct HashValue_6a4850 {
    uint32_t mKey;
    char     mValue[0x10];
    HashValue_6a4850(const HashValue_6a4850& o);   // 0x009fc440
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct HashNode_6a4850 {
    HashValue_6a4850 mValue;                     // +0x00
    HashNode_6a4850* mpNext;                     // +0x14
};
struct Hashtable_6a4850 {
    HashNode_6a4850* DoAllocateNode(const HashValue_6a4850& value);
};

// @ 0x006a4850
HashNode_6a4850* Hashtable_6a4850::DoAllocateNode(const HashValue_6a4850& value)
{
    HashNode_6a4850* n = (HashNode_6a4850*)EaAlloc_6a4850(sizeof(HashNode_6a4850), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&n->mValue) HashValue_6a4850(value);
    n->mpNext = 0;
    return n;
}
