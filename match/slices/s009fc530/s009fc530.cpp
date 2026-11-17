// rb-tree insertion (0x009fc530): pick the side, create the 0x18-byte node inline (the key/value pair is copied), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_9fc530(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_9fc530 { RBNodeBase_9fc530* mpNodeRight; RBNodeBase_9fc530* mpNodeLeft; RBNodeBase_9fc530* mpNodeParent; int mColor; };
void RBTreeInsert_9fc530(RBNodeBase_9fc530* pNode, RBNodeBase_9fc530* pNodeParent, RBNodeBase_9fc530* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_9fc530 {
    uint32_t first;
    uint32_t second;
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_9fc530 : RBNodeBase_9fc530 {
    Value_9fc530 mValue;                         // +0x10
};
struct Iterator_9fc530 {
    Node_9fc530* mpNode;
    explicit Iterator_9fc530(Node_9fc530* p) : mpNode(p) {}
};
struct Tree_9fc530 {
    int mCompare;                             // +0x00
    RBNodeBase_9fc530 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_9fc530 DoInsertValueImpl(Node_9fc530* pNodeParent, const Value_9fc530& value, bool bForceToLeft);
};

// @ 0x009fc530
Iterator_9fc530 Tree_9fc530::DoInsertValueImpl(Node_9fc530* pNodeParent, const Value_9fc530& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_9fc530*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_9fc530* pNodeNew = (Node_9fc530*)EaAlloc_9fc530(sizeof(Node_9fc530), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_9fc530(value);
    RBTreeInsert_9fc530(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_9fc530(pNodeNew);
}
