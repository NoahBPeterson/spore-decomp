// rbtree::DoInsertValue for unique keys (0x007d0850): walk down to the insertion point; insert (DoInsertValueImpl
// 0x7d05b0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_7d0850 { RBNodeBase_7d0850* mpNodeRight; RBNodeBase_7d0850* mpNodeLeft; RBNodeBase_7d0850* mpNodeParent; int mColor; };
RBNodeBase_7d0850* RBTreeDecrement_7d0850(const RBNodeBase_7d0850* pNode);   // 0x009215c0

struct Value_7d0850 { int32_t first; };
struct Node_7d0850 : RBNodeBase_7d0850 {
    Value_7d0850 mValue;                         // +0x10
};
struct Iterator_7d0850 {
    Node_7d0850* mpNode;
    explicit Iterator_7d0850(Node_7d0850* p) : mpNode(p) {}
};
struct InsertResult_7d0850 {
    Iterator_7d0850 first;
    bool second;
    InsertResult_7d0850(const Iterator_7d0850& it, bool b) : first(it), second(b) {}
};
struct TrueType_7d0850 {};
struct Tree_7d0850 {
    int mCompare;                             // +0x00
    RBNodeBase_7d0850 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_7d0850 DoInsertValueImpl(Node_7d0850* pNodeParent, const Value_7d0850& value, bool bForceToLeft);   // 0x007d05b0
    InsertResult_7d0850 DoInsertValue(const Value_7d0850& value, TrueType_7d0850);
};

// @ 0x007d0850
InsertResult_7d0850 Tree_7d0850::DoInsertValue(const Value_7d0850& value, TrueType_7d0850)
{
    Node_7d0850* pCurrent = (Node_7d0850*)mAnchor.mpNodeParent;
    Node_7d0850* pLowerBound = (Node_7d0850*)&mAnchor;
    Node_7d0850* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_7d0850*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_7d0850*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_7d0850*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_7d0850*)RBTreeDecrement_7d0850(pLowerBound);
        else {
            const Iterator_7d0850 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_7d0850(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_7d0850 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_7d0850(itResult, true);
    }

    return InsertResult_7d0850(Iterator_7d0850(pLowerBound), false);
}
