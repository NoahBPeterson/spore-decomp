// rbtree::DoInsertValue for unique keys (0x00cc57c0): walk down to the insertion point; insert (DoInsertValueImpl
// 0xcc5590) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_cc57c0 { RBNodeBase_cc57c0* mpNodeRight; RBNodeBase_cc57c0* mpNodeLeft; RBNodeBase_cc57c0* mpNodeParent; int mColor; };
RBNodeBase_cc57c0* RBTreeDecrement_cc57c0(const RBNodeBase_cc57c0* pNode);   // 0x009215c0

struct Value_cc57c0 { uint32_t first; };
struct Node_cc57c0 : RBNodeBase_cc57c0 {
    Value_cc57c0 mValue;                         // +0x10
};
struct Iterator_cc57c0 {
    Node_cc57c0* mpNode;
    explicit Iterator_cc57c0(Node_cc57c0* p) : mpNode(p) {}
};
struct InsertResult_cc57c0 {
    Iterator_cc57c0 first;
    bool second;
    InsertResult_cc57c0(const Iterator_cc57c0& it, bool b) : first(it), second(b) {}
};
struct TrueType_cc57c0 {};
struct Tree_cc57c0 {
    int mCompare;                             // +0x00
    RBNodeBase_cc57c0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_cc57c0 DoInsertValueImpl(Node_cc57c0* pNodeParent, const Value_cc57c0& value, bool bForceToLeft);   // 0x00cc5590
    InsertResult_cc57c0 DoInsertValue(const Value_cc57c0& value, TrueType_cc57c0);
};

// @ 0x00cc57c0
InsertResult_cc57c0 Tree_cc57c0::DoInsertValue(const Value_cc57c0& value, TrueType_cc57c0)
{
    Node_cc57c0* pCurrent = (Node_cc57c0*)mAnchor.mpNodeParent;
    Node_cc57c0* pLowerBound = (Node_cc57c0*)&mAnchor;
    Node_cc57c0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_cc57c0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_cc57c0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_cc57c0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_cc57c0*)RBTreeDecrement_cc57c0(pLowerBound);
        else {
            const Iterator_cc57c0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_cc57c0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_cc57c0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_cc57c0(itResult, true);
    }

    return InsertResult_cc57c0(Iterator_cc57c0(pLowerBound), false);
}
