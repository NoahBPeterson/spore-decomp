// rb-tree insertion (0x00660770): pick the side, create the 0x34-byte node inline (the value is copy-constructed (0x65fcd0)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_660770(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_660770 { RBNodeBase_660770* mpNodeRight; RBNodeBase_660770* mpNodeLeft; RBNodeBase_660770* mpNodeParent; int mColor; };
void RBTreeInsert_660770(RBNodeBase_660770* pNode, RBNodeBase_660770* pNodeParent, RBNodeBase_660770* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_660770 {
    uint32_t first;
    char mRest[0x20];
    Value_660770(const Value_660770& o);   // 0x0065fcd0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_660770 : RBNodeBase_660770 {
    Value_660770 mValue;                         // +0x10
};
struct Iterator_660770 {
    Node_660770* mpNode;
    explicit Iterator_660770(Node_660770* p) : mpNode(p) {}
};
struct Tree_660770 {
    int mCompare;                             // +0x00
    RBNodeBase_660770 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_660770 DoInsertValueImpl(Node_660770* pNodeParent, const Value_660770& value, bool bForceToLeft);
};

// @ 0x00660770
Iterator_660770 Tree_660770::DoInsertValueImpl(Node_660770* pNodeParent, const Value_660770& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_660770*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_660770* pNodeNew = (Node_660770*)EaAlloc_660770(sizeof(Node_660770), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_660770(value);
    RBTreeInsert_660770(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_660770(pNodeNew);
}
