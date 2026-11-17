// rbtree::DoInsertValue for unique keys (0x009fe110): walk down to the insertion point; insert (DoInsertValueImpl
// 0x9fe090) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_9fe110 { RBNodeBase_9fe110* mpNodeRight; RBNodeBase_9fe110* mpNodeLeft; RBNodeBase_9fe110* mpNodeParent; int mColor; };
RBNodeBase_9fe110* RBTreeDecrement_9fe110(const RBNodeBase_9fe110* pNode);   // 0x009215c0

struct Value_9fe110 { uint32_t first; };
struct Node_9fe110 : RBNodeBase_9fe110 {
    Value_9fe110 mValue;                         // +0x10
};
struct Iterator_9fe110 {
    Node_9fe110* mpNode;
    explicit Iterator_9fe110(Node_9fe110* p) : mpNode(p) {}
};
struct InsertResult_9fe110 {
    Iterator_9fe110 first;
    bool second;
    InsertResult_9fe110(const Iterator_9fe110& it, bool b) : first(it), second(b) {}
};
struct TrueType_9fe110 {};
struct Tree_9fe110 {
    int mCompare;                             // +0x00
    RBNodeBase_9fe110 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_9fe110 DoInsertValueImpl(Node_9fe110* pNodeParent, const Value_9fe110& value, bool bForceToLeft);   // 0x009fe090
    InsertResult_9fe110 DoInsertValue(const Value_9fe110& value, TrueType_9fe110);
};

// @ 0x009fe110
InsertResult_9fe110 Tree_9fe110::DoInsertValue(const Value_9fe110& value, TrueType_9fe110)
{
    Node_9fe110* pCurrent = (Node_9fe110*)mAnchor.mpNodeParent;
    Node_9fe110* pLowerBound = (Node_9fe110*)&mAnchor;
    Node_9fe110* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_9fe110*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_9fe110*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_9fe110*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_9fe110*)RBTreeDecrement_9fe110(pLowerBound);
        else {
            const Iterator_9fe110 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_9fe110(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_9fe110 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_9fe110(itResult, true);
    }

    return InsertResult_9fe110(Iterator_9fe110(pLowerBound), false);
}
