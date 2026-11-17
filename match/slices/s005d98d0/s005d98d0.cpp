// rb-tree insertion (0x005d98d0): pick the side, create the 0x28-byte node inline (the value is copy-constructed (0x5d9560)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_5d98d0(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_5d98d0 { RBNodeBase_5d98d0* mpNodeRight; RBNodeBase_5d98d0* mpNodeLeft; RBNodeBase_5d98d0* mpNodeParent; int mColor; };
void RBTreeInsert_5d98d0(RBNodeBase_5d98d0* pNode, RBNodeBase_5d98d0* pNodeParent, RBNodeBase_5d98d0* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_5d98d0 {
    uint32_t first;
    char mRest[0x14];
    Value_5d98d0(const Value_5d98d0& o);   // 0x005d9560
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_5d98d0 : RBNodeBase_5d98d0 {
    Value_5d98d0 mValue;                         // +0x10
};
struct Iterator_5d98d0 {
    Node_5d98d0* mpNode;
    explicit Iterator_5d98d0(Node_5d98d0* p) : mpNode(p) {}
};
struct Tree_5d98d0 {
    int mCompare;                             // +0x00
    RBNodeBase_5d98d0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_5d98d0 DoInsertValueImpl(Node_5d98d0* pNodeParent, const Value_5d98d0& value, bool bForceToLeft);
};

// @ 0x005d98d0
Iterator_5d98d0 Tree_5d98d0::DoInsertValueImpl(Node_5d98d0* pNodeParent, const Value_5d98d0& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_5d98d0*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_5d98d0* pNodeNew = (Node_5d98d0*)EaAlloc_5d98d0(sizeof(Node_5d98d0), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_5d98d0(value);
    RBTreeInsert_5d98d0(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_5d98d0(pNodeNew);
}
