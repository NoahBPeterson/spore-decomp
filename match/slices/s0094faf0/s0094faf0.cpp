// rbtree::DoInsertValue for unique keys (0x0094faf0): walk down to the insertion point; insert (DoInsertValueImpl
// 0x94fa60) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_94faf0 { RBNodeBase_94faf0* mpNodeRight; RBNodeBase_94faf0* mpNodeLeft; RBNodeBase_94faf0* mpNodeParent; int mColor; };
RBNodeBase_94faf0* RBTreeDecrement_94faf0(const RBNodeBase_94faf0* pNode);   // 0x009215c0

struct Value_94faf0 { uint32_t first; };
struct Node_94faf0 : RBNodeBase_94faf0 {
    Value_94faf0 mValue;                         // +0x10
};
struct Iterator_94faf0 {
    Node_94faf0* mpNode;
    explicit Iterator_94faf0(Node_94faf0* p) : mpNode(p) {}
};
struct InsertResult_94faf0 {
    Iterator_94faf0 first;
    bool second;
    InsertResult_94faf0(const Iterator_94faf0& it, bool b) : first(it), second(b) {}
};
struct TrueType_94faf0 {};
struct Tree_94faf0 {
    int mCompare;                             // +0x00
    RBNodeBase_94faf0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_94faf0 DoInsertValueImpl(Node_94faf0* pNodeParent, const Value_94faf0& value, bool bForceToLeft);   // 0x0094fa60
    InsertResult_94faf0 DoInsertValue(const Value_94faf0& value, TrueType_94faf0);
};

// @ 0x0094faf0
InsertResult_94faf0 Tree_94faf0::DoInsertValue(const Value_94faf0& value, TrueType_94faf0)
{
    Node_94faf0* pCurrent = (Node_94faf0*)mAnchor.mpNodeParent;
    Node_94faf0* pLowerBound = (Node_94faf0*)&mAnchor;
    Node_94faf0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_94faf0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_94faf0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_94faf0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_94faf0*)RBTreeDecrement_94faf0(pLowerBound);
        else {
            const Iterator_94faf0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_94faf0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_94faf0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_94faf0(itResult, true);
    }

    return InsertResult_94faf0(Iterator_94faf0(pLowerBound), false);
}
