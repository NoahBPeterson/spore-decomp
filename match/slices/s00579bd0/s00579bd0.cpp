// rbtree::DoInsertValue for unique keys (0x00579bd0): walk down to the insertion point; insert (DoInsertValueImpl
// 0x579b50) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_579bd0 { RBNodeBase_579bd0* mpNodeRight; RBNodeBase_579bd0* mpNodeLeft; RBNodeBase_579bd0* mpNodeParent; int mColor; };
RBNodeBase_579bd0* RBTreeDecrement_579bd0(const RBNodeBase_579bd0* pNode);   // 0x009215c0

struct Value_579bd0 { uint32_t first; };
struct Node_579bd0 : RBNodeBase_579bd0 {
    Value_579bd0 mValue;                         // +0x10
};
struct Iterator_579bd0 {
    Node_579bd0* mpNode;
    explicit Iterator_579bd0(Node_579bd0* p) : mpNode(p) {}
};
struct InsertResult_579bd0 {
    Iterator_579bd0 first;
    bool second;
    InsertResult_579bd0(const Iterator_579bd0& it, bool b) : first(it), second(b) {}
};
struct TrueType_579bd0 {};
struct Tree_579bd0 {
    int mCompare;                             // +0x00
    RBNodeBase_579bd0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_579bd0 DoInsertValueImpl(Node_579bd0* pNodeParent, const Value_579bd0& value, bool bForceToLeft);   // 0x00579b50
    InsertResult_579bd0 DoInsertValue(const Value_579bd0& value, TrueType_579bd0);
};

// @ 0x00579bd0
InsertResult_579bd0 Tree_579bd0::DoInsertValue(const Value_579bd0& value, TrueType_579bd0)
{
    Node_579bd0* pCurrent = (Node_579bd0*)mAnchor.mpNodeParent;
    Node_579bd0* pLowerBound = (Node_579bd0*)&mAnchor;
    Node_579bd0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_579bd0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_579bd0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_579bd0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_579bd0*)RBTreeDecrement_579bd0(pLowerBound);
        else {
            const Iterator_579bd0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_579bd0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_579bd0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_579bd0(itResult, true);
    }

    return InsertResult_579bd0(Iterator_579bd0(pLowerBound), false);
}
