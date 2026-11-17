// Hashtable node allocation (0x00845660): allocate a 0x18-byte node, copy-construct the 0x14-byte value into it
// (0x844a60) and clear the bucket link.
#include "game/types.h"

void* EaAlloc_845660(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0

struct HashValue_845660 {
    char mData[0x14];
    HashValue_845660(const HashValue_845660& o);   // 0x00844a60
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct HashNode_845660 {
    HashValue_845660 mValue;                     // +0x00
    HashNode_845660* mpNext;                     // +0x14
};
struct Hashtable_845660 {
    HashNode_845660* DoAllocateNode(const HashValue_845660& value);
};

// @ 0x00845660
HashNode_845660* Hashtable_845660::DoAllocateNode(const HashValue_845660& value)
{
    HashNode_845660* n = (HashNode_845660*)EaAlloc_845660(sizeof(HashNode_845660), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&n->mValue) HashValue_845660(value);
    n->mpNext = 0;
    return n;
}
