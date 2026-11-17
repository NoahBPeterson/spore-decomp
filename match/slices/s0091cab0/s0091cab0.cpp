// rbtree::DoInsertValue for unique keys (0x0091cab0): walk down to the insertion point; insert (DoInsertValueImpl
// 0x91c5b0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_91cab0 { RBNodeBase_91cab0* mpNodeRight; RBNodeBase_91cab0* mpNodeLeft; RBNodeBase_91cab0* mpNodeParent; int mColor; };
RBNodeBase_91cab0* RBTreeDecrement_91cab0(const RBNodeBase_91cab0* pNode);   // 0x009215c0

struct Value_91cab0 { uint32_t first; };
struct Node_91cab0 : RBNodeBase_91cab0 {
    Value_91cab0 mValue;                         // +0x10
};
struct Iterator_91cab0 {
    Node_91cab0* mpNode;
    explicit Iterator_91cab0(Node_91cab0* p) : mpNode(p) {}
};
struct InsertResult_91cab0 {
    Iterator_91cab0 first;
    bool second;
    InsertResult_91cab0(const Iterator_91cab0& it, bool b) : first(it), second(b) {}
};
struct TrueType_91cab0 {};
struct Tree_91cab0 {
    int mCompare;                             // +0x00
    RBNodeBase_91cab0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_91cab0 DoInsertValueImpl(Node_91cab0* pNodeParent, const Value_91cab0& value, bool bForceToLeft);   // 0x0091c5b0
    InsertResult_91cab0 DoInsertValue(const Value_91cab0& value, TrueType_91cab0);
};

// @ 0x0091cab0
InsertResult_91cab0 Tree_91cab0::DoInsertValue(const Value_91cab0& value, TrueType_91cab0)
{
    Node_91cab0* pCurrent = (Node_91cab0*)mAnchor.mpNodeParent;
    Node_91cab0* pLowerBound = (Node_91cab0*)&mAnchor;
    Node_91cab0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_91cab0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_91cab0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_91cab0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_91cab0*)RBTreeDecrement_91cab0(pLowerBound);
        else {
            const Iterator_91cab0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_91cab0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_91cab0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_91cab0(itResult, true);
    }

    return InsertResult_91cab0(Iterator_91cab0(pLowerBound), false);
}
