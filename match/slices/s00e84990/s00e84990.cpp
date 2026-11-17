// rb-tree insertion (0x00e84990): pick the side, create the 0x28-byte node inline (the value is copy-constructed (0xe84850)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_e84990(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_e84990 { RBNodeBase_e84990* mpNodeRight; RBNodeBase_e84990* mpNodeLeft; RBNodeBase_e84990* mpNodeParent; int mColor; };
void RBTreeInsert_e84990(RBNodeBase_e84990* pNode, RBNodeBase_e84990* pNodeParent, RBNodeBase_e84990* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_e84990 {
    uint32_t first;
    char mRest[0x14];
    Value_e84990(const Value_e84990& o);   // 0x00e84850
    static void* operator new(size_t, void* p) throw() { return p; }
};
bool KeyLess_e84990(const Value_e84990& a, const Value_e84990& b);   // 0x00812210
struct Node_e84990 : RBNodeBase_e84990 {
    Value_e84990 mValue;                         // +0x10
};
struct Iterator_e84990 {
    Node_e84990* mpNode;
    explicit Iterator_e84990(Node_e84990* p) : mpNode(p) {}
};
struct Tree_e84990 {
    int mCompare;                             // +0x00
    RBNodeBase_e84990 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_e84990 DoInsertValueImpl(Node_e84990* pNodeParent, const Value_e84990& value, bool bForceToLeft);
};

// @ 0x00e84990
Iterator_e84990 Tree_e84990::DoInsertValueImpl(Node_e84990* pNodeParent, const Value_e84990& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_e84990*)&mAnchor || KeyLess_e84990(value, pNodeParent->mValue))
        side = 0;
    else
        side = 1;
    Node_e84990* pNodeNew = (Node_e84990*)EaAlloc_e84990(sizeof(Node_e84990), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_e84990(value);
    RBTreeInsert_e84990(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_e84990(pNodeNew);
}
