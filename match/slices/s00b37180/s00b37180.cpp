// rbtree::DoInsertValue for unique keys (0x00b37180): walk down to the insertion point; insert (DoInsertValueImpl
// 0xb36440) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_b37180 { RBNodeBase_b37180* mpNodeRight; RBNodeBase_b37180* mpNodeLeft; RBNodeBase_b37180* mpNodeParent; int mColor; };
RBNodeBase_b37180* RBTreeDecrement_b37180(const RBNodeBase_b37180* pNode);   // 0x009215c0

struct Value_b37180 { int32_t first; };
struct Node_b37180 : RBNodeBase_b37180 {
    Value_b37180 mValue;                         // +0x10
};
struct Iterator_b37180 {
    Node_b37180* mpNode;
    explicit Iterator_b37180(Node_b37180* p) : mpNode(p) {}
};
struct InsertResult_b37180 {
    Iterator_b37180 first;
    bool second;
    InsertResult_b37180(const Iterator_b37180& it, bool b) : first(it), second(b) {}
};
struct TrueType_b37180 {};
struct Tree_b37180 {
    int mCompare;                             // +0x00
    RBNodeBase_b37180 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_b37180 DoInsertValueImpl(Node_b37180* pNodeParent, const Value_b37180& value, bool bForceToLeft);   // 0x00b36440
    InsertResult_b37180 DoInsertValue(const Value_b37180& value, TrueType_b37180);
};

// @ 0x00b37180
InsertResult_b37180 Tree_b37180::DoInsertValue(const Value_b37180& value, TrueType_b37180)
{
    Node_b37180* pCurrent = (Node_b37180*)mAnchor.mpNodeParent;
    Node_b37180* pLowerBound = (Node_b37180*)&mAnchor;
    Node_b37180* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_b37180*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_b37180*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_b37180*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_b37180*)RBTreeDecrement_b37180(pLowerBound);
        else {
            const Iterator_b37180 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_b37180(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_b37180 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_b37180(itResult, true);
    }

    return InsertResult_b37180(Iterator_b37180(pLowerBound), false);
}
