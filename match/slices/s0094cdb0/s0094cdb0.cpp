// rb-tree insertion (0x0094cdb0): pick the side, create the 0x28-byte node inline (the value is copy-constructed (0xe84850)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_94cdb0(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_94cdb0 { RBNodeBase_94cdb0* mpNodeRight; RBNodeBase_94cdb0* mpNodeLeft; RBNodeBase_94cdb0* mpNodeParent; int mColor; };
void RBTreeInsert_94cdb0(RBNodeBase_94cdb0* pNode, RBNodeBase_94cdb0* pNodeParent, RBNodeBase_94cdb0* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_94cdb0 {
    uint32_t first;
    char mRest[0x14];
    Value_94cdb0(const Value_94cdb0& o);   // 0x00e84850
    static void* operator new(size_t, void* p) throw() { return p; }
};
bool KeyLess_94cdb0(const Value_94cdb0& a, const Value_94cdb0& b);   // 0x00812210
struct Node_94cdb0 : RBNodeBase_94cdb0 {
    Value_94cdb0 mValue;                         // +0x10
};
struct Iterator_94cdb0 {
    Node_94cdb0* mpNode;
    explicit Iterator_94cdb0(Node_94cdb0* p) : mpNode(p) {}
};
struct Tree_94cdb0 {
    int mCompare;                             // +0x00
    RBNodeBase_94cdb0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_94cdb0 DoInsertValueImpl(Node_94cdb0* pNodeParent, const Value_94cdb0& value, bool bForceToLeft);
};

// @ 0x0094cdb0
Iterator_94cdb0 Tree_94cdb0::DoInsertValueImpl(Node_94cdb0* pNodeParent, const Value_94cdb0& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_94cdb0*)&mAnchor || KeyLess_94cdb0(value, pNodeParent->mValue))
        side = 0;
    else
        side = 1;
    Node_94cdb0* pNodeNew = (Node_94cdb0*)EaAlloc_94cdb0(sizeof(Node_94cdb0), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_94cdb0(value);
    RBTreeInsert_94cdb0(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_94cdb0(pNodeNew);
}
