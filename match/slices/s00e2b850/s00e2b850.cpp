// rbtree::DoInsertValue for unique keys (0x00e2b850): walk down to the insertion point; insert (DoInsertValueImpl
// 0xe2b760) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_e2b850 { RBNodeBase_e2b850* mpNodeRight; RBNodeBase_e2b850* mpNodeLeft; RBNodeBase_e2b850* mpNodeParent; int mColor; };
RBNodeBase_e2b850* RBTreeDecrement_e2b850(const RBNodeBase_e2b850* pNode);   // 0x009215c0

struct Value_e2b850 { uint32_t first; };
struct Node_e2b850 : RBNodeBase_e2b850 {
    Value_e2b850 mValue;                         // +0x10
};
struct Iterator_e2b850 {
    Node_e2b850* mpNode;
    explicit Iterator_e2b850(Node_e2b850* p) : mpNode(p) {}
};
struct InsertResult_e2b850 {
    Iterator_e2b850 first;
    bool second;
    InsertResult_e2b850(const Iterator_e2b850& it, bool b) : first(it), second(b) {}
};
struct TrueType_e2b850 {};
struct Tree_e2b850 {
    int mCompare;                             // +0x00
    RBNodeBase_e2b850 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_e2b850 DoInsertValueImpl(Node_e2b850* pNodeParent, const Value_e2b850& value, bool bForceToLeft);   // 0x00e2b760
    InsertResult_e2b850 DoInsertValue(const Value_e2b850& value, TrueType_e2b850);
};

// @ 0x00e2b850
InsertResult_e2b850 Tree_e2b850::DoInsertValue(const Value_e2b850& value, TrueType_e2b850)
{
    Node_e2b850* pCurrent = (Node_e2b850*)mAnchor.mpNodeParent;
    Node_e2b850* pLowerBound = (Node_e2b850*)&mAnchor;
    Node_e2b850* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_e2b850*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_e2b850*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_e2b850*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_e2b850*)RBTreeDecrement_e2b850(pLowerBound);
        else {
            const Iterator_e2b850 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_e2b850(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_e2b850 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_e2b850(itResult, true);
    }

    return InsertResult_e2b850(Iterator_e2b850(pLowerBound), false);
}
