// rb-tree insertion (0x00cc5590): pick the side, create the 0x38-byte node inline (the value is copy-constructed (0xcc5230)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_cc5590(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_cc5590 { RBNodeBase_cc5590* mpNodeRight; RBNodeBase_cc5590* mpNodeLeft; RBNodeBase_cc5590* mpNodeParent; int mColor; };
void RBTreeInsert_cc5590(RBNodeBase_cc5590* pNode, RBNodeBase_cc5590* pNodeParent, RBNodeBase_cc5590* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_cc5590 {
    uint32_t first;
    char mRest[0x24];
    Value_cc5590(const Value_cc5590& o);   // 0x00cc5230
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_cc5590 : RBNodeBase_cc5590 {
    Value_cc5590 mValue;                         // +0x10
};
struct Iterator_cc5590 {
    Node_cc5590* mpNode;
    explicit Iterator_cc5590(Node_cc5590* p) : mpNode(p) {}
};
struct Tree_cc5590 {
    int mCompare;                             // +0x00
    RBNodeBase_cc5590 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_cc5590 DoInsertValueImpl(Node_cc5590* pNodeParent, const Value_cc5590& value, bool bForceToLeft);
};

// @ 0x00cc5590
Iterator_cc5590 Tree_cc5590::DoInsertValueImpl(Node_cc5590* pNodeParent, const Value_cc5590& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_cc5590*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_cc5590* pNodeNew = (Node_cc5590*)EaAlloc_cc5590(sizeof(Node_cc5590), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_cc5590(value);
    RBTreeInsert_cc5590(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_cc5590(pNodeNew);
}
