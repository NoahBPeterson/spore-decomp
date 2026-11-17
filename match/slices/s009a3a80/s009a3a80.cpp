// rbtree::DoInsertValue for unique keys (0x009a3a80): walk down to the insertion point; insert (DoInsertValueImpl
// 0x9a3980) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_9a3a80 { RBNodeBase_9a3a80* mpNodeRight; RBNodeBase_9a3a80* mpNodeLeft; RBNodeBase_9a3a80* mpNodeParent; int mColor; };
RBNodeBase_9a3a80* RBTreeDecrement_9a3a80(const RBNodeBase_9a3a80* pNode);   // 0x009215c0

struct Value_9a3a80 { uint32_t first; };
struct Node_9a3a80 : RBNodeBase_9a3a80 {
    Value_9a3a80 mValue;                         // +0x10
};
struct Iterator_9a3a80 {
    Node_9a3a80* mpNode;
    explicit Iterator_9a3a80(Node_9a3a80* p) : mpNode(p) {}
};
struct InsertResult_9a3a80 {
    Iterator_9a3a80 first;
    bool second;
    InsertResult_9a3a80(const Iterator_9a3a80& it, bool b) : first(it), second(b) {}
};
struct TrueType_9a3a80 {};
struct Tree_9a3a80 {
    int mCompare;                             // +0x00
    RBNodeBase_9a3a80 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_9a3a80 DoInsertValueImpl(Node_9a3a80* pNodeParent, const Value_9a3a80& value, bool bForceToLeft);   // 0x009a3980
    InsertResult_9a3a80 DoInsertValue(const Value_9a3a80& value, TrueType_9a3a80);
};

// @ 0x009a3a80
InsertResult_9a3a80 Tree_9a3a80::DoInsertValue(const Value_9a3a80& value, TrueType_9a3a80)
{
    Node_9a3a80* pCurrent = (Node_9a3a80*)mAnchor.mpNodeParent;
    Node_9a3a80* pLowerBound = (Node_9a3a80*)&mAnchor;
    Node_9a3a80* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_9a3a80*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_9a3a80*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_9a3a80*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_9a3a80*)RBTreeDecrement_9a3a80(pLowerBound);
        else {
            const Iterator_9a3a80 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_9a3a80(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_9a3a80 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_9a3a80(itResult, true);
    }

    return InsertResult_9a3a80(Iterator_9a3a80(pLowerBound), false);
}
