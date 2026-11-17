// rbtree::DoInsertValue for unique keys (0x00d72de0): walk down to the insertion point; insert (DoInsertValueImpl
// 0xd72d50) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_d72de0 { RBNodeBase_d72de0* mpNodeRight; RBNodeBase_d72de0* mpNodeLeft; RBNodeBase_d72de0* mpNodeParent; int mColor; };
RBNodeBase_d72de0* RBTreeDecrement_d72de0(const RBNodeBase_d72de0* pNode);   // 0x009215c0

struct Value_d72de0 { uint32_t first; };
struct Node_d72de0 : RBNodeBase_d72de0 {
    Value_d72de0 mValue;                         // +0x10
};
struct Iterator_d72de0 {
    Node_d72de0* mpNode;
    explicit Iterator_d72de0(Node_d72de0* p) : mpNode(p) {}
};
struct InsertResult_d72de0 {
    Iterator_d72de0 first;
    bool second;
    InsertResult_d72de0(const Iterator_d72de0& it, bool b) : first(it), second(b) {}
};
struct TrueType_d72de0 {};
struct Tree_d72de0 {
    int mCompare;                             // +0x00
    RBNodeBase_d72de0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_d72de0 DoInsertValueImpl(Node_d72de0* pNodeParent, const Value_d72de0& value, bool bForceToLeft);   // 0x00d72d50
    InsertResult_d72de0 DoInsertValue(const Value_d72de0& value, TrueType_d72de0);
};

// @ 0x00d72de0
InsertResult_d72de0 Tree_d72de0::DoInsertValue(const Value_d72de0& value, TrueType_d72de0)
{
    Node_d72de0* pCurrent = (Node_d72de0*)mAnchor.mpNodeParent;
    Node_d72de0* pLowerBound = (Node_d72de0*)&mAnchor;
    Node_d72de0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_d72de0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_d72de0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_d72de0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_d72de0*)RBTreeDecrement_d72de0(pLowerBound);
        else {
            const Iterator_d72de0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_d72de0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_d72de0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_d72de0(itResult, true);
    }

    return InsertResult_d72de0(Iterator_d72de0(pLowerBound), false);
}
