// Tree node allocation (0x006811d0): allocate a 0x38-byte rb-tree node and copy-construct its value: the key is copied
// and the 0x24-byte mapped value is copy-constructed (0x680c30).
#include "game/types.h"

void* EaAlloc_6811d0(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0

struct Mapped_6811d0 {
    char mData[0x24];
    Mapped_6811d0(const Mapped_6811d0& o);   // 0x00680c30
};
struct TreeValue_6811d0 {
    uint32_t first;
    Mapped_6811d0 second;
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct TreeNode_6811d0 {
    void* mpNodeRight; void* mpNodeLeft; void* mpNodeParent; int mColor;   // +0x00
    TreeValue_6811d0 mValue;                                                  // +0x10
};
struct Tree_6811d0 {
    TreeNode_6811d0* DoCreateNode(const TreeValue_6811d0& value);
};

// @ 0x006811d0
TreeNode_6811d0* Tree_6811d0::DoCreateNode(const TreeValue_6811d0& value)
{
    TreeNode_6811d0* n = (TreeNode_6811d0*)EaAlloc_6811d0(sizeof(TreeNode_6811d0), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&n->mValue) TreeValue_6811d0(value);
    return n;
}
