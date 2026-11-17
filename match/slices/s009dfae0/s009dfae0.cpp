// rb-tree insertion (0x009dfae0): pick the side, create the 0x18-byte node inline (the key/value pair is copied), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_9dfae0(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_9dfae0 { RBNodeBase_9dfae0* mpNodeRight; RBNodeBase_9dfae0* mpNodeLeft; RBNodeBase_9dfae0* mpNodeParent; int mColor; };
void RBTreeInsert_9dfae0(RBNodeBase_9dfae0* pNode, RBNodeBase_9dfae0* pNodeParent, RBNodeBase_9dfae0* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_9dfae0 {
    uint32_t first;
    uint32_t second;
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_9dfae0 : RBNodeBase_9dfae0 {
    Value_9dfae0 mValue;                         // +0x10
};
struct Iterator_9dfae0 {
    Node_9dfae0* mpNode;
    explicit Iterator_9dfae0(Node_9dfae0* p) : mpNode(p) {}
};
struct Tree_9dfae0 {
    int mCompare;                             // +0x00
    RBNodeBase_9dfae0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_9dfae0 DoInsertValueImpl(Node_9dfae0* pNodeParent, const Value_9dfae0& value, bool bForceToLeft);
};

// @ 0x009dfae0
Iterator_9dfae0 Tree_9dfae0::DoInsertValueImpl(Node_9dfae0* pNodeParent, const Value_9dfae0& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_9dfae0*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_9dfae0* pNodeNew = (Node_9dfae0*)EaAlloc_9dfae0(sizeof(Node_9dfae0), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_9dfae0(value);
    RBTreeInsert_9dfae0(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_9dfae0(pNodeNew);
}
