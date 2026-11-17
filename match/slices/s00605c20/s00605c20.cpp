// rbtree::DoInsertValue for unique keys (0x00605c20): walk down to the insertion point; insert (DoInsertValueImpl
// 0x605ba0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_605c20 { RBNodeBase_605c20* mpNodeRight; RBNodeBase_605c20* mpNodeLeft; RBNodeBase_605c20* mpNodeParent; int mColor; };
RBNodeBase_605c20* RBTreeDecrement_605c20(const RBNodeBase_605c20* pNode);   // 0x009215c0

struct Value_605c20 { uint32_t first; };
struct Node_605c20 : RBNodeBase_605c20 {
    Value_605c20 mValue;                         // +0x10
};
struct Iterator_605c20 {
    Node_605c20* mpNode;
    explicit Iterator_605c20(Node_605c20* p) : mpNode(p) {}
};
struct InsertResult_605c20 {
    Iterator_605c20 first;
    bool second;
    InsertResult_605c20(const Iterator_605c20& it, bool b) : first(it), second(b) {}
};
struct TrueType_605c20 {};
struct Tree_605c20 {
    int mCompare;                             // +0x00
    RBNodeBase_605c20 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_605c20 DoInsertValueImpl(Node_605c20* pNodeParent, const Value_605c20& value, bool bForceToLeft);   // 0x00605ba0
    InsertResult_605c20 DoInsertValue(const Value_605c20& value, TrueType_605c20);
};

// @ 0x00605c20
InsertResult_605c20 Tree_605c20::DoInsertValue(const Value_605c20& value, TrueType_605c20)
{
    Node_605c20* pCurrent = (Node_605c20*)mAnchor.mpNodeParent;
    Node_605c20* pLowerBound = (Node_605c20*)&mAnchor;
    Node_605c20* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_605c20*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_605c20*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_605c20*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_605c20*)RBTreeDecrement_605c20(pLowerBound);
        else {
            const Iterator_605c20 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_605c20(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_605c20 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_605c20(itResult, true);
    }

    return InsertResult_605c20(Iterator_605c20(pLowerBound), false);
}
