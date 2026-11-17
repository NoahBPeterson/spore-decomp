// rb-tree insertion (0x00ba83a0): pick the side, create the 0x18-byte node inline (the key/value pair is copied), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_ba83a0(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_ba83a0 { RBNodeBase_ba83a0* mpNodeRight; RBNodeBase_ba83a0* mpNodeLeft; RBNodeBase_ba83a0* mpNodeParent; int mColor; };
void RBTreeInsert_ba83a0(RBNodeBase_ba83a0* pNode, RBNodeBase_ba83a0* pNodeParent, RBNodeBase_ba83a0* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_ba83a0 {
    uint32_t first;
    uint32_t second;
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_ba83a0 : RBNodeBase_ba83a0 {
    Value_ba83a0 mValue;                         // +0x10
};
struct Iterator_ba83a0 {
    Node_ba83a0* mpNode;
    explicit Iterator_ba83a0(Node_ba83a0* p) : mpNode(p) {}
};
struct Tree_ba83a0 {
    int mCompare;                             // +0x00
    RBNodeBase_ba83a0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_ba83a0 DoInsertValueImpl(Node_ba83a0* pNodeParent, const Value_ba83a0& value, bool bForceToLeft);
};

// @ 0x00ba83a0
Iterator_ba83a0 Tree_ba83a0::DoInsertValueImpl(Node_ba83a0* pNodeParent, const Value_ba83a0& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_ba83a0*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_ba83a0* pNodeNew = (Node_ba83a0*)EaAlloc_ba83a0(sizeof(Node_ba83a0), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_ba83a0(value);
    RBTreeInsert_ba83a0(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_ba83a0(pNodeNew);
}
