// rbtree::DoInsertValue for unique keys (0x005d8e80): walk down to the insertion point; insert (DoInsertValueImpl
// 0x5d8df0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_5d8e80 { RBNodeBase_5d8e80* mpNodeRight; RBNodeBase_5d8e80* mpNodeLeft; RBNodeBase_5d8e80* mpNodeParent; int mColor; };
RBNodeBase_5d8e80* RBTreeDecrement_5d8e80(const RBNodeBase_5d8e80* pNode);   // 0x009215c0

struct Value_5d8e80 { uint32_t first; };
struct Node_5d8e80 : RBNodeBase_5d8e80 {
    Value_5d8e80 mValue;                         // +0x10
};
struct Iterator_5d8e80 {
    Node_5d8e80* mpNode;
    explicit Iterator_5d8e80(Node_5d8e80* p) : mpNode(p) {}
};
struct InsertResult_5d8e80 {
    Iterator_5d8e80 first;
    bool second;
    InsertResult_5d8e80(const Iterator_5d8e80& it, bool b) : first(it), second(b) {}
};
struct TrueType_5d8e80 {};
struct Tree_5d8e80 {
    int mCompare;                             // +0x00
    RBNodeBase_5d8e80 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_5d8e80 DoInsertValueImpl(Node_5d8e80* pNodeParent, const Value_5d8e80& value, bool bForceToLeft);   // 0x005d8df0
    InsertResult_5d8e80 DoInsertValue(const Value_5d8e80& value, TrueType_5d8e80);
};

// @ 0x005d8e80
InsertResult_5d8e80 Tree_5d8e80::DoInsertValue(const Value_5d8e80& value, TrueType_5d8e80)
{
    Node_5d8e80* pCurrent = (Node_5d8e80*)mAnchor.mpNodeParent;
    Node_5d8e80* pLowerBound = (Node_5d8e80*)&mAnchor;
    Node_5d8e80* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_5d8e80*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_5d8e80*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_5d8e80*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_5d8e80*)RBTreeDecrement_5d8e80(pLowerBound);
        else {
            const Iterator_5d8e80 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_5d8e80(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_5d8e80 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_5d8e80(itResult, true);
    }

    return InsertResult_5d8e80(Iterator_5d8e80(pLowerBound), false);
}
