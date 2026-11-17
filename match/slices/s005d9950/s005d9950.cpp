// rb-tree insertion (0x005d9950): pick the side, create the 0x28-byte node inline (the value is copy-constructed (0x5d95c0)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_5d9950(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_5d9950 { RBNodeBase_5d9950* mpNodeRight; RBNodeBase_5d9950* mpNodeLeft; RBNodeBase_5d9950* mpNodeParent; int mColor; };
void RBTreeInsert_5d9950(RBNodeBase_5d9950* pNode, RBNodeBase_5d9950* pNodeParent, RBNodeBase_5d9950* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_5d9950 {
    uint32_t first;
    char mRest[0x14];
    Value_5d9950(const Value_5d9950& o);   // 0x005d95c0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_5d9950 : RBNodeBase_5d9950 {
    Value_5d9950 mValue;                         // +0x10
};
struct Iterator_5d9950 {
    Node_5d9950* mpNode;
    explicit Iterator_5d9950(Node_5d9950* p) : mpNode(p) {}
};
struct Tree_5d9950 {
    int mCompare;                             // +0x00
    RBNodeBase_5d9950 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_5d9950 DoInsertValueImpl(Node_5d9950* pNodeParent, const Value_5d9950& value, bool bForceToLeft);
};

// @ 0x005d9950
Iterator_5d9950 Tree_5d9950::DoInsertValueImpl(Node_5d9950* pNodeParent, const Value_5d9950& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_5d9950*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_5d9950* pNodeNew = (Node_5d9950*)EaAlloc_5d9950(sizeof(Node_5d9950), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_5d9950(value);
    RBTreeInsert_5d9950(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_5d9950(pNodeNew);
}
