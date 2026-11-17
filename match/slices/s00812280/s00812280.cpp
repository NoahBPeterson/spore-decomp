// rb-tree insertion (0x00812280): pick the side, create the 0x24-byte node inline (the value is copy-constructed (0x9fc440)), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_812280(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_812280 { RBNodeBase_812280* mpNodeRight; RBNodeBase_812280* mpNodeLeft; RBNodeBase_812280* mpNodeParent; int mColor; };
void RBTreeInsert_812280(RBNodeBase_812280* pNode, RBNodeBase_812280* pNodeParent, RBNodeBase_812280* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_812280 {
    uint32_t first;
    char mRest[0x10];
    Value_812280(const Value_812280& o);   // 0x009fc440
    static void* operator new(size_t, void* p) throw() { return p; }
};
bool KeyLess_812280(const Value_812280& a, const Value_812280& b);   // 0x00812210
struct Node_812280 : RBNodeBase_812280 {
    Value_812280 mValue;                         // +0x10
};
struct Iterator_812280 {
    Node_812280* mpNode;
    explicit Iterator_812280(Node_812280* p) : mpNode(p) {}
};
struct Tree_812280 {
    int mCompare;                             // +0x00
    RBNodeBase_812280 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_812280 DoInsertValueImpl(Node_812280* pNodeParent, const Value_812280& value, bool bForceToLeft);
};

// @ 0x00812280
Iterator_812280 Tree_812280::DoInsertValueImpl(Node_812280* pNodeParent, const Value_812280& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_812280*)&mAnchor || KeyLess_812280(value, pNodeParent->mValue))
        side = 0;
    else
        side = 1;
    Node_812280* pNodeNew = (Node_812280*)EaAlloc_812280(sizeof(Node_812280), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_812280(value);
    RBTreeInsert_812280(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_812280(pNodeNew);
}
