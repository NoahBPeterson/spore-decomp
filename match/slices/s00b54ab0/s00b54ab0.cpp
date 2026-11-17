// rbtree::DoInsertValue for unique keys (0x00b54ab0): walk down to the insertion point; insert (DoInsertValueImpl
// 0xb53700) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_b54ab0 { RBNodeBase_b54ab0* mpNodeRight; RBNodeBase_b54ab0* mpNodeLeft; RBNodeBase_b54ab0* mpNodeParent; int mColor; };
RBNodeBase_b54ab0* RBTreeDecrement_b54ab0(const RBNodeBase_b54ab0* pNode);   // 0x009215c0

struct Value_b54ab0 { int32_t first; };
struct Node_b54ab0 : RBNodeBase_b54ab0 {
    Value_b54ab0 mValue;                         // +0x10
};
struct Iterator_b54ab0 {
    Node_b54ab0* mpNode;
    explicit Iterator_b54ab0(Node_b54ab0* p) : mpNode(p) {}
};
struct InsertResult_b54ab0 {
    Iterator_b54ab0 first;
    bool second;
    InsertResult_b54ab0(const Iterator_b54ab0& it, bool b) : first(it), second(b) {}
};
struct TrueType_b54ab0 {};
struct Tree_b54ab0 {
    int mCompare;                             // +0x00
    RBNodeBase_b54ab0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_b54ab0 DoInsertValueImpl(Node_b54ab0* pNodeParent, const Value_b54ab0& value, bool bForceToLeft);   // 0x00b53700
    InsertResult_b54ab0 DoInsertValue(const Value_b54ab0& value, TrueType_b54ab0);
};

// @ 0x00b54ab0
InsertResult_b54ab0 Tree_b54ab0::DoInsertValue(const Value_b54ab0& value, TrueType_b54ab0)
{
    Node_b54ab0* pCurrent = (Node_b54ab0*)mAnchor.mpNodeParent;
    Node_b54ab0* pLowerBound = (Node_b54ab0*)&mAnchor;
    Node_b54ab0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_b54ab0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_b54ab0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_b54ab0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_b54ab0*)RBTreeDecrement_b54ab0(pLowerBound);
        else {
            const Iterator_b54ab0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_b54ab0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_b54ab0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_b54ab0(itResult, true);
    }

    return InsertResult_b54ab0(Iterator_b54ab0(pLowerBound), false);
}
