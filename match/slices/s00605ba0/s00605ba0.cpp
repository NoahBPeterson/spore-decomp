// rb-tree insertion (0x00605ba0): pick the side, create the 0x28-byte node inline (the value is copy-constructed (0x605a60)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_605ba0(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_605ba0 { RBNodeBase_605ba0* mpNodeRight; RBNodeBase_605ba0* mpNodeLeft; RBNodeBase_605ba0* mpNodeParent; int mColor; };
void RBTreeInsert_605ba0(RBNodeBase_605ba0* pNode, RBNodeBase_605ba0* pNodeParent, RBNodeBase_605ba0* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_605ba0 {
    uint32_t first;
    char mRest[0x14];
    Value_605ba0(const Value_605ba0& o);   // 0x00605a60
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_605ba0 : RBNodeBase_605ba0 {
    Value_605ba0 mValue;                         // +0x10
};
struct Iterator_605ba0 {
    Node_605ba0* mpNode;
    explicit Iterator_605ba0(Node_605ba0* p) : mpNode(p) {}
};
struct Tree_605ba0 {
    int mCompare;                             // +0x00
    RBNodeBase_605ba0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_605ba0 DoInsertValueImpl(Node_605ba0* pNodeParent, const Value_605ba0& value, bool bForceToLeft);
};

// @ 0x00605ba0
Iterator_605ba0 Tree_605ba0::DoInsertValueImpl(Node_605ba0* pNodeParent, const Value_605ba0& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_605ba0*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_605ba0* pNodeNew = (Node_605ba0*)EaAlloc_605ba0(sizeof(Node_605ba0), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_605ba0(value);
    RBTreeInsert_605ba0(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_605ba0(pNodeNew);
}
