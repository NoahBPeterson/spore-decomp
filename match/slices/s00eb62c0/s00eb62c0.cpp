// rbtree::DoInsertValue for unique keys (0x00eb62c0): walk down to the insertion point; insert (DoInsertValueImpl
// 0xeb5b70) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_eb62c0 { RBNodeBase_eb62c0* mpNodeRight; RBNodeBase_eb62c0* mpNodeLeft; RBNodeBase_eb62c0* mpNodeParent; int mColor; };
RBNodeBase_eb62c0* RBTreeDecrement_eb62c0(const RBNodeBase_eb62c0* pNode);   // 0x009215c0

struct Value_eb62c0 { uint32_t first; };
struct Node_eb62c0 : RBNodeBase_eb62c0 {
    Value_eb62c0 mValue;                         // +0x10
};
struct Iterator_eb62c0 {
    Node_eb62c0* mpNode;
    explicit Iterator_eb62c0(Node_eb62c0* p) : mpNode(p) {}
};
struct InsertResult_eb62c0 {
    Iterator_eb62c0 first;
    bool second;
    InsertResult_eb62c0(const Iterator_eb62c0& it, bool b) : first(it), second(b) {}
};
struct TrueType_eb62c0 {};
struct Tree_eb62c0 {
    int mCompare;                             // +0x00
    RBNodeBase_eb62c0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_eb62c0 DoInsertValueImpl(Node_eb62c0* pNodeParent, const Value_eb62c0& value, bool bForceToLeft);   // 0x00eb5b70
    InsertResult_eb62c0 DoInsertValue(const Value_eb62c0& value, TrueType_eb62c0);
};

// @ 0x00eb62c0
InsertResult_eb62c0 Tree_eb62c0::DoInsertValue(const Value_eb62c0& value, TrueType_eb62c0)
{
    Node_eb62c0* pCurrent = (Node_eb62c0*)mAnchor.mpNodeParent;
    Node_eb62c0* pLowerBound = (Node_eb62c0*)&mAnchor;
    Node_eb62c0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_eb62c0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_eb62c0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_eb62c0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_eb62c0*)RBTreeDecrement_eb62c0(pLowerBound);
        else {
            const Iterator_eb62c0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_eb62c0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_eb62c0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_eb62c0(itResult, true);
    }

    return InsertResult_eb62c0(Iterator_eb62c0(pLowerBound), false);
}
