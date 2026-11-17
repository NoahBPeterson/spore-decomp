// rbtree::DoInsertValue for unique keys (0x005d9ad0): walk down to the insertion point; insert (DoInsertValueImpl
// 0x5d98d0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_5d9ad0 { RBNodeBase_5d9ad0* mpNodeRight; RBNodeBase_5d9ad0* mpNodeLeft; RBNodeBase_5d9ad0* mpNodeParent; int mColor; };
RBNodeBase_5d9ad0* RBTreeDecrement_5d9ad0(const RBNodeBase_5d9ad0* pNode);   // 0x009215c0

struct Value_5d9ad0 { uint32_t first; };
struct Node_5d9ad0 : RBNodeBase_5d9ad0 {
    Value_5d9ad0 mValue;                         // +0x10
};
struct Iterator_5d9ad0 {
    Node_5d9ad0* mpNode;
    explicit Iterator_5d9ad0(Node_5d9ad0* p) : mpNode(p) {}
};
struct InsertResult_5d9ad0 {
    Iterator_5d9ad0 first;
    bool second;
    InsertResult_5d9ad0(const Iterator_5d9ad0& it, bool b) : first(it), second(b) {}
};
struct TrueType_5d9ad0 {};
struct Tree_5d9ad0 {
    int mCompare;                             // +0x00
    RBNodeBase_5d9ad0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_5d9ad0 DoInsertValueImpl(Node_5d9ad0* pNodeParent, const Value_5d9ad0& value, bool bForceToLeft);   // 0x005d98d0
    InsertResult_5d9ad0 DoInsertValue(const Value_5d9ad0& value, TrueType_5d9ad0);
};

// @ 0x005d9ad0
InsertResult_5d9ad0 Tree_5d9ad0::DoInsertValue(const Value_5d9ad0& value, TrueType_5d9ad0)
{
    Node_5d9ad0* pCurrent = (Node_5d9ad0*)mAnchor.mpNodeParent;
    Node_5d9ad0* pLowerBound = (Node_5d9ad0*)&mAnchor;
    Node_5d9ad0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_5d9ad0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_5d9ad0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_5d9ad0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_5d9ad0*)RBTreeDecrement_5d9ad0(pLowerBound);
        else {
            const Iterator_5d9ad0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_5d9ad0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_5d9ad0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_5d9ad0(itResult, true);
    }

    return InsertResult_5d9ad0(Iterator_5d9ad0(pLowerBound), false);
}
