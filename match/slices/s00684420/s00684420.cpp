// Tree node allocation (0x00684420): allocate a 0x40-byte rb-tree node and copy-construct its value: the key is copied
// and the 0x2c-byte mapped value is copy-constructed (0x683670).
#include "game/types.h"

void* EaAlloc_684420(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0

struct Mapped_684420 {
    char mData[0x2c];
    Mapped_684420(const Mapped_684420& o);   // 0x00683670
};
struct TreeValue_684420 {
    uint32_t first;
    Mapped_684420 second;
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct TreeNode_684420 {
    void* mpNodeRight; void* mpNodeLeft; void* mpNodeParent; int mColor;   // +0x00
    TreeValue_684420 mValue;                                                  // +0x10
};
struct Tree_684420 {
    TreeNode_684420* DoCreateNode(const TreeValue_684420& value);
};

// @ 0x00684420
TreeNode_684420* Tree_684420::DoCreateNode(const TreeValue_684420& value)
{
    TreeNode_684420* n = (TreeNode_684420*)EaAlloc_684420(sizeof(TreeNode_684420), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&n->mValue) TreeValue_684420(value);
    return n;
}
