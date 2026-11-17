// rb-tree insertion (0x005d9a50): pick the side, create the 0x28-byte node inline (the value is copy-constructed (0x5d9680)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_5d9a50(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_5d9a50 { RBNodeBase_5d9a50* mpNodeRight; RBNodeBase_5d9a50* mpNodeLeft; RBNodeBase_5d9a50* mpNodeParent; int mColor; };
void RBTreeInsert_5d9a50(RBNodeBase_5d9a50* pNode, RBNodeBase_5d9a50* pNodeParent, RBNodeBase_5d9a50* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_5d9a50 {
    uint32_t first;
    char mRest[0x14];
    Value_5d9a50(const Value_5d9a50& o);   // 0x005d9680
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_5d9a50 : RBNodeBase_5d9a50 {
    Value_5d9a50 mValue;                         // +0x10
};
struct Iterator_5d9a50 {
    Node_5d9a50* mpNode;
    explicit Iterator_5d9a50(Node_5d9a50* p) : mpNode(p) {}
};
struct Tree_5d9a50 {
    int mCompare;                             // +0x00
    RBNodeBase_5d9a50 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_5d9a50 DoInsertValueImpl(Node_5d9a50* pNodeParent, const Value_5d9a50& value, bool bForceToLeft);
};

// @ 0x005d9a50
Iterator_5d9a50 Tree_5d9a50::DoInsertValueImpl(Node_5d9a50* pNodeParent, const Value_5d9a50& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_5d9a50*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_5d9a50* pNodeNew = (Node_5d9a50*)EaAlloc_5d9a50(sizeof(Node_5d9a50), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_5d9a50(value);
    RBTreeInsert_5d9a50(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_5d9a50(pNodeNew);
}
