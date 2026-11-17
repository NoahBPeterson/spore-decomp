// rbtree::DoInsertValue for unique keys (0x00bf2710): walk down to the insertion point; insert (DoInsertValueImpl
// 0xbf1d90) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_bf2710 { RBNodeBase_bf2710* mpNodeRight; RBNodeBase_bf2710* mpNodeLeft; RBNodeBase_bf2710* mpNodeParent; int mColor; };
RBNodeBase_bf2710* RBTreeDecrement_bf2710(const RBNodeBase_bf2710* pNode);   // 0x009215c0

struct Value_bf2710 { int32_t first; };
struct Node_bf2710 : RBNodeBase_bf2710 {
    Value_bf2710 mValue;                         // +0x10
};
struct Iterator_bf2710 {
    Node_bf2710* mpNode;
    explicit Iterator_bf2710(Node_bf2710* p) : mpNode(p) {}
};
struct InsertResult_bf2710 {
    Iterator_bf2710 first;
    bool second;
    InsertResult_bf2710(const Iterator_bf2710& it, bool b) : first(it), second(b) {}
};
struct TrueType_bf2710 {};
struct Tree_bf2710 {
    int mCompare;                             // +0x00
    RBNodeBase_bf2710 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_bf2710 DoInsertValueImpl(Node_bf2710* pNodeParent, const Value_bf2710& value, bool bForceToLeft);   // 0x00bf1d90
    InsertResult_bf2710 DoInsertValue(const Value_bf2710& value, TrueType_bf2710);
};

// @ 0x00bf2710
InsertResult_bf2710 Tree_bf2710::DoInsertValue(const Value_bf2710& value, TrueType_bf2710)
{
    Node_bf2710* pCurrent = (Node_bf2710*)mAnchor.mpNodeParent;
    Node_bf2710* pLowerBound = (Node_bf2710*)&mAnchor;
    Node_bf2710* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_bf2710*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_bf2710*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_bf2710*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_bf2710*)RBTreeDecrement_bf2710(pLowerBound);
        else {
            const Iterator_bf2710 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_bf2710(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_bf2710 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_bf2710(itResult, true);
    }

    return InsertResult_bf2710(Iterator_bf2710(pLowerBound), false);
}
