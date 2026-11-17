// rb-tree insertion (0x009fe090): pick the side, create the 0x28-byte node inline (the value is copy-constructed (0x9fd7f0)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_9fe090(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_9fe090 { RBNodeBase_9fe090* mpNodeRight; RBNodeBase_9fe090* mpNodeLeft; RBNodeBase_9fe090* mpNodeParent; int mColor; };
void RBTreeInsert_9fe090(RBNodeBase_9fe090* pNode, RBNodeBase_9fe090* pNodeParent, RBNodeBase_9fe090* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_9fe090 {
    uint32_t first;
    char mRest[0x14];
    Value_9fe090(const Value_9fe090& o);   // 0x009fd7f0
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_9fe090 : RBNodeBase_9fe090 {
    Value_9fe090 mValue;                         // +0x10
};
struct Iterator_9fe090 {
    Node_9fe090* mpNode;
    explicit Iterator_9fe090(Node_9fe090* p) : mpNode(p) {}
};
struct Tree_9fe090 {
    int mCompare;                             // +0x00
    RBNodeBase_9fe090 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_9fe090 DoInsertValueImpl(Node_9fe090* pNodeParent, const Value_9fe090& value, bool bForceToLeft);
};

// @ 0x009fe090
Iterator_9fe090 Tree_9fe090::DoInsertValueImpl(Node_9fe090* pNodeParent, const Value_9fe090& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_9fe090*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_9fe090* pNodeNew = (Node_9fe090*)EaAlloc_9fe090(sizeof(Node_9fe090), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_9fe090(value);
    RBTreeInsert_9fe090(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_9fe090(pNodeNew);
}
