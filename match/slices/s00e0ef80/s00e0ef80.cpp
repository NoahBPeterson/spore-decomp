// rbtree::DoInsertValue for unique keys (0x00e0ef80): walk down to the insertion point; insert (DoInsertValueImpl
// 0xe0ef00) unless a node with an equal key exists, which is returned with false.
#include "game/types.h"

struct RBNodeBase_e0ef80 { RBNodeBase_e0ef80* mpNodeRight; RBNodeBase_e0ef80* mpNodeLeft; RBNodeBase_e0ef80* mpNodeParent; int mColor; };
RBNodeBase_e0ef80* RBTreeDecrement_e0ef80(const RBNodeBase_e0ef80* pNode);   // 0x009215c0

struct Value_e0ef80 { uint32_t first; };
struct Node_e0ef80 : RBNodeBase_e0ef80 {
    Value_e0ef80 mValue;                         // +0x10
};
struct Iterator_e0ef80 {
    Node_e0ef80* mpNode;
    explicit Iterator_e0ef80(Node_e0ef80* p) : mpNode(p) {}
};
struct InsertResult_e0ef80 {
    Iterator_e0ef80 first;
    bool second;
    InsertResult_e0ef80(const Iterator_e0ef80& it, bool b) : first(it), second(b) {}
};
struct TrueType_e0ef80 {};
struct Tree_e0ef80 {
    int mCompare;                             // +0x00
    RBNodeBase_e0ef80 mAnchor;                   // +0x04
    unsigned mnSize;                          // +0x14
    Iterator_e0ef80 DoInsertValueImpl(Node_e0ef80* pNodeParent, const Value_e0ef80& value, bool bForceToLeft);   // 0x00e0ef00
    InsertResult_e0ef80 DoInsertValue(const Value_e0ef80& value, TrueType_e0ef80);
};

// @ 0x00e0ef80
InsertResult_e0ef80 Tree_e0ef80::DoInsertValue(const Value_e0ef80& value, TrueType_e0ef80)
{
    Node_e0ef80* pCurrent = (Node_e0ef80*)mAnchor.mpNodeParent;
    Node_e0ef80* pLowerBound = (Node_e0ef80*)&mAnchor;
    Node_e0ef80* pParent;
    bool bValueLessThanNode = true;

    while (pCurrent) {
        bValueLessThanNode = value.first < pCurrent->mValue.first;
        pLowerBound = pCurrent;
        if (bValueLessThanNode)
            pCurrent = (Node_e0ef80*)pCurrent->mpNodeLeft;
        else
            pCurrent = (Node_e0ef80*)pCurrent->mpNodeRight;
    }

    pParent = pLowerBound;

    if (bValueLessThanNode) {
        if (pLowerBound != (Node_e0ef80*)mAnchor.mpNodeLeft)
            pLowerBound = (Node_e0ef80*)RBTreeDecrement_e0ef80(pLowerBound);
        else {
            const Iterator_e0ef80 itResult(DoInsertValueImpl(pLowerBound, value, false));
            return InsertResult_e0ef80(itResult, true);
        }
    }

    if (pLowerBound->mValue.first < value.first) {
        const Iterator_e0ef80 itResult(DoInsertValueImpl(pParent, value, false));
        return InsertResult_e0ef80(itResult, true);
    }

    return InsertResult_e0ef80(Iterator_e0ef80(pLowerBound), false);
}
