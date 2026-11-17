// rb-tree insertion (0x00801cf0): pick the side, create the 0x34-byte node inline (the key is copied and the mapped value copy-constructed (0x801c80)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_801cf0(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_801cf0 { RBNodeBase_801cf0* mpNodeRight; RBNodeBase_801cf0* mpNodeLeft; RBNodeBase_801cf0* mpNodeParent; int mColor; };
void RBTreeInsert_801cf0(RBNodeBase_801cf0* pNode, RBNodeBase_801cf0* pNodeParent, RBNodeBase_801cf0* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Mapped_801cf0 {
    char mData[0x20];
    Mapped_801cf0(const Mapped_801cf0& o);   // 0x00801c80
};
struct Value_801cf0 {
    uint32_t first;
    Mapped_801cf0 second;
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_801cf0 : RBNodeBase_801cf0 {
    Value_801cf0 mValue;                         // +0x10
};
struct Iterator_801cf0 {
    Node_801cf0* mpNode;
    explicit Iterator_801cf0(Node_801cf0* p) : mpNode(p) {}
};
struct Tree_801cf0 {
    int mCompare;                             // +0x00
    RBNodeBase_801cf0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_801cf0 DoInsertValueImpl(Node_801cf0* pNodeParent, const Value_801cf0& value, bool bForceToLeft);
};

// @ 0x00801cf0
Iterator_801cf0 Tree_801cf0::DoInsertValueImpl(Node_801cf0* pNodeParent, const Value_801cf0& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_801cf0*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_801cf0* pNodeNew = (Node_801cf0*)EaAlloc_801cf0(sizeof(Node_801cf0), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_801cf0(value);
    RBTreeInsert_801cf0(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_801cf0(pNodeNew);
}
