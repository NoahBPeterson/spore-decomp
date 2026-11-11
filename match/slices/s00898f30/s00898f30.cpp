// Slice s00898f30: eastl red-black-tree node creation (MSVC 2008 SP1, /O2).
//
// DoCreateNode(const value_type&): pop a slot from the tree's node free list or
// allocate one through the EASTL tagged allocator, then construct the 16-byte
// value in the slot at +0x10.
#include "types.h"

typedef unsigned int u32;

// 0x00f473a0: eastl tagged allocation (size, name, flags, align, file, line).
void* __cdecl FUN_00f473a0(u32 size, const char* pName, int a, int b, const char* pFile, int line);

// The four-dword user value stored at the tail of a tree node.
struct RBValue {
    u32 a, b, c, d;
};

// One fixed-pool node: the pool links free slots through the first dword; the
// user value starts at +0x10.
struct RBNode {
    RBNode* mpNext;             // +0x00
    u32     mPad04[3];          // +0x04..+0x0f
    RBValue mValue;             // +0x10
};

struct RBTree {
    u32     mPad00[0x18 / 4];   // +0x00
    RBNode* mpFreeList;         // +0x18
    u32     mPad1c[0x28 / 4 - 0x1c / 4];   // +0x1c
    u32     mNodeSize;          // +0x28

    RBNode* DoCreateNode(const RBValue* pValue);
};

// @ 0x00898f30
RBNode* RBTree::DoCreateNode(const RBValue* pValue)
{
    RBNode* node = mpFreeList;
    if (node != 0) {
        mpFreeList = node->mpNext;
    } else {
        u32 nSize = mNodeSize;
        node = (RBNode*)FUN_00f473a0(
            nSize, "EASTL", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    }
    if (&node->mValue != 0)
        node->mValue = *pValue;
    return node;
}
