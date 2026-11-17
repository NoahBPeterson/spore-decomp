// rbtree::DoInsertValue for unique keys (0x005d9c80): walk down to the insertion point; insert (DoInsertValueImpl
// 0x5d9a50) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_5d9c80 { RBNodeBase_5d9c80* mpNodeRight; RBNodeBase_5d9c80* mpNodeLeft; RBNodeBase_5d9c80* mpNodeParent; int mColor; };
RBNodeBase_5d9c80* RBTreeDecrement_5d9c80(const RBNodeBase_5d9c80* pNode);   // 0x009215c0

struct Value_5d9c80 { uint32_t first; };
struct Node_5d9c80 : RBNodeBase_5d9c80 {
    Value_5d9c80 mValue;                         // +0x10
};
struct Iterator_5d9c80 {
    Node_5d9c80* mpNode;
    explicit Iterator_5d9c80(Node_5d9c80* p) : mpNode(p) {}
};
struct InsertResult_5d9c80 {
    Iterator_5d9c80 first;
    bool second;
    InsertResult_5d9c80(const Iterator_5d9c80& it, bool b) : first(it), second(b) {}
};
struct TrueType_5d9c80 {};
struct Tree_5d9c80 {
    int mCompare;                             // +0x00
    RBNodeBase_5d9c80 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_5d9c80 DoInsertValueImpl(Node_5d9c80* pNodeParent, const Value_5d9c80& value, bool bForceToLeft);   // 0x005d9a50
    InsertResult_5d9c80 DoInsertValue(const Value_5d9c80& value, TrueType_5d9c80);
};

// @ 0x005d9c80
InsertResult_5d9c80 Tree_5d9c80::DoInsertValue(const Value_5d9c80& value, TrueType_5d9c80)
{
    Node_5d9c80* pCurrent = (Node_5d9c80*)mAnchor.mpNodeParent;
    Node_5d9c80* pLowerBound = (Node_5d9c80*)&mAnchor;
    Node_5d9c80* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_5d9c80*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_5d9c80*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_5d9c80*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_5d9c80*)RBTreeDecrement_5d9c80(pLowerBound);
        else {
            const Iterator_5d9c80 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_5d9c80(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_5d9c80 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_5d9c80(itResult, true);
    }

    return InsertResult_5d9c80(Iterator_5d9c80(pLowerBound), false);
}
