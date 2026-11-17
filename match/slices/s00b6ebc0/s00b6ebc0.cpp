// rbtree::DoInsertValue for unique keys (0x00b6ebc0): walk down to the insertion point; insert (DoInsertValueImpl
// 0xb6eb30) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_b6ebc0 { RBNodeBase_b6ebc0* mpNodeRight; RBNodeBase_b6ebc0* mpNodeLeft; RBNodeBase_b6ebc0* mpNodeParent; int mColor; };
RBNodeBase_b6ebc0* RBTreeDecrement_b6ebc0(const RBNodeBase_b6ebc0* pNode);   // 0x009215c0

struct Value_b6ebc0 { uint32_t first; };
struct Node_b6ebc0 : RBNodeBase_b6ebc0 {
    Value_b6ebc0 mValue;                         // +0x10
};
struct Iterator_b6ebc0 {
    Node_b6ebc0* mpNode;
    explicit Iterator_b6ebc0(Node_b6ebc0* p) : mpNode(p) {}
};
struct InsertResult_b6ebc0 {
    Iterator_b6ebc0 first;
    bool second;
    InsertResult_b6ebc0(const Iterator_b6ebc0& it, bool b) : first(it), second(b) {}
};
struct TrueType_b6ebc0 {};
struct Tree_b6ebc0 {
    int mCompare;                             // +0x00
    RBNodeBase_b6ebc0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_b6ebc0 DoInsertValueImpl(Node_b6ebc0* pNodeParent, const Value_b6ebc0& value, bool bForceToLeft);   // 0x00b6eb30
    InsertResult_b6ebc0 DoInsertValue(const Value_b6ebc0& value, TrueType_b6ebc0);
};

// @ 0x00b6ebc0
InsertResult_b6ebc0 Tree_b6ebc0::DoInsertValue(const Value_b6ebc0& value, TrueType_b6ebc0)
{
    Node_b6ebc0* pCurrent = (Node_b6ebc0*)mAnchor.mpNodeParent;
    Node_b6ebc0* pLowerBound = (Node_b6ebc0*)&mAnchor;
    Node_b6ebc0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_b6ebc0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_b6ebc0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_b6ebc0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_b6ebc0*)RBTreeDecrement_b6ebc0(pLowerBound);
        else {
            const Iterator_b6ebc0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_b6ebc0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_b6ebc0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_b6ebc0(itResult, true);
    }

    return InsertResult_b6ebc0(Iterator_b6ebc0(pLowerBound), false);
}
