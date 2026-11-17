// rbtree::DoInsertValue for unique keys (0x0082c6e0): walk down to the insertion point; insert (DoInsertValueImpl
// 0x82c000) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_82c6e0 { RBNodeBase_82c6e0* mpNodeRight; RBNodeBase_82c6e0* mpNodeLeft; RBNodeBase_82c6e0* mpNodeParent; int mColor; };
RBNodeBase_82c6e0* RBTreeDecrement_82c6e0(const RBNodeBase_82c6e0* pNode);   // 0x009215c0

struct Value_82c6e0 { uint32_t first; };
struct Node_82c6e0 : RBNodeBase_82c6e0 {
    Value_82c6e0 mValue;                         // +0x10
};
struct Iterator_82c6e0 {
    Node_82c6e0* mpNode;
    explicit Iterator_82c6e0(Node_82c6e0* p) : mpNode(p) {}
};
struct InsertResult_82c6e0 {
    Iterator_82c6e0 first;
    bool second;
    InsertResult_82c6e0(const Iterator_82c6e0& it, bool b) : first(it), second(b) {}
};
struct TrueType_82c6e0 {};
struct Tree_82c6e0 {
    int mCompare;                             // +0x00
    RBNodeBase_82c6e0 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_82c6e0 DoInsertValueImpl(Node_82c6e0* pNodeParent, const Value_82c6e0& value, bool bForceToLeft);   // 0x0082c000
    InsertResult_82c6e0 DoInsertValue(const Value_82c6e0& value, TrueType_82c6e0);
};

// @ 0x0082c6e0
InsertResult_82c6e0 Tree_82c6e0::DoInsertValue(const Value_82c6e0& value, TrueType_82c6e0)
{
    Node_82c6e0* pCurrent = (Node_82c6e0*)mAnchor.mpNodeParent;
    Node_82c6e0* pLowerBound = (Node_82c6e0*)&mAnchor;
    Node_82c6e0* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_82c6e0*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_82c6e0*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_82c6e0*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_82c6e0*)RBTreeDecrement_82c6e0(pLowerBound);
        else {
            const Iterator_82c6e0 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_82c6e0(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_82c6e0 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_82c6e0(itResult, true);
    }

    return InsertResult_82c6e0(Iterator_82c6e0(pLowerBound), false);
}
