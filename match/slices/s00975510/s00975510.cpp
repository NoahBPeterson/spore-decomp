// rbtree::DoInsertValue for unique keys (0x00975510): walk down to the insertion point; insert (DoInsertValueImpl
// 0x973ef0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_975510 { RBNodeBase_975510* mpNodeRight; RBNodeBase_975510* mpNodeLeft; RBNodeBase_975510* mpNodeParent; int mColor; };
RBNodeBase_975510* RBTreeDecrement_975510(const RBNodeBase_975510* pNode);   // 0x009215c0

struct Value_975510 { int32_t first; };
struct Node_975510 : RBNodeBase_975510 {
    Value_975510 mValue;                         // +0x10
};
struct Iterator_975510 {
    Node_975510* mpNode;
    explicit Iterator_975510(Node_975510* p) : mpNode(p) {}
};
struct InsertResult_975510 {
    Iterator_975510 first;
    bool second;
    InsertResult_975510(const Iterator_975510& it, bool b) : first(it), second(b) {}
};
struct TrueType_975510 {};
struct Tree_975510 {
    int mCompare;                             // +0x00
    RBNodeBase_975510 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_975510 DoInsertValueImpl(Node_975510* pNodeParent, const Value_975510& value, bool bForceToLeft);   // 0x00973ef0
    InsertResult_975510 DoInsertValue(const Value_975510& value, TrueType_975510);
};

// @ 0x00975510
InsertResult_975510 Tree_975510::DoInsertValue(const Value_975510& value, TrueType_975510)
{
    Node_975510* pCurrent = (Node_975510*)mAnchor.mpNodeParent;
    Node_975510* pLowerBound = (Node_975510*)&mAnchor;
    Node_975510* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_975510*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_975510*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_975510*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_975510*)RBTreeDecrement_975510(pLowerBound);
        else {
            const Iterator_975510 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_975510(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_975510 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_975510(itResult, true);
    }

    return InsertResult_975510(Iterator_975510(pLowerBound), false);
}
