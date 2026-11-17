// rbtree::DoInsertValue for unique keys (0x00a09d80): walk down to the insertion point; insert (DoInsertValueImpl
// 0xa09cf0) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_a09d80 { RBNodeBase_a09d80* mpNodeRight; RBNodeBase_a09d80* mpNodeLeft; RBNodeBase_a09d80* mpNodeParent; int mColor; };
RBNodeBase_a09d80* RBTreeDecrement_a09d80(const RBNodeBase_a09d80* pNode);   // 0x009215c0

struct Value_a09d80 { uint32_t first; };
struct Node_a09d80 : RBNodeBase_a09d80 {
    Value_a09d80 mValue;                         // +0x10
};
struct Iterator_a09d80 {
    Node_a09d80* mpNode;
    explicit Iterator_a09d80(Node_a09d80* p) : mpNode(p) {}
};
struct InsertResult_a09d80 {
    Iterator_a09d80 first;
    bool second;
    InsertResult_a09d80(const Iterator_a09d80& it, bool b) : first(it), second(b) {}
};
struct TrueType_a09d80 {};
struct Tree_a09d80 {
    int mCompare;                             // +0x00
    RBNodeBase_a09d80 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_a09d80 DoInsertValueImpl(Node_a09d80* pNodeParent, const Value_a09d80& value, bool bForceToLeft);   // 0x00a09cf0
    InsertResult_a09d80 DoInsertValue(const Value_a09d80& value, TrueType_a09d80);
};

// @ 0x00a09d80
InsertResult_a09d80 Tree_a09d80::DoInsertValue(const Value_a09d80& value, TrueType_a09d80)
{
    Node_a09d80* pCurrent = (Node_a09d80*)mAnchor.mpNodeParent;
    Node_a09d80* pLowerBound = (Node_a09d80*)&mAnchor;
    Node_a09d80* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_a09d80*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_a09d80*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_a09d80*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_a09d80*)RBTreeDecrement_a09d80(pLowerBound);
        else {
            const Iterator_a09d80 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_a09d80(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_a09d80 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_a09d80(itResult, true);
    }

    return InsertResult_a09d80(Iterator_a09d80(pLowerBound), false);
}
