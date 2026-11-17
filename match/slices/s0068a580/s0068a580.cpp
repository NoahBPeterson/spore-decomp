// Tree node allocation (0x0068a580): allocate a 0x38-byte rb-tree node and copy-construct its value: the key is copied
// and the 0x24-byte mapped value is copy-constructed (0x689ee0).
#include "game/types.h"

void* EaAlloc_68a580(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0

struct Mapped_68a580 {
    char mData[0x24];
    Mapped_68a580(const Mapped_68a580& o);   // 0x00689ee0
};
struct TreeValue_68a580 {
    uint32_t first;
    Mapped_68a580 second;
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct TreeNode_68a580 {
    void* mpNodeRight; void* mpNodeLeft; void* mpNodeParent; int mColor;   // +0x00
    TreeValue_68a580 mValue;                                                  // +0x10
};
struct Tree_68a580 {
    TreeNode_68a580* DoCreateNode(const TreeValue_68a580& value);
};

// @ 0x0068a580
TreeNode_68a580* Tree_68a580::DoCreateNode(const TreeValue_68a580& value)
{
    TreeNode_68a580* n = (TreeNode_68a580*)EaAlloc_68a580(sizeof(TreeNode_68a580), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&n->mValue) TreeValue_68a580(value);
    return n;
}
