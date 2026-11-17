// rbtree::DoInsertValue for unique keys (0x00dd6740): walk down to the insertion point; insert (DoInsertValueImpl
// 0xd4b4f0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_dd6740 { RBNodeBase_dd6740* mpNodeRight; RBNodeBase_dd6740* mpNodeLeft; RBNodeBase_dd6740* mpNodeParent; int mColor; };
RBNodeBase_dd6740* RBTreeDecrement_dd6740(const RBNodeBase_dd6740* pNode);   // 0x009215c0

struct Value_dd6740 { uint32_t first; };
struct Node_dd6740 : RBNodeBase_dd6740 {
    Value_dd6740 mValue;                         // +0x10
};
struct Iterator_dd6740 {
    Node_dd6740* mpNode;
    explicit Iterator_dd6740(Node_dd6740* p) : mpNode(p) {}
};
struct InsertResult_dd6740 {
    Iterator_dd6740 first;
    bool second;
    InsertResult_dd6740(const Iterator_dd6740& it, bool b) : first(it), second(b) {}
};
struct TrueType_dd6740 {};
struct Tree_dd6740 {
    int mCompare;                             // +0x00
    RBNodeBase_dd6740 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_dd6740 DoInsertValueImpl(Node_dd6740* pNodeParent, const Value_dd6740& value, bool bForceToLeft);   // 0x00d4b4f0
    InsertResult_dd6740 DoInsertValue(const Value_dd6740& value, TrueType_dd6740);
};

// @ 0x00dd6740
InsertResult_dd6740 Tree_dd6740::DoInsertValue(const Value_dd6740& value, TrueType_dd6740)
{
    Node_dd6740* pCurrent = (Node_dd6740*)mAnchor.mpNodeParent;
    Node_dd6740* pLowerBound = (Node_dd6740*)&mAnchor;
    Node_dd6740* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_dd6740*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_dd6740*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_dd6740*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_dd6740*)RBTreeDecrement_dd6740(pLowerBound);
        else {
            const Iterator_dd6740 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_dd6740(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_dd6740 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_dd6740(itResult, true);
    }

    return InsertResult_dd6740(Iterator_dd6740(pLowerBound), false);
}
