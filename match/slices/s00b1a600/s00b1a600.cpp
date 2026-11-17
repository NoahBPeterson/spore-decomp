// rb-tree insertion (0x00b1a600): pick the side, create the 0x24-byte node inline (the value is copy-constructed (0x9fc440)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_b1a600(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_b1a600 { RBNodeBase_b1a600* mpNodeRight; RBNodeBase_b1a600* mpNodeLeft; RBNodeBase_b1a600* mpNodeParent; int mColor; };
void RBTreeInsert_b1a600(RBNodeBase_b1a600* pNode, RBNodeBase_b1a600* pNodeParent, RBNodeBase_b1a600* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_b1a600 {
    uint32_t first;
    char mRest[0x10];
    Value_b1a600(const Value_b1a600& o);   // 0x009fc440
    static void* operator new(size_t, void* p) throw() { return p; }
};
bool KeyLess_b1a600(const Value_b1a600& a, const Value_b1a600& b);   // 0x00812210
struct Node_b1a600 : RBNodeBase_b1a600 {
    Value_b1a600 mValue;                         // +0x10
};
struct Iterator_b1a600 {
    Node_b1a600* mpNode;
    explicit Iterator_b1a600(Node_b1a600* p) : mpNode(p) {}
};
struct Tree_b1a600 {
    int mCompare;                             // +0x00
    RBNodeBase_b1a600 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_b1a600 DoInsertValueImpl(Node_b1a600* pNodeParent, const Value_b1a600& value, bool bForceToLeft);
};

// @ 0x00b1a600
Iterator_b1a600 Tree_b1a600::DoInsertValueImpl(Node_b1a600* pNodeParent, const Value_b1a600& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_b1a600*)&mAnchor || KeyLess_b1a600(value, pNodeParent->mValue))
        side = 0;
    else
        side = 1;
    Node_b1a600* pNodeNew = (Node_b1a600*)EaAlloc_b1a600(sizeof(Node_b1a600), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_b1a600(value);
    RBTreeInsert_b1a600(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_b1a600(pNodeNew);
}
