// rbtree::DoInsertValue for unique keys (0x005f04c0): walk down to the insertion point; insert (DoInsertValueImpl
// 0x5f0390) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_5f04c0 { RBNodeBase_5f04c0* mpNodeRight; RBNodeBase_5f04c0* mpNodeLeft; RBNodeBase_5f04c0* mpNodeParent; int mColor; };
RBNodeBase_5f04c0* RBTreeDecrement_5f04c0(const RBNodeBase_5f04c0* pNode);   // 0x009215c0

struct Value_5f04c0 { uint32_t first; };
struct Node_5f04c0 : RBNodeBase_5f04c0 {
    Value_5f04c0 mValue;                         // +0x10
};
struct Iterator_5f04c0 {
    Node_5f04c0* mpNode;
    explicit Iterator_5f04c0(Node_5f04c0* p) : mpNode(p) {}
};
struct InsertResult_5f04c0 {
    Iterator_5f04c0 first;
    bool second;
    InsertResult_5f04c0(const Iterator_5f04c0& it, bool b) : first(it), second(b) {}
};
struct TrueType_5f04c0 {};
struct Tree_5f04c0 {
    int mCompare;                             // +0x00
    RBNodeBase_5f04c0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_5f04c0 DoInsertValueImpl(Node_5f04c0* pNodeParent, const Value_5f04c0& value, bool bForceToLeft);   // 0x005f0390
    InsertResult_5f04c0 DoInsertValue(const Value_5f04c0& value, TrueType_5f04c0);
};

// @ 0x005f04c0
InsertResult_5f04c0 Tree_5f04c0::DoInsertValue(const Value_5f04c0& value, TrueType_5f04c0)
{
    Node_5f04c0* pCurrent = (Node_5f04c0*)mAnchor.mpNodeParent;
    Node_5f04c0* pLowerBound = (Node_5f04c0*)&mAnchor;
    Node_5f04c0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_5f04c0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_5f04c0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_5f04c0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_5f04c0*)RBTreeDecrement_5f04c0(pLowerBound);
        else {
            const Iterator_5f04c0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_5f04c0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_5f04c0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_5f04c0(itResult, true);
    }

    return InsertResult_5f04c0(Iterator_5f04c0(pLowerBound), false);
}
