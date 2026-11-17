// rbtree::DoInsertValue for unique keys (0x00f0f200): walk down to the insertion point; insert (DoInsertValueImpl
// 0xf0f170) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_f0f200 { RBNodeBase_f0f200* mpNodeRight; RBNodeBase_f0f200* mpNodeLeft; RBNodeBase_f0f200* mpNodeParent; int mColor; };
RBNodeBase_f0f200* RBTreeDecrement_f0f200(const RBNodeBase_f0f200* pNode);   // 0x009215c0

struct Value_f0f200 { uint32_t first; };
struct Node_f0f200 : RBNodeBase_f0f200 {
    Value_f0f200 mValue;                         // +0x10
};
struct Iterator_f0f200 {
    Node_f0f200* mpNode;
    explicit Iterator_f0f200(Node_f0f200* p) : mpNode(p) {}
};
struct InsertResult_f0f200 {
    Iterator_f0f200 first;
    bool second;
    InsertResult_f0f200(const Iterator_f0f200& it, bool b) : first(it), second(b) {}
};
struct TrueType_f0f200 {};
struct Tree_f0f200 {
    int mCompare;                             // +0x00
    RBNodeBase_f0f200 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_f0f200 DoInsertValueImpl(Node_f0f200* pNodeParent, const Value_f0f200& value, bool bForceToLeft);   // 0x00f0f170
    InsertResult_f0f200 DoInsertValue(const Value_f0f200& value, TrueType_f0f200);
};

// @ 0x00f0f200
InsertResult_f0f200 Tree_f0f200::DoInsertValue(const Value_f0f200& value, TrueType_f0f200)
{
    Node_f0f200* pCurrent = (Node_f0f200*)mAnchor.mpNodeParent;
    Node_f0f200* pLowerBound = (Node_f0f200*)&mAnchor;
    Node_f0f200* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_f0f200*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_f0f200*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_f0f200*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_f0f200*)RBTreeDecrement_f0f200(pLowerBound);
        else {
            const Iterator_f0f200 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_f0f200(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_f0f200 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_f0f200(itResult, true);
    }

    return InsertResult_f0f200(Iterator_f0f200(pLowerBound), false);
}
