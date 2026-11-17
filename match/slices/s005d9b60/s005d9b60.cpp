// rbtree::DoInsertValue for unique keys (0x005d9b60): walk down to the insertion point; insert (DoInsertValueImpl
// 0x5d9950) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_5d9b60 { RBNodeBase_5d9b60* mpNodeRight; RBNodeBase_5d9b60* mpNodeLeft; RBNodeBase_5d9b60* mpNodeParent; int mColor; };
RBNodeBase_5d9b60* RBTreeDecrement_5d9b60(const RBNodeBase_5d9b60* pNode);   // 0x009215c0

struct Value_5d9b60 { uint32_t first; };
struct Node_5d9b60 : RBNodeBase_5d9b60 {
    Value_5d9b60 mValue;                         // +0x10
};
struct Iterator_5d9b60 {
    Node_5d9b60* mpNode;
    explicit Iterator_5d9b60(Node_5d9b60* p) : mpNode(p) {}
};
struct InsertResult_5d9b60 {
    Iterator_5d9b60 first;
    bool second;
    InsertResult_5d9b60(const Iterator_5d9b60& it, bool b) : first(it), second(b) {}
};
struct TrueType_5d9b60 {};
struct Tree_5d9b60 {
    int mCompare;                             // +0x00
    RBNodeBase_5d9b60 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_5d9b60 DoInsertValueImpl(Node_5d9b60* pNodeParent, const Value_5d9b60& value, bool bForceToLeft);   // 0x005d9950
    InsertResult_5d9b60 DoInsertValue(const Value_5d9b60& value, TrueType_5d9b60);
};

// @ 0x005d9b60
InsertResult_5d9b60 Tree_5d9b60::DoInsertValue(const Value_5d9b60& value, TrueType_5d9b60)
{
    Node_5d9b60* pCurrent = (Node_5d9b60*)mAnchor.mpNodeParent;
    Node_5d9b60* pLowerBound = (Node_5d9b60*)&mAnchor;
    Node_5d9b60* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_5d9b60*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_5d9b60*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_5d9b60*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_5d9b60*)RBTreeDecrement_5d9b60(pLowerBound);
        else {
            const Iterator_5d9b60 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_5d9b60(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_5d9b60 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_5d9b60(itResult, true);
    }

    return InsertResult_5d9b60(Iterator_5d9b60(pLowerBound), false);
}
