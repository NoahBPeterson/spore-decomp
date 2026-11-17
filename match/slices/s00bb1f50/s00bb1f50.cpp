// rb-tree insertion (0x00bb1f50): pick the side, create the 0x48-byte node inline (the key is copied and the mapped value copy-constructed (0xbae0a0)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_bb1f50(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_bb1f50 { RBNodeBase_bb1f50* mpNodeRight; RBNodeBase_bb1f50* mpNodeLeft; RBNodeBase_bb1f50* mpNodeParent; int mColor; };
void RBTreeInsert_bb1f50(RBNodeBase_bb1f50* pNode, RBNodeBase_bb1f50* pNodeParent, RBNodeBase_bb1f50* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Mapped_bb1f50 {
    char mData[0x34];
    Mapped_bb1f50(const Mapped_bb1f50& o);   // 0x00bae0a0
};
struct Value_bb1f50 {
    uint32_t first;
    Mapped_bb1f50 second;
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_bb1f50 : RBNodeBase_bb1f50 {
    Value_bb1f50 mValue;                         // +0x10
};
struct Iterator_bb1f50 {
    Node_bb1f50* mpNode;
    explicit Iterator_bb1f50(Node_bb1f50* p) : mpNode(p) {}
};
struct Tree_bb1f50 {
    int mCompare;                             // +0x00
    RBNodeBase_bb1f50 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_bb1f50 DoInsertValueImpl(Node_bb1f50* pNodeParent, const Value_bb1f50& value, bool bForceToLeft);
};

// @ 0x00bb1f50
Iterator_bb1f50 Tree_bb1f50::DoInsertValueImpl(Node_bb1f50* pNodeParent, const Value_bb1f50& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_bb1f50*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_bb1f50* pNodeNew = (Node_bb1f50*)EaAlloc_bb1f50(sizeof(Node_bb1f50), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_bb1f50(value);
    RBTreeInsert_bb1f50(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_bb1f50(pNodeNew);
}
