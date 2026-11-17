// Tree node allocation (0x006b2380): allocate a 0x1c-byte rb-tree node and copy-construct its value: the key is copied
// and the 0x8-byte mapped value is copy-constructed (0x6b1e90).
#include "game/types.h"

void* EaAlloc_6b2380(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0

struct Mapped_6b2380 {
    char mData[0x8];
    Mapped_6b2380(const Mapped_6b2380& o);   // 0x006b1e90
};
struct TreeValue_6b2380 {
    uint32_t first;
    Mapped_6b2380 second;
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct TreeNode_6b2380 {
    void* mpNodeRight; void* mpNodeLeft; void* mpNodeParent; int mColor;   // +0x00
    TreeValue_6b2380 mValue;                                                  // +0x10
};
struct Tree_6b2380 {
    TreeNode_6b2380* DoCreateNode(const TreeValue_6b2380& value);
};

// @ 0x006b2380
TreeNode_6b2380* Tree_6b2380::DoCreateNode(const TreeValue_6b2380& value)
{
    TreeNode_6b2380* n = (TreeNode_6b2380*)EaAlloc_6b2380(sizeof(TreeNode_6b2380), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&n->mValue) TreeValue_6b2380(value);
    return n;
}
