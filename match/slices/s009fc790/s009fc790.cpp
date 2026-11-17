// rbtree::DoInsertValue for unique keys (0x009fc790): walk down to the insertion point; insert (DoInsertValueImpl
// 0x9fc4a0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_9fc790 { RBNodeBase_9fc790* mpNodeRight; RBNodeBase_9fc790* mpNodeLeft; RBNodeBase_9fc790* mpNodeParent; int mColor; };
RBNodeBase_9fc790* RBTreeDecrement_9fc790(const RBNodeBase_9fc790* pNode);   // 0x009215c0

struct Value_9fc790 { uint32_t first; };
struct Node_9fc790 : RBNodeBase_9fc790 {
    Value_9fc790 mValue;                         // +0x10
};
struct Iterator_9fc790 {
    Node_9fc790* mpNode;
    explicit Iterator_9fc790(Node_9fc790* p) : mpNode(p) {}
};
struct InsertResult_9fc790 {
    Iterator_9fc790 first;
    bool second;
    InsertResult_9fc790(const Iterator_9fc790& it, bool b) : first(it), second(b) {}
};
struct TrueType_9fc790 {};
struct Tree_9fc790 {
    int mCompare;                             // +0x00
    RBNodeBase_9fc790 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_9fc790 DoInsertValueImpl(Node_9fc790* pNodeParent, const Value_9fc790& value, bool bForceToLeft);   // 0x009fc4a0
    InsertResult_9fc790 DoInsertValue(const Value_9fc790& value, TrueType_9fc790);
};

// @ 0x009fc790
InsertResult_9fc790 Tree_9fc790::DoInsertValue(const Value_9fc790& value, TrueType_9fc790)
{
    Node_9fc790* pCurrent = (Node_9fc790*)mAnchor.mpNodeParent;
    Node_9fc790* pLowerBound = (Node_9fc790*)&mAnchor;
    Node_9fc790* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_9fc790*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_9fc790*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_9fc790*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_9fc790*)RBTreeDecrement_9fc790(pLowerBound);
        else {
            const Iterator_9fc790 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_9fc790(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_9fc790 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_9fc790(itResult, true);
    }

    return InsertResult_9fc790(Iterator_9fc790(pLowerBound), false);
}
