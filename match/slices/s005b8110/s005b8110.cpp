// rbtree::DoInsertValue for unique keys (0x005b8110): walk down to the insertion point; insert (DoInsertValueImpl
// 0x5b8070) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_5b8110 { RBNodeBase_5b8110* mpNodeRight; RBNodeBase_5b8110* mpNodeLeft; RBNodeBase_5b8110* mpNodeParent; int mColor; };
RBNodeBase_5b8110* RBTreeDecrement_5b8110(const RBNodeBase_5b8110* pNode);   // 0x009215c0

struct Value_5b8110 { uint32_t first; };
struct Node_5b8110 : RBNodeBase_5b8110 {
    Value_5b8110 mValue;                         // +0x10
};
struct Iterator_5b8110 {
    Node_5b8110* mpNode;
    explicit Iterator_5b8110(Node_5b8110* p) : mpNode(p) {}
};
struct InsertResult_5b8110 {
    Iterator_5b8110 first;
    bool second;
    InsertResult_5b8110(const Iterator_5b8110& it, bool b) : first(it), second(b) {}
};
struct TrueType_5b8110 {};
struct Tree_5b8110 {
    int mCompare;                             // +0x00
    RBNodeBase_5b8110 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_5b8110 DoInsertValueImpl(Node_5b8110* pNodeParent, const Value_5b8110& value, bool bForceToLeft);   // 0x005b8070
    InsertResult_5b8110 DoInsertValue(const Value_5b8110& value, TrueType_5b8110);
};

// @ 0x005b8110
InsertResult_5b8110 Tree_5b8110::DoInsertValue(const Value_5b8110& value, TrueType_5b8110)
{
    Node_5b8110* pCurrent = (Node_5b8110*)mAnchor.mpNodeParent;
    Node_5b8110* pLowerBound = (Node_5b8110*)&mAnchor;
    Node_5b8110* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_5b8110*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_5b8110*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_5b8110*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_5b8110*)RBTreeDecrement_5b8110(pLowerBound);
        else {
            const Iterator_5b8110 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_5b8110(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_5b8110 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_5b8110(itResult, true);
    }

    return InsertResult_5b8110(Iterator_5b8110(pLowerBound), false);
}
