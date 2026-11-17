// rbtree::DoInsertValue for unique keys (0x005d9bf0): walk down to the insertion point; insert (DoInsertValueImpl
// 0x5d99d0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_5d9bf0 { RBNodeBase_5d9bf0* mpNodeRight; RBNodeBase_5d9bf0* mpNodeLeft; RBNodeBase_5d9bf0* mpNodeParent; int mColor; };
RBNodeBase_5d9bf0* RBTreeDecrement_5d9bf0(const RBNodeBase_5d9bf0* pNode);   // 0x009215c0

struct Value_5d9bf0 { uint32_t first; };
struct Node_5d9bf0 : RBNodeBase_5d9bf0 {
    Value_5d9bf0 mValue;                         // +0x10
};
struct Iterator_5d9bf0 {
    Node_5d9bf0* mpNode;
    explicit Iterator_5d9bf0(Node_5d9bf0* p) : mpNode(p) {}
};
struct InsertResult_5d9bf0 {
    Iterator_5d9bf0 first;
    bool second;
    InsertResult_5d9bf0(const Iterator_5d9bf0& it, bool b) : first(it), second(b) {}
};
struct TrueType_5d9bf0 {};
struct Tree_5d9bf0 {
    int mCompare;                             // +0x00
    RBNodeBase_5d9bf0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_5d9bf0 DoInsertValueImpl(Node_5d9bf0* pNodeParent, const Value_5d9bf0& value, bool bForceToLeft);   // 0x005d99d0
    InsertResult_5d9bf0 DoInsertValue(const Value_5d9bf0& value, TrueType_5d9bf0);
};

// @ 0x005d9bf0
InsertResult_5d9bf0 Tree_5d9bf0::DoInsertValue(const Value_5d9bf0& value, TrueType_5d9bf0)
{
    Node_5d9bf0* pCurrent = (Node_5d9bf0*)mAnchor.mpNodeParent;
    Node_5d9bf0* pLowerBound = (Node_5d9bf0*)&mAnchor;
    Node_5d9bf0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_5d9bf0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_5d9bf0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_5d9bf0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_5d9bf0*)RBTreeDecrement_5d9bf0(pLowerBound);
        else {
            const Iterator_5d9bf0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_5d9bf0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_5d9bf0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_5d9bf0(itResult, true);
    }

    return InsertResult_5d9bf0(Iterator_5d9bf0(pLowerBound), false);
}
