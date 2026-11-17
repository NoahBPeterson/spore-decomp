// rb-tree insertion (0x00a24640): pick the side, create the 0x18-byte node inline (the key/value pair is copied), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_a24640(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_a24640 { RBNodeBase_a24640* mpNodeRight; RBNodeBase_a24640* mpNodeLeft; RBNodeBase_a24640* mpNodeParent; int mColor; };
void RBTreeInsert_a24640(RBNodeBase_a24640* pNode, RBNodeBase_a24640* pNodeParent, RBNodeBase_a24640* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_a24640 {
    uint32_t first;
    uint32_t second;
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_a24640 : RBNodeBase_a24640 {
    Value_a24640 mValue;                         // +0x10
};
struct Iterator_a24640 {
    Node_a24640* mpNode;
    explicit Iterator_a24640(Node_a24640* p) : mpNode(p) {}
};
struct Tree_a24640 {
    int mCompare;                             // +0x00
    RBNodeBase_a24640 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_a24640 DoInsertValueImpl(Node_a24640* pNodeParent, const Value_a24640& value, bool bForceToLeft);
};

// @ 0x00a24640
Iterator_a24640 Tree_a24640::DoInsertValueImpl(Node_a24640* pNodeParent, const Value_a24640& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_a24640*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_a24640* pNodeNew = (Node_a24640*)EaAlloc_a24640(sizeof(Node_a24640), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_a24640(value);
    RBTreeInsert_a24640(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_a24640(pNodeNew);
}
