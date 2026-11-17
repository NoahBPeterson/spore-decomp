// rb-tree insertion (0x00579b50): pick the side, create the 0x18-byte node inline (the key/value pair is copied), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_579b50(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_579b50 { RBNodeBase_579b50* mpNodeRight; RBNodeBase_579b50* mpNodeLeft; RBNodeBase_579b50* mpNodeParent; int mColor; };
void RBTreeInsert_579b50(RBNodeBase_579b50* pNode, RBNodeBase_579b50* pNodeParent, RBNodeBase_579b50* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_579b50 {
    uint32_t first;
    uint32_t second;
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_579b50 : RBNodeBase_579b50 {
    Value_579b50 mValue;                         // +0x10
};
struct Iterator_579b50 {
    Node_579b50* mpNode;
    explicit Iterator_579b50(Node_579b50* p) : mpNode(p) {}
};
struct Tree_579b50 {
    int mCompare;                             // +0x00
    RBNodeBase_579b50 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_579b50 DoInsertValueImpl(Node_579b50* pNodeParent, const Value_579b50& value, bool bForceToLeft);
};

// @ 0x00579b50
Iterator_579b50 Tree_579b50::DoInsertValueImpl(Node_579b50* pNodeParent, const Value_579b50& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_579b50*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_579b50* pNodeNew = (Node_579b50*)EaAlloc_579b50(sizeof(Node_579b50), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_579b50(value);
    RBTreeInsert_579b50(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_579b50(pNodeNew);
}
