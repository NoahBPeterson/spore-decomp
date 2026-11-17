// rb-tree insertion (0x00a6e570): pick the side, create the 0x20-byte node inline (the value is copy-constructed (0x57cb10)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_a6e570(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_a6e570 { RBNodeBase_a6e570* mpNodeRight; RBNodeBase_a6e570* mpNodeLeft; RBNodeBase_a6e570* mpNodeParent; int mColor; };
void RBTreeInsert_a6e570(RBNodeBase_a6e570* pNode, RBNodeBase_a6e570* pNodeParent, RBNodeBase_a6e570* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_a6e570 {
    uint32_t first;
    char mRest[0xc];
    Value_a6e570(const Value_a6e570& o);   // 0x0057cb10
    static void* operator new(size_t, void* p) throw() { return p; }
};
bool KeyLess_a6e570(const Value_a6e570& a, const Value_a6e570& b);   // 0x00812210
struct Node_a6e570 : RBNodeBase_a6e570 {
    Value_a6e570 mValue;                         // +0x10
};
struct Iterator_a6e570 {
    Node_a6e570* mpNode;
    explicit Iterator_a6e570(Node_a6e570* p) : mpNode(p) {}
};
struct Tree_a6e570 {
    int mCompare;                             // +0x00
    RBNodeBase_a6e570 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_a6e570 DoInsertValueImpl(Node_a6e570* pNodeParent, const Value_a6e570& value, bool bForceToLeft);
};

// @ 0x00a6e570
Iterator_a6e570 Tree_a6e570::DoInsertValueImpl(Node_a6e570* pNodeParent, const Value_a6e570& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_a6e570*)&mAnchor || KeyLess_a6e570(value, pNodeParent->mValue))
        side = 0;
    else
        side = 1;
    Node_a6e570* pNodeNew = (Node_a6e570*)EaAlloc_a6e570(sizeof(Node_a6e570), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_a6e570(value);
    RBTreeInsert_a6e570(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_a6e570(pNodeNew);
}
