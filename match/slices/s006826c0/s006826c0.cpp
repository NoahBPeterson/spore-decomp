// Tree node allocation (0x006826c0): allocate a 0x4c-byte rb-tree node and copy-construct its value: the key is copied
// and the 0x38-byte mapped value is copy-constructed (0x681700).
#include "game/types.h"

void* EaAlloc_6826c0(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0

struct Mapped_6826c0 {
    char mData[0x38];
    Mapped_6826c0(const Mapped_6826c0& o);   // 0x00681700
};
struct TreeValue_6826c0 {
    uint32_t first;
    Mapped_6826c0 second;
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct TreeNode_6826c0 {
    void* mpNodeRight; void* mpNodeLeft; void* mpNodeParent; int mColor;   // +0x00
    TreeValue_6826c0 mValue;                                                  // +0x10
};
struct Tree_6826c0 {
    TreeNode_6826c0* DoCreateNode(const TreeValue_6826c0& value);
};

// @ 0x006826c0
TreeNode_6826c0* Tree_6826c0::DoCreateNode(const TreeValue_6826c0& value)
{
    TreeNode_6826c0* n = (TreeNode_6826c0*)EaAlloc_6826c0(sizeof(TreeNode_6826c0), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&n->mValue) TreeValue_6826c0(value);
    return n;
}
