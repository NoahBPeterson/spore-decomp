// rb-tree insertion (0x0082c080): pick the side, create the 0x18-byte node inline (the key/value pair is copied), link it in with
// RBTreeInsert (0x9216a0) and count it.
#include "game/types.h"

void* EaAlloc_82c080(unsigned size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
struct RBNodeBase_82c080 { RBNodeBase_82c080* mpNodeRight; RBNodeBase_82c080* mpNodeLeft; RBNodeBase_82c080* mpNodeParent; int mColor; };
void RBTreeInsert_82c080(RBNodeBase_82c080* pNode, RBNodeBase_82c080* pNodeParent, RBNodeBase_82c080* pNodeAnchor, int insertionSide);  // 0x009216a0

struct Value_82c080 {
    uint32_t first;
    uint32_t second;
    static void* operator new(size_t, void* p) throw() { return p; }
};
struct Node_82c080 : RBNodeBase_82c080 {
    Value_82c080 mValue;                         // +0x10
};
struct Iterator_82c080 {
    Node_82c080* mpNode;
    explicit Iterator_82c080(Node_82c080* p) : mpNode(p) {}
};
struct Tree_82c080 {
    int mCompare;                             // +0x00
    RBNodeBase_82c080 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_82c080 DoInsertValueImpl(Node_82c080* pNodeParent, const Value_82c080& value, bool bForceToLeft);
};

// @ 0x0082c080
Iterator_82c080 Tree_82c080::DoInsertValueImpl(Node_82c080* pNodeParent, const Value_82c080& value, bool bForceToLeft)
{
    int side;
    if (bForceToLeft || pNodeParent == (Node_82c080*)&mAnchor || value.first < pNodeParent->mValue.first)
        side = 0;
    else
        side = 1;
    Node_82c080* pNodeNew = (Node_82c080*)EaAlloc_82c080(sizeof(Node_82c080), "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    new (&pNodeNew->mValue) Value_82c080(value);
    RBTreeInsert_82c080(pNodeNew, pNodeParent, &mAnchor, side);
    ++mnSize;
    return Iterator_82c080(pNodeNew);
}
