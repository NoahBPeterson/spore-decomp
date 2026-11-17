// Hashtable node allocation (0x0083d0c0): allocate a 0x18-byte node, copy-construct the 0x14-byte value into it
// (0x83d020) and clear the bucket link.
#include "game/types.h"

void* EaAlloc_83d0c0(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0

struct HashValue_83d0c0 {
    char mData[0x14];
    HashValue_83d0c0(const HashValue_83d0c0& o);   // 0x0083d020
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct HashNode_83d0c0 {
    HashValue_83d0c0 mValue;                     // +0x00
    HashNode_83d0c0* mpNext;                     // +0x14
};
struct Hashtable_83d0c0 {
    HashNode_83d0c0* DoAllocateNode(const HashValue_83d0c0& value);
};

// @ 0x0083d0c0
HashNode_83d0c0* Hashtable_83d0c0::DoAllocateNode(const HashValue_83d0c0& value)
{
    HashNode_83d0c0* n = (HashNode_83d0c0*)EaAlloc_83d0c0(sizeof(HashNode_83d0c0), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&n->mValue) HashValue_83d0c0(value);
    n->mpNext = 0;
    return n;
}
