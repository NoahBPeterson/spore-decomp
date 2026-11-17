// rb-tree insertion (0x00e2b760): pick the side, create the 0x28-byte node inline (the key is copied and the mapped value copy-constructed (0x6b56f0)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_e2b760(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_e2b760 { RBNodeBase_e2b760* mpNodeRight; RBNodeBase_e2b760* mpNodeLeft; RBNodeBase_e2b760* mpNodeParent; int mColor; };
void RBTreeInsert_e2b760(RBNodeBase_e2b760* pNode, RBNodeBase_e2b760* pNodeParent, RBNodeBase_e2b760* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Mapped_e2b760 {
    char mData[0x14];
    Mapped_e2b760(const Mapped_e2b760& o);   // 0x006b56f0
};
struct Value_e2b760 {
    uint32_t first;
    Mapped_e2b760 second;
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_e2b760 : RBNodeBase_e2b760 {
    Value_e2b760 mValue;                         // +0x10
};
struct Iterator_e2b760 {
    Node_e2b760* mpNode;
    explicit Iterator_e2b760(Node_e2b760* p) : mpNode(p) {}
};
struct Tree_e2b760 {
    int mCompare;                             // +0x00
    RBNodeBase_e2b760 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_e2b760 DoInsertValueImpl(Node_e2b760* pNodeParent, const Value_e2b760& value, bool bForceToLeft);
};

// @ 0x00e2b760
Iterator_e2b760 Tree_e2b760::DoInsertValueImpl(Node_e2b760* pNodeParent, const Value_e2b760& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_e2b760*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_e2b760* pNodeNew = (Node_e2b760*)EaAlloc_e2b760(sizeof(Node_e2b760), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_e2b760(value);
    RBTreeInsert_e2b760(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_e2b760(pNodeNew);
}
