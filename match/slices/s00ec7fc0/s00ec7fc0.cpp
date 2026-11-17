// rbtree::DoInsertValue for unique keys (0x00ec7fc0): walk down to the insertion point; insert (DoInsertValueImpl
// 0xec7f40) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_ec7fc0 { RBNodeBase_ec7fc0* mpNodeRight; RBNodeBase_ec7fc0* mpNodeLeft; RBNodeBase_ec7fc0* mpNodeParent; int mColor; };
RBNodeBase_ec7fc0* RBTreeDecrement_ec7fc0(const RBNodeBase_ec7fc0* pNode);   // 0x009215c0

struct Value_ec7fc0 { int32_t first; };
struct Node_ec7fc0 : RBNodeBase_ec7fc0 {
    Value_ec7fc0 mValue;                         // +0x10
};
struct Iterator_ec7fc0 {
    Node_ec7fc0* mpNode;
    explicit Iterator_ec7fc0(Node_ec7fc0* p) : mpNode(p) {}
};
struct InsertResult_ec7fc0 {
    Iterator_ec7fc0 first;
    bool second;
    InsertResult_ec7fc0(const Iterator_ec7fc0& it, bool b) : first(it), second(b) {}
};
struct TrueType_ec7fc0 {};
struct Tree_ec7fc0 {
    int mCompare;                             // +0x00
    RBNodeBase_ec7fc0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_ec7fc0 DoInsertValueImpl(Node_ec7fc0* pNodeParent, const Value_ec7fc0& value, bool bForceToLeft);   // 0x00ec7f40
    InsertResult_ec7fc0 DoInsertValue(const Value_ec7fc0& value, TrueType_ec7fc0);
};

// @ 0x00ec7fc0
InsertResult_ec7fc0 Tree_ec7fc0::DoInsertValue(const Value_ec7fc0& value, TrueType_ec7fc0)
{
    Node_ec7fc0* pCurrent = (Node_ec7fc0*)mAnchor.mpNodeParent;
    Node_ec7fc0* pLowerBound = (Node_ec7fc0*)&mAnchor;
    Node_ec7fc0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_ec7fc0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_ec7fc0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_ec7fc0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_ec7fc0*)RBTreeDecrement_ec7fc0(pLowerBound);
        else {
            const Iterator_ec7fc0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_ec7fc0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_ec7fc0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_ec7fc0(itResult, true);
    }

    return InsertResult_ec7fc0(Iterator_ec7fc0(pLowerBound), false);
}
