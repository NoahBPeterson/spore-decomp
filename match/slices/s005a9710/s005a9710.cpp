// rbtree::DoInsertValue for unique keys (0x005a9710): walk down to the insertion point; insert (DoInsertValueImpl
// 0x5a9690) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_5a9710 { RBNodeBase_5a9710* mpNodeRight; RBNodeBase_5a9710* mpNodeLeft; RBNodeBase_5a9710* mpNodeParent; int mColor; };
RBNodeBase_5a9710* RBTreeDecrement_5a9710(const RBNodeBase_5a9710* pNode);   // 0x009215c0

struct Value_5a9710 { uint32_t first; };
struct Node_5a9710 : RBNodeBase_5a9710 {
    Value_5a9710 mValue;                         // +0x10
};
struct Iterator_5a9710 {
    Node_5a9710* mpNode;
    explicit Iterator_5a9710(Node_5a9710* p) : mpNode(p) {}
};
struct InsertResult_5a9710 {
    Iterator_5a9710 first;
    bool second;
    InsertResult_5a9710(const Iterator_5a9710& it, bool b) : first(it), second(b) {}
};
struct TrueType_5a9710 {};
struct Tree_5a9710 {
    int mCompare;                             // +0x00
    RBNodeBase_5a9710 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_5a9710 DoInsertValueImpl(Node_5a9710* pNodeParent, const Value_5a9710& value, bool bForceToLeft);   // 0x005a9690
    InsertResult_5a9710 DoInsertValue(const Value_5a9710& value, TrueType_5a9710);
};

// @ 0x005a9710
InsertResult_5a9710 Tree_5a9710::DoInsertValue(const Value_5a9710& value, TrueType_5a9710)
{
    Node_5a9710* pCurrent = (Node_5a9710*)mAnchor.mpNodeParent;
    Node_5a9710* pLowerBound = (Node_5a9710*)&mAnchor;
    Node_5a9710* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_5a9710*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_5a9710*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_5a9710*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_5a9710*)RBTreeDecrement_5a9710(pLowerBound);
        else {
            const Iterator_5a9710 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_5a9710(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_5a9710 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_5a9710(itResult, true);
    }

    return InsertResult_5a9710(Iterator_5a9710(pLowerBound), false);
}
