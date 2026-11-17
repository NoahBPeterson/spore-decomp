// rb-tree insertion (0x00a0dc70): pick the side, create the 0x54-byte node inline (the key is copied and the mapped value copy-constructed (0xa0d7a0)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_a0dc70(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_a0dc70 { RBNodeBase_a0dc70* mpNodeRight; RBNodeBase_a0dc70* mpNodeLeft; RBNodeBase_a0dc70* mpNodeParent; int mColor; };
void RBTreeInsert_a0dc70(RBNodeBase_a0dc70* pNode, RBNodeBase_a0dc70* pNodeParent, RBNodeBase_a0dc70* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Mapped_a0dc70 {
    char mData[0x40];
    Mapped_a0dc70(const Mapped_a0dc70& o);   // 0x00a0d7a0
};
struct Value_a0dc70 {
    uint32_t first;
    Mapped_a0dc70 second;
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_a0dc70 : RBNodeBase_a0dc70 {
    Value_a0dc70 mValue;                         // +0x10
};
struct Iterator_a0dc70 {
    Node_a0dc70* mpNode;
    explicit Iterator_a0dc70(Node_a0dc70* p) : mpNode(p) {}
};
struct Tree_a0dc70 {
    int mCompare;                             // +0x00
    RBNodeBase_a0dc70 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_a0dc70 DoInsertValueImpl(Node_a0dc70* pNodeParent, const Value_a0dc70& value, bool bForceToLeft);
};

// @ 0x00a0dc70
Iterator_a0dc70 Tree_a0dc70::DoInsertValueImpl(Node_a0dc70* pNodeParent, const Value_a0dc70& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_a0dc70*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_a0dc70* pNodeNew = (Node_a0dc70*)EaAlloc_a0dc70(sizeof(Node_a0dc70), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_a0dc70(value);
    RBTreeInsert_a0dc70(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_a0dc70(pNodeNew);
}
