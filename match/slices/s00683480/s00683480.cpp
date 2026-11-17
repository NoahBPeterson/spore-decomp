// Tree node allocation (0x00683480): allocate a 0x64-byte rb-tree node and copy-construct its value: the key is copied
// and the 0x50-byte mapped value is copy-constructed (0x682a10).
#include "game/types.h"

void* EaAlloc_683480(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0

struct Mapped_683480 {
    char mData[0x50];
    Mapped_683480(const Mapped_683480& o);   // 0x00682a10
};
struct TreeValue_683480 {
    uint32_t first;
    Mapped_683480 second;
    static void* operator new(size_t, void* p) throw() { return p; }
    static void operator delete(void*, void*) throw() {}
};
struct TreeNode_683480 {
    void* mpNodeRight; void* mpNodeLeft; void* mpNodeParent; int mColor;   // +0x00
    TreeValue_683480 mValue;                                                  // +0x10
};
struct Tree_683480 {
    TreeNode_683480* DoCreateNode(const TreeValue_683480& value);
};

// @ 0x00683480
TreeNode_683480* Tree_683480::DoCreateNode(const TreeValue_683480& value)
{
    TreeNode_683480* n = (TreeNode_683480*)EaAlloc_683480(sizeof(TreeNode_683480), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&n->mValue) TreeValue_683480(value);
    return n;
}
