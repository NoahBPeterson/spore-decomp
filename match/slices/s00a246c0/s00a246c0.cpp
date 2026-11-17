// rbtree::DoInsertValue for unique keys (0x00a246c0): walk down to the insertion point; insert (DoInsertValueImpl
// 0xa24640) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_a246c0 { RBNodeBase_a246c0* mpNodeRight; RBNodeBase_a246c0* mpNodeLeft; RBNodeBase_a246c0* mpNodeParent; int mColor; };
RBNodeBase_a246c0* RBTreeDecrement_a246c0(const RBNodeBase_a246c0* pNode);   // 0x009215c0

struct Value_a246c0 { uint32_t first; };
struct Node_a246c0 : RBNodeBase_a246c0 {
    Value_a246c0 mValue;                         // +0x10
};
struct Iterator_a246c0 {
    Node_a246c0* mpNode;
    explicit Iterator_a246c0(Node_a246c0* p) : mpNode(p) {}
};
struct InsertResult_a246c0 {
    Iterator_a246c0 first;
    bool second;
    InsertResult_a246c0(const Iterator_a246c0& it, bool b) : first(it), second(b) {}
};
struct TrueType_a246c0 {};
struct Tree_a246c0 {
    int mCompare;                             // +0x00
    RBNodeBase_a246c0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_a246c0 DoInsertValueImpl(Node_a246c0* pNodeParent, const Value_a246c0& value, bool bForceToLeft);   // 0x00a24640
    InsertResult_a246c0 DoInsertValue(const Value_a246c0& value, TrueType_a246c0);
};

// @ 0x00a246c0
InsertResult_a246c0 Tree_a246c0::DoInsertValue(const Value_a246c0& value, TrueType_a246c0)
{
    Node_a246c0* pCurrent = (Node_a246c0*)mAnchor.mpNodeParent;
    Node_a246c0* pLowerBound = (Node_a246c0*)&mAnchor;
    Node_a246c0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_a246c0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_a246c0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_a246c0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_a246c0*)RBTreeDecrement_a246c0(pLowerBound);
        else {
            const Iterator_a246c0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_a246c0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_a246c0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_a246c0(itResult, true);
    }

    return InsertResult_a246c0(Iterator_a246c0(pLowerBound), false);
}
