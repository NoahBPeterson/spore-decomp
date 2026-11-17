// rb-tree insertion (0x00e0ef00): pick the side, create the 0x38-byte node inline (the value is copy-constructed (0xe0c6b0)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_e0ef00(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_e0ef00 { RBNodeBase_e0ef00* mpNodeRight; RBNodeBase_e0ef00* mpNodeLeft; RBNodeBase_e0ef00* mpNodeParent; int mColor; };
void RBTreeInsert_e0ef00(RBNodeBase_e0ef00* pNode, RBNodeBase_e0ef00* pNodeParent, RBNodeBase_e0ef00* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_e0ef00 {
    uint32_t first;
    char mRest[0x24];
    Value_e0ef00(const Value_e0ef00& o);   // 0x00e0c6b0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_e0ef00 : RBNodeBase_e0ef00 {
    Value_e0ef00 mValue;                         // +0x10
};
struct Iterator_e0ef00 {
    Node_e0ef00* mpNode;
    explicit Iterator_e0ef00(Node_e0ef00* p) : mpNode(p) {}
};
struct Tree_e0ef00 {
    int mCompare;                             // +0x00
    RBNodeBase_e0ef00 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_e0ef00 DoInsertValueImpl(Node_e0ef00* pNodeParent, const Value_e0ef00& value, bool bForceToLeft);
};

// @ 0x00e0ef00
Iterator_e0ef00 Tree_e0ef00::DoInsertValueImpl(Node_e0ef00* pNodeParent, const Value_e0ef00& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_e0ef00*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_e0ef00* pNodeNew = (Node_e0ef00*)EaAlloc_e0ef00(sizeof(Node_e0ef00), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_e0ef00(value);
    RBTreeInsert_e0ef00(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_e0ef00(pNodeNew);
}
