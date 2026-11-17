// rb-tree insertion (0x00b1a3b0): pick the side, create the 0x24-byte node inline (the value is copy-constructed (0xb20b90)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_b1a3b0(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_b1a3b0 { RBNodeBase_b1a3b0* mpNodeRight; RBNodeBase_b1a3b0* mpNodeLeft; RBNodeBase_b1a3b0* mpNodeParent; int mColor; };
void RBTreeInsert_b1a3b0(RBNodeBase_b1a3b0* pNode, RBNodeBase_b1a3b0* pNodeParent, RBNodeBase_b1a3b0* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_b1a3b0 {
    uint32_t first;
    char mRest[0x10];
    Value_b1a3b0(const Value_b1a3b0& o);   // 0x00b20b90
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_b1a3b0 : RBNodeBase_b1a3b0 {
    Value_b1a3b0 mValue;                         // +0x10
};
struct Iterator_b1a3b0 {
    Node_b1a3b0* mpNode;
    explicit Iterator_b1a3b0(Node_b1a3b0* p) : mpNode(p) {}
};
struct Tree_b1a3b0 {
    int mCompare;                             // +0x00
    RBNodeBase_b1a3b0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_b1a3b0 DoInsertValueImpl(Node_b1a3b0* pNodeParent, const Value_b1a3b0& value, bool bForceToLeft);
};

// @ 0x00b1a3b0
Iterator_b1a3b0 Tree_b1a3b0::DoInsertValueImpl(Node_b1a3b0* pNodeParent, const Value_b1a3b0& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_b1a3b0*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_b1a3b0* pNodeNew = (Node_b1a3b0*)EaAlloc_b1a3b0(sizeof(Node_b1a3b0), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_b1a3b0(value);
    RBTreeInsert_b1a3b0(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_b1a3b0(pNodeNew);
}
