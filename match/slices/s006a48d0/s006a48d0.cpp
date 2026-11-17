// Hashtable node allocation (0x006a48d0): allocate a 0x18-byte node, copy-construct the 0x14-byte value into it
// (0xb20b90) and clear the bucket link.
#include "game/types.h"

void* EaAlloc_6a48d0(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0

struct HashValue_6a48d0 {
    char mData[0x14];
    HashValue_6a48d0(const HashValue_6a48d0& o);   // 0x00b20b90
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct HashNode_6a48d0 {
    HashValue_6a48d0 mValue;                     // +0x00
    HashNode_6a48d0* mpNext;                     // +0x14
};
struct Hashtable_6a48d0 {
    HashNode_6a48d0* DoAllocateNode(const HashValue_6a48d0& value);
};

// @ 0x006a48d0
HashNode_6a48d0* Hashtable_6a48d0::DoAllocateNode(const HashValue_6a48d0& value)
{
    HashNode_6a48d0* n = (HashNode_6a48d0*)EaAlloc_6a48d0(sizeof(HashNode_6a48d0), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&n->mValue) HashValue_6a48d0(value);
    n->mpNext = 0;
    return n;
}
