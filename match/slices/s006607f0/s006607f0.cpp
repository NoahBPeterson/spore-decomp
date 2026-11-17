// rbtree::DoInsertValue for unique keys (0x006607f0): walk down to the insertion point; insert (DoInsertValueImpl
// 0x660770) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_6607f0 { RBNodeBase_6607f0* mpNodeRight; RBNodeBase_6607f0* mpNodeLeft; RBNodeBase_6607f0* mpNodeParent; int mColor; };
RBNodeBase_6607f0* RBTreeDecrement_6607f0(const RBNodeBase_6607f0* pNode);   // 0x009215c0

struct Value_6607f0 { uint32_t first; };
struct Node_6607f0 : RBNodeBase_6607f0 {
    Value_6607f0 mValue;                         // +0x10
};
struct Iterator_6607f0 {
    Node_6607f0* mpNode;
    explicit Iterator_6607f0(Node_6607f0* p) : mpNode(p) {}
};
struct InsertResult_6607f0 {
    Iterator_6607f0 first;
    bool second;
    InsertResult_6607f0(const Iterator_6607f0& it, bool b) : first(it), second(b) {}
};
struct TrueType_6607f0 {};
struct Tree_6607f0 {
    int mCompare;                             // +0x00
    RBNodeBase_6607f0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_6607f0 DoInsertValueImpl(Node_6607f0* pNodeParent, const Value_6607f0& value, bool bForceToLeft);   // 0x00660770
    InsertResult_6607f0 DoInsertValue(const Value_6607f0& value, TrueType_6607f0);
};

// @ 0x006607f0
InsertResult_6607f0 Tree_6607f0::DoInsertValue(const Value_6607f0& value, TrueType_6607f0)
{
    Node_6607f0* pCurrent = (Node_6607f0*)mAnchor.mpNodeParent;
    Node_6607f0* pLowerBound = (Node_6607f0*)&mAnchor;
    Node_6607f0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_6607f0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_6607f0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_6607f0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_6607f0*)RBTreeDecrement_6607f0(pLowerBound);
        else {
            const Iterator_6607f0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_6607f0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_6607f0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_6607f0(itResult, true);
    }

    return InsertResult_6607f0(Iterator_6607f0(pLowerBound), false);
}
