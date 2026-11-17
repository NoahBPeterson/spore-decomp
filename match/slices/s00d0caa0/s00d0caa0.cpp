// rbtree::DoInsertValue for unique keys (0x00d0caa0): walk down to the insertion point; insert (DoInsertValueImpl
// 0xd0c970) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_d0caa0 { RBNodeBase_d0caa0* mpNodeRight; RBNodeBase_d0caa0* mpNodeLeft; RBNodeBase_d0caa0* mpNodeParent; int mColor; };
RBNodeBase_d0caa0* RBTreeDecrement_d0caa0(const RBNodeBase_d0caa0* pNode);   // 0x009215c0

struct Value_d0caa0 { uint32_t first; };
struct Node_d0caa0 : RBNodeBase_d0caa0 {
    Value_d0caa0 mValue;                         // +0x10
};
struct Iterator_d0caa0 {
    Node_d0caa0* mpNode;
    explicit Iterator_d0caa0(Node_d0caa0* p) : mpNode(p) {}
};
struct InsertResult_d0caa0 {
    Iterator_d0caa0 first;
    bool second;
    InsertResult_d0caa0(const Iterator_d0caa0& it, bool b) : first(it), second(b) {}
};
struct TrueType_d0caa0 {};
struct Tree_d0caa0 {
    int mCompare;                             // +0x00
    RBNodeBase_d0caa0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_d0caa0 DoInsertValueImpl(Node_d0caa0* pNodeParent, const Value_d0caa0& value, bool bForceToLeft);   // 0x00d0c970
    InsertResult_d0caa0 DoInsertValue(const Value_d0caa0& value, TrueType_d0caa0);
};

// @ 0x00d0caa0
InsertResult_d0caa0 Tree_d0caa0::DoInsertValue(const Value_d0caa0& value, TrueType_d0caa0)
{
    Node_d0caa0* pCurrent = (Node_d0caa0*)mAnchor.mpNodeParent;
    Node_d0caa0* pLowerBound = (Node_d0caa0*)&mAnchor;
    Node_d0caa0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_d0caa0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_d0caa0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_d0caa0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_d0caa0*)RBTreeDecrement_d0caa0(pLowerBound);
        else {
            const Iterator_d0caa0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_d0caa0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_d0caa0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_d0caa0(itResult, true);
    }

    return InsertResult_d0caa0(Iterator_d0caa0(pLowerBound), false);
}
