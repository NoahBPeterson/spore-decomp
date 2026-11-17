// rbtree::DoInsertValue for unique keys (0x009c1700): walk down to the insertion point; insert (DoInsertValueImpl
// 0x9c1560) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_9c1700 { RBNodeBase_9c1700* mpNodeRight; RBNodeBase_9c1700* mpNodeLeft; RBNodeBase_9c1700* mpNodeParent; int mColor; };
RBNodeBase_9c1700* RBTreeDecrement_9c1700(const RBNodeBase_9c1700* pNode);   // 0x009215c0

struct Value_9c1700 { uint32_t first; };
struct Node_9c1700 : RBNodeBase_9c1700 {
    Value_9c1700 mValue;                         // +0x10
};
struct Iterator_9c1700 {
    Node_9c1700* mpNode;
    explicit Iterator_9c1700(Node_9c1700* p) : mpNode(p) {}
};
struct InsertResult_9c1700 {
    Iterator_9c1700 first;
    bool second;
    InsertResult_9c1700(const Iterator_9c1700& it, bool b) : first(it), second(b) {}
};
struct TrueType_9c1700 {};
struct Tree_9c1700 {
    int mCompare;                             // +0x00
    RBNodeBase_9c1700 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_9c1700 DoInsertValueImpl(Node_9c1700* pNodeParent, const Value_9c1700& value, bool bForceToLeft);   // 0x009c1560
    InsertResult_9c1700 DoInsertValue(const Value_9c1700& value, TrueType_9c1700);
};

// @ 0x009c1700
InsertResult_9c1700 Tree_9c1700::DoInsertValue(const Value_9c1700& value, TrueType_9c1700)
{
    Node_9c1700* pCurrent = (Node_9c1700*)mAnchor.mpNodeParent;
    Node_9c1700* pLowerBound = (Node_9c1700*)&mAnchor;
    Node_9c1700* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_9c1700*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_9c1700*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_9c1700*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_9c1700*)RBTreeDecrement_9c1700(pLowerBound);
        else {
            const Iterator_9c1700 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_9c1700(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_9c1700 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_9c1700(itResult, true);
    }

    return InsertResult_9c1700(Iterator_9c1700(pLowerBound), false);
}
