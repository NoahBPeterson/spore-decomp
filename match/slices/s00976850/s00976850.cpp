// rbtree::DoInsertValue for unique keys (0x00976850): walk down to the insertion point; insert (DoInsertValueImpl
// 0x976550) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_976850 { RBNodeBase_976850* mpNodeRight; RBNodeBase_976850* mpNodeLeft; RBNodeBase_976850* mpNodeParent; int mColor; };
RBNodeBase_976850* RBTreeDecrement_976850(const RBNodeBase_976850* pNode);   // 0x009215c0

struct Value_976850 { int32_t first; };
struct Node_976850 : RBNodeBase_976850 {
    Value_976850 mValue;                         // +0x10
};
struct Iterator_976850 {
    Node_976850* mpNode;
    explicit Iterator_976850(Node_976850* p) : mpNode(p) {}
};
struct InsertResult_976850 {
    Iterator_976850 first;
    bool second;
    InsertResult_976850(const Iterator_976850& it, bool b) : first(it), second(b) {}
};
struct TrueType_976850 {};
struct Tree_976850 {
    int mCompare;                             // +0x00
    RBNodeBase_976850 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_976850 DoInsertValueImpl(Node_976850* pNodeParent, const Value_976850& value, bool bForceToLeft);   // 0x00976550
    InsertResult_976850 DoInsertValue(const Value_976850& value, TrueType_976850);
};

// @ 0x00976850
InsertResult_976850 Tree_976850::DoInsertValue(const Value_976850& value, TrueType_976850)
{
    Node_976850* pCurrent = (Node_976850*)mAnchor.mpNodeParent;
    Node_976850* pLowerBound = (Node_976850*)&mAnchor;
    Node_976850* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_976850*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_976850*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_976850*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_976850*)RBTreeDecrement_976850(pLowerBound);
        else {
            const Iterator_976850 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_976850(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_976850 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_976850(itResult, true);
    }

    return InsertResult_976850(Iterator_976850(pLowerBound), false);
}
