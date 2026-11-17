// rb-tree insertion (0x00c78390): pick the side, create the 0x58-byte node inline (the key is copied and the mapped value copy-constructed (0xc76f60)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_c78390(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_c78390 { RBNodeBase_c78390* mpNodeRight; RBNodeBase_c78390* mpNodeLeft; RBNodeBase_c78390* mpNodeParent; int mColor; };
void RBTreeInsert_c78390(RBNodeBase_c78390* pNode, RBNodeBase_c78390* pNodeParent, RBNodeBase_c78390* pNodeAnchor, int insertionSide);  // 0x009216a0

struct __declspec(align(8)) Mapped_c78390 {
    char mData[0x40];
    Mapped_c78390(const Mapped_c78390& o);   // 0x00c76f60
};
struct Value_c78390 {
    uint32_t first;
    Mapped_c78390 second;
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_c78390 : RBNodeBase_c78390 {
    Value_c78390 mValue;                         // +0x10
};
struct Iterator_c78390 {
    Node_c78390* mpNode;
    explicit Iterator_c78390(Node_c78390* p) : mpNode(p) {}
};
struct Tree_c78390 {
    int mCompare;                             // +0x00
    RBNodeBase_c78390 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_c78390 DoInsertValueImpl(Node_c78390* pNodeParent, const Value_c78390& value, bool bForceToLeft);
};

// @ 0x00c78390
Iterator_c78390 Tree_c78390::DoInsertValueImpl(Node_c78390* pNodeParent, const Value_c78390& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_c78390*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_c78390* pNodeNew = (Node_c78390*)EaAlloc_c78390(sizeof(Node_c78390), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_c78390(value);
    RBTreeInsert_c78390(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_c78390(pNodeNew);
}
