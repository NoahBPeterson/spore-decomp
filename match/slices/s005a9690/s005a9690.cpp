// rb-tree insertion (0x005a9690): pick the side, create the 0x28-byte node inline (the value is copy-constructed (0x5a9610)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_5a9690(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_5a9690 { RBNodeBase_5a9690* mpNodeRight; RBNodeBase_5a9690* mpNodeLeft; RBNodeBase_5a9690* mpNodeParent; int mColor; };
void RBTreeInsert_5a9690(RBNodeBase_5a9690* pNode, RBNodeBase_5a9690* pNodeParent, RBNodeBase_5a9690* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_5a9690 {
    uint32_t first;
    char mRest[0x14];
    Value_5a9690(const Value_5a9690& o);   // 0x005a9610
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_5a9690 : RBNodeBase_5a9690 {
    Value_5a9690 mValue;                         // +0x10
};
struct Iterator_5a9690 {
    Node_5a9690* mpNode;
    explicit Iterator_5a9690(Node_5a9690* p) : mpNode(p) {}
};
struct Tree_5a9690 {
    int mCompare;                             // +0x00
    RBNodeBase_5a9690 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_5a9690 DoInsertValueImpl(Node_5a9690* pNodeParent, const Value_5a9690& value, bool bForceToLeft);
};

// @ 0x005a9690
Iterator_5a9690 Tree_5a9690::DoInsertValueImpl(Node_5a9690* pNodeParent, const Value_5a9690& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_5a9690*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_5a9690* pNodeNew = (Node_5a9690*)EaAlloc_5a9690(sizeof(Node_5a9690), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_5a9690(value);
    RBTreeInsert_5a9690(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_5a9690(pNodeNew);
}
