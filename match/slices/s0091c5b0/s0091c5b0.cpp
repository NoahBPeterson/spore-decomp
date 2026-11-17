// rb-tree insertion (0x0091c5b0): pick the side, create the 0x40-byte node inline (the key is copied and the mapped value copy-constructed (0x91c140)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_91c5b0(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_91c5b0 { RBNodeBase_91c5b0* mpNodeRight; RBNodeBase_91c5b0* mpNodeLeft; RBNodeBase_91c5b0* mpNodeParent; int mColor; };
void RBTreeInsert_91c5b0(RBNodeBase_91c5b0* pNode, RBNodeBase_91c5b0* pNodeParent, RBNodeBase_91c5b0* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Mapped_91c5b0 {
    char mData[0x2c];
    Mapped_91c5b0(const Mapped_91c5b0& o);   // 0x0091c140
};
struct Value_91c5b0 {
    uint32_t first;
    Mapped_91c5b0 second;
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_91c5b0 : RBNodeBase_91c5b0 {
    Value_91c5b0 mValue;                         // +0x10
};
struct Iterator_91c5b0 {
    Node_91c5b0* mpNode;
    explicit Iterator_91c5b0(Node_91c5b0* p) : mpNode(p) {}
};
struct Tree_91c5b0 {
    int mCompare;                             // +0x00
    RBNodeBase_91c5b0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_91c5b0 DoInsertValueImpl(Node_91c5b0* pNodeParent, const Value_91c5b0& value, bool bForceToLeft);
};

// @ 0x0091c5b0
Iterator_91c5b0 Tree_91c5b0::DoInsertValueImpl(Node_91c5b0* pNodeParent, const Value_91c5b0& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_91c5b0*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_91c5b0* pNodeNew = (Node_91c5b0*)EaAlloc_91c5b0(sizeof(Node_91c5b0), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_91c5b0(value);
    RBTreeInsert_91c5b0(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_91c5b0(pNodeNew);
}
