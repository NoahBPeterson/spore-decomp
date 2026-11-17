// rbtree::DoInsertValue for unique keys (0x00ebbe70): walk down to the insertion point; insert (DoInsertValueImpl
// 0xebbd70) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_ebbe70 { RBNodeBase_ebbe70* mpNodeRight; RBNodeBase_ebbe70* mpNodeLeft; RBNodeBase_ebbe70* mpNodeParent; int mColor; };
RBNodeBase_ebbe70* RBTreeDecrement_ebbe70(const RBNodeBase_ebbe70* pNode);   // 0x009215c0

struct Value_ebbe70 { uint32_t first; };
struct Node_ebbe70 : RBNodeBase_ebbe70 {
    Value_ebbe70 mValue;                         // +0x10
};
struct Iterator_ebbe70 {
    Node_ebbe70* mpNode;
    explicit Iterator_ebbe70(Node_ebbe70* p) : mpNode(p) {}
};
struct InsertResult_ebbe70 {
    Iterator_ebbe70 first;
    bool second;
    InsertResult_ebbe70(const Iterator_ebbe70& it, bool b) : first(it), second(b) {}
};
struct TrueType_ebbe70 {};
struct Tree_ebbe70 {
    int mCompare;                             // +0x00
    RBNodeBase_ebbe70 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_ebbe70 DoInsertValueImpl(Node_ebbe70* pNodeParent, const Value_ebbe70& value, bool bForceToLeft);   // 0x00ebbd70
    InsertResult_ebbe70 DoInsertValue(const Value_ebbe70& value, TrueType_ebbe70);
};

// @ 0x00ebbe70
InsertResult_ebbe70 Tree_ebbe70::DoInsertValue(const Value_ebbe70& value, TrueType_ebbe70)
{
    Node_ebbe70* pCurrent = (Node_ebbe70*)mAnchor.mpNodeParent;
    Node_ebbe70* pLowerBound = (Node_ebbe70*)&mAnchor;
    Node_ebbe70* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_ebbe70*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_ebbe70*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_ebbe70*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_ebbe70*)RBTreeDecrement_ebbe70(pLowerBound);
        else {
            const Iterator_ebbe70 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_ebbe70(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_ebbe70 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_ebbe70(itResult, true);
    }

    return InsertResult_ebbe70(Iterator_ebbe70(pLowerBound), false);
}
