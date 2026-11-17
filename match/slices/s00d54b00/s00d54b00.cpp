// rb-tree insertion (0x00d54b00): pick the side, create the 0x40-byte node inline (the value is copy-constructed (0xd54780)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_d54b00(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_d54b00 { RBNodeBase_d54b00* mpNodeRight; RBNodeBase_d54b00* mpNodeLeft; RBNodeBase_d54b00* mpNodeParent; int mColor; };
void RBTreeInsert_d54b00(RBNodeBase_d54b00* pNode, RBNodeBase_d54b00* pNodeParent, RBNodeBase_d54b00* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_d54b00 {
    uint32_t first;
    char mRest[0x2c];
    Value_d54b00(const Value_d54b00& o);   // 0x00d54780
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_d54b00 : RBNodeBase_d54b00 {
    Value_d54b00 mValue;                         // +0x10
};
struct Iterator_d54b00 {
    Node_d54b00* mpNode;
    explicit Iterator_d54b00(Node_d54b00* p) : mpNode(p) {}
};
struct Tree_d54b00 {
    int mCompare;                             // +0x00
    RBNodeBase_d54b00 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_d54b00 DoInsertValueImpl(Node_d54b00* pNodeParent, const Value_d54b00& value, bool bForceToLeft);
};

// @ 0x00d54b00
Iterator_d54b00 Tree_d54b00::DoInsertValueImpl(Node_d54b00* pNodeParent, const Value_d54b00& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_d54b00*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_d54b00* pNodeNew = (Node_d54b00*)EaAlloc_d54b00(sizeof(Node_d54b00), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_d54b00(value);
    RBTreeInsert_d54b00(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_d54b00(pNodeNew);
}
