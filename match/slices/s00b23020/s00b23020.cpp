// rbtree::DoInsertValue for unique keys (0x00b23020): walk down to the insertion point; insert (DoInsertValueImpl
// 0xb21fe0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_b23020 { RBNodeBase_b23020* mpNodeRight; RBNodeBase_b23020* mpNodeLeft; RBNodeBase_b23020* mpNodeParent; int mColor; };
RBNodeBase_b23020* RBTreeDecrement_b23020(const RBNodeBase_b23020* pNode);   // 0x009215c0

struct Value_b23020 { int32_t first; };
struct Node_b23020 : RBNodeBase_b23020 {
    Value_b23020 mValue;                         // +0x10
};
struct Iterator_b23020 {
    Node_b23020* mpNode;
    explicit Iterator_b23020(Node_b23020* p) : mpNode(p) {}
};
struct InsertResult_b23020 {
    Iterator_b23020 first;
    bool second;
    InsertResult_b23020(const Iterator_b23020& it, bool b) : first(it), second(b) {}
};
struct TrueType_b23020 {};
struct Tree_b23020 {
    int mCompare;                             // +0x00
    RBNodeBase_b23020 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_b23020 DoInsertValueImpl(Node_b23020* pNodeParent, const Value_b23020& value, bool bForceToLeft);   // 0x00b21fe0
    InsertResult_b23020 DoInsertValue(const Value_b23020& value, TrueType_b23020);
};

// @ 0x00b23020
InsertResult_b23020 Tree_b23020::DoInsertValue(const Value_b23020& value, TrueType_b23020)
{
    Node_b23020* pCurrent = (Node_b23020*)mAnchor.mpNodeParent;
    Node_b23020* pLowerBound = (Node_b23020*)&mAnchor;
    Node_b23020* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_b23020*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_b23020*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_b23020*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_b23020*)RBTreeDecrement_b23020(pLowerBound);
        else {
            const Iterator_b23020 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_b23020(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_b23020 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_b23020(itResult, true);
    }

    return InsertResult_b23020(Iterator_b23020(pLowerBound), false);
}
