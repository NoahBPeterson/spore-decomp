// rbtree::DoInsertValue for unique keys (0x008db6a0): walk down to the insertion point; insert (DoInsertValueImpl
// 0x8db560) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_8db6a0 { RBNodeBase_8db6a0* mpNodeRight; RBNodeBase_8db6a0* mpNodeLeft; RBNodeBase_8db6a0* mpNodeParent; int mColor; };
RBNodeBase_8db6a0* RBTreeDecrement_8db6a0(const RBNodeBase_8db6a0* pNode);   // 0x009215c0

struct Value_8db6a0 { int32_t first; };
struct Node_8db6a0 : RBNodeBase_8db6a0 {
    Value_8db6a0 mValue;                         // +0x10
};
struct Iterator_8db6a0 {
    Node_8db6a0* mpNode;
    explicit Iterator_8db6a0(Node_8db6a0* p) : mpNode(p) {}
};
struct InsertResult_8db6a0 {
    Iterator_8db6a0 first;
    bool second;
    InsertResult_8db6a0(const Iterator_8db6a0& it, bool b) : first(it), second(b) {}
};
struct TrueType_8db6a0 {};
struct Tree_8db6a0 {
    int mCompare;                             // +0x00
    RBNodeBase_8db6a0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_8db6a0 DoInsertValueImpl(Node_8db6a0* pNodeParent, const Value_8db6a0& value, bool bForceToLeft);   // 0x008db560
    InsertResult_8db6a0 DoInsertValue(const Value_8db6a0& value, TrueType_8db6a0);
};

// @ 0x008db6a0
InsertResult_8db6a0 Tree_8db6a0::DoInsertValue(const Value_8db6a0& value, TrueType_8db6a0)
{
    Node_8db6a0* pCurrent = (Node_8db6a0*)mAnchor.mpNodeParent;
    Node_8db6a0* pLowerBound = (Node_8db6a0*)&mAnchor;
    Node_8db6a0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_8db6a0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_8db6a0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_8db6a0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_8db6a0*)RBTreeDecrement_8db6a0(pLowerBound);
        else {
            const Iterator_8db6a0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_8db6a0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_8db6a0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_8db6a0(itResult, true);
    }

    return InsertResult_8db6a0(Iterator_8db6a0(pLowerBound), false);
}
