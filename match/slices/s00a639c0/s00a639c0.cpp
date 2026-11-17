// rbtree::DoInsertValue for unique keys (0x00a639c0): walk down to the insertion point; insert (DoInsertValueImpl
// 0xa63770) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_a639c0 { RBNodeBase_a639c0* mpNodeRight; RBNodeBase_a639c0* mpNodeLeft; RBNodeBase_a639c0* mpNodeParent; int mColor; };
RBNodeBase_a639c0* RBTreeDecrement_a639c0(const RBNodeBase_a639c0* pNode);   // 0x009215c0

struct Value_a639c0 { uint32_t first; };
struct Node_a639c0 : RBNodeBase_a639c0 {
    Value_a639c0 mValue;                         // +0x10
};
struct Iterator_a639c0 {
    Node_a639c0* mpNode;
    explicit Iterator_a639c0(Node_a639c0* p) : mpNode(p) {}
};
struct InsertResult_a639c0 {
    Iterator_a639c0 first;
    bool second;
    InsertResult_a639c0(const Iterator_a639c0& it, bool b) : first(it), second(b) {}
};
struct TrueType_a639c0 {};
struct Tree_a639c0 {
    int mCompare;                             // +0x00
    RBNodeBase_a639c0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_a639c0 DoInsertValueImpl(Node_a639c0* pNodeParent, const Value_a639c0& value, bool bForceToLeft);   // 0x00a63770
    InsertResult_a639c0 DoInsertValue(const Value_a639c0& value, TrueType_a639c0);
};

// @ 0x00a639c0
InsertResult_a639c0 Tree_a639c0::DoInsertValue(const Value_a639c0& value, TrueType_a639c0)
{
    Node_a639c0* pCurrent = (Node_a639c0*)mAnchor.mpNodeParent;
    Node_a639c0* pLowerBound = (Node_a639c0*)&mAnchor;
    Node_a639c0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_a639c0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_a639c0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_a639c0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_a639c0*)RBTreeDecrement_a639c0(pLowerBound);
        else {
            const Iterator_a639c0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_a639c0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_a639c0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_a639c0(itResult, true);
    }

    return InsertResult_a639c0(Iterator_a639c0(pLowerBound), false);
}
