// rb-tree insertion (0x00b1a690): pick the side, create the 0x28-byte node inline (the key is copied and the mapped value copy-constructed (0xb1a350)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_b1a690(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_b1a690 { RBNodeBase_b1a690* mpNodeRight; RBNodeBase_b1a690* mpNodeLeft; RBNodeBase_b1a690* mpNodeParent; int mColor; };
void RBTreeInsert_b1a690(RBNodeBase_b1a690* pNode, RBNodeBase_b1a690* pNodeParent, RBNodeBase_b1a690* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Mapped_b1a690 {
    char mData[0x14];
    Mapped_b1a690(const Mapped_b1a690& o);   // 0x00b1a350
};
struct Value_b1a690 {
    uint32_t first;
    Mapped_b1a690 second;
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_b1a690 : RBNodeBase_b1a690 {
    Value_b1a690 mValue;                         // +0x10
};
struct Iterator_b1a690 {
    Node_b1a690* mpNode;
    explicit Iterator_b1a690(Node_b1a690* p) : mpNode(p) {}
};
struct Tree_b1a690 {
    int mCompare;                             // +0x00
    RBNodeBase_b1a690 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_b1a690 DoInsertValueImpl(Node_b1a690* pNodeParent, const Value_b1a690& value, bool bForceToLeft);
};

// @ 0x00b1a690
Iterator_b1a690 Tree_b1a690::DoInsertValueImpl(Node_b1a690* pNodeParent, const Value_b1a690& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_b1a690*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_b1a690* pNodeNew = (Node_b1a690*)EaAlloc_b1a690(sizeof(Node_b1a690), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_b1a690(value);
    RBTreeInsert_b1a690(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_b1a690(pNodeNew);
}
